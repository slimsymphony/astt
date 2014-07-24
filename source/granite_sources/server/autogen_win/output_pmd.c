/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                output_pmd.c
                ------------
                SW Module






Project:          autogen

%name:            output_pmd.c %
%version:         co1tss#207 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 12:03:30 2011 %

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
#include "autogen_object.h"
#include "autogen_prop.h"
#include "autogen_util.h"
#include "autogen_parsexml.h"

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

#ifdef _MSC_VER
 #include <direct.h>
#endif

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL
#endif /* LOCAL */

#ifdef _MSC_VER /* We use strict ANSI option, where chdir, mkdir, and getcwd are not declared */
 #define chdir _chdir
 #define getcwd _getcwd
 #define mkdir _mkdir
#endif /* _MSV_VER */

#ifndef PMD_FILE_NAME
 #ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
  #define PMD_FILE_NAME "product"
 #elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_DSP)
  #define PMD_FILE_NAME "dsp"
 #elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_ADSP)
  #define PMD_FILE_NAME "adsp"
 #elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN)
  #define PMD_FILE_NAME "symbian"
 #elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE)
  #define PMD_FILE_NAME "device"
 #else
  #define PMD_FILE_NAME "local"
 #endif /* AUTOGEN_ENVIRONMENT_XXX */
#endif

/*  This structure contains the information about a PMD object, such as
    PMD_CLASS_NUMBER_PRESENTATION_CONSTANT. A list of certain types of PMD 
    objects is built
*/
typedef struct t_pmd_object
{
    /* pointer to the next pmd object */
    struct t_pmd_object* next;

    /* assigned id and class of the object */
    unsigned int object_id;
    unsigned int object_class;

    /* a string to contain class specific data */
    const char* string;

    /* radix */
    unsigned int radix;

} pmd_object;

/* */
typedef struct t_pmd_const_reuse
{
    /* resource for which this list relates to */
    autogen_res* res;

    /* pointer to next sequence in this resource list */
    struct t_pmd_const_reuse* child;

    /* pointer to list of next resource */
    struct t_pmd_const_reuse* next;

    /* name of constant */
    const char* constname;

    /* object / class  id of constant presentation */
    unsigned int   object_id;
    unsigned short class_id;
} pmd_const_reuse;

/* list of objects for reuse */
LOCAL pmd_object*       s_reused_objects = NULL;
LOCAL pmd_const_reuse*  s_pmd_reused_const = NULL;

LOCAL void          pmd_write_asc_header(pmd_env* env, FILE* fpmd, const char* mcuswversion);
LOCAL void          pmd_write_bin_header(FILE* fpmd);
LOCAL void          pmd_write_xml_header(pmd_env* env, FILE* fpmd, const char* mcuswversion);
LOCAL void          pmd_write_cpmd(pmd_env* env, int normal_file);
LOCAL void          pmd_write_parameters(pmd_env* env);

LOCAL void          pmd_file_generate(OutFilenames *out_filenames, int file_restriction, int include_debug);
LOCAL void          pmd_file_generate_output_buffer(pmd_env* env);
LOCAL void          pmd_file_generate_copy(const char* src_filename, const char* dest_filename, long filesize);
LOCAL void          pmd_file_generate_name(pmd_env* env, char* str_filename, char* str_version);

LOCAL void          pmd_file_write(pmd_env* env, const char* filename, const char* version_str);

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

#if (defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU && !defined _MSC_VER)
  extern const char *const dev_sw_version;
#else
  const char* const dev_sw_version = "XXXX";
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

/* Stores the current working directory when autogen starts up */
extern char working_dir[]; 

/* --------------------------------------------------------------------------------------------- */
/*  Name: output_pmd
 
    Purpose: 
        The main function that generates the PMD file
 
    Functional Description:
        Builds a data model of PMD objects and then writes the objects to the file

    Arguments: 
        none
*/
/* --------------------------------------------------------------------------------------------- */
void output_pmd(OutFilenames *out_filenames, int file_restrictions, int include_debug)
{
    if (file_restrictions & AUTOGEN_PMD_FILE_RESTRICTION_RD)
    {
        pmd_file_generate(out_filenames, AUTOGEN_PMD_FILE_RESTRICTION_RD, include_debug);
    }
    if (file_restrictions & AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED)
    {
        pmd_file_generate(NULL, AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED, include_debug);
    }
    if (file_restrictions & AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC)
    {
        pmd_file_generate(NULL, AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC, include_debug);
    }
}

