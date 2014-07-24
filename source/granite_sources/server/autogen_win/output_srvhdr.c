/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_srvhdr.c
                ---------------
                SW Include






Project:          autogen

%name:            output_srvhdr.c %
%version:         co1tss#173 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Fri Jan 22 15:52:01 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file contains the ISI header file generation code
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_ref.h"
#include "autogen_prop.h"
#include "autogen_util.h"
#include "pmd_heap.h"
#include "autogen_ver_history.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <math.h>

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
#define LOCAL static
#endif /* LOCAL */


/* The length in characters of the maximum version string as
   formatted by hdr_format_ver 
*/
#define MAX_VERSION_LENGTH      30
#define MAX_MASKS               50

#define HDR_LINE_WIDTH          77
#define HDR_LINE_INDENT         4
#define HDR_LINE_COMMENT_START  25

/* ISI header file type */
#define ISIHDR_TYPE_8           1
#define ISIHDR_TYPE_16          2

typedef struct t_hdr_item_size
{
    struct t_hdr_item_size* next;

    char* type_name;

    char* aggs;

    unsigned int simple_count;
} hdr_item_size;

#define HDR_ITEM_ARRAY          0x00000001u
#define HDR_ITEM_ARRAY_2        0x00000002u
#define HDR_ITEM_STRUCT         0x00000004u
#define HDR_ITEM_MERGE          0x00000008u
#define HDR_ITEM_EMPTY          0x00000010u /* item only contains comments */
#define HDR_ITEM_NOT_IN_SIZE    0x00000020u /* item should not be part of size calculation */
#define HDR_ITEM_FILLER         0x00000080u
#define HDR_ITEM_UNION          0x00000100u
#define HDR_ITEM_FIXED_TYPENAME 0x00000200u /* Typename should not be changed for 8/16 bit file */
#define HDR_ITEM_FIXED_ARRAY    0x00000400u /* Array should not be changed for 8/16 bit file */
#define HDR_ITEM_POINTER        0x00000800u
#define HDR_ITEM_MERGE_HI       0x00001000u
#define HDR_ITEM_MERGE_LO       0x00002000u
#define HDR_ITEM_PHONET_HDR     0x00004000u /* Item is part of PhoNet header */

typedef struct t_hdr_item
    {
    struct t_hdr_item* next;
    struct t_hdr_item* child_list;

    /* variable name of item */
    const char* varname;
    const char* varname_16;

    /* parameter name of item */
    const char* parname;

    /* typde definition of item */
    const char* type_name;

    /* size of type in bits, eg. 8 for uint8 or uint8* */
    int type_length;

    /* size of field in bits, eg. 32 for uint32 or uint8* */
    int field_length;

    /* aggregation */
    unsigned agg_n[2];
    char* agg_str[2];

    /* comment */
    autogen_cmt* cmt;

    /* flags */
    unsigned int flags;

    /* version - for unions only */
    const unsigned short* ver_from;
    const unsigned short* ver_to;

    /* list of properties for item */
    autogen_prop* prop;

    /* feature flags for object */
    struct t_autogen_feature* feature_flags;

    /* presentation */
    autogen_pres pres;

    } hdr_item;

typedef struct t_hdr_environment
    {
    /* pointer to the isi header file */
    FILE* fout;

    /* pointer to the current server */
    autogen_res* res;

    /* range of versions seen in this resource */
    autogen_ver res_ver;

    /* Should PhoNet header be included in message structures? */
    int include_phonet_header;

    /* Layout (0-2) of PhoNet header */
    unsigned int phonet_header_layout;

    /* ISI header file type, either ISIHDR_TYPE_8 or ISIHDR_TYPE_16 */
    unsigned int type;

    /* Flag to use to exclude objects. Can be either
       AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_8 or AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_16
    */
    unsigned int dont_generate_flag;

    /* ISI header file name */
    const char* filename;

    /* handle to the pmd heap, now used all over in this file */
    pmd_heap_handle* heap_handle;

    /* Byte item to be saved for merge in 16 bit header file */
    hdr_item* isihdr_16_item_byte;

    } hdr_environment;


LOCAL FILE*     hdr_open_file(hdr_environment* env, char** trailer);
LOCAL void      hdr_server(hdr_environment* env);

LOCAL const char* hdr_format_ver(const autogen_ver* ver);
LOCAL char*     hdr_format_comment(unsigned int indent, int delimiters,
                                   const autogen_cmt* list);

LOCAL void      hdr_print_const(hdr_environment* env, int print_dup,
                                const autogen_obj* constant,
                                const char* trailing_comment);
LOCAL void      hdr_print_ver_cond(hdr_environment* env, const autogen_ver* ver);
LOCAL void      hdr_print_obj_header(hdr_environment* env, const autogen_obj* obj, const char* heading);
LOCAL void      hdr_print_table_header(hdr_environment* env, autogen_tbl *table);
LOCAL void      hdr_print_enum_header(hdr_environment* env, autogen_tbl* table);

LOCAL void      hdr_print_obj_trailer(hdr_environment* env, autogen_obj* obj);
LOCAL void      hdr_print_min_version(hdr_environment* env, 
                                      const unsigned short* ver, 
                                      int not);
LOCAL void print_feature_flag(hdr_environment* env, autogen_feature **lastFeatureFlag, autogen_feature *currentFeatureFlag);
LOCAL void hdr_print_feature_flag_begin(hdr_environment* env, const autogen_feature* feature_flags, int negate);
LOCAL void hdr_print_feature_flag_end(hdr_environment* env);

LOCAL const char* hdr_typename_from_length(int length);
LOCAL const char* hdr_ftd_typename_from_length(int length);

LOCAL void      hdr_cmt_append(hdr_environment* env, unsigned int type, const char* text, autogen_cmt** cmt_list);
LOCAL void      hdr_cmt_append_const_tbl(hdr_environment* env, const autogen_item_value* item, autogen_cmt** cmt_list);
LOCAL void      hdr_cmt_ensure_newline(hdr_environment *env, autogen_cmt **cmt);

LOCAL void      hdr_top_comment(hdr_environment* env, const autogen_cmt* cmt_list);

LOCAL void      hdr_before_comment(hdr_environment* env, const autogen_cmt* cmt_list);
LOCAL void      hdr_after_comment(hdr_environment* env, const autogen_cmt* cmt_list);

LOCAL void      hdr_seq_begin(hdr_environment* env);
LOCAL void      hdr_seq_end(hdr_environment* env, const hdr_item* item_list, autogen_seq* seq);

LOCAL void      hdr_structure_item_add(hdr_item** hdr_item_list, hdr_item* item);
LOCAL hdr_item* hdr_structure_item_clone(hdr_environment* env, autogen_item* item, unsigned int flags);
LOCAL hdr_item* hdr_structure_item_create(hdr_environment* env, const char* varname, const char* parname, int length, autogen_cmt* cmt, unsigned int flags);
LOCAL hdr_item* hdr_structure_item_merge(hdr_environment* env, hdr_item* item1, hdr_item* item2);
LOCAL void      hdr_structure_item_set_aggregation(hdr_environment* env, hdr_item* item, autogen_item* org_item);
LOCAL void      hdr_structure_item_set_comment(hdr_environment* env, hdr_item* item, autogen_item* org_item);
LOCAL void      hdr_structure_item_set_length(hdr_item* item, const autogen_item* org_item);
LOCAL void      hdr_structure_item_set_typename(hdr_environment* env, hdr_item* item, const autogen_item* org_item);
LOCAL hdr_item* hdr_structure_item_specialize_8(hdr_environment* env, hdr_item* item, const autogen_item* org_item);
LOCAL hdr_item* hdr_structure_item_specialize_16(hdr_environment* env, const autogen_seq* seq, 
                                                 hdr_item** hdr_item_list, hdr_item* item, const autogen_item* org_item);
LOCAL hdr_item* hdr_structure_item_split(hdr_environment* env, hdr_item* item, const char* varname1, const char* varname2, int length);

LOCAL void      hdr_structure_print_item(hdr_environment* env, const hdr_item* item, unsigned int indent);
LOCAL void      hdr_structure_print_items(hdr_environment* env, const hdr_item* item_list);
LOCAL void      hdr_structure_print_merge_constants(hdr_environment* env, const autogen_seq* seq, const hdr_item* item_list);
LOCAL void      hdr_structure_print_index_constants(hdr_environment* env, const autogen_seq* seq, const hdr_item* item_list);
LOCAL void      hdr_structure_print_value_constants(hdr_environment* env, const autogen_seq* seq, const hdr_item* item_list);

LOCAL void		hdr_generate_choice_unions(hdr_environment* env, autogen_seq* seq);

LOCAL void      hdr_generate_embedded_structure_names(hdr_environment* env, 
                                                      const char* varname1, const char* varname2,
                                                      char** s_name, char** m_name, char** l_name);

LOCAL void      hdr_generate_message(hdr_environment* env, autogen_seq* msg);
LOCAL void      hdr_generate_message_ids(hdr_environment* env, autogen_obj_list* msg_list, const char* heading2);
LOCAL void      hdr_generate_messages(hdr_environment* env, autogen_obj_list* msg_list);

LOCAL void      hdr_generate_structure_items(hdr_environment* env, const autogen_seq* seq, hdr_item** hdr_item_list, autogen_obj_list* obj_list);
LOCAL hdr_item* hdr_generate_structure_item_list(hdr_environment* env, autogen_seq* seq);
LOCAL void      hdr_generate_structure_item_comments(hdr_environment* env, hdr_item* item_list);

LOCAL void      hdr_generate_structure_size(hdr_environment* env, const autogen_seq* seq, const hdr_item* hdr_item_list);

LOCAL void      hdr_generate_submsg_unions(hdr_environment* env);

LOCAL void      hdr_generic_heading(hdr_environment* env, const char* heading, const char* heading2);

LOCAL void      hdr_item_size_add(hdr_environment* env, hdr_item_size** size_list, const char* type_name, const char* agg, unsigned int count);
 
#if (PMD_FILE_FORMAT >= 600)
LOCAL void      hdr_print_defines_value_constants(hdr_environment* env, const char* name, 
                                                  const unsigned long long* min, int min_is_signed,
                                                  const unsigned long long* max, int max_is_signed,
                                                  const autogen_pres *pres);
#else
LOCAL void      hdr_print_defines_value_constants(hdr_environment* env, const char* name, 
                                                  const unsigned int* min, int min_is_signed,
                                                  const unsigned int* max, int max_is_signed,
                                                  const autogen_pres *pres);
#endif
LOCAL void      hdr_print_define_double(hdr_environment* env, const char* name, double value, const char* comment);
#if (PMD_FILE_FORMAT >= 600)
LOCAL void      hdr_print_define_hex(hdr_environment* env, const char* name, unsigned long long value);
LOCAL void      hdr_print_define_hex_with_comment(hdr_environment* env, const char* name, unsigned long long value, const char* comment);
#else
LOCAL void      hdr_print_define_hex(hdr_environment* env, const char* name, unsigned int value);
LOCAL void      hdr_print_define_hex_with_comment(hdr_environment* env, const char* name, unsigned int value, const char* comment);
#endif
LOCAL void      hdr_print_define(hdr_environment* env, const char* name, const char* value, const char* comment);
LOCAL void      hdr_print_bitmap_mask(hdr_environment* env, autogen_obj* tbl, autogen_it* entry_it, unsigned int* mask);


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: output_srvhdr
 
    Purpose: 
        Generates ISI header files for all resources/servers included in autogen
 
    Functional Description:
        Main function for the ISI header file generator
*/
/* --------------------------------------------------------------------------------------------- */
void output_srvhdr(void)
{
    hdr_environment env = { 0 };
    autogen_it res_it = INIT_ITERATOR;

    env.heap_handle = pmd_heap_init_h(80000);

    printf("Generating ISI header files...\n");
    fprintf(g_log, "\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");
    fprintf(g_log, "Generating ISI header files\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");

    /* generate 8 bit versions */
    res_it.typemask        = AUTOGEN_OBJ_RES;
    res_it.subtypemask     = ~RESOURCE_SYMBOLS;
    env.type               = ISIHDR_TYPE_8;
    env.dont_generate_flag = AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_8;

    env.res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
    while (env.res)
    {
        env.isihdr_16_item_byte   = NULL;
        env.filename              = prop_get_string_default((autogen_obj*)env.res, PROPERTY_ISIHDR_FILENAME, "");
        env.include_phonet_header = prop_has((autogen_obj*)env.res, PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER);
        env.phonet_header_layout  = (unsigned int)prop_get_value_default((autogen_obj*)env.res, PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT, 0);

        /* only generate file, if a filename is specified */
        if (env.filename[0])
        {
            hdr_server(&env);
        }

        env.res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
    }

    /* generate 16 bit versions */
    env.type               = ISIHDR_TYPE_16;
    env.dont_generate_flag = AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR_16;

    env.res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
    while (env.res)
    {
        env.isihdr_16_item_byte   = NULL;
        env.filename              = prop_get_string_default((autogen_obj*)env.res, PROPERTY_ISIHDR_FILENAME_16, "");
        env.include_phonet_header = prop_has((autogen_obj*)env.res, PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16);
        env.phonet_header_layout  = (unsigned int)prop_get_value_default((autogen_obj*)env.res, PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT, 0);

        /* only generate file, if a filename is specified */
        if (env.filename[0])
        {
            hdr_server(&env);
        }

        env.res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
    }

    pmd_heap_free_h(env.heap_handle);
}


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

LOCAL void hdr_generate_message(hdr_environment* env, autogen_seq* msg)
{
    hdr_item* item_list = NULL;
    char heading[256];

    /* Determine heading for the structure */
    strcpy(heading, util_get_obj_type_name(&msg->base));
    strcat(heading, ": ");
    strcat(heading, util_get_obj_name(&msg->base));
    heading[0] = (char)toupper(heading[0]);

    /* Print header for the sequence */
    hdr_print_obj_header(env, &msg->base, heading);

    /* Generate choice unions */
    if (prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_CHOICE_UNIONS))
    {
        hdr_generate_choice_unions(env, msg);
    }

    /* Print leading typedef and initialise environment */
    hdr_seq_begin(env);

    /* Generate a list of structure items for the message */
    item_list = hdr_generate_structure_item_list(env, msg);

    /* Update comments */
    hdr_generate_structure_item_comments(env, item_list);

    /* Finally, print all the items */
    hdr_structure_print_items(env, item_list);

    /* Print trailer for typedef */
    hdr_seq_end(env, item_list, msg);

    /* Print object trailer */
    hdr_print_obj_trailer(env, &msg->base);
}

LOCAL void hdr_generate_message_ids(hdr_environment* env, autogen_obj_list* msg_list, const char* heading2)
{
        autogen_obj* msg;
        autogen_it msg_it = INIT_ITERATOR;
        autogen_feature *lastFeatureFlag = NULL;

        msg_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

        /* Generate heading for message ID's */
        msg = autogen_obj_find_in_list(&msg_it, msg_list);
        if (msg)
            {
            autogen_it base_msg_it = INIT_ITERATOR;

            base_msg_it.typemask = AUTOGEN_OBJ_MSG_BASE;

            if (autogen_obj_find_in_list(&base_msg_it, msg_list))
                {
                hdr_generic_heading(env, "Message ID's and Submessage ID's", heading2);
                }
            else
                {
                hdr_generic_heading(env, "Message ID's", heading2);
                }

            /* Generate user comment to the object */
            if (env->res->msg_id_section && env->res->msg_id_section->cmt_list)
                {
                char* comment = hdr_format_comment(0, TRUE, env->res->msg_id_section->cmt_list);
                if (comment && *comment)
                    {
                    fprintf(env->fout, "%s\n", comment);
                    }
                }

            fprintf(env->fout, "\n");

            /* Generate custom comment for the object */
            if (env->res->msg_id_section)
                {
                hdr_before_comment(env, env->res->msg_id_section->cmt_list);
                }

            /* Generate ID definitions */
            while (msg)
                {
                if (!prop_has(msg, PROPERTY_ISIHDR_DONT_GENERATE_ID))
                    {
                    /* If present, print feature flags */
                    print_feature_flag(env, &lastFeatureFlag, msg->feature_flags);

                    hdr_print_const(env, FALSE, msg, NULL);
                    }
                msg = autogen_obj_find_next_in_list(&msg_it);
                }

            /* If we were under feature flag at the end of loop then insert an feature flag end. */
            print_feature_flag(env, &lastFeatureFlag, NULL);

            /* Generate custom comment for the object */
            if (env->res->msg_id_section)
                {
                hdr_after_comment(env, env->res->msg_id_section->cmt_list);
                }
            }

        /* Generate submessage ID's */
            {
            autogen_seq* msg;
            autogen_it msg_it = INIT_ITERATOR;

            msg_it.typemask  = AUTOGEN_OBJ_MSG_BASE;
            msg_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

            /* Find any submessage ID's for the given message */
            msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, msg_list);
            while (msg)
                {
                autogen_obj* submsg;
                autogen_it submsg_it = INIT_ITERATOR;

                submsg_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

                submsg = autogen_obj_find_in_list(&submsg_it, &msg->submsg_list);
                if (submsg)
                    {
                    fprintf(env->fout, "\n/* Submessage ID's for %s */\n", msg->base.name);

                    lastFeatureFlag = NULL;
                    while (submsg)
                        {
                        /* If present, print feature flags */
                        print_feature_flag(env, &lastFeatureFlag, submsg->feature_flags);

                        hdr_print_const(env, FALSE, submsg, NULL);

                        submsg = autogen_obj_find_next_in_list(&submsg_it);
                        }
                    /* If we were under feature flag at the end of loop then insert an feature flag end. */
                    print_feature_flag(env, &lastFeatureFlag, NULL);
                    }
                msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
                }
            }
}

LOCAL void hdr_generate_messages(hdr_environment* env, autogen_obj_list* msg_list)
{
        autogen_seq* msg;
        autogen_it msg_it = INIT_ITERATOR;
        autogen_feature *lastFeatureFlag = NULL;

        msg_it.typemask = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
        msg_it.flagnone = AUTOGEN_OBJ_IS_LEGACY;

        /* Generate each structure */
        msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, msg_list);
        while (msg)
        {
            if (msg->base.type == AUTOGEN_OBJ_MSG_BASE)
            {
                autogen_obj* submsg;
                autogen_it submsg_it = INIT_ITERATOR;

                submsg_it.flagnone = AUTOGEN_OBJ_IS_LEGACY;

                if ((msg->base.flag & AUTOGEN_MSG_BASE_IS_USER_DEFINED) && !(msg->base.flag & env->dont_generate_flag))
                {
                    /* If present, print feature flags */
                    print_feature_flag(env, &lastFeatureFlag, msg->base.feature_flags);

                    hdr_generate_message(env, msg);
                }
                
                submsg = autogen_obj_find_in_list(&submsg_it, &msg->submsg_list);
                while (submsg)
                {
                    if (!(submsg->flag & env->dont_generate_flag))
                    {
                        /* If present, print feature flags */
                        print_feature_flag(env, &lastFeatureFlag, submsg->feature_flags);

                        hdr_generate_message(env, (autogen_seq*)submsg);
                    }

                    submsg = autogen_obj_find_next_in_list(&submsg_it);
                }
                /* If present, print feature flags */
                print_feature_flag(env, &lastFeatureFlag, NULL);
            }
            else if (!(msg->base.flag & env->dont_generate_flag))
            {
                /* If present, print feature flags */
                print_feature_flag(env, &lastFeatureFlag, msg->base.feature_flags);

                hdr_generate_message(env, msg);
            }

            msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
        }
        /* If present, print feature flags */
        print_feature_flag(env, &lastFeatureFlag, NULL);
    }

