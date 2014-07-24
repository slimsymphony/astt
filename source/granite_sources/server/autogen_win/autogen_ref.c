/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_ref.c
                -------------
                SW Module






Project:          autogen

%name:            autogen_ref.c %
%version:         16 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Wed Nov 11 16:51:50 2009 %

Copyright (c) Nokia. All rights reserved
*/

/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the source code for handling references (tags).
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_object.h"
#include "autogen_prop.h"
#include "autogen_util.h"
#include "autogen_ref.h"

#include "pmdconstants.h"
#include "pmd_heap.h"

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

typedef struct t_autogen_ref_conf
{
    struct t_autogen_ref_conf* next;

    /* Reference type (AUTOGEN_REFERENCE_TYPE_XXX) */
    unsigned int type;

    /* Reference name */
    const char* name;

    /* Length of reference */
    int length;

    /* Is value reference (which can be transformed)? */
    int is_value;

    /* PMD number special type (PMD_NUMBER_SPECIAL_TYPE_XXX) */
    unsigned short special_type;

    /* Resource types, allowing reference use */
    unsigned int res_type;

    /* Seq types, allowing reference use */
    unsigned int seq_type;

} autogen_ref_conf;

#define AUTOGEN_REF_LENGTH_8_16    -2
#define AUTOGEN_REF_LENGTH_8_16_32 -3

autogen_ref_conf* s_ref_conf = NULL;

#define AUTOGEN_REFERENCE_RESERVED_MAX 5

const char* s_ref_reserved_names[AUTOGEN_REFERENCE_RESERVED_MAX] = 
{
    "REF_AS_MANY_AS_POSSIBLE",
    "REF_AS_LONG_AS_POSSIBLE",
    "REF_OPTIONAL",
    "REF_LENGTH_UNKNOWN",
    "REF_LENGTH_DETERMINED_BY_ZERO"
};

autogen_ref s_ref_system;


/* list containing unused references for the resource */
LOCAL autogen_ref* s_ref_unused_references = NULL;

/* list containing unresolved references for the resource */
LOCAL autogen_ref* s_ref_unresolved_references = NULL;


LOCAL autogen_ref*  reference_add(autogen_ref_handle* ref_handle, const char* name, autogen_ref_type type, autogen_item* item, autogen_feature *featureflag);

LOCAL void          reference_check_for_redefinition(autogen_ref_handle* ref_handle, const autogen_item* item, const char* name, autogen_feature *featureflag);
LOCAL void          reference_check_special_type_size(const autogen_item* item, int res_size, int length);

LOCAL void          reference_clone_items(autogen_obj_list* obj_list, autogen_ref_handle* src_ref_handle);

LOCAL void          reference_conf_add(unsigned int type, const char* name, int length, int is_value, unsigned short special_type, unsigned int obj_type, unsigned int obj_sub_type);

LOCAL int           reference_find_unresolved_in_seq(autogen_ref* ref, autogen_seq* seq);

LOCAL const autogen_ref_conf*   
                    reference_get_configuration(const char* name);
LOCAL autogen_obj*  reference_get_handle_obj_from_obj(autogen_obj* obj);
LOCAL unsigned int  reference_get_special_type(const char* name);

LOCAL int           reference_is_counter(const autogen_ref* ref);

LOCAL void          reference_resolve(autogen_ref* ref);

LOCAL void          reference_update_transformations(autogen_ref_handle* ref_handle, autogen_ref* ref);

LOCAL void          reference_use(autogen_ref* ref);

/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* Adds reference to ref_handle. 

   If reference is unresolved (type is xxxUnresolved), reference is added to list of unresolved
   Reference is added to list of unused references, if it is not a predefined reference.
*/
LOCAL autogen_ref* reference_add(autogen_ref_handle* ref_handle, const char* name, autogen_ref_type type, autogen_item* item, autogen_feature *featureflag)
{
    autogen_ref* ref = NULL;

    /* Ensure that reference is not already defined */
    reference_check_for_redefinition(ref_handle, item, name, featureflag); 

    /* Ensure that reference name is not reserved */
    if (reference_is_name_reserved(name))
    {
        int line = item ? item->base.file_line : 0;

        util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
            "Reference name '%s' is reserved and can't be used in this context", name);
        return NULL;
    }
    /* Else create and add the reference to the handle */
    else
    {
        ref = (autogen_ref*)pmd_heap_alloc(sizeof(autogen_ref));

        ref->name = name;
        ref->original_name = name;

		ref->item = item;

        ref->type = type;

        ref->algorithm = PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH;
        ref->value     = 0;
        ref->conf      = reference_get_configuration(name);

        ref->feature_flags = featureflag;

        ref->next = ref_handle->ref_list;
        ref_handle->ref_list = ref;

        if (ref->type == referenceTypePredefined)
        {
            ref->is_used = TRUE;
        }
		else if (ref->type != referenceTypeCounterUnresolved && 
                 ref->type != referenceTypeTransformationUnresolved && 
                 ref->type != referenceTypeTagUnresolved)
        {
            /* Add to front of list of unused references */
            if (s_ref_unused_references)
            {
                s_ref_unused_references->prev_unused = ref;
                ref->next_unused = s_ref_unused_references;
            }
            s_ref_unused_references = ref;
        }
        /* Add reference to list of unresolved references */
        else if (ref->type == referenceTypeCounterUnresolved ||
                 ref->type == referenceTypeTransformationUnresolved ||
                 ref->type == referenceTypeTagUnresolved)
        {
            ref->item            = NULL;
    		ref->unresolved_item = item;

		    /* Add to front of list of unresolved references */
		    if (s_ref_unresolved_references)
		    {
			    s_ref_unresolved_references->prev_unresolved = ref;
		    }
		    ref->next_unresolved = s_ref_unresolved_references;
		    s_ref_unresolved_references = ref;
        }
    }

    return ref;
}

