/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_util.c
                --------------
                SW Module






Project:          autogen

%name:            autogen_util.c %
%version:         co1tss#84 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Fri Jul 16 18:21:01 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  This file is part of the source code for the autogen tool

    The file contains some utility functions used by the autogen tool
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_ref.h"
#include "autogen_object.h"
#include "autogen_util.h"
#include "pmd_heap.h"
#include "autogen_prop.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL static
#endif /* LOCAL */


LOCAL void util_validate_printf_argument(const char *file, 
                                         int line, 
                                         char type, 
                                         autogen_item *item);
LOCAL char *util_add_comment_line(char *destination,
                                  const char *prefix,
                                  const char *line,
                                  unsigned int line_length,
                                  unsigned int hanging_indent);

#if (PMD_FILE_FORMAT >= 600)
LOCAL unsigned int util_get_resulting_alignment_64(unsigned int alignment1, unsigned int alignment2, int align_to_64_bits);
#endif
LOCAL unsigned int util_get_resulting_alignment_32(unsigned int alignment1, unsigned int alignment2);


#ifdef AUTOGEN_ENVIRONMENT_LOCAL
#if (PMD_FILE_FORMAT >= 600)
LOCAL unsigned int util_get_seq_size_from_item(autogen_obj_list* obj_list, autogen_ver* ver, unsigned long long* min_val, unsigned long long* max_val);
#else
LOCAL unsigned int util_get_seq_size_from_item(autogen_obj_list* obj_list, autogen_ver* ver, unsigned int* min_val, unsigned int* max_val);
#endif
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

LOCAL unsigned int util_upper_limit_newlines(const char *text, unsigned int linewidth);


LOCAL autogen_res* s_unique_res_cmn = NULL;
LOCAL autogen_res* s_unique_res_cmn_sym = NULL;
LOCAL autogen_res* s_unique_res_cmn_ext = NULL;
LOCAL autogen_res* s_unique_res_media_ctrl = NULL;
LOCAL autogen_res* s_unique_res_master = NULL;


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_build_unformatted_comment
 
    Purpose: Collects the comment text from the given comment list
 
    Functional Description:
        util_build_unformatted_comment traverses the given comment list, creates
        or reads the text for each item, and concatenates the text for all the
        items into a single text string.

    Arguments: 
         list - [in] Pointer to the first element in the comment list. May be NULL.
         exclusive_type - [in] The type of comment to include, given as e.g.
                               COMMENT_PROPERTY_ISIHDR_ONLY for ISI headers.

    Return Values:
        The method returns a pointer to an unformatted character string allocated
        on the PMD heap. The string may be empty, but will never be NULL.
*/
/* --------------------------------------------------------------------------------------------- */
char *util_build_unformatted_comment(const autogen_cmt* list, int exclusive_type)
{
    static const unsigned int buffer_space_chunk_size = 1000;
    static char* buffer = NULL;
    static char* max_pos = NULL;

    char *current_pos = buffer;
    int display_comment = TRUE;
    autogen_comment_id last_id = COMMENT_NONE;

    /*  Process each comment in the list  */
    for (; list; list = list->next)
    {
        unsigned int itemlen;

        /*  Find text for the comment item at hand  */
        const char* itemText1 = NULL;
        const char* itemText2 = "";
        const char* itemText3 = "";

        switch (list->id)
        {
        case COMMENT_PROPERTY_ISIHDR_ONLY:
        case COMMENT_PROPERTY_HTML_ONLY:
            {
                display_comment = (list->id == exclusive_type);
            }
            itemText1 = "";
            break;

        case COMMENT_PROPERTY_ALL_OUTPUTS:
            {
                display_comment = TRUE;
                itemText1 = "";
            }
            break;

        case COMMENT_PROPERTY_ISIHDR_DISABLE:
            {
                if (exclusive_type == COMMENT_PROPERTY_ISIHDR_ONLY)
                {
                    display_comment = FALSE;
                }
                itemText1 = "";
            }
            break;

        case COMMENT_PROPERTY_HTML_DISABLE:
            {
                if (exclusive_type == COMMENT_PROPERTY_HTML_ONLY)
                {
                    display_comment = FALSE;
                }
                itemText1 = "";
            }
            break;

        case COMMENT_NONE:
            {
                itemText1 = "";
            }
            break;

        case COMMENT_WEB_LINK:
            {
                if (display_comment)
                {
                    if (last_id == COMMENT_PARAGRAPH)
                    {
                        itemText1 = "\n";
                        itemText2 = list->comment;
                    }
                    else
                    {
                        itemText1 = list->comment;
                    }

                    last_id = list->id;
                }
                else
                {
                    itemText1 = "";
                }
            }
            break;

        case COMMENT_TEXT:          /* Fall through */
        case COMMENT_PARAGRAPH:
            {
                if (display_comment)
                {
                    if (last_id == COMMENT_PARAGRAPH ||
                        last_id == COMMENT_BULLET)
                    {
                        itemText1 = "\n";
                        itemText2 = list->comment;
                    }
                    else
                    {
                        itemText1 = list->comment;
                    }

                    last_id = list->id;
                }
                else
                {
                    itemText1 = "";
                }
            }
            break;

        case COMMENT_NEWLINE:
            {
                if (display_comment)
                {
                    if ((last_id == COMMENT_ISIHDR_BEFORE_DEF) ||
                        (last_id == COMMENT_ISIHDR_BEFORE_DEF_16) ||
                        (last_id == COMMENT_ISIHDR_AFTER_DEF) ||
                        (last_id == COMMENT_ISIHDR_AFTER_DEF_16))
                    {
                        itemText1 = "";
                    }
                    else if (last_id == COMMENT_PARAGRAPH)
                    {
                        itemText1 = "\n\n";
                    }
                    else
                    {
                        itemText1 = "\n";
                    }

                    last_id = list->id;
                }
                else
                {
                    itemText1 = "";
                }
            }
            break;

        case COMMENT_BULLET:
            {
                if (display_comment)
                {
                    /* Only add a leading newline if it's not the first comment */
                    itemText1 = (buffer && *buffer) ? "\n- " : "- ";
                    itemText2 = list->comment;

                    last_id = list->id;
                }
                else
                {
                    itemText1 = "";
                }
            }
            break;

        case COMMENT_LINK_TYPE:
            {
                if (display_comment)
                {
                    if (list->linksubname && list->linksubname[0])
                    {
                        itemText1 = list->linkname;
                        itemText2 = " / ";
                        itemText3 = list->linksubname;
                    }
                    else
                    {
                        itemText1 = list->linkname;
                    }

                    last_id = list->id;
                }
                else
                {
                    itemText1 = "";
                }
            }
            break;

        case COMMENT_ISIHDR_BEFORE_DEF:
        case COMMENT_ISIHDR_BEFORE_DEF_16:
        case COMMENT_ISIHDR_AFTER_DEF:
        case COMMENT_ISIHDR_AFTER_DEF_16:
        case COMMENT_ISIHDR_TOP:
        case COMMENT_ISIHDR_TOP_16:
            {
                itemText1 = "";
                last_id = list->id;
            }
            break;

        default:
            {
                itemText1 = "";

                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Default case met in util_build_unformatted_comment(). list->id is %u", list->id);
            }
            break;
        }

        /*  Add the text(s) to the buffer  */
        while (*itemText1)
        {
            itemlen = strlen(itemText1);
            if (current_pos + itemlen > max_pos)
            {
                /* Reallocate the current buffer */
                unsigned int current_size = current_pos - buffer;
                unsigned int new_size = current_size + itemlen + buffer_space_chunk_size;
                char *new_buffer = pmd_heap_alloc(new_size);
                memcpy(new_buffer, buffer, current_size);
                buffer = new_buffer;
                current_pos = buffer + current_size;
                max_pos = buffer + new_size - 1;
            }

            memcpy(current_pos, itemText1, itemlen);
            current_pos += itemlen;
            itemText1 = itemText2;
            itemText2 = itemText3;
            itemText3 = "";
        }
    }

    if (!buffer)
    {
        /* This could happen if we haven't created a comment yet */
        return "";
    }

    *current_pos = 0;
    return buffer;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_error_line
 
    Purpose: 
        Produces an error in the log file autogen.log
 
    Functional Description:
        The produced error depends on the actual environment mode
        If the error is fatal, the tool aborts        

    Arguments: 
        current_file      - [in] the filename of the current message definition file (optional)
        line              - [in] line, where the error origined (optional)
        error_type        - [in] level of the error. AUTOGEN_ERROR_INFO, AUTOGEN_ERROR_FATAL etc.
        env_mask          - [in] for which environments should the error be reported
        detailed_err_desc - [in] number used to point to a detailed description online. 0 = no description.
        error_text        - [in] the actual error textr
*/
/* --------------------------------------------------------------------------------------------- */
void util_error_line(const char* current_file, int line, unsigned int error_type, 
                     unsigned int env_mask, unsigned int detailed_err_desc, char* error_text, ...)
{
    char buffer[20480];
    va_list arg_list;

    va_start(arg_list, error_text);
    vsprintf(buffer, error_text, arg_list);
    va_end(arg_list);

    if (g_autogen_env & env_mask)
    {
        if (line > 0)
        {
            fprintf(g_log, "Line %d: ", line);
        }

        switch (error_type)
        {
        case AUTOGEN_ERROR_INFO:
            {
                fprintf(g_log, "Information: ");
            }
            break;

        case AUTOGEN_ERROR_WARNING:
            {
                fprintf(g_log, "Warning: ");
            }
            break;

        case AUTOGEN_ERROR_WARNING_INTERNAL:
            {
                fprintf(g_log, "Internal warning: ");
            }
            break;

        case AUTOGEN_ERROR_FATAL_INTERNAL:
            {
                fprintf(g_log, "Internal error: ");
            }
            break;

        default:
            {
                fprintf(g_log, "Error: ");
            }
        }

        fprintf(g_log, "%s", buffer);

        if (detailed_err_desc > 0)
        {
            fprintf(g_log, " - Detailed error description: http://rdsuite.europe.nokia.com/products/autogen/documentation/errorcodepage.aspx?name=Error_%d", detailed_err_desc);
        }
        fprintf(g_log, "\n");
    }


    if ((error_type == AUTOGEN_ERROR_FATAL_INTERNAL || error_type == AUTOGEN_ERROR_FATAL) &&
        (g_autogen_env & env_mask))
    {
        printf("\n\nError occured");

        if (line > 0)
        {
            printf(" in line %d", line);
        }
        if (current_file && current_file[0])
        {
            printf(" of file '%s'", current_file);
        }

        printf(":\n- %s\n\n", buffer);

        if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
        {
            printf("Please remove the file from the autogen build and recompile\n\n");
        }

        pmd_heap_free();
        fclose(g_log);
        exit(1);
    }

    /* remember that there were warnings */
    if (error_type == AUTOGEN_ERROR_WARNING && (g_autogen_env & env_mask))
    {
        g_has_warnings = TRUE;
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_hyphens
 
    Purpose: Returns a pointer to the given number of hyphens
 
    Functional Description:
        util_get_hyphens returns a pointer to a zero-terminated string of hyphens.
        The number of hyphens in the string equals the given parameter, unless
        too many hyphens are requested.

    Arguments: 
        num_hyphens - [in] The number of hyphens to return

    Return Values:
        A const string containing the given number of hyphens
*/
/* --------------------------------------------------------------------------------------------- */
const char *util_get_hyphens(unsigned int num_hyphens)
{
    static const char util_hyphens[] = "----------------------------------------"
        "----------------------------------------"
        "----------------------------------------";

    if (num_hyphens >= sizeof(util_hyphens))
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "Too many hyphens (%u) requested in util_get_hyphens()", num_hyphens);

        num_hyphens = sizeof(util_hyphens)-1;
    }

    return util_hyphens + sizeof(util_hyphens) - 1 - num_hyphens;
}
    
    
/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_merge_offset
 
    Purpose: 
        Returns the bit offset of an item within a merged field
 
    Functional Description:
        Returns the bit offset of an item within a merged field.
        The item must be placed in a merged field to obtain a useful offset

    Arguments: 
        item - [in] pointer to the item for which the bit offset is wanted

    Return Values:
        bit offset (0 in case of an error)
*/
/* --------------------------------------------------------------------------------------------- */
unsigned int util_get_merge_offset(autogen_item* item)
{
    unsigned int offset = 0;
    autogen_item* item_trav = (autogen_item*)autogen_obj_get_first_in_list(&item->base.parent->child_list);
    while (item_trav && item_trav != item)
    {
        if (item_trav->base.subtype != AUTOGEN_ITEM_FILLER || !(item_trav->base.flag & AUTOGEN_FILLER_IS_REPLACED))
        {
            offset += abs(item_trav->length);
        }

        item_trav = (autogen_item*)item_trav->base.next;
    }

    return offset;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_spaces
 
    Purpose: Returns a pointer to the given number of spaces
 
    Functional Description:
        util_get_spaces returns a pointer to a zero-terminated string of spaces.
        The number of spaces in the string equals the given parameter, unless
        too many spaces are requested.

    Arguments: 
        num_spaces - [in] The number of spaces to return

    Return Values:
        A const string containing the given number of spaces
*/
/* --------------------------------------------------------------------------------------------- */
const char *util_get_spaces(unsigned int num_spaces)
{
    static const char util_spaces[]  = "                                        "
        "                                        "
        "                                        ";

    if (num_spaces >= sizeof(util_spaces))
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "Too many spaces (%u) requested in util_get_spaces()", num_spaces);

        num_spaces = sizeof(util_spaces)-1;
    }

    return util_spaces + sizeof(util_spaces) - 1 - num_spaces;
}


