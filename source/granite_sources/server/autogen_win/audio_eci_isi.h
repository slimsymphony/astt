/*
NOKIA                                                             CONFIDENTIAL
OULU
Harlekin
Mika P. Kangas



                  audio_eci_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1gif

project path:    global_interface/ISI/Core

name:            audio_eci_isi.h

version:         002.000

type:            incl

instance:        ou_pcms#1


ISI header file for ECI audio Block

Current   ISI Version : 002.000
Supported ISI Versions: 000.001, 000.002, 001.000, 001.001, 002.000

Generated with autogen version 09_w03 on 15-Jan-2009 11:01:32
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 002.000    NON-DRAFT   15-Jan-2009    Seppo Jauho
Reason      : Change request
Reference   : ADB SWAM CR AN08120855382
Description : Changed Subblock AUD_SB_ECI_DAC_ADC_LEVELS
              File Updated 

Version     : 001.001    NON-DRAFT   28-Nov-2006    Raija Kylmanen
Reason      : Change request
Reference   : ADB SWAM CR RK06112949175
Description : Added Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR to AUD_ECI_AUDIO_BLOCK_NTF
              Added Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR to AUD_ECI_AUDIO_BLOCK_NTF
              Added Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR to AUD_ECI_AUDIO_BLOCK_RESP
              Added Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR to AUD_ECI_AUDIO_BLOCK_RESP
              Added Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR to AUD_ECI_PARAM_CONF_REQ
              Added Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR to AUD_ECI_PARAM_CONF_REQ
              Added Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR
              Added Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR
              Added Subblock AUD_SB_ECI_FIR_EQU_PARAMS
              Added Constant table AUD_ECI_COMMON_BITS_PER_SAMPLE
              Added Constant AUD_ECI_IFIREQ_INTEGRATOR_SIZE
              File Updated 

Version     : 001.000    NON-DRAFT   19-Jan-2006    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM CR MK06012039990
Description : Added Subblock AUD_SB_ECI_DSDRC_PROPS to AUD_ECI_AUDIO_BLOCK_NTF
              Discontinued Subblock AUD_SB_ECI_GAIN_COMPENSATION in AUD_ECI_AUDIO_BLOCK_NTF
              Added Subblock AUD_SB_ECI_DSDRC_PROPS to AUD_ECI_AUDIO_BLOCK_RESP
              Discontinued Subblock AUD_SB_ECI_GAIN_COMPENSATION in AUD_ECI_AUDIO_BLOCK_RESP
              Added Message AUD_ECI_GAIN_COMPENSATION_FAIL_RESP
              Added Message AUD_ECI_GAIN_COMPENSATION_OK_RESP
              Added Message AUD_ECI_GAIN_COMPENSATION_REQ
              Changed Message AUD_ECI_PARAM_CONF_REQ
              Changed Message AUD_ECI_PARAM_CONF_RESP
              Changed Sequence AUD_ECI_EQU_IIR_BLOCK_DATA
              Changed Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
              Changed Subblock AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
              Changed Subblock AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
              Discontinued Subblock AUD_SB_ECI_GAIN_COMPENSATION
              Changed Subblock AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
              Changed Subblock AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
              Changed Subblock AUD_SB_ECI_UL_SIDETONE_EQU_IIR
              Changed Subblock AUD_SB_ECI_UL_SPEECH_EQU_IIR
              Discontinued Constant table AUD_ECI_GAIN_COMP_PHYS_STRM
              Added Constant table AUD_ECI_GAIN_COMP_SIGNAL_PATH
              File Updated 

Version     : 000.002    NON-DRAFT   13-Dec-2005    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM CR MK05121336568
Description : Added Subblock AUD_SB_ECI_DSDRC_PARAMS to AUD_ECI_AUDIO_BLOCK_NTF
              Added Subblock AUD_SB_ECI_DSDRC_PARAMS to AUD_ECI_AUDIO_BLOCK_RESP
              Discontinued Subblock AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS in AUD_ECI_PARAM_CONF_RESP
              Added Subblock AUD_SB_ECI_DSDRC_PROPS to AUD_ECI_PARAM_CONF_RESP
              Added Subblock AUD_SB_ECI_DSDRC_PARAMS
              Added Subblock AUD_SB_ECI_DSDRC_PROPS
              File Updated 

Version     : 000.001    NON-DRAFT   07-Oct-2005    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM CR MK05092652108
Description : File created and ECI Audio Block implemented 

------------------------------------------------------------------------------
*/

#ifndef _AUDIO_ECI_ISI_H
#define _AUDIO_ECI_ISI_H

#include "isi_conf.h"

#ifndef AUD_ECI_ISI_VERSION
#define AUD_ECI_ISI_VERSION
#define AUD_ECI_ISI_VERSION_Z   2
#define AUD_ECI_ISI_VERSION_Y   0
#endif

#define AUD_ECI_ISI_MIN_VERSION(z,y) \
 ((AUD_ECI_ISI_VERSION_Z == (z) && AUD_ECI_ISI_VERSION_Y >= (y)) || \
  (AUD_ECI_ISI_VERSION_Z > (z)))

#if !AUD_ECI_ISI_MIN_VERSION(0,1)
#error The specified interface version is not supported by this header file
#elif AUD_ECI_ISI_MIN_VERSION(2,1)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

#define NDEF                                     0x0F
#define AUD_ECI_IFIREQ_INTEGRATOR_SIZE           0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_ACCESSORY - Valid from version 000.001          */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_ACCESSORY_CONST;

#define AUD_ECI_ACCESSORY_HD                     0x00  /* Headset */
#define AUD_ECI_ACCESSORY_LPS                    0x01  /* Loopset */
#define AUD_ECI_ACCESSORY_HF_CAR                 0x02  /* Car handsfree */
/* Home/office handsfree */
#define AUD_ECI_ACCESSORY_HF_OFFICE              0x03
/* Music Listening decive  */
#define AUD_ECI_ACCESSORY_HF_MUSIC               0x04
/* Wire or adapter  */
#define AUD_ECI_ACCESSORY_WIRE                   0x05
#define AUD_ECI_ACCESSORY_TTY                    0x06  /* TTY */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_USER_VOLUME - Valid from version 000.001        */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_USER_VOLUME_CONST;

/* User is not able to adjust the phone volume */
#define AUD_ECI_USER_VOLUME_OFF                  0x00
/* User is able to adjust the phone volume */
#define AUD_ECI_USER_VOLUME_ON                   0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_WIND_NOISE_REDUCTION - Valid from version 000.001 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_WIND_NOISE_REDUCTION_CONST;

/* Wind Noise Reduction OFF (WNR not used in Accessory)  */
#define AUD_ECI_WIND_NOISE_RED_ACC_OFF           0x00
/* Wind Noise Reduction ON (WNR is in use in attached Accessory)  */
#define AUD_ECI_WIND_NOISE_RED_ACC_ON            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_DL_DRC - Valid from version 000.001             */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_DL_DRC_CONST;

/* Accessory does not have Dynamic Range Control. (OFF) */
#define AUD_ECI_DL_DRC_ACC_OFF                   0x00
/* Accessory has Dynamic Range Control (ON) */
#define AUD_ECI_DL_DRC_ACC_ON                    0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_DL_NG - Valid from version 000.001              */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_DL_NG_CONST;