/* Checks, if reference 'name' is already defined */
LOCAL void reference_check_for_redefinition(autogen_ref_handle* ref_handle, const autogen_item* item, const char* name, autogen_feature *featureflag)
{
    int line = item ? item->base.file_line : 0;

    autogen_ref* ref_deep = reference_find_from_handle(ref_handle, name, featureflag, TRUE);
    autogen_ref* ref_no_deep = reference_find_from_handle(ref_handle, name, featureflag, FALSE);
    /* Error, if reference is redefined in same scope */
    if (ref_no_deep)
    {
        if (ref_no_deep->item)
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Reference '%s' is re-defined. Is originally defined in line %d", name, ref_no_deep->item->base.file_line);
        }
        else
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Reference '%s' is re-defined", name);
        }
    }
    /* Warning, if reference is redefined in other scope */
    else if (ref_deep)
    {
        if (ref_deep->item)
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Reference '%s' is re-defined. Is originally defined in line %d", name, ref_deep->item->base.file_line);
        }
        else
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Reference '%s' is re-defined", name);
        }
    }
}

/* Checks if special type reference has correct length/size */
LOCAL void reference_check_special_type_size(const autogen_item* item, int res_size, int length)
{
    if (res_size == AUTOGEN_VALUE_VARIES)
    {
        /* Must be even sizes */
        if (length != 8 && length != 16 && length != 32)
        {
            util_error_line(NULL, item->base.file_line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument 'length' is %d, which is out of range. Value must be 8, 16 or 32 in this context", length);
        }
    }
    /* Must match */
    else if (length != res_size)
    {
        util_error_line(NULL, item->base.file_line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument 'length' is %d, which is out of range. Value must be 8, 16 or 32 in this context", length);
    }
}

void reference_clone_items(autogen_obj_list* obj_list, autogen_ref_handle* src_ref_handle)
{
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        reference_copy_item(item, src_ref_handle);

        reference_clone_items(&item->base.child_list, src_ref_handle);

        item = (autogen_item*)item->base.next;
    }   
}

/* Adds configuration entry for predefined reference */
LOCAL void reference_conf_add(unsigned int type, const char* name, int length, int is_value, unsigned short special_type, unsigned int res_type, unsigned int seq_type)
{
    autogen_ref_conf* ref_conf_it = s_ref_conf;
    autogen_ref_conf* ref_conf_it_last = NULL;

    autogen_ref_conf* ref_conf = pmd_heap_alloc(sizeof(autogen_ref_conf));

    ref_conf->type = type;
    ref_conf->name = name;
    ref_conf->length = length;
    ref_conf->is_value = is_value;
    ref_conf->special_type = special_type;
    ref_conf->res_type = res_type;
    ref_conf->seq_type = seq_type;

    /* Insert configuration in list */
    while (ref_conf_it && strcmp(ref_conf_it->name, name) < 0)
    {
        ref_conf_it_last = ref_conf_it;
        ref_conf_it      = ref_conf_it->next;
    }

    if (ref_conf_it_last)
    {
        ref_conf->next = ref_conf_it_last->next;
        ref_conf_it_last->next = ref_conf;
    }
    else
    {
        s_ref_conf = ref_conf;
    }
}

/* Finds all uses of the unresolved reference 'ref' starting in seq 'seq' */
LOCAL int reference_find_unresolved_in_seq(autogen_ref* ref, autogen_seq* seq)
{
	int result = OK;
	autogen_obj* rel_obj = NULL;
	autogen_it rel_obj_it = INIT_ITERATOR;

    if (!seq || seq->base.type == AUTOGEN_OBJ_MSG)
    {
        result = FAIL;
    }

    if (result)
    {
        rel_obj = autogen_obj_find_in_list(&rel_obj_it, &seq->base.related_obj);
	}

    /* No relations? Then there is no reference defined */
    if (!rel_obj)
    {
        if (seq->base.type == AUTOGEN_OBJ_MSG || seq->base.type == AUTOGEN_OBJ_TRACE)
        {
            result = FAIL;
        }
    }
	while (rel_obj && result)
	{
		autogen_ref_handle* ref_handle = NULL;
		autogen_seq* rel_seq = NULL;

		if (rel_obj->subtype == AUTOGEN_OBJ_ITEM)
		{
			rel_seq    = util_get_parent_seq((autogen_item*)rel_obj->ptr);
			ref_handle = reference_get_handle_from_obj(rel_obj->ptr);
		}
		else if (rel_obj->subtype & AUTOGEN_OBJ_SEQ_ANY)
		{
			rel_seq    = (autogen_seq*)rel_obj->ptr;
			ref_handle = &rel_seq->ref_handle;
		}

		if (ref_handle)
		{
			autogen_ref* ref_it = reference_find_from_handle(ref_handle, ref->name, NULL, TRUE);
			if (ref_it)
			{
                int line = ref->unresolved_item ? ref->unresolved_item->base.file_line : 0;

				reference_use(ref_it);

                ref_it->is_used_externally = TRUE;

				ref->item = ref_it->item;

				/* Incorrect use of tag */
				if (ref->type == referenceTypeTagUnresolved && ref_it->type != referenceTypeTag)
                {
                    util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                        "Reference '%s' is not a tag (based on REFERENCE_CONST)", ref->name);
                }
				/* Incorrect use of counter */
				else if (ref->type == referenceTypeCounterUnresolved && ref_it->type != referenceTypeCounter && ref_it->type != referenceTypeTransformation)
                {
                    util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                        "Reference '%s' is not a value reference", ref->name);
                }
                /* Check choice against reference */
                else if (ref->type == referenceTypeTagUnresolved && ref_it->type == referenceTypeTag)
                {
                    reference_check_choice((autogen_item_value*)ref_it->item, (autogen_item_choice*)ref->unresolved_item);
                }

				/* If external counter, update to transformation, if such is found */
				if (ref_it->type == referenceTypeTransformation && ref->type == referenceTypeCounterUnresolved)
				{
					ref->type = referenceTypeTransformationUnresolved;

					ref->original_name = ref_it->original_name;
					ref->algorithm     = ref_it->algorithm;
					ref->value         = ref_it->value;
				}

			}
			/* Reference not found. Do another iteration */
			else
			{
				result = reference_find_unresolved_in_seq(ref, rel_seq);
			}
		}
		/* Reference not found. Do another iteration */
		else
		{
			result = reference_find_unresolved_in_seq(ref, rel_seq);
		}

		rel_obj = autogen_obj_find_next_in_list(&rel_obj_it);
	}

	return result;
}

