/*
NOKIA                                                             CONFIDENTIAL
OULU
MCU Audio
Mika P. Kangas



                  audio_eap_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1glint

project path:    global_interface/ISI/Core

name:            audio_eap_isi.h

version:         001.002

type:            incl

instance:        ou_pcms#1


ISI header file for EAP Module

Current   ISI Version : 001.002
Supported ISI Versions: 001.000, 001.001, 001.002

Generated with autogen version 11w05 on 16-Mar-2011 13:43:15
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 001.002    NON-DRAFT   04-Mar-2011    Janne Vimpari
Reason      : Change Request: Audio EAP ISI: Nokia Virtual Surround effect
Reference   : SWAM CR: JV11030441438
Description : Added Subblock AUD_EAP_EFFECT_VSURROUND_REQ_SB to AUD_EAP_EFFECT_ADJUST_REQ
              Added Subblock AUD_EAP_EFFECT_VSURROUND_RESP_SB to AUD_EAP_EFFECT_ADJUST_RESP
              Added Subblock AUD_EAP_EFFECT_VSURROUND_REQ_SB to AUD_EAP_EFFECT_CREATE_REQ
              Added Subblock AUD_EAP_EFFECT_VSURROUND_RESP_SB to AUD_EAP_EFFECT_CREATE_RESP
              Added Subblock AUD_EAP_DESTROY_VSURROUND_REQ_SB to AUD_EAP_EFFECT_DESTROY_REQ
              Added Subblock AUD_EAP_EFFECT_VSURROUND_RESP_SB to AUD_EAP_EFFECT_DESTROY_RESP
              Added Subblock AUD_EAP_DESTROY_VSURROUND_REQ_SB
              Added Subblock AUD_EAP_EFFECT_VSURROUND_REQ_SB
              Added Subblock AUD_EAP_EFFECT_VSURROUND_RESP_SB
              Possibility to control Nokia Virtual Surround through EAP ISI
              interface

Version     : 001.001    NON-DRAFT   1-Nov-2010     Ari Hyväri
Reason      : Change Request: Audio EAP ISI interface changes for pocket band
Reference   : SWAM CR: JV10102934365
Description : Option to select capture source in STREAM_CAPTURE_REQ_SB

Version     : 001.000    NON-DRAFT   24-Jan-2008    Janne Vimpari
Reason      : Change request
Reference   : SWAM CR: JV08011556803
Description : EAP ISI messages and definitions separated from common audio.
              This file Created. 

------------------------------------------------------------------------------
*/

#ifndef _AUDIO_EAP_ISI_H
#define _AUDIO_EAP_ISI_H

#include "isi_conf.h"

#ifndef AUD_EAP_ISI_VERSION
#define AUD_EAP_ISI_VERSION
#define AUD_EAP_ISI_VERSION_Z   1
#define AUD_EAP_ISI_VERSION_Y   2
#endif

#define AUD_EAP_ISI_MIN_VERSION(z,y) \
 ((AUD_EAP_ISI_VERSION_Z == (z) && AUD_EAP_ISI_VERSION_Y >= (y)) || \
  (AUD_EAP_ISI_VERSION_Z > (z)))

#if !AUD_EAP_ISI_MIN_VERSION(1,0)
#error The specified interface version is not supported by this header file
#elif AUD_EAP_ISI_MIN_VERSION(1,3)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

#define AUD_EAP_EAP_MUMDRC_NUM_CURVE_POINTS      0x05
#define AUD_EAP_EAP_MUMDRC_NUM_BANDS_MAX         0x03
#define AUD_EAP_EAP_MUMDRC_NUM_VOLUMES_MAX       0x05
/* constant for variable-length definitions */
#define AUD_EAP_ANY_SIZE                         1
#define AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN  0x0200
#define AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN  0x0100

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_STREAM_SAMPLERATE                               */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EAP_STREAM_SAMPLERATE_CONST;

/* Samplerate 5.5125KHz */
#define AUD_EAP_STREAM_SAMPLERATE_5_5125KHZ      0x00
/* Samplerate 8KHz */
#define AUD_EAP_STREAM_SAMPLERATE_8KHZ           0x01
/* Samplerate 11.025KHz */
#define AUD_EAP_STREAM_SAMPLERATE_11_025KHZ      0x02
/* Samplerate 12KHz */
#define AUD_EAP_STREAM_SAMPLERATE_12KHZ          0x03
/* Samplerate 16KHz */
#define AUD_EAP_STREAM_SAMPLERATE_16KHZ          0x04
/* Samplerate 22.05KHz */
#define AUD_EAP_STREAM_SAMPLERATE_22_05KHZ       0x05
/* Samplerate 24KHz */
#define AUD_EAP_STREAM_SAMPLERATE_24KHZ          0x06
/* Samplerate 32KHz */
#define AUD_EAP_STREAM_SAMPLERATE_32KHZ          0x07
/* Samplerate 44.1KHz */
#define AUD_EAP_STREAM_SAMPLERATE_44_1KHZ        0x08
/* Samplerate 48KHz */
#define AUD_EAP_STREAM_SAMPLERATE_48KHZ          0x09
/* Samplerate 64KHz */
#define AUD_EAP_STREAM_SAMPLERATE_64KHZ          0x0A
/* Samplerate 88.2KHz */
#define AUD_EAP_STREAM_SAMPLERATE_88_2KHZ        0x0B
/* Samplerate 96KHz */
#define AUD_EAP_STREAM_SAMPLERATE_96KHZ          0x0C

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_BUFFER_OVERFLOW_REASON                          */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EAP_BUFFER_OVERFLOW_REASON_CONST;

/* Buffer overflow */
#define AUD_EAP_BUFFER_OVERFLOW                  0x01
/* Buffer out of memory */
#define AUD_EAP_BUFFER_OUT_OF_MEMORY             0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_STREAM_CHANNELS                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EAP_STREAM_CHANNELS_CONST;

#define AUD_EAP_STREAM_CHANNEL_MONO              0x01  /* Mono */
#define AUD_EAP_STREAM_CHANNEL_STEREO            0x02  /* Stereo */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_EAP_STREAM_BUFFER_FORMAT                             */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_EAP_STREAM_BUFFER_FORMAT_CONST;

/* INT16 */
#define AUD_EAP_STREAM_SAMPLE_INT16              0x0001  /* ---------------1 */
/* INT32 */
#define AUD_EAP_STREAM_SAMPLE_INT32              0x0002  /* --------------1- */
/* INT8 */
#define AUD_EAP_STREAM_SAMPLE_INT8               0x0003  /* --------------11 */
/* INTERLEAVED */
#define AUD_EAP_STREAM_SAMPLE_INTERLEAVED        0x0010  /* -----------1---- */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_STREAM_TYPE                                     */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_EAP_STREAM_TYPE_CONST;

/* Audio playback */
#define AUD_EAP_STREAM_TYPE_AUDIO_PLAYBACK       0x0011
/* Audio capture */
#define AUD_EAP_STREAM_TYPE_AUDIO_CAPTURE        0x0012
/* Speech playback */
#define AUD_EAP_STREAM_TYPE_SPEECH_PLAYBACK      0x0021
/* Speech capture */
#define AUD_EAP_STREAM_TYPE_SPEECH_CAPTURE       0x0022

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_EAP_STREAM_FLAGS                                     */
/* ----------------------------------------------------------------------- */
typedef uint32 AUD_EAP_STREAM_FLAGS_CONST;

/* no flags */
#define AUD_EAP_STREAM_FLAGS_NO                  0x00000000  /* -------------------------------- */
/* static stream */
#define AUD_EAP_STREAM_FLAGS_STATIC              0x00000001  /* -------------------------------1 */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_STREAM_REASON                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EAP_STREAM_REASON_CONST;