#ifdef AUTOGEN_ENVIRONMENT_LOCAL

#if (PMD_FILE_FORMAT >= 600)
unsigned int util_get_seq_size(autogen_seq* seq, autogen_ver* ver, unsigned long long* min_val, unsigned long long* max_val)
#else
unsigned int util_get_seq_size(autogen_seq* seq, autogen_ver* ver, unsigned int* min_val, unsigned int* max_val)
#endif
{
    /* initialize return values */
    *min_val = 0;
    *max_val = 0;

    return util_get_seq_size_from_item(&seq->base.child_list, ver, min_val, max_val);
}

#endif /* AUTOGEN_ENVIRONMENT_LOCAL */


/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_base_res
 
    Purpose: 
        Returns a pointer to teh base resource to 'res'
 
    Arguments: 
        res - [in] a resourcer extension

    Return Values:
        pointer to resource object (or NULL if not found, or 'res' is not a resource extension)
*/
/* --------------------------------------------------------------------------------------------- */
autogen_res* util_get_base_res(const autogen_res* res)
{
    autogen_res* base_res = NULL;

    if (res->base.type == AUTOGEN_OBJ_RES && (res->base.subtype & RESOURCE_EXTENSION_ANY))
    {
        autogen_it res_it = INIT_ITERATOR;

        /* find base resource */
        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        res_it.obj.id      = res->base.id;

        if (res->base.subtype == RESOURCE_MEDIA_MODULE_EXTENSION)
        {
            res_it.subtypemask = RESOURCE_MEDIA_MODULE;
        }
        else if (res->base.subtype == RESOURCE_ISI_EXTENSION)
        {
            res_it.subtypemask = RESOURCE_ISI;
        }
        else if (res->base.subtype == RESOURCE_PROTOCOL_EXTENSION)
        {
            res_it.subtypemask = RESOURCE_PROTOCOL;
        }

        if (res->base.subtype)
        {
            base_res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        }
    }

    return base_res;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_unique_res
 
    Purpose: 
        Resturns a pointer to a given resource
 
    Arguments: 
        type - [in] resource type, AUTOGEN_RES_XXX

    Return Values:
        pointer to resource object (or NULL if not found)
*/
/* --------------------------------------------------------------------------------------------- */
autogen_res* util_get_unique_res(unsigned int type)
{
    autogen_res* res = NULL;
    autogen_res** unique_res = NULL;

    if (type == RESOURCE_SYMBOLS)
    {
        unique_res = &s_unique_res_cmn_sym;
    }
    else if (type == RESOURCE_ISI_COMMON_MESSAGES)
    {
        unique_res = &s_unique_res_cmn;
    }
    else if (type == RESOURCE_ISI_COMMON_MESSAGES_EXT)
    {
        unique_res = &s_unique_res_cmn_ext;
    }
    else if (type == RESOURCE_ISI_MEDIA_CONTROL)
    {
        unique_res = &s_unique_res_media_ctrl;
    }

    if (unique_res)
    {
        res = *unique_res;
        }
    if (!res)
    {
        autogen_it res_it = INIT_ITERATOR;

        res_it.typemask    = AUTOGEN_OBJ_RES;
        res_it.subtypemask = type;

        res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);

        if (unique_res)
        {
            *unique_res = res;
        }
    }

    return res;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_ext_res
 
    Purpose: 
        Returns a pointer to a specific resource extension
 
    Arguments: 
        restype - [in] resource type, for which a extension should be found
        resid   - [in] resource ID

    Return Values:
        Pointer to resource object (or NULL if not found)
*/
/* --------------------------------------------------------------------------------------------- */
#if (PMD_FILE_FORMAT >= 600)
autogen_res* util_get_ext_res(unsigned int restype, unsigned long long resid)
#else
autogen_res* util_get_ext_res(unsigned int restype, unsigned int resid)
#endif
{
    autogen_it res_it = INIT_ITERATOR;

    res_it.typemask    = AUTOGEN_OBJ_RES;
    res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
    res_it.obj.id      = resid;

    if (restype == RESOURCE_PROTOCOL)
    {
        res_it.subtypemask = RESOURCE_PROTOCOL_EXTENSION;
    }
    else if (restype == RESOURCE_MEDIA_MODULE)
    {
        res_it.subtypemask = RESOURCE_MEDIA_MODULE_EXTENSION;
    }
    else
    {
        res_it.subtypemask = RESOURCE_ISI_EXTENSION;
    }

    return (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_protocol_res
 
    Purpose: 
        Returns a pointer to a protocol resource
 
    Arguments: 
        name - [in] Name of the protocol (PROTOCOL_XXX)

    Return Values:
        Pointer to resource object (or NULL if not found)
*/
/* --------------------------------------------------------------------------------------------- */

autogen_res* util_get_protocol_res(const char* name)
{
    autogen_it res_it = INIT_ITERATOR;

    res_it.typemask    = AUTOGEN_OBJ_RES;
    res_it.subtypemask = RESOURCE_PROTOCOL;
    res_it.obj.name    = name;

    return (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_res
 
    Purpose: 
        Returns the resource pointer associated for the ISI resource with the given ID. If no 
        existing, NULL is returned
 
    Arguments: 
        id - [in] The ID to retrieve the resource pointer for.

    Return Values:
        Pointer to resource object (or NULL if none)

*/
/* --------------------------------------------------------------------------------------------- */

autogen_res *util_get_res(unsigned int id)
{
    autogen_it res_it = INIT_ITERATOR;

    res_it.typemask    = AUTOGEN_OBJ_RES;
    res_it.subtypemask = RESOURCE_ISI | RESOURCE_ISI_DSP | RESOURCE_ISI_MEDIA_CONTROL;
    res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
    res_it.obj.id      = id;

    return (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
}


const char* util_get_obj_type_name(const autogen_obj* obj)
{
    switch (obj->type)
    {
    case AUTOGEN_OBJ_RES:
        {
            return "Resource";
        }

    case AUTOGEN_OBJ_CONST:
        {
            return "Constant";
        }

    case AUTOGEN_OBJ_SB_TEMPLATE:
        {
            return "Subblock template";
        }

    case AUTOGEN_OBJ_SEQ:
        {
            return "Sequence";
        }

    case AUTOGEN_OBJ_SB:
    case AUTOGEN_OBJ_REF:
        {
            return "Subblock";
        }

    case AUTOGEN_OBJ_MSG_BASE:
        {
            return "Base message";
        }

    case AUTOGEN_OBJ_MSG:
        {
            if ((obj->flag & AUTOGEN_MSG_FUNCTION_MASK) == AUTOGEN_MSG_TRC)
            {
                return "Trace";
            }
            else
            {
                return "Message";
            }
        }

    case AUTOGEN_OBJ_NOTE:
        {
            return "Note";
        }

    case AUTOGEN_OBJ_TRACEGRP:
        {
            return "Trace group";
        }

    case AUTOGEN_OBJ_TRACE:
        {
            return "Trace";
        }

    case AUTOGEN_OBJ_TBL:
        {
            if (obj->subtype == AUTOGEN_TBL_FTD)
            {
                return "FTD table";
            }
            else if (obj->subtype == AUTOGEN_TBL_PPC)
            {
                return "PPC table";
            }
            else if (obj->subtype == AUTOGEN_TBL_CONST)
            {
                return "Constant table";
            }
            else if (obj->subtype == AUTOGEN_TBL_BIT)
            {
                return "Bitmask table";
            }
            else if (obj->subtype == AUTOGEN_TBL_DERCONST)
            {
                return "Derived constant table";
            }
            else if (obj->subtype == AUTOGEN_TBL_DERBIT)
            {
                return "Derived bitmask table";
            }
            else
            {
                return "Table";
            }
        }

    case AUTOGEN_OBJ_ITEM:
        {
            if (obj->subtype == AUTOGEN_ITEM_CASE)
            {
                return "Case";
            }
            else if (obj->subtype == AUTOGEN_ITEM_LST)
            {
                return "List";
            }
            else if (obj->subtype == AUTOGEN_ITEM_PRINTF)
            {
                return "Printf";
            }
            else
                return "Item";
        }

    case AUTOGEN_OBJ_TBLENTRY:
        {
            return "Entry";
        }

    case AUTOGEN_OBJ_DATA:
        {
            if (obj->subtype == AUTOGEN_DATA_FTD)
            {
                return "FTD data";
            }
            else
            {
                return "Entry";
            }
        }

    case AUTOGEN_OBJ_SHARED_FILE:
        {
            return "Shared file";
        }

    case AUTOGEN_OBJ_VERSION_HISTORY:
        {
            return "Version history entry";
        }

    default:
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "Default case met in util_get_obj_type_name(). obj->type is 0x%8.8X", obj->type);
        break;
    }

    return "<unknown object>";
}


const char* util_get_obj_name(const autogen_obj* obj)
{
    if (obj->type == AUTOGEN_OBJ_ITEM)
    {
        if (obj->subtype == AUTOGEN_ITEM_CASE)
        {
            if (obj->flag & AUTOGEN_CASE_DEFAULT)
            {
                return "default";
            }
            else
            {
                return obj->name;
            }
        }
        else
        {
            return ((autogen_item*)obj)->parname;
        }
    }
    else if (obj->type == AUTOGEN_OBJ_MSG && (obj->flag & AUTOGEN_MSG_IS_SUBMSG))
    {
        if (prop_has((autogen_obj*)obj->res, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
        {
            return obj->name;
        }
        else
        {
            char* obj_name = (char*)malloc(strlen(obj->base_obj->name) + strlen(obj->name) + 5);

            strcpy(obj_name, obj->base_obj->name);
            strcat(obj_name, ".");
            strcat(obj_name, obj->name);

            return obj_name;
        }
    }
    else if (obj->type == AUTOGEN_OBJ_TBL && obj->subtype == AUTOGEN_TBL_FTD)
    {
        return "FTD table";
    }
    else if (obj->type == AUTOGEN_OBJ_TBL && obj->subtype == AUTOGEN_TBL_PPC)
    {
        return "PPC table";
    }
    else
    {
        return obj->name;
    }
}

const autogen_obj* util_get_base_parent(const autogen_obj* obj)
{
    const autogen_obj* parent = (const autogen_obj*)obj->parent;

    while (parent && parent->type == AUTOGEN_OBJ_ITEM)
    {
        parent = (const autogen_obj*)parent->parent;
    }

    return parent;
}

#if (PMD_FILE_FORMAT >= 600)
unsigned long long util_get_case_id(const char* name, const char* tblname, autogen_res* tblres, const autogen_ver* ver)
#else
unsigned int util_get_case_id(const char* name, const char* tblname, autogen_res* tblres, const autogen_ver* ver)
#endif
{
    autogen_it tbl_it = INIT_ITERATOR;
    autogen_it entry_it = INIT_ITERATOR;
    autogen_tbl* tbl;
    autogen_tbl* parent_tbl;
    autogen_obj* entry;

    /* find constant table */
    tbl_it.typemask    = AUTOGEN_OBJ_TBL;
    tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_DERCONST;
    tbl_it.obj.name    = tblname;
    tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
    tbl_it.ver         = ver;

    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &tblres->tbl_list);
    if (!tbl)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "Function:util_get_case_id(tblname='%s') Error:tbl=NULL", tblname);
    }

    /* find constant */
    entry_it.typemask = AUTOGEN_OBJ_TBLENTRY;
    entry_it.obj.name = name;
    entry_it.vercrit  = AUTOGEN_OBJ_VERSION_INCLUDES;
    entry_it.ver      = ver;

    parent_tbl = util_get_parent_table(tbl, ver);

    entry = autogen_obj_find_in_list(&entry_it, &parent_tbl->base.child_list);
    if (!entry)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "Function:util_get_case_id() Error:entry %s doesn't exist", name);
    }

    return entry->id;
}

const char* util_get_case_mask(const char* name, const char* tblname, autogen_res* tblres, const autogen_ver* ver)
{
    autogen_it tbl_it = INIT_ITERATOR;
    autogen_it entry_it = INIT_ITERATOR;
    autogen_tbl* tbl;
    autogen_tbl* parent_tbl;
    autogen_bittbl_entry* entry;

    /* find constant table */
    tbl_it.typemask    = AUTOGEN_OBJ_TBL;
    tbl_it.subtypemask = AUTOGEN_TBL_BIT | AUTOGEN_TBL_DERBIT;
    tbl_it.obj.name    = tblname;
    tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
    tbl_it.ver         = ver;

    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &tblres->tbl_list);
    if (!tbl)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "Function:util_get_case_mask(tblname='%s', tblres='%s') Error:tbl=NULL", tblname, tblres->base.name);
    }

    /* find constant */
    entry_it.typemask = AUTOGEN_OBJ_TBLENTRY;
    entry_it.obj.name = name;
    entry_it.vercrit  = AUTOGEN_OBJ_VERSION_INCLUDES;
    entry_it.ver      = ver;

    parent_tbl = util_get_parent_table(tbl , ver);

    entry = (autogen_bittbl_entry*)autogen_obj_find_in_list(&entry_it, &parent_tbl->base.child_list);
    if (!entry)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "Function:util_get_case_mask() Error:entry %s doesn't exist", name);
    }

    return entry->bit_pattern;
}

