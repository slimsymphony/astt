/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_pmd_msg.c
                ----------------
                SW Module






Project:          autogen

%name:            output_pmd_msg.c %
%version:         co1tss#36 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Wed Nov 18 13:54:56 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the part of the source code for the PMD output generator that generates and
    writes message related objects (such as OS task info)
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_object.h"
#include "autogen_prop.h"
#include "autogen_util.h"

#include "pmdconstants.h"
#include "pmd_compression2.h"
#include "pmd_stringpool.h"
#include "pmd_heap.h"

#include "output_pmd.h"


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL
#endif /* LOCAL */

LOCAL void              pmd_msgent_write(pmd_env* env, pmd_msgent* msgent);
LOCAL void              pmd_msggrp_write(pmd_env* env, pmd_msggrp* msggrp, unsigned int flags);

LOCAL unsigned short    pmd_msg_set_function(unsigned int flags);
LOCAL void              pmd_msg_write(pmd_env* env, pmd_msg* msg, unsigned int flags);


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

LOCAL void pmd_msgent_write(pmd_env* env, pmd_msgent* msgent)
{
    /* Write named object */
    pmd_namedobj_write(env, &msgent->namedobj);

    /* Write logical name */
    pmd_write_string(env, msgent->logical_name);

    /* Write ID */
#if (PMD_FILE_FORMAT >= 600)
    pmd_write_dword(env, (unsigned int)msgent->id);
#else
    pmd_write_dword(env, msgent->id);
#endif

    /* Write trace identifier */
    pmd_write_string(env, msgent->identifier);

    /* Write trace groups */
    pmd_write_dword(env, msgent->n_trace_groups);

    if (msgent->n_trace_groups > 0)
    {
        pmd_msggrp* grp_it = msgent->trace_groups;
        while (grp_it)
        {
            pmd_msggrp_write(env, grp_it, PMD_WRITE_MSG_DATA | PMD_WRITE_COUNTERS);

            grp_it = grp_it->next;
        }
    }

    /* Write messages */
    pmd_write_dword(env, msgent->n_messages);

    if (msgent->n_messages > 0)
    {
        pmd_msg* msg_it = msgent->messages;
        while (msg_it)
        {
            pmd_msg_write(env, msg_it, PMD_WRITE_MSG_DATA | PMD_WRITE_COUNTERS);

            msg_it = msg_it->next;
        }
    }

    /* Write type representing group in PMD model */
    if (msgent->ref_type)
    {
        pmd_write_objid(env, &msgent->ref_type->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }
}

LOCAL void pmd_msggrp_write(pmd_env* env, pmd_msggrp* msggrp, unsigned int flags)
{
    /* Write named object */
    pmd_namedobj_write(env, &msggrp->namedobj);

    /* Write ID */
#if (PMD_FILE_FORMAT >= 600)
    pmd_write_dword(env, (unsigned int)msggrp->id);
#else
    pmd_write_dword(env, msggrp->id);
#endif

    /* Write trace identifier */
    pmd_write_string(env, msggrp->identifier);

    /* Write messages */
    pmd_write_dword(env, msggrp->n_messages);

    if (msggrp->n_messages > 0)
    {
        pmd_msg* msg_trav = msggrp->messages;
        while (msg_trav)
        {
            pmd_msg_write(env, msg_trav, flags);

            msg_trav = msg_trav->next;
        }
    }

    /* Write logical name */
    pmd_write_string(env, msggrp->logical_name);

    /* Write resource specific info */
    if (msggrp->type == PMD_CLASS_RESOURCE)
    {
        unsigned int object_id = 0;
        char str_ver[10] = "";

        /* Write resource interface version */
        if (msggrp->res->base.ver.type != AUTOGEN_OBJ_VERSION_ALL)
        {
            sprintf(str_ver, "%03hu.%03hu", msggrp->res->base.ver.from[0], msggrp->res->base.ver.from[1]);
        }

        pmd_write_string(env, str_ver);

        /* Write default PhoNet object ID */
        if (prop_has_value((autogen_obj*)msggrp->res, PROPERTY_PMD_PHONET_OBJECT_ID))
        {
            object_id = (unsigned int)prop_get_value((autogen_obj*)msggrp->res, PROPERTY_PMD_PHONET_OBJECT_ID);
        }
        else if (prop_has_valid_string((autogen_obj*)msggrp->res, PROPERTY_PMD_PHONET_OBJECT_ID))
        {
            autogen_tbl* tbl;
            autogen_it tbl_it = INIT_ITERATOR;

            tbl_it.typemask    = AUTOGEN_OBJ_TBL;
            tbl_it.subtypemask = AUTOGEN_TBL_CONST;
            tbl_it.obj.name    = "SYMBOLS_PN_OBJECT";

            tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &util_get_unique_res(RESOURCE_SYMBOLS)->tbl_list);
            if (tbl)
            {
                autogen_obj* entry;
                autogen_it entry_it = INIT_ITERATOR;

                entry_it.obj.name = prop_get_string((autogen_obj*)msggrp->res, PROPERTY_PMD_PHONET_OBJECT_ID);

                entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
                if (entry)
                {
                    object_id = (unsigned int)entry->id;
                }
            }
        }
        pmd_write_word(env, object_id);

    }

    /* Write type representing group in PMD model */
    if (msggrp->ref_type)
    {
        pmd_write_objid(env, &msggrp->ref_type->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }
}

LOCAL unsigned short pmd_msg_set_function(unsigned int flags)
{
    unsigned short function = PMD_FUNCTION_UNKNOWN;

    if (flags & AUTOGEN_MSG_REQ)
    {
        function = PMD_FUNCTION_REQUEST;
    }
    else if (flags & AUTOGEN_MSG_RESP)
    {
        function = PMD_FUNCTION_RESPONSE;
    }
    else if (flags & AUTOGEN_MSG_IND)
    {
        function = PMD_FUNCTION_INDICATION;
    }
    else if (flags & AUTOGEN_MSG_NTF)
    {
        function = PMD_FUNCTION_NOTIFICATION;
    }

    return function;
}

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* ================================================================================================ */
/* Message type functions */
/* ================================================================================================ */

#if (PMD_FILE_FORMAT >= 600)
pmd_msgtype* pmd_msgtype_create(pmd_env* env, unsigned short device_id, unsigned long long id, const char* name, const char* identifier, unsigned int flags)
#else
pmd_msgtype* pmd_msgtype_create(pmd_env* env, unsigned short device_id, unsigned int id, const char* name, const char* identifier, unsigned int flags)
#endif
{
    pmd_msgtype* obj = pmd_msgtype_find(env, device_id, id);
    if (!obj)
    {
        /* Allocate new object */
        obj = (pmd_msgtype*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_msgtype));

        /* Initialize new object */
        pmd_namedobj_init(env, &obj->namedobj, name, FALSE, PMD_CLASS_NULL, 0);
        obj->namedobj.managedobj.flags = flags;

        obj->id         = id;
        obj->identifier = pmd_heap_strdup_h(env->heap_handle, identifier);

        obj->message_groups_res   = NULL;
        obj->n_message_groups_res = 0;

        obj->message_groups_trc   = NULL;
        obj->n_message_groups_trc = 0;

        obj->messages             = NULL;
        obj->n_messages           = 0;

        obj->ref_type             = NULL;
    }

    return obj;
}

