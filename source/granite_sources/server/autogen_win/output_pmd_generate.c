/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_pmd_generate.c
                ---------------------
                SW Module






Project:          autogen

%name:            output_pmd_generate.c %
%version:         128 %
%instance:        co1tss_1 %
%derived_by:      nosterga %
%date_modified:   Mon Jun 07 14:00:12 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the source code for the PMD output generator.
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_ref.h"
#include "autogen_object.h"
#include "autogen_prop.h"
#include "autogen_util.h"

#include "pmdconstants.h"
#include "pmd_compression2.h"
#include "pmd_stringpool.h"
#include "pmd_heap.h"

#include "output_pmd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL
#endif /* LOCAL */

LOCAL pmd_typ*      pmd_generate_array(pmd_env* env, const char* name, const pmd_typ* array_len, const pmd_typ* array_data, pmd_mod* module);

LOCAL pmd_choice*   pmd_generate_choice_forward(pmd_env* env, const char* name, int tag_length, unsigned short tag_offset, pmd_mod* module);

LOCAL void          pmd_generate_data_subblocks(pmd_env* env, autogen_res* res, unsigned int type);

LOCAL void          pmd_generate_ftd_test_data_structure(pmd_env* env, autogen_res* res, pmd_mod* mod, pmd_msg* ref_msg);

LOCAL void          pmd_generate_media_controller_structure(pmd_env* env, autogen_res* res);
LOCAL pmd_choice*   pmd_generate_media_module_specific_structure(pmd_env* env, unsigned int flag_func, autogen_res* res, pmd_mod* mod);

LOCAL pmd_typ*      pmd_generate_message(pmd_env* env, autogen_res* res, pmd_mod* base_mod, autogen_seq* msg, autogen_res* msg_res, pmd_msgtype* msgtype, pmd_msggrp* msggrp);
LOCAL pmd_choice*   pmd_generate_message_direction_selection(pmd_env* env, const char* name, const autogen_res* res, const pmd_choice* msg_sel_req, const pmd_choice* msg_sel_resp, pmd_mod* module);
LOCAL pmd_choice*   pmd_generate_message_selection(pmd_env* env, const char* name, const autogen_res* res, pmd_mod* module);
LOCAL int           pmd_generate_message_structure(pmd_env* env, pmd_choice* msg_sel, unsigned int flag_func, unsigned int flag_all, unsigned int flag_none, autogen_res* res, autogen_res* msg_res, autogen_obj_list* msg_list, pmd_msgtype* msgtype, pmd_msggrp* msg_grp, pmd_mod* res_mod);

