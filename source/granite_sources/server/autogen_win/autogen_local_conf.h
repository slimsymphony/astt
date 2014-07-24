/* Nokia/Devices/Devices R&D/Common Technologies/Adaptation SW/DSS/DS/Corleone


                        %full_filespec:  example_autogen_conf.h-34:incl:co1tss#1 %

                        %derived_by: nosterga %

                        %date_modified: Thu Dec  3 13:23:33 2009 %

                        %state: %


Copyright (c) Nokia. All rights reserved

<conf_file>
  Owner          : Stig Holmsten Eliasen
  SCF            : Adaptation SW/DSS/DS/Corleone
  Team           : Corleone
  SCF Contacts   : Stig Holmsten Eliasen
  Parent feature : -
</conf_file>

<override_links>
 <parse-problem/>
 override_links.pl cannot be used to replace individual configuration items
</override_links>

Change history:
VERSION     : 32       DRAFT        26-Aug-2009  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : PMD_FILE_FORMAT 501 set as default.
              LE support in MERGE fields requires this format.

Change history:
VERSION     : 30       DRAFT        19-Jun-2009  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : PMD_FILE_FORMAT 501 introduced. When specifying 501 in DEVICE builds
              LE is supported in SB_ID, non-ISI MSG_ID, and Trace ID.
              Decoding requires FastTrace 3.2

Change history:
VERSION     : 23       DRAFT        13-Nov-2008  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Update regarding endianess of simulation environments.


Change history:
VERSION     : 19       DRAFT        09-Sep-2008  Stig Holmsten Eliasen
REASON      : Error
REFERENCE   : -
DESCRIPTION : Changed flag for inclusion of miscellaneous (GEEK UI) MCU traces.
              Removed flag for HW_MASTER builds.


VERSION     : 17       DRAFT        20-Jun-2008  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Introduced flag for generation of Local mode outputs from sos_ftd_isi_m.h.
              This is caused by subblock templates for FTD data.

VERSION     : 16       DRAFT        19-Jun-2008  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Added flag for inclusion of miscellaneous (GEEK UI) MCU traces.

VERSION     : 14       DRAFT        20-May-2008  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Added flag for HW_MASTER builds

VERSION     : 12       DRAFT        08-May-2008  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Added flags AUTOGEN_PMD_LINE_NUMBERS, AUTOGEN_PROCESSOR_1,
              AUTOGEN_PROCESSOR_2, ..., AUTOGEN_PROCESSOR_9

VERSION     : 9        DRAFT        28-Sep-2007  Christian Jacob Hansen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Added flags AUTOGEN_DEVICE_ASCII_PRINTF_TYPE,
              AUTOGEN_DEVICE_XTI_MASTER_DEVICE and AUTOGEN_INCLUDE_VENDOR_TRACES

VERSION     : 4         DRAFT        12-Sep-2007  Christian Jacob Hansen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Removed support for flag AUTOGEN_SYMBIAN_TRACE_INCLUDE_COMPONENT_ID

VERSION     : 3         DRAFT        20-Aug-2007  Christian Jacob Hansen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Header changed, contents updated

VERSION     : 2         DRAFT        08-Aug-2007  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : Changed symbian flag

VERSION     : 1         DRAFT        16-Jun-2007  Christian Jacob Hansen
REASON      : -
REFERENCE   : -
DESCRIPTION : First version of file
*/

#ifndef AUTOGEN_CONF_HFILE
#define AUTOGEN_CONF_HFILE

