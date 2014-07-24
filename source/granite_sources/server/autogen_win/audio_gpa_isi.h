/*
NOKIA                                                             CONFIDENTIAL
OULU
MCU Audio
Mika P. Kangas



                  audio_gpa_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1glint

project path:    global_interface/ISI/Core

name:            audio_gpa_isi.h

version:         001.000

type:            incl

instance:        ou_pcms#1


ISI header file for GPA Module

Current   ISI Version : 001.000
Supported ISI Versions: 001.000

Generated with autogen version 09_w07_1 on 18-Feb-2009 15:04:21
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 001.000    NON-DRAFT   18-Feb-2009    Seppo Jauho
Reason      : Change request
Reference   : SWAM CR: SJ09010841712
Description : GPA ISI messages. This file Created. 

------------------------------------------------------------------------------
*/

#ifndef _AUDIO_GPA_ISI_H
#define _AUDIO_GPA_ISI_H

#include "isi_conf.h"

#ifndef AUD_GPA_ISI_VERSION
#define AUD_GPA_ISI_VERSION
#define AUD_GPA_ISI_VERSION_Z   1
#define AUD_GPA_ISI_VERSION_Y   0
#endif

#define AUD_GPA_ISI_MIN_VERSION(z,y) \
 ((AUD_GPA_ISI_VERSION_Z == (z) && AUD_GPA_ISI_VERSION_Y >= (y)) || \
  (AUD_GPA_ISI_VERSION_Z > (z)))

#if !AUD_GPA_ISI_MIN_VERSION(1,0)
#error The specified interface version is not supported by this header file
#elif AUD_GPA_ISI_MIN_VERSION(1,1)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

#define AUD_GPA_MAX_DRC_BANDS                    0x05

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_GPA_HW_PATH_SELECT                                  */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_GPA_HW_PATH_SELECT_CONST;

/* Audio Block for AV */
#define AUD_GPA_HW_PATH_AV                       0x0001
/* Audio Block for HP */
#define AUD_GPA_HW_PATH_HP                       0x0002
/* Audio Block for IHF */
#define AUD_GPA_HW_PATH_IHF                      0x0004
/* Audio Block for USB */
#define AUD_GPA_HW_PATH_USB                      0x0008
/* Audio Block for BT */
#define AUD_GPA_HW_PATH_BT                       0x0010

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_GPA_HW_PATH_AV_SUBTYPE_SELECT                       */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_GPA_HW_PATH_AV_SUBTYPE_SELECT_CONST;

/* Audio Block for AV Generic */
#define AUD_GPA_HW_PATH_AV_GENERIC               0x0000
/* Audio Block for AV Basic HF */
#define AUD_GPA_HW_PATH_AV_BASIC_HF              0x0001
/* Audio Block for AV FMTX */
#define AUD_GPA_HW_PATH_AV_FMTX                  0x0002
/* Audio Block for AV Lineout */
#define AUD_GPA_HW_PATH_AV_LINEOUT               0x0003
/* Audio Block for AV TTY */
#define AUD_GPA_HW_PATH_AV_TTY                   0x0004

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_GPA_ACCESSORY_TYPE_SELECT                           */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_GPA_ACCESSORY_TYPE_SELECT_CONST;

#define AUD_GPA_ACCESSORY_TYPE_HEADSET           0x00  /* Headset */
#define AUD_GPA_ACCESSORY_TYPE_LOOPSET           0x01  /* Loopset */
#define AUD_GPA_ACCESSORY_TYPE_CAR_HANDSFREE     0x02  /* Car Handsfree */
/* Home / Office Handsfree */
#define AUD_GPA_ACCESSORY_TYPE_HOME_OR_OFFICE_HANDSFREE 0x03
/* Music listening device */
#define AUD_GPA_ACCESSORY_TYPE_MUSIC_LISTENING_DEVICE 0x04
/* Wire or Adapter */
#define AUD_GPA_ACCESSORY_TYPE_WIRE_OR_ADAPTER   0x05
#define AUD_GPA_ACCESSORY_TYPE_TTY_DEVICE        0x06  /* TTY device */
#define AUD_GPA_ACCESSORY_TYPE_TBD               0x07  /* TBD */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_GPA_ROUTING_SELECT                                  */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_GPA_ROUTING_SELECT_CONST;