LOCAL pmd_typ*      pmd_generate_number_const(pmd_env* env, const char* name, int length, const char* const_name, unsigned int special_type, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_dec(pmd_env* env, int length, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_dec_no_reuse(pmd_env* env, const char* name, int length, unsigned int special_type, pmd_mod* module);
LOCAL void          pmd_generate_number_default_value(pmd_env* env, pmd_number* number, const autogen_obj* obj, const autogen_pres* pres, autogen_res* res);
LOCAL pmd_typ*      pmd_generate_number_from_pres(pmd_env* env, const autogen_obj* obj, const char* name, int length, const autogen_pres* pres, autogen_res* res, unsigned int special_type, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_hex(pmd_env* env, int length, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_hex_tag(pmd_env* env, int length, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_hex_no_reuse(pmd_env* env, const char* name, int length, unsigned int order, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_pn_const(pmd_env* env, const char* name, const char* const_name, unsigned int special_type, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_pn_object(pmd_env* env, const char* name, int length, pmd_typ* dev_typ, unsigned int special_type, pmd_mod* module);

LOCAL pmd_typ*      pmd_generate_number_primary_id(pmd_env* env, autogen_item_value* value, unsigned int special_type, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_range(pmd_env* env, autogen_item* item, pmd_mod* mod);
LOCAL pmd_typ*      pmd_generate_number_secondary_id(pmd_env* env, autogen_item_value* value, unsigned int special_type, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_trace_data_length(pmd_env* env, unsigned int trc_type, int length, unsigned int order, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_trace_group_id(pmd_env* env, unsigned int trc_type, int entity_index, const char* name, unsigned int order, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_trace_id(pmd_env* env, unsigned int trc_type, autogen_trcgrp* trace_group, const char* name, unsigned int order, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_number_transaction_id(pmd_env* env, pmd_mod* module);

LOCAL void          pmd_generate_ost(pmd_env* env);

LOCAL pmd_choice*   pmd_generate_pn_phonet_type_selection(pmd_env* env, const char* name, pmd_typ* def_type, pmd_mod* module);
LOCAL pmd_choice*   pmd_generate_pn_resource_selection(pmd_env* env, const char* name, pmd_mod* module);

LOCAL pmd_number_pres* pmd_generate_presentation_from_table(pmd_env* env, autogen_res* res, unsigned int tbl_mask, const char* tbl_name, unsigned int flag_all, unsigned int flag_any, unsigned int flag_none);

LOCAL int           pmd_generate_resource_extensions(pmd_env *env, pmd_choice* msg_sel, unsigned int flag_func, autogen_res* res, pmd_msggrp* msg_grp, pmd_mod* res_mod);
LOCAL pmd_typ*      pmd_generate_resource_structure(pmd_env* env, autogen_res* res, pmd_msgtype* msgtype);
LOCAL void          pmd_generate_resource_type_structures(pmd_env* env, unsigned int res_type);

LOCAL pmd_seq*      pmd_generate_sequence(pmd_env* env, autogen_res* res, pmd_mod* mod, autogen_seq* seq, pmd_ref* ref_lst, pmd_msg* ref_msg);
LOCAL pmd_ref*      pmd_generate_sequence_element(pmd_env* env, autogen_res* res, pmd_mod* seq_mod, pmd_mod* str_mod, autogen_res* seq_res, pmd_msg* ref_msg, autogen_item* item, autogen_data* data, pmd_ref* ref_lst);
LOCAL pmd_ref*      pmd_generate_sequence_elements(pmd_env* env, autogen_res* res, autogen_obj_list* obj_lst, pmd_mod* seq_mod, pmd_mod* str_mod, autogen_res* seq_res, pmd_msg* ref_msg, autogen_data* data, pmd_ref* ref_lst, int del_ref_lst);
LOCAL pmd_seq*      pmd_generate_sequence_structure(pmd_env* env, autogen_res* res, pmd_mod* mod, autogen_seq* org_seq, const char* name, pmd_msg* ref_msg, autogen_data* data, pmd_ref* ref_lst);

LOCAL void          pmd_generate_sti_trace_structure(pmd_env* env, autogen_res* res);

LOCAL void          pmd_generate_string(pmd_env* env, autogen_item* item, const char* parname, pmd_mod* seq_mod, pmd_ref* ref_lst);

LOCAL pmd_typ*      pmd_generate_subblock_id(pmd_env* env, autogen_item* item, autogen_res* res, pmd_mod* mod);
LOCAL pmd_typ*      pmd_generate_subblock_list(pmd_env* env, autogen_item* item, autogen_res* res, autogen_res* seq_res, pmd_ref* ref_lst, pmd_msg* ref_msg, pmd_mod* mod);

LOCAL pmd_choice*   pmd_generate_submessage_selection(pmd_env* env, const char* name, const autogen_res* res, pmd_mod* module);
LOCAL int           pmd_generate_submessage_structure(pmd_env* env, pmd_choice* submsg_sel, autogen_seq* base_msg, unsigned int flag_func, unsigned int flag_all, unsigned int flag_none, autogen_res* res, autogen_res* msg_res, pmd_msgtype* msgtype, pmd_msggrp* msg_grp, pmd_mod* res_mod);

LOCAL pmd_choice*   pmd_generate_trace_data_selection(pmd_env* env, unsigned int trc_type, const pmd_typ* trcdata_typ, pmd_mod* module);

LOCAL pmd_typ*      pmd_generate_trace_entity_id(pmd_env* env, unsigned int trc_type, unsigned int order, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_trace_group_id(pmd_env* env, unsigned int trc_type, unsigned int order, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_trace_id(pmd_env* env, unsigned int trc_type, unsigned int order, pmd_mod* module);
LOCAL pmd_typ*      pmd_generate_trace_id_from_list(pmd_env* env, const char* name, unsigned int size, autogen_obj_list* trc_list, unsigned int number_special_type);

LOCAL pmd_typ*      pmd_generate_trace_group_structure(pmd_env* env, unsigned int trc_type, pmd_mod* module);

LOCAL void          pmd_generate_trace_structures(pmd_env* env);
LOCAL pmd_typ*      pmd_generate_trace_structure(pmd_env* env, unsigned int trc_type);
LOCAL pmd_typ*      pmd_generate_trace_structure_dsp5(pmd_env* env, autogen_res* res, unsigned int type, int generate_model);
LOCAL void          pmd_generate_trace_structure_masters(pmd_env* env);
LOCAL void          pmd_generate_trace_structure_master_hw(pmd_env* env);

LOCAL pmd_typ*      pmd_generate_trace_structure_xti_masters_links(pmd_env* env, pmd_mod* seq_mod, pmd_ref* ref_lst);


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

LOCAL pmd_typ* pmd_generate_array(pmd_env* env, const char* name, const pmd_typ* array_len, 
                                  const pmd_typ* array_data, pmd_mod* module)
{
    /* create CSequenceOf object */
    pmd_seq_of* seq_of = pmd_seq_of_create(env, name, array_data);

    /* set length to array length */
    pmd_length_init_as_tag(&seq_of->constructed.length_obj, array_len);

    /* add array object to module */
    pmd_typedef_type_add(module, &seq_of->constructed.type);

    return &seq_of->constructed.type;
}

LOCAL pmd_choice* pmd_generate_choice_forward(pmd_env* env, const char* name, int tag_length, 
                                              unsigned short tag_offset, pmd_mod* module)
{
    /* create CChoice object without any default type */
    pmd_choice* choice = pmd_choice_create(env, name, NULL, env->device_id);

    /* create dummy tag and set tag to be placed x bytes after current position*/
    pmd_typ* tag = pmd_generate_number_hex_tag(env, tag_length, module);

    pmd_tag_init(&choice->tag, tag, PMD_BIT_POSITION_AFTER, tag_offset);

    /* NOTE!!! actual elements are added later on */

    /* add choice object to module */
    pmd_typedef_type_add(module, &choice->constructed.type);

    return choice;
}

LOCAL void pmd_generate_data_subblocks(pmd_env* env, autogen_res* res, unsigned int type)
{
    pmd_mod* res_mod = pmd_typedef_module_lookup(pmd_typedef_module_get_name_from_object(&res->base), env->typ_root_module);
    pmd_mod* typ_mod = NULL;

    autogen_it tbl_it = INIT_ITERATOR;
    autogen_tbl* tbl;

    tbl_it.typemask    = AUTOGEN_OBJ_TBL;
    tbl_it.subtypemask = type;
    tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;
    tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
    tbl_it.ver         = &res->base.ver;

    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
    if (tbl)
    {
        autogen_it data_it = INIT_ITERATOR;
        autogen_data* data;

        data_it.flagall  = env->flag_all;
        data_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        data_it.ver      = &res->base.ver;
        data_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_DATA_FTD_IS_INPUT_DATA;

        data = (autogen_data*)autogen_obj_find_in_list(&data_it, &tbl->base.child_list);
        while (data)
        {
            autogen_seq* sb = NULL;
            autogen_it sb_it = INIT_ITERATOR;

            /* Find subblock template */
            sb_it.typemask = AUTOGEN_OBJ_SB_TEMPLATE;
            sb_it.obj.name = data->seqname;
            sb_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

            /* TBS HANDLE SYMBIAN */
            if (type == AUTOGEN_TBL_FTD)
            {
                autogen_res* comm_res = NULL;
                if (res->base.subtype == RESOURCE_ISI_PREFIX)
                {
                    comm_res = util_get_unique_res(RESOURCE_ISI_COMMON_MESSAGES_EXT);
                }
                else
                {
                    comm_res = util_get_unique_res(RESOURCE_ISI_COMMON_MESSAGES);
                }
                if (comm_res)
                {
                    sb = (autogen_seq*)autogen_obj_find_in_list(&sb_it, &comm_res->seq_list);
                }
            }
            else
            {
                sb = (autogen_seq*)autogen_obj_find_in_list(&sb_it, &res->seq_list);
            }

            if (sb)
            {
                if (!typ_mod)
                {
                    typ_mod = pmd_typedef_module_add(env, pmd_typedef_module_get_name_from_object(&data->base), res_mod);
                }

                /* add subblock */
                pmd_generate_sequence_structure(env, res, typ_mod, sb, data->base.name, NULL, data, NULL);
            }

            data = (autogen_data*)autogen_obj_find_next_in_list(&data_it);
        }
    }
}

LOCAL void pmd_generate_ftd_test_data_structure(pmd_env* env, autogen_res* res, pmd_mod* mod, pmd_msg* ref_msg)
{
    pmd_number* ftd_id = pmd_number_create(env, "ftd_data_item", 16, PMD_NUMBER_SPECIAL_TYPE_NONE);

    ftd_id->pres = pmd_generate_presentation_from_table(env, res, AUTOGEN_TBL_FTD, NULL, AUTOGEN_DATA_FTD_IS_INPUT_DATA | env->flag_all, AUTOGEN_OBJ_ANY, 0);

    pmd_typedef_type_add(mod, &ftd_id->primitive.type);
    pmd_seq_el_add(env, mod->seq, "FTD data ID", &ftd_id->primitive.type);

    /* add 16 bit filler */
    {
        pmd_filler_static* filler = pmd_filler_static_create(env, "filler_x", 16);

        pmd_typedef_type_add(mod, &filler->filler.type);
        pmd_seq_el_add(env, mod->seq, "Filler", &filler->filler.type);
    }

    /* add choice */
    {
        pmd_choice* ftd_sel = pmd_choice_create(env, "user_provided_data", pmd_generate_number_hex(env, 32, mod), env->device_id);
        pmd_tag_init(&ftd_sel->tag, &ftd_id->primitive.type, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
        
        pmd_typedef_type_add(mod, &ftd_sel->constructed.type);
        pmd_seq_el_add(env, mod->seq, "Input data", &ftd_sel->constructed.type);
        {
            autogen_tbl* tbl = NULL;
            autogen_data* ftd = NULL;

            /* find constant table definition */
            autogen_it entry_it = INIT_ITERATOR;
            autogen_it tbl_it   = INIT_ITERATOR;

            tbl_it.typemask    = AUTOGEN_OBJ_TBL;
            tbl_it.subtypemask = AUTOGEN_TBL_FTD;
            tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
            tbl_it.ver         = &res->base.ver;

            tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
            if (tbl)
            {
                /* iterate through all entries */
                entry_it.flagall  = AUTOGEN_DATA_FTD_IS_INPUT_DATA | env->flag_all;
                entry_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;
                entry_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                entry_it.ver      = &res->base.ver;

                ftd = (autogen_data*)autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
                while (ftd)
                {
                    pmd_mod* ftd_mod = pmd_typedef_module_add(env, ftd->base.name, mod);

                    ftd_mod->seq = pmd_seq_create(env, ftd->base.name, PMD_SEQUENCE_TYPE_ANONYMOUS);
                   
                    pmd_generate_sequence_elements(env, res, &ftd->base.child_list, ftd_mod, ftd_mod, res, ref_msg, NULL, NULL, TRUE);

                    pmd_choice_el_add_simple(env, ftd_sel, ftd->base.name, ftd->base.id, &ftd_mod->seq->constructed.type);

                    ftd = (autogen_data*)autogen_obj_find_next_in_list(&entry_it);
                }
            }
        }
    }
}

LOCAL void pmd_generate_media_controller_structure(pmd_env* env, autogen_res* res)
{
    autogen_seq* msg;
    autogen_it msg_it = INIT_ITERATOR;

    pmd_mod* res_mod = pmd_typedef_module_lookup(pmd_typedef_module_get_name_from_object(&res->base), env->typ_root_module);
    pmd_typ* media_id = NULL;

    msg_it.typemask = AUTOGEN_OBJ_MSG;
    msg_it.flagall  = AUTOGEN_MSG_IS_MM_SPECIFIC | env->flag_all;
    msg_it.flagnone = AUTOGEN_MSG_HAS_NO_ELEMENTS | AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;
    msg_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
    msg_it.ver      = &res->base.ver;

    msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, &res->msg_list);
    if (msg)
    {
        media_id = pmd_generate_number_hex_tag(env, 8, res_mod);
    }
    while (msg)
    {
        pmd_entry_point* entry_point = NULL;
        pmd_mod* msg_mod = pmd_typedef_module_add(env, msg->base.name, res_mod);

        pmd_choice* media_sel = pmd_choice_create(env, "media_sel", NULL, env->device_id);

        {
            char ep_name[255];
            sprintf(ep_name, "ENTRY_POINT_MEDIA_CONTROLLER_%2.2X", msg->base.id);

            entry_point = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + (unsigned short)msg->base.id, PMD_INFO_TYPE_NONE);

            media_sel->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;

            media_sel->entry_point_name      = "ENTRY_POINT_MEDIA_CONTROLLER";
            media_sel->entry_point_id        = PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + (unsigned short)msg->base.id;
        }

        /* iterate through all media modules and create copy of media controller message to each */
        {
            autogen_res* mm_res;
            autogen_it mm_res_it = INIT_ITERATOR;

            mm_res_it.flagall     = env->flag_all;
            mm_res_it.typemask    = AUTOGEN_OBJ_RES;
            mm_res_it.subtypemask = RESOURCE_MEDIA_MODULE;
            mm_res_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

            mm_res = (autogen_res*)autogen_obj_find_in_list(&mm_res_it, g_res_list);
            if (mm_res)
            {
                pmd_msgtype_add(env, mm_res->device_id, mm_res->conf->msg_type, 
                    pmd_constant_lookup_message_type_name(mm_res->conf->msg_type), 
                    pmd_constant_lookup_message_type_identifier(mm_res->conf->msg_type), 
                    pmd_constant_lookup_message_type_flags(mm_res->conf->msg_type));
            }
            while (mm_res)
            {
                pmd_mod* mm_res_mod = pmd_typedef_module_add(env, pmd_typedef_module_get_name_from_object(&mm_res->base), env->typ_root_module);

                pmd_msgtype* mm_msgtype = pmd_msgtype_add(env, mm_res->device_id, mm_res->conf->msg_type,
                    pmd_constant_lookup_message_type_name(mm_res->conf->msg_type), 
                    pmd_constant_lookup_message_type_identifier(mm_res->conf->msg_type), 
                    pmd_constant_lookup_message_type_flags(mm_res->conf->msg_type));

                pmd_msggrp* mm_msggrp   = pmd_msggrp_res_add_to_msgtype(env, mm_msgtype, mm_res->base.id, mm_res->base.name, mm_res->logical_name, mm_res);

                /* generate message copy */
                pmd_typ* msg_seq = pmd_generate_message(env, mm_res, mm_res_mod, msg, res, mm_msgtype, mm_msggrp);

                /* add message sequence to media selection */
                {
                    unsigned short device_id = mm_res->device_id;
                    if (device_id == AUTOGEN_DEVICE_CURRENT)
                    {
                        device_id = env->device_id;
                    }
#if PMD_FILE_FORMAT >= 501
	                media_sel->device_id = device_id; 
#endif

                    pmd_entry_point_subtree_el_add(env, device_id, entry_point, mm_res->base.name, mm_res->base.id, msg_seq);
                }
                mm_res = (autogen_res*)autogen_obj_find_next_in_list(&mm_res_it);
            }
        }

        pmd_tag_init(&media_sel->tag, media_id, PMD_BIT_POSITION_AFTER, 2);

        /* add media selection object to module */
        pmd_typedef_type_add(msg_mod, &media_sel->constructed.type);

        /* add media selection object to media controller message selection */
        pmd_choice_el_add_simple(env, (pmd_choice*)env->typ_res_entrypoint[res->index], msg->base.name, msg->base.id, &media_sel->constructed.type);

        msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
    }
}

LOCAL pmd_choice* pmd_generate_media_module_specific_structure(pmd_env* env, unsigned int flag_func, autogen_res* res, pmd_mod* mod)
{
    pmd_mod* res_mod = pmd_typedef_module_add(env, pmd_typedef_module_get_name_from_object(&res->base), env->typ_root_module);

    /* create choice object */
    pmd_choice* msg_sel = pmd_choice_create(env, "msg_sel", NULL, env->device_id);

    pmd_typ* msg_id      = pmd_generate_number_hex_tag(env, res->msg_id_size, res_mod);
    pmd_msgtype* msgtype = pmd_msgtype_add(env, res->device_id, res->conf->msg_type,
								pmd_constant_lookup_message_type_name(res->conf->msg_type), 
								pmd_constant_lookup_message_type_identifier(res->conf->msg_type), 
								pmd_constant_lookup_message_type_flags(res->conf->msg_type));
    pmd_msggrp*  msggrp  = pmd_msggrp_res_add_to_msgtype(env, msgtype, res->base.id, res->base.name, res->logical_name, res);

    msggrp->ref_type = &msg_sel->constructed.type;

    pmd_tag_init(&msg_sel->tag, msg_id, PMD_BIT_POSITION_AFTER, (unsigned short)res->msg_id_offset);

    /* generate messages */
    pmd_generate_message_structure(env, msg_sel, flag_func, flag_func, 0, res, res, &res->msg_list, msgtype, msggrp, res_mod);

    /* generate extension messages */
    {
        autogen_res* ext_res;
        autogen_it ext_res_it = INIT_ITERATOR;

        ext_res_it.flagall     = env->flag_all;
        ext_res_it.typemask    = AUTOGEN_OBJ_RES;
        ext_res_it.subtypemask = RESOURCE_MEDIA_MODULE_EXTENSION;
        ext_res_it.idcrit      = AUTOGEN_OBJ_ID_EXACT;
        ext_res_it.obj.id      = res->base.id;
        ext_res_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

        ext_res = (autogen_res*)autogen_obj_find_in_list(&ext_res_it, g_res_list);
        while (ext_res)
        {
            /* generate messages */
            pmd_generate_message_structure(env, msg_sel, flag_func, flag_func, 0, res, ext_res, &ext_res->msg_list, msgtype, msggrp, res_mod);

            ext_res = (autogen_res*)autogen_obj_find_next_in_list(&ext_res_it);
        }
    }

    /* add choice object to module */
    pmd_typedef_type_add(mod, &msg_sel->constructed.type);

    return msg_sel;
}

LOCAL pmd_typ* pmd_generate_message(pmd_env* env, autogen_res* res, pmd_mod* base_mod, autogen_seq* msg, 
                                    autogen_res* msg_res, pmd_msgtype* msgtype, pmd_msggrp* msggrp)
{
    pmd_msg* ref_msg = NULL;
    pmd_mod* msg_mod = NULL;
    pmd_seq* msg_seq = NULL;

    msg_mod = pmd_typedef_module_add(env, msg->base.base_obj->name, base_mod);

    /* if submessage, add message structure */
    if (msg->base.flag & AUTOGEN_MSG_IS_SUBMSG)
    {
        int skip_message = FALSE;

        if (env->file_restriction & AUTOGEN_PMD_FILE_RESTRICTION_NON_RD)
        {
            if (((msg_res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES || msg_res->base.subtype == RESOURCE_ISI_COMMON_MESSAGES_EXT) &&
                (!strcmp(msg->base.name, "COMM_FTD_DATA_RESP") ||
                !strcmp(msg->base.name, "COMM_FTD_TEST_DATA_REQ"))) ||
                ((msg_res->base.subtype == RESOURCE_ISI || msg_res->base.id == PN_RES_TYPE_SOS_FIELD_TEST) &&
                (!strcmp(msg->base.name, "SOS_FTD_ACTIVATE_RESP") ||
                !strcmp(msg->base.name, "SOS_FTD_EXECUTE_REQ"))))
            {
                autogen_it tbl_it = INIT_ITERATOR;
                autogen_tbl* tbl;

                tbl_it.typemask    = AUTOGEN_OBJ_TBL;
                tbl_it.subtypemask = AUTOGEN_TBL_FTD;
                tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                tbl_it.ver         = &res->base.ver;
                tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

                tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
                if (tbl)
                {
                    autogen_it data_it = INIT_ITERATOR;

                    data_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                    data_it.ver      = &res->base.ver;

                    if (!strcmp(msg->base.name, "COMM_FTD_TEST_DATA_REQ"))
                    {
                        data_it.flagall  = AUTOGEN_DATA_FTD_IS_INPUT_DATA | env->flag_all;
                        data_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

                        if (!autogen_obj_find_in_list(&data_it, &tbl->base.child_list))
                        {
                            skip_message = TRUE;
                        }
                    }
                    else if (!strcmp(msg->base.name, "COMM_FTD_DATA_RESP"))
                    {
                        data_it.flagall  = env->flag_all;
                        data_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_DATA_FTD_IS_INPUT_DATA;

                        if (!autogen_obj_find_in_list(&data_it, &tbl->base.child_list))
                        {
                            skip_message = TRUE;
                        }
                    }
                    else if (!strcmp(msg->base.name, "SOS_FTD_EXECUTE_REQ"))
                    {
                        data_it.flagall  = AUTOGEN_DATA_FTD_IS_INPUT_DATA | env->flag_all;
                        data_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

                        if (!autogen_obj_find_in_list(&data_it, &tbl->base.child_list))
                        {
                            skip_message = TRUE;
                        }
                    }
                    else if (!strcmp(msg->base.name, "SOS_FTD_ACTIVATE_RESP"))
                    {
                        data_it.flagall  = env->flag_all;
                        data_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_DATA_FTD_IS_INPUT_DATA;

                        if (!autogen_obj_find_in_list(&data_it, &tbl->base.child_list))
                        {
                            skip_message = TRUE;
                        }
                    }
                }
                else
                {
                    skip_message = TRUE;
                }
            }
        }

        if (!skip_message)
        {
            pmd_mod* submsg_mod = pmd_typedef_module_add(env, msg->base.name, msg_mod);
            submsg_mod->seq = pmd_seq_create(env, submsg_mod->name, PMD_SEQUENCE_TYPE_MESSAGE);
            submsg_mod->seq->org_seq = msg;
            msg_seq = submsg_mod->seq;

            if (msggrp)
            {
                ref_msg = pmd_msg_add_to_msggrp(env, msggrp, util_get_obj_name((autogen_obj*)msg), msg->base.id, msg_seq);
            }
            else
            {
                ref_msg = pmd_msg_add_to_msgtype(env, msgtype, util_get_obj_name((autogen_obj*)msg), msg->base.id, msg_seq);
            }

            /* set message flags */
            if (prop_has(&msg->base, PROPERTY_PMD_MESSAGE_IN_SUMMARY))
            {
                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IN_SUMMARY;
            }
            if (prop_has(&msg->base, PROPERTY_PMD_MESSAGE_IS_CARRIER))
            {
                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IS_CARRIER_MESSAGE;
            }
            if (prop_has_valid_string(&msg->base, PROPERTY_PMD_TRACE_IDENTIFIER))
            {
                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_IDENTIFIER;
                ref_msg->identifier = prop_get_string(&msg->base, PROPERTY_PMD_TRACE_IDENTIFIER);
            }
            /* add all the message elements to that sequence */
            pmd_generate_sequence_elements(env, res, &msg->base.child_list, submsg_mod, submsg_mod, msg_res, ref_msg, NULL, NULL, TRUE);
        }
    }
    /* else if normal message, add message structure */
    else if (msg->base.child_list.n_obj > 0)
    {
        /* add a sequence to the module */
        msg_mod->seq = pmd_seq_create(env, msg_mod->name, PMD_SEQUENCE_TYPE_MESSAGE);
        msg_mod->seq->org_seq = msg;
        msg_seq = msg_mod->seq;

        if (msggrp)
        {
            ref_msg = pmd_msg_add_to_msggrp(env, msggrp, util_get_obj_name((autogen_obj*)msg), msg->base.id, msg_mod->seq);
        }
        else
        {
            ref_msg = pmd_msg_add_to_msgtype(env, msgtype, util_get_obj_name((autogen_obj*)msg), msg->base.id, msg_mod->seq);
        }

        /* set message flags */
        if (prop_has(&msg->base, PROPERTY_PMD_MESSAGE_IN_SUMMARY))
        {
            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IN_SUMMARY;
        }
        if (prop_has(&msg->base, PROPERTY_PMD_MESSAGE_IS_CARRIER))
        {
            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IS_CARRIER_MESSAGE;
        }
        if (prop_has_valid_string(&msg->base, PROPERTY_PMD_TRACE_IDENTIFIER))
        {
            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_IDENTIFIER;
            ref_msg->identifier = prop_get_string(&msg->base, PROPERTY_PMD_TRACE_IDENTIFIER);
        }
        /* add all the message elements to that sequence */
        pmd_generate_sequence_elements(env, res, &msg->base.child_list, msg_mod, msg_mod, msg_res, ref_msg, NULL, NULL, TRUE);
    }

    /* add length information */
    if (msgtype->id == PMD_MESSAGE_TYPE_PHONET_)
    {
        pmd_length_init_as_tag(&msg_mod->seq->constructed.length_obj, env->typ_pn_length);
    }
    else if (msgtype->id == PMD_MESSAGE_TYPE_PROTOCOL)
    {
        const autogen_item* length_item = reference_get_special_item(&msg->ref_handle, PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH);
        if (length_item)
        {
            pmd_tag_init(&msg_seq->constructed.length_obj.tag, msg_seq->length_type, 
                PMD_BIT_POSITION_AFTER, (unsigned short)length_item->offset);

            msg_seq->constructed.length_obj.alg = PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH;

            if (prop_has(&msg_seq->org_seq->base, PROPERTY_MSG_LENGTH_RELATES_TO_DATA_PART_ONLY))
            {
                msg_seq->constructed.length_obj.length = (int)(length_item->offset) + length_item->length/8;
            }
            else
            {
                msg_seq->constructed.length_obj.length = 0;
            }
        }
    }

    return msg_seq ? &msg_seq->constructed.type : NULL;
}

LOCAL pmd_choice* pmd_generate_message_direction_selection(pmd_env* env, const char* name, const autogen_res* res,
                                                           const pmd_choice* msg_sel_req, const pmd_choice* msg_sel_resp,
                                                           pmd_mod* module)
{
    /* create CChoice object with default type (response messages) */
    pmd_choice* choice = pmd_choice_create(env, name, &msg_sel_resp->constructed.type, env->device_id);

    /* set tag to receiver decive in PhoNet header */
    pmd_tag_init(&choice->tag, env->typ_pn_receiver_device, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

    /* add single choice element for request messages */
    pmd_choice_el_add_simple(env, choice, 
        prop_get_string(&res->base, PROPERTY_PMD_PHONET_DEVICE_ID),
        prop_get_value(&res->base, PROPERTY_PMD_PHONET_DEVICE_ID),
        &msg_sel_req->constructed.type);

    /* add choice object to module */
    pmd_typedef_type_add(module, &choice->constructed.type);

    return choice;
}

LOCAL pmd_choice* pmd_generate_message_selection(pmd_env* env, const char* name, const autogen_res* res, pmd_mod* module)
{
    /* generate message ID tag dummy */
    pmd_typ* msg_id = pmd_generate_number_hex_tag(env, res->msg_id_size, module);

    /* create CChoice object without default type */
    pmd_choice* choice = pmd_choice_create(env, name, NULL, env->device_id);

    /* set tag to dummy message ID at defined relative position */
    pmd_tag_init(&choice->tag, msg_id, PMD_BIT_POSITION_AFTER, (unsigned short)res->msg_id_offset);

    /* add choice object to module */
    pmd_typedef_type_add(module, &choice->constructed.type);

    return choice;
}

LOCAL int pmd_generate_message_structure(pmd_env* env, pmd_choice* msg_sel, 
                                         unsigned int flag_func, unsigned int flag_all, unsigned int flag_none,
                                         autogen_res* res, autogen_res* msg_res, autogen_obj_list* msg_list, 
                                         pmd_msgtype* msgtype, pmd_msggrp* msggrp, pmd_mod* res_mod)
{
    int has_msg = FALSE;

    autogen_seq* msg;
    autogen_it msg_it = INIT_ITERATOR;

    msg_it.typemask = AUTOGEN_OBJ_MSG | AUTOGEN_OBJ_MSG_BASE;
    msg_it.flagall  = flag_all | env->flag_all;
    msg_it.flagany  = flag_func;
    msg_it.flagnone = AUTOGEN_MSG_HAS_NO_ELEMENTS | AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_MSG_IS_SUBMSG | flag_none;
    msg_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
    msg_it.ver      = &msg_res->base.ver;

    msg = (autogen_seq*)autogen_obj_find_in_list(&msg_it, msg_list);
    while (msg)
    {
        /* change message type in case flag AUTOGEN_MSG_TRC_STI is set */
        pmd_msgtype* new_msgtype = msgtype;
        pmd_msggrp*  new_msggrp  = msggrp;

        if (msg->base.flag & AUTOGEN_MSG_TRC_STI)
        {
            const autogen_res_conf* sti_trc_conf = util_get_res_conf(RESOURCE_TRC_STI);
            if (sti_trc_conf)
            {
                new_msgtype = pmd_msgtype_add(env, msg_res->device_id, sti_trc_conf->msg_type, 
                    pmd_constant_lookup_message_type_name(sti_trc_conf->msg_type), 
                    pmd_constant_lookup_message_type_identifier(sti_trc_conf->msg_type), 
                    pmd_constant_lookup_message_type_flags(sti_trc_conf->msg_type));
                new_msggrp  = NULL;
            }
        }

        /* if message is a base for a submessage, 
           generate whole submessage structure for that message ID
        */
        if (msg->base.type == AUTOGEN_OBJ_MSG_BASE)
        {
            pmd_choice* submsg_sel = NULL;
            char sel_name[AUTOGEN_MAX_NAME_LENGTH + 20];
            sprintf(sel_name, "submsg_sel_%s", msg->base.name);

            if (prop_has(&res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
            {
                if (msg->base.flag & AUTOGEN_MSG_REQ)
                {
                    strcat(sel_name, "_req");
                }
                else
                {
                    strcat(sel_name, "_resp");
                }
            }

            submsg_sel = pmd_generate_submessage_selection(env, sel_name, msg_res, res_mod);
            if (submsg_sel)
            {
                if (pmd_generate_submessage_structure(env, submsg_sel, msg, 
                        flag_func, flag_all, flag_none, res, msg_res, new_msgtype, new_msggrp, res_mod))
                {
                    /* add submessage selection to main message selection */
                    pmd_choice_el_add_simple(env, msg_sel, msg->base.base_obj->name, msg->base.base_obj->id, 
                        &submsg_sel->constructed.type);

                    has_msg = TRUE;
                }
            }
        }
        /* else generate single message and add to message selection */
        else
        {
            pmd_typ* msg_seq = pmd_generate_message(env, res, res_mod, msg, msg_res, new_msgtype, new_msggrp);
            if (msg_seq)
            {
                /* add the message to the message selection */
                pmd_choice_el_add_simple(env, msg_sel, msg->base.name, msg->base.id, msg_seq);

                has_msg = TRUE;
            }
        }

        msg = (autogen_seq*)autogen_obj_find_next_in_list(&msg_it);
    }

    return has_msg;
}

LOCAL pmd_typ* pmd_generate_number_const(pmd_env* env, const char* name, int length, 
                                         const char* const_name, unsigned int special_type, pmd_mod* module)
{
    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, name, length, special_type);

    /* create constant presentation object */
    number->pres = pmd_number_pres_const_create(env, const_name);

    /* add object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

/* Generate a number type with decimal presentation. Try to reuse object */
LOCAL pmd_typ* pmd_generate_number_dec(pmd_env* env, int length, pmd_mod* module)
{
    if (!env->typ_value_dec[length-1])
    {
        pmd_number* number = NULL;
        char name[20];
        sprintf(name, "dec_%d", length);

        /* create CNumberType object */
        number = pmd_number_create(env, name, length, PMD_NUMBER_SPECIAL_TYPE_NONE);

        /* set presentation type CNumberPresentationSimple (DEC) */
        number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_DEC, "");

        /* add type object to module */
        pmd_typedef_type_add(module, &number->primitive.type);

        /* save type for later reuse */
        env->typ_value_dec[length-1] = &number->primitive.type;
    }

    return env->typ_value_dec[length-1];
}

/* Generate a number type with decimal presentation. No reuse of objects */
LOCAL pmd_typ* pmd_generate_number_dec_no_reuse(pmd_env* env, const char* name, int length, 
                                                unsigned int special_type, pmd_mod* module)
{
    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, name, length, special_type);

    /* set presentation type CNumberPresentationSimple (DEC) */
    number->pres= pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_DEC, "");

    /* add type object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

LOCAL void pmd_generate_number_default_value(pmd_env* env, pmd_number* number, const autogen_obj* obj, 
                                             const autogen_pres* pres, autogen_res* res)
{
    int has_default = FALSE;

    /* default value as strng defined */
    if (prop_has_valid_string(obj, PROPERTY_ITEM_DEFAULT_VALUE))
    {
        autogen_it tbl_it = INIT_ITERATOR;
        autogen_tbl* tbl;
        autogen_it entry_it = INIT_ITERATOR;
        autogen_obj* entry = NULL;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST_ANY;
        tbl_it.obj.name    = pres->tblname;
        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.ver         = &res->base.ver;
        tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
        tbl = util_get_parent_table(tbl, &res->base.ver);

        if (tbl)
        {
            entry_it.obj.name = prop_get_string(obj, PROPERTY_ITEM_DEFAULT_VALUE);

            entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
        }
        if (entry)
        {
            pmd_number_set_default_value(env, number, entry->id, entry->name);

            has_default = TRUE;
        }
    }
    /* default value as value defined */
    if (!has_default && prop_has_value(obj, PROPERTY_ITEM_DEFAULT_VALUE))
    {
        char default_value_str[30] = "";
#if (PMD_FILE_FORMAT >= 600)
        unsigned long long default_value = prop_get_value(obj, PROPERTY_ITEM_DEFAULT_VALUE);
#else
        unsigned int default_value = prop_get_value(obj, PROPERTY_ITEM_DEFAULT_VALUE);
#endif

        if (number->primitive.type.managedobj.flags & PMD_NUMBER_IS_SIGNED)
        {
#if (PMD_FILE_FORMAT >= 600)
            sprintf(default_value_str, "%lld", (long long)default_value);
#else
            sprintf(default_value_str, "%d", (int)default_value);
#endif
        }
        else
        {
#if (PMD_FILE_FORMAT >= 600)
            sprintf(default_value_str, "%llu", default_value);
#else
            sprintf(default_value_str, "%u", default_value);
#endif
        }

        pmd_number_set_default_value(env, number, default_value, default_value_str);
    }
}

LOCAL pmd_typ* pmd_generate_number_from_pres(pmd_env* env, const autogen_obj* obj, const char* name, int length, 
                                             const autogen_pres* pres, autogen_res* res, 
                                             unsigned int special_type, pmd_mod* module)
{
    /* create CNumberType object */
    pmd_number_pres* actual_pres = NULL;
    pmd_number_pres_cond* exceptional_pres_cond = NULL;
    pmd_number* number;
    
    if (obj && obj->type == AUTOGEN_OBJ_DATA)
    {
        number = pmd_number_create(env, name, ((autogen_data*)obj)->length, special_type);
    }
    else
    {
        number = pmd_number_create(env, name, length, special_type);
    }


    /* generate default value and set on number */
    pmd_generate_number_default_value(env, number, obj, pres, res);

    /* create presentation based autogen presentation object */
    if (pres->type & AUTOGEN_PRESENTATION_CONST_ANY)
    {
        actual_pres = pmd_generate_presentation_from_table(env, pres->tblres, AUTOGEN_TBL_CONST_ANY, pres->tblname, 0, AUTOGEN_OBJ_ANY, 0);
    }
    else if (pres->type & AUTOGEN_PRESENTATION_LINEAR)
    {
        actual_pres = pmd_number_pres_trans_create(env, pres->scale, pres->offset, pres->unit);
    }
    else if (pres->type & AUTOGEN_PRESENTATION_QN)
    {
        double scale = 1.0f / pow(2, pres->subtype);

        actual_pres = pmd_number_pres_trans_create(env, scale, pres->offset, pres->unit);
    }
    else if (pres->type & (AUTOGEN_PRESENTATION_SIMPLE | AUTOGEN_PRESENTATION_HEX | AUTOGEN_PRESENTATION_BIN))
    {
        unsigned int radix = PMD_VALUE_PRESENTATION_HEX;
        
        if (pres->type & AUTOGEN_PRESENTATION_DEC)
            {
            radix = PMD_VALUE_PRESENTATION_DEC;
            }
        else 
        if (pres->type & AUTOGEN_PRESENTATION_BIN)
            {
            radix = PMD_VALUE_PRESENTATION_BIN;
            }

        actual_pres = pmd_number_pres_simple_create(env, radix, pres->unit);
    }
    else if (pres->type & AUTOGEN_PRESENTATION_FTDID)
    {
        actual_pres = pmd_generate_presentation_from_table(env, res, AUTOGEN_TBL_FTD, NULL, env->flag_all, AUTOGEN_OBJ_ANY, AUTOGEN_DATA_FTD_IS_INPUT_DATA);
    }
    else if (pres->type & AUTOGEN_PRESENTATION_PPCID)
    {
        actual_pres = pmd_generate_presentation_from_table(env, res, AUTOGEN_TBL_PPC, NULL, env->flag_all, AUTOGEN_OBJ_ANY, 0);
    }
    else
    {
        actual_pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, NULL);
    }

    /* create exceptional values and limits condition */
    if (obj && obj->type == AUTOGEN_OBJ_ITEM)
        {
        /* Retrieve interval limits, if any */
        const autogen_prop* minprop = prop_find_first(obj, PROPERTY_ITEM_MINIMUM_VALUE);
        const autogen_prop* maxprop = prop_find_first(obj, PROPERTY_ITEM_MAXIMUM_VALUE);

        /* Create exceptional value presentations */
        const autogen_prop* exprop = prop_find_first(obj, PROPERTY_ITEM_EXCEPTIONAL_VALUE);
        if (exprop)
        {
            exceptional_pres_cond = pmd_number_pres_cond_create(env, NULL);
        }
        while (exprop)
        {
#if (PMD_FILE_FORMAT >= 600)
            pmd_number_pres_cond_el_add_simple(env, exceptional_pres_cond, (long long)exprop->value, exprop->str);
#else
            pmd_number_pres_cond_el_add_simple(env, exceptional_pres_cond, (int)exprop->value, exprop->str);
#endif
            exprop = prop_find_next(exprop);
        }

        /* generate an interval for the limits */
        if (minprop || maxprop)
        {
            pmd_cond_el* limits_cond_el = NULL;
            pmd_number_pres_cond_el* limits_pres_cond_el = NULL;

#if (PMD_FILE_FORMAT >= 600)
            unsigned long long minval = 0LL;
            unsigned long long maxval = 0LL;
#else
            unsigned int minval = 0;
            unsigned int maxval = 0;
#endif
        
            char maxvalstr[2*AUTOGEN_MAX_NAME_LENGTH] = "";
            char minvalstr[2*AUTOGEN_MAX_NAME_LENGTH] = "";

            util_get_item_limits((const autogen_item*)obj, &minval, &maxval, minvalstr, maxvalstr);
        
            if (minprop)
            {
                minval = minprop->value;
            }
            if (maxprop)
            {
                maxval = maxprop->value;
            }

#if (PMD_FILE_FORMAT >= 600)
            limits_cond_el = pmd_cond_el_int_create(env, (long long)minval, (long long)maxval);
#else
            limits_cond_el = pmd_cond_el_int_create(env, (int)minval, (int)maxval);
#endif
            limits_pres_cond_el = pmd_number_pres_cond_el_create(env, limits_cond_el, actual_pres);
            actual_pres = NULL;

            if (!exceptional_pres_cond)
            {
                exceptional_pres_cond = pmd_number_pres_cond_create(env, NULL);
            }

            pmd_number_pres_cond_el_add(exceptional_pres_cond, limits_pres_cond_el);
        }
        else if (exceptional_pres_cond)
        {
            exceptional_pres_cond->default_pres = actual_pres;
            actual_pres = NULL;
        }
    }

    /* set presentation on number */
    if (exceptional_pres_cond)
    {
        number->pres = &exceptional_pres_cond->number_pres;
    }
    else
    {
        number->pres = actual_pres;
    }

    /* add object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

/* Generate a number type with hex presentation. Try to reuse object */
LOCAL pmd_typ* pmd_generate_number_hex(pmd_env* env, int length, pmd_mod* module)
{
    if (!env->typ_value_hex[length-1])
    {
        pmd_number* number = NULL;
        char name[20];
        sprintf(name, "hex_%d", length);

        /* create CNumberType object */
        number = pmd_number_create(env, name, length, PMD_NUMBER_SPECIAL_TYPE_NONE);

        /* set presentation type CNumberPresentationSimple (HEX) */
        number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");

        /* add type object to module */
        pmd_typedef_type_add(module, &number->primitive.type);

        /* save type for later reuse */
        env->typ_value_hex[length-1] = &number->primitive.type;
    }

    return env->typ_value_hex[length-1];
}

/* Generate a number type with hex presentation, which is used as tag. Try to reuse object */
LOCAL pmd_typ* pmd_generate_number_hex_tag(pmd_env* env, int length, pmd_mod* module)
{
    if (!env->typ_value_hex_tag[length-1])
    {
        pmd_number* number = NULL;
        char name[20];
        sprintf(name, "hex_%d_tag", length);

        /* create CNumberType object */
        number = pmd_number_create(env, name, length, PMD_NUMBER_SPECIAL_TYPE_NONE);

        /* set presentation type CNumberPresentationSimple (HEX) */
        number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");

        /* add type object to module */
        pmd_typedef_type_add(module, &number->primitive.type);

        /* save type for later reuse */
        env->typ_value_hex_tag[length-1] = &number->primitive.type;
    }

    return env->typ_value_hex_tag[length-1];
}

/* Generate a number type with hex presentation. No reuse of objects */
LOCAL pmd_typ* pmd_generate_number_hex_no_reuse(pmd_env* env, const char* name, int length, unsigned int order, pmd_mod* module)
{
    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, name, length, PMD_NUMBER_SPECIAL_TYPE_NONE);

    /* set presentation type CNumberPresentationSimple (HEX) */
    number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");

    /* set LE */
    if (order == LE)
    {
        pmd_number_set_data_order_little_endian(number);
    }

    /* add type object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

LOCAL pmd_typ* pmd_generate_number_pn_const(pmd_env* env, const char* name, const char* const_name, 
                                            unsigned int special_type, pmd_mod* module)
{
    char tbl_name[100];

    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, name, 8, special_type);

    /* generate presentation from table */
    sprintf(tbl_name, "SYMBOLS_%s", const_name);

    number->pres = pmd_generate_presentation_from_table(env, util_get_unique_res(RESOURCE_SYMBOLS), AUTOGEN_TBL_CONST_ANY, tbl_name, 0, AUTOGEN_OBJ_ANY, 0);

    /* add object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

LOCAL pmd_typ* pmd_generate_number_pn_object(pmd_env* env, const char* name, int length, pmd_typ* dev_typ, 
                                             unsigned int special_type, pmd_mod* module)
{
    unsigned int dev_length = ((pmd_number*)dev_typ)->length;
    int div = (dev_length == 6) ? 4 : 1;

    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, name, length, special_type);

    /* create conditional presentation, based on device ID. Default presentation is Decimal */
    pmd_number_pres_cond* pres_cond = pmd_number_pres_cond_create(env, pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_DEC, ""));
    pmd_number_pres_cond_set_tag(env, pres_cond, dev_typ);

    /* add presentations for PN_DEV_HOST (MCU) */
    {
        pmd_number_pres* pres_def = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_DEC, "");
        pmd_number_pres* pres = pmd_number_pres_info_create(env, PMD_INFO_TYPE_PN_OBJECTS, PN_DEV_HOST, pres_def);
#if (PMD_FILE_FORMAT >= 600)
        pmd_cond_el* cond_el = pmd_cond_el_int_create(env, (long long)PN_DEV_HOST/div, (long long)PN_DEV_HOST/div);
#else
        pmd_cond_el* cond_el = pmd_cond_el_int_create(env, PN_DEV_HOST/div, PN_DEV_HOST/div);
#endif
        pmd_number_pres_cond_el* pres_cond_el = pmd_number_pres_cond_el_create(env, cond_el, pres);

        /* add the presentation for PN_DEV_HOST */
        pmd_number_pres_cond_el_add(pres_cond, pres_cond_el);
    }

    /* add presentations for PN_DEV_TRACEBOX */
    {
        pmd_number_pres* pres_def = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_DEC, "");
        pmd_number_pres* pres = pmd_number_pres_info_create(env, PMD_INFO_TYPE_PN_OBJECTS, PN_DEV_TRACEBOX, pres_def);
#if (PMD_FILE_FORMAT >= 600)
        pmd_cond_el* cond_el = pmd_cond_el_int_create(env, (long long)PN_DEV_TRACEBOX/div, (long long)PN_DEV_TRACEBOX/div);
#else
        pmd_cond_el* cond_el = pmd_cond_el_int_create(env, PN_DEV_TRACEBOX/div, PN_DEV_TRACEBOX/div);
#endif
        pmd_number_pres_cond_el* pres_cond_el = pmd_number_pres_cond_el_create(env, cond_el, pres);

        /* add the presentation for PN_DEV_TRACEBOX */
        pmd_number_pres_cond_el_add(pres_cond, pres_cond_el);
    }

    /* apply presentation to number */
    number->pres = &pres_cond->number_pres;

    /* add object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

/* Generate message ID / subblock ID / private ID field with constant presentation definining the name */
LOCAL pmd_typ* pmd_generate_number_primary_id(pmd_env* env, autogen_item_value* value, unsigned int special_type, pmd_mod* module)
{
    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, value->base.varname, value->base.length, special_type);

    /* set presentation */
    pmd_number_pres_cond* pres_cond = pmd_number_pres_cond_create(env, NULL);
    pmd_number_pres_cond_el_add_simple(env, pres_cond, value->pres.obj->base_obj->id, value->pres.obj->base_obj->name);

    number->pres = &pres_cond->number_pres;

    /* add type object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

LOCAL pmd_typ* pmd_generate_number_range(pmd_env* env, autogen_item* item, pmd_mod* mod)
{
    /* create number type object */
    pmd_number* number = pmd_number_create(env, item->varname, item->length, PMD_NUMBER_SPECIAL_TYPE_NONE);

    /* create number presentation condition object */
    pmd_number_pres_cond* pres_cond = pmd_number_pres_cond_create(env, NULL);

    autogen_item_range_entry* entry = (autogen_item_range_entry*)autogen_obj_get_first_in_list(&item->base.child_list);
    while (entry)
    {
        /* create condition element */
#if (PMD_FILE_FORMAT >= 600)
        pmd_cond_el* cond_el = pmd_cond_el_int_create(env, (long long)entry->from, (long long)entry->to);
#else
        pmd_cond_el* cond_el = pmd_cond_el_int_create(env, (int)entry->from, (int)entry->to);
#endif

        /* create presentation element */
        pmd_number_pres* pres = NULL;
        if (entry->base.base.flag & AUTOGEN_RANGE_ENTRY_STRING)
        {
            pres = pmd_number_pres_const_create(env, entry->text);
        }
        else if (entry->base.base.flag & AUTOGEN_RANGE_ENTRY_VALUE)
        {
            unsigned int radix = PMD_VALUE_PRESENTATION_HEX;
            
            if (entry->pres.type & AUTOGEN_PRESENTATION_DEC)
            {
                radix = PMD_VALUE_PRESENTATION_DEC;
            }
            else if (entry->pres.type & AUTOGEN_PRESENTATION_BIN)
            {
                radix = PMD_VALUE_PRESENTATION_BIN;
            }

            pres = pmd_number_pres_simple_create(env, radix, entry->pres.unit);
        }
        else if (entry->base.base.flag & AUTOGEN_RANGE_ENTRY_VALUE_EX)
        {
            pres = pmd_number_pres_trans_create(env, entry->pres.scale, entry->pres.offset, entry->pres.unit);
        }

        /* add the presentation conditional element */
        if (pres)
        {
            pmd_number_pres_cond_el_add(pres_cond, pmd_number_pres_cond_el_create(env, cond_el, pres));
        }

        entry = (autogen_item_range_entry*)entry->base.base.next;
    }

    /* set the presentation on the number */
    number->pres = &pres_cond->number_pres;

    /* add the number type object to the module */
    pmd_typedef_type_add(mod, &number->primitive.type);

    return &number->primitive.type;
}

/* Generate submessage ID field with constant presentation definining the name */
LOCAL pmd_typ* pmd_generate_number_secondary_id(pmd_env* env, autogen_item_value* value, unsigned int special_type, pmd_mod* module)
{
    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, value->base.varname, value->base.length, special_type);

    /* set presentation */
    pmd_number_pres_cond* pres_cond = pmd_number_pres_cond_create(env, NULL);
    pmd_number_pres_cond_el_add_simple(env, pres_cond, value->pres.obj->id, value->pres.obj->name);

    number->pres = &pres_cond->number_pres;

    /* add type object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

/* Generate trace data length field. Try reusing object */
LOCAL pmd_typ* pmd_generate_number_trace_data_length(pmd_env* env, unsigned int trc_type, int length, unsigned int order, pmd_mod* module)
{
    trc_type;

    if (!env->typ_trace_data_length)
    {
        /* create CNumberType object */
        pmd_number* number = pmd_number_create(env, PMD_TYPE_NAME_TRACE_DATA_LENGTH, length, PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH);

        /* set order LE */
        if (order == LE)
        {
            pmd_number_set_data_order_little_endian(number);
        }

        /* set presentation type CNumberPresentationSimple (DEC) */
        number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_DEC, "");

        /* add type object to module */
        pmd_typedef_type_add(module, &number->primitive.type);

        /* save type for later use */
        env->typ_trace_data_length = &number->primitive.type;
    }

    return env->typ_trace_data_length;
}

LOCAL pmd_typ* pmd_generate_number_trace_group_id(pmd_env* env, unsigned int trc_type, int entity_index, const char* name, unsigned int order, pmd_mod* module)
{
    pmd_number_pres_cond* pres_cond = NULL;
    autogen_it trcgrp_it = INIT_ITERATOR;
    autogen_obj* trcgrp;

    /* create CNumberType object */
    pmd_number* number = 
        pmd_number_create(env, name, g_trcgrp_conf[trc_type].group_size, g_trcgrp_conf[trc_type].group_special_type);

    /* set order LE */
    if (order == LE)
    {
        pmd_number_set_data_order_little_endian(number);
    }

    /* create CNumberPresentationCondition object with no default presentation */
    pres_cond = pmd_number_pres_cond_create(env, NULL);

    trcgrp_it.typemask = AUTOGEN_OBJ_TRACEGRP;
    trcgrp_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_TRACEGRP_TEMPORARY_GROUP;

    /* add constant presentation for each trace group */
    trcgrp = autogen_obj_find_in_list(&trcgrp_it, g_trcgrp_conf[trc_type].list[entity_index]);
    while (trcgrp)
    {
        pmd_number_pres_cond_el_add_simple(env, pres_cond, trcgrp->id, trcgrp->name);

        trcgrp = autogen_obj_find_next_in_list(&trcgrp_it);
    }

    /* set final presentation on number */
    if (pres_cond->n_pres_cond_el > 0)
    {
        number->pres = &pres_cond->number_pres;
    }
    else
    {
        number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");
    }

    /* add type object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

LOCAL pmd_typ* pmd_generate_number_trace_id(pmd_env* env, unsigned int trc_type, autogen_trcgrp* trace_group, const char* name, unsigned int order, pmd_mod* module)
{
    pmd_number_pres_cond* pres_cond;
    autogen_obj* trc = NULL;
    autogen_it trc_it = INIT_ITERATOR;

    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, name, g_trcgrp_conf[trc_type].id_size, g_trcgrp_conf[trc_type].id_special_type);

    /* set order LE */
    if (order == LE)
    {
        pmd_number_set_data_order_little_endian(number);
    }

    /* create CNumberPresentationCondition object with no default presentation */
    pres_cond = pmd_number_pres_cond_create(env, NULL);

    trc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

    /* add constant presentation for each trace */
    if (trace_group)
    {
        trc = autogen_obj_find_in_list(&trc_it, &trace_group->base.child_list);
    }
    else if (g_trcgrp_conf[trc_type].list)
    {
        trc = autogen_obj_find_in_list(&trc_it, g_trcgrp_conf[trc_type].list[0]);
    }
    while (trc)
    {
        pmd_number_pres_cond_el_add_simple(env, pres_cond, trc->id, trc->name);
    
        trc = autogen_obj_find_next_in_list(&trc_it);
    }

    /* set final presentation on number */
    if (pres_cond->n_pres_cond_el > 0)
    {
        number->pres = &pres_cond->number_pres;
    }
    else
    {
        number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");
    }

    /* add type object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

/* Generate transaction ID field. Try reusing object */
LOCAL pmd_typ* pmd_generate_number_transaction_id(pmd_env* env, pmd_mod* module)
{
    if (!env->typ_transaction_id)
    {
        /* save type for later use */
        env->typ_transaction_id = 
            pmd_generate_number_dec_no_reuse(env, "transaction_id", 8, PMD_NUMBER_SPECIAL_TYPE_TRANSACTION_ID, module);
    }

    return env->typ_transaction_id;
}

/* This selection is needed to separate PhoNet resources from PhoNet/ISI resources
   before the actual resource ID selection.
   Plain PhoNet messages do not have sender/receiver object ID's
*/
LOCAL pmd_choice* pmd_generate_pn_phonet_type_selection(pmd_env* env, const char* name, pmd_typ* def_type, pmd_mod* module)
{
    /* create CChoice object with default type (sequence containg sender/receiver object IS's) */
    pmd_choice* choice = pmd_choice_create(env, name, def_type, env->device_id);

    /* set tag to resource ID in PhoNet header */
    pmd_tag_init(&choice->tag, env->typ_pn_resource, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

    /* add choice object to module */
    pmd_typedef_type_add(module, &choice->constructed.type);

    /* Generate entry point */
    pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_PHONET_RESOURCE, PMD_INFO_TYPE_PN_RESOURCES);

    choice->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;

    choice->entry_point_name = "ENTRY_POINT_PHONET_RESOURCE";
    choice->entry_point_id   = PMD_ENTRY_POINT_PHONET_RESOURCE;

    return choice;
}

/* This type selects the message selections in each resource, based on the resource ID in the PhoNet header
*/
LOCAL pmd_choice* pmd_generate_pn_resource_selection(pmd_env* env, const char* name, pmd_mod* module)
{
    /* create CChoice object without any default type */
    pmd_choice* choice = pmd_choice_create(env, name, NULL, env->device_id);

    /* set tag to resource ID in PhoNet header */
    pmd_tag_init(&choice->tag, env->typ_pn_resource, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

    /* NOTE!!! actual elements (all phonet resources) are added later on */
    
    /* add choice object to module */
    pmd_typedef_type_add(module, &choice->constructed.type);

    /* Generate entry point */
    pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_PN_RESOURCE, PMD_INFO_TYPE_PN_RESOURCES);

    choice->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;

    choice->entry_point_name = "ENTRY_POINT_PN_RESOURCE";
    choice->entry_point_id   = PMD_ENTRY_POINT_PN_RESOURCE;

    return choice;
}


LOCAL pmd_number_pres* pmd_generate_presentation_from_table(pmd_env* env, autogen_res* res, 
                                                            unsigned int tbl_mask, const char* tbl_name, 
                                                            unsigned int flag_all, unsigned int flag_any, unsigned int flag_none)
{
    pmd_number_pres* pres = NULL;

    if (res == util_get_unique_res(RESOURCE_SYMBOLS))
    {
        const autogen_symbol_conf* p_sym_conf = util_get_sym_conf_by_tblname(tbl_name);
        if (p_sym_conf && p_sym_conf->pmd_info_type != PMD_INFO_TYPE_NONE)
        {
            if ((p_sym_conf->pmd_flag & env->flag_all) == env->flag_all)
            {
                unsigned short device_id = p_sym_conf->device_id;
                if (device_id == AUTOGEN_DEVICE_CURRENT)
                {
                    device_id = env->device_id;
                }
				pres = pmd_number_pres_info_create(env, p_sym_conf->pmd_info_type, device_id, NULL);

                if (p_sym_conf->pmd_info_type == PMD_INFO_TYPE_PN_OBJECTS ||
                    p_sym_conf->pmd_info_type == PMD_INFO_TYPE_PN_OBJECTS_HOST ||
                    p_sym_conf->pmd_info_type == PMD_INFO_TYPE_PN_OBJECTS_TRACEBOX)
                {
                    ((pmd_number_pres_info*)pres)->default_pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_DEC, "");
                }
            }
            else
            {
                pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, NULL);
            }
        }
    }

    if (!pres)
    {
        /* create presentation condition object */
        pmd_number_pres_cond* pres_cond = pmd_number_pres_cond_create(env, NULL);

        autogen_tbl* tbl = NULL;
        autogen_tbl* org_tbl = NULL;

        /* find constant table definition */
        autogen_it entry_it = INIT_ITERATOR;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = tbl_mask;
        tbl_it.obj.name    = tbl_name;
        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.ver         = &res->base.ver;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);

        /* Find correct version of parent table (for looking up values) */
        org_tbl = util_get_parent_table(tbl, &res->base.ver);
        
        if (org_tbl)
        {
            autogen_obj* entry = NULL;
            autogen_obj* org_entry = NULL;

            autogen_it org_entry_it = INIT_ITERATOR;

            org_entry_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            org_entry_it.ver      = &res->base.ver;
            org_entry_it.flagall  = flag_all;
            org_entry_it.flagany  = flag_any;
            org_entry_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | flag_none;

            /* iterate through all entries in table */
            entry_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            entry_it.ver      = &res->base.ver;
            entry_it.flagall  = flag_all;
            entry_it.flagany  = flag_any;
            entry_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | flag_none;

            entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
            while (entry)
            {
                if (tbl == org_tbl)
                {
                    org_entry = entry;
                }
                else
                {
                    org_entry_it.obj.name = entry->name;

                    org_entry = autogen_obj_find_in_list(&org_entry_it, &org_tbl->base.child_list);
                }

                if (org_entry)
                {
                    /* bit table */
                    if (org_tbl->base.subtype == AUTOGEN_TBL_BIT)
                    {
                        pmd_number_pres_cond_el* pres_cond_el = pmd_number_pres_cond_el_create(env,
                            pmd_cond_el_bit_create(env, ((autogen_bittbl_entry*)org_entry)->bit_pattern),
                            pmd_number_pres_const_create(env, org_entry->name));

                        pmd_number_pres_cond_el_add(pres_cond, pres_cond_el);
                    }
                    /* constant / FTD / PPC table */
                    else
                    {
                        pmd_number_pres_cond_el_add_simple(env, pres_cond, org_entry->id, org_entry->name);
                    }
                }

                entry = autogen_obj_find_next_in_list(&entry_it);
            }
        }

        /* add DEC default presentation for PN_OBJECT table presentations */
        if (res == util_get_unique_res(RESOURCE_SYMBOLS) && tbl_name && strstr(tbl_name, "PN_OBJECT"))
        {
            pres_cond->default_pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_DEC, "");
        }

        if (pres_cond->n_pres_cond_el > 0)
        {
            pres = &pres_cond->number_pres;
        }
    }

    if (!pres)
    {
        pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, NULL);
    }

    return pres;
}

LOCAL int pmd_generate_resource_extensions(pmd_env *env, pmd_choice* msg_sel, unsigned int flag_func, 
                                           autogen_res* res, pmd_msggrp* msggrp, pmd_mod* res_mod)
{
    int has_msg = FALSE;

    if (res->conf->ext_res_type != 0)
    {
        autogen_it ext_res_it = INIT_ITERATOR;
        autogen_res* ext_res;

        ext_res_it.flagall      = env->flag_all;
        ext_res_it.typemask     = AUTOGEN_OBJ_RES;
        ext_res_it.subtypemask  = res->conf->ext_res_type;
        ext_res_it.idcrit       = AUTOGEN_OBJ_ID_EXACT;
        ext_res_it.obj.id       = res->base.id;
        ext_res_it.flagnone     = AUTOGEN_MSG_HAS_NO_ELEMENTS | AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

        /* iterate through all extensions */
        ext_res = (autogen_res*)autogen_obj_find_in_list(&ext_res_it, g_res_list);
        while (ext_res)
        {
            int has_msg_res = FALSE;
            int msggrp_to_be_added = FALSE;
		    const char* res_mod_name = pmd_typedef_module_get_name_from_object(&ext_res->base);
            pmd_msggrp* new_msggrp = msggrp;
			pmd_msgtype* msgtype = pmd_msgtype_add(env, ext_res->device_id, ext_res->conf->msg_type,
				pmd_constant_lookup_message_type_name(ext_res->conf->msg_type),
				pmd_constant_lookup_message_type_identifier(ext_res->conf->msg_type),
				pmd_constant_lookup_message_type_flags(ext_res->conf->msg_type));

			/* add the resource module, the parent module to all modules in the resource */
			pmd_typedef_module_add(env, res_mod_name, env->typ_root_module);

            /* generate message group (resource) */
            if (strcmp(res->base.name, ext_res->base.name) != 0)
            {
                new_msggrp = pmd_msggrp_res_find_in_msgtype(msgtype, ext_res);
                if (!new_msggrp)
                {
                    new_msggrp = pmd_msggrp_res_create(env, msgtype, ext_res->base.id, ext_res->base.name, ext_res->logical_name, ext_res);
                    msggrp_to_be_added = TRUE;

                    if (prop_has(&ext_res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
                    {
                        new_msggrp->namedobj.managedobj.flags |= PMD_RESOURCE_HAS_CONFLICTING_MESSAGES;
                    }
                }
            }

            /* generate all messages on the extension resource and add to resource message selection */
            has_msg_res = pmd_generate_message_structure(env, msg_sel, flag_func, 0, 0, ext_res, ext_res, &ext_res->msg_list, msgtype, new_msggrp, res_mod);
            has_msg |= has_msg_res;

            /* add resource object? */
            if (has_msg_res && msggrp_to_be_added)
            {
                pmd_msggrp_res_insert_in_msgtype(msgtype, new_msggrp);
            }

            ext_res = (autogen_res*)autogen_obj_find_next_in_list(&ext_res_it);
        }
    }

    return has_msg;
}

LOCAL pmd_typ* pmd_generate_resource_structure(pmd_env* env, autogen_res* res, pmd_msgtype* msgtype)
{
    int has_msg = FALSE;
    int msggrp_to_be_added = FALSE;
    int msgtype_to_be_added = FALSE;
    pmd_choice* msg_sel = NULL;
    pmd_choice* msg_sel_req = NULL;
    pmd_choice* msg_sel_resp = NULL;
    pmd_mod* res_mod;
    const char* res_mod_name = pmd_typedef_module_get_name_from_object(&res->base);
    pmd_msggrp* msggrp = NULL;
    unsigned short device_id = res->device_id;

    /* if resource has already been built, return */
    if (pmd_typedef_module_lookup(res_mod_name, env->typ_root_module))
    {
        return NULL;
    }

    if (device_id == AUTOGEN_DEVICE_CURRENT)
    {
        device_id = env->device_id;
    }

    /* if device, which resource belongs to, doesn't exist, don't create resource... */
    if (!pmd_device_find(env, device_id) && device_id != PMD_DEVICE_GENERAL)
    {
        if (!pmd_device_add_default(env, device_id))
        {
            return NULL;
        }
    }

    /* if message type is not defined, define it! */
    if (!msgtype)
    {
        msgtype = pmd_msgtype_find(env, device_id, res->conf->msg_type);

        if (res->conf->msg_type_flags)
        {
            if (!msgtype)
            {
                msgtype = pmd_msgtype_create(env, device_id, res->conf->msg_type, 
                    pmd_constant_lookup_message_type_name(res->conf->msg_type), 
                    res->identifier, 
                    pmd_constant_lookup_message_type_flags(res->conf->msg_type));
                msgtype_to_be_added = TRUE;
            }

            if (pmd_constant_lookup_message_type_flags(res->conf->msg_type) & PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE)
            {
                if (!pmd_msggrp_res_find_in_msgtype(msgtype, res))
                {
                    msggrp = pmd_msggrp_res_create(env, msgtype, res->base.id, res->base.name, res->logical_name, res);
                    msggrp_to_be_added = TRUE;

                    if (prop_has(&res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
                    {
                        msggrp->namedobj.managedobj.flags |= PMD_RESOURCE_HAS_CONFLICTING_MESSAGES;
                    }
                }
            }
        }
    }

    /* add the resource module, the parent module to all modules in the resource */
    res_mod = pmd_typedef_module_add(env, res_mod_name, env->typ_root_module);

    /* Build subblocks */
    pmd_generate_data_subblocks(env, res, AUTOGEN_TBL_FTD);
    pmd_generate_data_subblocks(env, res, AUTOGEN_TBL_PPC);
    /* TBS HANDLE SYMBIAN ??? */

    /* generate selection objects */
    if (prop_has(&res->base, PROPERTY_DEVICE_DEPENDENT_MESSAGES))
    {
        msg_sel_req  = pmd_generate_message_selection(env, "msg_sel_req",  res, res_mod);
        msg_sel_resp = pmd_generate_message_selection(env, "msg_sel_resp", res, res_mod);

        msg_sel = pmd_generate_message_direction_selection(env, "msg_sel", res, msg_sel_req, msg_sel_resp, res_mod);

        has_msg |= pmd_generate_message_structure(env, msg_sel_req, 
            AUTOGEN_MSG_REQ, 0, 
            AUTOGEN_MSG_RESP | AUTOGEN_MSG_IND | AUTOGEN_MSG_NTF | AUTOGEN_MSG_TRC | AUTOGEN_MSG_IS_MM_SPECIFIC, res, res, &res->msg_dev_dep_req_list, msgtype, msggrp, res_mod);

        has_msg |= pmd_generate_message_structure(env, msg_sel_resp, 
            AUTOGEN_MSG_RESP | AUTOGEN_MSG_IND | AUTOGEN_MSG_NTF | AUTOGEN_MSG_TRC, 0,
            AUTOGEN_MSG_REQ | AUTOGEN_MSG_IS_MM_SPECIFIC, res, res, &res->msg_dev_dep_resp_list, msgtype, msggrp, res_mod);

        /* generate common messages */

        /* TBS HANDLE SYMBIAN */

        if (res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES)
        {
            autogen_res* comm_res = NULL;
            if (res->base.subtype == RESOURCE_ISI_PREFIX)
            {
                comm_res = util_get_unique_res(RESOURCE_ISI_COMMON_MESSAGES_EXT);
            }
            else
            {
                comm_res = util_get_unique_res(RESOURCE_ISI_COMMON_MESSAGES);
            }
            if (comm_res)
            {
                has_msg |= pmd_generate_message_structure(env, msg_sel_req, 
                    AUTOGEN_MSG_REQ, 0, AUTOGEN_MSG_IS_MM_SPECIFIC, res, comm_res, &comm_res->msg_list, msgtype, msggrp, res_mod);

                has_msg |= pmd_generate_message_structure(env, msg_sel_resp, 
                    AUTOGEN_MSG_RESP, 0, AUTOGEN_MSG_IS_MM_SPECIFIC, res, comm_res, &comm_res->msg_list, msgtype, msggrp, res_mod);
            }
        }
    }
    else if (res->msg_id_offset != AUTOGEN_NOT_SUPPORTED)
    {
        msg_sel = pmd_generate_message_selection(env, "msg_sel", res, res_mod);
        if (msg_sel && msggrp_to_be_added)
        {
            msggrp->ref_type = &msg_sel->constructed.type;
        }

        has_msg |= pmd_generate_message_structure(env, msg_sel, 
            AUTOGEN_MSG_FUNCTION_MASK, 0, AUTOGEN_MSG_IS_MM_SPECIFIC, res, res, &res->msg_list, msgtype, msggrp, res_mod);

        /* generate common messages */
        if (res->base.flag & AUTOGEN_RES_SUPPORTS_COMMON_MESSAGES)
        {
            autogen_res* comm_res = NULL;
            if (res->base.subtype == RESOURCE_ISI_PREFIX)
            {
                comm_res = util_get_unique_res(RESOURCE_ISI_COMMON_MESSAGES_EXT);
            }
            else
            {
                comm_res = util_get_unique_res(RESOURCE_ISI_COMMON_MESSAGES);
            }
            if (comm_res)
            {
                has_msg |= pmd_generate_message_structure(env, msg_sel, 
                    AUTOGEN_MSG_FUNCTION_MASK, 0, AUTOGEN_MSG_IS_MM_SPECIFIC, res, comm_res, &comm_res->msg_list, msgtype, msggrp, res_mod);
            }
        }
        /* generate resource extensions */
        has_msg |= pmd_generate_resource_extensions(env, msg_sel, AUTOGEN_MSG_FUNCTION_MASK, res, msggrp, res_mod);
    }

    /* Add resource object / message type ? */
    if (has_msg && msgtype_to_be_added)
    {
        pmd_msgtype_insert_in_device(env, device_id, msgtype);
    }
    if (has_msg && msggrp_to_be_added)
    {
        pmd_msggrp_res_insert_in_msgtype(msgtype, msggrp);
    }

    return (msg_sel && has_msg) ? &msg_sel->constructed.type : NULL;
}

LOCAL void pmd_generate_resource_type_structures(pmd_env* env, unsigned int res_type)
{
    autogen_res* res;
    autogen_it res_it = INIT_ITERATOR;

    res_it.flagall     = env->flag_all;
    res_it.typemask    = AUTOGEN_OBJ_RES;
    res_it.subtypemask = res_type;
    res_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

    res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
    while (res)
    {
        if (res->base.subtype == RESOURCE_PROTOCOL && prop_has(&res->base, PROPERTY_PROTOCOL_HAS_NO_MESSAGES) && res->msg_list.n_obj)
        {
            unsigned short device_id = (unsigned short)prop_get_value_default(&res->base, PROPERTY_PMD_PHONET_DEVICE_ID, PMD_DEVICE_GENERAL);

            pmd_mod* res_mod = pmd_typedef_module_add(env, pmd_typedef_module_get_name_from_object(&res->base), env->typ_root_module);
            res_mod->seq = pmd_seq_create(env, res_mod->name, PMD_SEQUENCE_TYPE_ENTRY_POINT);

            /* add items of "dummy" message */
            pmd_generate_sequence_elements(env, res, &autogen_obj_get_first_in_list(&res->msg_list)->child_list, res_mod, res_mod, res, NULL, NULL, NULL, TRUE);

            env->typ_res_entrypoint[res->index] = &res_mod->seq->constructed.type;

            /* add entry point */
            if (device_id == AUTOGEN_DEVICE_CURRENT)
            {
                device_id = env->device_id;
            }
            {
                pmd_entry_point* entry_point = pmd_entry_point_create(env, device_id, res->base.name, (unsigned short)res->base.id, &res_mod->seq->constructed.type);
                if (prop_has(&res->base, PROPERTY_PMD_PROTOCOL_IS_LE))
                {
                    entry_point->managedobj.flags |= PMD_ENTRY_POINT_PROTOCOL_IS_LE;
                }
            }
        }
        else
        {
            pmd_typ* msg_sel = pmd_generate_resource_structure(env, res, NULL);
            if (msg_sel)
            {
                /* add message selection to phonet resource selection */
                if (res->conf->res_sel)
                {
                    pmd_entry_point* ep = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_PN_RESOURCE, PMD_INFO_TYPE_PN_RESOURCES);
                    unsigned short device_id = res->device_id;
                    if (device_id == AUTOGEN_DEVICE_CURRENT)
                    {
                        device_id = env->device_id;
                    }

                    pmd_entry_point_subtree_el_add(env, device_id, ep, res->base.name, res->base.id, msg_sel);
                }
                /* if PHONET messages, add message selection to phonet type selection */
                else if (res_type == RESOURCE_PHONET)
                {
                    pmd_entry_point* ep = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_PHONET_RESOURCE, PMD_INFO_TYPE_PN_RESOURCES);
                    unsigned short device_id = res->device_id;
                    if (device_id == AUTOGEN_DEVICE_CURRENT)
                    {
                        device_id = env->device_id;
                    }

                    pmd_entry_point_subtree_el_add(env, device_id, ep, res->base.name, res->base.id, msg_sel);
                }
                /* add entry point for protocol resources */
                if (res->base.subtype == RESOURCE_PROTOCOL)
                {
                    pmd_entry_point* entry_point = pmd_entry_point_create(env, PMD_DEVICE_GENERAL, res->base.name, (unsigned short)res->base.id, msg_sel);
                    if (prop_has(&res->base, PROPERTY_PMD_PROTOCOL_IS_LE))
                    {
                        entry_point->managedobj.flags |= PMD_ENTRY_POINT_PROTOCOL_IS_LE;
                    }
                }
            }

            env->typ_res_entrypoint[res->index] = msg_sel;
        }

        res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
    }
}

LOCAL pmd_seq* pmd_generate_sequence(pmd_env* env, autogen_res* res, pmd_mod* mod, autogen_seq* org_seq,
                                     pmd_ref* ref_lst, pmd_msg* ref_msg)
{
    const char* res_mod_name = NULL;
    const char* seq_base_mod_name = pmd_typedef_module_get_name_from_object(&org_seq->base);
    pmd_mod* res_mod = NULL;
    pmd_mod* seq_base_mod = NULL;
    pmd_mod* seq_mod = NULL;
    pmd_seq* seq = NULL;

    /* subblocks using external references are placed in the message module */
    if (org_seq->ref_handle.uses_external_references)
    {
        seq_base_mod = mod;
    }
    /* shared, reusable subblocks, are placed in the shared resource / subblocks module */
    else if (org_seq->base.flag & AUTOGEN_OBJ_IS_SHARED)
    {
        autogen_it shr_sb_it = INIT_ITERATOR;

        res_mod_name      = pmd_typedef_module_get_name_from_object(&org_seq->base.res->base);
        res_mod           = pmd_typedef_module_lookup(res_mod_name, env->typ_root_module);
        seq_base_mod      = pmd_typedef_module_lookup(seq_base_mod_name, res_mod);

        /* find correct version. org_seq has the name, but not necessarily the right version */
        shr_sb_it.typemask    = org_seq->base.type;
        shr_sb_it.obj.name    = org_seq->base.name;
        shr_sb_it.ver         = &org_seq->base.res->base.ver;
        shr_sb_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;

        org_seq = (autogen_seq*)autogen_obj_find_in_list(&shr_sb_it, &org_seq->base.res->seq_list);
    }
    /* normal, reusable subblocks, are placed in the resource / subblocks module */
    else
    {
        res_mod_name = pmd_typedef_module_get_name_from_object(&res->base);
        res_mod      = pmd_typedef_module_lookup(res_mod_name, env->typ_root_module);
        if (!res_mod)
        {
            res_mod = pmd_typedef_module_add(env, res_mod_name, env->typ_root_module);
        }
        seq_base_mod = pmd_typedef_module_lookup(seq_base_mod_name, res_mod);
    }

    /* if subblock module doesn't exist, create it! */
    if (!seq_base_mod)
    {
        seq_base_mod = pmd_typedef_module_add(env, seq_base_mod_name, res_mod);
    }

    /* if sequence doesn't exist, create it! */
    if (org_seq)
    {
        seq_mod = pmd_typedef_module_lookup(org_seq->base.name, seq_base_mod);
        if (seq_mod)
        {
            seq = seq_mod->seq;
        }
        else
        {
            seq = pmd_generate_sequence_structure(env, res, seq_base_mod, org_seq, org_seq->base.name, ref_msg, NULL, ref_lst);
        }
    }

    return seq;
}

LOCAL pmd_ref* pmd_generate_sequence_element(pmd_env* env, autogen_res* res, pmd_mod* seq_mod, pmd_mod* str_mod,
                                             autogen_res* seq_res, pmd_msg* ref_msg, autogen_item* item, autogen_data* data, pmd_ref* ref_lst)
{
    switch (item->base.subtype)
    {
    case AUTOGEN_ITEM_FILLER:
        {
            if (item->agg_type == AGG_TYPE_DYNAMIC_ALIGNMENT)
            {
                pmd_filler_dyn* filler_dyn = NULL;
                unsigned int alignment = PMD_ALIGNMENT_MODULUS;
                int length = item->length;
                if (item->length == 24)
                {
                    length = 32;
                    alignment = PMD_ALIGNMENT_MODULUS_MINUS_8;
                }

                filler_dyn = pmd_filler_dyn_create(env, item->varname, length, alignment, seq_mod->seq);

                /* add filler type to module */
                pmd_typedef_type_add(seq_mod, &filler_dyn->filler.type);

                pmd_seq_el_add(env, seq_mod->seq, item->parname, &filler_dyn->filler.type);
            }
            else
            {
                unsigned int filler_size = item->length * item->agg_n;

#if (PMD_FILE_FORMAT >= 600)
                if (filler_size < 64)
#else
                if (filler_size < 32)
#endif
                {
                    if (!env->typ_fixed_filler[filler_size])
                    {
                        /* create filler type and save for later use */
                        env->typ_fixed_filler[filler_size] = (pmd_typ*)pmd_filler_static_create(env, item->varname, filler_size);

                        /* add filler type to module */
                        pmd_typedef_type_add(seq_mod, env->typ_fixed_filler[filler_size]);
                    }

                    pmd_seq_el_add(env, seq_mod->seq, item->parname, env->typ_fixed_filler[filler_size]);
                }
                else
                {
                    pmd_filler_static* filler_static = pmd_filler_static_create(env, item->varname, item->length);
                    
                    /* add filler type to module */
                    pmd_typedef_type_add(seq_mod, &filler_static->filler.type);

                    /* add array specifier */
                    if (!pmd_seq_el_add_as_array(env, item, &filler_static->filler.type, ref_lst, seq_mod, 0, 0))
                    {
                        pmd_seq_el_add(env, seq_mod->seq, item->parname, &filler_static->filler.type);
                    }
                }
            }
        }
        break;

    case AUTOGEN_ITEM_REF:
        {
            /* create new reference object */
            pmd_ref* new_ref = (pmd_ref*)calloc(1, sizeof(pmd_ref));

            /* initialize object */
            new_ref->name = item->base.name;
            new_ref->next = ref_lst;
            new_ref->item = (autogen_item_value*)item;

            pmd_length_clear(&new_ref->len);

            ref_lst = new_ref;
        }
        /* continue through here... */

    case AUTOGEN_ITEM_VALUE:
    case AUTOGEN_ITEM_POINTER:
        {
            autogen_item_value* item_val = (autogen_item_value*)item;
            pmd_typ* primitive = NULL;
            unsigned int el_flags = 0;
            int update_primitive_attr = TRUE;

            /* reuse hex value */
            if (item->base.subtype == AUTOGEN_ITEM_VALUE && 
                item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_NONE &&
                item_val->pres.type == AUTOGEN_PRESENTATION_HEX &&
                item->length > 0 && item->length < 32 &&
                item->order == AUTOGEN_ORDER_BE &&
                !prop_has(&item->base, PROPERTY_ITEM_DEFAULT_VALUE) &&
                !prop_has(&item->base, PROPERTY_ITEM_EXCEPTIONAL_VALUE) &&
                !prop_has(&item->base, PROPERTY_ITEM_MINIMUM_VALUE) &&
                !prop_has(&item->base, PROPERTY_ITEM_MAXIMUM_VALUE) &&
                !prop_has(&item->base, PROPERTY_PMD_PARAMETER_IN_SUMMARY) &&
                !data)
            {
                primitive = pmd_generate_number_hex(env, item->length, seq_mod);
            }
            /* reuse dec value */
            else if (item->base.subtype == AUTOGEN_ITEM_VALUE && 
                     item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_NONE &&
                     item_val->pres.type == AUTOGEN_PRESENTATION_DEC &&
                     item->length > 0 && item->length < 32 &&
                     item->order == AUTOGEN_ORDER_BE &&
                     !prop_has(&item->base, PROPERTY_ITEM_DEFAULT_VALUE) &&
                     !prop_has(&item->base, PROPERTY_ITEM_EXCEPTIONAL_VALUE) &&
                     !prop_has(&item->base, PROPERTY_ITEM_MINIMUM_VALUE) &&
                     !prop_has(&item->base, PROPERTY_ITEM_MAXIMUM_VALUE) &&
                     !prop_has(&item->base, PROPERTY_PMD_PARAMETER_IN_SUMMARY) &&
                     !item->base.prop_list &&
                     !data)
            {
                primitive = pmd_generate_number_dec(env, item->length, seq_mod);
            }

            /* reuse transaction ID */
            else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRANSACTION_ID)
            {
                primitive = pmd_generate_number_transaction_id(env, seq_mod);
            }
            /* primary ID */
            else if ((item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID ||
                      item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID) && item_val->pres.obj)
            {
                unsigned int special_type = item->special_number_type;
                const autogen_obj* seq = util_get_base_parent((autogen_obj*)item);

                if (res->base.subtype & RESOURCE_TRC_ANY)
                {
                    if (seq && seq->type == AUTOGEN_OBJ_MSG && (seq->flag & AUTOGEN_MSG_IS_SUBMSG))
                    {
                        special_type = PMD_NUMBER_SPECIAL_TYPE_TRACE_GROUP_ID;
                    }
                    else
                    {
                        special_type = PMD_NUMBER_SPECIAL_TYPE_TRACE_ID;
                    }
                }
                /* if STI trace, change special type to trace ID */
                else if (seq && seq->type == AUTOGEN_OBJ_MSG && (seq->flag & AUTOGEN_MSG_TRC_STI))
                {
                    special_type = PMD_NUMBER_SPECIAL_TYPE_STI_TRACE_ID;
                }

                primitive = pmd_generate_number_primary_id(env, item_val, special_type, seq_mod);
            }
            /* secondary ID */
            else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID && item_val->pres.obj)
            {
                unsigned int special_type = item->special_number_type;

                /* if trace resource, change special type to trace ID */
                if (res->base.subtype & RESOURCE_TRC_ANY)
                {
                    special_type = PMD_NUMBER_SPECIAL_TYPE_TRACE_ID;
                }

                primitive = pmd_generate_number_secondary_id(env, item_val, special_type, seq_mod);
            }
            /* item represents a trace entity ID */
            else if (item_val->base.special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_ENTITY_ID ||
                     item_val->base.special_number_type == PMD_NUMBER_SPECIAL_TYPE_PRINTF_ID)
            {
                if (!env->typ_trace_entity_id[item_val->base.trc_type])
                {
                    env->typ_trace_entity_id[item_val->base.trc_type] = 
                        pmd_generate_trace_entity_id(env, item_val->base.trc_type, item_val->base.order, seq_mod);
                }
                primitive = env->typ_trace_entity_id[item_val->base.trc_type];

                update_primitive_attr = FALSE;
            }
            /* item represents a trace group ID */
            else if (item_val->base.special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_GROUP_ID)
            {
                if (!env->typ_trace_group_id[item_val->base.trc_type])
                {
                    env->typ_trace_group_id[item_val->base.trc_type] = 
                        pmd_generate_trace_group_id(env, item_val->base.trc_type, item_val->base.order, seq_mod);
                }
                primitive = env->typ_trace_group_id[item_val->base.trc_type];

                update_primitive_attr = FALSE;
            }
            /* item represents a trace ID */
            else if (item_val->base.special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_ID)
            {
                if (!env->typ_trace_id[item_val->base.trc_type])
                {
                    env->typ_trace_id[item_val->base.trc_type] =
                        pmd_generate_trace_id(env, item_val->base.trc_type, item_val->base.order, seq_mod);
                }
                primitive = env->typ_trace_id[item_val->base.trc_type];


                update_primitive_attr = FALSE;
            }
            /* item represents a trace data length */
            else if (item_val->base.special_number_type == PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH)
            {
                primitive = pmd_generate_number_trace_data_length(env, item_val->base.trc_type, item_val->base.length, item_val->base.order, seq_mod);
            }
            /* item represents a message / subblock length */
            else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH ||
                     item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH)
            {
                unsigned int special_type = item->special_number_type;

                if (res->base.subtype & RESOURCE_TRC_ANY)
                {
                    special_type = PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH;
                }

                primitive = pmd_generate_number_dec_no_reuse(env, item->varname, item->length, special_type, seq_mod);

                seq_mod->seq->length_type = primitive;
            }
            /* item represents a device object ID */
            else if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_OBJECT)
            {
                primitive = 
                    pmd_generate_number_pn_object(env, item_val->base.varname, item_val->base.length, 
                        env->typ_last_pn_dev, PMD_NUMBER_SPECIAL_TYPE_NONE, seq_mod);
            }
            /* item is a ppc data */
            else if (item->base.subtype == AUTOGEN_ITEM_VALUE && !strcmp(item->varname, "data") && data)
            {
                /* if table data, parameter is part of a set of unknown size */
                int is_set = FALSE;

                if (data->seqname && strstr(data->seqname, "TABLE"))
                {
                    is_set = TRUE;
                }

                primitive = pmd_generate_number_from_pres(env, (const autogen_obj*)data, item->varname, item->length, 
                    &data->pres, res, PMD_NUMBER_SPECIAL_TYPE_PPC_VALUE, seq_mod);
            }
            else if (item_val->pres.type & AUTOGEN_PRESENTATION_CHAR)
            {
                pmd_string* str = NULL;

                unsigned short char_type = PMD_CHARACTER_TYPE_UNICODE;
                if (item_val->pres.type & AUTOGEN_PRESENTATION_ASCII_CHAR)
                {
                    char_type = PMD_CHARACTER_TYPE_ASCII;
                }

                str  = (pmd_string*)pmd_string_create(env, item->varname, char_type, "");
                primitive = &str->primitive.type;

                /* set string length to 1 character */
                pmd_length_init(&str->length_obj, 1, PMD_LENGTH_ALGORITHM_FIXEDLENGTH);

                /* add string type to module */
                pmd_typedef_type_add(seq_mod, primitive);
            }
            /* item is a normal item */
            else
            {
                if (item_val->pres.type & AUTOGEN_PRESENTATION_REF_DATAID)
                {
                    primitive = pmd_generate_number_const(env, item->varname, item->length, 
                        data->base.name, item->special_number_type, seq_mod);
                }
                else
                {
                    primitive = pmd_generate_number_from_pres(env, (const autogen_obj*)item_val, item_val->base.varname, 
                        item_val->base.length, &item_val->pres, res, item_val->base.special_number_type, seq_mod);
                }

                /* if reference, set the object id of the reference object in 
                   the reference list */
                if (item->base.subtype == AUTOGEN_ITEM_REF)
                {
                    pmd_length_init_as_tag(&ref_lst->len, primitive);
                }
            }

            if (item->order == AUTOGEN_ORDER_LE && update_primitive_attr == TRUE)
            {
                pmd_number_set_data_order_little_endian((pmd_number*)primitive);
            }

            /* set general flags */
            if (prop_has((autogen_obj*)item, PROPERTY_PMD_PARAMETER_IN_SUMMARY))
            {
                el_flags |= PMD_FIELD_IN_SUMMARY;
            }
            /* set default Is parameter */
            if (update_primitive_attr == TRUE)
            {
                pmd_primitive* prim = (pmd_primitive*) primitive;
                
                if (prim->special_type == PMD_NUMBER_SPECIAL_TYPE_NONE ||
                    prim->special_type == PMD_NUMBER_SPECIAL_TYPE_MCU_FUNCTION_ADDR ||
                    prim->special_type == PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE ||
                    prim->special_type == PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_OBJECT ||
                    prim->special_type == PMD_NUMBER_SPECIAL_TYPE_PPC_VALUE)
                {
                    el_flags |= PMD_FIELD_IS_PARAMETER;
                }
            }
            /* Overrule Is parameter */
            if (prop_has((autogen_obj*)item, PROPERTY_PMD_PARAMETER))
            {
                el_flags |= PMD_FIELD_IS_PARAMETER;
            }
            else if (prop_has((autogen_obj*)item, PROPERTY_PMD_IS_NOT_PARAMETER))
            {
                el_flags &= ~PMD_FIELD_IS_PARAMETER;
            }

            /* add array specifier */
            if (!pmd_seq_el_add_as_array(env, item, primitive, ref_lst, seq_mod, 0, el_flags))
            {
                pmd_seq_el* seq_el = pmd_seq_el_add(env, seq_mod->seq, item->parname, primitive);
                seq_el->namedobj.managedobj.flags |= el_flags;
            }

            /* if PN address field, store for later use */
            if (item->special_number_type == PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE)
            {
                env->typ_last_pn_dev = primitive;
                ((pmd_primitive*) primitive)->special_type = PMD_NUMBER_SPECIAL_TYPE_NONE;
            }
        }
        break;

    case AUTOGEN_ITEM_RANGE:
        {
            unsigned int el_flags = 0;
            pmd_typ* type = pmd_generate_number_range(env, item, seq_mod);

            /* if parameter, add parameter */
            if (prop_has((autogen_obj*)item, PROPERTY_PMD_PARAMETER))
            {
                el_flags |= PMD_FIELD_IS_PARAMETER;
            }
            else if (prop_has((autogen_obj*)item, PROPERTY_PMD_IS_NOT_PARAMETER))
            {
                el_flags &= ~PMD_FIELD_IS_PARAMETER;
            }

            if (item->order == AUTOGEN_ORDER_LE)
            {
                type->managedobj.flags |= PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN;
            }

            /* add array specifier */
            if (!pmd_seq_el_add_as_array(env, item, type, ref_lst, seq_mod, 0, el_flags))
            {
                pmd_seq_el* seq_el = pmd_seq_el_add(env, seq_mod->seq, item->parname, type);
                seq_el->namedobj.managedobj.flags |= PMD_FIELD_IS_PARAMETER;
            }
        }
        break;

    case AUTOGEN_ITEM_TIMESTAMP:
        {
            pmd_number* number = pmd_number_create(env, item->varname, item->length, item->special_number_type);
            pmd_typ* type = &number->primitive.type;

            if (item->order == AUTOGEN_ORDER_LE)
            {
                pmd_number_set_data_order_little_endian(number);
            }

            /* set CNumberPresentationTimestamp presentation */
            number->pres = pmd_number_pres_time_create(env, item->item_sub_type);

            /* add number type to module */
            pmd_typedef_type_add(seq_mod, type);

            /* set array specifier */
            if (!pmd_seq_el_add_as_array(env, item, type, ref_lst, seq_mod, 0, 0))
            {
                pmd_seq_el_add(env, seq_mod->seq, item->parname, type);
            }
        }
        break;

    case AUTOGEN_ITEM_MERGE:
        {
            unsigned int seq_type = ((item->order == AUTOGEN_ORDER_BE) ? PMD_SEQUENCE_TYPE_BIG_ENDIAN_MERGED : PMD_SEQUENCE_TYPE_LITTLE_ENDIAN_MERGED);

            /* create module for sequence or subblock */
            pmd_mod* merge_mod = pmd_typedef_module_add(env, item->varname, seq_mod);
            merge_mod->seq = pmd_seq_create(env, merge_mod->name, seq_type);

            /* add the types from the merged field */
            ref_lst = pmd_generate_sequence_elements(env, res, &item->base.child_list, merge_mod, str_mod, seq_res, ref_msg, NULL, ref_lst, FALSE);

            /* add array specifier */
            if (!pmd_seq_el_add_as_array(env, item, &merge_mod->seq->constructed.type, ref_lst, seq_mod, 0, 0))
            {
                pmd_seq_el_add(env, seq_mod->seq, item->parname, &merge_mod->seq->constructed.type);
            }
        }
        break;

    case AUTOGEN_ITEM_PRINTF:
        {
            autogen_item_printf *printf_item = (autogen_item_printf *)item;

            /* Create module for sequence */
            pmd_mod* printf_mod = pmd_typedef_module_add(env, item->varname, seq_mod);
            printf_mod->seq = pmd_seq_create(env, printf_mod->name, PMD_SEQUENCE_TYPE_PRINTF);

            /* Add the types from the printf arguments */
            ref_lst = pmd_generate_sequence_elements(env, res, &item->base.child_list, printf_mod, str_mod, seq_res, ref_msg, NULL, ref_lst, FALSE);

            /* Add sequence */
            pmd_seq_el_add(env, seq_mod->seq, item->parname, &printf_mod->seq->constructed.type);

            /* Store printf in info object */
            pmd_info_add(env, env->device_id, PMD_INFO_TYPE_OST_PRINTF, 
                printf_item->format, env->printf_info_obj_count++,
                3, (unsigned int)printf_item->component_id, (unsigned int)printf_item->tracegrp_id, (unsigned int)printf_item->trace_id, 0);
        }
        break;

    case AUTOGEN_ITEM_STRUCT:
        {
            autogen_item_struct* str_item = (autogen_item_struct*)item;
            autogen_it seq_it = INIT_ITERATOR;
            autogen_seq* str;
            autogen_res* str_res = str_item->seqres;

            seq_it.typemask = AUTOGEN_OBJ_SEQ | AUTOGEN_OBJ_SB;
            seq_it.obj.name = str_item->seqname;
            seq_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            seq_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;
            seq_it.ver      = &str_res->base.ver;

            str = (autogen_seq*)autogen_obj_find_in_list(&seq_it, &str_res->seq_list);
            if (str)
            {
                pmd_seq* str_seq = pmd_generate_sequence(env, str_res, seq_mod, str, ref_lst, ref_msg);
                if (str_seq)
                {
                    /* add array specifier */
                    if (!pmd_seq_el_add_as_array(env, item, &str_seq->constructed.type, ref_lst, seq_mod, 0, 0))
                    {
                        pmd_seq_el_add(env, seq_mod->seq, item->parname, &str_seq->constructed.type);
                    }
                }
            }
        }
        break;

    case AUTOGEN_ITEM_LST:
        {
            pmd_typ* type = NULL;
            unsigned int el_flags = 0;
            unsigned int vec_flags = 0;

            /* list of subblock ID's */
            if (item->base.flag & AUTOGEN_LST_SBID)
            {
                type = pmd_generate_subblock_id(env, item, res, seq_mod);

                if (prop_has((autogen_obj*)item, PROPERTY_PMD_PARAMETER))
                {
                    el_flags |= PMD_FIELD_IS_PARAMETER;
                }
                else if (prop_has((autogen_obj*)item, PROPERTY_PMD_IS_NOT_PARAMETER))
                {
                    el_flags &= ~PMD_FIELD_IS_PARAMETER;
                }
            }
            /* list of subblocks */
            else
            {
                type = pmd_generate_subblock_list(env, item, res, seq_res, ref_lst, ref_msg, seq_mod);
                vec_flags |= PMD_SEQUENCE_OF_SUB_BLOCKS;
            }

            /* add array specifier */
            if (!pmd_seq_el_add_as_array(env, item, type, ref_lst, seq_mod, vec_flags, el_flags))
            {
                pmd_seq_el_add(env, seq_mod->seq, item->parname, type);
            }
        }
        break;

    case AUTOGEN_ITEM_STRING:
        {
            pmd_generate_string(env, item, item->parname, seq_mod, ref_lst);
        }
        break;

    case AUTOGEN_ITEM_BLOCK:
        {
            pmd_typ* type = NULL;
            pmd_block* block = NULL;
            autogen_item_block* item_block = (autogen_item_block*)item;

            /* If protocol block, make link to protocol resource */
            if (item->item_sub_type == BLOCK_PROTOCOL)
            {
                if (!strcmp(item_block->data1, "PROTOCOL_PHONET"))
                {
                    block = pmd_block_entry_point_create(env, item->varname, item_block->data1, PMD_PROTOCOL_PHONET, PMD_DEVICE_GENERAL);
                }
                else
                {
                    autogen_res* prot_res = util_get_protocol_res(item_block->data1);

                    unsigned short device_id = (unsigned short)prop_get_value_default(&item->base, PROPERTY_PMD_PHONET_DEVICE_ID, PMD_DEVICE_GENERAL);
                    if (device_id == AUTOGEN_DEVICE_CURRENT)
                    {
                        device_id = env->device_id;
                    }

                    /* create block type */
                    if (prot_res)
                    {
                        block = pmd_block_entry_point_create(env, item->varname, item_block->data1, (unsigned short)prot_res->base.id, device_id);

                        if (ref_msg)
                        {
                            if (prot_res->base.id == PMD_PROTOCOL_INVARIANT_TRACE || prot_res->base.id == PMD_ENTRY_POINT_INVARIANT_TRACE ||
                                prot_res->base.id == PMD_PROTOCOL_MCU_TRACE       || prot_res->base.id == PMD_ENTRY_POINT_MCU_TRACE ||
                                prot_res->base.id == PMD_PROTOCOL_SYMBIAN_TRACE   || prot_res->base.id == PMD_ENTRY_POINT_SYMBIAN_TRACE ||
                                prot_res->base.id == PMD_ENTRY_POINT_XTI_MASTER   || prot_res->base.id == PMD_ENTRY_POINT_VENDOR_COMPONENT_TRACE ||
                                prot_res->base.id == PMD_ENTRY_POINT_MASTER_TRACE || prot_res->base.id == PMD_PROTOCOL_OST)
                            {
                                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_EMBEDDED_TRACES;
                            }
                            if (prot_res->base.id == PMD_PROTOCOL_EUTRAN_L2_INTERNAL_MSGS ||
                                prot_res->base.id == PMD_PROTOCOL_OST)
                            {
                                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_EMBEDDED_PROTOCOL_MESSAGE;
                            }
                        }
                    }
                    else
                    {
                        unsigned short id = pmd_constant_lookup_entry_point_id(item_block->data1);
                        if (id != PMD_ENTRY_POINT_UNDEFINED)
                        {
                            block = pmd_block_entry_point_create(env, item->varname, item_block->data1, id, device_id);
                        }
                    }
                }
            }
            else if (item->item_sub_type == BLOCK_PMD_ANCHOR)
            {
                if (!strcmp(item_block->data1, "MM_SPECIFIC_DATA"))
                {
                    type = (pmd_typ*) pmd_generate_media_module_specific_structure(env, 
                        item->base.parent->flag & AUTOGEN_MSG_FUNCTION_MASK, res, seq_mod);
                }
                else
                {
                    unsigned int n;

                    for (n = 1; n < AUTOGEN_OBJ_TRACEGRP_MAX && type == NULL; n++)
                    {
                        if (!strcmp(item_block->data1, g_trcgrp_conf[n].anchor))
                        {
                            if (n == AUTOGEN_OBJ_TRACEGRP_MASTER)
                            {
#if AUTOGEN_XTI_VERSION == AUTOGEN_XTI_V3
                                type = pmd_generate_trace_structure_xti_masters_links(env, seq_mod, ref_lst);
#endif
                            }
                            else if (g_trcgrp_conf[n].has_groups)
                            {
                                if (!env->typ_trace_structure[n])
                                {
                                    if ((g_trcgrp_conf[n].pmd_class & env->flag_all) == env->flag_all)
                                    {
                                        env->typ_trace_structure[n] = pmd_generate_trace_group_structure(env, n, seq_mod);
                                    }
                                }
                                type = env->typ_trace_structure[n];
                            }
                            else
                            {
                                type = env->typ_trace_type_entrypoint[n];
                            }

                            if (ref_msg)
                            {
                                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_EMBEDDED_TRACES;
                            }
                        }
                    }
                    for (n = 0; n < AUTOGEN_RESOURCE_TYPES_MAX && type == NULL; n++)
                    {
                        if (!strcmp(item_block->data1, g_res_conf[n].anchor))
                        {
                            autogen_res* unique_res = util_get_unique_res(g_res_conf[n].res_type);
                            if (unique_res)
                            {
                                type = env->typ_res_entrypoint[unique_res->index];
                            }
                        }
                    }
                }

                if (type)
                {
                    pmd_seq_el_add(env, seq_mod->seq, item->parname, type);
                }
            }
            else if (item->item_sub_type == BLOCK_X_FILE)
            {
                /* create block type */
                block = pmd_block_create(env, item->varname, item->item_sub_type);
            }
            else if (item->item_sub_type == BLOCK_RAW_DATA)
            {
                /* do nothing... */
            }
            else if (item->item_sub_type == BLOCK_EXT_DECODER)
            {
                /* create block type */
                block = pmd_block_dll_create(env, item->varname, item_block->data1, item_block->data2);

                /* set flags */
                block->constructed.type.managedobj.flags |= item->base.flag;
            }
            else if (item->item_sub_type == BLOCK_PN_MSG)
            {
                block = pmd_block_entry_point_create(env, item->varname, "PROTOCOL_PHONET", PMD_PROTOCOL_PHONET, PMD_DEVICE_GENERAL);

                /* set flags */
                block->constructed.type.managedobj.flags |= item->base.flag;
            }

            /* if block is defined, set length etc. */
            if (block)
            {
                /* set length on block */
                pmd_length_init_from_item(env, &block->constructed.length_obj, item, seq_mod->seq, ref_lst);

                /* add block type to module */
                pmd_typedef_type_add(seq_mod, &block->constructed.type);

                /* add block to sequence */
                pmd_seq_el_add(env, seq_mod->seq, item->parname, &block->constructed.type);
            }
            /* if no type defined, add a sequence of bytes */
            else if (!type)
            {
                type = pmd_generate_number_hex(env, 8, seq_mod);

                /* add array specifier */
                if (!pmd_seq_el_add_as_array(env, item, type, ref_lst, seq_mod, 0, 0))
                {
                    pmd_seq_el_add(env, seq_mod->seq, item->parname, type);
                }
            }
        }
        break;

    case AUTOGEN_ITEM_CHOICE:
        {
            autogen_item_choice* item_choice = (autogen_item_choice*)item;
            const pmd_ref* ref = ref_lst;

            pmd_choice* choice = pmd_choice_create(env, item_choice->base.varname, NULL, env->device_id);

            pmd_typedef_type_add(seq_mod, &choice->constructed.type);

            if (item_choice->base.base.flag & AUTOGEN_CHOICE_FORWARD)
            {
                pmd_typ* tag;
                autogen_it tbl_it = INIT_ITERATOR;
                autogen_tbl* tbl;

                tbl_it.typemask    = AUTOGEN_OBJ_TBL;
                tbl_it.subtypemask = AUTOGEN_TBL_CONST | AUTOGEN_TBL_DERCONST;
                tbl_it.obj.name    = item_choice->tblname;
                tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
                tbl_it.ver         = &item_choice->tblres->base.ver;

                tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &item_choice->tblres->tbl_list);
                tbl = util_get_parent_table(tbl, &item_choice->tblres->base.ver);
              
                tag = pmd_generate_number_hex_tag(env, abs(tbl->length), seq_mod);

                pmd_tag_init(&choice->tag, tag, PMD_BIT_POSITION_AFTER, item_choice->relpos);
            }
            else
            {
                autogen_ref* org_ref = reference_find(item);
                ref = pmd_tag_init_reference(env, &choice->tag, ref_lst, org_ref->name, org_ref);
            }

            pmd_seq_el_add(env, seq_mod->seq, item_choice->base.parname, &choice->constructed.type);

            /* add cases */
            {
                autogen_it case_it = INIT_ITERATOR;
                autogen_item_case* case_item;

                case_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                case_it.ver      = &item_choice->base.seq->base.res->base.ver;
                case_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

                case_item = (autogen_item_case*)autogen_obj_find_in_list(&case_it, &item_choice->base.base.child_list);
                while (case_item)
                {
                    char case_name[2*AUTOGEN_MAX_NAME_LENGTH + 2];
                    pmd_mod* case_mod;

                    /* lookup case ID / mask */
                    if (!(case_item->base.base.flag & AUTOGEN_CASE_HAS_ID))
                    {
                        const char* tbl_name = (item_choice->base.base.flag & AUTOGEN_CHOICE_FORWARD) ? item_choice->tblname : ref->item->pres.tblname;
                        autogen_res* tbl_res = (item_choice->base.base.flag & AUTOGEN_CHOICE_FORWARD) ? item_choice->tblres  : ref->item->pres.tblres;

                        if (item_choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_CONSTANT)
                        {
                            case_item->base.base.id = util_get_case_id(case_item->base.base.name, tbl_name, tbl_res, &case_item->base.base.ver);
                        }
                        else if (item_choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_BITMASK)
                        {
                            case_item->base.bit_pattern = pmd_heap_strdup(util_get_case_mask(case_item->base.base.name, tbl_name, tbl_res, &case_item->base.base.ver));
                        }
                    }

                    sprintf(case_name, "%s %s", item_choice->base.varname, case_item->base.base.name);

                    /* create module for sequence */
                    case_mod = pmd_typedef_module_add(env, case_name, seq_mod);
                    case_mod->seq = pmd_seq_create(env, case_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

                    /* add the types from the case */
                    pmd_generate_sequence_elements(env, res, &case_item->base.base.child_list, case_mod, str_mod, seq_res, ref_msg, data, ref_lst, TRUE);

                    /* add the case to the choice */
                    if (item_choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_VALUE)
                    {
                        pmd_choice_el_add_simple(env, choice, 
                            pmd_heap_strdup_h(env->heap_handle, case_name),
                            case_item->base.base.id, &case_mod->seq->constructed.type);
                    }
                    else if (item_choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_CONSTANT)
                    {
                        pmd_choice_el_add_simple(env, choice, 
                            pmd_heap_strdup_h(env->heap_handle, case_name),
                            case_item->base.base.id, &case_mod->seq->constructed.type);
                    }
                    else if (item_choice->base.base.flag & AUTOGEN_CHOICE_REFERENCE_BITMASK)
                    {
                        pmd_choice_el_add_mask(env, choice, 
                            pmd_heap_strdup_h(env->heap_handle, case_name),
                            case_item->base.bit_pattern, &case_mod->seq->constructed.type);
                    }

                    case_item = (autogen_item_case*)autogen_obj_find_next_in_list(&case_it);
                }

                /* Default case */
                case_item = item_choice->default_case;
                if (case_item)
                {
                    char case_name[2*AUTOGEN_MAX_NAME_LENGTH + 2];
                    pmd_mod* case_mod;

                    sprintf(case_name, "%s def", item_choice->base.varname);

                    /* create module for sequence */
                    case_mod = pmd_typedef_module_add(env, case_name, seq_mod);
                    case_mod->seq = pmd_seq_create(env, case_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

                    /* add the types from the case */
                    pmd_generate_sequence_elements(env, res, &case_item->base.base.child_list, case_mod, str_mod, seq_res, ref_msg, data, ref_lst, TRUE);

                    choice->default_type = &case_mod->seq->constructed.type;
                }
            }
        }
        break;

    default:
        {
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
            "pmd_generate_sequence_element(): Default case met. item->base.subtype is 0x%8.8X", item->base.subtype);
        }
        break;
    }

    return ref_lst;
}

LOCAL pmd_ref* pmd_generate_sequence_elements(pmd_env* env, autogen_res* res, autogen_obj_list* obj_list,
                                              pmd_mod* seq_mod, pmd_mod* str_mod, autogen_res* seq_res, pmd_msg* ref_msg, 
                                              autogen_data* data, pmd_ref* ref_lst, int del_ref_lst)
{
    int skip_rest = FALSE;
    pmd_ref* org_ref_lst = ref_lst;
    autogen_item* item = NULL;
    autogen_it item_it = INIT_ITERATOR;

    item_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;
    item_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
    item_it.ver      = &seq_res->base.ver;

    item = (autogen_item*)autogen_obj_find_in_list(&item_it, obj_list);
    while (item && !skip_rest)
    {
        int skip = FALSE;
        const char* anchor = prop_get_string_default((autogen_obj*)item, PROPERTY_PMD_ANCHOR, "");
        if (anchor[0])
        {
            /* if the item is the place where media module specific messages should be invoked,
               insert the specific message selection here, and don't continue... 
            */
            if (!strcmp(anchor, "MM_SPECIFIC_DATA"))
            {
                pmd_choice* msg_sel = pmd_generate_media_module_specific_structure(env, 
                    obj_list->parent->flag & AUTOGEN_MSG_FUNCTION_MASK, res, seq_mod);

                if (msg_sel)
                {
                    pmd_seq_el_add(env, seq_mod->seq, item->parname, &msg_sel->constructed.type);
                    skip = TRUE;

                    if (ref_msg)
                    {
                        ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_EMBEDDED_MEDIA_MODULE_MESSAGE;
                    }
                }
            }
            /* if FTD value item, replace with sub structure */
            else if (!strcmp(anchor, "FTD_DATA_VALUE"))
            {
                pmd_generate_sequence_elements(env, res, &data->base.child_list, seq_mod, str_mod, res, ref_msg, NULL, ref_lst, TRUE);
                skip = TRUE;
            }
            /* if FTD table item, replace with an array of the sub structure */
            else if (!strcmp(anchor, "FTD_DATA_TABLE"))
            {
                pmd_seq_of* data_rep = NULL;
                pmd_mod* data_mod = pmd_typedef_module_add(env, "table_data", seq_mod);
                data_mod->seq = pmd_seq_create(env, data_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

                pmd_generate_sequence_elements(env, res, &data->base.child_list, data_mod, str_mod, res, ref_msg, NULL, ref_lst, TRUE);

                /* create CSequenceOf object */
                data_rep = pmd_seq_of_create(env, "data_array", &data_mod->seq->constructed.type);

                /* set length to array length */
                pmd_length_init_from_item(env, &data_rep->constructed.length_obj, item, seq_mod->seq, ref_lst);

                /* add array object to module */
                pmd_typedef_type_add(seq_mod, &data_rep->constructed.type);

                pmd_seq_el_add(env, seq_mod->seq, item->parname, &data_rep->constructed.type);

                skip = TRUE;
            }
            /* if FTD string item, replace with correct name */
            else if (!strcmp(anchor, "FTD_DATA_STRING"))
            {
                pmd_generate_string(env, item, data->parname, seq_mod, ref_lst);
                skip = TRUE;
            }
            /* if FTD test data structure, replace with generated structure */
            else if (!strcmp(anchor, "FTD_TEST_DATA_STRUCTURE"))
            {
                pmd_generate_ftd_test_data_structure(env, res, seq_mod, ref_msg);
                skip_rest = TRUE;
                skip = TRUE;
            }
        }

        /* else just generate the type.... */
        if (!skip)
        {
            ref_lst = pmd_generate_sequence_element(env, res, seq_mod, str_mod, seq_res, ref_msg, item, data, ref_lst);
        }

        item = (autogen_item*)autogen_obj_find_next_in_list(&item_it);
    }

    /* delete the new references */
    if (del_ref_lst)
    {
        while (ref_lst != org_ref_lst)
        {
            pmd_ref* next_ref = ref_lst->next;

            free(ref_lst);

            ref_lst = next_ref;
        }
    }

    return ref_lst;
}    

LOCAL pmd_seq* pmd_generate_sequence_structure(pmd_env* env, autogen_res* res, pmd_mod* mod, autogen_seq* org_seq, 
                                               const char* name, pmd_msg* ref_msg, autogen_data* data, pmd_ref* ref_lst)
{
    /* create module for sequence or subblock */
    pmd_mod* seq_mod = pmd_typedef_module_add(env, name, mod);

    /* create sequence ... */
    if (!seq_mod->seq)
    {
        if (org_seq->base.type == AUTOGEN_OBJ_SB || org_seq->base.type == AUTOGEN_OBJ_SB_TEMPLATE)
        {
            seq_mod->seq = pmd_seq_create(env, seq_mod->name, PMD_SEQUENCE_TYPE_SUB_BLOCK);
            seq_mod->seq->org_seq = org_seq;
        }
        else
        {
            seq_mod->seq = pmd_seq_create(env, seq_mod->name, PMD_SEQUENCE_TYPE_STRUCTURE);
            seq_mod->seq->org_seq = org_seq;
        }

        /* add the types from the sequence */
        pmd_generate_sequence_elements(env, res, &org_seq->base.child_list, seq_mod, seq_mod, org_seq->base.res, ref_msg, data, ref_lst, TRUE);

        /* set sequence length reference */
        if (org_seq->base.type == AUTOGEN_OBJ_SB && !prop_has((autogen_obj*)org_seq, PROPERTY_SB_LENGTH_MISSING) || 
            org_seq->base.type == AUTOGEN_OBJ_SB_TEMPLATE)
        {
            if (seq_mod->seq->length_type)
            {
                const autogen_item* length_item = reference_get_special_item(&org_seq->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH);

                pmd_tag_init(&seq_mod->seq->constructed.length_obj.tag, seq_mod->seq->length_type, 
                    PMD_BIT_POSITION_AFTER, (unsigned short)length_item->offset);

                seq_mod->seq->constructed.length_obj.alg = PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH;

                if (org_seq->base.type == AUTOGEN_OBJ_SB && 
                    prop_has((autogen_obj*)org_seq, PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY))
                {
                    seq_mod->seq->constructed.length_obj.length = 
                        (unsigned short)(length_item->offset + length_item->length/8);
                }
                else
                {
                    seq_mod->seq->constructed.length_obj.length = 0;
                }
            }
        }
    }

    return seq_mod->seq;
}

LOCAL void pmd_generate_sti_trace_structure(pmd_env* env, autogen_res* res)
{
    autogen_res* sti_res;
    autogen_it sti_res_it = INIT_ITERATOR;

    sti_res_it.flagall     = env->flag_all;
    sti_res_it.typemask    = AUTOGEN_OBJ_RES;
    sti_res_it.subtypemask = RESOURCE_TRC_STI;

    sti_res = (autogen_res*)autogen_obj_find_in_list(&sti_res_it, g_res_list);
    while (sti_res)
    {
        pmd_choice* msg_sel = NULL;

        unsigned int msgtype_id = (unsigned int)prop_get_value_default((autogen_obj*)sti_res, PROPERTY_PMD_TRACE_SOURCE, sti_res->conf->msg_type);
        const char* msg_id      = prop_get_string_indexed_default(&g_pmd_environment_variables, PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER, msgtype_id, pmd_constant_lookup_message_type_identifier(sti_res->conf->msg_type));
        const char* trc_type    = prop_get_string_indexed_default(&g_pmd_environment_variables, PROPERTY_PMD_TRACE_SOURCE_NAME, msgtype_id, pmd_constant_lookup_message_type_name(sti_res->conf->msg_type));
        pmd_msgtype* msgtype    = pmd_msgtype_add(env, sti_res->device_id, msgtype_id, trc_type, msg_id, pmd_constant_lookup_message_type_flags(sti_res->conf->msg_type));

        /* generate the resource (one set of submessages) */
        msg_sel = (pmd_choice*)pmd_generate_resource_structure(env, sti_res, msgtype);

        /* add the submessage selection to PN_OSTRICH message selection */
        if (msg_sel && msg_sel->choice_el)
        {
            pmd_choice* dev_sel = (pmd_choice*)env->typ_res_entrypoint[res->index];
            if (dev_sel->default_type)
            {
                pmd_choice* trc_sel = (pmd_choice*)dev_sel->default_type;

                pmd_choice_el* msg_sel_el = msg_sel->choice_el;
                while (msg_sel_el)
                {
                    pmd_choice_el_add(env, trc_sel, msg_sel_el->namedobj.name, msg_sel_el->cond_el, msg_sel_el->type);

                    msg_sel_el = msg_sel_el->next;
                }
            }
        }

        sti_res = (autogen_res*)autogen_obj_find_next_in_list(&sti_res_it);
    }
}

LOCAL void pmd_generate_string(pmd_env* env, autogen_item* item, const char* parname, pmd_mod* seq_mod, pmd_ref* ref_lst)
{
    unsigned int el_flags = PMD_FIELD_IS_PARAMETER;
    pmd_string* str = NULL;
    unsigned short chartype = PMD_CHARACTER_TYPE_ASCII;
    if (item->base.flag & AUTOGEN_STRING_UNICODE)
    {
        chartype = PMD_CHARACTER_TYPE_UNICODE;
    }
    else if (item->base.flag & AUTOGEN_STRING_BCD)
    {
        chartype = PMD_CHARACTER_TYPE_BCD;
    }
    else if (item->base.flag & AUTOGEN_STRING_GSM)
    {
        chartype = PMD_CHARACTER_TYPE_GSM;
    }
    else if (item->base.flag & AUTOGEN_STRING_UTF8)
    {
        chartype = PMD_CHARACTER_TYPE_UTF8;
    }

    str = pmd_string_create(env, item->varname, chartype, NULL);

    /* set string length */
    pmd_length_init_from_item(env, &str->length_obj, item, seq_mod->seq, ref_lst);

    /* set string flags */
    if (item->base.flag & AUTOGEN_STRING_ZERO_TERMINATED)
    {
        str->primitive.type.managedobj.flags |= PMD_STRING_IS_NULL_TERMINATED;
    }
    if (item->base.flag & (AUTOGEN_STRING_BCD | AUTOGEN_STRING_GSM | AUTOGEN_STRING_UTF8))
    {
        str->primitive.type.managedobj.flags |= PMD_STRING_LENGTH_IN_BYTES;
    }
    if (item->order & (AUTOGEN_ORDER_LE | AUTOGEN_ORDER_BCD_NSW))
    {
        pmd_string_set_data_order_little_endian(str);
    }
    if (prop_has(&item->base, PROPERTY_STRING_UNFORMATTED))
    {
        str->primitive.type.managedobj.flags |= PMD_STRING_IS_UNFORMATTED;
    }

    /* set BCD map */
    if (prop_has((autogen_obj*)item, PROPERTY_STRING_BCD_MAP))
    {
        pmd_string_set_bcd_map(env, str, prop_get_string((autogen_obj*)item, PROPERTY_STRING_BCD_MAP));
    }

    /* add string type to module */
    pmd_typedef_type_add(seq_mod, &str->primitive.type);

    /* set general flags */
    if (prop_has((autogen_obj*)item, PROPERTY_PMD_PARAMETER_IN_SUMMARY))
    {
        el_flags |= PMD_FIELD_IN_SUMMARY;
    }

    /* Overrule Is parameter */
    if (prop_has((autogen_obj*)item, PROPERTY_PMD_PARAMETER))
    {
        el_flags |= PMD_FIELD_IS_PARAMETER;
    }
    else if (prop_has((autogen_obj*)item, PROPERTY_PMD_IS_NOT_PARAMETER))
    {
        el_flags &= ~PMD_FIELD_IS_PARAMETER;
    }

    /* set array specifier */
    if (item->agg_type == AGG_TYPE_FIXED_MULTIPLE)
    {
        pmd_seq_el_add_as_array(env, item, &str->primitive.type, ref_lst, seq_mod, 0, el_flags);
    }
    else
    {
        pmd_seq_el* seq_el = pmd_seq_el_add(env, seq_mod->seq, parname, &str->primitive.type);
        seq_el->namedobj.managedobj.flags |= el_flags;
    }
}

LOCAL pmd_typ* pmd_generate_subblock_id(pmd_env* env, autogen_item* item, autogen_res* res, pmd_mod* mod)
{
    int length = (item->base.flag & AUTOGEN_LST_SB_HAVE_WORD_IDS) ? 16 : 8;

    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, item->varname, length, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID);

    /* create CNumberPresentationCondition object with default HEX presentation */
    pmd_number_pres_cond* pres_cond = pmd_number_pres_cond_create(env, 
        pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, ""));

    number->pres = &pres_cond->number_pres;

    /* add all normal subblocks */
    if (item->base.flag & AUTOGEN_LST_SB)
    {
        autogen_seq_ref* ref;
        autogen_it ref_it = INIT_ITERATOR;

        ref_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        ref_it.ver      = &res->base.ver;
        ref_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

        ref = (autogen_seq_ref*)autogen_obj_find_in_list(&ref_it, &item->base.child_list);
        while (ref)
        {
            /* find subblock */
            if (ref->seqptr)
            {
                pmd_number_pres_cond_el_add_simple(env, pres_cond, ref->base.id, ref->base.name);
            }
            else
            {
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                    "pmd_generate_subblock_id(): Could not lookup sequence for subblock '%s'", ref->base.name);
            }

            ref = (autogen_seq_ref*)autogen_obj_find_next_in_list(&ref_it);
        }
    }

    /* add all ftd/ppc data */
    if (item->base.flag & (AUTOGEN_LST_PPC | AUTOGEN_LST_FTD))
    {
        autogen_it tbl_it = INIT_ITERATOR;
        autogen_tbl* tbl;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = (item->base.flag & AUTOGEN_LST_FTD) ? AUTOGEN_TBL_FTD : AUTOGEN_TBL_PPC;
        tbl_it.vercrit     = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.ver         = &res->base.ver;
        tbl_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

        tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
        if (tbl)
        {
            autogen_obj* data;
            autogen_it data_it = INIT_ITERATOR;

            data_it.flagall  = env->flag_all;
            data_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
            data_it.ver      = &res->base.ver;
            data_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_DATA_FTD_IS_INPUT_DATA;

            data = autogen_obj_find_in_list(&data_it, &tbl->base.child_list);
            while (data)
            {
                pmd_number_pres_cond_el_add_simple(env, pres_cond, data->id, data->name);

                data = autogen_obj_find_next_in_list(&data_it);
            }
        }
    }

    /* add type object to module */
    pmd_typedef_type_add(mod, &number->primitive.type);

    return &number->primitive.type;
}

