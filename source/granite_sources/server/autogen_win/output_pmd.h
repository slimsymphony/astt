/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_pmd.h
                -------------
                SW Include






Project:          autogen

%name:            output_pmd.h %
%version:         co1tss#77 %
%instance:        co_pctls_2 %
%derived_by:      nosterga %
%date_modified:   Tue Feb 15 18:05:11 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    The file contains some functions and structures used for PMD file generation
*/

#ifndef _OUTPUT_PMD_H_
#define _OUTPUT_PMD_H_

#include "list.h"

/* ============================================================================================= */
/* PMD type name constants */
/* ============================================================================================= */

#define PMD_TYPE_NAME_TRACE_ENTITY_ID           "trc_entity_id"

#define PMD_TYPE_NAME_TRACE_GROUP_ID            "trc_grp_id"
#define PMD_TYPE_NAME_TRACE_GROUP_ID_DEFAULT    "trc_grp_id_def"
#define PMD_TYPE_NAME_TRACE_GROUP_ID_ENTITY_SEL "trc_grp_id_entity_sel"

#define PMD_TYPE_NAME_TRACE_ID                  "trc_id"
#define PMD_TYPE_NAME_TRACE_ID_DEFAULT          "trc_id_def"
#define PMD_TYPE_NAME_TRACE_ID_ENTITY_SEL       "trc_id_entity_sel"
#define PMD_TYPE_NAME_TRACE_ID_GROUP_SEL        "trc_id_grp_sel"

#define PMD_TYPE_NAME_TRACE_DATA_BYTE           "trc_data_byte"
#define PMD_TYPE_NAME_TRACE_DATA_LENGTH         "trc_data_len"
#define PMD_TYPE_NAME_TRACE_DATA_DUMP           "trc_data_dump"

#define PMD_TYPE_NAME_TRACE_DATA_ENTITY_SEL     "trc_data_entity_sel"
#define PMD_TYPE_NAME_TRACE_DATA_GROUP_SEL      "trc_data_group_sel"
#define PMD_TYPE_NAME_TRACE_DATA_TRACE_SEL      "trc_data_trace_sel"


/* ============================================================================================= */
/* Global structures */
/* ============================================================================================= */

/* CManagedObject */
typedef struct t_pmd_managedobj
{
    /* should object be streamed out? */
    int stream_out;

    /* is object ID streamed in/out? */
    int stream_obj_id;

    /* the assigned PMD object id for the object */
    unsigned int   object_id;
    unsigned short class_id;

    /* object flags */
    unsigned int   flags;

} pmd_managedobj;


/* CNamedObject */
typedef struct t_pmd_namedobj
{
    /* managed object */
    pmd_managedobj managedobj;

    /* name of the object */
    const char* name;

} pmd_namedobj;

/* CType derived object */
typedef struct t_pmd_type
{
    /* CManagedObject - must be first element in this structure */
    pmd_managedobj managedobj;

    /* Name of the type */
    char* name;

    /* pointer to the next type object in the list (NULL if none) */
    struct t_pmd_type* next;

} pmd_typ;

/* CTag */
typedef struct t_pmd_tag
{
    /* managed object */
    pmd_managedobj managedobj;

    /* [number] type, identifying tag (NULL, if none) */
    const pmd_typ* ref_type;

    /* relative and bit position of tag (for miscellanous usage) */
    unsigned short bit_pos;
    unsigned short rel_pos;

} pmd_tag;

/* CLength */
typedef struct t_pmd_length
{
    /* tag */
    pmd_tag tag;

    unsigned short alg;
    int length;

} pmd_len;

/* CPrimitiveType */
typedef struct t_pmd_primitive
{
    /* CType - must be first element in this structure */
    pmd_typ type;

    /* PMD number special type (PMD_NUMBER_SPECIAL_TYPE_XXX) */
    unsigned int special_type;

} pmd_primitive;

/* CConstructedType */
typedef struct t_pmd_constructed
{
    /* CType - must be first element in this structure */
    pmd_typ type;

    /* Length definition */
    pmd_len length_obj;

} pmd_constructed;

/* CConditionElement */
typedef struct t_pmd_cond_el
{
    /* CManagedObject - must be first element in this structure */
    pmd_managedobj managedobj;

} pmd_cond_el;

/* CConditionElementBitstate */
typedef struct t_pmd_cond_el_bit
{
    /* CConditionElement - must be first element in this structure */
    pmd_cond_el cond_el;

    const char* bitstate;

} pmd_cond_el_bit;

/* CConditionElementInterval */
typedef struct t_pmd_cond_el_int
{
    /* CConditionElement - must be first element in this structure */
    pmd_cond_el cond_el;

    /* Interval - PMD_cond_el_HAS_SINGLE_VALUE_INTERVAL is set when from equals to */
#if (PMD_FILE_FORMAT >= 600)
    long long from;
    long long to;
#else
    int from;
    int to;
#endif

} pmd_cond_el_int;

/* CNumberPresentation */
typedef struct t_pmd_number_pres
{
    /* CManagedObject - must be first element in this structure */
    pmd_managedobj managedobj;

} pmd_number_pres;

/* CNumberPresentationConditionElement */
typedef struct t_pmd_number_pres_cond_el
{
    /* CManagedObject - must be first element in this structure */
    pmd_managedobj managedobj;

    /* condition element */
    const pmd_cond_el* cond_el;

    /* presentation element */
    const pmd_number_pres* pres;

    /* pointer to next element in the list (NULL if none) */
    struct t_pmd_number_pres_cond_el* next;

} pmd_number_pres_cond_el;

/* CNumberPresentationCondition */
typedef struct t_pmd_number_pres_cond
{
    /* CNumberPresentation - must be first element in this structure */
    pmd_number_pres number_pres;

    /* Number of presentation condition elements */
    unsigned int n_pres_cond_el;

    pmd_number_pres_cond_el* pres_cond_el;

    /* tag when flag PMD_NUMBER_PRESENTATION_CONDITION_HAS_TAG is set */
    const pmd_tag* tag;
    const char* tag_name;

    /* Default presentation (NULL if none) */
    const pmd_number_pres* default_pres;

} pmd_number_pres_cond;

/* CNumberPresentationConstant */
typedef struct t_pmd_number_pres_const
{
    /* CNumberPresentation - must be first element in this structure */
    pmd_number_pres number_pres;

    /* The actual presentation */
    const char* text;

} pmd_number_pres_const;

/* CNumberPresentationInfo */
typedef struct t_pmd_number_pres_info
{
    /* CNumberPresentation - must be first element in this structure */
    pmd_number_pres number_pres;

    /* PMD_INFO_TYPE_XXX */
    unsigned int info_group_id;

    /* Device ID of info group or PMD_DEVICE_GENERAL */
    unsigned short device_id;

    /* Default presentation (NULL if none) */
    const pmd_number_pres* default_pres;

} pmd_number_pres_info;

