/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw4.h
                -----------------
                SW Include






Project:          autogen

%name:            autogen_coresw4.h %
%version:         8 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Tue Feb 08 10:25:36 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes fourth part of core message definition files
*/

#if (ICF_SSL == ON)
 #include "ssl_isi_m.h"
#else
 printf("* ICF_SSL is OFF. Excluding 'ssl_isi_m.h'\n");
#endif /* ICF_SSL == ON */


#if (ICF_ST_SERV == ON)
 #include "st_isi_m.h"
#else
 printf("* ICF_ST_SERV is OFF. Excluding 'st_isi_m.h'\n");
#endif /* ICF_ST_SERV == ON */


#if (ICF_TEST_SERV == ON)
 #include "test_isi_m.h"
 #include "test_master_test_isi_m.h"
#else
 printf("* ICF_TEST_SERV is OFF. Excluding 'test_isi_m.h'\n");
#endif /* ICF_TEST_SERV == ON */


#if (ICF_TIME_SERV == ON)
 #include "time_isi_m.h"
#else
 printf("* ICF_TIME_SERV is OFF. Excluding 'time_isi_m.h'\n");
#endif /* ICF_TIME_SERV == ON */


#if (ICF_TNT_SERV == ON)
 #include "tnt_isi_m.h"
#else
 printf("* ICF_TNT_SERV is OFF. Excluding 'tnt_isi_m.h'\n");
#endif /* ICF_TNT_SERV == ON */


#if (ICF_TOUCHPAD_SERV == ON)
 #include "touchpad_isi_m.h"
#else
 printf("* ICF_TOUCHPAD_SERV is OFF. Excluding 'touchpad_isi_m.h'\n");
#endif /* ICF_TOUCHPAD_SERV == ON */


#if (ICF_TUNEPLAYER_SERV == ON)
 #include "tuneplayer_isi_m.h"
#else
 printf("* ICF_TUNEPLAYER_SERV is OFF. Excluding 'tuneplayer_isi_m.h'\n");
#endif /* ICF_TUNEPLAYER_SERV == ON */


#if (ICF_VRR_SERV == ON)
 #include "vrr_isi_m.h"
#else
 printf("* ICF_VRR_SERV is OFF. Excluding 'vrr_isi_m.h'\n");
#endif /* ICF_VRR_SERV == ON */


#if (ICF_VIDEO_RECORDER == ON)
 #include "trackrec_isi_m.h"
 #include "mux_isi_m.h"
#else
 printf("* ICF_VIDEO_RECORDER is OFF. Excluding 'trackrec_isi_m.h'\n");
 printf("* ICF_VIDEO_RECORDER is OFF. Excluding 'mux_isi_m.h'\n");
#endif /* ICF_VIDEO_RECORDER == ON */

#if (ICF_PRINT_SERV == ON)
 #include "print_isi_m.h"
 #include "mts_isi_m.h"
#else
 printf("* ICF_PRINT_SERV is OFF. Excluding 'print_isi_m.h'\n");
 printf("* ICF_PRINT_SERV is OFF. Excluding 'mts_isi_m.h'\n");
#endif /* ICF_PRINT_SERV == ON */

#if (ICF_WLAN == ON)
 #include "wlan_isi_m.h" 
 #include "eap_isi_m.h"
#else
 printf("* ICF_WLAN is OFF\n");
#endif /* ICF_WLAN == ON */


/*  End of file autogen_coresw4.h */
