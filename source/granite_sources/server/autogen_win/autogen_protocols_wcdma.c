/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols_wcdma.c
                ------------------------
                SW Module






Project:          autogen

%name:            autogen_protocols_wcdma.c %
%version:         co1tss#10 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 13:03:46 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all WCDMA protocol message definition files
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
        Builds WCDMA protocols part
*/
/* --------------------------------------------------------------------------------------------- */

void build_protocols_wcdma()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #if (IPF_WCDMA_RAT == ON)
  #include "autogen_protocols_wcdma.h"
 #endif
#elif (defined AUTOGEN_BINARY_RELEASE) 
  #include "autogen_protocols_wcdma_bin.h"
#endif
}

/*  End of file autogen_protocols_wcdma.c  */
