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

%name:              aud_eap_isi_m.h %

%version:           001.001 %

%cvtype:            incl %

%instance:          ou1core_1 %


Copyright(c)Nokia


Change history:

VERSION     : 001.001 NONDRAFT  18-Nov-2010 Ari Hyväri
REASON      : Change Request: Audio EAP ISI interface changes for pocket band
REFERENCE   : SWAM CR: JV10102934365
DESCRIPTION : option to select capture source in CAPTURE_REQ_SB

VERSION     : 001.000 NONDRAFT  24-Jan-2006 Janne Vimpari
REASON      : Change request
REFERENCE   : SWAM CR: JV08011556803
DESCRIPTION : EAP ISI messages separated from AUDIO ISI messages

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

/* EAP message Id's */
#define AUD_EAP_STREAM_REQ                        0x80
#define AUD_EAP_STREAM_RESP                       0x81
#define AUD_EAP_BUFFER_CLIENT_NTF                 0x82
#define AUD_EAP_BUFFER_SERVER_NTF                 0x83
#define AUD_EAP_BUFFER_OVERFLOW_NTF               0x84
#define AUD_EAP_EFFECT_CREATE_REQ                 0x85
#define AUD_EAP_EFFECT_CREATE_RESP                0x86
#define AUD_EAP_EFFECT_DESTROY_REQ                0x87
#define AUD_EAP_EFFECT_DESTROY_RESP               0x88
#define AUD_EAP_BUFFER_EMPTY_NTF                  0x89
#define AUD_EAP_EFFECT_INFO_REQ                   0x8A
#define AUD_EAP_EFFECT_INFO_RESP                  0x8B
#define AUD_EAP_EFFECT_ADJUST_REQ                 0x8C
#define AUD_EAP_EFFECT_ADJUST_RESP                0x8D
#define AUD_EAP_VISUALIZATION_DATA_NTF            0x8E
#define AUD_EAP_DATA_TRACING_REQ                  0x8F
#define AUD_EAP_DATA_TRACING_RESP                 0x90
#define AUD_EAP_TUNING_PARAM_READ_REQ							0x91
#define AUD_EAP_TUNING_PARAM_READ_RESP						0x92
#define AUD_EAP_TUNING_PARAM_WRITE_REQ						0x93
#define AUD_EAP_TUNING_PARAM_WRITE_RESP						0x94
#define AUD_EAP_TUNING_PARAM_LOCK_REQ							0x95
#define AUD_EAP_TUNING_PARAM_LOCK_RESP						0x96
#define AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ				0x97
#define AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP			0x98
#define AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ			0x99
#define AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP			0x9A

/* EAP stream command Id's */
#define AUD_EAP_STREAM_OPEN_REQ_SB          0x00
#define AUD_EAP_STREAM_PLAY_REQ_SB          0x01
#define AUD_EAP_STREAM_CLOSE_REQ_SB         0x02
#define AUD_EAP_STREAM_OPEN_RESP_SB         0x03
#define AUD_EAP_STREAM_PLAY_RESP_SB         0x04
#define AUD_EAP_STREAM_CLOSE_RESP_SB        0x05
#define AUD_EAP_STREAM_CAPTURE_REQ_SB       0x06
#define AUD_EAP_STREAM_CAPTURE_RESP_SB      0x07
#define AUD_EAP_STREAM_TIME_REQ_SB          0x08
#define AUD_EAP_STREAM_TIME_RESP_SB         0x09
#define AUD_EAP_STREAM_PAUSE_REQ_SB         0x0A
#define AUD_EAP_STREAM_PAUSE_RESP_SB        0x0B

/* EAP effect command Id's */
#define AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB       0x00
#define AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB      0x01
#define AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB      0x02
#define AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB     0x03
#define AUD_EAP_CREATE_RATECONTROL_REQ_SB           0x04
#define AUD_EAP_DESTROY_RATECONTROL_REQ_SB          0x05
#define AUD_EAP_CREATE_RATECONTROL_RESP_SB          0x06
#define AUD_EAP_DESTROY_RATECONTROL_RESP_SB         0x07
#define AUD_EAP_CREATE_LEVELCHANGE_REQ_SB           0x08
#define AUD_EAP_CREATE_LEVELCHANGE_RESP_SB          0x09
#define AUD_EAP_CREATE_PANCHANGE_REQ_SB             0x0A
#define AUD_EAP_CREATE_PANCHANGE_RESP_SB            0x0B

#define AUD_EAP_EFFECT_3D_LISTENER_REQ_SB           0x0C
#define AUD_EAP_EFFECT_3D_SOURCE_REQ_SB             0x0D
#define AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB        0x0E
#define AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB          0x0F
#define AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB      0x10
#define AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB      0x11
#define AUD_EAP_EFFECT_3D_COMMIT_REQ_SB             0x12

#define AUD_EAP_EFFECT_3D_LISTENER_RESP_SB          0x13
#define AUD_EAP_EFFECT_3D_SOURCE_RESP_SB            0x14
#define AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB       0x15
#define AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB         0x16
#define AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB     0x17
#define AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB     0x18
#define AUD_EAP_EFFECT_3D_COMMIT_RESP_SB            0x19

#define AUD_EAP_DESTROY_3D_LISTENER_REQ_SB          0x1A
#define AUD_EAP_DESTROY_3D_SOURCE_REQ_SB            0x1B
#define AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB       0x1C
#define AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB         0x1D
#define AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB     0x1E
#define AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB     0x1F

#define AUD_EAP_DESTROY_3D_LISTENER_RESP_SB         0x20
#define AUD_EAP_DESTROY_3D_SOURCE_RESP_SB           0x21
#define AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB      0x22
#define AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB        0x23
#define AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB    0x24
#define AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB    0x25

#define AUD_EAP_EFFECT_VISUALIZATION_REQ_SB         0x26
#define AUD_EAP_DESTROY_VISUALIZATION_REQ_SB        0x27
#define AUD_EAP_EFFECT_VISUALIZATION_RESP_SB        0x28
#define AUD_EAP_DESTROY_VISUALIZATION_RESP_SB       0x29

#define AUD_EAP_EFFECT_VSURROUND_REQ_SB             0x2A
#define AUD_EAP_DESTROY_VSURROUND_REQ_SB            0x2B
#define AUD_EAP_EFFECT_VSURROUND_RESP_SB            0x2C

/* subblock's for EFFECT_INFO */
#define AUD_EAP_INFO_RATECONTROL_REQ_SB     0x00
#define AUD_EAP_INFO_RATECONTROL_RESP_SB    0x01
#define AUD_EAP_INFO_AVAILABILITY_REQ_SB    0x02
#define AUD_EAP_INFO_AVAILABILITY_RESP_SB   0x03
#define AUD_EAP_INFO_VISUALIZATION_REQ_SB   0x04
#define AUD_EAP_INFO_VISUALIZATION_RESP_SB  0x05

/* subblock's for visualization */
#define AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB   0x00
#define AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB   0x01

/* Audio Visualization data length constants */
#define AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN 512
#define AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN 256

/* Effect tuning IF constants */
#define AUD_EAP_EAP_MUMDRC_NUM_BANDS_MAX	3
#define AUD_EAP_EAP_MUMDRC_NUM_CURVE_POINTS	5
#define AUD_EAP_EAP_MUMDRC_NUM_VOLUMES_MAX	5


/* Macros */

/* This is used for old message where struc define is old */
#define AUD_EAP_COMMON_SB(struct_name) \
    MSG_COMMENT(COMMENT_STRUCT_NAME, #struct_name) \
    REFERENCE(8, BE, command, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, subblock_lenght, "Subblock length", SB_LENGTH) \

/* This is used for old message where struc define is old */
#define AUD_EAP_FIXED_COMMON_SB(struct_name) \
    MSG_COMMENT(COMMENT_STRUCT_NAME, #struct_name) \
    REFERENCE(8, BE, command, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, subblock_length, "Subblock length", SB_LENGTH) \

/* This is used for old message where struc define is old */
#define AUD_EAP_MSG_HDR(struct_name) \
    MSG_COMMENT(COMMENT_STRUCT_NAME, #struct_name) \
    VALUE(8, BE, transaction_id, "Transaction ID", DEC) \
    REFERENCE(8, BE, message_id, "Message ID", MSG_ID)


#ifndef AUD_EAP_ISI_VERSION
#define AUD_EAP_ISI_VERSION
#define AUD_EAP_ISI_VERSION_Z   1
#define AUD_EAP_ISI_VERSION_Y   2
#endif

/* version history and cover page information */
/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "OULU")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "MCU Audio")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Mika P. Kangas")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIAL")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "AUDIO SERVER / EAP AUDIO MODULE ISI MESSAGE DESCRIPTION")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_aud_eap_isi_m.html")
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
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "audio_eap_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "audio_eap_isi_16.h")

