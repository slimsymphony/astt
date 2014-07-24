/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_pmd_info.c
                -----------------
                SW Module






Project:          autogen

%name:            output_pmd_info.c %
%version:         co1tss#131 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Tue Feb 08 14:02:22 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the part of the source code for the PMD output generator that generates and
    write Info objects (such as OS task info)
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

#include <malloc.h>
#include <string.h>
#include <time.h>

#ifdef AUTOGEN_INCLUDE_NOS_TRACES

 #undef OS_TASK_NAME
 #undef OS_TIMER_NAME
 #undef OS_RESOURCE_NAME
 #undef OS_BLOCK_SET_NAME
 #undef OS_CONF_H

 #include "os.h"

 #define callback_task(handle, stack, addr, prio, msg_buf_l, fast_msg_buf_l, cb_buf_length, os_task_init_msg) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_TASK_MCU, #handle, task_id++, 4, prio, stack, msg_buf_l, fast_msg_buf_l);
 #define task(handle, stack, addr, prio, msg_buf_l, fast_msg_buf_l, os_task_init_msg) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_TASK_MCU, #handle, task_id++, 4, prio, stack, msg_buf_l, fast_msg_buf_l);
 #define timer(handle, type, dest_task, message) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_TIMER_MCU, #handle, timer_id++, 3, type, dest_task, 0, 0);
 #define timer_no_msg(handle) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_TIMER_MCU, #handle, timer_id++, 3, 0, 0, 0, 0);
 #define timer_default_msg(handle, type, dest_task) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_TIMER_MCU, #handle, timer_id++, 3, type, dest_task, 0, 0);
 #define block(count, size) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_BLOCK_SET_MCU, "BLOCK_" #size, block_id++, 2, count, size, 0, 0);

 #ifdef resource
  #undef resource
 #endif

 #ifdef semaphore
  #undef semaphore
 #endif

 #define resource(handle) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_RESOURCE_MCU, #handle, res_id++, 0, 0, 0, 0, 0);
 #define semaphore(handle) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_RESOURCE_MCU, #handle, res_id++, 0, 0, 0, 0, 0);
 #define resource_strict(handle, type, init) \
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_RESOURCE_MCU, #handle, res_id++, 0, 0, 0, 0, 0);
 #define heap(max, min) \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_SIZE_MAX, max); \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_SIZE_MIN, min);
 #define heap_area_1(size) \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_AREA_1_SIZE, size);
 #define heap_area_2(size) \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_AREA_2_SIZE, size);
 #define slow_heap(max, min) \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_SIZE_MAX, max); \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_SIZE_MIN, min);
 #define slow_heap_area_1(size) \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_AREA_1_SIZE, size);
 #define slow_heap_area_2(size) \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_AREA_2_SIZE, size);
 #define static_heap(size) \
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_HEAP_SIZE, size);

#endif /* AUTOGEN_INCLUDE_NOS_TRACES */


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL
#endif /* LOCAL */

LOCAL unsigned int      pmd_env_add_value(pmd_env* env, unsigned short device_id, unsigned int id, unsigned int value);
LOCAL unsigned int      pmd_env_add_string(pmd_env* env, unsigned short device_id, unsigned int id, const char* value);

LOCAL pmd_info*         pmd_info_add_entry(pmd_env* env, pmd_info_group* info_group, const char* name, unsigned int id, 
                                           unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4);
LOCAL pmd_info*         pmd_info_find(pmd_info_group* info_group, unsigned int id);
LOCAL void              pmd_info_write(pmd_env* env, const pmd_info* info, unsigned int n_data);

#ifdef AUTOGEN_INCLUDE_NOS_TRACES
 LOCAL void             pmd_info_generate_os(pmd_env* env);
 LOCAL void             pmd_info_generate_os_trace_groups(pmd_env* env);
#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

LOCAL void              pmd_info_generate_symbols(pmd_env* env);

LOCAL pmd_info_group*   pmd_info_group_find(pmd_env* env, unsigned short device_id, unsigned int type);
LOCAL void              pmd_info_group_write(pmd_env* env, const pmd_info_group* info_group);

/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

#ifdef AUTOGEN_INCLUDE_NOS_TRACES

LOCAL void pmd_info_generate_os(pmd_env* env)
{
    unsigned int task_id = OS_DYNAMIC_TASK_AMOUNT;
    unsigned int timer_id = OS_DYNAMIC_TIMER_AMOUNT;
    unsigned int block_id = 0;
#if defined OS_DYNAMIC_RESOURCE_AMOUNT
    unsigned int res_id = OS_DYNAMIC_RESOURCE_AMOUNT;
#else
    unsigned int res_id = 0;
#endif

#include "os_elem.h"

    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_TASK_MCU, "OS_INTERRUPT_HANDLER", 0x00FE, 0, 0,0,0,0);
    pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_TASK_MCU, "OS_UNKNOWN_TASK",      0x00FF, 0, 0,0,0,0);
}

LOCAL void pmd_info_generate_os_trace_groups(pmd_env* env)
{
    /* Add OS traces */
    autogen_res* res = util_get_res(PN_MON);

    if (res)
    {
        autogen_it tbl_it = INIT_ITERATOR;
        autogen_tbl* tbl;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
        tbl_it.obj.name    = "MON_OS_TRACE_CONTROL_BITMAP";
        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.ver         = &res->base.ver;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
        if (tbl)
        {
            autogen_it entry_it = INIT_ITERATOR;
            autogen_obj* entry;

            pmd_msgtype_add(env, env->device_id, PMD_MESSAGE_TYPE_OS_TRACE, "OS traces", "os", 0);

            entry_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
            entry_it.ver     = &res->base.ver;

            entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
            while (entry)
            {
                char* trc_name = pmd_heap_strdup_h(env->heap_handle, entry->name);
                unsigned int name_len;

                if (!strncmp(entry->name, "MON_", 4))
                {
                    strcpy(trc_name, &entry->name[4]);
                }

                name_len = strlen(trc_name);

                if (name_len > 4 && !strcmp(&trc_name[name_len-4], "_BIT"))
                {
                    trc_name[name_len-4] = 0;
                }

                pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OS_TRACE_GROUPS, trc_name, (unsigned int)entry->id, 0, 0, 0, 0, 0);

                entry = autogen_obj_find_next_in_list(&entry_it);
            }
        }
    }
}

#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_info_generate_symbols

    Purpose: 
    Generates info objects based on symbol tables

    Functional Description:
    Generates all objects for the following info types
    - PMD_INFO_TYPE_PN_OBJECTS_HOST
    - PMD_INFO_TYPE_PN_RESOURCES
    - PMD_INFO_TYPE_PN_MEDIAS
    - PMD_INFO_TYPE_PN_DEVICES

*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void pmd_info_generate_symbols(pmd_env* env)
{
    autogen_res* res = util_get_unique_res(RESOURCE_SYMBOLS);
    autogen_it tbl_it = INIT_ITERATOR;
    unsigned int n;

    for (n = 0; n < AUTOGEN_SYMBOL_TYPES_MAX; n++)
    {
        unsigned short device_id = env->device_id;
        if (g_symbol_conf[n].device_id != AUTOGEN_DEVICE_CURRENT)
        {
            device_id = g_symbol_conf[n].device_id;
        }

        /* Generate info type, if it doesn't already exist */
        if (g_symbol_conf[n].pmd_info_type != PMD_INFO_TYPE_NONE)
        {
            autogen_tbl* tbl;

            tbl_it.obj.name = g_symbol_conf[n].tblname;

            tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
            if (tbl)
            {
                int to_be_generated = TRUE;

                if (env->file_restriction & AUTOGEN_PMD_FILE_RESTRICTION_NON_RD)
                {
                    if (!(g_symbol_conf[n].pmd_flag & env->file_restriction)) to_be_generated = FALSE;
                }

                /* should symbols be generated in PMD file? */
                if (to_be_generated)
                {
                    autogen_obj* entry = autogen_obj_get_first_in_list(&tbl->base.child_list);
                    while (entry)
                    {   
                        autogen_pmd_info_attr* attr = (autogen_pmd_info_attr*)autogen_obj_get_first_in_list(&entry->child_list);

                        if (attr)
                        {
                            pmd_info_add(env, device_id, g_symbol_conf[n].pmd_info_type, entry->name, 
                                (unsigned int)entry->id, attr->n_attr, attr->attr[0], attr->attr[1], attr->attr[2], attr->attr[3]);
                        }
                        else
                        {
                            pmd_info_add(env, device_id, g_symbol_conf[n].pmd_info_type, entry->name, 
                                (unsigned int)entry->id, 0, 0, 0, 0, 0);
                        }

                        entry = entry->next;
                    }
                }
            }

        }
    }
}

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_env_add_value

    Purpose: 
    Adds an environment variable object to the PMD model

    Functional Description:
    Creates a PMD environment variable object and places the new object in the PMD model

    Arguments:
    id       - [in] ID of the environment variable
    value    - [in] value of the variable

    Returns:
    Object ID of the new PMD environment variable object
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL unsigned int pmd_env_add_value(pmd_env* env, unsigned short device_id, unsigned int id, unsigned int value)
{
    pmd_device* device = pmd_device_find(env, device_id);

    /* create environment variable object */
    pmd_env_var* envvar = (pmd_env_var*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_env_var));

    /* initialize object */
    pmd_managedobj_init(&envvar->managedobj, FALSE, PMD_CLASS_ENVIRONMENT_VAR, 0);

    envvar->id    = id;
    envvar->type  = PMD_ENVIRONMENT_VAR_TYPE_INTEGER;
    envvar->value = value;

    if (device)
    {
        /* add environment variable to the list */
        envvar->next     = device->env_vars;
        device->env_vars = envvar;

        /* update the number of environment variables */
        ++device->n_env_vars;
    }
    else
    {
        /* add environment variable to the list */
        envvar->next  = env->env_vars;
        env->env_vars = envvar;

        /* update the number of environment variables */
        ++env->n_env_vars;
    }

    return envvar->managedobj.object_id;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_env_add_string

