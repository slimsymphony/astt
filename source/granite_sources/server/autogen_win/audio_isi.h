/*
NOKIA                                                             CONFIDENTIAL
OULU
My Entertainment/ My Audio
Achim Peters



                  audio_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1gif

project path:    global_interface/ISI/Core

name:            audio_isi.h

version:         010.002

type:            incl

instance:        ou_pcms#1


ISI header file for Audio Server

Current   ISI Version : 010.002
Supported ISI Versions: 005.020, 005.021, 005.022, 005.023, 005.024, 005.025, 
                        005.026, 005.027, 005.028, 006.000, 006.001, 006.002, 
                        006.003, 006.004, 006.005, 006.006, 006.007, 006.008, 
                        006.009, 006.010, 006.011, 006.012, 006.013, 006.014, 
                        007.000, 007.001, 007.002, 007.003, 007.004, 007.005, 
                        007.006, 007.007, 007.008, 007.009, 008.000, 008.001, 
                        008.002, 008.003, 008.004, 008.005, 008.006, 008.007, 
                        008.008, 008.009, 008.010, 008.011, 008.012, 008.013, 
                        008.014, 008.015, 008.016, 008.017, 008.018, 008.019, 
                        009.000, 009.001, 009.002, 009.003, 009.004, 009.005, 
                        009.006, 009.007, 009.008, 009.009, 009.010, 009.011, 
                        009.012, 009.013, 009.014, 010.000, 010.001, 010.002

Generated with autogen version 10_w49 on 14-Jun-2011 11:47:25
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 010.002    NON-DRAFT   14-Jun-2011    Jani Kärkelä
Reason      : Change request
Reference   : SWAM CR: JR11061043660
Description : 010.002 version is used to add Sidetone support with version
              number 9.14. This is due to backward compability with 9.2 and
              10.4 branches.

Version     : 010.001    NON-DRAFT   27-May-2011    Adrian Chirica
Reason      : Change request
Reference   : SWAM CR: AC11052756663
Description : Fix for duplicate var name which causes error during xml file
              generation for Coltrane tool

Version     : 010.000    NON-DRAFT   07-Apr-2011    Adrian Chirica
Reason      : Change request
Reference   : SWAM CR: AC11041159481
Description : Changed Message AUD_LOOPBACK_REQ
              Changed Message AUD_LOOPBACK_RESP
              Added Sequence AUD_LOOPBACK_IN_OUT_PARAMS_SEQ
              Added Subblock AUD_LOOPBACK_IN_PARAMS_SB
              Added Subblock AUD_LOOPBACK_OUT_PARAMS_SB
              Added Subblock AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB
              Added Sequence AUD_LOOPBACK_TONE_GEN_PARAMS_SEQ
              Added Entry AUD_LOOPBACK_IN_TONE_GENERATOR to AUD_LOOPBACK_IN_SELECT
              Added Entry AUD_LOOPBACK_OUT_FM_TX to AUD_LOOPBACK_OUT_SELECT
              Added Entry AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS to AUD_LOOPBACK_OUT_SELECT
              Added Constant AUD_LOOPBACK_GAIN_DEFAULT
              Audio loopback interface changed to support sub-blocks

Version     : 009.014    NON-DRAFT   14-Jun-2011    Jani Kärkelä
Reason      : Change request
Reference   : SWAM CR: JR11061043660
Description : Added Case AUD_MIXER_SIDETONE_SWITCH to AUD_LAYER_SETTING
              Added Case AUD_MIXER_SIDETONE_SWITCH to AUD_SETTING_REPORT
              Added Entry AUD_MIXER_SIDETONE_SWITCH to AUD_MIXER_ATTRIBUTES_ALL
              Changed Constant AUD_NUM_MIXER_ATTRIBUTES
              Support for sidetone switch.

Version     : 009.013    NON-DRAFT   24-Mar-2011    Anton Nevala
Reason      : Change request
Reference   : SWAM CR: AN11032440034
Description : Added Entry AUD_MIXER_TONE_OUT_HQ_EAR to AUD_MIXER_TONE_OUT_SELECT
              New tone out select

Version     : 009.012    NON-DRAFT   11-Jan-2011    Tuomas Haikarainen
Reason      : Change request
Reference   : SWAM CR: JR11011356972
Description : Discontinued Entry AUD_DSP_ALGORITHM_MB_UDRC in AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MMIC_NREF to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MMIC_VAD to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MWNR to AUD_DSP_ALGORITHMS_5
              Discontinued Entry AUD_DSP_ALGORITHM_TRUE_WB in AUD_DSP_ALGORITHMS_5
              Discontinued Entry AUD_DSP_ALGORITHM_UDRC_WHISPER_MODE in AUD_DSP_ALGORITHMS_5
              Support for uplink noise cancellation switch

Version     : 009.011    NON-DRAFT   23-Nov-2010    Ville Laaksonen
Reason      : Change request
Reference   : SWAM CR: JR10112338329
Description : Added Case AUD_DSP_ACA_ALGORITHMS to AUD_LAYER_SETTING
              Added Case AUD_DSP_ACA_ALGORITHMS_MASK to AUD_LAYER_SETTING
              Added Case AUD_DSP_ACA_ALGORITHMS to AUD_SETTING_REPORT
              Added Case AUD_DSP_ACA_ALGORITHMS_MASK to AUD_SETTING_REPORT
              Added Bitmask table AUD_DSP_ACA_ALGORITHMS
              Added Entry AUD_DSP_ACA_ALGORITHMS to AUD_DSP_PARAMS_ATTRIBUTES_ALL
              Added Entry AUD_DSP_ACA_ALGORITHMS_MASK to AUD_DSP_PARAMS_ATTRIBUTES_ALL
              Changed Constant AUD_NUM_DSP_PARAMS_ATTRIBUTES
              Layer based ACA algorithm control

Version     : 009.010    NON-DRAFT   29-Jan-2010    Adrian Chirica
Reason      : Change request
Reference   : SWAM CR: AC10012248779
Description : Added Entry AUD_MIXER_DL_OUT_BT_STEREO to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_BT_WB_EAR to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_UL_IN_BT_WB to AUD_MIXER_UL_IN_SELECT
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
              Changed Constant AUD_NUM_MIXER_UL_IN_ATTRIBUTES
              2 new selections added for AUD_MIXER_DL_OUT_SELECT and 1 new
              for AUD_MIXER_UL_IN_SELECT

Version     : 009.009    NON-DRAFT   25-Jun-2009    Paavo Salonen
Reason      : Change request
Reference   : SWAM CR: PS09061651680
Description : Added Message AUD_LOOPBACK_GAIN_SET_REQ
              Added Message AUD_LOOPBACK_GAIN_SET_RESP
              Added Message AUD_LOOPBACK_REQ
              Added Message AUD_LOOPBACK_RESP
              Added Sequence AUD_LOOPBACK_INPUT_DATA
              Added Subblock AUD_LOOPBACK_INPUT_GAIN_SB
              Added Sequence AUD_LOOPBACK_OUTPUT_DATA
              Added Subblock AUD_LOOPBACK_OUTPUT_GAIN_SB
              Added Constant table AUD_LOOPBACK_IN_SELECT
              Added Constant table AUD_LOOPBACK_OUT_SELECT
              New loopback interface fine tuning. AUD_LOOPBACK_REQ / RESP and
              AUD_LOOPBACK_GAIN_SET_REQ / RESP were redone.

Version     : 009.008    NON-DRAFT   22-Jun-2009    Seppo Jauho
Reason      : Change request
Reference   : SWAM CR: AN09061631439
Description : Added Entry AUD_MODE_USB_TTY to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              USB TTY audio mode added

Version     : 009.007    NON-DRAFT   27-Apr-2009    Katja Ahonen
Reason      : Change request
Reference   : SWAM CR: KA09042739989
Description : Added Entry AUD_MIXER_DL_OUT_IHF to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_IHF_L to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_IHF_R to AUD_MIXER_DL_OUT_SELECT
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
              Gazoo TPA selection

Version     : 009.006    NON-DRAFT   03-Apr-2009    Katja Ahonen
Reason      : Change request
Reference   : SWAM CR: PS09032047966
Description : Added Message AUD_SELFTEST_REQ
              Added Message AUD_SELFTEST_RESP
              Added Constant table AUD_INPUT_OUTPUT_MODE
              Added Constant table AUD_SELFTEST_TYPES
              Changes to Audio server interface, new messages for MCL

Version     : 009.005    NON-DRAFT   31-Mar-2009    Niina Pussinen
Reason      : Change request
Reference   : SWAM CR: NP09031339141
Description : MCL fix for Hands Free Voice UI (SCO 417-35747)

Version     : 009.004    NON-DRAFT   18-Mar-2009    Niina Pussinen
Reason      : Change request
Reference   : SWAM CR: NP09031339141
Description : Added Message AUD_FEATURE_SET_REQ
              Added Message AUD_FEATURE_SET_RESP
              Added Constant table AUD_FEATURE_ID
              MCL Hands Free Voice UI (SCO 417-35747)

Version     : 009.003    NON-DRAFT   06-Mar-2009    Katja Ahonen
Reason      : Change request
Reference   : SWAM CR: KA09021158148
Description : Added Message AUD_S60_VOIP_EMERGENCY_CALL_NTF
              Added Entry AUD_MIXER_UL_IN_EANC_BOTH_MICS to AUD_MIXER_UL_IN_SELECT
              Added Entry AUD_MIXER_UL_IN_EANC_MIC1 to AUD_MIXER_UL_IN_SELECT
              Added Entry AUD_MIXER_UL_IN_EANC_MIC2 to AUD_MIXER_UL_IN_SELECT
              Added Entry AUD_MODE_HP_SLIDE_SHORT_OPEN to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_MIXER_UL_IN_ATTRIBUTES
              Changes to Audio server interface, new messages and new audio
              modes (for MCL)

Version     : 009.002    NON-DRAFT   18-Feb-2009    Seppo Jauho
Reason      : Change request
Reference   : SWAM CR: SJ09010841712
Description : GPA isi intrerface added

Version     : 009.001    NON-DRAFT   27-Jan-2009    Katja Ahonen
Reason      : Change request
Reference   : SWAM CR: AN08101685298
Description : Added Entry AUD_TEST_EANC_MIC1_IN_USB_OUT_EAR_L to AUD_TEST_TYPES
              Added Entry AUD_TEST_EANC_MIC2_IN_USB_OUT_EAR_L to AUD_TEST_TYPES
              Added Entry AUD_TEST_HP_MIC1_IN_USB_OUT_EAR_L to AUD_TEST_TYPES
              Added Entry AUD_TEST_HP_MIC2_IN_USB_OUT_EAR_L to AUD_TEST_TYPES
              Added Entry AUD_TEST_USB_IN_IHF_OUT_LEFT to AUD_TEST_TYPES
              Added Entry AUD_TEST_USB_IN_IHF_OUT_RIGHT to AUD_TEST_TYPES
              Added Entry AUD_TEST_USB_IN_USB_OUT_EAR_L to AUD_TEST_TYPES
              Audio mic testing through uUSB

Version     : 009.000    NON-DRAFT   14-Jan-2009    Katja Ahonen
Reason      : Change request
Reference   : SWAM CR: KA09010952478
Description : Changed Message AUD_TEST_START_REQ
              Added Entry AUD_DSP_ALGORITHM_APSSAS to AUD_DSP_ALGORITHMS_4
              Discontinued Entry AUD_TEST_AIC33_LINEIN_LEFT_HP_OUT in AUD_TEST_TYPES
              Added Entry AUD_TEST_AV_IN_IHF_LEFT_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_AV_IN_IHF_RIGHT_OUT to AUD_TEST_TYPES
              Discontinued Entry AUD_TEST_BUZZER in AUD_TEST_TYPES
              Discontinued Entry AUD_TEST_EXT_IN_EXT_OUT in AUD_TEST_TYPES
              Discontinued Entry AUD_TEST_EXT_IN_HP_OUT in AUD_TEST_TYPES
              Discontinued Entry AUD_TEST_EXT_IN_IHF_OUT in AUD_TEST_TYPES
              Discontinued Entry AUD_TEST_FM_IN_EXT_OUT in AUD_TEST_TYPES
              Discontinued Entry AUD_TEST_HP_IN_EXT_OUT in AUD_TEST_TYPES
              Discontinued Entry AUD_TEST_HP_STEREO_IN_AV_OUT in AUD_TEST_TYPES
              Discontinued Entry AUD_TEST_STEREO_DIG_IN_EXT_OUT in AUD_TEST_TYPES
              Test loops clean up

Version     : 008.019    NON-DRAFT   12-Sep-2008    Adrian Chirica
Reason      : Change request
Reference   : SWAM CR: AC08083040574
Description : Added Case AUD_MODE_SECONDARY to AUD_LAYER_SETTING
              Added Case AUD_MODE_SECONDARY to AUD_SETTING_REPORT
              Added Entry AUD_MODE_SECONDARY to AUD_MODE_ATTRIBUTES_ALL
              Changed Constant AUD_NUM_MODE_ATTRIBUTES
              Secondary audio mode introducted to interface

Version     : 008.018    NON-DRAFT   15-May-2008    Adrian Chirica
Reason      : Bug Fix
Reference   : SWAM CR: AN08041749576
Description :  Fix for bug introduced with task ou1core#90208

Version     : 008.017    NON-DRAFT   07-May-2008    Adrian Chirica, Jaakko Rautiainen 
Reason      : Change request
Reference   : SWAM CR: AC08042449305
Description : Added Message AUD_EANC_MIC_DATA_REQ
              Added Message AUD_EANC_MIC_DATA_RESP
              Added Entry AUD_TEST_HP_MIC1_IN_AV_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_HP_MIC2_IN_AV_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_HP_STEREO_IN_AV_OUT to AUD_TEST_TYPES
              Changed Constant AUD_NUM_TEST_TYPES
               Added 3 new test loops for twin microphones and more EANC
              messages

Version     : 008.016    NON-DRAFT   23-Mar-2008    Pasi Alatalo
Reason      : Change request
Reference   : SWAM CR: AN08041749576
Description : Re-introduced Message AUD_TEST_START_REQ
              Added Constant table AUD_TEST_TX_OUT_ROUTE
              Added Entry AUD_TEST_FM_TX_OUT to AUD_TEST_TYPES
              Changed Constant AUD_NUM_TEST_TYPES
               Added new interfaces for FM TX test loop

Version     : 008.015    NON-DRAFT   31-Mar-2008    Petteri Hyvonen
Reason      : Change request
Reference   : SWAM CR: EH08033156573
Description : Discontinued Message AUD_TEST_START_REQ
              Added Entry AUD_MIXER_DL_OUT_EAR_I2S_L to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_EAR_I2S_R to AUD_MIXER_DL_OUT_SELECT
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
               Added DL out selections for I2S left and I2S right

Version     : 008.014    NON-DRAFT   20-Mar-2008    Jaakko Rautiainen
Reason      : Change request
Reference   : SWAM CR: JR08032051561
Description : Added Message AUD_EANC_STATUS_CHANGE_IND
               Added EANC state indication

Version     : 008.013    NON-DRAFT   19-Feb-2008    Jaakko Rautiainen
Reason      : Change request
Reference   : SWAM CR: JR08022051386
Description : Added Entry AUD_EANC_BOTH_MICS_FAIL to AUD_TEST_ERRORS
              Added Entry AUD_EANC_L_MIC_FAIL to AUD_TEST_ERRORS
              Added Entry AUD_EANC_R_MIC_FAIL to AUD_TEST_ERRORS
              Added Entry AUD_TEST_EANC_PROD_MODE to AUD_TEST_TYPES
              Added Entry AUD_TEST_EANC_SP_MODE to AUD_TEST_TYPES
               Added more EANC definitions

Version     : 008.012    NON-DRAFT   14-Feb-2008    Janne Ervasti, Rasmus Rahunen, Jani Kärkelä
Reason      : Audio server UPP split.
Reference   : 414-4504, 403-5694, 403-10649
Description : Added Message AUD_VOLUME_CONTROL_IND
              Changed Subblock AUD_VOLUME_CONTROL_RESPONSE_SB
              Added Entry AUD_MODE_POC_BTH to AUD_MODE_VALUES
              Added Entry AUD_MODE_POC_HS to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
               Split of Audio server ISI IF for BB5. New indication
              AUD_VOLUME_CONTROL_IND and new parameters to
              AUD_VOLUME_CONTROL_RESPONSE_SB. ISI interface update, POC_HS
              and POC_BTH modes.

Version     : 008.011    NON-DRAFT   15-Jan-2008    Janne Vimpari
Reason      : Change request
Reference   : SWAM CR: JV08011556803
Description :  SWAM CR: JV08011556803: Separate EAP ISI messages from Audio
              ISI messages

Version     : 008.010    NON-DRAFT   04-Jan-2008    Janne Vimpari
Reason      : Change request
Reference   : RM-RIM 403-9345, ADB SWAM JV0801044858
Description :  Added two messages to support run time trace activation

Version     : 008.009    NON-DRAFT   10-Dec-2007    Paavo Salonen
Reason      : Change request
Reference   : RM-RIM 401-5601, ADB SWAM PS07121059105
Description : Added Entry AUD_DSP_ALGORITHM_LIMITER to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_LIMITER_CONDITIONAL to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MMIC to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MMIC_SELECT_AIC to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MMIC_SELECT_CAL_GAIN_APPLY to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MMIC_SELECT_CAL_GAIN_ESTIM to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MMIC_SELECT_POS to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_MMIC_SELECT_STB to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_NB_SPC_EMPHASIS to AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHM_TRUE_WB to AUD_DSP_ALGORITHMS_5
               Added new defines for AUD_DSP_ALGORITHMS_5 bitmask.

Version     : 008.008    NON-DRAFT   20-Nov-2007    Jaakko Rautiainen
Reason      : Change request
Reference   : RM-RIM 403-9201, ADB SWAM JR07111958783
Description : Added Message AUD_EANC_STATUS_CHANGE_REQ
              Added Message AUD_EANC_STATUS_CHANGE_RESP
              Added Constant table AUD_EANC_STATE
              Added Entry AUD_TEST_MIC_IN_EANC_OFF_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_MIC_IN_EANC_ON_OUT to AUD_TEST_TYPES
               Added support for EANC

Version     : 008.007    NON-DRAFT   06-Nov-2007    Paavo Salonen
Reason      : Change request
Reference   : RM-RIM 401-5611, ADB SWAM PS07110651102
Description : Added Entry AUD_DSP_ALGORITHM_FULLBAND_AGC to AUD_DSP_ALGORITHMS_4
              Added Entry AUD_DSP_ALGORITHM_REC_LIMITER to AUD_DSP_ALGORITHMS_4
              Added Entry AUD_DSP_ALGORITHM_REC_MUMDRC to AUD_DSP_ALGORITHMS_4
               Added new defines for AUD_DSP_ALGORITHMS_4 bitmask.

Version     : 008.006    NON-DRAFT   25-Sep-2007    Seppo Jauho
Reason      : Change request
Reference   : RM-RIM 401-5500, ADB SWAM SJ07092554528
Description : Added Entry AUD_MODE_FMTX_AND_PHONE to AUD_MODE_VALUES
              Added Entry AUD_MODE_FMTX_ONLY to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
               Added AUD_MODE_FMTX_ONLY and AUD_MODE_FMTX_AND_PHONE 

Version     : 008.005    NON-DRAFT   19-Sep-2007    Seppo Jauho
Reason      : Change request
Reference   : RM-RIM 401-5307, RM-RIM 401-5190, ADB SWAM SJ07091242230
Description : Added Entry AUD_MIXER_DL_OUT_HAC to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MODE_MOBILE_TV to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
               Added AUD_MODE_MOBILE_TV and AUD_MIXER_DL_OUT_HAC 

Version     : 008.004    NON-DRAFT   09-Aug-2007    Mika P. Kangas
Reason      : Change request
Reference   : RM-RIM 402-2988, 010-31685, ADB SWAM MK07080950055
Description : Added Entry AUD_MODE_FM_RADIO_USB to AUD_MODE_VALUES
              Added Entry AUD_MODE_USB_EXT_MIC to AUD_MODE_VALUES
              Added Entry AUD_MODE_USB_HD_HP_MIC to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
               Add new audio modes for USB Audio 

Version     : 008.003    NON-DRAFT   26-Jun-2007    Janne Vimpari
Reason      : Change request
Reference   : RM-RIM 009-30070, ADB SWAM JV07060855686
Description :  Create ISI interface for Audio Visualization post effect 

Version     : 008.002    NON-DRAFT   19-Jun-2007    Janne Vimpari
Reason      : Change request Add AUD_MODE_AUDIO_REC
Reference   : RM-RIM 403-1583, ADB SWAM JV07061359846
Description : Added Entry AUD_MODE_AUDIO_REC to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
               Add new audio mode (AUD_MODE_AUDIO_REC) 

Version     : 008.001    NON-DRAFT   3-May-2007     Janne Ervasti
Reason      : Change request (FTD data mode changes).
Reference   : RM-RIM 009-28730, ADB SWAM JE07050239685
Description :  FTD data mode changes to operator mode. 

Version     : 008.000    NON-DRAFT   12-Mar-2007    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM AN07032036224
Description : Added Case AUD_MIXER_APE_SPEECH_TONE_SWITCH to AUD_LAYER_SETTING
              Added Case AUD_MIXER_APE_SPEECH_TONE_SWITCH to AUD_SETTING_REPORT
              Added Entry AUD_MIXER_APE_SPEECH_TONE_SWITCH to AUD_MIXER_ATTRIBUTES_ALL
              Discontinued Entry AUD_MIXER_TONE_OUT_ACC in AUD_MIXER_TONE_OUT_SELECT
              Discontinued Entry AUD_MIXER_TONE_OUT_MEMORY in AUD_MIXER_TONE_OUT_SELECT
              Added Entry AUD_MIXER_TONE_OUT_SPEECH_EAR to AUD_MIXER_TONE_OUT_SELECT
              Changed Constant AUD_NUM_MIXER_ATTRIBUTES
               

Version     : 007.009    NON-DRAFT   12-Mar-2007    Marko Kangasluoma
Reason      : Change request
Reference   : ADB SWAM MK07031251079
Description : Added Message AUD_FIFO_INTERRUPT_IND
               

Version     : 007.008    NON-DRAFT   20-Dec-2006    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM AN06121952700
Description : Added Entry AUD_TONE_SEQUENCE_MUSIC_PLAY to AUD_TONE_SEQUENCE_TYPE
               

Version     : 007.007    NON-DRAFT   22-Nov-2006    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM MK06112154700
Description : Added Case AUD_MIXER_PLAYBACK_MODE_SELECT to AUD_LAYER_SETTING
              Added Case AUD_MIXER_PLAYBACK_MODE_SELECT to AUD_SETTING_REPORT
              Added Entry AUD_MIXER_PLAYBACK_MODE_SELECT to AUD_MIXER_ATTRIBUTES_ALL
              Added Entry AUD_MIXER_DL_OUT_FMTX to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_FMTX_L to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_FMTX_R to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_HD_EAR_L to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_HD_EAR_R to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_USB to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_USB_L to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_USB_R to AUD_MIXER_DL_OUT_SELECT
              Added Constant table AUD_MIXER_PLAYBACK_MODE_SELECT
              Added Entry AUD_MIXER_UL_IN_USB_MIC to AUD_MIXER_UL_IN_SELECT
              Added Entry AUD_TEST_HP_IN_USB_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_USB_IN_HP_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_USB_IN_IHF_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_USB_IN_USB_OUT to AUD_TEST_TYPES
              Changed Constant AUD_NUM_MIXER_ATTRIBUTES
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
              Changed Constant AUD_NUM_MIXER_UL_IN_ATTRIBUTES
              Changed Constant AUD_NUM_TEST_TYPES
               

Version     : 007.006    NON-DRAFT   10-Nov-2006    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM MK06110953626
Description : Added Entry AUD_MODE_USB_CAR_HF to AUD_MODE_VALUES
              Added Entry AUD_MODE_USB_HD to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
               

Version     : 007.005    NON-DRAFT   18-Oct-2006    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM AN06101758966, ADB SWAM AN06102056604
Description : Added Entry AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS_L to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS_R to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_TEST_AV_IN_HP_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_AV_IN_IHF_OUT to AUD_TEST_TYPES
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
              Changed Constant AUD_NUM_TEST_TYPES
               

Version     : 007.004    NON-DRAFT   26-Sep-2006    Jaakko Rautiainen
Reason      : Change request
Reference   : ADB SWAM JR06092049285
Description : Added Entry AUD_MIXER_DL_OUT_EXT_EAR_AMP_L to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_EXT_EAR_AMP_R to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_TEST_AV_IN_AV_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_FM_IN_AV_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_HP_IN_AV_OUT to AUD_TEST_TYPES
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
              Changed Constant AUD_NUM_TEST_TYPES
               

Version     : 007.003    NON-DRAFT   12-Sep-2006    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM AN06090761597
Description : Added Entry AUD_MIXER_UL_IN_EXT_MIC to AUD_MIXER_UL_IN_SELECT
              Added Entry AUD_MODE_LINE_OUT to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_MIXER_UL_IN_ATTRIBUTES
               

Version     : 007.002    NON-DRAFT   11-Aug-2006    Jani Pellikka
Reason      : Change request
Reference   : ADB SWAM JP06081433480
Description :  

Version     : 007.001    NON-DRAFT   08-Jun-2006    Jani Pellikka
Reason      : Change request
Reference   : ADB SWAM JP06060844679
Description : Added Entry AUD_KODIAK_CLIENT_TYPE to AUD_CLIENT_TYPES
              Added Entry AUD_MIXER_DL_OUT_EAR_I2S to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MODE_THWK_HIFI_HD to AUD_MODE_VALUES
              Added Entry AUD_MODE_THWK_RADIO_HD to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_CLIENT_TYPES
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
               

Version     : 007.000    NON-DRAFT   22-May-2006    Jani Pellikka
Reason      : Change request
Reference   : ADB SWAM JP06052429518
Description : Added Case AUD_DSP_ALGORITHMS_3 to AUD_LAYER_SETTING
              Added Case AUD_DSP_ALGORITHMS_4 to AUD_LAYER_SETTING
              Added Case AUD_DSP_ALGORITHMS_5 to AUD_LAYER_SETTING
              Added Case AUD_DSP_ALGORITHMS_3 to AUD_SETTING_REPORT
              Added Case AUD_DSP_ALGORITHMS_4 to AUD_SETTING_REPORT
              Added Case AUD_DSP_ALGORITHMS_5 to AUD_SETTING_REPORT
              Added Entry AUD_DSP_ALGORITHM_AEC_CN to AUD_DSP_ALGORITHMS_1
              Discontinued Entry AUD_DSP_ALGORITHM_BEQ in AUD_DSP_ALGORITHMS_1
              Added Entry AUD_DSP_ALGORITHM_ABE to AUD_DSP_ALGORITHMS_2
              Added Entry AUD_DSP_ALGORITHM_HQ_EEQ to AUD_DSP_ALGORITHMS_2
              Added Entry AUD_DSP_ALGORITHM_HQ_MEQ to AUD_DSP_ALGORITHMS_2
              Added Bitmask table AUD_DSP_ALGORITHMS_3
              Added Bitmask table AUD_DSP_ALGORITHMS_4
              Added Bitmask table AUD_DSP_ALGORITHMS_5
              Added Entry AUD_DSP_ALGORITHMS_3 to AUD_DSP_PARAMS_ATTRIBUTES_ALL
              Added Entry AUD_DSP_ALGORITHMS_4 to AUD_DSP_PARAMS_ATTRIBUTES_ALL
              Added Entry AUD_DSP_ALGORITHMS_5 to AUD_DSP_PARAMS_ATTRIBUTES_ALL
              Changed Constant AUD_NUM_DSP_PARAMS_ATTRIBUTES
               

Version     : 006.014    NON-DRAFT   10-May-2006    Jani Pellikka
Reason      : Change request
Reference   : ADB SWAM CR AN06050233373
Description : Added Entry AUD_MIXER_APE_TONE_AUD_REC to AUD_MIXER_APP_REC_SELECT
              Added Entry AUD_MIXER_UL_IN_DIGI_STEREO to AUD_MIXER_UL_IN_SELECT
              Added Entry AUD_MIXER_UL_IN_FCI to AUD_MIXER_UL_IN_SELECT
              Added Entry AUD_MIXER_UL_IN_I2S to AUD_MIXER_UL_IN_SELECT
              Added Entry AUD_MODE_SPEECH_REC to AUD_MODE_VALUES
              Added Entry AUD_MODE_VIDEO_REC to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_MIXER_UL_IN_ATTRIBUTES
               

Version     : 006.013    NON-DRAFT   09-Mar-2006    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN06030757429
Description : Added Message AUD_VOLUME_CONTROL_REQ
              Added Message AUD_VOLUME_CONTROL_RESP
              Added Message AUD_VOLUME_GET_REQ
              Added Message AUD_VOLUME_GET_RESP
              Added Subblock AUD_VOLUME_CONTROL_RESPONSE_SB
              Added Subblock AUD_VOLUME_CONTROL_SB
              Added Entry AUD_MIXER_DL_OUT_EXT_EAR_AMP to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MODE_AV_TTY to AUD_MODE_VALUES
              Added Constant table AUD_VOLUME_CONTROL_TYPE
              Added Bitmask table AUD_VOLUME_MEDIA_TYPE
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
               

Version     : 006.012    NON-DRAFT   03-Mar-2006    Marko Kangasluoma
Reason      : Change request
Reference   : ADB SWAM CR MK06022753147
Description : Audio policy interface added to separate file

Version     : 006.011    NON-DRAFT   12-Dec-2005    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN05120942086
Description : Changed Entry AUD_MODE_HS20 in AUD_MODE_VALUES
              Changed Entry AUD_MODE_HS29 in AUD_MODE_VALUES
               

Version     : 006.010    NON-DRAFT   12-Dec-2005    Marko Kangasluoma
Reason      : Change request
Reference   : ADB SWAM CR MK05112246823
Description : Added Message AUD_EQU_ADJUSTED_IND
              Added Message AUD_EQU_CREATED_IND
              Added Message AUD_EQU_DELETED_IND
              Added Message AUD_EQU_GENERAL_INFO_REQ
              Added Message AUD_EQU_GENERAL_INFO_RESP
              Added Subblock AUD_EQU_GENERAL_INFO
               

Version     : 006.009    NON-DRAFT   01-Dec-2005    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN05120136458
Description : Added Case AUD_MIXER_DL_OUT_TRANSMIT_SELECT to AUD_LAYER_SETTING
              Added Case AUD_MIXER_DL_OUT_TRANSMIT_SELECT to AUD_SETTING_REPORT
              Added Entry AUD_MIXER_DL_OUT_TRANSMIT_SELECT to AUD_MIXER_ATTRIBUTES_ALL
              Added Constant table AUD_MIXER_DL_OUT_TRANSMIT_SELECT
              Added Entry AUD_MODE_AV_BASIC_HF to AUD_MODE_VALUES
              Added Entry AUD_MODE_AV_EXT_MIC to AUD_MODE_VALUES
              Added Entry AUD_MODE_STEREO_CAR_HF to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_MIXER_ATTRIBUTES
               

Version     : 006.008    NON-DRAFT   14-Nov-2005    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN05110956275
Description : Added Entry AUD_MIXER_DL_OUT_EXT_IHF to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_EXT_IHF_LEFT to AUD_MIXER_DL_OUT_SELECT
              Added Entry AUD_MIXER_DL_OUT_EXT_IHF_RIGHT to AUD_MIXER_DL_OUT_SELECT
              Changed Constant AUD_NUM_MIXER_DL_OUT_ATTRIBUTES
               

Version     : 006.007    NON-DRAFT   20-Oct-2005    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN05102044080
Description : Added Entry AUD_MODE_HS20 to AUD_MODE_VALUES
              Added Entry AUD_MODE_HS29 to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
               

Version     : 006.006    NON-DRAFT   10-Oct-2005    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM CR MK05092652108
Description : Included the new ECI IF 

Version     : 006.005    NON-DRAFT   23-Sep-2005    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM CR MK05092652108
Description : Added Entry AUD_MODE_AD15 to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              ISIHDR generation enabled, after this macrofile version isihdr
              will be generated by the autogen macro

Version     : 006.004    NON-DRAFT   15-Sep-2005    Marko Kangasluoma
Reason      : Change request
Reference   : ADB SWAM CR MK05083056633
Description :  

Version     : 006.003    NON-DRAFT   31-Aug-2005    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN05083058267
Description : Added Entry AUD_MODE_AV_GENERIC to AUD_MODE_VALUES
              Added Entry AUD_MODE_AV_STEREO_HD to AUD_MODE_VALUES
              Added Entry AUD_MODE_AV_STEREO_HD_HP_MIC to AUD_MODE_VALUES
              Added Entry AUD_TEST_EXT_IN_HAC_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_STEREO_DIG_IN_EXT_OUT to AUD_TEST_TYPES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_TEST_TYPES
               

Version     : 006.002    NON-DRAFT   15-Aug-2005    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN05080947503
Description : Added Entry AUD_MODE_TVOUT to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
               

Version     : 006.001    NON-DRAFT   12-Apr-2005    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM CR MK05050241185
Description : Added Entry AUD_MODE_PHAP_HP to AUD_MODE_VALUES
              Added Entry AUD_MODE_PHAP_HP_SLIDE_OPEN to AUD_MODE_VALUES
              Added Entry AUD_TEST_AIC33_LINEIN_LEFT_HP_OUT to AUD_TEST_TYPES
              Added Entry AUD_TEST_AIC33_LINEIN_RIGHT_HP_OUT to AUD_TEST_TYPES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_TEST_TYPES
               

Version     : 006.000    NON-DRAFT   28-Apr-2005    Marko Kangasluoma
Reason      : Change request
Reference   : ADB SWAM CR MK05041955966 Audio Server: EAP time and pause
              interface"
Description :  

Version     : 005.028    NON-DRAFT   08-Apr-2005    Jaakko Rautiainen
Reason      : Change request
Reference   : ADB SWAM CR JR05040539062 "Audio Server: 5 new modes, 1 new
              client type"
Description : Added Entry AUD_UI_2_CLIENT_TYPE to AUD_CLIENT_TYPES
              Added Entry AUD_MODE_EXT_MIC to AUD_MODE_VALUES
              Added Entry AUD_MODE_FM_RADIO_REC to AUD_MODE_VALUES
              Added Entry AUD_MODE_LINE_IN_REC to AUD_MODE_VALUES
              Added Entry AUD_MODE_UNIV_STEREO to AUD_MODE_VALUES
              Added Entry AUD_MODE_UNIV_STEREO_EXT_MIC to AUD_MODE_VALUES
              Changed Constant AUD_NUM_ACC_MODES
              Changed Constant AUD_NUM_CLIENT_TYPES
               

Version     : 005.027    NON-DRAFT   01-Apr-2005    Mika P. Kangas
Reason      : Change request
Reference   : ADB SWAM CR MK05031647456
Description : Added Message AUD_ATTACH_ACCESSORY_EVENT_OK_RESP
              Added Message AUD_ATTACH_ACCESSORY_EVENT_REQ
              Added Subblock ACC_SB_THWK_AUDIO_BLOCK
              Added Subblock ACC_SB_THWK_EXEC_FEATURE
              Added Subblock ACC_SB_THWK_INFO_FEATURE
              Added Bitmask table ACC_THWK_EXEC_FEATURE_ID
              Added Bitmask table ACC_THWK_INFO_FEATURE2_ID
              Added Bitmask table ACC_THWK_INFO_FEATURE_ID
              Added Constant table ACC_THWK_MASTER_TYPE
              Added Constant table ACC_THWK_SUB_TYPE_ADAPTER
              Added Constant table ACC_THWK_SUB_TYPE_CAM
              Added Constant table ACC_THWK_SUB_TYPE_DC
              Added Constant table ACC_THWK_SUB_TYPE_HD
              Added Constant table ACC_THWK_SUB_TYPE_HF
              Added Constant table ACC_THWK_SUB_TYPE_MISC
              Added Constant table ACC_THWK_SUB_TYPE_NO_INFORMATION
              Added Constant table ACC_THWK_SUB_TYPE_OTHER
              Added Constant table ACC_THWK_SUB_TYPE_TD
              Added Constant ACC_ISI_VERSION_YYY
              Added Constant ACC_ISI_VERSION_ZZZ
              Added Shared file from PN_ACCESSORY
              New audio isi messages: AUD_ATTACH_ACCESSORY_EVENT_REQ and
              AUD_ATTACH_ACCESSORY_EVENT_OK_RESP

Version     : 005.026    NON-DRAFT   07-Feb-2005    Marko Kangasluoma
Reason      : Change request
Reference   : ADB SWAM CR MK05013157091 "Audio Server: EAP capture and effect
              interface change"
Description :  

Version     : 005.025    NON-DRAFT   17-Jan-2005    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN05011349117 "Audio Server: New value for
              AUD_MIXER_APP_REC_SELECT Attribute"
Description : Added Entry AUD_MIXER_APE_AUD_REC to AUD_MIXER_APP_REC_SELECT
               

Version     : 005.024    NON-DRAFT   05-Jan-2005    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN04122334741 "Audio Server: 3 new modes, 2 message
              definition remove"
Description : New Audio Modes: AUD_MODE_TEST_CABLE, AUD_MODE_HD_ST_2 and
              AUD_MODE_STEREO_MIC

Version     : 005.023    NON-DRAFT   08-Dec-2004    Jaakko Rautiainen
Reason      : Change request
Reference   : ADB SWAM CR JR04120334038 "Audio server: New audio mode for
              CK-10, Car Kit 10"
Description : New mode AUD_MODE_CK_10

Version     : 005.022    NON-DRAFT   29-Oct-2004    Anton Nevala
Reason      : Change request
Reference   : ADB SWAM CR AN04102544508 "Audio server: Audio ISI interface
              changes for HAC"
Description : Added Message AUD_DEFATTR_CHANGE_REQ
              Added Message AUD_DEFATTR_CHANGE_RESP
              Added Message AUD_DEFATTR_VALUE_GET_REQ
              Added Message AUD_DEFATTR_VALUE_GET_RESP
              Default attribute setting messages currently for HAC

Version     : 005.021    NON-DRAFT   21-Oct-2004    Marko Kangasluoma
Reason      : Change request
Reference   : ADB SWAM CR MK04101543136 "Audio server: EAP interface changes"
Description : EAP messages, subblocks, constants and structures added

Version     : 005.020    NON-DRAFT   25-Sep-2004    Jaakko Rautiainen
Reason      : Change request
Reference   : ADB SWAM CR JR04092239071 "Audio server: BT streaming changes"
Description : New mode AUD_MODE_BTHSTREAM and new messages

------------------------------------------------------------------------------
*/