RES_BEGIN(RESOURCE_ISI_EXTENSION, PN_AUDIO, AUD_EAP, "EAP Module",
    RES_VERSION_STRING(AUD_EAP_ISI_VERSION_Z, AUD_EAP_ISI_VERSION_Y), TRUE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    /* TODO: Add version history block every time the interface is changed */

     /* Latest version */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change Request: Audio EAP ISI: Nokia Virtual Surround effect")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JV11030441438")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "04-Mar-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Janne Vimpari")
    COMMENT(COMMENT_TEXT, "Possibility to control Nokia Virtual Surround through EAP ISI interface")
    ISI_VERSION_HISTORY("001.002") 
     
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change Request: Audio EAP ISI interface changes for pocket band")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JV10102934365")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "1-Nov-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Ari Hyväri")
    COMMENT(COMMENT_TEXT, "Option to select capture source in STREAM_CAPTURE_REQ_SB")
    ISI_VERSION_HISTORY("001.001")

    /* older ones */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JV08011556803")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "24-Jan-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Janne Vimpari")
    COMMENT(COMMENT_TEXT, "EAP ISI messages and definitions separated from common audio. This file Created. ")
    ISI_VERSION_HISTORY("001.000")


    /* CONSTANT TABLES */

    CONST_TBL_BEGIN(AUD_EAP_STREAM_SAMPLERATE, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_5_5125KHZ,    0x00, "Samplerate 5.5125KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_8KHZ,         0x01, "Samplerate 8KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_11_025KHZ,    0x02, "Samplerate 11.025KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_12KHZ,        0x03, "Samplerate 12KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_16KHZ,        0x04, "Samplerate 16KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_22_05KHZ,     0x05, "Samplerate 22.05KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_24KHZ,        0x06, "Samplerate 24KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_32KHZ,        0x07, "Samplerate 32KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_44_1KHZ,      0x08, "Samplerate 44.1KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_48KHZ,        0x09, "Samplerate 48KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_64KHZ,        0x0A, "Samplerate 64KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_88_2KHZ,      0x0B, "Samplerate 88.2KHz")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_SAMPLERATE_96KHZ,        0x0C, "Samplerate 96KHz")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_BUFFER_OVERFLOW_REASON, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_BUFFER_OVERFLOW,        0x01, "Buffer overflow")
        CONST_TBL_ENTRY(AUD_EAP_BUFFER_OUT_OF_MEMORY,   0x02, "Buffer out of memory")
    CONST_TBL_END


    CONST_TBL_BEGIN(AUD_EAP_STREAM_CHANNELS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_CHANNEL_MONO,            0x01, "Mono")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_CHANNEL_STEREO,          0x02, "Stereo")
    CONST_TBL_END

    BIT_TBL_BEGIN(AUD_EAP_STREAM_BUFFER_FORMAT, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", AUD_EAP_STREAM_SAMPLE_INT16, "INT16")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", AUD_EAP_STREAM_SAMPLE_INT32, "INT32")
        COMMENT(COMMENT_TEXT, "INT8")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX11", AUD_EAP_STREAM_SAMPLE_INT8, "")
        BIT_TBL_ENTRY("XXXXXXXXXXX1XXXX", AUD_EAP_STREAM_SAMPLE_INTERLEAVED, "INTERLEAVED")
    BIT_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_STREAM_TYPE, 16, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_TYPE_AUDIO_PLAYBACK,     0x11, "Audio playback")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_TYPE_AUDIO_CAPTURE,      0x12, "Audio capture")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_TYPE_SPEECH_PLAYBACK,    0x21, "Speech playback")
        CONST_TBL_ENTRY(AUD_EAP_STREAM_TYPE_SPEECH_CAPTURE,     0x22, "Speech capture")
    CONST_TBL_END

    BIT_TBL_BEGIN(AUD_EAP_STREAM_FLAGS, 32, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", AUD_EAP_STREAM_FLAGS_NO, "no flags")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1", AUD_EAP_STREAM_FLAGS_STATIC, "static stream")
    BIT_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_STREAM_REASON, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_COMMAND_OK,                     0x00, "OK")
        CONST_TBL_ENTRY(AUD_EAP_COMMAND_FAIL,                   0x01, "FAIL")
        CONST_TBL_ENTRY(AUD_EAP_COMMAND_NOT_SUPPORTED,          0x02, "The feature (ie. effect) is not supported")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_PREDEFINED_STREAM_ID, 16, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_MASTER_STREAM_ID,    0xFF, "Master stream id")
        CONST_TBL_ENTRY(AUD_EAP_AUDIO_PLAYBACK_STREAM_ID,  0xFE, "")
        CONST_TBL_ENTRY(AUD_EAP_AUDIO_CAPTURE_STREAM_ID,  0xFD, "")
        CONST_TBL_ENTRY(AUD_EAP_SPEECH_PLAYBACK_STREAM_ID,  0xFC, "")
        CONST_TBL_ENTRY(AUD_EAP_SPEECH_CAPTURE_STREAM_ID,  0xFB, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_EFFECT_AVAILABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_2D_LEVEL_CONTROL,    0x01, "Volume level control")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_2D_PAN_CONTROL,  0x02, "Pan control")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_3D_LOCATION_CONTROL,  0x03, "3D location control")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_3D_OBSTRUCTION_CONTROL,  0x04, "3D obstruction control")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_3D_OCCLUSION_CONTROL,  0x05, "3D occlusion control")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_3D_DISTANCE_CONTROL,  0x06, "3D distance attenuation control")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_3D_REVERB_CONTROL,  0x07, "3D reverberation control")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_3D_COMMIT_CONTROL,  0x08, "3D commit control")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_OBSTRUCTION_PRESET, 16, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_NONE,    0x00, "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_WINDOW_SINGLE,  0x01, "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_WINDOW_DOUBLE,  0x02, "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_DOOR_THIN,  0x03, "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_DOOR_THICK,  0x04, "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_WALL_WOOD,  0x05, "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_WALL_BRICK,  0x06, "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_WALL_STONE,  0x07, "")
        CONST_TBL_ENTRY(AUD_EAP_OBSTRUCTION_PRESET_CURTAIN,  0x08, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_OCCLUSION_PRESET, 16, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_NONE,    0x00, "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_WINDOW_SINGLE,  0x01, "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_WINDOW_DOUBLE,  0x02, "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_DOOR_THIN,  0x03, "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_DOOR_THICK,  0x04, "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_WALL_WOOD,  0x05, "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_WALL_BRICK,  0x06, "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_WALL_STONE,  0x07, "")
        CONST_TBL_ENTRY(AUD_EAP_OCCLUSION_PRESET_CURTAIN,  0x08, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_REVERBERATION_PRESET, 16, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_NONE,    0x00, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_ALLEY,  0x01, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_ARENA,  0x02, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_AUDITORIUM,  0x03, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_BATHROOM,  0x04, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_CAVE,  0x05, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_HALLWAY,  0x06, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_HANGAR,  0x07, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_LIVINGROOM,  0x08, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_MOUNTAINS,  0x09, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_ROOM,  0x0A, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_UNDERWATER,  0x0B, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_SMALLROOM,  0x0C, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_MEDIUMROOM,  0x0D, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_LARGEROOM,  0x0E, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_LARGEHALL,  0x0F, "")
        CONST_TBL_ENTRY(AUD_EAP_REVERB_PRESET_PLATE,  0x10, "")
    CONST_TBL_END

    BIT_TBL_BEGIN(AUD_VISUALIZATION_OP_MODE, 2, BE, "", "")
        BIT_TBL_ENTRY("x1", AUD_EAP_FREQ_DATA_ENABLED, "Frequecy data sending enabled")
        BIT_TBL_ENTRY("1x", AUD_EAP_WAVE_DATA_ENABLED, "Waveform data sending enabled")
    BIT_TBL_END

    BIT_TBL_BEGIN(AUD_EAP_CHANNEL_IDENTIFICATION, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", AUD_EAP_CHANNEL_LEFT, "Channel left")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", AUD_EAP_CHANNEL_RIGHT, "Channel right")
    BIT_TBL_END

    /* ------------------------------------------------------------------ */
    /* EAP data tracing related symbols                        			      */
    /* ------------------------------------------------------------------ */

    BIT_TBL_BEGIN(AUD_EAP_DATA_TRACE_POINTS, 32, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", AUD_EAP_TRACE_POINT_NONE, "no trace points")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx1", AUD_EAP_TRACE_POINT_STREAM_INPUT, "trace stream input")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx1x", AUD_EAP_TRACE_POINT_SRC_OUTPUT, "trace SRC output")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx1xx", AUD_EAP_TRACE_POINT_MDAIF_WRITE, "trace data written to MDAIF")
        BIT_TBL_ENTRY("11111111111111111111111111111111", AUD_EAP_TRACE_POINT_ALL, "trace all points")
    BIT_TBL_END

    /* ------------------------------------------------------------------ */
    /* EAP effect tuning related symbols                       			      */
    /* ------------------------------------------------------------------ */

    SEQ_BEGIN(AUD_EAP_REAL32, DONT_CREATE_STRUCT, "", "")
    	VALUE(-32, BE, data, "Data", HEX)
  	SEQ_END

    CONST_TBL_BEGIN(AUD_EAP_EFFECT, 8, BE, "", "")
        COMMENT(COMMENT_PARAGRAPH,
                "Used as response status if the effect (instance) does not exist")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_ERROR, 	0x00, "")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_MUMDRC,    	0x01, "Music-MDRC")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_STW,       	0x02, "Stereo widening")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_POS3D,    		0x03, "Positional 3D audio")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_DOPPLER,   	0x04, "Doppler")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_REVERB,    	0x05, "Environmental reverb")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_GEQ,       	0x06, "Graphic EQ")
        CONST_TBL_ENTRY(AUD_EAP_EFFECT_STW_3D,	    0x07, "Stereo widening 3D")
    CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Tuning parameters for stereo widening (loudspeaker version only).")
    SEQ_BEGIN(AUD_EAP_TUNING_PARAM_STW, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_PARAGRAPH,
                "Crosstalk delay in microseconds. [IEEE 754]"
                 " In practice the range of this value is 4.1667-83.3333 when sampling"
                 " rate is 48000 Hz")
        VALUE(32, BE, delay, "Crosstalk delay", Q23)
        COMMENT(COMMENT_PARAGRAPH,
                "Crosstalk gain. Value range 0.0-0.7. [IEEE 754]")
        VALUE(32, BE, gain, "Crosstalk gain", Q23)
    SEQ_END

    DER_CONST_TBL_BEGIN(AUD_EAP_EFFECT_TUNING, AUD_EAP_EFFECT,
                        "", "")
        DER_CONST_TBL_ENTRY(AUD_EAP_EFFECT_MUMDRC)
        DER_CONST_TBL_ENTRY(AUD_EAP_EFFECT_STW)
    DER_CONST_TBL_END

     CONST_TBL_BEGIN(AUD_EAP_SWITCH, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_SWITCH_OFF,     0x00, "Off")
        CONST_TBL_ENTRY(AUD_EAP_SWITCH_ON,      0x01, "On")
        CONST_TBL_ENTRY(AUD_EAP_SWITCH_DEFAULT, 0x02, "Default setting")
    CONST_TBL_END


    DER_CONST_TBL_BEGIN(AUD_EAP_SWITCH_ONOFF, AUD_EAP_SWITCH,
                        "", "")
        DER_CONST_TBL_ENTRY(AUD_EAP_SWITCH_OFF)
        DER_CONST_TBL_ENTRY(AUD_EAP_SWITCH_ON)
    DER_CONST_TBL_END

    CONST_TBL_BEGIN(AUD_EAP_MUMDRC_SWITCH, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EAP_MUMDRC_OFF,     0, "Off")
        CONST_TBL_ENTRY(AUD_EAP_MUMDRC_ON,      1, "On")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_EAP_MUMDRC_ONOFF, AUD_EAP_MUMDRC_SWITCH,
                        "", "")
        DER_CONST_TBL_ENTRY(AUD_EAP_MUMDRC_OFF)
        DER_CONST_TBL_ENTRY(AUD_EAP_MUMDRC_ON)
    DER_CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Sets source of capturing. AUD_EAP_STREAM_CAPTURE_RECORDING is used when a client wants capture"
            "an existing recording stream, AUD_EAP_STREAM_CAPTURE_MICROPHONE is used when a client wants capture"
            "normally from the microphone or speech call, AUD_EAP_STREAM_CAPTURE_PLAYBACK is used when a client wants to capture"
            "currently playing playback stream(s). AUD_EAP_STREAM_CAPTURE_DEFAULT is here only to make this change"
            "backward compatible. Effectively it is the same as AUD_EAP_STREAM_CAPTURE_MICROPHONE functionality when"
            "a client has left the whole bitfield unfilled. Use case examples: when a client wants to capture for example"
            "streamed audio it sends AUD_EAP_STREAM_CAPTURE_PLAYBACK. When a client wants to capture a video phone call"
            "audio it sends AUD_EAP_STREAM_CAPTURE_RECORDING|AUD_EAP_STREAM_CAPTURE_PLAYBACK. EAP mixes"
            "both currently running streams and sends data to the client in started capture stream.")
    BIT_TBL_BEGIN(AUD_EAP_STREAM_CAPTURE_SOURCE, 16, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxxxx",AUD_EAP_STREAM_CAPTURE_DEFAULT,            "capture from default (ie. mic )")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxxx1",AUD_EAP_STREAM_CAPTURE_RECORDING,          "capture from existing recording stream")
        BIT_TBL_ENTRY("xxxxxxxxxxxxxx1x",AUD_EAP_STREAM_CAPTURE_MICROPHONE,         "capture from mdaif")
        BIT_TBL_ENTRY("xxxxxxxxxxxxx1xx",AUD_EAP_STREAM_CAPTURE_PLAYBACK,           "capture from existing playback stream")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Tuning parameters for Music-MDRC, volume specific.")
    SEQ_BEGIN(AUD_EAP_TUNING_PARAM_MUMDRC_VOLUME, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_PARAGRAPH,
                "Volume setting this compression curve applies to, in dB. "
                "[IEEE 754]")
		PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(32, BE, iVolume, "Volume setting", HEX)
        COMMENT(COMMENT_PARAGRAPH,
                "Limiting level for the compression curve, in dB. "
                "[IEEE 754]")
		PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(32, BE, iEqLimit, "Limiting level", HEX)
        COMMENT(COMMENT_PARAGRAPH,
                "Input level points of the compression curve, in dB. "
                "[IEEE 754]")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0xC2960000)
        SEQ_OF(iCompressionCurveInLevels, "Compression curve input levels",
               AUD_EAP_REAL32, AUD_EAP_EAP_MUMDRC_NUM_CURVE_POINTS)
        COMMENT(COMMENT_PARAGRAPH,
                "Output level points of the compression curve, in dB. "
                "[IEEE 754]")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0xC2960000)
        SEQ_OF(iCompressionCurveOutLevels, "Compression curve output levels",
               AUD_EAP_REAL32, AUD_EAP_EAP_MUMDRC_NUM_CURVE_POINTS)
    SEQ_END

    COMMENT(COMMENT_PARAGRAPH,
            "Tuning parameters for Music-MDRC, band specific.")
    SEQ_BEGIN(AUD_EAP_TUNING_PARAM_MUMDRC_BAND, CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE,
                       AUD_EAP_EAP_MUMDRC_NUM_BANDS_MAX - 1)
		PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(16, BE, iFrequencyBandNumber, "Band number", DEC)
        FILLER(FILLER_FIXED, 16)
        COMMENT(COMMENT_PARAGRAPH,
                "Attack time (ms) of the attack and release time filter. "
                "[IEEE 754]")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0x40600000)
        VALUE(32, BE, iAttackTime, "Attack time", HEX)
        COMMENT(COMMENT_PARAGRAPH,
                "Delay time (ms) of the attack and release time filter. "
                "[IEEE 754]")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0x43480000)
        VALUE(32, BE, iReleaseTime, "Release time", HEX)
        SEQ_OF_REF(volume_tunings, "Volume specific tunings",
                   AUD_EAP_TUNING_PARAM_MUMDRC_VOLUME, NUM_VOLUMES,
                   ISIHDR_POINTER)
    SEQ_END

    COMMENT(COMMENT_PARAGRAPH,
            "Tuning parameters for Music-MDRC, band/volume independent.")
    SEQ_BEGIN(AUD_EAP_TUNING_PARAM_MUMDRC, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_PARAGRAPH, "How many bands this set defines")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE,
                       AUD_EAP_EAP_MUMDRC_NUM_BANDS_MAX)
		PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        REFERENCE(16, BE, iNbrOfMuMdrcBands, "Number of DRC bands", NUM_BANDS)
        COMMENT(COMMENT_PARAGRAPH,
                "Number of volume dependent parameter sets for each band")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE,
                       AUD_EAP_EAP_MUMDRC_NUM_VOLUMES_MAX)
		PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        REFERENCE(16, BE, iNbrOfVolumeSets, "Number of volume sets", NUM_VOLUMES)
        COMMENT(COMMENT_PARAGRAPH,
                "Delay time (ms) of the attack and release time filter of "
                "the DRC. [IEEE 754]")
		PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0x40900000)
        VALUE(32, BE, iDelayTime, "Delay time", HEX)
        COMMENT(COMMENT_PARAGRAPH,
                "Linking between different channels in the MDRC configuration "
                "so that the band level estimates depend on each other. Value "
                "range 0.0-1.0. [IEEE 754]")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(32, BE, iCrossBandLink, "Crossband linking", HEX)
        COMMENT(COMMENT_PARAGRAPH,
                "Is MDRC used. 1 - MDRC in use. 0 - MDRC not in use.")
        VALUE_CONST(iUseMuMdrc, "MDRC in use", AUD_EAP_MUMDRC_ONOFF)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF_REF(band_tunings, "Band specific tunings",
                   AUD_EAP_TUNING_PARAM_MUMDRC_BAND, NUM_BANDS, ISIHDR_POINTER)
    SEQ_END

   SEQ_BEGIN(AUD_EAP_EFFECT_STATUS, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_PARAGRAPH,
                "ID of a specific component of the effect as defined in the "
                "audio routing network, used with stream specific effects.")
        VALUE(32, BE, component, "Component ID", HEX)
        VALUE_CONST(status, "Status", AUD_EAP_SWITCH_ONOFF)
        FILLER(FILLER_FIXED, 24)
    SEQ_END

    /* Subblock Definitions */

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_OPEN_REQ_SB */
    /* ------------------------------------------------------------------ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_OPEN_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_OPEN_REQ_SB, "", "")
        AUD_EAP_COMMON_SB(tISI_aud_eap_stream_open_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( samplerate, "Samplerate", AUD_EAP_STREAM_SAMPLERATE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( channels, "Channels", AUD_EAP_STREAM_CHANNELS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( buffer_format, "Buffer format", AUD_EAP_STREAM_BUFFER_FORMAT)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Size of frame in samples")
        VALUE( 16, BE, frame_size, "Frame size", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Amount of frames")
        VALUE( 16, BE, frame_count, "Frame count", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( stream_type, "Stream type", AUD_EAP_STREAM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( flags, "Flags", AUD_EAP_STREAM_FLAGS)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_PLAY_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_PLAY_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_PLAY_REQ_SB, "", "")
        AUD_EAP_COMMON_SB(tISI_aud_eap_stream_play_req_sb)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_CLOSE_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_CLOSE_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_CLOSE_REQ_SB, "", "")
        AUD_EAP_COMMON_SB(tISI_aud_eap_stream_close_req_sb)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_CAPTURE_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_CAPTURE_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_CAPTURE_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_stream_capture_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "0 = continue until stopped, 1,2.. continue until amount of frames captured")
        VALUE( 16, BE, frame_count, "Frame count", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Amount of free frames until notification send, if 0 = default value is used")
        VALUE( 16, BE, threshold, "Threshold", HEX)
        COMMENT(COMMENT_TEXT, "Source of capturing: internal, external or external playback, if 0 = default value is used.")
        VALUE_CONST( capture_source, "Capture source", AUD_EAP_STREAM_CAPTURE_SOURCE)

    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_TIME_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_TIME_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_TIME_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_stream_time_req_sb)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_PAUSE_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_PAUSE_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_PAUSE_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_stream_pause_req_sb)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_OPEN_RESP_SB */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_OPEN_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_OPEN_RESP_SB, "", "")
        AUD_EAP_COMMON_SB(tISI_aud_eap_stream_open_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_PLAY_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_PLAY_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_PLAY_RESP_SB, "", "")
        AUD_EAP_COMMON_SB(tISI_aud_eap_stream_play_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_CLOSE_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_CLOSE_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_CLOSE_RESP_SB, "", "")
        AUD_EAP_COMMON_SB(tISI_aud_eap_stream_close_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
        VALUE( 32, BE, time, "Time in ms, the value of the stream time in the moment stream was closed", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_TIME_RESP_SB */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_TIME_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_TIME_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_stream_time_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
        VALUE( 32, BE, time, "Time in ms", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_PAUSE_RESP_SB */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_PAUSE_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_PAUSE_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_stream_pause_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
        VALUE( 32, BE, time, "Time in ms, the value of the stream time in the moment stream was paused", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_STREAM_CAPTURE_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_CAPTURE_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_STREAM_CAPTURE_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_stream_capture_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_create_stereo_widening_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_stereo_widening_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_create_stereo_widening_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_stereo_widening_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_CREATE_RATECONTROL_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_CREATE_RATECONTROL_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_CREATE_RATECONTROL_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_create_ratecontrol_req_sb)
        FILLER_EX(filler1, 16, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE( 32, BE, rate, "playback speed in millipercentage", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_RATECONTROL_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_RATECONTROL_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_RATECONTROL_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_ratecontrol_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_CREATE_RATECONTROL_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_CREATE_RATECONTROL_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_CREATE_RATECONTROL_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_create_ratecontrol_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
        VALUE( 32, BE, rate, "set playback speed in millipercentage", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_RATECONTROL_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_RATECONTROL_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_RATECONTROL_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_ratecontrol_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_LISTENER_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_LISTENER_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_LISTENER_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_listener_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_LISTENER_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_LISTENER_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_LISTENER_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_listener_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_SOURCE_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_SOURCE_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_SOURCE_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_source_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_SOURCE_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_SOURCE_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_SOURCE_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_source_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_obstruction_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_obstruction_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_occlusion_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_occlusion_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_distance_attn_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_distance_attn_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_reverberation_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_3d_reverberation_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END
    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_VISUALIZATION_REQ_SB*/
    /* ------------------------------------------------------------------ */
    COMMENT(COMMENT_PARAGRAPH,
        "With this message the visualization effect is destroyed.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_VISUALIZATION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_VISUALIZATION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_visualization_req_sb)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_VISUALIZATION_RESP_SB*/
    /* ------------------------------------------------------------------ */
    COMMENT(COMMENT_PARAGRAPH,
        "This is response to AUD_EAP_DESTROY_VISUALIZATION_REQ_SB.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_VISUALIZATION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_VISUALIZATION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_visualization_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END


    /* -------------------------------------------------------------------- */
    /* AUD_EAP_EFFECT_VISUALIZATION_REQ_SB */
    /* -------------------------------------------------------------------- */
     COMMENT(COMMENT_PARAGRAPH,
        "This subblock is for configuring visualization effect. This SB is used when "
        "creating the visualization effect or adjusting its parameter when visualization is "
        "already running. ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_VISUALIZATION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_VISUALIZATION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_visualization_req_sb)
        FILLER_EX(filler, 16, 1)
        COMMENT(COMMENT_PARAGRAPH, "Data Collection Frequency. Describes how many times per second "
                                    "the client will receive AUD_EAP_VISUALIZATION_DATA_NTF ")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 10)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        VALUE(16, BE, data_rate, "Data Rate", DEC)
        COMMENT(COMMENT_PARAGRAPH, "AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN if waveform"
                                    "visualization enabled")
        VALUE(16, BE, num_samples_waveform, "Number of Waveform datasamples", DEC)
        COMMENT(COMMENT_PARAGRAPH, "AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN if spectrum"
                                            "visualization enabled")
        VALUE(16, BE, num_samples_spectrum, "Number of Spectrum datasamples", DEC)
        MERGE_BEGIN(16, BE, ctrl_flags, "Control Flags")
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE(8, BE, reserved, "Reserved", DEC)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            COMMENT(COMMENT_PARAGRAPH,
              "Set to zero for normal operation. Values 1-15 can be used for"
              "to select built-in tests. Tests not defined yet.")
            VALUE(4, BE, test_mode, "Test mode", DEC)

            VALUE(2, BE, reserved2, "Reserved2", DEC)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE_CONST(operation_mode, "Enabled features",
                    AUD_VISUALIZATION_OP_MODE)
        MERGE_END

    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_EFFECT_VISUALIZATION_RESP_SB */
    /* -------------------------------------------------------------------- */
    COMMENT(COMMENT_PARAGRAPH,
        "This subblock is response for AUD_EAP_EFFECT_VISUALIZATION_REQ_SB.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_VISUALIZATION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_VISUALIZATION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_viualization_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END


    /* ------------------------------------------------------------------ */
    /* AUD_EAP_INFO_RATECONTROL_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_INFO_RATECONTROL_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_INFO_RATECONTROL_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_info_ratecontrol_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_INFO_RATECONTROL_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_INFO_RATECONTROL_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_INFO_RATECONTROL_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_info_ratecontrol_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
        VALUE( 32, BE, min_rate, "minimum possible speed rate in millipercentage", DEC)
        VALUE( 32, BE, max_rate, "maximum possible speed rate in millipercentage", DEC)
        VALUE( 32, BE, cur_rate, "current speed rate in millipercentage", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_CREATE_LEVELCHANGE_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_CREATE_LEVELCHANGE_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_CREATE_LEVELCHANGE_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_create_levelchange_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( channel, "Channel", AUD_EAP_CHANNEL_IDENTIFICATION)
        VALUE( 32, BE, volume, "Volume level in Q1.14", DEC)
        VALUE( 32, BE, time, "ms, time when level change will be applied in playback time", DEC)
        VALUE( 32, BE, duration, "ms, time how long level will take change to new value", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_CREATE_LEVELCHANGE_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_CREATE_LEVELCHANGE_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_CREATE_LEVELCHANGE_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_create_levelchange_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_CREATE_PANCHANGE_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_CREATE_PANCHANGE_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_CREATE_PANCHANGE_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_create_panchange_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( channel, "Channel", AUD_EAP_CHANNEL_IDENTIFICATION)
        VALUE( 32, BE, pan, "0 - 100, 50 = normal, 0 = full left, 100 = full right", DEC)
        VALUE( 32, BE, time, "ms, time when pan change will be applied in playback time", DEC)
        VALUE( 32, BE, duration, "ms, time how long pan will take change to new value", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_CREATE_PANCHANGE_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_CREATE_PANCHANGE_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_CREATE_PANCHANGE_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_create_panchange_resp_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_INFO_AVAILABILITY_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_INFO_AVAILABILITY_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_INFO_AVAILABILITY_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_info_availability_req_sb)
        FILLER_EX(filler1, 16, 1)
    SB_END

    SEQ_BEGIN(AUD_EAP_EFFECT_AVAILABLE_SEQ, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST( effects, "effects", AUD_EAP_EFFECT_AVAILABLE )
    SEQ_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_INFO_AVAILABILITY_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_INFO_AVAILABILITY_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_INFO_AVAILABILITY_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_info_availability_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        VALUE(8, BE, nbr_of_effects, "number of effects", DEC)
        SEQ_OF_REF(effects, "list of effects available", AUD_EAP_EFFECT_AVAILABLE_SEQ, N,
               ISIHDR_MARKER_ANYSIZE)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_INFO_VISUALIZATION_REQ_SB                                    */
    /* -------------------------------------------------------------------- */
    COMMENT(COMMENT_PARAGRAPH,
        "With this subblock client can enquire visualization parameters.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_INFO_VISUALIZATION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_INFO_VISUALIZATION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_info_visualization_req_sb)
        FILLER_EX(filler, 16, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_INFO_VISUALIZATION_RESP_SB                                    */
    /* -------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH,
        "With this subblock visualization parameters are delivered to the client.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_INFO_VISUALIZATION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_INFO_VISUALIZATION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_info_visualization_resp_sb)
        COMMENT(COMMENT_PARAGRAPH, "Sample rate of visualized audio")
        VALUE_CONST( sample_rate, "Samplerate", AUD_EAP_STREAM_SAMPLERATE)
        COMMENT(COMMENT_PARAGRAPH, "Data Collection Frequency. Describes how many times per second "
                                    "the client will receive AUD_EAP_VISUALIZATION_DATA_NTF ")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 10)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        VALUE_EX(8, BE, data_rate, "Data rate", DEC, 1.0, 0.0, "Hz")
        FILLER_EX(filler, 16, 1)

        MERGE_BEGIN(16, BE, ctrl_flags, "Control Flags")
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE(8, BE, reserved, "Reserved", DEC)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            COMMENT(COMMENT_PARAGRAPH,
              "Set to zero for normal operation. Values 1-15 can be used for"
              "to select built-in tests. Tests not defined yet.")
            VALUE(4, BE, test_mode, "Test mode", DEC)

            VALUE(2, BE, reserved2, "Reserved2", DEC)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE_CONST(operation_mode, "Enabled features",
                    AUD_VISUALIZATION_OP_MODE)
        MERGE_END

        COMMENT(COMMENT_PARAGRAPH, "AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN if waveform"
                                            "visualization enabled")
        COMMENT(COMMENT_PARAGRAPH, "Number of waveform data samples")
        VALUE(16, BE, num_samples_waveform, "Waveform samples", DEC)
        COMMENT(COMMENT_PARAGRAPH, "AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN if spectrum"
                                            "visualization enabled")
        COMMENT(COMMENT_PARAGRAPH, "Number of spectrum data samples")
        VALUE(16, BE, num_samples_spectrum, "Spectrum samples", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_PARAGRAPH, "Timestamp is a running 64-bit count of the samples "
                                   "received from the input stream. "
                                   "For example, if data collection is set to take place ten times per second, "
                                   "the acquisition period is 4800 samples (as sample rate within visualization is fixed to 48 kHz) "
                                   "and data collection is started from every 4800th sample of the input stream. "
                                   "The timestamp value in the output buffer sent to the client reflects the number "
                                   "of the first sample in the buffer. In other words, if data rate is 10 the timestamp in the "
                                   "first buffer is 0, in the second buffer 4800, in the third buffer 9600 and so on. ")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x00000000)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0xffffffff)
        VALUE(32, BE, timestampHi, "Higher part of 64bit timestamp", HEX)

        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x00000000)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0xffffffff)
        VALUE(32, BE, timestampLo, "Lower part of 64bit timestamp", HEX)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_LISTENER_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_LISTENER_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_LISTENER_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_listener_req_sb)
        FILLER_EX(filler1, 16, 1)
        COMMENT( COMMENT_TEXT, "ms, time when effect will be applied in playback time")
        VALUE( 32, BE, time, "time", DEC)
        COMMENT( COMMENT_TEXT, "mm, listener x coordinate")
        VALUE( -32, BE, location_x, "location x", DEC)
        COMMENT( COMMENT_TEXT, "mm, listener y coordinate")
        VALUE( -32, BE, location_y, "location y", DEC)
        COMMENT( COMMENT_TEXT, "mm, listener z coordinate")
        VALUE( -32, BE, location_z, "location z", DEC)
        COMMENT( COMMENT_TEXT, "heading rotation in radians")
        VALUE( -32, BE, heading, "heading", DEC)
        COMMENT( COMMENT_TEXT, "pitch rotation in radians")
        VALUE( -32, BE, pitch, "pitch", DEC)
        COMMENT( COMMENT_TEXT, "roll rotation in radians")
        VALUE( -32, BE, roll, "roll", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_LISTENER_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_LISTENER_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_LISTENER_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_listener_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_SOURCE_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_SOURCE_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_SOURCE_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_source_req_sb)
        FILLER_EX(filler1, 16, 1)
        COMMENT( COMMENT_TEXT, "ms, time when effect will be applied in playback time")
        VALUE( 32, BE, time, "time", DEC)
        COMMENT( COMMENT_TEXT, "mm, source x coordinate")
        VALUE( -32, BE, location_x, "location x", DEC)
        COMMENT( COMMENT_TEXT, "mm, source y coordinate")
        VALUE( -32, BE, location_y, "location y", DEC)
        COMMENT( COMMENT_TEXT, "mm, source z coordinate")
        VALUE( -32, BE, location_z, "location z", DEC)
        COMMENT( COMMENT_TEXT, "heading rotation in radians")
        VALUE( -32, BE, heading, "heading", DEC)
        COMMENT( COMMENT_TEXT, "pitch rotation in radians")
        VALUE( -32, BE, pitch, "pitch", DEC)
        COMMENT( COMMENT_TEXT, "roll rotation in radians")
        VALUE( -32, BE, roll, "roll", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_SOURCE_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_SOURCE_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_SOURCE_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_source_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_obstruction_req_sb)
        VALUE_CONST( preset, "preset", AUD_EAP_OBSTRUCTION_PRESET)
        COMMENT( COMMENT_TEXT, "ms, time when effect will be applied in playback time")
        VALUE( 32, BE, time, "time", DEC)
        COMMENT( COMMENT_TEXT, "mB, output level at 5000 hz in millibels( 1mB = 1 / 100 dB ) at which \
                                   the sound directly from source will be heard compared to the overall \
                                   level of the source. Must be non-positive value. Setting the level \
                                   to 0 makes the source's frequency response flat.")
        VALUE( -32, BE, hf_level, "hf level", DEC)
        COMMENT( COMMENT_TEXT, "mB, level in millibels ( 1mB = 1 / 100 dB ) at which the sound directly \
                                from a source wull be heard compared to a non-obstructed source. Must be \
                                non-positive value. Setting the level to 0 makes the source non-osbtructed")
        VALUE( -32, BE, level, "level", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_obstruction_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_occlusion_req_sb)
        VALUE_CONST( preset, "preset", AUD_EAP_OCCLUSION_PRESET)
        COMMENT( COMMENT_TEXT, "ms, time when effect will be applied in playback time")
        VALUE( 32, BE, time, "time", DEC)
        COMMENT( COMMENT_TEXT, "mB, output level at 5000 hz in millibels( 1mB = 1 / 100 dB ) at which \
                                   the sound directly from source will be heard compared to the overall \
                                   level of the source. Must be non-positive value. Setting the level \
                                   to 0 makes the source's frequency response flat.")
        VALUE( -32, BE, hf_level, "hf level", DEC)
        COMMENT( COMMENT_TEXT, "mB, level in millibels ( 1mB = 1 / 100 dB ) at which the sound directly \
                                from a source wull be heard compared to a non-obstructed source. Must be \
                                non-positive value. Setting the level to 0 makes the source non-occluded")
        VALUE( -32, BE, level, "level", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_occlusion_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_distance_attn_req_sb)
        FILLER_EX(filler1, 8, 1)
        COMMENT( COMMENT_TEXT, "TRUE/FALSE, determines how distance gain behaves at distances dreater than maximum distance")
        VALUE( 8, BE, mute_after_max, "mute after max", DEC)
        COMMENT( COMMENT_TEXT, "ms, time when effect will be applied in playback time")
        VALUE( 32, BE, time, "time", DEC)
        COMMENT( COMMENT_TEXT, "mm, distance when distance gain is clipped to its maximum value. Default value is 1000")
        VALUE( -32, BE, min_distace, "minimum distance", DEC)
        COMMENT( COMMENT_TEXT, "mm, distance when distance gain does not decrease any more")
        VALUE( -32, BE, max_distace, "maximum distance", DEC)
        COMMENT( COMMENT_TEXT, "Specifies how the direct sound from sound source attenuates with the distance to the listener. Default value is 1000")
        VALUE( -32, BE, roll_off_factor, "roll off factor", DEC)
        COMMENT( COMMENT_TEXT, "mB")
        VALUE( -32, BE, air_absorption_level, "air absorption level", DEC)
        COMMENT( COMMENT_TEXT, "Specifies how the energy level of the room effect from the sound \
                                               source attenuates with the distance. If reverberation effect \
                                               is not active then this value has no impact on the audio. \
                                               Default value is 0")
        VALUE( -32, BE, room_roll_off_factor, "room roll off factor", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_distance_attn_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_reverberation_req_sb)
        VALUE_CONST( preset, "preset", AUD_EAP_REVERBERATION_PRESET)
        COMMENT( COMMENT_TEXT, "ms, time when effect will be applied in playback time")
        VALUE( 32, BE, time, "time", DEC)
        COMMENT( COMMENT_TEXT, "mB")
        VALUE( -32, BE, reflection_level, "reflection level", DEC)
        COMMENT( COMMENT_TEXT, "ms")
        VALUE( 32, BE, reflection_delay, "reflection delay", DEC)
        COMMENT( COMMENT_TEXT, "mB")
        VALUE( -32, BE, reverb_level, "reverberation level", DEC)
        COMMENT( COMMENT_TEXT, "ms")
        VALUE( 32, BE, reverb_delay, "reverberation delay", DEC)
        COMMENT( COMMENT_TEXT, "ms")
        VALUE( 32, BE, decay_time, "decay time", DEC)
        COMMENT( COMMENT_TEXT, "decay hf ratio in millipercentage, 1000 = 100%")
        VALUE( 32, BE, decay_hf_ratio, "decay hf ratio", DEC)
        COMMENT( COMMENT_TEXT, "diffusion in millipercentage, 1000 = 100%")
        VALUE( 32, BE, diffusion, "diffusion", DEC)
        COMMENT( COMMENT_TEXT, "modal density in millipercentage, 1000 = 100%")
        VALUE( 32, BE, modal_density, "modal density", DEC)
        COMMENT( COMMENT_TEXT, "mB")
        VALUE( -32, BE, room_level, "room level", DEC)
        COMMENT( COMMENT_TEXT, "mB")
        VALUE( -32, BE, room_hf_level, "room hf level", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_reverberation_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_COMMIT_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_COMMIT_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_COMMIT_REQ_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_commit_req_sb)
        FILLER_EX(filler1, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_3D_COMMIT_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_3D_COMMIT_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_3D_COMMIT_RESP_SB, "", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_3d_commit_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB*/
    /* ------------------------------------------------------------------ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB" "_LEN")
    SB_BEGIN(AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB, "", "")
        COMMON_SB_LONG
        COMMENT(COMMENT_PARAGRAPH, "16 bit mono samples for waveform visualization")
        SEQ_OF(waveform_data, "Waveform Data",
         AUTOGEN_SEQ_WORD_HEX, AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB*/
    /* ------------------------------------------------------------------ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB" "_LEN")
    SB_BEGIN(AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB, "", "")
        COMMON_SB_LONG
        COMMENT(COMMENT_PARAGRAPH, "32 bit power spectrum density values for spectrum visualization")
        SEQ_OF(spectrum_data, "Spectrum Data",
         AUTOGEN_SEQ_DWORD_HEX, AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_VSURROUND_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_VSURROUND_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_VSURROUND_REQ_SB, "001.002", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_vsurround_req_sb)
        FILLER_EX(filler1, 16, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT( COMMENT_TEXT, "Effect strength in percentages (0-100)")
        VALUE( 32, BE, strength, "strength", DEC)
    SB_END
    
    /* ------------------------------------------------------------------ */
    /* AUD_EAP_EFFECT_VSURROUND_RESP_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_VSURROUND_RESP_SB" "_LEN")
    SB_BEGIN(AUD_EAP_EFFECT_VSURROUND_RESP_SB, "001.002", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_effect_vsurround_resp_sb)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END
    
    /* ------------------------------------------------------------------ */
    /* AUD_EAP_DESTROY_VSURROUND_REQ_SB*/
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DESTROY_VSURROUND_REQ_SB" "_LEN")
    SB_BEGIN(AUD_EAP_DESTROY_VSURROUND_REQ_SB, "001.002", "")
        AUD_EAP_FIXED_COMMON_SB(tISI_aud_eap_destroy_vsurround_req_sb)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        FILLER_EX(filler1, 16, 1)
    SB_END
    
    /* EAP Message descriptions */

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_STREAM_REQ, AUD_EAP_STREAM_RESP */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_REQ" "_LEN")
    MSG_BEGIN(AUD_EAP_STREAM_REQ, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_stream_req)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Unique ID for stream identification")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_STREAM_OPEN_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_PLAY_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_CLOSE_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_CAPTURE_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_TIME_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_PAUSE_REQ_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_STREAM_RESP" "_LEN")
    MSG_BEGIN(AUD_EAP_STREAM_RESP, MESSAGE_RESP, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_stream_resp)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Unique ID for stream identification")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, reason, "Reason", DEC)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_STREAM_OPEN_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_PLAY_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_CLOSE_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_CAPTURE_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_TIME_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_STREAM_PAUSE_RESP_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_EAP_STREAM_REQ, AUD_EAP_STREAM_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_EFFECT_CREATE_REQ, AUD_EAP_EFFECT_CREATE_RESP */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_CREATE_REQ" "_LEN")
    MSG_BEGIN(AUD_EAP_EFFECT_CREATE_REQ, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_effect_create_req)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "AUD_EAP_MASTER_STREAM_ID, or affected stream_id")
        VALUE_CONST( stream_id, "Stream ID", AUD_EAP_PREDEFINED_STREAM_ID)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_CREATE_RATECONTROL_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_CREATE_LEVELCHANGE_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_CREATE_PANCHANGE_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_LISTENER_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_SOURCE_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VISUALIZATION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VSURROUND_REQ_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_CREATE_RESP" "_LEN")
    MSG_BEGIN(AUD_EAP_EFFECT_CREATE_RESP, MESSAGE_RESP, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_effect_create_resp)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "AUD_EAP_MASTER_STREAM_ID, or affected stream_id")
        VALUE_CONST( stream_id, "Stream ID", AUD_EAP_PREDEFINED_STREAM_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, reason, "Reason", DEC)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_CREATE_RATECONTROL_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_CREATE_LEVELCHANGE_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_CREATE_PANCHANGE_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_LISTENER_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_SOURCE_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VISUALIZATION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VSURROUND_RESP_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_EAP_EFFECT_CREATE_REQ, AUD_EAP_EFFECT_CREATE_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_EFFECT_DESTROY_REQ, AUD_EAP_EFFECT_DESTROY_RESP */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_DESTROY_REQ" "_LEN")
    MSG_BEGIN(AUD_EAP_EFFECT_DESTROY_REQ, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_effect_destroy_req)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "AUD_EAP_MASTER_STREAM_ID, or affected stream_id")
        VALUE_CONST( stream_id, "Stream ID", AUD_EAP_PREDEFINED_STREAM_ID)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_RATECONTROL_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_LISTENER_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_SOURCE_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_OBSTRUCTION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_OCCLUSION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_DISTANCE_ATTN_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_REVERBERATION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_VISUALIZATION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_VSURROUND_REQ_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_DESTROY_RESP" "_LEN")
    MSG_BEGIN(AUD_EAP_EFFECT_DESTROY_RESP, MESSAGE_RESP, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_effect_destroy_resp)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "AUD_EAP_MASTER_STREAM_ID, or affected stream_id")
        VALUE_CONST( stream_id, "Stream ID", AUD_EAP_PREDEFINED_STREAM_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, reason, "Reason", DEC)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_RATECONTROL_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_LISTENER_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_SOURCE_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_OBSTRUCTION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_OCCLUSION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_DISTANCE_ATTN_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_3D_REVERBERATION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_DESTROY_VISUALIZATION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VSURROUND_RESP_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_EAP_EFFECT_DESTROY_REQ, AUD_EAP_EFFECT_DESTROY_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_EFFECT_INFO_REQ, AUD_EAP_EFFECT_INFO_RESP */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_INFO_REQ" "_LEN")
    MSG_BEGIN(AUD_EAP_EFFECT_INFO_REQ, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_effect_info_req)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "AUD_EAP_MASTER_STREAM_ID, or affected stream_id")
        VALUE_CONST( stream_id, "Stream ID", AUD_EAP_PREDEFINED_STREAM_ID)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_INFO_RATECONTROL_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_INFO_AVAILABILITY_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_INFO_VISUALIZATION_REQ_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_INFO_RESP" "_LEN")
    MSG_BEGIN(AUD_EAP_EFFECT_INFO_RESP, MESSAGE_RESP, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_effect_info_resp)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "AUD_EAP_MASTER_STREAM_ID, or affected stream_id")
        VALUE_CONST( stream_id, "Stream ID", AUD_EAP_PREDEFINED_STREAM_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, reason, "Reason", DEC)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_INFO_RATECONTROL_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_INFO_AVAILABILITY_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_INFO_VISUALIZATION_RESP_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_EAP_EFFECT_INFO_REQ, AUD_EAP_EFFECT_INFO_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_EFFECT_ADJUST_REQ, AUD_EAP_EFFECT_ADJUST_RESP */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_ADJUST_REQ" "_LEN")
    MSG_BEGIN(AUD_EAP_EFFECT_ADJUST_REQ, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_effect_adjust_req)
        COMMENT( COMMENT_TEXT, "or user acquired stream id")
        VALUE_CONST( stream_id, "Stream ID", AUD_EAP_PREDEFINED_STREAM_ID)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_LISTENER_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_SOURCE_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_OBSTRUCTION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_OCCLUSION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_DISTANCE_ATTN_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_REVERBERATION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_COMMIT_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VISUALIZATION_REQ_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VSURROUND_REQ_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_EFFECT_ADJUST_RESP" "_LEN")
    MSG_BEGIN(AUD_EAP_EFFECT_ADJUST_RESP, MESSAGE_RESP, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_effect_adjust_resp)
        COMMENT( COMMENT_TEXT, "or user acquired stream id")
        VALUE_CONST( stream_id, "Stream ID", AUD_EAP_PREDEFINED_STREAM_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, reason, "Reason", DEC)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_LISTENER_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_SOURCE_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_OBSTRUCTION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_OCCLUSION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_DISTANCE_ATTN_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_REVERBERATION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_3D_COMMIT_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VISUALIZATION_RESP_SB)
            SB_LST_ENTRY(AUD_EAP_EFFECT_VSURROUND_RESP_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_EAP_EFFECT_ADJUST_REQ, AUD_EAP_EFFECT_ADJUST_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_BUFFER_CLIENT_NTF */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_BUFFER_CLIENT_NTF" "_LEN")
    MSG_BEGIN(AUD_EAP_BUFFER_CLIENT_NTF, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_buffer_client_ntf)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Unique ID for stream identification")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_BUFFER_SERVER_NTF */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_BUFFER_SERVER_NTF" "_LEN")
    MSG_BEGIN(AUD_EAP_BUFFER_SERVER_NTF, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_buffer_server_ntf)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Unique ID for stream identification")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_BUFFER_OVERFLOW_NTF */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_BUFFER_OVERFLOW_NTF" "_LEN")
    MSG_BEGIN(AUD_EAP_BUFFER_OVERFLOW_NTF, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_buffer_overflow_ntf)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Unique ID for stream identification")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Buffer overflow reason", AUD_EAP_BUFFER_OVERFLOW_REASON)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 16, 1)
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_BUFFER_EMPTY_NTF */
    /* -------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH,
        "This message informs client when all buffer's are empty and EAP start's "
        "feeding some filling data to output")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_BUFFER_EMPTY_NTF" "_LEN")
    MSG_BEGIN(AUD_EAP_BUFFER_EMPTY_NTF, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_buffer_empty_ntf)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Unique ID for stream identification")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_VISUALIZATION_DATA_NTF                                       */
    /* -------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH,
        "With this notification visualization data is sent to client. Notification is sent "
        "every time the algorithm has collected as many waveform and/or spectrum data samples "
        "as configured.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_VISUALIZATION_DATA_NTF" "_LEN")
    MSG_BEGIN(AUD_EAP_VISUALIZATION_DATA_NTF, MESSAGE_NTF, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_visualization_data_ntf)
        FILLER_EX(filler1, 16, 1)
        COMMENT(COMMENT_PARAGRAPH, "AUD_EAP_VISUALIZATION_WAVEFORM_DATA_LEN if waveform"
                                            "visualization enabled")
        COMMENT(COMMENT_PARAGRAPH, "Number of waveform data samples")
        VALUE(16, BE, num_samples_waveform, "Waveform samples", DEC)
        COMMENT(COMMENT_PARAGRAPH, "AUD_EAP_VISUALIZATION_SPECTRUM_DATA_LEN if spectrum"
                                            "visualization enabled")
        COMMENT(COMMENT_PARAGRAPH, "Number of spectrum data samples")
        VALUE(16, BE, num_samples_spectrum, "Spectrum samples", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_PARAGRAPH, "Timestamp is a running 64-bit count of the samples "
                                   "received from the input stream. "
                                   "For example, if data collection is set to take place ten times per second, "
                                   "the acquisition period is 4800 samples (as sample rate within visualization is fixed to 48 kHz) "
                                   "and data collection is started from every 4800th sample of the input stream. "
                                   "The timestamp value in the output buffer sent to the client reflects the number "
                                   "of the first sample in the buffer. In other words, if data rate is 10 the timestamp in the "
                                   "first buffer is 0, in the second buffer 4800, in the third buffer 9600 and so on. ")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x00000000)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0xffffffff)
        VALUE(32, BE, timestampHi, "Higher part of 64bit timestamp", HEX)

        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x00000000)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0xffffffff)
        VALUE(32, BE, timestampLo, "Lower part of 64bit timestamp", HEX)
        FILLER_EX(filler2, 8, 3)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EAP_VISUALIZATION_WAVEFORM_DATA_SB)
            SB_LST_ENTRY(AUD_EAP_VISUALIZATION_SPECTRUM_DATA_SB)
        SB_LST_REF_END
     MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_DATA_TRACING_REQ, AUD_EAP_DATA_TRACING_RESP */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DATA_TRACING_REQ" "_LEN")
    MSG_BEGIN(AUD_EAP_DATA_TRACING_REQ, MESSAGE_REQ, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_data_tracing_req)
        FILLER_EX(filler1, 16, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( trace_points, "Trace points", AUD_EAP_DATA_TRACE_POINTS)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EAP_DATA_TRACING_RESP" "_LEN")
    MSG_BEGIN(AUD_EAP_DATA_TRACING_RESP, MESSAGE_RESP, "", "")
        AUD_EAP_MSG_HDR(tISI_aud_eap_data_tracing_resp)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST( reason, "Reason", AUD_EAP_STREAM_REASON)
        FILLER_EX(filler1, 8, 1)
    MSG_END

    MSG_PAIR(AUD_EAP_DATA_TRACING_REQ, AUD_EAP_DATA_TRACING_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_TUNING_PARAM_READ_REQ, AUD_EAP_TUNING_PARAM_READ_RESP */
    /* -------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH,
            "This message is used for requesting the current tuning parameter "
            "values of the selected audio effect from the phone.")
    MSG_BEGIN(AUD_EAP_TUNING_PARAM_READ_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(effect, "Effect", AUD_EAP_EFFECT_TUNING)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH,
            "This message returns the current tuning parameter values of the "
            "selected audio effect from the phone.")
    MSG_BEGIN(AUD_EAP_TUNING_PARAM_READ_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(effect, "Effect", EFFECT, AUD_EAP_EFFECT)
        FILLER(FILLER_FIXED, 8)
        CHOICE_BEGIN(params, "Parameters", EFFECT)
			CASE_BEGIN(AUD_EAP_EFFECT_STW, "", "")
				SEQ_OF(tunings, "Parameters", AUD_EAP_TUNING_PARAM_STW, 1)
			CASE_END
			CASE_BEGIN(AUD_EAP_EFFECT_MUMDRC, "", "")
			   SEQ_OF(tunings, "Parameters", AUD_EAP_TUNING_PARAM_MUMDRC, 1)
			CASE_END
        CHOICE_END
    MSG_END

    MSG_PAIR(AUD_EAP_TUNING_PARAM_READ_REQ, AUD_EAP_TUNING_PARAM_READ_RESP)

     /* -------------------------------------------------------------------- */
    /* AUD_EAP_TUNING_PARAM_WRITE_REQ, AUD_EAP_TUNING_PARAM_WRITE_RESP      */
    /* -------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH,
            "This message is used for writing the tuning parameter values for "
            "the selected audio effect to the phone.")
    MSG_BEGIN(AUD_EAP_TUNING_PARAM_WRITE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(effect, "Effect", EFFECT, AUD_EAP_EFFECT_TUNING)
        COMMENT(COMMENT_PARAGRAPH,
                "When the lock is set on, tuning parameter values for the "
                "selected effect can only be changed with this request and "
                "not by any other event in the system. This applies until "
                "the lock is set off.")
        VALUE_CONST(lock, "Lock request", AUD_EAP_SWITCH_ONOFF)
        CHOICE_BEGIN(params, "Parameters", EFFECT)
			CASE_BEGIN(AUD_EAP_EFFECT_STW, "", "")
				SEQ_OF(tunings, "Parameters", AUD_EAP_TUNING_PARAM_STW, 1)
			CASE_END
			CASE_BEGIN(AUD_EAP_EFFECT_MUMDRC, "", "")
			   SEQ_OF(tunings, "Parameters", AUD_EAP_TUNING_PARAM_MUMDRC, 1)
			CASE_END
        CHOICE_END
    MSG_END

    COMMENT(COMMENT_PARAGRAPH,
            "This message is used as a response when the tuning parameter "
            "values for the selected audio effect have been taken into use "
            "as requested.")
    MSG_BEGIN(AUD_EAP_TUNING_PARAM_WRITE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(effect, "Effect", AUD_EAP_EFFECT)
        VALUE_CONST(lock, "Lock status", AUD_EAP_SWITCH_ONOFF)
    MSG_END

    MSG_PAIR(AUD_EAP_TUNING_PARAM_WRITE_REQ, AUD_EAP_TUNING_PARAM_WRITE_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_TUNING_PARAM_LOCK_REQ, AUD_EAP_TUNING_PARAM_LOCK_RESP      */
    /* -------------------------------------------------------------------- */


    COMMENT(COMMENT_PARAGRAPH,
            "This message is used to lock/unlock the current tuning parameter "
            "values for the selected effect in the phone.")
    MSG_BEGIN(AUD_EAP_TUNING_PARAM_LOCK_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(effect, "Effect", AUD_EAP_EFFECT_TUNING)
        COMMENT(COMMENT_TEXT,
                "When the lock is set on, tuning parameter values for the "
                "selected effect can only be changed with ")
        COMMENT_LINK(LINK_MESSAGE, "AUD_EAP_TUNING_PARAM_WRITE_REQ", "", "")
        COMMENT(COMMENT_PARAGRAPH,
                " and not by any other event in the system. This applies "
                "until the lock is set off.")
        VALUE_CONST(lock, "Lock request", AUD_EAP_SWITCH_ONOFF)
    MSG_END


    COMMENT(COMMENT_PARAGRAPH,
            "This message is used as a response when the tuning parameter "
            "lock request for the selected audio effect has been processed.")
    MSG_BEGIN(AUD_EAP_TUNING_PARAM_LOCK_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(effect, "Effect", AUD_EAP_EFFECT)
        VALUE_CONST(lock, "Lock status", AUD_EAP_SWITCH_ONOFF)
    MSG_END

    MSG_PAIR(AUD_EAP_TUNING_PARAM_LOCK_REQ, AUD_EAP_TUNING_PARAM_LOCK_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ, AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP*/
    /* -------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH,
            "This message is used for reading the on/off status of the "
            "selected audio effect from the phone.")
    MSG_BEGIN(AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(effect, "Effect", AUD_EAP_EFFECT)
        FILLER(FILLER_FIXED, 8)
        COMMENT(COMMENT_PARAGRAPH,
                "ID of a specific instance of the effect as defined in the "
                "audio routing network, used with stream specific effects. "
                "0 means all instances are affected.")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(32, BE, instance, "Instance", HEX)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH,
            "This message returns the on/off status of the selected audio effect.")
    MSG_BEGIN(AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(effect, "Effect", AUD_EAP_EFFECT)
        COMMENT(COMMENT_PARAGRAPH,
                "Value can be greater than one only when all components of the "
                "effect have been queried for their status. Value is zero when "
                "there are no components of the effect in the system.")
        REFERENCE(8, BE, number, "Number of components", N)
        SEQ_OF_REF(status, "Status", AUD_EAP_EFFECT_STATUS, N, ISIHDR_POINTER)
    MSG_END

    MSG_PAIR(AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ, AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ, AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP*/
    /* -------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH,
            "This message is used for switching the selected audio effect "
            "on/off in the phone. The effect remains in the requested state "
            "until a new request is sent.")
    MSG_BEGIN(AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(effect, "Effect", AUD_EAP_EFFECT)
        FILLER(FILLER_FIXED, 8)
        COMMENT(COMMENT_PARAGRAPH,
                "ID of a specific instance of the effect as defined in the "
                "audio routing network, used with stream specific effects. "
                "0 means all instances are affected.")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(32, BE, instance, "Instance", HEX)
        VALUE_CONST(request, "Request", AUD_EAP_SWITCH)
        FILLER(FILLER_FIXED, 24)
    MSG_END


    COMMENT(COMMENT_PARAGRAPH,
            "This message is used as a response when the state of the selected "
            "audio effect has been changed as requested.")
    MSG_BEGIN(AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(effect, "Effect", AUD_EAP_EFFECT)
        FILLER(FILLER_FIXED, 8)
        COMMENT(COMMENT_PARAGRAPH,
                "ID of a specific instance of the effect as defined in the "
                "audio routing network, used with stream specific effects. "
                "0 means all instances are affected.")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(32, BE, instance, "Instance", HEX)
        VALUE_CONST(status, "Status", AUD_EAP_SWITCH_ONOFF)
        FILLER(FILLER_FIXED, 24)
    MSG_END

    MSG_PAIR(AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ, AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP)




RES_END

/* End of file aud_eap_isi_m.h */
