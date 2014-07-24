/*
NOKIA                                                             CONFIDENTIAL
Oulu
My Concurrent Audio
Kari Pohto



                  audio_pol_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1gif

project path:    global_interface/ISI/Core

name:            audio_pol_isi.h

version:         007.004

type:            incl

instance:        ou_pcms#1


ISI header file for Audio Policy

Current   ISI Version : 007.004
Supported ISI Versions: 000.001, 001.000, 002.000, 003.000, 004.000, 005.000, 
                        006.000, 007.000, 007.001, 007.002, 007.003, 007.004

Generated with autogen version 11w11 on 01-Apr-2011 12:31:13
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 007.004    NON-DRAFT   1-Apr-2011     Kari Pohto
Reason      : Change request
Reference   : ADB SWAM CR KP11040144090
Description : Added Entry AUD_POL_ROUTING_CAPTURE_MICROPHONE to AUD_POL_ROUTING
              Added Entry AUD_POL_ROUTING_CAPTURE_PLAYBACK to AUD_POL_ROUTING
              Added Entry AUD_POL_ROUTING_CAPTURE_RECORD to AUD_POL_ROUTING
               

Version     : 007.003    NON-DRAFT   1-Jan-2011     Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN11012153257
Description : Added Entry AUD_POL_PREF_TRACK_RECORDER to AUD_POL_APPL_PREF
               

Version     : 007.002    NON-DRAFT   11-Oct-2010    Kari Pohto
Reason      : Change request
Reference   : ADB SWAM CR KP10101136719
Description : Added Entry AUD_POL_AUDIO_MODE_FMTX to AUD_POL_AUDIO_MODE
               

Version     : 007.001    NON-DRAFT   31-May-2010    Kari Pohto
Reason      : Change request
Reference   : ADB SWAM CR KP10053157325
Description : Added Subblock AUD_POL_STATUS_IND_SB to AUD_POL_STATUS_RESP
              Added Subblock AUD_POL_STREAM_MUTE_REQ_SB to AUD_POL_VOLUME_REQ
              Added Subblock AUD_POL_STREAM_MUTE_RESP_SB to AUD_POL_VOLUME_RESP
              Added Subblock AUD_POL_STREAM_MUTE_REQ_SB
              Added Subblock AUD_POL_STREAM_MUTE_RESP_SB
              Added Entry AUD_POL_STATUS_TYPE_CLIENT_LIST to AUD_POL_STATUS_TYPE
               

Version     : 007.000    NON-DRAFT   25-Jul-2008    Petri E Hokkanen
Reason      : Change request
Reference   : ADB SWAM CR PH08081934540
Description : Added Subblock AUD_POL_STATUS_INFO_REQ_SB to AUD_POL_APPL_REQ
              Added Subblock AUD_POL_MODE_PROPERTIES_SB to AUD_POL_APPL_RESP
              Added Subblock AUD_POL_MODE_RESP_SB to AUD_POL_APPL_RESP
              Added Message AUD_POL_AUDIO_EFFECT_IND
              Added Message AUD_POL_AUDIO_EFFECT_REQ
              Added Message AUD_POL_AUDIO_EFFECT_RESP
              Changed Message AUD_POL_PRIVOL_NTF
              Changed Message AUD_POL_PRIVOL_REQ
              Added Subblock AUD_POL_MODE_PROPERTIES_SB to AUD_POL_STATUS_IND
              Added Message AUD_POL_STATUS_REQ
              Added Message AUD_POL_STATUS_RESP
              Added Subblock AUD_POL_MUTE_IND_SB to AUD_POL_VOLUME_IND
              Added Subblock AUD_POL_VOLUME_CHANGE_IND_SB to AUD_POL_VOLUME_IND
              Added Subblock AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB to AUD_POL_VOLUME_REQ
              Added Subblock AUD_POL_STREAM_VOLUME_REQ_SB to AUD_POL_VOLUME_REQ
              Added Subblock AUD_POL_VOLUME_CHANGE_REQ_SB to AUD_POL_VOLUME_REQ
              Added Subblock AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB to AUD_POL_VOLUME_RESP
              Added Subblock AUD_POL_STREAM_VOLUME_RESP_SB to AUD_POL_VOLUME_RESP
              Added Subblock AUD_POL_VOLUME_CHANGE_RESP_SB to AUD_POL_VOLUME_RESP
              Added Subblock AUD_POL_AUDIO_EFFECT_PHAP_SB
              Changed Subblock AUD_POL_MODE_IND_SB
              Added Subblock AUD_POL_MODE_PROPERTIES_SB
              Added Subblock AUD_POL_MODE_RESP_SB
              Added Subblock AUD_POL_MUTE_IND_SB
              Added Subblock AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB
              Added Subblock AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB
              Added Subblock AUD_POL_PRIVOL_CHANGE_NTF_SB
              Added Sequence AUD_POL_PROPERTY_SEQ
              Added Subblock AUD_POL_STATUS_INFO_REQ_SB
              Added Subblock AUD_POL_STREAM_VOLUME_REQ_SB
              Added Subblock AUD_POL_STREAM_VOLUME_RESP_SB
              Added Subblock AUD_POL_VOLUME_CHANGE_IND_SB
              Added Subblock AUD_POL_VOLUME_CHANGE_REQ_SB
              Added Subblock AUD_POL_VOLUME_CHANGE_RESP_SB
              Added Entry AUD_POL_PREF_MOBILE_TV to AUD_POL_APPL_PREF
              Added Entry AUD_POL_APPL_STREAMING to AUD_POL_APPL_TYPE
              Added Entry AUD_POL_APPL_VOLUME_UI to AUD_POL_APPL_TYPE
              Added Entry AUD_POL_AUDIO_MODE_STEREO_BT to AUD_POL_AUDIO_MODE
              Added Bitmask table AUD_POL_CAPABILITY_RESTRICTIONS
              Added Entry AUD_POL_PRIVOL_DEVICE_AVRCP to AUD_POL_DEVICE_TYPE
              Added Constant table AUD_POL_PROPERTY_TYPE
              Added Bitmask table AUD_POL_STATUS_TYPE
              Added Constant table AUD_POL_VOLUME_DIRECTION
              Added Constant AUD_POL_VALUE_NOT_VALID
               

Version     : 006.000    NON-DRAFT   19-May-2008    Juha Byman
Reason      : Change request
Reference   : ADB SWAM CR JB08052244175
Description : Changed Message AUD_POL_CONTROL_NTF
              Added Entry AUD_POL_PREF_ENTERTAINMENT_RADIO to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_KODIAK_POC to AUD_POL_APPL_PREF
              Added Entry AUD_POL_APPL_VIDEO_RECORDING to AUD_POL_APPL_TYPE
              Added Entry AUD_POL_APPL_VOICE_RECORDING to AUD_POL_APPL_TYPE
               

Version     : 005.000    NON-DRAFT   17-Mar-2008    Petri E Hokkanen
Reason      : Change request
Reference   : ADB SWAM CR PH08031744363
Description : Changed Subblock AUD_POL_MUTE_CONTROL_REQ_SB
               

Version     : 004.000    NON-DRAFT   4-Jan-2008     Petri E Hokkanen
Reason      : Change request
Reference   : ADB SWAM CR PH08010448841
Description : Added Subblock AUD_POL_MUTE_CONTROL_REQ_SB to AUD_POL_APPL_REQ
              Added Subblock AUD_POL_MUTE_CONTROL_RESP_SB to AUD_POL_APPL_RESP
              Added Subblock AUD_POL_MUTE_CONTROL_REQ_SB to AUD_POL_VOLUME_REQ
              Added Subblock AUD_POL_MUTE_CONTROL_RESP_SB to AUD_POL_VOLUME_RESP
              Added Subblock AUD_POL_MUTE_CONTROL_REQ_SB
              Added Subblock AUD_POL_MUTE_CONTROL_RESP_SB
              Changed Subblock AUD_POL_VOLUME_IND_SB
              Changed Subblock AUD_POL_VOL_CONTROL_REQ_SB
              Added Entry AUD_POL_PREF_NAVIGATION to AUD_POL_APPL_PREF
              Added Entry AUD_POL_AUDIO_MODE_BT to AUD_POL_AUDIO_MODE
              Added Entry AUD_POL_AUDIO_MODE_TVOUT to AUD_POL_AUDIO_MODE
              Added Entry AUD_POL_PRIVOL_DEVICE_LCIF to AUD_POL_DEVICE_TYPE
              Added Entry AUD_POL_PRIVOL_OWN_DEVICE to AUD_POL_DEVICE_TYPE
              Added Constant table AUD_POL_MIC_MUTING
              Added Entry AUD_POL_NOT_VALID_APPLICATION_ID to AUD_POL_REASON
              Added Constant table AUD_POL_SPEAKER_MUTING
              Discontinued Bitmask table AUD_POL_VOL_CONTROL_MUTING
              Discontinued Constant AUD_POL_VOL_LEVEL_NOT_RELEVANT
              AUD_POL_APPL_PREF_AUDIO_PROMPTING and
              AUD_POL_APPL_PREF_AUDIO_READING application preferenses
              renamed. Old names can still be used.

Version     : 003.000    NON-DRAFT   14-Nov-2007    Petri E Hokkanen
Reason      : Change request
Reference   : ADB SWAM CR PH07111443710
Description : Added Constant AUD_POL_APPL_ID_NOT_DEFINED
              Added Constant AUD_POL_VOL_LEVEL_NOT_RELEVANT
              AUD_POL_APPL_KARAOKE and AUD_POL_APPL_DICTAPHONE application
              types removed. AUD_POL_APPL_PREF_DEMO_ALERT application
              preference removed.

Version     : 002.000    NON-DRAFT   26-Mar-2007    Petteri Hyvonen
Reason      : Change request
Reference   : ADB SWAM CR EH07031543236
Description : Added Subblock AUD_POL_VOL_CONTROL_REQ_SB to AUD_POL_APPL_REQ
              Changed Message AUD_POL_APPL_RESP
              Added Message AUD_POL_PRIVOL_NTF
              Added Message AUD_POL_PRIVOL_REQ
              Added Message AUD_POL_PRIVOL_RESP
              Added Subblock AUD_POL_MODE_IND_SB to AUD_POL_STATUS_IND
              Changed Message AUD_POL_VOLUME_RESP
              Changed Subblock AUD_POL_APPL_ADD_STREAM_RESP_SB
              Changed Subblock AUD_POL_APPL_DESCRIPTOR_RESP_SB
              Changed Subblock AUD_POL_APPL_REMOVE_APPL_RESP_SB
              Changed Subblock AUD_POL_APPL_REMOVE_STREAM_RESP_SB
              Added Subblock AUD_POL_MODE_IND_SB
              Changed Subblock AUD_POL_VOL_CONTROL_RESP_SB
              Added Entry AUD_POL_PREF_AUDIO_PROMPTING to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_AUDIO_READING to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_DEMO_UI to AUD_POL_APPL_PREF
              Added Entry AUD_POL_APPL_FM_RECORDING to AUD_POL_APPL_TYPE
              Added Entry AUD_POL_APPL_SILENT_PLAYBACK to AUD_POL_APPL_TYPE
              Added Constant table AUD_POL_AUDIO_MODE
              Added Constant table AUD_POL_DEVICE_TYPE
              Added Entry AUD_POL_DIRECTIVE_DO_RESUME to AUD_POL_DIRECTIVE
              Added Entry AUD_POL_DIRECTIVE_DO_START to AUD_POL_DIRECTIVE
              Added Entry AUD_POL_DIRECTIVE_UNMUTED to AUD_POL_DIRECTIVE
              Added Entry AUD_POL_DIR_REASON_MODE_CHANGED to AUD_POL_DIRECTIVE_REASON
              Added Constant table AUD_POL_PRIVOL_COMMAND
              Added Constant table AUD_POL_REASON
              Added Entry AUD_POL_ROUTING_RX to AUD_POL_ROUTING
               

Version     : 001.000    NON-DRAFT   24-May-2006    Jani Pellikka
Reason      : Change request
Reference   : ADB SWAM CR JP06052439808
Description : Changed Message AUD_POL_CONTROL_NTF
              Added Message AUD_POL_RESOURCE_REQ
              Added Message AUD_POL_RESOURCE_RESP
              Added Message AUD_POL_STATUS_IND
              Added Message AUD_POL_VOLUME_IND
              Added Subblock AUD_POL_RESOURCE_REQ_SB
              Added Subblock AUD_POL_RESOURCE_RESP_SB
              Added Subblock AUD_POL_STATUS_IND_SB
              Added Subblock AUD_POL_VOLUME_IND_SB
              Changed Subblock AUD_POL_VOL_CONTROL_REQ_SB
              Added Entry AUD_POL_PREF_BATTERY_ALARM to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_CONFIRM_NOTIFY to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_COUNTDOWN_TIMER to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_ENTERTAINMENT to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_KEY_PRESS to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_NETWORK_TONE to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_SOUND_DEMOING to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_STARTUP_SHUTDOWN to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_VOICE_TRAINING to AUD_POL_APPL_PREF
              Added Entry AUD_POL_PREF_WARNING to AUD_POL_APPL_PREF
              Added Entry AUD_POL_DIRECTIVE_BLOCKED to AUD_POL_DIRECTIVE
              Added Entry AUD_POL_DIRECTIVE_REPLACE_WITH_BEEP to AUD_POL_DIRECTIVE
              Added Constant table AUD_POL_ENC_DEC_TYPE
              Added Constant table AUD_POL_RESOURCE_REASON
              Added Constant table AUD_POL_STATUS
               

Version     : 000.001    NON-DRAFT   02-Mar-2006    Marko Kangasluoma
Reason      : Change request
Reference   : ADB SWAM CR MK06022753147
Description : File created and Audio Policy implemented

------------------------------------------------------------------------------
*/

