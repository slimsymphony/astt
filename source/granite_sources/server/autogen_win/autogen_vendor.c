/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_vendor.c
                ----------------
                SW Module






Project:          autogen

%name:            autogen_vendor.c %
%version:         12 %
%instance:        co1tss_1 %
%derived_by:      nosterga %
%date_modified:   Tue Jun 08 16:47:59 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the source code for the chipset supplier xml description.

    This supports the following functionality:
    * Add trace activation of vendor traces to PMD file
    * Add decoding support for vendor traces to PMD file. Vendor traces are rerouted
      to a vendor DLL as specified in the Chipset Supplier Description
    * CrashDumps are read from the Chipset Supplier Description and stored in the PMD file.

    The XML schema for the chipset supplier description can be found in the file 
    ChipsetSupplierDescription.xsd.

*/


/* ============================================================================================= */
/* Includes                                                                                      */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_object.h"
#include "autogen_util.h"
#include "autogen_parsexml.h"

#include "pmdconstants.h"
#include "pmd_compression2.h"
#include "pmd_heap.h"

#include "output_pmd.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ============================================================================================= */
/* Locals                                                                                        */
/* ============================================================================================= */

#ifdef AUTOGEN_INCLUDE_VENDOR_DLL_TRACE
#ifdef AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION

#ifndef LOCAL
#define LOCAL static
#endif /* LOCAL */

/* Define the Resource Trace Master name used to look up the master traces in decoding tree */
#ifndef AUTOGEN_VENDOR_DLL_TRACE_DEC_RES_TRC_MASTER
#define AUTOGEN_VENDOR_DLL_TRACE_DEC_RES_TRC_MASTER "MASTER_TRACE"
#endif

/* Define the Vendor DLL Trace name used to look up the vendor dll traces in decoding tree */
#ifndef AUTOGEN_VENDOR_DLL_TRACE_DEC_VENDOR_DLL
#define AUTOGEN_VENDOR_DLL_TRACE_DEC_VENDOR_DLL "MASTER_VENDOR_DLL_TRACE"
#endif

LOCAL int autogen_getChipsetSupplierDescription(pmd_env *env, xml_element *csd_ptr, int *chipsetsupplierid, char **chipsetsuppliername);
LOCAL int autogen_getTraceVersionMask(pmd_env *env, xml_element *tm_child_ptr, int chipsetsupplierid);
LOCAL int autogen_getTraceCategory(pmd_env* env, xml_element *tm_child_ptr, int chipsetsupplierid, char *chipsetsuppliername, int file_restriction);
LOCAL int autogen_getCrashDump(pmd_env *env, xml_element *csd_child_ptr, int chipsetsupplierid, const char *chipsetsuppliername);
LOCAL int autogen_validate_pmd_structure(pmd_env *env);
LOCAL int autogen_add_vendor_decoding(pmd_env *env, const char *name, int id, const char *suppliername, const char *dll, const char *dllvermajor, const char *dllverminor, const char *function);
LOCAL int autogen_validate_DLL_Version(const char *major, const char *minor);

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_import_chipset_supplier_description
 
    Description: 
        Import chipset supplier description from xml file.
        Add appropriate PMD structures to PMD file.
 
    Arguments: 
        env              [in] - PMD environment
        xml_filename     [in] - Filename for xml file containing chipset supplier description.
        file_restriction [in] - Kind of PMD file: RnD, Restricted or Public

    Return
        None
