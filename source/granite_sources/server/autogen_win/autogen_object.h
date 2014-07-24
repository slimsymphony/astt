/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_object.h
                ----------------
                SW Include






Project:          autogen

%name:            autogen_object.h %
%version:         co1tss#98 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Jun  7 12:57:50 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    The file contains object definitions for the objects in the data model.
    Besides, the file contains prototypes for object creation methods, 
    deletion methods and several information retrieval methods.
*/

#ifndef _AUTOGEN_OBJECT_H_
#define _AUTOGEN_OBJECT_H_

/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"

#include <stdio.h>


/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

#define AUTOGEN_MAX_NAME_LENGTH                 100

/* Object types */
#define AUTOGEN_OBJ_UNKNOWN                     0x00000000

#define AUTOGEN_OBJ_RES                         0x00000001U
#define AUTOGEN_OBJ_MSG                         0x00000002U
#define AUTOGEN_OBJ_SB                          0x00000004U
#define AUTOGEN_OBJ_SB_TEMPLATE                 0x00000008U
#define AUTOGEN_OBJ_SEQ                         0x00000010U
#define AUTOGEN_OBJ_TBL                         0x00000020U
#define AUTOGEN_OBJ_MSGREL                      0x00000040U
#define AUTOGEN_OBJ_CONST                       0x00000080U
#define AUTOGEN_OBJ_VERSION                     0x00000100U
#define AUTOGEN_OBJ_TBLENTRY                    0x00000200U
#define AUTOGEN_OBJ_DATA                        0x00000400U
#define AUTOGEN_OBJ_ITEM                        0x00001000U
#define AUTOGEN_OBJ_REF                         0x00002000U
#define AUTOGEN_OBJ_REL                         0x00004000U
#define AUTOGEN_OBJ_DEF                         0x00008000U
#define AUTOGEN_OBJ_SHARED_FILE                 0x00010000U
#define AUTOGEN_OBJ_NOTE                        0x00020000U
#define AUTOGEN_OBJ_TRACE                       0x00100000U
#define AUTOGEN_OBJ_TRACEGRP                    0x00200000U
#define AUTOGEN_OBJ_EMBEDDED_FILE               0x00400000U
#define AUTOGEN_OBJ_ENV_CONST                   0x00800000U
#define AUTOGEN_OBJ_MSG_ID_SECTION              0x01000000U
#define AUTOGEN_OBJ_VERSION_HISTORY             0x02000000U
#define AUTOGEN_OBJ_SB_ID_SECTION               0x04000000U
#define AUTOGEN_OBJ_PMD_INFO_ATTR               0x08000000U
#define AUTOGEN_OBJ_OLD_MACRO_USAGE             0x10000000U
#define AUTOGEN_OBJ_MSG_BASE                    0x20000000U

#define AUTOGEN_OBJ_SEQ_ANY                    (AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SB_TEMPLATE | AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_TRACE)

#define AUTOGEN_OBJ_ANY                         0xFFFFFFFF

/* Flags */
/* ----------------------------------------------------- */
/* 0xXXX-----: common object flags */
/* 0x---XXXXX: object specific flags */


/* common flags for all objects */
#define AUTOGEN_OBJ_IS_PMD_RD                   0x00100000U
#define AUTOGEN_OBJ_IS_PMD_PUBLIC               0x00200000U
#define AUTOGEN_OBJ_IS_PMD_RESTRICTED           0x00400000U

#define AUTOGEN_OBJ_IS_SHARED                   0x01000000U /* Object is placed in shared file */
#define AUTOGEN_OBJ_IS_SHARED_EXTERNAL          0x02000000U /* Object is placed in shared file, 
                                                               not owned by this resoure */
#define AUTOGEN_OBJ_IS_NOT_GENERATED_PMD        0x04000000U
#define AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_8   0x08000000U
#define AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_16  0x10000000U
#define AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR    (AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_8 | \
                                                AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_16)
#define AUTOGEN_OBJ_IS_NOT_GENERATED_HTML       0x20000000U
#define AUTOGEN_OBJ_IS_LEGACY                   0x40000000U /* Object is legacy, placed in separate file */

#define AUTOGEN_OBJ_COMMON_FLAGS_ALL            0xFFF00000U


#define AUTOGEN_PMD_FILE_RESTRICTION_RD         (AUTOGEN_OBJ_IS_PMD_RD)
#define AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC     (AUTOGEN_OBJ_IS_PMD_PUBLIC)
#define AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED (AUTOGEN_OBJ_IS_PMD_RESTRICTED)

#define AUTOGEN_PMD_FILE_RESTRICTION_NON_RD     (AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC | AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED)
#define AUTOGEN_PMD_FILE_RESTRICTION_ANY        (AUTOGEN_PMD_FILE_RESTRICTION_NON_RD | AUTOGEN_PMD_FILE_RESTRICTION_RD)

/* flags for type AUTOGEN_OBJ_RES */
#define AUTOGEN_RES_HAS_EXTENSIONS              0x00000001U
#define AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES    0x00000002U
#define AUTOGEN_RES_HAS_ANY_SIZE_CONSTANT       0x00000004U
#define AUTOGEN_RES_IS_DUPLICATE                0x00000008U
#define AUTOGEN_RES_HAS_NO_MESSAGES             0x00000020U /* Single message with one structure defines entire protocol */
#define AUTOGEN_RES_IS_LEGACY                   0x00000040U /* To indicate legacy part of resource */
#define AUTOGEN_RES_TRC_IS_HW_MASTER            0x00000080U /* To indicate that RESOURCE_TRC_MASTER specifies a HW Master trace */

/* sub types for type AUTOGEN_OBJ_EMBEDDED_FILE */
#define AUTOGEN_EMBEDDED_FILE_INFO              0x00000001U
#define AUTOGEN_EMBEDDED_FILE_PMD               0x00000002U

/* sub types for type AUTOGEN_OBJ_DEF */
#define AUTOGEN_DEF_NAME                        0x00000001U
#define AUTOGEN_DEF_CONST                       0x00000002U

#define AUTOGEN_DEF_ANY                         0xFFFFFFFF

/* sub types for type AUTOGEN_OBJ_TRACEGRP */
 /* Are defined in autogen_def.h */

/* flags for type AUTOGEN_OBJ_TRACEGRP */
#define AUTOGEN_TRACEGRP_TEMPORARY_GROUP        0x00000001U

/* sub types for type AUTOGEN_OBJ_VERSION_HISTORY */
#define AUTOGEN_VERSION_HISTORY_OBJECT_ADDED                        0x00000001U
#define AUTOGEN_VERSION_HISTORY_OBJECT_DISCONTINUED                 0x00000002U
#define AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED                      0x00000004U
#define AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_COMPATIBLE           0x00000008U
#define AUTOGEN_VERSION_HISTORY_OBJECT_REINTRODUCED                 0x00000010U
#define AUTOGEN_VERSION_HISTORY_FILLER_REPLACED                     0x00000020U
#define AUTOGEN_VERSION_HISTORY_OBJECT_MOVED_TO_SHARED_FILE         0x00000040U
#define AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_CONST_TBL_TO_BIT_TBL 0x00000080U
#define AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_BIT_TBL_TO_CONST_TBL 0x00000100U


/* sub types for type AUTOGEN_OBJ_MSG */
#define AUTOGEN_MSG_ANY                         0xFFFFFFFF

/* flags for type AUTOGEN_OBJ_MSG */
#define AUTOGEN_MSG_REQ                         0x00000001U
#define AUTOGEN_MSG_RESP                        0x00000002U
#define AUTOGEN_MSG_IND                         0x00000004U
#define AUTOGEN_MSG_NTF                         0x00000008U
#define AUTOGEN_MSG_TRC                         0x00000010U

#define AUTOGEN_MSG_TRC_STI                     0x00000020U

#define AUTOGEN_MSG_FUNCTION_MASK              (AUTOGEN_MSG_REQ | \
                                                AUTOGEN_MSG_RESP | \
                                                AUTOGEN_MSG_IND | \
                                                AUTOGEN_MSG_NTF | \
                                                AUTOGEN_MSG_TRC)

