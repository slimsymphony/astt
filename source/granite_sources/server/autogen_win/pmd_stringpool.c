/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                pmd_stringpool.c
                ----------------
                SW Module






Project:          autogen

%name:            pmd_stringpool.c %
%version:         co1tss#8 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Jan  4 09:51:50 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  This file is part of the source code for autogen

    The file contains the source code for the PMD string pool.
*/

#ifdef _MSC_VER
#pragma warning(disable: 4711)
#endif /* _MSC_VER */

/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "pmd_stringpool.h"

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
#define LOCAL static
#endif /* LOCAL */

LOCAL pmd_stringpool_struct s_pmd_stringpool_data = { 0 }; /* string pool data */


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */
/*================================================================
    pmd_stringpool_init
--------------------------------*/
int pmd_stringpool_init_h(const unsigned int size,
                          const pmd_heap_handle* heap,
                          const unsigned int hashsize,
                          pmd_stringpool_struct* pmd_stringpool_data)
{
    int error = 0;
    unsigned int index = 0;

    /* verify preconditions */
    assert(size > 0);
    assert(heap);
    assert(hashsize > 0);

    /* init pool itself */
    pmd_stringpool_data->pmd_stringpool = (pmd_stringpool_element*)calloc(size, sizeof(pmd_stringpool_element));
    if (!pmd_stringpool_data->pmd_stringpool)
    {
        error = 1; /* error! */
    }

    pmd_stringpool_data->pmd_stringpool_size_used = 0;
    pmd_stringpool_data->pmd_stringpool_size_allocated = size;

    /* init heap */
    pmd_stringpool_data->pmd_stringpool_heap = (pmd_heap_handle*)heap;

    /* init hash table */
    pmd_stringpool_data->pmd_stringpool_hashtable = (unsigned int*)calloc(hashsize, sizeof(int));
    if (!pmd_stringpool_data->pmd_stringpool_hashtable)
    {
        error = 1; /* error! */
    }

    pmd_stringpool_data->pmd_stringpool_hashtable_size = hashsize;

    /* insert empty string in index 0 */
    if (!pmd_stringpool_add_simple_h("", 0, &index, pmd_stringpool_data))
    {
        error = 1; /* error! */
    }
    if (index != 0)
    {
        error = 1; /* error! */
    }

    /* cleanup if error */
    if (error)
    {
        pmd_stringpool_free_h(pmd_stringpool_data);
        return 0;
    }

    return 1;
}


int pmd_stringpool_init(const unsigned int size, const pmd_heap_handle* heap, const unsigned int hashsize)
{
	return pmd_stringpool_init_h(size,heap,hashsize,&s_pmd_stringpool_data);
}

/*================================================================
    pmd_stringpool_add
--------------------------------*/
int pmd_stringpool_add_h(const char* text,
					     const unsigned int data,
					     unsigned int* index,
					     pmd_stringpool_struct* pmd_stringpool_data)
{

    unsigned int hash = 0;
    unsigned int current_index = 0;
    unsigned int prev_index = 0;


    /* verify preconditions */
    assert(text);
    assert(index);
	assert(pmd_stringpool_data);
	assert(pmd_stringpool_data->pmd_stringpool);
    assert(pmd_stringpool_data->pmd_stringpool_hashtable);


    /* empty string is always at index 0 */
    if (text[0] == 0)
    {
        *index = 0;
        return 1;
    }


    /* get hash index */
    hash = pmd_stringpool_hash_h(text,pmd_stringpool_data);

    
    /* find string */
    current_index = pmd_stringpool_data->pmd_stringpool_hashtable[hash];
    while (current_index) 
    {
        if (strcmp(text, pmd_stringpool_data->pmd_stringpool[current_index].text) == 0)
        {
            /* found */
            *index = current_index;
            return 1;
        }
        else
        {
            /* continue search */
            prev_index = current_index;
            current_index = pmd_stringpool_data->pmd_stringpool[current_index].next_hash_entry;
        }
    }


    /* insert in pool and hash table */
    if (pmd_stringpool_add_simple_h(text, data, index,pmd_stringpool_data))
    {
        /* insert as first element in hash index */
        if (!prev_index)
        {
            pmd_stringpool_data->pmd_stringpool_hashtable[hash] = *index;
        }
        /* insert in nested list in hash inddex */
        else
        {
            pmd_stringpool_data->pmd_stringpool[prev_index].next_hash_entry = *index;
        }
    }
    else
    {
        return 0; /* error */
    }

            
    return 1;
}

