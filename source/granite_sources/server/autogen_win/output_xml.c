/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_xml.c
                -------------
                SW Module






Project:          autogen

%name:            output_xml.c %
%version:         co1tss#67 %
%instance:        co1pctls_1 %
%derived_by:      eliasen %
%date_modified:   Fri Feb 04 16:04:42 2011 %

Copyright (c) Nokia. All right reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the source code for the XML output generator.
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#ifdef AUTOGEN_ENVIRONMENT_LOCAL

#include "autogen_def.h"
#include "autogen_ref.h"
#include "autogen_check.h"
#include "autogen_object.h"
#include "autogen_prop.h"
#include "autogen_util.h"
#include "pmd_heap.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL static
#endif /* LOCAL */

#define XML_NEWLINE_BEFORE         0x0001
#define XML_NEWLINE_AFTER          0x0002
#define XML_NEWLINE_NONE           0x0004

#define XML_TAB_SIZE                4

typedef struct t_xml_environment
{
    /* pointer to the xml file */
    FILE* fxml;

    /* filename */
    char* filename;

    /* pointer to the current resource */
    autogen_res* res;

    /* handle to heap to be used for all allocations */
    pmd_heap_handle* heap_handle;

    /* buffer allocated for string buffer handling */
    char* char_buffer;

} xml_environment;

/* Utilities */
LOCAL unsigned int xml_calc_chars(int field_length);

/* General element constructs */
LOCAL const char* xml_print_element_start_tag(xml_environment* env, const char* el_name);
LOCAL void xml_print_element_start_tag_end(xml_environment* env, int new_line);
LOCAL void xml_print_element_end_tag(xml_environment* env, const char* el_name);
LOCAL void xml_print_element_end_tag_comment(xml_environment* env, const char* el_name, const autogen_obj* obj);
LOCAL void xml_print_element_end_tag_empty(xml_environment* env);
LOCAL void xml_print_element_simple(xml_environment* env, const char* el_name);
LOCAL void xml_print_text(xml_environment* env, const char* text);

/* Attributes */
LOCAL void xml_print_attr_bool(xml_environment* env, const char* attr_name, int value);
#if (PMD_FILE_FORMAT >= 600)
LOCAL void xml_print_attr_int(xml_environment* env, const char* attr_name, signed long long value);
#else
LOCAL void xml_print_attr_int(xml_environment* env, const char* attr_name, int value);
#endif
LOCAL void xml_print_attr_float_f(xml_environment* env, const char* attr_name, double value);
LOCAL void xml_print_attr_float_g(xml_environment* env, const char* attr_name, double value);
#if (PMD_FILE_FORMAT >= 600)
LOCAL void xml_print_attr_hex(xml_environment* env, const char* attr_name, unsigned long long value, int n_chars);
#else
LOCAL void xml_print_attr_hex(xml_environment* env, const char* attr_name, unsigned int value, int n_chars);
#endif
LOCAL void xml_print_attr_names(xml_environment* env, const autogen_item* item, int print_varname);
LOCAL void xml_print_attr_string(xml_environment* env, const char* attr_name, const char* format, ...);
LOCAL void xml_print_attr_version(xml_environment* env, const char* attr_name, const autogen_ver* ver, unsigned int type);
LOCAL void xml_print_attr_version_span(xml_environment* env, const autogen_obj* obj);
LOCAL void xml_print_attr_featureflag_operand(xml_environment* env, unsigned int flag_logic, const char *flag, const char *value);

/* File header/footer */
LOCAL void xml_generate_file(xml_environment* env);
LOCAL void xml_generate_file_header(xml_environment* env);
LOCAL void xml_generate_file_footer(xml_environment* env);

/* Common elements */
LOCAL void xml_generate_element_count(xml_environment* env, autogen_item* item);
LOCAL void xml_generate_element_description(xml_environment* env, const autogen_obj* obj);
LOCAL void xml_generate_element_description_notes(xml_environment* env, autogen_res* res);
LOCAL void xml_generate_element_from_property(xml_environment* env, const autogen_item_value* item, const char* el_name, autogen_property_id prop_id, int multiple_values);
LOCAL void xml_generate_element_presentation(xml_environment* env, const autogen_item_value* item);
LOCAL void xml_generate_element_featureflag(xml_environment* env, const autogen_feature *feature_flag);
LOCAL void xml_generate_element_filler_replacement(xml_environment* env, const autogen_obj* obj);
LOCAL void xml_generate_element_suppress_autogen_warnings(xml_environment* env, const autogen_obj* obj);

/* Project info */
LOCAL void xml_generate_element_project_info(xml_environment* env, const autogen_obj* obj);

/* ISI Header info*/
LOCAL void xml_generate_element_isihdr_info(xml_environment* env, const autogen_obj* obj);

/* HTML info */
LOCAL void xml_generate_element_html_info(xml_environment* env, const autogen_obj* obj);

/* PMD info */
LOCAL void xml_generate_element_pmd_info(xml_environment* env, const autogen_obj* obj);

/* Version history */
LOCAL void xml_generate_element_version_history(xml_environment* env);

/* Shared files */
LOCAL void xml_generate_element_shared_files(xml_environment* env);

/* Constants */
LOCAL void xml_generate_element_constants(xml_environment* env);

/* Message pairs */
LOCAL void xml_generate_element_related_messages(xml_environment* env, autogen_obj* msg);

/* Tables */
LOCAL void xml_generate_element_tables(xml_environment* env);
LOCAL void xml_generate_element_constant_table(xml_environment* env, autogen_tbl* tbl, const char* tbl_name);
LOCAL void xml_generate_element_constant_table_subset(xml_environment* env, autogen_tbl* tbl);
LOCAL void xml_generate_element_bitmask_table(xml_environment* env, autogen_tbl* tbl);
LOCAL void xml_generate_element_bitmask_table_subset(xml_environment* env, autogen_tbl* tbl);
LOCAL void xml_generate_element_ftd_table(xml_environment* env, autogen_tbl* tbl);
LOCAL void xml_generate_element_ftd_mode(xml_environment* env, const autogen_obj* obj);
LOCAL void xml_generate_element_ppc_table(xml_environment* env, autogen_tbl* tbl);


/* Sequences */
LOCAL void xml_generate_sequences(xml_environment* env, unsigned int obj_type, const char* outer_el_name, const char* el_name);
LOCAL void xml_generate_element_structures(xml_environment* env);
LOCAL void xml_generate_element_subblocks(xml_environment* env);
LOCAL void xml_generate_element_subblock_templates(xml_environment* env);
LOCAL void xml_generate_element_message(xml_environment* env, autogen_obj* msg);
LOCAL void xml_generate_element_messages(xml_environment* env);
LOCAL void xml_generate_element_traces(xml_environment* env);


/* Sequence items */
LOCAL void xml_generate_sequence_items(xml_environment* env, autogen_obj_list* obj_list, int print_details);
LOCAL void xml_generate_element_array_start(xml_environment* env, autogen_item* item, int print_details);
LOCAL void xml_generate_element_array_end(xml_environment* env, const autogen_item* item);
LOCAL void xml_generate_element_array_of_bytes(xml_environment* env, autogen_item* item, int print_details);
LOCAL void xml_generate_element_filler(xml_environment* env, const autogen_item* item, int print_details);
LOCAL void xml_generate_element_irregular_structure(xml_environment* env, autogen_item* item, int print_details);
LOCAL void xml_generate_element_number(xml_environment* env, autogen_item_value* item, int print_details);
LOCAL void xml_generate_element_protocol_reference(xml_environment* env, autogen_item_block* item, int print_details);
LOCAL void xml_generate_element_dll_data_flags(xml_environment* env, autogen_item_block* item);
LOCAL void xml_generate_element_external_decoder(xml_environment* env, autogen_item_block* item, int print_details);
LOCAL void xml_generate_element_phonet_msg_block(xml_environment* env, autogen_item_block* item, int print_details);
LOCAL void xml_generate_element_pmd_anchor(xml_environment* env, autogen_item_block* item, int print_details);
LOCAL void xml_generate_element_raw_data_block(xml_environment* env, autogen_item_block* item, int print_details);
LOCAL void xml_generate_element_x_file_block(xml_environment* env, autogen_item_block* item, int print_details);
LOCAL void xml_generate_element_selection(xml_environment* env, autogen_item_choice* choice, int print_details);
LOCAL void xml_generate_element_string(xml_environment* env, autogen_item_string* item, int print_details);
LOCAL void xml_generate_element_structure_reference(xml_environment* env, autogen_item_struct* item, int print_details);
LOCAL void xml_generate_element_subblock_list(xml_environment* env, autogen_item* item, int print_details, int only_ids);
LOCAL void xml_generate_element_string_bcd_map(xml_environment* env, const autogen_obj* obj);
LOCAL void xml_generate_element_printf(xml_environment* env, autogen_item_printf* item, int print_details);

/* ================================================================================================ */
/* Utilities */
/* ================================================================================================ */

/* Find number of hexadecimal characters needed in presentation */
LOCAL unsigned int xml_calc_chars(int field_length)
{
    unsigned int n_chars = 2;

    if (abs(field_length) > 32)
    {
        n_chars = 16;
    }
    else if (abs(field_length) > 16)
    {
        n_chars = 8;
    }
    else if (abs(field_length) > 8)
    {
        n_chars = 4;
    }

    return n_chars;
}


/* ================================================================================================ */
/* General element constructs */
/* ================================================================================================ */

LOCAL const char* xml_print_element_start_tag(xml_environment* env, const char* el_name)
{
    fprintf(env->fxml, "<%s", el_name);

    return el_name;
}

LOCAL void xml_print_element_start_tag_end(xml_environment* env, int new_line)
{
    fprintf(env->fxml, ">%s", new_line ? "\n" : "");
}
        
LOCAL void xml_print_element_end_tag(xml_environment* env, const char* el_name)
{
    fprintf(env->fxml, "</%s>\n", el_name);
}

LOCAL void xml_print_element_end_tag_comment(xml_environment* env, const char* el_name, const autogen_obj* obj)
{
    if ((obj->cmt_list) || (obj->prop_list) || (obj->feature_flags))
    {
        fprintf(env->fxml, ">\n");
        xml_generate_element_featureflag(env, obj->feature_flags);
        xml_generate_element_description(env, obj);
        xml_generate_element_isihdr_info(env, obj);
        xml_generate_element_html_info(env, obj);
        xml_generate_element_pmd_info(env, obj);
        xml_generate_element_suppress_autogen_warnings(env, obj);
        xml_print_element_end_tag(env, el_name);
    }
    else
    {
        xml_print_element_end_tag_empty(env);
    }
}

LOCAL void xml_print_element_end_tag_empty(xml_environment* env)
{
    fprintf(env->fxml, " />\n");
}

LOCAL void xml_print_element_simple(xml_environment* env, const char* el_name)
{
    xml_print_element_start_tag(env, el_name);
    xml_print_element_end_tag_empty(env);
}

/*
Scans the input string for illegel characters: ", ', &, <, and >
" is converted to &quot;
' is converted to &#39; (as IE does not like &apos;)
& is converted to &amp;
< is converted to &lt;
> is converted to &gt;
Other non-printable characters are removed
*/
LOCAL void xml_print_text(xml_environment* env, const char* text)
{
    size_t n, len = text ? strlen(text) : 0;

    for (n = 0; n < len; n++)
    {
        switch(text[n])
        {
        case '\"':
            fprintf(env->fxml, "&quot;");
            break;

        case '\'':
            fprintf(env->fxml, "&#39;");
            break;

        case '&':
            fprintf(env->fxml, "&amp;");
            break;

        case '<':
            fprintf(env->fxml, "&lt;");
            break;

        case '>':
            fprintf(env->fxml, "&gt;");
            break;

        default:
            if (isprint((unsigned char)text[n]) || text[n] == '%') 
            {
                fputc(text[n], env->fxml);
            }
            break;
        }
    }
}

/* ================================================================================================ */
/* Attributes */
/* ================================================================================================ */