void pmd_msgtype_insert_in_device(pmd_env* env, unsigned short device_id, pmd_msgtype* msgtype)
{
    /* Insert object in list */
    pmd_device* device = pmd_device_find(env, device_id);
    if (device)
    {
        msgtype->next    = device->msgtypes;
        device->msgtypes = msgtype;

        ++device->n_msgtypes;
    }
    else
    {
        msgtype->next = env->msgtypes;
        env->msgtypes = msgtype;

        ++env->n_msgtypes;
    }
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msgtype* pmd_msgtype_add(pmd_env* env, unsigned short device_id, unsigned long long id, const char* name, const char* identifier, unsigned int flags)
#else
pmd_msgtype* pmd_msgtype_add(pmd_env* env, unsigned short device_id, unsigned int id, const char* name, const char* identifier, unsigned int flags)
#endif
{
    pmd_msgtype* msgtype = pmd_msgtype_find(env, device_id, id);
    if (!msgtype)
    {
        msgtype = pmd_msgtype_create(env, device_id, id, name, identifier, flags);
        pmd_msgtype_insert_in_device(env, device_id, msgtype);
    }

    return msgtype;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msgtype* pmd_msgtype_find(pmd_env* env, unsigned short device_id, unsigned long long id)
#else
pmd_msgtype* pmd_msgtype_find(pmd_env* env, unsigned short device_id, unsigned int id)
#endif
{
    pmd_msgtype* msgtype;
    pmd_device* device = pmd_device_find(env, device_id);
    if (!device && device_id != PMD_DEVICE_GENERAL)
    {
        device = pmd_device_add_default(env, device_id);
    }

    /* Find message type object */
    msgtype = device ? device->msgtypes : env->msgtypes;

    while (msgtype && msgtype->id != id)
    {
        msgtype = msgtype->next;
    }

    return msgtype;
}

/* ================================================================================================ */
/* Message entity functions */
/* ================================================================================================ */

#if (PMD_FILE_FORMAT >= 600)
pmd_msgent* pmd_msgent_add(pmd_env* env, pmd_msgtype* msgtype, unsigned long long id, const char* name, const char* logical_name, const char* identifier)
#else
pmd_msgent* pmd_msgent_add(pmd_env* env, pmd_msgtype* msgtype, unsigned int id, const char* name, const char* logical_name, const char* identifier)
#endif
{
    pmd_msgent* msgent = pmd_msgent_find(msgtype, id);
    if (!msgent)
    {
        pmd_msgent* msgent_it   = msgtype->message_entities;
        pmd_msgent* msgent_last = NULL;

        /* Allocate new object */
        msgent = (pmd_msgent*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_msgent));

        /* Initialize new object */
        pmd_namedobj_init(env, &msgent->namedobj, name, FALSE, PMD_CLASS_MESSAGE_ENTITY, 0);

        msgent->msgtype = msgtype;
        msgent->logical_name = logical_name;

        msgent->id         = id;
        msgent->identifier = identifier;

        msgent->trace_groups   = NULL;
        msgent->n_trace_groups = 0;

        msgent->ref_type = NULL;

        /* Insert object in message type */
        while (msgent_it && msgent_it->id < msgent->id)
        {
            msgent_last = msgent_it;
            msgent_it   = msgent_it->next;
        }

        if (msgent_last)
        {
            msgent->next      = msgent_last->next;
            msgent_last->next = msgent;
        }
        else
        {
            msgent->next              = msgtype->message_entities;
            msgtype->message_entities = msgent;
        }

        ++msgtype->n_message_entitites;
    }

    return msgent;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msgent* pmd_msgent_find(pmd_msgtype* msgtype, unsigned long long id)
#else
pmd_msgent* pmd_msgent_find(pmd_msgtype* msgtype, unsigned int id)
#endif
{
    /* Find message entity object */
    pmd_msgent* msgent = msgtype->message_entities;

    while (msgent && msgent->id != id)
    {
        msgent = msgent->next;
    }

    return msgent;
}

/* ================================================================================================ */
/* Message group functions */
/* ================================================================================================ */

#if (PMD_FILE_FORMAT >= 600)
pmd_msggrp* pmd_msggrp_trc_create(pmd_env* env, unsigned long long id, const char* name, const char* identifier, const char* logical_name)
#else
pmd_msggrp* pmd_msggrp_trc_create(pmd_env* env, unsigned int id, const char* name, const char* identifier, const char* logical_name)
#endif
{
    /* Allocate new object */
    pmd_msggrp* msggrp = (pmd_msggrp*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_msggrp));

    /* Initialize new object */
    pmd_namedobj_init(env, &msggrp->namedobj, name, FALSE, PMD_CLASS_NULL, 0);

    msggrp->type         = PMD_CLASS_TRACE_GROUP;

    msggrp->id           = id;
    msggrp->identifier   = identifier;

    msggrp->msgtype      = NULL;
    msggrp->msgent       = NULL;

    msggrp->logical_name = pmd_heap_strdup_h(env->heap_handle, logical_name);
    msggrp->res          = NULL;

    msggrp->messages     = NULL;
    msggrp->n_messages   = 0;
    msggrp->ref_type     = NULL;

    return msggrp;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msggrp* pmd_msggrp_trc_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, unsigned long long id, const char* identifier, const char* name, const char* logical_name)
#else
pmd_msggrp* pmd_msggrp_trc_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, unsigned int id, const char* identifier, const char* name, const char* logical_name)
#endif
{
    pmd_msggrp* msggrp = NULL;
    pmd_msggrp* trcgrp_it = msgtype->message_groups_trc;

    while (trcgrp_it && trcgrp_it->id != id)
    {
        trcgrp_it = trcgrp_it->next;
    }
    if (trcgrp_it)
    {
        return trcgrp_it;
    }

    if (!msggrp)
    {
        pmd_msggrp** trcgrp_trav = NULL;

        /* Allocate new object */
        msggrp = pmd_msggrp_trc_create(env, id, name, identifier, logical_name); 
        msggrp->msgtype = msgtype;

        /* Insert object at end of list */
        trcgrp_trav = &msgtype->message_groups_trc;

        while (*trcgrp_trav && (*trcgrp_trav)->id < id)
        {
            trcgrp_trav = &(*trcgrp_trav)->next;
        }

        msggrp->next = *trcgrp_trav;
        *trcgrp_trav = msggrp;

        ++msgtype->n_message_groups_trc;
    }

    return msggrp;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msggrp* pmd_msggrp_trc_add_to_msgent(pmd_env* env, pmd_msgent* msgent, unsigned long long id, const char* identifier, const char* name, const char* logical_name)
#else
pmd_msggrp* pmd_msggrp_trc_add_to_msgent(pmd_env* env, pmd_msgent* msgent, unsigned int id, const char* identifier, const char* name, const char* logical_name)
#endif
{
    pmd_msggrp* msggrp = NULL;
    pmd_msggrp* trcgrp_it = msgent->trace_groups;

    while (trcgrp_it && trcgrp_it->id != id)
    {
        trcgrp_it = trcgrp_it->next;
    }
    if (trcgrp_it)
    {
        return trcgrp_it;
    }

    if (!msggrp)
    {
        pmd_msggrp** trcgrp_trav = NULL;

        /* Allocate new object */
        msggrp = pmd_msggrp_trc_create(env, id, name, identifier, logical_name); 
        msggrp->msgent = msgent;

        /* Insert object at end of list */
        trcgrp_trav = &msgent->trace_groups;

        while (*trcgrp_trav && (*trcgrp_trav)->id < id)
        {
            trcgrp_trav = &(*trcgrp_trav)->next;
        }

        msggrp->next = *trcgrp_trav;
        *trcgrp_trav = msggrp;

        ++msgent->n_trace_groups;
    }

    return msggrp;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msggrp* pmd_msggrp_res_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, unsigned long long id, const char* name, const char* logical_name, const autogen_res* res)
#else
pmd_msggrp* pmd_msggrp_res_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, unsigned int id, const char* name, const char* logical_name, const autogen_res* res)
#endif
{
    pmd_msggrp* msggrp = pmd_msggrp_res_find_in_msgtype(msgtype, res);
    if (!msggrp)
    {
        msggrp = pmd_msggrp_res_create(env, msgtype, id, name, logical_name, res);

        pmd_msggrp_res_insert_in_msgtype(msgtype, msggrp);
    }

    return msggrp;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msggrp* pmd_msggrp_res_create(pmd_env* env, pmd_msgtype* msgtype, unsigned long long id, const char* name, 
                                  const char* logical_name, const autogen_res* res)
#else
pmd_msggrp* pmd_msggrp_res_create(pmd_env* env, pmd_msgtype* msgtype, unsigned int id, const char* name, 
                                  const char* logical_name, const autogen_res* res)
#endif
{
    pmd_msggrp* obj = pmd_msggrp_res_find_in_msgtype(msgtype, res);
    if (!obj)
    {
        /* Allocate new object */
        obj = (pmd_msggrp*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_msggrp));

        /* Initialize new object */
        pmd_namedobj_init(env, &obj->namedobj, name, FALSE, PMD_CLASS_NULL, 0);

        obj->type         = PMD_CLASS_RESOURCE;

        obj->id             = id;
        obj->identifier     = res->identifier;
        obj->msgtype        = msgtype;
        obj->msgent         = NULL;
        obj->logical_name   = pmd_heap_strdup_h(env->heap_handle, logical_name);
        obj->res            = res;
        obj->messages     = NULL;
        obj->n_messages   = 0;
        obj->ref_type     = NULL;
    }

    return obj;
}

