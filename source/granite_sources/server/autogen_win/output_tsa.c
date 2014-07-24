/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_tsa.c
                ------------
                SW Include






Project:          autogen

%name:            output_tsa.c %
%version:         co1tss#74 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Nov 22 10:31:49 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file contains the TSS Server API file generation code
*/

/*  TODO:
    Consider skipping of resource prefix (e.g. TONE prefix on SRVTONE server)
    Generate check for encoding non-empty sub block containers for sub block versions not
            including the actual message version
    Generate encode+decode check that the actual version of structures is within the limits
            for the structure
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_ref.h"
#include "autogen_util.h"
#include "autogen_object.h"
#include "autogen_prop.h"
#include "pmd_heap.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL static
#endif /* LOCAL */

typedef struct t_tsa_parameter
    {
    struct t_tsa_parameter* next;
    const char* varname;
    const char* parname;
    const char* reftypename;
    const char* valtypename;
    const char* initvalue;
    const char* comment;
    const autogen_item *item;
    const autogen_seq *seq;
    } tsa_parameter;

static const char hresult_typename[] = "HRESULT";
#if (PMD_FILE_FORMAT >= 600)
static const char ulonglong_typename[] = "unsigned long long";
#endif
static const char ulong_typename[] = "unsigned long";
static const char ushort_typename[] = "unsigned short";
static const char uchar_typename[] = "unsigned char";
#if (PMD_FILE_FORMAT >= 600)
static const char longlong_typename[] = "long long"; 
#endif
static const char long_typename[] = "long";
static const char short_typename[] = "short";
static const char char_typename[] = "signed char";
static const char string_typename[] = "std::wstring";
static const char size_t_typename[] = "size_t";
static const char byte_array_typename[] = "std::vector<unsigned char>";
static const char idlist_typename[] = "unsigned long"; /* Note: It's the type of the element IDs */
static const char shared_namespace_suffix[] = "Shared";
static const char tsa_namespace[] = "Tss::ServerApi";

static const char base_indent_string[] = "";
static const unsigned int base_indent = sizeof(base_indent_string) - 1;
static const unsigned int line_width = 77;
static const unsigned int indent_step = 4;

static const unsigned int tsa_not_request_mask =
        AUTOGEN_MSG_RESP | AUTOGEN_MSG_IND | AUTOGEN_MSG_NTF | AUTOGEN_MSG_TRC;


static char s_res_prefix[AUTOGEN_MAX_NAME_LENGTH];
static char s_res_namespace[AUTOGEN_MAX_NAME_LENGTH+10];
static char s_classname[AUTOGEN_MAX_NAME_LENGTH];
static char s_scoped_classname[AUTOGEN_MAX_NAME_LENGTH*2+2];
static autogen_res *s_current_res = NULL;

static char s_constname_versioned[AUTOGEN_MAX_NAME_LENGTH+17];
static char s_version_suffix[17];

#define TSA_NAMESPACE_SHARED  0x00000001
#define TSA_NAMESPACE_SUBMSG  0x00000002
#define TSA_NAMESPACE_ALWAYS  0x00000004
#define TSA_C_PREFIX          0x00000008
#define TSA_VEC_PREFIX        0x00000010
#define TSA_VERSION_SUFFIX    0x00000020

/*------------------------------------------------------------------------------------------------

    Name: tsa_name
 
    Purpose: Returns a name in TSS API style from the given name, skipping any given prefix.
 
    Functional Description:
        tsa_name changes the Unix style (lowercase with underscores) name given to a TSS
        API style name (mixed case without underscores). If a prefix is given, and the name
        starts with that prefix, it is stripped from the resulting name.

    Arguments: 
        name - [in] The name get the TSS API style name for.
        prefix - [in] Any prefix that should be stripped from the given name. May be NULL.

    Return Values: A pointer to a static buffer containing the name.

------------------------------------------------------------------------------------------------*/

LOCAL char* tsa_name(const char* name, char* prefix)
    {
    static char tsa_str_name[256];

    unsigned int i;
    unsigned int index = 0;

    int uppercase = TRUE;

    for (i = 0; i <= strlen(name); i++)
        {
        if (name[i] == '_' || name[i] == ' ')
            {
            uppercase = TRUE;
            }
        else
        if (name[i] == '+')
        {
            static const char plus_text[] = "Plus";
            memcpy(tsa_str_name+index, plus_text, sizeof(plus_text)-1);
            index += sizeof(plus_text)-1;
            uppercase = TRUE;
        }
        else
        if (name[i] == '-')
        {
            static const char minus_text[] = "Minus";
            memcpy(tsa_str_name+index, minus_text, sizeof(minus_text)-1);
            index += sizeof(minus_text)-1;
            uppercase = TRUE;
        }
        else
        if (!isalnum(name[i]))
            {
            /* Just skip the character */
            }
        else
        if (uppercase)
            {
            tsa_str_name[index++] = (char)toupper(name[i]);
            uppercase = FALSE;
            }
        else
            {
            tsa_str_name[index++] = (char)tolower(name[i]);
            }
        }

    tsa_str_name[index] = 0;

    if (prefix && !strncmp(tsa_str_name, prefix, strlen(prefix)))
        {
        return &tsa_str_name[strlen(prefix)];
        }

    return tsa_str_name;
    }



/*------------------------------------------------------------------------------------------------

    Name: tsa_is_item_aggregated
 
    Purpose: Checks whether the given item is aggregated.
 
    Functional Description:
        tsa_is_item_aggregated returns TRUE if the given item is aggregated, FALSE otherwise.
        Fillers and strings are always considered non-aggregated in TSA generation.

    Arguments: 
        item - [in] The item to check.

    Return Values: TRUE if the item is aggregated, FALSE otherwise.

------------------------------------------------------------------------------------------------*/