LOCAL pmd_typ* pmd_generate_subblock_list(pmd_env* env, autogen_item* item, 
                                          autogen_res* res, autogen_res* seq_res,
                                          pmd_ref* ref_lst, pmd_msg* ref_msg, pmd_mod* mod)
{
    char sel_varname[AUTOGEN_MAX_NAME_LENGTH + 10];
    pmd_choice* choice;

    /* create tag */
    pmd_typ* type = pmd_generate_number_hex_tag(env, (item->base.flag & AUTOGEN_LST_SB_HAVE_BYTE_IDS) ? 8 : 16, mod);

    /* create choice type */
    sprintf(sel_varname, "%s_sel", item->varname);
    choice = pmd_choice_create(env, sel_varname, NULL, env->device_id);

    /* set tag on choice */
    pmd_tag_init(&choice->tag, type, PMD_BIT_POSITION_AFTER, 0);

    /* if LE then set little endian flag */
    if (item->order == AUTOGEN_DEVICE_ENDIANESS_LE)
    {
        pmd_choice_set_data_order_little_endian(choice);
    }

    /* add normal subblocks */
    if (item->base.flag & AUTOGEN_LST_SB)
    {
        autogen_seq_ref* ref;
        autogen_it ref_it = INIT_ITERATOR;

        ref_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        ref_it.ver      = &seq_res->base.ver;
        ref_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

        ref = (autogen_seq_ref*)autogen_obj_find_in_list(&ref_it, &item->base.child_list);
        while (ref)
        {
            pmd_seq* sb_seq = pmd_generate_sequence(env, res, mod, ref->seqptr, ref_lst, ref_msg);
            if (sb_seq)
            {
                pmd_choice_el_add_simple(env, choice, ref->seqptr->base.name, ref->seqptr->base.id, &sb_seq->constructed.type);
            }

            ref = (autogen_seq_ref*)autogen_obj_find_next_in_list(&ref_it);
        }
    }

    /* add ftd/ppc data */
    if ((item->base.flag & AUTOGEN_LST_PPC) || 
        (item->base.flag & AUTOGEN_LST_FTD) && (res->base.subtype == RESOURCE_ISI_MEDIA_CONTROL || !strcmp(mod->name, "COMM_FTD_DATA_RESP")))
    {
        autogen_it tbl_it = INIT_ITERATOR;
        autogen_tbl* tbl;

        tbl_it.typemask = AUTOGEN_OBJ_TBL;

        if (item->base.flag & AUTOGEN_LST_FTD)
        {
            tbl_it.subtypemask = AUTOGEN_TBL_FTD;
        }
        else
        {
            tbl_it.subtypemask = AUTOGEN_TBL_PPC;
        }

        tbl_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
        tbl_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

        /* if media controller, add FTD data for all MM's */
        if (res->base.subtype == RESOURCE_ISI_MEDIA_CONTROL)
        {
            autogen_it mm_res_it = INIT_ITERATOR;
            autogen_res* mm_res;

            mm_res_it.flagall     = env->flag_all;
            mm_res_it.typemask    = AUTOGEN_OBJ_RES;
            mm_res_it.subtypemask = RESOURCE_MEDIA_MODULE;

            mm_res = (autogen_res*)autogen_obj_find_in_list(&mm_res_it, g_res_list);
            while (mm_res)
            {
                tbl_it.ver = &mm_res->base.ver;

                tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &mm_res->tbl_list);
                if (tbl)
                {
                    autogen_obj* data;
                    autogen_it data_it = INIT_ITERATOR;

                    data_it.flagall  = env->flag_all;
                    data_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                    data_it.ver      = &mm_res->base.ver;
                    data_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_DATA_FTD_IS_INPUT_DATA;

                    data = autogen_obj_find_in_list(&data_it, &tbl->base.child_list);
                    while (data)
                    {
                        pmd_mod* res_mod  = pmd_typedef_module_lookup(pmd_typedef_module_get_name_from_object(&mm_res->base), env->typ_root_module);
                        pmd_mod* sb_mod   = pmd_typedef_module_lookup(pmd_typedef_module_get_name_from_object(data), res_mod);
                        pmd_mod* data_mod = pmd_typedef_module_lookup(data->name, sb_mod);

                        if (data_mod)
                        {
                            pmd_choice_el_add_simple(env, choice, data->name, data->id, &data_mod->seq->constructed.type);
                        }
                        else
                        {
                            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                                "pmd_generate_subblock_list(): Could not locate data sequence '%s'", data->name);
                        }

                        data = autogen_obj_find_next_in_list(&data_it);
                    }
                }

                mm_res = (autogen_res*)autogen_obj_find_next_in_list(&mm_res_it);
            }
        }
        else
        {
            tbl_it.ver = &res->base.ver;

            tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &res->tbl_list);
            if (tbl)
            {
                autogen_obj* data;
                autogen_it data_it = INIT_ITERATOR;

                data_it.flagall  = env->flag_all;
                data_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
                data_it.ver      = &res->base.ver;
                data_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_DATA_FTD_IS_INPUT_DATA;

                data = autogen_obj_find_in_list(&data_it, &tbl->base.child_list);
                while (data)
                {
                    pmd_mod* res_mod  = pmd_typedef_module_lookup(pmd_typedef_module_get_name_from_object(&res->base), env->typ_root_module);
                    pmd_mod* sb_mod   = pmd_typedef_module_lookup(pmd_typedef_module_get_name_from_object(data), res_mod);
                    pmd_mod* data_mod = pmd_typedef_module_lookup(data->name, sb_mod);

                    if (data_mod)
                    {
                        pmd_choice_el_add_simple(env, choice, data->name, data->id, &data_mod->seq->constructed.type);
                    }
                    else
                    {
                        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING_INTERNAL, AUTOGEN_ENV_ALL, 0,
                            "pmd_generate_subblock_list(): Could not locate data sequence '%s'", data->name);
                    }

                    data = autogen_obj_find_next_in_list(&data_it);
                }
            }
        }
    }

    /* add type object to module */
    pmd_typedef_type_add(mod, &choice->constructed.type);

    return &choice->constructed.type;
}