/* --------------------------------------------------------------------------------------------- */
/*  Name: hdr_server
 
    Purpose: 
        Generates one ISI header file
 
    Functional Description:
        Generates the ISI header file for the server contained in 'res' of
        the hdr_environment env

    Arguments: 
        env - [in] the ISI header output environment
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void hdr_server(hdr_environment* env)
    {
    char* trailer = NULL;
    autogen_ver init_res_ver = INIT_VERSION_ALL;

    memcpy(&env->res_ver, &init_res_ver, sizeof(env->res_ver));

    env->fout = hdr_open_file(env, &trailer);

    /* clear definition flags */
        {
        autogen_def* def = (autogen_def*)autogen_obj_get_first_in_list(&env->res->def_list);
        while (def)
            {
            def->is_generated = FALSE;

            def = (autogen_def*)def->base.next;
            }
        }

    /* ==================================================================== */
    /* Generate starting definitions */
    /* ==================================================================== */

    /* Generate private definitions */
    if (env->res->base.subtype == RESOURCE_ISI_PRIVATE)
        {
        fprintf(env->fout, "#define %-32s 0x%4.4X\n", env->res->base.name, env->res->base.id);
        fprintf(env->fout, "#define %-32s ((%s << 8) | PN_PRIVATE)\n\n", &env->res->base.name[11], env->res->base.name);
        }    
    
    /* Generate version check macro */
    if (env->res->base.subtype == RESOURCE_ISI ||
        env->res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES ||
        env->res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT ||
        env->res->base.subtype == RESOURCE_ISI_MEDIA_CONTROL ||
        env->res->base.subtype == RESOURCE_ISI_PRIVATE ||
        env->res->base.subtype == RESOURCE_ISI_PREFIX ||
        env->res->base.subtype == RESOURCE_ISI_TRACE ||
        env->res->base.subtype == RESOURCE_SHARED ||
        env->res->base.subtype == RESOURCE_ISI_EXTENSION ||
        env->res->base.subtype == RESOURCE_MEDIA_MODULE ||
        env->res->base.subtype == RESOURCE_MEDIA_MODULE_EXTENSION)
        {
        int from_given = FALSE;
        int to_given = FALSE;

        hdr_top_comment(env, env->res->base.cmt_list);

        /* General ISI #include */
        if (!prop_has(&env->res->base, PROPERTY_ISI_VERSIONING_NOT_SUPPORTED))
        {
            fprintf(env->fout, "#include \"isi_conf.h\"\n\n");
        }

        /* Include base file */
        if (prop_has(&env->res->base, PROPERTY_INHERIT_BASE_RESOURCE_DEFINITIONS))
        {
            autogen_res* base_res = util_get_base_res(env->res);
            if (base_res)
            {
                fprintf(env->fout, "#include \"%s\"\n\n", prop_get_string(&base_res->base, PROPERTY_ISIHDR_FILENAME));
            }
        }

        if (!prop_has(&env->res->base, PROPERTY_ISI_VERSIONING_NOT_SUPPORTED))
            {
            /* Definition of current server version */
            fprintf(env->fout, "#ifndef %s_ISI_VERSION\n",
                    env->res->resnameshort_u);
            fprintf(env->fout, "#define %s_ISI_VERSION\n",
                    env->res->resnameshort_u);
            fprintf(env->fout, "#define %s_ISI_VERSION_Z %3hu\n",
                    env->res->resnameshort_u, env->res->base.ver.from[0]);
            fprintf(env->fout, "#define %s_ISI_VERSION_Y %3hu\n",
                    env->res->resnameshort_u, env->res->base.ver.from[1]);
            fprintf(env->fout, "#endif\n\n");

            /* Definition of backward compatibility macro */
            fprintf(env->fout, "#define %s_ISI_MIN_VERSION(z,y) \\\n",
                    env->res->resnameshort_u);
            fprintf(env->fout, " ((%s_ISI_VERSION_Z == (z) && "
                            "%s_ISI_VERSION_Y >= (y)) || \\\n",
                    env->res->resnameshort_u, env->res->resnameshort_u);
            fprintf(env->fout, "  (%s_ISI_VERSION_Z > (z)))\n\n",
                    env->res->resnameshort_u);

            /* Check of overridden server version */
            if (env->res_ver.type & AUTOGEN_OBJ_VERSION_FROM)
                {
                from_given = TRUE;
                }
            if (env->res_ver.type & AUTOGEN_OBJ_VERSION_TO)
                {
                to_given = TRUE;
                }
            if (from_given)
                {
                fprintf(env->fout, "#if ");

                hdr_print_min_version(env, env->res_ver.from, TRUE);

                fprintf(env->fout, "\n");

                fprintf(env->fout, "#error The specified interface version "
                                "is not supported by this header file\n");
                if (to_given)
                    {
                    fprintf(env->fout, "#elif ");
                    }
                else
                    {
                    fprintf(env->fout, "#endif\n\n");
                    }
                }
            if (to_given)
                {
                if (!from_given)
                    {
                    fprintf(env->fout, "#if ");
                    }

                hdr_print_min_version(env, env->res_ver.to, FALSE);

                fprintf(env->fout, "\n");
                fprintf(env->fout, "#error The specified interface version "
                                "is not supported by this header file\n");
                fprintf(env->fout, "#endif\n\n");
                }

            /* generate check for no longer supported versions */
                {
                autogen_it ver_it = INIT_ITERATOR;
                autogen_obj* ver;

                ver_it.flagcrit  = AUTOGEN_OBJ_FLAG_ALL;
                ver_it.flagmask  = AUTOGEN_VERSION_NO_LONGER_SUPPORTED;
                ver_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_VERSION;

                ver = autogen_obj_find_in_list(&ver_it, &env->res->ver_list);
                if (ver)
                    {
                    fprintf(env->fout, "#if (");

                    while (ver)
                        {
                        autogen_obj* ver_next;
                    
                        fprintf(env->fout, "(%s_ISI_VERSION_Z == %3hu && %s_ISI_VERSION_Y == %3hu)",
                                env->res->resnameshort_u, ver->ver.from[0], env->res->resnameshort_u, ver->ver.from[1]);

                        /* Only print a comma if this is not the last version */
                        ver_next = autogen_obj_find_next_in_list(&ver_it);
                        if (ver_next)
                            {
                            fprintf(env->fout, " || \\\n     ");
                            }
                        else
                            {
                            fprintf(env->fout, ")\n");
                            fprintf(env->fout, "#error The specified interface version is no longer supported\n");
                            fprintf(env->fout, "#endif\n\n");
                            }

                        ver = ver_next;
                        }
                    }
                }
            }

        /* generate check for not yet supported versions */
            {
            autogen_it ver_it = INIT_ITERATOR;
            autogen_obj* ver;

            ver_it.flagcrit = AUTOGEN_OBJ_FLAG_ALL;
            ver_it.flagmask = AUTOGEN_VERSION_NOT_YET_SUPPORTED;

            ver = autogen_obj_find_in_list(&ver_it, &env->res->ver_list);
            if (ver)
                {
                fprintf(env->fout, "#if (");

                while (ver)
                    {
                    autogen_obj* ver_next;

                    fprintf(env->fout, "(%s_ISI_VERSION_Z == %3hu && %s_ISI_VERSION_Y == %3hu)",
                            env->res->resnameshort_u, ver->ver.from[0], env->res->resnameshort_u, ver->ver.from[1]);

                    /* Only print a comma if this is not the last version */
                    ver_next = autogen_obj_find_next_in_list(&ver_it);
                    if (ver_next)
                        {
                        fprintf(env->fout, " || \\\n     ");
                        }
                    else
                        {
                        fprintf(env->fout, ")\n");
                        fprintf(env->fout, "#error The specified interface version is not yet supported\n");
                        fprintf(env->fout, "#endif\n\n");
                        }

                    ver = ver_next;
                    }
                }
            }
        }

    /* Generate custom definitions for the resource */
    hdr_before_comment(env, env->res->base.cmt_list);

    if ((env->res->base.subtype & RESOURCE_ISI_ANY) && env->res->base.subtype != RESOURCE_ISI_EXTENSION)
        {
        /* Definition of PhoNet type */
        if (env->include_phonet_header && 
            env->type == ISIHDR_TYPE_8 && 
            prop_has_valid_string((autogen_obj*)env->res, PROPERTY_ISIHDR_DEFINITION_NAME))
            {
            fprintf(env->fout, "/* Definition of PhoNet type */\n");
            fprintf(env->fout, "typedef uint8 %s;\n\n", 
                prop_get_string((autogen_obj*)env->res, PROPERTY_ISIHDR_DEFINITION_NAME));
            }
        }

    /* ==================================================================== */
    /* Generate constants outside tables */
    /* ==================================================================== */
        {
        autogen_obj* cons;
        autogen_it cons_it = INIT_ITERATOR;
        autogen_feature *lastFeatureFlag = NULL;

        cons_it.typemask = AUTOGEN_OBJ_CONST;
        cons_it.flagnone = AUTOGEN_OBJ_IS_SHARED | env->dont_generate_flag | AUTOGEN_OBJ_IS_LEGACY;

        cons = autogen_obj_find_in_list(&cons_it, &env->res->const_list);
        if (cons)
            {
            hdr_generic_heading(env, "Constants", "");

            fprintf(env->fout, "\n");

            while (cons)
                {
                /* If present, print feature flags */
                print_feature_flag(env, &lastFeatureFlag, cons->feature_flags);

                /* Print the constant */
                hdr_print_const(env, FALSE, cons, NULL);

                cons = autogen_obj_find_next_in_list(&cons_it);
                }

                /* If we were under feature flag at the end of loop then insert an feature flag end. */
                print_feature_flag(env, &lastFeatureFlag, NULL);
             }
        }

    /* ==================================================================== */
    /* Generate constant and bit tables */
    /* ==================================================================== */
        {
        autogen_obj* tbl;
        autogen_it tbl_it = INIT_ITERATOR;
        autogen_feature *lastFeatureFlag = NULL;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
        tbl_it.flagnone    = env->dont_generate_flag | AUTOGEN_OBJ_IS_LEGACY;

        tbl = autogen_obj_find_in_list(&tbl_it, &env->res->tbl_list);
        while (tbl)
            {
            autogen_obj* entry;
            autogen_it entry_it = INIT_ITERATOR;

            /* If present, print feature flags */
            print_feature_flag(env, &lastFeatureFlag, tbl->feature_flags);

            entry = autogen_obj_find_in_list(&entry_it, &tbl->child_list);

            /* If there are any items, print a header and iterate though them */
            if (entry)
                {
                /* Generate as enum? 8 bit or 16 bit. If you want both then specify both! */
                    
                int generate_as_enum   = FALSE;
                const char* enum_type_name = NULL;
                autogen_obj* flagged_entry = NULL;

                if (env->type == ISIHDR_TYPE_16)
                    {
                    if (prop_has(tbl, PROPERTY_ISIHDR_GENERATE_AS_ENUM_16))
                        {
                        enum_type_name = prop_get_string(tbl, PROPERTY_ISIHDR_GENERATE_AS_ENUM_16);
                        generate_as_enum = TRUE;
                        }
                    }
                else if (env->type == ISIHDR_TYPE_8)
                    {
                    if (prop_has(tbl, PROPERTY_ISIHDR_GENERATE_AS_ENUM_8))
                        {
                        enum_type_name = prop_get_string(tbl, PROPERTY_ISIHDR_GENERATE_AS_ENUM_8);
                        generate_as_enum = TRUE;
                        }
                    }

                if (generate_as_enum)
                    {
                    char* comment = NULL;
                    autogen_feature *lastFeatureFlagItem = NULL;

                    hdr_print_enum_header(env, (autogen_tbl*)tbl);

                    while (entry)
                        {
                            /* If present, print feature flags */
                            print_feature_flag(env, &lastFeatureFlagItem, entry->feature_flags);

                        if (entry_it.current_index)
                            {
                            fprintf(env->fout, ","); /* finish line */
                            if (comment && *comment) 
                                {
                                fprintf(env->fout, " %s\n", comment); /* add comment to end of line */
                                comment = NULL;
                                }
                            else
                                fprintf(env->fout, "\n"); 
                            }
                        /* if version condition has been set then terminate by #endif <version condition> */
                        if (flagged_entry)
                            {
                            fprintf(env->fout, "#endif /* ");
                            hdr_print_ver_cond(env, &flagged_entry->ver);
                            fprintf(env->fout, " */\n");
                            flagged_entry = NULL;
                            }
                        /* Check version, set #if <version condition> if needed */
                        if (entry->ver.type & AUTOGEN_OBJ_VERSION_TO)
                            {
                            fprintf(env->fout, "#if ");
                            hdr_print_ver_cond(env, &entry->ver);
                            fprintf(env->fout, "\n");
                            flagged_entry = entry;
                            }

                        comment = hdr_format_comment(0, TRUE, entry->cmt_list);

                        if (((autogen_tbl*)tbl)->length <= 8)
                            {
                            fprintf(env->fout, "    %-42s = 0x%02X", entry->name, entry->id);
                            }
                        else if (((autogen_tbl*)tbl)->length == 16)
                            {
                            fprintf(env->fout, "    %-42s = 0x%04X", entry->name, entry->id);
                            }

                        /* No support for enums for 32 bits - no property defined */

                        entry = autogen_obj_find_next_in_list(&entry_it);
                        }

                    /* Add comment to last entry :o( */
                    if (comment && *comment) 
                        fprintf(env->fout, "  %s", comment);
                    /* if version condition has been set then terminate by #endif <version condition> */
                    if (flagged_entry)
                        {
                        fprintf(env->fout, "\n#endif /* ");
                        hdr_print_ver_cond(env, &flagged_entry->ver);
                        fprintf(env->fout, " */");
                        flagged_entry = FALSE;
                        }

                    /* If present, print feature flags */
                    print_feature_flag(env, &lastFeatureFlagItem, NULL);

                    fprintf(env->fout,"\n    } %s;\n", enum_type_name);

                    /* Print trailer and clean up */
                    hdr_print_obj_trailer(env, tbl);
                    }
                else
                    {
                    unsigned int mask_list[MAX_MASKS + 1];
                    autogen_feature *lastFeatureFlagItem = NULL;

                    memset(&mask_list, 0, sizeof(unsigned int)*(MAX_MASKS + 1));

                    hdr_print_table_header(env, (autogen_tbl*)tbl);

                    while (entry)
                        {
                        /* Retrieve the trailing comment for bit tables */
                        const char* trailing_comment = NULL;

                        /* If present, print feature flags */
                        print_feature_flag(env, &lastFeatureFlagItem, entry->feature_flags);

                        if (tbl->subtype == AUTOGEN_TBL_BIT)
                            {
                            trailing_comment = ((autogen_bittbl_entry*)entry)->bit_pattern;
                            }

                        /* Generate bittable masks */
                        if (tbl->subtype == AUTOGEN_TBL_BIT &&
                            ((prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_BITTABLE_MASKS)    && env->type == ISIHDR_TYPE_8) ||
                             (prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_BITTABLE_MASKS_16) && env->type == ISIHDR_TYPE_16)))
                            {
                            hdr_print_bitmap_mask(env, tbl, &entry_it, mask_list);
                            }

                        /* Generate the constant definition */
                        hdr_print_const(env, TRUE, entry, trailing_comment);

                        entry = autogen_obj_find_next_in_list(&entry_it);
                        }

                    /* If we were under feature flag at the end of loop then insert an feature flag end. */
                    print_feature_flag(env, &lastFeatureFlagItem, NULL);

                    /* Print trailer and clean up */
                    hdr_print_obj_trailer(env, tbl);
                    }

                tbl = autogen_obj_find_next_in_list(&tbl_it);
                }
            }
            /* If we were under feature flag at the end of loop then insert an feature flag end. */
            print_feature_flag(env, &lastFeatureFlag, NULL);
        }

    /* ==================================================================== */
    /* Generate R&D Display data ID tables and PPC ID tables */
    /* ==================================================================== */
        {
        autogen_tbl* tbl;
        autogen_it tbl_it = INIT_ITERATOR;
        autogen_feature *lastFeatureFlag = NULL;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_FTD | AUTOGEN_TBL_PPC;
        tbl_it.flagnone    = env->dont_generate_flag | AUTOGEN_OBJ_IS_LEGACY;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &env->res->tbl_list);
        while (tbl)
            {
            autogen_data* entry;
            autogen_it entry_it = INIT_ITERATOR;
            autogen_feature *lastFeatureFlagItem = NULL;

            /* If present, print feature flags */
            print_feature_flag(env, &lastFeatureFlag, tbl->base.feature_flags);

            entry = (autogen_data*)autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);

            /* If there are any items, print a header and iterate though them */
            if (entry)
                {
                hdr_print_table_header(env, tbl);

                while (entry)
                    {
                    autogen_def* def;
                    autogen_it def_it = INIT_ITERATOR;

                    /* Format the type as a trailing comment */
                    char trailing_comment[50] = "";

                    autogen_data* dataitem = entry;

                    /* If present, print feature flags */
                    print_feature_flag(env, &lastFeatureFlagItem, entry->base.feature_flags);

                    def_it.typemask    = AUTOGEN_OBJ_DEF;
                    def_it.subtypemask = AUTOGEN_DEF_CONST;
                    def_it.obj.name    = entry->base.name;
                    def_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                    def_it.ver         = &entry->base.ver;

                    def = (autogen_def*)autogen_obj_find_in_list(&def_it, &env->res->def_list);
                    /* if version of found definition is not the same as for the item,
                       find item of the default version and base the type comment on that */
                    if (def && !autogen_obj_ver_is_exact(&def->base.ver, &dataitem->base.ver))
                        {
                        autogen_it data_it = INIT_ITERATOR;
                        autogen_data* data;

                        data_it.obj.name = entry->base.name;
                        data_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                        data_it.ver      = &env->res->base.ver;

                        data = (autogen_data*)autogen_obj_find_in_list(&data_it, &tbl->base.child_list);
                        if (data)
                            {
                            dataitem = data;
                            }
                        }

                    if (dataitem->base.flag & AUTOGEN_DATA_TABLE)
                        {
                        strcat(trailing_comment, "table of ");
                        strcat(trailing_comment, hdr_ftd_typename_from_length(dataitem->length));
                        strcat(trailing_comment, "s");
                        }
                    else
                        {
                        strcat(trailing_comment, hdr_ftd_typename_from_length(dataitem->length));
                        }

                    trailing_comment[0] = (char)toupper(trailing_comment[0]);

                    /* Generate the definition and find the next item */
                    hdr_print_const(env, FALSE, &entry->base, trailing_comment);

                    entry = (autogen_data*)autogen_obj_find_next_in_list(&entry_it);
                    }

                /* If present, print feature flags */
                print_feature_flag(env, &lastFeatureFlagItem, NULL);

                hdr_print_obj_trailer(env, &tbl->base);
                }

            tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
            }
        /* If we were under feature flag at the end of loop then insert an feature flag end. */
        print_feature_flag(env, &lastFeatureFlag, NULL);
        }

    /* ==================================================================== */
    /* Generate message ID's */
    /* ==================================================================== */
    if (!env->res->msg_id_section || !(env->res->msg_id_section->flag & env->dont_generate_flag))
    {
        if (env->res->msg_list.n_obj > 0 || env->res->msg_dev_dep_req_list.n_obj > 0 || env->res->msg_dev_dep_resp_list.n_obj > 0)
        {
            if (prop_has(&env->res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
            {
                hdr_generate_message_ids(env, &env->res->msg_dev_dep_req_list, " (messages to component)");
                hdr_generate_message_ids(env, &env->res->msg_dev_dep_resp_list, " (messages from component)");
            }
            else
            {
                hdr_generate_message_ids(env, &env->res->msg_list, "");
            }
        }

        /* Generate message ID's (comments) for resource extension */
        if (env->res->base.flag & AUTOGEN_RES_HAS_EXTENSIONS)
            {
            autogen_it ext_res_it = INIT_ITERATOR;
            autogen_res* ext_res;

            /* find extension resources */
            ext_res_it.typemask = AUTOGEN_OBJ_RES;
            ext_res_it.idcrit   = AUTOGEN_OBJ_ID_EXACT;
            ext_res_it.obj.id   = env->res->base.id;

            if (env->res->base.subtype == RESOURCE_PROTOCOL)
                {
                ext_res_it.subtypemask = RESOURCE_PROTOCOL_EXTENSION;
                }
            else if (env->res->base.subtype == RESOURCE_MEDIA_MODULE)
                {
                ext_res_it.subtypemask = RESOURCE_MEDIA_MODULE_EXTENSION;
                }
            else
                {
                ext_res_it.subtypemask = RESOURCE_ISI_EXTENSION;
                }

            ext_res = (autogen_res*)autogen_obj_find_in_list(&ext_res_it, g_res_list);
            while (ext_res)
                {
                autogen_obj* msg;
                autogen_it msg_it = INIT_ITERATOR;

                msg_it.vercrit   = AUTOGEN_OBJ_VERSION_FIRST;
                msg_it.ver       = &ext_res->base.ver;
                msg_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_NAME;

                msg = autogen_obj_find_in_list(&msg_it, &ext_res->msg_list);
                if (msg)
                    {
                    char str_title[256];

                    sprintf(str_title, "Message ID's reserved for %s", ext_res->logical_name);
                    hdr_generic_heading(env, str_title, "");

                    fprintf(env->fout, "\n/*\n");

                    /* Generate ID definitions */
                    while (msg)
                        {
                        if (!prop_has(msg, PROPERTY_ISIHDR_DONT_GENERATE_ID))
                            {
                            fprintf(env->fout, "#define %-40s 0x%2.2X\n", msg->name, msg->id);
                            }

                        msg = autogen_obj_find_next_in_list(&msg_it);
                        }

                    fprintf(env->fout, "*/\n");
                    }

                ext_res = (autogen_res*)autogen_obj_find_next_in_list(&ext_res_it);
                }
            }
        }

    /* ==================================================================== */
    /* Generate trace ID's */
    /* ==================================================================== */
    if (env->res->base.subtype & g_trcgrp_conf[util_get_tracegroup_type(env->res)].trc_res_ids & RESOURCE_TRC_ANY)
        {
        unsigned int trc_type = util_get_tracegroup_type(env->res);
        autogen_it trcgrp_it = INIT_ITERATOR;
        autogen_trcgrp* trcgrp = NULL;
        autogen_feature *lastFeatureFlag = NULL;

        hdr_generic_heading(env, "Trace ID's", "");

        if (g_trcgrp_conf[trc_type].entity_size != 0)
        {
            fprintf(env->fout, "#define %-40s 0x%4.4X\n\n", env->res->base.name, env->res->base.id);
        }

        trcgrp_it.typemask = AUTOGEN_OBJ_TRACEGRP;
        trcgrp_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;

        trcgrp = (autogen_trcgrp*)autogen_obj_find_in_list(&trcgrp_it, env->res->trcgrp_list);
        while (trcgrp)
            {
            if (trcgrp->base.res == env->res)
                {
                autogen_seq* trc = (autogen_seq*)autogen_obj_get_first_in_list(&trcgrp->base.child_list);

                /* If present, print feature flags */
                print_feature_flag(env, &lastFeatureFlag, trcgrp->base.feature_flags);

                fprintf(env->fout, "#define %-40s 0x%4.4X\n", trcgrp->base.name, trcgrp->base.id);

                while (trc)
                    {
                    /* If present, print feature flags */
                    print_feature_flag(env, &lastFeatureFlag, trc->base.feature_flags);

                    fprintf(env->fout, "#define  %-40s 0x%4.4X\n", trc->base.name, trc->base.id);
                    trc = (autogen_seq*)trc->base.next;
                    }

                fprintf(env->fout, "\n");
                }

            trcgrp = (autogen_trcgrp*)autogen_obj_find_next_in_list(&trcgrp_it);
            }
        /* If we were under feature flag at the end of loop then insert an feature flag end. */
        print_feature_flag(env, &lastFeatureFlag, NULL);
        }
    /* ==================================================================== */
    /* Generate subblock ID's */
    /* ==================================================================== */
    if (!env->res->sb_id_section || !(env->res->sb_id_section->flag & env->dont_generate_flag))
        {
        autogen_obj* sb;
        autogen_it sb_it = INIT_ITERATOR;
        autogen_feature *lastFeatureFlag = NULL;

        sb_it.typemask = AUTOGEN_OBJ_SB;
        sb_it.flagnone = AUTOGEN_OBJ_IS_SHARED;

        sb = autogen_obj_find_in_list(&sb_it, &env->res->seq_list);
        if (sb)
            {
            hdr_generic_heading(env, "Subblock ID's", "");

            /* Generate user comment to the object */
            if (env->res->sb_id_section && env->res->sb_id_section->cmt_list)
                {
                char* comment = hdr_format_comment(0, TRUE, env->res->sb_id_section->cmt_list);
                if (comment && *comment)
                    {
                    fprintf(env->fout, "%s\n", comment);
                    }
                }

            fprintf(env->fout, "\n");

            /* If present, print feature flags */
            print_feature_flag(env, &lastFeatureFlag, sb->feature_flags);

            /* Generate custom comment for the object */
            if (env->res->sb_id_section)
                {
                hdr_before_comment(env, env->res->sb_id_section->cmt_list);
                }

            while (sb)
                {
                if (!prop_has(sb, PROPERTY_ISIHDR_DONT_GENERATE_ID))
                    {
                    /* If present, print feature flags */
                    print_feature_flag(env, &lastFeatureFlag, sb->feature_flags);

                    hdr_print_const(env, FALSE, sb, NULL);
                    }

                sb = autogen_obj_find_next_in_list(&sb_it);
                }

            /* Generate custom comment for the object */
            if (env->res->sb_id_section)
                {
                hdr_after_comment(env, env->res->sb_id_section->cmt_list);
                }
            /* If present, print feature flags */
            print_feature_flag(env, &lastFeatureFlag, NULL);
            }
        }

    /* ==================================================================== */
    /* Include shared files */
    /* ==================================================================== */
        {
        int first = TRUE;
        autogen_obj* shared = autogen_obj_get_first_in_list(&env->res->shared_list);
        autogen_feature *lastFeatureFlag = NULL;
        while (shared)
            {
            if (!(shared->flag & env->dont_generate_flag))
                {
                if (first)
                    {            
                    hdr_generic_heading(env, "Shared file inclusion", "");
                    fprintf(env->fout, "\n");
                    first = FALSE;
                    }

                /* If present, print feature flags */
                print_feature_flag(env, &lastFeatureFlag, shared->feature_flags);

                /* Generate custom comment for the object */
                hdr_before_comment(env, shared->cmt_list);

                if (shared->ver.type != AUTOGEN_OBJ_VERSION_ALL)
                    {
                    fprintf(env->fout, "#if ");
                    hdr_print_ver_cond(env, &shared->ver);
                    fprintf(env->fout, "\n");
                    }

                if (env->type == ISIHDR_TYPE_8 && prop_has_valid_string(shared->ptr, PROPERTY_ISIHDR_FILENAME))
                    {
                    fprintf(env->fout, "#include \"%s\"\n", prop_get_string(shared->ptr, PROPERTY_ISIHDR_FILENAME));
                    }
                else if (env->type == ISIHDR_TYPE_16 && prop_has_valid_string(shared->ptr, PROPERTY_ISIHDR_FILENAME_16))
                    {
                    fprintf(env->fout, "#include \"%s\"\n", prop_get_string(shared->ptr, PROPERTY_ISIHDR_FILENAME_16));
                    }

                if (shared->ver.type != AUTOGEN_OBJ_VERSION_ALL)
                    {
                    fprintf(env->fout, "#endif /* ");
                    hdr_print_ver_cond(env, &shared->ver);
                    fprintf(env->fout, " */\n");
                    }

                /* Generate custom comment for the object */
                hdr_after_comment(env, shared->cmt_list);

                if (shared->ver.type != AUTOGEN_OBJ_VERSION_ALL && !first)
                    {
                    fprintf(env->fout, "\n");
                    }
                }

            shared = shared->next;
            }
        /* If present, print feature flags */
        print_feature_flag(env, &lastFeatureFlag, NULL);
        }

    /* ==================================================================== */
    /* Generate sequence structures */
    /* ==================================================================== */
    {
        hdr_item* item_list = NULL;
        autogen_obj* str;
        autogen_it str_it = INIT_ITERATOR;
        autogen_feature *lastFeatureFlag = NULL;

        /* Generate structure from sequences and subblocks */
        str_it.typemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SB_TEMPLATE;
        str_it.flagnone = AUTOGEN_OBJ_IS_SHARED | AUTOGEN_SEQ_IS_NOT_STRUCT | 
                            env->dont_generate_flag | AUTOGEN_OBJ_IS_LEGACY;

        str = autogen_obj_find_in_list(&str_it, &env->res->seq_list);

        /* Generate each structure */
        while (str)
        {
            char heading[256];

            /* Determine heading for the structure */
            strcpy(heading, util_get_obj_type_name(str));
            strcat(heading, ": ");
            strcat(heading, util_get_obj_name(str));
            heading[0] = (char)toupper(heading[0]);

            /* If present, print feature flags */
            print_feature_flag(env, &lastFeatureFlag, str->feature_flags);

            /* Print header for the sequence */
            hdr_print_obj_header(env, str, heading);

            /* Generate choice unions */
            if (prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_CHOICE_UNIONS))
            {
                hdr_generate_choice_unions(env, (autogen_seq*)str);
            }

            /* Print leading typedef and initialise environment */
            hdr_seq_begin(env);

            /* Generate a list of structure items for the message */
            item_list = hdr_generate_structure_item_list(env, (autogen_seq*)str);

            /* Update comments */
            hdr_generate_structure_item_comments(env, item_list);

            /* Finally, print all the items */
            hdr_structure_print_items(env, item_list);

            /* Print trailer for typedef */
            hdr_seq_end(env, item_list, (autogen_seq*)str);

            /* Print object trailer */
            hdr_print_obj_trailer(env, str);

            str = autogen_obj_find_next_in_list(&str_it);
        }
        /* If present, print feature flags */
        print_feature_flag(env, &lastFeatureFlag, NULL);
    }

    /* ==================================================================== */
    /* Generate printf argument structures */
    /* ==================================================================== */
    if (env->res->trcgrp_list)
    {
        autogen_trcgrp* trcgrp = NULL;
        autogen_feature *lastFeatureFlag = NULL;

        autogen_it trcgrp_it = INIT_ITERATOR;
        trcgrp_it.typemask   = AUTOGEN_OBJ_TRACEGRP;
        trcgrp_it.flagnone   = AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR;

        /* Loop through all trace groups on the resource */
        trcgrp = (autogen_trcgrp*)autogen_obj_find_in_list(&trcgrp_it, env->res->trcgrp_list);
        while (trcgrp)
        {
            if (trcgrp->base.res == env->res)
            {
                autogen_seq* trc = (autogen_seq*)autogen_obj_get_first_in_list(&trcgrp->base.child_list);

                /* Loop through all traces in the given trace group */
                while (trc)
                {
                    autogen_item_printf *printf_item = NULL;

                    autogen_it printf_it  = INIT_ITERATOR;
                    printf_it.typemask    = AUTOGEN_OBJ_ITEM;
                    printf_it.subtypemask = AUTOGEN_ITEM_PRINTF;

                    /* Find if a printf is present in the trace */
                    printf_item = (autogen_item_printf *)autogen_obj_find_in_list(&printf_it, &trc->base.child_list);

                    if (printf_item != NULL)
                    {
                        char heading[256];
                        hdr_item* item_list = NULL;
                        autogen_seq *seq = NULL;
                        autogen_obj *str = &printf_item->base.base;

                        /* If present, print feature flags */
                        print_feature_flag(env, &lastFeatureFlag, trcgrp->base.feature_flags);

                        /* Determine heading for the structure */
                        strcpy(heading, util_get_obj_type_name(str));
                        strcat(heading, ": ");
                        strcat(heading, util_get_obj_name(str));
                        heading[0] = (char)toupper(heading[0]);

                        /* Print header for the sequence */
                        hdr_print_obj_header(env, str, heading);

                        /* Print leading typedef and initialise environment */
                        hdr_seq_begin(env);

                        /* Hack: Construct a autogen sequence object from printf item. */
                        /*       autogen_seq required as argument for functions below  */
                        /*       but the autogen sequence specific fields is not used  */
                        /*       by the functions.                                     */
                        seq = (autogen_seq *)pmd_heap_alloc(sizeof(autogen_seq));
                        memset(seq, 0, sizeof(autogen_seq));
                        memcpy(seq, printf_item, sizeof(autogen_obj));

                        /* Generate a list of structure items for the message */
                        hdr_generate_structure_items(env, seq, &item_list, &printf_item->base.base.child_list);

                        /* Update comments */
                        hdr_generate_structure_item_comments(env, item_list);

                        /* Finally, print all the items */
                        hdr_structure_print_items(env, item_list);

                        /* Print trailer for typedef */
                        hdr_seq_end(env, item_list, seq);

                        /* Print object trailer */
                        hdr_print_obj_trailer(env, str);
                    }
                    trc = (autogen_seq*)trc->base.next;
                }
            }
            trcgrp = (autogen_trcgrp*)autogen_obj_find_next_in_list(&trcgrp_it);
        }
        /* If we were under feature flag at the end of loop then insert an feature flag end. */
        print_feature_flag(env, &lastFeatureFlag, NULL);
    }

    /* ==================================================================== */
    /* Generate message structures */
    /* ==================================================================== */
    {
    if (prop_has(&env->res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
        {
        hdr_generate_messages(env, &env->res->msg_dev_dep_req_list);
        hdr_generate_messages(env, &env->res->msg_dev_dep_resp_list);
        }
    else
        {
        hdr_generate_messages(env, &env->res->msg_list);
        }
    }

    /* ==================================================================== */
    /* Generate trace structures */
    /* ==================================================================== */
    if (env->res->trcgrp_list)
    {
        autogen_obj* trcgrp = NULL;
        autogen_it trcgrp_it = INIT_ITERATOR;
        autogen_feature *lastFeatureFlag = NULL;

        trcgrp_it.flagnone = env->dont_generate_flag;

        trcgrp = autogen_obj_find_in_list(&trcgrp_it, env->res->trcgrp_list);
        while (trcgrp)
        {
            autogen_obj* trc = NULL;
            autogen_it trc_it = INIT_ITERATOR;

            trc_it.flagnone = env->dont_generate_flag;

            trc = autogen_obj_find_in_list(&trc_it, &trcgrp->child_list);
            while (trc)
            {
                if (trc->child_list.n_obj > 0)
                {
                    hdr_item* item_list = NULL;
                    char heading[256];

                    /* If present, print feature flags */
                    print_feature_flag(env, &lastFeatureFlag, trcgrp->feature_flags);

                    /* Determine heading for the structure */
                    strcpy(heading, util_get_obj_type_name(trc));
                    strcat(heading, ": ");
                    strcat(heading, util_get_obj_name(trc));
                    heading[0] = (char)toupper(heading[0]);

                    /* Print header for the sequence */
                    hdr_print_obj_header(env, trc, heading);

                    /* Print leading typedef and initialise environment */
                    hdr_seq_begin(env);

                    /* Generate a list of structure items for the message */
                    item_list = hdr_generate_structure_item_list(env, (autogen_seq*)trc);

                    /* Update comments */
                    hdr_generate_structure_item_comments(env, item_list);

                    /* Finally, print all the items */
                    hdr_structure_print_items(env, item_list);

                    /* Print trailer for typedef */
                    hdr_seq_end(env, item_list, (autogen_seq*)trc);

                    /* Print object trailer */
                    hdr_print_obj_trailer(env, trc);
                }

                trc = autogen_obj_find_next_in_list(&trc_it);
            }
            /* If present, print feature flags */
            print_feature_flag(env, &lastFeatureFlag, NULL);

            trcgrp = autogen_obj_find_next_in_list(&trcgrp_it);
        }
    }

    /* ==================================================================== */
    /* Generate submessage unions */
    /* ==================================================================== */
    if (env->type == ISIHDR_TYPE_16 && 
        prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_SUBMSG_UNIONS_16))
        {
        hdr_generate_submsg_unions(env);
        }

    /* ==================================================================== */
    /* Generate custom definitions for the resource */
    /* ==================================================================== */
    fprintf(env->fout, "\n");

    hdr_after_comment(env, env->res->base.cmt_list);

    fprintf(env->fout, "\n");

    /* ==================================================================== */
    /* Generate notes - unless we are doing output for 3rd parties */
    /* ==================================================================== */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
        {
        autogen_obj* note = autogen_obj_get_first_in_list(&env->res->note_list);
        if (note)
            {
            unsigned int max_note_len = 0;
            unsigned int note_coloumn_width = 30;
            hdr_generic_heading(env, "Notes", "");
            fprintf(env->fout, "/*");

            /* Find out how much space to reserve for note ID's */
            while (note)
                {
                if (strlen(note->name) > max_note_len)
                    {
                    max_note_len = strlen(note->name);
                    }

                note = note->next;
                }
            if (max_note_len < note_coloumn_width)
                {
                note_coloumn_width = max_note_len;
                }

            /* Format the notes and print them */
            note = autogen_obj_get_first_in_list(&env->res->note_list);
            while (note)
                {
                const unsigned int indent = note_coloumn_width + 5;

                char* comment = hdr_format_comment(indent, FALSE, note->cmt_list);
                if (comment && *comment)
                    {
                    fprintf(env->fout, "\n   %-*s  %s\n", note_coloumn_width, note->name, comment + indent);
                    }

                note = note->next;
                }

            fprintf(env->fout, "*/\n\n");
            }
        }

    /* Generate trailer created by hdr_open_file */
    if (trailer)
        {
        fprintf(env->fout, "%s", trailer);
        }

    fclose(env->fout);
    }

/*  This function outputs a constant definition #define ... with the name
    'constname' and the value 'value'.
    If the constant is already marked as generated in the given definition list,
    the definition is placed only as a comment. If print_dup is FALSE, it is not
    printed as a comment.
    Once defined, the constant is marked as generated in the given definition list.
*/
LOCAL void hdr_print_const(hdr_environment* env,
                           int print_dup,
                           const autogen_obj* orig_constant,
                           const char* trailing_comment)
{
    autogen_it def_it = INIT_ITERATOR;
    autogen_def *def = 0;
    autogen_obj constant = *orig_constant;

    if (util_is_predefined_constant(orig_constant->name))
        {
        return;
        }

    /* Hack the structure in case of message, submessage and subblock ID's */
    if (constant.type == AUTOGEN_OBJ_MSG || constant.type == AUTOGEN_OBJ_MSG_BASE)
        {
        /* Don't provide comments for message and submessage ID's */
        constant.cmt_list = NULL;

        constant.name = orig_constant->name;
        constant.id   = orig_constant->id;
        }
    else 
    if (constant.type == AUTOGEN_OBJ_SB)
        {
        /* Don't provide comments for subblock ID's */
        constant.cmt_list = NULL;
        }

    /* We want to find all definitions of the given constant that are valid
       for version intervals within the version of the constant. */
    def_it.typemask    = AUTOGEN_OBJ_DEF;
    def_it.subtypemask = AUTOGEN_DEF_CONST;
    def_it.obj.name    = constant.name;
    def_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
    def_it.ver         = &constant.ver;
    if (constant.feature_flags)
    {
        def_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
        def_it.obj.feature_flags = constant.feature_flags;
    }

    def = (autogen_def*)autogen_obj_find_in_list(&def_it, &env->res->def_list);
    while (def)
        {
        char value[22];
        int add_flags = FALSE;
        autogen_it check_it = INIT_ITERATOR;

        /* find any definitions with the same name, but with versions not included
           in this version */
        check_it.typemask = AUTOGEN_OBJ_DEF;
        check_it.obj.name = constant.name;
        check_it.idcrit   = AUTOGEN_OBJ_ID_NOT;
        check_it.obj.id   = constant.id;
        check_it.vercrit  = AUTOGEN_OBJ_VERSION_INCLUDES_NOT;
        check_it.ver      = &constant.ver;
        if (constant.feature_flags)
        {
            check_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
            check_it.obj.feature_flags = constant.feature_flags;
        }

        /* if such definition exist, flag the definition */
        if ((autogen_obj_find_in_list(&check_it, &env->res->def_list)) ||
            ((constant.type == AUTOGEN_OBJ_CONST) && (!(constant.subtype == AUTOGEN_CONST_AUTOGENERATED)) && (constant.ver.to[0]<256) && (def->base.ver.type != AUTOGEN_OBJ_VERSION_ALL)) ||
            (((constant.type == AUTOGEN_OBJ_TBLENTRY) || (constant.type == AUTOGEN_OBJ_DATA)) && (constant.ver.to[0]<256)))
            {
            add_flags = TRUE; /* versioned constants */
            }
        /* else, all constants of this type are duplicates. 
           Set is_generated on all of these, but the current
        */
        else
            {
            autogen_def* similar_def = NULL;
            autogen_it similar_it = INIT_ITERATOR;

            similar_it.typemask = AUTOGEN_OBJ_DEF;
            similar_it.obj.name = constant.name;
            similar_it.idcrit   = AUTOGEN_OBJ_ID_EXACT;
            similar_it.obj.id   = constant.id;
            similar_it.vercrit  = AUTOGEN_OBJ_VERSION_ANY;
            if (constant.feature_flags)
            {
                similar_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
                similar_it.obj.feature_flags = constant.feature_flags;
            }

            similar_def = (autogen_def*)autogen_obj_find_in_list(&similar_it, &env->res->def_list);
            while (similar_def)
                {
                if (similar_def != def)
                    {
                    similar_def->is_generated = TRUE;
                    }

                similar_def = (autogen_def*)autogen_obj_find_next_in_list(&similar_it);
                }
            }
        /* if add_flags == FALSE then try to see if the constant is in the constant list
           if it is in the constant list then check to see if it is a versioned constant
           if it is a versioned constant then set add_flags = TRUE
        {
        autogen_const* con  = NULL;
        autogen_it const_it = INIT_ITERATOR;

        const_it.obj.name = constant.name;

        con = (autogen_const*)autogen_obj_find_in_list(&const_it, &env->res->const_list);
        if (con) // In list of constants ENHANCEMENT: Check version of constant 
            add_flags = TRUE; // versioned constants 
        }
        */

        /* Format value */
        if (def->base.flag & AUTOGEN_CONST_SIGNED)
            {
#if (PMD_FILE_FORMAT >= 600)
            if (((signed long long)def->base.id) < 0)
                sprintf(value, "(%lld)", (signed long long) def->base.id); /* brackets added to avoid lint warnings */
            else
                sprintf(value, "%lld", (signed long long) def->base.id);
            }
#else
            if (((int)def->base.id) < 0)
                sprintf(value, "(%d)", (int) def->base.id); /* brackets added to avoid lint warnings */
            else
                sprintf(value, "%d", (int) def->base.id);
            }
#endif
        else
        if (def->base.flag & AUTOGEN_CONST_UNSIGNED_DEC)
            {
            if (def->base.id <= 0xFF)
                sprintf(value, "0x%02X", def->base.id);
            else
            if (def->base.id <= 0xFFFF)
                sprintf(value, "0x%04X", def->base.id);
            else
            if (def->base.id <= 0xFFFFFFFF)
                sprintf(value, "0x%08X", def->base.id);
#if (PMD_FILE_FORMAT >= 600)
            else
                sprintf(value, "0x%016llX", def->base.id);
#endif
            /*sprintf(value, "%u", def->base.id);*/
            }
        else
        if (def->base.flag & AUTOGEN_CONST_UNSIGNED_BYTE)
            {
            sprintf(value, "0x%02X", def->base.id);
            }
        else
        if (def->base.flag & AUTOGEN_CONST_UNSIGNED_WORD)
            {
            sprintf(value, "0x%04X", def->base.id);
            }
        else
        if (def->base.flag & AUTOGEN_CONST_UNSIGNED_DWORD)
            {
            sprintf(value, "0x%08X", def->base.id);
            }
        else
#if (PMD_FILE_FORMAT >= 600)
        if (def->base.flag & AUTOGEN_CONST_UNSIGNED_DDWORD)
            {
            sprintf(value, "0x%016llX", def->base.id);
            }
        else
#endif
            {
            sprintf(value, "%u", def->base.id);

            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in hdr_print_const(). def->base.flag is 0x%8.8X", def->base.flag);
            }

        /* New version of constant table or the like */
        if (constant.type == AUTOGEN_OBJ_TBLENTRY) 
            {
            /* So far we are only interested in CONST tables */
            if ((def->is_generated) && (constant.parent->subtype == AUTOGEN_TBL_CONST))
                {
                /* Is it a const that is being used as entry in a const table? */
                autogen_const* con  = NULL;
                autogen_it const_it = INIT_ITERATOR;

                const_it.obj.name = constant.name;

                con = (autogen_const*)autogen_obj_find_in_list(&const_it, &env->res->const_list);
                if (con) /* In list of constants ENHANCEMENT: Check version of constant */
                    {
                    /* printf("Constant %s was in constant list\n", constant.name); */
                    }
                else
                    {
                    autogen_data* tbl_entry;
                    autogen_it tbl_entry_it = INIT_ITERATOR;
                    autogen_it tbl_it = INIT_ITERATOR;
                    int defined_in_other_tbl = FALSE;
                    int scanning_cur_table   = FALSE;
                    /*
                    Search for tables with names different from current table (constant.parent) up to and including 
                    current table, but not beyond. Sort by ID
                    if not found then we have a simple case of entries in multiple versions of the same table - the only table defined, so set
                        def->is_generated = FALSE
                    else
                        while table
                            find children with name equal to name of current entry (constant.name)
                            if found then set defined in other table flag
                                (FUTURE ENHANCEMENT if needed)check version span of child against version span of current entry
                                if child ver span > current entry version span
                                    GENERATE ERROR: VERSION SPAN OF <CHILD> IN <PARENT TABLE> MOVE TO START OF CONST TABLE DECALARTIONS!
                                else
                                    No problem, keep def->is_generated.
                        table = next table
                    if (NOT defined in other table)
                        set def->is_generated to FALSE
                    */

                    tbl_it.typemask    = AUTOGEN_OBJ_TBL;
                    tbl_it.subtypemask = AUTOGEN_TBL_CONST;
                    tbl_it.flagnone    = env->dont_generate_flag | AUTOGEN_OBJ_IS_LEGACY;

                    tbl_entry = (autogen_data*)autogen_obj_find_in_list(&tbl_entry_it, &env->res->tbl_list);
                    while (tbl_entry)
                        {
                        if (strcmp(constant.parent->name, tbl_entry->base.name)) /* not the same table */
                            {
                            autogen_it entry_it = INIT_ITERATOR;

                            /* If constants are not defined inside table they must belong to a table defined prior to current table */
                            if (scanning_cur_table)
                                {
                                break; /* we are beyond current table and versions thereof */
                                }

                            entry_it.obj.name = constant.name;

                            if (autogen_obj_find_in_list(&entry_it, &tbl_entry->base.child_list))
                                {
                                defined_in_other_tbl = TRUE;
                                break;
                                }
                            }
                        else /* same table, but maybe another version */
                            {
                            if ((autogen_ver_comp(constant.parent->ver.from, tbl_entry->base.ver.from)& AUTOGEN_VER_EQUAL) &&
                                (autogen_ver_comp(constant.parent->ver.to, tbl_entry->base.ver.to)& AUTOGEN_VER_EQUAL))
                                scanning_cur_table = TRUE;
                            else /* older version of table */
                                {
                                /* Table has been flagged, do not apply flagging to constant */
                                }
                            }

                        tbl_entry = (autogen_data*)autogen_obj_find_next_in_list(&tbl_entry_it);
                        }

                    if (!defined_in_other_tbl)    
                        {
                        /*def->is_generated = FALSE;  flag was set due to multiple versions of same table */
                    
                        /* checking versioning within current table */
                        if (!(((autogen_ver_comp(def->base.parent->ver.to, def->base.ver.to) & AUTOGEN_VER_NEWER) ||
                            (autogen_ver_comp(def->base.parent->ver.to, def->base.ver.to) & AUTOGEN_VER_EQUAL)) &&
                            ((autogen_ver_comp(def->base.ver.from, constant.parent->ver.from) & AUTOGEN_VER_EQUAL) ||
                            ((autogen_ver_comp(def->base.ver.from, constant.parent->ver.from) & AUTOGEN_VER_NEWER)))))
                            def->is_generated = FALSE;
                        }
                    }

                }
            /* prepare versioning ... */

            }
        /* Generate the definition */
        if (!def->is_generated)
            {
            /* Format the comment string */
            char* comment = hdr_format_comment(0, TRUE, constant.cmt_list);
            int comment_before = FALSE;

            if ((!add_flags) && (!constant.type == AUTOGEN_OBJ_TBLENTRY))
                {
                /* in case the constant has Obsolete_from version other than "" then add flags*/
                if ((constant.ver.to[0] <= 255) && ((constant.ver.to[0] > 0) || (constant.ver.to[1] != 0)))
                    add_flags = TRUE;
                /* in case the constant has Valid_from version other than "" then add flags*/
                if ((constant.ver.from[0] != 0) || (constant.ver.from[1] != 0))
                    add_flags = TRUE;
                }

            /* add flags */
            if (add_flags)
                {
                if ((autogen_ver_comp(constant.ver.from, constant.parent->ver.from) & AUTOGEN_VER_EQUAL) &&
                    (autogen_ver_comp(constant.ver.to, constant.parent->ver.to) & AUTOGEN_VER_EQUAL))
                    {
                    /* Version flags added to parent object */
                    add_flags = FALSE;
                    }
                else
                    {
                    fprintf(env->fout, "\n#if ");

                    hdr_print_ver_cond(env, &def->base.ver);

                    fprintf(env->fout, "\n");
                    }
                }
            /* Generate custom definitions for the constant */
            hdr_before_comment(env, constant.cmt_list);

            /* If the comment is long, or a trailing comment argument is given,
               the comments is generated before the definition */
            if (trailing_comment ||
                comment && strlen(comment) > (unsigned int) (24 - strlen(value)))
                {
                comment_before = TRUE;
                }
            if (comment && *comment && comment_before)
                {
                fprintf(env->fout, "%s\n", comment);
                }

            /* Generate the definition */
            fprintf(env->fout, "#define %-40s %s", constant.name, value);

            /* If the comment is short, it is generated on the same line */
            if (comment && *comment && !comment_before)
                {
                fprintf(env->fout, "  %s", comment);
                }
            else
            if (trailing_comment)
                {
                fprintf(env->fout, "  /* %s */", trailing_comment);
                }
            fprintf(env->fout, "\n");

            /* Generate alias */
            if (prop_has_valid_string(&constant, PROPERTY_ISIHDR_ALIAS_NAME) &&
                constant.type != AUTOGEN_OBJ_MSG &&
                constant.type != AUTOGEN_OBJ_SB)
                {
                const autogen_prop* alias_prop = prop_find_first(&constant, PROPERTY_ISIHDR_ALIAS_NAME);
                while (alias_prop)
                    {
                    fprintf(env->fout, "#define %-40s %s\n", alias_prop->str, constant.name);

                    alias_prop = prop_find_next(alias_prop);
                    }
                }

            /* Generate custom comment for the constant */
            hdr_after_comment(env, constant.cmt_list);

            /* add flags */
            if (add_flags)
                {
                fprintf(env->fout, "#endif /* ");

                hdr_print_ver_cond(env, &def->base.ver);

                fprintf(env->fout, " */\n\n");
                }
            def->is_generated = TRUE;
            }
        else 
        if (print_dup)
            {
            fprintf(env->fout, "/* #define %-37s %s (already defined) */\n",
                    constant.name, value);
            }

        def = (autogen_def*)autogen_obj_find_next_in_list(&def_it);
        }
    }


