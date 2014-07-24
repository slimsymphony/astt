/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                autogen_parsexml.c
                ------------------
                SW Module






Project:          autogen

%name:            autogen_parsexml.c %
%version:         5 %
%instance:        co1tss_1 %
%derived_by:      nosterga %
%date_modified:   Thu Mar 24 17:58:06 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  This file is part of the source code for the autogen tool

    The file contains functions to parse xml
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "autogen_def.h"
#include "autogen_util.h" 
#include "autogen_parsexml.h"

#ifndef LOCAL
#define LOCAL static
#endif /* LOCAL */

LOCAL void         parsexml_strip_comments(char *xmldata);
LOCAL void         parsexml_strip_directives(char *xmldata);
LOCAL void         parsexml_strip_section(char *xmldata, const char *startmarker, const char *endmarker);
LOCAL const char  *parsexml_read_token(const char *xmldata, char **token);
LOCAL const char  *parsexml_read_string(const char *xmldata, char startmarker, char endmarker, char **string, int *errorcode);
LOCAL const char  *parsexml_skip_whitespace(const char *xmldata);
LOCAL const char  *parsexml_read_attr(const char *xmldata, xml_attribute **attribute, int *errorcode);
LOCAL const char  *parsexml_read_starttag(const char *xmldata, xml_element *element, int *element_finished, int *errorcode);
LOCAL const char  *parsexml_read_endtag(const char *xmldata, char **tag, int *errorcode);
LOCAL int          parsexml_next_is_starttag(const char *xmldata, const char **nexttag);
LOCAL const char  *parsexml_element(const char *xmldata, xml_element **element, int *errorcode);
LOCAL void         parsexml_free_attributes(xml_attribute *attribute);

#define MAX_ERRORCODE 16
const char *parsexml_errorcodes[MAX_ERRORCODE] = {
    /*  0 */ "No error",
    /*  1 */ "Error reading size of xml file.",
    /*  2 */ "Error reading xml file.",
    /*  3 */ "Can not open xml file.",
    /*  4 */ "Error reading start of string.",
    /*  5 */ "Error reading end of string.",
    /*  6 */ "Error no start tag name present",
    /*  7 */ "Start tag is missing.",
    /*  8 */ "Error no end tag name present",
    /*  9 */ "Missing > of end tag.",
    /* 10 */ "End tag expected.",
    /* 11 */ "Error reading attribute name.",
    /* 12 */ "Missing = when reading attribute",
    /* 13 */ "End tag was expected.",
    /* 14 */ "End tag does not match start tag",
    /* 15 */ "Error parsing xml file."
};

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_readfile
 
    Purpose: 
        Reads a text file. 
 
    Functional Description:
        Reads a text file and returns the data as a text string.

    Arguments: 
        filename  - [in]  filename of file to load
        errorcode - [out] contains error code in case of errors. 0 otherwise.

    Return values:
        String containing the contents of the file read (NULL in case of errors)
        Caller responsible for deallocating string
