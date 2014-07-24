/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_prop.c
                --------------
                SW Module






Project:          autogen

%name:            autogen_prop.c %
%version:         co1tss#82 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Wed Nov 11 16:47:04 2009 %

Copyright (c) Nokia. All rights reserved.
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_prop.h"
#include "autogen_check.h"
#include "autogen_object.h"
#include "autogen_util.h"
#include "pmd_heap.h"

#include <stdlib.h>
#include <string.h>

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

typedef struct autogen_prop_type_t
{
    unsigned int id;
    const char *name;
    const char *oldname;
    unsigned int property_flags;
    unsigned int object_flags;
    unsigned int object_type_mask;
    unsigned int object_subtype_mask;
} autogen_prop_type;


#define DEFINE_PROPERTY_OSS(id, old_name, pflag, oflag, obj_type, obj_subtype ) { id, #id, old_name, pflag, oflag, obj_type, obj_subtype },
#define DEFINE_PROPERTY_OS(id, old_id, pflag, oflag, obj_type, obj_subtype ) { id, #id, #old_id, pflag, oflag, obj_type, obj_subtype },
#define DEFINE_PROPERTY_S(id, pflag, oflag, obj_type, obj_subtype)  { id, #id, NULL, pflag, oflag, obj_type, obj_subtype },

