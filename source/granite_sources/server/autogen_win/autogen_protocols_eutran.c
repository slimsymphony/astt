/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols_eutran.c
                ------------------------
                SW Module






Project:          autogen

%name:            autogen_protocols_eutran.c %
%version:         6 %
%instance:        co1tss_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 12:59:48 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all EUTRAN protocol message definition files
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
/*  Name: build_protocols_eutran
 
    Purpose: 
        Builds EUTRAN protocols part
*/
/* --------------------------------------------------------------------------------------------- */

void build_protocols_eutran()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #if (IPF_EUTRAN == ON)
  #include "autogen_protocols_eutran.h" 
 #endif /* IPF_EUTRAN == ON */
#elif (defined AUTOGEN_BINARY_RELEASE) 
  #include "autogen_protocols_eutran_bin.h" 
#endif
}

/*  End of file autogen_protocols_eutran.c  */
