/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                pmd_stringpool.h
                ----------------
                SW Include






Project:          autogen

%name:            pmd_stringpool.h %
%version:         co1tss#5 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Jan  4 09:51:39 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen / PMD library

    Contains the prototypes and type definitions for the PMD string pool. 
*/

#ifndef _PMD_STRINGPOOL_H_
#define _PMD_STRINGPOOL_H_

/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "pmd_heap.h"


/*  Use "C" linkage specification when compiling for C++ only  */
#ifdef __cplusplus
extern "C"
{
#endif


/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

typedef struct
{
    char* text;                   /* the string contents */
    unsigned int data;            /* arbitrary data associated with string */
    unsigned int next_hash_entry; /* index of the next element in hash entry list */
} pmd_stringpool_element;

typedef struct
{
    unsigned int pmd_stringpool_size_allocated; /* allocated number of strings in pool */
    unsigned int pmd_stringpool_size_used;      /* number of strings in pool */
    pmd_heap_handle* pmd_stringpool_heap;       /* heap */
    unsigned int* pmd_stringpool_hashtable;     /* hash table for quick string search */
    unsigned int pmd_stringpool_hashtable_size; /* size of the hash table */
	pmd_stringpool_element *pmd_stringpool;     /* string pool */
} pmd_stringpool_struct;


/* ============================================================================================= */
/* Global prototypes */
/* ============================================================================================= */

/*================================================================
    pmd_stringpool_init

    --------
    Inits the string pool. Call this function before doing anything else with the pool.
    Returns 0 if the string pool wasn't initialized.

    --------
    poolsize :  Initial number of strings allocated in the pool. Every time the pool runs out of
                allocated string memory, the number of allocated strings is doubled.

    heap :      Handle to the heap in which the string pool will store its strings. You can use
                a shared heap or a dedicated one.
  
    hashsize :  Size of the search hash table.

--------------------------------*/
int pmd_stringpool_init(const unsigned int poolsize, const pmd_heap_handle* heap, const unsigned int hashsize);

int pmd_stringpool_init_h(const unsigned int size, const pmd_heap_handle* heap, const unsigned int hashsize,
						  pmd_stringpool_struct* pmd_stringpool_data);


/*================================================================
    pmd_stringpool_add

    --------
    Adds string to the string pool, if it doesn't already exits, and returns the index of the
    added string. If the string does exist, the functions just returns the index of the existing
    string. Returns 0 if the string wasn't added.
    
    Always use this function when adding strings!

    --------
    text :      The string to add.

    data :      Data associated with the string. Note that if the string already exists, the data
                will not be added.

    index :     Returns the index of the added string.
  
--------------------------------*/
int pmd_stringpool_add(const char* text, const unsigned int data, unsigned int* index);

int pmd_stringpool_add_h(const char* text, const unsigned int data, unsigned int* index,
					     pmd_stringpool_struct* pmd_stringpool_data);


/*================================================================
    pmd_stringpool_add_simple

    --------
    Adds a string to the end of the string pool. The function does NOT check if the string already
    exists in the pool, and does not insert the string in the hash table. Returns 0 if the string 
    wasn't added.

    DO NOT USE! Internal helper function.

    --------
    text :      The string to add.

    data :      Data associated with the string.

    index :     The index of the added string.

--------------------------------*/
int pmd_stringpool_add_simple(const char* text, const unsigned int data, unsigned int* index);

int pmd_stringpool_add_simple_h(const char* text, const unsigned int data, unsigned int* index,
								pmd_stringpool_struct* pmd_stringpool_data);


/*================================================================
    pmd_stringpool_update_data

    --------
    Updates the data associated with the string on the given index in the string pool. Returns 0,
    if the index is out of bounds.
    
    --------
    index :     The index of the string.

    data :      The new data to be associated with the string.

--------------------------------*/
int pmd_stringpool_update_data(const unsigned int index, const unsigned int data);

int pmd_stringpool_update_data_h(const unsigned int index, const unsigned int data,
                                 pmd_stringpool_struct* pmd_stringpool_data);


/*================================================================
    pmd_stringpool_get

    --------
    Gets the string located on the given index in the string pool. Returns 0, if the index is out
    of bounds.
    
    This function is also implemented as a MACRO. See below.

    --------
    index :     The index of the string to get.

--------------------------------*/
char* pmd_stringpool_get(const unsigned int index);

char* pmd_stringpool_get_h(const unsigned int index, pmd_stringpool_struct* pmd_stringpool_data);

/*--------------------------------
    PMD_STRINGPOOL_GET

    See details in the description of the pmd_stringpool_get function above.

    TODO: Make performance optimization of this
*/
#define PMD_STRINGPOOL_GET(index) pmd_stringpool_get(index)



/*================================================================
    pmd_stringpool_get_data

    --------
    Gets the data associated with the string located on the given index in the string pool. 
    Returns 0, if the index is out of bounds.
    
    --------
    index :     The index of the string to get.

--------------------------------*/
unsigned int pmd_stringpool_get_data(const unsigned int index);

unsigned int pmd_stringpool_get_data_h(const unsigned int index,pmd_stringpool_struct* pmd_stringpool_data);


/*================================================================
    pmd_stringpool_lookup

    --------
    Looks in the string pool for the given string and returns the index. If the string wasn't 
    found, the function returns 0. Note that the empty string is always located at index 0.
    
    --------
    text :      The string to look for.

--------------------------------*/
unsigned int pmd_stringpool_lookup(const char* text);

unsigned int pmd_stringpool_lookup_h(const char* text, pmd_stringpool_struct* pmd_stringpool_data);


/*================================================================
    pmd_stringpool_free

    --------
    Frees the string pool, but not the associated heap! If the string pool was not initialized,
    the function returns 0.

    --------
    index :     The index of the string to get.

--------------------------------*/
int pmd_stringpool_free();

int pmd_stringpool_free_h(pmd_stringpool_struct* pmd_stringpool_data);



/*================================================================
    pmd_stringpool_hash

    --------
    Creates hash index value from string and returns it.

    --------
    text :      The string to get the hash index of.

--------------------------------*/
unsigned int pmd_stringpool_hash(const char* text);

unsigned int pmd_stringpool_hash_h(const char* text, pmd_stringpool_struct* pmd_stringpool_data);


/*================================================================
    pmd_stringpool_monitor_hashtable

    --------
    Dumps statistics on hash table to file. Returns 0 if an error occurred.

    --------
    filename :  Path and name of file. Supports 8.3 format only!!

--------------------------------*/
int pmd_stringpool_monitor_hashtable(const char* filename);

int pmd_stringpool_monitor_hashtable_h(const char* filename, pmd_stringpool_struct* pmd_stringpool_data);

/*  Use "C" linkage specification when compiling for C++ only  */
#ifdef __cplusplus
}
#endif


#endif /*_PMD_STRINGPOOL_H_ */


/* End of file pmd_stringpool.h */