Purpose: 
Adds an environment variable (string) object to the PMD model

Functional Description:
Creates a PMD environment variable object and places the new object in the PMD model

Arguments:
id       - [in] ID of the environment variable
value    - [in] value of the variable

Returns:
Object ID of the new PMD environment variable object
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL unsigned int pmd_env_add_string(pmd_env* env, unsigned short device_id, unsigned int id, const char* value)
{
    pmd_device* device = pmd_device_find(env, device_id);

    /* create environment variable object */
    pmd_env_var* envvar = (pmd_env_var*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_env_var));

    /* initialize object */
    pmd_managedobj_init(&envvar->managedobj, FALSE, PMD_CLASS_ENVIRONMENT_VAR, 0);

    envvar->id           = id;
    envvar->type         = PMD_ENVIRONMENT_VAR_TYPE_STRING;
    envvar->value_string = pmd_heap_strdup_h(env->heap_handle, value);

    if (device)
    {
        /* add environment variable to the list */
        envvar->next     = device->env_vars;
        device->env_vars = envvar;

        /* update the number of environment variables */
        ++device->n_env_vars;
    }
    else
    {
        /* add environment variable to the list */
        envvar->next  = env->env_vars;
        env->env_vars = envvar;

        /* update the number of environment variables */
        ++env->n_env_vars;
    }

    return envvar->managedobj.object_id;
}

const char* pmd_env_lookup_string(pmd_env* env, unsigned short device_id, unsigned int id)
{
	pmd_device* device = pmd_device_find(env, device_id);

    const pmd_env_var* env_var = NULL;
	const pmd_env_var* env_it = device ? device->env_vars : env->env_vars;

    while (env_it && env_it->id != id)
    {
        env_it = env_it->next;
    }

    if (env_it && env_it->type == PMD_ENVIRONMENT_VAR_TYPE_STRING && env_it->id == id)
    {
        env_var = env_it;
    }

	return env_var ? env_var->value_string : NULL;
}

void pmd_env_vars_generate(pmd_env* env)
{
    const autogen_prop* prop = prop_find_first(&g_pmd_environment_variables, PROPERTY_PMD_ENVIRONMENT_VARIABLE);
    while (prop)
    {
        unsigned int envvar_id = (unsigned int)prop->index;

        if (prop->flags & PROPERTY_FLAG_STRING)
        {
            if (envvar_id == PMD_ENVIRONMENT_VAR_ID_ADSP_SW_VERSION ||
                envvar_id == PMD_ENVIRONMENT_VAR_ID_CDSP_SW_VERSION ||
                envvar_id == PMD_ENVIRONMENT_VAR_ID_MCU_SW_VERSION ||
                envvar_id == PMD_ENVIRONMENT_VAR_ID_CDMA_DSP_SW_VERSION)
            {
                envvar_id = PMD_ENVIRONMENT_VAR_ID_SW_VERSION;
            }
            pmd_env_add_string(env, env->device_id, envvar_id, prop->str);
        }
        else
        {
            pmd_env_add_value(env, env->device_id, envvar_id, (unsigned int)prop->value);
        }

        prop = prop_find_next(prop);
    }

    /* ------------------------------------------------------------------------- */
    /* add variables telling PMD file type and restriction */
    /* ------------------------------------------------------------------------- */

    pmd_env_add_value(env, PMD_DEVICE_GENERAL, PMD_ENVIRONMENT_VAR_ID_PMD_FILE_TYPE, AUTOGEN_PMD_FILE_TYPE);
    pmd_env_add_value(env, PMD_DEVICE_GENERAL, PMD_ENVIRONMENT_VAR_ID_PMD_FILE_RESTRICTION, env->file_restriction_pmd);

    /* ------------------------------------------------------------------------- */
    /* Add MCU OS variables */
    /* ------------------------------------------------------------------------- */
#if (defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU && defined AUTOGEN_INCLUDE_NOS_TRACES)

#ifdef OS_TIMER_INTERVAL
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_TIMER_INTERVAL, (unsigned int)(1000000.0f * OS_TIMER_INTERVAL));
#endif
#ifdef OS_DYNAMIC_TASK_AMOUNT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_AMOUNT, OS_DYNAMIC_TASK_AMOUNT);
#endif
#ifdef OS_DYNAMIC_TIMER_AMOUNT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TIMER_AMOUNT, OS_DYNAMIC_TIMER_AMOUNT);
#endif
#ifdef OS_DYNAMIC_RESOURCE_AMOUNT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_RESOURCE_AMOUNT, OS_DYNAMIC_RESOURCE_AMOUNT);
#endif
#ifdef OS_BLOCK_ALIGN
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_ALIGN, OS_BLOCK_ALIGN);
#endif
#ifdef OS_HEADER_DATA_SIZE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEADER_DATA_SIZE, OS_HEADER_DATA_SIZE);
#endif
#ifdef OS_AUX_HEAP_AREAS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_HEAP_AREAS, OS_AUX_HEAP_AREAS);
#endif
#ifdef OS_SYSTEM_STACK_SIZE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SYSTEM_STACK_SIZE, OS_SYSTEM_STACK_SIZE);
#endif
#ifdef OS_SYSTEM_STACK_1_SIZE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SYSTEM_STACK_1_SIZE, OS_SYSTEM_STACK_1_SIZE);
#endif
#ifdef OS_AUX_SLOW_HEAP_AREAS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_SLOW_HEAP_AREAS, OS_AUX_SLOW_HEAP_AREAS);
#endif
#ifdef OS_DYNAMIC_TASK_HIGH_PRIORITY
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_HIGH_PRIORITY, OS_DYNAMIC_TASK_HIGH_PRIORITY);
#endif
#ifdef OS_DYNAMIC_TASK_LOW_PRIORITY
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_LOW_PRIORITY, OS_DYNAMIC_TASK_LOW_PRIORITY);
#endif
#ifdef OS_STACK_MULTIPLY
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_STACK_MULTIPLY, OS_STACK_MULTIPLY);
#endif
#ifdef OS_64K_TIMERS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_64K_TIMERS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_64K_TIMERS, OFF);
#endif
#ifdef OS_REG_EVENT_TIMER_INT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_REG_EVENT_TIMER_INT, OS_REG_EVENT_TIMER_INT);
#endif
#ifdef OS_FILL_STACKS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_FILL_STACKS, OS_FILL_STACKS);
#endif
#ifdef OS_MONITOR
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_MONITOR, OS_MONITOR);
#endif
#ifdef OS_DYNAMIC_TRACE_CONTROL         
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TRACE_CONTROL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TRACE_CONTROL, OFF);
#endif
#ifdef OS_PORTABLE_LOG
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_PORTABLE_LOG, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_PORTABLE_LOG, OFF);
#endif
#ifdef OS_ERROR_CHK
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_ERROR_CHK, OS_ERROR_CHK);
#endif
#ifdef OS_AUX_DEALLOC_AREA_LO
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_DEALLOC_AREA_LO, OS_AUX_DEALLOC_AREA_LO);
#endif
#ifdef OS_AUX_DEALLOC_AREA_HI
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_DEALLOC_AREA_HI, OS_AUX_DEALLOC_AREA_HI);
#endif
#ifdef OS_BLOCK_PTR_VALIDITY_CHECK
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_PTR_VALIDITY_CHECK, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_PTR_VALIDITY_CHECK, OFF);
#endif
#ifdef OS_POOL_CALLER_DEPTH
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_CALLER_DEPTH, OS_POOL_CALLER_DEPTH);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_CALLER_DEPTH, 0);
#endif
#ifdef OS_POOL_HEADER_CALLER_STORE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_HEADER_CALLER_STORE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_HEADER_CALLER_STORE, OFF);
#endif
#ifdef OS_POOL_DEALLOCATOR_STORE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_DEALLOCATOR_STORE, OS_POOL_DEALLOCATOR_STORE);
#endif
#ifdef OS_POST_MORTEM_CALLER_STORE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_POST_MORTEM_CALLER_STORE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_POST_MORTEM_CALLER_STORE, OFF);
#endif
#ifdef OS_POST_MORTEM_CALLER_COUNT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_POST_MORTEM_CALLER_COUNT, OS_POST_MORTEM_CALLER_COUNT);
#endif
#ifdef OS_LAZY_FN_CALLER
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAZY_FN_CALLER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAZY_FN_CALLER, OFF);
#endif
#ifdef OS_FAILSAFE_STACK_SIZE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_FAILSAFE_STACK_SIZE, OS_FAILSAFE_STACK_SIZE);
#endif
#ifdef OS_IRQ_STACK_LOW_WARNING
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_IRQ_STACK_LOW_WARNING, OS_IRQ_STACK_LOW_WARNING);
#endif
#ifdef OS_TASK_STACK_LOW_WARNING
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_TASK_STACK_LOW_WARNING, OS_TASK_STACK_LOW_WARNING);
#endif
#ifdef OS_UPP_MTC_AWAKE_TIMER_LENGTH
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_UPP_MTC_AWAKE_TIMER_LENGTH, OS_UPP_MTC_AWAKE_TIMER_LENGTH);
#endif
#ifdef OS_UPP_MTC_AWAKE_DSPGPT_OPTIMIZATION
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_UPP_MTC_AWAKE_DSPGPT_OPTIMIZATION, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_UPP_MTC_AWAKE_DSPGPT_OPTIMIZATION, OFF);
#endif
#ifdef OS_REG_EVENT_SETTLE_TIME
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_REG_EVENT_SETTLE_TIME, OS_REG_EVENT_SETTLE_TIME);
#endif
#ifdef OS_MINIMUM_SLEEP_TIME
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_MINIMUM_SLEEP_TIME, OS_MINIMUM_SLEEP_TIME);
#endif
#ifdef OS_MULTIPLE_REG_EVENT_SOURCES
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_MULTIPLE_REG_EVENT_SOURCES, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_MULTIPLE_REG_EVENT_SOURCES, OFF);
#endif
#ifdef OS_SIMULATED_REG_EVENT_INT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SIMULATED_REG_EVENT_INT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SIMULATED_REG_EVENT_INT, OFF);
#endif
#ifdef OS_FREE_RUNNING_TIMER_USED
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_FREE_RUNNING_TIMER_USED, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_FREE_RUNNING_TIMER_USED, OFF);
#endif
#ifdef OS_LONG_SW_TIMERS                
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_LONG_SW_TIMERS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_LONG_SW_TIMERS, OFF);
#endif
#ifdef OS_CURRENT_TIME_USED
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_CURRENT_TIME_USED, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_CURRENT_TIME_USED, OFF);
#endif
#ifdef OS_CURRENT_TIME_IN_MS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_CURRENT_TIME_IN_MS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_CURRENT_TIME_IN_MS, OFF);
#endif
#ifdef OS_RESOURCE_ACTIVATION
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_ACTIVATION, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_ACTIVATION, OFF);
#endif
#ifdef OS_RESOURCE_INIT_VALUE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_INIT_VALUE, OS_RESOURCE_INIT_VALUE);
#endif
#ifdef OS_FATAL_OWNER_BLOCKING_RESOURCE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_FATAL_OWNER_BLOCKING_RESOURCE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_FATAL_OWNER_BLOCKING_RESOURCE, OFF);
#endif
#ifdef OS_FATAL_BLOCKING_ALLOC
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_FATAL_BLOCKING_ALLOC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_FATAL_BLOCKING_ALLOC, OFF);
#endif
#ifdef OS_HEAP_FIRST_FIT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_FIRST_FIT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_FIRST_FIT, OFF);
#endif
#ifdef OS_SLOW_HEAP_IN_USE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_IN_USE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_IN_USE, OFF);
#endif
#ifdef OS_DYNAMIC_MEMORY_SERVICE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_MEMORY_SERVICE, OS_DYNAMIC_MEMORY_SERVICE);
#endif
#ifdef OS_REGION_AMOUNT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_REGION_AMOUNT, OS_REGION_AMOUNT);
#endif
#ifdef OS_STATIC_TASK_NAMES
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_TASK_NAMES, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_TASK_NAMES, OFF);
#endif
#ifdef OS_STATIC_TIMER_NAMES            
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_TIMER_NAMES, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_TIMER_NAMES, OFF);
#endif

    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD)
    {
        pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_TASK_AMOUNT, OS_TASK_AMOUNT);
        pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_SET_AMOUNT, OS_BLOCK_SET_AMOUNT);
        pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_AMOUNT, OS_RESOURCE_AMOUNT);
        pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MCU_OS_TIMER_AMOUNT, OS_TIMER_AMOUNT);
    }

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU && AUTOGEN_INCLUDE_NOS_TRACES */


    /* ------------------------------------------------------------------------- */
    /* ISA protocol flags */
    /* ------------------------------------------------------------------------- */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU

#ifdef IPF_3GPP_SPEC_RELEASE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_3GPP_SPEC_RELEASE, IPF_3GPP_SPEC_RELEASE);
#endif

#if (IPF_ALS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_ALS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_ALS, OFF);
#endif

#if (IPF_AUTO_QMEAS_IN_RANDOM_ACCESS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_AUTO_QMEAS_IN_RANDOM_ACCESS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_AUTO_QMEAS_IN_RANDOM_ACCESS, OFF);
#endif

#if (ICF_BCS_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BCS_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BCS_SERV, OFF);
#endif

#if (ICF_BTCS_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BTCS_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BTCS_SERV, OFF);
#endif

#if (IPF_BTS_TEST == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BTS_TEST, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BTS_TEST, OFF);
#endif

#if (IPF_BTS_TEST_WITH_NMEAS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BTS_TEST_WITH_NMEAS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BTS_TEST_WITH_NMEAS, OFF);
#endif

#if (IPF_CALL_HOLD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CALL_HOLD, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CALL_HOLD, OFF);
#endif

#if (IPF_CALL_SERVER_FCS_CLIENT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CALL_SERVER_FCS_CLIENT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CALL_SERVER_FCS_CLIENT, OFF);
#endif

#if (IPF_CCBS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CCBS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CCBS, OFF);
#endif

#if (IPF_CELLMO_PLATFORM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CELLMO_PLATFORM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CELLMO_PLATFORM, OFF);
#endif

#if (IPF_CLIR == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CLIR, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CLIR, OFF);
#endif

#if (IPF_CNAP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CNAP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CNAP, OFF);
#endif

#if (IPF_COMBINED_PSW_SYNC_MEAS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_COMBINED_PSW_SYNC_MEAS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_COMBINED_PSW_SYNC_MEAS, OFF);
#endif

#if (IPF_CSD_24_CHANNEL_CODING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_24_CHANNEL_CODING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_24_CHANNEL_CODING, OFF);
#endif

#if (IPF_CSD_48_CHANNEL_CODING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_48_CHANNEL_CODING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_48_CHANNEL_CODING, OFF);
#endif
#if (IPF_CSD_96_CHANNEL_CODING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_96_CHANNEL_CODING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_96_CHANNEL_CODING, OFF);
#endif

#if (IPF_CSD_144_CHANNEL_CODING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_144_CHANNEL_CODING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_144_CHANNEL_CODING, OFF);
#endif

#if (IPF_CSD_AT_COMMAND_INTERPRETER == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_AT_COMMAND_INTERPRETER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_AT_COMMAND_INTERPRETER, OFF);
#endif

#ifdef IPF_CSD_MULTISLOT_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CSD_MULTISLOT_CLASS, IPF_CSD_MULTISLOT_CLASS);
#endif

#if (IPF_CTM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CTM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CTM, OFF);
#endif

#if (IPF_CUG == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CUG, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_CUG, OFF);
#endif

#if (IPF_DCM_DRIVE_MODE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DCM_DRIVE_MODE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DCM_DRIVE_MODE, OFF);
#endif
#ifdef IPF_DCT_PLATFORM
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DCT_PLATFORM, IPF_DCT_PLATFORM);
#endif
#if (IPF_DIGITAL_AFC == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DIGITAL_AFC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DIGITAL_AFC, OFF);
#endif
#if (IPF_DTM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DTM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DTM, OFF);
#endif
#ifdef IPF_DTM_EGPRS_MULTISLOT_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DTM_EGPRS_MULTISLOT_CLASS, IPF_DTM_EGPRS_MULTISLOT_CLASS);
#endif

#ifdef IPF_DTM_GPRS_MULTISLOT_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_DTM_GPRS_MULTISLOT_CLASS, IPF_DTM_GPRS_MULTISLOT_CLASS);
#endif

#if (IPF_ECT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_ECT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_ECT, OFF);
#endif

#if (IPF_EGPRS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS, OFF);
#endif

#if (IPF_EGPRS_8PSK_UPLINK == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_8PSK_UPLINK, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_8PSK_UPLINK, OFF);
#endif
#if (IPF_EGPRS_EXT_DYN_ALLOC == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_EXT_DYN_ALLOC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_EXT_DYN_ALLOC, OFF);
#endif
#ifdef IPF_EGPRS_MULTISLOT_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_MULTISLOT_CLASS, IPF_EGPRS_MULTISLOT_CLASS);
#endif
#ifdef IPF_EGPRS_POWER_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_POWER_CLASS, IPF_EGPRS_POWER_CLASS);
#endif
#ifdef IPF_EXT_DTM_EGPRS_MULTISLOT_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EXT_DTM_EGPRS_MULTISLOT_CLASS, IPF_EXT_DTM_EGPRS_MULTISLOT_CLASS);
#endif
#ifdef IPF_EXT_DTM_GPRS_MULTISLOT_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_EXT_DTM_GPRS_MULTISLOT_CLASS, IPF_EXT_DTM_GPRS_MULTISLOT_CLASS);
#endif
#if (IPF_FDN == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_FDN, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_FDN, OFF);
#endif
#if (ICF_FEATURE_CONTROL == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FEATURE_CONTROL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FEATURE_CONTROL, OFF);
#endif

#if (IPF_GERAN_FEATURE_PACKAGE_1 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GERAN_FEATURE_PACKAGE_1, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GERAN_FEATURE_PACKAGE_1, OFF);
#endif

