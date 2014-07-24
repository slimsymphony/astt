/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_ver_history.h
                ---------------------
                SW Include






Project:          autogen

%name:            autogen_ver_history.h %
%version:         co1tss#3 %
%instance:        co1pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Dec 28 10:15:35 2006 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains prototype for version history functions
*/

#ifndef _AUTOGEN_VER_HISTORY_H_
#define _AUTOGEN_VER_HISTORY_H_

/* ============================================================================================= */
/* Function prototypes */
/* ============================================================================================= */

void version_history_add_entry(autogen_res* res, autogen_obj* changed_obj, unsigned int type);
void version_history_generate(autogen_res* res);
void version_history_report_warnings(autogen_obj* ver_obj);

#endif /* _AUTOGEN_VER_HISTORY_H_*/


/*  End of file autogen_ver_history.h  */
