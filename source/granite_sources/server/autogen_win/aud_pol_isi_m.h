/*
NOKIA
Oulu
My Concurrent Audio










            AUDIO Server Policy Message Macro definitions
            --------------------------------------

            SW include - ANSI C




Continuus Ref:
--------------
database:           ou1gif

project path:       global_interface/ISI/Core

%name:              aud_pol_isi_m.h %

%version:           ou1s40#007.004 %

%cvtype:            incl %

%instance:          ou1core_1 %


Copyright(c)Nokia


Change history:

VERSION     : 007.004 NONDRAFT  1-Apr-2011 Kari Pohto
REASON      : Change request
REFERENCE   : ADB SWAM CR KP11040144090
DESCRIPTION : Add routing flags to define capture source

VERSION     : 007.003 NONDRAFT  1-Jan-2011 Anton Nevala
REASON      : Change request
REFERENCE   : ADB SWAM CR AN11012153257
DESCRIPTION : New application preference "AUD_POL_PREF_TRACK_RECORDER"

VERSION     : 007.002 NONDRAFT  11-Oct-2010 Kari Pohto
REASON      : Change request
REFERENCE   : ADB SWAM CR KP10101136719
DESCRIPTION : Added FM TX audio mode

VERSION     : 007.001 NONDRAFT  31-May-2010 Kari Pohto
REASON      : Change request
REFERENCE   : ADB SWAM CR KP10053157325
DESCRIPTION : Added client list request and stream muting

VERSION     : 007.000 NONDRAFT  25-Jul-2007 Petri E Hokkanen
REASON      : Change request
REFERENCE   : ADB SWAM CR PH08081934540
DESCRIPTION : Interface changes, see SWAM CR and HTML what actually has changed.

VERSION     : 006.000 NONDRAFT  19-May-2007 Juha Byman
REASON      : Change request
REFERENCE   : ADB SWAM CR JB08052244175
DESCRIPTION : Interface updates regarding recording features

VERSION     : 005.000 NONDRAFT  17-Mar-2007 Petri E Hokkanen
REASON      : Error
REFERENCE   : PCP / PH08031732916
DESCRIPTION : Preference based mute added to mute.

VERSION     : 004.000 NONDRAFT  14-Nov-2007 Petri E Hokkanen
REASON      : Change request
REFERENCE   : ADB SWAM CR PH08010448841
DESCRIPTION : Volume and mute separated to own sub blocks.
            : Few other changes. See generated history more details.

VERSION     : 003.000 NONDRAFT  14-Nov-2007 Petri E Hokkanen
REASON      : Change request
REFERENCE   : SWAM CR: PH07111443710
DESCRIPTION : Removing some legacy types and prefs.
            : Introducing AUD_POL_VOL_LEVEL_NOT_RELEVANT and AUD_POL_APPL_ID_NOT_DEFINED.

VERSION     : 002.000 NONDRAFT  26-Mar-2007 Petteri Hyvonen
REASON      : Change request
REFERENCE   : SWAM CR: EH07031543236
DESCRIPTION : Defining Audio Policy interface further

VERSION     : 001.000 NONDRAFT  05-Jun-2006 Jani Pellikka
REASON      : Change request
REFERENCE   : 010-23879: AUD_POL: Interface definition
              SWAM CR: JP06052439808
DESCRIPTION : Defining Audio Policy interface further

VERSION     : 000.001 NONDRAFT  02-Mar-2006 Marko Kangasluoma
REASON      : Change request
REFERENCE   : 010-17884: AUD Policy: Application Check In/Out Interface
              SWAM CR: MK06022753147
DESCRIPTION : Created the file and implemented Policy interface

*/


/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Header file for the ISI Autogeneration Application


    1.2    Functional description

    This file is the message definition file for the Audio Policy


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
#define AUD_POL_APPL_REQ                            0xA0
#define AUD_POL_APPL_RESP                           0xA1
#define AUD_POL_VOLUME_REQ                          0xA2
#define AUD_POL_VOLUME_RESP                         0xA3
#define AUD_POL_CONTROL_NTF                         0xA4
#define AUD_POL_APPL_NTF                            0xA5
#define AUD_POL_RESOURCE_REQ                        0xA6
#define AUD_POL_RESOURCE_RESP                       0xA7
#define AUD_POL_STATUS_IND                          0xA8
#define AUD_POL_VOLUME_IND                          0xA9
#define AUD_POL_PRIVOL_REQ                          0xAA
#define AUD_POL_PRIVOL_RESP                         0xAB
#define AUD_POL_PRIVOL_NTF                          0xAC
#define AUD_POL_STATUS_REQ                          0xAD
#define AUD_POL_STATUS_RESP                         0xAE
#define AUD_POL_AUDIO_EFFECT_REQ                    0xAF
#define AUD_POL_AUDIO_EFFECT_RESP                   0xB0
#define AUD_POL_AUDIO_EFFECT_IND                    0xB1


/* Audio policy subblocks */
#define AUD_POL_APPL_DESCRIPTOR_REQ_SB              0x01
#define AUD_POL_APPL_DESCRIPTOR_RESP_SB             0x02
#define AUD_POL_APPL_ADD_STREAM_REQ_SB              0x03
#define AUD_POL_APPL_ADD_STREAM_RESP_SB             0x04
#define AUD_POL_APPL_REMOVE_APPL_REQ_SB             0x05
#define AUD_POL_APPL_REMOVE_APPL_RESP_SB            0x06
#define AUD_POL_APPL_REMOVE_STREAM_REQ_SB           0x07
#define AUD_POL_APPL_REMOVE_STREAM_RESP_SB          0x08
#define AUD_POL_VOL_CONTROL_REQ_SB                  0x09
#define AUD_POL_VOL_CONTROL_RESP_SB                 0x0A
#define AUD_POL_CONTROL_PRIORITY_NTF_SB             0x0B
#define AUD_POL_RESOURCE_REQ_SB                     0x0C
#define AUD_POL_RESOURCE_RESP_SB                    0x0D
#define AUD_POL_VOLUME_IND_SB                       0x0E
#define AUD_POL_STATUS_IND_SB                       0x0F
#define AUD_POL_MODE_IND_SB                         0x10
#define AUD_POL_MUTE_CONTROL_REQ_SB                 0x11
#define AUD_POL_MUTE_CONTROL_RESP_SB                0x12
#define AUD_POL_MODE_RESP_SB                        0x13
#define AUD_POL_MODE_PROPERTIES_SB                  0x14
#define AUD_POL_STATUS_INFO_REQ_SB                  0x15
#define AUD_POL_VOLUME_CHANGE_REQ_SB                0x16
#define AUD_POL_VOLUME_CHANGE_RESP_SB               0x17
#define AUD_POL_VOLUME_CHANGE_IND_SB                0x18
#define AUD_POL_MUTE_IND_SB                         0x19
#define AUD_POL_STREAM_VOLUME_REQ_SB                0x1A
#define AUD_POL_STREAM_VOLUME_RESP_SB               0x1B
#define AUD_POL_AUDIO_EFFECT_PHAP_SB                0x1C
#define AUD_POL_PRIVOL_CHANGE_NTF_SB                0x1D
#define AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB          0x1E
#define AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB         0x1F
#define AUD_POL_STREAM_MUTE_REQ_SB                  0x20
#define AUD_POL_STREAM_MUTE_RESP_SB                 0x21


/*  4    MACROS */

#define AUD_POL_COMMON_SB \
    REFERENCE(8, BE, subblock_id, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, subblock_length, "Subblock length", SB_LENGTH) \

#define AUD_POL_MSG_HDR \
        VALUE(8, BE, transaction_id, "Transaction ID", DEC) \
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)

#ifndef AUD_POL_ISI_VERSION
#define AUD_POL_ISI_VERSION
#define AUD_POL_ISI_VERSION_Z   7
#define AUD_POL_ISI_VERSION_Y   4
#endif

/* version history and cover page information */
/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "Oulu")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "My Concurrent Audio")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Kari Pohto")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIAL")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "ISI AUDIO Server Audio Policy Message Description")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_aud_pol_isi_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou1gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS-ou1gif#browse")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "GIF_SPECS/CoreSW")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

/* ISIHDR properties */
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "ou_pcms#1")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou1gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_interface/ISI/Core")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "audio_pol_isi.h")


