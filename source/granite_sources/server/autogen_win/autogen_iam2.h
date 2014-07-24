/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_iam2.h
                -------------
                SW Include






Project:          autogen

%name:            autogen_iam2.h %
%version:         10 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Tue Oct 05 11:03:42 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes second part of IAM message definition files
*/

#ifdef PN_OBJ_JAVA_SERV
 #include "java_isi_m.h"
#else
 printf("* PN_OBJ_JAVA_SERV not in product. Excluding 'java_isi_m.h'\n");
#endif /* PN_OBJ_JAVA_SERV */

#ifdef PN_OBJ_KEYGUARD_SRV
 #include "keyguard_isi_m.h"
#else
 printf("* PN_OBJ_KEYGUARD_SRV not in product. Excluding 'keyguard_isi_m.h'\n");
#endif /* PN_OBJ_KEYGUARD_SRV */

#ifdef PN_OBJ_KODIAK_SRV
 #include "kodiak_isi_m.h"
#else
 printf("* PN_OBJ_KODIAK_SRV is not in product. Excluding 'kodiak_isi_m.h'\n");
#endif /* PN_OBJ_KODIAK_SRV */


#ifdef PN_OBJ_LANDMARK_SERV
 #include "landmark_isi_m.h"
#else
 printf("* PN_OBJ_LANDMARK_SERV is not in product. Excluding 'landmark_isi_m.h'\n");
#endif /* PN_OBJ_LANDMARK_SERV */


#ifdef PN_OBJ_LCIF
 #include "lcif_isi_m.h"
 #include "lcif_prot_m.h"
 #include "lcif_call_m.h"
 #include "lcif_mp_m.h"
 #include "lcif_time_m.h"
 #include "lcif_contacts_m.h"
 #include "lcif_phonecontrol_m.h"
 #include "lcif_radio_m.h"
 #include "lcif_voice_dial_m.h"
 #include "lcif_language_m.h"
 #include "lcif_phoneinfo_m.h"
 #include "lcif_sd_m.h"
 #include "lcif_volume_m.h"
 #include "lcif_messaging_m.h"
 #include "lcif_poc_m.h"    
 #include "lcif_sec_m.h"
#else
 printf("* PN_OBJ_LCIF is not in product. Excluding 'lcif_*.h'\n");
#endif /* PN_OBJ_LCIF */


#ifdef PN_OBJ_LCS_UI_SERV
 #include "lcs_ui_isi_m.h"
#else
 printf("* PN_OBJ_LCS_UI_SERV not in product. Excluding 'lcs_ui_isi_m.h'\n");
#endif /* PN_OBJ_LCS_UI_SERV */

#ifdef PN_OBJ_LIGHT_UI_SRV
 #include "light_ui_isi_m.h"
#else
 printf("* PN_OBJ_LIGHT_UI_SRV not in product. Excluding 'light_ui_isi_m.h'\n");
#endif /* PN_OBJ_LIGHT_UI_SRV */

#ifdef PN_OBJ_DYNAMIC_LOADER_SERV
 #include "ld_isi_m.h"
#else
 printf("* PN_OBJ_DYNAMIC_LOAD_SERV not in product. Excluding 'ld_isi_m.h'\n");
#endif /* PN_OBJ_DYNAMIC_LOAD_SERV */

#ifdef PN_OBJ_MDS_SERV
 #include "mds_isi_m.h"
#else
 printf("* PN_OBJ_MDS_SERV not in product. Excluding 'mds_isi_m.h'\n");
#endif /* PN_OBJ_MDS_SERV */

#ifdef PN_OBJ_MENU_SERV
 #include "menu_isi_m.h"
#else
 printf("* PN_OBJ_MENU_SERV not in product. Excluding 'menu_isi_m.h'\n");
#endif /* PN_OBJ_MENU_SERV */


#ifdef PN_OBJ_MES_SERV
 #include "mes_isi_m.h"
#else
 printf("* PN_OBJ_MES_SERV not in product. Excluding 'mes_isi_m.h'\n");
#endif /* PN_OBJ_MES_SERV */


#ifdef PN_OBJ_MESSAGE_STORAGE
 #include "message_storage_isi_m.h"
#else
 printf("* PN_OBJ_MESSAGE_STORAGE not in product. Excluding 'message_storage_isi_m.h'\n");
#endif /* PN_OBJ_MESSAGE_STORAGE */


#ifdef PN_OBJ_MESSAGING
 #include "srv_messaging_isi_m.h"
#else
 printf("* PN_OBJ_MESSAGING not in product. Excluding 'srv_messaging_isi_m.h'\n");
#endif /* PN_OBJ_MESSAGING */


#ifdef PN_OBJ_MULTI_SIM
 #include "multi_sim_isi_m.h"
#else
 printf("* PN_OBJ_MULTI_SIM not in product. Excluding 'multi_sim_isi_m.h'\n");
#endif /* PN_OBJ_MULTI_SIM */


#ifdef PN_OBJ_MY5_SERV
 #include "my5_isi_m.h"
#else
 printf("* PN_OBJ_MY5_SERV not in product. Excluding 'my5_isi_m.h'\n");
#endif /* PN_OBJ_MY5_SERV */


#ifdef PN_OBJ_NAPPS_EXTENDED
 #include "nam_isi_m.h"
#else
 printf("* PN_OBJ_NAPPS_EXTENDED not in product. Excluding 'nam_isi_m.h'\n");
#endif

#ifdef PN_OBJ_NOA_APPL
 #include "noa_appl_internal_msg_m.h"
#else
 printf("* PN_OBJ_NOA_APPL is not defined. Excluding 'noa_appl_internal_msg_m.h'\n");
#endif /* PN_OBJ_NOA_APPL */

#ifdef PN_OBJ_NOA_SERV
 #include "noa_isi_m.h"
 #include "noa_internal_msg_m.h"
#else
 printf("* PN_OBJ_NOA_SERV is not defined. Excluding 'noa_isi_m.h'\n");
 printf("* PN_OBJ_NOA_SERV is not defined. Excluding 'noa_internal_msg_m.h'\n");
#endif /* PN_OBJ_NOA_SERV */


#ifdef PN_OBJ_NWSD_SERV
 #include "nwsd_isi_m.h"
#else
 printf("* PN_OBJ_NWSD_SERV not in product. Excluding 'nwsd_isi_m.h'\n");
#endif /* PN_OBJ_NWSD_SERV */



/*  End of file autogen_iam2.h */