/* CNumberPresentationSimple */
typedef struct t_pmd_number_pres_simple
{
    /* CNumberPresentation - must be first element in this structure */
    pmd_number_pres number_pres;

    /* Presentation type (PMD_VALUE_PRESENTATION_XXX) */
    unsigned int type;

    /* Unit */
    const char* unit;

} pmd_number_pres_simple;

/* CNumberPresentationTimestamp */
typedef struct t_pmd_number_pres_time
{
    /* CNumberPresentation - must be first element in this structure */
    pmd_number_pres number_pres;

    /* Type of timestamp (PMD_TIMESTAMP_TYPE_XXX) */
    unsigned int type;

} pmd_number_pres_time;

/* CNumberPresentationTransform */
typedef struct t_pmd_number_pres_trans
{
    /* CNumberPresentation - must be first element in this structure */
    pmd_number_pres number_pres;

    /* scale and offset */
    double scale;
    double offset;

    /* Unit */
    const char* unit;

} pmd_number_pres_trans;

/* CNumberType */
typedef struct t_pmd_number
{
    /* CPrimitiveType - must be first element in this structure */
    pmd_primitive primitive;

    /* Length of number. Should be handled as signed, if flag PMD_NUMBER_IS_SIGNED is set */
    unsigned int length;

    /* Default value - only present if flag PMD_NUMBER_HAS_DEFAULT_VALUE is set */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long default_value;
#else
    unsigned int default_value;
#endif
    const char* default_value_str;

    /* Presentation object <abstract> */
    const pmd_number_pres* pres;

} pmd_number;

/* CStringType */
typedef struct t_pmd_string
{
    /* CPrimitiveType - must be first element in this structure */
    pmd_primitive primitive;

    /* String length definition */
    pmd_len length_obj;

    /* Character type (PMD_CHARACTER_TYPE_XXX) */
    unsigned short char_type;
        
    /* Unit of measure */
    const char* unit;

    /* BCD map (16 characters, only if flag PMD_STRING_HAS_BCD_MAP is set) */
    const char* bcd_map;

} pmd_string;

/* CSequenceElement object */
typedef struct t_pmd_seq_el
{
    /* Object ID and name of sequence elenet (object ID not used, as object is aggregated in CSequence) */
    pmd_namedobj namedobj;

    /* type */
    const pmd_typ* type;

    /* pointer to the next sequence element object in the list (NULL if none) */
    struct t_pmd_seq_el* next;

} pmd_seq_el;

/* CSequence */
typedef struct t_pmd_seq
{
    /* CConstructedType - must be first element in this structure */
    pmd_constructed constructed;

    /* Number of sequence elements */
    unsigned int n_seq_el;

    /* Pointer to the list of sequence elements to place in the sequence. 
       NULL if none
    */
    pmd_seq_el* seq_el;

    /* Pointer to the related sequence object in the autogen data model. 
       NULL if none
    */
    autogen_seq* org_seq;

    /* Type of the sequence (PMD_SEQUENCE_TYPE_XXX) */
    unsigned int seq_type;

    /* message / sub block length type */
    const pmd_typ* length_type;

} pmd_seq;

/* CFillerType */
typedef struct t_pmd_filler
{
    /* CType - must be first element in this structure */
    pmd_typ type;

    unsigned int n_bits;

} pmd_filler;

/* CFillerTypeDynamic */
typedef struct t_pmd_filler_dyn
{
    /* CFillerType - must be first element in this structure */
    pmd_filler filler;

    /* Alignment type (PMD_ALIGNMENT_MODULUS_XXX) */
    unsigned int alignment;

    /* Sequence type, which filler is calculated relatively from */
    const pmd_typ* ref_type;

} pmd_filler_dyn;

/* CFillerTypeStatic */
typedef struct t_pmd_filler_static
{
    /* CFillerType - must be first element in this structure */
    pmd_filler filler;

} pmd_filler_static;

/* CBlock */
typedef struct t_pmd_block
{
    /* CConstructedType - must be first element in this structure */
    pmd_constructed constructed;

    /* block algorithm (PMD_BLOCK_ALGORITHM_XXX) */
    unsigned int algorithm;

    /* type used for decoding messages */
    const pmd_seq* seq;

    /* Entry point data (for PMD_BLOCK_ALGORITHM_ENTRYPOINT) */
    const char* ep_name;
    unsigned short ep_id;
    unsigned short ep_device_id;

    /* DLL data (for PMD_BLOCK_ALGORITHM_EXTERNAL) */
    const char* dll_name;
    const char* dll_func;

    /* block attributes */
    const char* data1;
    const char* data2;
    unsigned int data_int;

} pmd_block;

/* CSequenceOf  */
typedef struct t_pmd_seq_of
{
    /* CConstructedType - must be first element in this structure */
    pmd_constructed constructed;

    /* array element type */
    const pmd_typ* type;

} pmd_seq_of;

/* CChoiceElement */
typedef struct t_pmd_choice_el
{
    /* CNamedObject - must be first element in this structure */
    pmd_namedobj namedobj;

    /* condition element */
    const pmd_cond_el* cond_el;

    /* type */
    const pmd_typ* type;

    /* pointer to next element in the list (NULL if none) */
    struct t_pmd_choice_el* next;

} pmd_choice_el;

/* CChoice */
typedef struct t_pmd_choice
{
    /* CConstructedType - must be first element in this structure */
    pmd_constructed constructed;

    /* tag */
    pmd_tag tag;

    /* Number of elements (conditions and types) */
    unsigned int n_choice_el;

    /* list of choice elements */
    pmd_choice_el* choice_el;

    /* Default case (NULL if none) */
    const pmd_typ* default_type;

    /* ID of entry point (only valid if flag PMD_CHOICE_ENTRY_POINT is set) */
    unsigned short entry_point_id;

    /* Name of entry point (only valid if flag PMD_CHOICE_ENTRY_POINT is set) */
    const char* entry_point_name;

    /* PMD_FILE_FORMAT 501 feature: include device_id to speed up decoding process */
    unsigned short device_id;

} pmd_choice;


/*  CMessage object 
*/
typedef struct t_pmd_msg
{
    /* Object ID and name of message */
    pmd_namedobj namedobj;

    /* ID of message/trace */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long id;
#else
    unsigned int id;
#endif

    /* Trace identifier (4 characters) 
       - Only valid if PMD_MESSAGE_HAS_IDENTIFIER is set
    */
    const char* identifier;

    /* message type, message belongs to, or NULL if none */
    struct t_pmd_msgtype* msgtype;

    /* message entity, message belongs to, or NULL if none */
    struct t_pmd_msgent* msgent;

    /* message group, message belongs to, or NULL if none */
    struct t_pmd_msggrp* msggrp;

    /* Function of message (PMD_FUNCTION_XXX) */
    unsigned short function;

    /* Related sequence describing message contents */
    const pmd_seq* ref_seq;

    /* Pointer to the next message object in the list (NULL if none) */
    struct t_pmd_msg* next;

} pmd_msg;