/* Accessory does not have DL noise dependant gaining (OFF), DSP should
   disable the feature
*/
#define AUD_ECI_DL_NG_ACC_OFF                    0x00
/* Accessory has DL noise dependant gaining (ON), DSP should enable the
   feature
*/
#define AUD_ECI_DL_NG_ACC_ON                     0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_HIGH_FREQ_COMP - Valid from version 000.001     */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_HIGH_FREQ_COMP_CONST;

/* Accessory does not have High frequency compensation (OFF) */
#define AUD_ECI_HIGH_FREQ_COMP_ACC_OFF           0x00
/* Accessory does has High frequency compensation (ON) */
#define AUD_ECI_HIGH_FREQ_COMP_ACC_ON            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_DL_NORM - Valid from version 000.001            */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_DL_NORM_CONST;

/* Accessory does not have Downlink normalisation (OFF) */
#define AUD_ECI_DL_NORM_ACC_OFF                  0x00
/* Accessory does has Downlink normalisation (ON) */
#define AUD_ECI_DL_NORM_ACC_ON                   0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_DL_NS - Valid from version 000.001              */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_DL_NS_CONST;

/* Accessory does not have Downlink noise suppressor (OFF) */
#define AUD_ECI_DL_NS_ACC_OFF                    0x00
/* Accessory does has Downlink noise suppressor (ON) */
#define AUD_ECI_DL_NS_ACC_ON                     0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_DOWNLINK_QUALITY - Valid from version 000.001   */
/* ----------------------------------------------------------------------- */
/*  Data defines variation in DL frequency responses between accessories in
   mono case or between left and right channels in stereo case. 
*/
typedef uint8 AUD_ECI_DOWNLINK_QUALITY_CONST;

/* Max variance in relative response > 5 dB  */
#define AUD_ECI_DOWNLINK_QUALITY_LOW             0x00
/* Max variance in relative response < 5 dB  */
#define AUD_ECI_DOWNLINK_QUALITY_MEDIUM          0x01
/* Max variance in relative response < 3 dB  */
#define AUD_ECI_DOWNLINK_QUALITY_GOOD            0x02
/* Max variance in relative response < 2 dB  */
#define AUD_ECI_DOWNLINK_QUALITY_EXCELLENT       0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_AEC_ATTENUATORS - Valid from version 000.001    */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ECI_AEC_ATTENUATORS_CONST;

/* Attenuators are NOT needed */
#define AUD_ECI_AEC_ATTENUATORS_OFF              0x00
/* Attenuators are needed */
#define AUD_ECI_AEC_ATTENUATORS_ON               0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_EX_ACOUSTIC_ECHO - Valid from version 000.001   */
/* ----------------------------------------------------------------------- */
/* Existence of Acoustic Echo from DL to UL in Accessory */
typedef uint8 AUD_ECI_EX_ACOUSTIC_ECHO_CONST;

/* Acoustic echo cancellation disabled in Accessory, Set Echo cancellation ON
   in phone
*/
#define AUD_ECI_EX_ACOUSTIC_NO                   0x00
/* Acoustic echo cancellation enabled in Accessory, Set Echo Cancellation OFF
   in phone
*/
#define AUD_ECI_EX_ACOUSTIC_YES                  0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_ECHO_RATE_CHANGE - Valid from version 000.001   */
/* ----------------------------------------------------------------------- */
/*  Slow choice should be used in case when echo path does not changes fast,
   for example when mic and loudspeaker have constant distance. 
*/
typedef uint8 AUD_ECI_ECHO_RATE_CHANGE_CONST;

/* Change of the rate is slow */
#define AUD_ECI_ECHO_RATE_CHANGE_SLOW            0x00
/* Change of rate is fast */
#define AUD_ECI_ECHO_RATE_CHANGE_FAST            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_USABLE_UL_LF - Valid from version 000.001       */
/* ----------------------------------------------------------------------- */
/*  Defines the lowest practically usable frequency of uplink. In practice -3
   dB point. 
*/
typedef uint16 AUD_ECI_USABLE_UL_LF_CONST;

#define AUD_ECI_USABLE_UL_LF_20HZ                0x0001  /* 20 Hz */
#define AUD_ECI_USABLE_UL_LF_50HZ                0x0004  /* 50 Hz */
#define AUD_ECI_USABLE_UL_LF_150HZ               0x0008  /* 150 Hz */
#define AUD_ECI_USABLE_UL_LF_300HZ               0x0010  /* 300 Hz */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_USABLE_UL_HF - Valid from version 000.001       */
/* ----------------------------------------------------------------------- */
/*  Defines the lowest practically usable frequency of uplink. In practice -3
   dB point. 
*/
typedef uint16 AUD_ECI_USABLE_UL_HF_CONST;

#define AUD_ECI_USABLE_UL_HF_4KHZ                0x0001  /* 4 kHz */
#define AUD_ECI_USABLE_UL_HF_6KHZ                0x0004  /* 6 kHz */
#define AUD_ECI_USABLE_UL_HF_9KHZ                0x0008  /* 9 kHz */
#define AUD_ECI_USABLE_UL_HF_20KHZ               0x0010  /* 20 kHz */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_USABLE_DL_HF - Valid from version 000.001       */
/* ----------------------------------------------------------------------- */
/*  Defines the lowest practically usable frequency of downlink. In practice
   -3 dB point. 
*/
typedef uint16 AUD_ECI_USABLE_DL_HF_CONST;

#define AUD_ECI_USABLE_DL_HF_4KHZ                0x0001  /* 4 kHz */
#define AUD_ECI_USABLE_DL_HF_6KHZ                0x0004  /* 6 kHz */
#define AUD_ECI_USABLE_DL_HF_9KHZ                0x0008  /* 9 kHz */
#define AUD_ECI_USABLE_DL_HF_20KHZ               0x0010  /* 20 kHz */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_EQ_FREQ_RATE - Valid from version 000.001       */
/* ----------------------------------------------------------------------- */
/*  There are three different choices for frequency at the moment 8, 16 and
   48 kHz.
*/
typedef uint8 AUD_ECI_EQ_FREQ_RATE_CONST;

#define AUD_ECI_EQ_FREQ_8KHZ                     0x01  /* 8 kHz */
#define AUD_ECI_EQ_FREQ_16KHZ                    0x04  /* 16 kHz */
#define AUD_ECI_EQ_FREQ_48KHZ                    0x09  /* 48 kHz */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_GAIN_COMP_REASON - Valid from version 000.001   */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_ECI_GAIN_COMP_REASON_CONST;

#define AUD_ECI_MIXER                            0x0000  /* Mixer */
#define AUD_ECI_PEAK_VALUE                       0x0001  /* Peak Value */
#define AUD_ECI_RMS_VALUE                        0x0002  /* RMS Value */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_GAIN_COMP_PHYS_STRM - Versions 000.001 - 001.000 */
/* ----------------------------------------------------------------------- */

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)
typedef uint16 AUD_ECI_GAIN_COMP_PHYS_STRM_CONST;