/* Returns pointer to configuration for predefined reference named 'name' */
LOCAL const autogen_ref_conf* reference_get_configuration(const char* name)
{
    const autogen_ref_conf* ref_conf = s_ref_conf;

    while (ref_conf && strcmp(ref_conf->name, name) < 0)
    {
        ref_conf = ref_conf->next;
    }

    return (ref_conf && !strcmp(ref_conf->name, name)) ? ref_conf : NULL;
}

/* Returns pointer to reference handle object (case / seq) from given object 'obj' */
LOCAL autogen_obj* reference_get_handle_obj_from_obj(autogen_obj* obj)
{
    while (obj->type == AUTOGEN_OBJ_ITEM && obj->subtype != AUTOGEN_ITEM_CASE)
    {
        obj = obj->parent;
    }

    return obj;
}

/* Returns special type ID (PMD_NUMBER_SPECIAL_TYPE_XXXX) for predefined reference name 'name' */
LOCAL unsigned int reference_get_special_type(const char* name)
{
    unsigned int special_type = PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE;
    const autogen_ref_conf* ref_conf = reference_get_configuration(name);
    if (ref_conf)
    {
        special_type = ref_conf->special_type;
    }
    else
    {
        int n;
        for (n = 0; n < AUTOGEN_OBJ_TRACEGRP_MAX && special_type == PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE; n++)
        {
            const autogen_trcgrp_conf* trc_conf = &g_trcgrp_conf[n];

            if (trc_conf->trace_entity_id_refname && !strcmp(trc_conf->trace_entity_id_refname, name))
            {
                special_type = trc_conf->entity_special_type;
            }
            else if (trc_conf->trace_group_id_refname && !strcmp(trc_conf->trace_group_id_refname, name))
            {
                special_type = trc_conf->group_special_type;
            }
            else if (trc_conf->trace_id_refname && !strcmp(trc_conf->trace_id_refname, name))
            {
                special_type = trc_conf->id_special_type;
            }
        }
    }

    return special_type;
}

/* Returns TRUE if given reference is a counter (from which transformations can be made) */
LOCAL int reference_is_counter(const autogen_ref* ref)
{
    int is_counter = TRUE;

    if (ref->type == referenceTypeTag ||
        ref->type == referenceTypeTagUnresolved ||
        ref->type == referenceTypePredefined && ref->conf->is_value == FALSE)
    {
        is_counter = FALSE;
    }

    return is_counter;
}

/* Returns TRUE if the reference is a given special type */
LOCAL int reference_is_special_type(const autogen_ref* ref, unsigned int special_type)
{
    return (ref->conf && ref->conf->special_type == special_type);
}

/* Removes reference from unresolved list */
LOCAL void reference_resolve(autogen_ref* ref)
{
    /* Change type */
    if (ref->type == referenceTypeTransformationUnresolved)
    {
        ref->type = referenceTypeTransformation;
    }
    else if (ref->type == referenceTypeTagUnresolved)
    {
        ref->type = referenceTypeTag;
    }
    else if (ref->type == referenceTypeCounterUnresolved)
    {
        ref->type = referenceTypeCounter;
    }

    /* Remove from unresolved list */
    if (ref->prev_unresolved)
    {
        ref->prev_unresolved->next_unresolved = ref->next_unresolved;
    }
    else
    {
        s_ref_unresolved_references = ref->next_unresolved;
    }
    if (ref->next_unresolved)
    {
        ref->next_unresolved->prev_unresolved = ref->prev_unresolved;
    }
    ref->prev_unresolved = NULL;
    ref->next_unresolved = NULL;

    ref->unresolved_item = NULL;
}

/* Update all transformations, based on the reference ref */
LOCAL void reference_update_transformations(autogen_ref_handle* ref_handle, autogen_ref* ref)
{
    autogen_ref* ref_it = ref_handle->ref_list;
    while (ref_it)
    {
        /* Found transformation? */
        if (ref_it->type == referenceTypeTransformationUnresolved && !strcmp(ref_it->original_name, ref->name))
        {
            ref_it->item = ref->item;

            /* Now, the original reference is used */
            reference_use(ref);

            /* Remove from unresolved list */
            reference_resolve(ref_it);
        }

        ref_it = ref_it->next;
    }
}