#define AUTOGEN_MSG_IS_SUBMSG                   0x00000100U
#define AUTOGEN_MSG_BASE_IS_USER_DEFINED        0x00000200U
#define AUTOGEN_MSG_BASE_IS_AUTO_DEFINED        0x00000400U
#define AUTOGEN_MSG_IS_MM_SPECIFIC              0x00000800U
#define AUTOGEN_MSG_HAS_NO_ELEMENTS             0x00001000U
#define AUTOGEN_MSG_IS_PUBLIC                   0x00002000U
#define AUTOGEN_MSG_IS_PROTOCOL                 0x00004000U

/* flags for type AUTOGEN_OBJ_SB */

#define AUTOGEN_SB_IS_TRACE                     0x00000001

#define AUTOGEN_SB_ANY                          0xFFFFFFFF




/* sub types for type AUTOGEN_OBJ_SB_TEMPLATE */
#define AUTOGEN_SB_TEMPLATE_FTD                 0x00000001U
#define AUTOGEN_SB_TEMPLATE_PPC                 0x00000002U
#define AUTOGEN_SB_TEMPLATE_SOS                 0x00000004U

#define AUTOGEN_SB_TEMPLATE_ANY                 0xFFFFFFFF


/* sub types for type AUTOGEN_OBJ_SEQ */
#define AUTOGEN_SEQ_ANY                         0xFFFFFFFF


/* Flags for sequences */
/* ----------------------------------------------------- */
/* 0xXXX-----: common object flags */
/* 0x---X----: common sequence flags */
/* 0x----XXXX: object specific flags */

/* common flags for 
    AUTOGEN_OBJ_SEQ
    AUTOGEN_OBJ_SB 
    AUTOGEN_OBJ_SB_TEMPLATE
    AUTOGEN_OBJ_MSG
*/
#define AUTOGEN_SEQ_IS_DYNAMIC                  0x00010000U
#define AUTOGEN_SEQ_HAS_ASMANYASPOSSIBLE        0x00020000U
#define AUTOGEN_SEQ_HAS_UNKNOWN_LENGTH          0x00040000U
#define AUTOGEN_SEQ_IS_NOT_STRUCT               0x00080000U
#define AUTOGEN_SEQ_IS_TEMPORARY                0x00100000U

/* sub types for type AUTOGEN_OBJ_ENV_VAR */
#define AUTOGEN_ENV_VAR_VALUE                   0x00000001U
#define AUTOGEN_ENV_VAR_STRING                  0x00000002U

#define AUTOGEN_ENV_VAR_ANY                     0xFFFFFFFFU


/* sub types for type AUTOGEN_OBJ_ITEM */
#define AUTOGEN_ITEM_REF                        0x00000001U
#define AUTOGEN_ITEM_VALUE                      0x00000002U
#define AUTOGEN_ITEM_FILLER                     0x00000004U
#define AUTOGEN_ITEM_LST                        0x00000008U
#define AUTOGEN_ITEM_STRING                     0x00000010U
#define AUTOGEN_ITEM_STRUCT                     0x00000020U
#define AUTOGEN_ITEM_CHOICE                     0x00000040U
#define AUTOGEN_ITEM_MERGE                      0x00000080U
#define AUTOGEN_ITEM_TRCSTRUCTURE               0x00000100U
#define AUTOGEN_ITEM_BLOCK                      0x00000200U
#define AUTOGEN_ITEM_CASE                       0x00000400U
#define AUTOGEN_ITEM_TIMESTAMP                  0x00000800U
#define AUTOGEN_ITEM_POINTER                    0x00001000U
#define AUTOGEN_ITEM_RANGE                      0x00002000U
#define AUTOGEN_ITEM_RANGE_ENTRY                0x00004000U
#define AUTOGEN_ITEM_PRINTF                     0x00008000U
#define AUTOGEN_ITEM_ANY                        0xFFFFFFFFU

/* Flags for items */
/* ----------------------------------------------------- */
/* 0xXXX-----: common object flags */
/* 0x---XX---: common item flags */
/* 0x-----XXX: item specific flags */


/* general types/settings for all items */
#define AUTOGEN_ITEM_IS_FILLER_REPLACEMENT          0x00008000U
#define AUTOGEN_ITEM_USE_IMPORTED_RES               0x00010000U
#define AUTOGEN_ITEM_USE_IMPORTED_RES_NOT_RESOLVED  0x00020000U
#define AUTOGEN_ITEM_IS_PART_OF_MERGE               0x00040000U

/* offset flags for items */
#define AUTOGEN_ITEM_OFFSET_UNDEFINED           0x00000000U
#define AUTOGEN_ITEM_OFFSET_EXACT               0x00000001U
#define AUTOGEN_ITEM_OFFSET_EXACT_UNALIGNED     0x00000002U
#define AUTOGEN_ITEM_OFFSET_VARIABLE            0x00000003U

/* types/settings for item AUTOGEN_ITEM_CONST */
#define AUTOGEN_CONST_IMPORT                    0x00000001U


/* types/settings for item AUTOGEN_ITEM_TIMESTAMP */
#define AUTOGEN_TIMESTAMP_UNKNOWN               0x00000000U
#define AUTOGEN_TIMESTAMP_OSTRICH               0x00000001U
#define AUTOGEN_TIMESTAMP_OS_TICKS              0x00000002U
#define AUTOGEN_TIMESTAMP_DSP5                  0x00000004U
#define AUTOGEN_TIMESTAMP_GSM_FRAME             0x00000008U

/* types/settings for item AUTOGEN_ITEM_REF */
#define AUTOGEN_REF_CONST                       0x00000002U

/* types/settings for item AUTOGEN_ITEM_FILLER */
#define AUTOGEN_FILLER_0_BYTES_POSSIBLE         0x00000001U
#define AUTOGEN_FILLER_1_BYTES_POSSIBLE         0x00000002U
#define AUTOGEN_FILLER_2_BYTES_POSSIBLE         0x00000004U
#define AUTOGEN_FILLER_3_BYTES_POSSIBLE         0x00000008U
#if (PMD_FILE_FORMAT >= 600)
#define AUTOGEN_FILLER_4_BYTES_POSSIBLE         0x00000010U
#define AUTOGEN_FILLER_5_BYTES_POSSIBLE         0x00000020U
#define AUTOGEN_FILLER_6_BYTES_POSSIBLE         0x00000040U
#define AUTOGEN_FILLER_7_BYTES_POSSIBLE         0x00000080U

#endif

#define AUTOGEN_FILLER_0_OR_1_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_1_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_OR_2_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_OR_3_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_1_OR_2_BYTES            (AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_1_OR_3_BYTES            (AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_TO_2_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_TO_3_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_1_TO_3_BYTES            (AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE)

#if (PMD_FILE_FORMAT >= 600)
#define AUTOGEN_FILLER_0_OR_2_OR_4_OR_6_BYTES  (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_4_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_6_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_1_OR_3_OR_5_OR_7_BYTES  (AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_5_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_7_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_OR_4_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_4_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_TO_4_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_4_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_TO_5_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_4_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_5_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_TO_6_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_4_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_5_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_6_BYTES_POSSIBLE)

#define AUTOGEN_FILLER_0_TO_7_BYTES            (AUTOGEN_FILLER_0_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_1_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_2_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_3_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_4_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_5_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_6_BYTES_POSSIBLE | \
                                                AUTOGEN_FILLER_7_BYTES_POSSIBLE)

#endif

#define AUTOGEN_FILLER_VAR_AUTONAME             0x00000100U
#define AUTOGEN_FILLER_IS_REPLACED              0x00000200U


/* flags for item AUTOGEN_ITEM_BLOCK */

#define AUTOGEN_BLOCK_PN_MSG_SKIP_TRACE                 PMD_BLOCK_PN_MSG_SKIP_TRACE_NAME /* 0x00000001U */

#define AUTOGEN_BLOCK_EXT_DECODER_SEND_WHOLE_EMB_MSG    PMD_BLOCK_EXT_DECODER_SEND_WHOLE_EMBEDDED_MESSAGE /* 0x00000001U */
#define AUTOGEN_BLOCK_EXT_DECODER_SKIP_ID               PMD_BLOCK_EXT_DECODER_SKIP_IDENTIFIER /* 0x00000002U */
#define AUTOGEN_BLOCK_EXT_DECODER_SKIP_TRACE            PMD_BLOCK_EXT_DECODER_SKIP_TRACE_NAME /* 0x00000004U */
 