LOCAL pmd_choice* pmd_generate_submessage_selection(pmd_env* env, const char* name, const autogen_res* res, pmd_mod* module)
{
    /* generate submessage ID tag dummy */
    pmd_typ* submsg_id = pmd_generate_number_hex_tag(env, res->submsg_id_size, module);

    /* create CChoice object without default type */
    pmd_choice* choice = pmd_choice_create(env, name, NULL, env->device_id);

    /* set tag to dummy submessage ID at defined relative position */
    pmd_tag_init(&choice->tag, submsg_id, PMD_BIT_POSITION_AFTER, (unsigned short)res->submsg_id_offset);

    /* add choice object to module */
    pmd_typedef_type_add(module, &choice->constructed.type);

    return choice;
}

LOCAL int pmd_generate_submessage_structure(pmd_env* env, pmd_choice* submsg_sel, autogen_seq* base_msg, 
                                            unsigned int flag_func, unsigned int flag_all, unsigned int flag_none,
                                            autogen_res* res, autogen_res* msg_res, 
                                            pmd_msgtype* msgtype, pmd_msggrp* msggrp, pmd_mod* res_mod)
{
    int has_msg = FALSE;

    autogen_seq* submsg;
    autogen_it submsg_it = INIT_ITERATOR;

    submsg_it.flagall  = flag_all | env->flag_all;
    submsg_it.flagany  = flag_func;
    submsg_it.flagnone = AUTOGEN_MSG_HAS_NO_ELEMENTS | AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | flag_none;
    submsg_it.vercrit  = AUTOGEN_OBJ_VERSION_OVERLAP;
    submsg_it.ver      = &msg_res->base.ver;

    submsg = (autogen_seq*)autogen_obj_find_in_list(&submsg_it, &base_msg->submsg_list);
    while (submsg)
    {
        pmd_typ* submsg_seq = pmd_generate_message(env, res, res_mod, submsg, msg_res, msgtype, msggrp);
        if (submsg_seq)
        {
            /* add the message to the message selection */
            pmd_choice_el_add_simple(env, submsg_sel, submsg->base.name, submsg->base.id, submsg_seq);

            has_msg = TRUE;
        }

        submsg = (autogen_seq*)autogen_obj_find_next_in_list(&submsg_it);
    }

    return has_msg;
}