RES_BEGIN(RESOURCE_ISI_EXTENSION, PN_AUDIO, AUD_POL, "Audio Policy",
    RES_VERSION_STRING(AUD_POL_ISI_VERSION_Z, AUD_POL_ISI_VERSION_Y), FALSE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    /* Latest version */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR KP11040144090")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "1-Apr-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Kari Pohto")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.004")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN11012153257")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "1-Jan-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.003")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR KP10101136719")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "11-Oct-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Kari Pohto")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR KP10053157325")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "31-May-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Kari Pohto")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.001")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR PH08081934540")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "25-Jul-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri E Hokkanen")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR JB08052244175")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-May-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Juha Byman")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR PH08031744363")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Mar-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri E Hokkanen")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("005.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR PH08010448841")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "4-Jan-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri E Hokkanen")
    COMMENT(COMMENT_TEXT, "AUD_POL_APPL_PREF_AUDIO_PROMPTING and AUD_POL_APPL_PREF_AUDIO_READING application preferenses renamed. Old names can still be used.")
    ISI_VERSION_HISTORY("004.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR PH07111443710")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Nov-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri E Hokkanen")
    COMMENT(COMMENT_TEXT, "AUD_POL_APPL_KARAOKE and AUD_POL_APPL_DICTAPHONE application types removed. ")
    COMMENT(COMMENT_TEXT, "AUD_POL_APPL_PREF_DEMO_ALERT application preference removed.")
    ISI_VERSION_HISTORY("003.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR EH07031543236")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "26-Mar-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petteri Hyvonen")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("002.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR JP06052439808")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "24-May-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jani Pellikka")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("001.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK06022753147")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "02-Mar-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Marko Kangasluoma")
    COMMENT(COMMENT_TEXT, "File created and Audio Policy implemented")
    ISI_VERSION_HISTORY("000.001")
    /* end of version history */

    /* Constants */

    CONSTANT_VER (AUD_POL_VOL_LEVEL_NOT_RELEVANT, 0, "003.000", "004.000")
    CONSTANT_VER (AUD_POL_APPL_ID_NOT_DEFINED   , 0, "003.000", "")
    CONSTANT_VER (AUD_POL_VALUE_NOT_VALID       , 0xFFFF, "007.000", "")

    /* Constant tables */

    CONST_TBL_BEGIN(AUD_POL_APPL_TYPE, 16, BE, "000.001", "")
        CONST_TBL_ENTRY(AUD_POL_APPL_NONE,                  0x00, "None")
        CONST_TBL_ENTRY(AUD_POL_APPL_CS_CALL,               0x01, "CS call")
        CONST_TBL_ENTRY(AUD_POL_APPL_PS_CALL,               0x02, "PS call")
        CONST_TBL_ENTRY(AUD_POL_APPL_PTT_CALL,              0x03, "PTT call")
        CONST_TBL_ENTRY(AUD_POL_APPL_MUSIC,                 0x04, "Music")
        CONST_TBL_ENTRY(AUD_POL_APPL_TONE_GEN,              0x05, "Tone generation")
        CONST_TBL_ENTRY(AUD_POL_APPL_DTMF_GEN,              0x06, "DTMF generation")
        CONST_TBL_ENTRY(AUD_POL_APPL_FM_RADIO,              0x07, "FM radio")
        CONST_TBL_ENTRY(AUD_POL_APPL_VOICE_CLIP,            0x08, "Voice clip")
        CONST_TBL_ENTRY(AUD_POL_APPL_VOICE_RECOG,           0x09, "Voice recognition")
        CONST_TBL_ENTRY(AUD_POL_APPL_VIDEO_AUDIO,           0x0A, "Video audio")
        COMMENT(COMMENT_TEXT, "Silent playback")
        CONST_TBL_ENTRY_VER(AUD_POL_APPL_SILENT_PLAYBACK,   0x0B, "002.000", "")
        COMMENT(COMMENT_TEXT, "FM recording")
        CONST_TBL_ENTRY_VER(AUD_POL_APPL_FM_RECORDING,      0x0C, "002.000", "")
        COMMENT(COMMENT_TEXT, "Voice recording")
        CONST_TBL_ENTRY_VER(AUD_POL_APPL_VOICE_RECORDING,   0x0D, "006.000", "")
        COMMENT(COMMENT_TEXT, "Video recording")
        CONST_TBL_ENTRY_VER(AUD_POL_APPL_VIDEO_RECORDING,   0x0E, "006.000", "")
        COMMENT(COMMENT_TEXT, "Video/audio streaming")
        CONST_TBL_ENTRY_VER(AUD_POL_APPL_STREAMING,         0x0F, "007.000", "")
        COMMENT(COMMENT_TEXT, "Volume UI")
        CONST_TBL_ENTRY_VER(AUD_POL_APPL_VOLUME_UI,         0x10, "007.000", "")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_APPL_PREF, 16, BE, "000.001", "")
        CONST_TBL_ENTRY(AUD_POL_PREF_NONE,                      0x00, "None")
        CONST_TBL_ENTRY(AUD_POL_PREF_RINGING,                   0x01, "Ringing")
        CONST_TBL_ENTRY(AUD_POL_PREF_ENTERTAINMENT_CAMERA,      0x02, "Entertainment camera")
        CONST_TBL_ENTRY(AUD_POL_PREF_ENTERTAINMENT_MUSIC,       0x03, "Entertainment music")
        CONST_TBL_ENTRY(AUD_POL_PREF_ENTERTAINMENT_GAME,        0x04, "Entertainment game")
        CONST_TBL_ENTRY(AUD_POL_PREF_CS_CALL,                   0x05, "CS call")
        CONST_TBL_ENTRY(AUD_POL_PREF_CS_CALL_EMERGENCY,         0x06, "CS call emergency")
        CONST_TBL_ENTRY(AUD_POL_PREF_PS_CALL,                   0x07, "PS call")
        CONST_TBL_ENTRY(AUD_POL_PREF_VIDEO_CALL,                0x08, "Video call")
        CONST_TBL_ENTRY(AUD_POL_PREF_UI_TONE,                   0x09, "UI tone")
        CONST_TBL_ENTRY(AUD_POL_PREF_SMS_ALERT,                 0x0A, "SMS alert")
        CONST_TBL_ENTRY(AUD_POL_PREF_CALENDAR_ALARM,            0x0B, "Calendar alarm")
        CONST_TBL_ENTRY(AUD_POL_PREF_ERROR_TONE,                0x0C, "Error tone")
        CONST_TBL_ENTRY(AUD_POL_PREF_WAKE_UP_ALARM,             0x0D, "Wake-up alarm")
        CONST_TBL_ENTRY(AUD_POL_PREF_CAMERA_SHUTTER,            0x0E, "Camera shutter")
        COMMENT(COMMENT_TEXT, "Entertainment")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_ENTERTAINMENT,         0x0F, "001.000", "")
        COMMENT(COMMENT_TEXT, "Voice training")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_VOICE_TRAINING,        0x10, "001.000", "")
        COMMENT(COMMENT_TEXT, "Sound demoing")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_SOUND_DEMOING,         0x11, "001.000", "")
        COMMENT(COMMENT_TEXT, "Key press")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_KEY_PRESS,             0x12, "001.000", "")
        COMMENT(COMMENT_TEXT, "Confirmation notification")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_CONFIRM_NOTIFY,        0x13, "001.000", "")
        COMMENT(COMMENT_TEXT, "Warning")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_WARNING,               0x14, "001.000", "")
        COMMENT(COMMENT_TEXT, "Network tone")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_NETWORK_TONE,          0x15, "001.000", "")
        COMMENT(COMMENT_TEXT, "Battery alarm")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_BATTERY_ALARM,         0x16, "001.000", "")
        COMMENT(COMMENT_TEXT, "Startup/shutdown")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_STARTUP_SHUTDOWN,      0x17, "001.000", "")
        COMMENT(COMMENT_TEXT, "Countdown timer")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_COUNTDOWN_TIMER,       0x18, "001.000", "")
        COMMENT(COMMENT_TEXT, "Audio prompting")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "AUD_POL_APPL_PREF_AUDIO_PROMPTING")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_AUDIO_PROMPTING,       0x19, "002.000", "")
        COMMENT(COMMENT_TEXT, "Audio reading")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "AUD_POL_APPL_PREF_AUDIO_READING")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_AUDIO_READING,         0x1A, "002.000", "")
        COMMENT(COMMENT_TEXT, "Demo UI")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_DEMO_UI,               0x1B, "002.000", "")
        COMMENT(COMMENT_TEXT, "Navigation Instructions")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_NAVIGATION,            0x1C, "004.000", "")
        COMMENT(COMMENT_TEXT, "FM Radio playback")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_ENTERTAINMENT_RADIO,   0x1D, "006.000", "")
        COMMENT(COMMENT_TEXT, "Kodiak PoC")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_KODIAK_POC,            0x1E, "006.000", "")
        COMMENT(COMMENT_TEXT, "Mobile TV")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_MOBILE_TV,             0x1F, "007.000", "")
        COMMENT(COMMENT_TEXT, "Track Recorder")
        CONST_TBL_ENTRY_VER(AUD_POL_PREF_TRACK_RECORDER,        0x20, "007.003", "")
    CONST_TBL_END

    /* Comment to AUD_POL_ROUTING table */
    COMMENT(COMMENT_TEXT, "For CALL use case, all these routings should be used: "
                          "AUD_POL_ROUTING_TX, AUD_POL_ROUTING_RX, AUD_POL_ROUTING_PLAY, AUD_POL_ROUTING_RECORD.")

    BIT_TBL_BEGIN(AUD_POL_ROUTING, 32, BE, "000.001", "")
        BIT_TBL_ENTRY("00000000000000000000000000000000",       AUD_POL_ROUTING_NONE,     "None")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1",       AUD_POL_ROUTING_PUBLIC,   "Public")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1X",       AUD_POL_ROUTING_PRIVATE,  "Private")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX100",       AUD_POL_ROUTING_DEFAULT,  "Default")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXX",       AUD_POL_ROUTING_PLAY,     "Play")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX",       AUD_POL_ROUTING_RECORD,   "Record")
        COMMENT(COMMENT_TEXT, "TX, should be used with AUD_POL_ROUTING_PLAY")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXX1XXXXX",       AUD_POL_ROUTING_TX,       "")
        COMMENT(COMMENT_TEXT, "RX, should be used with AUD_POL_ROUTING_RECORD")
        BIT_TBL_ENTRY_VER("XXXXXXXXXXXXXXXXXXXXXXXXX1XXXXXX",   AUD_POL_ROUTING_RX,       "002.000", "")
        COMMENT(COMMENT_TEXT, "Capture microphone, should be used with AUD_POL_ROUTING_RECORD")
        BIT_TBL_ENTRY_VER("XXXXXXXXXXXXXXXXXXXXXXXX1XXXXXXX",   AUD_POL_ROUTING_CAPTURE_MICROPHONE, "007.004", "")
        COMMENT(COMMENT_TEXT, "Capture playback streams, should be used with AUD_POL_ROUTING_RECORD")
        BIT_TBL_ENTRY_VER("XXXXXXXXXXXXXXXXXXXXXXX1XXXXXXXX",   AUD_POL_ROUTING_CAPTURE_PLAYBACK, "007.004", "")
        COMMENT(COMMENT_TEXT, "Capture recording streams, should be used with AUD_POL_ROUTING_RECORD")
        BIT_TBL_ENTRY_VER("XXXXXXXXXXXXXXXXXXXXXX1XXXXXXXXX",   AUD_POL_ROUTING_CAPTURE_RECORD, "007.004", "")
    BIT_TBL_END

    BIT_TBL_BEGIN(AUD_POL_FLAGS, 32, BE, "000.001", "")
        BIT_TBL_ENTRY("00000000000000000000000000000000", AUD_POL_FLAG_NONE,                "None")
        COMMENT(COMMENT_TEXT, "Audio policy pauses the application if this flag has been set and accessory is disconnected. "
                              "In case of FM radio, the application is muted when accessory is disconnected.")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1", AUD_POL_FLAG_MUTE_ACC_CHANGE,     "")