/* types/settings for item AUTOGEN_ITEM_LST */
#define AUTOGEN_LST_SB                          0x00000001U
#define AUTOGEN_LST_FTD                         0x00000002U
#define AUTOGEN_LST_PPC                         0x00000004U
#define AUTOGEN_LST_AS_PARAMETERS               0x00000008U
#define AUTOGEN_LST_SBID                        0x00000010U
#define AUTOGEN_LST_SBDATA                      0x00000020U

#define AUTOGEN_LST_SB_HAVE_BYTE_IDS            0x00000040U
#define AUTOGEN_LST_SB_HAVE_WORD_IDS            0x00000080U

#define AUTOGEN_LST_SOS_FTD                     0x00000100U

/* types/settings for item AUTOGEN_ITEM_STRING */
#define AUTOGEN_STRING_ASCII                    0x00000001U
#define AUTOGEN_STRING_UNICODE                  0x00000002U
#define AUTOGEN_STRING_BCD                      0x00000004U
#define AUTOGEN_STRING_UTF8                     0x00000008U
#define AUTOGEN_STRING_GSM                      0x00000010U

#define AUTOGEN_STRING_ZERO_TERMINATED          0x00000020U


/* types/settings for item AUTOGEN_ITEM_STRUCT */
#define AUTOGEN_STRUCT_SB                       0x00000001U
#define AUTOGEN_STRUCT_SEQ                      0x00000002U

/* types/settings for item AUTOGEN_ITEM_RANGE_ENTRY */
#define AUTOGEN_RANGE_ENTRY_STRING              0x00000001U
#define AUTOGEN_RANGE_ENTRY_VALUE               0x00000002U
#define AUTOGEN_RANGE_ENTRY_VALUE_EX            0x00000004U

/* types/settings for item AUTOGEN_ITEM_POINTER */
#define AUTOGEN_POINTER_VOID                    0x00000001U
#define AUTOGEN_POINTER_INT32                   0x00000002U
#define AUTOGEN_POINTER_UINT32                  0x00000004U
#define AUTOGEN_POINTER_INT16                   0x00000008U
#define AUTOGEN_POINTER_UINT16                  0x00000010U
#define AUTOGEN_POINTER_INT8                    0x00000020U
#define AUTOGEN_POINTER_UINT8                   0x00000040U
#define AUTOGEN_POINTER_INT64                   0x00000080U
#define AUTOGEN_POINTER_UINT64                  0x00000100U


/* types/settings for item AUTOGEN_ITEM_CHOICE */
#define AUTOGEN_CHOICE_FORWARD                  0x00000001U

#define AUTOGEN_CHOICE_REFERENCE_VALUE          0x00000002U
#define AUTOGEN_CHOICE_REFERENCE_CONSTANT       0x00000004U
#define AUTOGEN_CHOICE_REFERENCE_BITMASK        0x00000008U
#define AUTOGEN_CHOICE_REFERENCE_INTERVAL       0x00000010U


/* types/settings for item AUTOGEN_ITEM_MERGE */


/* types/settings for item AUTOGEN_ITEM_CASE */
#define AUTOGEN_CASE_DEFAULT                    0x00000001U
#define AUTOGEN_CASE_HAS_ID                     0x00000002U

#define AUTOGEN_CASE_ANY                        0xFFFFFFFF

/* types/settings for item AUTOGEN_ITEM_PRINTF */


/* sub types for type AUTOGEN_OBJ_TBL */
#define AUTOGEN_TBL_UNKNOWN                     0x00000000U

#define AUTOGEN_TBL_CONST                       0x00000001U
#define AUTOGEN_TBL_DERCONST                    0x00000002U
#define AUTOGEN_TBL_BIT                         0x00000004U
#define AUTOGEN_TBL_DERBIT                      0x00000008U

#define AUTOGEN_TBL_DER_ANY                    (AUTOGEN_TBL_DERCONST | AUTOGEN_TBL_DERBIT)
#define AUTOGEN_TBL_CONST_ANY                  (AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT | AUTOGEN_TBL_DER_ANY)

#define AUTOGEN_TBL_FTD                         0x00000020U
#define AUTOGEN_TBL_PPC                         0x00000040U

#define AUTOGEN_TBL_ANY                         0xFFFFFFFF


/* sub types for type AUTOGEN_OBJ_DATA */
#define AUTOGEN_DATA_FTD                        0x00000001U
#define AUTOGEN_DATA_PPC                        0x00000002U

/* flags for type AUTOGEN_OBJ_DATA */
#define AUTOGEN_DATA_VALUE                      0x00000001U
#define AUTOGEN_DATA_TABLE                      0x00000002U
#define AUTOGEN_DATA_STRING                     0x00000004U
#define AUTOGEN_DATA_TEST                       0x00000008U /* Obsolete */

#define AUTOGEN_DATA_FTD_IS_INPUT_DATA          0x00000010U


#define AUTOGEN_DATA_ANY                        0xFFFFFFFF


/* sub types for type AUTOGEN_OBJ_NOTE */
#define AUTOGEN_NOTE_ANY                        0xFFFFFFFF

/* flags for type AUTOGEN_OBJ_VER */
#define AUTOGEN_VERSION_NO_LONGER_SUPPORTED         0x00000001U
#define AUTOGEN_VERSION_NOT_YET_SUPPORTED           0x00000002U

#define AUTOGEN_VERSION_HAS_COMPATIBLE_CHANGES      0x00000004U
#define AUTOGEN_VERSION_HAS_INCOMPATIBLE_CHANGES    0x00000008U

#define AUTOGEN_VERSION_ANY                     0xFFFFFFFF



/* sub types for type AUTOGEN_OBJ_TBLITEM */
#define AUTOGEN_TBLENTRY_CONST                  0x00000001U
#define AUTOGEN_TBLENTRY_DERCONST               0x00000002U
#define AUTOGEN_TBLENTRY_BIT                    0x00000004U
#define AUTOGEN_TBLENTRY_DERBIT                 0x00000008U

#define AUTOGEN_TBLENTRY_ANY                    0xFFFFFFFF


/* sub types for type AUTOGEN_OBJ_REF */
#define AUTOGEN_REF_SB                          0x00000001U

#define AUTOGEN_REF_ANY                         0xFFFFFFFF


/* sub types for type AUTOGEN_OBJ_CONST / AUTOGEN_OBJ_ENV_CONST */
#define AUTOGEN_CONST_SIGNED                    0x00000001U
#define AUTOGEN_CONST_UNSIGNED_DEC              0x00000002U
#define AUTOGEN_CONST_UNSIGNED_BYTE             0x00000004U
#define AUTOGEN_CONST_UNSIGNED_WORD             0x00000008U
#define AUTOGEN_CONST_UNSIGNED_DWORD            0x00000010U
#if (PMD_FILE_FORMAT >= 600)
#define AUTOGEN_CONST_UNSIGNED_DDWORD           0x00000020U
#endif

#define AUTOGEN_CONST_AUTOGENERATED             0x00000100U
#define AUTOGEN_CONST_DEFINED                   0x00000200U

#define AUTOGEN_CONST_ANY                       0xFFFFFFFF

/* Indicator for feature flags */
/* FLAG1_AND_FLAG2 */
/* FLAG1_OR_FLAG2 */
#define FT_FLAG                                 0x00000000U
#define FT_NOTDEF_FLAG                          0x00000001U
#define FT_DEF_FLAG                             0x00000002U
#define FT_FLAG1_AND_FLAG2                      0x00000004U
#define FT_FLAG1_OR_FLAG2                       0x00000008U
#define FT_ELSE                                 0x00000010U

/* constants for object iterators */
#define AUTOGEN_OBJ_NAME_ANY                    NULL

#define AUTOGEN_OBJ_ID_EXACT                    1
#define AUTOGEN_OBJ_ID_NOT                      2
#define AUTOGEN_OBJ_ID_ANY                      3