/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

LOCAL void pmd_file_generate(OutFilenames *out_filenames, int file_restriction, int include_debug)
{
    char str_filename[256] = "";
    char str_version[256] = "";
    pmd_env env;
#if (!defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU || !defined AUTOGEN_INCLUDE_NOS_TRACES)
    out_filenames;
#endif /* !AUTOGEN_ENVIRONMENT_PRODUCT_MCU || !AUTOGEN_INCLUDE_NOS_TRACES */

    /* prepare environment */
    memset(&env, 0, sizeof(pmd_env));
    env.include_debug       = include_debug;
    env.file_restriction    = file_restriction;
    if (env.file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC)
    {
        env.file_restriction_pmd = PMD_FILE_RESTRICTION_PUBLIC;
        env.flag_all             = AUTOGEN_OBJ_IS_PMD_PUBLIC;
    }
    else if (env.file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED)
    {
        env.file_restriction_pmd = PMD_FILE_RESTRICTION_RESTRICTED;
        env.flag_all             = AUTOGEN_OBJ_IS_PMD_RESTRICTED;
    }
    else
    {
        env.file_restriction_pmd = PMD_FILE_RESTRICTION_RD;
    }
    env.heap_handle         = pmd_heap_init_h(800000);
    env.typ_res_entrypoint  = (pmd_typ**)pmd_heap_alloc_h(env.heap_handle, g_res_list->n_obj * sizeof(pmd_typ*));
    env.string_token_buffer = (pmd_token_buffer*)pmd_heap_alloc_h(env.heap_handle, sizeof(pmd_token_buffer));
    env.object_token_buffer = (pmd_token_buffer*)pmd_heap_alloc_h(env.heap_handle, sizeof(pmd_token_buffer));
    env.output_buffer       = (pmd_bit_buffer*)pmd_heap_alloc_h(env.heap_handle, sizeof(pmd_bit_buffer));
    env.instance_map        = (unsigned char*)pmd_heap_alloc_h(env.heap_handle, 400000);

    /* Initialise printf format info object count */
    env.printf_info_obj_count = 0;

	/* Set Device ID */
#ifdef AUTOGEN_DEVICE_ID
    env.device_id = AUTOGEN_DEVICE_ID;
#else
	env.device_id = PMD_DEVICE_GENERAL;
#endif

    pmd_stringpool_init(30000, env.heap_handle, 50000);

    /* set file name */
    pmd_file_generate_name(&env, str_filename, str_version);

    if (g_autogen_env == AUTOGEN_ENV_LOCAL)
    {
        fprintf(g_log, "\n");
        fprintf(g_log, "------------------------------------------------------------------------------\n");
        fprintf(g_log, "%s PMD file generation\n", 
            (file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD ? "R&D" : 
            (file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC ? "Public" : "Restricted")));
        fprintf(g_log, "------------------------------------------------------------------------------\n");
    }

    /* --------------------------------------------------------------------- */
    /* Generate normal PMD file */
    /* --------------------------------------------------------------------- */    
    {
        autogen_embedded_file* emb = (autogen_embedded_file*)autogen_obj_get_first_in_list(g_emb_file_list);

        printf("\nGenerating %s PMD file '%s'\n", 
            (file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD) ? "R&D" : 
            (file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC ? "public" : "restricted"),
            str_filename);
        printf("- Generating object model\n");

		/* generate devices */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
        pmd_device_add(&env, AUTOGEN_DEVICE_ID, AUTOGEN_DEVICE_NAME, AUTOGEN_DEVICE_LOGICAL_NAME);
#endif
        
        /* build object hierarchy */       
        pmd_generate_model(&env);
        pmd_env_vars_generate(&env);
        pmd_info_groups_generate(&env);

#ifdef AUTOGEN_INCLUDE_VENDOR_DLL_TRACE
#ifdef AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION
        {
            /* Inclusion of Chipset Supplier Description xml filenames */
            #ifndef AUTOGEN_VENDOR_DLL_TRACE_GROUP_FILE_NAME
                #include "autogen_vendor_includes.h"
                int cnt = 0;
            #endif

            char cwd[1024] = "";

            /* Store current working directory and go to the startup working directoy */
            getcwd(cwd, 1024);
            chdir(working_dir);

            /* Import chipset supplier description */
#ifdef AUTOGEN_VENDOR_DLL_TRACE_GROUP_FILE_NAME
            /* Backwards compatible. If defined only one chipset supplier description possible */
            autogen_import_chipset_supplier_description(&env, AUTOGEN_VENDOR_DLL_TRACE_GROUP_FILE_NAME, file_restriction);
#else
            /* Read in multiple chipset supplier descriptions */
            while (chipset_supplier_description_xml_files[cnt] != NULL)
            {
                autogen_import_chipset_supplier_description(&env, chipset_supplier_description_xml_files[cnt++], file_restriction);
            }
#endif
            /* Restore the current working directory */
            chdir(cwd);
        }
#endif /* AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION */
#endif /* AUTOGEN_INCLUDE_VENDOR_DLL_TRACE */

        /* write pmd objects */
        pmd_typedef_module_write(&env, env.typ_root_module);

#if (defined AUTOGEN_INCLUDE_NOS_TRACES && defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU)
        if (file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD)
        {
            int i;

            /* For each .out file given as input, generated symbol info for PMD file */
            for (i=0; i<out_filenames->n_filename; i++) {
                if (out_filenames->filename[i][0]) 
                {
                    FILE *fout = fopen(out_filenames->filename[i], "rb");

                    if (fout) 
                    {
                        /* Parse the .out file (ELF format) */
                        pmd_elf_generate_elf(&env, fout, out_filenames->filename[i]);
                        fclose(fout);
                    }
                    else
                    {
                        /* Error opening the .out file */
                        printf("   Error: Unable to open .out file '%s'\n\n", out_filenames->filename[i]);
                    }
                }
            }
        }
#endif /* AUTOGEN_INCLUDE_NOS_TRACES && AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

        pmd_write_cpmd(&env, TRUE);

        pmd_file_generate_output_buffer(&env);

        /* compress embedded files */
        while (emb)
        {
            if (emb->base.subtype == AUTOGEN_EMBEDDED_FILE_INFO)
            {
                unsigned int i;

                printf("- Compressing embedded file '%s'\n", emb->base.name);

                /* write number of bytes */
                pmd_write_dword(&env, emb->file_size);

                for (i = 0; i < emb->file_size; i++)
                {
                    pmd_write_byte(&env, ((unsigned char*)emb->base.ptr)[i]);
                }

                pmd_compress_block(env.object_token_buffer, env.output_buffer);
                pmd_release_tokens(env.object_token_buffer);
            }

            emb = (autogen_embedded_file*)emb->base.next;
        }

        pmd_file_write(&env, str_filename, str_version);

        if (g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU && env.file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RD)
        {
            pmd_file_generate_copy(str_filename, "product.pmd", env.file_size);
        }

        /* debug info */
        if (env.include_debug)
        {
            pmd_debug_dump_file(&env);
        }
    }

    /* clean up */
    pmd_stringpool_free();
    pmd_heap_free_h(env.heap_handle);
}

