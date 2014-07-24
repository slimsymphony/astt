/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                isi_macros.h
                ------------
                SW Include






Project:          autogen

%name:            isi_macros.h %
%version:         co1tss#201 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 13:02:06 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    This file contains all message macro definitions. Normally, a macro expands to a function
    call to a function, which analyzes the macro arguments and adds the information to the 
    data model
*/


#ifndef ISI_MACROS_H
#define ISI_MACROS_H

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

/* ============================================================================================= */
/* Message macro argument constants */
/* ============================================================================================= */

#define AUTOGEN_NO_RESOURCE_ID                  0xFFFFFFFFU
#define AUTOGEN_NO_MESSAGE_ID                   0x00


#define AUTOGEN_TRACE_GROUP_ID_UNDEFINED        0xFFFFFFFFU
#define AUTOGEN_TRACE_ID_UNDEFINED              0xFFFFFFFFU


/* algorithm types */
/*
///<enum name="E_ALGORITHM_TYPE">
///<summary>
///This enumeration defines various algorithms to be used with transformed 
///references (see <see cref_macro="REFERENCE_TRANSFORM"/>).
///</summary>
///[enum]
*/
#define ALG_ADD                                 1 /* <summary>New value = old value + n.</summary> */
#define ALG_SUB                                 2 /* <summary>New value = old value - n.</summary> */
#define ALG_MUL                                 3 /* <summary>New value = old value * n.</summary> */
#define ALG_DIV                                 4 /* <summary>New value = old value / n.</summary> */
#define ALG_DIV_ROUND_UP                        5 /* <summary>New value = int((old value + n – 1) / n).</summary> */
#define ALG_N_SUB                               6 /* <summary>New value = n - old value.</summary> */
/*
///</enum>
*/
#define ALG_MIN                                 ALG_ADD
#define ALG_MAX                                 ALG_N_SUB


/* block types */
/*
///<enum name="E_BLOCK_TYPE">
///<summary>
///This enumeration defines block types for the block macro <see cref_macro="BLOCK_REF"/>.
///</summary>
///[enum]
*/
#define BLOCK_RAW_DATA                          PMD_BLOCK_ALGORITHM_RAW_DATA   /* <summary>Block contains just raw data</summary> */
#define BLOCK_PN_MSG                            PMD_BLOCK_ALGORITHM_IDENTITY   /* <summary>Block contains an entire PhoNet message</summary> */
#define BLOCK_EXT_DECODER                       PMD_BLOCK_ALGORITHM_EXTERNAL   /* <summary>Block contains data to be decoded by external decode DLL</summary> */
#define BLOCK_X_FILE                            PMD_BLOCK_ALGORITHM_X_FILE     /* <summary>Block contains a Mulder dump (X-file)</summary> */
#define BLOCK_PROTOCOL                          PMD_BLOCK_ALGORITHM_ENTRYPOINT /* <summary>Block contains data do be decoded by specified entry point</summary> */
#define BLOCK_PMD_ANCHOR                        (PMD_BLOCK_ALGORITHM_LAST + 1) /* <summary>Block contains data, which is defined in different place in PMD file</summary> */
/*
///</enum>
*/

/* block flags */
/*
///<enum name="E_BLOCK_DLL_FLAGS">
///<summary>
///This enumeration defines block flags for the block macro <see cref_macro="BLOCK_REF"/>. 
///</summary>
///[enum]
*/
#define BLOCK_EXT_DECODER_SEND_WHOLE_EMB_MSG    PMD_BLOCK_EXT_DECODER_SEND_WHOLE_EMBEDDED_MESSAGE /* <summary>SDK should forward entire PhoNet message to DLL, not just the block data.</summary>*/
#define BLOCK_EXT_DECODER_SKIP_ID               PMD_BLOCK_EXT_DECODER_SKIP_IDENTIFIER             /* <summary>DLL identifier is not printed when decoded.</summary>*/
#define BLOCK_EXT_DECODER_SKIP_TRACE            PMD_BLOCK_EXT_DECODER_SKIP_TRACE_NAME             /* <summary>Trace ID is not printed when decoded.</summary>*/
#define BLOCK_EXT_DECODER_SEND_FROM_TRACE_START PMD_BLOCK_EXT_DECODER_SEND_FROM_TRACE_START       /* <summary>SDK should forward data from beginning of the trace to DLL, not just the block data.</summary>*/


/*
///</enum>
*/
/*
///<enum name="E_BLOCK_MSG_FLAGS">
///<summary>
///This enumeration defines block flags for the block macro <see cref_macro="BLOCK_REF"/>. 
///</summary>
///[enum]
*/
#define BLOCK_PN_MSG_SKIP_TRACE                 PMD_BLOCK_PN_MSG_SKIP_TRACE_NAME                  /* <summary>Trace wrapper is not printed in PMD compact decoding.</summary>*/
/*
///</enum>
*/


/* filler types */
/*
///<enum name="E_FILLER_TYPE">
///<summary>
///This enumeration defines the different supported filler types for the <see cref_macro="FILLER"/> macro.
///</summary>
///[enum]
*/
#define FILLER_FIXED                            1 /* <summary>The filler defines a fixed number of bytes. Typically this is used when a byte or word is reserved for future use.</summary> */
#define FILLER_VARIABLE                         2 /* <summary>The filler defines a variable number of bytes. The number of filler bytes in this case defines the resulting alignment after the filling. So a value of 4 means that after filling, a 32-bit aligned address is assured. Typical use of this is in the end of sub blocks containing variable length data, as sub blocks should always be divisible by 4 bytes in length.</summary> */
/*
///</enum>
*/

/* link types */
/*
///<enum name="E_COMMENT_LINK_TYPE">
///<summary>
///This enumeration defines possible link types for the macro <see cref_macro="COMMENT_LINK"/>. 
///The link type will tell autogen in which object group, the link should be resolved.
///</summary>
///[enum]
*/
#define LINK_MESSAGE                            1 /* <summary>The link is to a message, defined with the <see cref_macro="MSG_BEGIN"/> or <see cref_macro="SUB_MSG_BEGIN"/> macro.</summary> */
#define LINK_SUBBLOCK                           2 /* <summary>The link is to a sub block, defined with the <see cref_macro="SB_BEGIN"/> macro.</summary> */
#define LINK_SEQUENCE                           3 /* <summary>The link is to a sequence, defined with the <see cref_macro="SEQ_BEGIN"/> macro. Note that the sequence must be of type <b>CREATE_STRUCT</b>.</summary> */
#define LINK_TABLE                              4 /* <summary>The link is to a table (either constant, bit, FTD or PPC).</summary> */
#define LINK_NOTE                               5 /* <summary>The link is to a note, defined with the <see cref_macro="NOTE"/> macro.</summary> */
#define LINK_CONSTANT                           6 /* <summary>The link is to a constant, defined with the <see cref_macro="CONSTANT"/> or <see cref_macro="CONSTANT_VER"/> macro.</summary> */
/*
///</enum>
*/

/* list types */
/*
///<enum name="E_SBLIST_TYPE">
///<summary>
///This enumeration defines possible sub block list types for the 
///macros <see cref_macro="SB_LST_REF_BEGIN"/> and <see cref_macro="SB_LST_BEGIN"/>.
///</summary>
///[enum]
*/
#define LIST_OF_SUBBLOCKS                       1 /* <summary>List of whole sub blocks</summary> */
#define LIST_OF_SUBBLOCK_IDS                    2 /* <summary>List of sub block ID's only</summary> */
/*
///</enum>
*/

/* message types */
/*
///<enum name="E_MSG_TYPE">
///<summary>This enumeration defines the type of a message.</summary>
///[enum]
*/
#define MESSAGE_NONE                            0  /* <summary>No message. Must be used when defining resources without messages (one dummy message defines the resource)</summary> */
#define MESSAGE_UNKNOWN                         0  /* <not_to_be_documented/> */
#define MESSAGE_REQ                             1  /* <summary>Request message</summary> */
#define MESSAGE_RESP                            2  /* <summary>Response message</summary> */
#define MESSAGE_IND                             3  /* <summary>Indication message</summary> */
#define MESSAGE_NTF                             4  /* <summary>Notification message</summary> */
#define MESSAGE_BASE                            5  /* <to_be_documented_later/> */
#define MESSAGE_TRACE                           6  /* <to_be_documented_later/> */
#define WCDMA_CDSP_TRACE                        8  /* <to_be_documented_later/> */
#define ADSP_TRACE                              9  /* <to_be_documented_later/> */
#define STI_TRACE                               10 /* <to_be_documented_later/> */
#define CDMA_DSP_TRACE                          12 /* <to_be_documented_later/> */
/*
///</enum>
*/


/* order types */
/*
///<enum name="E_ORDER_TYPE">
///<summary>
///This enumeration defines possible data ordering flags for various items. 
///<br/>
///Except for BCD strings, the data ordering should be either <b>NATIVE</b>, <b>BE</b> or <b>LE</b>.
///<br/>
///For 8-bit items, this doen't make much sence, and autogen expects in this case that <b>BE</b> is specified as data order. 
///<br/><br/>
///In the following, M=Most, L=Least, S=Significant, B=Byte and W=Word.
///<br/><br/>
///16-bit values are ordered the following way:
///<br/>
///<b>BE</b>: MSB | LSB. The value 0x0113 is packed the following way: 0x0113
///<br/>
///<b>LE</b>: LSB | MSB. The value 0x0113 is packed the following way: 0x1301
///<br/><br/>
///32-bit values are ordered the following way:
///<br/>
///<b>BE</b>: MSW (MSB | LSB) | LSW (MSB | LSB). The value 0x0113 is packed the following way: 0x00000113
///<br/>
///<b>LE</b>: LSW (LSB | MSB) | MSW (LSB | MSB). The value 0x0113 is packed the following way: 0x13010000
///</summary>
///[enum]
*/
#define BE                                      0x01 /* <summary>Big Endian. This should be the data order for all items in ISI messages</summary> */
#define LE                                      0x02 /* <summary>Little Endian</summary> */
#define NONE                                    0x04 /* <summary>For BCD strings only. Defines no swapping within each byte in the string.</summary> */
#define NSW                                     0x08 /* <summary>For BCD strings only. Defines nibble swapping within each byte in the string.</summary> */
#define NATIVE BE                                    /* <summary>Native Endianess. Use this, when the endianess (BE / LE) should follow the HW endianess.</summary> */

#define AUTOGEN_DEVICE_ENDIANESS_BE             0x01 /* <summary>Big Endian. This should be the data order for all items in ISI messages marked with NATIVE order.</summary> */
#define AUTOGEN_DEVICE_ENDIANESS_LE             0x02 /*<summary>Little Endian</summary> */

/*
///</enum>
*/

/* when compiling under autogen for HW (not simulator) we force
   little endian-ness for UPP platforms
*/
#ifndef AUTOGEN_DEVICE_ENDIANESS
#if defined(AUTOGEN_ENVIRONMENT_PRODUCT_MCU) && (SIMULATION_ENVIRONMENT == G_SIMULATION_ENVIRONMENT_NONE)
 #if defined(UPP_8M) || defined(UPP_V2)
  #define AUTOGEN_DEVICE_ENDIANESS		AUTOGEN_DEVICE_ENDIANESS_BE
 #else
  #define AUTOGEN_DEVICE_ENDIANESS		AUTOGEN_DEVICE_ENDIANESS_LE
 #endif
#endif
#endif

#undef NATIVE

/* Define NATIVE. Default is BE */
#if ( AUTOGEN_DEVICE_ENDIANESS == AUTOGEN_DEVICE_ENDIANESS_LE )
 #define NATIVE     LE
#else
 #define NATIVE     BE
#endif

/* pointer types */
/*
///<enum name="E_POINTER_TYPE">
///<summary>This enumeration defines possible pointer representations in the ISI header files
///</summary>
///[enum]
*/
#define POINTER_VOID                            AUTOGEN_POINTER_VOID    /* <summary>Generates <b>void*</b></summary> */
#define POINTER_INT32                           AUTOGEN_POINTER_INT32   /* <summary>Generates <b>int32*</b></summary> */
#define POINTER_UINT32                          AUTOGEN_POINTER_UINT32  /* <summary>Generates <b>uint32*</b></summary> */
#define POINTER_INT16                           AUTOGEN_POINTER_INT16   /* <summary>Generates <b>int16*</b></summary> */
#define POINTER_UINT16                          AUTOGEN_POINTER_UINT16  /* <summary>Generates <b>uint16*</b></summary> */
#define POINTER_INT8                            AUTOGEN_POINTER_INT8    /* <summary>Generates <b>int8*</b></summary> */
#define POINTER_UINT8                           AUTOGEN_POINTER_UINT8   /* <summary>Generates <b>uint8*</b></summary> */
#define POINTER_INT64                           AUTOGEN_POINTER_INT64   /* <summary>Generates <b>int64* NOTE:</b> Supported from PMD_FILE_FORMAT 600</summary> */
#define POINTER_UINT64                          AUTOGEN_POINTER_UINT64  /* <summary>Generates <b>uint64* NOTE:</b> Supported from PMD_FILE_FORMAT 600</summary> */
/*
///</enum>
*/

/* presentation types */
/*
///<enum name="E_PRESENTATION_TYPE">
///<summary>This enumeration defines various value presentations. 
///Some of the presentations affect the generated HTML output, but they all affect the PMD file, and the way the value is to be decoded (and encoded).
///</summary>
///[enum]
*/
#define DEC                                     1  /* <summary>Decimal presentation, e.g. 19 or -19</summary> */
#define HEX                                     2  /* <summary>Hexadecimal presentation, e.g. 0x1d</summary> */
#define BIN                                     3  /* <summary>Binary presentation, e.g. b010001001</summary> */
#define ASCII_CHAR                              5  /* <summary>8 bit ASCII character presentation, e.g. 'A'</summary> */
#define UNICODE_CHAR                            6  /* <summary>16 bit Unicode character presentation, e.g. 'A'</summary> */
#define Q1                                      11 /* <summary>Qn notation. Q1 means that raw value is multiplied with 1/(2^1)</summary> */
#define Q2                                      12 /* <summary>Qn notation. Q2 means that raw value is multiplied with 1/(2^2)</summary> */
#define Q3                                      13 /* <summary>Qn notation. Q2 means that raw value is multiplied with 1/(2^3)</summary> */
#define Q4                                      14 /* <summary>Qn notation. Q4 means that raw value is multiplied with 1/(2^4)</summary> */
#define Q5                                      15 /* <summary>Qn notation. Q5 means that raw value is multiplied with 1/(2^5)</summary> */
#define Q6                                      16 /* <summary>Qn notation. Q6 means that raw value is multiplied with 1/(2^6)</summary> */
#define Q7                                      17 /* <summary>Qn notation. Q7 means that raw value is multiplied with 1/(2^7)</summary> */
#define Q8                                      18 /* <summary>Qn notation. Q8 means that raw value is multiplied with 1/(2^8)</summary> */
#define Q9                                      19 /* <summary>Qn notation. Q9 means that raw value is multiplied with 1/(2^9)</summary> */
#define Q10                                     20 /* <summary>Qn notation. Q10 means that raw value is multiplied with 1/(2^10)</summary> */
#define Q11                                     21 /* <summary>Qn notation. Q11 means that raw value is multiplied with 1/(2^11)</summary> */
#define Q12                                     22 /* <summary>Qn notation. Q12 means that raw value is multiplied with 1/(2^12)</summary> */
#define Q13                                     23 /* <summary>Qn notation. Q13 means that raw value is multiplied with 1/(2^13)</summary> */
#define Q14                                     24 /* <summary>Qn notation. Q14 means that raw value is multiplied with 1/(2^14)</summary> */
#define Q15                                     25 /* <summary>Qn notation. Q15 means that raw value is multiplied with 1/(2^15)</summary> */
#define Q16                                     26 /* <summary>Qn notation. Q16 means that raw value is multiplied with 1/(2^16)</summary> */
#define Q17                                     27 /* <summary>Qn notation. Q17 means that raw value is multiplied with 1/(2^17)</summary> */
#define Q18                                     28 /* <summary>Qn notation. Q18 means that raw value is multiplied with 1/(2^18)</summary> */
#define Q19                                     29 /* <summary>Qn notation. Q19 means that raw value is multiplied with 1/(2^19)</summary> */
#define Q20                                     30 /* <summary>Qn notation. Q20 means that raw value is multiplied with 1/(2^20)</summary> */
#define Q21                                     31 /* <summary>Qn notation. Q21 means that raw value is multiplied with 1/(2^21)</summary> */
#define Q22                                     32 /* <summary>Qn notation. Q22 means that raw value is multiplied with 1/(2^22)</summary> */
#define Q23                                     33 /* <summary>Qn notation. Q23 means that raw value is multiplied with 1/(2^23)</summary> */
#define Q24                                     34 /* <summary>Qn notation. Q24 means that raw value is multiplied with 1/(2^24)</summary> */
#define Q25                                     35 /* <summary>Qn notation. Q25 means that raw value is multiplied with 1/(2^25)</summary> */
#define Q26                                     36 /* <summary>Qn notation. Q26 means that raw value is multiplied with 1/(2^26)</summary> */
#define Q27                                     37 /* <summary>Qn notation. Q27 means that raw value is multiplied with 1/(2^27)</summary> */
#define Q28                                     38 /* <summary>Qn notation. Q28 means that raw value is multiplied with 1/(2^28)</summary> */
#define Q29                                     39 /* <summary>Qn notation. Q29 means that raw value is multiplied with 1/(2^29)</summary> */
#define Q30                                     40 /* <summary>Qn notation. Q30 means that raw value is multiplied with 1/(2^30)</summary> */
#define Q31                                     41 /* <summary>Qn notation. Q31 means that raw value is multiplied with 1/(2^31)</summary> */
#define Q32                                     42 /* <summary>Qn notation. Q32 means that raw value is multiplied with 1/(2^32)</summary> */
#define Q33                                     43 /* <summary>Qn notation. Q33 means that raw value is multiplied with 1/(2^33)</summary> */
#define Q34                                     44 /* <summary>Qn notation. Q34 means that raw value is multiplied with 1/(2^34)</summary> */
#define Q35                                     45 /* <summary>Qn notation. Q35 means that raw value is multiplied with 1/(2^35)</summary> */
#define Q36                                     46 /* <summary>Qn notation. Q36 means that raw value is multiplied with 1/(2^36)</summary> */
#define Q37                                     47 /* <summary>Qn notation. Q37 means that raw value is multiplied with 1/(2^37)</summary> */
#define Q38                                     48 /* <summary>Qn notation. Q38 means that raw value is multiplied with 1/(2^38)</summary> */
#define Q39                                     49 /* <summary>Qn notation. Q39 means that raw value is multiplied with 1/(2^39)</summary> */
#define Q40                                     50 /* <summary>Qn notation. Q40 means that raw value is multiplied with 1/(2^40)</summary> */
#define Q41                                     51 /* <summary>Qn notation. Q41 means that raw value is multiplied with 1/(2^41)</summary> */
#define Q42                                     52 /* <summary>Qn notation. Q42 means that raw value is multiplied with 1/(2^42)</summary> */
#define Q43                                     53 /* <summary>Qn notation. Q43 means that raw value is multiplied with 1/(2^43)</summary> */
#define Q44                                     54 /* <summary>Qn notation. Q44 means that raw value is multiplied with 1/(2^44)</summary> */
#define Q45                                     55 /* <summary>Qn notation. Q45 means that raw value is multiplied with 1/(2^45)</summary> */
#define Q46                                     56 /* <summary>Qn notation. Q46 means that raw value is multiplied with 1/(2^46)</summary> */
#define Q47                                     57 /* <summary>Qn notation. Q47 means that raw value is multiplied with 1/(2^47)</summary> */
#define Q48                                     58 /* <summary>Qn notation. Q48 means that raw value is multiplied with 1/(2^48)</summary> */
#define Q49                                     59 /* <summary>Qn notation. Q49 means that raw value is multiplied with 1/(2^49)</summary> */
#define Q50                                     60 /* <summary>Qn notation. Q50 means that raw value is multiplied with 1/(2^50)</summary> */
#define Q51                                     61 /* <summary>Qn notation. Q51 means that raw value is multiplied with 1/(2^51)</summary> */
#define Q52                                     62 /* <summary>Qn notation. Q52 means that raw value is multiplied with 1/(2^52)</summary> */
#define Q53                                     63 /* <summary>Qn notation. Q53 means that raw value is multiplied with 1/(2^53)</summary> */
#define Q54                                     64 /* <summary>Qn notation. Q54 means that raw value is multiplied with 1/(2^54)</summary> */
#define Q55                                     65 /* <summary>Qn notation. Q55 means that raw value is multiplied with 1/(2^55)</summary> */
#define Q56                                     66 /* <summary>Qn notation. Q56 means that raw value is multiplied with 1/(2^56)</summary> */
#define Q57                                     67 /* <summary>Qn notation. Q57 means that raw value is multiplied with 1/(2^57)</summary> */
#define Q58                                     68 /* <summary>Qn notation. Q58 means that raw value is multiplied with 1/(2^58)</summary> */
#define Q59                                     69 /* <summary>Qn notation. Q59 means that raw value is multiplied with 1/(2^59)</summary> */
#define Q60                                     70 /* <summary>Qn notation. Q60 means that raw value is multiplied with 1/(2^60)</summary> */
#define Q61                                     71 /* <summary>Qn notation. Q61 means that raw value is multiplied with 1/(2^61)</summary> */
#define Q62                                     72 /* <summary>Qn notation. Q62 means that raw value is multiplied with 1/(2^62)</summary> */
#define Q63                                     73 /* <summary>Qn notation. Q63 means that raw value is multiplied with 1/(2^63)</summary> */
#define Q64                                     74 /* <summary>Qn notation. Q64 means that raw value is multiplied with 1/(2^64)</summary> */
#define Q65                                     75 /* <summary>Qn notation. Q65 means that raw value is multiplied with 1/(2^65)</summary> */
#define Q66                                     76 /* <summary>Qn notation. Q66 means that raw value is multiplied with 1/(2^66)</summary> */
#define Q67                                     77 /* <summary>Qn notation. Q67 means that raw value is multiplied with 1/(2^67)</summary> */
#define Q68                                     78 /* <summary>Qn notation. Q68 means that raw value is multiplied with 1/(2^68)</summary> */
#define Q69                                     79 /* <summary>Qn notation. Q69 means that raw value is multiplied with 1/(2^69)</summary> */
#define Q70                                     80 /* <summary>Qn notation. Q70 means that raw value is multiplied with 1/(2^70)</summary> */
/*
///</enum>
*/

/* Predefined constant tables */
/*
///<enum name="E_PREDEFINED_CONSTANTS">
///<summary>
///Predefined constants are lists of manually og autogenerated constants, containing global or system related values. 
///Some of the predefined constants are very product dependant, e.g. object ID lists
///</summary>
///[enum]
*/
#define OS_TASK_NAME_8                          90 /* <summary>8 bit variant of MCU OS task names, e.g. UI_TASK. Values are generated from OS macros during PMD file generation</summary> */
#define OS_TASK_NAME                            91 /* <summary>MCU OS task names, e.g. UI_TASK. Values are generated from OS macros during PMD file generation</summary> */
#define OS_BLOCK_SET_NAME                       92 /* <summary>MCU OS block set names, e.g. BLOCK_SET_12. Values are generated from OS macros during PMD file generation</summary> */
#define OS_TIMER_NAME                           93 /* <summary>MCU OS timer names. Values are generated from OS macros during PMD file generation</summary> */
#define OS_RESOURCE_NAME                        94 /* <summary>MCU OS resource names. Values are generated from OS macros during PMD file generation</summary> */

#define ADSP_PROCESS_ID                         95 /* <summary>ADSP proces names (task names), e.g. _idle_task. Values are copied from constant table PROCESS_ID_TBL, generated with sig2macro tool. Note that this does not work with Base band 5 ADSP!</summary> */
#define CDSP_PROCESS_ID                         96 /* <summary>CDSP proces names (task names), e.g. _idle_task. Values are copied from constant table PROCESS_ID_TBL, generated with sig2macro tool. Note that this does not work with Base band 5 ADSP!</summary> */
#define CDSP5_TRACE_SOURCES                     97 /* <summary>CDSP trace source names (for Base band 5 only)</summary> */
#define ADSP5_TRACE_SOURCES                     98 /* <summary>CDSP trace source names (for Base band 5 only)</summary> */

#define OS_ERROR_CODE                           99 /* <summary>MCU OS responses. Values are maintained from os_trace_data.txt</summary> */
#define OS_TASK_STATE                           100 /* <summary>MCU OS task states, e.g. RUNNING.</summary> */
#define OS_HOOK_ID                              101 /* <summary>MCU OS Hook ID's, e.g. HOOK_ALLOC.</summary> */
#define HW_RESET_REASON                         102 /* <summary>HW reset reasons</summary> */
#define TRACEBOX_OBJECT_ID                      103 /* <summary>Object ID's of Trace box</summary> */
#define ADSP_SIGNAL_ID                          104 /* <summary>ADSP signal ID's</summary> */
#define CDSP_SIGNAL_ID                          105 /* <summary>CDSP signal ID's</summary> */
#define CDSP_INTERRUPT_ID                       106 /* <summary>CDSP interrupt ID's</summary> */
#define CDSP_ERROR_ID                           107 /* <summary>CDSP error ID's</summary> */
#define CDSP_ERROR_DESCRIPTION                  108 /* <not_to_be_documented/> */
#define CDSP_ERROR_EXTRA_PARAMETER              109 /* <not_to_be_documented/> */

#define MSG_ID                                  111 /* <not_to_be_documented/> */
#define SUB_MSG_ID                              112 /* <not_to_be_documented/> */
#define FTD_ID                                  113 /* <summary>FTD data names for the specific resource, the predefined constant is used in. Can only be used in Common and Media Controller messages</summary> */
#define PPC_ID                                  114 /* <summary>PPC names. This predefined constant can only be used within the resource, defining PPC resource (Monitor server)</summary> */
#define PRIVATE_ID                              115 /* <summary>Private ID's</summary> */
#define INVARIANT_TRACE_ENTITY_ID               116 /* <summary>Invariant Trace Entity ID's</summary> */
#define RESOURCE_ID                             117 /* <summary>Resource ID's</summary> */
#define XTI_MASTER_ID                           118 /* <summary>XTI master ID's</summary> */
#define SYMBIAN_COMPONENT_ID                    119 /* <summary>Symbian Component ID's</summary> */
#define VENDOR_COMPONENT_TRACE_ENTITY_ID        120 /* <summary>Vendor component trace entity ID's</summary> */

#define PN_RESOURCE                             151 /* <summary>8 bit resource ID, e.g. PN_CALL. Values are manually added the list in autogen source based on pn_const.h</summary> */
#define PN_MEDIA                                152 /* <summary>8 bit media ID, e.g. PN_MEDIA_BT. Values are manually added the list in autogen source based on pn_const.h</summary> */
#define PN_DEVICE                               153 /* <summary>8 bit device ID's, e.g. PN_DEV_PC. Values are manually added the list in autogen source based on pn_const.h</summary> */
#define PN_DEVICE_6                             154 /* <summary>6 bit device ID's, e.g. PN_DEV_PC. Values are manually added the list in autogen source based on pn_const.h. The 6 bit version is to be used with the 10 bit version of the object ID. Merge macros (see <see cref_topic="Merging items"/>) can combine the two into a 16 bit field</summary> */
#define PN_OBJECT                               155 /* <summary>8 bit object ID's, e.g. PN_OBJ_CALL_SERV. Values are parsed from pn_obj_auto.h during PMD file generation. Note that object ID's > 255 are not in this list!</summary> */
#define PN_OBJECT_10                            156 /* <summary>10 bit object ID's, e.g. PN_OBJ_CALL_SERV. Values are manually added the list in autogen source based on pn_const.h. The 10 bit version is to be used with the 6 bit version of the device ID. Merge macros (see <see cref_topic="Merging items"/>) can combine the two into a 16 bit field</summary> */
#define PN_OBJECT_16                            157 /* <summary>16 bit object ID's, e.g. PN_OBJ_CALL_SERV. Values are parsed from pn_obj_auto.h during PMD file generation</summary> */