#define AUD_GPA_ROUTING_LEFT                     0x00  /* Left only */
#define AUD_GPA_ROUTING_RIGHT                    0x01  /* Right only */
#define AUD_GPA_ROUTING_STEREO                   0x02  /* Stereo */
#define AUD_GPA_ROUTING_DUAL_MONO                0x03  /* Dual mono */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_GPA_VOLUME_CONTROL_SELECT                           */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_GPA_VOLUME_CONTROL_SELECT_CONST;

/* Volume buttons, no own gaining (e.g. HS-42) */
#define AUD_GPA_VOLUME_CONTROL_BUTTONS           0x00
/* own gain, informs phone */
#define AUD_GPA_VOLUME_CONTROL_OWN_INFORMS       0x01
/* own gain, doesn't inform phone (e.g. CK-20W) */
#define AUD_GPA_VOLUME_CONTROL_OWN_NO_INFORM     0x02
/* no volume nor gain control */
#define AUD_GPA_VOLUME_CONTROL_NO                0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_GPA_QUALITY_SELECT                                  */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_GPA_QUALITY_SELECT_CONST;

#define AUD_GPA_QUALITY_LOW                      0x00  /* Low */
#define AUD_GPA_QUALITY_MEDIUM                   0x01  /* Medium */
#define AUD_GPA_QUALITY_GOOD                     0x02  /* Good */
#define AUD_GPA_QUALITY_EXCELLENT                0x03  /* Excellent */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_GPA_EQ_SELECT                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_GPA_EQ_SELECT_CONST;

#define AUD_GPA_EQ_SPEECH                        0x00  /* Speech */
/* Wideband Speech */
#define AUD_GPA_EQ_WB_SPEECH                     0x01
#define AUD_GPA_EQ_AUDIO                         0x02  /* Audio */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_GPA_DL_UL_SELECT                                    */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_GPA_DL_UL_SELECT_CONST;

#define AUD_GPA_DOWNLINK                         0x00  /* Downlink */
#define AUD_GPA_UPLINK                           0x01  /* Uplink */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUG_GPA_HW_PATH_MULTI_SELECT                             */
/* ----------------------------------------------------------------------- */
typedef uint16 AUG_GPA_HW_PATH_MULTI_SELECT_CONST;

/* Path for AV */
#define AUD_GPA_HW_PATH_MULTI_AV                 0x0001  /* ---------------1 */
/* Path for HP */
#define AUD_GPA_HW_PATH_MULTI_HP                 0x0002  /* --------------1- */
/* Path for IHF */
#define AUD_GPA_HW_PATH_MULTI_IHF                0x0004  /* -------------1-- */
/* Path for USB */
#define AUD_GPA_HW_PATH_MULTI_USB                0x0008  /* ------------1--- */
/* Path for BT */
#define AUD_GPA_HW_PATH_MULTI_BT                 0x0010  /* -----------1---- */
/* All Paths */
#define AUD_GPA_HW_PATH_MULTI_ALL                0xFFFF  /* 1111111111111111 */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUG_GPA_HW_PATH_CORRECTION_CONDITION_SELECT              */
/* ----------------------------------------------------------------------- */
typedef uint16 AUG_GPA_HW_PATH_CORRECTION_CONDITION_SELECT_CONST;

