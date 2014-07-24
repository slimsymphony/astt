/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_dsp.c
                -------------
                SW Module






Project:          autogen

%name:            autogen_dsp.c %
%version:         co1tss#11 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Wed Jan 21 14:31:13 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all dsp message definition files
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
/*  Name: build_dsp
 
    Purpose: 
        Builds dsp part
*/
/* --------------------------------------------------------------------------------------------- */

void build_dsp()
{
#if ((defined AUTOGEN_INCLUDE_INTERFACES) && !defined(AUTOGEN_INCLUDE_VENDOR_TRACES))
 #include "autogen_dsp.h"
#elif (defined AUTOGEN_BINARY_RELEASE) 
 #include "autogen_dsp_bin.h"
#endif
}

/*  End of file autogen_dsp.c  */