/* Audio Playback */
#define AUD_ECI_AUDIO_PLAY                       0x0000
/* Speech Playback */
#define AUD_ECI_SPEECH_PLAY                      0x0001
#define AUD_ECI_RM_RADIO                         0x0002  /* FM Radio */
#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_GAIN_COMP_SIGNAL_PATH - Valid from version 001.000 */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_ECI_GAIN_COMP_SIGNAL_PATH_CONST;

#define AUD_ECI_CMT_TONE                         0x0000  /* CMT Tone */
/* CS Downlink Speech */
#define AUD_ECI_CS_DL_SPEECH                     0x0001
/* Symbian Speech Playback */
#define AUD_ECI_SYMBIAN_SPEECH_PLAY              0x0002
/* Symbian Audio Playback */
#define AUD_ECI_SYMBIAN_AUDIO_PLAY               0x0003
#define AUD_ECI_FM_RADIO                         0x0004  /* FM Radio */
/* Symbian Audio Recording */
#define AUD_ECI_SYMBIAN_AUDIO_REC                0x0005
/* Symbian Speech Recording */
#define AUD_ECI_SYMBIAN_SPEECH_REC               0x0006
/* CS Uplink Speech */
#define AUD_ECI_CS_UL_SPEECH                     0x0007

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ECI_COMMON_BITS_PER_SAMPLE - Valid from version 001.001 */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_ECI_COMMON_BITS_PER_SAMPLE_CONST;

/* 16 bit MSB align */
#define AUD_ECI_16_BITS_PER_SAMPLE               0x0000
/* 20 bit MSB align (reserved) */
#define AUD_ECI_20_BITS_PER_SAMPLE               0x0001
/* 24 bit MSB align (reserved) */
#define AUD_ECI_24_BITS_PER_SAMPLE               0x0002
/* 32 bit MSB align */
#define AUD_ECI_32_BITS_PER_SAMPLE               0x0003

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_ECI_DL_UL_CONFIGURATIONS - Valid from version 000.001 */
/* ----------------------------------------------------------------------- */
/*  Will include Downlink specific config information  */
typedef uint16 AUD_ECI_DL_UL_CONFIGURATIONS_CONST;

/* All Downlink paths are disabled */
#define AUD_ECI_DL_OFF                           0x0000  /* --------00000000 */
/* All Uplink paths are disabled */
#define AUD_ECI_UL_OFF                           0x0000  /* 00000000-------- */
/* Phones own mic is enabled */
#define AUD_ECI_HP_MIC_ON                        0x0100  /* -------1-------- */
/* Accessory's Uplink (mic) is available for speech call */
#define AUD_ECI_ACC_MIC_ON                       0x0200  /* ------1--------- */

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define AUD_ECI_AUDIO_BLOCK_REQ                  0x70
#define AUD_ECI_AUDIO_BLOCK_RESP                 0x71
#define AUD_ECI_AUDIO_BLOCK_FAIL_RESP            0x72
#define AUD_ECI_AUDIO_BLOCK_NTF                  0x73
#define AUD_ECI_PARAM_CONF_REQ                   0x74
#define AUD_ECI_PARAM_CONF_RESP                  0x75
#define AUD_ECI_PARAM_CONF_FAIL_RESP             0x76
#define AUD_ECI_GAIN_COMPENSATION_REQ            0x77
#define AUD_ECI_GAIN_COMPENSATION_OK_RESP        0x78
#define AUD_ECI_GAIN_COMPENSATION_FAIL_RESP      0x79

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define AUD_SB_ECI_GENERAL_PARAMS                0x01
#define AUD_SB_ECI_UPLINK_SENSITIVITY            0x02
#define AUD_SB_ECI_DOWNLINK_SENSITIVITY          0x03
#define AUD_SB_ECI_DL_PEAK_VOL_LIMITS            0x09
#define AUD_SB_ECI_ACOUSTIC_ECHO_CTRL            0x05
#define AUD_SB_ECI_SIDETONE                      0x04
#define AUD_SB_ECI_USABLE_BANDS                  0x06
#define AUD_SB_ECI_DISPL_THERM_LIMITS            0x07
#define AUD_SB_ECI_DAC_ADC_LEVELS                0x08
#define AUD_SB_ECI_FIR_EQU_PARAMS                0x1E
#define AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR        0x0A
#define AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR         0x0C
#define AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR         0x0D
#define AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR         0x0E
#define AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR         0x0F
#define AUD_SB_ECI_UL_APE_REC_EQU_1_IIR          0x10
#define AUD_SB_ECI_UL_APE_REC_EQU_2_IIR          0x12
#define AUD_SB_ECI_UL_SPEECH_EQU_IIR             0x14
#define AUD_SB_ECI_UL_SIDETONE_EQU_IIR           0x16
#define AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS         0x18
#define AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS        0x19
#define AUD_SB_ECI_GAIN_COMPENSATION             0x1A
#define AUD_SB_ECI_XPROT_PARAMS                  0x1B
#define AUD_SB_ECI_DSDRC_PROPS                   0x1C
#define AUD_SB_ECI_DSDRC_PARAMS                  0x1D

/* ----------------------------------------------------------------------- */
/* Sequence: AUD_ECI_EQU_IIR_BLOCK_DATA - Versions 000.001 - 001.000       */
/* ----------------------------------------------------------------------- */
/* Uplink / downlink equalizer filter block data. */

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint16  word0;        /* Number of Blocks - 1 */
    uint16  word1;        /* Offset to B coefficients */
    /* (1) Lines 1-4 are repeated as many times as many second order IIR
       blocks are used.
    */
    uint16  word2;
    uint16  word3;        /* (2) */
    uint16  word4;        /* (3) */
    uint16  word5;        /* (4) */
    uint16  word6;        /* Filter output */
    /* (5) Lines 5-7 are repeated as many times as many second order IIR
       blocks are used
    */
    uint16  word7;
    uint16  word8;        /* (6) */
    uint16  word9;        /* (7) */
    } AUD_ECI_EQU_IIR_BLOCK_DATA_STR;

#define SIZE_AUD_ECI_EQU_IIR_BLOCK_DATA_STR   \
        sizeof(AUD_ECI_EQU_IIR_BLOCK_DATA_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_GENERAL_PARAMS - Valid from version 000.001        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Audio mode value from ECI Audio Block
       Values from the constant table AUD_ECI_ACCESSORY
    */
    uint8   accessory_mode;
    /* To propose phone to disable (=0) or enable (=1; normal situation) user
       adjustable volume setting in phone. 
       In the disable case, the volume setting is fixed to same volume than
       in nominal volume level (5/10). 
       The disable case can be chosen when the accessory has it's own volume
       controls and potentially DSP. 
       Values from the constant table AUD_ECI_USER_VOLUME
    */
    uint8   user_volume;
    /* ECI Downlink and Uplink Configurations
       Values from the bitmask table AUD_ECI_DL_UL_CONFIGURATIONS
    */
    uint16  dlul_conf;
    /* Distance between the loudspeakers.Compared to default 30 cm usage
       distance.Distance is needed to calculate the stereo widening
    */
    uint16  ihf_distance;
    } AUD_SB_ECI_GENERAL_PARAMS_STR;