LOCAL void pmd_file_generate_name(pmd_env* env, char* str_filename, char* str_version)
{
    /* get version string, if any */
    if (g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU)
    {
        /* strncpy(version_str, core_sw_version_get(), 255); */
        strncpy(str_version, dev_sw_version, 255);
        prop_add_indexed_string_to_object(&g_pmd_environment_variables, PROPERTY_PMD_ENVIRONMENT_VARIABLE, str_version, 
            PMD_ENVIRONMENT_VAR_ID_MCU_SW_VERSION, NULL, 0, FALSE);
        
        /* create filename from version string */
        {
            int index = 0;
            char* p_prodname = NULL;
            char* p_sw_version = NULL;
            char* p_hw_version = NULL;
                            
            /* find SW version */
            p_sw_version = str_version;
            while (*p_sw_version && !isdigit(*p_sw_version))
            {
                ++p_sw_version;
            }

            /* find product name */
            p_prodname = strchr(str_version, '\n');

            if (p_prodname)
            {
                p_prodname = strchr(p_prodname + 1, '\n');
            }
            
            if (p_prodname)
            {
                ++p_prodname;
            }
            
            if (p_prodname && p_sw_version)
            {
                /* copy product name */
                while (*p_prodname && *p_prodname != '\n')
                {
                    if (isalnum(*p_prodname))
                    {
                        str_filename[index++] = (char)tolower(*p_prodname);
                    }
                    ++p_prodname;
                }
                
                /* add underscore*/
                str_filename[index++] = '_';
                
                /* find and copy HW version */
                p_hw_version = strchr(p_prodname, '\n');
                if (p_hw_version)
                {
                    p_hw_version = strchr(p_prodname + 1, '\n');
                    if (p_hw_version)
                    {
                        --p_hw_version;

                        while (isdigit(*p_hw_version) || *p_hw_version == '.')
                        {
                            --p_hw_version;
                        }

                        while (*p_hw_version != '\n')
                        {
                            if (isdigit(*p_hw_version))
                            {
                                str_filename[index++] = *p_hw_version;
                            }

                            ++p_hw_version;
                        }
                    }
                }

                /* copy SW version */
                while (*p_sw_version && *p_sw_version != '\n')
                {
                    if (isdigit(*p_sw_version) || isalpha(*p_sw_version))
                    {
                        str_filename[index++] = *p_sw_version;
                    }
                    ++p_sw_version;
                }
                
                str_filename[index] = 0;
            }
        }
    }
    else
    {
        strcpy(str_filename, PMD_FILE_NAME);
    }

    if (strlen(str_filename) == 0)
    {
        strcpy(str_filename, "product");
    }

    if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED)
    {
        strcat(str_filename, ".R");
    }
    else if (env->file_restriction == AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC)
    {
        strcat(str_filename, ".P");
    }

    strcat(str_filename, ".pmd");
}

