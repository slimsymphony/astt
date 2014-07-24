/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_mcu_trace_protocol.c
                ----------------------------
                SW Module






Project:          autogen

%name:            autogen_mcu_trace_protocol.c %
%version:         co1tss#13 %
%instance:        co1pctls_1 %
%derived_by:      eliasen %
%date_modified:   Fri Jan 07 16:25:01 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all protocol .ti files
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
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL

 #include "mon_trace_group_ids.h"

 /* Ensure correct trace macros */
 #if (!defined AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS || defined AUTOGEN_TRACES_HAVE_FIXED_IDS)
  #define AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
  #undef  AUTOGEN_TRACES_HAVE_FIXED_IDS
  #include "isi_macros.h"
 #endif

 #include "mcu_trace_conf_protocol.h"

#endif /* AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL */

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_mcu_trace_protocol
 
    Purpose: 
        Builds protocol MCU traces based on .ti files
*/
/* --------------------------------------------------------------------------------------------- */

void build_mcu_trace_protocol()
{
#if (SIMULATION_ENVIRONMENT == G_SIMULATION_ENVIRONMENT_NONE)
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL
 #include "mcu_trace_protocol.h"
#endif /* AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL */
#endif
#ifdef AUTOGEN_INCLUDE_VENDOR_TRACES
 #include "chipset_vendor_trace_mon.ti"
#endif
}

/*  End of file autogen_mcu_trace_protocol.c  */