#ifndef _AUDIO_ISI_H
#define _AUDIO_ISI_H

#include "isi_conf.h"

#ifndef AUD_ISI_VERSION
#define AUD_ISI_VERSION
#define AUD_ISI_VERSION_Z  10
#define AUD_ISI_VERSION_Y   2
#endif

#define AUD_ISI_MIN_VERSION(z,y) \
 ((AUD_ISI_VERSION_Z == (z) && AUD_ISI_VERSION_Y >= (y)) || \
  (AUD_ISI_VERSION_Z > (z)))

#if !AUD_ISI_MIN_VERSION(5,20)
#error The specified interface version is not supported by this header file
#elif AUD_ISI_MIN_VERSION(10,3)
#error The specified interface version is not supported by this header file
#endif

#include "acc_shared_isi.h"
#include "audio_eci_isi.h"
#include "audio_pol_isi.h"
#include "audio_eap_isi.h"
#include "audio_gpa_isi.h"

/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

#define AUD_NUM_MESSAGE_TYPES                    0x0071
#define AUD_COMM_MESSAGE_TYPES                   0x0B
#define AUD_NUM_MAX_CLIENTS                      0x20
#define AUD_NUM_LOOPBACK_INPUTS                  0x08
#define AUD_NUM_LOOPBACK_OUTPUTS                 0x06

#if !AUD_ISI_MIN_VERSION(5,28)
#define AUD_NUM_ACC_MODES                        0x002C
#endif /* !AUD_ISI_MIN_VERSION(5,28) */


#if AUD_ISI_MIN_VERSION(5,28) && !AUD_ISI_MIN_VERSION(6,1)
#define AUD_NUM_ACC_MODES                        0x0031
#endif /* AUD_ISI_MIN_VERSION(5,28) && !AUD_ISI_MIN_VERSION(6,1) */


#if AUD_ISI_MIN_VERSION(6,1) && !AUD_ISI_MIN_VERSION(6,2)
#define AUD_NUM_ACC_MODES                        0x0033
#endif /* AUD_ISI_MIN_VERSION(6,1) && !AUD_ISI_MIN_VERSION(6,2) */


#if AUD_ISI_MIN_VERSION(6,2) && !AUD_ISI_MIN_VERSION(6,3)
#define AUD_NUM_ACC_MODES                        0x0034
#endif /* AUD_ISI_MIN_VERSION(6,2) && !AUD_ISI_MIN_VERSION(6,3) */


#if AUD_ISI_MIN_VERSION(6,3) && !AUD_ISI_MIN_VERSION(6,5)
#define AUD_NUM_ACC_MODES                        0x0037
#endif /* AUD_ISI_MIN_VERSION(6,3) && !AUD_ISI_MIN_VERSION(6,5) */


#if AUD_ISI_MIN_VERSION(6,5) && !AUD_ISI_MIN_VERSION(6,7)
#define AUD_NUM_ACC_MODES                        0x0038
#endif /* AUD_ISI_MIN_VERSION(6,5) && !AUD_ISI_MIN_VERSION(6,7) */


#if AUD_ISI_MIN_VERSION(6,7) && !AUD_ISI_MIN_VERSION(6,9)
#define AUD_NUM_ACC_MODES                        0x003A
#endif /* AUD_ISI_MIN_VERSION(6,7) && !AUD_ISI_MIN_VERSION(6,9) */


#if AUD_ISI_MIN_VERSION(6,9) && !AUD_ISI_MIN_VERSION(6,13)
#define AUD_NUM_ACC_MODES                        0x003D
#endif /* AUD_ISI_MIN_VERSION(6,9) && !AUD_ISI_MIN_VERSION(6,13) */


#if AUD_ISI_MIN_VERSION(6,13) && !AUD_ISI_MIN_VERSION(6,14)
#define AUD_NUM_ACC_MODES                        0x003E
#endif /* AUD_ISI_MIN_VERSION(6,13) && !AUD_ISI_MIN_VERSION(6,14) */


#if AUD_ISI_MIN_VERSION(6,14) && !AUD_ISI_MIN_VERSION(7,1)
#define AUD_NUM_ACC_MODES                        0x0040
#endif /* AUD_ISI_MIN_VERSION(6,14) && !AUD_ISI_MIN_VERSION(7,1) */


#if AUD_ISI_MIN_VERSION(7,1) && !AUD_ISI_MIN_VERSION(7,3)
#define AUD_NUM_ACC_MODES                        0x0042
#endif /* AUD_ISI_MIN_VERSION(7,1) && !AUD_ISI_MIN_VERSION(7,3) */


#if AUD_ISI_MIN_VERSION(7,3) && !AUD_ISI_MIN_VERSION(7,6)
#define AUD_NUM_ACC_MODES                        0x0043
#endif /* AUD_ISI_MIN_VERSION(7,3) && !AUD_ISI_MIN_VERSION(7,6) */


#if AUD_ISI_MIN_VERSION(7,6) && !AUD_ISI_MIN_VERSION(8,2)
#define AUD_NUM_ACC_MODES                        0x0045
#endif /* AUD_ISI_MIN_VERSION(7,6) && !AUD_ISI_MIN_VERSION(8,2) */


#if AUD_ISI_MIN_VERSION(8,2) && !AUD_ISI_MIN_VERSION(8,4)
#define AUD_NUM_ACC_MODES                        0x0046
#endif /* AUD_ISI_MIN_VERSION(8,2) && !AUD_ISI_MIN_VERSION(8,4) */


#if AUD_ISI_MIN_VERSION(8,4) && !AUD_ISI_MIN_VERSION(8,5)
#define AUD_NUM_ACC_MODES                        0x0049
#endif /* AUD_ISI_MIN_VERSION(8,4) && !AUD_ISI_MIN_VERSION(8,5) */


#if AUD_ISI_MIN_VERSION(8,5) && !AUD_ISI_MIN_VERSION(8,6)
#define AUD_NUM_ACC_MODES                        0x004A
#endif /* AUD_ISI_MIN_VERSION(8,5) && !AUD_ISI_MIN_VERSION(8,6) */


#if AUD_ISI_MIN_VERSION(8,6) && !AUD_ISI_MIN_VERSION(8,12)
#define AUD_NUM_ACC_MODES                        0x004C
#endif /* AUD_ISI_MIN_VERSION(8,6) && !AUD_ISI_MIN_VERSION(8,12) */


#if AUD_ISI_MIN_VERSION(8,12) && !AUD_ISI_MIN_VERSION(9,3)
#define AUD_NUM_ACC_MODES                        0x004E
#endif /* AUD_ISI_MIN_VERSION(8,12) && !AUD_ISI_MIN_VERSION(9,3) */


#if AUD_ISI_MIN_VERSION(9,3) && !AUD_ISI_MIN_VERSION(9,8)
#define AUD_NUM_ACC_MODES                        0x4F
#endif /* AUD_ISI_MIN_VERSION(9,3) && !AUD_ISI_MIN_VERSION(9,8) */


#if AUD_ISI_MIN_VERSION(9,8)
#define AUD_NUM_ACC_MODES                        0x0050
#endif /* AUD_ISI_MIN_VERSION(9,8) */

#define AUD_NUM_CELL_MODES                       0x0002
#define AUD_NUM_SERVICES                         0x09
#define AUD_NUM_ANALOG_IN_ATTRIBUTES             0x0003
#define AUD_NUM_ANALOG_IN_VOLUME_LEVELS          0x0A
#define AUD_NUM_ANALOG_OUT_ATTRIBUTES            0x0003
#define AUD_NUM_ANALOG_OUT_VOLUME_LEVELS         0x0A

#if !AUD_ISI_MIN_VERSION(7,0)
#define AUD_NUM_DSP_PARAMS_ATTRIBUTES            0x0004
#endif /* !AUD_ISI_MIN_VERSION(7,0) */


#if AUD_ISI_MIN_VERSION(7,0) && !AUD_ISI_MIN_VERSION(9,11)
#define AUD_NUM_DSP_PARAMS_ATTRIBUTES            0x0007
#endif /* AUD_ISI_MIN_VERSION(7,0) && !AUD_ISI_MIN_VERSION(9,11) */


#if AUD_ISI_MIN_VERSION(9,11)
#define AUD_NUM_DSP_PARAMS_ATTRIBUTES            0x0009
#endif /* AUD_ISI_MIN_VERSION(9,11) */

#define AUD_NUM_DTMF_ATTRIBUTES                  0x0003
#define AUD_NUM_DTMF_VOLUME_LEVELS               0x0A
#define AUD_NUM_TONE_ATTRIBUTES                  0x000D
#define AUD_NUM_TONE_VOLUME_LEVELS               0x0A

#if !AUD_ISI_MIN_VERSION(6,9)
#define AUD_NUM_MIXER_ATTRIBUTES                 0x0F
#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES
#endif /* !AUD_ISI_MIN_VERSION(6,9) */


#if AUD_ISI_MIN_VERSION(6,9) && !AUD_ISI_MIN_VERSION(7,7)
#define AUD_NUM_MIXER_ATTRIBUTES                 0x10
#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES
#endif /* AUD_ISI_MIN_VERSION(6,9) && !AUD_ISI_MIN_VERSION(7,7) */


#if AUD_ISI_MIN_VERSION(7,7) && !AUD_ISI_MIN_VERSION(8,0)
#define AUD_NUM_MIXER_ATTRIBUTES                 0x11
#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES
#endif /* AUD_ISI_MIN_VERSION(7,7) && !AUD_ISI_MIN_VERSION(8,0) */


#if AUD_ISI_MIN_VERSION(8,0) && !AUD_ISI_MIN_VERSION(9,14)
#define AUD_NUM_MIXER_ATTRIBUTES                 0x12
#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES
#endif /* AUD_ISI_MIN_VERSION(8,0) && !AUD_ISI_MIN_VERSION(9,14) */


#if AUD_ISI_MIN_VERSION(9,14)
#define AUD_NUM_MIXER_ATTRIBUTES                 0x13
#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES
#endif /* AUD_ISI_MIN_VERSION(9,14) */


#if !AUD_ISI_MIN_VERSION(8,19)
#define AUD_NUM_MODE_ATTRIBUTES                  0x0002
#endif /* !AUD_ISI_MIN_VERSION(8,19) */


#if AUD_ISI_MIN_VERSION(8,19)
#define AUD_NUM_MODE_ATTRIBUTES                  0x0003
#endif /* AUD_ISI_MIN_VERSION(8,19) */

