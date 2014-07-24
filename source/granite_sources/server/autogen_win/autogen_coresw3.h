/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw3.h
                -----------------
                SW Include






Project:          autogen

%name:            autogen_coresw3.h %
%version:         co1tss#38 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Tue Feb 08 10:55:11 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes third part of core message definition files
*/

#if (ICF_MUSIC_SERV == ON)
 #include "music_isi_m.h"
 #if (ICF_BT_AUDIO_STREAMING == ON)
  #include "a2dp_isi_m.h"
 #else
  printf("* ICF_BT_AUDIO_STREAMING is OFF. Excluding 'a2dp_isi_m.h'\n");
 #endif
#else
 printf("* ICF_MUSIC_SERV is OFF. Excluding 'music_isi_m.h'\n");
#endif /* ICF_MUSIC_SERV == ON */


#if (ICF_NFC_SERV == ON)
 #include "nfc_serv_isi_m.h"
#else
 printf("* ICF_NFC_SERV is OFF. Excluding 'nfc_serv_isi_m.h'\n");
#endif /* ICF_NFC_SERV */


#if (ICF_NETWORKING_TEST_SERVER == ON)
 #include "nts_isi_m.h"
#else
 printf("* ICF_NETWORKING_TEST_SERVER is OFF. Excluding 'nts_isi_m.h'\n");
#endif /* ICF_NETWORKING_TEST_SERVER == ON */


#if (ICF_NVD_SERV == ON)
 #include "nvd_isi_m.h"
#else
 printf("* ICF_NVD_SERV is OFF. Excluding 'nvd_isi_m.h'\n");
#endif /* ICF_NVD_SERV == ON */


#if (ICF_OBEX_SERV == ON)
 #include "obex_isi_m.h"
#else
 printf("* ICF_OBEX_SERV is OFF. Excluding 'obex_isi_m.h'\n");
#endif /* ICF_OBEX_SERV == ON */


#if (ICF_ODIN_SERV == ON)
 #include "odin_isi_m.h"
#else
 printf("* ICF_ODIN_SERV is OFF. Excluding 'odin_isi_m.h'\n");
#endif /* ICF_ODIN_SERV == ON */


#if (ICF_PERM_SERV == ON)
 #include "perm_isi_m.h"
#else
 printf("* ICF_PERM_SERV is OFF. Excluding 'perm_isi_m.h'\n");
#endif /* ICF_PERM_SERV == ON */


#if (ICF_POWER_RESOURCE_MANAGER == ON)
 #include "prm_isi_m.h"
#else
 printf("* ICF_POWER_RESOURCE_MANAGER is OFF\n");
#endif


#if (ICF_FM_RADIO_SERV == ON)
 #include "radio_isi_m.h"
#else
 printf("* ICF_FM_RADIO_SERV is OFF. Excluding 'radio_isi_m.h'\n");
#endif /* ICF_FM_RADIO_SERV == ON */


#if (ICF_RMAN_SERV == ON)
 #include "rman_isi_m.h"
#else
 printf("* ICF_RMAN_SERV is OFF. Excluding 'rman_isi_m.h'\n");
#endif /* ICF_RMAN_SERV == ON */


#if (ICF_SECURITY == ON)
 #include "srvsec_isi_m.h"
#else
 printf("* ICF_SECURITY is OFF. Excluding 'srvsec_isi_m.h'\n");
#endif /* ICF_SECURITY == ON */


#if (ICF_SENSOR_SERV == ON)
 #include "sensor_isi_m.h"
#else
 printf("* ICF_SENSOR_SERV is OFF. Excluding 'sensor_isi_m.h'\n");
#endif /* ICF_SENSOR_SERV == ON */


#if (ICF_ASIM_SIM == ON)
 #include "sim_isi_m.h"
 #include "sim_dual_isi_m.h"
#else
 printf("*ICF_ASIM_SIM are OFF. Excluding 'sim_isi_m.h' and 'sim_dual_isi_m.h'\n");
#endif /* ICF_ASIM_SIM == ON */


#if (ICF_SIMLOCK == ON)
 #include "simlock_isi_m.h"
#else
 printf("* ICF_SIMLOCK is OFF. Excluding 'simlock_isi_m.h'\n");
#endif /* ICF_SIMLOCK == ON */


#if ((ICF_SOS_PROXY == ON) || (ICF_PN_MEDIA_SOS == ON))
 #if (ICF_PERM_SERV == ON)
  #include "sos_perm_isi_m.h"
 #else
  printf("* ICF_PERM_SERV is OFF. Excluding 'sos_perm_isi_m.h'\n");
 #endif /* ICF_PERM_SERV == ON */
#endif /* ICF_SOS_PROXY == ON */



/*  End of file autogen_coresw3.h */
