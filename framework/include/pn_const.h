/**
    Definitions Of The PhoNet Constants

    #####    ####       #    #   ####    #####      ######  #####      #     #####
    #    #  #    #      ##   #  #    #     #        #       #    #     #       #
    #    #  #    #      # #  #  #    #     #        #####   #    #     #       #
    #    #  #    #      #  # #  #    #     #        #       #    #     #       #
    #    #  #    #      #   ##  #    #     #        #       #    #     #       #
    #####    ####       #    #   ####      #        ######  #####      #       #


    You are not allowed to make you own version of this file containing you own
    modifications. The reason for this is that the constants defined in here
    need to have a unique value that must not change over time and between products.
    If your own not approved numbers end up in your final product, this product might
    not be compatible with standard Nokia tools and accessories.

    Do not change this warning.

Copyright (c) Nokia Corporation. All rights reserved.
*/

/*
------------------------------------------------------------------------------
If you have any questions please contact component owner.

Changes to this file should be requested through a processes described in
http://wikis.in.nokia.com/S40Architecture/ISIInterfaceChanges.

The constants in this file are tagged with some signatures. These can be used
together with "grep" to get an overview of classes of constants. Do like this:

    grep "\[S\]" pn_const.h

to find all servers.

These signatures are defined:

[M]  -  The constant defines a mediamodule
[D]  -  The constant defines a device id

[S]  -  The constant defines an approved server
[RS] -  The constant defines an approved server which is not usable from outside
        of device
[TS] -  The constant defines an approved server which is usable from outside
        of device only in R&D phase
[PN] -  The constant defines PhoNet system resource
[DR] -  DSP resources
[X]  -  The constant is obsolete and should not be used in new code
[R]  -  Resource like id's that is used in the code, but not associated with
        an approved server. Not usable from PC.
[A]  -  Alias. Watch out - it might be outdated. In that case: use the official name

[O]  -  A reserved object id

------------------------------------------------------------------------------
*/

#ifndef PN_CONST_H
#define PN_CONST_H

/* === PhoNet header size === */
#define PN_HEADER_SIZE                  0x06 /* 6, Note data[0]/[1] excluded */

/* ==== PhoNet Header media field constants ==== */

/* === "pseudo" media === */
#define PN_MEDIA_DISCONNECTED           0x00 /* used in media modules only  */
#define PN_MEDIA_RESERVED               0x01 /* used by CM only             */

/* === Media available for users === */
/* === Note! The highest bit cannot be 1 for real medias. Router uses it (0x80) to ===
   ===       distinguish whether message is coming from media module or from the   ===
   ===       other source in device.                                               === */
/* === Note! Value seen for medias are not running number, because some medias     ===
   ===       having intervening number(s) have been removed.                       === */

#define PN_MEDIA_GLOBAL                 0xFF /* [M] Not supported yet!!             */
#define PN_MEDIA_NOT_USED               0xFE /* [M] This media is reserved for      *
                                              *     non-PhoNet messages between     *
                                              *     tasks                           */
#define PN_MEDIA_ROUTING_REQ            0x00 /* [M] let Router select media.        */
#define PN_MEDIA_OS                     0x02 /* [M] Control message between Router  *
                                              *     and media modules.              */

#define PN_MEDIA_XTI                    0x10 /* [M] Extended Trace Interface        */

#define PN_MEDIA_BT                     0x19 /* [M] Bluetooth                       */

#define PN_MEDIA_USB                    0x1B /* [M] USB (currently used in Ostrich) */

#define PN_MEDIA_TCPIP                  0x1D /* [M] TCP/IP MOSIM/ESIM interface.    *
                                              *     Used in Simulation environment. */

#define PN_MEDIA_I2C                    0x24 /* [M] I2C media module for accessories*/

#define PN_MEDIA_MC                     0x28 /* [M] Modem Communication MM in S40.  *
                                              *     Handles modems for multi sim.   */

/* ==== PhoNet header receiver and sender DEVice addresses ==== */

/* === Following are basically for PhoNet system use only === */
#define PN_DEV_FIRST_FIXED              0x10 /* 016 */
#define PN_DEV_LAST_DYNAMIC             0xEF /* 239 */
#define PN_DEV_NUMBER_ADD               0xF0 /* 240 */
#define PN_DEV_LN_UNKNOWN               0xF8 /* 248 */
#define PN_DEV_TEMPORARY                0xFE /* 254 Temporary device number used
                                              *     in dynamic registration */

#define PN_DEV_SLAVE_IN_WT_MODE         0x7E /* [X] 126 */
#define PN_DEV_LAST_FIXED               0x7F /* 127 */
#define PN_DEV_FIRST_DYNAMIC            0x80 /* 128 */

#define PN_DEV_HOST_IN_SLAVE_MODE       PN_DEV_LAST_FIXED

/* === Users can also use the following === */
/* == For Host (phone) there is four different device numbers == */
#define PN_DEV_HOST                     0x00 /* [D]    0 */

#define PN_DEV_DONT_CARE                0x00 /* [X]    0 */
#define PN_DEV_GLOBAL                   0xFF /* [D] 255 */
#define PN_DEV_TRACE                    0xFD /* [D] 253 for trace type of messages */