void pmd_msggrp_res_insert_in_msgtype(pmd_msgtype* msgtype, pmd_msggrp* msggrp)
{
    /* Insert object in list */
    msggrp->next                = msgtype->message_groups_res;
    msgtype->message_groups_res = msggrp;

    ++msgtype->n_message_groups_res;
}

pmd_msggrp* pmd_msggrp_res_find_in_msgtype(pmd_msgtype* msgtype, const autogen_res* res)
{
    pmd_msggrp* msggrp = msggrp = msgtype->message_groups_res;
    while (msggrp && msggrp->res != res)
    {
        msggrp = msggrp->next;
    }

    return msggrp;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msg* pmd_msg_add_to_msgent(pmd_env* env, pmd_msgent* msgent, const char* name, unsigned long long id, const pmd_seq* seq)
#else
pmd_msg* pmd_msg_add_to_msgent(pmd_env* env, pmd_msgent* msgent, const char* name, unsigned int id, const pmd_seq* seq)
#endif
{
    /* Allocate new object */
    pmd_msg* obj = (pmd_msg*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_msg));

    /* Initialize new object */
    pmd_namedobj_init(env, &obj->namedobj, name, FALSE, PMD_CLASS_MESSAGE, 0);

    obj->id       = id;
    obj->msgent   = msgent;
    obj->msgtype  = msgent->msgtype;
    obj->msggrp   = NULL;
    obj->ref_seq  = seq;

    obj->function = pmd_msg_set_function((seq && seq->org_seq) ? seq->org_seq->base.flag : 0);

    /* Insert message in message type */
    obj->next = msgent->messages;
    msgent->messages = obj;

    ++msgent->n_messages;

    return obj;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msg* pmd_msg_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, const char* name, unsigned long long id, const pmd_seq* seq)
