/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_check.c
                ---------------
                SW Module






Project:          autogen

%name:            autogen_check.c %
%version:         co1tss#84 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Wed Nov 25 10:54:26 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file contains some functions that checks various things in the data model. All the 
    functions are part of the data model analysis code
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_check.h"
#include "autogen_prop.h"
#include "autogen_util.h"
#include "pmdconstants.h"
#include "pmd_heap.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL static
#endif /* LOCAL */


LOCAL void check_seq_alignment_from_list(const char* current_file, const autogen_seq* seq, autogen_obj_list* obj_list, autogen_ver* ver, unsigned int* alignment, int* first_warning);
LOCAL void check_item_size_alignment(const char* current_file, const autogen_seq* seq, unsigned int data_size, unsigned int alignment, int* first_warning);
LOCAL void check_update_alignment(unsigned int data_size, unsigned int* alignment, int is_fixed, int align_to_64_bits);
LOCAL void check_update_alignment_32(unsigned int data_size, unsigned int* alignment, int is_fixed);
#if (PMD_FILE_FORMAT >= 600)
LOCAL void check_update_alignment_64(unsigned int data_size, unsigned int* alignment, int is_fixed, int align_to_64_bits);
#endif

LOCAL void check_recursion_seq(const char* current_file, autogen_seq* seq, autogen_res* res, const autogen_ver* ver,
                               const autogen_seq *sequences[], int num_sequences, int max_sequences);

LOCAL void check_recursion_item_list(const char* current_file, autogen_obj_list* obj_list, autogen_res* res, const autogen_ver* ver,
                                     const autogen_seq *sequences[], int num_sequences, int max_sequences);

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: check_seq_alignment
 
    Purpose: 
        Checks the field alignment in a sequence
 
    Functional Description:
        Checks the alignment of all fields in a sequence for a certain version interval.
        The resulting alignment in the sequence is updated at the end
        All alignment problems are reported to the log file

    Arguments: 
        current_file - [in] filename of the current mdf, containing the sequence
        seq          - [in] pointer to the sequence, which should be checked
        ver          - [in] pointer to the version object, for which the sequence should be checked
*/
/* --------------------------------------------------------------------------------------------- */
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
unsigned int check_seq_alignment(const char* current_file, autogen_seq* seq, autogen_ver* ver)
{
    unsigned int alignment = AUTOGEN_ALIGNMENT_DWORD;
    int first_warning = TRUE;

#if (PMD_FILE_FORMAT >= 600)
    if (prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS))
    {
        alignment = AUTOGEN_ALIGNMENT_DDWORD;
        if (util_has_multiple_versions((autogen_obj*) seq))
        {
            /* Allow older versions to use 32-bit alignment */
            if (util_has_newer_version((autogen_obj*) seq))
            {
                alignment = AUTOGEN_ALIGNMENT_DWORD;
            }
        }
    }
#endif

    /* for PhoNet messages, set the initial alignment of the sequence to 16 bit */
    if (seq->base.res->base.subtype == RESOURCE_PHONET && seq->base.type == AUTOGEN_OBJ_MSG)
    {
        alignment = AUTOGEN_ALIGNMENT_WORD;
    }
    /* for MM messages, set different alignment for REQ/RESP and IND messages */
    else if (seq->base.res->base.subtype == RESOURCE_MEDIA_MODULE || seq->base.res->base.subtype == RESOURCE_MEDIA_MODULE_EXTENSION)
    {
        if (seq->base.flag & AUTOGEN_MSG_IND)
        {
            alignment = AUTOGEN_ALIGNMENT_BYTE_1;
        }
        else if (seq->base.flag & (AUTOGEN_MSG_NTF | AUTOGEN_MSG_REQ))
        {
            alignment = AUTOGEN_ALIGNMENT_BYTE_3;
        }
        else if (seq->base.flag & AUTOGEN_MSG_RESP)
        {
            alignment = AUTOGEN_ALIGNMENT_DWORD;
        }
    }


    check_seq_alignment_from_list(current_file, seq, &seq->base.child_list, ver, &alignment, &first_warning);

    /* check that (template) sub block length is divisible by 4 bytes */
    /* requirement DSUBL010, DSEQE205 */
    if (seq->base.type == AUTOGEN_OBJ_SB && 
        !prop_has((autogen_obj*)seq, PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4) ||
        seq->base.type == AUTOGEN_OBJ_SB_TEMPLATE)
    {
#if (PMD_FILE_FORMAT >= 600)
        if (prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS))
        {
            if (alignment != AUTOGEN_ALIGNMENT_DDWORD)
            {
                if (!prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_CHECK_DISABLE) && !prop_has((autogen_obj*)seq, PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_8))
                {
                    util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                        "Length of %s '%s' is not divisible by 8",
                        util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                }
            }
        }
        else
#endif
        if (alignment != AUTOGEN_ALIGNMENT_DWORD)
        {
            if (!prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_CHECK_DISABLE))
            {
                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                    "Length of %s '%s' is not divisible by 4",
                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
            }
        }
    }

    /* return sequence alignment 'lowest common denominator' */
    return util_get_resulting_alignment(seq->alignment, alignment, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
}
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

/* --------------------------------------------------------------------------------------------- */
/*  Name: check_seq_recursion
 
    Purpose: 
        Checks whether the sequence ultimately uses itself recursively
 
    Functional Description:
        check_seq_recursion traveres all structs, choices and sub blocks referenced directly
        or indirectly from this sequence. If any of these reference themselves directly or
        indirecty, this function stops autogen with a fatal error.

    Arguments: 
        current_file - [in] filename of the current mdf, containing the sequence
        seq          - [in] pointer to the sequence, which should be checked
        res          - [in] pointer to the resource, containing the resource
        ver          - [in] pointer to the version object, for which the sequence should be checked
*/
/* --------------------------------------------------------------------------------------------- */
void check_seq_recursion(const char* current_file, autogen_seq* seq, autogen_res* res, autogen_ver* ver)
{
    const autogen_seq *sequences[100];
    static const int max_sequences = sizeof(sequences)/sizeof(sequences[0]);

    check_recursion_seq(current_file, seq, res, ver, sequences, 0, max_sequences);
}

/* --------------------------------------------------------------------------------------------- */