#define AUD_DIGITAL_OUT_VOL_LEVEL                0x00
#define AUD_NUM_DIGITAL_OUT_ATTRIBUTES           0x0006
#define AUD_NUM_DIGITAL_OUT_VOLUME_LEVELS        0x0A
#define AUD_NUM_AUD_MUTE_ATTRIBUTES              0x03

#if !AUD_ISI_MIN_VERSION(6,14)
#define AUD_NUM_MIXER_UL_IN_ATTRIBUTES           0x0007
#endif /* !AUD_ISI_MIN_VERSION(6,14) */


#if AUD_ISI_MIN_VERSION(6,14) && !AUD_ISI_MIN_VERSION(7,3)
#define AUD_NUM_MIXER_UL_IN_ATTRIBUTES           0x000A
#endif /* AUD_ISI_MIN_VERSION(6,14) && !AUD_ISI_MIN_VERSION(7,3) */


#if AUD_ISI_MIN_VERSION(7,3) && !AUD_ISI_MIN_VERSION(7,7)
#define AUD_NUM_MIXER_UL_IN_ATTRIBUTES           0x000B
#endif /* AUD_ISI_MIN_VERSION(7,3) && !AUD_ISI_MIN_VERSION(7,7) */


#if AUD_ISI_MIN_VERSION(7,7) && !AUD_ISI_MIN_VERSION(9,3)
#define AUD_NUM_MIXER_UL_IN_ATTRIBUTES           0x000C
#endif /* AUD_ISI_MIN_VERSION(7,7) && !AUD_ISI_MIN_VERSION(9,3) */


#if AUD_ISI_MIN_VERSION(9,3) && !AUD_ISI_MIN_VERSION(9,10)
#define AUD_NUM_MIXER_UL_IN_ATTRIBUTES           0x0F
#endif /* AUD_ISI_MIN_VERSION(9,3) && !AUD_ISI_MIN_VERSION(9,10) */


#if AUD_ISI_MIN_VERSION(9,10)
#define AUD_NUM_MIXER_UL_IN_ATTRIBUTES           0x0010
#endif /* AUD_ISI_MIN_VERSION(9,10) */


#if !AUD_ISI_MIN_VERSION(6,8)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x0009
#endif /* !AUD_ISI_MIN_VERSION(6,8) */


#if AUD_ISI_MIN_VERSION(6,8) && !AUD_ISI_MIN_VERSION(6,13)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x000C
#endif /* AUD_ISI_MIN_VERSION(6,8) && !AUD_ISI_MIN_VERSION(6,13) */


#if AUD_ISI_MIN_VERSION(6,13) && !AUD_ISI_MIN_VERSION(7,1)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x000D
#endif /* AUD_ISI_MIN_VERSION(6,13) && !AUD_ISI_MIN_VERSION(7,1) */


#if AUD_ISI_MIN_VERSION(7,1) && !AUD_ISI_MIN_VERSION(7,4)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x000E
#endif /* AUD_ISI_MIN_VERSION(7,1) && !AUD_ISI_MIN_VERSION(7,4) */


#if AUD_ISI_MIN_VERSION(7,4) && !AUD_ISI_MIN_VERSION(7,5)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x0010
#endif /* AUD_ISI_MIN_VERSION(7,4) && !AUD_ISI_MIN_VERSION(7,5) */


#if AUD_ISI_MIN_VERSION(7,5) && !AUD_ISI_MIN_VERSION(7,7)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x0013
#endif /* AUD_ISI_MIN_VERSION(7,5) && !AUD_ISI_MIN_VERSION(7,7) */


#if AUD_ISI_MIN_VERSION(7,7) && !AUD_ISI_MIN_VERSION(8,5)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x001B
#endif /* AUD_ISI_MIN_VERSION(7,7) && !AUD_ISI_MIN_VERSION(8,5) */


#if AUD_ISI_MIN_VERSION(8,5) && !AUD_ISI_MIN_VERSION(8,15)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x001C
#endif /* AUD_ISI_MIN_VERSION(8,5) && !AUD_ISI_MIN_VERSION(8,15) */


#if AUD_ISI_MIN_VERSION(8,15) && !AUD_ISI_MIN_VERSION(9,7)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x001E
#endif /* AUD_ISI_MIN_VERSION(8,15) && !AUD_ISI_MIN_VERSION(9,7) */


#if AUD_ISI_MIN_VERSION(9,7) && !AUD_ISI_MIN_VERSION(9,10)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x0021
#endif /* AUD_ISI_MIN_VERSION(9,7) && !AUD_ISI_MIN_VERSION(9,10) */


#if AUD_ISI_MIN_VERSION(9,10)
#define AUD_NUM_MIXER_DL_OUT_ATTRIBUTES          0x0023
#endif /* AUD_ISI_MIN_VERSION(9,10) */


#if !AUD_ISI_MIN_VERSION(6,1)
#define AUD_NUM_TEST_TYPES                       0x08
#endif /* !AUD_ISI_MIN_VERSION(6,1) */


#if AUD_ISI_MIN_VERSION(6,1) && !AUD_ISI_MIN_VERSION(6,3)
#define AUD_NUM_TEST_TYPES                       0x0A
#endif /* AUD_ISI_MIN_VERSION(6,1) && !AUD_ISI_MIN_VERSION(6,3) */


#if AUD_ISI_MIN_VERSION(6,3) && !AUD_ISI_MIN_VERSION(7,4)
#define AUD_NUM_TEST_TYPES                       0x0C
#endif /* AUD_ISI_MIN_VERSION(6,3) && !AUD_ISI_MIN_VERSION(7,4) */


#if AUD_ISI_MIN_VERSION(7,4) && !AUD_ISI_MIN_VERSION(7,5)
#define AUD_NUM_TEST_TYPES                       0x0F
#endif /* AUD_ISI_MIN_VERSION(7,4) && !AUD_ISI_MIN_VERSION(7,5) */


#if AUD_ISI_MIN_VERSION(7,5) && !AUD_ISI_MIN_VERSION(7,7)
#define AUD_NUM_TEST_TYPES                       0x11
#endif /* AUD_ISI_MIN_VERSION(7,5) && !AUD_ISI_MIN_VERSION(7,7) */


#if AUD_ISI_MIN_VERSION(7,7) && !AUD_ISI_MIN_VERSION(8,16)
#define AUD_NUM_TEST_TYPES                       0x15
#endif /* AUD_ISI_MIN_VERSION(7,7) && !AUD_ISI_MIN_VERSION(8,16) */


#if AUD_ISI_MIN_VERSION(8,16) && !AUD_ISI_MIN_VERSION(8,17)
#define AUD_NUM_TEST_TYPES                       0x1A
#endif /* AUD_ISI_MIN_VERSION(8,16) && !AUD_ISI_MIN_VERSION(8,17) */


#if AUD_ISI_MIN_VERSION(8,17)
#define AUD_NUM_TEST_TYPES                       0x1D
#endif /* AUD_ISI_MIN_VERSION(8,17) */

#define AUD_NUM_ERROR_CAUSES                     0x0008
#define AUD_NUM_OPERATIONS                       0x0005
#define AUD_NUM_SETTING_STATUSES                 0x0005

#if !AUD_ISI_MIN_VERSION(5,28)
#define AUD_NUM_CLIENT_TYPES                     0x000B
#endif /* !AUD_ISI_MIN_VERSION(5,28) */


#if AUD_ISI_MIN_VERSION(5,28) && !AUD_ISI_MIN_VERSION(7,1)
#define AUD_NUM_CLIENT_TYPES                     0x000C
#endif /* AUD_ISI_MIN_VERSION(5,28) && !AUD_ISI_MIN_VERSION(7,1) */


#if AUD_ISI_MIN_VERSION(7,1)
#define AUD_NUM_CLIENT_TYPES                     0x000D
#endif /* AUD_ISI_MIN_VERSION(7,1) */

#define FTD_ACC                                  0x00
#define FTD_AD                                   0x01
#define FTD_ULI                                  0x02
#define FTD_DLO                                  0x03
#define FTD_GAIN                                 0x04
#define FTD_VOL                                  0x05
#define FTD_DPW                                  0x06
#define FTD_UPW                                  0x07
#define COMM_FTD_DATA_AUD_BASE                   0x01A0
#define AUD_COMM_FTD_DATA_NUM                    0x08
#define AUD_PAUSE                                0x00
#define AUD_DSP_MAX_PARDATA_LEN                  0x80
#define AUD_LOOPBACK_GAIN_DEFAULT                0x7FFF
#define AUD_EQU_MAX_NAME_LENGTH                  0x14

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MODE_VALUES                                         */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MODE_VALUES_CONST;

#define AUD_MODE_HP                              0x00  /* Handportable */
#define AUD_MODE_HDC5                            0x01  /* Headset HDC5 */
/* Headset HDC9, to be removed */
#define AUD_MODE_HDC9                            0x02
/* Loopset LPS1, to be removed */
#define AUD_MODE_LPS1                            0x03
#define AUD_MODE_LPS3                            0x04  /* Loopset LPS3 */
/* Plug & Play handsfree */
#define AUD_MODE_PPHF                            0x05
/* Plug & Play handsfree with external mic */
#define AUD_MODE_PPHF_EXT_MIC                    0x06
/* Car kit HFU2, to be removed */
#define AUD_MODE_CAR_HFU2                        0x07
/* Car kit HFU2 with handset off-hooked, to be removed */
#define AUD_MODE_CAR_HFU2_HS                     0x08
/* Handportable with ANCO codec */
#define AUD_MODE_ANCO_HP                         0x09
/* Handportable with ANCO codec, ANC ON */
#define AUD_MODE_ANCO_ANC                        0x0A
/* Handportable with ANCO codec, IHF ON */
#define AUD_MODE_ANCO_IHF                        0x0B
/* Smart accessory contains audio resources */
#define AUD_MODE_SMART_ACCESSORY                 0x0C
/* Integrated handsfree mode */
#define AUD_MODE_IHF                             0x0D
#define AUD_MODE_MSTI                            0x0E  /* MSTI test mode */
/* FM Radio audio mode */
#define AUD_MODE_FM_RADIO                        0x0F
/* Test mode for production line */
#define AUD_MODE_TEST                            0x10
/* TTY/TDD accessory device */
#define AUD_MODE_TTY                             0x11
/* HP with Slide/grip opened */
#define AUD_MODE_HP_SLIDE_OPEN                   0x12
/* HP with Active Cover ON */
#define AUD_MODE_ACTIVE_COVER                    0x13
/* FM Radio over IHF */
#define AUD_MODE_FM_RADIO_OVER_IHF               0x14
/* TOMAHAWK: Mono Headset */
#define AUD_MODE_THWK_HD_MO                      0x15
/* TOMAHAWK: Stereo Headset */
#define AUD_MODE_THWK_HD_ST                      0x16
/* TOMAHAWK: Loopset */
#define AUD_MODE_THWK_LPS                        0x17
/* TOMAHAWK: Basic Handsfree */
#define AUD_MODE_THWK_BHF                        0x18
/* TOMAHAWK: Advanced Handsfree */
#define AUD_MODE_THWK_HFU                        0x19
/* TOMAHAWK: Advanced Handsfree with external mic */
#define AUD_MODE_THWK_EXT_HS                     0x1A
/* TOMAHAWK: Music Deskstand(Office Stereo) */
#define AUD_MODE_THWK_HF_ST                      0x1B
/* Push Over Cellular */
#define AUD_MODE_POC                             0x1C
/* TOMAHAWK: Generic accessory with ACI audio block */
#define AUD_MODE_THWK_GENERIC                    0x1D
/* Universal headset */
#define AUD_MODE_UNIV_HEADSET                    0x1E
/* TTY using Universal HD plug */
#define AUD_MODE_UNIV_TTY                        0x1F
/* FM radio using universal headset */
#define AUD_MODE_UNIV_FM_RADIO                   0x20
/* Tomahawk headset HS-8 */
#define AUD_MODE_POC_HD                          0x21
/* Tomahawk carkit HF-2 */
#define AUD_MODE_POC_HF                          0x22
/* Loopset auxiliary mic */
#define AUD_MODE_LPS_AUMIC                       0x23
/* Loopset External input */
#define AUD_MODE_LPS_EXT_IN                      0x24
/* Tomahawk test box */
#define AUD_MODE_THWK_TEST_BOX                   0x25
/* Hearing Aid Compability */
#define AUD_MODE_HAC                             0x26
/* Bluetooth streaming */
#define AUD_MODE_BTHSTREAM                       0x27
#define AUD_MODE_CK_10                           0x28  /* Car kit CK-10 */
/* Audio Test Cable SB-8 */
#define AUD_MODE_TEST_CABLE                      0x29
#define AUD_MODE_HD_ST_2                         0x2A  /* HS-23 */
/* Stereo mic mode */
#define AUD_MODE_STEREO_MIC                      0x2B
/* External mic mode */
#define AUD_MODE_EXT_MIC                         0x2C
/* Universal stereo headset */
#define AUD_MODE_UNIV_STEREO                     0x2D
/* Universal stereo headset with external mic */
#define AUD_MODE_UNIV_STEREO_EXT_MIC             0x2E
/* Line-in recording mode */
#define AUD_MODE_LINE_IN_REC                     0x2F
/* FM Radio recording mode */
#define AUD_MODE_FM_RADIO_REC                    0x30
/* PHAP mode for HP */
#define AUD_MODE_PHAP_HP                         0x31
/* PHAP mode for slide feature */
#define AUD_MODE_PHAP_HP_SLIDE_OPEN              0x32
#define AUD_MODE_TVOUT                           0x33  /* TV-OUT mode */
/* Nokia AV stereo Headset with microphone */
#define AUD_MODE_AV_STEREO_HD                    0x34
/* Nokia AV stereo Headset, no microphone in headset */
#define AUD_MODE_AV_STEREO_HD_HP_MIC             0x35
/* Nokia AV Generic audio mode for Audio block accesories */
#define AUD_MODE_AV_GENERIC                      0x36
#define AUD_MODE_AD15                            0x37  /* AD-15i */

#if AUD_ISI_MIN_VERSION(6,7) && !AUD_ISI_MIN_VERSION(6,11)
#define AUD_MODE_HS29                            0x38  /* HS-29 */
#endif /* AUD_ISI_MIN_VERSION(6,7) && !AUD_ISI_MIN_VERSION(6,11) */


#if AUD_ISI_MIN_VERSION(6,7) && !AUD_ISI_MIN_VERSION(6,11)
#define AUD_MODE_HS20                            0x39  /* HS-20 */
#endif /* AUD_ISI_MIN_VERSION(6,7) && !AUD_ISI_MIN_VERSION(6,11) */


#if AUD_ISI_MIN_VERSION(6,11)
#define AUD_MODE_HS20                            0x38  /* HS-20 */
#endif /* AUD_ISI_MIN_VERSION(6,11) */


#if AUD_ISI_MIN_VERSION(6,11)
#define AUD_MODE_HS29                            0x39  /* HS-29 */
#endif /* AUD_ISI_MIN_VERSION(6,11) */

#define AUD_MODE_STEREO_CAR_HF                   0x3A  /* Stereo Car HF */
/* Nokia AV Basic HF */
#define AUD_MODE_AV_BASIC_HF                     0x3B
/* Nokia AV External mic */
#define AUD_MODE_AV_EXT_MIC                      0x3C
/* Nokia AV TTY device */
#define AUD_MODE_AV_TTY                          0x3D
/* Speech recording mode */
#define AUD_MODE_SPEECH_REC                      0x3E
/* Video recording mode */
#define AUD_MODE_VIDEO_REC                       0x3F
#define AUD_MODE_THWK_HIFI_HD                    0x40  /* HIFI headset */
/* HS-27R Stereo Radio Headset */
#define AUD_MODE_THWK_RADIO_HD                   0x41
#define AUD_MODE_LINE_OUT                        0x42  /* Line out */
/* USB Audio Headset */
#define AUD_MODE_USB_HD                          0x43
/* USB Audio Car HF */
#define AUD_MODE_USB_CAR_HF                      0x44
/* Audio recording mode */
#define AUD_MODE_AUDIO_REC                       0x45
/* FM Radio USB Headset */
#define AUD_MODE_FM_RADIO_USB                    0x46
#define AUD_MODE_USB_HD_HP_MIC                   0x47  /* USB headphones */
/* USB external mic */
#define AUD_MODE_USB_EXT_MIC                     0x48
#define AUD_MODE_MOBILE_TV                       0x49  /* Mobile TV */
#define AUD_MODE_FMTX_ONLY                       0x4A  /* FM Radio TX */
/* FM Radio TX and Phone */
#define AUD_MODE_FMTX_AND_PHONE                  0x4B
/* PoC HS(HS-9) accessory mode for Kodiak */
#define AUD_MODE_POC_HS                          0x4C
/* PoC BTH(BT headsets) accessory mode for Kodiak */
#define AUD_MODE_POC_BTH                         0x4D
/* HP with Slide/grip short opened */
#define AUD_MODE_HP_SLIDE_SHORT_OPEN             0x4E
#define AUD_MODE_USB_TTY                         0x4F  /* USB tty device */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MODE_ANA_DIGI                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MODE_ANA_DIGI_CONST;

/* Logical digital volume level, valid values 0-9 */
#define AUD_MODE_DIGITAL                         0x00
/* Absolute digital volume level which will be send to DSP */
#define AUD_MODE_ANALOG                          0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_SERVICES_ALL                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_SERVICES_ALL_CONST;

#define AUD_ANALOG_IN                            0x00  /* Microphones */
#define AUD_ANALOG_OUT                           0x01  /* Speakers */
/* DSP enhancement algorithms */
#define AUD_DSP_PARAMS                           0x02
/* DTMF generation */
#define AUD_DTMF                                 0x03
/* Tone generation */
#define AUD_TONE                                 0x04
#define AUD_MIXER                                0x05  /* Audio routing */
#define AUD_MODE                                 0x06  /* Audio mode */
/* Digital Volume Level */
#define AUD_DIGITAL_OUT                          0x07
#define AUD_MUTE                                 0x08  /* Mute */
#define AUD_ALL_SERVICES                         0x09

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ANALOG_IN_ATTRIBUTES_ALL                            */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ANALOG_IN_ATTRIBUTES_ALL_CONST;

/* Logical microphone gain level, valid values 0-9 */
#define AUD_ANALOG_IN_GAIN_LEVEL                 0x00
/* Absolute value in audio codec's MIC gain register */
#define AUD_ANALOG_IN_GAIN_ABS_VALUE             0x01
/* Sidetone, valid values 0-2 */
#define AUD_ANALOG_IN_SIDETONE                   0x02
#define AUD_ALL_ATTRIBUTES                       0x3F

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ANALOG_OUT_ATTRIBUTES_ALL                           */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ANALOG_OUT_ATTRIBUTES_ALL_CONST;

/* Logical volume level, valid values 0-9 */
#define AUD_ANALOG_OUT_VOL_LEVEL                 0x00
/* Absolute value in audio codec's EAR gain register */
#define AUD_ANALOG_OUT_VOL_ABS_VALUE             0x01
/* Balanced volume level in percents */
#define AUD_ANALOG_OUT_VOL_BALANCE               0x02
/* #define AUD_ALL_ATTRIBUTES                    0x3F (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_DSP_PARAMS_ATTRIBUTES_ALL                           */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_DSP_PARAMS_ATTRIBUTES_ALL_CONST;

/* Adjustment parameter block (size 2-128 bytes) for enhancement algorithms
   run by DSP. Audio server doesn't understand the contents of the block
*/
#define AUD_DSP_PARAM_BLOCK                      0x00
/* Basic audio enhancement algorithms to be run by DSP */
#define AUD_DSP_ALGORITHMS_1                     0x01
/* Additional enhancement algorithms to be run by DSP */
#define AUD_DSP_ALGORITHMS_2                     0x02
/* Adjustable PHAP settings( 0x00 - 0x04 ) */
#define AUD_DSP_PHAP                             0x03
/* Additional enhancement algorithms to be run by DSP */
#define AUD_DSP_ALGORITHMS_3                     0x04
/* Additional enhancement algorithms to be run by DSP */
#define AUD_DSP_ALGORITHMS_4                     0x05
/* Additional enhancement algorithms to be run by DSP */
#define AUD_DSP_ALGORITHMS_5                     0x06
/* ACA algorithm switches */
#define AUD_DSP_ACA_ALGORITHMS                   0x07
/* ACA control bitmask to signal which switches are controlled by the client.
*/
#define AUD_DSP_ACA_ALGORITHMS_MASK              0x08
/* #define AUD_ALL_ATTRIBUTES                    0x3F (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_DTMF_ATTRIBUTES_ALL                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_DTMF_ATTRIBUTES_ALL_CONST;

/* DTMF generation start/stop switch */
#define AUD_DTMF_SWITCH                          0x00
/* Digit information for producing the tone.Valid values are 0 and ASCII
   values of 0, 1, _, 9, #, *, A, B, C, D
*/
#define AUD_DTMF_DIGIT                           0x01
/* Volume level of the tone, valid values are 0-10. NOTE: Value 0 means a
   pause, it advices audio server not perform unnecessary power-off-on
   sequence for audio circuits between tones
*/
#define AUD_DTMF_VOLUME_LEVEL                    0x02
/* #define AUD_ALL_ATTRIBUTES                    0x3F (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_TONE_ATTRIBUTES_ALL                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_TONE_ATTRIBUTES_ALL_CONST;

/* Tone generation start/stop switch for channel 1, available values
   AUD_SWITCH_ON/_OFF
*/
#define AUD_TONE_SWITCH_1                        0x00
/* Frequency for the tone channel 1. Available values 0-65535. NOTE: The
   required accuracy for tone frequencies isn't known at the moment
*/
#define AUD_TONE_FREQUENCY_1                     0x01
/* Volume level for the tone channel 1. Valid values are 0-10. NOTE: Value 0
   means a pause, it advices audio server not perform unnecessary
   power-off-on sequence for audio circuits between tones
*/
#define AUD_TONE_VOLUME_LEVEL_1                  0x02
/* Ref AUD_TONE_SWITCH_1 */
#define AUD_TONE_SWITCH_2                        0x03
/* Frequency for the tone channel 2. Available values 0-65535 */
#define AUD_TONE_FREQUENCY_2                     0x04
/* Volume level for the tone channel 2,  ref AUD_TONE_VOLUME_LEVEL_1 */
#define AUD_TONE_VOLUME_LEVEL_2                  0x05
/* Ref AUD_TONE_SWITCH_1 */
#define AUD_TONE_SWITCH_3                        0x06
/* Frequency for the tone channel 3. Available values 0-65535 */
#define AUD_TONE_FREQUENCY_3                     0x07
/* Volume level for the tone channel 3, ref AUD_TONE_VOLUME_LEVEL_1 */
#define AUD_TONE_VOLUME_LEVEL_3                  0x08
/* Ref AUD_TONE_SWITCH_1 */
#define AUD_TONE_SWITCH_4                        0x09
/* Frequency for the tone channel 4. Available values 0-65535 */
#define AUD_TONE_FREQUENCY_4                     0x0A
/* Volume level for the tone channel 4, ref AUD_TONE_VOLUME_LEVEL_1 */
#define AUD_TONE_VOLUME_LEVEL_4                  0x0B
/* Type of the tone sequence to which the requested tone type belongs to. On
   the basis of this value audio server is able to make decisions concerning
   tone routing for smart accessories
*/
#define AUD_TONE_SEQUENCE_TYPE                   0x0C
/* #define AUD_ALL_ATTRIBUTES                    0x3F (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MIXER_ATTRIBUTES_ALL                                */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MIXER_ATTRIBUTES_ALL_CONST;