/*
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1X", AUD_POL_FLAG_MIXING_PREFERRED,    "Mixing preferred")
*/
    BIT_TBL_END

    BIT_TBL_BEGIN(AUD_POL_CAPABILITY_RESTRICTIONS, 32, BE, "007.000", "")
        BIT_TBL_ENTRY("00000000000000000000000000000000",       AUD_POL_CAPABILITY_NONE,              "None")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX01",       AUD_POL_CAPABILITY_NO_VOLUME,         "No volume")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX10",       AUD_POL_CAPABILITY_INCDEC_VOLUME,     "Inc/Dec volume")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XX",       AUD_POL_CAPABILITY_NO_DRM_CONTENT,    "DRM protected content not allowed")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXX",       AUD_POL_CAPABILITY_NO_RECOGNITION,    "No voice recognition")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX",       AUD_POL_CAPABILITY_NO_SPEAKER_MUTE,   "No speaker mute")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXXXXXXXXXXXX1XXXXX",       AUD_POL_CAPABILITY_NO_MIC_MUTE,       "No microphone mute")
    BIT_TBL_END

    CONST_TBL_BEGIN(AUD_POL_AUDIOBAND, 8, BE, "000.001", "")
        CONST_TBL_ENTRY(AUD_AUDIOBAND_NONE,             0x00,   "None")
        CONST_TBL_ENTRY(AUD_AUDIOBAND_NB,               0x01,   "Narrowband")
        CONST_TBL_ENTRY(AUD_AUDIOBAND_WB,               0x02,   "Wideband")
        CONST_TBL_ENTRY(AUD_AUDIOBAND_HQ,               0x03,   "High Quality")
    CONST_TBL_END

    BIT_TBL_BEGIN(AUD_POL_VOL_CONTROL_MUTING, 8, BE, "000.001", "004.000")
        BIT_TBL_ENTRY("00000000", AUD_POL_VOL_CONTROL_NONE,                 "None")
        BIT_TBL_ENTRY("XXXXXXX1", AUD_POL_VOL_CONTROL_MUTE_PLAY,            "Mute playback")
        BIT_TBL_ENTRY("XXXXXX1X", AUD_POL_VOL_CONTROL_MUTE_RECORD,          "Mute record")
    BIT_TBL_END

    BIT_TBL_BEGIN(AUD_POL_STATUS_TYPE, 8, BE, "007.000", "")
        BIT_TBL_ENTRY("00000000", AUD_POL_STATUS_TYPE_NONE,                 "None")
        BIT_TBL_ENTRY("XXXXXXX1", AUD_POL_STATUS_TYPE_AUDIO_MODE,           "Current audio mode")
        BIT_TBL_ENTRY("XXXXXX1X", AUD_POL_STATUS_TYPE_MODE_PROPERTIES,      "Audio mode properties")
		COMMENT(COMMENT_TEXT, "List of registered clients")
        BIT_TBL_ENTRY_VER("XXXXX1XX", AUD_POL_STATUS_TYPE_CLIENT_LIST,      "007.001", "")
    BIT_TBL_END

    CONST_TBL_BEGIN(AUD_POL_MIC_MUTING, 8, BE, "004.000", "")
        CONST_TBL_ENTRY(AUD_POL_MIC_MUTE_NOT_RELEVANT,  0x00,   "Microphone mute not changed")
        CONST_TBL_ENTRY(AUD_POL_MIC_MUTE,               0x01,   "Microphone muted")
        CONST_TBL_ENTRY(AUD_POL_MIC_UNMUTE,             0x02,   "Microphone unmuted")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_SPEAKER_MUTING, 8, BE, "004.000", "")
        CONST_TBL_ENTRY(AUD_POL_SPEAKER_MUTE_NOT_RELEVANT,  0x00,   "Speaker mute not changed")
        CONST_TBL_ENTRY(AUD_POL_SPEAKER_MUTE,               0x01,   "Speaker muted")
        CONST_TBL_ENTRY(AUD_POL_SPEAKER_UNMUTE,             0x02,   "Speaker unmuted")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_DIRECTIVE, 8, BE, "000.001", "")
        CONST_TBL_ENTRY(AUD_POL_DIRECTIVE_NONE,                  0x00, "None")
        CONST_TBL_ENTRY(AUD_POL_DIRECTIVE_DO_PAUSE,              0x01, "Do pause")
        CONST_TBL_ENTRY(AUD_POL_DIRECTIVE_DO_STOP,               0x02, "Do stop")
        CONST_TBL_ENTRY(AUD_POL_DIRECTIVE_DO_REMOVE,             0x03, "Do remove")
        CONST_TBL_ENTRY(AUD_POL_DIRECTIVE_REMOVED,               0x04, "Removed")
        CONST_TBL_ENTRY(AUD_POL_DIRECTIVE_MUTED,                 0x05, "Muted")
        COMMENT(COMMENT_TEXT, "Replace with beep")
        CONST_TBL_ENTRY_VER(AUD_POL_DIRECTIVE_REPLACE_WITH_BEEP, 0x06, "001.000", "")
        COMMENT(COMMENT_TEXT, "Blocked")
        CONST_TBL_ENTRY_VER(AUD_POL_DIRECTIVE_BLOCKED,           0x07, "001.000", "")
        COMMENT(COMMENT_TEXT, "Do start")
        CONST_TBL_ENTRY_VER(AUD_POL_DIRECTIVE_DO_START,          0x08, "002.000", "")
        COMMENT(COMMENT_TEXT, "Do resume")
        CONST_TBL_ENTRY_VER(AUD_POL_DIRECTIVE_DO_RESUME,         0x09, "002.000", "")
        COMMENT(COMMENT_TEXT, "Unmuted")
        CONST_TBL_ENTRY_VER(AUD_POL_DIRECTIVE_UNMUTED,           0x0A, "002.000", "")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_DIRECTIVE_REASON, 8, BE, "000.001", "")
        CONST_TBL_ENTRY(AUD_POL_DIR_REASON_NONE,                0x00, "None")
        CONST_TBL_ENTRY(AUD_POL_DIR_REASON_OUT_OF_MIPS,         0x01, "Out of MIPS")
        CONST_TBL_ENTRY(AUD_POL_DIR_REASON_OUT_OF_MEMORY,       0x02, "Out of memory")
        CONST_TBL_ENTRY(AUD_POL_DIR_REASON_HIGHER_PRIORITY,     0x03, "Higher priority")
        COMMENT(COMMENT_TEXT, "Mode changed")
        CONST_TBL_ENTRY_VER(AUD_POL_DIR_REASON_MODE_CHANGED,    0x04, "002.000", "")
    CONST_TBL_END

    /* Comment to AUD_POL_DIRECTIVE_STATUS */
    COMMENT(COMMENT_TEXT, "AUD_POL_DIR_STATUS_PROCEEDING and AUD_POL_DIR_STATUS_CHALLENGE are reserved for future. "
                          "The client could inform the Audio Policy that it takes longer time to perform some action "
                          "so Audio Policy could have some logic to handle the situation.")

    CONST_TBL_BEGIN(AUD_POL_DIRECTIVE_STATUS, 8, BE, "000.001", "")

        CONST_TBL_ENTRY(AUD_POL_DIR_STATUS_NONE,                0x00, "None")
        CONST_TBL_ENTRY(AUD_POL_DIR_STATUS_PROCEEDING,          0x01, "Proceeding")
        CONST_TBL_ENTRY(AUD_POL_DIR_STATUS_COMPLETED,           0x02, "Completed")
        CONST_TBL_ENTRY(AUD_POL_DIR_STATUS_CHALLENGE,           0x03, "Challenge")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_RESOURCE_REASON, 8, BE, "001.000", "")
        CONST_TBL_ENTRY(AUD_POL_RESOURCE_OK,                     0x00, "OK")
        CONST_TBL_ENTRY(AUD_POL_RESOURCE_FAIL,                   0x01, "FAIL")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_STATUS, 8, BE, "001.000", "")
        CONST_TBL_ENTRY(AUD_POL_STATUS_ACTIVE,                     0x00, "ACTIVE")
        CONST_TBL_ENTRY(AUD_POL_STATUS_INACTIVE,                   0x01, "INACTIVE")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_ENC_DEC_TYPE, 16, BE, "001.000", "")
        CONST_TBL_ENTRY(AUD_POL_DEC_MP3,            0x01, "MP3 decoder")
        CONST_TBL_ENTRY(AUD_POL_DEC_AAC,            0x02, "AAC decoder")
        CONST_TBL_ENTRY(AUD_POL_DEC_EAACPLUS,       0x03, "eACC+ decoder")
        CONST_TBL_ENTRY(AUD_POL_DEC_AMRNB,          0x04, "AMR narrow band decoder")
        CONST_TBL_ENTRY(AUD_POL_DEC_DSP_AMRNB,      0x05, "DSP AMR narrow band decoder")
        CONST_TBL_ENTRY(AUD_POL_DEC_AMRWB,          0x06, "AMR wide band decoder")
        CONST_TBL_ENTRY(AUD_POL_DEC_DSP_AMRWB,      0x07, "DSP AMR wide band decoder")
        CONST_TBL_ENTRY(AUD_POL_DEC_PCM,            0x08, "PCM (non-encoded) decoder")
        CONST_TBL_ENTRY(AUD_POL_ENC_AMRNB,          0x09, "AMR narrow band encoder")
        CONST_TBL_ENTRY(AUD_POL_ENC_DSP_AMRNB,      0x0A, "DSP AMR narrow band encoder")
        CONST_TBL_ENTRY(AUD_POL_ENC_AMRWB,          0x0B, "AMR wide band encoder")
        CONST_TBL_ENTRY(AUD_POL_ENC_DSP_AMRWB,      0x0C, "DSP AMR wide band encoder")
        CONST_TBL_ENTRY(AUD_POL_ENC_PCM,            0x0D, "PCM (non-encoded) decoder")
        CONST_TBL_ENTRY(AUD_POL_ENC_SPEECH_TO_TEXT, 0x0E, "Speech-to-text encoder")
        CONST_TBL_ENTRY(AUD_POL_ENC_TEXT_TO_SPEECH, 0x0F, "Text-to-speech encoder")
        CONST_TBL_ENTRY(AUD_POL_ENC_ACC,            0x10, "ACC encoder")
        CONST_TBL_ENTRY(AUD_POL_SYNTH_MIDI,         0x11, "MIDI synthesizer")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_AUDIO_MODE, 8, BE, "002.000", "")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_HANDPORTABLE,            0x00, "Handportable")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_IHF,                     0x01, "Integrated handsfree")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_HEADPHONES,              0x02, "Headset without MIC")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_HEADSET,                 0x03, "Headset with MIC")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_LOOPSET,                 0x04, "Hearing aid loopset")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_CARKIT,                  0x05, "Car handsfree")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_TTY,                     0x06, "Teletype device")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_MUSICSTAND,              0x07, "Music stand")
        CONST_TBL_ENTRY(AUD_POL_AUDIO_MODE_LINEOUT,                 0x08, "Line out")
        COMMENT(COMMENT_TEXT, "TV OUT")
        CONST_TBL_ENTRY_VER(AUD_POL_AUDIO_MODE_TVOUT,               0x09, "004.000", "")
        COMMENT(COMMENT_TEXT, "Bluetooth")
        CONST_TBL_ENTRY_VER(AUD_POL_AUDIO_MODE_BT,                  0x0A, "004.000", "")
        COMMENT(COMMENT_TEXT, "Stereo Bluetooth")
        CONST_TBL_ENTRY_VER(AUD_POL_AUDIO_MODE_STEREO_BT,           0x0B, "007.000", "")
        COMMENT(COMMENT_TEXT, "FM TX")
        CONST_TBL_ENTRY_VER(AUD_POL_AUDIO_MODE_FMTX,                0x0C, "007.002", "")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_VOLUME_DIRECTION, 8, BE, "007.000", "")
        CONST_TBL_ENTRY(AUD_POL_VOLDIR_INCREASE,                    0x01, "Increase the current volume")
        CONST_TBL_ENTRY(AUD_POL_VOLDIR_DECREASE,                    0x02, "Decrease the current volume")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_PRIVOL_COMMAND, 8, BE, "002.000", "")
        CONST_TBL_ENTRY(AUD_POL_PRIVOL_SUBSCRIBE,                   0x01, "Subscribe")
        CONST_TBL_ENTRY(AUD_POL_PRIVOL_ADJUST,                      0x02, "Adjust")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_DEVICE_TYPE, 8, BE, "002.000", "")
        COMMENT(COMMENT_TEXT, "Change has happened in the own device")
        CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_OWN_DEVICE,              0x00, "004.000", "")
        CONST_TBL_ENTRY(AUD_POL_PRIVOL_DEVICE_BT,                   0x01, "Bluetooth")
        COMMENT(COMMENT_TEXT, "Local connectivity interface accessories")
        CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_DEVICE_LCIF,             0x02, "004.000", "")
        COMMENT(COMMENT_TEXT, "Audio/Video Remote Control Profile used with A2DP devices")
        CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_DEVICE_AVRCP,            0x03, "007.000", "")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_PROPERTY_TYPE, 32, BE, "007.000", "")
        CONST_TBL_ENTRY(AUD_POL_PROPERTY_TYPE_IS_ANALOG,            0x00000001, "Value is TRUE, if audio mode is analog and FALSE if it is digital.")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_PRIVOL_DEVICE_TYPE, AUD_POL_DEVICE_TYPE, "002.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_PRIVOL_DEVICE_BT)
        DER_CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_DEVICE_LCIF, "004.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_DEVICE_AVRCP, "007.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_PRIVOL_NTF_DEVICE_TYPE, AUD_POL_DEVICE_TYPE, "002.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_OWN_DEVICE, "004.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_PRIVOL_DEVICE_BT)
        DER_CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_DEVICE_LCIF, "004.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_DEVICE_AVRCP, "007.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_VOL_DEVICE_TYPE, AUD_POL_DEVICE_TYPE, "004.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_OWN_DEVICE, "004.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_PRIVOL_DEVICE_BT)
        DER_CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_DEVICE_LCIF, "004.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_POL_PRIVOL_DEVICE_AVRCP, "007.000", "")
    DER_CONST_TBL_END

    CONST_TBL_BEGIN(AUD_POL_REASON, 8, BE, "002.000", "")
        CONST_TBL_ENTRY(AUD_POL_OK,                                 0x00, "Ok")
        CONST_TBL_ENTRY(AUD_POL_FAIL,                               0x01, "Fail")
        CONST_TBL_ENTRY(AUD_POL_OUT_OF_RANGE,                       0x02, "Out of range")
        CONST_TBL_ENTRY(AUD_POL_INVALID_DEVICE,                     0x03, "Invalid device")
        CONST_TBL_ENTRY(AUD_POL_NOT_ALLOWED,                        0x04, "Not allowed")
        CONST_TBL_ENTRY(AUD_POL_NOT_SUPPORTED,                      0x05, "Not supported")
        CONST_TBL_ENTRY(AUD_POL_REPLACED_WITH_BEEP,                 0x06, "Replaced with beep")
        CONST_TBL_ENTRY(AUD_POL_BLOCKED_BY_USER,                    0x07, "Blocked by user")
        CONST_TBL_ENTRY(AUD_POL_FEATURE_NOT_ALLOWED,                0x08, "Feature not allowed")
        CONST_TBL_ENTRY(AUD_POL_OUT_OF_MIPS,                        0x09, "Out of MIPS")
        CONST_TBL_ENTRY(AUD_POL_OUT_OF_MEMORY,                      0x0A, "Out of memory")
        CONST_TBL_ENTRY(AUD_POL_HIGHER_PRIORITY,                    0x0B, "Higher priority")
        CONST_TBL_ENTRY(AUD_POL_INVALID_DESCRIPTOR,                 0x0C, "Invalid descriptor")
        CONST_TBL_ENTRY(AUD_POL_ACCESSORY_CHANGE,                   0x0D, "Accessory change")
        CONST_TBL_ENTRY(AUD_POL_CLIENT_REQUEST,                     0x0E, "Client request")
        COMMENT(COMMENT_TEXT, "Not valid application ID")
        CONST_TBL_ENTRY_VER(AUD_POL_NOT_VALID_APPLICATION_ID,       0x0F, "004.000", "" )
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_OK_FAIL_REASON, AUD_POL_REASON, "002.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_OK)
        DER_CONST_TBL_ENTRY(AUD_POL_FAIL)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_PRIVOL_REASON, AUD_POL_REASON, "002.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_OK)
        DER_CONST_TBL_ENTRY(AUD_POL_OUT_OF_RANGE)
        DER_CONST_TBL_ENTRY(AUD_POL_INVALID_DEVICE)
        DER_CONST_TBL_ENTRY(AUD_POL_NOT_ALLOWED)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_VOLUME_REASON, AUD_POL_REASON, "002.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_OK)
        DER_CONST_TBL_ENTRY(AUD_POL_FAIL)
        DER_CONST_TBL_ENTRY(AUD_POL_OUT_OF_RANGE)
        DER_CONST_TBL_ENTRY(AUD_POL_NOT_ALLOWED)
        DER_CONST_TBL_ENTRY(AUD_POL_NOT_SUPPORTED)
        DER_CONST_TBL_ENTRY_VER(AUD_POL_NOT_VALID_APPLICATION_ID, "004.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_MUTE_REASON, AUD_POL_REASON, "002.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_OK)
        DER_CONST_TBL_ENTRY(AUD_POL_FAIL)
        DER_CONST_TBL_ENTRY(AUD_POL_NOT_ALLOWED)
        DER_CONST_TBL_ENTRY_VER(AUD_POL_NOT_VALID_APPLICATION_ID, "004.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_MODE_CHANGE_REASON, AUD_POL_REASON, "002.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_ACCESSORY_CHANGE)
        DER_CONST_TBL_ENTRY(AUD_POL_CLIENT_REQUEST)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(AUD_POL_DESC_REASON, AUD_POL_REASON, "002.000", "")
        DER_CONST_TBL_ENTRY(AUD_POL_OK)
        DER_CONST_TBL_ENTRY(AUD_POL_FAIL)
        DER_CONST_TBL_ENTRY(AUD_POL_REPLACED_WITH_BEEP)
        DER_CONST_TBL_ENTRY(AUD_POL_BLOCKED_BY_USER)
        DER_CONST_TBL_ENTRY(AUD_POL_FEATURE_NOT_ALLOWED)
        DER_CONST_TBL_ENTRY(AUD_POL_OUT_OF_MIPS)
        DER_CONST_TBL_ENTRY(AUD_POL_OUT_OF_MEMORY)
        DER_CONST_TBL_ENTRY(AUD_POL_HIGHER_PRIORITY)
        DER_CONST_TBL_ENTRY(AUD_POL_INVALID_DESCRIPTOR)
        DER_CONST_TBL_ENTRY_VER(AUD_POL_NOT_VALID_APPLICATION_ID, "004.000", "")
    DER_CONST_TBL_END

    /* Sequence structures */

    SEQ_BEGIN(AUD_POL_PROPERTY_SEQ, CREATE_STRUCT, "007.000", "")
        VALUE_CONST( property_type, "Property Type", AUD_POL_PROPERTY_TYPE)
        COMMENT( COMMENT_TEXT, "Value depends what is the type of property")
        VALUE(32, BE, property_value, "Property Value", HEX)
    SEQ_END

