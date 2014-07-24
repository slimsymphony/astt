/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                pmdconstants.h
                --------------
                SW Include






Project:          autogen

%name:            pmdconstants.h %
%version:         co1tss#245 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 12:12:01 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen and Tracing SDK

    The file contains the constant definitions needed for the PMD file format
*/

#ifndef _PMDCONSTANTS_H_
#define _PMDCONSTANTS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================= */
/* Constants */
/* ============================================================================================= */

/* enum EAlignment */
#define PMD_ALIGNMENT_FIXED_OBSOLETE 1
#define PMD_ALIGNMENT_MODULUS 2
#define PMD_ALIGNMENT_MODULUS_MINUS_8 3
#define PMD_ALIGNMENT_MODULUS_MINUS_24 4

/* enum EBitPosition */
#define PMD_BIT_POSITION_NOT_SPECIFIED 0
#define PMD_BIT_POSITION_BEFORE 1
#define PMD_BIT_POSITION_AFTER 2

/* enum EBlockAlgorithm */
#define PMD_BLOCK_ALGORITHM_NOT_SPECIFIED 0
#define PMD_BLOCK_ALGORITHM_RAW_DATA PMD_BLOCK_ALGORITHM_NOT_SPECIFIED
#define PMD_BLOCK_ALGORITHM_IDENTITY 1
#define PMD_BLOCK_ALGORITHM_X_FILE 2
#define PMD_BLOCK_ALGORITHM_ENTRYPOINT 3
#define PMD_BLOCK_ALGORITHM_EXTERNAL 12

#define PMD_BLOCK_ALGORITHM_LAST 12

#define PMD_BLOCK_ALGORITHM_MAX 5

/* enum ECharacterSet (obsolete) */
#define PMD_CHARACTER_SET_ASCII_OBSOLETE 1
#define PMD_CHARACTER_SET_GSM_DEFAULT_OBSOLETE 2
#define PMD_CHARACTER_SET_UNICODE_OBSOLETE 3
#define PMD_CHARACTER_SET_NUMERIC_BCD_OBSOLETE 4
#define PMD_CHARACTER_SET_TDMA_BCD_OBSOLETE 5
#define PMD_CHARACTER_SET_GSM_BCD_OBSOLETE 6

/* enum ECharacterType */
#define PMD_CHARACTER_TYPE_UNKNOWN      0
#define PMD_CHARACTER_TYPE_BCD          1
#define PMD_CHARACTER_TYPE_ASCII        2
#define PMD_CHARACTER_TYPE_UNICODE      3
#define PMD_CHARACTER_TYPE_GSM          4
#define PMD_CHARACTER_TYPE_UTF8         5

#define PMD_CHARACTER_TYPE_MAX          6

/* enum ECompressionType */
#define PMD_COMPRESSION_TYPE_NONE 0
#define PMD_COMPRESSION_TYPE_LZ14 1
#define PMD_COMPRESSION_TYPE_LZ17 2
#define PMD_COMPRESSION_TYPE_LZH  3

/* enum EDataOrder */
#define PMD_DATA_ORDER_BIG_ENDIAN 1
#define PMD_DATA_ORDER_LITTLE_ENDIAN 2

/* enum EEncryptionType */
#define PMD_ENCRYPTION_TYPE_NONE 0
#define PMD_ENCRYPTION_TYPE_XOR_AA 1

/* enum EExportType (obsolete) */
#define PMD_EXPORT_TYPE_SIMPLE_OBSOLETE 1
#define PMD_EXPORT_TYPE_ROOT_OBSOLETE 2
#define PMD_EXPORT_TYPE_ENTRY_POINT_OBSOLETE 3

/* enum EFunction */
#define PMD_FUNCTION_UNKNOWN                                0
#define PMD_FUNCTION_REQUEST                                1
#define PMD_FUNCTION_INDICATION                             2
#define PMD_FUNCTION_RESPONSE                               3
#define PMD_FUNCTION_NOTIFICATION                           4

#define PMD_FUNCTION_MAX                                    5

#define PMD_CDSP_TASK_TYPE_UNKNOWN                          0
#define PMD_CDSP_TASK_TYPE_IDLE                             1
#define PMD_CDSP_TASK_TYPE_INTERRUPT                        2
#define PMD_CDSP_TASK_TYPE_PRIORITY                         3

/* enum ELengthAlgorithm */
#define PMD_LENGTH_ALGORITHM_NOT_SPECIFIED                  0
#define PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH             1
#define PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MINUS_N            2
#define PMD_LENGTH_ALGORITHM_FIXEDLENGTH                    3
#define PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N              4
#define PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N_PLUS_1       5
#define PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N_MINUS_1      6
#define PMD_LENGTH_ALGORITHM_AS_MANY_AS_POSSIBLE            7
#define PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH              8
#define PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH_ROUNDUP      9
#define PMD_LENGTH_ALGORITHM_OPTIONAL                       10
#define PMD_LENGTH_ALGORITHM_UNKNOWN                        11

#define PMD_LENGTH_ALGORITHM_MAX                            12

/* enum ELengthType */
#define PMD_LENGTH_TYPE_CHARACTERS 1
#define PMD_LENGTH_TYPE_BYTES 2

/* Message type groups */

#define PMD_MESSAGE_TYPE_GROUP_NONE                         0
#define PMD_MESSAGE_TYPE_GROUP_DSP5_CDSP                    1
#define PMD_MESSAGE_TYPE_GROUP_DSP5_ADSP                    2
#define PMD_MESSAGE_TYPE_GROUP_INVARIANT                    3

#define PMD_MESSAGE_TYPE_GROUP_MAX                          4

/* Message types */
#define PMD_MESSAGE_TYPE_GROUP_1_FIRST                      0

#define PMD_MESSAGE_TYPE_UNDEFINED                          0
#define PMD_MESSAGE_TYPE_PHONET_HEADER                      1
#define PMD_MESSAGE_TYPE_ISI                                2
#define PMD_MESSAGE_TYPE_ISI_PRIVATE                        3
#define PMD_MESSAGE_TYPE_GSM_DSP_TRACE                      7
#define PMD_MESSAGE_TYPE_MCU_TRACE                          8
#define PMD_MESSAGE_TYPE_MEDIA_MODULE                       12
#define PMD_MESSAGE_TYPE_OS_TRACE                           13
#define PMD_MESSAGE_TYPE_STI_TRACE                          14
#define PMD_MESSAGE_TYPE_RESERVED_0                         15
#define PMD_MESSAGE_TYPE_WCDMA_CDSP_TRACE                   16
#define PMD_MESSAGE_TYPE_WCDMA_CDSP_ALGORITHM_TRACE         18
#define PMD_MESSAGE_TYPE_ADSP_TRACE                         19
#define PMD_MESSAGE_TYPE_EXTERNAL                           20
#define PMD_MESSAGE_TYPE_DSP5_CORE                          21
#define PMD_MESSAGE_TYPE_DSP5_SIGNALS                       22
#define PMD_MESSAGE_TYPE_DSP5_TASKS                         23
#define PMD_MESSAGE_TYPE_DSP5_WCDMA                         24
#define PMD_MESSAGE_TYPE_DSP5_GSM                           25
#define PMD_MESSAGE_TYPE_DSP5_APPLICATION                   26
/* TODO: this should be changed to PMD_MESSAGE_TYPE_PHONET later on */
#define PMD_MESSAGE_TYPE_PHONET_                            27
#define PMD_MESSAGE_TYPE_PHONET_EXT                         28

#define PMD_MESSAGE_TYPE_CDSP_OSE_TRACE                     29
#define PMD_MESSAGE_TYPE_ADSP_OSE_TRACE                     30
#define PMD_MESSAGE_TYPE_PROTOCOL                           31
#define PMD_MESSAGE_TYPE_HAL_TRACE                          32
/* Obsolete...
#define PMD_MESSAGE_TYPE_XTI_MASTER_TRACE                   33
*/
#define PMD_MESSAGE_TYPE_INVARIANT_TRACE                    34
#define PMD_MESSAGE_TYPE_CDSP5_TRACE                        35
#define PMD_MESSAGE_TYPE_ADSP5_TRACE                        36
#define PMD_MESSAGE_TYPE_MASTER_TRACE                       37
#define PMD_MESSAGE_TYPE_VENDOR_COMPONENT_TRACE             38
#define PMD_MESSAGE_TYPE_VENDOR_DLL_TRACE                   39
#define PMD_MESSAGE_TYPE_OST                                40
#define PMD_MESSAGE_TYPE_HSP_TRACE                          41
#define PMD_MESSAGE_TYPE_OST_HEADER                         42

#define PMD_MESSAGE_TYPE_GROUP_1_LAST                       PMD_MESSAGE_TYPE_OST_HEADER
#define PMD_MESSAGE_TYPE_GROUP_1_MAX                        (PMD_MESSAGE_TYPE_GROUP_1_LAST - PMD_MESSAGE_TYPE_GROUP_1_FIRST + 1)


#define PMD_MESSAGE_TYPE_GROUP_2_FIRST                      0x0100

#define PMD_MESSAGE_TYPE_CDMA_DSP_TRACE                     0x0100
#define PMD_MESSAGE_TYPE_SYMBIAN_TRACE                      0x0101

#define PMD_MESSAGE_TYPE_GROUP_2_LAST                       PMD_MESSAGE_TYPE_SYMBIAN_TRACE
#define PMD_MESSAGE_TYPE_GROUP_2_MAX                        (PMD_MESSAGE_TYPE_GROUP_2_LAST - PMD_MESSAGE_TYPE_GROUP_2_FIRST + 1)

#define PMD_MESSAGE_TYPE_INVARIANT_TRACE_FIRST              0x0102
#define PMD_MESSAGE_TYPE_INVARIANT_TRACE_LAST               (PMD_MESSAGE_TYPE_INVARIANT_TRACE_FIRST + 255)

#define PMD_MESSAGE_TYPE_DSP5_CDSP_FIRST                    0x1000

#define PMD_MESSAGE_TYPE_DSP5_CDSP_1                        0x1000
#define PMD_MESSAGE_TYPE_DSP5_CDSP_2                        0x1001
#define PMD_MESSAGE_TYPE_DSP5_CDSP_3                        0x1002
#define PMD_MESSAGE_TYPE_DSP5_CDSP_4                        0x1003
#define PMD_MESSAGE_TYPE_DSP5_CDSP_5                        0x1004
#define PMD_MESSAGE_TYPE_DSP5_CDSP_6                        0x1005
#define PMD_MESSAGE_TYPE_DSP5_CDSP_7                        0x1006
#define PMD_MESSAGE_TYPE_DSP5_CDSP_8                        0x1007
#define PMD_MESSAGE_TYPE_DSP5_CDSP_9                        0x1008
#define PMD_MESSAGE_TYPE_DSP5_CDSP_10                       0x1009
#define PMD_MESSAGE_TYPE_DSP5_CDSP_11                       0x100A
#define PMD_MESSAGE_TYPE_DSP5_CDSP_12                       0x100B
#define PMD_MESSAGE_TYPE_DSP5_CDSP_13                       0x100C
#define PMD_MESSAGE_TYPE_DSP5_CDSP_14                       0x100D
#define PMD_MESSAGE_TYPE_DSP5_CDSP_15                       0x100E
#define PMD_MESSAGE_TYPE_DSP5_CDSP_16                       0x100F
#define PMD_MESSAGE_TYPE_DSP5_CDSP_17                       0x1010
#define PMD_MESSAGE_TYPE_DSP5_CDSP_18                       0x1011
#define PMD_MESSAGE_TYPE_DSP5_CDSP_19                       0x1012
#define PMD_MESSAGE_TYPE_DSP5_CDSP_20                       0x1013
#define PMD_MESSAGE_TYPE_DSP5_CDSP_21                       0x1014
#define PMD_MESSAGE_TYPE_DSP5_CDSP_22                       0x1015
#define PMD_MESSAGE_TYPE_DSP5_CDSP_23                       0x1016
#define PMD_MESSAGE_TYPE_DSP5_CDSP_24                       0x1017
#define PMD_MESSAGE_TYPE_DSP5_CDSP_25                       0x1018
#define PMD_MESSAGE_TYPE_DSP5_CDSP_26                       0x1019
#define PMD_MESSAGE_TYPE_DSP5_CDSP_27                       0x101A
#define PMD_MESSAGE_TYPE_DSP5_CDSP_28                       0x101B
#define PMD_MESSAGE_TYPE_DSP5_CDSP_29                       0x101C
#define PMD_MESSAGE_TYPE_DSP5_CDSP_30                       0x101D

#define PMD_MESSAGE_TYPE_DSP5_CDSP_LAST                     0x101D
#define PMD_MESSAGE_TYPE_DSP5_CDSP_MAX                      (PMD_MESSAGE_TYPE_DSP5_CDSP_LAST - PMD_MESSAGE_TYPE_DSP5_CDSP_FIRST + 1)

#define PMD_MESSAGE_TYPE_DSP5_ADSP_FIRST                     0x2000

#define PMD_MESSAGE_TYPE_DSP5_ADSP_1                         0x2000
#define PMD_MESSAGE_TYPE_DSP5_ADSP_2                         0x2001
#define PMD_MESSAGE_TYPE_DSP5_ADSP_3                         0x2002
#define PMD_MESSAGE_TYPE_DSP5_ADSP_4                         0x2003
#define PMD_MESSAGE_TYPE_DSP5_ADSP_5                         0x2004
#define PMD_MESSAGE_TYPE_DSP5_ADSP_6                         0x2005
#define PMD_MESSAGE_TYPE_DSP5_ADSP_7                         0x2006
#define PMD_MESSAGE_TYPE_DSP5_ADSP_8                         0x2007
#define PMD_MESSAGE_TYPE_DSP5_ADSP_9                         0x2008
#define PMD_MESSAGE_TYPE_DSP5_ADSP_10                        0x2009
#define PMD_MESSAGE_TYPE_DSP5_ADSP_11                        0x200A
#define PMD_MESSAGE_TYPE_DSP5_ADSP_12                        0x200B
#define PMD_MESSAGE_TYPE_DSP5_ADSP_13                        0x200C
#define PMD_MESSAGE_TYPE_DSP5_ADSP_14                        0x200D
#define PMD_MESSAGE_TYPE_DSP5_ADSP_15                        0x200E
#define PMD_MESSAGE_TYPE_DSP5_ADSP_16                        0x200F
#define PMD_MESSAGE_TYPE_DSP5_ADSP_17                        0x2010
#define PMD_MESSAGE_TYPE_DSP5_ADSP_18                        0x2011
#define PMD_MESSAGE_TYPE_DSP5_ADSP_19                        0x2012
#define PMD_MESSAGE_TYPE_DSP5_ADSP_20                        0x2013
#define PMD_MESSAGE_TYPE_DSP5_ADSP_21                        0x2014
#define PMD_MESSAGE_TYPE_DSP5_ADSP_22                        0x2015
#define PMD_MESSAGE_TYPE_DSP5_ADSP_23                        0x2016
#define PMD_MESSAGE_TYPE_DSP5_ADSP_24                        0x2017
#define PMD_MESSAGE_TYPE_DSP5_ADSP_25                        0x2018
#define PMD_MESSAGE_TYPE_DSP5_ADSP_26                        0x2019
#define PMD_MESSAGE_TYPE_DSP5_ADSP_27                        0x201A
#define PMD_MESSAGE_TYPE_DSP5_ADSP_28                        0x201B
#define PMD_MESSAGE_TYPE_DSP5_ADSP_29                        0x201C
#define PMD_MESSAGE_TYPE_DSP5_ADSP_30                        0x201D

#define PMD_MESSAGE_TYPE_DSP5_ADSP_LAST                      0x201D
#define PMD_MESSAGE_TYPE_DSP5_ADSP_MAX (PMD_MESSAGE_TYPE_DSP5_ADSP_LAST - PMD_MESSAGE_TYPE_DSP5_ADSP_FIRST + 1)