unsigned int util_get_n_def(autogen_obj_list* obj_list)
{
    unsigned int n_def = 0;

    autogen_obj* item = autogen_obj_get_first_in_list(obj_list);
    while (item && item->type == AUTOGEN_OBJ_ITEM)
    {
        switch (item->subtype)
        {
        case AUTOGEN_ITEM_RANGE_ENTRY:
            {
                /* Do nothing */
            }
            break;
        case AUTOGEN_ITEM_FILLER:
        case AUTOGEN_ITEM_VALUE:
        case AUTOGEN_ITEM_RANGE:
        case AUTOGEN_ITEM_TIMESTAMP:
        case AUTOGEN_ITEM_POINTER:
        case AUTOGEN_ITEM_STRING:
        case AUTOGEN_ITEM_STRUCT:
        case AUTOGEN_ITEM_LST:
        case AUTOGEN_ITEM_MERGE:
        case AUTOGEN_ITEM_REF:
            {
                ++n_def;
            }
            break;

        case AUTOGEN_ITEM_CHOICE:
            {
                autogen_item_choice* item_choice = (autogen_item_choice*)item;

                n_def += util_get_n_def(&item->child_list);

                if (item_choice->default_case)
                {
                    n_def += util_get_n_def(&item_choice->default_case->base.base.child_list);
                }
            }
            break;

        case AUTOGEN_ITEM_CASE:
            {
                if (item->flag & AUTOGEN_CASE_DEFAULT)
                {
                    n_def += util_get_n_def(&item->child_list);
                }
            }
            break;

        default:
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                    "Default case met in util_get_n_def(). item->subtype is 0x%8.8X", item->subtype);
            }
        }

        item = item->next;
    }

    return n_def;
}


autogen_seq* util_get_parent_seq(autogen_item* item)
{
	while (item && item->base.type == AUTOGEN_OBJ_ITEM)
	{
		item = (autogen_item*)item->base.parent;
	}

	return (autogen_seq*)item;
}

/*------------------------------------------------------------------------------------------------

    Name: util_get_parent_table
    
    Purpose: Finds the specified version of the parent table
    
    Functional description:
    Searches for the parent table from which a derived CONST or BIT table has been made.
    In case version refers to an interval then it searches for version based on from-version
    
    Parameters: table and version
    
    Returns: Parent table matching version (from) criteria (or table itself if not a derived table)


------------------------------------------------------------------------------------------------*/

autogen_tbl*  util_get_parent_table(autogen_tbl* tbl , const autogen_ver* ver)
{
    autogen_tbl* parent_tbl = tbl;

    if (tbl && (tbl->base.subtype & (AUTOGEN_TBL_DERCONST | AUTOGEN_TBL_DERBIT)))
    {
        autogen_ver exact_ver ;
        autogen_it tbl_it = INIT_ITERATOR;

        autogen_obj_ver_set(&exact_ver, ver->from, ver->to);

        tbl_it.typemask     = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask  = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
        if (tbl->base.flag & (AUTOGEN_OBJ_IS_SHARED | AUTOGEN_OBJ_IS_SHARED_EXTERNAL))
            tbl_it.obj.name  = tbl->orgtbl->base.name;
        else
            tbl_it.obj.name = tbl->base.base_obj->name;
        tbl_it.vercrit      = AUTOGEN_OBJ_VERSION_COVER_SINGLE;
        tbl_it.ver          = &exact_ver;

        parent_tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &tbl->base.res->tbl_list);
    }

    return parent_tbl;
}


/*------------------------------------------------------------------------------------------------

    Name: util_has_multiple_versions
 
    Purpose: Checks whether different versions of the same object exists
 
    Functional Description:
        util_has_multiple_versions counts the number of different versions of the given
        object in the associated resource lists. If there are more than one version,
        this function returns TRUE, otherwise this function returns false. If the
        resource associated with this object could not be found, a warning is printed
        and this function returns FALSE.

    Arguments: 
        object - [in] The object to check for multiple versions.

    Return Values: TRUE if there are multiple versions, FALSE otherwise.

------------------------------------------------------------------------------------------------*/

int util_has_multiple_versions(const autogen_obj* obj)
{
    /* Prepare iterator to find other versions of the same object */
    autogen_obj_list* list_to_check;
    autogen_res* res = NULL;
    autogen_it obj_it = INIT_ITERATOR;

    obj_it.typemask    = obj->type;
    obj_it.subtypecrit = AUTOGEN_OBJ_SUBTYPE_EXACT;
    obj_it.subtypemask = obj->subtype;
    obj_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
    obj_it.obj.id      = obj->id;
    obj_it.obj.name    = obj->name;

    if ((obj->parent && obj->parent->type == AUTOGEN_OBJ_RES) || (obj->type == AUTOGEN_OBJ_MSG) && (obj->parent->type == AUTOGEN_OBJ_MSG_BASE))
    {
        res = (autogen_res*)obj->parent;
    }
    else
    {
        return FALSE;
    }

    /* Search different lists depending on object type */
    switch (obj->type)
    {
    case AUTOGEN_OBJ_RES:
        list_to_check = &res->ver_list;
        break;
    case AUTOGEN_OBJ_SEQ:
    case AUTOGEN_OBJ_SB:
        {
            unsigned short zeroVer[] = {0,0,0};

            if ((res->base.type | RESOURCE_ISI_SHARED) &&
                (autogen_ver_comp(obj->ver.from, (const unsigned short* )&zeroVer) != AUTOGEN_VER_EQUAL) )
            {
                return TRUE;
            }

            list_to_check = &res->seq_list;
        }
        break;
    case AUTOGEN_OBJ_MSG:
        if ((obj->type == AUTOGEN_OBJ_MSG) && (obj->parent->type == AUTOGEN_OBJ_MSG_BASE))  /* to take submessages into account, that's why */
        {
            list_to_check = &((autogen_seq*)obj->base_obj)->submsg_list;
        }
        else
        {
            list_to_check = &res->msg_list;
        }
        break;
    case AUTOGEN_OBJ_TBL:
        list_to_check = &res->tbl_list;
        break;
    default:
        list_to_check = &obj->parent->child_list;
        break;
    }

    /* Find the first object */
    if (!autogen_obj_find_in_list(&obj_it, list_to_check))
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "util_has_multiple_versions(): Unable to find given object in its resource. "
            "type=0x%08X, name=%s", obj->type, obj->name);
        return FALSE;
    }

    /* If there's only one, return FALSE, otherwise, return TRUE */
    if (!autogen_obj_find_next_in_list(&obj_it))
    {
        return FALSE;
    }

    return TRUE;
}

