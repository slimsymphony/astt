/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                master_trace.h
                ------------------
                SW Include






Project:          autogen

%name:            master_trace.h %
%version:         9 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Fri Jan 07 16:17:05 2011 %

Copyright (c) Nokia. All rights reserved
VERSION     : 8         DRAFT        28-Aug-2010  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : New MASTER_HWPC_DATA and reserved ID


VERSION     : 2         DRAFT        22-Nov-2007  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Enumeration replaced with #define to force 8-bit width
*/

/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen / CoreSW

    This file contains definitions of master trace types.
*/

#ifndef _MASTER_TRACE_H_
#define _MASTER_TRACE_H_

typedef unsigned char MASTER_TRACE_TYPE;      

/* Standard trace concepts */
/* Reserved for trace box - phone communication */
#define MASTER_TRACEBOX_MESSAGE          0x00
 
#define MASTER_MCU_TRACE                 0x01
#define MASTER_INVARIANT_TRACE           0x02
#define MASTER_HAL_TRACE                 0x03
#define MASTER_NOS_TRACE                 0x04
#define MASTER_ADSP5_TRACE               0x05
#define MASTER_CDSP5_TRACE               0x06
#define MASTER_SYMBIAN_TRACE             0x07
#define MASTER_OST                       0x08
#define MASTER_HSP_TRACE                 0x09
#define MASTER_SHA1_HASH_TRACE           0x0A

/* RESERVED                                 0x1B */

    /* Standarsd trace formats */
#define MASTER_ASCII_PRINTF              0x20
#define MASTER_ASSERT                    0x21
#define MASTER_CORE_DUMP                 0x22
#define MASTER_RAW_DATA                  0x23
#define MASTER_HWPC_DATA                 0x24

    /* Vendor traces */
#define MASTER_VENDOR_ASCII_PRINTF       0x70
#define MASTER_VENDOR_COMPONENT_TRACE    0x71
#define MASTER_VENDOR_DLL_TRACE          0x72
#define MASTER_VENDOR_BINARY_TRACE_1     0x73
#define MASTER_VENDOR_BINARY_TRACE_2     0x74
#define MASTER_VENDOR_BINARY_TRACE_3     0x75
#define MASTER_VENDOR_BINARY_TRACE_4     0x76
#define MASTER_VENDOR_BINARY_TRACE_5     0x77
#define MASTER_VENDOR_BINARY_TRACE_6     0x78
#define MASTER_VENDOR_BINARY_TRACE_7     0x79
#define MASTER_VENDOR_BINARY_TRACE_8     0x7A
#define MASTER_VENDOR_BINARY_TRACE_9     0x7B
#define MASTER_VENDOR_BINARY_TRACE_10    0x7C
#define MASTER_VENDOR_BINARY_TRACE_11    0x7D
#define MASTER_VENDOR_BINARY_TRACE_12    0x7E
#define MASTER_VENDOR_BINARY_TRACE_13    0x7F

    /* User traces */
#define MASTER_USER_TRACE_1              0x80

    /* PhoNet message */
#define MASTER_PN_MESSAGE                0xFF



#endif /* _MASTER_TRACE_H_ */