#define PMD_MESSAGE_TYPE_MAX (PMD_MESSAGE_TYPE_GROUP_1_MAX + \
                              PMD_MESSAGE_TYPE_GROUP_2_MAX)


/* compatibility defintions */
#define PMD_MESSAGE_TYPE_ADSP_TRANSPORT                     PMD_MESSAGE_TYPE_ADSP_OSE_TRACE
#define PMD_MESSAGE_TYPE_CDSP_TRANSPORT                     PMD_MESSAGE_TYPE_CDSP_OSE_TRACE


#define PMD_MESSAGE_TYPE_DSP5_OMAP_1                        PMD_MESSAGE_TYPE_DSP5_ADSP_1
#define PMD_MESSAGE_TYPE_DSP5_OMAP_2                        PMD_MESSAGE_TYPE_DSP5_ADSP_2
#define PMD_MESSAGE_TYPE_DSP5_OMAP_3                        PMD_MESSAGE_TYPE_DSP5_ADSP_3
#define PMD_MESSAGE_TYPE_DSP5_OMAP_4                        PMD_MESSAGE_TYPE_DSP5_ADSP_4
#define PMD_MESSAGE_TYPE_DSP5_OMAP_5                        PMD_MESSAGE_TYPE_DSP5_ADSP_5
#define PMD_MESSAGE_TYPE_DSP5_OMAP_6                        PMD_MESSAGE_TYPE_DSP5_ADSP_6
#define PMD_MESSAGE_TYPE_DSP5_OMAP_7                        PMD_MESSAGE_TYPE_DSP5_ADSP_7
#define PMD_MESSAGE_TYPE_DSP5_OMAP_8                        PMD_MESSAGE_TYPE_DSP5_ADSP_8
#define PMD_MESSAGE_TYPE_DSP5_OMAP_9                        PMD_MESSAGE_TYPE_DSP5_ADSP_9
#define PMD_MESSAGE_TYPE_DSP5_OMAP_10                       PMD_MESSAGE_TYPE_DSP5_ADSP_10
#define PMD_MESSAGE_TYPE_DSP5_OMAP_11                       PMD_MESSAGE_TYPE_DSP5_ADSP_11
#define PMD_MESSAGE_TYPE_DSP5_OMAP_12                       PMD_MESSAGE_TYPE_DSP5_ADSP_12
#define PMD_MESSAGE_TYPE_DSP5_OMAP_13                       PMD_MESSAGE_TYPE_DSP5_ADSP_13
#define PMD_MESSAGE_TYPE_DSP5_OMAP_14                       PMD_MESSAGE_TYPE_DSP5_ADSP_14
#define PMD_MESSAGE_TYPE_DSP5_OMAP_15                       PMD_MESSAGE_TYPE_DSP5_ADSP_15
#define PMD_MESSAGE_TYPE_DSP5_OMAP_16                       PMD_MESSAGE_TYPE_DSP5_ADSP_16
#define PMD_MESSAGE_TYPE_DSP5_OMAP_17                       PMD_MESSAGE_TYPE_DSP5_ADSP_17
#define PMD_MESSAGE_TYPE_DSP5_OMAP_18                       PMD_MESSAGE_TYPE_DSP5_ADSP_18
#define PMD_MESSAGE_TYPE_DSP5_OMAP_19                       PMD_MESSAGE_TYPE_DSP5_ADSP_19
#define PMD_MESSAGE_TYPE_DSP5_OMAP_20                       PMD_MESSAGE_TYPE_DSP5_ADSP_20

/* Message info tree element types */
#define PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_UNDEFINED                0
#define PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_GROUP       1
#define PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE             2
#define PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_ENTITY      3

/* enum ENullTermination */
#define PMD_NULL_TERMINATION_NONE                           0
#define PMD_NULL_TERMINATION_PRESENT                        1

/* enum EPmdObjectType */
#define PMD_CLASS_NULL 0
#define PMD_CLASS_BLOCK 1
#define PMD_CLASS_CHOICE 2
#define PMD_CLASS_CONDITION_ELEMENT_BITSTATE 3
#define PMD_CLASS_CONDITION_ELEMENT_INTERVAL 5
#define PMD_CLASS_DEFINITION_MODULE 7
#define PMD_CLASS_FILLER_TYPE_DYNAMIC 10
#define PMD_CLASS_FILLER_TYPE_STATIC 11
#define PMD_CLASS_MESSAGE 12
#define PMD_CLASS_NUMBER_PRESENTATION_CONDITION 13
#define PMD_CLASS_NUMBER_PRESENTATION_CONSTANT 14
#define PMD_CLASS_NUMBER_PRESENTATION_SIMPLE 15
#define PMD_CLASS_NUMBER_PRESENTATION_TRANSFORMATION 16
#define PMD_CLASS_NUMBER_TYPE 17
#define PMD_CLASS_PARAMETER_ASYNCHRONOUS_OBSOLETE 18
#define PMD_CLASS_PARAMETER_FTD_OBSOLETE 19
#define PMD_CLASS_PARAMETER_PPC_OBSOLETE 20
#define PMD_CLASS_PMD 21
#define PMD_CLASS_RESOURCE 22
#define PMD_CLASS_SEQUENCE 23
#define PMD_CLASS_SEQUENCE_OF 24
#define PMD_CLASS_STRING_PRESENTATION_SIMPLE_OBSOLETE 26
#define PMD_CLASS_STRING_TYPE 27
#define PMD_CLASS_PARAMETER 28
/* We reuse the same class id so that obsolete MCU trace groups will be loaded as post-1.11 trace groups */
#define PMD_CLASS_TRACE_GROUP                               29
#define PMD_CLASS_NUMBER_PRESENTATION_TIMESTAMP             30
#define PMD_CLASS_TRACE_SOURCE                              31
#define PMD_CLASS_ENVIRONMENT_VAR                           32
#define PMD_CLASS_MESSAGE_TYPE                              33
#define PMD_CLASS_RESOURCE_NEW                              34
#define PMD_CLASS_TRACE_GROUP_NEW                           35
#define PMD_CLASS_INFO                                      36
#define PMD_CLASS_INFO_TYPE                                 37
#define PMD_CLASS_INFO_GROUP                                PMD_CLASS_INFO_TYPE
#define PMD_CLASS_NUMBER_PRESENTATION_INFO                  38
#define PMD_CLASS_ENTRY_POINT                               39
#define PMD_CLASS_INDEX_SEQUENCE_OF                         40
#define PMD_CLASS_MESSAGE_TYPE_GROUP                        41
#define PMD_CLASS_ENTRY_POINT_SUBTREE                       42
#define PMD_CLASS_DEVICE                                    43
#define PMD_CLASS_MESSAGE_ENTITY                            44
#define PMD_CLASS_DEBUGINFO                                 45
#define PMD_CLASS_DEBUGINFODLL                              46

#define PMD_CLASS_FIRST 1
#define PMD_CLASS_LAST 46

/* Parameter types */
#define PMD_PARAMETER_TYPE_UNDEFINED                        0
#define PMD_PARAMETER_TYPE_ASYNCHRONOUS                     1
#define PMD_PARAMETER_TYPE_MCU_TRACE                        2
#define PMD_PARAMETER_TYPE_PPC                              3
#define PMD_PARAMETER_TYPE_RDD                              4
#define PMD_PARAMETER_TYPE_ISA_INDICATION                   5
#define PMD_PARAMETER_TYPE_OS_TRACE                         6
#define PMD_PARAMETER_TYPE_TIMESTAMP                        7
#define PMD_PARAMETER_TYPE_RESERVED_11                      8
#define PMD_PARAMETER_TYPE_WCDMA_CDSP_TRACE                 9
#define PMD_PARAMETER_TYPE_GSM_DSP_TRACE                    10
#define PMD_PARAMETER_TYPE_RESERVED_10                      11
#define PMD_PARAMETER_TYPE_WCDMA_CDSP_ALGORITHM_TRACE       12
#define PMD_PARAMETER_TYPE_ADSP_TRACE                       13
#define PMD_PARAMETER_TYPE_DSP5_CORE                        14
#define PMD_PARAMETER_TYPE_DSP5_SIGNALS                     15
#define PMD_PARAMETER_TYPE_DSP5_TASKS                       16
#define PMD_PARAMETER_TYPE_DSP5_WCDMA                       17
#define PMD_PARAMETER_TYPE_DSP5_GSM                         18
#define PMD_PARAMETER_TYPE_DSP5_APPLICATION                 19
#define PMD_PARAMETER_TYPE_STI_TRACE                        20
#define PMD_PARAMETER_TYPE_CDSP_TRANSPORT                   21
#define PMD_PARAMETER_TYPE_ADSP_TRANSPORT                   22
#define PMD_PARAMETER_TYPE_DSP5_ADSP                        23
#define PMD_PARAMETER_TYPE_DSP5_CDSP                        24
#define PMD_PARAMETER_TYPE_SYMBIAN                          25
#define PMD_PARAMETER_TYPE_MAX                              25

/* compactibility definitions */
#define PMD_PARAMETER_TYPE_DSP5_OMAP                        PMD_PARAMETER_TYPE_DSP5_ADSP


/* enum EPredefinedValue */
#define PMD_PREDEFINED_VALUE_NONE                           0
#define PMD_PREDEFINED_VALUE_GSM_BAND                       1
#define PMD_PREDEFINED_VALUE_TDMA_BAND                      2

/* enum EResourceType */
#define PMD_RESOURCE_TYPE_UNKNOWN                           0
#define PMD_RESOURCE_TYPE_SERVER                            1
#define PMD_RESOURCE_TYPE_MEDIA_MODULE                      4
#define PMD_RESOURCE_TYPE_SERVER_PRIVATE                    5
#define PMD_RESOURCE_TYPE_PHONET                            6
#define PMD_RESOURCE_TYPE_PHONET_EXT                        7
#define PMD_RESOURCE_TYPE_PROTOCOL                          8

#define PMD_RESOURCE_TYPE_MAX                               9

#define PMD_RESOURCE_TYPE_RESERVED_4                        9
#define PMD_RESOURCE_TYPE_RESERVED_5                        10
#define PMD_RESOURCE_TYPE_RESERVED_6                        11
#define PMD_RESOURCE_TYPE_RESERVED_7                        12
#define PMD_RESOURCE_TYPE_RESERVED_8                        13
#define PMD_RESOURCE_TYPE_RESERVED_9                        14

#define PMD_RESOURCE_TYPE_RESERVED_3                        PMD_RESOURCE_TYPE_PROTOCOL

/* enum ESequenceType */
#define PMD_SEQUENCE_TYPE_NONE                              0
#define PMD_SEQUENCE_TYPE_SIMPLE                            1
#define PMD_SEQUENCE_TYPE_SUB_BLOCK                         2
#define PMD_SEQUENCE_TYPE_BIG_ENDIAN_MERGED                 3
#define PMD_SEQUENCE_TYPE_LITTLE_ENDIAN_MERGED              4
#define PMD_SEQUENCE_TYPE_STRUCTURE                         5
#define PMD_SEQUENCE_TYPE_ANONYMOUS                         6
#define PMD_SEQUENCE_TYPE_MESSAGE                           7
#define PMD_SEQUENCE_TYPE_ENTRY_POINT                       8
#define PMD_SEQUENCE_TYPE_INDEX_ARRAY_ELEMENT               9
#define PMD_SEQUENCE_TYPE_PRINTF                            10

#define PMD_SEQUENCE_TYPE_MAX                               11

/* enum ETimestampType */
#define PMD_TIMESTAMP_TYPE_UNKNOWN 0
#define PMD_TIMESTAMP_TYPE_DSP5 1
#define PMD_TIMESTAMP_TYPE_GSM_FRAMES 2
#define PMD_TIMESTAMP_TYPE_MCU 3
#define PMD_TIMESTAMP_TYPE_STI_XTI 4
#define PMD_TIMESTAMP_TYPE_CDSP 5
#define PMD_TIMESTAMP_TYPE_ADSP 6
#define PMD_TIMESTAMP_TYPE_SOURCE 7
#define PMD_TIMESTAMP_TYPE_CDMA_SYSTEM 8
#define PMD_TIMESTAMP_TYPE_MAX 9

/* enum EValuePresentation */
#define PMD_VALUE_PRESENTATION_NOT_SPECIFIED 0
#define PMD_VALUE_PRESENTATION_HEX 1
#define PMD_VALUE_PRESENTATION_DEC 2
#define PMD_VALUE_PRESENTATION_BIN 3

/* Trace sources */
#define PMD_TRACE_SOURCE_UNKNOWN                            0
#define PMD_TRACE_SOURCE_MCU                                1
#define PMD_TRACE_SOURCE_OSTRICH_PRIMARY                    2
#define PMD_TRACE_SOURCE_OSTRICH_SECONDARY                  3
#define PMD_TRACE_SOURCE_OSTRICH_STATUS                     4
#define PMD_TRACE_SOURCE_GSM_DSP                            5
#define PMD_TRACE_SOURCE_OS                                 6
#define PMD_TRACE_SOURCE_WCDMA_CDSP                         7
#define PMD_TRACE_SOURCE_WCDMA_CDSP_ALGORITHM               8
#define PMD_TRACE_SOURCE_ADSP                               9
#define PMD_TRACE_SOURCE_DSP5_MAIN                          10
#define PMD_TRACE_SOURCE_DSP5_SIGNALS                       11
#define PMD_TRACE_SOURCE_DSP5_TASKS                         12
#define PMD_TRACE_SOURCE_DSP5_WCDMA                         13
#define PMD_TRACE_SOURCE_DSP5_GSM                           14
#define PMD_TRACE_SOURCE_DSP5_APPLICATION                   15
#define PMD_TRACE_SOURCE_OSTRICH_PRIMARY_XTI                16
#define PMD_TRACE_SOURCE_OSTRICH_SECONDARY_XTI              17
#define PMD_TRACE_SOURCE_OSTRICH_STATUS_XTI                 18
#define PMD_TRACE_SOURCE_WCDMA_CDSP_TASKS                   19
#define PMD_TRACE_SOURCE_ADSP_TASKS                         20
#define PMD_TRACE_SOURCE_STI                                21

#define PMD_TRACE_SOURCE_DSP5_CDSP_1                        0x1000 /* OS (or main control) */
#define PMD_TRACE_SOURCE_DSP5_CDSP_2                        0x1001 /* Core signals */
#define PMD_TRACE_SOURCE_DSP5_CDSP_3                        0x1002 /* Application signals */
#define PMD_TRACE_SOURCE_DSP5_CDSP_4                        0x1003 /* GSM signals */
#define PMD_TRACE_SOURCE_DSP5_CDSP_5                        0x1004 /* Shared signals */
#define PMD_TRACE_SOURCE_DSP5_CDSP_6                        0x1005 /* WCDMA signals */
#define PMD_TRACE_SOURCE_DSP5_CDSP_7                        0x1006 /* Application traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_8                        0x1007 /* WCDMA (alg.) traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_9                        0x1008 /* Shared traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_10                       0x1009 /* GSM Sleep traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_11                       0x100A /* GSM Common traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_12                       0x100B /* GSM MDI traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_13                       0x100C /* GSM Timing traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_14                       0x100D /* GSM AMR traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_15                       0x100E /* GSM GPRS traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_16                       0x100F /* GSM EDGE traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_17                       0x1010 /* GSM RF traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_18                       0x1011
#define PMD_TRACE_SOURCE_DSP5_CDSP_19                       0x1012
#define PMD_TRACE_SOURCE_DSP5_CDSP_20                       0x1013 /* RF HAL signal traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_21                       0x1014 /* RF HAL traces */
#define PMD_TRACE_SOURCE_DSP5_CDSP_22                       0x1015
#define PMD_TRACE_SOURCE_DSP5_CDSP_23                       0x1016
#define PMD_TRACE_SOURCE_DSP5_CDSP_24                       0x1017
#define PMD_TRACE_SOURCE_DSP5_CDSP_25                       0x1018
#define PMD_TRACE_SOURCE_DSP5_CDSP_26                       0x1019
#define PMD_TRACE_SOURCE_DSP5_CDSP_27                       0x101A
#define PMD_TRACE_SOURCE_DSP5_CDSP_28                       0x101B
#define PMD_TRACE_SOURCE_DSP5_CDSP_29                       0x101C
#define PMD_TRACE_SOURCE_DSP5_CDSP_30                       0x101D