/* CMessageGroup object */
typedef struct t_pmd_msggrp
{
    /* Name and object ID of message group */
    pmd_namedobj namedobj;

	/* Type of message group */
	unsigned int type;

    /* Group ID */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long id;
#else
    unsigned int id;
#endif

    /* Message type, messge group belongs to, or NULL if none */
    struct t_pmd_msgtype* msgtype;

    /* Message entity, messge group belongs to, or NULL if none */
    struct t_pmd_msgent* msgent;

	/* Logical name */
	const char* logical_name;

    /* Trace identifier (4 characters) */
    const char* identifier;

	/* Resource object (for resource groups) */
	const autogen_res* res;

    /* Message objects */
    pmd_msg* messages;

	unsigned int n_messages;

    /* Type representing group in PMD model */
    pmd_typ* ref_type;

    struct t_pmd_msggrp* next;

} pmd_msggrp;

/* CMessageEntity object */
typedef struct t_pmd_msgent
{
    /* Name and object ID of message entity */
    pmd_namedobj namedobj;

	/* Logical name */
	const char* logical_name;

    /* Entity ID */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long id;
#else
    unsigned int id;
#endif

    /* Trace identifier (4 characters) */
    const char* identifier;

    /* Message type, entity belongs to */
    struct t_pmd_msgtype* msgtype;

    /* Trace group objects */
    pmd_msggrp* trace_groups;
	unsigned int n_trace_groups;

    /* Message objects */
    pmd_msg* messages;
	unsigned int n_messages;

    /* Type representing message entity in PMD model */
    pmd_typ* ref_type;

    struct t_pmd_msgent* next;

} pmd_msgent;

/* CMessageType object*/
typedef struct t_pmd_msgtype
{
    /* Name and object ID of message type (object ID is not used though) */
    pmd_namedobj namedobj;

    /* ID of object, PMD_MESSAGE_TYPE_XXX */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long id;
#else
    unsigned int id;
#endif

    /* Trace identifier (4 characters) */
    const char* identifier;

    /* Number of messages */
    unsigned int n_messages;

    /* Message objects */
    pmd_msg* messages;

    /* Message groups (resources) */
    unsigned int n_message_groups_res;
    pmd_msggrp* message_groups_res;

    /* Message groups (traces) */
    unsigned int n_message_groups_trc;
    pmd_msggrp* message_groups_trc;

    /* Message entities */
    unsigned int n_message_entitites;
    pmd_msgent* message_entities;

    /* Type representing message type in PMD model */
    pmd_typ* ref_type;

    struct t_pmd_msgtype* next;

} pmd_msgtype;

/* Info objects */
typedef struct t_pmd_info
{
    /* name and object ID of info (object ID is not used) */
    pmd_namedobj namedobj;

    /* ID of info object */
    unsigned int id;

    /* Data */
    unsigned int data[5];

    struct t_pmd_info* next;
    struct t_pmd_info* hash_next;

} pmd_info;

/* Info groups */
#define PMD_INFO_GROUP_HASH_SIZE 256
typedef struct t_pmd_info_group
{
    /* managed object */
    pmd_managedobj managedobj;

    /* type of info object, PMD_INFO_XXX */
    unsigned int type;

    /* Number of data in each info object */
    unsigned int n_data;

    /* Info objects  */
    unsigned int n_info;

    pmd_info* hash_table[PMD_INFO_GROUP_HASH_SIZE];

    pmd_info* info;

    struct t_pmd_info_group* next;

} pmd_info_group;

/*  */
typedef struct t_pmd_ref
{
    /* pointer to next reference */
    struct t_pmd_ref* next;

    /* reference name */
    const char* name;

    /* length / tag information */
    pmd_len len;

    /* item object of reference (original) */
    autogen_item_value* item;

} pmd_ref;

/* Environment variable objects */
typedef struct t_pmd_env
{
    /* pointer to the next env var object in the list (NULL if none) */
    struct t_pmd_env* next;

    /* managed object */
    pmd_managedobj managedobj;

    /* ID of environment variable */
    unsigned int id;

    /* type of environment variable */
    unsigned int type;

    /* value of variable */
    unsigned int value;

    /* value of variable (string) */
    const char* value_string;

} pmd_env_var;


/*  This structure contains the information about one definition module .
    When writing the PMD objects, each of these objects result in a 
    CDefinitionModule object 
*/
typedef struct t_pmd_mod
{
    /* pointer to the parent definition module in the list (NULL if root module) */
    struct t_pmd_mod* parent;

    /* pointer to the next definition module in the list (NULL if none) */
    struct t_pmd_mod* next;

    /* pointer to the list of child definition modules (NULL if none) */
    struct t_pmd_mod* child;

    /* pointer to the list of types to place in the module (NULL if none) */
    pmd_typ* type;

    /* pointer to the module sequence object (if present) */
    pmd_seq* seq;

    /* name of the definition  */
    char* name;

} pmd_mod;


/*  This structure contains the information about one paremeter.
    When writing the PMD objects, each of these objects result in a 
    CParameterFTD or CParameterPPC object 
*/
typedef struct t_pmd_par
{
    /* Object ID and name of parameter */
    pmd_namedobj namedobj;

    /* type of the parameter, e.g. PMD_PARAMETER_TYPE_RDD */
    unsigned int par_type;

    /* id of parameter, e.g. FTD/PPC id */
    unsigned int id;

    /* primitive type reference */
    const pmd_typ* ref_typ;

    /* is the parameter part of a set? */
    int is_set;

    /* if it is, what are the minimum and maximum number of arameters in the set? 
       min = max = 0 indicates that it is not known how many.. (as many as possible)
    */
    unsigned int par_set_n_min;
    unsigned int par_set_n_max;

    /* pointer to the next parameter object in the list (NULL if none) */
    struct t_pmd_par* next;

} pmd_par;

typedef struct t_pmd_entry_point
{
    /* Object ID and name of entry point */
    pmd_managedobj managedobj;

    /* Name of entry point - mainly for debugging */
    const char* name;

    /* ID of entry point */
    unsigned short id;

    /* pointer to type, describing entry point structure */
    const pmd_typ* ref_type;

    /* pointer to the next entry point in the list (NULL if none) */
    struct t_pmd_entry_point* next;

} pmd_entry_point;

/* CEntryPointSubTreeElement object */
typedef struct t_pmd_entry_point_subtree_el
{
    /* Object ID and name of element (object ID not used, as object is aggregated in CEntryPointSubTree) */
    pmd_namedobj namedobj;

    /* ID */
#if (PMD_FILE_FORMAT >= 600)
    unsigned long long id;
#else
    unsigned int id;
#endif

    /* type */
    const pmd_typ* type;

    /* device, which element 'belongs' to */
    unsigned short device_id;

    /* pointer to the next element object in the list (NULL if none) */
    struct t_pmd_entry_point_subtree_el* next;

} pmd_entry_point_subtree_el;

/* CEntryPointSubTree object */
typedef struct t_pmd_entry_point_subtree
{
    /* Entry point */
    pmd_entry_point entry_point;

    /* The following two elements are only valid if flag PMD_ENTRY_POINT_HAS_INFO_GROUP_DEPENDENCY is set */

    /* PMD_INFO_TYPE_XXX */
    unsigned int info_group_id;

    unsigned int n_el;

    pmd_entry_point_subtree_el* el;

} pmd_entry_point_subtree;


