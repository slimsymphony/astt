/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_prop.h
                --------------
                SW Include






Project:          autogen

%name:            autogen_prop.h %
%version:         co1tss#9 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Wed Nov 11 16:47:27 2009 %

Copyright (c) Nokia. All rights reserved
*/

#ifndef _AUTOGEN_PROP_H_
#define _AUTOGEN_PROP_H_

#include "autogen_object.h"


/* This flag indicates that no value is associated with the property */
#define PROPERTY_FLAG_SIMPLE                0x00000001U

/* This flag indicates that a numeric value is associated with the property */
#define PROPERTY_FLAG_VALUE                 0x00000002U

/* This flag indicates that a string value is associated with the property */
#define PROPERTY_FLAG_STRING                0x00000004U

/* This is a mask for all of the above types */
#define PROPERTY_FLAG_ALLTYPES              (PROPERTY_FLAG_SIMPLE | PROPERTY_FLAG_VALUE | PROPERTY_FLAG_STRING)

/* This flag indicates that the property is indexed */
#define PROPERTY_FLAG_INDEX                 0x00000010U

/* This flag indicates that a string value is associated with the indexed property */
#define PROPERTY_FLAG_STRING_INDEX          (PROPERTY_FLAG_STRING | PROPERTY_FLAG_INDEX)

/* This flag indicates that a numeric value is associated with the indexed property */
#define PROPERTY_FLAG_VALUE_INDEX           (PROPERTY_FLAG_VALUE | PROPERTY_FLAG_INDEX)

/* This flag allows multiple instanced of the same property. Valid only on types */
#define PROPERTY_FLAG_MULTIPLE              0x00010000U

/* This flag indicates that the old name should be used for error messages. Valid only on properties */
#define PROPERTY_FLAG_USE_OLDNAME           0x00020000U

/* This flag indicates any string value must be a valid definition name. Valid only on types */
#define PROPERTY_FLAG_VALID_DEFINITION_NAME         0x00100000U

/* This flag indicates any string value must be a valid definition name (with an asterix *). Valid only on types */
#define PROPERTY_FLAG_VALID_DEFINITION_NAME_ASTERIX 0x00200000U

/* This flag indicates any string value must be a valid ISI header file identifier. Valid only on types */
#define PROPERTY_FLAG_VALID_ISIHDR_STRING   0x00400000U

/* This flag indicates any string value must not be empty. Valid only on types */
#define PROPERTY_FLAG_NONEMPTY              0x00800000U

/* This flag indicates that the object flags depends on whether the string is empty. Valid only on types */
#define PROPERTY_FLAG_OBJ_FLAG_IF_EMPTY     0x01000000U

/* This flag indicates that the property is obsolete. Valid only on types */
#define PROPERTY_FLAG_OBSOLETE              0x02000000U

/* This flag indicates that this is a default value. Valid only on properties */
#define PROPERTY_FLAG_DEFAULT               0x04000000U

/* This flag indicates that this is a negative value. Valid only on properties */
#define PROPERTY_FLAG_NEGATIVE              0x08000000U


/*** Functions working on the current property list ***/

/* Adds a simple property to the current property list */
extern void prop_add_simple(autogen_property_id id,
                            int lineno,
                            int is_oldname);

/* Adds a string property to the current property list */
extern void prop_add_string(autogen_property_id id,
                            const char *str,
                            int lineno,
                            int is_oldname);

/* Adds a value property to the current property list */
#if (PMD_FILE_FORMAT >= 600)
extern void prop_add_value(autogen_property_id id,
                           unsigned long long value,
                           int is_negative,
                           const char* str,
                           int lineno,
                           int is_oldname);
#else
extern void prop_add_value(autogen_property_id id,
                           unsigned int value,
                           int is_negative,
                           const char* str,
                           int lineno,
                           int is_oldname);
#endif

/* Adds an indexed string property to the current property list */
extern void prop_add_indexed_string(autogen_property_id id,
                                    const char *str,
                                    int index,
                                    int lineno,
                                    int is_oldname);

