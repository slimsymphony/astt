/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw_mon.h
                --------------------
                SW Include






Project:          autogen

%name:            autogen_coresw_mon.h %
%version:         co1tss#15 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Thu Dec  4 12:04:18 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file is the message definition file for the monitor server
*/

#ifndef ICF_MONITOR_SERV
 #ifdef PRODUCT_INCLUDES_CORESW_MONITOR_SERV
  #define ICF_MONITOR_SERV ON
 #else
  #define ICF_MONITOR_SERV OFF
 #endif /* PRODUCT_INCLUDES_CORESW_MONITOR_SERV */
#endif /* ICF_MONITOR_SERV */

#if (ICF_MONITOR_SERV == ON)
 #ifdef AUTOGEN_INCLUDE_MCU_TRACES
  #include "mon_trace_conf.h"
 #endif
 #if ((defined AUTOGEN_INCLUDE_INTERFACES) || (defined AUTOGEN_BINARY_RELEASE))
  #include "mon_isi_m.h"
 #endif /* AUTOGEN_INCLUDE_INTERFACES || AUTOGEN_BINARY_RELEASE */
 #include "trace_isi_m.h"
#endif /* ICF_MONITOR_SERV == ON */

/*  End of file autogen_coresw_mon.h */
