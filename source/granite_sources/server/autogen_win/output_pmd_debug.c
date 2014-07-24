/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_pmd_debug.c
                ------------------
                SW Module






Project:          autogen

%name:            output_pmd_debug.c %
%version:         66 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Wed Nov 18 14:05:42 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the source code for the PMD debug output.

    When generated (define flag PMD_DEBUG or autogen option -opmd_debug), 
    the following text files will be generated with the PMD file:

    - pmd_debug_types_detailed.txt 
       Lists all genrates types in the module definition hierarchy with
       object ID's on every single item

    - pmd_debug_types.txt
       Lists all genrates types in the module definition hierarchy

    - pmd_debug_tree.txt
       Lists the whole expanded decode tree

    - pmd_debug_info.txt
       Lists all info objects in the PMD file, such has message/group info, info objects and
       environment variablees
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_object.h"
#include "autogen_prop.h"
#include "autogen_util.h"

#include "pmdconstants.h"
#include "pmd_compression2.h"
#include "pmd_stringpool.h"
#include "pmd_heap.h"

#include "output_pmd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL
#endif /* LOCAL */


LOCAL const char s_pmd_debug_indent[] = "                                       ";

LOCAL const char*   pmd_debug_get_indent(int indent);

LOCAL void          pmd_debug_env_vars_write(const pmd_env_var* env_vars, FILE* fdebug);
LOCAL void          pmd_debug_info_groups_write(const pmd_info_group* info_groups, FILE* fdebug);
LOCAL void          pmd_debug_entry_points_write(const pmd_entry_point* pmd_entry_points, FILE* fdebug);
LOCAL void          pmd_debug_msg_types_write(const pmd_msgtype* msg_types, FILE* fdebug);

LOCAL void          pmd_debug_objid_dump(FILE* fdebug, const pmd_managedobj* managedobj, int detailed);
LOCAL void          pmd_debug_tag_dump(FILE* fdebug, const pmd_tag* tag, const pmd_typ* type);
LOCAL void          pmd_debug_length_dump(FILE* fdebug, const pmd_len* length_obj, const pmd_typ* type, int detailed);
LOCAL void          pmd_debug_pres_dump(FILE* fdebug, const pmd_number_pres* pres, const pmd_typ* type, int indent, int detailed);

LOCAL void          pmd_debug_block_type_dump(FILE* fdebug, const pmd_block* block, int indent, int detailed);
LOCAL void          pmd_debug_choice_type_dump(pmd_env* env, FILE* fdebug, const pmd_choice* choice, int indent, int detailed);
LOCAL void          pmd_debug_filler_dyn_dump(FILE* fdebug, const pmd_filler_dyn* filler_dyn, int indent, int detailed);
LOCAL void          pmd_debug_filler_static_dump(FILE* fdebug, const pmd_filler_static* filler_static, int indent, int detailed);
LOCAL void          pmd_debug_msg_dump(FILE* fdebug, const pmd_msgtype* msg_type, const pmd_msg* msg, int indent);
LOCAL void          pmd_debug_msgent_dump(FILE* fdebug, const pmd_msgent* msgent, int indent);
LOCAL void          pmd_debug_msgtype_dump(FILE* fdebug, const pmd_msgtype* msgtype, const char* type_name, int indent);
LOCAL void          pmd_debug_trcgrp_dump(FILE* fdebug, const pmd_msggrp* msggrp, int indent);
LOCAL void          pmd_debug_number_dump(FILE* fdebug, const pmd_number* number, int indent, int detailed);
LOCAL void          pmd_debug_seq_dump(FILE* fdebug, const pmd_seq* seq, int indent, int detailed);
LOCAL void          pmd_debug_seq_of_dump(FILE* fdebug, const pmd_seq_of* seq, int indent, int detailed);
LOCAL void          pmd_debug_string_dump(FILE* fdebug, const pmd_string* str, int indent, int detailed);
LOCAL void          pmd_debug_type_dump(pmd_env* env, FILE* fdebug, const pmd_typ* type, int indent, int detailed);

LOCAL void          pmd_debug_tree_write_block_info(FILE* fdebug, const pmd_block* block, const char* name, const char* name_addition, int indent);
LOCAL void          pmd_debug_tree_write_choice_info(pmd_env* env, FILE* fdebug, const pmd_choice* choice, const char* name, const char* name_addition, int indent);
LOCAL void          pmd_debug_tree_write_filler_dyn_info(FILE* fdebug, const pmd_filler_dyn* filler_dyn, const char* name, const char* name_addition);
LOCAL void          pmd_debug_tree_write_filler_static_info(FILE* fdebug, const pmd_filler_static* filler_static, const char* name, const char* name_addition);
LOCAL void          pmd_debug_tree_write_number_info(FILE* fdebug, const pmd_number* number, const char* name, const char* name_addition);
LOCAL void          pmd_debug_tree_write_seq_info(pmd_env* env, FILE* fdebug, const pmd_seq* seq, const char* name, const char* name_addition, int indent);
LOCAL void          pmd_debug_tree_write_seq_of_info(pmd_env* env, FILE* fdebug, const pmd_seq_of* seq_of, const char* name, const char* name_addition, int indent);
LOCAL void          pmd_debug_tree_write_string_info(FILE* fdebug, const pmd_string* str, const char* name, const char* name_addition);
LOCAL void          pmd_debug_tree_write_type_info(pmd_env* env, FILE* fdebug, const pmd_typ* type, const char* name, const char* name_addition, int indent);

LOCAL void          pmd_debug_write_seq_info(FILE* fdebug, pmd_seq* seq, int indent);
LOCAL void          pmd_debug_write_module_info(pmd_env* env, FILE* fdebug, pmd_mod* module, int indent, int detailed);

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