/* Adds an indexed value property to the current property list */
extern void prop_add_indexed_value(autogen_property_id id,
#if (PMD_FILE_FORMAT >= 600)
                                   unsigned long long value,
#else
                                   unsigned int value,
#endif
                                   int is_negative,
                                   const char* str,
                                   int index,
                                   int lineno,
                                   int is_oldname);

/* Adds a default string property to the current property list */
extern void prop_add_string_default(autogen_property_id id,
                                    const char *str);

/* Adds a default value property to the current property list */
extern void prop_add_value_default(autogen_property_id id,
                                   unsigned int value,
                                   int is_negative,
                                   const char* str);

/* Assigns all properties in the current property list to the given object and clears the list */
extern void prop_add_current_to_object(autogen_obj *obj,
                                       const char *filename);

/* Checks that the current list is empty, and erases it and prints a warning if not. */
extern void prop_force_current_empty(const char *filename);


/*** Functions adding properties directly to objects ***/


/* Adds a simple property to the given object */
extern void prop_add_simple_to_object(autogen_obj *obj,
                                      autogen_property_id id,
                                      const char *filename,
                                      int lineno,
                                      int is_oldname);

/* Adds a string property to the given object */
extern void prop_add_string_to_object(autogen_obj *obj,
                                      autogen_property_id id,
                                      const char *str,
                                      const char *filename,
                                      int lineno,
                                      int is_oldname);

/* Adds a value property to the given object */
extern void prop_add_value_to_object(autogen_obj *obj,
                                     autogen_property_id id,
                                     unsigned int value,
                                     int is_negative,
                                     const char* str,
                                     const char *filename,
                                     int lineno,
                                     int is_oldname);

/* Adds a combined string and value property to the current property list */
extern void prop_add_value_string_to_object(autogen_obj *obj,
                                            autogen_property_id id,
                                            unsigned int value,
                                            int is_negative,
                                            const char *str,
                                            const char *filename,
                                            int lineno,
                                            int is_oldname);

/* Adds an indexed string property to the given object */
extern void prop_add_indexed_string_to_object(autogen_obj *obj,
                                              autogen_property_id id,
                                              const char *str,
                                              int index,
                                              const char *filename,
                                              int lineno,
                                              int is_oldname);

/* Adds an indexed value property to the given object */
#if (PMD_FILE_FORMAT >= 600)
extern void prop_add_indexed_value_to_object(autogen_obj *obj,
                                             autogen_property_id id,
                                             unsigned long long value,
                                             int is_negative,
                                             const char *str,
                                             int index,
                                             const char *filename,
                                             int lineno,
                                             int is_oldname);
#else
extern void prop_add_indexed_value_to_object(autogen_obj *obj,
                                             autogen_property_id id,
                                             unsigned int value,
                                             int is_negative,
                                             const char *str,
                                             int index,
                                             const char *filename,
                                             int lineno,
                                             int is_oldname);
#endif

/* Adds a property to the object property list */
extern void prop_add_to_object(autogen_obj *obj,
                               autogen_prop *prop,
                               const char *filename);

/* Add a value to existing property */
#if (PMD_FILE_FORMAT >= 600)
extern void prop_object_add_value(autogen_obj *obj, autogen_property_id id, unsigned long long value, int is_negative);
#else
extern void prop_object_add_value(autogen_obj *obj, autogen_property_id id, unsigned int value, int is_negative);
#endif

/* Updates an existing value (or the value of a value_string) property on an object */
extern void prop_object_update_value(autogen_obj *obj,
                                     autogen_property_id id,
                                     unsigned int value,
                                     int is_negative);

/* Updates an existing string property on an object */
extern void prop_object_update_string(autogen_obj *obj,
                                      autogen_property_id id,
                                      const char* value);

/* Adds a copy of all properties in the given list to the given object */
extern void prop_copy_list_to_object(const autogen_prop* prop_list,
                                     autogen_obj *obj,
                                     const char *filename);

/*** Functions retrieving single property values ***/

/* Retrieves a string property. If not present, this function returns NULL */
extern const char *prop_get_string(const autogen_obj *obj,
                                   autogen_property_id id);

/* Retrieves a string property. If not present, this function returns the given default string */
extern const char *prop_get_string_default(const autogen_obj *obj,
                                           autogen_property_id id,
                                           const char *def);