#if (PMD_FILE_FORMAT >= 610)
typedef struct t_pmd_debuginfo_FileInfo
{
    /* File name of compile unit */
    const char *file_name;

    /* Low and hign address of code in compile unit */
    unsigned long long low_address;
    unsigned long long high_address;

    /* Current directory of compiler when compiling this compile unit */
    const char *compile_dir;

    /* Id of this file - pmd_debuginfo_FuncInfo objects will refer to this */
    unsigned int id;
} pmd_debuginfo_FileInfo;

typedef struct t_pmd_debuginfo_FuncInfo
{
    /* Function name */
    const char *function_name;

    /* Low and hign address of function code */
    unsigned long long low_address;
    unsigned long long high_address;

    /* Line in file where this function is declared */
    unsigned int declared_line;

    /* Id of file (pmd_debuginfo_FileInfo) which contains this function */
    unsigned int id;
} pmd_debuginfo_FuncInfo;

typedef struct t_pmd_debuginfo_LineInfo
{
    /* Adresss */
    unsigned long long address; 

    /* Associated line number in source file */
    unsigned int lineNo; 
} pmd_debuginfo_LineInfo;

typedef struct t_pmd_debuginfo
{
    /* named object and name of .out file */
    pmd_namedobj namedobj;

    /* FileInfo objects */
    list_header *file_info_list;

    /* FuncInfo objects */
    list_header *func_info_list;

    /* LineInfo objects */
    list_header *line_info_list;

    /* Type of .out file */
    /* ET_EXEC = 2  Executable file    */
    /* ET_DYN  = 3  Shared object file */
    unsigned int type;

    /* Keeps track of current file info id */
    unsigned int current_fileinfo_id;

    /* Points to current compile unit element. NULL is current compile unit has been rejected */
    list_element *current_compile_unit_element;

    /* Next element */
    struct t_pmd_debuginfo *next;
} pmd_debuginfo;
#endif

/* structure used for reusing condition element interval objects */
typedef struct t_pmd_cond_el_int_reuse
{
    const pmd_cond_el_int* cond_el_int;

    struct t_pmd_cond_el_int_reuse* next;

} pmd_cond_el_int_reuse;

/* structure used for reusing condition element bitmask objects */
typedef struct t_pmd_cond_el_bit_reuse
{
    const pmd_cond_el_bit* cond_el_bit;

    struct t_pmd_cond_el_bit_reuse* next;

} pmd_cond_el_bit_reuse;

/* structure used for reusing simple number presentation objects */
typedef struct t_pmd_number_pres_simple_reuse
{
    const pmd_number_pres_simple* pres_simple;

    struct t_pmd_number_pres_simple_reuse* next;

} pmd_number_pres_simple_reuse;

/* structure used for reusing info number presentation objects */
typedef struct t_pmd_number_pres_info_reuse
{
    const pmd_number_pres_info* pres_info;

    struct t_pmd_number_pres_info_reuse* next;

} pmd_number_pres_info_reuse;


typedef struct t_pmd_cond_el_int_node
{
#if (PMD_FILE_FORMAT >= 600)
  long long key;
#else
  int key;
#endif
  pmd_cond_el_int* cond_el_int;
} pmd_cond_el_int_node;

typedef struct t_pmd_device
{
    /* Object ID and name of device */
    pmd_namedobj namedobj;

    /* Device ID */
    unsigned short id;

    /* Logical name of device */
    const char* logical_name;

    /* List of info group objects */
    unsigned int n_info_groups;
    pmd_info_group* info_groups;

    /* List of environment vars */
    unsigned int n_env_vars;
    pmd_env_var* env_vars;

    /* List of entry points */
    unsigned int n_entry_points;
    pmd_entry_point* entry_points;

    /* List of entry point sub trees */
    unsigned int n_entry_point_subtrees;
    pmd_entry_point* entry_point_subtrees;

    /* list of message types */
    unsigned int n_msgtypes;
    pmd_msgtype* msgtypes;

    /* ID of device which is master for this device. 
       Is only relevant if flag PMD_DEVICE_HAS_XTI_MASTER_DEVICE is set 
    */
    unsigned short xti_master_device_id;

    struct t_pmd_device* next;

} pmd_device;

typedef struct t_pmd_environmemt
{
    /* handle for all PMD related memory allocation */
    pmd_heap_handle* heap_handle;

    /* buffer for uncompressed string data*/
    pmd_token_buffer* string_token_buffer;

    /* buffer for uncompressed object data*/
    pmd_token_buffer* object_token_buffer;

    /* output buffer for compressed objects */
    pmd_bit_buffer* output_buffer;

    /* the highest string index in the string pool */
    unsigned int string_index_max;

    /* buffer for instance ID's */
    unsigned char* instance_map;

    /* pointer to whole list of module objects */
    pmd_mod* typ_root_module;

    /* common objects for 1..63 bit fixed fillers */
    pmd_typ* typ_fixed_filler[64];

    /* common objects for 1..63 bit hex values */
    pmd_typ* typ_value_hex[64];

    /* common objects for 1..63 bit hex values (tags) */
    pmd_typ* typ_value_hex_tag[64];

    /* common objects for 1..63 bit dec values */
    pmd_typ* typ_value_dec[64];

    /* common transaction ID */
    pmd_typ* typ_transaction_id;

    /* trace groups/ids */
    pmd_typ* typ_trace_type_entrypoint[AUTOGEN_OBJ_TRACEGRP_MAX];
    pmd_typ* typ_trace_entity_id[AUTOGEN_OBJ_TRACEGRP_MAX];
    pmd_typ* typ_trace_group_id[AUTOGEN_OBJ_TRACEGRP_MAX];
    pmd_typ* typ_trace_id[AUTOGEN_OBJ_TRACEGRP_MAX];
    pmd_typ* typ_trace_structure[AUTOGEN_OBJ_TRACEGRP_MAX];
    pmd_typ* typ_trace_data_dump[AUTOGEN_OBJ_TRACEGRP_MAX];

    /* must be split when not only 16 is supported */
    pmd_typ* typ_trace_data_length;

    /* types in PhoNet header */
    pmd_typ* typ_pn_root_seq;
    pmd_typ* typ_pn_receiver_device;
    pmd_typ* typ_pn_sender_device;
    pmd_typ* typ_pn_receiver_object;
    pmd_typ* typ_pn_sender_object;
    pmd_typ* typ_pn_resource;
    pmd_typ* typ_pn_length;
    pmd_choice* typ_pn_phonet_selection;
    pmd_choice* typ_pn_resource_selection;
    pmd_choice* typ_pn_private_selection;
    pmd_choice* typ_pn_prefix_selection;

    /* resource entry points */
    pmd_typ** typ_res_entrypoint;

    /* list of info group objects */
    unsigned int n_info_groups;
    pmd_info_group* info_groups;

    /* list of environment objects */
    unsigned int n_env_vars;
    pmd_env_var* env_vars;

    /* list of message type objects */
    unsigned int n_msgtypes;
    pmd_msgtype* msgtypes;

    /* list of entry points */
    unsigned int n_entry_points;
    pmd_entry_point* entry_points;

    /* list of entry point subtrees */
    unsigned int n_entry_point_subtrees;
    pmd_entry_point* entry_point_subtrees;

    /* object ID */
    unsigned int last_object_id;

    /* should debug info be generated to text file(s)? */
    int include_debug;

    /* size of file */
    long file_size;

    /* last pn_dev type (to be used as tag) */
    pmd_typ* typ_last_pn_dev;

    /* PMD file restriction. AUTOGEN_PMD_FILE_RESTRICTION_XXX */
    int file_restriction;

    /* PMD file restriction. PMD_FILE_RESTRICTION_XXX */
    int file_restriction_pmd;

    /* object reuse list */
    pmd_cond_el_bit_reuse* cond_el_bit_reuse;
    pmd_number_pres_simple_reuse* pres_simple_reuse;
    pmd_number_pres_info_reuse* pres_info_reuse;

    pmd_cond_el_int_node *cond_el_int_list;
    unsigned cond_el_int_list_size;
    unsigned cond_el_int_list_used;

    /* flags which all objects must have */
    unsigned int flag_all;

    /* Device ID (for PMD file type PMD_FILE_TYPE_DEVICE) */
    unsigned short device_id;

    /* Devices */
    unsigned int n_devices;
    pmd_device* devices;

    /* Count of printf format string info objects */
    unsigned int printf_info_obj_count;

#if (PMD_FILE_FORMAT >= 610)
    /* Debug information from .out file */
    pmd_debuginfo *debuginfo;
#endif
} pmd_env;

