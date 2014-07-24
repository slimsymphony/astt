/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_pmd_types.c
                ------------------
                SW Module






Project:          autogen

%name:            output_pmd_types.c %
%version:         55 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 12:16:13 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the source code for the PMD output generator.
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_ref.h"
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
#include <math.h>
#include <ctype.h>

#include "list.h"

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL
#endif /* LOCAL */

/* ============================================================================================= */
/* CBlock functions */
/* ============================================================================================= */

pmd_block* pmd_block_create(pmd_env* env, const char* name, unsigned int alg)
{
    /* allocate CBlock object */
    pmd_block* block = (pmd_block*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_block));

    /* initialize CConstructedType part */
    pmd_constructed_init(env, &block->constructed, PMD_CLASS_BLOCK, name);

    /* initialize CBlock part */
    block->algorithm = alg;
    block->seq       = NULL;

    return block;
}

pmd_block* pmd_block_entry_point_create(pmd_env* env, const char* name, const char* ep_name, unsigned short ep_id, unsigned short ep_device_id)
{
    /* allocate CBlock object */
    pmd_block* block = pmd_block_create(env, name, PMD_BLOCK_ALGORITHM_ENTRYPOINT);

    block->ep_name      = pmd_heap_strdup_h(env->heap_handle, ep_name);
    block->ep_id        = ep_id;
    block->ep_device_id = ep_device_id;

    return block;
}

pmd_block* pmd_block_dll_create(pmd_env* env, const char* name, const char* dll_name, const char* dll_func)
{
    /* allocate CBlock object */
    pmd_block* block = pmd_block_create(env, name, PMD_BLOCK_ALGORITHM_EXTERNAL);

    block->dll_name = pmd_heap_strdup_h(env->heap_handle, dll_name);
    block->dll_func = pmd_heap_strdup_h(env->heap_handle, dll_func);

    return block;
}

pmd_typ* pmd_block_clone(pmd_env* env, const pmd_block* org_block)
{
    /* create CBlock object */
    pmd_block* block = pmd_block_create(env, NULL, org_block->algorithm);

    /* clone CConstructedType part */
    pmd_constructed_clone(&block->constructed, &org_block->constructed);

    /* clone CBlock part */
    block->data1     = org_block->data1;
    block->data2     = org_block->data2;
    block->data_int  = org_block->data_int;

    block->ep_name      = org_block->ep_name;
    block->ep_id        = org_block->ep_id;
    block->ep_device_id = org_block->ep_device_id;

    block->dll_func  = org_block->dll_func;
    block->dll_name  = org_block->dll_name;

    block->seq       = org_block->seq;

    return &block->constructed.type;

}

void pmd_block_write(pmd_env* env, const pmd_block* block)
{
    /* write CConstructedType part */
    pmd_constructed_write(env, &block->constructed);

    /* write CBlock part */
    pmd_write_word(env, block->algorithm);

    switch(block->algorithm)
    {
    case PMD_BLOCK_ALGORITHM_ENTRYPOINT:
        pmd_write_word(env, block->ep_id);
        pmd_write_dword(env, block->ep_device_id);
        break;

    case PMD_BLOCK_ALGORITHM_EXTERNAL:
        pmd_write_string(env, block->dll_name);
        pmd_write_string(env, block->dll_func);
        break;
    }
}

/* ============================================================================================= */
/* CChoice functions */
/* ============================================================================================= */

pmd_choice* pmd_choice_create(pmd_env* env, const char* name, const pmd_typ* default_type, unsigned short device_id)
{
    /* allocate CChoice object */
    pmd_choice* choice = (pmd_choice*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_choice));
    device_id;

    /* initialize CConstructedType part */
    pmd_constructed_init(env, &choice->constructed, PMD_CLASS_CHOICE, name);

    /* initialize CChoice part */
    pmd_tag_clear(&choice->tag);

    choice->n_choice_el = 0;
    choice->choice_el   = NULL;

    choice->default_type = default_type;

#if PMD_FILE_FORMAT >= 501
    choice->device_id = device_id;
#endif

    return choice;
}

pmd_typ* pmd_choice_clone(pmd_env* env, const pmd_choice* org_choice)
{
    /* clone default type */
    pmd_typ* def_type = pmd_type_clone_any(env, org_choice->default_type);

    /* create CChoice object */
    pmd_choice* choice = pmd_choice_create(env, NULL, def_type, org_choice->device_id);

    /* clone CConstructedType part */
    pmd_constructed_clone(&choice->constructed, &org_choice->constructed);

    /* clone CChoice part */
	choice->entry_point_name        = org_choice->entry_point_name;
	choice->entry_point_id          = org_choice->entry_point_id;
    choice->n_choice_el             = org_choice->n_choice_el;
    choice->choice_el               = pmd_choice_el_clone(env, org_choice->choice_el);

    pmd_tag_clone(&choice->tag, &org_choice->tag);

    return &choice->constructed.type;
}

void pmd_choice_set_data_order_little_endian(pmd_choice* choice)
{
    choice->constructed.type.managedobj.flags |= PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN;
    choice->tag.managedobj.flags  |= PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN;
}

void pmd_choice_write(pmd_env* env, const pmd_choice* choice)
{
    const pmd_choice_el* choice_el = choice->choice_el;

    /* write CConstructedType part */
    pmd_constructed_write(env, &choice->constructed);

    /* write CChoice part */
    pmd_tag_write(env, &choice->tag);
    
    if (choice->default_type)
    {
        pmd_write_objid(env, &choice->default_type->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }
    
    /* Write Entry point ID and device ID */
    if (choice->constructed.type.managedobj.flags & PMD_CHOICE_ENTRY_POINT)
    {
        pmd_write_word(env, choice->entry_point_id);
    }
#if PMD_FILE_FORMAT >= 501
    pmd_write_word(env, choice->device_id);
#endif


    pmd_write_dword(env, choice->n_choice_el);

    /* write elements*/
    choice_el = choice->choice_el;
    while (choice_el)
    {
        pmd_choice_el_write(env, choice_el);

        choice_el = choice_el->next;
    }

    /* write condition elements */
    choice_el = choice->choice_el;
    while (choice_el)
    {
        pmd_cond_el_write_any(env, choice_el->cond_el);

        choice_el = choice_el->next;
    }
}

/* ============================================================================================= */
/* CChoiceElement functions */
/* ============================================================================================= */

pmd_choice_el* pmd_choice_el_create(pmd_env* env, const char* name, const pmd_cond_el* cond_el, const pmd_typ* type)
{
    /* create CChoiceElement object */
    pmd_choice_el* choice_el = (pmd_choice_el*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_choice_el));

    /* initialize CNamedObject part */
    pmd_namedobj_init(env, &choice_el->namedobj, name, FALSE, PMD_CLASS_NULL, 0);

    choice_el->cond_el = cond_el;
    choice_el->type    = type;

    choice_el->next = NULL;

    return choice_el;
}

void pmd_choice_el_add(pmd_env* env, pmd_choice* choice, const char* name, const pmd_cond_el* cond_el, const pmd_typ* type)
{
    /* create CChoiceElement */
    pmd_choice_el* choice_el = pmd_choice_el_create(env, name, cond_el, type);

    /* if first element, just set in choice */
    if (!choice->choice_el)
    {
        choice->choice_el = choice_el;
    }
    /* else set as last element */
    else
    {
        pmd_choice_el* choice_el_it = choice->choice_el;

        while (choice_el_it->next)
        {
            choice_el_it = choice_el_it->next;
        }

        choice_el_it->next = choice_el;
    }

    choice->n_choice_el++;
}

#if (PMD_FILE_FORMAT >= 600)
void pmd_choice_el_add_simple(pmd_env* env, pmd_choice* choice, const char* name, long long id, const pmd_typ* type)
#else
void pmd_choice_el_add_simple(pmd_env* env, pmd_choice* choice, const char* name, int id, const pmd_typ* type)
#endif
{
    pmd_choice_el_add(env, choice, name, pmd_cond_el_int_create(env, id, id), type);
}

void pmd_choice_el_add_mask(pmd_env* env, pmd_choice* choice, const char* name, const char* mask, const pmd_typ* type)
{
    pmd_choice_el_add(env, choice, name, pmd_cond_el_bit_create(env, mask), type);
}

pmd_choice_el* pmd_choice_el_clone(pmd_env* env, const pmd_choice_el* org_choice_el)
{
    pmd_choice_el* choice_el = NULL;

    if (org_choice_el)
    {
        /* clone condition element */
        pmd_cond_el* cond_el = pmd_cond_el_clone_any(env, org_choice_el->cond_el);

        /* create CChoiceElement object */
        pmd_choice_el* choice_el = pmd_choice_el_create(env, NULL, cond_el, org_choice_el->type);

        /* clone CNamedObject part */
        pmd_namedobj_clone(&choice_el->namedobj, &org_choice_el->namedobj);

        /* clone children */
        choice_el->next = pmd_choice_el_clone(env, org_choice_el->next);
    }

    return choice_el;
}

void pmd_choice_el_write(pmd_env* env, const pmd_choice_el* choice_el)
{
    /* write CNamedObject part */
    pmd_namedobj_write(env, &choice_el->namedobj);

    /* write CNumberPresentationConditionElement part */
    pmd_write_objid(env, &choice_el->type->managedobj);
    pmd_write_objid(env, &choice_el->cond_el->managedobj);
}

/* ============================================================================================= */
/* CConditionElement functions */
/* ============================================================================================= */

void pmd_cond_el_init(pmd_cond_el* cond_el, unsigned short class_id, unsigned int object_id)
{
    /* initialize CManagedObject part */
    pmd_managedobj_init(&cond_el->managedobj, TRUE, class_id, object_id);

    /* initialize CConditionElement part */
     /* No member attributes */
}

void pmd_cond_el_clone(pmd_cond_el* cond_el, const pmd_cond_el* org_cond_el)
{
    /* clone CManagedObject part */
    pmd_managedobj_clone(&cond_el->managedobj, &org_cond_el->managedobj);

    /* clone CConditionElement part */
     /* No member attributes */
}

pmd_cond_el* pmd_cond_el_clone_any(pmd_env* env, const pmd_cond_el* org_cond_el)
{
    pmd_cond_el* cond_el = NULL;

    if (org_cond_el)
    {
        switch (org_cond_el->managedobj.class_id)
        {
        case PMD_CLASS_CONDITION_ELEMENT_BITSTATE:
            cond_el = pmd_cond_el_bit_clone(env, (pmd_cond_el_bit*)org_cond_el);
            break;
        case PMD_CLASS_CONDITION_ELEMENT_INTERVAL:
            cond_el = pmd_cond_el_int_clone(env, (pmd_cond_el_int*)org_cond_el);
            break;
        default:
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_cond_el_clone_any(): Unhandled condition element: %d [id:%u]", 
                org_cond_el->managedobj.class_id, org_cond_el->managedobj.object_id);
        }
    }

    return cond_el;
}

void pmd_cond_el_write(pmd_env* env, const pmd_cond_el* cond_el)
{
    /* write CManagedObject part */
    pmd_managedobj_write(env, &cond_el->managedobj);

    /* write CConditionElement part */
     /* No member attributes */
}