static const autogen_prop_type prop_table[PROPERTY_TOTAL_COUNT] =
{
    DEFINE_PROPERTY_S (PROPERTY_ALIGNMENT_64_BITS,                                                               PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ALIGNMENT_CHECK_BREAK,                                                           PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ALIGNMENT_CHECK_DISABLE,                 COMMENT_DISABLE_ALIGNMENT_CHECK,        PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ARRAY_MAXIMUM_SIZE,                                                              PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_ITEM, ~AUTOGEN_ITEM_STRING)
    DEFINE_PROPERTY_OS(PROPERTY_CHANGE_DATE,                             COMMENT_CHANGE_DATE,                    PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_VERSION, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_CHANGE_PERSON,                           COMMENT_CHANGE_PERSON,                  PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_VERSION, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_CHANGE_REASON,                           COMMENT_CHANGE_REASON,                  PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_VERSION, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_CHANGE_REFERENCE,                        COMMENT_CHANGE_REFERENCE,               PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING | PROPERTY_FLAG_MULTIPLE, 0, AUTOGEN_OBJ_VERSION, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_CHANGE_STATUS,                           COMMENT_CHANGE_STATUS,                  PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_VERSION, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_COMPONENT_ID,                                                                    PROPERTY_FLAG_VALUE,  0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_COPYRIGHT_YEAR,                                                                  PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_DEVICE_DEPENDENT_MESSAGES,                                                       PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, RESOURCE_ISI)
    DEFINE_PROPERTY_S (PROPERTY_FTD_IS_COMMAND,                                                                  PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_DATA, AUTOGEN_DATA_FTD)
    DEFINE_PROPERTY_S (PROPERTY_FTD_IS_INPUT_DATA,                                                               PROPERTY_FLAG_SIMPLE, AUTOGEN_DATA_FTD_IS_INPUT_DATA, AUTOGEN_OBJ_DATA, AUTOGEN_DATA_FTD)
    DEFINE_PROPERTY_OS(PROPERTY_FTD_IS_STATIC_DATA,                      COMMENT_STATIC_DATA,                    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_DATA, AUTOGEN_DATA_FTD)
    DEFINE_PROPERTY_S (PROPERTY_FTD_STRING_MAXIMUM_LENGTH,                                                       PROPERTY_FLAG_VALUE,  0, AUTOGEN_OBJ_DATA, AUTOGEN_DATA_FTD)
    DEFINE_PROPERTY_S (PROPERTY_FTD_STRING_MINIMUM_LENGTH,                                                       PROPERTY_FLAG_VALUE,  0, AUTOGEN_OBJ_DATA, AUTOGEN_DATA_FTD)
    DEFINE_PROPERTY_S (PROPERTY_FTD_SUPPORTED_MODES,                                                             PROPERTY_FLAG_VALUE,  0, AUTOGEN_OBJ_DATA, AUTOGEN_DATA_FTD)
    DEFINE_PROPERTY_S (PROPERTY_HTML_CONTINUUS_PROJECT_DB,                                                       PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,             COMMENT_HTML_CONTINUUS_PROJECT_NAME,    PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_HTML_DIRECTORY_PATH,                                                             PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_HTML_DOCUMENT_NUMBER,                    COMMENT_HTML_DOCUMENT_NUMBER,           PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_HTML_DONT_GENERATE,                                                              PROPERTY_FLAG_SIMPLE, AUTOGEN_OBJ_IS_NOT_GENERATED_HTML, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_HTML_EXPAND_CONSTANT_LISTS,                                                      PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_HTML_FILENAME,                           COMMENT_HTML_FILENAME,                  PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_HTML_INCLUDE_INTRODUCTION,               COMMENT_INCLUDE_HTML_INTRODUCTION,      PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_HTML_INCLUDE_PHONET_HEADER,                                                      PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_HTML_INCLUDE_VARNAME_COLUMN,                                                     PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS,                                                    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_HTML_TITLE,                              COMMENT_HTML_TITLE,                     PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_INCLUDE_PN_TRACE_OBJECTS,                COMMENT_INCLUDE_PN_TRACE_OBJECTS,       PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_INHERIT_BASE_RESOURCE_DEFINITIONS,                                               PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, RESOURCE_EXTENSION_ANY) 
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_ALIAS_NAME,                       COMMENT_ISIHDR_ALIAS_NAME,              PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_DEFINITION_NAME | PROPERTY_FLAG_MULTIPLE, 0, 
    AUTOGEN_OBJ_TBLENTRY | AUTOGEN_OBJ_DATA | AUTOGEN_OBJ_CONST | AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE | AUTOGEN_OBJ_SB | AUTOGEN_OBJ_DEF, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_ARRAY_MARKER,                                                             PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,          COMMENT_CONTINUUS_INSTANCE_NAME,        PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16,                                               PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,                                                     PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,                                                   PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,                                                PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_DEFINITION_NAME,                  COMMENT_DEFINITION_NAME,                PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_DEFINITION_NAME_ASTERIX, 0, 
        AUTOGEN_OBJ_RES | AUTOGEN_OBJ_TBL | AUTOGEN_OBJ_REF | AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_DONT_GENERATE,                    COMMENT_ISIHDR_DONT_GENERATE,           PROPERTY_FLAG_SIMPLE, AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_DONT_GENERATE_16,                                                         PROPERTY_FLAG_SIMPLE, AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_16, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_DONT_GENERATE_8,                                                          PROPERTY_FLAG_SIMPLE, AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_8, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_DONT_GENERATE_ID,                                                         PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE | AUTOGEN_OBJ_SB | AUTOGEN_OBJ_TRACE, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_FILENAME,                         COMMENT_ISIHDR_FILENAME,                PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_FILENAME_16,                      COMMENT_ISIHDR_FILENAME_16,             PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS,  COMMENT_SUPPORT_DYN_STRUCTS_IN_ISIHDR,  PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_GENERATE_AS_BITFIELD,             COMMENT_ISIHDR_GENERATE_AS_BITFIELD,    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_TBL | AUTOGEN_OBJ_ITEM, AUTOGEN_TBL_BIT | AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_REF)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_GENERATE_AS_BOOL,                 COMMENT_ISIHDR_GENERATE_AS_BOOL,        PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_TBL | AUTOGEN_OBJ_ITEM, AUTOGEN_TBL_CONST | AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_REF)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_AS_ENUM_16,                                                      PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_TBL, AUTOGEN_TBL_CONST)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_AS_ENUM_8,                                                       PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_TBL, AUTOGEN_TBL_CONST)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_GENERATE_BITFIELDS,               COMMENT_ISIHDR_GENERATE_BITFIELDS,      PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_BITTABLE_MASKS,                                                  PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES | AUTOGEN_OBJ_TBL, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_BITTABLE_MASKS_16,                                               PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES | AUTOGEN_OBJ_TBL, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_GENERATE_BOOLS,                   COMMENT_ISIHDR_GENERATE_BOOLS,          PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
	DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_CHOICE_UNIONS,                                                   PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_MERGED_MASKS,                                                    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_MERGED_MASKS_16,                                                 PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_MIN_MAX_CONSTANTS,                                               PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_MIN_MAX_CONSTANTS_16,                                            PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_STRUCT_BYTE_INDEX,                                               PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_STRUCT_BYTE_INDEX_16,                                            PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_GENERATE_SUBMSG_UNIONS_16,                                                PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER,                                                    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16,                                                 PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_MERGED_MASK_PREFIX,                                                       PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    /* 0 to 2 */
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE,                                              PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT,             PROPERTY_PHONET_HEADER_LAYOUT,          PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_SPLIT_AS_ARRAY,                                                           PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_SPLIT_DWORDS_16,                                                          PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED,               COMMENT_ISIHDR_SPLIT_DWORD_SIGNED,      PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED,             COMMENT_ISIHDR_SPLIT_DWORD_UNSIGNED,    PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_SPLIT_WORD_SIGNED,                COMMENT_ISIHDR_SPLIT_WORD_SIGNED,       PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED,              COMMENT_ISIHDR_SPLIT_WORD_UNSIGNED,     PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)

    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,               COMMENT_ISIHDR_STRUCT_LENGTH_NAME,      PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_DEFINITION_NAME, 0, AUTOGEN_OBJ_SB|AUTOGEN_OBJ_SEQ|AUTOGEN_OBJ_MSG|AUTOGEN_OBJ_MSG_BASE|AUTOGEN_OBJ_TRACE|AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_STRUCT_LENGTH_SIZEOF,                                                     PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_SB|AUTOGEN_OBJ_SEQ|AUTOGEN_OBJ_MSG|AUTOGEN_OBJ_MSG_BASE|AUTOGEN_OBJ_TRACE, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_STRUCT_LENGTH_SUM,                                                        PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_SB|AUTOGEN_OBJ_SEQ|AUTOGEN_OBJ_MSG|AUTOGEN_OBJ_MSG_BASE|AUTOGEN_OBJ_TRACE, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE,                                                      PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_SB|AUTOGEN_OBJ_SEQ|AUTOGEN_OBJ_MSG|AUTOGEN_OBJ_MSG_BASE|AUTOGEN_OBJ_TRACE, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_STRUCT_NAME,                      COMMENT_ISIHDR_STRUCT_NAME,             PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_DEFINITION_NAME | PROPERTY_FLAG_OBJ_FLAG_IF_EMPTY, AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR, AUTOGEN_OBJ_SB|AUTOGEN_OBJ_SEQ|AUTOGEN_OBJ_MSG|AUTOGEN_OBJ_MSG_BASE|AUTOGEN_OBJ_TRACE|AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_ISIHDR_STRUCT_PHONET_LENGTH_NAME,                                                PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_DEFINITION_NAME, 0, AUTOGEN_OBJ_RES|AUTOGEN_OBJ_SB|AUTOGEN_OBJ_SEQ|AUTOGEN_OBJ_MSG|AUTOGEN_OBJ_MSG_BASE|AUTOGEN_OBJ_TRACE, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_TITLE,                            COMMENT_ISIHDR_TITLE,                   PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_VARNAME_16,                       COMMENT_ISIHDR_VARNAME_16,              PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
	DEFINE_PROPERTY_S (PROPERTY_ISI_VERSIONING_NOT_SUPPORTED,                                                    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
	DEFINE_PROPERTY_S (PROPERTY_ISI_VERSION_AUTO_GENERATE,                                                       PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OSS(PROPERTY_ITEM_DEFAULT_VALUE,                     "ITEM_DEFAULT_VALUE",                   PROPERTY_FLAG_VALUE | PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_ITEM,
        AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_POINTER | AUTOGEN_ITEM_REF)
    DEFINE_PROPERTY_OSS(PROPERTY_ITEM_EXCEPTIONAL_VALUE,                 "ITEM_LIMITS",                          PROPERTY_FLAG_VALUE | PROPERTY_FLAG_MULTIPLE | PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_ITEM,
        AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_REF)
    DEFINE_PROPERTY_S (PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION,                                                 PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OSS(PROPERTY_ITEM_MAXIMUM_VALUE,                     "ITEM_LIMITS",                          PROPERTY_FLAG_VALUE | PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_ITEM,
        AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_REF)
    DEFINE_PROPERTY_OSS(PROPERTY_ITEM_MINIMUM_VALUE,                     "ITEM_LIMITS",                          PROPERTY_FLAG_VALUE | PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_ITEM,
        AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_REF)

    DEFINE_PROPERTY_OS(PROPERTY_MSG_IS_MEDIA_CTRL_SPECIFIC,              COMMENT_MEDIA_CTRL_SPECIFIC_MSG,        PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_MSG, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_MSG_LENGTH_LIMIT,                                                                PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_MSG, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_MSG_LENGTH_RELATES_TO_DATA_PART_ONLY,                                            PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_MSG, AUTOGEN_OBJ_ANY)

    DEFINE_PROPERTY_S (PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT,                                                   PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_PMD_ANCHOR,                              COMMENT_ANCHOR,                         PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_DONT_GENERATE,                                                               PROPERTY_FLAG_SIMPLE, AUTOGEN_OBJ_IS_NOT_GENERATED_PMD, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_ENVIRONMENT_VARIABLE,                                                        PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALUE | PROPERTY_FLAG_INDEX, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_IS_NOT_PARAMETER,                                                            PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_ITEM, 
        AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_POINTER | AUTOGEN_ITEM_STRING | AUTOGEN_ITEM_REF | AUTOGEN_ITEM_RANGE | AUTOGEN_ITEM_TIMESTAMP)
    DEFINE_PROPERTY_S (PROPERTY_PMD_MESSAGE_IN_SUMMARY,                                                          PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_TRACE | AUTOGEN_OBJ_SB, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_MESSAGE_IS_CARRIER,                                                          PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_TRACE | AUTOGEN_OBJ_SB, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_MESSAGE_IS_NOT_FILTERABLE,                                                   PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_TRACE | AUTOGEN_OBJ_SB, AUTOGEN_OBJ_ANY)
	DEFINE_PROPERTY_S (PROPERTY_PMD_NUMBER_SPECIAL_TYPE,                                                         PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_ITEM_POINTER | AUTOGEN_ITEM_VALUE)
    DEFINE_PROPERTY_OSS(PROPERTY_PMD_PARAMETER,                          "ITEM_PARAMETER",                       PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_ITEM, 
        AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_POINTER | AUTOGEN_ITEM_STRING | AUTOGEN_ITEM_REF | AUTOGEN_ITEM_RANGE | AUTOGEN_ITEM_TIMESTAMP)
    DEFINE_PROPERTY_S (PROPERTY_PMD_PARAMETER_IN_SUMMARY,                                                        PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_ITEM, 
        AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_POINTER | AUTOGEN_ITEM_STRING | AUTOGEN_ITEM_REF | AUTOGEN_ITEM_RANGE | AUTOGEN_ITEM_TIMESTAMP)
    DEFINE_PROPERTY_OS(PROPERTY_PMD_PHONET_DEVICE_ID,                    COMMENT_DEVICE_ID,                      PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_PMD_PHONET_OBJECT_ID,                    COMMENT_OBJECT_ID,                      PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY | PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_PROTOCOL_IS_LE,                                                              PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_PUBLIC,                                                                      PROPERTY_FLAG_SIMPLE, AUTOGEN_OBJ_IS_PMD_PUBLIC, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_RESOURCE_TRC_IS_HW_MASTER,                                                   PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_RESTRICTED,                                                                  PROPERTY_FLAG_SIMPLE, AUTOGEN_OBJ_IS_PMD_RESTRICTED, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON,                                           PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_TRACE | AUTOGEN_OBJ_TRACEGRP, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE,                                                    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_TRACE | AUTOGEN_OBJ_TRACEGRP, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_ACTIVATION_TEXT,                                                       PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_DECODE_TEXT,                                                           PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_TRACE, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT,                                                     PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_TRACEGRP, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_IDENTIFIER,                                                            PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_RES | AUTOGEN_OBJ_TRACEGRP | AUTOGEN_OBJ_TRACE | AUTOGEN_OBJ_MSG, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_LOGICAL_GROUP,                                                         PROPERTY_FLAG_STRING | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_SOURCE,                                                                PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_SOURCE_FLAGS,                                                          PROPERTY_FLAG_VALUE_INDEX, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER,                                                     PROPERTY_FLAG_STRING_INDEX | PROPERTY_FLAG_NONEMPTY | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_TRACE_SOURCE_NAME,                                                           PROPERTY_FLAG_STRING_INDEX | PROPERTY_FLAG_NONEMPTY, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PMD_USE_CONST_TBL_ENTRY_COMMENT,                                                 PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_TBL, AUTOGEN_TBL_CONST)
    DEFINE_PROPERTY_OS(PROPERTY_PROJECT_CONFIDENTIALITY,                 COMMENT_CONFIDENTIALITY,                PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_PROJECT_NAME,                            COMMENT_PROJECT_NAME,                   PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PROJECT_NOKIA_ENTITY,                                                            PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_PROJECT_OWNER_NAME,                      COMMENT_OWNER_NAME,                     PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_PROJECT_SITE_NAME,                       COMMENT_SITE_NAME,                      PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_PROTOCOL_HAS_NO_MESSAGES,                                                        PROPERTY_FLAG_SIMPLE, AUTOGEN_RES_HAS_NO_MESSAGES, AUTOGEN_OBJ_RES, RESOURCE_PROTOCOL | RESOURCE_OST)
    DEFINE_PROPERTY_S (PROPERTY_SB_LENGTH_LIMIT,                                                                 PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_SB, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_SB_LENGTH_MISSING,                                                               PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_SB, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4,                                                    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_SB, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_8,                                                    PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_SB, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY,     COMMENT_SB_LENGTH_RELATES_TO_DATA_PART_ONLY, PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_SB, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_SEQ_ASSIGN_MESSAGE_TYPE,                                                         PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_SEQ, AUTOGEN_OBJ_ANY)

	DEFINE_PROPERTY_S (PROPERTY_STRING_BCD_MAP,                                                                  PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_ITEM_STRING)
    DEFINE_PROPERTY_S (PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH,                                     PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_ITEM_STRING)
    DEFINE_PROPERTY_S (PROPERTY_STRING_MAXIMUM_LENGTH,                                                           PROPERTY_FLAG_VALUE, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_ITEM_STRING)
    DEFINE_PROPERTY_S (PROPERTY_STRING_UNFORMATTED,                                                              PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_ITEM, AUTOGEN_ITEM_STRING)

    DEFINE_PROPERTY_OS(PROPERTY_SUBMSG_NAMES_ARE_UNIQUE,                 COMMENT_SUBMSG_NAMES_ARE_UNIQUE,        PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)

    DEFINE_PROPERTY_S (PROPERTY_SUPPRESS_AUTOGEN_WARNINGS,                                                       PROPERTY_FLAG_SIMPLE, 0, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY)

    DEFINE_PROPERTY_S (PROPERTY_TSA_NAMESPACE,                                                                   PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
/*
    DEFINE_PROPERTY_S (PROPERTY_UNSUPPORTED_COMMON_MESSAGE,                                                      PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
	DEFINE_PROPERTY_S (PROPERTY_UNSUPPORTED_MEDIA_CONTROL_MESSAGE,                                               PROPERTY_FLAG_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
*/
    DEFINE_PROPERTY_OS(PROPERTY_VERSION_NOT_YET_SUPPORTED,               COMMENT_ISI_VERSION_NOT_YET_SUPPORTED,  PROPERTY_FLAG_SIMPLE, AUTOGEN_VERSION_NOT_YET_SUPPORTED,   AUTOGEN_OBJ_VERSION, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_VERSION_NO_LONGER_SUPPORTED,             COMMENT_ISI_VERSION_NO_LONGER_SUPPORTED,PROPERTY_FLAG_SIMPLE, AUTOGEN_VERSION_NO_LONGER_SUPPORTED, AUTOGEN_OBJ_VERSION, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_S (PROPERTY_XML_FILENAME,                                                                    PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALID_ISIHDR_STRING, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)


	/* obsolete properties */
    DEFINE_PROPERTY_OS(PROPERTY_HTML_PCMS_ITEM,                         COMMENT_PCMS_HTML_ITEM,                 PROPERTY_FLAG_STRING | PROPERTY_FLAG_OBSOLETE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_HTML_PCMS_PART,                         COMMENT_PCMS_HTML_PART,                 PROPERTY_FLAG_STRING | PROPERTY_FLAG_OBSOLETE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_CONTINUUS_PROJECT_NAME,           COMMENT_CONTINUUS_PROJECT_NAME,         PROPERTY_FLAG_STRING | PROPERTY_FLAG_OBSOLETE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_PCMS_ITEM,                       COMMENT_PCMS_ITEM,                      PROPERTY_FLAG_STRING | PROPERTY_FLAG_OBSOLETE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_PCMS_ITEM_16,                    COMMENT_PCMS_ISIHDR_ITEM_16,            PROPERTY_FLAG_STRING | PROPERTY_FLAG_OBSOLETE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_PCMS_PART,                       COMMENT_PCMS_ISIHDR_PART,               PROPERTY_FLAG_STRING | PROPERTY_FLAG_OBSOLETE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)
    DEFINE_PROPERTY_OS(PROPERTY_ISIHDR_PCMS_WORKSET,                    COMMENT_PCMS_WORKSET,                   PROPERTY_FLAG_STRING | PROPERTY_FLAG_OBSOLETE, 0, AUTOGEN_OBJ_RES, AUTOGEN_OBJ_ANY)

};


/* List of current properties */
static autogen_prop *s_current_prop_list = NULL;

/* End of the list of current properties. Properties are added here. */
static autogen_prop *s_current_prop_list_end = NULL;


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* Retrieves a type pointer for the given property */
static const autogen_prop_type *get_type(autogen_property_id id)
    {
    if (id < 0 || id >= PROPERTY_TOTAL_COUNT)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_ALL, 0,
                        "Property id is not valid");
        }
    return &prop_table[id];
    }

/* Check whether the given property is valid. If not, local environment runs
   will stop with a fatal error, while product environment runs attempts
   to force the property to be valid. Returns TRUE if the property should
   be inserted, and FALSE if it should be ignored. */
static int check_prop(autogen_prop *prop,
                      const char *filename)
    {
    const autogen_prop_type *type = NULL;
    if (prop->id < 0 || prop->id >= PROPERTY_TOTAL_COUNT)
        {
        util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property id is not valid");
        return FALSE; /* Don't insert the property in the product environment, either */
        }
    type = get_type(prop->id);

    /* Output a warning if the property is obsolete */
    if (type->property_flags & PROPERTY_FLAG_OBSOLETE)
        {
        util_error_line(filename, prop->lineno, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' is obsolete", prop_name(prop));
        return FALSE;
        }

    /* Check that index is not used with non-indexed properties */
    if ((prop->flags & PROPERTY_FLAG_INDEX) &&
        !(type->property_flags & PROPERTY_FLAG_INDEX))
        {
        util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' cannot be given an index", prop_name(prop));
        prop->index = 0;
        prop->flags &= ~PROPERTY_FLAG_INDEX;
        }

    /* Check that index is always used with indexed properties */
    if (!(prop->flags & PROPERTY_FLAG_INDEX) &&
        (type->property_flags & PROPERTY_FLAG_INDEX))
        {
        util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' must be given an index", prop_name(prop));
        prop->flags |= PROPERTY_FLAG_INDEX;
        }

    /* Check that simple properties are created as such */
    if ((prop->flags & PROPERTY_FLAG_SIMPLE) &&
        !(type->property_flags & PROPERTY_FLAG_SIMPLE))
        {
        util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' cannot have a value", prop_name(prop));
        prop->flags &= ~PROPERTY_FLAG_ALLTYPES;
        prop->flags |= type->property_flags & PROPERTY_FLAG_ALLTYPES;
        prop->str = "";  /* Guard against NULL strings */
        }

    /* Check that numeric values are only used with properties allowing that */
    if ((prop->flags & PROPERTY_FLAG_VALUE) &&
        !(type->property_flags & PROPERTY_FLAG_VALUE))
        {
        util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' is not a number", prop_name(prop));

        prop->flags &= ~PROPERTY_FLAG_ALLTYPES;
        prop->flags |= type->property_flags & PROPERTY_FLAG_ALLTYPES;
        prop->str = "";  /* Guard against NULL strings */
        }

    /* Check that string only values are only used with properties allowing that */
    if ((prop->flags & PROPERTY_FLAG_STRING) &&
        !(type->property_flags & PROPERTY_FLAG_STRING))
        {
        util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' is not a string", prop_name(prop));

        prop->flags &= ~PROPERTY_FLAG_ALLTYPES;
        prop->flags |= type->property_flags & PROPERTY_FLAG_ALLTYPES;
        }

    /* Perform a range of checks on strings */
    if (prop->flags & PROPERTY_FLAG_STRING)
        {
        /* Check that strings are not NULL */
        if (prop->str == NULL)
            {
            util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                            "The value of a string property must not be NULL");
            prop->str = "";
            }

        /* Check that strings with the NONEMPTY flag are not empty */
        if ((type->property_flags & PROPERTY_FLAG_NONEMPTY) && !*prop->str)
            {
            util_error_line(filename, prop->lineno, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                            "The value of the property '%s' must not be the empty string",
                            prop_name(prop));
            prop->str = "empty";
            return FALSE;
            }

        /* Check that a string to be used as a C identifier is valid */
        if ((type->property_flags & PROPERTY_FLAG_VALID_DEFINITION_NAME) &&
            *prop->str &&
            !check_c_name(filename, prop->lineno, prop_name(prop), prop->str, CHECK_NAME_NO_FLAGS))
            {
            static int next_ident = 1;
            char identifier[100];
            util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                            "The value of the property '%s' must be a valid C identifier",
                            prop_name(prop));
            sprintf(identifier, "bad_identifier_%d", next_ident++);
            prop->str = pmd_heap_strdup(identifier);
            return FALSE;
            }
        /* Check that a string to be used as a C identifier (with asterix) is valid */
        else
        if ((type->property_flags & PROPERTY_FLAG_VALID_DEFINITION_NAME_ASTERIX) &&
            *prop->str &&
            !check_c_name(filename, prop->lineno, prop_name(prop), prop->str, CHECK_NAME_ALLOW_ASTERIX))
            {
            static int next_ident = 1;
            char identifier[100];
            util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                            "The value of the property '%s' must be a valid C identifier",
                            prop_name(prop));
            sprintf(identifier, "bad_identifier_%d", next_ident++);
            prop->str = pmd_heap_strdup(identifier);
            return FALSE;
            }

        /* Check that we don't introduce comment symbols in ISI headers */
        if ((type->property_flags & PROPERTY_FLAG_VALID_ISIHDR_STRING) &&
            (strstr(prop->str, "/*") || strstr(prop->str, "*/")))
            {
            util_error_line(filename, prop->lineno, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                            "The property string '%s' is not valid, as is contains '/*' or '*/' codes",
                            prop_name(prop));
            prop->str = "invalid";
            return FALSE;
            }
        } /* End of string checks */

    return TRUE;
    }

