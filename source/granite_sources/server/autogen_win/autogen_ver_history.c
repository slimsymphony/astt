/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_ver_history.c
                ---------------------
                SW Module






Project:          autogen

%name:            autogen_ver_history.c %
%version:         co1tss#31 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Wed Jan 28 11:09:30 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file contains functions to auto generate the ISI version history for an interface
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */
#include "autogen_def.h"
#include "autogen_object.h"
#include "autogen_util.h"
#include "autogen_prop.h"
#include "autogen_ver_history.h"

#include <string.h>
#include <stdlib.h>

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL static
#endif /* LOCAL */

LOCAL void version_history_generate_type(autogen_res* res, autogen_obj* ver, autogen_obj_list* obj_list, autogen_ver* parent_ver, unsigned int flag_none);

/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: version_history_generate_type
 
    Purpose: 
        Generates version history for a certain type of objects
 
    Functional Description:
		Compares object versions (from, to) and previous object versions to current version.
		Determines whether the
		-	object has been added
		-	object has been changed
		-	object has been discontinued (deleted)
		-	object has been re-introduced (a version gap has occurred)

    Arguments: 
        res		   - [in] resource, which version history belongs to
        res		   - [in] version of interface
		obj_list   - [in] object list to be checked
		parent_ver - [in] version of parent object (optional)
        flag_none  - [in] flags, which must not be on for searched objects
*/
/* --------------------------------------------------------------------------------------------- */

