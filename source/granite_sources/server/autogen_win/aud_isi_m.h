/*
NOKIA
R&D Oulu
ISA Operations










            AUDIO Server Message Macro definitions
            --------------------------------------

            SW include - ANSI C




Continuus Ref:
--------------
database:       ou1gif

project path:   global_interface/ISI/Core

%name:              aud_isi_m.h %

%version:           sa1aswx1#010.002 %

%cvtype:            incl %

%instance:          ou_pcms_2 %


Copyright(c)Nokia


Change history:

VERSION     : 010.002 NONDRAFT  14-Jun-2011 Jani Kärkelä
DESCRIPTION : sa1aswx1#118863: MCU Audio: Jani Karkela: ISA Audio interface: Support for sidetone switch (ou1cimx1#844106)
REFERENCE   : SWAM CR: JR11061043660

VERSION     : 010.001 NONDRAFT  27-May-2011 Adrian Chirica
DESCRIPTION : ou1s40#108619: Audio_S40: Adrian Chirica: Conversion to XML files for Coltrane tool fails (AC11052435524)
REFERENCE   : SWAM CR: AC11052756663

VERSION     : 010.000 NONDRAFT  07-Apr-2011 Adrian Chirica
DESCRIPTION : ou1s40#93139: Audio S40: Adrian Chirica: Change Audio Test loops to use subblocks (1152025)
REFERENCE   : SWAM CR: AC11041159481

VERSION     : 009.013 NONDRAFT  24-Mar-2011 Anton NEvala
DESCRIPTION : ou1s40#100019 Audio_s40: Audio ISI hdr: Anton Nevala: Audio server ISI header changes (AN11032440034)
REFERENCE   : SWAM CR: AN11032440034

VERSION     : 009.012 NONDRAFT  11-Jan-2011 Tuomas Haikarainen
DESCRIPTION : sa1aswx1#112873: MCU Audio: Tuomas Haikarainen: ISA Audio Server: Support for uplink noise cancellation switch (1165476)
REFERENCE   : SWAM CR: JR11011356972

VERSION     : 009.011 NONDRAFT  23-Nov-2010 Ville Laaksonen
DESCRIPTION : sa1aswx1#108129: MCU Audio: Ville Laaksonen: Layer based ACA algorithm control (JR10112338329)
REFERENCE   : SWAM CR: JR10112338329

VERSION     : 009.010 NONDRAFT  29-Jan-2010 Adrian Chirica
DESCRIPTION : ou1core#167518: Audio_S40: Adrian Chirica: Add 3 new selection values for MIXER_DL_OUT_ and MIXER_UL_IN_ (AC10012248779)
REFERENCE   : SWAM CR: AC10012248779

VERSION     : 009.009 NONDRAFT  25-Jun-2009 Paavo Salonen
DESCRIPTION : ou1core#141017: Audio: Paavo Salonen: Audio isi change, new audio loopback interface fine tuning (PS09061651680)
REFERENCE   : SWAM CR: PS09061651680

VERSION     : 009.008 NONDRAFT  22-Jun-2009 Seppo Jauho
DESCRIPTION : ou1core#140553: Audio: Seppo Jauho: Audio isi change, usb tty mode added (AN09061631439)
REFERENCE   : SWAM CR: AN09061631439

VERSION     : 009.007 NONDRAFT  27-Apr-2009 Katja Ahonen
DESCRIPTION : ou1core#: Audio: Katja Ahonen: Gazoo TPA selection
REFERENCE   : SWAM CR: KA09042739989

VERSION     : 009.006 NONDRAFT  03-Apr-2009 Katja Ahonen
DESCRIPTION : ou1core#130794: Audio: Katja Ahonen: Changes to Audio server interface, new messages for MCL
REFERENCE   : SWAM CR: PS09032047966

VERSION     : 009.005 NONDRAFT  31-Mar-2009 Niina Pussinen
DESCRIPTION : ou1core#128709: Audio: Niina Pussinen: MCL fix for Hands Free Voice UI (SCO 417-35747)
REFERENCE   : SWAM CR: NP09031339141

VERSION     : 009.004 NONDRAFT  18-Mar-2009 Niina Pussinen
DESCRIPTION : ou1core#125979: Audio: Niina Pussinen: MCL Hands Free Voice UI (SCO 417-35747)
REFERENCE   : SWAM CR: NP09031339141

VERSION     : 009.003 NONDRAFT  06-Mar-2009 Katja Ahonen
DESCRIPTION : ou1core#123426: Audio: Katja Ahonen: Changes to Audio server interface, new messages and new audio modes (for MCL)
REFERENCE   : SWAM CR: KA09021158148

VERSION     : 009.002 NONDRAFT  18-Feb-2009 Seppo Jauho
DESCRIPTION : ou1core#122072: Audio: Seppo Jauho: GPA isi interface (SJ09010841712)
REFERENCE   : SWAM CR: SJ09010841712

VERSION     : 009.001 NONDRAFT  27-Jan-2009 Katja Ahonen
DESCRIPTION : ou1core#119300 Audio: Katja Ahonen: Audio mic testing through uUSB (AN08101685298)
REFERENCE   : SWAM CR: AN08101685298

VERSION     : 009.000 NONDRAFT  16-Jan-2009 Katja Ahonen
DESCRIPTION : ou1core#118139 Audio: Katja Ahonen: ISI interface changes for test loops (KA09010952478)
REFERENCE   : SWAM CR: KA09010952478

VERSION     : 008.019 NONDRAFT  12-Sep-2008 Adrian Chirica
DESCRIPTION : ou1core#101653 Audio: Adrian Chirica: Add secondary audio mode to interface (AC08083040574)
REFERENCE   : SWAM CR: AC08083040574

VERSION     : 008.018 NONDRAFT  15-May-2008 Adrian Chirica
DESCRIPTION : ou1core#92861 MCU Audio: Adrian Chirica: Fix task for ou1core#90208
REFERENCE   : SWAM CR: AN08041749576

VERSION     : 008.017 NONDRAFT  08-May-2008 Adrian Chirica and Jaakko Rautiainen
DESCRIPTION : ou1core#91988: MCU Audio: Adrian Chirica and Jaakko Rautiainen - ISI update with three new test loops
              for twin microphones and more EANC messages               
REFERENCE   : SWAM CR: AC08042449305

VERSION     : 008.016 NONDRAFT  23-Mar-2008 Pasi Alatalo
REFERENCE   : ou1core#90208: MCU Audio: Pasi Alatalo: Audio server ISI update, MCU Audio ISI Interface change for new test loop (417-5393)
              SWAM CR: AN08041749576

VERSION     : 008.015 NONDRAFT  31-Mar-2008 Petteri Hyvonen
REFERENCE   : ou1core#88747: MCU Audio: Petteri Hyvonen: Audio server ISI update, New DL out selections for I2S left and right (417-3729)
              SWAM CR: EH08033156573

VERSION     : 008.014 NONDRAFT  20-Mar-2008 Jaakko Rautiainen
REFERENCE   : ou1core#88270: Audio: Jaakko Rautiainen: EANC Audio Server ISI interface update, new indication, GLOBAL_HEADERS (417-3317)
              SWAM CR: JR08032051561
              
VERSION     : 008.013 NONDRAFT  19-Feb-2008 Jaakko Rautiainen
REFERENCE   : ou1core#84732: MCU Audio: Jaakko Rautiainen: EANC Audio Server ISI interface update, test loops (403-13253,403-13383)
              SWAM CR: JR08022051386
              
VERSION     : 008.012 NONDRAFT  14-Feb-2008 Janne Ervasti, Rasmus Rahunen, Jani Kärkelä
REASON      : Audio server UPP split, new indication and change request.
REFERENCE   : 414-4504, 403-5694, 403-10649
DESCRIPTION : Removal of unnecessary messages and flagging of BB5 specific messages.
              Added new indication AUD_VOLUME_CONTROL_IND and new parameters to 
              AUD_VOLUME_CONTROL_RESPONSE_SB. ISI interface update, POC_HS and POC_BTH modes.

VERSION     : 008.011 NONDRAFT  15-Jan-2008 Janne Vimpari
REFERENCE   : SWAM CR: JV08011556803: Separate EAP ISI messages from Audio ISI messages
              

VERSION     : 008.010 NONDRAFT  14-Jan-2008 Janne Vimpari
REFERENCE   : 403-9345 Aud EAP: Implement run time data path tracing
              SWAM CR: JV0801044858

VERSION     : 008.009 NONDRAFT  10-Dec-2007 Paavo Salonen
REFERENCE   : 401-5601: Audio Srv: SW support for True WB concept
              SWAM CR: PS07121059105

VERSION     : 008.008 NONDRAFT  20-Nov-2007 Jaakko Rautiainen
REFERENCE   : ou1core#79218: MCU Audio: Jaakko Rautiainen: EANC Audio Server ISI interface update [403-9201]
              SWAM CR: JR07111958783 
              
VERSION     : 008.007 NONDRAFT  06-Nov-2007 Paavo Salonen
REFERENCE   : 401-5611: Audio Server: ISI IF changes for Support for proper stereo recording
              SWAM CR: PS07110651102

VERSION     : 008.006 NONDRAFT  25-Sep-2007 Seppo Jauho
REFERENCE   : 401-5500: Audio Srv: FMTX Improvements, FMTX Specific Audio mode (RD)
              SWAM CR: SJ07092554528

VERSION     : 008.005 NONDRAFT   19-Sep-2007  Seppo Jauho
REASON      : Change Request
REFERENCE   : RM-RIM 401-5307, RM-RIM 401-5190, ADB SWAM SJ07091242230
DESCRIPTION : Add AUD_MODE_MOBILE_TV to audio server interface.
              HAC support via DSP HW control.

VERSION     : 008.004 NONDRAFT   09-Aug-2007  Mika P. Kangas
REASON      : Change Request
REFERENCE   : RM-RIM 02-2988, 010-31685, ADB SWAM MK07080950055
DESCRIPTION : Create ISI interface for new USB Audio modes
  
VERSION     : 008.003 NONDRAFT   26-Jun-2007  Janne Vimpari
REASON      : Change Request
REFERENCE   : RM-RIM 009-30070, ADB SWAM JV07060855686
DESCRIPTION : Create ISI interface for Audio Visualization post effect
  
VERSION     : 008.002 NONDRAFT   19-Jun-2007  Janne Vimpari
REASON      : Change Request
REFERENCE   : RM-RIM 403-1583, ADB SWAM JV07061359846
DESCRIPTION : Add AUD_MODE_AUDIO_REC to audio server interface

VERSION     : 008.001    DRAFT   3-May-2007  Janne Ervasti
REASON      : Change Request
REFERENCE   : RM-RIM 009-28730, ADB SWAM JE07050239685
DESCRIPTION : FTD data mode changes.

VERSION     : 008.000  NONDRAFT  22-Mar-2006 Anton Nevala
REFERENCE   : 009-31893 & EJ07021956160
              SWAM CR: AN07032036224

VERSION     : 007.009  NONDRAFT  13-Mar-2006 Marko Kangasluoma
REFERENCE   : 010-34994: Audio Srv: FIFO empty interrupt indication - interface change
              SWAM CR: MK07031251079

VERSION     : 007.008  NONDRAFT  20-Dec-2006 Anton Nevala
REFERENCE   : 009-27812 Mute logic for audio
              SWAM CR: AN06121952700

VERSION     : 007.007  NONDRAFT  22-Nov-2006 Mika P. Kangas
REASON      : Change request
REFERENCE   : 010-28011: AUD Srv: DSP Configuration for USB Audio Accessories
              009-23931: AUD Srv: DAC33: Provide an interface for Real Time and High Speed playback
              SWAM CR: MK06112154700

VERSION     : 007.006  NONDRAFT  10-Nov-2006 Mika P. Kangas
REASON      : Change request
REFERENCE   : 010-28010: AUD Srv: Implement USB Audio Modes
              SWAM CR: MK06110953626

VERSION     : 007.005  NONDRAFT  18-Oct-2006 Anton Nevala
REASON      : Change request
REFERENCE   : 010-27765 Audio server: Production Test Loops for Nokia AV for UPP
              SWAM CR: AN06102056604
              SWAM CR: AN06101758966

VERSION     : 007.004  NONDRAFT  26-Sep-2006 Jaakko Rautiainen
REASON      : Change request
REFERENCE   : 010-25757: AUD Srv: AIC33 Test Loops
              SWAM CR: JR06092049285

VERSION     : 007.003  NONDRAFT  12-Sep-2006 Anton Nevala
REASON      : Change request
REFERENCE   : 010-28296: Audio Srv: Improve Radio quality for UPP product with Nokia AV - Interface changes
              009-25301: Audio srv: Support for line-out- Interface change
              SWAM CR: AN06090761597

VERSION     : 007.002  NONDRAFT  11-Aug-2006 Jani Pellikka
REASON      : Change request
REFERENCE   : 010-27326: Audio srv: All FTD data should be included in ISA server macro
              SWAM CR: JP06081433480

VERSION     : 007.001  NONDRAFT  08-Jun-2006 Jani Pellikka
REASON      : Change request
REFERENCE   : 010-24951: Audio srv: New client type for Kodiak POC routing
              010-25755: Aud Srv: AIC Audio Routing - MUSIC&CALL
              SWAM CR: JP06060844679

VERSION     : 007.000  NONDRAFT  22-May-2006 Jani Pellikka
REASON      : Change request
REFERENCE   : 009-26204: Audio server: Align DSP algo switches 1-5 to audio_isi.h
              SWAM CR: JP06052429518

VERSION     : 006.014  NONDRAFT  10-May-2006 Jani Pellikka
REASON      : Change request
REFERENCE   : 009-24096: AUD srv: Separate algorithm & gain tunings for video/voice recording
              010-22402: AUD Srv: Add AUD_MIXER_APE_TONE_AUD_REC
              SWAM CR: AN06050233373

VERSION     : 006.013 NONDRAFT  09-Mar-2006 Anton Nevala
REASON      : Change request
REFERENCE   : 009-24306: AUD srv: Interface change for Improve Volume Control Handling in Size (S40 and S60)
              010-22159: AUD Srv: NOKAV: TTY Support
              SWAM CR: AN06030757429

VERSION     : 006.012 NONDRAFT  03-Mar-2006 Marko Kangasluoma
REASON      : Change request
REFERENCE   : 010-17884: AUD Policy: Application Check In/Out Interface
              SWAM CR: MK06022753147

VERSION     : 006.011a NONDRAFT  16-Dec-2005 Anton Nevala
REFERENCE   : ADDED \ BEFORE NEWLINE WHEN MULTILINE PARAMS USED
              REMOVED INVALID CHARACTER IN COMMENT
              RE-STRUCTURED LONG CONST_TBL_ENTRY COMMENTS (Eliasen Stig)

VERSION     : 006.011 NONDRAFT  12-Dec-2005 Anton Nevala
REFERENCE   : SWAM CR: AN05120942086

VERSION     : 006.010 NONDRAFT  29-Nov-2005 Marko Kangasluoma
REFERENCE   : 010-18029: AUD EAP: Interface for checking availabel EAP effects
              010-17874: AUD EAP: Provide interface for 3D Audio API
              010-18917: AUD Srv: EQU: Interface changes to EQU
              SWAM CR: MK05112246823

VERSION     : 006.009 NONDRAFT  01-Dec-2005 Anton Nevala
REFERENCE   : ou1core#38372 Audio: Anton Nevala: Audio ISI change, 3 new modes, one mixer attr (ISI hdr)
              SWAM CR: AN05120136458, Xmas is coming :)

VERSION     : 006.008 NONDRAFT  14-Nov-2005 Anton Nevala
REFERENCE   : 009-21566: Audio srv: Interface change to audio isi for left/right ihf speaker control
              SWAM CR: AN05110956275

VERSION     : 006.007 NONDRAFT  10-Oct-2005 Mika P. Kangas
REFERENCE   : 009-21520: AUD srv: HS-29 support
              SWAM CR: AN05102044080
DESCRIPTION :

VERSION     : 006.006 NONDRAFT  10-Oct-2005 Mika P. Kangas
REASON      : Change request
REFERENCE   : RM-RIM ID 009-19849 / SWAM CR: MK05092652108
DESCRIPTION : New ECI IF included in audio_isi.h

VERSION     : 006.005 NONDRAFT  23-Sep-2005 Mika P. Kangas
REASON      : Change request
REFERENCE   : RM-RIM ID 009-20921 and 009-18238 / SWAM CR: MK05092652108
DESCRIPTION : New Aud Mode: AUD_MODE_AD15 and Isihdr macro updates
              (Now isihdr can be generated from this macro file)


VERSION     : 006.004 NONDRAFT  15-Sep-2005 Marko Kangasluoma
REASON      : Change request
REFERENCE   : RM-RIM ID 009-19910: AUD EAP: Interface for Playback Rate Control
              RM-RIM ID 009-12778: Gain and Pan Algorithms in EAP mixer
              ActionDB for SWAM MK05083056633: Audio Server: EAP ratecontrol, volumecontrol and pancontrol
DESCRIPTION : New messages: AUD_EAP_EFFECT_INFO_REQ, AUD_EAP_EFFECT_INFO_RESP
              New subblocks: AUD_EAP_INFO_RATECONTROL_REQ_SB, AUD_EAP_INFO_RATECONTROL_RESP_SB,
                             AUD_EAP_CREATE_RATECONTROL_REQ_SB, AUD_EAP_DESTROY_RATECONTROL_REQ_SB,
                             AUD_EAP_CREATE_RATECONTROL_RESP_SB, AUD_EAP_DESTROY_RATECONTROL_RESP_SB,
                             AUD_EAP_CREATE_LEVELCHANGE_REQ_SB, AUD_EAP_CREATE_LEVELCHANGE_RESP_SB,
                             AUD_EAP_CREATE_PANCHANGE_REQ_SB, AUD_EAP_CREATE_PANCHANGE_RESP_SB
              New constants: AUD_EAP_CHANNEL_LEFT, AUD_EAP_CHANNEL_RIGHT

VERSION     : 006.003 NONDRAFT  31-Aug-2005 Anton Nevala
REASON      : Change request
REFERENCE   : RM-RIM ID 009-19829: AUD Srv: NOKAV: Audio Routing for Basic Headset
              RM-RIM ID 009-20722: AUD Srv: New audio loop from XMIC to HAC for Kowloon HAC testing
              RM-RIM ID 010-14271: AUD Srv: Digital stereo mic audio routing for production testings
              ActionDB for SWAM AN05083058267: Audio Server: 3 new modes, 2 new test types
DESCRIPTION : Audio modes: AUD_MODE_AV_STEREO_HD, AUD_MODE_AV_STEREO_HD_HP_MIC, AUD_MODE_AV_GENERIC
              Test modes: AUD_TEST_EXT_IN_HAC_OUT, AUD_TEST_STEREO_DIG_IN_EXT_OUT

VERSION     : 006.002 NONDRAFT  15-Aug-2005 Anton Nevala
REASON      : Change request
REFERENCE   : RM-RIM ID 010-12407: TV Out audio mode and audio routing policy in ISA (S60)
              ActionDB for SWAM AN05080947503
DESCRIPTION : New audio mode AUD_MODE_TVOUT

VERSION     : 006.001 NONDRAFT  12-Apr-2005 Mika P. Kangas
REASON      : Change request
REFERENCE   : RM-RIM ID 009-13420: AUD Srv: PHAP MCU based solution
              RM_RIM ID 010-11634: AUD Srv: Test Loops for Line-in recording (AIC33)
              ADB SWAM CR MK05050241185 Audio Server: 2 new modes
DESCRIPTION : 2 New audio modes AUD_MODE_PHAP_HP and AUD_MODE_PHAP_SLIDE_OPEN added. Test types
              AUD_TEST_AIC33_LINEIN_LEFT_HP_OUT and AUD_TEST_AIC33_LINEIN_RIGHT_HP_OUT added
              for audio test loops

VERSION     : 006.000 NONDRAFT  28-Apr-2005 Marko Kangasluoma
REASON      : Change request
REFERENCE   : RM-RIM ID 009-17978: EAP Timestamp and Pause/Resume Interface
              ADB SWAM CR MK05041955966 Audio Server: EAP time and pause interface
DESCRIPTION : Subblocks AUD_EAP_STREAM_TIME_REQ_SB, AUD_EAP_STREAM_TIME_RESP_SB, AUD_EAP_STREAM_PAUSE_REQ_SB and
              AUD_EAP_STREAM_PAUSE_RESP_SB added. Subblock AUD_EAP_STREAM_CLOSE_RESP_SB changed.
              Message AUD_EAP_BUFFER_EMPTY_NTF added

VERSION     : 005.028 NONDRAFT  07-Apr-2005 Jaakko Rautiainen
REASON      : Change request
REFERENCE   : RM-RIM ID 010-8866: AUD Server: New modes for Line-In and wing connector
                        010-8876: AUD Srv: New Client Type for UI clients
                        010-8875: AUD Srv: New mode for Line-in recording and AIC33 control for it
                        010-8871: AUD Srv: New audio mode for FM Radio recording
              ADB SWAM CR JR05040539062 Audio Server: 5 new modes, 1 new client type
DESCRIPTION : New modes: AUD_MODE_EXT_MIC, AUD_MODE_UNIV_STEREO
              AUD_MODE_UNIV_STEREO_EXT_MIC, AUD_MODE_LINE_IN_REC, AUD_MODE_FM_RADIO_REC
              New client type: AUD_UI_2_CLIENT_TYPE

VERSION     : 005.027 NONDRAFT  01-Apr-2005 Mika P. Kangas
REASON      : Change request
REFERENCE   : RM-RIM ID 009-17465: AUD Srv: Audio routing for S60 3.0
              ADB SWAM CR MK05031647456
DESCRIPTION : New messages defined AUD_ATTACH_ACCESSORY_EVENT_REQ and
              AUD_ATTACH_ACCESSORY_EVENT_OK_RESP.

VERSION     : 005.026 NONDRAFT  07-Feb-2005 Marko Kangasluoma
REASON      : Change request
REFERENCE   : RM-RIM ID 009-12779 "EAP mixer for audio capture"
                        010-10846 "EAP mixer interface to VRR SIND(RAP) for speech data"
                        009-16350 "AUD policy: stereo widening algorithm"
              ADB SWAM CR MK05013157091 Audio Server: EAP capture and effect interface change
DESCRIPTION : Added Messages AUD_EAP_BUFFER_OVERFLOW_NTF, AUD_EAP_EFFECT_CREATE_REQ, AUD_EAP_EFFECT_CREATE_RESP
                             AUD_EAP_EFFECT_DESTROY_REQ, AUD_EAP_EFFECT_DESTROY_RESP
              Added Sub blocks AUD_EAP_STREAM_CAPTURE_REQ_SB, AUD_EAP_STREAM_CAPTURE_RESP_SB,
                               AUD_EAP_CREATE_STEREO_WIDENING_REQ_SB, AUD_EAP_CREATE_STEREO_WIDENING_RESP_SB,
                               AUD_EAP_DESTROY_STEREO_WIDENING_REQ_SB, AUD_EAP_DESTROY_STEREO_WIDENING_RESP_SB,
                               AUD_EAP_STREAM_CAPTURE_REQ_SB, AUD_EAP_STREAM_CAPTURE_RESP_SB
              Added Constant table AUD_EAP_MASTER_STREAM_ID

VERSION     : 005.025 NONDRAFT  17-Jan-2005 Anton Nevala
REASON      : Change request
REFERENCE   : RM-RIM ID 010-8937: Audio Srv: Interface support for APE AUD REC
              ADB SWAM CR AN05011349117 Audio Server: New value for AUD_MIXER_APP_REC_SELECT Attribute
DESCRIPTION : New value for AUD_MIXER_APP_REC_SELECT attribute. New value is AUD_MIXER_APE_AUD_REC  0x04

VERSION     : 005.024 NONDRAFT  05-Jan-2005 Anton Nevala
REASON      : Change request
REFERENCE   : RM-RIM ID 009-14968: HS-23 for UPP8M audio server changes
              RM-RIM ID 010-9166: SB-8 PESQ-measurement cable (SB-8) support in audio server
              RM-RIM ID 010-8936: Audio Srv: Stereo Microphone Selection
              ADB SWAM CR AN04122334741 Audio Server: 3 new modes, 2 message definition remove
DESCRIPTION : New Audio Modes: AUD_MODE_TEST_CABLE, AUD_MODE_HD_ST_2 and AUD_MODE_STEREO_MIC

VERSION     : 005.023 NONDRAFT  08-Dec-2004 Jaakko Rautiainen
REASON      : Change request
REFERENCE   : RM-RIM ID 009-15584: Separate audio mode for CK-10
              ADB SWAM CR JR04120334038 "Audio server: New audio mode for CK-10, Car Kit 10"
DESCRIPTION : New mode AUD_MODE_CK_10

VERSION     : 005.022   NONDRAFT    29-Oct-2004 Anton Nevala
REASON      : Change request
REFERENCE   : RM-RIM ID 010-8209 "AUD Srv: HAC support interface changes and emergency call"
              ADB SWAM CR AN04102544508 "Audio server: Audio ISI interface changes for HAC"
DESCRIPTION : New messages added:
              AUD_DEFATTR_CHANGE_REQ
              AUD_DEFATTR_CHANGE_RESP
              AUD_DEFATTR_VALUE_GET_REQ
              AUD_DEFATTR_VALUE_GET_RESP

VERSION     : 005.021   NONDRAFT    21-Oct-2004 Marko Kangasluoma
REASON      : Change request
REFERENCE   : RM-RIM ID 009-12775 "EAP mixer interface"
              ADB SWAM CR MK04101543136 "Audio server: EAP interface changes"
DESCRIPTION : EAP messages, subblocks, constants and structures added

VERSION     : 005.020 NONDRAFT  25-Sep-2004 Jaakko Rautiainen
REASON      : Change request
REFERENCE   : RM-RIM ID 009-12920: BTH Streaming - new audio mode for BTH streaming
              and new messages
              ADB SWAM CR JR04092239071 "Audio server: BT streaming changes"
DESCRIPTION : New mode AUD_MODE_BTHSTREAM and new messages AUD_BTHSTREAM_STATUS_CHANGE_REQ and
              AUD_BTHSTREAM_STATUS_CHANGE_RESP

VERSION     : 005.019 NONDRAFT  30-Aug-2004 Anton Nevala
REASON      : Change request
REFERENCE   : RM-RIM ID 009-13202 "HAC (Hearing Aid Compability) support for Accessory and Audio"
              ADB SWAM AN04081952880 "Audio server: New audio mode for HAC"
DESCRIPTION : New mode AUD_MODE_HAC

VERSION     : 005.018 NONDRAFT  14-May-2004 Jaakko Rautiainen
REASON      : Change request
REFERENCE   : RM-RIM ID 010-3660: "AUD: THWK AUDIO Test Box Support"
              ADB SWAM CR JR04051438788 "Audio: THWK Test Box Support"
DESCRIPTION : New mode AUD_MODE_THWK_TEST_BOX.

VERSION     : 005.017   NONDRAFT    15-Mar-2004     Marko Kangasluoma
REASON      : Change request
REFERENCE   : RM-RIM ID 009-7597 "Audio personalization for tiku edge product"
              ADB SWAM MK04022558799 "Audio: New AUDIO_DSP_PARAMS attribute AUD_DSP_PHAP"
              Inspection Minutes: ADB for SWAM MK04031543303
DESCRIPTION : * new attribute AUD_DSP_PHAP
              * number of attributes AUD_NUM_DSP_PARAMS_ATTRIBUTES changed
              * Spare byte taken to use from tISI_AudAttributeLayerReport structure

VERSION     : 005.016   NONDRAFT    03-Feb-2004     Marko Kangasluoma
REASON      : Change request
REFERENCE   : RM-RIM ID 009-7667 "BTH Audio Link Open Interface"
              ADB SWAM MK04012163765 "Audio: New messages AUD_SCO_CONTROL_REQ/RESP"
DESCRIPTION : * new messages AUD_SCO_CONTROL_REQ/RESP
              * structures for AUD_SCO_CONTROL_REQ/RESP

VERSION     : 005.015   NONDRAFT    13-Jan-2004     Ivan Angelov
REASON      : moving to Continuus + SWAM CR
REFERENCE   : PCP Error DB PN03120938898 "Wrong accessory modes with AMR clips and MIDI"
              ADB SWAM MK03121952478 "Audio: New tone out selection:"AUD_MIXER_TONE_OUT_SPEECH"
              Inspection Minutes: ADB for AD IA04011351972
DESCRIPTION : * new value added to AUD_MIXER_TONE_OUT_ATTRIBUTE
              * document location updated

VERSION     : 005.014   NONDRAFT    18-Nov-2003     Marko Kangasluoma
REASON      : Update
REFERENCE   : RM-RIM ID 009-7027 "HF-2 (POC handsfree): Audio server changes"
                        009-7029 "HS-8 (POC headset): Audio server changes"
                        009-4817 "LPS-4 (Inductive loopset) - AuMic mode support"
                        009-4816 "LPS-4 (Inductive loopset) - External audio device support"
              ADB SWAM MK03102753382 "Audio: New audio modes for LPS4 and POC"
DESCRIPTION : Updated to audio_isi.h;005.014

VERSION     : 005.013   NONDRAFT    03-Oct-2003     Anton Nevala
REASON      : Update
REFERENCE   : RM-RIM ID 009-5714 "Universal Headset Jack Support - AUD server changes"
              ADB SWAM AN03092455035 "Audio: New audio modes for UNIV headset"
DESCRIPTION : Updated to audio_isi.h;005.013

VERSION     : 005.012   NONDRAFT    02-Oct-2003     Achim Peters
REASON      : Update
REFERENCE   : RM-RIM ID 009-6665 "Car Radio Mute (CRM) in Echnaton platform"
              ADB SWAM AP03100247505 "New messages AUD_ACI_AUDIO_BLOCK_IN_USE_REQ/-RESP"
DESCRIPTION : Updated to audio_isi.h;005.012

VERSION     : 005.011   NONDRAFT    25-Aug-2003     Achim Peters
REASON      : Update
REFERENCE   : RM-RIM ID 010-2159 "Generic audio mode for AudioBlock accessories"
              ADB SWAM AP03082050065 "Audio: New audio mode - "AUD_MODE_THWK_GENERIC"
DESCRIPTION : Updated to audio_isi.h;005.011

VERSION     : 005.010    DRAFT        10-Jun-2003  Achim Peters
REASON      : Update
REFERENCE   : ADB SWAM AP03061048876 "ISI Audio Server Message Interface Inspection 005.010"
DESCRIPTION : Updated to audio_isi.h;005.010

VERSION     : 005.009    DRAFT        14-May-2003  Achim Peters
REASON      : Update
REFERENCE   : RM-RIM ID 010-1757 "IHF for POC - New audio mode"
              ADB SWAM AP03051445321 "ISI Audio Server Message Interface Inspection"
DESCRIPTION : Updated to audio_isi.h;005.009

VERSION     : 005.008    DRAFT        29-Apr-2003  Achim Peters
REASON      : Update
REFERENCE   : ADB SWAM IA03011733743 "Audio Server Interface Changes for BB5.0"
              ADB SWAM AP03042944672 "ISI Audio Server Message Macro Inspection"
DESCRIPTION : Updated to audio_isi.h;005.008

VERSION     : 005.007    DRAFT        03-Feb-2003  Anton Nevala
REASON      : Update
REFERENCE   : ADB SWAM AN03020357255 "Audio Server Interface inspection"
DESCRIPTION : Updated to audio_isi.h;005.007

VERSION     : 005.006    DRAFT        04-Nov-2002  Achim Peters
REASON      : Update
REFERENCE   : ADB SWAM AP02101036843 "Audio Server Interface - Stereo Audio Control,
              Quality Control and Balanced Volume Control"
DESCRIPTION : Updated to audio_isi.h;005.006

VERSION     : 005.005    DRAFT        24-Sep-2002  Ivan Anguelov
REASON      : Update
REFERENCE   : Inspection:ADB SWAM IA02092451399
DESCRIPTION : Updated to audio_isi.h;005.005

VERSION     : 9          DRAFT        05-Aug-2002  Achim Peters
REASON      : Update & Error correction
REFERENCE   : PCP Error DB JK02080231542 "PMD file generation fails due aud_isi_m.h"
DESCRIPTION : Updated to audio_isi.h;005.004

VERSION     : 8          DRAFT        18-Feb-2002  Achim Peters
REASON      : Update
REFERENCE   : CR : LN ActionDB for TEC, PP02012939132
              IA : LN ActionDB for SWAM, IA02021834223
DESCRIPTION : Updated to audio_isi.h;005.001

VERSION     : 8          DRAFT        18-Feb-2002  Ivan Anguelov
REASON      : Update
REFERENCE   : -
DESCRIPTION : Updated to audio_isi.h;005.000

VERSION     : 7          DRAFT        02-Jul-2001  Christian Jacob Hansen
REASON      : Update
REFERENCE   : -
DESCRIPTION : Updated, so generated header file is as compatible as
              possible with hand-made header file

VERSION     : 6          DRAFT        09-May-2001  Christian Jacob Hansen
REASON      : Updated
REFERENCE   : -
DESCRIPTION : Updated according to i_aud_md.doc v.18 NON-DRAFT 26-Mar-2001

VERSION     : 5          DRAFT        23-Oct-2000  Christian Jacob Hansen
REASON      : Changes in autogeneration tool
REFERENCE   : -
DESCRIPTION : Changes to SEQ_OF, SEQ_OF_REF, and CHOICE_BEGIN
              macros.

VERSION     : 4          DRAFT        19-Oct-2000  Christian Jacob Hansen
REASON      : Changes in autogeneration tool
REFERENCE   : -
DESCRIPTION : Changes to SEQ_OF_REF, STRING_REF, PPC_TBL_REF and
              FTD_TBL_REF macros.

VERSION     : 3          DRAFT        17-Oct-2000  Christian Jacob Hansen
REASON      : Change in autogeneration tool
REFERENCE   : -
DESCRIPTION : Updated the choice structures.

VERSION     : 2          DRAFT        19-Sep-2000  Christian Jacob Hansen
REASON      : Change in autogeneration tool
REFERENCE   : -
DESCRIPTION : The file has been changed according to the changes made to
              the autogeneration tool

VERSION     : 1          DRAFT        25-Feb-2000  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : The file is based on the message description document
              i_aud_md.doc, version 8.0 NON-DRAFT, 24-Feb-99
*/