#ifndef _AUDIO_POL_ISI_H
#define _AUDIO_POL_ISI_H

#include "isi_conf.h"

#ifndef AUD_POL_ISI_VERSION
#define AUD_POL_ISI_VERSION
#define AUD_POL_ISI_VERSION_Z   7
#define AUD_POL_ISI_VERSION_Y   4
#endif

#define AUD_POL_ISI_MIN_VERSION(z,y) \
 ((AUD_POL_ISI_VERSION_Z == (z) && AUD_POL_ISI_VERSION_Y >= (y)) || \
  (AUD_POL_ISI_VERSION_Z > (z)))

#if !AUD_POL_ISI_MIN_VERSION(0,1)
#error The specified interface version is not supported by this header file
#elif AUD_POL_ISI_MIN_VERSION(7,5)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */


#if AUD_POL_ISI_MIN_VERSION(3,0) && !AUD_POL_ISI_MIN_VERSION(4,0)
#define AUD_POL_VOL_LEVEL_NOT_RELEVANT           0x00
#endif /* AUD_POL_ISI_MIN_VERSION(3,0) && !AUD_POL_ISI_MIN_VERSION(4,0) */

#define AUD_POL_APPL_ID_NOT_DEFINED              0x00
#define AUD_POL_VALUE_NOT_VALID                  0xFFFF
/* constant for variable-length definitions */
#define AUD_POL_ANY_SIZE                         1

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_APPL_TYPE - Valid from version 000.001          */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_POL_APPL_TYPE_CONST;

#define AUD_POL_APPL_NONE                        0x0000  /* None */
#define AUD_POL_APPL_CS_CALL                     0x0001  /* CS call */
#define AUD_POL_APPL_PS_CALL                     0x0002  /* PS call */
#define AUD_POL_APPL_PTT_CALL                    0x0003  /* PTT call */
#define AUD_POL_APPL_MUSIC                       0x0004  /* Music */
/* Tone generation */
#define AUD_POL_APPL_TONE_GEN                    0x0005
/* DTMF generation */
#define AUD_POL_APPL_DTMF_GEN                    0x0006
#define AUD_POL_APPL_FM_RADIO                    0x0007  /* FM radio */
#define AUD_POL_APPL_VOICE_CLIP                  0x0008  /* Voice clip */
/* Voice recognition */
#define AUD_POL_APPL_VOICE_RECOG                 0x0009
#define AUD_POL_APPL_VIDEO_AUDIO                 0x000A  /* Video audio */
/* Silent playback */
#define AUD_POL_APPL_SILENT_PLAYBACK             0x000B
#define AUD_POL_APPL_FM_RECORDING                0x000C  /* FM recording */
/* Voice recording */
#define AUD_POL_APPL_VOICE_RECORDING             0x000D
/* Video recording */
#define AUD_POL_APPL_VIDEO_RECORDING             0x000E
/* Video/audio streaming */
#define AUD_POL_APPL_STREAMING                   0x000F
#define AUD_POL_APPL_VOLUME_UI                   0x0010  /* Volume UI */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_APPL_PREF - Valid from version 000.001          */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_POL_APPL_PREF_CONST;