LOCAL void version_history_generate_type(autogen_res* res, autogen_obj* ver, autogen_obj_list* obj_list, autogen_ver* parent_ver, unsigned int flag_none)
{
    autogen_obj* obj;
    autogen_it obj_it = INIT_ITERATOR;

    if (!obj_list || obj_list->n_obj == 0) return;

    obj_it.flagnone  = flag_none;

    if (obj_list->flag & AUTOGEN_OBJ_LIST_SORTED_BY_NAME)
    {
        obj_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_NAME;
        obj_it.vercrit   = AUTOGEN_OBJ_VERSION_FIRST;
    }
    else
    {
        obj_it.sort_type = AUTOGEN_OBJ_LIST_SORT_NONE;
    }

    /* Make version history for objects in list */
    for (obj = autogen_obj_find_in_list(&obj_it, obj_list); obj != NULL; obj = autogen_obj_find_next_in_list(&obj_it))
    {
        if (obj->ver.system != AUTOGEN_VERSION_ISI)
        {
            continue;
        }
        if (obj->type == AUTOGEN_OBJ_ITEM && 
            obj->subtype != AUTOGEN_ITEM_CHOICE && obj->subtype != AUTOGEN_ITEM_CASE && obj->subtype != AUTOGEN_ITEM_LST)
        {
            continue;
        }

        /* For other items than cases, not need to look for other versions of each item */
        if (obj->type == AUTOGEN_OBJ_ITEM && obj->subtype != AUTOGEN_ITEM_CASE)
        {
            /* Sub block ID lists should not be generated. 
               Problem is that these ID's should not be in the child list in the first place...
            */
            if (obj->subtype == AUTOGEN_ITEM_LST && (obj->flag & AUTOGEN_LST_SBID))
            {
            }
            else
            {
                version_history_generate_type(res, ver, &obj->child_list, &obj->ver, 0);
            }
        }
        else
        {
            autogen_obj* last_obj = NULL;  /* last version of object */
            autogen_obj* obj_variation;
            autogen_it obj_it_inner = INIT_ITERATOR;

            /* outer loop has found an interesting object */
            obj_it_inner.typemask    = obj->type;
            obj_it_inner.flagnone    = flag_none;
            obj_it_inner.obj.name    = obj->name;
            obj_it_inner.sort_type   = obj_it.sort_type;

            /* It is OK to change constant tables to bit mask tables */
            if (obj->type == AUTOGEN_OBJ_TBL && (obj->subtype == AUTOGEN_TBL_CONST || obj->subtype == AUTOGEN_TBL_BIT))
            {
                obj_it_inner.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
            }

            obj_variation = autogen_obj_find_in_list(&obj_it_inner, obj_list);
            while (obj_variation)
            {
                /* If version of object is identical to parent version, ignore... */
                if (parent_ver && autogen_obj_ver_is_exact(parent_ver, &obj_variation->ver) && obj_variation->type != AUTOGEN_OBJ_MSG)
                {
                }
                /* Else if first object, and object version is not "first" version, the object has been added */
                else if (last_obj == NULL)
                {
                    /* Object is added after parent */
                    if (parent_ver && autogen_ver_comp(parent_ver->from, obj_variation->ver.from) != AUTOGEN_VER_EQUAL)
                    {
                        version_history_add_entry(res, obj_variation, AUTOGEN_VERSION_HISTORY_OBJECT_ADDED);
                    }
                    /* Object is added (and has no parent) */
                    else if ((!parent_ver || obj_variation->type == AUTOGEN_OBJ_MSG) && res->ver_list.n_obj > 0 && autogen_ver_comp(res->ver_list.map[AUTOGEN_OBJ_LIST_SORT_BY_VERSION][0]->ver.from, obj_variation->ver.from) != AUTOGEN_VER_EQUAL &&
                        (obj_variation->ver.from[0] != 0 || obj_variation->ver.from[1] != 0))
                    {
                        version_history_add_entry(res, obj_variation, AUTOGEN_VERSION_HISTORY_OBJECT_ADDED);
                    }
                }
                else
                {
                    if (autogen_ver_comp(last_obj->ver.to, obj_variation->ver.from) == AUTOGEN_VER_EQUAL)
                    {
                        /* Exception here is sub block list. Don't add any entries regarding changes */
                        if (obj_variation->type != AUTOGEN_OBJ_REF)
                        {
                            /* Moving to shared file */
                            if ((obj_variation->flag & AUTOGEN_OBJ_IS_SHARED) && !(last_obj->flag & AUTOGEN_OBJ_IS_SHARED))
                            {
                                version_history_add_entry(res, obj_variation, AUTOGEN_VERSION_HISTORY_OBJECT_MOVED_TO_SHARED_FILE);
                            }
                            else if (last_obj->type == AUTOGEN_OBJ_TBL && last_obj->subtype != obj_variation->subtype)
                            {
                                if (last_obj->subtype == AUTOGEN_TBL_CONST)
                                {
                                    version_history_add_entry(res, obj_variation, AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_CONST_TBL_TO_BIT_TBL);
                                }
                                else
                                {
                                    version_history_add_entry(res, obj_variation, AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_BIT_TBL_TO_CONST_TBL);
                                }
                            }
                            else
                            {
                                version_history_add_entry(res, obj_variation, AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED);
                            }
                        }
                    }
                    else
                    {
                        version_history_add_entry(res, last_obj, AUTOGEN_VERSION_HISTORY_OBJECT_DISCONTINUED);
                        version_history_add_entry(res, obj_variation, AUTOGEN_VERSION_HISTORY_OBJECT_REINTRODUCED);
                    }
                }

                /* Check child list */
                version_history_generate_type(res, ver, &obj_variation->child_list, &obj_variation->ver, 0);

                /* Check submessages */
                if (obj_variation->type == AUTOGEN_OBJ_MSG_BASE)
                {
                    version_history_generate_type(res, ver, &((autogen_seq*)obj_variation)->submsg_list, &obj_variation->ver, 0);
                }

                last_obj = obj_variation;

                obj_variation = autogen_obj_find_next_in_list(&obj_it_inner);
            }

            /* Check for discontinued object */
            if (last_obj)
            {
                /* Object is discontinued before parent */
                if (parent_ver && autogen_ver_comp(last_obj->ver.to, parent_ver->to) != AUTOGEN_VER_EQUAL)
                {
                    version_history_add_entry(res, last_obj, AUTOGEN_VERSION_HISTORY_OBJECT_DISCONTINUED);
                }
                /* Object is discontinued (and has no parent) */
                else if (!parent_ver && last_obj->ver.to[0] != 256)
                {
                    version_history_add_entry(res, last_obj, AUTOGEN_VERSION_HISTORY_OBJECT_DISCONTINUED);
                }
            }
        }
    }
}

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: version_history_add_entry
 
    Purpose: 
        Add versions history entry to object
 
    Functional Description:
		Adds version history information to object.
		Determines whether the

    Arguments: 
        ver			- [in] version of interface
		changed_obj	- [in] object changed in furrent version
		type	    - [in] type of change. Any of AUTOGEN_VERSION_HISTORY_XXX constants

*/
/* --------------------------------------------------------------------------------------------- */

