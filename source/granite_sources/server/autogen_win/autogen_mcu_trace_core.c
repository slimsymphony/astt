/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_mcu_trace_core.c
                ------------------------
                SW Module






Project:          autogen

%name:            autogen_mcu_trace_core.c %
%version:         co1tss#10 %
%instance:        co1pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Fri Aug 31 10:26:26 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all core .ti files
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_init.h"

/* Include trace configuration files */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 #include "mon_trace_conf.h"
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

/* Include trace group ID's */
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_CORE

 #include "mon_trace_group_ids.h"

 /* Ensure correct trace macros */
 #if (!defined AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS || defined AUTOGEN_TRACES_HAVE_FIXED_IDS)
  #define AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
  #undef  AUTOGEN_TRACES_HAVE_FIXED_IDS
  #include "isi_macros.h"
 #endif

 #include "mcu_trace_conf_core.h" 

#endif /* AUTOGEN_INCLUDE_MCU_TRACES_CORE */


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_mcu_trace_core
 
    Purpose: 
        Builds core MCU traces based on .ti files
*/
/* --------------------------------------------------------------------------------------------- */

void build_mcu_trace_core()
{
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_CORE
 #include "mcu_trace_core.h"
#endif /* AUTOGEN_INCLUDE_MCU_TRACES_CORE */
}

/*  End of file autogen_mcu_trace_core.c  */