#define SIZE_AUD_SB_ECI_GENERAL_PARAMS_STR   \
        sizeof(AUD_SB_ECI_GENERAL_PARAMS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UPLINK_SENSITIVITY - Valid from version 000.001    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint16  ul_sensitivity; /* Sensitivity of uplink speech  */
    /* Existence of Uplink Wind Noise Reduction in the attached Accessory.
       Values from the constant table AUD_ECI_WIND_NOISE_REDUCTION
    */
    uint8   wn_reduction;
    uint8   Reserved1;
    uint16  ul_amb_noise;
    } AUD_SB_ECI_UPLINK_SENSITIVITY_STR;

#define SIZE_AUD_SB_ECI_UPLINK_SENSITIVITY_STR   \
        sizeof(AUD_SB_ECI_UPLINK_SENSITIVITY_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DOWNLINK_SENSITIVITY - Valid from version 000.001  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Downlink Dynamic Range Control
       Values from the constant table AUD_ECI_DL_DRC
    */
    uint8   dl_drc;
    /* Downlink Noise Gaining
       Values from the constant table AUD_ECI_DL_NG
    */
    uint8   dl_ng;
    /* Existence of DL High frequency compensation in accessory,for example
       to improve intelligibility. 
       Values from the constant table AUD_ECI_HIGH_FREQ_COMP
    */
    uint8   hr_compensation;
    /* Downlink Normalisation. This is voluntary bit, meaning that accessory
       would benefit from long term speech level normalization, for example
       loopset users.
       Values from the constant table AUD_ECI_DL_NORM
    */
    uint8   hr_normalisation;
    /* Existence of Downlink Noise Suppressor in accessory. 
       Values from the constant table AUD_ECI_DL_NS
    */
    uint8   dl_ns;
    /*  Data defines variation in DL frequency responses between accessories
       in mono case or between left and right channels in stereo case. 
       Values from the constant table AUD_ECI_DOWNLINK_QUALITY
    */
    uint8   dl_quality;
    uint16  ltime_vol_limit; /* Long time Voltage limit. */
    uint16  Reserved1;
    } AUD_SB_ECI_DOWNLINK_SENSITIVITY_STR;

#define SIZE_AUD_SB_ECI_DOWNLINK_SENSITIVITY_STR   \
        sizeof(AUD_SB_ECI_DOWNLINK_SENSITIVITY_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_PEAK_VOL_LIMITS - Valid from version 000.001    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Cutoff frequencies/single band use.
       0000 = Limitation is used in single band
       f1/f2|	1500	1725 	1980	2275	2610
       ----------------------------------------------
       700_| 	0001	0010	0011	------	------
       830_|	0100	0101	0110	0111	------
       990_|	------  1000	1001	1010	1011
       1175|	------  ------  1100	1101	1110
       1400|	------  ------	------	1111	------
    */
    uint16  cutoff_freq;
    uint16  low_band_limit; /* Low time limitation. */
    uint16  mid_band_limit; /* Low time limitation. */
    uint16  high_band_limit; /* Low time limitation. */
    uint16  Reserved1;
    } AUD_SB_ECI_DL_PEAK_VOL_LIMITS_STR;

#define SIZE_AUD_SB_ECI_DL_PEAK_VOL_LIMITS_STR   \
        sizeof(AUD_SB_ECI_DL_PEAK_VOL_LIMITS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_ACOUSTIC_ECHO_CTRL - Valid from version 000.001    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Existence of Acoustic Echo from DL to UL in Accessory
       Values from the constant table AUD_ECI_EX_ACOUSTIC_ECHO
    */
    uint8   ex_acoustic_echo;
    /* Need of terminal AEC Attenuators
       Values from the constant table AUD_ECI_AEC_ATTENUATORS
    */
    uint8   aec_att;
    /* Defines how quickly the echo path is assumed to change in real usage.
       Values from the constant table AUD_ECI_ECHO_RATE_CHANGE
    */
    uint8   echo_rate;
    uint8   Reserved1;
    uint16  max_echo_gain; /* Maximum Echo Gain, Loudness of echo  */
    uint16  min_delay;    /* Echo delay seen by connectors from UL to DL.  */
    /* Proposed minimum length of audible acoustic echo used in AEC filter.
    */
    uint16  min_filter_len;
    } AUD_SB_ECI_ACOUSTIC_ECHO_CTRL_STR;

#define SIZE_AUD_SB_ECI_ACOUSTIC_ECHO_CTRL_STR   \
        sizeof(AUD_SB_ECI_ACOUSTIC_ECHO_CTRL_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_SIDETONE - Valid from version 000.001              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Sidetone Delta-G is to attenuate a default sidetone level (from uplink
       to downlink) of an accessory type.
    */
    uint16  stmr;
    } AUD_SB_ECI_SIDETONE_STR;

#define SIZE_AUD_SB_ECI_SIDETONE_STR   sizeof(AUD_SB_ECI_SIDETONE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_USABLE_BANDS - Valid from version 000.001          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Uplink usable low frequency limit
       Values from the constant table AUD_ECI_USABLE_UL_LF
    */
    uint16  ul_lf;
    /* Uplink usable high frequency limit
       Values from the constant table AUD_ECI_USABLE_UL_HF
    */
    uint16  ul_hf;
    /* Downlink usable high frequency limit
       Values from the constant table AUD_ECI_USABLE_DL_HF
    */
    uint16  dl_hf;
    } AUD_SB_ECI_USABLE_BANDS_STR;

#define SIZE_AUD_SB_ECI_USABLE_BANDS_STR   \
        sizeof(AUD_SB_ECI_USABLE_BANDS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DISPL_THERM_LIMITS - Valid from version 000.001    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Defines transducer resonance frequency in system  */
    uint16  res_freq_offset;
    /* Defines to what frequency, frequency response is desired to be
       extended. 
    */
    uint16  max_frequency;
    uint16  orig_q;       /* Original Q-Value  */
    uint16  target_q;     /* Target Q-Value  */
    uint16  max_displacement; /* Scaled maximum displacement of diaphram */
    uint16  therm_res_coil; /* Therm Resistance of Voice Coil  */
    uint16  time_const_coil; /* Time Constant of Voice Coil  */
    uint16  therm_res_mag; /* Thermal Resistance of Magnet  */
    uint16  time_const_magn; /* Time Constant of Magnet  */
    uint16  max_input_pwr; /* Maximum input power  */
    uint16  therm_limit;  /* Thermal Limit  */
    } AUD_SB_ECI_DISPL_THERM_LIMITS_STR;

#define SIZE_AUD_SB_ECI_DISPL_THERM_LIMITS_STR   \
        sizeof(AUD_SB_ECI_DISPL_THERM_LIMITS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DAC_ADC_LEVELS - Versions 000.001 - 002.000        */
/* ----------------------------------------------------------------------- */
/* DAC and ADC sensitivity levels are measurable values which depend on
   system clock frequency (dependent on the used cellular system like GSM,
   TDMA, WCDMA) and audio ASICs (like UEM(E), Retu). These levels are used
   with accessories that contain ACI Audio Block, to adjust analog and
   digital gains according to accessory and platform. Whenever these
   parameters are changed while an accessory with ECI Audio Block is
   connected, MCU Audio Server must recalculate the affected gains and send
   them to DSP as applicable.
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    int16   dac_level;    /* (V/FSU) Format: Q4.11 */
    int16   adc_level;    /* (FSU/V) Format: Q4.11 */
    uint16  Reserved1;
    } AUD_SB_ECI_DAC_ADC_LEVELS_STR;