/*  Writes a byte to the disk. All write functions call this function 
    ultimatively, so only here, the encryption "AA" is implemented.
*/
void pmd_write_byte(pmd_env* env, unsigned char value)
{
    PMD_APPEND_TOKEN(env->object_token_buffer, PMD_TOKEN_TYPE_SYMBOL, value);
}

/*  Writes a word to the disk */
void pmd_write_word(pmd_env* env, unsigned int value)
{
    PMD_APPEND_TOKEN(env->object_token_buffer, PMD_TOKEN_TYPE_SYMBOL, value);
}

/*  Writes a dword to the disk */
void pmd_write_dword(pmd_env* env, unsigned int value)
{
    PMD_APPEND_TOKEN(env->object_token_buffer, PMD_TOKEN_TYPE_SYMBOL, value);
}

#if (PMD_FILE_FORMAT >= 600)
/*  Writes a ddword to the disk */
void pmd_write_ddword(pmd_env* env, unsigned long long value)
{
    /* Write ddword (64 bit) as 2 x dword (little endian) */
    PMD_APPEND_TOKEN(env->object_token_buffer, PMD_TOKEN_TYPE_SYMBOL, (unsigned int)(value & 0x00000000ffffffffLL));
    PMD_APPEND_TOKEN(env->object_token_buffer, PMD_TOKEN_TYPE_SYMBOL, (unsigned int)(value >> 32));
}
#endif

/*  Writes a PMD string to the disk, consisting of a string length (2 bytes)
    and string data.
*/
void pmd_write_string(pmd_env* env, const char* str)
{
    unsigned int index = 0;

    if (str && str[0])
    {
        pmd_stringpool_add(str, 0, &index);
    }

    PMD_APPEND_TOKEN(env->object_token_buffer, PMD_TOKEN_TYPE_SYMBOL, index);

    /* Update the highest string index */
    if (index > env->string_index_max)
    {
        env->string_index_max = index;
    }
}

/*  Writes an object ID to the disk, consisting of a class ID (2 bytes) and
    an ID (4 bytes). If the id is 0, the class PMD_CLASS_NULL is written as 
    class ID.
*/
void pmd_write_objid(pmd_env* env, const pmd_managedobj* managed_obj)
{
    unsigned int index  = managed_obj->object_id / 8;
    unsigned int offset = managed_obj->object_id % 8;
    unsigned int mask   = 1 << offset;

    /* first time, class ID and object ID should be saved.
       next time, only object ID should be saved
    */
    if ((env->instance_map[index] & mask) || managed_obj->object_id == 0)
    {
        pmd_write_dword(env, managed_obj->object_id);
    }
    else
    {
        pmd_write_dword(env, managed_obj->object_id);
        pmd_write_word(env, managed_obj->class_id);

        env->instance_map[index] |= mask;
    }
}

/*  Writes the object ID NULL. */
void pmd_write_objid_null(pmd_env* env)
{
    pmd_write_dword(env, 0);
}

