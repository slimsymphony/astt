/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_util.h
                --------------
                SW Include






Project:          autogen

%name:            autogen_util.h %
%version:         co1tss#40 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 12:58:57 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains prototype for common utility functions
*/

#ifndef _AUTOGEN_UTIL_H_
#define _AUTOGEN_UTIL_H_

/* Stores the .out file names given on commandline (see -out cmdline option) */
typedef struct {
    char *filename[256];
    int n_filename;
} OutFilenames; 

/* ============================================================================================= */
/* Function prototypes */
/* ============================================================================================= */

unsigned int        util_get_merge_offset(autogen_item* item);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
#if (PMD_FILE_FORMAT >= 600)
unsigned int        util_get_seq_size(autogen_seq* seq, autogen_ver* ver, unsigned long long* min_val, unsigned long long* max_val);
#else
unsigned int        util_get_seq_size(autogen_seq* seq, autogen_ver* ver, unsigned int* min_val, unsigned int* max_val);
#endif
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

void                util_error_line(const char* filename, int line, unsigned int error_id, 
                               unsigned int env_mask, unsigned int detailed_err_desc, char* error_text, ...);

autogen_res*        util_get_base_res(const autogen_res* res);
autogen_res*        util_get_unique_res(unsigned int type);
#if (PMD_FILE_FORMAT >= 600)
autogen_res*        util_get_ext_res(unsigned int restype, unsigned long long resid);
#else
autogen_res*        util_get_ext_res(unsigned int restype, unsigned int resid);
#endif
autogen_res*        util_get_protocol_res(const char* name);
autogen_res*        util_get_res(unsigned int id);

#if (PMD_FILE_FORMAT >= 600)
int                 util_get_msgid_range(autogen_res* res, unsigned long long* from, unsigned long long* to);
#else
int                 util_get_msgid_range(autogen_res* res, unsigned int* from, unsigned int* to);
#endif

const char*         util_get_obj_type_name(const autogen_obj* obj);
const char*         util_get_obj_name(const autogen_obj* obj);

const autogen_obj*  util_get_base_parent(const autogen_obj* obj);
#if (PMD_FILE_FORMAT >= 600)
unsigned long long  util_get_case_id(const char* name, const char* tblname, autogen_res* tblres, const autogen_ver* ver);
#else
unsigned int        util_get_case_id(const char* name, const char* tblname, autogen_res* tblres, const autogen_ver* ver);
#endif
const char*         util_get_case_mask(const char* name, const char* tblname, autogen_res* tblres, const autogen_ver* ver);

const char *        util_get_hyphens(unsigned int num_hyphens);
const char *        util_get_spaces(unsigned int num_spaces);

unsigned int        util_get_n_def(autogen_obj_list* obj_list);
autogen_seq*        util_get_parent_seq(autogen_item* item);
autogen_tbl*        util_get_parent_table(autogen_tbl* tbl , const autogen_ver* ver);
int                 util_has_multiple_versions(const autogen_obj *obj);
int                 util_has_newer_version(const autogen_obj *obj);

#if (PMD_FILE_FORMAT >= 600)
void                util_get_item_limits(const autogen_item *item, unsigned long long* min_val, unsigned long long* max_val, char* min_val_str, char* max_val_str);
#else
void                util_get_item_limits(const autogen_item *item, unsigned int* min_val, unsigned int* max_val, char* min_val_str, char* max_val_str);
#endif

unsigned int        util_get_resulting_alignment(unsigned int alignment1, unsigned int alignment2, int align_to_64_bits);

const char*         util_get_filename(const char* filepath);

int                 util_is_obj_in_list(autogen_obj* obj, 
                                        autogen_obj** obj_list, 
                                        unsigned int elements_in_list);
int                 util_is_string_number(const char* str_value);
int                 util_is_predefined_constant(const char* name);

unsigned int        util_get_tracegroup_type(const autogen_res* res);
unsigned int        util_get_tracegroup_type_from_refname(const char* refname);

const autogen_res_conf* util_get_res_conf(unsigned int res_type);

const autogen_symbol_conf* util_get_sym_conf_by_type(unsigned int type);
const autogen_symbol_conf* util_get_sym_conf_by_name(const char* name);
const autogen_symbol_conf* util_get_sym_conf_by_tblname(const char* tblname);

/* Comment related functions */
char*               util_build_unformatted_comment(const autogen_cmt* list,
                                                   int exclusive_type);
char *              util_wrap_words(const char *unformatted,
                                    unsigned int line_len,
                                    const char *prefix,
                                    const char *separator,
                                    const char *suffix);

void                util_validate_printf_format_string(const char *file, int line, 
                                                       const char *format, autogen_obj_list *arg_list);

/* Functions for integrating into the autobuilder */
const char* util_ver_to_text(const autogen_ver* ver);
void        util_write_version_file(const char* filename,
                                    const autogen_ver* version);

                                            



#endif /* _AUTOGEN_UTIL_H_ */


/*  End of file autogen_util.h  */