#define PMD_TRACE_SOURCE_DSP5_CDSP_MAIN_CONTROL             PMD_TRACE_SOURCE_DSP5_CDSP_1
#define PMD_TRACE_SOURCE_DSP5_CDSP_CORE_SIGNALS             PMD_TRACE_SOURCE_DSP5_CDSP_2
#define PMD_TRACE_SOURCE_DSP5_CDSP_APPLICATION_SIGNALS      PMD_TRACE_SOURCE_DSP5_CDSP_3
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_SIGNALS              PMD_TRACE_SOURCE_DSP5_CDSP_4
#define PMD_TRACE_SOURCE_DSP5_CDSP_SHARED_SIGNALS           PMD_TRACE_SOURCE_DSP5_CDSP_5 /* Obsolete, has been used */
#define PMD_TRACE_SOURCE_DSP5_CDSP_WCDMA_SIGNALS            PMD_TRACE_SOURCE_DSP5_CDSP_6
#define PMD_TRACE_SOURCE_DSP5_CDSP_APPLICATION              PMD_TRACE_SOURCE_DSP5_CDSP_7
#define PMD_TRACE_SOURCE_DSP5_CDSP_WCDMA_ALGORITHM          PMD_TRACE_SOURCE_DSP5_CDSP_8
#define PMD_TRACE_SOURCE_DSP5_CDSP_SHARED                   PMD_TRACE_SOURCE_DSP5_CDSP_9
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_SLEEP                PMD_TRACE_SOURCE_DSP5_CDSP_10
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_COMMON               PMD_TRACE_SOURCE_DSP5_CDSP_11
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_MDI                  PMD_TRACE_SOURCE_DSP5_CDSP_12
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_TIMING               PMD_TRACE_SOURCE_DSP5_CDSP_13
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_AMR                  PMD_TRACE_SOURCE_DSP5_CDSP_14
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_GPRS                 PMD_TRACE_SOURCE_DSP5_CDSP_15
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_EDGE                 PMD_TRACE_SOURCE_DSP5_CDSP_16
#define PMD_TRACE_SOURCE_DSP5_CDSP_GSM_RF                   PMD_TRACE_SOURCE_DSP5_CDSP_17
#define PMD_TRACE_SOURCE_DSP5_CDSP_CDMA_SIGNALS             PMD_TRACE_SOURCE_DSP5_CDSP_18
#define PMD_TRACE_SOURCE_DSP5_CDSP_WCDMA_ASIP               PMD_TRACE_SOURCE_DSP5_CDSP_19
#define PMD_TRACE_SOURCE_DSP5_CDSP_RF_HAL_SIGNALS           PMD_TRACE_SOURCE_DSP5_CDSP_20
#define PMD_TRACE_SOURCE_DSP5_CDSP_RF_HAL                   PMD_TRACE_SOURCE_DSP5_CDSP_21

#define PMD_TRACE_SOURCE_DSP5_ADSP_1                        0x2000
#define PMD_TRACE_SOURCE_DSP5_ADSP_2                        0x2001
#define PMD_TRACE_SOURCE_DSP5_ADSP_3                        0x2002
#define PMD_TRACE_SOURCE_DSP5_ADSP_4                        0x2003
#define PMD_TRACE_SOURCE_DSP5_ADSP_5                        0x2004
#define PMD_TRACE_SOURCE_DSP5_ADSP_6                        0x2005
#define PMD_TRACE_SOURCE_DSP5_ADSP_7                        0x2006
#define PMD_TRACE_SOURCE_DSP5_ADSP_8                        0x2007
#define PMD_TRACE_SOURCE_DSP5_ADSP_9                        0x2008
#define PMD_TRACE_SOURCE_DSP5_ADSP_10                       0x2009
#define PMD_TRACE_SOURCE_DSP5_ADSP_11                       0x200A
#define PMD_TRACE_SOURCE_DSP5_ADSP_12                       0x200B
#define PMD_TRACE_SOURCE_DSP5_ADSP_13                       0x200C
#define PMD_TRACE_SOURCE_DSP5_ADSP_14                       0x200D
#define PMD_TRACE_SOURCE_DSP5_ADSP_15                       0x200E
#define PMD_TRACE_SOURCE_DSP5_ADSP_16                       0x200F
#define PMD_TRACE_SOURCE_DSP5_ADSP_17                       0x2010
#define PMD_TRACE_SOURCE_DSP5_ADSP_18                       0x2011
#define PMD_TRACE_SOURCE_DSP5_ADSP_19                       0x2012
#define PMD_TRACE_SOURCE_DSP5_ADSP_20                       0x2013
#define PMD_TRACE_SOURCE_DSP5_ADSP_21                       0x2014
#define PMD_TRACE_SOURCE_DSP5_ADSP_22                       0x2015
#define PMD_TRACE_SOURCE_DSP5_ADSP_23                       0x2016
#define PMD_TRACE_SOURCE_DSP5_ADSP_24                       0x2017
#define PMD_TRACE_SOURCE_DSP5_ADSP_25                       0x2018
#define PMD_TRACE_SOURCE_DSP5_ADSP_26                       0x2019
#define PMD_TRACE_SOURCE_DSP5_ADSP_27                       0x201A
#define PMD_TRACE_SOURCE_DSP5_ADSP_28                       0x201B
#define PMD_TRACE_SOURCE_DSP5_ADSP_29                       0x201C
#define PMD_TRACE_SOURCE_DSP5_ADSP_30                       0x201D

#define PMD_TRACE_SOURCE_DSP5_ADSP_MAIN_CONTROL             PMD_TRACE_SOURCE_DSP5_ADSP_1
#define PMD_TRACE_SOURCE_DSP5_ADSP_EAP                      PMD_TRACE_SOURCE_DSP5_ADSP_2
#define PMD_TRACE_SOURCE_DSP5_ADSP_VIDEO                    PMD_TRACE_SOURCE_DSP5_ADSP_3
#define PMD_TRACE_SOURCE_DSP5_ADSP_AUDIO                    PMD_TRACE_SOURCE_DSP5_ADSP_4
#define PMD_TRACE_SOURCE_DSP5_ADSP_SPEECH                   PMD_TRACE_SOURCE_DSP5_ADSP_5
#define PMD_TRACE_SOURCE_DSP5_ADSP_MIDI                     PMD_TRACE_SOURCE_DSP5_ADSP_6
#define PMD_TRACE_SOURCE_DSP5_ADSP_MUSIC_ENHANCED           PMD_TRACE_SOURCE_DSP5_ADSP_7
#define PMD_TRACE_SOURCE_DSP5_ADSP_VOICE_UI                 PMD_TRACE_SOURCE_DSP5_ADSP_8

/* compatibility definitions */
#define PMD_TRACE_SOURCE_DSP5_OMAP_1                        PMD_TRACE_SOURCE_DSP5_ADSP_1
#define PMD_TRACE_SOURCE_DSP5_OMAP_2                        PMD_TRACE_SOURCE_DSP5_ADSP_2
#define PMD_TRACE_SOURCE_DSP5_OMAP_3                        PMD_TRACE_SOURCE_DSP5_ADSP_3
#define PMD_TRACE_SOURCE_DSP5_OMAP_4                        PMD_TRACE_SOURCE_DSP5_ADSP_4
#define PMD_TRACE_SOURCE_DSP5_OMAP_5                        PMD_TRACE_SOURCE_DSP5_ADSP_5
#define PMD_TRACE_SOURCE_DSP5_OMAP_6                        PMD_TRACE_SOURCE_DSP5_ADSP_6
#define PMD_TRACE_SOURCE_DSP5_OMAP_7                        PMD_TRACE_SOURCE_DSP5_ADSP_7
#define PMD_TRACE_SOURCE_DSP5_OMAP_8                        PMD_TRACE_SOURCE_DSP5_ADSP_8
#define PMD_TRACE_SOURCE_DSP5_OMAP_9                        PMD_TRACE_SOURCE_DSP5_ADSP_9
#define PMD_TRACE_SOURCE_DSP5_OMAP_10                       PMD_TRACE_SOURCE_DSP5_ADSP_10
#define PMD_TRACE_SOURCE_DSP5_OMAP_11                       PMD_TRACE_SOURCE_DSP5_ADSP_11
#define PMD_TRACE_SOURCE_DSP5_OMAP_12                       PMD_TRACE_SOURCE_DSP5_ADSP_12
#define PMD_TRACE_SOURCE_DSP5_OMAP_13                       PMD_TRACE_SOURCE_DSP5_ADSP_13
#define PMD_TRACE_SOURCE_DSP5_OMAP_14                       PMD_TRACE_SOURCE_DSP5_ADSP_14
#define PMD_TRACE_SOURCE_DSP5_OMAP_15                       PMD_TRACE_SOURCE_DSP5_ADSP_15
#define PMD_TRACE_SOURCE_DSP5_OMAP_16                       PMD_TRACE_SOURCE_DSP5_ADSP_16
#define PMD_TRACE_SOURCE_DSP5_OMAP_17                       PMD_TRACE_SOURCE_DSP5_ADSP_17
#define PMD_TRACE_SOURCE_DSP5_OMAP_18                       PMD_TRACE_SOURCE_DSP5_ADSP_18
#define PMD_TRACE_SOURCE_DSP5_OMAP_19                       PMD_TRACE_SOURCE_DSP5_ADSP_19
#define PMD_TRACE_SOURCE_DSP5_OMAP_20                       PMD_TRACE_SOURCE_DSP5_ADSP_20


/* PMD file types */
#define PMD_FILE_TYPE_UNKNOWN                               0
#define PMD_FILE_TYPE_PRODUCT                               1
#define PMD_FILE_TYPE_CDSP                                  2
#define PMD_FILE_TYPE_ADSP                                  3
#define PMD_FILE_TYPE_DSP5                                  4
#define PMD_FILE_TYPE_HANDMADE                              5
#define PMD_FILE_TYPE_DSP5_CDSP                             6
#define PMD_FILE_TYPE_DSP5_ADSP                             7
#define PMD_FILE_TYPE_CDMA_DSP                              8
#define PMD_FILE_TYPE_RESOURCES                             9
#define PMD_FILE_TYPE_REDUCED                              10
#define PMD_FILE_TYPE_SYMBIAN                              11
#define PMD_FILE_TYPE_OPTRA                                12 /* obsolete */
#define PMD_FILE_TYPE_DEVICE                               13

#define PMD_FILE_TYPE_MAX                                  14

/* PMD file restrictions */
#define PMD_FILE_RESTRICTION_RD                             0
#define PMD_FILE_RESTRICTION_RESTRICTED                     1
#define PMD_FILE_RESTRICTION_PUBLIC                         2

#define PMD_FILE_RESTRICTION_MAX                            3

/* PMD version compability */
#define PMD_FILE_FORMAT_COMPATIBEL                          0
#define PMD_FILE_FORMAT_INCOMPATIBEL                        1

/* enum EEnvironmentVarId */
#define PMD_ENVIRONMENT_VAR_ID_ORIGINAL_FIRST               0

#define PMD_ENVIRONMENT_VAR_ID_UNDEFINED                    0
#define PMD_ENVIRONMENT_VAR_ID_MCU_TRACE_BITMAP_ID          1
#define PMD_ENVIRONMENT_VAR_ID_MCU_TRACE_BITMAP_LENGTH      2
#define PMD_ENVIRONMENT_VAR_ID_OS_TIMER_INTERVAL            3
#define PMD_ENVIRONMENT_VAR_ID_MCU_SW_VERSION               4
#define PMD_ENVIRONMENT_VAR_ID_CDSP_SW_VERSION              5
#define PMD_ENVIRONMENT_VAR_ID_ADSP_SW_VERSION              6
#define PMD_ENVIRONMENT_VAR_ID_PMD_FILE_TYPE                7
#define PMD_ENVIRONMENT_VAR_ID_PMD_FILE_DESCRIPTION         8
#define PMD_ENVIRONMENT_VAR_ID_PMD_FILE_MODIFY_DATE         9
#define PMD_ENVIRONMENT_VAR_ID_PMD_FILE_ORIGIN              10
#define PMD_ENVIRONMENT_VAR_ID_CDMA_DSP_SW_VERSION          11
#define PMD_ENVIRONMENT_VAR_ID_PMD_FILE_RESTRICTION         12
#define PMD_ENVIRONMENT_VAR_ID_SW_VERSION                   13
#define PMD_ENVIRONMENT_VAR_ID_MONITOR_SERVER_RESOURCE_ID   14
#define PMD_ENVIRONMENT_VAR_ID_MONITOR_SERVER_VERSION       15
#define PMD_ENVIRONMENT_VAR_ID_DEVICE_ENDIANESS             16

#define PMD_ENVIRONMENT_VAR_ID_ORIGINAL_LAST                16

#define PMD_ENVIRONMENT_VAR_ID_ORIGINAL_MAX (PMD_ENVIRONMENT_VAR_ID_ORIGINAL_LAST - PMD_ENVIRONMENT_VAR_ID_ORIGINAL_FIRST + 1)

/* ------------------------------------------------------------------------- */
/* MCU OS flags */
/* ------------------------------------------------------------------------- */

#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_FIRST                         30

#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_TIMER_INTERVAL                PMD_ENVIRONMENT_VAR_ID_OS_TIMER_INTERVAL
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_ALIGN                   30
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEADER_DATA_SIZE              31
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_SYSTEM_STACK_SIZE             32
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_SYSTEM_STACK_1_SIZE           33
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_HEAP_SIZE              34
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_HEAP_AREAS                35
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_SIZE_MIN                 36
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_SIZE_MAX                 37
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_AREA_1_SIZE              38
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_AREA_2_SIZE              39
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_SLOW_HEAP_AREAS           40
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_SIZE_MIN            41
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_SIZE_MAX            42
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_AREA_1_SIZE         43
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_AREA_2_SIZE         44
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_AMOUNT           45
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TIMER_AMOUNT          46
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_HIGH_PRIORITY    47
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_LOW_PRIORITY     48
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_STACK_MULTIPLY                49
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_64K_TIMERS                    50
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_REG_EVENT_TIMER_INT           51
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_FILL_STACKS                   52
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_MONITOR                       53
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TRACE_CONTROL         54
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_PORTABLE_LOG                  55
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_ERROR_CHK                     56
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_WATCHDOG_SUPPORT              57 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_DEALLOC_AREA_LO           58
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_DEALLOC_AREA_HI           59
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_PTR_VALIDITY_CHECK      60
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_CALLER_DEPTH             61
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_HEADER_CALLER_STORE      62
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_DEALLOCATOR_STORE        63
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_POST_MORTEM_CALLER_STORE      64
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_POST_MORTEM_CALLER_COUNT      65
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAZY_FN_CALLER                66
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_FAILSAFE_STACK_SIZE           67
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_IRQ_STACK_LOW_WARNING         68
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_TASK_STACK_LOW_WARNING        69
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_UPP_MTC_AWAKE_TIMER_LENGTH    70
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_UPP_MTC_AWAKE_DSPGPT_OPTIMIZATION 71
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_REG_EVENT_TICK                72
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_REG_EVENT_SETTLE_TIME         73
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_MINIMUM_SLEEP_TIME            74
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_MULTIPLE_REG_EVENT_SOURCES    75
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_SIMULATED_REG_EVENT_INT       76
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_FREE_RUNNING_TIMER_USED       77
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_LONG_SW_TIMERS                78
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_CURRENT_TIME_USED             79
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_CURRENT_TIME_IN_MS            80
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_ACTIVATION           81
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_INIT_VALUE           82
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_FATAL_OWNER_BLOCKING_RESOURCE 83
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_FATAL_BLOCKING_ALLOC          84
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_FIRST_FIT                85
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_IN_USE              86
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_MEMORY_SERVICE        87
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_REGION_AMOUNT                 88
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_TASK_NAMES             89
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_TIMER_NAMES            90
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_TASK_AMOUNT                   91
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_SET_AMOUNT              92
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_AMOUNT               93
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_TIMER_AMOUNT                  94
#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_RESOURCE_AMOUNT       95

