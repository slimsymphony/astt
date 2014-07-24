/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_object.c
                ----------------
                SW Module






Project:          autogen

%name:            autogen_object.c %
%version:         co1tss#41 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Thu Dec  3 12:00:54 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    The file contains functions for manipulating with the objects in the data model, such as 
    adding, deleting, copying and seaching for objects 
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_object.h"
#include "autogen_util.h"
#include "pmd_heap.h"

#include <string.h>
#include <stdlib.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL static
#endif /* LOCAL */

#define AUTOGEN_SORT_INCLUDE_VERSION        0x00000001
#define AUTOGEN_SORT_INCLUDE_FEATUREFLAG    0x00000002
#define AUTOGEN_SORT_INCLUDE_ALL            0xFFFFFFFF


/* current object ID */
LOCAL unsigned int s_autogen_object_id = 0;

LOCAL autogen_obj* autogen_obj_find_in_list_from_current_pos(autogen_it* it);

LOCAL int autogen_obj_comp_id_ver(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags);
LOCAL int autogen_obj_comp_name_ver(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags);
LOCAL int autogen_obj_comp_ver(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags);
LOCAL int autogen_obj_comp_ver_rev(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags);
LOCAL int autogen_obj_comp_type_and_name_ver(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags);

LOCAL int (*s_sort_func[AUTOGEN_OBJ_LIST_SORT_TYPES])(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags) = 
{ 
    autogen_obj_comp_name_ver, 
    autogen_obj_comp_id_ver, 
    autogen_obj_comp_ver,
    autogen_obj_comp_ver_rev,
    autogen_obj_comp_type_and_name_ver
};


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_cmt_create
 
    Purpose: 
        Creates and initializes a comment object
 
    Functional Description:
        Creates and initializes a comment object
        The created object is returned

    Arguments: 
        id          - [in] id of comment (COMMENT_XXX)
        linktype    - [in] type of link (only for comment type AUTOGEN_COMMENT_LINK_TYPE)
        linkname    - [in] name of linked object (only for comment type AUTOGEN_COMMENT_LINK_TYPE)
        linksubname - [in] subname of linked object (only for comment type AUTOGEN_COMMENT_LINK_TYPE)
        linkver     - [in] version of linked object (only for comment type AUTOGEN_COMMENT_LINK_TYPE)
        comment     - [in] comment text

    Return Values::
        pointer to allocated comment object