#define PMD_WRITE_ENVVAR_OBJECT_IDS     0x00000001
#define PMD_WRITE_ENVVAR_DATA           0x00000002

#define PMD_WRITE_MSG_OBJECT_IDS        0x00000010
#define PMD_WRITE_MSG_DATA              0x00000020

#define PMD_WRITE_COUNTERS              0x00000100

/* ============================================================================================= */
/* output_pmd.c */
/* ============================================================================================= */

void                        pmd_write_byte(pmd_env* env, unsigned char value);
void                        pmd_write_word(pmd_env* env, unsigned int value);
void                        pmd_write_dword(pmd_env* env, unsigned int value);
#if (PMD_FILE_FORMAT >= 600)
void                        pmd_write_ddword(pmd_env* env, unsigned long long value);
#endif
void                        pmd_write_string(pmd_env* env, const char* str);
void                        pmd_write_objid(pmd_env* env, const pmd_managedobj* managed_obj);
void                        pmd_write_objid_null(pmd_env* env);

/* ============================================================================================= */
/* output_pmd_generate.c */
/* ============================================================================================= */

void                        pmd_generate_model(pmd_env* env);

/* ============================================================================================= */
/* output_pmd_info.c */
/* ============================================================================================= */

const char*                 pmd_env_lookup_string(pmd_env* env, unsigned short device_id, unsigned int id);
void                        pmd_env_vars_generate(pmd_env* env);
void                        pmd_env_vars_write_all(pmd_env* env, unsigned int n_envvars, const pmd_env_var* envvars, unsigned int flags);

pmd_info*                   pmd_info_add(pmd_env* env, unsigned short device_id, unsigned int type, const char* name, 
                                         unsigned int id, unsigned int n_data,
                                         unsigned int data1, unsigned int data2, 
                                         unsigned int data3, unsigned int data4);
pmd_info*                   pmd_info_add_uncond(pmd_env* env, unsigned short device_id, unsigned int type, const char* name, 
                                                unsigned int id, unsigned int n_data,
                                                unsigned int data1, unsigned int data2, 
                                                unsigned int data3, unsigned int data4);

pmd_info_group*             pmd_info_group_add(pmd_env* env, unsigned short device_id, unsigned int type, unsigned int n_data);

void                        pmd_info_groups_generate(pmd_env* env);
void                        pmd_info_groups_write_all(pmd_env* env, unsigned int n_infogroups, const pmd_info_group* infogroups);

/* ============================================================================================= */
/* output_pmd_msg.c */
/* ============================================================================================= */
#if (PMD_FILE_FORMAT >= 600)

pmd_msgtype*                pmd_msgtype_create(pmd_env* env, unsigned short device_id, unsigned long long id, const char* name, 
                                               const char* identifier, unsigned int flags);

void                        pmd_msgtype_insert_in_device(pmd_env* env, unsigned short device_id, pmd_msgtype* msgtype);

pmd_msgtype*                pmd_msgtype_add(pmd_env* env, unsigned short device_id, unsigned long long id, const char* name, 
                                            const char* identifier, unsigned int flags);

pmd_msgtype*                pmd_msgtype_find(pmd_env* env, unsigned short device_id, unsigned long long id);
void                        pmd_msgtype_write(pmd_env* env, const pmd_msgtype* msgtype, unsigned int flags);
void                        pmd_msgtypes_write_all(pmd_env* env, unsigned int n_msgtypes, const pmd_msgtype* msgtypes, unsigned int flags);

pmd_msgent*                 pmd_msgent_add(pmd_env* env, pmd_msgtype* msgtype, 
                                              unsigned long long id, const char* name, const char* logical_name, const char* identifier);
pmd_msgent*                 pmd_msgent_find(pmd_msgtype* msgtype, unsigned long long id);

pmd_msggrp*                 pmd_msggrp_res_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, unsigned long long id, 
                                               const char* name, const char* logical_name, 
                                               const autogen_res* res);
pmd_msggrp*                 pmd_msggrp_res_create(pmd_env* env, pmd_msgtype* msgtype, unsigned long long id, 
                                                  const char* name, const char* logical_name, 
                                                  const autogen_res* res);
pmd_msggrp*                 pmd_msggrp_res_find_in_msgtype(pmd_msgtype* msgtype, const autogen_res* res);
void                        pmd_msggrp_res_insert_in_msgtype(pmd_msgtype* msgtype, pmd_msggrp* msggrp);

pmd_msggrp*                 pmd_msggrp_trc_create(pmd_env* env, unsigned long long id, const char* name, const char* identifier, const char* logical_name);

pmd_msggrp*                 pmd_msggrp_trc_add_to_msgent(pmd_env* env, pmd_msgent* msgent, unsigned long long id, const char* identifier, const char* name, const char* logical_name);
pmd_msggrp*                 pmd_msggrp_trc_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, unsigned long long id, const char* identifier, const char* name, const char* logical_name);

pmd_msg*                    pmd_msg_add_to_msgent(pmd_env* env, pmd_msgent* msgent, const char* name, unsigned long long id, const pmd_seq* seq);
pmd_msg*                    pmd_msg_add_to_msggrp(pmd_env* env, pmd_msggrp* msggrp, const char* name, unsigned long long id, const pmd_seq* seq);
pmd_msg*                    pmd_msg_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, const char* name, unsigned long long id, const pmd_seq* seq);
void                        pmd_msg_write_all(pmd_env* env);

