/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                pmd_heap.h
                ----------
                SW Include






Project:          autogen

%name:            pmd_heap.h %
%version:         co1tss#5.1.1 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Jan  4 09:51:57 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen / PMD library

    Contains the prototypes and type definitions for the PMD heap. 

    The PMD heap is used for allocating objects, which can't be removed (freed) until the 
    application is terminated
*/

#ifndef _PMD_HEAP_H_
#define _PMD_HEAP_H_

#ifdef __cplusplus
extern "C" {
#endif


/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

typedef struct
{
    unsigned int block_size; /* the size of the current block in bytes */
    unsigned char* block; /* pointer to the memory block */
    unsigned int block_remaining_size; /* the remain number of bytes in the current block */
    unsigned int block_offset; /* offset to the next free byte in current block */
    unsigned int total_size; /* total number of bytes allocated on the handle */
} pmd_heap_handle;


extern pmd_heap_handle* s_heap_handle;


/* ============================================================================================= */
/* Global prototypes */
/* ============================================================================================= */

/* Functions to be used when global heap handle should be used */

void pmd_heap_init(unsigned int block_size);
void pmd_heap_free();
void* pmd_heap_alloc(unsigned int size);
char* pmd_heap_strdup(const char* text);

/* Functions to be used when local heap handle should be used */

pmd_heap_handle* pmd_heap_init_h(unsigned int block_size);
void pmd_heap_free_h(pmd_heap_handle* handle);
void pmd_heap_clear_h(pmd_heap_handle* handle);
void* pmd_heap_alloc_h(pmd_heap_handle* handle, unsigned int size);
char* pmd_heap_strdup_h(pmd_heap_handle* handle, const char* text);


#ifdef __cplusplus
}
#endif


#endif /* _PMD_HEAP_H_ */

/* end of file pmd_heap.h */