void pmd_debug_dump_file(pmd_env* env)
{
    FILE* fdebug = NULL;
    char filename[100];
    const char* restriction = "";


    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC)
    {
        restriction = "pub_";
    }
    else if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED)
    {
        restriction = "res_";
    }
    printf("- Generating debug info\n");

    /* Generate debug file with type (detailed) info */
    sprintf(filename, "pmd_debug_types_detailed_%s0%d.txt", restriction, PMD_FILE_FORMAT);
    fdebug = fopen(filename, "wt");
    if (fdebug)
    {
        pmd_debug_write_module_info(env, fdebug, env->typ_root_module, 0, TRUE);

        fclose(fdebug);
    }

    /* Generate debug file with type info */
    sprintf(filename, "pmd_debug_types_%s0%d.txt", restriction, PMD_FILE_FORMAT);
    fdebug = fopen(filename, "wt");
    if (fdebug)
    {
        pmd_debug_write_module_info(env, fdebug, env->typ_root_module, 0, FALSE);

        fclose(fdebug);
    }

    /* Generate debug file with usage info */
    sprintf(filename, "pmd_debug_tree_%s0%d.txt", restriction, PMD_FILE_FORMAT);
    fdebug = fopen(filename, "wt");
    if (fdebug)
    {
        /* dump entry points */
        pmd_entry_point* entry_point = env->entry_points;
        while (entry_point)
        {
            unsigned int flags = entry_point->managedobj.flags;

            fprintf(fdebug, "--------------------------------------------------------------------\n");
            fprintf(fdebug, "Entry point: %s (0x%8.8x) ", entry_point->name, entry_point->id);

            /* flags */
            if (flags != 0)
            {
                int has_flags = FALSE;
                fprintf(fdebug, " flags:");

                if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "HAS_EMBEDDED_TRACES");
                    flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES;
                    has_flags = TRUE;
                }
                if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "HAS_EMBEDDED_PROTOCOL_MESSAGE");
                    flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE;
                    has_flags = TRUE;
                }
                if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "HAS_EMBEDDED_MEDIA_MODULE_MESSAGE");
                    flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE;
                    has_flags = TRUE;
                }
                if (flags)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "0x8.8X", flags);
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                        "pmd_debug_dump_file(): Unhandled flags 0x%8.8X in entry point %s", 
                        flags, entry_point->name);
                }
            }

            fprintf(fdebug, "\n--------------------------------------------------------------------\n");

            pmd_debug_tree_write_type_info(env, fdebug, entry_point->ref_type, "", "", 0);

            entry_point = entry_point->next;
        }

        /* dump entry point sub trees */
        entry_point = env->entry_point_subtrees;
        while (entry_point)
        {
            unsigned int flags = entry_point->managedobj.flags;
            
            fprintf(fdebug, "--------------------------------------------------------------------\n");
            fprintf(fdebug, "Entry point subtree: %s (0x%8.8x) ", entry_point->name, entry_point->id);

            /* flags */
            if (flags != 0)
            {
                int has_flags = FALSE;
                fprintf(fdebug, " flags:");

                if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "HAS_EMBEDDED_TRACES");
                    flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES;
                    has_flags = TRUE;
                }
                if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "HAS_EMBEDDED_PROTOCOL_MESSAGE");
                    flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE;
                    has_flags = TRUE;
                }
                if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "HAS_EMBEDDED_MEDIA_MODULE_MESSAGE");
                    flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE;
                    has_flags = TRUE;
                }
                if (flags & PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "HAS_INFO_GROUP_DEPENDENCY");
                    flags &= ~PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY;
                    has_flags = TRUE;
                }
                if (flags)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "0x8.8X", flags);
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                        "pmd_debug_dump_file(): Unhandled flags 0x%8.8X in entry point %s", 
                        flags, entry_point->name);
                }
            }

            if (entry_point->managedobj.flags & PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY)
            {
                const char* info_group_name = pmd_constant_lookup_info_type(((pmd_entry_point_subtree*)entry_point)->info_group_id);

                fprintf(fdebug, " INFO(%s)", info_group_name ? info_group_name : "Unknown");
            }

            fprintf(fdebug, "\n--------------------------------------------------------------------\n");

            if (((pmd_entry_point_subtree*)entry_point)->n_el > 0)
            {
                pmd_entry_point_subtree_el* el = ((pmd_entry_point_subtree*)entry_point)->el;

                while (el)
                {
                    char sz_name[255];

                    if (el->device_id == PMD_DEVICE_GENERAL)
                    {
#if (PMD_FILE_FORMAT >= 600)
                        sprintf(sz_name, "  %s(0x%8.8llX) device:GENERAL", el->namedobj.name, el->id);
#else
                        sprintf(sz_name, "  %s(0x%8.8X) device:GENERAL", el->namedobj.name, el->id);
#endif
                    }
                    else
                    {
                        const char* device_name = pmd_constant_lookup_device_logical_name(el->device_id);
                        if (device_name)
                        {
#if (PMD_FILE_FORMAT >= 600)
                            sprintf(sz_name, "  %s(0x%8.8llX) device:%s", el->namedobj.name, el->id, device_name);
#else
                            sprintf(sz_name, "  %s(0x%8.8X) device:%s", el->namedobj.name, el->id, device_name);
#endif
                        }
                        else
                        {
#if (PMD_FILE_FORMAT >= 600)
                            sprintf(sz_name, "  %s(0x%8.8llX) device:0x%2.2X", el->namedobj.name, el->id, el->device_id);
#else
                            sprintf(sz_name, "  %s(0x%8.8X) device:0x%2.2X", el->namedobj.name, el->id, el->device_id);
#endif
                        }
                    }

                    pmd_debug_tree_write_type_info(env, fdebug, el->type, sz_name, "", 1);

                    el = el->next;

                    fprintf(fdebug, "\n");
                }
            }

            entry_point = entry_point->next;
        }

        if (env->devices)
        {
            pmd_device* device = env->devices;
            while (device)
            {
                fprintf(fdebug, "\n");
                fprintf(fdebug, "=========================================================\n");
                fprintf(fdebug, "Device %s (%s) \n", device->logical_name, device->namedobj.name);
                fprintf(fdebug, "=========================================================\n");

                /* dump entry points */
                entry_point = device->entry_points;
                while (entry_point)
                {
                    unsigned int flags = entry_point->managedobj.flags;

                    fprintf(fdebug, "--------------------------------------------------------------------\n");
                    fprintf(fdebug, "Entry point: %s (0x%8.8x) ", entry_point->name, entry_point->id);

                    /* flags */
                    if (flags != 0)
                    {
                        int has_flags = FALSE;
                        fprintf(fdebug, " flags:");

                        if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "HAS_EMBEDDED_TRACES");
                            flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES;
                            has_flags = TRUE;
                        }
                        if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "HAS_EMBEDDED_PROTOCOL_MESSAGE");
                            flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE;
                            has_flags = TRUE;
                        }
                        if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "HAS_EMBEDDED_MEDIA_MODULE_MESSAGE");
                            flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE;
                            has_flags = TRUE;
                        }
                        if (flags)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "0x8.8X", flags);
                            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                                "pmd_debug_dump_file(): Unhandled flags 0x%8.8X in entry point %s", 
                                flags, entry_point->name);
                        }
                    }

                    fprintf(fdebug, "\n--------------------------------------------------------------------\n");

                    pmd_debug_tree_write_type_info(env, fdebug, entry_point->ref_type, "", "", 0);

                    entry_point = entry_point->next;
                }

                /* dump entry point sub trees */
                entry_point = device->entry_point_subtrees;
                while (entry_point)
                {
                    unsigned int flags = entry_point->managedobj.flags;
                    
                    fprintf(fdebug, "--------------------------------------------------------------------\n");
                    fprintf(fdebug, "Entry point subtree: %s (0x%8.8x) ", entry_point->name, entry_point->id);

                    /* flags */
                    if (flags != 0)
                    {
                        int has_flags = FALSE;
                        fprintf(fdebug, " flags:");

                        if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "HAS_EMBEDDED_TRACES");
                            flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES;
                            has_flags = TRUE;
                        }
                        if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "HAS_EMBEDDED_PROTOCOL_MESSAGE");
                            flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE;
                            has_flags = TRUE;
                        }
                        if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "HAS_EMBEDDED_MEDIA_MODULE_MESSAGE");
                            flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE;
                            has_flags = TRUE;
                        }
                        if (flags & PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "HAS_INFO_GROUP_DEPENDENCY");
                            flags &= ~PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY;
                            has_flags = TRUE;
                        }
                        if (flags)
                        {
                            if (has_flags) fprintf(fdebug, "|");
                            fprintf(fdebug, "0x8.8X", flags);
                            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                                "pmd_debug_dump_file(): Unhandled flags 0x%8.8X in entry point %s", 
                                flags, entry_point->name);
                        }
                    }

                    fprintf(fdebug, "\n--------------------------------------------------------------------\n");

                    if (((pmd_entry_point_subtree*)entry_point)->n_el > 0)
                    {
                        pmd_entry_point_subtree_el* el = ((pmd_entry_point_subtree*)entry_point)->el;

                        while (el)
                        {
                            char sz_name[255];
#if (PMD_FILE_FORMAT >= 600)
                            sprintf(sz_name, "%s (0x%8.8llX)", el->namedobj.name, el->id);
#else
                            sprintf(sz_name, "%s (0x%8.8X)", el->namedobj.name, el->id);
#endif

                            pmd_debug_tree_write_type_info(env, fdebug, el->type, sz_name, "", 1);

                            el = el->next;
                        }
                    }

                    entry_point = entry_point->next;
                }

                device = device->next;
            }
        }

        fclose(fdebug);
    }

    /* Generate debug file with info objects */
    sprintf(filename, "pmd_debug_info_%s0%d.txt", restriction, PMD_FILE_FORMAT);
    fdebug = fopen(filename, "wt");
    if (fdebug)
    {
        pmd_device* device = env->devices;

        fprintf(fdebug, "=========================================================\n");
        fprintf(fdebug, "Global definitions\n");
        fprintf(fdebug, "=========================================================\n");

        pmd_debug_env_vars_write(env->env_vars, fdebug);
        pmd_debug_info_groups_write(env->info_groups, fdebug);
        pmd_debug_msg_types_write(env->msgtypes, fdebug);
        pmd_debug_entry_points_write(env->entry_points, fdebug);
        pmd_debug_entry_points_write(env->entry_point_subtrees, fdebug);

        while (device)
        {
            fprintf(fdebug, "\n");
            fprintf(fdebug, "=========================================================\n");
            fprintf(fdebug, "Device %s (%s)", device->logical_name, device->namedobj.name);

            /* flags */
            if (device->namedobj.managedobj.flags != 0)
            {
                unsigned int flags = device->namedobj.managedobj.flags;
                int has_flags = FALSE;
                fprintf(fdebug, " flags:");

                if (flags & PMD_DEVICE_HAS_XTI_MASTER_DEVICE)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "HAS_XTI_MASTER_DEVICE");
                    flags &= ~PMD_DEVICE_HAS_XTI_MASTER_DEVICE;
                    has_flags = TRUE;
                }
                if (flags & PMD_DEVICE_IS_NOT_PHONE_DEVICE)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "IS_NOT_PHONE_DEVICE");
                    flags &= ~PMD_DEVICE_IS_NOT_PHONE_DEVICE;
                    has_flags = TRUE;
                }
                if (flags)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "0x%8.8X", flags);
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                        "pmd_debug_dump_file(): Unhandled flags 0x%8.8X in device %s", 
                        flags, device->namedobj.name);
                }
            }

            if (device->namedobj.managedobj.flags & PMD_DEVICE_HAS_XTI_MASTER_DEVICE)
            {
                const char* device_name = pmd_constant_lookup_device_logical_name(device->xti_master_device_id);
                if (device_name)
                {
                    fprintf(fdebug, " master:%s", device_name);
                }
                else
                {
                    fprintf(fdebug, " master:0x%2.2X", device->xti_master_device_id);
                }
            }

            fprintf(fdebug, "\n");
            fprintf(fdebug, "=========================================================\n");

            pmd_debug_env_vars_write(device->env_vars, fdebug);
            pmd_debug_info_groups_write(device->info_groups, fdebug);
            pmd_debug_msg_types_write(device->msgtypes, fdebug);
            pmd_debug_entry_points_write(device->entry_points, fdebug);

            device = device->next;
        }

        fclose(fdebug);
    }
}

/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

LOCAL const char* pmd_debug_get_indent(int indent)
{
    int index = 39 - 2*indent;

    return &s_pmd_debug_indent[(index < 0) ? 0 : index];
}

LOCAL void pmd_debug_objid_dump(FILE* fdebug, const pmd_managedobj* managedobj, int detailed)
{
    if (detailed)
    {
        fprintf(fdebug, "[id:%u]%s", managedobj->object_id, managedobj->stream_out ? "" : "[R]");
    }
}

LOCAL void pmd_debug_tag_dump(FILE* fdebug, const pmd_tag* tag, const pmd_typ* type)
{
    fprintf(fdebug, " tag:");

    if (tag->ref_type != NULL)
    {
        fprintf(fdebug, tag->ref_type->name);
    }
    else
    {
        fprintf(fdebug, "?");
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_tag_dump(): No tag reference type in type %s [id:%u]", 
            type->name, type->managedobj.object_id);
    }

    if (tag->rel_pos != 0 || tag->bit_pos != PMD_BIT_POSITION_NOT_SPECIFIED)
    {
        switch (tag->bit_pos)
        {
        case PMD_BIT_POSITION_AFTER:
            fprintf(fdebug, "(AFTER:%d)", tag->rel_pos);
            break;
        case PMD_BIT_POSITION_BEFORE:
            fprintf(fdebug, "(BEFORE:%d)", tag->rel_pos);
            break;
        case PMD_BIT_POSITION_NOT_SPECIFIED:
            fprintf(fdebug, "(UNDEF:%d)", tag->rel_pos);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_tag_dump(): Invalid tag combination bit_pos/rel_pos in type %s [id:%u]",
                type->name, type->managedobj.object_id);
            break;
        default:
            fprintf(fdebug, "(?:%d)", tag->rel_pos);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_tag_dump(): Unhandled tag bit position %d in type %s [id:%u]", 
                tag->bit_pos, type->name, type->managedobj.object_id);
        }
    }
}