#else

pmd_msgtype*                pmd_msgtype_create(pmd_env* env, unsigned short device_id, unsigned int id, const char* name, 
                                               const char* identifier, unsigned int flags);

void                        pmd_msgtype_insert_in_device(pmd_env* env, unsigned short device_id, pmd_msgtype* msgtype);

pmd_msgtype*                pmd_msgtype_add(pmd_env* env, unsigned short device_id, unsigned int id, const char* name, 
                                            const char* identifier, unsigned int flags);

pmd_msgtype*                pmd_msgtype_find(pmd_env* env, unsigned short device_id, unsigned int id);
void                        pmd_msgtype_write(pmd_env* env, const pmd_msgtype* msgtype, unsigned int flags);
void                        pmd_msgtypes_write_all(pmd_env* env, unsigned int n_msgtypes, const pmd_msgtype* msgtypes, unsigned int flags);

pmd_msgent*                 pmd_msgent_add(pmd_env* env, pmd_msgtype* msgtype, 
                                              unsigned int id, const char* name, const char* logical_name, const char* identifier);
pmd_msgent*                 pmd_msgent_find(pmd_msgtype* msgtype, unsigned int id);

pmd_msggrp*                 pmd_msggrp_res_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, unsigned int id, 
                                               const char* name, const char* logical_name, 
                                               const autogen_res* res);
pmd_msggrp*                 pmd_msggrp_res_create(pmd_env* env, pmd_msgtype* msgtype, unsigned int id, 
                                                  const char* name, const char* logical_name, 
                                                  const autogen_res* res);
pmd_msggrp*                 pmd_msggrp_res_find_in_msgtype(pmd_msgtype* msgtype, const autogen_res* res);
void                        pmd_msggrp_res_insert_in_msgtype(pmd_msgtype* msgtype, pmd_msggrp* msggrp);

pmd_msggrp*                 pmd_msggrp_trc_create(pmd_env* env, unsigned int id, const char* name, const char* identifier, const char* logical_name);

pmd_msggrp*                 pmd_msggrp_trc_add_to_msgent(pmd_env* env, pmd_msgent* msgent, unsigned int id, const char* identifier, const char* name, const char* logical_name);
pmd_msggrp*                 pmd_msggrp_trc_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, unsigned int id, const char* identifier, const char* name, const char* logical_name);

pmd_msg*                    pmd_msg_add_to_msgent(pmd_env* env, pmd_msgent* msgent, const char* name, unsigned int id, const pmd_seq* seq);
pmd_msg*                    pmd_msg_add_to_msggrp(pmd_env* env, pmd_msggrp* msggrp, const char* name, unsigned int id, const pmd_seq* seq);
pmd_msg*                    pmd_msg_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, const char* name, unsigned int id, const pmd_seq* seq);
void                        pmd_msg_write_all(pmd_env* env);

#endif

/* ============================================================================================= */
/* output_pmd_elf.c */
/* ============================================================================================= */

#if (defined AUTOGEN_INCLUDE_NOS_TRACES && defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU) 
void                        pmd_elf_generate_elf(pmd_env* env, FILE* fout, char* out_filename);
#endif /* AUTOGEN_INCLUDE_NOS_TRACES && AUTOGEN_ENVIRONMENT_PRODUCT_MCU

/* ============================================================================================= */
/* output_pmd_debug.c */
/* ============================================================================================= */

void                        pmd_debug_dump_file(pmd_env* env);

/* ============================================================================================= */
/* output_pmd_types.c */
/* ============================================================================================= */

pmd_block*                  pmd_block_create(pmd_env* env, const char* name, unsigned int alg);
pmd_block*                  pmd_block_dll_create(pmd_env* env, const char* name, const char* dll_name, const char* dll_func);
pmd_block*                  pmd_block_entry_point_create(pmd_env* env, const char* name, const char* ep_name, unsigned short ep_id, unsigned short ep_device_id);
pmd_typ*                    pmd_block_clone(pmd_env* env, const pmd_block* org_block);
void                        pmd_block_write(pmd_env* env, const pmd_block* block);

pmd_choice*                 pmd_choice_create(pmd_env* env, const char* name, const pmd_typ* default_type, unsigned short device_id);
pmd_typ*                    pmd_choice_clone(pmd_env* env, const pmd_choice* org_choice);
void                        pmd_choice_set_data_order_little_endian(pmd_choice* choice);
void                        pmd_choice_write(pmd_env* env, const pmd_choice* choice);

pmd_choice_el*              pmd_choice_el_create(pmd_env* env, const char* name, const pmd_cond_el* cond_el, const pmd_typ* type);
pmd_choice_el*              pmd_choice_el_clone(pmd_env* env, const pmd_choice_el* org_choice_el);
void                        pmd_choice_el_add(pmd_env* env, pmd_choice* choice, const char* name, const pmd_cond_el* cond_el, const pmd_typ* type);
void                        pmd_choice_el_add_mask(pmd_env* env, pmd_choice* choice, const char* name, const char* mask, const pmd_typ* type);
#if (PMD_FILE_FORMAT >= 600)
void                        pmd_choice_el_add_simple(pmd_env* env, pmd_choice* choice, const char* name, long long id, const pmd_typ* type);
#else
void                        pmd_choice_el_add_simple(pmd_env* env, pmd_choice* choice, const char* name, int id, const pmd_typ* type);
#endif
void                        pmd_choice_el_write(pmd_env* env, const pmd_choice_el* choice_el);

void                        pmd_cond_el_init(pmd_cond_el* cond_el, unsigned short class_id, unsigned int object_id);
void                        pmd_cond_el_clone(pmd_cond_el* cond_el, const pmd_cond_el* org_cond_el);
pmd_cond_el*                pmd_cond_el_clone_any(pmd_env* env, const pmd_cond_el* org_cond_el);
void                        pmd_cond_el_write(pmd_env* env, const pmd_cond_el* cond_el);
void                        pmd_cond_el_write_any(pmd_env* env, const pmd_cond_el* cond_el);

pmd_cond_el*                pmd_cond_el_bit_create(pmd_env* env, const char* bitstate);
pmd_cond_el*                pmd_cond_el_bit_clone(pmd_env* env, const pmd_cond_el_bit* org_cond_el_bit);
void                        pmd_cond_el_bit_write(pmd_env* env, const pmd_cond_el_bit* cond_el_bit);

#if (PMD_FILE_FORMAT >= 600)
pmd_cond_el*                pmd_cond_el_int_create(pmd_env* env, long long from, long long to);
#else
pmd_cond_el*                pmd_cond_el_int_create(pmd_env* env, int from, int to);
#endif
pmd_cond_el*                pmd_cond_el_int_clone(pmd_env* env, const pmd_cond_el_int* org_cond_el_int);
void                        pmd_cond_el_int_write(pmd_env* env, const pmd_cond_el_int* cond_el_int);

void                        pmd_constructed_init(pmd_env* env, pmd_constructed* constructed, unsigned short class_id, const char* name);
void                        pmd_constructed_clone(pmd_constructed* constructed, const pmd_constructed* org_constructed);
void                        pmd_constructed_write(pmd_env* env, const pmd_constructed* constructed);