#define YES_NO                                  161 /* <summary>8 bit version of YES and NO constants, as defined in global.h</summary> */
#define YES_NO_1                                162 /* <summary>1 bit version of YES and NO constants, as defined in global.h. This version must be used in a merged field (see <see cref_topic="Merging items"/>)</summary> */
#define YES_NO_16                               163 /* <summary>16 bit version of YES and NO constants, as defined in global.h</summary> */
#define ON_OFF                                  164 /* <summary>8 bit version of ON and OFF constants, as defined in global.h</summary> */
#define ON_OFF_1                                165 /* <summary>1 bit version of ON and OFF constants, as defined in global.h. This version must be used in a merged field (see <see cref_topic="Merging items"/>)</summary> */
#define ON_OFF_16                               166 /* <summary>16 bit version of ON and OFF constants, as defined in global.h</summary> */
#define ENABLED_DISABLED                        167 /* <summary>8 bit version of ENABLED and DISABLED constants, as defined in global.h</summary> */
#define ENABLED_DISABLED_1                      168 /* <summary>1 bit version of ENABLED and DISABLED constants, as defined in global.h. This version must be used in a merged field (see <see cref_topic="Merging items"/>)</summary> */
#define ENABLED_DISABLED_16                     169 /* <summary>16 bit version of ENABLED and DISABLED constants, as defined in global.h</summary> */
#define OK_FAIL                                 170 /* <summary>8 bit version of OK and FAIL constants, as defined in global.h</summary> */
#define OK_FAIL_1                               171 /* <summary>1 bit version of OK and FAIL constants, as defined in global.h. This version must be used in a merged field (see <see cref_topic="Merging items"/>)</summary> */
#define OK_FAIL_16                              172 /* <summary>16 bit version of OK and FAIL constants, as defined in global.h</summary> */
#define TRUE_FALSE                              173 /* <summary>8 bit version of TRUE and FALSE constants, as defined in global.h</summary> */
#define TRUE_FALSE_1                            174 /* <summary>1 bit version of TRUE and FALSE constants, as defined in global.h. This version must be used in a merged field (see <see cref_topic="Merging items"/>)</summary> */
#define TRUE_FALSE_16                           175 /* <summary>16 bit version of TRUE and FALSE constants, as defined in global.h</summary> */
#define COLD_WARM                               176 /* <summary>8 bit version of COLD and WARM constants, as defined in global.h</summary> */
#define COLD_WARM_1                             177 /* <summary>1 bit version of COLD and WARM constants, as defined in global.h. This version must be used in a merged field (see <see cref_topic="Merging items"/>)</summary> */
#define COLD_WARM_16                            178 /* <summary>16 bit version of COLD and WARM constants, as defined in global.h</summary> */
#define YES_NO_16_BE                            179 /* <summary>16 bit BE version of YES and NO constants, as defined in global.h</summary> */
#define YES_NO_16_LE                            180 /* <summary>16 bit LE version of YES and NO constants, as defined in global.h</summary> */
#define YES_NO_16_NATIVE                        181 /* <summary>16 bit NATIVE version of YES and NO constants, as defined in global.h</summary> */
#define ON_OFF_16_BE                            182 /* <summary>16 bit BE version of ON and OFF constants, as defined in global.h</summary> */
#define ON_OFF_16_LE                            183 /* <summary>16 bit LE version of ON and OFF constants, as defined in global.h</summary> */
#define ON_OFF_16_NATIVE                        184 /* <summary>16 bit NATIVE version of ON and OFF constants, as defined in global.h</summary> */
#define ENABLED_DISABLED_16_BE                  185 /* <summary>16 bit BE version of ENABLED and DISABLED constants, as defined in global.h</summary> */
#define ENABLED_DISABLED_16_LE                  186 /* <summary>16 bit LE version of ENABLED and DISABLED constants, as defined in global.h</summary> */
#define ENABLED_DISABLED_16_NATIVE              187 /* <summary>16 bit NATIVE version of ENABLED and DISABLED constants, as defined in global.h</summary> */
#define OK_FAIL_16_BE                           188 /* <summary>16 bit BE version of OK and FAIL constants, as defined in global.h</summary> */
#define OK_FAIL_16_LE                           189 /* <summary>16 bit LE version of OK and FAIL constants, as defined in global.h</summary> */
#define OK_FAIL_16_NATIVE                       190 /* <summary>16 bit NATIVE version of OK and FAIL constants, as defined in global.h</summary> */
#define TRUE_FALSE_16_BE                        191 /* <summary>16 bit BE version of TRUE and FALSE constants, as defined in global.h</summary> */
#define TRUE_FALSE_16_LE                        192 /* <summary>16 bit LE version of TRUE and FALSE constants, as defined in global.h</summary> */
#define TRUE_FALSE_16_NATIVE                    193 /* <summary>16 bit NATIVE version of TRUE and FALSE constants, as defined in global.h</summary> */
#define COLD_WARM_16_BE                         194 /* <summary>16 bit BE version of COLD and WARM constants, as defined in global.h</summary> */
#define COLD_WARM_16_LE                         195 /* <summary>16 bit LE version of COLD and WARM constants, as defined in global.h</summary> */
#define COLD_WARM_16_NATIVE                     196 /* <summary>16 bit NATIVE version of COLD and WARM constants, as defined in global.h</summary> */
/*
///</enum>
*/

/* resource types */
/*
///<enum name="E_RESOURCE_TYPE">
///<summary>This enumeration defines the resource type of a message macro file (typically one resource is defined in one message macro file). 
///It is very important the the correct resource type is defined, as a lot of tools and logic in autogen in based on this. One example is all ISI rules, 
///which are applied for all ISI resources.
///</summary>
///[enum]
*/
#define RESOURCE_UNKNOWN                        0x00000000U /* <not_to_be_documented/> */
#define RESOURCE_ISI                            0x00000001U /* <summary>See <see cref_topic="ISI resources"/> for a description.</summary> */
#define RESOURCE_ISI_DSP                        0x00000002U /* <not_to_be_documented/> */
#define RESOURCE_ISI_TRACE                      0x00000004U /* <not_to_be_documented/> */
#define RESOURCE_ISI_PREFIX                     0x00000008U /* <summary>ISI interface on <b>PN_PREFIX</b>. See <see cref_topic="ISI resources"/> for a description.</summary> */
#define RESOURCE_ISI_PRIVATE                    0x00000010U /* <summary>Private interface on <b>PN_PRIVATE</b>. See <see cref_topic="ISI private resources"/> for a description.</summary> */
#define RESOURCE_ISI_COMMON_MESSAGES_EXT        0x00000020U /* <summary>Common message interface for <b>PN_PREFIX</b>/<b>PN_PRIVATE</b></summary> */
#define RESOURCE_ISI_COMMON_MESSAGES            0x00000040U /* <summary>Common message interface</summary> */
#define RESOURCE_ISI_MEDIA_CONTROL              0x00000080U /* <summary>Only to be used for defining the <b>PN_MEDIA_CONTROL</b> resource.</summary> */
#define RESOURCE_ISI_GSM_DSP_TEST               0x00000100U /* <not_to_be_documented/> */
#define RESOURCE_ISI_EXTENSION                  0x00000200U /* <summary>Extension to an ISI interface (sharing same resource ID). See <see cref_topic="ISI resources"/>/<see cref_topic="Extension resources"/> for a description.</summary> */
#define RESOURCE_SHARED                         0x00000400U /* <summary>Shared definitions (sub blocks, constants). See <see cref_topic="Shared resources"/> for a description.</summary> */
#define RESOURCE_ISI_SHARED                     RESOURCE_SHARED /* <not_to_be_documented/> */
#define RESOURCE_OST                            0x00000800U /* <not_to_be_documented/> */
#define RESOURCE_TRC_HSP                        0x00001000U /* <not_to_be_documented/> */
#define RESOURCE_PHONET                         0x00002000U /* <summary>See <see cref_topic="PhoNet resources"/> for a description.</summary> */
#define RESOURCE_PHONET_EXT                     0x00004000U /* <summary>See <see cref_topic="PhoNet-Extended resources"/> for a description.</summary> */
#define RESOURCE_SYMBOLS                        0x00008000U /* <summary>Internal autogen resource for defining global constants as OK/FAIL. <b>Should not be used!</b></summary> */
#define RESOURCE_MEDIA_MODULE                   0x00010000U /* <summary>See <see cref_topic="Media module resources"/> for a description.</summary> */
#define RESOURCE_MEDIA_MODULE_EXTENSION         0x00020000U /* <summary>Extension to a media module interface. See <see cref_topic="Media module resources"/>/<see cref_topic="Extension resources"/> for a description.</summary> */
#define RESOURCE_TRC_SYMBIAN                    0x00040000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_INVARIANT                  0x00080000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_CDSP5                      0x00100000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_ADSP5                      0x00200000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_MASTER                     0x00400000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_OS                         0x00800000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_VENDOR                     0x01000000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_MCU                        0x02000000U /* <summary>See <see cref_topic="MCU traces"/> for a description.</summary> */
#define RESOURCE_TRC_DSP5_CDSP                  0x04000000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_DSP5_ADSP                  0x08000000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_DSP5_OMAP                  RESOURCE_TRC_DSP5_ADSP /* <not_to_be_documented/> */
#define RESOURCE_TRC_DSP5                       RESOURCE_TRC_DSP5_CDSP /* <not_to_be_documented/> */
#define RESOURCE_TRC_HAL                        0x10000000U /* <not_to_be_documented/> */
#define RESOURCE_TRC_STI                        0x20000000U /* <not_to_be_documented/> */
#define RESOURCE_PROTOCOL                       0x40000000U /* <summary>See <see cref_topic="Generic protocol resources"/> for a description.</summary> */
#define RESOURCE_PROTOCOL_EXTENSION             0x80000000U /* <summary>Extension to a generic protocol defintion. See <see cref_topic="Generic protocol resources"/>/<see cref_topic="Extension resources"/> for a description.</summary> */
#define RESOURCE_LEGACY                         0x00001234U /* <summary>See <see cref_topic="Resource Legacy"/> for a description.</summary> */


/*
///</enum>
*/

#define RESOURCE_ISI_PREFIX_ANY                (RESOURCE_ISI_PREFIX | RESOURCE_ISI_COMMON_MESSAGES_EXT)

#define RESOURCE_ISI_ANY                       (RESOURCE_ISI | \
                                                RESOURCE_ISI_EXTENSION | \
                                                RESOURCE_ISI_DSP | \
                                                RESOURCE_ISI_COMMON_MESSAGES | \
                                                RESOURCE_ISI_MEDIA_CONTROL | \
                                                RESOURCE_SHARED | \
                                                RESOURCE_ISI_PREFIX_ANY | \
                                                RESOURCE_ISI_PRIVATE)

#define RESOURCE_TRC_ANY                       (RESOURCE_TRC_DSP5_CDSP | \
                                                RESOURCE_TRC_DSP5_ADSP | \
                                                RESOURCE_TRC_CDSP5 | \
                                                RESOURCE_TRC_ADSP5 | \
                                                RESOURCE_TRC_MCU | \
                                                RESOURCE_TRC_SYMBIAN | \
                                                RESOURCE_TRC_INVARIANT | \
                                                RESOURCE_TRC_OS | \
                                                RESOURCE_TRC_HAL | \
                                                RESOURCE_TRC_MASTER | \
                                                RESOURCE_TRC_VENDOR | \
                                                RESOURCE_TRC_STI | \
                                                RESOURCE_TRC_HSP)

#define RESOURCE_EXTENSION_ANY                 (RESOURCE_ISI_EXTENSION | \
                                                RESOURCE_MEDIA_MODULE_EXTENSION | \
                                                RESOURCE_PROTOCOL_EXTENSION)

#define RESOURCE_PROTOCOL_ANY                  (RESOURCE_PROTOCOL | RESOURCE_PROTOCOL_EXTENSION)

#define RESOURCE_ANY                            0xFFFFFFFFU

/* sequence flags */
/*
///<enum name="E_SEQUENCE_TYPE">
///<summary>
///This enumeration defines possible sequence types for the macro <see cref_macro="SEQ_BEGIN"/>.
///</summary>
///[enum]
*/
#define CREATE_STRUCT                           1 /* <summary>A structure is generated in the ISI header file. Should be used when the sequence contains more than one element</summary> */
#define DONT_CREATE_STRUCT                      2 /* <summary>A structure is not generated in the ISI header file. Can be used when the sequence contains only one element</summary> */
/*
///</enum>
*/

/* string types */
/*
///<enum name="E_STRING_TYPE">
///<summary>
///This enumeration defines possible string types to be used with the 
///<see cref_macro="STRING"/> and <see cref_macro="STRING_REF"/> macros.
///</summary>
///[enum]
*/
#define STRING_ASCII                            AUTOGEN_STRING_ASCII                        /* <summary>ASCII string (8 bit per character), without 0-terminator</summary> */
#define STRING_UNICODE                          AUTOGEN_STRING_UNICODE                      /* <summary>Unicode string (16 bit per character), without 0-terminator</summary> */
#define STRING_BCD                              AUTOGEN_STRING_BCD                          /* <summary>Binary Coded Decimal string (4 bit per character/digit). These strings typically represents digits. A BCD string requires a conversion map, so the individual charactyers can be converted to ASCII. The property <see cref_property="PROPERTY_STRING_BCD_MAP"/> can be used to define such map for the BCD string</summary> */
#define STRING_UTF8                             AUTOGEN_STRING_UTF8                         /* <to_be_documented/> */
#define STRING_GSM                              AUTOGEN_STRING_GSM                          /* <not_to_be_documented/> */
#define STRING_ASCII_ZERO_TERMINATED            (STRING_ASCII | NULL_TERMINATION_PRESENT)   /* <summary>ASCII string (8 bit per character), with 0-terminator</summary> */
#define STRING_UNICODE_ZERO_TERMINATED          (STRING_UNICODE | NULL_TERMINATION_PRESENT) /* <summary>Unicode string (16 bit per character), witht 0-terminator</summary> */
#define STRING_UTF8_ZERO_TERMINATED             (STRING_UTF8 | NULL_TERMINATION_PRESENT)
/*
///</enum>
*/

/* timestamp types */
/*
///<enum name="E_TIMESTAMP_TYPE">
///<summary>This enumeration defines the timestamp type for the <see cref_macro="TIMESTAMP"/> macro.</summary>
///[enum]
*/
#define TIMESTAMP_OSTRICH                       PMD_TIMESTAMP_TYPE_STI_XTI      /* <summary>64 bit timestamp (STI/XTI timestamp)</summary> */
#define TIMESTAMP_DSP5                          PMD_TIMESTAMP_TYPE_DSP5         /* <summary>32 bit timestamp</summary> */
#define TIMESTAMP_OS_TICKS                      PMD_TIMESTAMP_TYPE_MCU          /* <summary>16/32 bit MCU timestamp</summary> */
#define TIMESTAMP_GSM_FRAME                     PMD_TIMESTAMP_TYPE_GSM_FRAMES   /* <summary>24 bit timestamp</summary> */
#define TIMESTAMP_WCDMA_CDSP                    PMD_TIMESTAMP_TYPE_CDSP         /* <summary>32 bit timestamp</summary> */
#define TIMESTAMP_ADSP                          PMD_TIMESTAMP_TYPE_ADSP         /* <summary>32 bit timestamp</summary> */
#define TIMESTAMP_WCDMA_ADSP                    PMD_TIMESTAMP_TYPE_ADSP         /* <not_to_be_documented/> */
/*
///</enum>
*/

/* FTD types */
/*
///<enum name="E_FTD_SUPPORTED_MODES">
///<summary>This enumeration defines the possible modes, a certain FTD data can be supported for. 
///The mode can be set using the property <see cref_property="PROPERTY_FTD_SUPPORTED_MODES"/>.
///</summary>
///[enum]
*/
#define FTD_MODE_RD                             PMD_FTD_MODE_RD         /* <summary>RD</summary> */
#define FTD_MODE_INFRA                          PMD_FTD_MODE_INFRA      /* <summary>Infra vendors, close 3rd parties</summary> */
#define FTD_MODE_OPERATOR                       PMD_FTD_MODE_OPERATOR   /* <summary>Operators, distant 3rd parties</summary> */
#define FTD_MODE_ANY                            PMD_FTD_MODE_ANY        /* <summary>Any mode (no restrictions)</summary> */
/*
///</enum>
*/




/* This must end here, as it should be possible to change macro behaviour within a 
   single source file by including this file multiple times
*/
#endif /* ISI_MACROS_H */


/* ============================================================================================= */
/* Message macros */
/* ============================================================================================= */

/* macros related to resource definitions */

