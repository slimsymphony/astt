/* Nokia/Devices/Devices R&D/Common Technologies/Adaptation SW/DSS/DS/Corleone









                mcu_trace_conf.h
                ----------------
                SW Include






Project:          autogen

%name:            mcu_trace_conf.h %
%version:         co1tss#12 %
%instance:        co1pctls_1 %
%derived_by:      nosterga %
%date_modified:   Fri Dec 19 16:48:00 2008 %

Copyright(c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen / Monitor server

    This file ultimately includes all MCU trace configuration flags
    The file must be included prior to parsing macros in .ti files, e.g. in mon.h and autogen
*/

#ifndef _MCU_TRACE_CONF_H_
#define _MCU_TRACE_CONF_H_

 #include "mcu_trace_conf_core.h"
 
 #if (ICF_ISA_UI == ON)
  #include "mcu_trace_conf_isa_ui.h"
 #endif /* ICF_ISA_UI == ON */
 
 #if (ICF_ISA_PROTOCOL == ON)
  #include "mcu_trace_conf_protocol.h"
 #endif /* ICF_ISA_PROTOCOL == ON */

 /* Geek UI traces - miscellaneous traces */
 #ifdef AUTOGEN_INCLUDE_MCU_TRACES_MISC
  #include "mcu_trace_conf_misc.h"
 #endif /* AUTOGEN_INCLUDE_MCU_TRACES_MISC */

#endif /* _MCU_TRACE_CONF_H_ */

/* End of file mcu_trace_conf.h */