/* This type selects whether trace data is present or not (TRACE_DATA_LENGTH = 0).
   Typically, trace data length is 0, when trace is actvated in SHORT mode, or if trace is a void trace
   The selection is copied to every single MCU/Symbian/GSM DSP trace definition, when the trace cointains data
*/
LOCAL pmd_choice* pmd_generate_trace_data_selection(pmd_env* env, unsigned int trc_type, 
                                                    const pmd_typ* trcdata_typ, pmd_mod* module)
{
    /* create CChoice object with default type equal to the actual trace data description */
    pmd_choice* choice = pmd_choice_create(env, "trc_data_sel", trcdata_typ, env->device_id);

    /* set tag to trace data length */
    pmd_tag_init(&choice->tag, env->typ_trace_data_length, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

    /* add choice element [0] -> trcdata_dump */
    pmd_choice_el_add_simple(env, choice, "No data", 0, env->typ_trace_data_dump[trc_type]);
    
    /* add choice object to module */
    pmd_typedef_type_add(module, &choice->constructed.type);

    return choice;
}

LOCAL pmd_typ* pmd_generate_trace_entity_id(pmd_env* env, unsigned int trc_type, unsigned int order, pmd_mod* module)
{
    autogen_it trc_res_it = INIT_ITERATOR;
    pmd_number_pres_cond* pres_cond = NULL;
    autogen_obj* trc_res;

    /* create CNumberType object */
    pmd_number* number = pmd_number_create(env, PMD_TYPE_NAME_TRACE_ENTITY_ID, g_trcgrp_conf[trc_type].entity_size, g_trcgrp_conf[trc_type].entity_special_type);

    /* set order LE */
    if (order == LE)
    {
        pmd_number_set_data_order_little_endian(number);
    }

    /* create CNumberPresentationCondition object with HEX default presentation */
    pres_cond = pmd_number_pres_cond_create(env, pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, ""));

    trc_res_it.flagall     = env->flag_all;
    trc_res_it.typemask    = AUTOGEN_OBJ_RES;
    trc_res_it.subtypemask = g_trcgrp_conf[trc_type].res_type;
    trc_res_it.flagnone    = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

    /* add constant presentation for each trace entity */
    trc_res = autogen_obj_find_in_list(&trc_res_it, g_res_list);
    while (trc_res)
    {
        pmd_number_pres_cond_el_add_simple(env, pres_cond, trc_res->id, trc_res->name);

        trc_res = autogen_obj_find_next_in_list(&trc_res_it);
    }

    /* set final presentation on number */
    if (pres_cond->n_pres_cond_el > 0)
    {
        number->pres = &pres_cond->number_pres;
    }
    else
    {
        number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");
    }

    /* add object to module */
    pmd_typedef_type_add(module, &number->primitive.type);

    return &number->primitive.type;
}

LOCAL pmd_typ* pmd_generate_trace_group_id(pmd_env* env, unsigned int trc_type, unsigned int order, pmd_mod* module)
{
    autogen_trcgrp_conf* trcgrp_conf = &g_trcgrp_conf[trc_type];
    autogen_it trcgrp_it = INIT_ITERATOR;
    autogen_trcgrp* trcgrp;
    pmd_typ* typ_trc_grp_id = NULL;
    pmd_choice* typ_trc_grp_id_entity_sel = NULL;
    unsigned int entity_index;

    /* If entities are supported, generate a choice of trace groups */
    if (trcgrp_conf->entity_size != 0)
    {
        pmd_typ*    typ_trc_entity_id = NULL;
        pmd_typ*    typ_trc_grp_id_def = NULL;

        /* create and add dummy (default) trace group ID */
        typ_trc_grp_id_def = pmd_generate_number_hex_no_reuse(env, PMD_TYPE_NAME_TRACE_GROUP_ID_DEFAULT, trcgrp_conf->group_size, order, module);

        /* create the trace entity ID selection */
        typ_trc_grp_id_entity_sel = pmd_choice_create(env, PMD_TYPE_NAME_TRACE_GROUP_ID_ENTITY_SEL, typ_trc_grp_id_def, env->device_id);
        /* add the trace entity ID selection to the module */
        pmd_typedef_type_add(module, &typ_trc_grp_id_entity_sel->constructed.type);

        /* set trace entity ID as tag */
        typ_trc_entity_id = pmd_typedef_type_lookup(PMD_TYPE_NAME_TRACE_ENTITY_ID, module, TRUE);
        pmd_tag_init(&typ_trc_grp_id_entity_sel->tag, typ_trc_entity_id, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
    }

    /* generate the trace group ID's for each entity */
    for (entity_index = 0; entity_index < trcgrp_conf->n_entities; entity_index++)
    {
        if (!trcgrp_conf->list || !trcgrp_conf->list[entity_index]) continue;

        trcgrp_it.typemask = AUTOGEN_OBJ_TRACEGRP;
        trcgrp_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_TRACEGRP_TEMPORARY_GROUP;

        trcgrp = (autogen_trcgrp*)autogen_obj_find_in_list(&trcgrp_it, trcgrp_conf->list[entity_index]);
        if (trcgrp)
        {
            char varname[255];
            autogen_res* res = (autogen_res*)trcgrp_conf->list[entity_index]->parent;

            /* create and add the trace group ID number */
            sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_GROUP_ID, trcgrp_conf->map[entity_index]);
            typ_trc_grp_id = pmd_generate_number_trace_group_id(env, trc_type, entity_index, varname, order, module);

            /* add trace group ID to entity selection */
            if (typ_trc_grp_id_entity_sel)
            {
                pmd_choice_el_add_simple(env, typ_trc_grp_id_entity_sel, res->base.name, res->base.id, typ_trc_grp_id);
            }
        }
    }

    if (trcgrp_conf->entity_size != 0)
    {
        typ_trc_grp_id = &typ_trc_grp_id_entity_sel->constructed.type;
    }

    /* assure at least default trace group ID */
    if (!typ_trc_grp_id)
    {
        typ_trc_grp_id = pmd_generate_number_hex_no_reuse(env, PMD_TYPE_NAME_TRACE_GROUP_ID_DEFAULT, trcgrp_conf->group_size, order, module);
    }

    return typ_trc_grp_id;
}