/* Audio uplink path physical power switch, available values AUD_SWITCH_ON /
   _OFF
*/
#define AUD_MIXER_UL_POWER_SWITCH                0x00
/* Audio uplink path physical input selection */
#define AUD_MIXER_UL_IN_SELECT                   0x01
/* Audio uplink path input logical mute switch, available values
   AUD_SWITCH_ON / _OFF
*/
#define AUD_MIXER_UL_IN_SWITCH                   0x02
/* Audio uplink path output logical mute switch */
#define AUD_MIXER_UL_OUT_SWITCH                  0x03
/* DTMF generation physical output device selection */
#define AUD_MIXER_DTMF_OUT_SELECT                0x04
/* Tone generation physical output device selection */
#define AUD_MIXER_TONE_OUT_SELECT                0x05
/* Audio downlink path physical power switch */
#define AUD_MIXER_DL_POWER_SWITCH                0x06
/* Audio downlink path input logical mute switch */
#define AUD_MIXER_DL_IN_SWITCH                   0x07
/* Audio downlink path input logical mute switch */
#define AUD_MIXER_DL_OUT_SWITCH                  0x08
/* Audio downlink path physical output selection */
#define AUD_MIXER_DL_OUT_SELECT                  0x09
/* Audio mixer mode output selection, available values:
   AUD_MIXER_MODE_OUT_STEREO / _MONO
*/
#define AUD_MIXER_MODE_OUT_SELECT                0x0A
/* Audio quality mode output selection */
#define AUD_MIXER_QUALITY_SELECT                 0x0B
/* Audio application input selection */
#define AUD_MIXER_APP_IN_SELECT                  0x0C
/* Audio application uplink path input selection */
#define AUD_MIXER_APP_UL_SELECT                  0x0D
/* Audio application  recording input selection */
#define AUD_MIXER_APP_REC_SELECT                 0x0E
/* Audio FM transmitter out selection */
#define AUD_MIXER_DL_OUT_TRANSMIT_SELECT         0x0F
/* Audio DAC33 Playback Mode selection */
#define AUD_MIXER_PLAYBACK_MODE_SELECT           0x10
/* APE Speech tone switch, enables tone mixing to APE Speech rec. Predefined
   gain value is send to DSP when switch is ON (AUD_SWITCH_ON / _OFF)
*/
#define AUD_MIXER_APE_SPEECH_TONE_SWITCH         0x11
/* Sidetone path mute switch. Available values: AUD_SWITCH_ON / _OFF. */
#define AUD_MIXER_SIDETONE_SWITCH                0x12
/* #define AUD_ALL_ATTRIBUTES                    0x3F (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MODE_ATTRIBUTES_ALL                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MODE_ATTRIBUTES_ALL_CONST;

/* Sets the operation mode in case the server is running in a dual-mode phone
*/
#define AUD_MODE_ANA_DIGI                        0x00
/* Tells the accessory mode that audio server is currently using. NOTE:This
   attribute is mainly updated internally by audio server (according the
   accessory information provided by ACC server & smart accessories).
   However, UI client can also update this attribute concerning ANC and IHF
   modes when ANCO chip is used
*/
#define AUD_MODE_ACCESSORY                       0x01
/* Secondary audio mode, this enables the possibility to have 2 audio modes
   in parallel in Audio Server. For example, this is used for FM Radio
   recording use case, where AUD_MODE_FM_RADIO_REC is added as secondary to
   already existing primary mode. The only supported value at the moment is
   AUD_MODE_FM_RADIO_REC. 
*/
#define AUD_MODE_SECONDARY                       0x02
/* #define AUD_ALL_ATTRIBUTES                    0x3F (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_DIGITAL_OUT_ATTRIBUTES_ALL                          */
/* ----------------------------------------------------------------------- */
/* AUD_DIGITAL_OUT_VOL_LEVEL and AUD_DIGITAL_OUT_SPEECH_GAIN_LOG are using
   the same hex value 0x00, to be backward compatible.
*/
typedef uint8 AUD_DIGITAL_OUT_ATTRIBUTES_ALL_CONST;

/* Logical digital volume level for speech (former AUD_DIGITAL_OUT_VOL_LEVEL)
*/
#define AUD_DIGITAL_OUT_SPEECH_GAIN_LOG          0x00
/* Absolute digital volume level */
#define AUD_DIGITAL_OUT_ABS_VALUE                0x01
/* Logical digital volume level for music playback */
#define AUD_DIGITAL_OUT_AUDIO_GAIN_LOG           0x02
/* Logical digital volume level for CMT DL */
#define AUD_DIGITAL_OUT_CMTDL_GAIN_LOG           0x03
/* Logical digital volume level for CMT UL */
#define AUD_DIGITAL_OUT_CMTUL_GAIN_LOG           0x04
/* Logical digital volume level for recording */
#define AUD_DIGITAL_OUT_REC_GAIN_LOG             0x05
/* #define AUD_ALL_ATTRIBUTES                    0x3F (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MUTE_ATTRIBUTES_ALL                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MUTE_ATTRIBUTES_ALL_CONST;

/* Analog mute, values AUD_SWITCH_ON (mute on)/ AUD_SWITCH_OFF (mute off) */
#define AUD_ANA_MUTE_SWITCH                      0x00
/* Digital mute, values AUD_SWITCH_ON (mute on)/ AUD_SWITCH_OFF (mute off) */
#define AUD_DIGI_MUTE_SWITCH                     0x01
/* #define AUD_ALL_ATTRIBUTES                    0x3F (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EQU_FAILURE_REASON                                  */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EQU_FAILURE_REASON_CONST;

/* Operation is not possible for this equalizer id */
#define AUD_EQU_ID_ERROR                         0x00
/* Error in gain for equalizer bands */
#define AUD_EQU_GAIN_ERROR                       0x01
/* Error in frequency limits in equalizer bands */
#define AUD_EQU_LIMIT_FREQ_ERROR                 0x02
/* Invalid number of bands. Valid number of bands are from 2 to 8 */
#define AUD_EQU_BAND_NUM_ERROR                   0x03
/* Invalid equalizer Id or equalizer Id not found */
#define AUD_EQU_INVALID_ID                       0x04

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EQU_TYPE                                            */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EQU_TYPE_CONST;

/* Preset equalizer */
#define AUD_EQU_PRESET                           0x00
/* Graphical equalizer */
#define AUD_EQU_GRAPHICAL                        0x01
/* 2 bands equalizer, self adjustable */
#define AUD_EQU_TONE_CONTROL                     0x02
/* Other type, adjustable */
#define AUD_EQU_OTHER_ADJUSTABLE                 0x03
/* Other type, non-adjustable */
#define AUD_EQU_OTHER_NON_ADJUSTABLE             0x04

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EQU_STATE                                           */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EQU_STATE_CONST;

/* Deactivate equalizer */
#define AUD_EQU_OFF                              0x00
/* Activate equalizer */
#define AUD_EQU_ON                               0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_SCO_STATE                                           */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_SCO_STATE_CONST;

/* Bluetooth Audio SCO OFF */
#define AUD_SCO_OFF                              0x00
/* Bluetooth Audio SCO ON */
#define AUD_SCO_ON                               0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_SCO_STATUS                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_SCO_STATUS_CONST;

/* Bluetooth Audio SCO OK */
#define AUD_SCO_OK                               0x00
/* Bluetooth Audio SCO FAIL */
#define AUD_SCO_FAIL                             0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_AVDTP_COMMAND                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_AVDTP_COMMAND_CONST;

/* Configure codec */
#define AUD_AVDTP_CONFIGURE                      0x00

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_AVDTP_STREAM_TYPE                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_AVDTP_STREAM_TYPE_CONST;

/* SBC codec in use */
#define AUD_AVDTP_SBC_IN_USE                     0x00
/* SBC codec not in use */
#define AUD_AVDTP_SBC_NOT_IN_USE                 0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_AVDTP_STATUS                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_AVDTP_STATUS_CONST;

#define AUD_AVDTP_OK                             0x00  /* Ok */
#define AUD_AVDTP_FAIL                           0x01  /* Failed */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_DEFATTR_STATUS                                      */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_DEFATTR_STATUS_CONST;

#define AUD_DEFATTR_OK                           0x00  /* Ok */
#define AUD_DEFATTR_FAIL                         0x01  /* Failed */
/* Failed, Invalid service */
#define AUD_DEFATTR_FAIL_INVALID_SERVICE         0x02
/* Failed, Invalid Attribute ID */
#define AUD_DEFATTR_FAIL_INVALID_ATTR_ID         0x03
/* Failed, Invalid value */
#define AUD_DEFATTR_FAIL_INVALID_VALUE           0x04

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_VOLUME_CONTROL_TYPE - Valid from version 006.013    */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_VOLUME_CONTROL_TYPE_CONST;

/* Volume control is using % value */
#define AUD_VOLUME_PERCENT_CONTROL               0x01
/* Volume control is using Q8.7 value */
#define AUD_VOLUME_Q87_CONTROL                   0x02

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_VOLUME_MEDIA_TYPE - Valid from version 006.013       */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_VOLUME_MEDIA_TYPE_CONST;

/* Call volume */
#define AUD_CALL_VOLUME                          0x0001  /* ---------------1 */
/* Speech playback volume, example AMR NB */
#define AUD_SPEECH_PLAYBACK_VOLUME               0x0002  /* --------------1- */
/* Media playeback volume, example MP3, MIDI, AAC */
#define AUD_MEDIA_PLAYBACK_VOLUME                0x0004  /* -------------1-- */
/* Tradiotional tone volume, example key tones, NRT ringtones */
#define AUD_TRADITIONAL_TONE_VOLUME              0x0008  /* ------------1--- */
/* FM radio volume */
#define AUD_FM_RADIO_VOLUME                      0x0010  /* -----------1---- */
/* DTMF tone volume */
#define AUD_DTMF_TONE_VOLUME                     0x0020  /* ----------1----- */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_EANC_STATE - Valid from version 008.008             */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_EANC_STATE_CONST;

/* AIC3254 EANC OFF */
#define AUD_EANC_OFF                             0x00
/* AIC3254 EANC ON */
#define AUD_EANC_ON                              0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_TONE_SEQUENCE_TYPE                                  */
/* ----------------------------------------------------------------------- */
/* NOTE: Also tone generation methods may differ between above mentioned
   types. Some accessories are able to download whole ringing tone sequencies
   from the phone. In this case producing "RING" sequencies need only 'start
   sequence' and 'stop sequence' commands by audio server. Alert tones are
   always generated note by note
*/
typedef uint8 AUD_TONE_SEQUENCE_TYPE_CONST;

/* Normal ringing tone generation: tones are routed to all accessories */
#define AUD_TONE_SEQUENCE_RING                   0x00
/* User scans available ringing tones, thus starting tone generation: tones
   are routed only the primary audio target accessory
*/
#define AUD_TONE_SEQUENCE_RING_SCAN              0x01
/* Alert tones: tones are routed to all accessories */
#define AUD_TONE_SEQUENCE_ALERT                  0x02
/* Non-DTMF Key tones - e.g. soft keys, arrow keys, etc */
#define AUD_TONE_SEQUENCE_KEY                    0x03
/* Playback is routed to primary accessory. In case of no accessory
   connected, audio is routed to IHF speaker. Special functionality: if audio
   is routed to accessory and accessory is disconnected. Audio is not
   automatically routed to IHF. Instead Audio playback is muted
*/
#define AUD_TONE_SEQUENCE_MUSIC_PLAY             0x04

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ANALOG_OUT_VOL_BALANCE                              */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ANALOG_OUT_VOL_BALANCE_CONST;

/* Left earline is muted */
#define AUD_ANALOG_OUT_VOL_BALANCE_L0            0x00
/* 10% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L1            0x01
/* 20% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L2            0x02
/* 30% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L3            0x03
/* 40% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L4            0x04
/* 50% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L5            0x05
/* 60% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L6            0x06
/* 70% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L7            0x07
/* 80% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L8            0x08
/* 90% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L9            0x09
/* 100% volume on left earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_L10           0x0A
/* Right earline is muted */
#define AUD_ANALOG_OUT_VOL_BALANCE_R0            0x10
/* 10% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R1            0x11
/* 20% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R2            0x12
/* 30% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R3            0x13
/* 40% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R4            0x14
/* 50% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R5            0x15
/* 60% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R6            0x16
/* 70% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R7            0x17
/* 80% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R8            0x18
/* 90% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R9            0x19
/* 100% volume on right earline */
#define AUD_ANALOG_OUT_VOL_BALANCE_R10           0x1A
/* 100% volume left and right */
#define AUD_ANALOG_OUT_VOL_BALANCE_C             0x20

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MIXER_UL_IN_SELECT                                  */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MIXER_UL_IN_SELECT_CONST;

/* Audio input set muted */
#define AUD_MIXER_UL_IN_MUTED                    0x00
/* HD microphone selected */
#define AUD_MIXER_UL_IN_HD_MIC                   0x01
/* HF microphone selected */
#define AUD_MIXER_UL_IN_HF_MIC                   0x02
/* HP microphone selected */
#define AUD_MIXER_UL_IN_HP_MIC                   0x03
/* FM radio input line selected */
#define AUD_MIXER_UL_IN_FM_MIC                   0x04
/* BT microphone selected */
#define AUD_MIXER_UL_IN_BT                       0x05
/* DIGITAL microphone selected */
#define AUD_MIXER_UL_IN_DIGI                     0x06
/* Active cover microphone selected */
#define AUD_MIXER_UL_IN_FCI                      0x07
/* I2S microphone selected */
#define AUD_MIXER_UL_IN_I2S                      0x08
/* Digital stereo microphone selected */
#define AUD_MIXER_UL_IN_DIGI_STEREO              0x09
/* MIC3 with +20db (FM mic) */
#define AUD_MIXER_UL_IN_EXT_MIC                  0x0A
#define AUD_MIXER_UL_IN_USB_MIC                  0x0B  /* USB Microphone */
/* Eanc microphone 1 selected */
#define AUD_MIXER_UL_IN_EANC_MIC1                0x0C
/* Eanc microphone 2 selected */
#define AUD_MIXER_UL_IN_EANC_MIC2                0x0D
/* Both eanc microphones selected */
#define AUD_MIXER_UL_IN_EANC_BOTH_MICS           0x0E
/* Wide-Band BT microphone selected */
#define AUD_MIXER_UL_IN_BT_WB                    0x0F

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_LOOPBACK_OUT_SELECT - Valid from version 009.009    */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_LOOPBACK_OUT_SELECT_CONST;

/* Audio output muted */
#define AUD_LOOPBACK_OFF                         0x00
/* Audio output in HP ear */
#define AUD_LOOPBACK_OUT_HP                      0x01
/* Audio output in IHF */
#define AUD_LOOPBACK_OUT_IHF                     0x02
/* Audio output in AV */
#define AUD_LOOPBACK_OUT_AV                      0x03
/* Audio output in USB */
#define AUD_LOOPBACK_OUT_USB                     0x04
/* Audio output in HAC */
#define AUD_LOOPBACK_OUT_HAC                     0x05
/* Audio output in FM TX */
#define AUD_LOOPBACK_OUT_FM_TX                   0x06
/* Audio input in Signal analysis */
#define AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS         0x07

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_LOOPBACK_IN_SELECT - Valid from version 009.009     */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_LOOPBACK_IN_SELECT_CONST;

/* #define AUD_LOOPBACK_OFF                      0x00 (already defined) */
/* Audio input in HP mic */
#define AUD_LOOPBACK_IN_HP_MIC                   0x01
/* Audio input in HP mic2 */
#define AUD_LOOPBACK_IN_HP_MIC2                  0x02
/* Audio input in AV mic */
#define AUD_LOOPBACK_IN_AV_MIC                   0x03
/* Audio input in FM mic */
#define AUD_LOOPBACK_IN_FM_MIC                   0x04
/* Audio input in USB mic */
#define AUD_LOOPBACK_IN_USB_MIC                  0x05
/* Audio input in EANC mic1 */
#define AUD_LOOPBACK_IN_EANC_MIC1                0x06
/* Audio input in EANC mic2 */
#define AUD_LOOPBACK_IN_EANC_MIC2                0x07
/* Audio input in Tone generator */
#define AUD_LOOPBACK_IN_TONE_GENERATOR           0x08

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MIXER_DL_OUT_SELECT                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MIXER_DL_OUT_SELECT_CONST;

/* Audio output set muted */
#define AUD_MIXER_DL_OUT_MUTED                   0x00
/* HP speaker selected */
#define AUD_MIXER_DL_OUT_HP_EAR                  0x01
/* HD speaker selected */
#define AUD_MIXER_DL_OUT_HD_EAR                  0x02
/* HF speaker selected */
#define AUD_MIXER_DL_OUT_HF_EAR                  0x03
/* XEAR speaker selected  */
#define AUD_MIXER_DL_OUT_X_EAR                   0x04
/* HD stereo speakers selected  */
#define AUD_MIXER_DL_OUT_STEREO_HD_EAR           0x05
/* HF stereo speakers selected  */
#define AUD_MIXER_DL_OUT_STEREO_HF_EAR           0x06
/* IHF speaker selected  */
#define AUD_MIXER_DL_OUT_IHFSP                   0x07
/* BT speaker selected  */
#define AUD_MIXER_DL_OUT_BT_EAR                  0x08
/* Stereo IHF speaker, IHF speaker not connected to IHFSp */
#define AUD_MIXER_DL_OUT_EXT_IHF                 0x09
/* Left IHF speaker, IHF speaker not connected to IHFSpL */
#define AUD_MIXER_DL_OUT_EXT_IHF_LEFT            0x0A
/* Right IHF speaker, IHF speaker not connected to IHFSpR */
#define AUD_MIXER_DL_OUT_EXT_IHF_RIGHT           0x0B
/* Nokia AV bottom connector ear selection (amplifier) */
#define AUD_MIXER_DL_OUT_EXT_EAR_AMP             0x0C
/* I2S ear selected */
#define AUD_MIXER_DL_OUT_EAR_I2S                 0x0D
/* Nokia AV bottom connector ear selection (amplifier), left */
#define AUD_MIXER_DL_OUT_EXT_EAR_AMP_L           0x0E
/* Nokia AV bottom connector ear selection (amplifier), right */
#define AUD_MIXER_DL_OUT_EXT_EAR_AMP_R           0x0F
/* Stereo or dual mono ear with Acodec HFBias control (for e.g. AD-15) */
#define AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS          0x10
/* L channel ear with Acodec HFBias control (for e.g. AD-15) */
#define AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS_L        0x11
/* R channel ear with Acodec HFBias control (for e.g. AD-15) */
#define AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS_R        0x12
/* Stereo or dual mono ear for FMTX */
#define AUD_MIXER_DL_OUT_FMTX                    0x13
/* Left Channel ear for FMTX */
#define AUD_MIXER_DL_OUT_FMTX_L                  0x14
/* Right Channel ear for FMTX */
#define AUD_MIXER_DL_OUT_FMTX_R                  0x15
/* Stereo or dual mono ear for USB Audio */
#define AUD_MIXER_DL_OUT_USB                     0x16
/* Left Channel ear for USB Audio */
#define AUD_MIXER_DL_OUT_USB_L                   0x17
/* Right Channel ear for USB Audio */
#define AUD_MIXER_DL_OUT_USB_R                   0x18
/* Left Channel ear for HD Speaker */
#define AUD_MIXER_DL_OUT_HD_EAR_L                0x19
/* Right Channel ear for HD Speaker */
#define AUD_MIXER_DL_OUT_HD_EAR_R                0x1A
#define AUD_MIXER_DL_OUT_HAC                     0x1B  /* HAC selected */
/* I2S ear, left channel */
#define AUD_MIXER_DL_OUT_EAR_I2S_L               0x1C
/* I2S ear, right channel */
#define AUD_MIXER_DL_OUT_EAR_I2S_R               0x1D
#define AUD_MIXER_DL_OUT_IHF                     0x1E  /* IHF Stereo */
#define AUD_MIXER_DL_OUT_IHF_L                   0x1F  /* IHF Left */
#define AUD_MIXER_DL_OUT_IHF_R                   0x20  /* IHF Right */
/* Stereo BT speaker selected */
#define AUD_MIXER_DL_OUT_BT_STEREO               0x21
/* Wide-Band BT speaker selected */
#define AUD_MIXER_DL_OUT_BT_WB_EAR               0x22

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_MIXER_DTMF_OUT_SELECT                                */
/* ----------------------------------------------------------------------- */
/* The resulting attribute value is a sum of selected device values. E.g. if
   DTMF tones are to be routed to speaker and simultaneously recorded, this
   attribute contains value 0x05. The default routing is decided by audio
   server according to the current accessory mode.
*/
typedef uint8 AUD_MIXER_DTMF_OUT_SELECT_CONST;

/* DTMF output set muted */
#define AUD_MIXER_DTMF_OUT_MUTED                 0x00  /* -------- */
/* DTMF output routed to speaker */
#define AUD_MIXER_DTMF_OUT_EAR                   0x01  /* -------1 */
/* DTMF output routed to smart accessory */
#define AUD_MIXER_DTMF_OUT_ACC                   0x02  /* ------1- */
/* DTMF output routed to memory */
#define AUD_MIXER_DTMF_OUT_MEMORY                0x04  /* -----1-- */
/* DTMF output routed to TX path (in analog mode only) */
#define AUD_MIXER_DTMF_OUT_TX                    0x08  /* ----1--- */
/* DTMF default routing */
#define AUD_MIXER_DTMF_OUT_DEFAULT               0x80  /* 1------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_MIXER_TONE_OUT_SELECT                                */
/* ----------------------------------------------------------------------- */
/* The default routing is decided by audio server according to the current
   accessory mode.
*/
typedef uint8 AUD_MIXER_TONE_OUT_SELECT_CONST;

/* Tone output set muted */
#define AUD_MIXER_TONE_OUT_MUTED                 0x00  /* -------- */
/* Tone output routed to speaker */
#define AUD_MIXER_TONE_OUT_EAR                   0x01  /* -------1 */

#if !AUD_ISI_MIN_VERSION(8,0)
/* Tone output routed to smart accessory */
#define AUD_MIXER_TONE_OUT_ACC                   0x02  /* ------1- */
#endif /* !AUD_ISI_MIN_VERSION(8,0) */

/* High Quality Audio ( MIDI, MP3, etc) routed to ear path.Hand Portable when
   no accessory connected. With headset, routing will be headset ear piece
*/
#define AUD_MIXER_TONE_OUT_HQ_EAR                0x02  /* ------1- */

#if !AUD_ISI_MIN_VERSION(8,0)
/* Tone output routed to memory */
#define AUD_MIXER_TONE_OUT_MEMORY                0x04  /* -----1-- */
#endif /* !AUD_ISI_MIN_VERSION(8,0) */

/* Tone output is routed to HandPortable speaker, audio is speech type (sends
   some special settings to ADSP)
*/
#define AUD_MIXER_TONE_OUT_SPEECH_EAR            0x04  /* -----1-- */
/* Tone output routed to buzzer */
#define AUD_MIXER_TONE_OUT_BUZZER                0x08  /* ----1--- */
/* Tone is routed to high-quality players ( MIDI, MP3, etc.) */
#define AUD_MIXER_TONE_OUT_HIGH_QUALITY          0x10  /* ---1---- */
/* Tone output is routed to speaker and TX path, i.e. tone is locally played(
   according current audio mode) and is routed to remote phone side -
   effective only in call state
*/
#define AUD_MIXER_TONE_OUT_EAR_TX                0x21  /* --1----1 */
/* Tone output is routed to loudspeaker (depending on the value of
   AUD_TONE_SEQUENCE_TYPE) but audio is speech.To be used for speech playback
   (e.g AMR)
*/
#define AUD_MIXER_TONE_OUT_SPEECH                0x40  /* -1------ */
/* Tone default routing */
#define AUD_MIXER_TONE_OUT_DEFAULT               0x80  /* 1------- */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MIXER_MODE_OUT_SELECT                               */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MIXER_MODE_OUT_SELECT_CONST;

/* Audio output set to Mono */
#define AUD_MIXER_MODE_OUT_MONO                  0x00
/* Audio output set to Stereo */
#define AUD_MIXER_MODE_OUT_STEREO                0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MIXER_QUALITY_SELECT                                */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MIXER_QUALITY_SELECT_CONST;

/* Audio output quality set to NarrowBand */
#define AUD_MIXER_QUALITY_NB                     0x00
/* Audio output quality set to WideBand */
#define AUD_MIXER_QUALITY_WB                     0x01
/* Audio output quality set to HighQuality */
#define AUD_MIXER_QUALITY_HQ                     0x02

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_MIXER_APP_IN_SELECT                                  */
/* ----------------------------------------------------------------------- */
/* Note that this attribute is a bit field and that values can be set
   simultaneously.
*/
typedef uint8 AUD_MIXER_APP_IN_SELECT_CONST;

/* Audio application input is muted */
#define AUD_MIXER_APP_IN_MUTE                    0x00  /* -------- */
/* Audio application input is CMT DL */
#define AUD_MIXER_APP_IN_CMT_DL                  0x01  /* -------1 */
/* Audio application input is APE Speech */
#define AUD_MIXER_APP_IN_APE_SPEECH              0x02  /* ------1- */
/* Audio application input is APE Audio */
#define AUD_MIXER_APP_IN_APE_AUDIO               0x04  /* -----1-- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_MIXER_APP_UL_SELECT                                  */
/* ----------------------------------------------------------------------- */
/* Note that this attribute is a bit field and that values can be set
   simultaneously.
*/
typedef uint8 AUD_MIXER_APP_UL_SELECT_CONST;

