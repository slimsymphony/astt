/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_html.c
                -------------
                SW Module






Project:          autogen

%name:            output_html.c %
%version:         co1tss#147 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Wed Nov 18 13:41:30 2009 %

Copyright (c) Nokia. All right reserved 
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the source code for the HTML output generator.
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_ref.h"
#include "autogen_object.h"
#include "autogen_prop.h"
#include "autogen_util.h"
#include "pmd_heap.h"
#include "autogen_ver_history.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#ifdef _MSC_VER
 #include <direct.h>
#endif

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
#define LOCAL static
#endif /* LOCAL */

#ifdef _MSC_VER /* We use strict ANSI option, where chdir, mkdir, and getcwd are not declared */
 #define chdir _chdir
 #define getcwd _getcwd
 #define mkdir _mkdir
#endif /* _MSC_VER */


#define TRACE_CONSTANT_TABLE        1
#define TRACE_BIT_TABLE             2
#define TRACE_CONSTANT              3
#define TRACE_SEQUENCE              4

#define HTML_NEWLINE_BEFORE         0x0001
#define HTML_NEWLINE_AFTER          0x0002
#define HTML_NEWLINE_NONE           0x0004
#define HTML_SET_FONT               0x0008
#define HTML_SET_ITALIC             0x0010

/* Structure for storing a list of feature flags */
typedef struct t_html_featureflag_lst
{
    /* Next feature flag in list */
    struct t_html_featureflag_lst *next;

    /* The tag/name given to this feature flag */
    unsigned int tag;

    /* The feature flag */
    autogen_feature *featureFlag;

} html_featureflag_lst;

typedef struct t_html_environment
    {
    /* pointer to the html file */
    FILE* fhtml;

    /* filename */
    const char* filename;

    /* GIF_SPECS directory depth */
    int gif_depth;

    /* should the varname be printed at the moment ? */
    int print_varname;

    /* is the current structure dynamic at this point ? */
    int is_dynamic;

    /* is table of contents generated in frame? */
    int is_in_frame;

    int section_index;

    /* pointer to the current resource */
    autogen_res* res;

    /* handle to heap to be used for all allocations */
    pmd_heap_handle* heap_handle;

    /* buffer allocated for string buffer handling */
    char* char_buffer;

    /* to collect feature flags */
    struct {
        char *char_buffer;
        unsigned int tag_count;
        html_featureflag_lst *head;
        html_featureflag_lst *tail;
    } collect_feature_flags;

    } html_environment;


LOCAL void html_bit_tbl(html_environment* env, autogen_tbl* tbl);
LOCAL const char* html_build_limits(html_environment* env, const autogen_obj* limit_obj, const autogen_ver* ver, const autogen_pres* pres);
LOCAL void html_comment(html_environment* env, const autogen_cmt* cmt_list, unsigned int flag);

LOCAL autogen_tbl* html_find_symbol(const char* name);

LOCAL const char* html_const_link(html_environment* env, const char* name, const autogen_ver* ver);
LOCAL void html_const_tbl(html_environment* env, autogen_tbl* const_tbl);
LOCAL void html_ftd_tbl(html_environment* env, autogen_tbl* tbl);
LOCAL void html_ftd(html_environment* env, autogen_data* ftd);

LOCAL void html_generate_introduction_section(html_environment* env, int* sec1, int is_toc);

LOCAL void html_generate_message_header_section(html_environment* env, int* sec1, int is_toc);
LOCAL void html_generate_message_id_section(html_environment* env, int sec1, int* sec2, int is_toc);
LOCAL void html_generate_message_ids(html_environment* env, unsigned int flagany, autogen_obj_list* msg_list, const char* heading_suffix, const char* linkname, int sec1, int* sec2, int is_toc);
LOCAL void html_generate_message_section(html_environment* env, int* sec1, int is_toc);
LOCAL void html_generate_messages(html_environment* env, unsigned int flagany, autogen_obj_list* msg_list, const char* heading_suffix, int* sec1, int is_toc);

LOCAL void html_generate_sequence_section(html_environment* env, int* sec1, int is_toc);
LOCAL void html_generate_sequences(html_environment* env, unsigned int typemask, const char* heading_prefix, int* sec1, int is_toc);

LOCAL void html_generate_traces(html_environment* env, int* sec1, int is_toc);

LOCAL const char* html_generate_reference_text(html_environment* env, autogen_item* item);

LOCAL void html_item_choice(html_environment* env, autogen_item_choice* choice);
LOCAL void html_item_filler(html_environment* env, autogen_item* item);
LOCAL void html_item_lst(html_environment* env, autogen_item* item);
LOCAL void html_item_merge(html_environment* env, autogen_item* item);
LOCAL void html_item_ref(html_environment* env, autogen_item* item);
LOCAL void html_item_struct(html_environment* env, autogen_item* item);
LOCAL void html_item_trcstruct(html_environment* env, autogen_item* item);
LOCAL void html_item_range(html_environment* env, autogen_item* item);
LOCAL void html_item_value(html_environment* env, autogen_item* item);
LOCAL void html_item_timestamp(html_environment* env, autogen_item* item);
LOCAL void html_item_pointer(html_environment* env, autogen_item* item);
LOCAL void html_item_string(html_environment* env, autogen_item* item);
LOCAL void html_item_block(html_environment* env, autogen_item* item);
LOCAL void html_item_printf(html_environment* env, autogen_item* item);

LOCAL void html_msg(html_environment* env, autogen_seq* seq, int is_toc);
LOCAL const char* html_obj_link(html_environment* env, const autogen_obj* obj, const autogen_res* res);
LOCAL const char* html_obj_ver_pres(html_environment* env, const autogen_obj* obj, autogen_obj_list* obj_list, const autogen_ver* ver, const autogen_ver* parent_ver); 
LOCAL const char* html_obj_ver_string(const autogen_ver* ver);

LOCAL void html_ppc_tbl(html_environment* env, autogen_tbl* tbl);
LOCAL void html_print_rel(html_environment* env, autogen_obj* obj, const char* objtypestr);

LOCAL void html_notes(html_environment* env);

LOCAL void html_sec(html_environment* env,  int is_toc, int sec, const char* format, ...);
LOCAL void html_ver_info(html_environment* env, const autogen_obj* obj);
LOCAL void html_seq(html_environment* env, autogen_seq* seq, int is_toc);
LOCAL void html_seq_items(html_environment* env, autogen_obj_list* obj_list);
LOCAL void html_res(html_environment* env);
LOCAL void html_subsec(html_environment* env, int is_toc, int sec1, int sec2, int sec3, const char* title, const char* refname, const char* linkname);
LOCAL void html_table(html_environment* env);
LOCAL void html_table_dat(html_environment* env, int courier, int grey, int bold, int width, const char* format, ...);
LOCAL void html_table_com(html_environment* env, const autogen_cmt* cmt_list);
LOCAL void html_table_ref(html_environment* env, const char* linkname, const char* itemname, const autogen_cmt* cmt, const char *postfixTxt);
LOCAL void html_table_size(html_environment* env, autogen_item* item);
LOCAL void html_table_par(html_environment* env, autogen_item* item);
#if (PMD_FILE_FORMAT >= 600)
LOCAL void html_table_pres(html_environment* env, const autogen_pres* pres, const autogen_obj* limit_obj, const autogen_ver* ver,
                           autogen_cmt* cmt_list, int add_cell, int has_def_val, unsigned long long def_val, const char* def_val_str, int length);
#else
LOCAL void html_table_pres(html_environment* env, const autogen_pres* pres, const autogen_obj* limit_obj, const autogen_ver* ver,
                           autogen_cmt* cmt_list, int add_cell, int has_def_val, unsigned int def_val, const char* def_val_str, int length);
#endif
LOCAL void html_table_row(html_environment* env, int fill);
LOCAL void html_table_row_end(html_environment* env);
LOCAL void html_table_section_start(html_environment* env, int use_new_index, const char* format, ...);
LOCAL void html_table_section_end(html_environment* env, const char* format, ...);
LOCAL void html_table_var(html_environment* env, autogen_item* item);

LOCAL const char* html_up_level(html_environment* env);

LOCAL void html_write_toc(html_environment* env);

LOCAL void html_add_featureflag_lst(html_environment *env, autogen_feature *feature_flag, char *formattedTag);
LOCAL void html_print_feature_flag_lst(html_environment *env);
LOCAL void html_print_feature_flag(html_environment* env, const char *prefix, const autogen_feature* feature_flag);

/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/*  Generates the HTML output for the bit table pointed to by 'tbl' 
*/

LOCAL void html_bit_tbl(html_environment* env, autogen_tbl* tbl)
{
    autogen_it entry_it = INIT_ITERATOR;
    char format_str[100];
    int nchar = 2;   
    autogen_bittbl_entry* entry;

    entry_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    html_ver_info(env,(autogen_obj*)tbl);

    html_comment(env, tbl->base.cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);

    if (tbl->base.feature_flags)
    {
        /* Print out feature flag */
        html_print_feature_flag(env, "<b>Feature flag:</b>", tbl->base.feature_flags);
    }

    html_table(env);
    html_table_row(env, TRUE);
    html_table_dat(env, 0, 0, 1, 0, "Bit ID");
    html_table_dat(env, 0, 0, 1, 0, "Bit mask");
    html_table_dat(env, 0, 0, 1, 0, "Bit map");
    html_table_dat(env, 0, 0, 1, 0, "Comment");
    html_table_row_end(env);

    if (tbl->length > 8 && tbl->length <= 16)
    {
        nchar = 4;
    }
    else if (tbl->length > 16 && tbl->length <= 32)
    {
        nchar = 8;
    }
    else if (tbl->length > 32)
    {
        nchar = 16;
    }

#if (PMD_FILE_FORMAT >= 600)
    sprintf(format_str, "0x%%%d.%dllX", nchar, nchar);
#else
    sprintf(format_str, "0x%%%d.%dX", nchar, nchar);
#endif

    entry = (autogen_bittbl_entry*)autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
    while (entry)
    {
        char* itemname = (char*)pmd_heap_alloc_h(env->heap_handle, 25 + strlen(entry->base.name));

        html_table_row(env, FALSE);

        strcpy(itemname, entry->base.name);

        if (!autogen_obj_ver_is_exact(&entry->base.ver, &tbl->base.ver))
        {
            strcat(itemname, " ");
            strcat(itemname, html_obj_ver_string(&entry->base.ver));
        }

        /* Check for presence of feature flag */
        if (entry->base.feature_flags)
        {
            /* Feature flags present */
            html_add_featureflag_lst(env, entry->base.feature_flags, env->collect_feature_flags.char_buffer);
            html_table_dat(env, 0, 0, 0, 0, "%s%s", itemname, env->collect_feature_flags.char_buffer);

        }
        else
        {
            /* No feature flag */
            html_table_dat(env, 0, 0, 0, 0, itemname);
        }

        html_table_dat(env, 0, 0, 0, 0, format_str, entry->base.id);
        html_table_dat(env, 1, 0, 0, 0, "<nobr>%s</nobr>", entry->bit_pattern);
        html_table_com(env, entry->base.cmt_list);
        html_table_row_end(env);

        entry = (autogen_bittbl_entry*)autogen_obj_find_next_in_list(&entry_it);
    }

    fprintf(env->fhtml, "</table>\n");

    if (env->collect_feature_flags.head)
    {
        /* Dump list of collected feature flags */
        html_print_feature_flag_lst(env);
    }
    fprintf(env->fhtml, "<br>\n");

    html_print_rel(env, (autogen_obj*)tbl, "table");

    fprintf(env->fhtml, "<br>\n");
}


/*  Builds a limits string base of a value limits definition. If the limits
    contains constants, references are made to the Constants section
*/
LOCAL const char* html_build_limits(html_environment* env, const autogen_obj* limit_obj, const autogen_ver* ver, const autogen_pres* pres)
{
    char* str_limits = NULL;
    const char* str_min_name = "";
    const char* str_max_name = "";
    char* str_unit = "";
    char* str_min_unit = "";
    char* str_max_unit = "";
    char* str_exc_names = "";
    const autogen_prop *minprop = prop_find_first(limit_obj, PROPERTY_ITEM_MINIMUM_VALUE);
    const autogen_prop *maxprop = prop_find_first(limit_obj, PROPERTY_ITEM_MAXIMUM_VALUE);
    const autogen_prop *exprop = NULL;
    unsigned int exsize = 1;
    int use_seperator = TRUE;


    if (pres && pres->unit && pres->unit[0] && 
        !(pres->type & (AUTOGEN_PRESENTATION_QN | AUTOGEN_PRESENTATION_LINEAR)))
    {
        str_unit = (char*)pmd_heap_alloc_h(env->heap_handle, 6 + strlen(pres->unit));
        if (!strcmp(pres->unit, "%"))
        {
            sprintf(str_unit, " %s", "&#37;"); /* %% doesn't work in Linux, it seems */
        }
        else
        {
            sprintf(str_unit, " %s", pres->unit);
        }
    }


    /* can references to the constant section be made ? */

    if (maxprop)
    {
        str_max_name = html_const_link(env, maxprop->str, ver);
        if (isdigit(str_max_name[0]) || str_max_name[0] == '-')
            str_max_unit = str_unit;
        use_seperator = TRUE;
    }
    if (minprop)
    {
        str_min_name = html_const_link(env, minprop->str, ver);
        if (isdigit(str_min_name[0]) || str_min_name[0] == '-')
            str_min_unit = str_unit;
        use_seperator = TRUE;
    }

    /* Write the exceptional values to str_exc_names */
    exprop = prop_find_first(limit_obj, PROPERTY_ITEM_EXCEPTIONAL_VALUE);
    while (exprop)
    {
        const char* str = exprop->str;
        const char* link = html_const_link(env, str, ver);

        if (exsize < (strlen(str_exc_names) + strlen(link) + 10))
        {
            char* new_str;

            exsize += strlen(str_exc_names) + strlen(link) + 10;
            new_str = (char*)pmd_heap_alloc_h(env->heap_handle, exsize);

            strcpy(new_str, str_exc_names);
            str_exc_names = new_str;
        }

        exprop = prop_find_next(exprop);

        if (use_seperator)
        {
            strcat(str_exc_names, exprop ? ", " : " or ");
        }
        strcat(str_exc_names, link);

        use_seperator = TRUE;
    }

    str_limits = (char*)pmd_heap_alloc_h(env->heap_handle, 30 + 2*strlen(str_unit) + strlen(str_exc_names) + strlen(str_min_name) + strlen(str_max_name));

    if (minprop && !maxprop)
    {
        sprintf(str_limits, "Value range: >= %s%s%s", str_min_name, str_min_unit, str_exc_names);
    }
    else if (maxprop && !minprop)
    {
        sprintf(str_limits, "Value range: <= %s%s%s", str_max_name, str_max_unit, str_exc_names);
    }
    else if (minprop && maxprop)
    {
        if (minprop->value == maxprop->value)
        {
            sprintf(str_limits, "Possible value: %s%s%s", str_min_name, str_unit, str_exc_names);
        }
        else if (maxprop->value - minprop->value == 1)
        {
            sprintf(str_limits, "Possible values: %s%s, %s%s%s", str_min_name, str_min_unit, str_max_name, str_max_unit, str_exc_names);
        }
        else
        {
            sprintf(str_limits, "Value range: %s%s to %s%s%s", str_min_name, str_min_unit, str_max_name, str_max_unit, str_exc_names);
        }
    }
    else if (prop_has(limit_obj, PROPERTY_ITEM_EXCEPTIONAL_VALUE))
    {
        if (str_unit[0])
        {
            sprintf(str_limits, "Value range: any value (in%s)%s", str_unit, str_exc_names);
        }
        else
        {
            sprintf(str_limits, "Value range: any value %s", str_exc_names);
        }
    }


    return str_limits;
}

/*  Generates the HTML output for the ChoiceBegin sequence item pointed to by 
    'p_item'
*/
LOCAL void html_item_choice(html_environment* env, autogen_item_choice* choice)
{
	int has_section = FALSE;
	int old_should_print = env->print_varname;
	autogen_obj* def_case;
	autogen_obj* case_item = NULL;
	autogen_it case_it = INIT_ITERATOR;

	case_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    /* Print feature flag of choice structure */
    if (choice->base.base.feature_flags)
    {
        /* Print out feature flag for choice */
        html_table_row(env, 0);
        fprintf(env->fhtml, "<td valign=\"top\" colspan=4>");
        html_print_feature_flag(env, "<b>Choice feature flag:</b>", choice->base.base.feature_flags); 
        fprintf(env->fhtml, "</td>");
        html_table_row_end(env);
    }

    case_item = autogen_obj_find_in_list(&case_it, &choice->base.base.child_list);
	while (case_item)
	{
		int incl_ver = FALSE;
		char* cond_text;
		unsigned int size = 25 + strlen(case_item->name);
		if (choice->base.refname)
		{
			size += strlen(choice->base.refname);
		}

		cond_text = (char*)pmd_heap_alloc_h(env->heap_handle, size);

		if (choice->base.base.flag & AUTOGEN_CHOICE_FORWARD)
		{
			sprintf(cond_text, "<b>%s</b>", case_item->name);
		}
		else
		{
			if (choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_BITMASK)
			{
				sprintf(cond_text, "<b>%s</b> & <b>%s</b>", choice->base.refname, case_item->name);
			}
			else
			{
				const char* str_ref = html_generate_reference_text(env, &choice->base);

				sprintf(cond_text, "%s = <b>%s</b>", str_ref, case_item->name);
			}
		}

		incl_ver = !autogen_obj_ver_is_exact(&case_item->ver, &case_item->parent->ver);

		html_table_section_start(env, !has_section, 
			"%s %s, the following element(s) are to be inserted%s%s%s", 
			has_section ? "Else if" : "If", cond_text,
			incl_ver ? " <b>" : "",
			incl_ver ? html_obj_ver_string(&case_item->ver) : "",
			incl_ver ? "</b>" : "");

		env->print_varname = FALSE;

        html_seq_items(env, &case_item->child_list);

		has_section = TRUE;

        case_item = autogen_obj_find_next_in_list(&case_it);
	}

	/* Default item */
    def_case = (autogen_obj*)choice->default_case;
	if (def_case && !(def_case->flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML))
	{
		if (has_section)
		{
			html_table_section_start(env, FALSE, "Else, the following element(s) are to be inserted");
		}

		env->print_varname = old_should_print;

		html_seq_items(env, &def_case->child_list);
	}

	if (has_section)
	{
		if (choice->base.base.next)
		{
			html_table_section_end(env, "&nbsp;");
		}
		else
		{
			--env->section_index;
		}
	}

	/* restore flag */
	env->print_varname = old_should_print;
}


/*  Generates the HTML output for the constant table pointed to 
    by 'const_tbl' 
*/

LOCAL void html_const_tbl(html_environment* env, autogen_tbl* tbl)
{
    autogen_it entry_it = INIT_ITERATOR;
    autogen_obj* entry;
    char format_str[80];

    entry_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    html_ver_info(env, (autogen_obj*)tbl);

    html_comment(env, tbl->base.cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);

    if (tbl->base.feature_flags)
    {
        /* Print out feature flag */
        html_print_feature_flag(env, "<b>Feature flag:</b>", tbl->base.feature_flags);
    }

    html_table(env);
    html_table_row(env, TRUE);
    html_table_dat(env, 0, 0, 1, 0, "Symbol ID");
    html_table_dat(env, 0, 0, 1, 0, "Value");
    html_table_dat(env, 0, 0, 1, 0, "Comment");
    html_table_row_end(env);


    if (tbl->length > 0)
    {
        int nchar = 2;

        if (tbl->length > 8 && tbl->length <= 16)
        {
            nchar = 4;
        }
        else if (tbl->length > 16 && tbl->length <= 32)
        {
            nchar = 8;
        }
        else if (tbl->length > 32)
        {
            nchar = 16;
        }

#if (PMD_FILE_FORMAT >= 600)
        sprintf(format_str, "0x%%%d.%dllX", nchar, nchar);
#else
        sprintf(format_str, "0x%%%d.%dX", nchar, nchar);
#endif
    }
    else
    {
#if (PMD_FILE_FORMAT >= 600)
        sprintf(format_str, "%%lld");
#else
        sprintf(format_str, "%%d");
#endif
    }

    entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
    while (entry)
    {
        char* entryname = (char*)pmd_heap_alloc_h(env->heap_handle, 25 + strlen(entry->name));

        html_table_row(env, FALSE);

        strcpy(entryname, entry->name);

        if (!autogen_obj_ver_is_exact(&entry->ver, &tbl->base.ver))
        {
            strcat(entryname, " ");
            strcat(entryname, html_obj_ver_string(&entry->ver));
        }

        /* Check for presence of feature flag */
        if (entry->feature_flags)
        {
            /* Feature flags present */
            html_add_featureflag_lst(env, entry->feature_flags, env->collect_feature_flags.char_buffer);
            html_table_dat(env, 0, 0, 0, 0, "%s%s", entryname, env->collect_feature_flags.char_buffer);

        }
        else
        {
            /* No feature flag */
            html_table_dat(env, 0, 0, 0, 0, entryname);
        }

        if (tbl->length < 0)
        {
#if (PMD_FILE_FORMAT >= 600)
            html_table_dat(env, 0, 0, 0, 0, format_str, (long long)entry->id);
#else
            html_table_dat(env, 0, 0, 0, 0, format_str, (int)entry->id);
#endif
        }
        else
        {
            html_table_dat(env, 0, 0, 0, 0, format_str, entry->id);
        }

        html_table_com(env, entry->cmt_list);
        html_table_row_end(env);

        entry = autogen_obj_find_next_in_list(&entry_it);
    }

    fprintf(env->fhtml, "</table>\n");
    
    if (env->collect_feature_flags.head)
    {
        /* Dump list of collected feature flags */
        html_print_feature_flag_lst(env);
    }
    fprintf(env->fhtml, "<br>\n");

    html_print_rel(env, (autogen_obj*)tbl, "table");

    fprintf(env->fhtml, "<br>\n");
}



/*  Generates the HTML output for the Filler sequence item pointed to by 'item' */
LOCAL void html_item_filler(html_environment* env, autogen_item* item)
{
    html_table_row(env, FALSE);

    if (item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
    {
        char str_alignment[50] = "-";
        unsigned int filler_mask = item->base.flag & AUTOGEN_FILLER_0_TO_3_BYTES;
        int show_in_bits = prop_has((autogen_obj*)env->res, PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS);

        switch (filler_mask)
        {
        case AUTOGEN_FILLER_0_BYTES_POSSIBLE:
            {
                strcpy(str_alignment, "0");
            }
            break;

        case AUTOGEN_FILLER_1_BYTES_POSSIBLE:
            {
                strcpy(str_alignment, show_in_bits ? "8":"1");
            }
            break;

        case AUTOGEN_FILLER_2_BYTES_POSSIBLE:
            {
                strcpy(str_alignment, show_in_bits ? "16":"2");
            }
            break;

        case AUTOGEN_FILLER_3_BYTES_POSSIBLE:
            {
                strcpy(str_alignment, show_in_bits ? "24":"3");
            }
            break;

#if (PMD_FILE_FORMAT >= 600)
        case AUTOGEN_FILLER_4_BYTES_POSSIBLE:
            {
                strcpy(str_alignment, show_in_bits ? "32":"4");
            }
            break;

        case AUTOGEN_FILLER_5_BYTES_POSSIBLE:
            {
                strcpy(str_alignment, show_in_bits ? "40":"5");
            }
            break;

        case AUTOGEN_FILLER_6_BYTES_POSSIBLE:
            {
                strcpy(str_alignment, show_in_bits ? "48":"6");
            }
            break;

        case AUTOGEN_FILLER_7_BYTES_POSSIBLE:
            {
                strcpy(str_alignment, show_in_bits ? "56":"7");
            }
            break;
#endif
        case AUTOGEN_FILLER_0_OR_1_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 or 8":"0 or 1");
            }
            break;

        case AUTOGEN_FILLER_0_OR_2_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 or 16":"0 or 2");
            }
            break;

        case AUTOGEN_FILLER_0_OR_3_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 or 24":"0 or 3");
            }
            break;

        case AUTOGEN_FILLER_1_OR_2_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "8 or 16":"1 or 2");
            }
            break;

        case AUTOGEN_FILLER_1_OR_3_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "8 or 24":"1 or 3");
            }
            break;

        case AUTOGEN_FILLER_1_TO_3_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "8 to 24":"1 to 3");
            }
            break;

        case AUTOGEN_FILLER_0_TO_2_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 to 16":"0 to 2");
            }
            break;

        case AUTOGEN_FILLER_0_TO_3_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 to 24":"0 to 3");
            }
            break;

#if (PMD_FILE_FORMAT >= 600)
        case AUTOGEN_FILLER_0_OR_2_OR_4_OR_6_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0, 16, 32 or 48":"0, 2, 4 or 6");
            }
            break;
        case AUTOGEN_FILLER_1_OR_3_OR_5_OR_7_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "8, 24, 40 or 56":"1, 3, 5 or 7");
            }
            break;
        case AUTOGEN_FILLER_0_OR_4_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 or 32":"0 or 4");
            }
            break;
        case AUTOGEN_FILLER_0_TO_4_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 to 32":"0 to 4");
            }
            break;
        case AUTOGEN_FILLER_0_TO_5_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 to 40":"0 to 5");
            }
            break;
        case AUTOGEN_FILLER_0_TO_6_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 to 48":"0 to 6");
            }
            break;
        case AUTOGEN_FILLER_0_TO_7_BYTES:
            {
                strcpy(str_alignment, show_in_bits ? "0 to 56":"0 to 7");
            }
            break;
#endif
        }

        html_table_dat(env, 0, 0, 0, 0, str_alignment);
    }
    else
    {
        html_table_size(env, item);
    }

    html_table_par(env, item);
    html_table_var(env, item);
    html_table_com(env, item->base.cmt_list);

    html_table_row_end(env);
}