/* Use reference 'ref' (remove it from list of unused references) */
LOCAL void reference_use(autogen_ref* ref)
{
    /* Remove from unused list */
    if (ref->prev_unused)
    {
        ref->prev_unused->next_unused = ref->next_unused ;
    }
    else
    {
        s_ref_unused_references = ref->next_unused;
    }

    if (ref->next_unused)
    {
        ref->next_unused->prev_unused = ref->prev_unused;
    }

    ref->prev_unused = NULL;
    ref->next_unused = NULL;

    ref->is_used = TRUE;
}


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* Add a new counter reference to the reference handle 'ref_handle' */
unsigned int reference_add_counter(autogen_ref_handle* ref_handle, autogen_item* item, const char* name, int length, autogen_feature *featureflag)
{
    unsigned int special_type = PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE;
    autogen_ref* ref = NULL;

    /* Predefined references */
    if (reference_is_name_predefined(name))
    {
        int line = item ? item->base.file_line : 0;
        const autogen_ref_conf* ref_conf = reference_get_configuration(name);

        special_type = ref_conf->special_type;

		ref = reference_add(ref_handle, name, referenceTypePredefined, item, featureflag);

        /* Is sequence object correct */
		if (!(util_get_base_parent(&item->base)->type & ref_conf->seq_type))
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference '%s' is not valid in this context", name);
        }
        /* Is resource object correct */
        if (!(item->base.res->base.subtype & ref_conf->res_type))
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference '%s' is not valid in this resource", name);
        }

        /* Is supported at all? */
        if (ref_conf->length == AUTOGEN_NOT_SUPPORTED)
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference '%s' is not valid in this context", name);
        }
        /* Is length 8 / 16 bit */
        else if (ref_conf->length == AUTOGEN_REF_LENGTH_8_16 && length != 8 && length != 16)
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Size of reference '%s' is %d, which is not valid in this context. Size should be 8 or 16", name, length);
        }
        /* Is length 8 / 16 / 32 bit */
        else if (ref_conf->length == AUTOGEN_REF_LENGTH_8_16_32 && length != 8 && length != 16 && length != 32)
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Size of reference '%s' is %d, which is not valid in this context. Size should be 8, 16 or 32", name, length);
        }
        /* Else, is length equal to defined length in configuration */
        else if (ref_conf->length > 0 && ref_conf->length != length)
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Size of reference '%s' is %d, which is not valid in this context. Size should be %d", name, length, ref_conf->length);
        }

        /* Check special types against lengths defined in resource */
        if (special_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID)
        {
            reference_check_special_type_size(item, item->base.res->msg_id_size, length);
        }
        else if (special_type == PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID)
        {
            reference_check_special_type_size(item, item->base.res->submsg_id_size, length);
        }
        else if (special_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH)
        {
            reference_check_special_type_size(item, item->base.res->msg_length_size, length);
        }

        /* Update types in */
        ref_handle->included_types |= ref_conf->type;

    }
    /* Simple counter */
    else
    {
		ref = reference_add(ref_handle, name, referenceTypeCounter, item, featureflag);
    }

    return special_type;
}

/* Add a new tag reference to the reference handle 'ref_handle' */
void reference_add_tag(autogen_ref_handle* ref_handle, autogen_item* item, const char* name, autogen_feature *featureflag)
{
    /* Predefined references */
    if (reference_is_name_predefined(name))
    {
        int line = item ? item->base.file_line : 0;

        util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Reference name '%s' is reserved for special use, and can't be used in this context", name);
    }
    else
    {
    	reference_add(ref_handle, name, referenceTypeTag, item, featureflag);
    }
}

/* Add a new transformation reference to the reference handle 'ref_handle' */
void reference_add_transformation(autogen_ref_handle* ref_handle, const char* new_name, const char* org_name, unsigned int algorithm, int value, int line, autogen_feature *featureflag)
{
    autogen_ref* ref = NULL;
    autogen_ref* org_ref = NULL;
    unsigned short pmd_alg_map[ALG_MAX] = 
    {
        /* ALG_ADD */           PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH,
        /* ALG_SUB */           PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH,
        /* ALG_MUL */           PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N,
        /* ALG_DIV */           PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH,
        /* ALG_DIV_ROUND_UP */  PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH_ROUNDUP,
        /* ALG_N_SUB */         PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MINUS_N
    };

    /* Check that reference names is legal */
    if (reference_is_name_reserved(org_name))
    {
        util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
            "Reference name '%s' is reserved and can't be used in transformations", org_name);
        return;
    }
    else if (reference_is_name_predefined(org_name))
    {
        const autogen_ref_conf* ref_conf = reference_get_configuration(org_name);
        if (!ref_conf->is_value)
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Reference name '%s' is reserved and can't be used in transformations", org_name);
            return;
        }
    }
    else if (reference_is_name_predefined(new_name))
    {
        util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
            "Reference name '%s' is reserved and can't be defined as a transformation", new_name);
        return;
    }

    /* Find original reference in handle */
    org_ref = reference_find_from_handle(ref_handle, org_name, featureflag, TRUE);
    if (!org_ref)
    {
        autogen_obj* handle_obj = ref_handle->parent;

        if (!strcmp(org_name, "TRACE_DATA_LENGTH"))
        {
            /* Must be used in a trace */
            if (!(handle_obj->res->base.subtype & RESOURCE_TRC_ANY) && strcmp(handle_obj->res->base.name, "PN_TRACE"))
            {
                util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Reference '%s' is reserved, and can't be used in this context", org_name);
                return;
            }

		    /* Add reference to list of references */
		    ref = reference_add(ref_handle, org_name, referenceTypeTraceDataLength, NULL, featureflag);
            ref->is_external = TRUE;

            reference_use(ref);
        }
        else if (handle_obj->type == AUTOGEN_OBJ_SEQ && (handle_obj->flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
        {
            /* This is OK */
        }
        else
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference transformation '%s' is based on '%s', which is not defined in the scope of %s '%s'", 
                new_name, org_name, util_get_obj_type_name(handle_obj), util_get_obj_name(handle_obj));
            return;
        }
    }

    /* Create new reference */
    ref = reference_add(ref_handle, new_name, referenceTypeTransformation, NULL, featureflag);

    ref->original_name = org_name;

    ref->algorithm = pmd_alg_map[algorithm - ALG_MIN];
    ref->value     = value;

    if (org_ref)
    {
        /* Transformations must not be made to tags */
        if (!reference_is_counter(org_ref))
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
                "Reference transformation '%s' is based on '%s', which is not a value reference", new_name, org_name);
        }
        /* The transformation is too complex, and is not supported */
        else if (org_ref->type == referenceTypeTransformation)
        {
            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference transformation '%s' is too complex", new_name);
            return;
        }

        ref->item = org_ref->item;

        reference_use(org_ref);
    }
}