#if (PMD_FILE_FORMAT >= 610)
pmd_debuginfo*              pmd_debuginfo_create(pmd_env *env, const char *filename, unsigned int filetype);
void                        pmd_debuginfo_write(pmd_env* env, pmd_debuginfo *debuginfo);
#endif

pmd_device*                 pmd_device_add(pmd_env* env, unsigned short device_id, const char* name, const char* logical_name);
pmd_device*                 pmd_device_add_default(pmd_env* env, unsigned short device_id);
pmd_device*                 pmd_device_find(pmd_env* env, unsigned short device_id);
void                        pmd_device_write_all(pmd_env* env);
void						pmd_device_write(pmd_env* env, const pmd_device* device);

pmd_entry_point*            pmd_entry_point_create(pmd_env* env, unsigned short device_id, const char* name, unsigned short id, const pmd_typ* ref_type);
void                        pmd_entry_point_add(pmd_env* env, unsigned short device_id, pmd_entry_point* entry_point);
pmd_entry_point*            pmd_entry_point_find(pmd_env* env, unsigned short device_id, unsigned short id, int is_subtree);
void                        pmd_entry_point_write(pmd_env* env, const pmd_entry_point* entry_point);
void                        pmd_entry_points_write_all(pmd_env* env, unsigned int n_entry_points, const pmd_entry_point* entry_points);

pmd_entry_point*            pmd_entry_point_subtree_create(pmd_env* env, unsigned short id, unsigned int info_group);
void                        pmd_entry_point_subtree_add(pmd_env* env, pmd_entry_point* entry_point);
#if (PMD_FILE_FORMAT >= 600)
void                        pmd_entry_point_subtree_el_add(pmd_env* env, unsigned short device_id, pmd_entry_point* entry_point, const char* name, unsigned long long id, const pmd_typ* ref_type);
#else
void                        pmd_entry_point_subtree_el_add(pmd_env* env, unsigned short device_id, pmd_entry_point* entry_point, const char* name, unsigned int id, const pmd_typ* ref_type);
#endif
void                        pmd_entry_point_subtree_el_write(pmd_env* env, const pmd_entry_point_subtree_el* el);

void                        pmd_filler_init(pmd_env* env, pmd_filler* filler, unsigned short class_id, const char* name, unsigned int n_bits);
void                        pmd_filler_clone(pmd_filler* filler, const pmd_filler* org_filler);
void                        pmd_filler_write(pmd_env* env, const pmd_filler* filler);

pmd_filler_dyn*             pmd_filler_dyn_create(pmd_env* env, const char* name, unsigned int n_bits, unsigned int alignment, const pmd_seq* ref_seq);
pmd_typ*                    pmd_filler_dyn_clone(pmd_env* env, const pmd_filler_dyn* org_filler_dyn);
void                        pmd_filler_dyn_write(pmd_env* env, const pmd_filler_dyn* filler);

pmd_filler_static*          pmd_filler_static_create(pmd_env* env, const char* name, unsigned int n_bits);
pmd_typ*                    pmd_filler_static_clone(pmd_env* env, const pmd_filler_static* org_filler_static);
void                        pmd_filler_static_write(pmd_env* env, const pmd_filler_static* filler);

void                        pmd_length_clear(pmd_len* length);
void                        pmd_length_init(pmd_len* length_obj, int length, unsigned short algorithm);
void                        pmd_length_init_as_many_as_possible(pmd_len* length_obj, const pmd_seq* seq, unsigned short algorithm);
void                        pmd_length_init_as_tag(pmd_len* length_obj, const pmd_typ* type);
void                        pmd_length_init_reference(pmd_env* env, pmd_len* length_obj, const pmd_ref* ref_list, autogen_ref* org_ref);
void                        pmd_length_init_reference_add_1(pmd_env* env, pmd_len* length_obj, const pmd_ref* ref_list, autogen_ref* org_ref);
void                        pmd_length_init_from_item(pmd_env* env, pmd_len* length_obj, autogen_item* item, const pmd_seq* seq, const pmd_ref* ref_lst);
void                        pmd_length_clone(pmd_len* length_obj, const pmd_len* org_length_obj);
void                        pmd_length_write(pmd_env* env, const pmd_len* length);

void                        pmd_managedobj_init(pmd_managedobj* managed_obj, int stream_obj_id, unsigned short class_id, unsigned int object_id);
void                        pmd_managedobj_clone(pmd_managedobj* managed_obj, const pmd_managedobj* org_maanged_obj);
void                        pmd_managedobj_write(pmd_env* env, const pmd_managedobj* managed_obj);

void                        pmd_managedobj_clear(pmd_managedobj* managed_obj, int stream_obj_id);
void                        pmd_namedobj_init(pmd_env* env, pmd_namedobj* namedobj, const char* name, int stream_obj_id, unsigned short class_id, unsigned int object_id);
void                        pmd_namedobj_clone(pmd_namedobj* namedobj, const pmd_namedobj* org_namedobj);
void                        pmd_namedobj_write(pmd_env* env, const pmd_namedobj* namedobj);

pmd_number*                 pmd_number_create(pmd_env* env, const char* name, int length, unsigned int special_type);
pmd_typ*                    pmd_number_clone(pmd_env* env, const pmd_number* org_number);
#if (PMD_FILE_FORMAT >= 600)
void                        pmd_number_set_default_value(pmd_env* env, pmd_number* number, unsigned long long value, const char* value_str);
#else
void                        pmd_number_set_default_value(pmd_env* env, pmd_number* number, unsigned int value, const char* value_str);
#endif
void                        pmd_number_set_data_order_little_endian(pmd_number* number);

void                        pmd_number_write(pmd_env* env, const pmd_number* number);

void                        pmd_number_pres_init(pmd_number_pres* pres, unsigned short class_id, unsigned int object_id);
void                        pmd_number_pres_clone(pmd_number_pres* pres, const pmd_number_pres* org_pres);
pmd_number_pres*            pmd_number_pres_clone_any(pmd_env* env, const pmd_number_pres* org_pres);
void                        pmd_number_pres_write(pmd_env* env, const pmd_number_pres* pres);
void                        pmd_number_pres_write_any(pmd_env* env, const pmd_number_pres* pres);

pmd_number_pres_cond*       pmd_number_pres_cond_create(pmd_env* env, const pmd_number_pres* default_pres);
void                        pmd_number_pres_cond_set_tag(pmd_env* env, pmd_number_pres_cond* pres_cond, const pmd_typ* typ);
pmd_number_pres*            pmd_number_pres_cond_clone(pmd_env* env, const pmd_number_pres_cond* org_pres_cond);
void                        pmd_number_pres_cond_write(pmd_env* env, const pmd_number_pres_cond* pres_cond);