/*  Opens an output file and generates header information. In case trailer
    information is needed, it is returned as a heap-allocated string in
    trailer. Otherwise a NULL pointer is returned in trailer.
*/
LOCAL FILE* hdr_open_file(hdr_environment* env, char** trailer)
{
    FILE* f;
    time_t thetime;
    struct tm* today;
    char timebuffer[100];

    /* open file */
    f = fopen(env->filename, "w");
    if (!f)
    {
        printf("\nError: Unable to open header file %s. Aborting...\n", env->filename);
        exit(0);
    }

    time(&thetime);
    today = localtime(&thetime);


    /* print header line */
    fprintf(f, "/*\n");
    fprintf(f, "%-30s", prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_NOKIA_ENTITY, "NOKIA"));
    fprintf(f, " ");
    fprintf(f, "%47s\n", prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_CONFIDENTIALITY, "CONFIDENTIAL"));

    /* print project/site information unless it is to be suppressed */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        fprintf(f, "%s\n", prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_SITE_NAME, ""));
        fprintf(f, "%s\n", prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_NAME, ""));
        fprintf(f, "%s\n\n\n\n", prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_OWNER_NAME, ""));
    }

    /* print document name */
    if (prop_has_valid_string((autogen_obj*)env->res, PROPERTY_ISIHDR_TITLE))
    {
        fprintf(f, "                  %s\n", prop_get_string((autogen_obj*)env->res, PROPERTY_ISIHDR_TITLE));
    }
    else
    {
        fprintf(f, "                  %s\n", env->filename);
    }
    fprintf(f, "                  --------------------------------\n");
    fprintf(f, "                  SW Include Document - ANSI C/C++\n\n\n\n");

    /* print Continuus information */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        fprintf(f, "Continuus Ref:\n");
        fprintf(f, "--------------\n");
        fprintf(f, "database:        %s\n\n", 
            prop_get_string_default((autogen_obj*)env->res, PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB, "-"));
        if (env->type == ISIHDR_TYPE_8)
        {
            fprintf(f, "project path:    %s\n\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH, "-"));
        }
        else
        {
            fprintf(f, "project path:    %s\n\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16, "-"));
        }
    }
    /* always include name, version, and type */
    fprintf(f, "name:            %s\n\n", env->filename);
    fprintf(f, "version:         %s\n\n", hdr_format_ver(&env->res->base.ver));
    fprintf(f, "type:            incl\n\n");
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        if (env->type == ISIHDR_TYPE_8)
        {
            fprintf(f, "instance:        %s\n\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME, "-"));
        }
        else
        {
            fprintf(f, "instance:        %s\n\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, "-"));
        }
    }

    fprintf(f, "\n");

    if (env->res->base.subtype == RESOURCE_ISI_PRIVATE)
    {
        fprintf(f, "ISI header file for %s (private interface\n\n", env->res->logical_name);
    }
    else if (env->res->base.subtype & RESOURCE_ISI_ANY)
    {
        fprintf(f, "ISI header file for %s\n\n", env->res->logical_name);
    }
    else
    {
        fprintf(f, "Header file for %s\n\n", env->res->logical_name);
    }

    if (env->res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES && 
        env->res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES_EXT &&
        !prop_has(&env->res->base, PROPERTY_ISI_VERSIONING_NOT_SUPPORTED))

    {
        /* Print current version of the resource */
        if (env->res->base.subtype & RESOURCE_ISI_ANY)
        {
            fprintf(f, "Current   ISI Version : %s\n", hdr_format_ver(&env->res->base.ver));
        }
        else
        {
            fprintf(f, "Current   version : %s\n", hdr_format_ver(&env->res->base.ver));
        }

        /* Print list of supported versions of the resource */
        {
            autogen_obj* ver;
            autogen_it ver_it = INIT_ITERATOR;

            int versions_per_line = 6;
            int versions_on_line  = 0;

            if (env->res->base.subtype & RESOURCE_ISI_ANY)
            {
                fprintf(f, "Supported ISI Versions: ");
            }
            else
            {
                fprintf(f, "Supported versions: ");
            }

            ver_it.flagnone  = AUTOGEN_VERSION_NOT_YET_SUPPORTED | AUTOGEN_VERSION_NO_LONGER_SUPPORTED | AUTOGEN_OBJ_IS_LEGACY;
            ver_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_VERSION;

            ver = autogen_obj_find_in_list(&ver_it, &env->res->ver_list);
            while (ver)
            {
                autogen_obj* ver_next;

                if (versions_on_line == versions_per_line)
                {
                    if (env->res->base.subtype & RESOURCE_ISI_ANY)
                    {
                        fprintf(f, "\n                        ");
                    }
                    else
                    {
                        fprintf(f, "\n                    ");
                    }

                    versions_on_line = 0;
                }

                ++versions_on_line;

                /* Only print a comma if this is not the last version */
                ver_next = autogen_obj_find_next_in_list(&ver_it);
                if (ver_next)
                {
                    fprintf(f, "%s, ", hdr_format_ver(&ver->ver));
                }
                else
                {
                    fprintf(f, "%s", hdr_format_ver(&ver->ver));
                }

                ver = ver_next;
            }
        }
    }

    fprintf(f, "\n\n");

    /* suppress references to autogen when generating output to 3rd party */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        strftime(timebuffer, sizeof(timebuffer)-1, "%d-%b-%Y %H:%M:%S", today);
        fprintf(f, "Generated with autogen version %s on %s\n", AUTOGEN_VERSION_NUMBER, timebuffer);
        fprintf(f, "DO NOT EDIT - changes will be lost at next autogeneration\n\n");
    }
    if (prop_has((autogen_obj*)env->res, PROPERTY_COPYRIGHT_YEAR))
    {
        fprintf(f, "Copyright (c) %s Nokia Corporation. All rights reserved.\n\n\n", prop_get_string((autogen_obj*)env->res, PROPERTY_COPYRIGHT_YEAR));
    }
    else
    {
        fprintf(f, "Copyright (c) Nokia Corporation. All rights reserved.\n\n\n");
    }

    /* Generate version history unless it is to be suppressed */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        int first = TRUE;
        autogen_obj* ver;
        autogen_it ver_it = INIT_ITERATOR;

        /* Set minimum version based on PROPERTY_ISI_VERSION_AUTO_GENERATE */
        unsigned short auto_ver_from[3] = { 0, 0, 0 };
        const char*    auto_ver_str = prop_get_string_default(&env->res->base, PROPERTY_ISI_VERSION_AUTO_GENERATE, "000.000");

        auto_ver_from[0] = (unsigned short)atoi(&auto_ver_str[0]);
        auto_ver_from[1] = (unsigned short)atoi(&auto_ver_str[4]);

        ver_it.flagnone  = AUTOGEN_OBJ_IS_LEGACY;
        ver_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_VERSION_REVERSED;

        ver = autogen_obj_find_in_list(&ver_it, &env->res->ver_list);
        while (ver)
        {
            int print_descr_lead = TRUE;

            /* Format comment */
            static const unsigned int comment_indent = 14;
            if (ver->flag & AUTOGEN_OBJ_IS_LEGACY)
            {
                ver = autogen_obj_find_next_in_list(&ver_it);
                continue;
            }

            /* Print header before the first element with a comment */
            if (first)
            {
                if ((env->res->base.subtype & RESOURCE_ISI_ANY) && !prop_has(&env->res->base, PROPERTY_ISI_VERSIONING_NOT_SUPPORTED))
                {
                    fprintf(f, "ISI version change history\n");
                }
                else
                {
                    fprintf(f, "Version change history\n");
                }

                first = FALSE;
            }

            /* Print version information */
            fprintf(f, "\nVersion     : %-10s ", hdr_format_ver(&ver->ver));
            fprintf(f, "%-11s ", prop_get_string_default(ver, PROPERTY_CHANGE_STATUS, ""));
            fprintf(f, "%-14s ", prop_get_string_default(ver, PROPERTY_CHANGE_DATE, ""));
            fprintf(f,           prop_get_string_default(ver, PROPERTY_CHANGE_PERSON, ""));

            /* Print reason */
            if (prop_has_valid_string(ver, PROPERTY_CHANGE_REASON))
            {
                autogen_cmt* cmt = autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, 
                    prop_get_string(ver, PROPERTY_CHANGE_REASON));

                char* reason = hdr_format_comment(comment_indent, FALSE, cmt);

                fprintf(f, "\nReason      : %s", reason ? reason+comment_indent : "-");
            }

            else
            {
                fprintf(f, "\nReason      : -");
            }

            /* Print reference */
            if (prop_has(ver, PROPERTY_CHANGE_REFERENCE))
            {
                char text[1024] = "";
                autogen_cmt* cmt;
                char* reference;
                const autogen_prop* prop = prop_find_first(ver, PROPERTY_CHANGE_REFERENCE);
                while (prop)
                {                    
                    if (text[0] && text[strlen(text)-1] != '\n')
                    {
                        strcat(text, "\n");
                    }

                    strcat(text, prop->str);

                    prop = prop_find_next(prop);
                }

                cmt = autogen_cmt_create(COMMENT_TEXT, 0, NULL, NULL, NULL, pmd_heap_strdup_h(env->heap_handle, text));

                reference = hdr_format_comment(comment_indent, FALSE, cmt);

                fprintf(f, "\nReference   : %s", reference && *reference ? reference+comment_indent : "-");
            }
            else
            {
                fprintf(f, "\nReference   : -");
            }

            /* Print description */
            /* auto-generated history */
            if (autogen_ver_comp(auto_ver_from, ver->ver.from) & (AUTOGEN_VER_EQUAL | AUTOGEN_VER_NEWER))
            {
                autogen_obj* changed_elements;
                autogen_it elements_it = INIT_ITERATOR;

                elements_it.typemask = AUTOGEN_OBJ_VERSION_HISTORY;
                elements_it.flagnone = AUTOGEN_OBJ_IS_LEGACY;

                changed_elements = autogen_obj_find_in_list(&elements_it, &ver->child_list);
                while (changed_elements)
                {
                    const char* title = "";
                    const char* where = "in";
                    const char* ch_mark = "";
                    const char* tbl_conversion = "";

                    autogen_obj* temp_obj = changed_elements->ptr;
                    switch (changed_elements->subtype)
                    {
                    case AUTOGEN_VERSION_HISTORY_OBJECT_ADDED:
                        {
                            title = "Added";
                            where = "to";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_DISCONTINUED:
                        {
                            title = "Discontinued";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED:
                    case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_COMPATIBLE:
                        {
                            title = "Changed";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_REINTRODUCED:
                        {
                            title = "Re-introduced";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_FILLER_REPLACED:
                        {
                            title   = "Filler replaced by";
                            ch_mark = "'";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_CONST_TBL_TO_BIT_TBL:
                        {
                            title = "Changed Constant table";
                            tbl_conversion = "to Bitmask table";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_BIT_TBL_TO_CONST_TBL:
                        {
                            title = "Changed Bitmask table";
                            tbl_conversion = "to Constant table";
                        }
                        break;
                    }

                    /* No output for derived tables, as these are not shown in ISI header anyway */
                    if (temp_obj->type == AUTOGEN_OBJ_TBLENTRY && (temp_obj->parent->subtype & AUTOGEN_TBL_DER_ANY) ||
                        temp_obj->type == AUTOGEN_OBJ_TBL      && (temp_obj->subtype & AUTOGEN_TBL_DER_ANY))
                    {
                        title = "";
                    }

                    /* Only generate for above listed types */
                    if (title[0])
                    {
                        fprintf(f,"\n%s", print_descr_lead ? "Description : " : util_get_spaces(comment_indent));

                        if (tbl_conversion[0])
                        {
                            fprintf(f, "%s %s %s", title, util_get_obj_name(temp_obj), tbl_conversion);
                        }
                        else if ((temp_obj->type == AUTOGEN_OBJ_TBLENTRY) || 
                            (temp_obj->type == AUTOGEN_OBJ_DATA) || 
                            (temp_obj->type == AUTOGEN_OBJ_ITEM) || 
                            (temp_obj->type == AUTOGEN_OBJ_REF))
                        {
                            fprintf(f, "%s %s %s%s%s %s %s", title, util_get_obj_type_name(temp_obj), ch_mark, util_get_obj_name(temp_obj), ch_mark, where, util_get_obj_name(util_get_base_parent(temp_obj)));
                        }
                        else if (temp_obj->type == AUTOGEN_OBJ_SHARED_FILE)
                        {
                            fprintf(f, "%s %s from %s", title, util_get_obj_type_name(changed_elements->ptr), util_get_obj_name(changed_elements->ptr));
                        }
                        else
                        {
                            fprintf(f, "%s %s %s", title, util_get_obj_type_name(changed_elements->ptr), util_get_obj_name(changed_elements->ptr));
                        }

                        print_descr_lead = FALSE;
                    }

                    changed_elements = autogen_obj_find_next_in_list(&elements_it);
                }
            }

            /* Print description */
            {
                char* comment = hdr_format_comment(comment_indent, FALSE, ver->cmt_list);

                if (print_descr_lead)
                {
                    fprintf(f, "\nDescription : %s", comment && *comment ? comment+comment_indent : "-");
                }
                else if (comment && *comment)
                {
                    fprintf(f, "\n              %s", comment+comment_indent);
                }
                fprintf(f, "\n");
            }

            ver = autogen_obj_find_next_in_list(&ver_it);
        }

        /* Have a look at the first and last version, and clean up */
        if (env->res->ver_list.n_obj > 0)
        {
            /* Note that the list is in reverse order */
            autogen_obj_ver_set(&env->res_ver, 
                env->res->ver_list.map[AUTOGEN_OBJ_LIST_SORT_BY_VERSION][0]->ver.from, 
                env->res->ver_list.map[AUTOGEN_OBJ_LIST_SORT_BY_VERSION_REVERSED][0]->ver.to);

            env->res_ver.to[1]++;
        }
    }

    fprintf(f, "\n------------------------------------------------------------------------------");

    /* Server description */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        char* comment = hdr_format_comment(0, FALSE, env->res->base.cmt_list);
        if (comment && *comment)
        {
            fprintf(f, "\n\nDescription\n\n%s\n", comment);
        }
    }


    fprintf(f, "\n*/\n\n");


    /* printf #ifdef.. statements */
    {
        unsigned int i;
        char* filedef = pmd_heap_strdup_h(env->heap_handle, env->filename);

        for (i = 0; i < strlen(filedef); i++)
        {
            filedef[i] = (char)toupper(filedef[i]);

            if (filedef[i] == '.') 
            {
                filedef[i] = '_';
            }
        }

        fprintf(f, "#ifndef _%s\n", filedef);
        fprintf(f, "#define _%s\n", filedef);
        fprintf(f, "\n");

        *trailer = (char*)pmd_heap_alloc_h(env->heap_handle, 200);
        sprintf(*trailer, "\n#endif /* _%s */\n", filedef);
    }

    return f;
}


/*  Formats human-readable version information. The returned string must
    be freed by the caller.
*/
LOCAL const char* hdr_format_ver(const autogen_ver* ver)
    {
    static char s_ver_str[MAX_VERSION_LENGTH+1] = "";

    if (ver->ver_str)
    {
        strncpy(s_ver_str, ver->ver_str, MAX_VERSION_LENGTH);
    }
    else
    {
        switch (ver->type)
        {
        case AUTOGEN_OBJ_VERSION_NONE:
            {
            sprintf(s_ver_str, "No versions");
            }
            break;

        case AUTOGEN_OBJ_VERSION_FROM:
            {
            sprintf(s_ver_str, "Valid from version %03hu.%03hu", ver->from[0], ver->from[1]);
            }
            break;

        case AUTOGEN_OBJ_VERSION_TO:
            {
            sprintf(s_ver_str, "Obsolete from version %03hu.%03hu", ver->to[0], ver->to[1]);
            }
            break;

        case AUTOGEN_OBJ_VERSION_INTERVAL:
            {
            sprintf(s_ver_str, "Versions %03hu.%03hu - %03hu.%03hu",
                    ver->from[0], ver->from[1], ver->to[0], ver->to[1]);
            }
            break;

        case AUTOGEN_OBJ_VERSION_ALL:
            {
            sprintf(s_ver_str, "All versions");
            }
            break;

        case AUTOGEN_OBJ_VERSION_EXACT:
            {
            sprintf(s_ver_str, "%03hu.%03hu", ver->from[0], ver->from[1]);
            }
            break;

        default:
            {
            s_ver_str[0] = 0;

            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in hdr_format_ver(). ver->type is 0x%8.8X", ver->type);
            }
            break;
        }
    }

    return s_ver_str;
    }


/*  Generates a C preprocessor condition for selecting the given version range.
*/
LOCAL void hdr_print_ver_cond(hdr_environment* env, const autogen_ver* ver)
    {
    switch (ver->type)
        {
        case AUTOGEN_OBJ_VERSION_NONE:
            {
            fprintf(env->fout, "0");
            }
            break;

        case AUTOGEN_OBJ_VERSION_FROM:
            {
            hdr_print_min_version(env, ver->from, FALSE);
            }
            break;

        case AUTOGEN_OBJ_VERSION_TO:
            {
            hdr_print_min_version(env, ver->to, TRUE);
            }
            break;

        case AUTOGEN_OBJ_VERSION_INTERVAL:
            {
            hdr_print_min_version(env, ver->from, FALSE);

            fprintf(env->fout, " && ");

            hdr_print_min_version(env, ver->to, TRUE);
            }
            break;

        case AUTOGEN_OBJ_VERSION_ALL:
            {
            fprintf(env->fout, "1");
            }
            break;

        case AUTOGEN_OBJ_VERSION_EXACT:
            {
            fprintf(env->fout, 
                "%s_ISI_VERSION_Z == %hu && %s_ISI_VERSION_Y == %hu",
                env->res->resnameshort_u, ver->from[0],
                env->res->resnameshort_u, ver->from[1]);
            }
            break;

        default:
            {
            fprintf(env->fout, "0");

            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in hdr_print_ver_cond(). ver->type is 0x%8.8X", ver->type);
            }
            break;
        }
    }


/*  Formats a comment, including comment delimiters, from the given comment
    list. It returns the formmated comment as heap-allocated string that must
    be freed by the caller. In case there's no comment, a NULL pointer is
    returned.
*/
LOCAL char* hdr_format_comment(unsigned int indent, int delimiters, const autogen_cmt* list)
    {
    /* Various formatting calculations */
    char *formatted = NULL;
    char *unformatted = NULL;
    const unsigned int broken_line_len = HDR_LINE_WIDTH - indent 
                                       - (delimiters ? 3 : 0);

    char first_line_prefix[100], subsequent_line_prefix[100], line_suffix[100] = "";
    if (delimiters)
        {
        sprintf(first_line_prefix, "%s/* ", util_get_spaces(indent));
        strcpy(subsequent_line_prefix, util_get_spaces(indent + 3));
        sprintf(line_suffix, "\n%s*/", util_get_spaces(indent));
        }
    else
        {
        strcpy(first_line_prefix, util_get_spaces(indent));
        strcpy(subsequent_line_prefix, first_line_prefix);
        }

    /* Build unformatted text */
    /* If we add a comment type for TSS API, this line must be changed */
    unformatted = util_build_unformatted_comment(list, COMMENT_PROPERTY_ISIHDR_ONLY);
    if (!*unformatted)
        {
        /* Just return the empty string if the comment is empty */
        return "";
        }

    /*  Select single-line or multi-line formatting  */
    if (strlen(unformatted) > broken_line_len-3 || strchr(unformatted, '\n'))
        {
        /* Do word wrapping and add comment symbols */
        formatted = util_wrap_words(unformatted, broken_line_len, first_line_prefix, subsequent_line_prefix, line_suffix);
        }
    else
        {
        /* Perform single-line formatting */
        if (delimiters)
            {
            formatted = util_wrap_words(unformatted, broken_line_len, first_line_prefix, "", " */");
            }
        else
            {
            formatted = util_wrap_words(unformatted, broken_line_len, first_line_prefix, "", "");
            }
        }

    return formatted;
    }

/*  Formats the header for a tables, structures, etc. Use with
    hdr_print_obj_trailer.
*/
LOCAL void hdr_print_obj_header(hdr_environment* env, const autogen_obj* obj, const char* heading)
    {
    int object_flagged = FALSE;
  
    /* Generate object header */
        {
        char* combined_heading_str = (char*)pmd_heap_alloc_h(env->heap_handle, MAX_VERSION_LENGTH + strlen(heading) + 10);

        sprintf(combined_heading_str, "%s", heading);

        if (obj->ver.type != AUTOGEN_OBJ_VERSION_ALL)
            {
            strcat(combined_heading_str, " - ");
            strcat(combined_heading_str, hdr_format_ver(&obj->ver));
            }

        hdr_generic_heading(env, combined_heading_str, "");
        }

    /* Generate user comment to the object */
        {
        char* comment = hdr_format_comment(0, TRUE, obj->cmt_list);
        if (comment && *comment)
            {
            fprintf(env->fout, "%s\n", comment);
            }
        }

    /* Generate leading #if in case of version conflicts */
    if (obj->ver.type != AUTOGEN_OBJ_VERSION_ALL && 
        (prop_has_valid_string(obj, PROPERTY_ISIHDR_DEFINITION_NAME) ||
         prop_has_valid_string(obj, PROPERTY_ISIHDR_STRUCT_NAME)))
        {
        autogen_it def_it = INIT_ITERATOR;

        /* find any definitions with the same name, but with versions not included
           in this version */
        def_it.typemask = AUTOGEN_OBJ_DEF;

        if (prop_has_valid_string(obj, PROPERTY_ISIHDR_STRUCT_NAME))
            {
            def_it.obj.name = prop_get_string(obj, PROPERTY_ISIHDR_STRUCT_NAME);
            }
        else
            {
            def_it.obj.name = prop_get_string(obj, PROPERTY_ISIHDR_DEFINITION_NAME);
            }
        def_it.vercrit  = AUTOGEN_OBJ_VERSION_INCLUDES_NOT;
        def_it.ver      = &obj->ver;

        /* if such definition exist, flag the definition */
        if (autogen_obj_find_in_list(&def_it, &env->res->def_list))
            {
            fprintf(env->fout, "\n#if ");

            hdr_print_ver_cond(env, &obj->ver);

            fprintf(env->fout, "\n");

            object_flagged = TRUE;
            }
        }

    /* Flag object, if it has been discontinued */
    if (!object_flagged)
        {
        if (obj->ver.type & AUTOGEN_OBJ_VERSION_TO)
            {
            fprintf(env->fout, "\n#if ");

            hdr_print_ver_cond(env, &obj->ver);

            fprintf(env->fout, "\n");
            }
        }

    /* Generate custom comment for the object */
    hdr_before_comment(env, obj->cmt_list);
    }


/*  Formats the header for a constant table, bit table, FTD table,
    PPC table, and possibly a few other types of tables as well.
    Use with hdr_print_obj_trailer.
*/
LOCAL void hdr_print_table_header(hdr_environment* env, autogen_tbl* tbl)
    {
    char heading[256];

    /* Check if there are any items in the table at all, and return of not */
    if (tbl->base.child_list.n_obj == 0)
        {
        return;
        }

    /* Generate table name */
    switch (tbl->base.subtype)
        {
        case AUTOGEN_TBL_CONST:
            sprintf(heading, "Constant Table: %s", tbl->base.name);
            break;
        case AUTOGEN_TBL_BIT:
            sprintf(heading, "Bitmask Table: %s", tbl->base.name);
            break;
        case AUTOGEN_TBL_FTD:
            strcpy(heading, "FTD Data Table");
            break;
        case AUTOGEN_TBL_PPC:
            strcpy(heading, "PPC Table");
            break;
        default:
            {
            strcpy(heading, "Unknown table type");

            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in hdr_print_table_header(). tbl->base.subtype is 0x%8.8X", tbl->base.subtype);
            }
            break;
        }

    /* Delegate the bulk of the work */
    hdr_print_obj_header(env, (autogen_obj*)tbl, heading);

    /* if length applies to C built-in type, create typedef for table */
    if (env->type == ISIHDR_TYPE_8 && prop_has_valid_string((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME))
        {
        if (tbl->length == 8 || tbl->length == 16 || tbl->length == 32 || tbl->length == 64)
            {
            fprintf(env->fout, "typedef uint%d %s;\n\n", tbl->length, 
                prop_get_string((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME));
            }
        else
        if (tbl->length == -8 || tbl->length == -16 || tbl->length == -32 || tbl->length == -64)
            {
            fprintf(env->fout, "typedef int%d %s;\n\n", -tbl->length,
                prop_get_string((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME));
            }
        }
    else if (env->type == ISIHDR_TYPE_16 && prop_has_valid_string((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME))
        {
        if (tbl->length == 16)
            {
            fprintf(env->fout, "typedef uint%d %s;\n\n", tbl->length, 
                prop_get_string((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME));
            }
        else if (tbl->length == -16)
            {
            fprintf(env->fout, "typedef int%d %s;\n\n", -tbl->length,
                prop_get_string((autogen_obj*)tbl, PROPERTY_ISIHDR_DEFINITION_NAME));
            }
        }
    }


/*  Formats the header for an enumerated type generated from a 
    constant table.
*/
LOCAL void hdr_print_enum_header(hdr_environment* env, autogen_tbl* tbl)
    {
    char heading[256];

    /* Check if there are any items in the table at all, and return of not */
    if (tbl->base.child_list.n_obj == 0)
        {
        return;
        }

    /* Generate table name */
    switch (tbl->base.subtype)
        {
        case AUTOGEN_TBL_CONST:
            sprintf(heading, "Enumeration based on Constant Table: %s", tbl->base.name);
            break;
        default:
            {
            strcpy(heading, "Unknown table type");

            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in hdr_print_enum_header(). tbl->base.subtype is 0x%8.8X", tbl->base.subtype);
            }
            break;
        }

    /* Delegate the bulk of the work */
    hdr_print_obj_header(env, (autogen_obj*)tbl, heading);

    fprintf(env->fout,"\ntypedef enum\n    {\n");
    }

/* In a loop check if feature flag should be printed. If so then do so */
LOCAL void print_feature_flag(hdr_environment* env, autogen_feature **lastFeatureFlag, autogen_feature *currentFeatureFlag)
{
    /* If last feature flag is the same as the current then do nothing */
    if (*lastFeatureFlag != currentFeatureFlag) 
    {
        /* Check if we still under feature flag */
        if (currentFeatureFlag) 
        {
            /* Still under feature flag */
            /* Check if current feature flag is part of same if-else-end or it is a new one */
            if (!currentFeatureFlag->head) 
            {
                /* This is a new if-else-end */
                if (*lastFeatureFlag)
                {
                    /* Terminate the last feature flag with #endif */
                    hdr_print_feature_flag_end(env);
                }
                hdr_print_feature_flag_begin(env, currentFeatureFlag, FALSE);
            } 
            else
            {
                /* Current feature flag is part of an ongoing if-else-end. */
                if (currentFeatureFlag->head == *lastFeatureFlag)
                {
                    /* Current flag part of same if-else-end as lastFeatureFlag */
                    /* It can just be printed out */
                    hdr_print_feature_flag_begin(env, currentFeatureFlag, FALSE);
                }
                else
                {
                    /* Current flag a new if-else-end sequence */
                    if (*lastFeatureFlag)
                    {
                        /* Terminate the last feature flag with #endif */
                        hdr_print_feature_flag_end(env);
                    }
                    /* We have no #if in front of us. So print this as the negated expression */
                    hdr_print_feature_flag_begin(env, currentFeatureFlag->head, TRUE);
                }
            }
        }
        else 
        {
            /* Not under feature flag any more. Print an #endif */
            hdr_print_feature_flag_end(env);
        }
        *lastFeatureFlag = currentFeatureFlag;
    }
}
/* Print contents of feature flag structure. For debugging only */
LOCAL void debug_print_feature_flag(const hdr_environment* env, const autogen_feature *ff)
{
    fprintf(env->fout, "DEBUG: Feature Flag: %p\n", ff);
    fprintf(env->fout, "  Type : %d\n", ff->flag_logic);
    if (ff->feature1) 
    {
        fprintf(env->fout, "  Flag1: %s : %s\n", ff->feature1->flag, ff->feature1->value);
    }
    if (ff->feature2)
    {
        fprintf(env->fout, "  Flag2: %s : %s\n", ff->feature2->flag, ff->feature2->value);
    }
    fprintf(env->fout, "  Head : %p\n", ff->head);
}

LOCAL void hdr_print_feature_flag_begin(hdr_environment* env, const autogen_feature* feature_flags, int negate)
{
    switch(feature_flags->flag_logic)
    {
    case FT_FLAG:
        {
            fprintf(env->fout, "\n#if %s(%s == %s)\n", (negate ? "!" : ""), 
                                                       feature_flags->feature1->flag, feature_flags->feature1->value);
            break;
        }
    case FT_NOTDEF_FLAG:
        {
            if (negate)
            {
                fprintf(env->fout, "\n#ifdef %s\n",feature_flags->feature1->flag);
            }
            else
            {
                fprintf(env->fout, "\n#ifndef %s\n",feature_flags->feature1->flag);
            }
            break;
        }
    case FT_DEF_FLAG:
        {
            if (negate) 
            {
                fprintf(env->fout, "\n#ifndef %s\n",feature_flags->feature1->flag);
            }
            else
            {
                fprintf(env->fout, "\n#ifdef %s\n",feature_flags->feature1->flag);
            }
            break;
        }
    case FT_FLAG1_AND_FLAG2:
        {
            fprintf(env->fout, "\n#if %s((%s == %s) && (%s == %s))\n",(negate ? "!" : ""), 
                                                                    feature_flags->feature1->flag, feature_flags->feature1->value, 
                                                                    feature_flags->feature2->flag, feature_flags->feature2->value);
            break;
        }
    case FT_FLAG1_OR_FLAG2:
        {
            fprintf(env->fout, "\n#if %s((%s == %s) || (%s == %s))\n", (negate ? "!" : ""), 
                                                                       feature_flags->feature1->flag, feature_flags->feature1->value, 
                                                                       feature_flags->feature2->flag, feature_flags->feature2->value);
            break;
        }
    case FT_ELSE:
        {
            fprintf(env->fout, "\n#else\n");
            break;
        }
    default:
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Invalid FEATURE_FLAG flag_logic value\n");
        }
    }
}

void hdr_print_feature_flag_end(hdr_environment* env)
{
    fprintf(env->fout, "\n#endif\n");
}

/*  Formats the trailer for a tables, structures etc. Use with
    hdr_print_XXX_header.
*/
LOCAL void hdr_print_obj_trailer(hdr_environment* env, autogen_obj* obj)
    {
    int object_flagged = FALSE;
    /* Generate custom comment for the object */
    hdr_after_comment(env, obj->cmt_list);

    /* Generate trailing #endif in case of version conflicts */
    if (obj->ver.type != AUTOGEN_OBJ_VERSION_ALL && 
        (prop_has_valid_string(obj, PROPERTY_ISIHDR_DEFINITION_NAME) ||
         prop_has_valid_string(obj, PROPERTY_ISIHDR_STRUCT_NAME)))
        {
        autogen_it def_it = INIT_ITERATOR;

        /* find any definitions with the same name, but with versions not included
           in this version */
        def_it.typemask = AUTOGEN_OBJ_DEF;
        if (prop_has_valid_string(obj, PROPERTY_ISIHDR_STRUCT_NAME))
            {
            def_it.obj.name = prop_get_string(obj, PROPERTY_ISIHDR_STRUCT_NAME);
            }
        else
            {
            def_it.obj.name = prop_get_string(obj, PROPERTY_ISIHDR_DEFINITION_NAME);
            }
        def_it.vercrit  = AUTOGEN_OBJ_VERSION_INCLUDES_NOT;
        def_it.ver      = &obj->ver;

        /* if such definition exist, flag the definition */
        if (autogen_obj_find_in_list(&def_it, &env->res->def_list))
            {
            fprintf(env->fout, "#endif /* ");

            hdr_print_ver_cond(env, &obj->ver);

            fprintf(env->fout, " */\n\n");
            object_flagged = TRUE;
            }
        }

    if (!object_flagged)
        {
        if (obj->ver.type & AUTOGEN_OBJ_VERSION_TO)
            {
            fprintf(env->fout, "#endif /* ");

            hdr_print_ver_cond(env, &obj->ver);

            fprintf(env->fout, " */\n\n");
            }
        }
    }


/*  Retrieves the name of a type from the length of a type. If the length
    is unknown, this function returns a default text.
*/
LOCAL const char* hdr_typename_from_length(int length)
    {
    switch (length)
        {
        case -64:
#if (PMD_FILE_FORMAT >= 600)
            return "int64";
#else
            return "int32";
#endif
        case -32:
            return "int32";
        case -16:
            return "int16";
        case -8:
            return "int8";
        case 8:
            return "uint8";
        case 16:
            return "uint16";
        case 32:
            return "uint32";
        case 64:
#if (PMD_FILE_FORMAT >= 600)
            return "uint64";
#else
            return "uint32";
#endif
        }

    return "";
    }

/*  Retrieves the name of a type from the length of a type. If the length
    is unknown, this function returns a default text.
*/
LOCAL const char* hdr_ftd_typename_from_length(int length)
    {
    switch (length)
        {
#if (PMD_FILE_FORMAT >= 600)
        case -64:
            return "Signed ddword";
#endif
        case -32:
            return "Signed dword";
        case -16:
            return "Signed word";
        case -8:
            return "Signed byte";
        case 8:
            return "Byte";
        case 16:
            return "Word";
        case 32:
            return "Dword";
#if (PMD_FILE_FORMAT >= 600)
        case 64:
            return "Ddword";
#endif
        }

    return "String";
    }

/*  Prints all COMMENT_ISIHDR_TOP in the given list.
*/
LOCAL void hdr_top_comment(hdr_environment* env, const autogen_cmt* cmt_list)
    {
    while (cmt_list)
        {
        if (env->type == ISIHDR_TYPE_8 && cmt_list->id == COMMENT_ISIHDR_TOP)
            {
            fprintf(env->fout, "%s\n", cmt_list->comment);
            }
        else
        if (env->type == ISIHDR_TYPE_16 && cmt_list->id == COMMENT_ISIHDR_TOP_16)
            {
            fprintf(env->fout, "%s\n", cmt_list->comment);
            }

        cmt_list = cmt_list->next;
        }
    }

/*  Prints all COMMENT_ISIHDR_BEFORE_DEF in the given list.
*/
LOCAL void hdr_before_comment(hdr_environment* env, const autogen_cmt* cmt_list)
    {
    while (cmt_list)
        {
        if (env->type == ISIHDR_TYPE_8 && cmt_list->id == COMMENT_ISIHDR_BEFORE_DEF)
            {
            fprintf(env->fout, "%s\n", cmt_list->comment);
            }
        else
        if (env->type == ISIHDR_TYPE_16 && cmt_list->id == COMMENT_ISIHDR_BEFORE_DEF_16)
            {
            fprintf(env->fout, "%s\n", cmt_list->comment);
            }

        cmt_list = cmt_list->next;
        }
    }


/*  Prints all COMMENT_ISIHDR_AFTER_DEF in the given list.
*/
LOCAL void hdr_after_comment(hdr_environment* env, const autogen_cmt* cmt_list)
    {
    while (cmt_list)
        {
        if (env->type == ISIHDR_TYPE_8 && cmt_list->id == COMMENT_ISIHDR_AFTER_DEF)
            {
            fprintf(env->fout, "%s\n", cmt_list->comment);
            }
        else
        if (env->type == ISIHDR_TYPE_16 && cmt_list->id == COMMENT_ISIHDR_AFTER_DEF_16)
            {
            fprintf(env->fout, "%s\n", cmt_list->comment);
            }

        cmt_list = cmt_list->next;
        }
    }

/*  Generates the starting brace/typedef of a sequence and initialises the
    environment (which is used and modified during sequence generation).
*/
LOCAL void hdr_seq_begin(hdr_environment* env)
    {
    fprintf(env->fout, "\ntypedef struct\n");
    fprintf(env->fout, "    {\n");
    }

/*  Generates the ending brace/typedef name of a sequence and its size
    definition. It uses the environment, which is modified during sequence
    generation.
*/
LOCAL void hdr_seq_end(hdr_environment* env, const hdr_item* item_list, autogen_seq* seq)
    {
    const char* str_name = prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_NAME);

    /* Generate end of structure */
    fprintf(env->fout, "    } %s;\n\n", str_name);

    /* Generate size definition */
    hdr_generate_structure_size(env, seq, item_list);

    /* Define structure alias(es) */
    if (prop_has_valid_string((autogen_obj*)seq, PROPERTY_ISIHDR_ALIAS_NAME))
        {
        const autogen_prop* alias_prop = prop_find_first((autogen_obj*)seq, PROPERTY_ISIHDR_ALIAS_NAME);
        while (alias_prop)
            {
            fprintf(env->fout, "typedef %s %s;\n", str_name, alias_prop->str);

            alias_prop = prop_find_next(alias_prop);
            }

        fprintf(env->fout, "\n");
        }

    /* Dump merge constants belonging to the structure */
    if (env->type == ISIHDR_TYPE_8  && prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_MERGED_MASKS) ||
        env->type == ISIHDR_TYPE_16 && prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_MERGED_MASKS_16))
        {
        hdr_structure_print_merge_constants(env, seq, item_list);
        }

    /* Dump offset constants belonging to the structure */
    if (env->type == ISIHDR_TYPE_8  && prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_STRUCT_BYTE_INDEX) ||
        env->type == ISIHDR_TYPE_16 && prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_STRUCT_BYTE_INDEX_16))
        {
        hdr_structure_print_index_constants(env, seq, item_list);
        }

    /* Dump min/max value constants belonging to the structure */
    if (env->type == ISIHDR_TYPE_8  && prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_MIN_MAX_CONSTANTS) ||
        env->type == ISIHDR_TYPE_16 && prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_MIN_MAX_CONSTANTS_16))
        {
        hdr_structure_print_value_constants(env, seq, item_list);
        }
    }