/* Compares two properties, returning -1, 0 or 1 depending on the result */
static int prop_comp(const autogen_prop *prop1, const autogen_prop *prop2)
    {
    /* Compare IDs */
    if (prop1->id < prop2->id)
        {
        return -1;
        }
    else if (prop1->id > prop2->id)
        {
        return 1;
        }

    /* Compare index */
    if (prop1->index < prop2->index)
        {
        return -1;
        }
    else if (prop1->index > prop2->index)
        {
        return 1;
        }

    /* compare strings */
    if (get_type(prop1->id)->property_flags & PROPERTY_FLAG_MULTIPLE)
        {
        if (strcmp(prop1->str, prop2->str) == 0)
            {
            return 0;
            }

        if ((prop1->flags & PROPERTY_FLAG_VALUE) && prop1->value  == prop2->value)
            {
            return 0;
            }

        return 1;
        }

    /* The properties are equal */
    return 0;
    }


/* Inserts the given property in the property list for the given object.
   Insertion is done before identical (multiple) properties, or in the proper
   index order for indexed properties. The property is assumed to be valid.
   No flag updates on the object are made. 

   Returns TRUE if flags should be updated to the object after it is inserted
*/
static int insert_prop(autogen_obj *obj,
                       autogen_prop *prop,
                       const char *filename)
    {
    /* Points to the next pointer pointing to the property we're examining */
    autogen_prop **ptr_to_next = &obj->prop_list;

    /* Find the next pointer in the property just before this one */
    while (*ptr_to_next && prop_comp(prop, *ptr_to_next) > 0)
        {
        ptr_to_next = &(*ptr_to_next)->next;
        }

    /* If there's a successor, check that they don't collide */
    if (*ptr_to_next)
        {
        autogen_prop *successor = *ptr_to_next;
        if (prop_comp(prop, successor) == 0)
            {
            /* They're identical. Check if we're inserting a new default value */
            if (prop->flags & PROPERTY_FLAG_DEFAULT)
                {
                /* Check that we've only assigned a default value once */
                if ((successor->flags & PROPERTY_FLAG_DEFAULT) &&
                    (successor->flags & prop->flags & PROPERTY_FLAG_ALLTYPES))
                    {
                    util_error_line(filename, prop->lineno, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                                    "Two default values were assigned to the property '%s'",
                                    prop_name(prop));
                    }

                /* Just ignore the default value if we already have a value */
                return FALSE;
                }

            /* They're identical. Check if we should issue a warning. */
            if (get_type(prop->id)->property_flags & PROPERTY_FLAG_MULTIPLE)
                {
                util_error_line(filename, prop->lineno, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                                "Redefinition of property '%s' with the value %s",
                                prop_name(prop), prop->str);
                /* We should accept the redefinition, so we just continue in this casee */
                }
            else
            if (!(successor->flags & PROPERTY_FLAG_DEFAULT))
                {
                util_error_line(filename, prop->lineno, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                                "Property '%s' can only be defined once for each object",
                                prop_name(prop));
                /* In order to be backward compatible, we accept a redefinition and use
                   the last value given. So we just continue in this case. */
                }

            /* Update the values in the existing property */
            if (prop->flags & PROPERTY_FLAG_STRING)
                {
                successor->flags |= PROPERTY_FLAG_STRING;
                successor->str = prop->str;
                }
            if (prop->flags & PROPERTY_FLAG_VALUE)
                {
                successor->flags |= PROPERTY_FLAG_VALUE;
                successor->value = prop->value;
                }

            successor->flags &= ~PROPERTY_FLAG_DEFAULT;

            /* Return since we don't want to insert the property after all */
            return TRUE;
            }
        }

    /* At this point, we know that the new property should be inserted */
    prop->next = *ptr_to_next;
    *ptr_to_next = prop;

    return TRUE;
    }