#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAST                          95

#define PMD_ENVIRONMENT_VAR_ID_MCU_OS_MAX (PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAST - PMD_ENVIRONMENT_VAR_ID_MCU_OS_FIRST + 1)

/* ------------------------------------------------------------------------- */
/* Product variables */
/* ------------------------------------------------------------------------- */

#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_FIRST                        100

#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_PROJECT                      100  /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_NAME                         101
#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_COMPILER_TYPE                102
#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_TEST_ENV                     103
#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_OS_TYPE                      104
#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_CS_TYPE                      105

#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_LAST                         105

#define PMD_ENVIRONMENT_VAR_ID_PRODUCT_MAX (PMD_ENVIRONMENT_VAR_ID_PRODUCT_LAST - PMD_ENVIRONMENT_VAR_ID_PRODUCT_FIRST + 1)

/* ------------------------------------------------------------------------- */
/* ISA core flags */
/* ------------------------------------------------------------------------- */

#define PMD_ENVIRONMENT_VAR_ID_ICF_FIRST                            200

#define PMD_ENVIRONMENT_VAR_ID_ICF_3D_IMAGES                        200
#define PMD_ENVIRONMENT_VAR_ID_ICF_3RD_PARTY_VIDEOCODEC             201
#define PMD_ENVIRONMENT_VAR_ID_ICF_ACC_SERV                         202
#define PMD_ENVIRONMENT_VAR_ID_ICF_ADL_SERV                         203
#define PMD_ENVIRONMENT_VAR_ID_ICF_APPL                             204
#define PMD_ENVIRONMENT_VAR_ID_ICF_ASSERT_LIB                       205
#define PMD_ENVIRONMENT_VAR_ID_ICF_ATK                              206
#define PMD_ENVIRONMENT_VAR_ID_ICF_AUDIO_SERV                       207
#define PMD_ENVIRONMENT_VAR_ID_ICF_AUXILIARY_SW_DOWNLOAD            208
#define PMD_ENVIRONMENT_VAR_ID_ICF_BOTTOM_CONNECTOR                 209
#define PMD_ENVIRONMENT_VAR_ID_ICF_BT                               210
#define PMD_ENVIRONMENT_VAR_ID_ICF_BT_AUDIO_STREAMING               211
#define PMD_ENVIRONMENT_VAR_ID_ICF_BT_AVRCP_TARGET                  212
#define PMD_ENVIRONMENT_VAR_ID_ICF_BTCS_SERV                        213
#define PMD_ENVIRONMENT_VAR_ID_ICF_BTIF_LIB                         214
#define PMD_ENVIRONMENT_VAR_ID_ICF_CAMERA                           215
#define PMD_ENVIRONMENT_VAR_ID_ICF_CAMERA_HAL                       216
#define PMD_ENVIRONMENT_VAR_ID_ICF_CAMERA_SERV                      217
#define PMD_ENVIRONMENT_VAR_ID_ICF_CDB_LIB                          218
#define PMD_ENVIRONMENT_VAR_ID_ICF_CHANGELOG_LIB                    219 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_CL                               220
#define PMD_ENVIRONMENT_VAR_ID_ICF_COLOR_DISPLAY                    221 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_COMPASS                          222
#define PMD_ENVIRONMENT_VAR_ID_ICF_COMP_LIB                         223
#define PMD_ENVIRONMENT_VAR_ID_ICF_CONTTYPE_LIB                     224
#define PMD_ENVIRONMENT_VAR_ID_ICF_CORE_ONLY_BUILD                  225
#define PMD_ENVIRONMENT_VAR_ID_ICF_CORE_WAKEUP                      226
#define PMD_ENVIRONMENT_VAR_ID_ICF_CRASH_DUMP                       227
#define PMD_ENVIRONMENT_VAR_ID_ICF_CRYPTO_LIB                       228
#define PMD_ENVIRONMENT_VAR_ID_ICF_CS_DATA                          229
#define PMD_ENVIRONMENT_VAR_ID_ICF_CXML_LIB                         230
#define PMD_ENVIRONMENT_VAR_ID_ICF_D2D_COPY                         231
#define PMD_ENVIRONMENT_VAR_ID_ICF_D2D_SYNC                         232
#define PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SERVER                  233
#define PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SERVER_SUBSET           234
#define PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SUBSYSTEM               235
#define PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SUBSYSTEM_SUBSET        236
#define PMD_ENVIRONMENT_VAR_ID_ICF_DISP                             237
#define PMD_ENVIRONMENT_VAR_ID_ICF_DSS                              238
#define PMD_ENVIRONMENT_VAR_ID_ICF_DUAL_MCU                         239
#define PMD_ENVIRONMENT_VAR_ID_ICF_EM                               240
#define PMD_ENVIRONMENT_VAR_ID_ICF_FASTMON_LIB                      241
#define PMD_ENVIRONMENT_VAR_ID_ICF_FBUS                             242
#define PMD_ENVIRONMENT_VAR_ID_ICF_FILE_SERV                        243
#define PMD_ENVIRONMENT_VAR_ID_ICF_FILE2                            244
#define PMD_ENVIRONMENT_VAR_ID_ICF_FILE2_ASL_SUPPORT                245
#define PMD_ENVIRONMENT_VAR_ID_ICF_FLIGHT_MODE                      246
#define PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO                         247
#define PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO_BUS_SELECTION           248 /* OBSOLETE */
#define PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO_CHIP                    249
#define PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO_SERV                    250
#define PMD_ENVIRONMENT_VAR_ID_ICF_FMAN_IF                          251 /* OBSOLETE */
#define PMD_ENVIRONMENT_VAR_ID_ICF_FMAN_LIB                         252
#define PMD_ENVIRONMENT_VAR_ID_ICF_FTS_APPL                         253
#define PMD_ENVIRONMENT_VAR_ID_ICF_FUNCTIONAL_COVERS                254 /* OBSOLETE */
#define PMD_ENVIRONMENT_VAR_ID_ICF_GDI                              255
#define PMD_ENVIRONMENT_VAR_ID_ICF_GPRS                             256
#define PMD_ENVIRONMENT_VAR_ID_ICF_HAL_I2C                          257
#define PMD_ENVIRONMENT_VAR_ID_ICF_HAL_LCD_LITE                     258
#define PMD_ENVIRONMENT_VAR_ID_ICF_HAL_LIGHT_LITE                   259
#define PMD_ENVIRONMENT_VAR_ID_ICF_HAL_HW_PMM_LITE                  260
#define PMD_ENVIRONMENT_VAR_ID_ICF_HSM_LIB                          261
#define PMD_ENVIRONMENT_VAR_ID_ICF_HTTP_SUPPORT                     262 /* OBSOLETE */
#define PMD_ENVIRONMENT_VAR_ID_ICF_HWDRV                            263
#define PMD_ENVIRONMENT_VAR_ID_ICF_HW_GENERATION                    264
#define PMD_ENVIRONMENT_VAR_ID_ICF_I2C_CORE_SERV                    265 /* OBSOLETE */
#define PMD_ENVIRONMENT_VAR_ID_ICF_IMAGES                           266
#define PMD_ENVIRONMENT_VAR_ID_ICF_IMAGE_ENGINE_LIB                 267
#define PMD_ENVIRONMENT_VAR_ID_ICF_IMM_LIB                          268
#define PMD_ENVIRONMENT_VAR_ID_ICF_IMO_LIB                          269 /* OBSOLETE */
#define PMD_ENVIRONMENT_VAR_ID_ICF_IMPLIB_LIB                       270
#define PMD_ENVIRONMENT_VAR_ID_ICF_INFO_SERV                        271
#define PMD_ENVIRONMENT_VAR_ID_ICF_IRDA                             272
#define PMD_ENVIRONMENT_VAR_ID_ICF_ISA2                             273
#define PMD_ENVIRONMENT_VAR_ID_ICF_ISA_UI                           274
#define PMD_ENVIRONMENT_VAR_ID_ICF_JAPANESE_INPUT                   275 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_JAVA_APPS_FILE2_SUPPORT          276
#define PMD_ENVIRONMENT_VAR_ID_ICF_KASUMI_LIB                       277
#define PMD_ENVIRONMENT_VAR_ID_ICF_KBD_SERV                         278
#define PMD_ENVIRONMENT_VAR_ID_ICF_LBEC                             279
#define PMD_ENVIRONMENT_VAR_ID_ICF_LCD_LIB                          280
#define PMD_ENVIRONMENT_VAR_ID_ICF_LCIF_SERV                        281
#define PMD_ENVIRONMENT_VAR_ID_ICF_LIBRARIES                        282
#define PMD_ENVIRONMENT_VAR_ID_ICF_LIGHT_SERV                       283
#define PMD_ENVIRONMENT_VAR_ID_ICF_LIST_LIB                         284
#define PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION                         285
#define PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_GOPHERS_LTM             286
#define PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_SERV                    287
#define PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_TEST_LTM                288
#define PMD_ENVIRONMENT_VAR_ID_ICF_MAX_VOICE_MODELS                 289
#define PMD_ENVIRONMENT_VAR_ID_ICF_MBUS                             290 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_MEDIA                            291
#define PMD_ENVIRONMENT_VAR_ID_ICF_MIDI_SERV                        292 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_MMC_SUPPORT                      293 /* Obsolete - replaced by 2 EMMC flags*/
#define PMD_ENVIRONMENT_VAR_ID_ICF_MMS_FILE2_SUPPORT                294 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_MONITOR_SERV                     295
#define PMD_ENVIRONMENT_VAR_ID_ICF_MS_ASIC_FAMILY                   296
#define PMD_ENVIRONMENT_VAR_ID_ICF_MTC_SERV                         297
#define PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC                            298
#define PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC_SERV                       299
#define PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC_SERVER_IN_USE              300 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_NAND_FLASH                       301
#define PMD_ENVIRONMENT_VAR_ID_ICF_NMPRT_LIB                        302
#define PMD_ENVIRONMENT_VAR_ID_ICF_NOR_DIRECT_CONTENT_FLASHING      303
#define PMD_ENVIRONMENT_VAR_ID_ICF_NOR_FLASH                        304
#define PMD_ENVIRONMENT_VAR_ID_ICF_NOTEPAD_SUPPORT                  305
#define PMD_ENVIRONMENT_VAR_ID_ICF_NVD_SERV                         306
#define PMD_ENVIRONMENT_VAR_ID_ICF_OBEX_SERV                        307
#define PMD_ENVIRONMENT_VAR_ID_ICF_ODIN_SERV                        308
#define PMD_ENVIRONMENT_VAR_ID_ICF_OMA_DM                           309
#define PMD_ENVIRONMENT_VAR_ID_ICF_OMA_DS                           310
#define PMD_ENVIRONMENT_VAR_ID_ICF_OS                               311
#define PMD_ENVIRONMENT_VAR_ID_ICF_OTA                              312
#define PMD_ENVIRONMENT_VAR_ID_ICF_OTI                              313
#define PMD_ENVIRONMENT_VAR_ID_ICF_PERM_DATA_FILLERS                314
#define PMD_ENVIRONMENT_VAR_ID_ICF_PERM_SERV                        315
#define PMD_ENVIRONMENT_VAR_ID_ICF_PMM                              316
#define PMD_ENVIRONMENT_VAR_ID_ICF_PMM_GENERATION                   317
#define PMD_ENVIRONMENT_VAR_ID_ICF_PMM2                             318
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_BT                      319
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_ENOS                    320 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_I2C                     321
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_IR                      322
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_IRDA                    323
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MBUS                    324 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MDI                     325
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MSTI                    326
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_RS232                   327 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_SOS_USB                 328
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_STI                     329
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_TCPIP                   330
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_TRUST                   331
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_USB                     332
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_XTI                     333
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_TERMINAL_ADAPTER              334
#define PMD_ENVIRONMENT_VAR_ID_ICF_POC_SUPPORT                      335
#define PMD_ENVIRONMENT_VAR_ID_ICF_PPM_AS_FILES                     336
#define PMD_ENVIRONMENT_VAR_ID_ICF_PRODUCT_TYPE                     337
#define PMD_ENVIRONMENT_VAR_ID_ICF_RENDER_3D_LIB                    338
#define PMD_ENVIRONMENT_VAR_ID_ICF_RS232                            339 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SBC_SERV                         340 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SCSI_PARSER                      341
#define PMD_ENVIRONMENT_VAR_ID_ICF_SDND                             342 /* Obselete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SECENV                           343
#define PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY                         344
#define PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY_LIB                     345
#define PMD_ENVIRONMENT_VAR_ID_ICF_SENSOR_SERV                      346
#define PMD_ENVIRONMENT_VAR_ID_ICF_SERVERS                          347
#define PMD_ENVIRONMENT_VAR_ID_ICF_SETTINGS_AS_FILES                348
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIM                              349
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIM_ATK                          350
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIM_COMMON                       361
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIM_GENERATION                   362 /* Obsolete from example_isa_core_product_conf.h #47 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIM_HWDRV                        363
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIM_HW_DRV                       364
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIMLOCK                          365
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIMSON_APDU                      366 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIMSON_SIM                       367 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SISA                             368
#define PMD_ENVIRONMENT_VAR_ID_ICF_SNOR_SUPPORT                     369
#define PMD_ENVIRONMENT_VAR_ID_ICF_SSI_LIB                          370
#define PMD_ENVIRONMENT_VAR_ID_ICF_ST_SERV                          371
#define PMD_ENVIRONMENT_VAR_ID_ICF_SUPERDONGLE                      372
#define PMD_ENVIRONMENT_VAR_ID_ICF_SYNCML                           373 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SYNCML_II_IN_USE                 374 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SYNCML_SERV                      375
#define PMD_ENVIRONMENT_VAR_ID_ICF_TASKS                            376
#define PMD_ENVIRONMENT_VAR_ID_ICF_TEST_SERV                        377
#define PMD_ENVIRONMENT_VAR_ID_ICF_TIME_SERV                        378
#define PMD_ENVIRONMENT_VAR_ID_ICF_TIME_ZONE                        379
#define PMD_ENVIRONMENT_VAR_ID_ICF_TOUCHPAD                         380
#define PMD_ENVIRONMENT_VAR_ID_ICF_TOUCHPAD_SERV                    381
#define PMD_ENVIRONMENT_VAR_ID_ICF_TRACE_INTERFACE                  382
#define PMD_ENVIRONMENT_VAR_ID_ICF_TTY_SUPPORT                      383
#define PMD_ENVIRONMENT_VAR_ID_ICF_UCS2_LIB                         384
#define PMD_ENVIRONMENT_VAR_ID_ICF_UI_THEMES                        385
#define PMD_ENVIRONMENT_VAR_ID_ICF_URL_LIB                          386
#define PMD_ENVIRONMENT_VAR_ID_ICF_USB                              387
#define PMD_ENVIRONMENT_VAR_ID_ICF_USB_MASS_STORAGE                 388
#define PMD_ENVIRONMENT_VAR_ID_ICF_USB_MASS_STORAGE_INTERNAL_MEMORY 389
#define PMD_ENVIRONMENT_VAR_ID_ICF_USER_DATA_AS_FILES               390 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_VERSIT_SERV                      391
#define PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO                            392
#define PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_RECORDER                   393
#define PMD_ENVIRONMENT_VAR_ID_ICF_VIDEOPLAYBACK                    394
#define PMD_ENVIRONMENT_VAR_ID_ICF_VOICE_RECORDING                  395
#define PMD_ENVIRONMENT_VAR_ID_ICF_VOICE_TAGS                       396
#define PMD_ENVIRONMENT_VAR_ID_ICF_VRR_SERV                         397
#define PMD_ENVIRONMENT_VAR_ID_ICF_XBUS_LIB                         398
#define PMD_ENVIRONMENT_VAR_ID_ICF_ZLIB_LIB                         399
/* example_isa_core_product_conf.h #31 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_BATT_CURRENT_MEASUREMENT         400
/* example_isa_core_product_conf.h #32 - No changes */
/* example_isa_core_product_conf.h #33 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_ZLIB_DEFLATE                     401
/* example_isa_core_product_conf.h #34 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_BT_FTP                           402
#define PMD_ENVIRONMENT_VAR_ID_ICF_I2C                              403
#define PMD_ENVIRONMENT_VAR_ID_ICF_OFFLINE_MODE                     404
/* example_isa_core_product_conf.h #35 - No changes */
/* example_isa_core_product_conf.h #36 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_HAC                              405
/* example_isa_core_product_conf.h #37 - No changes */
/* example_isa_core_product_conf.h #38 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SVG                              406
/* example_isa_core_product_conf.h #39 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_LOADERLESS_ADL                   407
#define PMD_ENVIRONMENT_VAR_ID_ICF_FLASH_DEVICES                    408
/* example_isa_core_product_conf.h #40 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_SIND                             409
#define PMD_ENVIRONMENT_VAR_ID_ICF_DEFAULT_BATTERY                  410
/* example_isa_core_product_conf.h #41 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_ISC_API                          411 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_WSM                              412 /* Obsolete */
/* example_isa_core_product_conf.h #42 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_WATCHDOG_SUPPORT                 413
#define PMD_ENVIRONMENT_VAR_ID_ICF_SLEEP_SUPPORT                    414
#define PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY_KEYGUARD                415
/* example_isa_core_product_conf.h #43 - No changes */
/* example_isa_core_product_conf.h #44 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_WSM_DUMMY_CRYPTO                 416 /* Obsolete */
/* example_isa_core_product_conf.h #45 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_NO_PMM_CLASS                     417
#define PMD_ENVIRONMENT_VAR_ID_ICF_RAT_DAMPS                        418 /* Obsolete */
/* example_isa_core_product_conf.h #46 - No changes */
/* example_isa_core_product_conf.h #47 - No changes */
/* example_isa_core_product_conf.h #48 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_OBEX                             419
#define PMD_ENVIRONMENT_VAR_ID_ICF_MEMORY_CARD_SUPPORT              420
#define PMD_ENVIRONMENT_VAR_ID_ICF_SD_CARD_SUPPORT                  421 /* Obsolete */
/* example_isa_core_product_conf.h #49 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_OVERLAY_UI                       422
/* example_isa_core_product_conf.h #50 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_HARDCORE_SERV                    423
#define PMD_ENVIRONMENT_VAR_ID_ICF_MEMORY_CARD_HOT_SWAP             424
#define PMD_ENVIRONMENT_VAR_ID_ICF_E3_PRODUCTION_BRANCH             425
/* example_isa_core_product_conf.h #51 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_JSR82_SUPPORT                    426
/* example_isa_core_product_conf.h #52 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_HAL_ONLY                         427
/* example_isa_core_product_conf.h #53 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_VIBRA                            428
#define PMD_ENVIRONMENT_VAR_ID_ICF_VIBRA_IF_NEW                     429
#define PMD_ENVIRONMENT_VAR_ID_ICF_DISCO_LIGHTS                     430
#define PMD_ENVIRONMENT_VAR_ID_ICF_OBEX_SERVER_MAX_FRAME_SIZE       431
#define PMD_ENVIRONMENT_VAR_ID_IUF_LCIF                             432
/* example_isa_core_product_conf.h #54 - No changes */
/* example_isa_core_product_conf.h #55 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_PICT_BRIDGE                      433
#define PMD_ENVIRONMENT_VAR_ID_ICF_USB_FLASHING                     434
/* example_isa_core_product_conf.h #56 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_RF_BAND_VARIABILITY              435
#define PMD_ENVIRONMENT_VAR_ID_ICF_MULTIPART_ADDRESS_SUPPORT        436
/* example_isa_core_product_conf.h #57 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_POWER_ON_BOOT_LOGO               437
#define PMD_ENVIRONMENT_VAR_ID_ICF_AVE                              438 /* Obsolete */
/* example_isa_core_product_conf.h #58 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_STEREO_IHF                       439
#define PMD_ENVIRONMENT_VAR_ID_ICF_EAP                              440
/* example_isa_core_product_conf.h #59 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_HS23_SUPPORT                     441
/* example_isa_core_product_conf.h #60 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_FMM_LIB                          442
/* example_isa_core_product_conf.h #61 - No changes */
/* example_isa_core_product_conf.h #62 */
#define PMD_ENVIRONMENT_VAR_ID_ICF_UNIVERSAL_HEADSET                443
#define PMD_ENVIRONMENT_VAR_ID_ICF_UNIVERSAL_STEREO                 444
#define PMD_ENVIRONMENT_VAR_ID_ICF_3_5MM_AUDIO_PLUG                 445
#define PMD_ENVIRONMENT_VAR_ID_ICF_FBUS_ROUTING_SUPPORT             446
#define PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_CALL                       447
#define PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_SHARING                    448
#define PMD_ENVIRONMENT_VAR_ID_ICF_CONTACT_BIRTHDAY                 449 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_CONTACT_FORMATTED_NAME           450 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_CONTACT_NICKNAME                 451 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_CONTACT_TITLE_ORG                452 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_DUAL_OS                          453
#define PMD_ENVIRONMENT_VAR_ID_ICF_CDMA_MOD                         455 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_RAT_CDMA                         456
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_FBUS                    457
#define PMD_ENVIRONMENT_VAR_ID_ICF_WLAN                             458
#define PMD_ENVIRONMENT_VAR_ID_ICF_WLAN_DRV                         459
#define PMD_ENVIRONMENT_VAR_ID_ICF_NAVIGATOR                        460 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_ICF_LOADER                           461
#define PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MADI                    462
#define PMD_ENVIRONMENT_VAR_ID_ICF_SOS_PROXY                        463
#define PMD_ENVIRONMENT_VAR_ID_ICF_TUNEPLAYER_SERV                  464
#define PMD_ENVIRONMENT_VAR_ID_ICF_IKE                              465
#define PMD_ENVIRONMENT_VAR_ID_ICF_SSL                              466
#define PMD_ENVIRONMENT_VAR_ID_ICF_FEATURE_CONTROL                  467
#define PMD_ENVIRONMENT_VAR_ID_ICF_BCS_SERV                         468
#define PMD_ENVIRONMENT_VAR_ID_ICF_STORAGE_EMMC_SUPPORT             469
#define PMD_ENVIRONMENT_VAR_ID_ICF_SYSTEM_EMMC_SUPPORT              470
#define PMD_ENVIRONMENT_VAR_ID_ICF_NOKIA_VIRTUAL_SURROUND           471
#define PMD_ENVIRONMENT_VAR_ID_ICF_USB_ACA_SUPPORT                  472
#define PMD_ENVIRONMENT_VAR_ID_ICF_OPTIRENDER_LIB                   473
#define PMD_ENVIRONMENT_VAR_ID_ICF_POWER_RESOURCE_MANAGER           474
#define PMD_ENVIRONMENT_VAR_ID_ICF_ENO_PROTOCOL_SUPPORT             475