/*  Generates a generic heading containing the given text
*/
LOCAL void hdr_generic_heading(hdr_environment* env, const char* heading, const char* heading2)
{
    int trailing_spaces = HDR_LINE_WIDTH - 6 - strlen(heading) - strlen(heading2);

    fprintf(env->fout,
        "\n/* --------------------------------------------------"
        "--------------------- */\n");
    fprintf(env->fout, "/* %s %s", heading, heading2);

    while (trailing_spaces-- > 0)
    {
        fprintf(env->fout, " ");
    }

    fprintf(env->fout, "*/\n");
    fprintf(env->fout,
        "/* --------------------------------------------------"
        "--------------------- */\n");
}


/*  Creates a new comment with the given type and string, and appends it
    to the given comment list.
*/
LOCAL void hdr_cmt_append(hdr_environment* env, unsigned int type, const char* text, autogen_cmt** cmt_list)
{
    autogen_cmt* new_comment = autogen_cmt_create(type, 0, NULL, NULL, NULL, pmd_heap_strdup_h(env->heap_handle, text));
    autogen_cmt_add(cmt_list, new_comment);
}


/*  Creates a new comment for the given item referring to a constant table,
    and appends the comment to the given comment list.
*/
LOCAL void hdr_cmt_append_const_tbl(hdr_environment* env, const autogen_item_value* item, autogen_cmt** cmt_list)
{
    char comment[AUTOGEN_MAX_NAME_LENGTH+100] = "";
    const char* tbl_name = item->pres.tblname;

    /* Retrieve name of (original) constant table */
    autogen_it tbl_it = INIT_ITERATOR;
    autogen_tbl* tbl = NULL;
    unsigned int tbl_types = 0;

    tbl_it.typemask = AUTOGEN_OBJ_TBL;
    tbl_it.obj.name = tbl_name;
    tbl_it.ver      = &item->base.base.ver;
    tbl_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;

    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &env->res->tbl_list);
    while (tbl)
    {
        autogen_tbl* parent_tbl = NULL;

        if (autogen_ver_comp(tbl->base.ver.to, env->res->base.ver.to) & AUTOGEN_VER_OLDER)
        {
            parent_tbl = util_get_parent_table(tbl, &env->res->base.ver);
        }
        else
        {
            parent_tbl = util_get_parent_table(tbl, &tbl->base.ver);
        }

        if (parent_tbl)
        {
            tbl_name   = parent_tbl->base.name;
            tbl_types |= parent_tbl->base.subtype;
        }

        tbl_types |= tbl->base.subtype;
        
        tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
    }

    if (tbl_types != 0)
    {
        const char* title = "Values";
        const char* tbl_type_name = "constant table";

        if (tbl_types & AUTOGEN_TBL_DER_ANY)
        {
            title = "A subset of values";
        }
        if ((tbl_types & AUTOGEN_TBL_CONST) && (tbl_types & AUTOGEN_TBL_BIT))
        {
            tbl_type_name = "constant/bitmask table";
        }
        else if (tbl_types & AUTOGEN_TBL_BIT)
        {
            tbl_type_name = "bitmask table";
        }

        sprintf(comment, "%s from the %s %s", title, tbl_type_name, tbl_name);
    }

    hdr_cmt_append(env, COMMENT_PARAGRAPH, comment, cmt_list);
}