#define AUTOGEN_OBJ_SUBTYPE_EXACT               1
#define AUTOGEN_OBJ_SUBTYPE_NOT                 2
#define AUTOGEN_OBJ_SUBTYPE_ANY                 3
#define AUTOGEN_OBJ_SUBTYPE_NOT_ANY             4

#define AUTOGEN_OBJ_FLAG_ANY                    2
#define AUTOGEN_OBJ_FLAG_ALL                    3

#define AUTOGEN_OBJ_FEATUREFLAG_NO_CHECK        0
#define AUTOGEN_OBJ_FEATUREFLAG_CHECK           1

#define AUTOGEN_OBJ_VERSION_NONE                0x0000U
#define AUTOGEN_OBJ_VERSION_FROM                0x0001U
#define AUTOGEN_OBJ_VERSION_TO                  0x0002U
#define AUTOGEN_OBJ_VERSION_INTERVAL           (AUTOGEN_OBJ_VERSION_FROM | AUTOGEN_OBJ_VERSION_TO)
#define AUTOGEN_OBJ_VERSION_ALL                 0x0004U
#define AUTOGEN_OBJ_VERSION_EXACT              (0x0008U | AUTOGEN_OBJ_VERSION_FROM | AUTOGEN_OBJ_VERSION_TO)

#define AUTOGEN_OBJ_VERSION_ANY                 0xFFFF
#define AUTOGEN_OBJ_VERSION_OVERLAP             0xFFFE
#define AUTOGEN_OBJ_VERSION_FIRST               0xFFFD
#define AUTOGEN_OBJ_VERSION_COVER_SINGLE        0xFFFC
#define AUTOGEN_OBJ_VERSION_COVER_MULTIPLE      0xFFFB
#define AUTOGEN_OBJ_VERSION_INCLUDES            0xFFF9
#define AUTOGEN_OBJ_VERSION_INCLUDES_NOT        0xFFF8


/* presentation types */
#define AUTOGEN_PRESENTATION_NONE               0x00000000U
#define AUTOGEN_PRESENTATION_DEC                0x00000001U
#define AUTOGEN_PRESENTATION_HEX                0x00000002U
#define AUTOGEN_PRESENTATION_BIN                0x00000004U
#define AUTOGEN_PRESENTATION_PN_CONST           0x00000008U
#define AUTOGEN_PRESENTATION_GLOBAL             0x00000080U
#define AUTOGEN_PRESENTATION_ASCII_CHAR         0x00000100U
#define AUTOGEN_PRESENTATION_UNICODE_CHAR       0x00000200U
#define AUTOGEN_PRESENTATION_CDSP_PROCESS_ID    0x00000400U
#define AUTOGEN_PRESENTATION_ADSP_PROCESS_ID    0x00000800U
#define AUTOGEN_PRESENTATION_OS_CONST           0x00002000U
#define AUTOGEN_PRESENTATION_SYMBOL             0x00004000U

#define AUTOGEN_PRESENTATION_CONST              0x00020000U

#define AUTOGEN_PRESENTATION_SCALAR             0x00040000U
#define AUTOGEN_PRESENTATION_OFFSET             0x00080000U
#define AUTOGEN_PRESENTATION_UNIT               0x00100000U

#define AUTOGEN_PRESENTATION_LINEAR            (AUTOGEN_PRESENTATION_SCALAR | \
                                                AUTOGEN_PRESENTATION_OFFSET)
#define AUTOGEN_PRESENTATION_SIMPLE            (AUTOGEN_PRESENTATION_DEC | \
                                                AUTOGEN_PRESENTATION_UNIT)
#define AUTOGEN_PRESENTATION_TRANS             (AUTOGEN_PRESENTATION_UNIT | \
                                                AUTOGEN_PRESENTATION_LINEAR)

#define AUTOGEN_PRESENTATION_TIMESTAMP          0x00200000U
#define AUTOGEN_PRESENTATION_FTDID              0x01000000U
#define AUTOGEN_PRESENTATION_PPCID              0x02000000U

#define AUTOGEN_PRESENTATION_STRING             0x04000000U

#define AUTOGEN_PRESENTATION_QN                 0x08000000U

#define AUTOGEN_PRESENTATION_REF_MSGID          0x10000000U
#define AUTOGEN_PRESENTATION_REF_SUBMSGID       0x20000000U
#define AUTOGEN_PRESENTATION_REF_SBID           0x30000000U
#define AUTOGEN_PRESENTATION_REF_DATAID         0x40000000U

#define AUTOGEN_PRESENTATION_ANY                0xFFFFFFFF

#define AUTOGEN_PRESENTATION_CHAR              (AUTOGEN_PRESENTATION_ASCII_CHAR | \
                                                AUTOGEN_PRESENTATION_UNICODE_CHAR)

#define AUTOGEN_PRESENTATION_ID_ANY            (AUTOGEN_PRESENTATION_FTDID | \
                                                AUTOGEN_PRESENTATION_PPCID)

#define AUTOGEN_PRESENTATION_VALUE_ANY         (AUTOGEN_PRESENTATION_DEC | \
                                                AUTOGEN_PRESENTATION_HEX | \
                                                AUTOGEN_PRESENTATION_BIN | \
                                                AUTOGEN_PRESENTATION_QN)

#define AUTOGEN_PRESENTATION_DSP_ANY           (AUTOGEN_PRESENTATION_CDSP_PROCESS_ID | \
                                                AUTOGEN_PRESENTATION_ADSP_PROCESS_ID)

#define AUTOGEN_PRESENTATION_SYMBOL_ANY        (AUTOGEN_PRESENTATION_PN_CONST | \
                                                AUTOGEN_PRESENTATION_GLOBAL | \
                                                AUTOGEN_PRESENTATION_DSP_ANY | \
                                                AUTOGEN_PRESENTATION_OS_CONST | \
                                                AUTOGEN_PRESENTATION_SYMBOL)

#define AUTOGEN_PRESENTATION_CONST_ANY         (AUTOGEN_PRESENTATION_SYMBOL_ANY | \
                                                AUTOGEN_PRESENTATION_CONST)


/* presentation types for definition constants */
#define AUTOGEN_DEF_CONST_SIGNED                AUTOGEN_CONST_SIGNED
#define AUTOGEN_DEF_CONST_UNSIGNED_DEC          AUTOGEN_CONST_UNSIGNED_DEC
#define AUTOGEN_DEF_CONST_UNSIGNED_BYTE         AUTOGEN_CONST_UNSIGNED_BYTE
#define AUTOGEN_DEF_CONST_UNSIGNED_WORD         AUTOGEN_CONST_UNSIGNED_WORD
#define AUTOGEN_DEF_CONST_UNSIGNED_DWORD        AUTOGEN_CONST_UNSIGNED_DWORD
#if (PMD_FILE_FORMAT >= 600)
#define AUTOGEN_DEF_CONST_UNSIGNED_DDWORD       AUTOGEN_CONST_UNSIGNED_DDWORD
#endif


/* data order types */
#define AUTOGEN_ORDER_BE                        0x00000001U
#define AUTOGEN_ORDER_LE                        0x00000002U

#define AUTOGEN_ORDER_BCD_NONE                  0x00000004U
#define AUTOGEN_ORDER_BCD_NSW                   0x00000008U


/* constants for sequence size */
#define AUTOGEN_SIZE_UNDEFINED                  0
#define AUTOGEN_SIZE_EXACT                      1
#define AUTOGEN_SIZE_INTERVAL                   2
#define AUTOGEN_SIZE_ASMANYASPOSSIBLE           3
#define AUTOGEN_SIZE_VERSION_DEPENDENT          4


/* constants for alignment */
#define AUTOGEN_ALIGNMENT_UNDEFINED             0
#define AUTOGEN_ALIGNMENT_DWORD                 1
#define AUTOGEN_ALIGNMENT_BYTE_1                2
#define AUTOGEN_ALIGNMENT_BYTE_3                3
#define AUTOGEN_ALIGNMENT_ODD                   4
#define AUTOGEN_ALIGNMENT_WORD                  5
#define AUTOGEN_ALIGNMENT_WORD_ANY              6
#define AUTOGEN_ALIGNMENT_BYTE_ANY              7
#if (PMD_FILE_FORMAT >= 600)
#define AUTOGEN_ALIGNMENT_DDWORD                8
#define AUTOGEN_ALIGNMENT_BYTE_5                9
#define AUTOGEN_ALIGNMENT_BYTE_6               10
#define AUTOGEN_ALIGNMENT_BYTE_7               11
#define AUTOGEN_ALIGNMENT_DWORD_ANY            12
#endif