/* Allocates a new simple property on the PMD heap */
static autogen_prop *create_simple(autogen_property_id id)
    {
    autogen_prop *prop = (autogen_prop *) pmd_heap_alloc(sizeof(autogen_prop));
    prop->flags = PROPERTY_FLAG_SIMPLE;
    prop->id = id;
    return prop;
    }

/* Allocates a new string property on the PMD heap */
static autogen_prop *create_string(autogen_property_id id,
                                   const char *str)
    {
    autogen_prop *prop = (autogen_prop *) pmd_heap_alloc(sizeof(autogen_prop));
    prop->flags = PROPERTY_FLAG_STRING;
    prop->id = id;
    prop->str = str;
    return prop;
    }

/* Allocates a new combined string value property on the PMD heap */
static autogen_prop *create_value_string(autogen_property_id id,
#if (PMD_FILE_FORMAT >= 600)
                                         unsigned long long value,
#else
                                         unsigned int value,
#endif
                                         int is_negative,
                                         const char *str)
    {
    autogen_prop *prop = (autogen_prop *) pmd_heap_alloc(sizeof(autogen_prop));
    prop->flags = PROPERTY_FLAG_VALUE;
    prop->id = id;
    prop->value = value;
    prop->str = str;
    if (is_negative)
        {
        prop->flags |= PROPERTY_FLAG_NEGATIVE;
        }
    return prop;
    }

