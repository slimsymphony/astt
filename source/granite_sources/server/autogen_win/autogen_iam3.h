/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_iam3.h
                -------------
                SW Include






Project:          autogen

%name:            autogen_iam3.h %
%version:         14 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Fri Jan 07 16:36:12 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes third part of IAM message definition files
*/

#ifdef PN_OBJ_PANEL
 #include "i_panel_isi_m.h"
#else
 printf("* PN_OBJ_PANEL not in product. Excluding 'i_panel_isi_m.h'\n");
#endif /* PN_OBJ_PANEL */


#ifdef PN_OBJ_PAYLOAD_TEST_SRV
 #include "payload_test_srv_isi_m.h"
#else
 printf("* PN_OBJ_PAYLOAD_TEST_SRV is not defined. Excluding 'payload_test_srv_isi_m.h'\n");
#endif /* PN_OBJ_PAYLOAD_TEST_SRV */

#ifdef PN_OBJ_PHONEBOOK_SERV
 #include "pnd_isi_m.h"
#else
 printf("* PN_OBJ_PHONEBOOK_SERV not in product. Excluding 'pnd_isi_m.h'\n");
#endif /* PN_OBJ_PHONEBOOK_SERV */


#ifdef PRODUCT_INCLUDES_OMA_POC
 #include "poc_call_isi_m.h"
#else
 printf("* PRODUCT_INCLUDES_OMA_POC is not defined. Excluding 'poc_call_isi_m.h'\n");
#endif /* PRODUCT_INCLUDES_OMA_POC */


#ifdef PN_OBJ_POC_UI_SERV
 #include "poc_ui_isi_m.h"
#else
 printf("* PN_OBJ_POC_UI_SERV not in product. Excluding 'poc_ui_isi_m.h'\n");
#endif /* PN_OBJ_POC_UI_SERV */


#ifdef PN_OBJ_POPCATCHER
 #include "popc_isi_m.h"
#else
 printf("* PN_OBJ_POPCATCHER not in product. Excluding 'popc_isi_m.h'\n");
#endif /* PN_OBJ_POPCATCHERV */


#ifdef PN_OBJ_PRESENCE_SERV
 #include "presence_isi_m.h"
#else
 printf("* PN_OBJ_PRESENCE_SERV not in product. Excluding 'presence_isi_m.h'\n");
#endif /* PN_OBJ_PRESENCE_SERV */


#ifdef PN_OBJ_PROV_SERV
 #include "prov_isi_m.h"
#else
 printf("* PN_OBJ_PROV_SERV not in product. Exclusing 'prov_isi_m.h'\n");
#endif /* PN_OBJ_PROV_SERV */

#ifdef PRODUCT_INCLUDES_PTT_SERVER
 #include "ptt_isi_m.h"
#else
 printf("* PRODUCT_INCLUDES_PTT_SERVER not in product. Excluding 'ptt_isi_m.h'\n");
#endif /* PRODUCT_INCLUDES_PTT_SERVER */


#ifdef PN_OBJ_RTP_SERV
 #include "rtp_isi_m.h"
#else
 printf("* PN_OBJ_RTP_SERV is not defined. Excluding 'rtp_isi_m.h'\n");
#endif /* PN_OBJ_RTP_SERV == ON */


#ifdef PN_OBJ_RTSP_SERV
 #include "rtsp_isi_m.h"
#else
 printf("* PN_OBJ_RTSP_SERV is not defined. Excluding 'rtsp_isi_m.h'\n");
#endif /* PN_OBJ_RTSP_SERV == ON */


#if (defined(PN_OBJ_SIP_SERV) || defined(PN_OBJ_SIP_V2_SERV))
 #include "sip_isi_m.h"
#else
 printf("* PN_OBJ_SIP_SERV or PN_OBJ_SIP_V2_SERV are not defined. Excluding 'sip_isi_m.h'\n");
#endif /* PN_OBJ_SIP_SERV || PN_OBJ_SIP_V2_SERV */


#ifdef PN_OBJ_SAPI_TEST_SERV
 #include "sapi_test_srv_isi_m.h" 
#else
 printf("* PN_OBJ_SAPI_TEST_SERV not in product. Excluding 'sapi_test_srv_isi_m.h'\n");
#endif

#ifdef PN_OBJ_SCREENSAVER_SRV
 #include "screensaver_isi_m.h"
#else
 printf("* PN_OBJ_SCREENSAVER_SRV not in product. Excluding 'screensaver_isi_m.h'\n");
#endif /* PN_OBJ_SCREENSAVER_SRV */

#ifdef PN_OBJ_SM_ROUTER
 #include "sm_router_isi_m.h"
#else
 printf("* PN_OBJ_SM_ROUTER not in product. Excluding 'sm_router_isi_m.h'\n");