LOCAL void pmd_debug_pres_dump(FILE* fdebug, const pmd_number_pres* pres, const pmd_typ* type, int indent, int detailed)
{
    switch(pres->managedobj.class_id)
    {
    case PMD_CLASS_NUMBER_PRESENTATION_CONSTANT:
        {
            pmd_number_pres_const* pres_const = (pmd_number_pres_const*)pres;

            fprintf(fdebug, "CONST(%s)", pres_const->text);
            pmd_debug_objid_dump(fdebug, &pres->managedobj, detailed);
            fprintf(fdebug, "\n");
        }
        break;
    case PMD_CLASS_NUMBER_PRESENTATION_INFO:
        {
            pmd_number_pres_info* pres_info = (pmd_number_pres_info*)pres;
            const char* info_group_name = pmd_constant_lookup_info_type(pres_info->info_group_id);

            fprintf(fdebug, "INFO(%s)", info_group_name ? info_group_name : "Unknown");
            pmd_debug_objid_dump(fdebug, &pres->managedobj, detailed);

            if (pres_info->device_id == PMD_DEVICE_GENERAL)
            {
                fprintf(fdebug, " device:GENERAL");
            }
            else
            {
                const char* device_name = pmd_constant_lookup_device_logical_name(pres_info->device_id);
                if (device_name)
                {
                    fprintf(fdebug, " device:%s", device_name);
                }
                else
                {
                    fprintf(fdebug, " device:%d", pres_info->device_id);
                }
            }

            if (pres_info->default_pres)
            {
                fprintf(fdebug, " def:");
                pmd_debug_pres_dump(fdebug, pres_info->default_pres, type, indent+1, detailed);
            }
            else
            {
                fprintf(fdebug, " def:None");
            }

            fprintf(fdebug, "\n");
        }
        break;
    case PMD_CLASS_NUMBER_PRESENTATION_TRANSFORMATION:
        {
            pmd_number_pres_trans* pres_trans = (pmd_number_pres_trans*)pres;

            fprintf(fdebug, "TRANSF(scale:%g,offset:%g", pres_trans->scale, pres_trans->offset);
            if (pres_trans->unit && pres_trans->unit[0])
            {
                fprintf(fdebug, ",unit:%s", pres_trans->unit);
            }
            fprintf(fdebug, ")");
            pmd_debug_objid_dump(fdebug, &pres->managedobj, detailed);
            fprintf(fdebug, "\n");
        }
        break;
    case PMD_CLASS_NUMBER_PRESENTATION_SIMPLE:
        {
            const pmd_number_pres_simple* pres_simple = (const pmd_number_pres_simple*)pres;

            fprintf(fdebug, "SIMPLE(");

            switch(pres_simple->type)
            {
            case PMD_VALUE_PRESENTATION_BIN:
                fprintf(fdebug, "BIN");
                break;
            case PMD_VALUE_PRESENTATION_HEX:
                fprintf(fdebug, "HEX");
                break;
            case PMD_VALUE_PRESENTATION_DEC:
                fprintf(fdebug, "DEC");
                break;
            default:
                fprintf(fdebug, "Unknown:%d", pres_simple->type);
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                    "pmd_debug_number_dump(): Unhandled value presentation %d in type %s [id:%u]", 
                    pres->managedobj.class_id, type->name, type->managedobj.object_id);
                break;
            }
            if (pres_simple->unit && pres_simple->unit[0])
            {
                fprintf(fdebug, ",unit:%s", pres_simple->unit);
            }
            fprintf(fdebug, ")");
            pmd_debug_objid_dump(fdebug, &pres->managedobj, detailed);
            fprintf(fdebug, "\n");
        }
        break;
    case PMD_CLASS_NUMBER_PRESENTATION_TIMESTAMP:
        {
            const pmd_number_pres_time* pres_time = (const pmd_number_pres_time*)pres;

            fprintf(fdebug, "TIMESTAMP(");

            switch(pres_time->type)
            {
            case PMD_TIMESTAMP_TYPE_ADSP:
                fprintf(fdebug, "ADSP");
                break;
            case PMD_TIMESTAMP_TYPE_CDMA_SYSTEM:
                fprintf(fdebug, "CDMA_SYSTEM");
                break;
            case PMD_TIMESTAMP_TYPE_CDSP:
                fprintf(fdebug, "CDSP");
                break;
            case PMD_TIMESTAMP_TYPE_DSP5:
                fprintf(fdebug, "DSP5");
                break;
            case PMD_TIMESTAMP_TYPE_GSM_FRAMES:
                fprintf(fdebug, "GSM_FRAMES");
                break;
            case PMD_TIMESTAMP_TYPE_MCU:
                fprintf(fdebug, "MCU");
                break;
            case PMD_TIMESTAMP_TYPE_STI_XTI:
                fprintf(fdebug, "STI/XTI");
                break;
            default:
                fprintf(fdebug, "Unknown:%d", pres_time->type);
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                    "pmd_debug_number_dump(): Unhandled timestamp presentation %d in type %s [id:%u]", 
                    pres_time->type, type->name, type->managedobj.object_id);
                break;
            }
            fprintf(fdebug, ")");
            pmd_debug_objid_dump(fdebug, &pres->managedobj, detailed);
            fprintf(fdebug, "\n");
        }
        break;

    case PMD_CLASS_NUMBER_PRESENTATION_CONDITION:
        {
            const pmd_number_pres_cond* pres_cond = (const pmd_number_pres_cond*)pres;

            if (pres->managedobj.flags & PMD_NUMBER_PRESENTATION_CONDITION_HAS_TAG)
            {
                fprintf(fdebug, "TAG:%s COND", pres_cond->tag_name);
            }
            else
            {
                fprintf(fdebug, "COND");
            }
            pmd_debug_objid_dump(fdebug, &pres->managedobj, detailed);

            if (pres_cond->default_pres)
            {
                fprintf(fdebug, " def:");
                pmd_debug_pres_dump(fdebug, pres_cond->default_pres, type, indent+1, detailed);
            }
            else
            {
                fprintf(fdebug, " def:None");
            }

            fprintf(fdebug, "\n");
        }
        break;

    default:
        {
            fprintf(fdebug, "Unknown(%d)", pres->managedobj.class_id);
            pmd_debug_objid_dump(fdebug, &pres->managedobj, detailed);
            fprintf(fdebug, "\n");

            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_number_dump(): Unhandled number presentation %d in type %s [id:%u]", 
                pres->managedobj.class_id, type->name, type->managedobj.object_id);
        }
    }

    /* now dump the condition elements */
    if (pres->managedobj.class_id == PMD_CLASS_NUMBER_PRESENTATION_CONDITION)
    {
        const pmd_number_pres_cond* pres_cond = (const pmd_number_pres_cond*)pres;
        const pmd_number_pres_cond_el* pres_cond_el = pres_cond->pres_cond_el;

        while (pres_cond_el)
        {
            switch (pres_cond_el->cond_el->managedobj.class_id)
            {
            case PMD_CLASS_CONDITION_ELEMENT_INTERVAL:
                {
                    const pmd_cond_el_int* cond_el_int = (const pmd_cond_el_int*)pres_cond_el->cond_el;
                    if (cond_el_int->cond_el.managedobj.flags & PMD_CONDITION_ELEMENT_HAS_SINGLE_VALUE_INTERVAL)
                    {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(fdebug, "%s[0x%2.2llX]", pmd_debug_get_indent(indent), cond_el_int->from);
#else
                        fprintf(fdebug, "%s[0x%2.2X]", pmd_debug_get_indent(indent), cond_el_int->from);
#endif
                    }
                    else
                    {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(fdebug, "%s[0x%2.2llX-0x%2.2llX]", pmd_debug_get_indent(indent), cond_el_int->from, cond_el_int->to);
#else
                        fprintf(fdebug, "%s[0x%2.2X-0x%2.2X]", pmd_debug_get_indent(indent), cond_el_int->from, cond_el_int->to);
#endif
                    }
                }
                break;
            case PMD_CLASS_CONDITION_ELEMENT_BITSTATE:
                {
                    const pmd_cond_el_bit* cond_el_bit = (const pmd_cond_el_bit*)pres_cond_el->cond_el;

                    fprintf(fdebug, "%s[%s]", pmd_debug_get_indent(indent), cond_el_bit->bitstate);
                }
                break;
            default:
                {
                    fprintf(fdebug, "%s[Unknown(%d)]", pmd_debug_get_indent(indent), 
                        pres_cond_el->cond_el->managedobj.class_id);
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                        "pmd_debug_number_dump(): Unhandled condition element %d in type %s [id:%u]", 
                        pres_cond_el->cond_el->managedobj.class_id,
                        type->name, type->managedobj.object_id);
                }
            }
            pmd_debug_objid_dump(fdebug, &pres_cond_el->cond_el->managedobj, detailed);

            fprintf(fdebug, ":");
            pmd_debug_pres_dump(fdebug, pres_cond_el->pres, type, indent, detailed);

            pres_cond_el = pres_cond_el->next;
        }
    }
}

LOCAL void pmd_debug_length_dump(FILE* fdebug, const pmd_len* length_obj, const pmd_typ* type, int detailed)
{
    char ref_name[100] = "?";
    char id_str[20] = "";
    if (detailed && length_obj->tag.ref_type)
    {
        sprintf(id_str, "[id:%d]", length_obj->tag.ref_type->managedobj.object_id);
    }
    if (length_obj->tag.ref_type)
    {
        strcpy(ref_name, length_obj->tag.ref_type->name);
    }
    strcat(ref_name, id_str);

    switch (length_obj->alg)
    {
    case PMD_LENGTH_ALGORITHM_AS_MANY_AS_POSSIBLE:
        if (type->managedobj.class_id == PMD_CLASS_STRING_TYPE)
        {
            fprintf(fdebug, " alg:ALAP");
        }
        else
        {
            fprintf(fdebug, " alg:AMAP");
        }
        break;
    case PMD_LENGTH_ALGORITHM_UNKNOWN:
        fprintf(fdebug, " alg:Unknown");
        break;
    case PMD_LENGTH_ALGORITHM_FIXEDLENGTH:
        fprintf(fdebug, " len:%d", length_obj->length);
        break;
    case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MINUS_N:
        fprintf(fdebug, " len:%d-%s", length_obj->length, ref_name);
        break;
    case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N:
        fprintf(fdebug, " len:%d*%s", length_obj->length, ref_name);
        break;
    case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N_MINUS_1:
        fprintf(fdebug, " len:%d*%s-1", length_obj->length, ref_name);
        break;
    case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N_PLUS_1:
        fprintf(fdebug, " len:%d*%s+1", length_obj->length, ref_name);
        break;
    case PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH:
        fprintf(fdebug, " len:%s/%d", ref_name, length_obj->length);
        break;
    case PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH_ROUNDUP:
        fprintf(fdebug, " len:~%s/%d", ref_name, length_obj->length);
        break;
    case PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH:
        if (length_obj->length > 0)
        {
            fprintf(fdebug, " len:%s+%d", ref_name, length_obj->length);
        }
        else if (length_obj->length < 0)
        {
            fprintf(fdebug, " len:%s%d", ref_name, length_obj->length);
        }
        else
        {
            fprintf(fdebug, " len:%s", ref_name);
        }
        break;
    case PMD_LENGTH_ALGORITHM_OPTIONAL:
        fprintf(fdebug, " len:OPTIONAL");
        break;
    case PMD_LENGTH_ALGORITHM_NOT_SPECIFIED:
        if (type->managedobj.class_id == PMD_CLASS_STRING_TYPE)
        {
            fprintf(fdebug, " len:0-TERMINATED");
        }
        else
        {
            fprintf(fdebug, " len:NOT_SPECIFIED!");
        }
        break;
    default:
        fprintf(fdebug, "Unknown(%d)", length_obj->alg);
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_length_dump(): Unhandled length algorithm %d in type [id:%u]", 
            length_obj->alg, type->name, type->managedobj.object_id);
        break;
    }

    /* check length */
    if (length_obj->alg != PMD_LENGTH_ALGORITHM_AS_MANY_AS_POSSIBLE &&
        length_obj->alg != PMD_LENGTH_ALGORITHM_NOT_SPECIFIED &&
        length_obj->alg != PMD_LENGTH_ALGORITHM_OPTIONAL &&
        length_obj->alg != PMD_LENGTH_ALGORITHM_FIXEDLENGTH &&
        length_obj->tag.ref_type == NULL)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_length_dump(): Invalid length object in type [id:%u]", type->managedobj.object_id);
    }

}

LOCAL void pmd_debug_tree_write_seq_info(pmd_env* env, FILE* fdebug, const pmd_seq* seq, const char* name, const char * name_addition, int indent)
{
    pmd_seq_el* el = NULL;

    if (!seq) return;
    
    fprintf(fdebug, "%s%s seq:%s%s\n", name, name_addition, seq->constructed.type.name,
        (seq->constructed.type.managedobj.stream_out == FALSE) ? "[R]" : "");

    indent++;

    /* write the sequence elements */
    el = seq->seq_el;
    while (el)
    {
        fprintf(fdebug, pmd_debug_get_indent(indent));
        pmd_debug_tree_write_type_info(env, fdebug, el->type, el->namedobj.name, "", indent);

        el = el->next;
    }
}