*/
/* --------------------------------------------------------------------------------------------- */
char *parsexml_readfile(const char *filename, int *errorcode)
{
    /* Store the read xml data */
    char *xmldata = NULL;   

    FILE *xmlfile = fopen(filename, "r");
    if (xmlfile)
    {
        long int size = 0L;
        long int actualsize = 0L;

        /* Get size of file */
        if (fseek(xmlfile, 0L, SEEK_END))
        {
            /* Error */
            fclose(xmlfile);

            *errorcode = 1;
            return NULL;
        }
        size = ftell(xmlfile);

        /* Reset pointer to start of file */
        if (fseek(xmlfile, 0L, SEEK_SET))
        {
            /* Error */
            fclose(xmlfile);

            *errorcode = 2;
            return NULL;
        }

        /* Allocate memory for reading the file into */
        xmldata = (char *)malloc(size+1);

        /* Read whole file into memory */
        actualsize = fread(xmldata, sizeof(char), size, xmlfile);
        xmldata[actualsize] = 0;

        fclose(xmlfile);
        *errorcode = 0;
    } 
    else
    {
        /* Error */
        *errorcode = 3;
    }
    return xmldata;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_strip_comments
 
    Purpose: 
        Strip out all xml comments. Text sections between <!-- and -->
 
    Functional Description:
        Strip out all xml comments by replacing it with spaces.

    Arguments: 
        xmldata  - [in] string containing stripped text.

    Return values:
        None
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void parsexml_strip_comments(char *xmldata)
{
    parsexml_strip_section(xmldata, "<!--", "-->");
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_strip_directives
 
    Purpose: 
        Strip out all xml directives. Text sections between <? and ?>
 
    Functional Description:
        Strip out all xml directives by replacing it with spaces.

    Arguments: 
        xmldata  - [in] string containing stripped text.

    Return values:
        None
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void parsexml_strip_directives(char *xmldata)
{
    parsexml_strip_section(xmldata, "<?", "?>");
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_strip_section
 
    Purpose: 
        Strip out all text between a start string and an end string. 
 
    Functional Description:
        Strip out all text between a start string and an end string replacing the text with spaces.
        Start string and end string will also be replaced with spaces.
        Can be used to e.g. remove xml comments.

    Arguments: 
        xmldata  - [in] string containing stripped text.

    Return values:
        None
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void parsexml_strip_section(char *xmldata, const char *startmarker, const char *endmarker)
{
    char *pointer = xmldata;

    /* Loop while not all data is checked */
    while (pointer != NULL && *pointer != 0)
    {
        char *section_start = NULL;
        char *section_end   = NULL;

        /* Find presence of a start marker */
        section_start = strstr(pointer, startmarker);
        if (section_start != NULL)
        {
            /* Start of marker found. Check an end marker can be found */
            section_end = strstr(section_start, endmarker);
            if (section_end == NULL)
            {
                /* Special case: No end marker. Terminate xml data at start marker */
                *section_start = 0;
                return;
            }
            else
            {
                /* Overwrite section with space */
                memset(section_start, ' ', section_end-section_start+strlen(endmarker));

                /* Continue from end of section */
                pointer = section_end+strlen(endmarker);
            }
        }
        else
        {
            /* No more sections to wipe out. */
            return;
        }
    }
    return;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_skip_whitespace
 
    Purpose: 
        Skip whitespace.
 
    Functional Description:
        Skip whitespace so cursor is placed at the next text element

    Arguments: 
        xmldata  - [in] string containing the xml data being parsed

    Return values:
        Pointer to where to continue to parse xml data
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL const char *parsexml_skip_whitespace(const char *xmldata)
{
    const char *pointer = xmldata;

    /* Find end of whitespace by skipping characters until non-whitespace */
    while(isspace(*pointer))
    {
        pointer++;
    };
    return pointer;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_read_string
 
    Purpose: 
        Read a string enclosed between two markers. E.g. like ".
 
    Functional Description:
        Check that the start marker is present. Read and store the string (exclusive the markers).
        Check that the end marker is present.
        Note: It is possible to say that no start marker is present.

    Arguments: 
        xmldata     - [in]  string containing the xml data being parsed
        startmarker - [in]  the character used as start marker. 0 = no start marker present.
        endmarker   - [in]  the character used as end marker.
        string      - [out] pointer to string extracted from xmldata. Caller must free() memory. 
                            An empty string will just contain the terminating 0.
        errorcode   - [out] contains error code in case of errors. 0 otherwise.

    Return values:
        Pointer to where to continue to parse xml data. NULL in case of errors.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL const char *parsexml_read_string(const char *xmldata, char startmarker, char endmarker, char **string, int *errorcode)
{
    const char *pointer = xmldata;
    const char *endmarkerptr = NULL;

    /* Check start marker if necessary */
    if (startmarker != 0 && *pointer++ != startmarker)
    {
        /* Error - Start marker required but not present */
        *errorcode = 4;
        return NULL;
    }

    /* Find the end marker */
    endmarkerptr = strchr(pointer, endmarker);
    if (endmarkerptr == NULL)
    {
        /* End marker not found */
        *errorcode = 5;
        return NULL;
    }

    /* Save the string */
    *string = (char *)malloc(endmarkerptr-pointer+1);
    strncpy(*string, pointer, endmarkerptr-pointer);
    (*string)[endmarkerptr-pointer] = 0;

    *errorcode = 0;
    return endmarkerptr+1;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_read_token
 
    Purpose: 
        Read an alpha-numeric string token. 
 
    Functional Description:
        Read alpha-numeric string token until meating character that is not alpha-numeric.

    Arguments: 
        xmldata  - [in]  string containing the xml data being parsed
        token    - [out] pointer to string token extracted from xmldata. Caller must free() memory. 
                         Can be NULL in case no token is present.

    Return values:
        Pointer to where to continue to parse xml data
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL const char *parsexml_read_token(const char *xmldata, char **token)
{
    const char *pointer = xmldata;

    /* Find end of token by skipping characters until non-alphanumeric (or : _ - .) */
    while(isalnum(*pointer) || *pointer == ':' || *pointer == '_' || *pointer == '-' || *pointer == '.')
    {
        pointer++;
    };

    /* Store the token */
    if (pointer-xmldata > 0)
    {
        /* String data present */
        *token = (char *)malloc(pointer-xmldata+1);
        strncpy(*token, xmldata, pointer-xmldata);
        (*token)[pointer-xmldata] = 0;
    } 
    else
    {
        /* No token */
        *token = NULL;
    }

    return pointer;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_read_starttag
 
    Purpose: 
        Read a start tag.
 
    Functional Description:
        Read a start tag and all associated attributes. This is stored in an xml_element.

    Arguments: 
        xmldata           - [in]  string containing the xml data being parsed
        xml_element       - [in]  Function updates members tag and attributes.   
        element_finished  - [out] True (1) = start tag terminated with '/>'
                                  False(0) = start tag terminate with '>'
        errorcode         - [out] contains error code in case of errors. 0 otherwise.

    Return values:
        Pointer to where to continue to parse xml data. In case of error then NULL is returned and
        caller must deallocate all memory associated with the xml_element.
        
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL const char *parsexml_read_starttag(const char *xmldata, xml_element *element, int *element_finished, int *errorcode)
{
    const char *pointer = xmldata;
    const char *endpointer = NULL;

    /* Verify start of tag */
    if (*pointer++ == '<')
    {
        int cont = 0;

        /* Skip whitespace */
        pointer = parsexml_skip_whitespace(pointer);

        /* Read tag name */
        pointer = parsexml_read_token(pointer, &element->tag);
        if (element->tag == NULL)
        {
            /* Error. No tag */
            *errorcode = 6;
            return NULL;
        }

        /* Read attributes if any present */
        cont = 1;
        while (cont)
        {
            xml_attribute *attribute = NULL;

            /* Skip whitespace */
            pointer = parsexml_skip_whitespace(pointer);

            /* Check of end of starttag */
            if (*pointer == '>')
            {
                /* End of starttag. No attributes */
                endpointer = pointer+1;
                *element_finished = 0;
                cont = 0;
            }
            else if (strncmp(pointer, "/>", 2) == 0)
            {
                /* End of starttag. No attributes */
                endpointer = pointer+2;
                *element_finished = 1;
                cont = 0;
            }
            else
            {
                /* Get attribute */
                pointer = parsexml_read_attr(pointer, &attribute, errorcode);
                if (pointer == NULL)
                {
                    /* Error reading attribute */
                    /* Free allocated storage */
                    free(element->tag);
                    element->tag = NULL;

                    parsexml_free_attributes(element->attributes_head);
                    element->attributes_head = NULL;
                    element->attributes_tail = NULL;

                    return NULL;
                }

                /* Store attribute */
                if (element->attributes_head == NULL)
                {
                    /* No attributes already inserted */
                    element->attributes_head = attribute;
                    element->attributes_tail = attribute;
                }
                else
                {
                    /* attributes already present */
                    element->attributes_tail->next = attribute;
                    element->attributes_tail = attribute;
                }

                cont = 1;
            }
        }
    }
    else
    {
        /* Error */
        *errorcode = 7;
        return NULL;
    }

    *errorcode = 0;
    return endpointer;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_read_endtag
 
    Purpose: 
        Read an end tag.
 
    Functional Description:
        Read an end tag.

    Arguments: 
        xmldata   - [in]  string containing the xml data being parsed
        tag       - [out] End tag name. Caller must deallocate memory.
        errorcode - [out] contains error code in case of errors. 0 otherwise.

    Return values:
        Pointer to where to continue to parse xml data. In case of error then NULL is returned.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL const char *parsexml_read_endtag(const char *xmldata, char **tag, int *errorcode)
{
    const char *pointer = xmldata;

    /* Verify start of end tag */
    if (strncmp(pointer, "</", 2) == 0)
    {
        pointer += 2;

        /* Skip whitespace */
        pointer = parsexml_skip_whitespace(pointer);

        /* Read tag name */
        pointer = parsexml_read_token(pointer, tag);
        if (*tag == NULL)
        {
            /* Error. No tag */
            *errorcode = 8;
            return NULL;
        }

        /* Skip whitespace */
        pointer = parsexml_skip_whitespace(pointer);

        /* Check of end of starttag */
        if (*pointer++ != '>')
        {
            /* Error */
            free(*tag);

            *errorcode = 9;
            return NULL;
        }

        *errorcode = 0;
        return pointer;
    }

    /* Error */
    *errorcode = 10;
    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_read_attr
 
    Purpose: 
        Read an attribute/value part of a start tag.
 
    Functional Description:
        Read a single attribute/value pair.

    Arguments: 
        xmldata   - [in]  string containing the xml data being parsed
        attribute - [out] data structure containing the attribute. (Caller must deallocate memory)
        errorcode - [out] contains error code in case of errors. 0 otherwise.

    Return values:
        Pointer to where to continue to parse xml data. NULL in case of errors.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL const char *parsexml_read_attr(const char *xmldata, xml_attribute **attribute, int *errorcode)
{
    const char *pointer = xmldata;
    char *attrname = NULL;
    char *attrvalue = NULL;

    *attribute = NULL;

    /* Read attribute name */
    pointer = parsexml_read_token(pointer, &attrname);
    if (attrname == NULL)
    {
        /* Error */
        *errorcode = 11;
        return NULL;
    }

    /* Skip whitespace */
    pointer = parsexml_skip_whitespace(pointer);

    if (*pointer++ != '=')
    {
        /* Error */
        free(attrname);
        *errorcode = 12;
        return NULL;
    }

    /* Skip whitespace */
    pointer = parsexml_skip_whitespace(pointer);

    /* Read attribute value */
    pointer = parsexml_read_string(pointer, '\"', '\"', &attrvalue, errorcode);
    if (pointer == NULL)
    {
        /* Error */
        free(attrname);
        return NULL;
    }

    /* Store the extracted attribute */
    *attribute = (xml_attribute *)malloc(sizeof(xml_attribute));
    (*attribute)->name  = attrname;
    (*attribute)->value = attrvalue;
    (*attribute)->next  = NULL;

    *errorcode = 0;
    return pointer;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_next_is_starttag
 
    Purpose: 
        Determine if next tag is a start tag or end tag
 
    Functional Description:
        Check the next tag and check if it is a start tag or end tag.

    Arguments: 
        xmldata - [in]  string containing the xml data being parsed
        nexttag - [out] pointer to the start of next tag. NULL if non found.
        
    Return values:
        True:  if next tag is a start tag. 'nexttag' will point to a valid string.
        False: if next tag is an endtag or if none found. 
               'nexttag' will point to a valid string if a tag is found. 
               If no tag is found then 'nexttag' will be NULL.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int parsexml_next_is_starttag(const char *xmldata, const char **nexttag)
{
    /* Find next tag */
    *nexttag = strchr(xmldata, '<');
    if (*nexttag == NULL)
    {   
        /* Not found - return false */
        return 0;
    }
    else
    {
        /* Found - check if it is a start tag or end tag*/
        if (*(*nexttag + 1) == '/')
        {
            /* End tag */
            return 0;
        }
        else
        {
            /* Start tag */
            return 1;
        }
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_element
 
    Purpose: 
        Parse the next xml element.
 
    Functional Description:
        Parse the next xml element. Calls it self recursively to parse any xml elements 
        part of the internal of the given element.

    Arguments: 
        xmldata   - [in]  string containing the xml data being parsed
        element   - [out] Element read. Caller must deallocated memory.
        errorcode - [out] contains error code in case of errors. 0 otherwise.

    Return values:
        Pointer to where to continue to parse xml data. NULL in case of errors.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL const char *parsexml_element(const char *xmldata, xml_element **element, int *errorcode)
{
    const char *pointer = xmldata;
    int element_finished = 0;
    char *endtag = NULL;
    const char *nexttag = NULL;
    const char *after_end_tag = NULL;
    int cont = 0;

    *element = (xml_element *)malloc(sizeof(xml_element));

    /* Initialise xml element */
    (*element)->tag = NULL;
    (*element)->attributes_head = NULL;
    (*element)->attributes_tail = NULL;
    (*element)->children_head = NULL;
    (*element)->children_tail = NULL;
    (*element)->data = NULL;
    (*element)->next = NULL;

    /* Read the start tag */
    pointer = parsexml_read_starttag(pointer, *element, &element_finished, errorcode);
    if (pointer == NULL)
    {
        /* Error */
        parsexml_free_element(*element);
        return NULL;
    }

    /* Tag like this <start ... />. */
    if (element_finished)
    {
        *errorcode = 0;
        return pointer;
    }

    cont = 1;
    while (cont)
    {
        /* Check if any start tags (for child elements) present before the end tag for this element */
        if (parsexml_next_is_starttag(pointer, &nexttag))
        {
            /* Next tag is a start tag ie a child element */
            xml_element *childelement = NULL;

            /* Read child element - skipping any text in front of child element. Mixed text / elements not supported */
            pointer = parsexml_element(nexttag, &childelement, errorcode); 
            if (pointer == NULL)
            {
                /* Error */
                parsexml_free_element(*element);
                return NULL;
            }

            /* Store child element in parent element */
            if ((*element)->children_head == NULL)
            {
                /* No children already inserted */
                (*element)->children_head = childelement;
                (*element)->children_tail = childelement;
            }
            else
            {
                /* Children already present */
                (*element)->children_tail->next = childelement;
                (*element)->children_tail = childelement;
            }

            /* Continue loop */
        }
        else
        {
            /* Next tag is NOT a start tag. Check if any next tag was found at all */ 
            if (nexttag == NULL)
            {
                /* Error - No next tag */
               parsexml_free_element(*element);

               *errorcode = 13;
               return NULL;
            }

            /* Next tag is an end tag ie. end of current element. Jump out of loop to read end tag */
            cont = 0;
        }
    }

    /* Next tag is an end tag. Get it */ 
    after_end_tag = parsexml_read_endtag(nexttag, &endtag, errorcode);
    if (after_end_tag == NULL)
    {
        /* Error */
        parsexml_free_element(*element);
        return NULL;
    }

    /* Check that it is the end tag of current element */
    if (strcmp(endtag, (*element)->tag) != 0)
    {
        /* Error. End tag does not match start tag */
        free(endtag);
        parsexml_free_element(*element);
        *errorcode = 14;
        return NULL;
    }

    /* endtag no longer needed. */
    free(endtag);

    /* Store text data - only if no embedded child xml elements. Mixed text / elements not supported */
    if ((*element)->children_head == NULL) 
    {
        /* No child elements - Store text */
        (*element)->data = (char *)malloc(nexttag - pointer + 1);
        strncpy((*element)->data, pointer, nexttag - pointer);
        (*element)->data[nexttag - pointer] = 0;
    }

    *errorcode = 0;
    return after_end_tag;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_parse
 
    Purpose: 
        Parse an xml document and return it as a data structure
 
    Functional Description:
        Parse an xml document and return it as a data structure

    Arguments: 
        xmldata   - [in]  xml document
        errorcode - [out] contains error code in case of errors. 0 otherwise.

    Return values:
        An xml structure representing the xml document. NULL in case of an error
*/
/* --------------------------------------------------------------------------------------------- */
xml_element *parsexml_parse(const char *xmldata, int *errorcode)
{
    const char *pointer = xmldata;

    /* Initialise an xml root element */
    xml_element *root_elem = (xml_element *)malloc(sizeof(xml_element));
    root_elem->tag = (char *)malloc(strlen("root")+1);
    strcpy(root_elem->tag, "root");
    root_elem->attributes_head = NULL;
    root_elem->attributes_tail = NULL;
    root_elem->children_head = NULL;
    root_elem->children_tail = NULL;
    root_elem->data = NULL;
    root_elem->next = NULL;

    /* Remove all xml comments and directives */
    /* Note: constness is removed because comments/directives are removed by overwritting them with spaces */
    parsexml_strip_comments((char *)pointer);
    parsexml_strip_directives((char *)pointer);

    /* Find all top level elements and attach them as child elements to the root element */
    while (pointer != NULL)
    {
        xml_element *elem = NULL;

        /* Skip any whitespace */
        pointer = parsexml_skip_whitespace(pointer);

        /* Get element */
        pointer = parsexml_element(pointer, &elem, errorcode);
        if (pointer == NULL)
        {
            /* Error */
            parsexml_free_element(root_elem);
            return NULL;
        }

        /* Store the xml element */
        if (root_elem->children_head == NULL)
        {
            /* No children already inserted */
            root_elem->children_head = elem;
            root_elem->children_tail = elem;
        }
        else
        {
            /* Children already present */
            root_elem->children_tail->next = elem;
            root_elem->children_tail = elem;
        }

        /* Skip to next element */
        if (!parsexml_next_is_starttag(pointer, &pointer))
        {
            /* No more start tags - check if we found an erronous end tag */
            if (pointer != NULL)
            {
                /* Error - end tag encountered */
                parsexml_free_element(root_elem);

                *errorcode = 15;
                return NULL;
            }
        }
        /* Pointer points to next start tag or pointer is NULL */
    }
    *errorcode = 0;
    return root_elem;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_free_element
 
    Purpose: 
        Free all data (recursively) associated with the xml_element parameter given as argument.
 
    Functional Description:
        Free all data (recursively) associated with the xml_element parameter given as argument.

    Arguments: 
        element - [in] Free all allocated memory associated with this argument.
        
    Return values:
        None
*/
/* --------------------------------------------------------------------------------------------- */
void parsexml_free_element(xml_element *element)
{
    /* Stop recursion */
    if (element == NULL)
    {
        return;
    }

    /* Free data */
    free(element->tag);
    free(element->data);
    parsexml_free_attributes(element->attributes_head);
    parsexml_free_element(element->children_head);

    /* Free rest of chain */
    parsexml_free_element(element->next);

    /* Free the element itself */
    free(element);
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_free_attributes
 
    Purpose: 
        Free all data (recursively) associated with the xml_attribute parameter given as argument.
 
    Functional Description:
        Free all data (recursively) associated with the xml_attribute parameter given as argument.

    Arguments: 
        attribute - [in] Free all allocated memory associated with this argument.
        
    Return values:
        None
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void parsexml_free_attributes(xml_attribute *attribute)
{
    /* Stop recursion */
    if (attribute == NULL)
    {
        return;
    }

    /* Free data */
    free(attribute->name);
    free(attribute->value);

    /* Free rest of chain */
    parsexml_free_attributes(attribute->next);

    /* Free the attribute itself */
    free(attribute);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_find_element_tag
 
    Purpose: 
        Find a xml_element with a given tag in a list of xml_element.
 
    Functional Description:
        Search through the xml_element list until first element with given tag is found

    Arguments: 
        xml_element - [in] list of xml_elements
        tag         - [in] tag to search for
        
    Return values:
        NULL : tag not found in list
        ptr  : pointer to xml_element with given tag
*/
/* --------------------------------------------------------------------------------------------- */
xml_element *parsexml_find_element_tag(xml_element *elem, const char *tag)
{
    xml_element *ptr = elem;
    while (ptr)
    {
        if (strcmp(ptr->tag, tag) == 0)
        {
            /* Found */
            return ptr;
        }
        ptr = ptr->next;
    }
    /* Not found */
    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_find_attribute
 
    Purpose: 
        Find a xml_attribute with a given name in a list of xml_attributes.
 
    Functional Description:
        Search through the xml_attribute list until first attribute with given name is found

    Arguments: 
        xml_attribute - [in] list of xml_attribute
        name          - [in] name to search for
        
    Return values:
        NULL : attribute not found in list
        value: attribute found and its value is returned.
*/
/* --------------------------------------------------------------------------------------------- */
const char *parsexml_find_attribute(xml_attribute *attr, const char *name)
{
    xml_attribute *ptr = attr;
    while (ptr)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            /* Found */
            return ptr->value;
        }
        ptr = ptr->next;
    }
    /* Not found */
    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: parsexml_get_error_text
 
    Purpose: 
        Look up the given error code and return the describing error text.
 
    Functional Description:
        Look up the given error code and return the describing error text.

    Arguments: 
        errorcode - [in] Error code for which to look up the corresponding text string
        
    Return values:
        Text string describing the error code
*/
/* --------------------------------------------------------------------------------------------- */
const char *parsexml_get_error_text(int errorcode)
{
    if (errorcode < 0 || errorcode > MAX_ERRORCODE)
    {
        /* Error */
        return "";
    }

    return parsexml_errorcodes[errorcode];
}