#if (IPF_GPRS_EXT_DYN_ALLOC == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_EXT_DYN_ALLOC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_EXT_DYN_ALLOC, OFF);
#endif

#ifdef IPF_GPRS_MULTISLOT_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_MULTISLOT_CLASS, IPF_GPRS_MULTISLOT_CLASS);
#endif
#ifdef IPF_GPRS_NON_DRX_TIMER_VALUE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_NON_DRX_TIMER_VALUE, IPF_GPRS_NON_DRX_TIMER_VALUE);
#endif
#if (IPF_GPRS_PDA_OPTIMIZATION == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_PDA_OPTIMIZATION, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_PDA_OPTIMIZATION, OFF);
#endif
#ifdef IPF_GPRS_READY_TIMER_UNIT
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_READY_TIMER_UNIT, IPF_GPRS_READY_TIMER_UNIT);
#endif
#ifdef IPF_GPRS_READY_TIMER_VALUE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_READY_TIMER_VALUE, IPF_GPRS_READY_TIMER_VALUE);
#endif
#if (IPF_GPRS_RFC1144_HEADER_COMP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC1144_HEADER_COMP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC1144_HEADER_COMP, OFF);
#endif
#if (IPF_GPRS_RFC2507_HEADER_COMP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC2507_HEADER_COMP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC2507_HEADER_COMP, OFF);
#endif
#if (IPF_GPRS_RFC3095_HEADER_COMP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC3095_HEADER_COMP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC3095_HEADER_COMP, OFF);
#endif
#if (IPF_GPRS_V42BIS_DATA_COMP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_V42BIS_DATA_COMP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_V42BIS_DATA_COMP, OFF);
#endif
#if (IPF_GSM_CSD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_CSD, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_CSD, OFF);
#endif
#if (IPF_GSM_LCS_MS_BASED_EOTD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_LCS_MS_BASED_EOTD, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_LCS_MS_BASED_EOTD, OFF);
#endif
#ifdef IPF_GSM_LOWER_BAND_POWER_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_LOWER_BAND_POWER_CLASS, IPF_GSM_LOWER_BAND_POWER_CLASS);
#endif
#if (IPF_GSM_PS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_PS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_PS, OFF);
#endif

#if (IPF_GSM_RAT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_RAT, ON);
#if (IPF_BAND_GSM_450 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_450, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_450, OFF);
#endif
#if (IPF_BAND_GSM_480 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_480, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_480, OFF);
#endif
#if (IPF_BAND_GSM_700 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_700, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_700, OFF);
#endif
#if (IPF_BAND_GSM_850 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_850, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_850, OFF);
#endif
#if (IPF_BAND_GSM_900 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_900, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_900, OFF);
#endif
#if (IPF_BAND_GSM_1800 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_1800, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_1800, OFF);
#endif
#if (IPF_BAND_GSM_1900 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_1900, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_1900, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_RAT, OFF);
#endif /* IPF_GSM_RAT == ON */

#ifdef IPF_GSM_UPPER_BAND_POWER_CLASS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_GSM_UPPER_BAND_POWER_CLASS, IPF_GSM_UPPER_BAND_POWER_CLASS);
#endif

#if (IPF_H3G_ALWAYS_ON_PDP_CONTEXT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_H3G_ALWAYS_ON_PDP_CONTEXT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_H3G_ALWAYS_ON_PDP_CONTEXT, OFF);
#endif

#if (ICF_IKE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_IKE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_IKE, OFF);
#endif

#if (IPF_IMS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_IMS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_IMS, OFF);
#endif

#if (IPF_IPV6 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_IPV6, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_IPV6, OFF);
#endif

#ifdef IPF_ISA_PLATFORM
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_ISA_PLATFORM, IPF_ISA_PLATFORM);
#endif

#if (INFO_PP_LCS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_INFO_PP_LCS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_INFO_PP_LCS, OFF);
#endif

#if (INFO_PP_LCS_AGPS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_INFO_PP_LCS_AGPS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_INFO_PP_LCS_AGPS, OFF);
#endif

#if (IPF_LCS_EOTD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_LCS_EOTD, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_LCS_EOTD, OFF);
#endif

#if (IPF_LCS_MO_LR == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_LCS_MO_LR, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_LCS_MO_LR, OFF);
#endif

#if (IPF_LCS_PRIVACY == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_LCS_PRIVACY, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_LCS_PRIVACY, OFF);
#endif
#if (IPF_LICENSE_BLOCK_OPTIMIZATION == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_LICENSE_BLOCK_OPTIMIZATION, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_LICENSE_BLOCK_OPTIMIZATION, OFF);
#endif

#ifdef IPF_MAX_PDP_CONTEXTS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_MAX_PDP_CONTEXTS, IPF_MAX_PDP_CONTEXTS);
#endif

#if (IPF_MPTY == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_MPTY, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_MPTY, OFF);
#endif

#if (IPF_MS_INIT_PDP_CONTEXT_MODIFICATION == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_MS_INIT_PDP_CONTEXT_MODIFICATION, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_MS_INIT_PDP_CONTEXT_MODIFICATION, OFF);
#endif

#if (IPF_MULTIMEDIA_CALL == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_MULTIMEDIA_CALL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_MULTIMEDIA_CALL, OFF);
#endif

#if (IPF_NOKIA_TEST_MOBILE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_NOKIA_TEST_MOBILE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_NOKIA_TEST_MOBILE, OFF);
#endif

#if (IPF_NW_INIT_PDP_CONTEXT_ACTIVATION == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_NW_INIT_PDP_CONTEXT_ACTIVATION, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_NW_INIT_PDP_CONTEXT_ACTIVATION, OFF);
#endif

#if (IPF_OFFLINE_MODE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_OFFLINE_MODE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_OFFLINE_MODE, OFF);
#endif

#if IPF_OMA_POC
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_OMA_POC, IPF_OMA_POC);
#endif

#if (IPF_PERFORMANCE_TRACES == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERFORMANCE_TRACES, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERFORMANCE_TRACES, OFF);
#endif

#if (IPF_PERM_BTS_TEST_CARRIER == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERM_BTS_TEST_CARRIER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERM_BTS_TEST_CARRIER, OFF);
#endif

#if (IPF_PERM_GPRS_AUTO_ATTACH == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERM_GPRS_AUTO_ATTACH, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERM_GPRS_AUTO_ATTACH, OFF);
#endif

#if (IPF_PERM_GSM_BANDS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERM_GSM_BANDS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERM_GSM_BANDS, OFF);
#endif


#if (IPF_PERM_WCDMA_BANDS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERM_WCDMA_BANDS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PERM_WCDMA_BANDS, OFF);
#endif

#if (IPF_PFC == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PFC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PFC, OFF);
#endif

#if (IPF_PPC_COUNTERS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PPC_COUNTERS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PPC_COUNTERS, OFF);
#endif

#if (IPF_PP_CSD_MULTISLOT_CLASS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PP_CSD_MULTISLOT_CLASS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PP_CSD_MULTISLOT_CLASS, OFF);
#endif

#if (IPF_PREPAID_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PREPAID_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_PREPAID_SUPPORT, OFF);
#endif

#if (IPF_RD_FEATURES == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_RD_FEATURES, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_RD_FEATURES, OFF);
#endif

#if (IPF_RF_POWER_CLASS_REDUCTION == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_RF_POWER_CLASS_REDUCTION, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_RF_POWER_CLASS_REDUCTION, OFF);
#endif

#if (INFO_PP_SECONDARY_PDP_CONTEXTS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_INFO_PP_SECONDARY_PDP_CONTEXTS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_INFO_PP_SECONDARY_PDP_CONTEXTS, OFF);
#endif

#ifdef IPF_SMS_RESEND
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SMS_RESEND, IPF_SMS_RESEND);
#endif

#if (IPF_SMSCB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SMSCB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SMSCB, OFF);
#endif

#if (IPF_SMSCB_EXT_CBCH == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SMSCB_EXT_CBCH, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SMSCB_EXT_CBCH, OFF);
#endif

#if (IPF_SOCKET == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SOCKET, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SOCKET, OFF);
#endif

#ifdef IPF_SPLIT_PG_CYCLE_CODE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SPLIT_PG_CYCLE_CODE, IPF_SPLIT_PG_CYCLE_CODE);
#endif

#if (IPF_SPLIT_PG_CYCLE_ON_CCCH == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SPLIT_PG_CYCLE_ON_CCCH, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SPLIT_PG_CYCLE_ON_CCCH, OFF);
#endif

#if (ICF_SSL == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SSL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SSL, OFF);
#endif

#if (IPF_SSOM_TEST_SUITE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SSOM_TEST_SUITE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_SSOM_TEST_SUITE, OFF);
#endif

#if (IPF_UMA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_UMA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_UMA, OFF);
#endif

#if (IPF_UUS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_UUS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_UUS, OFF);
#endif

#if (IPF_WCDMA_CSD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_CSD, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_CSD, OFF);
#endif

#if (IPF_WCDMA_PS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_PS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_PS, OFF);
#endif

#if (IPF_WCDMA_RAT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_RAT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_RAT, OFF);
#endif

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */


    /* ------------------------------------------------------------------------- */
    /* ISA core flags */
    /* ------------------------------------------------------------------------- */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU

#if (ICF_3_5MM_AUDIO_PLUG == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_3_5MM_AUDIO_PLUG, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_3_5MM_AUDIO_PLUG, OFF);
#endif

#if (ICF_ACC_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ACC_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ACC_SERV, OFF);
#endif

#if (ICF_ADL_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ADL_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ADL_SERV, OFF);
#endif

#if (ICF_APPL == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_APPL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_APPL, OFF);
#endif

#if (ICF_ASSERT_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ASSERT_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ASSERT_LIB, OFF);
#endif

#if (ICF_ATK == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ATK, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ATK, OFF);
#endif

#if (ICF_AUDIO_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_AUDIO_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_AUDIO_SERV, OFF);
#endif

#if (ICF_AUXILIARY_SW_DOWNLOAD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_AUXILIARY_SW_DOWNLOAD, ON);
#if (ICF_FMM_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FMM_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FMM_LIB, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_AUXILIARY_SW_DOWNLOAD, OFF);
#endif /* ICF_AUXILIARY_SW_DOWNLOAD == ON */

#if (ICF_BATT_CURRENT_MEASUREMENT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BATT_CURRENT_MEASUREMENT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BATT_CURRENT_MEASUREMENT, OFF);
#endif

#ifdef ICF_BOTTOM_CONNECTOR
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BOTTOM_CONNECTOR, ICF_BOTTOM_CONNECTOR);
#endif

#if (ICF_BT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BT, ON);
#if (ICF_BT_AUDIO_STREAMING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BT_AUDIO_STREAMING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BT_AUDIO_STREAMING, OFF);
#endif
#if (ICF_BT_AVRCP_TARGET == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BT_AVRCP_TARGET, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BT_AVRCP_TARGET, OFF);
#endif
#if (ICF_BT_FTP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BT_FTP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BT_FTP, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BT, OFF);
#endif /* ICF_BT == ON */

#if (ICF_BTIF_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BTIF_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_BTIF_LIB, OFF);
#endif

#if (ICF_CAMERA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CAMERA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CAMERA, OFF);
#endif

#if (ICF_CDB_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CDB_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CDB_LIB, OFF);
#endif

#if (ICF_CL == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CL, OFF);
#endif

#if (ICF_COMPASS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_COMPASS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_COMPASS, OFF);
#endif

#if (ICF_COMP_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_COMP_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_COMP_LIB, OFF);
#endif

#if (ICF_CONTTYPE_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CONTTYPE_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CONTTYPE_LIB, OFF);
#endif

#if (ICF_CORE_ONLY_BUILD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CORE_ONLY_BUILD, ON);
#if (ICF_CORE_WAKEUP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CORE_WAKEUP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CORE_WAKEUP, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CORE_ONLY_BUILD, OFF);
#endif /* ICF_CORE_ONLY_BUILD == ON */

#if (ICF_CRASH_DUMP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CRASH_DUMP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CRASH_DUMP, OFF);
#endif
#if (ICF_CRYPTO_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CRYPTO_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CRYPTO_LIB, OFF);
#endif
#if (ICF_CS_DATA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CS_DATA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CS_DATA, OFF);
#endif
#ifdef ICF_CXML_LIB
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_CXML_LIB, ICF_CXML_LIB);
#endif

#ifdef ICF_D2D_COPY
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_D2D_COPY, ICF_D2D_COPY);
#endif

#ifdef ICF_D2D_SYNC
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_D2D_SYNC, ICF_D2D_SYNC);
#endif

#if (ICF_DCT4_SIM_SERVER == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SERVER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SERVER, OFF);
#endif

#if (ICF_DCT4_SIM_SERVER_SUBSET == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SERVER_SUBSET, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SERVER_SUBSET, OFF);
#endif

#if (ICF_DCT4_SIM_SUBSYSTEM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SUBSYSTEM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SUBSYSTEM, OFF);
#endif

#if (ICF_DCT4_SIM_SUBSYSTEM_SUBSET == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SUBSYSTEM_SUBSET, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SUBSYSTEM_SUBSET, OFF);
#endif

#ifdef ICF_DEFAULT_BATTERY
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DEFAULT_BATTERY, ICF_DEFAULT_BATTERY);
#endif

#if (ICF_DISCO_LIGHTS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DISCO_LIGHTS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DISCO_LIGHTS, OFF);
#endif

#if (ICF_DISP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DISP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DISP, OFF);
#endif

#if (ICF_DUAL_OS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DUAL_OS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DUAL_OS, OFF);
#endif

#ifdef ICF_E3_PRODUCTION_BRANCH
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_E3_PRODUCTION_BRANCH , ICF_E3_PRODUCTION_BRANCH);
#endif

#if (ICF_EAP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_EAP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_EAP, OFF);
#endif

#if (ICF_EM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_EM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_EM, OFF);
#endif

#if (ICF_ENO_PROTOCOL_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ENO_PROTOCOL_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ENO_PROTOCOL_SUPPORT, OFF);
#endif

#if (ICF_FASTMON_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FASTMON_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FASTMON_LIB, OFF);
#endif

#if (ICF_FBUS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FBUS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FBUS, OFF);
#endif

#if (ICF_FBUS_ROUTING_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FBUS_ROUTING_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FBUS_ROUTING_SUPPORT, OFF);
#endif

#if (ICF_FILE_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FILE_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FILE_SERV, OFF);
#endif

#if (ICF_FILE2 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FILE2, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FILE2, OFF);
#endif

#if (ICF_FILE2_ASL_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FILE2_ASL_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FILE2_ASL_SUPPORT, OFF);
#endif

#ifdef ICF_FLASH_DEVICES
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FLASH_DEVICES, ICF_FLASH_DEVICES);
#endif

#if (ICF_FLIGHT_MODE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FLIGHT_MODE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FLIGHT_MODE, OFF);
#endif

#if (ICF_FM_RADIO == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO, ON);
#ifdef ICF_FM_RADIO_CHIP
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO_CHIP, ICF_FM_RADIO_CHIP);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO, OFF);
#endif /* ICF_FM_RADIO == ON */


#if (ICF_FTS_APPL == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FTS_APPL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_FTS_APPL, OFF);
#endif

#if (ICF_GDI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_GDI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_GDI, OFF);
#endif

#if (ICF_GPRS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_GPRS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_GPRS, OFF);
#endif

#if (ICF_HAC == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAC, OFF);
#endif

#if (ICF_HAL_I2C == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_I2C, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_I2C, OFF);
#endif

#if (ICF_HAL_LCD_LITE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_LCD_LITE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_LCD_LITE, OFF);
#endif

#if (ICF_HAL_LIGHT_LITE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_LIGHT_LITE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_LIGHT_LITE, OFF);
#endif

#if (ICF_HAL_HW_PMM_LITE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_HW_PMM_LITE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_HW_PMM_LITE, OFF);
#endif

#if (ICF_HAL_ONLY == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_ONLY, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HAL_ONLY, OFF);
#endif

#if (ICF_HARDCORE_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HARDCORE_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HARDCORE_SERV, OFF);
#endif

#if (ICF_HS23_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HS23_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HS23_SUPPORT, OFF);
#endif

#if (ICF_HSM_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HSM_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HSM_LIB, OFF);
#endif

#if (ICF_HWDRV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HWDRV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HWDRV, OFF);
#endif

#ifdef ICF_HW_GENERATION
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_HW_GENERATION, ICF_HW_GENERATION);
#endif

#if (ICF_I2C == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_I2C, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_I2C, OFF);
#endif /* ICF_I2C == ON */

#if (ICF_IMAGES == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_IMAGES, ON);
 #if (ICF_3D_IMAGES == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_3D_IMAGES, ON);
 #else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_3D_IMAGES, OFF);
 #endif
 #if (ICF_SVG == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SVG, ON);
 #else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SVG, OFF);
 #endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_IMAGES, OFF);
#endif /* ICF_IMAGES == ON */

#if (ICF_INFO_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_INFO_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_INFO_SERV, OFF);
#endif

#if (ICF_IRDA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_IRDA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_IRDA, OFF);
#endif

#if (ICF_ISA2 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ISA2, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ISA2, OFF);
#endif

#if (ICF_ISA_UI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ISA_UI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ISA_UI, OFF);
#endif

#if (ICF_JSR82_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_JSR82_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_JSR82_SUPPORT, OFF);
#endif

#if (ICF_KASUMI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_KASUMI_LIB, ON);
#else    
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_KASUMI_LIB, OFF);
#endif

#if (ICF_KBD_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_KBD_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_KBD_SERV, OFF);
#endif

#if (ICF_LBEC == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LBEC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LBEC, OFF);
#endif

#if (ICF_LCD_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LCD_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LCD_LIB, OFF);
#endif

#if (IUF_LCIF == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IUF_LCIF, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_IUF_LCIF, OFF);
#endif

#if (ICF_LCIF_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LCIF_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LCIF_SERV, OFF);
#endif

#if (ICF_LIBRARIES == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LIBRARIES, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LIBRARIES, OFF);
#endif

#if (ICF_LIGHT_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LIGHT_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LIGHT_SERV, OFF);
#endif
#if (ICF_LIST_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LIST_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LIST_LIB, OFF);
#endif

#if (ICF_LOADER == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOADER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOADER, OFF);
#endif

#if (ICF_LOADERLESS_ADL == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOADERLESS_ADL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOADERLESS_ADL, OFF);
#endif

