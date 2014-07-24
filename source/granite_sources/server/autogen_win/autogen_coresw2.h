/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw2.h
                -----------------
                SW Include






Project:          autogen

%name:            autogen_coresw2.h %
%version:         co1tss#30 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Tue Mar 22 10:22:25 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes second part of core (non CL) message definition files
*/

#if (ICF_FILE_SERV == ON)
 #include "file_isi_m.h"
#else
 printf("* ICF_FILE_SERV is OFF. Excluding 'file_isi_m.h'\n");
#endif /* ICF_FILE_SERV == ON */


#if (ICF_HARDCORE_SERV == ON)
 #include "hardcore_isi_m.h"
#else
 printf("* ICF_HARDCORE_SERV is OFF. Excluding 'hardcore_isi_m.h'\n");
#endif /* ICF_HARDCORE_SERV == ON */


#if (ICF_IKE == ON)
 #include "ike_isi_m.h"
#else
 printf("* ICF_IKE is OFF. Excluding 'ike_isi_m.h'\n");
#endif /* ICF_IKE == ON */


#if (ICF_INFO_SERV == ON)
 #include "info_isi_m.h"
#else
 printf("* ICF_INFO_SERV is OFF. Excluding 'info_isi_m.h'\n");
#endif /* ICF_INFO_SERV == ON */


#if (ICF_JSR82_SUPPORT == ON)
 #include "jsr82server_isi_m.h"
#else
 printf("* ICF_JSR82_SUPPORT is OFF. Excluding 'jsr82server_isi_m.h'\n");
#endif /* ICF_JSR82_SUPPORT == ON */


#if (ICF_KBD_SERV == ON)
 #include "kbd_isi_m.h"
#else
 printf("* ICF_KBD_SERV is OFF. Excluding 'kbd_isi_m.h'\n");
#endif /* ICF_KBD_SERV == ON */

 
#if (ICF_LIGHT_SERV == ON)
 #include "light_isi_m.h"
#else
 printf("* ICF_LIGHT_SERV is OFF. Excluding 'light_isi_m.h'\n");
#endif /* ICF_LIGHT_SERV == ON */


#if (ICF_LOCATION_SERV == ON)
 #include "location_isi_m.h"
 #if !(ICF_GPS_CHIP == ICF_OFF) && (SIMULATION_ENVIRONMENT == G_SIMULATION_ENVIRONMENT_NONE)
  #include "npe_if_m.h"
 #endif
#else
 printf("* ICF_LOCATION_SERV is OFF. Excluding 'location_isi_m.h'\n");
#endif /* ICF_LOCATION_SERV == ON */


#if (ICF_LOCOS_SERV == ON)
 #include "locos_isi_m.h"
#else
 printf("* ICF_LOCOS_SERV is OFF. Excluding 'locos_isi_m.h'\n");
#endif /* ICF_LOCOS_SERV */


#if (ICF_MOP_SERV == ON)
 #include "mop_isi_m.h"
#else
 printf("* ICF_MOP_SERV is OFF. Excluding 'mop_isi_m.h'\n");
#endif /* ICF_MOP_SERV == ON */


#if (ICF_MTC_SERV == ON)
 #include "mtc_isi_m.h"
#else
 printf("* ICF_MTC_SERV is OFF. Excluding 'mtc_isi_m.h'\n");
#endif /* ICF_MTC_SERV == ON */

/*  End of file autogen_coresw2.h */
