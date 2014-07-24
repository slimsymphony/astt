/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_init.h
                --------------
                SW Include






Project:          autogen

%name:            autogen_init.h %
%version:         co1tss#63 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Thu Nov 12 09:53:56 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    The file contains the prototypes of the init_xxx functions used to
    initialize all macros and check the macro arguments. For each common 
    macro, a corresponding init_xxx function exists
*/

#ifndef _AUTOGEN_INIT_H_
#define _AUTOGEN_INIT_H_

/* ============================================================================================= */
/* Function prototypes */
/* ============================================================================================= */

void    init_bit_tbl_begin(int line, const char* name, int length, unsigned int order, const char* verfrom, const char* verto, const char* cmt);
void    init_bit_tbl_end(int line);
void    init_bit_tbl_entry(int line, const char* bits, const char* bitname, const char* verfrom, const char* verto, const char* cmt);


void    init_block(int line, unsigned int order, const char* varname, const char* parname, unsigned int type, 
                   const char* data1, const char* data2, unsigned int flags, const char* refname, unsigned int n, const char* nstr);

void    init_case(int line, const char* tagname, unsigned int tagid, int has_id, const char* seqname, const char* verfrom, const char* verto, int macro_type);
void    init_case_end(int line);

void    init_comment(int line, autogen_comment_id id, const char* comment);
void    init_comment_property(int line, autogen_comment_id id);
void    init_comment_link(int line, unsigned int objtype, const char* name, const char* subname, const char* ver);

void    init_const_tbl_begin(int line, const char* name, int length, unsigned int order, const char* verfrom, const char* verto, const char* cmt);
void    init_const_tbl_end(int line);

#if (PMD_FILE_FORMAT >= 600)
void init_const_tbl_entry(int line, const char* name, unsigned long long id, const char* verfrom, const char* verto, const char* cmt);
#else
void    init_const_tbl_entry(int line, const char* name, unsigned int id, const char* verfrom, const char* verto, const char* cmt);
#endif

#if (PMD_FILE_FORMAT >= 600)
void    init_constant(int line, const char* constname, unsigned long long id, const char* idstr, int is_negative, const char* verfrom, const char* verto);
#else
void    init_constant(int line, const char* constname, unsigned int id, const char* idstr, int is_negative, const char* verfrom, const char* verto);
#endif

void    init_choice_begin(int line, const char* varname, const char* parname, const char* refname, const char* tblname, unsigned short relpos, int macro_type);
void    init_choice_end(int line);

void    init_merge_begin(int line, int length, unsigned int order, const char* varname, const char* parname);
void    init_merge_end(int line);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
void    init_note(int line, const char* name);
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

void    init_der_bit_tbl_begin(int line, const char* tblname, const char* orgtblname, const char* verfrom, const char* verto);
void    init_der_bit_tbl_end(int line);
void    init_der_bit_tbl_entry(int line, const char* name);
void    init_der_bit_tbl_entry_ver(int line, const char* name, const char* verfrom, const char* verto);

void    init_der_const_tbl_begin(int line, const char* tblname, const char* orgtblname, const char* verfrom, const char* verto);
void    init_der_const_tbl_end(int line);
void    init_der_const_tbl_entry(int line, const char* name);
void    init_der_const_tbl_entry_ver(int line, const char* name, const char* verfrom, const char* verto);

void    init_feature_flag_begin(int line, const char* flag, const char* value);
void    init_feature_flag_or_flag_begin(int line, const char* flag1, const char* value1, const char* flag2, const char* value2);
void    init_feature_flag_and_flag_begin(int line, const char* flag1, const char* value1, const char* flag2, const char* value2);
void    init_feature_flag_else(int line);
void    init_feature_flag_end(int line);

void    init_filler(int line, unsigned int type, unsigned int length);
void    init_filler_ex(int line, const char* varname, unsigned int length, unsigned int n);

void    init_ftd_tbl_begin(int line, const char* verfrom, const char* verto, const char* cmt);
void    init_ftd_tbl_end(int line);

void    init_ftd_tbl_entry_begin(int line, const char* name, unsigned int id, const char* verfrom, const char* verto, 
                                 unsigned int type, const char* parname);
void    init_ftd_tbl_entry_end(int line, unsigned int type);

void    init_isi_begin();
void    init_isi_end();

void    init_isi_version_history(int line, const char* version);

void    init_item_default_value(int line, unsigned int val, int val_is_negative, const char* val_str);
void    init_item_limits(int line, 
                         unsigned int minval, int minval_is_negative, const char* minvalstr, 
                         unsigned int maxval, int maxval_is_negative, const char* maxvalstr, 
                         unsigned int excval1, int excval1_is_negative, const char* excvalstr1,
                         unsigned int excval2, int excval2_is_negative, const char* excvalstr2,
                         unsigned int excval3, int excval3_is_negative, const char* excvalstr3);


void    init_msg_begin(int line, unsigned int id, const char* name, unsigned int type, const char* verfrom, const char* verto, const char* cmt);
void    init_msg_end(int line);
void    init_msg_id_section(int line);
void    init_msg_pair(int line, const char* reqmsgname, const char* respmsgname, const char* resname, const char* verfrom, const char* verto);
void    init_msg_set_type(int line, unsigned int type);

void    init_old_comment(int line, unsigned int target, unsigned int type, const char* value, int req_comment);
void    init_old_comment_link(int line, unsigned int target, unsigned int objtype, const char* name, const char* subname, const char* ver);

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
void    init_old_macro_used(const char* text);
#endif