#define SIZE_AUD_SB_ECI_DAC_ADC_LEVELS_STR   \
        sizeof(AUD_SB_ECI_DAC_ADC_LEVELS_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DAC_ADC_LEVELS - Valid from version 002.000        */
/* ----------------------------------------------------------------------- */
/* DAC and ADC sensitivity levels are measurable values which depend on
   system clock frequency (dependent on the used cellular system like GSM,
   TDMA, WCDMA) and audio ASICs (like UEM(E), Retu). These levels are used
   with accessories that contain ACI Audio Block, to adjust analog and
   digital gains according to accessory and platform. Whenever these
   parameters are changed while an accessory with ECI Audio Block is
   connected, MCU Audio Server must recalculate the affected gains and send
   them to DSP as applicable.
*/

#if AUD_ECI_ISI_MIN_VERSION(2,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    int16   dac_level;    /* (V/FSU) Format: Q4.11 */
    int16   adc_level;    /* (FSU/V) Format: Q4.11 */
    int16   xear_bypass_comp_val;
    } AUD_SB_ECI_DAC_ADC_LEVELS_STR;

#define SIZE_AUD_SB_ECI_DAC_ADC_LEVELS_STR   \
        sizeof(AUD_SB_ECI_DAC_ADC_LEVELS_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(2,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_FIR_EQU_PARAMS - Valid from version 001.001        */
/* ----------------------------------------------------------------------- */
/* FIR Equalizer parameters calculated by the MCU Audio Server.  */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint16  Reserved1;
    int32   lastRnd;      /* HP-TPDF Dither. Default = 1. */
    /*  Threshold for FEQ-D (dynamic response). Format: Q12 => 4096 equals to
       0dB .
    */
    int32   FEQ_D_threshold;
    /*  Ultra-Fine Gain Control - left. Format: Q12 linear. Default = 4096.
    */
    int16   UFGC_gain_left;
    /*  Ultra-Fine Gain Control - right. Format: Q12 linear. Default = 4096.
    */
    int16   UFGC_gain_right;
    /* Attack - for FEQ-D (dynamic response). Default = 32751 (samples). */
    int16   FEQ_D_attack;
    /* Release - for FEQ-D (dynamic response). Default = 3276 (samples). */
    int16   FEQ_D_release;
    /* Hold attack - for FEQ-D (dynamic response). Default = 97 (samples). */
    int16   FEQ_D_hold_attack;
    /* Enabling/disabling dynamic response. 1=enabled, 0=disabled. Should be
       disabled for headset. 
    */
    int16   use_dyn_resp;
    /* 16 or 32-bit sample size
       Values from the constant table AUD_ECI_COMMON_BITS_PER_SAMPLE
    */
    uint16  sample_size;
    uint16  nb_coeffs;    /* Number of FIR filter coefficients  */
    uint16  length_of_delay_lines; /* Length of delay lines */
    /* 1st order IIR integrator coefficients: [a0 b0 b1], for low
       frequencies.
    */
    int16   integrator_coeffs[AUD_ECI_IFIREQ_INTEGRATOR_SIZE];
    /* Filter coefficients (int16); added internally by the MCU audio server.
       NOTE: Actual sub-block size depends on the number of these
       coefficients.
    */
    } AUD_SB_ECI_FIR_EQU_PARAMS_STR;

#define SIZE_AUD_SB_ECI_FIR_EQU_PARAMS_STR   (2*sizeof(uint8) + \
        4*sizeof(uint16) + 2*sizeof(int32) + \
        (6 + AUD_ECI_IFIREQ_INTEGRATOR_SIZE)*sizeof(int16))


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR - Versions 000.001 - 001.000 */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in Tone_Speech
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* IIR specific filter block parameters */
    AUD_ECI_EQU_IIR_BLOCK_DATA_STR iir_block_data;
    } AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR_STR;

#define SIZE_AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR_STR   \
        sizeof(AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR - Valid from version 001.000 */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in Tone_Speech
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* See AUD_ECI_EQU_IIR_BLOCK_DATA. Data size depends on the number of IIR
       filter blocks.
       NOTE! This Data block structure will be build internally in Audio
       Server.
    */
    } AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR_STR;

#define SIZE_AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR - Versions 000.001 - 001.000 */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in APE Playback 1
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* IIR specific filter block parameters */
    AUD_ECI_EQU_IIR_BLOCK_DATA_STR iir_block_data;
    } AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR_STR;

#define SIZE_AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR_STR   \
        sizeof(AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR - Valid from version 001.000 */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in APE Playback 1
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* See AUD_ECI_EQU_IIR_BLOCK_DATA. Data size depends on the number of IIR
       filter blocks.
       NOTE! This Data block structure will be build internally in Audio
       Server.
    */
    } AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR_STR;

#define SIZE_AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR - Valid from version 001.001 */
/* ----------------------------------------------------------------------- */
/* Equalizer properties are used together with information read from the ECI
   Audio Block by the MCU Audio Server to calculate equalizer parameters for
   the DSP 
*/

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum FIR filter order that can be used in the high quality ear EQU
       on the DSP
    */
    uint16  max_order;
    /* 16 or 32-bit sample size on the DSP
       Values from the constant table AUD_ECI_COMMON_BITS_PER_SAMPLE
    */
    uint16  sample_size;
    /* Sampling frequency on the DSP
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    uint8   num_sb;   /* num_sb=0 (clients) or num_sb=1 (MCU Audio Server) */
    /* Subblock list:
       AUD_SB_ECI_FIR_EQU_PARAMS
    */
    } AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR_STR;

#define SIZE_AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR_STR   (4*sizeof(uint8) + \
        2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR - Versions 000.001 - 001.000 */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in APE Playback 2
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* IIR specific filter block parameters */
    AUD_ECI_EQU_IIR_BLOCK_DATA_STR iir_block_data;
    } AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR_STR;

#define SIZE_AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR_STR   \
        sizeof(AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR - Valid from version 001.000 */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in APE Playback 2
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* See AUD_ECI_EQU_IIR_BLOCK_DATA. Data size depends on the number of IIR
       filter blocks.
       NOTE! This Data block structure will be build internally in Audio
       Server.
    */
    } AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR_STR;

#define SIZE_AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR - Valid from version 001.001 */
/* ----------------------------------------------------------------------- */
/* Equalizer properties are used together with information read from the ECI
   Audio Block by the MCU Audio Server to calculate equalizer parameters for
   the DSP 
*/

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum FIR filter order that can be used in the high quality ear EQU
       on the DSP
    */
    uint16  max_order;
    /* 16 or 32-bit sample size on the DSP
       Values from the constant table AUD_ECI_COMMON_BITS_PER_SAMPLE
    */
    uint16  sample_size;
    /* Sampling frequency on the DSP
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    uint8   num_sb;   /* num_sb=0 (clients) or num_sb=1 (MCU Audio Server) */
    /* Subblock list:
       AUD_SB_ECI_FIR_EQU_PARAMS
    */
    } AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR_STR;