#define PMD_ENVIRONMENT_VAR_ID_ICF_LAST                             475

#define PMD_ENVIRONMENT_VAR_ID_ICF_MAX (PMD_ENVIRONMENT_VAR_ID_ICF_LAST - PMD_ENVIRONMENT_VAR_ID_ICF_FIRST + 1)

/* ------------------------------------------------------------------------- */
/* ISA protocols flags */
/* ------------------------------------------------------------------------- */

#define PMD_ENVIRONMENT_VAR_ID_IPF_FIRST                            600

#define PMD_ENVIRONMENT_VAR_ID_IPF_3GPP_SPEC_RELEASE                600
#define PMD_ENVIRONMENT_VAR_ID_IPF_A5_1                             601 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_A5_2                             602 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_A5_3                             603 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_A5_4                             604 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_A5_5                             605 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_A5_6                             606 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_A5_7                             607 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_ALS                              608
#define PMD_ENVIRONMENT_VAR_ID_IPF_AOC                              609 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_AOC_VOLUME_BASED                 610 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_AUTO_QMEAS_IN_RANDOM_ACCESS      611
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_E_GSM                       612 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_450                     613
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_480                     614
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_700                     615
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_850                     616
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_900                     617
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_1800                    618
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_1900                    619
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_R_GSM                       620 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_UMTS_REGION_A               621 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_BAND_UMTS_REGION_B               622 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_BEARER_CONTROL                   623 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_BTS_TEST                         624
#define PMD_ENVIRONMENT_VAR_ID_IPF_BTS_TEST_WITH_NMEAS              625
#define PMD_ENVIRONMENT_VAR_ID_IPF_CALL_DEFLECTION                  626 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CALL_HOLD                        627
#define PMD_ENVIRONMENT_VAR_ID_IPF_CCBS                             628
#define PMD_ENVIRONMENT_VAR_ID_IPF_CDMA_RAT                         629 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CELLMO_PLATFORM                  630
#define PMD_ENVIRONMENT_VAR_ID_IPF_CLIR                             631
#define PMD_ENVIRONMENT_VAR_ID_IPF_CNAP                             632
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_AMR_FR                 633 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_AMR_HR                 634 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_AMR_WB                 635 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_EFR                    636 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_FR                     637 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_HR                     638 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_WCDMA_AMR                  639 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_WCDMA_AMR_2                640 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_WCDMA_AMR_WB               641 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_COMBINED_PSW_SYNC_MEAS           642
#define PMD_ENVIRONMENT_VAR_ID_IPF_COMMON_LARGE_MEM_BUFFER          643 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CSD_24_CHANNEL_CODING            644
#define PMD_ENVIRONMENT_VAR_ID_IPF_CSD_48_CHANNEL_CODING            645
#define PMD_ENVIRONMENT_VAR_ID_IPF_CSD_96_CHANNEL_CODING            646
#define PMD_ENVIRONMENT_VAR_ID_IPF_CSD_144_CHANNEL_CODING           647
#define PMD_ENVIRONMENT_VAR_ID_IPF_CSD_MULTISLOT_CLASS              648
#define PMD_ENVIRONMENT_VAR_ID_IPF_CTM                              649
#define PMD_ENVIRONMENT_VAR_ID_IPF_CUG                              650
#define PMD_ENVIRONMENT_VAR_ID_IPF_DCM_DRIVE_MODE                   651
#define PMD_ENVIRONMENT_VAR_ID_IPF_DCT_PLATFORM                     652
#define PMD_ENVIRONMENT_VAR_ID_IPF_DIGITAL_AFC                      653
#define PMD_ENVIRONMENT_VAR_ID_IPF_DTM                              654
#define PMD_ENVIRONMENT_VAR_ID_IPF_DTM_EGPRS_MULTISLOT_CLASS        655
#define PMD_ENVIRONMENT_VAR_ID_IPF_DTM_GPRS_MULTISLOT_CLASS         656
#define PMD_ENVIRONMENT_VAR_ID_IPF_ECSD_MULTISLOT_CLASS             657 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_ECT                              658
#define PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS                            659
#define PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_8PSK_UPLINK                660
#define PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_EXT_DYN_ALLOC              661
#define PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_MULTISLOT_CLASS            662
#define PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_POWER_CLASS                663
#define PMD_ENVIRONMENT_VAR_ID_IPF_EXT_DTM_EGPRS_MULTISLOT_CLASS    664
#define PMD_ENVIRONMENT_VAR_ID_IPF_EXT_DTM_GPRS_MULTISLOT_CLASS     665
#define PMD_ENVIRONMENT_VAR_ID_IPF_EXT_UL_TBF_NO_DUMMY_BLOCKS       666 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_FDN                              667
#define PMD_ENVIRONMENT_VAR_ID_IPF_FEATURE_CONTROL                  668
#define PMD_ENVIRONMENT_VAR_ID_IPF_FLEXIBLE_PLMN_NAME               669 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_FLOW_CTRL_UL_SINGLE_CREDIT       670 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GEA1                             671 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GEA2                             672 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GEA3                             673 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GEA4                             674 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GEA5                             675 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GEA6                             676 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GEA7                             677 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GHOST_SMS                        678 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_EXT_DYN_ALLOC               679
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_LOSSLESS_SRNS_RELOC_SUPPORT 680 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_MAC_DSP_INTERFACE           681 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_MULTISLOT_CLASS             682
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_NON_DRX_TIMER_VALUE         683
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_PDA_OPTIMIZATION            684
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_READY_TIMER_UNIT            685
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_READY_TIMER_VALUE           686
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC1144_HEADER_COMP         687
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC2507_HEADER_COMP         688
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC3095_HEADER_COMP         689
#define PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_V42BIS_DATA_COMP            690
#define PMD_ENVIRONMENT_VAR_ID_IPF_GSM_CSD                          691
#define PMD_ENVIRONMENT_VAR_ID_IPF_GSM_LCS_MS_BASED_EOTD            692
#define PMD_ENVIRONMENT_VAR_ID_IPF_GSM_LOWER_BAND_POWER_CLASS       693
#define PMD_ENVIRONMENT_VAR_ID_IPF_GSM_PS                           694
#define PMD_ENVIRONMENT_VAR_ID_IPF_GSM_RAT                          695
#define PMD_ENVIRONMENT_VAR_ID_IPF_GSM_UPPER_BAND_POWER_CLASS       696
#define PMD_ENVIRONMENT_VAR_ID_IPF_HTTP_CLIENT_PROTOCOL             698 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_HTTP_SERVER_PROTOCOL             699 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_IMPS                             700 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_IPV6                             701
#define PMD_ENVIRONMENT_VAR_ID_IPF_ISA2_ADAPTATION                  702 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_ISA_PLATFORM                     703
#define PMD_ENVIRONMENT_VAR_ID_IPF_LCS                              704 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_LCS_AGPS                         705 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_LCS_EOTD                         706
#define PMD_ENVIRONMENT_VAR_ID_IPF_LCS_MO_LR                        707
#define PMD_ENVIRONMENT_VAR_ID_IPF_LCS_PRIVACY                      708
#define PMD_ENVIRONMENT_VAR_ID_IPF_LICENSE_BLOCK_OPTIMIZATION       709
#define PMD_ENVIRONMENT_VAR_ID_IPF_MAX_PDP_CONTEXTS                 710
#define PMD_ENVIRONMENT_VAR_ID_IPF_MPTY                             711
#define PMD_ENVIRONMENT_VAR_ID_IPF_MS_INIT_PDP_CONTEXT_MODIFICATION 712
#define PMD_ENVIRONMENT_VAR_ID_IPF_MULTIMEDIA_CALL                  713
#define PMD_ENVIRONMENT_VAR_ID_IPF_NITZ                             714 /* Obcolete from example_isa_prot_product_conf.h #45 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_NITZ_DAYLIGHT_TIME               715 /* Obcolete from example_isa_prot_product_conf.h #45 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_NO_MDI_DEACTIVATE_WHEN_SUSPEND   716 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_NOKIA_TEST_MOBILE                717
#define PMD_ENVIRONMENT_VAR_ID_IPF_NW_INIT_PDP_CONTEXT_ACTIVATION   718
#define PMD_ENVIRONMENT_VAR_ID_IPF_OFFLINE_MODE                     719
#define PMD_ENVIRONMENT_VAR_ID_IPF_PERFORMANCE_TRACES               720
#define PMD_ENVIRONMENT_VAR_ID_IPF_PERM_BTS_TEST_CARRIER            721
#define PMD_ENVIRONMENT_VAR_ID_IPF_PERM_GPRS_AUTO_ATTACH            722
#define PMD_ENVIRONMENT_VAR_ID_IPF_PERM_GSM_BANDS                   723
#define PMD_ENVIRONMENT_VAR_ID_IPF_PFC                              724
#define PMD_ENVIRONMENT_VAR_ID_IPF_POC                              725 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_POC_ACTIVE_GROUPS_MAXIMUM        726 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_POC_DIAL_OUT                     727 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_POC_LOGIN_STATUS                 728 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PPC_COUNTERS                     729
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_ADAPTIVE_MS_REV_LEVEL         730 /* Obsolete from example_isa_prot_product_conf.h #42 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_ADAPTIVE_QOS                  731 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_CELL_INFO_DISPLAY             732 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_CSD_MULTISLOT_CLASS           733
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_DTM                           734 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_GEA                           735 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_NON_3GPP_EONS                 737 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_NON_DRX_8S                    738 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_PREFERRED_PLMN_SCAN           739 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_SPEECH_CODECS                 740 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_SUPPORTED_RATS                741 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_RD_FEATURES                      742
#define PMD_ENVIRONMENT_VAR_ID_IPF_RF_POWER_CLASS_REDUCTION         743
#define PMD_ENVIRONMENT_VAR_ID_IPF_RTCP                             744 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_RTP                              745 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_RTSP                             746 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SECONDARY_PDP_CONTEXTS           747 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SIM_ATK                          748 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SIM_ATK_CALL_CONTROL             749 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SIM_ATK_ED_LOCATION_STATUS       750 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SIM_ATK_NMR                      751 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SIP                              752 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SMS_RESEND                       753
#define PMD_ENVIRONMENT_VAR_ID_IPF_SMSCB                            754
#define PMD_ENVIRONMENT_VAR_ID_IPF_SMSCB_EXT_CBCH                   755
#define PMD_ENVIRONMENT_VAR_ID_IPF_SOCKET                           756
#define PMD_ENVIRONMENT_VAR_ID_IPF_SPLIT_PG_CYCLE_CODE              757
#define PMD_ENVIRONMENT_VAR_ID_IPF_SPLIT_PG_CYCLE_ON_CCCH           758
#define PMD_ENVIRONMENT_VAR_ID_IPF_SSL                              759 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SSOM_TEST_SUITE                  760
#define PMD_ENVIRONMENT_VAR_ID_IPF_STREAMING                        761 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_TEMP_NEW_SYSTEM_LOCK_IF          762 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_UMTS_CIPHERING_INDICATION        763 /* Obcolete from example_isa_prot_product_conf.h #45 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_US_TDMA_CSD                      764 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_US_TDMA_RAT                      765 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_USER_AGENT_APPENDED_STRING       766 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_USER_AGENT_MARKUP_VERSION        767 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_USER_AGENT_PRODUCT_NAME          768 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_UUS                              769
#define PMD_ENVIRONMENT_VAR_ID_IPF_WAP_1_X                          770 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_WAP_2_X                          771 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_CSD                        772
#define PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_PS                         773
#define PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_RAT                        774
#define PMD_ENVIRONMENT_VAR_ID_IPF_WDP                              775 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_WSP                              776 /* Obsolete */
/* example_isa_prot_product_conf.h #28 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_IMS                              777
#define PMD_ENVIRONMENT_VAR_ID_IPF_CSD_AT_COMMAND_INTERPRETER       778
#define PMD_ENVIRONMENT_VAR_ID_IPF_UMA                              779
#define PMD_ENVIRONMENT_VAR_ID_IPF_WLAN_RAT                         780 /* Obsolete */
/* example_isa_prot_product_conf.h #29 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_POC_REPLAY                       781 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_POC_REPLAY_BUFFER_MAX            782 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_GERAN_FEATURE_PACKAGE_1          783
/* example_isa_prot_product_conf.h #30 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_MES                              784 /* Obsolete */
/* example_isa_prot_product_conf.h #31 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_AUTO_TX_PWR_REDUCTION         785 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CDMA_MDI_REVISION                786 /* Obsolete */
/* example_isa_prot_product_conf.h #32 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_EARLY_SERVICE_INDICATION      787 /* Obsolete */
/* example_isa_prot_product_conf.h #33 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PP_ADV_HPLMN_RECOGNITION         788 /* Obsolete */
/* example_isa_prot_product_conf.h #34 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_NEWS_DELIVERY                    789
/* example_isa_prot_product_conf.h #35 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PERM_WCDMA_BANDS                 790
/* example_isa_prot_product_conf.h #36 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_CDMA_SUPPORT_RUIM                791 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SS_CALL_ALLOWED_FEATURE          792 /* Obsolete */
/* example_isa_prot_product_conf.h #37 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_IKE                              793 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_NO_PMM_CLASS                     794 /* Obsolete */
/* example_isa_prot_product_conf.h #39 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_SIP_V2                           795 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_IMS_ISA_SERVER                   796 /* Obsolete */
/* example_isa_prot_product_conf.h #40 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_OMA_POC                          797
#define PMD_ENVIRONMENT_VAR_ID_IPF_POC_3G_DND                       798 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PREPAID_SUPPORT                  799
#define PMD_ENVIRONMENT_VAR_ID_IPF_SHORT_DATA_BURST                 800 /* Obsolete */
#define PMD_ENVIRONMENT_VAR_ID_IPF_307_2_KBPS_SUPPORT               801 /* Obsolete */
/* example_isa_prot_product_conf.h #41 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_PTT                              802 /* Obsolete */
/* example_isa_prot_product_conf.h #42 */
#define PMD_ENVIRONMENT_VAR_ID_IPF_H3G_ALWAYS_ON_PDP_CONTEXT        803
#define PMD_ENVIRONMENT_VAR_ID_IPF_CALL_SERVER_FCS_CLIENT           804
/* example_isa_prot_product_conf.h #43 - No changes */
#define PMD_ENVIRONMENT_VAR_ID_IPF_AM_SERV                          805 /* Obsolete */
/* Changed from IPF_ */
#define PMD_ENVIRONMENT_VAR_ID_INFO_PP_SECONDARY_PDP_CONTEXTS       806
#define PMD_ENVIRONMENT_VAR_ID_INFO_PP_LCS                          807
#define PMD_ENVIRONMENT_VAR_ID_INFO_PP_LCS_AGPS                     808