/* ------------------------------------------------------------------------- */



/*  1    ABSTRACT

    1.1    Module type

    Header file for the ISI Autogeneration Application


    1.2    Functional description

    This file is the message definition file for the Audio Server


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

#include "aud_eci_isi_m.h"
#include "acc_shared_isi_m.h"
#include "aud_pol_isi_m.h"
#include "aud_eap_isi_m.h"
#include "aud_gpa_isi_m.h"

COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#include \"acc_shared_isi.h\"")
COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#include \"audio_eci_isi.h\"")
COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#include \"audio_pol_isi.h\"")
COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#include \"audio_eap_isi.h\"")
COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#include \"audio_gpa_isi.h\"")

/*  3    CONSTANTS */

/* Message ID's */
#define AUD_REGISTER_IN_REQ                 0x00
#define AUD_REGISTER_IN_OK_RESP             0x01
#define AUD_REGISTER_IN_FAIL_RESP           0x02
#define AUD_REGISTER_IN_IND                 0x03
#define AUD_REGISTER_OUT_REQ                0x04
#define AUD_REGISTER_OUT_OK_RESP            0x05
#define AUD_REGISTER_OUT_FAIL_RESP          0x06
#define AUD_REGISTER_OUT_IND                0x07
#define AUD_SERVICES_GET_REQ                0x08
#define AUD_SERVICES_GET_DEFAULT_OK_RESP    0x09
#define AUD_SERVICES_GET_CUSTOM_OK_RESP     0x0A
#define AUD_ATTRIBUTES_GET_REQ              0x0B
#define AUD_ATTRIBUTES_GET_DEFAULT_OK_RESP  0x0C
#define AUD_ATTRIBUTES_GET_CUSTOM_OK_RESP   0x0D
#define AUD_ATTRIBUTES_GET_FAIL_RESP        0x0E
#define AUD_REGISTERED_GET_REQ              0x0F
#define AUD_REGISTERED_GET_OK_RESP          0x10
#define AUD_SETTING_GET_REQ                 0x11
#define AUD_SETTING_GET_OK_RESP             0x12
#define AUD_SETTING_GET_FAIL_RESP           0x13
#define AUD_LAYER_UPDATE_REQ                0x14
#define AUD_LAYER_UPDATE_OK_RESP            0x15
#define AUD_LAYER_UPDATE_FAIL_RESP          0x16
#define AUD_LAYER_UPDATE_IND                0x17
#define AUD_LAYER_UPDATE_NEEDED_IND         0x18
#define AUD_LAYER_DESTROY_REQ               0x19
#define AUD_LAYER_DESTROY_OK_RESP           0x1A
#define AUD_LAYER_DESTROY_FAIL_RESP         0x1B
#define AUD_TEST_START_REQ                  0x1C
#define AUD_TEST_START_OK_RESP              0x1D
#define AUD_TEST_START_FAIL_RESP            0x1E
#define AUD_TEST_STOP_REQ                   0x1F
#define AUD_TEST_STOP_OK_RESP               0x20
#define AUD_TEST_STOP_FAIL_RESP             0x21
#define AUD_HW_STATUS_IND                   0x22

#define AUD_ATTACH_ACCESSORY_EVENT_REQ      0x23
#define AUD_ATTACH_ACCESSORY_EVENT_OK_RESP  0x24
/* 0x25 is taken, look to the bottom of this list*/
#define AUD_S60_VOIP_EMERGENCY_CALL_NTF     0x27
#define AUD_FEATURE_SET_REQ                 0x28
#define AUD_FEATURE_SET_RESP                0x29
#define AUD_SELFTEST_REQ                    0x2A
#define AUD_SELFTEST_RESP                   0x2B
#define AUD_LOOPBACK_REQ                    0x2C
#define AUD_LOOPBACK_RESP                   0x2D
#define AUD_LOOPBACK_GAIN_SET_REQ           0x2E
#define AUD_LOOPBACK_GAIN_SET_RESP          0x2F

#define AUD_EQU_CREATE_REQ                  0x40
#define AUD_EQU_CREATE_OK_RESP              0x41
#define AUD_EQU_CREATE_FAIL_RESP            0x42
#define AUD_EQU_INFO_REQ                    0x43
#define AUD_EQU_INFO_OK_RESP                0x44
#define AUD_EQU_INFO_FAIL_RESP              0x45
#define AUD_EQU_SWITCH_STATE_REQ            0x46
#define AUD_EQU_SWITCH_STATE_OK_RESP        0x47
#define AUD_EQU_SWITCH_STATE_FAIL_RESP      0x48
#define AUD_EQU_SWITCH_STATE_IND            0x49
#define AUD_EQU_ADJUST_REQ                  0x4A
#define AUD_EQU_ADJUST_OK_RESP              0x4B
#define AUD_EQU_ADJUST_FAIL_RESP            0x4C
#define AUD_EQU_DELETE_REQ                  0x4D
#define AUD_EQU_DELETE_OK_RESP              0x4E
#define AUD_EQU_DELETE_FAIL_RESP            0x4F
#define AUD_EQU_ACTIVE_ID_REQ               0x50
#define AUD_EQU_ACTIVE_ID_OK_RESP           0x51
#define AUD_EQU_ACTIVE_ID_FAIL_RESP         0x52

#define AUD_SCO_CONTROL_REQ                 0x59
#define AUD_SCO_CONTROL_RESP                0x5A

#define AUD_BTHSTREAM_STATUS_CHANGE_REQ     0x5B
#define AUD_BTHSTREAM_STATUS_CHANGE_RESP    0x5C

/* default Attribute control messages (HAC) */
#define AUD_DEFATTR_CHANGE_REQ              0x5D
#define AUD_DEFATTR_CHANGE_RESP             0x5E
#define AUD_DEFATTR_VALUE_GET_REQ           0x5F
#define AUD_DEFATTR_VALUE_GET_RESP          0x60

#define AUD_EQU_GENERAL_INFO_REQ            0x61
#define AUD_EQU_GENERAL_INFO_RESP           0x62
#define AUD_EQU_CREATED_IND                 0x63
#define AUD_EQU_DELETED_IND                 0x64
#define AUD_EQU_ADJUSTED_IND                0x65

/* Volume interface messages */
#define AUD_VOLUME_CONTROL_REQ              0x66
#define AUD_VOLUME_CONTROL_RESP             0x67
#define AUD_VOLUME_GET_REQ                  0x68
#define AUD_VOLUME_GET_RESP                 0x69

#define AUD_FIFO_INTERRUPT_IND              0x6A

#define AUD_EANC_STATUS_CHANGE_REQ          0x6B
#define AUD_EANC_STATUS_CHANGE_RESP         0x6C

#define AUD_VOLUME_CONTROL_IND              0x6D
#define AUD_EANC_STATUS_CHANGE_IND          0x6E

#define AUD_EANC_MIC_DATA_REQ               0x6F
#define AUD_EANC_MIC_DATA_RESP              0x70

/* NOTE! */
/* Message IDs from 0x70 to 0x7F are reserved for eci */
/* Message IDs from 0x80 to 0x9F are reserved for EAP */
/* Message IDs from 0xA0 to 0xB1 are reserved for Audio Policy */

/* Sub block IDs */
#define AUD_SERVICE_REPORT                  0
#define AUD_ATTRIBUTE_SETUP_REPORT          1
#define AUD_SETTING_REPORT                  2
#define AUD_LAYER_SETTING                   3
#define AUD_DSP_PARBLOCK                    4
#define AUD_ATTRIBUTE_LAYER_REPORT          5
#define AUD_ATTRIBUTE_UPDATE_REPORT         6
#define AUD_EQU_DEFINITION                  7
#define AUD_EQU_GENERAL_INFO                8

/* Volume control Sub block IDs */
#define AUD_VOLUME_CONTROL_SB               0x09
#define AUD_VOLUME_CONTROL_RESPONSE_SB      0x0A
#define AUD_LOOPBACK_INPUT_GAIN_SB          0x0B
#define AUD_LOOPBACK_OUTPUT_GAIN_SB         0x0C

/* Loopbacks subblock IDs */
#define AUD_LOOPBACK_IN_PARAMS_SB            0x0D
#define AUD_LOOPBACK_OUT_PARAMS_SB           0x0E
#define AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB  0x0F

/*FTD related*/
#define AUD_COMM_FTD_DATA_BYTE              0x01

#define AUD_PAUSE                           0

/* this definition should be changed to CONSTANT_VER
    to version 006.008 this was AUD_ALL_ATTRIBUTES 0x0F
    from version 006.009 this was AUD_ALL_ATTRIBUTES 0x3F */
#define AUD_ALL_ATTRIBUTES                  0x3F

/* FTD constants for internal use */
#define FTD_ACC  0
#define FTD_AD   1
#define FTD_ULI  2
#define FTD_DLO  3
#define FTD_GAIN 4
#define FTD_VOL  5
#define FTD_DPW  6
#define FTD_UPW  7
#define AUD_COMM_FTD_DATA_NUM 8

/* Audio Server FTD DATA "signature" */
#define COMM_FTD_DATA_AUD_BASE       0x01A0

/* Default value for loopback input or output gain; if set,
 * default gain is applied */
#define AUD_LOOPBACK_GAIN_DEFAULT    0x7FFF

/*  4    MACROS */

/* these macros are redefined versions of the COMMON macros defined
   in isi_macros.h. These local versions are needed in order to
   generate a back-ward compatible header file
*/

/* This is used for old message where struc define is old */
#define AUD_COMMON_SB(struct_name) \
    MSG_COMMENT(COMMENT_STRUCT_NAME, #struct_name) \
    REFERENCE(8, BE, SubBlockId, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, SubBlockLength, "Sub Block Length", SB_LENGTH) \
/* This is used for old message where struc define is old */
#define AUD_COMMON_FTD_SB(struct_name) \
    MSG_COMMENT(COMMENT_STRUCT_NAME, #struct_name) \
    REFERENCE(16, BE, subblockID, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, subblock_length, "Sub Block Length", SB_LENGTH) \
/* This is used for new messages where struct name is generated by autogen */
#define AUD_COMMON_SB_NEW \
    REFERENCE(8, BE, SubBlockId, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, SubBlockLength, "Sub Block Length", SB_LENGTH) \


/* This is used for old message where struc define is old */
#define AUD_MSG_HDR(struct_name) \
    MSG_COMMENT(COMMENT_STRUCT_NAME, #struct_name) \
    VALUE(8, BE, TransactionId, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageId, "Message ID", MSG_ID)
/* This is used for new messages where struct name is generated by autogen */
#define AUD_MSG_HDR_NEW \
    VALUE(8, BE, TransactionId, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageId, "Message ID", MSG_ID)

#ifndef AUD_ISI_VERSION
#define AUD_ISI_VERSION
#define AUD_ISI_VERSION_Z   10
#define AUD_ISI_VERSION_Y   2
#endif

/* version history and cover page information */
/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "OULU")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "My Entertainment/ My Audio")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Achim Peters")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIAL")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "ISI AUDIO Server Message Description")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_aud_isi_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou1gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS-ou1gif#browse")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "GIF_SPECS/CoreSW")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

/* ISIHDR properties */
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "ou_pcms#1")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou1gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_interface/ISI/Core")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "audio_isi.h")


COMMENT(COMMENT_ISIHDR_FILENAME, "audio_isi.h")
RES_BEGIN(RESOURCE_ISI, PN_AUDIO, AUD, "Audio Server",
    RES_VERSION_STRING(AUD_ISI_VERSION_Z, AUD_ISI_VERSION_Y), TRUE)


    /* Include shared definitions */
    /* Most propably means that from this version and forever */
    INCLUDE_SHARED_FILE(PN_ACCESSORY, "005.027", "")


    COMMENT(COMMENT_TEXT, "Current version...")
    ISI_VERSION_HISTORY("010.002")

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    /* TODO: Add version history block every time the interface is changed */
    /* Latest version */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JR11061043660")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Jun-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jani Kärkelä")
    COMMENT(COMMENT_TEXT, "010.002 version is used to add Sidetone support with version number 9.14. ")
    COMMENT(COMMENT_TEXT, "This is due to backward compability with 9.2 and 10.4 branches.")
    ISI_VERSION_HISTORY("010.002")
	
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AC11052756663")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "27-May-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Adrian Chirica")
    COMMENT(COMMENT_TEXT, "Fix for duplicate var name which causes error during xml file generation for Coltrane tool")
    ISI_VERSION_HISTORY("010.001")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AC11041159481")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "07-Apr-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Adrian Chirica")
    COMMENT(COMMENT_TEXT, "Audio loopback interface changed to support sub-blocks")
    ISI_VERSION_HISTORY("010.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JR11061043660")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Jun-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jani Kärkelä")
    COMMENT(COMMENT_TEXT, "Support for sidetone switch.")
    ISI_VERSION_HISTORY("009.014")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AN11032440034")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "24-Mar-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, "New tone out select")
    ISI_VERSION_HISTORY("009.013")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JR11011356972")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "11-Jan-2011")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Tuomas Haikarainen")
    COMMENT(COMMENT_TEXT, "Support for uplink noise cancellation switch")
    ISI_VERSION_HISTORY("009.012")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JR10112338329")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "23-Nov-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Ville Laaksonen")
    COMMENT(COMMENT_TEXT, "Layer based ACA algorithm control")
    ISI_VERSION_HISTORY("009.011")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AC10012248779")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "29-Jan-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Adrian Chirica")
    COMMENT(COMMENT_TEXT, "2 new selections added for AUD_MIXER_DL_OUT_SELECT and 1 new for AUD_MIXER_UL_IN_SELECT")
    ISI_VERSION_HISTORY("009.010")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: PS09061651680")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "25-Jun-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Paavo Salonen")
    COMMENT(COMMENT_TEXT, "New loopback interface fine tuning. AUD_LOOPBACK_REQ / RESP and AUD_LOOPBACK_GAIN_SET_REQ / RESP were redone.")
    ISI_VERSION_HISTORY("009.009")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AN09061631439")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "22-Jun-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Seppo Jauho")
    COMMENT(COMMENT_TEXT, "USB TTY audio mode added")
    ISI_VERSION_HISTORY("009.008")
         
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: KA09042739989")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "27-Apr-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Katja Ahonen")
    COMMENT(COMMENT_TEXT, "Gazoo TPA selection")
    ISI_VERSION_HISTORY("009.007")
           
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: PS09032047966")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "03-Apr-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Katja Ahonen")
    COMMENT(COMMENT_TEXT, "Changes to Audio server interface, new messages for MCL")
    ISI_VERSION_HISTORY("009.006")
           
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: NP09031339141")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "31-Mar-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Niina Pussinen")
    COMMENT(COMMENT_TEXT, "MCL fix for Hands Free Voice UI (SCO 417-35747)")
    ISI_VERSION_HISTORY("009.005")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: NP09031339141")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "18-Mar-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Niina Pussinen")
    COMMENT(COMMENT_TEXT, "MCL Hands Free Voice UI (SCO 417-35747)")
    ISI_VERSION_HISTORY("009.004")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: KA09021158148")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Mar-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Katja Ahonen")
    COMMENT(COMMENT_TEXT, "Changes to Audio server interface, new messages and new audio modes (for MCL)")
    ISI_VERSION_HISTORY("009.003")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: SJ09010841712")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "18-Feb-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Seppo Jauho")
    COMMENT(COMMENT_TEXT, "GPA isi intrerface added")
    ISI_VERSION_HISTORY("009.002")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AN08101685298")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "27-Jan-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Katja Ahonen")
    COMMENT(COMMENT_TEXT, "Audio mic testing through uUSB")
    ISI_VERSION_HISTORY("009.001")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: KA09010952478")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Jan-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Katja Ahonen")
    COMMENT(COMMENT_TEXT, "Test loops clean up")
    ISI_VERSION_HISTORY("009.000")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AC08083040574")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "12-Sep-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Adrian Chirica")
    COMMENT(COMMENT_TEXT, "Secondary audio mode introducted to interface")
    ISI_VERSION_HISTORY("008.019")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Bug Fix")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AN08041749576")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-May-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Adrian Chirica")
    COMMENT(COMMENT_TEXT, " Fix for bug introduced with task ou1core#90208")
    ISI_VERSION_HISTORY("008.018")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AC08042449305")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "07-May-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Adrian Chirica, Jaakko Rautiainen ")
    COMMENT(COMMENT_TEXT, " Added 3 new test loops for twin microphones and more EANC messages")
    ISI_VERSION_HISTORY("008.017")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: AN08041749576")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "23-Mar-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Pasi Alatalo")
    COMMENT(COMMENT_TEXT, " Added new interfaces for FM TX test loop")
    ISI_VERSION_HISTORY("008.016")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: EH08033156573")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "31-Mar-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petteri Hyvonen")
    COMMENT(COMMENT_TEXT, " Added DL out selections for I2S left and I2S right")
    ISI_VERSION_HISTORY("008.015")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JR08032051561")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "20-Mar-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jaakko Rautiainen")
    COMMENT(COMMENT_TEXT, " Added EANC state indication")
    ISI_VERSION_HISTORY("008.014")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JR08022051386")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-Feb-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jaakko Rautiainen")
    COMMENT(COMMENT_TEXT, " Added more EANC definitions")
    ISI_VERSION_HISTORY("008.013")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Audio server UPP split.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "414-4504, 403-5694, 403-10649")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Feb-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Janne Ervasti, Rasmus Rahunen, Jani Kärkelä")
    COMMENT(COMMENT_TEXT, " Split of Audio server ISI IF for BB5." )
    COMMENT(COMMENT_TEXT, " New indication AUD_VOLUME_CONTROL_IND and new parameters to AUD_VOLUME_CONTROL_RESPONSE_SB.")
    COMMENT(COMMENT_TEXT, " ISI interface update, POC_HS and POC_BTH modes.")
    ISI_VERSION_HISTORY("008.012")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "SWAM CR: JV08011556803")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-Jan-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Janne Vimpari")
    COMMENT(COMMENT_TEXT, " SWAM CR: JV08011556803: Separate EAP ISI messages from Audio ISI messages")
    ISI_VERSION_HISTORY("008.011")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 403-9345, ADB SWAM JV0801044858")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "04-Jan-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Janne Vimpari")
    COMMENT(COMMENT_TEXT, " Added two messages to support run time trace activation")
    ISI_VERSION_HISTORY("008.010")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 401-5601, ADB SWAM PS07121059105")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "10-Dec-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Paavo Salonen")
    COMMENT(COMMENT_TEXT, " Added new defines for AUD_DSP_ALGORITHMS_5 bitmask.")
    ISI_VERSION_HISTORY("008.009")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 403-9201, ADB SWAM JR07111958783")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "20-Nov-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jaakko Rautiainen")
    COMMENT(COMMENT_TEXT, " Added support for EANC")
    ISI_VERSION_HISTORY("008.008")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 401-5611, ADB SWAM PS07110651102")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Nov-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Paavo Salonen")
    COMMENT(COMMENT_TEXT, " Added new defines for AUD_DSP_ALGORITHMS_4 bitmask.")
    ISI_VERSION_HISTORY("008.007")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 401-5500, ADB SWAM SJ07092554528")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "25-Sep-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Seppo Jauho")
    COMMENT(COMMENT_TEXT, " Added AUD_MODE_FMTX_ONLY and AUD_MODE_FMTX_AND_PHONE ")
    ISI_VERSION_HISTORY("008.006")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 401-5307, RM-RIM 401-5190, ADB SWAM SJ07091242230")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-Sep-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Seppo Jauho")
    COMMENT(COMMENT_TEXT, " Added AUD_MODE_MOBILE_TV and AUD_MIXER_DL_OUT_HAC ")
    ISI_VERSION_HISTORY("008.005")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 402-2988, 010-31685, ADB SWAM MK07080950055")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "09-Aug-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika P. Kangas")
    COMMENT(COMMENT_TEXT, " Add new audio modes for USB Audio ")
    ISI_VERSION_HISTORY("008.004")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 009-30070, ADB SWAM JV07060855686")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "26-Jun-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Janne Vimpari")
    COMMENT(COMMENT_TEXT, " Create ISI interface for Audio Visualization post effect ")
    ISI_VERSION_HISTORY("008.003")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request Add AUD_MODE_AUDIO_REC")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 403-1583, ADB SWAM JV07061359846")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-Jun-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Janne Vimpari")
    COMMENT(COMMENT_TEXT, " Add new audio mode (AUD_MODE_AUDIO_REC) ")
    ISI_VERSION_HISTORY("008.002")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request (FTD data mode changes).")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM 009-28730, ADB SWAM JE07050239685")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "3-May-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Janne Ervasti")
    COMMENT(COMMENT_TEXT, " FTD data mode changes to operator mode. ")
    ISI_VERSION_HISTORY("008.001")
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM AN07032036224")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "12-Mar-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("008.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM MK07031251079")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "12-Mar-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Marko Kangasluoma")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.009")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM AN06121952700")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "20-Dec-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.008")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM MK06112154700")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "22-Nov-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika P. Kangas")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.007")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM MK06110953626")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "10-Nov-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika P. Kangas")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.006")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM AN06101758966, ADB SWAM AN06102056604")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "18-Oct-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.005")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM JR06092049285")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "26-Sep-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jaakko Rautiainen")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.004")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM AN06090761597")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "12-Sep-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.003")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM JP06081433480")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "11-Aug-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jani Pellikka")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM JP06060844679")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "08-Jun-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jani Pellikka")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.001")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM JP06052429518")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "22-May-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jani Pellikka")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("007.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN06050233373")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "10-May-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jani Pellikka")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.014")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN06030757429")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "09-Mar-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.013")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK06022753147")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "03-Mar-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Marko Kangasluoma")
    COMMENT(COMMENT_TEXT, "Audio policy interface added to separate file")
    ISI_VERSION_HISTORY("006.012")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN05120942086")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "12-Dec-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.011")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK05112246823")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "12-Dec-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Marko Kangasluoma")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.010")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN05120136458")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "01-Dec-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.009")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN05110956275")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Nov-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.008")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN05102044080")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "20-Oct-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.007")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK05092652108")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "10-Oct-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika P. Kangas")
    COMMENT(COMMENT_TEXT, "Included the new ECI IF ")
    ISI_VERSION_HISTORY("006.006")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK05092652108")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "23-Sep-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika P. Kangas")
    COMMENT(COMMENT_TEXT, "ISIHDR generation enabled, after this macrofile version ")
    COMMENT(COMMENT_TEXT, "isihdr will be generated by the autogen macro")
    ISI_VERSION_HISTORY("006.005")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK05083056633")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-Sep-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Marko Kangasluoma")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.004")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN05083058267")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "31-Aug-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.003")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN05080947503")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-Aug-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK05050241185")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "12-Apr-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika P. Kangas")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.001")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK05041955966 Audio Server: EAP time and pause interface\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "28-Apr-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Marko Kangasluoma")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("006.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR JR05040539062 \"Audio Server: 5 new modes, 1 new client type\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "08-Apr-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jaakko Rautiainen")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("005.028")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK05031647456")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "01-Apr-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika P. Kangas")
    COMMENT(COMMENT_TEXT, "New audio isi messages: AUD_ATTACH_ACCESSORY_EVENT_REQ and AUD_ATTACH_ACCESSORY_EVENT_OK_RESP")
    ISI_VERSION_HISTORY("005.027")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK05013157091 \"Audio Server: EAP capture and effect interface change\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "07-Feb-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Marko Kangasluoma")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("005.026")

    /* 005.025 */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN05011349117 \"Audio Server: New value for AUD_MIXER_APP_REC_SELECT Attribute\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Jan-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, " ")
    ISI_VERSION_HISTORY("005.025")

    /* 005.024 */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN04122334741 \"Audio Server: 3 new modes, 2 message definition remove\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "05-Jan-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, "New Audio Modes: AUD_MODE_TEST_CABLE, AUD_MODE_HD_ST_2 and AUD_MODE_STEREO_MIC")
    ISI_VERSION_HISTORY("005.024")
    /* 005.023 */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR JR04120334038 \"Audio server: New audio mode for CK-10, Car Kit 10\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "08-Dec-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jaakko Rautiainen")
    COMMENT(COMMENT_TEXT, "New mode AUD_MODE_CK_10")
    ISI_VERSION_HISTORY("005.023")
    /* 005.022 */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR AN04102544508 \"Audio server: Audio ISI interface changes for HAC\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "29-Oct-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Anton Nevala")
    COMMENT(COMMENT_TEXT, "Default attribute setting messages currently for HAC")
    ISI_VERSION_HISTORY("005.022")
    /* 005.021 */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR MK04101543136 \"Audio server: EAP interface changes\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "21-Oct-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Marko Kangasluoma")
    COMMENT(COMMENT_TEXT, "EAP messages, subblocks, constants and structures added")
    ISI_VERSION_HISTORY("005.021")
    /* 005.020 */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change request")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ADB SWAM CR JR04092239071 \"Audio server: BT streaming changes\"")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON-DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "25-Sep-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jaakko Rautiainen")
    COMMENT(COMMENT_TEXT, "New mode AUD_MODE_BTHSTREAM and new messages")
    ISI_VERSION_HISTORY("005.020")

    /* TODO - add references in next update !!! */
/* end of version history */