void pmd_cond_el_write_any(pmd_env* env, const pmd_cond_el* cond_el)
{
    if (cond_el && cond_el->managedobj.stream_out)
    {
        /* write CConditionElement part */
        pmd_cond_el_write(env, cond_el);

        switch (cond_el->managedobj.class_id)
        {
        case PMD_CLASS_CONDITION_ELEMENT_BITSTATE:
            pmd_cond_el_bit_write(env, (const pmd_cond_el_bit*)cond_el);
            break;
        case PMD_CLASS_CONDITION_ELEMENT_INTERVAL:
            pmd_cond_el_int_write(env, (const pmd_cond_el_int*)cond_el);
            break;
        default:
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_cond_el_write_any(): Unhandled condition element: %d [id:%u]", 
                cond_el->managedobj.class_id, cond_el->managedobj.object_id);
        }
    }
}

/* ============================================================================================= */
/* CConditionElementBitstate functions */
/* ============================================================================================= */

pmd_cond_el* pmd_cond_el_bit_create(pmd_env* env, const char* bitstate)
{
    pmd_cond_el_bit* cond_el_bit = NULL;
    pmd_cond_el_bit_reuse* last_cond_el_bit_reuse = NULL;
    pmd_cond_el_bit_reuse* cond_el_bit_reuse_it = env->cond_el_bit_reuse;

    /* try reusing object */
    if (cond_el_bit_reuse_it)
    {
        while (cond_el_bit_reuse_it && strcmp(cond_el_bit_reuse_it->cond_el_bit->bitstate, bitstate) < 0)
        {
            last_cond_el_bit_reuse = cond_el_bit_reuse_it;
            cond_el_bit_reuse_it = cond_el_bit_reuse_it->next;
        }

        /* found... clone it! */
        if (cond_el_bit_reuse_it && strcmp(cond_el_bit_reuse_it->cond_el_bit->bitstate, bitstate) == 0)
        {
            cond_el_bit = (pmd_cond_el_bit*)pmd_cond_el_bit_clone(env, cond_el_bit_reuse_it->cond_el_bit);
        }
    }
    /* else create new object */
    if (!cond_el_bit)
    {
        /* allocate CConditionElementBitstate object */
        cond_el_bit = (pmd_cond_el_bit*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_cond_el_bit));

        /* initialize CConditionElement part */
        pmd_cond_el_init(&cond_el_bit->cond_el, PMD_CLASS_CONDITION_ELEMENT_BITSTATE, ++env->last_object_id);

        /* initialize CConditionElementBitstate part */
        cond_el_bit->bitstate = pmd_heap_strdup_h(env->heap_handle, bitstate);

        /* save object for later reuse */
        {
            pmd_cond_el_bit_reuse* cond_el_bit_reuse = 
                (pmd_cond_el_bit_reuse*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_cond_el_bit_reuse));

            cond_el_bit_reuse->cond_el_bit = cond_el_bit;

            if (last_cond_el_bit_reuse)
            {
                last_cond_el_bit_reuse->next = cond_el_bit_reuse;
            }
            else
            {
                env->cond_el_bit_reuse = cond_el_bit_reuse;
            }

            cond_el_bit_reuse->next = cond_el_bit_reuse_it;
        }
    }

    return &cond_el_bit->cond_el;
}

pmd_cond_el* pmd_cond_el_bit_clone(pmd_env* env, const pmd_cond_el_bit* org_cond_el_bit)
{
    /* allocate CConditionElementBitstate object */
    pmd_cond_el_bit* cond_el_bit = 
        (pmd_cond_el_bit*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_cond_el_bit));

    /* clone CConditionElement object */
    pmd_cond_el_clone(&cond_el_bit->cond_el, &org_cond_el_bit->cond_el);

     /* clone CConditionElementBitstate object */
    cond_el_bit->bitstate = org_cond_el_bit->bitstate;

    return &cond_el_bit->cond_el;
}

void pmd_cond_el_bit_write(pmd_env* env, const pmd_cond_el_bit* cond_el_bit)
{
    /* write CConditionElement part */
     /* has been written already... */

    /* write CConditionElementBitstate part */
    pmd_write_string(env, cond_el_bit->bitstate);
}

/* ============================================================================================= */
/* CConditionElementInterval functions */
/* ============================================================================================= */
#if (PMD_FILE_FORMAT >= 600)
pmd_cond_el* pmd_cond_el_int_create(pmd_env* env, long long from, long long to)
#else
pmd_cond_el* pmd_cond_el_int_create(pmd_env* env, int from, int to)
#endif
{
    pmd_cond_el_int* cond_el_int = NULL;

    /* insertion point in sorted pointer array */
    int ins = 0;

    /* try reusing object if from = to */
    if (from == to)
    {
        int left  = 0;
        int mid   = 0;
        int right = env->cond_el_int_list_used - 1;
        int match = -1;

        /* binary search */
        while (left <= right)
        {
            mid = (left + right) / 2;

            if (env->cond_el_int_list[mid].key == from)
            {
                match = mid;
                break;
            }
            if (env->cond_el_int_list[mid].key < from)  /* reverse sorted */
            {
                right = mid - 1;
                ins   = mid;
            }
            else
            {
                left = mid + 1;
                ins  = mid + 1;
            }
        }

        if (match == -1)
        {
            if (env->cond_el_int_list_size == env->cond_el_int_list_used)
            {
                env->cond_el_int_list_size += 4096;
                env->cond_el_int_list = (pmd_cond_el_int_node*)realloc(env->cond_el_int_list, env->cond_el_int_list_size * sizeof(pmd_cond_el_int_node));
                (void)memset(env->cond_el_int_list + env->cond_el_int_list_used,
                    (sizeof(pmd_cond_el_int_node) * (env->cond_el_int_list_size - env->cond_el_int_list_used)), 0x00);
            }

            if ((unsigned)ins < env->cond_el_int_list_used)
            {
                (void)memmove(env->cond_el_int_list + (ins + 1),
                    env->cond_el_int_list +  ins     ,
                    (sizeof(pmd_cond_el_int_node) * (env->cond_el_int_list_used - ins)));
            }

            env->cond_el_int_list_used++;

            cond_el_int = (pmd_cond_el_int*)
                pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_cond_el_int));

            pmd_cond_el_init(&cond_el_int->cond_el,
                PMD_CLASS_CONDITION_ELEMENT_INTERVAL,
                ++env->last_object_id);

            cond_el_int->from = from;
            cond_el_int->to   = to;

            cond_el_int->cond_el.managedobj.flags |= PMD_CONDITION_ELEMENT_HAS_SINGLE_VALUE_INTERVAL;

            /* save object for later reuse */
            env->cond_el_int_list[ins].key         = from;
            env->cond_el_int_list[ins].cond_el_int = cond_el_int;
        }
        else
        {
            /* clone matched element */
            cond_el_int = (pmd_cond_el_int*)
                pmd_cond_el_int_clone(env, env->cond_el_int_list[match].cond_el_int);
        }
    }
    else
    {
        /* else create new object */
        /* allocate CConditionElementInterval object */
        cond_el_int = (pmd_cond_el_int*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_cond_el_int));

        /* initialize CConditionElement part */
        pmd_cond_el_init(&cond_el_int->cond_el, PMD_CLASS_CONDITION_ELEMENT_INTERVAL, ++env->last_object_id);

        /* initialize CConditionElementInterval part */
        cond_el_int->from = from;
        cond_el_int->to   = to;
    }

    return &cond_el_int->cond_el;
}

pmd_cond_el* pmd_cond_el_int_clone(pmd_env* env, const pmd_cond_el_int* org_cond_el_int)
{
    /* allocate CConditionElementInterval object */
    pmd_cond_el_int* cond_el_int = (pmd_cond_el_int*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_cond_el_int));

    /* clone CConditionElement object */
    pmd_cond_el_clone(&cond_el_int->cond_el, &org_cond_el_int->cond_el);

    /* clone CConditionElement object */
    cond_el_int->from = org_cond_el_int->from;
    cond_el_int->to   = org_cond_el_int->to;

    return &cond_el_int->cond_el;
}

void pmd_cond_el_int_write(pmd_env* env, const pmd_cond_el_int* cond_el_int)
{
    /* write CConditionElement part */
     /* has been written already... */

    /* write CConditionElementInterval part */
#if (PMD_FILE_FORMAT >= 600)
    pmd_write_ddword(env, cond_el_int->from);

    if (!(cond_el_int->cond_el.managedobj.flags & PMD_CONDITION_ELEMENT_HAS_SINGLE_VALUE_INTERVAL))
    {
        pmd_write_ddword(env, cond_el_int->to);
    }
#else
    pmd_write_dword(env, cond_el_int->from);

    if (!(cond_el_int->cond_el.managedobj.flags & PMD_CONDITION_ELEMENT_HAS_SINGLE_VALUE_INTERVAL))
    {
        pmd_write_dword(env, cond_el_int->to);
    }
#endif
}

/* ============================================================================================= */
/* CConstructedType functions */
/* ============================================================================================= */

void pmd_constructed_init(pmd_env* env, pmd_constructed* constructed, unsigned short class_id, const char* name)
{
    /* initialize CType part */
    pmd_type_init(env, &constructed->type, class_id, name);

    /* initialize CConstructedType part */
    pmd_length_clear(&constructed->length_obj);
}

void pmd_constructed_clone(pmd_constructed* constructed, const pmd_constructed* org_constructed)
{
    /* clone CType part */
    pmd_type_clone(&constructed->type, &org_constructed->type);

    /* clone CConstructedType part */
    pmd_length_clone(&constructed->length_obj, &org_constructed->length_obj);
}

void pmd_constructed_write(pmd_env* env, const pmd_constructed* constructed)
{
    /* write CType part */
    pmd_type_write(env, &constructed->type);

    /* write CConstructed part */
    pmd_length_write(env, &constructed->length_obj);
}


/* ============================================================================================= */
/* CDebugInfo functions (these functions is also used as CDebugInfoDLL object functions)         */
/* ============================================================================================= */

#if (PMD_FILE_FORMAT >= 610)
pmd_debuginfo *pmd_debuginfo_create(pmd_env *env, const char *filename, unsigned int filetype)
{
    /* Create CDebugInfo / CDebugInfoDLL object */
    pmd_debuginfo *debuginfo = (pmd_debuginfo *)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_debuginfo));

    /* initialize CNamedObject - Determines if a CDebugInfo or CDebugInfoDLL object is created */
    if (filetype == 2)
    {
        /* ET_EXEC = 2  Executable file   */
        pmd_namedobj_init(env, &debuginfo->namedobj, filename, FALSE, PMD_CLASS_DEBUGINFO, ++env->last_object_id);
    }
    else if (filetype == 3)
    {
        /* ET_DYN  = 3 Shared object file */
        pmd_namedobj_init(env, &debuginfo->namedobj, filename, FALSE, PMD_CLASS_DEBUGINFODLL, ++env->last_object_id);
    }
    else
    {
        /* Not supported */
        pmd_namedobj_init(env, &debuginfo->namedobj, filename, FALSE, PMD_CLASS_NULL, ++env->last_object_id);
    }

    /* Initialise lists */
    debuginfo->file_info_list = list_new();
    debuginfo->func_info_list = list_new();
    debuginfo->line_info_list = list_new();

    /* Init type of file              */
    /* ET_EXEC = 2 Executable file    */
    /* ET_DYN  = 3 Shared object file */
    debuginfo->type = filetype;

    /* Init start of fileinfo id */
    debuginfo->current_fileinfo_id = 0;

    /* Init pointer to current compile unit element */
    debuginfo->current_compile_unit_element = NULL;

    debuginfo->next = NULL;

    return debuginfo;
}