/* In this file, autogen can be configured using various compile flags 

==============================================================================================
 Possible flags in different environments
==============================================================================================

                                           Local   Product     Possible values   Default value
----------------------------------------------------------------------------------------------
AUTOGEN_DEVICE_ID                                  x(device)   PN_DEV_<XXX>      Not defined
AUTOGEN_DEVICE_NAME                                x(device)   "PN_DEV_<XXX>"    Not defined
AUTOGEN_DEVICE_LOGICAL_NAME                        x(device)   "<XXX>"           Not defined
AUTOGEN_DEVICE_MONITOR_SERVER_RESOURCE_ID          x(device)   PN_XXX            Not defined
AUTOGEN_DEVICE_ASCII_PRINTF_TYPE                   x(device)   PRINTF_TYPE_XXX   Not defined
AUTOGEN_DEVICE_XTI_MASTER_DEVICE                   x(device)   PN_DEV_XXX        Not defined
AUTOGEN_PROCESSOR_1                                x(device)   ON or OFF         OFF
AUTOGEN_PROCESSOR_2                                x(device)   ON or OFF         OFF
AUTOGEN_PROCESSOR_3                                x(device)   ON or OFF         OFF
AUTOGEN_PROCESSOR_4                                x(device)   ON or OFF         OFF
AUTOGEN_PROCESSOR_5                                x(device)   ON or OFF         OFF
AUTOGEN_PROCESSOR_6                                x(device)   ON or OFF         OFF
AUTOGEN_PROCESSOR_7                                x(device)   ON or OFF         OFF
AUTOGEN_PROCESSOR_8                                x(device)   ON or OFF         OFF
AUTOGEN_PROCESSOR_9                                x(device)   ON or OFF         OFF
AUTOGEN_DEVICE_ENDIANESS                           x           AUTOGEN_DEVICE_ENDIANESS_BE Not defined
                                                               AUTOGEN_DEVICE_ENDIANESS_LE

AUTOGEN_INCLUDE_MCU_TRACES                         x           Defined or not    Depends on product
AUTOGEN_INCLUDE_MCU_TRACES_CORE                    x           Defined or not    Depends on product
AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL                x           Defined or not    Depends on product
AUTOGEN_INCLUDE_MCU_TRACES_ISA_UI                  x           Defined or not    Depends on product
AUTOGEN_INCLUDE_MCU_TRACES_MISC                    x           Defined or not    Depends on product
AUTOGEN_INCLUDE_NOS_TRACES                         x           Defined or not    Depends on product
AUTOGEN_INCLUDE_HAL_TRACES                         x           Defined or not    Depends on product
AUTOGEN_INCLUDE_INVARIANT_TRACES                   x           Defined or not    Depends on product
AUTOGEN_INCLUDE_SYMBIAN_TRACES                     x           Defined or not    Depends on product
AUTOGEN_INCLUDE_OST                                x           Defined or not    Depends on product
AUTOGEN_INCLUDE_X_FILE                             x           Defined or not    Depends on product
AUTOGEN_INCLUDE_VENDOR_TRACES                      x           Defined or not    Not defined
AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION           x           Defined or not    Not defined

PMD_FILE_FORMAT                            x       x           500 / 501 / 600   501
PMD_FILE_NAME                              x       x           "<name.pmd>"      product/local/...

AUTOGEN_PMD_LINE_NUMBERS                           x           Defined or not    Not defined
AUTOGEN_DISABLE_TOUGH_CHECKS               x                   Defined or not    Not defined
DO_VENDOR_OUTPUT                           x                   Defined or not    Not defined
AUTOGEN_BINARY_RELEASE                             x           Defined or not    Not defined
AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES      x                   Defined or not    Not defined
----------------------------------------------------------------------------------------------

==============================================================================================
 Description of flags
==============================================================================================

AUTOGEN_DEVICE_ID
- Defines value of device in Device product environment (PN_DEV_XXX)

AUTOGEN_DEVICE_LOGICAL_NAME
- Defines logical name of device in Device product environment ("XXX")

AUTOGEN_DEVICE_NAME
- Defines name of device in Device product environment ("PN_DEV_XXX")
- Note 1: Should be same as AUTOGEN_DEVICE_ID

AUTOGEN_DEVICE_MONITOR_SERVER_RESOURCE_ID
- Defines the resource ID of the monitor server on the device

AUTOGEN_DEVICE_ASCII_PRINTF_TYPE
- Defines the format of printf's for the device/processor
- Possible values are: 
  * PRINTF_TYPE_CL470_LE  - TI C1470 compiler. LE processor
  * PRINTF_TYPE_CL470_BE  - TI C1470 compiler. BE processor
  * PRINTF_TYPE_LEAD      - TI lead C compiler. BE mode
  * PRINTF_FORMATTED      - Formatting of string is done in processor

AUTOGEN_DEVICE_XTI_MASTER_DEVICE
- Defines that the current device does not have a XTI message handler, but is controlled by another device. 
  Setting this value will ease usage of FastTrace 3.0+ when configuring XTI's versus devices.

  Current device has following values (depending on build environment):
  - AUTOGEN_ENVIRONMENT_PRODUCT_MCU:     PN_DEV_HOST
  - AUTOGEN_ENVIRONMENT_PRODUCT_DSP:     PN_DEV_DSP_MAIN
  - AUTOGEN_ENVIRONMENT_PRODUCT_ADSP:    PN_DEV_DSP_AUX
  - AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN: PN_DEV_SOS
  - AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE:  AUTOGEN_DEVICE_ID (see above)

AUTOGEN_DEVICE_ENDIANESS
- Defines the native endianess of the target device wrt. all macros that have endianess defined as NATIVE.

  The following values are possible:
  - AUTOGEN_DEVICE_ENDIANESS_BE:         NATIVE is interpretated a big endianess
  - AUTOGEN_DEVICE_ENDIANESS_LE:         NATIVE is interpretated as little endianess

AUTOGEN_DISABLE_TOUGH_CHECKS
- Disables extensive checks on e.g. parameter names

DO_VENDOR_OUTPUT
- Requires the following lines to be added to message macro file before RES_BEGIN
#ifdef DO_VENDOR_OUTPUT
PROPERTY(PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT)
#endif
- When flag is defined then autogen will exclude sensitive information from ISI header and HTML doc.

AUTOGEN_BINARY_RELEASE
- When defined it causes autogen to include from binary release configuration files
- instead of its normal configuration files. It is the responsibility of the user to provide
- and setup these *_bin.h configuration files. The user must take care to ensure that the correct 
- set of servers are included when using these *_bin.h configuration files.
- 
- The following table lists the configuration files that autogen includes from when the flag is defined 
- and when it is not defined.
-   Flag NOT defined:             Flag defined:
-   --------------------------------------------------------------
-     autogen_coresw.h              autogen_coresw_bin.h
-     autogen_coresw2.h             autogen_coresw2_bin.h
-     autogen_coresw3.h             autogen_coresw3_bin.h
-     autogen_coresw4.h             autogen_coresw4_bin.h
-     autogen_coresw_cl.h           autogen_coresw_cl_bin.h
-     autogen_dsp.h                 autogen_dsp_bin.h
-     autogen_iam.h                 autogen_iam_bin.h
-     autogen_iam2.h                autogen_iam2_bin.h
-     autogen_iam3.h                autogen_iam3_bin.h
-     autogen_protocols.h           autogen_protocols_bin.h
-     autogen_protocols2.h          autogen_protocols2_bin.h
-     autogen_protocols3.h          autogen_protocols3_bin.h
-     autogen_protocols_eutran.h    autogen_protocols_eutran_bin.h
-     autogen_protocols_gsm.h       autogen_protocols_gsm_bin.h
-     autogen_protocols_wcdma.h     autogen_protocols_wcdma_bin.h

AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES
- Applicable to sos_ftd_isi_m.h for generating Local mode outputs only.

AUTOGEN_INCLUDE_HAL_TRACES
- HAL trace structure will be generated in PMD file
- Note 1: Actual traces are defined in hal_trc_m.h, which must be present

AUTOGEN_INCLUDE_MCU_TRACES
- MCU trace structure will be generated in PMD file
- Note 1: Must defined, if any of the flags AUTOGEN_INCLUDE_MCU_TRACES_XXX are defined
- Note 2: mon_trace_group_ids.h must exist, defining MCU trace group ID's

AUTOGEN_INCLUDE_MCU_TRACES_CORE
- Core MCU trace structure will be generated in PMD file
- Note 1: mcu_trace_core_conf.h must exist and defined TRACE_ICF_XXX flags
- Note 2: mcu_trace_core.h must exist and include .ti files based on TRACE_ICF_XXX flags

AUTOGEN_INCLUDE_MCU_TRACES_ISA_UI
- MTM MCU trace structure will be generated in PMD file
- Note 1: mcu_trace_isa_ui_conf.h must exist and defined TRACE_IUF_XXX flags
- Note 2: mcu_trace_isa_ui.h must exist and include .ti files based on TRACE_IUF_XXX flags

AUTOGEN_INCLUDE_MCU_TRACES_MISC
- Geek (misc) MCU trace structure will be generated in PMD file
- Note 1: mcu_trace_conf_misc.h must exist and defined TRACE_GEEK_XXX flags
- Note 2: mcu_trace_misc.h must exist and include .ti files based on TRACE_???_XXX flags

AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL
- Protocol MCU trace structure will be generated in PMD file
- Note 1: mcu_trace_protocol_conf.h must exist and defined TRACE_IPF_XXX flags
- Note 2: mcu_trace_protocol.h must exist and include .ti files based on TRACE_IPF_XXX flags

AUTOGEN_INCLUDE_NOS_TRACES
- NOS trace structure will be generated in PMD file
- Note 1: Actual traces are defined in os_trc_m.h
- Note 2: To generate task, block, timer and resource info, os.h, os_elem.h and os_conf.h are included

AUTOGEN_INCLUDE_OST
- Open System Traces will be enabled and trace structure will be generated in PMD file
- Requires PMD 5.00 format (see PMD_FILE_FORMAT)
  Always enabled for Symbian builds using PMD 5.00 format
- Additional flags associated with AUTOGEN_INCLUDE_OST
  - AUTOGEN_INCLUDE_OST_CONTROL_PROTOCOL  Include support for the OST control protocol
  - AUTOGEN_INCLUDE_OST_PHONET_PROTOCOL   Include support for PhoNet over OST protocol
  - AUTOGEN_INCLUDE_OST_XTIV3             Include support for XTIv3 over OST protocol

AUTOGEN_INCLUDE_SYMBIAN_TRACES
- Symbian trace structure will be generated in PMD file
- Requires PMD 5.00 format (see PMD_FILE_FORMAT)

AUTOGEN_INCLUDE_VENDOR_TRACES
- Vendor trace structure will be generated in PMD file
- Requires PMD 5.00 format (see PMD_FILE_FORMAT)

AUTOGEN_INCLUDE_VENDOR_DLL_TRACE
- Support vendor DLL traces

AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION
- Make it possible for autogen to read Chipset Supplier Descriptions. (Vendor traces)
  AUTOGEN_INCLUDE_VENDOR_TRACES and AUTOGEN_INCLUDE_VENDOR_DLL_TRACE must also be set.

  - char *chipset_supplier_description_xml_files[] : Paths and filenames of the Chipset Supplier Description xml files
                                                     Relative to current working directory when executing autogen
                                                     Note that list of strings MUST be terminated by NULL.
                                                     This must be defined in a file named "autogen_vendor_includes.h".
                                                     This include file will be included by autogen and all chipset 
                                                     supplier descriptions specified here will be loaded.
                                                     Example:
                                                        char *chipset_supplier_description_xml_files[] = {
                                                            "chipset_supplier_description.xml",
                                                            NULL // Stop condition. Do not remove..
                                                        };

  - AUTOGEN_VENDOR_DLL_TRACE_DEC_RES_TRC_MASTER    : Name of the resource trace master containing the Vendor DLL master trace

  - AUTOGEN_VENDOR_DLL_TRACE_DLL_FILE_NAME         : If defined it defines the default DLL to be called if message does not
  - AUTOGEN_VENDOR_DLL_TRACE_DLL_FUNCTION_NAME     : match any of the definitions in the chipset supplier description XML file.
                                                     If not defined then the message is written as HEX data.

  - AUTOGEN_VENDOR_DLL_TRACE_NAME                  : Text to be presented when decoding the trace. Part of TRACE_BEGIN macro.

AUTOGEN_VENDOR_IDENTIFIER
- Used by various vendor traces to specify the trace identifier.
  The trace identifier is a 4 character name, which is displayed when a trace is decoded with PMD in compact format. 

AUTOGEN_INCLUDE_X_FILE
- Adds X-file structure to PMD file (required in order to decode X-file with PMD)

AUTOGEN_PMD_LINE_NUMBERS
- When defined, line numbers will be included in the PMD file. Line numbers are extracted
  from the .out file

AUTOGEN_PROCESSOR_<n> OFF/ON
- These flags indicate to autogen for which processor a PMD file is to be generated. 
  Processor specific message macro files are included from processor<n>_files.h, which are
  included from autogen_device_includes.h.
  The processor<n>_files.h are NOT autogen files.
  For all practical purposes only one flag should be ON for each PMD generation.

PMD_FILE_FORMAT
- Defines actual PMD file format.

PMD_FILE_NAME
- Defines PMD file name. ".pmd" will be added by autogen

==============================================================================================
 Example of configurations 
==============================================================================================
*/