LOCAL void pmd_debug_tree_write_block_info(FILE* fdebug, const pmd_block* block, 
                                           const char* name, const char* name_addition, int indent)
{
    const char* alg = pmd_constant_lookup_block_algorithm(block->algorithm);
    fprintf(fdebug, "%s%s blk:%s%s", name, name_addition, block->constructed.type.name,
        (block->constructed.type.managedobj.stream_out == FALSE) ? "[R]" : "");

    indent;


    /* alg */
    fprintf(fdebug, " typ:");
    if (alg && block->algorithm == PMD_BLOCK_ALGORITHM_ENTRYPOINT)
    {
        fprintf(fdebug, alg);

        fprintf(fdebug, " ep:%s", block->ep_name);
        fprintf(fdebug, " ep_id:0x%8.8X", block->ep_id);

        if (block->ep_device_id == PMD_DEVICE_GENERAL)
        {
            fprintf(fdebug, " ep_device:GENERAL");
        }
        else
        {
            const char* device_name = pmd_constant_lookup_device_logical_name(block->ep_device_id);
            if (device_name)
            {
                fprintf(fdebug, " ep_device:%s", device_name);
            }
            else
            {
                fprintf(fdebug, " ep_device:%d", block->ep_device_id);
            }
        }
    }
    else if (alg)
    {
        fprintf(fdebug, alg);

        if (block->data1)
        {
            fprintf(fdebug, "[%s", block->data1);
            if (block->data2)
            {
                fprintf(fdebug, ":%s", block->data2);
            }
            fprintf(fdebug, "]");
        }

        fprintf(fdebug, " id:0x%8.8X", block->data_int);
    }
    else
    {
        fprintf(fdebug, "Unknown(%d)", block->algorithm);
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_block_type_dump(): Unhandled block algorithm %d in type %s [id:%u]",
            block->algorithm, block->constructed.type.name, 
            block->constructed.type.managedobj.object_id);
    }

    /* length */
    pmd_debug_length_dump(fdebug, &block->constructed.length_obj, &block->constructed.type, FALSE);

    fprintf(fdebug, "\n");
}

LOCAL void pmd_debug_tree_write_choice_info(pmd_env* env, FILE* fdebug, const pmd_choice* choice, const char* name, const char* name_addition, int indent)
{
    const pmd_choice_el* choice_el = choice->choice_el;

    fprintf(fdebug, "%s%s sel:%s%s", name, name_addition,
        choice->constructed.type.name,
        (choice->constructed.type.managedobj.stream_out == FALSE) ? "[R]" : "");

    pmd_debug_tag_dump(fdebug, &choice->tag, &choice->constructed.type);

    if (choice->constructed.type.managedobj.flags & PMD_CHOICE_ENTRY_POINT)
    {
        fprintf(fdebug, " %s", choice->entry_point_name);
        fprintf(fdebug, " ep_id:0x%8.8X", choice->entry_point_id);
    }

    /* Device id */
#if PMD_FILE_FORMAT >= 501
    if (choice->device_id == PMD_DEVICE_GENERAL)
    {
        fprintf(fdebug, " device:GENERAL");
    }
    else
    {
        const char* device_name = pmd_constant_lookup_device_logical_name(choice->device_id);
        if (device_name)
        {
            fprintf(fdebug, " device:%s", device_name);
        }
        else
        {
            fprintf(fdebug, " device:%d", choice->device_id);
        }
    }
#endif

    fprintf(fdebug, "\n");

    indent++;

    if (choice->constructed.type.managedobj.flags & PMD_CHOICE_ENTRY_POINT)
    {
        pmd_entry_point_subtree* ep = (pmd_entry_point_subtree*)pmd_entry_point_find(env, PMD_DEVICE_GENERAL, choice->entry_point_id, TRUE);
        if (ep)
        {
            if (ep->n_el > 0)
            {
                pmd_entry_point_subtree_el* el = ep->el;
                while (el)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(fdebug, "%s%s[0x%2.2llX]\n", pmd_debug_get_indent(indent), el->namedobj.name, el->id);
#else
                    fprintf(fdebug, "%s%s[0x%2.2X]\n", pmd_debug_get_indent(indent), el->namedobj.name, el->id);
#endif

                    el = el->next;
                }
            }
        }
        if (choice->default_type)
        {
            fprintf(fdebug, pmd_debug_get_indent(indent));
            pmd_debug_tree_write_type_info(env, fdebug, choice->default_type, "(Default)", "", indent);
        }
    }
    else
    {
        while (choice_el)
        {
            char str_addition[50] = "";

            if (choice_el->cond_el->managedobj.class_id == PMD_CLASS_CONDITION_ELEMENT_INTERVAL)
            {
#if (PMD_FILE_FORMAT >= 600)
                sprintf(str_addition, "[0x%2.2llX]", ((pmd_cond_el_int*)choice_el->cond_el)->from);
#else
                sprintf(str_addition, "[0x%2.2X]", ((pmd_cond_el_int*)choice_el->cond_el)->from);
#endif
            }
            else if (choice_el->cond_el->managedobj.class_id == PMD_CLASS_CONDITION_ELEMENT_BITSTATE)
            {
                sprintf(str_addition, "[%s]", ((pmd_cond_el_bit*)choice_el->cond_el)->bitstate);
            }
            else
            {
                sprintf(str_addition, "[???]");
            }

            fprintf(fdebug, pmd_debug_get_indent(indent));
            pmd_debug_tree_write_type_info(env, fdebug, choice_el->type, choice_el->namedobj.name, str_addition, indent);

            choice_el = choice_el->next;
        }
        if (choice->default_type)
        {
            fprintf(fdebug, pmd_debug_get_indent(indent));
            pmd_debug_tree_write_type_info(env, fdebug, choice->default_type, "(Default)", "", indent);
        }
    }
}

LOCAL void pmd_debug_tree_write_seq_of_info(pmd_env* env, FILE* fdebug, const pmd_seq_of* seq_of, const char* name, const char* name_addition, int indent)
{
    if (!seq_of) return;

    fprintf(fdebug, "%s%s vec:%s%s", name, name_addition, seq_of->constructed.type.name,
        (seq_of->constructed.type.managedobj.stream_out == FALSE) ? "[R]" : "");

    /* length */
    pmd_debug_length_dump(fdebug, &seq_of->constructed.length_obj, &seq_of->constructed.type, FALSE);

    /* type */
    fprintf(fdebug, " type:%s", seq_of->type->name);

    fprintf(fdebug, "\n");

    indent++;

    if (seq_of->type)
    {
        fprintf(fdebug, pmd_debug_get_indent(indent));
        pmd_debug_tree_write_type_info(env, fdebug, seq_of->type, name, "", indent);
    }
}

LOCAL void pmd_debug_tree_write_filler_dyn_info(FILE* fdebug, const pmd_filler_dyn* filler_dyn, 
                                                const char* name, const char* name_addition)
{
    if (!filler_dyn) return;

    fprintf(fdebug, "%s%s fil:%s%s\n", name, name_addition, filler_dyn->filler.type.name,
        (filler_dyn->filler.type.managedobj.stream_out == FALSE) ? "[R]" : "");
}

LOCAL void pmd_debug_tree_write_filler_static_info(FILE* fdebug, const pmd_filler_static* filler_static, 
                                                   const char* name, const char* name_addition)
{
    if (!filler_static) return;

    fprintf(fdebug, "%s%s fil:%s%s\n", name, name_addition, filler_static->filler.type.name,
        (filler_static->filler.type.managedobj.stream_out == FALSE) ? "[R]" : "");
}

LOCAL void pmd_debug_tree_write_number_info(FILE* fdebug, const pmd_number* number, 
                                            const char* name, const char* name_addition)
{
    if (!number) return;

    fprintf(fdebug, "%s%s num:%s%s", name, name_addition, number->primitive.type.name,
        (number->primitive.type.managedobj.stream_out == FALSE) ? "[R]" : "");

    /* size */
    fprintf(fdebug, " siz:%d", number->length);

    /* order */
    fprintf(fdebug, " order:%s", (number->primitive.type.managedobj.flags & PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN) ? "LE" : "BE");

    /* default value */
    if (number->primitive.type.managedobj.flags & PMD_NUMBER_HAS_DEFAULT_VALUE)
    {
        fprintf(fdebug, " def:%s", number->default_value_str);
    }

    /* special type */
    if (pmd_constant_lookup_number_special_type(number->primitive.special_type))
    {
        fprintf(fdebug, " spec:%s", pmd_constant_lookup_number_special_type(number->primitive.special_type));
    }

    fprintf(fdebug, "\n");
}

LOCAL void pmd_debug_tree_write_string_info(FILE* fdebug, const pmd_string* str, 
                                            const char* name, const char* name_addition)
{
    if (!str) return;

    fprintf(fdebug, "%s%s str:%s%s\n", name, name_addition, str->primitive.type.name,
        (str->primitive.type.managedobj.stream_out == FALSE) ? "[R]" : "");
}

LOCAL void pmd_debug_tree_write_type_info(pmd_env* env, FILE* fdebug, const pmd_typ* type, 
                                          const char* name, const char* name_addition, int indent)
{
    if (!type) return;

    switch (type->managedobj.class_id)
    {
    case PMD_CLASS_BLOCK:
        pmd_debug_tree_write_block_info(fdebug, (const pmd_block*)type, name, name_addition, indent);
        break;
    case PMD_CLASS_CHOICE:
        pmd_debug_tree_write_choice_info(env, fdebug, (const pmd_choice*)type, name, name_addition, indent);
        break;
    case PMD_CLASS_FILLER_TYPE_DYNAMIC:
        pmd_debug_tree_write_filler_dyn_info(fdebug, (const pmd_filler_dyn*)type, name, name_addition);
        break;
    case PMD_CLASS_FILLER_TYPE_STATIC:
        pmd_debug_tree_write_filler_static_info(fdebug, (const pmd_filler_static*)type, name, name_addition);
        break;
    case PMD_CLASS_NUMBER_TYPE:
        pmd_debug_tree_write_number_info(fdebug, (const pmd_number*)type, name, name_addition);
        break;
    case PMD_CLASS_SEQUENCE:
        pmd_debug_tree_write_seq_info(env, fdebug, (const pmd_seq*)type, name, name_addition, indent);
        break;
    case PMD_CLASS_SEQUENCE_OF:
        pmd_debug_tree_write_seq_of_info(env, fdebug, (const pmd_seq_of*)type, name, name_addition, indent);
        break;
    case PMD_CLASS_STRING_TYPE:
        pmd_debug_tree_write_string_info(fdebug, (const pmd_string*)type, name, name_addition);
        break;
    default:
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_tree_write_type_info(): Unhandled type %d (%s) [id:%u]", 
            type->managedobj.class_id, type->name, type->managedobj.object_id);
        break;
    }
}

LOCAL void pmd_debug_write_module_info(pmd_env* env, FILE* fdebug, pmd_mod* mod, int indent, int detailed)
{
    pmd_typ* type;

    if (!mod) return;

    fprintf(fdebug, "%smod:%s\n", pmd_debug_get_indent(indent), mod->name);
    fprintf(fdebug, "%s-------------------------------------------------------------------\n", pmd_debug_get_indent(indent));

    /* write the module sequence */
    if (mod->seq)
    {
        pmd_debug_seq_dump(fdebug, mod->seq, indent, detailed);
    }

    /* write the module types */
    type = mod->type;
    while (type)
    {
        pmd_debug_type_dump(env, fdebug, type, indent+1, detailed);

        type = type->next;
    }

    /* write the child module */
    if (mod->child)
    {
        pmd_debug_write_module_info(env, fdebug, mod->child, indent+1, detailed);
    }

    /* write the nested module */
    if (mod->next)
    {
        pmd_debug_write_module_info(env, fdebug, mod->next, indent, detailed);
    }
}