#if (ICF_LOCATION == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION, ON);
#if (ICF_LOCATION_GOPHERS_LTM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_GOPHERS_LTM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_GOPHERS_LTM, OFF);
#endif
#if (ICF_LOCATION_TEST_LTM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_TEST_LTM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_TEST_LTM, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION, OFF);
#endif /* ICF_LOCATION == ON */

#if (ICF_MEDIA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MEDIA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MEDIA, OFF);
#endif

#if (ICF_MEMORY_CARD_SUPPORT == ON) /* Support for microSD memory card */
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MEMORY_CARD_SUPPORT, ON);
#if (ICF_MEMORY_CARD_HOT_SWAP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MEMORY_CARD_HOT_SWAP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MEMORY_CARD_HOT_SWAP, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MEMORY_CARD_SUPPORT, OFF);
#endif /* ICF_MEMORY_CARD_SUPPORT == ON */

#if (ICF_STORAGE_EMMC_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_STORAGE_EMMC_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_STORAGE_EMMC_SUPPORT, OFF);
#endif
#if (ICF_SYSTEM_EMMC_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SYSTEM_EMMC_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SYSTEM_EMMC_SUPPORT, OFF);
#endif

#if (ICF_MONITOR_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MONITOR_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MONITOR_SERV, OFF);
#endif

#ifdef ICF_MS_ASIC_FAMILY
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MS_ASIC_FAMILY, ICF_MS_ASIC_FAMILY);
#endif

#if (ICF_MTC_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MTC_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MTC_SERV, OFF);
#endif

#if (ICF_MULTIPART_ADDRESS_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MULTIPART_ADDRESS_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MULTIPART_ADDRESS_SUPPORT, OFF);
#endif

#if (ICF_MUSIC == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC, OFF);
#endif /* ICF_MUSIC == ON */

#if (ICF_MUSIC_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC_SERV, OFF);
#endif

#if (ICF_NAND_FLASH == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NAND_FLASH, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NAND_FLASH, OFF);
#endif

#if (ICF_NO_PMM_CLASS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NO_PMM_CLASS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NO_PMM_CLASS, OFF);
#endif

#if (ICF_NOKIA_VIRTUAL_SURROUND == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NOKIA_VIRTUAL_SURROUND, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NOKIA_VIRTUAL_SURROUND, OFF);
#endif

#if (ICF_NOR_DIRECT_CONTENT_FLASHING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NOR_DIRECT_CONTENT_FLASHING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NOR_DIRECT_CONTENT_FLASHING, OFF);
#endif

#if (ICF_NOR_FLASH == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NOR_FLASH, ON);
#if (ICF_SNOR_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SNOR_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SNOR_SUPPORT, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NOR_FLASH, OFF);
#endif /* ICF_NOR_FLASH == ON */

#if (ICF_NOTEPAD_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NOTEPAD_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NOTEPAD_SUPPORT, OFF);
#endif

#if (ICF_NVD_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NVD_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_NVD_SERV, OFF);
#endif

#if (ICF_OBEX == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OBEX, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OBEX, OFF);
#endif

#if (ICF_OBEX_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OBEX_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OBEX_SERV, OFF);
#endif

#ifdef ICF_OBEX_SERVER_MAX_FRAME_SIZE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OBEX_SERVER_MAX_FRAME_SIZE, ICF_OBEX_SERVER_MAX_FRAME_SIZE);
#endif

#if (ICF_ODIN_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ODIN_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ODIN_SERV, OFF);
#endif

#if (ICF_OFFLINE_MODE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OFFLINE_MODE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OFFLINE_MODE, OFF);
#endif

#if (ICF_OMA_DM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OMA_DM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OMA_DM, OFF);
#endif

#if (ICF_OMA_DS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OMA_DS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OMA_DS, OFF);
#endif

#if (ICF_OPTIRENDER_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OPTIRENDER_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OPTIRENDER_LIB, OFF);
#endif

#if (ICF_OS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OS, OFF);
#endif

#if (ICF_OTA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OTA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OTA, OFF);
#endif

#if (ICF_OTI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OTI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OTI, OFF);
#endif

#if (ICF_OVERLAY_UI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OVERLAY_UI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_OVERLAY_UI, OFF);
#endif

#if (ICF_PERM_DATA_FILLERS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PERM_DATA_FILLERS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PERM_DATA_FILLERS, OFF);
#endif

#if (ICF_PERM_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PERM_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PERM_SERV, OFF);
#endif

#if (ICF_PICT_BRIDGE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PICT_BRIDGE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PICT_BRIDGE, OFF);
#endif

#if (ICF_PMM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PMM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PMM, OFF);
#endif

#ifdef ICF_PMM_GENERATION
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PMM_GENERATION, ICF_PMM_GENERATION);
#endif

#if (ICF_PMM2 == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PMM2, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PMM2, OFF);
#endif

#if (ICF_PN_MEDIA_BT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_BT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_BT, OFF);
#endif

#if (ICF_PN_MEDIA_FBUS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_FBUS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_FBUS, OFF);
#endif

#if (ICF_PN_MEDIA_I2C == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_I2C, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_I2C, OFF);
#endif

#if (ICF_PN_MEDIA_IRDA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_IRDA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_IRDA, OFF);
#endif

#if (ICF_PN_MEDIA_MADI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MADI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MADI, OFF);
#endif

#if (ICF_PN_MEDIA_MDI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MDI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MDI, OFF);
#endif

#if (ICF_PN_MEDIA_MSTI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MSTI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MSTI, OFF);
#endif

#if (ICF_PN_MEDIA_STI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_STI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_STI, OFF);
#endif

#if (ICF_PN_MEDIA_TCPIP == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_TCPIP, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_TCPIP, OFF);
#endif

#if (ICF_PN_MEDIA_TRUST == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_TRUST, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_TRUST, OFF);
#endif

#if (ICF_PN_MEDIA_USB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_USB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_USB, OFF);
#endif

#if (ICF_PN_MEDIA_XTI == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_XTI, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_XTI, OFF);
#endif

#if (ICF_PN_TERMINAL_ADAPTER == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_TERMINAL_ADAPTER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_TERMINAL_ADAPTER, OFF);
#endif

#if (ICF_POC_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_POC_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_POC_SUPPORT, OFF);
#endif

#if (ICF_POWER_ON_BOOT_LOGO == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_POWER_ON_BOOT_LOGO, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_POWER_ON_BOOT_LOGO, OFF);
#endif

#if (ICF_POWER_RESOURCE_MANAGER == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_POWER_RESOURCE_MANAGER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_POWER_RESOURCE_MANAGER, OFF);
#endif

#ifdef ICF_PPM_AS_FILES
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PPM_AS_FILES, ICF_PPM_AS_FILES);
#endif

#ifdef ICF_PRODUCT_TYPE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PRODUCT_TYPE, ICF_PRODUCT_TYPE);
#if (ICF_PRODUCT_TYPE == ICF_S60_80_90)
#if (ICF_DUAL_MCU == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DUAL_MCU, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_DUAL_MCU, OFF);
#endif
#if (ICF_PN_MEDIA_SOS_USB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_SOS_USB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_SOS_USB, OFF);
#endif
#endif /* ICF_PRODUCT_TYPE == ICF_S60_80_90 */
#endif /* ICF_PRODUCT_TYPE */

#if (ICF_RAT_CDMA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_RAT_CDMA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_RAT_CDMA, OFF);
#endif /* ICF_RAT_CDMA == ON */

#if (ICF_RENDER_3D_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_RENDER_3D_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_RENDER_3D_LIB, OFF);
#endif

#ifdef ICF_RF_BAND_VARIABILITY
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_RF_BAND_VARIABILITY, ICF_RF_BAND_VARIABILITY);
#endif

#if (ICF_SCSI_PARSER == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SCSI_PARSER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SCSI_PARSER, OFF);
#endif

#if (ICF_SECENV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SECENV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SECENV, OFF);
#endif
#if (ICF_SECURITY == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY, OFF);
#endif
#if (ICF_SECURITY_KEYGUARD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY_KEYGUARD, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY_KEYGUARD, OFF);
#endif

#if (ICF_SECURITY_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY_LIB, OFF);
#endif

#if (ICF_SERVERS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SERVERS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SERVERS, OFF);
#endif

#if (ICF_SIM == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM, OFF);
#endif

#if (ICF_SIM_ATK == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM_ATK, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM_ATK, OFF);
#endif

#if (ICF_SIM_COMMON == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM_COMMON, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM_COMMON, OFF);
#endif

#if (ICF_SIM_HWDRV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM_HWDRV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM_HWDRV, OFF);
#endif

#if (ICF_SIM_HW_DRV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM_HW_DRV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIM_HW_DRV, OFF);
#endif

#if (ICF_SIMLOCK == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIMLOCK, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIMLOCK, OFF);
#endif

#if (ICF_SISA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SISA, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SISA, OFF);
#endif

#if (ICF_SLEEP_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SLEEP_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SLEEP_SUPPORT, OFF);
#endif

#if (ICF_SOS_PROXY == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SOS_PROXY, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SOS_PROXY, OFF);
#endif

#if (ICF_SSI_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SSI_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SSI_LIB, OFF);
#endif

#if (ICF_STEREO_IHF == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_STEREO_IHF, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_STEREO_IHF, OFF);
#endif