*/
/* --------------------------------------------------------------------------------------------- */
autogen_cmt* autogen_cmt_create(autogen_comment_id id, unsigned int linktype, const char* linkname,
                                const char* linksubname, const char* linkver, const char* comment)
{
    autogen_cmt* cmt = NULL;


    if (id == COMMENT_NEWLINE)
    {
        cmt = (autogen_cmt*)pmd_heap_alloc(sizeof(autogen_cmt));

        cmt->id = COMMENT_NEWLINE;
    }
    else if (id == COMMENT_LINK_TYPE)
    {
        cmt = (autogen_cmt*)pmd_heap_alloc(sizeof(autogen_cmt));

        cmt->id     = COMMENT_LINK_TYPE;
        cmt->linktype = linktype;
        cmt->linkname = linkname;

        if (linksubname && strcmp(linksubname, "NULL"))
        {
            cmt->linksubname = linksubname;
        }
        else
        {
            cmt->linksubname = "";
        }

        /* set linked object version */
        if (linkver && linkver[0] && strlen(linkver) >= 7)
        {
            cmt->linkver.system = AUTOGEN_VERSION_ISI;

            cmt->linkver.from[0] = (unsigned short)atoi(linkver);
            cmt->linkver.from[1] = (unsigned short)atoi(linkver + 4);
            cmt->linkver.from[2] = 0;

            if (strlen(linkver) >= 11)
            {
                cmt->linkver.from[2] = (unsigned short)atoi(linkver + 8);
                cmt->linkver.system  = AUTOGEN_VERSION_DSP;
            }

            cmt->linkver.to[0] = cmt->linkver.from[0];
            cmt->linkver.to[1] = cmt->linkver.from[1];
            cmt->linkver.to[2] = cmt->linkver.from[2];

            cmt->linkver.type = AUTOGEN_OBJ_VERSION_EXACT;
        }
        else
        {
            cmt->linkver.type   = AUTOGEN_OBJ_VERSION_ALL;
            cmt->linkver.system = AUTOGEN_VERSION_ISI;
        }
    }
    else if (comment && (strlen(comment) > 0 ||
        (id != COMMENT_TEXT &&
        id != COMMENT_PARAGRAPH &&
        id != COMMENT_BULLET)))
    {
        cmt = (autogen_cmt*)pmd_heap_alloc(sizeof(autogen_cmt));

        cmt->id      = id;
        cmt->comment = comment;
    }
    else
    {
        cmt = (autogen_cmt*)pmd_heap_alloc(sizeof(autogen_cmt));

        cmt->id      = id;
        cmt->comment = "";
    }

    return cmt;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_cmt_add
 
    Purpose: 
        Adds a comment object to a comment list
 
    Functional Description:
        Adds the comment 'cmt' to the end of the comment list 'cmt_list'.

    Arguments: 
        cmt_list - [in] pointer to the comment list
        cmt      - [in] pointer to the comment object
*/
/* --------------------------------------------------------------------------------------------- */
void autogen_cmt_add(autogen_cmt** cmt_list, autogen_cmt* cmt)
{
    if (cmt)
    {
        autogen_cmt* cmt_trav = *cmt_list;

        /* should the new comment be placed as the first comment in the list? */
        if (!cmt_trav)
        {
            cmt->next = *cmt_list;
            *cmt_list = cmt;
        }
        /* else find the comment, which the new comment should be linked to */
        else
        {
            autogen_cmt* cmt_trav_last = cmt_trav;

            while (cmt_trav)
            {
                cmt_trav_last = cmt_trav;
                cmt_trav = cmt_trav->next;
            }

            /* now place the new comment */
            cmt->next = cmt_trav;
            cmt_trav_last->next = cmt;
        }
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_cmt_find
 
    Purpose: 
        Finds a comment of a specific type in a comment list
 
    Functional Description:
        Finds and returns the first occurence of one of the comment types satisfied by 'typemask'

    Arguments: 
        cmt_list - [in] pointer to the comment list
        id       - [in] comment id (COMMENT_XXX)

    Return Values::
        pointer to the found comment object or NULL if no comment fulfilled the search criteria
*/
/* --------------------------------------------------------------------------------------------- */
autogen_cmt* autogen_cmt_find(autogen_cmt* cmt_list, autogen_comment_id id)
{
    autogen_cmt* cmt_trav = cmt_list;

    while (cmt_trav && cmt_trav->id != id)
    {
        cmt_trav = cmt_trav->next;
    }

    return cmt_trav;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_obj_create
 
    Purpose: 
        Creates and initializes an object
 
    Functional Description:
        Creates and initializes an object
        The whole object is zero-initialized and then the base part of the object is initialized
        with the given attributes
        The created object is returned

    Arguments: 
        parent       - [in] pointer to parent object
        size         - [in] size of óbject to allocate (in bytes)
        type         - [in] type of object (AUTOGEN_OBJ_XXX)
        subtype      - [in] subtype of object (e.g. AUTOGEN_RES_XXX or AUTOGEN_ITEM_XXX)
        id           - [in] ID of object
        res          - [in] pointer to resource, containing the object
        name         - [in] name of object (or "" if none)
        feature_flag - [in] feature flag surrounding the object. NULL if none

    Return Values::
        pointer to allocated object
*/
/* --------------------------------------------------------------------------------------------- */
#if (PMD_FILE_FORMAT >= 600)
autogen_obj* autogen_obj_create(const char* file_name, int file_line, autogen_res* res, autogen_obj* parent, 
                                unsigned int size, unsigned int type, unsigned int subtype,
                                unsigned long long id, const char* name, autogen_feature *feature_flag)
#else
autogen_obj* autogen_obj_create(const char* file_name, int file_line, autogen_res* res, autogen_obj* parent, 
                                unsigned int size, unsigned int type, unsigned int subtype,
                                unsigned int id, const char* name, autogen_feature *feature_flag)
#endif
{
    autogen_obj* obj = (autogen_obj*)pmd_heap_alloc(size);

    /* set unique object id */
    obj->obj_id  = ++s_autogen_object_id;

    obj->base_obj = obj;

    obj->size    = size;
    obj->type    = type;
    obj->subtype = subtype;
    obj->id      = id;

    obj->name    = name ? name : "";

    obj->ver.system  = AUTOGEN_VERSION_ISI;
    obj->ver.type    = AUTOGEN_OBJ_VERSION_ALL;
    obj->ver.from[0] = 0;
    obj->ver.from[1] = 0;
    obj->ver.from[2] = 0;
    obj->ver.to[0]   = 256;
    obj->ver.to[1]   = 0;
    obj->ver.to[2]   = 0;

    obj->res    = res;
    obj->parent = parent;

    obj->feature_flags = feature_flag;

    obj->file_name = file_name;
    obj->file_line = file_line;

    return obj;
}

/*  autogen_obj_ver_is_included

    is version2 entirely included in version1?
    
    V2:     |     ALL    EXACT   INTERVAL
    ---------------------------------------
    V1: ALL |   TRUE      TRUE     TRUE
      EXACT |  FALSE       ?      FALSE 
   INTERVAL |  FALSE       ?        ? 
*/
int autogen_obj_ver_is_included(const autogen_ver* version1, const autogen_ver* version2)
{
    int is_incl = FALSE;

    if (version1->ver_str || version2->ver_str)
    {
        /* FALSE */
    }
    if (version1->type == AUTOGEN_OBJ_VERSION_ALL) /* Obvious */
    {
        is_incl = TRUE;
    }
    else if (version2->type == AUTOGEN_OBJ_VERSION_ALL) /* Obvious */
    {
        /* FALSE */
    }
    else if ((version1->type == AUTOGEN_OBJ_VERSION_EXACT) && (version2->type == AUTOGEN_OBJ_VERSION_EXACT))
    {
        is_incl = autogen_obj_ver_is_exact(version1, version2);
    }
    else if ((version1->type == AUTOGEN_OBJ_VERSION_EXACT) && (version2->type == AUTOGEN_OBJ_VERSION_INTERVAL))
    {
        /* FALSE */
    }
    else if ((version1->type == AUTOGEN_OBJ_VERSION_INTERVAL) && (version2->type == AUTOGEN_OBJ_VERSION_EXACT))
    {
        if ((autogen_ver_comp(version2->to,   version1->to)   & AUTOGEN_VER_NEWER) &&
            (autogen_ver_comp(version2->from, version1->from) & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL)))
        {
            is_incl = TRUE;
        }
    }
    else if ((autogen_ver_comp(version2->to,   version1->to)   & (AUTOGEN_VER_EQUAL | AUTOGEN_VER_NEWER)) &&
             (autogen_ver_comp(version2->from, version1->from) & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL)))
    {
        is_incl = TRUE;
    }

    return is_incl;
}


/*  autogen_obj_ver_is_exact

    Checks if the object version is identical to the given version

    Return codes:

    TRUE, if the object version is identical to the given version
    FALSE, if not

    Test: 
*/

int autogen_obj_ver_is_exact(const autogen_ver* version1, const autogen_ver* version2)
{
    int is_exact = 
        (version1->to[0] == version2->to[0] &&
        version1->to[1] == version2->to[1] &&
        version1->to[2] == version2->to[2] &&

        version1->from[0] == version2->from[0] &&
        version1->from[1] == version2->from[1] &&
        version1->from[2] == version2->from[2] &&

        version1->ver_str == NULL &&
        version2->ver_str == NULL);

    return is_exact;
}



int autogen_obj_ver_is_overlapping(const autogen_ver* version1, const autogen_ver* version2)
{
    int is_overlapping;

    if ((autogen_ver_comp(version2->from, version1->from) & AUTOGEN_VER_OLDER) &&
        (autogen_ver_comp(version2->from, version1->to) & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL)))
    {
        is_overlapping = FALSE;        
    }
    else if ((autogen_ver_comp(version1->from, version2->from) & AUTOGEN_VER_OLDER) &&
        (autogen_ver_comp(version1->from, version2->to) & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL)))
    {
        is_overlapping = FALSE;        
    }
    else
    {
        is_overlapping = TRUE;
    }

    return is_overlapping;
}