#else
pmd_msg* pmd_msg_add_to_msgtype(pmd_env* env, pmd_msgtype* msgtype, const char* name, unsigned int id, const pmd_seq* seq)
#endif
{
    /* Allocate new object */
    pmd_msg* obj = (pmd_msg*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_msg));

    /* Initialize new object */
    pmd_namedobj_init(env, &obj->namedobj, name, FALSE, PMD_CLASS_MESSAGE, 0);

    obj->id       = id;
    obj->msgtype  = msgtype;
    obj->msggrp   = NULL;
    obj->ref_seq  = seq;

    obj->function = pmd_msg_set_function((seq && seq->org_seq) ? seq->org_seq->base.flag : 0);

    /* Insert message in message type */
    obj->next = msgtype->messages;
    msgtype->messages = obj;

    ++msgtype->n_messages;

    return obj;
}

#if (PMD_FILE_FORMAT >= 600)
pmd_msg* pmd_msg_add_to_msggrp(pmd_env* env, pmd_msggrp* msggrp, const char* name, unsigned long long id, const pmd_seq* seq)
#else
pmd_msg* pmd_msg_add_to_msggrp(pmd_env* env, pmd_msggrp* msggrp, const char* name, unsigned int id, const pmd_seq* seq)
#endif 
{
    /* Allocate new object */
    pmd_msg* obj = (pmd_msg*)pmd_heap_alloc_h(env->heap_handle, sizeof(pmd_msg));

    /* Initialize new object */
    pmd_namedobj_init(env, &obj->namedobj, name, FALSE, PMD_CLASS_MESSAGE, 0);

    obj->id      = id;
    obj->msgtype = NULL;
    obj->msggrp  = msggrp;
    obj->ref_seq = seq;

    obj->function = pmd_msg_set_function((seq && seq->org_seq) ? seq->org_seq->base.flag : 0);

    /* Insert message in message group */
    obj->next = msggrp->messages;
    msggrp->messages = obj;

    ++msggrp->n_messages;

    return obj;
}

