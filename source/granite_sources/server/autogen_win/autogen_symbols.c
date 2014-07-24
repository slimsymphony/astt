/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_symbols.c
                -----------------
                SW Module






Project:          autogen

%name:            autogen_symbols.c %
%version:         co1tss#44 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Aug  3 12:55:14 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file contains all common symbol table definitions
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_prop.h"
#include "autogen_init.h"
#include "autogen_util.h"
#include "pmd_heap.h"
#include "pmdconstants.h"

#ifdef AUTOGEN_INCLUDE_NOS_TRACES
 #undef OS_TASK_NAME
 #undef OS_TIMER_NAME
 #undef OS_RESOURCE_NAME
 #undef OS_BLOCK_SET_NAME
 #undef OS_CONF_H

 #include "os.h"
#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

#include <string.h>
#include <stdlib.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
#define LOCAL static
#endif /* LOCAL */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 LOCAL void read_pn_obj_auto(const char* filename);
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: read_pn_obj_auto
 
    Purpose: 
        Reads the file pn_obj_auto.h and adds the constants to the symbol table
        'SYMBOLS_PN_OBJECT'.
*/
/* --------------------------------------------------------------------------------------------- */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU

LOCAL void read_pn_obj_auto(const char* filename)
{
    /* open file */
    FILE* fobj = fopen(filename, "rt");
    if (fobj)
    {
        const char* short_filename = util_get_filename(filename);

        autogen_res* res = util_get_unique_res(RESOURCE_SYMBOLS);

        printf("    Importing constants from '%s'...\n", (short_filename != NULL) ? short_filename : filename);

        if (res)
        {
            /* find table where constants should be added */
            autogen_it tbl_it = INIT_ITERATOR;
            autogen_tbl* tbl;
            autogen_tbl* tbl_10;
            autogen_tbl* tbl_16;

            tbl_it.typemask    = AUTOGEN_OBJ_TBL;
            tbl_it.subtypemask = AUTOGEN_TBL_CONST;

            tbl_it.obj.name = "SYMBOLS_PN_OBJECT";
            tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);

            tbl_it.obj.name = "SYMBOLS_PN_OBJECT_10";
            tbl_10 = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);

            tbl_it.obj.name = "SYMBOLS_PN_OBJECT_16";
            tbl_16 = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);

            while (!feof(fobj))
            {
                char str_line[256];

                fgets(str_line, 255, fobj);

                if (strstr(str_line, "#define PN_OBJ"))
                {
                    char const_name[256] = "";
                    unsigned int const_id = 0;

                    sscanf(str_line, "#define %s 0x%x", const_name, &const_id);

                    /* only add valid constants and only 10 bit values */
                    if (strlen(const_name) > 0 && const_id > 0 && const_id <= 0x3FF)
                    {
                        autogen_obj* entry = autogen_obj_create(NULL, 0, tbl->base.res, &tbl->base, sizeof(autogen_obj), AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, 
                            const_id, pmd_heap_strdup(const_name), NULL);

                        autogen_obj_list_add_obj(&tbl->base.child_list, entry, AUTOGEN_ENV_NONE);
                    }
                    /* add 10 bit and 16 bit value */
                    if (strlen(const_name) > 0 && const_id > 0)
                    {
                        autogen_obj* entry = autogen_obj_create(NULL, 0, tbl_10->base.res, &tbl_10->base, sizeof(autogen_obj), AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, 
                            const_id, pmd_heap_strdup(const_name), NULL);

                        autogen_obj_list_add_obj(&tbl_10->base.child_list, entry, AUTOGEN_ENV_NONE);

                        entry = autogen_obj_copy_deep(entry, NULL, &tbl_16->base, &entry->ver);

                        autogen_obj_list_add_obj(&tbl_16->base.child_list, entry, AUTOGEN_ENV_NONE);
                    }
                }
            }
        }

        fclose(fobj);
    }
}

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: build_symbols
 
    Purpose: 
        Build common symbols
*/
/* --------------------------------------------------------------------------------------------- */

void build_symbols(const char* obj_filename)
{
#ifndef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
    obj_filename;
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

#include "autogen_symbols.h"

    /* Generate all missing tables based on global symbol configuration */
    {
        int n;
        autogen_res* sym_res = util_get_unique_res(RESOURCE_SYMBOLS);
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST;

        for (n = 0; n < AUTOGEN_SYMBOL_TYPES_MAX; n++)
        {
            tbl_it.obj.name = g_symbol_conf[n].tblname;

            if (g_symbol_conf[n].type != 0 && !autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list))
            {
                /* Now, create table... */
                autogen_tbl* new_tbl = (autogen_tbl*)autogen_obj_create(NULL, 0, sym_res, &sym_res->base, sizeof(autogen_tbl), 
                    AUTOGEN_OBJ_TBL, AUTOGEN_TBL_CONST, 0, g_symbol_conf[n].tblname, NULL);

                autogen_obj_list_init(&new_tbl->base.child_list, &new_tbl->base, AUTOGEN_OBJ_LIST_SORTED_BY_ID | AUTOGEN_OBJ_LIST_SORTED_BY_NAME, 100);

                /* Initialize members, not part of autogen_obj */
                new_tbl->base.res = sym_res;
                new_tbl->length   = g_symbol_conf[n].length;
                new_tbl->order    = BE;
                new_tbl->orgtbl   = new_tbl;

                /* Add table */
                autogen_obj_list_add_obj(&sym_res->tbl_list, &new_tbl->base, AUTOGEN_ENV_NONE);

                /* Generate entries ? */
                if (g_symbol_conf[n].pmd_const_map)
                {
                    unsigned int i;

                    for (i = 0; i < g_symbol_conf[n].pmd_const_map_size; i++)
                    {
                        if (g_symbol_conf[n].pmd_const_map[i].name)
                        {
						    autogen_obj* entry = autogen_obj_create(NULL, 0, new_tbl->base.res, &new_tbl->base, sizeof(autogen_obj), 
                                AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, 
                                g_symbol_conf[n].pmd_const_map[i].id, g_symbol_conf[n].pmd_const_map[i].name, NULL);

                            autogen_obj_list_add_obj(&new_tbl->base.child_list, entry, AUTOGEN_ENV_NONE);
                        }
                    }
                }
            }
        }
    }

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
    if (obj_filename && obj_filename[0])
    {
        read_pn_obj_auto(obj_filename);
    }
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */
}

void build_symbols_post()
{
#ifdef AUTOGEN_INCLUDE_INVARIANT_TRACES
    {
        autogen_res* sym_res = util_get_unique_res(RESOURCE_SYMBOLS);
        autogen_it tbl_it = INIT_ITERATOR;
        autogen_obj* tbl;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST;

        /* Fill out entity ID map */
        tbl_it.obj.name = "SYMBOLS_INVARIANT_TRACE_ENTITY_ID";

        tbl = autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
        if (tbl)
        {
            autogen_res* res;
            autogen_it res_it = INIT_ITERATOR;

            res_it.subtypemask = RESOURCE_TRC_INVARIANT;
            res_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

            res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
            while (res)
            {
                autogen_obj* entry = autogen_obj_create(NULL, 0, tbl->res, tbl, sizeof(autogen_obj), 
                    AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, 
                    res->base.id, res->base.name, NULL);

                autogen_obj_list_add_obj(&tbl->child_list, entry, AUTOGEN_ENV_NONE);

                res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
            }
        }
    }
 #endif /* AUTOGEN_INCLUDE_INVARIANT_TRACES */
}

/*  End of file autogen_symbols.c  */