/* Checks that the choice 'item' uses the reference correctly */
void reference_check_choice(autogen_item_value* ref_item, autogen_item_choice* choice)
{
    autogen_it tbl_it = INIT_ITERATOR;
    autogen_obj* tbl;

    tbl_it.typemask    = AUTOGEN_OBJ_TBL;
    tbl_it.subtypemask = AUTOGEN_TBL_CONST_ANY;
    tbl_it.obj.name    = ref_item->pres.tblname;
    tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
    tbl_it.ver         = &choice->base.base.ver;
    if (choice->base.base.feature_flags)
    {
        tbl_it.featureflagcrit   = AUTOGEN_OBJ_FEATUREFLAG_CHECK;
        tbl_it.obj.feature_flags = choice->base.base.feature_flags;
    }

    tbl = autogen_obj_find_in_list(&tbl_it, &ref_item->pres.tblres->tbl_list);
    if (!tbl && !(choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_VALUE))
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "The constant/bitmask table '%s' doesn't exist for all needed versions", ref_item->pres.tblname);
    }

    /* update choice reference flag */
    if (tbl->subtype == AUTOGEN_TBL_CONST || tbl->subtype == AUTOGEN_TBL_DERCONST)
    {
        choice->base.base.flag |= AUTOGEN_CHOICE_REFERENCE_CONSTANT;
    }
    else if (tbl->subtype == AUTOGEN_TBL_BIT || tbl->subtype == AUTOGEN_TBL_DERBIT)
    {
        choice->base.base.flag |= AUTOGEN_CHOICE_REFERENCE_BITMASK;
    }

    if (!(choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_VALUE))
    {
        autogen_item_case* case_item = (autogen_item_case*)autogen_obj_get_first_in_list(&choice->base.base.child_list);
        while (case_item)
        {
            autogen_obj* entry;
            autogen_it entry_it = INIT_ITERATOR;

            /* check that a table constant with the same name as the case exist */
            entry_it.typemask = AUTOGEN_OBJ_TBLENTRY;
            entry_it.obj.name = case_item->base.base.name;
            entry_it.vercrit  = AUTOGEN_OBJ_VERSION_INCLUDES;
            entry_it.ver      = &case_item->base.base.ver;

            entry = autogen_obj_find_in_list(&entry_it, &tbl->child_list);
            if (!entry)
            {
                autogen_obj_find_in_list(&entry_it, &tbl->child_list);

                util_error_line(NULL, case_item->base.base.file_line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Case '%s' is not defined in table '%s'", case_item->base.base.name, tbl->name);
            }

            if (tbl->subtype == AUTOGEN_TBL_BIT || tbl->subtype == AUTOGEN_TBL_DERBIT)
            {
                case_item->base.bit_pattern = ((autogen_bittbl_entry*)entry)->bit_pattern;
            }

            case_item = (autogen_item_case*)case_item->base.base.next;
        }
    }
}

/* Checks all unresolved reference. If they remain unresolved, an error is thrown */
void reference_check_unresolved()
{
    while (s_ref_unresolved_references)
    {
        autogen_seq* seq = util_get_parent_seq(s_ref_unresolved_references->unresolved_item);

        if (s_ref_unresolved_references->type == referenceTypeTransformationUnresolved)
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Reference transformation '%s' is unresolved", s_ref_unresolved_references->name);
        }
        else if (!reference_find_unresolved_in_seq(s_ref_unresolved_references, seq))
		{
            int line = s_ref_unresolved_references->unresolved_item ? s_ref_unresolved_references->unresolved_item->base.file_line : 0;

            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Reference '%s' is not defined", s_ref_unresolved_references->name);
		}
		else
		{
			s_ref_unresolved_references->is_external = TRUE;
            seq->ref_handle.uses_external_references = TRUE;

			if (s_ref_unresolved_references->type == referenceTypeCounterUnresolved)
			{
				s_ref_unresolved_references->type = referenceTypeCounter;
			}
			else if (s_ref_unresolved_references->type == referenceTypeTagUnresolved)
			{
				s_ref_unresolved_references->type = referenceTypeTag;
			}
            else if (s_ref_unresolved_references->type == referenceTypeTransformationUnresolved)
			{
                s_ref_unresolved_references->type = referenceTypeTransformation;
			}
		}
		
        s_ref_unresolved_references->prev_unresolved = NULL;
        s_ref_unresolved_references = s_ref_unresolved_references->next_unresolved;
    }
}

/* Checks all unused reference. Any unused reference is reported as a warning */
void reference_check_unused()
{
    while (s_ref_unused_references)
    {
        int line = s_ref_unused_references->item ? s_ref_unused_references->item->base.file_line : 0;

        util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
            "Reference '%s' is not used", s_ref_unused_references->name);

        s_ref_unused_references->prev_unused = NULL;
        s_ref_unused_references = s_ref_unused_references->next_unused;
    }
}

void reference_clone_seq(autogen_seq* seq, autogen_ref_handle* src_ref_handle)
{
    autogen_ref_handle* ref_handle = &seq->ref_handle;
    autogen_ref* ref_it = src_ref_handle->ref_list;

    /* Reset handle */
    ref_handle->included_types = 0;
    ref_handle->ref_list = NULL;

    /* Clone transformations */
    while (ref_it)
    {
        if (ref_it->type == referenceTypeTransformation)
        {
            autogen_ref* new_ref = reference_add(ref_handle, ref_it->name, ref_it->type, NULL, NULL);

            new_ref->original_name = ref_it->original_name;
            new_ref->value         = ref_it->value;
            new_ref->algorithm     = ref_it->algorithm;
            new_ref->conf          = ref_it->conf;
        }

        ref_it = ref_it->next;
    }

    reference_clone_items(&seq->base.child_list, src_ref_handle);
}