/* Sets the oldname flag and line number depending on the arguments. Returns prop. */
static autogen_prop *set_line_oldname(autogen_prop *prop, int lineno, int is_oldname)
    {
    prop->lineno = lineno;
    if (is_oldname)
        {
        prop->flags |= PROPERTY_FLAG_USE_OLDNAME;
        }
    return prop;
    }

/* Sets the index and the index flag */
static void set_index(autogen_prop *prop,
                      int index)
    {
    prop->flags |= PROPERTY_FLAG_INDEX;
    prop->index = index;
    }

/* Adds the given property to the end of the current list. prop->next must be NULL. */
static void add_to_current(autogen_prop *prop)
    {
    if (s_current_prop_list_end)
        {
        s_current_prop_list_end->next = prop;
        }
    else
        {
        s_current_prop_list = prop;
        }
    s_current_prop_list_end = prop;
    }

/* ============================================================================================= */
/* Functions working on the current property list */
/* ============================================================================================= */

/* Adds a simple property to the current property list */
void prop_add_simple(autogen_property_id id, int lineno, int is_oldname)
    {
    autogen_prop *prop = create_simple(id);
    set_line_oldname(prop, lineno, is_oldname);
    add_to_current(prop);
    }

/* Adds a string property to the current property list */
void prop_add_string(autogen_property_id id, const char *str, int lineno, int is_oldname)
    {
    autogen_prop *prop = create_string(id, str);
    set_line_oldname(prop, lineno, is_oldname);
    add_to_current(prop);
    }

/* Adds a value property to the current property list */
void prop_add_value(autogen_property_id id,
#if (PMD_FILE_FORMAT >= 600)
                    unsigned long long value,
#else
                    unsigned int value,
#endif
                    int is_negative,
                    const char* str,
                    int lineno,
                    int is_oldname)
    {
    autogen_prop *prop = create_value_string(id, value, is_negative, str);
    set_line_oldname(prop, lineno, is_oldname);
    add_to_current(prop);
    }