LOCAL pmd_typ* pmd_generate_trace_id(pmd_env* env, unsigned int trc_type, unsigned int order, pmd_mod* module)
{
    autogen_trcgrp_conf* trcgrp_conf = &g_trcgrp_conf[trc_type];
    autogen_trcgrp* trcgrp;
    pmd_typ* typ_trc_id_ret = NULL;
    pmd_typ* typ_trc_id_def = NULL;
    pmd_choice* typ_trc_id_entity_sel = NULL;

    /* If entities are supported, generate a choice of trace groups */
    if (trcgrp_conf->entity_size != 0)
    {
        pmd_typ* typ_trc_entity_id = NULL;

        /* create and add dummy (default) trace ID */
        typ_trc_id_def = pmd_generate_number_hex_no_reuse(env, PMD_TYPE_NAME_TRACE_ID_DEFAULT, trcgrp_conf->id_size, order, module);

        /* create the trace ID entity selection */
        typ_trc_id_entity_sel = pmd_choice_create(env, PMD_TYPE_NAME_TRACE_ID_ENTITY_SEL, typ_trc_id_def, env->device_id);

        /* add the trace ID entity selection to the module */
        pmd_typedef_type_add(module, &typ_trc_id_entity_sel->constructed.type);

        /* set trace entity ID as tag */
        typ_trc_entity_id = pmd_typedef_type_lookup(PMD_TYPE_NAME_TRACE_ENTITY_ID, module, TRUE);
        pmd_tag_init(&typ_trc_id_entity_sel->tag, typ_trc_entity_id, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

        /* if LE then set little endian flag */
        if (order == AUTOGEN_DEVICE_ENDIANESS_LE)
        {
            pmd_choice_set_data_order_little_endian(typ_trc_id_entity_sel);
        }

        /* set return type */
        typ_trc_id_ret = &typ_trc_id_entity_sel->constructed.type;
    }

    /* If trace groups are supported, generate trace group ID selections */
    if (trcgrp_conf->group_size != 0)
    {
        unsigned int entity_index;

        /* generate the trace group ID selections for each entity */
        for (entity_index = 0; entity_index < trcgrp_conf->max_entities; entity_index++)
        {
            char varname[255];
            pmd_typ* typ_trc_group_id = NULL;
            pmd_choice* typ_trc_id_grp_sel = NULL;
            autogen_res* res = NULL;
            autogen_it trcgrp_it = INIT_ITERATOR;

            if (!trcgrp_conf->list || !trcgrp_conf->list[entity_index]) continue;

            res = (autogen_res*)trcgrp_conf->list[entity_index]->parent;

            trcgrp_it.typemask = AUTOGEN_OBJ_TRACEGRP;
            trcgrp_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_TRACEGRP_TEMPORARY_GROUP;

            /* find correct trace group ID as tag */
            sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_GROUP_ID, trcgrp_conf->map[entity_index]);
            typ_trc_group_id = pmd_typedef_type_lookup(varname, module, TRUE);

            /* only continue, if trace group was found */
            if (typ_trc_group_id)
            {
                /* create and add dummy (default) trace ID */
                if (!typ_trc_id_def)
                {
                    typ_trc_id_def = pmd_generate_number_hex_no_reuse(env, PMD_TYPE_NAME_TRACE_ID_DEFAULT, trcgrp_conf->id_size, order, module);
                }

                /* create the trace ID group selection */
                sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_ID_GROUP_SEL, trcgrp_conf->map[entity_index]);
                typ_trc_id_grp_sel = pmd_choice_create(env, varname, typ_trc_id_def, env->device_id);

                /* add the trace ID group selection to the module */
                pmd_typedef_type_add(module, &typ_trc_id_grp_sel->constructed.type);

                /* set trace group ID as tag */
                pmd_tag_init(&typ_trc_id_grp_sel->tag, typ_trc_group_id, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

                /* set return value */
                if (!typ_trc_id_ret) 
                {
                    typ_trc_id_ret = &typ_trc_id_grp_sel->constructed.type;
                }

                /* add the trace ID group selection to the trace ID entity selection */
                if (typ_trc_id_entity_sel)
                {
                    pmd_choice_el_add_simple(env, typ_trc_id_entity_sel, res->base.name, res->base.id, &typ_trc_id_grp_sel->constructed.type);
                }

                trcgrp = (autogen_trcgrp*)autogen_obj_find_in_list(&trcgrp_it, trcgrp_conf->list[entity_index]);
                while (trcgrp)
                {
                    /* dont generate trace ID's when DLL direct diversion */
                    if (!trcgrp->dll_name)
                    {
                        pmd_typ* typ_trc_id_number = NULL;

                        /* create and add the trace ID number */
                        sprintf(varname, "%s_%d_%d", PMD_TYPE_NAME_TRACE_ID, trcgrp_conf->map[entity_index], trcgrp->base.id);
                        typ_trc_id_number = pmd_generate_number_trace_id(env, trc_type, trcgrp, varname, order, module);

                        /* add trace ID to trace group selection */
                        pmd_choice_el_add_simple(env, typ_trc_id_grp_sel, trcgrp->base.name, trcgrp->base.id, typ_trc_id_number);
                    }

                    trcgrp = (autogen_trcgrp*)autogen_obj_find_next_in_list(&trcgrp_it);
                }
            }
        }
    }
    /* Else generate plain trace ID's */
    else
    {
        unsigned int entity_index;

        /* generate the trace ID's for each entity */
        for (entity_index = 0; entity_index < trcgrp_conf->n_entities; entity_index++)
        {
            char varname[255];
            pmd_typ* typ_trc_id = NULL;
            autogen_res* res = NULL;

            if (!trcgrp_conf->list || !trcgrp_conf->list[entity_index]) continue;

            res = (autogen_res*)trcgrp_conf->list[entity_index]->parent;

            sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_ID, trcgrp_conf->map[entity_index]);

            /* If trace groups exist, but are not used in decoding (as in OS traces),
               generate trace ID based on all traces in all groups
            */
            if (trcgrp_conf->has_groups)
            {
                pmd_number_pres_cond* pres_cond;
                autogen_it trcgrp_it = INIT_ITERATOR;

                trcgrp_it.typemask = AUTOGEN_OBJ_TRACEGRP;
                trcgrp_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

                typ_trc_id = &pmd_number_create(env, varname, trcgrp_conf->id_size, trcgrp_conf->id_special_type)->primitive.type;

                /* create CNumberPresentationCondition object with HEX default presentation */
                pres_cond = pmd_number_pres_cond_create(env, pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, ""));

                trcgrp = (autogen_trcgrp*)autogen_obj_find_in_list(&trcgrp_it, trcgrp_conf->list[entity_index]);
                while (trcgrp)
                {
                    /* dont add presentations when DLL direct diversion */
                    if (!trcgrp->dll_name)
                    {
                        autogen_seq* trc;
                        autogen_it trc_it = INIT_ITERATOR;

                        trc_it.typemask = AUTOGEN_OBJ_TRACE;
                        trc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

                        trc = (autogen_seq*)autogen_obj_find_in_list(&trc_it, &trcgrp->base.child_list);
                        while (trc)
                        {
                            pmd_number_pres_cond_el_add_simple(env, pres_cond, trc->base.id, trc->base.name);

                            trc = (autogen_seq*)autogen_obj_find_next_in_list(&trc_it);
                        }
                    }

                    trcgrp = (autogen_trcgrp*)autogen_obj_find_next_in_list(&trcgrp_it);
                }

                if (pres_cond->n_pres_cond_el > 0)
                {
                    ((pmd_number*)typ_trc_id)->pres = &pres_cond->number_pres;
                }
                else
                {
                    ((pmd_number*)typ_trc_id)->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");
                }
            }
            else
            {
                typ_trc_id = pmd_generate_trace_id_from_list(env, varname, trcgrp_conf->id_size, trcgrp_conf->list[entity_index], trcgrp_conf->id_special_type);
            }

            pmd_typedef_type_add(module, typ_trc_id);

            /* set return type */
            if (!typ_trc_id_ret)
            {
                typ_trc_id_ret = typ_trc_id;
            }
        }
    }

    /* assure at least default trace ID */
    if (!typ_trc_id_ret)
    {
        typ_trc_id_ret = pmd_generate_number_hex_no_reuse(env, PMD_TYPE_NAME_TRACE_ID_DEFAULT, trcgrp_conf->id_size, order, module);
    }

    return typ_trc_id_ret;
}

LOCAL pmd_typ* pmd_generate_trace_id_from_list(pmd_env* env, const char* name, unsigned int size, autogen_obj_list* trc_list, unsigned int number_special_type)
{
    pmd_number* number;
    pmd_number_pres_cond* pres_cond;

    autogen_obj* trc;
    autogen_it trc_it = INIT_ITERATOR;

    /* create CNumberType object */
    number = pmd_number_create(env, name, size, number_special_type);

    /* create CNumberPresentationCondition object with no default presentation */
    pres_cond = pmd_number_pres_cond_create(env, NULL);

    trc_it.typemask = AUTOGEN_OBJ_TRACE;
    trc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

    trc = autogen_obj_find_in_list(&trc_it, trc_list);
    while (trc)
    {
        pmd_number_pres_cond_el_add_simple(env, pres_cond, trc->id, trc->name);
    
        trc = autogen_obj_find_next_in_list(&trc_it);
    }

    /* set final presentation on number */
    if (pres_cond->n_pres_cond_el > 0)
    {
        number->pres = &pres_cond->number_pres;
    }
    else
    {
        number->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");
    }

    return &number->primitive.type;
}