/* Audio application uplink input is muted */
#define AUD_MIXER_APP_UL_MUTED                   0x00  /* -------- */
/* Audio application uplink input is microphone */
#define AUD_MIXER_APP_UL_MIC                     0x01  /* -------1 */
/* Audio application uplink input is tone */
#define AUD_MIXER_APP_UL_TONE                    0x02  /* ------1- */
/* Audio application uplink input is speech */
#define AUD_MIXER_APP_UL_SPEECH                  0x04  /* -----1-- */
/* Audio application uplink input is audio */
#define AUD_MIXER_APP_UL_AUDIO                   0x08  /* ----1--- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_MIXER_APP_REC_SELECT                                 */
/* ----------------------------------------------------------------------- */
/* Note that this attribute is a bit field and that values can be set
   simultaneously.
*/
typedef uint8 AUD_MIXER_APP_REC_SELECT_CONST;

/* Audio application recording input is muted */
#define AUD_MIXER_APP_REC_MUTED                  0x00  /* -------- */
/* Audio application recording input is microphone */
#define AUD_MIXER_APP_REC_MIC                    0x01  /* -------1 */
/* Audio application recording input is CMT DL */
#define AUD_MIXER_APP_REC_CMTDL                  0x02  /* ------1- */
/* Audio application recording input is High quality recording path (Video
   recording)
*/
#define AUD_MIXER_APE_AUD_REC                    0x04  /* -----1-- */
/* Enable DSP generated tones to APE Audio recording path */
#define AUD_MIXER_APE_TONE_AUD_REC               0x08  /* ----1--- */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MIXER_DL_OUT_TRANSMIT_SELECT - Valid from version 006.009 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MIXER_DL_OUT_TRANSMIT_SELECT_CONST;

/* Audio FM transmit output is OFF */
#define AUD_MIXER_DL_OUT_TRANSMIT_OFF            0x00
/* Audio FM transmit output is TX only */
#define AUD_MIXER_DL_OUT_TRANSMIT_TX_ONLY        0x01
/* Audio FM transmit output is TX and Phone */
#define AUD_MIXER_DL_OUT_TRANSMIT_TX_AND_PHONE   0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_MIXER_PLAYBACK_MODE_SELECT - Valid from version 007.007 */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_MIXER_PLAYBACK_MODE_SELECT_CONST;

/* DAC33 real time Playback mode, no buffering */
#define AUD_MIXER_PLAYBACK_REALTIME              0x00
/* DAC33 real time Powersave mode, buffering enabled */
#define AUD_MIXER_PLAYBACK_POWERSAVE             0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_TEST_TYPES                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_TEST_TYPES_CONST;


#if !AUD_ISI_MIN_VERSION(9,0)
/* Audio codec loop back path routing from HP microphone input to external
   speaker output
*/
#define AUD_TEST_HP_IN_EXT_OUT                   0x01
#endif /* !AUD_ISI_MIN_VERSION(9,0) */


#if !AUD_ISI_MIN_VERSION(9,0)
/* Audio codec loop back path routing from external microphone input to HP
   speaker output
*/
#define AUD_TEST_EXT_IN_HP_OUT                   0x02
#endif /* !AUD_ISI_MIN_VERSION(9,0) */

/* Audio codec loop back path routing from digital input (PDMIN) directly
   back to digital output (PDMOUT)
*/
#define AUD_TEST_DIG_IN_DIG_OUT                  0x04

#if AUD_ISI_MIN_VERSION(6,1) && !AUD_ISI_MIN_VERSION(9,0)
/* Audio codec loop back path routing from AIC33 line in left to HP speaker
*/
#define AUD_TEST_AIC33_LINEIN_LEFT_HP_OUT        0x05
#endif /* AUD_ISI_MIN_VERSION(6,1) && !AUD_ISI_MIN_VERSION(9,0) */

/* Audio codec loop back path routing from AIC33 line in right to HP speaker
*/
#define AUD_TEST_AIC33_LINEIN_RIGHT_HP_OUT       0x06
/* Audio codec loop back path routing from external microphone to HAC coil */
#define AUD_TEST_EXT_IN_HAC_OUT                  0x07
/* Audio codec loop back path routing from sigma-delta modulator output to
   DAC input
*/
#define AUD_TEST_ADC_OUT_DAC_IN                  0x08

#if AUD_ISI_MIN_VERSION(6,3) && !AUD_ISI_MIN_VERSION(9,0)
/* Audio codec loop back path routing from phone digital stereo mic to stereo
   ext ear out
*/
#define AUD_TEST_STEREO_DIG_IN_EXT_OUT           0x09
#endif /* AUD_ISI_MIN_VERSION(6,3) && !AUD_ISI_MIN_VERSION(9,0) */

/* Audio codec loopback from AV mic to IHF left */
#define AUD_TEST_AV_IN_IHF_LEFT_OUT              0x0A
/* Audio codec loopback from AV mic to IHF right */
#define AUD_TEST_AV_IN_IHF_RIGHT_OUT             0x0B

#if !AUD_ISI_MIN_VERSION(9,0)
#define AUD_TEST_BUZZER                          0x10  /* Buzzer test */
#endif /* !AUD_ISI_MIN_VERSION(9,0) */

/* Audio codec loopback path routing from HP mic to AV ear */
#define AUD_TEST_HP_IN_AV_OUT                    0x11
/* Audio codec loopback path routing from AV mic to AV ear */
#define AUD_TEST_AV_IN_AV_OUT                    0x12
/* Audio codec loopback path routing from FM mic to AV ear */
#define AUD_TEST_FM_IN_AV_OUT                    0x13
/* Audio codec loopback path routing from AV mic to IHF ear */
#define AUD_TEST_AV_IN_IHF_OUT                   0x14
/* Audio codec loopback path routing from AV mic to HP ear */
#define AUD_TEST_AV_IN_HP_OUT                    0x15
/* Audio codec loopback path routing from USB mic to USB ear */
#define AUD_TEST_USB_IN_USB_OUT                  0x16
/* Audio codec loopback path routing from HP mic to USB ear */
#define AUD_TEST_HP_IN_USB_OUT                   0x17
/* Audio codec loopback path routing from USB mic to IHF ear */
#define AUD_TEST_USB_IN_IHF_OUT                  0x18
/* Audio codec loopback path routing from USB mic to HP ear */
#define AUD_TEST_USB_IN_HP_OUT                   0x19
/* Audio codec loopback path routing from HP mic to active EANC ear */
#define AUD_TEST_MIC_IN_EANC_ON_OUT              0x1A
/* Audio codec loopback path routing from HP mic to bypass EANC ear */
#define AUD_TEST_MIC_IN_EANC_OFF_OUT             0x1B
/* Audio EANC production test */
#define AUD_TEST_EANC_PROD_MODE                  0x1C
/* Audio EANC service place test */
#define AUD_TEST_EANC_SP_MODE                    0x1D
/* FM TX test out selection */
#define AUD_TEST_FM_TX_OUT                       0x1E
/* Audio codec loopback path routing from HP mic1 to AV ear */
#define AUD_TEST_HP_MIC1_IN_AV_OUT               0x1F

#if !AUD_ISI_MIN_VERSION(9,0)
/* Audio-codec loopback path routing from external microphone line to used
   integrated handsfree line (not available for all products)
*/
#define AUD_TEST_EXT_IN_IHF_OUT                  0x20
#endif /* !AUD_ISI_MIN_VERSION(9,0) */

/* Audio codec loopback path routing from HP mic2 to AV ear */
#define AUD_TEST_HP_MIC2_IN_AV_OUT               0x21

#if AUD_ISI_MIN_VERSION(8,17) && !AUD_ISI_MIN_VERSION(9,0)
/* Audio codec loopback path routing from HP twin mics to AV ear */
#define AUD_TEST_HP_STEREO_IN_AV_OUT             0x22
#endif /* AUD_ISI_MIN_VERSION(8,17) && !AUD_ISI_MIN_VERSION(9,0) */

/* Audio codec loopback path routing from uUSB headset mic to uUSB headset
   ear left
*/
#define AUD_TEST_USB_IN_USB_OUT_EAR_L            0x23
/* Audio mic test: Route phone internal mic1 to uUSB headset ear left */
#define AUD_TEST_HP_MIC1_IN_USB_OUT_EAR_L        0x24
/* Audio mic2 test: Route phone internal mic2 to uUSB headset ear left */
#define AUD_TEST_HP_MIC2_IN_USB_OUT_EAR_L        0x25
/* IHF test: Route uUSB headset mic to phone IHF (left) */
#define AUD_TEST_USB_IN_IHF_OUT_LEFT             0x26
/* IHF test: Route uUSB headset mic to phone IHF (right) */
#define AUD_TEST_USB_IN_IHF_OUT_RIGHT            0x27
/* EANC mic1 test: Route EANC mic1 to uUSB headset ear left */
#define AUD_TEST_EANC_MIC1_IN_USB_OUT_EAR_L      0x28
/* EANC mic2 test: Route EANC mic2 to uUSB headset ear left */
#define AUD_TEST_EANC_MIC2_IN_USB_OUT_EAR_L      0x29

#if !AUD_ISI_MIN_VERSION(9,0)
/* Audio-codec loopback path routing from external microphone line to
   external speaker output (not available for all products)
*/
#define AUD_TEST_EXT_IN_EXT_OUT                  0x40
#endif /* !AUD_ISI_MIN_VERSION(9,0) */


#if !AUD_ISI_MIN_VERSION(9,0)
/* Audio-codec loopback path routing from fm radio microphone line to
   external speaker output (not available for all products)
*/
#define AUD_TEST_FM_IN_EXT_OUT                   0x80
#endif /* !AUD_ISI_MIN_VERSION(9,0) */


/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ERROR_CAUSES                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ERROR_CAUSES_CONST;

/* Unknown client type */
#define AUD_CLIENT_NOT_SUPPORTED                 0x00
/* The current status of server prevents operation with requested client type
*/
#define AUD_CLIENT_NOT_ALLOWED                   0x01
/* The client isn't registered in server */
#define AUD_CLIENT_NOT_REGISTERED                0x02
/* Unknown service */
#define AUD_SERVICE_NOT_AVAILABLE                0x03
/* Unknown attribute */
#define AUD_ATTRIBUTE_NOT_AVAILABLE              0x04
/* All requested attribute update settings are invalid */
#define AUD_ALL_SETTINGS_INVALID                 0x05
/* Unsuccessful setting operation */
#define AUD_SETTING_NOT_POSSIBLE                 0x06
/* Unknown test type */
#define AUD_TEST_TYPE_NOT_AVAILABLE              0x07

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_ATTRIBUTE_SETTING_OPERATIONS                        */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_ATTRIBUTE_SETTING_OPERATIONS_CONST;

/* Current attribute value is substituted with the new value in request  */
#define AUD_VALUE_SUBSTITUTE                     0x00
/* Value in request is added the current value of attribute */
#define AUD_VALUE_INCREASE                       0x01
/* Value in request is subtracted from the current value of attribute */
#define AUD_VALUE_DECREASE                       0x02
/* Value in request is bitwise ORed to the current value of attribute */
#define AUD_VALUE_BITWISE_OR                     0x03
/* Value in request is bitwise ANDed to the current value of attribute */
#define AUD_VALUE_BITWISE_AND                    0x04

/* ----------------------------------------------------------------------- */
/* Constant Table: AUDIO_SERVICE_CONFIGURATIONS                            */
/* ----------------------------------------------------------------------- */
typedef uint8 AUDIO_SERVICE_CONFIGURATIONS_CONST;

/* Server service configuration isn't the default one */
#define AUD_CONFIG_NON_DEFAULT                   0x00
/* Server service configuration is the default one */
#define AUD_CONFIG_DEFAULT                       0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_LAYER_UPDATE_GENERAL_STATUS                         */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_LAYER_UPDATE_GENERAL_STATUS_CONST;

/* All settings in update request were valid */
#define AUD_ALL_SETTINGS_OK                      0x00
/* Some settings in update request had to be limited, no setting was
   erroneous
*/
#define AUD_SOME_SETTINGS_LIMITED                0x01
/* Some settings in update request were erroneous. It's also possible that
   some other settings were limited
*/
#define AUD_SOME_SETTINGS_INVALID                0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_LAYER_UPDATE_ATTR_SPEC_STATUS                       */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_LAYER_UPDATE_ATTR_SPEC_STATUS_CONST;

/* Client is not allowed to update requested attribute */
#define AUD_SETTING_NOT_ALLOWED                  0x00
/* Requested setting value is invalid */
#define AUD_SETTING_VALUE_NOT_OK                 0x01
/* Requested setting value is valid */
#define AUD_SETTING_OK                           0x02
/* Requested setting value was truncated to upper limit value */
#define AUD_SETTING_CUT_TO_UPPER_LIMIT           0x03
/* Requested setting value was truncated to lower limit value */
#define AUD_SETTING_CUT_TO_LOWER_LIMIT           0x04

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_LAYER_UPDATE_GENERAL_EFFICIENCY                     */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_LAYER_UPDATE_GENERAL_EFFICIENCY_CONST;

/* All settings in update request are valid */
#define AUD_ALL_SETTINGS_EFFECTIVE               0x00
/* Some settings in update request had to be limited */
#define AUD_SOME_SETTINGS_INEFFECTIVE            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_LAYER_UPDATE_ATTR_EFFICIENCY                        */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_LAYER_UPDATE_ATTR_EFFICIENCY_CONST;

/* Updated layer is not effective */
#define AUD_LAYER_INEFFECTIVE                    0x00
/* Updated layer is effective */
#define AUD_LAYER_EFFECTIVE                      0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_LAYER_UPDATE_ATTR_EVENTS                            */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_LAYER_UPDATE_ATTR_EVENTS_CONST;

/* The client controlling the effective layer has changed, thus causing the
   change of attribute setting
*/
#define AUD_LAYER_ON_TOP                         0x00
/* The client controlling the effective layer remains the same, it has only
   changed its previous setting
*/
#define AUD_LAYER_SETTING_CHANGE                 0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_SELFTEST_TYPES - Valid from version 009.006         */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_SELFTEST_TYPES_CONST;

#define AUD_SELFTEST_AMPLIFIER_TEST              0x01  /* Amplifier test */
/* Kelvin ihf test */
#define AUD_SELFTEST_KELVIN_XEAR_TEST            0x02
#define AUD_SELFTEST_AUDIO_PLL_TEST              0x03  /* Audio PLL test */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_FEATURE_ID - Valid from version 009.004             */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_FEATURE_ID_CONST;

/* Audio Voice UI  */
#define AUD_VOICE_UI                             0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_SWITCH_VALUES                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_SWITCH_VALUES_CONST;

#define AUD_SWITCH_OFF                           0x00
#define AUD_SWITCH_ON                            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_CLIENT_TYPES                                        */
/* ----------------------------------------------------------------------- */
/* NOTE: UI, CS and DSP clients are considered 'basic' ie. they are supposed
   to always exist in the MCU SW
*/
typedef uint8 AUD_CLIENT_TYPES_CONST;

/* This is used only in layer update indications to tell that no client's
   layer affects the attribute, i.e. attribute has the default setting
*/
#define AUD_NO_CLIENT_TYPE                       0x00
/* UI client, primary handler of AUD_MIXER attributes */
#define AUD_UI_CLIENT_TYPE                       0x01
/* CS client, primary handler of AUD_MIXER attributes */
#define AUD_CS_CLIENT_TYPE                       0x02
/* Smart accessory client */
#define AUD_ACC_CLIENT_TYPE                      0x03
/* External client, not necessarily an accessory */
#define AUD_EXT_CLIENT_TYPE                      0x04
/* Battery accessory client */
#define AUD_BATT_CLIENT_TYPE                     0x05
#define AUD_DSP_CLIENT_TYPE                      0x06  /* DSP client */
#define AUD_TEST_CLIENT_TYPE                     0x07  /* Test client */
/* High quality sound player ( MIDI, MP3, etc.) */
#define AUD_SOUND_CLIENT_TYPE                    0x08
/* CS client with higher priority than AUD_CS_CLIENT_TYPE */
#define AUD_CS_HIGH_CLIENT_TYPE                  0x09
/* Volume Control client type. All clients of this typeare using same layer
   when accessing AUD_ANALOG_OUT:AUD_ANALOG_OUT_VOL_LEVEL attribute
*/
#define AUD_VOL_CTRL_CLIENT_TYPE                 0x0A
/* UI_2 client, higher priority than AUD_UI_CLIENT_TYPE */
#define AUD_UI_2_CLIENT_TYPE                     0x0B
/* Client type for Kodiak POC routing */
#define AUD_KODIAK_CLIENT_TYPE                   0x0C

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_DSP_PHAP_VALUES                                     */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_DSP_PHAP_VALUES_CONST;

#define AUD_DSP_PHAP_OFF                         0x00  /* PHAP OFF */
#define AUD_DSP_PHAP_NORMAL                      0x01  /* PHAP NORMAL */
#define AUD_DSP_PHAP_SLIGHT                      0x02  /* PHAP SLIGHT */
#define AUD_DSP_PHAP_MILD                        0x03  /* PHAP MILD */
#define AUD_DSP_PHAP_MODERATE                    0x04  /* PHAP MODERATE */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_INPUT_OUTPUT_MODE - Valid from version 009.006      */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_INPUT_OUTPUT_MODE_CONST;

#define AUD_MODE_MONO                            0x00
#define AUD_MODE_STEREO                          0x01
#define AUD_MODE_LEFT                            0x02
#define AUD_MODE_RIGHT                           0x03

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_DSP_ALGORITHMS_1                                     */
/* ----------------------------------------------------------------------- */
/* Note: Setting some of the bit fields means that appropriate algorithmin
   DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP
   willuse default set of enhancement algorithms for current accessory mode.
*/
typedef uint16 AUD_DSP_ALGORITHMS_1_CONST;

/* Default set of enhancement algorithms in use */
#define AUD_DSP_ALGORITHM_OFF                    0x0000  /* ---------------- */
/* Acoustic Echo Canceller */
#define AUD_DSP_ALGORITHM_AEC                    0x0001  /* ---------------1 */
/* AEC suppressor */
#define AUD_DSP_ALGORITHM_AEC_SUPP               0x0002  /* --------------1- */
/* Uplink ALWE */
#define AUD_DSP_ALGORITHM_UALWE                  0x0004  /* -------------1-- */
/* Pause attenuation for UALWE */
#define AUD_DSP_ALGORITHM_UALWE_PAUSE_ATT        0x0008  /* ------------1--- */
/* Downlink ALWE */
#define AUD_DSP_ALGORITHM_DALWE                  0x0010  /* -----------1---- */
/* Pause attenuation for DALWE */
#define AUD_DSP_ALGORITHM_DALWE_PAUSE_ATT        0x0020  /* ----------1----- */
/* Time domain DDRC (AEP 3) or Multiband DRC (AEP 4) */
#define AUD_DSP_ALGORITHM_DDRC                   0x0040  /* ---------1------ */
/* Uplink Dynamic Range Control */
#define AUD_DSP_ALGORITHM_UDRC                   0x0080  /* --------1------- */
/* Fast DRC addition to DRC */
#define AUD_DSP_ALGORITHM_FDRC                   0x0100  /* -------1-------- */
/* Microphone Adaptive Gain Control */
#define AUD_DSP_ALGORITHM_AGC                    0x0200  /* ------1--------- */
/* Automatic Volume Control */
#define AUD_DSP_ALGORITHM_AVC                    0x0400  /* -----1---------- */
/* Graphic Equalizer */
#define AUD_DSP_ALGORITHM_GEQ                    0x0800  /* ----1----------- */
/* Preset Equalizer */
#define AUD_DSP_ALGORITHM_PEQ                    0x1000  /* ---1------------ */

#if !AUD_ISI_MIN_VERSION(7,0)
/* Basic Equalizer */
#define AUD_DSP_ALGORITHM_BEQ                    0x2000  /* --1------------- */
#endif /* !AUD_ISI_MIN_VERSION(7,0) */

/* AEC Comfort Noise */
#define AUD_DSP_ALGORITHM_AEC_CN                 0x2000  /* --1------------- */
/* Integrated Hands Free algorithm */
#define AUD_DSP_ALGORITHM_IHF                    0x4000  /* -1-------------- */
/* MIDI Multiband DRC */
#define AUD_DSP_ALGORITHM_MIMDRC                 0x8000  /* 1--------------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_DSP_ALGORITHMS_2                                     */
/* ----------------------------------------------------------------------- */
/* Note: Setting some of the bit fields means that appropriate algorithmin
   DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP
   willuse default set of enhancement algorithms for current accessory mode.
*/
typedef uint16 AUD_DSP_ALGORITHMS_2_CONST;

/* #define AUD_DSP_ALGORITHM_OFF                 0x0000 (already defined) */
/* Earpiece Equalizer */
#define AUD_DSP_ALGORITHM_EEQ                    0x0001  /* ---------------1 */
/* Microphone Equalizer */
#define AUD_DSP_ALGORITHM_MEQ                    0x0002  /* --------------1- */
/* Active Noise Control */
#define AUD_DSP_ALGORITHM_ANC                    0x0004  /* -------------1-- */
/* Microphone High Pass filter in DSP */
#define AUD_DSP_ALGORITHM_MICHP                  0x0008  /* ------------1--- */
/* Decimation in UEM interrupt server */
#define AUD_DSP_ALGORITHM_UEM_DECIM              0x0010  /* -----------1---- */
/* Interpolation in UEM interrupt server */
#define AUD_DSP_ALGORITHM_UEM_INTERP             0x0020  /* ----------1----- */
/* Sidetone Equalizer */
#define AUD_DSP_ALGORITHM_SIDETONE_EQU           0x0040  /* ---------1------ */
/* MIDI High-Pass Filter used also for MuMDRC HP filter */
#define AUD_DSP_ALGORITHM_MIDI_HP                0x0080  /* --------1------- */
/* MIDI Equalizer */
#define AUD_DSP_ALGORITHM_MIDI_EQU               0x0100  /* -------1-------- */
/* MIDI Limiter */
#define AUD_DSP_ALGORITHM_MIDI_LIM               0x0200  /* ------1--------- */
/* DDRC volume dependency */
#define AUD_DSP_ALGORITHM_DDRC_VOL_DEP           0x0400  /* -----1---------- */
/* DDRC noise dependency */
#define AUD_DSP_ALGORITHM_DDRC_NOISE_DEP         0x0800  /* ----1----------- */
/* MIDI reverberation */
#define AUD_DSP_ALGORITHM_MIDI_REVERB            0x1000  /* ---1------------ */
/* 48kHz earpiece equalizer */
#define AUD_DSP_ALGORITHM_HQ_EEQ                 0x2000  /* --1------------- */
/* 48kHz microphone equalizer */
#define AUD_DSP_ALGORITHM_HQ_MEQ                 0x4000  /* -1-------------- */
/* Artificial Bandwidth Expansion (ABE) */
#define AUD_DSP_ALGORITHM_ABE                    0x8000  /* 1--------------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_DSP_ALGORITHMS_3 - Valid from version 007.000        */
/* ----------------------------------------------------------------------- */
/* Note: Setting some of the bit fields means that appropriate algorithmin
   DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP
   willuse default set of enhancement algorithms for current accessory mode.
*/
typedef uint16 AUD_DSP_ALGORITHMS_3_CONST;

/* #define AUD_DSP_ALGORITHM_OFF                 0x0000 (already defined) */
/* Network Echo Suppressor (Amadeus) */
#define AUD_DSP_ALGORITHM_NES                    0x0001  /* ---------------1 */
/* Analog mode Acoustic Echo Suppressor (Amadeus) */
#define AUD_DSP_ALGORITHM_AMODE_AEC              0x0002  /* --------------1- */
/* Ear Protection Limiter (Amadeus) */
#define AUD_DSP_ALGORITHM_EAR_PROT_LIM           0x0004  /* -------------1-- */
/* Fast DRC (different from FDRC in switch 1) (Amadeus) */
#define AUD_DSP_ALGORITHM_FAST_DRC               0x0008  /* ------------1--- */
/* Speech Codec Teletype (Amadeus, Gemini) */
#define AUD_DSP_ALGORITHM_SPC_TTY                0x0010  /* -----------1---- */
/* Sizzling Suppressor (Amadeus) */
#define AUD_DSP_ALGORITHM_SIZZ_SUPP              0x0020  /* ----------1----- */
/* Automatic Volume Control for Loopset (Amadeus) */
#define AUD_DSP_ALGORITHM_AVC_LOOPSET            0x0040  /* ---------1------ */
/* Analog mode LIMA filter (Amadeus) */
#define AUD_DSP_ALGORITHM_AMODE_LIMA             0x0080  /* --------1------- */
/* Earpiece High-Pass filter (Amadeus, Gemini) */
#define AUD_DSP_ALGORITHM_EARHP                  0x0100  /* -------1-------- */
/* Fast DRC for TX (Amadeus) */
#define AUD_DSP_ALGORITHM_FAST_DRC_TX            0x0200  /* ------1--------- */
/* Wind Noise Reduction - WNR */
#define AUD_DSP_ALGORITHM_WNR                    0x0400  /* -----1---------- */
/* Sidetone Howling control - SHC */
#define AUD_DSP_ALGORITHM_SHC                    0x0800  /* ----1----------- */
/* Voice Activity Detection - VAD */
#define AUD_DSP_ALGORITHM_VAD                    0x1000  /* ---1------------ */
/* Sound level meter */
#define AUD_DSP_ALGORITHM_SLM                    0x2000  /* --1------------- */
/* When set, prevents accessory dependent algorithm switch updating in DSP */
#define AUD_DSP_ALGORITHM_MANUAL_CONTROL         0x4000  /* -1-------------- */
/* Transducer DRC (XDRC) */
#define AUD_DSP_ALGORITHM_XDRC                   0x8000  /* 1--------------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_DSP_ALGORITHMS_4 - Valid from version 007.000        */
/* ----------------------------------------------------------------------- */
/* Note: Setting some of the bit fields means that appropriate algorithmin
   DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP
   willuse default set of enhancement algorithms for current accessory mode.
*/
typedef uint16 AUD_DSP_ALGORITHMS_4_CONST;