/* Adds an indexed string property to the current property list */
void prop_add_indexed_string(autogen_property_id id,
                             const char *str,
                             int index,
                             int lineno,
                             int is_oldname)
    {
    autogen_prop *prop = create_string(id, str);
    set_line_oldname(prop, lineno, is_oldname);
    set_index(prop, index);
    add_to_current(prop);
    }

/* Adds an indexed value property to the current property list */
void prop_add_indexed_value(autogen_property_id id,
#if (PMD_FILE_FORMAT >= 600)
                            unsigned long long value,
#else
                            unsigned int value,
#endif
                            int is_negative,
                            const char* str,
                            int index,
                            int lineno,
                            int is_oldname)
    {
    autogen_prop *prop = create_value_string(id, value, is_negative, str);
    set_line_oldname(prop, lineno, is_oldname);
    set_index(prop, index);
    add_to_current(prop);
    }

/* Adds a default string property to the current property list */
void prop_add_string_default(autogen_property_id id,
                             const char *str)
    {
    autogen_prop *prop = create_string(id, str);
    prop->flags |= PROPERTY_FLAG_DEFAULT;
    add_to_current(prop);
    }

/* Adds a default value property to the current property list */
void prop_add_value_default(autogen_property_id id,
                            unsigned int value,
                            int is_negative,
                            const char* str)
    {
    autogen_prop *prop = create_value_string(id, value, is_negative, str);
    prop->flags |= PROPERTY_FLAG_DEFAULT;
    add_to_current(prop);
    }

/* Assigns all properties in the current property list to the given object and clears the list */
void prop_add_current_to_object(autogen_obj *obj, const char *filename)
    {
    while (s_current_prop_list)
        {
        autogen_prop *prop = s_current_prop_list;
        s_current_prop_list = s_current_prop_list->next;
        prop->next = NULL;
        prop_add_to_object(obj, prop, filename);
        }
    s_current_prop_list_end = NULL;
    }


/* Checks that the current list is empty, and erases it and prints a warning if not. */
void prop_force_current_empty(const char *filename)
    {
    if (s_current_prop_list != NULL)
        {
        util_error_line(filename, s_current_prop_list->lineno, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0, 
                        "Orphaned properties ignored");
        s_current_prop_list = NULL;
        }
    s_current_prop_list_end = NULL;
    }


/* ============================================================================================= */
/* Functions adding properties directly to objects */
/* ============================================================================================= */

/* Adds a simple property to the given object */
void prop_add_simple_to_object(autogen_obj *obj,
                               autogen_property_id id,
                               const char *filename,
                               int lineno,
                               int is_oldname)
    {
    autogen_prop *prop = create_simple(id);
    set_line_oldname(prop, lineno, is_oldname);
    prop_add_to_object(obj, prop, filename);
    }

/* Adds a string property to the given object */
void prop_add_string_to_object(autogen_obj *obj,
                               autogen_property_id id,
                               const char *str,
                               const char *filename,
                               int lineno,
                               int is_oldname)
    {
    autogen_prop *prop = create_string(id, str);
    set_line_oldname(prop, lineno, is_oldname);
    prop_add_to_object(obj, prop, filename);
    }

/* Adds a value property to the given object */
void prop_add_value_to_object(autogen_obj *obj,
                              autogen_property_id id,
                              unsigned int value,
                              int is_negative,
                              const char* str,
                              const char *filename,
                              int lineno,
                              int is_oldname)
    {
    autogen_prop *prop = create_value_string(id, value, is_negative, str);
    set_line_oldname(prop, lineno, is_oldname);
    prop_add_to_object(obj, prop, filename);
    }

/* Adds an indexed string property to the given object */
void prop_add_indexed_string_to_object(autogen_obj *obj,
                                       autogen_property_id id,
                                       const char *str,
                                       int index,
                                       const char *filename,
                                       int lineno,
                                       int is_oldname)
    {
    autogen_prop *prop = create_string(id, str);
    set_line_oldname(prop, lineno, is_oldname);
    set_index(prop, index);
    prop_add_to_object(obj, prop, filename);
    }

/* Adds an indexed value property to the given object */
void prop_add_indexed_value_to_object(autogen_obj *obj,
                                      autogen_property_id id,
#if (PMD_FILE_FORMAT >= 600)
                                      unsigned long long value,
#else
                                      unsigned int value,
#endif
                                      int is_negative,
                                      const char* str,
                                      int index,
                                      const char *filename,
                                      int lineno,
                                      int is_oldname)
    {
    autogen_prop *prop = create_value_string(id, value, is_negative, str);
    set_line_oldname(prop, lineno, is_oldname);
    set_index(prop, index);
    prop_add_to_object(obj, prop, filename);
    }

/* Adds a combined string and value property to the current property list */
void prop_add_value_string_to_object(autogen_obj *obj,
                                     autogen_property_id id,
                                     unsigned int value,
                                     int is_negative,
                                     const char *str,
                                     const char *filename,
                                     int lineno,
                                     int is_oldname)
    {
    autogen_prop *prop = create_value_string(id, value, is_negative, str);
    set_line_oldname(prop, lineno, is_oldname);
    prop_add_to_object(obj, prop, filename);
    }

/* Assigns the given property to the given object */
void prop_add_to_object(autogen_obj *obj,
                        autogen_prop *prop,
                        const char *filename)
    {
    const autogen_prop_type *type = get_type(prop->id);
    const char *name = (prop->flags & PROPERTY_FLAG_USE_OLDNAME) ? type->oldname : type->name;

    /* Do all checks on the property itself */
    if (!check_prop(prop, filename))
        {
        /* The checks indicated that the property should not be inserted */
        return;
        }

    /* Check that the property is acceptable to the object */
    if ((obj->type & ~type->object_type_mask) || (obj->subtype & ~type->object_subtype_mask))
        {
        util_error_line(filename, prop->lineno, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' is not valid in this context", name);
        return; /* Don't add the property in Product environment, either */
        }

    /* Add the property to the object */
    if (!insert_prop(obj, prop, filename))
        return; /* Don't update flags */

    /* Update the flags of the object (if not default property) */
    if (!(prop->flags & PROPERTY_FLAG_DEFAULT))
        {
        if (type->property_flags & PROPERTY_FLAG_OBJ_FLAG_IF_EMPTY)
            {
            /* Special flag handling: Set the flag if the string is empty */
            if (prop->flags & PROPERTY_FLAG_STRING)
                {
                if (*prop->str)
                    {
                    obj->flag &= ~type->object_flags;
                    }
                else
                    {
                    obj->flag |= type->object_flags;
                    }
                }
            else
                {
                util_error_line(filename, prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                                "Property '%s' has not been assigned a string value, "
                                "but its flag settings require this", name);
                }
            }
        else
            {
            /* No special flag handling, just set the flags that were defined on the property */
            obj->flag |= type->object_flags;
            }
        }
    }


#if (PMD_FILE_FORMAT >= 600)
void prop_object_add_value(autogen_obj *obj, autogen_property_id id, unsigned long long value, int is_negative)
#else
void prop_object_add_value(autogen_obj *obj, autogen_property_id id, unsigned int value, int is_negative)
#endif
    {
    /* Search for a property with the right ID */
    autogen_prop *prop = obj->prop_list;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to update non-existing value property '%s'",
                        get_type(id)->name);
        return;
        }

    /* Check that we haven't found an indexed one */
    if (prop->flags & PROPERTY_FLAG_INDEX)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to update indexed property '%s'",
                        prop_name(prop));
        return;
        }

    prop->flags |= PROPERTY_FLAG_VALUE;
    prop->value = value;
    if (is_negative)
        {
        prop->flags |= PROPERTY_FLAG_NEGATIVE;
        }
    else
        {
        prop->flags &= ~PROPERTY_FLAG_NEGATIVE;
        }
    }