void pmd_debuginfo_write(pmd_env* env, pmd_debuginfo *debuginfo)
{
    list_element *ptr = NULL;

    /* write CNamedObject part */
    pmd_namedobj_write(env, &debuginfo->namedobj);

    /* write number of FileInfo objects */
    pmd_write_dword(env, debuginfo->file_info_list->count);

    /* write all FileInfo objects */
    ptr = list_iterator_reset(debuginfo->file_info_list);
    while (ptr)
    {
        pmd_debuginfo_FileInfo *file_info = (pmd_debuginfo_FileInfo *)ptr->data;

        /* write file name */
        pmd_write_string(env, file_info->file_name);

        /* write low address */
        pmd_write_ddword(env, file_info->low_address);

        /* write high address */
        pmd_write_ddword(env, file_info->high_address);

        /* write compile dir */
        if (file_info->compile_dir)
        {
            /* Compile dir given - write string */
            pmd_write_string(env, file_info->compile_dir);
        }
        else
        {
            /* Compile dir not given - write empty string */
            pmd_write_string(env, "");
        }

        /* write file info id */
        pmd_write_dword(env, file_info->id);

        /* Next element */
        ptr = list_iterator_next(debuginfo->file_info_list);
    }

    /* write number of FuncInfo objects */
    pmd_write_dword(env, debuginfo->func_info_list->count);

    /* write all FuncInfo objects */
    ptr = list_iterator_reset(debuginfo->func_info_list);
    while (ptr)
    {
        pmd_debuginfo_FuncInfo *func_info = (pmd_debuginfo_FuncInfo *)ptr->data;

        /* write function name */
        pmd_write_string(env, func_info->function_name);

        /* write low address */
        pmd_write_ddword(env, func_info->low_address);

        /* write high address */
        pmd_write_ddword(env, func_info->high_address);

        /* write line where function is declared */
        pmd_write_dword(env, func_info->declared_line);

        /* write file info id */
        pmd_write_dword(env, func_info->id);

        /* Next element */
        ptr = list_iterator_next(debuginfo->func_info_list);
    }

    /* write number of LineInfo objects */
    pmd_write_dword(env, debuginfo->line_info_list->count);

    /* write all LineInfo objects */
    ptr = list_iterator_reset(debuginfo->line_info_list);
    while (ptr)
    {
        pmd_debuginfo_LineInfo *line_info = (pmd_debuginfo_LineInfo *)ptr->data;

        /* write address */
        pmd_write_ddword(env, line_info->address);

        /* write line number */
        pmd_write_dword(env, line_info->lineNo);

        /* Next element */
        ptr = list_iterator_next(debuginfo->line_info_list);
    }
}
#endif

/* ============================================================================================= */
/* CDevice functions */
/* ============================================================================================= */

pmd_device* pmd_device_add(pmd_env* env, unsigned short device_id, const char* name, const char* logical_name)
{
    pmd_device* device = pmd_device_find(env, device_id);

    if (!device && device_id != PMD_DEVICE_GENERAL)
    {
        pmd_device* device_it = env->devices;
        pmd_device* device_last = NULL;

        /* Create and initialize device */
        device = (pmd_device*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_device));

        pmd_namedobj_init(env, &device->namedobj, name, FALSE, PMD_CLASS_DEVICE, ++env->last_object_id);

        device->id = device_id;
        device->logical_name = logical_name;
        device->namedobj.managedobj.flags |= pmd_constant_lookup_device_flags(device_id);

        /* Set XTI master device ID */
#if (defined AUTOGEN_DEVICE_ID && defined AUTOGEN_DEVICE_XTI_MASTER_DEVICE)
        if (device_id == AUTOGEN_DEVICE_ID)
        {
            device->namedobj.managedobj.flags |= PMD_DEVICE_HAS_XTI_MASTER_DEVICE;
            device->xti_master_device_id = AUTOGEN_DEVICE_XTI_MASTER_DEVICE;
        }
#endif

        /* Insert device in list */
        while (device_it && device_it->id < device_id)
        {
            device_last = device_it;
            device_it = device_it->next;
        }

        if (device_last)
        {
            device->next = device_last->next;
            device_last->next = device;
        }
        else
        {
            device->next = env->devices;
            env->devices = device;
        }

        ++env->n_devices;
    }

    return device;
}

pmd_device* pmd_device_add_default(pmd_env* env, unsigned short device_id)
{
    pmd_device* device = pmd_device_find(env, device_id);

    if (!device && device_id != PMD_DEVICE_GENERAL)
    {
        const char* device_name = pmd_constant_lookup_device_name(device_id);
        if (device_name)
        {
            device = pmd_device_add(env, device_id, device_name, pmd_constant_lookup_device_logical_name(device_id));

            device->namedobj.managedobj.flags |= pmd_constant_lookup_device_flags(device_id);
        }
    }

    return device;
}

pmd_device* pmd_device_find(pmd_env* env, unsigned short device_id)
{
    pmd_device* device = NULL;

	if (device_id != PMD_DEVICE_GENERAL)
    {
        if (device_id == AUTOGEN_DEVICE_CURRENT)
        {
            device_id = env->device_id;
        }

        device = env->devices;
        while (device && device->id < device_id)
        {
            device = device->next;
        }

        if (device && device->id != device_id)
        {
            device = NULL;
        }
    }

    return device;
}

void pmd_device_write_all(pmd_env* env)
{
    pmd_write_dword(env, env->n_devices);

    if (env->n_devices > 0)
    {
        pmd_device* device = env->devices;
        while (device)
        {
			pmd_device_write(env, device);

            device = device->next;
        }
    }
}

void pmd_device_write(pmd_env* env, const pmd_device* device)
{
    /* Write CNamedObject part */
    pmd_namedobj_write(env, &device->namedobj);

	/* Write logical name */
	pmd_write_string(env, device->logical_name);

	/* Write ID */
	pmd_write_dword(env, device->id);

    /* Write entry points */
    pmd_entry_points_write_all(env, device->n_entry_points, device->entry_points);

    /* Write info groups */
    pmd_info_groups_write_all(env, device->n_info_groups, device->info_groups);

    /* Write environment variables */
	pmd_env_vars_write_all(env, device->n_env_vars, device->env_vars, PMD_WRITE_ENVVAR_DATA | PMD_WRITE_COUNTERS);

    /* Write message types */
    pmd_msgtypes_write_all(env, device->n_msgtypes, device->msgtypes, PMD_WRITE_MSG_DATA | PMD_WRITE_COUNTERS);

    /* Write XTI master device */
    if (device->namedobj.managedobj.flags & PMD_DEVICE_HAS_XTI_MASTER_DEVICE)
    {
        pmd_write_dword(env, device->xti_master_device_id);
    }
}

/* ============================================================================================= */
/* CEntryPoint functions */
/* ============================================================================================= */

pmd_entry_point* pmd_entry_point_create(pmd_env* env, unsigned short device_id, const char* name, unsigned short id, const pmd_typ* ref_type)
{
    pmd_entry_point* entry_point = pmd_entry_point_find(env, device_id, id, FALSE);
    if (!entry_point)
    {
         /* allocate CEntryPoint object */
        entry_point = (pmd_entry_point*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_entry_point));

        /* initialize CManagedObject part */
        pmd_managedobj_init(&entry_point->managedobj, FALSE, PMD_CLASS_ENTRY_POINT, ++env->last_object_id);

        /* initialize CEntryPoint part */
        entry_point->name     = name;
        entry_point->id       = id;
        entry_point->ref_type = ref_type;

        /* Add entry point to list of entry points */
        pmd_entry_point_add(env, device_id, entry_point);
    }

    return entry_point;
}

pmd_entry_point* pmd_entry_point_subtree_create(pmd_env* env, unsigned short id, unsigned int info_group_id)
{
    pmd_entry_point* entry_point = pmd_entry_point_find(env, PMD_DEVICE_GENERAL, id, TRUE);
    if (!entry_point)
    {
        /* allocate CEntryPointSubTree object */
        entry_point = (pmd_entry_point*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_entry_point_subtree));

        /* initialize CManagedObject part */
        pmd_managedobj_init(&entry_point->managedobj, FALSE, PMD_CLASS_ENTRY_POINT_SUBTREE, ++env->last_object_id);

        /* initialize CEntryPoint part */
        entry_point->name     = pmd_constant_lookup_entry_point(id);
        entry_point->id       = id;
        entry_point->ref_type = NULL;

        /* Add entry point to list of entry points */
        pmd_entry_point_subtree_add(env, entry_point);
    }

    if (info_group_id != PMD_INFO_TYPE_NONE)
    {
        /* Set dependency to info group */
        entry_point->managedobj.flags |= PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY;

        ((pmd_entry_point_subtree*)entry_point)->info_group_id = info_group_id;

        /* Add info group */
        pmd_info_group_add(env, PMD_DEVICE_GENERAL, info_group_id, 0);
    }

    return entry_point;
}

#if (PMD_FILE_FORMAT >= 600)
void pmd_entry_point_subtree_el_add(pmd_env* env, unsigned short device_id, pmd_entry_point* entry_point, const char* name, unsigned long long id, const pmd_typ* ref_type)
#else
void pmd_entry_point_subtree_el_add(pmd_env* env, unsigned short device_id, pmd_entry_point* entry_point, const char* name, unsigned int id, const pmd_typ* ref_type)
#endif
{
    pmd_entry_point_subtree* entry_point_subtree = (pmd_entry_point_subtree*)entry_point;

    pmd_entry_point_subtree_el* el_it = entry_point_subtree->el;
    pmd_entry_point_subtree_el* el_last = NULL;

    /* allocate CEntryPointSubTreeElement object */
    pmd_entry_point_subtree_el* el = (pmd_entry_point_subtree_el*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_entry_point_subtree_el));

    /* Initialize element */
    el->namedobj.name = name;
    el->id            = id;
    el->type          = ref_type;
    el->device_id     = device_id;

    el->next = NULL;

    /* Add element to list */
    while (el_it && el_it->id < id)
    {
        el_last = el_it;
        el_it   = el_it->next;
    }

    if (el_last)
    {
        el->next      = el_last->next; 
        el_last->next = el;
    }
    else
    {
        el->next = entry_point_subtree->el;
        entry_point_subtree->el = el;
    }

    ++entry_point_subtree->n_el;

    /* Update info map */
    if (entry_point_subtree->entry_point.managedobj.flags & PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY)
    {
        pmd_info_add(env, PMD_DEVICE_GENERAL, entry_point_subtree->info_group_id, name, (unsigned int)id, 0, 0, 0, 0, 0);
    }
}

void pmd_entry_point_add(pmd_env* env, unsigned short device_id, pmd_entry_point* entry_point)
{
    pmd_device* device = pmd_device_find(env, device_id);

    pmd_entry_point* last_entry_point = NULL;
    pmd_entry_point** entry_point_list = device ? &device->entry_points : &env->entry_points;
    pmd_entry_point* entry_point_it = *entry_point_list;

    /* find position in list where entry point object should be inserted */
    while (entry_point_it && entry_point_it->id < entry_point->id)
    {
        last_entry_point = entry_point_it;
        entry_point_it = entry_point_it->next;
    }

    /* insert in front of list */
    if (!last_entry_point)
    {
        entry_point->next = *entry_point_list;
        *entry_point_list = entry_point;
    }
    /* insert at arbitrary position */
    else
    {
        entry_point->next = last_entry_point->next;
        last_entry_point->next = entry_point;
    }

    if (device)
    {
        device->n_entry_points++;
    }
    else
    {
        env->n_entry_points++;
    }
}