void pmd_msg_write_all(pmd_env* env)
{
    pmd_msgtype* msgtype = env->msgtypes;
    while (msgtype)
    {
        /* Write messages on message type object */
        if (msgtype->n_messages > 0)
        {
            pmd_msg* msg = msgtype->messages;
            while (msg)
            {
                pmd_msg_write(env, msg, PMD_WRITE_MSG_DATA);

                msg = msg->next;
            }
        }

        /* Write messages on message group (resource) objects */
        if (msgtype->n_message_groups_res > 0)
        {
            const pmd_msggrp* msggrp = msgtype->message_groups_res;
            while (msggrp)
            {
                pmd_msg* msg = msggrp->messages;
                while (msg)
                {
                    pmd_msg_write(env, msg, PMD_WRITE_MSG_DATA);

                    msg = msg->next;
                }
                msggrp = msggrp->next;
            }
        }

        /* Write messages on message group (trace) objects */
        if (msgtype->n_message_groups_trc > 0)
        {
            const pmd_msggrp* msggrp = msgtype->message_groups_trc;
            while (msggrp)
            {
                pmd_msg* msg = msggrp->messages;
                while (msg)
                {
                    pmd_msg_write(env, msg, PMD_WRITE_MSG_DATA);

                    msg = msg->next;
                }
                msggrp = msggrp->next;
            }
        }

        msgtype = msgtype->next;
    }
}