#endif /* PN_OBJ_SM_ROUTER */


#ifdef PN_OBJ_SMS_MEMORY_SERV
 #include "srv_sms_memory_isi_m.h"
#else
 printf("* PN_OBJ_SMS_MEMORY_SERV not in product. Excluding 'srv_sms_memory_isi_m.h'\n");
#endif /* PN_OBJ_PROV_SERV */


#ifdef PN_OBJ_SYNCML_SERV
 #include "syncmlsrv_isi_m.h"
#else
 printf("* PN_OBJ_SYNCML_SERV not in product. Excluding 'syncmlsrv_isi_m.h'\n");
#endif /* PN_OBJ_SYNCML_SERV */


#ifdef PN_OBJ_THEMES_SERV
 #include "themes_isi_m.h"
#else
 printf("* PN_OBJ_THEMES_SERV not in product. Exclusing 'themes_isi_m.h'\n");
#endif /* PN_OBJ_THEMES_SERV */


#ifdef PN_OBJ_TONE_SERV
 #include "tone_isi_m.h"
#else
 printf("* PN_OBJ_TONE_SERV not in product. Excluding 'tone_isi_m.h'\n");
#endif /* PN_OBJ_TONE_SERV */


#ifdef PN_OBJ_TRACFONE
 #include "tracfone_isi_m.h"
#else
 printf("* PN_OBJ_TRACFONE not in product. Excluding 'tracfone_isi_m.h'\n");
#endif /* PN_OBJ_TRACFONE */


#ifdef PN_OBJ_UI_STARTUP_CTRL_SERV
 #include "ui_startup_ctrl_isi_m.h"
#else
 printf("* PN_OBJ_UI_STARTUP_CTRL_SERV not in product. Excluding 'ui_startup_ctrl_isi_m.h'\n");
#endif /* PN_OBJ_UI_STARTUP_CTRL_SERV */


#ifdef PN_OBJ_UPF_SERV
 #include "autogen_upf.h"
#else
 printf("* PN_OBJ_UPF_SERV not in product. Excluding 'autogen_upf.h'\n");
#endif /* PN_OBJ_UPF_SERV */


#ifdef PN_OBJ_VERSIT_SERV
 #include "versit_isi_m.h"
#else
 printf("* PN_OBJ_VERSIT_SERV not in product. Excluding 'versit_isi_m.h'\n");
#endif /* PN_OBJ_VERSIT_SERV */


#ifdef PN_OBJ_VIDEO_SERV
 #include "vip_isi_m.h"
#else
 printf("* PN_OBJ_VIDEO_SERV not in product. Excluding 'vip_isi_m.h'\n");
#endif /* PN_OBJ_VIDEO_SERV */


#ifdef PN_OBJ_VOICE_SERV
 #include "srvvoice_isi_m.h"
#else
 printf("* PN_OBJ_VOICE_SERV not in product. Excluding 'srvvoice_isi_m.h'\n");
#endif /* PN_OBJ_VOICE_SERV */


#ifdef PN_OBJ_VOL_CTRL_SERV
 #include "vol_ctrl_isi_m.h"
#else
 printf("* PN_OBJ_VOL_CTRL_SERV not in product. Excluding 'vol_ctrl_isi_m.h'\n");
#endif /* PN_OBJ_VOL_CTRL_SERV */


#ifdef PN_OBJ_WAP_CONN_SERV
 #include "wapconn_isi_m.h"
#else
 printf("* PN_OBJ_WAP_CONN_SERV not in product. Excluding 'wapconn_isi_m.h'\n");
#endif /* PN_OBJ_WAP_CONN_SERV */


#ifdef PN_OBJ_WIM_SERV
 #include "wim_isi_m.h"
#else
 printf("* PN_OBJ_WIM_SERV not in product\n");
#endif /* PN_OBJ_WIM_SERV */


#ifdef PN_OBJ_WDP_SERV
 #include "wdp_isi_m.h"
#else
 printf("* PN_OBJ_WDP_SERV not in product. Excluding 'wdp_isi_m.h'\n");
#endif /* PN_OBJ_WDP_SERV */


#if PN_OBJ_WSP_SERV
/* 
 #include "wsp_isi_m.h" 
*/
 printf("* Macro file wsp_isi_m.h will eventually be included...\n");
#else
 printf("* PN_OBJ_WSP_SERV not in product\n");
#endif /* PN_OBJ_WSP_SERV */


#ifdef PN_OBJ_XCAP_SERV
 #include "xcap_isi_m.h"
#else
 printf("* PN_OBJ_XCAP_SERV not in product. Excluding 'xcap_isi_m.h'\n");
#endif /* PN_OBJ_XCAP_SERV */




/*  End of file autogen_iam.h */
