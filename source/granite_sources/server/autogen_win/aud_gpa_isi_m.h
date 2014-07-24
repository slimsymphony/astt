/*
NOKIA
R&D Oulu
ISA Operations










            AUDIO Server ECI Message Macro definitions
            ------------------------------------------

            SW include - ANSI C




Continuus Ref:
--------------
database:           ou1gif

project path:       global_interface/ISI/Core

%name:              aud_gpa_isi_m.h %

%version:           001.000.1 %

%cvtype:            incl %

%instance:          ou1core_1 %


Copyright(c)Nokia


Change history:

VERSION     : 001.000 NONDRAFT  18-Feb-2009 Seppo Jauho
REASON      : Change request
REFERENCE   : SWAM CR: SJ09010841712
DESCRIPTION : ou1core#122072: Audio: Seppo Jauho: GPA isi interface (SJ09010841712)
              
*/


/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Header file for the ISI Autogeneration Application


    1.2    Functional description

    This file is the message definition file for the ISA EAP Module


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

/* GPA message Id's */
#define AUD_GPA_AB_WRITE_REQ                    0xd0
#define AUD_GPA_AB_WRITE_RESP                   0xd1
#define AUD_GPA_AB_READ_REQ                     0xd2
#define AUD_GPA_AB_READ_RESP                    0xd3
#define AUD_GPA_CURRENT_HW_PATH_IND             0xd4
#define AUD_GPA_AB_CORRECTION_WRITE_REQ         0xd5
#define AUD_GPA_AB_CORRECTION_WRITE_RESP        0xd6
#define AUD_GPA_AB_CORRECTION_READ_REQ          0xd7
#define AUD_GPA_AB_CORRECTION_READ_RESP         0xd8
#define AUD_GPA_AB_AV_LOCK_REQ                  0xd9
#define AUD_GPA_AB_AV_LOCK_RESP                 0xda
#define AUD_GPA_AB_AV_UNLOCK_REQ                0xdb
#define AUD_GPA_AB_AV_UNLOCK_RESP               0xdc

/* Audio Block subblock Id's */
#define AUD_GPA_AB_ACCESSORY_TYPE_SB                     0x00
#define AUD_GPA_AB_DOWNLINK_ROUTINGS_SB                  0x01
#define AUD_GPA_AB_DOWNLINK_SPEAKERS_SB                  0x02
#define AUD_GPA_AB_UPLINK_SENSITIVITY_SB                 0x03
#define AUD_GPA_AB_UPLINK_FILTER_SB                      0x04
#define AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB           0x05
#define AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB            0x06
#define AUD_GPA_AB_ACOUSTIC_ECHO_SB                      0x07
#define AUD_GPA_AB_SIDETONE_SB                           0x08
#define AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB               0x09
#define AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB      0x0a
#define AUD_GPA_AB_DOWNLINK_FILTER_SB                    0x0b
#define AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB         0x0c
#define AUD_GPA_AB_DOWNLINK_DRC_SB                       0x0d
#define AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB   0x0e
#define AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB      0x0f
#define AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB             0x10
#define AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB            0x11
#define AUD_GPA_AB_AEC_SB                                0x12
#define AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB             0x13
#define AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB           0x14
#define AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB       0x15
#define AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB          0x16
#define AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB   0x17
#define AUD_GPA_AB_DOWNLINK_QUALITY_SB                   0x18
#define AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB         0x19
#define AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB                0x1a
#define AUD_GPA_AB_DOWNLINK_XPROT_SB                     0x1b
#define AUD_GPA_AB_FM_RADIO_CORRECTION_SB                0x1c
#define AUD_GPA_AB_EQ_GAINS_SB                           0x1d
#define AUD_GPA_AB_EQ_GAIN_VALUE_SB                      0x1e

/* Macros */

#ifndef AUD_GPA_ISI_VERSION
#define AUD_GPA_ISI_VERSION
#define AUD_GPA_ISI_VERSION_Z   1
#define AUD_GPA_ISI_VERSION_Y   0
#endif

/* version history and cover page information */
/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "OULU")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "MCU Audio")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Mika P. Kangas")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIAL")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "AUDIO SERVER / GPA AUDIO MODULE ISI MESSAGE DESCRIPTION")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_aud_gpa_isi_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou1glint")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS-ou1glint#browse")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "GIF_SPECS/CoreSW")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

/* ISIHDR properties */
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "ou_pcms#1")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, "ou_pcms#1")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou1glint")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_interface/ISI/Core")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,  "global_interface/ISI/Core")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "audio_gpa_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "audio_gpa_isi_16.h")