pmd_entry_point* pmd_entry_point_find(pmd_env* env, unsigned short device_id, unsigned short id, int is_subtree)
{
    pmd_device* device = pmd_device_find(env, device_id);

    pmd_entry_point* entry_point_it = device ? device->entry_points : env->entry_points;
    if (is_subtree)
    {
        entry_point_it = device ? device->entry_point_subtrees : env->entry_point_subtrees;
    }

    /* find entry point */
    while (entry_point_it && entry_point_it->id < id)
    {
        entry_point_it = entry_point_it->next;
    }

    if (entry_point_it && entry_point_it->id == id)
    {
        return entry_point_it;
    }

    return NULL;
}

void pmd_entry_point_subtree_add(pmd_env* env, pmd_entry_point* entry_point)
{
    pmd_entry_point* last_entry_point = NULL;
    pmd_entry_point** entry_point_list = &env->entry_point_subtrees;
    pmd_entry_point* entry_point_it = *entry_point_list;

    /* find position in list where entry point object should be inserted */
    while (entry_point_it && entry_point_it->id < entry_point->id)
    {
        last_entry_point = entry_point_it;
        entry_point_it = entry_point_it->next;
    }

    /* insert in front of list */
    if (!last_entry_point)
    {
        entry_point->next = *entry_point_list;
        *entry_point_list = entry_point;
    }
    /* insert at arbitrary position */
    else
    {
        entry_point->next = last_entry_point->next;
        last_entry_point->next = entry_point;
    }

    env->n_entry_point_subtrees++;
}

void pmd_entry_point_subtree_el_write(pmd_env* env, const pmd_entry_point_subtree_el* el)
{
    /* write CNamedObject part */
    pmd_namedobj_write(env, &el->namedobj);

    /* write CEntryPointSubTreeElement part */
#if (PMD_FILE_FORMAT >= 600)
    pmd_write_dword(env, (unsigned int)el->id);
#else
    pmd_write_dword(env, el->id);
#endif
    pmd_write_objid(env, &el->type->managedobj);
    pmd_write_word(env, el->device_id);

}

void pmd_entry_point_write(pmd_env* env, const pmd_entry_point* entry_point)
{
    /* write CManagedObject part */
    pmd_managedobj_write(env, &entry_point->managedobj);
    
    /* write CEntryPoint part */
    pmd_write_dword(env, entry_point->id);

    if (entry_point->ref_type)
    {
        pmd_write_objid(env, &entry_point->ref_type->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }

    /* Write CEntryPointSubTree part */
    if (entry_point->managedobj.class_id == PMD_CLASS_ENTRY_POINT_SUBTREE)
    {
        pmd_entry_point_subtree* entry_point_subtree = (pmd_entry_point_subtree*) entry_point;
        pmd_entry_point_subtree_el* entry_point_subtree_el = entry_point_subtree->el;

        if (entry_point->managedobj.flags & PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY)
        {
            pmd_write_dword(env, entry_point_subtree->info_group_id);
        }

        /* write number of sequence elements */
        pmd_write_dword(env, entry_point_subtree->n_el);
            
        /* write sequence elements */
        while (entry_point_subtree_el)
        {
            pmd_entry_point_subtree_el_write(env, entry_point_subtree_el);
        
            entry_point_subtree_el = entry_point_subtree_el->next;
        }
    }
}

void pmd_entry_points_write_all(pmd_env* env, unsigned int n_entry_points, const pmd_entry_point* entry_points)
{
    pmd_write_dword(env, n_entry_points);

    while (entry_points)
    {
        pmd_entry_point_write(env, entry_points);

        entry_points = (const pmd_entry_point*)entry_points->next;
    }
}


/* ============================================================================================= */
/* CFillerType functions */
/* ============================================================================================= */

void pmd_filler_init(pmd_env* env, pmd_filler* filler, unsigned short class_id, const char* name, unsigned int n_bits)
{
    /* initialize CType part */
    pmd_type_init(env, &filler->type, class_id, name);

    /* initialize CFillerType part */
    filler->n_bits = n_bits;
}

void pmd_filler_clone(pmd_filler* filler, const pmd_filler* org_filler)
{
    /* clone CType part */
    pmd_type_clone(&filler->type, &org_filler->type);

    /* clone CFillerType part */
    filler->n_bits = org_filler->n_bits;
}

void pmd_filler_write(pmd_env* env, const pmd_filler* filler)
{
    /* write CType part */
    pmd_type_write(env, &filler->type);
    
    /* write CFillerType part */
    pmd_write_word(env, filler->n_bits);
}

/* ============================================================================================= */
/* CFillerTypeDynamic functions */
/* ============================================================================================= */

pmd_filler_dyn* pmd_filler_dyn_create(pmd_env* env, const char* name, unsigned int n_bits, 
                                      unsigned int alignment, const pmd_seq* ref_seq)
{
    /* allocate CFillerTypeDynamic object */
    pmd_filler_dyn* filler_dyn = (pmd_filler_dyn*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_filler_dyn));

    /* initialize CFillerType part */
    pmd_filler_init(env, &filler_dyn->filler, PMD_CLASS_FILLER_TYPE_DYNAMIC, name, n_bits);

    filler_dyn->alignment = alignment;
    filler_dyn->ref_type  = &ref_seq->constructed.type;

    return filler_dyn;
}

pmd_typ* pmd_filler_dyn_clone(pmd_env* env, const pmd_filler_dyn* org_filler_dyn)
{
    /* create CFillerTypeDynamic object */
    pmd_filler_dyn* filler_dyn = pmd_filler_dyn_create(env, NULL, 
        org_filler_dyn->filler.n_bits, org_filler_dyn->alignment, (const pmd_seq*)org_filler_dyn->ref_type);

    /* clone CFillerType part */
    pmd_filler_clone(&filler_dyn->filler, &org_filler_dyn->filler);

    return &filler_dyn->filler.type;
}

void pmd_filler_dyn_write(pmd_env* env, const pmd_filler_dyn* filler_dyn)
{
    /* write CFillerType part */
    pmd_filler_write(env, &filler_dyn->filler);
    
    /* write CFillerTypeDynamic part */
    pmd_write_word(env, filler_dyn->alignment);

    if (filler_dyn->ref_type)
    {
        pmd_write_objid(env, &filler_dyn->ref_type->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }
}

/* ============================================================================================= */
/* CFillerTypeStatic functions */
/* ============================================================================================= */

pmd_filler_static* pmd_filler_static_create(pmd_env* env, const char* name, unsigned int n_bits)
{
    /* allocate CFillerTypeStatic object */
    pmd_filler_static* filler_static = (pmd_filler_static*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_filler_static));

    /* initialize CFillerType part */
    pmd_filler_init(env, &filler_static->filler, PMD_CLASS_FILLER_TYPE_STATIC, name, n_bits);

    /* initialize CFillerTypeStatic part */
     /* no member attributes */

    return filler_static;
}

pmd_typ* pmd_filler_static_clone(pmd_env* env, const pmd_filler_static* org_filler_static)
{
    /* create CFillerTypeStatic object */
    pmd_filler_static* filler_static = pmd_filler_static_create(env, NULL, org_filler_static->filler.n_bits);

    /* clone CFillerType part */
    pmd_filler_clone(&filler_static->filler, &org_filler_static->filler);

    return &filler_static->filler.type;
}

void pmd_filler_static_write(pmd_env* env, const pmd_filler_static* filler)
{
    /* write CFillerType part */
    pmd_filler_write(env, &filler->filler);
    
    /* write CFillerTypeStatic part */
     /* no member attributes */
}

/* ============================================================================================= */
/* CLength functions */
/* ============================================================================================= */

void pmd_length_clear(pmd_len* length_obj)
{
    pmd_length_init(length_obj, 0, PMD_LENGTH_ALGORITHM_NOT_SPECIFIED);
}

void pmd_length_clone(pmd_len* length_obj, const pmd_len* org_length_obj)
{
    /* clone CTag part */
    pmd_tag_clone(&length_obj->tag, &org_length_obj->tag);

    /* clone CLength part */
    length_obj->length = org_length_obj->length;
    length_obj->alg    = org_length_obj->alg;
}

void pmd_length_init(pmd_len* length_obj, int length, unsigned short algorithm)
{
    /* clear CTag part */
    pmd_tag_clear(&length_obj->tag);

    length_obj->length = length;
    length_obj->alg    = algorithm;
}