/* Updates an existing value (or the value of an value_string) property on an object */
void prop_object_update_value(autogen_obj *obj,
                              autogen_property_id id,
                              unsigned int value,
                              int is_negative)
    {
    /* Search for a property with the right ID */
    autogen_prop *prop = obj->prop_list;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to update non-existing value property '%s'",
                        get_type(id)->name);
        return;
        }

    /* Check that we haven't found an indexed one */
    if (prop->flags & PROPERTY_FLAG_INDEX)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to update indexed property '%s'",
                        prop_name(prop));
        return;
        }

    /* Check that it's a value */
    if (!(prop->flags & PROPERTY_FLAG_VALUE))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to update non-numeric property '%s' with a number",
                        prop_name(prop));
        return;
        }

    prop->value = value;
    if (is_negative)
        {
        prop->flags |= PROPERTY_FLAG_NEGATIVE;
        }
    else
        {
        prop->flags &= ~PROPERTY_FLAG_NEGATIVE;
        }
    }


/* Updates an existing string property on an object */
void prop_object_update_string(autogen_obj *obj,
                               autogen_property_id id,
                               const char* value)
    {
    /* Search for a property with the right ID */
    autogen_prop *prop = obj->prop_list;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to update non-existing string property '%s'",
                        get_type(id)->name);
        return;
        }

    /* Check that it's a string */
    if (!(prop->flags & PROPERTY_FLAG_STRING))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to update numeric property '%s' with a string",
                        prop_name(prop));
        return;
        }

    prop->str = value;
    }


/* Adds a copy of all properties in the given list to the given object */
void prop_copy_list_to_object(const autogen_prop* prop_list,
                              autogen_obj *obj,
                              const char *filename)
    {
    while (prop_list)
        {
        prop_add_to_object(obj, prop_copy(prop_list), filename);
        prop_list = prop_list->next;
        }
    }


/* ============================================================================================= */
/* Functions retrieving single property values */
/* ============================================================================================= */

/* Retrieves a string property. If not present, this function returns NULL */
const char *prop_get_string(const autogen_obj *obj, autogen_property_id id)
    {
    return prop_get_string_default(obj, id, NULL);
    }

/* Retrieves a string property. If not present, this function returns the given default string */
const char *prop_get_string_default(const autogen_obj *obj, autogen_property_id id, const char *def)
    {
    /* Search for a property with the right ID */
    const autogen_prop *prop = (obj != NULL) ? obj->prop_list : s_current_prop_list;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        return def;
        }

    /* Check that we haven't found an indexed one */
    if (prop->flags & PROPERTY_FLAG_INDEX)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to retrieve indexed property '%s' without an index",
                        prop_name(prop));
        return def;
        }

    /* Check that it's a string */
    if (!(prop->flags & (PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALUE)))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to retrieve non-string property '%s' as a string",
                        prop_name(prop));
        return def;
        }

    /* Return the property string */
    return prop->str;
    }

/* Retrieves a value property. If not present, this function returns 0 */
#if (PMD_FILE_FORMAT >= 600)
unsigned long long prop_get_value(const autogen_obj *obj, autogen_property_id id)
#else
unsigned int prop_get_value(const autogen_obj *obj, autogen_property_id id)
#endif
    {
    return prop_get_value_default(obj, id, 0);
    }

/* Retrieves a value property. If not present, this function returns the given default value */
#if (PMD_FILE_FORMAT >= 600)
unsigned long long prop_get_value_default(const autogen_obj *obj, autogen_property_id id, unsigned int def)
#else
unsigned int prop_get_value_default(const autogen_obj *obj, autogen_property_id id, unsigned int def)
#endif
    {
    /* Search for a property with the right ID */
    const autogen_prop *prop = (obj != NULL) ? obj->prop_list : s_current_prop_list;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        return def;
        }

    /* Check that we haven't found an indexed one */
    if (prop->flags & PROPERTY_FLAG_INDEX)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to retrieve indexed property '%s' without an index",
                        prop_name(prop));
        return def;
        }

    /* Check that it's a value */
    if (!(prop->flags & PROPERTY_FLAG_VALUE) && !(get_type(prop->id)->property_flags & PROPERTY_FLAG_VALUE))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to retrieve non-numeric property '%s' as a number",
                        prop_name(prop));
        return def;
        }

    /* Return the property value */
    return prop->value;
    }


/* ============================================================================================= */
/* Functions retrieving indexed property values */
/* ============================================================================================= */

/* Retrieves a string property with the given index. If not present, this function returns NULL */
const char *prop_get_string_indexed(const autogen_obj *obj, autogen_property_id id, int index)
    {
    return prop_get_string_indexed_default(obj, id, index, NULL);
    }

/* Retrieves a string property with the given index. If not present, this function returns the given default string */
const char *prop_get_string_indexed_default(const autogen_obj *obj, autogen_property_id id, int index, const char *def)
    {
    /* Search for a property with the right ID and index */
    const autogen_prop *prop = (obj != NULL) ? obj->prop_list : s_current_prop_list;
    while (prop && (prop->id != id || (prop->id == id && prop->index != index)))
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id || prop->index != index)
        {
        return def;
        }

    /* Check that we have found an indexed one */
    if (!(prop->flags & PROPERTY_FLAG_INDEX))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to retrieve non-indexed property '%s' with an index",
                        prop_name(prop));
        return def;
        }

    /* Check that it's a string */
    if (!(prop->flags & (PROPERTY_FLAG_STRING | PROPERTY_FLAG_VALUE)))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to retrieve non-string property '%s' as a string",
                        prop_name(prop));
        return def;
        }

    /* Return the property value */
    return prop->str;
    }

/* Retrieves a value property with the given index. If not present, this function returns 0 */
#if (PMD_FILE_FORMAT >= 600)
unsigned long long prop_get_value_indexed(const autogen_obj *obj, autogen_property_id id, int index)
#else
unsigned int prop_get_value_indexed(const autogen_obj *obj, autogen_property_id id, int index)
#endif
    {
    return prop_get_value_indexed_default(obj, id, index, 0);
    }