#define AUD_EAP_COMMAND_OK                       0x00  /* OK */
#define AUD_EAP_COMMAND_FAIL                     0x01  /* FAIL */
/* The feature (ie. effect) is not supported */
#define AUD_EAP_COMMAND_NOT_SUPPORTED            0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_PREDEFINED_STREAM_ID                            */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_EAP_PREDEFINED_STREAM_ID_CONST;

/* Master stream id */
#define AUD_EAP_MASTER_STREAM_ID                 0x00FF
#define AUD_EAP_AUDIO_PLAYBACK_STREAM_ID         0x00FE
#define AUD_EAP_AUDIO_CAPTURE_STREAM_ID          0x00FD
#define AUD_EAP_SPEECH_PLAYBACK_STREAM_ID        0x00FC
#define AUD_EAP_SPEECH_CAPTURE_STREAM_ID         0x00FB

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_EFFECT_AVAILABLE                                */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EAP_EFFECT_AVAILABLE_CONST;

/* Volume level control */
#define AUD_EAP_EFFECT_2D_LEVEL_CONTROL          0x01
#define AUD_EAP_EFFECT_2D_PAN_CONTROL            0x02  /* Pan control */
/* 3D location control */
#define AUD_EAP_EFFECT_3D_LOCATION_CONTROL       0x03
/* 3D obstruction control */
#define AUD_EAP_EFFECT_3D_OBSTRUCTION_CONTROL    0x04
/* 3D occlusion control */
#define AUD_EAP_EFFECT_3D_OCCLUSION_CONTROL      0x05
/* 3D distance attenuation control */
#define AUD_EAP_EFFECT_3D_DISTANCE_CONTROL       0x06
/* 3D reverberation control */
#define AUD_EAP_EFFECT_3D_REVERB_CONTROL         0x07
/* 3D commit control */
#define AUD_EAP_EFFECT_3D_COMMIT_CONTROL         0x08

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_OBSTRUCTION_PRESET                              */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_EAP_OBSTRUCTION_PRESET_CONST;

#define AUD_EAP_OBSTRUCTION_PRESET_NONE          0x0000
#define AUD_EAP_OBSTRUCTION_PRESET_WINDOW_SINGLE 0x0001
#define AUD_EAP_OBSTRUCTION_PRESET_WINDOW_DOUBLE 0x0002
#define AUD_EAP_OBSTRUCTION_PRESET_DOOR_THIN     0x0003
#define AUD_EAP_OBSTRUCTION_PRESET_DOOR_THICK    0x0004
#define AUD_EAP_OBSTRUCTION_PRESET_WALL_WOOD     0x0005
#define AUD_EAP_OBSTRUCTION_PRESET_WALL_BRICK    0x0006
#define AUD_EAP_OBSTRUCTION_PRESET_WALL_STONE    0x0007
#define AUD_EAP_OBSTRUCTION_PRESET_CURTAIN       0x0008

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_OCCLUSION_PRESET                                */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_EAP_OCCLUSION_PRESET_CONST;

#define AUD_EAP_OCCLUSION_PRESET_NONE            0x0000
#define AUD_EAP_OCCLUSION_PRESET_WINDOW_SINGLE   0x0001
#define AUD_EAP_OCCLUSION_PRESET_WINDOW_DOUBLE   0x0002
#define AUD_EAP_OCCLUSION_PRESET_DOOR_THIN       0x0003
#define AUD_EAP_OCCLUSION_PRESET_DOOR_THICK      0x0004
#define AUD_EAP_OCCLUSION_PRESET_WALL_WOOD       0x0005
#define AUD_EAP_OCCLUSION_PRESET_WALL_BRICK      0x0006
#define AUD_EAP_OCCLUSION_PRESET_WALL_STONE      0x0007
#define AUD_EAP_OCCLUSION_PRESET_CURTAIN         0x0008

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_REVERBERATION_PRESET                            */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_EAP_REVERBERATION_PRESET_CONST;

#define AUD_EAP_REVERB_PRESET_NONE               0x0000
#define AUD_EAP_REVERB_PRESET_ALLEY              0x0001
#define AUD_EAP_REVERB_PRESET_ARENA              0x0002
#define AUD_EAP_REVERB_PRESET_AUDITORIUM         0x0003
#define AUD_EAP_REVERB_PRESET_BATHROOM           0x0004
#define AUD_EAP_REVERB_PRESET_CAVE               0x0005
#define AUD_EAP_REVERB_PRESET_HALLWAY            0x0006
#define AUD_EAP_REVERB_PRESET_HANGAR             0x0007
#define AUD_EAP_REVERB_PRESET_LIVINGROOM         0x0008
#define AUD_EAP_REVERB_PRESET_MOUNTAINS          0x0009
#define AUD_EAP_REVERB_PRESET_ROOM               0x000A
#define AUD_EAP_REVERB_PRESET_UNDERWATER         0x000B
#define AUD_EAP_REVERB_PRESET_SMALLROOM          0x000C
#define AUD_EAP_REVERB_PRESET_MEDIUMROOM         0x000D
#define AUD_EAP_REVERB_PRESET_LARGEROOM          0x000E
#define AUD_EAP_REVERB_PRESET_LARGEHALL          0x000F
#define AUD_EAP_REVERB_PRESET_PLATE              0x0010

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_VISUALIZATION_OP_MODE                                */
/* ----------------------------------------------------------------------- */
/* Frequecy data sending enabled */
#define AUD_EAP_FREQ_DATA_ENABLED                0x01  /* -1 */
/* Waveform data sending enabled */
#define AUD_EAP_WAVE_DATA_ENABLED                0x02  /* 1- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_EAP_CHANNEL_IDENTIFICATION                           */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_EAP_CHANNEL_IDENTIFICATION_CONST;

/* Channel left */
#define AUD_EAP_CHANNEL_LEFT                     0x0001  /* ---------------1 */
/* Channel right */
#define AUD_EAP_CHANNEL_RIGHT                    0x0002  /* --------------1- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_EAP_DATA_TRACE_POINTS                                */
/* ----------------------------------------------------------------------- */
typedef uint32 AUD_EAP_DATA_TRACE_POINTS_CONST;

/* no trace points */
#define AUD_EAP_TRACE_POINT_NONE                 0x00000000  /* -------------------------------- */
/* trace stream input */
#define AUD_EAP_TRACE_POINT_STREAM_INPUT         0x00000001  /* -------------------------------1 */
/* trace SRC output */
#define AUD_EAP_TRACE_POINT_SRC_OUTPUT           0x00000002  /* ------------------------------1- */
/* trace data written to MDAIF */
#define AUD_EAP_TRACE_POINT_MDAIF_WRITE          0x00000004  /* -----------------------------1-- */
/* trace all points */
#define AUD_EAP_TRACE_POINT_ALL                  0xFFFFFFFF  /* 11111111111111111111111111111111 */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_EFFECT                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EAP_EFFECT_CONST;

/* Used as response status if the effect (instance) does not exist */
#define AUD_EAP_EFFECT_ERROR                     0x00
#define AUD_EAP_EFFECT_MUMDRC                    0x01  /* Music-MDRC */
/* Stereo widening */
#define AUD_EAP_EFFECT_STW                       0x02
/* Positional 3D audio */
#define AUD_EAP_EFFECT_POS3D                     0x03
#define AUD_EAP_EFFECT_DOPPLER                   0x04  /* Doppler */
/* Environmental reverb */
#define AUD_EAP_EFFECT_REVERB                    0x05
#define AUD_EAP_EFFECT_GEQ                       0x06  /* Graphic EQ */
/* Stereo widening 3D */
#define AUD_EAP_EFFECT_STW_3D                    0x07

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_SWITCH                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EAP_SWITCH_CONST;

#define AUD_EAP_SWITCH_OFF                       0x00  /* Off */
#define AUD_EAP_SWITCH_ON                        0x01  /* On */
/* Default setting */
#define AUD_EAP_SWITCH_DEFAULT                   0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EAP_MUMDRC_SWITCH                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EAP_MUMDRC_SWITCH_CONST;