/*  Generates the HTML output for the FTD Data table pointed to by 'tbl' */
LOCAL void html_ftd_tbl(html_environment* env, autogen_tbl* tbl)
{
    autogen_it ftd_it = INIT_ITERATOR;
    autogen_data* ftd;

    ftd_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    html_ver_info(env, (autogen_obj*)tbl);

    html_comment(env, tbl->base.cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);

    if (tbl->base.feature_flags)
    {
        /* Print out feature flag */
        html_print_feature_flag(env, "<b>Feature flag:</b>", tbl->base.feature_flags);
    }

    html_table(env);
    html_table_row(env, TRUE);
    html_table_dat(env, 0, 0, 1, 0, "FTD Data name");
    html_table_dat(env, 0, 0, 1, 0, "ID");
    html_table_dat(env, 0, 0, 1, 0, "Supported in modes");
    html_table_dat(env, 0, 0, 1, 0, "Subblock template");
    html_table_row_end(env);

    ftd_it.typemask = AUTOGEN_OBJ_DATA;

    ftd = (autogen_data*)autogen_obj_find_in_list(&ftd_it, &tbl->base.child_list);
    while (ftd)
    {
        char mode_str[100] = "";
#if (PMD_FILE_FORMAT >= 600)
        unsigned long long mode;
#else
        unsigned int mode;
#endif

        char* ftdname = (char*)pmd_heap_alloc_h(env->heap_handle, 25 + strlen(ftd->base.name));

        html_table_row(env, FALSE);

        strcpy(ftdname, ftd->base.name);

        if (!autogen_obj_ver_is_exact(&ftd->base.ver, &tbl->base.ver))
        {
            strcat(ftdname, " ");
            strcat(ftdname, html_obj_ver_string(&ftd->base.ver));
        }

        fprintf(env->fhtml, "  <td valign=\"top\"><a href=\"%s\">%s</a></td>\n", 
            html_obj_link(env, &ftd->base, NULL), ftdname);

#if (PMD_FILE_FORMAT >= 600)
        html_table_dat(env, 0, 0, 0, 0, "0x%4.4llX", ftd->base.id);
#else
        html_table_dat(env, 0, 0, 0, 0, "0x%4.4X", ftd->base.id);
#endif

        mode = prop_get_value_default(&ftd->base, PROPERTY_FTD_SUPPORTED_MODES, 0);
        if (mode & FTD_MODE_RD)
        {
            strcpy(mode_str, "R&D");
        }
        if (mode & FTD_MODE_INFRA)
        {
            if (mode_str[0]) strcat(mode_str, ", ");
            strcat(mode_str, "Infra vendor");
        }
        if (mode & FTD_MODE_OPERATOR)
        {
            if (mode_str[0]) strcat(mode_str, ", ");
            strcat(mode_str, "Operator");
        }
        if (!mode_str[0])
        {
            strcpy(mode_str, "?");
        }

        html_table_dat(env, 0, 0, 0, 0, mode_str);

        /* print the template subblock name */
        if (ftd->base.flag & AUTOGEN_DATA_FTD_IS_INPUT_DATA)
        {
            fprintf(env->fhtml, "  <td valign=\"top\">Data is input data</td>");
        }
        else
        {
            fprintf(env->fhtml, "  <td valign=\"top\">%s", ftd->seqname);

            /* print the type of table */
            if ((ftd->base.flag & AUTOGEN_DATA_TABLE) && abs(ftd->length) == 8)
            {
                fprintf(env->fhtml, " (BYTES)");
            }
            else if ((ftd->base.flag & AUTOGEN_DATA_TABLE) && abs(ftd->length) == 16)
            {
                fprintf(env->fhtml, " (WORDS)");
            }
            else if ((ftd->base.flag & AUTOGEN_DATA_TABLE) && abs(ftd->length) == 32)
            {
                fprintf(env->fhtml, " (DWORDS)");
            }

            fprintf(env->fhtml, "</td>\n");
        }

        html_table_row_end(env);

        ftd = (autogen_data*)autogen_obj_find_next_in_list(&ftd_it);
    }

    fprintf(env->fhtml, "</table><br>\n");

    html_print_rel(env, (autogen_obj*)tbl, "table");

    fprintf(env->fhtml, "<br>\n");
}

/*  Generates the HTML output for the FTD Data pointed to by 'ftd' */
LOCAL void html_ftd(html_environment* env, autogen_data* ftd)
{
    html_ver_info(env, (autogen_obj*)ftd);

    html_comment(env, ftd->base.cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);

    if (ftd->base.flag & AUTOGEN_DATA_STRING)
    {
        if (prop_has(&ftd->base, PROPERTY_FTD_STRING_MAXIMUM_LENGTH))
        {
            fprintf(env->fhtml, "String length: ");
            if (prop_has(&ftd->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH))
            {
                fprintf(env->fhtml, html_const_link(env, prop_get_string(&ftd->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH), &ftd->base.ver));
            }
            else
            {
                fprintf(env->fhtml, "0");
            }

            fprintf(env->fhtml, " to ");
            fprintf(env->fhtml, html_const_link(env, prop_get_string(&ftd->base, PROPERTY_FTD_STRING_MAXIMUM_LENGTH), &ftd->base.ver));
        }
        else if (prop_has(&ftd->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH))
        {
            fprintf(env->fhtml, "Minimum string length: ");
            fprintf(env->fhtml, html_const_link(env, prop_get_string(&ftd->base, PROPERTY_FTD_STRING_MINIMUM_LENGTH), &ftd->base.ver));
        }
    }
    else
    {
        /* print the sequence table header */
        html_table(env);
        html_table_row(env, TRUE);
        if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS))
        {	
            html_table_dat(env, 0, 0, 1, 10, "Size in bits");
        }
        else
        {	
            html_table_dat(env, 0, 0, 1, 10, "Size in bytes");
        }	
        html_table_dat(env, 0, 0, 1, 30, "Parameter");

        if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_VARNAME_COLUMN))
        {
            html_table_dat(env, 0, 0, 1, 20, "Variable");
        }

        html_table_dat(env, 0, 0, 1, 40, "Description");
        html_table_row_end(env);

        /* print the ftd fields */
        html_seq_items(env, &ftd->base.child_list);

        /* end the ftd table */
        fprintf(env->fhtml, "</table><br>\n");
    }

    fprintf(env->fhtml, "<br>\n");
}

/*  Generates the HTML output for the merge sequence item pointed 
    to by 'p_item' */
LOCAL void html_item_merge(html_environment* env, autogen_item* item)
{
    html_table_row(env, FALSE);

    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);
    html_table_com(env, item->base.cmt_list);
    html_table_row_end(env);

    html_seq_items(env, &item->base.child_list);
}


/*  Generates the HTML output for the Message pointed to by 'seq' */
LOCAL void html_msg(html_environment* env, autogen_seq* seq, int is_toc)
{
    autogen_obj* rel;
    int show_in_bits = prop_has((autogen_obj*)env->res, PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS);
    autogen_it rel_it = INIT_ITERATOR;

    if (is_toc)
    {
        return;
    }

    if (seq->base.flag & AUTOGEN_OBJ_IS_LEGACY)
    {
        return;
    }

    if (seq->base.type == AUTOGEN_OBJ_MSG && seq->base.child_list.n_obj > 0)
    {
        html_ver_info(env, (autogen_obj*)seq);
    }

    rel_it.typemask    = AUTOGEN_OBJ_REL;
    rel_it.subtypemask = AUTOGEN_OBJ_MSG;
    rel_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;
    rel_it.sort_type   = AUTOGEN_OBJ_LIST_SORT_BY_TYPE_AND_NAME;

    rel = autogen_obj_find_in_list(&rel_it, &seq->base.related_obj);
    if (rel)
    {
        if (seq->base.flag & AUTOGEN_MSG_REQ)
        {
            fprintf(env->fhtml,
                "<font size=\"2\">"
                "Request message. Corresponding response message(s):<br>\n");
        }
        else if (seq->base.flag & AUTOGEN_MSG_RESP)
        {
            fprintf(env->fhtml,
                "<font size=\"2\">"
                "Response message to request message(s):<br>\n");
        }

        while (rel)
        {
            autogen_seq* msg = (autogen_seq*)rel->ptr;
            autogen_obj_list* msg_list = &msg->base.res->msg_list;

            if (msg->base.flag & AUTOGEN_MSG_IS_SUBMSG)
            {
                msg_list = &((autogen_seq*)msg->base.base_obj)->submsg_list;
            }

            /* Any feature flags on message pair */
            env->collect_feature_flags.char_buffer[0] = '\0';
            if (rel->feature_flags)
            {
                /* Save feature flag in list */
                html_add_featureflag_lst(env, rel->feature_flags, env->collect_feature_flags.char_buffer);
            }

            /* Is related message in same resource? */
            if (msg->base.res == seq->base.res)
            {
                fprintf(env->fhtml, " &nbsp;<a href=\"%s\">%s</a>%s<br>\n",
                    html_obj_link(env, (autogen_obj*)msg, NULL),
                    html_obj_ver_pres(env, (autogen_obj*)msg, msg_list, &rel->ver, NULL),
                    env->collect_feature_flags.char_buffer);
            }
            else
            {
                fprintf(env->fhtml, " &nbsp;<a href=\"%s\">%s</a>%s<br>\n",
                    html_obj_link(env, (autogen_obj*)msg, msg->base.res),
                    html_obj_ver_pres(env, (autogen_obj*)msg, msg_list, &rel->ver, NULL),
                    env->collect_feature_flags.char_buffer);
            }

            rel = autogen_obj_find_next_in_list(&rel_it);
        }

        /* Print out list of feature flags if any */
        if (env->collect_feature_flags.head)
        {
            /* Dump list of collected feature flags */
            fprintf(env->fhtml, "<br>\n");
            html_print_feature_flag_lst(env);
        }

        fprintf(env->fhtml, "</font><br>\n");
    }

    html_comment(env, seq->base.cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);

    if (seq->base.feature_flags)
    {
        /* Print out feature flag */
        html_print_feature_flag(env, "<b>Feature flag:</b>", seq->base.feature_flags);
    }

    if (seq->base.type != AUTOGEN_OBJ_MSG_BASE && seq->base.child_list.n_obj > 0)
    {
        html_table(env);

        html_table_row(env, TRUE);
        if (show_in_bits)
        {	
            html_table_dat(env, 0, 0, 1, 10, "Size in bits");
        }
        else
        {	
            html_table_dat(env, 0, 0, 1, 10, "Size in bytes");
        }	
        html_table_dat(env, 0, 0, 1, 30, "Parameter");
        if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_VARNAME_COLUMN))
        {
            html_table_dat(env, 0, 0, 1, 20, "Variable");
        }
        html_table_dat(env, 0, 0, 1, 40, "Description");
        html_table_row_end(env);

        /* add phonet header fields */
        if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_PHONET_HEADER) &&
            env->res->base.subtype != RESOURCE_SYMBOLS &&
            !(env->res->base.subtype & RESOURCE_TRC_ANY))
        {
            fprintf(env->fhtml, " <tr bgcolor=\"#e0e0e0\">");
            html_table_dat(env, 0, 1, 0, 0, show_in_bits ? "24":"3");
            html_table_dat(env, 0, 1, 0, 0, "Message header info");
            if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_VARNAME_COLUMN))
            {
                html_table_dat(env, 0, 1, 0, 0, "-");
            }
            html_table_dat(env, 0, 1, 0, 0, "As in the PhoNet header");
            html_table_row_end(env);

            html_table_row(env, FALSE);
            html_table_dat(env, 0, 0, 0, 0, show_in_bits ? "8":"1");
            html_table_dat(env, 0, 0, 0, 0, "Resource");
            if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_VARNAME_COLUMN))
            {
                if (prop_get_value_default((autogen_obj*)env->res, PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT, 0) == 0)
                {
                    html_table_dat(env, 0, 0, 0, 0, "res");
                }
                else if (prop_get_value((autogen_obj*)env->res, PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT) == 1)
                {
                    html_table_dat(env, 0, 0, 0, 0, "function");
                }
                else
                {
                    html_table_dat(env, 0, 0, 0, 0, "resource");
                }
            }

            if (env->res->base.subtype == RESOURCE_MEDIA_MODULE ||
                env->res->base.subtype == RESOURCE_MEDIA_MODULE_EXTENSION)
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>PN_MEDIA_CONTROL</i>");
            }
            else if (env->res->base.subtype == RESOURCE_ISI_PREFIX ||
                     env->res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT)
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>PN_PREFIX</i>");
            }
            else if (env->res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES)
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>%s</i>", seq->base.res->base.name);
            }
            else
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>RESOURCE_ID of the actual server</i>");
            }

            html_table_row_end(env);

            fprintf(env->fhtml, " <tr bgcolor=\"#e0e0e0\">");

            html_table_dat(env, 0, 1, 0, 0, show_in_bits ? "32":"4");
            html_table_dat(env, 0, 1, 0, 0, "Message header info");
            if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_VARNAME_COLUMN))
            {
                html_table_dat(env, 0, 1, 0, 0, "-");
            }
            html_table_dat(env, 0, 1, 0, 0, "As in the PhoNet header");
            html_table_row_end(env);
        }

        /* If media module specific message, dump the elements of the media controller carrier message */
        if ((env->res->base.subtype == RESOURCE_MEDIA_MODULE || 
            env->res->base.subtype == RESOURCE_MEDIA_MODULE_EXTENSION))
        {
            autogen_res* mctrlres = util_get_unique_res(RESOURCE_ISI_MEDIA_CONTROL);
            if (mctrlres)
            {
                unsigned int namelen = strlen(seq->base.parent->name);
                unsigned int maxlen  = namelen;
                if (namelen > 16)
                    maxlen = 16;
                /* Only dump it if not media controller */
                if ((namelen != 16)||(strncmp(seq->base.parent->name, "PN_MEDIA_CONTROL", maxlen)))
                {
                    autogen_it msg_it = INIT_ITERATOR;
                    autogen_seq* msg = NULL;

                    msg_it.typemask = AUTOGEN_OBJ_MSG;
                    msg_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;
                    msg_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                    msg_it.ver      = &mctrlres->base.ver;

                    if (seq->base.flag & AUTOGEN_MSG_REQ)
                    {
                        msg_it.obj.name = "PNS_MEDIA_SPECIFIC_REQ";
                    }
                    else if (seq->base.flag & AUTOGEN_MSG_RESP)
                    {
                        msg_it.obj.name = "PNS_MEDIA_SPECIFIC_RESP";
                    }
                    else if (seq->base.flag & AUTOGEN_MSG_NTF)
                    {
                        msg_it.obj.name = "PNS_MEDIA_SPECIFIC_NTF";
                    }
                    else if (seq->base.flag & AUTOGEN_MSG_IND)
                    {
                        msg_it.obj.name = "PNS_MEDIA_IND";
                    }

                    msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, &mctrlres->msg_list);
                    if (msg)
                    {
                        html_seq_items(env, &msg->base.child_list); 
                    }
                }
            }
        }

        html_seq_items(env, &seq->base.child_list);

        fprintf(env->fhtml, "</table>");

        if (env->collect_feature_flags.head)
        {
            /* Dump list of collected feature flags */
            html_print_feature_flag_lst(env);
        }
        fprintf(env->fhtml, "<br>");
    }
}


/*  Generates the HTML output for the PPC table pointed to by 'tbl' */
LOCAL void html_ppc_tbl(html_environment* env, autogen_tbl* tbl)
{
    autogen_it ppc_it = INIT_ITERATOR;
    autogen_data* ppc;

    html_ver_info(env, (autogen_obj*)tbl);

    html_comment(env, tbl->base.cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);

    if (tbl->base.feature_flags)
    {
        /* Print out feature flag */
        html_print_feature_flag(env, "<b>Feature flag:</b>", tbl->base.feature_flags);
    }

    html_table(env);
    html_table_row(env, TRUE);
    html_table_dat(env, 0, 0, 1, 0, "PPC Name");
    html_table_dat(env, 0, 0, 1, 0, "ID");
    html_table_dat(env, 0, 0, 1, 0, "Template subblock");
    html_table_row_end(env);

    ppc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    ppc = (autogen_data*)autogen_obj_find_in_list(&ppc_it, &tbl->base.child_list);
    while (ppc)
    {
        autogen_it seq_it = INIT_ITERATOR;
        autogen_obj* seq;

        char* ppcname = (char*)pmd_heap_alloc_h(env->heap_handle, 25 + strlen(ppc->base.name));

        seq_it.typemask = AUTOGEN_OBJ_SB_TEMPLATE;
        seq_it.obj.name = ppc->seqname;

        seq = autogen_obj_find_in_list(&seq_it, &env->res->seq_list);

        html_table_row(env, FALSE);

        strcpy(ppcname, ppc->base.name);

        if (!autogen_obj_ver_is_exact(&ppc->base.ver, &tbl->base.ver))
        {
            strcat(ppcname, " ");
            strcat(ppcname, html_obj_ver_string(&ppc->base.ver));
        }

        html_table_dat(env, 0, 0, 0, 0, ppcname);
#if (PMD_FILE_FORMAT >= 600)
        html_table_dat(env, 0, 0, 0, 0, "0x%4.4llX", ppc->base.id);
#else
        html_table_dat(env, 0, 0, 0, 0, "0x%4.4X", ppc->base.id);
#endif
        html_table_ref(env, 
            html_obj_link(env, seq, NULL), 
            util_get_obj_name(seq), ppc->base.cmt_list, NULL);

        html_table_row_end(env);

        ppc = (autogen_data*)autogen_obj_find_next_in_list(&ppc_it);
    }

    fprintf(env->fhtml, "</table><br>\n");

    html_print_rel(env, (autogen_obj*)tbl, "table");

    fprintf(env->fhtml, "<br>\n");
}


/*  Prints a list of messages, subblocks or sequences, referring to 'obj' */
LOCAL void html_print_rel(html_environment* env, autogen_obj* obj, const char* objtypestr)
{
    int first = TRUE;
    autogen_obj* rel;
    autogen_it rel_it = INIT_ITERATOR;

    rel_it.typemask    = AUTOGEN_OBJ_REL;
    rel_it.subtypemask = AUTOGEN_OBJ_MSG;
    rel_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;
    rel_it.sort_type   = AUTOGEN_OBJ_LIST_SORT_BY_TYPE_AND_NAME;

    rel = autogen_obj_find_in_list(&rel_it, &obj->related_obj);
    if (rel)
    {
        fprintf(env->fhtml, 
            "<font size=\"2\">"
            "The %s is referred to from the following objects:<br>\n", objtypestr);

        while (rel)
        {
            autogen_obj* msg = (autogen_obj*)rel->ptr;

            fprintf(env->fhtml, " &nbsp;<a href=\"%s\">%s</a><br>\n", 
                html_obj_link(env, msg, NULL),
                html_obj_ver_pres(env, msg, &env->res->msg_list, &msg->ver, NULL));

            rel = autogen_obj_find_next_in_list(&rel_it);
        }

        fprintf(env->fhtml, "</font><br>\n");

        first = FALSE;
    }

    /* related sequences */
    rel_it.typemask    = AUTOGEN_OBJ_REL;
    rel_it.subtypemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SB_TEMPLATE;
    rel_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;
    rel_it.sort_type   = AUTOGEN_OBJ_LIST_SORT_BY_TYPE_AND_NAME;

    rel = autogen_obj_find_in_list(&rel_it, &obj->related_obj);
    if (rel)
    {
        if (first)
        {
            fprintf(env->fhtml, 
                "<font size=\"2\">"
                "The %s is referred to from the following objects:<br>\n", objtypestr);
        }

        while (rel)
        {
            autogen_obj* seq = (autogen_obj*)rel->ptr;

            fprintf(env->fhtml, " &nbsp;<a href=\"%s\">%s</a><br>\n", 
                html_obj_link(env, seq, NULL),
                html_obj_ver_pres(env, seq, &env->res->seq_list, &seq->ver, NULL));

            rel = autogen_obj_find_next_in_list(&rel_it);
        }

        if (first)
        {
            fprintf(env->fhtml, "</font><br>\n");
        }
    }
}


/*  Generates the HTML output for the Reference sequence item pointed to by 
    'item'
*/

LOCAL void html_item_ref(html_environment* env, autogen_item* item)
{
    autogen_item_value* item_val = (autogen_item_value*)item;
    autogen_seq* seq = (autogen_seq*)item->seq;
    const char* str_limits = pmd_heap_strdup_h(env->heap_handle, "");


    if (prop_has((autogen_obj*)item, PROPERTY_ITEM_MINIMUM_VALUE) ||
        prop_has((autogen_obj*)item, PROPERTY_ITEM_MAXIMUM_VALUE) ||
        prop_has((autogen_obj*)item, PROPERTY_ITEM_EXCEPTIONAL_VALUE))
    {
        autogen_item_value* item_value = (autogen_item_value*)item;

        str_limits = html_build_limits(env, &item_value->base.base, &item->base.ver, &item_value->pres);
    }

    html_table_row(env, FALSE);

    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);

    fprintf(env->fhtml, "  <td valign=\"top\">");

    if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE ||
        item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH)
    {
        fprintf(env->fhtml, "Reference name: <b>%s</b>", item->base.name);
    }
    else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID)
    {
        if (item->length == 16)
        {
#if (PMD_FILE_FORMAT >= 600)
            fprintf(env->fhtml, "<i>%s (= 0x%4.4llX)</i>", seq->base.base_obj->name, seq->base.base_obj->id);
#else
            fprintf(env->fhtml, "<i>%s (= 0x%4.4X)</i>", seq->base.base_obj->name, seq->base.base_obj->id);
#endif
        }
        else
        {
#if (PMD_FILE_FORMAT >= 600)
            fprintf(env->fhtml, "<i>%s (= 0x%2.2llX)</i>", seq->base.base_obj->name, seq->base.base_obj->id);
#else
            fprintf(env->fhtml, "<i>%s (= 0x%2.2X)</i>", seq->base.base_obj->name, seq->base.base_obj->id);
#endif
        }
    }
    else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID)
    {
        if (item->length == 16)
        {
#if (PMD_FILE_FORMAT >= 600)
            fprintf(env->fhtml, "<i>%s (= 0x%4.4llX)</i>", seq->base.name, seq->base.id);
#else
            fprintf(env->fhtml, "<i>%s (= 0x%4.4X)</i>", seq->base.name, seq->base.id);
#endif
        }
        else
        {
#if (PMD_FILE_FORMAT >= 600)
            fprintf(env->fhtml, "<i>%s (= 0x%2.2llX)</i>", seq->base.name, seq->base.id);
#else
            fprintf(env->fhtml, "<i>%s (= 0x%2.2X)</i>", seq->base.name, seq->base.id);
#endif
        }
    }
    else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID)
    {
        if (seq->base.type == AUTOGEN_OBJ_SB_TEMPLATE)
        {
            if (seq->base.subtype == AUTOGEN_SB_TEMPLATE_FTD)
            {
                fprintf(env->fhtml, "<i>COMM_FTD_DATA_*</i>");
            }
            else if (seq->base.subtype == AUTOGEN_SB_TEMPLATE_SOS) /* Symbian */
            {
                fprintf(env->fhtml, "<i>SOS_FTD_DATA_*</i>");
            }
            else
            {
                fprintf(env->fhtml, "<i>MON_PPC_*</i>");
            }
        }
        else
        {
            if (abs(item->length) / 8 == 2)
            {
#if (PMD_FILE_FORMAT >= 600)
                fprintf(env->fhtml, "<i>%s (= 0x%4.4llX)</i>", seq->base.name, seq->base.id);
#else
                fprintf(env->fhtml, "<i>%s (= 0x%4.4X)</i>", seq->base.name, seq->base.id);
#endif
            }
            else
            {
#if (PMD_FILE_FORMAT >= 600)
                fprintf(env->fhtml, "<i>%s (= 0x%2.2llX)</i>", seq->base.name, seq->base.id);
#else
                fprintf(env->fhtml, "<i>%s (= 0x%2.2X)</i>", seq->base.name, seq->base.id);
#endif
            }
        }
    }
    else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH ||
        item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH)
    {
        switch (seq->size.type)
        {
        case AUTOGEN_SIZE_EXACT:
            {
                if (seq->size.min == 1)
                {
                    fprintf(env->fhtml, "1 byte");
                }
                else
                {
                    fprintf(env->fhtml, "%u bytes", seq->size.min);
                }
            }
            break;

        case AUTOGEN_SIZE_INTERVAL:
            {
                fprintf(env->fhtml, "%u to %u bytes", seq->size.min, seq->size.max);
            }
            break;

        case AUTOGEN_SIZE_ASMANYASPOSSIBLE:
            {
                unsigned int minlength = seq->size.min;
#if (PMD_FILE_FORMAT >= 600)
                unsigned long long maxlength = 0;
#else
                unsigned int maxlength = 0;
#endif

                if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH)
                {
                    /* calculate the min length (must be divisible by 4) */
                    minlength = seq->size.min;
                    if (minlength % 4)
                    {
                        minlength += (4 - (minlength % 4));
                    }
                    if (prop_has((autogen_obj*)seq, PROPERTY_SB_LENGTH_LIMIT))
                    {
                        maxlength = seq->size.max;
                    }
                    else
                    {
                        const autogen_item* length_item = reference_get_special_item(&seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH);

                        /* calculate the max length (must be divisible by 4) */
#if (PMD_FILE_FORMAT >= 600)
                        maxlength  = (1LL << abs(length_item->length)) - 1;
#else
                        maxlength  = (1 << abs(length_item->length)) - 1;
#endif

                        if (!prop_has(&seq->base, PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4))
                        {
                            maxlength -= (maxlength % 4);
                        }
                    }
                }
                else
                {
                    const autogen_item* length_item = reference_get_special_item(&seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH);

                    /* calculate the max length */
                    if (prop_has(&seq->base, PROPERTY_MSG_LENGTH_LIMIT))
                    {
                        maxlength = seq->size.max;
                    }
                    else
                    {
#if (PMD_FILE_FORMAT >= 600)
                        maxlength  = (1LL << abs(length_item->length)) - 1;
#else
                        maxlength  = (1 << abs(length_item->length)) - 1;
#endif
                    }
                }

#if (PMD_FILE_FORMAT >= 600)
                fprintf(env->fhtml, "%u to %llu bytes", minlength, maxlength);
#else
                fprintf(env->fhtml, "%u to %u bytes", minlength, maxlength);
#endif
            }
            break;

        case AUTOGEN_SIZE_VERSION_DEPENDENT:
            {
                fprintf(env->fhtml, "Version dependent");
            }
            break;

        default:
            {
                fprintf(env->fhtml, "Undefined");

                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0, 
                    "Default case met in html_item_ref(). seq->size.type is 0x%8.8X",
                    seq->size.type);
            }
            break;
        }
    }
    else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_PRIVATE_ID)
    {
#if (PMD_FILE_FORMAT >= 600)
        fprintf(env->fhtml, "<i>%s (= 0x%4.4llX)</i>", seq->base.res->base.name, seq->base.res->base.id);
#else
        fprintf(env->fhtml, "<i>%s (= 0x%4.4X)</i>", seq->base.res->base.name, seq->base.res->base.id);
#endif
    }
    else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_RESOURCE_ID)
    {
        if (env->res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT)
        {
            fprintf(env->fhtml, "Type | Sub type of actual server");
        }
        else
        {
#if (PMD_FILE_FORMAT >= 600)
            fprintf(env->fhtml, "<i>%s (= 0x%4.4llX)</i>", seq->base.res->base.name, seq->base.res->base.id);
#else
            fprintf(env->fhtml, "<i>%s (= 0x%4.4X)</i>", seq->base.res->base.name, seq->base.res->base.id);
#endif
        }

    }
    else if (item->base.flag & AUTOGEN_REF_CONST)
    {
        fprintf(env->fhtml, "Reference name: <b>%s</b><br><br>", item->base.name);

        html_table_pres(env, &item_val->pres, NULL, &item->base.ver, NULL, FALSE, FALSE, 
            0, 0, item->length);
    }
    else
    {
        fprintf(env->fhtml, "&nbsp;");
    }

    /* add a value range description ? */
    if (strlen(str_limits) > 0)
    {
        fprintf(env->fhtml, "<br><br>%s", str_limits);
    }

    html_comment(env, item->base.cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);

    fprintf(env->fhtml, "</td>\n");

    html_table_row_end(env);
}