/*
///<macro name="RES_BEGIN" group="Resource macros">
///<param name="_type" type="E_RESOURCE_TYPE">Resource type</param>
///<param name="_id" type="constant">Resource ID. The value depends on the resource type. 
///In general, for all trace resources, this should be <b>AUTOGEN_NO_RESOURCE_ID</b></param>
///<param name="_shortname" type="string">Short name of resource, e.g. CALL for Call server. 
///This name is used for autonaming ISI header files (will be [_shortname].h and [_shortname_16.h])</param>
///<param name="_sername" type="string">Server name, e.g. "Call Server". 
///This is the name of the resource to be presented</param>
///<param name="_version" type="string">ISI version of interface. 
///This string determines the actual version of the interface. 
///In product environment, this string should be the exact same as defined 
///in <b>isi_conf.h</b> (so e.g. PMD file corresponds to actual version). 
///In local environment, 
///the version should just be the recommened version, normally the newest. 
///The macro <see cref_macro="RES_VERSION_STRING"/> 
///can be used to automatically define the string based on <b>isi_conf.h</b> and local definitions 
///(in the macro file, the resource is defined) of the version Z and Y constants</param>
///<param name="_suppcomm" type="boolean">Support for common messages. Should be <b>TRUE</b> or <b>FALSE</b>. 
///For non-ISI resources, this should be <b>FALSE</b></param>
///<summary>Begins a resource definition.</summary>
///<remarks>A resource, in autogen terms, is basically a message macro file, 
///representing either an ISI interface or group of trace definitions, 
///e.g. MCU traces for a specific server. 
///<br/><br/>
///All object definitions (messages, traces, sub blocks, constants etc.) must be defined within a resource. 
///So basically the entire file must be encapsulated in <b>RES_BEGIN</b>/<b>RES_END</b> macros. 
///Only macros allowed before <b>RES_BEGIN</b> are comments and properties to the actual resource.
///<br/><br/>
///For each resource type, autogen applies a set of rules for validation the definitions. 
///E.g. a message within an ISI resource must have a transaction ID followed by a message ID, 
///whereas a Phonet message (in a phonet resoures) does not have a transaction ID, and message ID is first byte.
///</remarks>
///<propertyref cref_property="PROPERTY_ALIGNMENT_64_BITS"/>
///<propertyref cref_property="PROPERTY_ALIGNMENT_CHECK_BREAK"/>
///<propertyref cref_property="PROPERTY_ALIGNMENT_CHECK_DISABLE"/>
///<propertyref cref_property="PROPERTY_COPYRIGHT_YEAR"/>
///<propertyref cref_property="PROPERTY_HTML_CONTINUUS_PROJECT_DB"/>
///<propertyref cref_property="PROPERTY_HTML_CONTINUUS_PROJECT_NAME"/>
///<propertyref cref_property="PROPERTY_HTML_DIRECTORY_PATH"/>
///<propertyref cref_property="PROPERTY_HTML_DOCUMENT_NUMBER"/>
///<propertyref cref_property="PROPERTY_HTML_FILENAME"/>
///<propertyref cref_property="PROPERTY_HTML_INCLUDE_INTRODUCTION"/>
///<propertyref cref_property="PROPERTY_HTML_INCLUDE_PHONET_HEADER"/>
///<propertyref cref_property="PROPERTY_HTML_INCLUDE_VARNAME_COLUMN"/>
///<propertyref cref_property="PROPERTY_HTML_TITLE"/>
///<propertyref cref_property="PROPERTY_INHERIT_BASE_RESOURCE_DEFINITIONS"/>
///<propertyref cref_property="PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB"/>
///<propertyref cref_property="PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH"/>
///<propertyref cref_property="PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_FILENAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_FILENAME_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS"/>
///<propertyref cref_property="PROPERTY_ISIHDR_GENERATE_BITFIELDS"/>
///<propertyref cref_property="PROPERTY_ISIHDR_GENERATE_BOOLS"/>
///<propertyref cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER"/>
///<propertyref cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORDS_16"/>
///<propertyref cref_property="PROPERTY_ISI_VERSION_AUTO_GENERATE"/>
///<propertyref cref_property="PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT"/>
///<propertyref cref_property="PROPERTY_PMD_PHONET_DEVICE_ID"/>
///<propertyref cref_property="PROPERTY_PMD_PHONET_OBJECT_ID"/>
///<propertyref cref_property="PROPERTY_PMD_RESOURCE_TRC_IS_HW_MASTER"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_IDENTIFIER"/>
///<propertyref cref_property="PROPERTY_PROJECT_CONFIDENTIALITY"/>
///<propertyref cref_property="PROPERTY_PROJECT_NAME"/>
///<propertyref cref_property="PROPERTY_PROJECT_NOKIA_ENTITY"/>
///<propertyref cref_property="PROPERTY_PROJECT_OWNER_NAME"/>
///<propertyref cref_property="PROPERTY_PROJECT_SITE_NAME"/>
///<propertyref cref_property="PROPERTY_SUBMSG_NAMES_ARE_UNIQUE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="RES_END"/>
///<seealso cref_macro="RES_VERSION_STRING"/>
///</macro>
*/
#undef  RES_BEGIN
#define RES_BEGIN(_type, _id, _shortname, _sername, _version, _suppcomm) \
    init_res_begin(__NOKIA_FILE__, __LINE__, _type, _id, #_id, _sername, #_shortname, _version, _suppcomm, NULL);

/*
///<macro name="RES_END" group="Resource macros">
///<summary>Ends a resource definition.</summary>
///<remarks>
///See <see cref_macro="RES_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="RES_BEGIN"/>
///</macro>
*/
#undef  RES_END
#define RES_END \
    init_res_end(__LINE__);

/*
///<macro name="RES_VERSION_STRING" group="Resource macros">
///<summary>Combines two version numbers into a text string (Z, Y) -> "ZZZ.YYY".</summary>
///<remarks>
///This macro can be used when defining the resource ISI version 
///(using the <see cref_macro="RES_BEGIN"/> macro).
///<br/><br/>
///For an example, showing use of this macro, see 
///<see cref_example="Template file for ISI resources"/>.
///</remarks>
///<seealso cref_macro="RES_BEGIN"/>
///</macro>
*/
#undef  RES_VERSION_STRING
#define RES_VERSION_STRING(_Z, _Y) \
    init_res_version_string(__LINE__, _Z, _Y)

/*
///<macro name="INCLUDE_SHARED_FILE" group="Resource macros">
///<param name="_id" type="constant">ID of the shared resource</param>
///<param name="_verfrom" type="string">Version of client resource, 
///from which the shared resource is included ("" for any).</param>
///<param name="_verto" type="string">Version of client resource, 
///from which the shared resource is no longer included ("" for none).</param>
///<summary>Includes all shared objects from a shared resource file.</summary>
///<remarks>
///See <see cref_topic="Shared resources"/> for an example and more information 
///on shared files.
///</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///</macro>
*/
#undef  INCLUDE_SHARED_FILE
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define INCLUDE_SHARED_FILE(_id, _verfrom, _verto) \
    init_res_include_shared_file(__LINE__, _id, #_id, _verfrom, _verto);
#else
 #define INCLUDE_SHARED_FILE(_id, _verfrom, _verto) \
    init_res_include_shared_file(__LINE__, _id, #_id, _verfrom, _verto);
#endif

/* macros related to constant definitions */

/*
///<macro name="CONSTANT" group="Constant macros">
///<param name="_name" type="constant">Symbolic name of the constant.</param>
///<param name="_id" type="constant">ID of the constant.</param>
///<summary>Defines a constant in the ISI header file, which is valid for all ISI versions.</summary>
///<remarks>
///In case constants larger than what fits into 32 bits are needed it is necessary to switch to PMD_FILE_FORMAT 600 
///by adding the following definition to autogen_local_conf.h and autogen_conf.h:<br/>
///<b>#define PMD_FILE_FORMAT 600</b><br/>
///<b>NOTE: By switching to 64-bit the size of the PMD file will increase!</b>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CONSTANT_VER"/>
///</macro>
*/
#undef  CONSTANT
#if (PMD_FILE_FORMAT >= 600)
#define CONSTANT(_name, _id) \
    init_constant(__LINE__, #_name, (unsigned long long)_id, #_id, _id<0?TRUE:FALSE, "", "");
#else
#define CONSTANT(_name, _id) \
    init_constant(__LINE__, #_name, (unsigned int)_id, #_id, _id<0?TRUE:FALSE, "", "");
#endif

/*
///<macro name="CONSTANT_VER" group="Constant macros">
///<param name="_name" type="constant">Symbolic name of the constant.</param>
///<param name="_id" type="constant">ID of the constant.</param>
///<param name="_verfrom" type="string">Version, from which the constant is valid.</param>
///<param name="_verto" type="string">Version, from which the constant is obsolete.</param>
///<summary>Defines a constant, which is valid for a limited ISI version interval.</summary>
///<remarks>
///In case constants larger than what fits into 32 bits are needed it is necessary to switch to PMD_FILE_FORMAT 600 
///by adding the following definition to autogen_local_conf.h and autogen_conf.h:<br/>
///<b>#define PMD_FILE_FORMAT 600</b><br/>
///<b>NOTE: By switching to 64-bit the size of the PMD file will increase!</b>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CONSTANT"/>
///</macro>
*/
#undef  CONSTANT_VER
#if (PMD_FILE_FORMAT >= 600)
#define CONSTANT_VER(_name, _id, _verfrom, _verto) \
    init_constant(__LINE__, #_name, (unsigned long long)_id, #_id, _id<0?TRUE:FALSE, _verfrom, _verto);
#else
#define CONSTANT_VER(_name, _id, _verfrom, _verto) \
    init_constant(__LINE__, #_name, (unsigned int)_id, #_id, _id<0?TRUE:FALSE, _verfrom, _verto);
#endif


/* macros related to constant table definitions */

/*
///<macro name="CONST_TBL_BEGIN" group="Constant macros">
///<param name="_name" type="constant">Name of table</param>
///<param name="_length" type="constant">Size of constant in bits (a negative value defines a signed constant)</param>
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_verfrom" type="string">Version, from which the table is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the table is obsolete ("" for any version)</param>
///<summary>Begins a constant table definition.</summary>
///<remarks>
///Constant tables are used for defining constant message elements, 
///see <see cref_macro="VALUE_CONST"/>.<br/><br/>
///In case constants larger than what fits into 32 bits are needed it is necessary to switch to PMD_FILE_FORMAT 600. See <see cref_subtopic="Updating an existing message macro file"/><br/>
///Example, showing use of macro:
///<code filename="const_tbl_begin_macro.txt"/>
///which generates the following in the ISI header file:<code filename="const_tbl_begin_isihdr.txt"/>
///and the following in the XML file:<code filename="const_tbl_begin_xml.txt"/>
///With PMD, the message in the example could be decoded like this:<code filename="const_tbl_begin_pmd.txt"/>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_GENERATE_AS_BOOL"/>
///<propertyref cref_property="PROPERTY_ISIHDR_GENERATE_AS_ENUM_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_GENERATE_AS_ENUM_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_USE_CONST_TBL_ENTRY_COMMENT"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CONST_TBL_END"/>
///<seealso cref_macro="BIT_TBL_BEGIN"/>
///<seealso cref_macro="VALUE_CONST"/>
///</macro>
*/
#undef  CONST_TBL_BEGIN
#define CONST_TBL_BEGIN(_name, _length, _order, _verfrom, _verto) \
    init_const_tbl_begin(__LINE__, #_name, _length, _order, _verfrom, _verto, NULL);

/*
///<macro name="CONST_TBL_END" group="Constant macros">
///<summary>Ends a constant table definition.</summary>
///<remarks>
///See <see cref_macro="CONST_TBL_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="CONST_TBL_BEGIN"/>
///</macro>
*/
#undef  CONST_TBL_END
#define CONST_TBL_END \
    init_const_tbl_end(__LINE__);

/*
///<macro name="CONST_TBL_ENTRY" group="Constant macros">
///<param name="_name" type="constant">Symbolic name of table entry</param>
///<param name="_id" type="constant">ID of constant</param>
///<param name="_comment" type="string">Short comment related to the constant. 
///For longer comments, use <see cref_macro="COMMENT"/> macro.</param>
///<summary>
///Defines a constant in a constant table, which is valid for the same ISI versions as 
///the constant table itself.</summary>
///<remarks>
///See <see cref_macro="CONST_TBL_BEGIN"/> for an example of using this macro.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CONST_TBL_BEGIN"/>
///<seealso cref_macro="CONST_TBL_ENTRY_VER"/>
///</macro>
*/
#undef  CONST_TBL_ENTRY
#if (PMD_FILE_FORMAT >= 600)
#define CONST_TBL_ENTRY(_name, _id, _comment) \
    init_const_tbl_entry(__LINE__, #_name,(unsigned long long)_id, "", "", _comment);
#else
#define CONST_TBL_ENTRY(_name, _id, _comment) \
    init_const_tbl_entry(__LINE__, #_name,(unsigned int)_id, "", "", _comment);
#endif

/*
///<macro name="CONST_TBL_ENTRY_VER" group="Constant macros">
///<param name="_name" type="constant">Symbolic name of table entry</param>
///<param name="_id" type="constant">ID of constant</param>
///<param name="_verfrom" type="string">Version, from which the entry is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the entry is obsolete ("" for any version)</param>
///<summary>Defines a constant in a constant table, which is valid for only part of 
///the versions for which the table is valid.</summary>
///<remarks>Comments must be placed before the entry in a separate <see cref_macro="COMMENT"/>.<br/>
///This macro is typically used when adding new entries to an existing constant table.
///<br/><br/>
///See <see cref_macro="CONST_TBL_BEGIN"/> for an example of using this macro.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CONST_TBL_BEGIN"/>
///<seealso cref_macro="CONST_TBL_ENTRY"/>
///</macro>
*/
#undef  CONST_TBL_ENTRY_VER
#if (PMD_FILE_FORMAT >= 600)
#define CONST_TBL_ENTRY_VER(_name, _id, _verfrom, _verto) \
    init_const_tbl_entry(__LINE__, #_name,(unsigned long long)_id, _verfrom, _verto, NULL);
#else
#define CONST_TBL_ENTRY_VER(_name, _id, _verfrom, _verto) \
    init_const_tbl_entry(__LINE__, #_name,(unsigned int)_id, _verfrom, _verto, NULL);
#endif

/*
///<macro name="DER_CONST_TBL_BEGIN" group="Constant macros">
///<param name="_name" type="constant">Name of derived table.</param>
///<param name="_consttblname" type="constant">Name of table from which it was derived.</param>
///<param name="_verfrom" type="string">Version, from which the table is valid.</param>
///<param name="_verto" type="string">Version, from which the table is obsolete.</param>
///<summary>Begins a derived constant table definition.</summary>
///<remarks>
///A derived constant table is a subset of constants already defined 
///in a separate constant table.
///<br/><br/>
///Derived tables are used, when only some of the constants in a table are possible 
///in a given context.
///<br/><br/>
///Nothing is generated in ISI header files from derived table definitions.
///<br/><br/>
///Example, showing derived table definition:
///<code filename="der_const_tbl_begin_macro.txt"/>
///Note that the <see cref_macro="VALUE_CONST"/> macro refers to the derived table, 
///just as it refers to normal tables.
///<br/><br/>
///Please refer to <see cref_macro="CONST_TBL_BEGIN"/> for more information on 
///constant tables in general and more examples.
///</remarks>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<seealso cref_macro="DER_CONST_TBL_END"/>
///<seealso cref_macro="CONST_TBL_BEGIN"/>
///<seealso cref_macro="VALUE_CONST"/>
///</macro>
*/
#undef  DER_CONST_TBL_BEGIN
#define DER_CONST_TBL_BEGIN(_name, _consttblname, _verfrom, _verto) \
    init_der_const_tbl_begin(__LINE__, #_name, #_consttblname, _verfrom, _verto);

/*
///<macro name="DER_CONST_TBL_END" group="Constant macros">
///<summary>Ends a derived constant table definition.</summary>
///<remarks>
///See <see cref_macro="DER_CONST_TBL_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="DER_CONST_TBL_BEGIN"/>
///</macro>
*/
#undef  DER_CONST_TBL_END
#define DER_CONST_TBL_END \
    init_der_const_tbl_end(__LINE__);

/*
///<macro name="DER_CONST_TBL_ENTRY" group="Constant macros">
///<param name="_constname" type="constant">Symbolic name of table entry</param>
///<summary>Defines a constant in a derived constant table.</summary>
///<remarks>
///Please refer to <see cref_macro="DER_CONST_TBL_BEGIN"/> for more information on 
///derived tables and examples.
///</remarks>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="DER_CONST_TBL_ENTRY_VER"/>
///<seealso cref_macro="DER_CONST_TBL_BEGIN"/>
///</macro>
*/
#undef  DER_CONST_TBL_ENTRY
#define DER_CONST_TBL_ENTRY(_constname) \
    init_der_const_tbl_entry(__LINE__, #_constname);

/*
///<macro name="DER_CONST_TBL_ENTRY_VER" group="Constant macros">
///<param name="_constname" type="constant">Symbolic name of table entry</param>
///<param name="_verfrom" type="string">Version, from which the entry is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the entry is obsolete ("" for any version)</param>
///<summary>Defines a constant in a derived constant table for a limited ISI version interval.</summary>
///<remarks>
///Please refer to <see cref_macro="DER_CONST_TBL_BEGIN"/> for more information on 
///derived tables and examples.
///</remarks>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="DER_CONST_TBL_ENTRY"/>
///<seealso cref_macro="DER_CONST_TBL_BEGIN"/>
///</macro>
*/
#undef  DER_CONST_TBL_ENTRY_VER
#define DER_CONST_TBL_ENTRY_VER(_constname, _verfrom, _verto) \
    init_der_const_tbl_entry_ver(__LINE__, #_constname, _verfrom, _verto);


/* macros related to bit table definitions */

/*
///<macro name="BIT_TBL_BEGIN" group="Constant macros">
///<param name="_name" type="constant">Name of table</param>
///<param name="_length" type="constant">Size of constant in bits</param>
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_verfrom" type="string">Version, from which the table is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the table is obsolete ("" for any version)</param>
///<summary>Begins a bit mask table definition. Bit mask tables are typically used for defining bit fields.</summary>
///<remarks>
///To define a message element, using the bit mask table, use the macro <see cref_macro="VALUE_CONST"/>.<br/><br/>
///In case constants larger than what fits into 32 bits are needed it is necessary to switch to PMD_FILE_FORMAT 600 
///<br/><br/>
///Example, showing use of macro:<code filename="bit_tbl_begin_macro.txt"/>
///which generates the following in the ISI header file:<code filename="bit_tbl_begin_isihdr.txt"/>
///and the following in the XML file:<code filename="bit_tbl_begin_xml.txt"/>
///With PMD, the message in the example could be decoded like this:<code filename="bit_tbl_begin_pmd.txt"/>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_GENERATE_AS_BITFIELD"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CONST_TBL_BEGIN"/>
///<seealso cref_macro="BIT_TBL_END"/>
///<seealso cref_macro="VALUE_CONST"/>
///</macro>
*/
#undef  BIT_TBL_BEGIN
#define BIT_TBL_BEGIN(_name, _length, _order, _verfrom, _verto) \
    init_bit_tbl_begin(__LINE__, #_name, _length, _order, _verfrom, _verto, NULL);
   
/*
///<macro name="BIT_TBL_END" group="Constant macros">
///<summary>Ends a bit mask table definition.</summary>
///<remarks>
///See <see cref_macro="BIT_TBL_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="BIT_TBL_BEGIN"/>
///</macro>
*/
#undef  BIT_TBL_END
#define BIT_TBL_END \
    init_bit_tbl_end(__LINE__);

/*
///<macro name="BIT_TBL_ENTRY" group="Constant macros">
///<param name="_bits" type="constant">Bitmask. See remarks.</param>
///<param name="_bitname" type="constant">Symbolic name of the bitmask</param>
///<param name="_comment" type="string">Short comment related to the bit mask. 
///For longer comments, use <see cref_macro="COMMENT"/> macro.</param>
///<summary>Defines a bit mask entry in a bit mask table, which is valid for the same ISI versions as the bit mask table itself.</summary>
///<remarks>
///The bitmask must be a string, with a length corresponding to the size of the bitfield, 
///as defined with <see cref_macro="BIT_TBL_BEGIN"/>. 
///<br/>
///The bitmask string can contain 0, 1 and don't care characters. Typically, a bitmask is defined like this:
///<code filename="bit_tbl_entry_mask1_macro.txt"/>
///which means that if bit 1 is set, the flag is set, else not. A variant could be to define ON/OFF values:
///<code filename="bit_tbl_entry_mask2_macro.txt"/>
///Here, the two constants are mutual exclusive, and are not possible at the same time.
///<br/>
///0's and 1's can be combined in the same string, making the bitfield a bit more complex:
///<code filename="bit_tbl_entry_mask3_macro.txt"/>
///Here, <b>TEST_FLAG_COMBINATION</b> and <b>TEST_FLAG_ON</b> can't be combined, 
///as there is a conflict on 1st bit.
///<br/><br/>
///See <see cref_macro="BIT_TBL_BEGIN"/> for an example of using this macro.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="BIT_TBL_ENTRY_VER"/>
///</macro>
*/
#undef  BIT_TBL_ENTRY
#define BIT_TBL_ENTRY(_bits, _bitname, _comment) \
    init_bit_tbl_entry(__LINE__, _bits, #_bitname, "", "", _comment);

/*
///<macro name="BIT_TBL_ENTRY_VER" group="Constant macros">
///<param name="_bits" type="constant">Bitmask</param>
///<param name="_bitname" type="constant">Symbolic name of the bitmask</param>
///<param name="_verfrom" type="string">Version, from which the entry is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the entry is obsolete ("" for any version)</param>
///<summary>Defines a bit mask entry in a bit mask table, which is valid for only part of the versions the table is valid for.</summary>
///<remarks>
///Typically, this macro is used when adding entries to an existing table. 
///See <see cref_mecro="BIT_TBL_ENTRY"/> for more comments on the parameters.<br/><br/>
///See <see cref_macro="BIT_TBL_BEGIN"/> for an example of using this macro.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="BIT_TBL_ENTRY"/>
///</macro>
*/
#undef  BIT_TBL_ENTRY_VER
#define BIT_TBL_ENTRY_VER(_bits, _bitname, _verfrom, _verto) \
    init_bit_tbl_entry(__LINE__, _bits, #_bitname, _verfrom, _verto, NULL);

/*
///<macro name="DER_BIT_TBL_BEGIN" group="Constant macros">
///<param name="_name" type="constant">Name of table</param>
///<param name="_bittblname" type="constant">Name of original bitmask table</param>
///<param name="_verfrom" type="string">Version, from which the table is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the table is obsolete ("" for any version)</param>
///<summary>Begins a derived bit mask table definition.</summary>
///<remarks>
///A derived bit mask table is a subset of constants already defined 
///in a separate bit mask table.
///<br/><br/>
///Derived tables are used, when only some of the constants in a table are possible 
///in a given context.
///<br/><br/>
///Nothing is generated in ISI header files from derived table definitions.
///<br/><br/>
///Example, showing derived table definition:
///<code filename="der_bit_tbl_begin_macro.txt"/>
///Note that the <see cref_macro="VALUE_CONST"/> macro refers to the derived table, 
///just as it refers to normal tables.
///<br/><br/>
///Please refer to <see cref_macro="BIT_TBL_BEGIN"/> for more information on 
///bitmask tables in general and more examples.
///</remarks>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="DER_BIT_TBL_END"/>
///<seealso cref_macro="BIT_TBL_BEGIN"/>
///<seealso cref_macro="VALUE_CONST"/>
///</macro>
*/
#undef  DER_BIT_TBL_BEGIN
#define DER_BIT_TBL_BEGIN(_name, _bittblname, _verfrom, _verto) \
    init_der_bit_tbl_begin(__LINE__, #_name, #_bittblname, _verfrom, _verto);

/*
///<macro name="DER_BIT_TBL_END" group="Constant macros">
///<summary>Ends a derived bit mask table definition.</summary>
///<remarks>
///See <see cref_macro="DER_BIT_TBL_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="DER_BIT_TBL_BEGIN"/>
///</macro>
*/
#undef  DER_BIT_TBL_END
#define DER_BIT_TBL_END \
    init_der_bit_tbl_end(__LINE__);

/*
///<macro name="DER_BIT_TBL_ENTRY" group="Constant macros">
///<param name="_constname" type="constant">Symbolic name of table entry</param>
///<summary>Defines a constant in a derived bit mask table.</summary>
///<remarks>
///Please refer to <see cref_macro="DER_BIT_TBL_BEGIN"/> for more information on 
///derived tables and examples.
///</remarks>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="DER_BIT_TBL_ENTRY_VER"/>
///<seealso cref_macro="DER_BIT_TBL_BEGIN"/>
///</macro>
*/
#undef  DER_BIT_TBL_ENTRY
#define DER_BIT_TBL_ENTRY(_constname) \
    init_der_bit_tbl_entry(__LINE__, #_constname);

/*
///<macro name="DER_BIT_TBL_ENTRY_VER" group="Constant macros">
///<param name="_constname" type="constant">Symbolic name of table entry</param>
///<param name="_verfrom" type="string">Version, from which the entry is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the entry is obsolete ("" for any version)</param>
///<summary>Defines a constant in a derived bit mask table for a limited ISI version interval.</summary>
///<remarks>
///Please refer to <see cref_macro="DER_BIT_TBL_BEGIN"/> for more information on 
///derived tables and examples.
///</remarks>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<seealso cref_macro="DER_BIT_TBL_ENTRY"/>
///<seealso cref_macro="DER_BIT_TBL_BEGIN"/>
///</macro>
*/
#undef  DER_BIT_TBL_ENTRY_VER
#define DER_BIT_TBL_ENTRY_VER(_constname, _verfrom, _verto) \
    init_der_bit_tbl_entry_ver(__LINE__, #_constname, _verfrom, _verto);


/* macros related to FTD table definitions */

/*
///<macro name="FTD_TBL_BEGIN" group="FTD macros">
///<param name="_verfrom" type="string">Version, from which the table is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the table is obsolete ("" for any version)</param>
///<summary>Begins a FTD table definition.</summary>
///<remarks>
///For examples of FTD data definitions, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="FTD_TBL_END"/>
///<seealso cref_macro="FTD_STRING"/>
///<seealso cref_macro="FTD_VALUE_BEGIN"/>
///<seealso cref_macro="FTD_TABLE_BEGIN"/>
///</macro>
*/
#undef  FTD_TBL_BEGIN
#define FTD_TBL_BEGIN(_verfrom, _verto) \
    init_ftd_tbl_begin(__LINE__, _verfrom, _verto, NULL);

/*
///<macro name="FTD_TBL_END" group="FTD macros">
///<summary>Ends a FTD table definition.</summary>
///<remarks>
///For examples of FTD data definitions, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///<seealso cref_macro="FTD_TBL_BEGIN"/>
///</macro>
*/
#undef  FTD_TBL_END
#define FTD_TBL_END \
    init_ftd_tbl_end(__LINE__);

/*
///<macro name="FTD_STRING" group="FTD macros">
///<param name="_name" type="constant">Symbolic name of the FTD data.</param>
///<param name="_id" type="constant">ID of the constant.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the value.</param>
///<param name="_verfrom" type="string">Version, from which the entry is valid ("" for same version as the table)</param>
///<param name="_verto" type="string">Version, from which the entry is obsolete ("" for same version as the table)</param>
///<summary>Defines a string entry in a FTD table.</summary>
///<remarks>
///For examples of FTD data definitions, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///<propertyref cref_property="PROPERTY_FTD_IS_STATIC_DATA"/>
///<propertyref cref_property="PROPERTY_FTD_SUPPORTED_MODES"/>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="FTD_VALUE_BEGIN"/>
///<seealso cref_macro="FTD_TABLE_BEGIN"/>
///</macro>
*/
#undef  FTD_STRING
#define FTD_STRING(_name, _id, _parname, _verfrom, _verto) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_STRING, _parname);

/*
///<macro name="FTD_TABLE_BEGIN" group="FTD macros">
///<param name="_name" type="constant">Symbolic name of the FTD data.</param>
///<param name="_id" type="constant">ID of the constant.</param>
///<param name="_verfrom" type="string">Version, from which the entry is valid ("" for same version as the table)</param>
///<param name="_verto" type="string">Version, from which the entry is obsolete ("" for same version as the table)</param>
///<summary>Defines a table value entry (an array of values) in a FTD table.</summary>
///<remarks>
///The actual value must be defined using general value macros. The total size of the values defined must be 8, 16 or 32 bits.
///<br/><br/>
///For examples of FTD data definitions, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///<propertyref cref_property="PROPERTY_FTD_IS_STATIC_DATA"/>
///<propertyref cref_property="PROPERTY_FTD_SUPPORTED_MODES"/>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="FTD_TABLE_END"/>
///<seealso cref_macro="FTD_VALUE_BEGIN"/>
///<seealso cref_macro="FTD_STRING"/>
///</macro>
*/
#undef  FTD_TABLE_BEGIN
#define FTD_TABLE_BEGIN(_name, _id, _verfrom, _verto) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_TABLE, NULL);

/*
///<macro name="FTD_TABLE_END" group="FTD macros">
///<summary>Ends a FTD table entry definition.</summary>
///<remarks>
///For examples of FTD data definitions, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///<seealso cref_macro="FTD_TABLE_BEGIN"/>
///</macro>
*/
#undef  FTD_TABLE_END
#define FTD_TABLE_END \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_TABLE);

/*
///<macro name="FTD_VALUE_BEGIN" group="FTD macros">
///<param name="_name" type="constant">Symbolic name of the FTD data.</param>
///<param name="_id" type="constant">ID of the constant.</param>
///<param name="_verfrom" type="string">Version, from which the entry is valid ("" for same version as the table)</param>
///<param name="_verto" type="string">Version, from which the entry is obsolete ("" for same version as the table)</param>
///<summary>Defines a value entry in a FTD table.</summary>
///<remarks>
///The actual value must be defined using general value macros. The total size of the values defined must be 8, 16 or 32 bits.
///<br/><br/>
///For examples of FTD data definitions, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///<propertyref cref_property="PROPERTY_FTD_IS_INPUT_DATA"/>
///<propertyref cref_property="PROPERTY_FTD_IS_STATIC_DATA"/>
///<propertyref cref_property="PROPERTY_FTD_SUPPORTED_MODES"/>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="FTD_VALUE_END"/>
///<seealso cref_macro="FTD_STRING"/>
///<seealso cref_macro="FTD_TABLE_BEGIN"/>
///</macro>
*/
#undef  FTD_VALUE_BEGIN
#define FTD_VALUE_BEGIN(_name, _id, _verfrom, _verto) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_VALUE, NULL);

/*
///<macro name="FTD_VALUE_END" group="FTD macros">
///<summary>Ends a FTD table entry definition.</summary>
///<remarks>
///For examples of FTD data definitions, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///<seealso cref_macro="FTD_VALUE_BEGIN"/>
///</macro>
*/
#undef  FTD_VALUE_END
#define FTD_VALUE_END \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);


/* macros related to PPC table definitions */

/*
///<macro name="PPC_TBL_BEGIN" group="PPC macros">
///<param name="_verfrom" type="string">Version, from which the table is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the table is obsolete ("" for any version)</param>
///<summary>Begins a PPC table definition.</summary>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="PPC_TBL_END"/>
///</macro>
*/
#undef  PPC_TBL_BEGIN
#define PPC_TBL_BEGIN(_verfrom, _verto) \
    init_ppc_tbl_begin(__LINE__, _verfrom, _verto);

/*
///<macro name="PPC_TBL_END" group="PPC macros">
///<summary>Ends a PPC table definition.</summary>
///<seealso cref_macro="PPC_TBL_BEGIN"/>
///</macro>
*/
#undef  PPC_TBL_END
#define PPC_TBL_END \
    init_ppc_tbl_end(__LINE__);

/*
///<macro name="PPC_TBL_ENTRY" group="PPC macros">
///<param name="_name" type="constant">Name of the PPC to define. 
///This ends up as a #define in the ISI header file.</param>
///<param name="_id" type="constant">The numeric value of the PPC. 
///This is the value that the name is #defined to.</param>
///<param name="_seqname" type="string">The name of the sequence that defines that data content of the PPC. 
///This sequence must have the same structure as a sub block.</param>
///<summary>Defines an entry in the PPC table, 
///which is valid for the same versions as the PPC table itself.
///</summary>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="PPC_TBL_ENTRY_VER"/>
///</macro>
*/
#undef  PPC_TBL_ENTRY
#define PPC_TBL_ENTRY(_name, _id, _seqname) \
    init_ppc_tbl_entry(__LINE__, #_name, _id, #_seqname);

/*
///<macro name="PPC_TBL_ENTRY_VER" group="PPC macros">
///<param name="_name" type="constant">Name of the PPC to define. 
///This ends up as a #define in the ISI header file.</param>
///<param name="_id" type="constant">The numeric value of the PPC. 
///This is the value that the name is #defined to.</param>
///<param name="_seqname" type="string">The name of the sequence that defines that 
///data content of the PPC. This sequence must have the same structure as a sub block.
///</param>
///<param name="_verfrom" type="string">Version, from which the table is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which the table is obsolete ("" for any version)</param>
///<summary>Defines an entry in the PPC table, 
///which is only valid for the some of the versions in which the PPC table itself is valid.
///</summary>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<seealso cref_macro="PPC_TBL_ENTRY"/>
///</macro>
*/
#undef  PPC_TBL_ENTRY_VER
#define PPC_TBL_ENTRY_VER(_name, _id, _seqname, _verfrom, _verto) \
    init_ppc_tbl_entry_ver(__LINE__, #_name, _id, #_seqname, _verfrom, _verto);


/* macros related to placeholder sections */

/*
///<macro name="MSG_ID_SECTION" group="Miscellaneous Macros">
///<summary>This is not a normal autogen object, 
///but a placeholder for the part of the generated HTML or ISI header files 
///that lists the possible message ID's.
///</summary>
///<remarks>
///To be used to comment on the message ID section, or remove it!
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SB_ID_SECTION"/>
///</macro>
*/
#undef  MSG_ID_SECTION
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MSG_ID_SECTION \
    init_msg_id_section(__LINE__);
#else
 #define MSG_ID_SECTION
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


/*
///<macro name="SB_ID_SECTION" group="Miscellaneous Macros">
///<summary>This is not a normal autogen object, 
///but a placeholder for the part of the generated HTML or ISI header files 
///that lists the possible sub block ID's.
///</summary>
///<remarks>
///To be used to comment on the sub block ID section, or remove it!
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="MSG_ID_SECTION"/>
///</macro>
*/
#undef  SB_ID_SECTION
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SB_ID_SECTION \
    init_sb_id_section(__LINE__);
#else
 #define SB_ID_SECTION
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


/* macros related to ISI version history definitions */

/*
///<macro name="ISI_VERSION_HISTORY" group="Versioning macros">
///<param name="_version" type="string">ISI version of history element</param>
///<summary>Defines an ISI version history entry</summary>
///<remarks>
///A version history change entry should be made for each version of the interface.<br/>
///The ISI version history only affects ISI header files and HTML documentation.
///<br/><br/>
///Example of an ISI version history entry:
///<code filename="isi_version_history_macro.txt"/>
///which generates the following in the top part (comment section) of the ISI header file, 
///and similar text in the generated HTML documentation:
///<code filename="isi_version_history_isihdr.txt"/>
///</remarks>
///<propertyref cref_property="PROPERTY_CHANGE_DATE"/>
///<propertyref cref_property="PROPERTY_CHANGE_PERSON"/>
///<propertyref cref_property="PROPERTY_CHANGE_REASON"/>
///<propertyref cref_property="PROPERTY_CHANGE_REFERENCE"/>
///<propertyref cref_property="PROPERTY_CHANGE_STATUS"/>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<propertyref cref_property="PROPERTY_VERSION_NO_LONGER_SUPPORTED"/>
///<propertyref cref_property="PROPERTY_VERSION_NOT_YET_SUPPORTED"/>
///</macro>
*/
#undef  ISI_VERSION_HISTORY
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define ISI_VERSION_HISTORY(_version) \
    init_isi_version_history(__LINE__, _version);
#else
 #define ISI_VERSION_HISTORY(_version)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


/* macros related to note definitions */

/*
///<macro name="NOTE" group="Comment macros">
///<param name="_name" type="constant">Name of note</param>
///<summary>Defines a note to be referred to from any comment.</summary>
///<remarks>
///You can refer to the note in any comment definition, using the <see cref_macro="COMMENT_LINK"/> 
///macro with <b>LINK_NOTE</b> as type.
///<br/><br/>
///For an example of note definitions, see <see cref_example="Template file for ISI resources"/>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///</macro>
*/
#undef  NOTE
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
#define NOTE(_name) \
    init_note(__LINE__, _name);
#else
#define NOTE(_name)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


/* macros related to message definitions */
/*
///<macro name="MSG_BEGIN" group="Message macros">
///<param name="_id" type="constant">Message ID, see remarks</param>
///<param name="_type" type="E_MSG_TYPE">Message type</param>
///<param name="_verfrom" type="string">Version, from which message is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which message is obsolete ("" for any version)</param>
///<summary>Begins a message definition.</summary>
///<remarks>
///A message is a specialised sequence of item, for which certain rules are applied. 
///The rules depend on the type of the resourse, the message beongs to, and the message type.<br/>
///All messages, regardles of type, must contain a message ID, defined as a <see cref_macro="REFERENCE"/> with the name <b>MSG_ID</b>.
///<br/><br/>
///The short-cut macro <see cref_macro="COMMON_MSG_HDR"/> can be used for defining the common message 
///items (transaction ID and message ID) for ISI message definitions.
///<br/><br/>
///Example, showing definition of a message pair (request/response):<code filename="msg_begin_macro.txt"/>
///which generates the following in the ISI header file:<code filename="msg_begin_isihdr.txt"/>
///and the following in the XML file:<code filename="msg_begin_xml.txt"/>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_ID"/>
///<propertyref cref_property="PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_NAME"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_MESSAGE_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="MSG_END"/>
///<seealso cref_macro="MSG_PAIR"/>
///<seealso cref_macro="MSG_PAIR_VER"/>
///<seealso cref_macro="SUB_MSG_BEGIN"/>
///</macro>
*/
#undef  MSG_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
#define MSG_BEGIN(_id, _type, _verfrom, _verto) \
    init_msg_begin(__LINE__, _id, #_id, _type, _verfrom, _verto, NULL);
#else
#define MSG_BEGIN(_id, _type, _verfrom, _verto) \
    init_msg_begin(__LINE__, _id, #_id, _type, _verfrom, _verto, NULL);
#endif

/*
///<macro name="MSG_END" group="Message macros">
///<summary>Ends a message definition.</summary>
///<remarks>
///See <see cref_macro="MSG_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="MSG_BEGIN"/>
///<seealso cref_macro="MSG_PAIR"/>
///<seealso cref_macro="MSG_PAIR_VER"/>
///</macro>
*/
#undef  MSG_END
#define MSG_END \
    init_msg_end(__LINE__);

/*
///<macro name="MSG_PAIR" group="Message macros">
///<param name="_reqmsgname" type="constant">Name of request message</param>
///<param name="_respmsgname" type="constant">name of response message</param>
///<summary>Defines a message pair (request/response relation).</summary>
///<remarks>
///This is used to tell autogen which response(s) are possible for a given request.<br/>
///Note that several responses can be possible for a request.
///<br/><br/>
///See <see cref_macro="MSG_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="MSG_BEGIN"/>
///<seealso cref_macro="MSG_PAIR_VER"/>
///<seealso cref_macro="MSG_PAIR_EXT"/>
///<seealso cref_macro="MSG_PAIR_EXT_VER"/>
///</macro>
*/
#undef  MSG_PAIR
#define MSG_PAIR(_reqmsgname, _respmsgname) \
    init_msg_pair(__LINE__, #_reqmsgname, #_respmsgname, NULL, "", "");

/*
///<macro name="MSG_PAIR_EXT" group="Message macros">
///<param name="_reqmsgname" type="constant">Name of request message</param>
///<param name="_respmsgname" type="constant">name of response message</param>
///<param name="_resource" type="constant">name of resource, which contains definition of request message</param>
///<summary>Defines a message pair, when the request message is defined in seperate resource.
///</summary>
///<remarks>
///The macro must be used in the response resource.
///<br/><br/>
///Example of macro use:<code filename="msg_pair_ext_macro.txt"/>
///</remarks>
///<seealso cref_macro="MSG_PAIR"/>
///<seealso cref_macro="MSG_PAIR_VER"/>
///<seealso cref_macro="MSG_PAIR_EXT_VER"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///</macro>
*/
#undef  MSG_PAIR_EXT
#define MSG_PAIR_EXT(_reqmsgname, _respmsgname, _resname) \
    init_msg_pair(__LINE__, #_reqmsgname, #_respmsgname, #_resname, "", "");

/*
///<macro name="MSG_PAIR_VER" group="Message macros">
///<param name="_reqmsgname" type="constant">Name of request message</param>
///<param name="_respmsgname" type="constant">name of response message</param>
///<param name="_verfrom" type="string">Version, from which message pair is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which message pair is obsolete ("" for any version)</param>
///<summary>Defines a message pair (request/response relation) which is only valid for a specified version range.</summary>
///<remarks>
///This is used to tell autogen which response(s) are possible for a given request.<br/>
///Note that several responses can be possible for a request.
///<br/><br/>
///In the following example a general response message is being replaced by a specific response message from version 001.000<br/>
///Macro file before applying versioning to MSG_PAIR:
///<code filename="msg_pair_before_versioning.txt"/>
///Macro file after applying versioning to MSG_PAIR:
///<code filename="msg_pair_after_versioning.txt"/>
///In the example no versioning has been applied to the general response message assuming it it still being used elsewhere in the macro file.
///</remarks>
///<seealso cref_macro="MSG_BEGIN"/>
///<seealso cref_macro="MSG_PAIR"/>
///<seealso cref_macro="MSG_PAIR_EXT"/>
///<seealso cref_macro="MSG_PAIR_EXT_VER"/>
///</macro>
*/
#undef  MSG_PAIR_VER
#define MSG_PAIR_VER(_reqmsgname, _respmsgname, _verfrom, _verto) \
    init_msg_pair(__LINE__, #_reqmsgname, #_respmsgname, NULL, _verfrom, _verto);

/*
///<macro name="MSG_PAIR_EXT_VER" group="Message macros">
///<param name="_reqmsgname" type="constant">Name of request message</param>
///<param name="_respmsgname" type="constant">name of response message</param>
///<param name="_resource" type="constant">name of resource, which contains definition of request message</param>
///<param name="_verfrom" type="string">Version, from which message pair is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which message pair is obsolete ("" for any version)</param>
///<summary>Defines a message pair, when the request message is defined in seperate resource.
///The message pair is only valid for a specified version range.
///</summary>
///<remarks>
///The macro must be used in the response resource.
///<br/><br/>
///</remarks>
///<seealso cref_macro="MSG_PAIR"/>
///<seealso cref_macro="MSG_PAIR_VER"/>
///<seealso cref_macro="MSG_PAIR_EXT"/>
///</macro>
*/
#undef  MSG_PAIR_EXT_VER
#define MSG_PAIR_EXT_VER(_reqmsgname, _respmsgname, _resname, _verfrom, _verto) \
    init_msg_pair(__LINE__, #_reqmsgname, #_respmsgname, #_resname, _verfrom, _verto);

/*
///<macro name="SUB_MSG_BEGIN" group="Message macros">
///<param name="_subid" type="constant">sub message ID</param>
///<param name="_id" type="constant">Message ID</param>
///<param name="_type" type="E_MSG_TYPE">Message type</param>
///<param name="_verfrom" type="string">Version, from which message is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which message is obsolete ("" for any version)</param>
///<summary>Begins a sub message definition.</summary>
///<remarks>A sub message has a primary and secondary message ID.
///<br/><br/>
///The short-cut macro <see cref_macro="COMMON_SUB_MSG_HDR"/> can be used for defining the common message 
///items (transaction ID, message ID and sub message ID) for ISI message definitions.
///<br/><br/>
///By defining a base message it is possible to add a general description to a group of submessages
///based on the base message.
///<br/>
///In case no common description can be given, only the base message ID need to be defined.
///<br/><br/>
///Example, showing definition of a submessages based on base message:
///<code filename="sub_msg_begin_macro.txt"/>
///from which the following is generated in the ISI header file:
///<code filename="sub_msg_begin_isihdr.txt"/>
///If you do not want the base message to appear in the ISI header file then apply
///PROPERTY_ISIHDR_DONT_GENERATE to the base message.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_ID"/>
///<propertyref cref_property="PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_NAME"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_MESSAGE_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SUB_MSG_END"/>
///<seealso cref_macro="SUB_MSG_PAIR"/>
///<seealso cref_macro="MSG_BEGIN"/>
///</macro>
*/
#undef  SUB_MSG_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SUB_MSG_BEGIN(_subid, _id, _type, _verfrom, _verto) \
    init_sub_msg_begin(__LINE__, _subid, #_subid, _id, #_id, _type, _verfrom, _verto, NULL);
#else
 #define SUB_MSG_BEGIN(_subid, _id, _type, _verfrom, _verto) \
    init_sub_msg_begin(__LINE__, _subid, #_subid, _id, #_id, _type, _verfrom, _verto, NULL);
#endif

/*
///<macro name="SUB_MSG_END" group="Message macros">
///<summary>Ends a sub message definition.</summary>
///<remarks>
///See <see cref_macro="SUB_MSG_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="SUB_MSG_BEGIN"/>
///<seealso cref_macro="SUB_MSG_PAIR"/>
///</macro>
*/
#undef  SUB_MSG_END
#define SUB_MSG_END \
    init_sub_msg_end(__LINE__);

/*
///<macro name="SUB_MSG_PAIR" group="Message macros">
///<param name="_reqsubmsgname" type="constant">Name of request submessage</param>
///<param name="_reqmsgname" type="constant">Name of request message</param>
///<param name="_respsubmsgname" type="constant">name of response submessage</param>
///<param name="_respmsgname" type="constant">name of response message</param>
///<summary>Defines a sub message pair.</summary>
///<remarks>
///This is used to tell autogen which response(s) are possible for a given request.<br/>
///Note that several responses can be possible for a request.
///<br/><br/>
///See <see cref_macro="SUB_MSG_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="SUB_MSG_BEGIN"/>
///<seealso cref_macro="SUB_MSG_PAIR_VER"/>
///</macro>
*/
#undef  SUB_MSG_PAIR
#define SUB_MSG_PAIR(_reqsubmsgname, _reqmsgname, _respsubmsgname, _respmsgname) \
    init_sub_msg_pair(__LINE__, #_reqsubmsgname, #_reqmsgname, #_respsubmsgname, #_respmsgname, "", "");

/*
///<macro name="SUB_MSG_PAIR_VER" group="Message macros">
///<param name="_reqsubmsgname" type="constant">Name of request submessage</param>
///<param name="_reqmsgname" type="constant">Name of request message</param>
///<param name="_respsubmsgname" type="constant">name of response submessage</param>
///<param name="_respmsgname" type="constant">name of response message</param>
///<param name="_verfrom" type="string">Version, from which message pair is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which message pair is obsolete ("" for any version)</param>
///<summary>Defines a sub message pair which is only valid for a specified version range.</summary>
///<remarks>
///This is used to tell autogen which response(s) are possible for a given request.<br/>
///Note that several responses can be possible for a request.
///<br/><br/>
///See <see cref_macro="MSG_PAIR_VER"/> for an example of versioning message pair macros.
///</remarks>
///<seealso cref_macro="SUB_MSG_BEGIN"/>
///<seealso cref_macro="SUB_MSG_PAIR"/>
///</macro>
*/
#undef  SUB_MSG_PAIR_VER
#define SUB_MSG_PAIR_VER(_reqsubmsgname, _reqmsgname, _respsubmsgname, _respmsgname, _verfrom, _verto) \
    init_sub_msg_pair(__LINE__, #_reqsubmsgname, #_reqmsgname, #_respsubmsgname, #_respmsgname, _verfrom, _verto);


/* subblock related macros */

/*
///<macro name="SB_BEGIN" group="Sub block macros">
///<param name="_id" type="constant">Name of the subblock.</param>
///<param name="_verfrom" type="string">Version, from which subblock is valid ("" for any version).</param>
///<param name="_verto" type="string">Version, from which subblock is obsolete ("" for any version).</param>
///<summary>Begins a sub block definition.</summary>
///<remarks>
///See <see cref_topic="Sub blocks"/> for more information on sub blocks and examples.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_ID"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_NAME"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_ACTIVATION_TEXT"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_SOURCE"/>
///<propertyref cref_property="PROPERTY_SB_LENGTH_LIMIT"/>
///<propertyref cref_property="PROPERTY_SB_LENGTH_MISSING"/>
///<propertyref cref_property="PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4"/>
///<propertyref cref_property="PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SB_END"/>
///</macro>
*/
#undef  SB_BEGIN
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define SB_BEGIN(_id, _verfrom, _verto) \
    init_sb_begin(__LINE__, #_id, _id, _verfrom, _verto, NULL);
#else
 #define SB_BEGIN(_id, _verfrom, _verto) \
    init_sb_begin(__LINE__, #_id, _id, _verfrom, _verto, NULL);
#endif

/*
///<macro name="SB_END" group="Sub block macros">
///<summary>Ends a sub block definition.</summary>
///<remarks>
///See <see cref_macro="SB_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="SB_BEGIN"/>
///</macro>
*/
#undef  SB_END
#define SB_END \
    init_sb_end(__LINE__);


/* macros related to sequence definitions */

/*
///<macro name="SEQ_BEGIN" group="Sequence macros">
///<param name="_name" type="constant">Name of the sequence.</param>
///<param name="_flag" type="E_SEQUENCE_TYPE">Structure flag</param>
///<param name="_verfrom" type="string">Version, from which sequence is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, from which sequence is obsolete ("" for any version)</param>
///<summary>Begins a sequence definition.</summary>
///<remarks>Sequences are used for defining arrays and structures that are not sub blocks.
///<br/><br/>
///See <see cref_topic="Sequences"/> for examples and more information on sequences in general.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ALIAS_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_NAME"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SEQ_END"/>
///</macro>
*/
#undef  SEQ_BEGIN
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define SEQ_BEGIN(_name, _flag, _verfrom, _verto) \
    init_seq_begin(__LINE__, #_name, _flag, _verfrom, _verto, NULL);
#else
 #define SEQ_BEGIN(_name, _flag, _verfrom, _verto) \
    init_seq_begin(__LINE__, #_name, _flag, _verfrom, _verto, NULL);
#endif
   
/*
///<macro name="SEQ_END" group="Sequence macros">
///<summary>Ends a sequence definition.</summary>
///<remarks>
///See <see cref_macro="SEQ_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="SEQ_BEGIN"/>
///</macro>
*/
#undef  SEQ_END
#define SEQ_END \
    init_seq_end(__LINE__);


/* macros related to merging sequence elements */

/*
///<macro name="MERGE_BEGIN" group="Item macros">
///<param name="_length" type="constant">Size of merged field in bits (8, 16 or 32. 64 available from PMD 6.00).</param>
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the value.</param>
///<summary>Begins a merged field definition.</summary>
///<remarks>Allows merging of several message elements into one. 
///Merging fields is the only way to define items of odd size, not 8, 16, 32, or 64 bits.<br/>
///In case <b>PMD_FILE_FORMAT 600</b> or higher is used (defined in autogen_local_conf.h / autogen_conf.h)
///the merge structure can also be 64 bits wide if 64-bit alignment is enabled. See: <see cref_topic="Using 64-bit macros"/>.
///<br/><br/>
///For examples and more information on merged items, see <see cref_topic="Merging items"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="MERGE_END"/>
///</macro>
*/
#undef  MERGE_BEGIN
#define MERGE_BEGIN(_length, _order, _varname, _parname) \
    init_merge_begin(__LINE__, _length, _order, #_varname, _parname);
   
/*
///<macro name="MERGE_END" group="Item macros">
///<summary>Ends a merged field definition.</summary>
///<remarks>
///See <see cref_macro="MERGE_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="MERGE_BEGIN"/>
///</macro>
*/
#undef  MERGE_END
#define MERGE_END \
    init_merge_end(__LINE__);


/* macros related to constant sequence elements */

/*
///<macro name="VALUE_CONST" group="Item macros">
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the constant.</param>
///<param name="_tblname" type="constant">
///Name of the (derived) constant or (derived) bit mask table, defining the possible constants. 
///The name can also refer to one of the predefined constants, see <see cref_enum="E_PREDEFINED_CONSTANTS"/>.
///</param>
///<summary>Defines a constant, which is based on a (derived) constant or (derived) bit mask table.</summary>
///<remarks>
///For an example of this macro, see <see cref_macro="CONST_TBL_BEGIN"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="VALUE_CONST_IMP"/>
///</macro>
*/
#undef  VALUE_CONST
#define VALUE_CONST(_varname, _parname, _tblname) \
    init_value_const(__LINE__, #_varname, _parname, #_tblname, NULL);

/*
///<macro name="VALUE_CONST_IMP" group="Item macros">
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the constant.</param>
///<param name="_tblname" type="constant">Name of (derived) constant table or 
///(derived) bit mask table.</param>
///<param name="_resname" type="constant">Name of resource where table is defined.</param>
///<summary>Defines a constant, which is based on a constant or bit mask table 
///defined in a separate resource.</summary>
///<remarks>This macro is not commonly used, 
///but it's very convenient when you want to use the same constants in different resources. 
///<br/><br/>
///If the referred table is not found in the given resource, 
///autogen will search possible resource extensions or shared file of the resource.
///<br/><br/>
///Example, showing use of macro within MCU trace:
///<code filename="value_const_imp_macro.txt"/>
///<br/>
///Sharing constants can also be done by using <see cref_topic="Shared resources"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="VALUE_CONST"/>
///</macro>
*/
#undef  VALUE_CONST_IMP
#define VALUE_CONST_IMP(_varname, _parname, _tblname, _resname) \
    init_value_const(__LINE__, #_varname, _parname, #_tblname, #_resname);

/* macros related to sub block list sequence elements */

/*
///<macro name="SB_LST_REF_BEGIN" group="Sub block macros">
///<param name="_type" type="E_SBLIST_TYPE">Type of list</param>
///<param name="_varname" type="string">Name of list variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the list.</param>
///<param name="_refname" type="string">Name of the reference, 
///which stores the number of sub blocks / ID's in the list. See remarks.</param>
///<param name="_flag" type="E_ISIHDR_GENERATION_TYPE">ISI header generation flag.</param>
///<summary>Defines a sub block / sub block ID list with a dynamic number of entries.</summary>
///<remarks>The following predefined names can also be used for <b>_refname</b>:
///<br/>
///<ul>
///<li><b>REF_AS_MANY_AS_POSSIBLE</b>: number of entries is unknown, but implicitly defined by sub block length or message length</li>
///<li><b>REF_OPTIONAL</b>: as <b>REF_AS_MANY_AS_POSSIBLE</b>, but only 0 or 1 occurrence</li>
///</ul>
///<br/>
///For examples and more information on sub blocks, see <see cref_topic="Sub blocks"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SB_LST_REF_END"/>
///<seealso cref_macro="SB_LST_BEGIN"/>
///<seealso cref_macro="REFERENCE"/>
///<seealso cref_macro="REFERENCE_TRANSFORM"/>
///</macro>
*/
#undef  SB_LST_REF_BEGIN
#define SB_LST_REF_BEGIN(_type, _varname, _parname, _refname, _flag) \
    init_sb_lst_begin(__LINE__, _type, #_varname, _parname, 0, NULL, #_refname, _flag);

/*
///<macro name="SB_LST_REF_END" group="Sub block macros">
///<summary>Ends a sub block / sub block ID list definition with a dynamic number of entries.</summary>
///<remarks>
///See <see cref_macro="SB_LST_REF_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="SB_LST_REF_BEGIN"/>
///</macro>
*/
#undef  SB_LST_REF_END
#define SB_LST_REF_END \
    init_sb_lst_end(__LINE__);
   
/*
///<macro name="SB_LST_BEGIN" group="Sub block macros">
///<param name="_type" type="E_SBLIST_TYPE">Type of list</param>
///<param name="_varname" type="string">Name of list variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the list.</param>
///<param name="_n" type="constant">Number of entries in the list.</param>
///<param name="_flag" type="E_ISIHDR_GENERATION_TYPE">ISI header generation flag.</param>
///<summary>Defines a sub block / sub block ID list with a fixed number of entries.</summary>
///<remarks>
///For examples and more information on sub blocks, see <see cref_topic="Sub blocks"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ARRAY_MARKER"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SB_LST_END"/>
///<seealso cref_macro="SB_LST_REF_BEGIN"/>
///</macro>
*/
#undef  SB_LST_BEGIN
#define SB_LST_BEGIN(_type, _varname, _parname, _n, _flag) \
    init_sb_lst_begin(__LINE__, _type, #_varname, _parname, _n, #_n, NULL, _flag);

/*
///<macro name="SB_LST_END" group="Sub block macros">
///<summary>Ends a sub block / sub block ID list definition with a fixed number of entries.</summary>
///<remarks>
///See <see cref_macro="SB_LST_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="SB_LST_BEGIN"/>
///</macro>
*/
#undef  SB_LST_END
#define SB_LST_END \
    init_sb_lst_end(__LINE__);
   
/*
///<macro name="SB_LST_ENTRY" group="Sub block macros">
///<param name="_sbname" type="constant">Name of sub block.</param>
///<summary>Defines a sub block entry in a sub block / sub block ID list.</summary>
///<remarks>The following predefined names can also be used for <b>_sbname</b>:
///<br/>
///<ul>
///<li><b>SB_FTD_ANY</b>: all FTD’s will be inserted here (only valid in common messages)</li>
///<li><b>SB_PPC_ANY</b>: all PPC’s will be inserted here (only valid in Monitor server)</li>
///</ul>
///<br/>
///For examples and more information on sub blocks, see <see cref_topic="Sub blocks"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SB_LST_ENTRY_VER"/>
///<seealso cref_macro="SB_LST_REF_BEGIN"/>
///<seealso cref_macro="SB_LST_BEGIN"/>
///</macro>
*/
#undef  SB_LST_ENTRY
#define SB_LST_ENTRY(_sbname) \
    init_sb_lst_entry(__LINE__, #_sbname, "", "");

/*
///<macro name="SB_LST_ENTRY_VER" group="Sub block macros">
///<param name="_sbname" type="constant">Name of sub block.</param>
///<param name="_verfrom" type="string">Version, 
///from which subblock list entry is valid ("" for any version)</param>
///<param name="_verto" type="string">Version, 
///from which subblock list entry is obsolete ("" for any version)</param>
///<summary>Defines a sub block entry in a sub block / sub block ID list, 
///when the sub block is added for a limited ISI version interval only.</summary>
///<remarks>
///This macro should only be used, when a sub block is inserted in a 
///message/sub block at a later version than the message/sub block itself 
///is defined from. Else, <see cref_macro="SB_LST_ENTRY"/> should be used.
///<br/><br/>
///The following predefined names can also be used for <b>_sbname</b>:
///<br/>
///<ul>
///<li><b>SB_FTD_ANY</b>: all FTD’s will be inserted here (only valid in common messages)</li>
///<li><b>SB_PPC_ANY</b>: all PPC’s will be inserted here (only valid in PPC messages in Monitor server)</li>
///</ul>
///<br/>
///For examples and more information on sub blocks, see <see cref_topic="Sub blocks"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SB_LST_ENTRY"/>
///<seealso cref_macro="SB_LST_REF_BEGIN"/>
///<seealso cref_macro="SB_LST_BEGIN"/>
///</macro>
*/
#undef  SB_LST_ENTRY_VER
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define SB_LST_ENTRY_VER(_sbname, _verfrom, _verto) \
    init_sb_lst_entry(__LINE__, #_sbname, _verfrom, _verto);
#else
 #define SB_LST_ENTRY_VER(_sbname, _verfrom, _verto) \
    init_sb_lst_entry(__LINE__, #_sbname, _verfrom, _verto);
#endif


/* macros related to string sequence elements */

/*
///<macro name="STRING" group="Item macros">
///<param name="_type" type="E_STRING_TYPE">Type of string</param>
///<param name="_order" type="E_ORDER_TYPE">Ordering of bits and bytes in string</param>
///<param name="_varname" type="string">Name of string variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the string.</param>
///<param name="_n" type="constant">String length as number of characters (number of bytes if BCD or UTF-8 string).</param>
///<summary>Defines a text string of fixed length.</summary>
///<remarks>
///For ASCII and Unicode strings, the length is the number of characters (including zero termination, if specified).<br/>
///For BCD and UTF-8 strings, the length is the number of bytes.<br/><br/>
///See <see cref_topic="Strings"/> for a general description of strings.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ARRAY_MARKER"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_STRING_BCD_MAP"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="STRING_REF"/>
///</macro>
*/
#undef  STRING
#define STRING(_type, _order, _varname, _parname, _n) \
    init_string(__LINE__, _type, _order, #_varname, _parname, _n, #_n);

/*
///<macro name="STRING_REF" group="Item macros">
///<param name="_type" type="E_STRING_TYPE">Type of string</param>
///<param name="_order" type="E_ORDER_TYPE">Ordering of bits and bytes in string</param>
///<param name="_varname" type="string">Name of string variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the string.</param>
///<param name="_refname" type="string">Name of the reference, which stores the number of elements. <br/>
///The following predefined reference names can also be used:
///<br/>
///<ul>
///<li><b>REF_AS_LONG_AS_POSSIBLE</b>: String length is unknown, but implicitly defined by sub block length or message length</li>
///<li><b>REF_LENGTH_DETERMINED_BY_ZERO</b>: Length is unknown, but determined by terminating NULL character.</li>
///</ul>
///</param>
///<param name="_flag" type="E_ISIHDR_GENERATION_TYPE">ISI header generation flag.</param>
///<summary>Defines a text string of variable length.</summary>
///<remarks>
///For ASCII and Unicode strings, the length is the number of characters  (including zero termination, if specified).<br/>
///For BCD and UTF-8 strings, the length is the number of bytes.<br/><br/>
///See <see cref_topic="Strings"/> for a general description of strings.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_STRING_BCD_MAP"/>
///<propertyref cref_property="PROPERTY_STRING_MAXIMUM_LENGTH"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="STRING"/>
///<seealso cref_macro="REFERENCE"/>
///<seealso cref_macro="REFERENCE_TRANSFORM"/>
///</macro>
*/
#undef  STRING_REF
#define STRING_REF(_type, _order, _varname, _parname, _refname, _flag) \
    init_string_ref(__LINE__, _type, _order, #_varname, _parname, #_refname, _flag);


/* macros related to array sequence elements */

/*
///<macro name="SEQ_OF" group="Item macros">
///<param name="_varname" type="string">Name of array variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the array.</param>
///<param name="_seqname" type="string">
///Name of sequence or sub block, which defines a single entry in the array.
///<br/><br/>
///The following predefined simple sequences can be used:
///<br/>
///<b>AUTOGEN_SEQ_BYTE_DEC</b><br/>
///<b>AUTOGEN_SEQ_BYTE_HEX</b><br/>
///<b>AUTOGEN_SEQ_WORD_DEC</b><br/>
///<b>AUTOGEN_SEQ_WORD_DEC_BE</b><br/>
///<b>AUTOGEN_SEQ_WORD_DEC_LE</b><br/>
///<b>AUTOGEN_SEQ_WORD_DEC_NATIVE</b><br/>
///<b>AUTOGEN_SEQ_WORD_HEX</b><br/>
///<b>AUTOGEN_SEQ_WORD_HEX_BE</b><br/>
///<b>AUTOGEN_SEQ_WORD_HEX_LE</b><br/>
///<b>AUTOGEN_SEQ_WORD_HEX_NATIVE</b><br/>
///<b>AUTOGEN_SEQ_DWORD_DEC</b><br/>
///<b>AUTOGEN_SEQ_DWORD_DEC_BE</b><br/>
///<b>AUTOGEN_SEQ_DWORD_DEC_LE</b><br/>
///<b>AUTOGEN_SEQ_DWORD_DEC_NATIVE</b><br/>
///<b>AUTOGEN_SEQ_DWORD_HEX</b><br/>
///<b>AUTOGEN_SEQ_DWORD_HEX_BE</b><br/>
///<b>AUTOGEN_SEQ_DWORD_HEX_LE</b><br/>
///<b>AUTOGEN_SEQ_DWORD_HEX_NATIVE</b><br/>
///When using PMD_FILE_FORMAT >= 600 (which has 64-bits support) the following sequences can also be used:
///<b>AUTOGEN_SEQ_DDWORD_DEC_BE</b><br/>
///<b>AUTOGEN_SEQ_DDWORD_DEC_LE</b><br/>
///<b>AUTOGEN_SEQ_DDWORD_DEC_NATIVE</b><br/>
///<b>AUTOGEN_SEQ_DDWORD_HEX_BE</b><br/>
///<b>AUTOGEN_SEQ_DDWORD_HEX_LE</b><br/>
///<b>AUTOGEN_SEQ_DDWORD_HEX_NATIVE</b><br/>
///</param>
///<param name="_n" type="constant">Number of elements in the array.</param>
///<summary>Defines an array with a fixed number of entries.</summary>
///<remarks>
///See <see cref_topic="Arrays"/> and <see cref_topic="Sequences"/> for example and more information.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SEQ_OF_REF"/>
///</macro>
*/
#undef  SEQ_OF
#define SEQ_OF(_varname, _parname, _seqname, _n) \
    init_seq_of(__LINE__, #_varname, _parname, #_seqname, NULL, 0, _n, #_n);

/*
///<macro name="SEQ_OF_REF" group="Item macros">
///<param name="_varname" type="string">Name of array variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the array.</param>
///<param name="_seqname" type="string">
///Name of sequence or sub block, which defines a single entry in the array.
///<br/><br/>
///The following predefined simple sequences can be used:
///<br/>
///<b>AUTOGEN_SEQ_BYTE_DEC</b><br/>
///<b>AUTOGEN_SEQ_BYTE_HEX</b><br/>
///<b>AUTOGEN_SEQ_WORD_DEC</b><br/>
///<b>AUTOGEN_SEQ_WORD_HEX</b><br/>
///<b>AUTOGEN_SEQ_DWORD_DEC</b><br/>
///<b>AUTOGEN_SEQ_DWORD_HEX</b><br/>
///</param>
///<param name="_refname" type="string">Name of the reference, which stores the number of elements.
///<br/><br/>
///The following predefined reference names can also be used:
///<ul>
///<li><b>REF_AS_MANY_AS_POSSIBLE</b>: number of entries is unknown, but implicitly defined by sub block length or message length.</li>
///<li><b>REF_OPTIONAL</b>: as <b>REF_AS_MANY_AS_POSSIBLE</b>, but only 0 or 1 occurrence.</li>
///<li><b>TRACE_DATA_LENGTH</b>: number is identical to the trace data length.</li>
///</ul>
///</param>
///<param name="_flag" type="E_ISIHDR_GENERATION_TYPE">Flag for the variable in the ISI header file</param>
///<summary>Defines an array with a dynamic number of entries.</summary>
///<remarks>
///See <see cref_topic="Arrays"/> and <see cref_topic="Sequences"/> for example and more information.
///</remarks>
///<propertyref cref_property="PROPERTY_ARRAY_MAXIMUM_SIZE"/>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="SEQ_OF"/>
///<seealso cref_macro="REFERENCE"/>
///<seealso cref_macro="REFERENCE_TRANSFORM"/>
///</macro>
*/
#undef  SEQ_OF_REF
#define SEQ_OF_REF(_varname, _parname, _seqname, _refname, _flag) \
    init_seq_of(__LINE__, #_varname, _parname, #_seqname, #_refname, _flag, 0, "0");


/* macros related to reference sequence elemenents */

/*
///<macro name="REFERENCE" group="Item macros">
///<param name="_length" type="constant">Size of value in bits (a negative value defines a signed value).</param>
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_varname" type="constant">Name of reference variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the reference.</param>
///<param name="_refname" type="constant">Name of the reference. See remarks.</param>
///<summary>Defines a value reference to be used as string length, 
///sub block length, sub block count, array size etc.</summary>
///<remarks>
///The following predefined reference names have a special meaning:
///<br/>
///<ul>
///<li><b>MSG_ID</b>: defines a message ID in a message structure.</li>
///<li><b>MSG_LENGTH</b>: defines a message length (only for messages on <see cref_topic="Generic protocol resources"/>).</li>
///<li><b>SUB_MSG_ID</b>: defines a sub message ID in a sub message structure.</li>
///<li><b>SB_ID</b>: defines a sub block ID in a sub block structure.</li>
///<li><b>SB_LENGTH</b>: defines a sub block length in a sub block structure.</li>
///<li><b>PRIVATE_ID</b>: defines a private ID (only for messages on <see cref_topic="ISI private resources"/>).</li>
///<li><b>RESOURCE_ID</b>: defines a prefix resource ID (only for messages on <see cref_topic="ISI prefix resources"/>).</li>
///<li><b>TRACE_GROUP_ID</b>: defines the 16 bit trace group ID (for <see cref_topic="MCU traces"/> only).</li>
///<li><b>TRACE_ID</b>: defines the 16 bit trace ID (for <see cref_topic="MCU traces"/> only).</li>
///<li><b>TRACE_DATA_LENGTH</b>: defines the trace data length field.</li>
///</ul>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_EXCEPTIONAL_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_MINIMUM_VALUE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="REFERENCE_TRANSFORM"/>
///</macro>
*/
#undef  REFERENCE
#define REFERENCE(_length, _order, _varname, _parname, _refname) \
    init_reference(__LINE__, _length, _order, #_varname, _parname, #_refname);

/*
///<macro name="REFERENCE_TRANSFORM" group="Item macros">
///<param name="_oldrefname" type="constant">Name of reference to transform. 
///The following predefined reference names can also be used:<br/>
///<b>TRACE_DATA_LENGTH</b>: length of trace data.
///<b>SB_LENGTH</b>: length of sub block (within sub blocks only).</param>
///<param name="_newrefname" type="constant">Name of new reference.</param>
///<param name="_alg" type="E_ALGORITHM_TYPE">Type of transformation algorithm.</param>
///<param name="_n" type="constant"></param>
///<summary>
///Transforms a value reference to another value reference 
///(for converting bits to bytes, number of bytes to number of characters etc.).
///</summary>
///<remarks>
///Unicode string lengths must be defined in number as characters. The character size is 2 bytes. 
///If a string length in a message is defined in bytes, a transformation is needed.
///<br/><br/>
///Example, showing conversion of the string length from number of bytes to 
///number of Unicode characters:
///<code filename="reference_transform_macro.txt"/>
///</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="REFERENCE"/>
///<seealso cref_macro="SEQ_OF_REF"/>
///<seealso cref_macro="STRING_REF"/>
///<seealso cref_macro="SB_LST_REF_BEGIN"/>
///</macro>
*/
#undef  REFERENCE_TRANSFORM
#define REFERENCE_TRANSFORM(_oldrefname, _newrefname, _alg, _n) \
    init_reference_transform(__LINE__, #_oldrefname, #_newrefname, _alg, #_alg, _n);

/*
///<macro name="REFERENCE_CONST" group="Item macros">
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the value.</param>
///<param name="_refname" type="constant">Name of the reference.</param>
///<param name="_tblname" type="constant">
///Name of the (derived) constant or (derived) bit mask table, 
///defining the possible constants. 
///The name can also refer to one of the predefined constants, 
///see <see cref_enum="E_PREDEFINED_CONSTANTS"/>.
///</param>
///<summary>Defines a constant reference, 
///which serves as a tag for a choice structure.
///</summary>
///<remarks>
///See <see cref_macro="CHOICE_BEGIN"/> for an example of using the macro.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="VALUE_CONST"/>
///</macro>
*/
#undef  REFERENCE_CONST
#define REFERENCE_CONST(_varname, _parname, _refname, _tblname) \
    init_reference_const(__LINE__, #_varname, _parname, #_refname, #_tblname);


/* macros related to filler sequence elements */

/*
///<macro name="FILLER" group="Item macros">
///<param name="_type" type="E_FILLER_TYPE">Type of filler</param>
///<param name="_length" type="constant">Size of filler in bits (for type <b>FILLER_FIXED</b>) 
///or size of alignment in bits (for type <b>FILLER_VARIABLE</b>)</param>
///<summary>Adds a filler element to a sequence, message or sub block.</summary>
///<remarks>The filler variable name in the ISI header file is auto named (e.g. fill1).
///<br/><br/>
///Note, that if replaceing a filler/reserved field with an information field, 
///the new field must have a default value of 0 (which must be defined with 
///<see cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>) to be backward compatible.
///<br/><br/>
///Example of a filler definitions:
///<code filename="filler_macro.txt"/>
///Note that the first filler definition ensures correct alignment of the 16-bit field, 
///whereas the second ensures that the sub block length is divisible by 4.
///<br/>
///In case 64-bits alignment is used then a 64-bits variable filler must be used to ensure that sub block length 
///is divisible by 8. See <see cref_subtopic="Updating an existing message macro file"/>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="FILLER_EX"/>
///</macro>
*/
#undef  FILLER
#define FILLER(_type, _length) \
    init_filler(__LINE__, _type, _length);

/*
///<macro name="FILLER_EX" group="Item macros">
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_length" type="constant">Size of filler in bits (must be 8 or 16).</param>
///<param name="_n" type="constant">Number of fillers (of size <b>_length</b>).</param>
///<summary>Adds a filler element to a sequence, message or sub block.</summary>
///<remarks>Should be used when a certain variable name is wanted for the filler.
///<br/><br/>
///Note, that this macro variant only works for fixed fillers.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="FILLER"/>
///</macro>
*/
#undef  FILLER_EX
#define FILLER_EX(_varname, _length, _n) \
    init_filler_ex(__LINE__, #_varname, _length, _n);


/* macros related to block sequence elements */

/*
///<macro name="BLOCK" group="Item macros">
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the value.</param>
///<param name="_type" type="E_BLOCK_TYPE">Block type.</param>
///<param name="_data1" type="constant">Block data (1).
///For <b>_type</b> = <b>BLOCK_EXT_DECODER</b>: name of DLL.<br/>
///For <b>_type</b> = <b>BLOCK_PROTOCOL</b>: name of protocol.<br/>
///For <b>_type</b> = <b>BLOCK_PMD_ANCHOR</b>: name of structure. Must be agreed with TSS.<br/>
///Else NULL
///</param>
///<param name="_data2" type="constant">Block data (2).<br/><br/>
///For <b>_type</b> = <b>BLOCK_EXT_DECODER</b>: name of function in DLL<br/>
///Else NULL
///</param>
///<param name="_flag" type="value">Block flags. 
///<br/><br/>
///For <b>_type</b> = <b>BLOCK_EXT_DECODER</b>: Flags: <see cref_enum="E_BLOCK_DLL_FLAGS"/><br/>
///For <b>_type</b> = <b>BLOCK_PN_MSG</b>: Flags: <see cref_enum="E_BLOCK_MSG_FLAGS"/><br/>
///Else, the value should be 0.
///</param>
///<param name="_n" type="constant">Number of elements in the array.</param>
///<summary>Defines a block of bytes, which should be decoded in a special way. The block has a fixed length</summary>
///<remarks>
///Before using this macro for an external decoding DLL, 
///please check with tracing.support@nokia.com whether there are other options.
///<br/><br/>
///See <see cref_topic="Generic protocol resources"/> for a description of generic protocols and examples.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="BLOCK_REF"/>
///</macro>
*/
#undef  BLOCK
#define BLOCK(_order, _varname, _parname, _type, _data1, _data2, _flags, _n) \
    init_block(__LINE__, _order, #_varname, _parname, _type, _data1, _data2, _flags, NULL, _n, #_n);

/*
///<macro name="BLOCK_REF" group="Item macros">
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the value.</param>
///<param name="_type" type="E_BLOCK_TYPE">Block type.</param>
///<param name="_data1" type="constant">Block data (1).
///For <b>_type</b> = <b>BLOCK_EXT_DECODER</b>: name of DLL.<br/>
///For <b>_type</b> = <b>BLOCK_PROTOCOL</b>: name of protocol.<br/>
///For <b>_type</b> = <b>BLOCK_PMD_ANCHOR</b>: name of structure. Must be agreed with TSS.<br/>
///Else NULL
///</param>
///<param name="_data2" type="constant">Block data (2).<br/><br/>
///For <b>_type</b> = <b>BLOCK_EXT_DECODER</b>: name of function in DLL<br/>
///Else NULL
///</param>
///<param name="_flag" type="value">Block flags. 
///<br/><br/>
///For <b>_type</b> = <b>BLOCK_EXT_DECODER</b>: Flags: <see cref_enum="E_BLOCK_DLL_FLAGS"/><br/>
///For <b>_type</b> = <b>BLOCK_PN_MSG</b>: Flags: <see cref_enum="E_BLOCK_MSG_FLAGS"/><br/>
///Else, the value should be 0.
///</param>
///<param name="_refname" type="constant">Name of the reference, which stores the number of bytes in the block.<br/>
///The following predefined reference names can also be used:
///<br/>
///<ul>
///<li><b>REF_AS_MANY_AS_POSSIBLE</b>: 
///number of bytes is unknown, but is implicitly defined by sub block length or message length.</li>
///<li><b>REF_LENGTH_UNKNOWN</b>: 
///number of bytes is unknown, but is implicitly defined by the block data.</li>
///<li><b>TRACE_DATA_LENGTH</b>: 
///number of bytes is identical to the trace data length.</li>
///</ul>
///</param>
///<summary>Defines a block, which should be decoded in a special way.</summary>
///<remarks>
///Example of defining a MCU trace containing an embedded PhoNet message:
///<code filename="block_ref_msg_macro.txt"/>
///Example of defining a MCU trace containing data to be decoded by external DLL:
///<code filename="block_ref_dll_macro.txt"/>
///<br/>
///Before using this macro for an external decoding DLL, 
///please check with tracing.support@nokia.com whether there are other options.
///<br/><br/>
///See <see cref_topic="Generic protocol resources"/> for a description of generic protocols and examples.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_ARRAY_MARKER"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="BLOCK_REF"/>
///</macro>
*/
#undef  BLOCK_REF
#define BLOCK_REF(_order, _varname, _parname, _type, _data1, _data2, _flags, _refname) \
    init_block(__LINE__, _order, #_varname, _parname, _type, _data1, _data2, _flags, #_refname, 0, "0");

/* printf sequence elements */

/*
///<macro name="PRINTF_BEGIN" group="Item macros">
///<param name="_format" type="string">
///Format string for printf macro.<br/>
///The format string is similar to a C printf format string with the restrictions listed here:<br/>
///<ul>
///  <li>Only a subset of C specifiers allowed: c, d, i, o, u, x, X, p, s, %<br/>
///    <table border="0">
///      <tr valign="top">
///        <td>Specifier</td>
///        <td>Allowed macro to contain argument value</td>
///        <td>Comment</td>
///      </tr>
///      <tr valign="top">
///        <td>c, d, i, o, u, x, X</td>
///        <td><see cref_macro="VALUE"/></td>
///        <td>Use presentation type ASCII_CHAR for %c, presentation type HEX for %o, %x, %X and presentation type DEC for %d, %i and %u.
///            See <see cref_enum="E_PRESENTATION_TYPE"/></td>
///      </tr>
///      <tr valign="top">
///        <td>p</td>
///        <td><see cref_macro="POINTER"/></td>
///        <td></td>
///      </tr>
///      <tr valign="top">
///        <td>s</td>
///        <td><see cref_macro="STRING"/> or <see cref_macro="STRING_REF"/></td>
///        <td>Only string type STRING_ASCII and STRING_ASCII_ZERO_TERMINATED allowed. See <see cref_enum="E_STRING_TYPE"/></td>
///      </tr>
///    </table>
///  </li>
///</ul>
///It is allowed to use <see cref_macro="FILLER"/> in the parameter list. The filler will not be matched up against a specifier.
///</param>
///<summary>Begins a definition of a printf statement. Currently only supported for Symbian traces.</summary>
///<remarks>
///See <see cref_topic="Printf"/> topic for further description of for usage and examples.
///</remarks>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME"/>
///<seealso cref_macro="PRINTF_END"/>
///<seealso cref_property="PROPERTY_COMPONENT_ID"/>
///</macro>
*/
#undef PRINTF_BEGIN
#ifndef PRINTF_BEGIN
#define PRINTF_BEGIN(_format) \
    init_printf_begin(__LINE__, _format);
#endif

/*
///<macro name="PRINTF_END" group="Item macros">
///<summary>Ends a definition of a printf statement. Currently only supported for Symbian traces.</summary>
///<remarks>
///See <see cref_topic="Printf"/> topic for further description of for usage and examples.
///</remarks>
///<seealso cref_macro="PRINTF_BEGIN"/>
///</macro>
*/
#undef PRINTF_END
#ifndef PRINTF_END
#define PRINTF_END \
    init_printf_end(__LINE__);
#endif

/* macros related to timestamp sequence elements */

/*
///<macro name="TIMESTAMP" group="Item macros">
///<param name="_length" type="constant">Size of value in bits (a negative value defines a signed value).</param>
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_varname" type="constant">Name of timestamp variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the timestamp.</param>
///<param name="_type" type="E_TIMESTAMP_TYPE">Timestamp type.</param>
///<summary>Defines a timestamp. Timestamps are most often used in trace related messages or in traces themselves.</summary>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///</macro>
*/
#undef  TIMESTAMP
#define TIMESTAMP(_length, _order, _varname, _parname, _type) \
    init_timestamp(__LINE__, _length, _order, #_varname, _parname, _type);


/* macros related to pointer sequence elements */

/*
///<macro name="POINTER" group="Item macros">
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_varname" type="constant">Name of pointer variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the pointer.</param>
///<param name="_type" type="E_POINTER_TYPE">Type of the pointer <see cref="POINTER_TYPES"/>.</param>
///<summary>Defines a pointer value.</summary>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///</macro>
*/
#undef  POINTER
#define POINTER(_order, _varname, _parname, _type) \
    init_pointer(__LINE__, _order, #_varname, _parname, _type);


/* macros related to value sequence elements */

/*
///<macro name="VALUE" group="Item macros">
///<param name="_length" type="constant">Size of value in bits 
///(a negative value defines a signed value).</param>
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the value.</param>
///<param name="_pres" type="E_PRESENTATION_TYPE">Presentation type.</param>
///<summary>Defines a simple value item.</summary>
///<remarks>
///This macro can be used in any message, trace, sub block or sequence definition.
///<br/>
///In case constants larger than what fits into 32 bits are needed it is necessary to switch to PMD_FILE_FORMAT 600. See <see cref_subtopic="Updating an existing message macro file"/> 
///<br/><br/>
///Example of a value definition in a sub block:
///<code filename="value1_macro.txt"/>
///The value represents an unsigned word (16-bit), and is encoded/decoded as decimal 
///value with PMD. Besides, a default value of 1 is assigned the value.
///<br/><br/>
///Example of a more complex value definition:
///<code filename="value2_macro.txt"/>
///The value represents a signed word (16-bit) and is encoded/decoded as Q2 value, 
///which means that a value of -5 will be decoded as -5*1/2^2 = -1.25.
///<br/><br/>
///Even more complex values can be defined using the macro <see cref_macro="VALUE_EX"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_EXCEPTIONAL_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION"/>
///<propertyref cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_MINIMUM_VALUE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="VALUE_EX"/>
///<seealso cref_macro="VALUE_CONST"/>
///</macro>
*/
#undef  VALUE
#define VALUE(_length, _order, _varname, _parname, _pres) \
    init_value(__LINE__, _length, _order, #_varname, _parname, _pres);

/*
///<macro name="VALUE_EX" group="Item macros">
///<param name="_length" type="constant">Size of value in bits 
///(a negative value defines a signed value).</param>
///<param name="_order" type="E_ORDER_TYPE"><b>NATIVE</b>, <b>BE</b> or <b>LE</b></param>
///<param name="_varname" type="constant">Name of variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the value.</param>
///<param name="_pres" type="E_PRESENTATION_TYPE">Presentation type.</param>
///<param name="_scale" type="constant">Scale to be applied when presenting the 
///value (default  = 1.0).</param>
///<param name="_offset" type="constant">Offset to be applied when presenting the 
///value (default  = 0.0).</param>
///<param name="_unit" type="string">Unit of measure ("" if none).</param>
///<summary>Defines a simple value item with extended presentation possibilities.</summary>
///<remarks>
///This macro can be used in any message, trace, sub block or sequence definition.
///<br/>
///In case constants larger than what fits into 32 bits are needed it is necessary to switch to PMD_FILE_FORMAT 600. See <see cref_subtopic="Updating an existing message macro file"/>
///<br/><br/>
///Example of a value definition in a sub block:
///<code filename="value_ex_macro.txt"/>
///The value represents an unsigned byte (8-bit), with the real value range from -63.0 dBm to 64.5 dBm.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_AS_ARRAY"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_EXCEPTIONAL_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION"/>
///<propertyref cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>
///<propertyref cref_property="PROPERTY_ITEM_MINIMUM_VALUE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER"/>
///<propertyref cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="VALUE"/>
///<seealso cref_macro="VALUE_CONST"/>
///</macro>
*/
#undef  VALUE_EX
#define VALUE_EX(_length, _order, _varname, _parname, _pres, _scale, _offset, _unit) \
    init_value_ex(__LINE__, _length, _order, #_varname, _parname, _pres, (double)_scale, (double)_offset, _unit);


/* macros related to choice sequence elements */

/*
///<macro name="CHOICE_BEGIN" group="Item macros">
///<param name="_varname" type="constant">Name of choice variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the choice.</param>
///<param name="_refname" type="string">Name of the reference (tag).</param>
///<summary>Begins a choice structure.</summary>
///<remarks>
///A choice structure is similar to a switch/case structure in the C language.
///<br/><br/>
///A tag must be defined using the macro <see cref_macro="REFERENCE_CONST"/>, 
///which is based on a constant table. 
///Each case must be defined using the <see cref_macro="CASE"/> or 
///<see cref_macro="CASE_VER"/> macros, 
///and a default case can be defined using the macro <see cref_macro="CASE_DEFAULT"/>.
///<br/><br/>
///The different cases (what is the message structure like, when the tag has a special value), 
///must be defined using <see cref_macro="CASE_BEGIN"/> / <see cref_macro="CASE_END"/> and 
///<see cref_macro="DEFAULT_BEGIN"/> / <see cref_macro="DEFAULT_END"/>.
///<br/><br/>
///In the ISI header file, only the default value is generated. 
///So most likely, you need to define a default value, though you might not need one.
///<br/><br/>
///Example of choice structure:
///<code filename="choice_begin_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="choice_begin_isihdr.txt"/>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="REFERENCE_CONST"/>
///<seealso cref_macro="CASE_BEGIN"/>
///<seealso cref_macro="CASE_END"/>
///<seealso cref_macro="DEFAULT_BEGIN"/>
///<seealso cref_macro="DEFAULT_END"/>
///</macro>
*/
#undef  CHOICE_BEGIN
#define CHOICE_BEGIN(_varname, _parname, _refname) \
    init_choice_begin(__LINE__, #_varname, _parname, #_refname, NULL, 0, MACRO_CHOICE_BEGIN);

/*
///<macro name="CHOICE_VALUE_BEGIN" group="Item macros">
///<param name="_varname" type="constant">Name of choice variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the choice.</param>
///<param name="_refname" type="string">Name of the reference (tag).</param>
///<summary>Begins a choice structure based on a value reference.</summary>
///<remarks>
///A choice structure is similar to a switch/case structure in the C language.
///<br/><br/>
///A tag must be defined using the macro <see cref_macro="REFERENCE"/>. 
///Each case must be defined using the <see cref_macro="CASE"/> or 
///<see cref_macro="CASE_VER"/> macros, 
///and a default case can be defined using the macro <see cref_macro="CASE_DEFAULT"/>.
///<br/><br/>
///The different cases (what is the message structure like, when the tag has a special value), 
///must be defined using <see cref_macro="CASE_BEGIN"/> / <see cref_macro="CASE_END"/> and 
///<see cref_macro="DEFAULT_BEGIN"/> / <see cref_macro="DEFAULT_END"/>.
///<br/><br/>
///In the ISI header file, only the default value is generated. 
///So most likely, you need to define a default value, though you might not need one.
///<br/><br/>
///Example of choice value begin structure:
///<code filename="choiceValueBegin.txt"/>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DEFINITION_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_VARNAME_16"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="REFERENCE"/>
///<seealso cref_macro="REFERENCE_TRANSFORM"/>
///<seealso cref_macro="CASE_BEGIN"/>
///<seealso cref_macro="CASE_END"/>
///<seealso cref_macro="DEFAULT_BEGIN"/>
///<seealso cref_macro="DEFAULT_END"/>
///</macro>
*/
#undef  CHOICE_VALUE_BEGIN
#define CHOICE_VALUE_BEGIN(_varname, _parname, _refname) \
    init_choice_begin(__LINE__, #_varname, _parname, #_refname, NULL, 0, MACRO_CHOICE_VALUE_BEGIN);

/*
///<macro name="CHOICE_END" group="Item macros">
///<summary>Ends a choice definition.</summary>
///<remarks>
///See <see cref_macro="CHOICE_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="CHOICE_BEGIN"/>
///<seealso cref_macro="CHOICE_VALUE_BEGIN"/>
///</macro>
*/
#undef  CHOICE_END
#define CHOICE_END \
    init_choice_end(__LINE__);

/*
///<macro name="CHOICE_FORWARD_BEGIN" group="Item macros">
///<param name="_varname" type="constant">Name of choice variable in ISI header file.</param>
///<param name="_parname" type="string">Name used when encoding/decoding the choice.</param>
///<param name="_tblname" type="constant">
///Name of the (derived) constant or (derived) bit mask table, defining the possible constants. 
///The name can also refer to one of the predefined constants, 
///see <see cref_enum="E_PREDEFINED_CONSTANTS"/>.
///</param>
///<param name="_relpos" type="constant">Position of the value deciding the choice, 
///relative to the position of the CHOICE_FORWARD_BEGIN macro. The offset is given in bytes.</param>
///<summary>
///Begins a choice structure, much like <see cref_macro="CHOICE_BEGIN"/>, 
///except it doesn't use an ordinary reference, 
///but rather uses the value somewhere later in the message.
///</summary>
///<remarks>
///This macro should not be used unless it's absolutely necessary, 
///as autogen is not able to verify the validity of the choice reference.
///</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CHOICE_BEGIN"/>
///<seealso cref_macro="REFERENCE_CONST"/>
///<seealso cref_macro="CASE_BEGIN"/>
///<seealso cref_macro="CASE_END"/>
///<seealso cref_macro="DEFAULT_BEGIN"/>
///<seealso cref_macro="DEFAULT_END"/>
///</macro>
*/
#undef  CHOICE_FORWARD_BEGIN
#define CHOICE_FORWARD_BEGIN(_varname, _parname, _tblname, _relpos) \
    init_choice_begin(__LINE__, #_varname, _parname, "", #_tblname, _relpos, MACRO_CHOICE_FORWARD_BEGIN);


/*
///<macro name="CASE_BEGIN" group="Item macros">
///<param name="_tagname" type="string">Name of constant, which defines this case.</param>
///<param name="_verfrom" type="string">Version, 
///from which the case should be included ("" for the same version as the whole choice structue).</param>
///<param name="_verto" type="string">Version, 
///from which the case should no longer be included ("" for the same version as the whole choice structue).</param>
///<summary>Defines a case in a choice structure.</summary>
///<remarks>
///The value to switch on must be one of the constants in the constant table 
///used as tag (defined with the <see cref_macro="REFERENCE_CONST"/> macro).
///<br/><br/>
///See <see cref_macro="CHOICE_BEGIN"/> for examples of choice structures.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CHOICE_BEGIN"/>
///<seealso cref_macro="REFERENCE_CONST"/>
///<seealso cref_macro="CASE_END"/>
///<seealso cref_macro="DEFAULT_BEGIN"/>
///</macro>
*/
#undef  CASE_BEGIN
#define CASE_BEGIN(_tagname, _verfrom, _verto) \
    init_case(__LINE__, #_tagname, 0, FALSE, NULL, _verfrom, _verto, MACRO_CASE_BEGIN);

/*
///<macro name="CASE_END" group="Item macros">
///<summary>Ends a case definition in a choice structure.</summary>
///<seealso cref_macro="CASE_BEGIN"/>
///</macro>
*/
#undef  CASE_END
#define CASE_END \
    init_case_end(__LINE__);

/*
///<macro name="DEFAULT_BEGIN" group="Item macros">
///<param name="_verfrom" type="string">Version, 
///from which the case should be included ("" for the same version as the whole choice structue).</param>
///<param name="_verto" type="string">Version, 
///from which the case should no longer be included ("" for the same version as the whole choice structue).</param>
///<summary>Defines a case in a choice structure.</summary>
///<remarks>
///The value to switch on must be one of the constants in the constant table 
///used as tag (defined with the <see cref_macro="REFERENCE_CONST"/> macro).
///<br/><br/>
///See <see cref_macro="CHOICE_BEGIN"/> for examples of choice structures.
///Example of default begin structure:
///<code filename="choiceCaseDefaultBegin.txt"/>
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="CHOICE_BEGIN"/>
///<seealso cref_macro="REFERENCE_CONST"/>
///<seealso cref_macro="CASE_END"/>
///<seealso cref_macro="DEFAULT_END"/>
///</macro>
*/
#undef  DEFAULT_BEGIN
#define DEFAULT_BEGIN(_verfrom, _verto) \
    init_case(__LINE__, NULL, 0, FALSE, NULL, _verfrom, _verto, MACRO_DEFAULT_BEGIN);

/*
///<macro name="DEFAULT_END" group="Item macros">
///<summary>Ends a case definition in a choice structure.</summary>
///<seealso cref_macro="DEFAULT_BEGIN"/>
///</macro>
*/
#undef  DEFAULT_END
#define DEFAULT_END \
    init_case_end(__LINE__);

/* trace related macros */

/*
///<macro name="TRACE_GROUP_BEGIN" group="Trace macros">
///<param name="_grpname" type="constant">Symbolic name of trace group. 
///For MCU traces, the name must be identical to a group defintion in <b>mon_grp.ti</b>.
///</param>
///<param name="_dectext" type="string">Group part of trace name. 
///Typically, the name is <b>"XXX:/"</b>.</param>
///<param name="_state" type="boolean">Flag enabling/disabling the trace group on compile time. 
///<br/><br/>
///For MCU traces, the flag name should be on the format <b>TRACE_I?F_XXX</b>, where <b>?</b> is <b>C</b> (coresw), 
///<b>U</b> (MAUI) or <b>P</b> (protocols), and the flag should default to <b>ON</b> or <b>OFF</b> in the top of the .ti file 
///depending on the importance of the trace group.
///</param>
///<summary>
///Starts a trace group definition.
///</summary>
///<remarks>
///For MCU traces, the macro replaces the former <b>MON_TRACE_ID_TBL_BEGIN</b> macro 
///as part of the <see cref_subtopic="New MCU trace concept"/>. 
///Eventually, <b>mon_grp.ti</b> will be obsolete, 
///and MCU trace group configuration in products will be done based on use of this macro entirely. 
///<br/><br/>
///The actual traces in the group must be defined as before using the 
///<see cref_macro="TRACE_ID"/> or <see cref_macro="TRACE_BEGIN"/> macros.
///<br/><br/>
///Example of an MCU trace group definition in a .ti file:
///<code filename="mcu_trace_group_begin_macro.txt"/>
///The trace in the group is decoded the following way with PMD (compact decoding):
///<code filename="mcu_trace_group_begin_pmd.txt"/>
///For more MCU trace examples, see <see cref_example="Template file for MCU traces"/> and <see cref_subtopic="Adding traces to a component"/>.
///<br/><br/>
///For a general description of this macro, see <see cref_topic="General trace structure"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_IDENTIFIER"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="TRACE_GROUP_END"/>
///<seealso cref_macro="TRACE_ID"/>
///<seealso cref_macro="TRACE_BEGIN"/>
///</macro>
*/
#ifdef AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
 #undef  TRACE_GROUP_BEGIN
 #define TRACE_GROUP_BEGIN(_grpname, _dectext, _state) \
     init_trace_group_begin(__LINE__, #_grpname, _grpname, _state, _dectext, "TRACE_GROUP_BEGIN");
#else
 #undef  TRACE_GROUP_BEGIN
 #define TRACE_GROUP_BEGIN(_grpname, _dectext, _state) \
     init_trace_group_begin(__LINE__, #_grpname, AUTOGEN_TRACE_GROUP_ID_UNDEFINED, _state, _dectext, "TRACE_GROUP_BEGIN");
#endif
/*
///<macro name="TRACE_GROUP_END" group="Trace macros">
///<summary>Ends a trace group definition.</summary>
///<seealso cref_macro="TRACE_GROUP_BEGIN"/>
///</macro>
*/
#undef  TRACE_GROUP_END
#define TRACE_GROUP_END() \
    init_trace_group_end(__LINE__);

/*
///<macro name="TRACE_GROUP_DECODER" group="Trace macros">
///<param name="_grpname" type="constant">Symbolic name of trace group.</param>
///<param name="_dllname" type="constant">Name of decode DLL.</param>
///<param name="_dllfunc" type="constant">Name of function in DLL.</param>
///<param name="_flags" type="E_BLOCK_DLL_FLAGS">Flags.</param>
///<param name="_state" type="boolean">Flag enabling/disabling the trace group on compile time. 
///<br/><br/>
///For MCU traces, the flag name should be on the format <b>TRACE_I?F_XXX</b>, where <b>?</b> is <b>C</b> (coresw), 
///<b>U</b> (MAUI) or <b>P</b> (protocols), and the flag should default to <b>ON</b> or <b>OFF</b> in the top of the .ti file 
///depending on the importance of the trace group.
///</param>
///<summary>
///Defines that all traces belonging to the given trace group are forwarded to an external decode module (DLL).
///</summary>
///<remarks>
///For MCU traces, this macro replaces the macro <b>MON_TRACE_DEFINE_GROUP_DECODER</b>.
///<br/><br/>
///For more information on MCU traces, see <see cref_topic="MCU traces"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///</macro>
*/
#ifdef AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
 #undef  TRACE_GROUP_DECODER
 #define TRACE_GROUP_DECODER(_grpname, _dllname, _dllfunc, _flags, _state) \
     init_trace_group_decoder(__LINE__, #_grpname, _grpname, _state, _dllname, _dllfunc, _flags);
#else
 #undef  TRACE_GROUP_DECODER
 #define TRACE_GROUP_DECODER(_grpname, _dllname, _dllfunc, _flags, _state) \
     init_trace_group_decoder(__LINE__, #_grpname, AUTOGEN_TRACE_GROUP_ID_UNDEFINED, _state, _dllname, _dllfunc, _flags);
#endif

/*
///<macro name="TRACE_BEGIN" group="Trace macros">
///<param name="_trcname" type="constant">Symbolic name of trace, the actual trace ID</param>
///<param name="_dectext" type="string">Text to be presented when decoding the trace</param>
///<summary>Starts a trace definition in a trace group.</summary>
///<remarks>
///For MCU traces, this macro replaces the macro <b>MON_TRACE_DEFINE_ID_BEGIN</b>.
///<br/><br/>
///The macro is to be used when the trace contains data. 
///If the trace contains no data, the macro <see cref_macro="TRACE_ID"/> should be used instead.
///<br/><br/>
///For a general description of this macro, see <see cref_topic="General trace structure"/>.
///<br/><br/>
///For MCU trace examples, see <see cref_example="Template file for MCU traces"/> and <see cref_subtopic="Adding traces to a component"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_8"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_16"/>
///<propertyref cref_property="PROPERTY_ISIHDR_DONT_GENERATE_ID"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE"/>
///<propertyref cref_property="PROPERTY_ISIHDR_STRUCT_NAME"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_IDENTIFIER"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="TRACE_END"/>
///<seealso cref_macro="TRACE_ID"/>
///<seealso cref_macro="TRACE_GROUP_BEGIN"/>
///</macro>
*/
#ifdef AUTOGEN_TRACES_HAVE_FIXED_IDS
 #undef  TRACE_BEGIN
 #define TRACE_BEGIN(_trcname, _dectext) \
     init_trace_begin(__LINE__, #_trcname, _trcname, _dectext, NULL, TRUE, "TRACE_BEGIN");
#else
 #undef  TRACE_BEGIN
 #define TRACE_BEGIN(_trcname, _dectext) \
     init_trace_begin(__LINE__, #_trcname, AUTOGEN_TRACE_ID_UNDEFINED, _dectext, NULL, TRUE, "TRACE_BEGIN");
#endif

/*
///<macro name="TRACE_END" group="Trace macros">
///<summary>Ends a trace definition in a trace group.</summary>
///<seealso cref_macro="TRACE_BEGIN"/>
///</macro>
*/
#undef  TRACE_END
#define TRACE_END() \
    init_trace_end(__LINE__);

/*
///<macro name="TRACE_ID" group="Trace macros">
///<param name="_trcname" type="constant">Name of trace (symbolic name).</param>
///<param name="_dectext" type="string">Name of trace (text to print when decoding trace).</param>
///<summary>Defines a trace, containing no data, to a trace group.</summary>
///<remarks>
///For MCU traces, this macro replaces the former macro <b>MON_TRACE_DEFINE_ID</b> as part 
///of the <see cref_subtopic="New MCU trace concept"/>.
///<br/><br/>
///MCU trace examples: <see cref_example="Template file for MCU traces"/> and <see cref_subtopic="Adding traces to a component"/>.
///<br/><br/>
///A general description of this macro can be found here: <see cref_topic="General trace structure"/>.
///</remarks>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_IN_SUMMARY"/>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="TRACE_BEGIN"/>
///</macro>
*/
#ifdef AUTOGEN_TRACES_HAVE_FIXED_IDS
 #undef  TRACE_ID
 #define TRACE_ID(_trcname, _dectext) \
     init_trace_begin(__LINE__, #_trcname, _trcname, _dectext, NULL, FALSE, "TRACE_ID");
#else
 #undef  TRACE_ID
 #define TRACE_ID(_trcname, _dectext) \
     init_trace_begin(__LINE__, #_trcname, AUTOGEN_TRACE_ID_UNDEFINED, _dectext, NULL, FALSE, "TRACE_ID");
#endif

/* feature flag macros */

/*
///<macro name="FEATURE_FLAG_DEFINED" group="Feature flag macros">
///<param name="_flagname" type="string">Name of flag.</param>
///<param name="_value" type="string">Value (value to compare value of flag against).</param>
///<summary>Compiles only the code under the feature flag if flag has the specified value</summary>
///<remarks>
///This macro enables conditional compilation of the macro file. If the flag has the specified value then section 
///under flag will be compiled.<br/><br/>
///Example of feature flag.
///<code filename="featureflag_ex_if-flag.txt"/>
///The generated ISI header file will look like this:
///<code filename="featureflag_ex_if-flag-isi.txt"/><br/>
///A specicial construction allows autogen to generate #ifdef and #ifndef. To generate these the flag must be
///prepended with the string <b>AUTOGEN_</b> and the value must be <b>ON</b> to generate a #ifdef and it must be
///<b>OFF</b> to generate a #ifndef. The following shows an example of usage.
///<code filename="featureflag_ex_if-def-flag.txt"/>
///The generated ISI header file will look like this:
///<code filename="featureflag_ex_if-def-flag-isi.txt"/>
///</remarks>
///<seealso cref_macro="FEATURE_FLAG_DEFINED_OR_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_DEFINED_AND_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_ELSE"/>
///<seealso cref_macro="FEATURE_FLAG_END"/>
///</macro>
*/
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #undef FEATURE_FLAG_DEFINED
 #define FEATURE_FLAG_DEFINED(_flag, _value) \
 init_feature_flag_begin(__LINE__, #_flag, #_value);
#else
 #undef FEATURE_FLAG_DEFINED
 #define FEATURE_FLAG_DEFINED(_flag, _value) \
    if (_flag == _value){
#endif

/*
///<macro name="FEATURE_FLAG_DEFINED_OR_DEFINED" group="Feature flag macros">
///<param name="_flagname1" type="string">Name of first flag.</param>
///<param name="_value1" type="string">Value (value to compare value of first flag against).</param>
///<param name="_flagname2" type="string">Name of second flag.</param>
///<param name="_value2" type="string">Value (value to compare value of second flag against).</param>
///<summary>Compiles only the code under the feature flag if either of the two flags is equal to the corresponding value.</summary>
///<remarks>
///This macro enables conditional compilation of the macro file. If either the first flag is equal to the corresponding 
///value or the second flag is equal to the second value then the section under flag will be compiled.<br/><br/>
///Example of feature flag.
///<code filename="featureflag_ex_if-flag-or-flag.txt"/>
///The generated ISI header file will look like this:
///<code filename="featureflag_ex_if-flag-or-flag-isi.txt"/><br/>
///</remarks>
///<seealso cref_macro="FEATURE_FLAG_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_DEFINED_AND_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_ELSE"/>
///<seealso cref_macro="FEATURE_FLAG_END"/>
///</macro>
*/
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #undef FEATURE_FLAG_DEFINED_OR_DEFINED
 #define FEATURE_FLAG_DEFINED_OR_DEFINED(_flag1, _value1, _flag2, _value2) \
    init_feature_flag_or_flag_begin(__LINE__, #_flag1, #_value1, #_flag2, #_value2);
#else
 #undef FEATURE_FLAG_DEFINED_OR_DEFINED
 #define FEATURE_FLAG_DEFINED_OR_DEFINED(_flag1, _value1, _flag2, _value2) \
    if ((_flag1 == _value1) || (_flag2 == _value2)){
#endif

/*
///<macro name="FEATURE_FLAG_DEFINED_AND_DEFINED" group="Feature flag macros">
///<param name="_flagname1" type="string">Name of first flag.</param>
///<param name="_value1" type="string">Value (value to compare value of first flag against).</param>
///<param name="_flagname2" type="string">Name of second flag.</param>
///<param name="_value2" type="string">Value (value to compare value of second flag against).</param>
///<summary>Compiles only the code under the feature flag if both of the two flags is equal to the corresponding value.</summary>
///<remarks>
///This macro enables conditional compilation of the macro file. If both the first flag and the second flag is equal to 
///the corresponding value then the section under flag will be compiled.<br/><br/>
///Example of feature flag.
///<code filename="featureflag_ex_if-flag-and-flag.txt"/>
///The generated ISI header file will look like this:
///<code filename="featureflag_ex_if-flag-and-flag-isi.txt"/><br/>
///</remarks>
///<seealso cref_macro="FEATURE_FLAG_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_DEFINED_OR_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_ELSE"/>
///<seealso cref_macro="FEATURE_FLAG_END"/>
///</macro>
*/
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #undef FEATURE_FLAG_DEFINED_AND_DEFINED
 #define FEATURE_FLAG_DEFINED_AND_DEFINED(_flag1, _value1, _flag2, _value2) \
    init_feature_flag_and_flag_begin(__LINE__, #_flag1, #_value1, #_flag2, #_value2);
#else
 #undef FEATURE_FLAG_DEFINED_AND_DEFINED
 #define FEATURE_FLAG_DEFINED_AND_DEFINED(_flag1, _value1, _flag2, _value2) \
    if ((_flag1 == _value1) && (_flag2 == _value2)){
#endif

/*
///<macro name="FEATURE_FLAG_ELSE" group="Feature flag macros">
///<summary>Else part of a feature flag.</summary>
///<remarks>
///Example of feature flag.
///<code filename="featureflag_ex_if-flag-else.txt"/>
///The generated ISI header file will look like this:
///<code filename="featureflag_ex_if-flag-else-isi.txt"/><br/>
///</remarks>
///<seealso cref_macro="FEATURE_FLAG_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_DEFINED_OR_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_DEFINED_AND_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_END"/>
///</macro>
*/
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #undef FEATURE_FLAG_ELSE
 #define FEATURE_FLAG_ELSE() \
    init_feature_flag_else(__LINE__);
#else
 #undef FEATURE_FLAG_ELSE
 #define FEATURE_FLAG_ELSE() \
    }else{
#endif

/*
///<macro name="FEATURE_FLAG_END" group="Feature flag macros">
///<summary>End of a feature flag.</summary>
///<seealso cref_macro="FEATURE_FLAG_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_DEFINED_OR_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_DEFINED_AND_DEFINED"/>
///<seealso cref_macro="FEATURE_FLAG_ELSE"/>
///</macro>
*/
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #undef FEATURE_FLAG_END
 #define FEATURE_FLAG_END() \
    init_feature_flag_end(__LINE__);
#else
 #undef FEATURE_FLAG_END
 #define FEATURE_FLAG_END() \
    }
#endif


/* miscellaneous macros */

/*
///<macro name="COMMENT" group="Comment macros">
///<param name="_type" type="E_COMMENT_TYPE">Type of the comment</param>
///<param name="_comment" type="string">The actual comment text</param>
///<summary>Defines a comment to an object.</summary>
///<remarks>These macros are used to specify various kinds of comments.<br/>
///They must be placed before the object that they are commenting.
///</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="COMMENT_LINK"/>
///<seealso cref_macro="COMMENT_PROPERTY"/>
///</macro>
*/
#undef  COMMENT
#ifdef  AUTOGEN_FORMAT_L1NUTS
 #define COMMENT(_comment, _type) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_ITEM, _type, _comment, TRUE);
#else
 #ifdef AUTOGEN_ENVIRONMENT_LOCAL
  #define COMMENT(_type, _comment) \
    init_comment(__LINE__, _type, _comment);
 #else
  #define COMMENT(_type, _comment)
 #endif  /* AUTOGEN_ENVIRONMENT_LOCAL */
#endif /* AUTOGEN_FORMAT_L1NUTS */

/*
///<macro name="COMMENT_LINK" group="Comment macros">
///<param name="_type" type="E_COMMENT_LINK_TYPE">Type of object to link to.</param>
///<param name="_name" type="string">Name of the object.</param>
///<param name="_subname" type="string">Sub name of the object (only used for sub messages, else leave as empty "").</param>
///<param name="_ver" type="string">ISI version of object (or "" for any).</param>
///<summary>Adds a link to a comment definition for a resource, table or sequence/message/sub block definition.</summary>
///<remarks>These macros are used to specify various kinds of comments.<br/>
///They must be placed before the object that they are commenting.</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="COMMENT"/>
///<seealso cref_macro="COMMENT_PROPERTY"/>
///</macro>
*/
#undef  COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
#define COMMENT_LINK(_type, _name, _subname, _ver) \
    init_comment_link(__LINE__, _type, _name, _subname, _ver);
#else
#define COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

/*
///<macro name="COMMENT_PROPERTY" group="Comment macros">
///<param name="_type" type="E_COMMENT_PROPERTY_TYPE">Comment property type.</param>
///<summary>Adds a property to the comment.</summary>
///<remarks>
///Such properties are used to control which parts of the comment appear in which outputs.
///<br/>
///The ordering of the comment properties with respect to the comments is thus quite significant. 
///</remarks>
///<seealso cref_macro="COMMENT"/>
///<seealso cref_macro="COMMENT_LINK"/>
///</macro>
*/
#undef  COMMENT_PROPERTY
#define COMMENT_PROPERTY(_type) \
    init_comment_property(__LINE__, _type);

/*
///<macro name="PROPERTY" group="Property macros">
///<param name="_type" type="constant">The property to set</param>
///<summary>This macro sets a property.</summary>
///<remarks>This property must be placed before the object that it is to affect.</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="PROPERTY_STRING"/>
///<seealso cref_macro="PROPERTY_STRING_INDEX"/>
///<seealso cref_macro="PROPERTY_VALUE"/>
///<seealso cref_macro="PROPERTY_VALUE_INDEX"/>
///</macro>
*/
#undef  PROPERTY
#define PROPERTY(_type) \
    init_property(__LINE__, _type);

/*
///<macro name="PROPERTY_STRING" group="Property macros">
///<param name="_type" type="constant">The property to set.</param>
///<param name="_value" type="string">The string value to set the property to.</param>
///<summary>This macro sets a string property.</summary>
///<remarks>This property must be placed before the object that it is to affect.</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="PROPERTY"/>
///<seealso cref_macro="PROPERTY_STRING_INDEX"/>
///<seealso cref_macro="PROPERTY_VALUE"/>
///<seealso cref_macro="PROPERTY_VALUE_INDEX"/>
///</macro>
*/
#undef  PROPERTY_STRING
#define PROPERTY_STRING(_type, _value) \
    init_property_string(__LINE__, _type, _value);

/*
///<macro name="PROPERTY_STRING_INDEX" group="Property macros">
///<param name="_type" type="constant">The property to set.</param>
///<param name="_index" type="constant">The index to set the string for. 
///Each index can only be set once for a given property on a given object.</param>
///<param name="_value" type="string">The string value to set the given index of the property to.</param>
///<summary>This macro sets an indexed string property.</summary>
///<remarks>This property must be placed before the object that it is to affect.</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="PROPERTY"/>
///<seealso cref_macro="PROPERTY_STRING"/>
///<seealso cref_macro="PROPERTY_VALUE"/>
///<seealso cref_macro="PROPERTY_VALUE_INDEX"/>
///</macro>
*/
#undef  PROPERTY_STRING_INDEX
#define PROPERTY_STRING_INDEX(_type, _index, _value) \
    init_property_string_index(__LINE__, _type, _index, _value);

/*
///<macro name="PROPERTY_VALUE" group="Property macros">
///<param name="_type" type="constant">The property to set.</param>
///<param name="_value" type="constant">The value to set the property to.</param>
///<summary>This macro sets a value property.</summary>
///<remarks>This property must be placed before the object that it is to affect.</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="PROPERTY"/>
///<seealso cref_macro="PROPERTY_STRING"/>
///<seealso cref_macro="PROPERTY_STRING_INDEX"/>
///<seealso cref_macro="PROPERTY_VALUE_INDEX"/>
///</macro>
*/
#undef  PROPERTY_VALUE
#if (PMD_FILE_FORMAT >= 600)
#define PROPERTY_VALUE(_type, _value) \
    init_property_value(__LINE__, _type, (unsigned long long)_value, _value<0, #_value);
#else
#define PROPERTY_VALUE(_type, _value) \
    init_property_value(__LINE__, _type, (unsigned int)_value, _value<0, #_value);
#endif

/*
///<macro name="PROPERTY_VALUE_INDEX" group="Property macros">
///<param name="_type" type="constant">The property to set</param>
///<param name="_index" type="constant">The index to set the value for. 
///Each index can only be set once for a given property on a given object.</param>
///<param name="_value" type="constant">The value to set the given index of the property to.</param>
///<summary>This macro sets a value property.</summary>
///<remarks>This property must be placed before the object that it is to affect.</remarks>
///<propertyref cref_property="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS"/>
///<seealso cref_macro="PROPERTY"/>
///<seealso cref_macro="PROPERTY_STRING"/>
///<seealso cref_macro="PROPERTY_STRING_INDEX"/>
///<seealso cref_macro="PROPERTY_VALUE"/>
///</macro>
*/
#undef  PROPERTY_VALUE_INDEX
#if (PMD_FILE_FORMAT >= 600)
#define PROPERTY_VALUE_INDEX(_type, _index, _value) \
    init_property_value_index(__LINE__, _type, _index, (unsigned long long)_value, _value<0, #_value);
#else
#define PROPERTY_VALUE_INDEX(_type, _index, _value) \
    init_property_value_index(__LINE__, _type, _index, (unsigned int)_value, _value<0, #_value);
#endif

    
/* ============================================================================================= */
/* Short-cut message macros */
/* ============================================================================================= */

/*
///<macro name="COMMON_MSG_HDR" group="Message macros">
///<summary>This macro defines the transaction ID and message ID that every ISI message contain.</summary>
///<remarks>The macro can be used as first macro within a message definition, 
///see <see cref_macro="MSG_BEGIN"/>. See also <see cref_macro="MSG_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="COMMON_SUB_MSG_HDR"/>
///</macro>
*/
#undef  COMMON_MSG_HDR
#define COMMON_MSG_HDR \
    VALUE(8, BE, trans_id, "Transaction ID", DEC) \
    REFERENCE(8, BE, message_id, "Message ID", MSG_ID)

/*
///<macro name="COMMON_SUB_MSG_HDR" group="Message macros">
///<summary>This macro defines the transaction ID, message ID ans sub message ID that every ISI sub message contain.</summary>
///<remarks>The macro can be used as first macro within a message definition, 
///see <see cref_macro="SUB_MSG_BEGIN"/>. See also <see cref_macro="SUB_MSG_BEGIN"/> for an example of using this macro.
///</remarks>
///<seealso cref_macro="COMMON_MSG_HDR"/>
///</macro>
*/
#undef  COMMON_SUB_MSG_HDR
#define COMMON_SUB_MSG_HDR \
    COMMON_MSG_HDR \
    REFERENCE(8, BE, sub_message_id, "Sub Message ID", SUB_MSG_ID)

/*
///<macro name="COMMON_PREFIX_MSG_HDR" group="Message macros">
///<summary>This macro defines the transaction ID, message ID and 16-bit resource ID that every ISI message using <b>PN_PREFIX</b> contain.</summary>
///<remarks>The macro can be used as first macro within a message definition, 
///see <see cref_macro="MSG_BEGIN"/>.
///</remarks>
///</macro>
*/
#undef  COMMON_PREFIX_MSG_HDR
#define COMMON_PREFIX_MSG_HDR \
    COMMON_MSG_HDR \
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF_16, "    /* Declaration to be split into type and sub_type and used in 8-bit header file") \
    PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "sub_type") \
    COMMENT(COMMENT_ISIHDR_AFTER_DEF_16, "    xxxxxxxx--------  type") \
    COMMENT(COMMENT_ISIHDR_AFTER_DEF_16, "    --------xxxxxxxx  sub_type") \
    COMMENT(COMMENT_ISIHDR_AFTER_DEF_16, "    */ ") \
    COMMENT(COMMENT_ISIHDR_AFTER_DEF_16, "    uint16  type_and_sub_type;  /* Part of extended resource */" ) \
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY) \
    COMMENT(COMMENT_TEXT, "Type | Sub type") \
    REFERENCE(16, BE, type, "Resource ID", RESOURCE_ID)

/*
///<macro name="COMMON_PREFIX_SUB_MSG_HDR" group="Message macros">
///<summary>This macro defines the transaction ID, message ID, 16-bit resource ID that every ISI message using <b>PN_PREFIX</b> contain. 
///Besides, it defines a sub message ID</summary>
///<remarks>The macro can be used as first macro within a message definition, 
///see <see cref_macro="MSG_BEGIN"/>.
///</remarks>
///</macro>
*/
#undef  COMMON_PREFIX_SUB_MSG_HDR
#define COMMON_PREFIX_SUB_MSG_HDR \
    COMMON_PREFIX_MSG_HDR \
    REFERENCE(8, BE, sub_message_id, "Sub Message ID", SUB_MSG_ID)

/*
///<macro name="COMMON_SB" group="Sub block macros">
///<summary>
///This macro defines the two 8-bit fields, sub block ID and sub block length, 
///which most sub blocks start with.
///</summary>
///<remarks>
///For other size combinations of ID and length field, refer to the macro variants in the see also section.
///</remarks>
///<seealso cref_macro="COMMON_SB_LONG"/>
///<seealso cref_macro="COMMON_SB_16"/>
///<seealso cref_macro="COMMON_SB_16_LONG"/>
///</macro>
*/
#undef  COMMON_SB
#define COMMON_SB \
    REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, sb_len, "Sub Block Length", SB_LENGTH) 

/*
///<macro name="COMMON_SB_LONG" group="Sub block macros">
///<summary>This macro defines an 8-bit sub block ID, an 8-bit filler, and a 16-bit sub block length.</summary>
///<remarks>
///For other size combinations of ID and length field, refer to the macro variants in the see also section.
///</remarks>
///<seealso cref_macro="COMMON_SB"/>
///<seealso cref_macro="COMMON_SB_16"/>
///<seealso cref_macro="COMMON_SB_16_LONG"/>
///</macro>
*/
#undef  COMMON_SB_LONG
#define COMMON_SB_LONG \
    REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID) \
    FILLER(FILLER_FIXED, 8) \
    REFERENCE(16, BE, sb_len, "Sub Block Length", SB_LENGTH)

/*
///<macro name="COMMON_SB_16" group="Sub block macros">
///<summary>This macro defines a 16-bit sub block ID and an 8-bit sub block length.</summary>
///<remarks>
///For other size combinations of ID and length field, refer to the macro variants in the see also section.
///</remarks>
///<seealso cref_macro="COMMON_SB"/>
///<seealso cref_macro="COMMON_SB_LONG"/>
///<seealso cref_macro="COMMON_SB_16_LONG"/>
///</macro>
*/
#undef  COMMON_SB_16
#define COMMON_SB_16 \
    REFERENCE(16, BE, sb_id, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, sb_len, "Sub Block Length", SB_LENGTH) 

/*
///<macro name="COMMON_SB_16_LONG" group="Sub block macros">
///<summary>This macro defines two 16-bit fields, sub block ID and sub block length.</summary>
///<remarks>
///For other size combinations of ID and length field, refer to the macro variants in the see also section.
///</remarks>
///<seealso cref_macro="COMMON_SB"/>
///<seealso cref_macro="COMMON_SB_LONG"/>
///<seealso cref_macro="COMMON_SB_16"/>
///</macro>
*/
#undef  COMMON_SB_16_LONG
#define COMMON_SB_16_LONG \
    REFERENCE(16, BE, sb_id, "Sub Block ID", SB_ID) \
    REFERENCE(16, BE, sb_len, "Sub Block Length", SB_LENGTH)

/*
///<macro name="STI_TRACE_BEGIN" group="Trace macros">
///<to_be_documented_later/>
///<param name="_traceid" type=""></param>
///<summary></summary>
///<propertyref cref_property="PROPERTY_HTML_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_DONT_GENERATE"/>
///<propertyref cref_property="PROPERTY_PMD_TRACE_IN_SUMMARY"/>
///</macro>
*/
#undef  STI_TRACE_BEGIN
#define STI_TRACE_BEGIN(_traceid) \
    init_sub_msg_begin(__LINE__, _traceid, #_traceid, g_sti_trace_id, g_sti_trace_name, MESSAGE_TRACE, "", "", NULL); \
    VALUE(8, BE, transaction_id, "Transaction ID", DEC) \
    REFERENCE(8, BE, group_id, "Group ID", MSG_ID) \
    REFERENCE(8, BE, trace_id, "Trace ID", SUB_MSG_ID) \
    FILLER(FILLER_FIXED, 8) \
    TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)

/*
///<macro name="STI_TRACE_END" group="Trace macros">
///<to_be_documented_later/>
///<summary></summary>
///<remarks></remarks>
///</macro>
*/
#undef  STI_TRACE_END
#define STI_TRACE_END \
    init_sub_msg_end(__LINE__);


/* ============================================================================================= */
/* L1NUTS additions */
/* ============================================================================================= */

#undef  COMMON_ISI_HDR_16 
#define COMMON_ISI_HDR_16 \
    MERGE_BEGIN(16, BE, media_dev, "1st word of PhoNet header") \
        VALUE(8, BE, media, "Media from pn_const.h", HEX) \
        VALUE(8, BE, receiver_dev, "Receiver device from pn_const.h", HEX) \
    MERGE_END \
    MERGE_BEGIN(16, BE, dev_res, "2nd word of PhoNet header") \
        VALUE(8, BE, sender_dev, "Sender device from pn_const.h", HEX) \
        /* 'sender' is forbidden name in SDL */ \
        VALUE(8, BE, resource, "Resource for msg ID's, pn_const.h", HEX) \
    MERGE_END \
    VALUE(16, BE, length, "Length of msg in bytes beginning from rec. obj.", DEC) \
    MERGE_BEGIN(16, BE, obj, "ISI header") \
        VALUE(8, BE, receiver_obj, "Receiver object, product specific config", HEX) \
        VALUE(8, BE, sender_obj, "Sender object, product specific config", HEX) \
    MERGE_END
  
#undef  COMMON_ISI_HDR_16_REF 
#define COMMON_ISI_HDR_16_REF \
    MERGE_BEGIN(16, BE, media_dev, "1st word of PhoNet header") \
        VALUE(8, BE, media, "Media from pn_const.h", HEX) \
        VALUE(8, BE, receiver_dev, "Receiver device from pn_const.h", HEX) \
    MERGE_END \
    MERGE_BEGIN(16, BE, dev_res, "2nd word of PhoNet header") \
        VALUE(8, BE, sender_dev, "Sender device from pn_const.h", HEX) \
        /* 'sender' is forbidden name in SDL */ \
        VALUE(8, BE, resource, "Resource for msg ID's, pn_const.h", HEX) \
    MERGE_END \
    REFERENCE(16, BE, length, "Ref:Length of msg in bytes beginning from rec.obj.", ISI_LEN) \
    MERGE_BEGIN(16, BE, obj, "ISI header") \
        VALUE(8, BE, receiver_obj, "Receiver object, product specific config", HEX) \
        VALUE(8, BE, sender_obj, "Sender object, product specific config", HEX) \
    MERGE_END

#undef  COMMON_ISI_HDR
#define COMMON_ISI_HDR \
    VALUE(8, BE, media, "Media from pn_const.h", HEX) \
    VALUE(8, BE, receiver_dev, "Receiver device from pn_const.h", HEX) \
    VALUE(8, BE, sender_dev, "Sender device from pn_const.h", HEX) \
    /* 'sender' is forbidden name in SDL */ \
    VALUE(8, BE, resource, "Resource for msg ID's, pn_const.h", HEX) \
    VALUE(16, BE, length, "Length of msg in bytes beginning from rec. obj.", DEC) \
    VALUE(8, BE, receiver_obj, "Receiver object, product specific config", HEX) \
    VALUE(8, BE, sender_obj, "Sender object, product specific config", HEX)

#undef  COMMON_ISI_HDR_REF
#define COMMON_ISI_HDR_REF \
    VALUE(8, BE, media, "Media from pn_const.h", HEX) \
    VALUE(8, BE, receiver_dev, "Receiver device from pn_const.h", HEX) \
    VALUE(8, BE, sender_dev, "Sender device from pn_const.h", HEX) \
    /* 'sender' is forbidden name in SDL */ \
    VALUE(8, BE, resource, "Resource for msg ID's, pn_const.h", HEX) \
    REFERENCE(16, BE, length, "Ref: Length of msg in bytes beginning from rec.obj.", ISI_LEN) \
    VALUE(8, BE, receiver_obj, "Receiver object, product specific config", HEX) \
    VALUE(8, BE, sender_obj, "Sender object, product specific config", HEX)
  
#undef  COMMON_MSG_HDR_16
#define COMMON_MSG_HDR_16 \
    MERGE_BEGIN(16, BE, id, "Message header") \
        COMMON_MSG_HDR \
    MERGE_END

#undef  FILLER_16
#define FILLER_16 \
    MERGE_BEGIN(16, BE, fill_w, "Filler Word") \
        FILLER(FILLER_FIXED, 8) \
        FILLER(FILLER_FIXED, 8) \
    MERGE_END \

#undef  FILLER_16_2
#define FILLER_16_2 \
    MERGE_BEGIN(16, BE, fill_w_2, "2nd Filler Word") \
        FILLER(FILLER_FIXED, 8) \
        FILLER(FILLER_FIXED, 8) \
    MERGE_END
        
#undef  COMMON_MSG_REQ_16
#define COMMON_MSG_REQ_16 \
	COMMON_MSG_HDR_16
	
#undef  COMMON_MSG_RESP_16
#define COMMON_MSG_RESP_16 \
	COMMON_MSG_HDR_16
	
#undef  COMMON_MSG_IND_16
#define COMMON_MSG_IND_16 \
    COMMON_MSG_HDR_16
 
#undef  COMMON_SB_WORD
#define COMMON_SB_WORD \
    MERGE_BEGIN(16, BE, sb_hdr, "General ISI sub block as word") \
        COMMON_SB \
    MERGE_END \

#undef  COMMON_SB_LONG_WORD
#define COMMON_SB_LONG_WORD \
    MERGE_BEGIN(16, BE, sb_hdr_long, "SubBlock header") \
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID) \
        FILLER(FILLER_FIXED, 8) \
    MERGE_END \
    REFERENCE(16, BE, sb_len, "Sub Block Length", SB_LENGTH)

#undef  COMMON_SB_ID16
#define COMMON_SB_ID16 \
    REFERENCE(16, BE, sb_id, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, sb_len, "Sub Block Length", SB_LENGTH) \
    FILLER(FILLER_FIXED, 8)

#undef  COMMON_SB_WORD_ID16
#define COMMON_SB_WORD_ID16 \
    REFERENCE(16, BE, sb_id, "Sub Block ID", SB_ID) \
    MERGE_BEGIN(16, BE, sb_hdr, "Sub block length") \
        REFERENCE(8, BE, sb_len, "Sub Block Length", SB_LENGTH) \
        FILLER(FILLER_FIXED, 8) \
    MERGE_END


/* ============================================================================================= */
/* Internal autogen constants */
/* ============================================================================================= */

/* internal choice macro types */
#define MACRO_CHOICE_BEGIN           0
#define MACRO_CHOICE_VALUE_BEGIN     1
#define MACRO_CHOICE_FORWARD_BEGIN   2

#define MACRO_CASE                  0
#define MACRO_CASE_VER              1
#define MACRO_CASE_DEFAULT          2
#define MACRO_CASE_OLD              3
#define MACRO_CASE_BEGIN            4
#define MACRO_DEFAULT_BEGIN         5

/* internal comment/property targets */
#define AUTOGEN_TARGET_TBLENTRY                 0x00000001U
#define AUTOGEN_TARGET_ITEM                     0x00000002U
#define AUTOGEN_TARGET_CONSTANT                 0x00000004U
#define AUTOGEN_TARGET_VERSION                  0x00000008U
#define AUTOGEN_TARGET_NOTE                     0x00000010U
#define AUTOGEN_TARGET_INCLUDE_SHARED_FILE      0x00000020U
#define AUTOGEN_TARGET_MAIN                     0x00000040U
#define AUTOGEN_TARGET_MSGID                    0x00000080U
#define AUTOGEN_TARGET_TRCIDTBL                 0x00000100U

/* ============================================================================================= */
/* Old constants defined for backward compatibility */
/* ============================================================================================= */

/* old filler types */
#define FIXED_FILLER                            FILLER_FIXED
#define VARIABLE_FILLER                         FILLER_VARIABLE

/* old list types */
#define INSERT_SUBBLOCKS                        LIST_OF_SUBBLOCKS
#define INSERT_IDS                              LIST_OF_SUBBLOCK_IDS

/* old message types */
#define OSMO_TRACE                              OS_TRACE
#define WCDMA_ADSP_TRACE                        ADSP_TRACE
#define AUTOGEN_MSG_TYPE_REQ                    MESSAGE_REQ
#define AUTOGEN_MSG_TYPE_RESP                   MESSAGE_RESP
#define AUTOGEN_MSG_TYPE_IND                    MESSAGE_IND

/* old resource types */
#define AUTOGEN_RES_CMNMSG                      RESOURCE_ISI_COMMON_MESSAGES
#define SERVER_TYPE_ISA                         RESOURCE_ISI
#define SERVER_TYPE_COMMON_MESSAGES             RESOURCE_ISI_COMMON_MESSAGES
#define SERVER_TYPE_MEDIA_CONTROL               RESOURCE_ISI_MEDIA_CONTROL
#define SERVER_TYPE_MM                          RESOURCE_MEDIA_MODULE

/* old string types */
#define NULL_TERMINATION_PRESENT                AUTOGEN_STRING_ZERO_TERMINATED
#define NULL_TERMINATION_NONE                   0
#define ASCII                                   STRING_ASCII
#define UNICODE                                 STRING_UNICODE
#define AS_MANY_AS_POSSIBLE                     0

/* old environment variable types */
#define ENV_CONST_MCU_TRACE_BITMAP_ID           PMD_ENVIRONMENT_VAR_ID_MCU_TRACE_BITMAP_ID
#define ENV_VAR_MCU_TRACE_BITMAP_ID             PMD_ENVIRONMENT_VAR_ID_MCU_TRACE_BITMAP_ID
#define ENV_CONST_MCU_TRACE_BITMAP_LENGTH       PMD_ENVIRONMENT_VAR_ID_MCU_TRACE_BITMAP_LENGTH
#define ENV_VAR_MCU_TRACE_BITMAP_LENGTH         PMD_ENVIRONMENT_VAR_ID_MCU_TRACE_BITMAP_LENGTH
#define ENV_VAR_OS_TICKS_INTERVAL               PMD_ENVIRONMENT_VAR_ID_OS_TIMER_INTERVAL
#define ENV_VAR_MCU_SW_VERSION                  PMD_ENVIRONMENT_VAR_ID_MCU_SW_VERSION
#define ENV_VAR_CDSP_SW_VERSION                 PMD_ENVIRONMENT_VAR_ID_CDSP_SW_VERSION
#define ENV_VAR_ADSP_SW_VERSION                 PMD_ENVIRONMENT_VAR_ID_ADSP_SW_VERSION
#define ENV_VAR_PMD_FILE_TYPE                   PMD_ENVIRONMENT_VAR_ID_PMD_FILE_TYPE

/* old item limit constant */
#define LIMITS_NO_VALUE                         0x00000000


/* ============================================================================================= */
/* Old message macros defined for backward compatibility */
/* ============================================================================================= */

/* old macros related to resource definitions */

#undef  RES_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define RES_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("RES_COMMENT_LINK: Replace macro with COMMENT_LINK macro (and place before RES_BEGIN)"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_MAIN, _type, _name, _subname, _ver);
#else
 #define RES_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_SERVER_BEGIN
#ifdef  AUTOGEN_FORMAT_L1NUTS
 #ifdef  AUTOGEN_ENVIRONMENT_LOCAL
  #define DEFINE_SERVER_BEGIN(_id, _sername, _version, _comment) \
    init_old_macro_used("DEFINE_SERVER_BEGIN: Replace with RES_BEGIN macro"); \
    init_res_begin(__NOKIA_FILE__, __LINE__, RESOURCE_ISI_DSP, _id, #_id, _sername, &#_id[3], _version, TRUE, _comment);
 #else
  #define DEFINE_SERVER_BEGIN(_id, _sername, _version, _comment) \
    init_res_begin(__NOKIA_FILE__, __LINE__, RESOURCE_ISI_DSP, _id, #_id, _sername, &#_id[3], _version, TRUE, NULL);
 #endif
#else
 #ifdef AUTOGEN_ENVIRONMENT_LOCAL
  #define DEFINE_SERVER_BEGIN(_id, _sername, _version, _comment) \
    init_old_macro_used("DEFINE_SERVER_BEGIN: Replace with RES_BEGIN macro"); \
    init_res_begin(__NOKIA_FILE__, __LINE__, RESOURCE_ISI, _id, #_id, _sername, &#_id[3], _version, TRUE, _comment);
 #else
  #define DEFINE_SERVER_BEGIN(_id, _sername, _version, _comment) \
    init_res_begin(__NOKIA_FILE__, __LINE__, RESOURCE_ISI, _id, #_id, _sername, &#_id[3], _version, TRUE, NULL);
 #endif
#endif

#undef  RES_INCLUDE_SHARED_FILE
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define RES_INCLUDE_SHARED_FILE(_id, _verfrom, _verto) \
    init_old_macro_used("RES_INCLUDE_SHARED_FILE: Replace macro with INCLUDE_SHARED_FILE macro"); \
    init_res_include_shared_file(__LINE__, _id, #_id, _verfrom, _verto);
#else
 #define RES_INCLUDE_SHARED_FILE(_id, _verfrom, _verto) \
    init_res_include_shared_file(__LINE__, _id, #_id, _verfrom, _verto);
#endif

#undef  SERVER_SET_COMMON_MESSAGE_SUPPORT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SERVER_SET_COMMON_MESSAGE_SUPPORT(_supports_comm) \
    init_old_macro_used("SERVER_SET_COMMON_MESSAGE_SUPPORT: Obsolete macro. common message support is argument to RES_BEGIN macro"); \
    init_server_set_common_message_support(__LINE__, _supports_comm);
#else
 #define SERVER_SET_COMMON_MESSAGE_SUPPORT(_supports_comm) \
    init_server_set_common_message_support(__LINE__, _supports_comm);
#endif

#undef  SERVER_SET_SHORT_NAME
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SERVER_SET_SHORT_NAME(_name) \
    init_old_macro_used("SERVER_SET_SHORT_NAME: Obsolete macro. Short name is argument to RES_BEGIN macro"); \
    init_server_set_short_name(__LINE__, #_name);
#else
 #define SERVER_SET_SHORT_NAME(_name) \
    init_server_set_short_name(__LINE__, #_name);
#endif

#undef  SERVER_SET_TYPE
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SERVER_SET_TYPE(_type) \
    init_old_macro_used("SERVER_SET_TYPE: Obsolete macro. resource type is argument to RES_BEGIN macro"); \
    init_server_set_type(__LINE__, _type);
#else
 #define SERVER_SET_TYPE(_type) \
    init_server_set_type(__LINE__, _type);
#endif

#undef  RES_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define RES_COMMENT(_type, _comment) \
    init_old_macro_used("RES_COMMENT: Replace macro with COMMENT macro (and place before RES_BEGIN)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define RES_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#endif

#undef  INCLUDE_SHARED_FILE_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define INCLUDE_SHARED_FILE_COMMENT(_type, _comment) \
    init_old_macro_used("INCLUDE_SHARED_FILE_COMMENT: Replace macro with COMMENT macro (and place before INCLUDE_SHARED_FILE)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_INCLUDE_SHARED_FILE, _type, _comment, TRUE);
#else
 #define INCLUDE_SHARED_FILE_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_SERVER_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SERVER_END \
    init_old_macro_used("DEFINE_SERVER_END: Replace with RES_END macro"); \
    init_res_end(__LINE__);
#else
 #define DEFINE_SERVER_END \
    init_res_end(__LINE__);
#endif

/* old macros related to constant definitions */

#undef  CONSTANT_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define CONSTANT_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("CONSTANT_COMMENT_LINK: Replace macro with COMMENT_LINK macro"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_CONSTANT, _type, _name, _subname, _ver);
#else
 #define CONSTANT_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  CONSTANT_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define CONSTANT_COMMENT(_type, _comment) \
    init_old_macro_used("CONSTANT_COMMENT: Replace macro with COMMENT macro"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_CONSTANT, _type, _comment, TRUE);
#else
 #define CONSTANT_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


/* old macros related to constant table definitions */

#undef  CONST_TBL_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define CONST_TBL_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("CONST_TBL_COMMENT_LINK: Replace macro with COMMENT_LINK macro (and place before CONST_TBL_BEGIN)"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_MAIN, _type, _name, _subname, _ver);
#else
 #define CONST_TBL_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  CONST_TBL_ENTRY_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define CONST_TBL_ENTRY_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("CONST_TBL_ENTRY_COMMENT_LINK: Replace macro with COMMENT_LINK macro"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_TBLENTRY, _type, _name, _subname, _ver);
#else
 #define CONST_TBL_ENTRY_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_CONST_TBL_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_CONST_TBL_BEGIN(_name, _length, _order, _comment) \
    init_old_macro_used("DEFINE_CONST_TBL_BEGIN: Replace with CONST_TBL_BEGIN macro"); \
    init_const_tbl_begin(__LINE__, #_name, _length, _order, "", "", _comment);
#else
 #define DEFINE_CONST_TBL_BEGIN(_name, _length, _order, _comment) \
    init_const_tbl_begin(__LINE__, #_name, _length, _order, "", "", _comment);
#endif

#undef  CONST_TBL_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define CONST_TBL_COMMENT(_type, _comment) \
    init_old_macro_used("CONST_TBL_COMMENT: Replace macro with COMMENT macro (and place before CONST_TBL_BEGIN)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define CONST_TBL_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  CONST_TBL_ENTRY_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define CONST_TBL_ENTRY_COMMENT(_type, _comment) \
    init_old_macro_used("CONST_TBL_ENTRYCOMMENT: Replace macro with COMMENT macro"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TBLENTRY, _type, _comment, TRUE);
#else
 #define CONST_TBL_ENTRY_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_CONST_TBL_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_CONST_TBL_END \
    init_old_macro_used("DEFINE_CONST_TBL_END: Replace with CONST_TBL_END macro"); \
    init_const_tbl_end(__LINE__);
#else
 #define DEFINE_CONST_TBL_END \
    init_const_tbl_end(__LINE__);
#endif

/* old macros related to bit table definitions */

#undef  BIT_TBL_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define BIT_TBL_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("BIT_TBL_COMMENT_LINK: Replace macro with COMMENT_LINK macro (and place before BIT_TBL_BEGIN)"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_MAIN, _type, _name, _subname, _ver);
#else
 #define BIT_TBL_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_BIT_TBL_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_BIT_TBL_BEGIN(_name, _length, _order, _comment) \
    init_old_macro_used("DEFINE_BIT_TBL_BEGIN: Replace macro with BIT_TBL_BEGIN macro"); \
    init_bit_tbl_begin(__LINE__, #_name, _length, _order, "", "", _comment);
#else
 #define DEFINE_BIT_TBL_BEGIN(_name, _length, _order, _comment) \
    init_bit_tbl_begin(__LINE__, #_name, _length, _order, "", "", _comment);
#endif

#undef  BIT_TBL_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define BIT_TBL_COMMENT(_type, _comment) \
    init_old_macro_used("BIT_TBL_COMMENT: Replace macro with COMMENT macro (and place before BIT_TBL_BEGIN)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define BIT_TBL_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  BIT_TBL_ENTRY_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define BIT_TBL_ENTRY_COMMENT(_type, _comment) \
    init_old_macro_used("BIT_TBL_ENTRY_COMMENT: Replace macro with COMMENT macro"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TBLENTRY, _type, _comment, TRUE);
#else
 #define BIT_TBL_ENTRY_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_BIT_TBL_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_BIT_TBL_END \
    init_old_macro_used("DEFINE_BIT_TBL_END: Replace macro with BIT_TBL_END macro"); \
    init_bit_tbl_end(__LINE__);
#else
 #define DEFINE_BIT_TBL_END \
    init_bit_tbl_end(__LINE__);
#endif

/* old macros related to FTD table definitions */

#undef  FTD_TBL_ENTRY_CONST
#ifdef  AUTOGEN_FORMAT_L1NUTS
 #ifdef  AUTOGEN_ENVIRONMENT_LOCAL
  #define FTD_TBL_ENTRY_CONST(_name, _id, _tblname, _comment) \
    init_old_macro_used("FTD_TBL_ENTRY_CONST: Replace macro with FTD_VALUE_BEGIN structure"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TBLENTRY, COMMENT_TEXT, _comment, FALSE); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        init_value_const(__LINE__, "data", "Data", #_tblname, NULL); \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
 #else
  #define FTD_TBL_ENTRY_CONST(_name, _id, _tblname, _comment) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        init_value_const(__LINE__, "data", "Data", #_tblname, NULL); \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
 #endif
#else
 #ifdef AUTOGEN_ENVIRONMENT_LOCAL
  #define FTD_TBL_ENTRY_CONST(_name, _id, _tblname, _comment) \
    COMMENT(COMMENT_TEXT, _comment) \
    init_old_macro_used("FTD_TBL_ENTRY_CONST: Replace macro with FTD_VALUE_BEGIN structure"); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        init_value_const(__LINE__, "data", "Data", #_tblname, NULL); \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
 #else
  #define FTD_TBL_ENTRY_CONST(_name, _id, _tblname, _comment) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        init_value_const(__LINE__, "data", "Data", #_tblname, NULL); \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
 #endif
#endif

#undef  FTD_TBL_ENTRY_CONST_VER
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_CONST_VER(_name, _id, _tblname, _verfrom, _verto) \
    init_old_macro_used("FTD_TBL_ENTRY_CONST_VER: Replace macro with FTD_VALUE_BEGIN structure"); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_VALUE, NULL); \
        init_value_const(__LINE__, "data", "Data", #_tblname, NULL); \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
#else
 #define FTD_TBL_ENTRY_CONST_VER(_name, _id, _tblname, _verfrom, _verto) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_VALUE, NULL); \
        init_value_const(__LINE__, "data", "Data", #_tblname, NULL); \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
#endif

#undef  FTD_TBL_ENTRY_STRING
#ifdef  AUTOGEN_FORMAT_L1NUTS
 #ifdef  AUTOGEN_ENVIRONMENT_LOCAL
  #define FTD_TBL_ENTRY_STRING(_name, _id, _unit, _comment) \
    init_old_macro_used("FTD_TBL_ENTRY_STRING: Replace macro with FTD_STRING macro"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TBLENTRY, COMMENT_TEXT, _comment, FALSE); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_STRING, "Data");
 #else
  #define FTD_TBL_ENTRY_STRING(_name, _id, _unit, _comment) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_STRING, "Data");
 #endif
#else
 #ifdef  AUTOGEN_ENVIRONMENT_LOCAL
  #define FTD_TBL_ENTRY_STRING(_name, _id, _unit, _comment) \
    COMMENT(COMMENT_TEXT, _comment) \
    init_old_macro_used("FTD_TBL_ENTRY_STRING: Replace macro with FTD_STRING macro"); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_STRING, "Data");
 #else
  #define FTD_TBL_ENTRY_STRING(_name, _id, _unit, _comment) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_STRING, "Data");
 #endif
#endif

#undef  FTD_TBL_ENTRY_STRING_VER
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_STRING_VER(_name, _id, _unit, _verfrom, _verto) \
    init_old_macro_used("FTD_TBL_ENTRY_STRING_VER: Replace macro with FTD_STRING macro"); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_STRING, "Data");
#else
 #define FTD_TBL_ENTRY_STRING_VER(_name, _id, _unit, _verfrom, _verto) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_STRING, "Data");
#endif

#undef  FTD_TBL_ENTRY_TABLE
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_TABLE(_name, _id, _length, _pres, _unit, _comment) \
    init_old_macro_used("FTD_TBL_ENTRY_TABLE: Replace macro with FTD_TABLE_BEGIN structure"); \
    COMMENT(COMMENT_TEXT, _comment) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_TABLE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_TABLE);
#else
 #define FTD_TBL_ENTRY_TABLE(_name, _id, _length, _pres, _unit, _comment) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_TABLE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_TABLE);
#endif

#undef  FTD_TBL_ENTRY_TABLE_VER
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_TABLE_VER(_name, _id, _length, _pres, _unit, _verfrom, _verto) \
    init_old_macro_used("FTD_TBL_ENTRY_TABLE_VER: Replace macro with FTD_TABLE_BEGIN structure"); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_TABLE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_TABLE);
#else
 #define FTD_TBL_ENTRY_TABLE_VER(_name, _id, _length, _pres, _unit, _verfrom, _verto) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_TABLE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_TABLE);
#endif

#undef  FTD_TBL_ENTRY_TABLE_CONST
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_TABLE_CONST(_name, _id, _tblname) \
    init_old_macro_used("FTD_TBL_ENTRY_TABLE_CONST: Replace macro with FTD_TABLE_BEGIN structure"); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_TABLE, NULL); \
        init_value_const(__LINE__, "data", "Data", #_tblname, NULL); \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_TABLE);
#else
 #define FTD_TBL_ENTRY_TABLE_CONST(_name, _id, _tblname) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_TABLE, NULL); \
        init_value_const(__LINE__, "data", "Data", #_tblname, NULL); \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_TABLE);
#endif

#undef  FTD_TBL_ENTRY_VALUE
#ifdef  AUTOGEN_FORMAT_L1NUTS
 #ifdef  AUTOGEN_ENVIRONMENT_LOCAL
  #define FTD_TBL_ENTRY_VALUE(_name, _id, _length, _pres, _unit, _comment) \
    init_old_macro_used("FTD_TBL_ENTRY_VALUE: Replace macro with FTD_VALUE_BEGIN structure"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TBLENTRY, COMMENT_TEXT, _comment, FALSE); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
 #else
  #define FTD_TBL_ENTRY_VALUE(_name, _id, _length, _pres, _unit, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TBLENTRY, COMMENT_TEXT, _comment, FALSE); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
 #endif
#else
 #ifdef  AUTOGEN_ENVIRONMENT_LOCAL
  #define FTD_TBL_ENTRY_VALUE(_name, _id, _length, _pres, _unit, _comment) \
    init_old_macro_used("FTD_TBL_ENTRY_VALUE: Replace macro with FTD_VALUE_BEGIN structure"); \
    COMMENT(COMMENT_TEXT, _comment) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
 #else
  #define FTD_TBL_ENTRY_VALUE(_name, _id, _length, _pres, _unit, _comment) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
 #endif
#endif

#undef  FTD_TBL_ENTRY_VALUE_VER
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_VALUE_VER(_name, _id, _length, _pres, _unit, _verfrom, _verto) \
    init_old_macro_used("FTD_TBL_ENTRY_VALUE_VER: Replace macro with FTD_VALUE_BEGIN structure"); \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_VALUE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
#else
 #define FTD_TBL_ENTRY_VALUE_VER(_name, _id, _length, _pres, _unit, _verfrom, _verto) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_VALUE, NULL); \
        VALUE_EX(_length, BE, data, "Data", _pres, 1.0, 0.0, _unit) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
#endif

#undef  FTD_TBL_ENTRY_TEST
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_TEST(_name, _id) \
    init_old_macro_used("FTD_TBL_ENTRY_TEST: Replace macro with FTD_VALUE_BEGIN structure"); \
    PROPERTY(PROPERTY_FTD_IS_INPUT_DATA) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        VALUE(32, BE, data, "Data", DEC) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
#else
 #define FTD_TBL_ENTRY_TEST(_name, _id) \
    PROPERTY(PROPERTY_FTD_IS_INPUT_DATA) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, "", "", AUTOGEN_DATA_VALUE, NULL); \
        VALUE(32, BE, data, "Data", DEC) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
#endif

#undef  FTD_TBL_ENTRY_TEST_VER
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_TEST_VER(_name, _id, _verfrom, _verto) \
    init_old_macro_used("FTD_TBL_ENTRY_TEST_VER: Replace macro with FTD_VALUE_BEGIN structure"); \
    PROPERTY(PROPERTY_FTD_IS_INPUT_DATA) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_VALUE, NULL); \
        VALUE(32, BE, data, "Data", DEC) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
#else
 #define FTD_TBL_ENTRY_TEST_VER(_name, _id, _verfrom, _verto) \
    PROPERTY(PROPERTY_FTD_IS_INPUT_DATA) \
    init_ftd_tbl_entry_begin(__LINE__, #_name, _id, _verfrom, _verto, AUTOGEN_DATA_VALUE, NULL); \
        VALUE(32, BE, data, "Data", DEC) \
    init_ftd_tbl_entry_end(__LINE__, AUTOGEN_DATA_VALUE);
#endif

#undef  FTD_TBL_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("FTD_TBL_COMMENT_LINK: Replace macro with COMMENT_LINK macro (and place before FTD_TBL_BEGIN)"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_MAIN, _type, _name, _subname, _ver);
#else
 #define FTD_TBL_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  FTD_TBL_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_COMMENT(_type, _comment) \
    init_old_macro_used("FTB_TBL_COMMENT: Replace macro with COMMENT macro (and place before FTD_TBL_BEGIN)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define FTD_TBL_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  FTD_TBL_ENTRY_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define FTD_TBL_ENTRY_COMMENT(_type, _comment) \
    init_old_macro_used("FTB_TBL_ENTRY_COMMENT: Replace macro with COMMENT macro"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TBLENTRY, _type, _comment, TRUE);
#else
 #define FTD_TBL_ENTRY_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TBLENTRY, _type, _comment, TRUE);
#endif

/* old macros related to ISI version history definitions */

#undef  ISI_VERSION_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define ISI_VERSION_COMMENT(_type, _comment) \
    init_old_macro_used("ISI_VERSION_COMMENT: Actual comment should be defined with COMMENT macro, and properties set with PROPERTY_CHANGE_XXX properties"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_VERSION, _type, _comment, TRUE);
#else
 #define ISI_VERSION_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


/* old macros related to note definitions */

#undef  NOTE_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define NOTE_COMMENT(_type, _comment) \
    init_old_macro_used("NOTE_COMMENT: Replace macro with COMMENT macro"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_NOTE, _type, _comment, TRUE);
#else
 #define NOTE_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


/* old macros related to message definitions */

#undef  MSG_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MSG_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("MSG_COMMENT_LINK: Replace macro with COMMENT_LINK macro (and place before MSG_BEGIN)"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_MAIN, _type, _name, _subname, _ver);
#else
 #define MSG_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  SUB_MSG_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SUB_MSG_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("SUB_MSG_COMMENT_LINK: Replace macro with COMMENT_LINK macro (and place before SUB_MSG_BEGIN)"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_MAIN, _type, _name, _subname, _ver);
#else
 #define SUB_MSG_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_MSG_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_MSG_BEGIN(_id, _verfrom, _verto, _comment) \
    init_old_macro_used("DEFINE_MSG_BEGIN: Replace macro with MSG_BEGIN macro"); \
    init_msg_begin(__LINE__, _id, #_id, MESSAGE_UNKNOWN, _verfrom, _verto, _comment);
#else
 #define DEFINE_MSG_BEGIN(_id, _verfrom, _verto, _comment) \
    init_msg_begin(__LINE__, _id, #_id, MESSAGE_UNKNOWN, _verfrom, _verto, _comment);
#endif

#undef  DEFINE_SUB_MSG_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SUB_MSG_BEGIN(_id, _subid, _verfrom, _verto, _comment) \
    init_old_macro_used("DEFINE_SUB_MSG_BEGIN: Replace macro with SUB_MSG_BEGIN macro"); \
    init_sub_msg_begin(__LINE__, _id, #_id, _subid, #_subid, MESSAGE_UNKNOWN, _verfrom, _verto, _comment);
#else
 #define DEFINE_SUB_MSG_BEGIN(_id, _subid, _verfrom, _verto, _comment) \
    init_sub_msg_begin(__LINE__, _id, #_id, _subid, #_subid, MESSAGE_UNKNOWN, _verfrom, _verto, _comment);
#endif

#undef  MSG_SET_TYPE
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MSG_SET_TYPE(_type) \
    init_old_macro_used("MSG_SET_TYPE: Obsolete macro. Message type is argument to MSG_BEGIN macro"); \
    init_msg_set_type(__LINE__, _type);
#else
 #define MSG_SET_TYPE(_type) \
    init_msg_set_type(__LINE__, _type);
#endif

#undef  MSG_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MSG_COMMENT(_type, _comment) \
    init_old_macro_used("MSG_COMMENT: Replace macro with COMMENT macro (and place before SEQ_BEGIN)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define MSG_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#endif

#undef  MSG_ID_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MSG_ID_COMMENT(_type, _comment) \
    init_old_macro_used("MSG_ID_COMMENT: Replace macro with COMMENT macro (and place before MSG_ID_SECTION)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MSGID, _type, _comment, TRUE);
#else
 #define MSG_ID_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  SUB_MSG_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SUB_MSG_COMMENT(_type, _comment) \
    init_old_macro_used("SUB_MSG_COMMENT: Replace macro with COMMENT macro (and place before SUB_MSG_BEGIN)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define SUB_MSG_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#endif

#undef  DEFINE_MSG_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_MSG_END \
    init_old_macro_used("DEFINE_MSG_END: Replace macro with MSG_END macro"); \
    init_msg_end(__LINE__);
#else
 #define DEFINE_MSG_END \
    init_msg_end(__LINE__);
#endif

#undef  DEFINE_MSG_PAIR
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_MSG_PAIR(_reqmsgname, _respmsgname) \
    init_old_macro_used("DEFINE_MSG_PAIR: Replace macro with (SUB_)MSG_PAIR(_VER) macro"); \
    init_msg_pair(__LINE__, #_reqmsgname, #_respmsgname, NULL, "", "");
#else
 #define DEFINE_MSG_PAIR(_reqmsgname, _respmsgname) \
    init_msg_pair(__LINE__, #_reqmsgname, #_respmsgname, NULL, "", "");
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_SUB_MSG_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SUB_MSG_END \
    init_old_macro_used("DEFINE_SUB_MSG_END: Replace macro with SUB_MSG_END macro"); \
    init_sub_msg_end(__LINE__);
#else
 #define DEFINE_SUB_MSG_END \
    init_sub_msg_end(__LINE__);
#endif

/* old sub block related macros */

#undef  SB_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SB_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("SB_COMMENT_LINK: Replace macro with COMMENT_LINK macro (and place before SB_BEGIN)"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_MAIN, _type, _name, _subname, _ver);
#else
 #define SB_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_SB_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SB_BEGIN(_id, _verfrom, _verto, _comment) \
    init_old_macro_used("DEFINE_SB_BEGIN: Replace macro with SB_BEGIN macro"); \
    init_sb_begin(__LINE__, #_id, _id, _verfrom, _verto, _comment);
#else
 #define DEFINE_SB_BEGIN(_id, _verfrom, _verto, _comment) \
    init_sb_begin(__LINE__, #_id, _id, _verfrom, _verto, NULL);
#endif

#undef  SB_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SB_COMMENT(_type, _comment) \
    init_old_macro_used("SB_COMMENT: Replace macro with COMMENT macro (and place before SEQ_BEGIN)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define SB_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#endif

#undef  DEFINE_SB_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SB_END \
    init_old_macro_used("DEFINE_SB_END: Replace macro with SB_END macro"); \
    init_sb_end(__LINE__);
#else
 #define DEFINE_SB_END \
    init_sb_end(__LINE__);
#endif

#undef  DEFINE_SB_LST_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SB_LST_END \
    init_old_macro_used("DEFINE_SB_LST_END: Replace macro with SB_LST_REF_END macro"); \
    init_sb_lst_end(__LINE__);
#else
 #define DEFINE_SB_LST_END \
    init_sb_lst_end(__LINE__);
#endif

/* old macros related to sequence definitions */

#undef  SEQ_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SEQ_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("SEQ_COMMENT_LINK: Replace macro with COMMENT_LINK macro (and place before SEQ_BEGIN)"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_MAIN, _type, _name, _subname, _ver);
#else
 #define SEQ_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  DEFINE_SEQ_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SEQ_BEGIN(_name, _flag, _comment) \
    init_old_macro_used("DEFINE_SEQ_BEGIN: Macro should be replaced with SEQ_BEGIN macro"); \
    init_seq_begin(__LINE__, #_name, _flag, "", "", _comment);
#else
 #define DEFINE_SEQ_BEGIN(_name, _flag, _comment) \
    init_seq_begin(__LINE__, #_name, _flag, "", "", NULL);
#endif

#undef  SEQ_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SEQ_COMMENT(_type, _comment) \
    init_old_macro_used("SEQ_COMMENT: Replace macro with COMMENT macro (and place before SEQ_BEGIN)"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define SEQ_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#endif

#undef  DEFINE_SEQ_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SEQ_END \
    init_old_macro_used("DEFINE_SEQ_END: Macro should be replaced with SEQ_END macro"); \
    init_seq_end(__LINE__);
#else
 #define DEFINE_SEQ_END \
    init_seq_end(__LINE__);
#endif

/* old macros related to sequence elements */

#undef  ITEM_COMMENT_LINK
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define ITEM_COMMENT_LINK(_type, _name, _subname, _ver) \
    init_old_macro_used("ITEM_COMMENT_LINK: Replace macro with COMMENT_LINK macro"); \
    init_old_comment_link(__LINE__, AUTOGEN_TARGET_ITEM, _type, _name, _subname, _ver);
#else
 #define ITEM_COMMENT_LINK(_type, _name, _subname, _ver)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  ITEM_PARAMETER
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define ITEM_PARAMETER \
    init_old_macro_used("ITEM_PARAMETER: Macro is obsolete and should be removed");
#else
 #define ITEM_PARAMETER \
    init_property(__LINE__, PROPERTY_PMD_PARAMETER);
#endif

#undef  PARAMETER
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define PARAMETER(_name, _desc) \
    init_old_macro_used("PARAMETER: Macro is obsolete and should be removed");
#else
 #define PARAMETER(_name, _desc) \
    init_property(__LINE__, PROPERTY_PMD_PARAMETER);
#endif

#undef  ITEM_LIMITS
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define ITEM_LIMITS(_minval, _maxval, _excval1, _excval2, _excval3) \
    init_old_macro_used("ITEM_LIMITS: Replace macro with PROPERTY_ITEM_XXX_VALUE properties"); \
    init_item_limits(__LINE__, \
       (unsigned int)_minval, _minval<0?TRUE:FALSE, #_minval, \
       (unsigned int)_maxval, _maxval<0?TRUE:FALSE, #_maxval, \
       (unsigned int)_excval1, _excval1<0?TRUE:FALSE, #_excval1, \
       (unsigned int)_excval2, _excval2<0?TRUE:FALSE, #_excval2, \
       (unsigned int)_excval3, _excval3<0?TRUE:FALSE, #_excval3);
#else
 #define ITEM_LIMITS(_minval, _maxval, _excval1, _excval2, _excval3) \
    init_item_limits(__LINE__, \
       (unsigned int)_minval, _minval<0?TRUE:FALSE, #_minval, \
       (unsigned int)_maxval, _maxval<0?TRUE:FALSE, #_maxval, \
       (unsigned int)_excval1, _excval1<0?TRUE:FALSE, #_excval1, \
       (unsigned int)_excval2, _excval2<0?TRUE:FALSE, #_excval2, \
       (unsigned int)_excval3, _excval3<0?TRUE:FALSE, #_excval3);
#endif

#undef  VALUE_LIMITS
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define VALUE_LIMITS(_type, _minval, _maxval, _excval) \
    init_old_macro_used("VALUE_LIMITS: Replace macro with PROPERTY_ITEM_XXX_VALUE properties"); \
    init_item_limits(__LINE__, \
       (unsigned int)_minval, _minval<0?TRUE:FALSE, #_minval, \
       (unsigned int)_maxval, _maxval<0?TRUE:FALSE, #_maxval, \
       (unsigned int)_excval, _excval<0?TRUE:FALSE, #_excval, \
       (unsigned int)0, FALSE, "LIMITS_NO_VALUE", \
       (unsigned int)0, FALSE, "LIMITS_NO_VALUE");
#else
 #define VALUE_LIMITS(_type, _minval, _maxval, _excval) \
    init_item_limits(__LINE__, \
       (unsigned int)_minval, _minval<0?TRUE:FALSE, #_minval, \
       (unsigned int)_maxval, _maxval<0?TRUE:FALSE, #_maxval, \
       (unsigned int)_excval, _excval<0?TRUE:FALSE, #_excval, \
       (unsigned int)0, FALSE, "LIMITS_NO_VALUE", \
       (unsigned int)0, FALSE, "LIMITS_NO_VALUE");
#endif

#undef  ITEM_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define ITEM_COMMENT(_type, _comment) \
    init_old_macro_used("ITEM_COMMENT: Replace macro with COMMENT macro"); \
    init_old_comment(__LINE__, AUTOGEN_TARGET_ITEM, _type, _comment, TRUE);
#else
 #define ITEM_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_ITEM, _type, _comment, TRUE);
#endif

#undef  ITEM_DEFAULT_VALUE
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define ITEM_DEFAULT_VALUE(_value) \
    init_old_macro_used("ITEM_DEFAULT_VALUE: Replace macro with PROPERTY_ITEM_DEFAULT_VALUE property"); \
    init_property_value(__LINE__, PROPERTY_ITEM_DEFAULT_VALUE, (unsigned int)_value, _value<0, #_value);
#else
 #define ITEM_DEFAULT_VALUE(_value) \
    init_property_value(__LINE__, PROPERTY_ITEM_DEFAULT_VALUE, (unsigned int)_value, _value<0, #_value);
#endif

#undef  PROTOCOL_REF
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define PROTOCOL_REF(_id, _varname, _parname, _refname, _flag) \
    init_old_macro_used("PROTOCOL_REF: Macro should be replaced with BLOCK_REF macro with BLOCK_PROTOCOL as type"); \
    PROPERTY_VALUE(PROPERTY_ISIHDR_ARRAY_MARKER, _flag) \
    BLOCK_REF(BE, _varname, _parname, BLOCK_PROTOCOL, #_id, NULL, 0, _refname)
#else
 #define PROTOCOL_REF(_id, _varname, _parname, _refname, _flag) \
    BLOCK_REF(BE, _varname, _parname, BLOCK_PROTOCOL, #_id, NULL, 0, _refname)
#endif

/* old macros related to merging sequence elements */

#undef  DEFINE_MERGE_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_MERGE_BEGIN(_length, _order, _varname, _parname) \
    init_old_macro_used("DEFINE_MERGE_BEGIN: Replace macro with MERGE_BEGIN macro"); \
    init_merge_begin(__LINE__, _length, _order, #_varname, _parname);
#else
 #define DEFINE_MERGE_BEGIN(_length, _order, _varname, _parname) \
    init_merge_begin(__LINE__, _length, _order, #_varname, _parname);
#endif

#undef  DEFINE_MERGE_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_MERGE_END \
    init_old_macro_used("DEFINE_MERGE_END: Replace macro with MERGE_END macro"); \
    init_merge_end(__LINE__);
#else
 #define DEFINE_MERGE_END \
    init_merge_end(__LINE__);
#endif

/* old macros related to constant sequence elements */

#undef  CONST_REF
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define CONST_REF(_varname, _parname, _tblname) \
    init_old_macro_used("CONST_REF: Replace macro with VALUE_CONST macro"); \
    init_value_const(__LINE__, #_varname, _parname, #_tblname, NULL);
#else
 #define CONST_REF(_varname, _parname, _tblname) \
    init_value_const(__LINE__, #_varname, _parname, #_tblname, NULL);
#endif

#undef  BIT_REF
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define BIT_REF(_varname, _parname, _tblname) \
    init_old_macro_used("BIT_REF: Replace macro with VALUE_CONST macro"); \
    init_value_const(__LINE__, #_varname, _parname, #_tblname, NULL);
#else
 #define BIT_REF(_varname, _parname, _tblname) \
    init_value_const(__LINE__, #_varname, _parname, #_tblname, NULL);
#endif

/* old macros related to sub block list sequence elements */

#undef  DEFINE_SB_LST_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_SB_LST_BEGIN \
    init_old_macro_used("DEFINE_SB_LST_BEGIN: Replace macro with SB_LST_REF_BEGIN macro"); \
    SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", SB_COUNTER, ISIHDR_DONT_GENERATE)
#else
 #define DEFINE_SB_LST_BEGIN \
    SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", SB_COUNTER, ISIHDR_DONT_GENERATE)
#endif

#undef  SB_LST_ENTRY_NAME
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SB_LST_ENTRY_NAME(_varname) \
    init_old_macro_used("SB_LST_ENTRY_NAME: Macro should be replaced with PROPERTY_ISIHDR_DEFINITION_NAME property"); \
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, #_varname)
#else
 #define SB_LST_ENTRY_NAME(_varname)
#endif

/* old macros related to array sequence elements */

#undef  SB_REF
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define SB_REF(_varname, _parname, _sbname) \
    init_old_macro_used("SB_REF: Macro should be replaced with SEQ_OF_REF macro"); \
    init_seq_of(__LINE__, #_varname, _parname, #_sbname, NULL, 0, 1, "1");
#else
 #define SB_REF(_varname, _parname, _sbname) \
    init_seq_of(__LINE__, #_varname, _parname, #_sbname, NULL, 0, 1, "1");
#endif

/* old macros related to choice sequence elements */

#undef  DEFINE_CHOICE_REF_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_CHOICE_REF_BEGIN(_varname, _parname, _refname) \
    init_old_macro_used("DEFINE_CHOICE_REF_BEGIN: Macro should be replaced with CHOICE_VALUE_BEGIN macro"); \
    init_choice_begin(__LINE__, #_varname, _parname, #_refname, NULL, 0, MACRO_CHOICE_VALUE_BEGIN);
#else
 #define DEFINE_CHOICE_REF_BEGIN(_varname, _parname, _refname) \
    init_choice_begin(__LINE__, #_varname, _parname, #_refname, NULL, 0, MACRO_CHOICE_VALUE_BEGIN);
#endif

#undef  DEFINE_CHOICE_REF_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define DEFINE_CHOICE_REF_END \
    init_old_macro_used("DEFINE_CHOICE_REF_END: Macro should be replaced with CHOICE_END macro"); \
    init_choice_end(__LINE__);
#else
 #define DEFINE_CHOICE_REF_END \
    init_choice_end(__LINE__);
#endif

#undef  CASE
#ifdef  AUTOGEN_FORMAT_L1NUTS
 #ifdef  AUTOGEN_ENVIRONMENT_LOCAL
  #define CASE(_tagname, _seqname) \
    init_old_macro_used("CASE: Macro should be replaced with CASE_BEGIN/CASE_END macros"); \
    init_case(__LINE__, "TAG_"#_tagname, _tagname, TRUE, #_seqname, "", "", MACRO_CASE_OLD);
 #else
  #define CASE(_tagname, _seqname) \
    init_case(__LINE__, "TAG_"#_tagname, _tagname, TRUE, #_seqname, "", "", MACRO_CASE_OLD);
 #endif
#else
 #define CASE(_tagname, _seqname) \
    init_case(__LINE__, #_tagname, 0, FALSE, #_seqname, "", "", MACRO_CASE);
#endif

#undef  CASE_VER
#define CASE_VER(_tagname, _seqname, _verfrom, _verto) \
    init_case(__LINE__, #_tagname, 0, FALSE, #_seqname, _verfrom, _verto, MACRO_CASE_VER);

#undef  CASE_DEFAULT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define CASE_DEFAULT(_seqname) \
    init_old_macro_used("CASE_DEFAULT: Macro should be replaced with DEFAULT_BEGIN/DEFAULT_END macros"); \
    init_case(__LINE__, NULL, 0, FALSE, #_seqname, "", "", MACRO_CASE_DEFAULT);
#else
 #define CASE_DEFAULT(_seqname) \
    init_case(__LINE__, NULL, 0, FALSE, #_seqname, "", "", MACRO_CASE_DEFAULT);
#endif


/* old trace related macros */

#undef  MON_TRACE_DEFINE_GROUP_DECODER
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_DEFINE_GROUP_DECODER(_grpname, _dllname, _dllfunc, _flags) \
    init_old_macro_used("MON_TRACE_DEFINE_GROUP_DECODER: Replace macro with TRACE_GROUP_DECODER macro"); \
    init_trace_group_decoder(__LINE__, #_grpname, _grpname, ON, _dllname, _dllfunc, _flags);
#else
 #define MON_TRACE_DEFINE_GROUP_DECODER(_grpname, _dllname, _dllfunc, _flags) \
    init_trace_group_decoder(__LINE__, #_grpname, _grpname, ON, _dllname, _dllfunc, _flags);
#endif

#undef  MON_TRACE_DEFINE_ID_FIXED
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_DEFINE_ID_FIXED(_trcname, _dectext, _func, _grp, _id) \
    init_old_macro_used("MON_TRACE_DEFINE_ID_FIXED: Replace macro with TRACE_BEGIN macro"); \
    init_trace_begin(__LINE__, #_trcname, _id, _dectext, #_grp, FALSE, "MON_TRACE_DEFINE_ID_FIXED");
#else
 #define MON_TRACE_DEFINE_ID_FIXED(_trcname, _dectext, _func, _grp, _id) \
    init_trace_begin(__LINE__, #_trcname, _id, _dectext, #_grp, FALSE, "MON_TRACE_DEFINE_ID_FIXED");
#endif

#undef  MON_TRACE_DEFINE_ID_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_DEFINE_ID_BEGIN(_trcname, _dectext) \
    init_old_macro_used("MON_TRACE_DEFINE_ID_BEGIN: Replace macro with TRACE_BEGIN macro"); \
    init_trace_begin(__LINE__, #_trcname, AUTOGEN_TRACE_ID_UNDEFINED, _dectext, NULL, TRUE, "MON_TRACE_DEFINE_ID_BEGIN");
#else
 #define MON_TRACE_DEFINE_ID_BEGIN(_trcname, _dectext) \
    init_trace_begin(__LINE__, #_trcname, AUTOGEN_TRACE_ID_UNDEFINED, _dectext, NULL, TRUE, "MON_TRACE_DEFINE_ID_BEGIN");
#endif

#undef  MON_TRACE_DEFINE_ID_FIXED_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_DEFINE_ID_FIXED_BEGIN(_trcname, _dectext, _grp, _id) \
    init_old_macro_used("MON_TRACE_DEFINE_ID_FIXED_BEGIN: Replace macro with TRACE_BEGIN macro"); \
    init_trace_begin(__LINE__, #_trcname, _id, _dectext, #_grp, TRUE, "MON_TRACE_DEFINE_ID_FIXED_BEGIN");
#else
 #define MON_TRACE_DEFINE_ID_FIXED_BEGIN(_trcname, _dectext, _grp, _id) \
    init_trace_begin(__LINE__, #_trcname, _id, _dectext, #_grp, TRUE, "MON_TRACE_DEFINE_ID_FIXED_BEGIN");
#endif

#undef  MON_TRACE_DEFINE_ID_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_DEFINE_ID_END() \
    init_old_macro_used("MON_TRACE_DEFINE_ID_END: Replace macro with TRACE_END macro"); \
    init_trace_end(__LINE__);
#else
 #define MON_TRACE_DEFINE_ID_END() \
    init_trace_end(__LINE__);
#endif

#undef  MON_TRACE_ID_TBL_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_ID_TBL_BEGIN(_varname, _grpname) \
    init_old_macro_used("MON_TRACE_ID_TBL_BEGIN: Replace macro with TRACE_GROUP_BEGIN macro"); \
    init_trace_group_begin(__LINE__, #_grpname, _grpname, ON, NULL, "MON_TRACE_ID_TBL_BEGIN");
#else
 #define MON_TRACE_ID_TBL_BEGIN(_varname, _grpname) \
    init_trace_group_begin(__LINE__, #_grpname, _grpname, ON, NULL, "MON_TRACE_ID_TBL_BEGIN");
#endif

#undef  MON_TRACE_ID_TBL_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_ID_TBL_END() \
    init_old_macro_used("MON_TRACE_ID_TBL_END: Replace macro with TRACE_GROUP_END macro"); \
    init_trace_group_end(__LINE__);
#else
 #define MON_TRACE_ID_TBL_END() \
    init_trace_group_end(__LINE__);
#endif

#undef  MON_TRACE_DEFINE_ID
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_DEFINE_ID(_trcname, _dectext, _func) \
    init_old_macro_used("MON_TRACE_DEFINE_ID: Replace macro with TRACE_ID macro"); \
    init_trace_begin(__LINE__, #_trcname, AUTOGEN_TRACE_ID_UNDEFINED, _dectext, NULL, FALSE, "MON_TRACE_DEFINE_ID");
#else
 #define MON_TRACE_DEFINE_ID(_trcname, _dectext, _func) \
    init_trace_begin(__LINE__, #_trcname, AUTOGEN_TRACE_ID_UNDEFINED, _dectext, NULL, FALSE, "MON_TRACE_DEFINE_ID");
#endif

#undef  MCU_TRACE_GROUP_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MCU_TRACE_GROUP_BEGIN(_grpname, _dectext, _state) \
    init_old_macro_used("MCU_TRACE_GROUP_BEGIN: Replace macro with TRACE_GROUP_BEGIN macro"); \
    init_trace_group_begin(__LINE__, #_grpname, _grpname, _state, _dectext, "MCU_TRACE_GROUP_BEGIN");
#else
 #define MCU_TRACE_GROUP_BEGIN(_grpname, _dectext, _state) \
    init_trace_group_begin(__LINE__, #_grpname, _grpname, _state, _dectext, "MCU_TRACE_GROUP_BEGIN");
#endif

#undef  MCU_TRACE_GROUP_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MCU_TRACE_GROUP_END() \
    init_old_macro_used("MCU_TRACE_GROUP_END: Replace macro with TRACE_GROUP_END macro"); \
    init_trace_group_end(__LINE__);
#else
 #define MCU_TRACE_GROUP_END() \
    init_trace_group_end(__LINE__);
#endif

#undef  MON_TRACE_GROUP_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_GROUP_BEGIN(_varname, _grpname, _dectext) \
    init_old_macro_used("MON_TRACE_GROUP_BEGIN: Replace macro with TRACE_GROUP_BEGIN macro"); \
    init_trace_group_begin(__LINE__, #_grpname, _grpname, ON, _dectext, "MON_TRACE_GROUP_BEGIN");
#else
 #define MON_TRACE_GROUP_BEGIN(_varname, _grpname, _dectext) \
    init_trace_group_begin(__LINE__, #_grpname, _grpname, ON, _dectext, "MON_TRACE_GROUP_BEGIN");
#endif

#undef  MON_TRACE_GROUP_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_GROUP_END() \
    init_old_macro_used("MON_TRACE_GROUP_END: Replace macro with TRACE_GROUP_END macro"); \
    init_trace_group_end(__LINE__);
#else
 #define MON_TRACE_GROUP_END() \
    init_trace_group_end(__LINE__);
#endif

#undef  MON_TRACE_ID_TBL_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_ID_TBL_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_TRCIDTBL, _type, _comment, TRUE);
#else
 #define MON_TRACE_ID_TBL_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

#undef  MON_TRACE_ID_COMMENT
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_ID_COMMENT(_type, _comment) \
    init_old_comment(__LINE__, AUTOGEN_TARGET_MAIN, _type, _comment, TRUE);
#else
 #define MON_TRACE_ID_COMMENT(_type, _comment)
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

/* Old L1NUTS additions */

#undef  DEFINE_RANGE_FIELD_BEGIN
#define DEFINE_RANGE_FIELD_BEGIN(_length, _order, _varname, _parname) \
    init_range_begin(__LINE__, _length, _order, #_varname, _parname);

#undef  DEFINE_RANGE_FIELD_END
#define DEFINE_RANGE_FIELD_END \
    init_range_end(__LINE__);

#undef  RANGE_ENTRY_STRING
#define RANGE_ENTRY_STRING(_from, _to, _text) \
    init_range_entry_string(__LINE__, (unsigned int)_from, (unsigned int)_to, _text);

#undef  RANGE_ENTRY_VALUE
#define RANGE_ENTRY_VALUE(_from, _to, _pres) \
    init_range_entry_value(__LINE__, (unsigned int)_from, (unsigned int)_to, _pres);

#undef  RANGE_ENTRY_VALUE_EX
#define RANGE_ENTRY_VALUE_EX(_from, _to, _scale, _offset, _unit, _pres) \
    init_range_entry_value_ex(__LINE__, (unsigned int)_from, (unsigned int)_to, _scale, _offset, _unit, _pres);

/* old shortcut message macros */

#undef COMMON_MSG_REQ
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define COMMON_MSG_REQ \
    init_old_macro_used("COMMON_MSG_REQ: Replace macro with COMMON_MSG_HDR macro"); \
	COMMON_MSG_HDR
#else
 #define COMMON_MSG_REQ \
	COMMON_MSG_HDR
#endif

#undef COMMON_MSG_RESP
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define COMMON_MSG_RESP \
    init_old_macro_used("COMMON_MSG_RESP: Replace macro with COMMON_MSG_HDR macro"); \
	COMMON_MSG_HDR
#else
 #define COMMON_MSG_RESP \
	COMMON_MSG_HDR
#endif

#undef COMMON_MSG_IND 
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define COMMON_MSG_IND \
    init_old_macro_used("COMMON_MSG_IND: Replace macro with COMMON_MSG_HDR macro"); \
	COMMON_MSG_HDR
#else
 #define COMMON_MSG_IND \
	COMMON_MSG_HDR
#endif

#undef COMMON_MSG_NTF
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define COMMON_MSG_NTF \
    init_old_macro_used("COMMON_MSG_NTF: Replace macro with COMMON_MSG_HDR macro"); \
	COMMON_MSG_HDR
#else
 #define COMMON_MSG_NTF \
	COMMON_MSG_HDR
#endif


/* ============================================================================================= */
/* unsupported macros */
/* ============================================================================================= */

#undef  DEFINE_BCD_TBL_BEGIN
#define DEFINE_BCD_TBL_BEGIN(_name, _comment)
   
#undef  DEFINE_BCD_TBL_END
#define DEFINE_BCD_TBL_END

#undef  BCD_TBL_ENTRY
#define BCD_TBL_ENTRY(_index, _value)

#undef  BCD_REF_ENTRY
#define BCD_REF_ENTRY(_n, _varname, _parname)

#undef  MON_TRACE_GROUP_TBL_BEGIN
#define MON_TRACE_GROUP_TBL_BEGIN(_tblname)

#undef  MON_TRACE_GROUP_TBL_END
#define MON_TRACE_GROUP_TBL_END()

#undef  MON_TRACE_DEFINE_GROUP_ID
#define MON_TRACE_DEFINE_GROUP_ID(_grpname, _dectext)

#undef  MON_TRACE_DEFINE_GROUP_ID_FIXED
#define MON_TRACE_DEFINE_GROUP_ID_FIXED(_grpname, _id, _dectext)

#undef  MON_TRACE_LOGICAL_GROUP_BEGIN
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_LOGICAL_GROUP_BEGIN(_logname, _logdesc) \
    init_old_macro_used("MON_TRACE_LOGICAL_GROUP_BEGIN: Obsolete macro. Please remove...");
#else
 #define MON_TRACE_LOGICAL_GROUP_BEGIN(_logname, _logdesc)
#endif

#undef  MON_TRACE_LOGICAL_GROUP_END
#ifdef  AUTOGEN_ENVIRONMENT_LOCAL
 #define MON_TRACE_LOGICAL_GROUP_END() \
    init_old_macro_used("MON_TRACE_LOGICAL_GROUP_END: Obsolete macro. Please remove...");
#else
 #define MON_TRACE_LOGICAL_GROUP_END()
#endif

/* End of file isi_macros.h */
