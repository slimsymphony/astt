/*
NOKIA
R&D Copenhagen
ASW/DSS/DS/Corleone









                autogen_device_includes.c
                ------------------------
                SW Module






Project:          autogen

%name:            autogen_device_includes.c %
%version:         1 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Thu May  8 12:33:20 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file includes device specific message definition files
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
/*  Name: autogen_device_includes
 
    Purpose: 
        Builds device part
*/
/* --------------------------------------------------------------------------------------------- */

void build_device()
{
 #include "autogen_device_includes.h" 
}

/*  End of file autogen_device_includes.c  */