/* WB Call */
#define AUD_GPA_HW_PROP_WB_CALL                  0x0001  /* ---------------1 */
/* PHAP */
#define AUD_GPA_HW_PROP_PHAP                     0x0002  /* --------------1- */
/* Slide Open */
#define AUD_GPA_HW_PROP_SLIDE_OPEN               0x0004  /* -------------1-- */

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define AUD_GPA_AB_WRITE_REQ                     0xD0
#define AUD_GPA_AB_WRITE_RESP                    0xD1
#define AUD_GPA_AB_READ_REQ                      0xD2
#define AUD_GPA_AB_READ_RESP                     0xD3
#define AUD_GPA_CURRENT_HW_PATH_IND              0xD4
#define AUD_GPA_AB_CORRECTION_WRITE_REQ          0xD5
#define AUD_GPA_AB_CORRECTION_WRITE_RESP         0xD6
#define AUD_GPA_AB_CORRECTION_READ_REQ           0xD7
#define AUD_GPA_AB_CORRECTION_READ_RESP          0xD8
#define AUD_GPA_AB_AV_LOCK_REQ                   0xD9
#define AUD_GPA_AB_AV_LOCK_RESP                  0xDA
#define AUD_GPA_AB_AV_UNLOCK_REQ                 0xDB
#define AUD_GPA_AB_AV_UNLOCK_RESP                0xDC

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define AUD_GPA_AB_ACCESSORY_TYPE_SB             0x00
#define AUD_GPA_AB_DOWNLINK_ROUTINGS_SB          0x01
#define AUD_GPA_AB_DOWNLINK_SPEAKERS_SB          0x02
#define AUD_GPA_AB_UPLINK_SENSITIVITY_SB         0x03
#define AUD_GPA_AB_UPLINK_FILTER_SB              0x04
#define AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB   0x05
#define AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB    0x06
#define AUD_GPA_AB_ACOUSTIC_ECHO_SB              0x07
#define AUD_GPA_AB_SIDETONE_SB                   0x08
#define AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB       0x09
#define AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB 0x0A
#define AUD_GPA_AB_DOWNLINK_FILTER_SB            0x0B
#define AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB 0x0C
#define AUD_GPA_AB_DOWNLINK_DRC_SB               0x0D
#define AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB 0x0E
#define AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB 0x0F
#define AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB     0x10
#define AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB    0x11
#define AUD_GPA_AB_AEC_SB                        0x12
#define AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB     0x13
#define AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB   0x14
#define AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB 0x15
#define AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB  0x16
#define AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB 0x17
#define AUD_GPA_AB_DOWNLINK_QUALITY_SB           0x18
#define AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB 0x19
#define AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB        0x1A
#define AUD_GPA_AB_DOWNLINK_XPROT_SB             0x1B
#define AUD_GPA_AB_FM_RADIO_CORRECTION_SB        0x1C
#define AUD_GPA_AB_EQ_GAINS_SB                   0x1D
#define AUD_GPA_AB_EQ_GAIN_VALUE_SB              0x1E

/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_ACCESSORY_TYPE_SB                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    /* Values from the constant table AUD_GPA_ACCESSORY_TYPE_SELECT */
    uint8   accessory_type;
    uint8   fill2[3];
    } AUD_GPA_AB_ACCESSORY_TYPE_SB_STR;

#define SIZE_AUD_GPA_AB_ACCESSORY_TYPE_SB_STR   \
        sizeof(AUD_GPA_AB_ACCESSORY_TYPE_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_ROUTINGS_SB                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    /* Values from the constant table AUD_GPA_ROUTING_SELECT */
    uint8   speech_routing;
    /* Values from the constant table AUD_GPA_ROUTING_SELECT */
    uint8   music_routing;
    uint8   fill2[2];
    } AUD_GPA_AB_DOWNLINK_ROUTINGS_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_ROUTINGS_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_ROUTINGS_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_SPEAKERS_SB                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint16  input_impedance;
    uint16  distance_between_loudspeakers;
    } AUD_GPA_AB_DOWNLINK_SPEAKERS_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_SPEAKERS_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_SPEAKERS_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_UPLINK_SENSITIVITY_SB                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    int16   sensitivity;
    uint8   fill2[2];
    } AUD_GPA_AB_UPLINK_SENSITIVITY_SB_STR;