#define PMD_ENVIRONMENT_VAR_ID_IPF_LAST                             808

#define PMD_ENVIRONMENT_VAR_ID_IPF_MAX (PMD_ENVIRONMENT_VAR_ID_IPF_LAST - PMD_ENVIRONMENT_VAR_ID_IPF_FIRST + 1)

/* ------------------------------------------------------------------------- */
/* Monitor server / MCU trace flags */
/* ------------------------------------------------------------------------- */

#define PMD_ENVIRONMENT_VAR_ID_MON_FIRST                            1000

#define PMD_ENVIRONMENT_VAR_ID_MON_TRACE_BITMAP_ID                  PMD_ENVIRONMENT_VAR_ID_MCU_TRACE_BITMAP_ID
#define PMD_ENVIRONMENT_VAR_ID_MON_TRACE_BITMAP_LENGTH              PMD_ENVIRONMENT_VAR_ID_MCU_TRACE_BITMAP_LENGTH
#define PMD_ENVIRONMENT_VAR_ID_MON_TRACE_ENABLE                     1000
#define PMD_ENVIRONMENT_VAR_ID_MON_TRACE_STORED_ACT_USE_ONCE        1001
#define PMD_ENVIRONMENT_VAR_ID_MON_FW_TRACE_ENABLE                  1002
#define PMD_ENVIRONMENT_VAR_ID_MON_EPOC_TRACE_ENABLE                1003
#define PMD_ENVIRONMENT_VAR_ID_MON_BT_TRACE_ENABLE                  1004
#define PMD_ENVIRONMENT_VAR_ID_MON_PPC_ENABLE                       1005
#define PMD_ENVIRONMENT_VAR_ID_MON_RESET_NON_RD_DISABLE             1006
#define PMD_ENVIRONMENT_VAR_ID_MON_RBUG_ENABLE                      1007
#define PMD_ENVIRONMENT_VAR_ID_MON_STACK_INFO_ENABLE                1008
#define PMD_ENVIRONMENT_VAR_ID_MON_TRACE_INFO_SUPPORT               1009
#define PMD_ENVIRONMENT_VAR_ID_MON_STI_TRACE_TIMESTAMP_SB_ENABLE    1010
#define PMD_ENVIRONMENT_VAR_ID_MON_TRACE_ANY_GROUP_ENABLED_CHECK    1011
#define PMD_ENVIRONMENT_VAR_ID_MON_STI_TRACE_BUF_AMOUNT             1012

#define PMD_ENVIRONMENT_VAR_ID_MON_LAST                             1012

#define PMD_ENVIRONMENT_VAR_ID_MON_MAX (PMD_ENVIRONMENT_VAR_ID_MON_LAST - PMD_ENVIRONMENT_VAR_ID_MON_FIRST + 1)

/* ------------------------------------------------------------------------- */
/* Symbian variables                                                         */
/* ------------------------------------------------------------------------- */

#define PMD_ENVIRONMENT_VAR_ID_SOS_FIRST                            1100

#define PMD_ENVIRONMENT_VAR_ID_SOS_MON_OBJ_ID                       1100

#define PMD_ENVIRONMENT_VAR_ID_SOS_LAST                             1100

#define PMD_ENVIRONMENT_VAR_ID_SOS_MAX (PMD_ENVIRONMENT_VAR_ID_SOS_LAST - PMD_ENVIRONMENT_VAR_ID_SOS_FIRST + 1)

#define PMD_ENVIRONMENT_VAR_ID_MAX (PMD_ENVIRONMENT_VAR_ID_ORIGINAL_MAX + \
                                    PMD_ENVIRONMENT_VAR_ID_MCU_OS_MAX + \
                                    PMD_ENVIRONMENT_VAR_ID_PRODUCT_MAX + \
                                    PMD_ENVIRONMENT_VAR_ID_ICF_MAX + \
                                    PMD_ENVIRONMENT_VAR_ID_IPF_MAX + \
                                    PMD_ENVIRONMENT_VAR_ID_MON_MAX + \
                                    PMD_ENVIRONMENT_VAR_ID_SOS_MAX)

/* enum EEnvironmentVarType */
#define PMD_ENVIRONMENT_VAR_TYPE_UNDEFINED                  0
#define PMD_ENVIRONMENT_VAR_TYPE_INTEGER                    1
#define PMD_ENVIRONMENT_VAR_TYPE_STRING                     2

/*
///<enum name="E_PMD_NUMBER_SPECIAL_TYPE">
///<not_to_be_documented/>
///<summary>This enumeration defines possible PMD field types.
///autogen determines the field type from various macros and macro arguments, so typically,
///the user should not change this field type. In special situations where this might be needed,
///the field type can be set using the property <see cref_property="PROPERTY_PMD_NUMBER_SPECIAL_TYPE"/>.
///</summary>
///[enum]
*/
#define PMD_NUMBER_SPECIAL_TYPE_NONE                         0 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_MEDIA                 1 /* <summary>Media field in PhoNet header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_RECEIVER_DEVICE       2 /* <summary>Receiver device ID field in PhoNet header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_SENDER_DEVICE         3 /* <summary>Sender device ID field in PhoNet header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_RESOURCE              4 /* <summary>Resource ID field in PhoNet header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_LENGTH                5 /* <summary>PhoNet length field PhoNet header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_RECEIVER_OBJECT       6 /* <summary>Receiver object ID field in PhoNet header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_SENDER_OBJECT         7 /* <summary>Sender object ID field in PhoNet header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_TRANSACTION_ID               8 /* <summary>Transaction ID field. Present in ISI message only</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_RAW_DATA                     9 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE       10 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_OBJECT       11 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID                  12 /* <summary>Message ID field. Present for all types of messages</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID              13 /* <summary>Sub message ID field. Present for all types of messages</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID                14 /* <summary>Sub block ID field</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH            15 /* <summary>Sub block length field. Not present in sub block structures</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_TRACE_GROUP_ID              16 /* <summary>Trace group ID field. Present for all trace types, supporting groups</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_TRACE_ID                    17 /* <summary>Trace ID field. Present for all traces, regardless of type</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH           18 /* <summary>Trace data length field. Present for all traces types, providing length information</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PRIVATE_ID                  19 /* <summary>Private ID field. Present in all private messages</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_FTD_VALUE                   20 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PPC_VALUE                   21 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE             22 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH              23 /* <summary>Message length field. Not present for all message types</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_MCU_FUNCTION_ADDR           24 /* <summary>MCU function address field. This field contains a valid address to a function in the MCU. The function name can </summary> */
#define PMD_NUMBER_SPECIAL_TYPE_DSP_SIGNAL_ID               29 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_ACTUAL_MEDIA                32 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_TIMESTAMP                   33 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_TRACE_ENTITY_ID             34 /* <summary>Trace entity ID field. Present on certain trace types</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_RESOURCE_ID                 35 /* <summary>Resource ID field. Present in all ISI messages, based on the <b>PN_PREFIX</b> structure</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_STI_TRACE_ID                36 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_XTI_MASTER_ID               37 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_TRACE_MASTER_ID             38 /* <summary></summary> */
#define PMD_NUMBER_SPECIAL_TYPE_PRINTF_ID                   39 /* <summary>Trace type supporting printf macro functionality</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_OST_LENGTH_SHORT            40 /* <summary>OST short length field</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_OST_LENGTH_EXTENDED         41 /* <summary>OST extended length field</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_OST_VERSION                 42 /* <summary>OST version field in Ost header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_OST_ENTITY_ID               43 /* <summary>OST entity ID field in Ost header</summary> */
#define PMD_NUMBER_SPECIAL_TYPE_OST_PROTOCOL_ID             44 /* <summary>OST protocol ID field in Ost header</summary> */

#define PMD_NUMBER_SPECIAL_TYPE_MIN                         0
#define PMD_NUMBER_SPECIAL_TYPE_MAX                         45
/*
///</enum>
*/

/* constants for CIndexSequenceOf */
#define PMD_INDEX_SEQUENCE_OF_SHOW_ROW_RULE_ALL             0
#define PMD_INDEX_SEQUENCE_OF_SHOW_ROW_RULE_VALUE           1
#define PMD_INDEX_SEQUENCE_OF_SHOW_ROW_RULE_NON_VALUE       2


/* ----------------------------------------------------------------------- */
/* Object flags */
/* ----------------------------------------------------------------------- */

/* flags for blocks, forwarding data to external decode modules (DLL's) */
#define PMD_BLOCK_EXT_DECODER_SEND_WHOLE_EMBEDDED_MESSAGE   0x00000001
#define PMD_BLOCK_EXT_DECODER_SKIP_IDENTIFIER               0x00000002
#define PMD_BLOCK_EXT_DECODER_SKIP_TRACE_NAME               0x00000004
#define PMD_BLOCK_EXT_DECODER_SEND_FROM_TRACE_START         0x00000008

/* flags for blocks, containing embedded PhoNet messages */
#define PMD_BLOCK_PN_MSG_SKIP_TRACE_NAME                    0x00000001

/* flags for choices */
#define PMD_CHOICE_ENTRY_POINT                              0x00000001

/* flags for parameters */
#define PMD_PARAMETER_RDD_COMMAND                           0x00000001
#define PMD_PARAMETER_RDD_STATIC                            0x00000002
#define PMD_PARAMETER_IS_PART_OF_SET                        0x00000004

/* flags for message types */
#define PMD_MESSAGE_TYPE_FLAG_DSP5_USE_2_BIT_PER_TRACE      0x00000001
#define PMD_MESSAGE_TYPE_FLAG_IS_TRACE                      0x00000002
#define PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE                    0x00000004

/* flags for message entities */
#define PMD_MESSAGE_ENTITY_FLAG_DSP5_USE_2_BIT_PER_TRACE    PMD_MESSAGE_TYPE_FLAG_DSP5_USE_2_BIT_PER_TRACE
#define PMD_MESSAGE_ENTITY_FLAG_IS_TRACE                    PMD_MESSAGE_TYPE_FLAG_IS_TRACE
#define PMD_MESSAGE_ENTITY_FLAG_IS_MESSAGE                  PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE

