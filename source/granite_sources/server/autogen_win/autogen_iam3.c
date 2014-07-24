/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_iam3.c
                -------------
                SW Module






Project:          autogen

%name:            autogen_iam3.c %
%version:         4 %
%instance:        co1tss_1 %
%derived_by:      nosterga %
%date_modified:   Wed Dec  3 13:08:58 2008 %

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
        Builds IAM part 3
*/
/* --------------------------------------------------------------------------------------------- */

void build_iam3()
{
#if (defined AUTOGEN_INCLUDE_INTERFACES)
 #include "autogen_iam3.h"
#elif (defined AUTOGEN_BINARY_RELEASE) 
 #include "autogen_iam3_bin.h"
#endif
}

/*  End of file autogen_iam3.c  */