#define SIZE_AUD_GPA_AB_UPLINK_SENSITIVITY_SB_STR   \
        sizeof(AUD_GPA_AB_UPLINK_SENSITIVITY_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_UPLINK_FILTER_SB                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint16  low_freq;     /* Low frequency filter center frequency */
    int16   low_gain;     /* Low frequency filter gain */
    uint16  low_bandwidth; /* Low frequency filter Bandwidth */
    uint16  mid_freq;     /* Mid frequency filter center frequency */
    int16   mid_gain;     /* Mid frequency filter gain */
    uint16  mid_bandwidth; /* Mid frequency filter Bandwidth */
    uint16  hi_freq;      /* Hi frequency filter center frequency */
    int16   hi_gain;      /* Hi frequency filter gain */
    uint16  hi_bandwidth; /* Hi frequency filter Bandwidth */
    uint8   fill2[2];
    } AUD_GPA_AB_UPLINK_FILTER_SB_STR;

#define SIZE_AUD_GPA_AB_UPLINK_FILTER_SB_STR   \
        sizeof(AUD_GPA_AB_UPLINK_FILTER_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   inbuilt;
    uint8   fill2[3];
    } AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB_STR;

#define SIZE_AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB_STR   \
        sizeof(AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   inbuilt;
    uint8   fill2[3];
    } AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB_STR;

#define SIZE_AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB_STR   \
        sizeof(AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_ACOUSTIC_ECHO_SB                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   inbuilt;
    uint8   fill2;
    int16   maximum_echo_gain;
    /* Minimum pure delay represented in 8kHz samples. */
    uint16  minimum_pure_delay;
    uint8   fill3[2];
    } AUD_GPA_AB_ACOUSTIC_ECHO_SB_STR;

#define SIZE_AUD_GPA_AB_ACOUSTIC_ECHO_SB_STR   \
        sizeof(AUD_GPA_AB_ACOUSTIC_ECHO_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_SIDETONE_SB                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    int16   offset;
    uint8   fill2[2];
    } AUD_GPA_AB_SIDETONE_SB_STR;

#define SIZE_AUD_GPA_AB_SIDETONE_SB_STR   sizeof(AUD_GPA_AB_SIDETONE_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    int16   sensitivity;
    uint8   fill2[2];
    } AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint16  highpass_filter_frequency;
    uint8   fill2[2];
    } AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_FILTER_SB                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint16  low_freq;     /* Low frequency filter center frequency */
    int16   low_gain;     /* Low frequency filter gain */
    uint16  low_bandwidth; /* Low frequency filter Bandwidth */
    uint16  low_mid_freq; /* Low-Mid frequency filter center frequency */
    int16   low_mid_gain; /* Low Mid frequency filter gain */
    uint16  low_mid_bandwidth; /* Low Mid frequency filter Bandwidth */
    uint16  mid_hi_freq;  /* Mid-Hi frequency filter center frequency */
    int16   mid_hi_gain;  /* Mid-Hi frequency filter gain */
    uint16  mid_hi_bandwidth; /* Mid-Hi frequency filter Bandwidth */
    uint16  hi_freq;      /* Hi frequency filter center frequency */
    int16   hi_gain;      /* Hi frequency filter gain */
    uint16  hi_bandwidth; /* Hi frequency filter Bandwidth */
    uint16  hi_shelf_freq; /* Hi shelf filter center frequency */
    int16   hi_shelf_gain; /* Hi shelf filter gain */
    } AUD_GPA_AB_DOWNLINK_FILTER_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_FILTER_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_FILTER_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    int16   safety_limit;
    uint8   fill2[2];
    } AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_DRC_SB                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   inbuilt;
    uint8   fill2[3];
    } AUD_GPA_AB_DOWNLINK_DRC_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_DRC_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_DRC_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   inbuilt;
    uint8   fill2[3];
    } AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   inbuilt;
    uint8   fill2[3];
    } AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   uplink_available;
    uint8   fill2[3];
    } AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB_STR;

