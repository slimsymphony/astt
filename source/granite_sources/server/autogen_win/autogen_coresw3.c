/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw3.c
                -----------------
                SW Module






Project:          autogen

%name:            autogen_coresw3.c %
%version:         co1tss#12 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 12:48:11 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes third part of all CoreSW message definition files
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
/*  Name: build_coresw
 
    Purpose: 
        Builds coresw part
*/
/* --------------------------------------------------------------------------------------------- */

void build_coresw3()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #include "autogen_coresw3.h"
#elif (defined AUTOGEN_BINARY_RELEASE) 
 #include "autogen_coresw3_bin.h"
#endif
}

/*  End of file autogen_coresw3.c  */
