/*
NOKIA MOBILE PHONES
R&D Copenhagen
ISA Operations



            garbage_isi_m.h
            -------------------
            SW include - ANSI C



Continuus Ref:
--------------
Project:          [CM_PROJECT_NAME]

%name:            autogen_garbage.h %
%version:         co1pctls#015.011 %
%cvtype:          incl %
%instance:        co_pctls_1 %

Document code:    -

Copyright(c) Nokia Corporation. All rights reserved.

Change History:

VERSION     : 015.011           DRAFT           24-Nov-2004  Stig Holmsten Eliasen
REASON      : Update
REFERENCE   : -
DESCRIPTION : Constants added, const table extended, SETT_RESET_PERFORMED_IND added

VERSION     : 015.010           DRAFT           17-Feb-2004  Nikolaj Sloth
REASON      : Update
REFERENCE   : -
DESCRIPTION : New settings for interface (Shutdown Tone, Idle Font Color, and
              Second Display Wallpaper)

VERSION     : 015.009           DRAFT           17-Feb-2004  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the macro file
*/

/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogen
   

    1.2    Functional description

    This file is the message definition file for the garbage server


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

#ifndef _GARBAGE_ISI_M_H_
#define _GARBAGE_ISI_M_H_


/*  3    CONSTANTS */

/* Message ID's */
#define SETT_VALUE_IND			    0x01
#define SETT_VALUE_GET_REQ		    0x02
#define SETT_VALUE_GET_RESP		    0x03
#define SETT_VALUE_SET_REQ		    0x04
#define SETT_VALUE_SET_RESP		    0x05
#define SETT_RESET_PERFORMED_IND    0x06

/* Sub block ID's */


/* Other constants */
#define SETTING_VALUE_MAX_LENGHT 886

/*  4    MACROS */

#define SETT_MSG_HDR \
    VALUE(8, BE, transaction_number, "Transaction ID", DEC) \
    REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
    

/* TODO: Change the version whenever the interface is changed */
/* default ISI version */

#ifndef GARBAGE_ISI_VERSION
#define GARBAGE_ISI_VERSION
#define GARBAGE_ISI_VERSION_Z      15
#define GARBAGE_ISI_VERSION_Y      18
#endif

/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "R&D Copenhagen")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "ISA Operations")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Tim Laursen")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIALITY")

/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                      "Garbage Server Message Definitions")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "srvgarbage_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou_gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_interface/ISI/IAM")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,  "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "co_ui#5")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, "")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "ISI Garbage Server Message Descriptions")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_garbage_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou_gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS-ou_gif#1.1.1")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "GIF_SPECS/IAM")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