/* === Fixed Slave count === */
#define PN_FIXED_SLAVE_COUNT \
        ((PN_DEV_LAST_FIXED-PN_DEV_FIRST_FIXED)+1)

/* ==== Allocated fixed DEVice numbers ==== */

#define PN_DEV_PC                       0x10 /* [D] 16, PC tools, like PCLOCals, *
                                              *         service, FT etc.         *
                                              *         softwares                */
#define PN_DEV_DSP_TESTER               0x14 /* [D] 20, DSP tester device (PC)   *
                                              *         FMON, DAI                */
#define PN_DEV_COMBOX                   0x18 /* [D] 24, COMBOX software          */
#define PN_DEV_SECBOX                   0x20 /* [D] 32, Security Box for IMEI,   *
                                              *         ESN, Flash etc.          *
                                              *         protection               */
#define PN_DEV_FLASHBOX                 0x20 /* [D] 32, Flash box (synonym for   *
                                              *         PN_DEV_SECBOX).          */
#define PN_DEV_SIM_READER               0x30 /* [D] 48, External SIM reader      */
#define PN_DEV_BTHF                     0x34 /* [D] 52, HFW-1 (handsfree device)
                                                        + HDW-1 (headset device) */
#define PN_DEV_PU                       0x38 /* [D] 56, Phone unit (for CD941)   */
#define PN_DEV_SERVICE_TOOL             0x40 /* [D] 64, Service tool e.g. JPV-1  */
#define PN_DEV_DATA_PIC                 0x48 /* [D] 72, Data Cable with PIC      *
                                              *     processor                */
#define PN_DEV_OSTRICH                  0x4C /* [D] 76, Ostrich                  */
#define PN_DEV_TA                       0x54 /* [D] 84, Telphone adapter in car  *
                                              *         environment              */

#define PN_DEV_FASTTRACE                0x58 /* [D] 88, Device type used by FastTrace tool */
#define PN_DEV_MODEM_HOST_1             0x5C /* [D] 92  Device for modem host 1 */
#define PN_DEV_MODEM                    0x60 /* [D] 96  Modem device number 1 */
#define PN_DEV_MODEM_HOST_3             0x64 /* [D] 100 Device for modem host 3 */
#define PN_DEV_MODEM_2                  0x68 /* [D] 104 Modem device number 2 */
#define PN_DEV_SOS                      0x6C /* [D] 108 Device for SOS media module */

#define PN_DEV_REMOTE_HOST              0x74 /* [D] 116, 'remote' host in host/host communication */
#define PN_DEV_DSP_AUX                  0x78 /* [D] 120, Auxiliary DSP processor */
#define PN_DEV_DSP_MAIN                 0x7C /* [D] 124, Main DSP processor      */


/* ==== Internal receiver OBJect special addresses (RECEIVER object) ==== */

/* === Following are basically for PhoNet system use only === */
#define PN_OBJ_USER_FIRST              0x01 /* 001 */
#define PN_OBJ_USER_LAST               0xEF /* 239 */

/* === Users can use the following === */
#define PN_OBJ_ROUTING_REQ             0x00 /* [O] 000, function/resource routing */
#define PN_OBJ_EVENT_MULTICAST         0x20 /* [O] 32   Events between devices should
                                                        be sent to this object    */
#define PN_OBJ_TRACE                   0xFD /* [X] 253, for trace messages.
                                                        Not supported             */
#define PN_OBJ_GLOBAL                  0xFF /* [X] 255, for globally for all      *
                                             *          objects. This is not      *
                                             *          supported yet!            *
                                             */

/* ==== Internal sender OBJect special addresses (SENDER object) ==== */
/* === Router uses this in responses === */
#define PN_OBJ_ROUTER                   0x00 /* [O] router -> object */

/* === User can use this if no response for message is waited === */
#define PN_OBJ_DONT_CARE                0x00 /* [X] object -> router */

/* ==== PhoNet application FUNCTION (RESOURCE) defines ==== */

/* First define the limits, these are basically for PhoNet
 * system use only
 */
#define PN_FIRST_MCU_FUNCTION           0x00    /*   0 */

#define PN_FIRST_USER_FUNCTION          0x00    /*   0 */
#define PN_LAST_USER_FUNCTION           0xCF    /* 207 */

#define PN_FIRST_SYSTEM_FUNCTION        0xD0    /* 208 */
#define PN_LAST_SYSTEM_FUNCTION         0xDF    /* 223 */

#define PN_LAST_MCU_FUNCTION            0xE5    /* 229 */

#define PN_FIRST_DSP_FUNCTION           0xE6    /* 230 */
#define PN_LAST_DSP_FUNCTION            0xFE    /* 254 */

/* ==== Constants for PhoNet header's function (resource field) ==== */

/* Special trace resource id */
#define PN_TRACE                        0   /* 0x00  [PN] Trace messages */

