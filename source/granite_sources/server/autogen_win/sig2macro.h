/*
NOKIA MOBILE PHONES
R&D Copenhagen
TSS









                Module definition
                -----------------

                SW Include






Status:           DRAFT

Continuus DB:     co_pctls

Project:          autogen

%name:            sig2macro.h %

%version:         2 %

%instance:        co_pctls_1 %

%derived_by:      cjhansen %

%date_modified:   Wed Dec  3 13:09:11 2003 %

Copyright (c) 2002-2003. Nokia Corporation. All rights reserved


Change history:

VERSION     : 2          DRAFT        03-Dec-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Add trace source as argument

VERSION     : 1          DRAFT        09-Jan-2003  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  This file is part of the source code for the sig2macro tool
*/


/* ============================================================================================= */
/* Definitions */
/* ============================================================================================= */

#define TRUE  1
#define FALSE 0

typedef struct t_signal_file
{
    struct t_signal_file* next;
    char* filename;
    char* filename_m;
    char* filepath;
    char* filepath_m;
    int should_exclude;
} sig_file;

typedef struct t_signal
{
    struct t_signal* next;
    sig_file* fileinfo;
    int fileline;
    char* name;
    char* source;
    unsigned int id;
    int is_generated;
} sig;


int add_signal_id(FILE* flog, sig** list, 
                  const char* file, int line, 
                  const char* name, unsigned int id, const char* source);
int generate_signal_ids(FILE* flog, sig** list);