RES_BEGIN(RESOURCE_ISI, PN_GARBAGE, SRVGARBAGE, "Garbage Server", 
    RES_VERSION_STRING(GARBAGE_ISI_VERSION_Z, GARBAGE_ISI_VERSION_Y), TRUE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    /* TODO: Add version history block every time the interface is changed */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Update")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "-")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-Nov-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Tim Laursen")
    COMMENT(COMMENT_TEXT, "New settings for interface and new indication (SETT_RESET_PERFORMED_IND) ")
    ISI_VERSION_HISTORY("015.018")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Update")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "-")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Feb-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Sloth")
    COMMENT(COMMENT_TEXT, "New settings for interface (Shutdown Tone, Idle Font Color, and"
             "Second Display Wallpaper) ")
    ISI_VERSION_HISTORY("015.010")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "-")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "-")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-Feb-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Sloth")
    COMMENT(COMMENT_TEXT, "First autogenerated version")
    ISI_VERSION_HISTORY("015.009")


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

    COMMENT(COMMENT_TEXT, 
        "These constants are here for backward compatibility")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(GARBAGE_ISI_VERSION_ZZZ, GARBAGE_ISI_VERSION_Z)
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(GARBAGE_ISI_VERSION_YYY, GARBAGE_ISI_VERSION_Y)

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SETT_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(SETT_OK,					0, "")
        CONST_TBL_ENTRY(SETT_BAD_ID,				1, "")
        CONST_TBL_ENTRY(SETT_BAD_VALUE,			    2, "")
        CONST_TBL_ENTRY(SETT_PMM_FAIL,			    3, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SETT_ID, 8, BE, "", "")
        CONST_TBL_ENTRY(ALS_STATE_ID,							       0, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UWN_TEXT_RAM_LENGTH                       45")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(UWN_TEXT_ID,								   1, "")

        CONST_TBL_ENTRY(CALL_TIMER_SELECTED_STATE_ID,			       2, "")
        CONST_TBL_ENTRY(LAST_CALL_TIME_STATE_ID,					   3, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define ONE_KEY_DIAL_OPTION_OFF                   0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define ONE_KEY_DIAL_OPTION_ON                    1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(ONE_KEY_DIAL_OPTION_ID,					       4, "")

        CONST_TBL_ENTRY(ANYKEY_SELECT_STATE_ID,					       5, "")
        CONST_TBL_ENTRY(DISPLAY_TEXT_LANGUAGE_SELECT_STATE_ID,	       6, "")
        CONST_TBL_ENTRY(DISPLAY_TEXT_LANGUAGE_SETTING_STATE_ID,	       7, "")
        CONST_TBL_ENTRY(CUG_SETTING_ID,							       8, "")
        CONST_TBL_ENTRY(CLI_SETTING_ID,							       9, "")
        CONST_TBL_ENTRY(CALL_REPEAT_SELECTION_ID,				       10, "")
        CONST_TBL_ENTRY(STORED_CALL_TIMERS_ID,					       11, "")
        CONST_TBL_ENTRY(STORED_LIFE_TIMERS_ID,					       12, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define LIFE_TIMERS_SETTINGS_LENGHT               4")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(CTN_APPL_STATE_ID,						       13, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_MEMORY_BROWSER_LAYOUT_NAME_LIST        0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_MEMORY_BROWSER_LAYOUT_NAME_AND_NUMBER  1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_MEMORY_BROWSER_LAYOUT_LARGE_FONT       2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_MEMORY_BROWSER_LAYOUT_NAME_AND_IMAGE   3")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(MEMORY_BROWSER_LAYOUT_SELECT_ID,			   14, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define GRAPHICS_setting_lenght                   886")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(DWN_GRAPHICS_ID,							   15, "")

        CONST_TBL_ENTRY(DWN_TEXT_ID,								   16, "")
        CONST_TBL_ENTRY(ALS_SUPPORT_ID,							       17, "")
        CONST_TBL_ENTRY(T9_LANGUAGE_STATE_ID,					       18, "")
        CONST_TBL_ENTRY(CALC_EXCHANGE_RATE_ID,					       19, "")
        CONST_TBL_ENTRY(T9_STATE_ID,								   20, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_VOICE_PRIVACY_OFF                      0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_VOICE_PRIVACY_ON                       1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_VOICE_PRIVACY_USEROFF                  2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_CALLMODE_ANALOG                        0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_CALLMODE_DIGITAL                       1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_CALLMODE_DIGITAL_ANALOG                2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_ANYKEY_SELECT_OFF                      0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_ANYKEY_SELECT_ON                       1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(VOICE_CRYPT_SELECT_STATE_ID,                   21, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DTMF_MODE_OFF                          0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DTMF_MODE_BURST                        1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DTMF_MODE_CONTINUOUS                   2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(DTMF_MODE_SELECT_STATE_ID,                     22, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DTMF_LENGTH_SHORT                      0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DTMF_LENGTH_LONG                       1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_AUTO_ANSWER_OFF                        0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_AUTO_ANSWER_ON                         1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(DTMF_LENGTH_SELECT_STATE_ID,                   23, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_FTD_DISPLAY_OFF                        0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_FTD_DISPLAY_OON                        1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_FTD_DISPLAY_LIGHTSON                   2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_FTD_DISPLAY_SUSPENDED                  3")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(FTD_SELECT_STATE_ID,                           24, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_FTD_DISPLAY_NUMBER_MIN                 0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_FTD_DISPLAY_NUMBER_MAX                 65535")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(FTD_DISPLAY_NUMBER_SELECT_STATE_ID,            25, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_ND_MEMO_PLAYBACK_VOL_MIN               0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_ND_MEMO_PLAYBACK_VOL_MED               3")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_ND_MEMO_PLAYBACK_VOL_MAX               10")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_CALL_REPEAT_OFF                        0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_CALL_REPEAT_ON                         1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(ND_MEMO_PLAYBACK_VOL_SELECT_STATE_ID,          26, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_AUTOLOCK_SELECT_OFF                    0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_AUTOLOCK_SELECT_ON                     1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(AUTOLOCK_SELECT_STATE_ID,                      27, "")

        CONST_TBL_ENTRY(AUTOLOCK_UNLOCKED_SELECT_STATE_ID,             28, "")
        CONST_TBL_ENTRY(UNLOCKED_PHONE_NBR_ID,					       29, "")
        CONST_TBL_ENTRY(EMAIL_GATEWAY_ADDR_ID,                         30, "")
        CONST_TBL_ENTRY(CALLBACK_NUMBER_ID,                            31, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_VVOL_LEVEL_MIN                         0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_VVOL_LEVEL_MED                         3")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_VVOL_LEVEL_MAX                         10")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(VVOL_HEADSET_LEVEL_ID,					       32, "")

        CONST_TBL_ENTRY(VVOL_HANDPORTABLE_LEVEL_ID,				       33, "")
        CONST_TBL_ENTRY(VVOL_HANDSFREE_LEVEL_ID,					   34, "")
        CONST_TBL_ENTRY(VVOL_DIGITAL_LEVEL_ID,					       35, "")
        CONST_TBL_ENTRY(VVOL_IHF_LEVEL_ID,                             36, "")
        CONST_TBL_ENTRY(DWS_GRAPHICS_CM_SOURCE_ID,		               37, "")
        CONST_TBL_ENTRY(ART2_SERVER_ACTIVE_ID,			               38, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define PANEL_KEYGUARD_SEC_CODE_QUERY_OFF         0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define PANEL_KEYGUARD_SEC_CODE_QUERY_ON          1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(PANEL_KEYGUARD_SEC_CODE_QUERY_ID,			   39, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define PANEL_KEYGUARD_STATE_OFF                  0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define PANEL_KEYGUARD_STATE_ON                   1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define PANEL_KEYGUARD_STATE_TEMP_OFF             2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(PANEL_KEYGUARD_STATE_ID,					   40, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_WALLPAPER_STATE_OFF                    0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_WALLPAPER_STATE_ON                     1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(WALLPAPER_STATE_ID,			                   41, "")

        CONST_TBL_ENTRY(WALLPAPER_DEFAULT_IMAGE_ID,		               42, "")
        CONST_TBL_ENTRY(WALLPAPER_CURRENT_IMAGE_ID,		               43, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_IGNITION_SENSE_STATE_OFF               0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_IGNITION_SENSE_STATE_ON                1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(IGNITION_SENSE_STATE_ID,			           44, "")

        CONST_TBL_ENTRY(DEALER_SHUTDOWN_SCREEN_FILE_ID,		           45, "")
        CONST_TBL_ENTRY(DEALER_SHUTDOWN_TUNE_FILE_ID,		           46, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DYNAMIC_PRESENCE_SETTINGS_DEFAULT         0x00")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DYNAMIC_PRESENCE_SETTINGS_SHOW_IN_IDLE    0x01")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DYNAMIC_PRESENCE_SETTINGS_LINK_TO_PROFILE 0x02")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_DYNAMIC_PRESENCE_SETTINGS_CONNECTION_TYPE 0x04")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(DYNAMIC_PRESENCE_SETTINGS_ID,				   47, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define PANEL_KEYGUARD_setting_lenght             4")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(PANEL_KEYGUARD_SETTING_ID,		               48, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_GRID_MENU_STATE_NONE                   0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_GRID_MENU_STATE_FULL                   1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_GRID_MENU_STATE_GRID                   2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(GRID_MENU_STATE_ID,                            49, "")

        CONST_TBL_ENTRY(WRITING_TEXT_LANGUAGE_SETTING_ID,	           50, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_TOUCHPAD_FLIP_CALL_SELECT_STATE_NO_CALLS        0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_TOUCHPAD_FLIP_CALL_SELECT_STATE_ALL_CALLS       1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define UI_TOUCHPAD_FLIP_CALL_SELECT_STATE_INCOMING_CALLS  2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(TOUCHPAD_FLIP_CALL_SELECT_STATE_ID,            51, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "  #define OPDN_TEXT_LENGTH                          45")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
        CONST_TBL_ENTRY(OPERATOR_POWERDOWN_NOTE_TEXT_ID,               52, "")

        CONST_TBL_ENTRY(SECOND_WAKEUP_SCREEN_FILE_ID,		           53, "")
        CONST_TBL_ENTRY(SECOND_SHUTDOWN_SCREEN_FILE_ID,		           54, "")

        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define SHUTDOWN_TONE_STATE_OFF       0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define SHUTDOWN_TONE_STATE_ON        1")
        CONST_TBL_ENTRY_VER(SHUTDOWN_TONE_STATE_SETTING_ID,            57, "015.010", "")
        CONST_TBL_ENTRY_VER(IDLE_FONT_COLOR_SETTING_ID,                58, "015.010", "")
        CONST_TBL_ENTRY_VER(SECOND_WALLPAPER_STATE_ID,                 59, "015.010", "")
        CONST_TBL_ENTRY_VER(SECOND_WALLPAPER_DEFAULT_IMAGE_ID,         60, "015.010", "")
        CONST_TBL_ENTRY_VER(SECOND_WALLPAPER_CURRENT_IMAGE_ID,         61, "015.010", "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define UI_BACKGROUND_STATE_OFF 0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define UI_BACKGROUND_STATE_ON  1")
        CONST_TBL_ENTRY( BACKGROUND_STATE_ID,                     62, "")

        CONST_TBL_ENTRY( BACKGROUND_DEFAULT_IMAGE_ID,             63, "")
        CONST_TBL_ENTRY( BACKGROUND_CURRENT_IMAGE_ID,             64, "")

        CONST_TBL_ENTRY( SECOND_BACKGROUND_STATE_ID,      	      65, "")
        CONST_TBL_ENTRY( SECOND_BACKGROUND_DEFAULT_IMAGE_ID,      66, "")
        CONST_TBL_ENTRY( SECOND_BACKGROUND_CURRENT_IMAGE_ID,      67, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define PB_FONT_SIZE_NORMAL   0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define PB_FONT_SIZE_LARGE    1")
        CONST_TBL_ENTRY( PHONEBOOK_FONT_SIZE_SETTING_ID,          68, "")

        CONST_TBL_ENTRY( ROTATOR_SPEED_SETTING_ID,                69, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define DISPLAY_FONT_SIZE_EXTRA_SMALL   0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define DISPLAY_FONT_SIZE_SMALL         1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define DISPLAY_FONT_SIZE_NORMAL        2")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define DISPLAY_FONT_SIZE_LARGE         3")
        CONST_TBL_ENTRY( DISPLAY_FONT_SIZE_SETTING_ID,            70, "")

        CONST_TBL_ENTRY( FOLD_OPEN_MINI_DISPLAY_IMAGE_ID,         71, "")

        CONST_TBL_ENTRY( CLOCK_NOT_SET_IMAGE_ID,                  72, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define ANSWER_ON_OPEN_STATE_OFF        0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define ANSWER_ON_OPEN_STATE_ON         1")
        CONST_TBL_ENTRY( ANSWER_ON_OPEN_STATE_SETTING_ID,         73, "")

        CONST_TBL_ENTRY( GRBG_BROWSER_LAUNCH_LOGO_ID,       	  74, "")
        CONST_TBL_ENTRY( GRBG_BROWSER_LAUNCH_LOGO_DURATION_ID,    75, "")
        CONST_TBL_ENTRY( GRBG_POWER_ON_LOGO_DURATION_ID,       	  76, "")
        CONST_TBL_ENTRY( GRBG_POWER_OFF_LOGO_DURATION_ID,         77, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define GRBG_WIMUI_USER_CERT_PHONE              0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define GRBG_WIMUI_USER_CERT_SECURITY_MODULE    1")
        CONST_TBL_ENTRY( GRBG_WIMUI_USER_CERT_STORAGE_ID,         78, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define GRBG_WIMUI_AUTH_CERT_PHONE              0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define GRBG_WIMUI_AUTH_CERT_SECURITY_MODULE    1")
        CONST_TBL_ENTRY( GRBG_WIMUI_AUTH_CERT_STORAGE_ID,         79, "")

        CONST_TBL_ENTRY( GRBG_INBOX_STATE_ID,                     80, "")
        CONST_TBL_ENTRY( GRBG_INBOX_AUTOCONNECT_STATE_ID,         81, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define GRBG_INBOX_DISABLED                     0")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define GRBG_INBOX_ENABLED                      1")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define GRBG_INBOX_NOT_SET                      0xFF")
        CONST_TBL_ENTRY( GRBG_INBOX_MSG_FILTER_STATE_ID,          82, "")

        CONST_TBL_ENTRY( SCREENSAVER_TIMEOUT_ID,                  83, "")
        CONST_TBL_ENTRY( SCREENSAVER_STATE_ID,                    84, "")
        CONST_TBL_ENTRY( SCREENSAVER_CURRENT_IMAGE_ID,            85, "")
        CONST_TBL_ENTRY( SCREENSAVER_DEFAULT_IMAGE_ID,            86, "")
        CONST_TBL_ENTRY( SECOND_SCREENSAVER_TIMEOUT_ID,           87, "")
        CONST_TBL_ENTRY( SECOND_SCREENSAVER_STATE_ID,             88, "")
        CONST_TBL_ENTRY( SECOND_SCREENSAVER_CURRENT_IMAGE_ID,     89, "")
        CONST_TBL_ENTRY( SECOND_SCREENSAVER_DEFAULT_IMAGE_ID,     90, "")

        CONST_TBL_ENTRY( PARTIALDISPLAY_TIMEOUT_ID,               91, "")
        CONST_TBL_ENTRY( PARTIALDISPLAY_STATE_ID,                 92, "")
        CONST_TBL_ENTRY( PARTIALDISPLAY_CURRENT_IMAGE_ID,         93, "")
        CONST_TBL_ENTRY( PARTIALDISPLAY_DEFAULT_IMAGE_ID,         94, "")
        CONST_TBL_ENTRY( SECOND_PARTIALDISPLAY_TIMEOUT_ID,        95, "")
        CONST_TBL_ENTRY( SECOND_PARTIALDISPLAY_STATE_ID,          96, "")
        CONST_TBL_ENTRY( SECOND_PARTIALDISPLAY_CURRENT_IMAGE_ID,  97, "")
        CONST_TBL_ENTRY( SECOND_PARTIALDISPLAY_DEFAULT_IMAGE_ID,  98, "")

        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    #define COLOR_NOT_SET                       0xFFFF")
        CONST_TBL_ENTRY( SOFTKEY_FONT_COLOR_SETTING_ID,           99, "")

        CONST_TBL_ENTRY( DWS_TUNE_CM_SOURCE_ID,                   100, "")

        CONST_TBL_ENTRY( MENU_FONT_COLOR_SETTING_ID,              101, "")
        CONST_TBL_ENTRY( SIND_UI_LANGUAGE_ID,                     102, "")

        CONST_TBL_ENTRY( FOLD_CLOSE_SOUND_SETTING_ID,             103, "")
        CONST_TBL_ENTRY( FOLD_OPEN_SOUND_SETTING_ID,              104, "")

        CONST_TBL_ENTRY( PRIMARY_STARTUP_ANIM_FILE_ID,            105, "")
        CONST_TBL_ENTRY( SECONDARY_STARTUP_ANIM_FILE_ID,          106, "")
        CONST_TBL_ENTRY( STARTUP_ANIMATION_TUNE_FILE_ID,          107, "")
        CONST_TBL_ENTRY( STARTUP_ANIMATION_DURATION_ID,           108, "")
        CONST_TBL_ENTRY( PRIMARY_SHUTDOWN_ANIM_FILE_ID,           109, "")
        CONST_TBL_ENTRY( SECONDARY_SHUTDOWN_ANIM_FILE_ID,         110, "")
        CONST_TBL_ENTRY( SHUTDOWN_ANIMATION_TUNE_FILE_ID,         111, "")
        CONST_TBL_ENTRY( SHUTDOWN_ANIMATION_DURATION_ID,          112, "")

        CONST_TBL_ENTRY( WAIT_IMAGE_SETTING_ID,                   113, "")

    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* FTD data table */
    /* --------------------------------------------------------------------- */


    /* --------------------------------------------------------------------- */
    /* Sequences */
    /* --------------------------------------------------------------------- */

    SEQ_BEGIN(SETT_DATA, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, data, "Data", HEX)
    SEQ_END


    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    /* SETT_VALUE_IND */ 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSettValueInd")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SETT_VALUE_IND, MESSAGE_IND, "", "")
        SETT_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SettingId, "Setting ID", SETT_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ARRAY_MAXIMUM_SIZE, SETTING_VALUE_MAX_LENGHT)
        SEQ_OF_REF(SettingValue, "Setting value", SETT_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_RESERVE_SPACE)
    MSG_END


    /* SETT_VALUE_GET */ 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSettValueGetReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SETT_VALUE_GET_REQ, MESSAGE_REQ, "", "")
        SETT_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SettingId, "Setting ID", SETT_ID)
        FILLER_EX(reserved, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(SETT_VALUE_GET_STATUS, SETT_STATUS, "", "")
        DER_CONST_TBL_ENTRY(SETT_OK)
        DER_CONST_TBL_ENTRY(SETT_BAD_ID)
        DER_CONST_TBL_ENTRY(SETT_PMM_FAIL)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSettValueGetResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_TEXT, 
        "The length of the data is defined above, "
        "don't use this C-structure for reserving the memory needed")
    MSG_BEGIN(SETT_VALUE_GET_RESP, MESSAGE_RESP, "", "")
        SETT_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SettingId, "Setting ID", SETT_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(status, "Status", SETT_VALUE_GET_STATUS)
        PROPERTY_VALUE(PROPERTY_ARRAY_MAXIMUM_SIZE, SETTING_VALUE_MAX_LENGHT)
        SEQ_OF_REF(SettingValue, "Setting value", SETT_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    MSG_END

    MSG_PAIR(SETT_VALUE_GET_REQ, SETT_VALUE_GET_RESP)


    /* SETT_VALUE_SET */ 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSettValueSetReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_TEXT, 
        "The length of the data is defined above, "
        "don't use this C-structure for reserving the memory needed")
    MSG_BEGIN(SETT_VALUE_SET_REQ, MESSAGE_REQ, "", "")
        SETT_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SettingId, "Setting ID", SETT_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ARRAY_MAXIMUM_SIZE, SETTING_VALUE_MAX_LENGHT)
        SEQ_OF_REF(SettingValue, "Setting value", SETT_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSettValueSetResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SETT_VALUE_SET_RESP, MESSAGE_RESP, "", "")
        SETT_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SettingId, "Setting ID", SETT_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(status, "Status", SETT_STATUS)
    MSG_END

    MSG_PAIR(SETT_VALUE_SET_REQ, SETT_VALUE_SET_RESP)

    /* SETT_RESET_PERFORMED_IND */ 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tResetPerformedInd")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SETT_RESET_PERFORMED_IND, MESSAGE_IND, "", "")
        SETT_MSG_HDR
    MSG_END

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */

#endif /* _GARBAGE_ISI_M_H_

/* End of file garbage_isi_m.h */