RES_BEGIN(RESOURCE_ISI_EXTENSION, PN_AUDIO, AUD_GPA, "GPA Module",
    RES_VERSION_STRING(AUD_GPA_ISI_VERSION_Z, AUD_GPA_ISI_VERSION_Y), FALSE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */
    
    /* TODO: Add version history block every time the interface is changed */

     /* Latest version */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: SJ09010841712")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "18-Feb-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Seppo Jauho")
    COMMENT(COMMENT_TEXT, "GPA ISI messages. This file Created. ")
    ISI_VERSION_HISTORY("001.000")
    
    /* CONSTANT TABLES */
    
    CONST_TBL_BEGIN(AUD_GPA_HW_PATH_SELECT, 16, BE, "", "")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_AV,  0x1, "Audio Block for AV")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_HP,  0x2, "Audio Block for HP")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_IHF, 0x4, "Audio Block for IHF")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_USB, 0x8, "Audio Block for USB")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_BT, 0x10, "Audio Block for BT")
    CONST_TBL_END
    
    CONST_TBL_BEGIN(AUD_GPA_HW_PATH_AV_SUBTYPE_SELECT, 16, BE, "", "")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_AV_GENERIC,  0x0, "Audio Block for AV Generic")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_AV_BASIC_HF, 0x1, "Audio Block for AV Basic HF")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_AV_FMTX,     0x2, "Audio Block for AV FMTX")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_AV_LINEOUT,  0x3, "Audio Block for AV Lineout")
        CONST_TBL_ENTRY(AUD_GPA_HW_PATH_AV_TTY,      0x4, "Audio Block for AV TTY")
    CONST_TBL_END
    
    CONST_TBL_BEGIN(AUD_GPA_ACCESSORY_TYPE_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_GPA_ACCESSORY_TYPE_HEADSET,                  0x0, "Headset")
        CONST_TBL_ENTRY(AUD_GPA_ACCESSORY_TYPE_LOOPSET,                  0x1, "Loopset")
        CONST_TBL_ENTRY(AUD_GPA_ACCESSORY_TYPE_CAR_HANDSFREE,            0x2, "Car Handsfree")
        CONST_TBL_ENTRY(AUD_GPA_ACCESSORY_TYPE_HOME_OR_OFFICE_HANDSFREE, 0x3, "Home / Office Handsfree")
        CONST_TBL_ENTRY(AUD_GPA_ACCESSORY_TYPE_MUSIC_LISTENING_DEVICE,   0x4, "Music listening device")
        CONST_TBL_ENTRY(AUD_GPA_ACCESSORY_TYPE_WIRE_OR_ADAPTER,          0x5, "Wire or Adapter")
        CONST_TBL_ENTRY(AUD_GPA_ACCESSORY_TYPE_TTY_DEVICE,               0x6, "TTY device")
        CONST_TBL_ENTRY(AUD_GPA_ACCESSORY_TYPE_TBD,                      0x7, "TBD")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_GPA_ROUTING_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_GPA_ROUTING_LEFT,      0x0, "Left only")
        CONST_TBL_ENTRY(AUD_GPA_ROUTING_RIGHT,     0x1, "Right only")
        CONST_TBL_ENTRY(AUD_GPA_ROUTING_STEREO,    0x2, "Stereo")
        CONST_TBL_ENTRY(AUD_GPA_ROUTING_DUAL_MONO, 0x3, "Dual mono")
    CONST_TBL_END
    
    CONST_TBL_BEGIN(AUD_GPA_VOLUME_CONTROL_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_GPA_VOLUME_CONTROL_BUTTONS,       0x0, "Volume buttons, no own gaining (e.g. HS-42)")
        CONST_TBL_ENTRY(AUD_GPA_VOLUME_CONTROL_OWN_INFORMS,   0x1, "own gain, informs phone")
        CONST_TBL_ENTRY(AUD_GPA_VOLUME_CONTROL_OWN_NO_INFORM, 0x2, "own gain, doesn't inform phone (e.g. CK-20W)")
        CONST_TBL_ENTRY(AUD_GPA_VOLUME_CONTROL_NO,            0x3, "no volume nor gain control")
    CONST_TBL_END 
    
    CONST_TBL_BEGIN(AUD_GPA_QUALITY_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_GPA_QUALITY_LOW,       0x0, "Low")
        CONST_TBL_ENTRY(AUD_GPA_QUALITY_MEDIUM,    0x1, "Medium")
        CONST_TBL_ENTRY(AUD_GPA_QUALITY_GOOD,      0x2, "Good")
        CONST_TBL_ENTRY(AUD_GPA_QUALITY_EXCELLENT, 0x3, "Excellent")
    CONST_TBL_END
    
    CONST_TBL_BEGIN(AUD_GPA_EQ_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_GPA_EQ_SPEECH,    0x0, "Speech")
        CONST_TBL_ENTRY(AUD_GPA_EQ_WB_SPEECH, 0x1, "Wideband Speech")
        CONST_TBL_ENTRY(AUD_GPA_EQ_AUDIO,     0x2, "Audio")
    CONST_TBL_END    
    
    CONST_TBL_BEGIN(AUD_GPA_DL_UL_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_GPA_DOWNLINK, 0x0, "Downlink")
        CONST_TBL_ENTRY(AUD_GPA_UPLINK,   0x1, "Uplink")
    CONST_TBL_END        
    
    /* BIT TABLES */     
    
    BIT_TBL_BEGIN(AUG_GPA_HW_PATH_MULTI_SELECT, 16, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxxx1", AUD_GPA_HW_PATH_MULTI_AV,  /*    0x1, */ "Path for AV")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxx1x", AUD_GPA_HW_PATH_MULTI_HP,  /*    0x2, */ "Path for HP")
        BIT_TBL_ENTRY("xxxxxxxxxxxxx1xx", AUD_GPA_HW_PATH_MULTI_IHF, /*    0x4, */ "Path for IHF")
        BIT_TBL_ENTRY("xxxxxxxxxxxx1xxx", AUD_GPA_HW_PATH_MULTI_USB, /*    0x8, */ "Path for USB")
        BIT_TBL_ENTRY("xxxxxxxxxxx1xxxx", AUD_GPA_HW_PATH_MULTI_BT,  /*   0x10, */ "Path for BT")
        BIT_TBL_ENTRY("1111111111111111", AUD_GPA_HW_PATH_MULTI_ALL, /* 0xffff, */ "All Paths")
    BIT_TBL_END
    
    BIT_TBL_BEGIN(AUG_GPA_HW_PATH_CORRECTION_CONDITION_SELECT, 16, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxxx1", AUD_GPA_HW_PROP_WB_CALL,    /* 0x1, */ "WB Call")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxx1x", AUD_GPA_HW_PROP_PHAP,       /* 0x2, */ "PHAP")
        BIT_TBL_ENTRY("xxxxxxxxxxxxx1xx", AUD_GPA_HW_PROP_SLIDE_OPEN, /* 0x4, */ "Slide Open")
    BIT_TBL_END
    
    /* Subblock Definitions */
   
    SB_BEGIN(AUD_GPA_AB_ACCESSORY_TYPE_SB, "", "")
        COMMON_SB_LONG
        
        VALUE_CONST(accessory_type, "Accessory Type", AUD_GPA_ACCESSORY_TYPE_SELECT)
        
        FILLER(FILLER_FIXED, 24)
    SB_END
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_ROUTINGS_SB, "", "")
        COMMON_SB_LONG    
    
        VALUE_CONST(speech_routing, "Speech Routing", AUD_GPA_ROUTING_SELECT)
        
        VALUE_CONST(music_routing, "Music Routing", AUD_GPA_ROUTING_SELECT)
        
        FILLER(FILLER_FIXED, 16)
    SB_END
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_SPEAKERS_SB, "", "")
        COMMON_SB_LONG
        
        VALUE_EX(16, BE, input_impedance, "Input Impedance", DEC, 1.0, 0.0, "ohms")

        VALUE_EX(16, BE, distance_between_loudspeakers, "Distance Between Loudspeakers", DEC, 1.0, 0.0, "cm")
     SB_END
     
    SB_BEGIN(AUD_GPA_AB_UPLINK_SENSITIVITY_SB, "", "")
        COMMON_SB_LONG

        VALUE_EX(-16, BE, sensitivity, "Sensitivity", DEC, 0.01, 0.0, "dBV/Pa")
        
        FILLER(FILLER_FIXED, 16)
    SB_END
    
    SB_BEGIN(AUD_GPA_AB_UPLINK_FILTER_SB, "", "")
        COMMON_SB_LONG
        
        COMMENT(COMMENT_TEXT, "Low frequency filter center frequency")
        VALUE_EX(16, BE, low_freq, "Low Freq", DEC, 1.0, 0.0, "Hz")
        COMMENT(COMMENT_TEXT, "Low frequency filter gain")
        VALUE_EX(-16, BE, low_gain, "Low Gain", DEC, 0.01, 0.0, "dB")
        COMMENT(COMMENT_TEXT, "Low frequency filter Bandwidth")
        VALUE_EX(16, BE, low_bandwidth, "Low Bandwidth", DEC, 0.01, 0.0, "oct")
        
        COMMENT(COMMENT_TEXT, "Mid frequency filter center frequency")
        VALUE_EX(16, BE, mid_freq, "Mid Freq", DEC, 1.0, 0.0, "Hz")
        COMMENT(COMMENT_TEXT, "Mid frequency filter gain")
        VALUE_EX(-16, BE, mid_gain, "Mid Gain", DEC, 0.01, 0.0, "dB")
        COMMENT(COMMENT_TEXT, "Mid frequency filter Bandwidth")
        VALUE_EX(16, BE, mid_bandwidth, "Mid Bandwidth", DEC, 0.01, 0.0, "oct")
        
        COMMENT(COMMENT_TEXT, "Hi frequency filter center frequency")
        VALUE_EX(16, BE, hi_freq, "Hi Freq", DEC, 1.0, 0.0, "Hz")
        COMMENT(COMMENT_TEXT, "Hi frequency filter gain")
        VALUE_EX(-16, BE, hi_gain, "Hi Gain", DEC, 0.01, 0.0, "dB")
        COMMENT(COMMENT_TEXT, "Hi frequency filter Bandwidth")
        VALUE_EX(16, BE, hi_bandwidth, "Hi Bandwidth", DEC, 0.01, 0.0, "oct")
        
        FILLER(FILLER_FIXED, 16)
    SB_END

    SB_BEGIN(AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB, "", "")
        COMMON_SB_LONG
        
        VALUE_CONST(inbuilt, "Inbuilt", YES_NO)
        
        FILLER(FILLER_FIXED, 24)
    SB_END 
 
    SB_BEGIN(AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(inbuilt, "Inbuilt", YES_NO)
        
        FILLER(FILLER_FIXED, 24)
    SB_END 
    
    SB_BEGIN(AUD_GPA_AB_ACOUSTIC_ECHO_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(inbuilt, "Inbuilt", YES_NO)        
        FILLER(FILLER_FIXED, 8)
 
        VALUE_EX(-16, BE, maximum_echo_gain, "Maximum Echo Gain", DEC, 0.01, 0.0, "dB")
 
        COMMENT(COMMENT_TEXT, "Minimum pure delay represented in 8kHz samples.")
        VALUE_EX(16, BE, minimum_pure_delay, "Minimum Pure Delay", DEC, 1.0, 0.0, "samples")
        
        FILLER(FILLER_FIXED, 16)
    SB_END     
 
    SB_BEGIN(AUD_GPA_AB_SIDETONE_SB, "", "")
        COMMON_SB_LONG

        VALUE_EX(-16, BE, offset, "Offset", DEC, 0.01, 0.0, "dB")
        
        FILLER(FILLER_FIXED, 16)
    SB_END 
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB, "", "")
        COMMON_SB_LONG

        VALUE_EX(-16, BE, sensitivity, "Sensitivity", DEC, 0.01, 0.0, "dBPa/V")
        
        FILLER(FILLER_FIXED, 16)
    SB_END
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB, "", "")
        COMMON_SB_LONG
 
        VALUE_EX(16, BE, highpass_filter_frequency, "Highpass Filter Frequency", DEC, 1.0, 0.0, "Hz")
        
        FILLER(FILLER_FIXED, 16)
     SB_END
     
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_FILTER_SB, "", "")
        COMMON_SB_LONG
        
        COMMENT(COMMENT_TEXT, "Low frequency filter center frequency")
        VALUE_EX(16, BE, low_freq, "Low Freq", DEC, 1.0, 0.0, "Hz")
        COMMENT(COMMENT_TEXT, "Low frequency filter gain")
        VALUE_EX(-16, BE, low_gain, "Low Gain", DEC, 0.01, 0.0, "dB")
        COMMENT(COMMENT_TEXT, "Low frequency filter Bandwidth")
        VALUE_EX(16, BE, low_bandwidth, "Low Bandwidth", DEC, 0.01, 0.0, "oct")
        
        COMMENT(COMMENT_TEXT, "Low-Mid frequency filter center frequency")
        VALUE_EX(16, BE, low_mid_freq, "Low Mid Freq", DEC, 1.0, 0.0, "Hz")
        COMMENT(COMMENT_TEXT, "Low Mid frequency filter gain")
        VALUE_EX(-16, BE, low_mid_gain, "Low Mid Gain", DEC, 0.01, 0.0, "dB")
        COMMENT(COMMENT_TEXT, "Low Mid frequency filter Bandwidth")
        VALUE_EX(16, BE, low_mid_bandwidth, "Low Mid Bandwidth", DEC, 0.01, 0.0, "oct")
        
        COMMENT(COMMENT_TEXT, "Mid-Hi frequency filter center frequency")
        VALUE_EX(16, BE, mid_hi_freq, "Mid Hi Freq", DEC, 1.0, 0.0, "Hz")
        COMMENT(COMMENT_TEXT, "Mid-Hi frequency filter gain")
        VALUE_EX(-16, BE, mid_hi_gain, "Mid Hi Gain", DEC, 0.01, 0.0, "dB")
        COMMENT(COMMENT_TEXT, "Mid-Hi frequency filter Bandwidth")
        VALUE_EX(16, BE, mid_hi_bandwidth, "Mid Hi Bandwidth", DEC, 0.01, 0.0, "oct")
        
        COMMENT(COMMENT_TEXT, "Hi frequency filter center frequency")
        VALUE_EX(16, BE, hi_freq, "Hi Freq", DEC, 1.0, 0.0, "Hz")
        COMMENT(COMMENT_TEXT, "Hi frequency filter gain")
        VALUE_EX(-16, BE, hi_gain, "Hi Gain", DEC, 0.01, 0.0, "dB")
        COMMENT(COMMENT_TEXT, "Hi frequency filter Bandwidth")
        VALUE_EX(16, BE, hi_bandwidth, "Hi Bandwidth", DEC, 0.01, 0.0, "oct")
        
        COMMENT(COMMENT_TEXT, "Hi shelf filter center frequency")
        VALUE_EX(16, BE, hi_shelf_freq, "Hi Shelf Freq", DEC, 1.0, 0.0, "Hz")
        COMMENT(COMMENT_TEXT, "Hi shelf filter gain")
        VALUE_EX(-16, BE, hi_shelf_gain, "Hi Shelf Gain", DEC, 0.01, 0.0, "dB")
        
     SB_END
     
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB, "", "")
        COMMON_SB_LONG

        VALUE_EX(-16, BE, safety_limit, "Safety Limit", DEC, 0.01, 0.0, "dBV")
        
        FILLER(FILLER_FIXED, 16)
    SB_END
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_DRC_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(inbuilt, "Inbuilt", YES_NO)
        
        FILLER(FILLER_FIXED, 24)        
    SB_END     
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(inbuilt, "Inbuilt", YES_NO)
        
        FILLER(FILLER_FIXED, 24)
    SB_END         

    SB_BEGIN(AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(inbuilt, "Inbuilt", YES_NO)
        
        FILLER(FILLER_FIXED, 24)        
    SB_END         
    
    /* - - - Extension - - - */
    
    SB_BEGIN(AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(uplink_available, "Uplink Available", YES_NO)
        
        FILLER(FILLER_FIXED, 24)
    SB_END         
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB, "", "")
        COMMON_SB_LONG
    
        VALUE_CONST(user_volume_in_phone, "User Volume In Phone", YES_NO)
        FILLER(FILLER_FIXED, 8)
    
        VALUE_CONST(volume_control_type, "Volume Control Type", AUD_GPA_VOLUME_CONTROL_SELECT)
        FILLER(FILLER_FIXED, 8)
    SB_END

    SB_BEGIN(AUD_GPA_AB_AEC_SB, "", "")
        COMMON_SB_LONG
        
        COMMENT(COMMENT_PARAGRAPH, "Minimum filter length represented in 8kHz samples.")
        VALUE_EX(16, BE, minimum_filter_length, "Minimum Filter Length", DEC, 1.0, 0.0, "samples")
        
        COMMENT(COMMENT_TEXT, "Need of terminal AEC attenuators.")
        VALUE_CONST(need_aec_attenuators, "Need Aec Attenuators", YES_NO)
        
        COMMENT(COMMENT_TEXT, "Defines how quickly the echo path is assumed to change in real usage. "
         "Slow choice should be used when mic and loudspeaker have constant distance compared to each other.")
        VALUE_CONST(SlowEchoRateOfChange, "Slow Echo Rate Of Change", YES_NO)        
    SB_END
    
    SB_BEGIN(AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(inbuilt_wind_noise_reduction, "Inbuilt Wind Noise Reduction", YES_NO)
        FILLER(FILLER_FIXED, 8)
        
        VALUE_EX(-16, BE, ambient_noise_reduction, "Ambient Noise Reduction", DEC, 0.01, 0.0, "dB")
    SB_END    
    
    SB_BEGIN(AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB, "", "")
        COMMON_SB_LONG
        
        VALUE_EX(32, BE, low_freq_limit, "Low Freq Limit", DEC, 1.0, 0.0, "Hz")
      
        VALUE_EX(32, BE, hi_freq_limit, "Hi Freq Limit", DEC, 0.01, 0.0, "Hz")
    SB_END    
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(prefer_normalized_levels, "Prefer Normalized Levels", YES_NO)
        
        FILLER(FILLER_FIXED, 24)
    SB_END    
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB, "", "")
        COMMON_SB_LONG

        VALUE_CONST(inbuilt, "Inbuilt", YES_NO)
        
        FILLER(FILLER_FIXED, 24)
    SB_END      

    SB_BEGIN(AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB, "", "")
        COMMON_SB_LONG

        VALUE_EX(-16, BE, voltage_limit, "Voltage Limit", DEC, 0.01, 0.0, "dBV")
        
        FILLER(FILLER_FIXED, 16)
    SB_END
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_QUALITY_SB, "", "")
        COMMON_SB_LONG
    
        VALUE_CONST(quality, "Quality", AUD_GPA_QUALITY_SELECT)
        
        FILLER(FILLER_FIXED, 24)
    SB_END    
    
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB, "", "")
        COMMON_SB_LONG
        
        VALUE_EX(32, BE, hi_freq_limit, "Hi Freq Limit", DEC, 1.0, 0.0, "Hz")
    SB_END         
 