/*  -------------------------------------------------------------------------------------------- */
/*  Name: autogen_ver_comp
 
    Purpose: 
        Compare version number of two objects
 
    Functional Description:
        The function compares the version numbers of two objects
        ver1 is expected to be the "reference version", ver2 is compared to the reference version
		i.e. if ver1 is greater (newer) than ver2 then the AUTOGEN_VER_OLDER bit will be set in
		the return code (meaning: ver2 is older than ver1)

    Arguments: 
        ver1 - [in] version of first object (derived from autogen_obj)
        ver2 - [in] version of second object (derived from autogen_obj)

    Return Values (bit mask):
        AUTOGEN_VER_EQUAL                1  if versions are identical
        AUTOGEN_VER_NEWER                2  ver2 greater (newer) than ver1
        AUTOGEN_VER_OLDER                4  ver2 lower (older) than ver1
        AUTOGEN_VER_MAJOR_INCREMENTED    8  major version number of ver2 higher than ver1
        AUTOGEN_VER_MAJOR_DECREMENTED   16  major version number of ver2 lower than ver1
        AUTOGEN_VER_MINOR_INCREMENTED   32  minor version number of ver2 higher than ver1
        AUTOGEN_VER_MINOR_DECREMENTED   64  minor version number of ver2 lower than ver1
        AUTOGEN_VER_MINOR_IS_NULL      128  minor version number of ver2 is 0
*/
/* --------------------------------------------------------------------------------------------- */
int autogen_ver_comp(const unsigned short* ver1, const unsigned short* ver2)
{
    int ret_code = 0; 

    /* first do a general version comparison */
    if (ver1[0] > ver2[0] || ver1[0] == ver2[0] && (ver1[1] > ver2[1] || ver1[1] == ver2[1] && ver1[2] > ver2[2]))
    {
        ret_code |= AUTOGEN_VER_OLDER;
    }
    else if (ver1[0] == ver2[0] && ver1[1] == ver2[1] && ver1[2] == ver2[2])
    {
        ret_code = AUTOGEN_VER_EQUAL; /* versions are identical */
    }
    else
    {
        ret_code |= AUTOGEN_VER_NEWER;
    }

    /* let's have a look at major version number */
    if (ver1[0] > ver2[0])
    {
        ret_code |= AUTOGEN_VER_MAJOR_DECREMENTED;
    }
    else if (ver1[0] < ver2[0])
    {
        ret_code |= AUTOGEN_VER_MAJOR_INCREMENTED;
    }

    /* now, how about the minor version number */
    if (ver1[1] > ver2[1])
    {
        if (ver2[1] == 0)
        {
            ret_code |= AUTOGEN_VER_MINOR_IS_NULL;
        } 
        else
        {
            ret_code |= AUTOGEN_VER_MINOR_DECREMENTED;
        }
    }
    else if (ver1[1] < ver2[1])
    {
        ret_code |= AUTOGEN_VER_MINOR_INCREMENTED;
    }

    return ret_code;
}


autogen_obj* autogen_res_ver_add(autogen_res* res, const unsigned short* ver, unsigned int system)
{
    autogen_obj* ver_obj = NULL;

    if (res && ver && ver[0] < 256 && (ver[0] != 0 || ver[1] != 0))
    {
        ver_obj = autogen_obj_create(NULL, 0, res, &res->base, sizeof(autogen_obj), AUTOGEN_OBJ_VERSION, 0, 0, NULL, NULL);

        ver_obj->ver.from[0] = ver[0];
        ver_obj->ver.from[1] = ver[1];
        ver_obj->ver.from[2] = ver[2];
        ver_obj->ver.to[0]   = ver[0];
        ver_obj->ver.to[1]   = ver[1];
        ver_obj->ver.to[2]   = ver[2];
        ver_obj->ver.type    = AUTOGEN_OBJ_VERSION_EXACT;
        ver_obj->ver.system  = system;

        if (autogen_obj_list_add_obj(&res->ver_list, ver_obj, AUTOGEN_ENV_NONE))
        {
            autogen_obj_list_init(&ver_obj->child_list, ver_obj, 0, 20);
        }
    }

    return ver_obj;
}

unsigned int autogen_obj_ver_merge(const autogen_ver* ver1, const autogen_ver* ver2, autogen_ver* retver)
{
    unsigned int result = AUTOGEN_OK;
    const unsigned short* verfrom = ver1->from;
    const unsigned short* verto   = ver1->to;


    if (!autogen_obj_ver_is_overlapping(ver1, ver2) &&
        !(ver1->to[0] == ver2->from[0] && ver1->to[1] == ver2->from[1] && ver1->to[2] == ver2->from[2]) &&
        !(ver2->to[0] == ver1->from[0] && ver2->to[1] == ver1->from[1] && ver2->to[2] == ver1->from[2]))
    {
        result = AUTOGEN_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        if (autogen_ver_comp(ver2->from, verfrom) & AUTOGEN_VER_NEWER)
        {
            verfrom = ver2->from;
        }
        if (autogen_ver_comp(ver2->to, verto) & AUTOGEN_VER_OLDER)
        {
            verto = ver2->to;
        }

        autogen_obj_ver_set(retver, verfrom, verto);
    }

    return result;
}

unsigned int autogen_obj_ver_set(autogen_ver* ver, const unsigned short* ver_from, const unsigned short* ver_to)
{
    unsigned int result = AUTOGEN_OK;


    /* copy versions */
    ver->from[0] = ver_from[0];
    ver->from[1] = ver_from[1];
    ver->from[2] = ver_from[2];

    ver->to[0] = ver_to[0];
    ver->to[1] = ver_to[1];
    ver->to[2] = ver_to[2];

    if (ver->to[0] == 255 && ver->to[1] == 255 && ver->to[2] == 255)
    {
        ver->to[0] = 256;
        ver->to[1] = 0;
        ver->to[2] = 0;
    }

    /* set version flag */
    if (ver_from[0] == 0 && ver_from[1] == 0 && ver_from[2] == 0 &&
        ver_to[0] == 256 && ver_to[1] == 0   && ver_to[2] == 0)
    {
        ver->type = AUTOGEN_OBJ_VERSION_ALL;
    }
    else if (ver_from[0] == ver_to[0] && ver_from[1] == ver_to[1] && ver_from[2] == ver_to[2])
    {
        ver->type = AUTOGEN_OBJ_VERSION_EXACT;
    }
    else if (ver_from[0] == 0 && ver_from[1] == 0 && ver_from[2] == 0)
    {
        ver->type = AUTOGEN_OBJ_VERSION_TO;
    }
    else if (ver_to[0] == 256 && ver_to[1] == 0 && ver_to[2] == 0)
    {
        ver->type = AUTOGEN_OBJ_VERSION_FROM;
    }
    else
    {
        ver->type = AUTOGEN_OBJ_VERSION_INTERVAL;
    }

    /* check intervals */
    if (autogen_ver_comp(ver->from, ver->to) & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL))
    {
        result = AUTOGEN_ERROR_ITEM_VERSION_CONFLICT;
    }

    return result;
}