LOCAL const char* html_generate_reference_text(html_environment* env, autogen_item* item)
{
    autogen_ref* ref = reference_find(item);

    const char* str_ref = NULL;

    switch (ref->algorithm)
    {
    case PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH:
        {
            if (ref->value != 0)
            {
                char* ref_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(ref->original_name) + 20);
                str_ref = ref_str;

                if (ref->value > 0)
                {
                    sprintf(ref_str, "(<b>%s</b> + %d)", ref->original_name, ref->value);
                }
                else
                {
                    sprintf(ref_str, "(<b>%s</b> - %d)", ref->original_name, -ref->value);
                }
            }
        }
        break;

    case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MINUS_N:
        {
            char* ref_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(ref->original_name) + 20);
            str_ref = ref_str;

            sprintf(ref_str, "(%d - <b>%s</b>)", ref->value, ref->original_name);
        }
        break;

    case PMD_LENGTH_ALGORITHM_FIXEDLENGTH_MUL_N:
        {
            char* ref_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(ref->original_name) + 20);
            str_ref = ref_str;

            sprintf(ref_str, "%d*<b>%s</b>", ref->value, ref->original_name);
        }
        break;

    case PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH:
        {
            char* ref_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(ref->original_name) + 20);
            str_ref = ref_str;

            sprintf(ref_str, "<b>%s</b>/%d", ref->original_name, ref->value);
        }
        break;

    case PMD_LENGTH_ALGORITHM_N_DIV_FIXEDLENGTH_ROUNDUP:
        {
            char* ref_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(ref->original_name) + 20);
            str_ref = ref_str;

            sprintf(ref_str, "(<b>%s</b>+%d)/%d", ref->original_name, ref->value-1, ref->value);
        }
        break;

    default:
        {
        }
    }

    /* Default to just reference name */
    if (!str_ref)
    {
        char* ref_str = (char*)pmd_heap_alloc_h(env->heap_handle, strlen(ref->original_name) + 20);
        str_ref = ref_str;

        sprintf(ref_str, "<b>%s</b>", ref->original_name);
    }

    return str_ref;
}


/*  prints a new section, either in the table of contents or in the document
    itself
*/

LOCAL void html_sec(html_environment* env, int is_toc, int sec, const char* format, ...)
{
    va_list arg_list;
        
    va_start(arg_list, format);
    vsprintf(env->char_buffer, format, arg_list);
    va_end(arg_list);

    fprintf(env->fhtml, 
        "<font size=\"%d\">%s%d.&nbsp;%s%s</font><br>%s\n", 
        is_toc ? 4 : 5, is_toc ? "" : "<b>", sec, env->char_buffer, is_toc ? "" : "</b>",
        is_toc ? "" : "<br>");
}


/*  Generates the HTML output for the Sequence pointed to by 'seq' 
*/

LOCAL void html_seq(html_environment* env, autogen_seq* seq, int is_toc)
{
    if (is_toc) return;

    html_ver_info(env, (autogen_obj*)seq);

    html_comment(env, seq->base.cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);

    if (seq->base.feature_flags)
    {
        /* Print out feature flag */
        html_print_feature_flag(env, "<b>Feature flag:</b>", seq->base.feature_flags);
    }

    /* print the sequence table header */
    html_table(env);
    html_table_row(env, TRUE);
    if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS))
    {	
        html_table_dat(env, 0, 0, 1, 10, "Size in bits");
    }
    else
    {	
        html_table_dat(env, 0, 0, 1, 10, "Size in bytes");
    }	
    html_table_dat(env, 0, 0, 1, 30, "Parameter");

    if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_VARNAME_COLUMN))
    {
        html_table_dat(env, 0, 0, 1, 20, "Variable");
    }

    html_table_dat(env, 0, 0, 1, 40, "Description");
    html_table_row_end(env);

    /* print the sequence fields */
    html_seq_items(env, &seq->base.child_list);

    /* end the sequence table */
    fprintf(env->fhtml, "</table>\n");

    if (env->collect_feature_flags.head)
    {
        /* Dump list of collected feature flags */
        html_print_feature_flag_lst(env);
    }
    fprintf(env->fhtml, "<br>");

    html_print_rel(env, (autogen_obj*)seq, seq->base.type == AUTOGEN_OBJ_SB ? "subblock" : "sequence");

    fprintf(env->fhtml, "<br>\n");
}


/*  Generates the HTML output for all the sequence items in the list pointed to by 'item_list'
*/

LOCAL void html_seq_items(html_environment* env, autogen_obj_list* obj_list)
{
    autogen_it item_it = INIT_ITERATOR;
    autogen_item* item = NULL;

    item_it.typemask = AUTOGEN_OBJ_ITEM;
    item_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    item = (autogen_item*)autogen_obj_find_in_list(&item_it, obj_list);
    while (item)
    {
        if ((env->res->base.subtype != RESOURCE_MEDIA_MODULE && 
            env->res->base.subtype != RESOURCE_MEDIA_MODULE_EXTENSION) || 
            !prop_has((autogen_obj*)item, PROPERTY_PMD_ANCHOR))
        {
            switch (item->base.subtype)
            {
            case AUTOGEN_ITEM_REF:
                {
                    html_item_ref(env, item);
                }
                break;

            case AUTOGEN_ITEM_VALUE:
                {
                    html_item_value(env, item);
                }
                break;

            case AUTOGEN_ITEM_RANGE:
                {
                    html_item_range(env, item);
                }
                break;

            case AUTOGEN_ITEM_TIMESTAMP:
                {
                    html_item_timestamp(env, item);
                }
                break;

            case AUTOGEN_ITEM_POINTER:
                {
                    html_item_pointer(env, item);
                }
                break;

            case AUTOGEN_ITEM_FILLER:
                {
                    if (!(item->base.flag & AUTOGEN_FILLER_IS_REPLACED))
                    {
                        html_item_filler(env, item);
                    }
                }
                break;

            case AUTOGEN_ITEM_LST:
                {
                    html_item_lst(env, item);
                }
                break;

            case AUTOGEN_ITEM_STRING:
                {
                    html_item_string(env, item);
                }
                break;

            case AUTOGEN_ITEM_MERGE:
                {
                    html_item_merge(env, item);
                }
                break;

            case AUTOGEN_ITEM_CHOICE:
                {
                    html_item_choice(env, (autogen_item_choice*)item);
                }
                break;

            case AUTOGEN_ITEM_STRUCT:
                {
                    html_item_struct(env, item);
                }
                break;

            case AUTOGEN_ITEM_BLOCK:
                {
                    html_item_block(env, item);
                }
                break;

            case AUTOGEN_ITEM_TRCSTRUCTURE:
                {
                    html_item_trcstruct(env, item);
                }
                break;

            case AUTOGEN_ITEM_PRINTF:
                {
                    html_item_printf(env, item);
                }
                break;

            default:
                {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in html_seq_items(). item->base.subtype is 0x%8.8X", item->base.subtype);
                }
            }
        }

        item = (autogen_item*)autogen_obj_find_next_in_list(&item_it);
    }
}

LOCAL void html_generate_introduction_section(html_environment* env, int* sec1, int is_toc)
{
    if (env->res->base.cmt_list || prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_INTRODUCTION))
    {
        html_sec(env, is_toc, ++(*sec1), "Introduction");

        if (!is_toc)
        {
            if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_INTRODUCTION) && env->res->base.subtype != RESOURCE_SHARED)
            {
                autogen_obj* note;
                autogen_it note_it = INIT_ITERATOR;
                char linkname[10] = "";

                note_it.typemask = AUTOGEN_OBJ_NOTE;
                note_it.obj.name = linkname;
                note_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

                fprintf(env->fhtml, "<font size=\"2\">");

                fprintf(env->fhtml, "The purpose of this document is to specify the ISI messages for %s. ",
                    env->res->logical_name);

                if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
                {
                    if (env->res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES &&
                        env->res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES_EXT &&
                        env->res->base.subtype != RESOURCE_MEDIA_MODULE &&
                        env->res->base.subtype != RESOURCE_MEDIA_MODULE_EXTENSION)
                    {
                        fprintf(env->fhtml, "There are also common messages which must be supported by every server (see reference ");

                        strcpy(linkname, "/4/");
                        note = autogen_obj_find_in_list(&note_it, &env->res->note_list);

                        if (note)
                        {
                            fprintf(env->fhtml, "<a href=\"%s\">%s</a>",
                                html_obj_link(env, note, NULL),
                                html_obj_ver_pres(env, note, &env->res->note_list, &note->ver, NULL));
                        }
                        else
                        {
                            fprintf(env->fhtml, linkname);
                        }

                        fprintf(env->fhtml, ").");
                    }

                    fprintf(env->fhtml, "<br>\n<br>\n");
                    fprintf(env->fhtml, "More general guidelines about ISI server specification can be found from references ");

                    strcpy(linkname, "/2/");
                    note = autogen_obj_find_in_list(&note_it, &env->res->note_list);

                    if (note)
                    {
                        fprintf(env->fhtml, "<a href=\"%s\">%s</a> and ",
                            html_obj_link(env, note, NULL),
                            html_obj_ver_pres(env, note, &env->res->note_list, &note->ver, NULL));
                    }
                    else
                    {
                        fprintf(env->fhtml, "%s and ", linkname);
                    }

                    strcpy(linkname, "/3/");
                    note = autogen_obj_find_in_list(&note_it, &env->res->note_list);

                    if (note)
                    {
                        fprintf(env->fhtml, "<a href=\"%s\">%s</a>.",
                            html_obj_link(env, note, NULL),
                            html_obj_ver_pres(env, note, &env->res->note_list, &note->ver, NULL));
                    }
                    else
                    {
                        fprintf(env->fhtml, "%s.", linkname);
                    }

                    if (env->res->base.cmt_list)
                    {
                        fprintf(env->fhtml, "<br>\n<br>\n");
                    }
                }

                fprintf(env->fhtml, "</font>");
            }

            if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
            {
                if (env->res->base.cmt_list)
                {
                    html_comment(env, env->res->base.cmt_list, 
                        (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_INTRODUCTION) ? HTML_NEWLINE_AFTER : 0) | HTML_SET_FONT);
                }
            }

            fprintf(env->fhtml, "<br>");
        }

        fprintf(env->fhtml, "<br>\n");
    }
}

LOCAL void html_generate_message_header_section(html_environment* env, int* sec1, int is_toc)
{
    if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_INTRODUCTION) && env->res->base.subtype != RESOURCE_SHARED)
    {
        html_sec(env, is_toc, ++(*sec1), "Message Header");

        if (!is_toc)
        {
            autogen_it note_it = INIT_ITERATOR;
            autogen_obj* note;
            char linkname[10] = "/3/";

            note_it.typemask = AUTOGEN_OBJ_NOTE;
            note_it.obj.name = linkname;
            note_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

            note = autogen_obj_find_in_list(&note_it, &env->res->note_list);

            fprintf(env->fhtml, "<font size=\"2\">");

            fprintf(env->fhtml, "Every ISI message contains a message header. ");
            fprintf(env->fhtml, "The header is based on the Phonet message header plus some extra fields specific to ISI. ");
            if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
            {
                fprintf(env->fhtml, "More details concerning the ISI message header and how to build and use an ISI message ");
                fprintf(env->fhtml, "can be found in ISI General Information document (see reference ");

                if (note)
                {
                    fprintf(env->fhtml, "<a href=\"%s\">%s</a>",
                        html_obj_link(env, note, NULL),
                        html_obj_ver_pres(env, note, &env->res->note_list, &note->ver, NULL));
                }
                else
                {
                    fprintf(env->fhtml, linkname);
                }
                
                fprintf(env->fhtml, ").");
            }

            fprintf(env->fhtml, "<br>\n");

            fprintf(env->fhtml, "The ISI message specifications do not include the complete header information in each message, ");
            fprintf(env->fhtml, "as this is unnecessary. ");
            fprintf(env->fhtml, "The ISI message specifications refer only to the following field from the message header.<br>\n");
            if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
            {
                fprintf(env->fhtml, "&nbsp;·	Resource - This describes the function or resource (and therefore the server) that the message belongs to, e.g. PN_SECURITY, PN_CALL etc.<br>\n<br>\n");
            }

            fprintf(env->fhtml, "<b>Message specifications use the following format.</b>");
            fprintf(env->fhtml, "</font><br>\n<br>\n");

            /* dump example message */
            html_table(env);

            html_table_row(env, TRUE);
            if (prop_has((autogen_obj*)env->res, PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS))
            {	
                html_table_dat(env, 0, 0, 1, 10, "Size in bits");
            }
            else
            {	
                html_table_dat(env, 0, 0, 1, 10, "Size in bytes");
            }	
            html_table_dat(env, 0, 0, 1, 30, "Parameter");
            html_table_dat(env, 0, 0, 1, 40, "Description");
            html_table_row_end(env);

            fprintf(env->fhtml, " <tr bgcolor=\"#e0e0e0\">");
            html_table_dat(env, 0, 1, 0, 0, "3");
            html_table_dat(env, 0, 1, 0, 0, "Message header info");
            html_table_dat(env, 0, 1, 0, 0, "As in the PhoNet header");
            html_table_row_end(env);

            html_table_row(env, FALSE);
            html_table_dat(env, 0, 0, 0, 0, "1");
            html_table_dat(env, 0, 0, 0, 0, "Resource");

            if (env->res->base.subtype == RESOURCE_MEDIA_MODULE || env->res->base.subtype == RESOURCE_MEDIA_MODULE_EXTENSION)
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>PN_MEDIA_CONTROL</i>");
            }
            else if (env->res->base.subtype == RESOURCE_ISI_PRIVATE)
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>PN_PRIVATE</i>");
            }
            else if (env->res->base.subtype == RESOURCE_ISI_PREFIX || env->res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT)
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>PN_PREFIX</i>");
            }
            else if (env->res->base.subtype != RESOURCE_ISI_COMMON_MESSAGES)
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>%s</i>", env->res->base.name);
            }
            else
            {
                html_table_dat(env, 0, 0, 0, 0, "<i>RESOURCE_ID of the actual server</i>");
            }
            html_table_row_end(env);

            fprintf(env->fhtml, " <tr bgcolor=\"#e0e0e0\">");
            html_table_dat(env, 0, 1, 0, 0, "4");
            html_table_dat(env, 0, 1, 0, 0, "Message header info");
            html_table_dat(env, 0, 1, 0, 0, "As in the PhoNet header");
            html_table_row_end(env);

            html_table_row(env, FALSE);
            html_table_dat(env, 0, 1, 0, 0, "1");
            html_table_dat(env, 0, 1, 0, 0, "Transaction ID");
            html_table_dat(env, 0, 1, 0, 0, "&nbsp;");
            html_table_row_end(env);

            html_table_row(env, FALSE);
            html_table_dat(env, 0, 1, 0, 0, "1");
            html_table_dat(env, 0, 1, 0, 0, "Message ID");
            html_table_dat(env, 0, 1, 0, 0, "&nbsp;");
            html_table_row_end(env);

            if (env->res->base.subtype == RESOURCE_ISI_PRIVATE)
            {
                html_table_row(env, FALSE);
                html_table_dat(env, 0, 1, 0, 0, "2");
                html_table_dat(env, 0, 1, 0, 0, "Private ID");
                html_table_dat(env, 0, 1, 0, 0, "&nbsp;");
                html_table_row_end(env);
            }
            else if (env->res->base.subtype == RESOURCE_ISI_PREFIX || env->res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT)
            {
                html_table_row(env, FALSE);
                html_table_dat(env, 0, 1, 0, 0, "2");
                html_table_dat(env, 0, 1, 0, 0, "Resource ID");
                html_table_dat(env, 0, 1, 0, 0, "Type | Sub type");
                html_table_row_end(env);
            }

            html_table_row(env, FALSE);
            html_table_dat(env, 0, 1, 0, 0, "1");
            html_table_dat(env, 0, 1, 0, 0, "Some message specific data");
            html_table_dat(env, 0, 1, 0, 0, "&nbsp;");
            html_table_row_end(env);

            html_table_row(env, FALSE);
            html_table_dat(env, 0, 1, 0, 0, "1");
            html_table_dat(env, 0, 1, 0, 0, "Some more message specific data");
            html_table_dat(env, 0, 1, 0, 0, "&nbsp;");
            html_table_row_end(env);

            html_table_row(env, FALSE);
            html_table_dat(env, 0, 1, 0, 0, "1");
            html_table_dat(env, 0, 1, 0, 0, "Even more message specific data");
            html_table_dat(env, 0, 1, 0, 0, "&nbsp;");
            html_table_row_end(env);

            fprintf(env->fhtml, "</table><br>\n");
        }

        fprintf(env->fhtml, "<br>\n");
    }
}