int pmd_stringpool_add(const char* text,
					   const unsigned int data,
					   unsigned int* index)
{
    return pmd_stringpool_add_h(text,data,index,&s_pmd_stringpool_data);
}

/*================================================================
    pmd_stringpool_add_simple
--------------------------------*/
int pmd_stringpool_add_simple_h(const char* text,
								const unsigned int data,
								unsigned int* index,
					            pmd_stringpool_struct* pmd_stringpool_data)
{

    char* heap_text = 0;


    /* verify preconditions */
	assert(pmd_stringpool_data);
    assert(text);
    assert(index);


    /* resize pool, if necessary */
    if (pmd_stringpool_data->pmd_stringpool_size_used == pmd_stringpool_data->pmd_stringpool_size_allocated)
    {
        pmd_stringpool_data->pmd_stringpool = (pmd_stringpool_element*) realloc(pmd_stringpool_data->pmd_stringpool,
			pmd_stringpool_data->pmd_stringpool_size_allocated * 2 * sizeof(pmd_stringpool_element));
        if (!pmd_stringpool_data->pmd_stringpool) 
        {
            return 0; /* error! */
        }
        pmd_stringpool_data->pmd_stringpool_size_allocated *= 2;
    }


    /* add string to pool */
    heap_text = pmd_heap_strdup_h(pmd_stringpool_data->pmd_stringpool_heap, text);
    if (!heap_text)
    {
        return 0; /* error! */
    }

    pmd_stringpool_data->pmd_stringpool[pmd_stringpool_data->pmd_stringpool_size_used].text = heap_text;
    pmd_stringpool_data->pmd_stringpool[pmd_stringpool_data->pmd_stringpool_size_used].data = data;
    pmd_stringpool_data->pmd_stringpool[pmd_stringpool_data->pmd_stringpool_size_used].next_hash_entry = 0;
    *index = (pmd_stringpool_data->pmd_stringpool_size_used)++;

    return 1;
}

int pmd_stringpool_add_simple(const char* text,
                              const unsigned int data,
                              unsigned int* index)
{
    return pmd_stringpool_add_simple_h(text,data,index,&s_pmd_stringpool_data);
}

/*================================================================
    pmd_stringpool_update_data
--------------------------------*/
int pmd_stringpool_update_data_h(const unsigned int index,
                                 const unsigned int data,
                                 pmd_stringpool_struct* pmd_stringpool_data)
{

    /* verify preconditions */
    if (index >= pmd_stringpool_data->pmd_stringpool_size_used)
    {
        return 0;
    }


    /* update data */
    pmd_stringpool_data->pmd_stringpool[index].data = data;


    return 1;
}

int pmd_stringpool_update_data(const unsigned int index, const unsigned int data)
{
	return pmd_stringpool_update_data_h(index, data, &s_pmd_stringpool_data);
}

/*================================================================
    pmd_stringpool_get
--------------------------------*/
char* pmd_stringpool_get_h(const unsigned int index,
                           pmd_stringpool_struct* pmd_stringpool_data)
{

    /* verify preconditions */
    if (index >= pmd_stringpool_data->pmd_stringpool_size_used)
    {
        return 0;
    }


    /* return string */
    return pmd_stringpool_data->pmd_stringpool[index].text;

}

char* pmd_stringpool_get(const unsigned int index)
{
    return pmd_stringpool_get_h(index, &s_pmd_stringpool_data);
}

/*================================================================
    pmd_stringpool_get_data
--------------------------------*/
unsigned int pmd_stringpool_get_data_h(const unsigned int index,
                                     pmd_stringpool_struct* pmd_stringpool_data)
{

    /* verify preconditions */
    if (index >= pmd_stringpool_data->pmd_stringpool_size_used)
    {
        return 0;
    }


    /* return string */
    return pmd_stringpool_data->pmd_stringpool[index].data;

}

unsigned int pmd_stringpool_get_data(const unsigned int index)
{
    return pmd_stringpool_get_data_h(index,&s_pmd_stringpool_data); 
}

/*================================================================
    pmd_stringpool_lookup
--------------------------------*/
unsigned int pmd_stringpool_lookup_h(const char* text,
                                     pmd_stringpool_struct* pmd_stringpool_data)
{

    unsigned int hash = 0;
    unsigned int current_index = 0;


    /* verify preconditions */
    assert(text);
    assert(pmd_stringpool_data);
    assert(pmd_stringpool_data->pmd_stringpool_hashtable);
    assert(pmd_stringpool_data->pmd_stringpool_hashtable_size > 0);


    /* get hash index */
    hash = pmd_stringpool_hash_h(text,pmd_stringpool_data);


    /* find string */
    current_index = pmd_stringpool_data->pmd_stringpool_hashtable[hash];
    while (current_index)
    {
        if (strcmp(text, pmd_stringpool_data->pmd_stringpool[current_index].text) == 0)
        {
            /* found */
            return current_index;
        }
        else
        {
            /* continue search */
            current_index = pmd_stringpool_data->pmd_stringpool[current_index].next_hash_entry;
        }
    }


    /* return not found */
    return 0;

}