#define AUD_POL_PREF_NONE                        0x0000  /* None */
#define AUD_POL_PREF_RINGING                     0x0001  /* Ringing */
/* Entertainment camera */
#define AUD_POL_PREF_ENTERTAINMENT_CAMERA        0x0002
/* Entertainment music */
#define AUD_POL_PREF_ENTERTAINMENT_MUSIC         0x0003
/* Entertainment game */
#define AUD_POL_PREF_ENTERTAINMENT_GAME          0x0004
#define AUD_POL_PREF_CS_CALL                     0x0005  /* CS call */
/* CS call emergency */
#define AUD_POL_PREF_CS_CALL_EMERGENCY           0x0006
#define AUD_POL_PREF_PS_CALL                     0x0007  /* PS call */
#define AUD_POL_PREF_VIDEO_CALL                  0x0008  /* Video call */
#define AUD_POL_PREF_UI_TONE                     0x0009  /* UI tone */
#define AUD_POL_PREF_SMS_ALERT                   0x000A  /* SMS alert */
/* Calendar alarm */
#define AUD_POL_PREF_CALENDAR_ALARM              0x000B
#define AUD_POL_PREF_ERROR_TONE                  0x000C  /* Error tone */
/* Wake-up alarm */
#define AUD_POL_PREF_WAKE_UP_ALARM               0x000D
/* Camera shutter */
#define AUD_POL_PREF_CAMERA_SHUTTER              0x000E
/* Entertainment */
#define AUD_POL_PREF_ENTERTAINMENT               0x000F
/* Voice training */
#define AUD_POL_PREF_VOICE_TRAINING              0x0010
/* Sound demoing */
#define AUD_POL_PREF_SOUND_DEMOING               0x0011
#define AUD_POL_PREF_KEY_PRESS                   0x0012  /* Key press */
/* Confirmation notification */
#define AUD_POL_PREF_CONFIRM_NOTIFY              0x0013
#define AUD_POL_PREF_WARNING                     0x0014  /* Warning */
#define AUD_POL_PREF_NETWORK_TONE                0x0015  /* Network tone */
/* Battery alarm */
#define AUD_POL_PREF_BATTERY_ALARM               0x0016
/* Startup/shutdown */
#define AUD_POL_PREF_STARTUP_SHUTDOWN            0x0017
/* Countdown timer */
#define AUD_POL_PREF_COUNTDOWN_TIMER             0x0018
/* Audio prompting */
#define AUD_POL_PREF_AUDIO_PROMPTING             0x0019
#define AUD_POL_APPL_PREF_AUDIO_PROMPTING        AUD_POL_PREF_AUDIO_PROMPTING
/* Audio reading */
#define AUD_POL_PREF_AUDIO_READING               0x001A
#define AUD_POL_APPL_PREF_AUDIO_READING          AUD_POL_PREF_AUDIO_READING
#define AUD_POL_PREF_DEMO_UI                     0x001B  /* Demo UI */
/* Navigation Instructions */
#define AUD_POL_PREF_NAVIGATION                  0x001C
/* FM Radio playback */
#define AUD_POL_PREF_ENTERTAINMENT_RADIO         0x001D
#define AUD_POL_PREF_KODIAK_POC                  0x001E  /* Kodiak PoC */
#define AUD_POL_PREF_MOBILE_TV                   0x001F  /* Mobile TV */
/* Track Recorder */
#define AUD_POL_PREF_TRACK_RECORDER              0x0020

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_POL_ROUTING - Valid from version 000.001             */
/* ----------------------------------------------------------------------- */
/* For CALL use case, all these routings should be used: AUD_POL_ROUTING_TX,
   AUD_POL_ROUTING_RX, AUD_POL_ROUTING_PLAY, AUD_POL_ROUTING_RECORD.
*/
typedef uint32 AUD_POL_ROUTING_CONST;

/* None */
#define AUD_POL_ROUTING_NONE                     0x00000000  /* 00000000000000000000000000000000 */
/* Public */
#define AUD_POL_ROUTING_PUBLIC                   0x00000001  /* -------------------------------1 */
/* Private */
#define AUD_POL_ROUTING_PRIVATE                  0x00000002  /* ------------------------------1- */
/* Default */
#define AUD_POL_ROUTING_DEFAULT                  0x00000004  /* -----------------------------100 */
/* Play */
#define AUD_POL_ROUTING_PLAY                     0x00000008  /* ----------------------------1--- */
/* Record */
#define AUD_POL_ROUTING_RECORD                   0x00000010  /* ---------------------------1---- */
/* TX, should be used with AUD_POL_ROUTING_PLAY */
#define AUD_POL_ROUTING_TX                       0x00000020  /* --------------------------1----- */
/* RX, should be used with AUD_POL_ROUTING_RECORD */
#define AUD_POL_ROUTING_RX                       0x00000040  /* -------------------------1------ */
/* Capture microphone, should be used with AUD_POL_ROUTING_RECORD */
#define AUD_POL_ROUTING_CAPTURE_MICROPHONE       0x00000080  /* ------------------------1------- */
/* Capture playback streams, should be used with AUD_POL_ROUTING_RECORD */
#define AUD_POL_ROUTING_CAPTURE_PLAYBACK         0x00000100  /* -----------------------1-------- */
/* Capture recording streams, should be used with AUD_POL_ROUTING_RECORD */
#define AUD_POL_ROUTING_CAPTURE_RECORD           0x00000200  /* ----------------------1--------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_POL_FLAGS - Valid from version 000.001               */
/* ----------------------------------------------------------------------- */
typedef uint32 AUD_POL_FLAGS_CONST;

/* None */
#define AUD_POL_FLAG_NONE                        0x00000000  /* 00000000000000000000000000000000 */
/* Audio policy pauses the application if this flag has been set and
   accessory is disconnected. In case of FM radio, the application is muted
   when accessory is disconnected.
*/
#define AUD_POL_FLAG_MUTE_ACC_CHANGE             0x00000001  /* -------------------------------1 */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_POL_CAPABILITY_RESTRICTIONS - Valid from version 007.000 */
/* ----------------------------------------------------------------------- */
typedef uint32 AUD_POL_CAPABILITY_RESTRICTIONS_CONST;

/* None */
#define AUD_POL_CAPABILITY_NONE                  0x00000000  /* 00000000000000000000000000000000 */
/* No volume */
#define AUD_POL_CAPABILITY_NO_VOLUME             0x00000001  /* ------------------------------01 */
/* Inc/Dec volume */
#define AUD_POL_CAPABILITY_INCDEC_VOLUME         0x00000002  /* ------------------------------10 */
/* DRM protected content not allowed */
#define AUD_POL_CAPABILITY_NO_DRM_CONTENT        0x00000004  /* -----------------------------1-- */
/* No voice recognition */
#define AUD_POL_CAPABILITY_NO_RECOGNITION        0x00000008  /* ----------------------------1--- */
/* No speaker mute */
#define AUD_POL_CAPABILITY_NO_SPEAKER_MUTE       0x00000010  /* ---------------------------1---- */
/* No microphone mute */
#define AUD_POL_CAPABILITY_NO_MIC_MUTE           0x00000020  /* --------------------------1----- */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_AUDIOBAND - Valid from version 000.001          */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_AUDIOBAND_CONST;

#define AUD_AUDIOBAND_NONE                       0x00  /* None */
#define AUD_AUDIOBAND_NB                         0x01  /* Narrowband */
#define AUD_AUDIOBAND_WB                         0x02  /* Wideband */
#define AUD_AUDIOBAND_HQ                         0x03  /* High Quality */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_POL_VOL_CONTROL_MUTING - Versions 000.001 - 004.000  */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(4,0)
typedef uint8 AUD_POL_VOL_CONTROL_MUTING_CONST;

/* None */
#define AUD_POL_VOL_CONTROL_NONE                 0x00  /* 00000000 */
/* Mute playback */
#define AUD_POL_VOL_CONTROL_MUTE_PLAY            0x01  /* -------1 */
/* Mute record */
#define AUD_POL_VOL_CONTROL_MUTE_RECORD          0x02  /* ------1- */
#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(4,0) */


/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_POL_STATUS_TYPE - Valid from version 007.000         */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_STATUS_TYPE_CONST;

/* None */
#define AUD_POL_STATUS_TYPE_NONE                 0x00  /* 00000000 */
/* Current audio mode */
#define AUD_POL_STATUS_TYPE_AUDIO_MODE           0x01  /* -------1 */
/* Audio mode properties */
#define AUD_POL_STATUS_TYPE_MODE_PROPERTIES      0x02  /* ------1- */
/* List of registered clients */
#define AUD_POL_STATUS_TYPE_CLIENT_LIST          0x04  /* -----1-- */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_MIC_MUTING - Valid from version 004.000         */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_MIC_MUTING_CONST;

/* Microphone mute not changed */
#define AUD_POL_MIC_MUTE_NOT_RELEVANT            0x00
/* Microphone muted */
#define AUD_POL_MIC_MUTE                         0x01
/* Microphone unmuted */
#define AUD_POL_MIC_UNMUTE                       0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_SPEAKER_MUTING - Valid from version 004.000     */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_SPEAKER_MUTING_CONST;