autogen_cmt* autogen_cmt_copy(const autogen_cmt* src)
    {
    autogen_cmt* cmt_list = NULL;

    /* copy comments */
    while (src)
        {
        /* allocate new comment object */
        autogen_cmt* new_cmt = (autogen_cmt*)pmd_heap_alloc(sizeof(autogen_cmt));

        /* copy all comment attributes */
        memcpy(new_cmt, src, sizeof(autogen_cmt));
    
        /* reset some attributes */
        new_cmt->next = NULL;

        autogen_cmt_add(&cmt_list, new_cmt);

        src = src->next;
        }

    return cmt_list;
    }

autogen_obj* autogen_obj_copy_deep(const autogen_obj* src, autogen_obj* obj, autogen_obj* parent, const autogen_ver* ver)
{
    /* only copy objects which overlaps with given version */
    if (src && autogen_obj_ver_is_overlapping(&src->ver, ver))
    {
        int n;

        /* allocate new object */
        if (!obj)
        {
            obj = (autogen_obj*)pmd_heap_alloc(src->size);
        }

        /* copy all object attributes */
        memcpy(obj, src, src->size);

        obj->related_obj.n_obj = 0;

        obj->next = NULL;
        obj->parent = parent;
        if (parent)
        {
            obj->res = parent->res;
        }
        else
        {
            obj->res = NULL;
        }

        if (src->base_obj == src)
        {
            obj->base_obj = obj;
        }
        else
        {
            obj->base_obj = obj->parent;
        }

        if (src->type == AUTOGEN_ITEM_CHOICE)
        {
            autogen_item_choice* choice = (autogen_item_choice*)src;

            choice->default_case = (autogen_item_case*)autogen_obj_copy_deep(&choice->default_case->base.base, NULL, obj, ver);
        }

        /* crop version of object agains given version */
        memcpy(&obj->ver, autogen_obj_ver_crop(&obj->ver, ver), sizeof(autogen_ver));

        /* initialize child list */
        autogen_obj_list_init(&obj->child_list, obj, src->child_list.flag, src->child_list.n_obj_allocated);

        /* deep copy items */
        for (n = 0; n < src->child_list.n_obj; n++)
        {
            autogen_obj* src_obj = src->child_list.obj_list[n];

            autogen_obj* child_obj = autogen_obj_create(src_obj->file_name, src_obj->file_line, src_obj->res, obj, src_obj->size, src_obj->type, src_obj->subtype, 
                src_obj->id, src_obj->name, src_obj->feature_flags);

            autogen_obj_list_add_obj(&obj->child_list, child_obj, AUTOGEN_ENV_NONE);

            autogen_obj_copy_deep(src_obj, child_obj, obj, ver);
        }
    }

    return obj;
}

void autogen_obj_ver_replace_deep(autogen_obj* obj, const autogen_ver* ver, int replace_next)
{
    if (obj)
    {
        int n;

        /* exchange all next pointers with new allocations */
        if (replace_next)
        {
            autogen_obj_ver_replace_deep(obj->next, ver, TRUE);
        }

        memcpy(&obj->ver, ver, sizeof(autogen_ver));

        /* relace version on child items */
        for (n = 0; n < obj->child_list.n_obj; n++)
        {
            autogen_obj_ver_replace_deep(obj->child_list.obj_list[n], ver, TRUE);
        }
    }
}

const autogen_ver* autogen_obj_ver_crop(const autogen_ver* ver1, const autogen_ver* ver2)
{
    static autogen_ver s_obj_ver_crop = INIT_VERSION_ALL;
    const unsigned short* from = NULL;

    /* invalid interval */
    if ((autogen_ver_comp(ver1->to,   ver2->from) & (AUTOGEN_VER_EQUAL | AUTOGEN_VER_NEWER)) ||
        (autogen_ver_comp(ver1->from, ver2->to)   & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL)))
    {
    }
    else
    {
        /* set left interval */
        if (autogen_ver_comp(ver1->from, ver2->from) & AUTOGEN_VER_NEWER)
        {
            from = ver2->from;
        }
        else
        {
            from = ver1->from;
        }

        /* set right interval */
        if (autogen_ver_comp(ver1->to, ver2->to) & AUTOGEN_VER_OLDER)
        {
            autogen_obj_ver_set(&s_obj_ver_crop, from, ver2->to);
        }
        else
        {
            autogen_obj_ver_set(&s_obj_ver_crop, from, ver1->to);
        }
    }

    return &s_obj_ver_crop;
}

int autogen_obj_ver_comp(const autogen_ver* ver_left, const autogen_ver* ver_right)
{
    int comp;

    if (autogen_obj_ver_is_overlapping(ver_left, ver_right))
    {
        return 0;
    }
    comp = autogen_ver_comp(ver_left->from, ver_right->from);

    if (comp & AUTOGEN_VER_EQUAL) return 0;

    return (comp & AUTOGEN_VER_OLDER) ? 1 : -1;
}

LOCAL int autogen_obj_featureflag_comp_string(const char* left, const char *right)
{
    /* If one or both strings is a null pointer */
    if (!left || !right)
    {
        /* Both are null pointers */
        if (left == right) {
            return 0;
        }
        /* Only one string is a null pointer */
        return (left ? 1 : -1);
    }

    /* Compare flags */
    return strcmp(left, right);
}

int autogen_obj_featureflag_comp(const autogen_feature *left, const autogen_feature *right)
{
    int comp;

    /* Take into consideration that one or both parameters (left, right) may be NULL  */
    if (left == NULL || right == NULL)
    {
        /* A null flag is considered as no feature flag. */
        /* Consider the flags being the same */
        return 0;
    }

    /* Compare flag logic */
    if (left->flag_logic != right->flag_logic)
    {
        return (left->flag_logic < right->flag_logic ? 1 : -1);
    }

    /* If both logic flags are FT_ELSE then we must compare the head of the feature flag */
    if (left->flag_logic == FT_ELSE)
    {
        return autogen_obj_featureflag_comp(left->head, right->head);
    }

    /* Check the first flag */
    if (left->feature1 && right->feature1) 
    {
        /* Compare flags */
        comp = autogen_obj_featureflag_comp_string(left->feature1->flag, right->feature1->flag);
        if (comp != 0) return comp;

        /* Compare values */
        comp = autogen_obj_featureflag_comp_string(left->feature1->value, right->feature1->value);
        if (comp != 0) return comp;
    }

    /* Check the second flag */
    if (left->feature2 && right->feature2) 
    {
        /* Compare flags */
        comp = autogen_obj_featureflag_comp_string(left->feature2->flag, right->feature2->flag);
        if (comp != 0) return comp;

        /* Compare values */
        comp = autogen_obj_featureflag_comp_string(left->feature2->value, right->feature2->value);
        if (comp != 0) return comp;
    }

    return 0;
}