LOCAL void html_generate_message_id_section(html_environment* env, int sec1, int* sec2, int is_toc)
{
    if (!env->res->msg_id_section || !(env->res->msg_id_section->flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML))
    {
        if (prop_has(&env->res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
        {
            html_generate_message_ids(env, AUTOGEN_MSG_REQ,                                      &env->res->msg_dev_dep_req_list,  " (Messages To Component)",   "#MSG_ID_TO",   sec1, sec2, is_toc);
            html_generate_message_ids(env, AUTOGEN_MSG_RESP | AUTOGEN_MSG_IND | AUTOGEN_MSG_NTF, &env->res->msg_dev_dep_resp_list, " (Messages From Component)", "#MSG_ID_FROM", sec1, sec2, is_toc);
        }
        else
        {
            html_generate_message_ids(env, AUTOGEN_MSG_FUNCTION_MASK, &env->res->msg_list, "", "#MSG_ID", sec1, sec2, is_toc);
        }
    }
}

LOCAL void html_generate_message_ids(html_environment* env, unsigned int flagany, autogen_obj_list* msg_list, const char* heading_suffix, const char* linkname, int sec1, int* sec2, int is_toc)
{
    int unique_submsg_name = prop_has(&env->res->base, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE);

    autogen_seq* msg;
    autogen_it msg_it = INIT_ITERATOR;

    msg_it.flagany   = flagany;
    msg_it.flagnone  = AUTOGEN_MSG_IS_PROTOCOL | AUTOGEN_OBJ_IS_LEGACY;
    msg_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

    msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, msg_list);
    if (msg)
    {
        /* Generate heading for message ID's */
        if (env->res->base.subtype & RESOURCE_TRC_ANY)
        {
            sprintf(env->char_buffer, "Trace ID's%s", heading_suffix);
        }
        else
        {
            sprintf(env->char_buffer, "Message ID's%s", heading_suffix);
        }

        html_subsec(env, is_toc, sec1, ++(*sec2), 0, "", env->char_buffer, linkname);
    }

    if (msg && !is_toc)
    {
        if (env->res->msg_id_section)
        {
            html_comment(env, env->res->msg_id_section->cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);
        }

        html_table(env);
        html_table_row(env, TRUE);

        if (env->res->base.subtype & RESOURCE_TRC_ANY)
        {
            html_table_dat(env, 0, 0, 1, 80, "Trace ID");
        }
        else
        {
            html_table_dat(env, 0, 0, 1, 80, "Message ID");
        }

        html_table_dat(env, 0, 0, 1, 20, "Hex value");
        html_table_row_end(env);

        while (msg)
        {
            const autogen_item* id_item = reference_get_special_item(&((autogen_seq*)msg)->ref_handle, PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID);

            if (msg->base.type == AUTOGEN_OBJ_MSG_BASE)
            {
                const autogen_item* submsg_id_item = reference_get_special_item(&msg->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID);

                autogen_obj* submsg;
                autogen_it submsg_it = INIT_ITERATOR;

                submsg_it.flagany   = flagany;
                submsg_it.flagnone  = AUTOGEN_MSG_IS_PROTOCOL | AUTOGEN_OBJ_IS_LEGACY;
                submsg_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

                /* Generate heading for message ID's */
                submsg = autogen_obj_find_in_list(&submsg_it, &msg->submsg_list);
                while (submsg)
                {
                    char msg_id_str[50] = "";

                    if (!unique_submsg_name)
                    {
                        if (id_item->length == 16)
                        {
#if (PMD_FILE_FORMAT >= 600)
                            sprintf(msg_id_str, "0x%4.4llX / ", msg->base.id);
#else
                            sprintf(msg_id_str, "0x%4.4X / ", msg->base.id);
#endif
                        }
                        else
                        {
#if (PMD_FILE_FORMAT >= 600)
                            sprintf(msg_id_str, "0x%2.2llX / ", msg->base.id);
#else
                            sprintf(msg_id_str, "0x%2.2X / ", msg->base.id);
#endif
                        }
                    }

                    if (submsg_id_item->length == 16)
                    {
#if (PMD_FILE_FORMAT >= 600)
                        sprintf(msg_id_str + strlen(msg_id_str), "0x%4.4llX", submsg->id);
#else
                        sprintf(msg_id_str + strlen(msg_id_str), "0x%4.4X", submsg->id);
#endif
                    }
                    else
                    {
#if (PMD_FILE_FORMAT >= 600)
                        sprintf(msg_id_str + strlen(msg_id_str), "0x%2.2llX", submsg->id);
#else
                        sprintf(msg_id_str + strlen(msg_id_str), "0x%2.2X", submsg->id);
#endif
                    }

                    html_table_row(env, FALSE);

                    if (msg->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML)
                    {
                        /* Check for presence of feature flag */
                        if (submsg->feature_flags)
                        {
                            /* Feature flags present */
                            html_add_featureflag_lst(env, submsg->feature_flags, env->collect_feature_flags.char_buffer);
                        }
                        else
                        {
                            /* No feature flag */
                            env->collect_feature_flags.char_buffer[0] = '\0';
                        }

                        /* Print out */
                        html_table_dat(env, 0, 0, 0, 0, 
                            "%s%s", html_obj_ver_pres(env, submsg, &msg->submsg_list, &submsg->ver, NULL), env->collect_feature_flags.char_buffer);
                    }
                    else
                    {
                        /* Check for presence of feature flag */
                        if (submsg->feature_flags)
                        {
                            /* Feature flags present */
                            html_add_featureflag_lst(env, submsg->feature_flags, env->collect_feature_flags.char_buffer);
                        }
                        else
                        {
                            /* No feature flag */
                            env->collect_feature_flags.char_buffer[0] = '\0';
                        }

                        /* Print out */
                        html_table_ref(env, 
                            html_obj_link(env, submsg, NULL), 
                            html_obj_ver_pres(env, submsg, &msg->submsg_list, &submsg->ver, NULL),
                            NULL, env->collect_feature_flags.char_buffer);
                    }

                    html_table_dat(env, 0, 0, 0, 0, msg_id_str);
                    html_table_row_end(env);

                    submsg = autogen_obj_find_next_in_list(&submsg_it);
                }
            }
            else if (msg->base.child_list.n_obj > 0)
            {
                char msg_id_str[50] = "";

                if (id_item->length == 16)
                {
#if (PMD_FILE_FORMAT >= 600)
                    sprintf(msg_id_str, "0x%4.4llX", msg->base.id);
#else
                    sprintf(msg_id_str, "0x%4.4X", msg->base.id);
#endif
                }
                else
                {
#if (PMD_FILE_FORMAT >= 600)
                    sprintf(msg_id_str, "0x%2.2llX", msg->base.id);
#else
                    sprintf(msg_id_str, "0x%2.2X", msg->base.id);
#endif
                }

                html_table_row(env, FALSE);

                if (msg->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML)
                {
                    /* Check for presence of feature flag */
                    if (msg->base.feature_flags)
                    {
                        /* Feature flags present */
                        html_add_featureflag_lst(env, msg->base.feature_flags, env->collect_feature_flags.char_buffer);
                    }
                    else
                    {
                        /* No feature flag */
                        env->collect_feature_flags.char_buffer[0] = '\0';
                    }

                    /* Print out */
                    html_table_dat(env, 0, 0, 0, 0, 
                        "%s%s", html_obj_ver_pres(env, &msg->base, &env->res->msg_list, &msg->base.ver, NULL), env->collect_feature_flags.char_buffer);
                }
                else
                {
                    /* Check for presence of feature flag */
                    if (msg->base.feature_flags)
                    {
                        /* Feature flags present */
                        html_add_featureflag_lst(env, msg->base.feature_flags, env->collect_feature_flags.char_buffer);
                    }
                    else
                    {
                        /* No feature flag */
                        env->collect_feature_flags.char_buffer[0] = '\0';
                    }

                    /* Print out */
                    html_table_ref(env, 
                        html_obj_link(env, &msg->base, NULL), 
                        html_obj_ver_pres(env, &msg->base, &env->res->msg_list, &msg->base.ver, NULL),
                        NULL, env->collect_feature_flags.char_buffer);
                }

                html_table_dat(env, 0, 0, 0, 0, msg_id_str);
                html_table_row_end(env);
            }

            msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
        }

        fprintf(env->fhtml, "</table>\n");

        if (env->collect_feature_flags.head)
        {
            /* Dump list of collected feature flags */
            html_print_feature_flag_lst(env);
        }
        fprintf(env->fhtml, "<br><br>\n");
    }
}

LOCAL void html_generate_message_section(html_environment* env, int* sec1, int is_toc)
{
    if (env->res->base.subtype == RESOURCE_MEDIA_MODULE || env->res->base.subtype == RESOURCE_MEDIA_MODULE_EXTENSION)
    {
        /* Media control messages */
        autogen_res* mctrlres = util_get_unique_res(RESOURCE_ISI_MEDIA_CONTROL);
        if (mctrlres)
        {
            html_generate_messages(env, AUTOGEN_MSG_FUNCTION_MASK, &mctrlres->msg_list, " (Media Control)", sec1, is_toc);
        }

        /* MM specific messages */
        html_generate_messages(env, AUTOGEN_MSG_REQ | AUTOGEN_MSG_RESP, &env->res->msg_list, " (Media Specific Control)", sec1, is_toc);
        html_generate_messages(env, AUTOGEN_MSG_NTF,                    &env->res->msg_list, " (Media Specific Notifications)",    sec1, is_toc);
        html_generate_messages(env, AUTOGEN_MSG_IND,                    &env->res->msg_list, " (Media Specific Indications)",      sec1, is_toc);
    }
    else if (prop_has(&env->res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        html_generate_messages(env, AUTOGEN_MSG_REQ,                                      &env->res->msg_dev_dep_req_list,  " (Messages To Component)",   sec1, is_toc);
        html_generate_messages(env, AUTOGEN_MSG_RESP | AUTOGEN_MSG_IND | AUTOGEN_MSG_NTF, &env->res->msg_dev_dep_resp_list, " (Messages From Component)", sec1, is_toc);
    }
    else
    {
        html_generate_messages(env, AUTOGEN_MSG_FUNCTION_MASK, &env->res->msg_list, "", sec1, is_toc);
    }
}

LOCAL void html_generate_messages(html_environment* env, unsigned int flagany, autogen_obj_list* msg_list, const char* heading_suffix, int* sec1, int is_toc)
{
    autogen_seq* msg;
    autogen_it msg_it = INIT_ITERATOR;

    msg_it.flagany   = flagany;
    msg_it.flagnone  = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;
    msg_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

    msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, msg_list);
    if (msg)
    {
        autogen_res* res = (autogen_res*)msg_list->parent;
        int sec2 = 0;

        if (env->res->base.subtype & RESOURCE_TRC_ANY)
        {
            html_sec(env, is_toc, ++(*sec1), "Trace Descriptions%s", heading_suffix);
        }
        else
        {
            html_sec(env, is_toc, ++(*sec1), "Message Descriptions%s", heading_suffix);
        }

        while (msg)
        {
            if (msg->base.type == AUTOGEN_OBJ_MSG_BASE)
            {
                int sec3 = 0;
                autogen_obj* submsg;
                autogen_it submsg_it = INIT_ITERATOR;

                submsg_it.flagany   = flagany;
                submsg_it.flagnone  = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;
                submsg_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

                submsg = autogen_obj_find_in_list(&submsg_it, &msg->submsg_list);
                if (submsg)
                {
                    html_subsec(env, is_toc, *sec1, ++sec2, 0, "", msg->base.name, html_obj_link(env, &msg->base, env->is_in_frame ? res : NULL));

                    html_msg(env, msg, is_toc);
                }
                while (submsg)
                {
                    html_subsec(env, is_toc, *sec1, sec2, ++sec3, "", 
                        html_obj_ver_pres(env, submsg, &msg->submsg_list, &submsg->ver, NULL), 
                        html_obj_link(env, submsg, env->is_in_frame ? res : NULL));

                    html_msg(env, (autogen_seq*)submsg, is_toc);

                    submsg = autogen_obj_find_next_in_list(&submsg_it);
                }
            }
            else
            {
                int generate = TRUE;

                /* When generatin media control messages for media modules, exclude specific messages... */
                if (res->base.subtype == RESOURCE_ISI_MEDIA_CONTROL && strlen(heading_suffix) > 0)
                {
                    if (prop_has(&msg->base, PROPERTY_MSG_IS_MEDIA_CTRL_SPECIFIC))
                    {
                        generate = FALSE;
                    }
                    else if (!strcmp(msg->base.name, "PNS_MEDIA_SPECIFIC_REQ") ||
                        !strcmp(msg->base.name, "PNS_MEDIA_SPECIFIC_RESP") ||
                        !strcmp(msg->base.name, "PNS_MEDIA_SPECIFIC_NTF") ||
                        !strcmp(msg->base.name, "PNS_MEDIA_IND"))
                    {
                        generate = FALSE;
                    }
                }

                if (generate)
                {
                    html_subsec(env, is_toc, *sec1, ++sec2, 0, "", 
                        html_obj_ver_pres(env, &msg->base, msg_list, &msg->base.ver, NULL), 
                        html_obj_link(env, &msg->base, env->is_in_frame ? res : NULL));
                }

                html_msg(env, msg, is_toc);
            }

            msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
        }

        fprintf(env->fhtml, "<br>\n");
    }
}

LOCAL void html_generate_sequence_section(html_environment* env, int* sec1, int is_toc)
{
    /* generate sequences */
    html_generate_sequences(env, AUTOGEN_OBJ_SB,          "Subblock ",          sec1, is_toc);
    html_generate_sequences(env, AUTOGEN_OBJ_SB_TEMPLATE, "Subblock Template ", sec1, is_toc);
    html_generate_sequences(env, AUTOGEN_OBJ_SEQ,         "Sequence ",          sec1, is_toc);
}

LOCAL void html_generate_sequences(html_environment* env, unsigned int typemask, const char* heading_prefix, int* sec1, int is_toc)
{
    autogen_obj* seq;
    autogen_it seq_it = INIT_ITERATOR;
    int sec2 = 0;

    seq_it.typemask = typemask;
    seq_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY | AUTOGEN_SEQ_IS_NOT_STRUCT;

    if (env->res->base.subtype != RESOURCE_SHARED)
    {
        seq_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
    }

    seq = autogen_obj_find_in_list(&seq_it, &env->res->seq_list);
    if (seq)
    {
        html_sec(env, is_toc, ++(*sec1), "%sDescriptions", heading_prefix);
    
        while (seq)
        {
            html_subsec(env, is_toc, *sec1, ++sec2, 0, "", 
                html_obj_ver_pres(env, seq, &env->res->seq_list, &seq->ver, NULL), 
                html_obj_link(env, seq, env->is_in_frame ? env->res : NULL));

            html_seq(env, (autogen_seq*)seq, is_toc);

            seq = autogen_obj_find_next_in_list(&seq_it);
        }

        fprintf(env->fhtml, "<br>\n");
    }
}

LOCAL void html_generate_traces(html_environment* env, int* sec1, int is_toc)
{
    if (env->res->trcgrp_list)
    {
        if (env->res->trc_conf->has_groups)
        {
            int sec2 = 0;
            int first = TRUE;
            autogen_obj* trcgrp;
            autogen_it trcgrp_it = INIT_ITERATOR;

            trcgrp_it.typemask  = AUTOGEN_OBJ_TRACEGRP;
            trcgrp_it.flagnone  = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;
            trcgrp_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

            trcgrp = autogen_obj_find_in_list(&trcgrp_it, env->res->trcgrp_list);
            while (trcgrp)
            {
                if (trcgrp->res == env->res)
                {
                    int sec3 = 0;

                    autogen_obj* trc;
                    autogen_it trc_it = INIT_ITERATOR;

                    trc_it.typemask  = AUTOGEN_OBJ_TRACE;
                    trc_it.flagnone  = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;
                    trc_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

                    if (first)
                    {
                        html_sec(env, is_toc, ++(*sec1), pmd_constant_lookup_message_type_name(env->res->trc_conf->msg_type));
                        first = FALSE;
                    }

                    html_subsec(env, is_toc, *sec1, ++sec2, 0, "", trcgrp->name, 
                        html_obj_link(env, trcgrp, NULL));

                    if (!is_toc)
                    {
                        html_comment(env, trcgrp->cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);
                    }

                    if (!is_toc && trcgrp->feature_flags)
                    {
                        /* Print out feature flag for trace group */
                        html_print_feature_flag(env, "<b>Feature flag:</b>", trcgrp->feature_flags);
                        fprintf(env->fhtml, "<br><br>\n");

                    }

                    trc = autogen_obj_find_in_list(&trc_it, &trcgrp->child_list);
                    while (trc)
                    {
                        html_subsec(env, is_toc, *sec1, sec2, ++sec3, "", trc->name, 
                            html_obj_link(env, trc, NULL));

                        html_msg(env, (autogen_seq*)trc, is_toc);

                        trc = autogen_obj_find_next_in_list(&trc_it);
                    }
                }

                trcgrp = autogen_obj_find_next_in_list(&trcgrp_it);
            }
        }
        else
        {
            autogen_obj* trc;
            autogen_it trc_it = INIT_ITERATOR;

            trc_it.typemask  = AUTOGEN_OBJ_TRACE;
            trc_it.flagnone  = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;
            trc_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;

            trc = autogen_obj_find_in_list(&trc_it, env->res->trcgrp_list);
            if (trc)
            {
                int sec2 = 0;

                html_sec(env, is_toc, ++(*sec1), pmd_constant_lookup_message_type_name(env->res->trc_conf->msg_type));

                while (trc)
                {
                    html_subsec(env, is_toc, *sec1, ++sec2, 0, "", trc->name, 
                        html_obj_link(env, trc, NULL));

                    if (trc->feature_flags)
                    {
                        /* Print out feature flag for trace group */
                        html_print_feature_flag(env, "<b>Feature flag:</b>", trc->feature_flags);
                        fprintf(env->fhtml, "<br><br>");
                    }

                    html_msg(env, (autogen_seq*)trc, is_toc);

                    trc = autogen_obj_find_next_in_list(&trc_it);
                }
            }

            fprintf(env->fhtml, "<br>\n");
        }
    }
}

/*  Generates the resource page */
LOCAL void html_res(html_environment* env)
{
    char str_file[200];
    int sec1 = 0, sec2 = 0, sec3 = 0;

    FILE* old_fhtml = env->fhtml;

    env->gif_depth = 0;

    if (!prop_has((autogen_obj*)env->res, PROPERTY_HTML_DIRECTORY_PATH))
    {
        /* give warning, dump to html directory - except for SYMBOLS & traces */
        if (env->res->base.subtype != RESOURCE_SYMBOLS && !(env->res->base.subtype & RESOURCE_TRC_ANY))
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                "Property 'PROPERTY_HTML_DIRECTORY_PATH' not found for resource %s. Dumping to default directory.", env->res->resnameshort_u);
        }
    }
    else
    {
        char str_dir[100];
        int index = 0;
        int i = 0;
        const char *html_dir_path = prop_get_string((autogen_obj*)env->res, PROPERTY_HTML_DIRECTORY_PATH);
        int len = strlen(html_dir_path);
        memset(str_dir, '\0', 100);
        for (i = 0; i <= len; i++) /* '=' ? Create deepest dir upon i = len, that's why! */
        {
            char c = '\0';
            if (i < len)
            {
                c = (char)*(html_dir_path+i);
                if ((c == '/') && (i == (len-1)))/* ending with '/', not according to spec. */
                    c = '\0';
            }
            if ((c == '/') || (i == len))
            {
#ifdef _MSC_VER
                if (mkdir (str_dir) == 0)
#else
                if (mkdir (str_dir, 0755) == 0)/* set access rights */
#endif
                {
                    chdir(str_dir);
                    env->gif_depth++;
                }
                else
                {
                    /* if (errno == EEXIST) Not known by all compilers :-( */
                    if (chdir(str_dir) == 0) /* Directory existed */
                    {
                        env->gif_depth++;
                    }
                    else
                    {
                        /* give warning, dump to default directory */
                        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_LOCAL, 0,
                            "Failed to create directory %s. Dumping to default directory.", str_dir);
                        while (env->gif_depth) /* back to html root */
                        {
                            chdir("..");
                            env->gif_depth--;
                        }
                        break;
                    }
                }
                memset(str_dir, '\0', 100);
                index = 0;
            }
            else
            {
                str_dir[index++] = c;
            }
        }
    }
    env->fhtml = fopen(env->filename, "w");
    if (!env->fhtml)
    {
        printf("\nError: Unable to open file %s for writing. Aborting...\n", env->filename);
        exit(1);
    }

    fprintf(env->fhtml, "<html>\n");
    fprintf(env->fhtml, "<head><title>%s</title></head>\n", 
        prop_get_string_default((autogen_obj*)env->res, PROPERTY_HTML_TITLE, env->filename));
    fprintf(env->fhtml, "<body leftmargin=20>\n");


    /* print company information */
    fprintf(env->fhtml, "<table width=\"100%%\" border=\"0\" bordercolor=\"#000000\">\n");

    html_table_row(env, FALSE);
    html_table_dat(env, 0, 0, 0, 0, 
        prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_NOKIA_ENTITY, "Nokia"));
    fprintf(env->fhtml, "<td align=right>%s</td>", 
        prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_CONFIDENTIALITY, "CONFIDENTIAL"));
    html_table_row_end(env);

    /* site name */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        html_table_row(env, FALSE);
        html_table_dat(env, 0, 0, 0, 0, prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_SITE_NAME, ""));
        html_table_dat(env, 0, 0, 0, 0, "&nbsp;");
        html_table_row_end(env);

        /* project name */
        html_table_row(env, FALSE);
        html_table_dat(env, 0, 0, 0, 0, prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_NAME, ""));
        html_table_dat(env, 0, 0, 0, 0, "&nbsp;");
        html_table_row_end(env);
    }

    fprintf(env->fhtml, "</table><br>\n<br>\n");

    /* print title */
    fprintf(env->fhtml, "<font size=\"5\"><center><b><a href=#doc_toc>%s</a></b></center><br></font><br>\n", 
        prop_get_string_default((autogen_obj*)env->res, PROPERTY_HTML_TITLE, env->filename));


    fprintf(env->fhtml, "<center><table cellspacing=\"1\" cellpadding=\"5\" "
        "border=\"1\" bordercolor=\"#000000\" "
        "bordercolordark=\"#000000\" bordercolorlight=\"#000000\">\n");

    /* print version information */
    {
        autogen_it ver_it = INIT_ITERATOR;
        autogen_obj* ver_obj;
        const char* ver_str = util_ver_to_text(&env->res->base.ver);

        ver_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        ver_it.ver      = &env->res->base.ver;
        ver_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

        ver_obj = autogen_obj_find_in_list(&ver_it, &env->res->ver_list);
        if (strlen(ver_str) > 1 && strcmp(ver_str, "000.000") && strcmp(ver_str, "000.000.000"))
        {
            fprintf(env->fhtml, " <tr><td valign=\"top\">Version</td>");
            fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", ver_str);
        }

        if (ver_obj)
        {
            /* print status */
            if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
            {
                fprintf(env->fhtml, " <tr><td valign=\"top\">Status</td>");
                fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", 
                    prop_get_string_default(ver_obj, PROPERTY_CHANGE_STATUS, "-"));
            }

            /* print date */
            fprintf(env->fhtml, " <tr><td valign=\"top\">Date</td>");
            fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", 
                prop_get_string_default(ver_obj, PROPERTY_CHANGE_DATE, "-"));
        }

        if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
        {
            /* print document number */
            fprintf(env->fhtml, " <tr><td valign=\"top\">Document number</td>");
            fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_HTML_DOCUMENT_NUMBER, "-"));

            /* print owner */
            fprintf(env->fhtml, " <tr><td valign=\"top\">Owner</td>");
            fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_PROJECT_OWNER_NAME, "-"));

            /* print Continuus information */
            fprintf(env->fhtml, " <tr><td valign=\"top\">Continuus database</td>");
            fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_HTML_CONTINUUS_PROJECT_DB, "-"));

            fprintf(env->fhtml, " <tr><td valign=\"top\">Continuus project</td>");
            fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_HTML_CONTINUUS_PROJECT_NAME, "-"));

            /* print directory path */
            fprintf(env->fhtml, " <tr><td valign=\"top\">Directory path</td>");
            fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", 
                prop_get_string_default((autogen_obj*)env->res, PROPERTY_HTML_DIRECTORY_PATH, "-"));
        }

        /* print filename */
        fprintf(env->fhtml, " <tr><td valign=\"top\">File name</td>");
        fprintf(env->fhtml, "<td valign=\"top\">%s</td></tr>\n", env->filename);

        fprintf(env->fhtml, "</table></center><br><br>\n");
    }


    if (env->res->base.subtype == RESOURCE_ISI_PRIVATE)
    {
        fprintf(env->fhtml, "This interface is a private interface.<br><br>\n");
    }

    /* Generate version history */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        int first = TRUE;
        autogen_obj* ver;
        autogen_it ver_it = INIT_ITERATOR;

        /* Set minimum version based on PROPERTY_ISI_VERSION_AUTO_GENERATE */
        unsigned short auto_ver_from[3] = { 0, 0, 0 };
        const char*    auto_ver_str = prop_get_string_default(&env->res->base, PROPERTY_ISI_VERSION_AUTO_GENERATE, "000.000");

        auto_ver_from[0] = (unsigned short)atoi(&auto_ver_str[0]);
        auto_ver_from[1] = (unsigned short)atoi(&auto_ver_str[4]);
        /* END FOR AUTO GENERATED VERSION HISTORY ONLY */

        ver_it.flagnone  = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;
        ver_it.sort_type = AUTOGEN_OBJ_LIST_SORT_BY_VERSION_REVERSED;

        ver = autogen_obj_find_in_list(&ver_it, &env->res->ver_list);
        while (ver)
        {
            int description_printed = FALSE;

            /* Output header as soon as we know that we have a comment */
            if (first)
            {
                if ((env->res->base.subtype & RESOURCE_ISI_ANY) && !prop_has(&env->res->base, PROPERTY_ISI_VERSIONING_NOT_SUPPORTED))
                {
                    fprintf(env->fhtml, "<b>ISI Version Change History</b><br><br>\n");
                }
                else
                {
                    fprintf(env->fhtml, "<b>Version Change History</b><br><br>\n");
                }

                fprintf(env->fhtml, "<table cellspacing=\"1\" cellpadding=\"1\" "
                    "border=\"0\" bordercolor=\"#000000\" "
                    "bordercolordark=\"#000000\" bordercolorlight=\"#000000\">\n");

                first = FALSE;
            }
            else
            {
                html_table_row(env, FALSE);
                html_table_dat(env, 0, 0, 0, 0, "&nbsp;");
                html_table_dat(env, 0, 0, 0, 0, "&nbsp;");
                html_table_row_end(env);
            }

            /* Output ISI version */
            html_table_row(env, FALSE);
            html_table_dat(env, 0, 0, 0, 0, "Version:");

            if (prop_has(ver, PROPERTY_VERSION_NO_LONGER_SUPPORTED))
            {
                html_table_dat(env, 0, 0, 0, 0, "%s&nbsp;&nbsp;<b>(No longer supported)</b>",
                    util_ver_to_text(&ver->ver));
            }
            else if (prop_has(ver, PROPERTY_VERSION_NOT_YET_SUPPORTED))
            {
                html_table_dat(env, 0, 0, 0, 0, "%s&nbsp;&nbsp;<b>(No yet supported)</b>",
                    util_ver_to_text(&ver->ver));
            }
            else
            {
                html_table_dat(env, 0, 0, 0, 0, util_ver_to_text(&ver->ver));
            }
            html_table_row_end(env);

            /* Output change status */
            html_table_row(env, FALSE);
            html_table_dat(env, 0, 0, 0, 0, "Status:");
            html_table_dat(env, 0, 0, 0, 0, 
                prop_get_string_default(ver, PROPERTY_CHANGE_STATUS, "-"));
            html_table_row_end(env);

            /* Output change date */
            html_table_row(env, FALSE);
            html_table_dat(env, 0, 0, 0, 0, "Date:");
            html_table_dat(env, 0, 0, 0, 0, "%s&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%s", 
                prop_get_string_default(ver, PROPERTY_CHANGE_DATE, "-"),
                prop_get_string_default(ver, PROPERTY_CHANGE_PERSON, "-"));
            html_table_row_end(env);

            /* Output change reason */
            html_table_row(env, FALSE);
            html_table_dat(env, 0, 0, 0, 0, "Reason:");
            html_table_dat(env, 0, 0, 0, 0, 
                prop_get_string_default(ver, PROPERTY_CHANGE_REASON, "-"));
            html_table_row_end(env);

            /* Output change reference */
            {
                const autogen_prop* prop = prop_find_first(ver, PROPERTY_CHANGE_REFERENCE);
                {
                    html_table_row(env, FALSE);
                    html_table_dat(env, 0, 0, 0, 0, "Reference:");
                    html_table_dat(env, 0, 0, 0, 0, prop ? prop->str : "-");
                    html_table_row_end(env);
                }
                if (prop)
                {
                    prop = prop_find_next(prop);
                }
                while (prop)
                {
                    html_table_row(env, FALSE);
                    html_table_dat(env, 0, 0, 0, 0, "&nbsp;");
                    html_table_dat(env, 0, 0, 0, 0, prop->str);
                    html_table_row_end(env);

                    prop = prop_find_next(prop);
                }
            }

            /* Output change description */
            if (autogen_ver_comp(auto_ver_from, ver->ver.from) & (AUTOGEN_VER_EQUAL | AUTOGEN_VER_NEWER))
            {
                autogen_obj* changed_elements = autogen_obj_get_first_in_list(&ver->child_list);
                while (changed_elements)
                {
                    const char* title = "";
                    const char* where = "in";
                    const char* ch_mark = "";
                    const char* tbl_conversion = "";

                    autogen_obj* temp_obj = changed_elements->ptr;

                    switch (changed_elements->subtype)
                    {
                    case AUTOGEN_VERSION_HISTORY_OBJECT_ADDED:
                        {
                            title = "Added";
                            where = "to";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_DISCONTINUED:
                        {
                            title = "Discontinued";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED:
                    case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_COMPATIBLE:
                        {
                            title = "Changed";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_REINTRODUCED:
                        {
                            title = "Reintroduced";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_FILLER_REPLACED:
                        {
                            title   = "Filler replaced by";
                            ch_mark = "'";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_CONST_TBL_TO_BIT_TBL:
                        {
                            title = "Changed Constant table";
                            tbl_conversion = "to Bitmask table";
                        }
                        break;
                    case AUTOGEN_VERSION_HISTORY_OBJECT_CHANGED_BIT_TBL_TO_CONST_TBL:
                        {
                            title = "Changed Bitmask table";
                            tbl_conversion = "to Constant table";
                        }
                        break;
                    }

                    /* No output for derived tables, as these are not shown in ISI header anyway */
                    if (temp_obj->type == AUTOGEN_OBJ_TBLENTRY && (temp_obj->parent->subtype & AUTOGEN_TBL_DER_ANY) ||
                        temp_obj->type == AUTOGEN_OBJ_TBL      && (temp_obj->subtype & AUTOGEN_TBL_DER_ANY))
                    {
                        title = "";
                    }

                    /* Only generate for above listed types */
                    if (title[0])
                    {
                        html_table_row(env, FALSE);

                        if (description_printed)
                        {
                            html_table_dat(env, 0, 0, 0, 0, "&nbsp;");/* empty column */
                        }
                        else
                        {
                            html_table_dat(env, 0, 0, 0, 0, "Description:&nbsp;&nbsp;");
                            description_printed = TRUE;
                        }

                        if (tbl_conversion[0])
                        {
                            html_table_dat(env, 0, 0, 0, 0, "%s <a href=\"%s\">%s</a> %s", 
                                title,
                                html_obj_link(env, temp_obj, NULL), 
                                util_get_obj_name(temp_obj),
                                tbl_conversion);
                        }
                        else if ((temp_obj->type == AUTOGEN_OBJ_TBLENTRY) || 
                            (temp_obj->type == AUTOGEN_OBJ_DATA && temp_obj->subtype == AUTOGEN_DATA_PPC) || 
                            (temp_obj->type == AUTOGEN_OBJ_ITEM))
                        {
                            html_table_dat(env, 0, 0, 0, 0, "%s %s %s%s%s %s <a href=\"%s\">%s</a>", 
                                title,
                                util_get_obj_type_name(temp_obj), 
                                ch_mark, util_get_obj_name(temp_obj), ch_mark,
                                where,
                                html_obj_link(env, util_get_base_parent(temp_obj), NULL),
                                util_get_obj_name(util_get_base_parent(temp_obj)));
                        }
                        else if (temp_obj->type == AUTOGEN_OBJ_REF)
                        {
                            if ((temp_obj->flag) & (AUTOGEN_OBJ_IS_SHARED | AUTOGEN_OBJ_IS_SHARED_EXTERNAL))
                            {
                                html_table_dat(env, 0, 0, 0, 0, "%s&nbsp;%s&nbsp;<a href=\"%s%s\">%s</a>&nbsp;%s&nbsp;<a href=\"%s\">%s</a>", 
                                    title,
                                    util_get_obj_type_name(temp_obj),
                                    html_up_level(env),
                                    html_obj_link(env, ((autogen_obj*)((autogen_seq_ref*)temp_obj)->seqptr)->ptr, (autogen_res*)((autogen_seq_ref*)temp_obj)->seqptr->base.res),
                                    util_get_obj_name(temp_obj),
                                    where,
                                    html_obj_link(env, util_get_base_parent(temp_obj), NULL),
                                    util_get_obj_name(util_get_base_parent(temp_obj)));
                            }
                            else
                            {
                                html_table_dat(env, 0, 0, 0, 0, "%s&nbsp;%s&nbsp;<a href=\"%s\">%s</a>&nbsp;%s&nbsp;<a href=\"%s\">%s</a>", 
                                    title,
                                    util_get_obj_type_name(temp_obj), 
                                    html_obj_link(env, (autogen_obj*)((autogen_seq_ref*)temp_obj)->seqptr, NULL),
                                    util_get_obj_name(temp_obj),
                                    where,
                                    html_obj_link(env, util_get_base_parent(temp_obj), NULL),
                                    util_get_obj_name(util_get_base_parent(temp_obj)));
                            }
                        }
                        else if (temp_obj->type == AUTOGEN_OBJ_CONST)
                        {
                            html_table_dat(env, 0, 0, 0, 0, "%s&nbsp;%s&nbsp;%s",
                                title, util_get_obj_type_name(temp_obj),
                                html_const_link(env, temp_obj->name, &temp_obj->ver));
                        }
                        else if (temp_obj->type == AUTOGEN_OBJ_SHARED_FILE)
                        {
                            /* "Added Shared file from <resource>" */
                            html_table_dat(env, 0, 0, 0, 0, "%s&nbsp;%s&nbsp;from&nbsp;%s",
                                title, util_get_obj_type_name(temp_obj),
                                html_const_link(env, temp_obj->name, &temp_obj->ver));
                        }
                        else
                        {
                            /*  To Do? Do not list if defined in shared file 
                            if (!((temp_obj->flag) & (AUTOGEN_OBJ_IS_SHARED | AUTOGEN_OBJ_IS_SHARED_EXTERNAL)))
                            */
                            html_table_dat(env, 0, 0, 0, 0, "%s&nbsp;%s&nbsp;<a href=\"%s\">%s</a>",
                                title, util_get_obj_type_name(temp_obj),
                                html_obj_link(env, temp_obj, NULL),
                                util_get_obj_name(temp_obj));
                        }

                        html_table_row_end(env);

                        description_printed = TRUE; /* elements to be printed, so it's ok to assume that something will be printed*/
                    }

                    changed_elements = changed_elements->next;
                }
            }
            /* END OF AUTO GENERATED VERSION HISTORY */


            /* User description */
            if (ver->cmt_list)
            {
                html_table_row(env, FALSE);
                if (description_printed)
                {
                    html_table_dat(env, 0, 0, 0, 0, "&nbsp;");/* empty column */
                }
                else
                {
                    html_table_dat(env, 0, 0, 0, 0, "Description:&nbsp;&nbsp;");
                }
                html_table_com(env, ver->cmt_list);
                html_table_row_end(env);
            }
            else if (!description_printed)
            {
                html_table_row(env, FALSE);
                html_table_dat(env, 0, 0, 0, 0, "Description:&nbsp;&nbsp;");
                html_table_dat(env, 0, 0, 0, 0, "-");
                html_table_row_end(env);
            }

            ver = autogen_obj_find_next_in_list(&ver_it);
        }

        /* Output end of table if we ever begun it */
        if (!first)
        {
            fprintf(env->fhtml, "</table><br>\n");
        }
    }

    if (prop_has((autogen_obj*)env->res, PROPERTY_COPYRIGHT_YEAR))
    {
        fprintf(env->fhtml, "Copyright (c) %s Nokia Corporation. All rights reserved.<br>\n<br>\n<br>\n", prop_get_string((autogen_obj*)env->res, PROPERTY_COPYRIGHT_YEAR));
    }
    else
    {
        fprintf(env->fhtml, "Copyright (c) Nokia Corporation. All rights reserved.<br>\n<br>\n<br>\n");
    }

    /* insert an anchor for the toc */
    fprintf(env->fhtml, "<a name=doc_toc></a>");

    html_write_toc(env);

    /* insert an anchor for the start of the document */
    fprintf(env->fhtml, "<a name=doc_start></a>");


    /* generate introduction */
    html_generate_introduction_section(env, &sec1, FALSE);

    /* generate message header */
    html_generate_message_header_section(env, &sec1, FALSE);

    /* generate messages */
    html_generate_message_section(env, &sec1, FALSE);

    /* generate traces */
    html_generate_traces(env, &sec1, FALSE);

    /* generate sequences */
    html_generate_sequence_section(env, &sec1, FALSE);

    /* generate symbol information */
    html_sec(env, FALSE, ++sec1, "Symbol Information");
    sec2 = 0;

    /* generate constants */
    {
        autogen_obj* cons;
        autogen_it cons_it = INIT_ITERATOR;

        cons_it.typemask = AUTOGEN_OBJ_CONST;
        cons_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            cons_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        cons = autogen_obj_find_in_list(&cons_it, &env->res->const_list);
        if (cons)
        {
            /* Generate table header */
            html_subsec(env, FALSE, sec1, ++sec2, 0, "", "Constants", "GENERAL_CONST");

            html_table(env);
            html_table_row(env, TRUE);
            html_table_dat(env, 0, 0, 1, 50, "Constant");
            html_table_dat(env, 0, 0, 1, 15, "Value");
            html_table_dat(env, 0, 0, 1, 35, "Comment");
            html_table_row_end(env);

            /* Generate each of the table rows */
            while (cons)
            {
                /* Generate the table row */
                html_table_row(env, FALSE);

                if (cons->feature_flags)
                {
                    /* Feature flags present */
                    html_add_featureflag_lst(env, cons->feature_flags, env->collect_feature_flags.char_buffer);
                    html_table_dat(env, 0, 0, 0, 0, 
                        "%s%s", html_obj_ver_pres(env, cons, &env->res->const_list, &cons->ver, NULL), env->collect_feature_flags.char_buffer);
                }
                else
                {
                    /* No feature flags */
                    html_table_dat(env, 0, 0, 0, 0, 
                        html_obj_ver_pres(env, cons, &env->res->const_list, &cons->ver, NULL));
                }

                /* Format value */
                if (cons->flag & AUTOGEN_CONST_SIGNED)
                {
#if (PMD_FILE_FORMAT >= 600)
                    html_table_dat(env, 0, 0, 0, 0, "%lld", (long long)cons->id);
#else
                    html_table_dat(env, 0, 0, 0, 0, "%d", (int)cons->id);
#endif
                }
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_DEC)
                {
                    if (cons->id <= 0xFF)
                    {
#if (PMD_FILE_FORMAT >= 600)
                        html_table_dat(env, 0, 0, 0, 0, "0x%02llX", cons->id);
#else
                        html_table_dat(env, 0, 0, 0, 0, "0x%02X", cons->id);
#endif
                    }
                    else if (cons->id <= 0xFFFF)
                    {
#if (PMD_FILE_FORMAT >= 600)
                        html_table_dat(env, 0, 0, 0, 0, "0x%04llX", cons->id);
#else
                        html_table_dat(env, 0, 0, 0, 0, "0x%04X", cons->id);
#endif
                    }
#if (PMD_FILE_FORMAT >= 600)
                    else if (cons->id <= 0xFFFFFFFF)
                    {
                        html_table_dat(env, 0, 0, 0, 0, "0x%08llX", cons->id);
                    }
                    else
                    {
                        html_table_dat(env, 0, 0, 0, 0, "0x%016llX", cons->id);
                    }
#else
                    else
                    {
                        html_table_dat(env, 0, 0, 0, 0, "0x%08X", cons->id);
                    }
#endif
                }
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_BYTE)
                {
#if (PMD_FILE_FORMAT >= 600)
                    html_table_dat(env, 0, 0, 0, 0, "0x%02llX", cons->id);
#else
                    html_table_dat(env, 0, 0, 0, 0, "0x%02X", cons->id);
#endif
                }
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_WORD)
                {
#if (PMD_FILE_FORMAT >= 600)
                    html_table_dat(env, 0, 0, 0, 0, "0x%04llX", cons->id);
#else
                    html_table_dat(env, 0, 0, 0, 0, "0x%04X", cons->id);
#endif
                }
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_DWORD)
                {
#if (PMD_FILE_FORMAT >= 600)
                    html_table_dat(env, 0, 0, 0, 0, "0x%08llX", cons->id);
#else
                    html_table_dat(env, 0, 0, 0, 0, "0x%08X", cons->id);
#endif
                }
#if (PMD_FILE_FORMAT >= 600)
                else if (cons->flag & AUTOGEN_CONST_UNSIGNED_DDWORD)
                {
                    html_table_dat(env, 0, 0, 0, 0, "0x%016llX", cons->id);
                }
#endif
                else
                {
#if (PMD_FILE_FORMAT >= 600)
                    html_table_dat(env, 0, 0, 0, 0, "%llu", cons->id);
#else
                    html_table_dat(env, 0, 0, 0, 0, "%u", cons->id);
#endif

                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in html_res(). cons->flag is 0x%8.8X", cons->flag);
                }

                html_table_com(env, cons->cmt_list);

                html_table_row_end(env);

                cons = autogen_obj_find_next_in_list(&cons_it);
            }

            /* End the table and clean up */
            fprintf(env->fhtml, "</table>\n\n");

            if (env->collect_feature_flags.head)
            {
                /* Dump list of collected feature flags */
                html_print_feature_flag_lst(env);
            }
            fprintf(env->fhtml, "<br><br>");
        }
    }

    /* generate trace ID's */
    if (env->res->trcgrp_list)
    {
        if (!env->res->trc_conf->has_groups)
        {
            autogen_obj* trc = NULL;
            autogen_it trc_it = INIT_ITERATOR;

            trc_it.typemask = AUTOGEN_OBJ_TRACE;
            trc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

            trc = autogen_obj_find_in_list(&trc_it, env->res->trcgrp_list);
            if (trc)
            {
                html_subsec(env, FALSE, sec1, ++sec2, 0, "", "Trace ID's", "MSG_ID");
                sec2 = 0;

                while (trc)
                {
                    html_subsec(env, FALSE, sec1, ++sec2, 0, "", trc->name, 
                        html_obj_link(env, trc, NULL));

                    html_msg(env, (autogen_seq*)trc, FALSE);

                    trc = autogen_obj_find_next_in_list(&trc_it);
                }
            }
        }
    }

    /* generate Message ID's */
    html_generate_message_id_section(env, sec1, &sec2, FALSE);

    /* generate subblock ID's */
    {
        autogen_obj* sb;
        autogen_it sb_it = INIT_ITERATOR;

        sb_it.typemask = AUTOGEN_OBJ_SB;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            sb_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        sb = autogen_obj_find_in_list(&sb_it, &env->res->seq_list);
        if (sb)
        {
            html_subsec(env, FALSE, sec1, ++sec2, 0, "", "Subblock ID's", "#SB_ID");

            if (env->res->sb_id_section)
            {
                html_comment(env, env->res->sb_id_section->cmt_list, HTML_NEWLINE_AFTER | HTML_SET_FONT);
            }

            html_table(env);
            html_table_row(env, TRUE);
            html_table_dat(env, 0, 0, 1, 80, "Subblock ID");
            html_table_dat(env, 0, 0, 1, 20, "Hex value");
            html_table_row_end(env);

            sec3 = 0;

            while (sb)
            {
                const autogen_item* id_item =  reference_get_special_item(&((autogen_seq*)sb)->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID);

                html_table_row(env, FALSE);

                if (sb->flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML)
                {
                    /* Check for presence of feature flag */
                    if (sb->feature_flags)
                    {
                        /* Feature flags present */
                        html_add_featureflag_lst(env, sb->feature_flags, env->collect_feature_flags.char_buffer);
                    }
                    else
                    {
                        /* No feature flag */
                        env->collect_feature_flags.char_buffer[0] = '\0';
                    }

                    /* Print out */
                    html_table_dat(env, 0,0,0,0,
                        "%s%s", html_obj_ver_pres(env, sb, &env->res->seq_list, &sb->ver, NULL), env->collect_feature_flags.char_buffer);
                }
                else
                {
                    /* Check for presence of feature flag */
                    if (sb->feature_flags)
                    {
                        /* Feature flags present */
                        html_add_featureflag_lst(env, sb->feature_flags, env->collect_feature_flags.char_buffer);
                    }
                    else
                    {
                        /* No feature flag */
                        env->collect_feature_flags.char_buffer[0] = '\0';
                    }

                    /* Print out */
                    if (sb->flag & AUTOGEN_OBJ_IS_SHARED)
                    {
                        html_table_ref(env, "Shared subblock", 
                            html_obj_ver_pres(env, sb, &env->res->seq_list, &sb->ver, NULL), NULL, env->collect_feature_flags.char_buffer);
                    }
                    else
                    {
                        html_table_ref(env, 
                            html_obj_link(env, sb, NULL), 
                            html_obj_ver_pres(env, sb, &env->res->seq_list, &sb->ver, NULL), NULL, env->collect_feature_flags.char_buffer);
                    }
                }

                if (id_item->length == 16)
                {
#if (PMD_FILE_FORMAT >= 600)
                    html_table_dat(env, 0, 0, 0, 0, "0x%4.4llX", sb->id);
#else
                    html_table_dat(env, 0, 0, 0, 0, "0x%4.4X", sb->id);
#endif
                }
                else
                {
#if (PMD_FILE_FORMAT >= 600)
                    html_table_dat(env, 0, 0, 0, 0, "0x%2.2llX", sb->id);
#else
                    html_table_dat(env, 0, 0, 0, 0, "0x%2.2X", sb->id);
#endif
                }

                html_table_row_end(env);

                sb = autogen_obj_find_next_in_list(&sb_it);
            }

            fprintf(env->fhtml, "</table>\n");

            if (env->collect_feature_flags.head)
            {
                /* Dump list of collected feature flags */
                html_print_feature_flag_lst(env);
            }
            fprintf(env->fhtml, "<br><br>\n");
        }
    }

    /* generate constant tables */
    {
        autogen_obj* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
        tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            tbl_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        tbl = autogen_obj_find_in_list(&tbl_it, &env->res->tbl_list);
        if (tbl)
        {
            html_subsec(env, FALSE, sec1, ++sec2, 0, "Constant tables", "", "");

            sec3 = 0;

            while (tbl)
            {
                html_subsec(env, FALSE, sec1, sec2, ++sec3, "", 
                    html_obj_ver_pres(env, tbl, &env->res->tbl_list, &tbl->ver, NULL), 
                    html_obj_link(env, tbl, NULL));

                if (tbl->subtype == AUTOGEN_TBL_CONST)
                {
                    html_const_tbl(env, (autogen_tbl*)tbl);
                }
                else
                {
                    html_bit_tbl(env, (autogen_tbl*)tbl);
                }

                tbl = autogen_obj_find_next_in_list(&tbl_it);
            }
        }
    }

    /* generate ftd data table */
    {
        autogen_tbl* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_FTD;
        tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &env->res->tbl_list);
        while (tbl)
        {
            autogen_it ftd_it = INIT_ITERATOR;
            autogen_data* ftd = NULL;
            int sec3 = 0;

            html_subsec(env, FALSE, sec1, ++sec2, 0, "", 
                html_obj_ver_pres(env, (autogen_obj*)tbl, &env->res->tbl_list, &tbl->base.ver, NULL), 
                html_obj_link(env, (autogen_obj*)tbl, NULL));

            html_ftd_tbl(env, tbl);

            ftd_it.typemask    = AUTOGEN_OBJ_DATA;
            ftd_it.subtypemask = AUTOGEN_DATA_FTD;
            ftd_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

            ftd = (autogen_data*)autogen_obj_find_in_list(&ftd_it, &tbl->base.child_list);
            while (ftd)
            {
                html_subsec(env, FALSE, sec1, sec2, ++sec3, "", 
                    html_obj_ver_pres(env, (autogen_obj*)ftd, &tbl->base.child_list, &ftd->base.ver, NULL), 
                    html_obj_link(env, (autogen_obj*)ftd, NULL));

                html_ftd(env, ftd);

                ftd = (autogen_data*)autogen_obj_find_next_in_list(&ftd_it);
            }

            tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
        }
    }

    /* generate ppc table */
    {
        autogen_tbl* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_PPC;
        tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &env->res->tbl_list);
        while (tbl)
        {
            html_subsec(env, FALSE, sec1, ++sec2, 0, "", 
                html_obj_ver_pres(env, (autogen_obj*)tbl, &env->res->tbl_list, &tbl->base.ver, NULL), 
                html_obj_link(env, (autogen_obj*)tbl, NULL));

            html_ppc_tbl(env, tbl);

            tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
        }
    }

    /* generate notes*/
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        autogen_it note_it = INIT_ITERATOR;

        note_it.typemask    = AUTOGEN_OBJ_NOTE;
        note_it.subtypemask = AUTOGEN_NOTE_ANY;
        note_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            note_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        if (autogen_obj_find_in_list(&note_it, &env->res->note_list))
        {
            html_sec(env, FALSE, ++sec1, "Notes");
            sec2 = 0;

            html_notes(env);
        }
    }


    fprintf(env->fhtml, "</body>\n");
    fprintf(env->fhtml, "</html>\n");

    /* write autogen comments */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        time_t thetime;
        struct tm* today;
        char str_mon[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

        time(&thetime);
        today = localtime(&thetime);

        fprintf(env->fhtml, 
            "Generated with <a href=http://autogen.europe.nokia.com>autogen</a> %s on %2.2d-%s-%d %2.2d:%2.2d:%2.2d<br>\n", AUTOGEN_VERSION_NUMBER,
            today->tm_mday, str_mon[today->tm_mon], today->tm_year+1900,
            today->tm_hour, today->tm_min, today->tm_sec);
    }

    fclose(env->fhtml);
    env->fhtml = old_fhtml;

    while (env->gif_depth) /* back to html root */
    {
        chdir("..");
        env->gif_depth--;
    }

    /* write frame file */
    {
        FILE* fhtml;

        if (env->res->base.subtype == RESOURCE_SHARED)
        {
            sprintf(str_file, "i_%s_shared_frm.html", env->res->resnameshort_l);
        }
        else
        {
            sprintf(str_file, "i_%s_frm.html", env->res->resnameshort_l);
        }

        fhtml = fopen(str_file, "w");
        if (!fhtml)
        {
            printf("\nError: Unable to open file %s for writing. Aborting...\n", str_file);
            exit(1);
        }

        fprintf(fhtml, "<html>\n");

        fprintf(fhtml, " <head>\n");
        fprintf(fhtml, "  <title>%s\n", env->res->logical_name);
        fprintf(fhtml, "  </title>\n");
        fprintf(fhtml, " </head>\n");

        fprintf(fhtml, " <frameset cols='30%%,*'>\n");

        if (env->res->base.subtype == RESOURCE_SHARED)
        {
            fprintf(fhtml, "  <frame name=toc src='i_%s_shared_toc.html'>\n", env->res->resnameshort_l);
        }
        else
        {
            fprintf(fhtml, "  <frame name=toc src='i_%s_toc.html'>\n", env->res->resnameshort_l);
        }

        fprintf(fhtml, "  <frame name=isi src='%s#doc_start'>\n", env->filename);
        fprintf(fhtml, " </frameset>\n");

        fprintf(fhtml, "</html>\n");

        fclose(fhtml);
    }


    /* write toc file */
    {
        FILE* fhtml_old = env->fhtml;

        if (env->res->base.subtype == RESOURCE_SHARED)
        {
            sprintf(str_file, "i_%s_shared_toc.html", env->res->resnameshort_l);
        }
        else
        {
            sprintf(str_file, "i_%s_toc.html", env->res->resnameshort_l);
        }

        env->fhtml = fopen(str_file, "w");
        if (!env->fhtml)
        {
            printf("\nError: Unable to open file %s for writing. Aborting...\n", str_file);
            exit(1);
        }

        fprintf(env->fhtml, "<html>\n");
        fprintf(env->fhtml, "<head><title>%s</title></head>\n", env->res->logical_name);
        fprintf(env->fhtml, "<body leftmargin=20>\n");

        env->is_in_frame = TRUE;
        html_write_toc(env);
        env->is_in_frame = FALSE;

        fclose(env->fhtml);

        env->fhtml = fhtml_old;
    }
}