/* 'item' is a clone of another item. Check that references to/from the item are updated correctly */
void reference_copy_item(autogen_item* item, autogen_ref_handle* src_ref_handle)
{
    autogen_ref_handle* ref_handle = reference_get_handle_from_obj(&item->base);

    /* Item uses a reference. Check that it exists */
    if (item->agg_type == AGG_TYPE_DYNAMIC_REF)
    {
        reference_use_counter(item, item->base.feature_flags);
    }
    else if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
    {
        reference_use_tag(item, item->base.feature_flags);
    }

    /* Item is a reference. Update item pointer in handle */
    if (item->base.subtype == AUTOGEN_ITEM_REF)
    {
        autogen_ref* ref = NULL;

        autogen_ref* src_ref = reference_find_from_handle(src_ref_handle, item->base.name, item->base.feature_flags, TRUE);

        /* Is the reference redefined? */
        reference_check_for_redefinition(ref_handle, item, src_ref->name, item->base.feature_flags);

        /* Copy reference to new handle */
        ref = reference_add(ref_handle, src_ref->name, src_ref->type, item, item->base.feature_flags);

        /* Update transformations, based on the reference */
        reference_update_transformations(ref_handle, ref);
    }
}

/* Copy all transformations from 'src_ref_handle' to 'ref_handle' */
void reference_copy_transformations(autogen_ref_handle* ref_handle, autogen_ref_handle* src_ref_handle)
{
    autogen_ref* ref_it = src_ref_handle->ref_list;
    while (ref_it)
    {
        /* Found transformation? */
        if (ref_it->type == referenceTypeTransformation || ref_it->type == referenceTypeTransformationUnresolved)
        {
            autogen_ref* new_ref = NULL;

            /* Look up the original name in the new handle */
            autogen_ref* org_ref = reference_find_from_handle(ref_handle, ref_it->original_name, NULL, TRUE);

            /* If it exists, create a proper transformation */
            if (org_ref)
            {
                /* Check that original reference type is correct */
                if (!reference_is_counter(org_ref))
                {
                    int line = org_ref->item ? org_ref->item->base.file_line : 0;

                    util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                        "Reference '%s' is not a value reference", org_ref->name);
                }

                new_ref = reference_add(ref_handle, ref_it->name, referenceTypeTransformation, org_ref->item, NULL);

                reference_use(org_ref);
            }
            /* Else create an unresolved transformation */
            else
            {
                new_ref = reference_add(ref_handle, ref_it->name, referenceTypeTransformationUnresolved, ref_it->unresolved_item, NULL);
            }

            /* Copy common attributes */
            new_ref->original_name = ref_it->original_name;
            new_ref->algorithm     = ref_it->algorithm;
            new_ref->value         = ref_it->value;
        }

        ref_it = ref_it->next;
    }
}

/* Finds the reference, which is referred from 'item' */
autogen_ref* reference_find(autogen_item* item)
{
    autogen_ref* ref = NULL;

    if (item->refname && !strcmp(item->refname, "TRACE_DATA_LENGTH"))
    {
        ref = &s_ref_system;
    }
    else
    {
        autogen_ref_handle* ref_handle = reference_get_handle_from_obj(&item->base);

        ref = reference_find_from_handle(ref_handle, item->refname, item->base.feature_flags, TRUE);
    }

    return ref;
}

/* Finds the reference 'name' from handle 'ref_handle' */
autogen_ref* reference_find_from_handle(autogen_ref_handle* ref_handle, const char* name, autogen_feature *featureflag, int deep)
{
    autogen_ref* ref = ref_handle->ref_list;

    if (name == NULL)
    {
        return NULL;
    }

    while (ref && (strcmp(name, ref->name) || autogen_obj_featureflag_comp(ref->feature_flags, featureflag)))
    {
        ref = ref->next;
    }

    if (deep && !ref && ref_handle->base_handle)
    {
        ref = reference_find_from_handle(ref_handle->base_handle, name, featureflag, deep);
    }

    return ref;
}

/* Returns a pointer to the reference handle, a given object uses */
autogen_ref_handle* reference_get_handle_from_obj(autogen_obj* obj)
{
    obj = reference_get_handle_obj_from_obj(obj);

    if (obj->type == AUTOGEN_OBJ_ITEM)
    {
        return &((autogen_item_case*)obj)->ref_handle;
    }
    else
    {
        return &((autogen_seq*)obj)->ref_handle;
    }
}

