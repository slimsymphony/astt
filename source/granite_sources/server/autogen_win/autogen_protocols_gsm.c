/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols_gsm.c
                -----------------------
                SW Module






Project:          autogen

%name:            autogen_protocols_gsm.c %
%version:         co1tss#10 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 13:01:38 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all GSM protocol message definition files
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_init.h"


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_protocols
 
    Purpose: 
        Builds GSM protocols part
*/
/* --------------------------------------------------------------------------------------------- */

void build_protocols_gsm()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #if (IPF_GSM_RAT == ON)
  #include "autogen_protocols_gsm.h"
 #endif
#elif (defined AUTOGEN_BINARY_RELEASE) 
 #include "autogen_protocols_gsm_bin.h"
#endif
}

/*  End of file autogen_protocols.c  */
