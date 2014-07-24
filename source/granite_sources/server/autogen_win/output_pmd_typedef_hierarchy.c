/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_pmd_typedef_hierarchy.c
                ------------------------------
                SW Module






Project:          autogen

%name:            output_pmd_typedef_hierarchy.c %
%version:         12 %
%instance:        co1tss_1 %
%derived_by:      cjhansen %
%date_modified:   Fri Sep 14 15:52:39 2007 %

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


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL
#endif /* LOCAL */


/* ============================================================================================= */
/* Typedefinition module functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_typedef_module_add
 
    Purpose: 
        Creates a new definition module in the PMD data model
 
    Functional Description:
        A new definition module named 'name' is created in the definition module
        'par_mod'. If the definition module already exists, a pointer to the existing module
        is returned, else a pointer to the new module is returned

    Arguments: 
        name    - [in] name of the definition module
        par_mod - [in] parent module to the new module

    Returns:
        Pointer to new module
*/
/* --------------------------------------------------------------------------------------------- */
pmd_mod* pmd_typedef_module_add(pmd_env* env, const char* name, pmd_mod* par_mod)
{
    pmd_mod* module = NULL;

    /* if first module, the module represents the root module */
    if (!env->typ_root_module)
    {
        module = (pmd_mod*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_mod));

        env->typ_root_module = module;
    }
    /* else, the object should be placed as module */
    else
    {
        pmd_mod* trav_mod = par_mod->child;

        /* if the module is the first module in the parent module */
        if (!trav_mod)
        {
            module = (pmd_mod*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_mod));

            par_mod->child = module;
        }
        /* else, check if module already exist. If not, place object at the 
           end of modules in the parent module 
        */
        else
        {
            pmd_mod* last_mod = NULL;

            /* find module */
            while (trav_mod && trav_mod->name[0] < name[0])
            {
                last_mod = trav_mod;
                trav_mod = trav_mod->next;
            }

            while (trav_mod && trav_mod->name[0] == name[0] && strcmp(trav_mod->name, name) < 0)
            {
                last_mod = trav_mod;
                trav_mod = trav_mod->next;
            }

            if (trav_mod && !strcmp(trav_mod->name, name))
            {
                module = trav_mod;
            }
            else                
            {
                module = (pmd_mod*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_mod));

                if (last_mod)
                {
                    last_mod->next = module;
                }
                else
                {
                    par_mod->child = module;
                }

                module->next = trav_mod;    
            }
        }
    }
    
    /* initialize object */
    if (!module->name)
    {
        module->name      = pmd_heap_strdup_h(env->heap_handle, name);
        module->parent    = par_mod;
    }

    return module;
}

pmd_mod* pmd_typedef_module_lookup(const char* name, pmd_mod* par_mod)
{
    pmd_mod* mod = (par_mod ? par_mod->child : NULL);
    
    if (!name || !name[0])
    {
        return NULL;
    }

    /* find module */
    while (mod && strcmp(mod->name, name) < 0)
    {
        mod = mod->next;
    }

    if (mod && strcmp(mod->name, name))
    {
        mod = NULL;
    }
    
    return mod;
}

const char* pmd_typedef_module_get_name_from_object(const autogen_obj* obj)
{
    if (obj->type == AUTOGEN_OBJ_DATA)
    {
        if (obj->subtype == AUTOGEN_DATA_FTD)
        {
            return "FTD data";
        }
        else if (obj->subtype == AUTOGEN_DATA_PPC)
        {
            return "PPC data";
        }
    }
    else if (obj->type == AUTOGEN_OBJ_SEQ)
    {
        return "Sequences";
    }
    else if (obj->type == AUTOGEN_OBJ_SB)
    {
        return "Sub blocks";
    }
    else if (obj->type == AUTOGEN_OBJ_RES)
    {
        const autogen_res* res = (const autogen_res*)obj;

        if ((res->base.subtype & RESOURCE_TRC_ANY) && (util_get_tracegroup_type(res) != AUTOGEN_OBJ_TRACEGRP_NONE))
        {
            return pmd_constant_lookup_message_type_name(g_trcgrp_conf[util_get_tracegroup_type(res)].msg_type);
        }
        else if (res->conf->is_unique)
        {
            return res->logical_name;
        }
        else
        {
            char* res_name = pmd_heap_alloc(strlen(res->logical_name) + 10);
            sprintf(res_name, "%s %d", res->logical_name, res->index);

            return res_name;
        }
    }
    else if (obj->type == AUTOGEN_OBJ_MSG)
    {
        if (obj->flag & AUTOGEN_MSG_REQ)
        {
            return "Requests";
        }
        else if (obj->flag & AUTOGEN_MSG_RESP)
        {
            return "Responses";
        }
        else if (obj->flag & AUTOGEN_MSG_NTF)
        {
            return "Notifications";
        }
        else if (obj->flag & AUTOGEN_MSG_IND)
        {
            return "Indications";
        }
        else if (obj->flag & AUTOGEN_MSG_TRC)
        {
            return "Traces";
        }
    }

    return "";
}

/* ============================================================================================= */
/* Typedefinition type functions */
/* ============================================================================================= */

void pmd_typedef_type_add(pmd_mod* module, pmd_typ* type)
{
    if (module)
    {
        /* insert type at right (sorted) position */
        pmd_typ* trav_type = module->type;
        pmd_typ* last_type = NULL;

        if (!trav_type)
        {
            module->type = type;
        }
        else
        {
            while (trav_type && strcmp(trav_type->name, type->name) < 0)
            {
                last_type = trav_type;
                trav_type = trav_type->next;
            }

            if (last_type)
            {
                last_type->next = type;
            }
            else
            {
                module->type = type;
            }

            type->next = trav_type;
        }
    }
}

pmd_typ* pmd_typedef_type_lookup(const char* name, pmd_mod* module, int search_resursively)
{
    pmd_typ* trav_typ = module ? module->type : NULL;

    /* find type */
    while (trav_typ && strcmp(trav_typ->name, name) < 0)
    {
        trav_typ = trav_typ->next;
    }

    if (trav_typ && strcmp(trav_typ->name, name) != 0)
    {
        trav_typ = NULL;
    }

    if (!trav_typ && search_resursively)
    {
        trav_typ = pmd_typedef_type_lookup(name, module->child, FALSE);
    }

    return trav_typ;
}

void pmd_typedef_module_write(pmd_env* env, const pmd_mod* mod)
{    
    /* iterate through all modules */
    while (mod)
    {
        const pmd_typ* type = mod->type;

        /* write the child module */
        if (mod->child)
        {
            pmd_typedef_module_write(env, mod->child);
        }
        
        /* write the module sequence */
        if (mod->seq)
        {
            pmd_seq_write(env, mod->seq);
        }
        
        /* write the module types */
        while (type)
        {
            pmd_type_write_any(env, type);

            type = type->next;
        }

        /* next module */
        mod = mod->next;
    }
}