/* Server resource id's (Part 1) */
#define PN_CALL                         1   /* 0x01  [S] Call Control */
#define PN_SMS                          2   /* 0x02  [S] Short Message Services */
#define PN_PHONEBOOK                    3   /* 0x03  [S] Phonebook */
#define PN_PHONE_STATUS                 4   /* 0x04  [X] */
#define PN_SETTINGS                     5   /* 0x05  [S] Settings server - initially only in CUI!!! */
#define PN_SS                           6   /* 0x06  [S] Supplementary Services */
#define PN_CUSTOM_IDLE                  7   /* 0x07  [S] Custom Idle framework Server */
#define PN_SECURITY                     8   /* 0x08  [S] PIN, PUK, etc handling   */
#define PN_SIM                          9   /* 0x09  [S] Generic SIM access etc. */
#define PN_NETWORK                      10  /* 0x0A  [S] Operator selection etc */
#define PN_AUDIO                        11  /* 0x0B  [S] Audio control */
#define PN_KEY                          12  /* 0x0C  [S] Keyboard server */
#define PN_MULTI_SIM                    13  /* 0x0D  [TS] Multi SIM Server */
#define PN_PANEL                        14  /* 0x0E  [S] Plato panel server       */
#define PN_ECHO                         15  /* 0x0F  [R] Can be used for debugging/test */
#define PN_COMMGR                       16  /* 0x10  [PN] CM messages */
#define PN_JAVA                         17  /* 0x11  [S] Java server */
#define PN_LOCAL_CONNECTIVITY           18  /* 0x12  [S] Local connectivity server */
#define PN_CLDR                         19  /* 0x13  [S] Calendar server */
#define PN_SMS_MEMORY                   20  /* 0x14  [S] SMS memory message */
#define PN_MTC                          21  /* 0x15  [S] Mobile Terminal Control */
#define PN_CSD                          22  /* 0x16  [S] Circuit Switched Data */
#define PN_ENERGY                       23  /* 0x17  [S] Energy management */
#define PN_MENU                         24  /* 0x18  [S] Menu server */
#define PN_TIME                         25  /* 0x19  [S] Time services */
#define PN_DATA_TEST                    26  /* 0x1A  [S] Bearer/Socket test server */
#define PN_PHONE_INFO                   27  /* 0x1B  [S] Phone Info Server */
#define PN_ACCESSORY                    28  /* 0x1C  [S] Accessory server */
#define PN_UDM                          29  /* 0x1D  [S] Universal Diagnostic Monitor Support Server */
#define PN_THEME                        30  /* 0x1E  [S] UI Themes Server */
#define PN_TONE                         31  /* 0x1F  [S] Tone server */
#define PN_CONTACTS                     32  /* 0x20  [S] Contacts server. Replacement for Phonebook */
#define PN_SOS_ADL                      33  /* 0x21  [S] SOS ADL server */
#define PN_PROVISIONING                 34  /* 0x22  [S] Provisioning Server */
#define PN_PERMANENT_DATA               35  /* 0x23  [S] Permanent Data */
#define PN_ANALYTICS                    36  /* 0x24  [TS] Analytics Server*/
#define PN_SWUPD                        37  /* 0x25  [S] Software Update Server */

#define PN_WDP                          38  /* 0x26  [S] Wireless Datagram Protocol */

#define PN_WSP                          41  /* 0x29  [R] Temporaty WAP server. Will eventually not be needed */

#define PN_SOCKET                       43  /* 0x2B  [S] Socket server */
#define PN_HELP                         44  /* 0x2C  [S] Help common application */


/* === Project specific resources. Can be redefined in pn_conf.h  === */
#define PN_PRJ_RESOURCE_C               48  /* 0x30  [R] Project specific resource id C */

/* Server resource id's (Part 1 cont.) */
#define PN_GPDS                         49  /* 0x31  [S] General Packet Radio System Server */
#define PN_GSS                          50  /* 0x32  [S] GSM Stack Server */

#define PN_SELFTEST                     53  /* 0x35  [S] Selftest server */
#define PN_OBEX                         54  /* 0x36  [S] Obex Server */
#define PN_PRINT                        55  /* 0x37  [S] Print Server */
#define PN_MON                          56  /* 0x38  [S] Monitor server */
#define PN_UPF                          57  /* 0x39  [S] User Profile server */
#define PN_LIGHT                        58  /* 0x3A  [S] Light server */

#define PN_GSM_CS_PH                    60  /* 0x3C  [S] GSM CS Layer 1 */

#define PN_FM_RADIO                     62  /* 0x3E  [S] FM Radio Server */
#define PN_WAP_CONN                     63  /* 0x3F  [S] WAP connectivity server. */
#define PN_TEST                         64  /* 0x40  [S] Test server */

#define PN_WARRANTY                     66  /* 0x42  [S] Warranty transfer server - TO BE RECYCLED */
#define PN_NVD                          67  /* 0x43  [S] Non volatile data server */
#define PN_SECBOX                       68  /* 0x44  [R] Used between PC<->Security Box */
#define PN_COMBOX                       69  /* 0x45  [R] Used between PC<->ComBox */
#define PN_RTSP                         70  /* 0x46  [S] Real Time Streaming Protocol */
#define PN_SENSOR                       71  /* 0x47  [S] Sensor server */
#define PN_APDU                         72  /* 0x48  [S] APDU Server */
#define PN_CONTENT_DISPATCH             73  /* 0x49  [S] Content dispatch server */
#define PN_VOICE                        74  /* 0x4A  [S] Voice server */