unsigned int pmd_stringpool_lookup(const char* text)
{
    return pmd_stringpool_lookup_h(text,&s_pmd_stringpool_data);
}

/*================================================================
    pmd_stringpool_free
--------------------------------*/
int pmd_stringpool_free_h(pmd_stringpool_struct* pmd_stringpool_data)
{

    /* verify preconditions */
    assert(pmd_stringpool_data->pmd_stringpool);

    /* free pool itself */
    if (pmd_stringpool_data->pmd_stringpool)
    {
        free(pmd_stringpool_data->pmd_stringpool);
    }

    pmd_stringpool_data->pmd_stringpool = NULL;

    pmd_stringpool_data->pmd_stringpool_size_allocated = 0;
    pmd_stringpool_data->pmd_stringpool_size_used = 0;


    /* release heap */
    pmd_stringpool_data->pmd_stringpool_heap = 0;


    /* free hash table */
    if (pmd_stringpool_data->pmd_stringpool_hashtable)
    {
        free(pmd_stringpool_data->pmd_stringpool_hashtable);
    }

    pmd_stringpool_data->pmd_stringpool_hashtable = 0;
    pmd_stringpool_data->pmd_stringpool_hashtable_size = 0;


    return 1;
}

int pmd_stringpool_free()
{
    return pmd_stringpool_free_h(&s_pmd_stringpool_data);
}

/*================================================================
    pmd_stringpool_hash
--------------------------------*/
unsigned int pmd_stringpool_hash_h(const char* text, pmd_stringpool_struct* pmd_stringpool_data)
{

    unsigned int i = 0;
    unsigned int length = strlen(text);
    unsigned int hash = 0;
    
    
    /* verify preconditions */
    assert(text);
    assert(pmd_stringpool_data->pmd_stringpool_hashtable_size > 0);


    /* make hash from string */
    for (i = 0; i < length; i++)
    {
        hash = ((hash * 23) ^ text[i]) % (pmd_stringpool_data->pmd_stringpool_hashtable_size);
    }

    
    return hash;
}

unsigned int pmd_stringpool_hash(const char* text)
{
    return pmd_stringpool_hash_h(text, &s_pmd_stringpool_data);
}

/*================================================================
    pmd_stringpool_monitor_hashtable
--------------------------------*/
int pmd_stringpool_monitor_hashtable_h(const char* filename,
                                     pmd_stringpool_struct* pmd_stringpool_data)
{

    FILE* stream;
    unsigned int hash_index = 0;
    unsigned int index = 0;
    unsigned int stats[100] = {0}; /* holds hash table statistics */
    unsigned int count = 0;


    /* verify preconditions */
    assert(filename);
    assert(pmd_stringpool_data->pmd_stringpool_hashtable);


    /* traverse hash table */
    for (hash_index = 0; hash_index < pmd_stringpool_data->pmd_stringpool_hashtable_size; hash_index++)
    {

        /* count elements in hash index */
        count = 0;
        index = pmd_stringpool_data->pmd_stringpool_hashtable[hash_index];
        while (index)
        {
            count++;
            index = pmd_stringpool_data->pmd_stringpool[index].next_hash_entry;
        }

        /* count of more than 99 is just too much anyway */
        if (count > 99)
        {
            count = 99;
        }

        /* update stats */
        stats[count]++;

    }


    /* open file */
    stream = fopen(filename, "w");
    if (stream == NULL)
    {
        return 0; /* error */
    }


    /* write stats to file */
    count = 0;
    for (index = 0; index < 100; index++)
    {
        count += index * stats[index];
        fprintf(stream, "hash indices with %u elements: %d\n", index, stats[index]);
    }
    fprintf(stream, "total number of elements, excluding empty string (unreliable if any index with more than 99 elements): %d\n", count);


    /* close file */
    fclose(stream);


    return 1;
}

int pmd_stringpool_monitor_hashtable(const char* filename)
{
	return pmd_stringpool_monitor_hashtable_h(filename, &s_pmd_stringpool_data);
}

/* End of file pmd_stringpool.c */