LOCAL int tsa_is_item_aggregated(const autogen_item *item)
    {
    return item->agg_type != AGG_TYPE_FIXED_SINGLE &&
           item->base.subtype != AUTOGEN_ITEM_STRING &&
           item->base.subtype != AUTOGEN_ITEM_FILLER;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_is_parameter_aggregated
 
    Purpose: Checks whether the given parameter is aggregated.
 
    Functional Description:
        tsa_is_parameter_aggregated returns TRUE if the given parameter is aggregated,
        FALSE otherwise. Fillers and strings are always considered non-aggregated in
        TSA generation.

    Arguments: 
        parameter - [in] The parameter to check.

    Return Values: TRUE if the parameter is aggregated, FALSE otherwise.

------------------------------------------------------------------------------------------------*/

LOCAL int tsa_is_parameter_aggregated(const tsa_parameter *parameter)
    {
    return tsa_is_item_aggregated(parameter->item);
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_item_varname
 
    Purpose: Constructs a TSA varname from the varname of the given item.
 
    Functional Description:
        tsa_item_varname builds a TSA name from the given varname, and
        adds a type prefix depending on the type of item. No m_ prefix
        is added.

    Arguments: 
        item - [in] The item to retrieve the varname for.

    Return Values: Pointer to the name in a static buffer.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_item_varname(const autogen_item *item)
    {
    static char tsa_str_varname[AUTOGEN_MAX_NAME_LENGTH+20];
    const char *prefix = "";

    if (tsa_is_item_aggregated(item))
        {
        prefix = "vec";
        }
    else
        {
        switch (item->base.subtype)
            {
            case AUTOGEN_ITEM_VALUE:
                {
                if (item->length < 0)
                    {
                    prefix = "l";
                    }
                else
                    {
                    prefix = "ul";
                    }
                }
                break;

            case AUTOGEN_ITEM_STRING:
                prefix = "ws";
                break;

            case AUTOGEN_ITEM_LST:
                prefix = "vec";
                break;

            case AUTOGEN_ITEM_STRUCT:
                /* Keep default prefix of none */
                break;

            case AUTOGEN_ITEM_POINTER:
                prefix = "ul";
                break;

            default:
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Default met in tsa_item_varname. item->base.subtype is 0x%08X", item->base.subtype);
                break;
            }
        }

    strcpy(tsa_str_varname, prefix);
    strcat(tsa_str_varname, tsa_name(item->varname, NULL));
    return tsa_str_varname;
    }
    
/*------------------------------------------------------------------------------------------------
    Name: is_versioned
    
    Purpose: Helper function for format_version_suffix()
    
    Functional Description: Checks whether or not an object has a version different from
                            000.000 to max version

    Arguments: Object to be checked.

    Return Value: Boolean
    TRUE if object has a version different from 000.000 to max version
    FALSE if object is not versioned
    
  ------------------------------------------------------------------------------------------------*/
LOCAL int is_versioned (autogen_obj *obj)
{
    if ((obj->ver.from[0] == 0) && (obj->ver.from[1] == 0) && (obj->ver.to[0] == 256))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
    
/*------------------------------------------------------------------------------------------------
    Name: format_version_suffix
    
    Purpose: Make names of versioned constants unique
    
    Functional Description: Adds version suffix to object name

    Arguments: Object to have name formatted (added version suffix to it)

    Return Value: Formatted name returned in s_version_suffix
    
  ------------------------------------------------------------------------------------------------*/
LOCAL void format_version_suffix(autogen_obj *obj)
    {
    memset(s_constname_versioned, '\0', sizeof(s_constname_versioned));
    memset(s_version_suffix, '\0', 17);
    sprintf(s_constname_versioned,"%s", obj->name);

    /* special handling in case of derived table */
    if ((obj->type == AUTOGEN_OBJ_TBLENTRY) && ((obj->subtype == AUTOGEN_TBLENTRY_DERCONST) || (obj->subtype == AUTOGEN_TBLENTRY_DERBIT)))
    {
        autogen_obj* entry;
        autogen_it entry_it = INIT_ITERATOR;

        /* Find entry */
        entry_it.typemask  = AUTOGEN_OBJ_TBLENTRY;
        entry_it.obj.name  = obj->name;
        
        entry = autogen_obj_find_in_list(&entry_it, &obj->parent->base_obj->child_list);
        if (entry)
        {
            if (is_versioned(entry))
            {
                if (entry->ver.to[0] == 256) /* to version is "", dont add */
                {
                    sprintf(s_version_suffix, "_%03hd_%03hd", entry->ver.from[0], entry->ver.from[1]);
                }
                else
                {
                    sprintf(s_version_suffix, "_%03hd_%03hd_%03hd_%03hd", entry->ver.from[0], entry->ver.from[1], entry->ver.to[0], entry->ver.to[1]);
                }
                strcat(s_constname_versioned, s_version_suffix);
            }
        }
    }
    else if (is_versioned(obj))
        {
        if (obj->ver.to[0] == 256) /* to version is "", dont add */
        {
            sprintf(s_version_suffix, "_%03hd_%03hd", obj->ver.from[0], obj->ver.from[1]);
        }
        else
        {
            sprintf(s_version_suffix, "_%03hd_%03hd_%03hd_%03hd", obj->ver.from[0], obj->ver.from[1], obj->ver.to[0], obj->ver.to[1]);
        }
        strcat(s_constname_versioned, s_version_suffix);
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_initname
 
    Purpose: Constructs a TSA name for initialisation variable for the given parameter.
 
    Functional Description:
        tsa_initname builds a TSA name for a boolean corresponsing to the given parameter,
        including an m_ prefix. This function returns NULL for parameters not needing
        initialisation variables, such as simple items with a default value, or arrays.

    Arguments: 
        par - [in] The parameter to retrieve the initialisation variable name for.

    Return Values: Pointer to the name in a static buffer, or NULL.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_initname(const tsa_parameter *par)
    {
    static char tsa_str_initname[AUTOGEN_MAX_NAME_LENGTH+50];

    /* Format name of variable */
    sprintf(tsa_str_initname, "m_b%sInitialized", tsa_name(par->item->varname, NULL));

    /* Check if it's a structure existing in different versions */
    if ((par->item->base.subtype & AUTOGEN_ITEM_STRUCT))
        {
        const autogen_item_struct *item_struct = (const autogen_item_struct *) par->item;
        int has_multiple = FALSE;

        /* Look up the sequence in the parent sequence's resource */
        autogen_it str_it = INIT_ITERATOR;
        autogen_obj *str = NULL;

        /* Find definitions of structure in the resource */
        str_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
        str_it.obj.name = item_struct->seqname;

        str = autogen_obj_find_in_list(&str_it, &par->item->seq->base.res->seq_list);
        if (str != NULL && autogen_obj_find_next_in_list(&str_it))
            {
            has_multiple = TRUE;
            }

        /* Append version suffix */
        if (has_multiple)
            {
            unsigned short firstver=0, lastver=0;
            unsigned int parnamelen = strlen(par->parname);
            if (parnamelen > 8)
                {
                const char *suffix = par->parname+parnamelen-8;
                if (sscanf(suffix, "_%03hd_%03hd", &firstver, &lastver) == 2)
                    {
                    strcat(tsa_str_initname, suffix);
                    }
                }
            else
                {
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Structure exists in multiple versions, but structure parameter doesn't. "
                    "The generated code may not compile.");
                }
            }
        }

    return tsa_str_initname;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_classname
 
    Purpose: Creates a name for the class corresponding to the given sequence.
 
    Functional Description:
        tsa_classname creates a name with the following components:
        
            [<namespace>::][<basemessage>::][<prefix>]<name>[<version>]

        The namespace qualifier depends on the resource associated with the object.
        The basemessage qualifier depends on the base message name for submessages.
        The version suffix depends on the version of the object compared to that
        of other versions of the same object and of the associated resource.
        The prefix depends on the flags given. The following flags control which
        parts of the name are present:

            TSA_NAMESPACE_SHARED - Includes namespace qualifier only for shared objects.
            TSA_NAMESPACE_SUBMSG - Includes namespace qualifier for submessages.
            TSA_NAMESPACE_ALWAYS - Always includes namespace and any submessage qualifier.
            TSA_C_PREFIX         - Includes "C" (without quotes) in front of the class name.
            TSA_VEC_PREFIX       - Includes "vec" (without quotes) in front of the class name.
            TSA_VERSION_SUFFIX   - Includes a version suffix if multiple versions exist.

        The base message qualifier is never included for messages that are not submessages,
        or when the resource flag for unique submessages is set. The version suffix is never
        included when there are no other versions of the same object.

    Arguments: 
        seq - [in] The object to create a name for.
        flags - [in] Flags as described above.

    Return Values: Pointer to a statically allocated buffer.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_classname(const autogen_seq *seq, int flags)
    {
    static char tsa_str_classname[AUTOGEN_MAX_NAME_LENGTH*3+20];
    int is_submessage = (seq->base.type == AUTOGEN_OBJ_MSG) &&
                        (seq->base.flag & AUTOGEN_MSG_IS_SUBMSG);

    /* Determine whether we're on another (shared) resource */
    char *prefix = s_res_prefix;
    const autogen_res *resource = seq->base.res;
    if (!resource)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Unable to find resource for sequence");
        }
    if (resource->base.subtype == RESOURCE_ISI_COMMON_MESSAGES)
        {
        /* We're on the common messages resource. Treat as the current resource */
        resource = s_current_res;
        }
    if (resource != s_current_res)
        {
        /* We're on a shared resource. Create a new prefix */
        static char res_prefix[AUTOGEN_MAX_NAME_LENGTH];
        strcpy(res_prefix, tsa_name(resource->resnameshort_l, NULL));
        prefix = res_prefix;
        }

    /* Build any resource namespace qualifier */
    tsa_str_classname[0] = 0;
    if ( (((flags & TSA_NAMESPACE_ALWAYS) ||
          (flags & TSA_NAMESPACE_SHARED) && resource != s_current_res))
          ||
          ((flags & TSA_NAMESPACE_SHARED) && (resource->base.subtype & RESOURCE_SHARED))) /* or if the res is shared.... */
        {
        sprintf(tsa_str_classname, "%s::%s", tsa_namespace, prefix);
        if ((resource != s_current_res &&
            (resource->base.subtype & RESOURCE_SHARED))
            ||
            ((resource->base.subtype & RESOURCE_SHARED))) /* or if the res is shared.... */
            {
            strcat(tsa_str_classname, shared_namespace_suffix);
            }
        strcat(tsa_str_classname, "::");
        }

    /* Build submessage namespace qualifier */
    if (is_submessage &&
        (flags & (TSA_NAMESPACE_SUBMSG | TSA_NAMESPACE_ALWAYS)) &&
        !prop_has((autogen_obj*)seq->base.res, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
        {
        strcat(tsa_str_classname, tsa_name(seq->base.base_obj->name, prefix));
        strcat(tsa_str_classname, "::");
        }

    /* Write the class name with prefix and a check for submessages */
    if (flags & TSA_VEC_PREFIX)
        {
        strcat(tsa_str_classname, "vec");
        }
    if (flags & TSA_C_PREFIX)
        {
        strcat(tsa_str_classname, "C");
        }

    strcat(tsa_str_classname, tsa_name(seq->base.name, prefix));

    /* Write version suffix */
        if ((flags & TSA_VERSION_SUFFIX) &&                     /*If version suffix is requested, and */
            
            ((util_has_multiple_versions(&seq->base)) ||        /*either the object has multible versions, or */
            
             ((seq->base.res->base.subtype == RESOURCE_ISI_SHARED) &&
              ((seq->base.ver.from[0] != 0) || /* the object is in a shred resource, and has version diffrerent from 0 */
               (seq->base.ver.from[1] != 0) ))))
        {
            if(seq->base.ver.to[0] == 256)/* to version is "", dont add */
            {
                sprintf(tsa_str_classname+strlen(tsa_str_classname), "_%03hd_%03hd",
                    seq->base.ver.from[0], seq->base.ver.from[1]);
            }
            else
            {
                sprintf(tsa_str_classname+strlen(tsa_str_classname), "_%03hd_%03hd_%03hd_%03hd",
                    seq->base.ver.from[0], seq->base.ver.from[1], seq->base.ver.to[0], seq->base.ver.to[1]);
            }
        }

    return tsa_str_classname;
    }


LOCAL char *tsa_struct_name(const autogen_item_struct *item_struct,
                            const autogen_seq *seq,
                            int is_parname)
    {
    static char name_result[AUTOGEN_MAX_NAME_LENGTH + 20];
    const char *name = is_parname ? item_struct->base.parname : item_struct->base.varname;

    /* Handle initialisation and "vec" prefix */
    name_result[0] = 0;
    if (tsa_is_item_aggregated(&item_struct->base) && !is_parname)
        {
        strcat(name_result, "vec");
        }

    /* Handle the name itself */
    strcat(name_result, tsa_name(name, NULL));

    /* Handle the version suffix */
    if (util_has_multiple_versions(&seq->base))
        {
        sprintf(name_result+strlen(name_result), "_%03hd_%03hd",
                seq->base.ver.from[0], seq->base.ver.from[1]);
        }

    return name_result;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_space_after_typename
 
    Purpose: Returns the empty string or a single space, depending on the given type name
 
    Functional Description:
        tsa_space_after_typename checks the given type name. If the name ends with a '&',
        this function returns the empty string. Otherwise, this function returns a string
        with a single space. The purpose is to allow callers to only include a space where
        it's necessary for correct tokenisation.

    Arguments: 
        type - [in] The name of the type. May be NULL.

    Return Values:
        A constant string, either "" or " ". Must not be freed.

------------------------------------------------------------------------------------------------*/

LOCAL const char *tsa_space_after_typename(const char *type)
    {
    /* If the last character is a reference symbol, we don't need a space */
    if (type && *type && type[strlen(type)-1] == '&')
        {
        return "";
        }

    /* If it's not a reference, we should add a space after the typename */
    /* In cases where this is not needed, this function should not be called at all. */
    return " ";
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_heading
 
    Purpose: Writes a heading-style comment with the given text.
 
    Functional Description:
        tsa_write_heading formats a comment with additional lines surrounding it in order
        to emphasize it. It then writes the comment to the given stream, indented with
        the given number of spaces.

    Arguments: 
        f - [in,out] Stream pointer to write the heading to.
        indent - [in] The number of spaces to indent the heading.
        heading - [in] The text to use in the heading.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_heading(FILE *f, unsigned int indent, const char *heading)
    {
    const char *indent_string = util_get_spaces(indent);
    const char *hyphen_string = util_get_hyphens(line_width - indent - 3);
    fprintf(f, "%s// %s\n", indent_string, hyphen_string);
    fprintf(f, "%s// %s\n", indent_string, heading);
    fprintf(f, "%s// %s\n", indent_string, hyphen_string);
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_format_comment
 
    Purpose: Formats the given comment list suitably for TSA
 
    Functional Description:
        tsa_format_comment formats the given comment using the given indent and
        single-line comment tokens.

    Arguments: 
        indent - [in] The number of spaces to indent the comment tokens.
        list - [in] The comment list to format.

    Return Values: A pointer to text allocated on the PMD heap.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_format_comment(unsigned int indent, const autogen_cmt* list)
    {
    /* Various formatting calculations */
    static const char comment[] = "// ";
    const unsigned int line_len = line_width - indent - sizeof(comment)-1;
    char line_prefix[100];
    char *formatted = NULL;
    char *unformatted = NULL;

    strcpy(line_prefix, util_get_spaces(indent+base_indent));
    strcat(line_prefix, comment);

    /* Build unformatted text */
    /* If we add a comment type for TSS API, this line must be changed */
    unformatted = util_build_unformatted_comment(list, COMMENT_PROPERTY_ALL_OUTPUTS);
    if (!*unformatted)
        {
        /* Just return the empty string if the comment is empty */
        return "";
        }

    /* Do word wrapping and add comment symbols */
    formatted = util_wrap_words(unformatted, line_len, line_prefix, line_prefix, "\n");
    return formatted;
    }

/*------------------------------------------------------------------------------------------------

    Name: tsa_fill_par_names
 
    Purpose: Fills in the varname and parname fields of the given tsa_parameter struct
 
    Functional Description:
        tsa_fill_par_names sets the varname and parname fields to the corresponsing TSA
        names allocated on the PMD heap.

    Arguments: 
        parameter - [in] The parameter structure to fill out the two names for.
        item - [in] Item whose names to use.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_fill_par_names(tsa_parameter *parameter,
                              const autogen_item *item)
    {
    parameter->varname = pmd_heap_strdup(tsa_item_varname(item));
    parameter->parname = pmd_heap_strdup(tsa_name(item->varname, NULL));
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_fill_par_numeric_type
 
    Purpose: Fills typename and initial value fields for value items.
 
    Functional Description:
        tsa_fill_par_numeric_type fills in the valtypename, reftypename and initvalue fields
        of the given tsa_parameter struct for plain, numeric items.

    Arguments: 
        parameter - [in] The parameter structure to fill out the three fields for.
        item - [in] Item that the parameter is based on.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_fill_par_numeric_type(tsa_parameter *parameter,
                                     autogen_item_value *item)
    {
    /* Check sign */
    if (item->base.length < 0)
        {
        parameter->valtypename = long_typename;
        }
    else
        {
        parameter->valtypename = ulong_typename;
        }

    /* Since it's a built-in type, just use the value type for const reference */
    parameter->reftypename = parameter->valtypename;

    /* Check for any default value */
    if (prop_has_valid_string((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE))
    {
        /* Are we dealing with a value_const entry... */
        if (item->pres.tblname)
        {
            /* ... then find entry in table - to get version info */
            autogen_it tbl_it   = INIT_ITERATOR;
            autogen_tbl *tbl    = NULL;
            autogen_res *res    = NULL;

            tbl_it.typemask  = AUTOGEN_OBJ_TBL;
            tbl_it.obj.name  = item->pres.tblname;
            tbl_it.vercrit   = AUTOGEN_OBJ_VERSION_FIRST;
            
            res = item->base.seq->base.res;

            tbl = (autogen_tbl *)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
            if (tbl)
            {
                autogen_obj* entry;
                autogen_it entry_it = INIT_ITERATOR;

                entry_it.typemask  = AUTOGEN_OBJ_TBLENTRY;
                entry_it.obj.name  = prop_get_string((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE);
                
                entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
                if (entry)
                {
                    format_version_suffix(entry);
                    parameter->initvalue = pmd_heap_strdup(s_constname_versioned); /* constant now has versioning appended if needed */
                }
            }
        }
        else
        {
            parameter->initvalue = prop_get_string((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE);
        }
    }
    else
    if (prop_has_value((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE))
        {
        char default_value[20];
#if (PMD_FILE_FORMAT >= 600)
        sprintf(default_value, "%llu", prop_get_value((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE));
#else
        sprintf(default_value, "%u", prop_get_value((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE));
#endif
        parameter->initvalue = pmd_heap_strdup(default_value);
        }
    else
        {
        parameter->initvalue = NULL;
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_fill_par_enum_type
 
    Purpose: Fills typename and initial value fields for constant table items.
 
    Functional Description:
        tsa_fill_par_enum_type fills in the valtypename, reftypename and initvalue
        fields of the given tsa_parameter struct for constant table values and references.

    Arguments: 
        parameter - [in] The parameter structure to fill out the three fields for.
        item - [in] Item that the parameter is based on.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_fill_par_enum_type(tsa_parameter *parameter,
                                  autogen_item_value *item)
    {
    autogen_it tbl_it = INIT_ITERATOR;
    autogen_tbl *tbl  = NULL;
    autogen_res *res  = NULL;
    autogen_obj *parent = item->base.base.parent;

    /* Fill in values for numeric fields. Initialiser will be overwritten later, */
    /* unless an error occurs */
    tsa_fill_par_numeric_type(parameter, item);

    /* Check whether we have a default value. */
    if (prop_has((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE))
        {
        /* If we have an explicit default value, don't look for other possibilities */
        return;
        }

    /* Retrieve resource object */
    while (parent->type & AUTOGEN_OBJ_ITEM &&
           parent->subtype & ((AUTOGEN_ITEM_MERGE | AUTOGEN_ITEM_CASE | AUTOGEN_ITEM_CHOICE)))
        {
        parent = parent->parent;
        }
    if (!(parent->type & (AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_MSG)))
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "Unknown parent type in tsa_fill_enum_par(). "
            "parent->type is 0x%08X, parent->subtype is 0x%08X",
            parent->type, parent->subtype);
        return;
        }
    res = ((autogen_seq *) parent)->base.res;

    /* Search for the appropriate constant table */
    tbl_it.typemask   = AUTOGEN_OBJ_TBL;
    tbl_it.obj.name   = item->pres.tblname;
    tbl_it.ver        = &item->base.base.ver;
    tbl_it.vercrit    = AUTOGEN_OBJ_VERSION_OVERLAP;

    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
    /* Check that the corresponding constant table exists */
    if (!tbl)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "No constant table for enumerated parameter %s in tsa_fill_enum_par(). item->base.subtype is 0x%08X",
            item->base.base.name, item->base.base.subtype);
        return;
        }

    /* Check that there are any constant table entries */
    if (tbl->base.child_list.n_obj == 0)
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
            "No constant table entries for enumerated parameter %s in tsa_fill_enum_par()",
            item->base.base.name);
        return;
        }

    /* Use the first value as an initialiser */
        { /*lint !e539   Did not expect positive indentation from the if above */
        autogen_it entry_it = INIT_ITERATOR;
        autogen_obj *entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
        
        format_version_suffix(entry);
        parameter->initvalue = pmd_heap_strdup(s_constname_versioned); /* constant now has versioning appended if needed */
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_create_single_parameter
 
    Purpose: Creates a tsa_parameter structure without adding it to any list.
 
    Functional Description:
        tsa_create_single_parameter initializes a tsa_parameter structure on the PMD heap, and fills
        the seq, comment and item elements. The comment is formatted and allocated on the PMD
        heap, the other fields are simply taken from the arguments. The new structure is then
        inserted after the element pointed to by the last pointer, and that pointer is then
        updated to point to the new element. Finally, the new element is returned.

    Arguments: 
        item - [in] The item to create a parameter for.

    Return Values: A pointer to the new element.

------------------------------------------------------------------------------------------------*/

tsa_parameter *tsa_create_single_parameter(const autogen_seq *seq,
                                           const autogen_item *item)
    {
    tsa_parameter *result = pmd_heap_alloc(sizeof(tsa_parameter));
    result->seq = seq;
    result->comment = pmd_heap_strdup(tsa_format_comment(indent_step, item->base.cmt_list));
    result->item = item;
    return result;
    }

/*------------------------------------------------------------------------------------------------

    Name: tsa_create_parameter
 
    Purpose: Creates a tsa_parameter structure and adds it after the given list element.
 
    Functional Description:
        tsa_create_parameter allocates a tsa_parameter structure on the PMD heap, and fills
        the seq, comment and item elements. The comment is formatted and allocated on the PMD
        heap, the other fields are simply taken from the arguments. The new structure is then
        inserted after the element pointed to by the last pointer, and that pointer is then
        updated to point to the new element. Finally, the new element is returned.

    Arguments: 
        seq - [in] The top-level sequence (class) that this item is in.
        item - [in] The item to create a parameter for.
        last - [in,out] Pointer to a pointer to the last element in the list.

    Return Values: A pointer to the new element.

------------------------------------------------------------------------------------------------*/

tsa_parameter *tsa_create_parameter(const autogen_seq *seq,
                                    const autogen_item *item,
                                    tsa_parameter **last)
    {
    tsa_parameter *par_item = tsa_create_single_parameter(seq, item);
    if (*last)
        {
        (*last)->next = par_item;
        }
    *last = par_item;
    return par_item;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_create_item_parameters
 
    Purpose: Creates any parameters corresponding to the given item.
 
    Functional Description:
        tsa_create_item_parameters checks the item to see if any parameters should be created
        for that item. If so, they are created on the PMD heap, initiliased and inserted after
        the element pointed to by the last pointer.

    Arguments: 
        item - [in] The item to check for parameters.
        seq - [in] The top-level sequence (class) that this item is in.
        last - [in,out] Pointer to a pointer to the last element in the list.

------------------------------------------------------------------------------------------------*/

void tsa_create_item_parameters(autogen_item *item,
                                const autogen_seq *seq,
                                tsa_parameter **last)
    {
    switch (item->base.subtype)
        {
        case AUTOGEN_ITEM_REF:
            if (item->base.flag & AUTOGEN_REF_CONST)
                {
                tsa_parameter *par_item = tsa_create_parameter(seq, item, last);
                autogen_item_value *item_value = (autogen_item_value*) item;
                tsa_fill_par_numeric_type(par_item, item_value);
                /*tsa_fill_par_enum_type(par_item, item_value);*/
                tsa_fill_par_names(par_item, item);
                }
            break;

        case AUTOGEN_ITEM_VALUE:
            {
            if (item->special_number_type != PMD_NUMBER_SPECIAL_TYPE_TRANSACTION_ID)
                {
                tsa_parameter *par_item = tsa_create_parameter(seq, item, last);
                autogen_item_value *item_value = (autogen_item_value*) item;
                if (item_value->pres.type & AUTOGEN_PRESENTATION_CONST)
                    {
                    tsa_fill_par_enum_type(par_item, item_value);
                    }
                else
                    {
                    tsa_fill_par_numeric_type(par_item, item_value);
                    }
                tsa_fill_par_names(par_item, item);
                }
            }
            break;

        case AUTOGEN_ITEM_FILLER:
            /* Don't create parameters for fillers */
            break;

        case AUTOGEN_ITEM_LST:
            {
            /* Only create parameters for IDs */
            if (item->base.flag & AUTOGEN_LST_SBID)
                {
                tsa_parameter *par_item = tsa_create_parameter(seq, item, last);
                par_item->valtypename = idlist_typename;
                par_item->reftypename = idlist_typename;
                tsa_fill_par_names(par_item, item);
                }
            }
            break;

        case AUTOGEN_ITEM_STRING:
            {
            /* Fill in type and type names */
            tsa_parameter *par_item = tsa_create_parameter(seq, item, last);
            char ref_type_name[sizeof(string_typename) + 50];
            par_item->valtypename = string_typename;
            sprintf(ref_type_name, "const %s &", string_typename);
            par_item->reftypename = pmd_heap_strdup(ref_type_name);

            /* Fill in name fields */
            tsa_fill_par_names(par_item, item);
            }
            break;

        case AUTOGEN_ITEM_STRUCT:
            {
            autogen_item_struct *item_struct = (autogen_item_struct *) item;
            autogen_it str_it = INIT_ITERATOR;
            autogen_obj *str = NULL;

            /* Find definitions of structure in the resource */
            str_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
            str_it.obj.name = item_struct->seqname;

        str_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        str_it.ver         = &item_struct->base.base.ver;


            for (str = autogen_obj_find_in_list(&str_it, &seq->base.res->seq_list);
                 str != NULL;
                 str = autogen_obj_find_next_in_list(&str_it))
                {
                autogen_seq *refseq = (autogen_seq *) str;
                tsa_parameter *par_item = tsa_create_parameter(refseq, item, last);
                char type_name[AUTOGEN_MAX_NAME_LENGTH + 50];

                /* Fill in typenames */
                par_item->valtypename = pmd_heap_strdup(tsa_classname(refseq,
                            TSA_C_PREFIX | TSA_NAMESPACE_SHARED | TSA_VERSION_SUFFIX));
                sprintf(type_name, "const %s &", par_item->valtypename);
                par_item->reftypename = pmd_heap_strdup(type_name);

                /* Fill in variable names */
                par_item->parname = pmd_heap_strdup(tsa_struct_name(item_struct, refseq, TRUE));
                par_item->varname = pmd_heap_strdup(tsa_struct_name(item_struct, refseq, FALSE));
                }
            }
            break;

        case AUTOGEN_ITEM_CHOICE:
            {
                autogen_item_case* default_item = ((autogen_item_choice*)item)->default_case;
                autogen_it case_it = INIT_ITERATOR;
                autogen_obj* case_item;

                case_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
                case_it.ver     = &item->base.ver;

                /* default case */
                if (default_item) /* default item found, does it match version */
                {
                    case_item = autogen_obj_find_in_list(&case_it, &default_item->base.base.child_list);
                    while (case_item) /* a default case found */
                    {
                        tsa_create_item_parameters((autogen_item*)case_item, seq, last);

                        case_item = autogen_obj_find_next_in_list(&case_it);
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_MERGE:
            {
            if (tsa_is_item_aggregated(item))
                {
                /* Aggregated merged fields are only supported as entire words */
                tsa_parameter *par_item = tsa_create_parameter(seq, item, last);
                par_item->valtypename = ulong_typename;
                par_item->reftypename = par_item->valtypename;
                par_item->initvalue   = NULL;
                tsa_fill_par_names(par_item, item);
                }
            else
                {
                /* Non-aggregated merged fields get access methods for each element */
                autogen_item* merge_item = (autogen_item*)autogen_obj_get_first_in_list(&item->base.child_list);
                while (merge_item)
                    {
                    tsa_create_item_parameters(merge_item, seq, last);

                    merge_item = (autogen_item*)merge_item->base.next;
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_POINTER:
            {
            tsa_parameter *par_item = tsa_create_parameter(seq, item, last);
            par_item->valtypename = ulong_typename;
            par_item->reftypename = ulong_typename;
            par_item->initvalue = NULL;
            tsa_fill_par_names(par_item, item);
            }
            break;

        default:
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in tsa_create_item_parameters(). item->base.subtype is 0x%08X",
                item->base.subtype);
            }
            break;
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_build_par_list
 
    Purpose: Creates the list of parameters for the given sequence.
 
    Functional Description:
        tsa_build_par_list checks all the items in the sequence and creates any
        parameters for these items. It returns the head of the list.

    Arguments: 
        seq - [in] The (top-level or class) sequence to generate parameters for.

    Return Values: The head of the list, or NULL if the list is empty.

------------------------------------------------------------------------------------------------*/

tsa_parameter* tsa_build_par_list(autogen_seq* seq)
    {
    tsa_parameter head = { 0 };
    tsa_parameter* start = &head;
    tsa_parameter* check = NULL;
    tsa_parameter** last = &start;
    autogen_obj* item = autogen_obj_get_first_in_list(&seq->base.child_list);

    /* Create parameters for each item in the sequence */
    for (; item != NULL; item = item->next)
        {
        tsa_create_item_parameters((autogen_item*)item, seq, last);
        }
    start = head.next;

    /* Eliminate duplicates (could happen with choices or merged fields) */
    for (check = start; check != NULL; check = check->next)
        {
        tsa_parameter *match = NULL;
        tsa_parameter *follow = check;
        for (match = check->next; match != NULL; follow = match, match = match->next)
            {
            if (strcmp(check->varname, match->varname) == 0 ||
                strcmp(check->parname, match->parname) == 0)
                {
                /* Not good. The two parameters have the same TSA varname. We take a wild
                   shot and erase one of them, hoping that they have compatible types
                   (so that encode/decode will at least compile) */
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                    "Duplicate TSA varnames (%s). "
                    "No variable generated for %s. Encoding/decoding may fail.",
                    check->varname, match->parname);
                follow->next = match->next;
                match = follow;
                }
            }
        }

    return start;
    }


/*------------------------------------------------------------------------------------------------

    Name: find_sb_lists
 
    Purpose: Retrieves any sub block lists in the given item list
 
    Functional Description:
        find_sb_lists traverses the item list in order to find any sub block list items.
        It returns a pointer to a statically allocated array of lists, and filles in the
        list_count parameter with the number of lists found. If no lists are found,
        the returned pointer is NULL.

    Arguments: 
        item_list - [in] The list of items to check for sub block lists.
        list_count - [out] Receives the number of found lists. Possibly 0.

    Return Values: A pointer to a statically allocated array of lists, or NULL if none.

------------------------------------------------------------------------------------------------*/

LOCAL autogen_seq_ref **find_sb_lists(autogen_obj_list* obj_list, unsigned int *list_count)
    {
    static autogen_seq_ref *lists[10];
    static const unsigned int max_lists = sizeof(lists) / sizeof(lists[0]);
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    *list_count = 0;

    /* Collect the lists in this sequence */
    while (item)
        {
        if (item->base.subtype == AUTOGEN_ITEM_CHOICE)
            {
            /* Check if there's a default branch */
            autogen_obj* item_case = (autogen_obj*)((autogen_item_choice*)item)->default_case;
            if (item_case)
                {
                /* The problem here is that we're about to call this function recursively,
                   which could overwrite our static buffer. Before the recursive call,
                   we'll create a backup of our static buffer on the stack, and after
                   the call we'll merge the two arrays. This is considered better than
                   to use a non-static buffer. The code in this branch does not assume
                   that it's the same buffer, for defensive reasons. */

                /* Create a backup of our current lists */
                autogen_seq_ref *backup_lists[10];
                unsigned int backup_count = *list_count;
                autogen_seq_ref **choice_lists = NULL;
                unsigned int choice_count = 0;
                memcpy(backup_lists, lists, sizeof(lists[0])*backup_count);

                /* Call this function recursively */
                choice_lists = find_sb_lists(&item_case->child_list, &choice_count);
                if (choice_lists)
                    {
                    /* Merge the results */
                    *list_count = backup_count + choice_count;
                    if (*list_count > max_lists)
                        {
                        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                            "Internal limit on number of sub block lists (%u) exceeded.",
                            max_lists);
                        }
                    memmove(lists, choice_lists, sizeof(lists[0])*choice_count);
                    memmove(lists+choice_count, backup_lists, sizeof(lists[0])*backup_count);
                    }
                }
            }
        else if (item->base.subtype == AUTOGEN_ITEM_LST && (item->base.flag & AUTOGEN_LST_SB))
            {
            if (*list_count == max_lists)
                {
                util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Internal limit on number of sub block lists (%u) exceeded.",
                    max_lists);
                }
            lists[(*list_count)++] = (autogen_seq_ref*)autogen_obj_get_first_in_list(&item->base.child_list);
            }

        item = (autogen_item*)item->base.next;
        }

    /* Check if any sub block lists were found and return */
    if (*list_count == 0)
        {
        return NULL;
        }
    return lists;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_get_scoped_typename
 
    Purpose: Returns the given name, with any scoping qualifier added
 
    Functional Description:
        tsa_get_scoped_typename checks if the type is one of a number of predefined
        types (such as unsigned long). If not, the current resource prefix is
        preprended to the type name. If the name starts with a const qualifier,
        any scoping qualifier is added after the const.

    Arguments: 
        name - [in] The name without scoping.

    Return Values: Pointer to a static buffer containing the name with any scoping added.

------------------------------------------------------------------------------------------------*/

LOCAL const char *tsa_get_scoped_typename(const char *name)
    {
    static const char const_prefix[] = "const ";
    static const char scope_operator[] = "::";
    static const unsigned int const_prefix_length = sizeof(const_prefix) - 1;
    static char result[AUTOGEN_MAX_NAME_LENGTH*2+1];
    char *end = result;

    /* If there's a const prefix, leave that out of any scoping */
    if (strncmp(name, const_prefix, const_prefix_length) == 0)
        {
        memcpy(end, const_prefix, const_prefix_length);
        end += const_prefix_length;
        name += const_prefix_length;
        }

    /* If the name is already scoped with the TSA namespace, don't change it */
    if (strncmp(name, tsa_namespace, sizeof(tsa_namespace)-1) == 0)
    {
        /* We can't just return name here, because of const (and because
           the caller might expect to be able to overwrite name */
        strcpy(end, name);
        return result;
    }

    /* If there's an std prefix, don't change the name */
    if (strncmp(name, const_prefix, const_prefix_length) == 0)
        {
        /* We can't just return name here, because of const (and because
           the caller might expect to be able to overwrite name */
        strcpy(end, name);
        return result;
        }

    /* Try any predefined names that might be used */
    if (strncmp(name, hresult_typename, sizeof(hresult_typename)-1) != 0 &&
#if (PMD_FILE_FORMAT >= 600)
        strncmp(name, ulonglong_typename, sizeof(ulonglong_typename)-1) != 0 &&
#endif
        strncmp(name, ulong_typename, sizeof(ulong_typename)-1) != 0 &&
        strncmp(name, ushort_typename, sizeof(ushort_typename)-1) != 0 &&
        strncmp(name, uchar_typename, sizeof(uchar_typename)-1) != 0 &&
#if (PMD_FILE_FORMAT >= 600)
        strncmp(name, longlong_typename, sizeof(longlong_typename)-1) != 0 &&
#endif
        strncmp(name, long_typename, sizeof(long_typename)-1) != 0 &&
        strncmp(name, short_typename, sizeof(short_typename)-1) != 0 &&
        strncmp(name, char_typename, sizeof(char_typename)-1) != 0 &&
        strncmp(name, string_typename, sizeof(string_typename)-1) != 0 &&
        strncmp(name, size_t_typename, sizeof(size_t_typename)-1) != 0 &&
        strncmp(name, byte_array_typename, sizeof(byte_array_typename)-1) != 0 &&
        strncmp(name, idlist_typename, sizeof(idlist_typename)-1) != 0 &&
        strstr(name, scope_operator) == NULL)
        {
        /* It's not a known name, so it must be something from the current namespace */
        end += sprintf(end, "%s::%s::", tsa_namespace, s_res_prefix);
        }

    /* Just use the rest of the name as is */
    strcpy(end, name);
    return result;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_header
 
    Purpose: Writes a Continuus header to the given file
 
    Functional Description:
        tsa_write_header writes a standard TSS Continuus header to the given
        file. Some of the fields are pre-filled with appropriate values.

    Arguments: 
        f - [in] Stream to write the header to.
        res - [in] Resource that the file pertains to
        is_header - [in] Whether it's an include file.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_header(FILE* f, autogen_res* res, int is_header)
    {
    char caption[AUTOGEN_MAX_NAME_LENGTH*2 + 100];

    /* Format timestamp */
    time_t the_time_t = time(&the_time_t);
    struct tm *the_tm = localtime(&the_time_t);
    char *time_string = asctime(the_tm);

    /* Format caption*/
    sprintf(caption, "TSS Product Message class for %s (%s)",
            res->logical_name, res->base.name);

    /* Write Continuus header */
    fprintf(f, "/*\n");
    fprintf(f, "NOKIA\n");
    fprintf(f, "R&D Copenhagen\n");
    fprintf(f, "Corleone\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "                %s\n", caption);
    fprintf(f, "                %s\n", util_get_hyphens(strlen(caption)));
    fprintf(f, "\n");
    fprintf(f, "                %s\n", is_header ? "SW Include" : "SW Module");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "\n");
    fprintf(f, "Continuus DB:     sa_pctls\n");
    fprintf(f, "\n");
    fprintf(f, "Project:          Server API\n");
    fprintf(f, "\n");
    fprintf(f, "%%name:            tsa_%s_isi.%s %%\n",
            res->resnameshort_l, is_header ? "h" : "cpp");
    fprintf(f, "\n");
    fprintf(f, "%%version:         %03hd.%03hd %%\n",
            res->base.ver.from[0], res->base.ver.from[1]);
    fprintf(f, "\n");
    fprintf(f, "%%instance:        %%\n");
    fprintf(f, "\n");
    fprintf(f, "%%full_filespec:   %%\n");
    fprintf(f, "\n");
    fprintf(f, "%%derived_by:      %%\n");
    fprintf(f, "\n");
    fprintf(f, "%%date_modified:   %.*s %%\n", strlen(time_string)-1, time_string);
    fprintf(f, "\n");
    fprintf(f, "Copyright (c) Nokia. All rights reserved.\n");
    fprintf(f, "*/\n");
    fprintf(f, "\n");
    fprintf(f, "// Generated with autogen version %s\n", AUTOGEN_VERSION_NUMBER);
    fprintf(f, "// DO NOT EDIT - changes will be lost at next autogeneration\n");
    fprintf(f, "\n");
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_get_parameter_type
 
    Purpose: Determines the type of a given parameter
 
    Functional Description:
        tsa_get_parameter_type checks if the parameter corresponds to one of the built-in
        types in C++. If not, it simply returns the reference typename for the parameter.
        It then checks if the type should be widened. If so, it returns "unsigned long"
        for unsigned types and "long" for signed types. If the type should not be
        widened, it returns the name of the corresponding built-in type, e.g. "unsigned short".

    Arguments: 
        parameter - [in] Pointer to the parameter structure.
        widen - [in] Whether the returned type should be widened

------------------------------------------------------------------------------------------------*/
LOCAL const char* tsa_get_parameter_type(tsa_parameter *parameter, int widen)
    {
    switch(parameter->item->length)
        {
        case 8:
            return widen ? ulong_typename : uchar_typename;
        case 16:
            return widen ? ulong_typename : ushort_typename;
        case 32:
            return ulong_typename;
#if (PMD_FILE_FORMAT >= 600)
        case 64:
            return ulonglong_typename;
#endif
        case -8:
            return widen ? long_typename : char_typename;
        case -16:
            return widen ? long_typename : short_typename;
        case -32:
            return long_typename;
#if (PMD_FILE_FORMAT >= 600)
        case -64:
            return longlong_typename;
#endif
        default:
            /* Check for a special case with submessage namespace ambiguity */
            if (!strcmp(parameter->valtypename, tsa_classname((autogen_seq*)util_get_base_parent((autogen_obj*)parameter->item), TSA_C_PREFIX | TSA_VERSION_SUFFIX)))
            {
                static char scoped_name[AUTOGEN_MAX_NAME_LENGTH*3+20];
                strcpy(scoped_name, tsa_get_scoped_typename(parameter->reftypename));
                return scoped_name;
            }

            return parameter->reftypename;
        }
    }

/*------------------------------------------------------------------------------------------------

    Name: tsa_write_getset_method
 
    Purpose: Writes GetXXX and/or SetXXX methods for the given parameter.
 
    Functional Description:
        tsa_write_getset_method checks the parent sequence for the parameter.
        If it's not a message, both GetXXX and SetXXX are written. Otherwise,
        the flags for the message is checked. If the flags include
        AUTOGEN_MSG_REQ, only a SetXXX method is written, otherwise,
        only a GetXXX method is written.

        An additional newline, and any comment for the parameter, is written
        before the method(s). The methods are named GetXXX/SetXXX, where XXX
        indicates the TSA name for the parameter.

    Arguments: 
        f_h - [in,out] The stream to write the method declaration to.
        f_c - [in,out] The stream to write the method definition to.
        parameter - [in] Pointer to the parameter structure.

------------------------------------------------------------------------------------------------*/
LOCAL void tsa_write_getset_method(FILE *f_h,
                                   FILE *f_c,
                                   tsa_parameter *parameter)
    {
    /* Constants for printing both in header and source file */
    char indent[50] = "";
    const char *end_decl = ";";
    const autogen_obj *parent_base = &parameter->seq->base;

    /* Prepare for code in either header file or C file */
    if (f_h == f_c)
        {
        sprintf(indent, "%s    ", base_indent_string);
        end_decl = "";
        }

    /* Write the Set method if the request flag is set, or if it's not a message */
    if (!(parent_base->type & AUTOGEN_OBJ_MSG) || (parent_base->flag & AUTOGEN_MSG_REQ))
        {
        fprintf(f_h, "\n");
        fprintf(f_h, "%s    // %s", base_indent_string, parameter->item->parname);
        if (parameter->comment && *parameter->comment)
            {
            fprintf(f_h, ":\n%s", parameter->comment);
            }
        else
            {
            fprintf(f_h, "\n");
            }

        fprintf(f_h, "%s    void Set%s(%s%s%s)%s\n",
                base_indent_string,
                parameter->parname,
                tsa_get_parameter_type(parameter, TRUE),
                tsa_space_after_typename(tsa_get_parameter_type(parameter, TRUE)),
                parameter->varname,
                end_decl);
        if (f_h != f_c)
            {
            fprintf(f_c, "\n");
            fprintf(f_c, "void %s::Set%s(%s%s%s)\n",
                    s_scoped_classname,
                    parameter->parname,
                    tsa_get_parameter_type(parameter, TRUE),
                    tsa_space_after_typename(tsa_get_parameter_type(parameter, TRUE)),
                    parameter->varname);
            }
        fprintf(f_c, "%s{\n", indent);
        fprintf(f_c, "%s    m_%s = %s;\n", indent, parameter->varname, parameter->varname);
        if (!parameter->initvalue)
            {
            fprintf(f_c, "%s    %s = true;\n", indent, tsa_initname(parameter));
            }
        fprintf(f_c, "%s}\n", indent);
        }

    /* Write Get method if any other flag than request is set, or if it's not a message */
    if (!(parent_base->type & AUTOGEN_OBJ_MSG) || (parent_base->flag & tsa_not_request_mask))
        {
        fprintf(f_h, "\n");
        fprintf(f_h, "%s    // %s", base_indent_string, parameter->item->parname);
        if (parameter->comment && *parameter->comment)
            {
            fprintf(f_h, ":\n%s", parameter->comment);
            }
        else
            {
            fprintf(f_h, "\n");
            }

        fprintf(f_h, "%s    %s%sGet%s() const%s\n",
                base_indent_string,
                tsa_get_parameter_type(parameter, FALSE),
                tsa_space_after_typename(tsa_get_parameter_type(parameter, FALSE)),
                parameter->parname,
                end_decl);
        if (f_h != f_c)
            {
            const char *scoped_typename = tsa_get_scoped_typename(tsa_get_parameter_type(parameter, FALSE));
            fprintf(f_c, "\n");
            fprintf(f_c, "%s%s", scoped_typename, tsa_space_after_typename(scoped_typename));
            fprintf(f_c, "%s::Get%s() const\n", s_scoped_classname, parameter->parname);
            }
        fprintf(f_c, "%s{\n", indent);
        if (!parameter->initvalue)
            {
            fprintf(f_c, "%s    CheckInit(%s,\n", indent, tsa_initname(parameter));
            fprintf(f_c, "%s              \"%s::Get%s\");\n",
                    indent,
                    s_scoped_classname,
                    parameter->parname);
            }
        if (parameter->item->length == 8  || parameter->item->length == -8 ||
            parameter->item->length == 16 || parameter->item->length == -16)
            {
            fprintf(f_c, "%s    return static_cast<%s>(m_%s);\n",
                    indent, tsa_get_parameter_type(parameter, FALSE), parameter->varname);
            }
        else
            {
            fprintf(f_c, "%s    return m_%s;\n", indent, parameter->varname);
            }
        fprintf(f_c, "%s}\n", indent);
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_add_method
 
    Purpose: Writes the AddXXX method used for lists
 
    Functional Description:
        tsa_write_add_method writes an AddXXX method to the given header and implementation
        files. The XXX is given as the varname parameter,  the member variable name
        (excluding m_ prefix) is given as the varname parameter, and the type to use
        for the parameters is given as the reftypename parameter.

    Arguments: 
        f_h - [in,out] Pointer to file stream to write the declaration to.
        f_c - [in,out] Pointer to file stream to write the implementation to.
        varname - [in] The TSA varname of the parameter (internal in the class)
        parname - [in] The TSA parname of the parameter (external to the class)
        reftypename - [in] The type of the parameter (as used for references).

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_add_method(FILE *f_h,
                                FILE *f_c,
                                const char *varname,
                                const char *parname,
                                const char *reftypename)
    {
    /* Variables for handling combined or separate declaration and implementation */
    const char *indent = "";
    const char *end_decl = ";";
    if (f_h == f_c)
        {
        indent = util_get_spaces(base_indent + indent_step);
        end_decl = "";
        }

    /* Write the declaration in the header */
    fprintf(f_h, "\n");
    fprintf(f_h, "%s    void Add%s(%s%selement)%s\n",
            base_indent_string,
            parname,
            reftypename,
            tsa_space_after_typename(reftypename),
            end_decl);

    /* Also write a prototype in the implementation file, if different */
    if (f_h != f_c)
        {
        fprintf(f_c, "\n");
        fprintf(f_c, "void %s::Add%s(%s%selement)\n",
                s_scoped_classname,
                parname,
                reftypename,
                tsa_space_after_typename(reftypename));
        }

    /* Write the implementation */
    fprintf(f_c, "%s{\n", indent);
    fprintf(f_c, "%s    m_%s.push_back(element);\n", indent, varname);
    fprintf(f_c, "%s}\n", indent);
    }



/*------------------------------------------------------------------------------------------------

    Name: tsa_write_getcount_methods
 
    Purpose: Writes the GetXXX and GetXXXCount methods used for lists.
 
    Functional Description:
        tsa_write_getcount_methods writes a GetXXX and a GetXXXCount method to the
        given header and implementation files. The XXX is given as the parname parameter,
        the member variable name (excluding m_ prefix) is given as the varname parameter,
        and the type to use for the return value for GetXXX is given as the reftypename
        parameter. In case of user-defined types, the reftypename should NOT include any
        scoping qualifiers. If needed, they will be added by this method.

    Arguments: 
        f_h - [in,out] Pointer to file stream for the header file.
        f_c - [in,out] Pointer to file stream for the implementation file.
        varname - [in] The TSA varname of the parameter (internal in the class)
        parname - [in] The TSA parname of the parameter (external to the class)
        reftypename - [in] Name of the type of the variable.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_getcount_methods(FILE *f_h,
                                      FILE *f_c,
                                      const char *varname,
                                      const char *parname,
                                      const char *reftypename)
    {
    /* Variables for handling rearrangement of Count and version */
    static const char ver_format[] = "_%3d_%3d";
    int dummy_ver = 0;
    int parname_base_len = (int) strlen(parname) - ((int) sizeof(ver_format) - 1);
    char count_method[AUTOGEN_MAX_NAME_LENGTH+20];

    /* Variables for handling combined or separate declaration and implementation */
    const char *indent = "";
    const char *end_decl = ";";
    if (f_h == f_c)
        {
        indent = util_get_spaces(base_indent + indent_step);
        end_decl = "";
        }

    /* Calculate the name for GetXXXCount */
    if (parname_base_len > 0 &&
        sscanf(parname + parname_base_len, ver_format, &dummy_ver, &dummy_ver) == 2)
        {
        sprintf(count_method, "Get%.*sCount%s",
                parname_base_len, parname, parname + parname_base_len);
        }
    else
        {
        sprintf(count_method, "Get%sCount", parname);
        }

    /* Write the declaration of GetXXX in the header */
    fprintf(f_h, "%s    %s%sGet%s(%s index = 0) const%s\n",
            base_indent_string,
            reftypename,
            tsa_space_after_typename(reftypename),
            parname,
            size_t_typename,
            end_decl);

    /* Also write a prototype for GetXXX in the implementation, if different */
    if (f_h != f_c)
        {
        fprintf(f_c, "\n");
        fprintf(f_c, "%s%s%s::Get%s(%s index /* = 0 */) const\n",
                tsa_get_scoped_typename(reftypename),
                tsa_space_after_typename(reftypename),
                s_scoped_classname,
                parname,
                size_t_typename);
        }

    /* Write the implementation of GetXXX */
    fprintf(f_c, "%s{\n", indent);
    fprintf(f_c, "%s    %s::CheckIndex(index, \n", indent, tsa_namespace);
    fprintf(f_c, "%s                   %sm_%s.size(),\n",
            util_get_spaces(sizeof(tsa_namespace)-3), indent, varname);
    fprintf(f_c, "%s                   %s\"%s::Get%s()\");\n",
            util_get_spaces(sizeof(tsa_namespace)-3),
            indent,
            s_scoped_classname,
            parname);
    fprintf(f_c, "%s    return m_%s[index];\n", indent, varname);
    fprintf(f_c, "%s}\n", indent);

    /* Write the declaration of GetXXXCount in the header */
    fprintf(f_h, "%s    %s %s() const%s\n",
            base_indent_string, size_t_typename, count_method, end_decl);

    /* Also write a prototype for GetXXXCount in the implementation, if different */
    if (f_h != f_c)
        {
        fprintf(f_c, "\n");
        fprintf(f_c, "%s %s::%s() const\n",
                size_t_typename,
                s_scoped_classname,
                count_method);
        }

    /* Write the implementation of GetXXXCount */
    fprintf(f_c, "%s{\n", indent);
    fprintf(f_c, "%s    return m_%s.size();\n", indent, varname);
    fprintf(f_c, "%s}\n", indent);
    }

/*------------------------------------------------------------------------------------------------

    Name: tsa_write_single_set_of_subblock_methods
 
    Purpose: Writes the AddXXX, GetXXXCount and GetXXX methods used for one specific sub block
 
    Functional Description:
        tsa_write_single_set_of_subblock_methods writes all three methods.
        Otherwise, the flags for the message is checked. If the flags include AUTOGEN_MSG_REQ, only an
        AddXXX method is written, otherwise, only GetXXX and GetXXXCount
        methods are written.

        An additional newline, and any comment for the parameter, is written
        before the method(s). The methods are named AddXXX, GetXXX and GetXXXCount,
        where XXX indicates the TSA name for the sub block.

    Arguments: 
        f_h - [in,out] The stream to write the method declarations to.
        f_c - [in,out] The stream to write the method definitions to.
        sb_trav - [in] The sub block to write the methods for.
        parent - [in] Sequence containing this sub block list.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_single_set_of_subblock_methods(FILE *f_h,
                                      FILE *f_c,
                                      const autogen_seq_ref *sb_trav,
                                                    const autogen_seq *parent,
                                                    const char* parname,
                                                    const char* varname,
                                                    const char* reftypename)
    {
    unsigned int msg_flags = AUTOGEN_MSG_REQ | AUTOGEN_MSG_RESP;
    if (parent->base.type & AUTOGEN_OBJ_MSG)
        {
        msg_flags = parent->base.flag;
        }

    /* Only print the sub block name comment if we have more than one method */
    if (msg_flags & tsa_not_request_mask)
        {
        fprintf(f_h, "\n");
        fprintf(f_h, "%s    // %s", base_indent_string, sb_trav->seqptr->base.name);
        }

    /* Write the Add method */
    if (msg_flags & AUTOGEN_MSG_REQ)
        {
        tsa_write_add_method(f_h, f_c, varname, parname, reftypename);
        }

    if (msg_flags & tsa_not_request_mask)
        {
        /* Only print a separator if the previous method was not for this sub block */
        if (!(msg_flags & AUTOGEN_MSG_REQ))
            {
            fprintf(f_h, "\n");
            }

        tsa_write_getcount_methods(f_h, f_c, varname, parname, reftypename);
        }
    }

/*------------------------------------------------------------------------------------------------

    Name: tsa_write_subblock_methods
 
    Purpose: Writes the AddXXX, GetXXXCount and GetXXX methods used for sub blocks
 
    Functional Description:
        tsa_write_subblock_methods checks the parent to see if it's a message sequence.
        If not, all three methods are written. Otherwise, the flags for the
        message is checked. If the flags include AUTOGEN_MSG_REQ, only an
        AddXXX method is written, otherwise, only GetXXX and GetXXXCount
        methods are written.

        An additional newline, and any comment for the parameter, is written
        before the method(s). The methods are named AddXXX, GetXXX and GetXXXCount,
        where XXX indicates the TSA name for the sub block.

    Arguments: 
        f_h - [in,out] The stream to write the method declarations to.
        f_c - [in,out] The stream to write the method definitions to.
        sb_trav - [in] The sub block to write the methods for.
        parent - [in] Sequence containing this sub block list.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_subblock_methods(FILE *f_h,
                                      FILE *f_c,
                                      const autogen_seq_ref *sb_trav,
                                      const autogen_seq *parent)
    {
    /* Constants for printing both in header and source file */
    char varname[AUTOGEN_MAX_NAME_LENGTH];
    char parname[AUTOGEN_MAX_NAME_LENGTH];
    char reftypename[AUTOGEN_MAX_NAME_LENGTH+20];

    if (sb_trav->base.flag & AUTOGEN_OBJ_IS_SHARED_EXTERNAL)  /* Make different versioning if shared resource */
        {
        autogen_obj* sb;
        autogen_it sb_it = INIT_ITERATOR;

        sb_it.typemask = AUTOGEN_OBJ_SB;
        sb_it.obj.name = ((autogen_seq_ref*)sb_trav)->seqptr->base.name;

        sb = autogen_obj_find_in_list(&sb_it, &((autogen_seq_ref*)sb_trav)->seqptr->base.res->seq_list);
        while (sb)
            {
            char version_suffix[AUTOGEN_MAX_NAME_LENGTH];
            if ((sb->ver.from[0] != 0) || (sb->ver.from[1] != 0) || util_has_multiple_versions(sb))
                {
                sprintf(version_suffix , "_%03hd_%03hd", sb->ver.from[0], sb->ver.from[1]);
                }
            else
                {
                sprintf(version_suffix , "");
                }

            sprintf(parname, "%s%s", tsa_classname(sb_trav->seqptr, 0), version_suffix);
            sprintf(varname, "%s%s", tsa_classname(sb_trav->seqptr, TSA_VEC_PREFIX), version_suffix);
            sprintf(reftypename, "const %s%s &", tsa_classname(sb_trav->seqptr, TSA_C_PREFIX | TSA_NAMESPACE_SHARED), version_suffix);

            tsa_write_single_set_of_subblock_methods(   f_h,
                                                        f_c,
                                                        sb_trav,
                                                        parent,
                                                        parname,
                                                        varname,
                                                        reftypename );

            sb = autogen_obj_find_next_in_list(&sb_it);
            }
        }
    else
        {
        strcpy(parname, tsa_classname(sb_trav->seqptr, TSA_VERSION_SUFFIX));
        strcpy(varname, tsa_classname(sb_trav->seqptr, TSA_VERSION_SUFFIX | TSA_VEC_PREFIX));
        sprintf(reftypename, "const %s &", tsa_classname(sb_trav->seqptr,
            TSA_C_PREFIX | TSA_NAMESPACE_SHARED | TSA_VERSION_SUFFIX));

        tsa_write_single_set_of_subblock_methods(   f_h,
                                                    f_c,
                                                    sb_trav,
                                                    parent,
                                                    parname,
                                                    varname,
                                                    reftypename );
        }
    }

LOCAL void tsa_write_setversion(FILE *f_h,
                                FILE *f_c,
                                const autogen_ver* ver)
    {
    if(ver->type != AUTOGEN_OBJ_VERSION_ALL)
        {
        fprintf(f_h, "\n");
        fprintf(f_h, "%s    void SetIsiVersion(const CVersion &version);\n", base_indent_string);

        fprintf(f_c, "\n");
        fprintf(f_c, "void %s::SetIsiVersion(const CVersion &version)\n", s_scoped_classname);
        fprintf(f_c, "{\n");
        switch(ver->type)
        {
        case AUTOGEN_OBJ_VERSION_FROM:
            fprintf(f_c, "    if (version < %s::CVersion(%hd,%hd))\n", tsa_namespace, ver->from[0], ver->from[1] );
            break;
        case AUTOGEN_OBJ_VERSION_TO:
            fprintf(f_c, "    if (version >= %s::CVersion(%hd,%hd))\n", tsa_namespace, ver->to[0], ver->to[1] );
            break;
        case AUTOGEN_OBJ_VERSION_INTERVAL:
            fprintf(f_c, "    if ((version < %s::CVersion(%hd,%hd)) || (version >= %s::CVersion(%hd,%hd)))\n", tsa_namespace, ver->from[0], ver->from[1], tsa_namespace, ver->to[0], ver->to[1] );
            break;
        case AUTOGEN_OBJ_VERSION_EXACT:
            fprintf(f_c, "    if (!(version == %s::CVersion(%hd,%hd)))\n", tsa_namespace, ver->from[0], ver->from[1]);
            break;
        default:
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in tsa_write_setversion(). ver->type is 0x%08X",
                ver->type);
            fprintf(f_c, "    if (false != false)\n"); /* Avoid exception */
            break;
        }
        fprintf(f_c, "    {\n");
        fprintf(f_c, "        CException::Throw(__LOC__, TSSSA_E_INVALID_VERSION, \n");
        fprintf(f_c, "                          \"%s::SetIsiVersion()\",\n", s_scoped_classname );
        fprintf(f_c, "                          version.GetZ(), version.GetY());\n");
        fprintf(f_c, "    }\n");

        fprintf(f_c, "    static_cast<%s::CBaseImpl *>(this)->SetIsiVersion(version);\n", tsa_namespace);
        fprintf(f_c, "    %s::%s::ResourceVersion = version;\n", tsa_namespace, s_res_namespace);

        fprintf(f_c, "}\n");
        }
    }

LOCAL void tsa_write_access_methods(FILE *f_h,
                                    FILE *f_c,
                                    tsa_parameter *parameter)
    {
    const autogen_obj *parent_base = &parameter->seq->base;

    /* In case of simple get/set, delegate to the appropriate function */
    if (!tsa_is_parameter_aggregated(parameter))
        {
        tsa_write_getset_method(f_h, f_c, parameter);
        return;
        }
    
    /* We have some kind of aggregration. Write the list access methods */
    fprintf(f_h, "\n");
    fprintf(f_h, "%s", parameter->comment);

    /* Write the Add method if the request flag is set, or if it's not a message */
    if (!(parent_base->type & AUTOGEN_OBJ_MSG) || (parent_base->flag & AUTOGEN_MSG_REQ))
        {
        tsa_write_add_method(f_h, f_c, parameter->varname,
                             parameter->parname, parameter->reftypename);
        }

    /* Write Get and GetCount methods if any other flag than request is set, or if it's not a message */
    if (!(parent_base->type & AUTOGEN_OBJ_MSG) || (parent_base->flag & tsa_not_request_mask))
        {
        tsa_write_getcount_methods(f_h, f_c, parameter->varname,
                                   parameter->parname, parameter->reftypename);
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_member_variable
 
    Purpose: Writes a member variable definition for the given parameter
 
    Functional Description:
        tsa_write_member_variable 

    Arguments: 
        f - [in] The stream pointer to write the definition to.
        parameter - [in] 

    Return Values: The return value is of type LOCAL void

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_member_variable(FILE *f, tsa_parameter *parameter)
    {
    char valtypename[AUTOGEN_MAX_NAME_LENGTH+10];
    sprintf(valtypename, "%s", parameter->valtypename);

    fprintf(f, "%s%s", base_indent_string, util_get_spaces(indent_step));
    if((parameter->item->base.parent->type == AUTOGEN_OBJ_MSG) &&
       (parameter->item->base.parent->flag & AUTOGEN_MSG_IS_SUBMSG) &&
       (! prop_has(&((autogen_seq*)parameter->item->base.parent)->base.res->base, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE)))
        {
        /* Is SubMessage, and namespace is made for it */

        if(0 == strcmp(parameter->valtypename, tsa_classname((autogen_seq*)parameter->item->base.parent, TSA_C_PREFIX | TSA_VERSION_SUFFIX)))
            {
            sprintf(valtypename, "%s::%s::%s", tsa_namespace, s_res_namespace, parameter->valtypename);
            }
        }

    if (tsa_is_parameter_aggregated(parameter))
        {
        fprintf(f, "std::vector<%s> ", valtypename);
        }
    else
        {
        fprintf(f, "%s%s",
                valtypename,
                tsa_space_after_typename(valtypename));
        }
    fprintf(f, "m_%s;  // %s\n", parameter->varname, parameter->item->varname);
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_base_initializer
 
    Purpose: Writes the initializer for the base class
 
    Functional Description:
        tsa_write_version_initializer writes an appropriate initialisation of the base
        class into the file. The initilizer includes a leading colon, but no trailing
        comma.

    Arguments: 
        f - [in,out] The stream to write the initializer to.
        seq - [in] Structure to write base class initialisation for.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_base_initializer(FILE *f, const autogen_seq *seq)
{
    if (seq->base.ver.type & AUTOGEN_OBJ_VERSION_TO)
    {
        /* Find the last resource version within the sequence version range */
        autogen_it ver_it = INIT_ITERATOR;
        autogen_obj* ver = NULL;

        ver_it.ver       = &seq->base.ver;
        ver_it.vercrit   = AUTOGEN_OBJ_VERSION_OVERLAP;
        ver_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_VERSION_REVERSED;

        ver = autogen_obj_find_in_list(&ver_it, &seq->base.res->ver_list);

        /* Check if a version exists and print it */
        if (ver)
        {
            fprintf(f, ": %s::CBaseImpl(%s::CVersion(%u,%u))",
                tsa_namespace, tsa_namespace, ver[0].ver.from[0], ver[0].ver.from[1]);
        }
        else
        {
            fprintf(f, ": %s::CBaseImpl(%s::CVersion(0,0))",
                tsa_namespace, tsa_namespace);
        }
    }
    else
    {
        fprintf(f, ": %s::CBaseImpl(%s::CVersion(%u,%u))",
            tsa_namespace,
            tsa_namespace,
            seq->base.res->base.ver.from[0],
            seq->base.res->base.ver.from[1]);
    }
}

/*------------------------------------------------------------------------------------------------

    Name: tsa_write_constructor
 
    Purpose: Writes the definition of the constructor for the current class
 
    Functional Description:
        tsa_write_constructor writes the declaration of the constructor
        in the header file and writes the definition of it in the implementation
        file. The given parameter list is used as arguments to the constructor.
        The name of the class is taken from s_classname and s_scoped_classname.

    Arguments: 
        f_h - [in,out] The stream to write the declaration to.
        f_c - [in,out] The stream to write the definition to.
        parameter - [in] The list of parameters for this type.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_constructor(FILE *f_h,
                                 FILE *f_c,
                                 const autogen_seq *seq,
                                 tsa_parameter *parameter)
    {
    int is_first = TRUE;
    int num_args = 0;

    /* Constants for printing both in header and source file */
    char indent[50] = "";
    const char *end_decl = ";\n";
    tsa_parameter *current = NULL;
    if (f_h == f_c)
        {
        sprintf(indent, "%s    ", base_indent_string);
        end_decl = "";
        }

    /* Count the number of arguments to the constructor */
    for (current = parameter; current != NULL; current = current->next)
        {
        if (!tsa_is_parameter_aggregated(current))
            {
            num_args++;
            }
        }

    /* If there are any arguments, write another constructor without arguments */
    if (num_args > 0)
        {
        fprintf(f_h, "%s    // Default constructor\n", base_indent_string);
        fprintf(f_h, "%s    %s()%s",
                base_indent_string,
                tsa_classname(seq, TSA_C_PREFIX | TSA_VERSION_SUFFIX),
                end_decl);
        if (f_h != f_c)
            {
            fprintf(f_c, "\n");
            fprintf(f_c, "%s::",
                    tsa_classname(seq, TSA_C_PREFIX | TSA_VERSION_SUFFIX | TSA_NAMESPACE_ALWAYS));
            fprintf(f_c, "%s()",
                    tsa_classname(seq, TSA_C_PREFIX | TSA_VERSION_SUFFIX));
            }
        fprintf(f_c, "\n%s", indent);
        tsa_write_base_initializer(f_c, seq);
        for (current = parameter; current != NULL; current = current->next)
            {
            if (!tsa_is_parameter_aggregated(current))
                {
                fprintf(f_c, ",\n  ");
                if (current->initvalue)
                    {
                    fprintf(f_c, "m_%s(%s)", current->varname, current->initvalue);
                    }
                else
                    {
                    fprintf(f_c, "%s(false)", tsa_initname(current));
                    }
                }
            }
        fprintf(f_c, "\n{\n");
        fprintf(f_c, "}\n");
        fprintf(f_h, "\n");
        }

    /* Write the declaraction of the constructor in the header */
    fprintf(f_h, "%s    // Initialising constructor\n", base_indent_string);
    fprintf(f_h, "%s    %s%s(",
            base_indent_string,
            num_args == 1 ? "explicit " : "",
            tsa_classname(seq, TSA_C_PREFIX | TSA_VERSION_SUFFIX));
    is_first = TRUE;
    for (current = parameter; current != NULL; current = current->next)
        {
        if (!tsa_is_parameter_aggregated(current))
            {
            /* Go to a new line */
            if (!is_first)
                {
                fprintf(f_h, ",");
                }
            is_first = FALSE;
            fprintf(f_h, "\n");
            fprintf(f_h, "%s        ", base_indent_string);

            /* Print the parameter */
            fprintf(f_h, "%s%s%s",
                    tsa_get_parameter_type(current, TRUE),
                    tsa_space_after_typename(tsa_get_parameter_type(current, TRUE)),
                    current->varname);
            }
        }
    fprintf(f_h, ")%s", end_decl);

    /* Also write a prototype for the constructor in the implementation, if different */
    if (f_h != f_c)
        {
        fprintf(f_c, "\n");
        fprintf(f_c, "%s::",
                tsa_classname(seq, TSA_C_PREFIX | TSA_VERSION_SUFFIX | TSA_NAMESPACE_ALWAYS));
        fprintf(f_c, "%s(", tsa_classname(seq, TSA_C_PREFIX | TSA_VERSION_SUFFIX));
        is_first = TRUE;
        for (current = parameter; current != NULL; current = current->next)
            {
            if (!tsa_is_parameter_aggregated(current))
                {
                /* Go to a new line */
                if (!is_first)
                    {
                    fprintf(f_c, ",");
                    }
                is_first = FALSE;
                fprintf(f_c, "\n");
                fprintf(f_c, "    ");

                /* Print the parameter with initialiser in comments */
                fprintf(f_c, "%s%s%s",
                        tsa_get_parameter_type(current, TRUE),
                        tsa_space_after_typename(tsa_get_parameter_type(current, TRUE)),
                        current->varname);
                }
            }
        fprintf(f_c, ")");
        }

    /* Write the implementation of the constructor */
    fprintf(f_c, "\n%s", indent);
    tsa_write_base_initializer(f_c, seq);
    for (current = parameter; current != NULL; current = current->next)
        {
        if (!tsa_is_parameter_aggregated(current))
            {
            fprintf(f_c, ",\n%s  m_%s(%s)", indent, current->varname, current->varname);
            if (!current->initvalue)
                {
                fprintf(f_c, ",\n%s  %s(true)", indent, tsa_initname(current));
                }
            }
        }
    fprintf(f_c, "\n");
    fprintf(f_c, "%s{\n", indent);
    fprintf(f_c, "%s}\n", indent);
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_get_endianness
 
    Purpose: Returns an enumeration value string indicating the endianness of the given item.
 
    Functional Description:
        tsa_get_endianness returns one of two constant strings, depending on the endianness
        of the given item. It considers nibble-swapped BCD strings as little-endian.

    Arguments: 
        item - [in] The item to retrieve the endianness of

    Return Values: A static string of form "Tss::ServerApi::CEncodeDecodeBase::e<Big|Little>Endian"

------------------------------------------------------------------------------------------------*/

LOCAL const char *tsa_get_endianness(const autogen_item *item)
    {
    static char buffer[sizeof(tsa_namespace)+100];
    char *endianness = NULL;
    if (item->order & (AUTOGEN_ORDER_BE | AUTOGEN_ORDER_BCD_NONE))
        {
        endianness = "eBigEndian";
        }
    else
        {
        endianness = "eLittleEndian";
        }
    sprintf(buffer, "%s::CEncodeDecodeBase::%s", tsa_namespace, endianness);
    return buffer;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_get_instance_name
 
    Purpose: Retrieves the name of the encoder/decoder helper class instance
 
    Functional Description:
        tsa_get_instance_name returns either "encoder" or "decoder", depending on
        whether the given operation in "Encode" or "Decode", respectively.

    Arguments: 
        operation - [in] The name of the given operation. Must be "Encode" or "Decode".

    Return Values: A pointer to a statically allocated string with the instance name.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_get_instance_name(const char *operation)
    {
    static char instance[20];
    sprintf(instance, "%c%sr", tolower(*operation), operation+1);
    return instance;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_get_class_name
 
    Purpose: Retrieves the name of the encoder/decoder helper class
 
    Functional Description:
        tsa_get_class_name returns either "CEncoder" or "CDecoder", depending on
        whether the given operation is "Encode" or "Decode", respectively. The class
        name is prefixed with the standard TSS Server API namespace qualifiers.

    Arguments: 
        operation - [in] The name of the given operation. Must be "Encode" or "Decode".

    Return Values: A pointer to a statically allocated string with the class name.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_get_class_name(const char *operation)
    {
    static char class_name[20];
    sprintf(class_name, "%s::C%sr", tsa_namespace, operation);
    return class_name;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_get_reference_declaration
 
    Purpose: Returns a declaration of a reference variable for the given item.
 
    Functional Description:
        tsa_get_reference_declaration returns a declaration of a reference variable
        for the given item, which is assumed to be a reference. The declaration
        is of the form "<type> <name>", and no initializer or semicolon is included.

    Arguments: 
        item - [in] The reference item.
        refname - [in] The reference name
        operation - [in] The name of the given operation. Must be "Encode" or "Decode".

    Return Values: A pointer to a statically allocated string with the declaration.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_get_reference_declaration(const autogen_item *item, const char* refname, const char *operation)
    {
    static char ref_decl[100];
    sprintf(ref_decl, "%s::CReference<%s> %s",
            tsa_get_class_name(operation),
            item->length < 0 ? long_typename : ulong_typename,
            refname);
    return ref_decl;
    }

/*------------------------------------------------------------------------------------------------

    Name: tsa_get_reference_usage
 
    Purpose: Returns an expression evaluating to the reference used by the given item.
 
    Functional Description:
        tsa_get_reference_usage returns an expression evaluating to a reference object.
        The expression is either simply the name of a local value defining the
        reference, or an invocation of a lookup of an external reference.

    Arguments: 
        ref - [in] Pointer to reference object
        refname - [in] Name of reference
        operation - [in] The name of the given operation. Must be "Encode" or "Decode".

    Return Values: A pointer to a statically allocated string with the expression.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_get_reference_usage(const autogen_ref* ref, const char* refname, const char *operation)
    {
    static char ref_exp[100];
    if (ref->is_external)
        {
        /* We assume that the reference is unsigned. External references
           and signed references both occur rarely enough to excuse this */
        sprintf(ref_exp, "(%s.LookupNonlocalReference(\"%s\"))", tsa_get_instance_name(operation), refname);
        }
    else
        {
        strcpy(ref_exp, refname);
        }
    return ref_exp;
    }


LOCAL void tsa_generate_reference_transformation(FILE* f, const char* indent, autogen_item* item, const char *operation)
{
    autogen_ref* ref = NULL;
    
    if (item && item->refname) ref = reference_find(item);

    if (ref && ref->type == referenceTypeTransformation)
    {
        switch (ref->algorithm)                         
        {
        case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N:
            fprintf(f, "%s%s = %s.Mul(%d);\n",
                indent,
                tsa_get_reference_declaration(item, ref->name, operation),
                tsa_get_reference_usage(ref, ref->original_name, operation),
                ref->value);
            break;

        case PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH:
            fprintf(f, "%s%s = %s.Add(%d);\n",
                indent,
                tsa_get_reference_declaration(item, ref->name, operation),
                tsa_get_reference_usage(ref, ref->original_name, operation),
                ref->value);
            break;

        case PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH:
            fprintf(f, "%s%s = %s.Div(%d);\n",
                indent,
                tsa_get_reference_declaration(item, ref->name, operation),
                tsa_get_reference_usage(ref, ref->original_name, operation),
                ref->value);
            break;

        case PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH_ROUNDUP:
            fprintf(f, "%s%s = %s.DivRoundUp(%d);\n",
                indent,
                tsa_get_reference_declaration(item, ref->name, operation),
                tsa_get_reference_usage(ref, ref->original_name, operation),
                ref->value);
            break;
        }
    }
}

/*------------------------------------------------------------------------------------------------

    Name: tsa_check_external_reference
 
    Purpose: Checks whether the reference is external, if so, it generates code to publish it.
 
    Functional Description:
        tsa_check_external_reference first checks if the items is a reference that is used
        externally. If not, it simply returns. Otherwise, it generates a statement that
        makes it possible to look up the reference from contained structures.

    Arguments: 
        f - [in,out] The file to write the statement to.
        indent_count - [in] The number of spaces to write before the statement.
        item - [in] The reference item.
        operation - [in] The name of the given operation. Must be "Encode" or "Decode".

    Return Values: A pointer to a statically allocated string with the expression.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_check_external_reference(FILE *f, unsigned int indent_count, autogen_item *item, const char *operation)
{
    autogen_ref_handle* ref_handle = reference_get_handle_from_obj(&item->base);
    autogen_ref* ref = reference_find_from_handle(ref_handle, item->base.name, NULL, FALSE);

    if (ref->is_used_externally)
    {
        fprintf(f, "%s%s.InsertNonlocalReference(\"%s\", %s);\n",
            util_get_spaces(indent_count),
            tsa_get_instance_name(operation),
            item->base.name,
            item->base.name);
    }
}


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_value_args
 
    Purpose: Writes the arguments to encode/decode for numeric values
 
    Functional Description:
        tsa_write_value_args writes a string of the following form:
            "<sign>(<endian>, <length>"
        where
            <sign> - either Signed or Unsigned.
            <endian> - either eBigEndian or eLittleEndian, prefixed with CEncodeDecodeBase.
            <length> - the number of bits in the value.
        An example string is "Unsigned(CEncodeDecodeBase::eBigEndian, 16".

    Arguments: 
        f - [in,out] Stream to write the argument string to.
        item_value - [in] Pointer to the item value to write arguments for.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_value_args(FILE *f,
                                const autogen_item_value *item_value)
    {
    int length = item_value->base.length;
    fprintf(f, "%s(%s, %d",
            (length < 0) ? "Signed" : "Unsigned",    
            tsa_get_endianness(&item_value->base),
            (length < 0) ? -length : length);
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_get_minimum_item_size
 
    Purpose: Retrieves the minimum size of the given item, excluding any aggregation.
 
    Functional Description:
        tsa_get_minimum_item_size checks if the given item is a value, and returns the size
        of the value if so. Otherwise it checks if the given item is a struct, and returns
        32 if so. If none of these conditions are met, this function returns zero and
        prints an error.

    Arguments: 
        item - [in] The item to calculate the minimum size for.

    Return Values: The minimum size of the item in bits.

------------------------------------------------------------------------------------------------*/

LOCAL unsigned int tsa_get_minimum_item_size(const autogen_item *item)
    {
    unsigned int min_size = 0;
    if (item->base.subtype & (AUTOGEN_ITEM_VALUE | AUTOGEN_ITEM_POINTER))
        {
        min_size = item->length < 0 ? -item->length : item->length;
        }
    else if (item->base.subtype & AUTOGEN_ITEM_STRUCT)
        {
        min_size = 32;
        }
    else
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "Final else met in tsa_get_minimum_item_size(). item->base.subtype is 0x%08X",
            item->base.subtype);
        }
    return min_size;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_encode_decode_aggregation
 
    Purpose: Writes an aggregation suffix to the file and returns a pointer to a parameter string.
 
    Functional Description:
        tsa_encode_decode_aggregation checks the item for any aggregation. If so, it writes
        a suffix indicating the aggregation type to the given file. It could be "ArrayRef",
        for instance. It also formats a matching parameter, prefixed with a comma, and returns
        a pointer to a static buffer containing this parameter. It could be the name of the
        reference, for instance. If there's no aggregation, this function does nothing.

    Arguments: 
        f - [in,out] The file to write the aggregation suffix to.
        item - [in] The item to write the aggregation for.
        operation - [in] "Encode" or "Decode".

    Return Values: The return value is of type LOCAL char

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_encode_decode_aggregation(FILE *f, autogen_item *item, const char *operation)
    {
    static const unsigned int value_item_mask = AUTOGEN_ITEM_REF | AUTOGEN_ITEM_VALUE |
                                                AUTOGEN_ITEM_FILLER | AUTOGEN_ITEM_MERGE |
                                                AUTOGEN_ITEM_TIMESTAMP | AUTOGEN_ITEM_POINTER;
    static char finalarg[AUTOGEN_MAX_NAME_LENGTH];
    finalarg[0] = 0;

    switch (item->agg_type)
        {
        case AGG_TYPE_FIXED_SINGLE:
            {
            /* No further arguments */
            }
            break;

        case AGG_TYPE_FIXED_MULTIPLE:
            {
            fprintf(f, "ArrayFixed");
            sprintf(finalarg, ", %d", item->agg_n);
            }
            break;

        case AGG_TYPE_DYNAMIC_REF:
            {
            autogen_ref* ref = reference_find(item);

            fprintf(f, "ArrayRef");
            sprintf(finalarg, ", %s", tsa_get_reference_usage(ref, ref->name, operation));
            }
            break;

        case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
            {
            fprintf(f, "ArrayAMAP");
            if (!(item->base.subtype & value_item_mask))
                {
                sprintf(finalarg, ", %u", tsa_get_minimum_item_size(item));
                }
            }
            break;

        case AGG_TYPE_DYNAMIC_OPTIONAL:
            {
            fprintf(f, "Optional");
            if (!(item->base.subtype & value_item_mask))
                {
                sprintf(finalarg, ", %u", tsa_get_minimum_item_size(item));
                }
            }
            break;

        default:
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Final else met in tsa_encode_decode_aggregation(). item->agg_type is %u",
                item->agg_type);
            }
        }

    return finalarg;
    }

/*------------------------------------------------------------------------------------------------

    Name: tsa_write_encode_decode_item
 
    Purpose: Writes the code used to encode or decode the given item.
 
    Functional Description:
        tsa_write_encode_decode_item writes the code to either encode or
        decode the given item, depending on operation. This code basically
        calls the same method on either the encode or decoder, so it
        only handles the cases that use similar code in the two cases.

    Arguments: 
        f - [in,out] Stream to write the code to.
        indent_count - [in] The number of spaces to indent the code.
        item - [in] Pointer to the item to write the code for.
        operation - [in] Either "Encode" or "Decode".
        filler_replacement - [in,out] TRUE = PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION encountered and active
                                      FALSE = Filler replacement not active

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_encode_decode_item(FILE *f,
                                        unsigned int indent_count,
                                        autogen_item *item,
                                        const char *operation,
                                        int *filler_replacement)
    {
    const char *instance = tsa_get_instance_name(operation);
    const char *indent = util_get_spaces(indent_count);
    switch (item->base.subtype & AUTOGEN_ITEM_ANY)
        {
        case AUTOGEN_ITEM_REF:
            {
            if ((item->base.flag & AUTOGEN_REF_CONST) ||
                item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE)
                {
                fprintf(f, "%s%s = %s.Ref",
                        indent,
                        tsa_get_reference_declaration(item, item->base.name, operation),
                        instance);
                tsa_write_value_args(f, (const autogen_item_value*) item);
                
                /* For ReferenceConst add an extra attribute to the encode/decoder */
                if (item->base.flag & AUTOGEN_REF_CONST)
                    {
                    fprintf(f, ", m_%s", tsa_item_varname(item));
                    }
                fprintf(f, ");\n");
                tsa_check_external_reference(f, indent_count, item, operation);
                }
            else
            if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID)
                {
                fprintf(f, "%s%s.MessageId", indent, instance);
                tsa_write_value_args(f, (const autogen_item_value*) item);
#if (PMD_FILE_FORMAT >= 600)
                fprintf(f, ", %llu);\n", item->seq->base.base_obj->id);
#else
                fprintf(f, ", %u);\n", item->seq->base.base_obj->id);
#endif
                }
            else
            if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID)
                {
                fprintf(f, "%s%s.SubMessageId", indent, instance);
                tsa_write_value_args(f, (const autogen_item_value*) item);
#if (PMD_FILE_FORMAT >= 600)
                fprintf(f, ", %llu);\n", item->seq->base.id);
#else
                fprintf(f, ", %u);\n", item->seq->base.id);
#endif
                }
            else
            if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID)
                {
                fprintf(f, "%s%s.SubBlockId", indent, instance);
                tsa_write_value_args(f, (const autogen_item_value*) item);
#if (PMD_FILE_FORMAT >= 600)
                fprintf(f, ", %llu);\n", item->seq->base.id);
#else
                fprintf(f, ", %u);\n", item->seq->base.id);
#endif
                }
            else
            if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH)
                {
                fprintf(f, "%s%s.SubBlockLength", indent, instance);
                tsa_write_value_args(f, (const autogen_item_value*) item);
                fprintf(f, ");\n");
                }
            else
            if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH ||
                item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_GROUP_ID ||
                item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_ID)
                {
                util_error_line(NULL, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                                "Trace messages are not supported for TSS API");
                fprintf(f, "%s%s.Unsupported(\"Trace messages\");\n",
                        indent, instance);
                }
            else 
            if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_PRIVATE_ID)
                {
                util_error_line(NULL, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                                "Private interfaces are not supported for TSS API");
                fprintf(f, "%s%s.Unsupported(\"Private interfaces\");\n",
                        indent, instance);
                }
            }
            break;

        case AUTOGEN_ITEM_VALUE:
            {
            if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRANSACTION_ID)
                {
                fprintf(f, "%s%s.TransactionId();\n", indent, instance);
                }
            else
                {
                int length = item->length;
                int abs_length = length < 0 ? -length : length;
                const char *sign = length < 0 ? "Signed" : "Unsigned";
                if (item->agg_type == AGG_TYPE_FIXED_SINGLE)
                    {
                    if (prop_has(&(item->base), PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION) && *filler_replacement)
                        {
                        /* PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION is active */
                        indent = util_get_spaces(indent_count + indent_step);
                        }
                    if( strcmp(operation, "Encode") == 0)
                        {
                        fprintf(f, "#ifdef _DEBUG\n");
                            fprintf(f, "%s%s.", indent, instance);
                            tsa_write_value_args(f, (const autogen_item_value*) item);
                            fprintf(f, ", m_%s", tsa_item_varname(item));
                            fprintf(f, ", \"%s\");\n", tsa_item_varname(item));
                        fprintf(f, "#else\n");
                            fprintf(f, "%s%s.", indent, instance);
                            tsa_write_value_args(f, (const autogen_item_value*) item);
                            fprintf(f, ", m_%s", tsa_item_varname(item));
                            fprintf(f, ");\n");
                        fprintf(f, "#endif\n");
                        }
                    else
                        {
                        fprintf(f, "%s%s.", indent, instance);
                        tsa_write_value_args(f, (const autogen_item_value*) item);
                        fprintf(f, ", m_%s", tsa_item_varname(item));
                        fprintf(f, ");\n");
                        }
                    if (prop_has(&(item->base), PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION) && *filler_replacement)
                        {
                        /* PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION is active */
                        indent = util_get_spaces(indent_count);
                        fprintf(f, "%s}\n", indent);

                        /* Filler replacement not to be active anymore */
                        *filler_replacement = FALSE;
                        }
                    }
                else
                    {
                    tsa_generate_reference_transformation(f, indent, item, operation);

                    fprintf(f, "%s%s.", indent, instance);
                    fprintf(f, "Value");
                    fprintf(f, "(&%s::%s, %s, %d, m_%s%s",
                            tsa_get_class_name(operation),
                            sign,
                            tsa_get_endianness(item),
                            abs_length,
                            tsa_item_varname(item),
                            tsa_encode_decode_aggregation(f, item, operation));
                    fprintf(f, ");\n");
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_FILLER:
            {
            if (item->base.flag & AUTOGEN_FILLER_IS_REPLACED)
                {
                /* PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION is active */
                fprintf(f, "%sif (%s::%s::ResourceVersion < Tss::ServerApi::CVersion(%d,%d))\n", indent, tsa_namespace, s_res_namespace, item->base.ver.to[0], item->base.ver.to[1]);
                fprintf(f, "%s{\n", indent);
                indent = util_get_spaces(indent_count + indent_step);
                }

            if (item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
                {
                fprintf(f, "%s%s.DynamicFiller(%d);\n", indent, instance, item->length);
                }
            else
                {
                fprintf(f, "%s%s.StaticFiller(%d);\n",
                        indent, instance, item->agg_n * item->length);
                }
            }

            if (item->base.flag & AUTOGEN_FILLER_IS_REPLACED)
                {
                /* PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION is active */
                indent = util_get_spaces(indent_count);
                fprintf(f, "%s}\n", indent);
                fprintf(f, "%selse\n", indent);
                fprintf(f, "%s{\n", indent);

                /* Filler replacement is marked to be active */
                *filler_replacement = TRUE;
                }

            break;

        case AUTOGEN_ITEM_LST:
            {
            if (item->base.flag & AUTOGEN_LST_SBID)
                {
                int length = (item->base.flag & AUTOGEN_LST_SB_HAVE_BYTE_IDS) ? 8 : 16;
                if (item->agg_type == AGG_TYPE_FIXED_SINGLE)
                    {
                    fprintf(f, "%s%s.Unsupported(\"Single element lists\");\n", indent, instance);
                    }
                else
                    {
                    tsa_generate_reference_transformation(f, indent, item, operation);

                    fprintf(f, "%s%s.Value", indent, instance);
                    fprintf(f, "(&%s::Unsigned, %s::CEncodeDecodeBase::eBigEndian, %d, m_%s%s);\n",
                            tsa_get_class_name(operation),
                            tsa_namespace,
                            length,
                            tsa_item_varname(item),
                            tsa_encode_decode_aggregation(f, item, operation));
                    }
                }
            else if (item->base.flag & AUTOGEN_LST_FTD)
                {
                util_error_line(NULL, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                    "FTD lists are not supported at this time");
                fprintf(f, "%s%s.Unsupported(\"FTD lists\");\n", indent, instance);
                }
            else if (item->base.flag & AUTOGEN_LST_PPC)
                {
                util_error_line(NULL, 0, AUTOGEN_ERROR_INFO, AUTOGEN_ENV_LOCAL, 0,
                    "PPC lists are not supported at this time");
                fprintf(f, "%s%s.Unsupported(\"PPC lists\");\n", indent, instance);
                }
            else
                {
                /* The specialisations for encoder and decoder are expected to handle SBDATA */
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Unexpected flag combination 0x%08X met in tsa_write_encode_decode_item().",
                    item->base.flag);
                fprintf(f, "%s%s.Unsupported(\"Unknown list type\");\n", indent, instance);
                }
            }
            break;

        case AUTOGEN_ITEM_STRING:
            {
            autogen_item_string *item_string = (autogen_item_string *) item;
            char common_params[200];
            strcpy(common_params, tsa_get_endianness(item));
            sprintf(common_params+strlen(common_params), ", %s::", tsa_get_class_name(operation));

            if(item->base.flag & AUTOGEN_STRING_ASCII)
                sprintf(common_params+strlen(common_params), "eASCII");
            else
            if(item->base.flag & AUTOGEN_STRING_BCD)
                sprintf(common_params+strlen(common_params), "eBCD");
            else
            if(item->base.flag & AUTOGEN_STRING_UTF8)
                sprintf(common_params+strlen(common_params), "eUTF8");
            else
            if(item->base.flag & AUTOGEN_STRING_UNICODE)
                sprintf(common_params+strlen(common_params), "eUnicode");
            else
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Unknown string type. Defaulting to ASCII. Flag combination 0x%08X.", item->base.flag);
                sprintf(common_params+strlen(common_params), "eASCII");
            }

            sprintf(common_params+strlen(common_params), ", %s",
                    (item->base.flag & AUTOGEN_STRING_ZERO_TERMINATED) ? "true" : "false");
            sprintf(common_params+strlen(common_params), ", m_%s", tsa_item_varname(item));

            switch (item->agg_type)
                {
                case AGG_TYPE_FIXED_SINGLE:
                case AGG_TYPE_FIXED_MULTIPLE:
                    {
                    fprintf(f, "%s%s.StringFixed(%s, %d);\n",
                            indent, instance, common_params, item_string->length);
                    }
                    break;

                case AGG_TYPE_DYNAMIC_REF:
                    {
                    autogen_ref* ref = reference_find(&item_string->base);

                    tsa_generate_reference_transformation(f, indent, &item_string->base, operation);

                    fprintf(f, "%s%s.StringRef(%s, %s);\n",
                            indent,
                            instance,
                            common_params,
                            tsa_get_reference_usage(ref, ref->name, operation));
                    }
                    break;

                case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
                    {
                    fprintf(f, "%s%s.StringALAP(%s);\n", indent, instance, common_params);
                    }
                    break;

                case AGG_TYPE_DYNAMIC_ZEROTERMINATED:
                    {
                    fprintf(f, "%s%s.StringZero(%s);\n", indent, instance, common_params);
                    }
                    break;

                default:
                    {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Final else met in tsa_write_encode_decode_item(). item->agg_type is %u",
                        item->agg_type);
                    fprintf(f, "%s%s.Unsupported(\"Unknown string length type\");\n", indent, instance);
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_STRUCT:
            {
            autogen_item_struct *item_struct = (autogen_item_struct *) item;

            /* Create array of sequence pointers for different versions */
            autogen_it str_it = INIT_ITERATOR;
            autogen_seq *str;
            unsigned int str_count;

            str_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
            str_it.obj.name = item_struct->seqname;
            str_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            str_it.ver      = &item->seq->base.ver;

            str_count = autogen_obj_count_in_list(&str_it, &item->seq->base.res->seq_list);

            str = (autogen_seq*)autogen_obj_find_in_list(&str_it, &item->seq->base.res->seq_list);
            /* Write code to encode/decode each version */
            while (str)
                {
                /* Check whether we need to include conditional encoding/decoding */
                const autogen_ver *seq_ver = &str->base.ver;
                int check_version = FALSE;
                if (str_count > 1 && !tsa_is_item_aggregated(item))
                    {
                    /* We have more than one version of inlined structures */
                    check_version = TRUE;
                    }

                /* Write the code to do the version checking */
                if (check_version)
                    {
                    int first_factor = TRUE;
                    fprintf(f, "%sif (", indent);
                    if ((seq_ver->type & AUTOGEN_OBJ_VERSION_FROM) &&
                        autogen_ver_comp(seq_ver->from, item->seq->base.ver.from) & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL))
                        {
                        fprintf(f, "GetIsiVersion() >= %s::CVersion(%hu, %hu)",
                                tsa_namespace, seq_ver->from[0], seq_ver->from[1]);
                        first_factor = FALSE;
                        }
                    if ((seq_ver->type & AUTOGEN_OBJ_VERSION_TO) &&
                        autogen_ver_comp(seq_ver->to, item->seq->base.ver.to) & (AUTOGEN_VER_NEWER | AUTOGEN_VER_EQUAL))
                        {
                        if (!first_factor)
                            {
                            fprintf(f, " && ");
                            }
                        fprintf(f, "GetIsiVersion() < %s::CVersion(%hu, %hu)",
                                tsa_namespace, seq_ver->to[0], seq_ver->to[1]);
                        }
                    fprintf(f, ")\n");
                    }

                /* Write the code to do the encoding/decoding */
                fprintf(f, "%s{\n", indent);
                if (*operation == 'E' && item->agg_type == AGG_TYPE_FIXED_SINGLE)
                    {
                    char initname[AUTOGEN_MAX_NAME_LENGTH+50];
                    
                    if( (prop_has(&(item->base), PROPERTY_PMD_PARAMETER)) && (item->seq != NULL))
                    {
                        strcpy(initname, tsa_initname( tsa_create_single_parameter(item->seq, item)));
                    }
                    else
                    {
                        sprintf(initname, "m_b%sInitialized", tsa_name(item->varname, NULL));
                    }
                    
                    if ((check_version) || ((seq_ver->to[0]) || (seq_ver->to[1])))
                        {
                        sprintf(initname+strlen(initname), "_%03hd_%03hd",
                                seq_ver->from[0], seq_ver->from[1]);
                        }
                    fprintf(f, "%s    CheckInit(%s, encoder.GetName());\n",
                            indent, initname);
                    }

                tsa_generate_reference_transformation(f, indent, item, operation);

                fprintf(f, "%s    %s.Structure", indent, instance);
                fprintf(f, "(m_%s%s", 
                        tsa_struct_name(item_struct, str, FALSE),
                        tsa_encode_decode_aggregation(f, item, operation));
                fprintf(f, ");\n");
                if (*operation == 'D' && item->agg_type == AGG_TYPE_FIXED_SINGLE)
                    {
                    char initname[AUTOGEN_MAX_NAME_LENGTH+50];
                    if( (prop_has(&(item->base), PROPERTY_PMD_PARAMETER)) && (item->seq != NULL))
                    {
                        strcpy(initname, tsa_initname( tsa_create_single_parameter(item->seq, item)));
                    }
                    else
                    {
                        sprintf(initname, "m_b%sInitialized", tsa_name(item->varname, NULL));
                    }
                    if ((check_version) || ((seq_ver->to[0]) || (seq_ver->to[1])))
                        {
                        sprintf(initname+strlen(initname), "_%03hd_%03hd",
                                seq_ver->from[0], seq_ver->from[1]);
                        }
                    fprintf(f, "%s    %s = true;\n", indent, initname);
                    }
                fprintf(f, "%s}\n", indent);

                str = (autogen_seq*)autogen_obj_find_next_in_list(&str_it);
                }
            }
            break;

        case AUTOGEN_ITEM_CHOICE:
            {
            autogen_obj* item_case = (autogen_obj*)((autogen_item_choice*)item)->default_case;

            autogen_it case_it = INIT_ITERATOR;
            autogen_obj* case_item;

            case_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
            case_it.ver     = &item->base.ver;


            if (item_case && item_case->child_list.n_obj > 0)
                {
                case_item = autogen_obj_find_in_list(&case_it, &item_case->child_list);
                fprintf(f, "%s{ // Default branch of choice \"%s\":\n", indent, item->parname);
                while (case_item) /* a default case found */
                    {
                    tsa_write_encode_decode_item(f, indent_count+indent_step, (autogen_item*)case_item, operation, filler_replacement);

                    case_item = autogen_obj_find_next_in_list(&case_it);
                    }
                fprintf(f, "%s}\n", indent);
                }
            else
                {
                fprintf(f, "%s// Choice \"%s\" has no items in default branch\n", indent, item->parname);
                }
            }
            break;

        case AUTOGEN_ITEM_POINTER:
            {
            if (prop_has(&(item->base), PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION) && *filler_replacement)
                {
                /* PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION is active */
                indent = util_get_spaces(indent_count + indent_step);
                }

            fprintf(f, "%s%s.Unsigned(%s, %u, m_%s);\n",
                    indent,
                    instance,
                    tsa_get_endianness(item),
                    item->length,
                    tsa_item_varname(item));

            if (prop_has(&(item->base), PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION) && *filler_replacement)
                {
                /* PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION is active */
                indent = util_get_spaces(indent_count);
                fprintf(f, "%s}\n", indent);

                /* Filler replacement not to be active anymore */
                *filler_replacement = FALSE;
                }
            }
            break;

        default:
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in tsa_write_encode_decode_item(). item->base.subtype is 0x%08X",
                item->base.subtype);
            fprintf(f, "%s%s.Unsupported(\"Unknown item type\");\n", indent, instance);
            }
            break;
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_size_calculation
 
    Purpose: Writes code to calculate the sum of container sizes to the given file.
 
    Functional Description:
        tsa_write_size_calculation writes an expression calculating the sum of the sizes of
        the member vectors corresponding to the referenced sequences in the given list.
        A line feed and suitable indent is included between the terms.

    Arguments: 
        f - [in,out] Stream pointer to write the size calculation code to.
        indent_count - [in] The number of spaces to indent terms except the first.
        seq_array - [in] Array of sequences to write calculation for.
        seq_count - [in] Size of sequence array.

    Note:
        The seq_array pointer may be NULL if seq_count equals 0.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_size_calculation(FILE *f,
                                      unsigned int indent_count,
                                      const autogen_seq * const * seq_array,
                                      unsigned int seq_count)
    {
    if (seq_count == 0)
        {
        fprintf(f, "0");
        }
    else
        {
        unsigned int seq_index = 0;
        for (seq_index = 0; seq_index < seq_count; seq_index++)
            {
            /* Only print separator if it's not the first */
            if (seq_index > 0)
                {
                fprintf(f, " +\n%s", util_get_spaces(indent_count));
                }

            if(seq_array[seq_index]->base.flag & AUTOGEN_OBJ_IS_SHARED_EXTERNAL)  /* Make different versioning if shared resource */
                {
                const autogen_seq* tra_seq = seq_array[seq_index];
                autogen_it sb_it = INIT_ITERATOR;
                autogen_obj* sb;
                int first = TRUE;

                sb_it.typemask = AUTOGEN_OBJ_SB;
                sb_it.obj.name = tra_seq->base.name;

                sb = autogen_obj_find_in_list(&sb_it, &tra_seq->base.res->seq_list);
                while (sb)
                    {
                    if (!first)
                        {
                        fprintf(f, " +\n%s", util_get_spaces(indent_count));
                        }
                    else
                        {
                        first = FALSE;
                        }

                        {
                        char version_suffix[AUTOGEN_MAX_NAME_LENGTH];
                        if ((sb->ver.from[0] != 0) || sb->ver.from[1] != 0 || util_has_multiple_versions(sb))
                            {
                            sprintf(version_suffix , "_%03hd_%03hd", sb->ver.from[0], sb->ver.from[1]);
                            }
                        else
                            {
                            sprintf(version_suffix , "");
                            }

                        fprintf(f, "m_%s%s.size()", tsa_classname(tra_seq, TSA_VEC_PREFIX), version_suffix);
                        }
                    sb = autogen_obj_find_next_in_list(&sb_it);
                    }
                }
            else
                {

            /* Write the term for the current version */
                    fprintf(f, "m_%s.size()", tsa_classname(seq_array[seq_index], TSA_VEC_PREFIX | TSA_VERSION_SUFFIX));
            }
        }
    }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_encode_aggregation
 
    Purpose: Writes code to handle the reference for aggregated values.
 
    Functional Description:
        tsa_write_encode_aggregation checks the type of aggregation and
        writes code to handle it appropriately.

    Arguments: 
        f - [in] The file to write the code to.
        indent_count - [in] The number of spaces to indent the code.
        item - [in] The item to write the aggregation code for.
        seq_array - [in] Array of sequences to write calculation for.
        seq_count - [in] Number of sequences in seq_array

    Return Values: The return value is of type LOCAL void

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_encode_aggregation(FILE *f, unsigned int indent_count, autogen_item *item, const autogen_seq * const * seq_array, unsigned int seq_count)
    {
    const char *indent = util_get_spaces(indent_count);
    switch (item->agg_type)
        {
        case AGG_TYPE_FIXED_SINGLE:
        case AGG_TYPE_FIXED_MULTIPLE:
            {
            if (item->agg_n != 1)
                {
                /* Generate code to check the container sizes count */
                fprintf(f, "%sif (", indent);
                tsa_write_size_calculation(f, indent_count + indent_step, seq_array, seq_count);
                fprintf(f, " != %dU)\n", item->agg_n);
                fprintf(f, "%s{\n", indent);
                fprintf(f, "%s    encoder.ThrowWrongFixedCount(%u, ", indent, item->agg_n);
                tsa_write_size_calculation(f, indent_count + 2*indent_step, seq_array, seq_count);
                fprintf(f, ");\n");
                fprintf(f, "%s}\n", indent);
                }
            }
            break;

        case AGG_TYPE_DYNAMIC_REF:
            {
            autogen_ref* ref = reference_find(item);
            const char *ref_usage = NULL;

            tsa_generate_reference_transformation(f, indent, item, "Encode");

            /* Generate code to set the reference appropriately */
            ref_usage = tsa_get_reference_usage(ref, ref->name, "Encoding");
            fprintf(f, "%s%s.Set(", indent, ref_usage);
            tsa_write_size_calculation(f, indent_count+strlen(ref_usage)+5, seq_array, seq_count);
            fprintf(f, ");\n");
            }
            break;

        case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
            {
            /* Ignore number of sequences for encoding */
            }
            break;

        case AGG_TYPE_DYNAMIC_OPTIONAL:
            {
            /* Generate code to check the sequence count */
            fprintf(f, "%sif (", indent);
            tsa_write_size_calculation(f, indent_count + indent_step, seq_array, seq_count);
            fprintf(f, " > 1U)\n");
            fprintf(f, "%s{\n", indent);
            fprintf(f, "%s    encoder.ThrowWrongOptionalCount(", indent);
            tsa_write_size_calculation(f, indent_count + 2*indent_step, seq_array, seq_count);
            fprintf(f, ");\n");
            fprintf(f, "%s}\n", indent);
            }
            break;

        default:
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Final else met in tsa_write_encode_item(). item->agg_type is %u",
                item->agg_type);
            fprintf(f, "%sencoder.Unsupported(\"Unknown aggregation type\");\n", indent);
            }
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_encode_item
 
    Purpose: Writes code to encode the given item to the given file.
 
    Functional Description:
        tsa_write_encode_item writes code to encode the given item. If the given item
        is not handled separately when encoding and decoding, the work is delegated to
        tsa_write_encode_decode_item.

    Arguments: 
        f - [in,out] Stream pointer to write the code to.
        indent_count - [in] Number of spaces to indent code lines.
        item - [in] The item to write encoding code for.
        filler_replacement - [in,out] TRUE = PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION encountered and active
                                      FALSE = Filler replacement not active

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_encode_item(FILE *f,
                                 unsigned int indent_count,
                                 autogen_item *item,
                                 int *filler_replacement)
    {
    const char *indent = util_get_spaces(indent_count);
    switch (item->base.subtype & AUTOGEN_ITEM_ANY)
        {
        case AUTOGEN_ITEM_LST:
            {
            if (item->base.flag & AUTOGEN_LST_SBDATA)
                {
                autogen_seq_ref *ref_list = (autogen_seq_ref*)autogen_obj_get_first_in_list(&item->base.child_list);

                /* Create array of sequence pointers for reference list */
                autogen_it all_it = INIT_ITERATOR;
                unsigned int ref_count = autogen_obj_count_in_list(&all_it, &item->base.child_list);
                autogen_seq **ref_array = (autogen_seq **)pmd_heap_alloc(ref_count * sizeof(autogen_seq *));
                unsigned int ref_index = 0;
                for (ref_list = (autogen_seq_ref*)autogen_obj_get_first_in_list(&item->base.child_list);
                     ref_list != NULL;
                     ref_list = (autogen_seq_ref*)ref_list->base.next)
                    {
                    ref_array[ref_index++] = ref_list->seqptr;
                    }

                /* Write code to check/set the aggregation count */
                tsa_write_encode_aggregation(f, indent_count, item, ref_array, ref_count);

                /* Generate code to encode each sub block container */
                for (ref_index = 0; ref_index < ref_count; ref_index++)
                    {
                    if (ref_array[ref_index]->base.flag & AUTOGEN_OBJ_IS_SHARED_EXTERNAL)  /* Make different versioning if shared resource */
                        {
                        autogen_seq* tra_seq = ref_array[ref_index];
                        autogen_it sb_it = INIT_ITERATOR;
                        autogen_obj* sb;

                        sb_it.typemask = AUTOGEN_OBJ_SB;
                        sb_it.obj.name = tra_seq->base.name;

                        sb = autogen_obj_find_in_list(&sb_it, &tra_seq->base.res->seq_list);
                        while (sb)
                            {
                            char version_suffix[AUTOGEN_MAX_NAME_LENGTH];
                            if (sb->ver.from[0] != 0 || sb->ver.from[1] != 0 || util_has_multiple_versions(sb))
                                {
                                sprintf(version_suffix , "_%03hd_%03hd", sb->ver.from[0], sb->ver.from[1]);
                                }
                            else
                                {
                                sprintf(version_suffix , "");
                                }

                            fprintf(f, "%sencoder.EncodeSubBlockContainer(m_%s%s, false);\n",
                                indent, tsa_classname(tra_seq, TSA_VEC_PREFIX), version_suffix);

                            sb = autogen_obj_find_next_in_list(&sb_it);
                            }
                        }
                    else
                        {
                    fprintf(f, "%sencoder.EncodeSubBlockContainer(m_%s);\n",
                            indent, tsa_classname(ref_array[ref_index], TSA_VERSION_SUFFIX | TSA_VEC_PREFIX));
                    }
                }
                }
            else
                {
                tsa_write_encode_decode_item(f, indent_count, item, "Encode", filler_replacement);
                }
            }
            break;

        case AUTOGEN_ITEM_MERGE:
            {
            if (item->agg_type != AGG_TYPE_FIXED_SINGLE)
                {
                fprintf(f, "%sencoder.Value", indent);
                fprintf(f, "(&%s::CEncoder::Unsigned, %s, %d, m_%s%s", /* Add &*/
                        tsa_namespace,
                        tsa_get_endianness(item),
                        item->length,
                        tsa_item_varname(item),
                        tsa_encode_decode_aggregation(f, item, "Encode"));
                fprintf(f, ");\n");
                }
            else
                {
                autogen_item* merge_item = NULL;
                int merge_offset = item->length;
                fprintf(f, "\n");
                fprintf(f, "%s// Merged field \"%s\"\n", indent, item->parname);
                fprintf(f, "%sencoder.Merged() = 0;\n", indent);
                for (merge_item = (autogen_item*)autogen_obj_get_first_in_list(&item->base.child_list);
                     merge_item != NULL;
                     merge_item = (autogen_item*)merge_item->base.next)
                    {
                    merge_offset -= merge_item->length;
                    if (merge_item->base.subtype & AUTOGEN_ITEM_FILLER)
                        {
                        fprintf(f, "%sencoder.Merged() <<= %u;\n", indent, merge_item->length);
                        }
                    else if (merge_item->base.subtype == AUTOGEN_ITEM_REF)
                        {
                        fprintf(f, "%s%s(&encoder, %s, %u, %u, %u);\n", 
                                indent,
                                tsa_get_reference_declaration(merge_item, merge_item->base.name, "Encode"),
                                tsa_get_endianness(item),
                                abs(item->length),
                                merge_item->length,
                                merge_offset);
                        tsa_check_external_reference(f, indent_count, merge_item, "Encode");
                        fprintf(f, "%sencoder.Merged() <<= %u;\n", indent, merge_item->length);
                        }
                    else
                        {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(f, "%sencoder.Merged() = (encoder.Merged() << %u) | (m_%s & 0x%08llX);\n",
                                indent,
                                merge_item->length,
                                tsa_item_varname(merge_item),
                                (1ULL << merge_item->length) - 1);
#else
                        fprintf(f, "%sencoder.Merged() = (encoder.Merged() << %u) | (m_%s & 0x%08X);\n",
                                indent,
                                merge_item->length,
                                tsa_item_varname(merge_item),
                                (1U << merge_item->length) - 1);
#endif
                        }
                    }
                fprintf(f, "%sencoder.Unsigned(%s, %d, encoder.Merged());\n",
                        indent, tsa_get_endianness(item), item->length);
                fprintf(f, "\n");
                }
            }
            break;

        default:
            {
            /* If there's nothing special for encoding, use the generic output */
            tsa_write_encode_decode_item(f, indent_count, item, "Encode", filler_replacement);
            }
            break;
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_encode

    Purpose: Writes the Encode method for the given sequence to the given files.

    Functional Description:
        tsa_write_encode writes the declaration of Encode to the given header file and writes
        the implementation of Encode to the given implementation file. The two stream pointers
        may point to the same stream.

    Arguments: 
        f_h - [in,out] Stream pointer to write declaration to.
        f_c - [in,out] Stream pointer to write implementation to.
        seq - [in] The sequence to write the Encode method on.
        par_list - [in] List of parameters created for this class.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_encode(FILE *f_h, FILE *f_c, autogen_seq *seq, tsa_parameter *par_list)
    {
    /* Constants for printing both in header and source file */
    autogen_item *item = NULL;
    int filler_replacement = FALSE;
    char indent[50] = "";
    const char *end_decl = ";";
    char argument[100] = "";
    const char *function_name = "GetData";
    if (f_h == f_c)
        {
        sprintf(indent, "%s    ", base_indent_string);
        end_decl = "";
        }

    /* Format argument text if we need a parent argument */
    if (seq->base.type != AUTOGEN_OBJ_MSG)
        {
        sprintf(argument, "%s::CEncoder *pParent", tsa_namespace);
        }

    /* Write the declaration of the helper in the header file */
    fprintf(f_h, "%s    virtual const counting_ptr<%s > GetData()%s\n",
            base_indent_string, byte_array_typename, end_decl);

    /* Also write a prototype in the implementation file, if different */
    if (f_h != f_c)
        {
        fprintf(f_c, "\n");
        fprintf(f_c, "const counting_ptr<%s > %s::GetData()\n",
                byte_array_typename, s_scoped_classname);
        }
    fprintf(f_c, "%s{\n", indent);

    /* Check whether we need an Encode method. In that case, we write delegation
       code into the currently "open" GetData, close it, and open a new "Encode"
       method. The actual decoding code will then be written there. */
    if (seq->base.type != AUTOGEN_OBJ_MSG)
        {
        /* Write delegation code and close the current GetData method */
        fprintf(f_c, "%s    return Encode(NULL);\n", indent);
        fprintf(f_c, "%s}\n", indent);
        function_name = "Encode";

        /* Create an Encode method */
        fprintf(f_h, "%s    const counting_ptr<%s > %s(%s::CEncoder *pParent)%s\n",
                base_indent_string,
                byte_array_typename,
                function_name,
                tsa_namespace,
                end_decl);
        if (f_h != f_c)
            {
            fprintf(f_c, "\n");
            fprintf(f_c, "const counting_ptr<%s > %s::%s(%s::CEncoder *pParent)\n",
                    byte_array_typename,
                    s_scoped_classname,
                    function_name,
                    tsa_namespace);
            }
        fprintf(f_c, "%s{\n", indent);
        }

    /* Write the declaration of the helper instance in the implementation file */
    fprintf(f_c, "%s    %s::CEncoder encoder(\"%s::%s()\",\n",
            indent, tsa_namespace, s_scoped_classname, function_name);
    fprintf(f_c, "%s                         %sGetIsiVersion(), %s::CEncoder::",
            indent, util_get_spaces(sizeof(tsa_namespace)-3), tsa_namespace);
    if (seq->base.type == AUTOGEN_OBJ_MSG)
        {
#if (PMD_FILE_FORMAT >= 600)
        fprintf(f_c, "eMessage, %llu", s_current_res->base.id);
#else
        fprintf(f_c, "eMessage, %u", s_current_res->base.id);
#endif
        }
    else if (seq->base.type == AUTOGEN_OBJ_SB)
        {
        fprintf(f_c, "eSubBlock, 0, pParent");
        }
    else
        {
        fprintf(f_c, "eStructure, 0, pParent");
        }
    fprintf(f_c, "%s);\n", indent);

    /* Write checks for uninitialised fields */
    while (par_list)
        {
        if (!par_list->initvalue)
            {
            /* Inlined structures are handled specially while encoding */
            if (par_list->item->base.subtype != AUTOGEN_ITEM_STRUCT &&
                !(tsa_is_parameter_aggregated(par_list)))
                {
                fprintf(f_c, "%s    CheckInit(%s, encoder.GetName());\n",
                        indent, tsa_initname(par_list));
                }
            }
        par_list = par_list->next;
        }

    /* Write the encoding of each item */
    for (item = (autogen_item*)autogen_obj_get_first_in_list(&seq->base.child_list); item != NULL; item = (autogen_item*)item->base.next)
        {
        tsa_write_encode_item(f_c, strlen(indent)+indent_step, item, &filler_replacement);
        }

    /* Write the final part of the function */
    fprintf(f_c, "%s    return encoder.Finalize();\n", indent);
    fprintf(f_c, "%s}\n", indent);
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_decode_item
 
    Purpose: Writes code to decode the given item to the given file.
 
    Functional Description:
        tsa_write_decode_item writes code to decode the given item. If the given item
        is not handled separately when encoding and decoding, the work is delegated to
        tsa_write_encode_decode_item.

    Arguments: 
        f - [in,out] Stream pointer to write the code to.
        indent_count - [in] Number of spaces to indent code lines.
        item - [in] The item to write decoding code for.
        filler_replacement - [in,out] TRUE = PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION encountered and active
                                      FALSE = Filler replacement not active

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_decode_item(FILE *f, unsigned int indent_count, autogen_item *item, int *filler_replacement)
    {
    const char *indent = util_get_spaces(indent_count);
    switch (item->base.subtype)
        {
        case AUTOGEN_ITEM_LST:
            {
            if (item->base.flag & AUTOGEN_LST_SBDATA)
                {
                const autogen_obj *ref_list = autogen_obj_get_first_in_list(&item->base.child_list);

                switch (item->agg_type)
                    {
                    case AGG_TYPE_FIXED_SINGLE:
                    case AGG_TYPE_FIXED_MULTIPLE:
                        {
                        /* A fixed for loop */
                        fprintf(f, "%sfor (size_t cntSbData = %d; cntSbData > 0; cntSbData--)\n",
                                indent, item->agg_n);
                        }
                        break;

                    case AGG_TYPE_DYNAMIC_REF:
                        {
                        autogen_ref* ref = reference_find(item);

                        tsa_generate_reference_transformation(f, indent, item, "Decode");

                        /* A for loop using the reference */
                        fprintf(f, "%sfor (size_t cnt%s = %s.Get(); cnt%s > 0; cnt%s--)\n",
                                indent,
                                ref->name,
                                tsa_get_reference_usage(ref, ref->name, "Decode"),
                                ref->name,
                                ref->name);
                        }
                        break;

                    case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
                        {
                        /* A while loop checking remaining bytes */
                        fprintf(f, "%swhile (decoder.GetRemainingBytes() >= 4)\n", indent);
                        }
                        break;
            
                    case AGG_TYPE_DYNAMIC_OPTIONAL:
                        {
                        /* An if statement checking remaining bytes */
                        fprintf(f, "%sif (decoder.GetRemainingBytes() >= 4)\n", indent);
                        }
                        break;

                    default:
                        {
                        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                            "Final else met in tsa_write_decode_item(). item->agg_type is %u",
                            item->agg_type);
                        fprintf(f, "%sdecoder.Unsupported(\"Unknown aggregation type\");\n", indent);
                        break;
                        }
                    }

                fprintf(f, "%s{\n", indent);
                fprintf(f, "%s    %s id = decoder.GetSubBlockId(%d);\n",
                        indent, ulong_typename,
                        (item->base.flag & AUTOGEN_LST_SB_HAVE_WORD_IDS) ? 16 : 8);
                fprintf(f, "%s   ", indent);
                for ( ; ref_list != NULL; ref_list = ref_list->next)
                    {
                    /* Write ID check, in different depending on the object has multible versions */
                    autogen_seq* sb_as_seq = ((autogen_seq_ref*)ref_list)->seqptr;
                    autogen_obj* sb_as_obj = &sb_as_seq->base;

                    if (((const autogen_seq_ref*)ref_list)->base.flag & AUTOGEN_OBJ_IS_SHARED_EXTERNAL)  /* Make different versioning if shared resource */
                        {
                        autogen_seq* sb_current = ((const autogen_seq_ref*)ref_list)->seqptr;
                        autogen_it sb_it = INIT_ITERATOR;
                        autogen_obj* sb = NULL;

                        sb_it.typemask = AUTOGEN_OBJ_SB;
                        sb_it.obj.name = sb_current->base.name;

                        sb = autogen_obj_find_in_list(&sb_it, &sb_current->base.res->seq_list);
                        while (sb)
                            {
                            char version_suffix[AUTOGEN_MAX_NAME_LENGTH];
                            if (sb->ver.from[0] != 0 || sb->ver.from[1] != 0 || util_has_multiple_versions(sb))
                                {
                                sprintf(version_suffix , "_%03hd_%03hd", sb->ver.from[0], sb->ver.from[1]);
                                }
                            else
                                {
                                sprintf(version_suffix , "");
                                }

                            {
                            char strVersion[AUTOGEN_MAX_NAME_LENGTH];
                            strcpy(strVersion, tsa_namespace);
                            strcat(strVersion, "::");
                            if(prop_has(&(sb_as_seq->base.res->base), PROPERTY_TSA_NAMESPACE))
                                {
                                strcat(strVersion, prop_get_string(&(sb_as_seq->base.res->base), PROPERTY_TSA_NAMESPACE));
                                }
                            else
                                {
                                strcat(strVersion, tsa_name(sb_as_seq->base.res->resnameshort_l, NULL));
                                }
                            strcat(strVersion, shared_namespace_suffix);
                            strcat(strVersion, "::ResourceVersion");

#if (PMD_FILE_FORMAT >= 600)
                            fprintf(f, " if ((id == %llu) && (%s >= CVersion(%d,%d)) && (%s < CVersion(%d,%d)))\n",  
                                                ((const autogen_seq_ref*)ref_list)->seqptr->base.id, strVersion, sb->ver.from[0], sb->ver.from[1], strVersion, sb->ver.to[0], sb->ver.to[1]);
#else
                            fprintf(f, " if ((id == %u) && (%s >= CVersion(%d,%d)) && (%s < CVersion(%d,%d)))\n",  
                                                ((const autogen_seq_ref*)ref_list)->seqptr->base.id, strVersion, sb->ver.from[0], sb->ver.from[1], strVersion, sb->ver.to[0], sb->ver.to[1]);
#endif
                            }

                            fprintf(f, "%s        decoder.DecodeSubBlock(m_%s%s, false);\n",
                                    indent,
                                    tsa_classname(sb_current, TSA_VEC_PREFIX), version_suffix);
                            fprintf(f, "%s    else", indent);

                            sb = autogen_obj_find_next_in_list(&sb_it);
                            }
                        }
                    else
                        {
                        if(util_has_multiple_versions(sb_as_obj))
                        {
#if (PMD_FILE_FORMAT >= 600)
                            fprintf(f, " if ((id == %llu) && (GetIsiVersion() >= CVersion(%d,%d)) && (GetIsiVersion() < CVersion(%d,%d)))\n",  
                                                ((const autogen_seq_ref*)ref_list)->seqptr->base.id,
                                                sb_as_obj->ver.from[0], sb_as_obj->ver.from[1],
                                                sb_as_obj->ver.to[0], sb_as_obj->ver.to[1]);
#else
                            fprintf(f, " if ((id == %u) && (GetIsiVersion() >= CVersion(%d,%d)) && (GetIsiVersion() < CVersion(%d,%d)))\n",  
                                                ((const autogen_seq_ref*)ref_list)->seqptr->base.id,
                                                sb_as_obj->ver.from[0], sb_as_obj->ver.from[1],
                                                sb_as_obj->ver.to[0], sb_as_obj->ver.to[1]);
#endif
                        }
                        else
                        {
#if (PMD_FILE_FORMAT >= 600)
                            fprintf(f, " if (id == %llu)\n", ((const autogen_seq_ref*)ref_list)->seqptr->base.id);
#else
                            fprintf(f, " if (id == %u)\n", ((const autogen_seq_ref*)ref_list)->seqptr->base.id);
#endif
                        }

                        fprintf(f, "%s        decoder.DecodeSubBlock(m_%s);\n",
                                indent,
                                tsa_classname(((const autogen_seq_ref*)ref_list)->seqptr, TSA_VERSION_SUFFIX | TSA_VEC_PREFIX));
                        fprintf(f, "%s    else", indent);
                        }
                    }
                if (item->base.child_list.n_obj > 0)
                    {
                    fprintf(f, "\n%s       ", indent);
                    }
                fprintf(f, " decoder.UnknownSubBlockId(id);\n");
                fprintf(f, "%s}\n", indent);
                }
            else
                {
                tsa_write_encode_decode_item(f, indent_count, item, "Decode", filler_replacement);
                }
            }
            break;

        case AUTOGEN_ITEM_MERGE:
            {
            autogen_item* merge_item = NULL;
            autogen_item* merged_items[32];
            unsigned int num_items = 0;

            /* Print informational message in case of aggregation */
            if (item->agg_type != AGG_TYPE_FIXED_SINGLE)
                {
                fprintf(f, "%sdecoder.Value", indent);
                fprintf(f, "(&%s::CDecoder::Unsigned, %s, %d, m_%s%s", /* Add & */
                        tsa_namespace,
                        tsa_get_endianness(item),
                        item->length,
                        tsa_item_varname(item),
                        tsa_encode_decode_aggregation(f, item, "Decode"));
                fprintf(f, ");\n");
                }
            else
                {
                /* Write code to retrieve data from message */
                fprintf(f, "\n");
                fprintf(f, "%s// Merged field \"%s\"\n", indent, item->parname);
                fprintf(f, "%sdecoder.Unsigned(%s, %d, decoder.Merged());\n",
                        indent, tsa_get_endianness(item), item->length);

                /* Build item array */
                for (merge_item = (autogen_item*)autogen_obj_get_first_in_list(&item->base.child_list);
                     merge_item != NULL;
                     merge_item = (autogen_item*)merge_item->base.next)
                    {
                    merged_items[num_items++] = merge_item;
                    }

                /* Write code to retrieve each item value */
                for (; num_items > 0; num_items--)
                    {
                    merge_item = merged_items[num_items-1];
                    if (merge_item->base.subtype == AUTOGEN_ITEM_REF)
                        {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(f, "%s%s(decoder.Merged() & 0x%08llX);\n",
                                indent,
                                tsa_get_reference_declaration(merge_item, merge_item->base.name, "Decode"),
                                (1ULL << merge_item->length) - 1);
#else
                        fprintf(f, "%s%s(decoder.Merged() & 0x%08X);\n",
                                indent,
                                tsa_get_reference_declaration(merge_item, merge_item->base.name, "Decode"),
                                (1U << merge_item->length) - 1);
#endif
                        tsa_check_external_reference(f, indent_count, merge_item, "Decode");
                        }
                    else if (merge_item->base.subtype != AUTOGEN_ITEM_FILLER)
                        {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(f, "%sm_%s = decoder.Merged() & 0x%08llX;\n",
                                indent,
                                tsa_item_varname(merge_item),
                                (1ULL << merge_item->length) - 1);
#else
                        fprintf(f, "%sm_%s = decoder.Merged() & 0x%08X;\n",
                                indent,
                                tsa_item_varname(merge_item),
                                (1U << merge_item->length) - 1);
#endif
                        }
                    fprintf(f, "%sdecoder.Merged() >>= %u;\n", indent, merge_item->length);
                    }
                fprintf(f, "\n");
                }
            }
            break;

        default:
            {
            /* If there's nothing special for decoding, use the generic output */
            tsa_write_encode_decode_item(f, indent_count, item, "Decode", filler_replacement);
            }
            break;
        }
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_decode

    Purpose: Writes the Decode method for the given sequence to the given files.

    Functional Description:
        tsa_write_decode writes the declaration of Decode to the given header file and writes
        the implementation of Encode to the given implementation file. The two stream pointers
        may point to the same stream.

    Arguments: 
        f_h - [in,out] Stream pointer to write declaration to.
        f_c - [in,out] Stream pointer to write implementation to.
        seq - [in] The sequence to write the Decode method on.
        par_list - [in] List of parameters created for this class.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_decode(FILE *f_h, FILE *f_c, autogen_seq *seq, tsa_parameter *par_list)
    {
    /* Constants for printing both in header and source file */
    autogen_item *item = NULL;
    int filler_replacement = FALSE;
    char indent[50] = "";
    const char *end_decl = ";";
    const char *function_name = "SetData";
    if (f_h == f_c)
        {
        sprintf(indent, "%s    ", base_indent_string);
        end_decl = "";
        }

    /* Write the start of the SetData method */
    fprintf(f_h, "%s    virtual void %s(const %s &bytes)%s\n",
            base_indent_string, function_name, byte_array_typename, end_decl);
    if (f_h != f_c)
        {
        fprintf(f_c, "\n");
        fprintf(f_c, "void %s::%s(const %s &bytes)\n",
                s_scoped_classname, function_name, byte_array_typename);
        }
    fprintf(f_c, "%s{\n", indent);

    /* Check whether we need a Decode method. In that case, we write delegation
       code into the currently "open" SetData, close it, and open a new "Decode"
       method. The actual decoding code will then be written there. */
    if (seq->base.type != AUTOGEN_OBJ_MSG)
        {
        /* Write delegation code and close the current SetData method */
        fprintf(f_c, "%s    Decode(bytes, NULL);\n", indent);
        fprintf(f_c, "%s}\n", indent);
        function_name = "Decode";

        /* Create a Decode method returning the remaining byte count */
        fprintf(f_h, "%s    size_t %s(const %s &bytes, %s::CDecoder *pParent)%s\n",
                base_indent_string,
                function_name,
                byte_array_typename,
                tsa_namespace,
                end_decl);
        if (f_h != f_c)
            {
            fprintf(f_c, "\n");
            fprintf(f_c, "size_t %s::%s(const %s &bytes, %s::CDecoder *pParent)\n",
                    s_scoped_classname,
                    function_name,
                    byte_array_typename,
                    tsa_namespace);
            }
        fprintf(f_c, "%s{\n", indent);
        }

    /* Check if the response is a COMM_SERVICE_NOT_AUTHENTICATED_RESP */
    if (seq->base.type == AUTOGEN_OBJ_MSG) 
        {
        fprintf(f_c, "%s    BackupData(bytes); //Save a copy of data\n", indent);

        /* resource has common messages */
        if (s_current_res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES) 
            {
            if (( 0!= strcmp(seq->base.name, "COMM_SERVICE_NOT_IDENTIFIED_RESP")) &&
                ( 0!= strcmp(seq->base.name, "COMM_SERVICE_NOT_AUTHENTICATED_RESP")) &&
                ( 0!= strcmp(seq->base.name, "COMM_ISA_ENTITY_NOT_REACHABLE_RESP")) )
                {
                    fprintf(f_c, "%s    CheckForUnexpectedMessages(bytes);\n\n", indent);
                }
            }
        }

    /* Write the implementation of the helper in the implementation file */
    fprintf(f_c, "%s    %s::CDecoder decoder(\"%s::%s()\",\n",
            indent, tsa_namespace, s_scoped_classname, function_name);
    fprintf(f_c, "%s                         %sGetIsiVersion(), %s::CDecoder::",
            indent, util_get_spaces(sizeof(tsa_namespace)-3), tsa_namespace);
    if (seq->base.type & AUTOGEN_OBJ_MSG)
        {
#if (PMD_FILE_FORMAT >= 600)
        fprintf(f_c, "eMessage, bytes, %llu", s_current_res->base.id);
#else
        fprintf(f_c, "eMessage, bytes, %u", s_current_res->base.id);
#endif
        }
    else if (seq->base.type & AUTOGEN_OBJ_SB)
        {
        fprintf(f_c, "eSubBlock, bytes, 0, pParent");
        }
    else
        {
        fprintf(f_c, "eStructure, bytes, 0, pParent");
        }
    fprintf(f_c, ");\n");
    fprintf(f_c, "%s    decoder.Clear(this);\n", indent);

    if( seq->base.type == AUTOGEN_OBJ_MSG)          /* If a message, and */
        {
        fprintf(f_c, "%s    BackupData(bytes); //Save a copy of data, cleared in line above\n", indent);
        }

    for (item = (autogen_item*)autogen_obj_get_first_in_list(&seq->base.child_list); item != NULL; item = (autogen_item*)item->base.next)
        {
        tsa_write_decode_item(f_c, strlen(indent)+indent_step, item, &filler_replacement);
        }
    while (par_list)
        {
        if (!par_list->initvalue)
            {
            /* Inlined structures are handled specially while decoding */
            if (par_list->item->base.subtype != AUTOGEN_ITEM_STRUCT)
                {
                fprintf(f_c, "%s    %s = true;\n", indent, tsa_initname(par_list));
                }
            }
        par_list = par_list->next;
        }
    fprintf(f_c, "%s    %sdecoder.Finalize();\n",
            indent,
            (seq->base.type == AUTOGEN_OBJ_MSG) ? "" : "return ");
    fprintf(f_c, "%s}\n", indent);
    }

/*------------------------------------------------------------------------------------------------

    Name: tsa_get_submsg_namespace
 
    Purpose: Retrieves the name of any namespace to place the given message in
 
    Functional Description:
        tsa_get_submsg_namespace returns the empty string in all cases except the following:
        The given sequence is a submessage in a resource marked for non-unique submessage
        names. In that case, this function returns the TSA name for the base message,
        which is suitable for use as a namespace for the submessage.

    Arguments: 
        msg - [in] The message to check for namespace requirement.

    Return Values: A pointer to a statically allocated string with the namespace.

------------------------------------------------------------------------------------------------*/

LOCAL char *tsa_get_submsg_namespace(const autogen_seq *msg)
    {
    static char result[AUTOGEN_MAX_NAME_LENGTH];
    if ((msg->base.type & AUTOGEN_OBJ_MSG) &&
        (msg->base.flag & AUTOGEN_MSG_IS_SUBMSG) &&
        !prop_has((autogen_obj*)msg->base.res, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
        {
        strcpy(result, tsa_name(msg->base.base_obj->name, s_res_prefix));
        }
    else
        {
        result[0] = 0;
        }
    return result;
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_write_class
 
    Purpose: Writes the code for a class corresponding to the given sequence
 
    Functional Description:
        tsa_write_class writes the definition of a class to the given header file,
        and the implementation of the methods to the given C++ file. The class
        has access methods for relevant items in the sequence, and has an Encode
        and Decode methods (for messages just one of those). If the stream pointers
        refer to the same file, the implementation is written inline in the
        class definition.

    Arguments: 
        f_h - [in,out] Stream pointer to write declaration to.
        f_c - [in,out] Stream pointer to write implemantation to.
        seq - [in] Sequence to write class for. May also be a sub block or a message.

------------------------------------------------------------------------------------------------*/

LOCAL void tsa_write_class(FILE *f_h, FILE *f_c, autogen_seq *seq)
    {
    int is_msg = (seq->base.type == AUTOGEN_OBJ_MSG);
    tsa_parameter* par_list = tsa_build_par_list(seq);
    tsa_parameter* par_trav = NULL;
    unsigned int sb_list_count = 0;
    unsigned int sb_list_index = 0;
    autogen_seq_ref **sb_list_array = find_sb_lists(&seq->base.child_list, &sb_list_count);
    const autogen_seq_ref* sb_trav = NULL;
    char *submsg_namespace = tsa_get_submsg_namespace(seq);
    char impl_comment[AUTOGEN_MAX_NAME_LENGTH + 100];
    char *comment = NULL;

    /* Skip certain messages and structures */
    if (seq->base.type == AUTOGEN_OBJ_SEQ && (seq->base.flag & AUTOGEN_SEQ_IS_NOT_STRUCT))
        {
        /* Don't generate sequences unless CREATE_STRUCT is given */
        return;
        }
    if (seq->base.res != s_current_res && !(seq->base.res->base.subtype & RESOURCE_ISI_COMMON_MESSAGES))
        {
        /* Don't generate sequences from other resources (should be included instead),
           unless it's the common message resource */
        return;
        }
    if (seq->base.type & (AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB))
        {
        /* Check that we don't have messages with these names */
        autogen_it msg_it = INIT_ITERATOR;

        msg_it.typemask = AUTOGEN_OBJ_MSG;
        msg_it.obj.name = seq->base.name;

        if (autogen_obj_find_in_list(&msg_it, &seq->base.res->msg_list) != NULL)
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Sequence %s would conflict with a message. "
                "The class for the sequence has not been generated.",
                seq->base.name);
            return;
            }
        }

    /* Create class name and possibly namespace */
    strcpy(s_classname, tsa_classname(seq, TSA_C_PREFIX | TSA_VERSION_SUFFIX));
    strcpy(s_scoped_classname,
           tsa_classname(seq, TSA_C_PREFIX | TSA_VERSION_SUFFIX | TSA_NAMESPACE_ALWAYS));
    if (*submsg_namespace)
        {
        fprintf(f_h, "%snamespace %s\n", base_indent_string, submsg_namespace);
        fprintf(f_h, "%s{\n", base_indent_string);
        }

    /* Write comment */
    if ((seq->base.type & AUTOGEN_OBJ_MSG) && (seq->base.flag & AUTOGEN_MSG_IS_SUBMSG))
        {
        fprintf(f_h, "%s// %s (sub message of %s)",
                base_indent_string, seq->base.name, seq->base.base_obj->name);
        }
    else
        {
        fprintf(f_h, "%s// %s", base_indent_string, seq->base.name);
        }
    if (prop_has_valid_string((autogen_obj*)seq, PROPERTY_ISIHDR_DEFINITION_NAME))
        {
        fprintf(f_h, " (ISI header file name %s)", prop_get_string((autogen_obj*)seq, PROPERTY_ISIHDR_DEFINITION_NAME));
        }
    comment = tsa_format_comment(0, seq->base.cmt_list);
    if (comment && *comment)
        {
        fprintf(f_h, ":\n%s", comment);
        }
    else
        {
        fprintf(f_h, "\n");
        }

    /* Write head of class declaration */
    fprintf(f_h, "%sclass %s : public %s::CBaseImpl\n",
            base_indent_string, s_classname, tsa_namespace);
    fprintf(f_h, "%s{\n", base_indent_string);
    if (sb_list_array || par_list)
        {
        fprintf(f_h, "%sprotected:\n", base_indent_string);
        }

    /* Write heading in implementation file */
    fprintf(f_c, "\n");
    sprintf(impl_comment, "Implementation of %s",
            tsa_classname(seq, TSA_C_PREFIX | TSA_NAMESPACE_SHARED |
                               TSA_NAMESPACE_SUBMSG | TSA_VERSION_SUFFIX));
    tsa_write_heading(f_c, 0, impl_comment);

    /* Parameter member variables */
    for (par_trav = par_list; par_trav != NULL; par_trav = par_trav->next)
        {
        tsa_write_member_variable(f_h, par_trav);
        }

    /* Initialisation flags for parameter members */
    for (par_trav = par_list; par_trav != NULL; par_trav = par_trav->next)
        {
        if (!par_trav->initvalue)
            {
            fprintf(f_h, "%s%s", base_indent_string, util_get_spaces(indent_step));
            fprintf(f_h, "bool %s;  // Flag for %s\n", tsa_initname(par_trav), par_trav->item->varname);
            }
        }

    /* sub block member variables */
    for (sb_list_index = 0; sb_list_index < sb_list_count; sb_list_index++)
        {
        for (sb_trav = sb_list_array[sb_list_index];
             sb_trav != NULL; 
             sb_trav = (const autogen_seq_ref*) sb_trav->base.next)
            {

            if(sb_trav->base.flag & AUTOGEN_OBJ_IS_SHARED_EXTERNAL)  /* Make different versioning if shared resource */
                {
                autogen_it sb_it = INIT_ITERATOR;
                autogen_obj* sb;

                sb_it.typemask = AUTOGEN_OBJ_SB;
                sb_it.obj.name = ((autogen_seq_ref*)sb_trav)->seqptr->base.name;

                sb = autogen_obj_find_in_list(&sb_it, &((autogen_seq_ref*)sb_trav)->seqptr->base.res->seq_list);
                while (sb)
                    {
                    char version_suffix[AUTOGEN_MAX_NAME_LENGTH];

                    if ((sb->ver.from[0] != 0) || sb->ver.from[1] != 0 || util_has_multiple_versions(sb))
                        {
                        sprintf(version_suffix , "_%03hd_%03hd", sb->ver.from[0], sb->ver.from[1]);
                        }
                    else
                        {
                        sprintf(version_suffix , "");
                        }

                    fprintf(f_h, "%s    std::vector<%s%s> ", 
                            base_indent_string,
                            tsa_classname(sb_trav->seqptr, TSA_NAMESPACE_SHARED | TSA_C_PREFIX),
                            version_suffix);
                    fprintf(f_h, "m_%s%s;\n",
                            tsa_classname(sb_trav->seqptr, TSA_VEC_PREFIX), 
                            version_suffix);

                    sb = autogen_obj_find_next_in_list(&sb_it);
                    }
                }
            else
                {
            fprintf(f_h, "%s    std::vector<%s> ", 
                    base_indent_string,
                    tsa_classname(sb_trav->seqptr,
                                  TSA_NAMESPACE_SHARED | TSA_C_PREFIX | TSA_VERSION_SUFFIX));
            fprintf(f_h, "m_%s;\n",
                    tsa_classname(sb_trav->seqptr,
                                  TSA_VEC_PREFIX | TSA_VERSION_SUFFIX));
            }
        }
        }

    /* Public members */
    if (par_list == NULL && sb_list_count == 0)
        {
        fprintf(f_h, "\n");
        }
    fprintf(f_h, "%spublic:\n", base_indent_string);

    /* Related message typedef */
    if (seq->base.related_obj.n_obj > 0)
        {
        /* Search for the related message object */
        autogen_obj *rel;
        autogen_it rel_it = INIT_ITERATOR;

        rel_it.typemask    = AUTOGEN_OBJ_MSG;
        rel_it.obj.name    = seq->base.related_obj.obj_list[0]->name;
        rel_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        rel_it.ver         = &seq->base.ver;

        rel = autogen_obj_find_in_list(&rel_it, &seq->base.res->seq_list);
        if (rel)
            {
            autogen_seq *rel_seq = (autogen_seq *) rel;
            char *rel_namespace = tsa_get_submsg_namespace(rel_seq);
            fprintf(f_h, "%s    // Related message typedef\n", base_indent_string);
            if (*rel_namespace)
                {
                fprintf(f_h, "%s    namespace %s {} // Related message namespace\n",
                        base_indent_string, rel_namespace);
                }
            fprintf(f_h, "%s    typedef class %s",
                    base_indent_string, tsa_classname(rel_seq,
                                TSA_C_PREFIX | TSA_NAMESPACE_SUBMSG | TSA_VERSION_SUFFIX));
            fprintf(f_h, "%s_message;\n",
                    (seq->base.flag & AUTOGEN_MSG_REQ) ? "response" : "request");
            fprintf(f_h, "\n");
            }
        }

    /* constructor */
    tsa_write_constructor(f_h, f_c, seq, par_list);

    /* Make specific SetVersion method */
        {
            tsa_write_setversion(f_h, f_c, &seq->base.ver);
        }

    /* GetXXX and SetXXX */
    for (par_trav = par_list; par_trav != NULL; par_trav = par_trav->next)
        {
        tsa_write_access_methods(f_h, f_c, par_trav);
        }

    /* generate sub block functions */
    for (sb_list_index = 0; sb_list_index < sb_list_count; sb_list_index++)
        {
        for (sb_trav = sb_list_array[sb_list_index];
             sb_trav != NULL; 
             sb_trav = (const autogen_seq_ref*) sb_trav->base.next)
            {
            tsa_write_subblock_methods(f_h, f_c, sb_trav, seq);
            }
        }

    /* Encoding and decoding */
    fprintf(f_h, "\n");
    if (is_msg)
        {
        if (seq->base.flag & AUTOGEN_MSG_REQ)
            {
            fprintf(f_h, "%s    // Encode this message into a sequence of bytes "
                    "(with PhoNet header)\n",
                    base_indent_string);
            tsa_write_encode(f_h, f_c, seq, par_list);
            }
        else
            {
            fprintf(f_h, "%s    // Decode the given byte sequence (with PhoNet header) "
                    "into this message\n",
                    base_indent_string);
            tsa_write_decode(f_h, f_c, seq, par_list);
            }
        }
    else
        {
        fprintf(f_h, "%s    // Encoding and decoding\n", base_indent_string);
        tsa_write_encode(f_h, f_c, seq, par_list);
        tsa_write_decode(f_h, f_c, seq, par_list);
        }

    /* End class and possibly namespace */
    fprintf(f_h, "%s};  // class %s\n", base_indent_string, s_classname);
    submsg_namespace = tsa_get_submsg_namespace(seq);
    if (*submsg_namespace)
        {
        fprintf(f_h, "%s};  // namespace %s\n", base_indent_string, submsg_namespace);
        }
    fprintf(f_h, "\n");
    }


/*------------------------------------------------------------------------------------------------

    Name: tsa_has_multiple_entries
 
    Purpose: Checks whether there are multiple versions of the given entry
 
    Functional Description:
        tsa_has_multiple_entries checks if there are multiple versions of the
        name of the given entry in the given table. If so, this function returns
        TRUE. Otherwise returns FALSE.

    Arguments: 
        tbl - [in] The table that contains the entry.
        entry - [in] The entry to check for multiple versions

    Return Values: TRUE if multiple versions exist, FALSE otherwise.

------------------------------------------------------------------------------------------------*/

LOCAL int tsa_has_multiple_entries(autogen_tbl *tbl, const autogen_obj *entry)
{
    /* First check if this entry spans the entire table version range */
    if (!autogen_obj_ver_is_exact(&tbl->base.ver, &entry->ver))
    {
        /* It did not. We must check for duplicate names */
        autogen_it dup_it = INIT_ITERATOR;

        dup_it.obj.name = entry->name;

        if (autogen_obj_count_in_list(&dup_it, &tbl->base.child_list) > 1)
        {
            return TRUE;
        }
    }
    return FALSE;
}


LOCAL void tsa_write_constants(FILE *f, autogen_res *res)
{
    autogen_it cbtbl_it  = INIT_ITERATOR;
    autogen_tbl* cbtbl   = NULL;
    autogen_it fptbl_it  = INIT_ITERATOR;
    autogen_tbl* fptbl   = NULL;

    cbtbl_it.typemask    = AUTOGEN_OBJ_TBL;
    cbtbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
    cbtbl_it.sort_type   = AUTOGEN_OBJ_LIST_SORT_BY_NAME;

    fptbl_it.typemask    = AUTOGEN_OBJ_TBL;
    fptbl_it.subtypemask = AUTOGEN_TBL_FTD | AUTOGEN_TBL_PPC;
    /* ==================================================================== */
    /* Generate constant and bit tables */
    /* ==================================================================== */

    /* generic constants */
    {
        autogen_obj* cons = autogen_obj_get_first_in_list(&res->const_list);
        if (cons)
        {
            tsa_write_heading(f, base_indent, "Generic Constants");

            while (cons)
            {
                format_version_suffix(cons);
                fprintf(f, "#define %-52s ", s_constname_versioned);

                if (cons->flag & AUTOGEN_CONST_SIGNED)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "%lld", (long long)cons->id);
#else
                    fprintf(f, "%d", (int)cons->id);
#endif
                }
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_BYTE)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "0x%02llX", cons->id);
#else
                    fprintf(f, "0x%02X", cons->id);
#endif
                }
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_WORD)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "0x%04llX", cons->id);
#else
                    fprintf(f, "0x%04X", cons->id);
#endif
                }
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_DWORD)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "0x%08llX", cons->id);
#else
                    fprintf(f, "0x%08X", cons->id);
#endif
                }
#if (PMD_FILE_FORMAT >= 600)
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_DDWORD)
                {
                    fprintf(f, "0x%016llX", cons->id);
                }
#endif
                else
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "%llu", cons->id);
#else
                    fprintf(f, "%u", cons->id);
#endif
                }
                fprintf(f, "\n");

                cons = cons->next;
            }
            fprintf(f, "\n");
        }
    }



    cbtbl = (autogen_tbl*)autogen_obj_find_in_list(&cbtbl_it, &res->tbl_list);
    if (cbtbl)
    {
        tsa_write_heading(f, base_indent, "Constants");
        fprintf(f, "\n");
    }
    while (cbtbl)
    {
        if (!(cbtbl->base.subtype & (AUTOGEN_TBL_DERCONST | AUTOGEN_TBL_DERBIT)))
        {
            autogen_it entry_it = INIT_ITERATOR;
            autogen_obj* entry = NULL;
            int table_versions = util_has_multiple_versions(&cbtbl->base);

            fprintf(f, "%s// Constant table %s", base_indent_string, cbtbl->base.name);
            if (table_versions)
            {
                fprintf(f, " (");
                if (cbtbl->base.ver.type & AUTOGEN_OBJ_VERSION_FROM)
                {
                    fprintf(f, "from %03hd.%03hd",
                        cbtbl->base.ver.from[0], cbtbl->base.ver.from[1]);
                }
                if (cbtbl->base.ver.type & AUTOGEN_OBJ_VERSION_TO)
                {
                    fprintf(f, "to %03hd.%03hd",
                        cbtbl->base.ver.to[0], cbtbl->base.ver.to[1]);
                }
                fprintf(f, ")");
            }
            fprintf(f, "\n");
            fprintf(f, "%s", tsa_format_comment(0, cbtbl->base.cmt_list));

            entry_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
            entry_it.ver     = &cbtbl->base.ver;

            entry = autogen_obj_find_in_list(&entry_it, &cbtbl->base.child_list);
            while (entry)
            {
                const char *name = entry->name;

                /* Write the comment */
                fprintf(f, "%s", tsa_format_comment(0, entry->cmt_list));

                /* Write any version suffix to the name */
                if (table_versions || tsa_has_multiple_entries(cbtbl, entry))
                {
                    static char name_buffer[AUTOGEN_MAX_NAME_LENGTH + 20];
                    sprintf(name_buffer, "%s_%03hd_%03hd", name, entry->ver.from[0], entry->ver.from[1]); 
                    
                    name = name_buffer;
                }
                format_version_suffix(entry);
                fprintf(f, "#define %-52s ", s_constname_versioned);

                /* TODO these flags are not currently set. Should change autogen_init... */                    
                if (entry->flag & AUTOGEN_CONST_SIGNED)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "%lld", (long long)entry->id);
#else
                    fprintf(f, "%d", (int)entry->id);
#endif
                }
                else if (entry->flag & AUTOGEN_CONST_UNSIGNED_BYTE)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "0x%02llX", entry->id);
#else
                    fprintf(f, "0x%02X", entry->id);
#endif
                }
                else if (entry->flag & AUTOGEN_CONST_UNSIGNED_WORD)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "0x%04llX", entry->id);
#else
                    fprintf(f, "0x%04X", entry->id);
#endif
                }
                else if (entry->flag & AUTOGEN_CONST_UNSIGNED_DWORD)
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "0x%08llX", entry->id);
#else
                    fprintf(f, "0x%08X", entry->id);