#if (ICF_ST_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ST_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ST_SERV, OFF);
#endif

#if (ICF_SUPERDONGLE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SUPERDONGLE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SUPERDONGLE, OFF);
#endif

#if (ICF_SYNCML_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SYNCML_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SYNCML_SERV, OFF);
#endif /* ICF_SYNCML_SERV == ON */

#if (ICF_TASKS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TASKS, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TASKS, OFF);
#endif
#if (ICF_TEST_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TEST_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TEST_SERV, OFF);
#endif
#if (ICF_TIME_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TIME_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TIME_SERV, OFF);
#endif
#if (ICF_TIME_ZONE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TIME_ZONE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TIME_ZONE, OFF);
#endif

#if (ICF_TOUCHPAD == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TOUCHPAD, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TOUCHPAD, OFF);
#endif

#if (ICF_TRACE_INTERFACE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TRACE_INTERFACE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TRACE_INTERFACE, OFF);
#endif

#if (ICF_TTY_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TTY_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TTY_SUPPORT, OFF);
#endif

#if (ICF_TUNEPLAYER_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TUNEPLAYER_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_TUNEPLAYER_SERV, OFF);
#endif

#if (ICF_UCS2_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_UCS2_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_UCS2_LIB, OFF);
#endif
#if (ICF_UI_THEMES == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_UI_THEMES, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_UI_THEMES, OFF);
#endif

#if (ICF_UNIVERSAL_HEADSET == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_UNIVERSAL_HEADSET, ON);
#if (ICF_UNIVERSAL_STEREO == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_UNIVERSAL_STEREO, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_UNIVERSAL_STEREO, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_UNIVERSAL_HEADSET, OFF);
#endif /* ICF_UNIVERSAL_HEADSET == ON */

#if (ICF_URL_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_URL_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_URL_LIB, OFF);
#endif

#if (ICF_USB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB, OFF);
#endif

#if (ICF_USB_ACA_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB_ACA_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB_ACA_SUPPORT, OFF);
#endif

#if (ICF_USB_FLASHING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB_FLASHING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB_FLASHING, OFF);
#endif

#if (ICF_USB_MASS_STORAGE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB_MASS_STORAGE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB_MASS_STORAGE, OFF);
#endif

#if (ICF_USB_MASS_STORAGE_INTERNAL_MEMORY == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB_MASS_STORAGE_INTERNAL_MEMORY, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_USB_MASS_STORAGE_INTERNAL_MEMORY, OFF);
#endif

#if (ICF_VERSIT_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VERSIT_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VERSIT_SERV, OFF);
#endif

#if (ICF_VIBRA == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIBRA, ON);
#if (ICF_VIBRA_IF_NEW == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIBRA_IF_NEW, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIBRA_IF_NEW, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIBRA, OFF);
#endif /* ICF_VIBRA == ON */

#if (ICF_VIDEO == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO, ON);
#if (ICF_VIDEOPLAYBACK == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEOPLAYBACK, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEOPLAYBACK, OFF);
#endif
#if (ICF_VIDEO_RECORDER == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_RECORDER, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_RECORDER, OFF);
#endif
#if (ICF_3RD_PARTY_VIDEOCODEC == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_3RD_PARTY_VIDEOCODEC, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_3RD_PARTY_VIDEOCODEC, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO, OFF);
#endif /* ICF_VIDEO == ON */

#if (ICF_VIDEO_CALL == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_CALL, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_CALL, OFF);
#endif

#if (ICF_VIDEO_SHARING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_SHARING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_SHARING, OFF);
#endif

#if (ICF_VOICE_RECORDING == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VOICE_RECORDING, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VOICE_RECORDING, OFF);
#endif

#if (ICF_VOICE_TAGS == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VOICE_TAGS, ON);
#ifdef ICF_MAX_VOICE_MODELS
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_MAX_VOICE_MODELS, ICF_MAX_VOICE_MODELS);
#endif
#if (ICF_SIND == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIND, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_SIND, OFF);
#endif
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VOICE_TAGS, OFF);
#endif /* ICF_VOICE_TAGS == ON */

#if (ICF_VRR_SERV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VRR_SERV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_VRR_SERV, OFF);
#endif

#if (ICF_WATCHDOG_SUPPORT == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_WATCHDOG_SUPPORT, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_WATCHDOG_SUPPORT, OFF);
#endif

#if (ICF_WLAN == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_WLAN, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_WLAN, OFF);
#endif

#if (ICF_WLAN_DRV == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_WLAN_DRV, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_WLAN_DRV, OFF);
#endif

#if (ICF_XBUS_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_XBUS_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_XBUS_LIB, OFF);
#endif

#if (ICF_ZLIB_LIB == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ZLIB_LIB, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ZLIB_LIB, OFF);
#endif

#if (ICF_ZLIB_DEFLATE == ON)
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ZLIB_DEFLATE, ON);
#else
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_ICF_ZLIB_DEFLATE, OFF);
#endif

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

    /* ------------------------------------------------------------------------- */
    /* Symbian variables */
    /* ------------------------------------------------------------------------- */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN
    {
        #include "iscnokiadefinitions.h"

        /* Include this environment variable in all Symbian PMD files (RD, RESTRICTED, PUBLIC) */
        pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_SOS_MON_OBJ_ID, EIscNokiaTraceCore);
    }
#endif

    /* ------------------------------------------------------------------------- */
    /* product info */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU

#ifdef PRODUCT_NAME
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_string(env, PMD_DEVICE_GENERAL, PMD_ENVIRONMENT_VAR_ID_PRODUCT_NAME, PRODUCT_NAME);
#endif
#ifdef PRODUCT_COMPILER_TYPE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, PMD_DEVICE_GENERAL, PMD_ENVIRONMENT_VAR_ID_PRODUCT_COMPILER_TYPE, PRODUCT_COMPILER_TYPE);
#endif
#ifdef PRODUCT_TEST_ENV
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, PMD_DEVICE_GENERAL, PMD_ENVIRONMENT_VAR_ID_PRODUCT_TEST_ENV, PRODUCT_TEST_ENV);
#endif
#ifdef PRODUCT_OS_TYPE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, PMD_DEVICE_GENERAL, PMD_ENVIRONMENT_VAR_ID_PRODUCT_OS_TYPE, PRODUCT_OS_TYPE);
#endif
#ifdef PRODUCT_CS_TYPE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) pmd_env_add_value(env, PMD_DEVICE_GENERAL, PMD_ENVIRONMENT_VAR_ID_PRODUCT_CS_TYPE, PRODUCT_CS_TYPE);
#endif

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */


    /* ------------------------------------------------------------------------- */
    /* device info */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE

    /* Store Monitor Server resource ID */
#ifdef AUTOGEN_DEVICE_MONITOR_SERVER_RESOURCE_ID
    pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MONITOR_SERVER_RESOURCE_ID, AUTOGEN_DEVICE_MONITOR_SERVER_RESOURCE_ID);
#endif

    /* Store device endianess for specific device and general device */
    /* Environment variable only created if device endianess is LE, ie. missing environment variable signifies BE */
#ifdef AUTOGEN_DEVICE_ENDIANESS
#if (AUTOGEN_DEVICE_ENDIANESS == AUTOGEN_DEVICE_ENDIANESS_LE)
    pmd_env_add_value(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_DEVICE_ENDIANESS, AUTOGEN_DEVICE_ENDIANESS_LE);
#endif
#endif

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE */

    /* add origin variable */
    {
        char str_origin[100];

        sprintf(str_origin, "autogen %s", AUTOGEN_VERSION_NUMBER);

        pmd_env_add_string(env, PMD_DEVICE_GENERAL, PMD_ENVIRONMENT_VAR_ID_PMD_FILE_ORIGIN, str_origin);
    }
    /* add monitor server version variable, version is exact */
    {
        char mon_ver[8];
        autogen_res* monitor_server = NULL;
        memset(mon_ver, '\0', 8);
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
        {
            int i=0;

            /* No aliases for PN_MODEM_MON_1 and PN_MODEM_MON_4 seems to be defined in pn_const.h */
            #ifndef PN_MODEM_MON_1
              #ifndef PN_MODEM_MCE
                i=4;    /* None of the symbols defined. Skip look-up completely */
              #else
                #define PN_MODEM_MON_1 PN_MODEM_MCE
              #endif
            #endif

            #ifndef PN_MODEM_MON_4
              #ifndef PN_MODEM_INFO
                i=4;    /* None of the symbols defined. Skip look-up completely */
              #else
                #define PN_MODEM_MON_4 PN_MODEM_INFO
              #endif
            #endif

            for (;i<4;i++) /* Modify in case number of modem mons (devices) increases */
            {
                switch(i)
                {
                case (0): monitor_server = util_get_res(PN_MODEM_MON_1); break;
                case (1): monitor_server = util_get_res(PN_MODEM_MON_2); break;
                case (2): monitor_server = util_get_res(PN_MODEM_MON_3); break;
                case (3): monitor_server = util_get_res(PN_MODEM_MON_4); break;
                default:;
                }
                if (monitor_server)
                    break;
            }
        }
#else
        {
            monitor_server = util_get_res(PN_MON);
        }
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE */
        if (monitor_server)
            sprintf(mon_ver, "%03hu.%03hu", monitor_server->base.ver.from[0], monitor_server->base.ver.from[1]);
        else
            sprintf(mon_ver, "---.---"); /* Should never happen, but ... */
        
        pmd_env_add_string(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_MONITOR_SERVER_VERSION, mon_ver);
    }
}