void pmd_length_init_as_many_as_possible(pmd_len* length_obj, const pmd_seq* seq, unsigned short algorithm)
{
    pmd_tag_init(&length_obj->tag, &seq->constructed.type, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

    length_obj->length = 0;
    length_obj->alg    = algorithm;
}

void pmd_length_init_as_tag(pmd_len* length_obj, const pmd_typ* type)
{
    pmd_tag_init(&length_obj->tag, type, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

    length_obj->length = 0;
    length_obj->alg    = PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH;
}

/* Initialize length object from reference item */
void pmd_length_init_reference(pmd_env* env, pmd_len* length_obj, const pmd_ref* ref_list, autogen_ref* org_ref)
{
    pmd_tag_init_reference(env, &length_obj->tag, ref_list, org_ref->name, org_ref);

    length_obj->length = org_ref->value;
    length_obj->alg    = org_ref->algorithm;
}

/* Initialize length object from reference item and add +1 to reference*/
void pmd_length_init_reference_add_1(pmd_env* env, pmd_len* length_obj, const pmd_ref* ref_list, autogen_ref* org_ref)
{
    pmd_tag_init_reference(env, &length_obj->tag, ref_list, org_ref->name, org_ref);

    if (org_ref->type == referenceTypeTransformation)
    {
        length_obj->length = org_ref->value;
        length_obj->alg    = org_ref->algorithm;

        switch (org_ref->algorithm)
        {
        case PMD_LENGTH_ALGORITHM_FIXEDLENGTH:
        case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MINUS_N:
            length_obj->length = length_obj->length + 1;
            break;

        case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N:
            length_obj->alg = PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N_PLUS_1;
            break;

        case PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH:
            length_obj->length = length_obj->length + 1;
            break;
        }
    }
    else
    {
        length_obj->length = 1;
        length_obj->alg    = PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH;
    }
}

void pmd_length_init_from_item(pmd_env* env, pmd_len* length_obj, autogen_item* item, const pmd_seq* seq, const pmd_ref* ref_lst)
{
    /* if dynamic, find reference */
    if (item->agg_type == AGG_TYPE_DYNAMIC_REF)
    {
        autogen_ref* ref = reference_find(item);

        if (item->base.subtype == AUTOGEN_ITEM_STRING &&
            prop_has(&item->base, PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH))
        {
            pmd_length_init_reference_add_1(env, length_obj, ref_lst, ref);
        }
        else
        {
            pmd_length_init_reference(env, length_obj, ref_lst, ref);
        }
    }
    else if (item->agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE)
    {
        pmd_length_init_as_many_as_possible(length_obj, seq, PMD_LENGTH_ALGORITHM_AS_MANY_AS_POSSIBLE);
    }
    else if (item->agg_type == AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH)
    {
        pmd_length_init_as_many_as_possible(length_obj, seq, PMD_LENGTH_ALGORITHM_UNKNOWN);
    }
    else if (item->agg_type == AGG_TYPE_DYNAMIC_ZEROTERMINATED)
    {
        pmd_length_init(length_obj, 0, PMD_LENGTH_ALGORITHM_NOT_SPECIFIED);
    }
    else if (item->agg_type == AGG_TYPE_DYNAMIC_OPTIONAL)
    {
        pmd_length_init_as_many_as_possible(length_obj, seq, PMD_LENGTH_ALGORITHM_OPTIONAL);
    }
    else if (item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
    {
        pmd_tag_init(&length_obj->tag, &seq->constructed.type, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
    }
    else if (item->agg_type == AGG_TYPE_FIXED_SINGLE || item->agg_type == AGG_TYPE_FIXED_MULTIPLE)
    {
        int length = (item->base.subtype == AUTOGEN_ITEM_STRING) ? (int)((autogen_item_string*)item)->length : item->agg_n;

        pmd_length_init(length_obj, length, PMD_LENGTH_ALGORITHM_FIXEDLENGTH);
    }
    else
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_set_length_info(): Default case met. item->agg_type is 0x%8.8X", item->agg_type);
    }
}

void pmd_length_write(pmd_env* env, const pmd_len* length_obj)
{
    /* write CTag part */
    pmd_tag_write(env, &length_obj->tag);

    /* write CLength part */
    pmd_write_word(env, (unsigned short)length_obj->length);
    pmd_write_word(env, length_obj->alg);

}

/* ============================================================================================= */
/* CManagedObject functions */
/* ============================================================================================= */

void pmd_managedobj_clear(pmd_managedobj* managed_obj, int stream_obj_id)
{
    pmd_managedobj_init(managed_obj, stream_obj_id, PMD_CLASS_NULL, 0);
}

void pmd_managedobj_clone(pmd_managedobj* managed_obj, const pmd_managedobj* org_managed_obj)
{
    managed_obj->class_id  = org_managed_obj->class_id;
    managed_obj->object_id = org_managed_obj->object_id;

    managed_obj->flags = org_managed_obj->flags;

    managed_obj->stream_out    = FALSE;
    managed_obj->stream_obj_id = org_managed_obj->stream_obj_id;
}

void pmd_managedobj_init(pmd_managedobj* managed_obj, int stream_obj_id, 
                         unsigned short class_id, unsigned int object_id)
{
    managed_obj->class_id  = class_id;
    managed_obj->object_id = object_id;

    managed_obj->flags = 0;

    managed_obj->stream_out          = TRUE;
    managed_obj->stream_obj_id = stream_obj_id;
}

void pmd_managedobj_write(pmd_env* env, const pmd_managedobj* managed_obj)
{
    /* Stream out object ID, if object is not directly aggregated */
    if (managed_obj->stream_obj_id)
    {
        /* Write object ID */
        pmd_write_objid(env, managed_obj);
    }

    /* write flags */
    pmd_write_dword(env, managed_obj->flags);
}

/* ============================================================================================= */
/* CNamedObject functions */
/* ============================================================================================= */

void pmd_namedobj_init(pmd_env* env, pmd_namedobj* namedobj, const char* name, int stream_obj_id, 
                       unsigned short class_id, unsigned int object_id)
{
    /* initialize CManagedObject part */
    pmd_managedobj_init(&namedobj->managedobj, stream_obj_id, class_id, object_id);

    /* initialize CNamedObject part */
    namedobj->name = pmd_heap_strdup_h(env->heap_handle, name);
}

void pmd_namedobj_clone(pmd_namedobj* namedobj, const pmd_namedobj* org_namedobj)
{
    /* clone CManagedObject part */
    pmd_managedobj_clone(&namedobj->managedobj, &org_namedobj->managedobj);

    /* clone CNamedObject part */
    namedobj->name = org_namedobj->name;
}

void pmd_namedobj_write(pmd_env* env, const pmd_namedobj* namedobj)
{
    /* write CManagedObject part */
    pmd_managedobj_write(env, &namedobj->managedobj);

    /* write CNamedObject part */
    pmd_write_string(env, namedobj->name);
}

/* ============================================================================================= */
/* CNumberPresentation functions */
/* ============================================================================================= */

void pmd_number_pres_init(pmd_number_pres* pres, unsigned short class_id, unsigned int object_id)
{
    /* initialize CManagedObject part */
    pmd_managedobj_init(&pres->managedobj, TRUE, class_id, object_id);

    /* initialize CNumberPresentation part */
     /* No member attributes */
}

void pmd_number_pres_clone(pmd_number_pres* pres, const pmd_number_pres* org_pres)
{
    /* clone CManagedObject part */
    pmd_managedobj_clone(&pres->managedobj, &org_pres->managedobj);

    /* clone CNumberPresentation part */
     /* No member attributes */
}

pmd_number_pres* pmd_number_pres_clone_any(pmd_env* env, const pmd_number_pres* org_pres)
{

    pmd_number_pres* pres = NULL;

    if (org_pres)
    {
        switch (org_pres->managedobj.class_id)
        {
        case PMD_CLASS_NUMBER_PRESENTATION_CONDITION:
            pres = pmd_number_pres_cond_clone(env, (pmd_number_pres_cond*)org_pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_CONSTANT:
            pres = pmd_number_pres_const_clone(env, (pmd_number_pres_const*)org_pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_INFO:
            pres = pmd_number_pres_info_clone(env, (pmd_number_pres_info*)org_pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_SIMPLE:
            pres = pmd_number_pres_simple_clone(env, (pmd_number_pres_simple*)org_pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_TIMESTAMP:
            pres = pmd_number_pres_time_clone(env, (pmd_number_pres_time*)org_pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_TRANSFORMATION:
            pres = pmd_number_pres_trans_clone(env, (pmd_number_pres_trans*)org_pres);
            break;
        default:
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_number_pres_clone_any(): Unhandled number presentation: %d [id:%u]", 
                org_pres->managedobj.class_id, org_pres->managedobj.object_id);
        }
    }

    return pres;
}

void pmd_number_pres_write(pmd_env* env, const pmd_number_pres* pres)
{
    /* write CManagedObject part */
    pmd_managedobj_write(env, &pres->managedobj);

    /* write CNumberPresentation part */
     /* No member attributes */
}

void pmd_number_pres_write_any(pmd_env* env, const pmd_number_pres* pres)
{
    if (pres && pres->managedobj.stream_out)
    {
        switch (pres->managedobj.class_id)
        {
        case PMD_CLASS_NUMBER_PRESENTATION_CONDITION:
            pmd_number_pres_cond_write(env, (const pmd_number_pres_cond*)pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_CONSTANT:
            pmd_number_pres_const_write(env, (const pmd_number_pres_const*)pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_INFO:
            pmd_number_pres_info_write(env, (const pmd_number_pres_info*)pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_SIMPLE:
            pmd_number_pres_simple_write(env, (const pmd_number_pres_simple*)pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_TIMESTAMP:
            pmd_number_pres_time_write(env, (const pmd_number_pres_time*)pres);
            break;
        case PMD_CLASS_NUMBER_PRESENTATION_TRANSFORMATION:
            pmd_number_pres_trans_write(env, (const pmd_number_pres_trans*)pres);
            break;
        default:
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_number_pres_write_any(): Unhandled number presentation: %d [id:%u]", 
                pres->managedobj.class_id, pres->managedobj.object_id);
        }
    }
}

/* ============================================================================================= */
/* CNumberPresentationConstant functions */
/* ============================================================================================= */

pmd_number_pres* pmd_number_pres_const_create(pmd_env* env, const char* text)
{
    pmd_number_pres_const* pres_const = NULL;
    unsigned int index = 0;
    unsigned int object_id = 0;
    int stream_out = TRUE;

    /* Add text string to string pool */
    pmd_stringpool_add(text, 0, &index);

    /* If text doesn't exist in pool, allocate new object ID and update ID in the pool */
    object_id = pmd_stringpool_get_data(index);
    if (!object_id)
    {
        object_id = ++env->last_object_id;

        pmd_stringpool_update_data(index, object_id);
    }
    /* else, the object should be reused and not be generated lated on */
    else
    {
        stream_out = FALSE;
    }

    /* allocate CNumberPresentationConstant object */
    pres_const = (pmd_number_pres_const*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_const));

    pres_const->number_pres.managedobj.stream_out = stream_out;

    /* initialize CNumberPresentation part */
    pmd_number_pres_init(&pres_const->number_pres, PMD_CLASS_NUMBER_PRESENTATION_CONSTANT, object_id);

    /* initialize CNumberPresentationConstant part */
    pres_const->text = pmd_heap_strdup_h(env->heap_handle, text);

    return &pres_const->number_pres;
}

pmd_number_pres* pmd_number_pres_const_clone(pmd_env* env, const pmd_number_pres_const* org_pres_const)
{
    /* create CNumberPresentationConstant object */
    pmd_number_pres* pres = pmd_number_pres_const_create(env, org_pres_const->text);

    /* clone CNumberPresentation object */
    pmd_number_pres_clone(pres, &org_pres_const->number_pres);

    return pres;
}

void pmd_number_pres_const_write(pmd_env* env, const pmd_number_pres_const* pres_const)
{
    /* write CNumberPresentation part */
    pmd_number_pres_write(env, &pres_const->number_pres);

    /* write CNumberPresentationConstant part */
    pmd_write_string(env, pres_const->text);
}

/* ============================================================================================= */
/* CNumberPresentationInfo functions */
/* ============================================================================================= */

pmd_number_pres* pmd_number_pres_info_create(pmd_env* env, unsigned int info_group_id, unsigned short device_id, const pmd_number_pres* default_pres)
{
    pmd_number_pres_info* pres_info = NULL;
    pmd_number_pres_info_reuse* last_pres_info_reuse = NULL;
    pmd_number_pres_info_reuse* pres_info_reuse_it = env->pres_info_reuse;

    /* try reusing presentation object */
    if (pres_info_reuse_it && !default_pres)
    {
        while (pres_info_reuse_it && pres_info_reuse_it->pres_info->info_group_id < info_group_id && pres_info_reuse_it->pres_info->device_id < device_id)
        {
            last_pres_info_reuse = pres_info_reuse_it;
            pres_info_reuse_it = pres_info_reuse_it->next;
        }

        /* found... clone it! */
        if (pres_info_reuse_it && pres_info_reuse_it->pres_info->info_group_id == info_group_id && pres_info_reuse_it->pres_info->device_id == device_id)
        {
            pres_info = (pmd_number_pres_info*)pmd_number_pres_info_clone(env, pres_info_reuse_it->pres_info);
        }
    }
    if (!pres_info)
    {
        /* allocate CNumberPresentationConstant object */
        pres_info = (pmd_number_pres_info*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_info));

        /* initialize CNumberPresentation part */
        pmd_number_pres_init(&pres_info->number_pres, PMD_CLASS_NUMBER_PRESENTATION_INFO, ++env->last_object_id);

        /* initialize CNumberPresentationConstant part */
        pres_info->info_group_id = info_group_id;
		pres_info->device_id     = device_id;
        pres_info->default_pres  = default_pres;

        /* save presentation object for later */
        {
            pmd_number_pres_info_reuse* pres_info_reuse = 
                (pmd_number_pres_info_reuse*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_info_reuse));

            pres_info_reuse->pres_info = pres_info;

            if (last_pres_info_reuse)
            {
                last_pres_info_reuse->next = pres_info_reuse;
            }
            else
            {
                env->pres_info_reuse = pres_info_reuse;
            }

            pres_info_reuse->next = pres_info_reuse_it;
        }
    }
    return &pres_info->number_pres;
}

pmd_number_pres* pmd_number_pres_info_clone(pmd_env* env, const pmd_number_pres_info* org_pres_info)
{
    /* allocate CNumberPresentationSimple object */
    pmd_number_pres_info* pres_info = 
        (pmd_number_pres_info*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_info));

    /* clone CNumberPresentationInfo part */
    pres_info->info_group_id = org_pres_info->info_group_id;
	pres_info->device_id     = org_pres_info->device_id;
    pres_info->default_pres  = org_pres_info->default_pres;

    /* clone CNumberPresentation object */
    pmd_number_pres_clone(&pres_info->number_pres, &org_pres_info->number_pres);

    return &pres_info->number_pres;
}

void pmd_number_pres_info_write(pmd_env* env, const pmd_number_pres_info* pres_info)
{
    /* write CNumberPresentation part */
    pmd_number_pres_write(env, &pres_info->number_pres);

    /* write CNumberPresentationInfo part */
    if (pres_info->default_pres)
    {
        pmd_write_objid(env, &pres_info->default_pres->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }

	/* Write Info group ID */
    pmd_write_dword(env, pres_info->info_group_id);

	/* Write device ID */
    pmd_write_dword(env, pres_info->device_id);
}

/* ============================================================================================= */
/* CNumberPresentationSimple functions */
/* ============================================================================================= */

pmd_number_pres* pmd_number_pres_simple_create(pmd_env* env, unsigned int type, const char* unit)
{
    pmd_number_pres_simple* pres_simple = NULL;
    pmd_number_pres_simple_reuse* last_pres_simple_reuse = NULL;
    pmd_number_pres_simple_reuse* pres_simple_reuse_it = env->pres_simple_reuse;

    if (unit == NULL)
    {
        unit = "";
    }

    /* try reusing presentation object */
    if (pres_simple_reuse_it)
    {
        while (pres_simple_reuse_it && pres_simple_reuse_it->pres_simple->type < type)
        {
            last_pres_simple_reuse = pres_simple_reuse_it;
            pres_simple_reuse_it = pres_simple_reuse_it->next;
        }
        while (pres_simple_reuse_it && 
            pres_simple_reuse_it->pres_simple->type == type && 
            strcmp(pres_simple_reuse_it->pres_simple->unit, unit) < 0)
        {
            last_pres_simple_reuse = pres_simple_reuse_it;
            pres_simple_reuse_it = pres_simple_reuse_it->next;
        }

        /* found... clone it! */
        if (pres_simple_reuse_it &&
            pres_simple_reuse_it->pres_simple->type == type && 
            strcmp(pres_simple_reuse_it->pres_simple->unit, unit) == 0)
        {
            pres_simple = (pmd_number_pres_simple*)
                pmd_number_pres_simple_clone(env, pres_simple_reuse_it->pres_simple);
        }
    }
    if (!pres_simple)
    {
        /* allocate CNumberPresentationSimple object */
        pres_simple = (pmd_number_pres_simple*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_simple));

        /* initialize CNumberPresentation part */
        pmd_number_pres_init(&pres_simple->number_pres, PMD_CLASS_NUMBER_PRESENTATION_SIMPLE, ++env->last_object_id);

        /* initialize CNumberPresentationSimple part */
        pres_simple->type = type;
        pres_simple->unit = pmd_heap_strdup_h(env->heap_handle, unit);

        /* save presentation object for later */
        {
            pmd_number_pres_simple_reuse* pres_simple_reuse = 
                (pmd_number_pres_simple_reuse*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_simple_reuse));

            pres_simple_reuse->pres_simple = pres_simple;

            if (last_pres_simple_reuse)
            {
                last_pres_simple_reuse->next = pres_simple_reuse;
            }
            else
            {
                env->pres_simple_reuse = pres_simple_reuse;
            }

            pres_simple_reuse->next = pres_simple_reuse_it;
        }
    }

    return &pres_simple->number_pres;
}

pmd_number_pres* pmd_number_pres_simple_clone(pmd_env* env, const pmd_number_pres_simple* org_pres_simple)
{
    /* allocate CNumberPresentationSimple object */
    pmd_number_pres_simple* pres_simple = 
        (pmd_number_pres_simple*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_simple));

    /* clone CNumberPresentation object */
    pmd_number_pres_clone(&pres_simple->number_pres, &org_pres_simple->number_pres);

    /* clone CNumberPresentationSimple object */
    pres_simple->type = org_pres_simple->type;
    pres_simple->unit = org_pres_simple->unit;

    return &pres_simple->number_pres;
}

void pmd_number_pres_simple_write(pmd_env* env, const pmd_number_pres_simple* pres_simple)
{
    /* write CNumberPresentation part */
    pmd_number_pres_write(env, &pres_simple->number_pres);

    /* write CNumberPresentationSimple part */
    pmd_write_word(env, pres_simple->type);
    pmd_write_string(env, pres_simple->unit);
}

/* ============================================================================================= */
/* CNumberPresentationCondition functions */
/* ============================================================================================= */

pmd_number_pres_cond* pmd_number_pres_cond_create(pmd_env* env, const pmd_number_pres* default_pres)
{
    /* allocate CNumberPresentationCondition object */
    pmd_number_pres_cond* pres_cond = 
        (pmd_number_pres_cond*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_cond));

    /* initialize CNumberPresentation part */
    pmd_number_pres_init(&pres_cond->number_pres, PMD_CLASS_NUMBER_PRESENTATION_CONDITION, ++env->last_object_id);

    /* initialize CNumberPresentationCondition part */
    pres_cond->n_pres_cond_el = 0;
    pres_cond->pres_cond_el   = NULL;

    pres_cond->default_pres = default_pres;
    pres_cond->tag = NULL;
    pres_cond->tag_name = "";

    return pres_cond;
}

void pmd_number_pres_cond_set_tag(pmd_env* env, pmd_number_pres_cond* pres_cond, const pmd_typ* typ)
{
    pres_cond->tag      = pmd_tag_create(env, typ, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
    pres_cond->tag_name = typ->name;

    pres_cond->number_pres.managedobj.flags |= PMD_NUMBER_PRESENTATION_CONDITION_HAS_TAG;
}

void pmd_number_pres_cond_el_add(pmd_number_pres_cond* pres_cond, pmd_number_pres_cond_el* pres_cond_el)
{
    /* if first element, just set element */
    if (!pres_cond->pres_cond_el)
    {
        pres_cond->pres_cond_el = pres_cond_el;
    }
    /* else find last element and ad to that */
    else
    {
        pmd_number_pres_cond_el* pres_cond_el_it = pres_cond->pres_cond_el;

        while (pres_cond_el_it->next)
        {
            pres_cond_el_it = pres_cond_el_it->next;
        }

        pres_cond_el_it->next = pres_cond_el;
    }

    pres_cond->n_pres_cond_el++;
}

#if (PMD_FILE_FORMAT >= 600)
void pmd_number_pres_cond_el_add_simple(pmd_env* env, pmd_number_pres_cond* pres_cond, long long id, const char* name)
#else
void pmd_number_pres_cond_el_add_simple(pmd_env* env, pmd_number_pres_cond* pres_cond, int id, const char* name)
#endif
{
    pmd_cond_el* cond_el = pmd_cond_el_int_create(env, id, id);
    pmd_number_pres* pres = pmd_number_pres_const_create(env, name);

    pmd_number_pres_cond_el* pres_cond_el = pmd_number_pres_cond_el_create(env, cond_el, pres);

    pmd_number_pres_cond_el_add(pres_cond, pres_cond_el);
}

pmd_number_pres* pmd_number_pres_cond_clone(pmd_env* env, const pmd_number_pres_cond* org_pres_cond)
{
    /* clone default presentation */
    pmd_number_pres* def_pres = pmd_number_pres_clone_any(env, org_pres_cond->default_pres);

    /* create CNumberPresentationCondition object */
    pmd_number_pres_cond* pres_cond = pmd_number_pres_cond_create(env, def_pres);

    /* clone CNumberPresentation part */
    pmd_number_pres_clone(&pres_cond->number_pres, &org_pres_cond->number_pres);

    /* clone CNumberPresentationCondition part */
    pres_cond->n_pres_cond_el = org_pres_cond->n_pres_cond_el;
    pres_cond->pres_cond_el = pmd_number_pres_cond_el_clone(env, org_pres_cond->pres_cond_el);
    pres_cond->tag = org_pres_cond->tag;
    pres_cond->tag_name = org_pres_cond->tag_name;

    return &pres_cond->number_pres;
}

void pmd_number_pres_cond_write(pmd_env* env, const pmd_number_pres_cond* pres_cond)
{
    const pmd_number_pres_cond_el* pres_cond_el = NULL;
    
    /* write CNumberPresentation part */
    pmd_number_pres_write(env, &pres_cond->number_pres);

    /* write CNumberPresentationCondition part */
    if (pres_cond->default_pres)
    {
        pmd_write_objid(env, &pres_cond->default_pres->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }

    pmd_write_dword(env, pres_cond->n_pres_cond_el);

    /* write elements */
    pres_cond_el = pres_cond->pres_cond_el;
    while (pres_cond_el)
    {
        pmd_number_pres_cond_el_write(env, pres_cond_el);

        pres_cond_el = pres_cond_el->next;
    }

    /* write tag */
    if (pres_cond->number_pres.managedobj.flags & PMD_NUMBER_PRESENTATION_CONDITION_HAS_TAG)
    {
        pmd_tag_write(env, pres_cond->tag);
    }

    /* THESE MUST BE LAST ACTIONS HERE, as it is not part of the presentation object itself */

    /* write conditions and presentations */
    pres_cond_el = pres_cond->pres_cond_el;
    while (pres_cond_el)
    {
        pmd_number_pres_write_any(env, pres_cond_el->pres);
        pmd_cond_el_write_any(env, pres_cond_el->cond_el);

        pres_cond_el = pres_cond_el->next;
    }

    /* write default presentation */
    if (pres_cond->default_pres)
    {
        pmd_number_pres_write_any(env, pres_cond->default_pres);
    }
}

/* ============================================================================================= */
/* CNumberPresentationConditionElement functions */
/* ============================================================================================= */

pmd_number_pres_cond_el* pmd_number_pres_cond_el_create(pmd_env* env, const pmd_cond_el* cond_el, const pmd_number_pres* pres)
{
    /* create CNumberPresentationConditionElement object */
    pmd_number_pres_cond_el* pres_cond_el = 
        (pmd_number_pres_cond_el*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_cond_el));

    /* initialize CManagedObject part */
    pmd_managedobj_init(&pres_cond_el->managedobj, FALSE, PMD_CLASS_NULL, 0);

    pres_cond_el->cond_el = cond_el;
    pres_cond_el->pres    = pres;

    pres_cond_el->next = NULL;

    return pres_cond_el;
}

pmd_number_pres_cond_el* pmd_number_pres_cond_el_clone(pmd_env* env, const pmd_number_pres_cond_el* org_pres_cond_el)
{
    pmd_number_pres_cond_el* pres_cond_el = NULL;

    if (org_pres_cond_el)
    {
        /* clone members of CNumberPresentationConditionElement */
        pmd_number_pres* pres = pmd_number_pres_clone_any(env, org_pres_cond_el->pres);
        pmd_cond_el* cond_el = pmd_cond_el_clone_any(env, org_pres_cond_el->cond_el);

        /* create CNumberPresentationConditionElement object */
        pres_cond_el = pmd_number_pres_cond_el_create(env, cond_el, pres);

        /* clone CManagedObject part */
        pmd_managedobj_clone(&pres_cond_el->managedobj, &org_pres_cond_el->managedobj);

        /* clone children of CNumberPresentationConditionElement */
        pres_cond_el->next = pmd_number_pres_cond_el_clone(env, org_pres_cond_el->next);
    }

    return pres_cond_el;

}

void pmd_number_pres_cond_el_write(pmd_env* env, const pmd_number_pres_cond_el* pres_cond_el)
{
    /* write CManagedObject part */
    pmd_managedobj_write(env, &pres_cond_el->managedobj);

    /* write CNumberPresentationConditionElement part */
    pmd_write_objid(env, &pres_cond_el->pres->managedobj);
    pmd_write_objid(env, &pres_cond_el->cond_el->managedobj);
}

/* ============================================================================================= */
/* CNumberPresentationTimestamp functions */
/* ============================================================================================= */

pmd_number_pres* pmd_number_pres_time_create(pmd_env* env, unsigned int type)
{
    /* allocate CNumberPresentationTimestamp object */
    pmd_number_pres_time* pres_time = 
        (pmd_number_pres_time*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_time));

    /* initialize CNumberPresentation part */
    pmd_number_pres_init(&pres_time->number_pres, PMD_CLASS_NUMBER_PRESENTATION_TIMESTAMP, ++env->last_object_id);

    /* initialize CNumberPresentationTimestamp part */
    pres_time->type = type;

    return &pres_time->number_pres;
}

pmd_number_pres* pmd_number_pres_time_clone(pmd_env* env, const pmd_number_pres_time* org_pres_time)
{
    /* create CNumberPresentationTimestamp object */
    pmd_number_pres* pres = pmd_number_pres_time_create(env, org_pres_time->type);

    /* clone CNumberPresentation object */
    pmd_number_pres_clone(pres, &org_pres_time->number_pres);

    return pres;
}

void pmd_number_pres_time_write(pmd_env* env, const pmd_number_pres_time* pres_time)
{
    /* write CNumberPresentation part */
    pmd_number_pres_write(env, &pres_time->number_pres);

    /* write CNumberPresentationTimestamp part */
    pmd_write_word(env, pres_time->type);
}

/* ============================================================================================= */
/* CNumberPresentationTransform functions */
/* ============================================================================================= */

pmd_number_pres* pmd_number_pres_trans_create(pmd_env* env, double scale, double offset, const char* unit)
{
    /* allocate CNumberPresentationTransform object */
    pmd_number_pres_trans* pres = 
        (pmd_number_pres_trans*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number_pres_trans));

    /* initialize CNumberPresentation part */
    pmd_number_pres_init(&pres->number_pres, PMD_CLASS_NUMBER_PRESENTATION_TRANSFORMATION, ++env->last_object_id);

    /* initialize CNumberPresentationTransform part */
    pres->scale  = scale;
    pres->offset = offset;
    pres->unit   = pmd_heap_strdup_h(env->heap_handle, unit);

    return &pres->number_pres;
}

pmd_number_pres* pmd_number_pres_trans_clone(pmd_env* env, const pmd_number_pres_trans* org_pres_trans)
{
    /* create CNumberPresentationTransform object */
    pmd_number_pres* pres = pmd_number_pres_trans_create(env, org_pres_trans->scale, org_pres_trans->offset, 
        org_pres_trans->unit);

    /* clone CNumberPresentation object */
    pmd_number_pres_clone(pres, &org_pres_trans->number_pres);

    return pres;
}

void pmd_number_pres_trans_write(pmd_env* env, const pmd_number_pres_trans* pres_trans)
{
    char str_float[50];

    /* write CNumberPresentation part */
    pmd_number_pres_write(env, &pres_trans->number_pres);

    /* write CNumberPresentationTransform part */
    sprintf(str_float, "%g", pres_trans->scale);
    pmd_write_string(env, str_float);
    
    sprintf(str_float, "%g", pres_trans->offset);
    pmd_write_string(env, str_float);
    
    pmd_write_string(env, pres_trans->unit);
}

/* ============================================================================================= */
/* CNumberType functions */
/* ============================================================================================= */

pmd_number* pmd_number_create(pmd_env* env, const char* name, int length, unsigned int special_type)
{
    /* allocate CNumberType object */
    pmd_number* number = (pmd_number*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_number));

    /* initialize CPrimitiveType part */
    pmd_type_init(env, &number->primitive.type, PMD_CLASS_NUMBER_TYPE, name);
    number->primitive.special_type = special_type;

    /* initialize CNumberType part */
    number->length = (unsigned int)abs(length);
    if (length < 0)
    {
        number->primitive.type.managedobj.flags |= PMD_NUMBER_IS_SIGNED;
    }

    number->pres = NULL;

    number->default_value     = 0;
    number->default_value_str = NULL;

    return number;
}

pmd_typ* pmd_number_clone(pmd_env* env, const pmd_number* org_number)
{
    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, NULL, org_number->length, org_number->primitive.special_type);

    /* clone CPrimitiveType part */
    pmd_primitive_clone(&number->primitive, &org_number->primitive);

    /* clone CNumberType part */
    number->default_value     = org_number->default_value;
    number->default_value_str = org_number->default_value_str;

    number->pres = pmd_number_pres_clone_any(env, org_number->pres);

    return &number->primitive.type;
}

