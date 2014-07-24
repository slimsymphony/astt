/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw.h
                ----------------
                SW Include






Project:          autogen

%name:            autogen_coresw.h %
%version:         co1tss#34 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Fri Feb 04 13:54:01 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes first part of core (non CL) message definition files
*/

#if (ICF_BCS_SERV == ON)
 #include "bearerctrl_isi_m.h"
 #if (ICF_FEATURE_CONTROL == ON)
  #include "featurectrl_isi_m.h"
 #else
  printf("* ICF_FEATURE_CONTROL is OFF. Excluding 'featurectrl_isi_m.h'\n");
 #endif /* ICF_FEATURE_CONTROL == ON */
#else
  printf("* ICF_BCS_SERV is OFF. Excluding 'bearerctrl_isi_m.h'\n");
#endif /* ICF_BCS_SERV == ON */


#if (ICF_SERVERS == ON)
 #include "comm_isi_m.h"
 #define COMMON_MESSAGES_EXTENDED_INTERFACE
 #include "comm_isi_m.h"
#else
 printf("* ICF_SERVERS is OFF. Excluding 'comm_isi_m.h'\n");
#endif /* ICF_SERVERS == ON */


#if (ICF_ACC_SERV == ON)
 #include "acc_isi_m.h"
#else
 printf("* ICF_ACC_SERV is OFF. Excluding 'acc_isi_m.h'\n");
#endif /* ICF_ACC_SERV == ON */


#if (ICF_ADL_SERV == ON)
 #include "adl_isi_m.h"
#else
 printf("* ICF_ADL_SERV is OFF. Excluding 'adl_isi_m.h'\n");
#endif /* ICF_ADL_SERV == ON */


#if (ICF_ATK == ON)
 #include "atk_isi_m.h"
#else
 printf("* ICF_ATK is OFF. Excluding 'atk_isi_m.h'\n");
#endif /* ICF_ATK == ON */


#if (ICF_AUDIO_SERV == ON)
 #include "aud_isi_m.h"
 #if ((defined ICF_CHIPSET_API) && (ICF_CHIPSET_API == ON)) 
  #include "audio_chipset_api_m.h"
 #else
  printf(" ICF_CHIPSET_API is OFF. Excluding audio_chipset_api_m.h'\n ");
 #endif  /* defined ICF_CHIPSET_API */ 
#else
 printf("* ICF_AUDIO_SERV is OFF. Excluding 'aud_isi_m.h'\n");
#endif /* ICF_AUDIO_SERV == ON */


#if (ICF_BTCS_SERV == ON)
 #include "btcs_isi_m.h"
#else
 printf("* ICF_BTCS_SERV is OFF. Excluding 'btcs_isi_m.h'\n");
#endif /* ICF_BTCS_SERV == ON */


#if (ICF_CAMERA_SERV == ON)
 #define CAMERA_INCLUDE_PRIVATE_INTERFACE
 #include "camera_isi_m.h"
#else
 printf("* ICF_CAMERA_SERV is OFF. Excluding 'camera_isi_m.h'\n");
#endif /* ICF_CAMERA_SERV == ON */


#if (ICF_EM == ON)
 #include "em_isi_m.h"
#else
 printf("* ICF_EM is OFF. Excluding 'em_isi_m.h'\n");
#endif /* ICF_EM == ON */

/*  End of file autogen_coresw.h */