#define AUD_EAP_MUMDRC_OFF                       0x00  /* Off */
#define AUD_EAP_MUMDRC_ON                        0x01  /* On */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_EAP_STREAM_CAPTURE_SOURCE                            */
/* ----------------------------------------------------------------------- */
/* Sets source of capturing. AUD_EAP_STREAM_CAPTURE_RECORDING is used when a
   client wants capturean existing recording stream,
   AUD_EAP_STREAM_CAPTURE_MICROPHONE is used when a client wants
   capturenormally from the microphone or speech call,
   AUD_EAP_STREAM_CAPTURE_PLAYBACK is used when a client wants to
   capturecurrently playing playback stream(s).
   AUD_EAP_STREAM_CAPTURE_DEFAULT is here only to make this changebackward
   compatible. Effectively it is the same as
   AUD_EAP_STREAM_CAPTURE_MICROPHONE functionality whena client has left the
   whole bitfield unfilled. Use case examples: when a client wants to capture
   for examplestreamed audio it sends AUD_EAP_STREAM_CAPTURE_PLAYBACK. When a
   client wants to capture a video phone callaudio it sends
   AUD_EAP_STREAM_CAPTURE_RECORDING|AUD_EAP_STREAM_CAPTURE_PLAYBACK. EAP
   mixesboth currently running streams and sends data to the client in
   started capture stream.
*/
typedef uint16 AUD_EAP_STREAM_CAPTURE_SOURCE_CONST;

/* capture from default (ie. mic ) */
#define AUD_EAP_STREAM_CAPTURE_DEFAULT           0x0000  /* ---------------- */
/* capture from existing recording stream */
#define AUD_EAP_STREAM_CAPTURE_RECORDING         0x0001  /* ---------------1 */
/* capture from mdaif */
#define AUD_EAP_STREAM_CAPTURE_MICROPHONE        0x0002  /* --------------1- */
/* capture from existing playback stream */
#define AUD_EAP_STREAM_CAPTURE_PLAYBACK          0x0004  /* -------------1-- */

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define AUD_EAP_STREAM_REQ                       0x80
#define AUD_EAP_STREAM_RESP                      0x81
#define AUD_EAP_BUFFER_CLIENT_NTF                0x82
#define AUD_EAP_BUFFER_SERVER_NTF                0x83
#define AUD_EAP_BUFFER_OVERFLOW_NTF              0x84
#define AUD_EAP_EFFECT_CREATE_REQ                0x85
#define AUD_EAP_EFFECT_CREATE_RESP               0x86
#define AUD_EAP_EFFECT_DESTROY_REQ               0x87
#define AUD_EAP_EFFECT_DESTROY_RESP              0x88
#define AUD_EAP_BUFFER_EMPTY_NTF                 0x89
#define AUD_EAP_EFFECT_INFO_REQ                  0x8A
#define AUD_EAP_EFFECT_INFO_RESP                 0x8B
#define AUD_EAP_EFFECT_ADJUST_REQ                0x8C
#define AUD_EAP_EFFECT_ADJUST_RESP               0x8D
#define AUD_EAP_VISUALIZATION_DATA_NTF           0x8E
#define AUD_EAP_DATA_TRACING_REQ                 0x8F
#define AUD_EAP_DATA_TRACING_RESP                0x90
#define AUD_EAP_TUNING_PARAM_READ_REQ            0x91
#define AUD_EAP_TUNING_PARAM_READ_RESP           0x92
#define AUD_EAP_TUNING_PARAM_WRITE_REQ           0x93
#define AUD_EAP_TUNING_PARAM_WRITE_RESP          0x94
#define AUD_EAP_TUNING_PARAM_LOCK_REQ            0x95
#define AUD_EAP_TUNING_PARAM_LOCK_RESP           0x96
#define AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ      0x97
#define AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP     0x98
#define AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ     0x99
#define AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP    0x9A

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define AUD_EAP_STREAM_OPEN_REQ_SB               0x00
#define AUD_EAP_STREAM_PLAY_REQ_SB               0x01
#define AUD_EAP_STREAM_CLOSE_REQ_SB              0x02
#define AUD_EAP_STREAM_CAPTURE_REQ_SB            0x06
#define AUD_EAP_STREAM_TIME_REQ_SB               0x08
#define AUD_EAP_STREAM_PAUSE_REQ_SB              0x0A
#define AUD_EAP_STREAM_OPEN_RESP_SB              0x03
#define AUD_EAP_STREAM_PLAY_RESP_SB              0x04
#define AUD_EAP_STREAM_CLOSE_RESP_SB             0x05
#define AUD_EAP_STREAM_TIME_RESP_SB              0x09
#define AUD_EAP_STREAM_PAUSE_RESP_SB             0x0B
#define AUD_EAP_STREAM_CAPTURE_RESP_SB           0x07
#define AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB    0x00
#define AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB   0x01
#define AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB   0x02
#define AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB  0x03
#define AUD_EAP_CREATE_RATECONTROL_REQ_SB        0x04
#define AUD_EAP_DESTROY_RATECONTROL_REQ_SB       0x05
#define AUD_EAP_CREATE_RATECONTROL_RESP_SB       0x06
#define AUD_EAP_DESTROY_RATECONTROL_RESP_SB      0x07
#define AUD_EAP_DESTROY_3D_LISTENER_REQ_SB       0x1A
#define AUD_EAP_DESTROY_3D_LISTENER_RESP_SB      0x20
#define AUD_EAP_DESTROY_3D_SOURCE_REQ_SB         0x1B
#define AUD_EAP_DESTROY_3D_SOURCE_RESP_SB        0x21
#define AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB    0x1C
#define AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB   0x22
#define AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB      0x1D
#define AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB     0x23
#define AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB  0x1E
#define AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB 0x24
#define AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB  0x1F
#define AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB 0x25
#define AUD_EAP_DESTROY_VISUALIZATION_REQ_SB     0x27
#define AUD_EAP_DESTROY_VISUALIZATION_RESP_SB    0x29
#define AUD_EAP_EFFECT_VISUALIZATION_REQ_SB      0x26
#define AUD_EAP_EFFECT_VISUALIZATION_RESP_SB     0x28
#define AUD_EAP_INFO_RATECONTROL_REQ_SB          0x00
#define AUD_EAP_INFO_RATECONTROL_RESP_SB         0x01
#define AUD_EAP_CREATE_LEVELCHANGE_REQ_SB        0x08
#define AUD_EAP_CREATE_LEVELCHANGE_RESP_SB       0x09
#define AUD_EAP_CREATE_PANCHANGE_REQ_SB          0x0A
#define AUD_EAP_CREATE_PANCHANGE_RESP_SB         0x0B
#define AUD_EAP_INFO_AVAILABILITY_REQ_SB         0x02
#define AUD_EAP_INFO_AVAILABILITY_RESP_SB        0x03
#define AUD_EAP_INFO_VISUALIZATION_REQ_SB        0x04
#define AUD_EAP_INFO_VISUALIZATION_RESP_SB       0x05
#define AUD_EAP_EFFECT_3D_LISTENER_REQ_SB        0x0C
#define AUD_EAP_EFFECT_3D_LISTENER_RESP_SB       0x13
#define AUD_EAP_EFFECT_3D_SOURCE_REQ_SB          0x0D
#define AUD_EAP_EFFECT_3D_SOURCE_RESP_SB         0x14
#define AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB     0x0E
#define AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB    0x15
#define AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB       0x0F
#define AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB      0x16
#define AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB   0x10
#define AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB  0x17
#define AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB   0x11
#define AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB  0x18
#define AUD_EAP_EFFECT_3D_COMMIT_REQ_SB          0x12
#define AUD_EAP_EFFECT_3D_COMMIT_RESP_SB         0x19
#define AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB   0x00
#define AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB   0x01
#define AUD_EAP_EFFECT_VSURROUND_REQ_SB          0x2A
#define AUD_EAP_EFFECT_VSURROUND_RESP_SB         0x2C
#define AUD_EAP_DESTROY_VSURROUND_REQ_SB         0x2B