/*MESSAGE STRUCTURES*/

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_DESCRIPTOR_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_DESCRIPTOR_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplDescriptorReqSB")
    COMMENT(COMMENT_TEXT, "This SB can be sent by application also to update its information "
                          "(not only when the application registers IN)")
    SB_BEGIN(AUD_POL_APPL_DESCRIPTOR_REQ_SB, "000.001", "")
        AUD_POL_COMMON_SB
        VALUE_CONST( audioband, "audioband", AUD_POL_AUDIOBAND)
        FILLER_EX(filler1, 8, 1)
        VALUE_CONST( appl_type, "application type", AUD_POL_APPL_TYPE)
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
        VALUE_CONST( flags, "flags", AUD_POL_FLAGS)
        VALUE_CONST( routing, "routing", AUD_POL_ROUTING)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_ADD_STREAM_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_ADD_STREAM_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplAddStreamReqSB")
    SB_BEGIN(AUD_POL_APPL_ADD_STREAM_REQ_SB, "000.001", "")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "Number of stream's to be created")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 10)
        VALUE(8, BE, nbr_of_streams, "Number of streams", DEC)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_REMOVE_STREAM_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_REMOVE_STREAM_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplRemoveStreamReqSB")
    SB_BEGIN(AUD_POL_APPL_REMOVE_STREAM_REQ_SB, "000.001", "")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "stream id, which is to be removed")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_REMOVE_APPL_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_REMOVE_APPL_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplRemoveApplReqSB")
    COMMENT(COMMENT_TEXT, "This will deallocate all the streams, there is no need to send the _REMOVE_STREAM_SB as well.")
    SB_BEGIN(AUD_POL_APPL_REMOVE_APPL_REQ_SB, "000.001", "")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "application id, which is to be removed")
        VALUE(16, BE, application_id, "Application ID", DEC)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_VOL_CONTROL_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOL_CONTROL_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolControlReqSB")
    SB_BEGIN(AUD_POL_VOL_CONTROL_REQ_SB, "000.001", "001.000")
        AUD_POL_COMMON_SB
        VALUE_CONST( appl_type, "application type", AUD_POL_APPL_TYPE)
        COMMENT( COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        VALUE(16, BE, volume, "volume level", DEC)
        VALUE_CONST( mute, "mute", AUD_POL_VOL_CONTROL_MUTING)
        FILLER_EX(filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOL_CONTROL_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolControlReqSB")
    SB_BEGIN(AUD_POL_VOL_CONTROL_REQ_SB, "001.000", "004.000")
        AUD_POL_COMMON_SB
        VALUE_CONST( appl_type, "application type", AUD_POL_APPL_TYPE)
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
        COMMENT( COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_STRING(PROPERTY_ITEM_EXCEPTIONAL_VALUE , "AUD_POL_VOL_LEVEL_NOT_RELEVANT")
        VALUE(16, BE, volume, "volume level", DEC)
        VALUE_CONST( mute, "mute", AUD_POL_VOL_CONTROL_MUTING)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 16, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOL_CONTROL_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolControlReqSB")
    SB_BEGIN(AUD_POL_VOL_CONTROL_REQ_SB, "004.000", "")
        AUD_POL_COMMON_SB
        FILLER_EX(filler1, 16, 1)
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
        COMMENT( COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        VALUE(16, BE, volume, "volume level", DEC)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_MUTE_CONTROL_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_MUTE_CONTROL_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolMuteControlReqSB")
    SB_BEGIN(AUD_POL_MUTE_CONTROL_REQ_SB, "004.000", "005.000")
        AUD_POL_COMMON_SB
        VALUE_CONST( mic_mute, "Microphone Mute", AUD_POL_MIC_MUTING)
        VALUE_CONST( speaker_mute, "Speaker Mute", AUD_POL_SPEAKER_MUTING)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_MUTE_CONTROL_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolMuteControlReqSB")
    SB_BEGIN(AUD_POL_MUTE_CONTROL_REQ_SB, "005.000", "")
        AUD_POL_COMMON_SB
        FILLER_EX(filler1, 16, 1)
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
        VALUE_CONST( mic_mute, "Microphone Mute", AUD_POL_MIC_MUTING)
        VALUE_CONST( speaker_mute, "Speaker Mute", AUD_POL_SPEAKER_MUTING)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_VOLUME_CHANGE_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_CHANGE_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolChangeReqSB")
    SB_BEGIN(AUD_POL_VOLUME_CHANGE_REQ_SB, "007.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST( volume_direction, "Volume direction", AUD_POL_VOLUME_DIRECTION)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_PRIVOL_CHANGE_NTF_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_PRIVOL_CHANGE_NTF_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolPriVolChangeNtfSB")
    SB_BEGIN(AUD_POL_PRIVOL_CHANGE_NTF_SB, "007.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST( volume_direction, "Volume direction", AUD_POL_VOLUME_DIRECTION)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_STREAM_VOLUME_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STREAM_VOLUME_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStreamVolReqSB")
    SB_BEGIN(AUD_POL_STREAM_VOLUME_REQ_SB, "007.000", "")
        AUD_POL_COMMON_SB
        FILLER_EX(filler1, 16, 1)
        VALUE(16, BE, stream_id, "Stream ID", DEC)
        COMMENT( COMMENT_TEXT, "Stream volume is percentage of application volume or preference volume. ")
        COMMENT( COMMENT_TEXT, "Preference volume is used only if application volume is not set. 100% = 1000.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        VALUE(16, BE, volume, "volume level", DEC)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_STREAM_MUTE_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STREAM_MUTE_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStreamMuteReqSB")
    SB_BEGIN(AUD_POL_STREAM_MUTE_REQ_SB, "007.001", "")
        AUD_POL_COMMON_SB
        FILLER_EX(filler1, 16, 1)
        VALUE(16, BE, stream_id, "Stream ID", DEC)
        COMMENT( COMMENT_TEXT, "TRUE=Muted, FALSE=Not muted")
		VALUE_CONST( mute_status, "Mute status", TRUE_FALSE )
        FILLER_EX(filler2, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolNbrVolLevelReqSB")
    SB_BEGIN(AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB, "007.000", "")
        AUD_POL_COMMON_SB
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        VALUE(16, BE, volume, "Number of volume levels", DEC)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_CONTROL_PRIORITY_NTF_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_CONTROL_PRIORITY_NTF_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolControlPriorityNtfSB")
    SB_BEGIN(AUD_POL_CONTROL_PRIORITY_NTF_SB, "000.001", "")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        VALUE_CONST( appl_type, "application type", AUD_POL_APPL_TYPE)
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_DESCRIPTOR_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_DESCRIPTOR_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplDescriptorRespSB")
    SB_BEGIN(AUD_POL_APPL_DESCRIPTOR_RESP_SB, "000.001", "002.000")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "not yet valid, will be used something like 0 = OK, otherwise error code")
        VALUE(8, BE, reason, "reason", DEC)
        FILLER_EX(filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_DESCRIPTOR_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplDescriptorRespSB")
    SB_BEGIN(AUD_POL_APPL_DESCRIPTOR_RESP_SB, "002.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "reason", AUD_POL_DESC_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_ADD_STREAM_SEQ */
    /* -------------------------------------------------------------------- */

    SEQ_BEGIN(AUD_POL_APPL_ADD_STREAM_SEQ, DONT_CREATE_STRUCT, "000.001", "")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
    SEQ_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_ADD_STREAM_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_ADD_STREAM_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplAddStreamRespSB")
    SB_BEGIN(AUD_POL_APPL_ADD_STREAM_RESP_SB, "000.001", "002.000")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "not yet valid, will be used something like 0 = OK, otherwise error code")
        VALUE(8, BE, reason, "reason", DEC)
        COMMENT( COMMENT_TEXT, "Number of streams created")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 10)
        REFERENCE(8, BE, nbr_of_streams, "Number of streams", N)
        SEQ_OF_REF(stream_id, "list of stream_ids", AUD_POL_APPL_ADD_STREAM_SEQ, N, ISIHDR_MARKER_ANYSIZE )
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_ADD_STREAM_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplAddStreamRespSB")
    SB_BEGIN(AUD_POL_APPL_ADD_STREAM_RESP_SB, "002.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "Reason", AUD_POL_OK_FAIL_REASON)
        COMMENT( COMMENT_TEXT, "Number of streams created")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 10)
        REFERENCE(8, BE, nbr_of_streams, "Number of streams", N)
        SEQ_OF_REF(stream_id, "list of stream_ids", AUD_POL_APPL_ADD_STREAM_SEQ, N, ISIHDR_MARKER_ANYSIZE )
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_REMOVE_STREAM_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_REMOVE_STREAM_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplRemoveStreamRespSB")
    SB_BEGIN(AUD_POL_APPL_REMOVE_STREAM_RESP_SB, "000.001", "002.000")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "not yet valid, will be used something like 0 = OK, otherwise error code")
        VALUE(8, BE, reason, "reason", DEC)
        FILLER_EX(filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_REMOVE_STREAM_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplRemoveStreamRespSB")
    SB_BEGIN(AUD_POL_APPL_REMOVE_STREAM_RESP_SB, "002.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "Reason", AUD_POL_OK_FAIL_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_REMOVE_APPL_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_REMOVE_APPL_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplRemoveApplRespSB")
    SB_BEGIN(AUD_POL_APPL_REMOVE_APPL_RESP_SB, "000.001", "002.000")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "application id, which is removed")
        VALUE(16, BE, application_id, "Application ID", DEC)
        COMMENT( COMMENT_TEXT, "not yet valid, will be used something like 0 = OK, otherwise error code")
        VALUE(8, BE, reason, "reason", DEC)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 16, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_REMOVE_APPL_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplRemoveApplRespSB")
    SB_BEGIN(AUD_POL_APPL_REMOVE_APPL_RESP_SB, "002.000", "")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "application id, which is removed")
        VALUE(16, BE, application_id, "Application ID", DEC)
        VALUE_CONST(reason, "Reason", AUD_POL_OK_FAIL_REASON)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 16, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_VOL_CONTROL_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOL_CONTROL_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolControlRespSB")
    SB_BEGIN(AUD_POL_VOL_CONTROL_RESP_SB, "000.001", "002.000")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "not yet valid, will be used something like 0 = OK, otherwise error code")
        VALUE(8, BE, reason, "reason", DEC)
        FILLER_EX(filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOL_CONTROL_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolControlRespSB")
    SB_BEGIN(AUD_POL_VOL_CONTROL_RESP_SB, "002.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "Reason", AUD_POL_VOLUME_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_MUTE_CONTROL_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_MUTE_CONTROL_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolMuteControlRespSB")
    SB_BEGIN(AUD_POL_MUTE_CONTROL_RESP_SB, "004.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "Reason", AUD_POL_MUTE_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_VOLUME_CHANGE_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_CHANGE_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolChangeRespSB")
    SB_BEGIN(AUD_POL_VOLUME_CHANGE_RESP_SB, "007.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "Reason", AUD_POL_VOLUME_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /*  AUD_POL_STREAM_VOLUME_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STREAM_VOLUME_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStreamVolRespSB")
    SB_BEGIN(AUD_POL_STREAM_VOLUME_RESP_SB, "007.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "Reason", AUD_POL_VOLUME_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /*  AUD_POL_STREAM_MUTE_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STREAM_MUTE_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStreamMuteRespSB")
    SB_BEGIN(AUD_POL_STREAM_MUTE_RESP_SB, "007.001", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "Reason", AUD_POL_OK_FAIL_REASON)
        FILLER_EX(filler1, 8, 1)
	SB_END

    /* -------------------------------------------------------------------- */
    /*  AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolNbrVolLevelRespSB")
    SB_BEGIN(AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB, "007.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "Reason", AUD_POL_VOLUME_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_RESOURCE_REQ_SB */
    /* -------------------------------------------------------------------- */

    COMMENT(COMMENT_TEXT, "Using either the mcycles or percentage field is enough. "
                          "Preferred way is to use mcycles.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_RESOURCE_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolResourceReqSB")
    SB_BEGIN(AUD_POL_RESOURCE_REQ_SB, "001.000", "")
        AUD_POL_COMMON_SB
        COMMENT(COMMENT_TEXT, "Encoder or decoder type")
        VALUE_CONST( enc_dec_type, "Encoder or decoder type", AUD_POL_ENC_DEC_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT(COMMENT_TEXT, "Mega cycles")
        VALUE(16, BE, mcycles, "MCycles", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT(COMMENT_TEXT, "percentage (range 0 - 1000, meaning 45.5% is 455)")
        VALUE(16, BE, percentage, "Percentage", DEC)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_RESOURCE_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_RESOURCE_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolResourceRespSB")
    SB_BEGIN(AUD_POL_RESOURCE_RESP_SB, "001.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(reason, "reason", AUD_POL_RESOURCE_REASON)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_VOLUME_IND_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_IND_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolumeIndSB")
    SB_BEGIN(AUD_POL_VOLUME_IND_SB, "001.000", "004.000")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        VALUE_CONST( appl_type, "application type", AUD_POL_APPL_TYPE)
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
        COMMENT( COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        VALUE(16, BE, volume, "volume level", DEC)
        VALUE_CONST( mute, "mute", AUD_POL_VOL_CONTROL_MUTING)
        FILLER_EX(filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_IND_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolumeIndSB")
    SB_BEGIN(AUD_POL_VOLUME_IND_SB, "004.000", "")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        FILLER_EX(filler1, 16, 1)
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
        COMMENT( COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        VALUE(16, BE, volume, "volume level", DEC)
        VALUE_CONST(device_type, "Device type", AUD_POL_VOL_DEVICE_TYPE)
        FILLER_EX(filler2, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_VOLUME_CHANGE_IND_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_CHANGE_IND_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolumeChangeIndSB")
    SB_BEGIN(AUD_POL_VOLUME_CHANGE_IND_SB, "007.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(volume_direction, "Volume direction", AUD_POL_VOLUME_DIRECTION)
        VALUE_CONST(device_type, "Device type", AUD_POL_VOL_DEVICE_TYPE)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_MUTE_IND_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_MUTE_IND_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolMuteIndSB")
    SB_BEGIN(AUD_POL_MUTE_IND_SB, "007.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
        VALUE_CONST( mic_mute, "Microphone Mute", AUD_POL_MIC_MUTING)
        VALUE_CONST( speaker_mute, "Speaker Mute", AUD_POL_SPEAKER_MUTING)
        FILLER_EX(filler2, 16, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_STATUS_IND_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STATUS_IND_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStatusIndSB")
    SB_BEGIN(AUD_POL_STATUS_IND_SB, "001.000", "")
        AUD_POL_COMMON_SB
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        VALUE_CONST( appl_type, "application type", AUD_POL_APPL_TYPE)
        VALUE_CONST( appl_pref, "application preference", AUD_POL_APPL_PREF)
        COMMENT(COMMENT_TEXT, "Whenever some application registers IN and gets permission to start the status is ACTIVE. "
                              "When the application registers OUT the status is INACTIVE, "
                              "or if the application is stopped or paused, it is also INACTIVE. "
                              "Also when application is resumed it is again ACTIVE")
        VALUE_CONST( status, "status", AUD_POL_STATUS)
        FILLER_EX(filler1, 8, 1)
        FILLER_EX(filler2, 16, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_MODE_IND_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_MODE_IND_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolModeIndSB")
    SB_BEGIN(AUD_POL_MODE_IND_SB, "002.000", "007.000")
        AUD_POL_COMMON_SB
        COMMENT(COMMENT_TEXT, "New audio mode")
        VALUE_CONST(audio_mode, "Audio mode", AUD_POL_AUDIO_MODE)
        COMMENT(COMMENT_TEXT, "Reason for audio mode change")
        VALUE_CONST(reason, "Reason", AUD_POL_MODE_CHANGE_REASON)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_MODE_IND_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolModeIndSB")
    SB_BEGIN(AUD_POL_MODE_IND_SB, "007.000", "")
        AUD_POL_COMMON_SB
        COMMENT(COMMENT_TEXT, "New audio mode")
        VALUE_CONST(audio_mode, "Audio mode", AUD_POL_AUDIO_MODE)
        COMMENT(COMMENT_TEXT, "Reason for audio mode change")
        VALUE_CONST(reason, "Reason", AUD_POL_MODE_CHANGE_REASON)
        VALUE_CONST(capabilities, "Capabilities", AUD_POL_CAPABILITY_RESTRICTIONS)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_MODE_RESP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_MODE_RESP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolModeRespSB")
    SB_BEGIN(AUD_POL_MODE_RESP_SB, "007.000", "")
        AUD_POL_COMMON_SB
        COMMENT(COMMENT_TEXT, "Current audio mode")
        VALUE_CONST(audio_mode, "Audio mode", AUD_POL_AUDIO_MODE)
        FILLER_EX(filler1, 8, 1)
        VALUE_CONST(capabilities, "Capabilities", AUD_POL_CAPABILITY_RESTRICTIONS)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_STATUS_INFO_REQ_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STATUS_INFO_REQ_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStatusInfoReqSB")
    SB_BEGIN(AUD_POL_STATUS_INFO_REQ_SB, "007.000", "")
        AUD_POL_COMMON_SB
        VALUE_CONST(status_type, "Status type", AUD_POL_STATUS_TYPE)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_MODE_PROPERTIES_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_MODE_PROPERTIES_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolModePropertiesSB")
    SB_BEGIN(AUD_POL_MODE_PROPERTIES_SB, "007.000", "")
        AUD_POL_COMMON_SB
        FILLER_EX(filler1, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1) /* Max is the number of the possible different properties */
        REFERENCE(8, BE, nbr_of_properties, "N", N)
        SEQ_OF_REF(array, "Properties array", AUD_POL_PROPERTY_SEQ, N, ISIHDR_RESERVE_SPACE)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_AUDIO_EFFECT_PHAP_SB */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_AUDIO_EFFECT_PHAP_SB_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolAudioEffectSB")
    SB_BEGIN(AUD_POL_AUDIO_EFFECT_PHAP_SB, "007.000", "")
        AUD_POL_COMMON_SB
        COMMENT(COMMENT_TEXT, "If PHAP is activated the status needs to be ACTIVE. "
                              "When PHAP is deactivated the status is INACTIVE.")
        VALUE_CONST( status, "status", AUD_POL_STATUS)
        FILLER_EX(filler1, 8, 1)
    SB_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_REQ / AUD_POL_APPL_RESP */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_REQ_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplReq")
    MSG_BEGIN(AUD_POL_APPL_REQ, MESSAGE_REQ, "000.001", "")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "New application id is created with value AUD_POL_APPL_ID_NOT_DEFINED, otherwise existing id is used")
        VALUE(16, BE, application_id, "Application ID", DEC)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_APPL_DESCRIPTOR_REQ_SB)
            SB_LST_ENTRY(AUD_POL_APPL_ADD_STREAM_REQ_SB)
            SB_LST_ENTRY(AUD_POL_APPL_REMOVE_STREAM_REQ_SB)
            SB_LST_ENTRY(AUD_POL_APPL_REMOVE_APPL_REQ_SB)
            SB_LST_ENTRY_VER(AUD_POL_VOL_CONTROL_REQ_SB, "002.000", "")
            SB_LST_ENTRY_VER(AUD_POL_MUTE_CONTROL_REQ_SB, "004.000", "")
            SB_LST_ENTRY_VER(AUD_POL_STATUS_INFO_REQ_SB, "007.000", "")
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_RESP_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplResp")
    MSG_BEGIN(AUD_POL_APPL_RESP, MESSAGE_RESP, "000.001", "002.000")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        FILLER_EX(filler1, 16, 1)
        COMMENT( COMMENT_TEXT, "not yet valid, will be used something like 0 = OK, otherwise error code")
        VALUE(8, BE, reason, "reason", DEC)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_APPL_DESCRIPTOR_RESP_SB)
            SB_LST_ENTRY(AUD_POL_APPL_ADD_STREAM_RESP_SB)
            SB_LST_ENTRY(AUD_POL_APPL_REMOVE_STREAM_RESP_SB)
            SB_LST_ENTRY(AUD_POL_APPL_REMOVE_APPL_RESP_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_RESP_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplResp")
    MSG_BEGIN(AUD_POL_APPL_RESP, MESSAGE_RESP, "002.000", "")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        FILLER_EX(filler1, 16, 1)
        COMMENT( COMMENT_TEXT, "Ok/Fail. More detailed error codes in sub blocks.")
        VALUE_CONST(reason, "reason", AUD_POL_OK_FAIL_REASON)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_APPL_DESCRIPTOR_RESP_SB)
            SB_LST_ENTRY(AUD_POL_APPL_ADD_STREAM_RESP_SB)
            SB_LST_ENTRY(AUD_POL_APPL_REMOVE_STREAM_RESP_SB)
            SB_LST_ENTRY(AUD_POL_APPL_REMOVE_APPL_RESP_SB)
            SB_LST_ENTRY(AUD_POL_VOL_CONTROL_RESP_SB)
            SB_LST_ENTRY_VER(AUD_POL_MUTE_CONTROL_RESP_SB, "004.000", "")
            SB_LST_ENTRY_VER(AUD_POL_MODE_RESP_SB, "007.000", "")
            SB_LST_ENTRY_VER(AUD_POL_MODE_PROPERTIES_SB, "007.000", "")
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_POL_APPL_REQ, AUD_POL_APPL_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_POL_VOLUME_REQ / AUD_POL_VOLUME_RESP */
    /* -------------------------------------------------------------------- */

   PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_REQ_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolReq")
    MSG_BEGIN(AUD_POL_VOLUME_REQ, MESSAGE_REQ, "000.001", "")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "application id")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_STRING(PROPERTY_ITEM_EXCEPTIONAL_VALUE , "AUD_POL_APPL_ID_NOT_DEFINED")
        VALUE(16, BE, application_id, "Application ID", DEC)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_VOL_CONTROL_REQ_SB)
            SB_LST_ENTRY_VER(AUD_POL_MUTE_CONTROL_REQ_SB, "004.000", "")
            SB_LST_ENTRY_VER(AUD_POL_VOLUME_CHANGE_REQ_SB, "007.000", "")
            SB_LST_ENTRY_VER(AUD_POL_STREAM_VOLUME_REQ_SB, "007.000", "")
			SB_LST_ENTRY_VER(AUD_POL_STREAM_MUTE_REQ_SB, "007.001", "")
            SB_LST_ENTRY_VER(AUD_POL_NBROF_VOLUME_LEVELS_REQ_SB, "007.000", "")
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_RESP_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolResp")
    MSG_BEGIN(AUD_POL_VOLUME_RESP, MESSAGE_RESP, "000.001", "002.000")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        FILLER_EX(filler1, 16, 1)
        COMMENT( COMMENT_TEXT, "not yet valid, will be used something like 0 = OK, otherwise error code. ")
        VALUE(8, BE, reason, "reason", DEC)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_VOL_CONTROL_RESP_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_RESP_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolResp")
    MSG_BEGIN(AUD_POL_VOLUME_RESP, MESSAGE_RESP, "002.000", "")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "Application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        FILLER_EX(filler1, 16, 1)
        COMMENT( COMMENT_TEXT, "Ok/Fail. More detailed error code in sub block.")
        VALUE_CONST(reason, "Reason", AUD_POL_OK_FAIL_REASON)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_VOL_CONTROL_RESP_SB)
            SB_LST_ENTRY_VER(AUD_POL_MUTE_CONTROL_RESP_SB, "004.000", "")
            SB_LST_ENTRY_VER(AUD_POL_VOLUME_CHANGE_RESP_SB, "007.000", "")
            SB_LST_ENTRY_VER(AUD_POL_STREAM_VOLUME_RESP_SB, "007.000", "")
			SB_LST_ENTRY_VER(AUD_POL_STREAM_MUTE_RESP_SB, "007.001", "")
            SB_LST_ENTRY_VER(AUD_POL_NBROF_VOLUME_LEVELS_RESP_SB, "007.000", "")
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_POL_VOLUME_REQ, AUD_POL_VOLUME_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_POL_CONTROL_NTF */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_CONTROL_NTF_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolControlNtf")
    MSG_BEGIN(AUD_POL_CONTROL_NTF, MESSAGE_NTF, "000.001", "001.000")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        VALUE_CONST( directive, "directive", AUD_POL_DIRECTIVE)
        VALUE_CONST( reason, "reason", AUD_POL_DIRECTIVE_REASON)
        FILLER_EX(filler1, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_CONTROL_PRIORITY_NTF_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_CONTROL_NTF_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolControlNtf")
    MSG_BEGIN(AUD_POL_CONTROL_NTF, MESSAGE_NTF, "001.000", "006.000")
        AUD_POL_MSG_HDR
        VALUE_CONST( directive, "directive", AUD_POL_DIRECTIVE)
        VALUE_CONST( reason, "reason", AUD_POL_DIRECTIVE_REASON)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_CONTROL_PRIORITY_NTF_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_CONTROL_NTF_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolControlNtf")
    MSG_BEGIN(AUD_POL_CONTROL_NTF, MESSAGE_NTF, "006.000", "")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        VALUE_CONST( directive, "directive", AUD_POL_DIRECTIVE)
        VALUE_CONST( reason, "reason", AUD_POL_DIRECTIVE_REASON)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_CONTROL_PRIORITY_NTF_SB)
        SB_LST_REF_END
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_APPL_NTF */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_APPL_NTF_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolApplNtf")
    COMMENT( COMMENT_TEXT, "By using this message, applications can tell to Audio Policy when certain command has been completed.")
    MSG_BEGIN(AUD_POL_APPL_NTF, MESSAGE_NTF, "000.001", "")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "application id")
        VALUE(16, BE, application_id, "Application ID", DEC)
        VALUE_CONST( directive, "directive", AUD_POL_DIRECTIVE)
        VALUE_CONST( status, "status", AUD_POL_DIRECTIVE_STATUS)
        FILLER_EX(filler1, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
        SB_LST_REF_END
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_RESOURCE_REQ / AUD_POL_RESOURCE_RESP */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_RESOURCE_REQ_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolResourceReq")
    MSG_BEGIN(AUD_POL_RESOURCE_REQ, MESSAGE_REQ, "001.000", "")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "stream id")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_RESOURCE_REQ_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_RESOURCE_RESP_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolResourceResp")
    MSG_BEGIN(AUD_POL_RESOURCE_RESP, MESSAGE_RESP, "001.000", "")
        AUD_POL_MSG_HDR
        COMMENT( COMMENT_TEXT, "stream id")
        VALUE(16, BE, stream_id, "Stream ID", DEC)
        FILLER_EX(filler1, 16, 1)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_RESOURCE_RESP_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_POL_RESOURCE_REQ, AUD_POL_RESOURCE_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_POL_STATUS_IND */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STATUS_IND_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStatusInd")
    COMMENT( COMMENT_TEXT, "This message is sent to all registered applications when something happens in Audio Policy.")
    MSG_BEGIN(AUD_POL_STATUS_IND, MESSAGE_NTF, "001.000", "")
        AUD_POL_MSG_HDR
        FILLER_EX(filler1, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_STATUS_IND_SB)
            SB_LST_ENTRY_VER(AUD_POL_MODE_IND_SB, "002.000", "")
            SB_LST_ENTRY_VER(AUD_POL_MODE_PROPERTIES_SB, "007.000", "")
        SB_LST_REF_END
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_VOLUME_IND */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_VOLUME_IND_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolVolumeInd")
    MSG_BEGIN(AUD_POL_VOLUME_IND, MESSAGE_REQ, "001.000", "")
        AUD_POL_MSG_HDR
        FILLER_EX(filler1, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_VOLUME_IND_SB)
            SB_LST_ENTRY(AUD_POL_VOLUME_CHANGE_IND_SB)
            SB_LST_ENTRY(AUD_POL_MUTE_IND_SB)
        SB_LST_REF_END
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_PRIVOL_REQ/AUD_POL_PRIVOL_RESP */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_PRIVOL_REQ_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolPrivolReq")
    MSG_BEGIN(AUD_POL_PRIVOL_REQ, MESSAGE_REQ, "002.000", "007.000")
        AUD_POL_MSG_HDR
        VALUE_CONST(command,     "Command",     AUD_POL_PRIVOL_COMMAND)
        VALUE_CONST(device_type, "Device type", AUD_POL_PRIVOL_DEVICE_TYPE)
        COMMENT(COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        VALUE(16, BE, volume, "Volume level", DEC)
        FILLER_EX(filler1, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_PRIVOL_REQ_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolPrivolReq")
    MSG_BEGIN(AUD_POL_PRIVOL_REQ, MESSAGE_REQ, "007.000", "")
        AUD_POL_MSG_HDR
        VALUE_CONST(command,     "Command",     AUD_POL_PRIVOL_COMMAND)
        VALUE_CONST(device_type, "Device type", AUD_POL_PRIVOL_DEVICE_TYPE)
        COMMENT(COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_STRING(PROPERTY_ITEM_EXCEPTIONAL_VALUE, "AUD_POL_VALUE_NOT_VALID")
        VALUE(16, BE, volume, "Volume level", DEC)
        FILLER_EX(filler1, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY_VER(AUD_POL_VOLUME_CHANGE_REQ_SB, "007.000", "")
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_PRIVOL_RESP_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolPrivolResp")
    MSG_BEGIN(AUD_POL_PRIVOL_RESP, MESSAGE_RESP, "002.000", "")
        AUD_POL_MSG_HDR
        VALUE_CONST(reason,   "Reason", AUD_POL_PRIVOL_REASON)
        FILLER_EX(filler1,  8, 1)
    MSG_END

    MSG_PAIR(AUD_POL_PRIVOL_REQ, AUD_POL_PRIVOL_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_POL_PRIVOL_NTF */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_PRIVOL_NTF_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolPrivolNtf")
    MSG_BEGIN(AUD_POL_PRIVOL_NTF, MESSAGE_REQ, "002.000", "007.000")
        AUD_POL_MSG_HDR
        VALUE_CONST(device_type, "Device type", AUD_POL_PRIVOL_NTF_DEVICE_TYPE)
        FILLER_EX(filler1,  8, 1)
        COMMENT(COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        VALUE(16, BE, volume, "Volume level", DEC)
        FILLER_EX(filler2, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_PRIVOL_NTF_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolPrivolNtf")
    MSG_BEGIN(AUD_POL_PRIVOL_NTF, MESSAGE_REQ, "007.000", "")
        AUD_POL_MSG_HDR
        VALUE_CONST(device_type, "Device type", AUD_POL_PRIVOL_NTF_DEVICE_TYPE)
        FILLER_EX(filler1,  8, 1)
        COMMENT(COMMENT_TEXT, "100% = 1000")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_STRING(PROPERTY_ITEM_EXCEPTIONAL_VALUE, "AUD_POL_VALUE_NOT_VALID")
        VALUE(16, BE, volume, "Volume level", DEC)
        FILLER_EX(filler2, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY_VER(AUD_POL_PRIVOL_CHANGE_NTF_SB, "007.000", "")
        SB_LST_REF_END
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_STATUS_REQ/AUD_POL_STATUS_RESP */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STATUS_REQ_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStatusReq")
    MSG_BEGIN(AUD_POL_STATUS_REQ, MESSAGE_REQ, "007.000", "")
        AUD_POL_MSG_HDR
        VALUE_CONST(status_type, "Status type", AUD_POL_STATUS_TYPE)
        FILLER_EX(filler1, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_STATUS_RESP_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolStatusResp")
    MSG_BEGIN(AUD_POL_STATUS_RESP, MESSAGE_RESP, "007.000", "")
        AUD_POL_MSG_HDR
        VALUE_CONST(reason,   "Reason", AUD_POL_OK_FAIL_REASON)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_MODE_RESP_SB)
            SB_LST_ENTRY(AUD_POL_MODE_PROPERTIES_SB)
            SB_LST_ENTRY_VER(AUD_POL_STATUS_IND_SB, "007.001", "")
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_POL_STATUS_REQ, AUD_POL_STATUS_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_POL_AUDIO_EFFECT_REQ/AUD_POL_AUDIO_EFFECT_RESP */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_AUDIO_EFFECT_REQ_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolAudioEffectReq")
    MSG_BEGIN(AUD_POL_AUDIO_EFFECT_REQ, MESSAGE_REQ, "007.000", "")
        AUD_POL_MSG_HDR
        FILLER_EX(filler1, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_AUDIO_EFFECT_PHAP_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_AUDIO_EFFECT_RESP_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolAudioEffectResp")
    MSG_BEGIN(AUD_POL_AUDIO_EFFECT_RESP, MESSAGE_RESP, "007.000", "")
        AUD_POL_MSG_HDR
        VALUE_CONST(reason,   "Reason", AUD_POL_OK_FAIL_REASON)
        FILLER_EX(filler1, 8, 1)
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_POL_AUDIO_EFFECT_IND */
    /* -------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_POL_AUDIO_EFFECT_IND_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudPolAudioEffectInd")
    MSG_BEGIN(AUD_POL_AUDIO_EFFECT_IND, MESSAGE_REQ, "007.000", "")
        AUD_POL_MSG_HDR
        FILLER_EX(filler1, 8, 1)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_POL_AUDIO_EFFECT_PHAP_SB)
        SB_LST_REF_END
    MSG_END

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */

/* End of file aud_pol_isi_m.h */