#endif
                }
#if (PMD_FILE_FORMAT >= 600)
                else if (entry->flag & AUTOGEN_CONST_UNSIGNED_DDWORD)
                {
                    fprintf(f, "0x%016llX", entry->id);
                }
#endif
                else
                {
#if (PMD_FILE_FORMAT >= 600)
                    fprintf(f, "%llu", entry->id);
#else
                    fprintf(f, "%u", entry->id);
#endif
                }

                fprintf(f, "\n");

                entry = autogen_obj_find_next_in_list(&entry_it);
            }

            fprintf(f, "\n");
        }

        cbtbl = (autogen_tbl*)autogen_obj_find_next_in_list(&cbtbl_it);
    }


    /* ==================================================================== */
    /* Generate R&D Display data ID tables and PPC ID tables */
    /* ==================================================================== */
    fptbl = (autogen_tbl*)autogen_obj_find_in_list(&fptbl_it, &res->tbl_list);
    while (fptbl)
    {
        autogen_data* entry;
        autogen_it entry_it = INIT_ITERATOR;

        entry = (autogen_data*)autogen_obj_find_in_list(&entry_it, &fptbl->base.child_list);

        /* If there are any items, print a header and iterate though them */
        if (entry)
        {
            tsa_write_heading(f, base_indent, (fptbl->base.subtype & AUTOGEN_TBL_FTD)
                ? "FTD table"
                : "PPC table");

            while (entry)
            {
                /* Format the type as a trailing comment */
                char trailing_comment[50] = "";
                autogen_data* dataitem = entry;
                const char *name = dataitem->base.name;

                if (dataitem->base.flag & AUTOGEN_DATA_TABLE)
                {
                    strcat(trailing_comment, "table of ");
                    strcat(trailing_comment,
                        dataitem->length < 0 ? long_typename : ulong_typename);
                    strcat(trailing_comment, "s");
                }
                else
                {
                    strcat(trailing_comment,
                        dataitem->length < 0 ? long_typename : ulong_typename);
                }

                trailing_comment[0] = (char)toupper(trailing_comment[0]);


                /* Generate the definition and find the next item */
                fprintf(f, "%s", tsa_format_comment(0, dataitem->base.cmt_list));
                if (tsa_has_multiple_entries(fptbl, &dataitem->base))
                {
                    static char name_buffer[AUTOGEN_MAX_NAME_LENGTH + 20];
                    sprintf(name_buffer, "%s_%03hd_%03hd",
                        name,
                        dataitem->base.ver.from[0],
                        dataitem->base.ver.from[1]);
                    name = name_buffer;
                }
#if (PMD_FILE_FORMAT >= 600)
                fprintf(f, "#define %-50s %5llu // %s\n",
                    name, dataitem->base.id, trailing_comment);
#else
                fprintf(f, "#define %-50s %5u // %s\n",
                    name, dataitem->base.id, trailing_comment);
#endif

                entry = (autogen_data*)autogen_obj_find_next_in_list(&entry_it);
            }

            fprintf(f, "\n");
        }

        fptbl = (autogen_tbl*)autogen_obj_find_next_in_list(&fptbl_it);
    }
}