/* ----------------------------------------------------------------------- */
/* Sequence: AUD_EAP_TUNING_PARAM_STW                                      */
/* ----------------------------------------------------------------------- */
/* Tuning parameters for stereo widening (loudspeaker version only). */

typedef struct
    {
    /* Crosstalk delay in microseconds. [IEEE 754] In practice the range of
       this value is 4.1667-83.3333 when sampling rate is 48000 Hz
    */
    uint32  delay;
    uint32  gain;       /* Crosstalk gain. Value range 0.0-0.7. [IEEE 754] */
    } AUD_EAP_TUNING_PARAM_STW_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_STW_STR   \
        sizeof(AUD_EAP_TUNING_PARAM_STW_STR)


/* ----------------------------------------------------------------------- */
/* Sequence: AUD_EAP_TUNING_PARAM_MUMDRC_VOLUME                            */
/* ----------------------------------------------------------------------- */
/* Tuning parameters for Music-MDRC, volume specific. */

typedef struct
    {
    /* Volume setting this compression curve applies to, in dB. [IEEE 754] */
    uint32  iVolume;
    /* Limiting level for the compression curve, in dB. [IEEE 754] */
    uint32  iEqLimit;
    /* Input level points of the compression curve, in dB. [IEEE 754] */
    int32   iCompressionCurveInLevels[AUD_EAP_EAP_MUMDRC_NUM_CURVE_POINTS];
    /* Output level points of the compression curve, in dB. [IEEE 754] */
    int32   iCompressionCurveOutLevels[AUD_EAP_EAP_MUMDRC_NUM_CURVE_POINTS];
    } AUD_EAP_TUNING_PARAM_MUMDRC_VOLUME_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_MUMDRC_VOLUME_STR   \
        sizeof(AUD_EAP_TUNING_PARAM_MUMDRC_VOLUME_STR)


/* ----------------------------------------------------------------------- */
/* Sequence: AUD_EAP_TUNING_PARAM_MUMDRC_BAND                              */
/* ----------------------------------------------------------------------- */
/* Tuning parameters for Music-MDRC, band specific. */

typedef struct
    {
    uint16  iFrequencyBandNumber;
    uint8   fill1[2];
    /* Attack time (ms) of the attack and release time filter. [IEEE 754] */
    uint32  iAttackTime;
    /* Delay time (ms) of the attack and release time filter. [IEEE 754] */
    uint32  iReleaseTime;
    AUD_EAP_TUNING_PARAM_MUMDRC_VOLUME_STR* volume_tunings;
    } AUD_EAP_TUNING_PARAM_MUMDRC_BAND_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_MUMDRC_BAND_STR   (sizeof(uint16) + \
        2*sizeof(uint8) + 2*sizeof(uint32) + \
        sizeof(AUD_EAP_TUNING_PARAM_MUMDRC_VOLUME_STR*))


/* ----------------------------------------------------------------------- */
/* Sequence: AUD_EAP_TUNING_PARAM_MUMDRC                                   */
/* ----------------------------------------------------------------------- */
/* Tuning parameters for Music-MDRC, band/volume independent. */

typedef struct
    {
    uint16  iNbrOfMuMdrcBands; /* How many bands this set defines */
    /* Number of volume dependent parameter sets for each band */
    uint16  iNbrOfVolumeSets;
    /* Delay time (ms) of the attack and release time filter of the DRC.
       [IEEE 754]
    */
    uint32  iDelayTime;
    /* Linking between different channels in the MDRC configuration so that
       the band level estimates depend on each other. Value range 0.0-1.0.
       [IEEE 754]
    */
    uint32  iCrossBandLink;
    /* Is MDRC used. 1 - MDRC in use. 0 - MDRC not in use.
       A subset of values from the constant table AUD_EAP_MUMDRC_SWITCH
    */
    uint8   iUseMuMdrc;
    uint8   fill1[3];
    AUD_EAP_TUNING_PARAM_MUMDRC_BAND_STR* band_tunings;
    } AUD_EAP_TUNING_PARAM_MUMDRC_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_MUMDRC_STR   (2*sizeof(uint16) + \
        2*sizeof(uint32) + 4*sizeof(uint8) + \
        sizeof(AUD_EAP_TUNING_PARAM_MUMDRC_BAND_STR*))


/* ----------------------------------------------------------------------- */
/* Sequence: AUD_EAP_EFFECT_STATUS                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    /* ID of a specific component of the effect as defined in the audio
       routing network, used with stream specific effects.
    */
    uint32  component;
    /* A subset of values from the constant table AUD_EAP_SWITCH */
    uint8   status;
    uint8   fill1[3];
    } AUD_EAP_EFFECT_STATUS_STR;

#define SIZE_AUD_EAP_EFFECT_STATUS_STR   sizeof(AUD_EAP_EFFECT_STATUS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_OPEN_REQ_SB                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_lenght;
    /* Values from the constant table AUD_EAP_STREAM_SAMPLERATE */
    uint8   samplerate;
    /* Values from the constant table AUD_EAP_STREAM_CHANNELS */
    uint8   channels;
    /* Values from the bitmask table AUD_EAP_STREAM_BUFFER_FORMAT */
    uint16  buffer_format;
    uint16  frame_size;   /* Size of frame in samples */
    uint16  frame_count;  /* Amount of frames */
    /* Values from the constant table AUD_EAP_STREAM_TYPE */
    uint16  stream_type;
    uint32  flags;   /* Values from the bitmask table AUD_EAP_STREAM_FLAGS */
    } tISI_aud_eap_stream_open_req_sb;

#define AUD_EAP_STREAM_OPEN_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_stream_open_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_PLAY_REQ_SB                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_lenght;
    uint16  filler1;
    } tISI_aud_eap_stream_play_req_sb;

#define AUD_EAP_STREAM_PLAY_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_stream_play_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_CLOSE_REQ_SB                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_lenght;
    uint16  filler1;
    } tISI_aud_eap_stream_close_req_sb;

#define AUD_EAP_STREAM_CLOSE_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_stream_close_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_CAPTURE_REQ_SB                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* 0 = continue until stopped, 1,2.. continue until amount of frames
       captured
    */
    uint16  frame_count;
    /* Amount of free frames until notification send, if 0 = default value is
       used
    */
    uint16  threshold;
    /* Source of capturing: internal, external or external playback, if 0 =
       default value is used.
       Values from the bitmask table AUD_EAP_STREAM_CAPTURE_SOURCE
    */
    uint16  capture_source;
    } tISI_aud_eap_stream_capture_req_sb;

#define AUD_EAP_STREAM_CAPTURE_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_stream_capture_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_TIME_REQ_SB                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_stream_time_req_sb;

#define AUD_EAP_STREAM_TIME_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_stream_time_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_PAUSE_REQ_SB                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_stream_pause_req_sb;

#define AUD_EAP_STREAM_PAUSE_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_stream_pause_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_OPEN_RESP_SB                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_lenght;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_stream_open_resp_sb;

#define AUD_EAP_STREAM_OPEN_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_stream_open_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_PLAY_RESP_SB                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_lenght;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_stream_play_resp_sb;

#define AUD_EAP_STREAM_PLAY_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_stream_play_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_CLOSE_RESP_SB                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_lenght;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    uint32  time;
    } tISI_aud_eap_stream_close_resp_sb;

#define AUD_EAP_STREAM_CLOSE_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_stream_close_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_TIME_RESP_SB                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    uint32  time;
    } tISI_aud_eap_stream_time_resp_sb;

#define AUD_EAP_STREAM_TIME_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_stream_time_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_PAUSE_RESP_SB                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    uint32  time;
    } tISI_aud_eap_stream_pause_resp_sb;