/* #define AUD_DSP_ALGORITHM_OFF                 0x0000 (already defined) */
/* X-Prot IHF thermal protection, temperature limiting */
#define AUD_DSP_ALGORITHM_XPROT_TEMP             0x0001  /* ---------------1 */
/* X-Prot IHF protection against excess displacement, displacement limiting
*/
#define AUD_DSP_ALGORITHM_XPROT_DISP             0x0002  /* --------------1- */
/* Music MDRC */
#define AUD_DSP_ALGORITHM_MUMDRC                 0x0004  /* -------------1-- */
/* Stereo widening for headset */
#define AUD_DSP_ALGORITHM_STW_HD                 0x0008  /* ------------1--- */
/* Stereo widening for loudspeakers */
#define AUD_DSP_ALGORITHM_STW_LS                 0x0010  /* -----------1---- */
/* Doppler effect */
#define AUD_DSP_ALGORITHM_DOPPLER                0x0020  /* ----------1----- */
/* Positional 3D audio for headset */
#define AUD_DSP_ALGORITHM_POS3D_HD               0x0040  /* ---------1------ */
/* Positional 3D audio for loudspeakers */
#define AUD_DSP_ALGORITHM_POS3D_LS               0x0080  /* --------1------- */
/* Environmental reverberation */
#define AUD_DSP_ALGORITHM_REVERB                 0x0100  /* -------1-------- */
/* Audio visualisation */
#define AUD_DSP_ALGORITHM_AUDIO_VIS              0x0200  /* ------1--------- */
/* Stereo Processing for Audio Capture */
#define AUD_DSP_ALGORITHM_SPAC                   0x0400  /* -----1---------- */
/* MuMDRC in recording path */
#define AUD_DSP_ALGORITHM_REC_MUMDRC             0x0800  /* ----1----------- */
/* Limiter in recording path */
#define AUD_DSP_ALGORITHM_REC_LIMITER            0x1000  /* ---1------------ */
/* Fullband AGC in recording path */
#define AUD_DSP_ALGORITHM_FULLBAND_AGC           0x2000  /* --1------------- */
/* APSSAS */
#define AUD_DSP_ALGORITHM_APSSAS                 0x4000  /* -1-------------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_DSP_ALGORITHMS_5 - Valid from version 007.000        */
/* ----------------------------------------------------------------------- */
/* Note: Setting some of the bit fields means that appropriate algorithmin
   DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP
   willuse default set of enhancement algorithms for current accessory mode.
*/
typedef uint16 AUD_DSP_ALGORITHMS_5_CONST;

/* #define AUD_DSP_ALGORITHM_OFF                 0x0000 (already defined) */

#if AUD_ISI_MIN_VERSION(7,0) && !AUD_ISI_MIN_VERSION(9,12)
/* UDRC whisper mode */
#define AUD_DSP_ALGORITHM_UDRC_WHISPER_MODE      0x0001  /* ---------------1 */
#endif /* AUD_ISI_MIN_VERSION(7,0) && !AUD_ISI_MIN_VERSION(9,12) */

/* Rx IAVC */
#define AUD_DSP_ALGORITHM_RX_IAVC                0x0002  /* --------------1- */
/* Tx IAVC, needs MB UL DRC */
#define AUD_DSP_ALGORITHM_TX_IAVC                0x0004  /* -------------1-- */

#if AUD_ISI_MIN_VERSION(7,0) && !AUD_ISI_MIN_VERSION(9,12)
/* Multiband UL DRC - in future */
#define AUD_DSP_ALGORITHM_MB_UDRC                0x0008  /* ------------1--- */
#endif /* AUD_ISI_MIN_VERSION(7,0) && !AUD_ISI_MIN_VERSION(9,12) */

/* Separate limiter algorithm switch - unconditional */
#define AUD_DSP_ALGORITHM_LIMITER                0x0010  /* -----------1---- */
/* Separate limiter algorithm switch - conditional */
#define AUD_DSP_ALGORITHM_LIMITER_CONDITIONAL    0x0020  /* ----------1----- */
/* Switch for speech emphasis EQU block. Note: despite its name, this switch
   can also be used in WB mode (but its frequency response is different).
*/
#define AUD_DSP_ALGORITHM_NB_SPC_EMPHASIS        0x0040  /* ---------1------ */
/* Switch for MMIC CAL gain estimation. */
#define AUD_DSP_ALGORITHM_MMIC_SELECT_CAL_GAIN_ESTIM 0x0080  /* --------1------- */
/* Switch for MMIC CAL gain apply. */
#define AUD_DSP_ALGORITHM_MMIC_SELECT_CAL_GAIN_APPLY 0x0100  /* -------1-------- */
/* Switch for MMIC STB. */
#define AUD_DSP_ALGORITHM_MMIC_SELECT_STB        0x0200  /* ------1--------- */
/* Switch for MMIC AIC. */
#define AUD_DSP_ALGORITHM_MMIC_SELECT_AIC        0x0400  /* -----1---------- */
/* Switch for MMIC POS. */
#define AUD_DSP_ALGORITHM_MMIC_SELECT_POS        0x0800  /* ----1----------- */
/* Switch for MMIC overall. */
#define AUD_DSP_ALGORITHM_MMIC                   0x1000  /* ---1------------ */

#if AUD_ISI_MIN_VERSION(8,9) && !AUD_ISI_MIN_VERSION(9,12)
/* Switch for True WB concept. */
#define AUD_DSP_ALGORITHM_TRUE_WB                0x2000  /* --1------------- */
#endif /* AUD_ISI_MIN_VERSION(8,9) && !AUD_ISI_MIN_VERSION(9,12) */

/* Switch for multi-mic WNR */
#define AUD_DSP_ALGORITHM_MWNR                   0x2000  /* --1------------- */
/* Switch for MMIC spatial VAD */
#define AUD_DSP_ALGORITHM_MMIC_VAD               0x4000  /* -1-------------- */
/* Switch for MMIC noise reference usage */
#define AUD_DSP_ALGORITHM_MMIC_NREF              0x8000  /* 1--------------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_DSP_ACA_ALGORITHMS - Valid from version 009.011      */
/* ----------------------------------------------------------------------- */
/* Note: For ACA algorithms 1=on and 0=off. The client must also specify
   a mask to tell the audio server which algorithms it wishes to explicitly
   control. If the mask bit is 1, the client controls the switch,
   otherwise the value will be taken from mode specific tunings.
*/
typedef uint16 AUD_DSP_ACA_ALGORITHMS_CONST;

/* ACA Optical Zoom Noise Control */
#define AUD_DSP_ACA_ALGORITHMS_OZN               0x0001  /* ---------------1 */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_CLIENT_TYPES_1                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_CLIENT_TYPES_1_CONST;

#define AUD_CLIENT_SOUND                         0x01  /* -------1 */
#define AUD_CLIENT_UI                            0x02  /* ------1- */
#define AUD_CLIENT_CS                            0x04  /* -----1-- */
#define AUD_CLIENT_ACC                           0x08  /* ----1--- */
#define AUD_CLIENT_EXT                           0x10  /* ---1---- */
#define AUD_CLIENT_BATT                          0x20  /* --1----- */
#define AUD_CLIENT_DSP                           0x40  /* -1------ */
#define AUD_CLIENT_TEST                          0x80  /* 1------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: AUD_CLIENT_TYPES_2                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_CLIENT_TYPES_2_CONST;

#define AUD_CLIENT_CS_HIGH                       0x02  /* ------1- */

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_HW_STATUSES                                         */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_HW_STATUSES_CONST;

#define AUD_HW_STATUS_READY                      0x00
#define AUD_HW_STATUS_BUSY                       0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_TEST_TX_OUT_ROUTE - Valid from version 008.016      */
/* ----------------------------------------------------------------------- */
typedef uint16 AUD_TEST_TX_OUT_ROUTE_CONST;

#define AUD_FM_TX_OUT_LEFT                       0x0001
#define AUD_FM_TX_OUT_RIGHT                      0x0002
#define AUD_FM_TX_OUT_STEREO                     0x0003

/* ----------------------------------------------------------------------- */
/* Constant Table: AUD_TEST_ERRORS                                         */
/* ----------------------------------------------------------------------- */
typedef uint8 AUD_TEST_ERRORS_CONST;

/* #define AUD_TEST_TYPE_NOT_AVAILABLE           0x07 (already defined) */
/* #define AUD_SETTING_NOT_ALLOWED               0x00 (already defined) */
/* #define AUD_SETTING_NOT_POSSIBLE              0x06 (already defined) */
/* Audio EANC test failed, left mic */
#define AUD_EANC_L_MIC_FAIL                      0x10
/* Audio EANC test failed, right mic */
#define AUD_EANC_R_MIC_FAIL                      0x11
/* Audio EANC test failed, both mics */
#define AUD_EANC_BOTH_MICS_FAIL                  0x12

/* ----------------------------------------------------------------------- */
/* FTD Data Table                                                          */
/* ----------------------------------------------------------------------- */
#define COMM_FTD_DATA_AUD_ACCESSORY_MODE         0x01A0  /* Byte */
#define COMM_FTD_DATA_AUD_ANADIGI_MODE           0x01A1  /* Byte */
#define COMM_FTD_DATA_AUD_MIXER_ULI              0x01A2  /* Byte */
#define COMM_FTD_DATA_AUD_MIXER_DLO              0x01A3  /* Byte */
#define COMM_FTD_DATA_AUD_AIN_GAIN               0x01A4  /* Byte */
#define COMM_FTD_DATA_AUD_AOU_VOL                0x01A5  /* Byte */
#define COMM_FTD_DATA_AUD_MIXER_DPW              0x01A6  /* Byte */
#define COMM_FTD_DATA_AUD_MIXER_UPW              0x01A7  /* Byte */

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define AUD_REGISTER_IN_REQ                      0x00
#define AUD_REGISTER_IN_OK_RESP                  0x01
#define AUD_REGISTER_IN_FAIL_RESP                0x02
#define AUD_REGISTER_IN_IND                      0x03
#define AUD_REGISTER_OUT_REQ                     0x04
#define AUD_REGISTER_OUT_OK_RESP                 0x05
#define AUD_REGISTER_OUT_FAIL_RESP               0x06
#define AUD_REGISTER_OUT_IND                     0x07
#define AUD_SERVICES_GET_REQ                     0x08
#define AUD_SERVICES_GET_DEFAULT_OK_RESP         0x09
#define AUD_SERVICES_GET_CUSTOM_OK_RESP          0x0A
#define AUD_ATTRIBUTES_GET_REQ                   0x0B
#define AUD_ATTRIBUTES_GET_DEFAULT_OK_RESP       0x0C
#define AUD_ATTRIBUTES_GET_CUSTOM_OK_RESP        0x0D
#define AUD_ATTRIBUTES_GET_FAIL_RESP             0x0E
#define AUD_REGISTERED_GET_REQ                   0x0F
#define AUD_REGISTERED_GET_OK_RESP               0x10
#define AUD_SETTING_GET_REQ                      0x11
#define AUD_SETTING_GET_OK_RESP                  0x12
#define AUD_SETTING_GET_FAIL_RESP                0x13
#define AUD_LAYER_UPDATE_REQ                     0x14
#define AUD_LAYER_UPDATE_OK_RESP                 0x15
#define AUD_LAYER_UPDATE_FAIL_RESP               0x16
#define AUD_LAYER_UPDATE_IND                     0x17
#define AUD_LAYER_UPDATE_NEEDED_IND              0x18
#define AUD_LAYER_DESTROY_REQ                    0x19
#define AUD_LAYER_DESTROY_OK_RESP                0x1A
#define AUD_LAYER_DESTROY_FAIL_RESP              0x1B
#define AUD_TEST_START_REQ                       0x1C
#define AUD_TEST_START_OK_RESP                   0x1D
#define AUD_TEST_START_FAIL_RESP                 0x1E
#define AUD_TEST_STOP_REQ                        0x1F
#define AUD_TEST_STOP_OK_RESP                    0x20
#define AUD_TEST_STOP_FAIL_RESP                  0x21
#define AUD_HW_STATUS_IND                        0x22
#define AUD_ATTACH_ACCESSORY_EVENT_REQ           0x23
#define AUD_ATTACH_ACCESSORY_EVENT_OK_RESP       0x24
#define AUD_S60_VOIP_EMERGENCY_CALL_NTF          0x27
#define AUD_FEATURE_SET_REQ                      0x28
#define AUD_FEATURE_SET_RESP                     0x29
#define AUD_SELFTEST_REQ                         0x2A
#define AUD_SELFTEST_RESP                        0x2B
#define AUD_LOOPBACK_REQ                         0x2C
#define AUD_LOOPBACK_RESP                        0x2D
#define AUD_LOOPBACK_GAIN_SET_REQ                0x2E
#define AUD_LOOPBACK_GAIN_SET_RESP               0x2F
#define AUD_EQU_CREATE_REQ                       0x40
#define AUD_EQU_CREATE_OK_RESP                   0x41
#define AUD_EQU_CREATE_FAIL_RESP                 0x42
#define AUD_EQU_INFO_REQ                         0x43
#define AUD_EQU_INFO_OK_RESP                     0x44
#define AUD_EQU_INFO_FAIL_RESP                   0x45
#define AUD_EQU_SWITCH_STATE_REQ                 0x46
#define AUD_EQU_SWITCH_STATE_OK_RESP             0x47
#define AUD_EQU_SWITCH_STATE_FAIL_RESP           0x48
#define AUD_EQU_SWITCH_STATE_IND                 0x49
#define AUD_EQU_ADJUST_REQ                       0x4A
#define AUD_EQU_ADJUST_OK_RESP                   0x4B
#define AUD_EQU_ADJUST_FAIL_RESP                 0x4C
#define AUD_EQU_DELETE_REQ                       0x4D
#define AUD_EQU_DELETE_OK_RESP                   0x4E
#define AUD_EQU_DELETE_FAIL_RESP                 0x4F
#define AUD_EQU_ACTIVE_ID_REQ                    0x50
#define AUD_EQU_ACTIVE_ID_OK_RESP                0x51
#define AUD_EQU_ACTIVE_ID_FAIL_RESP              0x52
#define AUD_SCO_CONTROL_REQ                      0x59
#define AUD_SCO_CONTROL_RESP                     0x5A
#define AUD_BTHSTREAM_STATUS_CHANGE_REQ          0x5B
#define AUD_BTHSTREAM_STATUS_CHANGE_RESP         0x5C
#define AUD_DEFATTR_CHANGE_REQ                   0x5D
#define AUD_DEFATTR_CHANGE_RESP                  0x5E
#define AUD_DEFATTR_VALUE_GET_REQ                0x5F
#define AUD_DEFATTR_VALUE_GET_RESP               0x60
#define AUD_EQU_GENERAL_INFO_REQ                 0x61
#define AUD_EQU_GENERAL_INFO_RESP                0x62
#define AUD_EQU_CREATED_IND                      0x63
#define AUD_EQU_DELETED_IND                      0x64
#define AUD_EQU_ADJUSTED_IND                     0x65
#define AUD_VOLUME_CONTROL_REQ                   0x66
#define AUD_VOLUME_CONTROL_RESP                  0x67
#define AUD_VOLUME_GET_REQ                       0x68
#define AUD_VOLUME_GET_RESP                      0x69
#define AUD_FIFO_INTERRUPT_IND                   0x6A
#define AUD_EANC_STATUS_CHANGE_REQ               0x6B
#define AUD_EANC_STATUS_CHANGE_RESP              0x6C
#define AUD_VOLUME_CONTROL_IND                   0x6D
#define AUD_EANC_STATUS_CHANGE_IND               0x6E
#define AUD_EANC_MIC_DATA_REQ                    0x6F
#define AUD_EANC_MIC_DATA_RESP                   0x70

/* ----------------------------------------------------------------------- */
/* Message ID's reserved for ECI audio Block                               */
/* ----------------------------------------------------------------------- */

/*
#define AUD_ECI_AUDIO_BLOCK_FAIL_RESP            0x72
#define AUD_ECI_AUDIO_BLOCK_NTF                  0x73
#define AUD_ECI_AUDIO_BLOCK_REQ                  0x70
#define AUD_ECI_AUDIO_BLOCK_RESP                 0x71
#define AUD_ECI_GAIN_COMPENSATION_FAIL_RESP      0x79
#define AUD_ECI_GAIN_COMPENSATION_OK_RESP        0x78
#define AUD_ECI_GAIN_COMPENSATION_REQ            0x77
#define AUD_ECI_PARAM_CONF_FAIL_RESP             0x76
#define AUD_ECI_PARAM_CONF_REQ                   0x74
#define AUD_ECI_PARAM_CONF_RESP                  0x75
*/

/* ----------------------------------------------------------------------- */
/* Message ID's reserved for Audio Policy                                  */
/* ----------------------------------------------------------------------- */

/*
#define AUD_POL_APPL_NTF                         0xA5
#define AUD_POL_APPL_REQ                         0xA0
#define AUD_POL_APPL_RESP                        0xA1
#define AUD_POL_AUDIO_EFFECT_IND                 0xB1
#define AUD_POL_AUDIO_EFFECT_REQ                 0xAF
#define AUD_POL_AUDIO_EFFECT_RESP                0xB0
#define AUD_POL_CONTROL_NTF                      0xA4
#define AUD_POL_PRIVOL_NTF                       0xAC
#define AUD_POL_PRIVOL_REQ                       0xAA
#define AUD_POL_PRIVOL_RESP                      0xAB
#define AUD_POL_RESOURCE_REQ                     0xA6
#define AUD_POL_RESOURCE_RESP                    0xA7
#define AUD_POL_STATUS_IND                       0xA8
#define AUD_POL_STATUS_REQ                       0xAD
#define AUD_POL_STATUS_RESP                      0xAE
#define AUD_POL_VOLUME_IND                       0xA9
#define AUD_POL_VOLUME_REQ                       0xA2
#define AUD_POL_VOLUME_RESP                      0xA3
*/

/* ----------------------------------------------------------------------- */
/* Message ID's reserved for EAP Module                                    */
/* ----------------------------------------------------------------------- */

/*
#define AUD_EAP_BUFFER_CLIENT_NTF                0x82
#define AUD_EAP_BUFFER_EMPTY_NTF                 0x89
#define AUD_EAP_BUFFER_OVERFLOW_NTF              0x84
#define AUD_EAP_BUFFER_SERVER_NTF                0x83
#define AUD_EAP_DATA_TRACING_REQ                 0x8F
#define AUD_EAP_DATA_TRACING_RESP                0x90
#define AUD_EAP_EFFECT_ADJUST_REQ                0x8C
#define AUD_EAP_EFFECT_ADJUST_RESP               0x8D
#define AUD_EAP_EFFECT_CREATE_REQ                0x85
#define AUD_EAP_EFFECT_CREATE_RESP               0x86
#define AUD_EAP_EFFECT_DESTROY_REQ               0x87
#define AUD_EAP_EFFECT_DESTROY_RESP              0x88
#define AUD_EAP_EFFECT_INFO_REQ                  0x8A
#define AUD_EAP_EFFECT_INFO_RESP                 0x8B
#define AUD_EAP_STREAM_REQ                       0x80
#define AUD_EAP_STREAM_RESP                      0x81
#define AUD_EAP_TEST_EFFECT_SWITCH_READ_REQ      0x97
#define AUD_EAP_TEST_EFFECT_SWITCH_READ_RESP     0x98
#define AUD_EAP_TEST_EFFECT_SWITCH_WRITE_REQ     0x99
#define AUD_EAP_TEST_EFFECT_SWITCH_WRITE_RESP    0x9A
#define AUD_EAP_TUNING_PARAM_LOCK_REQ            0x95
#define AUD_EAP_TUNING_PARAM_LOCK_RESP           0x96
#define AUD_EAP_TUNING_PARAM_READ_REQ            0x91
#define AUD_EAP_TUNING_PARAM_READ_RESP           0x92
#define AUD_EAP_TUNING_PARAM_WRITE_REQ           0x93
#define AUD_EAP_TUNING_PARAM_WRITE_RESP          0x94
#define AUD_EAP_VISUALIZATION_DATA_NTF           0x8E
*/

/* ----------------------------------------------------------------------- */
/* Message ID's reserved for GPA Module                                    */
/* ----------------------------------------------------------------------- */

/*
#define AUD_GPA_AB_AV_LOCK_REQ                   0xD9
#define AUD_GPA_AB_AV_LOCK_RESP                  0xDA
#define AUD_GPA_AB_AV_UNLOCK_REQ                 0xDB
#define AUD_GPA_AB_AV_UNLOCK_RESP                0xDC
#define AUD_GPA_AB_CORRECTION_READ_REQ           0xD7
#define AUD_GPA_AB_CORRECTION_READ_RESP          0xD8
#define AUD_GPA_AB_CORRECTION_WRITE_REQ          0xD5
#define AUD_GPA_AB_CORRECTION_WRITE_RESP         0xD6
#define AUD_GPA_AB_READ_REQ                      0xD2
#define AUD_GPA_AB_READ_RESP                     0xD3
#define AUD_GPA_AB_WRITE_REQ                     0xD0
#define AUD_GPA_AB_WRITE_RESP                    0xD1
#define AUD_GPA_CURRENT_HW_PATH_IND              0xD4
*/

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define AUD_SERVICE_REPORT                       0x00
#define AUD_ATTRIBUTE_SETUP_REPORT               0x01
#define AUD_DSP_PARBLOCK                         0x04
#define AUD_SETTING_REPORT                       0x02
#define AUD_LAYER_SETTING                        0x03
#define AUD_ATTRIBUTE_LAYER_REPORT               0x05
#define AUD_ATTRIBUTE_UPDATE_REPORT              0x06
#define AUD_VOLUME_CONTROL_SB                    0x09
#define AUD_VOLUME_CONTROL_RESPONSE_SB           0x0A
#define AUD_EQU_DEFINITION                       0x07
#define AUD_COMM_FTD_DATA_BYTE                   0x0001
#define AUD_EQU_GENERAL_INFO                     0x08
#define AUD_LOOPBACK_INPUT_GAIN_SB               0x0B
#define AUD_LOOPBACK_OUTPUT_GAIN_SB              0x0C
#define AUD_LOOPBACK_IN_PARAMS_SB                0x0D
#define AUD_LOOPBACK_OUT_PARAMS_SB               0x0E
#define AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB      0x0F

/* ----------------------------------------------------------------------- */
/* Shared file inclusion                                                   */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(5,27)
#include "acc_shared_isi.h"
#endif /* AUD_ISI_MIN_VERSION(5,27) */


/* ----------------------------------------------------------------------- */
/* Sequence: AUD_LOOPBACK_INPUT_DATA - Valid from version 009.009          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    /* Values from the constant table AUD_LOOPBACK_IN_SELECT */
    uint8   Input;
    /* Values from the constant table AUD_INPUT_OUTPUT_MODE */
    uint8   InputMode;
    uint8   fill1[2];
    } AUD_LOOPBACK_INPUT_DATA_STR;

#define SIZE_AUD_LOOPBACK_INPUT_DATA_STR   \
        sizeof(AUD_LOOPBACK_INPUT_DATA_STR)


