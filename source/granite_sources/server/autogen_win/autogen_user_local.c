/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_user_local.c
                --------------------
                SW Module






Project:          autogen

%name:            autogen_user_local.c %
%version:         co1tss#4 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Jun 14 12:52:30 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes user selected message definition files
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#define AUTOGEN_DONT_ERASE_DSP5_PMD_FILE_TYPE
#include "autogen_def.h"
#include "autogen_init.h"


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_user
 
    Purpose: 
        Builds user part (through autogen_local_server_conf.h)
*/
/* --------------------------------------------------------------------------------------------- */

void build_user()
{
  #include "autogen_local_server_conf.h"
}

/*  End of file autogen_user.c  */