/*  Generates the HTML output for the string item pointed to by 'item'
*/

LOCAL void html_item_string(html_environment* env, autogen_item* item)
{
    autogen_item_string* item_string = (autogen_item_string*)item;

    char* str_count = pmd_heap_strdup_h(env->heap_handle, "");


    /* don't output an empty string */
    if (item->agg_n == 0 && !item->refname)
    {
        return;
    }

    /* build the count string */
    switch (item->agg_type)
    {
    case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
    case AGG_TYPE_DYNAMIC_ZEROTERMINATED:
        {
            str_count = pmd_heap_strdup_h(env->heap_handle, "?");
        }
        break;

    case AGG_TYPE_DYNAMIC_REF:
        {
            const char* str_ref = html_generate_reference_text(env, item);

            str_count = (char*)pmd_heap_alloc_h(env->heap_handle, 10 + strlen(str_ref));

            if (prop_has(&item->base, PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH))
            {
                sprintf(str_count, "%s + 1", str_ref);
            }
            else
            {
                strcpy(str_count, str_ref);
            }
        }
        break;

    case AGG_TYPE_FIXED_SINGLE:
        {
            str_count = pmd_heap_strdup_h(env->heap_handle, html_const_link(env, item_string->length_str, &item->base.ver));
        }
        break;

    case AGG_TYPE_FIXED_MULTIPLE:
        {
            const char* left_link  = html_const_link(env, item->agg_n_str, &item->base.ver);
            const char* right_link = html_const_link(env, item_string->length_str, &item->base.ver);

            str_count = (char*)pmd_heap_alloc_h(env->heap_handle, 10 + strlen(left_link) + strlen(right_link));

            strcpy(str_count, right_link);
            strcat(str_count, "x");
            strcat(str_count, left_link);
        }
        break;
    }

    html_table_row(env, FALSE);

    if (item->base.flag & (AUTOGEN_STRING_ASCII | AUTOGEN_STRING_BCD | AUTOGEN_STRING_GSM | AUTOGEN_STRING_UTF8))
    {
        html_table_dat(env, 0, 0, 0, 0, str_count);
    }
    else if (item->base.flag & AUTOGEN_STRING_UNICODE)
    {
        html_table_dat(env, 0, 0, 0, 0, "%s x 2", str_count);
    }

    html_table_par(env, item);
    html_table_var(env, item);


    fprintf(env->fhtml, "  <td valign=\"top\">");

    if (item->base.flag & AUTOGEN_STRING_ASCII)
    {
        fprintf(env->fhtml, "ASCII string<br>");
        fprintf(env->fhtml, "    %s\n", 
            item->base.flag & AUTOGEN_STRING_ZERO_TERMINATED ? 
            "String is zero-terminated" : "String is not zero-terminated");
    }
    else if (item->base.flag & AUTOGEN_STRING_UNICODE)
    {
        fprintf(env->fhtml, "Unicode string<br>");
        fprintf(env->fhtml, "    %s\n", 
            item->base.flag & AUTOGEN_STRING_ZERO_TERMINATED ? 
            "String is zero-terminated" : "String is not zero-terminated");
    }
    else if (item->base.flag & AUTOGEN_STRING_UTF8)
    {
        fprintf(env->fhtml, "UTF-8 string<br>");
        fprintf(env->fhtml, "    %s\n", 
            item->base.flag & AUTOGEN_STRING_ZERO_TERMINATED ? 
            "String is zero-terminated" : "String is not zero-terminated");
    }
    else if (item->base.flag & AUTOGEN_STRING_GSM)
    {
        fprintf(env->fhtml, "GSM string<br>");
    }
    else if (item->base.flag & AUTOGEN_STRING_BCD)
    {
        const char *bcd_map;
        char index;
        int size = 0;
        if (prop_has((autogen_obj*)item, PROPERTY_STRING_BCD_MAP))
        {
            bcd_map = prop_get_string((const autogen_obj*)item, PROPERTY_STRING_BCD_MAP);
            size = strlen(bcd_map);
            if (size > 16)
                fprintf(env->fhtml, "INVALID BCD MAP string<br>");
            else
            {
                fprintf(env->fhtml, "BCD MAP<br>");
                for (index = 0; index < 16; index++)
                {
                    if (index < size)
                    {
                        if (isprint (*(bcd_map+index)))
                        {
                            fprintf(env->fhtml, "[%02d] -> ASCII %03d '%c'<br>", index, *(bcd_map+index), *(bcd_map+index));
                        }
                        else
                        {
                            fprintf(env->fhtml, "[%02d] -> ASCII %03d<br>", index, *(bcd_map+index));
                        }
                    }
                    else
                    {
                        fprintf(env->fhtml, "[%02d] -> ASCII %03d<br>", index, 0);
                    }
                }
            }
        }
        else
        {
            fprintf(env->fhtml, "BCD string<br>");
        }
    }

    if (item->agg_type == AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE)
    {
        if (prop_has((autogen_obj*)item, PROPERTY_STRING_MAXIMUM_LENGTH))
        {
            fprintf(env->fhtml, "<br><br>String length: 1 to ");
            fprintf(env->fhtml, html_const_link(env, prop_get_string((autogen_obj*)item, PROPERTY_STRING_MAXIMUM_LENGTH), &item->base.ver));
        }
        else
        {
            fprintf(env->fhtml, 
                "<br><br>The string length is determined by the "
                "subblock/message length");
        }
    }
    else if (item->agg_type == AGG_TYPE_DYNAMIC_ZEROTERMINATED)
    {
        if (prop_has((autogen_obj*)item, PROPERTY_STRING_MAXIMUM_LENGTH))
        {
            fprintf(env->fhtml, "<br><br>String length: 1 to ");
            fprintf(env->fhtml, html_const_link(env, prop_get_string((autogen_obj*)item, PROPERTY_STRING_MAXIMUM_LENGTH), &item->base.ver));
        }
        else
        {
            fprintf(env->fhtml, 
                "<br><br>The string length is determined by the "
                "NULL terminator");
        }
    }

    html_comment(env, item->base.cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);

    fprintf(env->fhtml, "</td>\n");

    html_table_row_end(env);
}


/*  Generates the HTML output for the structure item pointed to by 'item'
*/

LOCAL void html_item_struct(html_environment* env, autogen_item* item)
{
    const autogen_item_struct* str_item = (autogen_item_struct*)item;

    autogen_it seq_it = INIT_ITERATOR;
    autogen_seq* str;
    unsigned int count;
    int first = TRUE;
    unsigned int size_type = AUTOGEN_SIZE_UNDEFINED;
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long size = 0;
#else
    unsigned int size = 0;
#endif
    char* str_size = pmd_heap_strdup_h(env->heap_handle, "");

    seq_it.typemask = AUTOGEN_OBJ_SB | AUTOGEN_OBJ_SEQ;
    seq_it.obj.name = str_item->seqname;
    seq_it.ver      = &item->base.ver;
    seq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
    seq_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_SEQ_IS_NOT_STRUCT | AUTOGEN_OBJ_IS_LEGACY;

    str = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &str_item->seqres->seq_list);
    while (str && (size_type == AUTOGEN_SIZE_UNDEFINED || size_type == AUTOGEN_SIZE_EXACT))
    {
#if (PMD_FILE_FORMAT >= 600)
        unsigned long long min_size = 0;
        unsigned long long max_size = 0;
#else
        unsigned int min_size = 0;
        unsigned int max_size = 0;
#endif

        unsigned int type = util_get_seq_size(str, &str->base.ver, &min_size, &max_size);

        if (type == AUTOGEN_SIZE_EXACT)
        {
            if (size_type == AUTOGEN_SIZE_EXACT)
            {
                if (size != min_size)
                {
                    size_type = AUTOGEN_SIZE_INTERVAL;
                }
            }
            else
            {
                size_type = AUTOGEN_SIZE_EXACT;
                size      = min_size;
            }
        }
        else
        {
            size_type = AUTOGEN_SIZE_INTERVAL;
        }

        str = (autogen_seq*)autogen_obj_find_next_in_list(&seq_it);
    }


    if (size_type == AUTOGEN_SIZE_EXACT)
    {
        str_size = (char*)pmd_heap_alloc_h(env->heap_handle, 20);

#if (PMD_FILE_FORMAT >= 600)
        sprintf(str_size, "%llu", size);
#else
        sprintf(str_size, "%hu", size);
#endif
    }
    else
    {
        str_size = (char*)pmd_heap_alloc_h(env->heap_handle, 25 + strlen(str_item->seqname));

        sprintf(str_size, "size of %s", str_item->seqname);
    }


    html_table_row(env, FALSE);

    switch (item->agg_type)
    {
    case AGG_TYPE_FIXED_SINGLE:
        {
            html_table_dat(env, 0, 0, 0, 0, str_size);
        }
        break;

    case AGG_TYPE_FIXED_MULTIPLE:
        {
            html_table_dat(env, 0, 0, 0, 0, "%s x %s", 
                str_size, html_const_link(env, item->agg_n_str, &item->base.ver));
        }
        break;

    case AGG_TYPE_DYNAMIC_REF:
        {
            const char* str_ref = html_generate_reference_text(env, item);

            html_table_dat(env, 0, 0, 0, 0, "%s x %s", str_ref, str_size);
        }
        break;

    case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
        {
            html_table_dat(env, 0, 0, 0, 0, "? x %s", str_size);
        }
        break;

    case AGG_TYPE_DYNAMIC_OPTIONAL:
        {
            html_table_dat(env, 0, 0, 0, 0, "0 or %s", str_size);
        }
        break;
    }

    html_table_par(env, item);
    html_table_var(env, item);

    fprintf(env->fhtml, "  <td valign=\"top\">");

    count = autogen_obj_count_in_list(&seq_it, &str_item->seqres->seq_list);

    str = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &str_item->seqres->seq_list);
    while (str)
    {
        if (first)
        {
            first = FALSE;
        }
        else
        {
            fprintf(env->fhtml, "<br>\n");
        }

        /* specify that the structure is from a shared file */
        if (str->base.flag & AUTOGEN_OBJ_IS_SHARED)
        {
            fprintf(env->fhtml, "  <a href=\"%s\">%s</a> (from '%s')",
                html_obj_link(env, (autogen_obj*)str->base.ptr, str->base.res),
                util_get_obj_name((autogen_obj*)str), str->base.res->base.name);
        }
        /* structure is in separate file */
        else if (str_item->seqres != env->res)
        {
            fprintf(env->fhtml, "<a href=\"%s\">%s %s</a>",
                html_obj_link(env, (autogen_obj*)str, str_item->seqres), str->base.name,
                count > 0 ? html_obj_ver_string(autogen_obj_ver_crop(&str->base.ver, &item->base.ver)) : "");
        }
        /* structure is in this file */
        else
        {
            fprintf(env->fhtml, "<a href=\"%s\">%s %s</a>",
                html_obj_link(env, (autogen_obj*)str, NULL), str->base.name,
                count > 0 ? html_obj_ver_string(autogen_obj_ver_crop(&str->base.ver, &item->base.ver)) : "");
        }

        str = (autogen_seq*)autogen_obj_find_next_in_list(&seq_it);
    }

    html_comment(env, item->base.cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);

    fprintf(env->fhtml, "</td>\n");

    html_table_row_end(env);
}