/* Speaker mute not changed */
#define AUD_POL_SPEAKER_MUTE_NOT_RELEVANT        0x00
#define AUD_POL_SPEAKER_MUTE                     0x01  /* Speaker muted */
/* Speaker unmuted */
#define AUD_POL_SPEAKER_UNMUTE                   0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_DIRECTIVE - Valid from version 000.001          */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_DIRECTIVE_CONST;

#define AUD_POL_DIRECTIVE_NONE                   0x00  /* None */
#define AUD_POL_DIRECTIVE_DO_PAUSE               0x01  /* Do pause */
#define AUD_POL_DIRECTIVE_DO_STOP                0x02  /* Do stop */
#define AUD_POL_DIRECTIVE_DO_REMOVE              0x03  /* Do remove */
#define AUD_POL_DIRECTIVE_REMOVED                0x04  /* Removed */
#define AUD_POL_DIRECTIVE_MUTED                  0x05  /* Muted */
/* Replace with beep */
#define AUD_POL_DIRECTIVE_REPLACE_WITH_BEEP      0x06
#define AUD_POL_DIRECTIVE_BLOCKED                0x07  /* Blocked */
#define AUD_POL_DIRECTIVE_DO_START               0x08  /* Do start */
#define AUD_POL_DIRECTIVE_DO_RESUME              0x09  /* Do resume */
#define AUD_POL_DIRECTIVE_UNMUTED                0x0A  /* Unmuted */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_DIRECTIVE_REASON - Valid from version 000.001   */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_DIRECTIVE_REASON_CONST;

#define AUD_POL_DIR_REASON_NONE                  0x00  /* None */
#define AUD_POL_DIR_REASON_OUT_OF_MIPS           0x01  /* Out of MIPS */
#define AUD_POL_DIR_REASON_OUT_OF_MEMORY         0x02  /* Out of memory */
/* Higher priority */
#define AUD_POL_DIR_REASON_HIGHER_PRIORITY       0x03
#define AUD_POL_DIR_REASON_MODE_CHANGED          0x04  /* Mode changed */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_DIRECTIVE_STATUS - Valid from version 000.001   */
/* ----------------------------------------------------------------------- */
/* AUD_POL_DIR_STATUS_PROCEEDING and AUD_POL_DIR_STATUS_CHALLENGE are
   reserved for future. The client could inform the Audio Policy that it
   takes longer time to perform some action so Audio Policy could have some
   logic to handle the situation.
*/
typedef uint8 AUD_POL_DIRECTIVE_STATUS_CONST;

#define AUD_POL_DIR_STATUS_NONE                  0x00  /* None */
#define AUD_POL_DIR_STATUS_PROCEEDING            0x01  /* Proceeding */
#define AUD_POL_DIR_STATUS_COMPLETED             0x02  /* Completed */
#define AUD_POL_DIR_STATUS_CHALLENGE             0x03  /* Challenge */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_RESOURCE_REASON - Valid from version 001.000    */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_RESOURCE_REASON_CONST;

#define AUD_POL_RESOURCE_OK                      0x00  /* OK */
#define AUD_POL_RESOURCE_FAIL                    0x01  /* FAIL */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_STATUS - Valid from version 001.000             */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_STATUS_CONST;

#define AUD_POL_STATUS_ACTIVE                    0x00  /* ACTIVE */
#define AUD_POL_STATUS_INACTIVE                  0x01  /* INACTIVE */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_ENC_DEC_TYPE - Valid from version 001.000       */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_POL_ENC_DEC_TYPE_CONST;

#define AUD_POL_DEC_MP3                          0x0001  /* MP3 decoder */
#define AUD_POL_DEC_AAC                          0x0002  /* AAC decoder */
/* eACC+ decoder */
#define AUD_POL_DEC_EAACPLUS                     0x0003
/* AMR narrow band decoder */
#define AUD_POL_DEC_AMRNB                        0x0004
/* DSP AMR narrow band decoder */
#define AUD_POL_DEC_DSP_AMRNB                    0x0005
/* AMR wide band decoder */
#define AUD_POL_DEC_AMRWB                        0x0006
/* DSP AMR wide band decoder */
#define AUD_POL_DEC_DSP_AMRWB                    0x0007
/* PCM (non-encoded) decoder */
#define AUD_POL_DEC_PCM                          0x0008
/* AMR narrow band encoder */
#define AUD_POL_ENC_AMRNB                        0x0009
/* DSP AMR narrow band encoder */
#define AUD_POL_ENC_DSP_AMRNB                    0x000A
/* AMR wide band encoder */
#define AUD_POL_ENC_AMRWB                        0x000B
/* DSP AMR wide band encoder */
#define AUD_POL_ENC_DSP_AMRWB                    0x000C
/* PCM (non-encoded) decoder */
#define AUD_POL_ENC_PCM                          0x000D
/* Speech-to-text encoder */
#define AUD_POL_ENC_SPEECH_TO_TEXT               0x000E
/* Text-to-speech encoder */
#define AUD_POL_ENC_TEXT_TO_SPEECH               0x000F
#define AUD_POL_ENC_ACC                          0x0010  /* ACC encoder */
/* MIDI synthesizer */
#define AUD_POL_SYNTH_MIDI                       0x0011

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_AUDIO_MODE - Valid from version 002.000         */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_AUDIO_MODE_CONST;

#define AUD_POL_AUDIO_MODE_HANDPORTABLE          0x00  /* Handportable */
/* Integrated handsfree */
#define AUD_POL_AUDIO_MODE_IHF                   0x01
/* Headset without MIC */
#define AUD_POL_AUDIO_MODE_HEADPHONES            0x02
/* Headset with MIC */
#define AUD_POL_AUDIO_MODE_HEADSET               0x03
/* Hearing aid loopset */
#define AUD_POL_AUDIO_MODE_LOOPSET               0x04
#define AUD_POL_AUDIO_MODE_CARKIT                0x05  /* Car handsfree */
/* Teletype device */
#define AUD_POL_AUDIO_MODE_TTY                   0x06
#define AUD_POL_AUDIO_MODE_MUSICSTAND            0x07  /* Music stand */
#define AUD_POL_AUDIO_MODE_LINEOUT               0x08  /* Line out */
#define AUD_POL_AUDIO_MODE_TVOUT                 0x09  /* TV OUT */
#define AUD_POL_AUDIO_MODE_BT                    0x0A  /* Bluetooth */
/* Stereo Bluetooth */
#define AUD_POL_AUDIO_MODE_STEREO_BT             0x0B
#define AUD_POL_AUDIO_MODE_FMTX                  0x0C  /* FM TX */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_VOLUME_DIRECTION - Valid from version 007.000   */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_VOLUME_DIRECTION_CONST;

/* Increase the current volume */
#define AUD_POL_VOLDIR_INCREASE                  0x01
/* Decrease the current volume */
#define AUD_POL_VOLDIR_DECREASE                  0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_PRIVOL_COMMAND - Valid from version 002.000     */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_PRIVOL_COMMAND_CONST;

#define AUD_POL_PRIVOL_SUBSCRIBE                 0x01  /* Subscribe */
#define AUD_POL_PRIVOL_ADJUST                    0x02  /* Adjust */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_DEVICE_TYPE - Valid from version 002.000        */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_DEVICE_TYPE_CONST;

/* Change has happened in the own device */
#define AUD_POL_PRIVOL_OWN_DEVICE                0x00
#define AUD_POL_PRIVOL_DEVICE_BT                 0x01  /* Bluetooth */
/* Local connectivity interface accessories */
#define AUD_POL_PRIVOL_DEVICE_LCIF               0x02
/* Audio/Video Remote Control Profile used with A2DP devices */
#define AUD_POL_PRIVOL_DEVICE_AVRCP              0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_PROPERTY_TYPE - Valid from version 007.000      */
/* ----------------------------------------------------------------------- */
typedef uint32 AUD_POL_PROPERTY_TYPE_CONST;

/* Value is TRUE, if audio mode is analog and FALSE if it is digital. */
#define AUD_POL_PROPERTY_TYPE_IS_ANALOG          0x00000001

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_POL_REASON - Valid from version 002.000             */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_POL_REASON_CONST;