/*  Registers the given type name with the given agg count string
    (which may be NULL) for later summing up to the structure size.
*/
LOCAL void hdr_item_size_add(hdr_environment* env, hdr_item_size** size_list, const char* type_name, const char* agg, unsigned int count)
{
    /* Find or create a structure with the right name */
    hdr_item_size* current = NULL;

    if (*size_list)
    {
        current = *size_list;
        while (current->next && strcmp(current->type_name, type_name) != 0)
        {
            current = current->next;
        }

        if (strcmp(current->type_name, type_name) != 0)
        {
            current->next = (hdr_item_size*)pmd_heap_alloc_h(env->heap_handle, sizeof(hdr_item_size));
            current = current->next;

            current->type_name = (char*)pmd_heap_strdup_h(env->heap_handle, type_name);
        }
    }
    else
    {
        current = (hdr_item_size*)pmd_heap_alloc_h(env->heap_handle, sizeof(hdr_item_size));
        current->type_name = (char*)pmd_heap_strdup_h(env->heap_handle, type_name);

        *size_list = current;
    }

    /* Update the structure based on agg type */
    if (agg && agg[0])
    {
        unsigned int n;
        int is_number = TRUE;

        for (n = 0; n < strlen(agg) && is_number; n++)
        {
            if (!isdigit(agg[n]))
            {
                is_number = FALSE;
            }
        }

        if (is_number)
        {
            current->simple_count += (unsigned int)atoi(agg);
        }
        else if (current->aggs)
        {
            char* new_aggs = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(current->aggs) + strlen(agg) + 10);

            sprintf(new_aggs, "%s + %s", current->aggs, agg);

            current->aggs = new_aggs;
        }
        else
        {
            current->aggs = pmd_heap_strdup_h(env->heap_handle, agg);
        }
    }
    else if (count > 0)
    {
        current->simple_count += count;
    }
    else
    {
        current->simple_count++;
    }
}

LOCAL void hdr_print_min_version(hdr_environment* env, const unsigned short* ver, int not)
{
    if (not)
    {
        fprintf(env->fout, "!");
    }

    if (env->type == ISIHDR_TYPE_8)
    {
        fprintf(env->fout, "%s_ISI_MIN_VERSION(%hu,%hu)",
            env->res->resnameshort_u, ver[0], ver[1]);
    }
    else
    {
        fprintf(env->fout, "((%s_ISI_VERSION_Z == %hu && %s_ISI_VERSION_Y >= %hu) || (%s_ISI_VERSION_Z > %hu))",
            env->res->resnameshort_u, ver[0], env->res->resnameshort_u, ver[1], env->res->resnameshort_u, ver[0]);
    }
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL void hdr_print_defines_value_constants(hdr_environment* env, const char* name, 
                                             const unsigned long long* min, int min_is_signed,
                                             const unsigned long long* max, int max_is_signed,
                                             const autogen_pres *pres)
#else
LOCAL void hdr_print_defines_value_constants(hdr_environment* env, const char* name, 
                                             const unsigned int* min, int min_is_signed,
                                             const unsigned int* max, int max_is_signed,
                                             const autogen_pres *pres)
#endif
{
    char print_name[AUTOGEN_MAX_NAME_LENGTH*2+50];

    /* MIN */
    if (min)
    {
        sprintf(print_name, "%s%s", name, "_MIN");
        if (min_is_signed)
        {
            char value[50];
#if (PMD_FILE_FORMAT >= 600)
            sprintf(value, "%lld", (signed long long)*min);
#else
            sprintf(value, "%d", (int)*min);
#endif
            hdr_print_define(env, print_name, value, "");
        }
        else
        {
            hdr_print_define_hex(env, print_name, *min);
        }
    }

    /* MAX */
    if (max)
    {
        sprintf(print_name, "%s%s", name, "_MAX");
        if (max_is_signed)
        {
            char value[50];
#if (PMD_FILE_FORMAT >= 600)
            sprintf(value, "%lld", (signed long long)*max);
#else
            sprintf(value, "%d", (int)*max);
#endif
            hdr_print_define(env, print_name, value, "");
        }
        else
        {
            hdr_print_define_hex(env, print_name, *max);
        }
    }

    /* Presentation */
    if (pres)
    {
        if ((pres->type & AUTOGEN_PRESENTATION_SCALAR) || (pres->type & AUTOGEN_PRESENTATION_OFFSET))
        {
            /* FACTOR */
            {
                sprintf(print_name, "%s%s", name, "_FACTOR");
                hdr_print_define_double(env, print_name, (*pres).scale, "");
            }

            /* ENCODE_FACTOR */
            if ((*pres).scale != 0.0 && (*pres).scale != 1.0 && 1.0/(*pres).scale == (double)((int)(1.0/(*pres).scale)))
            {
                sprintf(print_name, "%s%s", name, "_ENCODE_FACTOR");
                hdr_print_define_double(env, print_name, 1.0/(*pres).scale, "");
            }

            /* OFFSET */
            {
                sprintf(print_name, "%s%s", name, "_VALUE_OFFSET");
                hdr_print_define_double(env, print_name, (*pres).offset, "");
            }        
        }
    }
}

LOCAL void hdr_print_define_double(hdr_environment* env, const char* name, double value, const char* comment)
{
    char string_value[100];
    sprintf(string_value, "%g", value);
    hdr_print_define(env, name, (char*)&string_value, comment);
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL void hdr_print_define_hex(hdr_environment* env, const char* name, unsigned long long value)
#else
LOCAL void hdr_print_define_hex(hdr_environment* env, const char* name, unsigned int value)
#endif
{
    char comment[100];
#if (PMD_FILE_FORMAT >= 600)
    if (prop_has((autogen_obj*)env->res, PROPERTY_ALIGNMENT_64_BITS))
    {
        sprintf(comment, "%llu", value);
    }
    else
#endif
    sprintf(comment, "%8u", value);
    hdr_print_define_hex_with_comment(env, name, value, (char*)&comment);
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL void hdr_print_define_hex_with_comment(hdr_environment* env, const char* name, unsigned long long value, const char* comment)
#else
LOCAL void hdr_print_define_hex_with_comment(hdr_environment* env, const char* name, unsigned int value, const char* comment)
#endif
{
    char string_value[100];
#if (PMD_FILE_FORMAT >= 600)
    if (prop_has((autogen_obj*)env->res, PROPERTY_ALIGNMENT_64_BITS))
    {
        sprintf(string_value, "0x%Xllu", value);
    }
    else
#endif
    sprintf(string_value, "0x%Xu", value);
    hdr_print_define(env, name, (char*)&string_value, comment);
}

LOCAL void hdr_print_define(hdr_environment* env, const char* name, const char* value, const char* comment)
{
    fprintf(env->fout, "#define %-51s ", name);
    fprintf(env->fout, "%13s", value);
    if(comment)
    {
        if(strlen(comment) > 0)
        {
            fprintf(env->fout, "  /* %s */", comment);
        }
    }
    fprintf(env->fout, "\n", comment);
}

LOCAL void hdr_generate_submsg_unions(hdr_environment* env)
{
    autogen_seq* msg;
    autogen_it msg_it = INIT_ITERATOR;
    autogen_feature *lastFeatureFlagM = NULL;
    autogen_feature *lastFeatureFlagSM = NULL;

    msg_it.typemask = AUTOGEN_OBJ_MSG_BASE;

    msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, &env->res->msg_list);
    if (msg)
    {
        hdr_generic_heading(env, "Message unions", "");

        while (msg)
        {
            autogen_obj* submsg = autogen_obj_get_first_in_list(&msg->submsg_list);
            if (submsg)
            {
                /* If present, print feature flags */
                print_feature_flag(env, &lastFeatureFlagM, msg->base.feature_flags);

                fprintf(env->fout, "typedef union\n");
                fprintf(env->fout, "    {\n");

                while (submsg)
                {
                    if (*prop_get_string_default(submsg, PROPERTY_ISIHDR_STRUCT_NAME, "") != 0)
                    {
                        /* If present, print feature flags */
                        print_feature_flag(env, &lastFeatureFlagSM, submsg->feature_flags);

                        fprintf(env->fout, "    %s  u%s;\n",
                            prop_get_string(submsg, PROPERTY_ISIHDR_STRUCT_NAME),
                            submsg->name);
                    }

                    submsg = submsg->next;
                }
                /* If present, print feature flags */
                print_feature_flag(env, &lastFeatureFlagSM, NULL);

                fprintf(env->fout, "    } %s_UNION;\n\n", msg->base.name);
            }

            msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
        }
        /* If present, print feature flags */
        print_feature_flag(env, &lastFeatureFlagM, NULL);
    }
}

LOCAL hdr_item* hdr_structure_item_split(hdr_environment* env, hdr_item* item, const char* varname1, const char* varname2, int length)
{
    hdr_item* item_m = NULL;
    hdr_item* item_l = NULL;
    hdr_item* item_s = NULL;

    hdr_cmt_ensure_newline(env, &item->cmt);

    /* If an array of split items, generate the following 
    
        struct 
            {
            (u)intx var1;
            (u)intx var2;
            } xxx[YYY][ZZZ];
    */
    if (item->flags & HDR_ITEM_ARRAY)
    {
        char* l_name = NULL;
        char* m_name = NULL;
        char* s_name = NULL;

        hdr_generate_embedded_structure_names(env, varname1, varname2, &s_name, &m_name, &l_name);

        item_m = hdr_structure_item_create(env, m_name, NULL, length, NULL, 0);
        item_l = hdr_structure_item_create(env, l_name, NULL, length, NULL, 0);
        item_s = hdr_structure_item_create(env, s_name, NULL, 0, item->cmt, HDR_ITEM_STRUCT);

        item_s->agg_n[0]   = item->agg_n[0];
        item_s->agg_n[1]   = item->agg_n[1];
        item_s->agg_str[0] = item->agg_str[0];
        item_s->agg_str[1] = item->agg_str[1];
        item_s->flags     |= (item->flags & (HDR_ITEM_ARRAY | HDR_ITEM_ARRAY_2 | HDR_ITEM_FIXED_ARRAY));

        item_s->child_list = item_m;
    }
    /* Else just split the item in two items */
    else
    {
        item_m = hdr_structure_item_create(env, varname1, NULL, length, item->cmt, 0);
        item_l = hdr_structure_item_create(env, varname2, NULL, length, NULL, 0);
    }

    item_m->next = item_l;

    /* If merge field is split, update individual fields in each new item */
    if (item->flags & HDR_ITEM_MERGE)
    {
        int offset = 0;
        hdr_item* merge_item = item->child_list;
        hdr_item* dest_item = item_m;

        item->child_list = NULL;

        while (merge_item)
        {
            hdr_item* next_item = merge_item->next;
            merge_item->next = NULL;

            /* If the end of the destination item is met, change destination */
            if (offset == abs(dest_item->type_length))
            {
                dest_item = dest_item->next;
                offset = 0;
            }

            /* There is room for entire item => move it! */
            if (offset + abs(merge_item->type_length) <= abs(dest_item->type_length))
            {
                hdr_structure_item_add(&dest_item->child_list, merge_item);

                offset += abs(merge_item->type_length);
            }
            /* There is room for some of the item. Split the item in two */
            else
            {
                hdr_item* split_item = hdr_structure_item_create(env, merge_item->varname, merge_item->parname, 
                    abs(dest_item->type_length) - offset, merge_item->cmt, HDR_ITEM_MERGE_HI);

                hdr_structure_item_add(&dest_item->child_list, split_item);

                offset += abs(split_item->type_length);

                /* Prepare the 2nd half of the merge item to be appended */
                merge_item->cmt          = NULL;
                merge_item->type_length  = abs(merge_item->type_length) - split_item->type_length;
                merge_item->field_length = merge_item->type_length;
                merge_item->flags       |= HDR_ITEM_MERGE_LO;

                next_item = merge_item;
            }

            merge_item = next_item;
        }

        item_m->flags |= HDR_ITEM_MERGE;
        item_l->flags |= HDR_ITEM_MERGE;
    }

    /* Remove pointer flags */
    item_m->flags &= ~HDR_ITEM_POINTER;
    item_l->flags &= ~HDR_ITEM_POINTER;
    if (item_s)
    {
        item_s->flags &= ~HDR_ITEM_POINTER;
    }

    return (item_s ? item_s : item_m);
}

LOCAL void hdr_structure_item_set_aggregation(hdr_environment* env, hdr_item* item, autogen_item* org_item)
{
    isihdr_marker_type marker = (unsigned int)prop_get_value_default(&org_item->base, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_NONE);

    /* Any size construction */
    if (marker == ISIHDR_MARKER_ANYSIZE ||
        marker == ISIHDR_MARKER_ANYSIZE_BYTE ||
        marker == ISIHDR_MARKER_ANYSIZE_WORD)
    {
        char* agg_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(env->res->resnameshort_u) + 20);
        sprintf(agg_str, "%s_ANY_SIZE", env->res->resnameshort_u);

        item->agg_n[0]   = 1;
        item->agg_str[0] = agg_str;
        item->flags     |= HDR_ITEM_ARRAY | HDR_ITEM_FIXED_ARRAY;
    }
    /* Single item */
    else if (org_item->agg_type == AGG_TYPE_FIXED_SINGLE)
    {
        if (org_item->base.subtype == AUTOGEN_ITEM_STRING)
        {
            item->agg_n[0]   = (int)((const autogen_item_string*)org_item)->length;
            item->agg_str[0] = pmd_heap_strdup_h(env->heap_handle, ((const autogen_item_string*)org_item)->length_str);

            item->flags     |= HDR_ITEM_ARRAY;
        }
    }
    /* Fixed array */
    else if (org_item->agg_type == AGG_TYPE_FIXED_MULTIPLE)
    {
        if (org_item->base.subtype == AUTOGEN_ITEM_STRING)
        {
            item->agg_n[0]   = (int)((const autogen_item_string*)org_item)->length;
            item->agg_str[0] = pmd_heap_strdup_h(env->heap_handle, ((const autogen_item_string*)org_item)->length_str);

            item->agg_n[1]   = org_item->agg_n;
            item->agg_str[1] = pmd_heap_strdup_h(env->heap_handle, org_item->agg_n_str);

            item->flags     |= HDR_ITEM_ARRAY_2;
        }
        else
        {
            item->agg_n[0]   = org_item->agg_n;
            item->agg_str[0] = pmd_heap_strdup_h(env->heap_handle, org_item->agg_n_str);
        }

        item->flags |= HDR_ITEM_ARRAY;
    }
    else if (marker == ISIHDR_RESERVE_SPACE)
    {
        /* Find the reference and print the maximum value, if any */
        if (org_item->agg_type == AGG_TYPE_DYNAMIC_ZEROTERMINATED ||
            org_item->agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE)
        {
            if (prop_has((autogen_obj*)org_item, PROPERTY_STRING_MAXIMUM_LENGTH))
            {
                item->agg_n[0]   = (unsigned int)prop_get_value((autogen_obj*)org_item, PROPERTY_STRING_MAXIMUM_LENGTH);
                item->agg_str[0] = pmd_heap_strdup_h(env->heap_handle, prop_get_string((autogen_obj*)org_item, PROPERTY_STRING_MAXIMUM_LENGTH));
                item->flags     |= HDR_ITEM_ARRAY;
            }
            else if (prop_has((autogen_obj*)org_item, PROPERTY_ARRAY_MAXIMUM_SIZE))
            {
                item->agg_n[0]   = (unsigned int)prop_get_value((autogen_obj*)org_item, PROPERTY_ARRAY_MAXIMUM_SIZE);
                item->agg_str[0] = pmd_heap_strdup_h(env->heap_handle, prop_get_string((autogen_obj*)org_item, PROPERTY_ARRAY_MAXIMUM_SIZE));
                item->flags     |= HDR_ITEM_ARRAY;
            }
        }
        /* If optional, set array count to 1 */
        else if (org_item->agg_type == AGG_TYPE_DYNAMIC_OPTIONAL)
        {
            item->agg_n[0]   = 1;
            item->agg_str[0] = "";
            item->flags     |= HDR_ITEM_ARRAY | HDR_ITEM_FIXED_ARRAY;
        }
        else if (org_item->agg_type == AGG_TYPE_DYNAMIC_REF)
        {
            char min_val_str[2*AUTOGEN_MAX_NAME_LENGTH] = "";
            char max_val_str[2*AUTOGEN_MAX_NAME_LENGTH] = "";

#if (PMD_FILE_FORMAT >= 600)
            signed long long min_val = 0;
            signed long long max_val = 0;
#else
            int min_val = 0;
            int max_val = 0;
#endif

            reference_get_limits(org_item, &min_val, &max_val, min_val_str, max_val_str);

            item->agg_n[0]   = (unsigned int)max_val;
            item->agg_str[0] = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(max_val_str) + 10);
            strcpy(item->agg_str[0], max_val_str);

            if (org_item->base.subtype == AUTOGEN_ITEM_STRING && 
                prop_has(&org_item->base, PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH))
            {
                ++max_val;
                strcat(item->agg_str[0], "+1");
            }

            item->flags     |= HDR_ITEM_ARRAY;
        }
    }

    if (util_is_string_number(item->agg_str[0]))
    {
        item->agg_str[0] = "";
    }
}