#define SIZE_AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR_STR   (4*sizeof(uint8) + \
        2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UL_APE_REC_EQU_1_IIR - Versions 000.001 - 001.000  */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in APE Audio Rec 1
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* IIR specific filter block parameters */
    AUD_ECI_EQU_IIR_BLOCK_DATA_STR iir_block_data;
    } AUD_SB_ECI_UL_APE_REC_EQU_1_IIR_STR;

#define SIZE_AUD_SB_ECI_UL_APE_REC_EQU_1_IIR_STR   \
        sizeof(AUD_SB_ECI_UL_APE_REC_EQU_1_IIR_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UL_APE_REC_EQU_1_IIR - Valid from version 001.000  */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in APE Audio Rec 1
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* See AUD_ECI_EQU_IIR_BLOCK_DATA. Data size depends on the number of IIR
       filter blocks.
       NOTE! This Data block structure will be build internally in Audio
       Server.
    */
    } AUD_SB_ECI_UL_APE_REC_EQU_1_IIR_STR;

#define SIZE_AUD_SB_ECI_UL_APE_REC_EQU_1_IIR_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UL_APE_REC_EQU_2_IIR - Versions 000.001 - 001.000  */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in APE Audio Rec 2
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* IIR specific filter block parameters */
    AUD_ECI_EQU_IIR_BLOCK_DATA_STR iir_block_data;
    } AUD_SB_ECI_UL_APE_REC_EQU_2_IIR_STR;

#define SIZE_AUD_SB_ECI_UL_APE_REC_EQU_2_IIR_STR   \
        sizeof(AUD_SB_ECI_UL_APE_REC_EQU_2_IIR_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UL_APE_REC_EQU_2_IIR - Valid from version 001.000  */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in APE Audio Rec 2
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* See AUD_ECI_EQU_IIR_BLOCK_DATA. Data size depends on the number of IIR
       filter blocks.
       NOTE! This Data block structure will be build internally in Audio
       Server.
    */
    } AUD_SB_ECI_UL_APE_REC_EQU_2_IIR_STR;

#define SIZE_AUD_SB_ECI_UL_APE_REC_EQU_2_IIR_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UL_SPEECH_EQU_IIR - Versions 000.001 - 001.000     */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in Uplink Speech
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* IIR specific filter block parameters */
    AUD_ECI_EQU_IIR_BLOCK_DATA_STR iir_block_data;
    } AUD_SB_ECI_UL_SPEECH_EQU_IIR_STR;

#define SIZE_AUD_SB_ECI_UL_SPEECH_EQU_IIR_STR   \
        sizeof(AUD_SB_ECI_UL_SPEECH_EQU_IIR_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UL_SPEECH_EQU_IIR - Valid from version 001.000     */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in Uplink Speech
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* See AUD_ECI_EQU_IIR_BLOCK_DATA. Data size depends on the number of IIR
       filter blocks.
       NOTE! This Data block structure will be build internally in Audio
       Server.
    */
    } AUD_SB_ECI_UL_SPEECH_EQU_IIR_STR;

#define SIZE_AUD_SB_ECI_UL_SPEECH_EQU_IIR_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UL_SIDETONE_EQU_IIR - Versions 000.001 - 001.000   */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in UL/DL Sidetone
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* IIR specific filter block parameters */
    AUD_ECI_EQU_IIR_BLOCK_DATA_STR iir_block_data;
    } AUD_SB_ECI_UL_SIDETONE_EQU_IIR_STR;

#define SIZE_AUD_SB_ECI_UL_SIDETONE_EQU_IIR_STR   \
        sizeof(AUD_SB_ECI_UL_SIDETONE_EQU_IIR_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_UL_SIDETONE_EQU_IIR - Valid from version 001.000   */
/* ----------------------------------------------------------------------- */
/* Equalizer parameters are used together with information read from ECI
   Audio Block by MCU Audio Server to calculate equalizer blocks for DSP. 
*/

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Maximum number of second order IIR blocks used in UL/DL Sidetone
       equalizer
    */
    uint8   max_blocks;
    /* Sampling Frequency of equalizer
       Values from the constant table AUD_ECI_EQ_FREQ_RATE
    */
    uint8   eq_freq;
    /* See AUD_ECI_EQU_IIR_BLOCK_DATA. Data size depends on the number of IIR
       filter blocks.
       NOTE! This Data block structure will be build internally in Audio
       Server.
    */
    } AUD_SB_ECI_UL_SIDETONE_EQU_IIR_STR;

#define SIZE_AUD_SB_ECI_UL_SIDETONE_EQU_IIR_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS - Valid from version 000.001 */
/* ----------------------------------------------------------------------- */
/* MuMDRC porperties are used together with information read from ECI Audio
   Block by MCU Audio Server to calculate parameters for MuMDRC.
*/

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Band count, which is needed for MuMDRC. Maximum band count is 5 */
    uint16  band_count;
    uint16  limit1;       /* Higher frequency limit for first band. */
    uint16  limit2;       /* Higher frequency limit for second band. */
    uint16  limit3;       /* Higher frequency limit for third band. */
    uint16  limit4;       /* Higher frequency limit for fourth band. */
    uint16  limit5;       /* Higher frequency limit for fifth band. */
    uint16  Reserved1;
    } AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS_STR;

#define SIZE_AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS_STR   \
        sizeof(AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS - Valid from version 000.001 */
/* ----------------------------------------------------------------------- */
/* MuMDRC parameters are sent to MuMDRC.  */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint16  band_count;   /* Band count. */
    uint16  gain1;        /* Gain value for first band. */
    uint16  gain2;        /* Gain value for second band. */
    uint16  gain3;        /* Gain value for third band. */
    uint16  gain4;        /* Gain value for fourth band. */
    uint16  gain5;        /* Gain value for fifth band. */
    uint16  limit_lev1;   /* Limitation level for first band. */
    uint16  limit_lev2;   /* Limitation level for second band. */
    uint16  limit_lev3;   /* Limitation level for third band. */
    uint16  limit_lev4;   /* Limitation level for fourth band. */
    uint16  limit_lev5;   /* Limitation level for fifth band. */
    } AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS_STR;

#define SIZE_AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS_STR   \
        sizeof(AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_GAIN_COMPENSATION - Versions 000.001 - 001.000     */
/* ----------------------------------------------------------------------- */
/*    */

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint16  gain;         /* Gain */
    /* Reason for the gain compensation
       Values from the constant table AUD_ECI_GAIN_COMP_REASON
    */
    uint16  gc_reason;
    /* Physical Stream of Audio
       Values from the constant table AUD_ECI_GAIN_COMP_PHYS_STRM
    */
    uint16  phys_strm;
    } AUD_SB_ECI_GAIN_COMPENSATION_STR;