void autogen_obj_list_init(autogen_obj_list* obj_list, autogen_obj* parent, unsigned int flags, int n_allocated)
{
    int n;

    obj_list->flag   = flags;
    obj_list->parent = parent;

    obj_list->obj_list = (autogen_obj**)pmd_heap_alloc(sizeof(autogen_obj*) * n_allocated);

    for (n = 0; n < AUTOGEN_OBJ_LIST_SORT_TYPES; n++)
    {
        if (flags & (1 << n))
        {
            obj_list->map[n] = (autogen_obj**)pmd_heap_alloc(sizeof(autogen_obj*) * n_allocated);
        }
    }

    obj_list->n_obj           = 0;
    obj_list->n_obj_allocated = n_allocated;
}

LOCAL int autogen_obj_comp_id_ver(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags)
{
    int comp;

    if (obj_left->id != obj_right->id) 
    {
        return obj_left->id < obj_right->id ? -1 : 1;
    }

    if (flags & AUTOGEN_SORT_INCLUDE_VERSION) 
    {
        comp = autogen_obj_ver_comp(&obj_left->ver, &obj_right->ver);
        if (comp != 0) return comp;
    }

    if (flags & AUTOGEN_SORT_INCLUDE_FEATUREFLAG)
    {
        return autogen_obj_featureflag_comp(obj_left->feature_flags, obj_right->feature_flags);
    }

    return 0;
}

LOCAL int autogen_obj_comp_type_and_name_ver(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags)
{
    int comp;

    if (!(obj_left->type & obj_right->type)) 
    {
        return (obj_left->type < obj_right->type) ? -1 : 1;
    }

    if (!(obj_left->subtype & obj_right->subtype)) 
    {
        return (obj_left->subtype < obj_right->subtype) ? -1 : 1;
    }

    comp = strcmp(obj_left->name, obj_right->name);
    if (comp != 0) return comp;

    if (flags & AUTOGEN_SORT_INCLUDE_VERSION) 
    {
        comp = autogen_obj_ver_comp(&obj_left->ver, &obj_right->ver);
        if (comp != 0) return comp;
    }

    if (flags & AUTOGEN_SORT_INCLUDE_FEATUREFLAG)
    {
        return autogen_obj_featureflag_comp(obj_left->feature_flags, obj_right->feature_flags);
    }

    return 0;
}

LOCAL int autogen_obj_comp_name_ver(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags)
{
    int comp = strcmp(obj_left->name, obj_right->name);
    if (comp != 0) return comp;
    
    if (flags & AUTOGEN_SORT_INCLUDE_VERSION) 
    {
        comp = autogen_obj_ver_comp(&obj_left->ver, &obj_right->ver);
        if (comp != 0) return comp;
    }
    
    if (flags & AUTOGEN_SORT_INCLUDE_FEATUREFLAG)
    {
        return autogen_obj_featureflag_comp(obj_left->feature_flags, obj_right->feature_flags);
    }

    return 0;
}

LOCAL int autogen_obj_comp_ver(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags)
{
    int comp;

    if (obj_right->ver.ver_str && obj_left->ver.ver_str)
    {
        if (!strcmp(obj_right->ver.ver_str, obj_left->ver.ver_str))
        {
            if (flags & AUTOGEN_SORT_INCLUDE_FEATUREFLAG)
            {
                return autogen_obj_featureflag_comp(obj_left->feature_flags, obj_right->feature_flags);
            }
            return 0;
        }
        return (obj_left->obj_id < obj_right->obj_id) ? +1 : -1;
    }

    comp = autogen_obj_ver_comp(&obj_left->ver, &obj_right->ver);
    if (comp != 0) return comp;

    if (flags & AUTOGEN_SORT_INCLUDE_FEATUREFLAG)
    {
        return autogen_obj_featureflag_comp(obj_left->feature_flags, obj_right->feature_flags);
    }

    return 0;
}

LOCAL int autogen_obj_comp_ver_rev(const autogen_obj* obj_left, const autogen_obj* obj_right, unsigned int flags)
{
    int comp;

    if (obj_right->ver.ver_str && obj_left->ver.ver_str)
    {
        if (!strcmp(obj_right->ver.ver_str, obj_left->ver.ver_str))
        {
            if (flags & AUTOGEN_SORT_INCLUDE_FEATUREFLAG)
            {
                return autogen_obj_featureflag_comp(obj_left->feature_flags, obj_right->feature_flags);
            }
            return 0;
        }
        return (obj_left->obj_id < obj_right->obj_id) ? -1 : +1;
    }

    comp = autogen_obj_ver_comp(&obj_right->ver, &obj_left->ver);
    if (comp != 0) return comp;

    if (flags & AUTOGEN_SORT_INCLUDE_FEATUREFLAG)
    {
        return autogen_obj_featureflag_comp(obj_left->feature_flags, obj_right->feature_flags);
    }

    return 0;
}