pmd_number_pres_cond_el*    pmd_number_pres_cond_el_create(pmd_env* env, const pmd_cond_el* cond_el, const pmd_number_pres* pres);
pmd_number_pres_cond_el*    pmd_number_pres_cond_el_clone(pmd_env* env, const pmd_number_pres_cond_el* org_pres_cond_el);
void                        pmd_number_pres_cond_el_add(pmd_number_pres_cond* pres_cond, pmd_number_pres_cond_el* pres_cond_el);
#if (PMD_FILE_FORMAT >= 600)
void                        pmd_number_pres_cond_el_add_simple(pmd_env* env, pmd_number_pres_cond* pres_cond, long long id, const char* name);
#else
void                        pmd_number_pres_cond_el_add_simple(pmd_env* env, pmd_number_pres_cond* pres_cond, int id, const char* name);
#endif
void                        pmd_number_pres_cond_el_write(pmd_env* env, const pmd_number_pres_cond_el* pres_el);

pmd_number_pres*            pmd_number_pres_const_create(pmd_env* env, const char* text);
pmd_number_pres*            pmd_number_pres_const_clone(pmd_env* env, const pmd_number_pres_const* org_pres_const);
void                        pmd_number_pres_const_write(pmd_env* env, const pmd_number_pres_const* pres_const);

pmd_number_pres*            pmd_number_pres_info_create(pmd_env* env, unsigned int info_group_id, unsigned short device_id, const pmd_number_pres* default_pres);
pmd_number_pres*            pmd_number_pres_info_clone(pmd_env* env, const pmd_number_pres_info* org_pres_info);
void                        pmd_number_pres_info_write(pmd_env* env, const pmd_number_pres_info* pres_info);

pmd_number_pres*            pmd_number_pres_simple_create(pmd_env* env, unsigned int type, const char* unit);
pmd_number_pres*            pmd_number_pres_simple_clone(pmd_env* env, const pmd_number_pres_simple* org_pres_simple);
void                        pmd_number_pres_simple_write(pmd_env* env, const pmd_number_pres_simple* pres_simple);

pmd_number_pres*            pmd_number_pres_time_create(pmd_env* env, unsigned int type);
pmd_number_pres*            pmd_number_pres_time_clone(pmd_env* env, const pmd_number_pres_time* org_pres_time);
void                        pmd_number_pres_time_write(pmd_env* env, const pmd_number_pres_time* pres_time);

pmd_number_pres*            pmd_number_pres_trans_create(pmd_env* env, double scale, double offset, const char* unit);
pmd_number_pres*            pmd_number_pres_trans_clone(pmd_env* env, const pmd_number_pres_trans* org_pres_trans);
void                        pmd_number_pres_trans_write(pmd_env* env, const pmd_number_pres_trans* pres_trans);

void                        pmd_primitive_init(pmd_env* env, pmd_primitive* primitive, unsigned short class_id, const char* name, unsigned int special_type);
void                        pmd_primitive_clone(pmd_primitive* primitive, const pmd_primitive* org_primitive);
void                        pmd_primitive_write(pmd_env* env, const pmd_primitive* primitive);

pmd_seq*                    pmd_seq_create(pmd_env* env, const char* name, unsigned int seq_type);
pmd_typ*                    pmd_seq_clone(pmd_env* env, const pmd_seq* org_seq);
void                        pmd_seq_write(pmd_env* env, const pmd_seq* seq);

pmd_seq_el*                 pmd_seq_el_create(pmd_env* env, const char* name, const pmd_typ* type);
pmd_seq_el*                 pmd_seq_el_add(pmd_env* env, pmd_seq* seq, const char* name, const pmd_typ* type);
pmd_seq_el*                 pmd_seq_el_add_as_array(pmd_env* env, autogen_item* item, const pmd_typ* type, const pmd_ref* ref_lst, pmd_mod* mod, unsigned int vec_flags, unsigned int el_flags);
pmd_seq_el*                 pmd_seq_el_clone(pmd_env* env, const pmd_seq_el* org_seq_el);
void                        pmd_seq_el_write(pmd_env* env, const pmd_seq_el* seq_el);

pmd_seq_of*                 pmd_seq_of_create(pmd_env* env, const char* name, const pmd_typ* type);
pmd_typ*                    pmd_seq_of_clone(pmd_env* env, const pmd_seq_of* org_seq_of);
void                        pmd_seq_of_write(pmd_env* env, const pmd_seq_of* seq_of);

pmd_string*                 pmd_string_create(pmd_env* env, const char* name, unsigned short char_type, const char* unit);
pmd_typ*                    pmd_string_clone(pmd_env* env, const pmd_string* org_str);
void                        pmd_string_set_bcd_map(pmd_env* env, pmd_string* str, const char* bcd_map);
void                        pmd_string_set_data_order_little_endian(pmd_string* str);
void                        pmd_string_write(pmd_env* env, const pmd_string* str);

pmd_tag*                    pmd_tag_create(pmd_env* env, const pmd_typ* ref_type, unsigned short bit_pos, unsigned short rel_pos);
void                        pmd_tag_clear(pmd_tag* tag);
void                        pmd_tag_init(pmd_tag* tag, const pmd_typ* ref_type, unsigned short bit_pos, unsigned short rel_pos);
const pmd_ref*              pmd_tag_init_reference(pmd_env* env, pmd_tag* tag, const pmd_ref* ref_list, const char* ref_name, autogen_ref* org_ref);
void                        pmd_tag_clone(pmd_tag* tag, const pmd_tag* org_tag);
void                        pmd_tag_write(pmd_env* env, const pmd_tag* tag);

void                        pmd_type_init(pmd_env* env, pmd_typ* type, unsigned short class_id, const char* name);
void                        pmd_type_clone(pmd_typ* type, const pmd_typ* org_type);
pmd_typ*                    pmd_type_clone_any(pmd_env* env, const pmd_typ* org_type);
void                        pmd_type_write(pmd_env* env, const pmd_typ* type);
void                        pmd_type_write_any(pmd_env* env, const pmd_typ* type);

/* ============================================================================================= */
/* output_pmd_typedef.c */
/* ============================================================================================= */

pmd_mod*                    pmd_typedef_module_add(pmd_env* env, const char* name, pmd_mod* par_mod);
pmd_mod*                    pmd_typedef_module_lookup(const char* name, pmd_mod* par_mod);
const char*                 pmd_typedef_module_get_name_from_object(const autogen_obj* obj);
void                        pmd_typedef_module_write(pmd_env* env, const pmd_mod* mod);

void                        pmd_typedef_type_add(pmd_mod* module, pmd_typ* type);
pmd_typ*                    pmd_typedef_type_lookup(const char* name, pmd_mod* module, int search_recursively);

/* ============================================================================================= */
/* autogen_vendor.c */
/* ============================================================================================= */
#ifdef AUTOGEN_INCLUDE_VENDOR_DLL_TRACE
#ifdef AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION
void                        autogen_import_chipset_supplier_description(pmd_env* env, const char *xml_filename, int file_restriction);
#endif /* AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION */
#endif /* AUTOGEN_INCLUDE_VENDOR_DLL_TRACE */

#endif /* _OUTPUT_PMD_H_ */


/*  End of output_pmd.h  */