/* constants for version type */
#define AUTOGEN_VERSION_ISI                     0x00000001U
#define AUTOGEN_VERSION_DSP                     0x00000002U


/* constants for version history */
#define AUTOGEN_VER_EQUAL                       1
#define AUTOGEN_VER_NEWER                       2
#define AUTOGEN_VER_NEWER_OR_EQUAL              3
#define AUTOGEN_VER_OLDER                       4
#define AUTOGEN_VER_OLDER_OR_EQUAL              5
#define AUTOGEN_VER_MAJOR_INCREMENTED           8
#define AUTOGEN_VER_MAJOR_DECREMENTED          16
#define AUTOGEN_VER_MINOR_INCREMENTED          32
#define AUTOGEN_VER_MINOR_DECREMENTED          64
#define AUTOGEN_VER_MINOR_IS_NULL             128

struct t_autogen_res;
struct t_autogen_seq;


typedef enum e_autogen_ref_type
{
    referenceTypeCounter,
    referenceTypeCounterUnresolved,
    referenceTypeTransformation,
    referenceTypeTransformationUnresolved,
    referenceTypeTag,
    referenceTypeTagUnresolved,
    referenceTypePredefined,
    referenceTypeTraceDataLength,
    referenceTypeExternal

} autogen_ref_type;

struct t_autogen_item;
struct t_autogen_item_value;
struct t_autogen_ref_conf;
struct t_autogen_seq;
struct t_autogen_ver;
struct t_autogen_feature;

typedef struct t_autogen_ref
{
    struct t_autogen_ref* next;

    /* Name of reference */
    const char* name;

    /* Name of reference in item */
    const char* original_name;

    /* Type of reference */
    autogen_ref_type type;

    /* autogen_*/
    const struct t_autogen_ref_conf* conf;

    /* Item, defining reference */
    struct t_autogen_item* item;

    /* Is reference used */
    int is_used;

    /* Is reference external */
    int is_external;

    /* Is reference used externally */
    int is_used_externally;

    /* Transformation properties */
    unsigned short algorithm; /* PMD_LENGTH_ALGORITHM_XX */
    int value;

    /* Feature flag */
    struct t_autogen_feature *feature_flags;

    /* Pointer to next unused reference */
    struct t_autogen_ref* prev_unused;
    struct t_autogen_ref* next_unused;

    /* Pointer to next unresolved reference */
    struct t_autogen_ref* prev_unresolved;
    struct t_autogen_ref* next_unresolved;

	struct t_autogen_item* unresolved_item;

} autogen_ref;


typedef struct t_autogen_ref_handle
{
    struct t_autogen_ref_handle* base_handle;

    /* object which embeds handle */
    struct t_autogen_obj* parent;

    /* References defined. Combination of AUTOGEN_REFERENCE_TYPE_XXX flags */
    unsigned int included_types;

    /* Does the handle include any external references? */
    int uses_external_references;

    /* List of references */
    autogen_ref* ref_list;

} autogen_ref_handle;


typedef struct t_autogen_prop
{
    unsigned int flags;
    autogen_property_id id;
    int index;
    int lineno;
    struct t_autogen_prop *next;
    const char *str;
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long value;
#else
    unsigned int value;
#endif
} autogen_prop;


typedef struct t_autogen_size
{
    /* type of the size
       can be any of the following types
         AUTOGEN_SIZE_UNDEFINED
         AUTOGEN_SIZE_EXACT
         AUTOGEN_SIZE_INTERVAL
         AUTOGEN_SIZE_DYNAMIC
         AUTOGEN_SIZE_ASMANYASPOSSIBLE
         AUTOGEN_SIZE_VERSION_DEPENDENT
    */
    unsigned int type;

    /* minimum and maximum sizes in bytes.
       when the size is exact, the two values are identical 
    */
    unsigned int min;
    unsigned int max;

} autogen_size;



typedef struct t_autogen_ver
{
    /* indicates type of version
       AUTOGEN_OBJ_VERSION_ALL      - valid for all possible versions (default)
       AUTOGEN_OBJ_VERSION_FROM     - the valid from version is defined
       AUTOGEN_OBJ_VERSION_TO       - the obsolete after version is defined
       AUTOGEN_OBJ_VERSION_INTERVAL - both version numbers are defined
       AUTOGEN_OBJ_VERSION_EXACT    - the version interval narrows to one version
    */
    unsigned int type;

    /* system for version
       AUTOGEN_VERSION_ISI - ZZZ.YYY
       AUTOGEN_VERSION_DSP - ZZZ.YYY.XXX
    */
    unsigned int system;

    /* ISI version, from which the object is valid */
    unsigned short from[3];

    /* ISI version, after which the object is obsolete*/
    unsigned short to[3];

    /* ID for sorting lists of version "strings" */
    unsigned int id;

    /* version string, when PROPERTY_ISI_VERSIONING_NOT_SUPPORTED is set */
    const char* ver_str;

} autogen_ver;


#define INIT_VERSION_ALL { AUTOGEN_OBJ_VERSION_ALL, AUTOGEN_VERSION_ISI, { 0, 0, 0 }, { 256, 0, 0 }, 0, NULL }


typedef struct t_autogen_cmt
{
    /* pointer to the next comment in the list
       a NULL indicates the end of the list
    */
    struct t_autogen_cmt* next;

    /* type of the comment
       can be any of the following values:
        AUTOGEN_COMMENT_NONE      - no comment (empty)
        AUTOGEN_COMMENT_TEXT      - simple text comment
        AUTOGEN_COMMENT_NEWLINE   - new line
        AUTOGEN_COMMENT_PARAGRAPH - a text with a newline
        AUTOGEN_COMMENT_BULLET    - comment with a bullet
        AUTOGEN_COMMENT_LINK      - a link (link.. attributes are valid)

        AUTOGEN_COMMENT_ISIHDR_BEFORE_DEF - comment in the ISI header file
        AUTOGEN_COMMENT_ISIHDR_AFTER_DEF  - comment in the ISI header file
    */
    autogen_comment_id id;

    /* object type of link (only valid for type AUTOGEN_COMMENT_LINK) 
       can be any of the AUTOGEN_OBJ_XXX values */
    unsigned int linktype;

    /* name of linked object (only valid for type AUTOGEN_COMMENT_LINK) */
    const char* linkname;

    /* subname of linked object (only valid for type AUTOGEN_COMMENT_LINK) */
    const char* linksubname;

    /* version of linked object (only valid for type AUTOGEN_COMMENT_LINK) */
    autogen_ver linkver;

    /* pointer to the comment string... */
    const char* comment;

} autogen_cmt;


typedef struct t_autogen_pres
{
    /* type of presentation */
    unsigned int type;

    /* sub type of presentation */
    unsigned int subtype;

    /* unit of measure */
    const char *unit;

    double scale;
    double offset;

    /* name of table for constants and symbols */
    const char* tblname;

    /* pointer to object, where constant / id is defined 
       used for presentations 
        AUTOGEN_PRESENTATION_REF_MSGID
        AUTOGEN_PRESENTATION_REF_SUBMSGID
        AUTOGEN_PRESENTATION_REF_SBID
        AUTOGEN_PRESENTATION_REF_TRCGRPID
    */
    struct t_autogen_obj* obj;

    /* resource, table belongs to */
    struct t_autogen_res* tblres;

    /* name of resource, table is defined in */
    const char* tblresname;

} autogen_pres;

#define INIT_PRES \
{ \
    0, 0, NULL, 1.0f, 0.0f, NULL, NULL, NULL, NULL \
}