#define PN_SIMLOCK                      83  /* 0x53  [S] Simlock Server */
#define PN_LOCATION                     84  /* 0x54  [S] Location server */

#define PN_SMC                          86  /* 0x56  [S] System mode control */
#define PN_VRR                          87  /* 0x57  [S] Voice recognition and recording */
#define PN_EPOC_TEST                    88  /* 0x58  [S] EPOC test server */
#define PN_EPOC_SELFTEST                89  /* 0x59  [S] EPOC selftest server */
#define PN_ATK                          90  /* 0x5A  [S] Application ToolKit server */
#define PN_WCDMA_CS_PH                  91  /* 0x5B  [S] WCDMA CS Physical Layer */
#define PN_SYNCML                       92  /* 0x5C  [S] SyncML server */
#define PN_VERSIT                       93  /* 0x5D  [S] Versit server */
#define PN_EPOC_MON                     94  /* 0x5E  [S] EPOC side monitor server */

#define PN_BEARERCTRL                   96  /* 0x60  [S] Bearer control (application access to GPRS bearer) */
#define PN_CAMERA                       97  /* 0x61  [S] Camera server */
#define PN_EPOC_INFO                    98  /* 0x62  [S] EPOC side info server */

#define PN_LCIF                         100 /* 0x64  [S] Local Connectivity InterFace server */
#define PN_IMPS_CONTACTS                101 /* 0x65  [S] IMPS Contacts Server */
#define PN_MESSAGING                    102 /* 0x66  [S] Messaging services */
#define PN_POC                          103 /* 0x67  [S] POC server (Push-to-talk over Cellular) */
#define PN_HTTPSRV                      104 /* 0x68  [S] HTTP server side functionality */

#define PN_HTTP                         107 /* 0x6B  [S] HTTP 1.1 protocol over TCP/IP */
#define PN_SSL                          108 /* 0x6C  [S] Secure Sockets Layer server */
#define PN_FILE                         109 /* 0x6D  [RS] File Manager Server */
#define PN_BLUETOOTH                    110 /* 0x6E  [S] BlueTooth Server */
#define PN_ADL                          111 /* 0x6F  [S] Auxiliary DownLoad Server - For reflashing */
#define PN_TOUCHPAD                     112 /* 0x70  [S] Touchpad server */
#define PN_WIM                          113 /* 0x71  [S] Wireless Identity Module and Certificates */
#define PN_CONCIERGE                    114 /* 0x72  [S] "Concierge" server */
#define PN_SIP                          115 /* 0x73  [S] Session Initiation Protocol server */
#define PN_RTP                          116 /* 0x74  [S] Real-time Transport Protocol server */
#define PN_MUSIC                        117 /* 0x75  [S] Music server - access to music codecs */
#define PN_IMPS                         118 /* 0x76  [S] Instant Messaging and Presence Service Server */
#define PN_TUNEPLAYER                   119 /* 0x77  [S] Tune Player server */
#define PN_ACC                          120 /* 0x78  [S] Accesory message. Comes from DCT3 accesories  */

#define PN_GARBAGE                      122 /* 0x7A  [S] UI settings */

#define PN_OSTRICH                      124 /* 0x7C  [R] Used between PC<->Ostrich box */
#define PN_LOCATION_STORAGE             125 /* 0x7D  [S] Location UI Server */

#define PN_ACK                          127 /* 0x7F  [PN] PhoNet Acknowledge messages */
#define PN_BLUETOOTH_CORE               128 /* 0x80  [S]  BlueTooth core server */
#define PN_I2C                          129 /* 0x81  [S]  I2C core server */

/* === Project specific resources continued. Can be redefined in pn_conf.h  === */
#define PN_PRJ_RESOURCE_A               130 /* 0x82  [R] Project specific resource id A */
#define PN_PRJ_RESOURCE_B               131 /* 0x83  [R] Project specific resource id B */

#define PN_RB_WAE1                      132 /* 0x84  [RS] OSS Browser */

/* === Project specific resources continued. Can be redefined in Aliases below  === */
#define PN_PRJ_RESOURCE_D               133 /* 0x85  [R] Project specific resource id D */
#define PN_PRJ_RESOURCE_E               134 /* 0x86  [R] Project specific resource id E */
#define PN_PRJ_RESOURCE_F               135 /* 0x87  [R] Project specific resource id F */
#define PN_PRJ_RESOURCE_G               136 /* 0x88  [R] Project specific resource id G */
#define PN_PRJ_RESOURCE_H               137 /* 0x89  [R] Project specific resource id H */
#define PN_PRJ_RESOURCE_I               138 /* 0x8A  [R] Project specific resource id I */
#define PN_PRJ_RESOURCE_J               139 /* 0x8B  [R] Project specific resource id J */