LOCAL void html_item_block(html_environment* env, autogen_item* item)
{
    autogen_item_block* item_block = (autogen_item_block*)item;

    html_table_row(env, FALSE);
    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);

    fprintf(env->fhtml, "  <td valign=\"top\">");

    switch (item->item_sub_type)
    {
    case BLOCK_PN_MSG:
        fprintf(env->fhtml, "Embedded message");
        break;
    case BLOCK_EXT_DECODER:
        fprintf(env->fhtml, "To be decoded using external decoder %s (function %s)",
            item_block->data1, item_block->data2);
        break;
    case BLOCK_RAW_DATA:
        fprintf(env->fhtml, "Raw data");
        break;
    case BLOCK_X_FILE:
        fprintf(env->fhtml, "X-file");
        break;
    case BLOCK_PROTOCOL:
        {
            const autogen_res* prot_res = util_get_protocol_res(item_block->data1);
            if (prot_res)
            {
                const char* prot_filename = prop_get_string_default((autogen_obj*)prot_res, PROPERTY_HTML_FILENAME, "");

                if ((prot_res->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML) || !prot_filename[0])
                {
                    fprintf(env->fhtml, "Protocol data, %s", prot_res->logical_name);
                }
                else
                {
                    fprintf(env->fhtml, "Protocol data, <a href=%s>%s</a>", prot_filename, prot_res->logical_name);
                }
            }
            else
            {
                fprintf(env->fhtml, "Protocol data, %s", item_block->data1);
            }
        }
        break;
    default:
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
            "Default case met in html_item_block(). item->base.flag is 0x%8.8X", item->base.flag);
    }

    html_comment(env, item->base.cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);

    fprintf(env->fhtml, "</td>\n");

    html_table_row_end(env);
}



/*  prints a new sub section, either in the table of contents or in the 
    document itself
*/

LOCAL void html_subsec(html_environment* env, int is_toc, 
                       int sec1, int sec2, int sec3, 
                       const char* title, const char* itemname,
                       const char* linkname)
    {
    int font = 4;
    int level = 3;

    if (!sec3)
        {
        level = 2;
        }

    fprintf(env->fhtml,  "<font size=\"%d\">", is_toc ? font-1 : font);

    fprintf(env->fhtml, "%d.%d.", sec1, sec2);
    if (sec3)
        {
        fprintf(env->fhtml, "%d.", sec3);
        }

    fprintf(env->fhtml, "&nbsp;&nbsp;%s", title);

    /* start link */
    if (linkname)
        {
        if (is_toc)
            {
            fprintf(env->fhtml, "<a %shref=\"%s\">", linkname[0] != '#' ? "target=isi " : "", linkname);
            }
        else
            {
            fprintf(env->fhtml, "<a name=\"%s\">", linkname[0] == '#' ? &linkname[1] : linkname);
            }
        }

    fprintf(env->fhtml, itemname);

    /* end link */
    if (linkname)
        {
        fprintf(env->fhtml, "</a>");
        }

    /* end header */
    fprintf(env->fhtml, "</font><br>\n");

    if (!is_toc)
        {
        fprintf(env->fhtml, "<br>\n");
        }
    }



/*  prints the table definition
*/

LOCAL void html_table(html_environment* env)
    {
    fprintf(env->fhtml, 
        "<table width=100%% cellspacing=\"0\" cellpadding=\"3\" "
        "border=\"1\" bordercolor=\"#000000\" "
        "bordercolordark=\"#000000\" bordercolorlight=\"#000000\">\n");
    }



/*  prints data for a table cell
*/

LOCAL void html_table_dat(html_environment* env, int courier, int grey, int bold, int width, const char* format, ...)
{
    va_list arg_list;
        
    fprintf(env->fhtml, "  <td valign=\"top\"%s", grey ? " color=\"#aaaaaa\"" : "");
    
    if (width)
        {
        fprintf(env->fhtml, "width=\"%d%%\"", width);
        }
    
    fprintf(env->fhtml, ">");
    
    if (courier)
    {
        fprintf(env->fhtml, "<font face=\"Courier\">");
    }

    va_start(arg_list, format);
    vsprintf(env->char_buffer, format, arg_list);
    va_end(arg_list);

    fprintf(env->fhtml, "%s%s%s", bold ? "<b>" : "", env->char_buffer, bold ? "</b>" : "");

    if (courier)
    {
        fprintf(env->fhtml, "</font>");
    }

    fprintf(env->fhtml, "</td>\n");
}



/*  prints a comment as table cell data
*/

LOCAL void html_table_com(html_environment* env, const autogen_cmt* cmt_list)
    {
    fprintf(env->fhtml, "  <td valign=\"top\">");

    html_comment(env, cmt_list, HTML_NEWLINE_NONE | HTML_SET_ITALIC);

    fprintf(env->fhtml, "&nbsp;</td>\n");
    }


/*  prints a comment
*/

LOCAL void html_table_ref(html_environment* env, 
                          const char* linkname, 
                          const char* itemname,
                          const autogen_cmt* cmt_list,
                          const char *postfixTxt)
    {
    fprintf(env->fhtml, "  <td valign=\"top\">\n");
    fprintf(env->fhtml, "    <a href=\"%s\">%s</a>\n", linkname, itemname);
 
    html_comment(env, cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);
    
    if (postfixTxt)
    {
        fprintf(env->fhtml, "%s", postfixTxt);
    }

    fprintf(env->fhtml, "  </td>\n");
    }


/*  prints a parameter name in a table cell
*/

LOCAL void html_table_par(html_environment* env, autogen_item* item)
    {
    if (item->base.flag & AUTOGEN_ITEM_IS_PART_OF_MERGE)
        {
        const autogen_item* merge = (autogen_item*)item->base.parent;
        unsigned int i;
        unsigned int offset = util_get_merge_offset(item);
        char str_bits[65];
        
        fprintf(env->fhtml, "  <td valign=\"top\">%s<br>", item->parname);
        
        for (i = 0; i < (unsigned int)merge->length; i++)
            {
            str_bits[i] = '-';
            
            if (i >= offset && 
                i < offset + (unsigned int)abs(item->length))
                {
                if (item->base.subtype == AUTOGEN_ITEM_FILLER)
                    {
                    str_bits[i] = '0';
                    }
                else
                    {
                    str_bits[i] = 'x';
                    }
                }
            else
                {
                str_bits[i] = '-';
                }
            }
        
        str_bits[merge->length] = 0;
        
        fprintf(env->fhtml, "<font face=\"Courier\">%s</font>", str_bits);
        fprintf(env->fhtml, "</td>\n");
        }
    else
        {
        if (item->base.feature_flags)
            {
            /* Feature flags present */
            html_add_featureflag_lst(env, item->base.feature_flags, env->collect_feature_flags.char_buffer);
            html_table_dat(env, 0, 0, 0, 0, "%s%s", item->parname[0] ? item->parname : "-", env->collect_feature_flags.char_buffer);
            }
        else 
            {
            /* No feature flags */
            html_table_dat(env, 0, 0, 0, 0, item->parname[0] ? item->parname : "-");
            }
        }
    }


/*  prints a new table row 
*/

LOCAL void html_table_row(html_environment* env, int fill)
    {
    fprintf(env->fhtml, " <tr%s>\n", fill ? " bgcolor=\"#aaaaaa\"" : "");
    }



/*  prints the end of a table row 
*/

LOCAL void html_table_row_end(html_environment* env)
    {
    fprintf(env->fhtml, " </tr>\n");
    }



/*  Inserts a new section in the table with the text 'format'. 
    If 'use_new_index' is TRUE, a new section color is used. Else, the current
    color is used.
*/

LOCAL void html_table_section_start(html_environment* env, int use_new_index, const char* format, ...)
    {
    va_list arg_list;
    char str_col[3][8] = { "#d0d0d0", "#a0a0a0", "#707070" };
    

    if (use_new_index)
        {
        ++env->section_index;
        }
    
    fprintf(env->fhtml, " <tr bgcolor=\"%s\">\n",
        env->section_index > 3 ? str_col[2] : str_col[env->section_index-1]);
    
    va_start(arg_list, format);
    vsprintf(env->char_buffer, format, arg_list);
    va_end(arg_list);
    
    fprintf(env->fhtml, "  <td valign=\"top\" colspan=4>%s</td>\n", env->char_buffer);
    fprintf(env->fhtml, " </tr>\n");
    }



/*  Ends a tables section. A colored table row is inserted with the text 
    'format'. The section number is decreased.
*/

LOCAL void html_table_section_end(html_environment* env, const char* format, ...)
    {
    va_list arg_list;
    char str_col[3][8] = { "#d0d0d0", "#a0a0a0", "#707070" };
    

    if (env->section_index == 0)
        {
        return;
        }
    
    fprintf(env->fhtml, " <tr bgcolor=\"%s\">\n",
        env->section_index > 3 ? str_col[2] : str_col[env->section_index-1]);
  
    va_start(arg_list, format);
    vsprintf(env->char_buffer, format, arg_list);
    va_end(arg_list);

    fprintf(env->fhtml, "  <td valign=\"top\" colspan=4>%s</td>\n", env->char_buffer);
    fprintf(env->fhtml, " </tr>\n");

    --env->section_index;
    }


/*  prints a variable name in a table cell
*/