int autogen_obj_list_add_obj(autogen_obj_list* obj_list, autogen_obj* obj, unsigned int error_env)
{
    int n;
    
    /* reallocate list ? */
    if (obj_list->n_obj_allocated == obj_list->n_obj)
    {
        int list_size = obj_list->n_obj_allocated * sizeof(autogen_obj*);
        int new_allocations = (obj_list->n_obj_allocated > 0) ? 2 * obj_list->n_obj_allocated : 10;
        int new_list_size   = new_allocations * sizeof(autogen_obj*);

        autogen_obj** old_list = obj_list->obj_list;
        obj_list->obj_list = (autogen_obj**)pmd_heap_alloc(new_list_size);
        memcpy(obj_list->obj_list, old_list, list_size);

        /* reallocate sorted maps */
        for (n = 0; n < AUTOGEN_OBJ_LIST_SORT_TYPES; n++)
        {
            if (obj_list->flag & (1 << n))
            {
                old_list = obj_list->map[n];
                obj_list->map[n] = (autogen_obj**)pmd_heap_alloc(new_list_size);
                memcpy(obj_list->map[n], old_list, list_size);
            }
        }

        obj_list->n_obj_allocated = new_allocations;
    }

    /* add object and set pointer from previous object */
    obj_list->obj_list[obj_list->n_obj] = obj;
    if (obj_list->n_obj > 0)
    {
        obj_list->obj_list[obj_list->n_obj-1]->next = obj;
    }

    for (n = 0; n < AUTOGEN_OBJ_LIST_SORT_TYPES; n++)
    {
        if (obj_list->flag & (1 << n))
        {
            /* insertion point in sorted pointer array */
            int ins   = 0;

            if (obj_list->n_obj > 0)
            {
                int left  = 0;
                int mid   = 0;
                int right = obj_list->n_obj;

                /* binary search */
                while (left <= right)
                {
                    int match = 1;

                    mid = (left + right) / 2;
                    if (mid < obj_list->n_obj)
                    {
                        match = s_sort_func[n](obj_list->map[n][mid], obj, AUTOGEN_SORT_INCLUDE_ALL);
                        /* Conflict when adding object? */
                        if (match == 0 && !(
                            obj->res->base.subtype == RESOURCE_MEDIA_MODULE && 
                            (obj->type & (AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE)) != 0 &&
                            (obj->flag & AUTOGEN_MSG_FUNCTION_MASK) != 0
                            ))
                        {
                            if (error_env != AUTOGEN_ENV_NONE)
                            {
                                char parent_info[100] = "";
                                autogen_obj* parent = obj->parent;
                                while (parent && parent->parent && parent->parent->type != AUTOGEN_OBJ_RES)
                                {
                                    parent = parent->parent;
                                }

                                if (parent && parent->type != AUTOGEN_OBJ_RES)
                                {
                                    sprintf(parent_info, " in %s '%s'", util_get_obj_type_name(parent), util_get_obj_name(parent));
                                }

                                if (n == AUTOGEN_OBJ_LIST_SORT_BY_ID)
                                {
#if (PMD_FILE_FORMAT >= 600)
                                    util_error_line(obj->file_name, obj->file_line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                                        "%s ID '0x%2.2llX'%s conflicts with earlier definition", util_get_obj_type_name(obj), obj->id, parent_info);
#else
                                    util_error_line(obj->file_name, obj->file_line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                                        "%s ID '0x%2.2X'%s conflicts with earlier definition", util_get_obj_type_name(obj), obj->id, parent_info);
#endif
                                }
                                else
                                {
                                    util_error_line(obj->file_name, obj->file_line, AUTOGEN_ERROR_FATAL, AUTOGEN_ENV_LOCAL, 0,
                                        "%s '%s' conflicts%s with earlier definition", util_get_obj_type_name(obj), util_get_obj_name(obj), parent_info);
                                }
                            }
                            return FALSE;
                        }
                    }
                    if (match > 0)
                    {
                        right = mid - 1;
                        ins   = mid;
                    }
                    else
                    {
                        left = mid + 1;
                        ins  = mid + 1;
                    }
                }

                if (ins < obj_list->n_obj)
                {
                    memmove(&obj_list->map[n][ins + 1], &obj_list->map[n][ins], sizeof(autogen_obj*)*(obj_list->n_obj - ins));
                }
            }

            obj_list->map[n][ins] = obj;
        }
    }

    obj_list->n_obj++;

    return TRUE;
}