/* Retrieves a value property. If not present, this function returns 0 */
#if (PMD_FILE_FORMAT >= 600)
extern unsigned long long prop_get_value(const autogen_obj *obj,
                                   autogen_property_id id);
#else
extern unsigned int prop_get_value(const autogen_obj *obj,
                                   autogen_property_id id);
#endif

/* Retrieves a value property. If not present, this function returns the given default value */
#if (PMD_FILE_FORMAT >= 600)
extern unsigned long long prop_get_value_default(const autogen_obj *obj,
                                           autogen_property_id id,
                                           unsigned int def);
#else
extern unsigned int prop_get_value_default(const autogen_obj *obj,
                                           autogen_property_id id,
                                           unsigned int def);
#endif


/*** Functions retrieving indexed property values ***/

/* Retrieves a string property with the given index. If not present, this function returns NULL */
extern const char *prop_get_string_indexed(const autogen_obj *obj,
                                           autogen_property_id id,
                                           int index);

/* Retrieves a string property with the given index. If not present, this function returns the given default string */
extern const char *prop_get_string_indexed_default(const autogen_obj *obj,
                                                   autogen_property_id id,
                                                   int index,
                                                   const char *def);

/* Retrieves a value property with the given index. If not present, this function returns 0 */
#if (PMD_FILE_FORMAT >= 600)
extern unsigned long long prop_get_value_indexed(const autogen_obj *obj,
                                           autogen_property_id id,
                                           int index);
#else
extern unsigned int prop_get_value_indexed(const autogen_obj *obj,
                                           autogen_property_id id,
                                           int index);
#endif

/* Retrieves a value property with the given index. If not present, this function returns the given default value */
#if (PMD_FILE_FORMAT >= 600)
extern unsigned long long prop_get_value_indexed_default(const autogen_obj *obj,
                                                   autogen_property_id id,
                                                   int index,
                                                   unsigned int def);
#else
extern unsigned int prop_get_value_indexed_default(const autogen_obj *obj,
                                                   autogen_property_id id,
                                                   int index,
                                                   unsigned int def);
#endif


/*** Functions browsing multiple property values ***/

/* Finds the first property with the given ID in a list of properties, or NULL if not found. */
extern const autogen_prop *prop_list_find_first(const autogen_prop *prop,
                                           autogen_property_id id);

/* Finds the next property with the same ID as prop_find_first, or NULL if not found. */
extern const autogen_prop *prop_list_find_next(const autogen_prop *prop);


/* Finds the first property with the given ID, or NULL if not found. */
extern const autogen_prop *prop_find_first(const autogen_obj *obj,
                                           autogen_property_id id);

/* Finds the next property with the same ID as prop_find_first, or NULL if not found. */
extern const autogen_prop *prop_find_next(const autogen_prop *prop);

/* Retrieves the count of the given property items for the given object */
extern int prop_count(const autogen_obj *obj,
                      autogen_property_id id);


/*** Miscellaneous functions ***/

/* Allocates a copy of the given property on the PMD heap */
extern autogen_prop* prop_copy(const autogen_prop* prop);

/* Checks whether the given object has the given property */
extern int prop_has(const autogen_obj *obj,
                    autogen_property_id id);

/* Checks if the given object has a non-empty string value as the given property */
extern int prop_has_valid_string(const autogen_obj *obj,
                                 autogen_property_id id);

/* Checks if the given object has a value as the given property */
extern int prop_has_value(const autogen_obj *obj,
                          autogen_property_id id);

/* Checks if the given property may be set without a value */
extern int prop_is_simple(autogen_property_id id);

/* Checks if the given property may be given a string */
extern int prop_is_string(autogen_property_id id);

/* Checks if the given property may be given a numeric value */
extern int prop_is_value(autogen_property_id id);

/* Retrieves the name for this property as it has been used */
const char *prop_name(const autogen_prop *prop);

/* Verifies that the property table IDs are correct. Should only be done once. */
extern void check_prop_table();

/* Gets the flag attribute for the given property */
extern int prop_get_flags(const autogen_obj *obj,
                          autogen_property_id id);


#endif /* _AUTOGEN_PROP_H_ */