LOCAL void hdr_structure_item_set_comment(hdr_environment* env, hdr_item* item, autogen_item* org_item)
    {
    /* Copy the comment from the original item */
    item->cmt = autogen_cmt_copy(org_item->base.cmt_list);

    switch (org_item->base.subtype)
        {
        case AUTOGEN_ITEM_LST:
            {
            /* Ensure that existing comment has new line */
            hdr_cmt_ensure_newline(env, &item->cmt);

            /* Determine whether it's subblocks or IDs */
            if (org_item->base.flag & AUTOGEN_LST_SBID)
                {
                hdr_cmt_append(env, COMMENT_PARAGRAPH, "Subblock ID's:", &item->cmt);
                }
            else
                {
                hdr_cmt_append(env, COMMENT_PARAGRAPH, "Subblock list:", &item->cmt);
                }

            /* Provide list of subblock IDs */
#if ((defined AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN) || (defined AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES))
            if (org_item->base.flag & AUTOGEN_LST_SOS_FTD)
                {
                hdr_cmt_append(env, COMMENT_PARAGRAPH, "SOS_FTD_DATA_*", &item->cmt);
                }
            else 
#endif
            if (org_item->base.flag & AUTOGEN_LST_FTD)
                {
                hdr_cmt_append(env, COMMENT_PARAGRAPH, "COMM_FTD_DATA_*", &item->cmt);
                }
            else if (org_item->base.flag & AUTOGEN_LST_PPC)
                {
                hdr_cmt_append(env, COMMENT_PARAGRAPH, "MON_PPC_*", &item->cmt);
                }
            if (org_item->base.flag & AUTOGEN_LST_SB)
                {
                autogen_obj* ref;
                autogen_it ref_it = INIT_ITERATOR;

                ref_it.typemask    = AUTOGEN_OBJ_REF;
                ref_it.subtypemask = AUTOGEN_OBJ_SB;
                ref_it.vercrit     = AUTOGEN_OBJ_VERSION_FIRST;
                ref_it.sort_type   = AUTOGEN_OBJ_LIST_SORT_BY_NAME;

                ref = autogen_obj_find_in_list(&ref_it, &org_item->base.child_list);
                while (ref)
                    {
                    hdr_cmt_append(env, COMMENT_PARAGRAPH, ref->name, &item->cmt);

                    ref = autogen_obj_find_next_in_list(&ref_it);
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_REF:
        case AUTOGEN_ITEM_VALUE:
            {
            const autogen_item_value* item_val = (const autogen_item_value*)org_item;

            if (item_val->pres.type & AUTOGEN_PRESENTATION_CONST)
                {
                /* Ensure that comment ends on a new line */
                hdr_cmt_ensure_newline(env, &item->cmt);
                if (!prop_has((autogen_obj*)org_item, PROPERTY_ISIHDR_DONT_GENERATE))
                    hdr_cmt_append_const_tbl(env, item_val, &item->cmt);
                }
            }
            break;

        case AUTOGEN_ITEM_BLOCK:
        case AUTOGEN_ITEM_FILLER:
        case AUTOGEN_ITEM_POINTER:
        case AUTOGEN_ITEM_RANGE:
        case AUTOGEN_ITEM_STRING:
        case AUTOGEN_ITEM_STRUCT:
        case AUTOGEN_ITEM_TIMESTAMP:
            {
            }
            break;

        case AUTOGEN_ITEM_MERGE:
            {
            /* Ensure that comment ends on a new line */
            hdr_cmt_ensure_newline(env, &item->cmt);
            }
            break;

        case AUTOGEN_ITEM_PRINTF:
            {
            /* Ensure that existing comment has new line */
            hdr_cmt_ensure_newline(env, &item->cmt);

            /* Add comments containing the printf format string */
            hdr_cmt_append(env, COMMENT_TEXT, "Printf format string: ", &item->cmt);
            hdr_cmt_append(env, COMMENT_PARAGRAPH, ((autogen_item_printf *)org_item)->format, &item->cmt);
            }
            break;

        /* Should never come here... */
        case AUTOGEN_ITEM_CASE:
        case AUTOGEN_ITEM_CHOICE:
        case AUTOGEN_ITEM_RANGE_ENTRY:
        case AUTOGEN_ITEM_TRCSTRUCTURE:
        default:
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in hdr_structure_item_set_comment(). org_item->base.subtype is 0x%8.8X", org_item->base.subtype);
            }
            break;
        }
    }

LOCAL void hdr_structure_item_set_length(hdr_item* item, const autogen_item* org_item)
    {
    switch (org_item->base.subtype)
        {
        case AUTOGEN_ITEM_BLOCK:
        case AUTOGEN_ITEM_FILLER:
        case AUTOGEN_ITEM_MERGE:
        case AUTOGEN_ITEM_POINTER:
        case AUTOGEN_ITEM_RANGE:
        case AUTOGEN_ITEM_REF:
        case AUTOGEN_ITEM_TIMESTAMP:
        case AUTOGEN_ITEM_VALUE:
        case AUTOGEN_ITEM_PRINTF:
            {
            item->type_length = org_item->length;
            }
            break;

        case AUTOGEN_ITEM_LST:
            {
            /* Determine size and whether it's subblocks or IDs */
            if (org_item->base.flag & AUTOGEN_LST_SBID)
                {
                /* Determine the size of the ID's */
                if ((org_item->base.flag & AUTOGEN_LST_SB) &&
                    (org_item->base.flag & AUTOGEN_LST_SB_HAVE_BYTE_IDS))
                    {
                    item->type_length = 8;
                    }
                else
                    {
                    item->type_length = 16;
                    }
                }
            else
                {
                item->type_length = 0;
                }
            }
            break;

        case AUTOGEN_ITEM_STRING:
            {
            if (org_item->base.flag & AUTOGEN_STRING_UNICODE)
                {
                item->type_length = -16;
                }
            else
            if (org_item->base.flag & AUTOGEN_STRING_ASCII)
                {
                item->type_length = -8;
                }
            else
                {
                item->type_length = 8;
                }
            }
            break;

        case AUTOGEN_ITEM_STRUCT:
            {
            item->type_length = 0;
            }
            break;

        /* Should never come here... */
        case AUTOGEN_ITEM_CHOICE:
        case AUTOGEN_ITEM_CASE:
        case AUTOGEN_ITEM_RANGE_ENTRY:
        case AUTOGEN_ITEM_TRCSTRUCTURE:
        default:
            {
            item->type_length = 0;

            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in hdr_structure_item_set_length(). item->base.subtype is 0x%8.8X", org_item->base.subtype);
            }
            break;
        }

    if (item->flags & HDR_ITEM_POINTER)
        {
        item->field_length = 32;
        }
    else
        {
        item->field_length = item->type_length;
        }
    }

LOCAL void hdr_structure_item_set_typename(hdr_environment* env, hdr_item* item, const autogen_item* org_item)
    {
    isihdr_marker_type marker = (unsigned int)prop_get_value_default(&org_item->base, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_NONE);

    if (prop_has_valid_string(&org_item->base, PROPERTY_ISIHDR_DEFINITION_NAME))
        {
        item->type_name = prop_get_string(&org_item->base, PROPERTY_ISIHDR_DEFINITION_NAME);
        }
    else if (marker == ISIHDR_MARKER_SINGLE_ELEMENT_BYTE ||
             marker == ISIHDR_MARKER_ANYSIZE_BYTE)
        {
        item->type_name = "uint8";
        }
    else if (marker == ISIHDR_MARKER_ANYSIZE_WORD)
        {
        item->type_name = "uint16";
        }
    else if (marker == ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        {
        item->type_name = "uint16";
        }
    else if (marker == ISIHDR_POINTER_VOID)
        {
        item->type_name = "void*";
        }
    else
        {
        /* 
        marker == ISIHDR_MARKER_ANYSIZE ||
        marker == ISIHDR_MARKER_SINGLE_ELEMENT ||
        marker == ISIHDR_MARKER_UNION ||
        marker == ISIHDR_RESERVE_SPACE ||
        marker == ISIHDR_MARKER_POINTER || - handled at end of function
        */
        switch (org_item->base.subtype)
            {
            case AUTOGEN_ITEM_BLOCK:
            case AUTOGEN_ITEM_FILLER:
            case AUTOGEN_ITEM_LST:
            case AUTOGEN_ITEM_MERGE:
            case AUTOGEN_ITEM_RANGE:
            case AUTOGEN_ITEM_TIMESTAMP:
                {
                item->type_name = hdr_typename_from_length(item->type_length);
                }
                break;

            case AUTOGEN_ITEM_POINTER:
                {
                if (org_item->base.flag & AUTOGEN_POINTER_UINT64)
                    {
                    item->type_name = "uint64*";
                    }
                else if (org_item->base.flag & AUTOGEN_POINTER_INT64)
                    {
                    item->type_name = "int64*";
                    }
                else if (org_item->base.flag & AUTOGEN_POINTER_UINT32)
                    {
                    item->type_name = "uint32*";
                    }
                else if (org_item->base.flag & AUTOGEN_POINTER_INT32)
                    {
                    item->type_name = "int32*";
                    }
                else if (org_item->base.flag & AUTOGEN_POINTER_UINT16)
                    {
                    item->type_name = "uint16*";
                    }
                else if (org_item->base.flag & AUTOGEN_POINTER_INT16)
                    {
                    item->type_name = "int16*";
                    }
                else if (org_item->base.flag & AUTOGEN_POINTER_UINT8)
                    {
                    item->type_name = "uint8*";
                    }
                else
                if (org_item->base.flag & AUTOGEN_POINTER_INT8)
                    {
                    item->type_name = "int8*";
                    }
                else
                    {
                    item->type_name = "void*";
                    }
                }
                break;

            case AUTOGEN_ITEM_STRING:
                {
                if (org_item->base.flag & AUTOGEN_STRING_UNICODE)
                    {
                    item->type_name = "char16";
                    }
                else if (org_item->base.flag & AUTOGEN_STRING_ASCII)
                    {
                    item->type_name = "char";
                    }
                else if (org_item->base.flag & AUTOGEN_STRING_UTF8)
                    {
                    item->type_name = "utf8_char";
                    }
                else
                    {
                    item->type_name = "uint8";
                    }
                }
                break;

            case AUTOGEN_ITEM_STRUCT:
                {
                const autogen_item_struct* item_struct = (const autogen_item_struct*)org_item;

                autogen_it struct_it = INIT_ITERATOR;

                struct_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
                struct_it.obj.name = item_struct->seqname;
                struct_it.ver      = &item_struct->base.base.ver;
                struct_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;

                item->type_name = prop_get_string(autogen_obj_find_in_list(&struct_it, &item_struct->seqres->seq_list), PROPERTY_ISIHDR_STRUCT_NAME);
                }
                break;

            case AUTOGEN_ITEM_VALUE:
            case AUTOGEN_ITEM_REF:
                {
                const autogen_item_value* item_val = (const autogen_item_value*)org_item;
                int generate_bool = 
                    prop_has((autogen_obj*)org_item, PROPERTY_ISIHDR_GENERATE_AS_BOOL) && 
                    prop_has((autogen_obj*)env->res, PROPERTY_ISIHDR_GENERATE_BOOLS);
                int generate_bitf = 
                    prop_has((autogen_obj*)org_item, PROPERTY_ISIHDR_GENERATE_AS_BITFIELD) && 
                    prop_has((autogen_obj*)env->res, PROPERTY_ISIHDR_GENERATE_BITFIELDS );

                if (item_val->pres.type == AUTOGEN_PRESENTATION_ASCII_CHAR)
                    {
                    item->type_name = "char";
                    }
                else if (item_val->pres.type == AUTOGEN_PRESENTATION_UNICODE_CHAR)
                    {
                    item->type_name = "char16";
                    }
                else if (generate_bool)
                    {
                    char* typename_bool = (char*)pmd_heap_alloc_h(env->heap_handle, 20);
                    sprintf(typename_bool, "bool%d", abs(item->type_length));
                    item->type_name = typename_bool;
                    }
                else if (generate_bitf)
                    {
                    char* typename_bitf = (char*)pmd_heap_alloc_h(env->heap_handle, 20);
                    sprintf(typename_bitf, "bits%d", abs(item->type_length));
                    item->type_name = typename_bitf;
                    }
                else
                    {
                    item->type_name = hdr_typename_from_length(item->type_length);
                    }
                }
                break;

            case AUTOGEN_ITEM_PRINTF:
                {
                item->type_name = prop_get_string(&org_item->base, PROPERTY_ISIHDR_STRUCT_NAME);
                }
                break;

            /* Should never come here... */
            case AUTOGEN_ITEM_CHOICE:
            case AUTOGEN_ITEM_CASE:
            case AUTOGEN_ITEM_RANGE_ENTRY:
            case AUTOGEN_ITEM_TRCSTRUCTURE:
            default:
                {
                item->type_name = hdr_typename_from_length(item->type_length);

                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Default case met in hdr_structure_item_set_typename(). item->base.subtype is 0x%8.8X", org_item->base.subtype);
                }
                break;
            }
        }

    /* Add pointer to typename? */
    if (marker == ISIHDR_MARKER_POINTER)
        {
        char* new_type_name = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(item->type_name) + 2);
        strcpy(new_type_name, item->type_name);
        strcat(new_type_name, "*");

        item->type_name = new_type_name;
        }

    if (!strcmp(item->type_name, ""))
        {
        item->type_name = "uint8";
        }
    }

LOCAL void hdr_dump_byte(hdr_environment* env, const autogen_seq* seq, hdr_item** hdr_item_list, int is_last)
    {
    if (env->isihdr_16_item_byte)
        {
        /* if last byte in message, change to merge field with filler byte as 2nd byte */
        if (is_last)
            {
            hdr_item* fill1 = hdr_structure_item_create(env, "fill1", "Filler", 8, NULL, HDR_ITEM_FILLER);
            hdr_item* merge = hdr_structure_item_merge(env, env->isihdr_16_item_byte, fill1);

            if (!(env->isihdr_16_item_byte->flags & HDR_ITEM_FIXED_TYPENAME))
                {
                merge->type_name = "uint16";
                }

            hdr_structure_item_add(hdr_item_list, merge);
            }
        else
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Warning: In the 16 bit structure for %s '%s', the variable '%s' is changed to uint16 to ensure correct alignment",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq), env->isihdr_16_item_byte->varname);

            if (!(env->isihdr_16_item_byte->flags & HDR_ITEM_FIXED_TYPENAME))
                {
                if (env->isihdr_16_item_byte->flags & HDR_ITEM_POINTER)
                    {
                    env->isihdr_16_item_byte->type_name = "uint16*";
                    }
                else
                    {
                    env->isihdr_16_item_byte->type_name = "uint16";
                    }
                }

            hdr_structure_item_add(hdr_item_list, env->isihdr_16_item_byte);
            }

        env->isihdr_16_item_byte = NULL;
        }
    }

LOCAL void hdr_halfen_agg(hdr_environment* env, const autogen_seq* seq, hdr_item* item)
    {
    /* even number */
    if ((item->agg_n[0] % 2) == 0)
        {
        item->agg_n[0] = item->agg_n[0]/2;
        }
    /* uneven number */
    else
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
            "Warning: In the 16 bit structure for %s '%s', the array size of variable '%s' is enlargened with one byte",
            util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq), item->varname);

        item->agg_n[0] = (item->agg_n[0] + 1)/2;
        }

    if (item->agg_str[0][0])
        {
        char* new_agg_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(item->agg_str[0]) + 10);

        strcpy(new_agg_str, "(");
        strcat(new_agg_str, item->agg_str[0]);
        strcat(new_agg_str, " + 1)/2");

        item->agg_str[0] = new_agg_str;
        }
    }

LOCAL void hdr_generate_structure_items(hdr_environment* env, const autogen_seq* seq, hdr_item** hdr_item_list, autogen_obj_list* obj_list)
    {
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
        {
        isihdr_marker_type marker = (unsigned int)prop_get_value_default(&item->base, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_NONE);
        hdr_item* new_item = NULL;

        /* If item should not be generated, generated an empty item with the comments only */
        if (item->base.flag & env->dont_generate_flag)
            {
            new_item = hdr_structure_item_clone(env, item, HDR_ITEM_EMPTY);
            }
        else
            {
            unsigned int flags = 0;

            switch (item->base.subtype)
                {
                case AUTOGEN_ITEM_FILLER:
                    {
                    /* Dont generate dynamic fillers */
                    if (item->agg_type != AGG_TYPE_DYNAMIC_ALIGNMENT)
                        {
                        new_item = hdr_structure_item_clone(env, item, HDR_ITEM_FILLER);
                        }
                    }
                    break;

                case AUTOGEN_ITEM_BLOCK:
                case AUTOGEN_ITEM_POINTER:
                case AUTOGEN_ITEM_RANGE:
                case AUTOGEN_ITEM_REF:
                case AUTOGEN_ITEM_STRING:
                case AUTOGEN_ITEM_STRUCT:
                case AUTOGEN_ITEM_TIMESTAMP:
                case AUTOGEN_ITEM_VALUE:
                case AUTOGEN_ITEM_PRINTF:
                    {
                    /* Dont generate dynamic fillers */
                    if (item->base.subtype == AUTOGEN_ITEM_FILLER && item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
                        {
                        break;
                        }

                    new_item = hdr_structure_item_clone(env, item, flags);

                    /* Split the item in two, if required */
                    if (prop_has_valid_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED))
                        {
                        new_item = hdr_structure_item_split(env, new_item, item->varname,
                            prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED), 16);
                        }
                    else
                        if (prop_has_valid_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED))
                        {
                        new_item = hdr_structure_item_split(env, new_item, item->varname,
                            prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED), -16);
                        }
                    }
                    break;

                case AUTOGEN_ITEM_MERGE:
                    {
                    autogen_item* merge_item = NULL;
                    autogen_it merge_item_it = INIT_ITERATOR;

                    new_item = hdr_structure_item_clone(env, item, HDR_ITEM_MERGE);

                    merge_item = (autogen_item*)autogen_obj_find_in_list(&merge_item_it, &item->base.child_list);
                    while (merge_item)
                        {
                            if (abs(merge_item->length) > 0 && (merge_item->base.subtype != AUTOGEN_ITEM_FILLER || !(merge_item->base.flag & AUTOGEN_FILLER_IS_REPLACED)))
                            {
                            hdr_item* new_merge_item = 
                                hdr_structure_item_create(env, merge_item->varname, merge_item->parname, merge_item->length, 
                                                        merge_item->base.cmt_list, 0);

                            /* Set flag, if item is a filler */
                            if (merge_item->base.subtype == AUTOGEN_ITEM_FILLER)
                                {
                                new_merge_item->flags |= HDR_ITEM_FILLER;
                                }

                            new_merge_item->prop = merge_item->base.prop_list;

                            if (merge_item->base.subtype & (AUTOGEN_ITEM_RANGE | AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_REF))
                                {
                                new_merge_item->pres = ((const autogen_item_value*)merge_item)->pres;
                                }

                            hdr_structure_item_add(&new_item->child_list, new_merge_item);
                            }

                        merge_item = (autogen_item*)autogen_obj_find_next_in_list(&merge_item_it);
                        }
                    }

                    /* Split the item in two, if required */
                    if (prop_has_valid_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED))
                        {
                        new_item = hdr_structure_item_split(env, new_item, item->varname,
                            prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED), 16);
                        }
                    else
                    if (prop_has_valid_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED))
                        {
                        new_item = hdr_structure_item_split(env, new_item, item->varname,
                            prop_get_string(&item->base, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED), -16);
                        }
                    break;

                case AUTOGEN_ITEM_CHOICE:
                    {
                    /* Refer to unions */
                    if (prop_has(&env->res->base, PROPERTY_ISIHDR_GENERATE_CHOICE_UNIONS))
                        {
                        autogen_cmt* cmt = NULL;

                        char* type_name = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(env->res->base.name) + strlen(seq->base.name) + strlen(item->refname) + 10);

                        hdr_cmt_append(env, COMMENT_TEXT, "Union on ", &cmt);
                        hdr_cmt_append(env, COMMENT_TEXT, item->refname, &cmt);

                        new_item = hdr_structure_item_create(env, item->varname, "", 0, cmt, HDR_ITEM_NOT_IN_SIZE);

                        sprintf(type_name, "%s_%s_%s_UNION", env->res->base.name, seq->base.name, item->refname);
                        new_item->type_name = type_name;
                        }
                    /* Default: only generate the default case of a choice */
                    else
                        {
                        autogen_obj* default_case = (autogen_obj*)((autogen_item_choice*)item)->default_case;
                        if (default_case)
                            {
                            hdr_generate_structure_items(env, seq, hdr_item_list, &default_case->child_list);
                            }
                        }
                    }
                    break;

                case AUTOGEN_ITEM_LST:
                    {
                    new_item = hdr_structure_item_clone(env, item, flags);

                    /* If a union is to be generated, generate a child for each item */
                    if (marker == ISIHDR_MARKER_UNION)
                        {
                        autogen_it ref_it = INIT_ITERATOR;
                        autogen_seq_ref* ref;

                        ref_it.typemask    = AUTOGEN_OBJ_REF;
                        ref_it.subtypemask = AUTOGEN_OBJ_SB;
                        ref_it.flagnone    = env->dont_generate_flag;
                        ref_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                        ref_it.ver         = &item->base.ver;
                        
                        ref = (autogen_seq_ref*)autogen_obj_find_in_list(&ref_it, &item->base.child_list);
                        while (ref)
                            {
                            autogen_obj* sb = &ref->seqptr->base;

                            hdr_item* union_item = hdr_structure_item_create(env, 
                                prop_get_string((autogen_obj*)ref, PROPERTY_ISIHDR_DEFINITION_NAME),
                                "", 0, NULL, 0);

                            union_item->type_name = prop_get_string(sb,  PROPERTY_ISIHDR_STRUCT_NAME);

                            /* if (autogen_ver_comp(ref->base.ver.from, item_it->base.ver.from) > 0) */
                            if (autogen_ver_comp(ref->base.ver.from, item->base.ver.from) & AUTOGEN_VER_OLDER)
                                {
                                union_item->ver_from = ref->base.ver.from;
                                }
                            /* if (autogen_ver_comp(ref->base.ver.to, item_it->base.ver.to) < 0) */
                            if (autogen_ver_comp(ref->base.ver.to, item->base.ver.to) & AUTOGEN_VER_NEWER)
                                {
                                union_item->ver_to = ref->base.ver.to;
                                }

                            hdr_structure_item_add(&new_item->child_list, union_item);

                            ref = (autogen_seq_ref*)autogen_obj_find_next_in_list(&ref_it);
                            }

                        new_item->flags |= HDR_ITEM_UNION;
                        }
                    }
                    break;

                case AUTOGEN_ITEM_TRCSTRUCTURE:
                    {
                    new_item = hdr_structure_item_clone(env, item, flags);
                    }
                    break;

                case AUTOGEN_ITEM_CASE:
                    {
                    /* Do nothing in these cases */
                    }
                    break;

                /* Should never come here... */
                default:
                    {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in hdr_generate_structure_items(). item->base.subtype is 0x%8.8X", item->base.subtype);
                    }
                    break;
                }
            }

        /* Add the new item to the item list */
        if (new_item)
            {
            /* If an ANY_SIZE_XXX item, always exclude from size calculations */
            if (marker == ISIHDR_MARKER_ANYSIZE ||
                marker == ISIHDR_MARKER_ANYSIZE_BYTE ||
                marker == ISIHDR_MARKER_ANYSIZE_WORD ||
                marker == ISIHDR_MARKER_UNION)
                {
                new_item->flags |= HDR_ITEM_NOT_IN_SIZE;

                if (env->isihdr_16_item_byte)
                    {
                    env->isihdr_16_item_byte->flags |= HDR_ITEM_NOT_IN_SIZE;
                    }
                }

            /* Specialise the item for 8 / 16 bit */
            if (env->type == ISIHDR_TYPE_8)
                {
                new_item = hdr_structure_item_specialize_8(env, new_item, item);
                }
            else
                {
                new_item = hdr_structure_item_specialize_16(env, seq, hdr_item_list, new_item, item);
                }

            if (new_item)
                {
                hdr_structure_item_add(hdr_item_list, new_item);
                }

            /* Update new items... */
            if (new_item && (new_item->flags & HDR_ITEM_NOT_IN_SIZE))
                {
                while (new_item)
                    {
                    new_item->flags |= HDR_ITEM_NOT_IN_SIZE;
                    new_item = new_item->next;
                    }
                }
            }

        item = (autogen_item*)item->base.next;
        }

    /* If 16-bit output, dump the last byte, if any */
    if (env->type == ISIHDR_TYPE_16)
        {
        hdr_dump_byte(env, seq, hdr_item_list, TRUE);
        }
    }

LOCAL hdr_item* hdr_structure_item_specialize_8(hdr_environment* env, hdr_item* item, const autogen_item* org_item)
    {
    switch (org_item->base.subtype)
        {
        case AUTOGEN_ITEM_MERGE:
        case AUTOGEN_ITEM_FILLER:
        case AUTOGEN_ITEM_RANGE:
        case AUTOGEN_ITEM_REF:
        case AUTOGEN_ITEM_TIMESTAMP:
        case AUTOGEN_ITEM_VALUE:
            {
            if (prop_has(&org_item->base, PROPERTY_ISIHDR_SPLIT_AS_ARRAY))
                {
                int n = abs(item->field_length) / 8;

                item->type_length  = 8;
                item->field_length = 8;
                item->type_name    = "uint8";

                if (item->flags & HDR_ITEM_ARRAY)
                    {
                    item->agg_n[1]   = (unsigned int)n;
                    item->agg_str[1] = "";

                    item->flags |= HDR_ITEM_ARRAY_2;
                    }
                else
                    {
                    item->agg_n[0]   = (unsigned int)n;
                    item->agg_str[0] = "";

                    item->flags |= HDR_ITEM_ARRAY;
                    }

                /* Remove pointer flag now */
                item->flags &= ~HDR_ITEM_POINTER;
                }
            else
            if (prop_has_valid_string(&org_item->base, PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED))
                {
                item = hdr_structure_item_split(env, item, org_item->varname,
                    prop_get_string(&org_item->base, PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED), 8);
                }
            else
            if (prop_has_valid_string(&org_item->base, PROPERTY_ISIHDR_SPLIT_WORD_SIGNED))
                {
                item = hdr_structure_item_split(env, item, org_item->varname,
                    prop_get_string(&org_item->base, PROPERTY_ISIHDR_SPLIT_WORD_SIGNED), -8);
                }
            }
            break;
        }

    return item;
    }