/*  Checks the value limits of the item 'limit_obj'. First checks, that limits are
    allowed for the item. Then checks that the defined limits are legal, and
    that the are within the range of the size of the item. Any errors or
    warnings are reported to the isi.log file.
*/
void check_item_limits(const char* current_file, const autogen_item_value *limit_obj)
{
    const autogen_prop *minprop = prop_find_first(&limit_obj->base.base,
        PROPERTY_ITEM_MINIMUM_VALUE);
    const autogen_prop *maxprop = prop_find_first(&limit_obj->base.base,
        PROPERTY_ITEM_MAXIMUM_VALUE);
    const autogen_prop *exprop = NULL;
    int minmaxline = maxprop ? maxprop->lineno : (minprop ? minprop->lineno : 0);

    /* check that the limits are valid for the item */
    if (limit_obj->base.length < 0)
    {
#if (PMD_FILE_FORMAT >= 600)
        signed long long length_s  = -limit_obj->base.length;
        signed long long max_val_s = ((unsigned long long)1 << (length_s - 1)) - 1;
        signed long long min_val_s = - ((signed long long)1 << (length_s - 1));
        signed long long max_val_s_used = max_val_s;
        signed long long min_val_s_used = min_val_s;
#else
        int length_s  = -limit_obj->base.length;
        int max_val_s = (1 << (length_s - 1)) - 1;
        int min_val_s = - (1 << (length_s - 1));
        int max_val_s_used = max_val_s;
        int min_val_s_used = min_val_s;
#endif

        /* check minimum value */
#if (PMD_FILE_FORMAT >= 600)
        if (minprop)
        {
            if (limit_obj->base.length == -8)
            {
                signed char temp_val = (signed char)minprop->value;
                ((autogen_prop *)minprop)->value = (unsigned long long)temp_val; /* TODO: avoid this const cast */
            }
            else if (limit_obj->base.length == -16)
            {
                signed short int temp_val = (signed short int)minprop->value;
                ((autogen_prop *)minprop)->value = (unsigned long long)temp_val; /* TODO: avoid this const cast */
            }
            else if (limit_obj->base.length == -32)
            {
                int temp_val = (int)minprop->value;
                ((autogen_prop *)minprop)->value = (unsigned long long)temp_val; /* TODO: avoid this const cast */
            }

            if ((signed long long)minprop->value < min_val_s || (signed long long)minprop->value > max_val_s)
            {
                util_error_line(current_file, minprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %lld, which is out of range [%lld; %lld]",
                    prop_name(minprop), (signed long long)minprop->value, min_val_s, max_val_s);
            }

            min_val_s_used = minprop->value;
        }
#else
        if (minprop)
        {
            if (limit_obj->base.length == -8)
            {
                signed char temp_val = (signed char)minprop->value;
                ((autogen_prop *)minprop)->value = (unsigned int)temp_val; /* TODO: avoid this const cast */
            }
            else if (limit_obj->base.length == -16)
            {
                signed short int temp_val = (signed short int)minprop->value;
                ((autogen_prop *)minprop)->value = (unsigned int)temp_val; /* TODO: avoid this const cast */
            }

            if ((int)minprop->value < min_val_s || (int)minprop->value > max_val_s)
            {
                util_error_line(current_file, minprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %d, which is out of range [%d; %d]",
                    prop_name(minprop), (int)minprop->value, min_val_s, max_val_s);
            }

            min_val_s_used = minprop->value;
        }
#endif

        /* check maximum value */
#if (PMD_FILE_FORMAT >= 600)
        if (maxprop)
        {
            if (limit_obj->base.length == -8)
            {
                signed char temp_val = (signed char)maxprop->value;
                ((autogen_prop *)maxprop)->value = (unsigned long long)temp_val; /* TODO: avoid this const cast */
            }
            else
                if (limit_obj->base.length == -16)
                {
                    signed short int temp_val = (signed short int)maxprop->value;
                    ((autogen_prop *)maxprop)->value = (unsigned long long)temp_val; /* TODO: avoid this const cast */
                }
            else if (limit_obj->base.length == -32)
            {
                int temp_val = (int)maxprop->value;
                ((autogen_prop *)maxprop)->value = (unsigned long long)temp_val; /* TODO: avoid this const cast */
            }

                if ((signed long long)maxprop->value < min_val_s || (signed long long)maxprop->value > max_val_s)
                {
                    util_error_line(current_file, maxprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Property '%s' is %lld, which is out of range [%lld; %lld]",
                        prop_name(maxprop), (signed long long)maxprop->value, min_val_s, max_val_s);
                }

                max_val_s_used = maxprop->value;
        }
#else
        if (maxprop)
        {
            if (limit_obj->base.length == -8)
            {
                signed char temp_val = (signed char)maxprop->value;
                ((autogen_prop *)maxprop)->value = (unsigned int)temp_val; /* TODO: avoid this const cast */
            }
            else
                if (limit_obj->base.length == -16)
                {
                    signed short int temp_val = (signed short int)maxprop->value;
                    ((autogen_prop *)maxprop)->value = (unsigned int)temp_val; /* TODO: avoid this const cast */
                }

                if ((int)maxprop->value < min_val_s || (int)maxprop->value > max_val_s)
                {
                    util_error_line(current_file, maxprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                        "Property '%s' is %d, which is out of range [%d; %d]",
                        prop_name(maxprop), (int)maxprop->value, min_val_s, max_val_s);
                }

                max_val_s_used = maxprop->value;
        }
#endif



        /* check interval */
        if (max_val_s_used < min_val_s_used)
        {
            util_error_line(current_file, minmaxline, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Invalid item limit interval defined: "
                "Property '%s' is %ld, which is smaller than property '%s' (which is %ld)",
                prop_name(maxprop), max_val_s_used, prop_name(minprop), min_val_s_used);
        }

        /* check exceptional values */
        exprop = prop_find_first(&limit_obj->base.base, PROPERTY_ITEM_EXCEPTIONAL_VALUE);
        while (exprop)
        {
#if (PMD_FILE_FORMAT >= 600)
            if (limit_obj->base.length == -8)
            {
                signed char temp_val = (signed char)exprop->value;
                ((autogen_prop *) exprop)->value = (unsigned long long)temp_val; /* TODO: avoid const cast? */
            }
            else if (limit_obj->base.length == -16)
            {
                signed short int temp_val = (signed short int)exprop->value;
                ((autogen_prop *) exprop)->value = (unsigned long long)temp_val; /* TODO: avoid const cast? */
            }
            else if (limit_obj->base.length == -32)
            {
                int temp_val = (int)exprop->value;
                ((autogen_prop *)exprop)->value = (unsigned long long)temp_val; /* TODO: avoid this const cast */
            }
#else
            if (limit_obj->base.length == -8)
            {
                signed char temp_val = (signed char)exprop->value;
                ((autogen_prop *) exprop)->value = (unsigned int)temp_val; /* TODO: avoid const cast? */
            }
            else if (limit_obj->base.length == -16)
            {
                signed short int temp_val = (signed short int)exprop->value;
                ((autogen_prop *) exprop)->value = (unsigned int)temp_val; /* TODO: avoid const cast? */
            }
#endif

#if (PMD_FILE_FORMAT >= 600)
            /* is exceptional value possible at all */
            if ((min_val_s > (signed long long)exprop->value || 
                max_val_s < (signed long long)exprop->value))
            {
                util_error_line(current_file, exprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %lld, which is out of range [%lld; %lld]",
                    prop_name(exprop), (signed long long)exprop->value, min_val_s, max_val_s);
            }

            /* is exceptional value within used interval */
            if (max_val_s_used >= (signed long long)exprop->value &&
                min_val_s_used <= (signed long long)exprop->value && (minprop || maxprop))
            {
                util_error_line(current_file, exprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %lld, which conflicts with defined interval [%lld; %lld]",
                    prop_name(exprop), (signed long long)exprop->value, min_val_s_used, max_val_s_used);
            }
#else
            /* is exceptional value possible at all */
            if ((min_val_s > (int)exprop->value || 
                max_val_s < (int)exprop->value))
            {
                util_error_line(current_file, exprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %d, which is out of range [%d; %d]",
                    prop_name(exprop), (int)exprop->value, min_val_s, max_val_s);
            }

            /* is exceptional value within used interval */
            if (max_val_s_used >= (int)exprop->value &&
                min_val_s_used <= (int)exprop->value && (minprop || maxprop))
            {
                util_error_line(current_file, exprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %d, which conflicts with defined interval [%d; %d]",
                    prop_name(exprop), (int)exprop->value, min_val_s_used, max_val_s_used);
            }
#endif

            /* next exceptional value */
            exprop = prop_find_next(exprop);
        }
    }
    else
    {
#if (PMD_FILE_FORMAT >= 600)
        unsigned long long length_us  = (unsigned long long) limit_obj->base.length;
        unsigned long long max_val_us = 0xFFFFFFFFFFFFFFFF;
        unsigned long long min_val_us_used = 0;
        unsigned long long max_val_us_used = max_val_us;
        if (length_us < 64)
        {
            max_val_us = ((unsigned long long)1 << length_us) - 1;
        }
#else
        unsigned int length_us  = (unsigned int) limit_obj->base.length;
        unsigned int max_val_us = 0xFFFFFFFF;
        unsigned int min_val_us_used = 0;
        unsigned int max_val_us_used = max_val_us;
        if (length_us < 32)
        {
            max_val_us = (1 << length_us) - 1;
        }
#endif

        /* check minimum value */
        if (minprop)
        {
            if (minprop->value > max_val_us)
            {
#if (PMD_FILE_FORMAT >= 600)
                util_error_line(current_file, minprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %llu, which out of range [0; %llu]",
                    prop_name(minprop), minprop->value, max_val_us);
#else
                util_error_line(current_file, minprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %u, which out of range [0; %u]",
                    prop_name(minprop), minprop->value, max_val_us);
#endif
            }

            min_val_us_used = minprop->value;
        }

        /* check maximum value */
        if (maxprop)
        {
            if (maxprop->value > max_val_us)
            {
#if (PMD_FILE_FORMAT >= 600)
                util_error_line(current_file, maxprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %llu, which is out of range [0; %llu]",
                    prop_name(maxprop), maxprop->value, max_val_us);
#else
                util_error_line(current_file, maxprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %u, which is out of range [0; %u]",
                    prop_name(maxprop), maxprop->value, max_val_us);
#endif
            }

            max_val_us_used = maxprop->value;
        }

        /* check interval */
        if (max_val_us_used < min_val_us_used)
        {
#if (PMD_FILE_FORMAT >= 600)
            util_error_line(current_file, minmaxline, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Invalid item limit interval defined: "
                "Property '%s' is %llu, which is smaller than property '%s' (which is %llu)",
                prop_name(maxprop), max_val_us_used, prop_name(minprop), min_val_us_used);
#else
            util_error_line(current_file, minmaxline, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Invalid item limit interval defined: "
                "Property '%s' is %u, which is smaller than property '%s' (which is %u)",
                prop_name(maxprop), max_val_us_used, prop_name(minprop), min_val_us_used);
#endif
        }

        /* check exceptional values */
        exprop = prop_find_first(&limit_obj->base.base, PROPERTY_ITEM_EXCEPTIONAL_VALUE);
        while (exprop)
        {
            /* is exceptional value possible at all */
            if (max_val_us < exprop->value)
            { 
#if (PMD_FILE_FORMAT >= 600)
                util_error_line(current_file, exprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "Property '%s' is %llu, which is out of range [0; %llu]",
                    prop_name(exprop), exprop->value, max_val_us);
#else
                util_error_line(current_file, exprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "Property '%s' is %u, which is out of range [0; %u]",
                    prop_name(exprop), exprop->value, max_val_us);
#endif
            }

            /* is exceptional value within used interval */
            if (max_val_us_used >= exprop->value && 
                min_val_us_used <= exprop->value && (minprop || maxprop))
            {
#if (PMD_FILE_FORMAT >= 600)
                util_error_line(current_file, exprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %llu, which conflicts with defined interval [%llu; %llu]",
                    prop_name(exprop), exprop->value, min_val_us_used, max_val_us_used);
#else
                util_error_line(current_file, exprop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Property '%s' is %u, which conflicts with defined interval [%u; %u]",
                    prop_name(exprop), exprop->value, min_val_us_used, max_val_us_used);
#endif
            }

            /* next exceptional value */
            exprop = prop_find_next(exprop);
        }
    }
}