autogen_obj* autogen_obj_find_in_list(autogen_it* it, autogen_obj_list* obj_list)
{
    /* reset iterator */
    it->current_index = 0;
    it->current_obj = NULL;
    it->current_obj_list = obj_list;

    it->sort_map          = obj_list->obj_list;
    it->sort_flags        = 0;
    it->use_binary_search = FALSE;

    if (it->ver && it->vercrit != AUTOGEN_OBJ_VERSION_ANY)
    {
        memcpy(&it->obj.ver, it->ver, sizeof(autogen_ver));
    }

    /* Setup for sorted list search */
    if (it->sort_type == AUTOGEN_OBJ_LIST_SORT_NONE)
    {
        it->sort_map  = obj_list->obj_list;
        it->sort_type = it->sort_type;
    }
    else if (it->sort_type != AUTOGEN_OBJ_LIST_SORT_UNDEFINED)
    {
        it->sort_map  = obj_list->map[it->sort_type];
        it->sort_type = it->sort_type;
    }
    else if (it->idcrit == AUTOGEN_OBJ_ID_EXACT && (obj_list->flag & AUTOGEN_OBJ_LIST_SORTED_BY_ID))
    {
        it->sort_map  = obj_list->map[AUTOGEN_OBJ_LIST_SORT_BY_ID];
        it->sort_type = AUTOGEN_OBJ_LIST_SORT_BY_ID;
    }
    else if (it->obj.name && (obj_list->flag & AUTOGEN_OBJ_LIST_SORTED_BY_NAME))
    {
        it->sort_map  = obj_list->map[AUTOGEN_OBJ_LIST_SORT_BY_NAME];
        it->sort_type = AUTOGEN_OBJ_LIST_SORT_BY_NAME;
    }

    /* setup binary search */
    if (it->idcrit == AUTOGEN_OBJ_ID_EXACT && (obj_list->flag & AUTOGEN_OBJ_LIST_SORTED_BY_ID) && it->sort_type == AUTOGEN_OBJ_LIST_SORT_BY_ID)
    {
        it->use_binary_search = TRUE;
    }
    else if (it->obj.name && (obj_list->flag & AUTOGEN_OBJ_LIST_SORTED_BY_NAME) && it->sort_type == AUTOGEN_OBJ_LIST_SORT_BY_NAME)
    {
        it->use_binary_search = TRUE;
    }
    else if (it->vercrit != AUTOGEN_OBJ_VERSION_ANY && (obj_list->flag & (AUTOGEN_OBJ_LIST_SORTED_BY_VERSION | AUTOGEN_OBJ_LIST_SORTED_BY_VERSION_REVERSED)) && (it->sort_type == AUTOGEN_OBJ_LIST_SORT_BY_VERSION || it->sort_type == AUTOGEN_OBJ_LIST_SORT_BY_VERSION_REVERSED))
    {
        it->use_binary_search = TRUE;
    }

    /* Do the actual binary search */
    if (it->use_binary_search == TRUE && obj_list->n_obj > 0 && it->vercrit != AUTOGEN_OBJ_VERSION_FIRST)
    {
        int left  = 0;
        int mid   = 0;
        int right = obj_list->n_obj;
        int match = 1;
        int found = FALSE;

        /* binary search */
        while (left <= right && found == FALSE)
        {
            match = 1;

            mid = (left + right) / 2;
            if (mid < obj_list->n_obj)
            {
                match = s_sort_func[it->sort_type](it->sort_map[mid], &it->obj, it->sort_flags);
            }
            if (match == 0)
            {
                it->current_index = mid;
                found = TRUE;
            }
            else if (match > 0)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        /* object found... Now reverse search to find first of the object */
        while (it->current_index > 0 && s_sort_func[it->sort_type](it->sort_map[it->current_index-1], &it->obj, it->sort_flags) == 0)
        {
            it->current_index--;
        }
    }


    /* Continue search by looking at all search criterias */
    return autogen_obj_find_in_list_from_current_pos(it);
}

autogen_obj* autogen_obj_find_next_in_list(autogen_it* it)
{
    autogen_obj* obj;
    autogen_obj* last_obj = it->current_obj;

    it->current_index++;
    it->current_obj = NULL;

    obj = autogen_obj_find_in_list_from_current_pos(it);

    if (it->vercrit == AUTOGEN_OBJ_VERSION_FIRST)
    {
        while (obj && s_sort_func[it->sort_type](obj, last_obj, it->sort_flags) == 0)
        {
            it->current_index++;
            it->current_obj = NULL;

            obj = autogen_obj_find_in_list_from_current_pos(it);
        }
    }

    return obj;
}

LOCAL autogen_obj* autogen_obj_find_in_list_from_current_pos(autogen_it* it)
{
    while (!it->current_obj && it->current_index < it->current_obj_list->n_obj)
    {
        autogen_obj* obj = it->sort_map[it->current_index];

        int found = TRUE;

        /* return, if we are past the searched object */
        if (it->use_binary_search == TRUE && it->vercrit != AUTOGEN_OBJ_VERSION_FIRST && s_sort_func[it->sort_type](obj, &it->obj, it->sort_flags) < 0)
        {
            return NULL;
        }

        /* compare object type */
        found = ((obj->type & it->typemask) != 0 || it->typemask == AUTOGEN_OBJ_ANY) ? TRUE : FALSE;

        /* compare flag_none - none of the flags must be set */
        if (found)
        {
            found = ((obj->flag & it->flagnone) != 0) ? FALSE : TRUE;
        }

        /* compare flag_all - all of the flags must be set */
        if (found)
        {
            found = ((obj->flag & it->flagall) == it->flagall) ? TRUE : FALSE;
        }

        /* compare flag_any - any of the flags must be set */
        if (found)
        {
            found = ((obj->flag & it->flagany) != 0 || it->flagany == AUTOGEN_OBJ_ANY) ? TRUE : FALSE;
        }

        /* compare object sub type */
        if (found)
        {
            switch (it->subtypecrit)
            {
            case AUTOGEN_OBJ_SUBTYPE_ANY:
                {
                    found = ((obj->subtype & it->subtypemask) != 0 || it->subtypemask == AUTOGEN_OBJ_ANY) ? TRUE : FALSE;
                }            
                break;

            case AUTOGEN_OBJ_SUBTYPE_NOT_ANY:
                {
                    found = ((obj->subtype & it->subtypemask) != 0 || it->subtypemask == AUTOGEN_OBJ_ANY) ? FALSE : TRUE;
                }            
                break;

            case AUTOGEN_OBJ_SUBTYPE_EXACT:
                {
                    found = (obj->subtype == it->subtypemask) ? TRUE : FALSE;
                }
                break;

            case AUTOGEN_OBJ_SUBTYPE_NOT:
                {
                    found = (obj->subtype != it->subtypemask) ? TRUE : FALSE;
                }
                break;

            default:
                {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in autogen_obj_matches(). subtypecrit is %d", it->subtypecrit);
                }
                break;
            }
        }

        /* compare object id */
        if (found)
        {
            switch (it->idcrit)
            {
            case AUTOGEN_OBJ_ID_ANY:
                {
                }
                break;

            case AUTOGEN_OBJ_ID_NOT:
                {
                    found = (it->obj.id != obj->id) ? TRUE : FALSE;
                }
                break;

            case AUTOGEN_OBJ_ID_EXACT:
                {
                    found = (it->obj.id == obj->id) ? TRUE : FALSE;
                }
                break;

            default:
                {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in autogen_obj_matches(). idcrit is %d", it->idcrit);
                }
                break;
            }
        }

        /* compare object flag */
        if (found)
        {
            switch (it->flagcrit)
            {
            case AUTOGEN_OBJ_FLAG_ANY:
                {
                    found = ((obj->flag & it->flagmask) != 0 || it->flagmask == AUTOGEN_OBJ_ANY) ? TRUE : FALSE;
                }            
                break;

            case AUTOGEN_OBJ_FLAG_ALL:
                {
                    found = ((obj->flag & it->flagmask) == it->flagmask) ? TRUE : FALSE;
                }
                break;

            default:
                {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in autogen_obj_matches(). flagcrit is %d", it->flagcrit);
                }
                break;
            }
        }

        /* compare object names */
        if (found)
        {
            found = (it->obj.name == AUTOGEN_OBJ_NAME_ANY || !strcmp(obj->name, it->obj.name));
        }

        /* compare object versions */
        if (found)
        {
            switch (it->vercrit)
            {
            case AUTOGEN_OBJ_VERSION_ANY:
            case AUTOGEN_OBJ_VERSION_FIRST:
                {
                    /* still ok... */
                }
                break;

            case AUTOGEN_OBJ_VERSION_OVERLAP:
                {
                    found = autogen_obj_ver_is_overlapping(&obj->ver, it->ver);
                }
                break;

            case AUTOGEN_OBJ_VERSION_COVER_SINGLE:
            case AUTOGEN_OBJ_VERSION_COVER_MULTIPLE:
                {
                    found = autogen_obj_ver_is_included(&obj->ver, it->ver);
                }
                break;

            case AUTOGEN_OBJ_VERSION_INCLUDES:
                {
                    found = autogen_obj_ver_is_included(&obj->ver, it->ver);
                }
                break;

            case AUTOGEN_OBJ_VERSION_INCLUDES_NOT:
                {
                    found = !autogen_obj_ver_is_included(&obj->ver, it->ver);
                }
                break;

            default:
                {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in autogen_obj_matches(). versioncrit is %d", it->vercrit);
                }
                break;
            }
        }

        /* compare feature flags */
        if (found)
        {
            switch (it->featureflagcrit)
            {
            case AUTOGEN_OBJ_FEATUREFLAG_CHECK:
                {
                    found = autogen_obj_featureflag_comp(obj->feature_flags, it->obj.feature_flags) == 0 ? TRUE : FALSE;
                }
                break;

            case AUTOGEN_OBJ_FEATUREFLAG_NO_CHECK:
                /* Do not check feature flags */
                break;

            default:
                {
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_LOCAL, 0,
                        "Default case met in autogen_obj_matches(). featureflagcrit is %d", it->featureflagcrit);
                }
                break;
            }
        }

        if (found)
        {
            it->current_obj = obj;
        }
        else
        {
            it->current_index++;
        }
    }

    return it->current_obj;
}