#if (PMD_FILE_FORMAT >= 600)
void pmd_number_set_default_value(pmd_env* env, pmd_number* number, unsigned long long value, const char* value_str)
#else
void pmd_number_set_default_value(pmd_env* env, pmd_number* number, unsigned int value, const char* value_str)
#endif
{
    number->default_value     = value;
    number->default_value_str = pmd_heap_strdup_h(env->heap_handle, value_str);

    number->primitive.type.managedobj.flags |= PMD_NUMBER_HAS_DEFAULT_VALUE;
}

void pmd_number_set_data_order_little_endian(pmd_number* number)
{
    number->primitive.type.managedobj.flags |= PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN;
}

void pmd_number_write(pmd_env* env, const pmd_number* number)
{
    /* write presentation first */
    pmd_number_pres_write_any(env, number->pres);

    /* write CPrimitiveType part */
    pmd_primitive_write(env, &number->primitive);
    
    /* write CNumberType part */
    if (number->primitive.type.managedobj.flags & PMD_NUMBER_HAS_DEFAULT_VALUE)
    {
#if (PMD_FILE_FORMAT >= 600)
        pmd_write_ddword(env, number->default_value);
#else
        pmd_write_dword(env, number->default_value);
#endif
    }

    pmd_write_objid(env, &number->pres->managedobj);
    pmd_write_word(env, number->length);
}