/* ----------------------------------------------------------------------- */
/* Sequence: AUD_LOOPBACK_OUTPUT_DATA - Valid from version 009.009         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    /* Values from the constant table AUD_LOOPBACK_OUT_SELECT */
    uint8   Output;
    /* Values from the constant table AUD_INPUT_OUTPUT_MODE */
    uint8   OutputMode;
    uint8   fill1[2];
    } AUD_LOOPBACK_OUTPUT_DATA_STR;

#define SIZE_AUD_LOOPBACK_OUTPUT_DATA_STR   \
        sizeof(AUD_LOOPBACK_OUTPUT_DATA_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SERVICE_REPORT                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    /* Values from the constant table AUDIO_SERVICE_CONFIGURATIONS */
    uint8   AttributeSetup;
    } tISI_AudServiceReport;

#define AUD_SERVICE_REPORT_LEN   sizeof(tISI_AudServiceReport)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_ATTRIBUTE_SETUP_REPORT                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   AttributeId;
    uint8   Spare1;
    uint16  DefaultValue; /* Value in the default service layer */
    /* The smallest available value for the attribute */
    uint16  MinimumValue;
    uint16  MaximumValue; /* The largest available value for the attribute */
    uint16  Spare2;
    } tISI_AudAttributeSetupReport;

#define AUD_ATTRIBUTE_SETUP_REPORT_LEN   sizeof(tISI_AudAttributeSetupReport)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_DSP_PARBLOCK                                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* The number of actual parameter data bytes in the data block */
    uint8   DataBlockLength;
    uint8   Spare;
    uint8   DataBlockFrame[AUD_DSP_MAX_PARDATA_LEN];
    } tISI_AudDSPParblock;

#define AUD_DSP_PARBLOCK_LEN   sizeof(tISI_AudDSPParblock)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_SETTING_REPORT                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   AttributeId;
    uint8   Spare1;
    uint16  AttributeValue;
    uint16  Spare2;
    } tISI_AudSettingReport;

#define AUD_SETTING_REPORT_LEN   sizeof(tISI_AudSettingReport)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_LAYER_SETTING                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   AttributeId;
    /* Values from the constant table AUD_ATTRIBUTE_SETTING_OPERATIONS */
    uint8   Operation;
    uint16  AttributeValue;
    uint16  Spare;
    } tISI_AudLayerSetting;

#define AUD_LAYER_SETTING_LEN   sizeof(tISI_AudLayerSetting)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_ATTRIBUTE_LAYER_REPORT                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   AttributeId;
    /* Values from the constant table AUD_LAYER_UPDATE_ATTR_EVENTS */
    uint8   Event;
    /* Type of the client that owns the effective layer for the service
       attribute from now on
       NOTE: AUD_NO_CLIENT_TYPE means that no client's layer affects this
       attribute, the default value is in effect
       Values from the constant table AUD_CLIENT_TYPES
    */
    uint8   ClientType;
    uint8   Spare1;
    uint16  AttributeValue;
    } tISI_AudAttributeLayerReport;

#define AUD_ATTRIBUTE_LAYER_REPORT_LEN   sizeof(tISI_AudAttributeLayerReport)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_ATTRIBUTE_UPDATE_REPORT                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   AttributeId;
    /* NOTE: NOT_ALLOWED and VALUE_NOT_OK statuses are error indications. For
       them, 'Efficiency' must always be regarded as INEFFECTIVE
       Values from the constant table AUD_LAYER_UPDATE_ATTR_SPEC_STATUS
    */
    uint8   Status;
    /* Values from the constant table AUD_LAYER_UPDATE_ATTR_EFFICIENCY */
    uint8   Efficiency;
    uint8   Spare1;
    uint16  Spare2;
    } tISI_AudAttributeUpdateReport;

#define AUD_ATTRIBUTE_UPDATE_REPORT_LEN   \
        sizeof(tISI_AudAttributeUpdateReport)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_VOLUME_CONTROL_SB - Valid from version 006.013            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Informs which media type volume is controlled (only one value can be
       selected in this message)
       Values from the bitmask table AUD_VOLUME_MEDIA_TYPE
    */
    uint16  media_type;
    /* Informs is control in %-format or in Q8.7 format
       Values from the constant table AUD_VOLUME_CONTROL_TYPE
    */
    uint8   control_format;
    uint8   fill1;
    uint8   fill2[2];
    /* Primary mode volume in % format (range 0 - 1000, meaning 45.5% is 455)
    */
    uint16  pri_volume_in_percetance;
    int16   pri_volume_in_q87; /* Primary mode volume in Q8.7 format */
    /* Secondary mode volume in % format (range 0 - 1000, meaning 45.5% is
       455)
    */
    uint16  sec_volume_in_percetance;
    int16   sec_volume_in_q87; /* Secondary mode volume in Q8.7 format */
    } AUD_VOLUME_CONTROL_SB_STR;

#define SIZE_AUD_VOLUME_CONTROL_SB_STR   sizeof(AUD_VOLUME_CONTROL_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_VOLUME_CONTROL_RESPONSE_SB - Versions 006.013 - 008.012   */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(6,13) && !AUD_ISI_MIN_VERSION(8,12)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Informs which media type volume was controlled (only one type per
       subblock)
       Values from the bitmask table AUD_VOLUME_MEDIA_TYPE
    */
    uint16  media_type;
    /* Informs was control in %-format or in Q8.7 format
       Values from the constant table AUD_VOLUME_CONTROL_TYPE
    */
    uint8   control_format;
    uint8   fill1;
    uint8   fill2[2];
    /* Requested primary mode volume in % format (range 0 - 1000, meaning
       45.5% is 455)
    */
    uint16  requested_pri_volume_in_percetance;
    /* requested primary mode volume in Q8.7 format */
    int16   requested_pri_volume_in_q87;
    /* Primary actual gain which is achieved by Audio system (Q8.7 format) */
    int16   pri_actual_gain;
    /* Primary missing gain which could not be achieved by Audio syste (Q8.7
       format)
    */
    int16   pri_missing_gain;
    /* Primary target gain, compensated gain (Q8.7 format) */
    int16   pri_target_gain;
    /* Primary analog gain which is written in hardware (Q8.7 format) */
    int16   pri_analog_gain;
    /* Primary digital gain which is used to as compensation to target gain
       (Q8.7 format)
    */
    int16   pri_digital_gain;
    /* Secondary mode volume in % format (range 0 - 1000, meaning 45.5% is
       455)
    */
    uint16  requested_sec_volume_in_percetance;
    /* Secondary mode volume in Q8.7 format */
    int16   requested_sec_volume_in_q87;
    /* Secondary actual gain which is achieved by Audio system (Q8.7 format)
    */
    int16   sec_actual_gain;
    /* Secondary missing gain which could not be achieved by Audio syste
       (Q8.7 format)
    */
    int16   sec_missing_gain;
    /* Secondary target gain, compensated gain (Q8.7 format) */
    int16   sec_target_gain;
    /* Secondary analog gain which is written in hardware (Q8.7 format) */
    int16   sec_analog_gain;
    /* Secondary digital gain which is used to as compensation to target gain
       (Q8.7 format)
    */
    int16   sec_digital_gain;
    } AUD_VOLUME_CONTROL_RESPONSE_SB_STR;

#define SIZE_AUD_VOLUME_CONTROL_RESPONSE_SB_STR   \
        sizeof(AUD_VOLUME_CONTROL_RESPONSE_SB_STR)

#endif /* AUD_ISI_MIN_VERSION(6,13) && !AUD_ISI_MIN_VERSION(8,12) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_VOLUME_CONTROL_RESPONSE_SB - Valid from version 008.012   */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(8,12)

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    /* Informs which media type volume was controlled (only one type per
       subblock)
       Values from the bitmask table AUD_VOLUME_MEDIA_TYPE
    */
    uint16  media_type;
    /* Informs was control in %-format or in Q8.7 format
       Values from the constant table AUD_VOLUME_CONTROL_TYPE
    */
    uint8   control_format;
    uint8   fill1;
    uint8   fill2[2];
    /* Requested primary mode volume in % format (range 0 - 1000, meaning
       45.5% is 455)
    */
    uint16  requested_pri_volume_in_percetance;
    /* Requested primary mode volume in Q8.7 format */
    int16   requested_pri_volume_in_q87;
    /* Primary actual gain which is achieved by Audio system (Q8.7 format) */
    int16   pri_actual_gain;
    /* Primary missing gain which could not be achieved by Audio system (Q8.7
       format)
    */
    int16   pri_missing_gain;
    /* Primary target gain, compensated gain (Q8.7 format) */
    int16   pri_target_gain;
    /* Primary analog gain which is written in hardware (Q8.7 format) */
    int16   pri_analog_gain;
    /* Primary digital gain which is used to as compensation to target gain
       (Q8.7 format)
    */
    int16   pri_digital_gain;
    /* Primary minimum gain that can be achieved by Audio system (Q8.7
       format)
    */
    int16   pri_min_gain;
    /* Primary maximum gain that can be achieved by Audio system (Q8.7
       format)
    */
    int16   pri_max_gain;
    /* Requested secondary mode volume in % format (range 0 - 1000, meaning
       45.5% is 455)
    */
    uint16  requested_sec_volume_in_percetance;
    /* Requested secondary mode volume in Q8.7 format */
    int16   requested_sec_volume_in_q87;
    /* Secondary actual gain which is achieved by Audio system (Q8.7 format)
    */
    int16   sec_actual_gain;
    /* Secondary missing gain which could not be achieved by Audio system
       (Q8.7 format)
    */
    int16   sec_missing_gain;
    /* Secondary target gain, compensated gain (Q8.7 format) */
    int16   sec_target_gain;
    /* Secondary analog gain which is written in hardware (Q8.7 format) */
    int16   sec_analog_gain;
    /* Secondary digital gain which is used to as compensation to target gain
       (Q8.7 format)
    */
    int16   sec_digital_gain;
    /* Secondary minimum gain that can be achieved by Audio system (Q8.7
       format)
    */
    int16   sec_min_gain;
    /* Secondary maximum gain that can be achieved by Audio system (Q8.7
       format)
    */
    int16   sec_max_gain;
    } AUD_VOLUME_CONTROL_RESPONSE_SB_STR;

#define SIZE_AUD_VOLUME_CONTROL_RESPONSE_SB_STR   \
        sizeof(AUD_VOLUME_CONTROL_RESPONSE_SB_STR)

#endif /* AUD_ISI_MIN_VERSION(8,12) */


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EQU_DEFINITION                                            */
/* ----------------------------------------------------------------------- */
/* The upper limit frequencies for band 1 to 8 can vary between
   differentproducts and is depending on the implementation of the DSP SW. In
   somecases the DSP SW may not support the full range.
*/

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   Spare1;
    uint8   Spare2;
    uint16  LimitFrequency[8]; /* Upper limit frequency of the x'th band */
    int8    BandsGain[8]; /* Gain of the x'th band */
    uint8   Spare3;
    uint8   NameLength;   /* Length of equalizer name */
    char16  Name;
    uint16  Fillers;
    } tISI_AudEquInfoSubBlock;

#define AUD_EQU_INFO_SUB_BLOCK_LEN   (6*sizeof(uint8) + 8*sizeof(uint16) + \
        8*sizeof(int8) + sizeof(char16))


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_COMM_FTD_DATA_BYTE                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  subblockID;
    uint8   subblock_length;
    uint8   data;         /* FTD data byte */
    } AUD_COMM_FTD_DATA_BYTE_STR;

#define AUD_COMM_FTD_DATA_BYTE_STR_LEN   sizeof(AUD_COMM_FTD_DATA_BYTE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_EQU_GENERAL_INFO - Valid from version 006.010             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   EquMaxNum;    /* Max number of equ's */
    uint8   EquPresetNum; /* Number of preset equ's */
    int8    GainMin;      /* Minimum gain */
    int8    GainMax;      /* Maximum gain */
    uint8   BandsMaxNum;  /* Maximum number of bands */
    uint8   Spare1;
    uint16  Bandwidth[8];
    uint16  CenterFreq[8];
    uint16  CrossOverFreq[7];
    uint16  Spare2;
    } tISI_AudEquGeneralInfoSubBlock;

#define AUD_EQU_GENERAL_INFO_LEN   sizeof(tISI_AudEquGeneralInfoSubBlock)


/* ----------------------------------------------------------------------- */
/* Sequence: AUD_LOOPBACK_TONE_GEN_PARAMS_SEQ - Valid from version 010.000 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    /* Digital gain for tone generator output, linear value; 0 db gain equals
       0xFFFF
    */
    uint16  gain;
    uint16  tone_frequency_1; /* 1st Frequency (Hz) */
    uint16  tone_frequency_2; /* 2nd Frequency (Hz) */
    uint8   fill1[2];
    } AUD_LOOPBACK_TONE_GEN_PARAMS_SEQ_STR;

#define SIZE_AUD_LOOPBACK_TONE_GEN_PARAMS_SEQ_STR   \
        sizeof(AUD_LOOPBACK_TONE_GEN_PARAMS_SEQ_STR)


/* ----------------------------------------------------------------------- */
/* Sequence: AUD_LOOPBACK_IN_OUT_PARAMS_SEQ - Valid from version 010.000   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  gain;      /* Gain for inputdB in Q14.1 format, step is 0.5 db */
    /* Input/output mode
       Values from the constant table AUD_INPUT_OUTPUT_MODE
    */
    uint8   mode;
    uint8   fill1;
    } AUD_LOOPBACK_IN_OUT_PARAMS_SEQ_STR;

#define SIZE_AUD_LOOPBACK_IN_OUT_PARAMS_SEQ_STR   \
        sizeof(AUD_LOOPBACK_IN_OUT_PARAMS_SEQ_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_LOOPBACK_INPUT_GAIN_SB - Valid from version 009.009       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    /* Values from the constant table AUD_LOOPBACK_IN_SELECT */
    uint8   input;
    uint8   Filler;
    uint16  gain;         /* dB in Q14.1 format, step is 0.5 db */
    } AUD_LOOPBACK_INPUT_GAIN_SB_STR;

#define SIZE_AUD_LOOPBACK_INPUT_GAIN_SB_STR   \
        sizeof(AUD_LOOPBACK_INPUT_GAIN_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_LOOPBACK_OUTPUT_GAIN_SB - Valid from version 009.009      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    /* Values from the constant table AUD_LOOPBACK_OUT_SELECT */
    uint8   output;
    uint8   Filler;
    uint16  gain;         /* dB in Q14.1 format, step is 0.5 db */
    } AUD_LOOPBACK_OUTPUT_GAIN_SB_STR;

#define SIZE_AUD_LOOPBACK_OUTPUT_GAIN_SB_STR   \
        sizeof(AUD_LOOPBACK_OUTPUT_GAIN_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_LOOPBACK_IN_PARAMS_SB - Valid from version 010.000        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   fill1;
    /* Values from the constant table AUD_LOOPBACK_IN_SELECT */
    uint8   input;
    } AUD_LOOPBACK_IN_PARAMS_SB_STR;

#define SIZE_AUD_LOOPBACK_IN_PARAMS_SB_STR   \
        sizeof(AUD_LOOPBACK_IN_PARAMS_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_LOOPBACK_OUT_PARAMS_SB - Valid from version 010.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint8   fill1;
    /* Values from the constant table AUD_LOOPBACK_OUT_SELECT */
    uint8   output;
    } AUD_LOOPBACK_OUT_PARAMS_SB_STR;

#define SIZE_AUD_LOOPBACK_OUT_PARAMS_SB_STR   \
        sizeof(AUD_LOOPBACK_OUT_PARAMS_SB_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB - Valid from version 010.000 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   SubBlockId;
    uint8   SubBlockLength;
    uint16  Frequencies[2];
    uint8   fill1[2];
    } AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB_STR;

#define SIZE_AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB_STR   \
        sizeof(AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTER_IN_REQ                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* NOTE: Restricting available client types to those above is necessary
       to enable efficient layer handling in the server
       Values from the constant table AUD_CLIENT_TYPES
    */
    uint8   ClientType;
    uint8   Filler;
    } tISI_AudRegisterInReq;

#define AUD_REGISTER_IN_REQ_LEN   sizeof(tISI_AudRegisterInReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTER_IN_OK_RESP                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Identification to be used when accessing the server.
       Client ID is received using AUD_REGISTER_IN_REQ message
    */
    uint8   ClientId;
    uint8   Filler;
    } tISI_AudRegisterInOkResp;

#define AUD_REGISTER_IN_OK_RESP_LEN   sizeof(tISI_AudRegisterInOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTER_IN_FAIL_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_ERROR_CAUSES */
    uint8   FailureReason;
    uint8   Filler;
    } tISI_AudRegisterInFailResp;

#define AUD_REGISTER_IN_FAIL_RESP_LEN   sizeof(tISI_AudRegisterInFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTER_IN_IND                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   ClientType; /* Values from the constant table AUD_CLIENT_TYPES */
    uint8   Filler;
    } tISI_AudRegisterInInd;

#define AUD_REGISTER_IN_IND_LEN   sizeof(tISI_AudRegisterInInd)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTER_OUT_REQ                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Identification to be used when accessing the server.
       Client ID is received using AUD_REGISTER_IN_REQ message
    */
    uint8   ClientId;
    uint8   Filler;
    } tISI_AudRegisterOutReq;

#define AUD_REGISTER_OUT_REQ_LEN   sizeof(tISI_AudRegisterOutReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTER_OUT_OK_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Fillers;
    } tISI_AudRegisterOutOkResp;

#define AUD_REGISTER_OUT_OK_RESP_LEN   sizeof(tISI_AudRegisterOutOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTER_OUT_FAIL_RESP                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_ERROR_CAUSES */
    uint8   FailureReason;
    uint8   Filler;
    } tISI_AudRegisterOutFailResp;

#define AUD_REGISTER_OUT_FAIL_RESP_LEN   sizeof(tISI_AudRegisterOutFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTER_OUT_IND                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   ClientType; /* Values from the constant table AUD_CLIENT_TYPES */
    uint8   Filler;
    } tISI_AudRegisterOutInd;

#define AUD_REGISTER_OUT_IND_LEN   sizeof(tISI_AudRegisterOutInd)


/* ----------------------------------------------------------------------- */
/* Message: AUD_SERVICES_GET_REQ                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Fillers;
    } tISI_AudServicesGetReq;

#define AUD_SERVICES_GET_REQ_LEN   sizeof(tISI_AudServicesGetReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_SERVICES_GET_DEFAULT_OK_RESP                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Fillers;
    } tISI_AudServicesGetDefaultOkResp;

#define AUD_SERVICES_GET_DEFAULT_OK_RESP_LEN   \
        sizeof(tISI_AudServicesGetDefaultOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_SERVICES_GET_CUSTOM_OK_RESP                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Spare;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_SERVICE_REPORT
    */
    } tISI_AudServicesGetCustomOkResp;

#define AUD_SERVICES_GET_CUSTOM_OK_RESP_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ATTRIBUTES_GET_REQ                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    uint8   Filler;
    } tISI_AudAttributesGetReq;

#define AUD_ATTRIBUTES_GET_REQ_LEN   sizeof(tISI_AudAttributesGetReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_ATTRIBUTES_GET_DEFAULT_OK_RESP                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    uint8   Filler;
    } tISI_AudAttributesGetDefaultOkResp;

#define AUD_ATTRIBUTES_GET_DEFAULT_OK_RESP_LEN   \
        sizeof(tISI_AudAttributesGetDefaultOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_ATTRIBUTES_GET_CUSTOM_OK_RESP                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_ATTRIBUTE_SETUP_REPORT
    */
    } tISI_AudAttributesGetCustomOkResp;

#define AUD_ATTRIBUTES_GET_CUSTOM_OK_RESP_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ATTRIBUTES_GET_FAIL_RESP                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    /* A subset of values from the constant table AUD_ERROR_CAUSES */
    uint8   FailureReason;
    } tISI_AudAttributesGetFailResp;

#define AUD_ATTRIBUTES_GET_FAIL_RESP_LEN   \
        sizeof(tISI_AudAttributesGetFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTERED_GET_REQ                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Fillers;
    } tISI_AudRegisteredGetReq;

#define AUD_REGISTERED_GET_REQ_LEN   sizeof(tISI_AudRegisteredGetReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_REGISTERED_GET_OK_RESP                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   NumOfClients;
    /* The field value is composed by adding bit values for corresponding
       registered clients in positions defined by the client type number
       Values from the bitmask table AUD_CLIENT_TYPES_1
    */
    uint8   ClientTypes;
    /* The field value is composed by adding bit values for corresponding
       registered clients in positions defined by the client type number
       Values from the bitmask table AUD_CLIENT_TYPES_2
    */
    uint8   ClientTypesE;
    uint8   Filler1;
    uint8   Filler2;
    uint8   Filler3;
    } tISI_AudRegisteredGetOkResp;

#define AUD_REGISTERED_GET_OK_RESP_LEN   sizeof(tISI_AudRegisteredGetOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_SETTING_GET_REQ                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    uint8   AttributeId;
    } tISI_AudSettingGetReq;

#define AUD_SETTING_GET_REQ_LEN   sizeof(tISI_AudSettingGetReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_SETTING_GET_OK_RESP                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_SETTING_REPORT
    */
    } tISI_AudSettingGetOkResp;

#define AUD_SETTING_GET_OK_RESP_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_SETTING_GET_FAIL_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    uint8   AttributeId;
    /* A subset of values from the constant table AUD_ERROR_CAUSES */
    uint8   FailureReason;
    uint8   Filler1;
    uint8   Filler2;
    uint8   Filler3;
    } tISI_AudSettingGetFailResp;

#define AUD_SETTING_GET_FAIL_RESP_LEN   sizeof(tISI_AudSettingGetFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_LAYER_UPDATE_REQ                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Identification to be used when accessing the server.
       Client ID is received using AUD_REGISTER_IN_REQ message
    */
    uint8   ClientId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    uint8   Spare1;
    uint8   Spare2;
    uint8   Spare3;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_LAYER_SETTING
    */
    } tISI_AudLayerUpdateReq;

#define AUD_LAYER_UPDATE_REQ_LEN   (8*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_LAYER_UPDATE_OK_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    /* Values from the constant table AUD_LAYER_UPDATE_GENERAL_STATUS */
    uint8   GeneralStatus;
    uint16  Spare;
    /* Values from the constant table AUD_LAYER_UPDATE_GENERAL_EFFICIENCY */
    uint8   GeneralEfficiency;
    /* NOTE: attribute-specific sub-blocks are not included if
       "general update status" is AUD_ALL_SETTINGS_OK and "general
       efficiency" is             AUD_ALL_SETTINGS_EFFECTIVE
    */
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_ATTRIBUTE_UPDATE_REPORT
    */
    } tISI_AudLayerUpdateOkResp;

#define AUD_LAYER_UPDATE_OK_RESP_LEN   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_LAYER_UPDATE_FAIL_RESP                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    /* A subset of values from the constant table AUD_ERROR_CAUSES */
    uint8   FailureReason;
    } tISI_AudLayerUpdateFailResp;

#define AUD_LAYER_UPDATE_FAIL_RESP_LEN   sizeof(tISI_AudLayerUpdateFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_LAYER_UPDATE_IND                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_ATTRIBUTE_LAYER_REPORT
    */
    } tISI_AudLayerUpdateInd;

#define AUD_LAYER_UPDATE_IND_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_LAYER_UPDATE_NEEDED_IND                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* The client from which the server wants to get update for its layer
       settings              Client ID is received using AUD_REGISTER_IN_REQ
       message
    */
    uint8   ClientId;
    /* A subset of values from the constant table AUD_SERVICES_ALL */
    uint8   ServiceId;
    } tISI_AudLayerUpdateNeededInd;

#define AUD_LAYER_UPDATE_NEEDED_IND_LEN   \
        sizeof(tISI_AudLayerUpdateNeededInd)


/* ----------------------------------------------------------------------- */
/* Message: AUD_LAYER_DESTROY_REQ                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Identification to be used when accessing the server.
       Client ID is received using AUD_REGISTER_IN_REQ message
    */
    uint8   ClientId;
    uint8   ServiceId;  /* Values from the constant table AUD_SERVICES_ALL */
    uint8   AttributeId;
    uint8   Filler1;
    uint8   Filler2;
    uint8   Filler3;
    } tISI_AudLayerDestroyReq;

#define AUD_LAYER_DESTROY_REQ_LEN   sizeof(tISI_AudLayerDestroyReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_LAYER_DESTROY_OK_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   ServiceId;  /* Values from the constant table AUD_SERVICES_ALL */
    uint8   AttributeId;
    } tISI_AudLayerDestroyOkResp;