LOCAL void pmd_debug_filler_dyn_dump(FILE* fdebug, const pmd_filler_dyn* filler_dyn, int indent, int detailed)
{
    unsigned int flags = filler_dyn->filler.type.managedobj.flags;

    fprintf(fdebug, "%sfil:%s", pmd_debug_get_indent(indent), filler_dyn->filler.type.name);
    pmd_debug_objid_dump(fdebug, &filler_dyn->filler.type.managedobj, detailed);

    /* size */
    fprintf(fdebug, " siz:%d", filler_dyn->filler.n_bits);

    /* alignment */
    fprintf(fdebug, " align:");

    switch (filler_dyn->alignment)
    {
    case PMD_ALIGNMENT_MODULUS:
        fprintf(fdebug, "MODULUS");
        break;
    case PMD_ALIGNMENT_MODULUS_MINUS_24:
        fprintf(fdebug, "MODULUS-24");
        break;
    case PMD_ALIGNMENT_MODULUS_MINUS_8:
        fprintf(fdebug, "MODULUS-8");
        break;
    default:
        fprintf(fdebug, "Unknown(%d)", filler_dyn->alignment);
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_filler_dyn_dump(): Unhandled alignment %d in type %s [id:%u]", 
            filler_dyn->alignment, filler_dyn->filler.type.name,
            filler_dyn->filler.type.managedobj.object_id);
        break;
    }

    /* sequence (ref_type) */
    if (filler_dyn->ref_type)
    {
        fprintf(fdebug, " seq:%s", filler_dyn->ref_type->name);
    }
    else
    {
        fprintf(fdebug, " seq:Undefined");
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_filler_dyn_dump(): Reference sequence undefined in type %s [id:%u]", 
            filler_dyn->filler.type.name, filler_dyn->filler.type.managedobj.object_id);
    }

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x%8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_filler_dyn_dump(): Unhandled flags 0x%8.8X in type %s [id:%u]", 
                flags, filler_dyn->filler.type.name, filler_dyn->filler.type.managedobj.object_id);
        }
    }

    fprintf(fdebug, "\n");
}

LOCAL void pmd_debug_filler_static_dump(FILE* fdebug, const pmd_filler_static* filler_static, int indent, int detailed)
{
    unsigned int flags = filler_static->filler.type.managedobj.flags;

    fprintf(fdebug, "%sfil:%s", pmd_debug_get_indent(indent), filler_static->filler.type.name);
    pmd_debug_objid_dump(fdebug, &filler_static->filler.type.managedobj, detailed);

    /* size */
    fprintf(fdebug, " siz:%d", filler_static->filler.n_bits);

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x%8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_filler_static_dump(): Unhandled flags 0x%8.8X in type %s [id:%u]", 
                flags, filler_static->filler.type.name, 
                filler_static->filler.type.managedobj.object_id);
        }
    }

    fprintf(fdebug, "\n");
}

LOCAL void pmd_debug_number_dump(FILE* fdebug, const pmd_number* number, int indent, int detailed)
{
    unsigned int flags = number->primitive.type.managedobj.flags;

    fprintf(fdebug, "%snum:%s", pmd_debug_get_indent(indent), number->primitive.type.name);
    pmd_debug_objid_dump(fdebug, &number->primitive.type.managedobj, detailed);

    /* size */
    fprintf(fdebug, " siz:%d", number->length);

    /* order */
    fprintf(fdebug, " order:%s", (number->primitive.type.managedobj.flags & PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN) ? "LE" : "BE");

    /* default value */
    if (flags & PMD_NUMBER_HAS_DEFAULT_VALUE)
    {
        fprintf(fdebug, " def:%s", number->default_value_str);
    }

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags & PMD_NUMBER_HAS_DEFAULT_VALUE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "HAS_DEFAULT_VALUE");
            flags &= ~PMD_NUMBER_HAS_DEFAULT_VALUE;
            has_flags = TRUE;
        }
        if (flags & PMD_NUMBER_IS_SIGNED)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_SIGNED");
            flags &= ~PMD_NUMBER_IS_SIGNED;
            has_flags = TRUE;
        }
        if (flags & PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "DATA_ORDER_LITTLE_ENDIAN");
            flags &= ~PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN;
            has_flags = TRUE;
        }
        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x%8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_number_dump(): Unhandled flags 0x%8.8X in type %s [id:%u]", 
                flags, number->primitive.type.name, number->primitive.type.managedobj.object_id);
        }
    }

    /* special type */
    if (pmd_constant_lookup_number_special_type(number->primitive.special_type))
    {
        fprintf(fdebug, " spec:%s", pmd_constant_lookup_number_special_type(number->primitive.special_type));
    }
    else
    {
        fprintf(fdebug, " spec:Unknown!!!");
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_number_dump(): Unhandled number special type %d in type %s [id:%u]", 
            number->primitive.special_type, number->primitive.type.name, 
            number->primitive.type.managedobj.object_id);
    }

    /* presentation */
    fprintf(fdebug, " pres:");
    pmd_debug_pres_dump(fdebug, number->pres, &number->primitive.type, indent+1, detailed);
}

LOCAL void pmd_debug_string_dump(FILE* fdebug, const pmd_string* str, int indent, int detailed)
{
    unsigned int flags = str->primitive.type.managedobj.flags;

    fprintf(fdebug, "%sstr:%s", pmd_debug_get_indent(indent), str->primitive.type.name);
    pmd_debug_objid_dump(fdebug, &str->primitive.type.managedobj, detailed);

    /* type */
    fprintf(fdebug, " typ:");
    if (pmd_constant_lookup_character_type(str->char_type))
    {
        fprintf(fdebug, pmd_constant_lookup_character_type(str->char_type));
    }
    else
    {
        fprintf(fdebug, "Unknown(%d)", str->char_type);
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_string_dump(): Unhandled character type %d in type %s [id:%u]", 
            str->char_type, str->primitive.type.name, str->primitive.type.managedobj.object_id);
    }

    /* length */
    pmd_debug_length_dump(fdebug, &str->length_obj, &str->primitive.type, detailed);

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags & PMD_STRING_IS_NULL_TERMINATED)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_NULL_TERMINATED");
            flags &= ~PMD_STRING_IS_NULL_TERMINATED;
            has_flags = TRUE;
        }
        if (flags & PMD_STRING_LENGTH_IN_BYTES)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "LENGTH_IN_BYTES");
            flags &= ~PMD_STRING_LENGTH_IN_BYTES;
            has_flags = TRUE;
        }
        if (flags & PMD_STRING_IS_FTD_DATA)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_FTD_DATA");
            flags &= ~PMD_STRING_IS_FTD_DATA;
            has_flags = TRUE;
        }
        if (flags & PMD_STRING_HAS_BCD_MAP)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "HAS_BCD_MAP");
            flags &= ~PMD_STRING_HAS_BCD_MAP;
            has_flags = TRUE;
        }
        if (flags & PMD_STRING_IS_UNFORMATTED)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "STRING_IS_UNFORMATTED");
            flags &= ~PMD_STRING_IS_UNFORMATTED;
            has_flags = TRUE;
        }
        if (flags & PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "DATA_ORDER_LITTLE_ENDIAN");
            flags &= ~PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN;
            has_flags = TRUE;
        }
        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x%8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_string_dump(): Unhandled flags: 0x%8.8X [id:%u]", 
                flags, str->primitive.type.managedobj.object_id);
        }
    }

    fprintf(fdebug, ")\n");
}

LOCAL void pmd_debug_seq_dump(FILE* fdebug, const pmd_seq* seq, int indent, int detailed)
{
    unsigned int flags = seq->constructed.type.managedobj.flags;

    fprintf(fdebug, "%sseq:%s", pmd_debug_get_indent(indent), seq->constructed.type.name);
    pmd_debug_objid_dump(fdebug, &seq->constructed.type.managedobj, detailed);

    /* type */
    {
        fprintf(fdebug, " typ:");

        if (pmd_constant_lookup_sequence_type(seq->seq_type))
        {
            fprintf(fdebug, pmd_constant_lookup_sequence_type(seq->seq_type));
            if (!strcmp(pmd_constant_lookup_sequence_type(seq->seq_type), "MSG") && (seq->org_seq->base.related_obj.obj_list))/* Simple output of related message */
            {
                fprintf(fdebug, " rel:%s", seq->org_seq->base.related_obj.obj_list[0]->name);
            }
        }
        else
        {
            fprintf(fdebug, "Unknown(%d)", seq->seq_type);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_seq_dump(): Unhandled sequence type %d in type %s [id:%u]", 
                seq->seq_type, seq->constructed.type.name, seq->constructed.type.managedobj.object_id);
        }
    }

    /* length */
    pmd_debug_length_dump(fdebug, &seq->constructed.length_obj, &seq->constructed.type, detailed);

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x%8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_seq_dump(): Unhandled flags 0x%8.8X in type %s [id:%u]", 
                flags, seq->constructed.type.name, seq->constructed.type.managedobj.object_id);
        }
    }

    fprintf(fdebug, "\n");
}

LOCAL void pmd_debug_block_type_dump(FILE* fdebug, const pmd_block* block, int indent, int detailed)
{
    const char* alg = pmd_constant_lookup_block_algorithm(block->algorithm);
    unsigned int flags = block->constructed.type.managedobj.flags;

    fprintf(fdebug, "%sblk:%s", pmd_debug_get_indent(indent), block->constructed.type.name);
    pmd_debug_objid_dump(fdebug, &block->constructed.type.managedobj, detailed);

    /* alg */
    fprintf(fdebug, " typ:");
    if (alg)
    {
        fprintf(fdebug, alg);

        if (block->data1)
        {
            fprintf(fdebug, "[%s", block->data1);
            if (block->data2)
            {
                fprintf(fdebug, ":%s", block->data2);
            }
            fprintf(fdebug, "]");
        }
    }
    else
    {
        fprintf(fdebug, "Unknown(%d)", block->algorithm);
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_block_type_dump(): Unhandled block algorithm %d in type %s [id:%u]",
            block->algorithm, block->constructed.type.name, 
            block->constructed.type.managedobj.object_id);
    }

    /* length */
    pmd_debug_length_dump(fdebug, &block->constructed.length_obj, &block->constructed.type, detailed);

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (block->algorithm == PMD_BLOCK_ALGORITHM_EXTERNAL)
        {
            if (flags & PMD_BLOCK_EXT_DECODER_SEND_WHOLE_EMBEDDED_MESSAGE)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "SEND_WHOLE_EMBEDDED_MESSAGE");
                flags &= ~PMD_BLOCK_EXT_DECODER_SEND_WHOLE_EMBEDDED_MESSAGE;
                has_flags = TRUE;
            }
            if (flags & PMD_BLOCK_EXT_DECODER_SKIP_IDENTIFIER)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "SKIP_IDENTIFIER");
                flags &= ~PMD_BLOCK_EXT_DECODER_SKIP_IDENTIFIER;
                has_flags = TRUE;
            }
            if (flags & PMD_BLOCK_EXT_DECODER_SKIP_TRACE_NAME)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "SKIP_TRACE_NAME");
                flags &= ~PMD_BLOCK_EXT_DECODER_SKIP_TRACE_NAME;
                has_flags = TRUE;
            }
            if (flags & PMD_BLOCK_EXT_DECODER_SEND_FROM_TRACE_START)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "SEND_FROM_TRACE_START");
                flags &= ~PMD_BLOCK_EXT_DECODER_SEND_FROM_TRACE_START;
                has_flags = TRUE;
            }
        }
        else
        {
            if (flags & PMD_BLOCK_PN_MSG_SKIP_TRACE_NAME)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "SKIP_TRACE_NAME");
                flags &= ~PMD_BLOCK_PN_MSG_SKIP_TRACE_NAME;
                has_flags = TRUE;
            }
        }

        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x%8.8X");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_block_dump(): Unhandled flags 0x%8.8X in type %s [id:%u]", 
                flags, block->constructed.type.name, block->constructed.type.managedobj.object_id);
        }
    }

    fprintf(fdebug, "\n");
}