void check_item_default_value(const char* current_file, autogen_item* item)
{
    const autogen_prop *default_prop = prop_find_first(&item->base, PROPERTY_ITEM_DEFAULT_VALUE);
    if (default_prop)
    {
#if (PMD_FILE_FORMAT >= 600)
        unsigned long long prop_value = default_prop->value;
        unsigned long long min_val = 0;
        unsigned long long max_val = 0;
#else
        unsigned int prop_value = default_prop->value;
        unsigned int min_val = 0;
        unsigned int max_val = 0;
#endif

        char min_val_str[2*AUTOGEN_MAX_NAME_LENGTH] = "";
        char max_val_str[2*AUTOGEN_MAX_NAME_LENGTH] = "";

        /* convert value from signed to unsigned as we now know the original size */
        if (item->length == -8)
        {
            signed char temp_val = (signed char)prop_value;
            ((autogen_prop *)default_prop)->value = (unsigned int)temp_val; /* TODO: avoid this const cast */
        }
        else if (item->length == -16)
        {
            signed short int temp_val = (signed short int)prop_value;
            ((autogen_prop *)default_prop)->value = (unsigned int)temp_val; /* TODO: avoid this const cast */
        }
#if (PMD_FILE_FORMAT >= 600)
        else if (item->length == -32)
        {
            int temp_val = (int)prop_value;
            ((autogen_prop *)default_prop)->value = (unsigned long long)temp_val; /* TODO: avoid this const cast */
        }
#endif

        util_get_item_limits(item, &min_val, &max_val, min_val_str, max_val_str);

        /* if default value is not within limits, 
        check that it is one of the exceptional values 
        */
        if (item->length < 0)
        {
            /* Handle the signed case */
            if ((int)prop_value > (int)max_val || (int)prop_value < (int)min_val)
            {
                /* Find any exceptional value property with the same value as the default property */
                const autogen_prop *exprop = prop_find_first(&item->base, PROPERTY_ITEM_EXCEPTIONAL_VALUE);
                while (exprop && (int) exprop->value != (int) prop_value)
                {
                    exprop = prop_find_next(exprop);
                }

                /* If none matched, the default value cannot be used */
                if (!exprop)
                {
#if (PMD_FILE_FORMAT >= 600)
                    util_error_line(current_file, default_prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, 
                        "Property '%s' is %lld, which is out of range [%lld; %lld]",
                        prop_name(default_prop), (long long)prop_value, min_val, max_val);
#else
                    util_error_line(current_file, default_prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, 
                        "Property '%s' is %d, which is out of range [%d; %d]",
                        prop_name(default_prop), (int)prop_value, min_val, max_val);
#endif
                }
            }
        }
        else
        {
            /* Handle the unsigned case */
            if (prop_value > max_val || prop_value < min_val)
            {
                /* Find any exceptional value property with the same value as the default property */
                const autogen_prop *exprop = prop_find_first(&item->base, PROPERTY_ITEM_EXCEPTIONAL_VALUE);
                while (exprop && exprop->value != prop_value)
                {
                    exprop = prop_find_next(exprop);
                }

                /* If none matched, the default value cannot be used */
                if (!exprop)
                {
#if (PMD_FILE_FORMAT >= 600)
                    util_error_line(current_file, default_prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' is %llu, which is out of range [%llu; %llu]",
                        prop_name(default_prop), prop_value, min_val, max_val);
#else
                    util_error_line(current_file, default_prop->lineno, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                        "Property '%s' is %u, which is out of range [%u; %u]",
                        prop_name(default_prop), prop_value, min_val, max_val);
#endif
                }
            }
        }
    }
}