/* flags for FTD data (info objects) */
#define PMD_FTD_IS_INPUT                                    0x00000001
#define PMD_FTD_IS_STATIC                                   0x00000002

#define PMD_FTD_MODE_RD                                     0x00001000
#define PMD_FTD_MODE_INFRA                                  0x00002000
#define PMD_FTD_MODE_OPERATOR                               0x00004000

#define PMD_FTD_MODE_ANY                                   (PMD_FTD_MODE_RD | PMD_FTD_MODE_INFRA | PMD_FTD_MODE_OPERATOR)

/*
///<enum name="E_DSP5_TRACE_SOURCE_FLAGS">
///<reviewed_ok/>
///<summary>These flags are used on trace source objects. They affect the DSP5 trace activation in e.g. FastTrace.</summary>
///[enum]
*/
#define PMD_TRACE_SOURCE_FLAG_DSP5_USE_2_BIT_PER_TRACE      PMD_MESSAGE_TYPE_FLAG_DSP5_USE_2_BIT_PER_TRACE /* <summary>When this flag is set on a DSP5 trace source, 2-bits are used per trace in the trace activation bitmap for the source. One bit is on/off and one is extended/short. Default, only one bit is used per trace (on/off).</summary> */
/*
///</enum>
*/

/* flags for number types */
#define PMD_NUMBER_IS_SIGNED                                0x00000001
#define PMD_NUMBER_HAS_DEFAULT_VALUE                        0x00000002

/* flags for string types */
#define PMD_STRING_IS_NULL_TERMINATED                       0x00000001
#define PMD_STRING_LENGTH_IN_BYTES                          0x00000002
#define PMD_STRING_IS_FTD_DATA                              0x00000004
#define PMD_STRING_HAS_BCD_MAP                              0x00000008
#define PMD_STRING_IS_UNFORMATTED                           0x00000010

/* flags for fields */
#define PMD_FIELD_IN_SUMMARY                                0x00001000
#define PMD_FIELD_IS_PARAMETER                              0x00002000

/* flags for messages / traces */
#define PMD_MESSAGE_IS_NON_FILTERABLE                       0x00000001
#define PMD_MESSAGE_IN_SUMMARY                              0x00000002
#define PMD_MESSAGE_HAS_EMBEDDED_TRACES                     0x00000004
#define PMD_MESSAGE_HAS_EMBEDDED_PROTOCOL_MESSAGE           0x00000008
#define PMD_MESSAGE_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE       0x00000010
#define PMD_MESSAGE_HAS_EMBEDDED_MESSAGE                    (PMD_MESSAGE_HAS_EMBEDDED_TRACES | PMD_MESSAGE_HAS_EMBEDDED_PROTOCOL_MESSAGE | PMD_MESSAGE_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE)
#define PMD_TRACE_EXCLUDE_FROM_TRACE_ACTIVATION             0x00000020
#define PMD_TRACE_DEFAULT_STATE_ON                          0x00000040
#define PMD_TRACE_HAS_IDENTIFIER                            0x00000080
#define PMD_MESSAGE_HAS_IDENTIFIER                          PMD_TRACE_HAS_IDENTIFIER
#define PMD_MESSAGE_IS_CARRIER_MESSAGE                      0x00000100

/* flags for entry points */
#define PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES                 0x00000004
#define PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE       0x00000008
#define PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE   0x00000010
#define PMD_ENTRY_POINT_HAS_EMBEDDED_MESSAGE                (PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES | PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE | PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE)
#define PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY           0x00000020
#define PMD_ENTRY_POINT_PROTOCOL_IS_LE                      0x00000040

/* flags for devices */
#define PMD_DEVICE_IS_NOT_PHONE_DEVICE                      0x00000001
#define PMD_DEVICE_HAS_XTI_MASTER_DEVICE                    0x00000002

/* flags for condition elements */
#define PMD_CONDITION_ELEMENT_HAS_SINGLE_VALUE_INTERVAL     0x00000001

/* flags for CType objects */
#define PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN                   0x80000000

/* flags for CNumberPresentationCondition objects */
#define PMD_NUMBER_PRESENTATION_CONDITION_HAS_TAG           0x00000001

/* flags for CSequenceOf objects */
#define PMD_SEQUENCE_OF_INCLUDE_INFO_DATA                   0x00000001
#define PMD_SEQUENCE_OF_SUB_BLOCKS                          0x00000002

/* flags for trace groups / resources */
#define PMD_TRACE_GROUP_EXCLUDE_FROM_TRACE_ACTIVATION       0x00000020
#define PMD_TRACE_GROUP_DEFAULT_STATE_ON                    0x00000040
#define PMD_RESOURCE_HAS_CONFLICTING_MESSAGES               0x00000080


/* ----------------------------------------------------------------------- */
/* CInfo classes */
/* ----------------------------------------------------------------------- */

#define PMD_INFO_TYPE_NONE                                       0

#define PMD_INFO_TYPE_OS_TASK_MCU                                1
 #define PMD_INFO_ATTR_OS_TASK_MCU_PRIORITY                       0
 #define PMD_INFO_ATTR_OS_TASK_MCU_STACK_SIZE                     1
 #define PMD_INFO_ATTR_OS_TASK_MCU_STACK_ADDRESS                  2
 #define PMD_INFO_ATTR_OS_TASK_MCU_MAIL_BOX_LENGTH                3
 #define PMD_INFO_ATTR_OS_TASK_MCU_FAST_MESSAGE_MAIL_BOX_LENGTH   4
 #define PMD_INFO_ATTR_OS_TASK_MCU_COUNT						  5

#define PMD_INFO_TYPE_OS_TIMER_MCU                               2
 #define PMD_INFO_ATTR_OS_TIMER_MCU_TYPE                          0
 #define PMD_INFO_ATTR_OS_TIMER_MCU_TASK                          1
 #define PMD_INFO_ATTR_OS_TIMER_MCU_MESSAGE                       2
 #define PMD_INFO_ATTR_OS_TIMER_MCU_COUNT                         3

#define PMD_INFO_TYPE_OS_RESOURCE_MCU                            3
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_OS_BLOCK_SET_MCU                           4
 #define PMD_INFO_ATTR_OS_BLOCK_SET_AMOUNT                        0
 #define PMD_INFO_ATTR_OS_BLOCK_SET_SIZE                          1
 #define PMD_INFO_ATTR_OS_BLOCK_SET_COUNT                         2

#define PMD_INFO_TYPE_ADSP_TASKS                                 5
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_CDSP_TASKS                                 6
#define PMD_INFO_TYPE_WCDMA_CDSP_TASKS                           PMD_INFO_TYPE_CDSP_TASKS
 #define PMD_INFO_ATTR_CDSP_TASKS_TYPE                            0
 #define PMD_INFO_ATTR_CDSP_TASKS_PRIORITY                        1
 #define PMD_INFO_ATTR_CDSP_TASKS_COUNT                           2

#define PMD_INFO_TYPE_OS_TRACE_GROUPS                            7
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_PN_OBJECTS_HOST                            8
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_PN_RESOURCES                               9
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_PN_MEDIAS                                  10
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_PN_DEVICES                                 11
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_HW_RESET_REASONS                           12
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_OS_ERROR_CODES_MCU                         13
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_OS_TASK_STATES_MCU                         14
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS                        15
 #define PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_LAST_ADDRESS            0
 #define PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_FILENAME                1
 #define PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_COUNT                   2

#define PMD_INFO_TYPE_MCU_DEBUG_FILENAMES                        16
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS                      17
 #define PMD_INFO_ATTR_MCU_DEBUG_LINENUMBER                       0
 #define PMD_INFO_ATTR_MCU_DEBUG_COUNT                            1

#define PMD_INFO_TYPE_MCU_DEBUG_DLL_FILENAMES                    18
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS_SHARED                 19
 #define PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_LAST_ADDRESS_SHARED     0
 #define PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_FILENAME_SHARED         1
 #define PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_DLL_SHARED              2
 #define PMD_INFO_ATTR_MCU_DEBUG_FUNCTIONS_SHARED_COUNT           3

#define PMD_INFO_TYPE_MCU_DEBUG_FILENAMES_SHARED                 20
 #define PMD_INFO_ATTR_MCU_DEBUG_FILENAMES_DLL_SHARED             0
 #define PMD_INFO_ATTR_MCU_DEBUG_FILENAMES_SHARED_COUNT           1

#define PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS_SHARED               21
 #define PMD_INFO_ATTR_MCU_DEBUG_LINENUMBER_SHARED                0
 #define PMD_INFO_ATTR_MCU_DEBUG_LINENUMBER_DLL_SHARED            1
 #define PMD_INFO_ATTR_MCU_DEBUG_LINENUMBERS_SHARED_COUNT         2

#define PMD_INFO_TYPE_OST_PRINTF                                 22
 #define PMD_INFO_ATTR_OST_PRINTF_COMPONENTID                     0
 #define PMD_INFO_ATTR_OST_PRINTF_GROUPID                         1
 #define PMD_INFO_ATTR_OST_PRINTF_TRACEID                         2
 #define PMD_INFO_ATTR_OST_PRINTF_COUNT                           3

#define PMD_INFO_TYPE_MCU_DEBUG_VARIABLES                        23
 #define PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_LAST_ADDRESS           0
 #define PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_FILENAME               1
 #define PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_COUNT                  2

#define PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED                 24
 #define PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_LAST_ADDRESS_SHARED    0
 #define PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_FILENAME_SHARED        1
 #define PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_DLL_SHARED             2
 #define PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_SHARED_COUNT           3

#define PMD_INFO_TYPE_GROUP_1_LAST                               (PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED)
#define PMD_INFO_TYPE_GROUP_1_MAX                                (PMD_INFO_TYPE_GROUP_1_LAST + 1)

/* This whole range were used by FTD info's earlier... */

#define PMD_INFO_TYPE_GROUP_2_FIRST                              (18 + 255 + 1 + 255 + 1)