/*  Writes the one and only CPMD object. */
LOCAL void pmd_write_cpmd(pmd_env* env, int normal_file)
{
    unsigned int n_emb = 0;
    autogen_embedded_file* emb = NULL;
    autogen_it emb_it = INIT_ITERATOR;
    pmd_managedobj managedobj;

    managedobj.class_id  = PMD_CLASS_PMD;
    managedobj.object_id = ++env->last_object_id;

    /* write object id */
    pmd_write_objid(env, &managedobj);

    /* Write flags */
    pmd_write_dword(env, 0);

    /* write entry points */
    pmd_entry_points_write_all(env, env->n_entry_points, env->entry_points);

    /* write entry point subtrees */
    pmd_entry_points_write_all(env, env->n_entry_point_subtrees, env->entry_point_subtrees);

    /* write embedded file info */
    if (normal_file)
    {
        emb_it.subtypemask = AUTOGEN_EMBEDDED_FILE_INFO;

        n_emb = autogen_obj_count_in_list(&emb_it, g_emb_file_list);

        /* write number of embedded files */
        pmd_write_dword(env, n_emb);

        emb = (autogen_embedded_file*)autogen_obj_find_in_list(&emb_it, g_emb_file_list);
        while (emb)
        {
            /* Write flags */
            pmd_write_dword(env, 0);

            /* write embedded file name */
            pmd_write_string(env, emb->base.name);

            /* write decoder file name */
            pmd_write_string(env, emb->decoder_name);

            emb = (autogen_embedded_file*)autogen_obj_find_next_in_list(&emb_it);
        }
    }
    else
    {
        pmd_write_dword(env, 0);
    }

    /* write embedded PMD file info */
    {
        emb_it.subtypemask = AUTOGEN_EMBEDDED_FILE_PMD;
        emb_it.flagall     = env->file_restriction;

        /* write number of embedded PMD files */
        n_emb = autogen_obj_count_in_list(&emb_it, g_emb_file_list);
        pmd_write_dword(env, n_emb);

        /* write embedded PMD file sizes */
        emb = (autogen_embedded_file*)autogen_obj_find_in_list(&emb_it, g_emb_file_list);
        while (emb)
        {
            /* write flags */
            pmd_write_dword(env, 0);

            /* write embedded PMD file name */
            pmd_write_string(env, emb->base.name);

            /* write embedded PMD file size */
            pmd_write_dword(env, emb->file_size);

            emb = (autogen_embedded_file*)autogen_obj_find_next_in_list(&emb_it);
        }
    }

    /* write environmnet variables */
	pmd_env_vars_write_all(env, env->n_env_vars, env->env_vars, PMD_WRITE_ENVVAR_DATA | PMD_WRITE_COUNTERS);

    /* write info groups */
    pmd_info_groups_write_all(env, env->n_info_groups, env->info_groups);

    /* write message type objects */
	pmd_msgtypes_write_all(env, env->n_msgtypes, env->msgtypes, PMD_WRITE_MSG_DATA | PMD_WRITE_COUNTERS);

    /* write devices */
    pmd_device_write_all(env);

#if (PMD_FILE_FORMAT >= 610)
    /* Write debug information */
    {
        unsigned int shared_cnt = 0;

        /* write debug info for executable .out file */
        pmd_debuginfo *ptr = env->debuginfo;
        while(ptr)
        {
            if (ptr->type == 2 /* ET_EXEC */)
            {
                pmd_debuginfo_write(env, ptr);

                /* write out only the first executable found */
                break;
            }
            else
            {
                ptr = ptr->next;
            }
        }

        /* if no executable .out file found then write null record */
        if (ptr == NULL)
        {
            pmd_debuginfo *null_pmd_debug = pmd_debuginfo_create(env, "", 2 /* ET_EXEC = 2 Executable file */);
            pmd_debuginfo_write(env, null_pmd_debug);
        }

        /* count and write number of shared .out files */
        shared_cnt = 0;
        ptr = env->debuginfo;
        while(ptr)
        {
            if (ptr->type == 3 /* ET_DYN */)
                shared_cnt++;
            ptr = ptr->next;
        }
        pmd_write_dword(env, shared_cnt);

        /* write debug info for shared .out files */
        ptr = env->debuginfo;
        while(ptr)
        {
            if (ptr->type == 3 /* ET_DYN */)
                pmd_debuginfo_write(env, ptr);
            ptr = ptr->next;
        }
    }
#endif
}