LOCAL void pmd_msg_write(pmd_env* env, pmd_msg* msg, unsigned int flags)
{
    if (flags & PMD_WRITE_MSG_OBJECT_IDS)
    {
        pmd_write_objid(env, &msg->namedobj.managedobj);
    }
    else if (flags & PMD_WRITE_MSG_DATA)
    {
        pmd_msg* related_msg[10];
        unsigned int n_related_msg = 0;

        /* write named object */
        pmd_namedobj_write(env, &msg->namedobj);

        /* write message ID */
#if (PMD_FILE_FORMAT >= 600)
        pmd_write_dword(env, (unsigned int)msg->id);
#else
        pmd_write_dword(env, msg->id);
#endif

        /* write message function */
        pmd_write_word(env, msg->function);

        /* write optional identifier */
        if (msg->namedobj.managedobj.flags & PMD_MESSAGE_HAS_IDENTIFIER)
        {
            pmd_write_string(env, msg->identifier);
        }

        /* generate related messages, if request message */
        if (msg->msggrp && msg->function == PMD_FUNCTION_REQUEST)
        {
            autogen_obj* rel_obj;
            autogen_it rel_it = INIT_ITERATOR;

            rel_it.typemask    = AUTOGEN_OBJ_REL;
            rel_it.subtypemask = AUTOGEN_OBJ_MSG;
            rel_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            rel_it.ver         = &msg->ref_seq->org_seq->base.ver;
            rel_it.sort_type   = AUTOGEN_OBJ_LIST_SORT_BY_TYPE_AND_NAME;

            rel_obj = autogen_obj_find_in_list(&rel_it, &msg->ref_seq->org_seq->base.related_obj);
            while (rel_obj)
            {
                autogen_seq* resp_msg = (autogen_seq*)rel_obj->ptr;
                pmd_msggrp* resp_msg_grp = pmd_msggrp_res_find_in_msgtype(msg->msggrp->msgtype, resp_msg->base.res);
                pmd_msg* msg_it = NULL;

                /* If message group (resource) could not be located from response message, try using the
                message group, the request belongs to
                */
                if (!resp_msg_grp)
                {
                    resp_msg_grp = msg->msggrp;
                }

                if (resp_msg_grp)
                {
                    msg_it = resp_msg_grp->messages;
                }
                while (msg_it && msg_it->ref_seq->org_seq != resp_msg)
                {
                    msg_it = msg_it->next;
                }

                /* found??? then add it... */
                if (msg_it && n_related_msg < 10)
                {
                    related_msg[n_related_msg++] = msg_it;
                }

                rel_obj = autogen_obj_find_next_in_list(&rel_it);
            }
        }

        /* write number of related messages */
        pmd_write_dword(env, n_related_msg);

        if (n_related_msg > 0)
        {
            unsigned int n;

            for (n = 0; n < n_related_msg; n++)
            {
                pmd_write_objid(env, &related_msg[n]->namedobj.managedobj);
            }
        }

        /* write constructed type reference */
        if (msg->ref_seq)
        {
            pmd_write_objid(env, &msg->ref_seq->constructed.type.managedobj);
        }
        else
        {
            pmd_write_objid_null(env);
        }
    }
}