#define SIZE_AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB_STR   \
        sizeof(AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   user_volume_in_phone;
    uint8   fill2;
    /* Values from the constant table AUD_GPA_VOLUME_CONTROL_SELECT */
    uint8   volume_control_type;
    uint8   fill3;
    } AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_AEC_SB                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    /* Minimum filter length represented in 8kHz samples. */
    uint16  minimum_filter_length;
    uint8   need_aec_attenuators; /* Need of terminal AEC attenuators. */
    /* Defines how quickly the echo path is assumed to change in real usage.
       Slow choice should be used when mic and loudspeaker have constant
       distance compared to each other.
    */
    uint8   SlowEchoRateOfChange;
    } AUD_GPA_AB_AEC_SB_STR;

#define SIZE_AUD_GPA_AB_AEC_SB_STR   sizeof(AUD_GPA_AB_AEC_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   inbuilt_wind_noise_reduction;
    uint8   fill2;
    int16   ambient_noise_reduction;
    } AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB_STR;

#define SIZE_AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB_STR   \
        sizeof(AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint32  low_freq_limit;
    uint32  hi_freq_limit;
    } AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB_STR;

#define SIZE_AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB_STR   \
        sizeof(AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   prefer_normalized_levels;
    uint8   fill2[3];
    } AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   inbuilt;
    uint8   fill2[3];
    } AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    int16   voltage_limit;
    uint8   fill2[2];
    } AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_QUALITY_SB                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    /* Values from the constant table AUD_GPA_QUALITY_SELECT */
    uint8   quality;
    uint8   fill2[3];
    } AUD_GPA_AB_DOWNLINK_QUALITY_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_QUALITY_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_QUALITY_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint32  hi_freq_limit;
    } AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   band_count;
    uint8   fill2;
    uint16  freq_limit[AUD_GPA_MAX_DRC_BANDS + 1];
    int16   peak_limit[AUD_GPA_MAX_DRC_BANDS];
    } AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_DOWNLINK_XPROT_SB                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   activate;
    /* Is transducer encosure design closed (otherwise it is reflex)? */
    uint8   is_closed;
    int16   resonance_frequency_offset;
    uint16  q_value;
    uint16  MaxDispTimesMassPerBiFactor;
    int16   TargetFreqOffset;
    uint16  ThermalResistanceOfVoiceCoil;
    uint16  TimeConstantOfVoiceCoil;
    uint16  ThermalResistanceOfMagnet;
    uint16  TimeConstantOfMagnet;
    uint16  ThermalLimit;
    uint16  AccessoryAmplification;
    uint16  ImpedanceOfDlTransducerAndWires;
    } AUD_GPA_AB_DOWNLINK_XPROT_SB_STR;

#define SIZE_AUD_GPA_AB_DOWNLINK_XPROT_SB_STR   \
        sizeof(AUD_GPA_AB_DOWNLINK_XPROT_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_FM_RADIO_CORRECTION_SB                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    int16   offset;
    uint8   fill2[2];
    } AUD_GPA_AB_FM_RADIO_CORRECTION_SB_STR;

#define SIZE_AUD_GPA_AB_FM_RADIO_CORRECTION_SB_STR   \
        sizeof(AUD_GPA_AB_FM_RADIO_CORRECTION_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_EQ_GAINS_SB                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    int16   speech_dl_g;
    int16   speech_ul_g;
    int16   wb_speech_dl_g;
    int16   wb_speech_ul_g;
    int16   audio_dl_g;
    int16   audio_ul_g;
    } AUD_GPA_AB_EQ_GAINS_SB_STR;

#define SIZE_AUD_GPA_AB_EQ_GAINS_SB_STR   sizeof(AUD_GPA_AB_EQ_GAINS_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_GPA_AB_EQ_GAIN_VALUE_SB                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   equalizer; /* Values from the constant table AUD_GPA_EQ_SELECT */
    /* Values from the constant table AUD_GPA_DL_UL_SELECT */
    uint8   direction;
    int16   gain;
    } AUD_GPA_AB_EQ_GAIN_VALUE_SB_STR;