/*------------------------------------------------------------------------------------------------

    Name: util_has_newer_version
 
    Purpose: Checks whether a newer version of the same object exists
 
    Functional Description:
        util_has_newer_version searches for versions of the given
        object in the associated resoure lists. If there is a newer version,
        this function returns TRUE, otherwise this function returns false. If the
        resource associated with this object could not be found, a warning is printed
        and this function returns FALSE.

    Arguments: 
        object - [in] The object to check for multiple versions.

    Return Values: TRUE if there are multiple versions, FALSE otherwise.

------------------------------------------------------------------------------------------------*/

int util_has_newer_version(const autogen_obj* obj)
{
    /* Prepare iterator to find other versions of the same object */
    autogen_obj_list* list_to_check;
    autogen_obj*         temp_obj;
    autogen_res* res = NULL;
    autogen_it obj_it = INIT_ITERATOR;

    obj_it.typemask    = obj->type;
    obj_it.subtypecrit = AUTOGEN_OBJ_SUBTYPE_EXACT;
    obj_it.subtypemask = obj->subtype;
    obj_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
    obj_it.obj.id      = obj->id;
    obj_it.obj.name    = obj->name;

    if ((obj->parent && obj->parent->type == AUTOGEN_OBJ_RES) || (obj->type == AUTOGEN_OBJ_MSG) && (obj->parent->type == AUTOGEN_OBJ_MSG_BASE))
    {
        res = (autogen_res*)obj->parent;
    }
    else
    {
        return FALSE;
    }

    /* Search different lists depending on object type */
    switch (obj->type)
    {
    case AUTOGEN_OBJ_RES:
        list_to_check = &res->ver_list;
        break;
    case AUTOGEN_OBJ_SEQ:
    case AUTOGEN_OBJ_SB:
        {
            list_to_check = &res->seq_list;
        }
        break;
    case AUTOGEN_OBJ_MSG:
        if ((obj->type == AUTOGEN_OBJ_MSG) && (obj->parent->type == AUTOGEN_OBJ_MSG_BASE))  /* to take submessages into account, that's why */
        {
            list_to_check = &((autogen_seq*)obj->base_obj)->submsg_list;
        }
        else
        {
            list_to_check = &res->msg_list;
        }
        break;
    case AUTOGEN_OBJ_TBL:
        list_to_check = &res->tbl_list;
        break;
    default:
        list_to_check = &obj->parent->child_list;
        break;
    }

    /* Find the first object */
    temp_obj = autogen_obj_find_in_list(&obj_it, list_to_check);
    if (!temp_obj)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "util_has_multiple_versions(): Unable to find given object in its resource. "
            "type=0x%08X, name=%s", obj->type, obj->name);
        return FALSE;
    }

    /* If there is a newer version return TRUE, otherwise return FALSE */
    while (temp_obj)
    {
        int ret_val = autogen_ver_comp(obj->ver.to, temp_obj->ver.to);
        if( ret_val & AUTOGEN_VER_NEWER)
        {
            return TRUE;
        }
        temp_obj = autogen_obj_find_next_in_list(&obj_it);
    }
    /* newer version not found */
    return FALSE;
}


