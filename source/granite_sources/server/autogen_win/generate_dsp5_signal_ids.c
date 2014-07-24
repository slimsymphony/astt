/*
NOKIA
R&D Copenhagen
TSS









                Module definition
                -----------------

                SW Module






Status:           DRAFT

Continuus DB:     co_pctls

Project:          autogen

%name:            generate_dsp5_signal_ids.c %

%version:         co1tss#11 %

%instance:        co_pctls_1 %

%derived_by:      eliasen %

%date_modified:   Wed May 19 10:02:25 2010 %

Copyright (c) 2003-2010. Nokia Corporation. All rights reserved


Change history:

VERSION     : 11         DRAFT        19-May-2010   Stig Holmsten Eliasen
REASON      : Incorrect IDs for RF_HAL 
REFERENCE   : JC10022256995
DESCRIPTION : Sequence of includes updated 

VERSION     : 9          DRAFT        20-Feb-2005   Stig Holmsten Eliasen
REASON      : Extended use of PCFG_MODE 
REFERENCE   : -
DESCRIPTION : PCFG_MODE dependent inclusion of g_signal_file_list.h, 
              cdma_signal_file_list.h, and w_signal_file_list.h

VERSION     : sd1dsp#8   DRAFT        01-Feb-2005   Sachin Ganpule
REASON      : Update for CDMA signal set inclusion
REFERENCE   : -
DESCRIPTION : Add code so that cdma signals are included in PMD file

VERSION     : fa1prot#7  DRAFT        26-Aug-2004  Haleema Hameed
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Merge of fa1prot#6 and fa1prot#5.1.1.

VERSION     : fa1prot#6  DRAFT        25-Aug-2004  Haleema Hameed
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Undo changes in fa1prot#5.

VERSION     : fa1prot#5.1.1  DRAFT     26-Aug-2004  Robert White
REASON      : Bug Fix
REFERENCE   : -
DESCRIPTION : Check for GSM mode using PCFG_MODE flag and not SYSTEM.

VERSION     : fa1prot#5  DRAFT        18-Aug-2004  Robert White
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Don't include WCDMA signals on GSM only build.

VERSION     : 4          DRAFT        25-May-2004  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Remove shared signals

VERSION     : 2          DRAFT        03-Dec-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Support trace sources

VERSION     : 1          DRAFT        08-Apr-2003  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  This file is part of the source code for the sig2macro tool

    The file contains the code for generating the list of signal ID's for DSP 5.0 signals
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include <stdio.h>
#include <string.h>

#include "sig2macro.h"


#ifdef SIG2MACRO_DSP5

/* Defined to get correct definitions from type_def.h */
#define HPUX 1

#include "type_def.h"
#include "ose.h"
#include "signal_id.h"

/* request only signal lists from .sig files */
#define SIGNAL_NUMBERING                                                   

