/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols.c
                -------------------
                SW Module






Project:          autogen

%name:            autogen_protocols.c %
%version:         co1tss#13 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 12:51:58 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all protocol message definition files
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
        Builds protocols part
*/
/* --------------------------------------------------------------------------------------------- */

void build_protocols()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #include "autogen_protocols.h"
#elif (defined AUTOGEN_BINARY_RELEASE) 
 #include "autogen_protocols_bin.h"
#endif
}

/*  End of file autogen_protocols.c  */