#if (PMD_FILE_FORMAT >= 600)
void  util_get_item_limits(const autogen_item *item, unsigned long long* min_val, unsigned long long* max_val, char* min_val_str, char* max_val_str)
#else
void util_get_item_limits(const autogen_item* item, unsigned int* min_val, unsigned int* max_val, char* min_val_str, char* max_val_str)
#endif
{
    int length = item ? item->length : 0;
    int is_signed = (length < 0) ? TRUE : FALSE;
    unsigned int length_us = abs(length);
    const autogen_prop *minprop = NULL;
    const autogen_prop *maxprop = NULL;

    if (item)
    {
        minprop = prop_find_first(&item->base, PROPERTY_ITEM_MINIMUM_VALUE);
        maxprop = prop_find_first(&item->base, PROPERTY_ITEM_MAXIMUM_VALUE);
    }

    /* initialize return values */
#if (PMD_FILE_FORMAT >= 600)
    *min_val = 0LL;
    *max_val = 0LL;
#else
    *min_val = 0;
    *max_val = 0;
#endif

    min_val_str[0] = 0;
    max_val_str[0] = 0;


#if (PMD_FILE_FORMAT >= 600)
    if (length_us > 64)
    {
        length_us = 64;
    }
    /* set maximum value */
    if (maxprop)
    {
        *max_val = maxprop->value;
        strcpy(max_val_str, maxprop->str);
    }
    else
    {
        if (is_signed)
        {
            signed long long max_val_s = (1 << (length_us - 1)) - 1;
            *max_val = (unsigned long long)max_val_s;
            sprintf(max_val_str, "%lld", *max_val);
        }
        else
        {
            if (length < 64)
            {
                *max_val = (1 << length_us) - 1;
            }
            else
            {
                *max_val = 0xFFFFFFFFFFFFFFFF;
            }
            sprintf(max_val_str, "%llu", *max_val);
        }
    }

    /* set minimum value */
    if (minprop)
    {
        *min_val = minprop->value;
        strcpy(min_val_str, minprop->str);
    }
    else
    {
        if (is_signed)
        {
            int min_val_s = - (1 << (length_us - 1));
            *min_val = (unsigned int)min_val_s;
            sprintf(min_val_str, "%lld", *min_val);
        }
        else
        {
            *min_val = 0;
            strcpy(min_val_str, "0");
        }
    }
#else
    if (length_us > 32)
    {
        length_us = 32;
    }

    /* set maximum value */
    if (maxprop)
    {
        *max_val = maxprop->value;
        strcpy(max_val_str, maxprop->str);
    }
    else
    {
        if (is_signed)
        {
            int max_val_s = (1 << (length_us - 1)) - 1;
            *max_val = (unsigned int)max_val_s;
            sprintf(max_val_str, "%d", *max_val);
        }
        else
        {
            *max_val = 0xFFFFFFFF;
            if (length < 32)
            {
                *max_val = (1 << length_us) - 1;
            }
            sprintf(max_val_str, "%u", *max_val);
        }
    }

    /* set minimum value */
    if (minprop)
    {
        *min_val = minprop->value;
        strcpy(min_val_str, minprop->str);
    }
    else
    {
        if (is_signed)
        {
            int min_val_s = - (1 << (length_us - 1));
            *min_val = (unsigned int)min_val_s;
            sprintf(min_val_str, "%d", *min_val);
        }
        else
        {
            *min_val = 0;
            strcpy(min_val_str, "0");
        }
    }
#endif
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL unsigned int util_get_resulting_alignment_64(unsigned int alignment1, unsigned int alignment2, int align_to_64_bits)
{
    unsigned int alignment;
    unsigned int res_alignment[12][12] =
    {
        /* DWord/DWord                  DWord/Byte1                  DWord/Byte3                 DWord/Odd                    DWord/Word                   DWord/WordAny                DWord/ByteAny                DWord/DDWord                 DWord/Byte5                  DWord/Byte6                  DWord/Byte7                 DWord/DWordAny */ 
        AUTOGEN_ALIGNMENT_DWORD,     AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_DWORD_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_DWORD_ANY, 

        /* Byte1/DWord                  Byte1/Byte1                  Byte1/Byte3                 Byte1/Odd                    Byte1/Word                   Byte1/WordAny                Byte1/ByteAny                Byte1/DDWord                 Byte1/Byte5                  Byte1/Byte6                  Byte1/Byte7                 Byte1/DWordAny */ 
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_1,    AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_BYTE_ANY,

        /* Byte3/DWord                  Byte3/Byte1                  Byte3/Byte3                 Byte3/Odd                    Byte3/Word                   Byte3/WordAny                Byte3/ByteAny                Byte3/DDWord                 Byte3/Byte5                  Byte3/Byte6                  Byte3/Byte7                 Byte3/DWordAny */ 
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_3,   AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_BYTE_ANY,

        /* Odd/DWord                    Odd/Byte1                    Odd/Byte3                   Odd/Odd                      Odd/Word                     Odd/WordAny                  Odd/ByteAny                  Odd/DDWord                   Odd/Byte5                    Odd/Byte6                    Odd/Byte7                   Odd/DWordAny */ 
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_BYTE_ANY,

        /* Word/DWord                   Word/Byte1                   Word/Byte3                  Word/Odd                     Word/Word                    Word/WordAny                 Word/ByteAny                 Word/DDWord                  Word/Byte5                   Word/Byte6                   Word/Byte7                  Word/DWordAny */ 
        AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD,      AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_WORD_ANY,  

        /* WordAny/DWord                WordAny/Byte1                WordAny/Byte3               WordAny/Odd                  WordAny/Word                 WordAny/WordAny              WordAny/ByteAny              WordAny/DDWord               WordAny/Byte5                WordAny/Byte6                WordAny/Byte7               WordAny/DWordAny */ 
        AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_WORD_ANY,  

        /* ByteAny/DWord                ByteAny/Byte1                ByteAny/Byte3               ByteAny/Odd                  ByteAny/Word                 ByteAny/WordAny              ByteAny/ByteAny              ByteAny/DDWord               ByteAny/Byte5                ByteAny/Byte6                ByteAny/Byte7               ByteAny/DWordAny */
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  

        /* DDWord/DWord                 DDWord/Byte1                 DDWord/Byte3                DDWord/Odd                   DDWord/Word                  DDWord/WordAny               DDWord/ByteAny               DDWord/DDWord                DDWord/Byte5                 DDWord/Byte6                 DDWord/Byte7                DDWord/DWordAny */
        AUTOGEN_ALIGNMENT_DWORD_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_DDWORD,    AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_DWORD_ANY, 

        /* Byte5/DWord                  Byte5/Byte1                  Byte5/Byte3                 Byte5/Odd                    Byte5/Word                   Byte5/WordAny                Byte5/ByteAny                Byte5/DDWord                 Byte5/Byte5                  Byte5/Byte6                  Byte5/Byte7                 Byte5/DWordAny */
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_5,    AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,

        /* Byte6/DWord                  Byte6/Byte1                  Byte6/Byte3                 Byte6/Odd                    Byte6/Word                   Byte6/WordAny                Byte6/ByteAny                Byte6/DDWord                 Byte6/Byte5                  Byte6/Byte6                  Byte6/Byte7                 Byte6/DWordAny */
        AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_6,    AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_WORD_ANY,

        /* Byte7/DWord                  Byte7/Byte1                  Byte7/Byte3                 Byte7/Odd                    Byte7/Word                   Byte7/WordAny                Byte7/ByteAny                Byte7/DDWord                 Byte7/Byte5                  Byte7/Byte6                  Byte7/Byte7                 Byte7/DWordAny */
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_ODD,      AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_7,   AUTOGEN_ALIGNMENT_BYTE_ANY, 

        /* DWordAny/DWord               DWordAny/Byte1               DWordAny/Byte3              DWordAny/Odd                 DWordAny/Word                DWordAny/WordAny             DWordAny/ByteAny             DWordAny/DDWord              DWordAny/Byte5               DWordAny/Byte6               DWordAny/Byte7              DWordAny/DWordAny */
        AUTOGEN_ALIGNMENT_DWORD_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_DWORD_ANY, AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, AUTOGEN_ALIGNMENT_DWORD_ANY, 
    };

    if (!align_to_64_bits)
    {
        alignment = util_get_resulting_alignment_32(alignment1, alignment2);
    }
    else
    {
        if (alignment1 == AUTOGEN_ALIGNMENT_UNDEFINED || alignment2 == AUTOGEN_ALIGNMENT_BYTE_ANY)
        {
            alignment = alignment2;
        }
        else if (alignment2 == AUTOGEN_ALIGNMENT_UNDEFINED || alignment1 == AUTOGEN_ALIGNMENT_BYTE_ANY)
        {
            alignment = alignment1;
        }
        else
        {
            alignment = res_alignment[alignment1-1][alignment2-1];
        }
    }

    return alignment;
}
#endif

LOCAL unsigned int util_get_resulting_alignment_32(unsigned int alignment1, unsigned int alignment2)
{
    unsigned int alignment;
    unsigned int res_alignment[6][6] =
    {
        /* Dword/Dword                  Dword/Byte1                  DWord/Byte3 */
        AUTOGEN_ALIGNMENT_DWORD,     AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, 
        /* DWord/Odd                    DWord/Word                   DWord/WordAny */ 
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,

        /* Byte1/Dword                  Byte1/Byte1                  Byte1/Byte3 */
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_1,    AUTOGEN_ALIGNMENT_ODD,       
        /* Byte1/Odd                    Byte1/Word                   Byte1/WordAny */ 
        AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, 

        /* Byte3/Dword                  Byte3/Byte1                  Byte3/Byte3 */
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_3,    
        /* Byte3/Odd                    Byte3/Word                   Byte3/WordAny */ 
        AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY , AUTOGEN_ALIGNMENT_BYTE_ANY, 

        /* Odd/Dword                    Odd/Byte1                    Odd/Byte3 */
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_ODD,       
        /* Odd/Odd                      Odd/Word                     Odd/WordAny */ 
        AUTOGEN_ALIGNMENT_ODD,       AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, 

        /* Word/Dword                   Word/Byte1                   Word/Byte3 */
        AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, 
        /* Word/Odd                     Word/Word                    Word/WordAny */ 
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD,      AUTOGEN_ALIGNMENT_WORD_ANY, 

        /* WordAny/Dword                WordAny/Byte1                WordAny/Byte3 */
        AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_BYTE_ANY, 
        /* WordAny/Odd                  WordAny/Word                 WordAny/WordAny */ 
        AUTOGEN_ALIGNMENT_BYTE_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY,  AUTOGEN_ALIGNMENT_WORD_ANY, 
    };

    if (alignment1 == AUTOGEN_ALIGNMENT_UNDEFINED || alignment2 == AUTOGEN_ALIGNMENT_BYTE_ANY)
    {
        alignment = alignment2;
    }
    else if (alignment2 == AUTOGEN_ALIGNMENT_UNDEFINED || alignment1 == AUTOGEN_ALIGNMENT_BYTE_ANY)
    {
        alignment = alignment1;
    }
    else
    {
        alignment = res_alignment[alignment1-1][alignment2-1];
    }

    return alignment;
}

unsigned int util_get_resulting_alignment(unsigned int alignment1, unsigned int alignment2, int align_to_64_bits)
{
    unsigned int alignment;
#if (PMD_FILE_FORMAT >= 600)
    alignment = util_get_resulting_alignment_64(alignment1, alignment2, align_to_64_bits);
#else
    align_to_64_bits;
    alignment = util_get_resulting_alignment_32(alignment1, alignment2);
#endif
    return alignment;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_wrap_words
 
    Purpose: Performs word wrapping on the given text
 
    Functional Description:
        util_wrap_words works on a buffer of unformatted text. It builds a buffer
        with formatted text, adding prefix in front of the first line, adding separator
        before subsequent lines, and adding suffix after the last line. Lines are
        broken at existing linefeeds, and if the length of a line exceeds the given
        line length (not counting the length of any prefix or separator).

    Arguments: 
        unformatted - [in] Unformatted text.
        line_len - [in] The maximum length of each line of bare comment text.
        prefix - [in] String added in front of the first line.
        separator - [in] String added in front of subsequent lines.
        suffix - [in] String added after the first line.

    Return Values:
        The method returns a pointer to a formatted character string allocated
        on the PMD heap. The string may be empty, but will never be NULL.
*/
/* --------------------------------------------------------------------------------------------- */
char *util_wrap_words(const char *unformatted,
                      unsigned int line_len,
                      const char *prefix,
                      const char *separator,
                      const char *suffix)
{
    static char *formatted = NULL;
    static unsigned int buffer_size = 0;

    /*  Variables used in formatting  */
    const char* this_line = unformatted;
    const char* last_space = 0;
    const char* first_char_after_space = 0;
    const char* current = unformatted-1;
    char *formatted_pos = NULL;
    unsigned int hanging_indent = 0;

    /*  Ensure that output buffer is of sufficient size */
    unsigned int max_newlines = util_upper_limit_newlines(unformatted, line_len);
    unsigned int extra_space_newlines = (strlen(separator)+3) * max_newlines;
    unsigned int affix_space = strlen(prefix) + strlen(suffix);
    unsigned int total_space = strlen(unformatted) + extra_space_newlines + affix_space + 1;
    const char *line_prefix = prefix;
    if (total_space > buffer_size)
    {
        buffer_size = total_space;
        formatted = (char *) pmd_heap_alloc(buffer_size);
    }
    formatted_pos = formatted;

    /*  Perform multi-line formatting  */
    while (*++current)
    {
        if (*current == '\n')
        {
            /*  Terminate current line and reset indicators  */
            formatted_pos = util_add_comment_line(formatted_pos, line_prefix,
                this_line, current-this_line,
                hanging_indent);
            line_prefix = separator;
            this_line = current + 1;
            last_space = 0;
            first_char_after_space = 0;
            hanging_indent = 0;
        }
        else
        {
            /* Check next character on the line */
            if (*current == ' ' || *current == '\t')
            {
                if (!last_space || first_char_after_space)
                {
                    /* We're not currently looking at spaces. Mark the last space */
                    last_space = current;
                    first_char_after_space = 0;
                }
            }
            else
            {
                if (last_space && !first_char_after_space)
                {
                    /* We've ended looking at spaces. Mark the first character */
                    first_char_after_space = current;
                }
            }

            /* Check if a word wrap should be performed */
            if (last_space && (unsigned int)(current-this_line) + hanging_indent >= line_len)
            {
                /* Break and output the current line */
                formatted_pos = util_add_comment_line(formatted_pos, line_prefix,
                    this_line, last_space-this_line,
                    hanging_indent);
                line_prefix = separator;

                /* Check if hanging indent should be enabled */
                if (this_line[0] == '-' && this_line[1] == ' ')
                {
                    hanging_indent = 2;
                }

                /* Find the start of the new line */
                if (first_char_after_space)
                {
                    this_line = first_char_after_space;
                }
                else
                {
                    /*  Find the first non-space character */
                    this_line = last_space + 1;
                    while (*this_line && (*this_line == ' ' || *this_line == '\t' ||
                        *this_line == '\r' || *this_line == '\n'))
                    {
                        this_line++;
                    }
                }

                /* Reset indicators */
                last_space = 0;
                first_char_after_space = 0;
                current = this_line - 1;
            }
        }
    }

    /* Output any remaining data */
    formatted_pos = util_add_comment_line(formatted_pos, line_prefix,
        this_line, current-this_line,
        hanging_indent);
    strcpy(formatted_pos-1, suffix); /* Skip the linefeed added above */
    return formatted;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: util_validate_printf_format_string
 
    Purpose: Validates the printf format string in PRINTF macro and the associated arguments
 
    Functional Description:
        The format string is similar to a C printf format string with the restrictions listed below.

        The following is validated:
        * All format specifiers are syntactical correct, ie %<format specifier>
        * Only allowed format specifiers are used (not all format specifiers from C printf is allowed)
          See below for the allowed ones.
        * Number of arguments matches number of format specifiers
        * Type of arguments matches corresponding format specifier.

        Allowed format specifiers
            c, d, i, o, u, x, X, p, s, %

    Arguments: 
        file     - [in] Macro file name. Output in case of errors.
        line     - [in] Line number of the printf macro. Output in case of errors.
        format   - [in] The printf format string to be validated
        arg_list - [in] List of arguments for the printf format string

    Return Values:
        none
*/
/* --------------------------------------------------------------------------------------------- */
void util_validate_printf_format_string(const char *file, int line, const char *format, autogen_obj_list *arg_list)
{
    int i = 0;
    int no_args = 0;
    int no_percent = 0;
    autogen_obj *obj = NULL;

    /* Number of arguments */
    no_args = arg_list->n_obj;

    /* Loop through all arguments and compare to the corresponding format specifiers */
    obj = autogen_obj_get_first_in_list(arg_list);
    while (obj && obj->type == AUTOGEN_OBJ_ITEM)
    {
        int search_percent = 1;
        autogen_item *item = (autogen_item *)obj;

        /* Skip FILLER items */
        if (item->base.subtype == AUTOGEN_ITEM_FILLER)
        {
            /* Continue with next argument */
            obj = obj->next;
            continue;
        }

        /* Find next % but skip all %% */
        search_percent = 1;
        while (search_percent)
        {
            /* Skip until the next % character in format string */
            while (format[i] != '\0' && format[i] != '%') i++;

            /* Check if it is a %% */
            if (format[i] == '%' && format[i+1] == '%')
            {
                /* Skip it and continue finding the next % */
                search_percent = 1;
                i += 2;
            } 
            else
            {
                /* Found start of a real %<specifier>. Continue after loop */
                search_percent = 0;
            }
        }

        /* Have we found the next format specification or end-of-line */
        if (format[i++] == '%')
        {
            /* Found a format specification. */
            int found = 0;
            int continue_search = 1;

            /* Skip all the format specification content and search for the 
            type character at the end of the format specification */
            while (continue_search && format[i] != '\0')
            {
                switch(format[i])
                {
                case 'c':  /* Allowed type characters (% already handled) */
                case 'd':
                case 'i':
                case 'o':
                case 'u':
                case 'x':
                case 'X':
                case 'p':
                case 's':
                    /* Found type char */
                    found = 1;
                    continue_search = 0;
                    break;
                case '%':
                    /* Type character missing. Found next format specification starting with % */
                    found = 0;
                    continue_search = 0;
                    break;
                default:
                    /* Character part of format specification. Continue */
                    continue_search = 1;
                    i++;
                    break;
                }
            }

            /* Found the type character? */
            if (!found)
            {
                /* Error */
                util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "Invalid format string in printf");
            }

            no_percent++;

            /* Validate that the specifier and argument matches */
            util_validate_printf_argument(file, line, format[i], item);

            i++;
        }
        else
        {
            /* End-of-line. Does number match with number of arguments */
            if (no_args != no_percent)
            {
                /* Error */
                util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "Number of arguments does not match number of %%<specifier> in printf");
            }
            return;
        }

        /* Next argument in list */
        obj = obj->next;
    }

    /* Check if there is more % in the format string. Skip %%'s */
    while (format[i] != '\0')
    {
        /* Skip until end-of-string or next % */
        while (format[i] != '\0' && format[i] != '%') i++;

        /* End of string encountered? */
        if (format[i] == '\0')
            break;

        /* Found % */
        if (format[i+1] == '%')
        {
            /* Skip %% */
            i += 2;
            continue;
        }

        /* Error */
        util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
            "Number of arguments does not match number of %%<specifier> in printf.");
    }
    return;
}


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_validate_printf_argument
 
    Purpose: Validate that a given format specifier matches the corresponding item argument.
 
    Functional Description:
        Validates that:
        * Format specifier matches the type of the item argument
        * Item restrictions are fulfilled. (Item type dependend)

    Arguments: 
        file      - [in] Macro file name. Output in case of errors.
        line      - [in] Line number of the printf macro. Output in case of errors.
        specifier - [in] The printf format specifier to be checked against the argument
        item      - [in] The item argument to be checked against the format specifier

    Return Values:
        none
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void util_validate_printf_argument(const char *file, int line, char type, autogen_item *item)
{
    switch (item->base.subtype)
    {
    case AUTOGEN_ITEM_VALUE:
        {
            autogen_item_value *value_item = (autogen_item_value *)item;

            if (strchr("cdiouxX", type) == NULL)
            {
                /* Wrong specifier */
                util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "Format specifier %%%c do not match value argument", type);
            }

            if (type == 'c' && value_item->pres.type != AUTOGEN_PRESENTATION_ASCII_CHAR)
            {
                /* Wrong presentation type for %c */
                util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "Value argument for format specifier %%c must use presentation type ASCII_CHAR in printf");
            }

            if (strchr("diu", type) != NULL)
            {
                if (value_item->pres.type != AUTOGEN_PRESENTATION_DEC)
                {
                    /* Wrong presentation type for above %<specifier>'s */
                    util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                        "Value argument for format specifier %%%c must use presentation type DEC in printf", type);
                }
            }

            if (strchr("oxX", type) != NULL)
            {
                if (value_item->pres.type != AUTOGEN_PRESENTATION_HEX)
                {
                    /* Wrong presentation type for above %<specifier>'s */
                    util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                        "Value argument for format specifier %%%c must use presentation type HEX in printf", type);
                }
            }
        }
        break;
    case AUTOGEN_ITEM_STRING:
        {
            autogen_item_string *string_item = (autogen_item_string *)item;

            if (type != 's')
            {
                /* Wrong specifier */
                util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "Format specifier %%%c do not match string argument", type);
            }

            if (!(string_item->base.base.flag & AUTOGEN_STRING_ASCII))
            {
                /* Wrong type for %s */
                util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "String argument for format specifier %%s must use string type STRING_ASCII or STRING_ASCII_ZERO_TERMINATED in printf");
            }

        }
        break;
    case AUTOGEN_ITEM_POINTER:
        {
            if (type != 'p')
            {
                /* Wrong specifier */
                util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                    "Format specifier %%%c do not match pointer argument", type);
            }
        }
        break;
    default:
        {
            /* Error - Macro not allowed in this context */
            util_error_line(file, line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0, 
                "Macro '%s' not allowed as argument for printf.", item->varname);
        }
        break;
    }
}