int check_c_name(const char* current_file, int line, const char* argname, const char* name, unsigned int flags)
{
    int success = TRUE;
    char car;
    const char *name_trav = name;


    /* check if name exist at all */
    /* requirement YYYY */
    if (!name || !name[0])
    {
        success = FALSE;
    }

    if (success)
    {
        car = *(name_trav++);

        /* check first character */
        /* requirement YYYY */

        if ((car < 'a' || car > 'z') && (car < 'A' || car > 'Z') && car != '_')
        {
            success = FALSE;
        }

        while (car && success)
        {
            if (car == '*' && (flags & CHECK_NAME_ALLOW_ASTERIX))
            {
                success = TRUE;
            }
            else if ((car < 'a' || car > 'z') && (car < 'A' || car > 'Z') && (car < '0' || car > '9') && car != '_')
            {
                success = FALSE;
            }

            car = *(name_trav++);
        }
    }

    if (!success && (flags & CHECK_NAME_EXIT_ON_FAIL))
    {
        util_error_line(current_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
            "Argument '%s' is not valid", argname);
    }

    return success;
}


void check_parname(const char* current_file, int line, char* name)
{
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
    unsigned int n;
    int is_valid = TRUE;
 #ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
    unsigned int leading_blanks;
    unsigned int trailing_blanks = 0;
    unsigned int lgt = name ? strlen(name) : 0;
 #endif /* AUTOGEN_DISABLE_TOUGH_CHECKS */
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

    /* Check for NULL */
    check_string(current_file, line, "parname", name, CHECK_NAME_EXIT_ON_FAIL);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
    /* check for leading blanks nd underscores*/
    for (leading_blanks=0; leading_blanks < lgt; leading_blanks++)
    {
        if (!((name[leading_blanks] == ' ') || (name[leading_blanks] == '_')))
            break;
    }
    if (leading_blanks)
    {
        util_error_line(current_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 1,
            "Argument 'parname' has leading blanks or underscores. Please remove!", name);
    }
    /* check for trailing blanks and underscores*/
    for (n = lgt-1; n >= 0; n--, trailing_blanks++)
    {
        if (!((name[n] == ' ') || (name[n] == '_')))
            break;
    }
    if (trailing_blanks)
    {
        util_error_line(current_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 1,
            "Argument 'parname' has trailing blanks or underscores. Please remove!", name);
    }
#endif /* AUTOGEN_DISABLE_TOUGH_CHECKS */

    /* check for unsupported characters */
    for (n = 0; n < strlen(name) && is_valid; n++)
    {
        if ((name[n] < 'a' || name[n] > 'z') && 
            (name[n] < 'A' || name[n] > 'Z') && 
            (name[n] < '0' || name[n] > '9') && 
            name[n] != '_' && 
            name[n] != ' ')
        {
            is_valid = FALSE;
        }
    }

    if (!is_valid)
    {
        util_error_line(current_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 2, 
            "Argument 'parname' contains invalid characters", name);
    }

 #ifndef AUTOGEN_DISABLE_TOUGH_CHECKS
    if (leading_blanks || trailing_blanks)
    {
        n=0;
        if ((leading_blanks + trailing_blanks) < lgt) /* at least one legal character */
        {
            /* skip leading blanks and leading underscores */
            for (n=0; n < (lgt - (leading_blanks + trailing_blanks)); n++)
            {
                name[n] = name[n+leading_blanks];
            }
        }
        /* Replace remaining characters in original name by NULL */
        for (; n < lgt; n++)
        {
            name[n] = '\0';
        }
    }

    /* Check for validity of string */
    check_string(current_file, line, "parname", name, CHECK_NAME_EXIT_ON_FAIL);

 #endif /* AUTOGEN_DISABLE_TOUGH_CHECKS */
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */
}

/*  Checks the actual value of the macro argument with name specified in 'argname'
    has a legal string value, specified in 'strname'.
    If the check fails, the application aborts. The following is checked:
    - the 'strname' pointer must exist (!NULL)
    - the length of 'strname' must not exceed the value specified in 'maxlength'
    - the length of 'strname' must be > 0 if 'type' specifies 'NonEmpty'
*/
/* --------------------------------------------------------------------------------------------- */
/*  Name: check_string
 
    Purpose: Checks the validity of a string
 
    Functional Description:
        Checks the validity of a string. Mainly used for checking
        or reads the text for each item, and concatenates the text for all the
        items into a single text string.

    Arguments: 
        current_file - [in] Pointer to the first element in the comment list. May be NULL.
        line         - [in] Pointer to the first element in the comment list. May be NULL.
        argname      - [in] Pointer to the first element in the comment list. May be NULL.
        strname      - [in] Pointer to the first element in the comment list. May be NULL.
        flags        - [in] Pointer to the first element in the comment list. May be NULL.

    Return Values:
        None
*/
/* --------------------------------------------------------------------------------------------- */
void check_string(const char* current_file, int line, const char* argname, const char* strname, unsigned int flags)
{
    if (!strname || !(flags & CHECK_NAME_ALLOW_EMPTY) && !strname[0])
    {
        if (flags & CHECK_NAME_EXIT_ON_FAIL)
        {
            util_error_line(current_file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                "Argument '%s' is not valid", argname);
        }
        else
        {
            util_error_line(current_file, line, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Argument '%s' is not valid", argname);
        }
    }
}


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
LOCAL void check_item_size_alignment(const char* current_file,
                                     const autogen_seq* seq,
                                     unsigned int data_size,
                                     unsigned int alignment,
                                     int* first_warning)
{
    unsigned int error_type = prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_CHECK_BREAK) ? AUTOGEN_ERROR_FATAL : AUTOGEN_ERROR_WARNING;

    if (data_size == 0 || !*first_warning || prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_CHECK_DISABLE))
    {
        return;
    }

    /* suppress warning? */
    if (error_type == AUTOGEN_ERROR_WARNING && prop_has(&seq->base, PROPERTY_SUPPRESS_AUTOGEN_WARNINGS))
    {
        return;
    }

#if (PMD_FILE_FORMAT >= 600)
    /* ddword is to be inserted */
    if (data_size == 8)
    {
        if (alignment == AUTOGEN_ALIGNMENT_BYTE_ANY ||
            alignment == AUTOGEN_ALIGNMENT_ODD ||
            alignment == AUTOGEN_ALIGNMENT_DWORD_ANY ||
            alignment == AUTOGEN_ALIGNMENT_WORD_ANY)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A dynamic 64 bit alignment is needed",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_BYTE_1)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 56 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_WORD)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 48 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_BYTE_3)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 40 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_DWORD)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 32 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_BYTE_5)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 24 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_BYTE_6)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 16 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_BYTE_7)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 8 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
    }
    else