#define AUD_POL_OK                               0x00  /* Ok */
#define AUD_POL_FAIL                             0x01  /* Fail */
#define AUD_POL_OUT_OF_RANGE                     0x02  /* Out of range */
#define AUD_POL_INVALID_DEVICE                   0x03  /* Invalid device */
#define AUD_POL_NOT_ALLOWED                      0x04  /* Not allowed */
#define AUD_POL_NOT_SUPPORTED                    0x05  /* Not supported */
/* Replaced with beep */
#define AUD_POL_REPLACED_WITH_BEEP               0x06
/* Blocked by user */
#define AUD_POL_BLOCKED_BY_USER                  0x07
/* Feature not allowed */
#define AUD_POL_FEATURE_NOT_ALLOWED              0x08
#define AUD_POL_OUT_OF_MIPS                      0x09  /* Out of MIPS */
#define AUD_POL_OUT_OF_MEMORY                    0x0A  /* Out of memory */
/* Higher priority */
#define AUD_POL_HIGHER_PRIORITY                  0x0B
/* Invalid descriptor */
#define AUD_POL_INVALID_DESCRIPTOR               0x0C
/* Accessory change */
#define AUD_POL_ACCESSORY_CHANGE                 0x0D
#define AUD_POL_CLIENT_REQUEST                   0x0E  /* Client request */
/* Not valid application ID */
#define AUD_POL_NOT_VALID_APPLICATION_ID         0x0F

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define AUD_POL_APPL_REQ                         0xA0
#define AUD_POL_APPL_RESP                        0xA1
#define AUD_POL_VOLUME_REQ                       0xA2
#define AUD_POL_VOLUME_RESP                      0xA3
#define AUD_POL_CONTROL_NTF                      0xA4
#define AUD_POL_APPL_NTF                         0xA5
#define AUD_POL_RESOURCE_REQ                     0xA6
#define AUD_POL_RESOURCE_RESP                    0xA7
#define AUD_POL_STATUS_IND                       0xA8
#define AUD_POL_VOLUME_IND                       0xA9
#define AUD_POL_PRIVOL_REQ                       0xAA
#define AUD_POL_PRIVOL_RESP                      0xAB
#define AUD_POL_PRIVOL_NTF                       0xAC
#define AUD_POL_STATUS_REQ                       0xAD
#define AUD_POL_STATUS_RESP                      0xAE
#define AUD_POL_AUDIO_EFFECT_REQ                 0xAF
#define AUD_POL_AUDIO_EFFECT_RESP                0xB0
#define AUD_POL_AUDIO_EFFECT_IND                 0xB1

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define AUD_POL_APPL_DESCRIPTOR_REQ_SB           0x01
#define AUD_POL_APPL_ADD_STREAM_REQ_SB           0x03
#define AUD_POL_APPL_REMOVE_STREAM_REQ_SB        0x07
#define AUD_POL_APPL_REMOVE_APPL_REQ_SB          0x05
#define AUD_POL_VOL_CONTROL_REQ_SB               0x09
#define AUD_POL_MUTE_CONTROL_REQ_SB              0x11
#define AUD_POL_VOLUME_CHANGE_REQ_SB             0x16
#define AUD_POL_PRIVOL_CHANGE_NTF_SB             0x1D
#define AUD_POL_STREAM_VOLUME_REQ_SB             0x1A
#define AUD_POL_STREAM_MUTE_REQ_SB               0x20
#define AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB       0x1E
#define AUD_POL_CONTROL_PRIORITY_NTF_SB          0x0B
#define AUD_POL_APPL_DESCRIPTOR_RESP_SB          0x02
#define AUD_POL_APPL_ADD_STREAM_RESP_SB          0x04
#define AUD_POL_APPL_REMOVE_STREAM_RESP_SB       0x08
#define AUD_POL_APPL_REMOVE_APPL_RESP_SB         0x06
#define AUD_POL_VOL_CONTROL_RESP_SB              0x0A
#define AUD_POL_MUTE_CONTROL_RESP_SB             0x12
#define AUD_POL_VOLUME_CHANGE_RESP_SB            0x17
#define AUD_POL_STREAM_VOLUME_RESP_SB            0x1B
#define AUD_POL_STREAM_MUTE_RESP_SB              0x21
#define AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB      0x1F
#define AUD_POL_RESOURCE_REQ_SB                  0x0C
#define AUD_POL_RESOURCE_RESP_SB                 0x0D
#define AUD_POL_VOLUME_IND_SB                    0x0E
#define AUD_POL_VOLUME_CHANGE_IND_SB             0x18
#define AUD_POL_MUTE_IND_SB                      0x19
#define AUD_POL_STATUS_IND_SB                    0x0F
#define AUD_POL_MODE_IND_SB                      0x10
#define AUD_POL_MODE_RESP_SB                     0x13
#define AUD_POL_STATUS_INFO_REQ_SB               0x15
#define AUD_POL_MODE_PROPERTIES_SB               0x14
#define AUD_POL_AUDIO_EFFECT_PHAP_SB             0x1C

/* ----------------------------------------------------------------------- */
/* Sequence: AUD_POL_PROPERTY_SEQ - Valid from version 007.000             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    /* Values from the constant table AUD_POL_PROPERTY_TYPE */
    uint32  property_type;
    uint32  property_value; /* Value depends what is the type of property */
    } AUD_POL_PROPERTY_SEQ_STR;

#define SIZE_AUD_POL_PROPERTY_SEQ_STR   sizeof(AUD_POL_PROPERTY_SEQ_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_DESCRIPTOR_REQ_SB - Valid from version 000.001   */
/* ----------------------------------------------------------------------- */
/* This SB can be sent by application also to update its information (not
   only when the application registers IN)
*/

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint8   audioband; /* Values from the constant table AUD_POL_AUDIOBAND */
    uint8   filler1;
    uint16  appl_type; /* Values from the constant table AUD_POL_APPL_TYPE */
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    uint32  flags;        /* Values from the bitmask table AUD_POL_FLAGS */
    uint32  routing;      /* Values from the bitmask table AUD_POL_ROUTING */
    } tISI_AudPolApplDescriptorReqSB;

#define AUD_POL_APPL_DESCRIPTOR_REQ_SB_LEN   \
        sizeof(tISI_AudPolApplDescriptorReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_ADD_STREAM_REQ_SB - Valid from version 000.001   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint8   nbr_of_streams; /* Number of stream's to be created */
    uint8   filler1;
    } tISI_AudPolApplAddStreamReqSB;

#define AUD_POL_APPL_ADD_STREAM_REQ_SB_LEN   \
        sizeof(tISI_AudPolApplAddStreamReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_REMOVE_STREAM_REQ_SB - Valid from version 000.001 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  stream_id;    /* stream id, which is to be removed */
    } tISI_AudPolApplRemoveStreamReqSB;

#define AUD_POL_APPL_REMOVE_STREAM_REQ_SB_LEN   \
        sizeof(tISI_AudPolApplRemoveStreamReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_REMOVE_APPL_REQ_SB - Valid from version 000.001  */
/* ----------------------------------------------------------------------- */
/* This will deallocate all the streams, there is no need to send the
   _REMOVE_STREAM_SB as well.
*/

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  application_id; /* application id, which is to be removed */
    } tISI_AudPolApplRemoveApplReqSB;

#define AUD_POL_APPL_REMOVE_APPL_REQ_SB_LEN   \
        sizeof(tISI_AudPolApplRemoveApplReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOL_CONTROL_REQ_SB - Versions 000.001 - 001.000       */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  appl_type; /* Values from the constant table AUD_POL_APPL_TYPE */
    uint16  volume;       /* 100% = 1000 */
    /* Values from the bitmask table AUD_POL_VOL_CONTROL_MUTING */
    uint8   mute;
    uint8   filler1;
    } tISI_AudPolVolControlReqSB;

#define AUD_POL_VOL_CONTROL_REQ_SB_LEN   sizeof(tISI_AudPolVolControlReqSB)

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOL_CONTROL_REQ_SB - Versions 001.000 - 004.000       */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(1,0) && !AUD_POL_ISI_MIN_VERSION(4,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  appl_type; /* Values from the constant table AUD_POL_APPL_TYPE */
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    uint16  volume;       /* 100% = 1000 */
    /* Values from the bitmask table AUD_POL_VOL_CONTROL_MUTING */
    uint8   mute;
    uint8   filler1;
    uint16  filler2;
    } tISI_AudPolVolControlReqSB;

#define AUD_POL_VOL_CONTROL_REQ_SB_LEN   sizeof(tISI_AudPolVolControlReqSB)

#endif /* AUD_POL_ISI_MIN_VERSION(1,0) && !AUD_POL_ISI_MIN_VERSION(4,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOL_CONTROL_REQ_SB - Valid from version 004.000       */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(4,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  filler1;
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    uint16  volume;       /* 100% = 1000 */
    } tISI_AudPolVolControlReqSB;

#define AUD_POL_VOL_CONTROL_REQ_SB_LEN   sizeof(tISI_AudPolVolControlReqSB)