LOCAL hdr_item* hdr_structure_item_specialize_16(hdr_environment* env, const autogen_seq* seq, 
                                                 hdr_item** hdr_item_list, hdr_item* item, const autogen_item* org_item)
    {
    int split_dwords = prop_has(&env->res->base, PROPERTY_ISIHDR_SPLIT_DWORDS_16);

    /* For empty items, do nothing */
    if (item->flags & HDR_ITEM_EMPTY)
        {
        }
    else
    if (item->field_length == 8 && item->agg_n[0] == 3 && (item->flags & HDR_ITEM_FILLER))
        {
        char* varname = pmd_heap_alloc_h(env->heap_handle, strlen(item->varname) + 10);

        hdr_item* filler_item = hdr_structure_item_create(env, item->varname, item->parname, 16, NULL, HDR_ITEM_FILLER);

        /* Remove array flags, so item is just a plain filler */
        item->flags &= ~(HDR_ITEM_ARRAY | HDR_ITEM_ARRAY_2);

        /* If a byte alreay exists, merge with first filler */
        if (env->isihdr_16_item_byte)
            {
            sprintf(varname, "%s_0", item->varname);

            item->varname = varname;
            item          = hdr_structure_item_merge(env, env->isihdr_16_item_byte, item);
            item->next    = filler_item;

            env->isihdr_16_item_byte = NULL;
            }
        else
            {
            sprintf(varname, "%s_2", item->varname);

            item->varname = varname;

            env->isihdr_16_item_byte = item;

            item = filler_item;
            }
        }
    else
    if ((abs(item->field_length) == 16 || abs(item->field_length) == 32) && prop_has(&org_item->base, PROPERTY_ISIHDR_SPLIT_AS_ARRAY))
        {
        int n = abs(item->field_length) / 16;

        item->type_length  = 16;
        item->field_length = 16;
        item->type_name    = "uint16";

        if (item->flags & HDR_ITEM_ARRAY)
            {
            item->agg_n[1]   = (unsigned int)n;
            item->agg_str[1] = "";

            item->flags |= HDR_ITEM_ARRAY_2;
            }
        else
            {
            item->agg_n[0]   = (unsigned int)n;
            item->agg_str[0] = "";

            item->flags |= HDR_ITEM_ARRAY;
            }

        /* Remove pointer flag now */
        item->flags &= ~HDR_ITEM_POINTER;
        }
    /* Split Dwords to words?? */
    else
    if (abs(item->field_length) == 32 && split_dwords)
        {
        char* varname1 = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(item->varname) + 5);
        char* varname2 = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(item->varname) + 5);

        sprintf(varname1, "%s_msw", item->varname);
        sprintf(varname2, "%s_lsw", item->varname);

        hdr_dump_byte(env, seq, hdr_item_list, FALSE);

        item = hdr_structure_item_split(env, item, varname1, varname2, 16);
        }
    else
    if (abs(item->field_length) == 8)
        {
        /* If an array, change the type and number of elements */
        if (item->flags & HDR_ITEM_ARRAY)
            {
            /* Dump the saved byte (if any) as a word and produce a warning */
            hdr_dump_byte(env, seq, hdr_item_list, FALSE);

            /* If the array size if fixed, dont do anything */
            if (item->flags & HDR_ITEM_FIXED_ARRAY)
                {
                }
            /* An array of 2 bytes should simply be a word */
            else
            if (item->agg_n[0] == 2 && !item->agg_str[0][0])
                {
                item->agg_n[0]  = 1;
                item->flags    &= ~HDR_ITEM_ARRAY;
                }
            /* Halfen the array size */
            else
                {
                hdr_halfen_agg(env, seq, item);
                }

            item->type_length  = 16;
            item->field_length = 16;
            }
        /* If a byte is already saved, merge the two into a word */
        else
        if (env->isihdr_16_item_byte)
            {
            item = hdr_structure_item_merge(env, env->isihdr_16_item_byte, item);
            env->isihdr_16_item_byte = NULL;
            }
        /* Save the byte for later */
        else
            {
            env->isihdr_16_item_byte = item;
            item = NULL;
            }

        if (item && !(item->flags & HDR_ITEM_FIXED_TYPENAME))
            {
            if (item->flags & HDR_ITEM_POINTER)
                {
                item->type_name = "uint16*";
                }
            else
                {
                item->type_name = "uint16";
                }
            }
        }
    /* If a byte is saved, dump it as a word and generate a warning */
    else
        {
        hdr_dump_byte(env, seq, hdr_item_list, FALSE);
        }

    /* Change the type name, if needed */
    if (item && item->type_name)
        {
        if (item->type_name && strcmp(item->type_name, "uint8") == 0)
            {
            item->type_name = "uint16";
            }
        else
        if (item->type_name && strcmp(item->type_name, "uint8*") == 0)
            {
            item->type_name = "uint16*";
            }
        else
        if (item->type_name && strcmp(item->type_name, "uint8**") == 0)
            {
            item->type_name = "uint16**";
            }
        else
        if (item->type_name && strcmp(item->type_name, "int8") == 0)
            {
            item->type_name = "int16";
            }
        else
        if (item->type_name && strcmp(item->type_name, "int8*") == 0)
            {
            item->type_name = "int16*";
            }
        else
        if (item->type_name && strcmp(item->type_name, "int8**") == 0)
            {
            item->type_name = "int16**";
            }
        else
        if (item->type_name && strcmp(item->type_name, "bool8") == 0)
            {
            item->type_name = "bool16";
            }
        else
        if (item->type_name && strcmp(item->type_name, "bool8*") == 0)
            {
            item->type_name = "bool16*";
            }
        else
        if (item->type_name && strcmp(item->type_name, "bool8**") == 0)
            {
            item->type_name = "bool16**";
            }
        else
        if (item->type_name && strcmp(item->type_name, "bits8") == 0)
            {
            item->type_name = "bits16";
            }
        else
        if (item->type_name && strcmp(item->type_name, "bits8*") == 0)
            {
            item->type_name = "bits16*";
            }
        else
        if (item->type_name && strcmp(item->type_name, "bits8**") == 0)
            {
            item->type_name = "bits16**";
            }
        else
        if (item->type_name && strcmp(item->type_name, "char*") == 0)
            {
            item->type_name = "uint16*";
            }
        else
        if (item->type_name && strcmp(item->type_name, "char**") == 0)
            {
            item->type_name = "uint16**";
            }
        else
        if (item->type_name && strcmp(item->type_name, "utf8_char*") == 0)
            {
            item->type_name = "uint16*";
            }
        else
        if (item->type_name && strcmp(item->type_name, "utf8_char**") == 0)
            {
            item->type_name = "uint16**";
            }
        }

    return item;
    }

/*
Creates a list of all items to be generated in a structure.
- The list is not specific for 8 or 16 bit output
- The type names of the items is empty
*/
LOCAL hdr_item* hdr_generate_structure_item_list(hdr_environment* env, autogen_seq* seq)
    {
    hdr_item* item_list = NULL;

    /* generate header items */
    if (seq->base.type == AUTOGEN_OBJ_MSG && 
        env->include_phonet_header &&
        !prop_has((autogen_obj*)seq, PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE))
        {
        hdr_item* rdv_item, *sdv_item, *res_item, *med_item, *len_item, *rob_item, *sob_item;

        autogen_cmt* cmt_before = NULL;
        autogen_cmt* cmt_after = NULL;

        hdr_cmt_append(env, COMMENT_ISIHDR_BEFORE_DEF, "/* PhoNet header */", &cmt_before);
        hdr_cmt_append(env, COMMENT_ISIHDR_BEFORE_DEF_16, "/* PhoNet header */", &cmt_before);

        hdr_cmt_append(env, COMMENT_ISIHDR_AFTER_DEF, "/* Message data */", &cmt_after);
        hdr_cmt_append(env, COMMENT_ISIHDR_AFTER_DEF_16, "/* Message data */", &cmt_after);

        med_item = hdr_structure_item_create(env, "media",        "Media",              8,  cmt_before,     HDR_ITEM_PHONET_HDR);
        len_item = hdr_structure_item_create(env, "length",       "Length",            16,  NULL,           HDR_ITEM_PHONET_HDR);
        rob_item = hdr_structure_item_create(env, "receiver_obj", "Receiver object",    8,  NULL,           HDR_ITEM_PHONET_HDR);
        sob_item = hdr_structure_item_create(env, "sender_obj",   "Sender object",      8,  cmt_after,      HDR_ITEM_PHONET_HDR);

        if (env->phonet_header_layout == 0)
            {
            rdv_item = hdr_structure_item_create(env, "receiver_dev", "Receiver device",    8,  NULL, HDR_ITEM_PHONET_HDR);
            sdv_item = hdr_structure_item_create(env, "sender_dev",   "Sender device",      8,  NULL, HDR_ITEM_PHONET_HDR);
            res_item = hdr_structure_item_create(env, "res",          "Resource ID",        8,  NULL, HDR_ITEM_PHONET_HDR);

            med_item->varname_16 = "media_dev";
            sdv_item->varname_16 = "dev_res";
            sob_item->varname_16 = "obj";
            }
        else
        if (env->phonet_header_layout == 1)
            {
            rdv_item = hdr_structure_item_create(env, "receiver",     "Receiver device",    8,  NULL, HDR_ITEM_PHONET_HDR);
            sdv_item = hdr_structure_item_create(env, "sender",       "Sender device",      8,  NULL, HDR_ITEM_PHONET_HDR);
            res_item = hdr_structure_item_create(env, "function",     "Resource ID",        8,  NULL, HDR_ITEM_PHONET_HDR);

            sob_item->varname_16 = "receiver_sender";
            }
        else
            {
            rdv_item = hdr_structure_item_create(env, "receiver_dev", "Receiver device",    8,  NULL, HDR_ITEM_PHONET_HDR);
            sdv_item = hdr_structure_item_create(env, "sender_dev",   "Sender device",      8,  NULL, HDR_ITEM_PHONET_HDR);
            res_item = hdr_structure_item_create(env, "resource",     "Resource ID",        8,  NULL, HDR_ITEM_PHONET_HDR);
            }

        if (env->type == ISIHDR_TYPE_16)
            {
            hdr_item* w1 = hdr_structure_item_merge(env, med_item, rdv_item);
            hdr_item* w2 = hdr_structure_item_merge(env, sdv_item, res_item);
            hdr_item* w4 = hdr_structure_item_merge(env, rob_item, sob_item);

            hdr_structure_item_add(&item_list, w1);
            hdr_structure_item_add(&item_list, w2);
            hdr_structure_item_add(&item_list, len_item);
            hdr_structure_item_add(&item_list, w4);
            }
        else
            {
            hdr_structure_item_add(&item_list, med_item);
            hdr_structure_item_add(&item_list, rdv_item);
            hdr_structure_item_add(&item_list, sdv_item);
            hdr_structure_item_add(&item_list, res_item);
            hdr_structure_item_add(&item_list, len_item);
            hdr_structure_item_add(&item_list, rob_item);
            hdr_structure_item_add(&item_list, sob_item);
            }
        }

    /* generate 'body' items */
    if (seq)
        {
        hdr_generate_structure_items(env, seq, &item_list, &seq->base.child_list);
        }

    return item_list;
    }

LOCAL void hdr_generate_embedded_structure_names(hdr_environment* env,
                                                 const char* varname1, const char* varname2,
                                                 char** s_name, char** m_name, char** l_name)
    {
    unsigned int index = 0;

    /* Find first character where the two string are different */
    while (varname1[index] && varname2[index] && varname1[index] == varname2[index])
        {
        ++index;
        }

    if (index != 0)
        {
        *s_name = (char*)pmd_heap_strdup_h(env->heap_handle, varname1);

        (*s_name)[index] = 0;
        if (index > 1 && (*s_name)[index-1] == '_')
            {
            (*s_name)[index-1] = 0;
            }

        *m_name = (char*)pmd_heap_strdup_h(env->heap_handle, &varname1[index]);
        *l_name = (char*)pmd_heap_strdup_h(env->heap_handle, &varname2[index]);
        }
    else
        {
        *s_name = (char*)pmd_heap_strdup_h(env->heap_handle, varname1);
        *m_name = (char*)pmd_heap_strdup_h(env->heap_handle, "ms");
        *l_name = (char*)pmd_heap_strdup_h(env->heap_handle, "ls");
        }
    }

LOCAL hdr_item* hdr_structure_item_create(hdr_environment* env, const char* varname, const char* parname, int length, autogen_cmt* cmt, unsigned int flags)
    {
    hdr_item* item = (hdr_item*)pmd_heap_alloc_h(env->heap_handle, sizeof(hdr_item));

    if (length != 0)
        {
        item->type_name = hdr_typename_from_length(length);
        }
    else
        {
        item->type_name = "";
        }

    item->agg_str[0]    = "";
    item->agg_str[1]    = "";
    item->varname       = varname;
    item->parname       = parname;
    item->type_length   = length;
    item->field_length  = length;
    item->flags         = flags;
    item->cmt           = cmt;
    item->prop          = NULL;
    item->feature_flags = NULL;

    return item;
    }

LOCAL hdr_item* hdr_structure_item_clone(hdr_environment* env, autogen_item* item, unsigned int flags)
    {
    hdr_item* new_item = hdr_structure_item_create(env, item->varname, item->parname, 0, NULL, flags);
    isihdr_marker_type marker = (unsigned int)prop_get_value_default(&item->base, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_NONE);

    /* Generate correct variable name */
    if (prop_has(&item->base, PROPERTY_ISIHDR_VARNAME_16))
        {
        new_item->varname_16 = prop_get_string(&item->base, PROPERTY_ISIHDR_VARNAME_16);
        }
 
    /* set pointer to property list */
    new_item->prop = item->base.prop_list;

    if (item->base.subtype & (AUTOGEN_ITEM_RANGE | AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_REF))
        {
        new_item->pres = ((autogen_item_value*)item)->pres;
        }

    /* Is item a pointer */
    if (marker == ISIHDR_MARKER_POINTER || marker == ISIHDR_POINTER)
        {
        new_item->flags |= HDR_ITEM_POINTER;
        }
    else if (marker == ISIHDR_POINTER_VOID)
        {
        new_item->flags |= HDR_ITEM_POINTER | HDR_ITEM_FIXED_TYPENAME;
        }
    /* try to see if this is where we should copy feature flags */
    if (item->base.feature_flags)
    {
        new_item->feature_flags = item->base.feature_flags;
    }

    hdr_structure_item_set_length(new_item, item);
    hdr_structure_item_set_aggregation(env, new_item, item);
    hdr_structure_item_set_typename(env, new_item, item);
    hdr_structure_item_set_comment(env, new_item, item);

    return new_item;
    }

LOCAL void hdr_structure_item_add(hdr_item** hdr_item_list, hdr_item* item)
    {
    if (*hdr_item_list)
        {
        hdr_item* item_it = *hdr_item_list;

        while (item_it->next)
            {
            item_it = item_it->next;
            }

        item_it->next = item;
        }
    else
        {
        *hdr_item_list = item;
        }
    }

/* Takes an item list and generates correct comments
*/
LOCAL void hdr_generate_structure_item_comments(hdr_environment* env, hdr_item* item_list)
    {
    hdr_item* item_it = item_list;
    while (item_it)
        {
        /* If structure, generate comments for all children */
        if (item_it->flags & HDR_ITEM_STRUCT)
            {
            hdr_generate_structure_item_comments(env, item_it->child_list);
            }
        /* Generate merge comments */
        if (item_it->flags & HDR_ITEM_MERGE)
            {
            hdr_item* merge_item = item_it->child_list;
            int offset = 0;

            while (merge_item)
                {
                char str_bits[65] = "---------------------------------------------------------------";
                int n;

                str_bits[abs(item_it->type_length)] = 0;
                for (n = offset; n < offset + abs(merge_item->type_length); n++)
                    {
                    str_bits[n] = 'x';
                    }

                hdr_cmt_append(env, COMMENT_TEXT, str_bits, &item_it->cmt);
                hdr_cmt_append(env, COMMENT_TEXT, "  ", &item_it->cmt);

                if (merge_item->flags & HDR_ITEM_MERGE_HI)
                    {
                    hdr_cmt_append(env, COMMENT_TEXT, merge_item->parname, &item_it->cmt);
                    hdr_cmt_append(env, COMMENT_PARAGRAPH, " (High part)", &item_it->cmt);
                    }
                else
                if (merge_item->flags & HDR_ITEM_MERGE_LO)
                    {
                    hdr_cmt_append(env, COMMENT_TEXT, merge_item->parname, &item_it->cmt);
                    hdr_cmt_append(env, COMMENT_PARAGRAPH, " (Low part)", &item_it->cmt);
                    }
                else
                    {
                    hdr_cmt_append(env, COMMENT_PARAGRAPH, merge_item->parname, &item_it->cmt);
                    }

                offset += abs(merge_item->type_length);

                merge_item = merge_item->next;
                }

            hdr_cmt_ensure_newline(env, &item_it->cmt);
            }

        item_it = item_it->next;
        }
    }

/* Prints a structure item
*/
LOCAL void hdr_structure_print_item(hdr_environment* env, const hdr_item* item, unsigned int indent)
    {
    unsigned int space_for_comment;
    char* comment;

    /* Generate declaration */
    char* declaration = (char*)pmd_heap_alloc_h(env->heap_handle,
                                                strlen(item->type_name) + strlen(item->varname) + 
                                                strlen(item->agg_str[0]) + strlen(item->agg_str[1]) + 30);
    if (strlen(item->type_name) > 7)
        {
        sprintf(declaration, "%s ", item->type_name);
        }
    else
        {
        sprintf(declaration, "%-8s", item->type_name);
        }
    strcat(declaration, item->varname);

    /* Generate array (2nd dimension) */
    if (item->flags & HDR_ITEM_ARRAY_2)
        {
        if (item->agg_str[1][0])
            {
            sprintf(declaration+strlen(declaration), "[%s]", item->agg_str[1]);
            }
        else
            {
            sprintf(declaration+strlen(declaration), "[%u]", item->agg_n[1]);
            }
        }

    /* Generate array (1st dimension) */
    if (item->flags & HDR_ITEM_ARRAY)
        {
        if (item->agg_str[0][0])
            {
            sprintf(declaration+strlen(declaration), "[%s]", item->agg_str[0]);
            }
        else
            {
            sprintf(declaration+strlen(declaration), "[%u]", item->agg_n[0]);
            }
        }
    strcat(declaration, ";");

    /* Genererate comment string */
    space_for_comment = HDR_LINE_WIDTH - 5 - strlen(declaration);
    comment = hdr_format_comment(indent, TRUE, item->cmt);

    /* If comment, print comment and declaration */
    if (comment && *comment)
        {
        /* If long comment of comment contains new line, print comment before declaration */
        if (strchr(comment, '\n') || strlen(comment)-indent > space_for_comment || (item->flags & HDR_ITEM_MERGE))
            {
            fprintf(env->fout, "%s\n", comment);
            fprintf(env->fout, "%-*s%s\n", indent, " ", declaration);
            }
        /* Else print comment next to declaration */
        else
            {
            if (strlen(comment+indent) >= HDR_LINE_WIDTH - HDR_LINE_COMMENT_START)
                {
                /* Right-align to end of line */
                fprintf(env->fout, "%-*s%s %*s\n", indent, " ", declaration, space_for_comment, comment+indent);
                }
            else
                {
                /* Left-align to item_comment_start */
                fprintf(env->fout, "%-*s%-*s %s\n", indent, " ", HDR_LINE_COMMENT_START-indent, declaration, comment+indent);
                }
            }
        }
    /* Else just print declaration */
    else
        {
        fprintf(env->fout, "%-*s%s\n", indent, " ", declaration);
        }
    }

/* Prints all items in the list item_list
*/
LOCAL void hdr_structure_print_items(hdr_environment* env, const hdr_item* item_list)
    {
    const hdr_item* item_it = item_list;
    const hdr_item* child_item_it;
    autogen_feature *lastFeatureFlag = NULL;

    while (item_it)
        {
        /* If present, print feature flags */
        print_feature_flag(env, &lastFeatureFlag, item_it->feature_flags);

        /* Print leading comments */
        hdr_before_comment(env, item_it->cmt);
        child_item_it = item_it->child_list;
        while (child_item_it)
            {
            hdr_before_comment(env, child_item_it->cmt);
            child_item_it = child_item_it->next;
            }

        /* If empty item, only print comments */
        if (item_it->flags & HDR_ITEM_EMPTY)
            {
            /* Genererate comment string */
            char* comment = hdr_format_comment(HDR_LINE_INDENT, TRUE, item_it->cmt);

            /* If comment, print comment and declaration */
            if (comment && *comment)
                {
                fprintf(env->fout, "%s\n", comment);
                }
            }
        /* If an array of elements, generate an embedded structure */
        else
        if (item_it->flags & HDR_ITEM_STRUCT)
            {
            fprintf(env->fout, "%-*sstruct\n", HDR_LINE_INDENT, " ");
            fprintf(env->fout, "%-*s{\n",    2*HDR_LINE_INDENT, " ");

            hdr_structure_print_item(env, item_it->child_list,       2*HDR_LINE_INDENT);
            hdr_structure_print_item(env, item_it->child_list->next, 2*HDR_LINE_INDENT);

            fprintf(env->fout, "%-*s} %s", 2*HDR_LINE_INDENT, " ", item_it->varname);

            if (item_it->flags & HDR_ITEM_ARRAY)
                {
                if (item_it->agg_str[0][0])
                    {
                    fprintf(env->fout, "[%s]", item_it->agg_str[0]);
                    }
                else
                    {
                    fprintf(env->fout, "[%u]", item_it->agg_n[0]);
                    }
                }
            if (item_it->flags & HDR_ITEM_ARRAY_2)
                {
                if (item_it->agg_str[1][0])
                    {
                    fprintf(env->fout, "[%s]", item_it->agg_str[1]);
                    }
                else
                    {
                    fprintf(env->fout, "[%u]", item_it->agg_n[1]);
                    }
                }

            fprintf(env->fout, ";\n");
            }
        /* Generate a union */
        else
        if (item_it->flags & HDR_ITEM_UNION)
            {
            const hdr_item* union_item = item_it->child_list;

            fprintf(env->fout, "%-*sunion\n", HDR_LINE_INDENT, " ");
            fprintf(env->fout, "%-*s{\n",   2*HDR_LINE_INDENT, " ");

            while (union_item)
                {
                int cond = FALSE;

                if (union_item->ver_from)
                    {
                    fprintf(env->fout, "#if ");

                    hdr_print_min_version(env, union_item->ver_from, FALSE);

                    cond = TRUE;
                    }

                if (union_item->ver_to)
                    {
                    if (!cond)
                        {
                        fprintf(env->fout, "#if ");
                        cond = TRUE;
                        }
                    else
                        {
                        fprintf(env->fout, " && ");
                        }

                    hdr_print_min_version(env, union_item->ver_to, TRUE);
                    }

                if (cond)
                    {
                    fprintf(env->fout, "\n");
                    }

                fprintf(env->fout, "%-*s%s %s;\n", 2*HDR_LINE_INDENT, " ", union_item->type_name, union_item->varname);

                if (cond)
                    {
                    fprintf(env->fout, "#endif\n");
                    }

                union_item = union_item->next;
                }

            fprintf(env->fout, "%-*s} %s;\n", 2*HDR_LINE_INDENT, " ", item_it->varname);
            }
        else
            {
            /* Print item */
            hdr_structure_print_item(env, item_it, HDR_LINE_INDENT);
            }

        /* Print trailing comments */
        hdr_after_comment(env, item_it->cmt);
        child_item_it = item_it->child_list;
        while (child_item_it)
            {
            hdr_after_comment(env, child_item_it->cmt);
            child_item_it = child_item_it->next;
            }

        item_it = item_it->next;
        }

        /* If we were under feature flag at the end of loop then insert an feature flag end. */
        print_feature_flag(env, &lastFeatureFlag, NULL);
    }


LOCAL void hdr_cmt_ensure_newline(hdr_environment *env, autogen_cmt **cmt)
    {
    autogen_cmt* last_given = *cmt;
    if (last_given)
        {
        while (last_given->next)
            {
            last_given = last_given->next;
            }

        /* Check the last of the given comment items */
        if (last_given->id != COMMENT_NEWLINE &&
            last_given->id != COMMENT_PARAGRAPH)
            {
            /* Add a newline to ensure separation of the comments */
            hdr_cmt_append(env, COMMENT_NEWLINE, "", cmt);
            }
        }
    }

