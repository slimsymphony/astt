/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_ref.h
                -------------
                SW Include






Project:          autogen

%name:            autogen_ref.h %
%version:         4 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Wed Nov 11 16:52:12 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    The file contains some functions and structures used for reference handling
*/

#ifndef _AUTOGEN_REF_H_
#define _AUTOGEN_REF_H_

/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

#define AUTOGEN_REFERENCE_TYPE_MSG_ID               0x00000001u
#define AUTOGEN_REFERENCE_TYPE_MSG_LENGTH           0x00000002u
#define AUTOGEN_REFERENCE_TYPE_SUB_MSG_ID           0x00000004u
#define AUTOGEN_REFERENCE_TYPE_SB_ID                0x00000008u
#define AUTOGEN_REFERENCE_TYPE_SB_LENGTH            0x00000010u
#define AUTOGEN_REFERENCE_TYPE_RESOURCE_ID          0x00000020u
#define AUTOGEN_REFERENCE_TYPE_PRIVATE_ID           0x00000040u
#define AUTOGEN_REFERENCE_TYPE_XTI_MASTER_ID        0x00000080u
#define AUTOGEN_REFERENCE_TYPE_TRACE_DATA_LENGTH    0x00000100u
#define AUTOGEN_REFERENCE_TYPE_TRACE_ENTITY_ID      0x00000200u
#define AUTOGEN_REFERENCE_TYPE_TRACE_GROUP_ID       0x00000400u
#define AUTOGEN_REFERENCE_TYPE_TRACE_ID             0x00000800u


/* ============================================================================================= */
/* Prototypes */
/* ============================================================================================= */

void            reference_add_to_handle(autogen_ref_handle* ref_handle, const autogen_item_value* item, const char* name, autogen_ref_type type);
unsigned int    reference_add_counter(autogen_ref_handle* ref_handle, autogen_item* item, const char* name, int length, autogen_feature *featureflag);
void            reference_add_tag(autogen_ref_handle* ref_handle, autogen_item* item, const char* name, autogen_feature *featureflag);
void            reference_add_transformation(autogen_ref_handle* ref_handle, const char* new_name, const char* org_name, unsigned int alg, int value, int line, autogen_feature *featureflag);

void            reference_check_choice(autogen_item_value* ref_item, autogen_item_choice* choice);
void            reference_check_unresolved();
void            reference_check_unused();

void            reference_clone_seq(autogen_seq* seq, autogen_ref_handle* src_ref_handle);

void            reference_copy_item(autogen_item* item, autogen_ref_handle* src_ref_handle);
void            reference_copy_transformations(autogen_ref_handle* ref_handle, autogen_ref_handle* src_ref_handle);

autogen_ref*    reference_find(autogen_item* item);
autogen_ref*    reference_find_from_handle(autogen_ref_handle* ref_handle, const char* name, autogen_feature *featureflag, int deep);

autogen_ref_handle* 
                reference_get_handle_from_obj(autogen_obj* obj);
#if (PMD_FILE_FORMAT >= 600)
void            reference_get_limits(autogen_item* item, signed long long* min_val, signed long long* max_val, char* min_val_str, char* max_val_str);
#else
void            reference_get_limits(autogen_item* item, int* min_val, int* max_val, char* min_val_str, char* max_val_str);
#endif
autogen_item*   reference_get_special_item(const autogen_ref_handle* ref_handle, unsigned short special_type);

void            reference_init();

int             reference_is_name_predefined(const char* name);
int             reference_is_name_reserved(const char* name);

void            reference_use_counter(autogen_item* item, autogen_feature *featureflag);
void            reference_use_tag(autogen_item* item, autogen_feature *featureflag);

#endif /* _AUTOGEN_REF_H_ */

/*  End of autogen_ref.h  */