/*------------------------------------------------------------------------------------------------

    Name: tsa_get_filename
 
    Purpose: Returns the filename defined in properties for the given resource

    Arguments: 
        res -   [in] The resource that holds filename in its resource

    Return Values: If the property is found the value is returned else an empty string is returned.

------------------------------------------------------------------------------------------------*/
LOCAL const char* tsa_get_filename(const autogen_res *res)
    {
    const char* filename;
    if(prop_has_valid_string((autogen_obj*)res, PROPERTY_ISIHDR_FILENAME))
        {
        filename = prop_get_string((autogen_obj*)res, PROPERTY_ISIHDR_FILENAME);
        }
    else
    if(prop_has_valid_string((autogen_obj*)res, PROPERTY_ISIHDR_FILENAME_16))
        {
        filename = prop_get_string((autogen_obj*)res, PROPERTY_ISIHDR_FILENAME_16);
        }
    else
        {
        filename = "";
        }
    return filename;
    }

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

LOCAL void tsa_write_helper_methods(FILE *f_h, FILE *f_c)
    {
    if(s_current_res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES)   /* resource has common messages */
        {
        fprintf(f_h, "%sstatic void CheckForUnexpectedMessages(const %s &bytes);\n\n", base_indent_string, byte_array_typename);

        fprintf(f_c, "%s\nvoid %s::%s::CheckForUnexpectedMessages(const %s &bytes)\n", base_indent_string, tsa_namespace, s_res_namespace, byte_array_typename);
        fprintf(f_c, "%s{\n", base_indent_string);
        fprintf(f_c, "%s    if( (bytes.size() >= 11) && (bytes[9] == 0xF0)) // If it's a common message\n", base_indent_string);
        fprintf(f_c, "%s    {\n", base_indent_string);
                        
        /* Check that the message is not a COMM_SERVICE_NOT_IDENTIFIED_RESP */
        fprintf(f_c, "%s        //COMM_SERVICE_NOT_IDENTIFIED_RESP\n", base_indent_string);
        fprintf(f_c, "%s        bool bIsAnNotIdentifiedResp = false;\n", base_indent_string);
        fprintf(f_c, "%s        CCommServiceNotIdentifiedResp commServiceNotIdentifiedResp;\n", base_indent_string, tsa_name(s_current_res->resnameshort_l, NULL));
        fprintf(f_c, "%s        try\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s            commServiceNotIdentifiedResp.SetData(bytes);\n", base_indent_string);
        fprintf(f_c, "%s            bIsAnNotIdentifiedResp = true;\n", base_indent_string);
        fprintf(f_c, "%s        }\n", base_indent_string);
        fprintf(f_c, "%s        catch(...)\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s        }\n", base_indent_string);
        fprintf(f_c, "%s        if(bIsAnNotIdentifiedResp)\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s            //If the decoding succedded the message is as COMM_SERVICE_NOT_IDENTIFIED_RESP\n", base_indent_string);
        fprintf(f_c, "%s            CException::Throw(__LOC__, TSSSA_E_COMM_SERVICE_NOT_IDENTIFIED_RESP_RETRIEVED, bytes[3], commServiceNotIdentifiedResp.GetNotServedMessageid(), commServiceNotIdentifiedResp.GetNotServedSubmessageid());\n", base_indent_string);
        fprintf(f_c, "%s        }\n\n", base_indent_string);

        /* And the message is not a COMM_ISA_ENTITY_NOT_REACHABLE_RESP */
        fprintf(f_c, "%s        //COMM_ISA_ENTITY_NOT_REACHABLE_RESP\n", base_indent_string);
        fprintf(f_c, "%s        bool bIsAnIsaEntityNotReachableResp = false;\n", base_indent_string);
        fprintf(f_c, "%s        CCommIsaEntityNotReachableResp commIsaEntityNotReachableResp;\n", base_indent_string);
        fprintf(f_c, "%s        try\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s            commIsaEntityNotReachableResp.SetData(bytes);\n", base_indent_string);
        fprintf(f_c, "%s            bIsAnIsaEntityNotReachableResp = true;\n", base_indent_string);
        fprintf(f_c, "%s        }\n", base_indent_string);
        fprintf(f_c, "%s        catch(...)\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s        }\n", base_indent_string);
        fprintf(f_c, "%s        if(bIsAnIsaEntityNotReachableResp)\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s            //If the decoding succedded the message is as COMM_ISA_ENTITY_NOT_REACHABLE_RESP\n", base_indent_string);
        fprintf(f_c, "%s            CException::Throw(__LOC__, TSSSA_E_COMM_ISA_ENTITY_NOT_REACHABLE_RESP_RETRIEVED, bytes[3], commIsaEntityNotReachableResp.GetNotDeliveredMessageid());\n", base_indent_string, s_scoped_classname);
        fprintf(f_c, "%s        }\n\n", base_indent_string);

        /* And the message is not a COMM_SERVICE_NOT_AUTHENTICATED_RESP */
        fprintf(f_c, "%s        //COMM_SERVICE_NOT_AUTHENTICATED_RESP\n", base_indent_string);
        fprintf(f_c, "%s        bool bIsAnNotAuthenticatedResp = false;\n", base_indent_string);
        fprintf(f_c, "%s        CCommServiceNotAuthenticatedResp commServiceNotAuthenticatedResp;\n", base_indent_string);
        fprintf(f_c, "%s        try\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s            commServiceNotAuthenticatedResp.SetData(bytes);\n", base_indent_string);
        fprintf(f_c, "%s            bIsAnNotAuthenticatedResp = true;\n", base_indent_string);
        fprintf(f_c, "%s        }\n", base_indent_string);
        fprintf(f_c, "%s        catch(...)\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s        }\n", base_indent_string);
        fprintf(f_c, "%s        if(bIsAnNotAuthenticatedResp)\n", base_indent_string);
        fprintf(f_c, "%s        {\n", base_indent_string);
        fprintf(f_c, "%s            //If the decoding succedded the message is as COMM_SERVICE_NOT_AUTHENTICATED_RESP_RETRIEVED\n", base_indent_string);
        fprintf(f_c, "%s            CException::Throw(__LOC__, TSSSA_E_COMM_SERVICE_NOT_AUTHENTICATED_RESP_RETRIEVED);\n", base_indent_string);
        fprintf(f_c, "%s        }\n", base_indent_string);
        fprintf(f_c, "%s    }\n", base_indent_string);
        fprintf(f_c, "%s}\n\n", base_indent_string);
        }
    }

