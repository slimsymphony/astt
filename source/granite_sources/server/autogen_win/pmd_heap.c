/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                pmd_heap.c
                ----------
                SW Module






Project:          autogen

%name:            pmd_heap.c %
%version:         co1tss#10.1 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Jan 11 08:40:26 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen and PMD library

    The file contains the source code for the PMD heap.
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "pmd_heap.h"

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>


/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

pmd_heap_handle* s_heap_handle = NULL;


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* Disable unwanted warning in MSVC 6.0 */
#ifdef _MSC_VER
#pragma warning(disable: 4711)      /* function 'XXX' selected for automatic inline expansion */
#endif /* _MSC_VER */

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_init_h
 
    Purpose: 
        Initializes memory heap
 
    Functional Description:
        Initalizes memory heap and sets block size.
        This function must be called prior to any other pmd_heap_xxx_h function

    Arguments: 
        blocksize - [in] size of each allocated block in bytes

    Returns:
        Handle to the heap
*/
/* --------------------------------------------------------------------------------------------- */
pmd_heap_handle* pmd_heap_init_h(unsigned int block_size)
{
    pmd_heap_handle* handle = calloc(1, sizeof(pmd_heap_handle));

    if (handle)
    {
        handle->block_size  = block_size;
        if ((block_size % 8) != 0)
        {
            handle->block_size += (8 - block_size % 8);
        }
        handle->block = NULL;
        handle->block_remaining_size = 0;
        handle->block_offset = 0;
        handle->total_size = sizeof(pmd_heap_handle);
    }

    return handle;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_alloc_h
 
    Purpose: 
        Allocates a block on the memory heap
 
    Functional Description:
        Allocates a block of 'size' bytes on the heap handled by 'handle'

    Arguments: 
        handle - [in] handle to the memory heap (created with pmd_heap_init_h)
        size   - [in] size of block in bytes

    Returns:
        Pointer to allocated block
*/
/* --------------------------------------------------------------------------------------------- */
void* pmd_heap_alloc_h(pmd_heap_handle* handle, unsigned int size)
{
    unsigned char* p_block = NULL;

    if ((size % 8) == 0 && (handle->block_offset % 8))
    {
        unsigned int diff = 8 - (handle->block_offset % 8);
        assert(handle->block_remaining_size >= diff);
        handle->block_offset         += diff;
        handle->block_remaining_size -= diff;
    }
    else
    if ((size % 4) == 0 && (handle->block_offset % 4))
    {
        unsigned int diff = 4 - (handle->block_offset  % 4);
        assert(handle->block_remaining_size >= diff);
        handle->block_offset         += diff;
        handle->block_remaining_size -= diff;
    }
    else
    if ((size % 2) == 0 && (handle->block_offset & 1))
    {
        assert(handle->block_remaining_size >= 1);
        handle->block_offset++;
        handle->block_remaining_size--;
    }

    /* no room for allocation in block */
    if (handle->block_remaining_size < size)
    {
        unsigned char* new_block = NULL;
        unsigned int new_block_size = handle->block_size;

        assert(!((size > (new_block_size - 8)) && (size <= (new_block_size + 8))));
        if (size > new_block_size - 8)
        {
            new_block_size += size;
            new_block_size += 8 - (new_block_size % 8);
        }

        new_block = (unsigned char*)calloc(1, new_block_size);
        if (new_block)
        {
            handle->block_remaining_size = new_block_size;

            *((unsigned char**)new_block) = handle->block;

            handle->block = new_block;
            handle->block_offset = 8; /* preserve room for pointer to previous block */

            p_block = handle->block + handle->block_offset;
            handle->block_remaining_size -= handle->block_offset;
            handle->total_size += new_block_size;
        }
    }
    else
    {
        p_block = handle->block + handle->block_offset;
    }

    if (p_block)
    {
        handle->block_remaining_size -= size;
        handle->block_offset         += size;
    }

    return p_block;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_strdup_h
 
    Purpose: 
        Allocates a string on the memory heap (as strdup)
 
    Functional Description:
        Allocates a string on the heap handled by 'handle'

    Arguments: 
        handle - [in] handle to the memory heap (created with pmd_heap_init_h)
        text   - [in] pointer to text to duplicate

    Returns:
        Pointer to allocated string
*/
/* --------------------------------------------------------------------------------------------- */
char* pmd_heap_strdup_h(pmd_heap_handle* handle, const char* text)
{
    char* new_text = NULL;

    if (text)
    {
        new_text = (char*)pmd_heap_alloc_h(handle, strlen(text) + 1);
        strcpy(new_text, text);
    }

    return new_text;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_free_h
 
    Purpose: 
        Releases the memory heap
 
    Functional Description:
        Releases the memory heap again and releases all related memory allocation
        The handle is also released itself, and must be considered invalid afterwards

    Arguments: 
        handle - [in] handle to the memory heap (created with pmd_heap_init_h)

    Returns:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void pmd_heap_free_h(pmd_heap_handle* handle)
{
    pmd_heap_clear_h(handle); /* free all blocks except current */

    free(handle->block); /* free current block */
    free(handle);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_clear_h
 
    Purpose: 
        Releases the memory heap except the last one, which is preserved
        for reuse.
 
    Functional Description:
        Releases the memory heap again and releases all related memory allocation
        except the last allocated block, which is preserved for reuse.
        The handle is still valid.

    Arguments: 
        handle - [in] handle to the memory heap (created with pmd_heap_init_h)

    Returns:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void pmd_heap_clear_h(pmd_heap_handle* handle)
{
    if (handle->block)
    {
        unsigned char* p_block = *((unsigned char**)handle->block);
        while (p_block)
        {
            unsigned char* p_next_block = *((unsigned char**)p_block);
            free(p_block);
            p_block = p_next_block;
        }

        *((unsigned char**)handle->block) = NULL;
        handle->block_offset = 8;
        handle->block_remaining_size = handle->block_size - handle->block_offset;
        memset(handle->block, 0, handle->block_offset);
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_init
 
    Purpose: 
        Initializes memory heap (using global handle)
 
    Functional Description:
        Initalizes memory heap and sets block size.
        The global memory heap handle is associated with the heap
        This function must be called prior to any other pmd_heap_xxx function

    Arguments: 
        blocksize - [in] size of each allocated block in bytes

    Returns:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void pmd_heap_init(unsigned int size)
{
    s_heap_handle = pmd_heap_init_h(size);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_alloc
 
    Purpose: 
        Allocates a block on the global memory heap
 
    Functional Description:
        Allocates a block of 'size' bytes on the global memory heap

    Arguments: 
        size - [in] size of block in bytes

    Returns:
        Pointer to allocated block
*/
/* --------------------------------------------------------------------------------------------- */
void* pmd_heap_alloc(unsigned int size)
{
    return pmd_heap_alloc_h(s_heap_handle, size);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_strdup
 
    Purpose: 
        Allocates a string on the global memory heap (as strdup)
 
    Functional Description:
        Allocates a string on the global memory heap

    Arguments: 
        text - [in] pointer to text to duplicate

    Returns:
        Pointer to allocated string
*/
/* --------------------------------------------------------------------------------------------- */
char* pmd_heap_strdup(const char* text)
{
    return pmd_heap_strdup_h(s_heap_handle, text);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_heap_free
 
    Purpose: 
        Releases the global memory heap
 
    Functional Description:
        Releases the global memory heap again and releases all related memory allocation
        The global handle is also released itself, and must be considered invalid afterwards

    Arguments: 
        -

    Returns:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void pmd_heap_free()
{
    pmd_heap_free_h(s_heap_handle);

    s_heap_handle = NULL;
}


/* End of file heap.c */