/* --------------------------------------------------------------------------------------------- */
/* Concatenates the given prefix, line and linefeed at the given destination point */
/* Returns the new destination point */
/* --------------------------------------------------------------------------------------------- */
LOCAL char *util_add_comment_line(char *destination,
                                  const char *prefix,
                                  const char *line,
                                  unsigned int line_length,
                                  unsigned int hanging_indent)
{
    /* Write prefix */
    unsigned int prefix_length = strlen(prefix);
    memcpy(destination, prefix, prefix_length);
    destination += prefix_length;

    /* Write hanging indent */
    while (hanging_indent--)
    {
        *destination++ = ' ';
    }

    /* Write line */
    memcpy(destination, line, line_length);
    destination += line_length;

    /* Write linefeed */
    *destination++ = '\n';
    return destination;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_seq_size_from_item
 
    Purpose: 
        Returns the size of a sequence, calculated from a certain item
 
    Functional Description:
        Returns the size of the sequence containing 'item'. The calculation is started from 'item',
        even though item is not the first item in the sequence.
        The size is calculated and added to min_val and max_val which are then returned.
        
    Arguments: 
        item    - [in] the item in the seuence from which the size should be calculated from
        ver     - [in] version for which the calculation should be performed
        min_val - [in,out] minimum size (in bytes) of the sequence
        max_val - [in,out] maximum size (in bytes) of the sequence

    Return Values:
        type of size
         AUTOGEN_SIZE_EQUAL - the min and max size are equal
         AUTOGEN_SIZE_INTERVAL - the min and max size are different
         AUTOGEN_SIZE_ASMANYASPOSSIBLE - size is aa long as possible (min and max sizes not valid)
*/
/* --------------------------------------------------------------------------------------------- */
#ifdef AUTOGEN_ENVIRONMENT_LOCAL

#if (PMD_FILE_FORMAT >= 600)
LOCAL unsigned int util_get_seq_size_from_item(autogen_obj_list* obj_list, autogen_ver* ver, unsigned long long* min_val, unsigned long long* max_val)
#else
LOCAL unsigned int util_get_seq_size_from_item(autogen_obj_list* obj_list, autogen_ver* ver, unsigned int* min_val, unsigned int* max_val)
#endif
{
    unsigned int size_type = 0;
    const autogen_seq* seq = NULL;
    autogen_item* item;
    autogen_it item_it = INIT_ITERATOR;

    item_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
    item_it.ver     = ver;

    item = (autogen_item*)autogen_obj_find_in_list(&item_it, obj_list);
    if (item)
    {
        seq = (const autogen_seq*)util_get_base_parent(&item->base);
    }
    while (item)
    {
#if (PMD_FILE_FORMAT >= 600)
        signed long long ref_min = 0;
        signed long long ref_max = 0;
        unsigned long long el_size_min = 0;
        unsigned long long el_size_max = 0;
        unsigned long long el_n_min = 0;
        unsigned long long el_n_max = 0;
#else
        int ref_min = 0;
        int ref_max = 0;

        unsigned int el_size_min = 0;
        unsigned int el_size_max = 0;
        unsigned int el_n_min = 0;
        unsigned int el_n_max = 0;
#endif


        /* set min/max number of elements */
        switch (item->agg_type)
        {
        case AGG_TYPE_FIXED_SINGLE:
        case AGG_TYPE_FIXED_MULTIPLE:
            {
                el_n_min = item->agg_n;
                el_n_max = item->agg_n;

                if (item->base.subtype == AUTOGEN_ITEM_STRING)
                {
                    el_n_min *= ((autogen_item_string*)item)->length;
                    el_n_max *= ((autogen_item_string*)item)->length;
                }
            }
            break;

        case AGG_TYPE_DYNAMIC_REF:
            {
                char max_val_str[2*AUTOGEN_MAX_NAME_LENGTH];
                char min_val_str[2*AUTOGEN_MAX_NAME_LENGTH];

                reference_get_limits(item, &ref_min, &ref_max, min_val_str, max_val_str);

                /* special addition of zero-termination */
                if (item->base.subtype == AUTOGEN_ITEM_STRING &&
                    prop_has(&item->base, PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH))
                {
                    ++ref_min;
                    ++ref_max;

                    strcat(min_val_str, " + 1");
                    strcat(max_val_str, " + 1");
                }

                el_n_min = (unsigned int)ref_min;
                el_n_max = (unsigned int)ref_max;
            }
            break;

        case AGG_TYPE_DYNAMIC_ALIGNMENT:
            {
                el_n_min = 1;
                el_n_max = 1;
            }
            break;

        case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
        case AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH:
            {
                if (prop_has((autogen_obj*)item, PROPERTY_STRING_MAXIMUM_LENGTH))
                {
                    el_n_min = 1;
                    el_n_max = prop_get_value((autogen_obj*)item, PROPERTY_STRING_MAXIMUM_LENGTH);

                    size_type = AUTOGEN_SIZE_INTERVAL;
                }
                else if (prop_has((autogen_obj*)item, PROPERTY_ARRAY_MAXIMUM_SIZE))
                {
                    el_n_min = 0;
                    el_n_max = prop_get_value((autogen_obj*)item, PROPERTY_ARRAY_MAXIMUM_SIZE);

                    size_type = AUTOGEN_SIZE_INTERVAL;
                }
                else
                {
                    el_n_min = 1;
                    el_n_max = 1;

                    size_type = AUTOGEN_SIZE_ASMANYASPOSSIBLE;
                }
            }
            break;

        case AGG_TYPE_DYNAMIC_ZEROTERMINATED:
            {
                if (prop_has((autogen_obj*)item, PROPERTY_STRING_MAXIMUM_LENGTH))
                {
                    el_n_min = 1;
                    el_n_max = prop_get_value((autogen_obj*)item, PROPERTY_STRING_MAXIMUM_LENGTH);

                    size_type = AUTOGEN_SIZE_INTERVAL;
                }
                else
                {
                    el_n_min = 1;
                    el_n_max = 1;

                    size_type = AUTOGEN_SIZE_ASMANYASPOSSIBLE;
                }
            }
            break;

        case AGG_TYPE_DYNAMIC_OPTIONAL:
            {
                el_n_min = 0;
                el_n_max = 0;

                size_type = AUTOGEN_SIZE_ASMANYASPOSSIBLE;
            }
            break;
        }

        /* set element min/max size */
        switch (item->base.subtype)
        {
        case AUTOGEN_ITEM_VALUE:
        case AUTOGEN_ITEM_RANGE:
        case AUTOGEN_ITEM_TIMESTAMP:
        case AUTOGEN_ITEM_POINTER:
        case AUTOGEN_ITEM_MERGE:
        case AUTOGEN_ITEM_REF:
            {
                el_size_min = (unsigned int)(abs(item->length)/8);
                el_size_max = el_size_min;

                /* set device ID / object ID special types */
                if (item->base.subtype == AUTOGEN_ITEM_VALUE)
                {
                    autogen_item_value* value1 = (autogen_item_value*)item;
                    autogen_item_value* value2 = (autogen_item_value*)item->base.next;

                    if (value1->pres.type == AUTOGEN_PRESENTATION_PN_CONST &&
                        value1->pres.subtype == PN_DEVICE &&
                        value2 &&
                        value2->base.base.subtype == AUTOGEN_ITEM_VALUE &&
                        value2->pres.type == AUTOGEN_PRESENTATION_PN_CONST &&
                        value2->pres.subtype == PN_OBJECT_16)
                    {
                        value1->base.special_number_type = PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE;
                        value2->base.special_number_type = PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_OBJECT;
                    }
                }
                else if (item->base.subtype == AUTOGEN_ITEM_REF)
                {
                    if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH && prop_has(&seq->base, PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY) ||
                        item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH   && prop_has(&seq->base, PROPERTY_MSG_LENGTH_RELATES_TO_DATA_PART_ONLY))
                    {
                        *min_val = 0;
                        *max_val = 0;

                        el_n_min = 0;
                        el_n_max = 0;
                    }
                }
                /* if merge, check if SB_ID or SB_LENGTH are defined correctly */
                else if (item->base.subtype == AUTOGEN_ITEM_MERGE)
                {
                    /* bit offset in merge */
                    unsigned int offset = 0;

                    int clear_length = FALSE;

                    autogen_item* merge_item = (autogen_item*)autogen_obj_get_first_in_list(&item->base.child_list);
                    while (merge_item)
                    {
                        if (merge_item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID ||
                            merge_item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH ||
                            merge_item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID ||
                            merge_item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH ||
                            merge_item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID)
                        {
                            /* these special items must be byte aligned */
                            if ((offset % 8) != 0)
                            {
                                util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_ALL, 0,
                                    "The '%s' item is placed at illegal offset in %s '%s'",
                                    merge_item->base.name,
                                    util_get_obj_type_name((autogen_obj*)seq), 
                                    util_get_obj_name((autogen_obj*)seq));
                            }

                            if (merge_item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH && prop_has(&seq->base, PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY) ||
                                merge_item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH   && prop_has(&seq->base, PROPERTY_MSG_LENGTH_RELATES_TO_DATA_PART_ONLY))
                            {
                                *min_val = 0;
                                *max_val = 0;

                                clear_length = TRUE;
                            }
                            else
                            {
                                offset += abs(merge_item->length);
                            }
                        }
                        else
                        {
                            offset += abs(merge_item->length);
                        }

                        merge_item = (autogen_item*)merge_item->base.next;
                    }

                    /* special handling, when a seq length should be calculated for data part only */
                    if (clear_length)
                    {
                        el_size_min = offset/8;
                        el_size_max = offset/8;
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_FILLER:
            {
                if (item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
                {
                    if (item->length == 16)
                    {
                        el_size_min = (*min_val % 2) > 0 ? (unsigned int)(2 - (*min_val % 2)) : 0;
                        el_size_max = (*max_val % 2) > 0 ? (unsigned int)(2 - (*max_val % 2)) : 0;
                    }
                    else if (item->length == 24)
                    {
                        el_size_min = (*min_val % 4) != 3 ? (unsigned int)(3 - (*min_val % 4)) : 0;
                        el_size_max = (*max_val % 4) != 3 ? (unsigned int)(3 - (*max_val % 4)) : 0;
                    }
                    else if (item->length == 32)
                    {
                        el_size_min = (*min_val % 4) > 0 ? (unsigned int)(4 - (*min_val % 4)) : 0;
                        el_size_max = (*max_val % 4) > 0 ? (unsigned int)(4 - (*max_val % 4)) : 0;
                    }
                }
                else
                {
                    el_size_min = (unsigned int)(abs(item->length)/8);
                    el_size_max = (unsigned int)(abs(item->length)/8);
                }
            }
            break;

        case AUTOGEN_ITEM_LST:
            {
                int first = TRUE;
                autogen_seq_ref* ref;
                autogen_it ref_it = INIT_ITERATOR;

                ref_it.vercrit = AUTOGEN_OBJ_VERSION_OVERLAP;
                ref_it.ver     = ver;

                ref = (autogen_seq_ref*)autogen_obj_find_in_list(&ref_it, &item->base.child_list);
                while (ref)
                {
#if (PMD_FILE_FORMAT >= 600)
                    unsigned long long sb_size_min;
                    unsigned long long sb_size_max;
#else
                    unsigned int sb_size_min;
                    unsigned int sb_size_max;
#endif

                    /* calculate the size of the sequence */
                    if (util_get_seq_size(ref->seqptr, ver, &sb_size_min, &sb_size_max) == AUTOGEN_SIZE_ASMANYASPOSSIBLE)
                    {
                        size_type = AUTOGEN_SIZE_ASMANYASPOSSIBLE;
                    }

                    /* update general sb min/max size */
                    if (first)
                    {
                        el_size_min = sb_size_min;
                        el_size_max = sb_size_max;

                        first = FALSE;
                    }
                    else
                    {
                        if (sb_size_min < el_size_min)
                        {
                            el_size_min = sb_size_min;
                        }
                        if (sb_size_max > el_size_max)
                        {
                            el_size_max = sb_size_max;
                        }
                    }

                    ref = (autogen_seq_ref*)autogen_obj_find_next_in_list(&ref_it);
                }
            }
            break;

        case AUTOGEN_ITEM_STRING:
            if (item->base.flag & AUTOGEN_STRING_UNICODE)
            {
                el_size_min = 2;
                el_size_max = 2;
            }
            else
            {
                el_size_min = 1;
                el_size_max = 1;
            }
            break;

        case AUTOGEN_ITEM_CHOICE:
            {
                autogen_item_choice* choice = (autogen_item_choice*)item;
                int first = TRUE;
#if (PMD_FILE_FORMAT >= 600)
                unsigned long long case_size_min = 0;
                unsigned long long case_size_max = 0;
#else
                unsigned int case_size_min = 0;
                unsigned int case_size_max = 0;
#endif
                autogen_it case_it = INIT_ITERATOR;
                autogen_item* case_item;

                /* find the releated sequence */
                case_it.typemask    = AUTOGEN_OBJ_ITEM;
                case_it.subtypemask = AUTOGEN_ITEM_CASE;
                case_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                case_it.ver         = ver;

                case_item = (autogen_item*)autogen_obj_find_in_list(&case_it, &choice->base.base.child_list);
                while (case_item)
                {
#if (PMD_FILE_FORMAT >= 600)
                    unsigned long long init_size_min = *min_val;
                    unsigned long long init_size_max = *max_val;
#else
                    unsigned int init_size_min = *min_val;
                    unsigned int init_size_max = *max_val;
#endif

                    unsigned int case_size_type = util_get_seq_size_from_item(&case_item->base.child_list, ver, &init_size_min, &init_size_max);

                    init_size_min -= *min_val;
                    init_size_max -= *max_val;

                    if (first)
                    {
                        case_size_min = init_size_min;
                        case_size_max = init_size_max;

                        first = FALSE;
                    }
                    else
                    {
                        if (case_size_min < init_size_min)
                        {
                            case_size_min = init_size_min;
                        }
                        if (case_size_max > init_size_max)
                        {
                            case_size_max = init_size_max;
                        }
                    }

                    if (case_size_type == AUTOGEN_SIZE_ASMANYASPOSSIBLE)
                    {
                        size_type = AUTOGEN_SIZE_ASMANYASPOSSIBLE;
                    }

                    case_item = (autogen_item*)autogen_obj_find_next_in_list(&case_it);
                }

                if (choice->default_case)
                {
                    el_size_min = *min_val;
                    el_size_max = *max_val;

                    util_get_seq_size_from_item(&choice->default_case->base.base.child_list, ver, &el_size_min, &el_size_max);

                    el_size_min -= *min_val;
                    el_size_max -= *max_val;
                }

                if (case_size_min < el_size_min)
                {
                    el_size_min = case_size_min;
                }
                if (case_size_max > el_size_max)
                {
                    el_size_max = case_size_max;
                }
            }
            break;

        case AUTOGEN_ITEM_STRUCT:
            {
                autogen_item_struct* item_struct = (autogen_item_struct*)item;

                autogen_it seq_it = INIT_ITERATOR;
                autogen_seq* seq;

                /* find the releated sequence */
                seq_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
                seq_it.obj.name = item_struct->seqname;
                seq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                seq_it.ver      = ver;

                seq = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &item->seq->base.res->seq_list);

                /* calculate the size of the sequence */
                if (seq)
                {
                    if (util_get_seq_size(seq, ver, &el_size_min, &el_size_max) == AUTOGEN_SIZE_ASMANYASPOSSIBLE)
                    {
                        size_type = AUTOGEN_SIZE_ASMANYASPOSSIBLE;
                    }
                }
            }
            break;

        case AUTOGEN_ITEM_TRCSTRUCTURE:
        case AUTOGEN_ITEM_BLOCK:
        case AUTOGEN_ITEM_RANGE_ENTRY:
            {
                el_size_min = 1;
                el_size_max = 1;
            }
            break;

        default:
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in util_get_seq_size(). item->base.subtype is 0x%8.8X", item->base.subtype);
        }

        /* update size object */
        if (size_type == AUTOGEN_SIZE_ASMANYASPOSSIBLE)
        {
        }
        else
        {
            *min_val += el_n_min * el_size_min;
            *max_val += el_n_max * el_size_max;

            if (*min_val == *max_val)
            {
                size_type = AUTOGEN_SIZE_EXACT;
            }
            else
            {
                size_type = AUTOGEN_SIZE_INTERVAL;
            }
        }

        /* next item in the sequence */
        item = (autogen_item*)autogen_obj_find_next_in_list(&item_it);
    }

    return size_type;
}

#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

/* --------------------------------------------------------------------------------------------- */
/* Calculates the worst case number of newlines in the given text if wrapped */
/* --------------------------------------------------------------------------------------------- */
LOCAL unsigned int util_upper_limit_newlines(const char *text, unsigned int linewidth)
{
    unsigned int num_lines = 1;
    const char* check_line = text;
    while (*check_line)
    {
        if (*check_line++ == '\n')
        {
            ++num_lines;
        }
    }
    return num_lines + (unsigned int) (check_line - text) / linewidth;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_is_obj_in_list
 
    Purpose: 
        Used for detecting if object is in list
 
    Arguments: 
        obj              - [in] pointer to search object
        obj_list         - [in] array of pointers to search
        elements_in_list - [in] number of elements in the list

    Return Values:
        0 if not found
        else found
*/
/* --------------------------------------------------------------------------------------------- */
int util_is_obj_in_list(autogen_obj* obj, autogen_obj** obj_list, unsigned int elements_in_list)
{
    unsigned int index = 0;
    for(index = 0; index<elements_in_list; ++index)
    {
        if(obj->obj_id == obj_list[index]->obj_id)
        {
            return 1; /* Found */    
        }
    }

    return 0;/* Not found */
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_is_string_number
 
    Purpose: 
        Returns TRUE, if the string 'str_value' represents a number
 
    Arguments: 
        str_value - [in] string to investigate

    Return Values:
        this function return TRUE/FALSE
*/
/* --------------------------------------------------------------------------------------------- */
int util_is_string_number(const char* str_value)
{
    unsigned int n;
    int is_number = TRUE;

    if (str_value)
    {
        for (n = 0; n < strlen(str_value); n++)
        {
            if (!isdigit(str_value[n]))
            {
                is_number = FALSE;
                break;
            }
        }

        return is_number;
    }
    else
    {
        return FALSE;
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_is_predefined_constant
 
    Purpose: 
        Returns TRUE, if the constant 'name' is a predefined constant, as defined in global.h
 
    Arguments: 
        name - [in] constant to investigate

    Return Values:
        this function return TRUE/FALSE
*/
/* --------------------------------------------------------------------------------------------- */
int util_is_predefined_constant(const char* name)
{
    return (!strcmp(name, "TRUE") ||
            !strcmp(name, "FALSE") ||
            !strcmp(name, "YES") ||
            !strcmp(name, "NO") ||
            !strcmp(name, "OK") ||
            !strcmp(name, "FAIL") ||
            !strcmp(name, "COLD") ||
            !strcmp(name, "WARM") ||
            !strcmp(name, "ON") ||
            !strcmp(name, "OFF") ||
            !strcmp(name, "ENABLED") ||
            !strcmp(name, "DISABLED"));
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_ver_to_text
 
    Purpose: 
        Returns the text representation of a resource-version
 
    Arguments: 
        res - [in] The resource

    Return Values:
        The version in text format
*/
/* --------------------------------------------------------------------------------------------- */
const char* util_ver_to_text(const autogen_ver* ver)
{
    static char ver_str[31];

    strcpy(ver_str, "-");

    if (ver->ver_str)
    {
        strncpy(ver_str, ver->ver_str, 30);
    }
    else if (ver->system == AUTOGEN_VERSION_DSP)
    {
        if (ver->type == AUTOGEN_OBJ_VERSION_FROM)
        {
            sprintf(ver_str, "%03hu.%03hu.%03hu", ver->from[0], ver->from[1], ver->from[2]);
        }
        else if (ver->type == AUTOGEN_OBJ_VERSION_TO)
        {
            sprintf(ver_str, "%03hu.%03hu.%03hu", ver->to[0], ver->to[1], ver->to[2]);
        }
        else if (ver->type == AUTOGEN_OBJ_VERSION_EXACT)
        {
            sprintf(ver_str, "%03hu.%03hu.%03hu", ver->from[0], ver->from[1], ver->from[2]);
        }
        else if (ver->type == AUTOGEN_OBJ_VERSION_INTERVAL)
        {
            sprintf(ver_str, "%03hu.%03hu.%03hu - %03hu.%03hu.%03hu", 
                ver->from[0], ver->from[1], ver->from[2], ver->to[0], ver->to[1], ver->to[2]);
        }
    }
    else
    {
        if (ver->type == AUTOGEN_OBJ_VERSION_FROM)
        {
            sprintf(ver_str, "%03hu.%03hu", ver->from[0], ver->from[1]);
        }
        else if (ver->type == AUTOGEN_OBJ_VERSION_TO)
        {
            sprintf(ver_str, "%03hu.%03hu", ver->to[0], ver->to[1]);
        }
        else if (ver->type == AUTOGEN_OBJ_VERSION_EXACT)
        {
            sprintf(ver_str, "%03hu.%03hu", ver->from[0], ver->from[1]);
        }
        else if (ver->type == AUTOGEN_OBJ_VERSION_INTERVAL)
        {
            sprintf(ver_str, "%03hu.%03hu - %03hu.%03hu", ver->from[0], ver->from[1], ver->to[0], ver->to[1]);
        }
    }

    return ver_str;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_write_version_file
 
    Purpose: 
        Writes the version data to a file, that can be read by the autobuilder
 
    Arguments: 
        filename - [in] file to make as output
        version  - [in] version to write in file

    Return Values:
        void
*/
/* --------------------------------------------------------------------------------------------- */
/* Functions for integrating into the autobuilder */
void util_write_version_file(const char* filename,
                             const autogen_ver* version)
{
    FILE* f_version = NULL;

    char version_filename[AUTOGEN_MAX_NAME_LENGTH*2];
    sprintf(version_filename, "%s%s", filename, ".autobuilder_info");

    f_version = fopen(version_filename, "wt");
    if (f_version == NULL)
    {
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
            "Unable to create file \"%s\" for TSA implementation file output", filename);
    }
    fprintf(f_version, "<info><version>");
    fprintf(f_version, util_ver_to_text(version));
    fprintf(f_version, "</version></info>");
    fclose(f_version);
}

#if (PMD_FILE_FORMAT >= 600)
int util_get_msgid_range(autogen_res* res, unsigned long long* from, unsigned long long* to)
#else
int util_get_msgid_range(autogen_res* res, unsigned int* from, unsigned int* to)
#endif
{
    autogen_it msg_it = INIT_ITERATOR;
    autogen_obj* msg;

    int has_range = FALSE;

    *from = 0;
    *to   = 0;

    msg_it.typemask = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;

    msg = autogen_obj_find_in_list(&msg_it, &res->msg_list);
    while (msg)
    {
        if (has_range)
        {
            *from = (*from > msg->id) ? msg->id : *from;
            *to   = (*to   < msg->id) ? msg->id : *to;
        }
        else
        {
            *from = msg->id;
            *to   = msg->id;

            has_range = TRUE;
        }

        msg = autogen_obj_find_next_in_list(&msg_it);
    }

    return has_range;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_tracegroup_type
 
    Purpose: 
        Returns the trace type, related to a given resource type
 
    Arguments: 
        res - [in] pointer to resource object

    Return Values:
        trace type (AUTOGEN_OBJ_TRACEGRP_XXX)
*/
/* --------------------------------------------------------------------------------------------- */
unsigned int util_get_tracegroup_type(const autogen_res* res)
{
    unsigned int trc_type = AUTOGEN_OBJ_TRACEGRP_NONE;

    if (res)
    {
        unsigned int n;

        for (n = 1; n < AUTOGEN_OBJ_TRACEGRP_MAX && trc_type == AUTOGEN_OBJ_TRACEGRP_NONE; n++)
        {
            if (res->base.subtype & g_trcgrp_conf[n].trc_res_ids)
            {
                trc_type = n;
            }
        }
    }

    return trc_type;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: util_get_tracegroup_type_from_refname
 
    Purpose: 
        Returns the trace type, related to a given resource type
 
    Arguments: 
        res - [in] reference name, e.g. "TRACE_ID"

    Return Values:
        trace type (AUTOGEN_OBJ_TRACEGRP_XXX)
*/
/* --------------------------------------------------------------------------------------------- */
unsigned int util_get_tracegroup_type_from_refname(const char* refname)
{
    unsigned int trc_type = AUTOGEN_OBJ_TRACEGRP_NONE;
    unsigned int n;

    for (n = 1; n < AUTOGEN_OBJ_TRACEGRP_MAX && trc_type == AUTOGEN_OBJ_TRACEGRP_NONE; n++)
    {
        if (!strcmp(g_trcgrp_conf[n].trace_entity_id_refname, refname) ||
            !strcmp(g_trcgrp_conf[n].trace_group_id_refname, refname) ||
            !strcmp(g_trcgrp_conf[n].trace_id_refname, refname))
        {
            trc_type = n;
        }
    }

    return trc_type;
}

/* get pointer to global resource configuration */
const autogen_res_conf* util_get_res_conf(unsigned int res_type)
{
    const autogen_res_conf* res_conf = NULL;
    unsigned int n;

    for (n = 0; n < AUTOGEN_RESOURCE_TYPES_MAX && !res_conf; n++)
    {
        if (g_res_conf[n].res_type == res_type)
        {
            res_conf = &g_res_conf[n];
        }
    }

    return res_conf;
}

/* get pointer to global symbol configuration */
const autogen_symbol_conf* util_get_sym_conf_by_type(unsigned int type)
{
    const autogen_symbol_conf* sym_conf = NULL;
    unsigned int n;

    for (n = 0; n < AUTOGEN_SYMBOL_TYPES_MAX && !sym_conf; n++)
    {
        if (g_symbol_conf[n].type == type)
        {
            sym_conf = &g_symbol_conf[n];
        }
    }

    return sym_conf;
}

/* get pointer to global symbol configuration */
const autogen_symbol_conf* util_get_sym_conf_by_name(const char* name)
{
    const autogen_symbol_conf* sym_conf = NULL;
    unsigned int n;

    for (n = 0; n < AUTOGEN_SYMBOL_TYPES_MAX && !sym_conf && name; n++)
    {
        if (!strcmp(name, g_symbol_conf[n].name))
        {
            sym_conf = &g_symbol_conf[n];
        }
    }

    return sym_conf;
}

/* get pointer to global symbol configuration */
const autogen_symbol_conf* util_get_sym_conf_by_tblname(const char* tblname)
{
    const autogen_symbol_conf* sym_conf = NULL;
    unsigned int n;

    for (n = 0; n < AUTOGEN_SYMBOL_TYPES_MAX && !sym_conf && tblname; n++)
    {
        if (!strcmp(tblname, g_symbol_conf[n].tblname))
        {
            sym_conf = &g_symbol_conf[n];
        }
    }

    return sym_conf;
}

const char* util_get_filename(const char* filepath)
{
    const char* filename = NULL;

    /* find filename in path */
    if (strrchr(filepath, '\\'))
    {
        filename = strrchr(filepath, '\\') + 1;
    }
    else if (strrchr(filepath, '/'))
    {
        filename = strrchr(filepath, '/') + 1;
    }

    return filename;
}

/*  End of file autogen_util.c  */