#define AUTOGEN_OBJ_LIST_SORT_BY_NAME               0
#define AUTOGEN_OBJ_LIST_SORT_BY_ID                 1
#define AUTOGEN_OBJ_LIST_SORT_BY_VERSION            2
#define AUTOGEN_OBJ_LIST_SORT_BY_VERSION_REVERSED   3
#define AUTOGEN_OBJ_LIST_SORT_BY_TYPE_AND_NAME      4

#define AUTOGEN_OBJ_LIST_SORT_TYPES                 5

#define AUTOGEN_OBJ_LIST_SORT_UNDEFINED             0xFFFFFFFE
#define AUTOGEN_OBJ_LIST_SORT_NONE                  0xFFFFFFFF

#define AUTOGEN_OBJ_LIST_SORTED_BY_NAME             (1 << AUTOGEN_OBJ_LIST_SORT_BY_NAME)
#define AUTOGEN_OBJ_LIST_SORTED_BY_ID               (1 << AUTOGEN_OBJ_LIST_SORT_BY_ID)
#define AUTOGEN_OBJ_LIST_SORTED_BY_VERSION          (1 << AUTOGEN_OBJ_LIST_SORT_BY_VERSION)
#define AUTOGEN_OBJ_LIST_SORTED_BY_VERSION_REVERSED (1 << AUTOGEN_OBJ_LIST_SORT_BY_VERSION_REVERSED)
#define AUTOGEN_OBJ_LIST_SORTED_BY_TYPE_AND_NAME    (1 << AUTOGEN_OBJ_LIST_SORT_BY_TYPE_AND_NAME)

typedef struct t_autogen_obj_list
{
    struct t_autogen_obj* parent;

    struct t_autogen_obj** obj_list;
    struct t_autogen_obj** map[AUTOGEN_OBJ_LIST_SORT_TYPES];

    unsigned int flag;

    int n_obj;
    int n_obj_allocated;

} autogen_obj_list;

#define INIT_OBJ_LIST \
{ \
    NULL, NULL, \
    NULL, NULL, NULL, NULL, NULL, \
    0, 0, 0 \
}

typedef struct t_autogen_feature_flag
{
    const char* flag;
    const char* value;
}autogen_feature_flag;

typedef struct t_autogen_feature
{
    /* Points to the head of if-else feature */
    /* Eg. the else part will point to the if part */
    struct t_autogen_feature *head;

    /* Flags. Name and value */
    struct t_autogen_feature_flag* feature1;
    struct t_autogen_feature_flag* feature2;

    /* Kind of flag. AND, OR, Defined, Not defined etc. */
    unsigned int flag_logic;
}autogen_feature;

typedef struct t_autogen_obj
{
    /* pointer to the next object in the list a NULL indicates the end of the list */
    struct t_autogen_obj* next;

    /* pointer to the parent object */
    struct t_autogen_obj* parent;

    /* pointer to the base object (e.g. message object for sub message) */
    struct t_autogen_obj* base_obj;

    /* optimized child list */
    autogen_obj_list child_list;

    /* pointer to a list of related objects */
    autogen_obj_list related_obj;

    /* type of the object
       can be any of the AUTOGEN_OBJ_XXX constants 
    */
    unsigned int type;

    /* secondary (sub) type of the object */
    unsigned int subtype;

    /* id of the object */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long id;
#else
    unsigned int id;
#endif

    /* object flags */
    unsigned int flag;

    /* pointer to a list of object comments.
       a NULL indicates no comments 
    */
    autogen_cmt* cmt_list;

    /* object version */
    autogen_ver ver;

    /* name of the object - not necesarilly unique within the list */
    const char* name;

    /* size of the object */
    unsigned int size;

    /* unique id for this object */
    unsigned int obj_id;

    /* pointer to an object */
    void* ptr;

    /* list of properties */
    autogen_prop* prop_list;

    /* feature flags for object */
    struct t_autogen_feature* feature_flags;

    /* resource, which object belongs to */
    struct t_autogen_res* res;

    /* File and line, where object is declared */
    const char* file_name;
    int file_line;

} autogen_obj;

#define INIT_OBJECT \
{ \
    NULL, NULL, NULL, INIT_OBJ_LIST, INIT_OBJ_LIST, \
    0, 0, 0, 0, \
    NULL, \
    INIT_VERSION_ALL, \
    NULL, sizeof(autogen_obj), 0, NULL, NULL, NULL, NULL, 0 \
}

typedef struct t_autogen_data
{
    /* base object
       obj type is AUTOGEN_OBJ_DATA
       obj subtype can be one of the following
        AUTOGEN_DATA_FTD
        AUTOGEN_DATA_PPC
       flags:
        AUTOGEN_DATA_VALUE
        AUTOGEN_DATA_TABLE
        AUTOGEN_DATA_STRING
    */
    struct t_autogen_obj base;

    /* size of FTD data (when integer value or constant)
       possible values are (-)8, (-)16 and (-)32
    */
    int length;

    /* name of parameter. Only for strings (AUTOGEN_DATA_STRING) */
    const char* parname;

    /* presentation object */
    autogen_pres pres;

    /* name of sequence (sub block template)
       that is used to encapsulate the data
    */
    const char* seqname;

}  autogen_data;

typedef struct t_autogen_tbl
{
    /* base object */
    struct t_autogen_obj base;

    int length;

    unsigned int order;

    /* reference to original table (for derived tables) */
    const struct t_autogen_tbl* orgtbl;

} autogen_tbl;

typedef struct t_autogen_bittbl_entry
{
    /* base object */
    struct t_autogen_obj base;

    /* pattern consisting og 0, 1 and x's */
    const char* bit_pattern;

    /* mask to be applied value to check whether entry is set */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long bit_mask;
#else
    unsigned int bit_mask;
#endif

} autogen_bittbl_entry;


typedef struct t_autogen_const
{
    /* base object */
    struct t_autogen_obj base;
} autogen_const;

typedef struct t_autogen_embedded_file
{
    /* base object */
    struct t_autogen_obj base;

    const char* decoder_name;

    unsigned int file_size;

} autogen_embedded_file;

typedef struct t_autogen_pmd_info_attr
{
    /* base object */
    struct t_autogen_obj base;

    /* number of attributes */
    int n_attr;

    /* actual attributes */
    unsigned int attr[4];

} autogen_pmd_info_attr;

typedef struct t_autogen_seq_ref
{
    /* base object */
    struct t_autogen_obj base;

    /* pointer to the object */
    struct t_autogen_seq* seqptr;

} autogen_seq_ref;