/* Server resource id's (Part 2) */
#define PN_UICC                         140 /* 0x8C  [S] Universal Integrated Circuit Card */
#define PN_MODEM_SIM_SRV                141 /* 0x8D  [S] Modem SIM Server, MSS */
#define PN_AT_MODEM                     142 /* 0x8E  [S] AT Modem Server */
#define PN_AT_APPL                      143 /* 0x8F  [S] AT Application Server */
#define PN_MODEM_LCS                    144 /* 0x90  [S] Modem LCS Server */
#define PN_MODEM_TEST                   145 /* 0x91  [S] Modem Test Server */
#define PN_MODEM_NVD                    146 /* 0x92  [S] Modem Non Volatile Data Server */
#define PN_MODEM_PERM                   147 /* 0x93  [S] Modem PERManent Data Server */
#define PN_ODIN                         148 /* 0x94  [S] Open Dynamic INterface server */
#define PN_WTA                          149 /* 0x95  [S] Wireless Telephony Application server */
#define PN_NFC                          150 /* 0x96  [S] Near Field Communication server */
#define PN_SCREENSAVER                  151 /* 0x97  [TS] Screensaver server */
#define PN_KEYGUARD                     152 /* 0x98  [TS] Keyguard server */
#define PN_LIGHT_UI                     153 /* 0x99  [TS] Light UI server */

/* Server resource id's (Part 3) */
/* 157 */
#define PN_VAM                          158 /* 0x9E  [S] Verizona Access Manager Server */

#define PN_IMS                          161 /* 0xA1  [S] IP Multimedia Subsystem (IMS) and
                                                         Session Initiation Protocol (SIP)
                                                         services.*/
#define PN_SOS_PERM                     162 /* 0xA2  [S] SOS PERManent Server */
#define PN_POC_UI                       163 /* 0xA3  [S] PoC UI Engine Server */
#define PN_PRESENCE                     164 /* 0xA4  [S] Presence server */
#define PN_XCAP                         165 /* 0xA5  [S] XML Configuration Access Protocol Server */
#define PN_POC_GROUP                    166 /* 0xA6  [S] POC Group Server */
#define PN_ISA_SETTINGS                 167 /* 0xA7  [S] Common Settings Module Server */

#define PN_TRACFONE                     169 /* 0xA9  [S] TRACFONE carrier pre-paid feature */
#define PN_MESSAGE_STORAGE              170 /* 0xAA  [S] Message Storage Server */
#define PN_MESSAGE_PROTOCOL             171 /* 0xAB  [S] Multimedia and E-mail Services Server */
#define PN_VTBTEST                      172 /* 0xAC  [S] Vertu Bus Test server   */

#define PN_IP_COMMS                     174 /* 0xAE  [S] IP Communications Server */
#define PN_HARDCORE                     175 /* 0xAF  [S] TSS Hardware access server */
#define PN_SOS_UMA                      176 /* 0xB0  [S] UMA Symbian Controller Server */
#define PN_VIDEO_PROTOCOL               177 /* 0xB1  [S] Video Protocol Server */
#define PN_WLAN                         178 /* 0xB2  [S] Wireless LAN (WLAN) connectivity Server */
#define PN_NEWS_DELIVERY                179 /* 0xB3  [S] News Delivery Server */
#define PN_WRAN                         180 /* 0xB4  [S] WCDMA Radio Factory Server*/
#define PN_RF_HAL                       183 /* 0xB7  [S] RF control and tuning server */
#define PN_IM                           184 /* 0xB8  [S] Instance Message Engine Server */
#define PN_NATT                         185 /* 0xB9  [S] Timing & NAT Traversal (TNT) Server */
#define PN_BACKUP                       186 /* 0xBA  [S] Backup Server */
#define PN_MODEM_FTD                    187 /* 0xBB  [S] Modem FTD Server */
#define PN_MOB_POLICY                   188 /* 0xBC  [S] Mobility Policy (MOP) Server */
#define PN_LANDMARK                     189 /* 0xBD  [S] Landmark Server */
#define PN_MOBICAST                     190 /* 0xBE  [S] Mobile Broadcast Services Server */
#define PN_FWD_ERR_CORR                 191 /* 0xBF  [S] Forward Error Correction (FEC) Server */
#define PN_GBA                          192 /* 0xC0  [S] Generic Bootstrapping Architecture (GBA) Server */
#define PN_DYNAMIC_LOADER               193 /* 0xC1  [S] Dynamic Loader Server */
#define PN_MODEM_MCE                    194 /* 0xC2  [S] Modem MCE Server */
#define PN_MODEM_MON_2                  195 /* 0xC3  [S] Modem HW Monitor 2 server */
#define PN_MODEM_MON_3                  196 /* 0xC4  [S] Modem HW Monitor 3 server */
#define PN_MODEM_INFO                   197 /* 0xC5  [S] Modem Info Server */
#define PN_RESOURCE_MANAGER             198 /* 0xC6  [S] Resource Manager server */
#define PN_VENDOR_SPECIFIC_TESTS        199 /* 0xC7  [S] Vendor specific production related tests for S40 Chipsets, e.g. RF etc */
#define PN_MODEM_NETWORK                200 /* 0xC8  [S] NET Server in Modem SW, related to PN_NETWORK */
#define PN_MODEM_CALL                   201 /* 0xC9  [S] CALL Server in Modem SW, related to PN_CALL */
#define PN_METADATA                     202 /* 0xCA  [S] Generic Metadata System Server Interface */
#define PN_MODEM_GAN                    203 /* 0xCB  [S] 3GPP GAN Protocol Stack Server */
#define PN_GSM_IO                       204 /* 0xCC  [S] GSM Interoperability server for communication btw GSM, WCDMA RATs */
#define PN_MODEM_CORE                   205 /* 0xCD  [RS] Modem Core Server on L1 processor */
#define PN_EAP_AUTH                     206 /* 0xCE  [S] Extensible Authentication Protocol Server */
#define PN_MY5                          207 /* 0xCF  [S] My5 Protocol server */