#define AUD_EAP_STREAM_PAUSE_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_stream_pause_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_STREAM_CAPTURE_RESP_SB                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_stream_capture_resp_sb;

#define AUD_EAP_STREAM_CAPTURE_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_stream_capture_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_create_stereo_widening_req_sb;

#define AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_create_stereo_widening_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_stereo_widening_req_sb;

#define AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_stereo_widening_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_create_stereo_widening_resp_sb;

#define AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_create_stereo_widening_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_stereo_widening_resp_sb;

#define AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_stereo_widening_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_CREATE_RATECONTROL_REQ_SB                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    uint32  rate;
    } tISI_aud_eap_create_ratecontrol_req_sb;

#define AUD_EAP_CREATE_RATECONTROL_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_create_ratecontrol_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_RATECONTROL_REQ_SB                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_ratecontrol_req_sb;

#define AUD_EAP_DESTROY_RATECONTROL_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_ratecontrol_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_CREATE_RATECONTROL_RESP_SB                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    uint32  rate;
    } tISI_aud_eap_create_ratecontrol_resp_sb;

#define AUD_EAP_CREATE_RATECONTROL_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_create_ratecontrol_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_RATECONTROL_RESP_SB                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_ratecontrol_resp_sb;

#define AUD_EAP_DESTROY_RATECONTROL_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_ratecontrol_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_LISTENER_REQ_SB                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_3d_listener_req_sb;

#define AUD_EAP_DESTROY_3D_LISTENER_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_listener_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_LISTENER_RESP_SB                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_3d_listener_resp_sb;

#define AUD_EAP_DESTROY_3D_LISTENER_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_listener_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_SOURCE_REQ_SB                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_3d_source_req_sb;

#define AUD_EAP_DESTROY_3D_SOURCE_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_source_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_SOURCE_RESP_SB                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_3d_source_resp_sb;

#define AUD_EAP_DESTROY_3D_SOURCE_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_source_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_3d_obstruction_req_sb;

#define AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_obstruction_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_3d_obstruction_resp_sb;

#define AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_obstruction_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_3d_occlusion_req_sb;

#define AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_occlusion_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_3d_occlusion_resp_sb;

#define AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_occlusion_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_3d_distance_attn_req_sb;

#define AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_distance_attn_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_3d_distance_attn_resp_sb;

#define AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_distance_attn_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_3d_reverberation_req_sb;

#define AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_reverberation_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_3d_reverberation_resp_sb;

#define AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_3d_reverberation_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_VISUALIZATION_REQ_SB                          */
/* ----------------------------------------------------------------------- */
/* With this message the visualization effect is destroyed. */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_visualization_req_sb;

#define AUD_EAP_DESTROY_VISUALIZATION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_visualization_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_VISUALIZATION_RESP_SB                         */
/* ----------------------------------------------------------------------- */
/* This is response to AUD_EAP_DESTROY_VISUALIZATION_REQ_SB. */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_destroy_visualization_resp_sb;

#define AUD_EAP_DESTROY_VISUALIZATION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_visualization_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_VISUALIZATION_REQ_SB                           */
/* ----------------------------------------------------------------------- */
/* This subblock is for configuring visualization effect. This SB is used
   when creating the visualization effect or adjusting its parameter when
   visualization is already running. 
*/

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler;
    /* Data Collection Frequency. Describes how many times per second the
       client will receive AUD_EAP_VISUALIZATION_DATA_NTF 
    */
    uint16  data_rate;
    /* AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN if waveformvisualization
       enabled
    */
    uint16  num_samples_waveform;
    /* AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN if spectrumvisualization
       enabled
    */
    uint16  num_samples_spectrum;
    /* xxxxxxxx--------  Reserved
       --------xxxx----  Test mode
       ------------xx--  Reserved2
       --------------xx  Enabled features
    */
    uint16  ctrl_flags;
    } tISI_aud_eap_effect_visualization_req_sb;

#define AUD_EAP_EFFECT_VISUALIZATION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_visualization_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_VISUALIZATION_RESP_SB                          */
/* ----------------------------------------------------------------------- */
/* This subblock is response for AUD_EAP_EFFECT_VISUALIZATION_REQ_SB. */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_viualization_resp_sb;

#define AUD_EAP_EFFECT_VISUALIZATION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_viualization_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_INFO_RATECONTROL_REQ_SB                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_info_ratecontrol_req_sb;

#define AUD_EAP_INFO_RATECONTROL_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_info_ratecontrol_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_INFO_RATECONTROL_RESP_SB                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    uint32  min_rate;
    uint32  max_rate;
    uint32  cur_rate;
    } tISI_aud_eap_info_ratecontrol_resp_sb;

#define AUD_EAP_INFO_RATECONTROL_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_info_ratecontrol_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_CREATE_LEVELCHANGE_REQ_SB                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the bitmask table AUD_EAP_CHANNEL_IDENTIFICATION */
    uint16  channel;
    uint32  volume;
    uint32  time;
    uint32  duration;
    } tISI_aud_eap_create_levelchange_req_sb;

#define AUD_EAP_CREATE_LEVELCHANGE_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_create_levelchange_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_CREATE_LEVELCHANGE_RESP_SB                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_create_levelchange_resp_sb;

#define AUD_EAP_CREATE_LEVELCHANGE_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_create_levelchange_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_CREATE_PANCHANGE_REQ_SB                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the bitmask table AUD_EAP_CHANNEL_IDENTIFICATION */
    uint16  channel;
    uint32  pan;
    uint32  time;
    uint32  duration;
    } tISI_aud_eap_create_panchange_req_sb;

#define AUD_EAP_CREATE_PANCHANGE_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_create_panchange_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_CREATE_PANCHANGE_RESP_SB                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_create_panchange_resp_sb;

#define AUD_EAP_CREATE_PANCHANGE_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_create_panchange_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_INFO_AVAILABILITY_REQ_SB                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_info_availability_req_sb;

#define AUD_EAP_INFO_AVAILABILITY_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_info_availability_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_INFO_AVAILABILITY_RESP_SB                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   nbr_of_effects;
    /* Values from the constant table AUD_EAP_EFFECT_AVAILABLE */
    uint8   effects[AUD_EAP_ANY_SIZE];
    } tISI_aud_eap_info_availability_resp_sb;

#define AUD_EAP_INFO_AVAILABILITY_RESP_SB_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_INFO_VISUALIZATION_REQ_SB                             */
/* ----------------------------------------------------------------------- */
/* With this subblock client can enquire visualization parameters. */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler;
    } tISI_aud_eap_info_visualization_req_sb;

#define AUD_EAP_INFO_VISUALIZATION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_info_visualization_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_INFO_VISUALIZATION_RESP_SB                            */
/* ----------------------------------------------------------------------- */
/* With this subblock visualization parameters are delivered to the client.
*/

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Sample rate of visualized audio
       Values from the constant table AUD_EAP_STREAM_SAMPLERATE
    */
    uint8   sample_rate;
    /* Data Collection Frequency. Describes how many times per second the
       client will receive AUD_EAP_VISUALIZATION_DATA_NTF 
    */
    uint8   data_rate;
    uint16  filler;
    /* xxxxxxxx--------  Reserved
       --------xxxx----  Test mode
       ------------xx--  Reserved2
       --------------xx  Enabled features
    */
    uint16  ctrl_flags;
    /* AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN if waveformvisualization
       enabled
       Number of waveform data samples
    */
    uint16  num_samples_waveform;
    /* AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN if spectrumvisualization
       enabled
       Number of spectrum data samples
    */
    uint16  num_samples_spectrum;
    /* Timestamp is a running 64-bit count of the samples received from the
       input stream. For example, if data collection is set to take place ten
       times per second, the acquisition period is 4800 samples (as sample
       rate within visualization is fixed to 48 kHz) and data collection is
       started from every 4800th sample of the input stream. The timestamp
       value in the output buffer sent to the client reflects the number of
       the first sample in the buffer. In other words, if data rate is 10 the
       timestamp in the first buffer is 0, in the second buffer 4800, in the
       third buffer 9600 and so on. 
    */
    uint32  timestampHi;
    uint32  timestampLo;
    } tISI_aud_eap_info_visualization_resp_sb;

