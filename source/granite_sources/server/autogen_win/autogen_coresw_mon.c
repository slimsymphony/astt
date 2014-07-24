/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw_mon.c
                --------------------
                SW Module






Project:          autogen

%name:            autogen_coresw_mon.c %
%version:         co1tss#20 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Fri Sep 14 15:51:40 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes the monitor server message definition file
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_init.h"


#ifdef AUTOGEN_INCLUDE_MCU_TRACES

 #include "mon_trace_group_ids.h"

 /* Ensure correct trace macros */
 #if (!defined AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS || defined AUTOGEN_TRACES_HAVE_FIXED_IDS)
  #define AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
  #undef  AUTOGEN_TRACES_HAVE_FIXED_IDS
  #include "isi_macros.h"
 #endif

 #ifdef AUTOGEN_INCLUDE_MCU_TRACES_CORE
  #include "mcu_trace_conf_core.h"
 #endif
 #ifdef AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL
  #include "mcu_trace_conf_protocol.h"
 #endif
 #ifdef AUTOGEN_INCLUDE_MCU_TRACES_ISA_UI
  #include "mcu_trace_conf_isa_ui.h"
 #endif

#elif (ICF_MONITOR_SERV == ON) /* Remove this elif when new trace concepts is in place */

 #include "mon_trace_group_ids.h"

#endif

#ifndef MON_TRACE_BITMAP_LEN
 #define MON_TRACE_BITMAP_LEN 64
#endif

#ifndef MON_BITMAP_ID
 #define MON_BITMAP_ID 0x00000000
#endif


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_coresw_mon
 
    Purpose: 
        Builds monitor server messages and traces (TI files)
*/
/* --------------------------------------------------------------------------------------------- */

void build_coresw_mon()
{
#include "autogen_coresw_mon.h"
}

/*  End of file autogen_coresw_mon.c  */
