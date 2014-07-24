/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols3.c
                -------------------
                SW Module






Project:          autogen

%name:            autogen_protocols3.c %
%version:         4 %
%instance:        co1tss_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 12:56:01 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes part three of protocol message definition files
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
        Builds protocols part three
*/
/* --------------------------------------------------------------------------------------------- */

void build_protocols3()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #include "autogen_protocols3.h"
#elif (defined AUTOGEN_BINARY_RELEASE) 
 #include "autogen_protocols3_bin.h"
#endif
}

/*  End of file autogen_protocols3.c  */