#endif /* AUD_POL_ISI_MIN_VERSION(4,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_MUTE_CONTROL_REQ_SB - Versions 004.000 - 005.000      */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(4,0) && !AUD_POL_ISI_MIN_VERSION(5,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint8   mic_mute; /* Values from the constant table AUD_POL_MIC_MUTING */
    /* Values from the constant table AUD_POL_SPEAKER_MUTING */
    uint8   speaker_mute;
    } tISI_AudPolMuteControlReqSB;

#define AUD_POL_MUTE_CONTROL_REQ_SB_LEN   sizeof(tISI_AudPolMuteControlReqSB)

#endif /* AUD_POL_ISI_MIN_VERSION(4,0) && !AUD_POL_ISI_MIN_VERSION(5,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_MUTE_CONTROL_REQ_SB - Valid from version 005.000      */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(5,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  filler1;
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    uint8   mic_mute; /* Values from the constant table AUD_POL_MIC_MUTING */
    /* Values from the constant table AUD_POL_SPEAKER_MUTING */
    uint8   speaker_mute;
    } tISI_AudPolMuteControlReqSB;

#define AUD_POL_MUTE_CONTROL_REQ_SB_LEN   sizeof(tISI_AudPolMuteControlReqSB)

#endif /* AUD_POL_ISI_MIN_VERSION(5,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOLUME_CHANGE_REQ_SB - Valid from version 007.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* Values from the constant table AUD_POL_VOLUME_DIRECTION */
    uint8   volume_direction;
    uint8   filler1;
    } tISI_AudPolVolChangeReqSB;

#define AUD_POL_VOLUME_CHANGE_REQ_SB_LEN   sizeof(tISI_AudPolVolChangeReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_PRIVOL_CHANGE_NTF_SB - Valid from version 007.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* Values from the constant table AUD_POL_VOLUME_DIRECTION */
    uint8   volume_direction;
    uint8   filler1;
    } tISI_AudPolPriVolChangeNtfSB;

#define AUD_POL_PRIVOL_CHANGE_NTF_SB_LEN   \
        sizeof(tISI_AudPolPriVolChangeNtfSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_STREAM_VOLUME_REQ_SB - Valid from version 007.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  filler1;
    uint16  stream_id;
    /* Stream volume is percentage of application volume or preference
       volume. Preference volume is used only if application volume is not
       set. 100% = 1000.
    */
    uint16  volume;
    } tISI_AudPolStreamVolReqSB;

#define AUD_POL_STREAM_VOLUME_REQ_SB_LEN   sizeof(tISI_AudPolStreamVolReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_STREAM_MUTE_REQ_SB - Valid from version 007.001       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  filler1;
    uint16  stream_id;
    uint8   mute_status;  /* TRUE=Muted, FALSE=Not muted */
    uint8   filler2;
    } tISI_AudPolStreamMuteReqSB;

#define AUD_POL_STREAM_MUTE_REQ_SB_LEN   sizeof(tISI_AudPolStreamMuteReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB - Valid from version 007.000 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  volume;
    } tISI_AudPolNbrVolLevelReqSB;

#define AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB_LEN   \
        sizeof(tISI_AudPolNbrVolLevelReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_CONTROL_PRIORITY_NTF_SB - Valid from version 000.001  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  application_id; /* application id */
    uint16  appl_type; /* Values from the constant table AUD_POL_APPL_TYPE */
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    } tISI_AudPolControlPriorityNtfSB;

#define AUD_POL_CONTROL_PRIORITY_NTF_SB_LEN   \
        sizeof(tISI_AudPolControlPriorityNtfSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_DESCRIPTOR_RESP_SB - Versions 000.001 - 002.000  */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* not yet valid, will be used something like 0 = OK, otherwise error
       code
    */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolApplDescriptorRespSB;

#define AUD_POL_APPL_DESCRIPTOR_RESP_SB_LEN   \
        sizeof(tISI_AudPolApplDescriptorRespSB)

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_DESCRIPTOR_RESP_SB - Valid from version 002.000  */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolApplDescriptorRespSB;

#define AUD_POL_APPL_DESCRIPTOR_RESP_SB_LEN   \
        sizeof(tISI_AudPolApplDescriptorRespSB)

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_ADD_STREAM_RESP_SB - Versions 000.001 - 002.000  */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* not yet valid, will be used something like 0 = OK, otherwise error
       code
    */
    uint8   reason;
    uint8   nbr_of_streams; /* Number of streams created */
    uint16  stream_id[AUD_POL_ANY_SIZE];
    } tISI_AudPolApplAddStreamRespSB;

#define AUD_POL_APPL_ADD_STREAM_RESP_SB_LEN   (4*sizeof(uint8))

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_ADD_STREAM_RESP_SB - Valid from version 002.000  */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   nbr_of_streams; /* Number of streams created */
    uint16  stream_id[AUD_POL_ANY_SIZE];
    } tISI_AudPolApplAddStreamRespSB;

#define AUD_POL_APPL_ADD_STREAM_RESP_SB_LEN   (4*sizeof(uint8))

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_REMOVE_STREAM_RESP_SB - Versions 000.001 - 002.000 */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* not yet valid, will be used something like 0 = OK, otherwise error
       code
    */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolApplRemoveStreamRespSB;

#define AUD_POL_APPL_REMOVE_STREAM_RESP_SB_LEN   \
        sizeof(tISI_AudPolApplRemoveStreamRespSB)

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_REMOVE_STREAM_RESP_SB - Valid from version 002.000 */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolApplRemoveStreamRespSB;

#define AUD_POL_APPL_REMOVE_STREAM_RESP_SB_LEN   \
        sizeof(tISI_AudPolApplRemoveStreamRespSB)

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_REMOVE_APPL_RESP_SB - Versions 000.001 - 002.000 */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  application_id; /* application id, which is removed */
    /* not yet valid, will be used something like 0 = OK, otherwise error
       code
    */
    uint8   reason;
    uint8   filler1;
    uint16  filler2;
    } tISI_AudPolApplRemoveApplRespSB;

#define AUD_POL_APPL_REMOVE_APPL_RESP_SB_LEN   \
        sizeof(tISI_AudPolApplRemoveApplRespSB)

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_APPL_REMOVE_APPL_RESP_SB - Valid from version 002.000 */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  application_id; /* application id, which is removed */
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    uint16  filler2;
    } tISI_AudPolApplRemoveApplRespSB;

#define AUD_POL_APPL_REMOVE_APPL_RESP_SB_LEN   \
        sizeof(tISI_AudPolApplRemoveApplRespSB)

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOL_CONTROL_RESP_SB - Versions 000.001 - 002.000      */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* not yet valid, will be used something like 0 = OK, otherwise error
       code
    */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolVolControlRespSB;

#define AUD_POL_VOL_CONTROL_RESP_SB_LEN   sizeof(tISI_AudPolVolControlRespSB)

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOL_CONTROL_RESP_SB - Valid from version 002.000      */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolVolControlRespSB;

#define AUD_POL_VOL_CONTROL_RESP_SB_LEN   sizeof(tISI_AudPolVolControlRespSB)

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_MUTE_CONTROL_RESP_SB - Valid from version 004.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolMuteControlRespSB;