#define PMD_INFO_TYPE_PN_OBJECTS_TRACEBOX                        PMD_INFO_TYPE_GROUP_2_FIRST
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_OS_HOOKS_MCU                               (PMD_INFO_TYPE_PN_OBJECTS_TRACEBOX + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_CDSP_SIGNALS                               (PMD_INFO_TYPE_OS_HOOKS_MCU + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_ADSP_SIGNALS                               (PMD_INFO_TYPE_CDSP_SIGNALS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_PRIVATE_IDS                                (PMD_INFO_TYPE_ADSP_SIGNALS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_INVARIANT_TRACE_ENTITY_IDS                 (PMD_INFO_TYPE_PRIVATE_IDS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_PN_DEVICES_6                               (PMD_INFO_TYPE_INVARIANT_TRACE_ENTITY_IDS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_RESOURCE_IDS                               (PMD_INFO_TYPE_PN_DEVICES_6 + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_XTI_MASTER_IDS                             (PMD_INFO_TYPE_RESOURCE_IDS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_CDSP_INTERRUPTS                            (PMD_INFO_TYPE_XTI_MASTER_IDS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_CDSP_ERRORS                                (PMD_INFO_TYPE_CDSP_INTERRUPTS + 1)
 #define PMD_INFO_ATTR_CDSP_ERRORS_DESCRIPTION_ID                 0
 #define PMD_INFO_ATTR_CDSP_ERRORS_EXTRA_PARAMETER_ID             1
 #define PMD_INFO_ATTR_CDSP_ERRORS_COUNT                          2

#define PMD_INFO_TYPE_CDSP_ERROR_DESCRIPTIONS                    (PMD_INFO_TYPE_CDSP_ERRORS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_CDSP_ERROR_EXTRA_PARAMETERS                (PMD_INFO_TYPE_CDSP_ERROR_DESCRIPTIONS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_SYMBIAN_COMPONENT_IDS                      (PMD_INFO_TYPE_CDSP_ERROR_EXTRA_PARAMETERS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_PN_OBJECTS                                 (PMD_INFO_TYPE_SYMBIAN_COMPONENT_IDS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_CDSP_TRACE_ENTITY_IDS                      (PMD_INFO_TYPE_PN_OBJECTS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_ADSP_TRACE_ENTITY_IDS                      (PMD_INFO_TYPE_CDSP_TRACE_ENTITY_IDS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_VENDOR_COMPONENT_TRACE_ENTITY_IDS          (PMD_INFO_TYPE_ADSP_TRACE_ENTITY_IDS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_OST_PROTOCOL_IDS                           (PMD_INFO_TYPE_VENDOR_COMPONENT_TRACE_ENTITY_IDS + 1)
 /* No attributes for this */                                   /*0*/

#define PMD_INFO_TYPE_VENDOR_TRACE_VERSION_MASK                  (PMD_INFO_TYPE_OST_PROTOCOL_IDS + 1)
 #define PMD_INFO_ATTR_VENDOR_TRACE_MASK_SUPPLIERID               0
 #define PMD_INFO_ATTR_VENDOR_TRACE_MASK_LENGTH                   1
 #define PMD_INFO_ATTR_VENDOR_TRACE_MASK_DATA1                    2
 #define PMD_INFO_ATTR_VENDOR_TRACE_MASK_DATA2                    3
 #define PMD_INFO_ATTR_VENDOR_TRACE_MASK_COUNT                    4

#define PMD_INFO_TYPE_VENDOR_CRASH_DUMP                          (PMD_INFO_TYPE_VENDOR_TRACE_VERSION_MASK + 1)
 #define PMD_INFO_TYPE_VENDOR_CRASH_DUMP_SUPPLIERID               0
 #define PMD_INFO_TYPE_VENDOR_CRASH_DUMP_SUBINDENT                1
 #define PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FN_INDEX                 2
 #define PMD_INFO_ATTR_VENDOR_CRASH_DUMP_COUNT                    3

#define PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME             (PMD_INFO_TYPE_VENDOR_CRASH_DUMP + 1)
 #define PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME_SUPPLIERID  0
 #define PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME_FN_INDEX    1
 #define PMD_INFO_ATTR_VENDOR_CRASH_DUMP_FUNCTIONNAME_COUNT       2

#define PMD_INFO_TYPE_GROUP_2_LAST                               (PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME)
#define PMD_INFO_TYPE_GROUP_2_MAX                                (PMD_INFO_TYPE_GROUP_2_LAST - PMD_INFO_TYPE_GROUP_2_FIRST + 1)


#define PMD_INFO_TYPE_MAX                                        (PMD_INFO_TYPE_GROUP_1_MAX + PMD_INFO_TYPE_GROUP_2_MAX)



/* sum of all attributes for all types */
#define PMD_INFO_ATTR_COUNT										 (PMD_INFO_ATTR_OS_TASK_MCU_COUNT + \
                                                                  PMD_INFO_ATTR_OS_TIMER_MCU_COUNT + \
                                                                  PMD_INFO_ATTR_OS_BLOCK_SET_COUNT + \
                                                                  PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_COUNT + \
                                                                  PMD_INFO_ATTR_MCU_DEBUG_COUNT + \
                                                                  PMD_INFO_ATTR_MCU_DEBUG_FUNCTIONS_SHARED_COUNT + \
                                                                  PMD_INFO_ATTR_MCU_DEBUG_FILENAMES_SHARED_COUNT + \
                                                                  PMD_INFO_ATTR_MCU_DEBUG_LINENUMBERS_SHARED_COUNT + \
                                                                  PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_COUNT + \
                                                                  PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_SHARED_COUNT + \
                                                                  PMD_INFO_ATTR_OST_PRINTF_COUNT + \
                                                                  PMD_INFO_ATTR_CDSP_TASKS_COUNT + \
                                                                  PMD_INFO_ATTR_CDSP_ERRORS_COUNT + \
                                                                  PMD_INFO_ATTR_VENDOR_TRACE_MASK_COUNT + \
                                                                  PMD_INFO_ATTR_VENDOR_CRASH_DUMP_COUNT) + \
                                                                  PMD_INFO_ATTR_VENDOR_CRASH_DUMP_FUNCTIONNAME_COUNT

/* ----------------------------------------------------------------------- */
/* Device info */
/* ----------------------------------------------------------------------- */

/* Used for objects that do not belong to specific device */
#define PMD_DEVICE_GENERAL                                      0xFFFF

/* ----------------------------------------------------------------------- */
/* Protocol info */
/* ----------------------------------------------------------------------- */

#define PMD_PROTOCOL_GROUP1_FIRST                               0x0000
#define  PMD_PROTOCOL_PHONET                                     0x0000
#define  PMD_PROTOCOL_AI2_CMD_PACKETS                            0x0001
#define  PMD_PROTOCOL_AI2_RSP_PACKETS                            0x0002
#define  PMD_PROTOCOL_X_FILE                                     0x0003
#define  PMD_PROTOCOL_INVARIANT_TRACE                            0x0004
#define  PMD_PROTOCOL_MODEM_L1_INTERNAL_MSGS                     0x0005
#define  PMD_PROTOCOL_EUTRAN_L2_INTERNAL_MSGS                    0x0006
#define  PMD_PROTOCOL_MCU_TRACE                                  0x0007
#define  PMD_PROTOCOL_SYMBIAN_TRACE                              0x0008
#define  PMD_PROTOCOL_IPC_INTERNAL_MSGS                          0x0009
#define  PMD_PROTOCOL_MEIF_MESSAGES                              0x000A
#define  PMD_PROTOCOL_PEIF_MESSAGES                              0x000B
#define  PMD_PROTOCOL_CDSP5_TRACE								 0x000C
#define  PMD_PROTOCOL_XTI_MASTER                                 0x000D
#define  PMD_PROTOCOL_OST                                        0x000E
                                                              /* 0x000F Obsolete - PMD_PROTOCOL_OST_VERSION */
#define  PMD_PROTOCOL_RANC_MSGS                                  0x0010
#define  PMD_PROTOCOL_MACN_MSGS                                  0x0011
#define  PMD_PROTOCOL_NOA_INTERNAL_MSGS                          0x0012
#define  PMD_PROTOCOL_LS_NPE_EVENT                               0x0013
#define  PROTOCOL_NOA_APPL_INTERNAL_MSGS                         0x0014
#define PMD_PROTOCOL_GROUP1_LAST                                PROTOCOL_NOA_APPL_INTERNAL_MSGS
#define PMD_PROTOCOL_GROUP1_COUNT                               (PMD_PROTOCOL_GROUP1_LAST - PMD_PROTOCOL_GROUP1_FIRST + 1)

#define PMD_PROTOCOL_GROUP2_FIRST                               0x0020
#define  PMD_PROTOCOL_LCIF                                       0x0020
#define  PMD_PROTOCOL_GERAN_INTERNAL_MSGS                        0x0021
#define  PMD_PROTOCOL_PH_INTERNAL_MSGS                           0x0022
#define PMD_PROTOCOL_GROUP2_LAST                                PMD_PROTOCOL_PH_INTERNAL_MSGS
#define PMD_PROTOCOL_GROUP2_COUNT                               (PMD_PROTOCOL_GROUP2_LAST - PMD_PROTOCOL_GROUP2_FIRST + 1)

#define PMD_ENTRY_POINT_SUBTREE_FIRST                           0x0200
#define  PMD_ENTRY_POINT_PN_RESOURCE                             0x0200
#define  PMD_ENTRY_POINT_PN_PRIVATE                              0x0201
#define  PMD_ENTRY_POINT_PN_PREFIX                               0x0202
#define  PMD_ENTRY_POINT_PHONET_RESOURCE                         0x0203
#define  PMD_ENTRY_POINT_XTI_MASTER                              0x0204
#define  PMD_ENTRY_POINT_SYMBIAN_TRACE_ENTITY                    0x0205
#define  PMD_ENTRY_POINT_INVARIANT_TRACE_ENTITY                  0x0206
#define  PMD_ENTRY_POINT_VENDOR_COMPONENT_TRACE_ENTITY           0x0207
#define  PMD_ENTRY_POINT_CDSP5_TRACE_ENTITY                      0x0208
#define  PMD_ENTRY_POINT_ADSP5_TRACE_ENTITY                      0x0209
#define  PMD_ENTRY_POINT_OST_PROTOCOL                            0x020A
#define PMD_ENTRY_POINT_SUBTREE_LAST                            PMD_ENTRY_POINT_OST_PROTOCOL
#define PMD_ENTRY_POINT_SUBTREE_COUNT                           (PMD_ENTRY_POINT_SUBTREE_LAST - PMD_ENTRY_POINT_SUBTREE_FIRST + 1)

#define PMD_ENTRY_POINT_FIRST                                   0x0300
#define  PMD_ENTRY_POINT_MCU_TRACE                               0x0300
#define  PMD_ENTRY_POINT_INVARIANT_TRACE                         0x0301
#define  PMD_ENTRY_POINT_NOS_TRACE                               0x0302
#define  PMD_ENTRY_POINT_HAL_TRACE                               0x0303
#define  PMD_ENTRY_POINT_SYMBIAN_TRACE                           0x0304
#define  PMD_ENTRY_POINT_CDSP5_TRACE				        	 0x0305
#define  PMD_ENTRY_POINT_ADSP5_TRACE				        	 0x0306
#define  PMD_ENTRY_POINT_CDSP5_TRACE_OLD				         0x0307
#define  PMD_ENTRY_POINT_ADSP5_TRACE_OLD            	         0x0308
#define  PMD_ENTRY_POINT_MASTER_TRACE               	         0x0309
#define  PMD_ENTRY_POINT_VENDOR_COMPONENT_TRACE                  0x030A
#define  PMD_ENTRY_POINT_HSP_TRACE                               0x030B
#define  PMD_ENTRY_POINT_MASTER_HW_TRACE               	         0x030C
#define  PMD_ENTRY_POINT_LAST                                    PMD_ENTRY_POINT_MASTER_HW_TRACE
#define PMD_ENTRY_POINT_COUNT                                   (PMD_ENTRY_POINT_LAST - PMD_ENTRY_POINT_FIRST + 1)

#define PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST                  0x0400
#define PMD_ENTRY_POINT_MEDIA_CONTROLLER_LAST                   0x04FF
#define PMD_ENTRY_POINT_MEDIA_CONTROLLER_COUNT                  (PMD_ENTRY_POINT_MEDIA_CONTROLLER_LAST - PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 1)

#define PMD_ENTRY_POINT_TOTAL_COUNT                             (PMD_PROTOCOL_GROUP1_COUNT + PMD_PROTOCOL_GROUP2_COUNT + PMD_ENTRY_POINT_SUBTREE_COUNT + PMD_ENTRY_POINT_COUNT + PMD_ENTRY_POINT_MEDIA_CONTROLLER_COUNT)

#define PMD_ENTRY_POINT_UNDEFINED                                0xFFFF

/* ----------------------------------------------------------------------- */
/* Trace activation info */
/* ----------------------------------------------------------------------- */

#define PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED                 0
#define PMD_TRACE_ACTIVATION_TYPE_SHORT_EXTENDED                1
#define PMD_TRACE_ACTIVATION_TYPE_ON_OFF                        2
#define PMD_TRACE_ACTIVATION_TYPE_ON_OFF_HOOKS                  3

/*  4    MACROS */

/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

typedef struct t_pmd_constant
{
    const char* name;
    unsigned int id;
} pmd_constant;

typedef struct t_pmd_info_attr
{
    unsigned int type;
    unsigned int id;
    const char* name;
} pmd_info_attr;

typedef struct t_pmd_message_type_group_conf
{
    const char* name;
    const char* xml_name;
    const char* identifier;
    unsigned int flags;
    unsigned int id;
    unsigned short device_id;
    unsigned int message_type_id;
    unsigned int info_group_id;
    unsigned int first_type_id;
    unsigned int last_type_id;
} pmd_message_type_group_conf;

typedef struct t_pmd_message_type_conf
{
    const char* name;
    const char* xml_name;
    const char* identifier;
    unsigned int flags;
    unsigned int id;
    unsigned int activation_type;
} pmd_message_type_conf;

typedef struct t_pmd_message_info_tree_conf
{
    const char* name;
    unsigned int element_type;
    unsigned int element_id;
} pmd_message_info_tree_conf;

typedef struct t_pmd_number_special_type_conf
{
    const char* name;
    const char* xml_name;
    unsigned int id;
} pmd_number_special_type_conf;

typedef struct t_pmd_timestamp_type_conf
{
    const char* name;
    const char* xml_name;
    unsigned int id;
} pmd_timestamp_type_conf;

typedef struct t_pmd_device_type_conf
{
    const char* name;
    const char* logical_name;
    unsigned short id;
    unsigned int flags;
} pmd_device_type_conf;

typedef struct t_pmd_version_compability
{
    unsigned int version;
    unsigned int compability;
} pmd_version_compability;

extern pmd_constant pmd_constant_block_algorithm[PMD_BLOCK_ALGORITHM_MAX];
extern pmd_constant pmd_constant_entry_point[PMD_ENTRY_POINT_TOTAL_COUNT];
extern pmd_constant pmd_constant_character_type[PMD_CHARACTER_TYPE_MAX];
extern pmd_constant pmd_constant_environment_var_id[PMD_ENVIRONMENT_VAR_ID_MAX];
extern pmd_constant pmd_constant_file_type[PMD_FILE_TYPE_MAX];
extern pmd_constant pmd_constant_file_restriction[PMD_FILE_RESTRICTION_MAX];
extern pmd_constant pmd_constant_function[PMD_FUNCTION_MAX];
extern pmd_constant pmd_constant_info_type[PMD_INFO_TYPE_MAX];
extern pmd_info_attr pmd_constant_info_attributes[PMD_INFO_ATTR_COUNT];
extern pmd_constant pmd_constant_length_algorithm[PMD_LENGTH_ALGORITHM_MAX];
extern pmd_constant pmd_constant_sequence_type[PMD_SEQUENCE_TYPE_MAX];
extern pmd_message_type_group_conf pmd_constant_message_type_group[PMD_MESSAGE_TYPE_GROUP_MAX];
extern pmd_message_type_conf pmd_constant_message_type[PMD_MESSAGE_TYPE_MAX];

#define PMD_MESSAGE_INFO_TREE_ELEMENTS_MAX 27
extern pmd_message_info_tree_conf pmd_constant_message_info_tree[PMD_MESSAGE_INFO_TREE_ELEMENTS_MAX];

extern pmd_number_special_type_conf pmd_constant_number_special_type[PMD_NUMBER_SPECIAL_TYPE_MAX];
extern pmd_timestamp_type_conf pmd_constant_timestamp_type[PMD_TIMESTAMP_TYPE_MAX];

#define PMD_DEVICE_TYPE_MAX 8
extern pmd_device_type_conf pmd_constant_device_type[PMD_DEVICE_TYPE_MAX];

#define PMD_HW_RESET_TYPE_MAX 40 /* from os_trace_data.txt */
extern pmd_constant pmd_constant_hw_reset_type[PMD_HW_RESET_TYPE_MAX];

#define PMD_OS_ERROR_CODE_MAX 48 /* from os_trace_data.txt */
extern pmd_constant pmd_constant_os_error_code[PMD_OS_ERROR_CODE_MAX];

#define PMD_OS_TASK_STATE_MAX 6
extern pmd_constant pmd_constant_os_task_state[PMD_OS_TASK_STATE_MAX];

#define PMD_OS_HOOK_MAX 162 /* from os_trc_m.h */
extern pmd_constant pmd_constant_os_hook[PMD_OS_HOOK_MAX];

#define PMD_TRACEBOX_OBJECT_ID_MAX 20
extern pmd_constant pmd_constant_tracebox_object_id[PMD_TRACEBOX_OBJECT_ID_MAX];

/*  9    FUNCTION PROTOTYPES */

const char*     pmd_constant_lookup_block_algorithm(unsigned int id);
const char*     pmd_constant_lookup_character_type(unsigned int id);
const char*     pmd_constant_lookup_environment_var_id(unsigned int id);
unsigned int    pmd_constant_lookup_environment_var_id_from_name(const char* name);
const char*     pmd_constant_lookup_file_type(unsigned int id);
const char*     pmd_constant_lookup_file_restriction(unsigned int id);
const char*     pmd_constant_lookup_function(unsigned int id);
const char*     pmd_constant_lookup_info_type(unsigned int id);
unsigned int    pmd_constant_lookup_info_type_id_from_name(const char* name);
const char*     pmd_constant_lookup_info_attribute(unsigned int type, unsigned int id);
const char*     pmd_constant_lookup_length_algorithm(unsigned int id);

unsigned short  pmd_constant_lookup_entry_point_id(const char* name);
const char*     pmd_constant_lookup_entry_point(unsigned short id);

const pmd_message_type_group_conf*
                pmd_constant_lookup_message_type_group_conf_from_message_type(unsigned int id);

const pmd_message_type_group_conf*
                pmd_constant_lookup_message_type_group_conf(unsigned int id);

const char*     pmd_constant_lookup_message_type_group_name(unsigned int id);
const char*     pmd_constant_lookup_message_type_group_xml(unsigned int id);
unsigned int    pmd_constant_lookup_message_type_group_id_from_xml(const char* xml);

unsigned int    pmd_constant_lookup_message_group_first_id(unsigned int id);
unsigned int    pmd_constant_lookup_message_group_last_id(unsigned int id);

const char*     pmd_constant_lookup_message_type_name(unsigned int id);
const char*     pmd_constant_lookup_message_type_xml(unsigned int id);
const char*     pmd_constant_lookup_message_type_identifier(unsigned int id);
unsigned int    pmd_constant_lookup_message_type_flags(unsigned int id);
unsigned int    pmd_constant_lookup_message_type_activation_type(unsigned int id);
unsigned int    pmd_constant_lookup_message_type_id_from_name(const char* name);
unsigned int    pmd_constant_lookup_message_type_id_from_name_helper(const char* name, unsigned int id_first, unsigned int id_last);
unsigned int    pmd_constant_lookup_message_type_id_from_xml(const char* xml);
unsigned int    pmd_constant_lookup_message_type_id_from_xml_helper(const char* xml, unsigned int id_first, unsigned int id_last);

unsigned int    pmd_constant_lookup_message_info_tree_element_type_from_message_type(unsigned int id);
unsigned int    pmd_constant_lookup_message_info_tree_element_type_from_xml(const char* xml);

const char*     pmd_constant_lookup_number_special_type(unsigned int id);
const char*     pmd_constant_lookup_number_special_type_xml(unsigned int id);

const char*     pmd_constant_lookup_resource_type(unsigned int id);
const char*     pmd_constant_lookup_sequence_type(unsigned int id);

const char*     pmd_constant_lookup_timestamp_type(unsigned int id);
const char*     pmd_constant_lookup_timestamp_type_xml(unsigned int id);

const char*     pmd_constant_lookup_device_name(unsigned short id);
const char*     pmd_constant_lookup_device_logical_name(unsigned short id);
unsigned int    pmd_constant_lookup_device_flags(unsigned short id);

const char*     pmd_constant_lookup_hw_reset_type(unsigned int id);
const char*     pmd_constant_lookup_os_error_code(unsigned int id);
const char*     pmd_constant_lookup_os_task_state(unsigned int id);
const char*     pmd_constant_lookup_os_hook(unsigned int id);
const char*     pmd_constant_lookup_tracebox_object_id(unsigned int id);

unsigned int check_pmd_version_compatibility(unsigned int pmd_version_1, unsigned int pmd_version_2);
unsigned int pmd_version_conversion(const char *fileformat);

#ifdef __cplusplus
}
#endif

#endif /* _PMDCONSTANTS_H_ */


/*  End of file pmdconstants.h  */