/* === PhoNet system resources === */
#define PN_REGISTRATION                 208 /* 0xD0  [PN] PhoNet registration Messages */
#define PN_RPC_REQ                      209 /* 0xD1  [PN] Remote Procedure Call requests */
#define PN_RPC_RESP                     210 /* 0xD2  [PN] Remote Procedure Call responses */

#define PN_SLAVE_LOGOUT                 212 /* 0xD4  [X] */
#define PN_ERROR_INFO                   213 /* 0xD5  [X] */

#define PN_MEDIA_CONTROL                215 /* 0xD7  [PN] Media Module Control Messages */
#define PN_MEDIA_REQUEST                216 /* 0xD8  [X] Check Rasmus */
#define PN_PIPE                         217 /* 0xD9  [PN] Pipe Messages */
#define PN_ALIVE                        218 /* 0xDA  [PN] PhoNet alive messages */
#define PN_NAMESERVICE                  219 /* 0xDB  [PN] Name Service Messages */
#define PN_ROUTER                       220 /* 0xDC  [PN] Router indications */

#define PN_AUTHENTICATION               222 /* 0xDE  [X] Used for SuperDongle challenge/response */
#define PN_DUMMY_RESOURCE               223 /* 0xDF  [X] Dummy resource ID */

/* 32-bit resource id types */
#define PN_PREFIX                       224 /* 0xE0  [P] Enhanced resource id message */
#define PN_PRIVATE                      225 /* 0xE1  [P] Private interface messages */

/* Server resource id's (Part 4) */
#define PN_SOS_AUDIO                    226 /* 0xE2  [S] SOS Audio Server */
#define PN_UI_STARTUP_CTRL              227 /* 0xE3  [S] Startup Control Server */
#define PN_KODIAK                       228 /* 0xE4  [S] KODIAK PoC Server */
#define PN_PAYLOAD_TEST                 229 /* 0xE5  [S] Payload Test Server */

/* === DSP resources === */
#define PN_DSP_CORE                     230 /* 0xE6  [DR] */
#define PN_DSP_VIDEO                    231 /* 0xE7  [DR] */
#define PN_DSP_VOICE                    232 /* 0xE8  [DR] */
#define PN_DSP_MIDI                     233 /* 0xE9  [DR] */
#define PN_ADSP_CORE                    234 /* 0xEA  [DR] */
#define PN_DSP_SELF_TEST                235 /* 0xEB  [DR] */
#define PN_DSP_COMMON_TEST              236 /* 0xEC  [DR] */
#define PN_WCDMA_DSP_CS                 237 /* 0xED  [DR] */
#define PN_WCDMA_DSP_TEST               238 /* 0xEE  [DR] */

#define PN_GSM_DSP_CS                   240 /* 0xF0  [DR] */
#define PN_GSM_DSP_TEST                 241 /* 0xF1  [DR] */
#define PN_GSM_DSP                      242 /* 0xF2  [DR] */
#define PN_DSP_AUDIO                    243 /* 0xF3  [DR] */

#define PN_DSP_GPRS                     253 /* 0xFD  [DR] */
#define PN_DSP_MUSIC                    254 /* 0xFE  [DR] */
#define PN_NO_ROUTING                   255 /* 0xFF */

/******* Extended resource id's *********************/

/* Resource types */
#define PN_RES_TYPE_SOS                   2 /* 0x02 Resources related to SOS */
#define PN_RES_TYPE_SOS_FIELD_TEST        3 /* 0x03 Reserved for identifying S60 owned FTD items,
                                                    no PhoNet resource routing applied for this type.
                                                    The extended resource IDs themselves are defined
                                                    by S60 CellMo adaptation SW elsewhere */
#define PN_RES_TYPE_ISA                   4 /* 0x04 Resources related to ISA */
#define PN_RES_TYPE_MODEM                 5 /* 0x05 Resources related to MODEM */

/* Macro handling extended resource id's */
#define PN_RES(Type, SubType)    (PN_PREFIX  + (Type << 8) + (SubType <<16))

