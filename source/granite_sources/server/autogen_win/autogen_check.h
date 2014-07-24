/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_check.h
                ---------------
                SW Include






Project:          autogen

%name:            autogen_check.h %
%version:         co1tss#16 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Wed Jun 27 08:55:45 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    The file contains some functions used through the analysis of the data model
*/

#ifndef _AUTOGEN_CHECK_H_
#define _AUTOGEN_CHECK_H_

/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_object.h"


/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

#define CHECK_NAME_NO_FLAGS          0x0000
#define CHECK_NAME_EXIT_ON_FAIL      0x0001
#define CHECK_NAME_ALLOW_ASTERIX     0x0002
#define CHECK_NAME_ALLOW_EMPTY       0x0004


/* ============================================================================================= */
/* Function prototypes */
/* ============================================================================================= */

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
unsigned int check_seq_alignment(const char* current_file, autogen_seq* seq, autogen_ver* ver);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

void         check_seq_recursion(const char* current_file, autogen_seq* seq, autogen_res* res, autogen_ver* ver);
void         check_item_limits(const char* current_file, const autogen_item_value *limit_obj);
void         check_item_default_value(const char* current_file, autogen_item* item);
int          check_c_name(const char* current_file, int line,const char* argname, const char* name, unsigned int flags);
void         check_parname(const char* current_file, int line, char* parname);
void         check_string(const char* current_file, int line, const char* argname, const char* strname, unsigned int flags);

#endif /* _AUTOGEN_CHECK_H_ */


/*  End of autogen_check.h  */
