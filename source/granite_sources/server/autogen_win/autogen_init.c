/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_init.c
                --------------
                SW Module






Project:          autogen

%name:            autogen_init.c %
%version:         co1tss#334 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 12:37:18 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file contains initialization functions to be called as first
    step in the macro implementations. The functions check and verify each of 
    the arguments (which are exactly the same as the macro arguments), and
    report fatal and syntax errors to the log file autogen.log.
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_ref.h"
#include "autogen_object.h"
#include "autogen_check.h"
#include "autogen_init.h"
#include "autogen_prop.h"
#include "autogen_ref.h"
#include "autogen_util.h"

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #include "autogen_ver_history.h"
#endif

#include "pmdconstants.h"
#include "pmd_heap.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

/* We need __NOKIA_FILE__. #define it to something if the compiler doesn't do it. */
#ifndef __NOKIA_FILE__
 #define __NOKIA_FILE__ "<unknown file name>"
#endif /* __NOKIA_FILE__ */

/* We need __LINE__. #define it to something if the compiler doesn't do it. */
#ifndef __LINE__
 #define __LINE__ 0
#endif /* __LINE__ */

#ifndef LOCAL
 #define LOCAL static
#endif /* LOCAL */

#define AUTOGEN_SINGLE_VERSION      1
#define AUTOGEN_VERSION_INTERVAL    2
#define AUTOGEN_RESOURCE_VERSION    3

#define SCOPE_UNDEFINED             0x00000001U
#define SCOPE_ISI                   0x00000002U
#define SCOPE_RES                   0x00000004U
#define SCOPE_MSG                   0x00000008U
#define SCOPE_SUB_MSG               0x00000010U
#define SCOPE_SB                    0x00000020U
#define SCOPE_SEQ                   0x00000040U
#define SCOPE_CONST_TBL             0x00000080U
#define SCOPE_BIT_TBL               0x00000100U
#define SCOPE_PPC_TBL               0x00000200U
#define SCOPE_FTD_TBL               0x00000400U
#define SCOPE_FTD_TBL_ENTRY         0x00000800U
#define SCOPE_TRACE_GROUP_TBL       0x00002000U
#define SCOPE_TRACE_ID_TBL          0x00004000U
#define SCOPE_TRACE                 0x00008000U
#define SCOPE_MERGE                 0x00010000U
#define SCOPE_SB_LST                0x00020000U
#define SCOPE_CHOICE                0x00040000U
#define SCOPE_CASE                  0x00080000U
#define SCOPE_DER_CONST_TBL         0x00100000U
#define SCOPE_DER_BIT_TBL           0x00200000U
#define SCOPE_RANGE                 0x00400000U
#define SCOPE_PRINTF                0x00800000U

#define SCOPE_ANY                   0xFFFFFFFFU

#define SCOPE_IS_SEQ           (SCOPE_MSG | SCOPE_SUB_MSG | SCOPE_SB | SCOPE_SEQ)
#define SCOPE_IS_MSG           (SCOPE_MSG | SCOPE_SUB_MSG)

#define SCOPE_IS_TBL           (SCOPE_CONST_TBL | SCOPE_DER_CONST_TBL | \
                                SCOPE_BIT_TBL | SCOPE_DER_BIT_TBL | \
                                SCOPE_PPC_TBL | SCOPE_FTD_TBL) 

typedef struct t_generation_scope
{
    struct t_generation_scope* next;
    unsigned int scope;
    autogen_obj* parent;
    /* feature flags */
    struct t_autogen_feature* feature_flags;
} generation_scope;

typedef struct t_generation_env
{
    generation_scope* scope;
    int ftd_length_sum; /* length of FTD table entry */
} generation_env;

LOCAL generation_env* s_env = NULL;

/* accumulated length of merged fields */
LOCAL int s_merge_length = 0;

/* pointer to the current sequence */
LOCAL autogen_seq* s_seq = NULL;

/* pointer to the current subblock list */
LOCAL autogen_item* s_lst = NULL;

/* pointer to the current item */
LOCAL autogen_item* s_item = NULL;

/* pointer to the ppc resource */
LOCAL autogen_res* s_ppc_res = NULL;

/* pointer to the current resource */
LOCAL autogen_res* s_res = NULL;

/* pointer to the resource just processed */
LOCAL autogen_res* s_last_res = NULL;

/* pointer to the old server (used for save/restoring server object */
LOCAL autogen_res* s_old_res = NULL;

/* pointet to the current table */
LOCAL autogen_tbl* s_tbl = NULL;

/* pointer to the current object (constant, note, version) */
LOCAL autogen_obj* s_object = NULL;

/* pointer to the current constant */
LOCAL autogen_const* s_constant = NULL;

/* unique item id */
LOCAL unsigned int s_id = 0;

/* current trace group ID */
LOCAL unsigned int s_trcgrp_id[AUTOGEN_OBJ_TRACEGRP_MAX];

/* current trace ID */
LOCAL unsigned int s_trc_id[AUTOGEN_OBJ_TRACEGRP_MAX];

/* current trace group table */
LOCAL autogen_trcgrp* s_trcgrp = NULL;

/* current file */
LOCAL const char* s_file = NULL;

/* last file */
LOCAL const char* s_file_last = NULL;

/* last old macro usage wanning ID */
LOCAL unsigned int s_last_old_macro_usage_warning_id = 0;

/* old file (used for saving/restoring s_file) */
LOCAL const char* s_old_file = NULL;

LOCAL void          init_add_obj_relation(autogen_obj* obj, autogen_obj* refobj, autogen_ver* ver_range, autogen_feature *featureflag);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
#if (PMD_FILE_FORMAT >= 600)
LOCAL void          init_add_def(int line, unsigned int type, const char* name, unsigned long long id, unsigned int flag, 
                                 autogen_ver* ver, autogen_cmt* cmt, const autogen_prop* alias_prop, autogen_feature *feature_flag);
#else
LOCAL void          init_add_def(int line, unsigned int type, const char* name, unsigned int id, unsigned int flag, 
                                 autogen_ver* ver, autogen_cmt* cmt, const autogen_prop* alias_prop, autogen_feature *feature_flag);
#endif
#endif

LOCAL autogen_item* init_handle_filler_replacement(int line, autogen_item* value, autogen_feature *feature_flag);

LOCAL void          init_check_length(int line, int length, int sign, int allow_64, int allow_24);
LOCAL unsigned int  init_check_order(int line, unsigned int ordermask, unsigned int order, int length, int allow_24);
LOCAL void          init_check_scope(int line, unsigned int scopemask);
LOCAL void          init_check_scope_macro(int line, unsigned int scopemask, const char* macro);
LOCAL autogen_obj*  init_check_scope_target(int line, unsigned int target);
LOCAL void          init_check_64_bit_alignment_prop(int line, int length);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
LOCAL void          init_check_usage(unsigned int type, unsigned int subtypecrit, unsigned int subtype, autogen_ver* ver, autogen_obj_list* lst);
#endif /* #ifdef AUTOGEN_ENVIRONMENT_LOCAL */

LOCAL int           init_check_version(const char* version, unsigned int system, int allow_empty);

LOCAL void          init_check_version_consistency(autogen_ver* ver, autogen_res* res);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
LOCAL void          init_reset_filler_varnames(int line, autogen_obj_list* obj_list);
LOCAL void          init_set_filler_varnames(int line, autogen_obj_list* obj_list, autogen_obj_list* check_list);
LOCAL unsigned int  init_count_varname(autogen_obj_list* obj_list, const char* varname, autogen_feature *feature_flag);
LOCAL void          init_check_varname(int line, autogen_item* item, autogen_obj_list* check_list);
LOCAL void          init_check_varnames(int line, autogen_obj_list* obj_list, autogen_obj_list* check_list);
LOCAL unsigned int  init_count_parname(autogen_obj_list* obj_list, const char* parname, autogen_feature *feature_flag);
LOCAL void          init_check_parname(int line, autogen_item* item, autogen_obj_list* check_list);
LOCAL void          init_check_parnames(int line, autogen_obj_list* obj_list, autogen_obj_list* check_list);
LOCAL void          init_check_for_empty_tables(int line);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

LOCAL void          init_check_object(autogen_res*, autogen_obj* obj);
LOCAL void          init_check_object_lst(autogen_res* res, autogen_obj_list* obj_list);
LOCAL void          init_check_res(autogen_res* res);

LOCAL void          init_check_string_prop(int line, autogen_obj* value, autogen_property_id id, autogen_feature *featureflag);

LOCAL void          init_common_seq_create(int line, unsigned int type, unsigned int subtype, unsigned int id, unsigned int flag, const char* name, const char* verfrom, const char* verto, autogen_feature *feature_flag);
LOCAL void          init_common_seq_end(int line, autogen_feature *feature_flag);

#if (PMD_FILE_FORMAT >= 600)
LOCAL void          init_constant_add(int line, const char* name, unsigned long long id, unsigned int const_type, unsigned int flag, autogen_ver* ver, autogen_feature *feature_flag);
LOCAL void          init_constant_add_unknown(int line, const char* name, unsigned long long id, const char* idstr, unsigned int const_type, int is_negative, autogen_ver* ver, autogen_feature *feature_flag);
#else
LOCAL void          init_constant_add(int line, const char* name, unsigned int id, unsigned int const_type, unsigned int flag, autogen_ver* ver, autogen_feature *feature_flag);
LOCAL void          init_constant_add_unknown(int line, const char* name, unsigned int id, const char* idstr, unsigned int const_type, int is_negative, autogen_ver* ver, autogen_feature *feature_flag);
#endif

LOCAL void          init_item_add(autogen_item* item, autogen_feature *feature_flag);
LOCAL void          init_item_add_relations(autogen_item* item, autogen_ver* ver, autogen_feature *featureflag);


LOCAL autogen_item* init_item_create(int line, unsigned int size, unsigned int subtype,
                                     unsigned int flag, const char* varname, const char* parname,
                                     autogen_feature *feature_flag);

LOCAL int init_pres_init(int line, autogen_pres* pres, unsigned int presflag, unsigned int presmask,
                         double scale, double offset, const char* unit, int length, autogen_res* tblres, int check_length);
LOCAL int init_pres_const(int line, autogen_pres* pres, unsigned int presmask, const char* tblname, autogen_res* tblres);

LOCAL void          init_obj_ver_set(int line, autogen_res* res, autogen_obj* obj, const char* verfrom, const char* verto,
                                     int type, unsigned int system, int allow_text);

LOCAL void          init_clear_properties_comments(int line);

LOCAL void          init_set_entry_version(int line, autogen_obj* entry, const char* verfrom, const char* verto);
LOCAL void          init_update_item_offsets(autogen_obj_list* obj_list, autogen_ver* ver, unsigned int* offset_type, unsigned int* offset);
LOCAL void          init_update_properties_comments(autogen_obj* obj);

LOCAL void          init_post_processing();
LOCAL void          init_post_processing_seq(autogen_seq* seq);

LOCAL void          init_scope_set(unsigned int scope, autogen_obj* parent);
LOCAL void          init_scope_restore();


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* General macro init functions */
LOCAL void init_der_tbl_begin(int line, const char* name, const char* orgtblname, const char* verfrom, const char* verto, 
                              unsigned int tbltype);
LOCAL void init_der_tbl_entry(int line, const char* name, const char* verfrom, const char* verto, 
                              unsigned int tbltype, unsigned int scope);

/* set new scope and parent */
LOCAL void init_scope_set(unsigned int scope, autogen_obj* parent)
{
    generation_scope* new_scope = (generation_scope*)calloc(1, sizeof(generation_scope));

    new_scope->parent        = parent;
    new_scope->scope         = scope;
    new_scope->feature_flags = NULL;
    new_scope->next          = s_env->scope;

    s_env->scope = new_scope;
}

/* restore scope and parent */
LOCAL void init_scope_restore()
{
    generation_scope* last_scope = s_env->scope;

    if (last_scope->feature_flags)
    {
        util_error_line(s_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Missing FEATURE_FLAG_END!");
    }

    s_env->scope = last_scope->next;

    free(last_scope);
}


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: init_set_entry_version
 
    Purpose: 
        Set version of entry
 
    Functional Description:
        Non-versioned entry: Copy version from table
        verfrom empty and table verfrom not empty: Apply table verfrom to entry
        
    Arguments: 
        entry    - [in] data order of the constants (e.g. BE or LE)
        verfrom  - [in] version from which the table is valid
        verto    - [in] version from which the table is obsolete
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void init_set_entry_version(int line, autogen_obj* entry, const char* verfrom, const char* verto)
{
    /* if version is not specified, copy from table */
    if (!verfrom[0] && !verto[0])
    {
        memcpy(&entry->ver, &s_tbl->base.ver, sizeof(autogen_ver));
    }
    /* else set version from arguments */
    else
    {
        /* Start version of entry not specified and table has a start version */
        if (!verfrom[0] && s_tbl->base.ver.from[0])
        {
            /*if (s_tbl->base.ver.from[0])  table has a start version */
            {
                char ver[12];
                memset(ver,'\0',12);
                if (s_res->base.subtype == RESOURCE_ISI_DSP)
                    sprintf(ver, "%03d.%03d.%03d", s_tbl->base.ver.from[0], s_tbl->base.ver.from[1], s_tbl->base.ver.from[2]);
                else
                    sprintf(ver, "%03d.%03d", s_tbl->base.ver.from[0], s_tbl->base.ver.from[1]);
                init_obj_ver_set(line, s_res, entry, ver, verto, AUTOGEN_VERSION_INTERVAL,
                    s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);
            }
        }
        else
        {
            init_obj_ver_set(line, s_res, entry, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
                s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);
        }
        /* is the version totally included in the table version? */
        if (!autogen_obj_ver_is_included(&s_tbl->base.ver, &entry->ver))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Version interval is out of range");
        }
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_bit_tbl_begin
 
    Purpose: 
        Begins a bitmask table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be defined at this point
        Adds the empty table to the data model for the current resource

    Arguments: 
        name     - [in] name of the bitmask table
        length   - [in] size of bitmasks in the table (in bits)
        orderstr - [in] data order of the constants (e.g. BE or LE)
        verfrom  - [in] version from which the table is valid
        verto    - [in] version from which the table is obsolete
        macro    - [in] name of macro (BIT_TBL_BEGIN or DEFINE_BIT_TBL_BEGIN)
*/
/* --------------------------------------------------------------------------------------------- */
void init_bit_tbl_begin(int line, const char* name, int length, unsigned int order, const char* verfrom, const char* verto, const char* cmt)
{
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    cmt;
#endif

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check table name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check bit size */
#if (PMD_FILE_FORMAT >= 600)
    if (length > 32)
    {
        if (!prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_64_BITS))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. For table length > 32 please apply resource property 'PROPERTY_ALIGNMENT_64_BITS'");
        }
    }
    if (length <= 0 || length > 64)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is out of range. Value must be between 1 and 64");
    }
#else
    if (length <= 0 || length > 32)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is out of range. Value must be between 1 and 32");
    }
#endif

    /* check data order */
    order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, length, (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* create table object */
    s_tbl = (autogen_tbl*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_tbl), AUTOGEN_OBJ_TBL, AUTOGEN_TBL_BIT, 0, name, (s_env->scope ? s_env->scope->feature_flags : NULL));

    autogen_obj_list_init(&s_tbl->base.child_list, &s_tbl->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);

    s_tbl->length    = length;
    s_tbl->order     = order;
    s_tbl->orgtbl    = s_tbl;

    /* set definition name */
    {
        char* def_name = pmd_heap_alloc(strlen(name) + 10);

        strcpy(def_name, name);
        strcat(def_name, "_CONST");

        prop_add_string_default(PROPERTY_ISIHDR_DEFINITION_NAME, def_name);
    }

    /* update properties and comments */
    init_update_properties_comments((autogen_obj*)s_tbl);

    /* check and set version numbers */
    init_obj_ver_set(line, s_res, (autogen_obj*)s_tbl, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    if (s_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* Object belongs to Legacy part of resource*/
    {
        ((autogen_obj*)s_tbl)->flag |= AUTOGEN_OBJ_IS_LEGACY;
    }

    /* add table object to server */
    autogen_obj_list_add_obj(&s_res->tbl_list, &s_tbl->base, AUTOGEN_ENV_ALL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&s_tbl->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* set new scope and parent */
    init_scope_set(SCOPE_BIT_TBL, &s_tbl->base);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_bit_tbl_end
 
    Purpose: 
        Ends a bitmask table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be ended at this point
*/
/* --------------------------------------------------------------------------------------------- */
void init_bit_tbl_end(int line)
    {
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_BIT_TBL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* verify that the table typedef name does not 
       conflict with other definitions */
    if (!(s_tbl->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR) &&
        prop_has_valid_string((autogen_obj*)s_tbl, PROPERTY_ISIHDR_DEFINITION_NAME))
        {
        init_add_def(line, AUTOGEN_DEF_NAME, 
            prop_get_string((autogen_obj*)s_tbl, PROPERTY_ISIHDR_DEFINITION_NAME),
            0, 0, &s_tbl->base.ver, NULL, NULL, s_tbl->base.feature_flags);
        }
    /* The following should actually cover all environments */
    init_check_for_empty_tables(line);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();

    s_tbl = NULL;
    }


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_bit_tbl_entry
 
    Purpose: 
        Inserts an entry in a bitmask table
 
    Functional Description:
        Validates the input arguments
        Verifies that the entry can be defined at this point
        Adds the entry to the bitmask table in the data model for the current resource

    Arguments: 
        bits    - [in] bitmask string
        bitname - [in] symbolic name of bitmask
        verfrom - [in] version from which the entry is valid
        verto   - [in] version from which the entry is obsolete
        macro   - [in] name of macro (BIT_TBL_ENTRY)
*/
/* --------------------------------------------------------------------------------------------- */
void init_bit_tbl_entry(int line, const char* bits, const char* bitname, const char* verfrom, const char* verto, const char* cmt)
{
    autogen_bittbl_entry* entry;
    unsigned int i;
    unsigned int offset = 0;
    unsigned int n_bits = 0;
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long mask = 0;
    unsigned long long val  = 0;
    char strbits[65]        = "";
#else
    unsigned int mask = 0;
    unsigned int val  = 0;
    char strbits[33]  = "";
#endif
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    unsigned int flag = AUTOGEN_CONST_UNSIGNED_BYTE;
#else
    cmt;
#endif

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_BIT_TBL);

    /* check bitmask name */
    check_c_name(s_file, line, "bitname", bitname, CHECK_NAME_EXIT_ON_FAIL);

    /* check bit pattern */
    check_string(s_file, line, "bits", bits, CHECK_NAME_EXIT_ON_FAIL);

    /* bits is not long enough */
    if ((int)strlen(bits) > s_tbl->length)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'bits' is not valid. Pattern must be %ld characters long", s_tbl->length);

        offset = strlen(bits) - (unsigned int)s_tbl->length;
        n_bits = (unsigned int)s_tbl->length;
    }
    else if ((int)strlen(bits) < s_tbl->length)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'bits' is not valid. Pattern must be %ld characters long", s_tbl->length);

        offset = (unsigned int)s_tbl->length - strlen(bits);
        n_bits = strlen(bits);
    }
    else
    {
        offset = 0;
        n_bits = (unsigned int)s_tbl->length;
    }

    strncpy(strbits, bits, n_bits);

    /* generate mask and bit string from bit pattern */
    for (i = 0; i < (unsigned int)s_tbl->length; i++)
    {
        if (strbits[i] == '1')
        {
            mask |= (unsigned long long)1 << ((unsigned int)s_tbl->length - i - 1);
            val  |= (unsigned long long)1 << ((unsigned int)s_tbl->length - i - 1);
        }
        else if (strbits[i] == '0')
        {
            mask |= (unsigned long long)1 << ((unsigned int)s_tbl->length - i - 1);
        }
        else
        {
            strbits[i] = '-';
        }
    }

    /* create table item */
    entry = (autogen_bittbl_entry*)autogen_obj_create(s_file, line, s_tbl->base.res, &s_tbl->base, sizeof(autogen_bittbl_entry), AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_BIT, val, bitname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    entry->base.flag |= s_tbl->base.flag & (AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR);

    entry->bit_pattern = (void*)pmd_heap_strdup(strbits);
    entry->bit_mask    = mask;

    /* update comments and properties */
    init_update_properties_comments(&entry->base);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    init_set_entry_version(line, &entry->base, verfrom, verto);

    /* add object to table */
    autogen_obj_list_add_obj(&s_tbl->base.child_list, &entry->base, AUTOGEN_ENV_LOCAL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
#if (PMD_FILE_FORMAT >= 600)
    if (s_tbl->length > 32)
    {
        flag = AUTOGEN_CONST_UNSIGNED_DDWORD;
    }
    else 
#endif
    if (s_tbl->length > 16)
    {
        flag = AUTOGEN_CONST_UNSIGNED_DWORD;
    }
    else if (s_tbl->length > 8)
    {
        flag = AUTOGEN_CONST_UNSIGNED_WORD;
    }

    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&entry->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    }

    if (!(entry->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR))
    {
        init_add_def(line, AUTOGEN_DEF_CONST, bitname, val, flag, &entry->base.ver, entry->base.cmt_list, 
            prop_find_first(&entry->base, PROPERTY_ISIHDR_ALIAS_NAME), entry->base.feature_flags);
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_case
 
    Purpose: 
        Inserts a case (branch) in a choice structure
 
    Functional Description:
        Validates the input arguments
        Verifies that the case can be defined at this point
        Adds the case to the choice structure in the data model for the current resource

    Arguments: 
        tagname    - [in] symbolic name of the tag (must exist in the constant reference)
        seqname    - [in] name of the sequence or subblock describing the branch
        verfrom    - [in] version from which the case is valid
        verto      - [in] version from which the case is obsolete
        is_default - [in] is the case the default case?
        macro      - [in] name of macro (CASE, CASE_BEGIN, CASE_VER or CASE_DEFAULT)
*/
/* --------------------------------------------------------------------------------------------- */
void init_case(int line, const char* tagname, unsigned int tagid, int has_id, const char* seqname, const char* verfrom, const char* verto, int macro_type)
{
    unsigned flag = (macro_type == MACRO_CASE_DEFAULT || macro_type == MACRO_DEFAULT_BEGIN) ? AUTOGEN_CASE_DEFAULT : 0;
    autogen_item_case* case_item = NULL;
    autogen_item_choice* choice = (autogen_item_choice*)s_env->scope->parent;
    autogen_seq* str;


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_CHOICE);

    /* check sequence/subblock name */
    if (macro_type != MACRO_CASE_BEGIN && macro_type != MACRO_DEFAULT_BEGIN)
    {
        check_c_name(s_file, line, "seqname", seqname, CHECK_NAME_EXIT_ON_FAIL);
    }

    /* check tag, if not default case */
    if (macro_type != MACRO_CASE_DEFAULT && macro_type != MACRO_DEFAULT_BEGIN && macro_type != MACRO_CASE_OLD && !has_id)
    {
        /* for value references, convert the tag to an id */
        if (choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_VALUE)
        {
            tagid  = (unsigned int)atoi(tagname);
            has_id = TRUE;
        }
        else
        {
            check_c_name(s_file, line, "tagname", tagname, CHECK_NAME_EXIT_ON_FAIL);
        }
    }

    if (has_id)
    {
        flag |= AUTOGEN_CASE_HAS_ID;
    }

    /* create and initialize case item object */
    case_item = (autogen_item_case*)init_item_create(line, sizeof(autogen_item_case), AUTOGEN_ITEM_CASE, flag, "", "", NULL);
 
    autogen_obj_list_init(&case_item->base.base.child_list, &case_item->base.base, 0, 10);

    /* Set base reference handle from case, so all references defined before the case is known in the case */
    case_item->ref_handle.base_handle = reference_get_handle_from_obj(&choice->base.base);
    case_item->ref_handle.parent = &case_item->base.base;

    s_item = NULL;

    if (macro_type != MACRO_CASE_DEFAULT && macro_type != MACRO_DEFAULT_BEGIN)
    {
        case_item->base.base.name = tagname;
    }

    if (has_id)
    {
        case_item->base.base.id = tagid;
    }

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* if version is not specified, copy from choice element */
    if (!verfrom[0] && !verto[0])
    {
        /* the version is given by the choice itself */
        memcpy(&case_item->base.base.ver, &choice->base.seq->base.ver, sizeof(autogen_ver));
    }
    /* else set version from arguments */
    else
    {
        char ver_fm[12];
        memset(ver_fm,'\0',12);
        /* Start version of entry not specified */
        if ((!verfrom[0]) && (&choice->base.seq->base.ver.from[0]))
        {
            /*if (&choice->base.seq->base.ver.from[0])*/
            {
                if (s_res->base.subtype == RESOURCE_ISI_DSP)
                {
                    sprintf(ver_fm, "%03d.%03d.%03d", choice->base.seq->base.ver.from[0], choice->base.seq->base.ver.from[1], choice->base.seq->base.ver.from[2]);
                }
                else
                {
                    sprintf(ver_fm, "%03d.%03d", choice->base.seq->base.ver.from[0], choice->base.seq->base.ver.from[1]);
                }

                init_obj_ver_set(line, s_res, &case_item->base.base, ver_fm, verto, AUTOGEN_VERSION_INTERVAL,
                    choice->base.seq->base.res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);
            }
        }
        else
        {
            init_obj_ver_set(line, choice->base.seq->base.res, &case_item->base.base, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
                choice->base.seq->base.res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);
        }

        /* is the version totally included in the choice version? */
        if (!autogen_obj_ver_is_included(&choice->base.base.ver, &case_item->base.base.ver))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, "Version interval is out of range");
        }
    }

    /* does case name or ID conflict with other case names in the choice? */
    if (macro_type != MACRO_CASE_DEFAULT && macro_type != MACRO_DEFAULT_BEGIN)
    {
        autogen_it case_it = INIT_ITERATOR;

        case_it.typemask    = AUTOGEN_OBJ_ITEM;
        case_it.subtypemask = AUTOGEN_ITEM_CASE;
        case_it.obj.name    = tagname;
        case_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        case_it.ver         = &case_item->base.base.ver;

        if (autogen_obj_find_in_list(&case_it, &choice->base.base.child_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Case '%s' conflicts with other cases in the choice", tagname);
        }
    }
    /* check that only one default case is defined */
    else if (macro_type == MACRO_CASE_DEFAULT && choice->default_case)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Two default cases are defined");
    }

    /* --------------------------------------------------------------------- */
    /* check the sequence being referenced */
    /* --------------------------------------------------------------------- */

    /* find the referenced sequence */
    if (macro_type != MACRO_CASE_BEGIN && macro_type != MACRO_DEFAULT_BEGIN)
    {
        autogen_it seq_it = INIT_ITERATOR;

        seq_it.typemask    = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB;
        seq_it.subtypemask = 0;
        seq_it.subtypecrit = AUTOGEN_OBJ_SUBTYPE_EXACT;
        seq_it.obj.name    = seqname;
        seq_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        seq_it.ver         = &case_item->base.base.ver;

        str = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &choice->base.seq->base.res->seq_list);
        if (!autogen_obj_list_verify_object_span(&seq_it, &choice->base.seq->base.res->seq_list) || !str)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "The referenced sequence '%s' doesn't exist in the required version interval", seqname);
            return; /* To avoid lint warnings */
        }

        /* --------------------------------------------------------------------- */
        /* add sequence information to case item object */
        /* --------------------------------------------------------------------- */

        /* set new scope and parent */
        init_scope_set(SCOPE_CASE, &case_item->base.base);

        /* case item is a structure */
        if (!(str->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
        {        
            /* create and initialize item object */
            autogen_item_struct* str_item = (autogen_item_struct*)init_item_create(line, sizeof(autogen_item_struct), 
                AUTOGEN_ITEM_STRUCT, flag | AUTOGEN_STRUCT_SEQ, 
                choice->base.varname, choice->base.parname, NULL);

            /* copy version */
            memcpy(&str_item->base.base.ver, &case_item->base.base.ver, sizeof(autogen_ver));

            str_item->base.agg_n     = 1;
            str_item->base.agg_type  = AGG_TYPE_FIXED_SINGLE;
            str_item->base.agg_n_str = "1";

            str_item->seqname = seqname;
            str_item->seqres  = choice->base.seq->base.res;

            /* add item relations */
            init_item_add_relations((autogen_item*)str_item, &case_item->base.base.ver, NULL);

            /* add stucture reference to case item */
            init_item_add(&str_item->base, NULL);
        }
        /* case item is not a structure - copy all elements */
        else
        {
            /* iterate though all items in the sequence */
            const autogen_item* item = (const autogen_item*)autogen_obj_get_first_in_list(&str->base.child_list);

            /* Copy reference transformations */
            reference_copy_transformations(&case_item->ref_handle, &str->ref_handle);

            while (item)
            {
                /* make a copy of the item */
                autogen_item* copy_item = (autogen_item*)autogen_obj_copy_deep((autogen_obj*)item, NULL, &case_item->base.base, &case_item->base.base.ver);

                /* copy version */
                memcpy(&copy_item->base.ver, &case_item->base.base.ver, sizeof(autogen_ver));

                /* add item relations */
                init_item_add_relations(copy_item, &case_item->base.base.ver, NULL);

                /* add item object to case item object */
                init_item_add(copy_item, NULL);

                /* Update reference table from item
                    - If item is a reference, the item pointer in the reference table should point to the copy, not org
                    - Verify at the same time that there are no redefinitions of references
                    - If item is using a reference, verify that it exist
                */
                reference_copy_item(copy_item, &str->ref_handle);

                item = (autogen_item*)item->base.next;
            }

            /* "Use" sequence */
            init_add_obj_relation(&case_item->base.base, &str->base, NULL, NULL);
        }

        /* restore scope and parent */
        init_scope_restore();
    }

    /* add case object to choice object */
    if (flag & AUTOGEN_CASE_DEFAULT)
    {
        case_item->base.seq = s_seq;

        choice->default_case = case_item;
    }
    else
    {
        init_item_add(&case_item->base, NULL);
    }

    if (macro_type == MACRO_CASE_BEGIN || macro_type == MACRO_DEFAULT_BEGIN)
    {
        /* set new scope and parent */
        init_scope_set(SCOPE_CASE, &case_item->base.base);
    }
}

void init_case_end(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_CASE);
 
    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: init_choice_begin
 
    Purpose: 
        Begins a choice definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the choice can be defined at this point
        Adds the choice to the data model for the current resource

    Arguments: 
        varname          - [in] name of the variable in the ISI header file
        name (parname)   - [in] name to be printed when encoding/decoding the element
        refname          - [in] name of the tag (defined as a constant reference)
        tblname          - [in] name of constant table (for forward choice only)
        macro            - [in] name of macro (CHOICE_BEGIN, CHOICE_VALUE_BEGIN, CHOICE_FORWARD_BEGIN or DEFINE_CHOICE_REF_BEGIN)
*/
/* --------------------------------------------------------------------------------------------- */
void init_choice_begin(int line, const char* varname, const char* name, const char* refname, const char* tblname, unsigned short relpos, int macro_type)
{
    unsigned int flag = 0;
    autogen_item_choice* choice = NULL;
    char* parname = pmd_heap_strdup(name);


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_TRACE | SCOPE_CASE);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check reference name */
    if (macro_type == MACRO_CHOICE_BEGIN || macro_type == MACRO_CHOICE_VALUE_BEGIN)
    {
        check_c_name(s_file, line, "refname", refname, CHECK_NAME_EXIT_ON_FAIL);
    }

    /* set value reference flag */
    if (macro_type == MACRO_CHOICE_VALUE_BEGIN)
    {
        flag |= AUTOGEN_CHOICE_REFERENCE_VALUE;
    }

    /* check constant table name */
    if (macro_type == MACRO_CHOICE_FORWARD_BEGIN)
    {
        autogen_tbl* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        check_c_name(s_file, line, "tblname", tblname, CHECK_NAME_EXIT_ON_FAIL);

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_DERCONST | AUTOGEN_TBL_BIT | AUTOGEN_TBL_DERBIT;
        tbl_it.obj.name    = tblname;
        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.ver         = &s_env->scope->parent->ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            tbl_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &s_res->tbl_list);
        if (!tbl)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "The constant/bitmask table '%s' doesn't exist for all needed versions", tblname);
        }

        /* check that the table size is valid */
        if (tbl->length != 8 && tbl->length != 16)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "The referred table has a length, which is not valid in this context");
        }

        flag |= AUTOGEN_CHOICE_FORWARD;
        if (tbl->base.subtype & AUTOGEN_TBL_CONST_ANY)
        {
            flag |= AUTOGEN_CHOICE_REFERENCE_CONSTANT;
        }
        else
        {
            flag |= AUTOGEN_CHOICE_REFERENCE_BITMASK;
        }
    }

    /* create and initialize choice item object */
    choice = (autogen_item_choice*)init_item_create(line, sizeof(autogen_item_choice), AUTOGEN_ITEM_CHOICE, 0, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    if (flag & AUTOGEN_CHOICE_REFERENCE_VALUE)
    {
        autogen_obj_list_init(&choice->base.base.child_list, &choice->base.base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME | AUTOGEN_OBJ_LIST_SORTED_BY_ID, 10);
    }
    else
    {
        autogen_obj_list_init(&choice->base.base.child_list, &choice->base.base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 10);
    }

    /* copy version */
    memcpy(&choice->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    choice->base.agg_type  = AGG_TYPE_FIXED_SINGLE;
    choice->base.agg_n     = 1;
    choice->base.agg_n_str = "1";

    choice->base.base.flag |= flag;

    if (flag & AUTOGEN_CHOICE_FORWARD)
    {
        choice->tblname = tblname;
        choice->tblres  = s_res;
        choice->relpos  = relpos;

        /* To avoid that autogen crashes when doing strcmp() against a NULL pointer */
        choice->base.refname = "";
    }
    else
    {
        choice->base.refname = refname;
        if (macro_type == MACRO_CHOICE_VALUE_BEGIN)
        {
            reference_use_counter(&choice->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

            choice->base.base.flag |= AUTOGEN_CHOICE_REFERENCE_VALUE;
        }
        else
        {
            reference_use_tag(&choice->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
        }
    }

    /* add choice object to sequence object */
    init_item_add(&choice->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* set new scope and parent */
    init_scope_set(SCOPE_CHOICE, &choice->base.base);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_choice_end
 
    Purpose: 
        Ends a choice definition
 
    Functional Description:
        Verifies that the choice can be ended at this point

    Arguments: 
        -
*/
/* --------------------------------------------------------------------------------------------- */
void init_choice_end(int line)
{
    autogen_ref* ref = NULL;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_CHOICE);

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* Check that choice uses reference correctly */
    ref = reference_find((autogen_item*)s_env->scope->parent);
    if (ref && ref->type == referenceTypeTag)
    {
        reference_check_choice((autogen_item_value*)ref->item, (autogen_item_choice*)s_env->scope->parent);
    }

    /* restore last scope and parent */
    init_scope_restore();
}

void init_comment(int line, autogen_comment_id id, const char* comment)
{
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    comment;
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    if (!s_object)
    {
        s_object = (autogen_obj*)pmd_heap_alloc(sizeof(autogen_obj));
    }

    if (id == COMMENT_TEXT || 
        id == COMMENT_PARAGRAPH ||
        id == COMMENT_WEB_LINK ||
        id == COMMENT_BULLET)
    {
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        if (!comment || !comment[0])
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'comment' should not be an empty string");
            return;
        }
        if (strstr(comment, "/*") || strstr(comment, "*/"))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'comment' is not valid, as is contains '/*' or '*/' codes");
            return;
        }
        autogen_cmt_add(&s_object->cmt_list, autogen_cmt_create(id, 0, NULL, NULL, NULL, comment));
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
    }
    else if (id == COMMENT_NEWLINE)
    {
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        if (comment && comment[0])
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'comment' should be an empty string");
        }
        autogen_cmt_add(&s_object->cmt_list, autogen_cmt_create(id, 0, NULL, NULL, NULL, NULL));
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
    }
    else if (id == COMMENT_RAW_DATA || id == GENERAL_COMMENT)
    {
        /* don't generate anything - obsolete comment type */
    }
    else if (id == COMMENT_ISIHDR_TOP ||
        id == COMMENT_ISIHDR_TOP_16 ||
        id == COMMENT_ISIHDR_BEFORE_DEF ||
        id == COMMENT_ISIHDR_BEFORE_DEF_16 ||
        id == COMMENT_ISIHDR_AFTER_DEF ||
        id == COMMENT_ISIHDR_AFTER_DEF_16)
    {
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        if (!comment || !comment[0])
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'comment' should not be an empty string");
            return;
        }

        autogen_cmt_add(&s_object->cmt_list, autogen_cmt_create(id, 0, NULL, NULL, NULL, comment));
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
            "Invalid property defined");
    }
}

void init_comment_property(int line, autogen_comment_id id)
{
    if (!s_object)
    {
        s_object = (autogen_obj*)pmd_heap_alloc(sizeof(autogen_obj));
    }

    if (id == COMMENT_PROPERTY_HTML_ONLY ||
        id == COMMENT_PROPERTY_HTML_DISABLE ||
        id == COMMENT_PROPERTY_ISIHDR_ONLY ||
        id == COMMENT_PROPERTY_ISIHDR_DISABLE ||
        id == COMMENT_PROPERTY_ALL_OUTPUTS)
    {
        autogen_cmt_add(&s_object->cmt_list, autogen_cmt_create(id, 0, NULL, NULL, NULL, NULL));
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
            "Invalid comment property defined");
    }
}

void init_comment_link(int line, unsigned int objtype, const char* name, const char* subname, const char* ver)
{
    if (!s_object)
    {
        s_object = (autogen_obj*)pmd_heap_alloc(sizeof(autogen_obj));
    }

    /* check link object type */
    if (objtype == LINK_MESSAGE)
    {
        objtype = AUTOGEN_OBJ_MSG;
    }
    else if (objtype == LINK_SUBBLOCK)
    {
        objtype = AUTOGEN_OBJ_SB;
    }
    else if (objtype == LINK_SEQUENCE)
    {
        objtype = AUTOGEN_OBJ_SEQ;
    }
    else if (objtype == LINK_TABLE)
    {
        objtype = AUTOGEN_OBJ_TBL;
    }
    else if (objtype == LINK_NOTE)
    {
        objtype = AUTOGEN_OBJ_NOTE;
    }
    else if (objtype == LINK_CONSTANT)
    {
        objtype = AUTOGEN_OBJ_CONST;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'type' is not valid");
        return;
    }

    /* check name */
    check_string(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check version */
    if (!ver)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'ver' is not valid");
        return;
    }
    else if (ver[0] && (strlen(ver) != 7 || ver[3] != '.' || atoi(ver) > 255 || atoi(ver+4) > 255))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'ver' is not valid");
        return;
    }

    autogen_cmt_add(&s_object->cmt_list, autogen_cmt_create(COMMENT_LINK_TYPE, objtype, name, subname, ver, NULL));
}

void init_old_comment(int line, unsigned int target, unsigned int id, const char* value, int req_comment)
{
    /* check scope */
    autogen_obj* obj = init_check_scope_target(line, target);
    if (!obj) return;

#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    req_comment;
#endif

    /* is id a comment ID ? */
    if (id >= COMMENT_FIRST && id <= COMMENT_LAST)
    {
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        /* are comments obsolete */
        if (s_env->scope->scope == SCOPE_SEQ && obj->flag & AUTOGEN_SEQ_IS_NOT_STRUCT)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                "Defined sequence comments have no effect");
            return;
        }

        if (id == COMMENT_TEXT || 
            id == COMMENT_PARAGRAPH ||
            id == COMMENT_WEB_LINK ||
            id == COMMENT_BULLET)
        {
            if (!value || !value[0])
            {
                if (req_comment)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                        "Argument 'comment' should not be an empty string");
                }
                return;
            }
            if (strstr(value, "/*") || strstr(value, "*/"))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Argument 'comment' is not valid, as is contains '/*' or '*/' codes");
                return;
            }
            autogen_cmt_add(&obj->cmt_list, autogen_cmt_create(id, 0, NULL, NULL, NULL, value));
        }
        else if (id == COMMENT_NEWLINE)
        {
            if (value && value[0])
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                    "Argument 'comment' should be an empty string");
            }
            autogen_cmt_add(&obj->cmt_list, autogen_cmt_create((autogen_comment_id)id, 0, NULL, NULL, NULL, NULL));
        }
        else if (id == COMMENT_RAW_DATA)
        {
            /* don't generate anything - obsolete comment type */
        }
        else if (id == COMMENT_ISIHDR_BEFORE_DEF ||
            id == COMMENT_ISIHDR_BEFORE_DEF_16 ||
            id == COMMENT_ISIHDR_AFTER_DEF ||
            id == COMMENT_ISIHDR_AFTER_DEF_16)
        {
            if (!value || !value[0])
            {
                if (req_comment)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                        "Argument 'comment' should not be an empty string");
                }
                return;
            }

            autogen_cmt_add(&obj->cmt_list, autogen_cmt_create((autogen_comment_id)id, 0, NULL, NULL, NULL, value));
        }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
    }
    else if (id >= COMMENT_PROPERTY_FIRST && id <= COMMENT_PROPERTY_LAST)
    {
        if (value && value[0])
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'comment' should be empty for comment properties");
        }

        autogen_cmt_add(&obj->cmt_list, autogen_cmt_create((autogen_comment_id)id, 0, NULL, NULL, NULL, NULL));
    }
    else if (id < PROPERTY_TOTAL_COUNT && prop_is_simple((autogen_property_id)id))
    {
        if (value && value[0])
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'comment' should be an empty string");
        }

        prop_add_simple_to_object(obj, (autogen_property_id)id, s_file, line, TRUE);
    }
    else if (id < PROPERTY_TOTAL_COUNT && prop_is_string((autogen_property_id)id))
    {
        prop_add_string_to_object(obj, (autogen_property_id)id, value, s_file, line, TRUE);
    }
    else if (id < PROPERTY_TOTAL_COUNT && prop_is_value((autogen_property_id)id))
    {
        prop_add_value_to_object(obj, (autogen_property_id)id, atoi(value), FALSE, value, s_file, line, TRUE);
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Property id is not valid");
    }
}

void init_property(int line, autogen_property_id id)
{
    prop_add_simple(id, line, FALSE);
}

void init_property_string(int line, autogen_property_id id, const char* value)
{
    prop_add_string(id, value, line, FALSE);
}

void init_property_string_index(int line, autogen_property_id id, unsigned int index, const char* value)
{
    if (id == PROPERTY_PMD_ENVIRONMENT_VARIABLE ||
        id == PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER ||
        id == PROPERTY_PMD_TRACE_SOURCE_NAME ||
        id == PROPERTY_PMD_TRACE_SOURCE_FLAGS)
    {
        prop_add_indexed_string_to_object(&g_pmd_environment_variables, id, value, index, s_file, line, FALSE);
    }
    else
    {
        prop_add_indexed_string(id, value, index, line, FALSE);
    }
}

#if (PMD_FILE_FORMAT >= 600)
void init_property_value(int line, autogen_property_id id, unsigned long long value, int is_negative, const char* value_str)
#else
void init_property_value(int line, autogen_property_id id, unsigned int value, int is_negative, const char* value_str)
#endif
{
    prop_add_value(id, value, is_negative, value_str, line, FALSE);

    if (id == PROPERTY_ITEM_MINIMUM_VALUE || id == PROPERTY_ITEM_MAXIMUM_VALUE || id == PROPERTY_ITEM_EXCEPTIONAL_VALUE || id == PROPERTY_ITEM_DEFAULT_VALUE)
    {
        if (s_env->scope->parent)
        {
            init_constant_add_unknown(line, value_str, value, value_str, AUTOGEN_CONST_AUTOGENERATED, is_negative, &s_env->scope->parent->ver, NULL);
        }
    }
}

#if (PMD_FILE_FORMAT >= 600)
void init_property_value_index(int line, autogen_property_id id, unsigned int index, unsigned long long value, int is_negative, const char* value_str)
#else
void init_property_value_index(int line, autogen_property_id id, unsigned int index, unsigned int value, int is_negative, const char* value_str)
#endif
{
    if (id == PROPERTY_PMD_ENVIRONMENT_VARIABLE || id == PROPERTY_PMD_TRACE_SOURCE_FLAGS)
    {
        prop_add_indexed_value_to_object(&g_pmd_environment_variables, id, value, is_negative, value_str, index, s_file, line, FALSE);
    }
    else
    {
        prop_add_indexed_value(id, value, is_negative, value_str, index, line, FALSE);
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: init_old_comment_link
 
    Purpose: 
        Inserts a comment (any comment)
 
    Functional Description:
        Validates the input arguments
        Verifies that the case can be defined at this point
        Adds the case to the choice structure in the data model for the current resource

    Arguments: 
        target     - [in] comment target. Any of the AUTOGEN_TARGET_XXX constants
        objtype    - [in] type of link, e.g. LINK_MESSAGE or LINK_SUBBLOCK
        name       - [in] name of link object (optional)
        subname    - [in] subname of link object (optional)
        ver        - [in] version of the object (optional)
        allow_empty_comment - [in] TRUE/FALSE
*/
/* --------------------------------------------------------------------------------------------- */
void init_old_comment_link(int line, unsigned int target, unsigned int objtype, const char* name, const char* subname, const char* ver)
{
    /* check scope */
    autogen_obj* obj = init_check_scope_target(line, target);
    if (!obj) return;

    /* check link object type */
    if (objtype == LINK_MESSAGE)
    {
        objtype = AUTOGEN_OBJ_MSG;
    }
    else if (objtype == LINK_SUBBLOCK)
    {
        objtype = AUTOGEN_OBJ_SB;
    }
    else if (objtype == LINK_SEQUENCE)
    {
        objtype = AUTOGEN_OBJ_SEQ;
    }
    else if (objtype == LINK_TABLE)
    {
        objtype = AUTOGEN_OBJ_TBL;
    }
    else if (objtype == LINK_NOTE)
    {
        objtype = AUTOGEN_OBJ_NOTE;
    }
    else if (objtype == LINK_CONSTANT)
    {
        objtype = AUTOGEN_OBJ_CONST;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'type' is not valid");
        return;
    }

    /* check name */
    check_string(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check version */
    if (!ver)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'ver' is not valid");
        return;
    }
    else if (ver[0] && (strlen(ver) != 7 || ver[3] != '.' || atoi(ver) > 255 || atoi(ver+4) > 255))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, 
            "Argument 'ver' is not valid");
        return;
    }

    if (obj)
    {
        autogen_cmt_add(&obj->cmt_list, autogen_cmt_create(COMMENT_LINK_TYPE, objtype, name, subname, ver, NULL));
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_constant
 
    Purpose: 
        Inserts a constant
 
    Functional Description:
        Validates the input arguments
        Verifies that the constant can be defined at this point
        Adds the constant to the data model for the current resource

    Arguments: 
        name       - [in] symbolic name of the constant
        id         - [in] value of the constant
        idstr      - [in] the ID as string
        is_negative- [in] is the value a signed value
        verfrom    - [in] version from which the constant is valid
        verto      - [in] version from which the constant is obsolete
        macro      - [in] name of macro (CONSTANT or CONSTANT_VER)
*/
/* --------------------------------------------------------------------------------------------- */
#if (PMD_FILE_FORMAT >= 600)
void    init_constant(int line, const char* name, unsigned long long id, const char* idstr, int is_negative, const char* verfrom, const char* verto)
#else
void    init_constant(int line, const char* name, unsigned int id, const char* idstr, int is_negative, const char* verfrom, const char* verto)
#endif
{
    autogen_const cons;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check constant name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check and set object version */
    init_obj_ver_set(line, s_res, (autogen_obj*)&cons, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    /* is constant conflicting with other defined constants? */
    {
        autogen_it cons_it = INIT_ITERATOR;

        cons_it.typemask    = AUTOGEN_OBJ_CONST;
        cons_it.subtypemask = AUTOGEN_CONST_DEFINED;
        cons_it.obj.name    = name;
        cons_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        cons_it.ver         = &cons.base.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            cons_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            cons_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        if (autogen_obj_find_in_list(&cons_it, &s_res->const_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Redefinition of constant '%s'", name);
        }
    }

    /* add the constant */
    init_constant_add_unknown(line, name, id, idstr, AUTOGEN_CONST_DEFINED, is_negative, &cons.base.ver, (s_env->scope ? s_env->scope->feature_flags : NULL));
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_const_tbl_begin
 
    Purpose: 
        Begins a constant table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be defined at this point
        Adds the empty table to the data model for the current resource

    Arguments: 
        name     - [in] name of the constant table
        length   - [in] size of constants in the table (in bits)
        order    - [in] data order of the constants (e.g. BE or LE)
        verfrom  - [in] version from which the table is valid
        verto    - [in] version from which the table is obsolete
        macro    - [in] name of macro (CONST_TBL_BEGIN or DEFINE_CONST_TBL_BEGIN)
*/
/* --------------------------------------------------------------------------------------------- */
void init_const_tbl_begin(int line, const char* name, int length, unsigned int order, const char* verfrom, const char* verto, const char* cmt)
{
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    cmt;
#endif

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check table name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check table constant sizes in bits */
#if (PMD_FILE_FORMAT >= 600)
    if (abs(length) > 32)
    {
        if (!prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_64_BITS))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. For table length > 32 or < -32 please apply resource property 'PROPERTY_ALIGNMENT_64_BITS'");
        }
    }
    if (length == 0 || length == -1 || abs(length) > 64)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is out of range. Value must be 1 or in the interval (-)2 to (-)64");
    }
#else
    if (length == 0 || length == -1 || abs(length) > 32)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is out of range. Value must be 1 or in the interval (-)2 to (-)32");
    }
#endif

    /* check data order */
    order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, length, (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* create and initialize table object */
    s_tbl = (autogen_tbl*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_tbl), AUTOGEN_OBJ_TBL, AUTOGEN_TBL_CONST, 0, name, (s_env->scope ? s_env->scope->feature_flags : NULL));

    autogen_obj_list_init(&s_tbl->base.child_list, &s_tbl->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);

    s_tbl->length    = length;
    s_tbl->order     = order;
    s_tbl->orgtbl    = s_tbl;

    /* set definition property */
    {
        char* def_name = pmd_heap_alloc(strlen(name) + 10);

        strcpy(def_name, name);
        strcat(def_name, "_CONST");

        prop_add_string_default(PROPERTY_ISIHDR_DEFINITION_NAME, def_name);
    }

    /* update comments and properties */
    init_update_properties_comments((autogen_obj*)s_tbl);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check and set version interval */
    init_obj_ver_set(line, s_res, (autogen_obj*)s_tbl, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    if (s_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* Object belongs to Legacy part of resource*/
    {
        ((autogen_obj*)s_tbl)->flag |= AUTOGEN_OBJ_IS_LEGACY;
    }

    /* add table object to server */
    autogen_obj_list_add_obj(&s_res->tbl_list, &s_tbl->base, AUTOGEN_ENV_ALL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&s_tbl->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* set new scope and parent */
    init_scope_set(SCOPE_CONST_TBL, &s_tbl->base);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_const_tbl_end
 
    Purpose: 
        Ends a constant table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be ended at this point
*/
/* --------------------------------------------------------------------------------------------- */
void init_const_tbl_end(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_CONST_TBL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* verify that the table typedef name does not 
    conflict with other definitions */
    if (!(s_tbl->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR) && prop_has_valid_string((autogen_obj*)s_tbl, PROPERTY_ISIHDR_DEFINITION_NAME))
    {
        init_add_def(line, AUTOGEN_DEF_NAME, prop_get_string((autogen_obj*)s_tbl, PROPERTY_ISIHDR_DEFINITION_NAME), 0, 0, &s_tbl->base.ver, NULL, NULL, s_tbl->base.feature_flags);
    }
    /* The following should actually cover all environments */
    init_check_for_empty_tables(line);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();

    s_tbl = NULL;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_const_tbl_entry
 
    Purpose: 
        Inserts a constant entry in a constant table
 
    Functional Description:
        Validates the input arguments
        Verifies that the constant entry can be defined at this point
        Adds the constant entry to the constant table in data model for the current resource

    Arguments: 
        name       - [in] symbolic name of the constant
        id         - [in] value of the constant
        verfrom    - [in] version from which the constant entry is valid
        verto      - [in] version from which the constant entry is obsolete
        macro      - [in] name of macro (CONST_TBL_ENTRY or CONST_TBL_ENTRY_VER)
*/
/* --------------------------------------------------------------------------------------------- */
#if (PMD_FILE_FORMAT >= 600)
void init_const_tbl_entry(int line, const char* name, unsigned long long id, const char* verfrom, const char* verto, const char* cmt)
#else
void init_const_tbl_entry(int line, const char* name, unsigned int id, const char* verfrom, const char* verto, const char* cmt)
#endif
{
    autogen_obj* entry;
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    unsigned int flag = AUTOGEN_CONST_SIGNED;
    int add_def = FALSE;
#else
    cmt;
#endif

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_CONST_TBL);

    /* check constant name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* verify that constant value is within legal range */
    /* signed values */
    if (s_tbl->length < 0)
    {
#if (PMD_FILE_FORMAT >= 600)
        signed long long length_s = abs(s_tbl->length);
        signed long long maxid    = ((unsigned long long)1 << (length_s - 1)) - 1;
        signed long long minid    = - ((signed long long)1 << (length_s - 1));
        if ((signed long long)id < minid || (signed long long)id > maxid)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is out of range. Value must be between %lld and %lld, as defined for the table",
                minid, maxid);
        }
#else
        int maxid;
        int minid;

        maxid = (int)(1 << (-s_tbl->length - 1)) - 1;
        minid = -(int)(1 << (-s_tbl->length - 1));

        if ((int)id < minid || (int)id > maxid)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is out of range. Value must be between %ld and %ld, as defined for the table",
                minid, maxid);
        }
#endif
    }
    /* unsigned values */
    else
    {
#if (PMD_FILE_FORMAT >= 600)
        unsigned long long maxid_us;

        if (s_tbl->length < 64)
        {
            maxid_us = ((unsigned long long)1 << s_tbl->length) - 1;
        }
        else
        {
            maxid_us = 0xffffffffffffffff;
        }

        if (id > maxid_us)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is out of range. Value must be between 0x00 and 0x%llX, as defined for the table",
                maxid_us);
        }
#else
        unsigned int maxid_us;

        if (s_tbl->length < 32)
        {
            maxid_us = (1 << s_tbl->length) - 1;
        }
        else
        {
            maxid_us = 0xffffffff;
        }

        if (id > maxid_us)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is out of range. Value must be between 0x00 and 0x%2X, as defined for the table",
                maxid_us);
        }
#endif
    }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* check predefined constants */
    if (!strcmp(name, "TRUE") && id != TRUE)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "FALSE") && id != FALSE)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "YES") && id != YES)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "NO") && id != NO)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "OK") && id != OK)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "FAIL") && id != FAIL)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "COLD") && id != COLD)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "WARM") && id != WARM)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "ON") && id != ON)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "OFF") && id != OFF)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "ENABLED") && id != ENABLED)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else if (!strcmp(name, "DISABLED") && id != DISABLED)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Definition '%s' conflicts with constant in global.h", name);
    }
    else
    {
        add_def = TRUE;
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* create table item */
    entry = autogen_obj_create(s_file, line, s_tbl->base.res, &s_tbl->base, sizeof(autogen_obj), AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, id, name, (s_env->scope ? s_env->scope->feature_flags : NULL));

    entry->flag |= s_tbl->base.flag & (AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR);

#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    if (prop_has((autogen_obj *)s_tbl, PROPERTY_PMD_USE_CONST_TBL_ENTRY_COMMENT))
    {
        if (cmt && cmt[0])
        {
            entry = autogen_obj_create(s_file, line, s_tbl->base.res, &s_tbl->base, sizeof(autogen_obj), AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, id, cmt, (s_env->scope ? s_env->scope->feature_flags : NULL));
        }
        /* else leave name */
    }
#endif

    /* update comments and properties */
    init_update_properties_comments(entry);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    init_set_entry_version(line, entry, verfrom, verto);

    /* add table item to table object */
    autogen_obj_list_add_obj(&s_tbl->base.child_list, entry, AUTOGEN_ENV_ALL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* verify that constant does not conflict with other definitions 
    or constants in the resource
    */
#if (PMD_FILE_FORMAT >= 600)
    if (s_tbl->length > 32)
    {
        flag = AUTOGEN_CONST_UNSIGNED_DDWORD;
    }
    else
#endif
    if (s_tbl->length > 16)
    {
        flag = AUTOGEN_CONST_UNSIGNED_DWORD;
    }
    else if (s_tbl->length > 8)
    {
        flag = AUTOGEN_CONST_UNSIGNED_WORD;
    }
    else if (s_tbl->length > 0)
    {
        flag = AUTOGEN_CONST_UNSIGNED_BYTE;
    }

    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&entry->cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    }

    if (add_def && !(entry->flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR))
    {
        init_add_def(line, AUTOGEN_DEF_CONST, name, id, flag, &entry->ver, entry->cmt_list, prop_find_first(entry, PROPERTY_ISIHDR_ALIAS_NAME), entry->feature_flags);
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_der_tbl_begin
 
    Purpose: 
        Begins a derived constant or bitmask table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be defined at this point
        Adds the empty table to the data model for the current resource

    Arguments: 
        tbltype    - [in] AUTOGEN_TBL_DERBIT or AUTOGEN_TBL_DERCONST
        name       - [in] name of the derived table
        orgtblname - [in] name of the original constant or bitmask table
        verfrom    - [in] version from which the table is valid
        verto      - [in] version from which the table is obsolete
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void init_der_tbl_begin(int line, const char* name, const char* orgtblname, const char* verfrom, const char* verto, unsigned int tbltype)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check table name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check name of referenced table */
    check_c_name(s_file, line, "orgtblname", orgtblname, CHECK_NAME_EXIT_ON_FAIL);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* create table object */
    s_tbl = (autogen_tbl*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_tbl), AUTOGEN_OBJ_TBL, tbltype, 0, name, (s_env->scope ? s_env->scope->feature_flags : NULL));

    autogen_obj_list_init(&s_tbl->base.child_list, &s_tbl->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);

    /* update properties and comments */
    init_update_properties_comments((autogen_obj*)s_tbl);

    /* check and set version numbers */
    init_obj_ver_set(line, s_res, (autogen_obj*)s_tbl, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    /* does the related constant table exist within at least same version */
    {
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
        tbl_it.obj.name    = orgtblname;
        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.ver         = &s_tbl->base.ver;
        if ((s_env->scope ? s_env->scope->feature_flags : NULL))
        {
            tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            tbl_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        if (!autogen_obj_list_verify_object_span(&tbl_it, &s_res->tbl_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "The table '%s' doesn't exist for all required versions", orgtblname);
        }

        s_tbl->base.base_obj = autogen_obj_find_in_list(&tbl_it, &s_res->tbl_list);
        s_tbl->orgtbl        = (autogen_tbl*)s_tbl->base.base_obj;
    }

    /* is the related table of the same type as the derived table */
    {
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = (tbltype == AUTOGEN_TBL_DERCONST ? AUTOGEN_TBL_CONST : AUTOGEN_TBL_BIT);
        tbl_it.obj.name    = orgtblname;
        if ((s_env->scope ? s_env->scope->feature_flags : NULL))
        {
            tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            tbl_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        if (!autogen_obj_find_in_list(&tbl_it, &s_res->tbl_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "The derived table '%s' is not of the same type as the original '%s'", name, orgtblname);
        }
    }

    /* add table object to server */
#ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
    autogen_obj_list_add_obj(&s_res->tbl_list, &s_tbl->base, AUTOGEN_ENV_LOCAL);
#else
    autogen_obj_list_add_obj(&s_res->tbl_list, &s_tbl->base, AUTOGEN_ENV_NONE);
#endif

    /* set new scope and parent */
    init_scope_set((tbltype == AUTOGEN_TBL_DERBIT) ? SCOPE_DER_BIT_TBL : SCOPE_DER_CONST_TBL, &s_tbl->base);
}


void init_der_bit_tbl_begin(int line, const char* name, const char* orgtblname, const char* verfrom, const char* verto)
    {
    init_der_tbl_begin(line, name, orgtblname, verfrom, verto, AUTOGEN_TBL_DERBIT);
    }

void init_der_const_tbl_begin(int line, const char* name, const char* orgtblname, const char* verfrom, const char* verto)
    {
    init_der_tbl_begin(line, name, orgtblname, verfrom, verto, AUTOGEN_TBL_DERCONST);
    }



/* --------------------------------------------------------------------------------------------- */
/*  Name: init_der_bit_tbl_end
 
    Purpose: 
        Ends a derived bit table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be ended at this point

    Arguments: 
        line - [in] 
*/
/* --------------------------------------------------------------------------------------------- */
void init_der_bit_tbl_end(int line)
    {
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_DER_BIT_TBL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* The following should actually cover all environments */
    init_check_for_empty_tables(line);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();

    s_tbl = NULL;
    }


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_der_const_tbl_end
 
    Purpose: 
        Ends a derived const table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be ended at this point

    Arguments: 
        line - [in] 
*/
/* --------------------------------------------------------------------------------------------- */
void init_der_const_tbl_end(int line)
    {
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_DER_CONST_TBL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* The following should actually cover all environments */
    init_check_for_empty_tables(line);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();

    s_tbl = NULL;
    }


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_ftd_tbl_begin
 
    Purpose: 
        Begins a FTD datatable definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be defined at this point
        Adds the empty table to the data model for the current resource

    Arguments: 
        verfrom  - [in] version from which the table is valid
        verto    - [in] version from which the table is obsolete
        macro    - [in] name of macro (FTD_TBL_BEGIN or DEFINE_FTD_TBL_BEGIN)
*/
/* --------------------------------------------------------------------------------------------- */
void init_ftd_tbl_begin(int line, const char* verfrom, const char* verto, const char* cmt)
{
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    cmt;
#endif

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* create and initialize table object */
    s_tbl = (autogen_tbl*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_tbl), AUTOGEN_OBJ_TBL, AUTOGEN_TBL_FTD, 0, "FTD_TBL", (s_env->scope ? s_env->scope->feature_flags : NULL));

    autogen_obj_list_init(&s_tbl->base.child_list, &s_tbl->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 100);

    s_tbl->length   = 16;
    s_tbl->order    = AUTOGEN_ORDER_BE;
    s_tbl->orgtbl   = s_tbl;

    /* update comments and properties */
    init_update_properties_comments((autogen_obj*)s_tbl);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check and set ISI version interval */
    init_obj_ver_set(line, s_res, (autogen_obj*)s_tbl, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    /* check for conflicting tables and add table object to server */
    autogen_obj_list_add_obj(&s_res->tbl_list, &s_tbl->base, AUTOGEN_ENV_ALL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&s_tbl->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* set new scope and parent */
    init_scope_set(SCOPE_FTD_TBL, &s_tbl->base);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_ftd_tbl_end
 
    Purpose: 
        Ends a FTD data table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be ended at this point
*/
/* --------------------------------------------------------------------------------------------- */
void init_ftd_tbl_end(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_FTD_TBL);

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();

    s_tbl = NULL;
}

void init_ftd_tbl_entry_begin(int line, const char* name, unsigned int id, const char* verfrom, const char* verto, 
                              unsigned int type, const char* pname)
{
    autogen_data* data = NULL;
    char* parname = pmd_heap_strdup(pname);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_FTD_TBL);

    /* check ID value */
    if (id < 0x0010 || id > 0xFFFF)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'id' is out of range. Value must be between 0x0010 and 0xFFFF");
    }

    /* check parname */
    if (type == AUTOGEN_DATA_STRING)
    {
        check_parname(s_file, line, parname);
    }

    /* create ftd object */
    data = (autogen_data*)autogen_obj_create(s_file, line, s_tbl->base.res, &s_tbl->base, sizeof(autogen_data), AUTOGEN_OBJ_DATA, AUTOGEN_DATA_FTD, id, name, NULL);

    autogen_obj_list_init(&data->base.child_list, &data->base, 0, 5);

    data->base.flag |= type;
    data->length     = 0; /* will be set when length has been calculated */
    data->parname    = parname;

    /* set default properties */
    prop_add_value_default(PROPERTY_FTD_SUPPORTED_MODES, FTD_MODE_RD, FALSE, "FTD_MODE_RD");

    /* update comments and properties */
    init_update_properties_comments(&data->base);

    /* update flags */
    if ((prop_get_value(&data->base, PROPERTY_FTD_SUPPORTED_MODES) & FTD_MODE_OPERATOR))
    {
        s_tbl->base.res->base.flag |= AUTOGEN_OBJ_IS_PMD_PUBLIC;
        data->base.flag |= AUTOGEN_OBJ_IS_PMD_PUBLIC;
    }
    if ((prop_get_value(&data->base, PROPERTY_FTD_SUPPORTED_MODES) & FTD_MODE_INFRA))
    {
        s_tbl->base.res->base.flag |= AUTOGEN_OBJ_IS_PMD_RESTRICTED;
        data->base.flag |= AUTOGEN_OBJ_IS_PMD_RESTRICTED;
    }
    if ((prop_get_value(&data->base, PROPERTY_FTD_SUPPORTED_MODES) & FTD_MODE_RD))
    {
        data->base.flag |= AUTOGEN_OBJ_IS_PMD_RD;
    }

    /* move properties to flags */
    data->base.flag |= prop_get_value(&data->base, PROPERTY_FTD_SUPPORTED_MODES);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    init_set_entry_version(line, (autogen_obj*)data, verfrom, verto);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* check if FTD constant conflicts with other constants or definitions */
    if (!(data->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR))
    {
        init_add_def(line, AUTOGEN_DEF_CONST, name, id, AUTOGEN_CONST_UNSIGNED_WORD, &data->base.ver, data->base.cmt_list,
            prop_find_first(&data->base, PROPERTY_ISIHDR_ALIAS_NAME), NULL);
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* add FTD entry to table */
    autogen_obj_list_add_obj(&s_tbl->base.child_list, &data->base, AUTOGEN_ENV_ALL);

    /* set new scope and parent */
    if (type != AUTOGEN_DATA_STRING)
    {
        init_scope_set(SCOPE_FTD_TBL_ENTRY, &data->base);
    }
    else
    {
#if ((defined AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN) || (defined AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES))
        data->seqname = "SOS_FTD_DATA_STRING";
#else
        data->seqname = "COMM_FTD_DATA_STRING";
#endif

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        if (prop_has(&data->base, PROPERTY_FTD_STRING_MAXIMUM_LENGTH))
        {
            init_constant_add(line, 
                prop_get_string(&data->base, PROPERTY_FTD_STRING_MAXIMUM_LENGTH),
                prop_get_value(&data->base, PROPERTY_FTD_STRING_MAXIMUM_LENGTH), 
                AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &data->base.ver, NULL);
        }
        if (prop_has(&data->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH))
        {
            init_constant_add(line, 
                prop_get_string(&data->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH),
                prop_get_value(&data->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH), 
                AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &data->base.ver, NULL);
        }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
    }

    s_env->ftd_length_sum = 0;
}

void init_ftd_tbl_entry_end(int line, unsigned int type)
{
    autogen_data* data = NULL;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_FTD_TBL_ENTRY);

    data = (autogen_data*) s_env->scope->parent;

    /* is this the right end function ? */
    if (!(data->base.flag & type))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Macro can't be used in this context");
    }

    /* check length */
    if (s_env->ftd_length_sum != 8 && s_env->ftd_length_sum != 16 && s_env->ftd_length_sum != 32)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Length of FTD data '%s' is %d, which is not valid", data->base.name, s_env->ftd_length_sum);
    }
    data->length = s_env->ftd_length_sum;

    /* check input property */
    if (prop_has(&data->base, PROPERTY_FTD_IS_INPUT_DATA))
    {
        if (!(data->base.flag & AUTOGEN_DATA_VALUE))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Property PROPERTY_FTD_IS_INPUT_DATA is not supported for this FTD type");
        }
        if (data->length != 32)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Length of FTD data '%s' is %d, which is not valid. Must be 32, when property PROPERTY_FTD_IS_INPUT_DATA is set", data->base.name, s_env->ftd_length_sum);
        }
    }

    /* set common sb template name */
#ifdef AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES
    if ((data->base.flag & AUTOGEN_DATA_VALUE) && data->length == 8)
    {
        data->seqname = "SOS_FTD_DATA_BYTE";
    }
    else if ((data->base.flag & AUTOGEN_DATA_VALUE) && data->length == 16)
    {
        data->seqname = "SOS_FTD_DATA_WORD";
    }
    else if ((data->base.flag & AUTOGEN_DATA_VALUE) && data->length == 32)
    {
        data->seqname = "SOS_FTD_DATA_DWORD";
    }
    else if (data->base.flag & AUTOGEN_DATA_TABLE)
    {
        data->seqname = "SOS_FTD_DATA_BYTEARRAY";
    }
    /* TBS HANDLE SYMBIAN */
    /*
    HANDLING OF:
    SOS_FTD_DATA_STATUS
    SOS_FTD_DATA_ALL
    SOS_FTD_INPUT_PROPERTY
    SOS_FTD_OUTPUT_PROPERTY
    is TBD
    */
#else
    if ((data->base.flag & AUTOGEN_DATA_VALUE) && data->length == 8)
    {
        data->seqname = "COMM_FTD_DATA_BYTE";
    }
    else if ((data->base.flag & AUTOGEN_DATA_VALUE) && data->length == 16)
    {
        data->seqname = "COMM_FTD_DATA_WORD";
    }
    else if ((data->base.flag & AUTOGEN_DATA_VALUE) && data->length == 32)
    {
        data->seqname = "COMM_FTD_DATA_DWORD";
    }
    else if (data->base.flag & AUTOGEN_DATA_TABLE)
    {
        data->seqname = "COMM_FTD_DATA_TABLE";
    }
#endif

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_merge_begin
 
    Purpose: 
        Begins a merged element definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the merged element can be defined at this point
        Adds the element to the current sequence in the data model for the current resource

    Arguments: 
        length          - [in] length of the merged element (in bits)
        order           - [in] data order of the element (BE or LE)
        varname         - [in] name of the variable in the ISI header file
        name (parname)  - [in] name to be printed when encoding/decoding the element
*/
/* --------------------------------------------------------------------------------------------- */
void init_merge_begin(int line, int length, unsigned int order, const char* varname, const char* name)
    {
    autogen_item* merge;
    char* parname = pmd_heap_strdup(name);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_TRACE | SCOPE_CASE | SCOPE_FTD_TBL_ENTRY);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check variable size in bits */
    init_check_length(line, length, FALSE, (PMD_FILE_FORMAT >= 600), FALSE);

    /* check data order */
    order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, length, FALSE);

    /* create and initialize merge item object */
    merge = init_item_create(line, sizeof(autogen_item), AUTOGEN_ITEM_MERGE, 0, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    autogen_obj_list_init(&merge->base.child_list, &merge->base, 0, 10);

    /* copy version */
    memcpy(&merge->base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    merge->length = length;
    merge->order  = order;

    /* add item object to sequence object */
    init_item_add(merge, (s_env->scope ? s_env->scope->feature_flags : NULL));

    if (s_env->scope->scope == SCOPE_FTD_TBL_ENTRY)
    {
        s_env->ftd_length_sum += abs(length);
    }

    /* set new scope and parent */
    init_scope_set(SCOPE_MERGE, &merge->base);

    s_merge_length = 0;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_merge_end
 
    Purpose: 
        Ends a merged field definition
 
    Functional Description:
        Verifies that the merged field can be ended at this point
*/
/* --------------------------------------------------------------------------------------------- */
void init_merge_end(int line)
{
    autogen_item* merge = (autogen_item*)s_env->scope->parent;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_MERGE);
 
    /* check that merge length equals the sum of the individual element sized */
    if (s_merge_length != abs(merge->length))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Sum of size of merged elements is not valid");
    }

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* Set merge flag, if PN address field defined */
    {
        autogen_item* merge_item = (autogen_item*)autogen_obj_get_first_in_list(&merge->base.child_list);
        while (merge_item)
        {
            autogen_item_value* item_val1 = (autogen_item_value*)merge_item;
            autogen_item_value* item_val2 = (autogen_item_value*)merge_item->base.next;

            if (item_val1->pres.type == AUTOGEN_PRESENTATION_PN_CONST &&
                item_val1->pres.subtype == PN_DEVICE_6 &&
                item_val2->pres.type == AUTOGEN_PRESENTATION_PN_CONST &&
                item_val2->pres.subtype == PN_OBJECT_10)
            {
                item_val1->base.special_number_type = PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE;
                item_val2->base.special_number_type = PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_OBJECT;
            }
            else if (item_val1->pres.type == AUTOGEN_PRESENTATION_PN_CONST &&
                     item_val1->pres.subtype == PN_DEVICE &&
                     item_val2->pres.type == AUTOGEN_PRESENTATION_PN_CONST &&
                     item_val2->pres.subtype == PN_OBJECT_16)
            {
                item_val1->base.special_number_type = PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE;
                item_val2->base.special_number_type = PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_OBJECT;
            }

            merge_item = (autogen_item*)merge_item->base.next;
        }
    }

    /* restore last scope and parent */
    init_scope_restore();
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_note
 
    Purpose: 
        Defines a note
 
    Functional Description:
        Validates the input arguments
        Verifies that the note can be defined at this point
        Adds the note to the data model for the current resource

    Arguments: 
        name  - [in] name of the note
*/
/* --------------------------------------------------------------------------------------------- */
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
void init_note(int line, const char* name)
{
    autogen_obj* note;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check note name */
    check_string(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    if (!s_object)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL,0,
            "The note doesn't contain any comments");
    }

    /* create note */
    note = autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_obj), AUTOGEN_OBJ_NOTE, 0, 0, name, NULL);

    /* Set feature flag if necessary */
    if (s_env->scope->feature_flags)
    {
        note->feature_flags = s_env->scope->feature_flags;
    }

    /* update comments and properties */
    init_update_properties_comments(note);

    /* check that note name is unique within the resource and add note to data model */
    autogen_obj_list_add_obj(&s_res->note_list, note, AUTOGEN_ENV_LOCAL);
}
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

/* --------------------------------------------------------------------------------------------- */
/*  Name: init_ppc_tbl_begin
 
    Purpose: 
        Begins a PPC table definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the table can be defined at this point
        Adds an empty PPC table to the data model for the current resource

    Arguments: 
        verfrom - [in] version from which the PPC table is valid
        verto   - [in] version from which the PPC table is obsolete
        macro   - [in] name of macro (PPC_TBL_BEGIN or DEFINE_PPC_TBL_BEGIN)
*/
/* --------------------------------------------------------------------------------------------- */
void init_ppc_tbl_begin(int line, const char* verfrom, const char* verto)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check that only one resource is the PPC resource */
    if (s_ppc_res && s_ppc_res != s_res)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Redefinition of PPC table");
    }

    s_ppc_res = s_res;

    /* create and initialize table object */
    s_tbl = (autogen_tbl*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_tbl), AUTOGEN_OBJ_TBL, AUTOGEN_TBL_PPC, 0, "PPC_TBL", (s_env->scope ? s_env->scope->feature_flags : NULL));

    autogen_obj_list_init(&s_tbl->base.child_list, &s_tbl->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 100);

    s_tbl->length   = 16;
    s_tbl->order    = AUTOGEN_ORDER_BE;
    s_tbl->orgtbl   = s_tbl;

    /* update comments and properties */
    init_update_properties_comments((autogen_obj*)s_tbl);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check and set ISI version interval */
    init_obj_ver_set(line, s_res, (autogen_obj*)s_tbl, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    /* check for conflicting tables and add table object to server */
    autogen_obj_list_add_obj(&s_res->tbl_list, &s_tbl->base, AUTOGEN_ENV_LOCAL);

    /* set new scope and parent */
    init_scope_set(SCOPE_PPC_TBL, &s_tbl->base);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_ppc_tbl_end
 
    Purpose: 
        Ends a PPC table definition
 
    Functional Description:
        Verifies that the table can be ended at this point

    Arguments: 
        macro - [in] name of macro (PPC_TBL_END or DEFINE_PPC_TBL_END)
*/
/* --------------------------------------------------------------------------------------------- */
void init_ppc_tbl_end(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_PPC_TBL);

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();

    s_tbl = NULL;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_res_begin
 
    Purpose: 
        Begins a resource definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the resource can be defined at this point

    Arguments: 
        filepath    - [in] name of the filepath of the message definition file
        type        - [in] resource type, e.g. RESOURCE_ISI or RESOURCE_MM
        resid       - [in] PhoNet resource ID or media module type
        resname     - [in] name of resource (phonet name or media module name, e.g. "PN_MON")
        sername     - [in] long name of resource (e.g. "Monitor server")
        shortname   - [in] ID of the resource (e.g. MON)
        version     - [in] version of the resource
        suppcomm    - [in] does the resource support common messages?
        macro       - [in] name of macro (RES_BEGIN, DEFINE_COMMON_SERVER_BEGIN or DEFINE_SERVER_BEGIN)
*/
/* --------------------------------------------------------------------------------------------- */
void init_res_begin(const char* filepath, int line, unsigned int restype, unsigned int resid, const char* resname, 
    const char* sername, const char* shortname, const char* version, int suppcomm, const char* cmt)
{
    char macro[] = "RES_BEGIN";
    unsigned int type = RESOURCE_UNKNOWN;
    const char* filename = filepath;
    int mcu_trc_res = FALSE;
    unsigned int n;
    unsigned int flags = 0;
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    cmt;
#endif

    /* convert filepath to filename */
    if (strrchr(filepath, '\\'))
    {
        filename = strrchr(filepath, '\\') + 1;
    }
    else if (strrchr(filepath, '/'))
    {
        filename = strrchr(filepath, '/') + 1;
    }

    s_file_last = s_file;
    s_file      = filename;

    /* check if macro is allowed in the current scope */
    if (restype == RESOURCE_TRC_MCU && (s_env->scope->scope & SCOPE_RES))
    {
        mcu_trc_res = TRUE;
    }
    else
    {
        init_check_scope(line, SCOPE_ISI);
    }

    /* Reject any resources with id = PN_DUMMY_RESOURCE */
#ifdef PN_DUMMY_RESOURCE
    if (resid == PN_DUMMY_RESOURCE)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "It is not allowed to use value '%u' ('PN_DUMMY_RESOURCE') as Resource ID for resource '%s'.", 
            PN_DUMMY_RESOURCE, (resname == NULL ? "" : resname));
    }
#endif

    /* convert resource ID for PN_PREFIX */
    if (restype == RESOURCE_ISI_PREFIX)
    {
        unsigned int tmpid = (resid & 0x00FF00); /* Mask away subtype and PN_PREFIX */
        resid = ((resid >> 16) & 0xFF) | tmpid;  /* Add subtype again, but in reverse order */
    }

    /* check logical resource name (server name) */
    check_string(s_file, line, "sername", sername, CHECK_NAME_EXIT_ON_FAIL);

    if (g_autogen_env == AUTOGEN_ENV_LOCAL)
    {
        fprintf(g_log, "\nFile: %s (%s)", s_file, sername);
        fprintf(g_log, "\n==============================================================================\n");
    }

    printf("  %s", sername);     

    /* check resource name */
    check_c_name(s_file, line, "resname", resname, CHECK_NAME_EXIT_ON_FAIL);

    /* set new scope */
    if (!mcu_trc_res)
    {
        s_old_res  = NULL;
        s_old_file = NULL;
    }
    else
    {
        /* save the current resource */
        s_old_res  = s_res;
        s_old_file = s_file;
    }

    /* check that resource name is not PN_PRIVATE and PN_PREFIX */
    if (!strcmp(resname, "PN_PRIVATE") || !strcmp(resname, "PN_PREFIX"))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'resname' is not valid. Resource name '%s' is reserved", resname);
    }

    /* check short resource name */
    check_c_name(s_file, line, "shortname", shortname, CHECK_NAME_EXIT_ON_FAIL);

    /* Are we dealing with Resource Legacy? */
    if (s_last_res)
    {
        if (restype == RESOURCE_LEGACY)
        {
            if (!(strcmp(resname, s_last_res->base.name)))
            {
                if (s_last_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* already dealing with legacy? */
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Multiple RESOURCE_LEGACY defined for resource '%s'", resname);
                }
                s_res = s_last_res;
                s_res->base.flag |= AUTOGEN_RES_IS_LEGACY;
                init_scope_set(SCOPE_RES, &s_res->base);
                return;
            }
            else /* Legacy does not match resource */
            {
                if (s_last_res->base.id != AUTOGEN_NO_RESOURCE_ID)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Legacy for resource '%s' included as legacy for resource '%s' or misplaced in '%s'", resname, s_last_res->base.name, resname);
                }
                else /* assume that inclusion of legacy is placed at the top of the file */
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                        "Inclusion of legacy for resource '%s' must be placed at the bottom of the file (after RES_END)", resname);
                }
            }
        }
        
    }

    for (n = 0; n < AUTOGEN_RESOURCE_TYPES_MAX && type == RESOURCE_UNKNOWN; n++)
    {
        if (g_res_conf[n].res_type == restype)
        {
            type = restype;
        }
    }

    /* invalid resource type */
    if (type == RESOURCE_UNKNOWN && g_autogen_env == AUTOGEN_ENV_LOCAL)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'type' is not valid");
    }

    /* special settings for STI traces */
    if (type == RESOURCE_TRC_STI)
    {
        g_sti_trace_id   = resid;
        g_sti_trace_name = resname;

        prop_add_simple(PROPERTY_ALIGNMENT_CHECK_DISABLE, 0, 0);
        prop_add_simple(PROPERTY_SUBMSG_NAMES_ARE_UNIQUE, 0, 0);
    }

    /* To be removed, when macro files below have correct definitions */
    if (!prop_has(NULL, PROPERTY_PMD_PHONET_DEVICE_ID))
    {
        if (restype == RESOURCE_ISI || restype == RESOURCE_ISI_DSP)
        {
            if (resid == PN_DSP_SELF_TEST || resid == PN_DSP_AUDIO || resid == PN_WCDMA_DSP_TEST || resid == PN_GSM_DSP_TEST)
            {
                prop_add_value(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_DSP_MAIN, FALSE, "PN_DEV_DSP_MAIN", 0, FALSE);
            }
        }
    }

    /* are we processing a HW Master trace file ... */
    if (restype == RESOURCE_TRC_MASTER)
    {
        if (prop_has(NULL, PROPERTY_PMD_RESOURCE_TRC_IS_HW_MASTER))
        {
            flags |= AUTOGEN_RES_TRC_IS_HW_MASTER;
        }
    }

    if (type & (RESOURCE_TRC_ANY & ~(RESOURCE_TRC_INVARIANT)))
    {
        prop_add_simple(PROPERTY_ISI_VERSIONING_NOT_SUPPORTED, 0, 0);
    }

    /* check that common message flag is true only for ISI resources */
    if (suppcomm && 
        type != RESOURCE_ISI && 
        type != RESOURCE_ISI_PREFIX && 
        type != RESOURCE_ISI_PRIVATE && 
        type != RESOURCE_ISI_DSP && 
        !strcmp(macro, "RES_BEGIN"))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'suppcomm' is not valid in this context. Value must be 'FALSE'");

        suppcomm = FALSE;
    }

    /* check for duplicate resource definitions */
    {
        autogen_res* res   = NULL;
        autogen_it res_it  = INIT_ITERATOR;

        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = type;
        res_it.obj.name    = (resid == AUTOGEN_NO_RESOURCE_ID ? sername : resname);
        res_it.obj.id      = resid;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;

        res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        while (res && !(flags & AUTOGEN_RES_IS_DUPLICATE))
        {
            if (!strcmp(filename, res->filename))
            {
                flags |= AUTOGEN_RES_IS_DUPLICATE;
            }
            else
            {
                res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
            }
        }
    }

    /* check for duplicate resource definitions */
    if (type == RESOURCE_ISI_COMMON_MESSAGES ||
        type == RESOURCE_ISI_COMMON_MESSAGES_EXT ||
        type == RESOURCE_ISI_MEDIA_CONTROL ||
        type == RESOURCE_SYMBOLS ||
        type == RESOURCE_TRC_DSP5_CDSP ||
        type == RESOURCE_TRC_DSP5_OMAP ||
        type == RESOURCE_TRC_MASTER)
    {
        autogen_it res_it = INIT_ITERATOR;

        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = type;
        res_it.flagnone |= AUTOGEN_RES_TRC_IS_HW_MASTER; /* Several MASTER HW TRACE resources can be included */

        if (autogen_obj_find_in_list(&res_it, g_res_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Redefinition of resource type");
        }
    }

    /* if resource is a media module, check that the media control has been defined */
    if (type == RESOURCE_MEDIA_MODULE)
    {
        if (!util_get_unique_res(RESOURCE_ISI_MEDIA_CONTROL))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Media controller resource is not defined");
        }
    }

    /* if private interface */
    if (type == RESOURCE_ISI_PRIVATE)
    {
        autogen_it res_it = INIT_ITERATOR;

        /* check that private ID is unique */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_ISI_PRIVATE;
        res_it.obj.name    = resname;

        if (autogen_obj_find_in_list(&res_it, g_res_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Redefinition of private name '%s'", resname);
        }

        /* check that private name is unique */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_ISI_PRIVATE;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = resid;
        res_it.obj.name    = AUTOGEN_OBJ_NAME_ANY;

        if (autogen_obj_find_in_list(&res_it, g_res_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Redefinition of private ID 0x%4.4X", resid);
        }

        /* check that name contains PN_PRIVATE_ */
        if (strncmp(resname, "PN_PRIVATE_", 11))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is not valid. Name must be on the format 'PN_PRIVATE_XXX'");
        }

        /* check that resource ID is in the range 0x0000 to 0xFFFF */
        if (resid > 0xFFFF)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is out of range. Value must be <= 0xFFFF");
        }
    }

    /* if prefix interface */
    if (type == RESOURCE_ISI_PREFIX)
    {
        autogen_it res_it = INIT_ITERATOR;

        /* check that private ID is unique */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_ISI_PREFIX;
        res_it.obj.name    = resname;

        if (autogen_obj_find_in_list(&res_it, g_res_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Redefinition of resource name '%s'", resname);
        }

        /* check that resource name is unique */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_ISI_PREFIX;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = resid;
        res_it.obj.name    = AUTOGEN_OBJ_NAME_ANY;

        if (autogen_obj_find_in_list(&res_it, g_res_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Redefinition of resource ID 0x%4.4X", resid);
        }

        /* check that resource ID is in the range 0x0000 to 0xFFFF */
        if (resid > 0xFFFF)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is out of range. Value must be <= 0xFFFF");
        }
    }

    /* add definition name */
    {
        char* def_name = pmd_heap_alloc(strlen(resname) + 10);

        strcpy(def_name, resname);
        strcat(def_name, "_TYPE");

        prop_add_string_default(PROPERTY_ISIHDR_DEFINITION_NAME, def_name);
    }

    /* Set additional resource flags */
    if (suppcomm)
    {
        flags |= AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES;
    }

    /* create resource object */
    s_res = (autogen_res*)autogen_obj_create(s_file, line, NULL, NULL, sizeof(autogen_res), AUTOGEN_OBJ_RES, type, resid, 
        resid == AUTOGEN_NO_RESOURCE_ID ? sername : resname, NULL);

    s_res->index = g_res_list->n_obj;
    s_res->base.flag |= flags;

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    autogen_obj_list_init(&s_res->def_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 100);
    autogen_obj_list_init(&s_res->note_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 10);
    autogen_obj_list_init(&s_res->old_macro_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 20);
#endif
    autogen_obj_list_init(&s_res->const_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 30);
    autogen_obj_list_init(&s_res->seq_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 30);
    autogen_obj_list_init(&s_res->tbl_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 30);

    if (prop_has(NULL, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        autogen_obj_list_init(&s_res->msg_dev_dep_req_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);
        autogen_obj_list_init(&s_res->msg_dev_dep_resp_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);
    }
    else
    {
        autogen_obj_list_init(&s_res->msg_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);
    }

    autogen_obj_list_init(&s_res->ver_list, &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_VERSION | AUTOGEN_OBJ_LIST_SORTED_BY_VERSION_REVERSED, 10);
    autogen_obj_list_init(&s_res->shared_list, &s_res->base, 0, 5);

    /* set short names (upper case and lower case */
    {
        unsigned int i;
        char* shortname_u = pmd_heap_strdup(shortname);
        char* shortname_l = pmd_heap_strdup(shortname);

        for (i = 0; i < strlen(shortname_u); i++)
        {
            shortname_u[i] = (char) toupper(shortname_u[i]);
            shortname_l[i] = (char) tolower(shortname_l[i]);
        }

        s_res->resnameshort_u = shortname_u;
        s_res->resnameshort_l = shortname_l;
    }

    /* set isihdr filenames */
    {
        char* isihdr_filename    = (char*)pmd_heap_alloc(strlen(s_res->resnameshort_l) + 50);
        char* isihdr_filename_16 = (char*)pmd_heap_alloc(strlen(s_res->resnameshort_l) + 50);

        strcpy(isihdr_filename,    s_res->resnameshort_l);
        strcpy(isihdr_filename_16, s_res->resnameshort_l);

        if (s_res->base.subtype == RESOURCE_SHARED)
        {
            strcat(isihdr_filename,    "_shared");
            strcat(isihdr_filename_16, "_shared");
        }

        if (s_res->base.subtype & RESOURCE_ISI_ANY)
        {
            strcat(isihdr_filename,    "_isi");
            strcat(isihdr_filename_16, "_isi");
        }

        strcat(isihdr_filename,    ".h");
        strcat(isihdr_filename_16, "_16.h");

        prop_add_string_default(PROPERTY_ISIHDR_FILENAME,    isihdr_filename);
        prop_add_string_default(PROPERTY_ISIHDR_FILENAME_16, isihdr_filename_16);
    }

    /* set HTML filename */
    {
        char buffer[256];
        char shared[10] = "";
        char isiext[10] = "";

        if (s_res->base.subtype & RESOURCE_ISI_ANY)
        {
            strcpy(isiext, "_isi");
        }

        if (s_res->base.subtype == RESOURCE_SHARED)
        {
            strcpy(shared, "_shared");
        }

        if (s_res->base.subtype == RESOURCE_TRC_MCU)
        {
            sprintf(buffer, "%s_trc.html", s_res->resnameshort_l);
        }
        else
        {
            sprintf(buffer, "i_%s%s%s_m.html", s_res->resnameshort_l, shared, isiext);
        }

        prop_add_string_default(PROPERTY_HTML_FILENAME, pmd_heap_strdup(buffer));
    }

    /* set HTML title */
    prop_add_string_default(PROPERTY_HTML_TITLE, sername);

    s_res->logical_name = sername;
    s_res->filename     = filename;

    /* update properties and comments */
    init_update_properties_comments((autogen_obj*)s_res);

    if (type == RESOURCE_ISI_COMMON_MESSAGES)
    {
        if (!prop_has((autogen_obj*)s_res, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
        {
            prop_add_simple_to_object((autogen_obj*)s_res, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE, s_file, line, FALSE);
        }
    }

    /* Checks for resource extensions */
    if (type & RESOURCE_EXTENSION_ANY)
    {
        autogen_it res_it = INIT_ITERATOR;
        autogen_res* res;
        autogen_res* ext_res;

        unsigned int res_subtype = RESOURCE_ISI;
        if (type == RESOURCE_MEDIA_MODULE_EXTENSION)
        {
            res_subtype = RESOURCE_MEDIA_MODULE;
        }
        else if (type == RESOURCE_PROTOCOL_EXTENSION)
        {
            res_subtype = RESOURCE_PROTOCOL;
        }

        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = res_subtype;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = resid;

        /* if ISI extension, verify that original resource is included */
        res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        if (res)
        {
            res->base.flag |= AUTOGEN_RES_HAS_EXTENSIONS;

            /* checks agains base resource */

            /* check for conflicting resource name */
            if (!strcmp(sername, res->logical_name))
            {
                char* new_sername;

                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Redefinition of resource name '%s'", sername);

                s_res->logical_name = new_sername = (char*)pmd_heap_alloc(strlen(sername) + 30);
                sprintf(new_sername, "%s Extended (%d)", sername, s_res->index);
            }

            /* check for conflicting resource short name */
            if (!strcmp(s_res->resnameshort_u, res->resnameshort_u))
            {
                char* new_resnameshort_l;
                char* new_resnameshort_u;

                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Redefinition of resource short name '%s'", s_res->resnameshort_u);

                s_res->resnameshort_l = new_resnameshort_l = (char*)pmd_heap_alloc(strlen(s_res->resnameshort_l) + 20);
                sprintf(new_resnameshort_l, "%s_ext_%d", res->resnameshort_l, s_res->index);

                s_res->resnameshort_u = new_resnameshort_u = (char*)pmd_heap_alloc(strlen(s_res->resnameshort_u) + 20);
                sprintf(new_resnameshort_u, "%s_EXT_%d", res->resnameshort_u, s_res->index);
            }
        }

        /* find other resource extensions */
        res_it.subtypemask = type;

        ext_res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        while (ext_res)
        {
            /* checks agains current resource */
            if (ext_res != s_res)
            {
                /* check for conflicting resource name */
                if (!strcmp(s_res->logical_name, ext_res->logical_name))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Redefinition of resource extension name '%s'", s_res->logical_name);
                }

                /* check for conflicting resource short name */
                if (!strcmp(s_res->resnameshort_u, ext_res->resnameshort_u))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Redefinition of resource extension short name '%s'", s_res->resnameshort_u);
                }
            }

            ext_res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
        }
    }
    else if (type == RESOURCE_ISI || type == RESOURCE_MEDIA_MODULE || type == RESOURCE_PROTOCOL)
    {
        /* if resource extension, set flag on resource */
        if (util_get_ext_res(type, resid))
        {
            s_res->base.flag |= AUTOGEN_RES_HAS_EXTENSIONS;
        }
    }

    /* set resource configuration */
    {
        int n;

        for (n = 0; n < AUTOGEN_RESOURCE_TYPES_MAX && !s_res->conf; n++)
        {
            if (g_res_conf[n].res_type == s_res->base.subtype)
            {
                s_res->conf = &g_res_conf[n];
            }
        }
    }

    /* Set default device on ISI / Phonet resources */
    if (!prop_has_value(&s_res->base, PROPERTY_PMD_PHONET_DEVICE_ID))
    {
        if ((s_res->base.subtype & RESOURCE_ISI_ANY) || s_res->base.subtype == RESOURCE_PHONET || s_res->base.subtype == RESOURCE_PHONET_EXT)
        {
            prop_add_value_to_object(&s_res->base, PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_HOST, FALSE, "PN_DEV_HOST", NULL, 0, FALSE);
        }
    }

    /* Set device ID on resource */
    if (prop_has_value(&s_res->base, PROPERTY_PMD_PHONET_DEVICE_ID))
    {
        s_res->device_id = (unsigned short)prop_get_value(&s_res->base, PROPERTY_PMD_PHONET_DEVICE_ID);
    }
    else
    {
        s_res->device_id = s_res->conf->device_id;
    }

    /* set trace configuration */
    {
        int n;

        s_res->trc_conf    = NULL;
        s_res->trcgrp_list = NULL;

        for (n = 0; n < AUTOGEN_OBJ_TRACEGRP_MAX && !s_res->trc_conf; n++)
        {
            if (g_trcgrp_conf[n].trc_res_ids & s_res->base.subtype)
            {
                unsigned int entity_index = 0;
                if (g_trcgrp_conf[n].max_entities > 1)
                {
                    entity_index = g_trcgrp_conf[n].n_entities++;
                }
                else
                {
                    g_trcgrp_conf[n].n_entities = 1;
                }

                s_res->trc_conf = &g_trcgrp_conf[n];

                /* allocate trace group list objects */
                if (!s_res->trc_conf->list)
                {
                    unsigned int i;

                    s_res->trc_conf->list = (autogen_obj_list**)pmd_heap_alloc(s_res->trc_conf->max_entities * sizeof(autogen_obj_list*));
                    s_res->trc_conf->map  = (unsigned int*)pmd_heap_alloc(s_res->trc_conf->max_entities * sizeof(unsigned int));

                    for (i = 0; i < s_res->trc_conf->max_entities; i++)
                    {
                        s_res->trc_conf->list[i] = (autogen_obj_list*)pmd_heap_alloc(sizeof(autogen_obj_list));

                        /* note thgat parent here is wrong. Is fixed in the else statement below */
                        autogen_obj_list_init(s_res->trc_conf->list[i], &s_res->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 100);
                    }
                }
                /* else update parent for correct list to this resource */
                else if (s_res->trc_conf->max_entities > 1)
                {
                    s_res->trc_conf->list[entity_index]->parent = &s_res->base;
                }

                /* set trace group list pointer */
                s_res->trcgrp_list = s_res->trc_conf->list[entity_index];

                /* update map index->entity ID */
                if (s_res->trc_conf->max_entities > 1)
                {
                    g_trcgrp_conf[n].map[entity_index] = resid;
                }

                /* update PMD restriction flag on resource */
                s_res->base.flag |= s_res->trc_conf->pmd_class;
            }
        }
    }

    /* set identifier. If not specified with property, use configiuration identifier */
    s_res->identifier = prop_get_string_default(&s_res->base, PROPERTY_PMD_TRACE_IDENTIFIER, 
        pmd_constant_lookup_message_type_identifier(s_res->conf->msg_type));

    /* set message rules */
    s_res->msg_id_size   = s_res->conf->msg_id_size;
    s_res->msg_id_offset = s_res->conf->msg_id_offset;

    s_res->submsg_id_size   = s_res->conf->submsg_id_size;
    s_res->submsg_id_offset = s_res->conf->submsg_id_offset;

    s_res->msg_length_size   = s_res->conf->msg_length_size;
    s_res->msg_length_offset = s_res->conf->msg_length_offset;

    /* check and set version number */
    init_obj_ver_set(line, s_res, (autogen_obj*)s_res, version, NULL, AUTOGEN_RESOURCE_VERSION,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, TRUE);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&s_res->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    } 
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* set scope and parent */
    if (!mcu_trc_res)
    {
        init_scope_set(SCOPE_RES, &s_res->base);
    }

    /* Include standard trace definitions for XTI v3 */
    if (s_res->base.subtype == RESOURCE_TRC_MASTER)
    {
        /* ... except if it is HW Master traces */
        if (!(s_res->base.flag & AUTOGEN_RES_TRC_IS_HW_MASTER))
        {
            #include "master_trace_m.h"
        }
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_res_end
 
    Purpose: 
        Ends a resource definition
 
    Functional Description:
        Verifies that the resource can be ended at this point
        Performs extensive version check on all objects in the resource
*/
/* --------------------------------------------------------------------------------------------- */
void init_res_end(int line)
{
    autogen_it ver_it = INIT_ITERATOR;
    autogen_obj* obj;
    autogen_obj* last_ver = NULL;
    autogen_obj* first_ver = NULL;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

#ifdef AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES
    /* check that the SOS FTD template subblocks are defined in sos_ftd_isi_m.h */
    if ((s_res->base.subtype == RESOURCE_ISI) && (s_res->base.id == PN_RES_TYPE_SOS_FIELD_TEST))
    {
        unsigned int i;
        /* NB! change array dimension as more templates are included ... */
        char sb_name[5][24] = 
        {
            /* TBS HANDLE SYMBIAN */
            /* What is this actually? */
            /*
            "SOS_FTD_DATA_STATUS",
            */
            "SOS_FTD_DATA_BYTE",
            "SOS_FTD_DATA_WORD",
            /*
            "SOS_FTD_DATA_ALL",
            */
            "SOS_FTD_DATA_DWORD",
            "SOS_FTD_DATA_STRING",
            "SOS_FTD_DATA_BYTEARRAY",
        };

        for (i = 0; i < 5; i++)
        {
            autogen_it sb_it = INIT_ITERATOR;
/**/
            sb_it.typemask    = AUTOGEN_OBJ_SB_TEMPLATE;
            sb_it.subtypemask = AUTOGEN_SB_TEMPLATE_SOS;
/**/
            sb_it.obj.name    = sb_name[i];

            if (!autogen_obj_find_in_list(&sb_it, &s_res->seq_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Required subblock template '%s' is not defined in the resource", sb_name[i]);
            }
        }
    }
#else
    /* check that the FTD template subblocks are defined in common messages */
    if (s_res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES || s_res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT)
    {
        unsigned int i;
        char sb_name[5][21] = 
        {
            "COMM_FTD_DATA_BYTE",
            "COMM_FTD_DATA_WORD",
            "COMM_FTD_DATA_DWORD",
            "COMM_FTD_DATA_TABLE",
            "COMM_FTD_DATA_STRING"
        };

        for (i = 0; i < 5; i++)
        {
            autogen_it sb_it = INIT_ITERATOR;

            sb_it.typemask = AUTOGEN_OBJ_SB_TEMPLATE;
            sb_it.obj.name = sb_name[i];

            if (!autogen_obj_find_in_list(&sb_it, &s_res->seq_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Required subblock template '%s' is not defined in the resource", sb_name[i]);
            }
        }
    }
#endif

    /* check for redefinition of the resource */
    if (s_res->base.subtype != RESOURCE_ISI_EXTENSION &&
        s_res->base.subtype != RESOURCE_PROTOCOL_EXTENSION &&
        s_res->base.subtype != RESOURCE_TRC_MCU &&
        s_res->base.subtype != RESOURCE_TRC_SYMBIAN &&
        !(s_res->base.flag & AUTOGEN_RES_IS_LEGACY))
    {
        autogen_it res_it = INIT_ITERATOR;

        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = s_res->base.subtype;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = s_res->base.id;
        res_it.obj.name    = s_res->base.name;

        if (autogen_obj_find_in_list(&res_it, g_res_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Redefinition of resource '%s'", s_res->base.name);

            /* empty properties and comments */
            init_clear_properties_comments(line);

            /* end current scope */
            init_scope_restore();

            s_file_last = s_file;
            s_file      = NULL;

            s_res = NULL;

            return;
        }
    }

    if (!(s_res->base.flag & AUTOGEN_RES_IS_LEGACY))
    {
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        /* verify that the resource typedef name does not conflict with other definitions */
        if (s_res->base.subtype == RESOURCE_ISI && !(s_res->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR) && 
            prop_has_valid_string((autogen_obj*)s_res, PROPERTY_ISIHDR_DEFINITION_NAME))
        {
            init_add_def(line, AUTOGEN_DEF_NAME, 
                prop_get_string((autogen_obj*)s_res, PROPERTY_ISIHDR_DEFINITION_NAME), 
                0, 0, &s_res->base.ver, NULL, NULL, NULL);
        }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

        /* add server to the list of servers */
        autogen_obj_list_add_obj(g_res_list, &s_res->base, AUTOGEN_ENV_NONE);

        /* check the resource */
        init_check_res(s_res);

	    /* check reference use */
        reference_check_unresolved();
        reference_check_unused();

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        version_history_generate(s_res);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    }/* Not for Legacy */

    ver_it.typemask  = AUTOGEN_OBJ_VERSION;
    ver_it.flagnone  = AUTOGEN_OBJ_IS_LEGACY;
    ver_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_VERSION;

    obj       = autogen_obj_find_in_list(&ver_it, &s_res->ver_list);
    first_ver = obj;

#ifdef AUTOGEN_ENVIRONMENT_LOCAL

    /* now analyze the interface for all needed versions */
    {
        int found = FALSE;
        unsigned int n = 0;

        /* Check if property PROPERTY_ISI_VERSION_AUTO_GENERATE is used correctly */
        const char* verstring = prop_get_string_default(&s_res->base, PROPERTY_ISI_VERSION_AUTO_GENERATE, "000.000");
        if (!init_check_version(verstring, AUTOGEN_VERSION_ISI, FALSE))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Property PROPERTY_ISI_VERSION_AUTO_GENERATE is not valid. Must be on the format 'ZZZ.YYY', ZZZ and YYY < 256");
        }

        /* if no version objects, check the interface anyway... */
        if (!obj && s_res->base.subtype != RESOURCE_SYMBOLS)
        {
            autogen_ver ver = INIT_VERSION_ALL;
            init_check_version_consistency(&ver, s_res);
        }

        /* else check all versions of the interface */
        while (obj)
        {
            /* print version info on screen and in log file */
            if (!found)
            {
                found = TRUE;
            }
            else
            {
                printf(", ");
            }

            if (n++ % 8 == 0)
            {
                printf("\n    ");
            }

            if (!prop_has(util_get_base_parent(obj), PROPERTY_ISI_VERSIONING_NOT_SUPPORTED))
            {
                printf("%03hu.%03hu", obj->ver.from[0], obj->ver.from[1]);

                if (obj->ver.system == AUTOGEN_VERSION_DSP)
                {
                    printf(".%03hu", obj->ver.from[2]);
                }
            }
            else
            {
                printf("%s", obj->ver.ver_str);
            }
            if ((obj->ver.system == AUTOGEN_VERSION_ISI) && (!prop_has(util_get_base_parent(obj), PROPERTY_ISI_VERSIONING_NOT_SUPPORTED)))
            {
                if (s_res->base.subtype & RESOURCE_ISI_ANY)
                {
                    fprintf(g_log, "ISI version");
                }
                else
                {
                    fprintf(g_log, "version");
                }
                fprintf(g_log, " %03hu.%03hu:\n", obj->ver.from[0], obj->ver.from[1]);
            }
            else
            {
                if (!prop_has(util_get_base_parent(obj), PROPERTY_ISI_VERSIONING_NOT_SUPPORTED))
                {
                    fprintf(g_log, "Server version %03hu.%03hu.%03hu:\n", obj->ver.from[0], obj->ver.from[1], obj->ver.from[2]);
                }
                else
                {
                    fprintf(g_log, "Server version %s:\n", obj->ver.ver_str);
                }
            }

            init_check_version_consistency(&obj->ver, s_res);

            if (obj != first_ver)
            {
                version_history_report_warnings(obj);
            }

            last_ver = obj;

            /* next interface version */
            obj = autogen_obj_find_next_in_list(&ver_it);
        }

        printf("\n");
    }
#else
    {
        if (!obj)
        {
            printf("\n");
        }
        else if (s_res->base.ver.system == AUTOGEN_VERSION_ISI)
        {
            printf(" (%03hu.%03hu)\n", s_res->base.ver.from[0], s_res->base.ver.from[1]);
        }
        else if (s_res->base.ver.system == AUTOGEN_VERSION_DSP)
        {
            printf(" (%03hu.%03hu.%03hu)\n", s_res->base.ver.from[0], s_res->base.ver.from[1], s_res->base.ver.from[2]);
        }
        else
        {
            printf("\n");
        }
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* check that the resource version is the newest version */
    if (g_autogen_env == AUTOGEN_ENV_LOCAL && last_ver)
    {
        if (autogen_ver_comp(s_res->base.ver.from, last_ver->ver.from) & AUTOGEN_VER_NEWER)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "The default version of the resource is not the newest version");
        }
    }

    /* add resource name to symbol PN_RESOURCE */
    if (s_res->base.subtype == RESOURCE_ISI)
    {
        autogen_res* symbols = util_get_unique_res(RESOURCE_SYMBOLS);
        autogen_tbl* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST;
        tbl_it.obj.name    = "SYMBOLS_PN_RESOURCE";

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &symbols->tbl_list);
        if (tbl)
        {
            autogen_it entry_it = INIT_ITERATOR;
            autogen_obj* entry;

            entry_it.idcrit = AUTOGEN_OBJ_ID_EXACT;
            entry_it.obj.id = s_res->base.id;

            /* if not found in the table, add the constant */
            entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
            if (entry)
            {
                /* if name has changed, rename... */
                if (strcmp(entry->name, s_res->base.name))
                {
                    entry->name = s_res->base.name;
                }
            }
            else
            {
                entry = autogen_obj_create(s_file, line, tbl->base.res, &tbl->base, sizeof(autogen_obj), AUTOGEN_OBJ_TBLENTRY, 0, s_res->base.id, s_res->base.name, NULL);

                autogen_obj_list_add_obj(&tbl->base.child_list, entry, AUTOGEN_ENV_NONE);
            }
        }
    }

    /* if ADSP trc resources, copy process ID table to symbol table */
    if (s_res->base.subtype == RESOURCE_TRC_DSP5_ADSP)
    {
        autogen_res* symbols = util_get_unique_res(RESOURCE_SYMBOLS);
        autogen_tbl* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST;
        tbl_it.obj.name    = "SYMBOLS_ADSP_PROCESS_ID";

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &symbols->tbl_list);

        /* only update table, if table is empty */
        if (tbl && tbl->base.child_list.n_obj == 0)
        {
            autogen_tbl* src_tbl;
            autogen_obj* entry;

            tbl_it.obj.name = "DSP5_OSE_PIDS";

            src_tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &s_res->tbl_list);
            if (src_tbl)
            {
                entry = autogen_obj_get_first_in_list(&src_tbl->base.child_list);
                while (entry)
                {
                    autogen_obj* new_entry = autogen_obj_create(NULL, 0, tbl->base.res, &tbl->base, sizeof(autogen_obj), AUTOGEN_OBJ_TBLENTRY, 0, 
                        entry->id, entry->name, NULL);

                    autogen_obj_list_add_obj(&tbl->base.child_list, new_entry, AUTOGEN_ENV_NONE);

                    entry = entry->next;
                }
            }        
        }        
    }

    /* if ADSP/CDSP trc resources, copy signal ID's to symbol table */
    if (s_res->base.subtype == RESOURCE_TRC_DSP5_ADSP || s_res->base.subtype == RESOURCE_TRC_DSP5_CDSP)
    {
        autogen_res* symbols = util_get_unique_res(RESOURCE_SYMBOLS);
        autogen_tbl* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST;

        if (s_res->base.subtype == RESOURCE_TRC_DSP5_CDSP)
        {
            tbl_it.obj.name = "SYMBOLS_CDSP_SIGNAL_ID";
        }
        else
        {
            tbl_it.obj.name = "SYMBOLS_ADSP_SIGNAL_ID";
        }

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &symbols->tbl_list);
        if (tbl)
        {
            autogen_obj* sb;
            autogen_it sb_it = INIT_ITERATOR;

            sb_it.typemask = AUTOGEN_OBJ_SB;

            sb = autogen_obj_find_in_list(&sb_it, &s_res->seq_list);
            while (sb)
            {
                if (strstr(sb->name, "DSP_SB_SIGNAL_RX_"))
                {
                    autogen_obj* new_entry = autogen_obj_create(NULL, 0, tbl->base.res, &tbl->base, sizeof(autogen_obj), 
                        AUTOGEN_OBJ_TBLENTRY, 0, sb->id + 0x3000,
                        sb->name+strlen("DSP_SB_SIGNAL_RX_"), NULL);

                    autogen_obj_list_add_obj(&tbl->base.child_list, new_entry, AUTOGEN_ENV_NONE);
                }

                sb = autogen_obj_find_next_in_list(&sb_it);
            }
        }        
    }

    /* empty properties and comments */
    init_clear_properties_comments(line);


#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* dump old macro layout */
    if (s_res->old_macro_list.n_obj > 0)
    {
        autogen_obj* old_macros;
        autogen_it old_macros_it = INIT_ITERATOR; 

        old_macros_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_NAME;

        fprintf(g_log, "\nOld message macros used, which should be replaced:\n");
        printf("\nOld message macros used, which should be replaced:\n");

        old_macros = autogen_obj_find_in_list(&old_macros_it, &s_res->old_macro_list);
        while (old_macros)
        {
            fprintf(g_log, " * %s\n", old_macros->name);
            printf(" * %s\n", old_macros->name);

            old_macros = autogen_obj_find_next_in_list(&old_macros_it);
        }

        fprintf(g_log, "\n - For more information on changing old macro to new, please refer to 'Message macro update guide'");
        fprintf(g_log, "\n   in 'General' topic on autogen WEB documentation (http://rdsuite.europe.nokia.com/products/autogen/documentation/default.html)\n");
        fprintf(g_log, "\n");

        printf("\n - For more information on changing old macro to new, please refer to 'Message macro update guide'");
        printf("\n   in 'General' topic on autogen WEB documentation (http://rdsuite.europe.nokia.com/products/autogen/documentation/default.html)\n");
        printf("\n");
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    if (s_old_res)
    {
        s_res  = s_old_res;
        s_file = s_old_file;

        if (g_autogen_env == AUTOGEN_ENV_LOCAL)
        {
            fprintf(g_log, "\nFile: %s (%s)", s_file, s_res->logical_name);
            fprintf(g_log, "\n======================================"
                "========================================\n");
        }

        s_old_res  = NULL;
        s_old_file = NULL;
    }
    else
    {
        /* restore last scope and parent */
        init_scope_restore();

        s_file_last = s_file;
        s_file      = NULL;

        /* Remember s_res. To be used in case of Resource Legacy */
        s_last_res = s_res;

        s_res = NULL;
    }
}

    
/* --------------------------------------------------------------------------------------------- */
/*  Name: init_sb_begin
 
    Purpose: 
        Begins a subblock definition
 
    Functional Description:
        Validates the input arguments
        Verifies that the subblock can be defined at this point

    Arguments: 
        name     - [in] symbolic name of the subblock
        id       - [in] value of the subblock ID
        verfrom  - [in] version from which the subblock is valid
        verto    - [in] version from which the subblock is obsolete
        macro    - [in] name of macro (SB_BEGIN or DEFINE_SB_BEGIN)
*/
/* --------------------------------------------------------------------------------------------- */
void init_sb_begin(int line, const char* name, unsigned int id, const char* verfrom, const char* verto, const char* cmt)
{
    unsigned int flags = 0;
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    cmt;
#endif

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check subblock name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    if (s_res->base.subtype & RESOURCE_TRC_ANY)
    {
        flags |= AUTOGEN_SB_IS_TRACE;
    }

    /* create and initialize sb object */
    init_common_seq_create(line, AUTOGEN_OBJ_SB, 0, id, flags, name, verfrom, verto, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* check that the subblock name does not conflict with any sequences */
    {
        autogen_it seq_it = INIT_ITERATOR;

        seq_it.typemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SB_TEMPLATE;
        seq_it.obj.name = name;
        seq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        seq_it.ver      = &s_seq->base.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            seq_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            seq_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        if (autogen_obj_find_in_list(&seq_it, &s_res->seq_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Subblock '%s' conflicts with a %s with the same name",
                name, util_get_obj_type_name((autogen_obj*)s_seq));
        }
    }
    
    if (s_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* Object belongs to Legacy part of resource*/
    {
        ((autogen_obj*)s_seq)->flag |= AUTOGEN_OBJ_IS_LEGACY;
    }

    /* add sb object to server */
    autogen_obj_list_add_obj(&s_res->seq_list, &s_seq->base, AUTOGEN_ENV_LOCAL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&s_seq->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* set new scope and parent */
    init_scope_set(SCOPE_SB, &s_seq->base);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_sb_end
 
    Purpose: 
        Ends a subblock definition
 
    Functional Description:
        Verifies that the subblock can be ended at this point
        Adds the subblock to the data model for the current resource
*/
/* --------------------------------------------------------------------------------------------- */
void init_sb_end(int line)
{
    unsigned int offset      = 0;
    unsigned int offset_type = AUTOGEN_ITEM_OFFSET_EXACT;

    const autogen_item* id_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_SB);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* Check for recursive structure */
    check_seq_recursion(s_file, s_seq, s_res, &s_seq->base.ver);
#endif

    /* set item offsets */
    init_update_item_offsets(&s_seq->base.child_list, &s_seq->base.ver, &offset_type, &offset);

    /* check subblock ID field */
    if (!id_item)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Reference 'SB_ID' is not defined in '%s'", util_get_obj_name(&s_seq->base));
        return; /* To avoid lint warnings */
    }
    /* check if ID is valid */
    else if (s_seq->base.id > (unsigned int)(1 << id_item->length) - 1)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Reference 'SB_ID' is out of range in '%s'", util_get_obj_name(&s_seq->base));
        return; /* To avoid lint warnings */
    }
    /* check if ID offset is valid */
    else if (id_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT || id_item->offset != 0)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Reference 'SB_ID' is not the first item in '%s'", util_get_obj_name(&s_seq->base));
        return; /* To avoid lint warnings */
    }

    /* Check if a subblock already has been defined using the same ID as this one */
    /* Report an warning if this is the case */
    { 
        autogen_it sb_it = INIT_ITERATOR;
        autogen_obj *sb = NULL;
        autogen_ver test_ver;

        /* Search for subblocks in the resource */
        sb_it.typemask = AUTOGEN_OBJ_SB;

        /* Do not use binary search */
        sb_it.sort_type = AUTOGEN_OBJ_LIST_SORT_NONE;

        /* Match the current subblock id against those in the resource subblock list */
        sb_it.idcrit = AUTOGEN_OBJ_ID_EXACT;
        sb_it.obj.id = s_seq->base.id;

        /* Match only subblocks that overlaps version wise */ 
        memcpy(&test_ver, &s_seq->base.ver, sizeof(autogen_ver));
        sb_it.ver      = &test_ver;
        sb_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;

        /* If feature flag defined then only look for subblocks under similar feature flag */
        if (s_env->scope->next ? s_env->scope->next->feature_flags : NULL)
        {
            sb_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            sb_it.obj.feature_flags = s_env->scope->next->feature_flags;
        }

        /* Check if there is subblocks with matching IDs in the resource */
        sb = autogen_obj_find_in_list(&sb_it, &s_res->seq_list);
        while(sb)
        {
            /* Current subblock has already been inserted into the resource */
            /* Check if we have found our self, ie. names are equal */
            if (strcmp(sb->name, s_seq->base.name))
            {        
                /* This is not our self. Report an warning */
                util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 8,
                    "Subblock already defined using the same ID. Subblocks: %s - %s", sb->name, s_seq->base.name);
                break;
            }

            /* We have found our self. Continue checking in the list */
            sb = autogen_obj_find_next_in_list(&sb_it);
        }
    } 

    /* check if SB_LENGTH is defined */
    if (!prop_has(&s_seq->base, PROPERTY_SB_LENGTH_MISSING))
    {
        const autogen_item* length_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH);

        if (!length_item)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'SB_LENGTH' is not defined in '%s'", util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
        /* check length offset */
        else if (length_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Reference 'SB_LENGTH' is not placed at a fixed offset in '%s'", util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
    }

    /* checks for subblocks in shared files */
    if (s_seq->base.res->base.subtype == RESOURCE_SHARED)
    {
        /* check that 16 bit subblock ID's are in the range 0xF000 and 0xF7FF
           for shared resources */
        if (id_item->length == 16 && s_seq->base.id < 0xF000)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'SB_ID' is out of range in '%s'. Value must be between 0xF000 and 0xF7FF", util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }

        /* check that the MSB of the subblock ID is the same as for
           other subblocks in the shared file */
        if (id_item->length == 16)
        {
            autogen_it sb_it = INIT_ITERATOR;
            autogen_obj* sb;

            sb_it.typemask = AUTOGEN_OBJ_SB;
            sb_it.obj.id   = s_seq->base.id;
            sb_it.idcrit   = AUTOGEN_OBJ_ID_NOT;

            /* find first subblock */
            sb = autogen_obj_find_in_list(&sb_it, &s_seq->base.res->seq_list);
            if (sb)
            {
                if ((sb->id & 0xFF00) != (s_seq->base.id & 0xFF00))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Reference 'SB_ID' is out of range in '%s'. Value must be 0x%2Xxx as the other subblocks",
                        util_get_obj_name(&s_seq->base), (sb->id & 0xFF00) >> 8);
                    return; /* To avoid lint warnings */
                }
            }
        }
    }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* verify that the subblock ID does not conflict with other constants of definitions */
    init_add_def(line, AUTOGEN_DEF_CONST, s_seq->base.name, s_seq->base.id, 
        id_item->length == 16 ? AUTOGEN_CONST_UNSIGNED_WORD : AUTOGEN_CONST_UNSIGNED_BYTE,
        &s_seq->base.ver, NULL, NULL, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));
#endif

    /* end the subblock... */
    init_common_seq_end(line, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));

    /* restore last scope and parent */
    init_scope_restore();
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_seq_of
 
    Purpose: 
        Inserts an array in the current sequence
 
    Functional Description:
        Validates the input arguments
        Verifies that the array can be defined at this point
        If number of elements in the array is 1, the element is inserted directly in the sequence
        Adds the array to the current sequence in the data model for the current resource

    Arguments: 
        varname        - [in] name of the variable in the ISI header file
        name (parname) - [in] name to be printed when encoding/decoding the element
        seqname        - [in] name of the sequence defining the array elements
        refname        - [in] name of the reference giving the number of elements (for dynamic arrays)
        flag           - [in] flag determining how the array should be generated inthe ISI header file
        n              - [in] number of elements in the array (for fixed arrays)
        nstr           - [in] number of elements (as string) in the array (for fixed arrays)
*/
/* --------------------------------------------------------------------------------------------- */
void init_seq_of(int line, const char* varname, const char* name, const char* seqname, const char* refname,
                 unsigned int flag, unsigned int n, const char* nstr)
{
    autogen_seq* seq_trav;
    autogen_seq* seq_first;
    autogen_agg_type agg_type = AGG_TYPE_FIXED_SINGLE;
    unsigned int item_flag = 0;    
    autogen_res* seq_res = NULL;
    char* parname = pmd_heap_strdup(name);

    /* check if macro is allowed in the current scope */
    /* reuirement DSEAR002, DSEAR102 */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_TRACE | SCOPE_CASE);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check sequence/subblock name */
    check_c_name(s_file, line, "seqname", seqname, CHECK_NAME_EXIT_ON_FAIL);

    /* --------------------------------------------------------------------- */
    /* checks for SEQ_OF and SB_REF */
    /* --------------------------------------------------------------------- */

    if (!refname)
    {
        /* check number of elements string */
        check_string(s_file, line, "n", nstr, CHECK_NAME_EXIT_ON_FAIL);

        /* check the number of elements */
        if (!strcmp(nstr, "AS_MANY_AS_POSSIBLE"))
        {
            agg_type   = AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE;
            item_flag |= AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;

            /* add the property */
            prop_add_value(PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_DONT_GENERATE, FALSE, "ISIHDR_DONT_GENERATE", 0, FALSE);
        }
        else if (n == 0 || n > 65535)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'n' is out of range. Value must be between 1 and 65535");
            return; /* To avoid lint warnings */
        }
        else if (n > 1)
        {
            agg_type = AGG_TYPE_FIXED_MULTIPLE;

            /* add the constant (or merge with existing constants) */
            init_constant_add(line, nstr, n, AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_env->scope->parent->ver, (s_env->scope ? s_env->scope->feature_flags : NULL));
        }
        else
        {
            agg_type = AGG_TYPE_FIXED_SINGLE;
        }
    }
    /* --------------------------------------------------------------------- */
    /* checks for SEQ_OF_REF */
    /* --------------------------------------------------------------------- */
    else
    {
        /* check reference name */
        check_c_name(s_file, line, "refname", refname, CHECK_NAME_EXIT_ON_FAIL);

        /* set aggregation type */
        /* allow predefined reference name REF_AS_MANY_AS_POSSIBLE or REF_OPTIONAL to be used */
        if (!strcmp(refname, "REF_AS_MANY_AS_POSSIBLE"))
        {
            agg_type = AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE;
        }
        else if (!strcmp(refname, "REF_OPTIONAL"))
        {
            agg_type = AGG_TYPE_DYNAMIC_OPTIONAL;
        }
        else
        {
            agg_type = AGG_TYPE_DYNAMIC_REF;
        }

        /* check array flag */
        if (flag == ISIHDR_MARKER_ANYSIZE ||
            flag == ISIHDR_MARKER_ANYSIZE_BYTE ||
            flag == ISIHDR_MARKER_ANYSIZE_WORD ||
            flag == ISIHDR_MARKER_SINGLE_ELEMENT ||
            flag == ISIHDR_MARKER_SINGLE_ELEMENT_BYTE ||
            flag == ISIHDR_RESERVE_SPACE ||
            flag == ISIHDR_POINTER ||
            flag == ISIHDR_POINTER_VOID ||
            flag == ISIHDR_MARKER_POINTER)
        {
        }
        else if (flag == ISIHDR_DONT_GENERATE)
        {
            item_flag |= AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;
        }
        /* default */
        else
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'flag' is not valid");

            flag = ISIHDR_MARKER_ANYSIZE;
        }

        /* Validate combinations of array type and marker flag */
        if (prop_has_value(NULL, PROPERTY_ARRAY_MAXIMUM_SIZE))
        {
            init_constant_add(line, 
                prop_get_string(NULL, PROPERTY_ARRAY_MAXIMUM_SIZE),
                prop_get_value(NULL, PROPERTY_ARRAY_MAXIMUM_SIZE), 
                AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_seq->base.ver, 
                (s_env->scope ? s_env->scope->feature_flags : NULL));
        }
        else if (flag == ISIHDR_RESERVE_SPACE && agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Impossible flag combination used: ISIHDR_RESERVE_SPACE and REF_AS_MANY_AS_POSSIBLE");

            flag = ISIHDR_MARKER_ANYSIZE;
        }

        /* add the property */
        prop_add_value(PROPERTY_ISIHDR_ARRAY_MARKER, flag, FALSE, "", 0, FALSE);
    }

    /* --------------------------------------------------------------------- */
    /* check the sequence(s) / subblock(s) being referenced */
    /* --------------------------------------------------------------------- */

    if (!strncmp(seqname, "AUTOGEN_SEQ_", strlen("AUTOGEN_SEQ_")))
    {
        seq_res = util_get_unique_res(RESOURCE_SYMBOLS);
    }
    else
    {
        seq_res = s_seq->base.res;
    }

    /* does the referenced sequence or subblock exist for all versions */
    {
        autogen_it seq_it = INIT_ITERATOR;

        seq_it.typemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB;
        seq_it.obj.name = seqname;
        seq_it.ver      = &s_env->scope->parent->ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            seq_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            seq_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        if (!autogen_obj_list_verify_object_span(&seq_it, &seq_res->seq_list))
        {
            int found = FALSE;

            /* try locating the table in the base file of the extension */
            if (prop_has(&seq_res->base, PROPERTY_INHERIT_BASE_RESOURCE_DEFINITIONS))
            {
                autogen_res* base_res = util_get_base_res(seq_res);
                if (base_res && base_res != seq_res)
                {
                    autogen_it seq_it = INIT_ITERATOR;

                    /* check that a sequence exists for the current resource version */
                    seq_it.typemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB;
                    seq_it.obj.name = seqname;
                    seq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                    seq_it.ver      = &base_res->base.ver;
                    if (s_env->scope ? s_env->scope->feature_flags : NULL)
                    {
                        seq_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                        seq_it.obj.feature_flags = s_env->scope->feature_flags;
                    }

                    if (autogen_obj_find_in_list(&seq_it, &base_res->seq_list))
                    {
                        seq_res = base_res;
                        found = TRUE;
                    }
                }
            }

            /* report the error... */
            if (found == FALSE)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "The sequence/subblock '%s' doesn't exist for all required versions", seqname);
            }
        }
    }

    /* find the first sequence */
    {
        autogen_it seq_it = INIT_ITERATOR;

        seq_it.typemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB;
        seq_it.obj.name = seqname;
        seq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        seq_it.ver      = &s_env->scope->parent->ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            seq_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            seq_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        seq_first = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &seq_res->seq_list);
        seq_trav  = seq_first;

        while (seq_trav)
        {
            /* check being performed for all sequences but the first */
            if (seq_trav != seq_first)
            {
                /* check that one sequence exist, if the sequence is not a struct */
                if ((seq_trav->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT) ||
                    (seq_first->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Conflicting sequences are referenced. The sequence types are different");
                    return; /* To avoid lint warnings */
                }

                /* check that the definition name is the same for the two structures */
                if (strcmp(prop_get_string((autogen_obj*)seq_trav, PROPERTY_ISIHDR_STRUCT_NAME),
                    prop_get_string((autogen_obj*)seq_first, PROPERTY_ISIHDR_STRUCT_NAME)))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Conflicting sequences are referenced. The sequences have different structure names");
                }
            }

            /* checks being performed for all sequences */
            {
                if (agg_type != AGG_TYPE_FIXED_SINGLE)
                {
                    /* check that sequence elements can be directly inserted,
                    if the sequence is not a structure
                    */
                    if ((seq_trav->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT) && util_get_n_def(&seq_trav->base.child_list) > 1)
                    {
                        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                            "The referenced sequence '%s' is inserted as an array ('n' > 1). "
                            "This is not possible, as the sequence contains several elements",
                            seq_trav->base.name);
                        return; /* To avoid lint warnings */
                    }
                }
            }

            /* find next sequence / subblock */
            seq_trav = (autogen_seq*)autogen_obj_find_next_in_list(&seq_it);
        }
    }

    /* --------------------------------------------------------------------- */
    /* add the sequence info to the sequence object */
    /* --------------------------------------------------------------------- */

    /* if sequence is a structure, make a reference to the sequence */
    if (!(seq_first->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
    {
        /* create and initialize item object */
        autogen_item* seq_of = init_item_create(line, sizeof(autogen_item_struct), AUTOGEN_ITEM_STRUCT, 
            item_flag | AUTOGEN_STRUCT_SEQ, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

        /* copy version */
        memcpy(&seq_of->base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

        seq_of->agg_n    = n;
        seq_of->agg_type = agg_type;

        ((autogen_item_struct*)seq_of)->seqname = seqname;
        ((autogen_item_struct*)seq_of)->seqres  = seq_res;

        if (agg_type == AGG_TYPE_FIXED_SINGLE ||
            agg_type == AGG_TYPE_FIXED_MULTIPLE)
        {
            seq_of->agg_n_str = nstr;
        }
        else if (agg_type == AGG_TYPE_DYNAMIC_REF)
        {
            seq_of->refname = refname;
            reference_use_counter(seq_of, (s_env->scope ? s_env->scope->feature_flags : NULL));
        }

        /* update properties and comments */
        init_update_properties_comments(&seq_of->base);

        /* add maximum array size (from property) */
        if (prop_has((autogen_obj*)seq_of, PROPERTY_ARRAY_MAXIMUM_SIZE))
        {
            init_constant_add(line, 
                prop_get_string((autogen_obj*)seq_of, PROPERTY_ARRAY_MAXIMUM_SIZE),
                prop_get_value((autogen_obj*)seq_of, PROPERTY_ARRAY_MAXIMUM_SIZE), 
                AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_seq->base.ver, 
                (s_env->scope ? s_env->scope->feature_flags : NULL));
        }

        /* add item relations */
        init_item_add_relations((autogen_item*)s_item, &s_env->scope->parent->ver, (s_env->scope ? s_env->scope->feature_flags : NULL));

        /* add item object to sequence object */
        init_item_add(s_item, (s_env->scope ? s_env->scope->feature_flags : NULL));
    }
    /* if sequence is not a structure, copy all items to the current sequence */
    else
    {
        const autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(&seq_first->base.child_list);
        unsigned int n_def = util_get_n_def(&seq_first->base.child_list);

        /* add relation from sequence to s_parent sequence */
        init_add_obj_relation(s_env->scope->parent, (autogen_obj*)seq_first, NULL, (s_env->scope ? s_env->scope->feature_flags : NULL));

        /* Copy reference transformations */
        reference_copy_transformations(reference_get_handle_from_obj(s_env->scope->parent), &seq_first->ref_handle);

        /* iterate through all items in the sequence */
        while (item)
        {
            /* make a copy of the item */
            autogen_item* copy_item = (autogen_item*)autogen_obj_copy_deep((autogen_obj*)item, NULL, s_env->scope->parent, &s_env->scope->parent->ver);

            memcpy(&copy_item->base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

            /* save feature flags from the scope */
            copy_item->base.feature_flags = (s_env->scope ? s_env->scope->feature_flags : NULL);

            /* verify that an multi dimensional array is not defined */
            if (agg_type != AGG_TYPE_FIXED_SINGLE && copy_item->agg_type != AGG_TYPE_FIXED_SINGLE)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Multidimensional array defined for this item");
                return; /* To avoid lint warnings */
            }

            if (n_def == 1)
            {
                /* transfer the saved comments to the first item */
                /* if old comments exist, produce a warning and remove old comments */
                if (copy_item->base.cmt_list)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                        "Comments to this item have no effect");

                    copy_item->base.cmt_list = NULL;
                }

                /* update properties and comments */
                init_update_properties_comments((autogen_obj*)copy_item);

                /* add maximum array size (from property) */
                if (prop_has((autogen_obj*)copy_item, PROPERTY_ARRAY_MAXIMUM_SIZE))
                {
                    init_constant_add(line, 
                        prop_get_string((autogen_obj*)copy_item, PROPERTY_ARRAY_MAXIMUM_SIZE),
                        prop_get_value((autogen_obj*)copy_item, PROPERTY_ARRAY_MAXIMUM_SIZE), 
                        AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_seq->base.ver, copy_item->base.feature_flags);
                }

                /* substitute varname and parname of the first element */
                copy_item->varname = varname;
                copy_item->parname = parname;

                copy_item->base.flag |= item_flag;

                /* upgrade aggregation information */
                if (agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE ||
                    agg_type == AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH ||
                    agg_type == AGG_TYPE_DYNAMIC_OPTIONAL)
                {
                    copy_item->agg_type = agg_type;
                }
                else if (agg_type == AGG_TYPE_DYNAMIC_REF)
                {
                    copy_item->agg_type = agg_type;
                    copy_item->refname  = refname;
                }
                else if (agg_type == AGG_TYPE_FIXED_MULTIPLE)
                {
                    copy_item->agg_type  = agg_type;
                    copy_item->agg_n     = n;
                    copy_item->agg_n_str = nstr;
                }

                /* check that an array of references is not defined */
                if (copy_item->base.subtype == AUTOGEN_ITEM_REF && copy_item->agg_type != AGG_TYPE_FIXED_SINGLE)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "An array of references is defined");
                    return; /* To avoid lint warnings */
                }

                /* check that an array of timestamps is not defined */
                if (copy_item->base.subtype == AUTOGEN_ITEM_TIMESTAMP &&
                    copy_item->agg_type != AGG_TYPE_FIXED_SINGLE &&
                    copy_item->agg_type != AGG_TYPE_DYNAMIC_OPTIONAL)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "An array of timestamps is defined");
                    return; /* To avoid lint warnings */
                }

                /* check that an array of choices is not defined */
                if (copy_item->base.subtype == AUTOGEN_ITEM_CHOICE &&
                    copy_item->agg_type != AGG_TYPE_FIXED_SINGLE)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "An array of choices is defined");
                    return; /* To avoid lint warnings */
                }

                /* check that an array of trace structures is not defined */
                if (copy_item->base.subtype == AUTOGEN_ITEM_TRCSTRUCTURE &&
                    copy_item->agg_type != AGG_TYPE_FIXED_SINGLE)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "An array of trace structures is defined");
                    return; /* To avoid lint warnings */
                }

                /* check that an array of merged fields containing 
                references and/or choices and/or timestamps is not defined */
                if (copy_item->base.subtype == AUTOGEN_ITEM_MERGE &&
                    copy_item->agg_type != AGG_TYPE_FIXED_SINGLE)
                {
                    autogen_obj* merge_item = autogen_obj_get_first_in_list(&copy_item->base.child_list);
                    while (merge_item)
                    {
                        if (merge_item->type == AUTOGEN_OBJ_ITEM && merge_item->subtype == AUTOGEN_ITEM_REF)
                        {
                            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                                "An array of references is defined");
                        }
                        else if (merge_item->type    == AUTOGEN_OBJ_ITEM &&
                                 merge_item->subtype == AUTOGEN_ITEM_CHOICE)
                        {
                            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                                "An array of choices is defined");
                        }
                        else if (merge_item->type    == AUTOGEN_OBJ_ITEM &&
                                 merge_item->subtype == AUTOGEN_ITEM_TIMESTAMP)
                        {
                            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                                "An array of timestamps is defined");
                        }

                        merge_item = merge_item->next;
                    }
                }
            }

            /* Update reference table from item
                - If item is a reference, the item pointer in the reference table should point to the copy, not org
                - Verify at the same time that there are no redefinitions of references
                - If item is using a reference, verify that it exist
            */
            reference_copy_item(copy_item, &seq_first->ref_handle);

            /* add item relations */
            init_item_add_relations(copy_item, &s_env->scope->parent->ver, copy_item->base.feature_flags);

            /* add item object to sequence object */
            init_item_add(copy_item, copy_item->base.feature_flags);

            item = (autogen_item*)item->base.next;
        }
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: init_value_const
 
    Purpose: 
        Inserts a constant element in the current sequence
 
    Functional Description:
        Validates the input arguments
        Verifies that the constant element can be defined at this point
        Adds the element to the current sequence in the data model for the current resource

    Arguments: 
        varname    - [in] name of the variable in the ISI header file
        parname    - [in] name to be printed when encoding/decoding the element
        tblname    - [in] name of the (predefined) constant or bitmask table
        resname    - [in] name of resource from which the table is located (optional)
        verto      - [in] version from which the constant is obsolete
*/
/* --------------------------------------------------------------------------------------------- */
void init_value_const(int line, const char* varname, const char* name, const char* tblname, const char* resname)
{
    autogen_item_value* value;
    autogen_it tbl_it = INIT_ITERATOR;
    autogen_tbl* tbl_first = NULL;
    autogen_tbl* tbl = NULL;
    char* parname = pmd_heap_strdup(name);
    autogen_item* filler_replacement = NULL;

    /* initialize table iterator handle */
    tbl_it.typemask    = AUTOGEN_OBJ_TBL;
    tbl_it.subtypemask = AUTOGEN_TBL_CONST_ANY;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE | SCOPE_FTD_TBL_ENTRY);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check referenced table name */ 
    check_c_name(s_file, line, "tblname", tblname, CHECK_NAME_EXIT_ON_FAIL);

    /* --------------------------------------------------------------------- */
    /* create value object */
    /* --------------------------------------------------------------------- */
    value = (autogen_item_value*)init_item_create(line, sizeof(autogen_item_value), 
        AUTOGEN_ITEM_VALUE, 0, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&value->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    /* handle filler replacement */
    filler_replacement = init_handle_filler_replacement(line, &value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* --------------------------------------------------------------------- */
    /* checks for VALUE_CONST_IMP */
    /* --------------------------------------------------------------------- */
    if (resname)
    {
        autogen_res* imp_res;
        autogen_it res_it = INIT_ITERATOR;

        /* add flag defining that the table should be imported */
        value->base.base.flag |= AUTOGEN_ITEM_USE_IMPORTED_RES;
        value->pres.tblname    = tblname;
        value->pres.tblresname = resname;

        /* check resource name */
        check_c_name(s_file, line, "resname", resname, CHECK_NAME_EXIT_ON_FAIL);

        /* check that the resource exist */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask ^= RESOURCE_SHARED; /* If VALUE_CONST_IMP is used then the table should not be in a shared file */
        res_it.obj.name    = resname;

        imp_res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        if (!imp_res)
        {
            value->base.base.flag  |= AUTOGEN_ITEM_USE_IMPORTED_RES_NOT_RESOLVED;

            value->base.order      = AUTOGEN_ORDER_BE;
            value->base.length     = 8;
            value->pres.type       = AUTOGEN_PRESENTATION_HEX;

            /* update merge info */
            if (s_env->scope->scope == SCOPE_MERGE)
            {
                s_merge_length += abs(value->base.length); 
            }

            /* add item object to s_parent object */
            init_item_add(&value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

            return;
        }

        value->base.length = init_pres_const(line, &value->pres, AUTOGEN_PRESENTATION_CONST, tblname, imp_res);

        /* check that a table exists for the current resource version */
        {
            tbl_it.obj.name    = value->pres.tblname;
            tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            tbl_it.ver         = &imp_res->base.ver;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                tbl_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            tbl_first = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &imp_res->tbl_list);
        }

        /* if table doesn't exist, try shared file. Maybe it was moved without telling clients... */
        if (!tbl_first && imp_res->shared_res)
        {
            imp_res = imp_res->shared_res;

            tbl_it.obj.name    = value->pres.tblname;
            tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            tbl_it.ver         = &imp_res->base.ver;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                tbl_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            tbl_first = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &imp_res->tbl_list);
        }
        /* if it still doesn't exist, either message macro file include order  or wrong table name 
           prevents us from finding the 
           Clear flag and try again in post processing. But offset calculation/alignment check is now lost!
        */
        if (!tbl_first)
        {
            value->base.base.flag |= AUTOGEN_ITEM_USE_IMPORTED_RES_NOT_RESOLVED;

            value->base.order  = AUTOGEN_ORDER_BE;
            value->base.length = 8;
            value->pres.type   = AUTOGEN_PRESENTATION_HEX;

            /* update merge info */
            if (s_env->scope->scope == SCOPE_MERGE)
            {
                s_merge_length += abs(value->base.length); 
            }

            /* add item object to s_parent object */
            init_item_add(&value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

            return;
        }
    }
    /* --------------------------------------------------------------------- */
    /* checks for VALUE_CONST, CONST_REF, BIT_REF */
    /* --------------------------------------------------------------------- */
    else
    {
        /* check if constant refers to predefined table */
        value->base.length = init_pres_const(line, &value->pres,
            AUTOGEN_PRESENTATION_CONST_ANY | AUTOGEN_PRESENTATION_ID_ANY,
            tblname, s_res);

        /* if predefined constant is referenced */ 
        if (value->pres.type & AUTOGEN_PRESENTATION_SYMBOL_ANY)
        {
            tbl_it.obj.name = value->pres.tblname;

            /* check that a table exist for the current resource version */
            tbl_first = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &value->pres.tblres->tbl_list);
            if (!tbl_first)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Argument 'tblname' is not valid");
            }
        }
        /* else if a defined constant table is referenced */ 
        else if (value->pres.type & AUTOGEN_PRESENTATION_CONST)
        {
            autogen_it tbl_check_it = INIT_ITERATOR;

            tbl_check_it.obj.name    = tblname;
            tbl_check_it.ver         = &value->base.base.ver;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                tbl_check_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                tbl_check_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            /* verify that the table is defined for the whole version interval of the parent */
            if (!autogen_obj_list_verify_object_span(&tbl_check_it, &s_env->scope->parent->res->tbl_list))
            {
                int found = FALSE;

                /* try locating the table in the base file of the extension */
                if (prop_has(&s_env->scope->parent->res->base, PROPERTY_INHERIT_BASE_RESOURCE_DEFINITIONS))
                {
                    autogen_res* base_res = util_get_base_res(s_env->scope->parent->res);
                    if (base_res && base_res != s_env->scope->parent->res)
                    {
                        /* check that a table exists for the current resource version */
                        tbl_it.obj.name    = tblname;
                        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                        tbl_it.ver         = &base_res->base.ver;
                        if (s_env->scope ? s_env->scope->feature_flags : NULL)
                        {
                            tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                            tbl_it.obj.feature_flags = s_env->scope->feature_flags;
                        }

                        tbl_first = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &base_res->tbl_list);
                        if (tbl_first)
                        {
                            value->pres.tblres     = base_res;
                            value->pres.tblresname = base_res->base.name;

                            found = TRUE;
                        }
                    }
                }

                /* report the error... */
                if (found == FALSE)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "The table '%s' doesn't exist for all required versions", tblname);
                }
            }

            /* setup version criteria for the general table checking */
            /* check any version within the version of the sequence */
            if (!tbl_first)
            {
                tbl_it.obj.name    = value->pres.tblname;
                tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                tbl_it.ver         = &value->base.base.ver;
                if (s_env->scope ? s_env->scope->feature_flags : NULL)
                {
                    tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    tbl_it.obj.feature_flags = s_env->scope->feature_flags;
                }

                tbl_first = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &value->pres.tblres->tbl_list);
            }
        }
        else if (value->pres.type & AUTOGEN_PRESENTATION_ID_ANY)
        {
            value->base.order = AUTOGEN_ORDER_BE;
            /* length is already set by item_pres_init */
        }
        else if (tblname && (!strcmp(tblname, "MSG_ID") || !strcmp(tblname, "SUB_MSG_ID")))
        {
            value->base.order = AUTOGEN_ORDER_BE;
            /* length is already set by item_pres_init */
        }
    }

    /* --------------------------------------------------------------------- */
    /* checks all referenced tables */
    /* --------------------------------------------------------------------- */
    if (value->pres.type & AUTOGEN_PRESENTATION_CONST_ANY)
    {
        value->base.length = tbl_first->orgtbl->length;
        value->base.order  = tbl_first->orgtbl->order;

        tbl = tbl_first;
        while (tbl)
        {
            /* check the size of the table constants */
            init_check_length(line, tbl->orgtbl->length, TRUE, (PMD_FILE_FORMAT >= 600), (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);
            /* Original
            init_check_length(line, tbl->orgtbl->length, TRUE, FALSE, (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);
            */

            /* check the data order of the table constants */
#if (PMD_FILE_FORMAT >= 501)
            /* data order LE can be used with an element in a merged field, but only if MERGE_BEGIN specifies LE */
            if (s_env->scope->scope == SCOPE_MERGE)
            {
                unsigned int merge_order = ((autogen_item*)s_env->scope->parent)->order;
                if (tbl->orgtbl->order != merge_order)
                {
                    if (tbl->length > 1)
                    {
                        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                            "Referenced table can't be used in this context. All elements within a merged field must have the same order as MERGE_BEGIN macro");
                        return;
                    }
                }
            }
#else
            /* data order LE can't be used with an element in a merged field */
            if (s_env->scope->scope == SCOPE_MERGE && tbl->orgtbl->order == AUTOGEN_ORDER_LE)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Referenced table can't be used in this context");
                return; 
            }
#endif

            /* check if table constants are binary compatible in size */
            if (tbl->orgtbl->length != value->base.length)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Several incompatible tables are referenced from this item");
                return; /* To avoid lint warnings */
            }

            /* check if table constants are binary compatible in data order */
            if (tbl->orgtbl->order != value->base.order)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Several incompatible tables are referenced from this item");
                return; /* To avoid lint warnings */
            }

            /* if a default value is defined, check that the constant exist 
               in the table and it has the same value
            */
            if (prop_has_valid_string((autogen_obj*)value, PROPERTY_ITEM_DEFAULT_VALUE))
            {
                autogen_obj* entry;
                autogen_it tbl_entry_it = INIT_ITERATOR;

                tbl_entry_it.obj.name = prop_get_string((autogen_obj*)value, PROPERTY_ITEM_DEFAULT_VALUE);
                if (s_env->scope ? s_env->scope->feature_flags : NULL)
                {
                    tbl_entry_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    tbl_entry_it.obj.feature_flags = s_env->scope->feature_flags;
                }

                entry = autogen_obj_find_in_list(&tbl_entry_it, &tbl->base.child_list);
                if (!entry)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "The default value defined for this item is not valid");
                }
            }

            /* find the next table  */
            tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
        }

        /* update bool type from table */
        if (prop_has((autogen_obj*)tbl_first, PROPERTY_ISIHDR_GENERATE_AS_BOOL))
        {
            prop_add_simple_to_object((autogen_obj*)value, PROPERTY_ISIHDR_GENERATE_AS_BOOL, NULL, 0, FALSE);
        }
        else if (prop_has((autogen_obj*)tbl_first, PROPERTY_ISIHDR_GENERATE_AS_BITFIELD))
        {
            prop_add_simple_to_object((autogen_obj*)value, PROPERTY_ISIHDR_GENERATE_AS_BITFIELD, NULL, 0, FALSE);
        }
        /* update definition name from table */
        if (!prop_has((autogen_obj*)value, PROPERTY_ISIHDR_DEFINITION_NAME) && prop_has((autogen_obj*)tbl_first, PROPERTY_ISIHDR_DEFINITION_NAME))
        {
            if (!(prop_get_flags((autogen_obj*)tbl_first, PROPERTY_ISIHDR_DEFINITION_NAME) & PROPERTY_FLAG_DEFAULT))
            {
                prop_add_string_to_object((autogen_obj*)value, PROPERTY_ISIHDR_DEFINITION_NAME, 
                    prop_get_string((autogen_obj*)tbl_first, PROPERTY_ISIHDR_DEFINITION_NAME), NULL, 0, FALSE);
            }
        }
    }

    /* handle filler replacement */
    if (filler_replacement)
    {
        filler_replacement->length = value->base.length;
    }

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += abs(value->base.length); 
    }
    else if (s_env->scope->scope == SCOPE_FTD_TBL_ENTRY)
    {
        s_env->ftd_length_sum += abs(value->base.length);
    }

    /* add the relation to this sequence from the table */
    init_item_add_relations((autogen_item*)value, &s_env->scope->parent->ver, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* add item object to s_parent object */
    init_item_add(&value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}


/*  Init function for the MSG_BEGIN macro */
void init_msg_begin(int line, unsigned int id, const char* name, unsigned int type, const char* verfrom, const char* verto, const char* cmt)
{
    unsigned int subtype = 0;
    unsigned int flag    = 0;
    autogen_obj_list* msg_list = &s_res->msg_list;
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    cmt;
#endif

    /* Set correct message list */
    if (prop_has(&s_res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        if (type == MESSAGE_REQ)
        {
            msg_list = &s_res->msg_dev_dep_req_list;
        }
        else
        {
            msg_list = &s_res->msg_dev_dep_resp_list;
        }
    }

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* default, don't generate in PMD for public/restricted PMD types */
    if (!prop_has(NULL, PROPERTY_PMD_PUBLIC))
    {
        if ((s_res->base.subtype & RESOURCE_ISI) && s_res->base.id == PN_TRACE && !strcmp(name, "TRACE_INV_DATA_IND"))
        {
            prop_add_simple(PROPERTY_PMD_PUBLIC, 0, FALSE);
        }
    }
    if (prop_has(NULL, PROPERTY_PMD_PUBLIC))
    {
        s_res->base.flag |= AUTOGEN_OBJ_IS_PMD_PUBLIC | AUTOGEN_OBJ_IS_PMD_RESTRICTED;
        flag |= AUTOGEN_OBJ_IS_PMD_PUBLIC | AUTOGEN_OBJ_IS_PMD_RESTRICTED;
    }
    if (prop_has(NULL, PROPERTY_PMD_RESTRICTED))
    {
        s_res->base.flag |= AUTOGEN_OBJ_IS_PMD_RESTRICTED;
        flag |= AUTOGEN_OBJ_IS_PMD_RESTRICTED;
    }

    /* check that the resource is not shared */
    if (s_res->base.subtype == RESOURCE_SHARED)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Macro can't be used in this context");
        return; /* To avoid lint warnings */
    }

    /* check message name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check message type and convert to internal constant */
    if (type == MESSAGE_UNKNOWN)
    {
        if (!(s_res->base.flag & AUTOGEN_RES_HAS_NO_MESSAGES))
        {
            if (strstr(name, "_REQ"))
            {
                flag |= AUTOGEN_MSG_REQ;
            }
            else if (strstr(name, "_RESP"))
            {
                flag |= AUTOGEN_MSG_RESP;
            }
            else if (strstr(name, "_IND"))
            {
                flag |= AUTOGEN_MSG_IND;
            }
            else if (strstr(name, "_NTF"))
            {
                flag |= AUTOGEN_MSG_NTF;
            }
        }
    }
    else if (type == MESSAGE_REQ)
    {
        flag |= AUTOGEN_MSG_REQ;
    }
    else if (type == MESSAGE_RESP)
    {
        flag |= AUTOGEN_MSG_RESP;
    }
    else if (type == MESSAGE_IND)
    {
        flag |= AUTOGEN_MSG_IND;
    }
    else if (type == MESSAGE_NTF)
    {
        flag |= AUTOGEN_MSG_NTF;
    }
    else if (type == MESSAGE_BASE)
    {
        flag |= AUTOGEN_MSG_FUNCTION_MASK | AUTOGEN_MSG_BASE_IS_USER_DEFINED;
    }
    else if (type == STI_TRACE)
    {
        flag |= AUTOGEN_MSG_TRC | AUTOGEN_MSG_TRC_STI;
    }
    else if (type == WCDMA_CDSP_TRACE)
    {
        flag |= AUTOGEN_MSG_TRC;
    }
    else if (type == MESSAGE_TRACE)
    {
        flag |= AUTOGEN_MSG_TRC;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'type' is not valid");
    }

    if (s_res->base.flag & AUTOGEN_RES_HAS_NO_MESSAGES)
    {
        flag |= AUTOGEN_MSG_IS_PROTOCOL;

    }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
#ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
    {
        autogen_it msg_it  = INIT_ITERATOR;

        msg_it.typemask    = (type == MESSAGE_BASE ? AUTOGEN_OBJ_MSG : AUTOGEN_OBJ_MSG_BASE);
        msg_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        msg_it.obj.id      = id;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            msg_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        if (autogen_obj_find_in_list(&msg_it, msg_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Message ID 0x%2.2X used in ordinary message and as base message for submessage(s)", id);
        }
    }
#endif
#endif

    /* check for normal messages */
    if (s_res->base.subtype & (RESOURCE_ISI_ANY | RESOURCE_MEDIA_MODULE | RESOURCE_MEDIA_MODULE_EXTENSION))
    {
        /* check if id is valid */
        if (id > 0xFF)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is out of range. Value must be between 0x00 and 0xFF");
        }

        /* check if id is < 0xF0 for ISI messages */
        if (s_res->base.subtype == RESOURCE_ISI || 
            s_res->base.subtype == RESOURCE_ISI_EXTENSION || 
            s_res->base.subtype == RESOURCE_ISI_PRIVATE || 
            s_res->base.subtype == RESOURCE_ISI_PREFIX)
        {
            autogen_res* base_res = util_get_base_res(s_res);
            if (!base_res) base_res = s_res;

            if ((base_res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES) && id >= 0xF0)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                    "Argument 'id' is out of range. Value >= 0xF0 are reserved for common messages");
            }
        }
    }

    /* create and initialize message object */
    init_common_seq_create(line, type == MESSAGE_BASE ? AUTOGEN_OBJ_MSG_BASE : AUTOGEN_OBJ_MSG, subtype, id, flag, name, verfrom, verto, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* checks for resource extensions */
    if (s_res->base.subtype == RESOURCE_ISI_EXTENSION)
    {
        autogen_it res_it = INIT_ITERATOR;
        autogen_res* ext_res;

        /* find original resource */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_ISI;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = s_res->base.id;

        ext_res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        if (ext_res)
        {
            autogen_it msg_it = INIT_ITERATOR;

            /* check for conflicting message name */
            msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
            msg_it.obj.name    = name;
            msg_it.ver         = &s_seq->base.ver;
            msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                msg_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            if (autogen_obj_find_in_list(&msg_it, &ext_res->msg_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Redefinition of message '%s'", name);
            }
        }

        if (ext_res)
        {
            autogen_it msg_it = INIT_ITERATOR;

            /* check for conflicting message ID's */
            msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
            msg_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
            msg_it.obj.id      = id;
            msg_it.ver         = &s_seq->base.ver;
            msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                msg_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            if (autogen_obj_find_in_list(&msg_it, &ext_res->msg_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Redefinition of message ID 0x%2.2X", id);
            }
        }

        /* find other resource extensions */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_ISI_EXTENSION;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = s_res->base.id;

        ext_res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        while (ext_res)
        {
            if (ext_res != s_res)
            {
                autogen_it msg_it = INIT_ITERATOR;

                /* check for conflicting message name */
                msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
                msg_it.obj.name    = name;
                msg_it.ver         = &s_seq->base.ver;
                msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                if (s_env->scope ? s_env->scope->feature_flags : NULL)
                {
                    msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    msg_it.obj.feature_flags = s_env->scope->feature_flags;
                }

                if (autogen_obj_find_in_list(&msg_it, &ext_res->msg_list))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Redefinition of message '%s'", name);
                }
            }

            if (ext_res != s_res)
            {
                autogen_it msg_it = INIT_ITERATOR;

                /* check for conflicting message ID's */
                msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
                msg_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
                msg_it.obj.id      = id;
                msg_it.ver         = &s_seq->base.ver;
                msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                if (s_env->scope ? s_env->scope->feature_flags : NULL)
                {
                    msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    msg_it.obj.feature_flags = s_env->scope->feature_flags;
                }

                if (autogen_obj_find_in_list(&msg_it, &ext_res->msg_list))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Redefinition of message ID 0x%2.2X", id);
                }
            }

            ext_res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
        }
    }
    else if (s_res->base.subtype == RESOURCE_PROTOCOL_EXTENSION)
    {
        autogen_it res_it = INIT_ITERATOR;
        autogen_res* ext_res;

        /* find original resource */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_PROTOCOL;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = s_res->base.id;

        ext_res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        if (ext_res)
        {
            autogen_it msg_it = INIT_ITERATOR;

            /* check for conflicting message name */
            msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
            msg_it.obj.name    = name;
            msg_it.ver         = &s_seq->base.ver;
            msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                msg_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            if (autogen_obj_find_in_list(&msg_it, &ext_res->msg_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Redefinition of message '%s'", name);
            }
        }
        if (ext_res)
        {
            autogen_it msg_it = INIT_ITERATOR;

            /* check for conflicting message ID's */
            msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
            msg_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
            msg_it.obj.id      = id;
            msg_it.ver         = &s_seq->base.ver;
            msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                msg_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            if (autogen_obj_find_in_list(&msg_it, &ext_res->msg_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Redefinition of message ID 0x%2.2X", id);
            }
        }

        /* find other resource extensions */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_PROTOCOL_EXTENSION;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = s_res->base.id;

        ext_res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        while (ext_res)
        {
            if (ext_res != s_res)
            {
                autogen_it msg_it = INIT_ITERATOR;

                /* check for conflicting message name */
                msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
                msg_it.obj.name    = name;
                msg_it.ver         = &s_seq->base.ver;
                msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                if (s_env->scope ? s_env->scope->feature_flags : NULL)
                {
                    msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    msg_it.obj.feature_flags = s_env->scope->feature_flags;
                }

                if (autogen_obj_find_in_list(&msg_it, &ext_res->msg_list))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Redefinition of message '%s'", name);
                }
            }
            if (ext_res != s_res)
            {
                autogen_it msg_it = INIT_ITERATOR;

                /* check for conflicting message ID's */
                msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
                msg_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
                msg_it.obj.id      = id;
                msg_it.ver         = &s_seq->base.ver;
                msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                if (s_env->scope ? s_env->scope->feature_flags : NULL)
                {
                    msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    msg_it.obj.feature_flags = s_env->scope->feature_flags;
                }

                if (autogen_obj_find_in_list(&msg_it, &ext_res->msg_list))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Redefinition of message ID 0x%2.2X", id);
                }
            }

            ext_res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
        }
    }
    else if ((s_res->base.subtype == RESOURCE_ISI) ||
             (s_res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES) ||
             (s_res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT) ||
             (s_res->base.subtype == RESOURCE_ISI_MEDIA_CONTROL) ||
             (s_res->base.subtype == RESOURCE_ISI_DSP) ||
             (s_res->base.subtype == RESOURCE_MEDIA_MODULE) ||
             (s_res->base.subtype == RESOURCE_PHONET) ||
             (s_res->base.subtype == RESOURCE_PHONET_EXT) ||
             (s_res->base.subtype == RESOURCE_TRC_MCU) ||
             (s_res->base.subtype == RESOURCE_TRC_DSP5_CDSP) ||
             (s_res->base.subtype == RESOURCE_TRC_DSP5_ADSP) ||
             (s_res->base.subtype == RESOURCE_ISI_PREFIX) ||
             (s_res->base.subtype == RESOURCE_ISI_PRIVATE) ||
             (s_res->base.subtype == RESOURCE_PROTOCOL))

    {
        {
            autogen_it msg_it = INIT_ITERATOR;

            /* check for conflicting message name */
            msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
            msg_it.obj.name    = name;
            msg_it.ver         = &s_seq->base.ver;
            msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                msg_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            if (autogen_obj_find_in_list(&msg_it, msg_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Redefinition of message '%s'", name);
            }
        }
        {
            autogen_it msg_it = INIT_ITERATOR;

            /* check for conflicting message ID's */
            msg_it.typemask    = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
            msg_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
            msg_it.obj.id      = id;
            msg_it.ver         = &s_seq->base.ver;
            msg_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                msg_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            /* for MM's ID's can be reused, but not with same type REQ/RESP/... */
            if (s_res->base.subtype == RESOURCE_MEDIA_MODULE)
            {
                msg_it.flagany = flag & AUTOGEN_MSG_FUNCTION_MASK;
            }

            if (autogen_obj_find_in_list(&msg_it, msg_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Redefinition of message ID 0x%2.2X", id);
            }
        }
    }

    if (s_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* Object belongs to Legacy part of resource*/
    {
        ((autogen_obj*)s_seq)->flag |= AUTOGEN_OBJ_IS_LEGACY;
    }
    /* add message object to server */
    autogen_obj_list_add_obj(msg_list, &s_seq->base, AUTOGEN_ENV_LOCAL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&s_seq->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    }

    /* check that the message ID doesn't conflict with other definitions
       or constants in the resource */
    init_add_def(line, AUTOGEN_DEF_CONST, name, id, AUTOGEN_CONST_UNSIGNED_BYTE, &s_seq->base.ver, NULL, NULL, (s_env->scope ? s_env->scope->feature_flags : NULL));

    if (!prop_has_valid_string(&s_seq->base, PROPERTY_ISIHDR_STRUCT_LENGTH_NAME) &&
         prop_has_valid_string(&s_seq->base, PROPERTY_ISIHDR_STRUCT_PHONET_LENGTH_NAME) )
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
            "When using PROPERTY_ISIHDR_STRUCT_PHONET_LENGTH_NAME, property PROPERTY_ISIHDR_STRUCT_LENGTH_NAME must be something other than empty string.");
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* set new scope and parent */
    init_scope_set(SCOPE_MSG, &s_seq->base);
}


/*  Init function for the MSG_END macro 
*/
void init_msg_end(int line)
{
    unsigned int offset      = 0;
    unsigned int offset_type = AUTOGEN_ITEM_OFFSET_EXACT;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_MSG);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* Check for recursive structure */
    check_seq_recursion(s_file, s_seq, s_res, &s_seq->base.ver);
#endif

    /* set item offsets */
    init_update_item_offsets(&s_seq->base.child_list, &s_seq->base.ver, &offset_type, &offset);

    if (s_seq->base.child_list.n_obj == 0)
    {
        s_seq->base.flag |= AUTOGEN_MSG_HAS_NO_ELEMENTS;
    }

    /* general message checks */
    if (s_seq->base.child_list.n_obj > 0 && s_res->msg_id_offset != AUTOGEN_NOT_SUPPORTED && !prop_has(&s_res->base, PROPERTY_PROTOCOL_HAS_NO_MESSAGES))
    {
        const autogen_item* id_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID);

        /* check that message ID is defined */
        if (!id_item)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'MSG_ID' is not defined in '%s'", util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
        else
        {
            /* if message ID offset varies with resource type, make sure it is set on the resource */
            if (s_res->msg_id_offset == AUTOGEN_VALUE_VARIES)
            {
                s_res->msg_id_offset = (int)id_item->offset;
            }
            /* check that message ID offset is fixed */
            if (id_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'MSG_ID' is not placed at fixed offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
            /* check that offset is correct according to resource rules */
            else if (id_item->offset != (unsigned int)s_res->msg_id_offset)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'MSG_ID' is placed at illegal offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
            /* check message ID value */
            else if (id_item->length == 8  && s_seq->base.id > 0xFF || 
                     id_item->length == 16 && s_seq->base.id > 0xFFFF)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Message ID in '%s' is out of range", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
        }
    }

    /* checks for message length fields */
    if (s_res->msg_length_offset != AUTOGEN_NOT_SUPPORTED)
    {
        const autogen_item* length_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH);
        if (length_item)
        {
            /* if message length offset varies with resource type, make sure it is set on the resource */
            if (s_res->msg_length_offset == AUTOGEN_VALUE_VARIES)
            {
                s_res->msg_length_offset = (int)length_item->offset;
            }
            /* check that message length is placed at fixed offset */
            if (length_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'MSG_LENGTH' is not placed at a fixed offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
            /* check that offset is correct according to resource rules */
            else if (length_item->offset != (unsigned int)s_res->msg_length_offset)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'MSG_ID' is placed at illegal offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
        }
    }

    /* checks for private messages */
    if (s_seq->base.res->base.subtype == RESOURCE_ISI_PRIVATE)
    {
        const autogen_item* priv_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_PRIVATE_ID);

        if (!priv_item)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'PRIVATE_ID' is not defined in '%s'", util_get_obj_name(&s_seq->base));
        }
        /* check that private ID is placed at fixed offset */
        else if (priv_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'PRIVATE_ID' is not placed at fixed offset in '%s'", util_get_obj_name(&s_seq->base));
        }
        /* check that private ID is placed at correct offset */
        else if (priv_item->offset != 2)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'PRIVATE_ID' is placed at illegal offset in '%s'", util_get_obj_name(&s_seq->base));
        }
    }
    /* checks for prefix messages */
    else if (s_seq->base.res->base.subtype == RESOURCE_ISI_PREFIX ||
             s_seq->base.res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT)
    {
        const autogen_item* res_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_RESOURCE_ID);

        if (!res_item)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'RESOURCE_ID' is not defined in '%s'", util_get_obj_name(&s_seq->base));
        }
        /* check that resource ID is placed at fixed offset */
        else if (res_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'RESOURCE_ID' is not placed at fixed offset in '%s'", util_get_obj_name(&s_seq->base));
        }
        /* check that resource ID is placed at correct offset */
        else if (res_item->offset != 2)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'RESOURCE_ID' is placed at illegal offset in '%s'", util_get_obj_name(&s_seq->base));
        }
    }
    /* if media module control resource and media is the 3rd byte in the message,
       mark the message as media module specific 
    */
    else if (s_seq->base.res->base.subtype == RESOURCE_ISI_MEDIA_CONTROL)
    {
        autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(&s_seq->base.child_list);

        /* iterate to 3rd item */
        if (item && item->base.next && item->base.next->next)
        {
            item = (autogen_item*)item->base.next->next;

            if (item && item->base.subtype == AUTOGEN_ITEM_VALUE &&
                (((autogen_item_value*)item)->pres.type & AUTOGEN_PRESENTATION_PN_CONST) &&
                (((autogen_item_value*)item)->pres.subtype == PN_MEDIA) &&
                !prop_has((autogen_obj*)s_seq, PROPERTY_MSG_IS_MEDIA_CTRL_SPECIFIC))
            {
                ((autogen_item_value*)item)->base.special_number_type = PMD_NUMBER_SPECIAL_TYPE_ACTUAL_MEDIA;
                s_seq->base.flag |= AUTOGEN_MSG_IS_MM_SPECIFIC;
            }
        }
    }

    /* end the message... */
    init_common_seq_end(line, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));

    /* restore last scope and parent */
    init_scope_restore();
}


/*  Init function for the MSG_PAIR macro */
void init_msg_pair(int line, const char* reqmsgname, const char* respmsgname, const char* resname, const char* verfrom, const char* verto)
{
    autogen_obj ver_obj = INIT_OBJECT;
    autogen_res* res = s_res;
    int found = FALSE;
    autogen_obj_list* req_msg_list = &s_res->msg_list;
    autogen_obj_list* resp_msg_list = &s_res->msg_list;


    /* set correct message list */
    if (prop_has(&s_res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        req_msg_list  = &s_res->msg_dev_dep_req_list;
        resp_msg_list = &s_res->msg_dev_dep_resp_list;
    }

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check request message name */
    check_c_name(s_file, line, "reqmsgname", reqmsgname, CHECK_NAME_EXIT_ON_FAIL);

    /* check response message name */
    check_c_name(s_file, line, "respmsgname", respmsgname, CHECK_NAME_EXIT_ON_FAIL);

    /* check resource name */
    if (resname)
    {
        check_c_name(s_file, line, "resname", resname, CHECK_NAME_EXIT_ON_FAIL);
    }

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check and set version numbers */
    init_obj_ver_set(line, s_res, &ver_obj, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    /* find proper resource */
    if (resname)
    {
        autogen_it res_it = INIT_ITERATOR;

        /* check that the resource exist */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_ISI | RESOURCE_ISI_COMMON_MESSAGES | RESOURCE_ISI_COMMON_MESSAGES_EXT | 
                             RESOURCE_ISI_MEDIA_CONTROL | RESOURCE_MEDIA_MODULE |
                             RESOURCE_PHONET | RESOURCE_PHONET_EXT;
        res_it.obj.name    = resname;

        res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        if (!res)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Undefined resource '%s'", resname);
            return;
        }
        else
        {
            req_msg_list = &res->msg_list;
        }
    }

    /* check request messages */
    {
        autogen_obj* req;
        autogen_it req_it = INIT_ITERATOR;

        req_it.typemask = AUTOGEN_OBJ_MSG;
        req_it.obj.name = reqmsgname;
        req_it.flagall  = AUTOGEN_MSG_REQ;
        req_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        req_it.ver      = &ver_obj.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            req_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            req_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        req = autogen_obj_find_in_list(&req_it, req_msg_list);
        if (req)
        {
            found = TRUE;
        }
        while (req)
        {
            autogen_obj* resp = NULL;
            autogen_it resp_it = INIT_ITERATOR;

            /* make relations to all response messages */
            resp_it.typemask = AUTOGEN_OBJ_MSG;
            resp_it.obj.name = respmsgname;
            resp_it.flagall  = AUTOGEN_MSG_RESP;
            resp_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            resp_it.ver      = &req->ver;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                resp_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                resp_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            if (g_autogen_env == AUTOGEN_ENV_LOCAL)
            {
                if (!autogen_obj_list_verify_object_span(&resp_it, resp_msg_list))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 10,
                        "The response message '%s' doesn't exist for all required versions", respmsgname);
                }
            }

            resp = autogen_obj_find_in_list(&resp_it, resp_msg_list);
            while (resp)
            {
                init_add_obj_relation(resp, req,  &ver_obj.ver, (s_env->scope ? s_env->scope->feature_flags : NULL));
                init_add_obj_relation(req,  resp, &ver_obj.ver, (s_env->scope ? s_env->scope->feature_flags : NULL));

                resp = autogen_obj_find_next_in_list(&resp_it);
            }

            req = autogen_obj_find_next_in_list(&req_it);
        }
    }

    /* if not found among messages, try submessages */
    if (!found)
    {
        autogen_seq* req;
        autogen_it req_it = INIT_ITERATOR;

        req_it.typemask = AUTOGEN_OBJ_MSG_BASE;
        req_it.flagall  = AUTOGEN_MSG_REQ;
        req_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        req_it.ver      = &ver_obj.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            req_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            req_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        req = (autogen_seq*)autogen_obj_find_in_list(&req_it, req_msg_list);
        while (req)
        {
            autogen_obj* subreq;
            autogen_it subreq_it = INIT_ITERATOR;

            subreq_it.obj.name = reqmsgname;
            subreq_it.flagall  = AUTOGEN_MSG_REQ;
            subreq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            subreq_it.ver      = &req->base.ver;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                subreq_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                subreq_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            subreq = autogen_obj_find_in_list(&subreq_it, &req->submsg_list);
            while (subreq)
            {
                autogen_seq* resp = NULL;
                autogen_it resp_it = INIT_ITERATOR;

                /* make relations to all response messages */
                resp_it.typemask = AUTOGEN_OBJ_MSG_BASE;
                resp_it.obj.name = req->base.name;
                resp_it.flagall  = AUTOGEN_MSG_RESP;
                resp_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                resp_it.ver      = &subreq->ver;
                if (s_env->scope ? s_env->scope->feature_flags : NULL)
                {
                    resp_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    resp_it.obj.feature_flags = s_env->scope->feature_flags;
                }

                resp = (autogen_seq*)autogen_obj_find_in_list(&resp_it, resp_msg_list);
                while (resp)
                {
                    autogen_obj* subresp;
                    autogen_it subresp_it = INIT_ITERATOR;

                    subresp_it.obj.name = respmsgname;
                    subresp_it.flagall  = AUTOGEN_MSG_RESP;
                    subresp_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                    subresp_it.ver      = &subreq->ver;
                    if (s_env->scope ? s_env->scope->feature_flags : NULL)
                    {
                        subresp_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                        subresp_it.obj.feature_flags = s_env->scope->feature_flags;
                    }

                    subresp = autogen_obj_find_in_list(&subresp_it, &resp->submsg_list);
                    while (subresp)
                    {
                        found = TRUE;

                        init_add_obj_relation(subresp, subreq,  &ver_obj.ver, (s_env->scope ? s_env->scope->feature_flags : NULL));
                        init_add_obj_relation(subreq,  subresp, &ver_obj.ver, (s_env->scope ? s_env->scope->feature_flags : NULL));

                        subresp = autogen_obj_find_next_in_list(&subresp_it);
                    }

                    resp = (autogen_seq*)autogen_obj_find_next_in_list(&resp_it);
                }
                
                subreq = autogen_obj_find_next_in_list(&subreq_it);
            }

            req = (autogen_seq*)autogen_obj_find_next_in_list(&req_it);
        }
    }

    /* if still not found, report an error */
    if (!found)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
            "Request message '%s' is not defined", reqmsgname);
    }
}


/*  Init function for the SUB_MSG_PAIR macro */
void init_sub_msg_pair(int line, const char* reqsubmsgname, const char* reqmsgname, const char* respsubmsgname, const char* respmsgname, const char* verfrom, const char* verto)
{
    autogen_obj ver_obj = INIT_OBJECT;
    autogen_seq* req;
    autogen_it req_it = INIT_ITERATOR;
    autogen_obj_list* req_msg_list = &s_res->msg_list;
    autogen_obj_list* resp_msg_list = &s_res->msg_list;

    /* set correct message list */
    if (prop_has(&s_res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        req_msg_list  = &s_res->msg_dev_dep_req_list;
        resp_msg_list = &s_res->msg_dev_dep_resp_list;
    }

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check request message name */
    check_c_name(s_file, line, "reqmsgname", reqmsgname, CHECK_NAME_EXIT_ON_FAIL);

    /* check request submessage name */
    check_c_name(s_file, line, "reqsubmsgname", reqsubmsgname, CHECK_NAME_EXIT_ON_FAIL);

    /* check response message name */
    check_c_name(s_file, line, "respmsgname", respmsgname, CHECK_NAME_EXIT_ON_FAIL);

    /* check response submessage name */
    check_c_name(s_file, line, "respsubmsgname", respsubmsgname, CHECK_NAME_EXIT_ON_FAIL);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check and set version numbers */
    init_obj_ver_set(line, s_res, &ver_obj, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    /* find first request base message */
    {
        req_it.typemask = AUTOGEN_OBJ_MSG_BASE;
        req_it.obj.name = reqmsgname;
        req_it.flagall  = AUTOGEN_MSG_REQ;
        req_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        req_it.ver      = &ver_obj.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            req_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            req_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        req = (autogen_seq*)autogen_obj_find_in_list(&req_it, req_msg_list);
        /* does any request exist ? */
        if (!req)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Referenced request base message '%s' doesn't exist", reqmsgname);
        }
    }

    /* For each request message, find all response messages */
    while (req)
    {
        autogen_obj* subreq;
        autogen_it subreq_it = INIT_ITERATOR;

        subreq_it.obj.name = reqsubmsgname;
        subreq_it.flagall  = AUTOGEN_MSG_REQ;
        subreq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        subreq_it.ver      = &ver_obj.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            subreq_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            subreq_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        subreq = autogen_obj_find_in_list(&subreq_it, &req->submsg_list);
        /* does any request exist ? */
        if (!subreq)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Referenced request message '%s.%s' doesn't exist", reqmsgname, reqsubmsgname);
        }

        while (subreq)
        {
            autogen_seq* resp;
            autogen_it resp_it = INIT_ITERATOR;

            /* find first response base message */
            resp_it.typemask = AUTOGEN_OBJ_MSG_BASE;
            resp_it.obj.name = respmsgname;
            resp_it.flagall  = AUTOGEN_MSG_RESP;
            resp_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            resp_it.ver      = &ver_obj.ver;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                resp_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                resp_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            resp = (autogen_seq*)autogen_obj_find_in_list(&resp_it, resp_msg_list);
            /* does any response exist ? */
            if (!resp)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Referenced response base message '%s' doesn't exist", respmsgname);
            }

            /* for each reponse base message, find all submessages */
            while (resp)
            {
                autogen_obj* subresp;
                autogen_it subresp_it = INIT_ITERATOR;

                /* make relations to all response messages */
                subresp_it.obj.name = respsubmsgname;
                subresp_it.flagall  = AUTOGEN_MSG_RESP;
                subresp_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                subresp_it.ver      = &subreq->ver;
                if (s_env->scope ? s_env->scope->feature_flags : NULL)
                {
                    subresp_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    subresp_it.obj.feature_flags = s_env->scope->feature_flags;
                }

                subresp = autogen_obj_find_in_list(&subresp_it, &resp->submsg_list);
                while (subresp)
                {
                    init_add_obj_relation(subresp, subreq,  &ver_obj.ver, (s_env->scope ? s_env->scope->feature_flags : NULL));
                    init_add_obj_relation(subreq,  subresp, &ver_obj.ver, (s_env->scope ? s_env->scope->feature_flags : NULL));

                    subresp = autogen_obj_find_next_in_list(&subresp_it);
                }

                resp = (autogen_seq*)autogen_obj_find_next_in_list(&resp_it);
            }

            /* verify that the response message is defined for all versions */
            if (g_autogen_env == AUTOGEN_ENV_LOCAL)
            {
                if (!autogen_obj_list_verify_object_span(&resp_it, resp_msg_list))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                        "The response submessage '%s.%s' doesn't exist for all required versions", respmsgname, respsubmsgname);
                }
            }

            subreq = autogen_obj_find_next_in_list(&subreq_it);
        }

        req = (autogen_seq*)autogen_obj_find_next_in_list(&req_it);
    }
}


/*  Init function for the MSG_SET_TYPE macro */
void init_msg_set_type(int line, unsigned int type)
{
    unsigned int flag = 0;


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_MSG);

    /* as this is an old macro, suggest to use the new macro */
    util_error_line(s_file, line, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
        "This macro should not be used any more");

    /* check message type and convert to internal constant */
    if (type == AUTOGEN_MSG_TYPE_REQ)
    {
        flag = AUTOGEN_MSG_REQ;
    }
    else if (type == AUTOGEN_MSG_TYPE_RESP)
    {
        flag = AUTOGEN_MSG_RESP;
    }
    else if (type == AUTOGEN_MSG_TYPE_IND)
    {
        flag = AUTOGEN_MSG_IND;
    }
    else if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
    {
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'type' is not valid");
    }

    /* update flag in message object */
    if (s_seq->base.type != AUTOGEN_OBJ_MSG_BASE)
    {
        s_seq->base.flag &= ~(AUTOGEN_MSG_REQ | AUTOGEN_MSG_RESP | AUTOGEN_MSG_IND | AUTOGEN_MSG_NTF);
    }

    s_seq->base.flag |= flag;
}


/*  Init function for the SB_LST_BEGIN macro 
*/

void init_sb_lst_begin(int line, unsigned int type, const char* varname, const char* name, unsigned int n, const char* nstr, const char* refname, unsigned int flag)
{
    unsigned int item_flag = 0;
    autogen_agg_type agg_type = AGG_TYPE_UNKNOWN;
    const char* agg_n_str = NULL;
    const char* agg_refname = NULL;
    char* parname = pmd_heap_strdup(name);


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_CASE);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* --------------------------------------------------------------------- */
    /* checks for SB_LST_BEGIN */
    /* --------------------------------------------------------------------- */
    if (!refname)
    {
        /* check number of elements string */
        check_string(s_file, line, "n", nstr, CHECK_NAME_EXIT_ON_FAIL);

        /* check the number of elements */
        if (n == 0 || n > 65535)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'n' is out of range. Value must be between 1 and 65535");
        }
        else if (n > 1)
        {
            agg_type  = AGG_TYPE_FIXED_MULTIPLE;
            agg_n_str = nstr;

            /* add the constant (or merge with existing constants) */
            init_constant_add(line, nstr, n, AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_env->scope->parent->ver, (s_env->scope ? s_env->scope->feature_flags : NULL));
        }
        else
        {
            agg_type  = AGG_TYPE_FIXED_SINGLE;
            agg_n_str = nstr;
        }
    }
    /* --------------------------------------------------------------------- */
    /* checks for SB_LST_REF_BEGIN */
    /* --------------------------------------------------------------------- */
    else
    {
        /* check reference name */
        check_c_name(s_file, line, "refname", refname, CHECK_NAME_EXIT_ON_FAIL);

        /* set aggregation type */
        /* allow predefined reference name REF_AS_MANY_AS_POSSIBLE to be used */
        if (!strcmp(refname, "REF_AS_MANY_AS_POSSIBLE"))
        {
            agg_type    = AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE;
        }
        else if (!strcmp(refname, "REF_OPTIONAL"))
        {
            agg_type    = AGG_TYPE_DYNAMIC_OPTIONAL;
        }
        else
        {
            agg_type    = AGG_TYPE_DYNAMIC_REF;
            agg_refname = refname;
        }
    }

    /* check list type string and convert to internal constant */
    if (type == LIST_OF_SUBBLOCKS)
    {
        item_flag |= AUTOGEN_LST_SBDATA;
    }
    else if (type == LIST_OF_SUBBLOCK_IDS)
    {
        item_flag |= AUTOGEN_LST_SBID;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'type' is not valid");
    }

    /* check array flag */
    if (flag == ISIHDR_MARKER_ANYSIZE ||
        flag == ISIHDR_MARKER_ANYSIZE_BYTE ||
        flag == ISIHDR_MARKER_ANYSIZE_WORD ||
        flag == ISIHDR_MARKER_SINGLE_ELEMENT ||
        flag == ISIHDR_MARKER_SINGLE_ELEMENT_BYTE ||
        flag == ISIHDR_RESERVE_SPACE ||
        flag == ISIHDR_MARKER_UNION ||
        flag == ISIHDR_POINTER ||
        flag == ISIHDR_POINTER_VOID ||
        flag == ISIHDR_MARKER_POINTER)
    {
    }
    else if (flag == ISIHDR_DONT_GENERATE)
    {
        item_flag |= AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'flag' is not valid");

        flag = ISIHDR_MARKER_ANYSIZE;
    }

    /* create and initialize item object */
    s_lst = (autogen_item*)init_item_create(line, sizeof(autogen_item), AUTOGEN_ITEM_LST, item_flag, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    autogen_obj_list_init(&s_lst->base.child_list, &s_lst->base, AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 10);

    /* copy version */
    memcpy(&s_lst->base.ver, &s_seq->base.ver, sizeof(autogen_ver));

    s_lst->seq = s_seq;

    s_lst->agg_type  = agg_type;
    s_lst->agg_n     = n;
    s_lst->agg_n_str = agg_n_str;

    if (agg_type == AGG_TYPE_DYNAMIC_REF)
    {
        s_lst->refname = agg_refname;
        reference_use_counter(s_lst, (s_env->scope ? s_env->scope->feature_flags : NULL));
    }
    /* Indicate device endianess */
#if ((defined AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE) &&(PMD_FILE_FORMAT >= 501))
    s_lst->order = AUTOGEN_DEVICE_ENDIANESS;
#endif

    /* check that the flag ISIHDR_RESERVE_SPACE is used correctly */
    if (flag == ISIHDR_RESERVE_SPACE)
    {
        if (item_flag & AUTOGEN_LST_SBDATA) 
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'flag' is not valid in this context");

            flag = ISIHDR_MARKER_ANYSIZE;
        }
        if (agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'flag' is not valid in this context");

            flag = ISIHDR_MARKER_ANYSIZE;
        }
    }

    /* add the property */
    prop_add_value_to_object((autogen_obj*)s_lst, PROPERTY_ISIHDR_ARRAY_MARKER, flag, FALSE, "", "", 0, FALSE);

    /* add item object to sequence object */
    init_item_add(s_lst, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* set new scope and parent */
    init_scope_set(SCOPE_SB_LST, &s_lst->base);
}


/*  Init function for the SB_LST_END macro 
*/
void init_sb_lst_end(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_SB_LST);

    /* check if the list is empty */
    if (s_lst->base.child_list.n_obj == 0 && !(s_lst->base.flag & AUTOGEN_LST_FTD) && !(s_lst->base.flag & AUTOGEN_LST_PPC) && !(s_lst->base.flag & AUTOGEN_LST_SOS_FTD))
    {
        /* produce an error if the list is empty for a fixed number of subblocks */
        if (s_lst->agg_type == AGG_TYPE_FIXED_SINGLE || s_lst->agg_type == AGG_TYPE_FIXED_MULTIPLE)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "The sub lock list is empty. It must contain at least one element");
        }
    }

    /* add item relations */
    init_item_add_relations(s_lst, &s_seq->base.ver, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));

    /* empty properties and comments */
    init_clear_properties_comments(line);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    {
        unsigned int flag = (unsigned int)prop_get_value_default((autogen_obj*)s_lst, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_DONT_GENERATE);

        if (flag == ISIHDR_MARKER_ANYSIZE ||
            flag == ISIHDR_MARKER_ANYSIZE_BYTE ||
            flag == ISIHDR_MARKER_ANYSIZE_WORD)
        {
            s_seq->base.flag |= AUTOGEN_SEQ_IS_DYNAMIC;
        }
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* restore last scope and parent */
    init_scope_restore();

    s_lst = NULL;
}


/*  Init function for the SEQ_BEGIN macro 
    Requirement 
*/
void init_seq_begin(int line, const char* name, unsigned int flag, const char* verfrom, const char* verto, const char* cmt)
    {
    unsigned int seq_flag = 0;
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    cmt;
#endif

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check sequence name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);
    
    /* convert flag from string to value */
    if (flag == CREATE_STRUCT)
        {
        }
    else if (flag == DONT_CREATE_STRUCT)
        {
        seq_flag |= AUTOGEN_SEQ_IS_NOT_STRUCT;
        }
    else
        {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'flag' is not valid");
        }

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);


    /* create seq object */
    init_common_seq_create(line, AUTOGEN_OBJ_SEQ, 0, 0, seq_flag, name, verfrom, verto, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* Check for identically named sequences in shared files, must have AUTOGEN_SEQ_IS_NOT_STRUCT */
#if (!(defined AUTOGEN_ENVIRONMENT_LOCAL) || defined AUTOGEN_DISABLE_TOUGH_CHECKS)
    {
        autogen_it seq_it = INIT_ITERATOR;
        autogen_obj* temp = NULL;

        seq_it.typemask   = AUTOGEN_OBJ_SEQ;
        seq_it.obj.name   = name;
        seq_it.flagall    = AUTOGEN_OBJ_IS_SHARED | AUTOGEN_SEQ_IS_NOT_STRUCT;
        seq_it.vercrit    = AUTOGEN_OBJ_VERSION_OVERLAP;
        seq_it.ver        = &s_seq->base.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            seq_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            seq_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        temp = autogen_obj_find_in_list(&seq_it, &s_res->seq_list);
        if (temp)
        {
            autogen_obj_ver_merge(&temp->ver, &s_seq->base.ver, &temp->ver);
            s_seq->base.flag |= AUTOGEN_SEQ_IS_TEMPORARY;
        }
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    if (!(s_seq->base.flag & AUTOGEN_SEQ_IS_TEMPORARY)) /* only perform check if sequence is not duplicated in shared */
    {
        /* check that the sequence name does not conflict with any subblocks */
        {
        autogen_it sb_it = INIT_ITERATOR;

        sb_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB_TEMPLATE;
        sb_it.obj.name = name;
        sb_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        sb_it.ver      = &s_seq->base.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            sb_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            sb_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        if (autogen_obj_find_in_list(&sb_it, &s_res->seq_list))
            {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Sequence '%s' conflicts with a %s with the same name",
                name, util_get_obj_type_name((autogen_obj*)s_seq));
            }
        }
    }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* add comment */
    if (cmt && cmt[0])
        {
        autogen_cmt_add(&s_seq->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
        }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* set new scope and parent */
    init_scope_set(SCOPE_SEQ, &s_seq->base);
    }


/*  Init function for the SEQ_END macro 
*/
void init_seq_end(int line)
{
    const autogen_item* id_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID);
    const autogen_item* length_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_SEQ);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* Check for recursive structure */
    check_seq_recursion(s_file, s_seq, s_res, &s_seq->base.ver);
#endif

    if (!(s_seq->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
    {
        unsigned int offset      = 0;
        unsigned int offset_type = AUTOGEN_ITEM_OFFSET_EXACT;

        /* set item offsets */
        init_update_item_offsets(&s_seq->base.child_list, &s_seq->base.ver, &offset_type, &offset);
    }

    /* is the sequence a subblock template? */
    if (id_item || length_item)
    {
        /* report error if not both references are defined */
        if (!id_item)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'SB_LENGTH' is defined in the subblock template '%s', but 'SB_ID' is not",
                util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
        else if (!length_item)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'SB_ID' is defined in the subblock template '%s', but 'SB_LENGTH' is not",
                util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
        /* check ID offset */
        else if (id_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT || id_item->offset != 0)
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'SB_ID' is not the first item in '%s'",
                util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
        /* check length offset */
        else if (length_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'SB_LENGTH' is not placed at a fixed offset in '%s'",
                util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }


        /* report error if the sequence is not a structure */
        if (s_seq->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Subblock template is not defined as a structure, which it should be");
        }

        /* if sequence is a sub bloc template, replace the object type */
        s_seq->base.type = AUTOGEN_OBJ_SB_TEMPLATE;

        /* check subblock template name / resource relation */
#if ((defined AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN) || (defined AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES))
        if (!strcmp(s_seq->base.name, "SOS_FTD_DATA_BYTE") ||
            !strcmp(s_seq->base.name, "SOS_FTD_DATA_WORD") ||
            !strcmp(s_seq->base.name, "SOS_FTD_DATA_DWORD") ||
            !strcmp(s_seq->base.name, "SOS_FTD_DATA_STRING") ||
            !strcmp(s_seq->base.name, "SOS_FTD_DATA_BYTEARRAY"))
        {
            s_seq->base.subtype = AUTOGEN_SB_TEMPLATE_SOS;
        }
        else 
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN */
        if (!strcmp(s_seq->base.name, "COMM_FTD_DATA_BYTE") ||
            !strcmp(s_seq->base.name, "COMM_FTD_DATA_WORD") ||
            !strcmp(s_seq->base.name, "COMM_FTD_DATA_DWORD") ||
            !strcmp(s_seq->base.name, "COMM_FTD_DATA_STRING") ||
            !strcmp(s_seq->base.name, "COMM_FTD_DATA_TABLE"))
        {
            s_seq->base.subtype = AUTOGEN_SB_TEMPLATE_FTD;
        }
        else if (!strcmp(s_seq->base.name, "MON_PPC_BYTE") ||
                 !strcmp(s_seq->base.name, "MON_PPC_WORD") ||
                 !strcmp(s_seq->base.name, "MON_PPC_DWORD") ||
                 !strcmp(s_seq->base.name, "MON_PPC_TABLE_BYTE") ||
                 !strcmp(s_seq->base.name, "MON_PPC_TABLE_WORD") ||
                 !strcmp(s_seq->base.name, "MON_PPC_TABLE_DWORD"))
        {
            s_seq->base.subtype = AUTOGEN_SB_TEMPLATE_PPC;
        }
        else
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Subblock template is not supported");
        }
    }

    if (!(s_seq->base.flag & AUTOGEN_SEQ_IS_TEMPORARY) )/* only insert sequence if it is not already inserted from shared */
    {
        /* add sequence object to server */
        autogen_obj_list_add_obj(&s_seq->base.res->seq_list, &s_seq->base, AUTOGEN_ENV_LOCAL);
    }

    /* end the sequence... */
    init_common_seq_end(line, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));

    /* restore last scope and parent */
    init_scope_restore();
}


/*  Init function for the SUB_MSG_BEGIN macro 
*/
void init_sub_msg_begin(int line, unsigned int submsgid, const char* submsgname, unsigned int msgid, const char* msgname, 
    unsigned int type, const char* verfrom, const char* verto, const char* cmt)
{
    autogen_it base_msg_it = INIT_ITERATOR;
    autogen_seq* base_msg = NULL;
    autogen_obj_list* base_msg_list = NULL;
    unsigned int flag = AUTOGEN_MSG_IS_SUBMSG;
    int add_base_msg = FALSE;
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    cmt;
#endif

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check submessage name */
    check_c_name(s_file, line, "submsgname", submsgname, CHECK_NAME_EXIT_ON_FAIL);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* check message name */
    check_c_name(s_file, line, "msgname", msgname, CHECK_NAME_EXIT_ON_FAIL);

    /* default, don't generate in PMD for public/restricted PMD types */
    if (prop_has(NULL, PROPERTY_PMD_PUBLIC))
    {
        s_res->base.flag |= AUTOGEN_OBJ_IS_PMD_PUBLIC | AUTOGEN_OBJ_IS_PMD_RESTRICTED;
        flag |= (AUTOGEN_OBJ_IS_PMD_PUBLIC | AUTOGEN_OBJ_IS_PMD_RESTRICTED);
    }
    if (prop_has(NULL, PROPERTY_PMD_RESTRICTED))
    {
        s_res->base.flag |= AUTOGEN_OBJ_IS_PMD_RESTRICTED;
        flag |= AUTOGEN_OBJ_IS_PMD_RESTRICTED;
    }

    /* check message type and convert to internal constant */
    if (type == MESSAGE_UNKNOWN)
    {
        if (strstr(msgname, "_REQ") || strstr(submsgname, "_REQ"))
        {
            flag |= AUTOGEN_MSG_REQ;
        }
        else if (strstr(msgname, "_RESP") || strstr(submsgname, "_RESP"))
        {
            flag |= AUTOGEN_MSG_RESP;
        }
        else if (strstr(msgname, "_IND") || strstr(submsgname, "_IND"))
        {
            flag |= AUTOGEN_MSG_IND;
        }
        else if (strstr(msgname, "_NTF") || strstr(submsgname, "_NTF"))
        {
            flag |= AUTOGEN_MSG_NTF;
        }
        else
        {
            flag |= AUTOGEN_MSG_REQ;
        }
    }
    else if (type == MESSAGE_REQ)
    {
        flag |= AUTOGEN_MSG_REQ;
    }
    else if (type == MESSAGE_RESP)
    {
        flag |= AUTOGEN_MSG_RESP;
    }
    else if (type == MESSAGE_IND)
    {
        flag |= AUTOGEN_MSG_IND;
    }
    else if (type == MESSAGE_NTF)
    {
        flag |= AUTOGEN_MSG_NTF;
    }
    else if (type == MESSAGE_TRACE)
    {
        flag |= AUTOGEN_MSG_TRC;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'type' is not valid");
    }

    /* Find base message. Create new, if it doesn't exist */
    base_msg_it.typemask    = AUTOGEN_OBJ_MSG_BASE | AUTOGEN_OBJ_MSG;
    base_msg_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
    base_msg_it.obj.id      = msgid;
    base_msg_it.obj.name    = msgname;
    if (s_env->scope ? s_env->scope->feature_flags : NULL)
    {
        base_msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
        base_msg_it.obj.feature_flags = s_env->scope->feature_flags;
    }

    base_msg_list = &s_res->msg_list;
    if (prop_has(&s_res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        if (flag & AUTOGEN_MSG_REQ)
        {
            base_msg_list = &s_res->msg_dev_dep_req_list;
        }
        else
        {
            base_msg_list = &s_res->msg_dev_dep_resp_list;
        }
    }

    base_msg = (autogen_seq*)autogen_obj_find_in_list(&base_msg_it, base_msg_list);
    if (!base_msg)
    {
        base_msg = (autogen_seq*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_seq), AUTOGEN_OBJ_MSG_BASE, 0, msgid, msgname, (s_env->scope ? s_env->scope->feature_flags : NULL));

        base_msg->base.flag = AUTOGEN_SEQ_IS_NOT_STRUCT | AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR | AUTOGEN_MSG_BASE_IS_AUTO_DEFINED |
                    (flag & (AUTOGEN_OBJ_IS_PMD_PUBLIC | AUTOGEN_OBJ_IS_PMD_RESTRICTED | AUTOGEN_MSG_FUNCTION_MASK));

        autogen_obj_list_init(&base_msg->submsg_list, &base_msg->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);

        add_base_msg = TRUE;
    }
#if (defined AUTOGEN_ENVIRONMENT_LOCAL && !defined AUTOGEN_DISABLE_TOUGH_CHECKS)
    else if (base_msg->base.type != AUTOGEN_OBJ_MSG_BASE)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Message ID 0x%2.2X used in ordinary message and as base for submessage %s", msgid, submsgname);
    }
#endif
    else
    {
        base_msg->base.flag |= (flag & (AUTOGEN_MSG_FUNCTION_MASK | AUTOGEN_OBJ_IS_PMD_PUBLIC | AUTOGEN_OBJ_IS_PMD_RESTRICTED));
    }

    /* Verify that msgid is within legal range */
    if (s_res->base.subtype & (RESOURCE_ISI_ANY | RESOURCE_MEDIA_MODULE | RESOURCE_MEDIA_MODULE_EXTENSION))
    {
        /* check if id is valid */
        if (msgid > 0xFF)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'msgid' is out of range. Value must be between 0x00 and 0xFF");
        }

        /* check if msgid is < 0xF0 for ISI messages */
        if (s_res->base.subtype == RESOURCE_ISI || 
            s_res->base.subtype == RESOURCE_ISI_EXTENSION || 
            s_res->base.subtype == RESOURCE_ISI_PRIVATE || 
            s_res->base.subtype == RESOURCE_ISI_PREFIX)
        {
            autogen_res* base_res = util_get_base_res(s_res);
            if (!base_res) base_res = s_res;

            if ((base_res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES) && msgid >= 0xF0)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                    "Argument 'msgid' is out of range. Value >= 0xF0 are reserved for common messages");
            }
        }
    }
    /* create and initialize message object */
    init_common_seq_create(line, AUTOGEN_OBJ_MSG, 0, submsgid, flag, submsgname, verfrom, verto, (s_env->scope ? s_env->scope->feature_flags : NULL));
    s_seq->base.parent   = &base_msg->base;
    s_seq->base.base_obj = &base_msg->base;

    /* for resource extension, check if id is conflicting */
    if (s_res->base.subtype == RESOURCE_PROTOCOL_EXTENSION ||
        s_res->base.subtype == RESOURCE_ISI_EXTENSION)
    {
        autogen_res* base_res = util_get_base_res(s_res);
        if (base_res && base_res != s_res)
        {
            autogen_it msg_it = INIT_ITERATOR;

            /* find conflicting message */
            msg_it.typemask    = AUTOGEN_OBJ_MSG;
            msg_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
            msg_it.obj.id      = msgid;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                msg_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                msg_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            if (autogen_obj_find_in_list(&msg_it, &base_res->msg_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Message ID is defined in both resource extension and base resource");
                return; /* To avoid lint warnings */
            }
        }
    }

    /* add base message to resource */
    if (add_base_msg)
    {
        memcpy(&base_msg->base.ver, &s_seq->base.ver, sizeof(autogen_ver));

        autogen_obj_list_add_obj(base_msg_list, &base_msg->base, AUTOGEN_ENV_ALL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        /* verify that definition is not already defined */
        init_add_def(line, AUTOGEN_DEF_CONST, base_msg->base.name, base_msg->base.id, AUTOGEN_CONST_UNSIGNED_BYTE, 
            &base_msg->base.ver, NULL, NULL, (s_env->scope ? s_env->scope->feature_flags : NULL));
#endif
    }
    else
    {
        autogen_obj_ver_merge(&base_msg->base.ver, &s_seq->base.ver, &base_msg->base.ver);
    }

    /* add message object to server */
    autogen_obj_list_add_obj(&base_msg->submsg_list, &s_seq->base, AUTOGEN_ENV_LOCAL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* add comment */
    if (cmt && cmt[0])
    {
        autogen_cmt_add(&s_seq->base.cmt_list, 
            autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, cmt));
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* set new scope and parent */
    init_scope_set(SCOPE_SUB_MSG, &s_seq->base);
}


/*  Init function for the SUB_MSG_END macro 
*/
void init_sub_msg_end(int line)
{
    unsigned int offset      = 0;
    unsigned int offset_type = AUTOGEN_ITEM_OFFSET_EXACT;

    autogen_item* id_item     = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID);
    autogen_item* sub_id_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID);
    autogen_item* length_item = reference_get_special_item(&s_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH);
   
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_SUB_MSG);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* Check for recursive structure */
    check_seq_recursion(s_file, s_seq, s_res, &s_seq->base.ver);
#endif

    /* set item offsets */
    init_update_item_offsets(&s_seq->base.child_list, &s_seq->base.ver, &offset_type, &offset);

    /* check that message ID is defined */
    if (s_res->msg_id_offset != AUTOGEN_NOT_SUPPORTED)
    {
        if (!id_item)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'MSG_ID' is not defined in '%s'", util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
        else
        {
            /* if message ID offset varies with resource type, make sure it is set on the resource */
            if (s_res->msg_id_offset == AUTOGEN_VALUE_VARIES)
            {
                s_res->msg_id_offset = (int)id_item->offset;
            }
            /* check that message ID offset is fixed */
            if (id_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'MSG_ID' is not placed at fixed offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
            /* check that offset is correct according to resource rules */
            else if (id_item->offset != (unsigned int)s_res->msg_id_offset)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'MSG_ID' is placed at illegal offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
            /* check message ID value */
            else if (id_item->length == 8  && s_seq->base.id > 0xFF || 
                     id_item->length == 16 && s_seq->base.id > 0xFFFF)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Message ID in '%s' is out of range", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
        }
    }

    /* check that submessage ID is defined */
    if (s_res->submsg_id_offset != AUTOGEN_NOT_SUPPORTED)
    {
        if (!sub_id_item)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference 'SUB_MSG_ID' is not defined in '%s'", util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
        else
        {
            /* if submessage ID offset varies with resource type, make sure it is set on the resource */
            if (s_res->submsg_id_offset == AUTOGEN_VALUE_VARIES)
            {
                s_res->submsg_id_offset = (int)sub_id_item->offset;
            }
            /* check that submessage ID offset is fixed */
            if (sub_id_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'SUB_MSG_ID' is not placed at fixed offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
            /* check that offset is correct according to resource rules */
            else if (sub_id_item->offset != (unsigned int)s_res->submsg_id_offset)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'SUB_MSG_ID' is placed at illegal offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
            /* check submessage ID value */
            if (sub_id_item->length == 8  && s_seq->base.id > 0xFF || 
                sub_id_item->length == 16 && s_seq->base.id > 0xFFFF)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Submessage ID in '%s' is out of range",
                    util_get_obj_name((autogen_obj*) s_seq));
            }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
            /* verify that submessage ID is not already defined */
            init_add_def(line, AUTOGEN_DEF_CONST, s_seq->base.name, s_seq->base.id, 
                sub_id_item->length == 16 ? AUTOGEN_CONST_UNSIGNED_WORD : AUTOGEN_CONST_UNSIGNED_BYTE, &s_seq->base.ver, NULL, NULL, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));
#endif
        }
    }

    /* checks for message length fields */
    if (s_res->msg_length_offset != AUTOGEN_NOT_SUPPORTED)
    {
        if (length_item)
        {
            /* if message length offset varies with resource type, make sure it is set on the resource */
            if (s_res->msg_length_offset == AUTOGEN_VALUE_VARIES)
            {
                s_res->msg_length_offset = (int)length_item->offset;
            }
            /* check that message length is placed at fixed offset */
            if (length_item->offset_type != AUTOGEN_ITEM_OFFSET_EXACT)
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'MSG_LENGTH' is not placed at a fixed offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
            /* check that offset is correct according to resource rules */
            else if (length_item->offset != (unsigned int)s_res->msg_length_offset)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference 'MSG_ID' is placed at illegal offset in '%s'", util_get_obj_name(&s_seq->base));
                return; /* To avoid lint warnings */
            }
        }
    }

    /* For base object,
       - ID fields are not defined, copy from this message
       - ID fields are defined, check that there is no conflict in length / offset
    */
    {
        autogen_seq* base_msg = (autogen_seq*)s_seq->base.base_obj;

        autogen_item* base_msg_id_item     = reference_get_special_item(&base_msg->ref_handle, PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID);
        autogen_item* base_msg_sub_id_item = reference_get_special_item(&base_msg->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID);

        if (!base_msg_id_item)
        {
            reference_add_counter(&base_msg->ref_handle, id_item, id_item->base.name, id_item->length, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL)); 

            base_msg_id_item = id_item;
        }
        else if (base_msg_id_item->length != id_item->length || base_msg_id_item->offset != id_item->offset)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Message ID field in '%s' is not consistent with other submessages",
                util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }

        if (!base_msg_sub_id_item)
        {
            reference_add_counter(&base_msg->ref_handle, sub_id_item, sub_id_item->base.name, sub_id_item->length, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL)); 

            base_msg_sub_id_item = sub_id_item;
        }
        else if (base_msg_sub_id_item->length != sub_id_item->length || base_msg_sub_id_item->offset != sub_id_item->offset)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Submessage ID in '%s' is not consistent with other submessages",
                util_get_obj_name(&s_seq->base));
            return; /* To avoid lint warnings */
        }
    }

    /* end the submessage... */
    init_common_seq_end(line, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));

    /* restore last scope and parent */
    init_scope_restore();
}


/*  Init function for the FILLER macro */
void init_filler(int line, unsigned int type, unsigned int length)
{
    autogen_item* filler;
    autogen_agg_type agg_type = AGG_TYPE_UNKNOWN;
    unsigned int flag = AUTOGEN_FILLER_VAR_AUTONAME;
    unsigned int n = 1;
    char str_n[20] = "";


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE | SCOPE_FTD_TBL_ENTRY | SCOPE_PRINTF);

    /* check filler type and convert to internal constant */
    if (type == FILLER_FIXED)
    {
    }
    else if (type == FILLER_VARIABLE)
    {
        agg_type = AGG_TYPE_DYNAMIC_ALIGNMENT;
        flag    |= AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;
    }
    /* invalid filler type */
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'type' is not valid");
    }

#if (PMD_FILE_FORMAT >= 600)
    init_check_64_bit_alignment_prop(line, length);
#endif

    if (s_env->scope->scope == SCOPE_MERGE)
    {
        /* filler type must be fixed */
        if (agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'type' is not valid in this context. "
                "Value must be 'FILLER_FIXED', when placed in a merged field");
        }
        else
        {
            agg_type = AGG_TYPE_FIXED_SINGLE;
        }
#if (PMD_FILE_FORMAT >= 600)
        /* filler size must be between 1 and 63 */
        if (length == 0 || length > 63)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. "
                "Value must be between 1 and 63, when placed in a merged field");
        }
#else
        /* filler size must be between 1 and 31 */
        if (length == 0 || length > 31)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. "
                "Value must be between 1 and 31, when placed in a merged field");
        }
#endif
    }
    else
    {
#if (PMD_FILE_FORMAT >= 600)
        /* dynamic fillers must specify a 16, 32, or 64 bit boundary */
        if (agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT && length != 64 && length != 32 && length != 24 && length != 16)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'length' is out of range. "
                "Value must be 16, 24, 32, or 64 when 'type' is 'FILLER_VARIABLE'");

            /* default length for product environment */
            if (prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_64_BITS))
            {
                length = 64;
            }
            else
            {
                length = 32;
            }
        }
#else
        /* dynamic fillers must specify a 16 or 32 bit boundary */
        if (agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT && length != 32 && length != 24 && length != 16)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'length' is out of range. "
                "Value must be 16, 24 or 32, when 'type' is 'FILLER_VARIABLE'");

            /* default length for product environment */
            length = 32;
        }
#endif

#if (PMD_FILE_FORMAT >= 600)
        /* fixed fillers must be of size 8, 16, 24, 32, 40, 48, 56, or 64 */
        if (agg_type != AGG_TYPE_DYNAMIC_ALIGNMENT && length != 8 && length != 16 && length != 24 && length != 32 && length != 40 && length != 48 && length != 56 && length != 64)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'length' is out of range. "
                "Value must be 8, 16, 24, 32, or 64 when 'type' is 'FILLER_FIXED'");

            /* default length for product environment */
            length = 8;
        }
#else
        /* fixed fillers must be of size 8, 16, 24 or 32 */
        if (agg_type != AGG_TYPE_DYNAMIC_ALIGNMENT && length != 8 && length != 16 && length != 24 && length != 32)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'length' is out of range. "
                "Value must be 8, 16, 24 or 32, when 'type' is 'FILLER_FIXED'");

            /* default length for product environment */
            length = 8;
        }
#endif

        if (agg_type != AGG_TYPE_DYNAMIC_ALIGNMENT)
        {
            n      = length / 8;
            length = 8;
        }
    }

    if (s_env->scope->scope != SCOPE_MERGE)
    {
        /* if agg_type is not set, do it */
        if (agg_type == 0)
        {
            if (n == 1)
            {
                agg_type = AGG_TYPE_FIXED_SINGLE;
            }
            else
            {
                agg_type = AGG_TYPE_FIXED_MULTIPLE;
            }
        }
    }

    /* create and initialize filler object */
    filler = init_item_create(line, sizeof(autogen_item), AUTOGEN_ITEM_FILLER, flag, (agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT) ? "" : "auto", "Filler", (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&filler->base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    filler->length = length;
    filler->order  = AUTOGEN_ORDER_BE;

    sprintf(str_n, "%lu", n);

    filler->agg_n     = n;
    filler->agg_n_str = pmd_heap_strdup(str_n);
    filler->agg_type  = agg_type;

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += n*abs(length); 
    }
    else if (s_env->scope->scope == SCOPE_FTD_TBL_ENTRY)
    {
        s_env->ftd_length_sum += n*abs(length);
    }

    /* add item object to sequence object */
    init_item_add(filler, (s_env->scope ? s_env->scope->feature_flags : NULL));
}


/*  Init function for the FILLER_EX macro */
void init_filler_ex(int line, const char* varname, unsigned int length, unsigned int n)
{
    autogen_item* filler;
    autogen_agg_type agg_type = AGG_TYPE_UNKNOWN;
    char str_n[20] = "";


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_TRACE | SCOPE_CASE | SCOPE_FTD_TBL_ENTRY);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* n must be between 1 and 65535 */
    if (n < 1 || n > 65535)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'n' is out of range. Value must be between 1 and 65535");
    }

    /* fixed fillers must be of size 8, 16, 24 or 32 */
    if (length != 8 && length != 16 && length != 24 && length != 32)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is out of range. Value must be 8, 16, 24 or 32");
    }

    /* when n > 1, the size of the filler must be 8, 16 or 32 */
    if (n != 1 && length != 8 && length != 16 && length != 32)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is out of range. Value must be 8, 16 or 32, when 'n' is not 1");
    }

    if (s_env->scope->scope != SCOPE_MERGE)
    {
        /* if agg_type is not set, do it */
        if (agg_type == 0)
        {
            if (n == 1)
            {
                agg_type = AGG_TYPE_FIXED_SINGLE;
            }
            else
            {
                agg_type = AGG_TYPE_FIXED_MULTIPLE;
            }
        }
    }

    /* create and initialize filler object */
    filler = init_item_create(line, sizeof(autogen_item), AUTOGEN_ITEM_FILLER, 0, varname, "Filler", (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&filler->base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    filler->length = length;
    filler->order  = AUTOGEN_ORDER_BE;

    sprintf(str_n, "%lu", n);

    filler->agg_n     = n;
    filler->agg_n_str = pmd_heap_strdup(str_n);
    filler->agg_type  = agg_type;

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += abs(length); 
    }
    else if (s_env->scope->scope == SCOPE_FTD_TBL_ENTRY)
    {
        s_env->ftd_length_sum += abs(length);
    }


    /* add item object to sequence object */
    init_item_add(filler, (s_env->scope ? s_env->scope->feature_flags : NULL));
}

/*  Init function for the ISI_BEGIN macro */
void init_isi_begin()
{
    int n;

    s_env = (generation_env*)pmd_heap_alloc(sizeof(generation_env));

    for (n = 0; n < AUTOGEN_OBJ_TRACEGRP_MAX; n++)
    {
        s_trcgrp_id[n] = 0;
        s_trc_id[n]    = 0;
    }

    /* set new scope */
    init_scope_set(SCOPE_ISI, NULL);

    /* Initialize reference library */
    reference_init();

    printf("Analyzing message definitions...\n\n");
}


/*  Init function for the ISI_END macro 
*/
void init_isi_end()
{
    /* check if macro is allowed in the current scope */
    if (s_env->scope->scope != SCOPE_ISI)
    {
        util_error_line(s_file_last, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "A RES_END macro is needed");
    }

    /* Create master trace resource, if it doesn't exist */
#ifdef AUTOGEN_INCLUDE_MASTER_TRACES
 #define MASTER_TRACE 0x00
    {
        autogen_it res_it = INIT_ITERATOR;

        res_it.typemask     = AUTOGEN_OBJ_RES;
        res_it.subtypemask  = RESOURCE_TRC_MASTER;
        res_it.obj.id       = 0x00; /* MCU master */

        if (!autogen_obj_find_in_list(&res_it, g_res_list))
        {
            printf(" ------------------------------------------------------\n");
            printf(" Master traces\n");
            printf(" ------------------------------------------------------\n");

            PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "mcu")
            PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_HOST)
            PROPERTY(PROPERTY_PMD_PUBLIC)
            RES_BEGIN(RESOURCE_TRC_MASTER, MASTER_TRACE, MASTER, "Trace masters", "", FALSE)
            RES_END
        }
    }
#endif /* AUTOGEN_INCLUDE_MASTER_TRACES */

    /* restore last scope and parent */
    init_scope_restore();
     
    init_post_processing();

    printf("\n");
}

/*  Init function for the TRACE_BEGIN macro */
void init_trace_begin(int line, const char* name, unsigned int id, const char* dectext, const char* grp, int has_scope, const char* macro)
{
    unsigned int flags = 0;
    char* dectext_copy = NULL;
    unsigned int trc_type = util_get_tracegroup_type(s_res);
    autogen_obj_list* trc_list = NULL;
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long trc_grp_id = 0;
#else
    unsigned int trc_grp_id = 0;
#endif
    const char* trc_grp_name = "";
    unsigned int scope = SCOPE_UNDEFINED;
    const char* trc_grp_info = "";

    if (trc_type == 0)
    {
        util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, "Trace type is not defined for trace '%s'", name);
    }

    /* settings, to differ from group concepts (like MCU) to trace concepts (like CDMA DSP) */
    if (g_trcgrp_conf[trc_type].has_groups)
    {
        if (s_trcgrp)
        {
            char* new_info = pmd_heap_alloc(strlen(s_trcgrp->base.name) + 20);

            trc_list = &s_trcgrp->base.child_list;

            trc_grp_id   = s_trcgrp->base.id;
            trc_grp_name = s_trcgrp->base.name;

            scope = SCOPE_TRACE_ID_TBL;

            sprintf(new_info, " in trace group '%s'", trc_grp_name);
            trc_grp_info = new_info;
        }
        else
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Trace '%s' is defined outside trace group", name);
        }
    }
    else
    {
        trc_list = s_res->trcgrp_list;

        scope = SCOPE_RES;

        dectext = name;
    }

    if (dectext)
    {
        dectext_copy = (char*)pmd_heap_alloc(strlen(dectext) + 10);
        strcpy(dectext_copy, dectext);
    }

    /* check if macro is allowed in the current scope */
    init_check_scope_macro(line, scope, macro);

    /* check trace name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check decode text */
    if (has_scope)
    {
        check_string(s_file, line, "dectext", dectext, CHECK_NAME_EXIT_ON_FAIL);
    }

    /* Set and check trace ID */
    if (id != AUTOGEN_TRACE_ID_UNDEFINED)
    {
        if (id > 0xFFFF)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' is out of range");
        }

        s_trc_id[trc_type] = id;
    }

    /* Check that trace group is the same as in current table */
    if (id != AUTOGEN_TRACE_ID_UNDEFINED)
    {
        char str_grp[256];
/* TODO: change this?? */
        if (trc_type == AUTOGEN_OBJ_TRACEGRP_MCU)
        {
            sprintf(str_grp, "MON_%s_GRP", trc_grp_name);
        }
        else if (grp)
        {
            strcpy(str_grp, grp);
        }
        else
        {
            strcpy(str_grp, trc_grp_name);
        }
    }

    /* check that trace decoding text is not reused in table */
    if (dectext_copy && dectext_copy[0])
    {
        int duplicate = FALSE;
        int count = 0;

        while (count == 0 || duplicate == TRUE)
        {
            autogen_seq* trc = (autogen_seq*)autogen_obj_get_first_in_list(trc_list);

            duplicate = FALSE;

            while (trc)
            {
                if (!strcmp(prop_get_string_default(&trc->base, PROPERTY_PMD_TRACE_DECODE_TEXT, ""), dectext_copy))
                {
                    if (count == 0)
                    {
                        if (g_autogen_env == AUTOGEN_ENV_LOCAL)
                        {
                            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                                "Duplicate trace text '%s'%s", dectext, trc_grp_info);
                        }
                        else
                        {
                            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_PRODUCT, 0,
                                "Duplicate trace text '%s'%s", dectext, trc_grp_info);
                        }
                    }

                    sprintf(dectext_copy, "%s_%d", dectext, count);

                    duplicate = TRUE;
                }

                trc = (autogen_seq*)trc->base.next;
            }

            count++;        
        }
    }

    /* create and initialize trace object, if non-empty */
    if (dectext_copy && dectext_copy[0])
    {
        prop_add_string_default(PROPERTY_PMD_TRACE_DECODE_TEXT, dectext_copy);

        init_common_seq_create(line, AUTOGEN_OBJ_TRACE, 0, s_trc_id[trc_type], flags, name, "", "", NULL);
        s_seq->base.parent = &s_trcgrp->base;

        if (g_trcgrp_conf[trc_type].has_groups)
        {
            s_trcgrp->has_traces = TRUE;
        }

        /* add trace object to list of traces */
        autogen_obj_list_add_obj(trc_list, &s_seq->base, AUTOGEN_ENV_ALL);
    }

    /* increment trace ID */
    ++s_trc_id[trc_type];

    /* set new scope and parent */
    init_scope_set(SCOPE_TRACE, &s_seq->base);

    /* if trace macro wihout _BEGIN has been used, end trace definition */
    if (!has_scope)
    {
        init_trace_end(line);
    }
}

/*  Init function for the MON_TRACE_DEFINE_ID_END macro 
*/
void init_trace_end(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_TRACE);
 
    if (s_seq)
    {
        /* Check for recursion */
        check_seq_recursion(s_file, s_seq, s_res, &s_res->base.ver);

        init_common_seq_end(line, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));
    }

    /* restore last scope and parent */
    init_scope_restore();
}

/*  Init function for the PPC _TBL_ENTRY macro 
*/
void init_ppc_tbl_entry_ver(int line, const char* name, unsigned int id, const char* seqname, const char* verfrom, const char* verto)
{
    autogen_data* data;

    /* --------------------------------------------------------------------- */
    /* general checks */
    /* --------------------------------------------------------------------- */

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_PPC_TBL);

    /* check ppc name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check subblock template name */
    check_c_name(s_file, line, "seqname", seqname, CHECK_NAME_EXIT_ON_FAIL);

    /* check ppc id */
    if (id > 0xFFFF)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'id' is out of range. Value must be between 0x0000 and 0xFFFF");
    }


    /* create ppc object */
    data = (autogen_data*)autogen_obj_create(s_file, line, s_tbl->base.res, &s_tbl->base, sizeof(autogen_data),
        AUTOGEN_OBJ_DATA, AUTOGEN_DATA_PPC, id, name, NULL);

    /* update properties and comments */
    init_update_properties_comments((autogen_obj*)data);

    /* Set feature flag */
    if (s_env->scope->feature_flags)
    {
        data->base.feature_flags = s_env->scope->feature_flags;
    }

    data->pres.type  = AUTOGEN_PRESENTATION_DEC;

    if (!strcmp(seqname, "MON_PPC_BYTE"))
    {
        data->base.flag |= AUTOGEN_DATA_VALUE;
        data->length  = 8;
        data->seqname = "MON_PPC_BYTE";
    }
    else if (!strcmp(seqname, "MON_PPC_WORD"))
    {
        data->base.flag |= AUTOGEN_DATA_VALUE;
        data->length  = 16;
        data->seqname = "MON_PPC_WORD";
    }
    else if (!strcmp(seqname, "MON_PPC_DWORD"))
    {
        data->base.flag |= AUTOGEN_DATA_VALUE;
        data->length  = 32;
        data->seqname = "MON_PPC_DWORD";
    }
    else if (!strcmp(seqname, "MON_PPC_TABLE_BYTE"))
    {
        data->base.flag |= AUTOGEN_DATA_TABLE;
        data->length  = 8;
        data->seqname = "MON_PPC_TABLE_BYTE";
    }
    else if (!strcmp(seqname, "MON_PPC_TABLE_WORD"))
    {
        data->base.flag |= AUTOGEN_DATA_TABLE;
        data->length  = 16;
        data->seqname = "MON_PPC_TABLE_WORD";
    }
    else if (!strcmp(seqname, "MON_PPC_TABLE_DWORD"))
    {
        data->base.flag |= AUTOGEN_DATA_TABLE;
        data->length  = 32;
        data->seqname = "MON_PPC_TABLE_DWORD";
    }
    /* unsupported subblock template */
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Unsupported PPC subblock template '%s' referenced", seqname);
    }

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    init_set_entry_version(line, (autogen_obj*)data, verfrom, verto);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    {
        autogen_it seq_it = INIT_ITERATOR;

        seq_it.typemask = AUTOGEN_OBJ_SB_TEMPLATE;
        seq_it.obj.name = seqname;
        seq_it.ver      = &s_tbl->base.ver;

         /* does the referenced subblock template exist for all versions */
        if (!autogen_obj_list_verify_object_span(&seq_it, &s_res->seq_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "The subblock template '%s' doesn't exist for all required versions", seqname);
        }
    }

    /* check if PPC constant conflicts with other constants or definitions */
    if (!(data->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR))
    {
        init_add_def(line, AUTOGEN_DEF_CONST, name, id, AUTOGEN_CONST_UNSIGNED_WORD, &data->base.ver, data->base.cmt_list,
            prop_find_first((autogen_obj*)data, PROPERTY_ISIHDR_ALIAS_NAME), NULL);
    }
#endif

    /* add PPC entry to table */
    autogen_obj_list_add_obj(&s_tbl->base.child_list, &data->base, AUTOGEN_ENV_ALL);
}

void init_ppc_tbl_entry(int line, const char* name, unsigned int id, const char* seqname)
{
    init_ppc_tbl_entry_ver(line, name, id, seqname, "", "");
}


/*  Init function for the REFERENCE macro */
void init_reference(int line, int length, unsigned int order, const char* varname, const char* name, const char* refname)
{
    autogen_item_value* value;
    unsigned int flag = 0;
    unsigned int special_type = PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE;
    unsigned int trc_type = AUTOGEN_OBJ_TRACEGRP_NONE;
    char* parname = pmd_heap_strdup(name);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check reference name */
    check_c_name(s_file, line, "refname", refname, CHECK_NAME_EXIT_ON_FAIL);

    /* check variable size in bits */
    init_check_length(line, length, TRUE, FALSE, (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* check data order */
    order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, length, (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* create and initialize reference object */
    value = (autogen_item_value*)init_item_create(line, sizeof(autogen_item_value), AUTOGEN_ITEM_REF, flag, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* Create and add the reference to the handle in the sequence */

    special_type = reference_add_counter(reference_get_handle_from_obj(&value->base.base), &value->base, refname, length, (s_env->scope ? s_env->scope->feature_flags : NULL));

    if (special_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID)
    {
        s_res->msg_id_size = length;
    }
    else if (special_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH)
    {
        s_res->msg_length_size = length;
    }
    else if (special_type == PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID)
    {
        s_res->submsg_id_size = length;
    }

    /* else check all trace groups / ids */
    else
    {
        trc_type = util_get_tracegroup_type_from_refname(refname);
        if (trc_type != AUTOGEN_OBJ_TRACEGRP_NONE)
        {
            if (!strcmp(refname, g_trcgrp_conf[trc_type].trace_entity_id_refname))
            {
                special_type = g_trcgrp_conf[trc_type].entity_special_type;

                if (length != g_trcgrp_conf[trc_type].entity_size)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Argument 'length' is %d, which is out of range. Value must be %d in this context", length, g_trcgrp_conf[trc_type].entity_size);
                }
            }
            else if (!strcmp(refname, g_trcgrp_conf[trc_type].trace_group_id_refname))
            {
                special_type = g_trcgrp_conf[trc_type].group_special_type;

                if (length != g_trcgrp_conf[trc_type].group_size)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Argument 'length' is %d, which is out of range. Value must be %d in this context", length, g_trcgrp_conf[trc_type].group_size);
                }
            }
            else if (!strcmp(refname, g_trcgrp_conf[trc_type].trace_id_refname))
            {
                special_type = g_trcgrp_conf[trc_type].id_special_type;

                if (length != g_trcgrp_conf[trc_type].id_size)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Argument 'length' is %d, which is out of range. Value must be %d in this context", length, g_trcgrp_conf[trc_type].id_size);
                }
            }
        }
    }

    /* copy version */
    memcpy(&value->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    /* look for defined constants */
    init_check_string_prop(line, (autogen_obj*)value, PROPERTY_ITEM_MINIMUM_VALUE, (s_env->scope ? s_env->scope->feature_flags : NULL));
    init_check_string_prop(line, (autogen_obj*)value, PROPERTY_ITEM_MAXIMUM_VALUE, (s_env->scope ? s_env->scope->feature_flags : NULL));

    value->base.length = length;
    value->base.order  = order;
    value->base.special_number_type = special_type;
    value->base.trc_type = trc_type;

    value->base.base.name = refname;

    /* set presentation type */
    if (special_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID)
    {
        if (s_seq->base.type == AUTOGEN_OBJ_SEQ)
        {
            value->pres.type = AUTOGEN_PRESENTATION_REF_DATAID;
        }
        else
        {
            value->pres.type = AUTOGEN_PRESENTATION_REF_SBID;
            value->pres.obj  = (autogen_obj*)s_seq;
        }
    }
    else if (special_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID ||
             special_type == PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID ||
             special_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_ID ||
             special_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_GROUP_ID ||
             special_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH)
    {
        value->pres.obj  = (autogen_obj*)s_seq;
    }
    else if (special_type == PMD_NUMBER_SPECIAL_TYPE_PRIVATE_ID)
    {
        const autogen_symbol_conf* p_sym_conf = util_get_sym_conf_by_type(PRIVATE_ID);

        value->pres.type    = p_sym_conf->pres_flag;
        value->pres.subtype = PRIVATE_ID;
        value->pres.tblname = p_sym_conf->tblname;
        value->pres.tblres  = util_get_unique_res(RESOURCE_SYMBOLS);
    }
    else if (special_type == PMD_NUMBER_SPECIAL_TYPE_XTI_MASTER_ID)
    {
        const autogen_symbol_conf* p_sym_conf = util_get_sym_conf_by_type(XTI_MASTER_ID);

        value->pres.type    = p_sym_conf->pres_flag;
        value->pres.subtype = XTI_MASTER_ID;
        value->pres.tblname = p_sym_conf->tblname;
        value->pres.tblres  = util_get_unique_res(RESOURCE_SYMBOLS);
    }
    else if (special_type == PMD_NUMBER_SPECIAL_TYPE_RESOURCE_ID)
    {
        const autogen_symbol_conf* p_sym_conf = util_get_sym_conf_by_type(RESOURCE_ID);

        value->pres.type    = p_sym_conf->pres_flag;
        value->pres.subtype = RESOURCE_ID;
        value->pres.tblname = p_sym_conf->tblname;
        value->pres.tblres  = util_get_unique_res(RESOURCE_SYMBOLS);
    }
    else
    {
        value->pres.type = AUTOGEN_PRESENTATION_DEC;
    }

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += abs(length); 
    }
    
    /* handle filler replacement */
    if (prop_has(&value->base.base, PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Property PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION can't be used with references\n");
    }

    /* add item object to sequence object */
    init_item_add(&value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}


/*  Init function for the REFERENCE_CONST macro 
*/
void init_reference_const(int line, const char* varname, const char* name, const char* refname, const char* tblname)
{
    autogen_tbl* tbl = NULL;
    autogen_item_value* ref = NULL;
    char* parname = pmd_heap_strdup(name);


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check reference name */
    check_c_name(s_file, line, "refname", refname, CHECK_NAME_EXIT_ON_FAIL);

    /* check constant table name */
    check_c_name(s_file, line, "tblname", tblname, CHECK_NAME_EXIT_ON_FAIL);

    /* create and initialize reference object */
    ref = (autogen_item_value*)init_item_create(line, sizeof(autogen_item_value), AUTOGEN_ITEM_REF, AUTOGEN_REF_CONST, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* Create and add the reference to the handle in the sequence */
    reference_add_tag(reference_get_handle_from_obj(&ref->base.base), &ref->base, refname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&ref->base.base.ver, &s_seq->base.ver, sizeof(autogen_ver));

    /* check if constant refers to predefined table */
    init_pres_const(line, &ref->pres, AUTOGEN_PRESENTATION_CONST_ANY, tblname, s_res);

    /* if predefined constant is referenced */ 
    if (ref->pres.type & AUTOGEN_PRESENTATION_SYMBOL_ANY)
    {
        autogen_it tbl_it = INIT_ITERATOR;

        /* check that a table exist for the current resource version */
        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_DERCONST;
        tbl_it.obj.name    = ref->pres.tblname;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &ref->pres.tblres->tbl_list);
        if (!tbl)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'tblname' is not valid");
        }
    }
    /* else if a defined constant table is referenced */ 
    else if (ref->pres.type & AUTOGEN_PRESENTATION_CONST)
    {
        autogen_it tbl_it = INIT_ITERATOR;

        /* find the table */
        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_DERCONST | AUTOGEN_TBL_BIT | AUTOGEN_TBL_DERBIT;
        tbl_it.obj.name    = tblname;
        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_COVER_SINGLE;
        tbl_it.ver         = &s_seq->base.ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            tbl_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &s_seq->base.res->tbl_list);
        if (!tbl)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "The constant/bitmask table '%s' doesn't exist for all required versions", tblname);
        }
    }

    ref->base.base.name = refname;

    ref->base.length = tbl->orgtbl->length;
    ref->base.order  = tbl->orgtbl->order;

    /* update bool type from table */
    if (prop_has((autogen_obj*)tbl, PROPERTY_ISIHDR_GENERATE_AS_BOOL))
    {
        prop_add_simple_to_object((autogen_obj*)ref, PROPERTY_ISIHDR_GENERATE_AS_BOOL, NULL, 0, FALSE);
    }
    else if (prop_has((autogen_obj*)tbl, PROPERTY_ISIHDR_GENERATE_AS_BITFIELD))
    {
        prop_add_simple_to_object((autogen_obj*)ref, PROPERTY_ISIHDR_GENERATE_AS_BITFIELD, NULL, 0, FALSE);
    }
    /* update definition name from table */
    if (prop_has((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME))
    {
        if (!(prop_get_flags((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME) & PROPERTY_FLAG_DEFAULT))
        {
            prop_add_string_to_object((autogen_obj*)ref, PROPERTY_ISIHDR_DEFINITION_NAME, 
                prop_get_string((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME), NULL, 0, FALSE);
        }
    }

    /* check the size of the table constants */
    init_check_length(line, tbl->orgtbl->length, TRUE, (PMD_FILE_FORMAT >= 600), (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += abs(tbl->orgtbl->length); 
    }

    /* add the relation to this sequence from the table */
    init_item_add_relations((autogen_item*)ref, &s_env->scope->parent->ver, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* handle filler replacement */
    if (prop_has(&ref->base.base, PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Property PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION can't be used with references\n");
    }

    /* add item object to sequence object */
    init_item_add(&ref->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}


/*  Init function for the REFERENCE_TRANSFORM macro */
void init_reference_transform(int line, const char* oldrefname, const char* newrefname, unsigned int alg, const char* alg_str, int n)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE);

    /* check old reference name */
    check_c_name(s_file, line, "oldrefname", oldrefname, CHECK_NAME_EXIT_ON_FAIL);

    /* check new reference name */
    check_c_name(s_file, line, "newrefname", newrefname, CHECK_NAME_EXIT_ON_FAIL);

    /* check names against each other */
    if (!strcmp(oldrefname, newrefname))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'oldrefname' and 'newrefname' are identical");
    }

    /* check algorithm type */
    if (alg < ALG_MIN || alg > ALG_MAX)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'alg' is '%s', which is not valid", alg_str);
    }

    /* check value */
    if (n < -65535 || n == 0 || n > 65535)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'n' is %d, which is out of range. Value must be between -65535 and 65535, and not zero", n);
    }
    if ((alg == ALG_DIV || alg == ALG_DIV_ROUND_UP || alg == ALG_N_SUB) && n < 0)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'n' is %d, which is out of range. Value must be positive", n);
    }

    /* if subtraction, negate and define as addition */
    if (alg == ALG_SUB)
    {
        alg = ALG_ADD;
        n = -n;
    }

    /* Verify and add the reference to the reference handle of the sequence */
    reference_add_transformation(reference_get_handle_from_obj(s_env->scope->parent), newrefname, oldrefname, alg, n, line, (s_env->scope ? s_env->scope->feature_flags : NULL));
}


/*  Init function for the  / SB_LST_ENTRY_VER macro 
*/
void init_sb_lst_entry(int line, const char* sbname, const char* verfrom, const char* verto)
{
    autogen_obj test_ver = INIT_OBJECT;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_SB_LST);

    /* check subblock name */
    check_c_name(s_file, line, "sbname", sbname, CHECK_NAME_EXIT_ON_FAIL);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);


    /* if version is not specified, copy from s_parent */
    if (!verfrom[0] && !verto[0])
    {
        memcpy(&test_ver.ver, &s_lst->seq->base.ver, sizeof(autogen_ver));
    }
    /* else check and set version from arguments */
    else
    {
        /* Start version of entry not specified */
        if (!verfrom[0] && s_lst->seq->base.ver.from[0])
        {
            char ver_fm[12];
            memset(ver_fm,'\0',12);
            /*if (s_lst->seq->base.ver.from[0])*/
            {
                if (s_res->base.subtype == RESOURCE_ISI_DSP)
                {
                    sprintf(ver_fm, "%03d.%03d.%03d", s_lst->seq->base.ver.from[0], s_lst->seq->base.ver.from[1], s_lst->seq->base.ver.from[2]);
                }
                else
                {
                    sprintf(ver_fm, "%03d.%03d", s_lst->seq->base.ver.from[0], s_lst->seq->base.ver.from[1]);
                }
                init_obj_ver_set(line, s_res, &test_ver, ver_fm, verto, AUTOGEN_VERSION_INTERVAL,
                    s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);
            }
        }
        else
        {
            init_obj_ver_set(line, s_res, &test_ver, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
                s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);
        }

        /* is the version totally included in the s_parent version? */
        if (!autogen_obj_ver_is_included(&s_lst->base.ver, &test_ver.ver))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Version interval is out of range");
        }
    }

    /* check if the subblock is 'SB_FTD_ANY' */
    if (!strcmp(sbname, "SB_FTD_ANY") || !strcmp(sbname, "SB_FTD_ANY_AS_PARAMETERS"))
    {
        /* check that the macro is not SB_LST_ENTRY_VER */
        if (verfrom[0] || verto[0])
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' is not valid in this context");
        }

        /* check that 'SB_FTD_ANY' does not conflict with other special sb */
        if (s_lst->base.flag & (AUTOGEN_LST_FTD | AUTOGEN_LST_PPC | AUTOGEN_LST_SOS_FTD))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' conflicts with other entries in the list");
        }

        /* check that 'SB_FTD_ANY' does not conflict with other subblocks (ID's) */
        if (s_lst->base.flag & AUTOGEN_LST_SB_HAVE_BYTE_IDS)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' conclicts with other entries in the list");
        }

        /* check that the resource supports FTD data */
        if (s_res->base.subtype != RESOURCE_ISI_MEDIA_CONTROL &&
            s_res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES &&
            s_res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES_EXT)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' is not valid in this context");
        }

        s_lst->base.flag |= AUTOGEN_LST_FTD;
        s_lst->base.flag |= AUTOGEN_LST_SB_HAVE_WORD_IDS;

        if (!strcmp(sbname, "SB_FTD_ANY_AS_PARAMETERS"))
        {
            s_lst->base.flag |= AUTOGEN_LST_AS_PARAMETERS;
        }
    }

 #ifdef AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES
    /* check if the subblock is 'SB_SOS_FTD_ANY' */
    else if (!strcmp(sbname, "SB_SOS_FTD_ANY") || !strcmp(sbname, "SB_SOS_FTD_ANY_AS_PARAMETERS"))
    {
        /* check that the macro is not SB_LST_ENTRY_VER */
        if (verfrom[0] || verto[0])
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' is not valid in this context");
        }

        /* check that 'SB_SOS_FTD_ANY' does not conflict with other special sb */
        if (s_lst->base.flag & (AUTOGEN_LST_FTD | AUTOGEN_LST_PPC | AUTOGEN_LST_SOS_FTD))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' conflicts with other entries in the list");
        }

        /* check that 'SB_SOS_FTD_ANY' does not conflict with other subblocks (ID's) */
        if (s_lst->base.flag & AUTOGEN_LST_SB_HAVE_BYTE_IDS)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' conclicts with other entries in the list");
        }

        /* check that the resource supports FTD data */
        /*
 ->       if (s_res->base.subtype != RESOURCE_ISI_MEDIA_CONTROL &&
 ->           s_res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES &&
 ->           s_res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES_EXT)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' is not valid in this context");
        }
        */
        s_lst->base.flag |= AUTOGEN_LST_SOS_FTD;
        s_lst->base.flag |= AUTOGEN_LST_SB_HAVE_WORD_IDS;

        if (!strcmp(sbname, "SB_FTD_ANY_AS_PARAMETERS"))
        {
            s_lst->base.flag |= AUTOGEN_LST_AS_PARAMETERS;
        }
    }
#endif

    /* check if the subblock is 'SB_PPC_ANY' or 'SB_PPC_ANY_AS_PARAMETERS' */
    else if (!strcmp(sbname, "SB_PPC_ANY") || !strcmp(sbname, "SB_PPC_ANY_AS_PARAMETERS"))
    {
        /* check that the macro is not SB_LST_ENTRY_VER */
        if (verfrom[0] || verto[0])
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' is not valid in this context");
        }

        /* check that 'SB_PPC_ANY' does not conflict with other special sb */
        if (s_lst->base.flag & (AUTOGEN_LST_FTD | AUTOGEN_LST_PPC | AUTOGEN_LST_SOS_FTD))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' conclicts with other entries in the list");
        }

        /* check that 'SB_PPC_ANY' does not conflict with other subblocks (ID's) */
        if (s_lst->base.flag & AUTOGEN_LST_SB_HAVE_BYTE_IDS)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'sbname' conclicts with other entries in the list");
        }

        /* set a relation between the PPC table(s) and the sequence */
        {
            autogen_obj* tbl;
            autogen_it tbl_it = INIT_ITERATOR;

            tbl_it.typemask    = AUTOGEN_OBJ_TBL;
            tbl_it.subtypemask = AUTOGEN_TBL_PPC;
            tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            tbl_it.ver         = &test_ver.ver;
            if (s_env->scope->next ? s_env->scope->next->feature_flags : NULL)
            {
                tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                tbl_it.obj.feature_flags = s_env->scope->next->feature_flags;
            }

            /* check that a PPC table is defined for the whole version interval of the entry */
            if (!autogen_obj_list_verify_object_span(&tbl_it, &s_res->tbl_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "The PPC table doesn't exist for all required versions");
            }

            tbl = autogen_obj_find_in_list(&tbl_it, &s_res->tbl_list);
            while (tbl)
            {
                init_add_obj_relation((autogen_obj*)s_lst, tbl, NULL, (s_env->scope->next ? s_env->scope->next->feature_flags : NULL));

                tbl = autogen_obj_find_next_in_list(&tbl_it);
            }
        }

        s_lst->base.flag |= AUTOGEN_LST_PPC;
        s_lst->base.flag |= AUTOGEN_LST_SB_HAVE_WORD_IDS;

        if (!strcmp(sbname, "SB_PPC_ANY_AS_PARAMETERS"))
        {
            s_lst->base.flag |= AUTOGEN_LST_AS_PARAMETERS;
        }
    }
    /* if the subblock is an ordinary subblock */
    else
    {
        autogen_seq* sb;
        autogen_it sb_it = INIT_ITERATOR;
        autogen_seq_ref* first_ref = NULL;

        /* find first subblock which satisfies the version criteria
           the subblock could exist in a shared file 
        */
        sb_it.typemask = AUTOGEN_OBJ_SB;
        sb_it.obj.name = sbname;
        sb_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        sb_it.ver      = &test_ver.ver;
        if (s_env->scope->next ? s_env->scope->next->feature_flags : NULL)
        {
            sb_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            sb_it.obj.feature_flags = s_env->scope->next->feature_flags;
        }

        sb = (autogen_seq*)autogen_obj_find_in_list(&sb_it, &s_res->seq_list);
        /* verify that at least one subblock is defined */
        if (!sb)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
               "The referenced subblock '%s' is not defined for any overlapping version",
                sbname);
        }
        /* iterate through all subblocks that satisfies the version criteria */
        while (sb)
        {
            const autogen_item* id_item = reference_get_special_item(&sb->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID);

            /* create a subblock reference */
            autogen_seq_ref* ref = 
                (autogen_seq_ref*)autogen_obj_create(s_file, line, s_lst->base.res, &s_lst->base, sizeof(autogen_seq_ref), AUTOGEN_OBJ_REF, AUTOGEN_OBJ_SB, sb->base.id, sbname, NULL);

            if (!first_ref)
            {
                first_ref = ref;

                /* update properties and comments */
                init_update_properties_comments((autogen_obj*)ref);
            }

            ref->seqptr         = sb;
            ref->base.flag      = sb->base.flag;
            ref->base.prop_list = first_ref->base.prop_list;

            /* copy entry version to reference */
            /* ensure that version is not wider than version of subblock */
            memcpy(&ref->base.ver, 
                autogen_obj_ver_crop(&test_ver.ver, &sb->base.ver), 
                sizeof(autogen_ver));

            /* Verify that this subblock ID is not already referenced */
            /* It is not allowed that two subblocks with the same ID */
            /* is referenced in the same SB_LST_REF_BEGIN/SB_LST_BEGIN */
            { 
                autogen_it ref_it = INIT_ITERATOR;
                autogen_obj *reference = NULL;

                /* Match a reference with subtype subblock */
                ref_it.typemask    = AUTOGEN_OBJ_REF;
                ref_it.subtypemask = AUTOGEN_OBJ_SB;
                ref_it.subtypecrit = AUTOGEN_OBJ_SUBTYPE_EXACT;

                /* Do not use binary search */
                ref_it.sort_type = AUTOGEN_OBJ_LIST_SORT_NONE;

                /* Match the subblock id */
                ref_it.idcrit = AUTOGEN_OBJ_ID_EXACT;
                ref_it.obj.id = ref->base.id;

                /* Match only subblocks that overlaps version wise */ 
                ref_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                ref_it.ver      = &ref->base.ver;

                /* Check if there is references to subblocks with matching IDs */
                reference = autogen_obj_find_in_list(&ref_it, &s_lst->base.child_list);
                if (reference)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 9,
                        "All referenced subblock IDs must be unique within subblock list."); 
                }
            } 

            /* add the subblock reference */
#ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
            autogen_obj_list_add_obj(&s_lst->base.child_list, &ref->base, AUTOGEN_ENV_LOCAL);
#else
            autogen_obj_list_add_obj(&s_lst->base.child_list, &ref->base, AUTOGEN_ENV_NONE);
#endif /* AUTOGEN_DISABLE_TOUGH_CHECKS */

            /* set subblock id size */
            if (id_item)
            {
                if (id_item->length == 8)
                {
                    s_lst->base.flag |= AUTOGEN_LST_SB_HAVE_BYTE_IDS;
                }
                else
                {
                    s_lst->base.flag |= AUTOGEN_LST_SB_HAVE_WORD_IDS;
                }
            }

            /* check that subblocks with conflicting subblock ID sizes are not defined */
            if ((s_lst->base.flag & AUTOGEN_LST_SB_HAVE_BYTE_IDS) &&
                (s_lst->base.flag & AUTOGEN_LST_SB_HAVE_WORD_IDS))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Subblocks with both 8 and 16 bit ID's are defined in the subblock list, which is not allowed"); 
            }

            /* check that a variable name is defined if a union is defined */
            if (prop_get_value_default((autogen_obj*)s_lst, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_ANYSIZE) == ISIHDR_MARKER_UNION)
            {
                if (!prop_has((autogen_obj*)ref, PROPERTY_ISIHDR_DEFINITION_NAME))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "No property 'PROPERTY_ISIHDR_DEFINITION_NAME' is defined for the subblock entry, which is a must when using ISIHDR_MARKER_UNION");
                }
            }

            /* find next subblock */
            sb = (autogen_seq*)autogen_obj_find_next_in_list(&sb_it);
        }

        s_lst->base.flag |= AUTOGEN_LST_SB;
    }
}


/*  Init function for the STRING macro 
*/
void init_string(int line, unsigned int strtype, unsigned int order, 
                 const char* varname, const char* name, unsigned int n, const char* nstr)
{
    autogen_item_string* string;
    unsigned int flag = 0;
    int size = 0;
    char* parname = pmd_heap_strdup(name);


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_TRACE | SCOPE_CASE | SCOPE_PRINTF);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check string type */
    if (strtype & STRING_ASCII)
    {
        flag = AUTOGEN_STRING_ASCII;
    }
    else if (strtype & STRING_UNICODE)
    {
        flag = AUTOGEN_STRING_UNICODE;
    }
    else if (strtype & STRING_BCD)
    {
        flag = AUTOGEN_STRING_BCD;
    }
    else if (strtype & STRING_UTF8)
    {
        flag = AUTOGEN_STRING_UTF8;
    }
    else if (strtype & STRING_GSM)
    {
        flag = AUTOGEN_STRING_GSM;
    }
    else if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
    {
        flag = AUTOGEN_STRING_ASCII;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'strtype' is not valid");
    }

    /* set zero-termination */
    if (strtype & NULL_TERMINATION_PRESENT)
    {
        flag |= AUTOGEN_STRING_ZERO_TERMINATED;
    }

    /* check data order */

    /* for BCD strings, order must be NSW or NONE */
    if (flag & AUTOGEN_STRING_BCD)
    {
        order = init_check_order(line, AUTOGEN_ORDER_BCD_NSW | AUTOGEN_ORDER_BCD_NONE, order, 8, FALSE);
    }
    /* for Unicode strings, order must be LE or BE */
    else if (flag & AUTOGEN_STRING_UNICODE)
    {
        order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, 16, FALSE);
    }
    /* for ASCII strings, order must be BE or LE */
    else
    {
        order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, 8, FALSE);
    }

    /* check length of string */
    if (flag & AUTOGEN_STRING_ASCII)
    {
        if (n < 1 || n > 65535)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'nchar' is out of range. Value must be between 1 and 65535 for ASCII strings");
        }
    }
    else if (flag & AUTOGEN_STRING_UNICODE)
    {
        if (n < 1 || n > 32767)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'nchar' is out of range. Value must be between 1 and 32767 for Unicode strings");
        }
    }
    else if (flag & AUTOGEN_STRING_BCD)
    {
        if (n < 1 || n > 65535)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'nchar' is out of range. Value must be between 1 and 65535 for BCD strings");
        }
    }

    /* add number of characters string to constants */
    init_constant_add(line, nstr, n, AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_seq->base.ver, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* create and initialize item object */
    string = (autogen_item_string*)init_item_create(line, sizeof(autogen_item_string), AUTOGEN_ITEM_STRING, flag, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&string->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    string->base.order    = order;
    string->base.agg_type = AGG_TYPE_FIXED_SINGLE;

    /* set aggregation info */
    string->base.agg_n_str  = "1";
    string->length          = (unsigned short)n;
    string->length_str      = nstr;

    /* add item object to sequence object */
    init_item_add(&string->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

    if (prop_has(&string->base.base, PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH))
    {
        char* new_str_len = (char*)pmd_heap_alloc(strlen(nstr) + 5);

        if (atoi(nstr) == (unsigned short)n)
        {
            sprintf(new_str_len, "%d", 1 + (unsigned short)n);
        }
        else
        {
            sprintf(new_str_len, "%s+1", nstr);
        }
        string->length_str = new_str_len;
        ++string->length;
    }

    /* In case a BCD to ASCII map is defined we must assure that the length of the map is max. 16 */
    if (flag & AUTOGEN_STRING_BCD)
    {
        if (prop_has(&string->base.base, PROPERTY_STRING_BCD_MAP))
        {
            const char *bcd_map = prop_get_string(&string->base.base, PROPERTY_STRING_BCD_MAP);
            size = strlen(bcd_map);
            if (size > 16)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "PROPERTY_STRING_BCD_MAP contains more than 16 characters!");
            }
        }
    }

    /* String is default not parameter in a scope printf */
    if (s_env->scope->scope == SCOPE_PRINTF)
    {
        if (!prop_has((autogen_obj*)string, PROPERTY_PMD_IS_NOT_PARAMETER))
        {
            prop_add_simple_to_object((autogen_obj*)string, PROPERTY_PMD_IS_NOT_PARAMETER, NULL, 0, 0);
        }
    }
}


/*  Init function for the STRING_REF macro 
*/
void init_string_ref(int line, unsigned int strtype, unsigned int order, 
                     const char* varname, const char* name, const char* refname, unsigned int flag)
{
    autogen_item_string* string;
    autogen_agg_type agg_type = AGG_TYPE_UNKNOWN;
    unsigned int item_flag = 0;
    char* parname = pmd_heap_strdup(name);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_TRACE | SCOPE_CASE | SCOPE_PRINTF);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check string type */
    if (strtype == STRING_ASCII || strtype == (STRING_ASCII | NULL_TERMINATION_PRESENT))
    {
        item_flag = AUTOGEN_STRING_ASCII;
    }
    else if (strtype == STRING_UNICODE || strtype == (STRING_UNICODE | NULL_TERMINATION_PRESENT))
    {
        item_flag = AUTOGEN_STRING_UNICODE;
    }
    else if (strtype == STRING_BCD)
    {
        item_flag = AUTOGEN_STRING_BCD;
    }
    else if (strtype == STRING_UTF8 || strtype == (STRING_UTF8 | NULL_TERMINATION_PRESENT))
    {
        item_flag = AUTOGEN_STRING_UTF8;
    }
    else if (strtype == STRING_GSM)
    {
        item_flag = AUTOGEN_STRING_GSM;
    }
    else if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
    {
        item_flag = AUTOGEN_STRING_ASCII;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'strtype' is not valid");
    }

    /* set zero-termination */
    if (strtype & NULL_TERMINATION_PRESENT)
    {
        item_flag |= AUTOGEN_STRING_ZERO_TERMINATED;
    }

    /* check data order */

    /* for BCD strings, order must be NSW or NONE */
    if (item_flag & AUTOGEN_STRING_BCD)
    {
        order = init_check_order(line, AUTOGEN_ORDER_BCD_NSW | AUTOGEN_ORDER_BCD_NONE, order, 8, FALSE);
    }
    /* for Unicode strings, order must be LE or BE */
    else if (item_flag & AUTOGEN_STRING_UNICODE)
    {
        order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, 16, FALSE);
    }
    /* for ASCII strings, order must be BE or LE */
    else
    {
        order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, 8, FALSE);
    }

    /* check reference name */
    check_c_name(s_file, line, "refname", refname, CHECK_NAME_EXIT_ON_FAIL);

    /* set aggregation type */
    /* allow predefined reference name REF_AS_LONG_AS_POSSIBLE and
       REF_LENGTH_DETERMINED_BY_ZERO to be used */
    if (!strcmp(refname, "REF_AS_LONG_AS_POSSIBLE"))
    {
        agg_type = AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE;
    }
    else if (!strcmp(refname, "REF_LENGTH_DETERMINED_BY_ZERO"))
    {
        /* can't be used with BCD strings */
        if (item_flag & AUTOGEN_STRING_BCD)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'refname' is not valid in this context");

            agg_type = AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE;
        }
        else
        {
            item_flag |= AUTOGEN_STRING_ZERO_TERMINATED;
            agg_type = AGG_TYPE_DYNAMIC_ZEROTERMINATED;
        }
    }
    else
    {
        agg_type = AGG_TYPE_DYNAMIC_REF;
    }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    /* check array flag */
    if (flag == ISIHDR_MARKER_ANYSIZE ||
        flag == ISIHDR_MARKER_ANYSIZE_BYTE ||
        flag == ISIHDR_MARKER_ANYSIZE_WORD ||
        flag == ISIHDR_MARKER_SINGLE_ELEMENT ||
        flag == ISIHDR_MARKER_SINGLE_ELEMENT_BYTE ||
        flag == ISIHDR_RESERVE_SPACE ||
        flag == ISIHDR_POINTER ||
        flag == ISIHDR_POINTER_VOID ||
        flag == ISIHDR_MARKER_POINTER)
    {
    }
    else if (flag == ISIHDR_DONT_GENERATE)
    {
        item_flag |= AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;
    }
    /* default */
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'flag' is not valid");

        flag = ISIHDR_MARKER_ANYSIZE;
    }

    /* add property */
    prop_add_value(PROPERTY_ISIHDR_ARRAY_MARKER, flag, FALSE, "", 0, FALSE);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* create and initialize item object */
    string = (autogen_item_string*)init_item_create(line, sizeof(autogen_item_string), 
        AUTOGEN_ITEM_STRING, item_flag, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&string->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    string->base.order    = order;
    string->base.agg_type = agg_type;

    /* set aggregation info and check reference */
    if (agg_type == AGG_TYPE_DYNAMIC_REF)
    {
        string->base.refname = refname;
        reference_use_counter(&string->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
    }

    /* add number of characters string to constants (from property) */
    if (prop_has((autogen_obj*)string, PROPERTY_STRING_MAXIMUM_LENGTH))
    {
        init_constant_add(line, 
            prop_get_string((autogen_obj*)string, PROPERTY_STRING_MAXIMUM_LENGTH),
            prop_get_value((autogen_obj*)string, PROPERTY_STRING_MAXIMUM_LENGTH), 
            AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_seq->base.ver, 
            (s_env->scope ? s_env->scope->feature_flags : NULL));
    }
    /* Validate combinations of array type and marker flag */
    else if (flag == ISIHDR_RESERVE_SPACE && 
        (agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE || 
         agg_type == AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH || 
          agg_type == AGG_TYPE_DYNAMIC_ZEROTERMINATED))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Impossible to reserve space as no length is defined");
    }
    else if (flag == ISIHDR_RESERVE_SPACE &&
        agg_type == AGG_TYPE_DYNAMIC_ZEROTERMINATED)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Impossible to reserve space as no length is defined");
    }

    /* String is default not parameter in a scope printf */
    if (s_env->scope->scope == SCOPE_PRINTF)
    {
        if (!prop_has((autogen_obj*)string, PROPERTY_PMD_IS_NOT_PARAMETER))
        {
            prop_add_simple_to_object((autogen_obj*)string, PROPERTY_PMD_IS_NOT_PARAMETER, NULL, 0, 0);
        }
    }

    /* add item object to sequence object */
    init_item_add(&string->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}

/* Init function for the PRINTF_BEGIN macro
*/
void init_printf_begin(int line, const char *_format)
{
    autogen_item_printf *printf_item;
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long component_id = 0;
    unsigned long long tracegrp_id  = 0;
    unsigned long long trace_id     = 0;
#else
    unsigned int component_id = 0;
    unsigned int tracegrp_id  = 0;
    unsigned int trace_id     = 0;
#endif
    char tmpname[100];
    char *varname, *parname;

    /* Check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_TRACE);

    /* Check if there is more than one printf. If so then error */
    {
        autogen_it printf_it = INIT_ITERATOR;

        printf_it.typemask    = AUTOGEN_OBJ_ITEM;
        printf_it.subtypemask = AUTOGEN_ITEM_PRINTF;

        if (autogen_obj_find_in_list(&printf_it, &s_env->scope->parent->child_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Only one printf macro allowed in a trace.");
        }
    }

    /* Retrieve the component, trace group and trace ID */
    component_id = prop_get_value_default(&s_res->base, PROPERTY_COMPONENT_ID, 0);
    tracegrp_id  = s_env->scope->parent->parent->id;
    trace_id     = s_env->scope->parent->id;

    /* Autogenerate varname, parname */
#if (PMD_FILE_FORMAT >= 600)
    sprintf(tmpname, "PRINTF_%llu_%llu_%llu", component_id, tracegrp_id, trace_id);
#else
    sprintf(tmpname, "PRINTF_%u_%u_%u", component_id, tracegrp_id, trace_id);
#endif
    varname = pmd_heap_strdup(tmpname);
    parname = pmd_heap_strdup(tmpname);

    /* Compute default structure name and size */
    {
        char *struct_name = (char *)pmd_heap_alloc(strlen(varname) + 5);
        char *len_name    = pmd_heap_alloc(strlen(varname) + 10);

        /* Default structure name */
        sprintf(struct_name, "%s_STR", varname);
        prop_add_string_default(PROPERTY_ISIHDR_STRUCT_NAME, struct_name);

        /* Default size name */
        strcpy(len_name, "SIZE_");
        strcat(len_name, struct_name);
        prop_add_string_default(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, len_name);
    }

    /* Create the printf item and init child list */
    printf_item = (autogen_item_printf *)init_item_create(line, sizeof(autogen_item_printf), AUTOGEN_ITEM_PRINTF, 0, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));
    autogen_obj_list_init(&printf_item->base.base.child_list, &printf_item->base.base, 0, 10);

    /* Set name */
    printf_item->base.base.name = varname;

    /* Copy version */
    memcpy(&printf_item->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    /* Store the component, trace group and trace ID */
    printf_item->component_id = component_id;
    printf_item->tracegrp_id  = tracegrp_id;
    printf_item->trace_id     = trace_id;

    /* Store the format string */
    printf_item->format = _format;

    /* Add item object to sequence object */
    init_item_add(&printf_item->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* Set new scope and parent */
    init_scope_set(SCOPE_PRINTF, &printf_item->base.base);
}

/* Init function for the PRINTF_END macro
*/
void init_printf_end(int line)
{
    autogen_item_printf *printf_item = (autogen_item_printf *)(s_env->scope->parent);

    /* Check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_PRINTF);

    /* Validate the syntax of the format string */
    /* and the corresponding arguments          */
    util_validate_printf_format_string(s_file, line, printf_item->format, &printf_item->base.base.child_list);

    /* Empty properties and comments */
    init_clear_properties_comments(line);

    /* Restore last scope and parent */
    init_scope_restore();
}

/*  Init function for the VALUE / VALUE_EX macros
*/
void init_timestamp(int line, int length, unsigned int order, const char* varname, const char* name, unsigned int type)
{
    autogen_item_value* value;
    char* parname = pmd_heap_strdup(name);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE | SCOPE_FTD_TBL_ENTRY);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check timestamp type */
    if (type > PMD_TIMESTAMP_TYPE_MAX)
    {
        if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
        {
            type = PMD_TIMESTAMP_TYPE_UNKNOWN;
        }
        /* else produce an error */
        else
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'type' is not valid");
        }
    }

    /* check variable size in bits */
    init_check_length(line, length, FALSE, TRUE, (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* create and initialize item object */
    value = (autogen_item_value*)init_item_create(line, sizeof(autogen_item_value), AUTOGEN_ITEM_TIMESTAMP, 0, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&value->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    value->base.item_sub_type = type;
    value->base.length = length;
    value->pres.type = AUTOGEN_PRESENTATION_TIMESTAMP;
    value->base.special_number_type  = PMD_NUMBER_SPECIAL_TYPE_TIMESTAMP;

    /* check data order */
    value->base.order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, length, FALSE);

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += abs(length); 
    }
    else if (s_env->scope->scope == SCOPE_FTD_TBL_ENTRY)
    {
        s_env->ftd_length_sum += abs(length);
    }

    if (!prop_has((autogen_obj*)value, PROPERTY_PMD_PARAMETER))
    {
        prop_add_simple_to_object((autogen_obj*)value, PROPERTY_PMD_PARAMETER, NULL, 0, 0);
    }

    /* add item object to sequence object */
    init_item_add(&value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}



/*  Init function for the DER_CONST_TBL_ENTRY, DER_BIT_TBL_ENTRY, DER_CONST_TBL_ENTRY_VER and DER_BIT_TBL_ENTRY_VER macros
*/
LOCAL void init_der_tbl_entry(int line, const char* name, const char* verfrom, const char* verto, 
                              unsigned int tbltype, unsigned int scope)
{
    autogen_obj* entry = NULL;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, scope);

    /* check constant/bitmask name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* create new object */
    entry = autogen_obj_create(s_file, line, s_tbl->base.res, &s_tbl->base, sizeof(autogen_obj), AUTOGEN_OBJ_TBLENTRY, tbltype, 0, name, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* update properties and comments */
    init_update_properties_comments(entry);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    init_set_entry_version(line, entry, verfrom, verto);

    /* is the constant/bitmask defined for all needed versions? */
    {
        autogen_obj* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = (AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT);
        tbl_it.obj.name    = s_tbl->base.base_obj->name;
        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.ver         = &entry->ver;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            tbl_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        tbl = autogen_obj_find_in_list(&tbl_it, &s_tbl->base.res->tbl_list);
        /* iterate though all parent tables, of the derived table within the interval of the entry */
        while (tbl)
        {
            const autogen_ver* entry_ver = autogen_obj_ver_crop(&tbl->ver, &entry->ver);

            autogen_it entry_it = INIT_ITERATOR;

            entry_it.obj.name = name;
            entry_it.ver      = entry_ver;
            if (s_env->scope ? s_env->scope->feature_flags : NULL)
            {
                entry_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                entry_it.obj.feature_flags = s_env->scope->feature_flags;
            }

            if (!autogen_obj_list_verify_object_span(&entry_it, &tbl->child_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "The %s '%s' doesn't exist for all required versions", tbltype == AUTOGEN_TBL_DERCONST ? "constant":"bitmask", name);
            }

            tbl = autogen_obj_find_next_in_list(&tbl_it);
        }
    }
    
    /* add the table entry object to the table */
    autogen_obj_list_add_obj(&s_tbl->base.child_list, entry, AUTOGEN_ENV_ALL);
}

void init_der_bit_tbl_entry(int line, const char* name)
{
    init_der_tbl_entry(line, name, "", "", AUTOGEN_TBLENTRY_DERBIT, SCOPE_DER_BIT_TBL);
}

void init_der_bit_tbl_entry_ver(int line, const char* name, const char* verfrom, const char* verto)
{
    init_der_tbl_entry(line, name, verfrom, verto, AUTOGEN_TBLENTRY_DERBIT, SCOPE_DER_BIT_TBL);
}

void init_der_const_tbl_entry(int line, const char* name)
{
    init_der_tbl_entry(line, name, "", "", AUTOGEN_TBLENTRY_DERCONST, SCOPE_DER_CONST_TBL);
}

void init_der_const_tbl_entry_ver(int line, const char* name, const char* verfrom, const char* verto)
{
    init_der_tbl_entry(line, name, verfrom, verto, AUTOGEN_TBLENTRY_DERCONST, SCOPE_DER_CONST_TBL);
}



/*  Init function for the VALUE_LIMITS macro 
*/
void init_item_limits(int line,
                      unsigned int minval,  int minval_is_negative, const char* minvalstr, 
                      unsigned int maxval,  int maxval_is_negative, const char* maxvalstr, 
                      unsigned int excval1, int excval1_is_negative, const char* excvalstr1,
                      unsigned int excval2, int excval2_is_negative, const char* excvalstr2,
                      unsigned int excval3, int excval3_is_negative, const char* excvalstr3)
{
    if (strcmp(minvalstr, "LIMITS_NO_VALUE"))
    {
        prop_add_value(PROPERTY_ITEM_MINIMUM_VALUE, minval, minval_is_negative, minvalstr, line, FALSE);

        init_constant_add_unknown(line, minvalstr, minval, minvalstr, AUTOGEN_CONST_AUTOGENERATED, minval_is_negative, &s_env->scope->parent->ver, NULL);
    }
    if (strcmp(maxvalstr, "LIMITS_NO_VALUE"))
    {
        prop_add_value(PROPERTY_ITEM_MAXIMUM_VALUE, maxval, maxval_is_negative, maxvalstr, line, FALSE);

        init_constant_add_unknown(line, maxvalstr, maxval, maxvalstr, AUTOGEN_CONST_AUTOGENERATED, maxval_is_negative, &s_env->scope->parent->ver, NULL);
    }
    if (strcmp(excvalstr1, "LIMITS_NO_VALUE"))
    {
        prop_add_value(PROPERTY_ITEM_EXCEPTIONAL_VALUE, excval1, excval1_is_negative, excvalstr1, line, FALSE);

        init_constant_add_unknown(line, excvalstr1, excval1, excvalstr1, AUTOGEN_CONST_AUTOGENERATED, excval1_is_negative, &s_env->scope->parent->ver, NULL);
    }
    if (strcmp(excvalstr2, "LIMITS_NO_VALUE"))
    {
        prop_add_value(PROPERTY_ITEM_EXCEPTIONAL_VALUE, excval2, excval2_is_negative, excvalstr2, line, FALSE);

        init_constant_add_unknown(line, excvalstr2, excval2, excvalstr2, AUTOGEN_CONST_AUTOGENERATED, excval2_is_negative, &s_env->scope->parent->ver, NULL);
    }
    if (strcmp(excvalstr3, "LIMITS_NO_VALUE"))
    {
        prop_add_value(PROPERTY_ITEM_EXCEPTIONAL_VALUE, excval3, excval3_is_negative, excvalstr3, line, FALSE);

        init_constant_add_unknown(line, excvalstr3, excval3, excvalstr3, AUTOGEN_CONST_AUTOGENERATED, excval3_is_negative, &s_env->scope->parent->ver, NULL);
    }
}

void init_item_default_value(int line, unsigned int val, int val_is_negative, const char* val_str)
{
    prop_add_value(PROPERTY_ITEM_DEFAULT_VALUE, val, val_is_negative, val_str, line, FALSE);

    init_constant_add_unknown(line, val_str, val, val_str, AUTOGEN_CONST_AUTOGENERATED, val_is_negative, &s_env->scope->parent->ver, NULL);
}


/*  Init function for the SERVER_SET_SHORT_NAME macro 
*/
void init_server_set_short_name(int line, const char* name)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check name */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* set short names (upper case and lower case */
    {
        unsigned int i;
        char* shortname_u = pmd_heap_strdup(name);
        char* shortname_l = pmd_heap_strdup(name);

        for (i = 0; i < strlen(shortname_u); i++)
        {
            shortname_u[i] = (char) toupper(shortname_u[i]);
            shortname_l[i] = (char) tolower(shortname_l[i]);
        }

        s_res->resnameshort_u = shortname_u;
        s_res->resnameshort_l = shortname_l;
    }
}


/*  Init function for the SERVER_SET_TYPE macro 
*/
void init_server_set_type(int line, unsigned int type)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check server type */
    if (type == RESOURCE_ISI ||
        type == RESOURCE_ISI_MEDIA_CONTROL ||
        type == RESOURCE_MEDIA_MODULE)
    {
    }
    else if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
    {
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'type' is not valid");
    }

    /* check for redefinition of global resources */
    if (type == RESOURCE_ISI_MEDIA_CONTROL)
    {
        autogen_it res_it = INIT_ITERATOR;

        res_it.typemask     = AUTOGEN_OBJ_RES;
        res_it.subtypemask  = type;

        if (autogen_obj_find_in_list(&res_it, g_res_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Redefinition of resource type");
        }
    }

    /* if mm server, check that media control messages are inserted */
    if (type == RESOURCE_MEDIA_MODULE)
    {
        if (!util_get_unique_res(RESOURCE_ISI_MEDIA_CONTROL))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Media control resource is not defined, which is required");
        }
    }

    s_res->base.subtype = type;

    /* set resource configuration */
    s_res->conf = NULL;
    {
        int n;

        for (n = 0; n < AUTOGEN_RESOURCE_TYPES_MAX && !s_res->conf; n++)
        {
            if (g_res_conf[n].res_type == s_res->base.subtype)
            {
                s_res->conf = &g_res_conf[n];
            }
        }
    }

    /* set message rules */
    s_res->msg_id_size   = s_res->conf->msg_id_size;
    s_res->msg_id_offset = s_res->conf->msg_id_offset;

    s_res->submsg_id_size  = s_res->conf->submsg_id_size;
    s_res->submsg_id_offset = s_res->conf->submsg_id_offset;

    s_res->msg_length_size   = s_res->conf->msg_length_size;
    s_res->msg_length_offset = s_res->conf->msg_length_offset;

    /* set identifier based on configiuration identifier */
    s_res->identifier = pmd_constant_lookup_message_type_identifier(s_res->conf->msg_type);
}


/*  Init function for the SERVER_SET_COMMON_MESSAGE_SUPPORT macro 
*/
void init_server_set_common_message_support(int line, int supports_comm)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    if (supports_comm == TRUE)
    {
        s_res->base.flag |= AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES;
    }
    else
    {
        s_res->base.flag &= ~AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES;
    }
}

LOCAL void init_obj_ver_set(int line, autogen_res* res, autogen_obj* obj,
                            const char* verfrom, const char* verto, int type, unsigned int system, int allow_text)
{
    unsigned short from[3] = { 0, 0, 0 };
    unsigned short to[3] = { 256, 0, 0 };

    obj->ver.system = system;

    if (prop_has(&res->base, PROPERTY_ISI_VERSIONING_NOT_SUPPORTED))
    {
        /* Set version to all versions */
        autogen_obj_ver_set(&obj->ver, from, to);
        if (allow_text)
        {
            if (verfrom && verfrom[0])
            {
                obj->ver.ver_str = verfrom;
            }
        }
        else
        {
            if (verto && verto[0])
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Argument 'verto' is not valid. Must be \"\", as property 'PROPERTY_ISI_VERSIONING_NOT_SUPPORTED' is set.");
            }
            if (verfrom && verfrom[0])
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Argument 'verto' is not valid. Must be \"\", as property 'PROPERTY_ISI_VERSIONING_NOT_SUPPORTED' is set.");
            }
        }
    }
    else
    {
        /* set 'from' version */
        if (!init_check_version(verfrom, system, TRUE))
        {
            /* special test because of VRR server. Arghhhh!! */
            if (type == AUTOGEN_RESOURCE_VERSION)
            {
            }
            else if (system == AUTOGEN_VERSION_ISI)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Argument 'verfrom' is not valid. Must be on the format 'ZZZ.YYY', ZZZ and YYY < 256");
            }
            else if (system == AUTOGEN_VERSION_DSP)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Argument 'verfrom' is not valid. Must be on the format 'ZZZ.YYY.XXX', ZZZ, YYY and XXX < 256");
            }
        }
        else if (verfrom && verfrom[0])
        {
            from[0] = (unsigned short)atoi(verfrom);
            from[1] = (unsigned short)atoi(verfrom + 4);

            if (system == AUTOGEN_VERSION_DSP)
            {
                from[2] = (unsigned short)atoi(verfrom + 8);
            }
            else if (system == AUTOGEN_VERSION_ISI && res)
            {
                autogen_res_ver_add(res, from, system);
            }
        }

        /* set 'to' version */
        if (type == AUTOGEN_VERSION_INTERVAL)
        {
            if (!init_check_version(verto, system, TRUE))
            {
                if (system == AUTOGEN_VERSION_ISI)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Argument 'verto' is not valid. Must be on the format 'ZZZ.YYY', ZZZ and YYY < 256");
                }
                else if (system == AUTOGEN_VERSION_DSP)
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Argument 'verto' is not valid. Must be on the format 'ZZZ.YYY.XXX', ZZZ, YYY and XXX < 256");
                }
            }
            else if (verto && verto[0])
            {
                to[0] = (unsigned short)atoi(verto);
                to[1] = (unsigned short)atoi(verto + 4);

                if (system == AUTOGEN_VERSION_DSP)
                {
                    to[2] = (unsigned short)atoi(verto + 8);
                }
                else if (system == AUTOGEN_VERSION_ISI && res)
                {
                    autogen_res_ver_add(res, to, system);

                    if (!verfrom || !verfrom[0])
                    {
                        autogen_res_ver_add(res, from, system);
                    }
                }
            }

            if (autogen_obj_ver_set(&obj->ver, from, to) != AUTOGEN_OK)
            { 
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Invalid specified version interval");
            }
        }
        else
        {
            /* check the 'from' version by applying the 'from' and maximum 'to' version */
            if (autogen_obj_ver_set(&obj->ver, from, to) != AUTOGEN_OK)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Invalid specified version interval");
            }

            /* now apply the version (as from and to version) to provoke the version type exact */
            autogen_obj_ver_set(&obj->ver, from, from);
        }
    }
}

LOCAL autogen_item* init_item_create(int line, unsigned int size, unsigned int subtype, unsigned int flag, const char* varname, const char* parname, autogen_feature *feature_flag)
{
    s_item = (autogen_item*)autogen_obj_create(s_file, line, s_res, s_env->scope->parent, size, AUTOGEN_OBJ_ITEM, subtype, 0, NULL, feature_flag);

    s_item->varname   = varname;
    s_item->parname   = parname;
    s_item->base.flag = flag;
    s_item->agg_n     = 1;
    s_item->agg_type  = AGG_TYPE_FIXED_SINGLE;

    s_item->offset      = 0;
    s_item->offset_type = AUTOGEN_ITEM_OFFSET_UNDEFINED;

    /* update comments and properties */
    init_update_properties_comments((autogen_obj*)s_item);

    return s_item;
}


LOCAL void init_item_add(autogen_item* item, autogen_feature *feature_flag)
{
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    feature_flag;
#endif

    item->seq = s_seq;
    item->special_number_type = (unsigned int)prop_get_value_default(&item->base, PROPERTY_PMD_NUMBER_SPECIAL_TYPE, item->special_number_type);

    /* add item to list of items */
    autogen_obj_list_add_obj(&s_env->scope->parent->child_list, &item->base, AUTOGEN_ENV_ALL);

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        autogen_item* merge = (autogen_item*)item->base.parent;

        char str_bits[65] = "";
        int i;


        for (i = 0; i < abs(merge->length); i++)
        {
            str_bits[i] = '-';
            
            if (i >= s_merge_length - abs(item->length) && i < s_merge_length)
            {
                str_bits[i] = 'x';
            }
            else
            {
                str_bits[i] = '-';
            }

            str_bits[i+1] = 0;
        }

        item->bit_pattern  = pmd_heap_strdup(str_bits);
        item->base.flag   |= AUTOGEN_ITEM_IS_PART_OF_MERGE;
    }

    /* sequence dependent updates */
    if (s_seq)
    {
        /* check if item is placed in an AS_MANY_AS_POSSIBLE / OPTIONAL structure or unknown length */
        if ((s_seq->base.flag & AUTOGEN_SEQ_HAS_ASMANYASPOSSIBLE) || (s_seq->base.flag & AUTOGEN_SEQ_HAS_UNKNOWN_LENGTH))
        {
            if (item->base.parent->type != AUTOGEN_OBJ_ITEM &&
                (item->base.subtype != AUTOGEN_ITEM_FILLER || 
                (item->agg_type == AGG_TYPE_FIXED_SINGLE ||
                item->agg_type == AGG_TYPE_FIXED_MULTIPLE)))
            {
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
                util_error_line(s_file, item->base.file_line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
                    "Item is placed after an array of unknown size or optional element, which is not allowed");
#else
				/* If item belongs to PN_DSP_AUDIO then let it pass.          */
				/* Decoding will fail, but format has been approved ages ago. */
				/* Don't issue any PCP errors on this!                        */
                const autogen_obj* parent = util_get_base_parent(&item->base);
				if (strcmp(parent->parent->name, "PN_DSP_AUDIO"))
				{
                    util_error_line(s_file, item->base.file_line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Item is placed after an array of unknown size or optional element, which is not allowed");
				}
#endif
            }
        }

        /* set dynamic flags */
        if (s_seq->base.flag & AUTOGEN_SEQ_IS_DYNAMIC)
        {
            if (!prop_has((autogen_obj*)s_res, PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS))
            {
                item->base.flag |= AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;
            }
        }

        /* if item is dynamic, now sequence is dynamic (unless we are in a choice/case) */
        if (item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT ||
            item->agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE ||
            item->agg_type == AGG_TYPE_DYNAMIC_OPTIONAL ||
            item->agg_type == AGG_TYPE_DYNAMIC_REF ||
            item->agg_type == AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH ||
            item->agg_type == AGG_TYPE_DYNAMIC_ZEROTERMINATED)
        {
            if (item->base.parent->type != AUTOGEN_OBJ_ITEM || 
                item->base.parent->subtype != AUTOGEN_ITEM_CASE ||
                (item->base.parent->flag & AUTOGEN_CASE_DEFAULT))
            {
                s_seq->base.flag |= AUTOGEN_SEQ_IS_DYNAMIC;

                if (item->agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE ||
                    item->agg_type == AGG_TYPE_DYNAMIC_OPTIONAL)
                {
                    s_seq->base.flag |= AUTOGEN_SEQ_HAS_ASMANYASPOSSIBLE;
                }
                if (item->agg_type == AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH)
                {
                    s_seq->base.flag |= AUTOGEN_SEQ_HAS_UNKNOWN_LENGTH;
                }
            }
        }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
        /* add XX_ANY_SIZE constant */
        if (!(s_seq->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR) &&
            prop_has((autogen_obj*)item, PROPERTY_ISIHDR_ARRAY_MARKER) &&
            (prop_get_value_default((autogen_obj*)item, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_ANYSIZE) == ISIHDR_MARKER_ANYSIZE ||
            prop_get_value_default((autogen_obj*)item, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_ANYSIZE) == ISIHDR_MARKER_ANYSIZE_BYTE ||
            prop_get_value_default((autogen_obj*)item, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_ANYSIZE) == ISIHDR_MARKER_ANYSIZE_WORD))
        {
            if (!(s_seq->base.res->base.flag & AUTOGEN_RES_HAS_ANY_SIZE_CONSTANT))
            {
                char* strname = pmd_heap_alloc(strlen(s_seq->base.res->resnameshort_u) + 12);

                autogen_ver ver = INIT_VERSION_ALL;
                autogen_obj* cons;
                autogen_it const_it = INIT_ITERATOR;

                sprintf(strname, "%s_ANY_SIZE", s_seq->base.res->resnameshort_u);

                /* add the constant */
                init_constant_add(item->base.file_line, strname, 1, AUTOGEN_CONST_DEFINED, AUTOGEN_CONST_SIGNED | AUTOGEN_OBJ_IS_NOT_GENERATED_HTML, &ver, feature_flag);

                const_it.typemask = AUTOGEN_OBJ_CONST;
                const_it.obj.name = strname;
                const_it.idcrit   = AUTOGEN_OBJ_ID_EXACT;
                const_it.obj.id   = 1;
                if (feature_flag)
                {
                    const_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    const_it.obj.feature_flags = feature_flag;
                }

                cons = autogen_obj_find_in_list(&const_it, &s_seq->base.res->const_list);
                if (cons && !cons->cmt_list)
                {
                    cons->cmt_list = autogen_cmt_create(COMMENT_TEXT, 0, "", "", "",
                        "constant for variable-length definitions");
                }

                s_seq->base.res->base.flag |= AUTOGEN_RES_HAS_ANY_SIZE_CONSTANT;
            }
        }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    }

    s_item = NULL;
}



LOCAL unsigned int init_check_order(int line, unsigned int ordermask, unsigned int order, int length, int allow_24)
{
#if (PMD_FILE_FORMAT >= 501)
    length;
    allow_24;
#endif
    if (order == BE)
    {
        order = AUTOGEN_ORDER_BE;
    }
    else if (order == LE)
    {
        order = AUTOGEN_ORDER_LE;
    }
    else if (order == NONE)
    {
        order = AUTOGEN_ORDER_BCD_NONE;
    }
    else if (order == NSW)
    {
        order = AUTOGEN_ORDER_BCD_NSW;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'order' is not valid");
    }

    if (!(order & ordermask))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'order' is not valid in this context");
    }

#if (PMD_FILE_FORMAT >= 501)
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        unsigned int merge_order = ((autogen_item*)s_env->scope->parent)->order;
        if (order != merge_order)
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'order' is not valid in this context. All elements within a merged field must have the same order as MERGE_BEGIN macro");
    }
#else
    /* data order LE can't be used with an element in a merged field */
    if (s_env->scope->scope == SCOPE_MERGE && order == AUTOGEN_ORDER_LE)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'order' is not valid in this context. 'LE' can't be used within a merged field");
    }
    else
    {
    /* data order LE can only be used with bit sizes (-)16, (-)32 and (-)64 */
    if (allow_24)
    {
        if (abs(length) == 8 && order == AUTOGEN_ORDER_LE) /* Typically when NATIVE has been specified */
        {
            order = AUTOGEN_ORDER_BE;
        }
        else if (abs(length) != 16 && abs(length) != 24 && abs(length) != 32 && abs(length) != 64 && order == AUTOGEN_ORDER_LE)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'order' is not valid in this context. 'LE' can only be used with bit sizes (-)16, (-)24, (-)32, or (-)64");
        }
    }
    else if (abs(length) != 8 && abs(length) != 16 && abs(length) != 32 && abs(length) != 64 && order == AUTOGEN_ORDER_LE)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'order' is not valid in this context. 'LE' can only be used with bit sizes (-)8, (-)16, (-)32 or (-)64");
    }
    } 
#endif
    return order;
}


LOCAL void init_add_obj_relation(autogen_obj* obj, autogen_obj* refobj, autogen_ver* ver_range, autogen_feature *featureflag)
{
    autogen_obj* objrel;

    /* create an object relation */
    objrel = autogen_obj_create(obj->file_name, obj->file_line, refobj->res, refobj, sizeof(autogen_obj), AUTOGEN_OBJ_REL, obj->type, 0, obj->name, featureflag);
    objrel->ptr = obj;

    /* copy common object flags to relation */
    objrel->flag = obj->flag & AUTOGEN_OBJ_COMMON_FLAGS_ALL;

    memcpy(&objrel->ver, autogen_obj_ver_crop(&obj->ver, &refobj->ver), sizeof(autogen_ver));

    if (ver_range)
    {
        memcpy(&objrel->ver, autogen_obj_ver_crop(&objrel->ver, ver_range), sizeof(autogen_ver));
    }

    if (refobj->related_obj.n_obj == 0)
    {
        autogen_obj_list_init(&refobj->related_obj, refobj, AUTOGEN_OBJ_LIST_SORTED_BY_TYPE_AND_NAME, 5);
    }

    /* add the object relation to the table */
    autogen_obj_list_add_obj(&refobj->related_obj, objrel, AUTOGEN_ENV_NONE);
}


#ifdef AUTOGEN_ENVIRONMENT_LOCAL
#if (PMD_FILE_FORMAT >= 600)
LOCAL void          init_add_def(int line, unsigned int type, const char* name, unsigned long long id, unsigned int flag, 
                                 autogen_ver* ver, autogen_cmt* cmt, const autogen_prop* alias_prop, autogen_feature *feature_flag)
#else
LOCAL void init_add_def(int line, unsigned int type, const char* name,  unsigned int id, 
                        unsigned int flag, autogen_ver* ver, autogen_cmt* cmt,
                        const autogen_prop* alias_prop, autogen_feature *feature_flag)
#endif
{
    autogen_ver it_ver = { AUTOGEN_OBJ_VERSION_INTERVAL, AUTOGEN_VERSION_ISI, 0, 0, 0, 0, 0, 0 };
    cmt;

    it_ver.system = ver->system;

    /* is name allowed */
    if (type == AUTOGEN_DEF_NAME)
    {
        autogen_it def_it = INIT_ITERATOR;

        def_it.typemask    = AUTOGEN_OBJ_DEF;
        def_it.subtypemask = AUTOGEN_DEF_ANY;
        def_it.obj.name    = name;
        def_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        def_it.ver         = ver;
        if (feature_flag)
        {
            def_it.featureflagcrit = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            def_it.obj.feature_flags = feature_flag;
        }

        if (autogen_obj_find_in_list(&def_it, &s_res->def_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Object '%s' conflicts with another definition", name);
        }
    }
    /* is value allowed */
    else if (type == AUTOGEN_DEF_CONST)
    {
        /* does constant name conflict with another definition? */
        {
            autogen_it def_it = INIT_ITERATOR;

            def_it.typemask    = AUTOGEN_OBJ_DEF;
            def_it.subtypemask = AUTOGEN_DEF_NAME;
            def_it.obj.name    = name;
            def_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            def_it.ver         = ver;
            if (feature_flag)
            {
                def_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                def_it.obj.feature_flags = feature_flag;
            }

            if (autogen_obj_find_in_list(&def_it, &s_res->def_list)) 
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Constant '%s' conflicts with another definition", name);
            }
        }

        /* does constant value conflict with another constant? */
        {
            autogen_it def_it = INIT_ITERATOR;

            def_it.typemask    = AUTOGEN_OBJ_DEF;
            def_it.subtypemask = AUTOGEN_DEF_CONST;
            def_it.obj.name    = name;
            def_it.idcrit      = AUTOGEN_OBJ_ID_NOT;
            def_it.obj.id      = id;
            def_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            def_it.ver         = ver;
            if (feature_flag)
            {
                def_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                def_it.obj.feature_flags = feature_flag;
            }

            if (autogen_obj_find_in_list(&def_it, &s_res->def_list))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Constant '%s' conflicts with other defined constant", name);
            }
        }

        /* is the constant already defined? */
        {
            autogen_it def_it = INIT_ITERATOR;

            def_it.typemask    = AUTOGEN_OBJ_DEF;
            def_it.subtypemask = AUTOGEN_DEF_CONST;
            def_it.obj.name    = name;
            def_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
            def_it.obj.id      = id;
            def_it.vercrit     = AUTOGEN_OBJ_VERSION_COVER_SINGLE;
            def_it.ver         = ver;
            if (feature_flag)
            {
                def_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                def_it.obj.feature_flags = feature_flag;
            }

            if (autogen_obj_find_in_list(&def_it, &s_res->def_list))
            {
                return;
            }
        }
    }

    /* try to merge the constant to an existing constant */
    if (type == AUTOGEN_DEF_CONST)
    {
        /* Merge definition with existing definitions */
        {
            autogen_def* def_trav;
            autogen_def* def_last = NULL;
            autogen_it def_it = INIT_ITERATOR;

            def_it.typemask    = AUTOGEN_OBJ_DEF;
            def_it.subtypemask = AUTOGEN_DEF_CONST;
            def_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
            def_it.obj.id      = id;
            def_it.obj.name    = name;
            if (feature_flag)
            {
                def_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                def_it.obj.feature_flags = feature_flag;
            }

            def_trav = (autogen_def*)autogen_obj_find_in_list(&def_it, &s_res->def_list);
            while (def_trav)
            {
                /* can last definition and current definitions be merged? 
                - if so, extend the version of the last definition and remove this instance.
                */
                if (def_last && autogen_ver_comp(def_trav->base.ver.from, def_last->base.ver.to) & AUTOGEN_VER_EQUAL)
                {
                    autogen_obj_ver_set(&def_last->base.ver, def_last->base.ver.from, def_trav->base.ver.to);

                    autogen_obj_list_delete_obj(&s_res->def_list, &def_trav->base);
                    return;
                }

                /* can the new constant be merged at the end of this constant? */
                if (autogen_ver_comp(ver->from, def_trav->base.ver.to) & AUTOGEN_VER_EQUAL)
                {
                    autogen_obj_ver_set(&def_trav->base.ver, def_trav->base.ver.from, ver->to);
                }
                /* can the new constant be merged at the beginning of this constant? */
                else if (autogen_ver_comp(ver->to, def_trav->base.ver.from) & AUTOGEN_VER_EQUAL)
                {
                    autogen_obj_ver_set(&def_trav->base.ver, ver->from, def_trav->base.ver.to);
                }
                /* is the old constant entirely included in the new? */
                else if (autogen_obj_ver_is_included(ver, &def_trav->base.ver))
                {
                    autogen_obj_ver_set(&def_trav->base.ver, ver->from, ver->to);
                }

                def_last = def_trav;
                def_trav = (autogen_def*)autogen_obj_find_next_in_list(&def_it);
            }
        }

        /* create new definition */
        {
            autogen_def* def_trav;
            autogen_it def_it = INIT_ITERATOR;

            def_it.typemask    = AUTOGEN_OBJ_DEF;
            def_it.subtypemask = AUTOGEN_DEF_CONST;
            def_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
            def_it.obj.id      = id;
            def_it.obj.name    = name;
            def_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            def_it.ver         = ver;
            if (feature_flag)
            {
                def_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                def_it.obj.feature_flags = feature_flag;
            }

            /* find first definition of that name and id */
            def_trav = (autogen_def*)autogen_obj_find_in_list(&def_it, &s_res->def_list);

            /* initialize lower part of test version number */
            it_ver.from[0] = ver->from[0];
            it_ver.from[1] = ver->from[1];
            it_ver.from[2] = ver->from[2];

            /* continue until iterator version is equal or greater than the original version of definition */
            while (autogen_ver_comp(it_ver.to, ver->to) & AUTOGEN_VER_NEWER)
            {
                int create_obj = FALSE;

                /* if an object exists, compare the version intervals and 
                create an object with the version interval that is the difference
                between the two...
                */
                if (def_trav)
                {
                    /* should a definition be created before the current object ? */
                    if (autogen_ver_comp(it_ver.from, def_trav->base.ver.from) & AUTOGEN_VER_NEWER)
                    {
                        create_obj = TRUE;

                        it_ver.to[0] = def_trav->base.ver.from[0];
                        it_ver.to[1] = def_trav->base.ver.from[1];
                        it_ver.to[2] = def_trav->base.ver.from[2];
                    }
                }
                /* if no object exists, create an object with the version interval equal to the rest of the interval */
                else
                {
                    /* should a definition be created before the current object ? */
                    if (autogen_ver_comp(it_ver.from, ver->to) & AUTOGEN_VER_NEWER)
                    {
                        create_obj = TRUE;

                        it_ver.to[0] = ver->to[0];
                        it_ver.to[1] = ver->to[1];
                        it_ver.to[2] = ver->to[2];
                    }
                }

                /* create and add definition object */
                if (create_obj)
                {
                    /* create definition object */
                    autogen_def* def_new = (autogen_def*)autogen_obj_create(NULL, 0, s_res, &s_res->base, sizeof(autogen_def), AUTOGEN_OBJ_DEF, type, id, name, feature_flag);

                    while (alias_prop)
                    {
                        prop_add_to_object((autogen_obj*)def_new, prop_copy(alias_prop), NULL);

                        alias_prop = prop_find_next(alias_prop);
                    }

                    def_new->is_generated   = FALSE;
                    def_new->base.flag     |= flag;

                    /* set version */
                    autogen_obj_ver_set(&def_new->base.ver, it_ver.from, it_ver.to);

                    /* add object to server */
                    autogen_obj_list_add_obj(&s_res->def_list, &def_new->base, AUTOGEN_ENV_NONE);
                }

                if (def_trav)
                {
                    /* update the test version interval */
                    it_ver.to[0] = def_trav->base.ver.to[0];
                    it_ver.to[1] = def_trav->base.ver.to[1];
                    it_ver.to[2] = def_trav->base.ver.to[2];

                    /* find the next object */
                    def_trav = (autogen_def*)autogen_obj_find_next_in_list(&def_it);
                }

                it_ver.from[0] = it_ver.to[0];
                it_ver.from[1] = it_ver.to[1];
                it_ver.from[2] = it_ver.to[2];
            }
        }
    }
    /* else add definition name */
    else
    {
        /* create definition object */
        autogen_def* def_new = (autogen_def*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_def), AUTOGEN_OBJ_DEF, type, 0, name, feature_flag);

        if (alias_prop)
        {
            prop_add_to_object((autogen_obj*)def_new, prop_copy(alias_prop), NULL);
        }

        def_new->is_generated   = FALSE;
        def_new->base.flag     |= flag;

        /* set version */
        autogen_obj_ver_set(&def_new->base.ver, ver->from, ver->to);

        /* add object to server */
        autogen_obj_list_add_obj(&s_res->def_list, &def_new->base, AUTOGEN_ENV_NONE);
    }
}
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

int s_included = 0;
int s_not_included = 0;

LOCAL void init_common_seq_create(int line, unsigned int type, unsigned int subtype, unsigned int id, unsigned int flag, const char* name, const char* verfrom, const char* verto, autogen_feature *feature_flag)
{
    /* create seq object */
    s_seq = (autogen_seq*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_seq), type, subtype, id, name, feature_flag);

    if (type == AUTOGEN_OBJ_MSG_BASE)
    {
        autogen_obj_list_init(&s_seq->submsg_list, &s_seq->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);
    }
    autogen_obj_list_init(&s_seq->base.child_list, &s_seq->base, 0, 10);

    s_seq->ref_handle.parent = &s_seq->base;
    s_seq->base.flag = flag;

    /* check and set version numbers */
    init_obj_ver_set(line, s_res, (autogen_obj*)s_seq, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    /* if the sequence is a structure, set flag and create definition names */
    if (!(flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
    {
        /* set definition property */
        {
            char* def_name = pmd_heap_alloc(strlen(name) + 10);

            strcpy(def_name, name);
            strcat(def_name, "_STR");

            prop_add_string_default(PROPERTY_ISIHDR_STRUCT_NAME, def_name);
        }

        /* generate default structure length constant name */
        {
            char* len_name = pmd_heap_alloc(strlen(name) + 15);

            strcpy(len_name, "SIZE_");
            strcat(len_name, name);
            strcat(len_name, "_STR");

            prop_add_string_default(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, len_name);
        }
    }

    /* update properties and comments */
    init_update_properties_comments(&s_seq->base);
}


LOCAL void init_item_add_relations(autogen_item* item, autogen_ver* ver, autogen_feature *featureflag)
{
    if (s_seq && s_seq->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT)
    {
        return;
    }

    switch (item->base.subtype)
    {
    case AUTOGEN_ITEM_VALUE:
    case AUTOGEN_ITEM_REF:
        {
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
            autogen_item_value* value = (autogen_item_value*)item;

            if (s_seq && value->pres.type & AUTOGEN_PRESENTATION_CONST)
            {
                autogen_tbl* tbl;
                autogen_it tbl_it = INIT_ITERATOR;

                tbl_it.typemask = AUTOGEN_OBJ_TBL;
                tbl_it.obj.name = value->pres.tblname;
                tbl_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                tbl_it.ver      = ver;
                if (featureflag)
                {
                    tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    tbl_it.obj.feature_flags = featureflag;
                }

                tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &s_seq->base.res->tbl_list);
                while (tbl)
                {
                    /* add a relation from the table (both derived and original) to the s_parent */
                    init_add_obj_relation((autogen_obj*)s_seq, (autogen_obj*)tbl, NULL, featureflag);
                    if (tbl != tbl->orgtbl)
                    {
                        init_add_obj_relation((autogen_obj*)s_seq, (autogen_obj*)tbl->orgtbl, NULL, featureflag);
                    }

                    tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
                }
            }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
        }
        break;

    case AUTOGEN_ITEM_LST:
        {
            if ((item->base.flag & AUTOGEN_LST_SB) && (item->base.flag & AUTOGEN_LST_SBDATA) && s_seq)
            {
                autogen_seq_ref* ref = (autogen_seq_ref*)autogen_obj_get_first_in_list(&item->base.child_list);
                while (ref)
                {
                    init_add_obj_relation((autogen_obj*)s_seq, (autogen_obj*)ref->seqptr, NULL, featureflag);

                    /* find next subblock reference for the list */
                    ref = (autogen_seq_ref*)ref->base.next;
                }
            }
        }
        break;

    case AUTOGEN_ITEM_STRUCT:
        if (s_seq)
        {
            autogen_item_struct* str_item = (autogen_item_struct*)item;

            autogen_obj* str;
            autogen_it str_it = INIT_ITERATOR;

            str_it.typemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB;
            str_it.obj.name = str_item->seqname;
            str_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            str_it.ver      = ver;
            if (featureflag)
            {
                str_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                str_it.obj.feature_flags = featureflag;
            }

            str = autogen_obj_find_in_list(&str_it, &s_seq->base.res->seq_list);
            while (str)
            {
                init_add_obj_relation((autogen_obj*)s_seq, str, NULL, featureflag);

                str = autogen_obj_find_next_in_list(&str_it);
            }
        }
        break;

    case AUTOGEN_ITEM_MERGE:
        {
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
            autogen_obj* merge_item = autogen_obj_get_first_in_list(&item->base.child_list);
            while (merge_item)
            {
                init_item_add_relations((autogen_item*)merge_item, ver, featureflag);

                merge_item = merge_item->next;
            }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
        }
        break;

    case AUTOGEN_ITEM_CHOICE:
        {
            autogen_item_choice* choice = (autogen_item_choice*)item;
            autogen_obj* cas = autogen_obj_get_first_in_list(&choice->base.base.child_list);
            while (cas)
            {
                autogen_obj* case_item = autogen_obj_get_first_in_list(&cas->child_list);
                while (case_item)
                {
                    init_item_add_relations((autogen_item*)case_item, &cas->ver, featureflag);

                    case_item = case_item->next;
                }

                cas = cas->next;
            }

            /* add table relation for forward choices */
            if (s_seq && (choice->base.base.flag & AUTOGEN_CHOICE_FORWARD))
            {
                autogen_tbl* tbl;
                autogen_it tbl_it = INIT_ITERATOR;

                tbl_it.typemask = AUTOGEN_OBJ_TBL;
                tbl_it.obj.name = choice->tblname;
                tbl_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                tbl_it.ver      = ver;
                if (featureflag)
                {
                    tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                    tbl_it.obj.feature_flags = featureflag;
                }

                tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &choice->tblres->tbl_list);
                while (tbl)
                {
                    /* add a relation from the table (both derived and original) to the s_parent */
                    init_add_obj_relation((autogen_obj*)s_seq, (autogen_obj*)tbl, NULL, featureflag);
                    if (tbl != tbl->orgtbl)
                    {
                        init_add_obj_relation((autogen_obj*)s_seq, (autogen_obj*)tbl->orgtbl, NULL, featureflag);
                    }

                    tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
                }
            }
        }
        break;

    case AUTOGEN_ITEM_CASE:
    case AUTOGEN_ITEM_TIMESTAMP:
    case AUTOGEN_ITEM_RANGE:
    case AUTOGEN_ITEM_RANGE_ENTRY:
    case AUTOGEN_ITEM_POINTER:
    case AUTOGEN_ITEM_STRING:
    case AUTOGEN_ITEM_FILLER:
    case AUTOGEN_ITEM_BLOCK:
        {
        }
        break;

    default:
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in init_item_add_relations(). item->base.subtype is 0x%8.8X", 
                item->base.subtype);
        }
        break;
    }
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL void init_constant_add_unknown(int line, const char* name, unsigned long long id, const char* idstr, unsigned int const_type, int is_negative, autogen_ver* ver, autogen_feature *feature_flag)
#else
LOCAL void init_constant_add_unknown(int line, const char* name, unsigned int id, const char* idstr, unsigned int const_type, int is_negative, autogen_ver* ver, autogen_feature *feature_flag)
#endif
{
    if (!util_is_predefined_constant(name))
    {
        unsigned int len;

        for (len = 1; len < strlen(idstr); len++)
        {
            if (idstr[len] == ' ' || idstr[len] == '(' || idstr[len] == ')' || idstr[len] == '-')
            {
                return;
            }
        }

        if (strlen(idstr) > 1 && idstr[0] == '0' && (idstr[1] == 'x' || idstr[1] == 'X'))
        {
#if (PMD_FILE_FORMAT >= 600)
            if (strlen(idstr) > 10) /* Greater than 0xFFFFFFFF */
            {
                init_constant_add(line, name, id, const_type, AUTOGEN_CONST_UNSIGNED_DDWORD, ver, feature_flag);
            }
            else 
#endif
            if (strlen(idstr) > 6)
            {
                init_constant_add(line, name, id, const_type, AUTOGEN_CONST_UNSIGNED_DWORD, ver, feature_flag);
            }
            else if (strlen(idstr) > 4)
            {
                init_constant_add(line, name, id, const_type, AUTOGEN_CONST_UNSIGNED_WORD, ver, feature_flag);
            }
            else
            {
                init_constant_add(line, name, id, const_type, AUTOGEN_CONST_UNSIGNED_BYTE, ver, feature_flag);
            }
        }
        else
        {
            init_constant_add(line, name, id, const_type, is_negative ? AUTOGEN_CONST_SIGNED : AUTOGEN_CONST_UNSIGNED_DEC, ver, feature_flag);
        }
    }
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL void init_constant_add(int line, const char* name, unsigned long long id, unsigned int const_type, unsigned int flag, autogen_ver* ver, autogen_feature *feature_flag)
#else
LOCAL void init_constant_add(int line, const char* name, unsigned int id, unsigned int const_type, unsigned int flag, autogen_ver* ver, autogen_feature *feature_flag)
#endif
{
    autogen_ver it_ver = { AUTOGEN_OBJ_VERSION_INTERVAL, 0, 0, 0, 0 };
    autogen_obj* cons;
    autogen_obj* const_trav;


    /* is name a constant at all? */
    if (!check_c_name(s_file, 0, "", name, CHECK_NAME_NO_FLAGS))
    {
        return;
    }

    /* is constant conflicting with other constants? */
    {
        autogen_it cons_it = INIT_ITERATOR;

        cons_it.typemask = AUTOGEN_OBJ_CONST;
        cons_it.idcrit   = AUTOGEN_OBJ_ID_NOT;
        cons_it.obj.id   = id;
        cons_it.obj.name = name;
        cons_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        cons_it.ver      = ver;
        if (feature_flag)
        {
            cons_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            cons_it.obj.feature_flags = feature_flag;
        }

        if (autogen_obj_find_in_list(&cons_it, &s_res->const_list))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Constant '%s' is already defined with different value", name);
        }
    }

    /* is the constant already defined? */
    {
        autogen_it cons_it = INIT_ITERATOR;

        cons_it.typemask = AUTOGEN_OBJ_CONST;
        cons_it.idcrit   = AUTOGEN_OBJ_ID_EXACT;
        cons_it.obj.id   = id;
        cons_it.obj.name = name;
        cons_it.vercrit  = AUTOGEN_OBJ_VERSION_COVER_SINGLE;
        cons_it.ver      = ver;
        if (feature_flag)
        {
            cons_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            cons_it.obj.feature_flags = feature_flag;
        }

        cons = autogen_obj_find_in_list(&cons_it, &s_res->const_list);
        if (cons)
        {
            /* update the type of the constant and return */
            cons->subtype |= const_type;

            /* if a constant object is defined */
            if (s_object && const_type == AUTOGEN_CONST_DEFINED)
            {
                init_update_properties_comments((autogen_obj*)cons);
            }

            return;
        }
    }

    /* add the constant for all non-overlapping intervals */
    {
        autogen_it cons_it = INIT_ITERATOR;

        cons_it.typemask = AUTOGEN_OBJ_CONST;
        cons_it.obj.name = name;
        cons_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        cons_it.ver      = ver;
        if (feature_flag)
        {
            cons_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            cons_it.obj.feature_flags = feature_flag;
        }

        const_trav = autogen_obj_find_in_list(&cons_it, &s_res->const_list);

        /* initialize lower part of iterator version number */
        it_ver.from[0] = ver->from[0];
        it_ver.from[1] = ver->from[1];
        it_ver.from[2] = ver->from[2];

        /* continue until iterator version is equal or greater than 
           the original version of the new constant 
        */
        while (autogen_ver_comp(it_ver.to, ver->to) & AUTOGEN_VER_NEWER)
        {
            int create_const = FALSE;

            /* if a constant exists, compare the version intervals and 
               create a constant with the version interval that is the difference
               between the two...
            */
            if (const_trav)
            {
                /* should a definition be created before the current object ? */
                if (autogen_ver_comp(it_ver.from, const_trav->ver.from) & AUTOGEN_VER_NEWER)
                {
                    create_const = TRUE;

                    it_ver.to[0] = const_trav->ver.from[0];
                    it_ver.to[1] = const_trav->ver.from[1];
                    it_ver.to[2] = const_trav->ver.from[2];
                }
            }
            /* if no constant exists, create a constant with the version interval
               equal to the rest of the interval
            */
            else
            {
                /* should a definition be created before the current object ? */
                if (autogen_ver_comp(it_ver.from, ver->to) & AUTOGEN_VER_NEWER)
                {
                    create_const = TRUE;

                    it_ver.to[0] = ver->to[0];
                    it_ver.to[1] = ver->to[1];
                    it_ver.to[2] = ver->to[2];
                }
            }

            /* create and add constant object */
            if (create_const)
            {
                /* create constant object */
                autogen_const* constant = (autogen_const*)autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_const), AUTOGEN_OBJ_CONST, 0, id, name, feature_flag);

                constant->base.flag |= flag;

                /* update properties and comments */
                if (const_type == AUTOGEN_CONST_DEFINED)
                {
                    init_update_properties_comments(&constant->base);
                }

                /* set version */
                autogen_obj_ver_set(&constant->base.ver, it_ver.from, it_ver.to);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
                /* verify that definition is not already defined */
                if (!(constant->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR))
                {
                    init_add_def(line, AUTOGEN_DEF_CONST, name, id, flag, &constant->base.ver, constant->base.cmt_list, NULL, feature_flag);
                }
#endif
                if (s_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* Object belongs to Legacy part of resource*/
                {
                    constant->base.flag |= AUTOGEN_OBJ_IS_LEGACY;
                }

                /* add constant to server */
                autogen_obj_list_add_obj(&s_res->const_list, &constant->base, AUTOGEN_ENV_NONE);
            }

            if (const_trav)
            {
                /* update the iterator version interval */
                it_ver.to[0] = const_trav->ver.to[0];
                it_ver.to[1] = const_trav->ver.to[1];
                it_ver.to[2] = const_trav->ver.to[2];

                /* find the next constant */
                const_trav = autogen_obj_find_next_in_list(&cons_it);
            }

            it_ver.from[0] = it_ver.to[0];
            it_ver.from[1] = it_ver.to[1];
            it_ver.from[2] = it_ver.to[2];
        }
    }
}

/*  Checks the actual value of the common macro argument 'length'. 'type'
    indicates whether a negative value of 'length' is legal (indicating a 
    signed value). If the check fails, the application aborts. The following 
    is checked:
    - 'length' must be positive if 'type' is 'Signed'
    - 'length' must be 8, 16 or 32, if macro is placed outoside a Merge Scope
    - the absolute value of 'length' must be between 1 and 32 when placed in a
     Merge Scope 
*/
LOCAL void init_check_length(int line, int length, int sign, int allow_64, int allow_24)
{
    unsigned int length_us = abs(length);


    if (!sign && length < 0)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is out of range. Value must be unsigned");
    }

    /* length can never be -1 */
    if (length == -1)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is out of range");
    }

    /* outside a merged field, length must be (-)8, (-16), (-)32 or (-)64 bits */
    if (s_env->scope->scope != SCOPE_MERGE)
    {
        if (length_us == 64 && allow_64)
        {
        }
        else if (length_us == 24 && allow_24)
        {
        }
        else if (length_us != 8 && length_us != 16 && length_us != 32)
        {
            if (allow_64 && (prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_64_BITS)))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Argument 'length' is out of range. Value must be one of the following: (-)8, (-)16, (-)32 or (-)64");
            }
            else
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Argument 'length' is out of range. Value must be one of the following: (-)8, (-)16, or (-)32");
            }
        }
    }
    /* in a merged field, length must be 1, (-)2, ... (-)31 bits, (-)63 bits if allow_64 */
    else
    if (allow_64)
    {
        if (length_us == 0 || length_us > 63)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'length' is out of range. Value must be between 1 and 63");
        }
    }
    else
    {
        if (length_us == 0 || length_us > 31)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'length' is out of range. Value must be between 1 and 31");
        }
    }
}

LOCAL int init_check_version(const char* version, unsigned int system, int allow_empty)
{
    int retval = TRUE;

    if (version && version[0])
    {
        unsigned short value[3] = { 0, 0, 0 };

        if (system == AUTOGEN_VERSION_ISI)
        {
            /* check that version is on the format ZZZ.YYY */
            if (strlen(version) != 7 ||
                !isdigit(version[0]) || !isdigit(version[1]) || !isdigit(version[2]) ||
                !isdigit(version[4]) || !isdigit(version[5]) || !isdigit(version[6]) ||
                version[3] != '.')
            {
                retval = FALSE;
            }
            else
            {
                value[0] = (unsigned short)atoi(version);
                value[1] = (unsigned short)atoi(version + 4);
            }
        }
        else
        {
            /* check that version is on the format ZZZ.YYY.XXX */
            if (strlen(version) != 11 ||
                !isdigit(version[0]) || !isdigit(version[1]) || !isdigit(version[2]) ||
                !isdigit(version[4]) || !isdigit(version[5]) || !isdigit(version[6]) ||
                !isdigit(version[8]) || !isdigit(version[9]) || !isdigit(version[10]) ||
                version[3] != '.' || version[7] != '.')
            {
                retval = FALSE;
            }
            else
            {
                value[0] = (unsigned short)atoi(version);
                value[1] = (unsigned short)atoi(version + 4);
                value[2] = (unsigned short)atoi(version + 8);
            }
        }

        /* check that version numbers are valid */
        if (retval)
        {
            if (value[0] > 256 || value[1] > 255 || value[2] > 255 || value[0] == 256 && value[1] > 0)
            {
                retval = FALSE;
            }
        }
    }
    else if (!allow_empty)
    {
        retval = FALSE;
    }

    return retval;
}


void init_res_include_shared_file(int line, unsigned int resid, const char* resname, const char* verfrom, const char* verto)
{
    autogen_ver ver_all = INIT_VERSION_ALL;
    autogen_obj* shared_file;
    autogen_res* shr_res;

    int is_owner = FALSE;


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* feature flags not allowed around include shared file */
    if (s_env->scope->feature_flags)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Feature flags not allowed around INCLUDE_SHARED_FILE.");
    }

    /* check resource name */
    check_c_name(s_file, line, "resname", resname, CHECK_NAME_EXIT_ON_FAIL);

    /* is shared resource defined ? */
    {
        autogen_it res_it = INIT_ITERATOR;

        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = RESOURCE_SHARED;
        res_it.obj.name    = resname;

        shr_res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list); 
        if (!shr_res)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Shared resource is not defined for '%s'", resname);
            return; /* To avoid lint warnings */
        }
    }

    /* if current resource is the owner, the ISI version much match
       the version of the shared file */
    if (!strcmp(s_res->base.name, resname) && !(s_res->base.subtype & RESOURCE_EXTENSION_ANY))
    {
        if (!(autogen_ver_comp(s_res->base.ver.from, shr_res->base.ver.from) & AUTOGEN_VER_EQUAL)) /* NOT equal */
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Shared file does not have the same ISI version as the owner");
        }

        /* set shared resource in current resource object */
        s_res->shared_res = shr_res;

        is_owner = TRUE;
    }

    /* create shared file object */
    shared_file = autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_obj), AUTOGEN_OBJ_SHARED_FILE, 0, resid, resname, NULL);
    shared_file->ptr = shr_res;

#if (PMD_FILE_FORMAT >= 600)
        if (prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_64_BITS))
        {
            if (!prop_has((autogen_obj*)shr_res, PROPERTY_ALIGNMENT_64_BITS))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Mixed 32-bit and 64-bit macros. Shared file '%s' does not have property 'PROPERTY_ALIGNMENT_64_BITS'", shr_res->base.name);
            }
        }
        else
        {
            if (!prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_CHECK_DISABLE))
            {
                if (prop_has((autogen_obj*)shr_res, PROPERTY_ALIGNMENT_64_BITS))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Mixed 32-bit and 64-bit macros. Shared file '%s' has property 'PROPERTY_ALIGNMENT_64_BITS'", shr_res->base.name);
                }
            }
        }
#endif

    /* update comments and properties */
    init_update_properties_comments(shared_file);

    /* check that version strings are valid */
    check_string(s_file, line, "verfrom", verfrom, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);
    check_string(s_file, line, "verto",   verto,   CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* set version numbers */
    init_obj_ver_set(line, s_res, shared_file, verfrom, verto, AUTOGEN_VERSION_INTERVAL,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, FALSE);

    /* add shared file object to resource */
    autogen_obj_list_add_obj(&s_res->shared_list, shared_file, AUTOGEN_ENV_LOCAL);

    /* --------------------------------------------------------------------- */
    /* copy shared resources to the current resource */
    /* --------------------------------------------------------------------- */

    /* symbol tables */
    {
        autogen_obj* shr_tbl;
        autogen_it shr_tbl_it = INIT_ITERATOR;

        shr_tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        shr_tbl_it.subtypemask = AUTOGEN_TBL_CONST_ANY;
    
        /* if owner, copy all objects that overlaps with the inclusion version interval */
        if (is_owner)
        {
            shr_tbl_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
            shr_tbl_it.ver     = &shared_file->ver;
        }
        /* else just copy the first version */
        else
        {
            shr_tbl_it.vercrit   = AUTOGEN_OBJ_VERSION_FIRST;
            shr_tbl_it.ver       = &ver_all;
            shr_tbl_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_NAME;
        }

        shr_tbl = autogen_obj_find_in_list(&shr_tbl_it, &shr_res->tbl_list);
        while (shr_tbl)
        {
            autogen_tbl* tbl = (autogen_tbl*)autogen_obj_copy_deep(shr_tbl, NULL, &s_res->base, shr_tbl_it.ver);

            tbl->base.file_name = s_file;
            tbl->base.file_line = line;
            tbl->base.flag |= AUTOGEN_OBJ_IS_SHARED | AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;
            tbl->base.res   = shr_res;

            if (is_owner)
            {
                autogen_res_ver_add(s_res, tbl->base.ver.from, AUTOGEN_VERSION_ISI);
                autogen_res_ver_add(s_res, tbl->base.ver.to,   AUTOGEN_VERSION_ISI);
            }
            /* if not owner, the version interval on each entry in the table should be the interval the shared 
               file is included in 
            */
            else
            {
                tbl->base.flag |= AUTOGEN_OBJ_IS_SHARED_EXTERNAL;

                autogen_obj_ver_replace_deep(&tbl->base, &shared_file->ver, FALSE);
            }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
            /* verify that the table typedef name with postfix _CONST does not 
               conflict with other definitions */
            if (prop_has_valid_string((autogen_obj*)shr_tbl, PROPERTY_ISIHDR_DEFINITION_NAME))
            {
                if (!(shr_tbl->flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR))
                {
                    init_add_def(line, AUTOGEN_DEF_NAME, 
                        prop_get_string((autogen_obj*)shr_tbl, PROPERTY_ISIHDR_DEFINITION_NAME),
                        0, 0, &tbl->base.ver, NULL, NULL, NULL);
                }
            }
#endif
            /* add table object to server */
            autogen_obj_list_add_obj(&s_res->tbl_list, &tbl->base, AUTOGEN_ENV_ALL);

            /* find next table */
            shr_tbl = autogen_obj_find_next_in_list(&shr_tbl_it);
            }
        }

    /* sequences */
    {
        autogen_obj* shr_seq;
        autogen_it shr_seq_it = INIT_ITERATOR;

        shr_seq_it.typemask    = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB;
        shr_seq_it.subtypemask = AUTOGEN_SEQ_ANY;
        /* if owner, copy all objects that overlaps with the inclusion version interval */
        if (is_owner)
        {
            shr_seq_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
            shr_seq_it.ver     = &shared_file->ver;
        }
        /* else just copy the first version */
        else
        {
            shr_seq_it.vercrit   = AUTOGEN_OBJ_VERSION_FIRST;
            shr_seq_it.ver       = &ver_all;
            shr_seq_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_NAME;
        }

        shr_seq = autogen_obj_find_in_list(&shr_seq_it, &shr_res->seq_list);
        while (shr_seq)
        {
            autogen_seq* seq = (autogen_seq*)autogen_obj_copy_deep(shr_seq, NULL, (autogen_obj*)s_res, shr_seq_it.ver);

            seq->base.file_name = s_file;
            seq->base.file_line = line;
            seq->base.flag |= AUTOGEN_OBJ_IS_SHARED | AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;
            seq->base.res = shr_res;

            if (is_owner)
            {
                autogen_res_ver_add(s_res, seq->base.ver.from, AUTOGEN_VERSION_ISI);
                autogen_res_ver_add(s_res, seq->base.ver.to,   AUTOGEN_VERSION_ISI);
            }
            /* if not owner, the version interval on each entry in the table should be the interval the shared 
               file is included in
            */
            else
            {
                seq->base.flag |= AUTOGEN_OBJ_IS_SHARED_EXTERNAL;

                autogen_obj_ver_replace_deep(&seq->base, &shared_file->ver, FALSE);
            }

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
            /* check that sequence definition does not conflict with other 
               definitions or constants in the current resource */
            if (!(seq->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR))
            {
                if (prop_has_valid_string((autogen_obj*)seq, PROPERTY_ISIHDR_DEFINITION_NAME))
                {
                    if (g_autogen_env == AUTOGEN_ENV_LOCAL)
                    {
                        /* verify that definition is not already defined */
                        init_add_def(line, AUTOGEN_DEF_NAME, 
                            prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_DEFINITION_NAME),
                            0, 0, &seq->base.ver, NULL, NULL, NULL);

                        /* verify that definition is not already defined */
                        if (prop_has_valid_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_LENGTH_NAME))
                        {
                            init_add_def(line, AUTOGEN_DEF_NAME, 
                                prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_LENGTH_NAME), 
                                0, 0, &seq->base.ver, NULL, NULL, NULL);
                        }
                    }
                }
            }
#endif

            seq->base.ptr = (void*)shr_seq;

            /* add sequence object to server */
            autogen_obj_list_add_obj(&s_res->seq_list, &seq->base, AUTOGEN_ENV_ALL);

            /* Clone references */
            reference_clone_seq(seq, &((autogen_seq*)shr_seq)->ref_handle);

            /* find next sequence */
            shr_seq = autogen_obj_find_next_in_list(&shr_seq_it);
        }
    }

    /* constants */
    {
        autogen_obj* shr_const;
        autogen_it shr_const_it = INIT_ITERATOR;

        shr_const_it.typemask    = AUTOGEN_OBJ_CONST;
        shr_const_it.subtypemask = AUTOGEN_CONST_ANY;

        /* if owner, copy all objects that overlaps with the inclusion version interval */
        if (is_owner)
        {
            shr_const_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
            shr_const_it.ver     = &shared_file->ver;
        }
        /* else just copy the first version */
        else
        {
            shr_const_it.vercrit   = AUTOGEN_OBJ_VERSION_FIRST;
            shr_const_it.ver       = &ver_all;
            shr_const_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_NAME;
        }

        shr_const = autogen_obj_find_in_list(&shr_const_it, &shr_res->const_list);
        while (shr_const)
        {
            autogen_const* cons = (autogen_const*)autogen_obj_copy_deep(shr_const, NULL, (autogen_obj*)s_res, shr_const_it.ver);

            cons->base.file_name = s_file;
            cons->base.file_line = line;
            cons->base.flag |= AUTOGEN_OBJ_IS_SHARED | AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;
            cons->base.res   = shr_res;

            if (is_owner)
            {
                autogen_res_ver_add(s_res, cons->base.ver.from, AUTOGEN_VERSION_ISI);
                autogen_res_ver_add(s_res, cons->base.ver.to,   AUTOGEN_VERSION_ISI);
            }
            /* if not owner, the version interval on each entry in the table should be the interval the shared 
               file is included in
            */
            else
            {
                cons->base.flag |= AUTOGEN_OBJ_IS_SHARED_EXTERNAL;

                autogen_obj_ver_replace_deep(&cons->base, &shared_file->ver, FALSE);
            }

            /* is constant conflicting with other defined constants? */
            {
                autogen_it const_it = INIT_ITERATOR;

                const_it.typemask    = AUTOGEN_OBJ_CONST;
                const_it.subtypemask = AUTOGEN_CONST_DEFINED;
                const_it.obj.name    = cons->base.name;
                const_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                const_it.ver         = &cons->base.ver;

                if (autogen_obj_find_in_list(&const_it, &s_res->const_list))
                {
                    util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Constant '%s' from the shared resource "
                        "conflicts with other constants in the client resource", cons->base.name);
                }
            }

            /* add the constant */
            init_constant_add(line, cons->base.name, cons->base.id, AUTOGEN_CONST_DEFINED, cons->base.flag, &cons->base.ver, NULL);

            /* find next constant */
            shr_const = autogen_obj_find_next_in_list(&shr_const_it);
        }
    }
}


void init_isi_version_history(int line, const char* version)
{
    autogen_obj test_ver;
    autogen_obj* obj_ver;
    autogen_it ver_it = INIT_ITERATOR;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check that version string is valid */
    check_string(s_file, line, "version", version, CHECK_NAME_EXIT_ON_FAIL | CHECK_NAME_ALLOW_EMPTY);

    /* initialize test object */
    memset(&test_ver, 0, sizeof(autogen_obj));

    /* check and set version number */
    init_obj_ver_set(line, s_res, &test_ver, version, NULL, AUTOGEN_SINGLE_VERSION,
        s_res->base.subtype == RESOURCE_ISI_DSP ? AUTOGEN_VERSION_DSP : AUTOGEN_VERSION_ISI, TRUE);

    /* if a string version is used, create a new version object */
    if (test_ver.ver.ver_str)
    {
        obj_ver = autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_obj), AUTOGEN_OBJ_VERSION, 0, 0, NULL, NULL);

        autogen_obj_list_init(&obj_ver->child_list, obj_ver, 0, 20);

        memcpy(&obj_ver->ver, &test_ver.ver, sizeof(autogen_ver));

        obj_ver->ver.id = obj_ver->obj_id;
        
        if (s_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* Do not generate version history for Legacy */
        {
            obj_ver->flag |= AUTOGEN_OBJ_IS_LEGACY;
        }

        autogen_obj_list_add_obj(&s_res->ver_list, obj_ver, AUTOGEN_ENV_NONE);
    }
    else
    {
        /* if version object is already defined, return a pointer to it */
        ver_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
        ver_it.ver     = &test_ver.ver;
        ver_it.flagnone |= AUTOGEN_OBJ_IS_LEGACY;

        obj_ver = autogen_obj_find_in_list(&ver_it, &s_res->ver_list);
        if (!obj_ver)
        {
            obj_ver = autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_obj), AUTOGEN_OBJ_VERSION, 0, 0, NULL, NULL);

            autogen_obj_list_init(&obj_ver->child_list, obj_ver, 0, 20);

            autogen_obj_ver_set(&obj_ver->ver, test_ver.ver.from, test_ver.ver.from);
            if (s_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* Legacy resource, don't include history */
            {
                obj_ver->flag |= AUTOGEN_OBJ_IS_LEGACY;
            }

            autogen_obj_list_add_obj(&s_res->ver_list, obj_ver, AUTOGEN_ENV_NONE);
        }
        else
        {
            if (s_res->base.flag & AUTOGEN_RES_IS_LEGACY) /* Legacy resource, don't include history */
            {
                obj_ver->flag |= AUTOGEN_OBJ_IS_LEGACY;
            }
        }
    }

    /* update properties and comments */
    if (obj_ver)
    {
        init_update_properties_comments(obj_ver);
    }
}


LOCAL void init_common_seq_end(int line, autogen_feature *feature_flag)
{
#ifndef AUTOGEN_ENVIRONMENT_LOCAL
    feature_flag;
#endif

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    if (!(s_seq->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR))
    {
        if (prop_has_valid_string((autogen_obj*)s_seq, PROPERTY_ISIHDR_STRUCT_NAME))
        {
            /* check that the structure name does not conflict with
               other definitions or constants in the resource */
            init_add_def(line, AUTOGEN_DEF_NAME, 
                prop_get_string((autogen_obj*)s_seq, PROPERTY_ISIHDR_STRUCT_NAME),
                0, 0, &s_seq->base.ver, NULL, NULL, feature_flag);

            /* check that the alias name does not conflict with
               other definitions or constants in the resource */
            if (prop_get_string((autogen_obj*)s_seq, PROPERTY_ISIHDR_ALIAS_NAME))
            {
                init_add_def(line, AUTOGEN_DEF_NAME, 
                    prop_get_string((autogen_obj*)s_seq, PROPERTY_ISIHDR_ALIAS_NAME), 
                    0, 0, &s_seq->base.ver, NULL, NULL, feature_flag);
            }

            /* check that the structure length definition does not conflict 
               with other definitions or constants in the resource */
            if (prop_has_valid_string((autogen_obj*)s_seq, PROPERTY_ISIHDR_STRUCT_LENGTH_NAME))
            {
                init_add_def(line, AUTOGEN_DEF_NAME, 
                    prop_get_string((autogen_obj*)s_seq, PROPERTY_ISIHDR_STRUCT_LENGTH_NAME),
                    0, 0, &s_seq->base.ver, NULL, NULL, feature_flag);
            }
        }
    }

    /* reset all autonamed filler variables and set names */
    init_reset_filler_varnames(line, &s_seq->base.child_list);
    init_set_filler_varnames(line, &s_seq->base.child_list, &s_seq->base.child_list);

    /* check that variable names are unique */
    init_check_varnames(line, &s_seq->base.child_list, &s_seq->base.child_list);

    /* check that parameter names are unique */
    init_check_parnames(line, &s_seq->base.child_list, &s_seq->base.child_list);

#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* empty properties and comments */
    init_clear_properties_comments(line);

    s_seq    = NULL;
}


char* init_res_version_string(int line, unsigned int _Z, unsigned int _Y)
{
    static char s_version_string[8] = "";

    /* check if macro is allowed in the current scope */
    if (g_autogen_env == AUTOGEN_ENV_LOCAL)
    {
        init_check_scope(line, SCOPE_ISI);
    }

    /* check version */
    if (_Z > 255)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument '_Z' is out of range. Value must be between 0 and 255");
    }
    if (_Y > 255)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument '_Y' is out of range. Value must be between 0 and 255");
    }

    sprintf(s_version_string, "%3.3u.%3.3u", _Z, _Y);

    return s_version_string;
}

#ifdef AUTOGEN_ENVIRONMENT_LOCAL

LOCAL void init_check_usage(unsigned int type, unsigned int subtypecrit, unsigned int subtype, autogen_ver* ver, autogen_obj_list* lst)
{
    autogen_it obj_it = INIT_ITERATOR;
    autogen_obj* obj;

    obj_it.typemask    = type;
    obj_it.subtypecrit = subtypecrit;
    obj_it.subtypemask = subtype;
    obj_it.flagnone    = AUTOGEN_OBJ_IS_SHARED;
    obj_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
    obj_it.ver         = ver;

    obj = autogen_obj_find_in_list(&obj_it, lst);
    while (obj)
    {
        autogen_it unused_it = INIT_ITERATOR;

        unused_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
        unused_it.ver     = ver;

        if (autogen_obj_count_in_list(&unused_it, &obj->related_obj) == 0 && !prop_has(obj, PROPERTY_SUPPRESS_AUTOGEN_WARNINGS))
        {
            util_error_line(s_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "The %s '%s' is defined, but not used", 
                util_get_obj_type_name(obj), util_get_obj_name(obj));
        }

        obj = autogen_obj_find_next_in_list(&obj_it);
    }
}

LOCAL void init_check_version_consistency(autogen_ver* ver, autogen_res* res)
{
    /* check object usage within ISI version (only for current version) */
    if (res->base.subtype != RESOURCE_SHARED && (autogen_ver_comp(ver->from, res->base.ver.from) & AUTOGEN_VER_EQUAL))
    {
        init_check_usage(AUTOGEN_OBJ_TBL, AUTOGEN_OBJ_SUBTYPE_ANY,
            AUTOGEN_TBL_CONST | AUTOGEN_TBL_DERCONST | 
            AUTOGEN_TBL_BIT | AUTOGEN_TBL_DERBIT | AUTOGEN_TBL_PPC, 
            ver, &res->tbl_list);

        if (!(res->base.subtype & RESOURCE_TRC_ANY))
        {
            init_check_usage(AUTOGEN_OBJ_SB,  AUTOGEN_OBJ_SUBTYPE_ANY, AUTOGEN_SB_ANY,  ver, &res->seq_list);
        }

        init_check_usage(AUTOGEN_OBJ_SEQ, AUTOGEN_OBJ_SUBTYPE_ANY, AUTOGEN_SEQ_ANY, ver, &res->seq_list);
    }

    /* check reference usage and alignment in messages */
    {
        autogen_seq* msg;
        autogen_it msg_it = INIT_ITERATOR;

        msg_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        msg_it.ver      = ver;

        msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, &res->msg_list);
        while (msg)
        {
            if (msg->base.type == AUTOGEN_OBJ_MSG_BASE)
            {
                autogen_seq* submsg = (autogen_seq*)autogen_obj_get_first_in_list(&msg->submsg_list);
                while (submsg)
                {
                    submsg->alignment = check_seq_alignment(s_file, submsg, ver);

                    submsg = (autogen_seq*)submsg->base.next;
                }
            }
            /* alignment check message (if not trace or protocol) */
            else if (!(msg->base.flag & AUTOGEN_MSG_TRC))
            {
                msg->alignment = check_seq_alignment(s_file, msg, ver);
            }

            msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
        }
    }


    /* check reference usage and alignment in sequences */
    {
        autogen_seq* seq;
        autogen_it seq_it = INIT_ITERATOR;

        seq_it.typemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SB_TEMPLATE;
        seq_it.flagnone = AUTOGEN_SEQ_IS_NOT_STRUCT;
        seq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        seq_it.ver      = ver;

        seq = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &res->seq_list);
        while (seq)
        {
            int should_test = FALSE;

            /* reference checking set some flags. 
               As SB templates are never referred from any message, these must be seperately ref. checked
            */
            if (g_autogen_env == AUTOGEN_ENV_LOCAL || seq->base.type == AUTOGEN_OBJ_SB_TEMPLATE || (seq->base.flag & AUTOGEN_SB_IS_TRACE))
            {
                autogen_it rel_it = INIT_ITERATOR;

                /* find any object using the sequence within the defined version interval */
                rel_it.typemask  = AUTOGEN_OBJ_REL;
                rel_it.vercrit   = AUTOGEN_OBJ_VERSION_OVERLAP;
                rel_it.ver       = ver;

                /* if no objects are using the sequence, the sequence should be reference checked */
                if (!autogen_obj_find_in_list(&rel_it, &seq->base.related_obj))
                {
                    should_test = TRUE;
                }
            }

            if (should_test)
            {
                /* alignment check sequence (if not trace) */
                if (!(res->base.subtype & RESOURCE_TRC_ANY))
                {
                    seq->alignment = check_seq_alignment(s_file, seq, ver);
                }
            }
            else if (seq->base.type == AUTOGEN_OBJ_SB)
            {
                seq->alignment = check_seq_alignment(s_file, seq, ver);
            }

            seq = (autogen_seq*)autogen_obj_find_next_in_list(&seq_it);
        }
    }

    /* check/calculate sizes for all messages, the size is not yet calculated for */
    {
        autogen_seq* msg;
        autogen_it msg_it = INIT_ITERATOR;

        msg_it.typemask = AUTOGEN_OBJ_MSG;
        msg_it.flagnone = AUTOGEN_MSG_HAS_NO_ELEMENTS;
        msg_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        msg_it.ver      = ver; 

        msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, &res->msg_list);
        while (msg)
        {
#if (PMD_FILE_FORMAT >= 600)
            unsigned long long size_min  = 0;
            unsigned long long size_max  = 0;
#else
            unsigned int size_min  = 0;
            unsigned int size_max  = 0;
#endif
            unsigned int size_type = util_get_seq_size(msg, ver, &size_min, &size_max);

            if (prop_has(&msg->base, PROPERTY_MSG_LENGTH_LIMIT))
            {
                size_max = prop_get_value(&msg->base, PROPERTY_MSG_LENGTH_LIMIT);
                size_type = AUTOGEN_SIZE_INTERVAL;
            }

            /* if first calculation, copy result to subblock object */
            if (msg->size.type == AUTOGEN_SIZE_UNDEFINED)
            {
                msg->size.type = size_type;
                msg->size.min  = (unsigned int)size_min;
                msg->size.max  = (unsigned int)size_max;
            }
            /* if different result than previous result, the subblock size must be version dependent */
            else if (size_type != msg->size.type || size_min  != msg->size.min || size_max  != msg->size.max)
            {
                msg->size.type = AUTOGEN_SIZE_VERSION_DEPENDENT;
                msg->size.min  = 0;
                msg->size.max  = 0;
            }

            msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
        }
    }

    /* check/calculate sizes for all subblocks and subblock templates, the size is not yet 
       calculated for 
    */
    {
        autogen_seq* sb;
        autogen_it sb_it = INIT_ITERATOR;

        sb_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB_TEMPLATE;
        sb_it.flagnone = AUTOGEN_SEQ_IS_NOT_STRUCT | AUTOGEN_OBJ_IS_SHARED;
        sb_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        sb_it.ver      = ver; 

        sb = (autogen_seq*)autogen_obj_find_in_list(&sb_it, &res->seq_list);
        while (sb)
        {
#if (PMD_FILE_FORMAT >= 600)
            unsigned long long size_min  = 0;
            unsigned long long size_max  = 0;
#else
            unsigned int size_min  = 0;
            unsigned int size_max  = 0;
#endif

            unsigned int size_type = util_get_seq_size(sb, ver, &size_min, &size_max);

            /* check that maximum subblock length is within the limits of the sb length field */
            if (sb->base.type == AUTOGEN_OBJ_SB && !prop_has((autogen_obj*)sb, PROPERTY_SB_LENGTH_MISSING) || 
                sb->base.type == AUTOGEN_OBJ_SB_TEMPLATE)
            {
                unsigned int maxlength;

                const autogen_item* length_item =  reference_get_special_item(&sb->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH);
                if (length_item == NULL)
                {
                    reference_get_special_item(&sb->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH);
                }
   
                if (sb->base.type == AUTOGEN_OBJ_SB && 
                    (size_type == AUTOGEN_SIZE_INTERVAL || size_type == AUTOGEN_SIZE_ASMANYASPOSSIBLE) && 
                    prop_has(&sb->base, PROPERTY_SB_LENGTH_LIMIT))
                {
                    size_max  = prop_get_value(&sb->base, PROPERTY_SB_LENGTH_LIMIT);
                    size_type = AUTOGEN_SIZE_INTERVAL;
                    maxlength = (unsigned int)size_max;
                }
                else if (length_item->length == 32)
                {
                    maxlength = 0xFFFFFFFC;
                }
                else
                {
                    maxlength  = (1 << abs(length_item->length)) - 1;

                    if (sb->base.type == AUTOGEN_OBJ_SB && !prop_has((autogen_obj*)sb, PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4))
                    {
#if (PMD_FILE_FORMAT >= 600)
                        if (prop_has((autogen_obj*)sb->base.res, PROPERTY_ALIGNMENT_64_BITS))
                        {
                            maxlength -= maxlength % 8;
                        }
                        else
#endif
                        maxlength -= maxlength % 4;
                    }
                }

                if ((unsigned int)size_max > maxlength)
                {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 3,
                        "Length of %s '%s' is %s%u bytes, "
                        "which is larger than the maximum allowed length of %u bytes",
                        util_get_obj_type_name((autogen_obj*)sb), util_get_obj_name((autogen_obj*)sb),
                        size_max != size_min ? "potentionally " : "", (unsigned int)size_max, maxlength);
                }
            }

            /* if first calculation, copy result to subblock object */
            if (sb->size.type == AUTOGEN_SIZE_UNDEFINED)
            {
                sb->size.type = size_type;
                sb->size.min  = (unsigned int)size_min;
                sb->size.max  = (unsigned int)size_max;
            }
            /* if different result than previous result, the subblock size must be version dependent */
            else if (size_type != sb->size.type || size_min  != sb->size.min || size_max  != sb->size.max)
            {
                sb->size.type = AUTOGEN_SIZE_VERSION_DEPENDENT;
                sb->size.min  = 0;
                sb->size.max  = 0;
            }

            sb = (autogen_seq*)autogen_obj_find_next_in_list(&sb_it);
        }
    }
}
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


LOCAL autogen_item* init_handle_filler_replacement(int line, autogen_item* value, autogen_feature *feature_flag)
{
    autogen_item* filler = NULL;

    if (prop_has(&value->base, PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION))
    {
        int is_major_version = FALSE;
        int ver_fm_comparison   = 0;
        int ver_to_comparison   = 0;
        unsigned short ver[3] = { 0, 0, 0 };
        const char* verstring = prop_get_string(&value->base, PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION);
        const autogen_obj* parent = util_get_base_parent((autogen_obj*)value); 
        autogen_ver filler_ver = INIT_VERSION_ALL;

        /* check if version string is valid */
        if (!init_check_version(verstring, AUTOGEN_VERSION_ISI, FALSE))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Property PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION is not valid. Must be on the format 'ZZZ.YYY', ZZZ and YYY < 256");

            verstring = "000.000";
        }

        ver[0] = (unsigned short)atoi(verstring);
        ver[1] = (unsigned short)atoi(verstring + 4);

        /* Verify that the filler replacement version is within the version range of the construct holding it */
        ver_fm_comparison = (autogen_ver_comp(parent->ver.from, ver) & AUTOGEN_VER_OLDER);
        ver_to_comparison = (autogen_ver_comp(parent->ver.to, ver) & AUTOGEN_VER_NEWER);
        if (ver_fm_comparison || ver_to_comparison)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Version specified in PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION is not valid. Must be inside the version range of construct containing it.");
        }

        is_major_version = ver[1] == 0; /* If major version then do not check for default value */

        if (is_major_version) /* Check for filler replacement in new version of containing structure - no need */
        {
            if ((ver[0]) == (parent->ver.from[0]))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Property PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION should not be used and is not needed when filler is replaced in same major version as that of the construct containing it.");
            }
        }

        if (!is_major_version)
        {
            if (prop_has(&value->base, PROPERTY_ITEM_DEFAULT_VALUE))
            {
                if (!prop_has_value(&value->base, PROPERTY_ITEM_DEFAULT_VALUE))
                {
                    if (!prop_has_valid_string(&value->base, PROPERTY_ITEM_DEFAULT_VALUE))
                    {
                        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                            "The default value for filler replacement must be 0");
                    }
                    /* if a string has been defined then try to find value ... */
                }
                else
                {
                    /* value must be 0 */
                    int def_val = (int)prop_get_value(&value->base, PROPERTY_ITEM_DEFAULT_VALUE);
                    if (def_val != 0)
                    {
                        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                            "The default value for filler replacement must be 0");
                    }
                }
            }
            else
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "The default value for filler replacement must be 0");
            }
        }

        autogen_obj_ver_set(&filler_ver, ver, ver);

        /* Verify that filler replacement version is within range of parent object */
        if (!autogen_obj_ver_is_included(&s_env->scope->parent->ver, &filler_ver))
        {
            /* TO DO: Fail if it is not. For now, ignore the filler... */
        }
        else
        {
            char* varname = (char*)pmd_heap_alloc(strlen(value->varname) + 20);;

            /* genererate filler item */
            filler = init_item_create(line, sizeof(autogen_item), AUTOGEN_ITEM_FILLER, AUTOGEN_FILLER_IS_REPLACED, "", "Filler", feature_flag);

            /* should not generate element in ISI header file */
            prop_add_simple_to_object(&filler->base, PROPERTY_ISIHDR_DONT_GENERATE, NULL, 0, FALSE);
            prop_add_simple_to_object(&filler->base, PROPERTY_HTML_DONT_GENERATE, NULL, 0, FALSE);

            /* generate version of new filler */
            autogen_obj_ver_set(&filler->base.ver, value->base.ver.from, ver);

            sprintf(varname, "%s_filler", value->varname);
            filler->varname = varname;

            filler->length = value->length;
            filler->order  = AUTOGEN_ORDER_BE;

            filler->agg_n     = 1;
            filler->agg_n_str = "1";
            filler->agg_type  = AGG_TYPE_FIXED_SINGLE;

            init_item_add(filler, feature_flag);

            /* change version of value */
            autogen_obj_ver_set(&value->base.ver, ver, value->base.ver.to);

            value->base.flag |= AUTOGEN_ITEM_IS_FILLER_REPLACEMENT;

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
            /* Add version history object */
            version_history_add_entry(s_res, &value->base, AUTOGEN_VERSION_HISTORY_FILLER_REPLACED);
#endif
        }
    }

    return filler;
}

/* count number of variables named varname. Look from item and forward.
   Filler names are not counted
   If argument feature_flag is non-null then the function will only count variables named varname under the given feature flag
   Otherwise it will count all variables named varname.
*/
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
LOCAL unsigned int init_count_varname(autogen_obj_list* obj_list, const char* varname, autogen_feature *feature_flag)
{
    unsigned int count = 0;

    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (*varname && item)
    {
#ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
        /* check if current varname is the named being searched for */
        if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
        {
            autogen_item_choice* choice_item = (autogen_item_choice*)item;
            autogen_item_case* case_item = choice_item->default_case;
            if (case_item)
            {
                count += init_count_varname(&case_item->base.base.child_list, varname, feature_flag);
            }
        }
        else 
#endif
        if (!strcmp(item->varname, varname))
        {
            /* If feature flag is defined then only count if item is under same feature flag */
            if (feature_flag == NULL || autogen_obj_featureflag_comp(item->base.feature_flags, feature_flag) == 0)
            {
                ++count;
            }
        }
        if (prop_has_valid_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED) && 
            !strcmp(prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED), varname))
        {
            /* If feature flag is defined then only count if item is under same feature flag */
            if (feature_flag == NULL || autogen_obj_featureflag_comp(item->base.feature_flags, feature_flag) == 0)
            {
                ++count;
            }
        }
        else if (prop_has_valid_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED) && 
            !strcmp(prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED), varname))
        {
            /* If feature flag is defined then only count if item is under same feature flag */
            if (feature_flag == NULL || autogen_obj_featureflag_comp(item->base.feature_flags, feature_flag) == 0)
            {
                ++count;
            }
        }
        else if (prop_has_valid_string(&item->base, PROPERTY_ISIHDR_SPLIT_WORD_SIGNED) && 
            !strcmp(prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_WORD_SIGNED), varname))
        {
            /* If feature flag is defined then only count if item is under same feature flag */
            if (feature_flag == NULL || autogen_obj_featureflag_comp(item->base.feature_flags, feature_flag) == 0)
            {
                ++count;
            }
        }
        else if (prop_has_valid_string(&item->base, PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED) && 
                !strcmp(prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED), varname))
        {
            /* If feature flag is defined then only count if item is under same feature flag */
            if (feature_flag == NULL || autogen_obj_featureflag_comp(item->base.feature_flags, feature_flag) == 0)
            {
                ++count;
            }
        }

        item = (autogen_item*)item->base.next;
    }

    return count;
}
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

/* check all varnames in seq */
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
LOCAL void init_reset_filler_varnames(int line, autogen_obj_list* obj_list)
{
    /* reset all autonamed filler names */
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        if (item->base.subtype == AUTOGEN_ITEM_MERGE)
        {
            init_reset_filler_varnames(line, &item->base.child_list);
        }
        else if (item->base.subtype == AUTOGEN_ITEM_FILLER && (item->base.flag & AUTOGEN_FILLER_VAR_AUTONAME))
        {
            item->varname = "";
        }
        else if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
        {
            autogen_item_choice* choice_item = (autogen_item_choice*)item;
            if (choice_item->default_case)
            {
                init_reset_filler_varnames(line, &choice_item->default_case->base.base.child_list);
            }
        }

        item = (autogen_item*)item->base.next;
    }
}

LOCAL void init_set_filler_varnames(int line, autogen_obj_list* obj_list, autogen_obj_list* check_list)
{
    /* reset all autonamed filler names */
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        if (item->base.subtype == AUTOGEN_ITEM_MERGE)
        {
            init_set_filler_varnames(line, &item->base.child_list, check_list);
        }
        else if (item->base.subtype == AUTOGEN_ITEM_FILLER && (item->base.flag & AUTOGEN_FILLER_VAR_AUTONAME))
        {
            int filler = 1;
            char str_varname[20];

            do
            {
                sprintf(str_varname, "fill%lu", filler++);

            } while (init_count_varname(check_list, str_varname, NULL) > 0);

            item->varname = pmd_heap_strdup(str_varname);
        }
        else if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
        {
            autogen_item_choice* choice_item = (autogen_item_choice*)item;
            if (choice_item->default_case)
            {
                init_set_filler_varnames(line, &choice_item->default_case->base.base.child_list, check_list);
            }
        }

        item = (autogen_item*)item->base.next;
    }
}

LOCAL void init_check_varname(int line, autogen_item* item, autogen_obj_list* check_list)
{
    const char* varname2;

    if (init_count_varname(check_list, item->varname, item->base.feature_flags) > 1)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Redefinition of 'varname' '%s'", item->varname);
    }

    varname2 = prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED);
    if (varname2 && init_count_varname(check_list, varname2, item->base.feature_flags) > 1)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Redefinition of 'varname' '%s'", varname2);
    }

    varname2 = prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED);
    if (varname2 && init_count_varname(check_list, varname2, item->base.feature_flags) > 1)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Redefinition of 'varname' '%s'", varname2);
    }

    varname2 = prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_WORD_SIGNED);
    if (varname2 && init_count_varname(check_list, varname2, item->base.feature_flags) > 1)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Redefinition of 'varname' '%s'", varname2);
    }

    varname2 = prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED);
    if (varname2 && init_count_varname(check_list, varname2, item->base.feature_flags) > 1)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Redefinition of 'varname' '%s'", varname2);
    }
}

LOCAL void init_check_varnames(int line, autogen_obj_list* obj_list, autogen_obj_list* check_list)
{
    /* reset all autonamed filler names */
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        if (item->base.subtype == AUTOGEN_ITEM_MERGE)
        {
            init_check_varname(line, item, check_list);

            /* check all merged items */
            init_check_varnames(line, &item->base.child_list, check_list);
        }
        else if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
        {
            autogen_item_choice* choice_item = (autogen_item_choice*)item;
            if (choice_item->default_case)
            {
                init_check_varnames(line, &choice_item->default_case->base.base.child_list, check_list);
            }
        }
        else
        {
            init_check_varname(line, item, check_list);
        }

        item = (autogen_item*)item->base.next;
    }
}

/* count number of variables named parname. Look from item and forward.
   Filler names are not counted
   If argument feature_flag is non-null then the function will only count variables named parname under the given feature flag
   Otherwise it will count all variables named parname.
*/
LOCAL unsigned int init_count_parname(autogen_obj_list* obj_list, const char* parname, autogen_feature *feature_flag)
{
    unsigned int count = 0;

    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (*parname && item)
    {
        /* if merge, count number of sub items named varname */
        if (item->base.subtype == AUTOGEN_ITEM_MERGE && (item->agg_type == AGG_TYPE_FIXED_SINGLE || item->agg_type == AGG_TYPE_FIXED_MULTIPLE))
        {
            if (!strcmp(item->parname, parname))
            {
                /* If feature flag is defined then only count if item is under same feature flag */
                if (feature_flag == NULL || autogen_obj_featureflag_comp(item->base.feature_flags, feature_flag) == 0)
                {
                    ++count;
                }
            }
        }
#ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
        /* if item is a choice element, iterate through sub items */
        else if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
        {
            unsigned int case_count_max = 0;

            autogen_item_choice* choice_item = (autogen_item_choice*)item;
            autogen_item_case* case_item = (autogen_item_case*)autogen_obj_get_first_in_list(&item->base.child_list);
            while (case_item)
            {
                unsigned int case_count = init_count_parname(&case_item->base.base.child_list, parname, feature_flag);
                case_count_max = (case_count > case_count_max ? case_count : case_count_max);

                case_item = (autogen_item_case*)case_item->base.base.next;
            }
            if (choice_item->default_case)
            {
                unsigned int case_count = init_count_parname(&choice_item->default_case->base.base.child_list, parname, feature_flag);
                case_count_max = (case_count > case_count_max ? case_count : case_count_max);
            }

            count += case_count_max;
        }
#endif /* AUTOGEN_DISABLE_TOUGH_CHECKS */
        /* check if current parname is the name being searched for */
        else if (item->base.subtype != AUTOGEN_ITEM_FILLER && item->base.subtype != AUTOGEN_ITEM_CHOICE && !strcmp(item->parname, parname))
        {
            /* If feature flag is defined then only count if item is under same feature flag */
            if (feature_flag == NULL || autogen_obj_featureflag_comp(item->base.feature_flags, feature_flag) == 0)
            {
                ++count;
            }
        }

        item = (autogen_item*)item->base.next;
    }

    return count;
}

LOCAL void init_check_parname(int line, autogen_item* item, autogen_obj_list* check_list)
{
    if (init_count_parname(check_list, item->parname, item->base.feature_flags) > 1)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Redefinition of 'parname' '%s'", item->parname);
    }
}

/* check all parnames in seq */
LOCAL void init_check_parnames(int line, autogen_obj_list* obj_list, autogen_obj_list* check_list)
{
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        /* if item is a merge, iterate through sub items */
        if (item->base.subtype == AUTOGEN_ITEM_MERGE && (item->agg_type == AGG_TYPE_FIXED_SINGLE || item->agg_type == AGG_TYPE_FIXED_MULTIPLE))
        {
            init_check_parname(line, item, check_list);

            /* In merged field, parname should be unique just within marged field */
            init_check_parnames(line, &item->base.child_list, &item->base.child_list);
        }
#ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
        /* if item is a choice element, iterate through sub items */
        else if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
        {
            autogen_item_choice* choice_item = (autogen_item_choice*)item;
            autogen_item_case* case_item = (autogen_item_case*)autogen_obj_get_first_in_list(&item->base.child_list);
            while (case_item)
            {
                init_check_parnames(line, &case_item->base.base.child_list, check_list);

                case_item = (autogen_item_case*)case_item->base.base.next;
            }

            if (choice_item->default_case)
            {
                init_check_parnames(line, &choice_item->default_case->base.base.child_list, check_list);
            }
        }
#endif
        else if (item->base.subtype != AUTOGEN_ITEM_FILLER && item->base.subtype != AUTOGEN_ITEM_CHOICE && item->base.subtype != AUTOGEN_ITEM_CHOICE)
        {
            init_check_parname(line, item, check_list);
        }

        item = (autogen_item*)item->base.next;
    }
}

LOCAL void init_check_for_empty_tables(int line)
{
    /* If we are not dealing with autogen_symbols then check for empty table */
    if (strncmp(s_file, "autogen_symbols.h", 17))
    {
        /* If the table is empty then report an error and stop processing */
        if (s_tbl->base.child_list.n_obj == 0)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "The table '%s' is empty. Empty tables are not allowed! If the table is not used then remove it. Otherwise add table entries", s_tbl->base.name);
        }
    }
}
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

LOCAL void init_check_object(autogen_res* res, autogen_obj* obj)
{
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    if (!(obj->flag & AUTOGEN_OBJ_IS_SHARED))
    {
        autogen_obj* link_obj;
        /* check that comment link link to defined objects */
        autogen_cmt* cmt = obj->cmt_list;

        cmt = autogen_cmt_find(cmt, COMMENT_LINK_TYPE);
        while (cmt)
        {
            autogen_obj_list* obj_list = NULL;
            autogen_it obj_it = INIT_ITERATOR;

            obj_it.typemask = cmt->linktype;
            obj_it.obj.name = cmt->linkname;
            obj_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            obj_it.ver      = &cmt->linkver;

            switch (cmt->linktype)
            {
            case AUTOGEN_OBJ_MSG:
                {
                    obj_list         = &res->msg_list;
                    obj_it.typemask |= AUTOGEN_OBJ_MSG_BASE;
                }
                break;

            case AUTOGEN_OBJ_SB:
                {
                    obj_list = &res->seq_list;
                }
                break;

            case AUTOGEN_OBJ_SEQ:
                {
                    obj_list        = &res->seq_list;
                    obj_it.flagnone = AUTOGEN_SEQ_IS_NOT_STRUCT;
                }
                break;

            case AUTOGEN_OBJ_TBL:
                {
                    obj_list           = &res->tbl_list;
                    obj_it.subtypemask = AUTOGEN_TBL_CONST_ANY;
                }
                break;

            case AUTOGEN_OBJ_NOTE:
                {
                    obj_list = &res->note_list;
                }
                break;

            case AUTOGEN_OBJ_CONST:
                {
                    obj_list = &res->const_list;
                }
                break;

            default:
                {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in init_check_object(). cmt->linktype is 0x%8.8X", cmt->linktype);
                }
                break;
            }

            link_obj = autogen_obj_find_in_list(&obj_it, obj_list);
            /* Check submessage */
            if (link_obj && cmt->linksubname && cmt->linksubname[0])
            {
                int fail = TRUE;

                if (link_obj->type == AUTOGEN_OBJ_MSG_BASE)
                {
                    obj_it.obj.name = cmt->linksubname;

                    fail = (autogen_obj_find_in_list(&obj_it, &((autogen_seq*)link_obj)->submsg_list) == NULL);
                }

                if (fail)
                {
                    util_error_line(s_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Invalid comment link '%s / %s' defined in %s '%s'",
                        cmt->linkname, cmt->linksubname, 
                        util_get_obj_type_name(obj), util_get_obj_name(obj));
                }
            }
            if (!link_obj)
            {
                if (cmt->linksubname && cmt->linksubname[0])
                {
                    util_error_line(s_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Invalid comment link '%s / %s' defined in %s '%s'",
                        cmt->linkname, cmt->linksubname, 
                        util_get_obj_type_name(obj), util_get_obj_name(obj));
                }
                else
                {
                    util_error_line(s_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Invalid comment link '%s' defined in %s '%s'",
                        cmt->linkname, util_get_obj_type_name(obj), util_get_obj_name(obj));
                }
            }

            cmt = autogen_cmt_find(cmt->next, COMMENT_LINK_TYPE);
        }
    }
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* check child objects */

    /* if resource, check all object lists */
    if (obj->type == AUTOGEN_OBJ_RES)
    {
        init_check_object_lst(res, &((autogen_res*)obj)->const_list);
        init_check_object_lst(res, &((autogen_res*)obj)->msg_list);
        init_check_object_lst(res, &((autogen_res*)obj)->seq_list);
        init_check_object_lst(res, &((autogen_res*)obj)->shared_list);
        init_check_object_lst(res, &((autogen_res*)obj)->tbl_list);
    }
    else if (obj->type == AUTOGEN_OBJ_TBL ||
        obj->type == AUTOGEN_OBJ_SB || obj->type == AUTOGEN_OBJ_SEQ || obj->type == AUTOGEN_OBJ_TRACE || 
        obj->type == AUTOGEN_OBJ_SB_TEMPLATE || 
        obj->type == AUTOGEN_OBJ_ITEM)
    {
        if (!(obj->flag & AUTOGEN_OBJ_IS_SHARED))
        {
            init_check_object_lst(res, &obj->child_list);
        }
    }
}

LOCAL void init_check_object_lst(autogen_res* res, autogen_obj_list* obj_list)
{
    autogen_obj* obj = autogen_obj_get_first_in_list(obj_list);
    while (obj)
    {
        /* check child objects */
        init_check_object(res, obj);

        obj = obj->next;
    }
}

LOCAL void init_check_res(autogen_res* res)
{
    /* check that comment links are valid */
    init_check_object(res, (autogen_obj*)res);
}

LOCAL void init_check_string_prop(int line, autogen_obj* value, autogen_property_id id, autogen_feature *featureflag)
{
    if (!prop_has_value((autogen_obj*)value, id))
    {
        if (prop_has_valid_string((autogen_obj*)value, id))
        {
            autogen_it entry_it = INIT_ITERATOR;
            autogen_obj* entry;

            entry_it.obj.name = prop_get_string((autogen_obj*)value, id);
            if (featureflag)
            {
                entry_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                entry_it.obj.feature_flags = featureflag;
            }

            entry = autogen_obj_find_in_list(&entry_it, &s_res->const_list);
            if (!entry)
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "The value defined for this item is not valid %s", entry_it.obj.name);
            }
            else
            {
                prop_object_add_value(value, id, entry->id, FALSE);
            }
        }
    }
}


void init_block(int line, unsigned int order, const char* varname, const char* name, unsigned int type, 
    const char* data1, const char* data2, unsigned int flags, const char* refname, unsigned int n, const char* nstr)
{
    autogen_item_block* block;
    unsigned int flag = 0;
    autogen_agg_type agg_type = AGG_TYPE_UNKNOWN;
    char* parname = pmd_heap_strdup(name);


    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_TRACE | SCOPE_CASE);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check data order */
    order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, 16, FALSE);

    /* check block type and convert to internal constant */
    if (type == BLOCK_PN_MSG)
    {
        /* check data */
        if (data1)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'data1' is not valid");
            data1 = NULL;
        }
        if (data2)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'data2' is not valid");
            data2 = NULL;
        }

        if (flags & BLOCK_PN_MSG_SKIP_TRACE)
        {
            flag |= AUTOGEN_BLOCK_PN_MSG_SKIP_TRACE;
        }
    }
    else if (type == BLOCK_EXT_DECODER)
    {
        /* check the data */
        check_string(s_file, line, "data1", data1, CHECK_NAME_EXIT_ON_FAIL);
        check_string(s_file, line, "data2", data2, CHECK_NAME_EXIT_ON_FAIL);

        flag |= flags;
    }
    else if (type == BLOCK_RAW_DATA || type == BLOCK_X_FILE)
    {
        /* check the data */
        if (data1)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'data1' is not valid");
            data1 = NULL;
        }
        if (data2)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'data2' is not valid");
            data2 = NULL;
        }
    }
    else if (type == BLOCK_PROTOCOL || type == BLOCK_PMD_ANCHOR)
    {
        /* check the data */
        check_string(s_file, line, "data1", data1, CHECK_NAME_EXIT_ON_FAIL);
        if (data2)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'data2' is not valid");
            data2 = NULL;
        }
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'type' is not valid");

        type = BLOCK_RAW_DATA;
    }

    /* --------------------------------------------------------------------- */
    /* checks for BLOCK */
    /* --------------------------------------------------------------------- */
    if (!refname)
    {
        /* check number of elements string */
        check_string(s_file, line, "n", nstr, CHECK_NAME_EXIT_ON_FAIL);

        if (n == 0 || n > 65535)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'n' is out of range. Value must be between 1 and 65535");
            return; /* To avoid lint warnings */
        }
        else if (n > 1)
        {
            agg_type = AGG_TYPE_FIXED_MULTIPLE;

            /* add the constant (or merge with existing constants) */
            init_constant_add(line, nstr, n, AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_env->scope->parent->ver, (s_env->scope ? s_env->scope->feature_flags : NULL));
        }
        else
        {
            agg_type = AGG_TYPE_FIXED_SINGLE;
        }
    }
    /* --------------------------------------------------------------------- */
    /* checks for BLOCK_REF */
    /* --------------------------------------------------------------------- */
    else
    {
        /* check reference name */
        check_c_name(s_file, line, "refname", refname, CHECK_NAME_EXIT_ON_FAIL);

        /* set aggregation type */
        /* allow predefined reference name REF_AS_MANY_AS_POSSIBLE or REF_OPTIONAL to be used */
        if (!strcmp(refname, "REF_AS_MANY_AS_POSSIBLE"))
        {
            agg_type = AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE;
        }
        else if (!strcmp(refname, "REF_LENGTH_UNKNOWN"))
        {
            agg_type = AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH;
        }
        else
        {
            agg_type = AGG_TYPE_DYNAMIC_REF;
        }
    }

    /* create and initialize item object */
    block = (autogen_item_block*)init_item_create(line, sizeof(autogen_item_block), AUTOGEN_ITEM_BLOCK, flag, varname, parname, 
                                                  (s_env->scope ? s_env->scope->feature_flags : NULL));

    block->base.item_sub_type = type;
    block->base.length        = 8;
    block->base.order         = order;
    block->base.agg_type      = agg_type;

    /* copy version */
    memcpy(&block->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    block->base.agg_n    = n;
    block->base.agg_type = agg_type;
    
    if (agg_type == AGG_TYPE_FIXED_SINGLE ||
        agg_type == AGG_TYPE_FIXED_MULTIPLE)
        {
        block->base.agg_n_str = nstr;
        }
    else if (agg_type == AGG_TYPE_DYNAMIC_REF)
    {
        block->base.refname = refname;
        reference_use_counter(&block->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
    }

    block->data1 = data1;
    block->data2 = data2;

    /* Validate combinations of array type and marker flag */
    if (prop_has_value(&block->base.base, PROPERTY_ARRAY_MAXIMUM_SIZE))
    {
        init_constant_add(line, 
            prop_get_string(&block->base.base, PROPERTY_ARRAY_MAXIMUM_SIZE),
            prop_get_value(&block->base.base, PROPERTY_ARRAY_MAXIMUM_SIZE), 
            AUTOGEN_CONST_AUTOGENERATED, AUTOGEN_CONST_UNSIGNED_DEC, &s_seq->base.ver, 
            (s_env->scope ? s_env->scope->feature_flags : NULL));
    }

    /* add item object to sequence object */
    init_item_add(&block->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}


/*  Init function for the POINTER macro */
void init_pointer(int line, unsigned int order, const char* varname, const char* name, unsigned int type)
{
    autogen_item_value* value;
    unsigned int flag = AUTOGEN_POINTER_VOID;
    char* parname = pmd_heap_strdup(name);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_TRACE | SCOPE_CASE | SCOPE_PRINTF);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check pointer type */
    if (type == POINTER_VOID ||
#if (PMD_FILE_FORMAT >= 600)
        type == POINTER_INT64 ||
        type == POINTER_UINT64 ||
#endif
        type == POINTER_INT32 ||
        type == POINTER_UINT32 ||
        type == POINTER_INT16 ||
        type == POINTER_UINT16 ||
        type == POINTER_INT8 ||
        type == POINTER_UINT8)
    {
#if (PMD_FILE_FORMAT >= 600)
        if (!prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_64_BITS))
        {
            if ((type == POINTER_INT64) || (type == POINTER_UINT64))
            {
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Argument 'type' is not valid. 64-bit pointer types require resource property 'PROPERTY_ALIGNMENT_64_BITS' to be applied");
            }
        }
#endif
        flag |= type;
    }
    else
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Argument 'type' is not valid");
    }

    /* create and initialize item object */
    value = (autogen_item_value*)init_item_create(line, sizeof(autogen_item_value), AUTOGEN_ITEM_POINTER, flag, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&value->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

#if (PMD_FILE_FORMAT >= 600)
    if((type == POINTER_INT64) ||(type == POINTER_UINT64))
    {
        value->base.length = 64;
    }
    else
    {
        value->base.length = 32;
    }
#else
    value->base.length = 32;
#endif
    value->pres.type   = AUTOGEN_PRESENTATION_HEX;

    /* check data order */
    value->base.order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, value->base.length, FALSE);

    /* handle filler replacement */
    init_handle_filler_replacement(line, &value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* Pointer is default not parameter in a scope printf */
    if (s_env->scope->scope == SCOPE_PRINTF)
    {
        if (!prop_has((autogen_obj*)value, PROPERTY_PMD_IS_NOT_PARAMETER))
        {
            prop_add_simple_to_object((autogen_obj*)value, PROPERTY_PMD_IS_NOT_PARAMETER, NULL, 0, 0);
        }
    }

    /* add item object to sequence object */
    init_item_add(&value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}

void init_trace_group_decoder(int line, const char* name, unsigned int id, int state, const char* dllname, const char* dllfunc, unsigned int flags)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* check grpname */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* check dll name */
    check_string(s_file, line, "dllname", dllname, CHECK_NAME_EXIT_ON_FAIL);

    /* check dll function */
    check_c_name(s_file, line, "dllfunc", dllfunc, CHECK_NAME_EXIT_ON_FAIL);

    /* add the trace group */
    init_trace_group_add(line, s_res, name, id, state, "TRACE_GROUP_DECODER", TRUE);

    /* set the decoder attributes */
    s_trcgrp->dll_name   = dllname;
    s_trcgrp->func_name  = dllfunc;

    s_trcgrp->base.child_list.n_obj = 0;

    if (flags & BLOCK_EXT_DECODER_SKIP_ID)
    {
        s_trcgrp->base.flag |= AUTOGEN_BLOCK_EXT_DECODER_SKIP_ID;
    }
}

LOCAL void init_check_scope(int line, unsigned int scopemask)
{
    if (!(s_env->scope->scope & scopemask))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Macro can't be used in this context");
    }
}

LOCAL void init_check_scope_macro(int line, unsigned int scopemask, const char* macro)
{
    if (!(s_env->scope->scope & scopemask))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Macro '%s' can't be used in this context", macro);
    }
}

LOCAL autogen_obj* init_check_scope_target(int line, unsigned int target)
{
    autogen_obj* obj = NULL;

    switch (target)
    {
        /* check if macro is allowed in the current scope */

    case AUTOGEN_TARGET_TBLENTRY:
        {
            init_check_scope(line, SCOPE_IS_TBL);
            if (!s_object)
            {
                s_object = (autogen_obj*)pmd_heap_alloc(sizeof(autogen_obj));
            }
            obj = (autogen_obj*)s_object;
        }
        break;

    case AUTOGEN_TARGET_ITEM:
        {
            init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE);
            if (!s_object)
            {
                s_object = (autogen_obj*)pmd_heap_alloc(sizeof(autogen_obj));
            }
            obj = s_object;
        }
        break;

    case AUTOGEN_TARGET_VERSION:
    case AUTOGEN_TARGET_NOTE:
    case AUTOGEN_TARGET_INCLUDE_SHARED_FILE:
    case AUTOGEN_TARGET_CONSTANT:
        {
            init_check_scope(line, SCOPE_RES);
            if (!s_object)
            {
                s_object = (autogen_obj*)pmd_heap_alloc(sizeof(autogen_obj));
            }
            obj = s_object;
        }
        break;

    case AUTOGEN_TARGET_MSGID:
        {
            init_check_scope(line, SCOPE_RES);
            if (!s_res->msg_id_section)
            {
                s_res->msg_id_section = (autogen_obj*)pmd_heap_alloc(sizeof(autogen_obj));
            }
            obj = s_res->msg_id_section;
        }
        break;

    case AUTOGEN_TARGET_MAIN:
        {
            init_check_scope(line, SCOPE_RES | SCOPE_IS_SEQ | SCOPE_IS_TBL | SCOPE_TRACE);
            if (s_env->scope->scope & SCOPE_RES)
            {
                obj = (autogen_obj*)s_res;
            }
            else if (s_env->scope->scope & SCOPE_IS_TBL)
            {
                obj = (autogen_obj*)s_tbl;
            }
            else if (s_env->scope->scope & (SCOPE_IS_SEQ | SCOPE_TRACE))
            {
                obj = (autogen_obj*)s_seq;
            }
        }
        break;

    case AUTOGEN_TARGET_TRCIDTBL:
        {
            init_check_scope(line, SCOPE_TRACE_ID_TBL);
            obj = (autogen_obj*)s_trcgrp;
        }
        break;
    }

    return obj;
}

/*  Init function for the VALUE macro
*/
void init_value(int line, int length, unsigned int order, const char* varname, const char* name, unsigned int pres)
{
    autogen_item_value* value;
    char* parname = pmd_heap_strdup(name);
        
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE | SCOPE_FTD_TBL_ENTRY | SCOPE_PRINTF);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check variable size in bits */
    init_check_length(line, length, TRUE, (PMD_FILE_FORMAT >= 600), (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* create and initialize item object */
    value = (autogen_item_value*)init_item_create(line, sizeof(autogen_item_value), AUTOGEN_ITEM_VALUE, 0, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&value->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    value->base.length = length;

    /* check data order */
    value->base.order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, length, (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* set transaction ID flag if first item */
    if (s_seq && (s_seq->base.type == AUTOGEN_OBJ_MSG || s_seq->base.type == AUTOGEN_OBJ_MSG_BASE) && (s_res->base.subtype & (RESOURCE_ISI_ANY | RESOURCE_TRC_STI)))
    {
        /* also, if first item in merged field, which then is first item */
        autogen_obj* item = autogen_obj_get_first_in_list(&s_seq->base.child_list);
        if (!item || (item->type == AUTOGEN_OBJ_ITEM && item->subtype == AUTOGEN_ITEM_MERGE && item->child_list.n_obj == 0))
        {
            value->base.special_number_type = PMD_NUMBER_SPECIAL_TYPE_TRANSACTION_ID;
        }
    }

    /* check presentation type and convert to number */
    {
        int new_length = init_pres_init(line, &value->pres, pres,
            AUTOGEN_PRESENTATION_VALUE_ANY | AUTOGEN_PRESENTATION_SYMBOL_ANY | 
            AUTOGEN_PRESENTATION_CHAR | AUTOGEN_PRESENTATION_FTDID | AUTOGEN_PRESENTATION_PPCID, 
            1.0f, 0.0f, NULL, length, s_res, TRUE);

        if (new_length != length)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. Value should be %ld", new_length);

            length = new_length;
        }

        /* check that no constant is defined */
        if (value->pres.type & AUTOGEN_PRESENTATION_SYMBOL_ANY)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                "The macro VALUE_CONST should be used instead");
        }
    }

#if (PMD_FILE_FORMAT >= 600)
    /* Align to 64 bits? */
    init_check_64_bit_alignment_prop(line, length);
#endif

    /* look for defined constants */
    init_check_string_prop(line, (autogen_obj*)value, PROPERTY_ITEM_MINIMUM_VALUE, (s_env->scope ? s_env->scope->feature_flags : NULL));
    init_check_string_prop(line, (autogen_obj*)value, PROPERTY_ITEM_MAXIMUM_VALUE, (s_env->scope ? s_env->scope->feature_flags : NULL));
    init_check_string_prop(line, (autogen_obj*)value, PROPERTY_ITEM_DEFAULT_VALUE, (s_env->scope ? s_env->scope->feature_flags : NULL));
    init_check_string_prop(line, (autogen_obj*)value, PROPERTY_ITEM_EXCEPTIONAL_VALUE, (s_env->scope ? s_env->scope->feature_flags : NULL));
    /* end look for defined constants */

    /* check item limits */
    check_item_limits(s_file, value);

    /* check default value */
    check_item_default_value(s_file, &value->base);

    /* handle filler replacement */
    init_handle_filler_replacement(line, &value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* Value is default not parameter in a scope printf */
    if (s_env->scope->scope == SCOPE_PRINTF)
    {
        if (!prop_has((autogen_obj*)value, PROPERTY_PMD_IS_NOT_PARAMETER))
        {
            prop_add_simple_to_object((autogen_obj*)value, PROPERTY_PMD_IS_NOT_PARAMETER, NULL, 0, 0);
        }
    }
    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += abs(length); 
    }
    else if (s_env->scope->scope == SCOPE_FTD_TBL_ENTRY)
    {
        s_env->ftd_length_sum += abs(length);
    }

    /* add item object to sequence object */
    init_item_add(&value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}

    
/*  Init function for the VALUE_EX macro
*/
void init_value_ex(int line, int length, unsigned int order, const char* varname, const char* name, unsigned int pres, double scale, double offset, const char* unit)
{
    autogen_item_value* value;
    char* parname = pmd_heap_strdup(name);
        
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_TRACE | SCOPE_CASE | SCOPE_FTD_TBL_ENTRY);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check variable size in bits */
    init_check_length(line, length, TRUE, (PMD_FILE_FORMAT >= 600), (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* create and initialize item object */
    value = (autogen_item_value*)init_item_create(line, sizeof(autogen_item_value), AUTOGEN_ITEM_VALUE, 0, varname, parname, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* copy version */
    memcpy(&value->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    value->base.length = length;

    /* check data order */
    value->base.order = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, length, (s_res->base.subtype & (RESOURCE_PROTOCOL | RESOURCE_TRC_ANY)) != 0);

    /* check presentation type and convert to number */
    init_pres_init(line, &value->pres, pres, AUTOGEN_PRESENTATION_VALUE_ANY, 
        scale, offset, unit, length, NULL, FALSE);

    init_check_string_prop(line, (autogen_obj*)value, PROPERTY_ITEM_MINIMUM_VALUE, (s_env->scope ? s_env->scope->feature_flags : NULL));
    init_check_string_prop(line, (autogen_obj*)value, PROPERTY_ITEM_MAXIMUM_VALUE, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* check item limits */
    check_item_limits(s_file, value);

    /* check default value */
    check_item_default_value(s_file, &value->base);

    /* handle filler replacement */
    init_handle_filler_replacement(line, &value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += abs(length); 
    }
    else if (s_env->scope->scope == SCOPE_FTD_TBL_ENTRY)
    {
        s_env->ftd_length_sum += abs(length);
    }

    /* add item object to sequence object */
    init_item_add(&value->base, (s_env->scope ? s_env->scope->feature_flags : NULL));
}

LOCAL int init_pres_init(int line, autogen_pres* pres, unsigned int presflag, unsigned int presmask,
    double scale, double offset, const char* unit, int length, autogen_res* tblres, int check_length)
{
    const autogen_symbol_conf* p_sym_conf = util_get_sym_conf_by_type(presflag);
    int ret_length = length;

    pres->type    = AUTOGEN_PRESENTATION_NONE;
    pres->scale   = 1.0f;
    pres->offset  = 0.0f;
    pres->tblname = NULL;
    pres->tblres  = NULL;
    pres->unit    = NULL;
    pres->obj     = NULL;


    /* convert presentation type string to number */

    /* normal value presentations */
    if (presflag == DEC)
    {
        pres->type = AUTOGEN_PRESENTATION_DEC;
    }
    else if (presflag == HEX)
    {
        pres->type = AUTOGEN_PRESENTATION_HEX;
    }
    else if (presflag == BIN)
    {
        pres->type = AUTOGEN_PRESENTATION_BIN;
    }
    /* Qn encoding */
    else if (presflag >= Q1 && presflag <= Q70)
    {
        unsigned int n = presflag - Q1 + 1;

        if (abs(length) < 2)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'length' is out of range. Absolute value should be > 1 for presentation 'QXX'");

            pres->type = AUTOGEN_PRESENTATION_DEC;
        }
        else if (n == 0)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'pres' is out of range. Value should be > 0");
        }

        pres->type    = AUTOGEN_PRESENTATION_QN;
        pres->subtype = (unsigned int)n;
    }
    /* Global symbols */
    else if (p_sym_conf)
    {
        pres->type    = p_sym_conf->pres_flag;
        pres->subtype = presflag;
        pres->tblname = p_sym_conf->tblname;
        pres->tblres  = util_get_unique_res(RESOURCE_SYMBOLS);

        ret_length    = p_sym_conf->length;
    }
    /* ID tables */
    else if (presflag == MSG_ID || presflag == SUB_MSG_ID)
    {
        /* Not supported anymore */
        pres->type = AUTOGEN_PRESENTATION_HEX;
        return 8;
    }
    else if (presflag == FTD_ID)
    {
        pres->type = AUTOGEN_PRESENTATION_FTDID;

        if (check_length && length != 16)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. Value must be 16 for this presentation");
        }
        /* check that the resource is common messages or media control */
        if (tblres->base.subtype != RESOURCE_ISI_COMMON_MESSAGES && 
            tblres->base.subtype != RESOURCE_ISI_COMMON_MESSAGES_EXT && 
            tblres->base.subtype != RESOURCE_ISI_MEDIA_CONTROL)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'pres' is not valid in this context");
        }

        ret_length = 16;
    }
    else if (presflag == PPC_ID)
    {
        pres->type = AUTOGEN_PRESENTATION_PPCID;

        if (check_length && length != 16)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. Value must be 16 for this presentation");
        }

        ret_length = 16;
    }
    else if (presflag == ASCII_CHAR)
    {
        pres->type = AUTOGEN_PRESENTATION_ASCII_CHAR;

        if (check_length && length != -8)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. Value must be -8 for this presentation");
        }

        ret_length = -8;
    }
    else if (presflag == UNICODE_CHAR)
    {
        pres->type = AUTOGEN_PRESENTATION_UNICODE_CHAR;

        if (check_length && length != -16)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is out of range. Value must be -16 for this presentation");
        }

        ret_length = -16;
    }
    else if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
    {
        pres->type = AUTOGEN_PRESENTATION_HEX;

        ret_length = abs(length);
        if (ret_length == 0)
        {
            ret_length = 8;
        }
    }
    /* invalid presentation */
    else 
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'pres' is not valid");
    }

    /* set linear transformation */

    /* check that scale is not 0 */
    if (scale == 0.0f)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'scale' is not valid");
    }
    else if (scale != 1.0f)
    {
        /* check that presentation type is DEC */
        if (!(pres->type & AUTOGEN_PRESENTATION_DEC))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'scale' is not valid in this context");

            pres->type = AUTOGEN_PRESENTATION_DEC;
        }

        pres->type |= AUTOGEN_PRESENTATION_SCALAR;
        pres->scale = scale;
    }

    if (offset != 0.0f)
    {
        /* check that presentation type is DEC */
        if (!(pres->type & (AUTOGEN_PRESENTATION_DEC | AUTOGEN_PRESENTATION_QN)))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'offset' is not valid in this context");

            pres->type &= AUTOGEN_PRESENTATION_SCALAR;
            pres->type |= AUTOGEN_PRESENTATION_DEC;
        }

        pres->type |= AUTOGEN_PRESENTATION_OFFSET;
        pres->offset = offset;
    }

    /* is a unit of measure defined ? */
    if (unit && unit[0])
    {
        /* check that presentation type is DEC or STRING */
        if (!(pres->type & (AUTOGEN_PRESENTATION_QN | AUTOGEN_PRESENTATION_DEC)))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument 'unit' is not valid in this context");
        }
        else
        {
            pres->type |= AUTOGEN_PRESENTATION_UNIT;
            pres->unit = unit;
        }
    }

    /* check that presentation type is valid in this context */
    if ((pres->type & presmask) == 0 && pres->type != presmask)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'pres' is not valid in this context");
    }

    return ret_length;
}

LOCAL int init_pres_const(int line, autogen_pres* pres, unsigned int presmask, const char* tblname, autogen_res* tblres)
{
    const autogen_symbol_conf* p_sym_conf = util_get_sym_conf_by_name(tblname);
    int ret_length = 0;

    pres->type    = AUTOGEN_PRESENTATION_NONE;
    pres->tblname = NULL;
    pres->tblres  = NULL;


    /* Global symbols */
    if (p_sym_conf)
    {
        pres->type    = p_sym_conf->pres_flag;
        pres->subtype = p_sym_conf->type;
        pres->tblname = p_sym_conf->tblname;
        pres->tblres  = util_get_unique_res(RESOURCE_SYMBOLS);

        ret_length    = p_sym_conf->length;
    }
    /* ID tables */
    else if (!strcmp(tblname, "MSG_ID") || !strcmp(tblname, "SUB_MSG_ID"))
    {
        /* not supported anymore */
        pres->type = AUTOGEN_PRESENTATION_HEX;
        return 8;
    }
    else if (!strcmp(tblname, "FTD_ID"))
    {
        pres->type = AUTOGEN_PRESENTATION_FTDID;

        /* check that the resource is common messages or media control */
        if (tblres->base.subtype != RESOURCE_ISI_COMMON_MESSAGES && 
            tblres->base.subtype != RESOURCE_ISI_COMMON_MESSAGES_EXT && 
            tblres->base.subtype != RESOURCE_ISI_MEDIA_CONTROL)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'pres' is not valid in this context");
        }

        ret_length = 16;
    }
    else if (!strcmp(tblname, "PPC_ID"))
    {
        pres->type = AUTOGEN_PRESENTATION_PPCID;

        ret_length = 16;
    }
    else
    {
        pres->type    = AUTOGEN_PRESENTATION_CONST;
        pres->tblname = tblname;
        pres->tblres  = tblres;

        ret_length = 0;
    }

    /* check that presentation type is valid in this context */
    if ((pres->type & presmask) == 0 && pres->type != presmask)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'pres' is not valid in this context");
    }

    return ret_length;
}

void init_range_begin(int line, int length, unsigned int order, const char* varname, const char* name)
{
    autogen_item_value* range;
    char* parname = pmd_heap_strdup(name);

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_IS_SEQ | SCOPE_MERGE | SCOPE_CASE);

    /* check variable name */
    check_c_name(s_file, line, "varname", varname, CHECK_NAME_EXIT_ON_FAIL);

    /* check parameter name */
    check_parname(s_file, line, parname);

    /* check variable size in bits */
    init_check_length(line, length, TRUE, FALSE, FALSE);

    /* create and initialize item object */
    range = (autogen_item_value*)init_item_create(line, sizeof(autogen_item_value), AUTOGEN_ITEM_RANGE, 0, varname, parname, NULL);

    autogen_obj_list_init(&range->base.base.child_list, &range->base.base, 0, 10);

    /* copy version */
    memcpy(&range->base.base.ver, &s_env->scope->parent->ver, sizeof(autogen_ver));

    range->base.length = length;
    range->base.order  = init_check_order(line, AUTOGEN_ORDER_BE | AUTOGEN_ORDER_LE, order, length, FALSE);
    range->pres.type   = AUTOGEN_PRESENTATION_DEC;

    /* update merge info */
    if (s_env->scope->scope == SCOPE_MERGE)
    {
        s_merge_length += abs(length); 
    }

    /* add item object to sequence object */
    init_item_add(&range->base, NULL);

    /* set new scope and parent */
    init_scope_set(SCOPE_RANGE, &range->base.base);
}

void init_range_end(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RANGE);

    /* restore last scope and parent */
    init_scope_restore();
}

void init_range_entry_value_ex(int line, unsigned int from, unsigned int to, double scale, double offset, const char* unit, unsigned int pres)
{
    autogen_item* range = (autogen_item*)s_env->scope->parent;
    autogen_item_range_entry* entry_item = NULL;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RANGE);

    /* create and initialize case item object */
    entry_item = (autogen_item_range_entry*)init_item_create(line, sizeof(autogen_item_range_entry), AUTOGEN_ITEM_RANGE_ENTRY, AUTOGEN_RANGE_ENTRY_VALUE_EX, "", "", NULL);

    entry_item->from = from;
    entry_item->to   = to;

    init_pres_init(line, &entry_item->pres, pres, AUTOGEN_PRESENTATION_VALUE_ANY, 
        scale, offset, unit, range->length, NULL, FALSE);

    /* copy version info from range element */
    memcpy(&entry_item->base.base.ver, &range->seq->base.ver, sizeof(autogen_ver));

    /* add range entry object to range object */
    init_item_add(&entry_item->base, NULL);
}

void init_range_entry_value(int line, unsigned int from, unsigned int to, unsigned int pres)
    {
    autogen_item* range = (autogen_item*)s_env->scope->parent;
    autogen_item_range_entry* entry_item = NULL;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RANGE);

    /* create and initialize case item object */
    entry_item = (autogen_item_range_entry*)init_item_create(line, sizeof(autogen_item_range_entry), AUTOGEN_ITEM_RANGE_ENTRY, AUTOGEN_RANGE_ENTRY_VALUE, "", "", NULL);

    entry_item->from = from;
    entry_item->to   = to;

    init_pres_init(line, &entry_item->pres, pres, AUTOGEN_PRESENTATION_VALUE_ANY, 
        1.0f, 0.0f, "", range->length, NULL, FALSE);

    /* copy version info from range element */
    memcpy(&entry_item->base.base.ver, &range->seq->base.ver, sizeof(autogen_ver));

    /* add range entry object to range object */
    init_item_add(&entry_item->base, NULL);
    }

void init_range_entry_string(int line, unsigned int from, unsigned int to, const char* text)
{
    autogen_item* range = (autogen_item*)s_env->scope->parent;
    autogen_item_range_entry* entry_item = NULL;

    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RANGE);

    /* create and initialize case item object */
    entry_item = (autogen_item_range_entry*)init_item_create(line, sizeof(autogen_item_range_entry), AUTOGEN_ITEM_RANGE_ENTRY, AUTOGEN_RANGE_ENTRY_STRING, "", "", NULL);

    entry_item->from = from;
    entry_item->to   = to;
    entry_item->text = text;

    /* copy version info from range element */
    memcpy(&entry_item->base.base.ver, &range->seq->base.ver, sizeof(autogen_ver));

    /* add range entry object to range object */
    init_item_add(&entry_item->base, NULL);
}

LOCAL void init_update_properties_comments(autogen_obj* obj)
{
    if (s_object)
    {
        if (obj != s_object)
        {
            obj->flag     |= s_object->flag;
            obj->cmt_list  = s_object->cmt_list;

            prop_copy_list_to_object(s_object->prop_list, obj, NULL);
        }

        s_object = NULL;
    }

    /* update properties */
    prop_add_current_to_object(obj, s_file);
}

LOCAL void init_clear_properties_comments(int line)
{
    /* empty properties */
    prop_force_current_empty(s_file);

    /* empty comments/properties */
    if (s_object)
    {
        if (s_object->cmt_list)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                "Orphaned comments ignored");
        }
        if (s_object->prop_list)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                "Orphaned properties ignored");
        }
        s_object = NULL;
    }
}


void init_msg_id_section(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    if (s_res->msg_id_section)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0, 
            "Multiple definition of message ID section");
    }
    else
    {
        if (s_object)
        {
            s_res->msg_id_section = s_object;
            s_object = NULL;
        }
        else
        {
            s_res->msg_id_section = autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_obj), AUTOGEN_OBJ_MSG_ID_SECTION, 0, 0, NULL, (s_env->scope ? s_env->scope->feature_flags : NULL));
        }
    }

    /* update properties and comments */
    init_update_properties_comments(s_res->msg_id_section);
}

void init_sb_id_section(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    if (s_res->sb_id_section)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0, 
            "Multiple definition of subblock ID section");
    }
    else
    {
        if (s_object)
        {
            s_res->sb_id_section = s_object;
            s_object = NULL;
        }
        else
        {
            s_res->sb_id_section = autogen_obj_create(s_file, line, s_res, &s_res->base, sizeof(autogen_obj), AUTOGEN_OBJ_SB_ID_SECTION, 0, 0, NULL, (s_env->scope ? s_env->scope->feature_flags : NULL));
        }
    }

    /* update properties and comments */
    init_update_properties_comments(s_res->sb_id_section);
}

LOCAL void init_update_item_offsets(autogen_obj_list* obj_list, autogen_ver* ver, unsigned int* offset_type, unsigned int* offset)
{
    unsigned int local_offset = 0;

    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        unsigned int u_length = (unsigned int)abs(item->length)/8;

        /* Set offset and type on item */
        if (item->base.flag & AUTOGEN_ITEM_IS_PART_OF_MERGE)
        {
            if (item->offset_type == AUTOGEN_ITEM_OFFSET_UNDEFINED)
            {
                if ((local_offset % 8) == 0)
                {
                    item->offset_type = AUTOGEN_ITEM_OFFSET_EXACT;
                    item->offset      = *offset;
                }
                else
                {
                    item->offset_type = AUTOGEN_ITEM_OFFSET_EXACT_UNALIGNED;
                    item->offset      = local_offset;
                }
            }
            else if (item->offset_type == AUTOGEN_ITEM_OFFSET_EXACT && item->offset != *offset || (local_offset % 8) != 0)
            {
                item->offset_type = AUTOGEN_ITEM_OFFSET_VARIABLE;
                item->offset      = 0;
            }
            else if (item->offset_type == AUTOGEN_ITEM_OFFSET_EXACT_UNALIGNED && item->offset != local_offset)
            {
                item->offset_type = AUTOGEN_ITEM_OFFSET_VARIABLE;
                item->offset      = 0;
            }
        }
        else
        {
            if (item->offset_type == AUTOGEN_ITEM_OFFSET_UNDEFINED)
            {
                item->offset_type = AUTOGEN_ITEM_OFFSET_EXACT;
                item->offset      = *offset;
            }
            else if (item->offset_type == AUTOGEN_ITEM_OFFSET_EXACT && item->offset != *offset)
            {
                item->offset_type = AUTOGEN_ITEM_OFFSET_VARIABLE;
                item->offset      = 0;
            }
        }

        /* if optional element */
        if (item->agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE ||
            item->agg_type == AGG_TYPE_DYNAMIC_OPTIONAL ||
            item->agg_type == AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH ||
            item->agg_type == AGG_TYPE_DYNAMIC_REF ||
            item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT ||
            item->agg_type == AGG_TYPE_DYNAMIC_ZEROTERMINATED)
        {
            *offset_type = AUTOGEN_ITEM_OFFSET_VARIABLE;
            *offset      = 0;
        }

        switch (item->base.subtype)
        {
        case AUTOGEN_ITEM_MERGE:
            {
                unsigned int merge_offset_type = *offset_type; 
                unsigned int merge_offset      = *offset;

                init_update_item_offsets(&item->base.child_list, ver, &merge_offset_type, &merge_offset);

                *offset += (unsigned int)item->agg_n * u_length;
            }
            break;

        case AUTOGEN_ITEM_VALUE:
        case AUTOGEN_ITEM_RANGE:
        case AUTOGEN_ITEM_POINTER:
        case AUTOGEN_ITEM_TIMESTAMP:
        case AUTOGEN_ITEM_BLOCK:
        case AUTOGEN_ITEM_REF:
            {
                if (item->agg_type == AGG_TYPE_FIXED_SINGLE ||
                    item->agg_type == AGG_TYPE_FIXED_MULTIPLE)
                {
                    *offset += (unsigned int)item->agg_n * u_length;
                }
            }
            break;

        case AUTOGEN_ITEM_FILLER:
            {
                if (item->agg_type != AGG_TYPE_DYNAMIC_ALIGNMENT)
                {
                    *offset += (unsigned int)item->agg_n * u_length;
                }
            }
            break;

        case AUTOGEN_ITEM_STRING:
            {
                autogen_item_string* item_str = (autogen_item_string*)item;

                if (item->agg_type == AGG_TYPE_FIXED_SINGLE ||
                    item->agg_type == AGG_TYPE_FIXED_MULTIPLE)
                {
                    unsigned int item_size = (unsigned int)item->agg_n * (unsigned int)item_str->length;

                    if (item->base.flag & AUTOGEN_STRING_UNICODE)
                    {
                        item_size *= 2; 
                    }

                    *offset += item_size;
                }
            }
            break;

        case AUTOGEN_ITEM_LST:
        case AUTOGEN_ITEM_TRCSTRUCTURE:
        case AUTOGEN_ITEM_STRUCT:
            {
                *offset_type = AUTOGEN_ITEM_OFFSET_VARIABLE;
                *offset      = 0;
            }
            break;

        case AUTOGEN_ITEM_CHOICE:
            {
                autogen_obj* case_item;
                autogen_it case_it = INIT_ITERATOR;

                case_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
                case_it.ver     = ver;

                case_item = autogen_obj_find_in_list(&case_it, &item->base.child_list);
                while (case_item)
                {
                    unsigned int case_offset_type = *offset_type; 
                    unsigned int case_offset      = *offset;

                    init_update_item_offsets(&case_item->child_list, ver, &case_offset_type, &case_offset);

                    case_item = autogen_obj_find_next_in_list(&case_it);
                }

                *offset_type = AUTOGEN_ITEM_OFFSET_VARIABLE;
                *offset      = 0;
            }
            break;

        case AUTOGEN_ITEM_RANGE_ENTRY:
            {
            }
            break;

        default:
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Default case met in init_update_item_offsets(). "
                    "item->base.subtype is 0x%8.8X",
                    item->base.subtype);
            }
            break;
        }

        if (item->base.flag & AUTOGEN_ITEM_IS_PART_OF_MERGE)
        {
            local_offset += (unsigned int)abs(item->length);
        }

        item = (autogen_item*)item->base.next;
    }
}

/*  Init function for the TRACE_GROUP_BEGIN */
void init_trace_group_begin(int line, const char* name, unsigned int id, int state, const char* dectext, const char* macro)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES);

    /* add the trace group */
    init_trace_group_add(line, s_res, name, id, state, macro, FALSE);

    /* Replace decode text for the trace group with the defined one */
    if (dectext && dectext[0])
    {
        if (prop_has((autogen_obj*)s_trcgrp, PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT))
        {
            prop_object_update_string((autogen_obj*)s_trcgrp, PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT, dectext);
        }
        else
        {
            prop_add_string_to_object((autogen_obj*)s_trcgrp, PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT, dectext, NULL, 0, FALSE);
        }
    }

    /* set new scope and parent */
    init_scope_set(SCOPE_TRACE_ID_TBL, &s_trcgrp->base);
}

void init_trace_group_end(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_TRACE_ID_TBL);

    /* empty properties and comments */
    init_clear_properties_comments(line);

    /* restore last scope and parent */
    init_scope_restore();

    s_trcgrp = NULL;
}

LOCAL void init_post_processing_seq(autogen_seq* seq)
{
    autogen_item* item = NULL;
    autogen_it item_it = INIT_ITERATOR;

    item_it.typemask    = AUTOGEN_OBJ_ITEM;
    item_it.subtypemask = AUTOGEN_ITEM_VALUE;
    item_it.flagall     = AUTOGEN_ITEM_USE_IMPORTED_RES | AUTOGEN_ITEM_USE_IMPORTED_RES_NOT_RESOLVED;

    item = (autogen_item*)autogen_obj_find_in_list(&item_it, &seq->base.child_list);
    while (item)
    {
        autogen_item_value* value = (autogen_item_value*)item;
        autogen_res* tblres;

        /* Find resource object from name (VALUE_CONST_IMP argument) */
        {
            autogen_it tblres_it = INIT_ITERATOR;

            tblres_it.typemask    = AUTOGEN_OBJ_RES;
            tblres_it.obj.name    = value->pres.tblresname;

            tblres = (autogen_res*)autogen_obj_find_in_list(&tblres_it, g_res_list);
            if (!tblres)
            {
                /* resource wasn't found. Replace constant with HEX presentation */
                item->base.flag &= ~(AUTOGEN_ITEM_USE_IMPORTED_RES | AUTOGEN_ITEM_USE_IMPORTED_RES_NOT_RESOLVED);

                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                    "Referred resource '%s' from VALUE_CONST_IMP doesn't exist", value->pres.tblresname);

                item = (autogen_item*)autogen_obj_find_next_in_list(&item_it);
                continue;
            }
            else
            {
                value->pres.tblres = tblres;
            }
        }

        /* Find table within resource */
        {
            autogen_tbl* tbl;
            autogen_it tbl_it = INIT_ITERATOR;

            tbl_it.obj.name = value->pres.tblname;
            tbl_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            tbl_it.ver      = &tblres->base.ver;
            if (value->base.base.feature_flags)
            {
                tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                tbl_it.obj.feature_flags = value->base.base.feature_flags;
            }

            tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &tblres->tbl_list);
            if (!tbl && tblres->shared_res)
            {
                /* Table wasn't found in resource. Try in shared resource */
                tbl_it.ver = &tblres->shared_res->base.ver;

                tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &tblres->shared_res->tbl_list);

                value->pres.tblres = tblres->shared_res;
            }
            if (!tbl && (tblres->base.flag & AUTOGEN_RES_HAS_EXTENSIONS))
            {
                /* Table wasn't found in shared resource. Try in resource extensions */
                autogen_res* ext_res = util_get_ext_res(tblres->base.subtype, tblres->base.id);
                if (ext_res)
                {
                    /* Table wasn't found in resource. Try in shared resource */
                    tbl_it.ver = &ext_res->base.ver;

                    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &ext_res->tbl_list);

                    value->pres.tblres = ext_res;
                }
            }
            if (!tbl)
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Referred table '%s' isn't defined in the used version of resource '%s'", value->pres.tblname, value->pres.tblresname);

                /* Remove flag AUTOGEN_ITEM_USE_IMPORTED_RES */
                item->base.flag &= ~(AUTOGEN_ITEM_USE_IMPORTED_RES | AUTOGEN_ITEM_USE_IMPORTED_RES_NOT_RESOLVED);
            }
            else
            {
                init_pres_const(0, &value->pres, AUTOGEN_PRESENTATION_CONST, value->pres.tblname, value->pres.tblres);

                value->base.length = tbl->orgtbl->length;
            }
        }

        /* Remove flag AUTOGEN_ITEM_USE_IMPORTED_RES_NOT_RESOLVED again */
        item->base.flag &= ~AUTOGEN_ITEM_USE_IMPORTED_RES_NOT_RESOLVED;

        item = (autogen_item*)autogen_obj_find_next_in_list(&item_it);
    }
}


/* Function to be invoked after all message macro files have been parsed. 
   Global links are resolved:
     constant table references (VALUE_CONST_IMP macro)
*/
LOCAL void init_post_processing()
{
    autogen_res* res = NULL;

           
    /* iterate through all resources */
    res = (autogen_res*)autogen_obj_get_first_in_list(g_res_list);
    while (res)
    {
        autogen_seq* seq;

        /* sequences */
        seq = (autogen_seq*)autogen_obj_get_first_in_list(&res->seq_list);
        while (seq)
        {
            init_post_processing_seq(seq);

            seq = (autogen_seq*)seq->base.next;
        }

        /* messages */
        seq = (autogen_seq*)autogen_obj_get_first_in_list(&res->msg_list);
        while (seq)
        {
            init_post_processing_seq(seq);

            seq = (autogen_seq*)seq->base.next;
        }

        /* traces */
        if (res->trcgrp_list)
        {
            autogen_obj* trcgrp = autogen_obj_get_first_in_list(res->trcgrp_list);
            while (trcgrp)
            {
                if (trcgrp->type == AUTOGEN_OBJ_TRACEGRP)
                {
                    seq = (autogen_seq*)autogen_obj_get_first_in_list(&trcgrp->child_list);
                    while (seq)
                    {
                        init_post_processing_seq(seq);

                        seq = (autogen_seq*)seq->base.next;
                    }
                }
                else if (trcgrp->type == AUTOGEN_OBJ_TRACE)
                {
                    init_post_processing_seq((autogen_seq*)trcgrp);
                }

                trcgrp = trcgrp->next;
            }
        }

        res = (autogen_res*)res->base.next;
    }

    /* in product environment, check if any empty trace groups exist */
    if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
    {
        unsigned int n;

        for (n = 1; n < AUTOGEN_OBJ_TRACEGRP_MAX; n++)
        {
            if (g_trcgrp_conf[n].list)
            {
                autogen_obj_list* trcgrp_list = g_trcgrp_conf[n].list[0];
                if (trcgrp_list && g_trcgrp_conf[n].has_groups)
                {
                    autogen_trcgrp* trcgrp = (autogen_trcgrp*)autogen_obj_get_first_in_list(trcgrp_list);
                    while (trcgrp)
                    {
                        if (!trcgrp->has_traces)
                        {
                            util_error_line(s_file, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_PRODUCT, 0,
                                "No traces are defined for group '%s'", trcgrp->base.name);

                            g_trcgrp_conf[n].conflicts = TRUE;
                        }

                        trcgrp = (autogen_trcgrp*)trcgrp->base.next;
                    }
                }
            }
        }
    }

    /* combine message ID fields on PROTOCOL / PROTOCOL_EXTENSIONS */
    res = (autogen_res*)autogen_obj_get_first_in_list(g_res_list);
    while (res)
    {
        if (res->base.subtype == RESOURCE_PROTOCOL)
        {
            autogen_it ext_res_it = INIT_ITERATOR;
            autogen_res* ext_res;
            
            ext_res_it.subtypemask = RESOURCE_PROTOCOL_EXTENSION;
            ext_res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
            ext_res_it.obj.id      = res->base.id;

            ext_res = (autogen_res*)autogen_obj_find_in_list(&ext_res_it, g_res_list);
            while (ext_res)
            {
                /* values are set on resource */
                if (res->msg_id_offset != AUTOGEN_VALUE_VARIES)
                {
                    /* if values are not set on extension, set them */
                    if (ext_res->msg_id_offset == AUTOGEN_VALUE_VARIES)
                    {
                        ext_res->msg_id_size      = res->msg_id_size;
                        ext_res->msg_id_offset    = res->msg_id_offset;
                    }
                    /* else check that values are identiacal! */
                    else if (ext_res->msg_id_size != res->msg_id_size)
                    {
                        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                            "Reference 'MSG_ID' length is not identical across PROTOCOL resources '%s'", res->base.name);
                        return; /* To avoid lint warnings */
                    }
                    /* else check that values are identiacal! */
                    else if (ext_res->msg_id_offset != res->msg_id_offset)
                    {
                        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                            "Reference 'MSG_ID' is not placed at same offset in all PROTOCOL resources '%s'", res->base.name);
                        return; /* To avoid lint warnings */
                    }
                }
                /* else copy values from extension */
                else
                {
                    res->msg_id_size   = ext_res->msg_id_size;
                    res->msg_id_offset = ext_res->msg_id_offset;
                }

                ext_res = (autogen_res*)autogen_obj_find_next_in_list(&ext_res_it);
            }
        }

        res = (autogen_res*)res->base.next;
    } 
}


/*  Adds trace group. Common to TRACE_GROUP_BEGIN / TRACE_GROUP_DECODER */
void init_trace_group_add(int line, autogen_res* res, const char* name, unsigned int id, int state, const char* macro, int duplicate_overrule)
{
    const char* str_grp = NULL;
    unsigned int trc_type = util_get_tracegroup_type(res);

    /* check arguments */
    check_c_name(s_file, line, "name", name, CHECK_NAME_EXIT_ON_FAIL);

    /* verify that the current resource is a valid resource */
    if (trc_type == AUTOGEN_OBJ_TRACEGRP_NONE)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Macro %s can't be used in this context", macro);
    }

    /* Check trace group ID */
    if (id != AUTOGEN_TRACE_GROUP_ID_UNDEFINED)
    {
        if (id > 0xFFFF)
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'id' for trace group '%s' is 0x%X, which is out of range", name, id);
        }
    }

    /* change group name from MON_XXX_GRP to XXX */
    if (strlen(name) > 8 && !strncmp(name, "MON_", 4) && !strcmp(&name[strlen(name)-4], "_GRP"))
    {
        char* str_grp_ = pmd_heap_strdup(&name[4]);
        str_grp_[strlen(name) - 8] = '\0';

        str_grp = str_grp_;
    }
    else
    {
        str_grp = name;
    }

    /* create trace group object */
    {
        unsigned int flag = 0;

        autogen_trcgrp* old_trcgrp;
        autogen_it trc_grp_it = INIT_ITERATOR;

        trc_grp_it.typemask = AUTOGEN_OBJ_TRACEGRP;
        trc_grp_it.obj.name = str_grp;
        if (s_env->scope ? s_env->scope->feature_flags : NULL)
        {
            trc_grp_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            trc_grp_it.obj.feature_flags = s_env->scope->feature_flags;
        }

        /* Clear global trace group pointer */
        s_trcgrp = NULL;

        if (state == OFF)
        {
            flag |= AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;
        }

        old_trcgrp = (autogen_trcgrp*)autogen_obj_find_in_list(&trc_grp_it, res->trcgrp_list);
        if (!old_trcgrp)
        {
            /* set trace group ID */
            if (id == AUTOGEN_TRACE_GROUP_ID_UNDEFINED)
            {
                if (state == ON || g_autogen_env == AUTOGEN_ENV_LOCAL)
                {
                    id = ++s_trcgrp_id[trc_type];
                }
                else
                {
                    id = 0;
                }
            }
        }
        /* trace group does exist, but should be overruled (TRACE_GROUP_DECODER) */
        else if (duplicate_overrule)
        {
            s_trcgrp = old_trcgrp;

            /* Clear traces in group */
            s_trcgrp->has_traces            = TRUE;
            s_trcgrp->base.child_list.n_obj = 0;
        }
        /* Create dummy group */
        else
        {
            id = 0;

            flag |= AUTOGEN_TRACEGRP_TEMPORARY_GROUP;

            util_error_line(s_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
                "Redefinition of the trace group '%s'", name);
        }

        /* Create new/temporary group... */
        if (!s_trcgrp)
        {
            /* create and initilize trace group object */
            s_trcgrp = (autogen_trcgrp*)autogen_obj_create(s_file, line, res, &res->base, sizeof(autogen_trcgrp), 
                                                           AUTOGEN_OBJ_TRACEGRP, trc_type, id, str_grp, 
                                                           (s_env->scope ? s_env->scope->feature_flags : NULL));

            autogen_obj_list_init(&s_trcgrp->base.child_list, &s_trcgrp->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 50);

            s_trcgrp->base.flag |= flag;

            /* update properties and comments */
            init_update_properties_comments((autogen_obj*)s_trcgrp);

            /* set trace identifier */
            if (prop_has(&s_trcgrp->base, PROPERTY_PMD_TRACE_IDENTIFIER))
            {
                s_trcgrp->identifier = prop_get_string(&s_trcgrp->base, PROPERTY_PMD_TRACE_IDENTIFIER);
            }
            else
            {
                /* prevent MCU traces from having identifer = "isi" */
                if (pmd_constant_lookup_message_type_flags(res->conf->msg_type) == pmd_constant_lookup_message_type_flags(g_trcgrp_conf[trc_type].msg_type))
                {
                    s_trcgrp->identifier = res->identifier;
                }
                else
                {
                    s_trcgrp->identifier = pmd_constant_lookup_message_type_identifier(g_trcgrp_conf[trc_type].msg_type);
                }
            }

            /* add trace group object to resource */
            autogen_obj_list_add_obj(res->trcgrp_list, &s_trcgrp->base, AUTOGEN_ENV_NONE);
        }
    }

    /* Reset trace id for the given type */
    s_trc_id[trc_type] = 0x0000;
}

autogen_feature* init_create_feature_flag(const char* flag1, const char* value1, const char* flag2, const char* value2, unsigned int flag_logic, autogen_feature *headFeature)
{
    /* Create the feature flag */
    autogen_feature* feature = (autogen_feature*)pmd_heap_alloc(sizeof(autogen_feature));
    if (flag1) 
    {
        feature->feature1 = (autogen_feature_flag*)pmd_heap_alloc(sizeof(autogen_feature_flag));
        feature->feature1->flag  = flag1;
        feature->feature1->value = value1;
    }
    if (flag2)
    {
        feature->feature2 = (autogen_feature_flag*)pmd_heap_alloc(sizeof(autogen_feature_flag));
        feature->feature2->flag  = flag2;
        feature->feature2->value = value2;
    }
    feature->flag_logic = flag_logic;
    feature->head = headFeature;

    return feature;
}

void init_feature_flag_begin(int line, const char* flag, const char* value)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES | SCOPE_IS_SEQ | SCOPE_IS_MSG | SCOPE_CONST_TBL | SCOPE_DER_CONST_TBL | SCOPE_BIT_TBL | SCOPE_DER_BIT_TBL);

    /* Check that flag and value is defined */
    if (!(flag && flag[0]) || !(value && value[0]))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Flag or value not defined for feature flag.");
    }

    /* No feature flag must currently be defined */
    if (!s_env->scope->feature_flags)
    {
        /* A flag with prefix AUTOGEN_ requires special handling. Will be converted to a #ifdef */
        if ((strlen(flag)>8) && !strncmp(flag, "AUTOGEN_", 8))
        {
            int flagLogic = FT_FLAG;

            char *flagToStore = (char *)pmd_heap_alloc(strlen(flag)-8+1);
            strcpy(flagToStore, flag+8);

            if (!strcmp(value, "ON")) 
            {
                flagLogic = FT_DEF_FLAG;
            }
            else if (!strcmp(value, "OFF"))
            {
                flagLogic = FT_NOTDEF_FLAG;
            }
            else 
            {
                /* Invalid flag value */
                util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Feature flag value must be ON or OFF");
            }
            s_env->scope->feature_flags = init_create_feature_flag(flagToStore, NULL, NULL, NULL, flagLogic, NULL);
        }
        else 
        {
            /* Normal situation */
            s_env->scope->feature_flags = init_create_feature_flag(flag, value, NULL, NULL, FT_FLAG, NULL);
        }
    }
    else
    {
        /* only one level of feature flags allowed*/
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Nested feature flags not allowed!");
    }
}

void init_feature_flag_or_flag_begin(int line, const char* flag1, const char* value1, const char* flag2, const char* value2)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES | SCOPE_IS_SEQ | SCOPE_IS_MSG | SCOPE_CONST_TBL | SCOPE_DER_CONST_TBL | SCOPE_BIT_TBL | SCOPE_DER_BIT_TBL);

    /* Check that flag and value is defined */
    if (!(flag1 && flag1[0]) || !(value1 && value1[0]) || !(flag2 && flag2[0]) || !(value2 && value2[0]))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Flag or value not defined for feature flag.");
    }

    /* No feature flag must currently be defined */
    if (!s_env->scope->feature_flags)
    {
        s_env->scope->feature_flags = init_create_feature_flag(flag1, value1, flag2, value2, FT_FLAG1_OR_FLAG2, NULL);
    }
    else
    {
        /* only one level of feature flags allowed*/
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Nested feature flags not allowed!");
    }
}

void init_feature_flag_and_flag_begin(int line, const char* flag1, const char* value1, const char* flag2, const char* value2)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES | SCOPE_IS_SEQ | SCOPE_IS_MSG | SCOPE_CONST_TBL | SCOPE_DER_CONST_TBL | SCOPE_BIT_TBL | SCOPE_DER_BIT_TBL);

    /* Check that flag and value is defined */
    if (!(flag1 && flag1[0]) || !(value1 && value1[0]) || !(flag2 && flag2[0]) || !(value2 && value2[0]))
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Flag or value not defined for feature flag.");
    }

    /* No feature flag must currently be defined */
    if (!s_env->scope->feature_flags)
    {
        s_env->scope->feature_flags = init_create_feature_flag(flag1, value1, flag2, value2, FT_FLAG1_AND_FLAG2, NULL);
    }
    else
    {
        /* only one level of feature flags allowed*/
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Nested feature flags not allowed!");
    }
}

void init_feature_flag_else(int line)
{
    /* check if macro is allowed in the current scope */
    init_check_scope(line, SCOPE_RES | SCOPE_IS_SEQ | SCOPE_IS_MSG | SCOPE_CONST_TBL | SCOPE_DER_CONST_TBL | SCOPE_BIT_TBL | SCOPE_DER_BIT_TBL);

    /* A feature flag definition must be in progress. */
    if (s_env->scope->feature_flags && s_env->scope->feature_flags->flag_logic != FT_ELSE )
    {
        /* Find the head of the if-else-end chain */
        autogen_feature *head = (s_env->scope->feature_flags->head == NULL ? s_env->scope->feature_flags : 
                                                                             s_env->scope->feature_flags->head);

        s_env->scope->feature_flags = init_create_feature_flag(NULL, NULL, NULL, NULL, FT_ELSE, head);
    }
    else
    {
        /* only one level of feature flags allowed*/
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Else feature flag used in wrong context!");
    }
}

void init_feature_flag_end(int line)
{
    if (!s_env->scope->feature_flags)
    {
        util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Misplaced FEATURE_FLAG_END()!");
    }
    s_env->scope->feature_flags = NULL;
}

void init_check_64_bit_alignment_prop(int line, int length)
{
    /* In case length is more than 32 bits we should use 64 bits alignment */
    /* A fatal error is generated unless alignment checking are disabled */
    if (!prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_CHECK_DISABLE))
    {
        if ((abs(length)>32) && (!prop_has((autogen_obj*)s_res, PROPERTY_ALIGNMENT_64_BITS)))
        {
            util_error_line(s_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "64-bit macros are being used without having applied resource property 'PROPERTY_ALIGNMENT_64_BITS'");
        }
    }
}


#ifdef AUTOGEN_ENVIRONMENT_LOCAL
void init_old_macro_used(const char* text)
{
    if (s_res)
    {
        autogen_obj* old_macro;
        autogen_it old_macros_it = INIT_ITERATOR;

        old_macros_it.obj.name = text;

        old_macro = autogen_obj_find_in_list(&old_macros_it, &s_res->old_macro_list);
        if (!old_macro)
        {
            old_macro = autogen_obj_create(NULL, 0, s_res, &s_res->base, sizeof(autogen_obj), AUTOGEN_OBJ_OLD_MACRO_USAGE, 0, ++s_last_old_macro_usage_warning_id, text, NULL);

            autogen_obj_list_add_obj(&s_res->old_macro_list, old_macro, AUTOGEN_ENV_NONE);
        }
    }
}
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

/*  End of file autogen_init.c  */