typedef struct t_autogen_item
{
    /* base object 
       obj type is AUTOGEN_OBJ_ITEM
       obj subtype can be one of the following
        AUTOGEN_ITEM_REF
        AUTOGEN_ITEM_VALUE
        AUTOGEN_ITEM_TIMESTAMP
        AUTOGEN_ITEM_POINTER
        AUTOGEN_ITEM_CONST
        AUTOGEN_ITEM_FILLER
        AUTOGEN_ITEM_LST
        AUTOGEN_ITEM_STRING
        AUTOGEN_ITEM_STRUCT
        AUTOGEN_ITEM_CHOICE
        AUTOGEN_ITEM_MERGE
        AUTOGEN_ITEM_RANGE
        AUTOGEN_ITEM_PRINTF
    */
    struct t_autogen_obj base;

    /* sub type of item
        AUTOGEN_ITEM_TIMESTAMP
            PMD_TIMESTAMP_XXX constants
    */
    unsigned int item_sub_type;

    /* item specific type and/or settings (flag value)

       If the item is placed in a merged field, the following flag is set
        AUTOGEN_ITEM_PART_OF_MERGE

       If the item is labeled as a parameter, the following flag is set
        AUTOGEN_ITEM_PARAMETER

       If the item contains a default value, the following flag is set
        AUTOGEN_ITEM_DEFAULT_VALUE

       for AUTOGEN_ITEM_REF, the following specific types are possible
        AUTOGEN_REF_CONST           - constant reference
                                      tblname contains name of constant table

       for AUTOGEN_ITEM_VALUE, there are no specific types

       for AUTOGEN_ITEM_TIMESTAMP, the following specific types are possible
        AUTOGEN_TIMESTAMP_OSTRICH

       for AUTOGEN_ITEM_POINTER, the following specific types are possible
        AUTOGEN_POINTER_VOID

       for AUTOGEN_ITEM_CONST, the following specific types are possible
        AUTOGEN_CONST_IMPORT        - const/bit table is placed in sep. resource
                                      resname contains name of resource

       for AUTOGEN_ITEM_FILLER, the following specific types are possible
        AUTOGEN_FILLER_0_BYTES_POSSIBLE - generated alignment info for dynamic fillers
        AUTOGEN_FILLER_1_BYTE_POSSIBLE  - generated alignment info for dynamic fillers
        AUTOGEN_FILLER_2_BYTES_POSSIBLE - generated alignment info for dynamic fillers
        AUTOGEN_FILLER_3_BYTES_POSSIBLE - generated alignment info for dynamic fillers
        AUTOGEN_FILLER_4_BYTES_POSSIBLE - generated alignment info for dynamic fillers
        AUTOGEN_FILLER_5_BYTES_POSSIBLE  - generated alignment info for dynamic fillers
        AUTOGEN_FILLER_6_BYTES_POSSIBLE - generated alignment info for dynamic fillers
        AUTOGEN_FILLER_7_BYTES_POSSIBLE - generated alignment info for dynamic fillers

       for AUTOGEN_ITEM_LST, the following specific types are possible
        AUTOGEN_LST_SB               - list of regular subblocks or ID's
        AUTOGEN_LST_FTD              - list of FTD subblocks or ID's
        AUTOGEN_LST_PPC              - list of PPC subblocks or ID's
        AUTOGEN_LST_SOS_FTD          - list of SOS FTD subblocks or ID's
        AUTOGEN_LST_SBID             - list contains ID's
        AUTOGEN_LST_SBDATA           - list contains actual data (subblocks)
        AUTOGEN_LST_SB_HAVE_BYTE_IDS - sub blocks have 8 bit ID's (only)
        AUTOGEN_LST_SB_HAVE_WORD_IDS - sub blocks have 16 bit ID's (only)

       for AUTOGEN_ITEM_STRING, the following specific types are possible
        AUTOGEN_STRING_ASCII        - ASCII string (8 bit characters)
        AUTOGEN_STRING_UNICODE      - unicode string (16 bit characters)
        AUTOGEN_STRING_BCD          - BCD string (4 bit characters)
                                      tblname refers to BCD table associated 
                                      with the string
        AUTOGEN_STRING_ZEROTERM     - string is NULL-terminated

       for AUTOGEN_ITEM_STRUCT, the following specific types are possible
        AUTOGEN_STRUCT_SB           - The structure is a subblock
                                      seqname contains the subblock name
        AUTOGEN_STRUCT_SEQ          - The structure is a sequence
                                      seqname contains the sequence name

       for AUTOGEN_ITEM_BLOCK, the following types are possible
        BLOCK_XXX

       for AUTOGEN_ITEM_PRINTF, the following types are possible
        none
    */
    /* data order of item */
    unsigned int order;

    /* size of item in bits (optional) */
    int length;

    /* variable name of item (C structure name) */
    const char* varname;

    /* parameter name of item (encode/decode name) */
    const char* parname;

    /* name of reference, item refers to (optional) */
    const char* refname;

    /* aggregation type of the item, AGG_TYPE_XXX */
    autogen_agg_type agg_type;

    /* for fixed aggregation, number of aggregations (size of array) */
    int agg_n;

    /* for fixed aggregation, number of aggragations (size of array), 
       text string */
    const char* agg_n_str;

    /* pointer to the sequence, the item ultimately belongs to */
    struct t_autogen_seq* seq;

    /* PMD special number type or PMD_NUMBER_SPECIAL_TYPE_NONE */
    unsigned int special_number_type;

    /* trace group list associated with resource
       - AUTOGEN_OBJ_TRACEGRP_NONE if none
    */
    unsigned int trc_type;

    /* Is offset valid?

       Possible values:
       AUTOGEN_ITEM_OFFSET_UNDEFINED - not set at all
       AUTOGEN_ITEM_OFFSET_EXACT     - exact offset
       AUTOGEN_ITEM_OFFSET_VARIABLE  - offset varies with other elements
    */
    unsigned int offset_type;
    /* Byte offset of item (from message start) */
    unsigned int offset;

    /* Bit pattern of item representation in merged field */
    const char* bit_pattern;

} autogen_item;

typedef struct t_autogen_item_string
{
    /* base item */
    autogen_item base;

    /* string length */
    unsigned short length;

    /* string length as string */
    const char* length_str;

} autogen_item_string;

typedef struct t_autogen_item_case
{
    /* base item */
    autogen_item base;

    /* References handle */
    autogen_ref_handle ref_handle;

} autogen_item_case;

typedef struct t_autogen_item_choice
{
    /* base item */
    autogen_item base;

    /* table reference for forward choice */
    const char* tblname;
    struct t_autogen_res* tblres;

    /* default case structure */
    struct t_autogen_item_case* default_case;

    /* relative position */
    unsigned short relpos;

} autogen_item_choice;

typedef struct t_autogen_item_value
{
    /* base item */
    autogen_item base;

    /* presentation object */
    autogen_pres pres;
    
} autogen_item_value;

typedef struct t_autogen_item_range_entry
{
    /* base item */
    autogen_item base;

    /* range */
    unsigned int from;
    unsigned int to;

    /* presentation object */
    autogen_pres pres;

    /* presentation string */
    const char* text;

} autogen_item_range_entry;

typedef struct t_autogen_item_struct
{
    /* base item */
    autogen_item base;

    /* name of sequence or sub block */
    const char* seqname;

    /* resource of sequence or sub block */
    struct t_autogen_res* seqres;

} autogen_item_struct;

typedef struct t_autogen_item_block
{
    /* base item */
    autogen_item base;

    /* valid when flag AUTOGEN_BLOCK_EXT_DECODER is set */
    const char* data1;
    const char* data2;

    /* valid when flag AUTOGEN_BLOCK_PROTOCOL is set */
    const char* protocol_name;

} autogen_item_block;

typedef struct t_autogen_item_printf
{
    /* base item */
    autogen_item base;

#if (PMD_FILE_FORMAT >= 600)
    /* component ID */
    unsigned long long component_id;

    /* trace group ID */
    unsigned long long tracegrp_id;

    /* trace ID */
    unsigned long long trace_id;
#else
    /* component ID */
    unsigned int component_id;

    /* trace group ID */
    unsigned int tracegrp_id;

    /* trace ID */
    unsigned int trace_id;
#endif

    /* printf format string */
    const char *format;

} autogen_item_printf;

typedef struct t_autogen_seq
{
    /* base object

    */
    struct t_autogen_obj base;

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* size object */
    autogen_size size;

    /* alignment of sequence */
    unsigned int alignment;
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* References handle */
    autogen_ref_handle ref_handle;

    /* List of submessages (only valid if type is AUTOGEN_OBJ_MSG_BASE) */
    autogen_obj_list submsg_list;

} autogen_seq;


typedef struct t_autogen_def
{
    /* base object */
    struct t_autogen_obj base;

    /* is the definition generated in the header file?
       TRUE / FALSE
    */
    int is_generated;

    /* presentation types for constant id's
        AUTOGEN_DEF_CONST_SIGNED          - should be presented as signed decimal value
        AUTOGEN_DEF_CONST_UNSIGNED_DEC    - should be presented as decimal value
        AUTOGEN_DEF_CONST_UNSIGNED_BYTE   - should be presented as 0xXX
        AUTOGEN_DEF_CONST_UNSIGNED_WORD   - should be presented as 0xXXXX
        AUTOGEN_DEF_CONST_UNSIGNED_DWORD  - should be presented as 0xXXXXXXXX
        AUTOGEN_DEF_CONST_UNSIGNED_DDWORD - should be presented as 0xXXXXXXXXXXXXXXXX
    */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long id_pres;
#else
    unsigned int id_pres;
#endif

} autogen_def;


typedef struct t_autogen_trcgrp
{
    /* base object */
    struct t_autogen_obj base;
 
    /* info for direct diversion of trace data to DLL */
    const char* dll_name;
    const char* func_name;

    /* TRUE, if any traces are defined in the group */
    int has_traces;

    /* PMD trace identifier (4 characters) */
    const char* identifier;

} autogen_trcgrp;

