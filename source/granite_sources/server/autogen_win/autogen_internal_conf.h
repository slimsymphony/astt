/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_def.h
                -------------
                SW Include






Project:          autogen

%name:            autogen_internal_conf.h %
%version:         27 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Tue Mar 01 14:10:35 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains internal definitions and includes
*/

#ifndef AUTOGEN_INTERNAL_CONF_HFILE
#define AUTOGEN_INTERNAL_CONF_HFILE


/* ----------------------------------------------*/
/* Local build */
/* ----------------------------------------------*/
#ifdef AUTOGEN_ENVIRONMENT_LOCAL

/* Empty... */


/* ----------------------------------------------*/
/* MCU product build */
/* ----------------------------------------------*/
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU)

 #define AUTOGEN_DEVICE_ID PN_DEV_HOST

 #include "isa_core_conf.h"
 #if (ICF_ISA_PROTOCOL == ON)
  #include "isa_prot_conf.h"
 #endif /* ICF_ISA_PROTOCOL == ON */

 #include "os_conf.h"
 #include "mon_conf.h"

 /* autogen feature configuration */
 #if (MON_TRACE_ENABLE == ON)
  #define AUTOGEN_INCLUDE_MCU_TRACES
  #define AUTOGEN_MCU_TRACE_SUPPORT_OLD_CONCEPT
  #define AUTOGEN_INCLUDE_MCU_TRACES_CORE
  #if (ICF_ISA_PROTOCOL == ON) && (ICF_CHIPSET_API == OFF)
   #define AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL
  #endif
  #if (ICF_ISA_UI == ON)
   #define AUTOGEN_INCLUDE_MCU_TRACES_ISA_UI
  #endif
 #endif /* MON_TRACE_ENABLE == ON */

 #if (ICF_CRASH_DUMP == ON)
  #define AUTOGEN_INCLUDE_X_FILE
 #endif /* ICF_CRASH_DUMP == ON */

 #if (((ICF_INVARIANT_TRACE == ON) || (IPF_INVARIANT_TRACE == ON)) && ICF_ISA_PROTOCOL == ON)
  #define AUTOGEN_INCLUDE_INVARIANT_TRACES
 #endif /* ((ICF_INVARIANT_TRACE == ON) || (IPF_INVARIANT_TRACE == ON)) && ICF_ISA_PROTOCOL == ON */

 #if (OS_MONITOR == ON)
  #define AUTOGEN_INCLUDE_NOS_TRACES
 #endif /* OS_MONITOR == ON */

 #if (ICF_HSP == ON )
  #define AUTOGEN_INCLUDE_HSP_TRACES
 #endif /* ICF_HSP == ON */

 /* Currently no flags for this... */
 #define AUTOGEN_INCLUDE_HAL_TRACES
 #define AUTOGEN_INCLUDE_MASTER_TRACES

 #ifdef ICF_XTI_VERSION
  #if (ICF_XTI_VERSION == ICF_XTI_VERSION_3)
   #define AUTOGEN_XTI_VERSION AUTOGEN_XTI_V3
  #else
   #define AUTOGEN_XTI_VERSION AUTOGEN_XTI_V2
  #endif
 #endif

/* ----------------------------------------------*/
/* CDSP build */
/* ----------------------------------------------*/
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_DSP)

 #define AUTOGEN_DEVICE_ID PN_DEV_DSP_MAIN

 #define AUTOGEN_INCLUDE_INVARIANT_TRACES
 #define AUTOGEN_INCLUDE_CDSP_TRACES


/* ----------------------------------------------*/
/* ADSP build */
/* ----------------------------------------------*/
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_ADSP)

 #define AUTOGEN_DEVICE_ID PN_DEV_DSP_AUX

 #define AUTOGEN_INCLUDE_ADSP_TRACES


/* ----------------------------------------------*/
/* Device build (modular modem) */
/* ----------------------------------------------*/
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE)

 #define AUTOGEN_DEVICE_ID           PN_DEV_OWN
 #define AUTOGEN_XTI_VERSION         AUTOGEN_XTI_V3

 #define PMD_FILE_FORMAT 501

/* ----------------------------------------------*/
/* Symbian build */
/* ----------------------------------------------*/
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN)

 #define AUTOGEN_DEVICE_ID PN_DEV_SOS

 #define AUTOGEN_INCLUDE_SYMBIAN_TRACES

 #define AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES

 #define AUTOGEN_INCLUDE_OST

 #define PMD_FILE_FORMAT 501

#endif

/* ----------------------------------------------*/
/* General flags */
/* ----------------------------------------------*/
#ifndef AUTOGEN_MASTER_ASCII_PRINTF_TYPE
 #ifdef LITTLE_ENDIAN_TYPE
  #define AUTOGEN_MASTER_ASCII_PRINTF_TYPE AUTOGEN_STRING_TYPE_UNFORMATTED_LE
 #else
  #define AUTOGEN_MASTER_ASCII_PRINTF_TYPE AUTOGEN_STRING_TYPE_UNFORMATTED_BE
 #endif
#endif /* AUTOGEN_MASTER_ASCII_PRINTF_TYPE */


#endif /* AUTOGEN_INTERNAL_CONF_HFILE */

/*  End of file autogen_internal_conf.h  */