LOCAL pmd_typ* pmd_generate_trace_group_structure(pmd_env* env, unsigned int trc_type, pmd_mod* module)
{
    char varname[255];
    autogen_it trcgrp_it = INIT_ITERATOR;
    autogen_trcgrp* trcgrp = NULL;
    autogen_trcgrp_conf* trcgrp_conf = &g_trcgrp_conf[trc_type];
    pmd_choice* typ_trc_data_entity_sel = NULL;
    pmd_typ* typ_trc_data = NULL;
    pmd_mod* res_module = NULL;
    unsigned int entity_index;
    unsigned int msgtype_id = 0;
    pmd_msgent* msgent = NULL;
    pmd_entry_point* entry_point = NULL;
    pmd_msgtype* msgtype = NULL;

    if (!trcgrp_conf->list) return NULL;

    /* create resource module for common structures etc. */
    if (module)
    {
        res_module = pmd_typedef_module_add(env, pmd_constant_lookup_message_type_name(trcgrp_conf->msg_type), env->typ_root_module);
    }

    /* create entry point subtree */
    if (module && trcgrp_conf->entity_size != 0 && trcgrp_conf->entry_point_id != 0)
    {
        entry_point = pmd_entry_point_subtree_create(env, trcgrp_conf->entry_point_id, trcgrp_conf->entry_point_info_type_id);
    }

    /* add the trace data length */
    if (module && trcgrp_conf->length_size != 0)
    {
        pmd_typ* typ_trc_data_byte = NULL;

        /* add the trace data byte */
        typ_trc_data_byte = pmd_generate_number_hex_no_reuse(env, PMD_TYPE_NAME_TRACE_DATA_BYTE, 8, BE, res_module);

        /* add the trace data dump */
        env->typ_trace_data_dump[trc_type] =
            pmd_generate_array(env, PMD_TYPE_NAME_TRACE_DATA_DUMP, env->typ_trace_data_length, typ_trc_data_byte, res_module);
    }

    /* add trace entity selection */
    if (module && trcgrp_conf->entity_size != 0)
    {
        pmd_typ* typ_trc_entity_id = NULL;

        /* find trace entity ID */
        typ_trc_entity_id = pmd_typedef_type_lookup(PMD_TYPE_NAME_TRACE_ENTITY_ID, module, TRUE);

        /* create and add the trace data entity selection */
        typ_trc_data_entity_sel = pmd_choice_create(env, PMD_TYPE_NAME_TRACE_DATA_ENTITY_SEL, env->typ_trace_data_dump[trc_type], env->device_id);
        pmd_typedef_type_add(res_module, &typ_trc_data_entity_sel->constructed.type);

        if (entry_point)
        {
            typ_trc_data_entity_sel->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;

            typ_trc_data_entity_sel->entry_point_name = entry_point->name;
            typ_trc_data_entity_sel->entry_point_id   = entry_point->id;
        }

        /* set tag to trace entity ID  */
        pmd_tag_init(&typ_trc_data_entity_sel->tag, typ_trc_entity_id, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
    }

    /* create message type object */
    {
        unsigned short device_id = util_get_res_conf(trcgrp_conf->res_type)->device_id;
        if (device_id == AUTOGEN_DEVICE_CURRENT)
        {
            /* If DSP build, use MCU as device for invariant traces */
            if (trcgrp_conf->res_type == RESOURCE_TRC_INVARIANT && g_autogen_env == AUTOGEN_ENV_PRODUCT_DSP)
            {
                device_id = PN_DEV_HOST;
            }
            else
            {
                device_id = env->device_id;
            }
        }

        msgtype_id = trcgrp_conf->msg_type;
        msgtype = pmd_msgtype_add(env, device_id, msgtype_id, 
                      pmd_constant_lookup_message_type_name(msgtype_id),
                      pmd_constant_lookup_message_type_identifier(msgtype_id),
                      pmd_constant_lookup_message_type_flags(msgtype_id));
    }

    /* generate structure for all entities */
    for (entity_index = 0; entity_index < trcgrp_conf->n_entities; entity_index++)
    {
#if PMD_FILE_FORMAT >= 600
        pmd_mod* trc_grp_mod = NULL;
#endif
        pmd_typ* typ_trc_group_id = NULL;
        pmd_typ* typ_trc_id = NULL;
        pmd_choice* typ_trc_data_grp_sel = NULL;
        pmd_choice* typ_trc_data_trace_sel = NULL;
        autogen_res* res = NULL;
        
        if (!trcgrp_conf->list || !trcgrp_conf->list[entity_index]) continue;

        res = (autogen_res*)trcgrp_conf->list[entity_index]->parent;

        trcgrp_it.typemask = AUTOGEN_OBJ_TRACEGRP;
        trcgrp_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD | AUTOGEN_TRACEGRP_TEMPORARY_GROUP;

        trcgrp = (autogen_trcgrp*)autogen_obj_find_in_list(&trcgrp_it, trcgrp_conf->list[entity_index]);
        if (trcgrp)
        {
            /* create message entity object and group module for the trace type */
            if (trcgrp_conf->entity_size != 0)
            {
                msgent = pmd_msgent_add(env, msgtype, res->base.id, res->base.name, res->logical_name, res->identifier);
#if PMD_FILE_FORMAT >= 600
                if (module)
                {
                    /* add module for containing all trace groups */
                    trc_grp_mod = pmd_typedef_module_add(env, res->base.name, res_module);
                }
            } 
            else
            {
                /* No entity and no group module. All types for the group module are placed on the Symbian trace module (res_module) */
                trc_grp_mod = res_module;
#endif
            }

            /* Create trace group selection for the entity */
            if (module && trcgrp_conf->group_size != 0)
            {
                /* find correct trace group ID */
                sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_GROUP_ID, trcgrp_conf->map[entity_index]);
                typ_trc_group_id = pmd_typedef_type_lookup(varname, module, TRUE);

                if (typ_trc_group_id)
                {
                    /* create and add the trace data group selection */
                    sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_DATA_GROUP_SEL, trcgrp_conf->map[entity_index]);
                    typ_trc_data_grp_sel = pmd_choice_create(env, varname, env->typ_trace_data_dump[trc_type], env->device_id);
#if PMD_FILE_FORMAT >= 600
                    pmd_typedef_type_add(trc_grp_mod, &typ_trc_data_grp_sel->constructed.type);
#else
                    pmd_typedef_type_add(res_module, &typ_trc_data_grp_sel->constructed.type);
#endif

                    /* set relation from message type / entity to PMD object */
                    if (msgent)
                    {
                        msgent->ref_type = &typ_trc_data_grp_sel->constructed.type;
                    }
                    else
                    if (msgtype)
                    {
                        msgtype->ref_type = &typ_trc_data_grp_sel->constructed.type;
                    }

                    /* set trace group ID as tag */
                    pmd_tag_init(&typ_trc_data_grp_sel->tag, typ_trc_group_id, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

                    /* set return type - maybe temporary */
                    typ_trc_data = &typ_trc_data_grp_sel->constructed.type;

                    /* add trace data group selection to trace data entity selection (if it exists) */
                    if (entry_point)
                    {
                        unsigned short device_id = res->device_id;
                        if (device_id == AUTOGEN_DEVICE_CURRENT)
                        {
                            device_id = env->device_id;
                        }

                        pmd_entry_point_subtree_el_add(env, device_id, entry_point, res->base.name, res->base.id, &typ_trc_data_grp_sel->constructed.type);
                    }
                }
            }
            /* If trace groups are not to be decoded, make trace selection instead */
            else if (module)
            {
                /* find trace ID */
                sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_ID, trcgrp_conf->map[entity_index]);
                typ_trc_id = pmd_typedef_type_lookup(varname, module, TRUE);

                if (typ_trc_id)
                {
                    /* create and add trace data trace selection */
                    sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_DATA_TRACE_SEL, trcgrp_conf->map[entity_index]);
                    typ_trc_data_trace_sel = pmd_choice_create(env, varname, env->typ_trace_data_dump[trc_type], env->device_id);
#if PMD_FILE_FORMAT >= 600
                    pmd_typedef_type_add(trc_grp_mod, &typ_trc_data_trace_sel->constructed.type);
#else
                    pmd_typedef_type_add(res_module, &typ_trc_data_trace_sel->constructed.type);
#endif

                    /* set relation from message type / entity to PMD object */
                    if (msgent)
                    {
                        msgent->ref_type = &typ_trc_data_trace_sel->constructed.type;
                    }
                    else 
                    if (msgtype)
                    {
                        msgtype->ref_type = &typ_trc_data_trace_sel->constructed.type;
                    }

                    /* set trace ID as tag */
                    pmd_tag_init(&typ_trc_data_trace_sel->tag, typ_trc_id, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

                    /* set return type - maybe temporary */
                    typ_trc_data = &typ_trc_data_trace_sel->constructed.type;

                    /* add trace data selection to trace data entity selection (if it exists) */
                    if (entry_point)
                    {
                        unsigned short device_id = res->device_id;
                        if (device_id == AUTOGEN_DEVICE_CURRENT)
                        {
                            device_id = env->device_id;
                        }

                        pmd_entry_point_subtree_el_add(env, device_id, entry_point, res->base.name, res->base.id, &typ_trc_data_trace_sel->constructed.type);
                    }
                }
            }
        }
        /* generate structure for all trace groups in entity */
        while (trcgrp)
        {
            autogen_seq* trc;
            autogen_it trc_it = INIT_ITERATOR;
            const char* logical_name = NULL;
            pmd_msggrp* msggrp = NULL;

            /* iterate through traces in the group */
            trc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

            trc = (autogen_seq*)autogen_obj_find_in_list(&trc_it, &trcgrp->base.child_list);

            if (trcgrp_conf->entity_size == 0 && !trcgrp->base.res->conf->is_unique)
            {
                logical_name = trcgrp->base.res->logical_name;
            }

            /* Add message group */
            if (msgent)
            {
                msggrp = pmd_msggrp_trc_add_to_msgent(env, msgent, trcgrp->base.id, trcgrp->identifier, trcgrp->base.name, logical_name ? logical_name : "");
            }
            else 
            if (msgtype)
            {
                msggrp = pmd_msggrp_trc_add_to_msgtype(env, msgtype, trcgrp->base.id, trcgrp->identifier, trcgrp->base.name, logical_name ? logical_name : "");
            }

            /* Set flags */
            if (prop_has(&trcgrp->base, PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE))
            {
                msggrp->namedobj.managedobj.flags |= PMD_TRACE_GROUP_EXCLUDE_FROM_TRACE_ACTIVATION;
            }
            if (prop_has(&trcgrp->base, PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON))
            {
                msggrp->namedobj.managedobj.flags |= PMD_TRACE_DEFAULT_STATE_ON;
            }

            if (module)
            {
                /* if a direct call to a decoder is defined, don't generate any trace ID's */
                if (trcgrp->dll_name && typ_trc_data_grp_sel)
                {
                    /* create block type */
                    pmd_block* block = pmd_block_dll_create(env, trcgrp->base.name, trcgrp->dll_name, trcgrp->func_name);

                    /* set block length */
                    pmd_length_init_as_tag(&block->constructed.length_obj, env->typ_trace_data_length);

                    /* set block flags */
                    block->constructed.type.managedobj.flags |= trcgrp->base.flag;

                    /* add block type to module */
#if PMD_FILE_FORMAT >= 600
                    pmd_typedef_type_add(trc_grp_mod, &block->constructed.type);
#else
                    pmd_typedef_type_add(res_module, &block->constructed.type);
#endif

                    /* add block to trace group selection */
                    pmd_choice_el_add_simple(env, typ_trc_data_grp_sel, trcgrp->base.name, trcgrp->base.id, &block->constructed.type);
                }
                else if (trc)
                {
                    pmd_mod* trc_base_mod = NULL;

                    if (trcgrp_conf->group_size != 0)
                    {
                        /* add module for trace group */
#if PMD_FILE_FORMAT >= 600
                        trc_base_mod = pmd_typedef_module_add(env, trcgrp->base.name, trc_grp_mod);
#else
                        trc_base_mod = pmd_typedef_module_add(env, trcgrp->base.name, res_module);
#endif

                        /* create and add trace data trace selection */
                        sprintf(varname, "%s_%d_%d", PMD_TYPE_NAME_TRACE_DATA_TRACE_SEL, trcgrp_conf->map[entity_index], trcgrp->base.id);
                        typ_trc_data_trace_sel = pmd_choice_create(env, varname, env->typ_trace_data_dump[trc_type], env->device_id);
                        pmd_typedef_type_add(trc_base_mod, &typ_trc_data_trace_sel->constructed.type);

                        /* set relation from trace group to selection object */
                        msggrp->ref_type = &typ_trc_data_trace_sel->constructed.type;

                        /* find trace ID */
                        sprintf(varname, "%s_%d_%d", PMD_TYPE_NAME_TRACE_ID, trcgrp_conf->map[entity_index], trcgrp->base.id);
                    }
                    else
                    {
                        /* set trace base module */
#if PMD_FILE_FORMAT >= 600
                        trc_base_mod = trc_grp_mod;
#else
                        trc_base_mod = res_module;
#endif

                        /* find trace ID */
                        sprintf(varname, "%s_%d", PMD_TYPE_NAME_TRACE_ID, trcgrp_conf->map[entity_index]);
                    }

                    /* find trace ID */
                    typ_trc_id = pmd_typedef_type_lookup(varname, module, TRUE);

                    /* only continue if trace ID is found */
                    if (typ_trc_id)
                    {
                        if (trcgrp_conf->group_size != 0)
                        {
                            /* set tag to trace ID */
                            pmd_tag_init(&typ_trc_data_trace_sel->tag, typ_trc_id, PMD_BIT_POSITION_NOT_SPECIFIED, 0);

                            /* add trace data selection to trace data group selection */
                            pmd_choice_el_add_simple(env, typ_trc_data_grp_sel, trcgrp->base.name, trcgrp->base.id, &typ_trc_data_trace_sel->constructed.type);
                        }

                        while (trc)
                        {
                            pmd_msg* ref_msg = NULL;
                            char msgname[3*AUTOGEN_MAX_NAME_LENGTH + 2];
                            char buffer[3*AUTOGEN_MAX_NAME_LENGTH + 2];
                            int  lgt = 0;

                            /* add module for trace */
                            pmd_mod* trc_mod = pmd_typedef_module_add(env, trc->base.name, trc_base_mod);
                            trc_mod->seq = pmd_seq_create(env, trc_mod->name, PMD_SEQUENCE_TYPE_MESSAGE);
                            trc_mod->seq->org_seq = trc;

                            /* associate TRACE_DATA_LENGTH with sequence */
                            if (trcgrp_conf->length_size != 0)
                            {
                                pmd_length_init_as_tag(&trc_mod->seq->constructed.length_obj, env->typ_trace_data_length);
                            }

                            /* add trace to trace selection */
                            pmd_choice_el_add_simple(env, typ_trc_data_trace_sel, trc->base.name, trc->base.id, 
                                &trc_mod->seq->constructed.type);

                            /* add message object */
                            strncpy(msgname, prop_get_string_default((autogen_obj*)trcgrp, PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT, ""), 3*AUTOGEN_MAX_NAME_LENGTH);
                            lgt = strlen(msgname);
                            strncpy(buffer, prop_get_string((autogen_obj*)trc, PROPERTY_PMD_TRACE_DECODE_TEXT), 3*AUTOGEN_MAX_NAME_LENGTH);
                            if ((strlen(buffer) + lgt) > 3*AUTOGEN_MAX_NAME_LENGTH)
                            {
                                /* Inform about decode text being truncated */
                                printf("Warning: Trace decode text truncated '%s'\n", buffer);
                            }
                            strncat(msgname, buffer, (3*AUTOGEN_MAX_NAME_LENGTH - lgt));

                            ref_msg = pmd_msg_add_to_msggrp(env, msggrp, msgname, trc->base.id, trc_mod->seq);

                            /*  set message flags */
                            if (prop_has(&trc->base, PROPERTY_PMD_MESSAGE_IN_SUMMARY))
                            {
                                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IN_SUMMARY;
                            }
                            if (prop_has(&trc->base, PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE))
                            {
                                ref_msg->namedobj.managedobj.flags |= PMD_TRACE_EXCLUDE_FROM_TRACE_ACTIVATION;
                            }
                            if (prop_has(&trc->base, PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON))
                            {
                                ref_msg->namedobj.managedobj.flags |= PMD_TRACE_DEFAULT_STATE_ON;
                            }
                            if (prop_has(&trc->base, PROPERTY_PMD_MESSAGE_IS_CARRIER))
                            {
                                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IS_CARRIER_MESSAGE;
                            }
                            if (prop_has_valid_string(&trc->base, PROPERTY_PMD_TRACE_IDENTIFIER))
                            {
                                ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_IDENTIFIER;
                                ref_msg->identifier = prop_get_string(&trc->base, PROPERTY_PMD_TRACE_IDENTIFIER);
                            }
                            /* add trace types */
                            if (trc->base.child_list.n_obj > 0)
                            {
                                /* if short mode is not supported, dump items directly */
                                if (!trcgrp_conf->support_short)
                                {
                                    /* add items of trace structure */
                                    pmd_generate_sequence_elements(env, res, &trc->base.child_list, trc_mod, trc_mod, res, ref_msg, NULL, NULL, TRUE);
                                }
                                /* else make selection for TRACE_DATA_LENGTH = 0 */
                                else
                                {
                                    pmd_choice* trcdata_sel = NULL;
                                    pmd_seq_el* trcdata_el = NULL;

                                    /* add module for trace data */ 
                                    pmd_mod* trcdata_mod = pmd_typedef_module_add(env, "trc data", trc_mod);
                                    trcdata_mod->seq = pmd_seq_create(env, trcdata_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

                                    /* add the trace data choice */
                                    trcdata_sel = pmd_generate_trace_data_selection(env, trc_type, 
                                        &trcdata_mod->seq->constructed.type, trc_mod);

                                    trcdata_el = pmd_seq_el_add(env, trc_mod->seq, "Trace data", &trcdata_sel->constructed.type);
                                    trcdata_el->namedobj.managedobj.flags |= PMD_FIELD_IS_PARAMETER;

                                    /* add items of trace structure */
                                    pmd_generate_sequence_elements(env, res, &trc->base.child_list, trcdata_mod, trc_mod, res, ref_msg, NULL, NULL, TRUE);
                                }
                            }
                            /* empty trace */
                            else
                            {
                                pmd_block* block = NULL;

                                /* try hardcoding block */
                                if (!strcmp(trcgrp->base.name, "CC_PDU_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "BuranaDLL.dll", "fnBuranaDecodeCCpdu");
                                }
                                else if (!strcmp(trcgrp->base.name, "MM_PDU_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "BuranaDLL.dll", "fnBuranaDecodeMMpdu");                      
                                }
                                else if (!strcmp(trcgrp->base.name, "RR_PDU_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "BuranaDLL.dll", "fnBuranaDecodeRRpdu");
                                }
                                else if (!strcmp(trcgrp->base.name, "SSCL_PDU_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "BuranaDLL.dll", "fnBuranaDecodeSSCLpdu");
                                }
                                else if (!strcmp(trcgrp->base.name, "SMS_PDU_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "BuranaDLL.dll", "fnBuranaDecodeSMSpdu");
                                }
                                else if (!strncmp(trcgrp->base.name, "ATI_GPRS_", 9))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "GPRSTraceDLL.dll", "fnGPRSDecodeFunc");
                                    block->constructed.type.managedobj.flags |= PMD_BLOCK_EXT_DECODER_SKIP_TRACE_NAME;
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_OVHM_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnACCH_rec_ovhm_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_FOCC_ORDER_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnACCH_rec_order_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_RECC_ORDER_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnACCH_snd_order_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_FVC_ORDER_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnAVCH_rec_order_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_RVC_ORDER_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnAVCH_snd_order_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_FDCCH_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnDCCH_rec_msg_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_RDCCH_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnDCCH_snd_msg_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_FDTCH_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnDTCH_rec_msg_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_RDTCH_MSG_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnDTCH_snd_msg_DecodeFunc");
                                }
                                else if (!strcmp(trcgrp->base.name, "DAMPS_CS_ACTION_TRA"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "TDMAL3DLL.dll", "fnCS_BUF_DecodeFunc");
                                }
                                else if (strstr(trcgrp->base.name, "_TRANSITION_"))
                                {
                                    block = pmd_block_dll_create(env, "trc_block", "BuranaDLL.dll", "fnBuranaDecodeTransitions");
                                    block->constructed.type.managedobj.flags |= PMD_BLOCK_EXT_DECODER_SKIP_IDENTIFIER;
                                }

                                /* if empty trace, add default decoding (hex dump) */
                                if (block)
                                {
                                    pmd_choice* trcdata_sel = NULL;
                                    pmd_seq_el* trcdata_el = NULL;

                                    /* add the trace data choice */ 
                                    trcdata_sel = pmd_generate_trace_data_selection(env, trc_type, &block->constructed.type, trc_mod);

                                    /* set the block length */
                                    pmd_length_init_as_tag(&block->constructed.length_obj, env->typ_trace_data_length);

                                    /* add the block to the module */
                                    pmd_typedef_type_add(trc_mod, &block->constructed.type);

                                    /* add the trace data selection to the sequence */
                                    trcdata_el = pmd_seq_el_add(env, trc_mod->seq, "Trace data", &trcdata_sel->constructed.type);
                                    trcdata_el->namedobj.managedobj.flags |= PMD_FIELD_IS_PARAMETER;

                                }
                                else if (trcgrp_conf->length_size != 0)
                                {
                                    pmd_seq_el* trcdata_el = NULL;

                                    trcdata_el = pmd_seq_el_add(env, trc_mod->seq, "Trace data", env->typ_trace_data_dump[trc_type]);
                                    trcdata_el->namedobj.managedobj.flags |= PMD_FIELD_IS_PARAMETER;
                                }
                            }

                            trc = (autogen_seq*)autogen_obj_find_next_in_list(&trc_it);
                        }
                    }
                }
            }

            trcgrp = (autogen_trcgrp*)autogen_obj_find_next_in_list(&trcgrp_it);
        }
    }

    if (module && trcgrp_conf->entity_size != 0)
    {
        typ_trc_data = &typ_trc_data_entity_sel->constructed.type;
    }

    return typ_trc_data;
}

LOCAL void pmd_generate_trace_structures(pmd_env* env)
{
    unsigned int n;

    for (n = 1; n < AUTOGEN_OBJ_TRACEGRP_MAX; n++)
    {
        if (!g_trcgrp_conf[n].has_groups)
        {
            int bGenerate = FALSE;
            if (env->file_restriction & AUTOGEN_PMD_FILE_RESTRICTION_NON_RD)
            {
                if (g_trcgrp_conf[n].pmd_class & env->file_restriction) bGenerate = TRUE;
            }
            else
            {
                bGenerate = TRUE;
            }

            if (bGenerate == TRUE)
            {
                if (n != AUTOGEN_OBJ_TRACEGRP_MASTER)
                {
                    env->typ_trace_type_entrypoint[n] = pmd_generate_trace_structure(env, n);
                }
            }
        }
    }
}


LOCAL pmd_typ* pmd_generate_trace_structure(pmd_env* env, unsigned int trc_type)
{
    autogen_trcgrp_conf* trcgrp_conf = &g_trcgrp_conf[trc_type];
    pmd_mod* mod = NULL;
    pmd_msgtype* msgtype = NULL;
    pmd_choice* trc_sel = NULL;
    autogen_res* res = util_get_unique_res(trcgrp_conf->res_type);
    autogen_obj* trc = NULL;
    autogen_it trc_it = INIT_ITERATOR;

    if (!trcgrp_conf->list) return NULL;

    /* create module */
    mod = pmd_typedef_module_add(env, pmd_constant_lookup_message_type_name(trcgrp_conf->msg_type), env->typ_root_module);

    trc_it.typemask = AUTOGEN_OBJ_TRACE;
    trc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

    trc = autogen_obj_find_in_list(&trc_it, trcgrp_conf->list[0]);
    if (trc)
    {
        pmd_typ* trc_id_dummy = NULL;

        /* create message type object */
        msgtype = pmd_msgtype_add(env, res->device_id, trcgrp_conf->msg_type, 
            pmd_constant_lookup_message_type_name(trcgrp_conf->msg_type), res->identifier,
            pmd_constant_lookup_message_type_flags(trcgrp_conf->msg_type));

        /* add the trace ID */
        if (trc_type != AUTOGEN_OBJ_TRACEGRP_OS)
        {
            trc_id_dummy = pmd_generate_number_hex_tag(env, trcgrp_conf->id_size, mod);
        }

        /* add the trace ID selection */
        trc_sel = pmd_choice_create(env, "trc_sel", NULL, env->device_id);
        pmd_typedef_type_add(mod, &trc_sel->constructed.type);

        /* If OS traces, trace ID offset varies (because of needed support for message NOS_TRACE. When NOS_TRACE support is removed, this can be removed too */
        {
            pmd_tag_init(&trc_sel->tag, trc_id_dummy, PMD_BIT_POSITION_BEFORE, (unsigned short)(trcgrp_conf->id_size/8));
        }

        /* relate message type with PMD object */
        if (msgtype)
        {
            msgtype->ref_type = &trc_sel->constructed.type;
        }
    }
    while (trc)
    {
        pmd_msg* ref_msg = NULL;

        /* add module for trace */
        pmd_mod* trc_mod = pmd_typedef_module_add(env, trc->name, mod);
        trc_mod->seq = pmd_seq_create(env, trc_mod->name, PMD_SEQUENCE_TYPE_MESSAGE);
        trc_mod->seq->org_seq = (autogen_seq*)trc;

        /* add trace to trace selection */
        pmd_choice_el_add_simple(env, trc_sel, trc->name, trc->id, &trc_mod->seq->constructed.type);

        /* add message object */
        ref_msg = pmd_msg_add_to_msgtype(env, msgtype, trc->name, trc->id, trc_mod->seq);

        /* set message flags */
        if (prop_has(trc, PROPERTY_PMD_MESSAGE_IN_SUMMARY))
        {
            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IN_SUMMARY;
        }
        if (prop_has(trc, PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE))
        {
            ref_msg->namedobj.managedobj.flags |= PMD_TRACE_EXCLUDE_FROM_TRACE_ACTIVATION;
        }
        if (prop_has(trc, PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON))
        {
            ref_msg->namedobj.managedobj.flags |= PMD_TRACE_DEFAULT_STATE_ON;
        }
        if (prop_has(trc, PROPERTY_PMD_MESSAGE_IS_CARRIER))
        {
            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IS_CARRIER_MESSAGE;
        }
        if (prop_has_valid_string(trc, PROPERTY_PMD_TRACE_IDENTIFIER))
        {
            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_IDENTIFIER;
            ref_msg->identifier = prop_get_string(trc, PROPERTY_PMD_TRACE_IDENTIFIER);
        }
        /* add trace types */
        if (trc->child_list.n_obj > 0)
        {
            pmd_generate_sequence_elements(env, res, &trc->child_list, trc_mod, trc_mod, res, ref_msg, NULL, NULL, TRUE);
        }
        /* empty trace */
        else if (env->typ_trace_data_dump[trc_type])
        {
            pmd_seq_el* trcdata_el = NULL;

            trcdata_el = pmd_seq_el_add(env, trc_mod->seq, "Trace data", env->typ_trace_data_dump[trc_type]);
            trcdata_el->namedobj.managedobj.flags |= PMD_FIELD_IS_PARAMETER;
        }

        trc = autogen_obj_find_next_in_list(&trc_it);
    }

    return trc_sel ? &trc_sel->constructed.type : NULL;
}

LOCAL pmd_typ* pmd_generate_trace_structure_dsp5(pmd_env* env, autogen_res* res, unsigned int type, int generate_model)
{
    unsigned int msgtype_id_base[2] = { PMD_MESSAGE_TYPE_DSP5_CDSP_FIRST, PMD_MESSAGE_TYPE_DSP5_ADSP_FIRST };
    unsigned int msgtype_id_org[2] = { PMD_MESSAGE_TYPE_CDSP5_TRACE, PMD_MESSAGE_TYPE_ADSP5_TRACE };
    const char dsp5_names[2][30][28] = 
    {
      { "CDSP Main control",
        "CDSP Core signals",
        "CDSP Application signals",
        "CDSP GSM signals",
        "CDSP Shared signals",
        "CDSP WCDMA signals",
        "CDSP Application traces",
        "CDSP WCDMA algorithm traces",
        "CDSP Shared traces",
        "CDSP GSM Sleep traces",
        "CDSP GSM Common traces",
        "CDSP GSM MDI traces",
        "CDSP GSM Timing traces",
        "CDSP GSM AMR traces",
        "CDSP GSM GPRS traces",
        "CDSP GSM EDGE traces",
        "CDSP GSM RF traces",
        "CDSP traces (18)",
        "CDSP traces (19)",
        "CDSP traces (20)",
        "CDSP traces (21)",
        "CDSP traces (22)",
        "CDSP traces (23)",
        "CDSP traces (24)",
        "CDSP traces (25)",
        "CDSP traces (26)",
        "CDSP traces (27)",
        "CDSP traces (28)",
        "CDSP traces (29)",
        "CDSP traces (30)" },

      { "ADSP Main control",
        "ADSP EAP",
        "ADSP Video",
        "ADSP Audio",
        "ADSP Speech",
        "ADSP MIDI",
        "ADSP Music Enhanced",
        "ADSP Voice UI",
        "ADSP traces (9)",
        "ADSP traces (10)",
        "ADSP traces (11)",
        "ADSP traces (12)",
        "ADSP traces (13)",
        "ADSP traces (14)",
        "ADSP traces (15)",
        "ADSP traces (16)",
        "ADSP traces (17)",
        "ADSP traces (18)",
        "ADSP traces (19)",
        "ADSP traces (20)",
        "ADSP traces (21)",
        "ADSP traces (22)",
        "ADSP traces (23)",
        "ADSP traces (24)",
        "ADSP traces (25)",
        "ADSP traces (26)",
        "ADSP traces (27)",
        "ADSP traces (28)",
        "ADSP traces (29)",
        "ADSP traces (30)" }
    };

    pmd_choice* sb_sel = NULL;
    pmd_typ* sb_id = NULL;
    pmd_typ* rep = NULL;
    pmd_typ* n_sb = NULL;
    autogen_seq* sb = NULL;
    autogen_it sb_it = INIT_ITERATOR;
    pmd_mod* trc_mod = NULL;
    pmd_mod* dsp5_mod = NULL;
    pmd_typ* dsp5_typ = NULL;

    unsigned int msgtype_id         = msgtype_id_org[type];
    unsigned int msgtype_flags      = pmd_constant_lookup_message_type_flags(msgtype_id);
    const char*  msgtype_name       = pmd_constant_lookup_message_type_name(msgtype_id);
    const char*  msgtype_identifier = pmd_constant_lookup_message_type_identifier(msgtype_id);

    /* create module for DSP5 traces */
    if (generate_model)
    {
        dsp5_mod = pmd_typedef_module_add(env, pmd_typedef_module_get_name_from_object(&res->base), env->typ_root_module);
        dsp5_mod->seq = pmd_seq_create(env, dsp5_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

        /* Add number of subblocks (tag) */
        n_sb = pmd_generate_number_dec_no_reuse(env, "trc_n", 16, PMD_NUMBER_SPECIAL_TYPE_NONE, dsp5_mod);

        /* Add subblock ID (tag) */
        sb_id = pmd_generate_number_hex_tag(env, 16, dsp5_mod);

        /* Add subblock selection */
        sb_sel = pmd_choice_create(env, "trc_sel", NULL, env->device_id);

        pmd_typedef_type_add(dsp5_mod, &sb_sel->constructed.type);
    }

    sb_it.typemask = AUTOGEN_OBJ_SB;
    sb_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

    sb = (autogen_seq*)autogen_obj_find_in_list(&sb_it, &res->seq_list);
    while (sb)
    {
        unsigned int msgent_id         = (unsigned int)prop_get_value_default(&sb->base, PROPERTY_PMD_TRACE_SOURCE, PMD_MESSAGE_TYPE_UNDEFINED);
        unsigned int msgent_flags      = (unsigned int)prop_get_value_indexed_default(&g_pmd_environment_variables, PROPERTY_PMD_TRACE_SOURCE_FLAGS, msgent_id, 0);
        const char* msgent_name        = dsp5_names[type][0];
        const char* msgent_identifier  = prop_get_string_indexed_default(&g_pmd_environment_variables, PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER, msgent_id, pmd_constant_lookup_message_type_identifier(msgent_id));
        const char* trc_name           = sb->base.name;
        const char* trc_grp_name       = prop_get_string_default(&sb->base, PROPERTY_PMD_TRACE_ACTIVATION_TEXT, trc_name);
        const char* trc_grp_log_name   = prop_get_string_default(&sb->base, PROPERTY_PMD_TRACE_LOGICAL_GROUP, "");

        pmd_msgtype* msgtype = pmd_msgtype_find(env, res->device_id, msgtype_id);
        pmd_msgent* msgent = NULL;

        if (msgent_id >= msgtype_id_base[type])
        {
            msgent_name = 
                prop_get_string_indexed_default(&g_pmd_environment_variables, 
                PROPERTY_PMD_TRACE_SOURCE_NAME, msgent_id, dsp5_names[type][msgent_id - msgtype_id_base[type]]);
        }
        /* Generate trace for all subblocks but timestamp */
        if (trc_name && trc_name[0])
        {
            pmd_msggrp* msggrp = NULL;
            pmd_seq* trc_mod_seq = NULL;

            if (!strncmp(trc_name, "DSP_SB_", 7))
            {
                trc_name += 7;
            }

            if (!msgtype && msgtype_id != PMD_MESSAGE_TYPE_UNDEFINED)
            {
                msgtype = pmd_msgtype_add(env, res->device_id, msgtype_id, msgtype_name, msgtype_identifier, msgtype_flags | PMD_MESSAGE_TYPE_FLAG_IS_TRACE);
            }
            if (!msgent && msgent_id != PMD_MESSAGE_TYPE_UNDEFINED)
            {
                msgent = pmd_msgent_add(env, msgtype, msgent_id, msgent_name, NULL, msgent_identifier);
                msgent->namedobj.managedobj.flags = msgent_flags | PMD_MESSAGE_ENTITY_FLAG_IS_TRACE;
            }
            /* Generate trace group */
            if (trc_grp_name && trc_grp_name[0])
            {
                if (!strncmp(trc_grp_name, "DSP_SB_", 7))
                {
                    trc_grp_name += 7;
                }

                if (msgent && msgent_id != PMD_MESSAGE_TYPE_UNDEFINED)
                {
                    msggrp = pmd_msggrp_trc_add_to_msgent(env, msgent, sb->base.id, msgent_identifier, trc_grp_name, trc_grp_log_name);
                }
            }

            if (generate_model)
            {
                pmd_msg* ref_msg = NULL;

                /* add module for trace */
                trc_mod = pmd_typedef_module_add(env, sb->base.name, dsp5_mod);
                trc_mod->seq = pmd_seq_create(env, trc_mod->name, PMD_SEQUENCE_TYPE_SUB_BLOCK);
                trc_mod->seq->org_seq = sb;
                trc_mod_seq = trc_mod->seq;

                if (msgent && msgent_id != PMD_MESSAGE_TYPE_UNDEFINED)
                {
                    ref_msg = pmd_msg_add_to_msgent(env, msgent, trc_name, sb->base.id, trc_mod_seq);
                }

                /* set message flags */
                if (ref_msg && prop_has(&sb->base, PROPERTY_PMD_MESSAGE_IN_SUMMARY))
                {
                    ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IN_SUMMARY;
                }
                if (ref_msg && prop_has(&sb->base, PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE))
                {
                    ref_msg->namedobj.managedobj.flags |= PMD_TRACE_EXCLUDE_FROM_TRACE_ACTIVATION;
                }
                if (ref_msg && prop_has(&sb->base, PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON))
                {
                    ref_msg->namedobj.managedobj.flags |= PMD_TRACE_DEFAULT_STATE_ON;
                }
                if (ref_msg && prop_has(&sb->base, PROPERTY_PMD_MESSAGE_IS_CARRIER))
                {
                    ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IS_CARRIER_MESSAGE;
                }
                if (ref_msg && prop_has_valid_string(&sb->base, PROPERTY_PMD_TRACE_IDENTIFIER))
                {
                    ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_IDENTIFIER;
                    ref_msg->identifier = prop_get_string(&sb->base, PROPERTY_PMD_TRACE_IDENTIFIER);
                }
                /* add items of trace structure */
                pmd_generate_sequence_elements(env, res, &sb->base.child_list, trc_mod, trc_mod, res, ref_msg, NULL, NULL, TRUE);

                /* set sequence length reference */
                if (trc_mod->seq->length_type)
                {
                    const autogen_item* length_item = reference_get_special_item(&sb->ref_handle, PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH);

                    pmd_tag_init(&trc_mod->seq->constructed.length_obj.tag, trc_mod->seq->length_type, 
                        PMD_BIT_POSITION_AFTER, (unsigned short)length_item->offset);

                    trc_mod->seq->constructed.length_obj.alg    = PMD_LENGTH_ALGORITHM_N_PLUS_FIXEDLENGTH;
                    trc_mod->seq->constructed.length_obj.length = 0;
                }

                /* add trace subblock to subblock selection */
                pmd_choice_el_add_simple(env, sb_sel, sb->base.name, sb->base.id, &trc_mod->seq->constructed.type);
            }
        }

        sb = (autogen_seq*)autogen_obj_find_next_in_list(&sb_it);
    }

    /* Add subblock repetition */
    if (generate_model)
    {
        pmd_tag_init(&sb_sel->tag, sb_id, PMD_BIT_POSITION_AFTER, 0);

        rep = pmd_generate_array(env, "trc_rep", n_sb, &sb_sel->constructed.type, dsp5_mod);

        pmd_seq_el_add(env, dsp5_mod->seq, "Number of subblocks", n_sb);
        pmd_seq_el_add(env, dsp5_mod->seq, "Subblocks", rep);

        dsp5_typ = &dsp5_mod->seq->constructed.type;
    }

    return dsp5_typ;
}

LOCAL void pmd_generate_trace_structure_master_hw(pmd_env* env)
{
    autogen_it res_it = INIT_ITERATOR;
    autogen_res* res;
    int add_trc = TRUE;

    res_it.flagall     = env->flag_all | AUTOGEN_RES_TRC_IS_HW_MASTER;
    res_it.typemask    = AUTOGEN_OBJ_RES;
    res_it.subtypemask = RESOURCE_TRC_MASTER;


    res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
    while (res)
    {
        pmd_entry_point* entry_point = NULL;

        pmd_msgtype* msgtype = pmd_msgtype_add(env, res->device_id, PMD_MESSAGE_TYPE_MASTER_TRACE,
				    pmd_constant_lookup_message_type_name(PMD_MESSAGE_TYPE_MASTER_TRACE),
				    prop_get_string_default(&res->base, PROPERTY_PMD_TRACE_IDENTIFIER, pmd_constant_lookup_message_type_identifier(PMD_MESSAGE_TYPE_MASTER_TRACE)),
				    pmd_constant_lookup_message_type_flags(PMD_MESSAGE_TYPE_MASTER_TRACE));

        /* Create XTI master entry point */
#if AUTOGEN_XTI_VERSION == AUTOGEN_XTI_V3
        if (!entry_point && strcmp(res->base.name, "MASTER_TRACE"))
        {
            entry_point = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_XTI_MASTER, PMD_INFO_TYPE_XTI_MASTER_IDS);
        }
#endif
        /* create module */
        if (res->trcgrp_list)
        {
            autogen_it trc_it = INIT_ITERATOR;
            autogen_obj* trc;

            pmd_typ* trc_id = NULL;
            pmd_choice* trc_sel = NULL;

            pmd_mod* res_mod = pmd_typedef_module_add(env, res->base.name, env->typ_root_module);

            trc_it.typemask = AUTOGEN_OBJ_TRACE;
            trc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

            trc = autogen_obj_find_in_list(&trc_it, res->trcgrp_list);
            if (trc)
            {
                /* Here we need to keep looping until trace belonging to Master HW trace resource is found or end of list */
                int searching = TRUE;
                while (trc && searching)
                {
                    if (!strcmp(res->base.name, trc->res->base.name))
                    {
                        searching = FALSE;
                        /* add trace ID type */
                        trc_id = pmd_generate_trace_id_from_list(env, PMD_TYPE_NAME_TRACE_ID, 8, res->trcgrp_list, PMD_NUMBER_SPECIAL_TYPE_TRACE_MASTER_ID);
                        pmd_typedef_type_add(res_mod, trc_id);

                        /* add trace selection (= entry point object) */
                        trc_sel = pmd_choice_create(env, PMD_TYPE_NAME_TRACE_DATA_TRACE_SEL, NULL, env->device_id);
                        pmd_typedef_type_add(res_mod, &trc_sel->constructed.type);

                        pmd_tag_init(&trc_sel->tag, trc_id, PMD_BIT_POSITION_BEFORE, 10);

                        /* Add entry point on device for the master hw traces */
                        pmd_entry_point_create(env, res->device_id, "ENTRY_POINT_MASTER_HW_TRACE", PMD_ENTRY_POINT_MASTER_HW_TRACE, &trc_sel->constructed.type);

                        /* On the global XTI master selection, add element */
                        if (entry_point && strcmp(res->base.name, "MASTER_TRACE"))
                        {
                            unsigned short device_id = res->device_id;
                            pmd_block* master_trace_block;
                            master_trace_block = pmd_block_entry_point_create(env, "master_trace_block", "ENTRY_POINT_MASTER_HW_TRACE", PMD_ENTRY_POINT_MASTER_HW_TRACE, res->device_id);

                            pmd_length_init_as_many_as_possible(&master_trace_block->constructed.length_obj, NULL, PMD_LENGTH_ALGORITHM_UNKNOWN);
                            pmd_typedef_type_add(res_mod, &master_trace_block->constructed.type);
                            if (device_id == AUTOGEN_DEVICE_CURRENT)
                            {
                                device_id = env->device_id;
                            }
                            pmd_entry_point_subtree_el_add(env, device_id, entry_point, res->base.name, res->base.id, &master_trace_block->constructed.type);
                        }
                    }
                    else
                    {
                        trc = autogen_obj_find_next_in_list(&trc_it);
                    }
                }
            }
            while (trc && add_trc)
            {
                pmd_msg* ref_msg = NULL;

                if (trc->res->base.flag & AUTOGEN_RES_TRC_IS_HW_MASTER)
                {
                    if (((env->file_restriction_pmd == PMD_FILE_RESTRICTION_RD)) || 
                        ((env->file_restriction_pmd == PMD_FILE_RESTRICTION_RESTRICTED) && (prop_has(trc, PROPERTY_PMD_PUBLIC)|| prop_has(trc, PROPERTY_PMD_RESTRICTED))) ||
                        ((env->file_restriction_pmd == PMD_FILE_RESTRICTION_PUBLIC) && (prop_has(trc, PROPERTY_PMD_PUBLIC))))
                    { 
                        pmd_mod* trc_mod = pmd_typedef_module_add(env, trc->name, res_mod);
                        /* add module for trace */
                        trc_mod->seq = pmd_seq_create(env, trc_mod->name, PMD_SEQUENCE_TYPE_MESSAGE);
                        trc_mod->seq->org_seq = (autogen_seq*)trc;

                        /* add trace to trace selection */
                        pmd_choice_el_add_simple(env, trc_sel, trc->name, trc->id, &trc_mod->seq->constructed.type);

                        /* add message object */
                        ref_msg = pmd_msg_add_to_msgtype(env, msgtype, trc->name, trc->id, trc_mod->seq);

                        /* set message flags */
                        if (prop_has(trc, PROPERTY_PMD_MESSAGE_IN_SUMMARY))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IN_SUMMARY;
                        }
                        if (prop_has(trc, PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_TRACE_EXCLUDE_FROM_TRACE_ACTIVATION;
                        }
                        if (prop_has(trc, PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_TRACE_DEFAULT_STATE_ON;
                        }
                        if (prop_has(trc, PROPERTY_PMD_MESSAGE_IS_CARRIER))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IS_CARRIER_MESSAGE;
                        }
                        if (prop_has_valid_string(trc, PROPERTY_PMD_TRACE_IDENTIFIER))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_IDENTIFIER;
                            ref_msg->identifier = prop_get_string(trc, PROPERTY_PMD_TRACE_IDENTIFIER);
                        }

                        /* add trace types */
                        if (trc->child_list.n_obj > 0)
                        {
                            pmd_generate_sequence_elements(env, res, &trc->child_list, trc_mod, trc_mod, res, ref_msg, NULL, NULL, TRUE);
                        }
                    }
                }
                trc = autogen_obj_find_next_in_list(&trc_it);
            }
        }
        add_trc = FALSE;
        res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
    }
}

LOCAL void pmd_generate_trace_structure_masters(pmd_env* env)
{
    autogen_it res_it = INIT_ITERATOR;
    autogen_res* res;

    res_it.flagall     = env->flag_all;
    res_it.typemask    = AUTOGEN_OBJ_RES;
    res_it.subtypemask = RESOURCE_TRC_MASTER;
    res_it.flagnone    = AUTOGEN_RES_TRC_IS_HW_MASTER; 

    res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
    if (res)
    {
        pmd_entry_point* entry_point = NULL;

        pmd_msgtype* msgtype = pmd_msgtype_add(env, res->device_id, PMD_MESSAGE_TYPE_MASTER_TRACE,
				    pmd_constant_lookup_message_type_name(PMD_MESSAGE_TYPE_MASTER_TRACE),
				    prop_get_string_default(&res->base, PROPERTY_PMD_TRACE_IDENTIFIER, pmd_constant_lookup_message_type_identifier(PMD_MESSAGE_TYPE_MASTER_TRACE)),
				    pmd_constant_lookup_message_type_flags(PMD_MESSAGE_TYPE_MASTER_TRACE));

        /* Create XTI master entry point */
#if AUTOGEN_XTI_VERSION == AUTOGEN_XTI_V3
        if (!entry_point && strcmp(res->base.name, "MASTER_TRACE"))
        {
            entry_point = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_XTI_MASTER, PMD_INFO_TYPE_XTI_MASTER_IDS);
        }
#endif
        /* create module */
        if (res->trcgrp_list)
        {
            autogen_it trc_it = INIT_ITERATOR;
            autogen_obj* trc;

            pmd_typ* trc_id = NULL;
            pmd_choice* trc_sel = NULL;

            pmd_mod* res_mod = pmd_typedef_module_add(env, res->base.name, env->typ_root_module);

            trc_it.typemask = AUTOGEN_OBJ_TRACE;
            trc_it.flagnone = AUTOGEN_OBJ_IS_NOT_GENERATED_PMD;

            trc = autogen_obj_find_in_list(&trc_it, res->trcgrp_list);
            if (trc)
            {
                /* Here we need to keep looping until Master SW trace resource is found or end of list */
                int searching = TRUE;
                while (trc && searching)
                {
                    if (!strcmp(res->base.name, trc->res->base.name))
                    {
                        searching = FALSE;
                        /* add trace ID type */
                        trc_id = pmd_generate_trace_id_from_list(env, PMD_TYPE_NAME_TRACE_ID, 8, res->trcgrp_list, PMD_NUMBER_SPECIAL_TYPE_TRACE_MASTER_ID);
                        pmd_typedef_type_add(res_mod, trc_id);

                        /* add trace selection (= entry point object) */
                        trc_sel = pmd_choice_create(env, PMD_TYPE_NAME_TRACE_DATA_TRACE_SEL, NULL, env->device_id);
                        pmd_typedef_type_add(res_mod, &trc_sel->constructed.type);

                        /* branch on next byte: "Trace type" */
                        pmd_tag_init(&trc_sel->tag, trc_id, PMD_BIT_POSITION_AFTER, 0);
                        /* Add entry point on device for the master sw traces */
                        pmd_entry_point_create(env, res->device_id, "ENTRY_POINT_MASTER_TRACE", PMD_ENTRY_POINT_MASTER_TRACE, &trc_sel->constructed.type);

                        /* On the global XTI master selection, add element */
                        if (entry_point && strcmp(res->base.name, "MASTER_TRACE"))
                        {
                            unsigned short device_id = res->device_id;
                            pmd_block* master_trace_block;
                            master_trace_block = pmd_block_entry_point_create(env, "master_trace_block", "ENTRY_POINT_MASTER_TRACE", PMD_ENTRY_POINT_MASTER_TRACE, res->device_id);
                            pmd_length_init_as_many_as_possible(&master_trace_block->constructed.length_obj, NULL, PMD_LENGTH_ALGORITHM_UNKNOWN);
                            pmd_typedef_type_add(res_mod, &master_trace_block->constructed.type);
                            if (device_id == AUTOGEN_DEVICE_CURRENT)
                            {
                                device_id = env->device_id;
                            }
                            pmd_entry_point_subtree_el_add(env, device_id, entry_point, res->base.name, res->base.id, &master_trace_block->constructed.type);
                        }
                    }
                    else
                    {
                        trc = autogen_obj_find_next_in_list(&trc_it);
                    }
                }
            }
            while (trc)
            {
                pmd_msg* ref_msg = NULL;

                if (!strcmp(res->base.name, trc->res->base.name))
                {
                    if (((env->file_restriction_pmd == PMD_FILE_RESTRICTION_RD)) || 
                        ((env->file_restriction_pmd == PMD_FILE_RESTRICTION_RESTRICTED) && (prop_has(trc, PROPERTY_PMD_PUBLIC)|| prop_has(trc, PROPERTY_PMD_RESTRICTED))) ||
                        ((env->file_restriction_pmd == PMD_FILE_RESTRICTION_PUBLIC) && (prop_has(trc, PROPERTY_PMD_PUBLIC))))
                    { 
                        /* add module for trace */
                        pmd_mod* trc_mod = pmd_typedef_module_add(env, trc->name, res_mod);
                        trc_mod->seq = pmd_seq_create(env, trc_mod->name, PMD_SEQUENCE_TYPE_MESSAGE);
                        trc_mod->seq->org_seq = (autogen_seq*)trc;

                        /* add trace to trace selection */
                        pmd_choice_el_add_simple(env, trc_sel, trc->name, trc->id, &trc_mod->seq->constructed.type);

                        /* add message object */
                        ref_msg = pmd_msg_add_to_msgtype(env, msgtype, trc->name, trc->id, trc_mod->seq);

                        /* set message flags */
                        if (prop_has(trc, PROPERTY_PMD_MESSAGE_IN_SUMMARY))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IN_SUMMARY;
                        }
                        if (prop_has(trc, PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_TRACE_EXCLUDE_FROM_TRACE_ACTIVATION;
                        }
                        if (prop_has(trc, PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_TRACE_DEFAULT_STATE_ON;
                        }
                        if (prop_has(trc, PROPERTY_PMD_MESSAGE_IS_CARRIER))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_IS_CARRIER_MESSAGE;
                        }
                        if (prop_has_valid_string(trc, PROPERTY_PMD_TRACE_IDENTIFIER))
                        {
                            ref_msg->namedobj.managedobj.flags |= PMD_MESSAGE_HAS_IDENTIFIER;
                            ref_msg->identifier = prop_get_string(trc, PROPERTY_PMD_TRACE_IDENTIFIER);
                        }
                        /* add type */
                        pmd_seq_el_add(env, trc_mod->seq, "Trace type", trc_id);

                        /* add trace types */
                        if (trc->child_list.n_obj > 0)
                        {
                            pmd_generate_sequence_elements(env, res, &trc->child_list, trc_mod, trc_mod, res, ref_msg, NULL, NULL, TRUE);
                        }
                    }
                }
                trc = autogen_obj_find_next_in_list(&trc_it);
            }
        }
        res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
    }
    /* Now look for MASTER_HW_TRACES */
    pmd_generate_trace_structure_master_hw(env);
}

LOCAL pmd_typ* pmd_generate_trace_structure_xti_masters_links(pmd_env* env, pmd_mod* seq_mod, pmd_ref* ref_lst)
{
    pmd_choice* trc_master_sel = pmd_choice_create(env, "master sel", NULL, env->device_id);
    pmd_typedef_type_add(seq_mod, &trc_master_sel->constructed.type);

    if (!pmd_tag_init_reference(env, &trc_master_sel->tag, ref_lst, "XTI_MASTER_ID", NULL))
    {
        return NULL;
    }

    trc_master_sel->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;
    trc_master_sel->entry_point_name = "ENTRY_POINT_XTI_MASTER";
    trc_master_sel->entry_point_id   = PMD_ENTRY_POINT_XTI_MASTER;

    return &trc_master_sel->constructed.type;
}

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

void pmd_generate_model(pmd_env* env)
{
    pmd_msgtype* pn_header_msgtype = NULL;
    pmd_mod* pn_mod;
    pmd_mod* pn_data_mod;
    pmd_typ* pn_media;
    autogen_res* res;

    /* add ISI message type */
    pmd_msgtype_add(env, env->device_id, PMD_MESSAGE_TYPE_ISI, 
        pmd_constant_lookup_message_type_name(PMD_MESSAGE_TYPE_ISI),
        pmd_constant_lookup_message_type_identifier(PMD_MESSAGE_TYPE_ISI),
        pmd_constant_lookup_message_type_flags(PMD_MESSAGE_TYPE_ISI));

    /* add the root module */
    pmd_typedef_module_add(env, "Types", NULL);

    /* --------------------------------------------------------------------- */
    /* Generate phonet header */
    /* --------------------------------------------------------------------- */
    pn_mod = pmd_typedef_module_add(env, "PHONET", env->typ_root_module);
    pn_mod->seq = pmd_seq_create(env, pn_mod->name, PMD_SEQUENCE_TYPE_ENTRY_POINT);

    env->typ_pn_root_seq = &pn_mod->seq->constructed.type;

    /* generate entry_point */
    pmd_entry_point_create(env, PMD_DEVICE_GENERAL, "PROTOCOL_PHONET", PMD_PROTOCOL_PHONET, &pn_mod->seq->constructed.type);

    /* add the phonet message */
    pn_header_msgtype = pmd_msgtype_add(env, PMD_DEVICE_GENERAL, PMD_MESSAGE_TYPE_PHONET_HEADER, "PhoNet", "msg", 0);
    pmd_msg_add_to_msgtype(env, pn_header_msgtype, "PhoNet", 0, pn_mod->seq);

    /* media */
    pn_media = pmd_generate_number_pn_const(env, "pn_media", "PN_MEDIA", PMD_NUMBER_SPECIAL_TYPE_PHONET_MEDIA, pn_mod);
    pmd_seq_el_add(env, pn_mod->seq, "Media", pn_media);

    /* receiver device */
    env->typ_pn_receiver_device = pmd_generate_number_pn_const(env, "pn_rcv_dev", "PN_DEVICE", PMD_NUMBER_SPECIAL_TYPE_PHONET_RECEIVER_DEVICE, pn_mod);
    pmd_seq_el_add(env, pn_mod->seq, "Receiver Device", env->typ_pn_receiver_device);

    /* sender device */
    env->typ_pn_sender_device = pmd_generate_number_pn_const(env, "pn_snd_dev", "PN_DEVICE", PMD_NUMBER_SPECIAL_TYPE_PHONET_SENDER_DEVICE, pn_mod);
    pmd_seq_el_add(env, pn_mod->seq, "Sender Device", env->typ_pn_sender_device);

    /* resource */
    env->typ_pn_resource = pmd_generate_number_pn_const(env, "pn_res", "PN_RESOURCE", PMD_NUMBER_SPECIAL_TYPE_PHONET_RESOURCE, pn_mod);
    pmd_seq_el_add(env, pn_mod->seq, "Resource", env->typ_pn_resource);

    /* length */
    env->typ_pn_length = pmd_generate_number_dec_no_reuse(env, "pn_length", 16, PMD_NUMBER_SPECIAL_TYPE_PHONET_LENGTH, pn_mod);
    pmd_seq_el_add(env, pn_mod->seq, "Length", env->typ_pn_length);

    /* PhoNet data sequence */
    pn_data_mod = pmd_typedef_module_add(env, "PhoNet Data", pn_mod);
    pn_data_mod->seq = pmd_seq_create(env, pn_data_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

    pmd_length_init_as_tag(&pn_data_mod->seq->constructed.length_obj, env->typ_pn_length);

    /* PhoNet type selection */
    env->typ_pn_phonet_selection = 
        pmd_generate_pn_phonet_type_selection(env, "pn_type_sel", &pn_data_mod->seq->constructed.type, pn_mod);
    pmd_seq_el_add(env, pn_mod->seq, "Type selection", &env->typ_pn_phonet_selection->constructed.type);

    /* receiver object */
    if (env->file_restriction & AUTOGEN_PMD_FILE_RESTRICTION_NON_RD)
    {
        env->typ_pn_receiver_object = pmd_generate_number_dec_no_reuse(env, "pn_rec_obj", 8,PMD_NUMBER_SPECIAL_TYPE_PHONET_RECEIVER_OBJECT, pn_mod);
    }
    else
    {
        env->typ_pn_receiver_object = pmd_generate_number_pn_object(env, "pn_rec_obj", 8, env->typ_pn_receiver_device, PMD_NUMBER_SPECIAL_TYPE_PHONET_RECEIVER_OBJECT, pn_mod);
    }
    pmd_seq_el_add(env, pn_data_mod->seq, "Receiver Object", env->typ_pn_receiver_object);

    /* sender object */
    if (env->file_restriction & AUTOGEN_PMD_FILE_RESTRICTION_NON_RD)
    {
        env->typ_pn_sender_object = pmd_generate_number_dec_no_reuse(env, "pn_snd_obj", 8, PMD_NUMBER_SPECIAL_TYPE_PHONET_SENDER_OBJECT, pn_mod);
    }
    else
    {
        env->typ_pn_sender_object = pmd_generate_number_pn_object(env, "pn_snd_obj", 8, env->typ_pn_sender_device, PMD_NUMBER_SPECIAL_TYPE_PHONET_SENDER_OBJECT, pn_mod);
    }
    pmd_seq_el_add(env, pn_data_mod->seq, "Sender Object", env->typ_pn_sender_object);

    /* resource selection */
    env->typ_pn_resource_selection = pmd_generate_pn_resource_selection(env, "pn_res_sel", pn_mod);
    pmd_seq_el_add(env, pn_data_mod->seq, "Resource selection", &env->typ_pn_resource_selection->constructed.type);

    /* --------------------------------------------------------------------- */
    /* generate all resource types */
    /* --------------------------------------------------------------------- */

    pmd_generate_resource_type_structures(env, RESOURCE_ISI_SHARED);

	/* Generate DSP traces */
    if (env->file_restriction != AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC)
    {
        /* Add DSP5 CDSP traces */
        res = util_get_unique_res(RESOURCE_TRC_DSP5_CDSP);
        if (res)
        {
            env->typ_res_entrypoint[res->index] = pmd_generate_trace_structure_dsp5(env, res, 0,
                env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD);
        }

        /* Add DSP5 ADSP traces */
        res = util_get_unique_res(RESOURCE_TRC_DSP5_ADSP);
        if (res)
        {
            env->typ_res_entrypoint[res->index] = pmd_generate_trace_structure_dsp5(env, res, 1,
                env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD);
        }
    }

    /* generate trace structures that are entry points */
    pmd_generate_trace_structures(env);

    {
        autogen_it res_it = INIT_ITERATOR;

        res_it.typemask = AUTOGEN_OBJ_RES;

        /* generate private ISI resources */
        res_it.flagall     = env->flag_all;
        res_it.subtypemask = RESOURCE_ISI_PRIVATE;

        res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        while (res)
        {
            pmd_typ* msg_sel = pmd_generate_resource_structure(env, res, NULL);

            /* add message selection to private resource selection */
            if (msg_sel)
            {
                if (!env->typ_pn_private_selection)
                {
                    /* generate private resource selection */
                    env->typ_pn_private_selection = pmd_generate_choice_forward(env, "pn_private_res_sel", 16, 2, pn_mod);
                    env->typ_pn_private_selection->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;

                    env->typ_pn_private_selection->entry_point_name = "ENTRY_POINT_PN_PRIVATE";
                    env->typ_pn_private_selection->entry_point_id   = PMD_ENTRY_POINT_PN_PRIVATE;

                    /* add private resource selection to phonet resource selection */
                    {
                        pmd_entry_point* ep = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_PN_RESOURCE, PMD_INFO_TYPE_PN_RESOURCES);
                        pmd_entry_point_subtree_el_add(env, PMD_DEVICE_GENERAL, ep, "PN_PRIVATE", PN_PRIVATE, &env->typ_pn_private_selection->constructed.type);
                    }
                }

                {
                    pmd_entry_point* ep = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_PN_PRIVATE, PMD_INFO_TYPE_PRIVATE_IDS);
                    unsigned short device_id = res->device_id;
                    if (device_id == AUTOGEN_DEVICE_CURRENT)
                    {
                        device_id = env->device_id;
                    }

                    pmd_entry_point_subtree_el_add(env, device_id, ep, res->base.name, res->base.id, msg_sel);
                }
            }

            res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
        }

        /* generate prefix ISI resources */
        res_it.flagall     = env->flag_all;
        res_it.subtypemask = RESOURCE_ISI_PREFIX;

        res = (autogen_res*)autogen_obj_find_in_list(&res_it, g_res_list);
        while (res)
        {
            pmd_typ* msg_sel = pmd_generate_resource_structure(env, res, NULL);

            /* add message selection to prefix resource selection */
            if (msg_sel)
            {
                if (!env->typ_pn_prefix_selection)
                {
                    /* generate prefix resource selection */
                    env->typ_pn_prefix_selection = pmd_generate_choice_forward(env, "pn_prefix_res_sel", 16, 2, pn_mod);

                    env->typ_pn_prefix_selection->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;

                    env->typ_pn_prefix_selection->entry_point_name      = "ENTRY_POINT_PN_PREFIX";
                    env->typ_pn_prefix_selection->entry_point_id        = PMD_ENTRY_POINT_PN_PREFIX;

                    /* add private resource selection to phonet resource selection */
                    {
                        pmd_entry_point* ep = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_PN_RESOURCE, PMD_INFO_TYPE_PN_RESOURCES);
                        pmd_entry_point_subtree_el_add(env, PMD_DEVICE_GENERAL, ep, "PN_PREFIX", PN_PREFIX, &env->typ_pn_prefix_selection->constructed.type);
                    }
                }

                {
                    pmd_entry_point* ep = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_PN_PREFIX, PMD_INFO_TYPE_RESOURCE_IDS);
                    unsigned short device_id = res->device_id;
                    if (device_id == AUTOGEN_DEVICE_CURRENT)
                    {
                        device_id = env->device_id;
                    }

                    pmd_entry_point_subtree_el_add(env, device_id, ep, res->base.name, res->base.id, msg_sel);
                }
            }

            res = (autogen_res*)autogen_obj_find_next_in_list(&res_it);
        }
    }

    /* Generate trace masters */
    pmd_generate_trace_structure_masters(env);

    /* generate other resources */
    pmd_generate_resource_type_structures(env, RESOURCE_ISI);
    pmd_generate_resource_type_structures(env, RESOURCE_ISI_DSP);
    pmd_generate_resource_type_structures(env, RESOURCE_PHONET);
    pmd_generate_resource_type_structures(env, RESOURCE_PHONET_EXT);
    pmd_generate_resource_type_structures(env, RESOURCE_ISI_MEDIA_CONTROL);

    /* add MM specific message to media controller */
    res = util_get_unique_res(RESOURCE_ISI_MEDIA_CONTROL);
    if (res && env->typ_res_entrypoint[res->index] && ((res->base.flag & env->flag_all) == env->flag_all))
    {
        pmd_generate_media_controller_structure(env, res);
    }

    /* add STI traces to PN_TRACEBOX */