/* === Constants related to extended resource id's === */
#define PN_NUMBER_OF_EXTEND_RES       25 /* Number of extended resources */
#define PN_NUMBER_OF_NOT_EXTEND_RES  256 /* Number of resources in 8 bits */
#define PN_TOTAL_NUMBER_OF_RES   (PN_NUMBER_OF_NOT_EXTEND_RES + PN_NUMBER_OF_EXTEND_RES)

/* Extended resources number example:
   3rd byte.Value        = PN_SOS_MOBILECRASH_EXTENDED
   2nd byte. Value       = PN_RES_TYPE_SOS
   1st byte(LSB). Value  = PN_PREFIX = 0x0E */

/* Extended resources of type: 'PN_RES_TYPE_SOS' */
#define PN_SOS_MOBILECRASH_EXTENDED     PN_RES(PN_RES_TYPE_SOS,1)   /* 0x0102E0  [S] Symbian Mobile Crash Software Server */
#define PN_SOS_DMC_EXTENDED             PN_RES(PN_RES_TYPE_SOS,2)   /* 0x0202E0  [S] Symbian Device Mode Controller */
#define PN_SOS_POWER_EXTENDED           PN_RES(PN_RES_TYPE_SOS,3)   /* 0x0302E0  [S] Symbian Side Power Management */
/* Extended resources of type: 'PN_RES_TYPE_ISA' */
#define PN_MAPS_EXTENDED                PN_RES(PN_RES_TYPE_ISA,1)   /* 0x0104E0  [S] Maps Server */
#define PN_CONTEXT_EXTENDED             PN_RES(PN_RES_TYPE_ISA,2)   /* 0x0204E0  [S] Context Server */
#define PN_NAPPS_EXTENDED               PN_RES(PN_RES_TYPE_ISA,3)   /* 0x0304E0  [S] Native Application Server */
#define PN_NOKIA_ACCOUNT_EXTENDED       PN_RES(PN_RES_TYPE_ISA,4)   /* 0x0404E0  [S] Nokia Account Server */
#define PN_VOLUME_EXTENDED              PN_RES(PN_RES_TYPE_ISA,5)   /* 0x0504E0  [S] Volume Control Server */
#define PN_SM_ROUTER_EXTENDED           PN_RES(PN_RES_TYPE_ISA,6)   /* 0x0604E0  [S] Short Message Router Server */
#define PN_FIREWALL_EXTENDED            PN_RES(PN_RES_TYPE_ISA,7)   /* 0x0704E0  [S] Firewall Server */
#define PN_CMT_EXTENDED                 PN_RES(PN_RES_TYPE_ISA,8)   /* 0x0804E0  [S] Community Server */
#define PN_NTS_EXTENDED                 PN_RES(PN_RES_TYPE_ISA,9)   /* 0x0904E0  [TS] Networking Test Server */
#define PN_POPCATCHER_EXTENDED          PN_RES(PN_RES_TYPE_ISA,10)  /* 0x0A04E0  [RS] PopCatcher Server */
#define PN_ENTITY_LIFECYCLE_EXTENDED    PN_RES(PN_RES_TYPE_ISA,11)  /* 0x0B04E0  [RS] Entity Lifecycle Server */
#define PN_NOTIFICATIONS_EXTENDED       PN_RES(PN_RES_TYPE_ISA,12)  /* 0x0C04E0  [RS] Notifications Server */
#define PN_PWR_RESOURCE_MGR_EXTENDED    PN_RES(PN_RES_TYPE_ISA,13)  /* 0x0D04E0  [TS] Power Resource Manager Server */
#define PN_APPL_RM_EXTENDED             PN_RES(PN_RES_TYPE_ISA,14)  /* 0x0E04E0  [RS] Resource Manager server */
#define PN_ALARM_CLOCK_EXTENDED         PN_RES(PN_RES_TYPE_ISA,15)  /* 0x0F04E0  [RS] Alarm Clock server */
#define PN_RCS_EXTENDED                 PN_RES(PN_RES_TYPE_ISA,16)  /* 0x1004E0  [TS] Rich Communication Suite server */
#define PN_MSRP_EXTENDED                PN_RES(PN_RES_TYPE_ISA,17)  /* 0x1104E0  [TS] Message Session Relay Protocol server */
#define PN_CHAT_EXTENDED                PN_RES(PN_RES_TYPE_ISA,18)  /* 0x1204E0  [TS] Chat server */
#define PN_PANGU_EXTENDED               PN_RES(PN_RES_TYPE_ISA,19)  /* 0x1304E0  [S] PanGu server */
#define PN_CALLLOG_EXTENDED             PN_RES(PN_RES_TYPE_ISA,20)  /* 0x1404E0  [S] Call Log Server */
#define PN_SIM_PROVIDER_EXTENDED        PN_RES(PN_RES_TYPE_ISA,21)  /* 0x1504E0  [S] SIM Provider Server */
#define PN_RCS_APP_EXTENDED             PN_RES(PN_RES_TYPE_ISA,22)  /* 0x1604E0  [S] Rich Communication Suite application */