#define SIZE_AUD_GPA_AB_EQ_GAIN_VALUE_SB_STR   \
        sizeof(AUD_GPA_AB_EQ_GAIN_VALUE_SB_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_WRITE_REQ - Valid from version 001.000              */
/* ----------------------------------------------------------------------- */
/* This message is used for writing audio block data. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table AUD_GPA_HW_PATH_SELECT */
    uint16  hw_path;
    uint16  hw_path_subtype;
    uint16  num_sb;
    /* Subblock list:
       AUD_GPA_AB_ACCESSORY_TYPE_SB
       AUD_GPA_AB_ACOUSTIC_ECHO_SB
       AUD_GPA_AB_AEC_SB
       AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB
       AUD_GPA_AB_DOWNLINK_DRC_SB
       AUD_GPA_AB_DOWNLINK_FILTER_SB
       AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB
       AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB
       AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB
       AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB
       AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB
       AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB
       AUD_GPA_AB_DOWNLINK_QUALITY_SB
       AUD_GPA_AB_DOWNLINK_ROUTINGS_SB
       AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB
       AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB
       AUD_GPA_AB_DOWNLINK_SPEAKERS_SB
       AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB
       AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB
       AUD_GPA_AB_DOWNLINK_XPROT_SB
       AUD_GPA_AB_EQ_GAINS_SB
       AUD_GPA_AB_EQ_GAIN_VALUE_SB
       AUD_GPA_AB_FM_RADIO_CORRECTION_SB
       AUD_GPA_AB_SIDETONE_SB
       AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB
       AUD_GPA_AB_UPLINK_FILTER_SB
       AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB
       AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB
       AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB
       AUD_GPA_AB_UPLINK_SENSITIVITY_SB
       AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB
    */
    } AUD_GPA_AB_WRITE_REQ_STR;

#define SIZE_AUD_GPA_AB_WRITE_REQ_STR   (2*sizeof(uint8) + 3*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_WRITE_RESP - Valid from version 001.000             */
/* ----------------------------------------------------------------------- */
/* This message returns either 0 (= OK) or the sub block IDs that failed or
   were not recognized.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  num_sb_id;
    /* Subblock ID's:
       AUD_GPA_AB_ACCESSORY_TYPE_SB
       AUD_GPA_AB_ACOUSTIC_ECHO_SB
       AUD_GPA_AB_AEC_SB
       AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB
       AUD_GPA_AB_DOWNLINK_DRC_SB
       AUD_GPA_AB_DOWNLINK_FILTER_SB
       AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB
       AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB
       AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB
       AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB
       AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB
       AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB
       AUD_GPA_AB_DOWNLINK_QUALITY_SB
       AUD_GPA_AB_DOWNLINK_ROUTINGS_SB
       AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB
       AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB
       AUD_GPA_AB_DOWNLINK_SPEAKERS_SB
       AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB
       AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB
       AUD_GPA_AB_DOWNLINK_XPROT_SB
       AUD_GPA_AB_EQ_GAINS_SB
       AUD_GPA_AB_EQ_GAIN_VALUE_SB
       AUD_GPA_AB_FM_RADIO_CORRECTION_SB
       AUD_GPA_AB_SIDETONE_SB
       AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB
       AUD_GPA_AB_UPLINK_FILTER_SB
       AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB
       AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB
       AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB
       AUD_GPA_AB_UPLINK_SENSITIVITY_SB
       AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB
    */
    } AUD_GPA_AB_WRITE_RESP_STR;