#ifdef PN_TRACEBOX
    res = util_get_res(PN_TRACEBOX);
#else
    res = util_get_res(PN_OSTRICH);
#endif /* PN_TRACEBOX */
    if (res && env->typ_res_entrypoint[res->index] && ((res->base.flag & env->flag_all) == env->flag_all))
    {
        pmd_generate_sti_trace_structure(env, res);
    }

    pmd_generate_resource_type_structures(env, RESOURCE_PROTOCOL);

    /* add X-file entry point */
#ifdef AUTOGEN_INCLUDE_X_FILE
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD)
    {
        pmd_block* xfile_block = pmd_block_create(env, "xfile_block", BLOCK_X_FILE);
        pmd_length_init_as_many_as_possible(&xfile_block->constructed.length_obj, NULL, PMD_LENGTH_ALGORITHM_AS_MANY_AS_POSSIBLE);

        pmd_typedef_type_add(pn_mod, &xfile_block->constructed.type);

        pmd_entry_point_create(env, PMD_DEVICE_GENERAL, "PROTOCOL_X_FILE", PMD_PROTOCOL_X_FILE, &xfile_block->constructed.type);
    }
#endif

    /* add trace information (for trace activation) */
    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED)
    {
        unsigned int n;

        for (n = 1; n < AUTOGEN_OBJ_TRACEGRP_MAX; n++)
        {
            /* don't add for trace types, which have already been added with decoding */
            if (g_trcgrp_conf[n].has_groups && (g_trcgrp_conf[n].pmd_class & env->flag_all) != env->flag_all)
            {
                pmd_generate_trace_group_structure(env, n, NULL);
            }
        }
    }

    /* add OST */
#ifdef AUTOGEN_INCLUDE_OST
    pmd_generate_ost(env);
#endif
}

#ifdef AUTOGEN_INCLUDE_OST
LOCAL void pmd_generate_ost(pmd_env* env)
{
    pmd_msgtype      *ost_msgtype        = NULL;
    pmd_msgtype      *ost_header_msgtype = NULL;

    pmd_mod          *ost_base_protocol_mod;

    pmd_number       *ost_version;
    pmd_number       *ost_entity_id;
    pmd_number       *ost_protocol_id;
    pmd_typ          *ost_length;

    pmd_choice       *ost_length_selection;
    pmd_mod          *ost_length_sel_default_mod;
    pmd_mod          *ost_length_sel_0_mod;

    pmd_entry_point  *ost_protocol_ep;

    /* Add OST message type */
    ost_msgtype = pmd_msgtype_add(env, env->device_id, PMD_MESSAGE_TYPE_OST,
        pmd_constant_lookup_message_type_name(PMD_MESSAGE_TYPE_OST),
        pmd_constant_lookup_message_type_identifier(PMD_MESSAGE_TYPE_OST),
        pmd_constant_lookup_message_type_flags(PMD_MESSAGE_TYPE_OST));

    /* Create module for OST base protocol. Child of root module */
    ost_base_protocol_mod = pmd_typedef_module_add(env, "OST", env->typ_root_module);

    /* Create sequence associated with module */
    ost_base_protocol_mod->seq = pmd_seq_create(env, ost_base_protocol_mod->name, PMD_SEQUENCE_TYPE_ENTRY_POINT);

    /* Define entrypoint for protocol OST */
    pmd_entry_point_create(env, PMD_DEVICE_GENERAL, "PROTOCOL_OST", PMD_PROTOCOL_OST, &ost_base_protocol_mod->seq->constructed.type);

    /* Add the OST dummy message type and message */
    ost_header_msgtype = pmd_msgtype_add(env, PMD_DEVICE_GENERAL, PMD_MESSAGE_TYPE_OST_HEADER, "OST", "msg", 0);
    pmd_msg_add_to_msgtype(env, ost_header_msgtype, "OST", 0, ost_base_protocol_mod->seq);

    /* Create the Version field and add to sequence. */
    /* Decoding of version numbers looked up in table SYMBOLS_OST_VERSION in RESOURCE_SYMBOLS */
    ost_version = pmd_number_create(env, "ost_version", 8, PMD_NUMBER_SPECIAL_TYPE_OST_VERSION);
    ost_version->pres = pmd_generate_presentation_from_table(env, util_get_unique_res(RESOURCE_SYMBOLS), AUTOGEN_TBL_CONST_ANY, "SYMBOLS_OST_VERSION", 0, AUTOGEN_OBJ_ANY, 0);
    {
        /* Compute and set default version for the Version field */
        const char *default_version = "OST_BASE_PROTOCOL_VERSION_1";   /* Default value to be used */

        /* Look up SYMBOLS_OST_VERSION table in RESOURCE_SYMBOLS */
        autogen_tbl *tbl;
        autogen_it tbl_it = INIT_ITERATOR;

        tbl_it.typemask    = AUTOGEN_OBJ_TBL;
        tbl_it.subtypemask = AUTOGEN_TBL_CONST_ANY;
        tbl_it.obj.name    = "SYMBOLS_OST_VERSION";

        tbl = (autogen_tbl *)autogen_obj_find_in_list(&tbl_it, &(util_get_unique_res(RESOURCE_SYMBOLS)->tbl_list));
        if (tbl)
        {
            /* Look up the selected default value in the table */
            autogen_it entry_it = INIT_ITERATOR;
            autogen_obj* entry  = NULL;

            entry_it.obj.name = default_version;
            entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
            if (entry)
            {
                /* Set default version on the ost version field */
                pmd_number_set_default_value(env, ost_version, entry->id, entry->name);
            }
        }
    }
    pmd_typedef_type_add(ost_base_protocol_mod, &ost_version->primitive.type);
    pmd_seq_el_add(env, ost_base_protocol_mod->seq, "Version", &ost_version->primitive.type);

    /* Create the Entity ID field and add to sequence */
    ost_entity_id = pmd_number_create(env, "ost_entity_id", 8, PMD_NUMBER_SPECIAL_TYPE_OST_ENTITY_ID);
    ost_entity_id->pres = pmd_number_pres_simple_create(env, PMD_VALUE_PRESENTATION_HEX, "");
    {
        /* Compute and set default value */
        pmd_number_set_default_value(env, ost_entity_id, 0x00, "0");
    }
    pmd_typedef_type_add(ost_base_protocol_mod, &ost_entity_id->primitive.type);
    pmd_seq_el_add(env, ost_base_protocol_mod->seq, "Entity ID", &ost_entity_id->primitive.type);

    /* Create the Protocol ID field and add to sequence */
    ost_protocol_id = pmd_number_create(env, "ost_protocol_id", 8, PMD_NUMBER_SPECIAL_TYPE_OST_PROTOCOL_ID);
    ost_protocol_id->pres = pmd_number_pres_info_create(env, PMD_INFO_TYPE_OST_PROTOCOL_IDS, PMD_DEVICE_GENERAL, NULL);
    {
        /* Compute and set default value */
        pmd_number_set_default_value(env, ost_protocol_id, 0x84, "132");    /* OST_XTIv3 (0x84) protocol */
    }
    pmd_typedef_type_add(ost_base_protocol_mod, &ost_protocol_id->primitive.type);
    pmd_seq_el_add(env, ost_base_protocol_mod->seq, "Protocol ID", &ost_protocol_id->primitive.type);

    /* Create the Length field and add to sequence */
    ost_length = pmd_generate_number_dec_no_reuse(env, "ost_length", 8, PMD_NUMBER_SPECIAL_TYPE_OST_LENGTH_SHORT, ost_base_protocol_mod);
    pmd_seq_el_add(env, ost_base_protocol_mod->seq, "Length", ost_length);

    /* Create a selection on the Length field.       */
    /* Choices: 0       = Use Extended Length field. */
    /*          Default = No Extended Length field   */

    /* Choice default : Contains the Protocol selection (No Extended Length field) */
    {
        pmd_choice *ost_protocol_selection;

        /* Create module and sequence to contain the default choice */
        ost_length_sel_default_mod = pmd_typedef_module_add(env, "OST Short", ost_base_protocol_mod);
        ost_length_sel_default_mod->seq = pmd_seq_create(env, ost_length_sel_default_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

        /* Create resource selection which chooses between upper layer protocols as defined in OST resources (RESOURCE_OST) */
        /* Create choice element for selection and set tag to point to Protocol ID */
        ost_protocol_selection = pmd_choice_create(env, "ost_protocol_selection", NULL, env->device_id);
        pmd_typedef_type_add(ost_length_sel_default_mod, &ost_protocol_selection->constructed.type);
        pmd_tag_init(&ost_protocol_selection->tag, &ost_protocol_id->primitive.type, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
        pmd_seq_el_add(env, ost_length_sel_default_mod->seq, "Protocol", &ost_protocol_selection->constructed.type);

        /* Setup entrypoint subtree on the above selection */
        ost_protocol_selection->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;
        ost_protocol_selection->entry_point_name = "ENTRY_POINT_OST_PROTOCOL";
        ost_protocol_selection->entry_point_id   = PMD_ENTRY_POINT_OST_PROTOCOL;
    }

    /* Choice 0 : Contains Extended Length field and Protocol selection */
    {
        pmd_typ    *ost_ext_length;
        pmd_choice *ost_protocol_selection;

        /* Create module and sequence to contain the 0 length choice */
        ost_length_sel_0_mod = pmd_typedef_module_add(env, "OST Long", ost_base_protocol_mod);
        ost_length_sel_0_mod->seq = pmd_seq_create(env, ost_length_sel_0_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

        /* Create the Extended Length field */
        ost_ext_length = pmd_generate_number_dec_no_reuse(env, "ost_ext_length", 32, PMD_NUMBER_SPECIAL_TYPE_OST_LENGTH_EXTENDED, ost_length_sel_0_mod);
        ost_ext_length->managedobj.flags |= PMD_TYPE_DATA_ORDER_LITTLE_ENDIAN;
        pmd_seq_el_add(env, ost_length_sel_0_mod->seq, "Extended Length", ost_ext_length);

        /* Create resource selection which chooses between upper layer protocols as defined in OST resources (RESOURCE_OST) */
        /* Create choice element for selection and set tag to point to Protocol ID */
        ost_protocol_selection = pmd_choice_create(env, "ost_protocol_selection", NULL, env->device_id);
        pmd_typedef_type_add(ost_length_sel_0_mod, &ost_protocol_selection->constructed.type);
        pmd_tag_init(&ost_protocol_selection->tag, &ost_protocol_id->primitive.type, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
        pmd_seq_el_add(env, ost_length_sel_0_mod->seq, "Protocol", &ost_protocol_selection->constructed.type);

        /* Setup entrypoint subtree on the above selection */
        ost_protocol_selection->constructed.type.managedobj.flags |= PMD_CHOICE_ENTRY_POINT;
        ost_protocol_selection->entry_point_name = "ENTRY_POINT_OST_PROTOCOL";
        ost_protocol_selection->entry_point_id   = PMD_ENTRY_POINT_OST_PROTOCOL;
    }

    /* Selection on the Length field - Uses the above choice definitions */
    ost_length_selection = pmd_choice_create(env, "ost_length_selection", &ost_length_sel_default_mod->seq->constructed.type, env->device_id);
    pmd_typedef_type_add(ost_base_protocol_mod, &ost_length_selection->constructed.type);
    pmd_tag_init(&ost_length_selection->tag, ost_length, PMD_BIT_POSITION_NOT_SPECIFIED, 0);
    pmd_seq_el_add(env, ost_base_protocol_mod->seq, "Extended Length Selection", &ost_length_selection->constructed.type);

    /* Add choice 0 */
    pmd_choice_el_add_simple(env, ost_length_selection, "Extended Length", 0, &ost_length_sel_0_mod->seq->constructed.type);

    /* Create entry point */
    ost_protocol_ep = pmd_entry_point_subtree_create(env, PMD_ENTRY_POINT_OST_PROTOCOL, PMD_INFO_TYPE_OST_PROTOCOL_IDS);

    /* Loop through all OST resources (RESOURCE_OST) and hook them up on the protocol selection entrypoint */
    {
        autogen_it ost_res_it = INIT_ITERATOR;
        autogen_res* ost_res;

        ost_res_it.flagall     = env->flag_all;
        ost_res_it.typemask    = AUTOGEN_OBJ_RES;
        ost_res_it.subtypemask = RESOURCE_OST;

        /* Find all RESOURCE_OST from global resource list */
        ost_res = (autogen_res*)autogen_obj_find_in_list(&ost_res_it, g_res_list);
        if (ost_res)
        {
            pmd_msgtype* msgtype = pmd_msgtype_add(env, ost_res->device_id, PMD_MESSAGE_TYPE_OST,
					    pmd_constant_lookup_message_type_name(PMD_MESSAGE_TYPE_OST),
					    prop_get_string_default(&ost_res->base, PROPERTY_PMD_TRACE_IDENTIFIER, pmd_constant_lookup_message_type_identifier(PMD_MESSAGE_TYPE_OST)),
					    pmd_constant_lookup_message_type_flags(PMD_MESSAGE_TYPE_OST));

            /* Loop though all RESOURCE_OST resources */
            while (ost_res)
            {
                if (prop_has(&ost_res->base, PROPERTY_PROTOCOL_HAS_NO_MESSAGES) && ost_res->msg_list.n_obj)
                {
                    /* Create module to contain the resource */
                    pmd_mod* res_mod = pmd_typedef_module_add(env, pmd_typedef_module_get_name_from_object(&ost_res->base), ost_base_protocol_mod);
                    res_mod->seq = pmd_seq_create(env, res_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

                    /* Add items of "dummy" message */
                    pmd_generate_sequence_elements(env, ost_res, 
                                                   &autogen_obj_get_first_in_list(&ost_res->msg_list)->child_list, 
                                                   res_mod, res_mod, ost_res, NULL, NULL, NULL, TRUE);

                    /* Add resource to entry point subtree resource selection */
                    pmd_entry_point_subtree_el_add(env, PMD_DEVICE_GENERAL, ost_protocol_ep, ost_res->base.name, ost_res->base.id, &res_mod->seq->constructed.type);
                }
                else
                {
                    /* Generate resouce */
                    pmd_typ* msg_sel = pmd_generate_resource_structure(env, ost_res, msgtype);
                    if (msg_sel)
                    {
                        /* Add resource to entry point subtree resource selection */
                        pmd_entry_point_subtree_el_add(env, PMD_DEVICE_GENERAL, ost_protocol_ep, ost_res->base.name, ost_res->base.id, msg_sel);
                    }
                }

                /* Next OST resource */
                ost_res = (autogen_res*)autogen_obj_find_next_in_list(&ost_res_it);
            }
        }
    }
}
#endif

/* End of file output_pmd_generate.c */