*/
/* --------------------------------------------------------------------------------------------- */
void autogen_import_chipset_supplier_description(pmd_env *env, const char *xml_filename, int file_restriction)
{
    char *xmldata = NULL;
    xml_element *xml = NULL;
    xml_element *ptr = NULL;
    int chipsetsupplierid = 0;
    char *chipsetsuppliername = NULL;
    int errorcode = 0;

    const char *base_filename = util_get_filename(xml_filename);
    printf("- Importing Chipset Supplier Description '%s'\n", (base_filename == NULL ? xml_filename : base_filename));

    /* Read chipset supplier xml document */
    xmldata = parsexml_readfile(xml_filename, &errorcode);
    if (xmldata == NULL)
    {
        /* Error */
        printf("Error finding file '%s'\n", xml_filename);
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, "Chipset Supplier Description: %s", (char *)parsexml_get_error_text(errorcode));
        return;
    }

    /* Parse the xml document */
    xml = parsexml_parse(xmldata, &errorcode);
    if (xml == NULL)
    {
        /* Error */
        free(xmldata);

        printf("Error parsing chipset supplier description xml\n");
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, "Chipset Supplier Description: %s", (char *)parsexml_get_error_text(errorcode));
        return;
    }

    /* xmldata not needed anymore */
    free(xmldata);

    /* Get children of root element */
    ptr = xml->children_head;

    /*************************************/
    /* Validate that PMD structure is OK */
    /*************************************/
    if (autogen_validate_pmd_structure(env))
    {
        /* Error occurred */
        parsexml_free_element(xml);
        return;
    }

    /*************************************/
    /* Find <ChipsetSupplierDescription> */
    /*************************************/
    if (autogen_getChipsetSupplierDescription(env, ptr, &chipsetsupplierid, &chipsetsuppliername))
    {
        /* Error occurred */
        parsexml_free_element(xml);
        return;
    }

    /*****************************/
    /* Find optional <TraceMask> */
    /*****************************/
    {
        xml_element *tm_ptr = parsexml_find_element_tag(ptr->children_head, "TraceMask");
        if (tm_ptr != NULL)
        {
            /* <TraceMask> is present */

            /**********************************/
            /* Get optional <TraceVersionMask */
            /**********************************/
            if (autogen_getTraceVersionMask(env, tm_ptr->children_head, chipsetsupplierid))
            {
                /* Error occurred */
                parsexml_free_element(xml);
                return;
            }

            /************************************/
            /* Loop through all <TraceCategory> */
            /************************************/
            if (autogen_getTraceCategory(env, tm_ptr->children_head, chipsetsupplierid, chipsetsuppliername, file_restriction))
            {
                /* Error occurred */
                parsexml_free_element(xml);
                return;
            }
        }
    }

    /********************************/
    /* Loop through all <CrashDump> */
    /********************************/
    if (autogen_getCrashDump(env, ptr->children_head, chipsetsupplierid, chipsetsuppliername))
    {
        /* Error occurred */
        parsexml_free_element(xml);
        return;
    }

    parsexml_free_element(xml);
    return;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_getChipsetSupplierDescription
 
    Description: 
        Get all relevant data related to the <autogen_getChipsetSupplierDescription> tag.
 
    Arguments: 
        env [in]                  - PMD environment
        csd_ptr [in]              - Pointes to the first xml element of the xml file.
        chipsetsupplierid [out]   - Returns the value of attribute ChipsetSupplierId.
        chipsetsuppliername [out] - Returns the value of attribute ChipsetSupplierName.

    Return
        0 : No errors
        1 : Error encountered. Error message already printed out.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int autogen_getChipsetSupplierDescription(pmd_env *env, xml_element *csd_ptr, int *chipsetsupplierid, char **chipsetsuppliername)
{
    *chipsetsupplierid = 0;

    /* Check if <ChipsetSupplierDescription> is present */
    csd_ptr = parsexml_find_element_tag(csd_ptr, "ChipsetSupplierDescription");
    if (csd_ptr == NULL)
    {
        /* Not found */
        printf("Error in structure of chipset supplier description xml\n");
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
            "Chipset Supplier Description: <ChipsetSupplierDescription> tag is missing");
        return 1;
    }

    /* Get ChipsetSupplierId attribute */
    {
        const char *csd_chipsetsupplierid = parsexml_find_attribute(csd_ptr->attributes_head, "ChipsetSupplierId");

        /* Check mandatory attribute */
        if (csd_chipsetsupplierid == NULL)
        {
            /* Error - missing attributes */
            printf("Error in structure of chipset supplier description xml\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Mandatory attribute (ChipsetSupplierId) is missing in <ChipsetSupplierDescription>");
            return 1;
        }

        /* Return the found value */
        *chipsetsupplierid = atoi(csd_chipsetsupplierid);
    }

    /* Get ChipsetSupplierName attribute */
    {
        const char *csd_chipsetsuppliername = parsexml_find_attribute(csd_ptr->attributes_head, "ChipsetSupplierName");

        /* Check mandatory attribute */
        if (csd_chipsetsuppliername == NULL)
        {
            /* Error - missing attributes */
            printf("Error in structure of chipset supplier description xml\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Mandatory attribute (ChipsetSupplierName) is missing in <ChipsetSupplierDescription>");
            return 1;
        }

        /* Return the found value */
        *chipsetsuppliername = pmd_heap_strdup_h(env->heap_handle, csd_chipsetsuppliername);
    }

    /* No errors */
    return 0;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_getTraceVersionMask
 
    Description: 
        Get all relevant data related to the <TraceVersionMask> tag and child elements.
 
    Arguments: 
        tm_child_ptr [in]             - Pointes to the first child element of the <TraceMask> where <TraceVersionMask> is
                                        an optional child element of.
        chipsetsupplierid [in]        - Chipset supplier Id

    Return
        0 : No errors
        1 : Error encountered. Error message already printed out.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int autogen_getTraceVersionMask(pmd_env *env, xml_element *tm_child_ptr, int chipsetsupplierid)
{
    static int info_obj_counter = 0;

    /* Max number of <Byte> elements allowed */
    #define MAX_N_BYTE 8

    /* Storage of the <Byte> values */
    int trace_version_mask[MAX_N_BYTE] = {0, 0, 0, 0, 0, 0, 0, 0};

    /* Check if <TraceVersionMask> is present */
    xml_element *ptr = parsexml_find_element_tag(tm_child_ptr, "TraceVersionMask");
    if (ptr != NULL)
    {
        /* <TraceVersionMask> is present */

        /***************************/
        /* Loop through all <Byte> */
        /***************************/
        int n_trace_version_mask = 0;
        ptr = parsexml_find_element_tag(ptr->children_head, "Byte");
        while (ptr && n_trace_version_mask < MAX_N_BYTE)
        {
            /* Get Value attribute */
            const char *byte_value = parsexml_find_attribute(ptr->attributes_head, "Value");

            /* Check mandatory attribute */
            if (byte_value == NULL)
            {
                /* Error - missing attributes */
                printf("Error in structure of chipset supplier description xml\n");
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                    "Chipset Supplier Description: Mandatory attribute is missing in <Byte>");
                return 1;
            }
            trace_version_mask[(n_trace_version_mask)++] = atoi(byte_value);

            /* Find next <Byte> */
            ptr = parsexml_find_element_tag(ptr->next, "Byte");
        }

        /* Check if more <Byte> tags are left. In this case there are more than allowed. */
        if (ptr != NULL)
        {
            /* Error - Too many <Byte> */
            printf("Error in structure of chipset supplier description xml\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Too many <Byte> tags.");
            return 1;
        }

        /* Store the trace version mask in an info object in the PMD model */
        {
            unsigned int data1 = 0;
            unsigned int data2 = 0;

            data1 = (    0 + trace_version_mask[0]) << 8;
            data1 = (data1 + trace_version_mask[1]) << 8;
            data1 = (data1 + trace_version_mask[2]) << 8;
            data1 = (data1 + trace_version_mask[3]);

            data2 = (    0 + trace_version_mask[4]) << 8;
            data2 = (data2 + trace_version_mask[5]) << 8;
            data2 = (data2 + trace_version_mask[6]) << 8;
            data2 = (data2 + trace_version_mask[7]);

            /* Add Info object with trace version mask */
            pmd_info_add(env, env->device_id, PMD_INFO_TYPE_VENDOR_TRACE_VERSION_MASK, 
                NULL, info_obj_counter++, 
                4, chipsetsupplierid, n_trace_version_mask, data1, data2);
        }
    }

    /* No errors */
    return 0;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_getTraceCategory
 
    Description: 
        Get all relevant data related to the <TraceCategory> tag and child elements.
 
    Arguments: 
        env [in]                 - PMD environment      
        tm_child_ptr [in]        - Pointes to the first child element of the <TraceMask> where <TraceCategory> is
                                   an optional child element of.
        chipsetsupplierid [in]   - Chipset supplier Id
        chipsetsuppliername [in] - Chipset supplier Name
        file_restriction [in]    - Kind of PMD file: RnD, Restricted or Public

    Return
        0 : No errors
        1 : Error encountered. Error message already printed out.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int autogen_getTraceCategory(pmd_env* env, xml_element *tm_child_ptr, int chipsetsupplierid, char *chipsetsuppliername, int file_restriction)
{
    /* Check if <TraceCategory> is present */
    xml_element *ptr = parsexml_find_element_tag(tm_child_ptr, "TraceCategory");
    while (ptr)
    {
        /* Found a <TraceCategory> */
        pmd_msgtype *msgtype;
        pmd_msgent  *msgent;

        xml_element *tgb_ptr = NULL;

        /* Get relevant attributes on the <TraceCategory> */
        const char *tc_name        = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "Name"));
        const char *tc_logicalname = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "LogicalName"));
        const char *tc_id          = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "Id"));
        const char *tc_restriction = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "Restriction"));
        const char *tc_dll         = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "DLLName"));
        const char *tc_dllvermajor = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "DLLVersionMajor"));
        const char *tc_dllverminor = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "DLLVersionMinor"));
        const char *tc_function    = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "Function"));

        int tc_restriction_enum = AUTOGEN_PMD_FILE_RESTRICTION_RD;

        /* Check for mandatory attributes */
        if (tc_name == NULL        || tc_logicalname == NULL || tc_id == NULL          || 
            tc_restriction == NULL || tc_dll == NULL         || tc_function == NULL)
        {
            /* Error - missing attributes */
            printf("Error in structure of chipset supplier description xml\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Mandatory attribute is missing in <TraceCategory>");
            return 1;
        }

        /* Check the enumerated value in Restriction */
        if (strcmp(tc_restriction, "RD") == 0)
        {
            tc_restriction_enum = AUTOGEN_PMD_FILE_RESTRICTION_RD;
        }
        else if (strcmp(tc_restriction, "Restricted") == 0)
        {
            tc_restriction_enum = AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED;
        }
        else if (strcmp(tc_restriction, "Public") == 0)
        {
            tc_restriction_enum = AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC;
        }
        else 
        {
            /* Error in enumerated value */
            printf("Error in structure of chipset supplier description xml\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Attribute Restriction only accepts: RD, Restricted or Public");
            return 1;
        }

        /* Check the version number in DLLVersionMajor and DLLVersionMinor if present. Must be 3 decimal digits */
        if (tc_dllvermajor != NULL && tc_dllverminor != NULL) 
        {
            if (autogen_validate_DLL_Version(tc_dllvermajor, tc_dllverminor))
            {
                printf("Error in structure of chipset supplier description xml\n");
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                    "Chipset Supplier Description: Attributes DLLVersionMajor and DLLVersionMinor must be exact 3 decimal digits");
                return 1;
            }
        }
        else if ((tc_dllvermajor != NULL) != (tc_dllverminor != NULL))
        {
            /* Either both major and minor version must be set or both must not be set */
            printf("Error in structure of chipset supplier description xml\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Either both attributes DLLVersionMajor and DLLVersionMinor are set or both are not set");
            return 1;
        }

        /* Got the <TraceCategory> attributes */

        /* Create the trace activation if the restrictions are OK. If not then skip this <TraceCategory> */
        if ((file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC     && tc_restriction_enum == AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC) ||
            (file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED && tc_restriction_enum != AUTOGEN_PMD_FILE_RESTRICTION_RD)     ||
            (file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD))
        {
            unsigned int chipsetsupplierid_trccatid = 0;
            char entityname[AUTOGEN_MAX_NAME_LENGTH*2+2];

            /* Restriction rules fulfilled */
            /* Create a message type */
            msgtype = pmd_msgtype_add(env, env->device_id, PMD_MESSAGE_TYPE_VENDOR_DLL_TRACE, 
                AUTOGEN_VENDOR_DLL_TRACE_TYPE_NAME, AUTOGEN_VENDOR_IDENTIFIER, PMD_MESSAGE_TYPE_FLAG_IS_TRACE);

            /* Compute concatenated chipset supplier id (top 16 bit) and trace catetory id (lower 16 bit) */
            chipsetsupplierid_trccatid = ((chipsetsupplierid & 0xffff) << 16) + (atoi(tc_id) & 0xffff);

            /* Compute entity name */
            sprintf(entityname, "%.*s_%.*s", AUTOGEN_MAX_NAME_LENGTH, chipsetsuppliername, AUTOGEN_MAX_NAME_LENGTH, tc_name);

            /* Create an associated message entity */
            msgent = pmd_msgent_add(env, msgtype, chipsetsupplierid_trccatid, entityname, tc_logicalname, "");

            /************************************/
            /* Loop through all <TraceGroupBit> */
            /************************************/
            {
                tgb_ptr = parsexml_find_element_tag(ptr->children_head, "TraceGroupBit");
                if (tgb_ptr == NULL)
                {
                    /* Error - At least one <TraceGroupBit> expected */
                    printf("Error in structure of chipset supplier description xml\n");
                    util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                        "Chipset Supplier Description: One or more <TraceGroupBit> expected");
                    return 1;
                }

                while (tgb_ptr)
                {
                    pmd_msggrp *msggrp; 

                    /* Found <TraceGroupBit> - Find the relevant attributes */
                    const char *tgb_name        = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(tgb_ptr->attributes_head, "Name"));
                    const char *tgb_logicalname = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(tgb_ptr->attributes_head, "LogicalName"));
                    const char *tgb_id          = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(tgb_ptr->attributes_head, "Id"));

                    if (tgb_name == NULL || tgb_logicalname == NULL || tgb_id == NULL)
                    {
                        /* Error - missing attributes */
                        printf("Error in structure of chipset supplier description xml\n");
                        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                            "Chipset Supplier Description: Mandatory attribute is missing in <TraceGroupBit>");
                        return 1;
                    }

                    /* Got the <TraceGroupBit> attributes */

                    /* Create a trace message group */
                    msggrp = pmd_msggrp_trc_add_to_msgent(env, msgent, atoi(tgb_id), AUTOGEN_VENDOR_IDENTIFIER, tgb_name, tgb_logicalname);

                    /* Next <TraceGroupBit> */
                    tgb_ptr = parsexml_find_element_tag(tgb_ptr->next, "TraceGroupBit");
                }
            }

            /* Add decoding of vendor traces to the PMD decoding tree */
            if (autogen_add_vendor_decoding(env, tc_name, chipsetsupplierid_trccatid, 
                                            chipsetsuppliername, tc_dll, tc_dllvermajor, tc_dllverminor, tc_function))
            {
                /* Error */
                return 1;
            }
        }

        /* Find next <TraceCategory> */
        ptr = parsexml_find_element_tag(ptr->next, "TraceCategory");
    }

    /* No errors */
    return 0;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_getCrashDump
 
    Description: 
        Get all relevant data related to the <CrashDump> tags.
 
    Arguments: 
        env [in]               - PMD environment      
        csd_child_ptr [in]     - Pointes to the first child element of the <ChipsetSupplierDescription> where <CrashDump> is
                                 an optional child element of.
        chipsetsupplierid [in] - Chipset supplier Id

    Return
        0 : No errors
        1 : Error encountered. Error message already printed out.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int autogen_getCrashDump(pmd_env *env, xml_element *csd_child_ptr, int chipsetsupplierid, const char *chipsetsuppliername)
{
    /* Check if <CrashDump> is present */
    xml_element *ptr = parsexml_find_element_tag(csd_child_ptr, "CrashDump");
    while (ptr)
    {
        char dll_name[AUTOGEN_MAX_NAME_LENGTH*2+20];
        char function_name[AUTOGEN_MAX_NAME_LENGTH+1];
        unsigned int info_obj_id = 0;

        /* Found a <CrashDump> */

        /* Get relevant attributes on the <CrashDump> */
        const char *cd_id           = parsexml_find_attribute(ptr->attributes_head, "Id");
        const char *cd_dll          = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "DLLName"));
        const char *cd_dllvermajor  = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "DLLVersionMajor"));
        const char *cd_dllverminor  = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "DLLVersionMinor"));
        const char *cd_functionname = pmd_heap_strdup_h(env->heap_handle, parsexml_find_attribute(ptr->attributes_head, "Function"));

        /* Check for mandatory attributes */
        if (cd_id == NULL || cd_dll == NULL || cd_functionname == NULL)
        {
            /* Error - missing attributes */
            printf("Error in structure of chipset supplier description xml\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Mandatory attribute is missing in <CrashDump>");
            return 1;
        }

        /* Check the version number in DLLVersionMajor and DLLVersionMinor if present. Must be 3 decimal digits */
        if (cd_dllvermajor != NULL && cd_dllverminor != NULL)
        {
            if (autogen_validate_DLL_Version(cd_dllvermajor, cd_dllverminor))
            {
                printf("Error in structure of chipset supplier description xml\n");
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                    "Chipset Supplier Description: Attributes DLLVersionMajor and DLLVersionMinor must be exact 3 decimal digits");
                return 1;
            }
        }
        else if ((cd_dllvermajor != NULL) != (cd_dllverminor != NULL))
        {
            /* Either both major and minor version must be set or both must not be set */
            printf("Error in structure of chipset supplier description xml\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Either both attributes DLLVersionMajor and DLLVersionMinor are set or both are not set");
            return 1;
        }

        /* Prepare DLL file name - Must be <supplier name>_<dll name>_<major version>_<minor version>.dll. Version info optional */
        if (cd_dllvermajor == NULL || cd_dllverminor == NULL) 
        {
            /* No major / minor version */
            sprintf(dll_name, "%.*s_%.*s.dll", AUTOGEN_MAX_NAME_LENGTH, chipsetsuppliername, AUTOGEN_MAX_NAME_LENGTH, cd_dll);
        }
        else
        {
            /* Version info included */
            sprintf(dll_name, "%.*s_%.*s_%.3s_%.3s.dll", AUTOGEN_MAX_NAME_LENGTH, chipsetsuppliername, AUTOGEN_MAX_NAME_LENGTH, cd_dll, cd_dllvermajor, cd_dllverminor);
        }

        /* Compute info object id as concatenated chipset supplier id (top 16 bit) and crash dump id (lower 16 bit) */
        info_obj_id = ((chipsetsupplierid & 0xffff) << 16) + (atoi(cd_id) & 0xffff);

        /* Store the <CrashDump> DLL information in an info object in PMD */
        pmd_info_add(env, PMD_DEVICE_GENERAL, PMD_INFO_TYPE_VENDOR_CRASH_DUMP, 
            dll_name, info_obj_id, 
            3, chipsetsupplierid, atoi(cd_id), info_obj_id, 0);

        /* Store the <CrashDump> functioname information in an info object in PMD */
        /* Must be prepended with 'fn' and appended with 'Trace' */
        sprintf(function_name, "fn%.*sTrace", AUTOGEN_MAX_NAME_LENGTH-7, cd_functionname);
        pmd_info_add(env, PMD_DEVICE_GENERAL, PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME, 
            function_name, info_obj_id, 
            2, chipsetsupplierid, info_obj_id, 0, 0);

        /* Find next <CrashDump> */
        ptr = parsexml_find_element_tag(ptr->next, "CrashDump");
    }

    /* No errors */
    return 0;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_validate_pmd_structure
 
    Description: 
        Validates that the PMD structure where the decoding is dynamically added is present in the PMD data structures.
        Looks for the following typedef modules:
            The resource trace master
            Master vendor DLL trace

        Checks that the choice 'trccat_choice' where the choice elements are dynamically added is present
 
    Arguments: 
        env [in]               - PMD environment  

    Return
        0 : No errors
        1 : Error encountered. 
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int autogen_validate_pmd_structure(pmd_env *env)
{
    pmd_mod    *mod_master_trace            = NULL;
    pmd_mod    *mod_master_vendor_dll_trace = NULL;
    pmd_choice *choice                      = NULL;

    /* Find the Resource Trace Master module as a child of the root module 'Types' */
    mod_master_trace = pmd_typedef_module_lookup(AUTOGEN_VENDOR_DLL_TRACE_DEC_RES_TRC_MASTER, env->typ_root_module);
    if (mod_master_trace == NULL)
    {
        /* Error - No MASTER_TRACE module */
        printf("Resource Trace Master definition '%s' not found.\n", AUTOGEN_VENDOR_DLL_TRACE_DEC_RES_TRC_MASTER);
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
            "Chipset Supplier Description: Resource Trace Master definition '%s' not found",
            AUTOGEN_VENDOR_DLL_TRACE_DEC_RES_TRC_MASTER);
        return 1;
    }

    /* Find the MASTER_VENDOR_DLL_TRACE module as child of MASTER_TRACE */
    mod_master_vendor_dll_trace = pmd_typedef_module_lookup(AUTOGEN_VENDOR_DLL_TRACE_DEC_VENDOR_DLL, mod_master_trace);
    if (mod_master_vendor_dll_trace == NULL)
    {
        /* Error - No MASTER_VENDOR_DLL_TRACE module */
        printf("Master vendor dll traces definition '%s' not found.\n", AUTOGEN_VENDOR_DLL_TRACE_DEC_VENDOR_DLL);
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
            "Chipset Supplier Description: Master vendor dll traces definition '%s' not found",
            AUTOGEN_VENDOR_DLL_TRACE_DEC_VENDOR_DLL);
        return 1;
    }

    /* Find choice element */
    choice = (pmd_choice *)pmd_typedef_type_lookup("trccat_choice", mod_master_vendor_dll_trace, FALSE);
    if (choice == NULL)
    {
        /* Error - Choice not found */
        printf("Internal error - trccat_choice not found\n");
        util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_ALL, 0, 
            "Chipset Supplier Description: Internal error - trccat_choice not found");
        return 1;
    }

    /* No errors */
    return 0;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_add_vendor_decoding
 
    Description: 
        Add decoding of vendor traces to the PMD decoding tree
 
    Arguments: 
        env [in]               - PMD environment  
        name [in]              - Name of the trace category. Used as name in the decoding hierarchy.
        id [in]                - Combined chipset supplier id and trace category id
        suppliername [in]      - Chipset supplier name
        dll [in]               - Name of DLL.
        dllvermajor [in]       - Major version number of DLL file
        dllverminor [in]       - Minor version number of DLL file
        function [in]          - Function name to call on DLL

    Return
        0 : No errors
        1 : Error encountered. Error message already printed out.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int autogen_add_vendor_decoding(pmd_env *env, const char *name, int id, const char *suppliername, const char *dll, const char *dllvermajor, const char *dllverminor, const char *function)
{
    pmd_mod *mod_master_trace            = NULL;
    pmd_mod *mod_master_vendor_dll_trace = NULL;

    /* Find the Resource Trace Master module as a child of the root module 'Types' */
    mod_master_trace = pmd_typedef_module_lookup(AUTOGEN_VENDOR_DLL_TRACE_DEC_RES_TRC_MASTER, env->typ_root_module);
    if (mod_master_trace == NULL)
    {
        /* Error - No MASTER_TRACE module */
        /* Should not occure as this should have been checked before calling this function */
        return 1;
    }

    /* Find the MASTER_VENDOR_DLL_TRACE module as child of MASTER_TRACE */
    mod_master_vendor_dll_trace = pmd_typedef_module_lookup(AUTOGEN_VENDOR_DLL_TRACE_DEC_VENDOR_DLL, mod_master_trace);
    if (mod_master_vendor_dll_trace == NULL)
    {
        /* Error - No MASTER_VENDOR_DLL_TRACE module */
        /* Should not occure as this should have been checked before calling this function */
        return 1;
    }

    /* Insert a choice case containing a block into the choice present in MASTER_VENDOR_DLL_TRACE */
    {
        char case_name[AUTOGEN_MAX_NAME_LENGTH+1];
        char dll_name[AUTOGEN_MAX_NAME_LENGTH*2+20];
        char function_name[AUTOGEN_MAX_NAME_LENGTH+1];
        pmd_mod* case_mod;
        pmd_block *block;
        pmd_choice *choice;

        /* Create a presentation name for the choice case */
        sprintf(case_name, "%.*s-%d-%d", AUTOGEN_MAX_NAME_LENGTH-12, name, (id >> 16), (id & 0xffff));

        /* Create module to contain the sequence. Module inserted as child of MASTER_VENDOR_DLL_TRACE */
        case_mod = pmd_typedef_module_add(env, case_name, mod_master_vendor_dll_trace);

        /* Create sequence to contain the block */
        case_mod->seq = pmd_seq_create(env, case_mod->name, PMD_SEQUENCE_TYPE_ANONYMOUS);

        /* Prepare DLL file name - Must be <supplier name>_<dll name>_<major version>_<minor version>.dll. Version info optional */
        if (dllvermajor == NULL || dllverminor == NULL) 
        {
            /* No major / minor version */
            sprintf(dll_name, "%.*s_%.*s.dll", AUTOGEN_MAX_NAME_LENGTH, suppliername, AUTOGEN_MAX_NAME_LENGTH, dll);
        }
        else
        {
            /* Version info included */
            sprintf(dll_name, "%.*s_%.*s_%.3s_%.3s.dll", AUTOGEN_MAX_NAME_LENGTH, suppliername, AUTOGEN_MAX_NAME_LENGTH, dll, dllvermajor, dllverminor);
        }

        /* Prepare DLL function name - Must be prepended with 'fn' and appended with 'Trace' */
        sprintf(function_name, "fn%.*sTrace", AUTOGEN_MAX_NAME_LENGTH-7, function);

        /* Create a block */
        block = pmd_block_dll_create(env, name, dll_name, function_name);
        if (block)
        {
            /* Set length on block */
            pmd_length_init_as_many_as_possible(&block->constructed.length_obj, case_mod->seq, PMD_LENGTH_ALGORITHM_UNKNOWN);

            /* Add block type to module */
            pmd_typedef_type_add(case_mod, &block->constructed.type);

            /* Add block to sequence */
            pmd_seq_el_add(env, case_mod->seq, name, &block->constructed.type);
        }
        else
        {
            /* Error - no block created */
            printf("Error adding decoding support for chipset supplier traces\n");
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0, 
                "Chipset Supplier Description: Error adding decoding support for chipset supplier traces");
            return 1;
        }

        /* Set length information on sequence */
        pmd_length_init_as_many_as_possible(&case_mod->seq->constructed.length_obj, case_mod->seq, PMD_LENGTH_ALGORITHM_NOT_SPECIFIED);

        /* Find choice element */
        choice = (pmd_choice *)pmd_typedef_type_lookup("trccat_choice", mod_master_vendor_dll_trace, FALSE);
        if (choice == NULL)
        {
            /* Error - Choice not found */
            /* Should not occure as this should have been checked before calling this function */
            return 1;
        }

        /* Add the case element to the choice */
        pmd_choice_el_add_simple(env, choice, pmd_heap_strdup_h(env->heap_handle, case_name), id, &case_mod->seq->constructed.type);
    }

    /* No errors */
    return 0;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: autogen_validate_DLL_Version
 
    Description: 
        Check that the major and minor part of the version number is correct formatted.
 
    Arguments: 
        major [in]             - Major part of DLL version number. Must be 3 decimal digits.  
        minor [in]             - Minor part of DLL version number. Must be 3 decimal digits.

    Return
        0 : No errors
        1 : Error encountered.
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int autogen_validate_DLL_Version(const char *major, const char *minor)
{
    int i = 0;

    /* Validate that number is 3 digits long */
    if (major == NULL || minor == NULL || strlen(major) != 3 || strlen(minor) != 3)
    {
        /* Error in version number */
        return 1;
    }

    /* Validate that number is decimal */
    for(i=0; i<3; i++)
    {
        if (!isdigit(major[i]) || !isdigit(minor[i]))
        {
            /* Error in version number */
            return 1;
        }
    }

    /* No errors */
    return 0;
}

#endif /* AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION */
#endif /* AUTOGEN_INCLUDE_VENDOR_DLL_TRACE */