/* Return the value limits, which the given item has */
#if (PMD_FILE_FORMAT >= 600)
void reference_get_limits(autogen_item* item, signed long long* min_val, signed long long* max_val, char* min_val_str, char* max_val_str)
#else
void reference_get_limits(autogen_item* item, int* min_val, int* max_val, char* min_val_str, char* max_val_str)
#endif
{
    int length = 0;

#if (PMD_FILE_FORMAT >= 600)
    unsigned long long min_val_us = 0;
    unsigned long long max_val_us = 0;
#else
    unsigned int min_val_us = 0;
    unsigned int max_val_us = 0;
#endif

    autogen_ref* ref = reference_find(item);

    if (item)
    {
        length = item->length;
    }

    min_val_str[0] = 0;
    max_val_str[0] = 0;

    /* Basic item limits */
    if (ref)
    {
        util_get_item_limits(ref->item, &min_val_us, &max_val_us, min_val_str, max_val_str);
    }

#if (PMD_FILE_FORMAT >= 600)
    *min_val = (signed long long)min_val_us;
    *max_val = (signed long long)max_val_us;
#else
    *min_val = (int)min_val_us;
    *max_val = (int)max_val_us;
#endif

    /* SE:TBD handle 64-bit alignment */

    /* If item is a sub block length, the length must be divisible by 4 */
    if (ref && reference_is_special_type(ref, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH))
    {
        *max_val -= (*max_val % 4);
    }

    /* Apply transformation on top */
    if (ref && ref->type == referenceTypeTransformation)
    {
        if (ref->algorithm == PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N)
        {
            *min_val *= ref->value;
            *max_val *= ref->value;

            sprintf(min_val_str + strlen(min_val_str), "*%d", ref->value);
            sprintf(max_val_str + strlen(max_val_str), "*%d", ref->value);
        }
        else if (ref->algorithm == PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH)
        {
            char tmp_val_str[2*AUTOGEN_MAX_NAME_LENGTH];

            char c = (char)((ref->value > 0) ? '+' : '-');

            *min_val += ref->value;
            *max_val += ref->value;

            strcpy(tmp_val_str, min_val_str);
            sprintf(min_val_str, "(%s %c %d)", tmp_val_str, c, ref->value);

            strcpy(tmp_val_str, max_val_str);
            sprintf(max_val_str, "(%s %c %d)", tmp_val_str, c, ref->value);
        }
        else if (ref->algorithm == PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH)
        {
            *min_val /= ref->value;
            *max_val /= ref->value;

            sprintf(min_val_str + strlen(min_val_str), "/%d", ref->value);
            sprintf(max_val_str + strlen(max_val_str), "/%d", ref->value);
        }
        else if (ref->algorithm == PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH_ROUNDUP)
        {
            char temp_str[2*AUTOGEN_MAX_NAME_LENGTH];

            *min_val = (*min_val + ref->value - 1)/ref->value;
            *max_val = (*max_val + ref->value - 1)/ref->value;

            strcpy(temp_str, min_val_str);
            sprintf(min_val_str, "(%s + %d)/%d", temp_str, ref->value, ref->value);

            strcpy(temp_str, max_val_str);
            sprintf(max_val_str, "(%s + %d)/%d", temp_str, ref->value, ref->value);
        }
    }

    /* Swap min / max values if necessary */
#if (PMD_FILE_FORMAT >= 600)
    if ((length < 0 && *min_val > *max_val) ||
        (length > 0 && (unsigned long long) *min_val > (unsigned long long) *max_val))
#else
    if ((length < 0 && *min_val > *max_val) ||
        (length > 0 && (unsigned int) *min_val > (unsigned int) *max_val))
#endif
    {
        char tmp_val_str[2*AUTOGEN_MAX_NAME_LENGTH];
#if (PMD_FILE_FORMAT >= 600)
        signed long long temp = *min_val;
#else
        int temp = *min_val;
#endif

        *min_val = *max_val;
        *max_val = temp;

        strcpy(tmp_val_str, min_val_str);
        strcpy(min_val_str, max_val_str);
        strcpy(max_val_str, tmp_val_str);
    }
}

/* Returns the special item reference given the special type */
autogen_item* reference_get_special_item(const autogen_ref_handle* ref_handle, unsigned short special_type)
{
    autogen_item* item = NULL;
    const autogen_ref* ref = ref_handle->ref_list;

    while (ref && !item)
    {
        if (ref->conf && ref->conf->special_type == special_type)
        {
            item = ref->item;

            /* Check if there is feature flags around special items */
            if (item && item->base.feature_flags)
            {
                int line = item ? item->base.file_line : 0;
                util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Predefined reference '%s' is not allowed to be surrounded by feature flags.", 
                    (item->base.name == NULL ? "<unknown>" : item->base.name));
            }
        }

        ref = ref->next;
    }

    return item;
}