/*  Writes the PMD file ASCII header */
LOCAL void pmd_write_asc_header(pmd_env* env, FILE* fpmd, const char* mcuswversion)
{
    char str_temp[100];

    pmd_write_xml_header(env, fpmd, mcuswversion);

    sprintf(str_temp, "%c", 26);
    fwrite(str_temp, 1, 1, fpmd);
}

/*  Writes the PMD file binary header, consisting of a length (6 bytes),
    a compression type and an encryption type.
*/
LOCAL void pmd_write_bin_header(FILE* fpmd)
{
    int i;
    unsigned char header[4] =
    {
        0, PMD_COMPRESSION_TYPE_LZH, 0, PMD_ENCRYPTION_TYPE_NONE
    };

    /* write compression type */
    for (i = 0; i < 4; i++)
    {
        fputc(header[i], fpmd);
    }
}

/*  Writes the PMD XML header */
LOCAL void pmd_write_xml_header(pmd_env* env, FILE* fpmd, const char* mcuswversion)
{
    const char* env_var_str;


    fprintf(fpmd, "<PmdFileInfo>");

    /* File format */
#if PMD_FILE_FORMAT == 500
    fprintf(fpmd, "<FileFormat>5.00</FileFormat>");
#elif PMD_FILE_FORMAT == 501
    fprintf(fpmd, "<FileFormat>5.01</FileFormat>");
#elif PMD_FILE_FORMAT == 600
    fprintf(fpmd, "<FileFormat>6.00</FileFormat>");
#elif PMD_FILE_FORMAT == 610
    fprintf(fpmd, "<FileFormat>6.10</FileFormat>");
#else
    util_error_line(NULL, 0, AUTOGEN_ERROR_FATAL_INTERNAL, AUTOGEN_ENV_ALL, 0, "Invalid PMD file format in pmd_write_xml_header()");
#endif

    /* File type */
    fprintf(fpmd, "<FileType>%s</FileType>", pmd_constant_lookup_file_type(AUTOGEN_PMD_FILE_TYPE));

    /* PMD file restriction */
    fprintf(fpmd, "<FileRestriction>%s</FileRestriction>", pmd_constant_lookup_file_restriction(env->file_restriction_pmd));


    if (g_autogen_env == AUTOGEN_ENV_PRODUCT_DEVICE)
    {
        env_var_str = pmd_env_lookup_string(env, env->device_id, PMD_ENVIRONMENT_VAR_ID_SW_VERSION);
        if (env_var_str)
        {
            fprintf(fpmd, "<SwVersion>%s</SwVersion>", env_var_str);
        }
    }
    else
    {
        /* MCU SW version */
        if (g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU)
        {
            fprintf(fpmd, "<SwVersion>%s</SwVersion>", mcuswversion);
        }

        /* CDSP SW version */
        env_var_str = pmd_env_lookup_string(env, PN_DEV_DSP_MAIN, PMD_ENVIRONMENT_VAR_ID_SW_VERSION);
        if (env_var_str)
        {
            fprintf(fpmd, "<SwVersion>%s</SwVersion>", env_var_str);
        }

        /* ADSP SW version */
        env_var_str = pmd_env_lookup_string(env, PN_DEV_DSP_AUX, PMD_ENVIRONMENT_VAR_ID_SW_VERSION);
        if (env_var_str)
        {
            fprintf(fpmd, "<SwVersion>%s</SwVersion>", env_var_str);
        }
    }

    /* Origin */
    fprintf(fpmd, "<Origin>autogen %s</Origin>", AUTOGEN_VERSION_NUMBER);

    /* Device */
    if (g_autogen_env == AUTOGEN_ENV_PRODUCT_DEVICE || 
        g_autogen_env == AUTOGEN_ENV_PRODUCT_DSP || 
        g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU || 
        g_autogen_env == AUTOGEN_ENV_PRODUCT_SYMBIAN || 
        g_autogen_env == AUTOGEN_ENV_PRODUCT_ADSP)
    {
        fprintf(fpmd, "<DeviceId>%d</DeviceId>", env->device_id);
    }

#if (PMD_FILE_FORMAT >= 610)
    /* Hash value of target flash file                                                                 */
    /* Post-processing tool will update PMD file with correct hash key. Here we just make space        */
    /* for complete hash key to be written. Hash key is 20 bytes written as 2 character hex values .   */
    /* In agreement with tracing SDK then a # as the first character will signify an invalid hash key. */
    /* This # character can be followed by an error message.                                           */
    fprintf(fpmd, "<Hashkey># No hash key has yet been written.     </Hashkey>");
#endif

    fprintf(fpmd, "</PmdFileInfo>");
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_file_generate_output_buffer
 
    Description: 
        Compresses string table and object buffer and releases related objects
        Generated output buffer is ready to be written to PMD file
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void pmd_file_generate_output_buffer(pmd_env* env)
{
    size_t i;

    printf("- Compressing string table\n");
    for (i = 1; i <= env->string_index_max; i++)
    {
        unsigned int j;
        char* str = pmd_stringpool_get(i);
        unsigned int len = strlen(str);

        for (j = 0; j <= len; j++)
        {
            PMD_APPEND_TOKEN(env->string_token_buffer, PMD_TOKEN_TYPE_SYMBOL, (unsigned char)str[j]);
        }
    }

    PMD_APPEND_TOKEN(env->string_token_buffer, PMD_TOKEN_TYPE_SYMBOL, 0);

    /* compress and release the string buffer */
    pmd_compress_block(env->string_token_buffer, env->output_buffer);
    pmd_release_tokens(env->string_token_buffer);

    /* compress and release the object buffer */
    printf("- Compressing objects\n");
    pmd_compress_block(env->object_token_buffer, env->output_buffer);
    pmd_release_tokens(env->object_token_buffer);
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_file_generate
 
    Description: 
        Generates the PMD file 'filename'¨and includes the version string 'version_str'
 
    Arguments: 
        filename    [in] - PMD file name
        version_str [in] - MCU SW Version string of PMD file

    Returns:
        -
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void pmd_file_write(pmd_env* env, const char* filename, const char* version_str)
{
    FILE* fpmd = fopen(filename, "wb");
    if (fpmd)
    {
        printf("- Writing PMD file\n");

        /* write pmd headers */
        pmd_write_asc_header(env, fpmd, version_str);
        pmd_write_bin_header(fpmd);

        /* write the compressed buffer */
        fwrite(pmd_get_byte_pointer(env->output_buffer), pmd_get_byte_count(env->output_buffer, TRUE), 1, fpmd);

        /* release compressed buffer */
        pmd_release_bits(env->output_buffer);

        /* write embedded PMD files */
        {
            autogen_embedded_file* emb;
            autogen_it emb_it = INIT_ITERATOR;

            emb_it.subtypemask = AUTOGEN_EMBEDDED_FILE_PMD;
            emb_it.flagall     = env->file_restriction;

            emb = (autogen_embedded_file*)autogen_obj_find_in_list(&emb_it, g_emb_file_list);
            while (emb)
            {
                printf("  Embedding PMD file '%s'\n", emb->base.name);

                fwrite(emb->base.ptr, emb->file_size, 1, fpmd);

                emb = (autogen_embedded_file*)autogen_obj_find_next_in_list(&emb_it);
            }
        }

        env->file_size = ftell(fpmd);

        fclose(fpmd);
    }
    else
    {
        printf("   Error: Unable to open output file '%s'\n\n", filename);
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_file_generate_copy
 
    Description: 
        Copies the PMD file 'src_filename' to the file 'dest_filename'
 
    Arguments: 
        src_filename  [in] - Source file name
        dest_filename [in] - Destination file name
        filesize      [in] - Size of PMD file in bytes
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL void pmd_file_generate_copy(const char* src_filename, const char* dest_filename, long filesize)
{
    if (filesize > 0L && strcmp(src_filename, dest_filename))
    {
        FILE* foldpmd = fopen(src_filename, "rb");    
        if (foldpmd)
        {
            FILE* fpmd = fopen(dest_filename, "wb");
            if (fpmd)
            {   
                void* buffer = malloc(filesize);
                if (buffer)
                {   
                    printf("- Copying PMD file '%s' to '%s'\n", src_filename, dest_filename);

                    fread(buffer,  filesize, 1, foldpmd);
                    fwrite(buffer, filesize, 1, fpmd);

                    free(buffer);
                }

                fclose(fpmd);
            }

            fclose(foldpmd);
        }
    }
}

/* End of file output_pmd.c */