LOCAL void pmd_debug_seq_of_type_dump(FILE* fdebug, const pmd_seq_of* seq_of, int indent, int detailed)
{
    unsigned int flags = seq_of->constructed.type.managedobj.flags;

    fprintf(fdebug, "%svec:%s", pmd_debug_get_indent(indent), seq_of->constructed.type.name);
    pmd_debug_objid_dump(fdebug, &seq_of->constructed.type.managedobj, detailed);

    /* length */
    pmd_debug_length_dump(fdebug, &seq_of->constructed.length_obj, &seq_of->constructed.type, detailed);

    /* type */
    fprintf(fdebug, " type:%s", seq_of->type->name);
    pmd_debug_objid_dump(fdebug, &seq_of->type->managedobj, detailed);

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags & PMD_SEQUENCE_OF_SUB_BLOCKS)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "SUB_BLOCKS");
            flags &= ~PMD_SEQUENCE_OF_SUB_BLOCKS;
            has_flags = TRUE;
        }
        if (flags & PMD_SEQUENCE_OF_INCLUDE_INFO_DATA)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "INCLUDE_INFO_DATA");
            flags &= ~PMD_SEQUENCE_OF_INCLUDE_INFO_DATA;
            has_flags = TRUE;
        }
        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x%8.8X)", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_seq_of_block_dump(): Unhandled flags 0x%8.8X in type %s [id:%u]", 
                flags, seq_of->constructed.type.name, 
                seq_of->constructed.type.managedobj.object_id);
        }
    }

    fprintf(fdebug, "\n");
}

LOCAL void pmd_debug_choice_type_dump(pmd_env* env, FILE* fdebug, const pmd_choice* choice, int indent, int detailed)
{
    const pmd_choice_el* choice_el = choice->choice_el;
    unsigned int flags = choice->constructed.type.managedobj.flags;
    unsigned int flags_ep = flags & ~PMD_CHOICE_ENTRY_POINT;


    fprintf(fdebug, "%ssel:%s", pmd_debug_get_indent(indent), choice->constructed.type.name);
    pmd_debug_objid_dump(fdebug, &choice->constructed.type.managedobj, detailed);

    /* tag */
    pmd_debug_tag_dump(fdebug, &choice->tag, &choice->constructed.type);

    /* Entry point ID */
    if (flags & PMD_CHOICE_ENTRY_POINT)
    {
        fprintf(fdebug, " entry_point:%s", choice->entry_point_name ? choice->entry_point_name : "(null)");
    }

    /* flags */
    if (flags_ep != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags_ep)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x%8.8X", flags_ep);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_choice_type_dump(): Unhandled flags 0x%8.8X in type %s [id:%u]", 
                flags_ep, choice->constructed.type.name, choice->constructed.type.managedobj.object_id);
        }
    }

    /* device id */
#if PMD_FILE_FORMAT >= 501
    if (choice->device_id == PMD_DEVICE_GENERAL)
    {
        fprintf(fdebug, " device:GENERAL");
    }
    else
    {
        const char* device_name = pmd_constant_lookup_device_logical_name(choice->device_id);
        if (device_name)
        {
            fprintf(fdebug, " device:%s", device_name);
        }
        else
        {
            fprintf(fdebug, " device:%d", choice->device_id);
        }
    }
#endif

    fprintf(fdebug, "\n");

    indent++;


    if (flags & PMD_CHOICE_ENTRY_POINT)
    {
        pmd_entry_point_subtree* ep = (pmd_entry_point_subtree*)pmd_entry_point_find(env, PMD_DEVICE_GENERAL, choice->entry_point_id, TRUE);
        if (ep)
        {
            if (ep->n_el > 0)
            {
                pmd_entry_point_subtree_el* el = ep->el;
                while (el)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(fdebug, "%s[0x%2.2llX]%s\n", pmd_debug_get_indent(indent), el->id, el->namedobj.name);
#else
                    fprintf(fdebug, "%s[0x%2.2X]%s\n", pmd_debug_get_indent(indent), el->id, el->namedobj.name);
#endif

                    el = el->next;
                }
            }
        }
    }
    else
    {
        while (choice_el)
        {
            if (choice_el->cond_el->managedobj.class_id == PMD_CLASS_CONDITION_ELEMENT_INTERVAL)
            {
#if (PMD_FILE_FORMAT >= 600)
                fprintf(fdebug, "%s[0x%2.2llX]", pmd_debug_get_indent(indent), ((pmd_cond_el_int*)choice_el->cond_el)->from);
#else
                fprintf(fdebug, "%s[0x%2.2X]", pmd_debug_get_indent(indent), ((pmd_cond_el_int*)choice_el->cond_el)->from);
#endif
            }
            else if (choice_el->cond_el->managedobj.class_id == PMD_CLASS_CONDITION_ELEMENT_BITSTATE)
            {
                fprintf(fdebug, "%s[%s]", pmd_debug_get_indent(indent), ((pmd_cond_el_bit*)choice_el->cond_el)->bitstate);
            }
            else
            {
                fprintf(fdebug, "%s[???]", pmd_debug_get_indent(indent));
            }

            pmd_debug_objid_dump(fdebug, &choice_el->cond_el->managedobj, detailed);
            fprintf(fdebug, "%s:%s", choice_el->namedobj.name, choice_el->type->name);
            pmd_debug_objid_dump(fdebug, &choice_el->type->managedobj, detailed);
            fprintf(fdebug, "\n");

            choice_el = choice_el->next;
        }
        if (choice->default_type)
        {
            fprintf(fdebug, "%s(Default):%s", pmd_debug_get_indent(indent), choice->default_type->name);
            pmd_debug_objid_dump(fdebug, &choice->default_type->managedobj, detailed);
            fprintf(fdebug, "\n");
        }
    }
}

LOCAL void pmd_debug_type_dump(pmd_env* env, FILE* fdebug, const pmd_typ* type, int indent, int detailed)
{
    if (!type) return;

    /* type */
    switch (type->managedobj.class_id)
    {
    case PMD_CLASS_NUMBER_TYPE:
        pmd_debug_number_dump(fdebug, (const pmd_number*)type, indent, detailed);
        break;

    case PMD_CLASS_STRING_TYPE:
        pmd_debug_string_dump(fdebug, (const pmd_string*)type, indent, detailed);
        break;

    case PMD_CLASS_BLOCK:
        pmd_debug_block_type_dump(fdebug, (const pmd_block*)type, indent, detailed);
        break;

    case PMD_CLASS_SEQUENCE:
        pmd_debug_seq_dump(fdebug, (const pmd_seq*)type, indent, detailed);
        break;

    case PMD_CLASS_SEQUENCE_OF:
        pmd_debug_seq_of_type_dump(fdebug, (const pmd_seq_of*)type, indent, detailed);
        break;

    case PMD_CLASS_CHOICE:
        pmd_debug_choice_type_dump(env, fdebug, (const pmd_choice*)type, indent, detailed);
        break;

    case PMD_CLASS_FILLER_TYPE_STATIC:
        pmd_debug_filler_static_dump(fdebug, (const pmd_filler_static*)type, indent, detailed);
        break;

    case PMD_CLASS_FILLER_TYPE_DYNAMIC:
        pmd_debug_filler_dyn_dump(fdebug, (const pmd_filler_dyn*)type, indent, detailed);
        break;

    default:
        fprintf(fdebug, "%styp:", pmd_debug_get_indent(indent));
        fprintf(fdebug, "%s (", type->name);
        fprintf(fdebug, ")\n");
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_debug_type_dump(): Unhandled type %d (%s) [id:%u]", 
            type->managedobj.class_id, type->name, type->managedobj.object_id);
    }
}

LOCAL void pmd_debug_msg_dump(FILE* fdebug, const pmd_msgtype* msgtype, const pmd_msg* msg, int indent)
{
    unsigned int flags = msg->namedobj.managedobj.flags;

    /* name */
    if (msgtype->namedobj.managedobj.flags & PMD_MESSAGE_TYPE_FLAG_IS_TRACE)
    {
        fprintf(fdebug, "%s  trace:%s", pmd_debug_get_indent(indent), msg->namedobj.name);
    }
    else
    {
        fprintf(fdebug, "%s  message:%s", pmd_debug_get_indent(indent), msg->namedobj.name);
    }

    /* id */
#if (PMD_FILE_FORMAT >= 600)
    fprintf(fdebug, " id:0x%2.2llX", msg->id);
#else
    fprintf(fdebug, " id:0x%2.2X", msg->id);
#endif

    /* identifier */
    if (msg->namedobj.managedobj.flags & PMD_MESSAGE_HAS_IDENTIFIER)
    {
        fprintf(fdebug, " identifier:%s", msg->identifier);
    }

    /* function */
    if (msgtype->namedobj.managedobj.flags & PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE)
    {
        const char* name = pmd_constant_lookup_function(msg->function);
        fprintf(fdebug, " func:%s", name ? name : "?");
    }

    /* PMD type */
    if (msg->ref_seq)
    {
        fprintf(fdebug, " type:%s", msg->ref_seq->constructed.type.name);
    }

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags & PMD_MESSAGE_HAS_EMBEDDED_TRACES)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "HAS_EMBEDDED_TRACES");
            flags &= ~PMD_MESSAGE_HAS_EMBEDDED_TRACES;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_HAS_EMBEDDED_PROTOCOL_MESSAGE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "HAS_EMBEDDED_PROTOCOL_MESSAGE");
            flags &= ~PMD_MESSAGE_HAS_EMBEDDED_PROTOCOL_MESSAGE;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "HAS_EMBEDDED_MEDIA_MODULE_MESSAGE");
            flags &= ~PMD_MESSAGE_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_IN_SUMMARY)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IN_SUMMARY");
            flags &= ~PMD_MESSAGE_IN_SUMMARY;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_IS_NON_FILTERABLE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_NON_FILTERABLE");
            flags &= ~PMD_MESSAGE_IS_NON_FILTERABLE;
            has_flags = TRUE;
        }
        if (flags & PMD_TRACE_EXCLUDE_FROM_TRACE_ACTIVATION)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "EXCLUDE_FROM_TA");
            flags &= ~PMD_TRACE_EXCLUDE_FROM_TRACE_ACTIVATION;
            has_flags = TRUE;
        }
        if (flags & PMD_TRACE_DEFAULT_STATE_ON)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "DEFAULT_ON");
            flags &= ~PMD_TRACE_DEFAULT_STATE_ON;
            has_flags = TRUE;
        }
        if (flags & PMD_TRACE_HAS_IDENTIFIER)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "HAS_IDENTIFIER");
            flags &= ~PMD_TRACE_HAS_IDENTIFIER;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_IS_CARRIER_MESSAGE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_CARRIER");
            flags &= ~PMD_MESSAGE_IS_CARRIER_MESSAGE;
            has_flags = TRUE;
        }
        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_msg_dump(): Unhandled flags 0x%8.8X in message type %s", 
                flags, msg->namedobj.name);
        }
    }

    fprintf(fdebug, "\n");
}