#endif
    /* dword is to be inserted */
    if (data_size == 4)
    {
        if (alignment == AUTOGEN_ALIGNMENT_BYTE_ANY ||
            alignment == AUTOGEN_ALIGNMENT_ODD ||
            alignment == AUTOGEN_ALIGNMENT_WORD_ANY)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, error_type, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A dynamic 32 bit alignment is needed",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_BYTE_1)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, error_type, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 24 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_BYTE_3)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, error_type, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 8 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_WORD)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, error_type, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 16 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
    }
    /* word is to be inserted */
    else if (data_size == 2)
    {
        if (alignment == AUTOGEN_ALIGNMENT_BYTE_ANY)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, error_type, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A dynamic 16 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
        else if (alignment == AUTOGEN_ALIGNMENT_BYTE_1 ||
            alignment == AUTOGEN_ALIGNMENT_BYTE_3 ||
            alignment == AUTOGEN_ALIGNMENT_ODD)
        {
            *first_warning = FALSE;

            util_error_line(current_file, 0, error_type, AUTOGEN_ENV_LOCAL, 7,
                "Alignment problem in %s '%s'. A fixed 8 bit alignment must be inserted",
                util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
        }
    }
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL void check_update_alignment_64(unsigned int data_size, unsigned int* alignment, int is_fixed, int align_to_64_bits)
{
    unsigned int size_mod_8;
    unsigned int align_dyn_fix[11][7]=
    {
/*DWORD (1)*/
        AUTOGEN_ALIGNMENT_BYTE_5,   AUTOGEN_ALIGNMENT_BYTE_6,   AUTOGEN_ALIGNMENT_BYTE_7,   AUTOGEN_ALIGNMENT_DDWORD,   AUTOGEN_ALIGNMENT_BYTE_1,   AUTOGEN_ALIGNMENT_WORD,     AUTOGEN_ALIGNMENT_BYTE_3,
/*BYTE_1 (2)*/
        AUTOGEN_ALIGNMENT_WORD,     AUTOGEN_ALIGNMENT_BYTE_3,   AUTOGEN_ALIGNMENT_DWORD,    AUTOGEN_ALIGNMENT_BYTE_5,   AUTOGEN_ALIGNMENT_BYTE_6,   AUTOGEN_ALIGNMENT_BYTE_7,   AUTOGEN_ALIGNMENT_DDWORD,
/*BYTE_3 (3)*/
        AUTOGEN_ALIGNMENT_DWORD,    AUTOGEN_ALIGNMENT_BYTE_5,   AUTOGEN_ALIGNMENT_BYTE_6,   AUTOGEN_ALIGNMENT_BYTE_7,   AUTOGEN_ALIGNMENT_DDWORD,   AUTOGEN_ALIGNMENT_BYTE_1,   AUTOGEN_ALIGNMENT_WORD,
/*ODD (4)*/
        AUTOGEN_ALIGNMENT_WORD_ANY, AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_WORD_ANY, AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_WORD_ANY, AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_WORD_ANY,
/*WORD (5)*/
        AUTOGEN_ALIGNMENT_BYTE_3,   AUTOGEN_ALIGNMENT_DWORD,    AUTOGEN_ALIGNMENT_BYTE_5,   AUTOGEN_ALIGNMENT_BYTE_6,   AUTOGEN_ALIGNMENT_BYTE_7,   AUTOGEN_ALIGNMENT_DDWORD,   AUTOGEN_ALIGNMENT_BYTE_1,
/*WORD_ANY (6)*/
        AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_WORD_ANY, AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_WORD_ANY, AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_WORD_ANY, AUTOGEN_ALIGNMENT_ODD,
/*BYTE_ANY (7)*/
        AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,
/*DDWORD (8)*/
        AUTOGEN_ALIGNMENT_BYTE_1,   AUTOGEN_ALIGNMENT_WORD,     AUTOGEN_ALIGNMENT_BYTE_3,   AUTOGEN_ALIGNMENT_DWORD,    AUTOGEN_ALIGNMENT_BYTE_5,   AUTOGEN_ALIGNMENT_BYTE_6,   AUTOGEN_ALIGNMENT_BYTE_7,
/*BYTE_5 (9)*/
        AUTOGEN_ALIGNMENT_BYTE_6,   AUTOGEN_ALIGNMENT_BYTE_7,   AUTOGEN_ALIGNMENT_DDWORD,   AUTOGEN_ALIGNMENT_BYTE_1,   AUTOGEN_ALIGNMENT_WORD,     AUTOGEN_ALIGNMENT_BYTE_3,   AUTOGEN_ALIGNMENT_DWORD,
/*BYTE_6 (10)*/
        AUTOGEN_ALIGNMENT_BYTE_7,   AUTOGEN_ALIGNMENT_DDWORD,   AUTOGEN_ALIGNMENT_BYTE_1,   AUTOGEN_ALIGNMENT_WORD,     AUTOGEN_ALIGNMENT_BYTE_3,   AUTOGEN_ALIGNMENT_DWORD,    AUTOGEN_ALIGNMENT_BYTE_5,
/*BYTE_7 (11)*/
        AUTOGEN_ALIGNMENT_DDWORD,   AUTOGEN_ALIGNMENT_BYTE_1,   AUTOGEN_ALIGNMENT_WORD,     AUTOGEN_ALIGNMENT_BYTE_3,   AUTOGEN_ALIGNMENT_DWORD,    AUTOGEN_ALIGNMENT_BYTE_5,   AUTOGEN_ALIGNMENT_BYTE_6

    };
    if (!align_to_64_bits)
    {
        check_update_alignment_32(data_size, alignment, is_fixed);
    }
    else
    {
        size_mod_8 = data_size % 8;

        if (size_mod_8 > 0)
        {
            if (is_fixed)
            {
                *alignment = align_dyn_fix[*alignment - 1][size_mod_8 - 1];
            }
            /* dynamic number of bytes */
            else
            {
                if (size_mod_8 == 1 || size_mod_8 == 3 || size_mod_8 == 5 || size_mod_8 == 7)
                {
                    *alignment = AUTOGEN_ALIGNMENT_BYTE_ANY;
                }
                else
                {
                    if (*alignment == AUTOGEN_ALIGNMENT_DWORD && size_mod_8 == 4)
                    {
                        *alignment = AUTOGEN_ALIGNMENT_DWORD_ANY;
                    }
                    else
                    {
                        if (*alignment == AUTOGEN_ALIGNMENT_DWORD ||
                            *alignment == AUTOGEN_ALIGNMENT_DWORD_ANY ||
                            *alignment == AUTOGEN_ALIGNMENT_WORD ||
                            *alignment == AUTOGEN_ALIGNMENT_WORD_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_WORD_ANY;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_1 ||
                            *alignment == AUTOGEN_ALIGNMENT_BYTE_3 ||
                            *alignment == AUTOGEN_ALIGNMENT_BYTE_5 ||
                            *alignment == AUTOGEN_ALIGNMENT_BYTE_7 ||
                            *alignment == AUTOGEN_ALIGNMENT_ODD)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_ODD;
                        }
                        else
                        {
                            *alignment = AUTOGEN_ALIGNMENT_BYTE_ANY;
                        }
                    }
                }
            }
        }
        /* else keep DDWORD alignment */
    }
}
#endif