#define SIZE_AUD_GPA_AB_WRITE_RESP_STR   (2*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_READ_REQ - Valid from version 001.000               */
/* ----------------------------------------------------------------------- */
/* This message is used for reading audio block data. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table AUD_GPA_HW_PATH_SELECT */
    uint16  hw_path;
    uint16  hw_path_subtype;
    uint16  num_sb_id;
    /* Subblock ID's:
       AUD_GPA_AB_ACCESSORY_TYPE_SB
       AUD_GPA_AB_ACOUSTIC_ECHO_SB
       AUD_GPA_AB_AEC_SB
       AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB
       AUD_GPA_AB_DOWNLINK_DRC_SB
       AUD_GPA_AB_DOWNLINK_FILTER_SB
       AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB
       AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB
       AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB
       AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB
       AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB
       AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB
       AUD_GPA_AB_DOWNLINK_QUALITY_SB
       AUD_GPA_AB_DOWNLINK_ROUTINGS_SB
       AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB
       AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB
       AUD_GPA_AB_DOWNLINK_SPEAKERS_SB
       AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB
       AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB
       AUD_GPA_AB_DOWNLINK_XPROT_SB
       AUD_GPA_AB_EQ_GAINS_SB
       AUD_GPA_AB_EQ_GAIN_VALUE_SB
       AUD_GPA_AB_FM_RADIO_CORRECTION_SB
       AUD_GPA_AB_SIDETONE_SB
       AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB
       AUD_GPA_AB_UPLINK_FILTER_SB
       AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB
       AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB
       AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB
       AUD_GPA_AB_UPLINK_SENSITIVITY_SB
       AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB
    */
    } AUD_GPA_AB_READ_REQ_STR;

#define SIZE_AUD_GPA_AB_READ_REQ_STR   (2*sizeof(uint8) + 3*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_READ_RESP - Valid from version 001.000              */
/* ----------------------------------------------------------------------- */
/* This message returns audio block data for supported sub block IDs. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  num_sb;
    /* Subblock list:
       AUD_GPA_AB_ACCESSORY_TYPE_SB
       AUD_GPA_AB_ACOUSTIC_ECHO_SB
       AUD_GPA_AB_AEC_SB
       AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB
       AUD_GPA_AB_DOWNLINK_DRC_SB
       AUD_GPA_AB_DOWNLINK_FILTER_SB
       AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB
       AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB
       AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB
       AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB
       AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB
       AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB
       AUD_GPA_AB_DOWNLINK_QUALITY_SB
       AUD_GPA_AB_DOWNLINK_ROUTINGS_SB
       AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB
       AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB
       AUD_GPA_AB_DOWNLINK_SPEAKERS_SB
       AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB
       AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB
       AUD_GPA_AB_DOWNLINK_XPROT_SB
       AUD_GPA_AB_EQ_GAINS_SB
       AUD_GPA_AB_EQ_GAIN_VALUE_SB
       AUD_GPA_AB_FM_RADIO_CORRECTION_SB
       AUD_GPA_AB_SIDETONE_SB
       AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB
       AUD_GPA_AB_UPLINK_FILTER_SB
       AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB
       AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB
       AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB
       AUD_GPA_AB_UPLINK_SENSITIVITY_SB
       AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB
    */
    } AUD_GPA_AB_READ_RESP_STR;

#define SIZE_AUD_GPA_AB_READ_RESP_STR   (2*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_CURRENT_HW_PATH_IND - Valid from version 001.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table AUD_GPA_HW_PATH_SELECT */
    uint16  pri_hw_path;
    /* Values from the constant table AUD_GPA_HW_PATH_SELECT */
    uint16  mic_hw_path;
    /* Values from the constant table AUD_GPA_HW_PATH_SELECT */
    uint16  sec_hw_path;
    /* Values from the constant table AUD_GPA_HW_PATH_AV_SUBTYPE_SELECT */
    uint16  hw_path_av_subtype;
    } AUD_GPA_CURRENT_HW_PATH_IND_STR;

#define SIZE_AUD_GPA_CURRENT_HW_PATH_IND_STR   \
        sizeof(AUD_GPA_CURRENT_HW_PATH_IND_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_CORRECTION_WRITE_REQ - Valid from version 001.000   */
/* ----------------------------------------------------------------------- */
/* This message is used for writing audio block correction data. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the bitmask table AUG_GPA_HW_PATH_MULTI_SELECT */
    uint16  hw_paths;
    /* Values from the bitmask table
       AUG_GPA_HW_PATH_CORRECTION_CONDITION_SELECT
    */
    uint16  condition;
    uint16  num_sb;
    /* Subblock list:
       AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB
       AUD_GPA_AB_SIDETONE_SB
       AUD_GPA_AB_UPLINK_SENSITIVITY_SB
    */
    } AUD_GPA_AB_CORRECTION_WRITE_REQ_STR;