/* === Old DSP functions. MUST NOT BE USED === */
#define PN_DATA_SEND                    240 /* 0xF0  [X] */
#define PN_RECEIVED_DATA                241 /* 0xF1  [X] */
#define PN_AUDIO_SEND                   242 /* 0xF2  [X] */
#define PN_RECEIVED_AUDIO               243 /* 0xF3  [X] */
#define PN_DSP_TEST_CONTROL             244 /* 0xF4  [X] */
#define PN_DSP_TRACE                    245 /* 0xF5  [X] */
#define PN_DAI_INTERFACE                246 /* 0xF6  [X] */
#define PN_FAST_AT_INPUT                247 /* 0xF7  [X] */
#define PN_FAST_AT_OUTPUT               248 /* 0xF8  [X] */
#define PN_AUDIO_AND_CTRL               249 /* 0xF9  [X] */

/* Aliases. Approved */
#define PN_SIM_ATK                      PN_ATK           /* [A] SIM Application ToolKit */
#define PN_FEATURE_CONTROL              PN_BEARERCTRL    /* [A] Feature Control (application access
                                                               to phone resources) */
#define PN_UTS                          PN_UDM           /* [A] Universal Tool Suite Support Server */
#define PN_SOS_TEST                     PN_EPOC_TEST     /* [A]  */
#define PN_SOS_SELFTEST                 PN_EPOC_SELFTEST /* [A]  */
#define PN_SOS_MON                      PN_EPOC_MON      /* [A] Symbian tracing */
#define PN_MEDIA_TRANSFER               PN_PRINT         /* [A] Media Transfer Server
                                                                (Previous Print Server) */
#define PN_COMMON                       PN_NVD           /* [A] Common server */
#define PN_TRACEBOX                     PN_OSTRICH       /* [A] Used between PC<->Ostrich box */
#define PN_DEV_TRACEBOX                 PN_DEV_OSTRICH   /* [A] Ostrich */
#define PN_HAL_AUDIO                    PN_DSP_AUDIO     /* [A] Chipset Audio HAL */
#define PN_DEV_MODEM_HOST_2             PN_DEV_MODEM     /* [A] Device for modem host 2 */

/* WAVE resource ID aliases */
#if ( SIMULATION_ENVIRONMENT != G_SIMULATION_ENVIRONMENT_NONE )
#ifndef PN_CARDREAD
#define PN_CARDREAD PN_PRJ_RESOURCE_C
#endif
#else
#ifndef PN_CARDREAD
#define PN_CARDREAD PN_SIM
#endif
#endif

/* Aliases. Outdated */
#define PN_UI_SETTINGS                  PN_SETTINGS     /* [X] [A] */
#define PN_EVENT_MANAGE                 PN_COMMGR       /* [X] [A] */
#define PN_POWER                        PN_MTC          /* [X] [A] */
#define PN_DATA                         PN_CSD          /* [X] [A] */
#define PN_CLOCK                        PN_TIME         /* [X] [A] */
#define PN_INFO                         PN_PHONE_INFO   /* [X] [A] */
#define PN_GPRS                         PN_GPDS         /* [X] [A] */
#define PN_PRNT                         PN_PRINT        /* [X] [A] */
#define PN_LOC                          PN_TEST         /* [X] [A] */
#define PN_LOC_WT                       PN_WARRANTY     /* [X] [A] */
#define PN_FLASHBOX                     PN_SECBOX       /* [X] [A] */
#define PN_VCS                          PN_VERSIT       /* [X] [A] */
#define PN_VCF                          PN_VERSIT       /* [X] [A] */
#define PN_RPC_RES                      PN_RPC_RESP     /* [X] [A] */
#define PN_NAME_SERVICE                 PN_NAMESERVICE  /* [X] [A] */
#define PN_NET                          PN_NETWORK      /* [X] [A] */

/* Dummied resource IDs */
#define PN_NAM                          PN_DUMMY_RESOURCE
#define PN_DAMPS_DSP_CS                 PN_DUMMY_RESOURCE
#define PN_DAMPS_DSP_TEST               PN_DUMMY_RESOURCE
#define PN_DAMPS_DSP                    PN_DUMMY_RESOURCE
#define PN_TETRA_DSP                    PN_DUMMY_RESOURCE
#define PN_TETRA_DSP_TEST               PN_DUMMY_RESOURCE
#define PN_TETRA_DSP_CS                 PN_DUMMY_RESOURCE


/* === PN_DEV_CONNECTION_INFO sub functions === */
#define PNS_DEV_CONNECTED              0x01 /* 1 */
#define PNS_DEV_DISCONNECTED           0x02 /* 2 */

/* === PN_ERROR_INFO sub functions === */
#define PNS_FAIL_REGISTRATION          0x01 /* 1 */
#define PNS_FAIL_SYSTEM_REQ            0x02 /* 2 */
#define PNS_FAIL_FUNCTION_ROUTING      0x03 /* 3 */
#define PNS_FAIL_OBJECT_ROUTING        0x04 /* 4 */
#define PNS_FAIL_MSG_SENDING           0x05 /* 5 */
#define PNS_FAIL_DEV_INACTIVE          0x06 /* 6 */
#define PNS_FAIL_OS_MBX_FULL           0x07 /* 7 */

#endif /* #ifndef PN_CONST_H */

/*  End of pn_const.h  */