LOCAL void check_update_alignment_32(unsigned int data_size, unsigned int* alignment, int is_fixed)
{
    unsigned int size_mod_4;
    unsigned int align_dyn_fix[7][3] =
    {
        /* Dword     = 1 */ 
        AUTOGEN_ALIGNMENT_BYTE_1,    AUTOGEN_ALIGNMENT_WORD,      AUTOGEN_ALIGNMENT_BYTE_3,
        /* Byte1     = 2 */  
        AUTOGEN_ALIGNMENT_WORD,      AUTOGEN_ALIGNMENT_BYTE_3,    AUTOGEN_ALIGNMENT_DWORD,
        /* Byte3     = 3 */ 
        AUTOGEN_ALIGNMENT_DWORD,     AUTOGEN_ALIGNMENT_BYTE_1,    AUTOGEN_ALIGNMENT_WORD,
        /* Odd       = 4 */ 
        AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_WORD_ANY,
        /* Word      = 5 */ 
        AUTOGEN_ALIGNMENT_BYTE_3,    AUTOGEN_ALIGNMENT_DWORD,     AUTOGEN_ALIGNMENT_BYTE_1,
        /* WordAny   = 6 */ 
        AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_ODD,
        /* ByteAny   = 7 */ 
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY
    };

    size_mod_4 = data_size % 4;

    if (size_mod_4 > 0)
    {
        /* fixed number of bytes */
        if (is_fixed)
        {
            *alignment = align_dyn_fix[*alignment - 1][size_mod_4 - 1];
        }
        /* dynamic number of bytes */
        else
        {
            if (size_mod_4 == 1 || size_mod_4 == 3)
            {
                *alignment = AUTOGEN_ALIGNMENT_BYTE_ANY;
            }
            else
            {
                if (*alignment == AUTOGEN_ALIGNMENT_DWORD ||
                    *alignment == AUTOGEN_ALIGNMENT_WORD ||
                    *alignment == AUTOGEN_ALIGNMENT_WORD_ANY)
                {
                    *alignment = AUTOGEN_ALIGNMENT_WORD_ANY;
                }
                else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_1 ||
                    *alignment == AUTOGEN_ALIGNMENT_BYTE_3 ||
                    *alignment == AUTOGEN_ALIGNMENT_ODD)
                {
                    *alignment = AUTOGEN_ALIGNMENT_ODD;
                }
                else
                {
                    *alignment = AUTOGEN_ALIGNMENT_BYTE_ANY;
                }
            }

        }
    }
}

LOCAL void check_update_alignment(unsigned int data_size, unsigned int* alignment, int is_fixed, int align_to_64_bits)
{
#if (PMD_FILE_FORMAT >= 600)
    check_update_alignment_64(data_size, alignment, is_fixed, align_to_64_bits);
#else
    if (align_to_64_bits)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Alignment to 64 bits only supported in PMD_FILE_FORMAT 600 or higher");
    }
    check_update_alignment_32(data_size, alignment, is_fixed);
#endif
}

LOCAL void check_seq_alignment_from_list(const char* current_file, const autogen_seq* seq, autogen_obj_list* obj_list, autogen_ver* ver, unsigned int* alignment, int* first_warning)
{
    autogen_item* item = NULL;

    int alignment_check_enabled = !prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_CHECK_DISABLE);

    item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        unsigned int u_fact = 1;
        unsigned int u_length = (unsigned int)abs(item->length)/8;

        if (prop_has((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED) || 
            prop_has((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED))
        {
            u_length = 2;
            u_fact   = 2;
        }
        else if (prop_has((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_WORD_SIGNED) || 
            prop_has((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED))
        {
            u_length = 1;
            u_fact   = 2;
        }
        else if (prop_has((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_AS_ARRAY))
        {
            u_fact   = u_length;
            u_length = 1;            
        }

        /* only check alignment, if element is placed in a structure */
        if (item->base.flag & AUTOGEN_ITEM_IS_PART_OF_MERGE)
        {
            continue;
        }

        switch (item->base.subtype)
        {
        case AUTOGEN_ITEM_VALUE:
        case AUTOGEN_ITEM_RANGE:
        case AUTOGEN_ITEM_POINTER:
        case AUTOGEN_ITEM_TIMESTAMP:
        case AUTOGEN_ITEM_MERGE:
        case AUTOGEN_ITEM_BLOCK:
        case AUTOGEN_ITEM_REF:
            {
                check_item_size_alignment(current_file, seq, u_length, *alignment, first_warning);

                if (item->agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE ||
                    item->agg_type == AGG_TYPE_DYNAMIC_OPTIONAL ||
                    item->agg_type == AGG_TYPE_DYNAMIC_REF ||
                    item->agg_type == AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH ||
                    item->agg_type == AGG_TYPE_DYNAMIC_ZEROTERMINATED)
                {
                    check_update_alignment(u_length, alignment, FALSE, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
                }
                else if (item->agg_type == AGG_TYPE_FIXED_SINGLE ||
                    item->agg_type == AGG_TYPE_FIXED_MULTIPLE)
                {
                    check_update_alignment(item->agg_n * u_length * u_fact, alignment, TRUE,prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
                }
            }
            break;

        case AUTOGEN_ITEM_FILLER:
            {
                if (item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
                {
                    /* align to next word */
                    if (u_length == 2)
                    {
                        if (*alignment == AUTOGEN_ALIGNMENT_BYTE_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_WORD_ANY;
                            item->base.flag |= AUTOGEN_FILLER_0_OR_1_BYTES;
                        }
                        /* could an 8 bit fixed filler be used instead */
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_1)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 16 bit dynamic filler can be replaced by an 8 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_WORD;
                            item->base.flag |= AUTOGEN_FILLER_1_BYTES_POSSIBLE;
                        }
                        /* could an 8 bit fixed filler be used instead */
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_3)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 16 bit dynamic filler can be replaced by an 8 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DWORD;
                            item->base.flag |= AUTOGEN_FILLER_1_BYTES_POSSIBLE;
                        }
                        /* could an 8 bit fixed filler be used instead */
                        else if (*alignment == AUTOGEN_ALIGNMENT_ODD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 16 bit dynamic filler can be replaced by an 8 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_WORD_ANY;
                            item->base.flag |= AUTOGEN_FILLER_1_BYTES_POSSIBLE;
                        }
                        /* are fillers needed at all? */
                        else if (*alignment == AUTOGEN_ALIGNMENT_DWORD ||
                            *alignment == AUTOGEN_ALIGNMENT_WORD ||
                            *alignment == AUTOGEN_ALIGNMENT_WORD_ANY)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 16 bit dynamic filler is not needed",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            item->base.flag |= AUTOGEN_FILLER_0_BYTES_POSSIBLE;
                        }
                    }
                    /* align to 24 bits */
                    else if (u_length == 3)
                    {
                        if (*alignment == AUTOGEN_ALIGNMENT_BYTE_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_BYTE_3;
                            item->base.flag |= AUTOGEN_FILLER_0_TO_3_BYTES;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_WORD_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_BYTE_3;
                            item->base.flag |= AUTOGEN_FILLER_1_OR_3_BYTES;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_ODD)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_BYTE_3;
                            item->base.flag |= AUTOGEN_FILLER_0_OR_2_BYTES;
                        }
                        /* could an 8 bit fixed filler be used instead */
                        else if (*alignment == AUTOGEN_ALIGNMENT_WORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 24 bit dynamic filler can be replaced by an 8 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_BYTE_3;
                            item->base.flag |= AUTOGEN_FILLER_1_BYTES_POSSIBLE;
                        }
                        /* could a 16 bit fixed filler be used instead */
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_1)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 24 bit dynamic filler can be replaced by a 16 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_BYTE_3;
                            item->base.flag |= AUTOGEN_FILLER_2_BYTES_POSSIBLE;
                        }
                        /* are fillers needed at all? */
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_3)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 32 bit dynamic filler is not needed",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            item->base.flag |= AUTOGEN_FILLER_0_BYTES_POSSIBLE;
                        }
                        /* could an 24 bit fixed filler be used instead */
                        else if (*alignment == AUTOGEN_ALIGNMENT_DWORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 24 bit dynamic filler can be replaced by a 24 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_BYTE_3;
                            item->base.flag |= AUTOGEN_FILLER_3_BYTES_POSSIBLE;
                        }
                    }
                    /* align to next dword */
                    else if (u_length == 4)
                    {
                        if (*alignment == AUTOGEN_ALIGNMENT_BYTE_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_DWORD;
                            item->base.flag |= AUTOGEN_FILLER_0_TO_3_BYTES;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_WORD_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_DWORD;
                            item->base.flag |= AUTOGEN_FILLER_0_OR_2_BYTES;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_ODD)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_DWORD;
                            item->base.flag |= AUTOGEN_FILLER_1_OR_3_BYTES;
                        }
                        /* could a 16 bit fixed filler be used instead */
                        /* requirement DSEFI015 */
                        else if (*alignment == AUTOGEN_ALIGNMENT_WORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 32 bit dynamic filler can be replaced by a 16 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DWORD;
                            item->base.flag |= AUTOGEN_FILLER_2_BYTES_POSSIBLE;
                        }
                        /* could a 24 bit fixed filler be used instead */
                        /* requirement DSEFI016 */
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_1)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 32 bit dynamic filler can be replaced by a 24 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DWORD;
                            item->base.flag |= AUTOGEN_FILLER_3_BYTES_POSSIBLE;
                        }
                        /* could an 8 bit fixed filler be used instead */
                        /* requirement DSEFI014 */
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_3)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 32 bit dynamic filler can be replaced by an 8 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DWORD;
                            item->base.flag |= AUTOGEN_FILLER_1_BYTES_POSSIBLE;
                        }
                        /* are fillers needed at all? */
                        /* requirement DSEFI017 */
                        else if (*alignment == AUTOGEN_ALIGNMENT_DWORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 32 bit dynamic filler is not needed",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            item->base.flag |= AUTOGEN_FILLER_0_BYTES_POSSIBLE;
                        }
                    }
