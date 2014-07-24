/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_user.c
                ----------------
                SW Module






Project:          autogen

%name:            autogen_user.c %
%version:         co1tss#10 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Tue Aug  7 13:38:27 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes user selected message definition files
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#define AUTOGEN_DONT_ERASE_DSP5_PMD_FILE_TYPE
#include "autogen_def.h"
#include "autogen_init.h"

#ifdef AUTOGEN_INCLUDE_MCU_TRACES_CORE
 #include "mcu_trace_conf_core.h"
#endif
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL
 #include "mcu_trace_conf_protocol.h"
#endif
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_ISA_UI
 #include "mcu_trace_conf_isa_ui.h"
#endif

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_user
 
    Purpose: 
        Builds user part (through autogen_server_conf.h)
*/
/* --------------------------------------------------------------------------------------------- */

void build_user()
{
#include "autogen_server_conf.h"
}

/*  End of file autogen_user.c  */