/* ----------------------------------------------*/
/* Local build */
/* ----------------------------------------------*/

/* Empty... */


/* ----------------------------------------------*/
/* MCU product build */
/* ----------------------------------------------*/

/* Standard configuration for chipset vendor builds */
#if (ICF_CHIPSET_API == ON)
 
#define PMD_FILE_FORMAT 501
#define AUTOGEN_INCLUDE_MCU_TRACES

#define AUTOGEN_INCLUDE_VENDOR_TRACES
#define AUTOGEN_INCLUDE_VENDOR_COMPONENT_TRACES
#define AUTOGEN_INCLUDE_VENDOR_DLL_TRACE
#define AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION

#define AUTOGEN_VENDOR_IDENTIFIER "vend"
#define AUTOGEN_VENDOR_DLL_TRACE_DEC_RES_TRC_MASTER "XTI_MASTER_MCU"

#define AUTOGEN_DEVICE_XTI_MASTER_DEVICE PN_DEV_HOST

#endif /* ICF_CHIPSET_API */

/* Simulation environment */
#if (SIMULATION_ENVIRONMENT != G_SIMULATION_ENVIRONMENT_NONE)
 #define AUTOGEN_DEVICE_ENDIANESS AUTOGEN_DEVICE_ENDIANESS_LE