/* Retrieves a value property with the given index. If not present, this function returns the given default value */
#if (PMD_FILE_FORMAT >= 600)
unsigned long long prop_get_value_indexed_default(const autogen_obj *obj, autogen_property_id id, int index, unsigned int def)
#else
unsigned int prop_get_value_indexed_default(const autogen_obj *obj, autogen_property_id id, int index, unsigned int def)
#endif
    {
    /* Search for a property with the right ID and index */
    const autogen_prop *prop = (obj != NULL) ? obj->prop_list : s_current_prop_list;
    while (prop && (prop->id != id || (prop->id == id && prop->index != index)))
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id || prop->index != index)
        {
        return def;
        }

    /* Check that we have found an indexed one */
    if (!(prop->flags & PROPERTY_FLAG_INDEX))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to retrieve non-indexed property '%s' with an index",
                        prop_name(prop));
        return def;
        }

    /* Check that it's a value */
    if (!(prop->flags & PROPERTY_FLAG_VALUE))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Attempt to retrieve non-numeric property '%s' as a number",
                        prop_name(prop));
        return def;
        }

    /* Return the property value */
    return prop->value;
    }


/* ============================================================================================= */
/* Functions browsing multiple property values */
/* ============================================================================================= */

/* Finds the first property with the given ID in a list of properties, or NULL if not found. */
const autogen_prop *prop_list_find_first(const autogen_prop *prop, autogen_property_id id)
    {
    /* Search for a property with the right ID */
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        return NULL;
        }

    return prop;
    }

/* Finds the next property with the same ID as prop_find_first, or NULL if not found. */
const autogen_prop *prop_list_find_next(const autogen_prop *prop)
    {
    /* Search for a property with the right ID, starting with the next in line */
    autogen_property_id id = prop->id;
    prop = prop->next;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        return NULL;
        }

    return prop;
    }



/* Finds the first property with the given ID, or NULL if not found. */
const autogen_prop *prop_find_first(const autogen_obj *obj, autogen_property_id id)
    {
    /* Search for a property with the right ID */
    const autogen_prop *prop = (obj != NULL) ? obj->prop_list : s_current_prop_list;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        return NULL;
        }

    return prop;
    }

/* Finds the next property with the same ID as prop_find_first, or NULL if not found. */
const autogen_prop *prop_find_next(const autogen_prop *prop)
    {
    /* Search for a property with the right ID, starting with the next in line */
    autogen_property_id id = prop->id;
    prop = prop->next;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Check if it's found */
    if (!prop || prop->id != id)
        {
        return NULL;
        }

    return prop;
    }

/* Retrieves the count of the given property items for the given object */
int prop_count(const autogen_obj *obj, autogen_property_id id)
    {
    /* Find the first with the right ID */
    int count = 0;
    const autogen_prop *prop = (obj != NULL) ? obj->prop_list : s_current_prop_list;
    while (prop && prop->id != id)
        {
        prop = prop->next;
        }

    /* Look through all properties with the right ID */
    while (prop && prop->id == id)
        {
        count++;
        prop = prop->next;
        }

    return count;
    }


/* ============================================================================================= */
/* Miscellaneous functions */
/* ============================================================================================= */

/* Allocates a copy of the given property on the PMD heap */
autogen_prop* prop_copy(const autogen_prop* prop)
    {
    autogen_prop* new_prop = (autogen_prop*)pmd_heap_alloc(sizeof(autogen_prop));

    new_prop->id    = prop->id;
    new_prop->flags = prop->flags;
    new_prop->index = prop->index;
    new_prop->str   = prop->str;
    new_prop->value = prop->value;

    return new_prop;
    }

/* Checks whether the given object has the given property */
int prop_has(const autogen_obj *obj, autogen_property_id id)
    {
    return prop_find_first(obj, id) != NULL;
    }

/* Checks if the given object has a non-empty string value as the given property */
int prop_has_valid_string(const autogen_obj *obj, autogen_property_id id)
    {
    const char *str = prop_get_string(obj, id);
    if (!str || !*str)
        {
        return FALSE;
        }
    return TRUE;
    }

/* Checks if the given object has value as the given property */
int prop_has_value(const autogen_obj *obj, autogen_property_id id)
    {
    const autogen_prop* prop = prop_find_first(obj, id);

    return (prop && (prop->flags & PROPERTY_FLAG_VALUE));
    }

/* Checks if the given property may be set without a value */
int prop_is_simple(autogen_property_id id)
    {
    return (get_type(id)->property_flags & PROPERTY_FLAG_SIMPLE) != 0;
    }

/* Checks if the given property is a string */
int prop_is_string(autogen_property_id id)
    {
    return (get_type(id)->property_flags & PROPERTY_FLAG_STRING) != 0;
    }

/* Checks if the given property may be given a numeric value */
int prop_is_value(autogen_property_id id)
    {
    return (get_type(id)->property_flags & PROPERTY_FLAG_VALUE) != 0;
    }

/* Retrieves the name for this property as it has been used */
const char *prop_name(const autogen_prop *prop)
    {
    const autogen_prop_type *type = NULL;
    if (prop == NULL)
        {
        return "(null)";
        }
    type = get_type(prop->id);
    if (prop->flags & PROPERTY_FLAG_USE_OLDNAME)
        {
        if (type->oldname != NULL)
            {
            return type->oldname;
            }
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' was marked as using an old name, but no old name was defined",
                        type->name);
        }
    return type->name;
    }

/* Verifies that the property table IDs are correct. Should only be done once. */
void check_prop_table()
    {
    unsigned int cnt;
    for (cnt = 0; cnt < PROPERTY_TOTAL_COUNT; cnt++)
        {
        if ((unsigned int) prop_table[cnt].id != cnt)
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                            "Expected id %u for property %s, found id %u",
                            cnt, prop_table[cnt].name, prop_table[cnt].id);
            }

        if ((prop_table[cnt].property_flags & PROPERTY_FLAG_MULTIPLE) &&
            (prop_table[cnt].property_flags & (PROPERTY_FLAG_DEFAULT | PROPERTY_FLAG_SIMPLE)))
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                            "Dafault/simple property flag can't be used with multiple (%s)",
                            prop_table[cnt].name);
            }

        if (cnt > 0 &&
            !(prop_table[cnt].property_flags & PROPERTY_FLAG_OBSOLETE) &&
            strcmp(prop_table[cnt-1].name, prop_table[cnt].name) >= 0)
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                            "Properties %s and %s are not ordered alphabetically",
                            prop_table[cnt-1].name, prop_table[cnt].name);
            }
        }
    }

/* Gets the flag attribute for the given property */
extern int prop_get_flags(const autogen_obj *obj, autogen_property_id id)
    {
    const autogen_prop* prop = prop_find_first(obj, id);
    if (prop)
        {
        return prop->flags;
        }
    else
        {
        return 0;
        }
    }