int autogen_obj_list_verify_object_span(autogen_it* it, autogen_obj_list* obj_list)
{
    int ret_code = TRUE;

    /* find first object of that type, regardles of version */
    autogen_obj* obj = autogen_obj_find_in_list(it, obj_list);
    if (obj)
    {
        int satisfactory = FALSE;
        autogen_ver ver_state = INIT_VERSION_ALL;

        ver_state.type  = AUTOGEN_OBJ_VERSION_NONE;
        ver_state.to[0] = 0;
        ver_state.to[1] = 0;
        ver_state.to[2] = 0;

        while (obj && satisfactory == FALSE && ret_code == TRUE)
        {
            /* update version state with next version information */

            /* if this is the first version information, simply
               copy it to the version state 
            */
            if (ver_state.type == AUTOGEN_OBJ_VERSION_NONE)
            {
                autogen_obj_ver_set(&ver_state, obj->ver.from, obj->ver.to);
            }
            /* if the new version information is an interval,
               append to existing version state, if possible
            */
            else 
            {
                /* are there intervals well connected */
                if (ver_state.to[0] == obj->ver.from[0] &&
                    ver_state.to[1] == obj->ver.from[1] &&
                    ver_state.to[2] == obj->ver.from[2])
                {
                    ver_state.to[0] = obj->ver.to[0];
                    ver_state.to[1] = obj->ver.to[1];
                    ver_state.to[2] = obj->ver.to[2];
                }
                /* else there is a hole in the versions */
                else
                {
                    ret_code = FALSE;
                }
            }

            /* check if the current saved version is relevant at all.
               If the version criteria has a lower version limit, any
               version information less than that is irrelevant 
            */
            if (autogen_ver_comp(it->ver->from, ver_state.to) & AUTOGEN_VER_OLDER)
            {
                ver_state.type = AUTOGEN_OBJ_VERSION_NONE;
            }


            /* is the required interval totally covered by the 
               interval of the current object? 
            */
            if ((autogen_ver_comp(it->ver->from, obj->ver.from) & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL)) &&
                (autogen_ver_comp(it->ver->to,   obj->ver.to)   & (AUTOGEN_VER_EQUAL | AUTOGEN_VER_NEWER)))
            {
                satisfactory = TRUE;
            }
            /* is the required interval totally covered by the 
               currently merged interval? 
            */
            else if ((autogen_ver_comp(it->ver->from, ver_state.from) & (AUTOGEN_VER_OLDER | AUTOGEN_VER_EQUAL)) && 
                     (autogen_ver_comp(it->ver->to,   ver_state.to)   & (AUTOGEN_VER_EQUAL | AUTOGEN_VER_NEWER)))
            {
                satisfactory = TRUE;
            }
            /* can the required interval be totally covered at all ?
               this can be determined by comparing the lower 
               interval boundaries 
            */
            else if (autogen_ver_comp(it->ver->from, ver_state.from) & AUTOGEN_VER_NEWER)
            {
                ret_code = FALSE;
            }

            /* find the next version information */
            obj = autogen_obj_find_next_in_list(it);
        }

        /* no, we are not satisfied */
        if (!satisfactory)
        {
            ret_code = FALSE;
        }
    }
    /* no versions of the object was found at all */
    else
    {
        ret_code = FALSE;
    }

    return ret_code;
}

autogen_obj* autogen_obj_get_first_in_list(autogen_obj_list* obj_list)
{
    autogen_obj* obj = NULL;

    if (obj_list && obj_list->n_obj)
    {
        return obj_list->obj_list[0];
    }

    return obj;
}

autogen_obj** autogen_obj_list_get_sorted_list(autogen_obj_list* obj_list, unsigned int map_type)
{
    return obj_list->map[map_type];
}

unsigned int autogen_obj_count_in_list(autogen_it* it, autogen_obj_list* obj_list)
{
    unsigned int count = 0;

    autogen_obj* obj = autogen_obj_find_in_list(it, obj_list);
    while (obj)
    {
        ++count;

        obj = autogen_obj_find_next_in_list(it);
    }

    return count;
}

void autogen_obj_list_delete_obj(autogen_obj_list* obj_list, autogen_obj* obj)
{
    autogen_obj* obj_it = NULL;
    int index = 0;

    if (!obj_list || !obj || obj_list->n_obj == 0) return;

    obj_it = obj_list->obj_list[0];

    while (index < obj_list->n_obj && obj_list->obj_list[index] != obj)
    {
        index++;
    }

    /* found? Then remove from list */
    if (index < obj_list->n_obj)
    {
        int n;

        /* Update next pointer */
        if (index > 0)
        {
            obj_list->obj_list[index-1]->next = obj->next;
        }

        /* Remove object */
        memmove(&obj_list->obj_list[index], &obj_list->obj_list[index+1], sizeof(autogen_obj*)*(obj_list->n_obj - index));

        /* Remove from sorted lists */
        for (n = 0; n < AUTOGEN_OBJ_LIST_SORT_TYPES; n ++)
        {
            if (obj_list->flag & (1 << n))
            {
                index = 0;

                while (index < obj_list->n_obj && obj_list->map[n][index] != obj)
                {
                    index++;
                }

                /* Remove object */
                memmove(&obj_list->map[n][index], &obj_list->map[n][index+1], sizeof(autogen_obj*)*(obj_list->n_obj - index));
            }
        }

        obj_list->n_obj--;
    }


}


/* End of file autogen_object.c */