LOCAL void xml_print_attr_bool(xml_environment* env, const char* attr_name, int value)
{
    xml_print_attr_string(env, attr_name, value ? "true" : "false");
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL void xml_print_attr_int(xml_environment* env, const char* attr_name, signed long long value)
#else
LOCAL void xml_print_attr_int(xml_environment* env, const char* attr_name, int value)
#endif
{
#if (PMD_FILE_FORMAT >= 600)
    xml_print_attr_string(env, attr_name, "%lld", value);
#else
    xml_print_attr_string(env, attr_name, "%d", value);
#endif
}

LOCAL void xml_print_attr_float_g(xml_environment* env, const char* attr_name, double value)
{
    xml_print_attr_string(env, attr_name, "%g", value);
}

LOCAL void xml_print_attr_float_f(xml_environment* env, const char* attr_name, double value)
{
    xml_print_attr_string(env, attr_name, "%f", value);
}
#if (PMD_FILE_FORMAT >= 600)
LOCAL void xml_print_attr_hex(xml_environment* env, const char* attr_name, unsigned long long value, int n_chars)
#else
LOCAL void xml_print_attr_hex(xml_environment* env, const char* attr_name, unsigned int value, int n_chars)
#endif
{
    n_chars;

#if (PMD_FILE_FORMAT >= 600)
    xml_print_attr_string(env, attr_name, "%llu", value);
#else
    xml_print_attr_string(env, attr_name, "%u", value);
#endif
}

LOCAL void xml_print_attr_names(xml_environment* env, const autogen_item* item, int print_varname)
{
    xml_print_attr_string(env, "Name", item->parname);

    if (print_varname)
    {
        xml_print_attr_string(env, "VarName", item->varname);
    }
}

LOCAL void xml_print_attr_string(xml_environment* env, const char* attr_name, const char* format, ...)
{
    va_list arg_list;
    
    va_start(arg_list, format);
    vsprintf(env->char_buffer, format, arg_list);
    va_end(arg_list);

    fprintf(env->fxml, " %s=\"", attr_name);
    xml_print_text(env, env->char_buffer);
    fprintf(env->fxml, "\"");
}

LOCAL void xml_print_attr_version(xml_environment* env, const char* attr_name, const autogen_ver* ver, unsigned int type)
{
    if (ver->ver_str)
    {
        xml_print_attr_string(env, attr_name, ver->ver_str);
    }
    else if (type == AUTOGEN_OBJ_VERSION_FROM)
    {
        xml_print_attr_string(env, attr_name, "%03d.%03d", ver->from[0], ver->from[1]);
    }
    else 
    {
        xml_print_attr_string(env, attr_name, "%03d.%03d", ver->to[0], ver->to[1]);
    }
}

LOCAL void xml_print_attr_version_span(xml_environment* env, const autogen_obj* obj)
{
    /* From version */
    if ((obj->parent->type == AUTOGEN_OBJ_RES || obj->type == AUTOGEN_OBJ_MSG) && (obj->ver.from[0] != 0 || obj->ver.from[1] != 0))
    {
        xml_print_attr_version(env, "ValidFrom", &obj->ver, AUTOGEN_OBJ_VERSION_FROM);
    }
    else if (!(autogen_ver_comp(obj->ver.from, obj->parent->ver.from) & AUTOGEN_VER_EQUAL) && (obj->ver.from[0] != 0 || obj->ver.from[1] != 0))
    {
        xml_print_attr_version(env, "ValidFrom", &obj->ver, AUTOGEN_OBJ_VERSION_FROM);
    }
    /* To version */
    if ((obj->parent->type == AUTOGEN_OBJ_RES || obj->type == AUTOGEN_OBJ_MSG) && obj->ver.to[0] != 256)
    {
        xml_print_attr_version(env, "ObsoleteFrom", &obj->ver, AUTOGEN_OBJ_VERSION_TO);
    }
    else if (!(autogen_ver_comp(obj->ver.to, obj->parent->ver.to) & AUTOGEN_VER_EQUAL) && obj->ver.to[0] != 256)
    {
        xml_print_attr_version(env, "ObsoleteFrom", &obj->ver, AUTOGEN_OBJ_VERSION_TO);
    }
}

LOCAL void xml_print_attr_featureflag_operand(xml_environment* env, unsigned int flag_logic, const char *flag, const char *value)
{
    xml_print_element_start_tag(env, "Operand");
    if (flag_logic == FT_NOTDEF_FLAG || flag_logic == FT_DEF_FLAG)
    {
        xml_print_attr_string(env, "Name", "AUTOGEN_%s", flag);
        xml_print_attr_string(env, "Value", (flag_logic == FT_DEF_FLAG ? "ON" : "OFF"));
    }
    else
    {
        xml_print_attr_string(env, "Name", flag);
        xml_print_attr_string(env, "Value", value);
    }
    xml_print_element_end_tag_empty(env);
}

/* ================================================================================================ */
/* File header / footer */
/* ================================================================================================ */

LOCAL void xml_generate_file_header(xml_environment* env)
{
    /* XML identification */
    fprintf(env->fxml, "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");

    /* autogen XML version and schema location */
    xml_print_element_start_tag(env, "AutogenXml");
    xml_print_attr_string(env, "Version", "3.004");
    xml_print_attr_string(env, "xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    xml_print_attr_string(env, "xsi:noNamespaceSchemaLocation", "http://rdsuite.europe.nokia.com/products/autogen/files/autogen_xml.xsd");
    xml_print_element_start_tag_end(env, TRUE);

	if (env->res->base.subtype == RESOURCE_SYMBOLS)
	{
	    xml_print_element_start_tag(env, "CommonSymbols");
	    xml_print_element_start_tag_end(env, TRUE);
		return;
	}

    /* Resource header */
    xml_print_element_start_tag(env, env->res->conf->xml_name);
    xml_print_attr_string(env, "Name", env->res->logical_name);

    /* Resource type dependent... */
    switch (env->res->base.subtype)
    {
    case RESOURCE_ISI:
    case RESOURCE_TRC_MASTER:
        {
        xml_print_attr_string(env, "PhonetName", env->res->base.name);
        if (env->res->base.id != AUTOGEN_NO_RESOURCE_ID)
        {
            xml_print_attr_hex(env, "PhonetId", (unsigned int)env->res->base.id, 2);
        }
        xml_print_attr_bool(env, "SupportsCommonMessages", env->res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES);
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;

    case RESOURCE_TRC_MCU:
        {
        xml_print_attr_string(env, "PhonetName", env->res->resnameshort_l);
        xml_print_attr_bool(env, "SupportsCommonMessages", env->res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES);
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;

    case RESOURCE_ISI_MEDIA_CONTROL:
    case RESOURCE_ISI_PREFIX:
        {
        xml_print_attr_string(env, "PhonetName", env->res->base.name);
        xml_print_attr_hex(env, "PhonetId", (unsigned int)env->res->base.id, env->res->base.subtype == RESOURCE_ISI_PREFIX ? 4 : 2);
        xml_print_attr_bool(env, "SupportsCommonMessages", env->res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES);
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;

    case RESOURCE_ISI_EXTENSION:
        {
        xml_print_attr_string(env, "PhonetName", env->res->base.name);
		xml_print_attr_hex(env, "PhonetId", (unsigned int)env->res->base.id, env->res->base.id > 0xFF ? 4 : 2);
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;

    case RESOURCE_ISI_SHARED:
        {
        xml_print_attr_string(env, "PhonetName", env->res->base.name);
        xml_print_attr_hex(env, "PhonetId", (unsigned int)env->res->base.id, env->res->base.id > 0xFF ? 4 : 2);
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;

    case RESOURCE_ISI_COMMON_MESSAGES:
    case RESOURCE_ISI_COMMON_MESSAGES_EXT:
        {
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;

    case RESOURCE_ISI_PRIVATE:
        {
        xml_print_attr_string(env, "PrivateName", env->res->base.name);
        xml_print_attr_hex(env, "PrivateId", (unsigned int)env->res->base.id, 4);
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;

    case RESOURCE_PHONET:
    case RESOURCE_PHONET_EXT:
        {
        xml_print_attr_string(env, "PhonetName", env->res->base.name);
        xml_print_attr_hex(env, "PhonetId", (unsigned int)env->res->base.id, 2);
        }
        break;

    case RESOURCE_PROTOCOL:
    case RESOURCE_PROTOCOL_EXTENSION:
        {
        xml_print_attr_string(env, "ProtocolName", env->res->base.name);
        xml_print_attr_hex(env, "ProtocolId", (unsigned int)env->res->base.id, 4);
        }
        break;

    case RESOURCE_MEDIA_MODULE:
    case RESOURCE_MEDIA_MODULE_EXTENSION:
        {
        xml_print_attr_string(env, "MediaName", env->res->base.name);
        xml_print_attr_hex(env, "MediaId", (unsigned int)env->res->base.id, 2);
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;

    case RESOURCE_TRC_INVARIANT:
    case RESOURCE_TRC_VENDOR:
        {
        xml_print_attr_string(env, "EntityName", env->res->base.name);
        xml_print_attr_hex(env, "EntityId", env->res->base.id, xml_calc_chars(env->res->trc_conf->entity_size));
        xml_print_attr_version(env, "Version", &env->res->base.ver, AUTOGEN_OBJ_VERSION_FROM);
        }
        break;
    case RESOURCE_TRC_ADSP5:
    case RESOURCE_TRC_CDSP5:
    case RESOURCE_TRC_HSP:
    case RESOURCE_TRC_SYMBIAN:
        {
        xml_print_attr_string(env, "EntityName", env->res->resnameshort_l);
        }
        break;

    /* Nothing done for RESOURCE_TRC_OS and RESOURCE_TRC_HAL. Just Name used */

    default:
        break;

    }

    xml_print_element_start_tag_end(env, TRUE);

    /* Resource description */
    xml_generate_element_description(env, &env->res->base);

    /* Project info */
    xml_generate_element_project_info(env, &env->res->base);

    /* ISI Header info*/
    xml_generate_element_isihdr_info(env, &env->res->base);

    /* HTML info */
    xml_generate_element_html_info(env, &env->res->base);

    /* PMD info */
    xml_generate_element_pmd_info(env, &env->res->base);

    xml_generate_element_suppress_autogen_warnings(env, &env->res->base);

    /* Description notes */
    xml_generate_element_description_notes(env, env->res);
}

LOCAL void xml_generate_file_footer(xml_environment* env)
{
	if (env->res->base.subtype == RESOURCE_SYMBOLS)
	{
	    xml_print_element_end_tag(env, "CommonSymbols");
	}
	else
	{
	    xml_print_element_end_tag(env, env->res->conf->xml_name);
	}
    xml_print_element_end_tag(env, "AutogenXml");
}

LOCAL void xml_generate_file(xml_environment* env)
{
    env->fxml = fopen(env->filename, "wt");
    if (!env->fxml)
    {
        printf("\nError: Unable to open file %s for writing. Aborting...\n", env->filename);
        exit(1);
    }

    /* File header */
    xml_generate_file_header(env);

    /* Version history */
    xml_generate_element_version_history(env);

    /* Shared files */
    xml_generate_element_shared_files(env);

    /* Commmon objects */
    xml_generate_element_constants(env);
    xml_generate_element_tables(env);
    xml_generate_element_structures(env);
    xml_generate_element_subblocks(env);

    if (env->res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES ||
        env->res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT)
    {
        xml_generate_element_subblock_templates(env);
    }

    /* Traces / Messages */
    if ((env->res->base.subtype == RESOURCE_TRC_CDSP5) ||
        (env->res->base.subtype == RESOURCE_TRC_ADSP5) ||
        (env->res->base.subtype == RESOURCE_TRC_MCU) ||
        (env->res->base.subtype == RESOURCE_TRC_SYMBIAN) ||
        (env->res->base.subtype == RESOURCE_TRC_INVARIANT) ||
        (env->res->base.subtype == RESOURCE_TRC_OS) ||
        (env->res->base.subtype == RESOURCE_TRC_HAL) ||
        (env->res->base.subtype == RESOURCE_TRC_MASTER) ||
        (env->res->base.subtype == RESOURCE_TRC_VENDOR) ||
        (env->res->base.subtype == RESOURCE_TRC_HSP))

    {
        xml_generate_element_traces(env);
    }
    else
    {
        xml_generate_element_messages(env);
    }

    /* File footer */
    xml_generate_file_footer(env);

    fclose(env->fxml);
}

/* ================================================================================================ */
/* Common elements */
/* ================================================================================================ */

LOCAL void xml_generate_element_count(xml_environment* env, autogen_item* item)
{
    if (item->agg_type != AGG_TYPE_DYNAMIC_OPTIONAL)
    {
        xml_print_element_start_tag(env, "Count");

        switch (item->agg_type)
        {
        case AGG_TYPE_FIXED_MULTIPLE:
            xml_print_attr_string(env, "Type", "Fixed");

            if (check_c_name(NULL, 0, NULL, item->agg_n_str, 0))
            {
                xml_print_attr_string(env, "Value", item->agg_n_str);
            }
            else
            {
                xml_print_attr_int(env, "Value", item->agg_n);
            }
            break;

        case AGG_TYPE_FIXED_SINGLE:
            xml_print_attr_string(env, "Type", "Fixed");
            if (item->base.subtype == AUTOGEN_ITEM_STRING)
            {
                const autogen_item_string* item_str = (const autogen_item_string*)item;

                if (check_c_name(NULL, 0, NULL, item_str->length_str, 0))
                {
                    xml_print_attr_string(env, "Value", item_str->length_str);
                }
                else
                {
                    xml_print_attr_int(env, "Value", item_str->length);
                }
            }
            else
            {
                xml_print_attr_string(env, "Value", item->agg_n_str);
            }
            break;

        case AGG_TYPE_DYNAMIC_REF:
            {
                int has_value = TRUE;
                autogen_ref* ref = reference_find(item);

                switch (ref->algorithm)
                {
                case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MINUS_N:
                    xml_print_attr_string(env, "Type", "ValueMinusTagValue");
                    break;

                case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N:
                    xml_print_attr_string(env, "Type", "ValueMultipliedWithTagValue");
                    break;

                case PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH:
                    if (ref->value != 0)
                    {
                        xml_print_attr_string(env, "Type", "TagValuePlusValue");
                    }
                    else
                    {
                        xml_print_attr_string(env, "Type", "TagValue");
                        has_value = FALSE;
                    }
                    break;

                case PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH:
                    xml_print_attr_string(env, "Type", "TagValueDividedWithValue");
                    break;

                case PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH_ROUNDUP:
                    xml_print_attr_string(env, "Type", "TagValueDividedWithValueRoundedUp");
                    break;

                default:
                    xml_print_attr_string(env, "Type", "TagValue");
                    has_value = FALSE;
                    break;
                }

                xml_print_attr_string(env, "TagName", ref->original_name);
                if (has_value)
                {
                    xml_print_attr_int(env, "Value", ref->value);
                }
            }
            break;

        case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
            xml_print_attr_string(env, "Type", "AsManyAsPossible");
            break;

        case AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH:
            xml_print_attr_string(env, "Type", "Unknown");
            break;

        case AGG_TYPE_DYNAMIC_ZEROTERMINATED:
            xml_print_attr_string(env, "Type", "ZeroTerminated");
            break;

        case AGG_TYPE_DYNAMIC_OPTIONAL:
            /* Do nothing. Element name is set to optional */
            break;
        }

        xml_print_element_end_tag_empty(env);
    }
}

LOCAL void xml_generate_element_description(xml_environment* env, const autogen_obj* obj)
{
    int has_description = FALSE;
    const char* section_el_name = NULL;

    const autogen_cmt* cmt_it = obj->cmt_list;
    while (cmt_it)
    {
        /* Skip non-interesting comment types */
        if (cmt_it->id == COMMENT_PROPERTY_HTML_ONLY ||
            cmt_it->id == COMMENT_PROPERTY_ISIHDR_ONLY ||
            cmt_it->id == COMMENT_ISIHDR_AFTER_DEF ||
            cmt_it->id == COMMENT_ISIHDR_BEFORE_DEF ||
            cmt_it->id == COMMENT_ISIHDR_AFTER_DEF_16 ||
            cmt_it->id == COMMENT_ISIHDR_BEFORE_DEF_16)
        {
            cmt_it = cmt_it->next;
            continue;
        }
        else if (cmt_it->id == COMMENT_NEWLINE && !has_description)
        {
            cmt_it = cmt_it->next;
            continue;
        }

        /* Add description element */
        if (!has_description)
        {
            xml_print_element_start_tag(env, "Description");
            xml_print_element_start_tag_end(env, TRUE);

            has_description = TRUE;
        }

        if (cmt_it->id == COMMENT_TEXT)
        {
            if (!section_el_name)
            {
                section_el_name = xml_print_element_start_tag(env, "Para");
                xml_print_element_start_tag_end(env, FALSE);
            }

            xml_print_text(env, cmt_it->comment);            
        }
        else if (cmt_it->id == COMMENT_PARAGRAPH)
        {
            if (section_el_name)
            {
                xml_print_element_end_tag(env, section_el_name);
                section_el_name = NULL;
            }

            section_el_name = xml_print_element_start_tag(env, "Para");
            xml_print_element_start_tag_end(env, FALSE);

            xml_print_text(env, cmt_it->comment);
        }
        else if (cmt_it->id == COMMENT_BULLET)
        {
            if (section_el_name)
            {
                xml_print_element_end_tag(env, section_el_name);
                section_el_name = NULL;
            }

            section_el_name = xml_print_element_start_tag(env, "Bullet");
            xml_print_element_start_tag_end(env, FALSE);

            xml_print_text(env, cmt_it->comment);
        }
        else if (cmt_it->id == COMMENT_LINK_TYPE)
        {
            if (!section_el_name)
            {
                section_el_name = xml_print_element_start_tag(env, "Para");
                xml_print_element_start_tag_end(env, FALSE);
            }

            xml_print_text(env, cmt_it->linkname);
            if (cmt_it->linksubname && cmt_it->linksubname[0])
            {
                xml_print_text(env, "/");
                xml_print_text(env, cmt_it->linksubname);
            }
        }
        else if (cmt_it->id == COMMENT_NEWLINE)
        {
            if (section_el_name)
            {
                xml_print_element_end_tag(env, section_el_name);
                section_el_name = NULL;
            }
            xml_print_element_simple(env, "Break");
        }

        cmt_it = cmt_it->next;
    }

    /* Add description element (end) */
    if (has_description)
    {
        if (section_el_name)
        {
            xml_print_element_end_tag(env, section_el_name);
        }

        xml_print_element_end_tag(env, "Description");
    }
}

LOCAL void xml_generate_element_description_notes(xml_environment* env, autogen_res* res)
{
    autogen_obj* note;
    autogen_it note_it = INIT_ITERATOR;

    note_it.typemask = AUTOGEN_OBJ_NOTE;

    note = autogen_obj_find_in_list(&note_it, &res->note_list);
    if (note)
    {
        const char* el_name = xml_print_element_start_tag(env, "DescriptionNotes");
        xml_print_element_start_tag_end(env, TRUE);

        while (note)
        {
            const char* note_el_name = xml_print_element_start_tag(env, "Note");
            xml_print_attr_string(env, "Name", note->name);
            xml_print_element_start_tag_end(env, TRUE);

            xml_generate_element_description(env, note);

            xml_print_element_end_tag(env, note_el_name);

            note = autogen_obj_find_next_in_list(&note_it);
        }

        xml_print_element_end_tag(env, el_name);
    }
}

LOCAL void xml_generate_element_from_property(xml_environment* env, const autogen_item_value* item, const char* el_name, autogen_property_id prop_id, int multiple_values)
{
    const autogen_prop* prop_it = prop_find_first(&item->base.base, prop_id);
    const char* end_el_name = NULL;

    if (prop_it)
    {
        end_el_name = xml_print_element_start_tag(env, el_name);
        xml_print_element_start_tag_end(env, multiple_values);
    }

    while (prop_it)
    {
        if (multiple_values)
        {
            xml_print_element_start_tag(env, "Value");
            xml_print_element_start_tag_end(env, FALSE);
        }

        /* Try generating constant */
        if (check_c_name(NULL, 0, NULL, prop_it->str, 0))
        {
            xml_print_text(env, prop_it->str);
        }
        else if (item->pres.type & (AUTOGEN_PRESENTATION_DEC | AUTOGEN_PRESENTATION_QN))
        {
            char value[22];
#if (PMD_FILE_FORMAT >= 600)
            if (prop_has((autogen_obj*)env->res, PROPERTY_ALIGNMENT_64_BITS))
            {
                if (item->base.length < 0)
                    sprintf(value, "%lld", (signed long long)prop_it->value);
                else
                    sprintf(value, "%llu", (signed long long)prop_it->value);
            }
            else
#endif
            if (item->base.length < 0)
                sprintf(value, "%d", (int)prop_it->value);
            else
                sprintf(value, "%u", (int)prop_it->value);

            xml_print_text(env, value);
        }
        else
        {
            char value[22];
#if (PMD_FILE_FORMAT >= 600)
            if (prop_has((autogen_obj*)env->res, PROPERTY_ALIGNMENT_64_BITS))
            {
                sprintf(value, "%llu", (unsigned long long)prop_it->value);
            }
            else
#endif
                sprintf(value, "%u", prop_it->value);

            xml_print_text(env, value);
        }

        if (multiple_values)
        {
            xml_print_element_end_tag(env, "Value");
        }

        prop_it = prop_find_next(prop_it);
    }

    if (end_el_name)
    {
        xml_print_element_end_tag(env, end_el_name);
    }
}

LOCAL void xml_generate_element_presentation(xml_environment* env, const autogen_item_value* item)
{
    xml_print_element_start_tag(env, "Presentation");

    if (item->pres.type & AUTOGEN_PRESENTATION_BIN)
    {
        xml_print_attr_string(env, "Type", "Binary");
    }
    else if (item->pres.type & AUTOGEN_PRESENTATION_HEX)
    {
        xml_print_attr_string(env, "Type", "HexaDecimal");
    }
    else if (item->pres.type & AUTOGEN_PRESENTATION_CHAR) /* Covers ASCII and Unicode */
    {
        xml_print_attr_string(env, "Type", "Character");
    }
    else if (item->pres.type & AUTOGEN_PRESENTATION_DEC)
    {
        xml_print_attr_string(env, "Type", "Decimal");

        if (item->pres.type & AUTOGEN_PRESENTATION_SCALAR)
        {
            xml_print_attr_float_g(env, "Scale", item->pres.scale);
        }
        if (item->pres.type & AUTOGEN_PRESENTATION_OFFSET)
        {
            xml_print_attr_float_f(env, "Offset", item->pres.offset);
        }
        if (item->pres.type & AUTOGEN_PRESENTATION_UNIT)
        {
            xml_print_attr_string(env, "Unit", item->pres.unit);
        }
    }
    else if (item->pres.type & AUTOGEN_PRESENTATION_FTDID)
    {
        xml_print_attr_string(env, "Type", "FtdId");
    }
    else if (item->pres.type & AUTOGEN_PRESENTATION_SYMBOL_ANY)
    {
        const autogen_symbol_conf* sym_conf = util_get_sym_conf_by_type(item->pres.subtype);
        if (sym_conf && sym_conf->xml_type_name && sym_conf->xml_const_name)
        {
            xml_print_attr_string(env, "Type", sym_conf->xml_type_name);
            xml_print_attr_string(env, "ConstantType", sym_conf->xml_const_name);
        }
        else
        {
            xml_print_attr_string(env, "Type", "HexaDecimal");
        }
    }
    else if (item->pres.type & AUTOGEN_PRESENTATION_TIMESTAMP)
    {
        xml_print_attr_string(env, "Type", "Timestamp");

        switch (item->base.item_sub_type)
        {
        case PMD_TIMESTAMP_TYPE_GSM_FRAMES:
            xml_print_attr_string(env, "Timestamp", "GsmFrame");
            break;
        case PMD_TIMESTAMP_TYPE_STI_XTI:
            xml_print_attr_string(env, "Timestamp", "StiXti");
            break;
        default:
            xml_print_attr_string(env, "Timestamp", "Unknown");
            break;
        }
    }
    else if (item->pres.type & AUTOGEN_PRESENTATION_CONST)
    {
        xml_print_attr_string(env, "Type", "Constant");
        xml_print_attr_string(env, "TableName", item->pres.tblname);

        if (env->res != item->pres.tblres)
        {
            xml_print_attr_string(env, "ResourceName", item->pres.tblresname);
        }
    }
    else if (item->pres.type & AUTOGEN_PRESENTATION_QN)
    {
        xml_print_attr_string(env, "Type", "Decimal", item->pres.subtype);
		xml_print_attr_int(env, "Q", (int)item->pres.subtype);

        if (item->pres.type & AUTOGEN_PRESENTATION_SCALAR)
        {
            xml_print_attr_float_g(env, "Scale", item->pres.scale);
        }
        if (item->pres.type & AUTOGEN_PRESENTATION_OFFSET)
        {
            xml_print_attr_float_f(env, "Offset", item->pres.offset);
        }
        if (item->pres.type & AUTOGEN_PRESENTATION_UNIT)
        {
            xml_print_attr_string(env, "Unit", item->pres.unit);
        }
    }
    else
    {
        xml_print_attr_string(env, "Type", "HexaDecimal");
    }

    xml_print_element_end_tag_empty(env);
}

/* ================================================================================================ */
/* Feature flags */
/* ================================================================================================ */
LOCAL void xml_generate_element_featureflag(xml_environment* env, const autogen_feature *feature_flag)
{
    /* Check if a feature flag is defined on object */
    if (feature_flag != NULL)
    {
        const autogen_feature *ft_flag = feature_flag;

        /* Print start tag */
        xml_print_element_start_tag(env, "FeatureFlag");

        /* Check if feature flag is else part of if-then-else */
        if (ft_flag->flag_logic == FT_ELSE)
        {
            /* Negate the logical expression */
            xml_print_attr_string(env, "Negate", "True");

            /* Find head of feature flag as this is what should be printed */
            ft_flag = ft_flag->head;
        }

        /* Print operator attribute */
        if (ft_flag->flag_logic == FT_FLAG1_AND_FLAG2 || ft_flag->flag_logic == FT_FLAG1_OR_FLAG2)
        {
            xml_print_attr_string(env, "Operator", (ft_flag->flag_logic == FT_FLAG1_AND_FLAG2 ? "And" : "Or"));
        }

        /* Print end of start tag */
        xml_print_element_start_tag_end(env, TRUE);

        /* Print 1. operand */
        xml_print_attr_featureflag_operand(env, ft_flag->flag_logic, ft_flag->feature1->flag, ft_flag->feature1->value);

        /* Print 2. operand */
        if (ft_flag->flag_logic == FT_FLAG1_AND_FLAG2 || ft_flag->flag_logic == FT_FLAG1_OR_FLAG2)
        {
            xml_print_attr_featureflag_operand(env, ft_flag->flag_logic, ft_flag->feature2->flag, ft_flag->feature2->value);
        }

        /* Print feature flag end */
        xml_print_element_end_tag(env, "FeatureFlag");
    }
}

/* ================================================================================================ */
/* Filler replacement version */
/* ================================================================================================ */
LOCAL void xml_generate_element_filler_replacement(xml_environment* env, const autogen_obj* obj)
{
    autogen_property_id id = PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION;
    if (prop_has_valid_string(obj, id))
    {
        xml_print_element_start_tag(env, "FillerReplacement");
        xml_print_attr_string(env, "Version", prop_get_string(obj, id));
        xml_print_element_end_tag_empty(env);
    }
}

/* ================================================================================================ */
/* Suppress autogen warnings */
/* ================================================================================================ */
LOCAL void xml_generate_element_suppress_autogen_warnings(xml_environment* env, const autogen_obj* obj)
{
    if (prop_has(obj, PROPERTY_SUPPRESS_AUTOGEN_WARNINGS))
    {
        xml_print_element_simple(env, "SuppressAutogenWarnings");
    }
}

/* ================================================================================================ */
/* Project info */
/* ================================================================================================ */

LOCAL void xml_generate_element_project_info(xml_environment* env, const autogen_obj* obj)
{
    const char* element_names[7] = { "NokiaEntity", "Confidentiality", "SiteName", "ProjectName", "ProjectOwner",
        "CopyrightYear", "IsiVersionAutoGenerate" };
    autogen_property_id element_ids[7] = { PROPERTY_PROJECT_NOKIA_ENTITY, PROPERTY_PROJECT_CONFIDENTIALITY, 
        PROPERTY_PROJECT_SITE_NAME, PROPERTY_PROJECT_NAME, PROPERTY_PROJECT_OWNER_NAME, PROPERTY_COPYRIGHT_YEAR,
        PROPERTY_ISI_VERSION_AUTO_GENERATE };

    const char* element_names_simple[8] = { "AlignmentCheckBreak", "AlignmentCheckDisable", "InheritBaseResourceDefinitions", 
        "IsiVersioningNotSupported", "Nokia3rdPartyVendorOutput", "ProtocolHasNoMessages", "SubmessageNamesAreUnique", "Alignment64Bits" };
    autogen_property_id element_ids_simple[8] = { PROPERTY_ALIGNMENT_CHECK_BREAK, PROPERTY_ALIGNMENT_CHECK_DISABLE, 
        PROPERTY_INHERIT_BASE_RESOURCE_DEFINITIONS, PROPERTY_ISI_VERSIONING_NOT_SUPPORTED, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT,
        PROPERTY_PROTOCOL_HAS_NO_MESSAGES, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE, PROPERTY_ALIGNMENT_64_BITS };

    int n;

    const char* el_name = xml_print_element_start_tag(env, "ProjectInfo");
    xml_print_element_start_tag_end(env, TRUE);

    for (n = 0; n < 7; n++)
    {
        if (prop_has_valid_string(obj, element_ids[n]))
        {
            xml_print_element_start_tag(env, element_names[n]);
            xml_print_element_start_tag_end(env, FALSE);

            xml_print_text(env, prop_get_string(obj, element_ids[n]));

            xml_print_element_end_tag(env, element_names[n]);
        }
    }
    for (n = 0; n < 8; n++)
    {
        if (prop_has(obj, element_ids_simple[n]))
        {
            xml_print_element_simple(env, element_names_simple[n]);
        }
    }

    xml_print_element_end_tag(env, el_name);
}

/* ================================================================================================ */
/* ISI Header info*/
/* ================================================================================================ */
LOCAL void xml_generate_element_isihdr_info(xml_environment* env, const autogen_obj* obj)
{
    const char* element_names[21] = { "AliasName", "ContinuusInstanceName", "ContinuusInstanceName16", 
                                      "ContinuusProjectDb", "ContinuusProjectPath", "ContinuusProjectPath16", "DefinitionName",
                                      "Filename", "Filename16", "MergedMaskPrefix", "PhonetHeaderLayout", "StructLengthName", 
                                      "StructLengthValue", "StructName", "StructPhonetLengthName", "Title", "Varname16", 
                                      "SplitDwordSigned", "SplitDwordUnsigned", "SplitWordSigned", "SplitWordUnsigned"};
    autogen_property_id element_ids[21] = { PROPERTY_ISIHDR_ALIAS_NAME, 
        PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME, PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,
        PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH, PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16, PROPERTY_ISIHDR_DEFINITION_NAME,
        PROPERTY_ISIHDR_FILENAME, PROPERTY_ISIHDR_FILENAME_16, PROPERTY_ISIHDR_MERGED_MASK_PREFIX, PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT, 
        PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE, PROPERTY_ISIHDR_STRUCT_NAME, PROPERTY_ISIHDR_STRUCT_PHONET_LENGTH_NAME, 
        PROPERTY_ISIHDR_TITLE, PROPERTY_ISIHDR_VARNAME_16, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED, 
        PROPERTY_ISIHDR_SPLIT_WORD_SIGNED,PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED};

    const char* element_names_simple[20] = { "DontGenerate", "DontGenerate16", "DontGenerate8", "DontGenerateId", "GenerateAllStructureElements",
        "GenerateAsBitfield", "GenerateAsBool", "GenerateAsEnum16", "GenerateAsEnum8", "GenerateBitfields", "GenerateBools", "GenerateMergedMasks", 
        "GenerateMergedMasks16", "IncludePhonetHeader", "IncludePhonetHeader16", "PhonetHeaderDontGenerate", "SplitAsArray", 
        "SplitDwords16", "StructLengthSizeof", "StructLengthSum"};
    autogen_property_id element_ids_simple[20] = { PROPERTY_ISIHDR_DONT_GENERATE, PROPERTY_ISIHDR_DONT_GENERATE_16,
        PROPERTY_ISIHDR_DONT_GENERATE_8, PROPERTY_ISIHDR_DONT_GENERATE_ID, PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS,
        PROPERTY_ISIHDR_GENERATE_AS_BITFIELD, PROPERTY_ISIHDR_GENERATE_AS_BOOL, PROPERTY_ISIHDR_GENERATE_AS_ENUM_16,
        PROPERTY_ISIHDR_GENERATE_AS_ENUM_8, PROPERTY_ISIHDR_GENERATE_BITFIELDS, PROPERTY_ISIHDR_GENERATE_BOOLS, PROPERTY_ISIHDR_GENERATE_MERGED_MASKS, 
        PROPERTY_ISIHDR_GENERATE_MERGED_MASKS_16, PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER, PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16, 
        PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE, PROPERTY_ISIHDR_SPLIT_AS_ARRAY, PROPERTY_ISIHDR_SPLIT_DWORDS_16, 
        PROPERTY_ISIHDR_STRUCT_LENGTH_SIZEOF, PROPERTY_ISIHDR_STRUCT_LENGTH_SUM};

    const char* comment_names[6] = { "IsiHeaderAfterDef", "IsiHeaderAfterDef16", "IsiHeaderBeforeDef", "IsiHeaderBeforeDef16", "IsiHeaderTop", "IsiHeaderTop16"};

    autogen_property_id comment_ids[6] = { COMMENT_ISIHDR_AFTER_DEF, COMMENT_ISIHDR_AFTER_DEF_16, COMMENT_ISIHDR_BEFORE_DEF,
        COMMENT_ISIHDR_BEFORE_DEF_16, COMMENT_ISIHDR_TOP, COMMENT_ISIHDR_TOP_16 };

    const char* generation_names[10] = { "DontGenerate", "Anysize", "AnysizeByte", "AnysizeWord", "SingleElement", "SingleElementByte", "ReserveSpace", 
        "PointerVoid", "Pointer", "Union"};

    const autogen_cmt* cmt_it = obj->cmt_list;

    int n;
    int start_tag_printed = FALSE;
    const char* el_name = "IsihdrInfo";
    isihdr_marker_type marker = (unsigned int)prop_get_value_default(obj, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_NONE);

    /* Properties with text or value */
    for (n = 0; n < 21; n++)
    {
        if (prop_has_valid_string(obj, element_ids[n]))
        {
            if (!start_tag_printed)
            {
                xml_print_element_start_tag(env, el_name);
                xml_print_element_start_tag_end(env, TRUE);
                start_tag_printed = TRUE;
            }
            xml_print_element_start_tag(env, element_names[n]);
            xml_print_element_start_tag_end(env, FALSE);

            xml_print_text(env, prop_get_string(obj, element_ids[n]));

            xml_print_element_end_tag(env, element_names[n]);
        }
    }
    /* ISI header generation flag */
    if (marker != ISIHDR_MARKER_NONE)
    {
        if (!start_tag_printed)
        {
            xml_print_element_start_tag(env, el_name);
            xml_print_element_start_tag_end(env, TRUE);
            start_tag_printed = TRUE;
        }
        xml_print_element_start_tag(env, "GenerationType");
        xml_print_element_start_tag_end(env, FALSE);

        xml_print_text(env, generation_names[marker]);

        xml_print_element_end_tag(env, "GenerationType");
    }
    else if ((obj->type == AUTOGEN_OBJ_ITEM) && (obj->subtype == AUTOGEN_ITEM_POINTER))
    {
        if (!start_tag_printed)
        {
            xml_print_element_start_tag(env, el_name);
            xml_print_element_start_tag_end(env, TRUE);
            start_tag_printed = TRUE;
        }
        xml_print_element_start_tag(env, "PointerGenerationType");
        xml_print_element_start_tag_end(env, FALSE);

        if(obj->flag & AUTOGEN_POINTER_UINT8)
            xml_print_text(env, "uint8*");
        else if(obj->flag & AUTOGEN_POINTER_INT8)
            xml_print_text(env, "int8*");
        else if(obj->flag & AUTOGEN_POINTER_UINT16)
            xml_print_text(env, "uint16*");
        else if(obj->flag & AUTOGEN_POINTER_INT16)
            xml_print_text(env, "int16*");
        else if(obj->flag & AUTOGEN_POINTER_UINT32)
            xml_print_text(env, "uint32*");
        else if(obj->flag & AUTOGEN_POINTER_INT32)
            xml_print_text(env, "int32*");
#if (PMD_FILE_FORMAT >= 600)
        else if(obj->flag & AUTOGEN_POINTER_UINT64)
            xml_print_text(env, "uint64*");
        else if(obj->flag & AUTOGEN_POINTER_INT64)
            xml_print_text(env, "int64*");
#endif
        else
            xml_print_text(env, "void*");

        xml_print_element_end_tag(env, "PointerGenerationType");
    }
    /* Simple properties */
    for (n = 0; n < 20; n++)
    {
        if (prop_has(obj, element_ids_simple[n]))
        {
            if (!start_tag_printed)
            {
                xml_print_element_start_tag(env, el_name);
                xml_print_element_start_tag_end(env, TRUE);
                start_tag_printed = TRUE;
            }
            xml_print_element_simple(env, element_names_simple[n]);
        }
    }
    /* Comments related to ISI Header */
    while (cmt_it)
    {
        /* Is the comment to be included in ISI Header info? */
        for (n = 0; n < 6; n++)
        {
            if (cmt_it->id == comment_ids[n])
                break;
        }
        if (n >= 6)
        {
            cmt_it = cmt_it->next;
            continue;
        }
        if (!start_tag_printed)
        {
            xml_print_element_start_tag(env, el_name);
            xml_print_element_start_tag_end(env, TRUE);
            start_tag_printed = TRUE;
        }
        xml_print_element_start_tag(env, comment_names[n]);
        xml_print_element_start_tag_end(env, FALSE);

        xml_print_text(env, cmt_it->comment);            

        xml_print_element_end_tag(env, comment_names[n]);

        cmt_it = cmt_it->next;
    }
    if (start_tag_printed)
        xml_print_element_end_tag(env, el_name);
}

/* ================================================================================================ */
/* HTML info */
/* ================================================================================================ */
LOCAL void xml_generate_element_html_info(xml_environment* env, const autogen_obj* obj)
{
    const char* element_names[6] = { "ContinuusProjectDb", "ContinuusProjectName", "DirectoryPath", "DocumentNumber", 
                                      "Filename", "Title"};
    autogen_property_id element_ids[6] = { PROPERTY_HTML_CONTINUUS_PROJECT_DB, PROPERTY_HTML_CONTINUUS_PROJECT_NAME, 
        PROPERTY_HTML_DIRECTORY_PATH, PROPERTY_HTML_DOCUMENT_NUMBER, PROPERTY_HTML_FILENAME, PROPERTY_HTML_TITLE};

    const char* element_names_simple[4] = { "DontGenerate", "IncludeIntroduction", "IncludePhonetHeader", "IncludeVarnameColumn"};
    autogen_property_id element_ids_simple[4] = { PROPERTY_HTML_DONT_GENERATE,
        PROPERTY_HTML_INCLUDE_INTRODUCTION, PROPERTY_HTML_INCLUDE_PHONET_HEADER, PROPERTY_HTML_INCLUDE_VARNAME_COLUMN};
    int n;
    int start_tag_printed = FALSE;
    const char* el_name = "HtmlInfo";

    for (n = 0; n < 6; n++)
    {
        if (prop_has_valid_string(obj, element_ids[n]))
        {
            if (!start_tag_printed)
            {
                xml_print_element_start_tag(env, "HtmlInfo");
                xml_print_element_start_tag_end(env, TRUE);
                start_tag_printed = TRUE;
            }
            xml_print_element_start_tag(env, element_names[n]);
            xml_print_element_start_tag_end(env, FALSE);

            xml_print_text(env, prop_get_string(obj, element_ids[n]));

            xml_print_element_end_tag(env, element_names[n]);
        }
    }
    for (n = 0; n < 4; n++)
    {
        if (prop_has(obj, element_ids_simple[n]))
        {
            if (!start_tag_printed)
            {
                xml_print_element_start_tag(env, "HtmlInfo");
                xml_print_element_start_tag_end(env, TRUE);
                start_tag_printed = TRUE;
            }
            xml_print_element_simple(env, element_names_simple[n]);
        }
    }

    if (start_tag_printed)
        xml_print_element_end_tag(env, el_name);
}

/* ================================================================================================ */
/* PMD info */
/* ================================================================================================ */
LOCAL void xml_generate_element_pmd_info(xml_environment* env, const autogen_obj* obj)
{
    /* Still to be implemented:
        PROPERTY_PMD_TRACE_SOURCE_FLAGS		I PROPERTY_VALUE_INDEX
        PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER	I PROPERTY_STRING_INDEX
        PROPERTY_PMD_TRACE_SOURCE_NAME		I PROPERTY_STRING_INDEX
    */
    const char* element_names[6] = { "TraceActivationText", "TraceIdentifier", "TraceLogicalGroup", 
                                     "TraceSource", "PmdPhonetDeviceId", "PmdPhonetObjectId" };
    autogen_property_id element_ids[6] = { PROPERTY_PMD_TRACE_ACTIVATION_TEXT, PROPERTY_PMD_TRACE_IDENTIFIER, 
        PROPERTY_PMD_TRACE_LOGICAL_GROUP, PROPERTY_PMD_TRACE_SOURCE, PROPERTY_PMD_PHONET_DEVICE_ID, PROPERTY_PMD_PHONET_OBJECT_ID };

    const char* element_names_simple[10] = { "DontGenerate", "EnvironmentVariable", "PmdIsNotParameter", 
        "PmdParameter", "ParameterInSummary", "UseConstTblComment", "TraceActivationDefaultStateOn", 
        "TraceActivationExclude", "HardwareMasterTrace", "ProtocolIsLittleEndian"};
    autogen_property_id element_ids_simple[10] = { PROPERTY_PMD_DONT_GENERATE,
        PROPERTY_PMD_ENVIRONMENT_VARIABLE, PROPERTY_PMD_IS_NOT_PARAMETER,
        PROPERTY_PMD_PARAMETER, PROPERTY_PMD_PARAMETER_IN_SUMMARY, PROPERTY_PMD_USE_CONST_TBL_ENTRY_COMMENT,
        PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON, PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE, 
        PROPERTY_PMD_RESOURCE_TRC_IS_HW_MASTER, PROPERTY_PMD_PROTOCOL_IS_LE};
    int n;
    int start_tag_printed = FALSE;
    const char* el_name = "PmdInfo";

    for (n = 0; n < 6; n++)
    {
        if (prop_has_valid_string(obj, element_ids[n]))
        {
            if (!start_tag_printed)
            {
                xml_print_element_start_tag(env, el_name);
                xml_print_element_start_tag_end(env, TRUE);
                start_tag_printed = TRUE;
            }
            xml_print_element_start_tag(env, element_names[n]);
            xml_print_element_start_tag_end(env, FALSE);

            xml_print_text(env, prop_get_string(obj, element_ids[n]));

            xml_print_element_end_tag(env, element_names[n]);
        }
    }
    for (n = 0; n < 10; n++)
    {
        if (prop_has(obj, element_ids_simple[n]))
        {           
            if (!start_tag_printed)
            {
                xml_print_element_start_tag(env, el_name);
                xml_print_element_start_tag_end(env, TRUE);
                start_tag_printed = TRUE;
            }
            xml_print_element_simple(env, element_names_simple[n]);
        }
    }
    /* Special handling: Identical IDs, but applies to different resources */
    if (prop_has(obj, PROPERTY_PMD_MESSAGE_IN_SUMMARY))
    {
        if (obj->base_obj->parent->type & RESOURCE_ISI_ANY)
        {
            if (!start_tag_printed)
            {
                xml_print_element_start_tag(env, el_name);
                xml_print_element_start_tag_end(env, TRUE);
                start_tag_printed = TRUE;
            }
            xml_print_element_simple(env, "MessageInSummary");
        }
    }
    if (prop_has(obj, PROPERTY_PMD_TRACE_IN_SUMMARY))
    {
        if (obj->base_obj->parent->type & RESOURCE_TRC_ANY)
        {        
            if (!start_tag_printed)
            {
                xml_print_element_start_tag(env, el_name);
                xml_print_element_start_tag_end(env, TRUE);
                start_tag_printed = TRUE;
            }
            xml_print_element_simple(env, "TraceInSummary");
        }
    }


    if (start_tag_printed)
        xml_print_element_end_tag(env, el_name);
}

/* ================================================================================================ */
/* Message pairs */
/* ================================================================================================ */
LOCAL void xml_generate_element_related_messages(xml_environment* env, autogen_obj* msg)
{
    autogen_obj* related_msg;
    autogen_it   msg_it = INIT_ITERATOR;
    msg_it.typemask     = AUTOGEN_OBJ_REL;
    msg_it.subtypemask  = AUTOGEN_OBJ_MSG;

    related_msg = autogen_obj_find_in_list(&msg_it, &msg->related_obj);
    if (related_msg)
    {
        xml_print_element_start_tag(env, "RelatedMessages");
        xml_print_element_start_tag_end(env, TRUE);
        while (related_msg)
        {
            xml_print_element_start_tag(env, "RelatedMessage");
            xml_print_attr_string(env, "Name", related_msg->name);
            xml_print_attr_version_span(env, related_msg);
            xml_print_element_end_tag_empty(env);

            related_msg = autogen_obj_find_next_in_list(&msg_it);
        }
        xml_print_element_end_tag(env, "RelatedMessages");
    }
}

/* ================================================================================================ */
/* Version history */
/* ================================================================================================ */

LOCAL void xml_generate_element_version_history(xml_environment* env)
{
    autogen_obj* ver;
    autogen_it ver_it = INIT_ITERATOR;

    ver_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_VERSION;

    ver = autogen_obj_find_in_list(&ver_it, &env->res->ver_list);
    if (ver)
    {
        xml_print_element_start_tag(env, "VersionHistory");
        xml_print_element_start_tag_end(env, TRUE);

        while (ver)
        {
            const char* change_status = prop_get_string_default(ver, PROPERTY_CHANGE_STATUS, "-");

            xml_print_element_start_tag(env, "VersionInfo");
            xml_print_attr_version(env, "Version", &ver->ver, AUTOGEN_OBJ_VERSION_FROM);

            /* Change status */
            if (!strcmp(change_status, "DRAFT") || !strcmp(change_status, "Draft"))
            {
                xml_print_attr_string(env, "Status", "Draft");
            }
            else if (!strcmp(change_status, "NON-DRAFT"))
            {
                xml_print_attr_string(env, "Status", "NonDraft");
            }
            else if (!strcmp(change_status, "APPROVED") || !strcmp(change_status, "Approved"))
            {
                xml_print_attr_string(env, "Status", "Approved");
            }
            else if (!strcmp(change_status, "PROPOSAL") || !strcmp(change_status, "Proposal"))
            {
                xml_print_attr_string(env, "Status", "Proposal");
            }
            else
            {
                xml_print_attr_string(env, "Status", "Unknown");
            }

            xml_print_attr_string(env, "Date", prop_get_string_default(ver, PROPERTY_CHANGE_DATE, "-"));
            xml_print_attr_string(env, "Editor", prop_get_string_default(ver, PROPERTY_CHANGE_PERSON, "-"));
            xml_print_element_start_tag_end(env, TRUE);

            /* ISI header info */
            xml_generate_element_isihdr_info(env, ver);
            /* HTML info */
            xml_generate_element_html_info(env, ver);

            /* Change reason */
            xml_print_element_start_tag(env, "Reason");
            xml_print_element_start_tag_end(env, FALSE);
            xml_print_text(env, prop_get_string_default(ver, PROPERTY_CHANGE_REASON, "-"));
            xml_print_element_end_tag(env, "Reason");

            /* Change references */
            xml_print_element_start_tag(env, "Reference");
            xml_print_element_start_tag_end(env, FALSE);
            if (prop_has_valid_string(ver, PROPERTY_CHANGE_REFERENCE))
            {
                const autogen_prop* prop_it = prop_find_first(ver, PROPERTY_CHANGE_REFERENCE);
                const autogen_prop* prop_first = prop_it;
                while (prop_it)
                {
                    if (prop_it->str && prop_it->str[0])
                    {
                        if (prop_first != prop_it)
                        {
                            xml_print_text(env, ", ");
                        }
                        xml_print_text(env, prop_it->str);
                    }

                    prop_it = prop_it->next;
                }
            }
            else
            {
                xml_print_text(env, "-");
            }
            xml_print_element_end_tag(env, "Reference");

            /* Version no longer / not yet supported */
            if (prop_has(ver, PROPERTY_VERSION_NO_LONGER_SUPPORTED))
            {
                xml_print_element_simple(env, "NoLongerSupported");
            }
            if (prop_has(ver, PROPERTY_VERSION_NOT_YET_SUPPORTED))
            {
                xml_print_element_simple(env, "NotYetSupported");
            }
            xml_generate_element_suppress_autogen_warnings(env, ver);

            /* Change description */
            xml_generate_element_description(env, ver);

            xml_print_element_end_tag(env, "VersionInfo");

            ver = autogen_obj_find_next_in_list(&ver_it);
        }

        xml_print_element_end_tag(env, "VersionHistory");
    }
}

/* ================================================================================================ */
/* Shared files */
/* ================================================================================================ */

LOCAL void xml_generate_element_shared_files(xml_environment* env)
{
    autogen_obj* shr = autogen_obj_get_first_in_list(&env->res->shared_list);
    if (shr)
    {
        xml_print_element_start_tag(env, "SharedFiles");
        xml_print_element_start_tag_end(env, TRUE);

		while (shr)
        {
            xml_print_element_start_tag(env, "SharedFile");
            xml_print_attr_string(env, "Name", shr->name);
			xml_print_attr_version_span(env, shr);

            xml_print_element_end_tag_comment(env, "SharedFile", shr);

			shr = shr->next;
        }

        xml_print_element_end_tag(env, "SharedFiles");
    }
}

/* ================================================================================================ */
/* Constants */
/* ================================================================================================ */

LOCAL void xml_generate_element_constants(xml_environment* env)
{
    autogen_obj* constants;
    autogen_it const_it = INIT_ITERATOR;

    const_it.typemask = AUTOGEN_OBJ_CONST;
    const_it.flagnone = AUTOGEN_OBJ_IS_SHARED;

    constants = autogen_obj_find_in_list(&const_it, &env->res->const_list);
    if (constants)
    {
        xml_print_element_start_tag(env, "Constants");
        xml_print_element_start_tag_end(env, TRUE);

        while (constants)
        {
            xml_print_element_start_tag(env, "Constant");
            xml_print_attr_string(env, "Name", constants->name);

            if (constants->flag & AUTOGEN_CONST_UNSIGNED_BYTE)
            {
                xml_print_attr_hex(env, "Id", constants->id, 2);
            }
            else if (constants->flag & AUTOGEN_CONST_UNSIGNED_WORD)
            {
                xml_print_attr_hex(env, "Id", constants->id, 4);
            }
            else if (constants->flag & AUTOGEN_CONST_UNSIGNED_DWORD)
            {
                xml_print_attr_hex(env, "Id", constants->id, 8);
            }
            else if (constants->flag & AUTOGEN_CONST_SIGNED)
            {
                xml_print_attr_int(env, "Id", constants->id);
            }
            else
            {
                xml_print_attr_hex(env, "Id", constants->id, 8);
            }

            xml_print_attr_version_span(env, constants);

            xml_print_element_end_tag_comment(env, "Constant", constants);

            constants = autogen_obj_find_next_in_list(&const_it);
        }

        xml_print_element_end_tag(env, "Constants");

        free (constants);
    }
}

/* ================================================================================================ */
/* Tables */
/* ================================================================================================ */

LOCAL void xml_generate_element_tables(xml_environment* env)
{
    autogen_tbl* tbl;
    autogen_it tbl_it = INIT_ITERATOR;

    tbl_it.typemask = AUTOGEN_OBJ_TBL;
    tbl_it.flagnone = AUTOGEN_OBJ_IS_SHARED;

    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &env->res->tbl_list);
    if (tbl)
    {
        xml_print_element_start_tag(env, "Tables");
        xml_print_element_start_tag_end(env, TRUE);

        while (tbl)
        {            
            switch (tbl->base.subtype)
            {
            case AUTOGEN_TBL_CONST:
				if (env->res->base.subtype == RESOURCE_SYMBOLS)
				{
					const autogen_symbol_conf* conf = util_get_sym_conf_by_tblname(tbl->base.name);
					if (conf && conf->xml_generate)
					{
		                xml_generate_element_constant_table(env, tbl, conf->xml_const_name);
					}
				}
				else
				{
	                xml_generate_element_constant_table(env, tbl, tbl->base.name);
				}
                break;

            case AUTOGEN_TBL_DERCONST:
                xml_generate_element_constant_table_subset(env, tbl);
                break;

            case AUTOGEN_TBL_BIT:
                xml_generate_element_bitmask_table(env, tbl);
                break;

            case AUTOGEN_TBL_DERBIT:
                xml_generate_element_bitmask_table_subset(env, tbl);
                break;

            case AUTOGEN_TBL_FTD:
                xml_generate_element_ftd_table(env, tbl);
                break;
            case AUTOGEN_TBL_PPC:
                xml_generate_element_ppc_table(env, tbl);
                break;
            }

            tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
        }

        xml_print_element_end_tag(env, "Tables");
    }
}

LOCAL void xml_generate_element_constant_table(xml_environment* env, autogen_tbl* tbl, const char* tbl_name)
{
    autogen_obj* entry;
    autogen_it entry_it = INIT_ITERATOR;

    entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
    if (entry)
    {
        xml_print_element_start_tag(env, "ConstantTable");
        xml_print_attr_string(env, "Name", tbl_name);
        xml_print_attr_bool(env, "SignedValues", tbl->length < 0);
        xml_print_attr_version_span(env, &tbl->base);
        xml_print_element_start_tag_end(env, TRUE);

        /* Generate feature flag */
        xml_generate_element_featureflag(env, tbl->base.feature_flags);

        /* Generate table description */
        xml_generate_element_description(env, &tbl->base);

        /* ISI Header info*/
        xml_generate_element_isihdr_info(env, &tbl->base);

        /* HTML info */
        xml_generate_element_html_info(env, &tbl->base);

        /* PMD info */
        xml_generate_element_pmd_info(env, &tbl->base);

        xml_generate_element_suppress_autogen_warnings(env, &tbl->base);
        while (entry)
        {
            xml_print_element_start_tag(env, "Constant");
            xml_print_attr_string(env, "Name", entry->name);

            if (tbl->length < 0) /* output in decimal */
            {
#if (PMD_FILE_FORMAT >= 600)
                xml_print_attr_int(env, "Id", (signed long long)entry->id);
#else
                xml_print_attr_int(env, "Id", (int)entry->id);
#endif
            }
            else
            {
                xml_print_attr_hex(env, "Id", entry->id, xml_calc_chars(tbl->length));
            }

            xml_print_attr_version_span(env, entry);
            xml_print_element_end_tag_comment(env, "Constant", entry);

            entry = autogen_obj_find_next_in_list(&entry_it);
        }            

        xml_print_element_end_tag(env, "ConstantTable");
    }
}

LOCAL void xml_generate_element_constant_table_subset(xml_environment* env, autogen_tbl* tbl)
{
    autogen_obj* entry = autogen_obj_get_first_in_list(&tbl->base.child_list);
    if (entry)
    {
        xml_print_element_start_tag(env, "ConstantTableSubset");
        xml_print_attr_string(env, "Name", tbl->base.name);
        xml_print_attr_string(env, "ParentConstantTable", tbl->base.base_obj->name);
        xml_print_attr_version_span(env, &tbl->base);
        xml_print_element_start_tag_end(env, TRUE);

        /* Generate feature flag */
        xml_generate_element_featureflag(env, tbl->base.feature_flags);

        /* Generate table description */
        xml_generate_element_description(env, &tbl->base);
        xml_generate_element_isihdr_info(env, &tbl->base);
        xml_generate_element_html_info(env, &tbl->base);
        xml_generate_element_pmd_info(env, &tbl->base);
        xml_generate_element_suppress_autogen_warnings(env, &tbl->base);

        while (entry)
        {
            xml_print_element_start_tag(env, "ConstantReference");
            xml_print_attr_string(env, "Name", entry->name);
            xml_print_attr_version_span(env, entry);
            xml_print_element_end_tag_comment(env, "ConstantReference", entry);

            entry = entry->next;
        }

        xml_print_element_end_tag(env, "ConstantTableSubset");
    }
}

LOCAL void xml_generate_element_bitmask_table(xml_environment* env, autogen_tbl* tbl)
{
    autogen_bittbl_entry* entry = (autogen_bittbl_entry*)autogen_obj_get_first_in_list(&tbl->base.child_list);
    if (entry)
    {
        xml_print_element_start_tag(env, "BitmaskTable");
        xml_print_attr_string(env, "Name", tbl->base.name);
        xml_print_attr_version_span(env, &tbl->base);
        xml_print_element_start_tag_end(env, TRUE);

        /* Generate feature flag */
        xml_generate_element_featureflag(env, tbl->base.feature_flags);

        /* Generate table description */
        xml_generate_element_description(env, &tbl->base);
        xml_generate_element_isihdr_info(env, &tbl->base);
        xml_generate_element_html_info(env, &tbl->base);
        xml_generate_element_pmd_info(env, &tbl->base);
        xml_generate_element_suppress_autogen_warnings(env, &tbl->base);
        while (entry)
        {
            xml_print_element_start_tag(env, "Bitmask");
            xml_print_attr_string(env, "Name", entry->base.name);
            xml_print_attr_string(env, "Pattern", entry->bit_pattern);

            xml_print_attr_hex(env, "Mask", entry->bit_mask, xml_calc_chars(tbl->length));
            xml_print_attr_hex(env, "Value", entry->base.id, xml_calc_chars(tbl->length));
            xml_print_attr_version_span(env, &entry->base);
            xml_print_element_end_tag_comment(env, "Bitmask", &entry->base);

            entry = (autogen_bittbl_entry*)entry->base.next;
        }                       

        xml_print_element_end_tag(env, "BitmaskTable");
    }
}

LOCAL void xml_generate_element_bitmask_table_subset(xml_environment* env, autogen_tbl* tbl)
{
    autogen_obj* entry = autogen_obj_get_first_in_list(&tbl->base.child_list);
    if (entry)
    {
        xml_print_element_start_tag(env, "BitmaskTableSubset");
        xml_print_attr_string(env, "Name", tbl->base.name);
        xml_print_attr_string(env, "ParentBitmaskTable", tbl->base.base_obj->name);
        xml_print_attr_version_span(env, &tbl->base);
        xml_print_element_start_tag_end(env, TRUE);

        /* Generate feature flag */
        xml_generate_element_featureflag(env, tbl->base.feature_flags);

        /* Generate table description */
        xml_generate_element_description(env, &tbl->base);
        xml_generate_element_isihdr_info(env, &tbl->base);
        xml_generate_element_html_info(env, &tbl->base);
        xml_generate_element_pmd_info(env, &tbl->base);
        xml_generate_element_suppress_autogen_warnings(env, &tbl->base);

        while (entry)
        {
            xml_print_element_start_tag(env, "BitmaskReference");
            xml_print_attr_string(env, "Name", entry->name);
            xml_print_attr_version_span(env, entry);
            xml_print_element_end_tag_comment(env, "BitmaskReference", entry);

            entry = entry->next;
        }

        xml_print_element_end_tag(env, "BitmaskTableSubset");
    }
}

LOCAL void xml_generate_element_ftd_table(xml_environment* env, autogen_tbl* tbl)
{
    autogen_data* entry = (autogen_data*)autogen_obj_get_first_in_list(&tbl->base.child_list);
    if (entry)
    {
        xml_print_element_start_tag(env, "FtdTable");
        xml_print_attr_version_span(env, &tbl->base);
        xml_print_element_start_tag_end(env, TRUE);

        /* Generate feature flag */
        xml_generate_element_featureflag(env, tbl->base.feature_flags);

        /* Generate table description  */
        xml_generate_element_description(env, &tbl->base);
        xml_generate_element_isihdr_info(env, &tbl->base);
        xml_generate_element_html_info(env, &tbl->base);
        xml_generate_element_pmd_info(env, &tbl->base);
        xml_generate_element_suppress_autogen_warnings(env, &tbl->base);

        while (entry)
        {
            const char* el_name = NULL;

            if (entry->base.flag & AUTOGEN_DATA_FTD_IS_INPUT_DATA)
            {
                el_name = xml_print_element_start_tag(env, "FtdInputValue");
            }
            else if (entry->base.flag & AUTOGEN_DATA_TABLE)
            {
                el_name = xml_print_element_start_tag(env, "FtdTableValue");
            }
            else if (entry->base.flag & AUTOGEN_DATA_STRING)
            {
                el_name = xml_print_element_start_tag(env, "FtdString");
            }
            else
            {
                el_name = xml_print_element_start_tag(env, "FtdValue");
            }

            /* Print Name and ID and close tag */
            xml_print_attr_string(env, "Name", entry->base.name);
            xml_print_attr_hex(env, "Id", entry->base.id, 4);

            if (entry->base.flag & (AUTOGEN_DATA_TABLE | AUTOGEN_DATA_VALUE))
            {
                xml_print_attr_int(env, "Size", abs(entry->length));
            }

            xml_print_attr_version_span(env, &entry->base);
            xml_print_element_start_tag_end(env, TRUE);
            xml_generate_element_description(env, &entry->base);
            
        xml_generate_element_isihdr_info(env, &entry->base);
        xml_generate_element_html_info(env, &entry->base);
        xml_generate_element_pmd_info(env, &entry->base);
        xml_generate_element_suppress_autogen_warnings(env, &entry->base);

            xml_generate_element_ftd_mode(env, &entry->base);
            if (prop_has(&entry->base, PROPERTY_FTD_IS_STATIC_DATA))
            {
                xml_print_element_simple(env, "FtdIsStaticData");
            }

            /* Print the actual FTD content */
            if (entry->base.flag & AUTOGEN_DATA_STRING)
            {
                xml_print_element_start_tag(env, "String");
                xml_print_attr_string(env, "Name", entry->parname);

                if (prop_has_value(&entry->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH) ||
                    prop_has_value(&entry->base, PROPERTY_FTD_STRING_MAXIMUM_LENGTH))
                {
                    if (prop_has(&entry->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH))
                    {
                        xml_print_attr_int(env, "MinLength", (int)prop_get_value(&entry->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH));
                    }
                    if (prop_has(&entry->base, PROPERTY_FTD_STRING_MAXIMUM_LENGTH))
                    {
                        xml_print_attr_int(env, "MaxLength", (int)prop_get_value(&entry->base, PROPERTY_FTD_STRING_MAXIMUM_LENGTH));
                    }
                }
                
                xml_print_element_end_tag_empty(env);

                xml_generate_element_description(env, &entry->base);
            
                xml_generate_element_isihdr_info(env, &entry->base);
                xml_generate_element_html_info(env, &entry->base);
                xml_generate_element_pmd_info(env, &entry->base);
                xml_generate_element_suppress_autogen_warnings(env, &entry->base);
            }
            else
            {
                xml_generate_sequence_items(env, &entry->base.child_list, TRUE);
            }

            /* Print the rest... */
            xml_print_element_end_tag(env, el_name);

            entry = (autogen_data*)entry->base.next;
        }

        xml_print_element_end_tag(env, "FtdTable");
    }
}

LOCAL void xml_generate_element_ppc_table(xml_environment* env, autogen_tbl* tbl)
{
    autogen_data* entry = (autogen_data*)autogen_obj_get_first_in_list(&tbl->base.child_list);
    if (entry)
    {
        xml_print_element_start_tag(env, "PpcTable");
        xml_print_attr_version_span(env, &tbl->base);
        xml_print_element_start_tag_end(env, TRUE);

        /* Generate table description  */
        xml_generate_element_description(env, &tbl->base);
        xml_generate_element_isihdr_info(env, &tbl->base);
        xml_generate_element_html_info(env, &tbl->base);
        xml_generate_element_pmd_info(env, &tbl->base);
        xml_generate_element_suppress_autogen_warnings(env, &tbl->base);

        while (entry)
        {
            xml_print_element_start_tag(env, "PpcEntry");
            xml_print_attr_string(env, "Name", entry->base.name);

            xml_print_attr_hex(env, "Id", entry->base.id, 5);
            xml_print_attr_string(env, "SequenceName", entry->seqname);

            xml_print_attr_version_span(env, &entry->base);
            xml_print_element_end_tag_comment(env, "PpcEntry", &entry->base);

            entry = (autogen_data*)entry->base.next;
        }
        
        xml_print_element_end_tag(env, "PpcTable");
    }
}

LOCAL void xml_generate_element_ftd_mode(xml_environment* env, const autogen_obj* obj)
{
    unsigned int modes = (unsigned int)prop_get_value_default(obj, PROPERTY_FTD_SUPPORTED_MODES, FTD_MODE_RD);

    xml_print_element_start_tag(env, "SupportedModes");
    xml_print_element_start_tag_end(env, TRUE);

    if (modes & FTD_MODE_OPERATOR)
    {
        xml_print_element_start_tag(env, "Mode");
        xml_print_element_start_tag_end(env, FALSE);
        xml_print_text(env, "Operator");
        xml_print_element_end_tag(env, "Mode");
    }
    if (modes & FTD_MODE_INFRA)
    {
        xml_print_element_start_tag(env, "Mode");
        xml_print_element_start_tag_end(env, FALSE);
        xml_print_text(env, "InfraVendors");
        xml_print_element_end_tag(env, "Mode");
    }
    if (modes & FTD_MODE_RD)
    {
        xml_print_element_start_tag(env, "Mode");
        xml_print_element_start_tag_end(env, FALSE);
        xml_print_text(env, "RD");
        xml_print_element_end_tag(env, "Mode");
    }

    xml_print_element_end_tag(env, "SupportedModes");
}


/* ================================================================================================ */
/* Sequences */
/* ================================================================================================ */

/* General function for all sequence types */
LOCAL void xml_generate_sequences(xml_environment* env, unsigned int obj_type, const char* outer_el_name, const char* el_name)
{
    autogen_seq* seq;
    autogen_it seq_it = INIT_ITERATOR;

    seq_it.typemask = obj_type;
    seq_it.flagnone = AUTOGEN_OBJ_IS_SHARED | AUTOGEN_SEQ_IS_NOT_STRUCT;

    seq = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &env->res->seq_list);
    if (seq)
    {
        xml_print_element_start_tag(env, outer_el_name);
        xml_print_element_start_tag_end(env, TRUE);

        while (seq)
        {
            xml_print_element_start_tag(env, el_name);
            xml_print_attr_string(env, "Name", seq->base.name);

            if (obj_type == AUTOGEN_OBJ_SB)
            {
                const autogen_item* id_item = reference_get_special_item(&seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID);

                xml_print_attr_hex(env, "Id", seq->base.id, xml_calc_chars(id_item->length));
            }

            xml_print_attr_version_span(env, &seq->base);
            xml_print_element_start_tag_end(env, TRUE);

            xml_generate_element_featureflag(env, seq->base.feature_flags);
            xml_generate_element_description(env, &seq->base);
            xml_generate_element_isihdr_info(env, &seq->base);
            xml_generate_element_html_info(env, &seq->base);
            xml_generate_element_pmd_info(env, &seq->base);
            xml_generate_element_suppress_autogen_warnings(env, &seq->base);

            if (obj_type == AUTOGEN_OBJ_SB)
            {
                if (prop_has(&seq->base, PROPERTY_SB_LENGTH_LIMIT))
                {
                    xml_print_element_start_tag(env, "SubblockLengthLimit");
                    xml_print_element_start_tag_end(env, FALSE);

                    xml_print_text(env, prop_get_string(&seq->base, PROPERTY_SB_LENGTH_LIMIT));

                    xml_print_element_end_tag(env, "SubblockLengthLimit");

                }
                if (prop_has(&seq->base, PROPERTY_SB_LENGTH_MISSING))
                {
                    xml_print_element_simple(env, "SubblockLengthMissing");
                }
                if (prop_has(&seq->base, PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4))
                {
                    xml_print_element_simple(env, "SubblockLengthNotDivisibleBy4");
                }
                if (prop_has(&seq->base, PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY))
                {
                    xml_print_element_simple(env, "SubblockLengthRelatesToDataPartOnly");
                }
            }

            xml_generate_sequence_items(env, &seq->base.child_list, TRUE);

            xml_print_element_end_tag(env, el_name);

            seq = (autogen_seq*)autogen_obj_find_next_in_list(&seq_it);
        }

        xml_print_element_end_tag(env, outer_el_name);
    }
}

LOCAL void xml_generate_element_structures(xml_environment* env)
{
    xml_generate_sequences(env, AUTOGEN_OBJ_SEQ, "Structures", "Structure");
}

LOCAL void xml_generate_element_subblocks(xml_environment* env)
{
    xml_generate_sequences(env, AUTOGEN_OBJ_SB, "Subblocks", "Subblock");
}

LOCAL void xml_generate_element_subblock_templates(xml_environment* env)
{
    xml_generate_sequences(env, AUTOGEN_OBJ_SB_TEMPLATE, "SubblockTemplates", "SubblockTemplate");
}

LOCAL void xml_generate_element_message(xml_environment* env, autogen_obj* msg)
{
    /* Some servers have empty messages (old problem that autogen has allowed it */
    if (msg->child_list.n_obj > 0)
    {
        xml_print_element_start_tag(env, "Message");
        xml_print_attr_string(env, "Name", msg->base_obj->name);
        xml_print_attr_hex(env, "Id", msg->base_obj->id, xml_calc_chars(env->res->msg_id_size));

        if (msg->flag & AUTOGEN_MSG_IS_SUBMSG)
        {
            xml_print_attr_string(env, "SubName", msg->name);
            xml_print_attr_hex(env, "SubId", msg->id, xml_calc_chars(env->res->submsg_id_size));
        }

        /* Get text */
        if (msg->type == AUTOGEN_OBJ_MSG_BASE)
        {
            xml_print_attr_string(env, "Function", "Base");
        }
        else if (msg->flag & AUTOGEN_MSG_REQ)
        {
            xml_print_attr_string(env, "Function", "Request");
        }
        else if (msg->flag & AUTOGEN_MSG_RESP)
        {
            xml_print_attr_string(env, "Function", "Response");
        }
        else if (msg->flag & AUTOGEN_MSG_IND)
        {
            xml_print_attr_string(env, "Function", "Indication");
        }
        else if (msg->flag & AUTOGEN_MSG_NTF)
        {
            xml_print_attr_string(env, "Function", "Notification");
        }
        else if (msg->flag & AUTOGEN_MSG_TRC_STI)
        {
            xml_print_attr_string(env, "Function", "StiTrace");
        }
        else
        {
            if (msg->parent->type | RESOURCE_ISI_ANY)
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                    "Unsupported message function in message '%s'. Only Base, Request, Response, Indication, and Notification supported", msg->base_obj->name);
            }
        }

        xml_print_attr_version_span(env, msg);
        xml_print_element_start_tag_end(env, TRUE);
        xml_generate_element_featureflag(env, msg->feature_flags);
        xml_generate_element_description(env, msg);


        xml_generate_element_isihdr_info(env, msg);
        xml_generate_element_html_info(env, msg);
        xml_generate_element_pmd_info(env, msg);
        xml_generate_element_suppress_autogen_warnings(env, msg);
        xml_generate_element_related_messages(env, msg);


        if (prop_has(msg, PROPERTY_MSG_LENGTH_RELATES_TO_DATA_PART_ONLY))
        {
            xml_print_element_simple(env, "MessageLengthRelatesToDataPartOnly");
        }

        xml_generate_sequence_items(env, &msg->child_list, TRUE);

        xml_print_element_end_tag(env, "Message");
    }
}

LOCAL void xml_generate_element_messages(xml_environment* env)
{
    autogen_obj_list* msg_list[2] = { NULL, NULL };
    unsigned int n_msg_list = 1; 

    if (prop_has(&env->res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        msg_list[0] = &env->res->msg_dev_dep_req_list;
        msg_list[1] = &env->res->msg_dev_dep_resp_list;

        n_msg_list = 2;
    }
    else
    {
        msg_list[0] = &env->res->msg_list;
        msg_list[1] = &env->res->msg_list;
    }

    if (msg_list[0]->n_obj > 0 || msg_list[1]->n_obj > 0)
    {
        unsigned int n;

        xml_print_element_start_tag(env, "Messages");
        xml_print_element_start_tag_end(env, TRUE);

        for (n = 0; n < n_msg_list; n++)
        {
            autogen_seq* msg = (autogen_seq*)autogen_obj_get_first_in_list(msg_list[n]);
            while (msg)
            {
                xml_generate_element_message(env, &msg->base);

                if (msg->base.type == AUTOGEN_OBJ_MSG_BASE)
                {
                    autogen_obj* submsg = autogen_obj_get_first_in_list(&msg->submsg_list);
                    while (submsg)
                    {
                        xml_generate_element_message(env, submsg);

                        submsg = submsg->next;
                    }
                }

                msg = (autogen_seq*)msg->base.next;
            }
        }

        xml_print_element_end_tag(env, "Messages");
    }
}

LOCAL void xml_generate_element_traces(xml_environment* env)
{
    autogen_obj* trcgrp = autogen_obj_get_first_in_list(env->res->trcgrp_list);
    if (trcgrp)
    {
        xml_print_element_start_tag(env, "TraceGroups");
        xml_print_element_start_tag_end(env, TRUE);

        while (trcgrp)
        {
            const char* str_grp = prop_get_string_default(trcgrp, PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT, "");
            autogen_obj* trc;

            xml_print_element_start_tag(env, "TraceGroup");
            xml_print_attr_string(env, "Name", trcgrp->name);
            xml_print_attr_hex(env, "Id", trcgrp->id, xml_calc_chars(env->res->trc_conf->group_size));
            xml_print_element_start_tag_end(env, TRUE);

            /* Generate feature flag */
            xml_generate_element_featureflag(env, trcgrp->feature_flags);

            /* Generate trace group description */
            xml_generate_element_description(env, trcgrp);
            xml_generate_element_isihdr_info(env, trcgrp);
            xml_generate_element_html_info(env, trcgrp);
            xml_generate_element_pmd_info(env, trcgrp);
            xml_generate_element_suppress_autogen_warnings(env, trcgrp);

            if (trcgrp->child_list.n_obj > 0)
            {
                xml_print_element_start_tag(env, "Traces");
                xml_print_element_start_tag_end(env, TRUE);
            }


            if (trcgrp->base_obj->res->base.subtype == RESOURCE_TRC_MASTER)
            {
                autogen_it trc_it = INIT_ITERATOR;

                trc_it.typemask = AUTOGEN_OBJ_TRACE;

                trc = autogen_obj_find_in_list(&trc_it, env->res->trcgrp_list);
                if (trc)
                {
                    const char* str_trc = prop_get_string_default(trcgrp, PROPERTY_PMD_TRACE_DECODE_TEXT, "");
                    char* str_decode_text = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(str_grp) + strlen(str_trc) + 2);

                    strcpy(str_decode_text, str_grp);
                    strcat(str_decode_text, str_trc);

                    xml_print_element_start_tag(env, "Trace");

                    xml_print_attr_string(env, "Name", trcgrp->name);
                    xml_print_attr_hex(env, "Id", trcgrp->id, xml_calc_chars(env->res->trc_conf->group_size));
                    xml_print_attr_string(env, "DecodeName", str_decode_text);
                    xml_print_element_start_tag_end(env, TRUE);

                    /* Generate trace elements */
                    xml_generate_sequence_items(env, &trc->child_list, TRUE);

                    xml_print_element_end_tag(env, "Trace");

                }
            }
            else
            {
                trc = autogen_obj_get_first_in_list(&trcgrp->child_list);
                while (trc)
                {
                    const char* str_trc = prop_get_string_default(trc, PROPERTY_PMD_TRACE_DECODE_TEXT, "");

                    char* str_decode_text = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(str_grp) + strlen(str_trc) + 2);

                    strcpy(str_decode_text, str_grp);
                    strcat(str_decode_text, str_trc);

                    xml_print_element_start_tag(env, "Trace");
                    xml_print_attr_string(env, "Name", trc->name);
                    xml_print_attr_hex(env, "Id", trc->id, xml_calc_chars(env->res->trc_conf->id_size));
                    xml_print_attr_string(env, "DecodeName", str_decode_text);
                    xml_print_element_start_tag_end(env, TRUE);

                    /* Feature flags currently not supported inside TraceGroups */

                    /* Generate trace description */
                    xml_generate_element_description(env, trc);

                    xml_generate_element_isihdr_info(env, trc);
                    xml_generate_element_html_info(env, trc);
                    xml_generate_element_pmd_info(env, trc);
                    xml_generate_element_suppress_autogen_warnings(env, trc);

                    /* Generate trace elements */
                    xml_generate_sequence_items(env, &trc->child_list, TRUE);

                    xml_print_element_end_tag(env, "Trace");

                    trc = trc->next;
                }
            }
            if (trcgrp->child_list.n_obj > 0)
            {
                xml_print_element_end_tag(env, "Traces");
            }

            xml_print_element_end_tag(env, "TraceGroup");

            trcgrp = trcgrp->next;
        }

        xml_print_element_end_tag(env, "TraceGroups");
    }
}

/* ================================================================================================ */
/* Sequence items */
/* ================================================================================================ */

LOCAL void xml_generate_sequence_items(xml_environment* env, autogen_obj_list* obj_list, int print_details)
{
    autogen_item* item = (autogen_item*)autogen_obj_get_first_in_list(obj_list);
    while (item)
    {
        switch (item->base.subtype)
        {
        case AUTOGEN_ITEM_REF:
        case AUTOGEN_ITEM_VALUE:
        case AUTOGEN_ITEM_RANGE:
        case AUTOGEN_ITEM_POINTER:
        case AUTOGEN_ITEM_TIMESTAMP:
            xml_generate_element_number(env, (autogen_item_value*)item, print_details);
            break;

        case AUTOGEN_ITEM_FILLER:
            xml_generate_element_filler(env, item, print_details);
            break;

        case AUTOGEN_ITEM_LST:
            if (item->base.flag & AUTOGEN_LST_SBID)
            {
                xml_generate_element_subblock_list(env, item, print_details, TRUE);
            }
            else
            {
                xml_generate_element_subblock_list(env, item, print_details, FALSE);
            }
            break;

        case AUTOGEN_ITEM_STRING:
            xml_generate_element_string(env, (autogen_item_string*)item, print_details);
            break;

        case AUTOGEN_ITEM_MERGE:
            xml_generate_element_irregular_structure(env, item, print_details);
            break;

        case AUTOGEN_ITEM_CHOICE:
            xml_generate_element_selection(env, (autogen_item_choice*)item, print_details);
            break;

        case AUTOGEN_ITEM_STRUCT:
            xml_generate_element_structure_reference(env, (autogen_item_struct*)item, print_details);
            break;

        case AUTOGEN_ITEM_BLOCK:
            if (item->item_sub_type == BLOCK_PROTOCOL)
            {
                xml_generate_element_protocol_reference(env, (autogen_item_block*)item, print_details);
            }
            else
            if (item->item_sub_type == BLOCK_EXT_DECODER)
            {
                xml_generate_element_external_decoder(env, (autogen_item_block*)item, print_details);
            }
            else
            if (item->item_sub_type == BLOCK_PN_MSG)
            {
                xml_generate_element_phonet_msg_block(env, (autogen_item_block*)item, print_details);
            }
            else
            if (item->item_sub_type == BLOCK_PMD_ANCHOR)
            {
                xml_generate_element_pmd_anchor(env, (autogen_item_block*)item, print_details);
            }
            else
            if (item->item_sub_type == BLOCK_RAW_DATA)
            {
                xml_generate_element_raw_data_block(env, (autogen_item_block*)item, print_details);
            }
            else
            if (item->item_sub_type == BLOCK_X_FILE)
            {
                xml_generate_element_x_file_block(env, (autogen_item_block*)item, print_details);
            }
            else /* whatever */
            {
                xml_generate_element_array_of_bytes(env, item, print_details);
            }
            break;

        case AUTOGEN_ITEM_PRINTF:
            xml_generate_element_printf(env, (autogen_item_printf *)item, print_details);
            break;
        }

        item = (autogen_item*)item->base.next;
    }
}

LOCAL void xml_generate_element_array_start(xml_environment* env, autogen_item* item, int print_details)
{
    if (item->agg_type != AGG_TYPE_FIXED_SINGLE)
    {
        xml_print_element_start_tag(env, item->agg_type == AGG_TYPE_DYNAMIC_OPTIONAL ? "Optional" : "Array");
        xml_print_attr_names(env, item, print_details);
        xml_print_attr_version_span(env, &item->base);
        xml_print_element_start_tag_end(env, TRUE);

        /* Generate feature flag */
        xml_generate_element_featureflag(env, item->base.feature_flags);

        /* Generate description */
        xml_generate_element_description(env, &item->base);
        xml_generate_element_isihdr_info(env, &item->base);
        xml_generate_element_html_info(env, &item->base);
        xml_generate_element_pmd_info(env, &item->base);
        xml_generate_element_suppress_autogen_warnings(env, &item->base);

        /* Generate size limitation */
        if (prop_has_valid_string(&item->base, PROPERTY_ARRAY_MAXIMUM_SIZE))
        {
            xml_print_element_start_tag(env, "ArrayMaximumSize");
            xml_print_element_start_tag_end(env, FALSE);

            xml_print_text(env, prop_get_string(&item->base, PROPERTY_ARRAY_MAXIMUM_SIZE));

            xml_print_element_end_tag(env, "ArrayMaximumSize");
        }

        /* Generate count info */
        xml_generate_element_count(env, item);
    }
}

LOCAL void xml_generate_element_array_end(xml_environment* env, const autogen_item* item)
{
    if (item->agg_type != AGG_TYPE_FIXED_SINGLE)
    {
        xml_print_element_end_tag(env, item->agg_type == AGG_TYPE_DYNAMIC_OPTIONAL ? "Optional" : "Array");
    }
}

LOCAL void xml_generate_element_array_of_bytes(xml_environment* env, autogen_item* item, int print_details)
{
    xml_generate_element_array_start(env, item, print_details);

    /* Generate number */
    xml_print_element_start_tag(env, "Number");
    xml_print_attr_names(env, item, FALSE);
    xml_print_attr_int(env, "Size", 8);
    xml_print_attr_bool(env, "Signed", FALSE);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.feature_flags);

    /* Generate presentation */
    xml_print_element_start_tag(env, "Presentation");
    xml_print_attr_string(env, "Type", "HexaDecimal");
    xml_print_element_end_tag_empty(env);

    xml_print_element_end_tag(env, "Number");

    xml_generate_element_array_end(env, item);
}

LOCAL void xml_generate_element_filler(xml_environment* env, const autogen_item* item, int print_details)
{
    const char* el_name = NULL;

    if (item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
    {
        el_name = xml_print_element_start_tag(env, "Alignment");
        xml_print_attr_int(env, "Boundary", item->length);
    }
    else
    {
        el_name = xml_print_element_start_tag(env, "Filler");
        /* Print varname and parname for completeness */
        if (print_details)
        {
            xml_print_attr_string(env, "Name", item->parname);
            xml_print_attr_string(env, "VarName", item->varname);
        }
        xml_print_attr_int(env, "Size", abs(item->length*item->agg_n));
    }

    xml_print_attr_version_span(env, &item->base);
    xml_print_element_end_tag_comment(env, el_name, &item->base);
}

LOCAL void xml_generate_element_irregular_structure(xml_environment* env, autogen_item* item, int print_details)
{
    /* Generate array info (start) */
    xml_generate_element_array_start(env, item, print_details);

    xml_print_element_start_tag(env, "IrregularStructure");
    xml_print_attr_names(env, item, print_details);
    xml_print_attr_int(env, "Size", abs(item->length));
    xml_print_attr_string(env, "Endian", item->order == AUTOGEN_ORDER_LE ? "LittleEndian" : "BigEndian");
    xml_print_attr_version_span(env, &item->base);
    xml_print_element_start_tag_end(env, TRUE);

    xml_generate_element_featureflag(env, item->base.feature_flags);
    xml_generate_element_description(env, &item->base);
    xml_generate_element_isihdr_info(env, &item->base);
    xml_generate_element_html_info(env, &item->base);
    xml_generate_element_pmd_info(env, &item->base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base);

    xml_generate_sequence_items(env, &item->base.child_list, TRUE);

    xml_print_element_end_tag(env, "IrregularStructure");

    /* Generate array info (end) */
    xml_generate_element_array_end(env, item);
}

LOCAL void xml_generate_element_number(xml_environment* env, autogen_item_value* item, int print_details)
{
    /* Handle special number types */
    if (item->base.special_number_type != PMD_NUMBER_SPECIAL_TYPE_NONE &&
		item->base.special_number_type != PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE &&
		item->base.special_number_type != PMD_NUMBER_SPECIAL_TYPE_TIMESTAMP &&
        item->base.special_number_type != PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE)
    {
        const char* el_name = pmd_constant_lookup_number_special_type_xml(item->base.special_number_type);
		if (item->base.special_number_type == PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_OBJECT)
		{
			el_name = "PhonetObject";
		}

        xml_print_element_start_tag(env, el_name);
        xml_print_attr_names(env, &item->base, print_details);
        xml_print_attr_int(env, "Size", abs(item->base.length));

        xml_print_element_end_tag_comment(env, el_name, &item->base.base);
    }
    /* Normal number types */
    else
    {
        const char* el_name = "Number";
		if (item->base.special_number_type == PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE)
		{
			el_name = "PhonetDevice";
		}

        /* Generate array info (start) */
        xml_generate_element_array_start(env, &item->base, print_details);

        xml_print_element_start_tag(env, el_name);
        xml_print_attr_names(env, &item->base, print_details);
        xml_print_attr_int(env, "Size", abs(item->base.length));
        xml_print_attr_bool(env, "Signed", item->base.length < 0);
        if (print_details)
        {
            xml_print_attr_string(env, "Endian", item->base.order == AUTOGEN_ORDER_LE ? "LittleEndian" : "BigEndian");
        }

        /* Print tag */
        if (item->base.base.name && item->base.base.name[0])
        {
            xml_print_attr_string(env, "Tag", item->base.base.name);
        }

        xml_print_element_start_tag_end(env, TRUE);

        /* Generate feature flag */
        xml_generate_element_featureflag(env, item->base.base.feature_flags);

        /* Generate number description */
        xml_generate_element_description(env, &item->base.base);

        /* Generate min, max, exceptional values */
        xml_generate_element_from_property(env, item, "DefaultValue", PROPERTY_ITEM_DEFAULT_VALUE, FALSE);
        xml_generate_element_from_property(env, item, "MinValue", PROPERTY_ITEM_MINIMUM_VALUE, FALSE);
        xml_generate_element_from_property(env, item, "MaxValue", PROPERTY_ITEM_MAXIMUM_VALUE, FALSE);
        xml_generate_element_from_property(env, item, "ExceptionalValues", PROPERTY_ITEM_EXCEPTIONAL_VALUE, TRUE);

        /* Generate presentation */
        xml_generate_element_presentation(env, item);

        /* Filler replacement */
        xml_generate_element_filler_replacement(env, &item->base.base);

        /* ISI Header info */
        xml_generate_element_isihdr_info(env, &item->base.base);
        /* HTML info */
        xml_generate_element_html_info(env, &item->base.base);
        /* PMD info */
        xml_generate_element_pmd_info(env, &item->base.base);
        xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

        xml_print_element_end_tag(env, el_name);

        /* Generate array info (end) */
        xml_generate_element_array_end(env, &item->base);
    }
}

LOCAL void xml_generate_element_protocol_reference(xml_environment* env, autogen_item_block* item, int print_details)
{
    xml_print_element_start_tag(env, "ProtocolReference");
    xml_print_attr_names(env, &item->base, print_details);
    xml_print_attr_string(env, "ProtocolName", item->data1);
    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

    /* Generate count */
    xml_generate_element_count(env, &item->base);

    xml_print_element_end_tag(env, "ProtocolReference");
}

LOCAL void xml_generate_element_dll_data_flags(xml_environment* env, autogen_item_block* item)
{
    if (item->base.base.flag)
    {
        xml_print_element_start_tag(env, "DecodeFlags");
        xml_print_element_start_tag_end(env, TRUE);
        xml_print_element_start_tag(env, "Flag");
        xml_print_element_start_tag_end(env, FALSE);
        if (item->base.base.flag & BLOCK_EXT_DECODER_SEND_WHOLE_EMB_MSG)
        {
            xml_print_text(env, "BLOCK_EXT_DECODER_SEND_WHOLE_EMB_MSG");
        }
        else 
        if (item->base.base.flag & BLOCK_EXT_DECODER_SKIP_ID)
        {
            xml_print_text(env, "BLOCK_EXT_DECODER_SKIP_ID");
        }
        else 
        if (item->base.base.flag & BLOCK_EXT_DECODER_SKIP_TRACE)
        {
            xml_print_text(env, "BLOCK_EXT_DECODER_SKIP_TRACE");
        }
        else 
        /* we have (item->base.base.flag & BLOCK_EXT_DECODER_SEND_FROM_TRACE_START) */
        {
            xml_print_text(env, "BLOCK_EXT_DECODER_SEND_FROM_TRACE_START");
        }
        xml_print_element_end_tag(env, "Flag");
        xml_print_element_end_tag(env, "DecodeFlags");
    }
}

LOCAL void xml_generate_element_external_decoder(xml_environment* env, autogen_item_block* item, int print_details)
{
    xml_print_element_start_tag(env, "ExternalDecoder");
    xml_print_attr_names(env, &item->base, print_details);
    xml_print_attr_string(env, "DecodeDLLName", item->data1);
    xml_print_attr_string(env, "FunctionName", item->data2);
    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

    /* Data handling flags */
    xml_generate_element_dll_data_flags(env, item);

    /* Generate count */
    xml_generate_element_count(env, &item->base);

    xml_print_element_end_tag(env, "ExternalDecoder");
}

LOCAL void xml_generate_element_phonet_msg_block(xml_environment* env, autogen_item_block* item, int print_details)
{
    xml_print_element_start_tag(env, "PhonetMessageBlock");
    xml_print_attr_names(env, &item->base, print_details);
    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

    /* Data handling flags */
    if (item->base.base.flag)
    {
        xml_print_element_start_tag(env, "MessageFlags");
        xml_print_element_start_tag_end(env, TRUE);
        xml_print_element_start_tag(env, "Flag");
        xml_print_element_start_tag_end(env, FALSE);
        if (item->base.base.flag & BLOCK_PN_MSG_SKIP_TRACE)
        {
            xml_print_text(env, "BLOCK_PN_MSG_SKIP_TRACE");
        }
        else /* ...should never happen */
        {
            xml_print_text(env, "");
        }
        xml_print_element_end_tag(env, "Flag");
        xml_print_element_end_tag(env, "MessageFlags");
    }
    /* Generate count */
    xml_generate_element_count(env, &item->base);

    xml_print_element_end_tag(env, "PhonetMessageBlock");
}

LOCAL void xml_generate_element_pmd_anchor(xml_environment* env, autogen_item_block* item, int print_details)
{
    xml_print_element_start_tag(env, "PmdAnchor");
    xml_print_attr_names(env, &item->base, print_details);
    xml_print_attr_string(env, "PmdStructureName", item->data1);
    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

    /* Generate count */
    xml_generate_element_count(env, &item->base);

    xml_print_element_end_tag(env, "PmdAnchor");
}

LOCAL void xml_generate_element_raw_data_block(xml_environment* env, autogen_item_block* item, int print_details)
{
    xml_print_element_start_tag(env, "RawData");
    xml_print_attr_names(env, &item->base, print_details);
    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

    /* Generate count */
    xml_generate_element_count(env, &item->base);

    xml_print_element_end_tag(env, "RawData");
}

LOCAL void xml_generate_element_x_file_block(xml_environment* env, autogen_item_block* item, int print_details)
{
    xml_print_element_start_tag(env, "XFile");
    xml_print_attr_names(env, &item->base, print_details);
    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

    /* Generate count */
    xml_generate_element_count(env, &item->base);

    xml_print_element_end_tag(env, "XFile");
}

LOCAL void xml_generate_element_selection(xml_environment* env, autogen_item_choice* item, int print_details)
{
    autogen_obj* case_item = NULL;

    /* Generate array info (start) */
    xml_generate_element_array_start(env, &item->base, print_details);

    xml_print_element_start_tag(env, "Selection");
    xml_print_attr_names(env, &item->base, print_details);
    xml_print_attr_string(env, "TagName", item->base.refname);
    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate choice description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

    /* Normal cases */
    case_item = autogen_obj_get_first_in_list(&item->base.base.child_list);
    while (case_item)
    {
        const char* el_name = xml_print_element_start_tag(env, "Case");

        xml_print_attr_string(env, "TagValue", case_item->name);

        xml_print_attr_version_span(env, case_item);
        /* Feature flags not supported at this level */
        xml_print_element_start_tag_end(env, TRUE);

        xml_generate_element_description(env, case_item);
        xml_generate_element_isihdr_info(env, case_item);
        xml_generate_element_html_info(env, case_item);
        xml_generate_element_pmd_info(env, case_item);
        xml_generate_element_suppress_autogen_warnings(env, case_item);

        xml_generate_sequence_items(env, &case_item->child_list, print_details);

        xml_print_element_end_tag(env, el_name);

        case_item = case_item->next;
    }

    /* Default items */
    case_item = (autogen_obj*)item->default_case;
    if (case_item)
    {
        const char* el_name = xml_print_element_start_tag(env, "Default");

        xml_print_attr_version_span(env, case_item);
        /* Feature flags not supported at this level */
        xml_print_element_start_tag_end(env, TRUE);

        xml_generate_element_description(env, case_item);
        xml_generate_element_isihdr_info(env, case_item);
        xml_generate_element_html_info(env, case_item);
        xml_generate_element_pmd_info(env, case_item);
        xml_generate_element_suppress_autogen_warnings(env, case_item);

        xml_generate_sequence_items(env, &case_item->child_list, print_details);

        xml_print_element_end_tag(env, el_name);
    }

    xml_print_element_end_tag(env, "Selection");

    /* Generate array info (end) */
    xml_generate_element_array_end(env, &item->base);
}

LOCAL void xml_generate_element_string(xml_environment* env, autogen_item_string* item, int print_details)
{
    xml_print_element_start_tag(env, "String");
    xml_print_attr_names(env, &item->base, print_details);

    /* Print string type attribute */
    if (item->base.base.flag & STRING_ASCII)
    {
        xml_print_attr_string(env, "Type", "Ascii");
    }
    else if (item->base.base.flag & STRING_UNICODE)
    {
        xml_print_attr_string(env, "Type", "Unicode");
    }
    else if (item->base.base.flag & STRING_BCD)
    {
        xml_print_attr_string(env, "Type", "Bcd");
    }
    else if (item->base.base.flag & STRING_UTF8)
    {
        xml_print_attr_string(env, "Type", "Utf8");
    }
    else if (item->base.base.flag & STRING_GSM)
    {
        xml_print_attr_string(env, "Type", "Gsm");
    }

    if (print_details)
    {
		if (item->base.base.flag & STRING_BCD)
		{
            xml_print_attr_string(env, "Endian", item->base.order == AUTOGEN_ORDER_BCD_NONE ? "NoBcdNsw" : "BcdNsw");
		}
		else
		{
            xml_print_attr_string(env, "Endian", item->base.order == AUTOGEN_ORDER_LE ? "LittleEndian" : "BigEndian");
		}
    }

    xml_print_attr_bool(env, "IsZeroTerminated", (item->base.base.flag & AUTOGEN_STRING_ZERO_TERMINATED) == AUTOGEN_STRING_ZERO_TERMINATED);
    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate string description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);


    /* If string type is BCD then print BCD to ASCII map if specified */
    if (item->base.base.flag & STRING_BCD)
    {
        xml_generate_element_string_bcd_map(env, &item->base.base);
    }
    if (prop_has(&item->base.base, PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH))
    {
        xml_print_element_simple(env, "StringExcludeZeroTerminationFromLength");
    }
    if (prop_has(&item->base.base, PROPERTY_STRING_UNFORMATTED))
    {
        xml_print_element_simple(env, "StringUnformatted");
    }
    if (prop_has(&item->base.base, PROPERTY_STRING_MAXIMUM_LENGTH))
    {
        xml_print_element_start_tag(env, "StringMaximumLength");
        xml_print_element_start_tag_end(env, FALSE);

        xml_print_text(env, prop_get_string(&item->base.base, PROPERTY_STRING_MAXIMUM_LENGTH));

        xml_print_element_end_tag(env, "StringMaximumLength");
    }
    /* Generate string length info (count) */
    xml_generate_element_count(env, &item->base);

    xml_print_element_end_tag(env, "String");
}

LOCAL void xml_generate_element_structure_reference(xml_environment* env, autogen_item_struct* item, int print_details)
{
    const char* el_name = NULL;

    /* Generate array info (start) */
    xml_generate_element_array_start(env, &item->base, print_details);

    if (item->base.base.flag & AUTOGEN_STRUCT_SEQ)
    {
        el_name = xml_print_element_start_tag(env, "StructureReference");
    }
    else
    {
        el_name = xml_print_element_start_tag(env, "SubblockReference");
    }

    xml_print_attr_names(env, &item->base, print_details);
    xml_print_attr_version_span(env, &item->base.base);

    if (item->base.base.flag & AUTOGEN_STRUCT_SEQ)
    {
        xml_print_attr_string(env, "StructureName", item->seqname);
    }
    else
    {
        xml_print_attr_string(env, "SubblockName", item->seqname);
    }

    xml_print_element_end_tag_comment(env, el_name, &item->base.base);

    /* Generate array info (end) */
    xml_generate_element_array_end(env, &item->base);
}

LOCAL void xml_generate_element_subblock_list(xml_environment* env, autogen_item* item, int print_details, int only_ids)
{
    autogen_obj* entry;

    entry = autogen_obj_get_first_in_list(&item->base.child_list);
    if (entry)
    {
        const char* el_name = xml_print_element_start_tag(env, only_ids ? "SubblockIdList" : "SubblockList");
        xml_print_attr_names(env, item, print_details);
        xml_print_attr_version_span(env, &item->base);
        xml_print_element_start_tag_end(env, TRUE);

        /* Generate feature flag */
        xml_generate_element_featureflag(env, item->base.feature_flags);

        /* Generate description */
        xml_generate_element_description(env, &item->base);
        xml_generate_element_isihdr_info(env, &item->base);
        xml_generate_element_html_info(env, &item->base);
        xml_generate_element_pmd_info(env, &item->base);
        xml_generate_element_suppress_autogen_warnings(env, &item->base);

        /* Generate length info */
        xml_generate_element_count(env, item);

        /* Hard-coded FTD sub blocks */
        if (item->base.flag & AUTOGEN_LST_FTD)
        {
            xml_print_element_start_tag(env, "FtdData");
            xml_print_element_end_tag_empty(env);
        }

        /* Normal sub blocks */
        while (entry)
        {
            xml_print_element_start_tag(env, "SubblockReference");
            xml_print_attr_string(env, "SubblockName", entry->name);
            xml_print_attr_version_span(env, entry);
            xml_print_element_end_tag_comment(env, "SubblockReference", entry);

            entry = entry->next;
        }

        xml_print_element_end_tag(env, el_name);
    }
}

LOCAL void xml_generate_element_string_bcd_map(xml_environment* env, const autogen_obj* obj)
{
    const char *bcd_map;
    char index;
    const char* section_el_name = NULL;
    int size = 0;
    if (prop_has(obj, PROPERTY_STRING_BCD_MAP))
    {
        bcd_map = prop_get_string(obj, PROPERTY_STRING_BCD_MAP);
        size = strlen(bcd_map);
        section_el_name = xml_print_element_start_tag(env, "StringBcdMap");
        xml_print_element_start_tag_end(env, TRUE);
        for (index = 0; index < 16; index++)
        {
            xml_print_element_start_tag(env, "Map");
            xml_print_attr_int(env, "BCD", index);
            if (index < size)
            {
                xml_print_attr_int(env, "ASCII", *(bcd_map+index));
            }
            else
            {
                xml_print_attr_int(env, "ASCII", 0);
            }
            xml_print_element_end_tag_empty(env);
        }
        xml_print_element_end_tag(env, section_el_name);
    }

}

LOCAL void xml_generate_element_printf(xml_environment* env, autogen_item_printf* item, int print_details)
{
    xml_print_element_start_tag(env, "Printf");
    xml_print_attr_names(env, &item->base, print_details);

    /* Print out format string. */
    /* Contains %<specifier> so we can not use xml_print_attr_string() directly */
    fprintf(env->fxml, " %s=\"", "Format");
    xml_print_text(env, item->format);
    fprintf(env->fxml, "\"");

    xml_print_attr_version_span(env, &item->base.base);
    xml_print_element_start_tag_end(env, TRUE);

    /* Generate feature flag */
    xml_generate_element_featureflag(env, item->base.base.feature_flags);

    /* Generate printf description */
    xml_generate_element_description(env, &item->base.base);
    xml_generate_element_isihdr_info(env, &item->base.base);
    xml_generate_element_html_info(env, &item->base.base);
    xml_generate_element_pmd_info(env, &item->base.base);
    xml_generate_element_suppress_autogen_warnings(env, &item->base.base);

    /* Output printf arguments */
    xml_generate_sequence_items(env, &item->base.base.child_list, print_details);

    xml_print_element_end_tag(env, "Printf");
}

/* ============================================================================================= */
/* Global function */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: output_xml
 
    Purpose: 
        The main function for generating XML output.
 
    Functional Description:
        Generates XML format based on contents of isi header macro files

    Arguments: 
        MakeAutobuilderVersionFiles: bool. If TRUE the version files for the autobuilder is written to disk.
*/
/* --------------------------------------------------------------------------------------------- */

void output_xml(int MakeAutobuilderVersionFiles)
{
    xml_environment env;

    env.heap_handle = pmd_heap_init_h(80000);
    env.char_buffer = (char*)pmd_heap_alloc_h(env.heap_handle, 4096);
    env.filename    = (char*)pmd_heap_alloc_h(env.heap_handle, 255);

    printf("Generating XML documents\n");
    fprintf(g_log, "\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");
    fprintf(g_log, "Generating XML documents\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");

    /*  generate xml output for all resources */
    {
        env.res = (autogen_res*)autogen_obj_get_first_in_list(g_res_list);
        while (env.res)
        {
            /* Only generate file, if name is defined in resource configuration */
            if (env.res->conf->xml_name)
            {
                const char* prefix = "";
                const char* isi_ext = "";
                const char* shared_ext = "";
                const char* trace_ext = "";

                if (env.res->base.subtype == RESOURCE_TRC_INVARIANT)
                {
                    prefix = "inv_trace_";
                }
                else if (env.res->base.subtype == RESOURCE_TRC_VENDOR)
                {
                    prefix = "vendor_trace_";
                }
                else if (env.res->base.subtype == RESOURCE_TRC_SYMBIAN)
                {
                    prefix = "symbian_";
                }
                else if (env.res->base.subtype == RESOURCE_PROTOCOL || 
                         env.res->base.subtype == RESOURCE_PROTOCOL_EXTENSION)
                {
                    prefix = "prot_";
                }

			    if (env.res->base.subtype == RESOURCE_TRC_MCU)
			    {
                    trace_ext = "_mcu_trace";
			    }
			    else if (env.res->base.subtype == RESOURCE_TRC_OS)
			    {
                    trace_ext = "_trace"; /* shortname is nos */
			    }
			    else if ((env.res->base.subtype == RESOURCE_TRC_HAL) ||
                    (env.res->base.subtype == RESOURCE_TRC_HSP) ||
                    (env.res->base.subtype == RESOURCE_TRC_CDSP5) ||
                    (env.res->base.subtype == RESOURCE_TRC_ADSP5) ||
                    (env.res->base.subtype == RESOURCE_TRC_SYMBIAN))
			    {
                    trace_ext = "_trace";
			    }
			    else if (env.res->base.subtype == RESOURCE_TRC_MASTER)
			    {
                    trace_ext = "_master_trace";
			    }

                if (env.res->base.subtype & RESOURCE_ISI_ANY)
                {
                    isi_ext = "_isi";
                }
                if (env.res->base.subtype == RESOURCE_ISI_SHARED)
                {
                    shared_ext = "_shared";
                }

                sprintf(env.filename, "%s%s%s%s%s.xml", prefix, env.res->resnameshort_l, shared_ext, isi_ext, trace_ext);

                if (MakeAutobuilderVersionFiles == TRUE)
                {
                    util_write_version_file(env.filename, &(env.res->base.ver));
                }

                xml_generate_file(&env);
            }
			else if (env.res->base.subtype == RESOURCE_SYMBOLS)
			{
                strcpy(env.filename, "symbols.xml");

                xml_generate_file(&env);
			}

            env.res = (autogen_res*)env.res->base.next;
        }
    }

    pmd_heap_free_h(env.heap_handle);
}

#endif  /* AUTOGEN_ENVIRONMENT_LOCAL */