void pmd_env_vars_write_all(pmd_env* env, unsigned int n_envvars, const pmd_env_var* envvars, unsigned int flags)
{
    if (flags & PMD_WRITE_COUNTERS)
    {
        pmd_write_dword(env, n_envvars);
    }

    /* iterate through all env vars */
    while (envvars)
    {
        if (flags & PMD_WRITE_ENVVAR_OBJECT_IDS)
        {
            pmd_write_objid(env, &envvars->managedobj);
        }
        else if (flags & PMD_WRITE_ENVVAR_DATA)
        {
            /* write managed object */
            pmd_managedobj_write(env, &envvars->managedobj);

            /* write ID */
            pmd_write_word(env, envvars->id);

            /* write type */
            pmd_write_word(env, envvars->type);

            if (envvars->type == PMD_ENVIRONMENT_VAR_TYPE_STRING)
            {
                /* write value */
                pmd_write_string(env, envvars->value_string);
            }
            else
            {
                /* write value */
                pmd_write_dword(env, envvars->value);
            }
        }

        envvars = (const pmd_env_var*)envvars->next;
    }
}

void pmd_env_write_ids(pmd_env* env)
{
    /* write number of environment variables */
    pmd_write_dword(env, env->n_env_vars);

    /* write environment variables */
    {
        pmd_env_var* envvar = env->env_vars;
        while (envvar)
        {
            pmd_write_objid(env, &envvar->managedobj);

            envvar = envvar->next;
        }
    }
}

#define pmd_info_hash(id) (						\
			   (((((unsigned int) id) >> 24) & 0xFF) ^	\
			    ((((unsigned int) id) >> 16) & 0xFF) ^	\
			    ((((unsigned int) id) >>  8) & 0xFF) ^	\
			    (( (unsigned int) id       ) & 0xFF)	\
			    ) & 0xFF)

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_info_add

    Purpose: 
      Adds an info object to the PMD model

    Functional Description:
      Checks if the relevant info group already exists. If not then it is created.
      Checks if the ID of the info object already exists in the PMD model. If this is the case then this object is returned.
      Otherwise it creates a PMD info object and places the new object in the PMD model.

    Arguments:
      env       - [in] Environment
      device_id - [in] Device id
      type      - [in] Type of the info group
      name      - [in] Name of the info object
      id        - [in] ID of the info object
      n_data    - [in] How many of the data1 - data4 that are in use
      data1     - [in] Info object data
      data2     - [in] Info object data
      data3     - [in] Info object data
      data4     - [in] Info object data

    Returns:
      Pointer to the found/created info object in the PMD model
*/
/* --------------------------------------------------------------------------------------------- */
pmd_info* pmd_info_add(pmd_env* env, unsigned short device_id, unsigned int type, const char* name, unsigned int id, unsigned int n_data,
                       unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4)
{
    /* Find info group. Create it if not already present */
    pmd_info_group* info_group = pmd_info_group_find(env, device_id, type);
    pmd_info* info = NULL;

    if (!info_group)
    {
        info_group = pmd_info_group_add(env, device_id, type, n_data);
    }

    /* Check if id already have been added. Skip add if already present */
    info = pmd_info_find(info_group, id);
    if (!info)
    {
        info = pmd_info_add_entry(env, info_group, name, id, data1, data2, data3, data4);
    }

    return info;
}
/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_info_add_uncond

    Purpose: 
      Adds an info object to the PMD model
  
    Functional Description:
      As pmd_info_add() described above, except that the function does not check if the ID of the info
      object is already in the PMD model. This means that the info object is added unconditional.

    Arguments:
      env       - [in] Environment
      device_id - [in] Device id
      type      - [in] Type of the info group
      name      - [in] Name of the info object
      id        - [in] ID of the info object
      n_data    - [in] How many of the data1 - data4 that are in use
      data1     - [in] Info object data
      data2     - [in] Info object data
      data3     - [in] Info object data
      data4     - [in] Info object data
 
    Returns:
      Pointer to the found/created info object in the PMD model
*/
/* --------------------------------------------------------------------------------------------- */
pmd_info* pmd_info_add_uncond(pmd_env* env, unsigned short device_id, unsigned int type, const char* name, unsigned int id, unsigned int n_data,
                              unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4)
{
    /* Find info group. Create it if not already present */
    pmd_info_group* info_group = pmd_info_group_find(env, device_id, type);
    pmd_info* info = NULL;

    if (!info_group)
    {
        info_group = pmd_info_group_add(env, device_id, type, n_data);
    }

    /* Add info unconditional */
    info = pmd_info_add_entry(env, info_group, name, id, data1, data2, data3, data4);

    return info;
}
/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_info_add_entry

    Purpose: 
      Adds an info object to the PMD model

    Functional Description:
      Adds info object to the PMD model given the info group.

    Arguments:
      env        - [in] Environment
      info_group - [in] Info group where info object is inserted.
      name       - [in] Name of the info object
      id         - [in] ID of the info object
      data1      - [in] Info object data
      data2      - [in] Info object data
      data3      - [in] Info object data
      data4      - [in] Info object data

    Returns:
      Pointer to the created info object in the PMD model
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL pmd_info* pmd_info_add_entry(pmd_env* env, pmd_info_group* info_group, const char* name, unsigned int id, 
                              unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4)
{
    pmd_info* info = NULL;
    unsigned int hash = pmd_info_hash(id);

    /* Allocate new object */
    info = (pmd_info*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_info));

    /* Initialize new object */
    pmd_namedobj_init(env, &info->namedobj, name, FALSE, PMD_CLASS_NULL, 0);

    info->id = id;

    info->data[0] = data1;
    info->data[1] = data2;
    info->data[2] = data3;
    info->data[3] = data4;

    /* Insert object in list */
    info->next = info_group->info;
    info_group->info = info;

    /* Insert object into hash */
    info->hash_next              = info_group->hash_table[hash];
    info_group->hash_table[hash] = info;

    ++info_group->n_info;

    return info;
}

LOCAL pmd_info* pmd_info_find(pmd_info_group* info_group, unsigned int id)
{
    pmd_info* info = info_group->hash_table[pmd_info_hash(id)];

    while (info && info->id != id)
    {
        info = info->hash_next;
    }

    return info;
}

LOCAL void pmd_info_write(pmd_env* env, const pmd_info* info, unsigned int n_data)
{
    unsigned int n;

    /* write named object */
    pmd_namedobj_write(env, &info->namedobj);

    /* write ID */
    pmd_write_dword(env, info->id);

    /* write data */
    for (n = 0; n < n_data; n++)
    {
        pmd_write_dword(env, info->data[n]);
    }
}

LOCAL pmd_info_group* pmd_info_group_find(pmd_env* env, unsigned short device_id, unsigned int type)

{
    pmd_device* device = pmd_device_find(env, device_id);
	pmd_info_group* info_group = device ? device->info_groups : env->info_groups;

    while (info_group && info_group->type != type)
    {
        info_group = info_group->next;
    }

    return info_group;
}

pmd_info_group* pmd_info_group_add(pmd_env* env, unsigned short device_id, unsigned int type, unsigned int n_data)
{
    pmd_info_group* info_group = pmd_info_group_find(env, device_id, type);
    if (!info_group)
    {
        pmd_device* device = pmd_device_find(env, device_id);

        /* allocate CInfoGroup object */
        info_group = (pmd_info_group*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_info_group));

        /* initialize CManagedObject part */
        pmd_managedobj_init(&info_group->managedobj, FALSE, PMD_CLASS_INFO_GROUP, 0);

        /* initialize CInfoGroup part */
        info_group->type   = type;
        info_group->n_data = n_data;

        info_group->n_info = 0;
        info_group->info   = NULL;

        /* insert object in list */
        if (device)
        {
            info_group->next    = device->info_groups;
            device->info_groups = info_group;

            ++device->n_info_groups;
        }
        else
        {
            info_group->next = env->info_groups;
            env->info_groups = info_group;

            ++env->n_info_groups;
        }
    }

    return info_group;
}

LOCAL void pmd_info_group_write(pmd_env* env, const pmd_info_group* info_group)
{
    const pmd_info* info = info_group->info;

    /* write CManagedObject part */
    pmd_managedobj_write(env, &info_group->managedobj);

    /* write group ID */
    pmd_write_dword(env, info_group->type);

    /* write number of data */
    pmd_write_dword(env, info_group->n_data);

    /* write number of info objects */
    pmd_write_dword(env, info_group->n_info);

    while (info)
    {
        pmd_info_write(env, info, info_group->n_data);

        info = (const pmd_info*)info->next;
    }
}

void pmd_info_groups_generate(pmd_env* env)
{
#ifdef AUTOGEN_INCLUDE_NOS_TRACES
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD)
    {
        pmd_info_generate_os(env);
    }
#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

    pmd_info_generate_symbols(env);
}

void pmd_info_groups_write_all(pmd_env* env, unsigned int n_infogroups, const pmd_info_group* infogroups)
{
    /* write number of info groups */
    pmd_write_dword(env, n_infogroups);

    while (infogroups)
    {
        pmd_info_group_write(env, infogroups);

        infogroups = (const pmd_info_group*)infogroups->next;
    }
}

/* End of file output_pmd_info.c */