struct t_autogen_res_conf* conf;

typedef struct t_autogen_res
{
    /* base object */
    struct t_autogen_obj base;

    /* short name of resource
       to be used for naming ISI header file, etc.
       default, it is derived from PN_XXX name (by removing "PN_")
    */
    const char* resnameshort_u;
    const char* resnameshort_l;

    /* name of resource */
    const char* logical_name;

    /* name of mdf */
    const char* filename;

    /* if the resource is an ISI owner of a shared resource,
       this points to that shared resource */
    struct t_autogen_res* shared_res;

    /* lists of objects */
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    autogen_obj_list def_list;
    autogen_obj_list note_list;
    autogen_obj_list old_macro_list;
#endif
    autogen_obj_list const_list;
    autogen_obj_list msg_list;
    autogen_obj_list msg_dev_dep_req_list;
    autogen_obj_list msg_dev_dep_resp_list;
    autogen_obj_list seq_list;
    autogen_obj_list shared_list;
    autogen_obj_list tbl_list;
    autogen_obj_list ver_list;

    /* message ID section (for comments and properties only) */
    autogen_obj* msg_id_section;

    /* sub block ID section (for comments and properties only) */
    autogen_obj* sb_id_section;

    /* message rules for resource */
    int msg_id_size;
    int msg_id_offset;
    int submsg_id_size;
    int submsg_id_offset;
    int msg_length_size;
    int msg_length_offset;

    /* resource index in g_res_conf */
    int index; 
    const struct t_autogen_res_conf* conf;

    /* trace configuration */
    struct t_autogen_trcgrp_conf* trc_conf;
    autogen_obj_list* trcgrp_list;

    /* PMD trace identifier (4 characters) */
    const char* identifier;

    /* Device ID, resource belongs to */
    unsigned short device_id;

} autogen_res;


typedef struct t_autogen_it
{
    /* iterator settings */
    unsigned int sort_type;
    unsigned int sort_flags;
    autogen_obj** sort_map;
    autogen_obj* current_obj;
    autogen_obj_list* current_obj_list;
    int current_index;
    int use_binary_search;

    unsigned int typemask;

    /* possible subtype criterias
        AUTOGEN_OBJ_SUBTYPE_EXACT
        AUTOGEN_OBJ_SUBTYPE_NOT
        AUTOGEN_OBJ_SUBTYPE_ANY (default)
        AUTOGEN_OBJ_SUBTYPE_NOT_ANY
    */
    unsigned int subtypecrit;

    unsigned int subtypemask;

    /* possible id criterias
        AUTOGEN_OBJ_ID_EXACT
        AUTOGEN_OBJ_ID_NOT
        AUTOGEN_OBJ_ID_ANY (default)
    */
    unsigned int idcrit;

    /* possible flag criterias
        AUTOGEN_OBJ_FLAG_ALL
        AUTOGEN_OBJ_FLAG_ANY (default)
    */
    unsigned int flagcrit;
    unsigned int flagmask;

    /* all of these flags must be set */
    unsigned int flagall;

    /* any of these flags must be set */
    unsigned int flagany;

    /* none of these flags must be set */
    unsigned int flagnone;

    /* possible version criterias:
        AUTOGEN_OBJ_VERSION_ANY (default)
        AUTOGEN_OBJ_VERSION_OVERLAP
        AUTOGEN_OBJ_VERSION_FIRST
        AUTOGEN_OBJ_VERSION_COVER_SINGLE
        AUTOGEN_OBJ_VERSION_COVER_MULTIPLE
    */
    unsigned int vercrit;

    const autogen_ver* ver;

    /* feature flag criterias
        AUTOGEN_OBJ_FEATUREFLAG_NO_CHECK
        AUTOGEN_OBJ_FEATUREFLAG_CHECK
    */
    unsigned int featureflagcrit;

    /* actual object settings */
    autogen_obj obj;

} autogen_it;

#define INIT_ITERATOR \
{ \
    AUTOGEN_OBJ_LIST_SORT_UNDEFINED, 0, NULL, NULL, NULL, 0, FALSE, \
    AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_SUBTYPE_ANY, AUTOGEN_OBJ_ANY, \
    AUTOGEN_OBJ_ID_ANY, \
    AUTOGEN_OBJ_FLAG_ANY, AUTOGEN_OBJ_ANY, 0, AUTOGEN_OBJ_ANY, 0, \
    AUTOGEN_OBJ_VERSION_ANY, NULL, \
    AUTOGEN_OBJ_FEATUREFLAG_NO_CHECK, \
    INIT_OBJECT \
}



/* ============================================================================================= */
/* Function prototypes */
/* ============================================================================================= */

/* comment related functions */

autogen_cmt*    autogen_cmt_create(autogen_comment_id id, unsigned int linktype, 
                                   const char* linkname, const char* linksubname, 
                                   const char* linkver, const char* comment);
void            autogen_cmt_add(autogen_cmt** cmt_list, autogen_cmt* cmt);
autogen_cmt*    autogen_cmt_copy(const autogen_cmt* src);
autogen_cmt*    autogen_cmt_find(autogen_cmt* cmt_list, autogen_comment_id id);


/* object related functions */

#if (PMD_FILE_FORMAT >= 600)
autogen_obj*    autogen_obj_create(const char* file_name, int file_line, autogen_res* res, autogen_obj* parent, unsigned int size, unsigned int type, unsigned int subtype, unsigned long long id, const char* name, autogen_feature *feature_flag);
#else
autogen_obj*    autogen_obj_create(const char* file_name, int file_line, autogen_res* res, autogen_obj* parent, unsigned int size, unsigned int type, unsigned int subtype, unsigned int id, const char* name, autogen_feature *feature_flag);
#endif
autogen_obj*    autogen_obj_copy_deep(const autogen_obj* src, autogen_obj* obj, autogen_obj* parent, const autogen_ver* ver);

unsigned int    autogen_obj_ver_set(autogen_ver* ver, const unsigned short* ver_from, const unsigned short* ver_to);
int             autogen_obj_ver_is_included(const autogen_ver* ver1, const autogen_ver* ver2);
int             autogen_obj_ver_is_exact(const autogen_ver* ver1, const autogen_ver* ver2);
int             autogen_obj_ver_is_overlapping(const autogen_ver* ver1, const autogen_ver* ver2);
unsigned int    autogen_obj_ver_merge(const autogen_ver* ver1, const autogen_ver* ver2, autogen_ver* retver);
const autogen_ver* autogen_obj_ver_crop(const autogen_ver* ver1, const autogen_ver* ver2);
void            autogen_obj_ver_replace_deep(autogen_obj* obj, const autogen_ver* ver, int replace_next);
int             autogen_ver_comp(const unsigned short* ver1, const unsigned short* ver2);
int             autogen_obj_featureflag_comp(const autogen_feature *left, const autogen_feature *right);

autogen_obj*    autogen_res_ver_add(autogen_res* res, const unsigned short* ver, unsigned int system);

void            autogen_obj_list_init(autogen_obj_list* obj_list, autogen_obj* parent, unsigned int flags, int n_allocated);
int             autogen_obj_list_add_obj(autogen_obj_list* obj_list, autogen_obj* obj, unsigned int error_env);
autogen_obj**   autogen_obj_list_get_sorted_list(autogen_obj_list* obj_list, unsigned int map_type);
void            autogen_obj_list_delete_obj(autogen_obj_list* obj_list, autogen_obj* obj);
int             autogen_obj_list_verify_object_span(autogen_it* it, autogen_obj_list* obj_list);
autogen_obj*    autogen_obj_find_in_list(autogen_it* it, autogen_obj_list* obj_list);
autogen_obj*    autogen_obj_find_next_in_list(autogen_it* it);
autogen_obj*    autogen_obj_get_first_in_list(autogen_obj_list* obj_list);
unsigned int    autogen_obj_count_in_list(autogen_it* it, autogen_obj_list* obj_list);


#endif /* _AUTOGEN_OBJECT_H_ */


/*  End of file autogen_object.h  */