/* ============================================================================================= */
/* CPrimitiveType functions */
/* ============================================================================================= */

void pmd_primitive_init(pmd_env* env, pmd_primitive* primitive, unsigned short class_id, 
                        const char* name, unsigned int special_type)
{
    /* initialize CType part */
    pmd_type_init(env, &primitive->type, class_id, name);

    /* initialize CPrimitiveType part */
    primitive->special_type = special_type;
}

void pmd_primitive_clone(pmd_primitive* primitive, const pmd_primitive* org_primitive)
{
    /* clone CType part */
    pmd_type_clone(&primitive->type, &org_primitive->type);

    /* clone CPrimitiveType part */
    primitive->special_type = org_primitive->special_type;
}

void pmd_primitive_write(pmd_env* env, const pmd_primitive* primitive)
{
    /* write CType part */
    pmd_type_write(env, &primitive->type);

    /* write CPrimitiveType part */
    pmd_write_word(env, primitive->special_type);
}

/* ============================================================================================= */
/* CSequence functions */
/* ============================================================================================= */

pmd_seq* pmd_seq_create(pmd_env* env, const char* name, unsigned int seq_type)
{
    /* allocate CSequence object */
    pmd_seq* seq = (pmd_seq*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_seq));

    /* initialize CConstructedType part */
    pmd_constructed_init(env, &seq->constructed, PMD_CLASS_SEQUENCE, name);

    /* initialize CSequence part */
    seq->n_seq_el = 0;
    seq->seq_el   = NULL;

    seq->seq_type = seq_type;
    seq->org_seq  = NULL;

    seq->length_type = NULL;

    return seq;
}

pmd_typ* pmd_seq_clone(pmd_env* env, const pmd_seq* org_seq)
{
    /* create CSequence part */
    pmd_seq* seq = pmd_seq_create(env, NULL, org_seq->seq_type);

    /* clone CConstructedType part */
    pmd_constructed_clone(&seq->constructed, &org_seq->constructed);

    /* clone CSequence part */
    seq->org_seq  = org_seq->org_seq;
    seq->n_seq_el = org_seq->n_seq_el;
    seq->seq_el   = pmd_seq_el_clone(env, seq->seq_el);

    seq->length_type = org_seq->length_type;

    return &seq->constructed.type;
}

void pmd_seq_write(pmd_env* env, const pmd_seq* seq)
{
    const pmd_seq_el* seq_el = seq->seq_el;

    /* CConstructedType object */
    pmd_constructed_write(env, &seq->constructed);

    /* write sequence type */
    pmd_write_word(env, seq->seq_type);
    
    /* write number of sequence elements */
    pmd_write_dword(env, seq->n_seq_el);
        
    /* write sequence elements */
    while (seq_el)
    {
        pmd_seq_el_write(env, seq_el);
    
        seq_el = seq_el->next;
    }
}

/* ============================================================================================= */
/* CSequenceElement functions */
/* ============================================================================================= */

pmd_seq_el* pmd_seq_el_create(pmd_env* env, const char* name, const pmd_typ* type)
{
    /* create CSequenceElement object */
    pmd_seq_el* seq_el = (pmd_seq_el*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_seq_el));

    /* initialize CNamedObject part */
    pmd_namedobj_init(env, &seq_el->namedobj, name, FALSE, PMD_CLASS_NULL, 0);

    seq_el->type = type;
    seq_el->next = NULL;

    return seq_el;
}

pmd_seq_el* pmd_seq_el_add(pmd_env* env, pmd_seq* seq, const char* name, const pmd_typ* type)
{
    /* create CSequenceElement */
    pmd_seq_el* seq_el = pmd_seq_el_create(env, name, type);

    /* if first element, just set in choice */
    if (!seq->seq_el)
    {
        seq->seq_el = seq_el;
    }
    /* else set as last element */
    else
    {
        pmd_seq_el* seq_el_it = seq->seq_el;

        while (seq_el_it->next)
        {
            seq_el_it = seq_el_it->next;
        }

        seq_el_it->next = seq_el;
    }

    seq->n_seq_el++;

    return seq_el;
}

pmd_seq_el* pmd_seq_el_add_as_array(pmd_env* env, autogen_item* item, const pmd_typ* type, const pmd_ref* ref_lst, pmd_mod* mod, unsigned int vec_flags, unsigned int el_flags)
{
    pmd_seq_el* seq_el = NULL;

    /* is there an array at all for the item ? */
    if (item->agg_type != AGG_TYPE_FIXED_SINGLE)
    {
        pmd_seq_of* seqof;
        char arr_varname[AUTOGEN_MAX_NAME_LENGTH + 10];

        sprintf(arr_varname, "%s_array", item->varname);

        seqof = pmd_seq_of_create(env, arr_varname, type);
        seqof->constructed.type.managedobj.flags |= vec_flags;

        pmd_length_init_from_item(env, &seqof->constructed.length_obj, item, mod->seq, ref_lst);

        pmd_typedef_type_add(mod, &seqof->constructed.type);

        seq_el = pmd_seq_el_add(env, mod->seq, item->parname, &seqof->constructed.type);

        /* set flags */
        seq_el->namedobj.managedobj.flags |= el_flags;
    }

    return seq_el;
}

