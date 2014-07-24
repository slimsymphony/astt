/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                list.c
                --------------
                SW Module






Project:          autogen

%name:             list.c %
%version:          1 %
%instance:         co1tss_1 %
%derived_by:       nosterga %
%date_modified:    Tue Feb 15 18:08:12 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  File part of the source code for the autogen tool

    Contains the implementation of the list handling functions
*/

#include <stdlib.h>
#include <string.h>

#include "list.h"

/* --------------------------------------------------------------------------------------------- */
/*  Name: list_new
 
    Purpose: 
        Creates and initialises a new and empty list
 
    Functional Description:
        -
    Arguments: 
        -

    Return Values:
        A pointer to an initialised list header
*/
/* --------------------------------------------------------------------------------------------- */
list_header *list_new()
{
    /* Allocate and zero init the header */
    list_header *buffer = (list_header *)malloc(sizeof(list_header));
    if (buffer)
    {
        memset(buffer, 0, sizeof(list_header));
    }

    return buffer;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: list_delete
 
    Purpose: 
        Deletes a complete list
 
    Functional Description:
        Loops through all elements in the list and each element is given as argument to
        the supplied user function 'free_element'. The purpose of this function is to release
        all memory associated with the data stored in the given list element.
        Finally it deletes the list header it self.

    Arguments: 
        hdr          :  List header
        free_element : Function to delete the memory associated with the data part of a list element
                       Example on user supplied function where data ~ struct my_struct:

                       struct {
                         int type;
                         char *text;
                       } my_struct;

                       void my_free_data(void *data)
                       {
                          struct my_struct *my_data = (struct my_struct *)data;

                          free(my_data->text);
                          free(my_data);
                       }


    Return Values:
        - 
*/
/* --------------------------------------------------------------------------------------------- */
void list_delete(list_header *hdr, void (*free_element)(void *))
{
    if (hdr)
    {
        /* Remove all elements in list */
        list_element *ptr = hdr->head;
        while(ptr)
        {
            /* Free data */
            free_element(ptr->data);
            ptr->data = NULL;

            /* Free list element */
            list_remove(hdr, ptr);
            ptr = hdr->head;
        }
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: list_add
 
    Purpose: 
        Adds a new element to a list
 
    Functional Description:
        The data is stored in a list element which is appended to the end of the list

    Arguments: 
        hdr  : List header
        data : Data to be added as an element to the end of the list

    Return Values:
        The newly added list element containing the data.
*/
/* --------------------------------------------------------------------------------------------- */
list_element *list_add(list_header *hdr, void *data)
{
    list_element *elem = NULL;

    if (hdr != NULL && data != NULL)
    {
        /* Allocate a new list element and initialise it */
        elem = (list_element *)malloc(sizeof(list_element));
        if (elem)
        {
            /* Init element */
            elem->data = data;
            elem->next = NULL;

            /* Add element to header */
            if (hdr->tail)
            {
                /* Add element to tail. List already contains at least one element */
                hdr->tail->next = elem;
                hdr->tail = elem;
            }
            else
            {
                /* List is empty and head/tail is undefined */
                hdr->head = elem;
                hdr->tail = elem;
            }

            /* Update count of elements */
            hdr->count++;
        }
    }

    return elem;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: list_remove
 
    Purpose: 
        Remove a list element from the list
 
    Functional Description:
        Search for the given list element in the list and remove it.
        The caller is responsible for first freeing the memory stored in 'data'
        The function will free the memory associated with the list element itself.
        Therefor the list element 'elem' is invalid after call.

    Arguments: 
        hdr  : List header
        elem : List element to be deleted from list

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void list_remove(list_header *hdr, list_element *elem)
{
    if (hdr != NULL && elem != NULL)
    {
        list_element *ptr  = hdr->head;
        list_element *prev = NULL;

        /* Search for list element with the same address as elem */
        while(ptr)
        {
            if (ptr == elem)
            {
                /* Found - remove the element from the list */
                if (prev == NULL)
                {
                    /* First element in list */
                    hdr->head = ptr->next;
                } 
                else
                {
                    /* Not first element in list */
                    prev->next = ptr->next;
                }

                /* Free memory */
                free(ptr);

                /* Update count of elements */
                hdr->count--;

                return;
            }

            /* Next element in list */
            prev = ptr;
            ptr = ptr->next;
        }
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: list_iterator_reset
 
    Purpose: 
        Reset iterator to beginning of list and return the first element
 
    Arguments: 
        hdr  : List header

    Return Values:
        First list element in the list. NULL if list is empty.

    Example:

        list_element *ptr = list_iterator_reset(list_hdr);
        while(ptr)
        {
            struct my_struct *my_data = (struct my_struct *)ptr->data;
              ...
            ptr = list_iterator_next(list_hdr);
        }
*/
/* --------------------------------------------------------------------------------------------- */
list_element *list_iterator_reset(list_header *hdr)
{
    list_element *first = NULL;

    if (hdr)
    {
        /* Get first element */
        first = hdr->head;

        if (first)
        {
            /* Iterator points to next element */
            hdr->iterator = first->next;
        }
        else
        {
            /* No elements in list */
            hdr->iterator = NULL;
        }
    }

    return first;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: list_iterator_next
 
    Purpose: 
        Return the next element in the list
 
    Arguments: 
        hdr  : List header

    Return Values:
        Next list element in the list. NULL if no more elements left.

    Example:

        list_element *ptr = list_iterator_reset(list_hdr);
        while(ptr)
        {
            struct my_struct *my_data = (struct my_struct *)ptr->data;
              ...
            ptr = list_iterator_next(list_hdr);
        }
*/
/* --------------------------------------------------------------------------------------------- */
list_element *list_iterator_next(list_header *hdr)
{
    list_element *elem = NULL;

    if (hdr)
    {
        /* Check if iterator is reset */
        if (hdr->iterator)
        {
            /* Get element */
            elem = hdr->iterator; 

            /* Advance iterator */
            hdr->iterator = hdr->iterator->next;
        }
    }

    return elem;
}