#define SIZE_AUD_SB_ECI_GAIN_COMPENSATION_STR   \
        sizeof(AUD_SB_ECI_GAIN_COMPENSATION_STR)

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_XPROT_PARAMS - Valid from version 000.001          */
/* ----------------------------------------------------------------------- */
/*    */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Displacement limit, relative to maximum possible (int16) */
    int16   x_lm;
    int16   t_lm;         /* Thermal limit (int16) */
    int16   sigma_T_amb;  /*  Scaling factor (int16) */
    int16   t_att;        /*  Temp. limiter 1 (int16) */
    int16   t_att1;       /*  Temp. limiter 2 (int16) */
    int16   t_rel1;       /* Release time1 (int16) */
    int16   t_rel2;       /* Release time2 (int16) */
    int16   t_rel3;       /* Release time3 (int16) */
    int16   t_limit_fast; /* Temperature limit (int16) */
    int16   sigma_dp;     /* Displ. predictor (int16) */
    int16   a_1_t;        /* Feedback coeff. 1 (int16) */
    int16   a_2_t;        /* Feedback coeff. 2 (int16) */
    int16   t_r;          /* Peak detector, Release-time constant (int16) */
    int16   t_av1;      /* Coefficient averaging,, Attack constant (int16) */
    int16   t_av2;      /* Coefficient averaging, Release constant (int16) */
    int16   pa1n_00;      /* A1 calc polynom. coeff. 0 (int16) */
    int16   pa1n_01;      /* A1 calc polynom. coeff. 1 (int16) */
    int16   pa1n_02;      /* A1 calc polynom. coeff. 2 (int16) */
    int16   pa1n_03;      /* A1 calc polynom. coeff. 3 (int16) */
    int16   pa1n_04;      /* A1 calc polynom. coeff. 4 (int16) */
    int16   pa2n_00;      /* A2 calc polynom. coeff. 0 (int16) */
    int16   pa2n_01;      /* A2 calc polynom. coeff. 1 (int16) */
    int16   pa2n_02;      /* A2 calc polynom. coeff. 2 (int16) */
    int16   pa2n_03;      /* A2 calc polynom. coeff. 3 (int16) */
    int16   pa2n_04;      /* A2 calc polynom. coeff. 4 (int16) */
    int16   s_pa1n;       /* A1 calc, scaling factor (int16) */
    int16   s_pa2n;       /* A2 calc, scaling factor (int16) */
    int16   b_d;          /* LFSN char. sens., denomitor (int16) */
    int16   a_1_r;        /* Init. val. for LFSN feedback coeff. 1 (int16) */
    int16   a_2_r;        /* Init. val. for LFSN feedback coeff. 2 (int16) */
    int16   b_1_c;        /* LFSN Feedforward coeff 1 (int16) */
    int16   b_2_c;        /* LFSN Feedforward coeff 2 (int16) */
    int16   sigma_c_0;    /* LFSN Sensitivity (int16) */
    int16   b_tv;  /* Thermal model, voice coil, feedforward coeff (int16) */
    int16   a_tv;     /* Thermal model, voice coil, feedback coeff (int16) */
    int16   b_tm; /* Thermal model, magnet coil, feedforward coeff (int16) */
    int16   a_tm;    /* Thermal model, magnet coil, feedback coeff (int16) */
    } AUD_SB_ECI_XPROT_PARAMS_STR;

#define SIZE_AUD_SB_ECI_XPROT_PARAMS_STR   \
        sizeof(AUD_SB_ECI_XPROT_PARAMS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DSDRC_PROPS - Valid from version 000.002           */
/* ----------------------------------------------------------------------- */
/* DSDRC properties are used by DSP to inform the Audio Server to calculate
   parameters for DSP DL Speech DRC.
*/

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Band count, which is needed for DSDRC. Maximum band count is 5 */
    uint16  band_count;
    uint16  limit1;       /* Higher frequency limit for first band. */
    uint16  limit2;       /* Higher frequency limit for second band. */
    uint16  limit3;       /* Higher frequency limit for third band. */
    uint16  limit4;       /* Higher frequency limit for fourth band. */
    uint16  limit5;       /* Higher frequency limit for fifth band. */
    uint16  Reserved1;
    } AUD_SB_ECI_DSDRC_PROPS_STR;

#define SIZE_AUD_SB_ECI_DSDRC_PROPS_STR   sizeof(AUD_SB_ECI_DSDRC_PROPS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SB_ECI_DSDRC_PARAMS - Valid from version 000.002          */
/* ----------------------------------------------------------------------- */
/* DSDRC parameters are sent to DSP DL Speech DRC.  */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint16  band_count;   /* Band count. */
    uint16  gain1;        /* Gain value for first band. */
    uint16  gain2;        /* Gain value for second band. */
    uint16  gain3;        /* Gain value for third band. */
    uint16  gain4;        /* Gain value for fourth band. */
    uint16  gain5;        /* Gain value for fifth band. */
    uint16  limit_lev1;   /* Limitation level for first band. */
    uint16  limit_lev2;   /* Limitation level for second band. */
    uint16  limit_lev3;   /* Limitation level for third band. */
    uint16  limit_lev4;   /* Limitation level for fourth band. */
    uint16  limit_lev5;   /* Limitation level for fifth band. */
    } AUD_SB_ECI_DSDRC_PARAMS_STR;

#define SIZE_AUD_SB_ECI_DSDRC_PARAMS_STR   \
        sizeof(AUD_SB_ECI_DSDRC_PARAMS_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_AUDIO_BLOCK_REQ - Valid from version 000.001           */
/* ----------------------------------------------------------------------- */
/* This message is used for requesting ECI audio block data from Audio Server
   by DSP. The message is sent first from DSP to Audio server with needed sub
   blocks id's and then Audio server responses with _RESP message, which will
   include the requested tuning parameters. 
*/

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb_id;
    /* Subblock ID's:
       AUD_SB_ECI_ACOUSTIC_ECHO_CTRL
       AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DISPL_THERM_LIMITS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_PEAK_VOL_LIMITS
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DOWNLINK_SENSITIVITY
       AUD_SB_ECI_DSDRC_PARAMS
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_GAIN_COMPENSATION
       AUD_SB_ECI_GENERAL_PARAMS
       AUD_SB_ECI_SIDETONE
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
       AUD_SB_ECI_UPLINK_SENSITIVITY
       AUD_SB_ECI_USABLE_BANDS
       AUD_SB_ECI_XPROT_PARAMS
    */
    } AUD_ECI_AUDIO_BLOCK_REQ_STR;

#define SIZE_AUD_ECI_AUDIO_BLOCK_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_AUDIO_BLOCK_RESP - Valid from version 000.001          */
/* ----------------------------------------------------------------------- */
/* This message is used for responding to AUD_ECI_AUDIO_BLOCK_REQ message.
   This message will include the required tuning params, which were requested
   by the DSP. 
*/

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb;
    /* Subblock list:
       AUD_SB_ECI_ACOUSTIC_ECHO_CTRL
       AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DISPL_THERM_LIMITS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_PEAK_VOL_LIMITS
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DOWNLINK_SENSITIVITY
       AUD_SB_ECI_DSDRC_PARAMS
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_GAIN_COMPENSATION
       AUD_SB_ECI_GENERAL_PARAMS
       AUD_SB_ECI_SIDETONE
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
       AUD_SB_ECI_UPLINK_SENSITIVITY
       AUD_SB_ECI_USABLE_BANDS
       AUD_SB_ECI_XPROT_PARAMS
    */
    } AUD_ECI_AUDIO_BLOCK_RESP_STR;