/* Some extra defines */
CONSTANT(AUD_NUM_MESSAGE_TYPES, 0x70+1)
CONSTANT(AUD_COMM_MESSAGE_TYPES, 0x0B)
CONSTANT(AUD_NUM_MAX_CLIENTS, 32)
CONSTANT(AUD_NUM_LOOPBACK_INPUTS, 0x08)
CONSTANT(AUD_NUM_LOOPBACK_OUTPUTS, 0x06)

    CONST_TBL_BEGIN(AUD_MODE_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_MODE_HP,                    0x00, "Handportable")
        CONST_TBL_ENTRY(AUD_MODE_HDC5,                  0x01, "Headset HDC5")
        CONST_TBL_ENTRY(AUD_MODE_HDC9,                  0x02, "Headset HDC9, to be removed")
        CONST_TBL_ENTRY(AUD_MODE_LPS1,                  0x03, "Loopset LPS1, to be removed")
        CONST_TBL_ENTRY(AUD_MODE_LPS3,                  0x04, "Loopset LPS3")
        CONST_TBL_ENTRY(AUD_MODE_PPHF,                  0x05, "Plug & Play handsfree")
        CONST_TBL_ENTRY(AUD_MODE_PPHF_EXT_MIC,          0x06, "Plug & Play handsfree with external mic")
        CONST_TBL_ENTRY(AUD_MODE_CAR_HFU2,              0x07, "Car kit HFU2, to be removed")
        CONST_TBL_ENTRY(AUD_MODE_CAR_HFU2_HS,           0x08, "Car kit HFU2 with handset off-hooked, to be removed")
        CONST_TBL_ENTRY(AUD_MODE_ANCO_HP,               0x09, "Handportable with ANCO codec")
        CONST_TBL_ENTRY(AUD_MODE_ANCO_ANC,              0x0A, "Handportable with ANCO codec, ANC ON")
        CONST_TBL_ENTRY(AUD_MODE_ANCO_IHF,              0x0B, "Handportable with ANCO codec, IHF ON")
        CONST_TBL_ENTRY(AUD_MODE_SMART_ACCESSORY,       0x0C, "Smart accessory contains audio resources")
        CONST_TBL_ENTRY(AUD_MODE_IHF,                   0x0D, "Integrated handsfree mode")
        CONST_TBL_ENTRY(AUD_MODE_MSTI,                  0x0E, "MSTI test mode")
        CONST_TBL_ENTRY(AUD_MODE_FM_RADIO,              0x0F, "FM Radio audio mode")
        CONST_TBL_ENTRY(AUD_MODE_TEST,                  0x10, "Test mode for production line")
        CONST_TBL_ENTRY(AUD_MODE_TTY,                   0x11, "TTY/TDD accessory device")
        CONST_TBL_ENTRY(AUD_MODE_HP_SLIDE_OPEN,         0x12, "HP with Slide/grip opened")
        CONST_TBL_ENTRY(AUD_MODE_ACTIVE_COVER,          0x13, "HP with Active Cover ON")
        CONST_TBL_ENTRY(AUD_MODE_FM_RADIO_OVER_IHF,     0x14, "FM Radio over IHF")
        CONST_TBL_ENTRY(AUD_MODE_THWK_HD_MO,            0x15, "TOMAHAWK: Mono Headset")
        CONST_TBL_ENTRY(AUD_MODE_THWK_HD_ST,            0x16, "TOMAHAWK: Stereo Headset")
        CONST_TBL_ENTRY(AUD_MODE_THWK_LPS,              0x17, "TOMAHAWK: Loopset")
        CONST_TBL_ENTRY(AUD_MODE_THWK_BHF,              0x18, "TOMAHAWK: Basic Handsfree")
        CONST_TBL_ENTRY(AUD_MODE_THWK_HFU,              0x19, "TOMAHAWK: Advanced Handsfree")
        CONST_TBL_ENTRY(AUD_MODE_THWK_EXT_HS,           0x1A, "TOMAHAWK: Advanced Handsfree with external mic")
        CONST_TBL_ENTRY(AUD_MODE_THWK_HF_ST,            0x1B, "TOMAHAWK: Music Deskstand(Office Stereo)")
        CONST_TBL_ENTRY(AUD_MODE_POC,                   0x1C, "Push Over Cellular")
        CONST_TBL_ENTRY(AUD_MODE_THWK_GENERIC,          0x1D, "TOMAHAWK: Generic accessory with ACI audio block")
        CONST_TBL_ENTRY(AUD_MODE_UNIV_HEADSET,          0x1E, "Universal headset")
        CONST_TBL_ENTRY(AUD_MODE_UNIV_TTY,              0x1F, "TTY using Universal HD plug")
        CONST_TBL_ENTRY(AUD_MODE_UNIV_FM_RADIO,         0x20, "FM radio using universal headset")
        CONST_TBL_ENTRY(AUD_MODE_POC_HD,                0x21, "Tomahawk headset HS-8")
        CONST_TBL_ENTRY(AUD_MODE_POC_HF,                0x22, "Tomahawk carkit HF-2")
        CONST_TBL_ENTRY(AUD_MODE_LPS_AUMIC,             0x23, "Loopset auxiliary mic")
        CONST_TBL_ENTRY(AUD_MODE_LPS_EXT_IN,            0x24, "Loopset External input")
        CONST_TBL_ENTRY(AUD_MODE_THWK_TEST_BOX,         0x25, "Tomahawk test box")
        CONST_TBL_ENTRY(AUD_MODE_HAC,                   0x26, "Hearing Aid Compability")
        CONST_TBL_ENTRY(AUD_MODE_BTHSTREAM,             0x27, "Bluetooth streaming")
        CONST_TBL_ENTRY(AUD_MODE_CK_10,                 0x28, "Car kit CK-10")
        CONST_TBL_ENTRY(AUD_MODE_TEST_CABLE,            0x29, "Audio Test Cable SB-8")
        CONST_TBL_ENTRY(AUD_MODE_HD_ST_2,               0x2A, "HS-23")
        CONST_TBL_ENTRY(AUD_MODE_STEREO_MIC,            0x2B, "Stereo mic mode")
        COMMENT(COMMENT_TEXT,               "External mic mode")
        CONST_TBL_ENTRY_VER(AUD_MODE_EXT_MIC,           0x2C, "005.028", "")
        COMMENT(COMMENT_TEXT,               "Universal stereo headset")
        CONST_TBL_ENTRY_VER(AUD_MODE_UNIV_STEREO,       0x2D, "005.028", "")
        COMMENT(COMMENT_TEXT,               "Universal stereo headset with external mic")
        CONST_TBL_ENTRY_VER(AUD_MODE_UNIV_STEREO_EXT_MIC, 0x2E, "005.028", "")
        COMMENT(COMMENT_TEXT,               "Line-in recording mode")
        CONST_TBL_ENTRY_VER(AUD_MODE_LINE_IN_REC,       0x2F, "005.028", "")
        COMMENT(COMMENT_TEXT,               "FM Radio recording mode")
        CONST_TBL_ENTRY_VER(AUD_MODE_FM_RADIO_REC,      0x30, "005.028", "")
        COMMENT(COMMENT_TEXT,               "PHAP mode for HP")
        CONST_TBL_ENTRY_VER(AUD_MODE_PHAP_HP,           0x31, "006.001", "")
        COMMENT(COMMENT_TEXT,               "PHAP mode for slide feature")
        CONST_TBL_ENTRY_VER(AUD_MODE_PHAP_HP_SLIDE_OPEN, 0x32, "006.001", "")
        COMMENT(COMMENT_TEXT,               "TV-OUT mode")
        CONST_TBL_ENTRY_VER(AUD_MODE_TVOUT,             0x33, "006.002", "")
        COMMENT(COMMENT_TEXT,               "Nokia AV stereo Headset with microphone")
        CONST_TBL_ENTRY_VER(AUD_MODE_AV_STEREO_HD,      0x34, "006.003", "")
        COMMENT(COMMENT_TEXT,               "Nokia AV stereo Headset, no microphone in headset")
        CONST_TBL_ENTRY_VER(AUD_MODE_AV_STEREO_HD_HP_MIC, 0x35, "006.003", "")
        COMMENT(COMMENT_TEXT,               "Nokia AV Generic audio mode for Audio block accesories")
        CONST_TBL_ENTRY_VER(AUD_MODE_AV_GENERIC,        0x36, "006.003", "")
        COMMENT(COMMENT_TEXT,               "AD-15i")
        CONST_TBL_ENTRY_VER(AUD_MODE_AD15,              0x37, "006.005", "")
        /* NOTE! This is old version of HS20 and HS29 Aud mode definition where definition is in wrong order */
        COMMENT(COMMENT_TEXT,               "HS-29")
        CONST_TBL_ENTRY_VER(AUD_MODE_HS29,              0x38, "006.007", "006.011")
        COMMENT(COMMENT_TEXT,               "HS-20")
        CONST_TBL_ENTRY_VER(AUD_MODE_HS20,              0x39, "006.007", "006.011")
        /* NOTE! This is new version of HS20 and HS29 where define values are correct */
        COMMENT(COMMENT_TEXT,               "HS-20")
        CONST_TBL_ENTRY_VER(AUD_MODE_HS20,              0x38, "006.011", "")
        COMMENT(COMMENT_TEXT,               "HS-29")
        CONST_TBL_ENTRY_VER(AUD_MODE_HS29,              0x39, "006.011", "")
        /* normal lide continues */
        COMMENT(COMMENT_TEXT,               "Stereo Car HF")
        CONST_TBL_ENTRY_VER(AUD_MODE_STEREO_CAR_HF,     0x3A, "006.009", "")
        COMMENT(COMMENT_TEXT,               "Nokia AV Basic HF")
        CONST_TBL_ENTRY_VER(AUD_MODE_AV_BASIC_HF,       0x3B, "006.009", "")
        COMMENT(COMMENT_TEXT,               "Nokia AV External mic")
        CONST_TBL_ENTRY_VER(AUD_MODE_AV_EXT_MIC,        0x3C, "006.009", "")
        COMMENT(COMMENT_TEXT,               "Nokia AV TTY device")
        CONST_TBL_ENTRY_VER(AUD_MODE_AV_TTY,        0x3D, "006.013", "")
        COMMENT(COMMENT_TEXT,               "Speech recording mode")
        CONST_TBL_ENTRY_VER(AUD_MODE_SPEECH_REC,    0x3E, "006.014", "")
        COMMENT(COMMENT_TEXT,               "Video recording mode")
        CONST_TBL_ENTRY_VER(AUD_MODE_VIDEO_REC,     0x3F, "006.014", "")
        COMMENT(COMMENT_TEXT,               "HIFI headset")
        CONST_TBL_ENTRY_VER(AUD_MODE_THWK_HIFI_HD,     0x40, "007.001", "")
        COMMENT(COMMENT_TEXT,               "HS-27R Stereo Radio Headset")
        CONST_TBL_ENTRY_VER(AUD_MODE_THWK_RADIO_HD,     0x41, "007.001", "")
        COMMENT(COMMENT_TEXT,               "Line out")
        CONST_TBL_ENTRY_VER(AUD_MODE_LINE_OUT,     0x42, "007.003", "")
        COMMENT(COMMENT_TEXT,               "USB Audio Headset")
        CONST_TBL_ENTRY_VER(AUD_MODE_USB_HD,       0x43, "007.006", "")
        COMMENT(COMMENT_TEXT,               "USB Audio Car HF")
        CONST_TBL_ENTRY_VER(AUD_MODE_USB_CAR_HF,   0x44, "007.006", "")
        COMMENT(COMMENT_TEXT,               "Audio recording mode")
        CONST_TBL_ENTRY_VER(AUD_MODE_AUDIO_REC,   0x45, "008.002", "")
        COMMENT(COMMENT_TEXT,               "FM Radio USB Headset")
        CONST_TBL_ENTRY_VER(AUD_MODE_FM_RADIO_USB,       0x46, "008.004", "")
        COMMENT(COMMENT_TEXT,               "USB headphones")
        CONST_TBL_ENTRY_VER(AUD_MODE_USB_HD_HP_MIC,       0x47, "008.004", "")
        COMMENT(COMMENT_TEXT,               "USB external mic")
        CONST_TBL_ENTRY_VER(AUD_MODE_USB_EXT_MIC,       0x48, "008.004", "")
        COMMENT(COMMENT_TEXT,               "Mobile TV")
        CONST_TBL_ENTRY_VER(AUD_MODE_MOBILE_TV,         0x49, "008.005", "")
        COMMENT(COMMENT_TEXT,               "FM Radio TX")
        CONST_TBL_ENTRY_VER(AUD_MODE_FMTX_ONLY ,        0x4a, "008.006", "")
        COMMENT(COMMENT_TEXT,               "FM Radio TX and Phone")
        CONST_TBL_ENTRY_VER(AUD_MODE_FMTX_AND_PHONE,    0x4b, "008.006", "")
        COMMENT(COMMENT_TEXT,               "PoC HS(HS-9) accessory mode for Kodiak")
        CONST_TBL_ENTRY_VER(AUD_MODE_POC_HS,            0x4c, "008.012", "")
        COMMENT(COMMENT_TEXT,               "PoC BTH(BT headsets) accessory mode for Kodiak")
        CONST_TBL_ENTRY_VER(AUD_MODE_POC_BTH,           0x4d, "008.012", "")
        COMMENT(COMMENT_TEXT,               "HP with Slide/grip short opened")
        CONST_TBL_ENTRY_VER(AUD_MODE_HP_SLIDE_SHORT_OPEN, 0x4E, "009.003", "")
        COMMENT(COMMENT_TEXT,               "USB tty device")
        CONST_TBL_ENTRY_VER(AUD_MODE_USB_TTY,           0x4F, "009.008", "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x2B+1, "", "005.028")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x30+1, "005.028", "006.001")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x32+1, "006.001", "006.002")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x33+1, "006.002", "006.003")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x36+1, "006.003", "006.005")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x37+1, "006.005", "006.007")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x39+1, "006.007", "006.009")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x3C+1, "006.009", "006.013")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x3D+1, "006.013", "006.014")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x3F+1, "006.014", "007.001")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x41+1, "007.001", "007.003")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x42+1, "007.003", "007.006")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x44+1, "007.006", "008.002")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x45+1, "008.002", "008.004")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x48+1, "008.004", "008.005")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x49+1, "008.005", "008.006")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x4b+1, "008.006", "008.012")    
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x4d+1, "008.012", "009.003")    
    CONSTANT_VER(AUD_NUM_ACC_MODES, 1+0x4e, "009.003", "009.008")
    CONSTANT_VER(AUD_NUM_ACC_MODES, 0x4f+1, "009.008", "")    

    CONST_TBL_BEGIN(AUD_MODE_ANA_DIGI, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_MODE_DIGITAL,               0x00,
                        "Logical digital volume level, valid values 0-9")
        CONST_TBL_ENTRY(AUD_MODE_ANALOG,                0x01,
                        "Absolute digital volume level which will be send to DSP")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_CELL_MODES, 0x01+1, "", "")


    /* Constant tables */


    /* ------------------------------------------------------------------ */
    /* AUD_SERVICES */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_SERVICES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_ANALOG_IN,                    0x00, "Microphones")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT,                   0x01, "Speakers")
        CONST_TBL_ENTRY(AUD_DSP_PARAMS,                   0x02, "DSP enhancement algorithms")
        CONST_TBL_ENTRY(AUD_DTMF,                         0x03, "DTMF generation")
        CONST_TBL_ENTRY(AUD_TONE,                         0x04, "Tone generation")
        CONST_TBL_ENTRY(AUD_MIXER,                        0x05, "Audio routing")
        CONST_TBL_ENTRY(AUD_MODE,                         0x06, "Audio mode")
        CONST_TBL_ENTRY(AUD_DIGITAL_OUT,                  0x07, "Digital Volume Level")
        CONST_TBL_ENTRY(AUD_MUTE,                         0x08, "Mute")
        CONST_TBL_ENTRY(AUD_ALL_SERVICES,                 0x09, "")
    CONST_TBL_END

    /*COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define AUD_ALL_SERVICES AUD_NUM_SERVICES")*/
    CONSTANT_VER(AUD_NUM_SERVICES, 0x09, "", "")

    DER_CONST_TBL_BEGIN(AUD_SERVICES, AUD_SERVICES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_ANALOG_IN)
        DER_CONST_TBL_ENTRY(AUD_ANALOG_OUT)
        DER_CONST_TBL_ENTRY(AUD_DSP_PARAMS)
        DER_CONST_TBL_ENTRY(AUD_DTMF)
        DER_CONST_TBL_ENTRY(AUD_TONE)
        DER_CONST_TBL_ENTRY(AUD_MIXER)
        DER_CONST_TBL_ENTRY(AUD_MODE)
        DER_CONST_TBL_ENTRY(AUD_DIGITAL_OUT)
        DER_CONST_TBL_ENTRY(AUD_MUTE)
    DER_CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* AUD_ANALOG_IN_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_ANALOG_IN_ATTRIBUTES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_ANALOG_IN_GAIN_LEVEL,         0x00,
                        "Logical microphone gain level, valid values 0-9")
        CONST_TBL_ENTRY(AUD_ANALOG_IN_GAIN_ABS_VALUE,     0x01,
                        "Absolute value in audio codec's MIC gain register")
        CONST_TBL_ENTRY(AUD_ANALOG_IN_SIDETONE,           0x02,
                        "Sidetone, valid values 0-2")
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,               AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_ANALOG_IN_ATTRIBUTES, 0x02+1, "", "")
    CONSTANT_VER(AUD_NUM_ANALOG_IN_VOLUME_LEVELS, 10, "", "")

    DER_CONST_TBL_BEGIN(AUD_ANALOG_IN_ATTRIBUTES, AUD_ANALOG_IN_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_ANALOG_IN_GAIN_LEVEL)
        DER_CONST_TBL_ENTRY(AUD_ANALOG_IN_GAIN_ABS_VALUE)
        DER_CONST_TBL_ENTRY(AUD_ANALOG_IN_SIDETONE)
    DER_CONST_TBL_END

    /* ------------------------------------------------------------------ */
    /* AUD_ANALOG_OUT_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_ANALOG_OUT_ATTRIBUTES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_LEVEL,         0x00,
                        "Logical volume level, valid values 0-9")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_ABS_VALUE,     0x01,
                        "Absolute value in audio codec's EAR gain register")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE,       0x02,
                        "Balanced volume level in percents")
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,               AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_ANALOG_OUT_ATTRIBUTES, 0x02+1, "", "")
    CONSTANT_VER(AUD_NUM_ANALOG_OUT_VOLUME_LEVELS, 10, "", "")

    DER_CONST_TBL_BEGIN(AUD_ANALOG_OUT_ATTRIBUTES, AUD_ANALOG_OUT_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_LEVEL)
        DER_CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_ABS_VALUE)
        DER_CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE)
    DER_CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* AUD_DSP_PARAMS_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_DSP_PARAMS_ATTRIBUTES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_DSP_PARAM_BLOCK,              0x00,
                        "Adjustment parameter block (size 2-128 bytes) "
                        "for enhancement algorithms run by DSP. "
                        "Audio server doesn't understand the contents of the block")
        CONST_TBL_ENTRY(AUD_DSP_ALGORITHMS_1,             0x01,
                        "Basic audio enhancement algorithms to be run by DSP")
        CONST_TBL_ENTRY(AUD_DSP_ALGORITHMS_2,             0x02,
                        "Additional enhancement algorithms to be run by DSP")
        CONST_TBL_ENTRY(AUD_DSP_PHAP,                     0x03,
                        "Adjustable PHAP settings( 0x00 - 0x04 )")
        COMMENT(COMMENT_TEXT,               "Additional enhancement algorithms to be run by DSP")
        CONST_TBL_ENTRY_VER(AUD_DSP_ALGORITHMS_3,     0x04, "007.000", "")
        COMMENT(COMMENT_TEXT,               "Additional enhancement algorithms to be run by DSP")
        CONST_TBL_ENTRY_VER(AUD_DSP_ALGORITHMS_4,     0x05, "007.000", "")
        COMMENT(COMMENT_TEXT,               "Additional enhancement algorithms to be run by DSP")
        CONST_TBL_ENTRY_VER(AUD_DSP_ALGORITHMS_5,     0x06, "007.000", "")
        COMMENT(COMMENT_TEXT,               "ACA algorithm switches")
        CONST_TBL_ENTRY_VER(AUD_DSP_ACA_ALGORITHMS,   0x07, "009.011", "")
        COMMENT(COMMENT_TEXT,               "ACA control bitmask to signal which switches are controlled by the client.")
        CONST_TBL_ENTRY_VER(AUD_DSP_ACA_ALGORITHMS_MASK,  0x08, "009.011", "")
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,               AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_DSP_PARAMS_ATTRIBUTES, 0x03+1, "", "007.000")
    CONSTANT_VER(AUD_NUM_DSP_PARAMS_ATTRIBUTES, 0x06+1, "007.000", "009.011")
    CONSTANT_VER(AUD_NUM_DSP_PARAMS_ATTRIBUTES, 0x08+1, "009.011", "")

    DER_CONST_TBL_BEGIN(AUD_DSP_PARAMS_ATTRIBUTES, AUD_DSP_PARAMS_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_DSP_PARAM_BLOCK)
        DER_CONST_TBL_ENTRY(AUD_DSP_ALGORITHMS_1)
        DER_CONST_TBL_ENTRY(AUD_DSP_ALGORITHMS_2)
        DER_CONST_TBL_ENTRY(AUD_DSP_PHAP)
        DER_CONST_TBL_ENTRY_VER(AUD_DSP_ALGORITHMS_3, "007.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_DSP_ALGORITHMS_4, "007.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_DSP_ALGORITHMS_5, "007.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_DSP_ACA_ALGORITHMS,      "009.011", "")
        DER_CONST_TBL_ENTRY_VER(AUD_DSP_ACA_ALGORITHMS_MASK, "009.011", "")
    DER_CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* AUD_DTMF_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_DTMF_ATTRIBUTES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_DTMF_SWITCH,                  0x00, "DTMF generation start/stop switch")
        COMMENT(COMMENT_TEXT, "Digit information for producing the tone.")
        COMMENT(COMMENT_TEXT, "Valid values are 0 and ASCII values of 0, 1, _, 9, #, *, A, B, C, D")
        CONST_TBL_ENTRY(AUD_DTMF_DIGIT,                   0x01, "")
        COMMENT(COMMENT_TEXT, "Volume level of the tone, valid values are 0-10. ")
        COMMENT(COMMENT_TEXT, "NOTE: Value 0 means a pause, it advices audio server not perform unnecessary power-off-on sequence for audio circuits between tones")
        CONST_TBL_ENTRY(AUD_DTMF_VOLUME_LEVEL,            0x02, "")
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,               AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_DTMF_ATTRIBUTES, 0x02+1, "", "")
    CONSTANT_VER(AUD_NUM_DTMF_VOLUME_LEVELS, 10, "", "")

    DER_CONST_TBL_BEGIN(AUD_DTMF_ATTRIBUTES, AUD_DTMF_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_DTMF_SWITCH)
        DER_CONST_TBL_ENTRY(AUD_DTMF_DIGIT)
        DER_CONST_TBL_ENTRY(AUD_DTMF_VOLUME_LEVEL)
    DER_CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* AUD_TONE_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_TONE_ATTRIBUTES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_TONE_SWITCH_1,                0x00,
                        "Tone generation start/stop switch for channel 1, "
                        "available values AUD_SWITCH_ON/_OFF")
        CONST_TBL_ENTRY(AUD_TONE_FREQUENCY_1,             0x01,
                        "Frequency for the tone channel 1. "
                        "Available values 0-65535. "
                        "NOTE: The required accuracy for tone frequencies "
                        "isn't known at the moment")
        CONST_TBL_ENTRY(AUD_TONE_VOLUME_LEVEL_1,          0x02,
                        "Volume level for the tone channel 1. Valid values "
                        "are 0-10. NOTE: Value 0 means a pause, it advices "
                        "audio server not perform unnecessary power-off-on "
                        "sequence for audio circuits between tones")
        CONST_TBL_ENTRY(AUD_TONE_SWITCH_2,                0x03,
                        "Ref AUD_TONE_SWITCH_1")
        CONST_TBL_ENTRY(AUD_TONE_FREQUENCY_2,             0x04,
                        "Frequency for the tone channel 2. Available values 0-65535")
        CONST_TBL_ENTRY(AUD_TONE_VOLUME_LEVEL_2,          0x05,
                        "Volume level for the tone channel 2,  ref AUD_TONE_VOLUME_LEVEL_1")
        CONST_TBL_ENTRY(AUD_TONE_SWITCH_3,                0x06,
                        "Ref AUD_TONE_SWITCH_1")
        CONST_TBL_ENTRY(AUD_TONE_FREQUENCY_3,             0x07,
                        "Frequency for the tone channel 3. Available values 0-65535")
        CONST_TBL_ENTRY(AUD_TONE_VOLUME_LEVEL_3,          0x08,
                        "Volume level for the tone channel 3, ref AUD_TONE_VOLUME_LEVEL_1")
        CONST_TBL_ENTRY(AUD_TONE_SWITCH_4,                0x09,
                        "Ref AUD_TONE_SWITCH_1")
        CONST_TBL_ENTRY(AUD_TONE_FREQUENCY_4,             0x0a,
                        "Frequency for the tone channel 4. Available values 0-65535")
        CONST_TBL_ENTRY(AUD_TONE_VOLUME_LEVEL_4,          0x0b,
                        "Volume level for the tone channel 4, ref AUD_TONE_VOLUME_LEVEL_1")
        CONST_TBL_ENTRY(AUD_TONE_SEQUENCE_TYPE,           0x0c,
                        "Type of the tone sequence to which the requested "
                        "tone type belongs to. On the basis of this value "
                        "audio server is able to make decisions concerning "
                        "tone routing for smart accessories")
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,               AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_TONE_ATTRIBUTES, 0x0c+1, "", "")
    CONSTANT_VER(AUD_NUM_TONE_VOLUME_LEVELS, 10, "", "")

    DER_CONST_TBL_BEGIN(AUD_TONE_ATTRIBUTES, AUD_TONE_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_TONE_SWITCH_1)
        DER_CONST_TBL_ENTRY(AUD_TONE_FREQUENCY_1)
        DER_CONST_TBL_ENTRY(AUD_TONE_VOLUME_LEVEL_1)
        DER_CONST_TBL_ENTRY(AUD_TONE_SWITCH_2)
        DER_CONST_TBL_ENTRY(AUD_TONE_FREQUENCY_2)
        DER_CONST_TBL_ENTRY(AUD_TONE_VOLUME_LEVEL_2)
        DER_CONST_TBL_ENTRY(AUD_TONE_SWITCH_3)
        DER_CONST_TBL_ENTRY(AUD_TONE_FREQUENCY_3)
        DER_CONST_TBL_ENTRY(AUD_TONE_VOLUME_LEVEL_3)
        DER_CONST_TBL_ENTRY(AUD_TONE_SWITCH_4)
        DER_CONST_TBL_ENTRY(AUD_TONE_FREQUENCY_4)
        DER_CONST_TBL_ENTRY(AUD_TONE_VOLUME_LEVEL_4)
        DER_CONST_TBL_ENTRY(AUD_TONE_SEQUENCE_TYPE)
    DER_CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* AUD_MIXER_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_MIXER_ATTRIBUTES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_MIXER_UL_POWER_SWITCH,        0x00,
                        "Audio uplink path physical power switch, available values AUD_SWITCH_ON / _OFF")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_SELECT,           0x01,
                        "Audio uplink path physical input selection")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_SWITCH,           0x02,
                        "Audio uplink path input logical mute switch, available values AUD_SWITCH_ON / _OFF")
        CONST_TBL_ENTRY(AUD_MIXER_UL_OUT_SWITCH,          0x03,
                        "Audio uplink path output logical mute switch")
        CONST_TBL_ENTRY(AUD_MIXER_DTMF_OUT_SELECT,        0x04,
                        "DTMF generation physical output device selection")
        CONST_TBL_ENTRY(AUD_MIXER_TONE_OUT_SELECT,        0x05,
                        "Tone generation physical output device selection")
        CONST_TBL_ENTRY(AUD_MIXER_DL_POWER_SWITCH,        0x06,
                        "Audio downlink path physical power switch")
        CONST_TBL_ENTRY(AUD_MIXER_DL_IN_SWITCH,           0x07,
                        "Audio downlink path input logical mute switch")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_SWITCH,          0x08,
                        "Audio downlink path input logical mute switch")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_SELECT,          0x09,
                        "Audio downlink path physical output selection")
        CONST_TBL_ENTRY(AUD_MIXER_MODE_OUT_SELECT,        0x0A,
                        "Audio mixer mode output selection, available values: AUD_MIXER_MODE_OUT_STEREO / _MONO")
        CONST_TBL_ENTRY(AUD_MIXER_QUALITY_SELECT,         0x0B,
                        "Audio quality mode output selection")
        CONST_TBL_ENTRY(AUD_MIXER_APP_IN_SELECT,          0x0C,
                        "Audio application input selection")
        CONST_TBL_ENTRY(AUD_MIXER_APP_UL_SELECT,          0x0D,
                        "Audio application uplink path input selection")
        CONST_TBL_ENTRY(AUD_MIXER_APP_REC_SELECT,         0x0E,
                        "Audio application  recording input selection")
        COMMENT(COMMENT_TEXT, "Audio FM transmitter out selection")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_TRANSMIT_SELECT, 0x0F, "006.009", "")
        COMMENT(COMMENT_TEXT, "Audio DAC33 Playback Mode selection")
        CONST_TBL_ENTRY_VER(AUD_MIXER_PLAYBACK_MODE_SELECT, 0x10, "007.007", "")
        COMMENT(COMMENT_TEXT, "APE Speech tone switch, enables tone mixing to APE Speech rec. Predefined gain value is send to DSP when switch is ON (AUD_SWITCH_ON / _OFF)")
        CONST_TBL_ENTRY_VER(AUD_MIXER_APE_SPEECH_TONE_SWITCH, 0x11, "008.000", "")
        COMMENT(COMMENT_TEXT, "Sidetone path mute switch. Available values: AUD_SWITCH_ON / _OFF.")
        CONST_TBL_ENTRY_VER(AUD_MIXER_SIDETONE_SWITCH, 0x12, "009.014", "")
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,               AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES")
    CONSTANT_VER(AUD_NUM_MIXER_ATTRIBUTES, 1+0x0E, "", "006.009")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES")
    CONSTANT_VER(AUD_NUM_MIXER_ATTRIBUTES, 1+0x0F, "006.009", "007.007")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES")
    CONSTANT_VER(AUD_NUM_MIXER_ATTRIBUTES, 1+0x10, "007.007", "008.000")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES")
    CONSTANT_VER(AUD_NUM_MIXER_ATTRIBUTES, 1+0x11, "008.000", "009.014")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define AUD_NUM_MAX_ATTRIBUTES AUD_NUM_MIXER_ATTRIBUTES")
    CONSTANT_VER(AUD_NUM_MIXER_ATTRIBUTES, 1+0x12, "009.014", "")
    
    DER_CONST_TBL_BEGIN(AUD_MIXER_ATTRIBUTES, AUD_MIXER_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_MIXER_UL_POWER_SWITCH)
        DER_CONST_TBL_ENTRY(AUD_MIXER_UL_IN_SELECT)
        DER_CONST_TBL_ENTRY(AUD_MIXER_UL_IN_SWITCH)
        DER_CONST_TBL_ENTRY(AUD_MIXER_UL_OUT_SWITCH)
        DER_CONST_TBL_ENTRY(AUD_MIXER_DTMF_OUT_SELECT)
        DER_CONST_TBL_ENTRY(AUD_MIXER_TONE_OUT_SELECT)
        DER_CONST_TBL_ENTRY(AUD_MIXER_DL_POWER_SWITCH)
        DER_CONST_TBL_ENTRY(AUD_MIXER_DL_IN_SWITCH)
        DER_CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_SWITCH)
        DER_CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_SELECT)
        DER_CONST_TBL_ENTRY(AUD_MIXER_MODE_OUT_SELECT)
        DER_CONST_TBL_ENTRY(AUD_MIXER_QUALITY_SELECT)
        DER_CONST_TBL_ENTRY(AUD_MIXER_APP_IN_SELECT)
        DER_CONST_TBL_ENTRY(AUD_MIXER_APP_UL_SELECT)
        DER_CONST_TBL_ENTRY(AUD_MIXER_APP_REC_SELECT)
        DER_CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_TRANSMIT_SELECT, "006.009", "")
        DER_CONST_TBL_ENTRY_VER(AUD_MIXER_PLAYBACK_MODE_SELECT, "007.007", "")
        DER_CONST_TBL_ENTRY_VER(AUD_MIXER_APE_SPEECH_TONE_SWITCH, "008.000", "")
        DER_CONST_TBL_ENTRY_VER(AUD_MIXER_SIDETONE_SWITCH, "009.014", "")
    DER_CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* AUD_MODE_ATTRIBUTES */
    /* ------------------------------------------------------------------ */
    CONST_TBL_BEGIN(AUD_MODE_ATTRIBUTES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_MODE_ANA_DIGI,                0x00,
                        "Sets the operation mode in case the server is running "
                        "in a dual-mode phone")
        CONST_TBL_ENTRY(AUD_MODE_ACCESSORY,               0x01,
                        "Tells the accessory mode that audio server is currently "
                        "using. NOTE:This attribute is mainly updated internally "
                        "by audio server (according the accessory information "
                        "provided by ACC server & smart accessories). However, UI "
                        "client can also update this attribute concerning ANC and "
                        "IHF modes when ANCO chip is used")
        COMMENT(COMMENT_TEXT, "Secondary audio mode, this enables the possibility to have "
                        "2 audio modes in parallel in Audio Server. For example, this "
                        "is used for FM Radio recording use case, where "
                        "AUD_MODE_FM_RADIO_REC is added as secondary to already existing "
                        "primary mode. "
                        "The only supported value at the moment is AUD_MODE_FM_RADIO_REC. ")
        CONST_TBL_ENTRY_VER(AUD_MODE_SECONDARY,               0x02, "008.019", "")
 
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,               AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_MODE_ATTRIBUTES, 0x01+1, "", "008.019")
    CONSTANT_VER(AUD_NUM_MODE_ATTRIBUTES, 0x01+2, "008.019", "")

    DER_CONST_TBL_BEGIN(AUD_MODE_ATTRIBUTES, AUD_MODE_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_MODE_ANA_DIGI)
        DER_CONST_TBL_ENTRY(AUD_MODE_ACCESSORY)
        DER_CONST_TBL_ENTRY_VER(AUD_MODE_SECONDARY, "008.019", "")
    DER_CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* AUD_DIGITAL_OUT_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    COMMENT(COMMENT_PARAGRAPH,
            "AUD_DIGITAL_OUT_VOL_LEVEL and AUD_DIGITAL_OUT_SPEECH_GAIN_LOG "
            "are using the same hex value 0x00, to be backward compatible.")

    CONST_TBL_BEGIN(AUD_DIGITAL_OUT_ATTRIBUTES_ALL, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_DIGITAL_OUT_SPEECH_GAIN_LOG, 0x00,
                        "Logical digital volume level for speech (former AUD_DIGITAL_OUT_VOL_LEVEL)")
        CONST_TBL_ENTRY(AUD_DIGITAL_OUT_ABS_VALUE,       0x01,
                        "Absolute digital volume level")
        CONST_TBL_ENTRY(AUD_DIGITAL_OUT_AUDIO_GAIN_LOG,  0x02,
                        "Logical digital volume level for music playback")
        CONST_TBL_ENTRY(AUD_DIGITAL_OUT_CMTDL_GAIN_LOG,  0x03,
                        "Logical digital volume level for CMT DL")
        CONST_TBL_ENTRY(AUD_DIGITAL_OUT_CMTUL_GAIN_LOG,  0x04,
                        "Logical digital volume level for CMT UL")
        CONST_TBL_ENTRY(AUD_DIGITAL_OUT_REC_GAIN_LOG,    0x05,
                        "Logical digital volume level for recording")
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,             AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    CONSTANT_VER(AUD_DIGITAL_OUT_VOL_LEVEL, 0x00, "", "")
    CONSTANT_VER(AUD_NUM_DIGITAL_OUT_ATTRIBUTES, 0x05+1, "", "")
    CONSTANT_VER(AUD_NUM_DIGITAL_OUT_VOLUME_LEVELS, 10, "", "")

    DER_CONST_TBL_BEGIN(AUD_DIGITAL_OUT_ATTRIBUTES, AUD_DIGITAL_OUT_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_DIGITAL_OUT_SPEECH_GAIN_LOG)
        DER_CONST_TBL_ENTRY(AUD_DIGITAL_OUT_ABS_VALUE)
        DER_CONST_TBL_ENTRY(AUD_DIGITAL_OUT_AUDIO_GAIN_LOG)
        DER_CONST_TBL_ENTRY(AUD_DIGITAL_OUT_CMTDL_GAIN_LOG)
        DER_CONST_TBL_ENTRY(AUD_DIGITAL_OUT_CMTUL_GAIN_LOG)
        DER_CONST_TBL_ENTRY(AUD_DIGITAL_OUT_REC_GAIN_LOG)
    DER_CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* AUD_MUTE_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_MUTE_ATTRIBUTES_ALL, 8, BE, "", "")

        CONST_TBL_ENTRY(AUD_ANA_MUTE_SWITCH,                0x00,
                        "Analog mute, values AUD_SWITCH_ON (mute on)/ AUD_SWITCH_OFF (mute off)")
        CONST_TBL_ENTRY(AUD_DIGI_MUTE_SWITCH,               0x01,
                        "Digital mute, values AUD_SWITCH_ON (mute on)/ AUD_SWITCH_OFF (mute off)")
        CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES,             AUD_ALL_ATTRIBUTES, "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_AUD_MUTE_ATTRIBUTES, 2+1, "", "")

    DER_CONST_TBL_BEGIN(AUD_MUTE_ATTRIBUTES, AUD_MUTE_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_ANA_MUTE_SWITCH)
        DER_CONST_TBL_ENTRY(AUD_DIGI_MUTE_SWITCH)
    DER_CONST_TBL_END

    /* ------------------------------------------------------------------ */
    /* AUD_ALL_ATTRIBUTES */
    /* ------------------------------------------------------------------ */

    DER_CONST_TBL_BEGIN(AUD_ALL_ATTRIBUTES_ALL, AUD_MUTE_ATTRIBUTES_ALL, "", "")
        DER_CONST_TBL_ENTRY(AUD_ALL_ATTRIBUTES)
    DER_CONST_TBL_END

    /* ------------------------------------------------------------------ */
    /* equalizer feature related symbols */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_EQU_FAILURE_REASON, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EQU_ID_ERROR,                 0x00,
                        "Operation is not possible for this equalizer id")
        CONST_TBL_ENTRY(AUD_EQU_GAIN_ERROR,               0x01,
                        "Error in gain for equalizer bands")
        CONST_TBL_ENTRY(AUD_EQU_LIMIT_FREQ_ERROR,         0x02,
                        "Error in frequency limits in equalizer bands")
        CONST_TBL_ENTRY(AUD_EQU_BAND_NUM_ERROR,           0x03,
                        "Invalid number of bands. Valid number of bands are from 2 to 8")
        CONST_TBL_ENTRY(AUD_EQU_INVALID_ID,               0x04,
                        "Invalid equalizer Id or equalizer Id not found")
    CONST_TBL_END


    CONST_TBL_BEGIN(AUD_EQU_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EQU_PRESET,                   0x00,
                        "Preset equalizer")
        CONST_TBL_ENTRY(AUD_EQU_GRAPHICAL,                0x01,
                        "Graphical equalizer")
        CONST_TBL_ENTRY(AUD_EQU_TONE_CONTROL,             0x02,
                        "2 bands equalizer, self adjustable")
        CONST_TBL_ENTRY(AUD_EQU_OTHER_ADJUSTABLE,         0x03,
                        "Other type, adjustable")
        CONST_TBL_ENTRY(AUD_EQU_OTHER_NON_ADJUSTABLE,     0x04,
                        "Other type, non-adjustable")
    CONST_TBL_END


    CONST_TBL_BEGIN(AUD_EQU_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_EQU_OFF,                      0x00,
                        "Deactivate equalizer")
        CONST_TBL_ENTRY(AUD_EQU_ON,                       0x01,
                        "Activate equalizer")
    CONST_TBL_END
    
    
    /* ------------------------------------------------------------------ */
    /* Bluetooth Audio SCO related symbols                                */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_SCO_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_SCO_OFF,    0x00,
                        "Bluetooth Audio SCO OFF")
        CONST_TBL_ENTRY(AUD_SCO_ON,     0x01,
                        "Bluetooth Audio SCO ON")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_SCO_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_SCO_OK,     0x00,
                        "Bluetooth Audio SCO OK")
        CONST_TBL_ENTRY(AUD_SCO_FAIL,   0x01,
                        "Bluetooth Audio SCO FAIL")
    CONST_TBL_END


    /* ------------------------------------------------------------------ */
    /* Bluetooth streaming related symbols                                */
    /* ------------------------------------------------------------------ */

    CONST_TBL_BEGIN(AUD_AVDTP_COMMAND, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_AVDTP_CONFIGURE,    0x00,
                        "Configure codec")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_AVDTP_STREAM_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_AVDTP_SBC_IN_USE,     0x00,
                        "SBC codec in use")
        CONST_TBL_ENTRY(AUD_AVDTP_SBC_NOT_IN_USE,   0x01,
                        "SBC codec not in use")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_AVDTP_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_AVDTP_OK,     0x00,
                        "Ok")
        CONST_TBL_ENTRY(AUD_AVDTP_FAIL,   0x01,
                        "Failed")
    CONST_TBL_END

    /* ------------------------------------------------------------------ */
    /* Default Attribute control related symbols                          */
    /* ------------------------------------------------------------------ */
    CONST_TBL_BEGIN(AUD_DEFATTR_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_DEFATTR_OK,                     0x00,
                        "Ok")
        CONST_TBL_ENTRY(AUD_DEFATTR_FAIL,                   0x01,
                        "Failed")
        CONST_TBL_ENTRY(AUD_DEFATTR_FAIL_INVALID_SERVICE,   0x02,
                        "Failed, Invalid service")
        CONST_TBL_ENTRY(AUD_DEFATTR_FAIL_INVALID_ATTR_ID,   0x03,
                        "Failed, Invalid Attribute ID")
        CONST_TBL_ENTRY(AUD_DEFATTR_FAIL_INVALID_VALUE,     0x04,
                        "Failed, Invalid value")
    CONST_TBL_END

    /* ------------------------------------------------------------------ */
    /* Volume control related symbols                                     */
    /* ------------------------------------------------------------------ */
    CONST_TBL_BEGIN(AUD_VOLUME_CONTROL_TYPE, 8, BE, "006.013", "")
        COMMENT(COMMENT_TEXT, "Volume control is using % value")
        CONST_TBL_ENTRY_VER(AUD_VOLUME_PERCENT_CONTROL, 0x01, "006.013", "")

        COMMENT(COMMENT_TEXT, "Volume control is using Q8.7 value")
        CONST_TBL_ENTRY_VER(AUD_VOLUME_Q87_CONTROL,     0x02, "006.013", "")
    CONST_TBL_END

    BIT_TBL_BEGIN(AUD_VOLUME_MEDIA_TYPE, 16, BE, "006.013", "")
        COMMENT(COMMENT_TEXT, "Call volume")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxxx1", AUD_CALL_VOLUME, "006.013", "")

        COMMENT(COMMENT_TEXT, "Speech playback volume, example AMR NB")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxx1x", AUD_SPEECH_PLAYBACK_VOLUME, "006.013", "")

        COMMENT(COMMENT_TEXT, "Media playeback volume, example MP3, MIDI, AAC")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxx1xx", AUD_MEDIA_PLAYBACK_VOLUME, "006.013", "")

        COMMENT(COMMENT_TEXT, "Tradiotional tone volume, example key tones, NRT ringtones")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxx1xxx", AUD_TRADITIONAL_TONE_VOLUME, "006.013", "")

        COMMENT(COMMENT_TEXT, "FM radio volume")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxx1xxxx", AUD_FM_RADIO_VOLUME, "006.013", "")

        COMMENT(COMMENT_TEXT, "DTMF tone volume")
        BIT_TBL_ENTRY_VER("xxxxxxxxxx1xxxxx", AUD_DTMF_TONE_VOLUME, "006.013", "")
    BIT_TBL_END

    /* ------------------------------------------------------------------ */
    /* EANC related symbols                                               */
    /* ------------------------------------------------------------------ */
    CONST_TBL_BEGIN(AUD_EANC_STATE, 8, BE, "008.008", "")
        CONST_TBL_ENTRY(AUD_EANC_OFF,    0x00, "AIC3254 EANC OFF")
        CONST_TBL_ENTRY(AUD_EANC_ON,     0x01, "AIC3254 EANC ON")
    CONST_TBL_END

    /* ------------------------------------------------------------------ */
    /* Miscellanous constant tables */
    /* ------------------------------------------------------------------ */

    COMMENT(COMMENT_TEXT,
           "NOTE: Also tone generation methods may differ between "
           "above mentioned types. Some accessories are able to "
           "download whole ringing tone sequencies from the phone. "
           "In this case producing \"RING\" sequencies need only "
           "'start sequence' and 'stop sequence' commands by audio "
           "server. Alert tones are always generated note by note")
    CONST_TBL_BEGIN(AUD_TONE_SEQUENCE_TYPE, 8, BE,"", "")

        CONST_TBL_ENTRY(AUD_TONE_SEQUENCE_RING,           0x00,
                        "Normal ringing tone generation: tones are routed to "
                        "all accessories")
        CONST_TBL_ENTRY(AUD_TONE_SEQUENCE_RING_SCAN,      0x01,
                       "User scans available ringing tones, thus starting tone "
                        "generation: tones are routed only the primary audio "
                        "target accessory")
        CONST_TBL_ENTRY(AUD_TONE_SEQUENCE_ALERT,          0x02,
                        "Alert tones: tones are routed to all accessories")
        CONST_TBL_ENTRY(AUD_TONE_SEQUENCE_KEY,            0x03,
                        "Non-DTMF Key tones - e.g. soft keys, arrow keys, etc")
        COMMENT(COMMENT_TEXT, "Playback is routed to primary accessory. "
                              "In case of no accessory connected, audio is routed "
                              "to IHF speaker. "
                              "Special functionality: if audio is routed to accessory "
                              "and accessory is disconnected. Audio is not automatically "
                              "routed to IHF. Instead Audio playback is muted")
        CONST_TBL_ENTRY_VER(AUD_TONE_SEQUENCE_MUSIC_PLAY,  0x04, "007.008", "")
    CONST_TBL_END


    CONST_TBL_BEGIN(AUD_ANALOG_OUT_VOL_BALANCE, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L0,    0x00,
                        "Left earline is muted")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L1,    0x01,
                        "10% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L2,    0x02,
                        "20% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L3,    0x03,
                        "30% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L4,    0x04,
                        "40% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L5,    0x05,
                        "50% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L6,    0x06,
                        "60% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L7,    0x07,
                        "70% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L8,    0x08,
                        "80% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L9,    0x09,
                        "90% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_L10,   0x0A,
                        "100% volume on left earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R0,    0x10,
                        "Right earline is muted")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R1,    0x11,
                        "10% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R2,    0x12,
                        "20% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R3,    0x13,
                        "30% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R4,    0x14,
                        "40% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R5,    0x15,
                        "50% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R6,    0x16,
                        "60% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R7,    0x17,
                        "70% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R8,    0x18,
                        "80% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R9,    0x19,
                        "90% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_R10,   0x1A,
                        "100% volume on right earline")
        CONST_TBL_ENTRY(AUD_ANALOG_OUT_VOL_BALANCE_C,     0x20,
                        "100% volume left and right")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_MIXER_UL_IN_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_MUTED,            0x00,
                        "Audio input set muted")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_HD_MIC,           0x01,
                        "HD microphone selected")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_HF_MIC,           0x02,
                        "HF microphone selected")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_HP_MIC,           0x03,
                        "HP microphone selected")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_FM_MIC,           0x04,
                        "FM radio input line selected")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_BT,               0x05,
                        "BT microphone selected")
        CONST_TBL_ENTRY(AUD_MIXER_UL_IN_DIGI,             0x06,
                        "DIGITAL microphone selected")
        COMMENT(COMMENT_TEXT, "Active cover microphone selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_FCI,     0x07, "006.014", "")
        COMMENT(COMMENT_TEXT, "I2S microphone selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_I2S,     0x08, "006.014", "")
        COMMENT(COMMENT_TEXT, "Digital stereo microphone selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_DIGI_STEREO,  0x09, "006.014", "")
        COMMENT(COMMENT_TEXT, "MIC3 with +20db (FM mic)")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_EXT_MIC,  0x0A, "007.003", "")
        COMMENT(COMMENT_TEXT, "USB Microphone")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_USB_MIC,  0x0B, "007.007", "")
        COMMENT(COMMENT_TEXT, "Eanc microphone 1 selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_EANC_MIC1,     0x0C, "009.003", "")
        COMMENT(COMMENT_TEXT, "Eanc microphone 2 selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_EANC_MIC2,     0x0D, "009.003", "")
        COMMENT(COMMENT_TEXT, "Both eanc microphones selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_EANC_BOTH_MICS,     0x0E, "009.003", "")
        COMMENT(COMMENT_TEXT, "Wide-Band BT microphone selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_UL_IN_BT_WB, 0x0F, "009.010", "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_MIXER_UL_IN_ATTRIBUTES, 0x06+1, "", "006.014")
    CONSTANT_VER(AUD_NUM_MIXER_UL_IN_ATTRIBUTES, 0x09+1, "006.014", "007.003")
    CONSTANT_VER(AUD_NUM_MIXER_UL_IN_ATTRIBUTES, 0x0A+1, "007.003", "007.007")
    CONSTANT_VER(AUD_NUM_MIXER_UL_IN_ATTRIBUTES, 0x0B+1, "007.007", "009.003")
    CONSTANT_VER(AUD_NUM_MIXER_UL_IN_ATTRIBUTES, 0x0F, "009.003", "009.010")
    CONSTANT_VER(AUD_NUM_MIXER_UL_IN_ATTRIBUTES, 0x0F+1, "009.010", "")
    
    CONST_TBL_BEGIN(AUD_LOOPBACK_OUT_SELECT, 8, BE, "009.009", "")
        CONST_TBL_ENTRY(AUD_LOOPBACK_OFF,                     0x00, "Audio output muted")
        CONST_TBL_ENTRY(AUD_LOOPBACK_OUT_HP,                  0x01, "Audio output in HP ear")
        CONST_TBL_ENTRY(AUD_LOOPBACK_OUT_IHF,                 0x02, "Audio output in IHF")
        CONST_TBL_ENTRY(AUD_LOOPBACK_OUT_AV,                  0x03, "Audio output in AV")
        CONST_TBL_ENTRY(AUD_LOOPBACK_OUT_USB,                 0x04, "Audio output in USB")
        CONST_TBL_ENTRY(AUD_LOOPBACK_OUT_HAC,                 0x05, "Audio output in HAC")
        COMMENT(COMMENT_TEXT, "Audio output in FM TX")
        CONST_TBL_ENTRY_VER(AUD_LOOPBACK_OUT_FM_TX,           0x06, "010.000", "")
        COMMENT(COMMENT_TEXT, "Audio input in Signal analysis")
        CONST_TBL_ENTRY_VER(AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS, 0x07, "010.000", "")
    CONST_TBL_END
    
    CONST_TBL_BEGIN(AUD_LOOPBACK_IN_SELECT, 8, BE, "009.009", "")
        CONST_TBL_ENTRY(AUD_LOOPBACK_OFF,                   0x00, "Audio input muted")
        CONST_TBL_ENTRY(AUD_LOOPBACK_IN_HP_MIC,             0x01, "Audio input in HP mic")
        CONST_TBL_ENTRY(AUD_LOOPBACK_IN_HP_MIC2,            0x02, "Audio input in HP mic2")
        CONST_TBL_ENTRY(AUD_LOOPBACK_IN_AV_MIC,             0x03, "Audio input in AV mic")
        CONST_TBL_ENTRY(AUD_LOOPBACK_IN_FM_MIC,             0x04, "Audio input in FM mic")
        CONST_TBL_ENTRY(AUD_LOOPBACK_IN_USB_MIC,            0x05, "Audio input in USB mic")
        CONST_TBL_ENTRY(AUD_LOOPBACK_IN_EANC_MIC1,          0x06, "Audio input in EANC mic1")
        CONST_TBL_ENTRY(AUD_LOOPBACK_IN_EANC_MIC2,          0x07, "Audio input in EANC mic2")
        COMMENT(COMMENT_TEXT, "Audio input in Tone generator")
        CONST_TBL_ENTRY_VER(AUD_LOOPBACK_IN_TONE_GENERATOR, 0x08, "010.000", "")
    CONST_TBL_END
    
    CONST_TBL_BEGIN(AUD_MIXER_DL_OUT_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_MUTED,           0x00,
                        "Audio output set muted")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_HP_EAR,          0x01,
                        "HP speaker selected")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_HD_EAR,          0x02,
                        "HD speaker selected")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_HF_EAR,          0x03,
                        "HF speaker selected")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_X_EAR,           0x04,
                        "XEAR speaker selected ")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_STEREO_HD_EAR,   0x05,
                        "HD stereo speakers selected ")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_STEREO_HF_EAR,   0x06,
                        "HF stereo speakers selected ")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_IHFSP,           0x07,
                        "IHF speaker selected ")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_BT_EAR,          0x08,
                        "BT speaker selected ")
        COMMENT(COMMENT_TEXT, "Stereo IHF speaker, IHF speaker not connected to IHFSp")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_IHF,     0x09, "006.008", "")
        COMMENT(COMMENT_TEXT, "Left IHF speaker, IHF speaker not connected to IHFSpL")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_IHF_LEFT, 0x0A, "006.008", "")
        COMMENT(COMMENT_TEXT, "Right IHF speaker, IHF speaker not connected to IHFSpR")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_IHF_RIGHT, 0x0B, "006.008", "")
        COMMENT(COMMENT_TEXT, "Nokia AV bottom connector ear selection (amplifier)")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_EAR_AMP, 0x0C, "006.013", "")
        COMMENT(COMMENT_TEXT, "I2S ear selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EAR_I2S, 0x0D, "007.001", "")
        COMMENT(COMMENT_TEXT, "Nokia AV bottom connector ear selection (amplifier), left")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_EAR_AMP_L, 0x0E, "007.004", "")
        COMMENT(COMMENT_TEXT, "Nokia AV bottom connector ear selection (amplifier), right")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_EAR_AMP_R, 0x0F, "007.004", "")

        COMMENT(COMMENT_TEXT, "Stereo or dual mono ear with Acodec HFBias control (for e.g. AD-15)")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS, 0x10, "007.005", "")

        COMMENT(COMMENT_TEXT, "L channel ear with Acodec HFBias control (for e.g. AD-15)")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS_L, 0x11, "007.005", "")

        COMMENT(COMMENT_TEXT, "R channel ear with Acodec HFBias control (for e.g. AD-15)")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EXT_EAR_HFBIAS_R, 0x12, "007.005", "")

        COMMENT(COMMENT_TEXT, "Stereo or dual mono ear for FMTX")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_FMTX, 0x13, "007.007", "")

        COMMENT(COMMENT_TEXT, "Left Channel ear for FMTX")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_FMTX_L, 0x14, "007.007", "")

        COMMENT(COMMENT_TEXT, "Right Channel ear for FMTX")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_FMTX_R, 0x15, "007.007", "")

        COMMENT(COMMENT_TEXT, "Stereo or dual mono ear for USB Audio")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_USB, 0x16, "007.007", "")

        COMMENT(COMMENT_TEXT, "Left Channel ear for USB Audio")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_USB_L, 0x17, "007.007", "")

        COMMENT(COMMENT_TEXT, "Right Channel ear for USB Audio")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_USB_R, 0x18, "007.007", "")

        COMMENT(COMMENT_TEXT, "Left Channel ear for HD Speaker")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_HD_EAR_L, 0x19, "007.007", "")

        COMMENT(COMMENT_TEXT, "Right Channel ear for HD Speaker")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_HD_EAR_R, 0x1A, "007.007", "")

        COMMENT(COMMENT_TEXT, "HAC selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_HAC, 0x1B, "008.005", "")

        COMMENT(COMMENT_TEXT, "I2S ear, left channel")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EAR_I2S_L, 0x1C, "008.015", "")

        COMMENT(COMMENT_TEXT, "I2S ear, right channel")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_EAR_I2S_R, 0x1D, "008.015", "")
  
        COMMENT(COMMENT_TEXT, "IHF Stereo")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_IHF, 0x1E, "009.007", "")
  
        COMMENT(COMMENT_TEXT, "IHF Left")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_IHF_L, 0x1F, "009.007", "")
  
        COMMENT(COMMENT_TEXT, "IHF Right")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_IHF_R, 0x20, "009.007", "")

        COMMENT(COMMENT_TEXT, "Stereo BT speaker selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_BT_STEREO, 0x21, "009.010", "")

        COMMENT(COMMENT_TEXT, "Wide-Band BT speaker selected")
        CONST_TBL_ENTRY_VER(AUD_MIXER_DL_OUT_BT_WB_EAR, 0x22, "009.010", "")
  
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x08+1, "", "006.008")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x0B+1, "006.008", "006.013")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x0C+1, "006.013", "007.001")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x0D+1, "007.001", "007.004")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x0F+1, "007.004", "007.005")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x12+1, "007.005", "007.007")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x1A+1, "007.007", "008.005")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x1B+1, "008.005", "008.015")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x1D+1, "008.015", "009.007")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x20+1, "009.007", "009.010")
    CONSTANT_VER(AUD_NUM_MIXER_DL_OUT_ATTRIBUTES, 0x22+1, "009.010", "")
        

    COMMENT(COMMENT_PARAGRAPH,
            "The resulting attribute value is a sum of selected device values. "
            "E.g. if DTMF tones are to be routed to speaker and simultaneously "
            "recorded, this attribute contains value 0x05. The default routing "
            "is decided by audio server according to the current accessory mode.")

    BIT_TBL_BEGIN(AUD_MIXER_DTMF_OUT_SELECT, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXX", AUD_MIXER_DTMF_OUT_MUTED, "DTMF output set muted")
        BIT_TBL_ENTRY("XXXXXXX1", AUD_MIXER_DTMF_OUT_EAR, "DTMF output routed to speaker")
        BIT_TBL_ENTRY("XXXXXX1X", AUD_MIXER_DTMF_OUT_ACC, "DTMF output routed to smart accessory")
        BIT_TBL_ENTRY("XXXXX1XX", AUD_MIXER_DTMF_OUT_MEMORY, "DTMF output routed to memory")
        BIT_TBL_ENTRY("XXXX1XXX", AUD_MIXER_DTMF_OUT_TX, "DTMF output routed to TX path (in analog mode only)")
        BIT_TBL_ENTRY("1XXXXXXX", AUD_MIXER_DTMF_OUT_DEFAULT, "DTMF default routing")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "The default routing is decided by audio server according to the current accessory mode.")

    BIT_TBL_BEGIN(AUD_MIXER_TONE_OUT_SELECT, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxxx", AUD_MIXER_TONE_OUT_MUTED, "Tone output set muted")
        BIT_TBL_ENTRY("xxxxxxx1", AUD_MIXER_TONE_OUT_EAR, "Tone output routed to speaker")
        
        COMMENT(COMMENT_TEXT, "Tone output routed to smart accessory")
        BIT_TBL_ENTRY_VER("xxxxxx1x", AUD_MIXER_TONE_OUT_ACC, "", "008.000")
        
        COMMENT(COMMENT_TEXT, "High Quality Audio ( MIDI, MP3, etc) routed to ear path." 
                              "Hand Portable when no accessory connected. With headset, routing will be headset ear piece")
        BIT_TBL_ENTRY_VER("xxxxxx1x", AUD_MIXER_TONE_OUT_HQ_EAR, "009.013", "")
        
        COMMENT(COMMENT_TEXT, "Tone output routed to memory")
        BIT_TBL_ENTRY_VER("xxxxx1xx", AUD_MIXER_TONE_OUT_MEMORY, "", "008.000" )
        
        COMMENT(COMMENT_TEXT, "Tone output is routed to HandPortable speaker, audio is speech type (sends some special settings to ADSP)")
        BIT_TBL_ENTRY_VER("xxxxx1xx", AUD_MIXER_TONE_OUT_SPEECH_EAR, "008.000", "")
        
        BIT_TBL_ENTRY("xxxx1xxx", AUD_MIXER_TONE_OUT_BUZZER, "Tone output routed to buzzer")
        BIT_TBL_ENTRY("xxx1xxxx", AUD_MIXER_TONE_OUT_HIGH_QUALITY, "Tone is routed to high-quality players ( MIDI, MP3, etc.)")
        BIT_TBL_ENTRY("xx1xxxx1", AUD_MIXER_TONE_OUT_EAR_TX, "Tone output is routed to speaker and TX path, i.e. tone "
                        "is locally played( according current audio mode) and is "
                        "routed to remote phone side - effective only in call state")
        BIT_TBL_ENTRY("x1xxxxxx", AUD_MIXER_TONE_OUT_SPEECH, "Tone output is routed to loudspeaker (depending on the "
                        "value of AUD_TONE_SEQUENCE_TYPE) but audio is speech."
                        "To be used for speech playback (e.g AMR)")
        BIT_TBL_ENTRY("1xxxxxxx", AUD_MIXER_TONE_OUT_DEFAULT, "Tone default routing")
    BIT_TBL_END

    CONST_TBL_BEGIN(AUD_MIXER_MODE_OUT_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_MIXER_MODE_OUT_MONO,          0x00,
                        "Audio output set to Mono")
        CONST_TBL_ENTRY(AUD_MIXER_MODE_OUT_STEREO,        0x01,
                        "Audio output set to Stereo")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_MIXER_QUALITY_SELECT, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_MIXER_QUALITY_NB,             0x00,
                        "Audio output quality set to NarrowBand")
        CONST_TBL_ENTRY(AUD_MIXER_QUALITY_WB,             0x01,
                        "Audio output quality set to WideBand")
        CONST_TBL_ENTRY(AUD_MIXER_QUALITY_HQ,             0x02,
                        "Audio output quality set to HighQuality")
    CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Note that this attribute is a bit field and that values can be set simultaneously.")

    BIT_TBL_BEGIN(AUD_MIXER_APP_IN_SELECT, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxxx", AUD_MIXER_APP_IN_MUTE, "Audio application input is muted")
        BIT_TBL_ENTRY("xxxxxxx1", AUD_MIXER_APP_IN_CMT_DL, "Audio application input is CMT DL")
        BIT_TBL_ENTRY("xxxxxx1x", AUD_MIXER_APP_IN_APE_SPEECH, "Audio application input is APE Speech")
        BIT_TBL_ENTRY("xxxxx1xx", AUD_MIXER_APP_IN_APE_AUDIO, "Audio application input is APE Audio")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Note that this attribute is a bit field and that values can be set simultaneously.")

    BIT_TBL_BEGIN(AUD_MIXER_APP_UL_SELECT, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxxx", AUD_MIXER_APP_UL_MUTED, "Audio application uplink input is muted")
        BIT_TBL_ENTRY("xxxxxxx1", AUD_MIXER_APP_UL_MIC, "Audio application uplink input is microphone")
        BIT_TBL_ENTRY("xxxxxx1x", AUD_MIXER_APP_UL_TONE, "Audio application uplink input is tone")
        BIT_TBL_ENTRY("xxxxx1xx", AUD_MIXER_APP_UL_SPEECH, "Audio application uplink input is speech")
        BIT_TBL_ENTRY("xxxx1xxx", AUD_MIXER_APP_UL_AUDIO, "Audio application uplink input is audio")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Note that this attribute is a bit field and that values can be set simultaneously.")

    BIT_TBL_BEGIN(AUD_MIXER_APP_REC_SELECT, 8, BE, "", "")
        BIT_TBL_ENTRY    ("xxxxxxxx", AUD_MIXER_APP_REC_MUTED, "Audio application recording input is muted")
        BIT_TBL_ENTRY    ("xxxxxxx1", AUD_MIXER_APP_REC_MIC, "Audio application recording input is microphone")
        BIT_TBL_ENTRY    ("xxxxxx1x", AUD_MIXER_APP_REC_CMTDL, "Audio application recording input is CMT DL")
        COMMENT(COMMENT_TEXT, "Audio application recording input is High quality recording path (Video recording)")
        BIT_TBL_ENTRY_VER("xxxxx1xx", AUD_MIXER_APE_AUD_REC, "005.025", "")
        COMMENT(COMMENT_TEXT, "Enable DSP generated tones to APE Audio recording path")
        BIT_TBL_ENTRY_VER("xxxx1xxx", AUD_MIXER_APE_TONE_AUD_REC, "006.014", "")
    BIT_TBL_END

    CONST_TBL_BEGIN(AUD_MIXER_DL_OUT_TRANSMIT_SELECT, 8, BE, "006.009", "")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_TRANSMIT_OFF,          0x00,
                        "Audio FM transmit output is OFF")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_TRANSMIT_TX_ONLY,      0x01,
                        "Audio FM transmit output is TX only")
        CONST_TBL_ENTRY(AUD_MIXER_DL_OUT_TRANSMIT_TX_AND_PHONE, 0x02,
                        "Audio FM transmit output is TX and Phone")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_MIXER_PLAYBACK_MODE_SELECT, 8, BE, "007.007", "")
        CONST_TBL_ENTRY(AUD_MIXER_PLAYBACK_REALTIME,          0x00,
                        "DAC33 real time Playback mode, no buffering")
        CONST_TBL_ENTRY(AUD_MIXER_PLAYBACK_POWERSAVE,         0x01,
                        "DAC33 real time Powersave mode, buffering enabled")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_TEST_TYPES, 8, BE, "", "")
        COMMENT(COMMENT_TEXT, "Audio codec loop back path routing from HP microphone "
                              "input to external speaker output")
        CONST_TBL_ENTRY_VER(AUD_TEST_HP_IN_EXT_OUT, 0x01, "", "009.000")
        COMMENT(COMMENT_TEXT, "Audio codec loop back path routing from external "
                                      "microphone input to HP speaker output")
        CONST_TBL_ENTRY_VER(AUD_TEST_EXT_IN_HP_OUT, 0x02, "", "009.000")
        COMMENT(COMMENT_TEXT, "Audio codec loop back path routing from digital input "
                              "(PDMIN) directly back to digital output (PDMOUT)")
        CONST_TBL_ENTRY(AUD_TEST_DIG_IN_DIG_OUT,                0x04, "")
        COMMENT(COMMENT_TEXT, "Audio codec loop back path routing from AIC33 line in left to HP speaker")
        CONST_TBL_ENTRY_VER(AUD_TEST_AIC33_LINEIN_LEFT_HP_OUT,  0x05, "006.001", "009.000")
        COMMENT(COMMENT_TEXT, "Audio codec loop back path routing from AIC33 line in right to HP speaker")
        CONST_TBL_ENTRY_VER(AUD_TEST_AIC33_LINEIN_RIGHT_HP_OUT, 0x06, "006.001", "")

        COMMENT(COMMENT_TEXT, "Audio codec loop back path routing from external microphone to "
                              "HAC coil")
        CONST_TBL_ENTRY_VER(AUD_TEST_EXT_IN_HAC_OUT, 0x07, "006.003", "")

        COMMENT(COMMENT_TEXT, "Audio codec loop back path routing from sigma-delta "
                              "modulator output to DAC input")
        CONST_TBL_ENTRY(AUD_TEST_ADC_OUT_DAC_IN,                0x08, "")

        COMMENT(COMMENT_TEXT, "Audio codec loop back path routing from phone digital stereo "
                              "mic to stereo ext ear out")
        CONST_TBL_ENTRY_VER(AUD_TEST_STEREO_DIG_IN_EXT_OUT, 0x09, "006.003", "009.000")
  
        COMMENT(COMMENT_TEXT, "Audio codec loopback from AV mic to IHF left")
        CONST_TBL_ENTRY_VER( AUD_TEST_AV_IN_IHF_LEFT_OUT, 0x0A, "009.000", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback from AV mic to IHF right")
        CONST_TBL_ENTRY_VER( AUD_TEST_AV_IN_IHF_RIGHT_OUT, 0x0B, "009.000", "")

        COMMENT(COMMENT_TEXT, "Buzzer test")
        CONST_TBL_ENTRY_VER(AUD_TEST_BUZZER, 0x10, "", "009.000")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from HP mic to AV ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_HP_IN_AV_OUT, 0x11, "007.004", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from AV mic to AV ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_AV_IN_AV_OUT, 0x12, "007.004", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from FM mic to AV ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_FM_IN_AV_OUT, 0x13, "007.004", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from AV mic to IHF ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_AV_IN_IHF_OUT, 0x14, "007.005", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from AV mic to HP ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_AV_IN_HP_OUT, 0x15, "007.005", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from USB mic to USB ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_USB_IN_USB_OUT, 0x16, "007.007", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from HP mic to USB ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_HP_IN_USB_OUT, 0x17, "007.007", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from USB mic to IHF ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_USB_IN_IHF_OUT, 0x18, "007.007", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from USB mic to HP ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_USB_IN_HP_OUT, 0x19, "007.007", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from HP mic to active EANC ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_MIC_IN_EANC_ON_OUT, 0x1A, "008.008", "")
        
        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from HP mic to bypass EANC ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_MIC_IN_EANC_OFF_OUT, 0x1B, "008.008", "")

        COMMENT(COMMENT_TEXT, "Audio EANC production test")
        CONST_TBL_ENTRY_VER( AUD_TEST_EANC_PROD_MODE, 0x1C, "008.013", "")

        COMMENT(COMMENT_TEXT, "Audio EANC service place test")
        CONST_TBL_ENTRY_VER( AUD_TEST_EANC_SP_MODE, 0x1D, "008.013", "")
                
        COMMENT(COMMENT_TEXT, "FM TX test out selection")
        CONST_TBL_ENTRY_VER( AUD_TEST_FM_TX_OUT, 0x1E, "008.016", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from HP mic1 to AV ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_HP_MIC1_IN_AV_OUT, 0x1F, "008.017", "")

        COMMENT(COMMENT_TEXT, "Audio-codec loopback path routing from external "
                              "microphone line to used integrated handsfree line "
                              "(not available for all products)")
        CONST_TBL_ENTRY_VER(AUD_TEST_EXT_IN_IHF_OUT, 0x20, "", "009.000")
  
        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from HP mic2 to AV ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_HP_MIC2_IN_AV_OUT, 0x21, "008.017", "")

        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from HP twin mics to AV ear")
        CONST_TBL_ENTRY_VER( AUD_TEST_HP_STEREO_IN_AV_OUT, 0x22, "008.017", "009.000")
  
        COMMENT(COMMENT_TEXT, "Audio codec loopback path routing from uUSB headset"
        " mic to uUSB headset ear left")
        CONST_TBL_ENTRY_VER(AUD_TEST_USB_IN_USB_OUT_EAR_L, 0x23, "009.001", "")
  
        COMMENT(COMMENT_TEXT, "Audio mic test: Route phone internal mic1 to uUSB"
        " headset ear left")
        CONST_TBL_ENTRY_VER(AUD_TEST_HP_MIC1_IN_USB_OUT_EAR_L, 0x24, "009.001", "")
  
        COMMENT(COMMENT_TEXT, "Audio mic2 test: Route phone internal mic2 to uUSB"
        " headset ear left")
        CONST_TBL_ENTRY_VER(AUD_TEST_HP_MIC2_IN_USB_OUT_EAR_L, 0x25, "009.001", "")
  
        COMMENT(COMMENT_TEXT, "IHF test: Route uUSB headset mic to phone IHF (left)")
        CONST_TBL_ENTRY_VER(AUD_TEST_USB_IN_IHF_OUT_LEFT, 0x26, "009.001", "")
  
        COMMENT(COMMENT_TEXT, "IHF test: Route uUSB headset mic to phone IHF (right)")
        CONST_TBL_ENTRY_VER(AUD_TEST_USB_IN_IHF_OUT_RIGHT, 0x27, "009.001", "")
  
        COMMENT(COMMENT_TEXT, "EANC mic1 test: Route EANC mic1 to uUSB headset ear left")
        CONST_TBL_ENTRY_VER(AUD_TEST_EANC_MIC1_IN_USB_OUT_EAR_L, 0x28, "009.001", "")
  
        COMMENT(COMMENT_TEXT, "EANC mic2 test: Route EANC mic2 to uUSB headset ear left")
        CONST_TBL_ENTRY_VER(AUD_TEST_EANC_MIC2_IN_USB_OUT_EAR_L, 0x29, "009.001", "")
  
        COMMENT(COMMENT_TEXT, "Audio-codec loopback path routing from external "
                              "microphone line to external speaker output "
                              "(not available for all products)")
        CONST_TBL_ENTRY_VER(AUD_TEST_EXT_IN_EXT_OUT, 0x40, "", "009.000")
  
        COMMENT(COMMENT_TEXT, "Audio-codec loopback path routing from fm radio "
                              "microphone line to external speaker output "
                              "(not available for all products)")
        CONST_TBL_ENTRY_VER(AUD_TEST_FM_IN_EXT_OUT, 0x80, "", "009.000")

    CONST_TBL_END

    /* remember to update when adding new test type */
    CONSTANT_VER(AUD_NUM_TEST_TYPES, 8, "", "006.001")
    CONSTANT_VER(AUD_NUM_TEST_TYPES, 10, "006.001", "006.003")
    CONSTANT_VER(AUD_NUM_TEST_TYPES, 12, "006.003", "007.004")
    CONSTANT_VER(AUD_NUM_TEST_TYPES, 15, "007.004", "007.005")
    CONSTANT_VER(AUD_NUM_TEST_TYPES, 17, "007.005", "007.007")
    CONSTANT_VER(AUD_NUM_TEST_TYPES, 21, "007.007", "008.016")
    CONSTANT_VER(AUD_NUM_TEST_TYPES, 26, "008.016", "008.017")
    CONSTANT_VER(AUD_NUM_TEST_TYPES, 29, "008.017", "")

    CONST_TBL_BEGIN(AUD_ERROR_CAUSES, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_CLIENT_NOT_SUPPORTED,         0x00,
                        "Unknown client type")
        CONST_TBL_ENTRY(AUD_CLIENT_NOT_ALLOWED,           0x01,
                        "The current status of server prevents operation with "
                        "requested client type")
        CONST_TBL_ENTRY(AUD_CLIENT_NOT_REGISTERED,        0x02,
                        "The client isn't registered in server")
        CONST_TBL_ENTRY(AUD_SERVICE_NOT_AVAILABLE,        0x03,
                        "Unknown service")
        CONST_TBL_ENTRY(AUD_ATTRIBUTE_NOT_AVAILABLE,      0x04,
                        "Unknown attribute")
        CONST_TBL_ENTRY(AUD_ALL_SETTINGS_INVALID,         0x05,
                        "All requested attribute update settings are invalid")
        CONST_TBL_ENTRY(AUD_SETTING_NOT_POSSIBLE,         0x06,
                        "Unsuccessful setting operation")
        CONST_TBL_ENTRY(AUD_TEST_TYPE_NOT_AVAILABLE,      0x07,
                        "Unknown test type")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_ERROR_CAUSES, 0x07+1, "", "")

    CONST_TBL_BEGIN(AUD_ATTRIBUTE_SETTING_OPERATIONS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_VALUE_SUBSTITUTE,             0x00,
                        "Current attribute value is substituted with the new value in request ")
        CONST_TBL_ENTRY(AUD_VALUE_INCREASE,               0x01,
                        "Value in request is added the current value of attribute")
        CONST_TBL_ENTRY(AUD_VALUE_DECREASE,               0x02,
                        "Value in request is subtracted from the current value of attribute")
        CONST_TBL_ENTRY(AUD_VALUE_BITWISE_OR,             0x03,
                        "Value in request is bitwise ORed to the current value of attribute")
        CONST_TBL_ENTRY(AUD_VALUE_BITWISE_AND,            0x04,
                        "Value in request is bitwise ANDed to the current value of attribute")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_OPERATIONS, 0x04+1, "", "")

    CONST_TBL_BEGIN(AUDIO_SERVICE_CONFIGURATIONS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_CONFIG_NON_DEFAULT,           0x00,
                        "Server service configuration isn't the default one")
        CONST_TBL_ENTRY(AUD_CONFIG_DEFAULT,               0x01,
                        "Server service configuration is the default one")
    CONST_TBL_END


    CONST_TBL_BEGIN(AUD_LAYER_UPDATE_GENERAL_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_ALL_SETTINGS_OK,              0x00,
                        "All settings in update request were valid")
        CONST_TBL_ENTRY(AUD_SOME_SETTINGS_LIMITED,        0x01,
                        "Some settings in update request had to be limited, "
                        "no setting was erroneous")
        CONST_TBL_ENTRY(AUD_SOME_SETTINGS_INVALID,        0x02,
                        "Some settings in update request were erroneous. "
                        "It's also possible that some other settings were limited")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_LAYER_UPDATE_ATTR_SPEC_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_SETTING_NOT_ALLOWED,          0x00,
                        "Client is not allowed to update requested attribute")
        CONST_TBL_ENTRY(AUD_SETTING_VALUE_NOT_OK,         0x01,
                        "Requested setting value is invalid")
        CONST_TBL_ENTRY(AUD_SETTING_OK,                   0x02,
                        "Requested setting value is valid")
        CONST_TBL_ENTRY(AUD_SETTING_CUT_TO_UPPER_LIMIT,   0x03,
                        "Requested setting value was truncated to upper limit value")
        CONST_TBL_ENTRY(AUD_SETTING_CUT_TO_LOWER_LIMIT,   0x04,
                        "Requested setting value was truncated to lower limit value")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_SETTING_STATUSES, 0x04+1, "", "")

    CONST_TBL_BEGIN(AUD_LAYER_UPDATE_GENERAL_EFFICIENCY, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_ALL_SETTINGS_EFFECTIVE,       0x00,
                        "All settings in update request are valid")
        CONST_TBL_ENTRY(AUD_SOME_SETTINGS_INEFFECTIVE,    0x01,
                        "Some settings in update request had to be limited")
    CONST_TBL_END


    CONST_TBL_BEGIN(AUD_LAYER_UPDATE_ATTR_EFFICIENCY, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_LAYER_INEFFECTIVE,            0x00,
                        "Updated layer is not effective")
        CONST_TBL_ENTRY(AUD_LAYER_EFFECTIVE,              0x01,
                        "Updated layer is effective")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_LAYER_UPDATE_ATTR_EVENTS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_LAYER_ON_TOP,                 0x00,
                        "The client controlling the effective layer has changed, "
                        "thus causing the change of attribute setting")
        CONST_TBL_ENTRY(AUD_LAYER_SETTING_CHANGE,         0x01,
                        "The client controlling the effective layer remains "
                        "the same, it has only changed its previous setting")
    CONST_TBL_END
    
    CONST_TBL_BEGIN(AUD_SELFTEST_TYPES, 8, BE, "009.006", "")
        CONST_TBL_ENTRY(AUD_SELFTEST_AMPLIFIER_TEST, 0x01, "Amplifier test")
        CONST_TBL_ENTRY(AUD_SELFTEST_KELVIN_XEAR_TEST, 0x02, "Kelvin ihf test")
        CONST_TBL_ENTRY(AUD_SELFTEST_AUDIO_PLL_TEST, 0x03, "Audio PLL test")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_FEATURE_ID, 8, BE, "009.004", "")
        CONST_TBL_ENTRY(AUD_VOICE_UI, 0x01, "Audio Voice UI ")
    CONST_TBL_END

    CONST_TBL_BEGIN(AUD_SWITCH_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_SWITCH_OFF,                   0x00, "")
        CONST_TBL_ENTRY(AUD_SWITCH_ON,                    0x01, "")
    CONST_TBL_END


    COMMENT(COMMENT_TEXT,
           "NOTE: UI, CS and DSP clients are considered 'basic' "
           "ie. they are supposed to always exist in the MCU SW")
    CONST_TBL_BEGIN(AUD_CLIENT_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_NO_CLIENT_TYPE,               0x00,
                        "This is used only in layer update indications to tell "
                        "that no client's layer affects the attribute, i.e. "
                        "attribute has the default setting")
        CONST_TBL_ENTRY(AUD_UI_CLIENT_TYPE,               0x01,
                        "UI client, primary handler of AUD_MIXER attributes")
        CONST_TBL_ENTRY(AUD_CS_CLIENT_TYPE,               0x02,
                        "CS client, primary handler of AUD_MIXER attributes")
        CONST_TBL_ENTRY(AUD_ACC_CLIENT_TYPE,              0x03,
                        "Smart accessory client")
        CONST_TBL_ENTRY(AUD_EXT_CLIENT_TYPE,              0x04,
                        "External client, not necessarily an accessory")
        CONST_TBL_ENTRY(AUD_BATT_CLIENT_TYPE,             0x05,
                        "Battery accessory client")
        CONST_TBL_ENTRY(AUD_DSP_CLIENT_TYPE,              0x06,
                        "DSP client")
        CONST_TBL_ENTRY(AUD_TEST_CLIENT_TYPE,             0x07,
                        "Test client")
        CONST_TBL_ENTRY(AUD_SOUND_CLIENT_TYPE,            0x08,
                        "High quality sound player ( MIDI, MP3, etc.)")
        CONST_TBL_ENTRY(AUD_CS_HIGH_CLIENT_TYPE,          0x09,
                        "CS client with higher priority than AUD_CS_CLIENT_TYPE")
        CONST_TBL_ENTRY(AUD_VOL_CTRL_CLIENT_TYPE,         0x0A,
                        "Volume Control client type. All clients of this type"
                        "are using same layer when accessing AUD_ANALOG_OUT:"
                        "AUD_ANALOG_OUT_VOL_LEVEL attribute")
        COMMENT(COMMENT_TEXT, "UI_2 client, higher priority than AUD_UI_CLIENT_TYPE")
        CONST_TBL_ENTRY_VER(AUD_UI_2_CLIENT_TYPE,             0x0B, "005.028", "")
        COMMENT(COMMENT_TEXT, "Client type for Kodiak POC routing")
        CONST_TBL_ENTRY_VER(AUD_KODIAK_CLIENT_TYPE,             0x0C, "007.001", "")
    CONST_TBL_END

    CONSTANT_VER(AUD_NUM_CLIENT_TYPES, 0x0A+1,"","005.028")
    CONSTANT_VER(AUD_NUM_CLIENT_TYPES, 0x0B+1,"005.028","007.001")
    CONSTANT_VER(AUD_NUM_CLIENT_TYPES, 0x0C+1,"007.001","")

    CONST_TBL_BEGIN(AUD_DSP_PHAP_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_DSP_PHAP_OFF,       0x00, "PHAP OFF")
        CONST_TBL_ENTRY(AUD_DSP_PHAP_NORMAL,    0x01, "PHAP NORMAL")
        CONST_TBL_ENTRY(AUD_DSP_PHAP_SLIGHT,    0x02, "PHAP SLIGHT")
        CONST_TBL_ENTRY(AUD_DSP_PHAP_MILD,      0x03, "PHAP MILD")
        CONST_TBL_ENTRY(AUD_DSP_PHAP_MODERATE,  0x04, "PHAP MODERATE")
    CONST_TBL_END
    
    
    CONST_TBL_BEGIN(AUD_INPUT_OUTPUT_MODE, 8, BE, "009.006", "")
        CONST_TBL_ENTRY(AUD_MODE_MONO, 0x00, "")
        CONST_TBL_ENTRY(AUD_MODE_STEREO, 0x01, "")
        CONST_TBL_ENTRY(AUD_MODE_LEFT, 0x02, "")
        CONST_TBL_ENTRY(AUD_MODE_RIGHT, 0x03, "")
    CONST_TBL_END
        

    /* bit tables */

    COMMENT(COMMENT_PARAGRAPH,
            "Note: Setting some of the bit fields means that appropriate algorithm"
            "in DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP will"
            "use default set of enhancement algorithms for current accessory mode.")

    BIT_TBL_BEGIN(AUD_DSP_ALGORITHMS_1, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXX", AUD_DSP_ALGORITHM_OFF, "Default set of enhancement algorithms in use")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", AUD_DSP_ALGORITHM_AEC, "Acoustic Echo Canceller")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", AUD_DSP_ALGORITHM_AEC_SUPP, "AEC suppressor")
        BIT_TBL_ENTRY("XXXXXXXXXXXXX1XX", AUD_DSP_ALGORITHM_UALWE, "Uplink ALWE")
        BIT_TBL_ENTRY("XXXXXXXXXXXX1XXX", AUD_DSP_ALGORITHM_UALWE_PAUSE_ATT, "Pause attenuation for UALWE")
        BIT_TBL_ENTRY("XXXXXXXXXXX1XXXX", AUD_DSP_ALGORITHM_DALWE, "Downlink ALWE")
        BIT_TBL_ENTRY("XXXXXXXXXX1XXXXX", AUD_DSP_ALGORITHM_DALWE_PAUSE_ATT, "Pause attenuation for DALWE")
        BIT_TBL_ENTRY("XXXXXXXXX1XXXXXX", AUD_DSP_ALGORITHM_DDRC, "Time domain DDRC (AEP 3) or Multiband DRC (AEP 4)")
        BIT_TBL_ENTRY("XXXXXXXX1XXXXXXX", AUD_DSP_ALGORITHM_UDRC, "Uplink Dynamic Range Control")
        BIT_TBL_ENTRY("XXXXXXX1XXXXXXXX", AUD_DSP_ALGORITHM_FDRC, "Fast DRC addition to DRC")
        BIT_TBL_ENTRY("XXXXXX1XXXXXXXXX", AUD_DSP_ALGORITHM_AGC, "Microphone Adaptive Gain Control")
        BIT_TBL_ENTRY("XXXXX1XXXXXXXXXX", AUD_DSP_ALGORITHM_AVC, "Automatic Volume Control")
        BIT_TBL_ENTRY("XXXX1XXXXXXXXXXX", AUD_DSP_ALGORITHM_GEQ, "Graphic Equalizer")
        BIT_TBL_ENTRY("XXX1XXXXXXXXXXXX", AUD_DSP_ALGORITHM_PEQ, "Preset Equalizer")
        COMMENT(COMMENT_TEXT, "Basic Equalizer")
        BIT_TBL_ENTRY_VER("XX1XXXXXXXXXXXXX", AUD_DSP_ALGORITHM_BEQ, "", "007.000")
        COMMENT(COMMENT_TEXT, "AEC Comfort Noise")
        BIT_TBL_ENTRY_VER("XX1XXXXXXXXXXXXX", AUD_DSP_ALGORITHM_AEC_CN, "007.000", "")
        BIT_TBL_ENTRY("X1XXXXXXXXXXXXXX", AUD_DSP_ALGORITHM_IHF, "Integrated Hands Free algorithm")
        BIT_TBL_ENTRY("1XXXXXXXXXXXXXXX", AUD_DSP_ALGORITHM_MIMDRC, "MIDI Multiband DRC")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Note: Setting some of the bit fields means that appropriate algorithm"
            "in DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP will"
            "use default set of enhancement algorithms for current accessory mode.")

    BIT_TBL_BEGIN(AUD_DSP_ALGORITHMS_2, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXXX", AUD_DSP_ALGORITHM_OFF, "Default set of enhancement algorithms in use")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", AUD_DSP_ALGORITHM_EEQ, "Earpiece Equalizer")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", AUD_DSP_ALGORITHM_MEQ, "Microphone Equalizer")
        BIT_TBL_ENTRY("XXXXXXXXXXXXX1XX", AUD_DSP_ALGORITHM_ANC, "Active Noise Control")
        BIT_TBL_ENTRY("XXXXXXXXXXXX1XXX", AUD_DSP_ALGORITHM_MICHP, "Microphone High Pass filter in DSP")
        BIT_TBL_ENTRY("XXXXXXXXXXX1XXXX", AUD_DSP_ALGORITHM_UEM_DECIM, "Decimation in UEM interrupt server")
        BIT_TBL_ENTRY("XXXXXXXXXX1XXXXX", AUD_DSP_ALGORITHM_UEM_INTERP, "Interpolation in UEM interrupt server")
        BIT_TBL_ENTRY("XXXXXXXXX1XXXXXX", AUD_DSP_ALGORITHM_SIDETONE_EQU, "Sidetone Equalizer")
        BIT_TBL_ENTRY("XXXXXXXX1XXXXXXX", AUD_DSP_ALGORITHM_MIDI_HP, "MIDI High-Pass Filter used also for MuMDRC HP filter")
        BIT_TBL_ENTRY("XXXXXXX1XXXXXXXX", AUD_DSP_ALGORITHM_MIDI_EQU, "MIDI Equalizer")
        BIT_TBL_ENTRY("XXXXXX1XXXXXXXXX", AUD_DSP_ALGORITHM_MIDI_LIM, "MIDI Limiter")
        BIT_TBL_ENTRY("XXXXX1XXXXXXXXXX", AUD_DSP_ALGORITHM_DDRC_VOL_DEP, "DDRC volume dependency")
        BIT_TBL_ENTRY("XXXX1XXXXXXXXXXX", AUD_DSP_ALGORITHM_DDRC_NOISE_DEP, "DDRC noise dependency")
        BIT_TBL_ENTRY("XXX1XXXXXXXXXXXX", AUD_DSP_ALGORITHM_MIDI_REVERB, "MIDI reverberation")
        COMMENT(COMMENT_TEXT, "48kHz earpiece equalizer")
        BIT_TBL_ENTRY_VER("xx1xxxxxxxxxxxxx", AUD_DSP_ALGORITHM_HQ_EEQ, "007.000", "")
        COMMENT(COMMENT_TEXT, "48kHz microphone equalizer")
        BIT_TBL_ENTRY_VER("x1xxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_HQ_MEQ, "007.000", "")
        COMMENT(COMMENT_TEXT, "Artificial Bandwidth Expansion (ABE)")
        BIT_TBL_ENTRY_VER("1xxxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_ABE, "007.000", "")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Note: Setting some of the bit fields means that appropriate algorithm"
            "in DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP will"
            "use default set of enhancement algorithms for current accessory mode.")

    BIT_TBL_BEGIN(AUD_DSP_ALGORITHMS_3, 16, BE, "007.000", "")
        COMMENT(COMMENT_TEXT, "Default set of enhancement algorithms in use");
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_OFF, "007.000", "")
        COMMENT(COMMENT_TEXT, "Network Echo Suppressor (Amadeus)")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxxx1", AUD_DSP_ALGORITHM_NES, "007.000", "")
        COMMENT(COMMENT_TEXT, "Analog mode Acoustic Echo Suppressor (Amadeus)")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxx1x", AUD_DSP_ALGORITHM_AMODE_AEC, "007.000", "")
        COMMENT(COMMENT_TEXT, "Ear Protection Limiter (Amadeus)")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxx1xx", AUD_DSP_ALGORITHM_EAR_PROT_LIM, "007.000", "")
        COMMENT(COMMENT_TEXT, "Fast DRC (different from FDRC in switch 1) (Amadeus)")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxx1xxx", AUD_DSP_ALGORITHM_FAST_DRC, "007.000", "")
        COMMENT(COMMENT_TEXT, "Speech Codec Teletype (Amadeus, Gemini)")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxx1xxxx", AUD_DSP_ALGORITHM_SPC_TTY, "007.000", "")
        COMMENT(COMMENT_TEXT, "Sizzling Suppressor (Amadeus)")
        BIT_TBL_ENTRY_VER("xxxxxxxxxx1xxxxx", AUD_DSP_ALGORITHM_SIZZ_SUPP, "007.000", "")
        COMMENT(COMMENT_TEXT, "Automatic Volume Control for Loopset (Amadeus)")
        BIT_TBL_ENTRY_VER("xxxxxxxxx1xxxxxx", AUD_DSP_ALGORITHM_AVC_LOOPSET, "007.000", "")
        COMMENT(COMMENT_TEXT, "Analog mode LIMA filter (Amadeus)")
        BIT_TBL_ENTRY_VER("xxxxxxxx1xxxxxxx", AUD_DSP_ALGORITHM_AMODE_LIMA, "007.000", "")
        COMMENT(COMMENT_TEXT, "Earpiece High-Pass filter (Amadeus, Gemini)")
        BIT_TBL_ENTRY_VER("xxxxxxx1xxxxxxxx", AUD_DSP_ALGORITHM_EARHP, "007.000", "")
        COMMENT(COMMENT_TEXT, "Fast DRC for TX (Amadeus)")
        BIT_TBL_ENTRY_VER("xxxxxx1xxxxxxxxx", AUD_DSP_ALGORITHM_FAST_DRC_TX, "007.000", "")
        COMMENT(COMMENT_TEXT, "Wind Noise Reduction - WNR")
        BIT_TBL_ENTRY_VER("xxxxx1xxxxxxxxxx", AUD_DSP_ALGORITHM_WNR, "007.000", "")
        COMMENT(COMMENT_TEXT, "Sidetone Howling control - SHC")
        BIT_TBL_ENTRY_VER("xxxx1xxxxxxxxxxx", AUD_DSP_ALGORITHM_SHC, "007.000", "")
        COMMENT(COMMENT_TEXT, "Voice Activity Detection - VAD")
        BIT_TBL_ENTRY_VER("xxx1xxxxxxxxxxxx", AUD_DSP_ALGORITHM_VAD, "007.000", "")
        COMMENT(COMMENT_TEXT, "Sound level meter")
        BIT_TBL_ENTRY_VER("xx1xxxxxxxxxxxxx", AUD_DSP_ALGORITHM_SLM, "007.000", "")
        COMMENT(COMMENT_TEXT, "When set, prevents accessory dependent algorithm switch updating in DSP")
        BIT_TBL_ENTRY_VER("x1xxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_MANUAL_CONTROL, "007.000", "")
        COMMENT(COMMENT_TEXT, "Transducer DRC (XDRC)")
        BIT_TBL_ENTRY_VER("1xxxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_XDRC, "007.000", "")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Note: Setting some of the bit fields means that appropriate algorithm"
            "in DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP will"
            "use default set of enhancement algorithms for current accessory mode.")

    BIT_TBL_BEGIN(AUD_DSP_ALGORITHMS_4, 16, BE, "007.000", "")
        COMMENT(COMMENT_TEXT, "Default set of enhancement algorithms in use");
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_OFF, "007.000", "")
        COMMENT(COMMENT_TEXT, "X-Prot IHF thermal protection, temperature limiting")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxxx1", AUD_DSP_ALGORITHM_XPROT_TEMP, "007.000", "")
        COMMENT(COMMENT_TEXT, "X-Prot IHF protection against excess displacement, displacement limiting")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxx1x", AUD_DSP_ALGORITHM_XPROT_DISP, "007.000", "")
        COMMENT(COMMENT_TEXT, "Music MDRC")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxx1xx", AUD_DSP_ALGORITHM_MUMDRC, "007.000", "")
        COMMENT(COMMENT_TEXT, "Stereo widening for headset")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxx1xxx", AUD_DSP_ALGORITHM_STW_HD, "007.000", "")
        COMMENT(COMMENT_TEXT, "Stereo widening for loudspeakers")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxx1xxxx", AUD_DSP_ALGORITHM_STW_LS, "007.000", "")
        COMMENT(COMMENT_TEXT, "Doppler effect")
        BIT_TBL_ENTRY_VER("xxxxxxxxxx1xxxxx", AUD_DSP_ALGORITHM_DOPPLER, "007.000", "")
        COMMENT(COMMENT_TEXT, "Positional 3D audio for headset")
        BIT_TBL_ENTRY_VER("xxxxxxxxx1xxxxxx", AUD_DSP_ALGORITHM_POS3D_HD, "007.000", "")
        COMMENT(COMMENT_TEXT, "Positional 3D audio for loudspeakers")
        BIT_TBL_ENTRY_VER("xxxxxxxx1xxxxxxx", AUD_DSP_ALGORITHM_POS3D_LS, "007.000", "")
        COMMENT(COMMENT_TEXT, "Environmental reverberation")
        BIT_TBL_ENTRY_VER("xxxxxxx1xxxxxxxx", AUD_DSP_ALGORITHM_REVERB, "007.000", "")
        COMMENT(COMMENT_TEXT, "Audio visualisation")
        BIT_TBL_ENTRY_VER("xxxxxx1xxxxxxxxx", AUD_DSP_ALGORITHM_AUDIO_VIS, "007.000", "")
        COMMENT(COMMENT_TEXT, "Stereo Processing for Audio Capture")
        BIT_TBL_ENTRY_VER("xxxxx1xxxxxxxxxx", AUD_DSP_ALGORITHM_SPAC, "007.000", "")
        COMMENT(COMMENT_TEXT, "MuMDRC in recording path")
        BIT_TBL_ENTRY_VER("xxxx1xxxxxxxxxxx", AUD_DSP_ALGORITHM_REC_MUMDRC, "008.007", "")
        COMMENT(COMMENT_TEXT, "Limiter in recording path")
        BIT_TBL_ENTRY_VER("xxx1xxxxxxxxxxxx", AUD_DSP_ALGORITHM_REC_LIMITER, "008.007", "")
        COMMENT(COMMENT_TEXT, "Fullband AGC in recording path")
        BIT_TBL_ENTRY_VER("xx1xxxxxxxxxxxxx", AUD_DSP_ALGORITHM_FULLBAND_AGC, "008.007", "")
        COMMENT(COMMENT_TEXT, "APSSAS")
        BIT_TBL_ENTRY_VER("x1xxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_APSSAS, "009.000", "")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Note: Setting some of the bit fields means that appropriate algorithm"
            "in DSP will be switched OFF. AUD_DSP_ALGORITHM_OFF value means that DSP will"
            "use default set of enhancement algorithms for current accessory mode.")

    BIT_TBL_BEGIN(AUD_DSP_ALGORITHMS_5, 16, BE, "007.000", "")
        COMMENT(COMMENT_TEXT, "Default set of enhancement algorithms in use")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_OFF, "007.000", "")
        COMMENT(COMMENT_TEXT, "UDRC whisper mode")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxxx1", AUD_DSP_ALGORITHM_UDRC_WHISPER_MODE, "007.000", "009.012")
        COMMENT(COMMENT_TEXT, "Rx IAVC")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxx1x", AUD_DSP_ALGORITHM_RX_IAVC, "007.000", "")
        COMMENT(COMMENT_TEXT, "Tx IAVC, needs MB UL DRC")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxx1xx", AUD_DSP_ALGORITHM_TX_IAVC, "007.000", "")
        COMMENT(COMMENT_TEXT, "Multiband UL DRC - in future")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxx1xxx", AUD_DSP_ALGORITHM_MB_UDRC, "007.000", "009.012")
        COMMENT(COMMENT_TEXT, "Separate limiter algorithm switch - unconditional")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxx1xxxx", AUD_DSP_ALGORITHM_LIMITER, "008.009", "")
        COMMENT(COMMENT_TEXT, "Separate limiter algorithm switch - conditional")
        BIT_TBL_ENTRY_VER("xxxxxxxxxx1xxxxx", AUD_DSP_ALGORITHM_LIMITER_CONDITIONAL, "008.009", "")
        COMMENT(COMMENT_TEXT, "Switch for speech emphasis EQU block. Note: despite its name, this switch can also be used in WB mode (but its frequency response is different).")
        BIT_TBL_ENTRY_VER("xxxxxxxxx1xxxxxx", AUD_DSP_ALGORITHM_NB_SPC_EMPHASIS, "008.009", "")
        COMMENT(COMMENT_TEXT, "Switch for MMIC CAL gain estimation.")
        BIT_TBL_ENTRY_VER("xxxxxxxx1xxxxxxx", AUD_DSP_ALGORITHM_MMIC_SELECT_CAL_GAIN_ESTIM, "008.009", "")
        COMMENT(COMMENT_TEXT, "Switch for MMIC CAL gain apply.")
        BIT_TBL_ENTRY_VER("xxxxxxx1xxxxxxxx", AUD_DSP_ALGORITHM_MMIC_SELECT_CAL_GAIN_APPLY, "008.009", "")
        COMMENT(COMMENT_TEXT, "Switch for MMIC STB.")
        BIT_TBL_ENTRY_VER("xxxxxx1xxxxxxxxx", AUD_DSP_ALGORITHM_MMIC_SELECT_STB, "008.009", "")
        COMMENT(COMMENT_TEXT, "Switch for MMIC AIC.")
        BIT_TBL_ENTRY_VER("xxxxx1xxxxxxxxxx", AUD_DSP_ALGORITHM_MMIC_SELECT_AIC, "008.009", "")
        COMMENT(COMMENT_TEXT, "Switch for MMIC POS.")
        BIT_TBL_ENTRY_VER("xxxx1xxxxxxxxxxx", AUD_DSP_ALGORITHM_MMIC_SELECT_POS, "008.009", "")
        COMMENT(COMMENT_TEXT, "Switch for MMIC overall.")
        BIT_TBL_ENTRY_VER("xxx1xxxxxxxxxxxx", AUD_DSP_ALGORITHM_MMIC, "008.009", "")
        COMMENT(COMMENT_TEXT, "Switch for True WB concept.")
        BIT_TBL_ENTRY_VER("xx1xxxxxxxxxxxxx", AUD_DSP_ALGORITHM_TRUE_WB, "008.009", "009.012")
        COMMENT(COMMENT_TEXT, "Switch for multi-mic WNR")
        BIT_TBL_ENTRY_VER("xx1xxxxxxxxxxxxx", AUD_DSP_ALGORITHM_MWNR, "009.012", "")
        COMMENT(COMMENT_TEXT, "Switch for MMIC spatial VAD")
        BIT_TBL_ENTRY_VER("x1xxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_MMIC_VAD, "009.012", "")
        COMMENT(COMMENT_TEXT, "Switch for MMIC noise reference usage")
        BIT_TBL_ENTRY_VER("1xxxxxxxxxxxxxxx", AUD_DSP_ALGORITHM_MMIC_NREF, "009.012", "")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
            "Note: For ACA algorithms 1=on and 0=off. The client must also specify \
             a mask to tell the audio server which algorithms it wishes to explicitly \
             control. If the mask bit is 1, the client controls the switch, \
             otherwise the value will be taken from mode specific tunings.")

    BIT_TBL_BEGIN(AUD_DSP_ACA_ALGORITHMS, 16, BE, "009.011", "")
        COMMENT(COMMENT_TEXT, "ACA Optical Zoom Noise Control")
        BIT_TBL_ENTRY_VER("xxxxxxxxxxxxxxx1", AUD_DSP_ACA_ALGORITHMS_OZN, "009.011", "")
    BIT_TBL_END

    BIT_TBL_BEGIN(AUD_CLIENT_TYPES_1, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXX1", AUD_CLIENT_SOUND, "")
        BIT_TBL_ENTRY("XXXXXX1X", AUD_CLIENT_UI, "")
        BIT_TBL_ENTRY("XXXXX1XX", AUD_CLIENT_CS, "")
        BIT_TBL_ENTRY("XXXX1XXX", AUD_CLIENT_ACC, "")
        BIT_TBL_ENTRY("XXX1XXXX", AUD_CLIENT_EXT, "")
        BIT_TBL_ENTRY("XX1XXXXX", AUD_CLIENT_BATT, "")
        BIT_TBL_ENTRY("X1XXXXXX", AUD_CLIENT_DSP, "")
        BIT_TBL_ENTRY("1XXXXXXX", AUD_CLIENT_TEST, "")
    BIT_TBL_END

    BIT_TBL_BEGIN(AUD_CLIENT_TYPES_2, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXX1X", AUD_CLIENT_CS_HIGH, "")
    BIT_TBL_END

    CONST_TBL_BEGIN(AUD_HW_STATUSES, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_HW_STATUS_READY,                   0x00, "")
        CONST_TBL_ENTRY(AUD_HW_STATUS_BUSY,                    0x01, "")
    CONST_TBL_END


    /* FTD constants for internal use */

    CONSTANT(FTD_ACC, FTD_ACC)
    CONSTANT(FTD_AD, FTD_AD)
    CONSTANT(FTD_ULI, FTD_ULI)
    CONSTANT(FTD_DLO, FTD_DLO)
    CONSTANT(FTD_GAIN, FTD_GAIN)
    CONSTANT(FTD_VOL, FTD_VOL)
    CONSTANT(FTD_DPW, FTD_DPW)
    CONSTANT(FTD_UPW, FTD_UPW)
    CONSTANT(COMM_FTD_DATA_AUD_BASE, COMM_FTD_DATA_AUD_BASE)

    /* FTD data table */

    FTD_TBL_BEGIN("", "")
        PROPERTY_VALUE( PROPERTY_FTD_SUPPORTED_MODES, FTD_MODE_OPERATOR )
        FTD_VALUE_BEGIN(COMM_FTD_DATA_AUD_ACCESSORY_MODE, (COMM_FTD_DATA_AUD_BASE+FTD_ACC), "", "")
            COMMENT(COMMENT_TEXT, "Accessory mode")
            VALUE_CONST(acc_mode, "Accessory mode", AUD_MODE_VALUES)
        FTD_VALUE_END
        
        FTD_VALUE_BEGIN(COMM_FTD_DATA_AUD_ANADIGI_MODE, (COMM_FTD_DATA_AUD_BASE+FTD_AD), "", "")
            COMMENT(COMMENT_TEXT, "Analog or digital mode selected")
            VALUE_CONST(anadigi_mode, "Analog or digital mode", AUD_MODE_ANA_DIGI)
        FTD_VALUE_END
        
        FTD_VALUE_BEGIN(COMM_FTD_DATA_AUD_MIXER_ULI, (COMM_FTD_DATA_AUD_BASE+FTD_ULI), "", "")
            COMMENT(COMMENT_TEXT, "Mixer uplink in")
            VALUE(8, BE, mixer_uli, "Uplink in", DEC)
        FTD_VALUE_END
        
        FTD_VALUE_BEGIN(COMM_FTD_DATA_AUD_MIXER_DLO, (COMM_FTD_DATA_AUD_BASE+FTD_DLO), "", "")
            COMMENT(COMMENT_TEXT, "Mixer downlink out")
            VALUE(8, BE, mixer_dlo, "Downlink out", DEC)
        FTD_VALUE_END
        
        FTD_VALUE_BEGIN(COMM_FTD_DATA_AUD_AIN_GAIN, (COMM_FTD_DATA_AUD_BASE+FTD_GAIN), "", "")
            COMMENT(COMMENT_TEXT, "Analog in gain value")
            VALUE(8, BE, ain_gain, "Analog in gain", DEC)
        FTD_VALUE_END
        
        FTD_VALUE_BEGIN(COMM_FTD_DATA_AUD_AOU_VOL, (COMM_FTD_DATA_AUD_BASE+FTD_VOL), "", "")
            COMMENT(COMMENT_TEXT, "Analog out volume")
            VALUE(8, BE, aou_vol, "Analog out volume", DEC)
        FTD_VALUE_END
        
        PROPERTY_VALUE( PROPERTY_FTD_SUPPORTED_MODES, FTD_MODE_OPERATOR )
        FTD_VALUE_BEGIN(COMM_FTD_DATA_AUD_MIXER_DPW, (COMM_FTD_DATA_AUD_BASE+FTD_DPW), "", "")
            COMMENT(COMMENT_TEXT, "Mixer downlink power")
            VALUE(8, BE, mixer_dpw, "Downlink power", DEC)
        FTD_VALUE_END
        
        PROPERTY_VALUE( PROPERTY_FTD_SUPPORTED_MODES, FTD_MODE_OPERATOR )
        FTD_VALUE_BEGIN(COMM_FTD_DATA_AUD_MIXER_UPW, (COMM_FTD_DATA_AUD_BASE+FTD_UPW), "", "")
            COMMENT(COMMENT_TEXT, "Mixer uplink power")
            VALUE(8, BE, mixer_upw, "Uplink power", DEC)
        FTD_VALUE_END
    FTD_TBL_END

    CONSTANT(AUD_COMM_FTD_DATA_NUM, 8)

    /* Sequences */


    /* ------------------------------------------------------------------ */
    /* value sequences for sevice attributes */
    /* ------------------------------------------------------------------ */

    SEQ_BEGIN(AUD_DEFAULT_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SEQ_END


    /* Analog in attribute value */

    SEQ_BEGIN(AUD_ANALOG_IN_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SEQ_END


    /* Analog out attribute value */

    /* SEQ_BEGIN(AUD_ANALOG_OUT_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SEQ_END */
    /*
    SEQ_BEGIN(AUD_ANALOG_OUT_VOL_BALANCE_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(AttributeValue, "Value", AUD_ANALOG_OUT_VOL_BALANCE)
    SEQ_END
    */
    SEQ_BEGIN(AUD_ANALOG_OUT_VOL_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SEQ_END

    SEQ_BEGIN(AUD_ANALOG_OUT_VOL_ABS_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SEQ_END

    SEQ_BEGIN(AUD_ANALOG_OUT_VOL_BALANCE_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_ANALOG_OUT_VOL_BALANCE)
    SEQ_END

    SEQ_BEGIN(AUD_ANALOG_OUT_VALUE, DONT_CREATE_STRUCT, "", "")
        CHOICE_BEGIN(AttributeValue, "Value", ID)
            CASE(AUD_ANALOG_OUT_VOL_LEVEL,     AUD_ANALOG_OUT_VOL_VALUE)
            CASE(AUD_ANALOG_OUT_VOL_ABS_VALUE, AUD_ANALOG_OUT_VOL_ABS_VALUE)
            CASE(AUD_ANALOG_OUT_VOL_BALANCE,   AUD_ANALOG_OUT_VOL_BALANCE_VALUE)
            CASE_DEFAULT(AUD_DEFAULT_VALUE)
        CHOICE_END
    SEQ_END

    /* DSP params attribute values */

    SEQ_BEGIN(AUD_DSP_ALGORITHMS_1_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(AttributeValue, "Value", AUD_DSP_ALGORITHMS_1)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_ALGORITHMS_2_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(AttributeValue, "Value", AUD_DSP_ALGORITHMS_2)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_PHAP_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(AttributeValue, "Value", AUD_DSP_PHAP_VALUES)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_ALGORITHMS_3_VALUE, DONT_CREATE_STRUCT, "007.000", "")
        VALUE_CONST(AttributeValue, "Value", AUD_DSP_ALGORITHMS_3)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_ALGORITHMS_4_VALUE, DONT_CREATE_STRUCT, "007.000", "")
        VALUE_CONST(AttributeValue, "Value", AUD_DSP_ALGORITHMS_4)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_ALGORITHMS_5_VALUE, DONT_CREATE_STRUCT, "007.000", "")
        VALUE_CONST(AttributeValue, "Value", AUD_DSP_ALGORITHMS_5)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_ACA_ALGORITHMS_VALUE, DONT_CREATE_STRUCT, "009.011", "")
        VALUE_CONST(AttributeValue, "Value", AUD_DSP_ACA_ALGORITHMS)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_ACA_ALGORITHMS_MASK_VALUE, DONT_CREATE_STRUCT, "009.011", "")
        VALUE_CONST(AttributeValue, "Value", AUD_DSP_ACA_ALGORITHMS)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_PARAMS_VALUE, DONT_CREATE_STRUCT, "", "")
        CHOICE_BEGIN(AttributeValue, "Value", ID)
            CASE(AUD_DSP_ALGORITHMS_1,    AUD_DSP_ALGORITHMS_1_VALUE)
            CASE(AUD_DSP_ALGORITHMS_2,    AUD_DSP_ALGORITHMS_2_VALUE)
            CASE(AUD_DSP_PHAP        ,    AUD_DSP_PHAP_VALUE)
            CASE_VER(AUD_DSP_ALGORITHMS_3,    AUD_DSP_ALGORITHMS_3_VALUE, "007.000", "")
            CASE_VER(AUD_DSP_ALGORITHMS_4,    AUD_DSP_ALGORITHMS_4_VALUE, "007.000", "")
            CASE_VER(AUD_DSP_ALGORITHMS_5,    AUD_DSP_ALGORITHMS_5_VALUE, "007.000", "")
            CASE_VER(AUD_DSP_ACA_ALGORITHMS,      AUD_DSP_ACA_ALGORITHMS_VALUE,      "009.011", "")
            CASE_VER(AUD_DSP_ACA_ALGORITHMS_MASK, AUD_DSP_ACA_ALGORITHMS_MASK_VALUE, "009.011", "")
            CASE_DEFAULT(AUD_DEFAULT_VALUE)
        CHOICE_END
    SEQ_END

    /* DTMF attribute values */

    SEQ_BEGIN(AUD_DTMF_SWITCH_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_SWITCH_VALUES)
    SEQ_END

    SEQ_BEGIN(AUD_DTMF_DIGIT_VALUE, DONT_CREATE_STRUCT, "", "")
        STRING(STRING_UNICODE, BE, AttributeValue, "Value", 1)
    SEQ_END

    SEQ_BEGIN(AUD_DTMF_VOLUME_LEVEL_VALUE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 10)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, AUD_PAUSE)
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SEQ_END

    SEQ_BEGIN(AUD_DTMF_VALUE, DONT_CREATE_STRUCT, "", "")
        CHOICE_BEGIN(AttributeValue, "Value", ID)
            CASE(AUD_DTMF_SWITCH,       AUD_DTMF_SWITCH_VALUE)
            CASE(AUD_DTMF_DIGIT,        AUD_DTMF_DIGIT_VALUE)
            CASE(AUD_DTMF_VOLUME_LEVEL, AUD_DTMF_VOLUME_LEVEL_VALUE)
            CASE_DEFAULT(AUD_DEFAULT_VALUE)
        CHOICE_END
    SEQ_END


    /* Tone attribute values */

    SEQ_BEGIN(AUD_TONE_SWITCH_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_SWITCH_VALUES)
    SEQ_END

    SEQ_BEGIN(AUD_TONE_FREQUENCY_VALUE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 65535)
        VALUE_EX(16, BE, AttributeValue, "Value", DEC, 1.0, 0.0, "Hz")
    SEQ_END

    SEQ_BEGIN(AUD_TONE_VOLUME_LEVEL_VALUE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 10)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, AUD_PAUSE)
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SEQ_END

    SEQ_BEGIN(AUD_TONE_SEQUENCE_TYPE_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_TONE_SEQUENCE_TYPE)
    SEQ_END

    SEQ_BEGIN(AUD_TONE_VALUE, DONT_CREATE_STRUCT, "", "")
        CHOICE_BEGIN(AttributeValue, "Value", ID)
            CASE(AUD_TONE_SWITCH_1,       AUD_TONE_SWITCH_VALUE)
            CASE(AUD_TONE_FREQUENCY_1,    AUD_TONE_FREQUENCY_VALUE)
            CASE(AUD_TONE_VOLUME_LEVEL_1, AUD_TONE_VOLUME_LEVEL_VALUE)
            CASE(AUD_TONE_SWITCH_2,       AUD_TONE_SWITCH_VALUE)
            CASE(AUD_TONE_FREQUENCY_2,    AUD_TONE_FREQUENCY_VALUE)
            CASE(AUD_TONE_VOLUME_LEVEL_2, AUD_TONE_VOLUME_LEVEL_VALUE)
            CASE(AUD_TONE_SWITCH_3,       AUD_TONE_SWITCH_VALUE)
            CASE(AUD_TONE_FREQUENCY_3,    AUD_TONE_FREQUENCY_VALUE)
            CASE(AUD_TONE_VOLUME_LEVEL_3, AUD_TONE_VOLUME_LEVEL_VALUE)
            CASE(AUD_TONE_SWITCH_4,       AUD_TONE_SWITCH_VALUE)
            CASE(AUD_TONE_FREQUENCY_4,    AUD_TONE_FREQUENCY_VALUE)
            CASE(AUD_TONE_VOLUME_LEVEL_4, AUD_TONE_VOLUME_LEVEL_VALUE)
            CASE(AUD_TONE_SEQUENCE_TYPE,  AUD_TONE_SEQUENCE_TYPE_VALUE)
            CASE_DEFAULT(AUD_DEFAULT_VALUE)
        CHOICE_END
    SEQ_END


    /* Mixer attribute values */

    SEQ_BEGIN(AUD_MIXER_SWITCH_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_SWITCH_VALUES)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_UL_IN_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_MIXER_UL_IN_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_DTMF_OUT_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_MIXER_DTMF_OUT_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_TONE_OUT_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_MIXER_TONE_OUT_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_DL_OUT_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_MIXER_DL_OUT_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_MODE_OUT_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(AttributeValue, "Value",ID, AUD_MIXER_MODE_OUT_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_QUALITY_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(AttributeValue, "Value",ID, AUD_MIXER_QUALITY_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_APP_IN_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(AttributeValue, "Value",ID, AUD_MIXER_APP_IN_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_APP_UL_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(AttributeValue, "Value",ID, AUD_MIXER_APP_UL_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_APP_REC_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(AttributeValue, "Value",ID, AUD_MIXER_APP_REC_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_DL_OUT_TRANSMIT_VALUE, DONT_CREATE_STRUCT, "006.009", "")
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(AttributeValue, "Value",ID, AUD_MIXER_DL_OUT_TRANSMIT_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_PLAYBACK_MODE_VALUE, DONT_CREATE_STRUCT, "007.007", "")
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(AttributeValue, "Value",ID, AUD_MIXER_PLAYBACK_MODE_SELECT)
    SEQ_END

    SEQ_BEGIN(AUD_MIXER_VALUE, DONT_CREATE_STRUCT, "", "")
        CHOICE_BEGIN(AttributeValue, "Value", ID)
            CASE(AUD_MIXER_UL_POWER_SWITCH, AUD_MIXER_SWITCH_VALUE)
            CASE(AUD_MIXER_UL_IN_SELECT,    AUD_MIXER_UL_IN_VALUE)
            CASE(AUD_MIXER_UL_IN_SWITCH,    AUD_MIXER_SWITCH_VALUE)
            CASE(AUD_MIXER_UL_OUT_SWITCH,   AUD_MIXER_SWITCH_VALUE)
            CASE(AUD_MIXER_DTMF_OUT_SELECT, AUD_MIXER_DTMF_OUT_VALUE)
            CASE(AUD_MIXER_TONE_OUT_SELECT, AUD_MIXER_TONE_OUT_VALUE)
            CASE(AUD_MIXER_DL_POWER_SWITCH, AUD_MIXER_SWITCH_VALUE)
            CASE(AUD_MIXER_DL_IN_SWITCH,    AUD_MIXER_SWITCH_VALUE)
            CASE(AUD_MIXER_DL_OUT_SWITCH,   AUD_MIXER_SWITCH_VALUE)
            CASE(AUD_MIXER_DL_OUT_SELECT,   AUD_MIXER_DL_OUT_VALUE)
            CASE(AUD_MIXER_MODE_OUT_SELECT, AUD_MIXER_MODE_OUT_VALUE)
            CASE(AUD_MIXER_QUALITY_SELECT,  AUD_MIXER_QUALITY_VALUE)
            CASE(AUD_MIXER_APP_IN_SELECT,   AUD_MIXER_APP_IN_VALUE)
            CASE(AUD_MIXER_APP_UL_SELECT,   AUD_MIXER_APP_UL_VALUE)
            CASE(AUD_MIXER_APP_REC_SELECT,  AUD_MIXER_APP_REC_VALUE)
            CASE_VER(AUD_MIXER_DL_OUT_TRANSMIT_SELECT, AUD_MIXER_DL_OUT_TRANSMIT_VALUE, "006.009", "")
            CASE_VER(AUD_MIXER_PLAYBACK_MODE_SELECT, AUD_MIXER_PLAYBACK_MODE_VALUE, "007.007", "")
            CASE_VER(AUD_MIXER_APE_SPEECH_TONE_SWITCH, AUD_MIXER_SWITCH_VALUE, "008.000", "")
            CASE_VER(AUD_MIXER_SIDETONE_SWITCH, AUD_MIXER_SWITCH_VALUE, "009.014", "")
            CASE_DEFAULT(AUD_DEFAULT_VALUE)
        CHOICE_END
    SEQ_END


    /* Mode attribute values */

    SEQ_BEGIN(AUD_MODE_ANA_DIGI_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_MODE_ANA_DIGI)
    SEQ_END

    SEQ_BEGIN(AUD_MODE_ACCESSORY_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_MODE_VALUES)
    SEQ_END

    SEQ_BEGIN(AUD_MODE_SECONDARY_VALUE, DONT_CREATE_STRUCT, "008.019", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_MODE_VALUES)
    SEQ_END

    SEQ_BEGIN(AUD_MODE_VALUE, DONT_CREATE_STRUCT, "", "")
        CHOICE_BEGIN(AttributeValue, "Value", ID)
            CASE(AUD_MODE_ANA_DIGI,     AUD_MODE_ANA_DIGI_VALUE)
            CASE(AUD_MODE_ACCESSORY,    AUD_MODE_ACCESSORY_VALUE)
            CASE_VER(AUD_MODE_SECONDARY,    AUD_MODE_SECONDARY_VALUE, "008.019", "")
            CASE_DEFAULT(AUD_DEFAULT_VALUE)
        CHOICE_END
    SEQ_END


    /* Digital out attribute value */

    SEQ_BEGIN(AUD_DIGITAL_OUT_VALUE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SEQ_END


    /* Mute attribute value */

    SEQ_BEGIN(AUD_MUTE_SWITCH_VALUE, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(AttributeValue, "Value", AUD_SWITCH_VALUES)
    SEQ_END

    SEQ_BEGIN(AUD_MUTE_VALUE, DONT_CREATE_STRUCT, "", "")
        CHOICE_BEGIN(AttributeValue, "Value", ID)
            CASE(AUD_ANA_MUTE_SWITCH,       AUD_MUTE_SWITCH_VALUE)
            CASE(AUD_DIGI_MUTE_SWITCH,      AUD_MUTE_SWITCH_VALUE)
            CASE_DEFAULT(AUD_DEFAULT_VALUE)
        CHOICE_END
    SEQ_END
    
    /* Selftest attribute values */

    /* Audio loopback data sequences */
    
    SEQ_BEGIN(AUD_LOOPBACK_INPUT_DATA, CREATE_STRUCT, "009.009", "")
        VALUE_CONST(Input, "Input", AUD_LOOPBACK_IN_SELECT)
        VALUE_CONST(InputMode, "Input mode", AUD_INPUT_OUTPUT_MODE)
        FILLER(FILLER_FIXED, 16)
    SEQ_END
    
    SEQ_BEGIN(AUD_LOOPBACK_OUTPUT_DATA, CREATE_STRUCT, "009.009", "")
        VALUE_CONST(Output, "Output", AUD_LOOPBACK_OUT_SELECT)
        VALUE_CONST(OutputMode, "Output mode", AUD_INPUT_OUTPUT_MODE)
        FILLER(FILLER_FIXED, 16)
    SEQ_END
   

    /* ------------------------------------------------------------------ */
    /* Sequences defining the Attribute ID field */
    /* - with the AUD_ALL_ATRBIUTES flag */
    /* ------------------------------------------------------------------ */

    #define AUD_ATTR_ALL(ATTR) \
        SEQ_BEGIN(AUD_##ATTR##_ATTR_ALL, DONT_CREATE_STRUCT, "", "") \
            VALUE_CONST(AttributeId, "Attribute ID", AUD_##ATTR##_ATTRIBUTES_ALL) \
        SEQ_END \

    AUD_ATTR_ALL(ANALOG_IN)
    AUD_ATTR_ALL(ANALOG_OUT)
    AUD_ATTR_ALL(DSP_PARAMS)
    AUD_ATTR_ALL(DTMF)
    AUD_ATTR_ALL(TONE)
    AUD_ATTR_ALL(MIXER)
    AUD_ATTR_ALL(MODE)
    AUD_ATTR_ALL(DIGITAL_OUT)
    AUD_ATTR_ALL(MUTE)
    AUD_ATTR_ALL(ALL)


    /* ------------------------------------------------------------------ */
    /* Sequences defining the Attribute ID field */
    /* - without the AUD_ALL_ATRBIUTES flag */
    /* ------------------------------------------------------------------ */

    #define AUD_ATTR(ATTR) \
        SEQ_BEGIN(AUD_##ATTR##_ATTR, DONT_CREATE_STRUCT, "", "") \
            VALUE_CONST(AttributeId, "Attribute ID", AUD_##ATTR##_ATTRIBUTES) \
        SEQ_END

    AUD_ATTR(ANALOG_IN)
    AUD_ATTR(ANALOG_OUT)
    AUD_ATTR(DSP_PARAMS)
    AUD_ATTR(DTMF)
    AUD_ATTR(TONE)
    AUD_ATTR(MIXER)
    AUD_ATTR(MODE)
    AUD_ATTR(DIGITAL_OUT)
    AUD_ATTR(MUTE)

    SEQ_BEGIN(AUD_DEFAULT_ATTR, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE,  AttributeId, "Attribute ID", HEX)
    SEQ_END

    /* Sub blocks */


    /* ------------------------------------------------------------------ */
    /* AUD_SERVICE_REPORT */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SERVICE_REPORT" "_LEN")
    SB_BEGIN(AUD_SERVICE_REPORT, "", "")
        AUD_COMMON_SB(tISI_AudServiceReport)
        VALUE_CONST(ServiceId, "Service ID", AUD_SERVICES)
        VALUE_CONST(AttributeSetup, "Attribute Configuration", AUDIO_SERVICE_CONFIGURATIONS)
    SB_END


    /* ------------------------------------------------------------------ */
    /* AUD_ATTRIBUTE_SETUP_REPORT */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTRIBUTE_SETUP_REPORT" "_LEN")
    SB_BEGIN(AUD_ATTRIBUTE_SETUP_REPORT, "", "")
        AUD_COMMON_SB(tISI_AudAttributeSetupReport)
        CHOICE_BEGIN(AttributeId, "Attribute ID", SERVICE)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_ATTR)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_ATTR)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_ATTR)
            CASE(AUD_DTMF,          AUD_DTMF_ATTR)
            CASE(AUD_TONE,          AUD_TONE_ATTR)
            CASE(AUD_MIXER,         AUD_MIXER_ATTR)
            CASE(AUD_MODE,          AUD_MODE_ATTR)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_ATTR)
            CASE(AUD_MUTE,          AUD_MUTE_ATTR)
            CASE_DEFAULT(AUD_DEFAULT_ATTR)
        CHOICE_END
        FILLER_EX(Spare1, 8, 1)
        COMMENT(COMMENT_TEXT,
            "Value in the default service layer")
        VALUE(16, BE, DefaultValue, "Default Value", DEC)
        COMMENT(COMMENT_TEXT,
            "The smallest available value for the attribute")
        VALUE(16, BE, MinimumValue, "Min Value", DEC)
        COMMENT(COMMENT_TEXT,
            "The largest available value for the attribute")
        VALUE(16, BE, MaximumValue, "Max Value", DEC)
        FILLER_EX(Spare2, 16, 1)
    SB_END


    /* ------------------------------------------------------------------ */
    /* AUD_SETTING_REPORT */
    /* ------------------------------------------------------------------ */

    /* Analog in attribute values */
    SEQ_BEGIN(AUD_ANALOG_IN_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(AttributeId, "Attribute ID", AUD_ANALOG_IN_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_DEFAULT_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END

    /* Analog out attribute values */
    SEQ_BEGIN(AUD_ANALOG_OUT_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        REFERENCE_CONST(AttributeId, "Attribute ID",ID, AUD_ANALOG_OUT_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_ANALOG_OUT_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END


    /* ------------------------------------------------------------------ */
    /* AUD_DSP_PARBLOCK */
    /* ------------------------------------------------------------------ */

    #define AUD_DSP_MAX_PARDATA_LEN 128 /* Max bytes in DSP param block */

    SEQ_BEGIN(AUD_PARAMETER_BLOCK, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, DataBlockFrame, "Parameter block", HEX)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_DSP_PARBLOCK" "_LEN")
    SB_BEGIN(AUD_DSP_PARBLOCK, "", "")
        AUD_COMMON_SB(tISI_AudDSPParblock)
        COMMENT(COMMENT_TEXT,
            "The number of actual parameter data bytes in the data block")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, AUD_DSP_MAX_PARDATA_LEN)
        VALUE(8, BE, DataBlockLength, "Actual block length", DEC)
        FILLER_EX(Spare, 8, 1)
        SEQ_OF(DataBlockFrame, "Parameter block", AUD_PARAMETER_BLOCK, AUD_DSP_MAX_PARDATA_LEN)
    SB_END


    /* DSP params attribute values */

    SEQ_BEGIN(AUD_DSP_PARAM_BLOCK_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        SEQ_OF(dsp_block, "Parameter block", AUD_DSP_PARBLOCK, 1)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_PARAM_BLOCK_SETTING_DEF_SEQ, DONT_CREATE_STRUCT, "", "")
    SEQ_END

    SEQ_BEGIN(AUD_DSP_PARAMS_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        REFERENCE_CONST(AttributeId, "Attribute ID", ID, AUD_DSP_PARAMS_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_DSP_PARAMS_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
        CHOICE_BEGIN(DSPParblock, "DSP Parblock", ID)
            CASE(AUD_DSP_PARAM_BLOCK,     AUD_DSP_PARAM_BLOCK_SETTING_SEQ)
            CASE_DEFAULT(AUD_DSP_PARAM_BLOCK_SETTING_DEF_SEQ)
        CHOICE_END
    SEQ_END


    /* DTMF attribute values */

    SEQ_BEGIN(AUD_DTMF_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        REFERENCE_CONST(AttributeId, "Attribute ID", ID, AUD_DTMF_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_DTMF_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END


    /* Tone attribute values */

    SEQ_BEGIN(AUD_TONE_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        REFERENCE_CONST(AttributeId, "Attribute ID", ID, AUD_TONE_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_TONE_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END


    /* Mixer attribute values */

    SEQ_BEGIN(AUD_MIXER_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        REFERENCE_CONST(AttributeId, "Attribute ID", ID, AUD_MIXER_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_MIXER_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END


    /* Mode attribute values */
    SEQ_BEGIN(AUD_MODE_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        REFERENCE_CONST(AttributeId, "Attribute ID", ID, AUD_MODE_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_MODE_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END


    /* Digital out attribute values */

    SEQ_BEGIN(AUD_DIGITAL_OUT_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(AttributeId, "Attribute ID", AUD_DIGITAL_OUT_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_DEFAULT_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END

    /* Mute attribute values */

    SEQ_BEGIN(AUD_MUTE_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(AttributeId, "Attribute ID", AUD_MUTE_ATTRIBUTES)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(AttributeValue, "Value", AUD_DEFAULT_VALUE, 1)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END

    /* Default attributes values */

    SEQ_BEGIN(AUD_DEFAULT_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, AttributeId, "Attribute ID", HEX)
        FILLER_EX(Spare1, 8, 1)
        VALUE(16, BE, AttributeValue, "Value", DEC)
        FILLER_EX(Spare2, 16, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SETTING_REPORT" "_LEN")
    SB_BEGIN(AUD_SETTING_REPORT, "", "")
        AUD_COMMON_SB(tISI_AudSettingReport)
        CHOICE_BEGIN(AttributeValue, "Value", SERVICE)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_SETTING_SEQ)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_SETTING_SEQ)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_SETTING_SEQ)
            CASE(AUD_DTMF,          AUD_DTMF_SETTING_SEQ)
            CASE(AUD_TONE,          AUD_TONE_SETTING_SEQ)
            CASE(AUD_MIXER,         AUD_MIXER_SETTING_SEQ)
            CASE(AUD_MODE,          AUD_MODE_SETTING_SEQ)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_SETTING_SEQ)
            CASE(AUD_MUTE,          AUD_MUTE_SETTING_SEQ)
            CASE_DEFAULT(AUD_DEFAULT_SETTING_SEQ)
        CHOICE_END
    SB_END


    /* AUD_ATTACH_ACCESSORY_EVENT_REQ related sequenses */
    SEQ_BEGIN(ACC_SUBTYPE_OTHER, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_OTHER)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_HEADSET, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_HD)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_HANDSFREE, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_HF)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_DATACABLE, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_DC)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_TEST_DEVICE, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_TD)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_CAMERA, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_CAM)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_MISC, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_MISC)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_ADAPTER, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_ADAPTER)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_NO_INFORMATION, DONT_CREATE_STRUCT, "005.027", "")
      VALUE_CONST(sub_type, "SubType", ACC_THWK_SUB_TYPE_NO_INFORMATION)
    SEQ_END

    SEQ_BEGIN(ACC_SUBTYPE_DEFAULT, DONT_CREATE_STRUCT, "005.027", "")
      VALUE(8, BE, sub_type, "SubType", HEX)
    SEQ_END
    
    /* ------------------------------------------------------------------ */
    /* AUD_LAYER_SETTING */
    /* ------------------------------------------------------------------ */

    SEQ_BEGIN(AUD_LAYER_SETTING_DEFAULT_OP, DONT_CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT,
            "This value is added to / subtracted from the current attribute value")
        VALUE(16, BE, AttributeValue, "Value", DEC)
        FILLER_EX(Spare, 16, 1)
    SEQ_END

    #define AUD_LAYER_SETTING_SEQ(ATTR) \
        SEQ_BEGIN(AUD_LAYER_SETTING_##ATTR, DONT_CREATE_STRUCT, "", "") \
            SEQ_OF(AttributeValue, "Value", AUD_##ATTR##_VALUE, 1) \
            FILLER_EX(Spare, 16, 1) \
        SEQ_END \
        SEQ_BEGIN(AUD_##ATTR##_LAYER_SETTING_SEQ, DONT_CREATE_STRUCT, "", "") \
            REFERENCE_CONST(AttributeId, "Attribute ID", ID, AUD_##ATTR##_ATTRIBUTES) \
            REFERENCE_CONST(Operation, "Operation", OP, AUD_ATTRIBUTE_SETTING_OPERATIONS) \
            CHOICE_BEGIN(AttributeValue, "Value", OP) \
                CASE(AUD_VALUE_SUBSTITUTE, AUD_LAYER_SETTING_##ATTR) \
                CASE_DEFAULT(AUD_LAYER_SETTING_DEFAULT_OP) \
            CHOICE_END \
        SEQ_END


    AUD_LAYER_SETTING_SEQ(ANALOG_IN)
    AUD_LAYER_SETTING_SEQ(ANALOG_OUT)
    AUD_LAYER_SETTING_SEQ(DTMF)
    AUD_LAYER_SETTING_SEQ(TONE)
    AUD_LAYER_SETTING_SEQ(MIXER)
    AUD_LAYER_SETTING_SEQ(MODE)
    AUD_LAYER_SETTING_SEQ(DIGITAL_OUT)
    AUD_LAYER_SETTING_SEQ(MUTE)

    SEQ_BEGIN(AUD_LAYER_SETTING_DSP_PARAMS, DONT_CREATE_STRUCT, "", "")
        SEQ_OF(AttributeValue, "Value", AUD_DSP_PARAMS_VALUE, 1)
        FILLER_EX(Spare, 16, 1)
    SEQ_END

    SEQ_BEGIN(AUD_DSP_PARAMS_LAYER_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        REFERENCE_CONST(AttributeId, "Attribute ID", ID, AUD_DSP_PARAMS_ATTRIBUTES)
        REFERENCE_CONST(Operation, "Operation", OP, AUD_ATTRIBUTE_SETTING_OPERATIONS)
        CHOICE_BEGIN(AttributeValue, "Value", OP)
            CASE(AUD_VALUE_SUBSTITUTE, AUD_LAYER_SETTING_DSP_PARAMS)
            CASE_DEFAULT(AUD_LAYER_SETTING_DEFAULT_OP)
        CHOICE_END
        CHOICE_BEGIN(DSPParblock, "DSP Parblock", ID)
            CASE(AUD_DSP_PARAM_BLOCK, AUD_DSP_PARAM_BLOCK_SETTING_SEQ)
            CASE_DEFAULT(AUD_DSP_PARAM_BLOCK_SETTING_DEF_SEQ)
        CHOICE_END
    SEQ_END

    SEQ_BEGIN(AUD_DEFAULT_LAYER_SETTING_SEQ, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, AttributeId, "Attribute ID", HEX)
        VALUE_CONST(Operation, "Operation", AUD_ATTRIBUTE_SETTING_OPERATIONS)
        VALUE(16, BE, AttributeValue, "Value", DEC)
        FILLER_EX(Spare, 16, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_SETTING" "_LEN")
    SB_BEGIN(AUD_LAYER_SETTING, "", "")
        AUD_COMMON_SB(tISI_AudLayerSetting)
        CHOICE_BEGIN(AttributeID, "Attribute ID", SERVICE)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_LAYER_SETTING_SEQ)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_LAYER_SETTING_SEQ)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_LAYER_SETTING_SEQ)
            CASE(AUD_DTMF,          AUD_DTMF_LAYER_SETTING_SEQ)
            CASE(AUD_TONE,          AUD_TONE_LAYER_SETTING_SEQ)
            CASE(AUD_MIXER,         AUD_MIXER_LAYER_SETTING_SEQ)
            CASE(AUD_MODE,          AUD_MODE_LAYER_SETTING_SEQ)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_LAYER_SETTING_SEQ)
            CASE(AUD_MUTE,          AUD_MUTE_LAYER_SETTING_SEQ)
            CASE_DEFAULT(AUD_DEFAULT_LAYER_SETTING_SEQ)
        CHOICE_END
    SB_END


    /* ------------------------------------------------------------------ */
    /* AUD_ATTRIBUTE_LAYER_REPORT */
    /* ------------------------------------------------------------------ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTRIBUTE_LAYER_REPORT" "_LEN")
    SB_BEGIN(AUD_ATTRIBUTE_LAYER_REPORT, "", "")
        AUD_COMMON_SB(tISI_AudAttributeLayerReport)
        CHOICE_BEGIN(AttributeID, "Attribute ID", SERVICE)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_ATTR)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_ATTR)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_ATTR)
            CASE(AUD_DTMF,          AUD_DTMF_ATTR)
            CASE(AUD_TONE,          AUD_TONE_ATTR)
            CASE(AUD_MIXER,         AUD_MIXER_ATTR)
            CASE(AUD_MODE,          AUD_MODE_ATTR)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_ATTR)
            CASE(AUD_MUTE,          AUD_MUTE_ATTR)
            CASE_DEFAULT(AUD_DEFAULT_ATTR)
        CHOICE_END
        VALUE_CONST(Event, "Event", AUD_LAYER_UPDATE_ATTR_EVENTS)
        COMMENT(COMMENT_PARAGRAPH,
            "Type of the client that owns the effective layer for the service attribute from now on")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: AUD_NO_CLIENT_TYPE means that no client's layer affects this attribute, the default value is in effect")
        VALUE_CONST(ClientType, "Client Type", AUD_CLIENT_TYPES)
        FILLER_EX(Spare1, 8, 1)
        VALUE(16, BE, AttributeValue, "Value", DEC)
    SB_END


    /* ------------------------------------------------------------------ */
    /* AUD_ATTRIBUTE_UPDATE_REPORT */
    /* ------------------------------------------------------------------ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTRIBUTE_UPDATE_REPORT" "_LEN")
    SB_BEGIN(AUD_ATTRIBUTE_UPDATE_REPORT, "", "")
        AUD_COMMON_SB(tISI_AudAttributeUpdateReport)
        CHOICE_BEGIN(AttributeID, "Attribute ID", SERVICE)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_ATTR)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_ATTR)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_ATTR)
            CASE(AUD_DTMF,          AUD_DTMF_ATTR)
            CASE(AUD_TONE,          AUD_TONE_ATTR)
            CASE(AUD_MIXER,         AUD_MIXER_ATTR)
            CASE(AUD_MODE,          AUD_MODE_ATTR)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_ATTR)
            CASE(AUD_MUTE,          AUD_MUTE_ATTR)
            CASE_DEFAULT(AUD_DEFAULT_ATTR)
        CHOICE_END
        COMMENT(COMMENT_TEXT,
            "NOTE: NOT_ALLOWED and VALUE_NOT_OK statuses are error "
            "indications. For them, 'Efficiency' must always be regarded as INEFFECTIVE")
        VALUE_CONST(Status, "Status", AUD_LAYER_UPDATE_ATTR_SPEC_STATUS)
        VALUE_CONST(Efficiency, "Efficiency", AUD_LAYER_UPDATE_ATTR_EFFICIENCY)
        FILLER_EX(Spare1, 8, 1)
        FILLER_EX(Spare2, 16, 1)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_VOLUME_CONTROL_SB */
    /* ------------------------------------------------------------------ */
    SB_BEGIN(AUD_VOLUME_CONTROL_SB, "006.013", "")
        AUD_COMMON_SB_NEW

        COMMENT(COMMENT_TEXT,  "Informs which media type volume is controlled (only one value can be selected in this message)")
        VALUE_CONST(media_type, "Media type", AUD_VOLUME_MEDIA_TYPE)

        COMMENT(COMMENT_TEXT,  "Informs is control in %-format or in Q8.7 format")
        VALUE_CONST(control_format, "Control format", AUD_VOLUME_CONTROL_TYPE)

        FILLER(FILLER_FIXED, 8)
        FILLER(FILLER_FIXED, 16)

        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT(COMMENT_TEXT,  "Primary mode volume in % format (range 0 - 1000, meaning 45.5% is 455)")
        VALUE(16, BE, pri_volume_in_percetance, "Primary volume in percetance", DEC)
        COMMENT(COMMENT_TEXT,  "Primary mode volume in Q8.7 format")
        VALUE(-16, BE, pri_volume_in_q87, "Primary volume in Q87", DEC)

        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT(COMMENT_TEXT,  "Secondary mode volume in % format (range 0 - 1000, meaning 45.5% is 455)")
        VALUE(16, BE, sec_volume_in_percetance, "Secondary volume in percetance", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary mode volume in Q8.7 format")
        VALUE(-16, BE, sec_volume_in_q87, "secondary volume in Q87", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_VOLUME_CONTROL_RESPONSE_SB */
    /* ------------------------------------------------------------------ */
    SB_BEGIN(AUD_VOLUME_CONTROL_RESPONSE_SB, "006.013", "008.012")
        AUD_COMMON_SB_NEW

        COMMENT(COMMENT_TEXT,  "Informs which media type volume was controlled (only one type per subblock)")
        VALUE_CONST(media_type, "Media type", AUD_VOLUME_MEDIA_TYPE)

        COMMENT(COMMENT_TEXT,  "Informs was control in %-format or in Q8.7 format")
        VALUE_CONST(control_format, "Control format", AUD_VOLUME_CONTROL_TYPE)

        FILLER(FILLER_FIXED, 8)
        FILLER(FILLER_FIXED, 16)

     /* For primary mode */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT(COMMENT_TEXT,  "Requested primary mode volume in % format (range 0 - 1000, meaning 45.5% is 455)")
        VALUE(16, BE, requested_pri_volume_in_percetance, "Requested primary volume in percetance", DEC)
        COMMENT(COMMENT_TEXT,  "requested primary mode volume in Q8.7 format")
        VALUE(-16, BE, requested_pri_volume_in_q87, "Requested primary volume in Q87", DEC)
        COMMENT(COMMENT_TEXT,  "Primary actual gain which is achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, pri_actual_gain, "Primary actual gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary missing gain which could not be achieved by Audio syste (Q8.7 format)")
        VALUE(-16, BE, pri_missing_gain, "Primary missing gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary target gain, compensated gain (Q8.7 format)")
        VALUE(-16, BE, pri_target_gain, "Primary target gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary analog gain which is written in hardware (Q8.7 format)")
        VALUE(-16, BE, pri_analog_gain, "Primary analog gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary digital gain which is used to as compensation to target gain (Q8.7 format)")
        VALUE(-16, BE, pri_digital_gain, "Primary digital gain", DEC)

     /* For secondary mode */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT(COMMENT_TEXT,  "Secondary mode volume in % format (range 0 - 1000, meaning 45.5% is 455)")
        VALUE(16, BE, requested_sec_volume_in_percetance, "Requested secondary volume in percetance", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary mode volume in Q8.7 format")
        VALUE(-16, BE, requested_sec_volume_in_q87, "Requested secondary volume in Q87", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary actual gain which is achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, sec_actual_gain, "Secondary actual gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary missing gain which could not be achieved by Audio syste (Q8.7 format)")
        VALUE(-16, BE, sec_missing_gain, "Secondary missing gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary target gain, compensated gain (Q8.7 format)")
        VALUE(-16, BE, sec_target_gain, "Secondary target gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary analog gain which is written in hardware (Q8.7 format)")
        VALUE(-16, BE, sec_analog_gain, "Secondary analog gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary digital gain which is used to as compensation to target gain (Q8.7 format)")
        VALUE(-16, BE, sec_digital_gain,  "Secondary digital gain", DEC)
    SB_END

    /* ------------------------------------------------------------------ */
    /* AUD_VOLUME_CONTROL_RESPONSE_SB */
    /* ------------------------------------------------------------------ */
    SB_BEGIN(AUD_VOLUME_CONTROL_RESPONSE_SB, "008.012", "")
        AUD_COMMON_SB_NEW

        COMMENT(COMMENT_TEXT,  "Informs which media type volume was controlled (only one type per subblock)")
        VALUE_CONST(media_type, "Media type", AUD_VOLUME_MEDIA_TYPE)

        COMMENT(COMMENT_TEXT,  "Informs was control in %-format or in Q8.7 format")
        VALUE_CONST(control_format, "Control format", AUD_VOLUME_CONTROL_TYPE)

        FILLER(FILLER_FIXED, 8)
        FILLER(FILLER_FIXED, 16)

     /* For primary mode */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT(COMMENT_TEXT,  "Requested primary mode volume in % format (range 0 - 1000, meaning 45.5% is 455)")
        VALUE(16, BE, requested_pri_volume_in_percetance, "Requested primary volume in percetance", DEC)
        COMMENT(COMMENT_TEXT,  "Requested primary mode volume in Q8.7 format")
        VALUE(-16, BE, requested_pri_volume_in_q87, "Requested primary volume in Q87", DEC)
        COMMENT(COMMENT_TEXT,  "Primary actual gain which is achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, pri_actual_gain, "Primary actual gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary missing gain which could not be achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, pri_missing_gain, "Primary missing gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary target gain, compensated gain (Q8.7 format)")
        VALUE(-16, BE, pri_target_gain, "Primary target gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary analog gain which is written in hardware (Q8.7 format)")
        VALUE(-16, BE, pri_analog_gain, "Primary analog gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary digital gain which is used to as compensation to target gain (Q8.7 format)")
        VALUE(-16, BE, pri_digital_gain, "Primary digital gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary minimum gain that can be achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, pri_min_gain, "Primary minimum gain", DEC)
        COMMENT(COMMENT_TEXT,  "Primary maximum gain that can be achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, pri_max_gain, "Primary maximum gain", DEC)

     /* For secondary mode */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT(COMMENT_TEXT,  "Requested secondary mode volume in % format (range 0 - 1000, meaning 45.5% is 455)")
        VALUE(16, BE, requested_sec_volume_in_percetance, "Requested secondary volume in percetance", DEC)
        COMMENT(COMMENT_TEXT,  "Requested secondary mode volume in Q8.7 format")
        VALUE(-16, BE, requested_sec_volume_in_q87, "Requested secondary volume in Q87", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary actual gain which is achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, sec_actual_gain, "Secondary actual gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary missing gain which could not be achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, sec_missing_gain, "Secondary missing gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary target gain, compensated gain (Q8.7 format)")
        VALUE(-16, BE, sec_target_gain, "Secondary target gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary analog gain which is written in hardware (Q8.7 format)")
        VALUE(-16, BE, sec_analog_gain, "Secondary analog gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary digital gain which is used to as compensation to target gain (Q8.7 format)")
        VALUE(-16, BE, sec_digital_gain,  "Secondary digital gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary minimum gain that can be achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, sec_min_gain, "Secondary minimum gain", DEC)
        COMMENT(COMMENT_TEXT,  "Secondary maximum gain that can be achieved by Audio system (Q8.7 format)")
        VALUE(-16, BE, sec_max_gain, "Secondary maximum gain", DEC)
    SB_END

   
    /* ------------------------------------------------------------------ */
    /* AUD_EQU_DEFINITION */
    /* ------------------------------------------------------------------ */

    SEQ_BEGIN(AUD_LIMIT_FREQ_SEQ, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 48000)
        VALUE_EX(16, BE, LimitFrequency, "Limit frequency", DEC, 1.0, 0.0, "Hz")
    SEQ_END

    SEQ_BEGIN(AUD_GAIN_SEQ, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, -12)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 12)
        VALUE(-8, BE, BandsGain, "Gain", DEC)
    SEQ_END

    COMMENT(COMMENT_PARAGRAPH,
            "The upper limit frequencies for band 1 to 8 can vary between different"
            "products and is depending on the implementation of the DSP SW. In some"
            "cases the DSP SW may not support the full range.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_INFO_SUB_BLOCK" "_LEN")
    SB_BEGIN(AUD_EQU_DEFINITION, "", "")
        AUD_COMMON_SB(tISI_AudEquInfoSubBlock)
        FILLER_EX(Spare1, 8, 1)
        FILLER_EX(Spare2, 8, 1)
        COMMENT(COMMENT_TEXT, "Upper limit frequency of the x'th band")
        SEQ_OF(LimitFrequency, "Limit Frequency", AUD_LIMIT_FREQ_SEQ, 8)
        COMMENT(COMMENT_TEXT, "Gain of the x'th band")
        SEQ_OF(BandsGain, "Gain", AUD_GAIN_SEQ, 8)
        FILLER_EX(Spare3, 8, 1)
        COMMENT(COMMENT_TEXT, "Length of equalizer name")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 20)
        REFERENCE(8, BE, NameLength, "Name length", NL)
        STRING_REF(STRING_UNICODE, BE, Name, "Name", NL, ISIHDR_MARKER_SINGLE_ELEMENT)
        COMMENT(COMMENT_ISIHDR_DONT_GENERATE, "")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16  Fillers;")
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_COMM_FTD_DATA_BYTE_STR" "_LEN")
    SB_BEGIN(AUD_COMM_FTD_DATA_BYTE, "", "")
      AUD_COMMON_FTD_SB(AUD_COMM_FTD_DATA_BYTE_STR)
      COMMENT(COMMENT_TEXT, "FTD data byte")
      VALUE(8, BE, data, "Data", DEC)
    SB_END


    /* ------------------------------------------------------------------ */
    /* AUD_EQU_GENERAL_INFO */
    /* ------------------------------------------------------------------ */

    SEQ_BEGIN(AUD_EQU_BANDWIDTH_SEQ, DONT_CREATE_STRUCT, "006.010", "")
        VALUE(16, BE, Bandwidth, "Bandwidth", DEC)
    SEQ_END

    SEQ_BEGIN(AUD_EQU_CENTER_FREQ_SEQ, DONT_CREATE_STRUCT, "006.010", "")
        VALUE(16, BE, CenterFreq, "CenterFreq", DEC)
    SEQ_END

    SEQ_BEGIN(AUD_EQU_CROSS_OVER_FREQ_SEQ, DONT_CREATE_STRUCT, "006.010", "")
        VALUE(16, BE, CrossOverFreq, "CrossOverFreq", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_GENERAL_INFO" "_LEN")
    SB_BEGIN(AUD_EQU_GENERAL_INFO, "006.010", "")
        AUD_COMMON_SB(tISI_AudEquGeneralInfoSubBlock)
        COMMENT( COMMENT_TEXT, "Max number of equ's")
        VALUE(8, BE, EquMaxNum, "EquMaxNum", DEC)
        COMMENT( COMMENT_TEXT, "Number of preset equ's")
        VALUE(8, BE, EquPresetNum, "EquPresetNum", DEC)
        COMMENT( COMMENT_TEXT, "Minimum gain")
        VALUE(-8, BE, GainMin, "GainMin", DEC)
        COMMENT( COMMENT_TEXT, "Maximum gain")
        VALUE(-8, BE, GainMax, "GainMax", DEC)
        COMMENT( COMMENT_TEXT, "Maximum number of bands")
        VALUE(8, BE, BandsMaxNum, "BandsMaxNum", DEC)
        FILLER_EX(Spare1, 8, 1)
        SEQ_OF(Bandwidth, "Bandwidth", AUD_EQU_BANDWIDTH_SEQ, 8)
        SEQ_OF(CenterFreq, "CenterFreq", AUD_EQU_CENTER_FREQ_SEQ, 8)
        SEQ_OF(CrossOverFreq, "CrossOverFreq", AUD_EQU_CROSS_OVER_FREQ_SEQ, 7)
        FILLER_EX(Spare2, 16, 1)
    SB_END
    
    /* ------------------------------------------------------------------ */
    /* AUD_LOOPBACK_REQ */
    /* ------------------------------------------------------------------ */
    SEQ_BEGIN(AUD_LOOPBACK_TONE_GEN_PARAMS_SEQ, CREATE_STRUCT, "010.000", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0xFFFF)
        COMMENT(COMMENT_PARAGRAPH, 
                "Digital gain for tone generator output, linear value; "
                "0 db gain equals 0xFFFF")
        VALUE(16, BE, gain, "Tone Gain", HEX)
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        COMMENT(COMMENT_TEXT, "1st Frequency (Hz)")
        VALUE(16, BE, tone_frequency_1, "1st Tone Frequency (Hz)", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        COMMENT(COMMENT_TEXT, "2nd Frequency (Hz)")
        VALUE(16, BE, tone_frequency_2, "2nd Tone Frequency (Hz)", DEC)
        FILLER(FILLER_FIXED, 16)
    SEQ_END

    SEQ_BEGIN(AUD_LOOPBACK_IN_OUT_PARAMS_SEQ, CREATE_STRUCT, "010.000", "")
        COMMENT(COMMENT_TEXT, "Gain for input")
        COMMENT(COMMENT_TEXT, "dB in Q14.1 format, step is 0.5 db")
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, AUD_LOOPBACK_GAIN_DEFAULT)
        VALUE(16, BE, gain, "Gain", HEX)
        COMMENT(COMMENT_TEXT, "Input/output mode")
        VALUE_CONST(mode, "Mode", AUD_INPUT_OUTPUT_MODE)
        FILLER(FILLER_FIXED, 8)
    SEQ_END

    SEQ_BEGIN(AUD_LOOPBACK_OFF_SEQ, DONT_CREATE_STRUCT, "010.000", "")
        COMMENT(COMMENT_TEXT, "Muted")
    SEQ_END
    
    SEQ_BEGIN(AUD_LOOPBACK_SIG_ANALYSIS_FREQ_SEQ, DONT_CREATE_STRUCT, "010.000", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(16, BE, frequency_1, "Frequency (Hz)", DEC)
    SEQ_END

    SEQ_BEGIN(AUD_LOOPBACK_SIG_ANALYSIS_PARAMS_SEQ, DONT_CREATE_STRUCT, "010.000", "")
        COMMENT(COMMENT_TEXT, "Frequencies to detect in Hz")
        SEQ_OF(Frequencies, "Frequencies to detect", AUD_LOOPBACK_SIG_ANALYSIS_FREQ_SEQ, 2)
        COMMENT(COMMENT_TEXT, "Analysis time (ms)")
        VALUE(32, BE, time, "Analysis Time (ms)", DEC)
    SEQ_END

    SB_BEGIN(AUD_LOOPBACK_INPUT_GAIN_SB, "009.009", "")
        COMMON_SB_LONG
        VALUE_CONST(input, "Input", AUD_LOOPBACK_IN_SELECT)
        FILLER_EX(Filler, 8, 1)
        COMMENT(COMMENT_TEXT, "dB in Q14.1 format, step is 0.5 db")
        VALUE(16, BE, gain, "Gain", HEX)
    SB_END

    SB_BEGIN(AUD_LOOPBACK_OUTPUT_GAIN_SB, "009.009", "")
        COMMON_SB_LONG
        VALUE_CONST(output, "Output", AUD_LOOPBACK_OUT_SELECT)
        FILLER_EX(Filler, 8, 1)
        COMMENT(COMMENT_TEXT, "dB in Q14.1 format, step is 0.5 db")
        VALUE(16, BE, gain, "Gain", HEX)
    SB_END

    SB_BEGIN(AUD_LOOPBACK_IN_PARAMS_SB, "010.000", "")
        AUD_COMMON_SB_NEW
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(input, "Input selection", INPUT, AUD_LOOPBACK_IN_SELECT)
        CHOICE_BEGIN(input_value, "Input value", INPUT)
            CASE(AUD_LOOPBACK_OFF, AUD_LOOPBACK_OFF_SEQ)
            CASE(AUD_LOOPBACK_IN_HP_MIC, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_IN_HP_MIC2, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_IN_AV_MIC, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_IN_FM_MIC, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_IN_USB_MIC, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_IN_EANC_MIC1, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_IN_EANC_MIC2, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_IN_TONE_GENERATOR, AUD_LOOPBACK_TONE_GEN_PARAMS_SEQ)
        CHOICE_END
    SB_END


    SB_BEGIN(AUD_LOOPBACK_OUT_PARAMS_SB, "010.000", "")
        AUD_COMMON_SB_NEW
        FILLER(FILLER_FIXED, 8)
        REFERENCE_CONST(output, "Output selection", OUTPUT, AUD_LOOPBACK_OUT_SELECT)
        CHOICE_BEGIN(output_value, "Output value", OUTPUT)
            CASE(AUD_LOOPBACK_OFF, AUD_LOOPBACK_OFF_SEQ)
            CASE(AUD_LOOPBACK_OUT_HP, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_OUT_IHF, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_OUT_AV, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_OUT_USB, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_OUT_HAC, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_OUT_FM_TX, AUD_LOOPBACK_IN_OUT_PARAMS_SEQ)
            CASE(AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS, AUD_LOOPBACK_SIG_ANALYSIS_PARAMS_SEQ)
        CHOICE_END
    SB_END
    
    SB_BEGIN(AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB, "010.000", "")
        AUD_COMMON_SB_NEW
        SEQ_OF(Frequencies, "Frequencies detected (Hz)", AUD_LOOPBACK_SIG_ANALYSIS_FREQ_SEQ, 2)
        FILLER(FILLER_FIXED, 16)
    SB_END

    /* ISI Messages */


    /* ------------------------------------------------------------------ */
    /* AUD_REGISTER_IN */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTER_IN_REQ" "_LEN")
    MSG_BEGIN(AUD_REGISTER_IN_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudRegisterInReq)
        COMMENT(COMMENT_TEXT,
            "NOTE: Restricting available client types to those above is necessary\
             to enable efficient layer handling in the server")
        VALUE_CONST(ClientType, "Client Type", AUD_CLIENT_TYPES)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTER_IN_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_REGISTER_IN_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudRegisterInOkResp)
        COMMENT(COMMENT_TEXT,
            "Identification to be used when accessing the server. \
             Client ID is received using AUD_REGISTER_IN_REQ message")
        VALUE(8, BE, ClientId, "Client ID", HEX)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(AUD_REGISTER_IN_ERRORS, AUD_ERROR_CAUSES, "", "")
        DER_CONST_TBL_ENTRY(AUD_CLIENT_NOT_SUPPORTED)
        DER_CONST_TBL_ENTRY(AUD_CLIENT_NOT_ALLOWED)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTER_IN_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_REGISTER_IN_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudRegisterInFailResp)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_REGISTER_IN_ERRORS)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_REGISTER_IN_REQ, AUD_REGISTER_IN_OK_RESP)
    MSG_PAIR(AUD_REGISTER_IN_REQ, AUD_REGISTER_IN_FAIL_RESP)

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTER_IN_IND" "_LEN")
    MSG_BEGIN(AUD_REGISTER_IN_IND, MESSAGE_IND, "", "")
        AUD_MSG_HDR(tISI_AudRegisterInInd)
        VALUE_CONST(ClientType, "Client Type", AUD_CLIENT_TYPES)
        FILLER_EX(Filler, 8, 1)
    MSG_END


    /* ------------------------------------------------------------------ */
    /* AUD_REGISTER_OUT */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTER_OUT_REQ" "_LEN")
    MSG_BEGIN(AUD_REGISTER_OUT_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudRegisterOutReq)
        COMMENT(COMMENT_TEXT,
            "Identification to be used when accessing the server. \
             Client ID is received using AUD_REGISTER_IN_REQ message")
        VALUE(8, BE, ClientId, "Client ID", HEX)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTER_OUT_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_REGISTER_OUT_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudRegisterOutOkResp)
        FILLER_EX(Fillers, 16, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(AUD_REGISTER_OUT_ERRORS, AUD_ERROR_CAUSES, "", "")
        DER_CONST_TBL_ENTRY(AUD_CLIENT_NOT_REGISTERED)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTER_OUT_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_REGISTER_OUT_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudRegisterOutFailResp)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_REGISTER_OUT_ERRORS)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_REGISTER_OUT_REQ, AUD_REGISTER_OUT_OK_RESP)
    MSG_PAIR(AUD_REGISTER_OUT_REQ, AUD_REGISTER_OUT_FAIL_RESP)

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTER_OUT_IND" "_LEN")
    MSG_BEGIN(AUD_REGISTER_OUT_IND, MESSAGE_IND, "", "")
        AUD_MSG_HDR(tISI_AudRegisterOutInd)
        VALUE_CONST(ClientType, "Client Type", AUD_CLIENT_TYPES)
        FILLER_EX(Filler, 8, 1)
    MSG_END


    /* ------------------------------------------------------------------ */
    /* AUD_SERVICES_GET */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SERVICES_GET_REQ" "_LEN")
    MSG_BEGIN(AUD_SERVICES_GET_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudServicesGetReq)
        FILLER_EX(Fillers, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SERVICES_GET_DEFAULT_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_SERVICES_GET_DEFAULT_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudServicesGetDefaultOkResp)
        FILLER_EX(Fillers, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SERVICES_GET_CUSTOM_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_SERVICES_GET_CUSTOM_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudServicesGetCustomOkResp)
        FILLER_EX(Spare, 8, 1)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_SERVICE_REPORT)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_SERVICES_GET_REQ, AUD_SERVICES_GET_DEFAULT_OK_RESP)
    MSG_PAIR(AUD_SERVICES_GET_REQ, AUD_SERVICES_GET_CUSTOM_OK_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_ATTRIBUTES_GET */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTRIBUTES_GET_REQ" "_LEN")
    MSG_BEGIN(AUD_ATTRIBUTES_GET_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudAttributesGetReq)
        VALUE_CONST(ServiceId, "Service ID", AUD_SERVICES)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTRIBUTES_GET_DEFAULT_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_ATTRIBUTES_GET_DEFAULT_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudAttributesGetDefaultOkResp)
        VALUE_CONST(ServiceId, "Service ID", AUD_SERVICES)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTRIBUTES_GET_CUSTOM_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_ATTRIBUTES_GET_CUSTOM_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudAttributesGetCustomOkResp)
        REFERENCE_CONST(ServiceId, "Service ID", SERVICE, AUD_SERVICES)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_ATTRIBUTE_SETUP_REPORT)
        SB_LST_REF_END
    MSG_END

    DER_CONST_TBL_BEGIN(AUD_ATTRIBUTES_GET_ERRORS, AUD_ERROR_CAUSES, "", "")
        DER_CONST_TBL_ENTRY(AUD_SERVICE_NOT_AVAILABLE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTRIBUTES_GET_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_ATTRIBUTES_GET_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudAttributesGetFailResp)
        VALUE_CONST(ServiceId, "Service ID", AUD_SERVICES)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_ATTRIBUTES_GET_ERRORS)
    MSG_END

    MSG_PAIR(AUD_ATTRIBUTES_GET_REQ, AUD_ATTRIBUTES_GET_DEFAULT_OK_RESP)
    MSG_PAIR(AUD_ATTRIBUTES_GET_REQ, AUD_ATTRIBUTES_GET_CUSTOM_OK_RESP)
    MSG_PAIR(AUD_ATTRIBUTES_GET_REQ, AUD_ATTRIBUTES_GET_FAIL_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_REGISTERED_GET */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTERED_GET_REQ" "_LEN")
    MSG_BEGIN(AUD_REGISTERED_GET_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudRegisteredGetReq)
        FILLER_EX(Fillers, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_REGISTERED_GET_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_REGISTERED_GET_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudRegisteredGetOkResp)
        VALUE(8, BE, NumOfClients, "Number of clients", DEC)
        COMMENT(COMMENT_TEXT,
            "The field value is composed by adding bit values for corresponding\
             registered clients in positions defined by the client type number")
        VALUE_CONST(ClientTypes,  "Client Types",   AUD_CLIENT_TYPES_1)
        COMMENT(COMMENT_TEXT,
            "The field value is composed by adding bit values for corresponding\
             registered clients in positions defined by the client type number")
        VALUE_CONST(ClientTypesE, "Client Types 2", AUD_CLIENT_TYPES_2)
        FILLER_EX(Filler1, 8, 1)
        FILLER_EX(Filler2, 8, 1)
        FILLER_EX(Filler3, 8, 1)
    MSG_END

    MSG_PAIR(AUD_REGISTERED_GET_REQ, AUD_REGISTERED_GET_OK_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_SETTING_GET */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SETTING_GET_REQ" "_LEN")
    MSG_BEGIN(AUD_SETTING_GET_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudSettingGetReq)
        REFERENCE_CONST(ServiceId, "Service ID", SERVICE, AUD_SERVICES)
        COMMENT(COMMENT_TEXT,
            "NOTE: With special parameter value AUD_ALL_ATTRIBUTES it's possible to\
             request settings of all service attributes")
        CHOICE_BEGIN(AttributeId, "Attribute ID", SERVICE)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_ATTR_ALL)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_ATTR_ALL)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_ATTR_ALL)
            CASE(AUD_DTMF,          AUD_DTMF_ATTR_ALL)
            CASE(AUD_TONE,          AUD_TONE_ATTR_ALL)
            CASE(AUD_MIXER,         AUD_MIXER_ATTR_ALL)
            CASE(AUD_MODE,          AUD_MODE_ATTR_ALL)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_ATTR_ALL)
            CASE(AUD_MUTE,          AUD_MUTE_ATTR_ALL)
            CASE_DEFAULT(AUD_DEFAULT_ATTR)
        CHOICE_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SETTING_GET_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_SETTING_GET_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudSettingGetOkResp)
        REFERENCE_CONST(ServiceId, "Service ID", SERVICE, AUD_SERVICES)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_SETTING_REPORT)
        SB_LST_REF_END
    MSG_END

    DER_CONST_TBL_BEGIN(AUD_SETTING_GET_ERRORS, AUD_ERROR_CAUSES, "", "")
        DER_CONST_TBL_ENTRY(AUD_SERVICE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(AUD_ATTRIBUTE_NOT_AVAILABLE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SETTING_GET_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_SETTING_GET_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudSettingGetFailResp)
        REFERENCE_CONST(ServiceId, "Service ID", ID, AUD_SERVICES)
        CHOICE_BEGIN(AttributeId, "Attribute ID", ID)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_ATTR_ALL)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_ATTR_ALL)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_ATTR_ALL)
            CASE(AUD_DTMF,          AUD_DTMF_ATTR_ALL)
            CASE(AUD_TONE,          AUD_TONE_ATTR_ALL)
            CASE(AUD_MIXER,         AUD_MIXER_ATTR_ALL)
            CASE(AUD_MODE,          AUD_MODE_ATTR_ALL)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_ATTR_ALL)
            CASE(AUD_MUTE,          AUD_MUTE_ATTR_ALL)
            CASE_DEFAULT(AUD_DEFAULT_ATTR)
        CHOICE_END
        VALUE_CONST(FailureReason, "Failure Reason", AUD_SETTING_GET_ERRORS)
        FILLER_EX(Filler1, 8, 1)
        FILLER_EX(Filler2, 8, 1)
        FILLER_EX(Filler3, 8, 1)
    MSG_END

    MSG_PAIR(AUD_SETTING_GET_REQ, AUD_SETTING_GET_OK_RESP)
    MSG_PAIR(AUD_SETTING_GET_REQ, AUD_SETTING_GET_FAIL_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_LAYER_UPDATE */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_UPDATE_REQ" "_LEN")
    MSG_BEGIN(AUD_LAYER_UPDATE_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudLayerUpdateReq)
        COMMENT(COMMENT_TEXT,
            "Identification to be used when accessing the server. \
             Client ID is received using AUD_REGISTER_IN_REQ message")
        VALUE(8, BE, ClientId, "Client ID", HEX)
        REFERENCE_CONST(ServiceId, "Service ID", SERVICE, AUD_SERVICES)
        FILLER_EX(Spare1, 8, 1)
        FILLER_EX(Spare2, 8, 1)
        FILLER_EX(Spare3, 8, 1)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_LAYER_SETTING)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_UPDATE_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_LAYER_UPDATE_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudLayerUpdateOkResp)
        REFERENCE_CONST(ServiceId, "Service ID", SERVICE, AUD_SERVICES)
        VALUE_CONST(GeneralStatus, "General Update Status", AUD_LAYER_UPDATE_GENERAL_STATUS)
        FILLER_EX(Spare, 16, 1)
        VALUE_CONST(GeneralEfficiency, "General Efficiency", AUD_LAYER_UPDATE_GENERAL_EFFICIENCY)
        COMMENT(COMMENT_TEXT,
            "NOTE: attribute-specific sub-blocks are not included if\
             \"general update status\" is AUD_ALL_SETTINGS_OK and \"general efficiency\" is\
             AUD_ALL_SETTINGS_EFFECTIVE")
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_ATTRIBUTE_UPDATE_REPORT)
        SB_LST_REF_END
    MSG_END

    DER_CONST_TBL_BEGIN(AUD_LAYER_UPDATE_ERRORS, AUD_ERROR_CAUSES, "", "")
        DER_CONST_TBL_ENTRY(AUD_CLIENT_NOT_REGISTERED)
        DER_CONST_TBL_ENTRY(AUD_SERVICE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(AUD_ATTRIBUTE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(AUD_ALL_SETTINGS_INVALID)
        DER_CONST_TBL_ENTRY(AUD_SETTING_NOT_POSSIBLE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_UPDATE_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_LAYER_UPDATE_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudLayerUpdateFailResp)
        VALUE_CONST(ServiceId, "Service ID", AUD_SERVICES)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_LAYER_UPDATE_ERRORS)
    MSG_END

    MSG_PAIR(AUD_LAYER_UPDATE_REQ, AUD_LAYER_UPDATE_OK_RESP)
    MSG_PAIR(AUD_LAYER_UPDATE_REQ, AUD_LAYER_UPDATE_FAIL_RESP)

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_UPDATE_IND" "_LEN")
    MSG_BEGIN(AUD_LAYER_UPDATE_IND, MESSAGE_IND, "", "")
        AUD_MSG_HDR(tISI_AudLayerUpdateInd)
        REFERENCE_CONST(ServiceId, "Service ID", SERVICE, AUD_SERVICES)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_ATTRIBUTE_LAYER_REPORT)
        SB_LST_REF_END
    MSG_END


    /* ------------------------------------------------------------------ */
    /* AUD_LAYER_UPDATE_NEEDED_IND */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_UPDATE_NEEDED_IND" "_LEN")
    MSG_BEGIN(AUD_LAYER_UPDATE_NEEDED_IND, MESSAGE_IND, "", "")
        AUD_MSG_HDR(tISI_AudLayerUpdateNeededInd)
        COMMENT(COMMENT_TEXT,
            "The client from which the server wants to get update for its layer settings \
             Client ID is received using AUD_REGISTER_IN_REQ message")
        VALUE(8, BE, ClientId, "Client ID", HEX)
        VALUE_CONST(ServiceId, "Service ID", AUD_SERVICES)
    MSG_END


    /* ------------------------------------------------------------------ */
    /* AUD_LAYER_DESTROY */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_DESTROY_REQ" "_LEN")
    MSG_BEGIN(AUD_LAYER_DESTROY_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudLayerDestroyReq)
        COMMENT(COMMENT_TEXT,
            "Identification to be used when accessing the server. \
             Client ID is received using AUD_REGISTER_IN_REQ message")
        VALUE(8, BE, ClientId, "Client ID", HEX)
        REFERENCE_CONST(ServiceId, "Service ID", SERVICE, AUD_SERVICES_ALL)
        CHOICE_BEGIN(AttributeId, "Attribute ID", SERVICE)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_ATTR_ALL)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_ATTR_ALL)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_ATTR_ALL)
            CASE(AUD_DTMF,          AUD_DTMF_ATTR_ALL)
            CASE(AUD_TONE,          AUD_TONE_ATTR_ALL)
            CASE(AUD_MIXER,         AUD_MIXER_ATTR_ALL)
            CASE(AUD_MODE,          AUD_MODE_ATTR_ALL)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_ATTR_ALL)
            CASE(AUD_MUTE,          AUD_MUTE_ATTR_ALL)
            CASE(AUD_ALL_SERVICES,  AUD_ALL_ATTR_ALL)
            CASE_DEFAULT(AUD_DEFAULT_ATTR)
        CHOICE_END
        FILLER_EX(Filler1, 8, 1)
        FILLER_EX(Filler2, 8, 1)
        FILLER_EX(Filler3, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_DESTROY_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_LAYER_DESTROY_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudLayerDestroyOkResp)
        REFERENCE_CONST(ServiceId, "Service ID", SERVICE, AUD_SERVICES_ALL)
        CHOICE_BEGIN(AttributeId, "Attribute ID", SERVICE)
            CASE(AUD_ANALOG_IN,     AUD_ANALOG_IN_ATTR_ALL)
            CASE(AUD_ANALOG_OUT,    AUD_ANALOG_OUT_ATTR_ALL)
            CASE(AUD_DSP_PARAMS,    AUD_DSP_PARAMS_ATTR_ALL)
            CASE(AUD_DTMF,          AUD_DTMF_ATTR_ALL)
            CASE(AUD_TONE,          AUD_TONE_ATTR_ALL)
            CASE(AUD_MIXER,         AUD_MIXER_ATTR_ALL)
            CASE(AUD_MODE,          AUD_MODE_ATTR_ALL)
            CASE(AUD_DIGITAL_OUT,   AUD_DIGITAL_OUT_ATTR_ALL)
            CASE(AUD_MUTE,          AUD_MUTE_ATTR_ALL)
            CASE(AUD_ALL_SERVICES,  AUD_ALL_ATTR_ALL)
            CASE_DEFAULT(AUD_DEFAULT_ATTR)
        CHOICE_END
    MSG_END

    DER_CONST_TBL_BEGIN(AUD_LAYER_DESTROY_ERRORS, AUD_ERROR_CAUSES, "", "")
        DER_CONST_TBL_ENTRY(AUD_CLIENT_NOT_REGISTERED)
        DER_CONST_TBL_ENTRY(AUD_SERVICE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(AUD_ATTRIBUTE_NOT_AVAILABLE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LAYER_DESTROY_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_LAYER_DESTROY_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudLayerDestroyFailResp)
        VALUE_CONST(ServiceId, "Service ID", AUD_SERVICES_ALL)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_LAYER_DESTROY_ERRORS)
    MSG_END

    MSG_PAIR(AUD_LAYER_DESTROY_REQ, AUD_LAYER_DESTROY_OK_RESP)
    MSG_PAIR(AUD_LAYER_DESTROY_REQ, AUD_LAYER_DESTROY_FAIL_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_TEST_START */
    /* ------------------------------------------------------------------ */

    SEQ_BEGIN(AUD_TEST_BUZZER_SEQ, DONT_CREATE_STRUCT, "", "009.000")
        VALUE_EX(16, BE, Frequency, "Tone frequency", DEC, 1.0, 0.0, "Hz")
        VALUE_EX(16, BE, Duration,  "Tone duration", DEC, 1.0, 0.0, "ms")
    SEQ_END

    SEQ_BEGIN(AUD_TEST_DEFAULT_SEQ, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(16, BE, Frequency, "Filler 1", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        VALUE(16, BE, Duration,  "Filler 2", DEC)
    SEQ_END

    CONST_TBL_BEGIN(AUD_TEST_TX_OUT_ROUTE, 16, BE, "008.016", "")
        CONST_TBL_ENTRY(AUD_FM_TX_OUT_LEFT, 0x01, "")
        CONST_TBL_ENTRY(AUD_FM_TX_OUT_RIGHT, 0x02, "")
        CONST_TBL_ENTRY(AUD_FM_TX_OUT_STEREO, 0x03, "")
    CONST_TBL_END

    SEQ_BEGIN(AUD_TEST_FM_TX_OUT_SEQ, DONT_CREATE_STRUCT, "008.016", "")
        VALUE_EX(16, BE, Frequency, "Tone frequency", DEC, 1.0, 0.0, "Hz")
        VALUE_CONST(Duration, "TX OUT route", AUD_TEST_TX_OUT_ROUTE)
    SEQ_END
             
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_TEST_START_REQ" "_LEN")
    MSG_BEGIN(AUD_TEST_START_REQ, MESSAGE_REQ, "", "008.015")
        AUD_MSG_HDR(tISI_AudTestStartReq)
        REFERENCE_CONST(TestType, "Test Type", TEST, AUD_TEST_TYPES)
        FILLER_EX(Spare, 8, 1)
        CHOICE_BEGIN(BuzzerData, "Buzzer data", TEST)
            CASE(AUD_TEST_BUZZER, AUD_TEST_BUZZER_SEQ)
            CASE_DEFAULT(AUD_TEST_DEFAULT_SEQ)
        CHOICE_END
    MSG_END
        
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_TEST_START_REQ" "_LEN")
    MSG_BEGIN(AUD_TEST_START_REQ, MESSAGE_REQ, "008.016", "009.000")
        AUD_MSG_HDR(tISI_AudTestStartReq)
        REFERENCE_CONST(TestType, "Test Type", TEST, AUD_TEST_TYPES)
        FILLER_EX(Spare, 8, 1)
        CHOICE_BEGIN(BuzzerData, "Buzzer data", TEST)
            CASE(AUD_TEST_BUZZER, AUD_TEST_BUZZER_SEQ)
            CASE(AUD_TEST_FM_TX_OUT, AUD_TEST_FM_TX_OUT_SEQ)
            CASE_DEFAULT(AUD_TEST_DEFAULT_SEQ)
        CHOICE_END
    MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_TEST_START_REQ" "_LEN")
    MSG_BEGIN(AUD_TEST_START_REQ, MESSAGE_REQ, "009.000", "")
        AUD_MSG_HDR(tISI_AudTestStartReq)
        REFERENCE_CONST(TestType, "Test Type", TEST, AUD_TEST_TYPES)
        FILLER_EX(Spare, 8, 1)
        CHOICE_BEGIN(BuzzerData, "Buzzer data", TEST)
            CASE(AUD_TEST_FM_TX_OUT, AUD_TEST_FM_TX_OUT_SEQ)
            CASE_DEFAULT(AUD_TEST_DEFAULT_SEQ)
        CHOICE_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_TEST_START_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_TEST_START_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudTestStartOkResp)
        COMMENT(COMMENT_TEXT, "Started test type")
        VALUE_CONST(TestType, "Test Type", AUD_TEST_TYPES)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    CONST_TBL_BEGIN(AUD_TEST_ERRORS, 8, BE, "", "")
        CONST_TBL_ENTRY(AUD_TEST_TYPE_NOT_AVAILABLE, 0x07, "")
        CONST_TBL_ENTRY(AUD_SETTING_NOT_ALLOWED,     0x00, "")
        CONST_TBL_ENTRY(AUD_SETTING_NOT_POSSIBLE,    0x06, "")

        COMMENT(COMMENT_TEXT, "Audio EANC test failed, left mic")  
        CONST_TBL_ENTRY_VER( AUD_EANC_L_MIC_FAIL, 0x10, "008.013", "")

        COMMENT(COMMENT_TEXT, "Audio EANC test failed, right mic")  
        CONST_TBL_ENTRY_VER( AUD_EANC_R_MIC_FAIL, 0x11, "008.013", "")
                
        COMMENT(COMMENT_TEXT, "Audio EANC test failed, both mics")  
        CONST_TBL_ENTRY_VER( AUD_EANC_BOTH_MICS_FAIL, 0x12, "008.013", "")
        
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_TEST_START_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_TEST_START_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudTestStartFailResp)
        VALUE_CONST(TestType, "Test Type", AUD_TEST_TYPES)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_TEST_ERRORS)
    MSG_END
    

    MSG_PAIR(AUD_TEST_START_REQ, AUD_TEST_START_OK_RESP)
    MSG_PAIR(AUD_TEST_START_REQ, AUD_TEST_START_FAIL_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_TEST_STOP */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_TEST_STOP_REQ" "_LEN")
    MSG_BEGIN(AUD_TEST_STOP_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudTestStopReq)
        VALUE_CONST(TestType, "Stopped Test Type", AUD_TEST_TYPES)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_TEST_STOP_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_TEST_STOP_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudTestStopOkResp)
        VALUE_CONST(TestType, "Stopped Test Type", AUD_TEST_TYPES)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_TEST_STOP_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_TEST_STOP_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudTestStopFailResp)
        VALUE_CONST(TestType, "Stopped Test type", AUD_TEST_TYPES)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_TEST_ERRORS)
    MSG_END

    MSG_PAIR(AUD_TEST_STOP_REQ, AUD_TEST_STOP_OK_RESP)
    MSG_PAIR(AUD_TEST_STOP_REQ, AUD_TEST_STOP_FAIL_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EANC_STATUS_CHANGE_REQ and AUD_EANC_STATUS_CHANGE_RESP           */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EANC_STATUS_CHANGE_REQ" "_LEN")
    MSG_BEGIN(AUD_EANC_STATUS_CHANGE_REQ, MESSAGE_REQ, "008.008", "")
        AUD_MSG_HDR(tISI_AudEancStatusChangeReq)
        VALUE_CONST(Command, "Command", AUD_EANC_STATE)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EANC_STATUS_CHANGE_RESP" "_LEN")
    MSG_BEGIN(AUD_EANC_STATUS_CHANGE_RESP, MESSAGE_RESP, "008.008", "")
        AUD_MSG_HDR(tISI_AudEancStatusChangeResp)
        VALUE_CONST(Command, "Command", AUD_EANC_STATE)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_EANC_STATUS_CHANGE_REQ, AUD_EANC_STATUS_CHANGE_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_EANC_STATUS_CHANGE_IND                                           */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EANC_STATUS_CHANGE_IND" "_LEN")
    MSG_BEGIN(AUD_EANC_STATUS_CHANGE_IND, MESSAGE_IND, "008.014", "")
        AUD_MSG_HDR(tISI_AudEancStatusChangeInd)
        VALUE_CONST(Status, "Status", AUD_EANC_STATE)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_EANC_MIC_DATA_REQ and AUD_EANC_MIC_DATA_RESP                     */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EANC_MIC_DATA_REQ" "_LEN")
    MSG_BEGIN(AUD_EANC_MIC_DATA_REQ, MESSAGE_REQ, "008.017", "")
        AUD_MSG_HDR(tISI_AudEancMicDataReq)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EANC_MIC_DATA_RESP" "_LEN")
    MSG_BEGIN(AUD_EANC_MIC_DATA_RESP, MESSAGE_REQ, "008.017", "")
        AUD_MSG_HDR(tISI_AudEancMicDataResp)
        COMMENT(COMMENT_TEXT,"Microphone 1 level data, signed 24 bits")
        VALUE(16, BE, Mic1Data_hi, "Microphone 1 level data 16 MSB bits", HEX)
        VALUE(16, BE, Mic1Data_low, "Microphone 1 level data 16 LSB bits", HEX)
        COMMENT(COMMENT_TEXT,"Microphone 2 level data, signed 24 bits")  
        VALUE(16, BE, Mic2Data_hi, "Microphone 2 level data 16 MSB bits", HEX)
        VALUE(16, BE, Mic2Data_low, "Microphone 2 level data 16 LSB bits", HEX)
    MSG_END

    MSG_PAIR(AUD_EANC_STATUS_CHANGE_REQ, AUD_EANC_STATUS_CHANGE_RESP)
    
    /* ------------------------------------------------------------------ */
    /* AUD_HW_STATUS_IND */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_HW_STATUS_IND" "_LEN")
    MSG_BEGIN(AUD_HW_STATUS_IND, MESSAGE_IND, "", "")
        AUD_MSG_HDR(tISI_AudHWStatusInd)
        VALUE_CONST(hw_status, "HW Status", AUD_HW_STATUSES)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    /* ------------------------------------------------------------------ */
    /* AUD_EQU_CREATE_REQ */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_CREATE_REQ" "_LEN")
    MSG_BEGIN(AUD_EQU_CREATE_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudEquCreateReq)
        COMMENT(COMMENT_TEXT, "Unique ID number of the equalizer")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        COMMENT(COMMENT_TEXT, "Amount of used bands in the equalizer")
        VALUE(8, BE, Bands, "Bands", DEC)
        VALUE_CONST(EqualizerType,  "Equalizer Type", AUD_EQU_TYPE)
        FILLER_EX(Spare1, 8, 1)
        FILLER_EX(Spare2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EQU_DEFINITION)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_CREATE_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_CREATE_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquCreateOkResp)
        FILLER_EX(Fillers, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_CREATE_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_CREATE_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquCreateFailResp)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_EQU_FAILURE_REASON)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_EQU_CREATE_REQ, AUD_EQU_CREATE_OK_RESP)
    MSG_PAIR(AUD_EQU_CREATE_REQ, AUD_EQU_CREATE_FAIL_RESP)

    CONSTANT_VER(AUD_EQU_MAX_NAME_LENGTH, 20, "", "")

    /* ------------------------------------------------------------------ */
    /* AUD_EQU_INFO_REQ */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_INFO_REQ" "_LEN")
    MSG_BEGIN(AUD_EQU_INFO_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudEquInfoReq)
        COMMENT(COMMENT_TEXT, "Unique ID number of the equalizer")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_INFO_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_INFO_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquInfoOkResp)
        COMMENT(COMMENT_PARAGRAPH, "Unique ID number of the equalizer.")
        COMMENT(COMMENT_PARAGRAPH, "This is the same ID as in the request")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        COMMENT(COMMENT_TEXT, "Amount of used bands in the equalizer")
        VALUE(8, BE, Bands, "Bands", DEC)
        VALUE_CONST(EqualizerType,  "Type", AUD_EQU_TYPE)
        VALUE_CONST(EqualizerState, "State", AUD_EQU_STATE)
        FILLER_EX(Spare, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EQU_DEFINITION)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_INFO_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_INFO_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquInfoFailResp)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_EQU_FAILURE_REASON)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_EQU_INFO_REQ, AUD_EQU_INFO_OK_RESP)
    MSG_PAIR(AUD_EQU_INFO_REQ, AUD_EQU_INFO_FAIL_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_EQU_SWITCH_STATE_REQ */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_SWITCH_STATE_REQ" "_LEN")
    MSG_BEGIN(AUD_EQU_SWITCH_STATE_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudEquSwitchStateReq)
        COMMENT(COMMENT_TEXT, "Unique ID number of the equalizer")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        VALUE_CONST(State, "State", AUD_EQU_STATE)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_SWITCH_STATE_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_SWITCH_STATE_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquSwitchStateOkResp)
        FILLER_EX(Fillers, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_SWITCH_STATE_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_SWITCH_STATE_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquSwitchStateFailResp)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_LAYER_DESTROY_ERRORS)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_EQU_SWITCH_STATE_REQ, AUD_EQU_SWITCH_STATE_OK_RESP)
    MSG_PAIR(AUD_EQU_SWITCH_STATE_REQ, AUD_EQU_SWITCH_STATE_FAIL_RESP)

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_SWITCH_STATE_IND" "_LEN")
    MSG_BEGIN(AUD_EQU_SWITCH_STATE_IND, MESSAGE_IND, "", "")
        AUD_MSG_HDR(tISI_AudEquSwitchStateInd)
        COMMENT(COMMENT_TEXT, "Unique ID number of the equalizer")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        VALUE_CONST(State, "State", AUD_EQU_STATE)
    MSG_END


    /* ------------------------------------------------------------------ */
    /* AUD_EQU_ADJUST_REQ */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_ADJUST_REQ" "_LEN")
    MSG_BEGIN(AUD_EQU_ADJUST_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudEquAdjustReq)
        COMMENT(COMMENT_TEXT, "Unique ID number of the equalizer")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EQU_DEFINITION)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_ADJUST_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_ADJUST_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquAdjustOkResp)
        FILLER_EX(Fillers, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_ADJUST_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_ADJUST_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquAdjustFailResp)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_EQU_FAILURE_REASON)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_EQU_ADJUST_REQ, AUD_EQU_ADJUST_OK_RESP)
    MSG_PAIR(AUD_EQU_ADJUST_REQ, AUD_EQU_ADJUST_FAIL_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_EQU_DELETE_REQ */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_DELETE_REQ" "_LEN")
    MSG_BEGIN(AUD_EQU_DELETE_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudEquDeleteReq)
        COMMENT(COMMENT_TEXT, "Unique ID number of the equalizer")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_DELETE_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_DELETE_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquDeleteOkResp)
        COMMENT(COMMENT_TEXT, "Unique ID number of the equalizer")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_DELETE_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_DELETE_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquDeleteFailResp)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_EQU_FAILURE_REASON)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_EQU_DELETE_REQ, AUD_EQU_DELETE_OK_RESP)
    MSG_PAIR(AUD_EQU_DELETE_REQ, AUD_EQU_DELETE_FAIL_RESP)


    /* ------------------------------------------------------------------ */
    /* AUD_EQU_ACTIVE_ID_REQ */
    /* ------------------------------------------------------------------ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_ACTIVE_ID_REQ" "_LEN")
    MSG_BEGIN(AUD_EQU_ACTIVE_ID_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudEquActiveIdReq)
        FILLER_EX(Fillers, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_ACTIVE_ID_OK_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_ACTIVE_ID_OK_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquActiveIdOkResp)
/* TODO: specify limits here...
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, AUDI_EQUALIZERS_MAX)
*/
        COMMENT(COMMENT_TEXT, "Value from 0 to AUD_EQUALIZERS_MAX. See product configuration file")
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(AUD_EQU_ACTIVE_ID_ERRORS, AUD_EQU_FAILURE_REASON, "", "")
        DER_CONST_TBL_ENTRY(AUD_EQU_ID_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_ACTIVE_ID_FAIL_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_ACTIVE_ID_FAIL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudEquActiveIdFailResp)
        VALUE_CONST(FailureReason, "Failure Reason", AUD_EQU_ACTIVE_ID_ERRORS)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_EQU_ACTIVE_ID_REQ, AUD_EQU_ACTIVE_ID_OK_RESP)
    MSG_PAIR(AUD_EQU_ACTIVE_ID_REQ, AUD_EQU_ACTIVE_ID_FAIL_RESP)

    /* ------------------------------------------------------------------ */
    /* AUD_EQU_GENERAL_INFO_REQ */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_GENERAL_INFO_REQ" "_LEN")
    MSG_BEGIN(AUD_EQU_GENERAL_INFO_REQ, MESSAGE_REQ, "006.010", "")
        AUD_MSG_HDR(tISI_AudEquGeneralInfoReq)
        FILLER_EX(Filler, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_GENERAL_INFO_RESP" "_LEN")
    MSG_BEGIN(AUD_EQU_GENERAL_INFO_RESP, MESSAGE_RESP, "006.010", "")
        AUD_MSG_HDR(tISI_AudEquGeneralInfoResp)
        FILLER_EX(Filler, 8, 1)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EQU_GENERAL_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_EQU_GENERAL_INFO_REQ, AUD_EQU_GENERAL_INFO_RESP)

    /* ------------------------------------------------------------------ */
    /* AUD_EQU_CREATED_IND */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_CREATED_IND" "_LEN")
    MSG_BEGIN(AUD_EQU_CREATED_IND, MESSAGE_IND, "006.010", "")
        AUD_MSG_HDR(tISI_AudEquCreatedInd)
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EQU_DEFINITION)
        SB_LST_REF_END
    MSG_END

    /* ------------------------------------------------------------------ */
    /* AUD_EQU_DELETED_IND */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_DELETED_IND" "_LEN")
    MSG_BEGIN(AUD_EQU_DELETED_IND, MESSAGE_IND, "006.010", "")
        AUD_MSG_HDR(tISI_AudEquDeletedInd)
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    /* ------------------------------------------------------------------ */
    /* AUD_EQU_ADJUSTED_IND */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_EQU_ADJUSTED_IND" "_LEN")
    MSG_BEGIN(AUD_EQU_ADJUSTED_IND, MESSAGE_IND, "006.010", "")
        AUD_MSG_HDR(tISI_AudEquAdjustedInd)
        VALUE(8, BE, EqualizerId, "Equalizer ID", HEX)
        REFERENCE(8, BE, NumOfSubBlocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_EQU_DEFINITION)
        SB_LST_REF_END
    MSG_END
    
    /* ------------------------------------------------------------------ */
    /* AUD_SCO_CONTROL_REQ and AUD_SCO_CONTROL_RESP */
    /* ------------------------------------------------------------------ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SCO_CONTROL_REQ" "_LEN")
    MSG_BEGIN(AUD_SCO_CONTROL_REQ, MESSAGE_REQ, "", "")
        AUD_MSG_HDR(tISI_AudScoControlReq)
        VALUE_CONST(State, "State", AUD_SCO_STATE)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SCO_CONTROL_RESP" "_LEN")
    MSG_BEGIN(AUD_SCO_CONTROL_RESP, MESSAGE_RESP, "", "")
        AUD_MSG_HDR(tISI_AudScoControlResp)
        VALUE_CONST(Status, "Status", AUD_SCO_STATUS)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_SCO_CONTROL_REQ, AUD_SCO_CONTROL_RESP)
    
    /* -------------------------------------------------------------------- */
    /* AUD_BTHSTREAM_STATUS_CHANGE_REQ and AUD_BTHSTREAM_STATUS_CHANGE_RESP */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_BTHSTREAM_STATUS_CHANGE_REQ" "_LEN")
    MSG_BEGIN(AUD_BTHSTREAM_STATUS_CHANGE_REQ, MESSAGE_REQ, "005.020", "")
        AUD_MSG_HDR(tISI_AudBthstreamStatusChangeReq)
        VALUE_CONST(Command, "Command", AUD_AVDTP_COMMAND)
        VALUE_CONST(StreamType, "Stream Type", AUD_AVDTP_STREAM_TYPE)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_BTHSTREAM_STATUS_CHANGE_RESP" "_LEN")
    MSG_BEGIN(AUD_BTHSTREAM_STATUS_CHANGE_RESP, MESSAGE_RESP, "005.020", "")
        AUD_MSG_HDR(tISI_AudBthstreamStatusChangeResp)
        VALUE_CONST(Command, "Command", AUD_AVDTP_COMMAND)
        VALUE_CONST(Status, "Status", AUD_AVDTP_STATUS)
    MSG_END

    MSG_PAIR(AUD_BTHSTREAM_STATUS_CHANGE_REQ, AUD_BTHSTREAM_STATUS_CHANGE_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_DEFATTR_CHANGE_REQ and AUD_DEFATTR_CHANGE_RESP                   */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_DEFATTR_CHANGE_REQ" "_LEN")
    MSG_BEGIN(AUD_DEFATTR_CHANGE_REQ, MESSAGE_REQ, "005.022", "")
        AUD_MSG_HDR(tISI_AudDefAttrChangeReq)
        COMMENT(COMMENT_TEXT, "Currently only supported valus is AUD_MODE")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0X06)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, Service, "Service", HEX)
        COMMENT(COMMENT_TEXT, "Currently only supported value is AUD_MODE_ACCESSORY")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0X01)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, AttributeId, "Attributeid", HEX)
        COMMENT(COMMENT_TEXT, "Currently only supported value is Audio mode (AUD_MODE_HP / AUD_MODE_HAC) \
                               Note! Value is actually uint16 (Correction to Macro done later)")
        MERGE_BEGIN(16, BE, Value, "AudModeAccMerge")
            FILLER(FILLER_FIXED, 8)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE_CONST(Value, "Value", AUD_MODE_VALUES)
        MERGE_END
        FILLER_EX(Spare, 16, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_DEFATTR_CHANGE_RESP" "_LEN")
    MSG_BEGIN(AUD_DEFATTR_CHANGE_RESP, MESSAGE_RESP, "005.022", "")
        AUD_MSG_HDR(tISI_AudDefAttrChangeResp)
        VALUE_CONST(Status, "Status", AUD_DEFATTR_STATUS)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_DEFATTR_CHANGE_REQ, AUD_DEFATTR_CHANGE_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_DEFATTR_VALUE_GET_REQ and AUD_DEFATTR_VALUE_GET_RESP             */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_DEFATTR_VALUE_GET_REQ" "_LEN")
    MSG_BEGIN(AUD_DEFATTR_VALUE_GET_REQ, MESSAGE_REQ, "005.022", "")
        AUD_MSG_HDR(tISI_AudDefAttrValueGetReq)
        COMMENT(COMMENT_TEXT, "Currently only supported value is AUD_MODE")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0x06)
        VALUE(8, BE, Service, "Service", HEX)
        COMMENT(COMMENT_TEXT, "Currently only supported value is AUD_MODE_ACCESSORY")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0x01)
        VALUE(8, BE, AttributeId, "AttributeId", HEX)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_DEFATTR_VALUE_GET_RESP" "_LEN")
    MSG_BEGIN(AUD_DEFATTR_VALUE_GET_RESP, MESSAGE_RESP, "005.022", "")
        AUD_MSG_HDR(tISI_AudDefAttrValueGetResp)
        VALUE_CONST(Status, "Status", AUD_DEFATTR_STATUS)
        FILLER_EX(Filler1, 8, 1)
        COMMENT(COMMENT_TEXT, "Currently only supported value is Audio mode (AUD_MODE_HP / AUD_MODE_HAC) \
                               Note! Value is actually uint16 (Correction to Macro done later)")
        MERGE_BEGIN(16, BE, Value, "AudModeAccMerge")
            FILLER(FILLER_FIXED, 8)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE_CONST(Value, "Value", AUD_MODE_VALUES)
        MERGE_END
        FILLER_EX(Filler2, 16, 1)
    MSG_END

    MSG_PAIR(AUD_DEFATTR_VALUE_GET_REQ, AUD_DEFATTR_VALUE_GET_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_VOLUME_CONTROL_REQ and AUD_VOLUME_CONTROL_RESP                   */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_VOLUME_CONTROL_REQ" "_LEN")
    MSG_BEGIN(AUD_VOLUME_CONTROL_REQ, MESSAGE_REQ, "006.013", "")
        AUD_MSG_HDR_NEW

        FILLER(FILLER_FIXED, 8)

        REFERENCE(8, BE, num_of_subblocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_VOLUME_CONTROL_SB)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_VOLUME_CONTROL_RESP" "_LEN")
    MSG_BEGIN(AUD_VOLUME_CONTROL_RESP, MESSAGE_RESP, "006.013", "")
        AUD_MSG_HDR_NEW
        COMMENT(COMMENT_TEXT, "Bitfield, informs which media type settings failed, zero = all OK")
        VALUE_CONST(failed_media_types, "Failed media types", AUD_VOLUME_MEDIA_TYPE)

        FILLER(FILLER_FIXED, 16)
        FILLER(FILLER_FIXED, 8)

        REFERENCE(8, BE, num_of_subblocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_VOLUME_CONTROL_RESPONSE_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_VOLUME_CONTROL_REQ, AUD_VOLUME_CONTROL_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_VOLUME_GET_REQ and AUD_VOLUME_GET_RESP                           */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_VOLUME_GET_REQ" "_LEN")
    MSG_BEGIN(AUD_VOLUME_GET_REQ, MESSAGE_REQ, "006.013", "")
        AUD_MSG_HDR_NEW

        COMMENT(COMMENT_TEXT, "Bitfield, requested media type volume settings will be delivered in response message subblock / media type")
        VALUE_CONST(media_types, "Media types", AUD_VOLUME_MEDIA_TYPE)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_VOLUME_GET_RESP" "_LEN")
    MSG_BEGIN(AUD_VOLUME_GET_RESP, MESSAGE_RESP, "006.013", "")
        AUD_MSG_HDR_NEW

        FILLER(FILLER_FIXED, 8)

        REFERENCE(8, BE, num_of_subblocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_VOLUME_CONTROL_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_VOLUME_GET_REQ, AUD_VOLUME_GET_RESP)
    
    /* -------------------------------------------------------------------- */
    /* AUD_VOLUME_CONTROL_IND                                               */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_VOLUME_CONTROL_IND" "_LEN")
    MSG_BEGIN(AUD_VOLUME_CONTROL_IND, MESSAGE_IND, "008.012", "")
        AUD_MSG_HDR_NEW

        FILLER(FILLER_FIXED, 8)

        REFERENCE(8, BE, num_of_subblocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_VOLUME_CONTROL_RESPONSE_SB)
        SB_LST_REF_END
    MSG_END


    
    
      
    /* -------------------------------------------------------------------- */
    /* AUD_ATTACH_ACCESSORY_EVENT_REQ */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTACH_ACCESSORY_EVENT_REQ" "_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudAttachAccEventReq")
    MSG_BEGIN(AUD_ATTACH_ACCESSORY_EVENT_REQ, MESSAGE_REQ, "005.027", "")
        AUD_MSG_HDR_NEW
        COMMENT(COMMENT_TEXT,
            "If master_type/sub_type not in use (in case of ACC_THWK_FEATURE_INFO_IND), it must be defined as NO_INFORMATION")
        REFERENCE_CONST(master_type, "MasterType", ACC_THWK_MASTER_TYPE,  ACC_THWK_MASTER_TYPE)
        CHOICE_BEGIN(sub_type, "SubType", ACC_THWK_MASTER_TYPE)
            CASE(ACC_THWK_OTHER, ACC_SUBTYPE_OTHER)
            CASE(ACC_THWK_HEADSET, ACC_SUBTYPE_HEADSET)
            CASE(ACC_THWK_HANDSFREE, ACC_SUBTYPE_HANDSFREE)
            CASE(ACC_THWK_DATACABLE, ACC_SUBTYPE_DATACABLE)
            CASE(ACC_THWK_TEST_DEVICE, ACC_SUBTYPE_TEST_DEVICE)
            CASE(ACC_THWK_CAMERA, ACC_SUBTYPE_CAMERA)
            CASE(ACC_THWK_MISC, ACC_SUBTYPE_MISC)
            CASE(ACC_THWK_ADAPTER, ACC_SUBTYPE_ADAPTER)
            CASE_VER(ACC_THWK_NO_INFORMATION, ACC_SUBTYPE_NO_INFORMATION, "005.027", "")
            CASE_DEFAULT(ACC_SUBTYPE_DEFAULT)
        CHOICE_END
        COMMENT(COMMENT_TEXT,
            "If AccID not in use (in case of ACC_THWK_FEATURE_INFO_IND), it must be defined as NO_INFORMATION")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x00)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0xFF)
        VALUE(8, BE, acc_id, "AccID", HEX)

        FILLER_EX(reserved1, 8, 1)
        FILLER_EX(reserved2, 8, 1)

        REFERENCE(8, BE, sub_block_count, "Number of sub blocks", N)
        COMMENT(COMMENT_PARAGRAPH, "These following subblocks are inherited from acc_shared_isi.h")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(ACC_SB_THWK_EXEC_FEATURE)
            SB_LST_ENTRY(ACC_SB_THWK_INFO_FEATURE)
            SB_LST_ENTRY(ACC_SB_THWK_AUDIO_BLOCK)
        SB_LST_REF_END

    MSG_END

    /* -------------------------------------------------------------------- */
    /* AUD_ATTACH_ACCESSORY_EVENT_OK_RESP */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_ATTACH_ACCESSORY_EVENT_OK_RESP" "_LEN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tISI_AudAttachAccEventOkResp")
    MSG_BEGIN(AUD_ATTACH_ACCESSORY_EVENT_OK_RESP, MESSAGE_RESP, "005.027", "")
        AUD_MSG_HDR_NEW
        FILLER_EX(reserved1, 8, 1)
        FILLER_EX(reserved2, 8, 1)
    MSG_END

    MSG_PAIR(AUD_ATTACH_ACCESSORY_EVENT_REQ, AUD_ATTACH_ACCESSORY_EVENT_OK_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_FIFO_INTERRUPT_IND */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_FIFO_INTERRUPT_IND" "_LEN")
    MSG_BEGIN(AUD_FIFO_INTERRUPT_IND, MESSAGE_IND, "007.009", "")
        AUD_MSG_HDR(tISI_AudFifoInterruptInd)
        FILLER_EX(Filler, 16, 1)
    MSG_END
    
    /* -------------------------------------------------------------------- */
    /* AUD_S60_VOIP_EMERGENCY_CALL_NTF */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_S60_VOIP_EMERGENCY_CALL_NTF" "_LEN")
    MSG_BEGIN(AUD_S60_VOIP_EMERGENCY_CALL_NTF, MESSAGE_IND, "009.003", "")
        COMMENT(COMMENT_TEXT, "Voip emergency call notification")
        AUD_MSG_HDR_NEW
        VALUE_CONST(State, "State", ON_OFF)
        FILLER_EX(Filler, 8, 1)
    MSG_END
    
    /* -------------------------------------------------------------------- */
    /* AUD_FEATURE_SET_REQ and AUD_FEATURE_SET_RESP                         */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_FEATURE_SET_REQ" "_LEN")
    MSG_BEGIN(AUD_FEATURE_SET_REQ, MESSAGE_REQ, "009.004", "")
        COMMENT(COMMENT_TEXT, "Feature set request")
        AUD_MSG_HDR_NEW
        VALUE_CONST(FeatureId, "Feature ID", AUD_FEATURE_ID)
        VALUE_CONST(FeatureIdState, "Feature ID State", ON_OFF)        
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_FEATURE_SET_RESP" "_LEN")
    MSG_BEGIN(AUD_FEATURE_SET_RESP, MESSAGE_RESP, "009.004", "")
         COMMENT(COMMENT_TEXT, "Feature set response")
        AUD_MSG_HDR_NEW
        VALUE_CONST(Result, "Result", OK_FAIL)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_FEATURE_SET_REQ, AUD_FEATURE_SET_RESP)

    /* -------------------------------------------------------------------- */
    /* AUD_SELFTEST_REQ and AUD_SELFTEST_RESP                               */
    /* -------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SELFTEST_REQ" "_LEN")
    MSG_BEGIN(AUD_SELFTEST_REQ, MESSAGE_REQ, "009.006", "")
        COMMENT(COMMENT_TEXT, "Selftest request")
        AUD_MSG_HDR_NEW
        VALUE_CONST(TestType, "Test Type", AUD_SELFTEST_TYPES)
        FILLER_EX(Filler, 8, 1)        
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_SELFTEST_RESP" "_LEN")
    MSG_BEGIN(AUD_SELFTEST_RESP, MESSAGE_RESP, "009.006", "")
        COMMENT(COMMENT_TEXT, "Selftest response")
        AUD_MSG_HDR_NEW
        VALUE_CONST(TestResult, "Test Result", OK_FAIL)
        FILLER_EX(Filler, 8, 1)
    MSG_END

    MSG_PAIR(AUD_SELFTEST_REQ, AUD_SELFTEST_RESP)
    
    /* -------------------------------------------------------------------- */
    /* AUD_LOOPBACK_REQ and AUD_LOOPBACK_RESP                               */
    /* -------------------------------------------------------------------- */
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LOOPBACK_REQ" "_LEN")
    MSG_BEGIN(AUD_LOOPBACK_REQ, MESSAGE_REQ, "009.009", "010.000")
        COMMENT(COMMENT_TEXT, "Loopback request")
        AUD_MSG_HDR_NEW
        REFERENCE(8, BE, InputNum, "Number of inputs", INPUT_NUM)
        REFERENCE(8, BE, OutputNum, "Number of outputs", OUTPUT_NUM)
        SEQ_OF_REF(InputData, "Input data", AUD_LOOPBACK_INPUT_DATA,INPUT_NUM,ISIHDR_DONT_GENERATE)
        SEQ_OF_REF(OutPutData, "Output data", AUD_LOOPBACK_OUTPUT_DATA,OUTPUT_NUM,ISIHDR_DONT_GENERATE)
    MSG_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LOOPBACK_REQ" "_LEN")
    MSG_BEGIN(AUD_LOOPBACK_REQ, MESSAGE_REQ, "010.000", "")
        COMMENT(COMMENT_TEXT, "Loopback request")
        AUD_MSG_HDR_NEW
        FILLER(FILLER_FIXED, 8)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_LOOPBACK_IN_PARAMS_SB)
            SB_LST_ENTRY(AUD_LOOPBACK_OUT_PARAMS_SB)
        SB_LST_REF_END
    MSG_END

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LOOPBACK_RESP" "_LEN")
    MSG_BEGIN(AUD_LOOPBACK_RESP, MESSAGE_RESP, "009.009", "010.000")
        COMMENT(COMMENT_TEXT, "Loopback response")
        AUD_MSG_HDR_NEW
        VALUE_CONST(Result, "Result", OK_FAIL)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LOOPBACK_RESP" "_LEN")
    MSG_BEGIN(AUD_LOOPBACK_RESP, MESSAGE_RESP, "010.000", "")
        COMMENT(COMMENT_TEXT, "Loopback response")
        AUD_MSG_HDR_NEW
        VALUE_CONST(Result, "Result", OK_FAIL)
        REFERENCE(8, BE, nbr_of_subblocks, "Number of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_LOOPBACK_OUT_SIGNAL_ANALYSIS_SB)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(AUD_LOOPBACK_REQ, AUD_LOOPBACK_RESP)
    
        
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LOOPBACK_GAIN_SET_REQ" "_LEN")
    MSG_BEGIN(AUD_LOOPBACK_GAIN_SET_REQ, MESSAGE_REQ, "009.009", "")
        COMMENT(COMMENT_TEXT, "Loopback gain set request")
        AUD_MSG_HDR_NEW 
        FILLER(FILLER_FIXED, 8)
        REFERENCE(8, BE, SbCounter, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(AUD_LOOPBACK_INPUT_GAIN_SB)
            SB_LST_ENTRY(AUD_LOOPBACK_OUTPUT_GAIN_SB)
        SB_LST_REF_END
    MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "AUD_LOOPBACK_GAIN_SET_RESP" "_LEN")
    MSG_BEGIN(AUD_LOOPBACK_GAIN_SET_RESP, MESSAGE_RESP, "009.009", "")
        COMMENT(COMMENT_TEXT, "Loopback gain set response")
        AUD_MSG_HDR_NEW
        VALUE_CONST(Result, "Result", OK_FAIL)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    MSG_PAIR(AUD_LOOPBACK_GAIN_SET_REQ, AUD_LOOPBACK_GAIN_SET_RESP)

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


/* End of file aud_isi_m.h */