/*  This function outputs some of the bit masks for merged fields.
    Input is the list that should be searched for input to the output.
*/
LOCAL void hdr_structure_print_merge_constants(hdr_environment* env, const autogen_seq* seq, const hdr_item* item_list)
{
    const hdr_item* item_it = item_list;
    const char* prefix = prop_get_string_default(&env->res->base, PROPERTY_ISIHDR_MERGED_MASK_PREFIX, "");
    char* seqname_str;
    int has_masks = FALSE;


    /* Generate sequence name (prefix of constants) */
    seqname_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(prefix) + strlen(seq->base.name) + strlen(seq->base.base_obj->name) + 5);

    if (seq->base.type == AUTOGEN_OBJ_MSG && (seq->base.flag & AUTOGEN_MSG_IS_SUBMSG))
    {
        if (prop_has(&env->res->base, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
        {
            sprintf(seqname_str, "%s%s_", prefix, seq->base.name);
        }
        else
        {
            sprintf(seqname_str, "%s%s_%s_", prefix, seq->base.base_obj->name, seq->base.name);
        }                        
    }
    else
    {
        sprintf(seqname_str, "%s%s_", prefix, seq->base.name);
    }

    /* Iterate through all items, but only look at merged fields */
    while (item_it)
    {
        if (item_it->flags & HDR_ITEM_MERGE)
        {
            unsigned int offset = 0;
            hdr_item* merge_it = item_it->child_list;

            while (merge_it)
            {
                offset += abs(merge_it->type_length);

                if (!(merge_it->flags & HDR_ITEM_FILLER))
                {
                    char* var_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(seqname_str) + strlen(item_it->varname) + 20);

                    if (!has_masks)
                    {
                        fprintf(env->fout, "/* Merge mask constants */\n");

                        has_masks = TRUE;
                    }

                    /* Offset */
                    strcpy(var_str, seqname_str);
                    strcat(var_str, merge_it->varname);
                    /* In case item extends across split, we have to avoid duplicate names */
                    if (merge_it->flags & HDR_ITEM_MERGE_HI)
                        strcat(var_str, "_H");
                    if (merge_it->flags & HDR_ITEM_MERGE_LO)
                        strcat(var_str, "_L");
                    strcat(var_str, "_OFFSET");

#if (PMD_FILE_FORMAT >= 600)
                    if (prop_has((autogen_obj*)env->res, PROPERTY_ALIGNMENT_64_BITS))
                    {
                         hdr_print_define_hex(env, var_str, (unsigned long long)abs(item_it->type_length) - offset);
                    }
                    else
#endif
                    {
                        hdr_print_define_hex(env, var_str, (unsigned int)abs(item_it->type_length) - offset);
                    }

                    /* Width */
                    strcpy(var_str, seqname_str);
                    strcat(var_str, merge_it->varname);
                    if (merge_it->flags & HDR_ITEM_MERGE_HI)
                        strcat(var_str, "_H");
                    if (merge_it->flags & HDR_ITEM_MERGE_LO)
                        strcat(var_str, "_L");
                    strcat(var_str, "_WIDTH");

#if (PMD_FILE_FORMAT >= 600)
                    if (prop_has((autogen_obj*)env->res, PROPERTY_ALIGNMENT_64_BITS))
                    {
                         hdr_print_define_hex(env, var_str, (unsigned long long)abs(merge_it->type_length));
                    }
                    else
#endif
                    {
                        hdr_print_define_hex(env, var_str, (unsigned int)abs(merge_it->type_length));
                    }

                    /* Mask */
                    strcpy(var_str, seqname_str);
                    strcat(var_str, merge_it->varname);
                    if (merge_it->flags & HDR_ITEM_MERGE_HI)
                        strcat(var_str, "_H");
                    if (merge_it->flags & HDR_ITEM_MERGE_LO)
                        strcat(var_str, "_L");
                    strcat(var_str, "_MASK");

                    if (prop_has((autogen_obj*)env->res, PROPERTY_ALIGNMENT_64_BITS))
                    {
                        hdr_print_define_hex(env, var_str, (~((~0u) << (unsigned long long)abs(merge_it->type_length))) << ((unsigned long long)abs(item_it->type_length) - offset));
                    }
                    else
                    {
                        hdr_print_define_hex(env, var_str, (~((~0u) << (unsigned int)abs(merge_it->type_length))) << ((unsigned int)abs(item_it->type_length) - offset));
                    }
                }

                merge_it = merge_it->next;
            }
        }

        item_it = item_it->next;
    }

    if (has_masks)
    {
        fprintf(env->fout, "\n");
    }
}

/*  */
LOCAL void hdr_generate_structure_size(hdr_environment* env, const autogen_seq* seq, const hdr_item* hdr_item_list)
    {
    /* Generate size definition */
    if (prop_has_valid_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_LENGTH_NAME))
        {
        const char* strlenname = prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_LENGTH_NAME);
        unsigned int starting_pos = strlen(strlenname) + 11;
        static const unsigned int indent = 8;

        fprintf(env->fout, "#define %s   ", strlenname);

        if (prop_has((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE))
            {
            fprintf(env->fout, "(%s)\n\n", prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE));
            }
        else
            {
            /* We have an XX_ANY_SIZE item. Generate a sizeof list */
            hdr_item_size* size_list = NULL;
            int use_sizeof;

            /* Iterate through all structure items and add build a list of the different used types */
            const hdr_item* item_it = hdr_item_list;
            while (item_it)
                {
                if (item_it->flags & HDR_ITEM_EMPTY)
                    {
                    }
                else
                if (item_it->flags & HDR_ITEM_NOT_IN_SIZE)
                    {
                    }
                else
                if (item_it->flags & HDR_ITEM_ARRAY)
                    {
                    if (item_it->flags & HDR_ITEM_STRUCT)
                        {
                        hdr_item_size_add(env, &size_list, item_it->child_list->type_name, item_it->agg_str[0], item_it->agg_n[0]);
                        hdr_item_size_add(env, &size_list, item_it->child_list->type_name, item_it->agg_str[0], item_it->agg_n[0]);
                        }
                    else
                        {
                        hdr_item_size_add(env, &size_list, item_it->type_name, item_it->agg_str[0], item_it->agg_n[0]);
                        }
                    }
                else
                if (item_it->flags & HDR_ITEM_STRUCT)
                    {
                    hdr_item_size_add(env, &size_list, item_it->child_list->type_name, NULL, 1);
                    hdr_item_size_add(env, &size_list, item_it->child_list->type_name, NULL, 1);
                    }
                else
                    {
                    hdr_item_size_add(env, &size_list, item_it->type_name, NULL, 1);
                    }

                item_it = item_it->next;
                }

            if (prop_has(&seq->base, PROPERTY_ISIHDR_STRUCT_LENGTH_SIZEOF))
                {
                use_sizeof = TRUE;
                }
            else
            if (prop_has(&seq->base, PROPERTY_ISIHDR_STRUCT_LENGTH_SUM))
                {
                use_sizeof = FALSE;
                }
            else
                {
                use_sizeof = !(seq->base.flag & AUTOGEN_SEQ_IS_DYNAMIC);
                }

            /* Now generate the sizeof definition in the file */
            if (use_sizeof)
                {
                /* No XX_ANY_SIZE items. Just use a simple sizeof */
                if (strlen(prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_NAME)) + starting_pos + 8 > HDR_LINE_WIDTH)
                    {
                    fprintf(env->fout, "\\\n        ");
                    }
                fprintf(env->fout, "sizeof(%s)\n\n", 
                    prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_NAME));
                }
            else
            if (size_list)
                {
                /* We have at least one item. Go for it. */
                unsigned int coloumn = starting_pos + 1;
                fprintf(env->fout, "(");
                while (size_list)
                    {
                    /* Allocate a buffer */
                    unsigned int buffer_size = AUTOGEN_MAX_NAME_LENGTH*2 + 50;
                    unsigned int current_length = 0;
                    char* buffer = NULL;
                    if (size_list->aggs)
                        {
                        buffer_size += strlen(size_list->aggs);
                        }
                    buffer = (char*)pmd_heap_alloc_h(env->heap_handle, buffer_size);

                    /* Format the size of the item */
                    if (size_list->aggs)
                        {
                        if (size_list->simple_count)
                            {
                            sprintf(buffer, "(%u + %s)*", size_list->simple_count, size_list->aggs);
                            }
                        else
                            {
                            if (strchr(size_list->aggs, '+'))
                                {
                                sprintf(buffer, "(%s)*", size_list->aggs);
                                }
                            else
                                {
                                sprintf(buffer, "%s*", size_list->aggs);
                                }
                            }
                        }
                    else
                        {
                        if (size_list->simple_count > 1)
                            {
                            sprintf(buffer, "%u*", size_list->simple_count);
                            }
                        }
                    sprintf(buffer+strlen(buffer), "sizeof(%s)", size_list->type_name);

                    /* Print the definition to the output */
                    if (size_list->next)
                        {
                        strcat(buffer, " + ");
                        }
                    current_length = strlen(buffer);
                    if (coloumn + current_length > HDR_LINE_WIDTH && coloumn != indent)
                        {
                        /* We need a line break */
                        fprintf(env->fout, "\\\n%*s", indent, "");
                        coloumn = indent;
                        }
                    fprintf(env->fout, "%s", buffer);
                    coloumn += current_length;

                    /* move to next item size */
                    size_list = size_list->next;
                    }
                fprintf(env->fout, ")\n\n");
                }
            else
                {
                /* There were no items before XX_ANY_SIZE */
                fprintf(env->fout, "0\n\n");
                }
            }

        if (prop_has_valid_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_PHONET_LENGTH_NAME))
            {
            char* value = pmd_heap_alloc_h(env->heap_handle, strlen(strlenname) + 10);

            sprintf(value, "(%s + 2)", strlenname);

            fprintf(env->fout, "/* Size including receiver and sender object fields */\n");

            hdr_print_define(env, prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_STRUCT_PHONET_LENGTH_NAME), value, "");

            fprintf(env->fout, "\n");
            }
        }
    }

LOCAL hdr_item* hdr_structure_item_merge(hdr_environment* env, hdr_item* item1, hdr_item* item2)
    {
    hdr_item* merge_item = NULL;
    const char* varname_16 = NULL;
    
    /* Generate correct variable name */
    if (item1->varname_16)
        {
        varname_16 = item1->varname_16;
        }
    else
    if (item2->varname_16)
        {
        varname_16 = item2->varname_16;
        }
    else
        {
        char* new_varname = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(item1->varname) + strlen(item2->varname) + 5);

        strcpy(new_varname, item1->varname);
        strcat(new_varname, "_");
        strcat(new_varname, item2->varname);

        varname_16 = new_varname;
        }

    /* If both items are merged items, add the merge items from item2 to the
       merge items of item1
    */
    if ((item1->flags & HDR_ITEM_MERGE) && (item2->flags & HDR_ITEM_MERGE))
        {
        item1->varname      = varname_16;
        item1->type_length  = 16;
        item1->field_length = 16;

        hdr_structure_item_add(&item1->child_list, item2->child_list);

        merge_item = item1;
        }
    /* If item1 is a merge field, add item2 as merged field in item1
    */
    else
    if (item1->flags & HDR_ITEM_MERGE)
        {
        item1->varname      = varname_16;
        item1->type_length  = 16;
        item1->field_length = 16;

        hdr_structure_item_add(&item1->child_list, item2);

        merge_item = item1;
        }
    /* If item2 is a merge field, item1 should be placed as the first merge field in item2
    */
    else
    if (item2->flags & HDR_ITEM_MERGE)
        {
        item2->varname      = varname_16;
        item2->type_length  = 16;
        item2->field_length = 16;

        item1->next       = item2->child_list;
        item2->child_list = item1;

        merge_item = item2;
        }
    /* No merged fields here, so simply create a new merge field with item1 
       and item2 as children
    */
    else
        {
        merge_item = hdr_structure_item_create(env, varname_16, "", 16, NULL, HDR_ITEM_MERGE);

        merge_item->child_list = item1;

        item1->next = item2;
        item2->next = NULL;

        merge_item->flags |= (item1->flags & HDR_ITEM_PHONET_HDR);
        }

    /* Merge items regarding feature flags */
    if (item1->feature_flags && !item2->feature_flags)
    {
        /* Item 1 has feature flag */
        merge_item->feature_flags = item1->feature_flags;
    }
    else if (!item1->feature_flags && item2->feature_flags)
    {
        /* Item2 has feature flag */
        merge_item->feature_flags = item2->feature_flags;
    }
    else if (item1->feature_flags && item2->feature_flags)
    {
        /* Both has feature flag */
        if (item1->feature_flags == item2->feature_flags)
        {
            /* Both items have the same feature flag */
            merge_item->feature_flags = item1->feature_flags;
        } 
        else 
        {
            /* TBD: What to do. Both items have feature flags but different. Currently chosen to select item1 feature flag */
            merge_item->feature_flags = item1->feature_flags;
        }
    }
    else 
    {
        /* No feature flags on any of the items. Do nothing. */
    }

    return merge_item;
    }


LOCAL void hdr_structure_print_item_value_constants(hdr_environment* env, const autogen_seq* seq, const hdr_item* item, int* has_constants)
{
    const autogen_prop* min_prop  = NULL;
    const autogen_prop* max_prop  = NULL;
#if (PMD_FILE_FORMAT >= 600)
    const unsigned long long *p_min     = NULL;
    const unsigned long long *p_max     = NULL;
#else
    const unsigned int *p_min     = NULL;
    const unsigned int *p_max     = NULL;
#endif
    int   min_is_negative         = FALSE;
    int   max_is_negative         = FALSE;

    char value_name[AUTOGEN_MAX_NAME_LENGTH*2+50];

    /* Min and max values */
    min_prop = prop_list_find_first(item->prop, PROPERTY_ITEM_MINIMUM_VALUE);
    if (min_prop)
    {
        min_is_negative = min_prop->flags & PROPERTY_FLAG_NEGATIVE;
        p_min = &min_prop->value;
    }
    max_prop = prop_list_find_first(item->prop, PROPERTY_ITEM_MAXIMUM_VALUE);
    if (max_prop)
    {
        max_is_negative = max_prop->flags & PROPERTY_FLAG_NEGATIVE;
        p_max = &max_prop->value;
    }
    if (min_prop || max_prop ||
        (item->pres.type & AUTOGEN_PRESENTATION_SCALAR) || 
        (item->pres.type & AUTOGEN_PRESENTATION_OFFSET))
    {
        if (!*has_constants)
        {
            fprintf(env->fout, "/* Value constants */\n");
        }

        sprintf(value_name, "%s_%s", seq->base.name, item->varname);
        hdr_print_defines_value_constants(env, value_name, p_min, min_is_negative, p_max, max_is_negative, &item->pres);

        *has_constants = TRUE;
    }
}

/*  This function outputs the value constants for all range elements
    Input is the list that should be searched for input to the output.
*/
LOCAL void hdr_structure_print_value_constants(hdr_environment* env, const autogen_seq* seq, const hdr_item* item_list)
{
    const hdr_item* item_it = item_list;
    int has_constants = FALSE;

    while (item_it)
    {
        /* iterate through merged items */
        if (item_it->flags & HDR_ITEM_MERGE)
        {
            const hdr_item* merge_item_it = item_it->child_list;
            while (merge_item_it)
            {
                hdr_structure_print_item_value_constants(env, seq, merge_item_it, &has_constants);

                merge_item_it = merge_item_it->next;
            }
        }
        else
        {
            hdr_structure_print_item_value_constants(env, seq, item_it, &has_constants);
        }

        item_it = item_it->next;
    }

    if (has_constants)
    {
        fprintf(env->fout, "\n");
    }
}

LOCAL void hdr_structure_print_index_constants_struct(hdr_environment* env, const hdr_item* item_list, const char* prefix, int* offset)
    {
    const hdr_item* item_it = item_list;
    int has_any_size = FALSE;
    int has_indexes = FALSE;

    int divisor = 8;
    if (env->type == ISIHDR_TYPE_16)
        {
        divisor = 16;
        }

    /* Iterate through all items */
    while (item_it && !has_any_size)
        {
        /* For empty items, dont do anything */
        if (item_it->flags & HDR_ITEM_EMPTY)
            {
            }
        /* For PhoNet header fields, do nothing */
        else if (item_it->flags & HDR_ITEM_PHONET_HDR)
            {
            *offset = -2; /* so offset = 0 is first real message element */
            }
        else
            {
            if (!has_indexes)
                {
                fprintf(env->fout, "/* Index constants */\n");

                has_indexes = TRUE;
                }

            /* For structures, make an index to both items */
            if (item_it->flags & HDR_ITEM_STRUCT)
                {
                /* First item */
                int length = abs(item_it->child_list->type_length / divisor);

                fprintf(env->fout, "#define %s_%s_%s_INDEX  %d\n", prefix, item_it->varname, item_it->child_list->varname, offset);

                *offset += length;

                /* Second item */
                length = abs(item_it->child_list->next->type_length / divisor);

                fprintf(env->fout, "#define %s_%s_%s_INDEX  %d\n", prefix, item_it->varname, item_it->child_list->next->varname, offset);

                *offset += length;
                }
            /* Else just make one index constant */
            else
                {
                int length = abs(item_it->type_length / divisor);

                if (divisor == 8 && length == 2)
                    {
                    fprintf(env->fout, "#define %s_%s_MSB_INDEX  %d\n", prefix, item_it->varname, *offset);
                    fprintf(env->fout, "#define %s_%s_LSB_INDEX  %d\n", prefix, item_it->varname, *offset + 1);
                    }
                else
                    {
                    fprintf(env->fout, "#define %s_%s_INDEX  %d\n", prefix, item_it->varname, *offset);
                    }

                *offset += length;
                }
            }

        /* If an array, update the offset accordingly */
        if (item_it->flags & HDR_ITEM_ARRAY_2)
            {
            *offset += (item_it->agg_n[0] - 1) * (item_it->agg_n[1] - 1) * abs(item_it->type_length / divisor);
            }
        else
        if (item_it->flags & HDR_ITEM_ARRAY)
            {
            *offset += (item_it->agg_n[0] - 1) * abs(item_it->type_length / divisor);
            }

        /* Continue ?? */
        if (item_it->flags & HDR_ITEM_NOT_IN_SIZE)
            {
            has_any_size = TRUE;
            }

        item_it = item_it->next;
        }

    if (has_indexes)
        {
        fprintf(env->fout, "\n");
        }
    }

LOCAL void hdr_structure_print_index_constants(hdr_environment* env, const autogen_seq* seq, const hdr_item* item_list)
{
    char* seqname_str = NULL;
    int offset = 0;

    int divisor = 8;
    if (env->type == ISIHDR_TYPE_16)
    {
        divisor = 16;
    }

    /* Generate sequence name (prefix of constants) */
    seqname_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(seq->base.base_obj->name) + strlen(seq->base.name) + 5);

    if (seq->base.type == AUTOGEN_OBJ_MSG && (seq->base.flag & AUTOGEN_MSG_IS_SUBMSG))
    {
        if (prop_has(&env->res->base, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
        {
            strcpy(seqname_str, seq->base.name);
        }
        else
        {
            sprintf(seqname_str, "%s_%s", seq->base.base_obj->name, seq->base.name);
        }                        
    }
    else
    {
        strcpy(seqname_str, seq->base.name);
    }

    hdr_structure_print_index_constants_struct(env, item_list, seqname_str, &offset);
}

LOCAL unsigned int hdr_generate_bitmap_mask(const char* str_bitmap, char* str_mask)
{
    unsigned int mask = 0;
    unsigned int n;

    if (str_mask)
    {
        strcpy(str_mask, str_bitmap);
    }

    for (n = 0; n < strlen(str_bitmap); n++)
    {
        if (str_bitmap[n] == '1' || str_bitmap[n] == '0')
        {
            if (str_mask) str_mask[n] = 'x';
            mask |= (1 << (strlen(str_bitmap) - n - 1));
        }
        else
        {
            if (str_mask) str_mask[n] = '-';
        }
    }

    return mask;
}

LOCAL void hdr_print_bitmap_mask(hdr_environment* env, autogen_obj* tbl, autogen_it* entry_it, unsigned int* mask_list)
{
    char str_bitmap_mask[50];
    unsigned int mask;
    unsigned int index = 0;

    /* generate mask string from bitmap entry */
    mask = hdr_generate_bitmap_mask(((autogen_bittbl_entry*)entry_it->current_obj)->bit_pattern, str_bitmap_mask);

    /* Has mask already been generated? */
    while (mask_list[index] != mask && mask_list[index] != 0)
    {
        index++;
    }

    /* Generate it ! */
    {
        char str_bitmap_mask_const[500] = "";
        autogen_it search_entry_it = INIT_ITERATOR;
        autogen_bittbl_entry* search_entry = NULL;

        memcpy(&search_entry_it, entry_it, sizeof(autogen_it));

        strcpy(str_bitmap_mask_const, entry_it->current_obj->name);

        search_entry = (autogen_bittbl_entry*)autogen_obj_find_next_in_list(&search_entry_it);
        while (search_entry)
        {
            unsigned int entry_mask = hdr_generate_bitmap_mask(search_entry->bit_pattern, NULL);
            if (entry_mask == mask)
            {
                sprintf(str_bitmap_mask_const+strlen(str_bitmap_mask_const), "__%s", search_entry->base.name);
            }

            search_entry = (autogen_bittbl_entry*)autogen_obj_find_next_in_list(&search_entry_it);
        }

        /* if already exist */
        strcat(str_bitmap_mask_const, "__MASK");

        if (abs(((autogen_tbl*)tbl)->length) > 32)
        {
            fprintf(env->fout, "#define %-40s 0x%16.16X  /* %s */\n", str_bitmap_mask_const, mask, str_bitmap_mask);
        }
        else if (abs(((autogen_tbl*)tbl)->length) > 16)
        {
            fprintf(env->fout, "#define %-40s 0x%8.8X  /* %s */\n", str_bitmap_mask_const, mask, str_bitmap_mask);
        }
        else if (abs(((autogen_tbl*)tbl)->length) > 8)
        {
            fprintf(env->fout, "#define %-40s 0x%4.4X  /* %s */\n", str_bitmap_mask_const, mask, str_bitmap_mask);
        }
        else
        {
            fprintf(env->fout, "#define %-40s 0x%2.2X  /* %s */\n", str_bitmap_mask_const, mask, str_bitmap_mask);
        }

        /* Add mask to list */
        index = 0;
        while (mask_list[index] != 0)
        {
            index++;
        }
        if (index < MAX_MASKS)
        {
            mask_list[index] = mask;
        }
    }
}

LOCAL void hdr_generate_choice_unions(hdr_environment* env, autogen_seq* seq)
{
    autogen_obj* item = NULL;
    autogen_it item_it = INIT_ITERATOR;
    autogen_feature *lastFeatureFlag = NULL;

    item_it.subtypemask = AUTOGEN_ITEM_CHOICE;
    item_it.flagnone = env->dont_generate_flag;

    item = autogen_obj_find_in_list(&item_it, &seq->base.child_list);
    while (item)
    {
        autogen_item_choice* choice = (autogen_item_choice*)item;
        autogen_item* choice_case = (autogen_item*)autogen_obj_get_first_in_list(&choice->base.base.child_list);
        autogen_ref* tag = reference_find(&choice->base);
        autogen_item_value* tag_item = (tag ? (autogen_item_value*)tag->item : NULL);

        /* If present, print feature flags */
        print_feature_flag(env, &lastFeatureFlag, item->feature_flags);

        fprintf(env->fout, "\n");
        fprintf(env->fout, "/* Union: %s_%s_%s_ */\n", env->res->base.name, seq->base.name, choice->base.refname);
        fprintf(env->fout, "typedef union\n");
        fprintf(env->fout, "    {\n");
        fprintf(env->fout, "      /* Choice on %s: */\n", choice->base.refname);

        while (choice_case && tag_item)
        {
            autogen_item* case_item = (autogen_item*)autogen_obj_get_first_in_list(&choice_case->base.child_list);

            /* If present, print feature flags */
            print_feature_flag(env, &lastFeatureFlag, choice_case->base.feature_flags);

            /* Case item must be a stucture to generate an entry in the union */
            if (case_item && case_item->base.subtype == AUTOGEN_ITEM_STRUCT)
            {
                const autogen_item_struct* item_struct = (const autogen_item_struct*)case_item;
                const autogen_seq* str = NULL;

                autogen_it struct_it = INIT_ITERATOR;

                struct_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
                struct_it.obj.name = item_struct->seqname;
                struct_it.ver      = &item_struct->base.base.ver;
                struct_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;

                str = (const autogen_seq*)autogen_obj_find_in_list(&struct_it, &env->res->seq_list);
                if (str)
                {
#if (PMD_FILE_FORMAT >= 600)
                    unsigned long long id = (choice_case->base.flag & AUTOGEN_CASE_HAS_ID) ? 
                        choice_case->base.id : util_get_case_id(choice_case->base.name, tag_item->pres.tblname, tag_item->pres.tblres, &item_struct->base.base.ver);

                    fprintf(env->fout, "         %s  u%s_%llu; \n", 
                        prop_get_string(&str->base, PROPERTY_ISIHDR_STRUCT_NAME),
                        str->base.name, id);
#else
                    unsigned int id = (choice_case->base.flag & AUTOGEN_CASE_HAS_ID) ? 
                        choice_case->base.id : util_get_case_id(choice_case->base.name, tag_item->pres.tblname, tag_item->pres.tblres, &item_struct->base.base.ver);

                    fprintf(env->fout, "         %s  u%s_%u; \n", 
                        prop_get_string(&str->base, PROPERTY_ISIHDR_STRUCT_NAME),
                        str->base.name, id);
#endif
                }
            }
            /* Else if just one case item, insert that */
            else if (!case_item->base.next)
            {
#if (PMD_FILE_FORMAT >= 600)
                unsigned long long id = (choice_case->base.flag & AUTOGEN_CASE_HAS_ID) ? 
                    choice_case->base.id : util_get_case_id(choice_case->base.name, tag_item->pres.tblname, tag_item->pres.tblres, &case_item->base.ver);

                fprintf(env->fout, "         %s u%s_%llu; \n", 
                    hdr_typename_from_length(case_item->length),
                    case_item->varname, id);
#else
                unsigned int id = (choice_case->base.flag & AUTOGEN_CASE_HAS_ID) ? 
                    choice_case->base.id : util_get_case_id(choice_case->base.name, tag_item->pres.tblname, tag_item->pres.tblres, &case_item->base.ver);

                fprintf(env->fout, "         %s u%s_%u; \n", 
                    hdr_typename_from_length(case_item->length),
                    case_item->varname, id);
 #endif
           }

            choice_case = (autogen_item*)choice_case->base.next;
        }
        /* If present, print feature flags */
        print_feature_flag(env, &lastFeatureFlag, item->feature_flags);

        /* Default case */
        choice_case = (autogen_item*)choice->default_case;
        if (choice_case && tag_item)
        {
            /* Case item must be a stucture to generate an entry in the union */
            autogen_item* case_item = (autogen_item*)autogen_obj_get_first_in_list(&choice_case->base.child_list);
            if (case_item && case_item->base.subtype == AUTOGEN_ITEM_STRUCT)
            {
                const autogen_item_struct* item_struct = (const autogen_item_struct*)case_item;
                const autogen_seq* str = NULL;

                autogen_it struct_it = INIT_ITERATOR;

                struct_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
                struct_it.obj.name = item_struct->seqname;
                struct_it.ver      = &item_struct->base.base.ver;
                struct_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;

                str = (const autogen_seq*)autogen_obj_find_in_list(&struct_it, &env->res->seq_list);
                if (str)
                {
                    fprintf(env->fout, "         %s  u%s_Default; \n", 
                        prop_get_string(&str->base, PROPERTY_ISIHDR_STRUCT_NAME),
                        str->base.name);
                }
            }
        }

        fprintf(env->fout, "    } %s_%s_%s_UNION;\n", env->res->base.name, seq->base.name, choice->base.refname);
        fprintf(env->fout, "\n");

        item = autogen_obj_find_next_in_list(&item_it);
    }
    /* If present, print feature flags */
    print_feature_flag(env, &lastFeatureFlag, NULL);
}


/*  End of file output_srvhdr.c  */