#define SIZE_AUD_ECI_AUDIO_BLOCK_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_AUDIO_BLOCK_FAIL_RESP - Valid from version 000.001     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb_id;
    /* Subblock ID's:
       AUD_SB_ECI_ACOUSTIC_ECHO_CTRL
       AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DISPL_THERM_LIMITS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_PEAK_VOL_LIMITS
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DOWNLINK_SENSITIVITY
       AUD_SB_ECI_DSDRC_PARAMS
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_GAIN_COMPENSATION
       AUD_SB_ECI_GENERAL_PARAMS
       AUD_SB_ECI_SIDETONE
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
       AUD_SB_ECI_UPLINK_SENSITIVITY
       AUD_SB_ECI_USABLE_BANDS
       AUD_SB_ECI_XPROT_PARAMS
    */
    } AUD_ECI_AUDIO_BLOCK_FAIL_RESP_STR;

#define SIZE_AUD_ECI_AUDIO_BLOCK_FAIL_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_AUDIO_BLOCK_NTF - Valid from version 000.001           */
/* ----------------------------------------------------------------------- */
/* This notification message is used for sending ECI tuning params from Audio
   server to DSP. No response message is required. 
*/

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb;
    /* Subblock list:
       AUD_SB_ECI_ACOUSTIC_ECHO_CTRL
       AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DISPL_THERM_LIMITS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_PEAK_VOL_LIMITS
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DOWNLINK_SENSITIVITY
       AUD_SB_ECI_DSDRC_PARAMS
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_GAIN_COMPENSATION
       AUD_SB_ECI_GENERAL_PARAMS
       AUD_SB_ECI_SIDETONE
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
       AUD_SB_ECI_UPLINK_SENSITIVITY
       AUD_SB_ECI_USABLE_BANDS
       AUD_SB_ECI_XPROT_PARAMS
    */
    } AUD_ECI_AUDIO_BLOCK_NTF_STR;

#define SIZE_AUD_ECI_AUDIO_BLOCK_NTF_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_PARAM_CONF_REQ - Versions 000.001 - 001.000            */
/* ----------------------------------------------------------------------- */
/* This request message is used to informs audio server the needed
   configurationparameters, which are needed for Gain Planning algorithm. 
*/

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb_id;
    /* Subblock ID's:
       AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DAC_ADC_LEVELS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
    */
    } AUD_ECI_PARAM_CONF_REQ_STR;

#define SIZE_AUD_ECI_PARAM_CONF_REQ_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_PARAM_CONF_REQ - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */
/* This request message is used to informs audio server the needed
   configurationparameters, which are needed for Gain Planning algorithm. 
*/

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb;
    /* Subblock list:
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DAC_ADC_LEVELS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
    */
    } AUD_ECI_PARAM_CONF_REQ_STR;

#define SIZE_AUD_ECI_PARAM_CONF_REQ_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_PARAM_CONF_RESP - Versions 000.001 - 001.000           */
/* ----------------------------------------------------------------------- */

#if AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb;
    /* Subblock list:
       AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DAC_ADC_LEVELS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
    */
    } AUD_ECI_PARAM_CONF_RESP_STR;

#define SIZE_AUD_ECI_PARAM_CONF_RESP_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(0,1) && !AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_PARAM_CONF_RESP - Valid from version 001.000           */
/* ----------------------------------------------------------------------- */

#if AUD_ECI_ISI_MIN_VERSION(1,0)

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb_id;
    /* Subblock ID's:
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DAC_ADC_LEVELS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
    */
    } AUD_ECI_PARAM_CONF_RESP_STR;

#define SIZE_AUD_ECI_PARAM_CONF_RESP_STR   (4*sizeof(uint8))

#endif /* AUD_ECI_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_PARAM_CONF_FAIL_RESP - Valid from version 000.001      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Reserved1;
    uint8   num_sb_id;
    /* Subblock ID's:
       AUD_SB_ECI_APE_PLAY_MUMDRC_PARAMS
       AUD_SB_ECI_APE_PLAY_MUMDRC_PROPS
       AUD_SB_ECI_DAC_ADC_LEVELS
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_1_IIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_FIR
       AUD_SB_ECI_DL_APE_PLAY_EQU_2_IIR
       AUD_SB_ECI_DL_TONE_SPEECH_EQU_IIR
       AUD_SB_ECI_DSDRC_PROPS
       AUD_SB_ECI_UL_APE_REC_EQU_1_IIR
       AUD_SB_ECI_UL_APE_REC_EQU_2_IIR
       AUD_SB_ECI_UL_SIDETONE_EQU_IIR
       AUD_SB_ECI_UL_SPEECH_EQU_IIR
    */
    } AUD_ECI_PARAM_CONF_FAIL_RESP_STR;

#define SIZE_AUD_ECI_PARAM_CONF_FAIL_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_GAIN_COMPENSATION_REQ - Valid from version 001.000     */
/* ----------------------------------------------------------------------- */
/*    */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  gain;         /* Gain */
    /* Reason for the gain compensation
       Values from the constant table AUD_ECI_GAIN_COMP_REASON
    */
    uint16  gc_reason;
    /* Signal Path of Audio
       Values from the constant table AUD_ECI_GAIN_COMP_SIGNAL_PATH
    */
    uint16  signal_path;
    } AUD_ECI_GAIN_COMPENSATION_REQ_STR;

#define SIZE_AUD_ECI_GAIN_COMPENSATION_REQ_STR   \
        sizeof(AUD_ECI_GAIN_COMPENSATION_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_GAIN_COMPENSATION_OK_RESP - Valid from version 001.000 */
/* ----------------------------------------------------------------------- */
/*    */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Reason for the gain compensation
       Values from the constant table AUD_ECI_GAIN_COMP_REASON
    */
    uint16  gc_reason;
    /* Signal Path of Audio
       Values from the constant table AUD_ECI_GAIN_COMP_SIGNAL_PATH
    */
    uint16  signal_path;
    uint16  Reserved1;
    } AUD_ECI_GAIN_COMPENSATION_OK_RESP_STR;

#define SIZE_AUD_ECI_GAIN_COMPENSATION_OK_RESP_STR   \
        sizeof(AUD_ECI_GAIN_COMPENSATION_OK_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_ECI_GAIN_COMPENSATION_FAIL_RESP - Valid from version 001.000 */
/* ----------------------------------------------------------------------- */
/*    */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Reason for the gain compensation
       Values from the constant table AUD_ECI_GAIN_COMP_REASON
    */
    uint16  gc_reason;
    /* Signal Path of Audio
       Values from the constant table AUD_ECI_GAIN_COMP_SIGNAL_PATH
    */
    uint16  signal_path;
    uint16  Reserved1;
    } AUD_ECI_GAIN_COMPENSATION_FAIL_RESP_STR;

#define SIZE_AUD_ECI_GAIN_COMPENSATION_FAIL_RESP_STR   \
        sizeof(AUD_ECI_GAIN_COMPENSATION_FAIL_RESP_STR)




#endif /* _AUDIO_ECI_ISI_H */