#define AUD_EAP_INFO_VISUALIZATION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_info_visualization_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_LISTENER_REQ_SB                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    uint32  time; /* ms, time when effect will be applied in playback time */
    int32   location_x;   /* mm, listener x coordinate */
    int32   location_y;   /* mm, listener y coordinate */
    int32   location_z;   /* mm, listener z coordinate */
    int32   heading;      /* heading rotation in radians */
    int32   pitch;        /* pitch rotation in radians */
    int32   roll;         /* roll rotation in radians */
    } tISI_aud_eap_effect_3d_listener_req_sb;

#define AUD_EAP_EFFECT_3D_LISTENER_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_listener_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_LISTENER_RESP_SB                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_3d_listener_resp_sb;

#define AUD_EAP_EFFECT_3D_LISTENER_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_listener_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_SOURCE_REQ_SB                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    uint32  time; /* ms, time when effect will be applied in playback time */
    int32   location_x;   /* mm, source x coordinate */
    int32   location_y;   /* mm, source y coordinate */
    int32   location_z;   /* mm, source z coordinate */
    int32   heading;      /* heading rotation in radians */
    int32   pitch;        /* pitch rotation in radians */
    int32   roll;         /* roll rotation in radians */
    } tISI_aud_eap_effect_3d_source_req_sb;

#define AUD_EAP_EFFECT_3D_SOURCE_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_source_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_SOURCE_RESP_SB                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_3d_source_resp_sb;

#define AUD_EAP_EFFECT_3D_SOURCE_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_source_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_OBSTRUCTION_PRESET */
    uint16  preset;
    uint32  time; /* ms, time when effect will be applied in playback time */
    /* mB, output level at 5000 hz in millibels( 1mB = 1 / 100 dB ) at which
       the sound directly from source will be heard compared to the overall
       level of the source. Must be non-positive value. Setting the level
       to 0 makes the source's frequency response flat.
    */
    int32   hf_level;
    /* mB, level in millibels ( 1mB = 1 / 100 dB ) at which the sound
       directly                                 from a source wull be heard
       compared to a non-obstructed source. Must be
       non-positive value. Setting the level to 0 makes the source
       non-osbtructed
    */
    int32   level;
    } tISI_aud_eap_effect_3d_obstruction_req_sb;

#define AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_obstruction_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_3d_obstruction_resp_sb;

#define AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_obstruction_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_OCCLUSION_PRESET */
    uint16  preset;
    uint32  time; /* ms, time when effect will be applied in playback time */
    /* mB, output level at 5000 hz in millibels( 1mB = 1 / 100 dB ) at which
       the sound directly from source will be heard compared to the overall
       level of the source. Must be non-positive value. Setting the level
       to 0 makes the source's frequency response flat.
    */
    int32   hf_level;
    /* mB, level in millibels ( 1mB = 1 / 100 dB ) at which the sound
       directly                                 from a source wull be heard
       compared to a non-obstructed source. Must be
       non-positive value. Setting the level to 0 makes the source
       non-occluded
    */
    int32   level;
    } tISI_aud_eap_effect_3d_occlusion_req_sb;

#define AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_occlusion_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_3d_occlusion_resp_sb;

#define AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_occlusion_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint8   filler1;
    /* TRUE/FALSE, determines how distance gain behaves at distances dreater
       than maximum distance
    */
    uint8   mute_after_max;
    uint32  time; /* ms, time when effect will be applied in playback time */
    /* mm, distance when distance gain is clipped to its maximum value.
       Default value is 1000
    */
    int32   min_distace;
    /* mm, distance when distance gain does not decrease any more */
    int32   max_distace;
    /* Specifies how the direct sound from sound source attenuates with the
       distance to the listener. Default value is 1000
    */
    int32   roll_off_factor;
    int32   air_absorption_level; /* mB */
    /* Specifies how the energy level of the room effect from the sound
       source attenuates with the distance. If reverberation effect
       is not active then this value has no impact on the audio.
       Default value is 0
    */
    int32   room_roll_off_factor;
    } tISI_aud_eap_effect_3d_distance_attn_req_sb;

#define AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_distance_attn_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_3d_distance_attn_resp_sb;

#define AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_distance_attn_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_REVERBERATION_PRESET */
    uint16  preset;
    uint32  time; /* ms, time when effect will be applied in playback time */
    int32   reflection_level; /* mB */
    uint32  reflection_delay; /* ms */
    int32   reverb_level; /* mB */
    uint32  reverb_delay; /* ms */
    uint32  decay_time;   /* ms */
    /* decay hf ratio in millipercentage, 1000 = 100% */
    uint32  decay_hf_ratio;
    uint32  diffusion;    /* diffusion in millipercentage, 1000 = 100% */
    /* modal density in millipercentage, 1000 = 100% */
    uint32  modal_density;
    int32   room_level;   /* mB */
    int32   room_hf_level; /* mB */
    } tISI_aud_eap_effect_3d_reverberation_req_sb;

#define AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_reverberation_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_3d_reverberation_resp_sb;

#define AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_reverberation_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_COMMIT_REQ_SB                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_effect_3d_commit_req_sb;

#define AUD_EAP_EFFECT_3D_COMMIT_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_commit_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_3D_COMMIT_RESP_SB                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_3d_commit_resp_sb;

#define AUD_EAP_EFFECT_3D_COMMIT_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_3d_commit_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    /* 16 bit mono samples for waveform visualization */
    uint16  waveform_data[AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN];
    } AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB_STR;

#define AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB_LEN   \
        sizeof(AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    /* 32 bit power spectrum density values for spectrum visualization */
    uint32  spectrum_data[AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN];
    } AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB_STR;

#define AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB_LEN   \
        sizeof(AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_VSURROUND_REQ_SB - Valid from version 001.002  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    uint32  strength;     /* Effect strength in percentages (0-100) */
    } tISI_aud_eap_effect_vsurround_req_sb;

#define AUD_EAP_EFFECT_VSURROUND_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_effect_vsurround_req_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_EFFECT_VSURROUND_RESP_SB - Valid from version 001.002 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_effect_vsurround_resp_sb;

#define AUD_EAP_EFFECT_VSURROUND_RESP_SB_LEN   \
        sizeof(tISI_aud_eap_effect_vsurround_resp_sb)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EAP_DESTROY_VSURROUND_REQ_SB - Valid from version 001.002 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   command;
    uint8   subblock_length;
    uint16  filler1;
    } tISI_aud_eap_destroy_vsurround_req_sb;

#define AUD_EAP_DESTROY_VSURROUND_REQ_SB_LEN   \
        sizeof(tISI_aud_eap_destroy_vsurround_req_sb)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_STREAM_REQ                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  stream_id;    /* Unique ID for stream identification */
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_STREAM_CAPTURE_REQ_SB
       AUD_EAP_STREAM_CLOSE_REQ_SB
       AUD_EAP_STREAM_OPEN_REQ_SB
       AUD_EAP_STREAM_PAUSE_REQ_SB
       AUD_EAP_STREAM_PLAY_REQ_SB
       AUD_EAP_STREAM_TIME_REQ_SB
    */
    } tISI_aud_eap_stream_req;

#define AUD_EAP_STREAM_REQ_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_STREAM_RESP                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  stream_id;    /* Unique ID for stream identification */
    uint8   reason;
    uint8   filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_STREAM_CAPTURE_RESP_SB
       AUD_EAP_STREAM_CLOSE_RESP_SB
       AUD_EAP_STREAM_OPEN_RESP_SB
       AUD_EAP_STREAM_PAUSE_RESP_SB
       AUD_EAP_STREAM_PLAY_RESP_SB
       AUD_EAP_STREAM_TIME_RESP_SB
    */
    } tISI_aud_eap_stream_resp;