/* ==================================================================== */
/* Plot the structures to the console */
/* ==================================================================== */
    #ifdef _DEBUG

    void TraverseObject(autogen_obj* object, int indent);

    char* GetIndent(int indent)
        {
        char* result = pmd_heap_alloc(indent + 1);
        memset(result, 32, indent);
        result[indent] = 0;
        return result;
        }

    void PrintToConsole(autogen_obj* object, const char* name, int indent)
        {
        char* indentString = GetIndent(indent++);
            printf("%s%s, %03d.%03d -> %03d.%03d ", 
                    indentString,
                    name,
                    object->ver.from[0],
                    object->ver.from[1],
                    object->ver.to[0],
                    object->ver.to[1]);
            if(object->flag & AUTOGEN_OBJ_IS_SHARED)
                printf(", Shared ");
            printf("Type: 0x%08X::0x%08X ", object->type, object->subtype);
            printf("\n");
        }

    void PrintSequence(autogen_seq* seq, int indent)
        {
        autogen_obj* child = autogen_obj_get_first_in_list(&seq->base.child_list);

        if((seq->base.name != NULL) && ((int)(seq->base.name) > 5000))
            PrintToConsole(&seq->base, seq->base.name, indent);
        else
            PrintToConsole(&seq->base, "No name", indent);

        while(child)
            {
                TraverseObject(child, indent);
                child = child->next;
            }
        }

    void PrintItem(autogen_item* item, int indent)
        {
        PrintToConsole(&item->base, item->base.name, indent);

        switch(item->base.subtype)
            {
        case AUTOGEN_ITEM_LST:
            {
            autogen_obj* child = autogen_obj_get_first_in_list(&item->base.child_list);
            while(child)
                {
                TraverseObject(child, indent);
                child = child->next;
                }
            }
            break;

        case AUTOGEN_ITEM_VALUE:
        case AUTOGEN_ITEM_FILLER:
        default:
            /*Do nothing, already printed */
            break;
            }
        }

    void PrintRef(autogen_seq_ref* ref, int indent)
        {
        printf("%sReference: ", GetIndent(indent));
        PrintToConsole(&ref->base, ref->base.name, indent);
        printf("%sRefering:  ", GetIndent(indent));
        PrintSequence(ref->seqptr, indent);
        }

    void TraverseObject(autogen_obj* object, int indent)
        {
            switch(object->type)
                {
            case AUTOGEN_OBJ_SB:
            case AUTOGEN_OBJ_MSG:
                PrintSequence((autogen_seq*)object, indent);
                break;
            case AUTOGEN_OBJ_ITEM:
                PrintItem((autogen_item*)object, indent);
                break;
            case AUTOGEN_OBJ_REF:
                PrintRef((autogen_seq_ref*)object, indent);
                break;
            default:
                PrintToConsole(object, object->name, indent);
                }
        }

    void ConsolePrintResource(autogen_res* res)
        {
        printf("*********************************************\n");
        printf("---------------------------------------------\n");
        printf("Resource: %s\n", res->base.name);
        printf("---------------------------------------------\n");
        printf("\n");

        printf("Messages:\n");
        PrintSequence((autogen_seq*)autogen_obj_get_first_in_list(&res->msg_list), 1);

        printf("Sequences:\n");
        PrintSequence((autogen_seq*)autogen_obj_get_first_in_list(&res->seq_list), 1);
        printf("*********************************************\n");

        }
    #endif