#define AUD_GPA_MAX_DRC_BANDS 5

    SEQ_BEGIN(AUD_GPA_FREQ_LIMIT_SEQ, DONT_CREATE_STRUCT, "", "")
        VALUE_EX(16, BE, freq_limit, "Freq Limit", DEC, 1.0, 0.0, "Hz")
    SEQ_END
    
    SEQ_BEGIN(AUD_GPA_PEAK_LIMIT_SEQ, DONT_CREATE_STRUCT, "", "")
        VALUE_EX(-16, BE, peak_limit, "Peak Limit", DEC, 0.01, 0.0, "dBVp-p")
    SEQ_END    
 
    SB_BEGIN(AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB, "", "")
        COMMON_SB_LONG
        
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, AUD_GPA_MAX_DRC_BANDS)
        VALUE(8, BE, band_count, "Band Count",DEC)
        FILLER(FILLER_FIXED, 8)
        
        SEQ_OF(freq_limit, "Freq Limit", AUD_GPA_FREQ_LIMIT_SEQ, AUD_GPA_MAX_DRC_BANDS + 1)
            
        SEQ_OF(peak_limit, "Peak Limit", AUD_GPA_PEAK_LIMIT_SEQ, AUD_GPA_MAX_DRC_BANDS)
    SB_END 

    SB_BEGIN(AUD_GPA_AB_DOWNLINK_XPROT_SB, "", "")
        COMMON_SB_LONG
        
        VALUE_CONST(activate, "Activate", YES_NO)
        
        COMMENT(COMMENT_TEXT, "Is transducer encosure design closed (otherwise it is reflex)?")
        VALUE_CONST(is_closed, "Is Closed", YES_NO)
        
        VALUE_EX(-16, BE, resonance_frequency_offset, "Resonance Frequency Offset", DEC, 0.01, 0.0, "oct")
        VALUE_EX(16, BE, q_value, "Q Value", DEC, 0.01, 0.0, "")
        VALUE_EX(16, BE, MaxDispTimesMassPerBiFactor, "MaxDispTimesMassPerBiFactor", DEC, 0.000000001, 0.0, "")
        VALUE_EX(-16, BE, TargetFreqOffset, "TargetFreqOffset", DEC, 0.01, 0.0, "oct")
        VALUE_EX(16, BE, ThermalResistanceOfVoiceCoil, "ThermalResistanceOfVoiceCoil", DEC, 1.0, 0.0, "K/W")
        VALUE_EX(16, BE, TimeConstantOfVoiceCoil, "TimeConstantOfVoiceCoil", DEC, 0.01, 0.0, "s")
        VALUE_EX(16, BE, ThermalResistanceOfMagnet, "ThermalResistanceOfMagnet", DEC, 1.0, 0.0, "K/W")
        VALUE_EX(16, BE, TimeConstantOfMagnet, "TimeConstantOfMagnet", DEC, 1.0, 0.0, "s")
        VALUE_EX(16, BE, ThermalLimit, "ThermalLimit", DEC, 1.0, 0.0, "C")
        VALUE_EX(16, BE, AccessoryAmplification, "AccessoryAmplification", DEC, 0.01, 0.0, "dB")
        VALUE_EX(16, BE, ImpedanceOfDlTransducerAndWires, "ImpedanceOfDlTransducerAndWires", DEC, 1.0, 0.0, "ohm")
    SB_END 

    /* - - - TGPA Extension - - - */

    SB_BEGIN(AUD_GPA_AB_FM_RADIO_CORRECTION_SB, "", "")
        COMMON_SB_LONG

        VALUE_EX(-16, BE, offset, "Offset", DEC, 0.01, 0.0, "dB")
        
        FILLER(FILLER_FIXED, 16)
    SB_END 
    
    SB_BEGIN(AUD_GPA_AB_EQ_GAINS_SB, "", "")
        COMMON_SB_LONG
       
        VALUE_EX(-16, BE, speech_dl_g, "Speech Dl G", DEC, 0.01, 0.0, "dB")
        VALUE_EX(-16, BE, speech_ul_g, "Speech Ul G", DEC, 0.01, 0.0, "dB")

        VALUE_EX(-16, BE, wb_speech_dl_g, "Wb Speech Dl G", DEC, 0.01, 0.0, "dB")
        VALUE_EX(-16, BE, wb_speech_ul_g, "Wb Speech Ul G", DEC, 0.01, 0.0, "dB")        

        VALUE_EX(-16, BE, audio_dl_g, "Audio Dl G", DEC, 0.01, 0.0, "dB")
        VALUE_EX(-16, BE, audio_ul_g, "Audio Ul G", DEC, 0.01, 0.0, "dB")        
    SB_END    
    
    SB_BEGIN(AUD_GPA_AB_EQ_GAIN_VALUE_SB, "", "")
        COMMON_SB_LONG
       
        VALUE_CONST(equalizer, "Equalizer", AUD_GPA_EQ_SELECT)
        VALUE_CONST(direction, "Direction", AUD_GPA_DL_UL_SELECT)

        VALUE_EX(-16, BE, gain, "Gain", DEC, 0.01, 0.0, "dB")

    SB_END    
    
    /* - - - Macro containing all audio block sub-blocks - - - */
    #define AUD_GPA_AB_SB_LIST \
      SB_LST_ENTRY_VER(AUD_GPA_AB_ACCESSORY_TYPE_SB,                     "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_ROUTINGS_SB,                  "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_SPEAKERS_SB,                  "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_UPLINK_SENSITIVITY_SB,                 "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_UPLINK_FILTER_SB,                      "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_UPLINK_ADAPTIVE_LEVELING_SB,           "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_UPLINK_NOISE_SUPPRESSOR_SB,            "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_ACOUSTIC_ECHO_SB,                      "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_SIDETONE_SB,                           "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB,               "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_HIGHPASS_FILTER_FREQ_SB,      "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_FILTER_SB,                    "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_SAFETY_LIMITATION_SB,         "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_DRC_SB,                       "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_NOISE_DEPENDENT_GAINING_SB,   "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_HI_FREQ_COMPENSATION_SB,      "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_UPLINK_FOR_SPEECH_CALL_SB,             "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_VOLUME_CONTROL_SB,            "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_AEC_SB,                                "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_UPLINK_NOISE_REDUCTION_SB,             "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_UPLINK_USABLE_FREQ_RANGE_SB,           "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_LEVEL_NORMALIZATION_SB,       "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_NOISE_SUPPRESSOR_SB,          "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_LONG_TIME_VOLTAGE_LIMIT_SB,   "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_QUALITY_SB,                   "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_USABLE_FREQ_RANGE_SB,         "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_DRC_LIMITS_SB,                "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_XPROT_SB,                     "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_FM_RADIO_CORRECTION_SB,                "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_EQ_GAINS_SB,                           "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_EQ_GAIN_VALUE_SB,                      "001.000", "")
      
    /* - - - Macro containing audio block sub-blocks as param - - - */      
    #define AUD_GPA_AB_SBS_PARAMS \
      PROPERTY(PROPERTY_PMD_PARAMETER) \
      REFERENCE(16, BE, num_sb, "Number of sub blocks to follow", N) \
      SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sb_list, "Sub blocks", N, \
                       ISIHDR_DONT_GENERATE) \
        AUD_GPA_AB_SB_LIST \
      SB_LST_REF_END
      
    /* - - - Macro containing audio block sub-block ids as param - - - */            
    #define AUD_GPA_AB_SB_IDS_PARAMS \
      PROPERTY(PROPERTY_PMD_PARAMETER) \
      REFERENCE(16, BE, num_sb_id, "Number of sub block IDs to follow", N) \
      SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, sb_id_list, "Sub block IDs", N, \
                       ISIHDR_DONT_GENERATE) \
        AUD_GPA_AB_SB_LIST \
      SB_LST_REF_END      

    /* - - - Macro for selecting audio block using hw path and sub path params - - - */
    #define AUD_GPA_AB_SELECT_PARAMS \
      PROPERTY(PROPERTY_PMD_PARAMETER) \
      REFERENCE_CONST(hw_path, "HW Path", HW_PATH_SELECT, AUD_GPA_HW_PATH_SELECT) \
      \
      CHOICE_BEGIN(hw_path_subtype, "HW Path Subtype", HW_PATH_SELECT) \
          CASE_BEGIN(AUD_GPA_HW_PATH_AV, "", "") \
              PROPERTY(PROPERTY_PMD_PARAMETER) \
              VALUE_CONST(hw_path_subtype, "Subtype for AV path", AUD_GPA_HW_PATH_AV_SUBTYPE_SELECT) \
          CASE_END \
          DEFAULT_BEGIN("", "") \
              FILLER_EX(hw_path_subtype, 16, 1)  \
          DEFAULT_END \
      CHOICE_END
      
    /* - - - Macro containing all audio block correction sub-blocks - - - */
    #define AUD_GPA_AB_CORRECTION_SB_LIST \
      SB_LST_ENTRY_VER(AUD_GPA_AB_UPLINK_SENSITIVITY_SB,                 "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_SIDETONE_SB,                           "001.000", "") \
      SB_LST_ENTRY_VER(AUD_GPA_AB_DOWNLINK_SENSITIVITY_SB,               "001.000", "")
        
    /* - - - Macro containing audio block correction sub-blocks as param - - - */              
    #define AUD_GPA_AB_CORRECTION_SBS_PARAMS \
      PROPERTY(PROPERTY_PMD_PARAMETER) \
      REFERENCE(16, BE, num_sb, "Number of sub blocks to follow", N) \
      SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sb_list, "Sub blocks", N, \
                       ISIHDR_DONT_GENERATE) \
          AUD_GPA_AB_CORRECTION_SB_LIST \
      SB_LST_REF_END
        
    /* - - - Macro containing audio block correction sub-block ids as param - - - */            
    #define AUD_GPA_AB_CORRECTION_SB_IDS_PARAMS \
      PROPERTY(PROPERTY_PMD_PARAMETER) \
      REFERENCE(16, BE, num_sb_id, "Number of sub block IDs to follow", N) \
      SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, sb_id_list, "Sub block IDs", N, \
                       ISIHDR_DONT_GENERATE) \
        AUD_GPA_AB_CORRECTION_SB_LIST \
      SB_LST_REF_END      

    /* - - - Macro for selecting audio block correction using hw path and condition params - - - */
    #define AUD_GPA_AB_CORRECTION_SELECT_PARAMS \
      PROPERTY(PROPERTY_PMD_PARAMETER) \
      VALUE_CONST(hw_paths, "HW Paths", AUG_GPA_HW_PATH_MULTI_SELECT) \
      PROPERTY(PROPERTY_PMD_PARAMETER) \
      VALUE_CONST(condition, "Condition", AUG_GPA_HW_PATH_CORRECTION_CONDITION_SELECT)          
   
    /* GPA Message descriptions */
    
    /* ---------------------------------------------------------------- */
    /* AUD_GPA_AB_WRITE_REQ, AUD_GPA_AB_WRITE_RESP    */
    /* ---------------------------------------------------------------- */
    
  COMMENT(COMMENT_PARAGRAPH,
          "This message is used for writing audio block data.")
  MSG_BEGIN(AUD_GPA_AB_WRITE_REQ, MESSAGE_REQ, "001.000", "")
    COMMON_MSG_HDR

    AUD_GPA_AB_SELECT_PARAMS
    AUD_GPA_AB_SBS_PARAMS
  MSG_END

  COMMENT(COMMENT_PARAGRAPH,
          "This message returns either 0 (= OK) or the sub block IDs "
          "that failed or were not recognized.")
  MSG_BEGIN(AUD_GPA_AB_WRITE_RESP, MESSAGE_RESP, "001.000", "")
    COMMON_MSG_HDR
    
    AUD_GPA_AB_SB_IDS_PARAMS
  MSG_END
  
  MSG_PAIR(AUD_GPA_AB_WRITE_REQ, AUD_GPA_AB_WRITE_RESP)
  
  COMMENT(COMMENT_PARAGRAPH,
          "This message is used for reading audio block data.")
  MSG_BEGIN(AUD_GPA_AB_READ_REQ, MESSAGE_REQ, "001.000", "")
    COMMON_MSG_HDR

    AUD_GPA_AB_SELECT_PARAMS
    AUD_GPA_AB_SB_IDS_PARAMS    
  MSG_END

  COMMENT(COMMENT_PARAGRAPH,
          "This message returns audio block data for supported sub block IDs.")
  MSG_BEGIN(AUD_GPA_AB_READ_RESP, MESSAGE_RESP, "001.000", "")
    COMMON_MSG_HDR
    
    AUD_GPA_AB_SBS_PARAMS
  MSG_END
  
  MSG_PAIR(AUD_GPA_AB_READ_REQ, AUD_GPA_AB_READ_RESP)  
  
  MSG_BEGIN(AUD_GPA_CURRENT_HW_PATH_IND, MESSAGE_IND, "001.000", "")
    COMMON_MSG_HDR
        
    PROPERTY(PROPERTY_PMD_PARAMETER)
    VALUE_CONST(pri_hw_path, "Pri HW Path", AUD_GPA_HW_PATH_SELECT)
    
    PROPERTY(PROPERTY_PMD_PARAMETER)
    VALUE_CONST(mic_hw_path, "Mic HW Path", AUD_GPA_HW_PATH_SELECT)
    
    PROPERTY(PROPERTY_PMD_PARAMETER)
    VALUE_CONST(sec_hw_path, "Sec HW Path", AUD_GPA_HW_PATH_SELECT)        
    
    PROPERTY(PROPERTY_PMD_PARAMETER)
    VALUE_CONST(hw_path_av_subtype, "Subtype for AV path", AUD_GPA_HW_PATH_AV_SUBTYPE_SELECT)

  MSG_END
  
  COMMENT(COMMENT_PARAGRAPH,
          "This message is used for writing audio block correction data.")
  MSG_BEGIN(AUD_GPA_AB_CORRECTION_WRITE_REQ, MESSAGE_REQ, "001.000", "")
    COMMON_MSG_HDR

    AUD_GPA_AB_CORRECTION_SELECT_PARAMS
    AUD_GPA_AB_CORRECTION_SBS_PARAMS
  MSG_END
  
  COMMENT(COMMENT_PARAGRAPH,
          "This message returns either 0 (= OK) or the sub block IDs "
          "that failed or were not recognized.")
  MSG_BEGIN(AUD_GPA_AB_CORRECTION_WRITE_RESP, MESSAGE_RESP, "001.000", "")
    COMMON_MSG_HDR

    AUD_GPA_AB_CORRECTION_SB_IDS_PARAMS
  MSG_END  
  
  MSG_PAIR(AUD_GPA_AB_CORRECTION_WRITE_REQ, AUD_GPA_AB_CORRECTION_WRITE_RESP)    
  
  COMMENT(COMMENT_PARAGRAPH,
          "This message is used for reading audio block correction data.")
  MSG_BEGIN(AUD_GPA_AB_CORRECTION_READ_REQ, MESSAGE_REQ, "001.000", "")
    COMMON_MSG_HDR

    AUD_GPA_AB_CORRECTION_SELECT_PARAMS
    AUD_GPA_AB_CORRECTION_SB_IDS_PARAMS
  MSG_END
  
  COMMENT(COMMENT_PARAGRAPH,
          "This message returns audio block correction data for supported sub block IDs.")
  MSG_BEGIN(AUD_GPA_AB_CORRECTION_READ_RESP, MESSAGE_RESP, "001.000", "")
    COMMON_MSG_HDR

    AUD_GPA_AB_CORRECTION_SBS_PARAMS
  MSG_END  
  
  MSG_PAIR(AUD_GPA_AB_CORRECTION_READ_REQ, AUD_GPA_AB_CORRECTION_READ_RESP)

  COMMENT(COMMENT_PARAGRAPH,
          "This message is used for locking audio block for av output.")
  MSG_BEGIN(AUD_GPA_AB_AV_LOCK_REQ, MESSAGE_REQ, "001.000", "")
    COMMON_MSG_HDR

    PROPERTY(PROPERTY_PMD_PARAMETER)
    VALUE_CONST(hw_path_av_subtype, "Subtype for AV path", AUD_GPA_HW_PATH_AV_SUBTYPE_SELECT)

  MSG_END
  
  MSG_BEGIN(AUD_GPA_AB_AV_LOCK_RESP, MESSAGE_RESP, "001.000", "")
    COMMON_MSG_HDR
    
  MSG_END  
  
  MSG_PAIR(AUD_GPA_AB_AV_LOCK_REQ, AUD_GPA_AB_AV_LOCK_RESP)
  
  COMMENT(COMMENT_PARAGRAPH,
          "This message is used for unlocking audio block for av output.")
  MSG_BEGIN(AUD_GPA_AB_AV_UNLOCK_REQ, MESSAGE_REQ, "001.000", "")
    COMMON_MSG_HDR

  MSG_END
  
  MSG_BEGIN(AUD_GPA_AB_AV_UNLOCK_RESP, MESSAGE_RESP, "001.000", "")
    COMMON_MSG_HDR
    
  MSG_END  
  
  MSG_PAIR(AUD_GPA_AB_AV_UNLOCK_REQ, AUD_GPA_AB_AV_UNLOCK_RESP)
    
RES_END

/* End of file aud_gpa_isi_m.h */
