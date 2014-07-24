/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                list.h
                --------------
                SW Include






Project:          autogen

%name:             list.h %
%version:          1 %
%instance:         co1tss_1 %
%derived_by:       nosterga %
%date_modified:    Tue Feb 15 18:08:20 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains the declarations for list handling
*/

#ifndef LIST_H
#define LIST_H

/* List element - Stores a single data element in the list */
typedef struct t_list_element {
    /* Store data */
    void *data;

    /* Points to previous list element */
    struct t_list_element *next;
} list_element;

/* List header - Stores a sequence of list elements and a count of elements */
typedef struct t_list_header {
    /* Points to first and last list element in list */
    struct t_list_element *head;
    struct t_list_element *tail;

    /* Contains the actual number of elements in the list */
    unsigned int count;

    /* Keeps track of the iterator used to travers the list */
    struct t_list_element *iterator;
} list_header;

/* Functions */
list_header  *list_new();
void          list_delete(list_header *hdr, void (*free_element)(void *));
list_element *list_add(list_header *hdr, void *data);
void          list_remove(list_header *hdr, list_element *elem);
list_element *list_iterator_next(list_header *hdr);
list_element *list_iterator_reset(list_header *hdr);

#endif /* LIST_H */