#define AUD_LAYER_DESTROY_OK_RESP_LEN   sizeof(tISI_AudLayerDestroyOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_LAYER_DESTROY_FAIL_RESP                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   ServiceId;  /* Values from the constant table AUD_SERVICES_ALL */
    /* A subset of values from the constant table AUD_ERROR_CAUSES */
    uint8   FailureReason;
    } tISI_AudLayerDestroyFailResp;

#define AUD_LAYER_DESTROY_FAIL_RESP_LEN   \
        sizeof(tISI_AudLayerDestroyFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_TEST_START_REQ - Obsolete from version 008.015             */
/* ----------------------------------------------------------------------- */

#if !AUD_ISI_MIN_VERSION(8,15)

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   TestType;     /* Values from the constant table AUD_TEST_TYPES */
    uint8   Spare;
    uint16  Frequency;
    uint16  Duration;
    } tISI_AudTestStartReq;

#define AUD_TEST_START_REQ_LEN   sizeof(tISI_AudTestStartReq)

#endif /* !AUD_ISI_MIN_VERSION(8,15) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_TEST_START_REQ - Versions 008.016 - 009.000                */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(8,16) && !AUD_ISI_MIN_VERSION(9,0)

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   TestType;     /* Values from the constant table AUD_TEST_TYPES */
    uint8   Spare;
    uint16  Frequency;
    uint16  Duration;
    } tISI_AudTestStartReq;

#define AUD_TEST_START_REQ_LEN   sizeof(tISI_AudTestStartReq)

#endif /* AUD_ISI_MIN_VERSION(8,16) && !AUD_ISI_MIN_VERSION(9,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_TEST_START_REQ - Valid from version 009.000                */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(9,0)

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   TestType;     /* Values from the constant table AUD_TEST_TYPES */
    uint8   Spare;
    uint16  Frequency;
    uint16  Duration;
    } tISI_AudTestStartReq;

#define AUD_TEST_START_REQ_LEN   sizeof(tISI_AudTestStartReq)

#endif /* AUD_ISI_MIN_VERSION(9,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_TEST_START_OK_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Started test type
       Values from the constant table AUD_TEST_TYPES
    */
    uint8   TestType;
    uint8   Filler;
    } tISI_AudTestStartOkResp;

#define AUD_TEST_START_OK_RESP_LEN   sizeof(tISI_AudTestStartOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_TEST_START_FAIL_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   TestType;     /* Values from the constant table AUD_TEST_TYPES */
    /* Values from the constant table AUD_TEST_ERRORS */
    uint8   FailureReason;
    } tISI_AudTestStartFailResp;

#define AUD_TEST_START_FAIL_RESP_LEN   sizeof(tISI_AudTestStartFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_TEST_STOP_REQ                                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   TestType;     /* Values from the constant table AUD_TEST_TYPES */
    uint8   Filler;
    } tISI_AudTestStopReq;

#define AUD_TEST_STOP_REQ_LEN   sizeof(tISI_AudTestStopReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_TEST_STOP_OK_RESP                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   TestType;     /* Values from the constant table AUD_TEST_TYPES */
    uint8   Filler;
    } tISI_AudTestStopOkResp;

#define AUD_TEST_STOP_OK_RESP_LEN   sizeof(tISI_AudTestStopOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_TEST_STOP_FAIL_RESP                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   TestType;     /* Values from the constant table AUD_TEST_TYPES */
    /* Values from the constant table AUD_TEST_ERRORS */
    uint8   FailureReason;
    } tISI_AudTestStopFailResp;

#define AUD_TEST_STOP_FAIL_RESP_LEN   sizeof(tISI_AudTestStopFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EANC_STATUS_CHANGE_REQ - Valid from version 008.008        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Command;      /* Values from the constant table AUD_EANC_STATE */
    uint8   Filler;
    } tISI_AudEancStatusChangeReq;

#define AUD_EANC_STATUS_CHANGE_REQ_LEN   sizeof(tISI_AudEancStatusChangeReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EANC_STATUS_CHANGE_RESP - Valid from version 008.008       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Command;      /* Values from the constant table AUD_EANC_STATE */
    uint8   Filler;
    } tISI_AudEancStatusChangeResp;

#define AUD_EANC_STATUS_CHANGE_RESP_LEN   \
        sizeof(tISI_AudEancStatusChangeResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EANC_STATUS_CHANGE_IND - Valid from version 008.014        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Status;       /* Values from the constant table AUD_EANC_STATE */
    uint8   Filler;
    } tISI_AudEancStatusChangeInd;

#define AUD_EANC_STATUS_CHANGE_IND_LEN   sizeof(tISI_AudEancStatusChangeInd)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EANC_MIC_DATA_REQ - Valid from version 008.017             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    } tISI_AudEancMicDataReq;

#define AUD_EANC_MIC_DATA_REQ_LEN   sizeof(tISI_AudEancMicDataReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EANC_MIC_DATA_RESP - Valid from version 008.017            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Mic1Data_hi;  /* Microphone 1 level data, signed 24 bits */
    uint16  Mic1Data_low;
    uint16  Mic2Data_hi;  /* Microphone 2 level data, signed 24 bits */
    uint16  Mic2Data_low;
    } tISI_AudEancMicDataResp;

#define AUD_EANC_MIC_DATA_RESP_LEN   sizeof(tISI_AudEancMicDataResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_HW_STATUS_IND                                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   hw_status;   /* Values from the constant table AUD_HW_STATUSES */
    uint8   Filler;
    } tISI_AudHWStatusInd;

#define AUD_HW_STATUS_IND_LEN   sizeof(tISI_AudHWStatusInd)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_CREATE_REQ                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;  /* Unique ID number of the equalizer */
    uint8   Bands;        /* Amount of used bands in the equalizer */
    uint8   EqualizerType; /* Values from the constant table AUD_EQU_TYPE */
    uint8   Spare1;
    uint8   Spare2;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_EQU_DEFINITION
    */
    } tISI_AudEquCreateReq;

#define AUD_EQU_CREATE_REQ_LEN   (8*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_CREATE_OK_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Fillers;
    } tISI_AudEquCreateOkResp;

#define AUD_EQU_CREATE_OK_RESP_LEN   sizeof(tISI_AudEquCreateOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_CREATE_FAIL_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Values from the constant table AUD_EQU_FAILURE_REASON */
    uint8   FailureReason;
    uint8   Filler;
    } tISI_AudEquCreateFailResp;

#define AUD_EQU_CREATE_FAIL_RESP_LEN   sizeof(tISI_AudEquCreateFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_INFO_REQ                                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;  /* Unique ID number of the equalizer */
    uint8   Filler;
    } tISI_AudEquInfoReq;

#define AUD_EQU_INFO_REQ_LEN   sizeof(tISI_AudEquInfoReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_INFO_OK_RESP                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Unique ID number of the equalizer.
       This is the same ID as in the request
    */
    uint8   EqualizerId;
    uint8   Bands;        /* Amount of used bands in the equalizer */
    uint8   EqualizerType; /* Values from the constant table AUD_EQU_TYPE */
    /* Values from the constant table AUD_EQU_STATE */
    uint8   EqualizerState;
    uint8   Spare;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_EQU_DEFINITION
    */
    } tISI_AudEquInfoOkResp;

#define AUD_EQU_INFO_OK_RESP_LEN   (8*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_INFO_FAIL_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Values from the constant table AUD_EQU_FAILURE_REASON */
    uint8   FailureReason;
    uint8   Filler;
    } tISI_AudEquInfoFailResp;

#define AUD_EQU_INFO_FAIL_RESP_LEN   sizeof(tISI_AudEquInfoFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_SWITCH_STATE_REQ                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;  /* Unique ID number of the equalizer */
    uint8   State;        /* Values from the constant table AUD_EQU_STATE */
    } tISI_AudEquSwitchStateReq;

#define AUD_EQU_SWITCH_STATE_REQ_LEN   sizeof(tISI_AudEquSwitchStateReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_SWITCH_STATE_OK_RESP                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Fillers;
    } tISI_AudEquSwitchStateOkResp;

#define AUD_EQU_SWITCH_STATE_OK_RESP_LEN   \
        sizeof(tISI_AudEquSwitchStateOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_SWITCH_STATE_FAIL_RESP                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_ERROR_CAUSES */
    uint8   FailureReason;
    uint8   Filler;
    } tISI_AudEquSwitchStateFailResp;

#define AUD_EQU_SWITCH_STATE_FAIL_RESP_LEN   \
        sizeof(tISI_AudEquSwitchStateFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_SWITCH_STATE_IND                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;  /* Unique ID number of the equalizer */
    uint8   State;        /* Values from the constant table AUD_EQU_STATE */
    } tISI_AudEquSwitchStateInd;

#define AUD_EQU_SWITCH_STATE_IND_LEN   sizeof(tISI_AudEquSwitchStateInd)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_ADJUST_REQ                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;  /* Unique ID number of the equalizer */
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_EQU_DEFINITION
    */
    } tISI_AudEquAdjustReq;

#define AUD_EQU_ADJUST_REQ_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_ADJUST_OK_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Fillers;
    } tISI_AudEquAdjustOkResp;

#define AUD_EQU_ADJUST_OK_RESP_LEN   sizeof(tISI_AudEquAdjustOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_ADJUST_FAIL_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Values from the constant table AUD_EQU_FAILURE_REASON */
    uint8   FailureReason;
    uint8   Filler;
    } tISI_AudEquAdjustFailResp;

#define AUD_EQU_ADJUST_FAIL_RESP_LEN   sizeof(tISI_AudEquAdjustFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_DELETE_REQ                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;  /* Unique ID number of the equalizer */
    uint8   Filler;
    } tISI_AudEquDeleteReq;

#define AUD_EQU_DELETE_REQ_LEN   sizeof(tISI_AudEquDeleteReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_DELETE_OK_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;  /* Unique ID number of the equalizer */
    uint8   Filler;
    } tISI_AudEquDeleteOkResp;

#define AUD_EQU_DELETE_OK_RESP_LEN   sizeof(tISI_AudEquDeleteOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_DELETE_FAIL_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Values from the constant table AUD_EQU_FAILURE_REASON */
    uint8   FailureReason;
    uint8   Filler;
    } tISI_AudEquDeleteFailResp;

#define AUD_EQU_DELETE_FAIL_RESP_LEN   sizeof(tISI_AudEquDeleteFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_ACTIVE_ID_REQ                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Fillers;
    } tISI_AudEquActiveIdReq;

#define AUD_EQU_ACTIVE_ID_REQ_LEN   sizeof(tISI_AudEquActiveIdReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_ACTIVE_ID_OK_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Value from 0 to AUD_EQUALIZERS_MAX. See product configuration file */
    uint8   EqualizerId;
    uint8   Filler;
    } tISI_AudEquActiveIdOkResp;

#define AUD_EQU_ACTIVE_ID_OK_RESP_LEN   sizeof(tISI_AudEquActiveIdOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_ACTIVE_ID_FAIL_RESP                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* A subset of values from the constant table AUD_EQU_FAILURE_REASON */
    uint8   FailureReason;
    uint8   Filler;
    } tISI_AudEquActiveIdFailResp;

#define AUD_EQU_ACTIVE_ID_FAIL_RESP_LEN   sizeof(tISI_AudEquActiveIdFailResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_GENERAL_INFO_REQ - Valid from version 006.010          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Filler;
    } tISI_AudEquGeneralInfoReq;

#define AUD_EQU_GENERAL_INFO_REQ_LEN   sizeof(tISI_AudEquGeneralInfoReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_GENERAL_INFO_RESP - Valid from version 006.010         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Filler;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_EQU_GENERAL_INFO
    */
    } tISI_AudEquGeneralInfoResp;

#define AUD_EQU_GENERAL_INFO_RESP_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_CREATED_IND - Valid from version 006.010               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_EQU_DEFINITION
    */
    } tISI_AudEquCreatedInd;

#define AUD_EQU_CREATED_IND_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_DELETED_IND - Valid from version 006.010               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;
    uint8   Filler;
    } tISI_AudEquDeletedInd;

#define AUD_EQU_DELETED_IND_LEN   sizeof(tISI_AudEquDeletedInd)


/* ----------------------------------------------------------------------- */
/* Message: AUD_EQU_ADJUSTED_IND - Valid from version 006.010              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   EqualizerId;
    uint8   NumOfSubBlocks;
    /* Subblock list:
       AUD_EQU_DEFINITION
    */
    } tISI_AudEquAdjustedInd;

#define AUD_EQU_ADJUSTED_IND_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_SCO_CONTROL_REQ                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   State;        /* Values from the constant table AUD_SCO_STATE */
    uint8   Filler;
    } tISI_AudScoControlReq;

#define AUD_SCO_CONTROL_REQ_LEN   sizeof(tISI_AudScoControlReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_SCO_CONTROL_RESP                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Status;       /* Values from the constant table AUD_SCO_STATUS */
    uint8   Filler;
    } tISI_AudScoControlResp;

#define AUD_SCO_CONTROL_RESP_LEN   sizeof(tISI_AudScoControlResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_BTHSTREAM_STATUS_CHANGE_REQ - Valid from version 005.020   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Command;   /* Values from the constant table AUD_AVDTP_COMMAND */
    /* Values from the constant table AUD_AVDTP_STREAM_TYPE */
    uint8   StreamType;
    } tISI_AudBthstreamStatusChangeReq;

#define AUD_BTHSTREAM_STATUS_CHANGE_REQ_LEN   \
        sizeof(tISI_AudBthstreamStatusChangeReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_BTHSTREAM_STATUS_CHANGE_RESP - Valid from version 005.020  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Command;   /* Values from the constant table AUD_AVDTP_COMMAND */
    uint8   Status;     /* Values from the constant table AUD_AVDTP_STATUS */
    } tISI_AudBthstreamStatusChangeResp;

#define AUD_BTHSTREAM_STATUS_CHANGE_RESP_LEN   \
        sizeof(tISI_AudBthstreamStatusChangeResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_DEFATTR_CHANGE_REQ - Valid from version 005.022            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Service;      /* Currently only supported valus is AUD_MODE */
    /* Currently only supported value is AUD_MODE_ACCESSORY */
    uint8   AttributeId;
    /* Currently only supported value is Audio mode (AUD_MODE_HP /
       AUD_MODE_HAC)                                Note! Value is actually
       uint16 (Correction to Macro done later)
       xxxxxxxx--------  Filler
       --------xxxxxxxx  Value
    */
    uint16  Value;
    uint16  Spare;
    } tISI_AudDefAttrChangeReq;

#define AUD_DEFATTR_CHANGE_REQ_LEN   sizeof(tISI_AudDefAttrChangeReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_DEFATTR_CHANGE_RESP - Valid from version 005.022           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Status;   /* Values from the constant table AUD_DEFATTR_STATUS */
    uint8   Filler;
    } tISI_AudDefAttrChangeResp;

#define AUD_DEFATTR_CHANGE_RESP_LEN   sizeof(tISI_AudDefAttrChangeResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_DEFATTR_VALUE_GET_REQ - Valid from version 005.022         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Service;      /* Currently only supported value is AUD_MODE */
    /* Currently only supported value is AUD_MODE_ACCESSORY */
    uint8   AttributeId;
    } tISI_AudDefAttrValueGetReq;

#define AUD_DEFATTR_VALUE_GET_REQ_LEN   sizeof(tISI_AudDefAttrValueGetReq)


/* ----------------------------------------------------------------------- */
/* Message: AUD_DEFATTR_VALUE_GET_RESP - Valid from version 005.022        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   Status;   /* Values from the constant table AUD_DEFATTR_STATUS */
    uint8   Filler1;
    /* Currently only supported value is Audio mode (AUD_MODE_HP /
       AUD_MODE_HAC)                                Note! Value is actually
       uint16 (Correction to Macro done later)
       xxxxxxxx--------  Filler
       --------xxxxxxxx  Value
    */
    uint16  Value;
    uint16  Filler2;
    } tISI_AudDefAttrValueGetResp;

#define AUD_DEFATTR_VALUE_GET_RESP_LEN   sizeof(tISI_AudDefAttrValueGetResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_VOLUME_CONTROL_REQ - Valid from version 006.013            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   fill1;
    uint8   num_of_subblocks;
    /* Subblock list:
       AUD_VOLUME_CONTROL_SB
    */
    } AUD_VOLUME_CONTROL_REQ_STR;

#define AUD_VOLUME_CONTROL_REQ_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_VOLUME_CONTROL_RESP - Valid from version 006.013           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Bitfield, informs which media type settings failed, zero = all OK
       Values from the bitmask table AUD_VOLUME_MEDIA_TYPE
    */
    uint16  failed_media_types;
    uint8   fill1[2];
    uint8   fill2;
    uint8   num_of_subblocks;
    /* Subblock list:
       AUD_VOLUME_CONTROL_RESPONSE_SB
    */
    } AUD_VOLUME_CONTROL_RESP_STR;

#define AUD_VOLUME_CONTROL_RESP_LEN   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: AUD_VOLUME_GET_REQ - Valid from version 006.013                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* Bitfield, requested media type volume settings will be delivered in
       response message subblock / media type
       Values from the bitmask table AUD_VOLUME_MEDIA_TYPE
    */
    uint16  media_types;
    } AUD_VOLUME_GET_REQ_STR;

#define AUD_VOLUME_GET_REQ_LEN   sizeof(AUD_VOLUME_GET_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_VOLUME_GET_RESP - Valid from version 006.013               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   fill1;
    uint8   num_of_subblocks;
    /* Subblock list:
       AUD_VOLUME_CONTROL_SB
    */
    } AUD_VOLUME_GET_RESP_STR;

#define AUD_VOLUME_GET_RESP_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_VOLUME_CONTROL_IND - Valid from version 008.012            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   fill1;
    uint8   num_of_subblocks;
    /* Subblock list:
       AUD_VOLUME_CONTROL_RESPONSE_SB
    */
    } AUD_VOLUME_CONTROL_IND_STR;

#define AUD_VOLUME_CONTROL_IND_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ATTACH_ACCESSORY_EVENT_REQ - Valid from version 005.027    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    /* If master_type/sub_type not in use (in case of
       ACC_THWK_FEATURE_INFO_IND), it must be defined as NO_INFORMATION
       Values from the constant table ACC_THWK_MASTER_TYPE
    */
    uint8   master_type;
    uint8   sub_type;
    /* If AccID not in use (in case of ACC_THWK_FEATURE_INFO_IND), it must be
       defined as NO_INFORMATION
    */
    uint8   acc_id;
    uint8   reserved1;
    uint8   reserved2;
    uint8   sub_block_count;
    /* These following subblocks are inherited from acc_shared_isi.h
       Subblock list:
       ACC_SB_THWK_AUDIO_BLOCK
       ACC_SB_THWK_EXEC_FEATURE
       ACC_SB_THWK_INFO_FEATURE
    */
    } tISI_AudAttachAccEventReq;

#define AUD_ATTACH_ACCESSORY_EVENT_REQ_LEN   (8*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_ATTACH_ACCESSORY_EVENT_OK_RESP - Valid from version 005.027 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint8   reserved1;
    uint8   reserved2;
    } tISI_AudAttachAccEventOkResp;

#define AUD_ATTACH_ACCESSORY_EVENT_OK_RESP_LEN   \
        sizeof(tISI_AudAttachAccEventOkResp)


/* ----------------------------------------------------------------------- */
/* Message: AUD_FIFO_INTERRUPT_IND - Valid from version 007.009            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId;
    uint8   MessageId;
    uint16  Filler;
    } tISI_AudFifoInterruptInd;

#define AUD_FIFO_INTERRUPT_IND_LEN   sizeof(tISI_AudFifoInterruptInd)


/* ----------------------------------------------------------------------- */
/* Message: AUD_S60_VOIP_EMERGENCY_CALL_NTF - Valid from version 009.003   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId; /* Voip emergency call notification */
    uint8   MessageId;
    uint8   State;
    uint8   Filler;
    } AUD_S60_VOIP_EMERGENCY_CALL_NTF_STR;

#define AUD_S60_VOIP_EMERGENCY_CALL_NTF_LEN   \
        sizeof(AUD_S60_VOIP_EMERGENCY_CALL_NTF_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_FEATURE_SET_REQ - Valid from version 009.004               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId; /* Feature set request */
    uint8   MessageId;
    uint8   FeatureId;    /* Values from the constant table AUD_FEATURE_ID */
    uint8   FeatureIdState;
    } AUD_FEATURE_SET_REQ_STR;

#define AUD_FEATURE_SET_REQ_LEN   sizeof(AUD_FEATURE_SET_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_FEATURE_SET_RESP - Valid from version 009.004              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId; /* Feature set response */
    uint8   MessageId;
    uint8   Result;
    uint8   Filler;
    } AUD_FEATURE_SET_RESP_STR;

#define AUD_FEATURE_SET_RESP_LEN   sizeof(AUD_FEATURE_SET_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_SELFTEST_REQ - Valid from version 009.006                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId; /* Selftest request */
    uint8   MessageId;
    uint8   TestType; /* Values from the constant table AUD_SELFTEST_TYPES */
    uint8   Filler;
    } AUD_SELFTEST_REQ_STR;

#define AUD_SELFTEST_REQ_LEN   sizeof(AUD_SELFTEST_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_SELFTEST_RESP - Valid from version 009.006                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId; /* Selftest response */
    uint8   MessageId;
    uint8   TestResult;
    uint8   Filler;
    } AUD_SELFTEST_RESP_STR;

#define AUD_SELFTEST_RESP_LEN   sizeof(AUD_SELFTEST_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: AUD_LOOPBACK_REQ - Versions 009.009 - 010.000                  */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(9,9) && !AUD_ISI_MIN_VERSION(10,0)

typedef struct
    {
    uint8   TransactionId; /* Loopback request */
    uint8   MessageId;
    uint8   InputNum;
    uint8   OutputNum;
    } AUD_LOOPBACK_REQ_STR;

#define AUD_LOOPBACK_REQ_LEN   (4*sizeof(uint8))

#endif /* AUD_ISI_MIN_VERSION(9,9) && !AUD_ISI_MIN_VERSION(10,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_LOOPBACK_REQ - Valid from version 010.000                  */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(10,0)

typedef struct
    {
    uint8   TransactionId; /* Loopback request */
    uint8   MessageId;
    uint8   fill1;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_LOOPBACK_IN_PARAMS_SB
       AUD_LOOPBACK_OUT_PARAMS_SB
    */
    } AUD_LOOPBACK_REQ_STR;

#define AUD_LOOPBACK_REQ_LEN   (4*sizeof(uint8))

#endif /* AUD_ISI_MIN_VERSION(10,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_LOOPBACK_RESP - Versions 009.009 - 010.000                 */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(9,9) && !AUD_ISI_MIN_VERSION(10,0)

typedef struct
    {
    uint8   TransactionId; /* Loopback response */
    uint8   MessageId;
    uint8   Result;
    uint8   fill1;
    } AUD_LOOPBACK_RESP_STR;

#define AUD_LOOPBACK_RESP_LEN   sizeof(AUD_LOOPBACK_RESP_STR)

#endif /* AUD_ISI_MIN_VERSION(9,9) && !AUD_ISI_MIN_VERSION(10,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_LOOPBACK_RESP - Valid from version 010.000                 */
/* ----------------------------------------------------------------------- */

#if AUD_ISI_MIN_VERSION(10,0)

typedef struct
    {
    uint8   TransactionId; /* Loopback response */
    uint8   MessageId;
    uint8   Result;
    uint8   nbr_of_subblocks;
    /* Subblock list:
       AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB
    */
    } AUD_LOOPBACK_RESP_STR;

#define AUD_LOOPBACK_RESP_LEN   (4*sizeof(uint8))

#endif /* AUD_ISI_MIN_VERSION(10,0) */


/* ----------------------------------------------------------------------- */
/* Message: AUD_LOOPBACK_GAIN_SET_REQ - Valid from version 009.009         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId; /* Loopback gain set request */
    uint8   MessageId;
    uint8   fill1;
    uint8   SbCounter;
    /* Subblock list:
       AUD_LOOPBACK_INPUT_GAIN_SB
       AUD_LOOPBACK_OUTPUT_GAIN_SB
    */
    } AUD_LOOPBACK_GAIN_SET_REQ_STR;

#define AUD_LOOPBACK_GAIN_SET_REQ_LEN   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: AUD_LOOPBACK_GAIN_SET_RESP - Valid from version 009.009        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   TransactionId; /* Loopback gain set response */
    uint8   MessageId;
    uint8   Result;
    uint8   fill1;
    } AUD_LOOPBACK_GAIN_SET_RESP_STR;

#define AUD_LOOPBACK_GAIN_SET_RESP_LEN   \
        sizeof(AUD_LOOPBACK_GAIN_SET_RESP_STR)




#endif /* _AUDIO_ISI_H */
