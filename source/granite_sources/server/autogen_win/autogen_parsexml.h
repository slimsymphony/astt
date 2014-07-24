/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_parsexml.h
                ------------------
                SW Module






Project:          autogen

%name:            autogen_parsexml.h %
%version:         2 %
%instance:        co1tss_1 %
%derived_by:      nosterga %
%date_modified:   Thu Sep 25 13:23:28 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  This file is part of the source code for the autogen tool

    The file contains functions to parse xml
*/

#ifndef PARSE_H
#define PARSE_H

typedef struct xml_attribute_t {
    char                   *name;
    char                   *value;
    
    struct xml_attribute_t *next;
} xml_attribute;

typedef struct xml_element_t {
    char                 *tag;
    xml_attribute        *attributes_head;
    xml_attribute        *attributes_tail;
    struct xml_element_t *children_head;
    struct xml_element_t *children_tail;
    char                 *data;    

    struct xml_element_t *next;
} xml_element;

char        *parsexml_readfile(const char *filename, int *errorcode);
xml_element *parsexml_parse(const char *xmldata, int *errorcode);

void         parsexml_free_element(xml_element *element);

xml_element *parsexml_find_element_tag(xml_element *elem, const char *tag);
const char  *parsexml_find_attribute(xml_attribute *attr, const char *name);
const char  *parsexml_get_error_text(int errorcode);

#endif