/* Initializes the reference library */
void reference_init()
{
    int n;
 /*                    Type                                      Name                Length                      IS value  PMD special type                            Resource types              Sequence types */
 /* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_MSG_ID,            "MSG_ID",           AUTOGEN_REF_LENGTH_8_16,    FALSE,    PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID,         ~RESOURCE_SHARED,           AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE | AUTOGEN_OBJ_SEQ);
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_MSG_LENGTH,        "MSG_LENGTH",       AUTOGEN_REF_LENGTH_8_16,    TRUE,     PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH,     RESOURCE_PROTOCOL_ANY,      AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_SEQ);
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_SUB_MSG_ID,        "SUB_MSG_ID",       AUTOGEN_REF_LENGTH_8_16,    FALSE,    PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID,     ~RESOURCE_SHARED,           AUTOGEN_OBJ_MSG);
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_SB_ID,             "SB_ID",            AUTOGEN_REF_LENGTH_8_16,    FALSE,    PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID,       RESOURCE_ANY,               AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SB_TEMPLATE | AUTOGEN_OBJ_SEQ);
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_SB_LENGTH,         "SB_LENGTH",        AUTOGEN_REF_LENGTH_8_16_32, TRUE,     PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH,   RESOURCE_ANY,               AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SB_TEMPLATE | AUTOGEN_OBJ_SEQ);
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_RESOURCE_ID,       "RESOURCE_ID",      16,                         FALSE,    PMD_NUMBER_SPECIAL_TYPE_RESOURCE_ID,        RESOURCE_ISI_PREFIX_ANY,    AUTOGEN_OBJ_MSG);
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_PRIVATE_ID,        "PRIVATE_ID",       16,                         FALSE,    PMD_NUMBER_SPECIAL_TYPE_PRIVATE_ID,         RESOURCE_ISI_PRIVATE,       AUTOGEN_OBJ_MSG);
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_XTI_MASTER_ID,     "XTI_MASTER_ID",    8,                          FALSE,    PMD_NUMBER_SPECIAL_TYPE_XTI_MASTER_ID,      RESOURCE_ANY,               AUTOGEN_OBJ_MSG);
    reference_conf_add(AUTOGEN_REFERENCE_TYPE_TRACE_DATA_LENGTH, "TRACE_DATA_LENGTH",16,                         TRUE,     PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH,  RESOURCE_ANY,               AUTOGEN_OBJ_ANY);

    for (n = 0; n < AUTOGEN_OBJ_TRACEGRP_MAX; n++)
    {
        const autogen_trcgrp_conf* trc_conf = &g_trcgrp_conf[n];

        if (trc_conf->trace_entity_id_refname && trc_conf->trace_entity_id_refname[0])
        {
            reference_conf_add(AUTOGEN_REFERENCE_TYPE_TRACE_ENTITY_ID, trc_conf->trace_entity_id_refname, 
                trc_conf->entity_size, FALSE, trc_conf->entity_special_type, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY);
        }
        if (trc_conf->trace_group_id_refname && trc_conf->trace_group_id_refname[0])
        {
            reference_conf_add(AUTOGEN_REFERENCE_TYPE_TRACE_GROUP_ID, trc_conf->trace_group_id_refname, 
                trc_conf->group_size, FALSE, trc_conf->group_special_type, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY);
        }
        if (trc_conf->trace_id_refname && trc_conf->trace_id_refname[0])
        {
            reference_conf_add(AUTOGEN_REFERENCE_TYPE_TRACE_ID, trc_conf->trace_id_refname, 
                trc_conf->id_size, FALSE, trc_conf->id_special_type, AUTOGEN_OBJ_ANY, AUTOGEN_OBJ_ANY);
        }
    }

    memset(&s_ref_system, 0, sizeof(autogen_ref));

    s_ref_system.name          = "TRACE_DATA_LENGTH";
    s_ref_system.original_name = s_ref_system.name;
    s_ref_system.is_used       = TRUE;
    s_ref_system.is_external   = TRUE;
    s_ref_system.type          = referenceTypeTraceDataLength;
    s_ref_system.value         = 0;
    s_ref_system.algorithm     = PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH;
}

/* Returns TRUE if the reference name is predefined (such as MSG_ID) */
int reference_is_name_predefined(const char* name)
{
    return (reference_get_configuration(name) != NULL);
}

/* Returns TRUE if the reference name is reseerved (such as REF_AS_MANY_AS_POSSIBLE) */
int reference_is_name_reserved(const char* name)
{
    int n = 0;

    for (; n < AUTOGEN_REFERENCE_RESERVED_MAX; n++)
    {
        if (!strcmp(name, s_ref_reserved_names[n]))
        {
            break;
        }
    }

    return n < AUTOGEN_REFERENCE_RESERVED_MAX;
}

/* Use the value reference given by item. If reference is not found, it is created as unresolved reference */
void reference_use_counter(autogen_item* item, autogen_feature *featureflag)
{
    autogen_ref_handle* ref_handle = reference_get_handle_from_obj(&item->base);
    autogen_ref* ref = reference_find_from_handle(ref_handle, item->refname, featureflag, TRUE);
    if (ref)
    {
        if (!reference_is_counter(ref))
        {
            int line = item ? item->base.file_line : 0;

            util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Reference '%s' is not a value reference", item->refname);
        }

        reference_use(ref);
    }
    else if (!strcmp(item->refname, "TRACE_DATA_LENGTH"))
    {
        /* Must be used in a trace */
        const autogen_obj* seq = util_get_base_parent(&item->base);
        if (!(seq->res->base.subtype & RESOURCE_TRC_ANY) && strcmp(seq->res->base.name, "PN_TRACE"))
        {
            int line = item ? item->base.file_line : 0;

            util_error_line(NULL, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Reference '%s' is reserved, and can't be used in this context", item->refname);
            return;
        }

		/* Add reference to list of references */
		ref = reference_add(ref_handle, item->refname, referenceTypeTraceDataLength, item, featureflag);
        ref->is_external = TRUE;
    }
    /* If reference is not found (and reference is not in a reusable sequence (no struct), add it as unresolved */
    else if (ref_handle->parent->type != AUTOGEN_OBJ_SEQ || !(ref_handle->parent->flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
    {
		/* Add unresolved reference to list of references */
		reference_add(ref_handle, item->refname, referenceTypeCounterUnresolved, item, featureflag);
    }
}

/* Use the tag reference given by item. If reference is not found, it is created as unresolved reference 
   Check that the constant/bit tables referred contain the definitions used in the cases
*/
void reference_use_tag(autogen_item* item, autogen_feature *featureflag)
{
    autogen_ref_handle* ref_handle = reference_get_handle_from_obj(&item->base);
    autogen_ref* ref = reference_find_from_handle(ref_handle, item->refname, featureflag, TRUE);
    if (ref)
    {
        if (reference_is_counter(ref))
        {
            int line = item ? item->base.file_line : 0;

            util_error_line(NULL, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
                "Reference '%s' is not a tag (based on REFERENCE_CONST)", item->refname);
            return;
        }
        else
        {
            reference_check_choice((autogen_item_value*)ref->item, (autogen_item_choice*)item);
        }

        reference_use(ref);
    }
    /* If reference is not found (and reference is not in a reusable sequence (no struct), add it as unresolved */
    else if (ref_handle->parent->type != AUTOGEN_OBJ_SEQ || !(ref_handle->parent->flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
    {
        /* Add unresolved reference to list of references */
        reference_add(ref_handle, item->refname, referenceTypeTagUnresolved, item, featureflag);
    }
}

/* End of file autogen_ref.c */
