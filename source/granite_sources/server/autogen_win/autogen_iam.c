/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_iam.c
                -------------
                SW Module






Project:          autogen

%name:            autogen_iam.c %
%version:         co1tss#14 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 13:06:55 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes all IAM message definition files
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
/*  Name: build_iam
 
    Purpose: 
        Builds IAM part
*/
/* --------------------------------------------------------------------------------------------- */

void build_iam()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #include "autogen_iam.h"
#elif (defined AUTOGEN_BINARY_RELEASE) 
 #include "autogen_iam_bin.h"
#endif
}

/*  End of file autogen_iam.c  */
