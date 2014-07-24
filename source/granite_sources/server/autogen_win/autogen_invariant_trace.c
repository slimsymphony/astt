/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_invariant_trace.c
                -------------------------
                SW Module






Project:          autogen

%name:            autogen_invariant_trace.c %
%version:         9 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Tue Mar 22 12:20:21 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all invariant traces
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_init.h"

/* Ensure correct trace macros */
#if (!defined AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS || !defined AUTOGEN_TRACES_HAVE_FIXED_IDS)
 #define AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
 #define AUTOGEN_TRACES_HAVE_FIXED_IDS
 #include "isi_macros.h"
#endif


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_invariant_trace
 
    Purpose: 
        Builds invariant traces
*/
/* --------------------------------------------------------------------------------------------- */

void build_invariant_trace()
{
#ifdef AUTOGEN_INCLUDE_INVARIANT_TRACES
 #define INVARIANT_TRACE_DEFINITIONS_AS_MACROS
  #if (ICF_CHIPSET_API == OFF)
   #include "inv_trace_prot_config.h"
  #else
   #include "inv_trace_asw_config.h"
  #endif
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */
}

/*  End of file autogen_invariant_trace.c  */
