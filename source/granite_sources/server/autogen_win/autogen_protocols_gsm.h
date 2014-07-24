/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols_gsm.h
                -----------------------
                SW Include






Project:          autogen

%name:            autogen_protocols_gsm.h %
%version:         co1tss#23 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Fri Jan 07 16:26:04 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes GSM protocol message definition files
*/

#define GSM_DSP_CS_GENERATE_CS_PH_VARIANT
#include "gsm_dsp_ph_cs_isi_m.h"


#ifdef PN_OBJ_CALL_SERV
 #if (IPF_ISA_PLATFORM == IPF_ISA3)
  #if (defined PN_OBJ_COMMON_CALL_SERV)
   #include "call_modem_isi_m.h" 
   #include "call_isi_m.h" 
   #include "call_privat_isi_m.h"
  #else
   #include "call_isi_m.h" 
   #include "call_privat_isi_m.h" 
  #endif
 #else
  printf("* ISA3 not supported. Excluding 'call_isi_m.h'\n");
 #endif /* IPF_ISA_PLATFORM == IPF_ISA3 */
#endif /* PN_OBJ_CALL_SERV */

#if (IPF_CSD_AT_COMMAND_INTERPRETER == ON)
 #include "csd_isi_m.h" 
#else
 printf("* IPF_CSD_AT_COMMAND_INTERPRETER is OFF. Excluding 'csd_isi_m.h'\n");
#endif /* IPF_CSD_AT_COMMAND_INTERPRETER == ON */

#ifdef PN_OBJ_AT_MODEM_SRV
 #include "at_modem_isi_m.h"
#else
 printf("* PN_OBJ_AT_MODEM_SRV not in product. Excluding 'at_modem_isi_m.h'\n");
#endif /* PN_OBJ_AT_MODEM_SRV */

#if (SIMULATION_ENVIRONMENT == G_SIMULATION_ENVIRONMENT_NONE)
#if (ICF_CHIPSET_API == OFF)
#if (IPF_GSM_RAT == ON)
 #include "ranc_autogen_hdrs.h" 
#else
 printf("* IPF_GSM_RAT is OFF. Excluding 'ranc_autogen_hdrs.h'\n");
#endif /* IPF_GSM_RAT == ON */


#if (IPF_GSM_RAT == ON)
 #include "geran_autogen_hdrs.h" 
#else
 printf("* IPF_GSM_RAT is OFF. Excluding 'geran_autogen_hdrs.h'\n");
#endif /* IPF_GSM_RAT == ON */
#endif /* ICF_CHIPSET_API == OFF*/
#endif /* SIMULATION_ENVIRONMENT == G_SIMULATION_ENVIRONMENT_NONE */

#if (defined(PN_OBJ_LCS_SERV) || defined(PN_OBJ_MODEM_LCS))
 #include "modem_lcs_isi_m.h" 
#else
 printf("* PN_OBJ_MODEM_LCS not in product. Excluding 'modem_lcs_isi_m.h'\n");
#endif /* PN_OBJ_MODEM_LCS */

#ifdef PN_OBJ_GPDS
 #include "gpds_isi_m.h" 
#else
 printf("* PN_OBJ_GPDS not in product. Excluding 'gpds_isi_m.h'\n");
#endif /* PN_OBJ_GPDS */


#ifdef PN_OBJ_GSS_SERV
 #include "gss_isi_m.h" 
#else
 printf("* PN_OBJ_GSS_SERV not in product. Excluding 'gss_isi_m.h'\n");
#endif /* PN_OBJ_GSS_SERV */


#ifdef PN_OBJ_MODEM_GAN_SERV
 #include "gan_wm_isi_m.h" 
#else
 printf("* PN_OBJ_MODEM_GAN_SERV not in product. Excluding 'gan_wm_isi_m.h'\n");
#endif /* PN_OBJ_MODEM_GAN_SERV */


#ifdef PN_OBJ_MODEM_SIM_SERV
 #include "msim_isi_m.h"
#endif /* PN_OBJ_MODEM_SIM_SERV */


#ifdef PN_OBJ_NET_SERV
 #include "net_isi_m.h"
#else
 printf("* PN_OBJ_NET_SERV not in product. Excluding 'net_isi_m.h'\n");
#endif /* PN_OBJ_NET_SERV */


#if ( defined (PN_OBJ_NET_SERV) || defined (PN_OBJ_MODEM_NET_SERV) )
 #include "net_modem_isi_m.h"
#else
 printf("* PN_OBJ_NET_SERV and PN_OBJ_MODEM_NET_SERV not in product. Excluding 'net_modem_isi_m.h'\n");
#endif /* PN_OBJ_NET_SERV || PN_OBJ_MODEM_NET_SERV */


#ifdef PN_OBJ_SMS_SERV
 #include "sms_isi_m.h"
#else
 printf("* PN_OBJ_SMS_SERV not in product. Excluding 'sms_isi_m.h'\n");
#endif /* PN_OBJ_SMS_SERV */


#ifdef PN_OBJ_SS_SERV
 #if (IPF_ISA_PLATFORM == IPF_ISA3)
  #include "ss_isi_m.h"
 #else
  printf("* IPF_ISA3 not supported. Excluding 'ss_isi_m.h'\n");
 #endif /* IPF_ISA_PLATFORM == IPF_ISA3 */
#endif /* PN_OBJ_SS_SERV */


#ifdef PN_OBJ_UICC_SERV
 #include "uicc_isi_m.h"
#endif /* PN_OBJ_UICC_SERV */


/*  End of file autogen_protocols_gsm.h */