#define AUD_EAP_STREAM_RESP_LEN   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_EFFECT_CREATE_REQ                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* AUD_EAP_MASTER_STREAM_ID, or affected stream_id
       Values from the constant table AUD_EAP_PREDEFINED_STREAM_ID
    */
    uint16  stream_id;
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_CREATE_LEVELCHANGE_REQ_SB
       AUD_EAP_CREATE_PANCHANGE_REQ_SB
       AUD_EAP_CREATE_RATECONTROL_REQ_SB
       AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB
       AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB
       AUD_EAP_EFFECT_3D_LISTENER_REQ_SB
       AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB
       AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB
       AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB
       AUD_EAP_EFFECT_3D_SOURCE_REQ_SB
       AUD_EAP_EFFECT_VISUALIZATION_REQ_SB
       AUD_EAP_EFFECT_VSURROUND_REQ_SB
    */
    } tISI_aud_eap_effect_create_req;

#define AUD_EAP_EFFECT_CREATE_REQ_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_EFFECT_CREATE_RESP                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* AUD_EAP_MASTER_STREAM_ID, or affected stream_id
       Values from the constant table AUD_EAP_PREDEFINED_STREAM_ID
    */
    uint16  stream_id;
    uint8   reason;
    uint8   filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_CREATE_LEVELCHANGE_RESP_SB
       AUD_EAP_CREATE_PANCHANGE_RESP_SB
       AUD_EAP_CREATE_RATECONTROL_RESP_SB
       AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB
       AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB
       AUD_EAP_EFFECT_3D_LISTENER_RESP_SB
       AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB
       AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB
       AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB
       AUD_EAP_EFFECT_3D_SOURCE_RESP_SB
       AUD_EAP_EFFECT_VISUALIZATION_RESP_SB
       AUD_EAP_EFFECT_VSURROUND_RESP_SB
    */
    } tISI_aud_eap_effect_create_resp;

#define AUD_EAP_EFFECT_CREATE_RESP_LEN   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_EFFECT_DESTROY_REQ                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* AUD_EAP_MASTER_STREAM_ID, or affected stream_id
       Values from the constant table AUD_EAP_PREDEFINED_STREAM_ID
    */
    uint16  stream_id;
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB
       AUD_EAP_DESTROY_3D_LISTENER_REQ_SB
       AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB
       AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB
       AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB
       AUD_EAP_DESTROY_3D_SOURCE_REQ_SB
       AUD_EAP_DESTROY_RATECONTROL_REQ_SB
       AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB
       AUD_EAP_DESTROY_VISUALIZATION_REQ_SB
       AUD_EAP_DESTROY_VSURROUND_REQ_SB
    */
    } tISI_aud_eap_effect_destroy_req;

#define AUD_EAP_EFFECT_DESTROY_REQ_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_EFFECT_DESTROY_RESP                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* AUD_EAP_MASTER_STREAM_ID, or affected stream_id
       Values from the constant table AUD_EAP_PREDEFINED_STREAM_ID
    */
    uint16  stream_id;
    uint8   reason;
    uint8   filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB
       AUD_EAP_DESTROY_3D_LISTENER_RESP_SB
       AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB
       AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB
       AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB
       AUD_EAP_DESTROY_3D_SOURCE_RESP_SB
       AUD_EAP_DESTROY_RATECONTROL_RESP_SB
       AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB
       AUD_EAP_DESTROY_VISUALIZATION_RESP_SB
       AUD_EAP_EFFECT_VSURROUND_RESP_SB
    */
    } tISI_aud_eap_effect_destroy_resp;

#define AUD_EAP_EFFECT_DESTROY_RESP_LEN   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_EFFECT_INFO_REQ                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* AUD_EAP_MASTER_STREAM_ID, or affected stream_id
       Values from the constant table AUD_EAP_PREDEFINED_STREAM_ID
    */
    uint16  stream_id;
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_INFO_AVAILABILITY_REQ_SB
       AUD_EAP_INFO_RATECONTROL_REQ_SB
       AUD_EAP_INFO_VISUALIZATION_REQ_SB
    */
    } tISI_aud_eap_effect_info_req;

#define AUD_EAP_EFFECT_INFO_REQ_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_EFFECT_INFO_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* AUD_EAP_MASTER_STREAM_ID, or affected stream_id
       Values from the constant table AUD_EAP_PREDEFINED_STREAM_ID
    */
    uint16  stream_id;
    uint8   reason;
    uint8   filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_INFO_AVAILABILITY_RESP_SB
       AUD_EAP_INFO_RATECONTROL_RESP_SB
       AUD_EAP_INFO_VISUALIZATION_RESP_SB
    */
    } tISI_aud_eap_effect_info_resp;

#define AUD_EAP_EFFECT_INFO_RESP_LEN   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_EFFECT_ADJUST_REQ                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* or user acquired stream id
       Values from the constant table AUD_EAP_PREDEFINED_STREAM_ID
    */
    uint16  stream_id;
    uint16  filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_EFFECT_3D_COMMIT_REQ_SB
       AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB
       AUD_EAP_EFFECT_3D_LISTENER_REQ_SB
       AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB
       AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB
       AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB
       AUD_EAP_EFFECT_3D_SOURCE_REQ_SB
       AUD_EAP_EFFECT_VISUALIZATION_REQ_SB
       AUD_EAP_EFFECT_VSURROUND_REQ_SB
    */
    } tISI_aud_eap_effect_adjust_req;

#define AUD_EAP_EFFECT_ADJUST_REQ_LEN   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_EFFECT_ADJUST_RESP                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* or user acquired stream id
       Values from the constant table AUD_EAP_PREDEFINED_STREAM_ID
    */
    uint16  stream_id;
    uint8   reason;
    uint8   filler1;
    uint8   filler2;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_EFFECT_3D_COMMIT_RESP_SB
       AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB
       AUD_EAP_EFFECT_3D_LISTENER_RESP_SB
       AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB
       AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB
       AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB
       AUD_EAP_EFFECT_3D_SOURCE_RESP_SB
       AUD_EAP_EFFECT_VISUALIZATION_RESP_SB
       AUD_EAP_EFFECT_VSURROUND_RESP_SB
    */
    } tISI_aud_eap_effect_adjust_resp;

#define AUD_EAP_EFFECT_ADJUST_RESP_LEN   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_BUFFER_CLIENT_NTF                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  stream_id;    /* Unique ID for stream identification */
    } tISI_aud_eap_buffer_client_ntf;

#define AUD_EAP_BUFFER_CLIENT_NTF_LEN   \
        sizeof(tISI_aud_eap_buffer_client_ntf)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_BUFFER_SERVER_NTF                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  stream_id;    /* Unique ID for stream identification */
    } tISI_aud_eap_buffer_server_ntf;

#define AUD_EAP_BUFFER_SERVER_NTF_LEN   \
        sizeof(tISI_aud_eap_buffer_server_ntf)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_BUFFER_OVERFLOW_NTF                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  stream_id;    /* Unique ID for stream identification */
    /* Values from the constant table AUD_EAP_BUFFER_OVERFLOW_REASON */
    uint8   reason;
    uint8   filler1;
    uint16  filler2;
    } tISI_aud_eap_buffer_overflow_ntf;

#define AUD_EAP_BUFFER_OVERFLOW_NTF_LEN   \
        sizeof(tISI_aud_eap_buffer_overflow_ntf)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_BUFFER_EMPTY_NTF                                       */
/* ----------------------------------------------------------------------- */
/* This message informs client when all buffer's are empty and EAP start's
   feeding some filling data to output
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  stream_id;    /* Unique ID for stream identification */
    } tISI_aud_eap_buffer_empty_ntf;