#if (PMD_FILE_FORMAT >= 600)
                    /* align to next ddword */
                    else if (u_length == 8)
                    {
                        if (*alignment == AUTOGEN_ALIGNMENT_BYTE_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_0_TO_7_BYTES;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_WORD_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_0_OR_2_OR_4_OR_6_BYTES;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_ODD)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_1_OR_3_OR_5_OR_7_BYTES;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_DWORD_ANY)
                        {
                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_0_OR_4_BYTES;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_DWORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler can be replaced by a 32 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_4_BYTES_POSSIBLE;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_1)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler can be replaced by a 56 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_7_BYTES_POSSIBLE;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_WORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler can be replaced by a 48 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_6_BYTES_POSSIBLE;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_3)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler can be replaced by an 40 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_5_BYTES_POSSIBLE;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_DWORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler can be replaced by an 32 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_4_BYTES_POSSIBLE;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_5)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler can be replaced by an 24 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_3_BYTES_POSSIBLE;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_6)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler can be replaced by an 16 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_2_BYTES_POSSIBLE;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_BYTE_7)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler can be replaced by an 8 bit fixed filler",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            *alignment = AUTOGEN_ALIGNMENT_DDWORD;
                            item->base.flag |= AUTOGEN_FILLER_1_BYTES_POSSIBLE;
                        }
                        else if (*alignment == AUTOGEN_ALIGNMENT_DDWORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 7,
                                    "In %s '%s', the 64 bit dynamic filler is not needed",
                                    util_get_obj_type_name((autogen_obj*)seq), util_get_obj_name((autogen_obj*)seq));
                            }

                            item->base.flag |= AUTOGEN_FILLER_0_BYTES_POSSIBLE;
                        }
                    }