LOCAL void pmd_debug_trcgrp_dump(FILE* fdebug, const pmd_msggrp* msggrp, int indent)
{
    const pmd_msg* msg_it = msggrp->messages;
    unsigned int flags = msggrp->namedobj.managedobj.flags;

    fprintf(fdebug, "%s  traceGroup:%s", pmd_debug_get_indent(indent), msggrp->namedobj.name);
#if (PMD_FILE_FORMAT >= 600)
    fprintf(fdebug, " id:0x%4.4Xll", msggrp->id);
#else
    fprintf(fdebug, " id:0x%4.4X", msggrp->id);
#endif

    if (msggrp->logical_name && msggrp->logical_name[0])
    {
        fprintf(fdebug, " logicalName:%s", msggrp->logical_name);
    }

    fprintf(fdebug, " identifier:%s", msggrp->identifier);
    if (msggrp->ref_type)
    {
        fprintf(fdebug, " type:%s", msggrp->ref_type->name);
    }

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags & PMD_TRACE_GROUP_EXCLUDE_FROM_TRACE_ACTIVATION)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "EXCLUDE_FROM_TA");
            flags &= ~PMD_TRACE_GROUP_EXCLUDE_FROM_TRACE_ACTIVATION;
            has_flags = TRUE;
        }
        if (flags & PMD_TRACE_GROUP_DEFAULT_STATE_ON)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "DEFAULT_ON");
            flags &= ~PMD_TRACE_GROUP_DEFAULT_STATE_ON;
            has_flags = TRUE;
        }
        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_trcgrp_dump(): Unhandled flags 0x%8.8X in trace group %s", 
                flags, msggrp->namedobj.name);
        }
    }

    fprintf(fdebug, "\n");

    while (msg_it)
    {
        pmd_debug_msg_dump(fdebug, msggrp->msgtype ? msggrp->msgtype : msggrp->msgent->msgtype, msg_it, indent+1);

        msg_it = msg_it->next;
    }
}

LOCAL void pmd_debug_msgent_dump(FILE* fdebug, const pmd_msgent* msgent, int indent)
{
    const pmd_msggrp* msggrp_trc_it = msgent->trace_groups;
    const pmd_msg* msg_it = msgent->messages;
    unsigned int flags = msgent->namedobj.managedobj.flags;

    /* name */
    fprintf(fdebug, "%s  entity:%s", pmd_debug_get_indent(indent), msgent->namedobj.name);

#if (PMD_FILE_FORMAT >= 600)
    fprintf(fdebug, " id:0x%4.4llX", msgent->id);
#else
    fprintf(fdebug, " id:0x%4.4X", msgent->id);
#endif

    /* logical name */
    if (msgent->logical_name && msgent->logical_name[0])
    {
        fprintf(fdebug, " logicalName:%s", msgent->logical_name);
    }

    /* id */
    fprintf(fdebug, " identifier:%s", msgent->identifier);

    /* reference type */
    if (msgent->ref_type)
    {
        fprintf(fdebug, " type:%s", msgent->ref_type->name);
    }

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags & PMD_MESSAGE_ENTITY_FLAG_DSP5_USE_2_BIT_PER_TRACE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "DSP5_USE_2_BIT_PER_TRACE");
            flags &= ~PMD_MESSAGE_ENTITY_FLAG_DSP5_USE_2_BIT_PER_TRACE;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_ENTITY_FLAG_IS_MESSAGE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_MESSAGE");
            flags &= ~PMD_MESSAGE_ENTITY_FLAG_IS_MESSAGE;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_ENTITY_FLAG_IS_TRACE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_TRACE");
            flags &= ~PMD_MESSAGE_ENTITY_FLAG_IS_TRACE;
            has_flags = TRUE;
        }        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_msgent_dump(): Unhandled flags 0x%8.8X in message entity %s", 
                flags, msgent->namedobj.name);
        }
    }

    fprintf(fdebug, "\n");

    /* trace groups */
    while (msggrp_trc_it)
    {
        pmd_debug_trcgrp_dump(fdebug, msggrp_trc_it, indent+1);

        msggrp_trc_it = (const pmd_msggrp*)msggrp_trc_it->next;
    }

    /* messages */
    while (msg_it)
    {
        pmd_debug_msg_dump(fdebug, msgent->msgtype, msg_it, indent+1);

        msg_it = (const pmd_msg*)msg_it->next;
    }
}

LOCAL void pmd_debug_msgtype_dump(FILE* fdebug, const pmd_msgtype* msgtype, const char* type_name, int indent)
{
    const pmd_msgent* msgent_it = msgtype->message_entities;
    const pmd_msggrp* msggrp_res_it = msgtype->message_groups_res;
    const pmd_msggrp* msggrp_trc_it = msgtype->message_groups_trc;
    const pmd_msg* msg_it = msgtype->messages;
    unsigned int flags = msgtype->namedobj.managedobj.flags;

    /* name */
    fprintf(fdebug, "%s  %s:%s", pmd_debug_get_indent(indent), type_name, msgtype->namedobj.name);

    /* id */
    fprintf(fdebug, " identifier:%s", msgtype->identifier);

    /* reference type */
    if (msgtype->ref_type)
    {
        fprintf(fdebug, " type:%s", msgtype->ref_type->name);
    }

    /* flags */
    if (flags != 0)
    {
        int has_flags = FALSE;
        fprintf(fdebug, " flags:");

        if (flags & PMD_MESSAGE_TYPE_FLAG_DSP5_USE_2_BIT_PER_TRACE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "DSP5_USE_2_BIT_PER_TRACE");
            flags &= ~PMD_MESSAGE_TYPE_FLAG_DSP5_USE_2_BIT_PER_TRACE;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_MESSAGE");
            flags &= ~PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE;
            has_flags = TRUE;
        }
        if (flags & PMD_MESSAGE_TYPE_FLAG_IS_TRACE)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "IS_TRACE");
            flags &= ~PMD_MESSAGE_TYPE_FLAG_IS_TRACE;
            has_flags = TRUE;
        }
        if (flags)
        {
            if (has_flags) fprintf(fdebug, "|");
            fprintf(fdebug, "0x8.8X", flags);
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_debug_msgtype_dump(): Unhandled flags 0x%8.8X in message type %s", 
                flags, msgtype->namedobj.name);
        }
    }

    fprintf(fdebug, "\n");

    /* messages */
    while (msg_it)
    {
        pmd_debug_msg_dump(fdebug, msgtype, msg_it, indent+1);

        msg_it = msg_it->next;
    }

    /* resources */
    while (msggrp_res_it)
    {
        msg_it = msggrp_res_it->messages;

        fprintf(fdebug, "%s  resource:%s", pmd_debug_get_indent(indent+1), msggrp_res_it->namedobj.name);
#if (PMD_FILE_FORMAT >= 600)
        fprintf(fdebug, " id:0x%2.2llX", msggrp_res_it->id);
#else
        fprintf(fdebug, " id:0x%2.2X", msggrp_res_it->id);
#endif
        fprintf(fdebug, " identifier:%s", msggrp_res_it->identifier);
        if (msggrp_res_it->ref_type)
        {
            fprintf(fdebug, " type:%s", msggrp_res_it->ref_type->name);
        }

        /* Write resource interface version */
        if (msggrp_res_it->res->base.ver.type != AUTOGEN_OBJ_VERSION_ALL)
        {
            fprintf(fdebug, " version:%03hu.%03hu", msggrp_res_it->res->base.ver.from[0], msggrp_res_it->res->base.ver.from[1]);
        }

        /* flags */
        flags = msggrp_res_it->namedobj.managedobj.flags;
        if (flags != 0)
        {
            int has_flags = FALSE;
            fprintf(fdebug, " flags:");

            if (flags & PMD_RESOURCE_HAS_CONFLICTING_MESSAGES)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "HAS_CONFLICTING_MESSAGES");
                flags &= ~PMD_RESOURCE_HAS_CONFLICTING_MESSAGES;
                has_flags = TRUE;
            }
            if (flags)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "0x8.8X", flags);
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                    "pmd_debug_msgtype_dump(): Unhandled flags 0x%8.8X in resource %s", 
                    flags, msggrp_res_it->namedobj.name);
            }
        }

        fprintf(fdebug, "\n");

        while (msg_it)
        {
            pmd_debug_msg_dump(fdebug, msgtype, msg_it, indent+2);

            msg_it = msg_it->next;
        }

        msggrp_res_it = msggrp_res_it->next;
    }

    /* trace groups */
    while (msggrp_trc_it)
    {
        pmd_debug_trcgrp_dump(fdebug, msggrp_trc_it, indent+1);

        msggrp_trc_it = (const pmd_msggrp*)msggrp_trc_it->next;
    }

    /* message entities */
    while (msgent_it)
    {
        pmd_debug_msgent_dump(fdebug, msgent_it, indent+1);

        msgent_it = (const pmd_msgent*)msgent_it->next;
    }
}

LOCAL void pmd_debug_env_vars_write(const pmd_env_var* env_vars, FILE* fdebug)
{
    if (env_vars)
    {
        fprintf(fdebug, "\n");
        fprintf(fdebug, "  Environment variables\n");
        fprintf(fdebug, "  ---------------------------------------------------------\n");
    }
    while (env_vars)
    {
        const char* name = pmd_constant_lookup_environment_var_id(env_vars->id);
        if (name)
        {
            fprintf(fdebug, "  [%3.3u] %s type:%d", env_vars->id, name, env_vars->type);
        }
        else
        {
            fprintf(fdebug, "  [%3.3u] (Unknown) type:%d", env_vars->id, env_vars->type);
        }

        if (env_vars->id == PMD_ENVIRONMENT_VAR_ID_PMD_FILE_ORIGIN)
        {
            fprintf(fdebug, " value:Hidden");
        }
        else if (env_vars->type == PMD_ENVIRONMENT_VAR_TYPE_INTEGER)
        {
            fprintf(fdebug, " value:%d", env_vars->value);
        }
        else if (env_vars->type == PMD_ENVIRONMENT_VAR_TYPE_STRING)
        {
            fprintf(fdebug, " value:%s", env_vars->value_string);
        }
        else
        {
            fprintf(fdebug, " value:?");
        }

        if (env_vars->id == PMD_ENVIRONMENT_VAR_ID_PMD_FILE_TYPE)
        {
            fprintf(fdebug, "(%s)", pmd_constant_lookup_file_type(env_vars->value));
        }

        if (env_vars->id == PMD_ENVIRONMENT_VAR_ID_PMD_FILE_RESTRICTION)
        {
            fprintf(fdebug, "(%s)", pmd_constant_lookup_file_restriction(env_vars->value));
        }

        fprintf(fdebug, "\n");

        env_vars = (const pmd_env_var*)env_vars->next;
    }
}