#define SIG(_name, _var) \
  if (!error) error = add_signal_id(flog, list, __FILE__, __LINE__, #_name, id++, source);

#define SIG_W_TYPE(_name, _type, _var) \
  if (!error) error = add_signal_id(flog, list, __FILE__, __LINE__, #_name, id++, source);
  
/* define the SDL generation macros to empty */
#define SDL_TO_ENV()
#define ENV_TO_SDL()
                                                    
int generate_signal_ids(FILE* flog, sig** list)
{
    int error = FALSE;
    unsigned int id = 0;
    const char* source = "PMD_TRACE_SOURCE_UNKNOWN";
    
    /*--- always include file c_signal_file_list.h ---*/

    fprintf(flog, "\nGenerating signal ID's (Core)\n");
    printf("\nGenerating signal ID's (Core)\n");

    id     = C_FIRST_SIGNAL_ID + 1;
    source = "PMD_TRACE_SOURCE_DSP5_CDSP_CORE_SIGNALS";

#undef C_SIGNAL_FILE_LIST_H
#include "c_signal_file_list.h"
    
    /*--- conditional inclusion of files rf_hal_signal_file_list.h ---*/

#ifdef COMMON_RF_HAL_ENABLED
 #if (COMMON_RF_HAL_ENABLED == TRUE)
#undef RF_HAL_SIGNAL_FILE_LIST_H
#include "rf_hal_signal_file_list.h"

    fprintf(flog, "\nGenerating signal ID's (RF HAL)\n");
    printf("\nGenerating signal ID's (RF HAL)\n");

    id     = RF_HAL_FIRST_SIGNAL_ID + 1;
    source = "PMD_TRACE_SOURCE_DSP5_CDSP_RF_HAL_SIGNALS";

 #endif
#endif
    
    /*--- always include file a_signal_file_list.h ---*/

    fprintf(flog, "\nGenerating signal ID's (Application)\n");
    printf("\nGenerating signal ID's (Application)\n");

    id     = A_FIRST_SIGNAL_ID + 1;
    source = "PMD_TRACE_SOURCE_DSP5_CDSP_APPLICATION_SIGNALS";

#undef A_SIGNAL_FILE_LIST_H
#include "a_signal_file_list.h"

    /*--- conditional inclusion of files g_signal_file_list.h, 
       cdma_signal_file_list.h, and w_signal_file_list.h  ---*/
    /* PCFG_MODE must be defined */

#if ! defined PCFG_MODE
 #error PCFG_MODE not defined.
#endif
    
    /*--- conditional inclusion of file cdma_signal_file_list.h ---*/
#if PCFG_MODE == PCFG_MODE_CDMA || PCFG_MODE == PCFG_MODE_GSM_CDMA || PCFG_MODE == PCFG_MODE_GSM_WCDMA_CDMA

    fprintf(flog, "\nGenerating signal ID's (CDMA)\n");
    printf("\nGenerating signal ID's (CDMA)\n");

    id     = CDMA_FIRST_SIGNAL_ID + 1;
    source = "PMD_TRACE_SOURCE_DSP5_CDSP_CDMA_SIGNALS";

 #undef CDMA_SIGNAL_FILE_LIST_H
 #include "cdma_signal_file_list.h"
#endif /* PCFG_MODE == PCFG_MODE_CDMA || ... */

    /*--- conditional inclusion of file g_signal_file_list.h ---*/
#if PCFG_MODE == PCFG_MODE_GSM || PCFG_MODE == PCFG_MODE_GSM_WCDMA || PCFG_MODE == PCFG_MODE_GSM_CDMA || PCFG_MODE == PCFG_MODE_GSM_WCDMA_CDMA

    fprintf(flog, "\nGenerating signal ID's (GSM)\n");
    printf("\nGenerating signal ID's (GSM)\n");

    id     = G_FIRST_SIGNAL_ID + 1;
    source = "PMD_TRACE_SOURCE_DSP5_CDSP_GSM_SIGNALS";

 #undef G_SIGNAL_FILE_LIST_H
 #include "g_signal_file_list.h"
#endif /* PCFG_MODE == PCFG_MODE_GSM || ... */ 

    /*--- conditional inclusion of file w_signal_file_list.h ---*/
#if PCFG_MODE == PCFG_MODE_WCDMA || PCFG_MODE == PCFG_MODE_GSM_WCDMA  || PCFG_MODE == PCFG_MODE_GSM_WCDMA_CDMA
    fprintf(flog, "\nGenerating signal ID's (WCDMA)\n");
    printf("\nGenerating signal ID's (WCDMA)\n");

    id     = W_FIRST_SIGNAL_ID + 1;
    source = "PMD_TRACE_SOURCE_DSP5_CDSP_WCDMA_SIGNALS";

 #undef W_SIGNAL_FILE_LIST_H
 #include "w_signal_file_list.h"
#endif /* PCFG_MODE == PCFG_MODE_WCDMA || ... */

    return error;
}

/* undefine special macros */
#undef SDL_TO_ENV
#undef ENV_TO_SDL
#undef SIG
#undef SIG_W_TYPE
#undef SIGNAL_NUMBERING


#endif /* SIG2MACRO_DSP5 */