#endif


/* ----------------------------------------------*/
/* CDSP build */
/* ----------------------------------------------*/

/* Empty */


/* ----------------------------------------------*/
/* Device build (modular modem) */
/* ----------------------------------------------*/

#define AUTOGEN_PROCESSOR_1 OFF
/*
OFF: void
ON : forces inclusion of processor1_files.h
*/

#define AUTOGEN_PROCESSOR_2 OFF
/*
OFF: void
ON : forces inclusion of processor2_files.h
*/

#define AUTOGEN_PROCESSOR_3 OFF
/*
OFF: void
ON : forces inclusion of processor3_files.h
*/

#define AUTOGEN_PROCESSOR_4 OFF
/*
OFF: void
ON : forces inclusion of processor4_files.h
*/

#define AUTOGEN_PROCESSOR_5 OFF
/*
OFF: void
ON : forces inclusion of processor5_files.h
*/

#define AUTOGEN_PROCESSOR_6 OFF
/*
OFF: void
ON : forces inclusion of processor6_files.h
*/

#define AUTOGEN_PROCESSOR_7 OFF
/*
OFF: void
ON : forces inclusion of processor7_files.h
*/

#define AUTOGEN_PROCESSOR_8 OFF
/*
OFF: void
ON : forces inclusion of processor8_files.h
*/

#define AUTOGEN_PROCESSOR_9 OFF
/*
OFF: void
ON : forces inclusion of processor9_files.h
*/

/* ----------------------------------------------*/
/* Symbian build */
/* ----------------------------------------------*/

/*  End of file autogen_conf.h  */
#endif