LOCAL void pmd_debug_info_groups_write(const pmd_info_group* info_groups, FILE* fdebug)
{
    if (info_groups)
    {
        fprintf(fdebug, "\n");
        fprintf(fdebug, "  Info groups\n");
        fprintf(fdebug, "  ---------------------------------------------------------\n");
    }
    while (info_groups)
    {
        unsigned int n;
        const pmd_info* info_it = info_groups->info;
        const char* name = pmd_constant_lookup_info_type(info_groups->type);

        if (info_groups->type == PMD_INFO_TYPE_CDSP_ERRORS)
        {
            fprintf(fdebug, "  %-60s", name ? name : "?");
        }
        else
        {
            fprintf(fdebug, "  %-58s", name ? name : "?");
        }

        for (n = 0; n < info_groups->n_data; n++)
        {
            const char* attr_name = pmd_constant_lookup_info_attribute(info_groups->type, n);
            fprintf(fdebug, "%-20s ", attr_name ? attr_name : "?");
        }

        fprintf(fdebug, "\n");

        while (info_it)
        {
            unsigned int flags = info_it->namedobj.managedobj.flags;

            if (info_groups->type == PMD_INFO_TYPE_CDSP_ERRORS)
            {
                fprintf(fdebug, "    [0x%8.8X] ", info_it->id);
            }
            else
            {
                fprintf(fdebug, "    [%3.3u] ", info_it->id);
            }

            fprintf(fdebug, "%-50s", info_it->namedobj.name);

            /* attributes */
            for (n = 0; n < info_groups->n_data; n++)
            {
                fprintf(fdebug, "%-20d ", info_it->data[n]);
            }

            /* flags */
            if (flags != 0)
            {
                int has_flags = FALSE;
                fprintf(fdebug, " flags:");

                if (flags & PMD_FTD_IS_INPUT)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "FTD_IS_INPUT");
                    flags &= ~PMD_FTD_IS_INPUT;
                    has_flags = TRUE;
                }
                if (flags & PMD_FTD_IS_STATIC)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "FTD_IS_STATIC");
                    flags &= ~PMD_FTD_IS_STATIC;
                    has_flags = TRUE;
                }
                if (flags & PMD_FTD_MODE_RD)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "FTD_MODE_RD");
                    flags &= ~PMD_FTD_MODE_RD;
                    has_flags = TRUE;
                }
                if (flags & PMD_FTD_MODE_INFRA)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "FTD_MODE_INFRA");
                    flags &= ~PMD_FTD_MODE_INFRA;
                    has_flags = TRUE;
                }
                if (flags & PMD_FTD_MODE_OPERATOR)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "FTD_MODE_OPERATOR");
                    flags &= ~PMD_FTD_MODE_OPERATOR;
                    has_flags = TRUE;
                }
                if (flags)
                {
                    if (has_flags) fprintf(fdebug, "|");
                    fprintf(fdebug, "0x8.8X", flags);
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                        "pmd_debug_infoobj_write(): Unhandled flags 0x%8.8X in info %s", 
                        flags, info_it->namedobj.name);
                }
            }

            fprintf(fdebug, "\n");

            info_it = (const pmd_info*)info_it->next;
        }

        info_groups = (const pmd_info_group*)info_groups->next;
    }
}

LOCAL void pmd_debug_entry_points_write(const pmd_entry_point* entry_points, FILE* fdebug)
{
    int is_subtree = FALSE;

    if (entry_points && entry_points->managedobj.class_id == PMD_CLASS_ENTRY_POINT_SUBTREE)
    {
        is_subtree = TRUE;
    }

    if (entry_points)
    {
        fprintf(fdebug, "\n");
        fprintf(fdebug, "  Entry point%s\n", is_subtree ? " sub trees" : "s");
        fprintf(fdebug, "  ---------------------------------------------------------\n");
    }
    while (entry_points)
    {
        /* name */
        fprintf(fdebug, "  %s:", entry_points->name);

        /* id */
        fprintf(fdebug, " id:0x%8.8X", entry_points->id);

        /* flags */
        if (entry_points->managedobj.flags != 0)
        {
            unsigned int flags = entry_points->managedobj.flags;
            int has_flags = FALSE;
            fprintf(fdebug, " flags:");

            if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "HAS_EMBEDDED_TRACES");
                flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_TRACES;
                has_flags = TRUE;
            }
            if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "HAS_EMBEDDED_PROTOCOL_MESSAGE");
                flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_PROTOCOL_MESSAGE;
                has_flags = TRUE;
            }
            if (flags & PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "HAS_EMBEDDED_MEDIA_MODULE_MESSAGE");
                flags &= ~PMD_ENTRY_POINT_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE;
                has_flags = TRUE;
            }
            if (flags & PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "HAS_INFO_GROUP_DEPENDENCY");
                flags &= ~PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY;
                has_flags = TRUE;
            }
            if (flags & PMD_ENTRY_POINT_PROTOCOL_IS_LE)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "PROTOCOL_IS_LE");
                flags &= ~PMD_ENTRY_POINT_PROTOCOL_IS_LE;
                has_flags = TRUE;
            }
            if (flags)
            {
                if (has_flags) fprintf(fdebug, "|");
                fprintf(fdebug, "0x8.8X", flags);
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                    "pmd_debug_entry_points_write(): Unhandled flags 0x%8.8X in entry point %s", 
                    flags, entry_points->name);
            }
        }

        if (entry_points->managedobj.flags & PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY)
        {
            const char* info_group_name = pmd_constant_lookup_info_type(((pmd_entry_point_subtree*)entry_points)->info_group_id);

            fprintf(fdebug, " INFO(%s)", info_group_name ? info_group_name : "Unknown");
        }

        /* type */
        if (!is_subtree)
        {
            fprintf(fdebug, " type_ref:%s", entry_points->ref_type ? entry_points->ref_type->name : "?");
        }

        fprintf(fdebug, "\n");

        if (is_subtree)
        {
            pmd_entry_point_subtree_el* el = ((pmd_entry_point_subtree*)entry_points)->el;

            while (el)
            {
                if (el->device_id == PMD_DEVICE_GENERAL)
                {
                    fprintf(fdebug, "    %s(0x%8.8X) device:GENERAL", el->namedobj.name, el->id);
                }
                else
                {
                    const char* device_name = pmd_constant_lookup_device_logical_name(el->device_id);
                    if (device_name)
                    {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(fdebug, "    %s(0x%8.8llX) device:%s", el->namedobj.name, el->id, device_name);
#else
                        fprintf(fdebug, "    %s(0x%8.8X) device:%s", el->namedobj.name, el->id, device_name);
#endif
                    }
                    else
                    {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(fdebug, "    %s(0x%8.8llX) device:0x%2.2X", el->namedobj.name, el->id, el->device_id);
#else
                        fprintf(fdebug, "    %s(0x%8.8X) device:0x%2.2X", el->namedobj.name, el->id, el->device_id);
#endif
                    }
                }

                fprintf(fdebug, "\n");

                el = el->next;
            }
        }

        entry_points = (pmd_entry_point*)entry_points->next;
    }
}

LOCAL void pmd_debug_msg_types_write_header(int* has_header, FILE* fdebug)
{
    if (*has_header == FALSE)
    {
        fprintf(fdebug, "\n");
        fprintf(fdebug, "  Message info tree\n");
        fprintf(fdebug, "  ---------------------------------------------------------\n");

        *has_header = TRUE;
    }
}

LOCAL void pmd_debug_msg_types_write_basics(int* has_header, int* has_basics, const pmd_message_info_tree_conf* tree_element, FILE* fdebug)
{
    if (*has_basics == FALSE)
    {
        pmd_debug_msg_types_write_header(has_header, fdebug);

        /* element type */
        fprintf(fdebug, "  elementType:");
        switch (tree_element->element_type)
        {
        case PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_GROUP:
            fprintf(fdebug, "MessageGroup");
            break;

        case PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE:
            fprintf(fdebug, "MessageType");
            break;

        default:
            fprintf(fdebug, "Unknown");
            break;
        }

        /* name */
        fprintf(fdebug, " elementName:%s", tree_element->name);
        fprintf(fdebug, "\n");

        *has_basics = TRUE;
    }
}

LOCAL void pmd_debug_msg_types_write(const pmd_msgtype* msg_types, FILE* fdebug)
{
    int i;
    int has_header = FALSE;

    for (i = 0; i < PMD_MESSAGE_INFO_TREE_ELEMENTS_MAX; i++)
    {
        int has_basics = FALSE;

        pmd_message_info_tree_conf* tree_element = &pmd_constant_message_info_tree[i];

        /* print the element */
        switch (tree_element->element_type)
        {
        case PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_GROUP:
            {
                int has_group = FALSE;
#if (PMD_FILE_FORMAT >= 600)
                unsigned long long entity;
#else
                unsigned int entity;
#endif
                const pmd_message_type_group_conf* group_conf = &pmd_constant_message_type_group[tree_element->element_id];

#if (PMD_FILE_FORMAT >= 600)
                for (entity = (unsigned long long)group_conf->first_type_id; entity <= (unsigned long long)group_conf->last_type_id; entity++)
#else
                for (entity = group_conf->first_type_id; entity <= group_conf->last_type_id; entity++)
#endif
                {
                    const pmd_msgtype* msgtype_it = msg_types;
                    while (msgtype_it && msgtype_it->id != entity)
                    {
                        msgtype_it = (const pmd_msgtype*)msgtype_it->next;
                    }
                    if (msgtype_it)
                    {
                        if (!has_group)
                        {
                            pmd_debug_msg_types_write_basics(&has_header, &has_basics, tree_element, fdebug);

                            /* group */
                            fprintf(fdebug, "    messageTypeGroup:%s\n", group_conf->name);

                            has_group = TRUE;
                        }

                        pmd_debug_msgtype_dump(fdebug, msgtype_it, "entity", 2);
                    }
                }
            }
            break;

        case PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE:
            {
                const pmd_msgtype* msgtype_it = msg_types;

#if (PMD_FILE_FORMAT >= 600)
                while (msgtype_it && msgtype_it->id != (unsigned long long)tree_element->element_id)
#else
                while (msgtype_it && msgtype_it->id != tree_element->element_id)
#endif
                {
                    msgtype_it = (const pmd_msgtype*)msgtype_it->next;
                }
                if (msgtype_it)
                {
                    pmd_debug_msg_types_write_basics(&has_header, &has_basics, tree_element, fdebug);

                    pmd_debug_msgtype_dump(fdebug, msgtype_it, "type", 1);
                }
            }
            break;
        }
    }
}

/* End of file output_pmd_debug.c */