#define AUD_EAP_BUFFER_EMPTY_NTF_LEN   sizeof(tISI_aud_eap_buffer_empty_ntf)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_VISUALIZATION_DATA_NTF                                 */
/* ----------------------------------------------------------------------- */
/* With this notification visualization data is sent to client. Notification
   is sent every time the algorithm has collected as many waveform and/or
   spectrum data samples as configured.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  filler1;
    /* AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN if waveformvisualization
       enabled
       Number of waveform data samples
    */
    uint16  num_samples_waveform;
    /* AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN if spectrumvisualization
       enabled
       Number of spectrum data samples
    */
    uint16  num_samples_spectrum;
    /* Timestamp is a running 64-bit count of the samples received from the
       input stream. For example, if data collection is set to take place ten
       times per second, the acquisition period is 4800 samples (as sample
       rate within visualization is fixed to 48 kHz) and data collection is
       started from every 4800th sample of the input stream. The timestamp
       value in the output buffer sent to the client reflects the number of
       the first sample in the buffer. In other words, if data rate is 10 the
       timestamp in the first buffer is 0, in the second buffer 4800, in the
       third buffer 9600 and so on. 
    */
    uint32  timestampHi;
    uint32  timestampLo;
    uint8   filler2[3];
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB
       AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB
    */
    } tISI_aud_eap_visualization_data_ntf;

#define AUD_EAP_VISUALIZATION_DATA_NTF_LEN   (6*sizeof(uint8) + \
        3*sizeof(uint16) + 2*sizeof(uint32))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_DATA_TRACING_REQ                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  filler1;
    /* Values from the bitmask table AUD_EAP_DATA_TRACE_POINTS */
    uint32  trace_points;
    } tISI_aud_eap_data_tracing_req;

#define AUD_EAP_DATA_TRACING_REQ_LEN   sizeof(tISI_aud_eap_data_tracing_req)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_DATA_TRACING_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the constant table AUD_EAP_STREAM_REASON */
    uint8   reason;
    uint8   filler1;
    } tISI_aud_eap_data_tracing_resp;

#define AUD_EAP_DATA_TRACING_RESP_LEN   \
        sizeof(tISI_aud_eap_data_tracing_resp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TUNING_PARAM_READ_REQ                                  */
/* ----------------------------------------------------------------------- */
/* This message is used for requesting the current tuning parameter values of
   the selected audio effect from the phone.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table AUD_EAP_EFFECT */
    uint8   effect;
    uint8   fill1;
    } AUD_EAP_TUNING_PARAM_READ_REQ_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_READ_REQ_STR   \
        sizeof(AUD_EAP_TUNING_PARAM_READ_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TUNING_PARAM_READ_RESP                                 */
/* ----------------------------------------------------------------------- */
/* This message returns the current tuning parameter values of the selected
   audio effect from the phone.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   effect;       /* Values from the constant table AUD_EAP_EFFECT */
    uint8   fill1;
    } AUD_EAP_TUNING_PARAM_READ_RESP_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_READ_RESP_STR   \
        sizeof(AUD_EAP_TUNING_PARAM_READ_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TUNING_PARAM_WRITE_REQ                                 */
/* ----------------------------------------------------------------------- */
/* This message is used for writing the tuning parameter values for the
   selected audio effect to the phone.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table AUD_EAP_EFFECT */
    uint8   effect;
    /* When the lock is set on, tuning parameter values for the selected
       effect can only be changed with this request and not by any other
       event in the system. This applies until the lock is set off.
       A subset of values from the constant table AUD_EAP_SWITCH
    */
    uint8   lock;
    } AUD_EAP_TUNING_PARAM_WRITE_REQ_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_WRITE_REQ_STR   \
        sizeof(AUD_EAP_TUNING_PARAM_WRITE_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TUNING_PARAM_WRITE_RESP                                */
/* ----------------------------------------------------------------------- */
/* This message is used as a response when the tuning parameter values for
   the selected audio effect have been taken into use as requested.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   effect;       /* Values from the constant table AUD_EAP_EFFECT */
    /* A subset of values from the constant table AUD_EAP_SWITCH */
    uint8   lock;
    } AUD_EAP_TUNING_PARAM_WRITE_RESP_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_WRITE_RESP_STR   \
        sizeof(AUD_EAP_TUNING_PARAM_WRITE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TUNING_PARAM_LOCK_REQ                                  */
/* ----------------------------------------------------------------------- */
/* This message is used to lock/unlock the current tuning parameter values
   for the selected effect in the phone.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table AUD_EAP_EFFECT */
    uint8   effect;
    /* When the lock is set on, tuning parameter values for the selected
       effect can only be changed with AUD_EAP_TUNING_PARAM_WRITE_REQ and not
       by any other event in the system. This applies until the lock is set
       off.
       A subset of values from the constant table AUD_EAP_SWITCH
    */
    uint8   lock;
    } AUD_EAP_TUNING_PARAM_LOCK_REQ_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_LOCK_REQ_STR   \
        sizeof(AUD_EAP_TUNING_PARAM_LOCK_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TUNING_PARAM_LOCK_RESP                                 */
/* ----------------------------------------------------------------------- */
/* This message is used as a response when the tuning parameter lock request
   for the selected audio effect has been processed.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   effect;       /* Values from the constant table AUD_EAP_EFFECT */
    /* A subset of values from the constant table AUD_EAP_SWITCH */
    uint8   lock;
    } AUD_EAP_TUNING_PARAM_LOCK_RESP_STR;

#define SIZE_AUD_EAP_TUNING_PARAM_LOCK_RESP_STR   \
        sizeof(AUD_EAP_TUNING_PARAM_LOCK_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ                            */
/* ----------------------------------------------------------------------- */
/* This message is used for reading the on/off status of the selected audio
   effect from the phone.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   effect;       /* Values from the constant table AUD_EAP_EFFECT */
    uint8   fill1;
    /* ID of a specific instance of the effect as defined in the audio
       routing network, used with stream specific effects. 0 means all
       instances are affected.
    */
    uint32  instance;
    } AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ_STR;

#define SIZE_AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ_STR   \
        sizeof(AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP                           */
/* ----------------------------------------------------------------------- */
/* This message returns the on/off status of the selected audio effect. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   effect;       /* Values from the constant table AUD_EAP_EFFECT */
    /* Value can be greater than one only when all components of the effect
       have been queried for their status. Value is zero when there are no
       components of the effect in the system.
    */
    uint8   number;
    AUD_EAP_EFFECT_STATUS_STR* status;
    } AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP_STR;

#define SIZE_AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP_STR   (4*sizeof(uint8) + \
        sizeof(AUD_EAP_EFFECT_STATUS_STR*))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ                           */
/* ----------------------------------------------------------------------- */
/* This message is used for switching the selected audio effect on/off in the
   phone. The effect remains in the requested state until a new request is
   sent.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   effect;       /* Values from the constant table AUD_EAP_EFFECT */
    uint8   fill1;
    /* ID of a specific instance of the effect as defined in the audio
       routing network, used with stream specific effects. 0 means all
       instances are affected.
    */
    uint32  instance;
    uint8   request;      /* Values from the constant table AUD_EAP_SWITCH */
    uint8   fill2[3];
    } AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ_STR;

#define SIZE_AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ_STR   \
        sizeof(AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP                          */
/* ----------------------------------------------------------------------- */
/* This message is used as a response when the state of the selected audio
   effect has been changed as requested.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   effect;       /* Values from the constant table AUD_EAP_EFFECT */
    uint8   fill1;
    /* ID of a specific instance of the effect as defined in the audio
       routing network, used with stream specific effects. 0 means all
       instances are affected.
    */
    uint32  instance;
    /* A subset of values from the constant table AUD_EAP_SWITCH */
    uint8   status;
    uint8   fill2[3];
    } AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP_STR;

#define SIZE_AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP_STR   \
        sizeof(AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP_STR)




#endif /* _AUDIO_EAP_ISI_H */