void pmd_msgtype_write(pmd_env* env, const pmd_msgtype* msgtype, unsigned int flags)
{
    /* write named object */
    pmd_namedobj_write(env, &msgtype->namedobj);

    /* write ID */
#if (PMD_FILE_FORMAT >= 600)
    pmd_write_dword(env, (unsigned int)msgtype->id);
#else
    pmd_write_dword(env, msgtype->id);
#endif

    /* write identifier */
    pmd_write_string(env, msgtype->identifier);

    /* write messages */
    pmd_write_dword(env, msgtype->n_messages);

    if (msgtype->n_messages > 0)
    {
        pmd_msg* msg_trav = msgtype->messages;
        while (msg_trav)
        {
            pmd_msg_write(env, msg_trav, flags);

            msg_trav = msg_trav->next;
        }
    }

    /* write message groups (resources) */
    pmd_write_dword(env, msgtype->n_message_groups_res);

    if (msgtype->n_message_groups_res > 0)
    {
        pmd_msggrp* grp_trav = msgtype->message_groups_res;
        while (grp_trav)
        {
            pmd_msggrp_write(env, grp_trav, flags);

            grp_trav = grp_trav->next;
        }
    }

    /* write message groups (traces) */
    pmd_write_dword(env, msgtype->n_message_groups_trc);

    if (msgtype->n_message_groups_trc > 0)
    {
        pmd_msggrp* grp_trav = msgtype->message_groups_trc;
        while (grp_trav)
        {
            pmd_msggrp_write(env, grp_trav, flags);

            grp_trav = grp_trav->next;
        }
    }

    /* write message entities */
    pmd_write_dword(env, msgtype->n_message_entitites);

    if (msgtype->message_entities > 0)
    {
        pmd_msgent* ent_it = msgtype->message_entities;
        while (ent_it)
        {
            pmd_msgent_write(env, ent_it);

            ent_it = ent_it->next;
        }
    }

    /* Write type representing message type in PMD model */
    if (msgtype->ref_type)
    {
        pmd_write_objid(env, &msgtype->ref_type->managedobj);
    }
    else
    {
        pmd_write_objid_null(env);
    }
}

void pmd_msgtypes_write_all(pmd_env* env, unsigned int n_msgtypes, const pmd_msgtype* msgtypes, unsigned int flags)
{
	if (flags & PMD_WRITE_COUNTERS)
	{
	    pmd_write_dword(env, n_msgtypes);
	}

    while (msgtypes)
    {
        pmd_msgtype_write(env, msgtypes, flags);

        msgtypes = (const pmd_msgtype*)msgtypes->next;
    }
}


/* End of file output_pmd_msg.c */
