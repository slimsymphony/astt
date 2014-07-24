/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw_cl.c
                -------------------
                SW Module






Project:          autogen

%name:            autogen_coresw_cl.c %
%version:         co1tss#19 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 12:32:34 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all CL message definition files
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
/*  Name: build_coresw_pn
 
    Purpose: 
        Builds coresw cl part
*/
/* --------------------------------------------------------------------------------------------- */

void build_coresw_cl()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #include "autogen_coresw_cl.h"
#elif (defined AUTOGEN_BINARY_RELEASE) 
 #include "autogen_coresw_cl_bin.h"
#endif
}

/*  End of file autogen_coresw_cl.c  */
