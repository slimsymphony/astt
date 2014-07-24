/* Nokia/Devices/Devices R&D/Common Technologies/Adaptation SW/DSS/DS/Corleone









                autogen_mcu_trace_misc.c
                ------------------------
                SW Module






Project:          autogen

%name:            autogen_mcu_trace_misc.c %
%version:         1 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Sat Jun 14 14:03:07 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all miscellaneous .ti files
    i.e. .ti files that does not belong to Core, Protocol, or ISA UI
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
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_MISC

 #include "mon_trace_group_ids.h"

 /* Ensure correct trace macros */
 #if (!defined AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS || defined AUTOGEN_TRACES_HAVE_FIXED_IDS)
  #define AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
  #undef  AUTOGEN_TRACES_HAVE_FIXED_IDS
  #include "isi_macros.h"
 #endif

 #include "mcu_trace_conf_misc.h" 

#endif /* AUTOGEN_INCLUDE_MCU_TRACES_MISC */


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_mcu_trace_misc
 
    Purpose: 
        Builds miscellaneous MCU traces based on .ti files
*/
/* --------------------------------------------------------------------------------------------- */

void build_mcu_trace_misc()
{
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_MISC
 #include "mcu_trace_misc.h"
#endif /* AUTOGEN_INCLUDE_MCU_TRACES_MISC */
}

/*  End of file autogen_mcu_trace_misc.c  */