#define AUD_POL_MUTE_CONTROL_RESP_SB_LEN   \
        sizeof(tISI_AudPolMuteControlRespSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOLUME_CHANGE_RESP_SB - Valid from version 007.000    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolVolChangeRespSB;

#define AUD_POL_VOLUME_CHANGE_RESP_SB_LEN   \
        sizeof(tISI_AudPolVolChangeRespSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_STREAM_VOLUME_RESP_SB - Valid from version 007.000    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolStreamVolRespSB;

#define AUD_POL_STREAM_VOLUME_RESP_SB_LEN   \
        sizeof(tISI_AudPolStreamVolRespSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_STREAM_MUTE_RESP_SB - Valid from version 007.001      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolStreamMuteRespSB;

#define AUD_POL_STREAM_MUTE_RESP_SB_LEN   sizeof(tISI_AudPolStreamMuteRespSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB - Valid from version 007.000 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolNbrVolLevelRespSB;

#define AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB_LEN   \
        sizeof(tISI_AudPolNbrVolLevelRespSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_RESOURCE_REQ_SB - Valid from version 001.000          */
/* ----------------------------------------------------------------------- */
/* Using either the mcycles or percentage field is enough. Preferred way is
   to use mcycles.
*/

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* Encoder or decoder type
       Values from the constant table AUD_POL_ENC_DEC_TYPE
    */
    uint16  enc_dec_type;
    uint16  mcycles;      /* Mega cycles */
    /* percentage (range 0 - 1000, meaning 45.5% is 455) */
    uint16  percentage;
    } tISI_AudPolResourceReqSB;

#define AUD_POL_RESOURCE_REQ_SB_LEN   sizeof(tISI_AudPolResourceReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_RESOURCE_RESP_SB - Valid from version 001.000         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* Values from the constant table AUD_POL_RESOURCE_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolResourceRespSB;

#define AUD_POL_RESOURCE_RESP_SB_LEN   sizeof(tISI_AudPolResourceRespSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOLUME_IND_SB - Versions 001.000 - 004.000            */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(1,0) && !AUD_POL_ISI_MIN_VERSION(4,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  application_id; /* application id */
    uint16  appl_type; /* Values from the constant table AUD_POL_APPL_TYPE */
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    uint16  volume;       /* 100% = 1000 */
    /* Values from the bitmask table AUD_POL_VOL_CONTROL_MUTING */
    uint8   mute;
    uint8   filler1;
    } tISI_AudPolVolumeIndSB;

#define AUD_POL_VOLUME_IND_SB_LEN   sizeof(tISI_AudPolVolumeIndSB)

#endif /* AUD_POL_ISI_MIN_VERSION(1,0) && !AUD_POL_ISI_MIN_VERSION(4,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOLUME_IND_SB - Valid from version 004.000            */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(4,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  application_id; /* application id */
    uint16  filler1;
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    uint16  volume;       /* 100% = 1000 */
    /* A subset of values from the constant table AUD_POL_DEVICE_TYPE */
    uint8   device_type;
    uint8   filler2;
    } tISI_AudPolVolumeIndSB;

#define AUD_POL_VOLUME_IND_SB_LEN   sizeof(tISI_AudPolVolumeIndSB)

#endif /* AUD_POL_ISI_MIN_VERSION(4,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_VOLUME_CHANGE_IND_SB - Valid from version 007.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* Values from the constant table AUD_POL_VOLUME_DIRECTION */
    uint8   volume_direction;
    /* A subset of values from the constant table AUD_POL_DEVICE_TYPE */
    uint8   device_type;
    } tISI_AudPolVolumeChangeIndSB;

#define AUD_POL_VOLUME_CHANGE_IND_SB_LEN   \
        sizeof(tISI_AudPolVolumeChangeIndSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_MUTE_IND_SB - Valid from version 007.000              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    uint8   mic_mute; /* Values from the constant table AUD_POL_MIC_MUTING */
    /* Values from the constant table AUD_POL_SPEAKER_MUTING */
    uint8   speaker_mute;
    uint16  filler2;
    } tISI_AudPolMuteIndSB;

#define AUD_POL_MUTE_IND_SB_LEN   sizeof(tISI_AudPolMuteIndSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_STATUS_IND_SB - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint16  application_id; /* application id */
    uint16  appl_type; /* Values from the constant table AUD_POL_APPL_TYPE */
    uint16  appl_pref; /* Values from the constant table AUD_POL_APPL_PREF */
    /* Whenever some application registers IN and gets permission to start
       the status is ACTIVE. When the application registers OUT the status is
       INACTIVE, or if the application is stopped or paused, it is also
       INACTIVE. Also when application is resumed it is again ACTIVE
       Values from the constant table AUD_POL_STATUS
    */
    uint8   status;
    uint8   filler1;
    uint16  filler2;
    } tISI_AudPolStatusIndSB;

#define AUD_POL_STATUS_IND_SB_LEN   sizeof(tISI_AudPolStatusIndSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_MODE_IND_SB - Versions 002.000 - 007.000              */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0) && !AUD_POL_ISI_MIN_VERSION(7,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* New audio mode
       Values from the constant table AUD_POL_AUDIO_MODE
    */
    uint8   audio_mode;
    /* Reason for audio mode change
       A subset of values from the constant table AUD_POL_REASON
    */
    uint8   reason;
    } tISI_AudPolModeIndSB;

#define AUD_POL_MODE_IND_SB_LEN   sizeof(tISI_AudPolModeIndSB)

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) && !AUD_POL_ISI_MIN_VERSION(7,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_MODE_IND_SB - Valid from version 007.000              */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(7,0)

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* New audio mode
       Values from the constant table AUD_POL_AUDIO_MODE
    */
    uint8   audio_mode;
    /* Reason for audio mode change
       A subset of values from the constant table AUD_POL_REASON
    */
    uint8   reason;
    /* Values from the bitmask table AUD_POL_CAPABILITY_RESTRICTIONS */
    uint32  capabilities;
    } tISI_AudPolModeIndSB;

#define AUD_POL_MODE_IND_SB_LEN   sizeof(tISI_AudPolModeIndSB)

#endif /* AUD_POL_ISI_MIN_VERSION(7,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_MODE_RESP_SB - Valid from version 007.000             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* Current audio mode
       Values from the constant table AUD_POL_AUDIO_MODE
    */
    uint8   audio_mode;
    uint8   filler1;
    /* Values from the bitmask table AUD_POL_CAPABILITY_RESTRICTIONS */
    uint32  capabilities;
    } tISI_AudPolModeRespSB;

#define AUD_POL_MODE_RESP_SB_LEN   sizeof(tISI_AudPolModeRespSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_STATUS_INFO_REQ_SB - Valid from version 007.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* Values from the bitmask table AUD_POL_STATUS_TYPE */
    uint8   status_type;
    uint8   filler1;
    } tISI_AudPolStatusInfoReqSB;

#define AUD_POL_STATUS_INFO_REQ_SB_LEN   sizeof(tISI_AudPolStatusInfoReqSB)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_MODE_PROPERTIES_SB - Valid from version 007.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    uint8   filler1;
    uint8   nbr_of_properties;
    AUD_POL_PROPERTY_SEQ_STR array[1];
    } tISI_AudPolModePropertiesSB;

#define AUD_POL_MODE_PROPERTIES_SB_LEN   (4*sizeof(uint8) + \
        sizeof(AUD_POL_PROPERTY_SEQ_STR))


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_POL_AUDIO_EFFECT_PHAP_SB - Valid from version 007.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   subblock_id;
    uint8   subblock_length;
    /* If PHAP is activated the status needs to be ACTIVE. When PHAP is
       deactivated the status is INACTIVE.
       Values from the constant table AUD_POL_STATUS
    */
    uint8   status;
    uint8   filler1;
    } tISI_AudPolAudioEffectSB;

#define AUD_POL_AUDIO_EFFECT_PHAP_SB_LEN   sizeof(tISI_AudPolAudioEffectSB)


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_APPL_REQ - Valid from version 000.001                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* New application id is created with value AUD_POL_APPL_ID_NOT_DEFINED,
       otherwise existing id is used
    */
    uint16  application_id;
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_APPL_ADD_STREAM_REQ_SB
       AUD_POL_APPL_DESCRIPTOR_REQ_SB
       AUD_POL_APPL_REMOVE_APPL_REQ_SB
       AUD_POL_APPL_REMOVE_STREAM_REQ_SB
       AUD_POL_MUTE_CONTROL_REQ_SB
       AUD_POL_STATUS_INFO_REQ_SB
       AUD_POL_VOL_CONTROL_REQ_SB
    */
    } tISI_AudPolApplReq;

#define AUD_POL_APPL_REQ_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_APPL_RESP - Versions 000.001 - 002.000                 */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  application_id; /* application id */
    uint16  filler1;
    /* not yet valid, will be used something like 0 = OK, otherwise error
       code
    */
    uint8   reason;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_APPL_ADD_STREAM_RESP_SB
       AUD_POL_APPL_DESCRIPTOR_RESP_SB
       AUD_POL_APPL_REMOVE_APPL_RESP_SB
       AUD_POL_APPL_REMOVE_STREAM_RESP_SB
    */
    } tISI_AudPolApplResp;

#define AUD_POL_APPL_RESP_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_APPL_RESP - Valid from version 002.000                 */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  application_id; /* application id */
    uint16  filler1;
    /* Ok/Fail. More detailed error codes in sub blocks.
       A subset of values from the constant table AUD_POL_REASON
    */
    uint8   reason;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_APPL_ADD_STREAM_RESP_SB
       AUD_POL_APPL_DESCRIPTOR_RESP_SB
       AUD_POL_APPL_REMOVE_APPL_RESP_SB
       AUD_POL_APPL_REMOVE_STREAM_RESP_SB
       AUD_POL_MODE_PROPERTIES_SB
       AUD_POL_MODE_RESP_SB
       AUD_POL_MUTE_CONTROL_RESP_SB
       AUD_POL_VOL_CONTROL_RESP_SB
    */
    } tISI_AudPolApplResp;

#define AUD_POL_APPL_RESP_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_VOLUME_REQ - Valid from version 000.001                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  application_id; /* application id */
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_MUTE_CONTROL_REQ_SB
       AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB
       AUD_POL_STREAM_MUTE_REQ_SB
       AUD_POL_STREAM_VOLUME_REQ_SB
       AUD_POL_VOLUME_CHANGE_REQ_SB
       AUD_POL_VOL_CONTROL_REQ_SB
    */
    } tISI_AudPolVolReq;