LOCAL void html_table_var(html_environment* env, autogen_item* item)
    {    
    /* should the variable be printed at all? */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_HTML_INCLUDE_VARNAME_COLUMN))
        {
        return;
        }

    if (env->print_varname && item->varname[0] && 
        !(item->base.flag & (AUTOGEN_ITEM_IS_PART_OF_MERGE | AUTOGEN_OBJ_IS_NOT_GENERATED_ISIHDR)) &&
        prop_get_value_default((autogen_obj*)item, PROPERTY_ISIHDR_ARRAY_MARKER, ISIHDR_MARKER_ANYSIZE) != ISIHDR_DONT_GENERATE)
        {

        if (prop_has_valid_string((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED))
            {
            html_table_dat(env, 0, 0, 0, 0, "%s<br>%s", item->varname, 
                prop_get_string((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED));
            }
        else if (prop_has_valid_string((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED))
            {
            html_table_dat(env, 0, 0, 0, 0, "%s<br>%s", item->varname, 
                prop_get_string((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED));
            }
        else if (prop_has_valid_string((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_WORD_SIGNED))
            {
            html_table_dat(env, 0, 0, 0, 0, "%s<br>%s", item->varname, 
                prop_get_string((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_WORD_SIGNED));
            }
        else if (prop_has_valid_string((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED))
            {
            html_table_dat(env, 0, 0, 0, 0, "%s<br>%s", item->varname, 
                prop_get_string((autogen_obj*)item, PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED));
            }
        else
            {
            html_table_dat(env, 0, 0, 0, 0, item->varname);
            }
        }
    else
        {
        html_table_dat(env, 0, 0, 0, 0, "-");
        }
    }

/*  Generates the HTML output for the TraceRef sequence item pointed to by 
    'p_item'
*/

LOCAL void html_item_trcstruct(html_environment* env, autogen_item* item)
    {
    html_table_row(env, FALSE);

    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);
    html_table_par(env, item);
    html_table_row_end(env);
    }

LOCAL void html_item_value(html_environment* env, autogen_item* item)
    {
    autogen_item_value* item_val = (autogen_item_value*)item;

    html_table_row(env, FALSE);
    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);
    html_table_pres(env, &item_val->pres, &item_val->base.base, &item->base.ver, item->base.cmt_list, TRUE,
        prop_has((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE),
        prop_get_value_default((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE, 0),
        prop_get_string_default((autogen_obj*)item, PROPERTY_ITEM_DEFAULT_VALUE, ""),
        item->length);

    html_table_row_end(env);
    }

LOCAL void html_item_range(html_environment* env, autogen_item* item)
{
    autogen_it entry_it = INIT_ITERATOR;

    autogen_item_range_entry* entry = (autogen_item_range_entry*)autogen_obj_get_first_in_list(&item->base.child_list);

    int sign = item->length < 0;
    int ncar = (abs(item->length) + 3) / 4;
    char this_str[100];

    html_table_row(env, FALSE);
    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);

    fprintf(env->fhtml, "  <td valign=\"top\">\n");
    fprintf(env->fhtml, "   <font face=\"Courier\" size=\"3\">\n");

#if (PMD_FILE_FORMAT >= 600)
    sprintf(this_str, "0x%%%d.%dX-0x%%%d.%dllX: ", ncar, ncar, ncar, ncar);
#else
    sprintf(this_str, "0x%%%d.%dX-0x%%%d.%dX: ", ncar, ncar, ncar, ncar);
#endif

    entry_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    entry = (autogen_item_range_entry*)autogen_obj_find_in_list(&entry_it, &item->base.child_list);
    while (entry)
    {
        if (sign)
        {
#if (PMD_FILE_FORMAT >= 600)
            fprintf(env->fhtml, "%6lld to %6lld: ", (long long)entry->from, (long long)entry->to);
#else
            fprintf(env->fhtml, "%6d to %6d: ", (int)entry->from, (int)entry->to);
#endif
        }
        else
        {
            fprintf(env->fhtml, this_str, entry->from, entry->to);
        }

        if (entry->base.base.flag & AUTOGEN_RANGE_ENTRY_STRING)
        {
            autogen_it obj_it = INIT_ITERATOR;

            obj_it.typemask    = AUTOGEN_OBJ_CONST;
            obj_it.subtypemask = AUTOGEN_CONST_ANY;
            obj_it.obj.name    = entry->text;
            obj_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            obj_it.ver         = &entry->base.base.ver;
            obj_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

            if (env->res->base.subtype != RESOURCE_SHARED)
            {
                obj_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
            }

            if (autogen_obj_find_in_list(&obj_it, &env->res->const_list))
            {
                fprintf(env->fhtml, "<a href=\"#GENERAL_CONST\">%s</a>", entry->text);
            }
            else
            {
                fprintf(env->fhtml, entry->text);
            }
        }
        else if (entry->base.base.flag & AUTOGEN_RANGE_ENTRY_VALUE)
        {
            fprintf(env->fhtml, "Real_val = Field_val");
        }
        else if (entry->base.base.flag & AUTOGEN_RANGE_ENTRY_VALUE_EX)
        {
            fprintf(env->fhtml, "Real_val = ");

            if (entry->pres.scale != 1.0)
            {
                fprintf(env->fhtml, "%5.2f * ", entry->pres.scale);
            }

            fprintf(env->fhtml, "Field_val");

            if (entry->pres.offset > 0)
            {
                fprintf(env->fhtml, " + %5.2f", entry->pres.offset);
            }
            else if (entry->pres.offset < 0)
            {
                fprintf(env->fhtml, " - %5.2f", -entry->pres.offset);
            }

            if (entry->pres.unit && entry->pres.unit[0])
            {
                fprintf(env->fhtml, " [%s]", entry->pres.unit);
            }
        }

        fprintf(env->fhtml, "<br>\n");

        entry = (autogen_item_range_entry*)autogen_obj_find_next_in_list(&entry_it);
    }

    fprintf(env->fhtml, "   </font>\n");

    html_comment(env, item->base.cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);

    fprintf(env->fhtml, "  </td>\n");

    html_table_row_end(env);
}

LOCAL void html_item_timestamp(html_environment* env, autogen_item* item)
    {
    html_table_row(env, FALSE);
    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);

    fprintf(env->fhtml, "  <td valign=\"top\">");

    if (item->item_sub_type == PMD_TIMESTAMP_TYPE_STI_XTI)
        {
        fprintf(env->fhtml, "Tracebox timestamp");
        }
    else if (item->item_sub_type == PMD_TIMESTAMP_TYPE_DSP5)
        {
        fprintf(env->fhtml, "DSP 5.0 timestamp");
        }
    else if (item->item_sub_type == PMD_TIMESTAMP_TYPE_MCU)
        {
        fprintf(env->fhtml, "OS Ticks timestamp");
        }
    else if (item->item_sub_type == PMD_TIMESTAMP_TYPE_GSM_FRAMES)
        {
        fprintf(env->fhtml, "GSM Frame");
        }
    else if (item->item_sub_type == PMD_TIMESTAMP_TYPE_CDSP)
        {
        fprintf(env->fhtml, "WCDMA CDSP timestamp");
        }
    else if (item->item_sub_type == PMD_TIMESTAMP_TYPE_ADSP)
        {
        fprintf(env->fhtml, "ADSP timestamp");
        }
    else if (item->item_sub_type == PMD_TIMESTAMP_TYPE_CDMA_SYSTEM)
        {
        fprintf(env->fhtml, "CDMA system timestamp");
        }
    else
        {
        fprintf(env->fhtml, "Unknown timestamp");
        }
    
    html_comment(env, item->base.cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);

    fprintf(env->fhtml, "</td>\n");

    html_table_row_end(env);
    }


LOCAL void html_item_pointer(html_environment* env, autogen_item* item)
    {
    html_table_row(env, FALSE);
    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);
    html_table_com(env, item->base.cmt_list);
    html_table_row_end(env);
    }

LOCAL void html_item_printf(html_environment* env, autogen_item* item)
{
    /* Output printf statement */
    html_table_row(env, TRUE);
    html_table_size(env, item);
    html_table_par(env, item);
    html_table_var(env, item);

    /* Comment section */
    fprintf(env->fhtml, "  <td valign=\"top\">");
    fprintf(env->fhtml, "Printf format string: '%s'", ((autogen_item_printf *)item)->format);
    html_comment(env, item->base.cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);
    fprintf(env->fhtml, "</td>\n");

    html_table_row_end(env);

    /* Output arguments */
    html_seq_items(env, &item->base.child_list);

    /* Blank line */
    html_table_row(env, TRUE);
    fprintf(env->fhtml, "  <td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>\n");
    html_table_row_end(env);
}


/*  Writes the table of contents to the HTML file. If the is_in_frame is TRUE,
    links are made to the contents frame, else they are just local.
*/

LOCAL void html_write_toc(html_environment* env)
{
    autogen_obj* obj;
    int sec1 = 0, sec2 = 0, sec3 = 0;

    /* generate introduction */
    html_generate_introduction_section(env, &sec1, TRUE);

    /* generate message header */
    html_generate_message_header_section(env, &sec1, TRUE);

    /* generate toc - message list */
    html_generate_message_section(env, &sec1, TRUE);

    /* generate toc - trace list */
    html_generate_traces(env, &sec1, TRUE);

    /* generate sequences */
    html_generate_sequence_section(env, &sec1, TRUE);

    /* generate toc - symbol information */
    html_sec(env, TRUE, ++sec1, "Symbol Information");

    sec2 = 0;


    /* generate toc - symbol information - constants */
    {
        autogen_it const_it = INIT_ITERATOR;

        const_it.typemask = AUTOGEN_OBJ_CONST;
        const_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            const_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        if (autogen_obj_find_in_list(&const_it, &env->res->const_list))
        {
            char* fileref = (char*)pmd_heap_alloc_h(env->heap_handle, 25 + strlen(env->filename));

            if (env->is_in_frame)
            {
                strcpy(fileref, env->filename);
            }

            strcat(fileref, "#GENERAL_CONST");

            html_subsec(env, TRUE, sec1, ++sec2, 0, "", "Constants", fileref);
        }
    }

    /* generate toc - symbol information - message IDs */
    html_generate_message_id_section(env, sec1, &sec2, TRUE);

    /* generate toc - symbol information - subblock IDs */
    if (!env->res->sb_id_section || !(env->res->sb_id_section->flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML))
    {
        autogen_it sb_it = INIT_ITERATOR;

        sb_it.typemask  = AUTOGEN_OBJ_SB;
        sb_it.flagnone  = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            sb_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        if (autogen_obj_find_in_list(&sb_it, &env->res->seq_list))
        {
            char fileref[256] = "";

            if (env->is_in_frame)
            {
                strcpy(fileref, env->filename);
            }

            strcat(fileref, "#SB_ID");

            html_subsec(env, TRUE, sec1, ++sec2, 0, "", "Subblock ID's", fileref);
        }
    }

    /* generate toc - symbol information - constant tables */
    {
        autogen_obj* tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
        tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            tbl_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        tbl = autogen_obj_find_in_list(&tbl_it, &env->res->tbl_list);
        if (tbl)
        {
            html_subsec(env, TRUE, sec1, ++sec2, 0, "Constant tables", "", "");

            sec3 = 0;

            while (tbl)
            {
                html_subsec(env, TRUE, sec1, sec2, ++sec3, "",
                    html_obj_ver_pres(env, tbl, &env->res->tbl_list, &tbl->ver, NULL),
                    html_obj_link(env, tbl, env->is_in_frame ? env->res : NULL));

                tbl = autogen_obj_find_next_in_list(&tbl_it);
            }
        }
    }

    /* generate toc - symbol information - ftd data tables */
    {
        autogen_it ftd_it = INIT_ITERATOR;

        ftd_it.typemask    = AUTOGEN_OBJ_TBL;
        ftd_it.subtypemask = AUTOGEN_TBL_FTD;
        ftd_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            ftd_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        obj = autogen_obj_find_in_list(&ftd_it, &env->res->tbl_list);
        while (obj)
        {
            html_subsec(env, TRUE, sec1, ++sec2, 0, "", 
                html_obj_ver_pres(env, obj, &env->res->tbl_list, &obj->ver, NULL),
                html_obj_link(env, obj, env->is_in_frame ? env->res : NULL));

            obj = autogen_obj_find_next_in_list(&ftd_it);
        }
    }    

    /* generate toc - symbol information - ppc tables */
    {
        autogen_it ppc_it = INIT_ITERATOR;

        ppc_it.typemask    = AUTOGEN_OBJ_TBL;
        ppc_it.subtypemask = AUTOGEN_TBL_PPC;
        ppc_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML | AUTOGEN_OBJ_IS_LEGACY;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            ppc_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        obj = autogen_obj_find_in_list(&ppc_it, &env->res->tbl_list);
        while (obj)
        {
            html_subsec(env, TRUE, sec1, ++sec2, 0, "", 
                html_obj_ver_pres(env, obj, &env->res->tbl_list, &obj->ver, NULL),
                html_obj_link(env, obj, env->is_in_frame ? env->res : NULL));

            obj = autogen_obj_find_next_in_list(&ppc_it);
        }

        fprintf(env->fhtml, "<br>\n");
    }


    /* generate toc - symbol information - notes */
    if (!prop_has((autogen_obj*)env->res, PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT))
    {
        autogen_it note_it = INIT_ITERATOR;

        note_it.typemask    = AUTOGEN_OBJ_NOTE;
        note_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

        if (env->res->base.subtype != RESOURCE_SHARED)
        {
            note_it.flagnone |= AUTOGEN_OBJ_IS_SHARED;
        }

        obj = autogen_obj_find_in_list(&note_it, &env->res->note_list);
        if (obj)
        {
            html_sec(env, TRUE, ++sec1, "Notes");
        }
    }    

    /* end file */
    if (!env->is_in_frame)
    {
        fprintf(env->fhtml, "<br><br>\n");
    }
}


/*  The main function that generates the entire HTML output 
*/

void output_html(void)
{
    autogen_it res_it = INIT_ITERATOR;
    html_environment env;

    env.print_varname                     = TRUE;
    env.section_index                     = 0;
    env.heap_handle                       = pmd_heap_init_h(80000);
    env.char_buffer                       = (char*)pmd_heap_alloc_h(env.heap_handle, 65536);
    env.collect_feature_flags.char_buffer = (char*)pmd_heap_alloc_h(env.heap_handle, 65536);
    env.collect_feature_flags.tag_count   = 0;
    env.collect_feature_flags.head        = NULL;
    env.collect_feature_flags.tail        = NULL;

    printf("Generating HTML documents...\n");
    fprintf(g_log, "\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");
    fprintf(g_log, "Generating HTML documents\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");


    res_it.typemask = AUTOGEN_OBJ_RES;


    /* generate html pages for all resources */
    {
        res_it.subtypemask = RESOURCE_ANY;
        res_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

        env.res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        while (env.res)
        {
            if (env.res->base.subtype != RESOURCE_UNKNOWN)
            {
                env.filename = prop_get_string((autogen_obj*)env.res, PROPERTY_HTML_FILENAME);
                if (env.filename[0])
                {
                    html_res(&env);
                }
            }

            env.res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
        }
    }

    pmd_heap_free_h(env.heap_handle);
}

LOCAL void html_ver_info(html_environment* env, const autogen_obj* obj)
    {
    if (obj->ver.system == AUTOGEN_VERSION_DSP)
        {
        if (obj->ver.type == AUTOGEN_OBJ_VERSION_INTERVAL)
            {
            fprintf(env->fhtml, 
                "<font size=\"2\">"
                "Valid from server version %03hu.%03hu.%03hu until %03hu.%03hu.%03hu</font><br><br>\n",
                obj->ver.from[0], obj->ver.from[1], obj->ver.from[2], obj->ver.to[0], obj->ver.to[1], obj->ver.to[2]);
            }
        else if (obj->ver.type == AUTOGEN_OBJ_VERSION_TO)
            {
            fprintf(env->fhtml, 
                "<font size=\"2\">"
                "Obsolete from server version %03hu.%03hu.%03hu</font><br><br>\n",
                obj->ver.to[0], obj->ver.to[1], obj->ver.to[2]);
            }
        else if (obj->ver.type == AUTOGEN_OBJ_VERSION_FROM)
            {
            fprintf(env->fhtml, 
                "<font size=\"2\">"
                "Valid from server version %03hu.%03hu.%03hu</font><br><br>\n",
                obj->ver.from[0], obj->ver.from[1], obj->ver.from[2]);
            }
        }
    else
        {
        if (obj->ver.type == AUTOGEN_OBJ_VERSION_INTERVAL)
            {
            fprintf(env->fhtml, 
                "<font size=\"2\">"
                "Valid from ISI version %03hu.%03hu until %03hu.%03hu</font><br><br>\n",
                obj->ver.from[0], obj->ver.from[1], obj->ver.to[0], obj->ver.to[1]);
            }
        else if (obj->ver.type == AUTOGEN_OBJ_VERSION_TO)
            {
            fprintf(env->fhtml, 
               "<font size=\"2\">"
               "Obsolete from ISI version %03hu.%03hu</font><br><br>\n",
               obj->ver.to[0], obj->ver.to[1]);
            }
        else if (obj->ver.type == AUTOGEN_OBJ_VERSION_FROM)
            {
            fprintf(env->fhtml, 
                "<font size=\"2\">"
                "Valid from ISI version %03hu.%03hu</font><br><br>\n",
                obj->ver.from[0], obj->ver.from[1]);
            }
        }
    }


/* Generates the HTML output for the SB List pointed to by 'item' 
*/

LOCAL void html_item_lst(html_environment* env, autogen_item* item)
{
    autogen_it ref_it = INIT_ITERATOR;
    autogen_seq_ref* ref = NULL;
    int first = TRUE;
    unsigned int idsize = 1;


    if (item->base.flag & AUTOGEN_LST_SB_HAVE_WORD_IDS)
    {
        idsize = 2;
    }

    html_table_row(env, FALSE);

    switch (item->agg_type)
    {
    case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
        {
            if (idsize == 1 || (item->base.flag & AUTOGEN_LST_SBDATA))
            {
                html_table_dat(env, 0, 0, 0, 0, "?");
            }
            else
            {
                html_table_dat(env, 0, 0, 0, 0, "? x %u", idsize);
            }

            html_table_par(env, item);
        }
        break;

    case AGG_TYPE_DYNAMIC_REF:
        {
            const char* str_ref = html_generate_reference_text(env, item);

            if (item->base.flag & AUTOGEN_LST_SBDATA)
            {
                html_table_dat(env, 0, 0, 0, 0, "?");
            }
            else if (idsize == 1)
            {
                html_table_dat(env, 0, 0, 0, 0, str_ref);
            }
            else
            {
                html_table_dat(env, 0, 0, 0, 0, "%s x %u", str_ref, idsize);
            }

            if (item->base.feature_flags)
            {
                /* Feature flags present */
                html_add_featureflag_lst(env, item->base.feature_flags, env->collect_feature_flags.char_buffer);
                html_table_dat(env, 0, 0, 0, 0, "%s%s. If %s > 0", item->parname, env->collect_feature_flags.char_buffer, str_ref);
            }
            else 
            {
                /* No feature flags */
                html_table_dat(env, 0, 0, 0, 0, "%s. If %s > 0", item->parname, str_ref);
            }
        }
        break;

    case AGG_TYPE_FIXED_SINGLE:
        {
            if (item->base.flag & AUTOGEN_LST_SBDATA)
            {
                html_table_dat(env, 0, 0, 0, 0, "?");
            }
            else
            {
                html_table_dat(env, 0, 0, 0, 0, "%u",idsize);
            }

            if (item->base.feature_flags)
            {
                /* Feature flags present */
                html_add_featureflag_lst(env, item->base.feature_flags, env->collect_feature_flags.char_buffer);
                html_table_dat(env, 0, 0, 0, 0, "%s%s", item->parname, env->collect_feature_flags.char_buffer);
            }
            else 
            {
                /* No feature flags */
                html_table_dat(env, 0, 0, 0, 0, "%s", item->parname);
            }
        }
        break;

    case AGG_TYPE_FIXED_MULTIPLE:
        {
            if (item->base.flag & AUTOGEN_LST_SBDATA)
            {
                html_table_dat(env, 0, 0, 0, 0, "?");
            }
            else if (idsize == 1)
            {
                html_table_dat(env, 0, 0, 0, 0, 
                    html_const_link(env, item->agg_n_str, &item->base.ver));
            }
            else
            {
                html_table_dat(env, 0, 0, 0, 0, "%s x %u",
                    html_const_link(env, item->agg_n_str, &item->base.ver), idsize);
            }

            if (item->base.feature_flags)
            {
                /* Feature flags present */
                html_add_featureflag_lst(env, item->base.feature_flags, env->collect_feature_flags.char_buffer);
                html_table_dat(env, 0, 0, 0, 0, "%s%s", item->parname, env->collect_feature_flags.char_buffer);
            }
            else 
            {
                /* No feature flags */
                html_table_dat(env, 0, 0, 0, 0, "%s", item->parname);
            }
        }
        break;

    default:
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                "Default case met in html_item_lst(). item->agg_type is %u", item->agg_type);
        }
    }

    html_table_var(env, item);

    fprintf(env->fhtml, "  <td valign=\"top\">\n");

    html_comment(env, item->base.cmt_list, HTML_NEWLINE_AFTER | HTML_SET_ITALIC);


    if (item->base.flag & AUTOGEN_LST_FTD)
    {
        fprintf(env->fhtml, "  COMM_FTD_DATA_*");

        first = FALSE;
    }
    else if (item->base.flag & AUTOGEN_LST_PPC)
    {
        fprintf(env->fhtml, "  MON_PPC_*");

        first = FALSE;
    }
#if ((defined AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN) || (defined AUTOGEN_GENERATE_SOS_FTD_SB_TEMPLATES))
    else if (item->base.flag & AUTOGEN_LST_SOS_FTD)
        fprintf(env->fhtml, "  SOS_FTD_DATA_*");

        first = FALSE;
#endif

    /* find first subblock reference for the item */
    ref_it.typemask    = AUTOGEN_OBJ_REF;
    ref_it.subtypemask = AUTOGEN_OBJ_SB;
    ref_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    ref = (autogen_seq_ref*)autogen_obj_find_in_list(&ref_it, &item->base.child_list);
    while (ref)
    {
        autogen_seq* str = ref->seqptr;
        if (!(str->base.flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML))
        {
            char insertion_ver[256] = "";

            if (first)
            {
                first = FALSE;
            }
            else
            {
                fprintf(env->fhtml, "<br>\n");
            }

            /* add the version interval, within which the 
            subblock should should be inserted.
            only relevant for when subblocks are inserted using the 
            SB_LST_ENTRY_VER macro
            */
            if (!autogen_obj_ver_is_exact(&ref->base.ver, &item->base.ver))
            {
                sprintf(insertion_ver, " %s", html_obj_ver_string(&ref->base.ver));
            }

            /* subblock is placed in the current resource */
            if (ref->seqptr->base.res == item->seq->base.res)
            {
                if (item->base.flag & AUTOGEN_LST_SBID) 
                {
                    /* No links when we have subblock IDs */
#if (PMD_FILE_FORMAT >= 600)
                    char *formatString = (idsize == 2 ? "%s (= 0x%4.4llX)" : "%s (= 0x%2.2llX)");
#else
                    char *formatString = (idsize == 2 ? "%s (= 0x%4.4X)" : "%s (= 0x%2.2X)");
#endif
                    fprintf(env->fhtml, formatString, 
                        html_obj_ver_pres(env, (autogen_obj*)str, &item->seq->base.res->seq_list, &ref->base.ver, &ref->base.ver),
                        ref->base.id);
                }
                else
                {
                    /* Subblocks */
                    fprintf(env->fhtml, "  <a href=\"%s\">%s</a>",
                        html_obj_link(env, (autogen_obj*)str, NULL),
                        html_obj_ver_pres(env, (autogen_obj*)str, &item->seq->base.res->seq_list, &ref->base.ver, &ref->base.ver));
                }
            }
            /* subblock is placed in shared file */
            else
            {
                if (item->base.flag & AUTOGEN_LST_SBID) 
                {
                    /* No links when we have subblock IDs */
#if (PMD_FILE_FORMAT >= 600)
                    char *formatString = (idsize == 2 ? "%s%s (= 0x%4.4llX) (from '%s')" : "%s%s (= 0x%2.2llX) (from '%s')");
#else
                    char *formatString = (idsize == 2 ? "%s%s (= 0x%4.4X) (from '%s')" : "%s%s (= 0x%2.2X) (from '%s')");
#endif
                    fprintf(env->fhtml, formatString, 
                        util_get_obj_name((autogen_obj*)str), insertion_ver,
                        ref->base.id,
                        ref->seqptr->base.res->base.name);
                }
                else
                {
                    /* Subblocks */
                    /* specify that the subblock is from own shared file */
                    fprintf(env->fhtml, "  <a href=\"%s%s\">%s%s</a> (from '%s')", html_up_level(env),
                        html_obj_link(env, (autogen_obj*)str->base.ptr, str->base.res),
                        util_get_obj_name((autogen_obj*)str), insertion_ver, 
                        ref->seqptr->base.res->base.name);
                }
            }
        }

        ref = (autogen_seq_ref*)autogen_obj_find_next_in_list(&ref_it);
    }

    if (first)
    {
        fprintf(env->fhtml, "&nbsp;");
    }

    fprintf(env->fhtml, "</td>\n");

    html_table_row_end(env);
}


LOCAL const char* html_obj_ver_string(const autogen_ver* ver)
{
    static char s_html_ver_str[25];

    strcpy(s_html_ver_str, "");

    if (ver)
    {
        if (ver->system == AUTOGEN_VERSION_DSP)
        {
            if (ver->type == AUTOGEN_OBJ_VERSION_TO)
            {
                sprintf(s_html_ver_str, "(until %03hu.%03hu.%03hu)", ver->to[0], ver->to[1], ver->to[2]);
            }
            else if (ver->type == AUTOGEN_OBJ_VERSION_INTERVAL)
            {
                sprintf(s_html_ver_str, "(%03hu.%03hu.%03hu until %03hu.%03hu.%03hu)", ver->from[0], ver->from[1], ver->from[2], ver->to[0], ver->to[1], ver->to[2]);
            }
            else if (ver->type == AUTOGEN_OBJ_VERSION_FROM)
            {
                sprintf(s_html_ver_str, "(from %03hu.%03hu.%03hu)", ver->from[0], ver->from[1], ver->from[2]);
            }
        }
        else
        {
            if (ver->type == AUTOGEN_OBJ_VERSION_TO)
            {
                sprintf(s_html_ver_str, "(until %03hu.%03hu)", ver->to[0], ver->to[1]);
            }
            else if (ver->type == AUTOGEN_OBJ_VERSION_INTERVAL)
            {
                sprintf(s_html_ver_str, "(%03hu.%03hu until %03hu.%03hu)", ver->from[0], ver->from[1], ver->to[0], ver->to[1]);
            }
            else if (ver->type == AUTOGEN_OBJ_VERSION_FROM)
            {
                sprintf(s_html_ver_str, "(from %03hu.%03hu)", ver->from[0], ver->from[1]);
            }
        }
    }

    return s_html_ver_str;
}

LOCAL const char* html_obj_ver_pres(html_environment* env, const autogen_obj* obj, autogen_obj_list* obj_list, const autogen_ver* ver, const autogen_ver* parent_ver)
{
    autogen_it obj_it = INIT_ITERATOR;
    const char* str_ver = html_obj_ver_string(ver);
    char* html_obj_ver_pres = pmd_heap_alloc_h(env->heap_handle, 25 + strlen(obj->name) + strlen(obj->base_obj->name) + strlen(str_ver));

    obj_it.typemask    = obj->type;
    obj_it.obj.name    = obj->name;
    obj_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    if (parent_ver)
    {
        obj_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        obj_it.ver      = parent_ver;
    }

    if (autogen_obj_count_in_list(&obj_it, obj_list) > 1)
    {
        if (obj->type == AUTOGEN_OBJ_MSG && (obj->flag & AUTOGEN_MSG_IS_SUBMSG))
        {
            if (prop_has(&obj->res->base, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
            {
                sprintf(html_obj_ver_pres, "%s %s", obj->name, str_ver);
            }
            else
            {
                sprintf(html_obj_ver_pres, "%s (%s) %s", obj->name, obj->base_obj->name, str_ver);
            }
        }
        else
        {
            sprintf(html_obj_ver_pres, "%s %s", util_get_obj_name(obj), str_ver);
        }
    }
    else
    {
        if (obj->type == AUTOGEN_OBJ_MSG && (obj->flag & AUTOGEN_MSG_IS_SUBMSG))
        {
            if (prop_has((autogen_obj*)((autogen_seq*)obj)->base.res, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
            {
                strcpy(html_obj_ver_pres, obj->name);
            }
            else
            {
                sprintf(html_obj_ver_pres, "%s (%s)", obj->name, obj->base_obj->name);
            }
        }
        else
        {
            if ((ver->to[0] < 0x0100) || (ver->from[0] > 0) || (ver->from[1] > 0))
            {
                sprintf(html_obj_ver_pres, "%s %s", util_get_obj_name(obj), str_ver);
            }
            else
            {
                strcpy(html_obj_ver_pres, util_get_obj_name(obj));
            }
        }
    }

    return html_obj_ver_pres;
}

LOCAL const char* html_obj_link(html_environment* env, const autogen_obj* obj, const autogen_res* res)
{
    char* html_obj_version_link;
    unsigned int size = 25 + strlen(obj->name) + strlen(obj->base_obj->name);
    const char* str_filename = NULL;
    const char* gif_location = NULL;
    int has_html_dir_prop    = FALSE;
    int add_dir_slash        = FALSE;
    char ch;

    /* only add file name if object belongs to external resource */
    if (res)
    {
        if (prop_has(obj->parent, PROPERTY_HTML_DIRECTORY_PATH))
        {
            gif_location = (char*)prop_get_string(obj->parent, PROPERTY_HTML_DIRECTORY_PATH);
            has_html_dir_prop = TRUE;
            ch = *(gif_location+(strlen(gif_location)-1));
            if (ch != '/')
            {
                add_dir_slash = TRUE;
                size += 1; /* include length of '/' */
            }
            size += strlen(gif_location); 
        }
        str_filename = prop_get_string_default(&res->base, PROPERTY_HTML_FILENAME, "");
        size += strlen(str_filename);
    }
    else
    {
        str_filename = pmd_heap_strdup_h(env->heap_handle, "");
    }

    html_obj_version_link = (char*)pmd_heap_alloc_h(env->heap_handle, size);

    if (has_html_dir_prop)
    {
        strcpy(html_obj_version_link, gif_location);
        if (add_dir_slash)
        {
            strcat(html_obj_version_link, "/");
        }
        strcat(html_obj_version_link, str_filename);
    }
    else
    {
        strcpy(html_obj_version_link, str_filename);
    }

    if (obj->base_obj != obj)
    {
        if (obj->type == AUTOGEN_OBJ_MSG && prop_has(&obj->res->base, PROPERTY_SUBMSG_NAMES_ARE_UNIQUE))
        {
            strcat(html_obj_version_link, "#");
            strcat(html_obj_version_link, obj->name);
        }
        else
        {
            strcat(html_obj_version_link, "#");
            strcat(html_obj_version_link, obj->base_obj->name);
            strcat(html_obj_version_link, "_");
            strcat(html_obj_version_link, obj->name);
        }
    }
    else if (obj->type == AUTOGEN_OBJ_TRACE)
    {
        strcat(html_obj_version_link, "#");
        strcat(html_obj_version_link, obj->parent->name);
        strcat(html_obj_version_link, "_");
        strcat(html_obj_version_link, obj->name);
    }
    else
    {
        strcat(html_obj_version_link, "#");
        strcat(html_obj_version_link, obj->name);
    }

    /* add version info */
    if (obj->ver.from[0] != 0 || obj->ver.from[1] != 0)
    {
        sprintf(html_obj_version_link + strlen(html_obj_version_link),
            "_%3.3d_%3.3d", obj->ver.from[0], obj->ver.from[1]);
    }

    return html_obj_version_link;
}                                        
                                        

LOCAL void html_comment(html_environment* env, const autogen_cmt* cmt_list, unsigned int flag)
    {
    const autogen_cmt* cmt = cmt_list;
    int first = TRUE;
    autogen_comment_id last_id = COMMENT_NONE;
    int disp_cmt = TRUE;

    while (cmt)
        {
        if (cmt->id == COMMENT_PROPERTY_ALL_OUTPUTS || cmt->id == COMMENT_PROPERTY_HTML_ONLY)
            {
            disp_cmt = TRUE;
            }
        else if (cmt->id == COMMENT_PROPERTY_ISIHDR_ONLY || cmt->id == COMMENT_PROPERTY_HTML_DISABLE)
            {
            disp_cmt = FALSE;
            }
        else
            {
            if (disp_cmt)
                {
                if (cmt->id == COMMENT_TEXT ||
                    cmt->id == COMMENT_PARAGRAPH ||
                    cmt->id == COMMENT_BULLET ||
                    cmt->id == COMMENT_WEB_LINK ||
                    cmt->id == COMMENT_NEWLINE ||
                    cmt->id == COMMENT_LINK_TYPE)
                    {
                    /* initialize comment */
                    if (first)
                        {
                        if (flag & HTML_NEWLINE_BEFORE)
                            {
                            fprintf(env->fhtml, "<br><br>");
                            }

                        if (flag & HTML_SET_FONT)
                            {
                            fprintf(env->fhtml, "<font size=\"2\">");
                            }

                        if (flag & HTML_SET_ITALIC)
                            {
                            fprintf(env->fhtml, "<i>");
                            }

                        first = FALSE;
                        }

                    /* print the comment */
                    if (cmt->id == COMMENT_TEXT || cmt->id == COMMENT_PARAGRAPH)
                        {
                        if (last_id == COMMENT_PARAGRAPH || last_id == COMMENT_BULLET)
                            {
                            fprintf(env->fhtml, "<br>");
                            }

                        fprintf(env->fhtml, "%s", cmt->comment);
                        }
                    else if (cmt->id == COMMENT_WEB_LINK)
                        {
                        if (last_id == COMMENT_PARAGRAPH)
                            {
                            fprintf(env->fhtml, "<br>");
                            }

                        fprintf(env->fhtml, "<a href=\"http://%s\">%s</a>", cmt->comment, cmt->comment);
                        }
                    /* add the link */
                    else if (cmt->id == COMMENT_LINK_TYPE)
                        {
                        if (cmt->linktype == AUTOGEN_OBJ_CONST)
                            {
                            fprintf(env->fhtml, "<a href=\"#GENERAL_CONST\">%s</a>", cmt->linkname);
                            }
                        else
                            {
                            autogen_it obj_it = INIT_ITERATOR;
                            autogen_obj* obj = NULL;
                            autogen_obj_list* lst = NULL;

                            /* find object that matches link criterias */
                            obj_it.typemask    = cmt->linktype;
                            obj_it.obj.name    = cmt->linkname;
                            obj_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                            obj_it.ver         = &cmt->linkver;
                            obj_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

                            switch (obj_it.typemask)
                                {
                                case AUTOGEN_OBJ_TBL:
                                    {
                                    lst = &env->res->tbl_list;
                                    }
                                    break;

                                case AUTOGEN_OBJ_SEQ:
                                case AUTOGEN_OBJ_SB:
                                case AUTOGEN_OBJ_SB_TEMPLATE:
                                    {
                                    lst = &env->res->seq_list;
                                    }
                                    break;

                                case AUTOGEN_OBJ_CONST:
                                    {
                                    lst = &env->res->const_list;
                                    }
                                    break;

                                case AUTOGEN_OBJ_MSG:
                                    {
                                    lst = &env->res->msg_list;
                                    }
                                    break;

                                case AUTOGEN_OBJ_NOTE:
                                    {
                                    lst = &env->res->note_list;
                                    }
                                    break;
                                }

                            if (lst)
                                {
                                obj = autogen_obj_find_in_list(&obj_it, lst);
                                }
                            /* If submessage, find submessage */
                            if (obj && obj->type == AUTOGEN_OBJ_MSG_BASE && cmt->linksubname && cmt->linksubname[0])
                            {
                                obj_it.obj.name = cmt->linksubname;

                                obj = autogen_obj_find_in_list(&obj_it, &((autogen_seq*)obj)->submsg_list);
                            }

                            /* if object was found, add the link */
                            if (obj)
                                {
                                if (obj->flag & AUTOGEN_OBJ_IS_NOT_GENERATED_HTML)
                                    {
                                    fprintf(env->fhtml, html_obj_ver_pres(env, obj, lst, &obj->ver, NULL));
                                    }
                                else
                                    {
                                    fprintf(env->fhtml, "<a href=\"%s\">%s</a>",
                                        html_obj_link(env, obj, NULL),
                                        html_obj_ver_pres(env, obj, lst, &obj->ver, NULL));
                                    }
                                }
                            }
                        }
                    /* print a new line */
                    else if (cmt->id == COMMENT_NEWLINE)
                        {
                        if (last_id == COMMENT_PARAGRAPH)
                            {
                            fprintf(env->fhtml, "<br>");
                            }

                        fprintf(env->fhtml, "<br>");
                        }
                    /* print a bullet */
                    else if (cmt->id == COMMENT_BULLET)
                        {
                        fprintf(env->fhtml, "<li>%s</li>", cmt->comment);
                        }
                    }

                last_id = cmt->id;
                }
            }

        cmt = cmt->next;
        }

    /* end comment */
    if (!first)
        {
        if (flag & HTML_SET_ITALIC)
            {
            fprintf(env->fhtml, "</i>");
            }

        if (flag & HTML_NEWLINE_AFTER)
            {
            fprintf(env->fhtml, "<br><br>");
            }
        }
    }


LOCAL void html_table_size(html_environment* env, autogen_item* item)
    {
    unsigned int len = abs(item->length);

    if (!prop_has((autogen_obj*)env->res, PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS))
        {
        len /= 8;
        }

    if (item->base.flag & AUTOGEN_ITEM_IS_PART_OF_MERGE ||
        item->length == 0)
        {
        html_table_dat(env, 0, 0, 0, 0, "-");
        }
    else
        {
        switch (item->agg_type)
            {
            case AGG_TYPE_FIXED_SINGLE:
                {
                html_table_dat(env, 0, 0, 0, 0, "%u", len);
                }
                break;

            case AGG_TYPE_FIXED_MULTIPLE:
                {
                if (abs(item->length) / 8 == 1)
                    {
                    html_table_dat(env, 0, 0, 0, 0, 
                        html_const_link(env, item->agg_n_str, &item->base.ver));
                    }
                else
                    {
                    html_table_dat(env, 0, 0, 0, 0, "%s x %u", 
                        html_const_link(env, item->agg_n_str, &item->base.ver), len);
                    }
                }
                break;

            case AGG_TYPE_DYNAMIC_REF:
                {
                const char* str_ref = html_generate_reference_text(env, item);

                if (abs(item->length) / 8 == 1)
                    {
                    html_table_dat(env, 0, 0, 0, 0, str_ref);
                    }
                else
                    {
                    html_table_dat(env, 0, 0, 0, 0, "%s x %u", str_ref, len);
                    }
                }
                break;

            case AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE:
                {
                if (abs(item->length) / 8 == 1)
                    {
                    html_table_dat(env, 0, 0, 0, 0, "?");
                    }
                else
                    {
                    html_table_dat(env, 0, 0, 0, 0, "? x %u", len);
                    }
                }
                break;

            case AGG_TYPE_DYNAMIC_OPTIONAL:
                {
                html_table_dat(env, 0, 0, 0, 0, "0 or %u", len);
                }
            break;
            }
        }
    }

LOCAL autogen_tbl* html_find_symbol(const char* name)
{
    autogen_res* res;
    autogen_tbl* tbl = NULL;

    /* find resource */
    res = util_get_unique_res(RESOURCE_SYMBOLS);

    /* find symbol table */
    if (res)
    {
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask     = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask  = AUTOGEN_TBL_ANY;
        tbl_it.obj.name     = name;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
    }

    return tbl;
}


LOCAL void html_print_tbl_link(html_environment* env, autogen_tbl* tbl, const autogen_pres* pres, const autogen_ver* ver)
{
    if (tbl->base.subtype == AUTOGEN_TBL_BIT)
    {
        fprintf(env->fhtml, "Bitfield: ");
    }
    else
    {
        fprintf(env->fhtml, "Constant: ");
    }

    if (pres->tblres != env->res)
    {
        fprintf(env->fhtml, 
            html_obj_ver_pres(env, &tbl->base, &env->res->tbl_list, &tbl->base.ver, ver));
    }
    else
    {
        /* Required: Special handling for tables i shared files */
        if (tbl->base.flag & (AUTOGEN_OBJ_IS_SHARED_EXTERNAL | AUTOGEN_OBJ_IS_SHARED))
        {
            fprintf(env->fhtml, 
                "<a href=\"%s%s\">%s</a>", html_up_level(env),
                html_obj_link(env, &tbl->base, tbl->base.res),
                html_obj_ver_pres(env, &tbl->base, &env->res->tbl_list, &tbl->base.ver, ver));
        }
        else
        {
            fprintf(env->fhtml, 
                "<a href=\"%s\">%s</a>",
                html_obj_link(env, &tbl->base, NULL),
                html_obj_ver_pres(env, &tbl->base, &env->res->tbl_list, &tbl->base.ver, ver));
        }
    }
}

LOCAL void html_print_tbl_entries(html_environment* env, autogen_tbl* tbl, const autogen_pres* pres, const autogen_ver* ver)
{
    int is_derived = (tbl->base.subtype == AUTOGEN_TBL_DERBIT || tbl->base.subtype == AUTOGEN_TBL_DERCONST);

    /* Entries should not be listed if table is a direct 
    constant/bitmask and the output configuration specifies it.
    Entries should not be listed if placed in other resource */
    if ((prop_has(&env->res->base, PROPERTY_HTML_EXPAND_CONSTANT_LISTS) || is_derived) && pres->tblres == env->res)
    {
        autogen_it entry_it = INIT_ITERATOR;
        autogen_obj* entry = NULL;
        int first_entry = TRUE;

        entry_it.typemask = AUTOGEN_OBJ_TBLENTRY;
        entry_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;
        entry_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        entry_it.ver      = ver;

        entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
        while (entry)
        {
            char entryname[256];

            if (first_entry)
            {
                fprintf(env->fhtml, "<br><br>");
                first_entry = FALSE;
            }
            else
            {
                if (tbl->base.subtype == AUTOGEN_TBL_BIT ||
                    tbl->base.subtype == AUTOGEN_TBL_DERBIT)
                {
                    fprintf(env->fhtml, " &<br>");
                }
                else
                {
                    fprintf(env->fhtml, " |<br>");
                }
            }

            /* create item name (add version info if necessary) */
            strcpy(entryname, entry->name);

            if (!autogen_obj_ver_is_exact(&entry->ver, &tbl->base.ver))
            {
                strcat(entryname, " ");
                strcat(entryname, html_obj_ver_string(&entry->ver));
            }

            if (entry->feature_flags)
            {
                /* Feature flags present */
                html_add_featureflag_lst(env, entry->feature_flags, env->collect_feature_flags.char_buffer);
                fprintf(env->fhtml, "%s%s", entryname, env->collect_feature_flags.char_buffer);
            }
            else 
            {
                /* No feature flags */
                fprintf(env->fhtml, "%s", entryname);
            }

            entry = autogen_obj_find_next_in_list(&entry_it);
        }
    }
}

#if (PMD_FILE_FORMAT >= 600)
LOCAL void html_table_pres(html_environment* env,
                           const autogen_pres* pres,
                           const autogen_obj* limit_obj,
                           const autogen_ver* ver,
                           autogen_cmt* cmt_list,
                           int add_cell,
                           int has_def_val,
                           unsigned long long def_val,
                           const char* def_val_str,
                           int length)
#else
LOCAL void html_table_pres(html_environment* env,
                           const autogen_pres* pres,
                           const autogen_obj* limit_obj,
                           const autogen_ver* ver,
                           autogen_cmt* cmt_list,
                           int add_cell,
                           int has_def_val,
                           unsigned int def_val,
                           const char* def_val_str,
                           int length)
#endif
{
    int has_comment = TRUE;
    const autogen_prop *minprop = limit_obj ? prop_find_first(limit_obj, PROPERTY_ITEM_MINIMUM_VALUE) : NULL;
    const autogen_prop *maxprop = limit_obj ? prop_find_first(limit_obj, PROPERTY_ITEM_MAXIMUM_VALUE) : NULL;

    if (add_cell)
    {
        fprintf(env->fhtml, "  <td valign=\"top\">");
    }

    /* constant presentation from global.h */
    if (pres->type & AUTOGEN_PRESENTATION_GLOBAL)
    {
        int first = TRUE;
        autogen_tbl* tbl = html_find_symbol(pres->tblname);
        autogen_obj* entry = NULL;

        autogen_it entry_it = INIT_ITERATOR;

        entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
        while (entry)
        {
            if (first)
            {
                fprintf(env->fhtml, "Possible values are ");
                first = FALSE;
            }
            else
            {
                fprintf(env->fhtml, " and ");
            }

            fprintf(env->fhtml, "%s", entry->name);

            entry = autogen_obj_find_next_in_list(&entry_it);
        }

        if (!first)
        {
            fprintf(env->fhtml, ", which are defined in the file global.h");
        }
    }
    /* constant presentation from pn_const.h */
    else if (pres->type & AUTOGEN_PRESENTATION_PN_CONST)
    {
        if (pres->subtype == PN_DEVICE || pres->subtype == PN_DEVICE_6)
        {
            fprintf(env->fhtml, "PN_DEV_XXX<br>");
            fprintf(env->fhtml, "Possible values are defined in the file pn_const.h");
        }
        else if (pres->subtype == PN_RESOURCE)
        {
            fprintf(env->fhtml, "PN_XXX<br>");
            fprintf(env->fhtml, "Possible values are defined in the file pn_const.h");
        }
        else if (pres->subtype == PN_MEDIA)
        {
            if (env->res->base.subtype == RESOURCE_MEDIA_MODULE ||
                env->res->base.subtype == RESOURCE_MEDIA_MODULE_EXTENSION)
            {
                fprintf(env->fhtml, "%s (= 0x%2.2X)", env->res->base.name, env->res->base.id);
            }
            else
            {
                fprintf(env->fhtml, "PN_MEDIA_XXX<br>");
                fprintf(env->fhtml, "Possible values are defined in the file pn_const.h");
            }
        }
        else if (pres->subtype == PN_OBJECT || pres->subtype == PN_OBJECT_10 || pres->subtype == PN_OBJECT_16)
        {
            fprintf(env->fhtml, "PN_OBJ_XXX<br>");
            fprintf(env->fhtml, "Possible values are defined in the file pn_obj_auto.h");
        }
    }
    /* constant presentation from os_trace_data.txt */
    else if (pres->type & AUTOGEN_PRESENTATION_OS_CONST)
    {
        fprintf(env->fhtml, "Possible values are defined in the file os_trace_data.txt");
    }
    /* DSP constants */
    else if (pres->type & AUTOGEN_PRESENTATION_DSP_ANY)
    {
    }
    /* PPC ID's */
    else if (pres->type & AUTOGEN_PRESENTATION_PPCID)
    {
    }
    /* FTD ID's */
    else if (pres->type & AUTOGEN_PRESENTATION_FTDID)
    {
    }
    /* constant presentation */
    else if (pres->type & AUTOGEN_PRESENTATION_CONST)
    {
        autogen_it tbl_it = INIT_ITERATOR;
        autogen_tbl* tbl;

        int include_spaces = FALSE;
        int first = TRUE;

        tbl_it.typemask = AUTOGEN_OBJ_TBL;
        tbl_it.obj.name = pres->tblname;
        tbl_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

        /* imported table ? */
        if (pres->tblres != env->res)
        {
            tbl_it.ver = &pres->tblres->base.ver;
        }
        else
        {
            tbl_it.ver = ver;
        }

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &pres->tblres->tbl_list);
        while (tbl)
        {
            /* if derived table, find all parent tables related to that */
            if (tbl->base.subtype & (AUTOGEN_TBL_DERCONST | AUTOGEN_TBL_DERBIT))
            {
                autogen_it parent_tbl_it = INIT_ITERATOR;
                autogen_tbl* parent_tbl;

                int first_parent = TRUE;

                parent_tbl_it.typemask    = AUTOGEN_OBJ_TBL;
                parent_tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_BIT;
                parent_tbl_it.obj.name    = tbl->base.base_obj->name;
                parent_tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                parent_tbl_it.ver         = &tbl->base.ver;
                parent_tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

                parent_tbl = (autogen_tbl*)autogen_obj_find_in_list(&parent_tbl_it, &pres->tblres->tbl_list);
                while (parent_tbl)
                {
                    if (include_spaces)
                    {
                        fprintf(env->fhtml, "<br><br>");
                        include_spaces = FALSE;
                    }
                    else if (!first_parent)
                    {
                        fprintf(env->fhtml, "<br>");
                    }
                    first_parent = FALSE;

                    html_print_tbl_link(env, parent_tbl, pres, ver);

                    parent_tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&parent_tbl_it);
                }
            }
            /* normal table */
            else
            {
                if (include_spaces)
                {
                    fprintf(env->fhtml, "<br><br>");
                    include_spaces = FALSE;
                }
                else if (!first)
                {
                    fprintf(env->fhtml, "<br>");
                }
                first = FALSE;

                html_print_tbl_link(env, tbl, pres, ver);
            }

            html_print_tbl_entries(env, tbl, pres, ver);
            include_spaces = TRUE;

            /* find next table */
            tbl = (autogen_tbl*)autogen_obj_find_next_in_list(&tbl_it);
        }
    }
    /* value presentation */
    else if (pres->type & AUTOGEN_PRESENTATION_LINEAR)
    {
        fprintf(env->fhtml, "Interpreted value = ");

        /* scaling */
        if (pres->type & AUTOGEN_PRESENTATION_SCALAR)
        {
            if (pres->scale == -1.0f)
            {
                fprintf(env->fhtml, "-");
            }
            else
            {
                fprintf(env->fhtml, "%g*", pres->scale);
            }
        }

        fprintf(env->fhtml, "Value");

        /* offset */
        if (pres->type & AUTOGEN_PRESENTATION_OFFSET)
        {
            if (pres->offset > 0.0f)
            {
                fprintf(env->fhtml, " + %g", pres->offset);
            }
            else 
                if (pres->offset < 0.0f)
                {
                    fprintf(env->fhtml, " - %g", -pres->offset);
                }
        }
    }
    else if (pres->type & AUTOGEN_PRESENTATION_QN)
    {
        fprintf(env->fhtml, "Q%u encoded value", pres->subtype);
    }
    else if (pres->type & AUTOGEN_PRESENTATION_UNICODE_CHAR)
    {
        fprintf(env->fhtml, "Unicode character");
    }
    else if (pres->type & AUTOGEN_PRESENTATION_ASCII_CHAR)
    {
        fprintf(env->fhtml, "ASCII character");
    }
    /* other presentation */
    else
    {
        has_comment = FALSE;
    }

    /* add unit */
    if (pres->type & AUTOGEN_PRESENTATION_UNIT)
    {
        if (has_comment)
        {
            fprintf(env->fhtml, "<br><br>");
        }

        fprintf(env->fhtml, "Unit of measure: [%s]", pres->unit);

        has_comment = TRUE;
    }

    /* add limits */
    if (limit_obj && prop_has(limit_obj, PROPERTY_ITEM_EXCEPTIONAL_VALUE) ||
        minprop || maxprop)
    {
        char* str_unit = pmd_heap_strdup_h(env->heap_handle, "");

        if (pres->type & AUTOGEN_PRESENTATION_UNIT)
        {
            str_unit = (char*)pmd_heap_alloc_h(env->heap_handle, 5 + strlen(pres->unit));
            sprintf(str_unit, " %s", pres->unit);
        }

        if (has_comment)
        {
            fprintf(env->fhtml, "<br><br>");
        }

        fprintf(env->fhtml, html_build_limits(env, limit_obj, ver, pres));

        if ((pres->type & (AUTOGEN_PRESENTATION_LINEAR | AUTOGEN_PRESENTATION_QN)) &&
            minprop && maxprop)
        {
            double scale  = pres->scale;
            double offset = pres->offset;

            if (pres->type & AUTOGEN_PRESENTATION_QN)
            {
                scale /= pow(2, pres->subtype);
            }

            fprintf(env->fhtml, "<br>");

            if (minprop && !maxprop)
            {
                if (length > 0)
                {
                    if (scale < 0.0f)
                    {
                        fprintf(env->fhtml, "Interpreted value range: <= %g%s", 
                            ((double)minprop->value)*scale + offset, str_unit);
                    }
                    else
                    {
                        fprintf(env->fhtml, "Interpreted value range: >= %g%s", 
                            ((double)minprop->value)*scale + offset, str_unit);
                    }
                }
                else
                {
                    if (scale < 0.0f)
                    {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(env->fhtml, "Interpreted value range: <= %g%s", 
                            ((double)((long long)minprop->value))*scale + offset, str_unit);
#else
                        fprintf(env->fhtml, "Interpreted value range: <= %g%s", 
                            ((double)((int)minprop->value))*scale + offset, str_unit);
#endif
                    }
                    else
                    {
#if (PMD_FILE_FORMAT >= 600)
                        fprintf(env->fhtml, "Interpreted value range: >= %g%s", 
                            ((double)((long long)minprop->value))*scale + offset, str_unit);
#else
                        fprintf(env->fhtml, "Interpreted value range: >= %g%s", 
                            ((double)((int)minprop->value))*scale + offset, str_unit);
#endif
                    }
                }
            }
            else
                if (maxprop && !minprop)
                {
                    if (length > 0)
                    {
                        if (scale < 0.0f)
                        {
                            fprintf(env->fhtml, "Interpreted value range: >= %g%s", 
                                ((double)maxprop->value)*scale + offset, str_unit);
                        }
                        else
                        {
                            fprintf(env->fhtml, "Interpreted value range: <= %g%s", 
                                ((double)maxprop->value)*scale + offset, str_unit);
                        }
                    }
                    else
                    {
                        if (scale < 0.0f)
                        {
#if (PMD_FILE_FORMAT >= 600)
                            fprintf(env->fhtml, "Interpreted value range: >= %g%s",
                                ((double)((long long)maxprop->value))*scale + offset, str_unit);
#else
                            fprintf(env->fhtml, "Interpreted value range: >= %g%s",
                                ((double)((int)maxprop->value))*scale + offset, str_unit);
#endif
                        }
                        else
                        {
#if (PMD_FILE_FORMAT >= 600)
                            fprintf(env->fhtml, "Interpreted value range: <= %g%s", 
                                ((double)((long long)maxprop->value))*scale + offset, str_unit);
#else
                            fprintf(env->fhtml, "Interpreted value range: <= %g%s", 
                                ((double)((int)maxprop->value))*scale + offset, str_unit);
#endif
                        }
                    }
                }
                else
                {
                    if (length > 0)
                    {
                        if (scale < 0.0f)
                        {
                            fprintf(env->fhtml, "Interpreted value range: %g%s to %g%s", 
                                ((double)maxprop->value)*scale + offset, str_unit,
                                ((double)minprop->value)*scale + offset, str_unit);
                        }
                        else
                        {
                            fprintf(env->fhtml, "Interpreted value range: %g%s to %g%s", 
                                ((double)minprop->value)*scale + offset, str_unit,
                                ((double)maxprop->value)*scale + offset, str_unit);
                        }
                    }
                    else
                    {
                        if (scale < 0.0f)
                        {
#if (PMD_FILE_FORMAT >= 600)
                            fprintf(env->fhtml, "Interpreted value range: %g%s to %g%s", 
                                ((double)((long long)maxprop->value))*scale + offset, str_unit,
                                ((double)((long long)minprop->value))*scale + offset, str_unit);
#else
                            fprintf(env->fhtml, "Interpreted value range: %g%s to %g%s", 
                                ((double)((int)maxprop->value))*scale + offset, str_unit,
                                ((double)((int)minprop->value))*scale + offset, str_unit);
#endif
                        }
                        else
                        {
#if (PMD_FILE_FORMAT >= 600)
                            fprintf(env->fhtml, "Interpreted value range: %g%s to %g%s", 
                                ((double)((long long)minprop->value))*scale + offset, str_unit,
                                ((double)((long long)maxprop->value))*scale + offset, str_unit);
#else
                            fprintf(env->fhtml, "Interpreted value range: %g%s to %g%s", 
                                ((double)((int)minprop->value))*scale + offset, str_unit,
                                ((double)((int)maxprop->value))*scale + offset, str_unit);
#endif
                        }
                    }
                }
        }

        has_comment = TRUE;
    }

    /* add default value */
    if (has_def_val)
    {
        if (has_comment)
        {
            fprintf(env->fhtml, "<br><br>");
        }

        fprintf(env->fhtml, "Default value: %s", def_val_str);

        /* add interpreted default value if the default value is not an exceptional value */
        if (pres->type & (AUTOGEN_PRESENTATION_LINEAR | AUTOGEN_PRESENTATION_QN))
        {
            double scale  = pres->scale;
            double offset = pres->offset;
            const autogen_prop *exprop = NULL;

            if (pres->type & AUTOGEN_PRESENTATION_QN)
            {
                scale /= pow(2, pres->subtype);
            }

            if (limit_obj)
            {
                exprop = prop_find_first(limit_obj, PROPERTY_ITEM_EXCEPTIONAL_VALUE);
            }
            while (exprop && exprop->value != def_val)
            {
                exprop = prop_find_next(exprop);
            }

            if (!exprop)
            {
                double dval = 0.0;

                if (length > 0)
                {
                    dval = ((double)def_val)*scale + offset;
                }
                else
                {
#if (PMD_FILE_FORMAT >= 600)
                    dval = ((double)((long long)def_val))*scale + offset;
#else
                    dval = ((double)((int)def_val))*scale + offset;
#endif
                }

                fprintf(env->fhtml, " (= %g", dval);

                if (pres->type & AUTOGEN_PRESENTATION_UNIT)
                {
                    fprintf(env->fhtml, " %s", pres->unit);
                }

                fprintf(env->fhtml, ")");
            }
        }

        has_comment = TRUE;
    }

    /* add comment */
    if (has_comment)
    {
        html_comment(env, cmt_list, HTML_NEWLINE_BEFORE | HTML_SET_ITALIC);
    }
    else
    {
        html_comment(env, cmt_list, HTML_SET_ITALIC);
    }

    if (add_cell)
    {
        fprintf(env->fhtml, "&nbsp;</td>\n");
    }
}


LOCAL const char* html_const_link(html_environment* env, const char* name, const autogen_ver* ver)
{
    char* html_const_link = (char*)pmd_heap_alloc_h(env->heap_handle, 30 + strlen(name));
    autogen_it cons_it = INIT_ITERATOR;

    strcpy(html_const_link, name);

    cons_it.typemask = AUTOGEN_OBJ_CONST;
    cons_it.obj.name = name;
    cons_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
    cons_it.ver      = ver;
    cons_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    if (autogen_obj_find_in_list(&cons_it, &env->res->const_list))
    {
        sprintf(html_const_link, "<a href=\"#GENERAL_CONST\">%s</a>", name);
    }

    return html_const_link;
}                                        


LOCAL void html_notes(html_environment* env)
{
    autogen_obj *note;
    autogen_it note_it = INIT_ITERATOR;

    html_table(env);

    note_it.typemask    = AUTOGEN_OBJ_NOTE;
    note_it.subtypemask = AUTOGEN_NOTE_ANY;
    note_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_HTML;

    note = autogen_obj_find_in_list(&note_it, &env->res->note_list);
    while (note)
    {
        html_table_row(env, FALSE);

        fprintf(env->fhtml, "  <td valign=\"top\"><a name=\"%s\">%s</a></td>\n", html_obj_link(env, note, NULL), note->name);

        html_table_com(env, note->cmt_list);
        html_table_row_end(env);

        note = autogen_obj_find_next_in_list(&note_it);
    }

    fprintf(env->fhtml, "</table><br>\n");
}

LOCAL const char* html_up_level(html_environment* env)
{
    char* str_up = NULL;
    int i, j;
    char up[32];
    memset(up, '\0', 32); /* up to 10 levels ...*/
    for (i=0, j=0; i < env->gif_depth; i++, j+=3)
    {
        up[j] = '.'; up[j+1] = '.'; up[j+2] = '/';
    }
    str_up = (char*)pmd_heap_alloc_h(env->heap_handle, 32);

    strcpy(str_up, up);
    return str_up;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: html_featureflag_match
 
    Purpose: 
        Check if two feature flags are equal.
 
    Functional Description:
        This function compares two feature flags and returns true or false depending on they are eqaul or not.
        The ELSE part of a feature flag will be negated before being compared with the other feature flag.

    Arguments: 
        env          - [in]  environment. List of feature flags is collected in a struct in this.
        feature_flag - [in]  feature flag to be added to the list
        formattedTag - [out] after the call it contains the tag (text) to be listed on the actual line
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int html_featureflag_match(autogen_feature *left, autogen_feature *right)
{
    int comp;
    int leftFlagNegated = FALSE;
    int rightFlagNegated = FALSE;

    /* Flag must be defined */
    if (!left || !right)
    {
        return FALSE;
    }

    /* If we have an ELSE then use the negated expresseion */
    if (left->flag_logic == FT_ELSE)
    {
        left = left->head;
        leftFlagNegated = TRUE;
    }

    /* If we have an ELSE then use the negated expresseion */
    if (right->flag_logic == FT_ELSE)
    {
        right = right->head;
        rightFlagNegated = TRUE;
    }

    /* Compare flag logic */
    /* If logic flags NOT equal then return false */
    if (! (
        /* Normal case */
        (left->flag_logic == right->flag_logic && leftFlagNegated == rightFlagNegated) ||
        /* Handle #ifdef and #ifndef */
        (left->flag_logic == FT_NOTDEF_FLAG && right->flag_logic == FT_DEF_FLAG && leftFlagNegated != rightFlagNegated) ||
        (left->flag_logic == FT_DEF_FLAG && right->flag_logic == FT_NOTDEF_FLAG && leftFlagNegated != rightFlagNegated)
        ))
    {
        return FALSE;
    }

    /* Check the first flag */
    if (left->feature1 && right->feature1) 
    {
        /* Flags must be set */
        if (!left->feature1->flag || !right->feature1->flag)
        {
            return FALSE;
        }

        /* Compare flags */
        comp = strcmp(left->feature1->flag, right->feature1->flag);
        if (comp != 0) return FALSE;

        /* Compare values. Note that for #ifdef and #ifndef then no values are present */
        if (left->feature1->value && right->feature1->value)
        {
            comp = strcmp(left->feature1->value, right->feature1->value);
            if (comp != 0) return FALSE;
        }
    }

    /* Check the second flag */
    if (left->feature2 && right->feature2) 
    {
        /* Flags and values must be set */
        if (!left->feature2->flag || !right->feature2->flag || !left->feature2->value || !right->feature2->value)
        {
            return FALSE;
        }

        /* Compare flags */
        comp = strcmp(left->feature2->flag, right->feature2->flag);
        if (comp != 0) return FALSE;

        /* Compare values */
        comp = strcmp(left->feature2->value, right->feature2->value);
        if (comp != 0) return FALSE;
    }
    return TRUE;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: html_add_featureflag_lst
 
    Purpose: 
        Add an entry to the collected feature flag list in the environment.
 
    Functional Description:
        This function adds a feature flag to a list that is to be printed later by the function
        html_print_feature_flag_lst(). Normally used to collect feature flags and write out a small tag/link
        that points to an other place where the actual feature flag is written out (using html_print_feature_flag_lst()).
        If a feature flag is already present in the list then the tag is reused such that a given feature flag is only 
        written out once at the end, ie. several lines can point to the same feature flag.

    Arguments: 
        env          - [in]  environment. List of feature flags is collected in a struct in this.
        feature_flag - [in]  feature flag to be added to the list
        formattedTag - [out] after the call it contains the tag (text) to be listed on the actual line
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void html_add_featureflag_lst(html_environment *env, autogen_feature *feature_flag, char *formattedTag)
{
    html_featureflag_lst *ftFlag;
    const char *formatString = "<sub><small>(<a href=\"#Flag%u\">Flag%u</a>)</small></sub>";

    /* Check if the feature flag is already present in the list */
    int found = FALSE;
    ftFlag = env->collect_feature_flags.head;
    while(ftFlag && !found)
    {
        /* Check if feature flag matches the new one. If not then continue */
        found = html_featureflag_match(ftFlag->featureFlag, feature_flag);
        if (!found)
        {
            ftFlag = ftFlag->next;
        }
    }       

    /* If feature flag found in list then reuse this */
    if (found)
    {
        /* Generate the tag to point to feature flag listed below the table */
        sprintf(formattedTag, formatString, ftFlag->tag, ftFlag->tag);
        return;
    }

    /* Feature flag not already present in list. Create a new entry */
    ftFlag = (html_featureflag_lst *)pmd_heap_alloc_h(env->heap_handle, sizeof(html_featureflag_lst));

    /* Save the feature flag in list */
    ftFlag->featureFlag = feature_flag;

    /* Save the tag */
    ftFlag->tag = env->collect_feature_flags.tag_count++;

    /* Insert into list at tail end */
    ftFlag->next = NULL;
    if (env->collect_feature_flags.head == NULL)
    {
        /* Empty list. Set head and tail to point on first entry */
        env->collect_feature_flags.head = ftFlag;
        env->collect_feature_flags.tail = ftFlag;
    }
    else 
    {
        /* Insert at tail */
        env->collect_feature_flags.tail->next = ftFlag;
        env->collect_feature_flags.tail = ftFlag;
    }

    /* Generate the tag to point to feature flag listed below the table */
    sprintf(formattedTag, formatString, ftFlag->tag, ftFlag->tag);
    return;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: html_print_feature_flag_lst
 
    Purpose: 
        Print out a list of feature flags to HTML
 
    Functional Description:
        Loop through the list of feature flags collected in the environment variable env. 
        Print each of the feature flags.
        This function is used to print out all feature flags collected with the function 
        html_add_featureflag_lst().

    Arguments: 
        env          - [in] environment
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void html_print_feature_flag_lst(html_environment *env)
{
    html_featureflag_lst *ftFlag = env->collect_feature_flags.head;
    
    /* Print list of feature flags */
    fprintf(env->fhtml, "<b>Feature flags:</b><br>");
    while(ftFlag)
    {
        if (ftFlag->featureFlag)
        {
            /* Define prefix to printed out feature flag */
            sprintf(env->collect_feature_flags.char_buffer, "<a name=\"Flag%u\">Flag%u:</a>", ftFlag->tag, ftFlag->tag);

            /* Print out feature flag */
            html_print_feature_flag(env, env->collect_feature_flags.char_buffer, ftFlag->featureFlag);
            fprintf(env->fhtml, "<br>");
        }
        ftFlag = ftFlag->next;
    }

    /* Reset list. Note: The allocated memory is not freed */
    env->collect_feature_flags.head = NULL;
    env->collect_feature_flags.tail = NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: html_print_feature_flag
 
    Purpose: 
        Print out a feature flag to HTML
 
    Functional Description:
        Check if it is ELSE part of a feature flag. If so then negate the expression being printed.
        Print out the feature flag

    Arguments: 
        env          - [in] environment
        prefix       - [in] text string to be printed in front of the actual feature flag
        feature_flag - [in] feature flag to be printed
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void html_print_feature_flag(html_environment *env, const char *prefix, const autogen_feature* feature_flag)
{
    const autogen_feature *ftFlag = NULL;
    int negate = FALSE;

    /* Return if no feature flag */
    if (!feature_flag)
        return;

    if (!prefix) 
    {
        prefix = "";
    }

    /* Check if IF or ELSE part should be printed */
    if (feature_flag->head)
    {
        /* ELSE part of a feature flag, ie. the condition must be negated */
        ftFlag = feature_flag->head;
        negate = TRUE;
    }
    else 
    {
        /* IF part of a feature flag */
        ftFlag = feature_flag;
        negate = FALSE;
    }

    switch(ftFlag->flag_logic)
    {
    case FT_FLAG:
        {
            fprintf(env->fhtml, "%s <i>#if %s(%s == %s)</i>\n", prefix, (negate ? "!" : ""), 
                                ftFlag->feature1->flag, ftFlag->feature1->value);
            break;
        }
    case FT_NOTDEF_FLAG:
        {
            if (negate)
            {
                fprintf(env->fhtml, "%s <i>#ifdef %s</i>\n", prefix, ftFlag->feature1->flag);
            }
            else
            {
                fprintf(env->fhtml, "%s <i>#ifndef %s</i>\n", prefix, ftFlag->feature1->flag);
            }
            break;
        }
    case FT_DEF_FLAG:
        {
            if (negate) 
            {
                fprintf(env->fhtml, "%s <i>#ifndef %s</i>\n", prefix, ftFlag->feature1->flag);
            }
            else
            {
                fprintf(env->fhtml, "%s <i>#ifdef %s</i>\n", prefix, ftFlag->feature1->flag);
            }
            break;
        }
    case FT_FLAG1_AND_FLAG2:
        {
            fprintf(env->fhtml, "%s <i>#if %s((%s == %s) && (%s == %s))</i>\n", prefix, (negate ? "!" : ""), 
                                ftFlag->feature1->flag, ftFlag->feature1->value, 
                                ftFlag->feature2->flag, ftFlag->feature2->value);
            break;
        }
    case FT_FLAG1_OR_FLAG2:
        {
            fprintf(env->fhtml, "%s <i>#if %s((%s == %s) || (%s == %s))</i>\n", prefix, (negate ? "!" : ""),
                                ftFlag->feature1->flag, ftFlag->feature1->value, 
                                ftFlag->feature2->flag, ftFlag->feature2->value);
            break;
        }
    default:
        {
            util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0, "Invalid FEATURE_FLAG flag_logic value\n");
        }
    }
}

/*  End of file output_html.c  */