void version_history_add_entry(autogen_res* res, autogen_obj* changed_obj, unsigned int type)
{
    autogen_obj* ver_obj_it = autogen_obj_get_first_in_list(&res->ver_list);
    unsigned short* ver_comp = changed_obj->ver.from;

    if (type == AUTOGEN_VERSION_HISTORY_OBJECT_DISCONTINUED)
    {
        ver_comp = changed_obj->ver.to;
    }

    /* If item, only cases / filler replacements should be added */
    if (changed_obj->type == AUTOGEN_OBJ_ITEM && changed_obj->subtype != AUTOGEN_ITEM_CASE && type != AUTOGEN_VERSION_HISTORY_FILLER_REPLACED)
    {
        return;
    }
    /* If message, no base messages should be added */
    if (changed_obj->type == AUTOGEN_OBJ_MSG_BASE && (changed_obj->flag & AUTOGEN_MSG_BASE_IS_AUTO_DEFINED))
    {
        return;
    }

    /* Find version object */
    while (ver_obj_it && autogen_ver_comp(ver_obj_it->ver.from, ver_comp) != AUTOGEN_VER_EQUAL)
    {
        ver_obj_it = ver_obj_it->next;
    }

    /* Add the new version history entry to the version object */
    if (ver_obj_it)
    {
        autogen_obj* entry = autogen_obj_create(NULL, 0, res, ver_obj_it, sizeof(autogen_obj), AUTOGEN_OBJ_VERSION_HISTORY, type, 0, NULL, NULL);
        entry->ptr = changed_obj;

        switch (type)
        {
        case AUTOGEN_VERSION_HISTORY_FILLER_REPLACED:
        case AUTOGEN_VERSION_HISTORY_OBJECT_ADDED:
        case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_COMPATIBLE:
        case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_CONST_TBL_TO_BIT_TBL:
        case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_BIT_TBL_TO_CONST_TBL:
        case AUTOGEN_VERSION_HISTORY_OBJECT_REINTRODUCED:
            ver_obj_it->flag |= AUTOGEN_VERSION_HAS_COMPATIBLE_CHANGES;
            break;

        case AUTOGEN_VERSION_HISTORY_OBJECT_DISCONTINUED:
        case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED:
            ver_obj_it->flag |= AUTOGEN_VERSION_HAS_INCOMPATIBLE_CHANGES;
            break;
        }

        autogen_obj_list_add_obj(&ver_obj_it->child_list, entry, AUTOGEN_ENV_NONE);
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: version_history_generate
 
    Purpose: 
        Generates complete version history for the given resource
 
    Functional Description:

    Arguments: 
        res         - [in] the resource for which the version history should be generated
		current_ver - [in] version currently being processed
*/
/* --------------------------------------------------------------------------------------------- */
void version_history_generate(autogen_res* res)
{
    autogen_obj* min_ver = res->ver_list.map[AUTOGEN_OBJ_LIST_SORT_BY_VERSION][0];

    /* Make version history for Messages */
    if (prop_has(&res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        version_history_generate_type(res, min_ver, &res->msg_dev_dep_req_list, NULL, 0);
        version_history_generate_type(res, min_ver, &res->msg_dev_dep_resp_list, NULL, 0);
    }
    else
    {
        version_history_generate_type(res, min_ver, &res->msg_list, NULL, 0);
    }

    /* Make version history for sequences */
    version_history_generate_type(res, min_ver, &res->seq_list, NULL, AUTOGEN_SEQ_IS_NOT_STRUCT);

    /* Make version history for tables */
    version_history_generate_type(res, min_ver, &res->tbl_list, NULL, 0);

    /* Make version history for constants */
    version_history_generate_type(res, min_ver, &res->const_list, NULL, 0);

    /* Make version history for shared resources */
    version_history_generate_type(res, min_ver, &res->shared_list, NULL, 0);
}

void version_history_report_warnings(autogen_obj* ver_obj)
{
    if ((!prop_has(ver_obj, PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)) && (!prop_has(util_get_base_parent(ver_obj), PROPERTY_ISI_VERSIONING_NOT_SUPPORTED)))
    {
        autogen_it obj_it = INIT_ITERATOR;
        autogen_obj* obj = NULL;

        /* General check, if version is correctly used */
        if (ver_obj->flag & AUTOGEN_VERSION_HAS_INCOMPATIBLE_CHANGES)
        {
            if (ver_obj->ver.from[1] != 0)
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 4,
                    "Possibly incompatible changes made, but version indicates compatible changes!");
            }
        }
        else if (ver_obj->flag & AUTOGEN_VERSION_HAS_COMPATIBLE_CHANGES)
        {
            if (ver_obj->ver.from[1] == 0)
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 6,
                    "Compatible changes made, but version indicates incompatible changes!");
            }
        }
        else
        {
            if (ver_obj->ver.from[1] == 0)
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                    "No changes made, but version indicates major change!");
            }
        }

        /* Check if version comments exist (if no auto generated comments) */
        if (!ver_obj->cmt_list && ver_obj->child_list.n_obj == 0)
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                "No comments are defined for the ISI version");
        }

        /* Else check for specific warnings */
        obj_it.subtypemask = AUTOGEN_VERSION_HISTORY_OBJECT_REINTRODUCED;

        obj = autogen_obj_find_in_list(&obj_it, &ver_obj->child_list);
        while (obj)
        {
            /* Output to autogen.log - inform of version gap */
            if (!prop_has(obj, PROPERTY_SUPPRESS_AUTOGEN_WARNINGS))
            {
                autogen_obj* gap_obj = (autogen_obj*)obj->ptr;
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 5,
                    "Re-introduced %s %s. Gap before version %03d.%03d detected", 
                    util_get_obj_type_name(gap_obj), util_get_obj_name(gap_obj), gap_obj->ver.from[0], gap_obj->ver.from[1]);
            }

            obj = autogen_obj_find_next_in_list(&obj_it);
        }
    }
}

/*  End of file autogen_ver_history.c  */