#endif
                }
                else if (!(item->base.flag & AUTOGEN_FILLER_IS_REPLACED))
                {
                    check_item_size_alignment(current_file, seq, u_length, *alignment, first_warning);

                    /* update sequence alignment */
                    check_update_alignment(item->agg_n * u_length * u_fact, alignment, TRUE, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
                }
            }
            break;

        case AUTOGEN_ITEM_LST:
            {
                /* requirement DSELI006 */
                if (item->base.flag & AUTOGEN_LST_SBDATA)
                {
#if (PMD_FILE_FORMAT >= 600)
                    if (prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS))
                    {
                        check_item_size_alignment(current_file, seq, 8, *alignment, first_warning);
                    }
                    else
#endif
                    check_item_size_alignment(current_file, seq, 4, *alignment, first_warning);
                }
                else
                {
                    /* if FTD or PPC ID's, check that list is word aligned */
                    if (item->base.flag & (AUTOGEN_LST_FTD | AUTOGEN_LST_PPC | AUTOGEN_LST_SOS_FTD))
                    {
                        check_item_size_alignment(current_file, seq, 2, *alignment, first_warning);

                        /* set new sequence alignment to any words */
                        *alignment = AUTOGEN_ALIGNMENT_WORD_ANY;
                    }
                    /* else determine list alignment requirement from resource 
                       sub block types 
                    */
                    else if (item->base.flag & AUTOGEN_LST_SB_HAVE_BYTE_IDS)
                    {
                        check_item_size_alignment(current_file, seq, 1, *alignment, first_warning);

                        /* set new sequence alignment to any */
                        *alignment = AUTOGEN_ALIGNMENT_BYTE_ANY;
                    }
                    else
                    {
                        check_item_size_alignment(current_file, seq, 2, *alignment, first_warning);

                        /* set new sequence alignment to any words */
                        *alignment = AUTOGEN_ALIGNMENT_WORD_ANY;
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_STRING:
            {
                autogen_item_string* item_str = (autogen_item_string*)item;

                if (item->base.flag & AUTOGEN_STRING_UNICODE)
                {
                    check_item_size_alignment(current_file, seq, 2, *alignment, first_warning);
                }

                /* update sequence alignment */
                if (item->agg_type == AGG_TYPE_FIXED_SINGLE ||
                    item->agg_type == AGG_TYPE_FIXED_MULTIPLE)
                {
                    unsigned int item_size = (unsigned int)item->agg_n * (unsigned int)item_str->length;

                    if (item->base.flag & AUTOGEN_STRING_UNICODE)
                    {
                        item_size *= 2; 
                    }

                    check_update_alignment(item_size, alignment, TRUE, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
                }
                else
                {
                    if (item->base.flag & AUTOGEN_STRING_UNICODE)
                    {
                        check_update_alignment(2, alignment, FALSE, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
                    }
                    else
                    {
                        check_update_alignment(1, alignment, FALSE, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_STRUCT:
            {
                autogen_item_struct* item_struct = (autogen_item_struct*)item;

                unsigned int first_seq_alignment = AUTOGEN_ALIGNMENT_UNDEFINED;

                autogen_it seq_it = INIT_ITERATOR;
                autogen_seq* str;

#if (PMD_FILE_FORMAT >= 600)
                if (prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS))
                {
                    check_item_size_alignment(current_file, seq, 8, *alignment, first_warning);
                }
                else
#endif
                check_item_size_alignment(current_file, seq, 4, *alignment, first_warning);

                /* update sequence alignment */
                seq_it.typemask  = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB;
                seq_it.obj.name  = item_struct->seqname;
                seq_it.vercrit   = AUTOGEN_OBJ_VERSION_OVERLAP;
                seq_it.ver       = ver;

                str = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &item->seq->base.res->seq_list);
                while (str)
                {
                    unsigned int seq_alignment = check_seq_alignment(current_file, str, ver);
                    str->alignment = util_get_resulting_alignment(str->alignment, seq_alignment, prop_has((autogen_obj*)str->base.res, PROPERTY_ALIGNMENT_64_BITS));

                    if (first_seq_alignment == AUTOGEN_ALIGNMENT_UNDEFINED)
                    {
                        first_seq_alignment = seq_alignment;
                        *alignment          = seq_alignment;
                    }

                    /* check that the sequence has a length divisible by 4 bytes,
                    if it is inserted several times 
                    */
                    /* requirement DSEAR005, DSEAR104 */
#if (PMD_FILE_FORMAT >= 600)
                    if (prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS))
                    {
                        if (item->agg_type != AGG_TYPE_FIXED_SINGLE && str->alignment != AUTOGEN_ALIGNMENT_DDWORD)
                        {
                            if (alignment_check_enabled)
                            {
                                util_error_line(current_file, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 7,
                                    "The %s '%s' is inserted several times, but doesn't have a length divisible by 8",
                                    util_get_obj_type_name((autogen_obj*)str), util_get_obj_name((autogen_obj*)str));
                            }
                        }
                    }
                    else
#endif
                    if (item->agg_type != AGG_TYPE_FIXED_SINGLE && str->alignment != AUTOGEN_ALIGNMENT_DWORD)
                    {
                        if (alignment_check_enabled)
                        {
                            util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 7,
                                "The %s '%s' is inserted several times, but doesn't have a length divisible by 4",
                                util_get_obj_type_name((autogen_obj*)str), util_get_obj_name((autogen_obj*)str));
                        }
                    }

                    str = (autogen_seq*)autogen_obj_find_next_in_list(&seq_it);
                }
            }
            break;

        case AUTOGEN_ITEM_TRCSTRUCTURE:
            {
                check_item_size_alignment(current_file, seq, 1, *alignment, first_warning);

                check_update_alignment(1, alignment, FALSE, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
            }
            break;

        case AUTOGEN_ITEM_CHOICE:
            {
                unsigned int init_alignment = *alignment;
                unsigned int case_alignment = AUTOGEN_ALIGNMENT_UNDEFINED;
                autogen_it case_it = INIT_ITERATOR;
                autogen_obj* case_item;

                case_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
                case_it.ver     = ver;

                case_item = autogen_obj_find_in_list(&case_it, &item->base.child_list);
                while (case_item)
                {
                    unsigned int new_alignment = init_alignment;

                    check_seq_alignment_from_list(current_file, seq, &case_item->child_list, ver, &new_alignment, first_warning);

                    case_alignment = util_get_resulting_alignment(case_alignment, new_alignment, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));

                    case_item = autogen_obj_find_next_in_list(&case_it);
                }

                /* default case */
                case_item = (autogen_obj*)((autogen_item_choice*)item)->default_case;
                if (case_item)
                {
                    unsigned int new_alignment = init_alignment;

                    check_seq_alignment_from_list(current_file, seq, &case_item->child_list, ver, &new_alignment, first_warning);

                    *alignment = new_alignment;
                }

                *alignment = util_get_resulting_alignment(*alignment, case_alignment, prop_has((autogen_obj*)seq->base.res, PROPERTY_ALIGNMENT_64_BITS));
            }
            break;

        case AUTOGEN_ITEM_RANGE_ENTRY:
            {
            }
            break;

        default:
            {
                util_error_line(current_file, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Default case met in check_seq_alignment_from_list(). "
                    "item->base.subtype is 0x%8.8X",
                    item->base.subtype);
            }
            break;
        }

        item = (autogen_item*)item->base.next;
    }
}

#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

LOCAL void check_recursion_seq(const char* current_file, autogen_seq* seq,  autogen_res* res, const autogen_ver* ver,
                               const autogen_seq *sequences[], int num_sequences, int max_sequences)
{
   /* Check that we're not currently looking at this sequence, and push this sequence */
    if (num_sequences >= max_sequences)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "Unable to perform full recursion check due to an internal limit.");
    }
    else
    {
        int cnt;
        for (cnt = 0; cnt<num_sequences; cnt++)
        {
            if (sequences[cnt] == seq)
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                    "Recursive reference involving '%s'", seq->base.name);
            }
        }
        sequences[num_sequences] = seq;
    }
    num_sequences++;

    /* Check the item list */
    check_recursion_item_list(current_file, &seq->base.child_list, res, ver, sequences, num_sequences, max_sequences);

    /* Pop this sequence */
    num_sequences--;
}


LOCAL void check_recursion_item_list(const char* current_file, autogen_obj_list* obj_list, autogen_res* res, const autogen_ver* ver, const autogen_seq *sequences[], int num_sequences, int max_sequences)
{
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        if (item->base.subtype == AUTOGEN_ITEM_LST && (item->base.flag & AUTOGEN_LST_SBDATA))
        {
            /* It's a sub block list. Check each sub block */
            autogen_obj* ref;
            for (ref = autogen_obj_get_first_in_list(&item->base.child_list); ref != NULL; ref = ref->next)
            {
                check_recursion_seq(current_file, ((autogen_seq_ref*)ref)->seqptr, res, ver, sequences, num_sequences, max_sequences);
            }
        }
        else if (item->base.subtype == AUTOGEN_ITEM_STRUCT)
        {
            /* It's a structure. Check it. */
            autogen_item_struct* item_struct = (autogen_item_struct*)item;

            /* Look up the sequence in the parent sequence's resource */
            autogen_obj* str;
            autogen_it str_it = INIT_ITERATOR;

            /* Find definitions of structure in the resource */
            str_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
            str_it.obj.name = item_struct->seqname;
            str_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            str_it.ver      = ver;

            str = autogen_obj_find_in_list(&str_it, &res->seq_list);
            while (str)
            {
                check_recursion_seq(current_file, (autogen_seq *) str, res, ver, sequences, num_sequences, max_sequences);

                str = autogen_obj_find_next_in_list(&str_it);
            }
        }
        else if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
        {
            autogen_item_choice* item_choice = (autogen_item_choice*)item;

            check_recursion_item_list(current_file, &item_choice->base.base.child_list, res, ver, sequences, num_sequences, max_sequences);

            if (item_choice->default_case)
            {
                check_recursion_item_list(current_file, &item_choice->default_case->base.base.child_list, res, ver, sequences, num_sequences, max_sequences);
            }
        }
        else if (item->base.subtype == AUTOGEN_ITEM_CASE)
        {
            check_recursion_item_list(current_file, &item->base.child_list, res, ver, sequences, num_sequences, max_sequences);
        }

        /* Move to the next item in the list */
        item = (autogen_item*)item->base.next;
    }
}

/*  End of file autogen_check.c  */