#define SIZE_AUD_GPA_AB_CORRECTION_WRITE_REQ_STR   (2*sizeof(uint8) + \
        3*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_CORRECTION_WRITE_RESP - Valid from version 001.000  */
/* ----------------------------------------------------------------------- */
/* This message returns either 0 (= OK) or the sub block IDs that failed or
   were not recognized.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  num_sb_id;
    /* Subblock ID's:
       AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB
       AUD_GPA_AB_SIDETONE_SB
       AUD_GPA_AB_UPLINK_SENSITIVITY_SB
    */
    } AUD_GPA_AB_CORRECTION_WRITE_RESP_STR;

#define SIZE_AUD_GPA_AB_CORRECTION_WRITE_RESP_STR   (2*sizeof(uint8) + \
        sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_CORRECTION_READ_REQ - Valid from version 001.000    */
/* ----------------------------------------------------------------------- */
/* This message is used for reading audio block correction data. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the bitmask table AUG_GPA_HW_PATH_MULTI_SELECT */
    uint16  hw_paths;
    /* Values from the bitmask table
       AUG_GPA_HW_PATH_CORRECTION_CONDITION_SELECT
    */
    uint16  condition;
    uint16  num_sb_id;
    /* Subblock ID's:
       AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB
       AUD_GPA_AB_SIDETONE_SB
       AUD_GPA_AB_UPLINK_SENSITIVITY_SB
    */
    } AUD_GPA_AB_CORRECTION_READ_REQ_STR;

#define SIZE_AUD_GPA_AB_CORRECTION_READ_REQ_STR   (2*sizeof(uint8) + \
        3*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_CORRECTION_READ_RESP - Valid from version 001.000   */
/* ----------------------------------------------------------------------- */
/* This message returns audio block correction data for supported sub block
   IDs.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  num_sb;
    /* Subblock list:
       AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB
       AUD_GPA_AB_SIDETONE_SB
       AUD_GPA_AB_UPLINK_SENSITIVITY_SB
    */
    } AUD_GPA_AB_CORRECTION_READ_RESP_STR;

#define SIZE_AUD_GPA_AB_CORRECTION_READ_RESP_STR   (2*sizeof(uint8) + \
        sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_AV_LOCK_REQ - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */
/* This message is used for locking audio block for av output. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table AUD_GPA_HW_PATH_AV_SUBTYPE_SELECT */
    uint16  hw_path_av_subtype;
    } AUD_GPA_AB_AV_LOCK_REQ_STR;

#define SIZE_AUD_GPA_AB_AV_LOCK_REQ_STR   sizeof(AUD_GPA_AB_AV_LOCK_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_AV_LOCK_RESP - Valid from version 001.000           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    } AUD_GPA_AB_AV_LOCK_RESP_STR;

#define SIZE_AUD_GPA_AB_AV_LOCK_RESP_STR   \
        sizeof(AUD_GPA_AB_AV_LOCK_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_AV_UNLOCK_REQ - Valid from version 001.000          */
/* ----------------------------------------------------------------------- */
/* This message is used for unlocking audio block for av output. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    } AUD_GPA_AB_AV_UNLOCK_REQ_STR;

#define SIZE_AUD_GPA_AB_AV_UNLOCK_REQ_STR   \
        sizeof(AUD_GPA_AB_AV_UNLOCK_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_GPA_AB_AV_UNLOCK_RESP - Valid from version 001.000         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    } AUD_GPA_AB_AV_UNLOCK_RESP_STR;

#define SIZE_AUD_GPA_AB_AV_UNLOCK_RESP_STR   \
        sizeof(AUD_GPA_AB_AV_UNLOCK_RESP_STR)




#endif /* _AUDIO_GPA_ISI_H */