#define AUD_POL_VOLUME_REQ_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_VOLUME_RESP - Versions 000.001 - 002.000               */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  application_id; /* application id */
    uint16  filler1;
    /* not yet valid, will be used something like 0 = OK, otherwise error
       code. 
    */
    uint8   reason;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_VOL_CONTROL_RESP_SB
    */
    } tISI_AudPolVolResp;

#define AUD_POL_VOLUME_RESP_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_VOLUME_RESP - Valid from version 002.000               */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  application_id; /* Application id */
    uint16  filler1;
    /* Ok/Fail. More detailed error code in sub block.
       A subset of values from the constant table AUD_POL_REASON
    */
    uint8   reason;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_MUTE_CONTROL_RESP_SB
       AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB
       AUD_POL_STREAM_MUTE_RESP_SB
       AUD_POL_STREAM_VOLUME_RESP_SB
       AUD_POL_VOLUME_CHANGE_RESP_SB
       AUD_POL_VOL_CONTROL_RESP_SB
    */
    } tISI_AudPolVolResp;

#define AUD_POL_VOLUME_RESP_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_CONTROL_NTF - Versions 000.001 - 001.000               */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  application_id; /* application id */
    uint8   directive; /* Values from the constant table AUD_POL_DIRECTIVE */
    /* Values from the constant table AUD_POL_DIRECTIVE_REASON */
    uint8   reason;
    uint8   filler1;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_CONTROL_PRIORITY_NTF_SB
    */
    } tISI_AudPolControlNtf;

#define AUD_POL_CONTROL_NTF_LEN   (6*sizeof(uint8) + sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(0,1) && !AUD_POL_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_CONTROL_NTF - Versions 001.000 - 006.000               */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(1,0) && !AUD_POL_ISI_MIN_VERSION(6,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   directive; /* Values from the constant table AUD_POL_DIRECTIVE */
    /* Values from the constant table AUD_POL_DIRECTIVE_REASON */
    uint8   reason;
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_CONTROL_PRIORITY_NTF_SB
    */
    } tISI_AudPolControlNtf;

#define AUD_POL_CONTROL_NTF_LEN   (6*sizeof(uint8) + sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(1,0) && !AUD_POL_ISI_MIN_VERSION(6,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_CONTROL_NTF - Valid from version 006.000               */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(6,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  application_id; /* application id */
    uint8   directive; /* Values from the constant table AUD_POL_DIRECTIVE */
    /* Values from the constant table AUD_POL_DIRECTIVE_REASON */
    uint8   reason;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_CONTROL_PRIORITY_NTF_SB
    */
    } tISI_AudPolControlNtf;

#define AUD_POL_CONTROL_NTF_LEN   (6*sizeof(uint8) + sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(6,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_APPL_NTF - Valid from version 000.001                  */
/* ----------------------------------------------------------------------- */
/* By using this message, applications can tell to Audio Policy when certain
   command has been completed.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  application_id; /* application id */
    uint8   directive; /* Values from the constant table AUD_POL_DIRECTIVE */
    /* Values from the constant table AUD_POL_DIRECTIVE_STATUS */
    uint8   status;
    uint8   filler1;
    uint8   nbr_of_subblocks;
    /* Subblock list: */
    } tISI_AudPolApplNtf;

#define AUD_POL_APPL_NTF_LEN   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_RESOURCE_REQ - Valid from version 001.000              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  stream_id;    /* stream id */
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_RESOURCE_REQ_SB
    */
    } tISI_AudPolResourceReq;

#define AUD_POL_RESOURCE_REQ_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_RESOURCE_RESP - Valid from version 001.000             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  stream_id;    /* stream id */
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_RESOURCE_RESP_SB
    */
    } tISI_AudPolResourceResp;

#define AUD_POL_RESOURCE_RESP_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_STATUS_IND - Valid from version 001.000                */
/* ----------------------------------------------------------------------- */
/* This message is sent to all registered applications when something happens
   in Audio Policy.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   filler1;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_MODE_IND_SB
       AUD_POL_MODE_PROPERTIES_SB
       AUD_POL_STATUS_IND_SB
    */
    } tISI_AudPolStatusInd;

#define AUD_POL_STATUS_IND_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_VOLUME_IND - Valid from version 001.000                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   filler1;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_MUTE_IND_SB
       AUD_POL_VOLUME_CHANGE_IND_SB
       AUD_POL_VOLUME_IND_SB
    */
    } tISI_AudPolVolumeInd;

#define AUD_POL_VOLUME_IND_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_PRIVOL_REQ - Versions 002.000 - 007.000                */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0) && !AUD_POL_ISI_MIN_VERSION(7,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the constant table AUD_POL_PRIVOL_COMMAND */
    uint8   command;
    /* A subset of values from the constant table AUD_POL_DEVICE_TYPE */
    uint8   device_type;
    uint16  volume;       /* 100% = 1000 */
    uint16  filler1;
    } tISI_AudPolPrivolReq;

#define AUD_POL_PRIVOL_REQ_LEN   sizeof(tISI_AudPolPrivolReq)

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) && !AUD_POL_ISI_MIN_VERSION(7,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_PRIVOL_REQ - Valid from version 007.000                */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(7,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the constant table AUD_POL_PRIVOL_COMMAND */
    uint8   command;
    /* A subset of values from the constant table AUD_POL_DEVICE_TYPE */
    uint8   device_type;
    uint16  volume;       /* 100% = 1000 */
    uint8   filler1;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_VOLUME_CHANGE_REQ_SB
    */
    } tISI_AudPolPrivolReq;

#define AUD_POL_PRIVOL_REQ_LEN   (6*sizeof(uint8) + sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(7,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_PRIVOL_RESP - Valid from version 002.000               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolPrivolResp;

#define AUD_POL_PRIVOL_RESP_LEN   sizeof(tISI_AudPolPrivolResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_PRIVOL_NTF - Versions 002.000 - 007.000                */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(2,0) && !AUD_POL_ISI_MIN_VERSION(7,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* A subset of values from the constant table AUD_POL_DEVICE_TYPE */
    uint8   device_type;
    uint8   filler1;
    uint16  volume;       /* 100% = 1000 */
    uint16  filler2;
    } tISI_AudPolPrivolNtf;

#define AUD_POL_PRIVOL_NTF_LEN   sizeof(tISI_AudPolPrivolNtf)

#endif /* AUD_POL_ISI_MIN_VERSION(2,0) && !AUD_POL_ISI_MIN_VERSION(7,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_PRIVOL_NTF - Valid from version 007.000                */
/* ----------------------------------------------------------------------- */

#if AUD_POL_ISI_MIN_VERSION(7,0)

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* A subset of values from the constant table AUD_POL_DEVICE_TYPE */
    uint8   device_type;
    uint8   filler1;
    uint16  volume;       /* 100% = 1000 */
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_PRIVOL_CHANGE_NTF_SB
    */
    } tISI_AudPolPrivolNtf;

#define AUD_POL_PRIVOL_NTF_LEN   (6*sizeof(uint8) + sizeof(uint16))

#endif /* AUD_POL_ISI_MIN_VERSION(7,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_STATUS_REQ - Valid from version 007.000                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the bitmask table AUD_POL_STATUS_TYPE */
    uint8   status_type;
    uint8   filler1;
    } tISI_AudPolStatusReq;

#define AUD_POL_STATUS_REQ_LEN   sizeof(tISI_AudPolStatusReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_STATUS_RESP - Valid from version 007.000               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_MODE_PROPERTIES_SB
       AUD_POL_MODE_RESP_SB
       AUD_POL_STATUS_IND_SB
    */
    } tISI_AudPolStatusResp;

#define AUD_POL_STATUS_RESP_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_AUDIO_EFFECT_REQ - Valid from version 007.000          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   filler1;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_AUDIO_EFFECT_PHAP_SB
    */
    } tISI_AudPolAudioEffectReq;

#define AUD_POL_AUDIO_EFFECT_REQ_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_AUDIO_EFFECT_RESP - Valid from version 007.000         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* A subset of values from the constant table AUD_POL_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_AudPolAudioEffectResp;

#define AUD_POL_AUDIO_EFFECT_RESP_LEN   sizeof(tISI_AudPolAudioEffectResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_POL_AUDIO_EFFECT_IND - Valid from version 007.000          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   filler1;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_POL_AUDIO_EFFECT_PHAP_SB
    */
    } tISI_AudPolAudioEffectInd;

#define AUD_POL_AUDIO_EFFECT_IND_LEN   (4*sizeof(uint8))




#endif /* _AUDIO_POL_ISI_H */