pmd_seq_el* pmd_seq_el_clone(pmd_env* env, const pmd_seq_el* org_seq_el)
{
    pmd_seq_el* seq_el = NULL;

    if (org_seq_el)
    {
        /* create CSequenceElement object */
        pmd_seq_el* seq_el = pmd_seq_el_create(env, NULL, org_seq_el->type);

        /* clone CNamedObject part */
        pmd_namedobj_clone(&seq_el->namedobj, &org_seq_el->namedobj);

        /* clone siblings */
        seq_el->next = pmd_seq_el_clone(env, org_seq_el->next);
    }

    return seq_el;
}

void pmd_seq_el_write(pmd_env* env, const pmd_seq_el* seq_el)
{
    /* write CNamedObject part */
    pmd_namedobj_write(env, &seq_el->namedobj);

    /* write CSequenceElement part */
    pmd_write_objid(env, &seq_el->type->managedobj);
}

/* ============================================================================================= */
/* CSequenceOf functions */
/* ============================================================================================= */

pmd_seq_of* pmd_seq_of_create(pmd_env* env, const char* name, const pmd_typ* type)
{
    /* allocate CSequenceOf object */
    pmd_seq_of* seq_of = (pmd_seq_of*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_seq_of));

    /* initialize CConstructedType part */
    pmd_constructed_init(env, &seq_of->constructed, PMD_CLASS_SEQUENCE_OF, name);

    /* initialize CSequenceOf part */
    seq_of->type = type;

    return seq_of;
}

pmd_typ* pmd_seq_of_clone(pmd_env* env, const pmd_seq_of* org_seq_of)
{
    /* create CSequenceOfType part */
    pmd_seq_of* seq_of = pmd_seq_of_create(env, NULL, org_seq_of->type);

    /* clone CConstructedType part */
    pmd_constructed_clone(&seq_of->constructed, &org_seq_of->constructed);

    return &seq_of->constructed.type;
}

void pmd_seq_of_write(pmd_env* env, const pmd_seq_of* seq_of)
{
    /* write CConstructedType part */
    pmd_constructed_write(env, &seq_of->constructed);

    /* write CSequenceOf part */
    pmd_write_objid(env, &seq_of->type->managedobj);
}

/* ============================================================================================= */
/* CStringType functions */
/* ============================================================================================= */

pmd_string* pmd_string_create(pmd_env* env, const char* name, unsigned short char_type, const char* unit)
{
    /* allocate CStringType object */
    pmd_string* str = (pmd_string*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_string));

    /* initialize CPrimitiveType part */
    pmd_primitive_init(env, &str->primitive, PMD_CLASS_STRING_TYPE, name, PMD_NUMBER_SPECIAL_TYPE_NONE);

    /* initialize CStringType part */
    pmd_length_clear(&str->length_obj);

    str->char_type = char_type;
    str->unit      = pmd_heap_strdup_h(env->heap_handle, unit);
    str->bcd_map   = NULL;

    return str;
}

void pmd_string_set_bcd_map(pmd_env* env, pmd_string* str, const char* bcd_map)
{
    str->bcd_map = pmd_heap_strdup_h(env->heap_handle, bcd_map);
    str->primitive.type.managedobj.flags |= PMD_STRING_HAS_BCD_MAP;
}

void pmd_string_set_data_order_little_endian(pmd_string* str)
{
    str->primitive.type.managedobj.flags |= PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN;
}

pmd_typ* pmd_string_clone(pmd_env* env, const pmd_string* org_str)
{
    /* create CStringType object */
    pmd_string* str = pmd_string_create(env, NULL, org_str->char_type, org_str->unit);

    /* clone CPrimitiveType part */
    pmd_primitive_clone(&str->primitive, &org_str->primitive);

    /* clone CStringType part */
    str->bcd_map = org_str->bcd_map;

    pmd_length_clone(&str->length_obj, &org_str->length_obj);

    return &str->primitive.type;
}

void pmd_string_write(pmd_env* env, const pmd_string* str)
{
    /* write CPrimitiveType object */
    pmd_primitive_write(env, &str->primitive);

    /* write CStringType object */
    pmd_write_string(env, str->unit);
    pmd_length_write(env, &str->length_obj);
    pmd_write_word(env, str->char_type);

    if (str->primitive.type.managedobj.flags & PMD_STRING_HAS_BCD_MAP)
    {
        size_t n;
        for (n = 0; n < 16; n++)
        {
            if (n < strlen(str->bcd_map))
            {
                pmd_write_byte(env, (unsigned char)str->bcd_map[n]);
            }
            else
            {
                pmd_write_byte(env, 0);
            }
        }
    }
}

/* ============================================================================================= */
/* CTag functions */
/* ============================================================================================= */

pmd_tag* pmd_tag_create(pmd_env* env, const pmd_typ* ref_type, unsigned short bit_pos, unsigned short rel_pos)
{
    /* allocate CTag object */
    pmd_tag* tag = (pmd_tag*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_tag));

    /* initialize CTag part */
    pmd_tag_init(tag, ref_type, bit_pos, rel_pos);

    return tag;
}

void pmd_tag_clear(pmd_tag* tag)
{
    pmd_managedobj managed_obj;

    /* clear CManagedObject part */
    pmd_managedobj_clear(&managed_obj, FALSE);

    /* clear CTag part */
    pmd_tag_init(tag, NULL, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
}

void pmd_tag_clone(pmd_tag* tag, const pmd_tag* org_tag)
{
    /* clone CManagedObject part */
    pmd_managedobj_clone(&tag->managedobj, &org_tag->managedobj);

    /* clone CTag part */
    tag->ref_type = org_tag->ref_type;
    tag->bit_pos  = org_tag->bit_pos;
    tag->rel_pos  = org_tag->rel_pos;
}

void pmd_tag_init(pmd_tag* tag, const pmd_typ* ref_type, unsigned short bit_pos, unsigned short rel_pos)
{
    /* clear CManagedObject part */
    pmd_managedobj_clear(&tag->managedobj, FALSE);

    /* initialize CTag part */
    tag->ref_type = ref_type;
    tag->rel_pos  = rel_pos;
    tag->bit_pos  = bit_pos;
}

const pmd_ref* pmd_tag_init_reference(pmd_env* env, pmd_tag* tag, const pmd_ref* ref_list, const char* refname, autogen_ref* org_ref)
{
    const pmd_ref* ref_it = NULL;

    if (org_ref && org_ref->type == referenceTypeTraceDataLength)
    {
        pmd_tag_init(tag, env->typ_trace_data_length, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
    }
    else
    {
        if (org_ref && org_ref->type == referenceTypeTransformation)
        {
            refname = org_ref->original_name;
        }

        ref_it = ref_list;

        /* find reference in list */
        while (ref_it && strcmp(ref_it->name, refname))
        {
            ref_it = ref_it->next;
        }

        if (ref_it)
        {
            pmd_tag_clone(tag, &ref_it->len.tag);
        }
    }

    return (org_ref && org_ref->type == referenceTypeTransformation ? NULL : ref_it);
}

void pmd_tag_write(pmd_env* env, const pmd_tag* tag)
{
    /* write CManagedObject part */
    pmd_managedobj_write(env, &tag->managedobj);

    /* write CTag part */
    pmd_write_word(env, tag->rel_pos);
    pmd_write_word(env, tag->bit_pos);

    if (tag->ref_type)
    {
        const pmd_typ* ref_type = tag->ref_type;

        pmd_write_objid(env, &ref_type->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }
}

/* ============================================================================================= */
/* CType functions */
/* ============================================================================================= */

void pmd_type_init(pmd_env* env, pmd_typ* type, unsigned short class_id, const char* name)
{
    /* initialize CManagedObject part */
    pmd_managedobj_init(&type->managedobj, TRUE, class_id, 
        class_id == PMD_CLASS_NULL ? 0 : ++env->last_object_id);

    /* initialize CType part */
    type->name     = pmd_heap_strdup_h(env->heap_handle, name);
}

void pmd_type_clone(pmd_typ* type, const pmd_typ* org_type)
{
    /* clone CManagedObject part */
    pmd_managedobj_clone(&type->managedobj, &org_type->managedobj);

    /* clone CType part */
    type->name = org_type->name;
}

pmd_typ* pmd_type_clone_any(pmd_env* env, const pmd_typ* org_type)
{
    pmd_typ* type = NULL;

    if (org_type)
    {
        switch (org_type->managedobj.class_id)
        {
        case PMD_CLASS_BLOCK:
            type = pmd_block_clone(env, (const pmd_block*)org_type);
            break;
        case PMD_CLASS_CHOICE:
            type = pmd_choice_clone(env, (const pmd_choice*)org_type);
            break;
        case PMD_CLASS_FILLER_TYPE_DYNAMIC:
            type = pmd_filler_dyn_clone(env, (const pmd_filler_dyn*)org_type);
            break;
        case PMD_CLASS_FILLER_TYPE_STATIC:
            type = pmd_filler_static_clone(env, (const pmd_filler_static*)org_type);
            break;
        case PMD_CLASS_NUMBER_TYPE:
            type = pmd_number_clone(env, (const pmd_number*)org_type);
            break;
        case PMD_CLASS_SEQUENCE:
            type = pmd_seq_clone(env, (const pmd_seq*)org_type);
            break;
        case PMD_CLASS_SEQUENCE_OF:
            type = pmd_seq_of_clone(env, (const pmd_seq_of*)org_type);
            break;
        case PMD_CLASS_STRING_TYPE:
            type = pmd_string_clone(env, (const pmd_string*)org_type);
            break;
        default:
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_type_clone_any(): Unhandled type: %d (%s) [id:%u]", 
                org_type->managedobj.class_id, org_type->name, org_type->managedobj.object_id);
        }
    }

    return type;
}

void pmd_type_write(pmd_env* env, const pmd_typ* type)
{
    /* write CManagedObject part */
    pmd_managedobj_write(env, &type->managedobj);

    /* write CType part */
     /* nothing to write */
}

void pmd_type_write_any(pmd_env* env, const pmd_typ* type)
{
    if (type && type->managedobj.stream_out)
    {
        /* which type should be written? */
        switch (type->managedobj.class_id)
        {
        case PMD_CLASS_FILLER_TYPE_DYNAMIC:
            pmd_filler_dyn_write(env, (const pmd_filler_dyn*)type);
            break;
        case PMD_CLASS_FILLER_TYPE_STATIC:
            pmd_filler_static_write(env, (const pmd_filler_static*)type);
            break;
        case PMD_CLASS_NUMBER_TYPE:
            pmd_number_write(env, (const pmd_number*)type);
            break;
        case PMD_CLASS_STRING_TYPE:
            pmd_string_write(env, (const pmd_string*)type);
            break;
        case PMD_CLASS_BLOCK:
            pmd_block_write(env, (const pmd_block*)type);
            break;
        case PMD_CLASS_CHOICE:
            pmd_choice_write(env, (const pmd_choice*)type);
            break;
        case PMD_CLASS_SEQUENCE:
            pmd_seq_write(env, (const pmd_seq*)type);
            break;
        case PMD_CLASS_SEQUENCE_OF:
            pmd_seq_of_write(env, (const pmd_seq_of*)type);
            break;
        default:
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                "pmd_type_write_any(): Unhandled type: %d (%s) [id:%u]", 
                type->managedobj.class_id, type->name, type->managedobj.object_id);
        }
    }
}

/* End of file output_pmd_types.c */