/* --------------------------------------------------------------------------------------------- */
/*  Name: output_tsa
 
    Purpose: 
        Generates TSS Server API
 
    Functional Description:
        Main function for the TSS Server API generator
*/
/* --------------------------------------------------------------------------------------------- */
void output_tsa(void)
    {
    autogen_it res_it = INIT_ITERATOR;
    autogen_res* res;

    printf("Generating TSS Server API source files...\n");
    fprintf(g_log, "\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");
    fprintf(g_log, "TSS Server API source file generation\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");

    res_it.typemask        = AUTOGEN_OBJ_RES;
    res_it.subtypemask     = RESOURCE_ISI | RESOURCE_SHARED | RESOURCE_ISI_EXTENSION | RESOURCE_PHONET_EXT;

    res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
    while (res)
        {
        FILE* f_h = NULL;
        FILE* f_c = NULL;
        const char* filename = tsa_get_filename(res);
        char hdr_filename[AUTOGEN_MAX_NAME_LENGTH+50];
        char impl_filename[AUTOGEN_MAX_NAME_LENGTH+50];
        char idempotency_macro[AUTOGEN_MAX_NAME_LENGTH+50];
        char *comment = tsa_format_comment(0, res->base.cmt_list);
        const char *extension = NULL;
        autogen_obj *shared_obj = NULL;
        s_current_res = res;
        /* If namespace is defined in property, use this, else use the short name */
        if(prop_has(&(s_current_res->base), PROPERTY_TSA_NAMESPACE))
        {
            strcpy(s_res_prefix, prop_get_string(&(s_current_res->base), PROPERTY_TSA_NAMESPACE));
        }
        else
        {
            strcpy(s_res_prefix, tsa_name(res->resnameshort_l, NULL));
        }
        strcpy(s_res_namespace, s_res_prefix);
        if (res->base.subtype & RESOURCE_SHARED)
            {
            strcat(s_res_namespace, shared_namespace_suffix);
            }

        /* Open header file and write Continuus header */
        sprintf(hdr_filename, "tsa_%s", filename);
        util_write_version_file(hdr_filename, &(s_current_res->base.ver));
        f_h = fopen(hdr_filename, "wt");
        if (f_h == NULL)
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Unable to create file \"%s\" for TSA header file output",
                hdr_filename);
            }
        tsa_write_header(f_h, res, TRUE);

        /* Write idempotency declarations */
        sprintf(idempotency_macro, "__TSA_%s_ISI_%sH__",
                res->resnameshort_u,
                (res->base.subtype & RESOURCE_SHARED) ? "SHARED_" : "");
        fprintf(f_h, "#ifndef %s\n", idempotency_macro);
        fprintf(f_h, "#define %s\n", idempotency_macro);
        fprintf(f_h, "\n");
        fprintf(f_h, "#if _MSC_VER > 1000\n");
        fprintf(f_h, "#pragma once\n");
        fprintf(f_h, "#endif // _MSC_VER > 1000\n");
        fprintf(f_h, "\n");

        /* Write standard include */
        fprintf(f_h, "#include \"tsa_defs.h\" // Definitions used in generated header files\n");

        /* Write shared resource includes */
        for (shared_obj = autogen_obj_get_first_in_list(&res->shared_list); shared_obj != NULL; shared_obj = shared_obj->next)
            {
            const autogen_res* shared_res = (const autogen_res*)shared_obj->ptr;

            fprintf(f_h, "#include \"tsa_%s\" // %s\n", tsa_get_filename(shared_res), shared_res->logical_name);
            }
        fprintf(f_h, "\n");

        /* Write resource comment and namespace start */
        fprintf(f_h, "\n");
        fprintf(f_h, "%s", comment);
        if (strcmp(tsa_namespace, "Tss::ServerApi") != 0)
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Incorrect namespace configuration");
            }
        fprintf(f_h, "namespace Tss\n");
        fprintf(f_h, "{\n");
        fprintf(f_h, "namespace ServerApi\n");
        fprintf(f_h, "{\n");
        fprintf(f_h, "namespace %s\n", s_res_namespace);
        fprintf(f_h, "{\n");

        /* Open implementation file and write Continuus header */
        extension = strrchr(filename, '.');
        if (extension == NULL)
            {
            extension = filename + strlen(filename);
            }
        sprintf(impl_filename, "tsa_%.*s.cpp", extension - filename, filename);
        util_write_version_file(impl_filename, &(s_current_res->base.ver));
        f_c = fopen(impl_filename, "wt");
        if (f_c == NULL)
            {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                "Unable to create file \"%s\" for TSA implementation file output",
                impl_filename);
            }
        tsa_write_header(f_c, res, FALSE);

        /* Write include directives */
        fprintf(f_c, "#include \"stdafx.h\"\n");
        fprintf(f_c, "#include \"tsa_%s\"\n", filename);
        fprintf(f_c, "\n");
        fprintf(f_c, "#include \"tsa_impl.h\"\n");

    /* ==================================================================== */
    /* Generate constants */
    /* ==================================================================== */

        tsa_write_constants(f_h, res);

    /* ==================================================================== */
    /* Generate resource version stuff */
    /* ==================================================================== */

        tsa_write_heading(f_h, base_indent, "Resource Version");
        fprintf(f_h, "\nstatic %s::CVersion ResourceVersion = %s::CVersion(%hd,%hd);\n\n", tsa_namespace, tsa_namespace, res->base.ver.from[0], res->base.ver.from[1]);

    /* ==================================================================== */
    /* Generate common message support */
    /* ==================================================================== */

        if (res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES)
            {
            autogen_res *comm_res           = NULL;
            autogen_it tbl_it               = INIT_ITERATOR;
            autogen_tbl* tbl                = NULL;
            autogen_ver *comm_version       = NULL;

            /* Find common message resource */
            comm_res = util_get_unique_res(RESOURCE_ISI_COMMON_MESSAGES);
            if (comm_res)
                {
                char heading[100];
                comm_version = &comm_res->base.ver;
                sprintf(heading, "Common message definitions (version %03hd.%03hd)",
                        comm_version->from[0], comm_version->from[1]);
                tsa_write_heading(f_h, base_indent, heading);
                fprintf(f_h, "\n");

                /* Generated bit tables and constant tables */
                tbl_it.typemask    = AUTOGEN_OBJ_TBL;
                tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
                tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                tbl_it.ver         = comm_version;

                tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &comm_res->tbl_list);
                if (tbl)
                    {
                    fprintf(f_h, "%s// Common message constants\n", base_indent_string);
                    fprintf(f_h, "\n");
                    }
                while (tbl)
                    {
                    if (!(tbl->base.subtype & (AUTOGEN_TBL_DERCONST | AUTOGEN_TBL_DERBIT)))
                        {
                        autogen_it entry_it = INIT_ITERATOR;
                        autogen_obj* entry = NULL;

                        fprintf(f_h, "%s// Constant table %s\n", base_indent_string, tbl->base.name);
                        fprintf(f_h, "%s", tsa_format_comment(0, tbl->base.cmt_list));

                        entry_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
                        entry_it.ver     = comm_version;

                        entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
                        while (entry)
                            {
                            fprintf(f_h, "%s", tsa_format_comment(0, entry->cmt_list));
                            format_version_suffix(entry);
                            fprintf(f_h, "#define %-52s ", s_constname_versioned);
                            /* TODO these flags are not currently set. Should change autogen_init... */                    
                            if (entry->flag & AUTOGEN_CONST_SIGNED)
                                {
#if (PMD_FILE_FORMAT >= 600)
                                fprintf(f_h, "%lld", (long long)entry->id);
#else
                                fprintf(f_h, "%d", (int)entry->id);
#endif
                                }
                            else if (entry->flag & AUTOGEN_CONST_UNSIGNED_BYTE)
                                {
#if (PMD_FILE_FORMAT >= 600)
                                fprintf(f_h, "0x%02llX", entry->id);
#else
                                fprintf(f_h, "0x%02X", entry->id);
#endif
                                }
                            else if (entry->flag & AUTOGEN_CONST_UNSIGNED_WORD)
                                {
#if (PMD_FILE_FORMAT >= 600)
                                fprintf(f_h, "0x%04llX", entry->id);
#else
                                fprintf(f_h, "0x%04X", entry->id);
#endif
                                }
                            else if (entry->flag & AUTOGEN_CONST_UNSIGNED_DWORD)
                                {
#if (PMD_FILE_FORMAT >= 600)
                                fprintf(f_h, "0x%08llX", entry->id);
#else
                                fprintf(f_h, "0x%08X", entry->id);
#endif
                                }
#if (PMD_FILE_FORMAT >= 600)
                            else if (entry->flag & AUTOGEN_CONST_UNSIGNED_DDWORD)
                                {
                                fprintf(f_h, "0x%016llX", entry->id);
                                }
#endif
                            else
                                {
#if (PMD_FILE_FORMAT >= 600)
                                fprintf(f_h, "%llu", entry->id);
#else
                                fprintf(f_h, "%u", entry->id);
#endif
                                }
                
                            fprintf(f_h, "\n");

                            entry = autogen_obj_find_next_in_list(&entry_it);
                            }

                        fprintf(f_h, "\n");
                        }

                    tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
                    }

                /* Generate common sub blocks and structures */
                    {
                    autogen_obj* sb;
                    autogen_it sb_it = INIT_ITERATOR;

                    sb_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;

                    sb = autogen_obj_find_in_list(&sb_it, &comm_res->seq_list);
                    if (sb)
                        {
                        fprintf(f_h, "%s// Common sub blocks and structures\n", base_indent_string);
                        fprintf(f_h, "\n");
                        }
                    while (sb)
                        {
                        tsa_write_class(f_h, f_c, (autogen_seq*)sb);

                        sb = autogen_obj_find_next_in_list(&sb_it);
                        }
                    }

                /* Generate common messages */
                    {
                    autogen_seq* msg;
                    autogen_it msg_it = INIT_ITERATOR;

                    msg_it.typemask = AUTOGEN_OBJ_MSG_BASE;

                    msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, &comm_res->msg_list);
                    if (msg)
                        {
                        autogen_obj* submsg;

                        fprintf(f_h, "%s// Common message classes\n", base_indent_string);
                        fprintf(f_h, "\n");

                        submsg = autogen_obj_get_first_in_list(&msg->submsg_list);
                        while (submsg)
                            {
                            tsa_write_class(f_h, f_c, (autogen_seq*)submsg);

                            submsg = submsg->next;
                            }
                        }
                    }
                }
            else
                {
                fprintf(f_h, "%s// No common message definitions included in autogen build\n",
                        base_indent_string);
                fprintf(f_h, "\n");
                }
            }

    /* ==================================================================== */
    /* Generate sub block and structure classes */
    /* ==================================================================== */
        {
        autogen_obj* sb;
        autogen_it sb_it = INIT_ITERATOR;

        sb_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;

        sb = autogen_obj_find_in_list(&sb_it, &res->seq_list);

        if (sb)
            {
            tsa_write_heading(f_h, base_indent, "Sub blocks and structures");
            fprintf(f_h, "\n");
            }

        while (sb)
            {
            tsa_write_class(f_h, f_c, (autogen_seq*)sb);

            sb = autogen_obj_find_next_in_list(&sb_it);
            }
        }

    /* ==================================================================== */
    /* Generate message classes */
    /* ==================================================================== */
        {
        autogen_seq* msg = (autogen_seq*)autogen_obj_get_first_in_list(&res->msg_list);

        if (msg)
            {
            tsa_write_heading(f_h, base_indent, "Messages");
            fprintf(f_h, "\n");
            }
        while (msg)
            {
            if (msg->base.type == AUTOGEN_OBJ_MSG_BASE)
                {
                autogen_obj* submsg = autogen_obj_get_first_in_list(&msg->submsg_list);
                while (submsg)
                    {
                    tsa_write_class(f_h, f_c, (autogen_seq*)submsg);

                    submsg = submsg->next;
                    }
                }
            else if (msg->base.child_list.n_obj > 0)
                {
                tsa_write_class(f_h, f_c, msg);
            }

            msg = (autogen_seq*)msg->base.next;
            }
        }

    /* ==================================================================== */
    /* Generate server specific helper functions */
    /* ==================================================================== */

            tsa_write_helper_methods(f_h, f_c);


        fprintf(f_h, "} // namespace %s\n", s_res_namespace);
        fprintf(f_h, "} // namespace ServerApi\n");
        fprintf(f_h, "} // namespace Tss\n");

        fprintf(f_h, "\n");
        fprintf(f_h, "#endif // %s\n", idempotency_macro);
        fprintf(f_h, "\n");
        fprintf(f_h, "// End of file %s\n", hdr_filename);
        fclose(f_h);

        fprintf(f_c, "\n");
        fprintf(f_c, "// End of file %s\n", impl_filename);
        fclose(f_c);

        /*ConsolePrintResource(res);*/

        res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
        }
    }

/*  End of file output_tsa.c  */