void    init_pointer(int line, unsigned int order, const char* varname, const char* parname, unsigned int type);

void    init_ppc_tbl_begin(int line, const char* verfrom, const char* verto);
void    init_ppc_tbl_end(int line);
void    init_ppc_tbl_entry(int line, const char* name, unsigned int id, const char* seqname);
void    init_ppc_tbl_entry_ver(int line, const char* name, unsigned int id, const char* seqname, const char* verfrom, const char* verto);

void    init_property(int line, autogen_property_id id);
void    init_property_string(int line, autogen_property_id id, const char* value);
void    init_property_string_index(int line, autogen_property_id id, unsigned int index, const char* value);
#if (PMD_FILE_FORMAT >= 600)
void    init_property_value(int line, autogen_property_id id, unsigned long long value, int is_negative, const char* value_str);
void    init_property_value_index(int line, autogen_property_id id, unsigned int index, unsigned long long value, int is_negative, const char* value_str);
#else
void    init_property_value(int line, autogen_property_id id, unsigned int value, int is_negative, const char* value_str);
void    init_property_value_index(int line, autogen_property_id id, unsigned int index, unsigned int value, int is_negative, const char* value_str);
#endif

void    init_range_begin(int line, int length, unsigned int order, const char* varname, const char* parname);
void    init_range_end(int line);
void    init_range_entry_value_ex(int line, unsigned int from, unsigned int to, double scale, double offset, const char* unit, unsigned int pres);
void    init_range_entry_value(int line, unsigned int from, unsigned int to, unsigned int pres);
void    init_range_entry_string(int line, unsigned int from, unsigned int to, const char* text);

void    init_reference(int line, int length, unsigned int order, const char* varname, const char* parname, const char* refname);
void    init_reference_const(int line, const char* varname, const char* parname, const char* refname, const char* tblname);
void    init_reference_transform(int line, const char* oldrefname, const char* newrefname, unsigned int alg, const char* alg_str, int n);

void    init_res_begin(const char* filepath, int line, unsigned int restype, unsigned int resid, const char* resname, 
                       const char* sername, const char* shortname, const char* version, int suppcomm, const char* cmt);
void    init_res_end(int line);
char*   init_res_version_string(int line, unsigned int _Z, unsigned int _Y);

void    init_res_include_shared_file(int line, unsigned int resid, const char* resname, const char* verfrom, const char* verto);

void    init_sb_begin(int line, const char* name, unsigned int id, const char* verfrom, const char* verto, const char* cmt);
void    init_sb_end(int line);
void    init_sb_id_section(int line);
void    init_sb_lst_begin(int line, unsigned int type, const char* varname, const char* parname, unsigned int n, const char* nstr, const char* refname, unsigned int flag);
void    init_sb_lst_end(int line);
void    init_sb_lst_entry(int line, const char* name, const char* verfrom, const char* verto);

void    init_seq_begin(int line, const char* name, unsigned int flag, const char* verfrom, const char* verto, const char* comment);
void    init_seq_end(int line);

void    init_seq_of(int line, const char* varname, const char* parname, const char* seqname, const char* refname, unsigned int flag, unsigned int n, const char* nstr);

void    init_server_set_common_message_support(int line, int supports_comm);
void    init_server_set_short_name(int line, const char* name);
void    init_server_set_type(int line, unsigned int type);

void    init_string(int line, unsigned int strtype, unsigned int order, const char* varname, const char* parname, unsigned int n, const char* nstr);
void    init_string_ref(int line, unsigned int strtype, unsigned int order, const char* varname, const char* parname, const char* refname, unsigned int flag);

void    init_sub_msg_begin(int line, unsigned int submsgid, const char* submsgname, unsigned int msgid, const char* msgname,
                           unsigned int type, const char* verfrom, const char* verto, const char* cmt);
void    init_sub_msg_end(int line);
void    init_sub_msg_pair(int line, const char* reqsubmsgname, const char* reqmsgname, const char* respsubmsgname, const char* respmsgname, const char* verfrom, const char* verto);

void    init_printf_begin(int line, const char *_format);
void    init_printf_end(int line);

void    init_timestamp(int line, int length, unsigned int order, const char* varname, const char* parname, unsigned int type);

void    init_value(int line, int length, unsigned int order, const char* varname, const char* parname, unsigned int pres);
void    init_value_ex(int line, int length, unsigned int order, const char* varname, const char* parname, unsigned int pres, 
                      double scale, double offset, const char* unit);
void    init_value_const(int line, const char* varname, const char* name, const char* tblname, const char* resname);

/* Trace macros */

void    init_trace_group_begin(int line, const char* name, unsigned int id, int state, 
                               const char* dectext, const char* macro);
void    init_trace_group_end(int line);

void    init_trace_group_decoder(int line, const char* name, unsigned int id, int state, 
                                 const char* dllname, const char* dllfunc, unsigned int flags);

void    init_trace_begin(int line, const char* name, unsigned int id, const char* dectext, const char* grp, 
                         int has_scope, const char* macro);
void    init_trace_end(int line);

void    init_trace_group_add(int line, autogen_res* res, const char* name, unsigned int id, int state, 
                             const char* macro, int duplicate_overrule);

#endif /* _AUTOGEN_INIT_H_ */


/*  End of file autogen_init.h  */
