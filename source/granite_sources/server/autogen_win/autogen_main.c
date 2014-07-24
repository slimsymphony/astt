/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_main.c
                --------------
                SW Module






Project:          autogen

%name:            autogen_main.c %
%version:         co1tss#131 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 12:47:48 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  This file is part of the source code for the autogen tool

    The file contains the main function which parses the tool arguments
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_def.h"
#include "autogen_init.h"
#include "autogen_object.h"
#include "autogen_prop.h"
#include "autogen_util.h"
#include "autogen_parsexml.h"

#include "pmdconstants.h"
#include "pmd_heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _MSC_VER
 #include <direct.h>
#endif



/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 void output_html();
 void output_srvhdr();
 void output_tsa();
 void output_xml();
#else
 void output_html() {}
 void output_srvhdr() {}
 void output_tsa() {}
 void output_xml() {}
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

void output_pmd(OutFilenames *out_filenames, int pmd_file_types, int include_debug);

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 void build_coresw();
 void build_coresw2();
 void build_coresw3();
 void build_coresw4();
 void build_coresw_cl();
 void build_coresw_mon();
 void build_iam();
 void build_iam2();
 void build_iam3();
 void build_protocols();
 void build_protocols2();
 void build_protocols3();
 void build_protocols_gsm();
 void build_protocols_eutran();
 void build_protocols_wcdma();
 #ifndef AUTOGEN_INCLUDE_VENDOR_TRACES
 void build_dsp();
 #endif /* AUTOGEN_INCLUDE_VENDOR_TRACES */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
  void build_device();
#endif

#ifdef AUTOGEN_INCLUDE_MCU_TRACES_CORE
 void build_mcu_trace_core();
#endif
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL
 void build_mcu_trace_protocol();
#endif
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_ISA_UI
 void build_mcu_trace_isa_ui();
#endif
#ifdef AUTOGEN_INCLUDE_MCU_TRACES_MISC
 void build_mcu_trace_misc();
#endif

#ifdef AUTOGEN_INCLUDE_INVARIANT_TRACES
  void build_invariant_trace();
#endif /* AUTOGEN_INCLUDE_INVARIANT_TRACES */

#ifdef AUTOGEN_INCLUDE_VENDOR_TRACES
  void build_vendor_trace();
#endif /* AUTOGEN_INCLUDE_VENDOR_TRACES */

void build_symbols(const char* obj_filename);
void build_symbols_post();
void build_user();
void build_entry_points();

/* Stores the current working directory when autogen starts up */
char working_dir[512] = "";

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL static
#endif /* LOCAL */

LOCAL void import_file(const char* filename, const char* decodername, unsigned int type, unsigned int flag);
LOCAL int  extract_pmd_version(const char *importfile, unsigned int *pmd_version, const char *filename);

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DSP
 LOCAL void import_dsp5_identifiers(const char* filename);
#else
 LOCAL void import_dsp5_identifiers(const char* filename) { filename; }
#endif

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 LOCAL void update_mcu_trace_group_text(const char* grpname, const char*dectext);
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

#ifdef _MSC_VER /* We use strict ANSI option, where chdir, mkdir, and getcwd are not declared */
 #define chdir _chdir
 #define getcwd _getcwd
 #define mkdir _mkdir
#endif /* _MSV_VER */


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: main
 
    Purpose: 
        Main function of the tool
 
    Functional Description:
        Validates the input arguments and then executes the application (builds data model and
        generates outputs)

    Arguments: 
        argc - [in] number of arguments passed to the tool (including the tool name itself)
        argv - [in] array of arguments (as strings)

    Return Values:
        1 on error, else 0
*/
/* --------------------------------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
    int i;
    time_t thetime;
    struct tm* today;
    char* pnobj_filename = NULL;
    time_t start, finish;
    double elapsed_time;
    OutFilenames out_filenames;

    /* Get start time */
    time(&start);

    /* Store working directory */
    getcwd(working_dir, 512);

    /* initialize PMD heap */
    pmd_heap_init(800000);

    /* Init storage of .out filenames */
    out_filenames.n_filename = 0;

    /* initialize resource list */
    g_res_list = pmd_heap_alloc(sizeof(autogen_obj_list));
    autogen_obj_list_init(g_res_list, NULL, 0, 200);

    g_emb_file_list = pmd_heap_alloc(sizeof(autogen_obj_list));
    autogen_obj_list_init(g_emb_file_list, NULL, 0, 5);

    /* autogen configuration */
    printf("=========================================================\n");
    printf("autogen configuration\n");
    printf("---------------------------------------------------------\n");
    printf("autogen version:      %s, %s\n", AUTOGEN_VERSION_NUMBER, AUTOGEN_VERSION_DATE);
    printf("Environment:          %s", AUTOGEN_ENVIRONMENT_STRING);
#ifdef AUTOGEN_DISABLE_TOUGH_CHECKS
    printf(" (tolerant)");
#endif
    printf("\n");
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
    printf("Device:               %s (0x%2.2X)\n", AUTOGEN_DEVICE_LOGICAL_NAME, AUTOGEN_DEVICE_ID);
#endif
    printf("PMD file format:      %s\n", PMD_FILE_FORMAT_STRING);
    printf("PMD file type:        %s\n", pmd_constant_lookup_file_type(AUTOGEN_PMD_FILE_TYPE));
    printf("XTI version:          %s\n", AUTOGEN_XTI_VERSION_STRING);
    printf("=========================================================\n\n\n");

    time(&thetime);
    today = localtime(&thetime);

    /* Open log file */
    g_log = fopen("autogen.log", "w");

    fprintf(g_log, "autogen execution log - autogen.log\n");
    fprintf(g_log, "------------------------------------------------------------------------------\n");
    fprintf(g_log, "Version:              %s\n", AUTOGEN_VERSION_NUMBER);
    fprintf(g_log, "Environment:          %s\n", AUTOGEN_ENVIRONMENT_STRING);
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
    fprintf(g_log, "Device:               %s (0x%2.2X)\n", AUTOGEN_DEVICE_LOGICAL_NAME, AUTOGEN_DEVICE_ID);
#endif
    fprintf(g_log, "PMD file type:        %s\n", pmd_constant_lookup_file_type(AUTOGEN_PMD_FILE_TYPE));
    fprintf(g_log, "Date:                 %2.2d-%2.2d-%d %d:%2.2d:%2.2d\n",
        today->tm_mday, today->tm_mon+1, today->tm_year+1900,
        today->tm_hour, today->tm_min, today->tm_sec);
    fprintf(g_log, "------------------------------------------------------------------------------\n");

    /* if user is not asking for help */
    if (argc > 1 && strcmp(argv[1], "-?"))
    {
        for (i = 1; i < argc; i++)
        {
            /* set pn_obj_auto.h file name */
            if (!strncmp(argv[i], "-obj", 4) && g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU)
            {
                pnobj_filename = &argv[i][4];
            }
            /* set .out file name */
            else if (!strncmp(argv[i], "-out", 4) && (g_autogen_env & AUTOGEN_ENV_PRODUCT))
            {
                out_filenames.filename[out_filenames.n_filename++] = &argv[i][4];
            }
            /* set dsp5_identifiers.txt file name */
            else if (!strncmp(argv[i], "-dsp5", 5) && g_autogen_env == AUTOGEN_ENV_PRODUCT_DSP)
            {
                /* dont import the file now... later ! */
            }
            /* set disperin.cfg file name */
            else if (!strncmp(argv[i], "-disp", 5) && g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU)
            {
                /* dont import the file now... later ! */
            }
            /* change destination directory */
            else if (!strncmp(argv[i], "-d", 2))
            {
                /* dont change directory yet */
            }
            else if (!strncmp(argv[i], "-embed_pmd_restricted", strlen("-embed_pmd_restricted")) && (g_autogen_env & AUTOGEN_ENV_PRODUCT))
            {
                import_file(&argv[i][strlen("-embed_pmd_restricted")], "", AUTOGEN_EMBEDDED_FILE_PMD, AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED);
            }
            else if (!strncmp(argv[i], "-embed_pmd_public", strlen("-embed_pmd_public")) && (g_autogen_env & AUTOGEN_ENV_PRODUCT))
            {
                import_file(&argv[i][strlen("-embed_pmd_public")], "", AUTOGEN_EMBEDDED_FILE_PMD, AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC);
            }
            else if (!strncmp(argv[i], "-embed_pmd", strlen("-embed_pmd")))
            {
                import_file(&argv[i][strlen("-embed_pmd")], "", AUTOGEN_EMBEDDED_FILE_PMD, AUTOGEN_PMD_FILE_RESTRICTION_RD);
            }
        }     

        /* initialize */
        init_isi_begin();

        /* Perform sanity check on the property table */
        check_prop_table();

        printf(" ------------------------------------------------------\n");
        printf(" General symbols:\n");
        printf(" ------------------------------------------------------\n");
        build_symbols(pnobj_filename);
        printf("\n");

        printf(" ------------------------------------------------------\n");
        printf(" User Included Interfaces/traces:\n");
        printf(" ------------------------------------------------------\n");
        build_user();
        printf("\n");

#ifdef AUTOGEN_INCLUDE_MCU_TRACES
 #ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
        printf(" ------------------------------------------------------\n");
        printf(" Core Interfaces Monitor server:\n");
        printf(" ------------------------------------------------------\n");
        build_coresw_mon();
        printf("\n");
 #endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */
#endif

#ifdef AUTOGEN_INCLUDE_NOS_TRACES
       
        printf(" ------------------------------------------------------\n");
        printf(" NOS traces\n");
        printf(" ------------------------------------------------------\n");

        #include "os_trc_m.h"
        printf("\n");

#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

#ifdef AUTOGEN_INCLUDE_HSP_TRACES

       printf(" ------------------------------------------------------\n");
       printf(" HSP XTI traces\n");
       printf(" ------------------------------------------------------\n");

       #include "hsp_trc_m.h"
       printf("\n");

#endif /* AUTOGEN_INCLUDE_HSP_TRACES */

#ifdef AUTOGEN_INCLUDE_HAL_TRACES
       
        printf(" ------------------------------------------------------\n");
        printf(" HAL traces\n");
        printf(" ------------------------------------------------------\n");

 /* Ensure correct trace macros */
 #if (!defined AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS || !defined AUTOGEN_TRACES_HAVE_FIXED_IDS)
  #define AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
  #define AUTOGEN_TRACES_HAVE_FIXED_IDS
  #include "isi_macros.h"
 #endif

 #include "hal_trc_m.h"

        printf("\n");
#endif /* AUTOGEN_INCLUDE_HAL_TRACES */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 /* The following #if can be omitted. Indicates which flags are used later on */
 #if ((defined AUTOGEN_INCLUDE_INTERFACES) || (defined AUTOGEN_BINARY_RELEASE))

        printf(" ------------------------------------------------------\n");
        printf(" Core Interfaces (general):\n");
        printf(" ------------------------------------------------------\n");
        build_coresw();
        build_coresw2();
        build_coresw3();
        build_coresw4();
        build_coresw_cl();
        printf("\n");

        printf(" ------------------------------------------------------\n");
        printf(" MAUI Interfaces:\n");
        printf(" ------------------------------------------------------\n");
        build_iam();
        build_iam2();
        build_iam3();
        printf("\n");

        printf(" ------------------------------------------------------\n");
        printf(" ISA Protocol Interfaces:\n");
        printf(" ------------------------------------------------------\n");
        build_protocols();
        build_protocols2();
        build_protocols3();
        build_protocols_gsm();
        build_protocols_eutran();
        build_protocols_wcdma();
        printf("\n");

  #ifndef AUTOGEN_INCLUDE_VENDOR_TRACES
        printf(" ------------------------------------------------------\n");
        printf(" DSP Interfaces:\n");
        printf(" ------------------------------------------------------\n");
        build_dsp();
        printf("\n");
  #endif /* AUTOGEN_INCLUDE_VENDOR_TRACES */
 #endif /* AUTOGEN_INCLUDE_INTERFACES || AUTOGEN_BINARY_RELEASE */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
        printf(" ------------------------------------------------------\n");
        printf(" Device Interfaces:\n");
        printf(" ------------------------------------------------------\n");
        build_device();
#endif

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT

        printf(" ------------------------------------------------------\n");
        printf(" Autogen Included Interfaces:\n");
        printf(" ------------------------------------------------------\n");

#include "autogen_ostrich.h"

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 #if ((defined AUTOGEN_INCLUDE_INTERFACES) || (defined AUTOGEN_BINARY_RELEASE))
  #include "autogen_rpc_req.h"
  #include "autogen_rpc_resp.h"
  #include "autogen_error_info.h"
 #endif /* AUTOGEN_INCLUDE_INTERFACES || AUTOGEN_BINARY_RELEASE */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
        printf("\n");
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */

#ifdef AUTOGEN_INCLUDE_MCU_TRACES

 #ifdef AUTOGEN_INCLUDE_MCU_TRACES_CORE
        printf(" ------------------------------------------------------\n");
        printf(" MCU traces (Core):\n");
        printf(" ------------------------------------------------------\n");
        build_mcu_trace_core();
        printf("\n");
 #endif

 #ifdef AUTOGEN_INCLUDE_MCU_TRACES_PROTOCOL
        printf(" ------------------------------------------------------\n");
        printf(" MCU traces (Protocol):\n");
        printf(" ------------------------------------------------------\n");
        build_mcu_trace_protocol();
        printf("\n");
 #endif

 #ifdef AUTOGEN_INCLUDE_MCU_TRACES_ISA_UI
        printf(" ------------------------------------------------------\n");
        printf(" MCU traces (ISA UI):\n");
        printf(" ------------------------------------------------------\n");
        build_mcu_trace_isa_ui();
        printf("\n");
 #endif

#ifdef AUTOGEN_INCLUDE_MCU_TRACES_MISC
        printf(" ------------------------------------------------------\n");
        printf(" MCU traces (MISC):\n");
        printf(" ------------------------------------------------------\n");
        build_mcu_trace_misc();
        printf("\n");
#endif


 #ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
  #include "isi_macros_empty.h"

  #undef  MON_TRACE_DEFINE_GROUP_ID
  #define MON_TRACE_DEFINE_GROUP_ID(_grpname, _dectext) \
     update_mcu_trace_group_text(#_grpname, _dectext);

  #include "mon_grp.ti"
  #include "isi_macros.h"
 #endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

#endif /* AUTOGEN_INCLUDE_MCU_TRACES */

#ifdef AUTOGEN_INCLUDE_INVARIANT_TRACES
        printf(" ------------------------------------------------------\n");
        printf(" Invariant traces:\n");
        printf(" ------------------------------------------------------\n");
        build_invariant_trace();
        printf("\n");
#endif /* AUTOGEN_INCLUDE_INVARIANT_TRACES */ 

#ifdef AUTOGEN_INCLUDE_VENDOR_TRACES
        printf(" ------------------------------------------------------\n");
        printf(" Vendor traces:\n");
        printf(" ------------------------------------------------------\n");
        build_vendor_trace();
        printf("\n");
#endif /* AUTOGEN_INCLUDE_VENDOR_TRACES */ 


#ifdef AUTOGEN_INCLUDE_OST
       
        printf(" ------------------------------------------------------\n");
        printf(" OST\n");
        printf(" ------------------------------------------------------\n");

        #include "ost_m.h"
        printf("\n");

#endif /* AUTOGEN_INCLUDE_OST */

        printf(" ------------------------------------------------------\n");
        printf(" Entry points:\n");
        printf(" ------------------------------------------------------\n");
#ifdef AUTOGEN_INCLUDE_X_FILE
        printf("  X-file entry point\n");
#endif
#ifdef AUTOGEN_INCLUDE_OST
        printf("  OST entry point\n");
#endif
#ifdef AUTOGEN_INCLUDE_HSP_TRACES
        printf("  HSP entry point\n");
#endif

#ifdef AUTOGEN_INCLUDE_MASTER_TRACES
        printf("  Trace master entry point\n");
#endif /* AUTOGEN_INCLUDE_MASTER_TRACES */
        build_entry_points();
        printf("\n");

        build_symbols_post();

        init_isi_end();

        printf("\n");
    }
    else
    {
        /* show usage if requested with -? parameter */
        printf("\nCopyright (c) Nokia. ");
        printf("All rights reserved.");
        printf("\n");
        printf("\nautogen_exe [options]");
        printf("\n");
        printf("\nOptions are:");
        printf("\n %-32s%s", "-?",             "Show this help");

        if (g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU)
        {
            printf("\n %-32s%s", "-obj<filename>", "Specify pn_obj_auto.h filepath");
            printf("\n %-32s%s", "-out<filename>", "Specify .out filepath");
            printf("\n %-32s%s", "-disp<filename>","Specify disperin.cfg filepath");
            printf("\n %-32s%s", "-embed_pmd<filename>","Specify PMD file to embed");
            printf("\n %-32s%s", "-embed_pmd_public<filename>","Specify public PMD file to embed");
            printf("\n %-32s%s", "-embed_pmd_restricted<filename>","Specify restricted PMD file to embed");
        }
        else if (g_autogen_env == AUTOGEN_ENV_PRODUCT_DSP)
        {
            printf("\n %-32s%s", "-dsp5<filename>", "Specify dsp5_identifiers.txt filepath");
        }
        printf("\n %-32s%s", "-pmd_debug",     "Generate PMD debug log");
        printf("\n %-32s%s", "-d<directory>",  "Specify destination directory");

        if (g_autogen_env == AUTOGEN_ENV_LOCAL)
        {
            printf("\n %-32s%s", "-oisihdr",         "Generate ISI header files");
            printf("\n %-32s%s", "-ohtml",           "Generate message specifications in HTML format");
            printf("\n %-32s%s", "-otsa",            "Generate TSS Server API source files");
            printf("\n %-32s%s", "-oxml",            "Generate XML files");
            printf("\n %-32s%s", "-opmd",            "Generate local PMD file");
            printf("\n %-32s%s", "-opmd_public",     "Generate public PMD file");
        }
        else if (g_autogen_env & AUTOGEN_ENV_PRODUCT)
        {
            printf("\n %-32s%s", "-opmd",            "Generate product PMD file");
            printf("\n %-32s%s", "-opmd_restricted", "Generate restricted PMD file");
            if (g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU)
            {
                printf("\n %-32s%s", "-opmd_public",     "Generate public PMD file");
            }
        }
    }

    if (argc > 1 && strcmp(argv[1], "-?"))
    {
        int nGeneratePMDTypes = 0;
        int bGeneratePMDDebug = FALSE;

        int has_import = FALSE;

        for (i = 1; i < argc; i++)
        {    
            /* import disperin.cfg file */
            if (!strncmp(argv[i], "-disp", 5))
            {
                if (!has_import)
                {
                    printf("Importing files\n");
                    has_import = TRUE;
                }
                import_file(&argv[i][5], "GPRSTraceDLL.dll", AUTOGEN_EMBEDDED_FILE_INFO, 0);
            }
            /* import dsp5_identifiers.txt file */
            else if (!strncmp(argv[i], "-dsp5", 5) && g_autogen_env == AUTOGEN_ENV_PRODUCT_DSP)
            {
                if (!has_import)
                {
                    printf("Importing files\n");
                    has_import = TRUE;
                }
                import_dsp5_identifiers(&argv[i][5]);
            }
            /* set output directory */
            else if (!strncmp(argv[i], "-d", 2))
            {
                chdir(working_dir);
                mkdir(&argv[i][2]);
                chdir(&argv[i][2]);
            }
            else if (!strcmp(argv[i], "-pmd_debug"))
            {
                bGeneratePMDDebug = TRUE;
            }
            else if (!strcmp(argv[i], "-opmd_restricted") && (g_autogen_env & AUTOGEN_ENV_PRODUCT))
            {
                nGeneratePMDTypes |= AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED;
            }
            else if (!strcmp(argv[i], "-opmd_public"))
            {
                nGeneratePMDTypes |= AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC;
            }
            else if (!strcmp(argv[i], "-opmd"))
            {
                nGeneratePMDTypes |= AUTOGEN_PMD_FILE_RESTRICTION_RD;
            }
            else if (!strcmp(argv[i], "-oisihdr") && g_autogen_env == AUTOGEN_ENV_LOCAL)
            {
                output_srvhdr();
            }
            else if (!strcmp (argv [i], "-ohtml") && g_autogen_env == AUTOGEN_ENV_LOCAL)
            {
                output_html();
            }
            else if (!strcmp(argv[i], "-otsa") && g_autogen_env == AUTOGEN_ENV_LOCAL)
            {
                output_tsa();
            }
            else if (!strcmp(argv[i], "-oxml") && g_autogen_env == AUTOGEN_ENV_LOCAL)
            {
                output_xml(FALSE /*MakeAutobuilderVersionFiles*/);
            }
            else if (!strcmp(argv[i], "-oxml_autobuilder_version") && g_autogen_env == AUTOGEN_ENV_LOCAL)
            {
                output_xml(TRUE /*MakeAutobuilderVersionFiles*/);
            }
        }

        if (nGeneratePMDTypes != 0)
        {
            output_pmd(&out_filenames, nGeneratePMDTypes, bGeneratePMDDebug);
        }

        if (g_autogen_env == AUTOGEN_ENV_PRODUCT_MCU && g_trcgrp_conf[AUTOGEN_OBJ_TRACEGRP_MCU].conflicts)
        {
            printf("\nWarning: There is a conflict between defined MCU trace groups and traces");
            printf("\n - autogen.log contains details about the conflict");
            printf("\n - for more information about solving the problem,");
            printf("\n   please refer to autogen_user_guide.txt, section 4\n\n");
        }
        else if (g_has_warnings)
        {
            printf("\nThere are warnings. See autogen.log for details\n\n");
        }
        else
        {
            printf("\nDone...\n\n");
        }
    }
    else 
    {
        printf("\n\n");
    }

    chdir(working_dir);

    /* free PMD heap */
    pmd_heap_free();

    time(&finish);

    elapsed_time = difftime( finish, start );
    printf( "\nTime spent: %d:%2.2d.%3.3d\n", ((int)(elapsed_time)) / 60, ((int)(elapsed_time)) % 60,
        (int)((elapsed_time - (int)(elapsed_time))*1000.0f));

    fclose(g_log);

    return 0;
}


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: import_file

    Purpose: 
    Reads the file 'filename' into a buffer and remembers the name of it. Stores the name of
    the decoder that should use the condiguration file along with the file name
*/
/* --------------------------------------------------------------------------------------------- */

LOCAL void import_file(const char* filename, const char* decodername, unsigned int type, unsigned int flag)
{
    FILE* femb = fopen(filename, "rb");
    if (femb)
    {
        long size = 0;

        fseek(femb, 0, SEEK_END);
        size = ftell(femb);

        if (size > 0)
        {
            void* buffer = malloc(size);
            if (buffer)
            {
                autogen_embedded_file* emb;
                char shortname[256];

                if (strrchr(filename, '\\'))
                {
                    strcpy(shortname, strrchr(filename, '\\') + 1);
                }
                else if (strrchr(filename, '/'))
                {
                    strcpy(shortname, strrchr(filename, '/') + 1);
                }
                else
                {
                    strcpy(shortname, filename);
                }

                fseek(femb, 0, SEEK_SET);

                if (type == AUTOGEN_EMBEDDED_FILE_PMD)
                {
                    if (flag == AUTOGEN_PMD_FILE_RESTRICTION_RESTRICTED)
                    {
                        printf("- Importing restricted PMD file '%s'...\n\n", shortname);
                    }
                    else if (flag == AUTOGEN_PMD_FILE_RESTRICTION_PUBLIC)
                    {
                        printf("- Importing public PMD file '%s'...\n\n", shortname);
                    }
                    else
                    {
                        printf("- Importing PMD file '%s'...\n\n", shortname);
                    }
                }
                else
                {
                    printf("- Importing embedded file '%s'...\n\n", shortname);
                }

                fread(buffer, size, 1, femb);

                /* If PMD file then check PMD version number of embedded PMD for incompability against this PMD version */
                if (type == AUTOGEN_EMBEDDED_FILE_PMD)
                {
                    unsigned int pmd_version;

                    /* Extract the PMD version from the embedded PMD file */
                    if (extract_pmd_version(buffer, &pmd_version, shortname))
                    {
                        unsigned int current_ver = 0;

                        /* Compute version from PMD_FILE_FORMAT */
                        current_ver = ((PMD_FILE_FORMAT / 1000)       << 12)
                                    | ((PMD_FILE_FORMAT % 1000 / 100) <<  8)
                                    | ((PMD_FILE_FORMAT % 100 / 10)   <<  4)
                                    | (PMD_FILE_FORMAT % 10);

                        /* PMD version extracted. Check compatibility */
                        if (check_pmd_version_compatibility(current_ver, pmd_version) == PMD_FILE_FORMAT_INCOMPATIBEL)
                        {
                            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 11,
                                "The file format version (%04x) of the embedded PMD file '%s' is not compatible in Tracing SDK "
                                "with the file format version (%04x) of this PMD file. '%s' has been REMOVED!", pmd_version, shortname, current_ver, shortname);
                            printf("Error: Embedded PMD file '%s' is incompatible and has been removed. Please consult the autogen.log file for further details\n\n.", shortname);

                            /* Clean up */
                            fclose(femb);
                            free(buffer);
                            return;
                        }
                    }
                    else
                    {
                        printf("Warning: Errors in embedded PMD file '%s'. Please consult the autogen.log file for further details\n\n", shortname);
                    }
                }

                /* create embedded file object */
                emb = (autogen_embedded_file*)autogen_obj_create(NULL, 0, NULL, NULL, sizeof(autogen_embedded_file), AUTOGEN_OBJ_EMBEDDED_FILE, type,
                    0, pmd_heap_strdup(shortname), NULL);

                emb->base.ptr  = buffer;
                emb->base.flag = flag;

                emb->file_size    = size;
                emb->decoder_name = decodername;

                /* add embedded file object */
                autogen_obj_list_add_obj(g_emb_file_list, &emb->base, AUTOGEN_ENV_NONE);
            }
        }

        fclose(femb);
    }
    else
    {
        printf("- File '%s' could not be opened\n", filename);
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: extract_pmd_version

    Purpose:
    Will extract the PMD version number from the PMD XML header.
    
    Arguments:
      importfile  [in] : Memory array containing the embedded PMD file
      pmd_version [out]: PMD version number read from the embedded PMD file. 0 in case of errors.
      filename    [in] : Name of the embedded PMD file.

    Returns:
      0 : Error.
      1 : Ok. Argument pmd_version contains the extracted PMD version number
*/
/* --------------------------------------------------------------------------------------------- */
LOCAL int extract_pmd_version(const char *importfile, unsigned int *pmd_version, const char *filename)
{
    #define MAX_BUF_SIZE 1023
    char buffer[MAX_BUF_SIZE+1];
    int cnt;

    /* Set PMD version in case of errors */
    *pmd_version = 0;    

    /* Search for end of XML header (0x1A) in PMD data */
    cnt = 0;
    while(importfile[cnt] != 0x1a && cnt < MAX_BUF_SIZE)
    {
        buffer[cnt] = importfile[cnt];
        cnt++;
    }
    buffer[cnt] = '\0';

    /* Any problems reading the XML header? */
    if (cnt == MAX_BUF_SIZE)
    {
        /* Error: End of XML header not found */
        util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
            "XML header of embedded PMD file '%s' is not recognised.", filename);
        return 0;
    }

    /* Convert text string to XML data structure for easier searching for <FileFormat>xxx</FileFormat> */
    {
        xml_element *xml            = NULL;
        xml_element *ptr            = NULL;
        xml_element *fileformat_ptr = NULL;
        int errorcode = 0;

        /* Parse the xml document into a datastructure */
        xml = parsexml_parse(buffer, &errorcode);
        if (xml == NULL)
        {
            /* Error parsing the XML data in the PMD file header */
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
                "XML header of embedded PMD file '%s' can not be parsed (%s)", filename, (char *)parsexml_get_error_text(errorcode));
            return 0;
        }

        /* Get child of root element (PMDFileInfo) */
        ptr = xml->children_head;

        /* Check if <FileFormat> is present as tag under <PMDFileInfo> */
        fileformat_ptr = parsexml_find_element_tag(ptr->children_head, "FileFormat");
        if (fileformat_ptr == NULL)
        {
            /* Error: Tag <FileFormat> is not found */
            util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
                "PMD version not found in embedded PMD file '%s'", filename);

            /* Release XML data structure memory */
            parsexml_free_element(xml);

            return 0;
        }

        /* Extract PMD file format version */
        *pmd_version = pmd_version_conversion(fileformat_ptr->data);

        /* Release XML data structure memory */
        parsexml_free_element(xml);
    }

    return 1;
}

/* temporary function to be removed when new MCU trace concept is in place */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU

LOCAL void update_mcu_trace_group_text(const char* grpname, const char* dectext)
{
    autogen_trcgrp* trc_grp = NULL;
    autogen_it grp_it = INIT_ITERATOR;

    /* check trace group name and deccode text */
    if (!grpname || !dectext) return;

    /* find trace group object */
    grp_it.typemask = AUTOGEN_OBJ_TRACEGRP;
    grp_it.obj.name = grpname;

    trc_grp = (autogen_trcgrp*)autogen_obj_find_in_list(&grp_it, g_trcgrp_conf[AUTOGEN_OBJ_TRACEGRP_MCU].list[0]);
    if (trc_grp)
    {
        /* if no trace group decoding is defined, define one! */
        if (!prop_has(&trc_grp->base, PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT))
        {
            prop_add_string_to_object(&trc_grp->base, PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT, dectext, NULL, 0, FALSE);
        }
    }
}

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */ 

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DSP

LOCAL void import_dsp5_identifiers(const char* filename)
{
    if (filename && filename[0])
    {
        FILE* fdsp5 = fopen(filename, "rt");
        if (fdsp5)
        {
            char str_line[1025];
            const char* shortname = util_get_filename(filename);

            int is_process_id = FALSE;
            int is_process_data = FALSE;
            int is_interrupt_id = FALSE;
            int is_error_codes_list = FALSE;
            int is_error_codes_complex = FALSE;
            int is_gsm_warning_codes = FALSE;

            unsigned int unique_error_description_id = 1;
            unsigned int unique_error_extra_param_id = 1;

            int* last_group = NULL;

            int skip_double_lines = FALSE;
            int skip_lines = FALSE;

            autogen_it tbl_it = INIT_ITERATOR;
            autogen_tbl* tbl = NULL;

            autogen_res* sym_res = util_get_unique_res(RESOURCE_SYMBOLS);

            printf("- Importing file '%s'...\n\n", shortname ? shortname : filename);

            while(!feof(fdsp5))
            {
                autogen_obj* entry = NULL;

                fgets(str_line, 1024, fdsp5);

                if (skip_double_lines && str_line[0] != '=')
                {
                    continue;
                }
                else if (skip_lines && str_line[0] != '-')
                {
                    continue;
                }
                else if (skip_double_lines || skip_lines)
                {
                    skip_double_lines = FALSE;
                    skip_lines        = FALSE;
                    continue;
                }

                /* Parse task ID and and add to symbol table */
                if (is_process_id)
                {
                    if (str_line[0] == '\n' || str_line[0] == '\r')
                    {
                        *last_group = FALSE;
                        last_group  = NULL;
                    }
                    else
                    {
                        autogen_obj* attr;
                        char task_name[256] = "";
                        int task_id = 0;

                        sscanf(str_line, "%s %d", task_name, &task_id);

                        entry = autogen_obj_create(NULL, 0, sym_res, &tbl->base, sizeof(autogen_obj), 
                            AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, task_id, pmd_heap_strdup(task_name), NULL);

                        autogen_obj_list_init(&entry->child_list, entry, 0, 1);

                        attr = autogen_obj_create(NULL, 0, sym_res, entry, sizeof(autogen_pmd_info_attr), 
                            AUTOGEN_OBJ_PMD_INFO_ATTR, AUTOGEN_OBJ_ANY, 0, NULL, NULL);

                        autogen_obj_list_add_obj(&entry->child_list, attr, AUTOGEN_ENV_NONE);
                    }
                }
                /* Parse task data and add as attributes to existing task ID entry in symbol table */
                else if (is_process_data)
                {
                    if (str_line[0] == '\n' || str_line[0] == '\r')
                    {
                        *last_group = FALSE;
                        last_group  = NULL;
                    }
                    else
                    {
                        const char* token_task_name = strtok(str_line, " ,\"\t");
                        const char* token_task_type = strtok(NULL, " ,\"\t");
                        const char* token_task_prio = strtok(NULL, " ,\"\t");

                        if (token_task_name && token_task_type && token_task_prio)
                        {
                            autogen_obj* task_entry = NULL;
                            autogen_it entry_it = INIT_ITERATOR;

                            entry_it.obj.name = token_task_name;

                            /* find corresponding task entry in table */
                            task_entry = autogen_obj_find_in_list(&entry_it, &tbl->base.child_list);
                            if (task_entry && task_entry->child_list.n_obj > 0)
                            {
                                autogen_pmd_info_attr* attr = (autogen_pmd_info_attr*)autogen_obj_get_first_in_list(&task_entry->child_list);

                                attr->n_attr = 2;

                                /* process type */
                                attr->attr[PMD_INFO_ATTR_CDSP_TASKS_TYPE] = PMD_CDSP_TASK_TYPE_UNKNOWN;
                                if (!strcmp(token_task_type, "PRTYPE_IDLE"))
                                {
                                    attr->attr[PMD_INFO_ATTR_CDSP_TASKS_TYPE] = PMD_CDSP_TASK_TYPE_IDLE;
                                }
                                else if (!strcmp(token_task_type, "PRTYPE_INT"))
                                {
                                    attr->attr[PMD_INFO_ATTR_CDSP_TASKS_TYPE] = PMD_CDSP_TASK_TYPE_INTERRUPT;
                                }
                                else if (!strcmp(token_task_type, "PRTYPE_PRIO"))
                                {
                                    attr->attr[PMD_INFO_ATTR_CDSP_TASKS_TYPE] = PMD_CDSP_TASK_TYPE_PRIORITY;
                                }

                                /* priority */
                                attr->attr[PMD_INFO_ATTR_CDSP_TASKS_PRIORITY] = 255;
                                if (isdigit(token_task_prio[0]))
                                {
                                    attr->attr[PMD_INFO_ATTR_CDSP_TASKS_PRIORITY] = (unsigned int)atoi(token_task_prio);
                                }
                            }
                        }
                    }
                }
                /* Parse interrupt ID and add to symbol table */
                else if (is_interrupt_id)
                {
                    if (str_line[0] == '\n' || str_line[0] == '\r')
                    {
                        *last_group = FALSE;
                        last_group  = NULL;
                    }
                    else if (tbl)
                    {
                        char interrupt_name[256] = "";
                        int interrupt_id = 0;

                        sscanf(str_line, "%s %d", interrupt_name, &interrupt_id);

                        entry = autogen_obj_create(NULL, 0, sym_res, &tbl->base, sizeof(autogen_obj), 
                            AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, interrupt_id, pmd_heap_strdup(interrupt_name), NULL);
                    }
                }
                /* Parse simple error code list and add to symbol table */
                else if (is_error_codes_list)
                {
                    if (str_line[0] == '\n' || str_line[0] == '\r')
                    {
                        *last_group = FALSE;
                        last_group  = NULL;
                    }
                    else
                    {
                        char error_name[256] = "";
                        char error_id_text[256] = "";

                        sscanf(str_line, "%s %s", error_name, error_id_text);
                        if (error_name[0] && strlen(error_id_text) == 10)
                        {
                            autogen_pmd_info_attr* attr = NULL;

                            unsigned int error_id = 0;
                            int n;

                            /* convert HEX string to number */
                            for (n = 0; n < 8; n++)
                            {
                                if (error_id_text[n + 2] >= 'A' && error_id_text[n + 2] <= 'F')
                                {
                                    error_id += 10 + (error_id_text[n + 2] - 'A');
                                }
                                else if (error_id_text[n + 2] >= 'a' && error_id_text[n + 2] <= 'f')
                                {
                                    error_id += 10 + (error_id_text[n + 2] - 'a');
                                }
                                else
                                {
                                    error_id += error_id_text[n + 2] - '0';
                                }

                                if (n < 7) error_id <<= 4;
                            }

                            entry = autogen_obj_create(NULL, 0, sym_res, &tbl->base, sizeof(autogen_obj), 
                                AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, error_id, pmd_heap_strdup(error_name), NULL);

                            autogen_obj_list_init(&entry->child_list, entry, 0, 1);

                            attr = (autogen_pmd_info_attr*)autogen_obj_create(NULL, 0, sym_res, entry, sizeof(autogen_pmd_info_attr), 
                                AUTOGEN_OBJ_PMD_INFO_ATTR, AUTOGEN_OBJ_ANY, 0, NULL, NULL);
                            attr->n_attr = 2;

                            autogen_obj_list_add_obj(&entry->child_list, &attr->base, AUTOGEN_ENV_NONE);
                        }
                    }
                }
                /* Parse GSM exception codes */
                /* Expected format: */
                /*
                -----------------------
                <exception name>:
                Exceptionid: <id> (<id in 32 bits hex>)
                Traceid: <traceid> (<traceid in 32 bits hex>)
                Description: <descriptive text or '-'>
                -----------------------
                */ 
                else if (is_gsm_warning_codes)
                {
                    if (str_line[0] == '\n' || str_line[0] == '\r')
                    {
                        *last_group = FALSE;
                        last_group  = NULL;
                    }
                    else
                    {
                        const char* token_exception_name   = strtok(str_line, " \t:");

                        char str_error_lines[4][513] = { "", "", "", "" };

                        fgets(str_error_lines[0], 512, fdsp5); /* Exceptionid: */
                        fgets(str_error_lines[1], 512, fdsp5); /* Traceid: */
                        fgets(str_error_lines[2], 512, fdsp5); /* Description: */
                        fgets(str_error_lines[3], 512, fdsp5); /* -------- */

                        if (token_exception_name && 
                            strstr(str_error_lines[0], "Exceptionid: ") &&
                            strstr(str_error_lines[1], "Traceid: ") &&
                            strstr(str_error_lines[2], "Description: ") &&
                            strstr(str_error_lines[3], "---"))
                        {
                            autogen_pmd_info_attr* attr = NULL;

                            autogen_obj* id_entry = NULL;
                            autogen_it entry_it = INIT_ITERATOR;

                            autogen_obj* id_tbl = NULL;
                            autogen_it tbl_it = INIT_ITERATOR;

                            const char* token_trace_id_hex = strtok(&str_error_lines[1][27], ")");
                            const char* error_description  = strtok(&str_error_lines[2][13], "\n\r");
                            
                            unsigned int error_id = 0;
                            int n;

                            /* convert HEX string to number */
                            for (n = 0; n < 8; n++)
                            {
                                if (token_trace_id_hex[n + 2] >= 'A' && token_trace_id_hex[n + 2] <= 'F')
                                {
                                    error_id += 10 + (token_trace_id_hex[n + 2] - 'A');
                                }
                                else if (token_trace_id_hex[n + 2] >= 'a' && token_trace_id_hex[n + 2] <= 'f')
                                {
                                    error_id += 10 + (token_trace_id_hex[n + 2] - 'a');
                                }
                                else
                                {
                                    error_id += token_trace_id_hex[n + 2] - '0';
                                }

                                if (n < 7) error_id <<= 4;
                            }

                            entry = autogen_obj_create(NULL, 0, sym_res, &tbl->base, sizeof(autogen_obj), 
                                AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, error_id, pmd_heap_strdup(token_exception_name), NULL);

                            autogen_obj_list_init(&entry->child_list, entry, 0, 1);

                            attr = (autogen_pmd_info_attr*)autogen_obj_create(NULL, 0, sym_res, entry, sizeof(autogen_pmd_info_attr), 
                                AUTOGEN_OBJ_PMD_INFO_ATTR, AUTOGEN_OBJ_ANY, 0, NULL, NULL);
                            attr->n_attr = 2;

                            autogen_obj_list_add_obj(&entry->child_list, &attr->base, AUTOGEN_ENV_NONE);

                            /* Insert error description ID in list */
                            tbl_it.obj.name = "SYMBOLS_CDSP_ERROR_DESCRIPTION";

                            id_tbl = autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                            if (id_tbl)
                            {
                                entry_it.obj.name = error_description;

                                id_entry = autogen_obj_find_in_list(&entry_it, &id_tbl->child_list);
                                if (!id_entry)
                                {
                                    id_entry = autogen_obj_create(NULL, 0, sym_res, &tbl->base, sizeof(autogen_obj), 
                                        AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, unique_error_description_id++, 
                                        pmd_heap_strdup(error_description), NULL);

                                    autogen_obj_list_add_obj(&id_tbl->child_list, id_entry, AUTOGEN_ENV_NONE);
                                }

                                attr->attr[PMD_INFO_ATTR_CDSP_ERRORS_DESCRIPTION_ID] = id_entry->id;
                            }

                        }
                    }
                }
                /* Parse complex error code list and add to symbol table */
                else if (is_error_codes_complex)
                {
                    if (str_line[0] == '\n' || str_line[0] == '\r')
                    {
                        *last_group = FALSE;
                        last_group  = NULL;
                    }
                    else
                    {
                        const char* token_error_name   = strtok(str_line, " \t:");
                        const char* token_error_id     = strtok(NULL, " \t:");
                        const char* token_error_id_hex = strtok(NULL, " \t:()");

                        char str_error_lines[4][513] = { "", "", "", "" };

                        fgets(str_error_lines[0], 512, fdsp5);
                        fgets(str_error_lines[1], 512, fdsp5);
                        fgets(str_error_lines[2], 512, fdsp5);
                        fgets(str_error_lines[3], 512, fdsp5);

                        if (token_error_name && token_error_id && token_error_id_hex && strlen(token_error_id_hex) == 10 &&
                            strstr(str_error_lines[0], "Description: ") &&
                            strstr(str_error_lines[1], "Extra param: ") &&
                            strstr(str_error_lines[3], "---"))
                        {
                            autogen_pmd_info_attr* attr = NULL;

                            autogen_obj* id_entry = NULL;
                            autogen_it entry_it = INIT_ITERATOR;

                            autogen_obj* id_tbl = NULL;
                            autogen_it tbl_it = INIT_ITERATOR;

                            const char* error_description = strtok(&str_error_lines[0][13], "\n\r");
                            const char* extra_par = strtok(&str_error_lines[1][13], "\n\r");

                            unsigned int error_id = 0;
                            int n;

                            /* convert HEX string to number */
                            for (n = 0; n < 8; n++)
                            {
                                if (token_error_id_hex[n + 2] >= 'A' && token_error_id_hex[n + 2] <= 'F')
                                {
                                    error_id += 10 + (token_error_id_hex[n + 2] - 'A');
                                }
                                else if (token_error_id_hex[n + 2] >= 'a' && token_error_id_hex[n + 2] <= 'f')
                                {
                                    error_id += 10 + (token_error_id_hex[n + 2] - 'a');
                                }
                                else
                                {
                                    error_id += token_error_id_hex[n + 2] - '0';
                                }

                                if (n < 7) error_id <<= 4;
                            }

                            entry = autogen_obj_create(NULL, 0, sym_res, &tbl->base, sizeof(autogen_obj), 
                                AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, error_id, pmd_heap_strdup(token_error_name), NULL);

                            autogen_obj_list_init(&entry->child_list, entry, 0, 1);

                            attr = (autogen_pmd_info_attr*)autogen_obj_create(NULL, 0, sym_res, entry, sizeof(autogen_pmd_info_attr), 
                                AUTOGEN_OBJ_PMD_INFO_ATTR, AUTOGEN_OBJ_ANY, 0, NULL, NULL);
                            attr->n_attr = 2;

                            autogen_obj_list_add_obj(&entry->child_list, &attr->base, AUTOGEN_ENV_NONE);

                            /* Insert error description ID in list */
                            tbl_it.obj.name = "SYMBOLS_CDSP_ERROR_DESCRIPTION";

                            id_tbl = autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                            if (id_tbl)
                            {
                                entry_it.obj.name = error_description;

                                id_entry = autogen_obj_find_in_list(&entry_it, &id_tbl->child_list);
                                if (!id_entry)
                                {
                                    id_entry = autogen_obj_create(NULL, 0, sym_res, &tbl->base, sizeof(autogen_obj), 
                                        AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, unique_error_description_id++, pmd_heap_strdup(error_description), NULL);

                                    autogen_obj_list_add_obj(&id_tbl->child_list, id_entry, AUTOGEN_ENV_NONE);
                                }

                                attr->attr[PMD_INFO_ATTR_CDSP_ERRORS_DESCRIPTION_ID] = id_entry->id;
                            }

                            /* Insert error extra parameter ID in list */
                            tbl_it.obj.name = "SYMBOLS_CDSP_ERROR_EXTRA_PARAMETER";

                            id_tbl = autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                            if (id_tbl)
                            {
                                entry_it.obj.name = extra_par;

                                id_entry = autogen_obj_find_in_list(&entry_it, &id_tbl->child_list);
                                if (!id_entry)
                                {
                                    id_entry = autogen_obj_create(NULL, 0, sym_res, &tbl->base, sizeof(autogen_obj), 
                                        AUTOGEN_OBJ_TBLENTRY, AUTOGEN_TBLENTRY_CONST, unique_error_extra_param_id++, pmd_heap_strdup(extra_par), NULL);

                                    autogen_obj_list_add_obj(&id_tbl->child_list, id_entry, AUTOGEN_ENV_NONE);
                                }

                                attr->attr[PMD_INFO_ATTR_CDSP_ERRORS_EXTRA_PARAMETER_ID] = id_entry->id;
                            }
                        }
                    }
                }

                /* Start of task ID section ? */
                if (strstr(str_line, "PROCESS IDENTIFIERS"))
                {
                    tbl_it.obj.name = "SYMBOLS_CDSP_PROCESS_ID";
                    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                    if (tbl)
                    {
                        is_process_id = TRUE;
                    }

                    if (last_group) *last_group = FALSE;

                    last_group = &is_process_id;
                    skip_double_lines = TRUE;
                }
                /* Start of task data section ? */
                else if (strstr(str_line, "PROCESS TYPES AND PRIORITIES"))
                {
                    tbl_it.obj.name = "SYMBOLS_CDSP_PROCESS_ID";
                    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                    if (tbl)
                    {
                        is_process_data = TRUE;
                    }

                    if (last_group) *last_group = FALSE;

                    last_group = &is_process_data;
                    skip_double_lines = TRUE;
                }
                /* Start of interrupt ID section ? */
                else if (strstr(str_line, "Interrupt IDs"))
                {
                    tbl_it.obj.name = "SYMBOLS_CDSP_INTERRUPT_ID";
                    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                    if (tbl)
                    {
                        is_interrupt_id = TRUE;
                    }

                    if (last_group) *last_group = FALSE;

                    last_group = &is_interrupt_id;
                    skip_double_lines = TRUE;
                }
                /* Start of simple error list ? */
                else if (strstr(str_line, "Error and warning codes for application SW") ||
                    strstr(str_line, "OSE caller information reference table"))
                {
                    tbl_it.obj.name = "SYMBOLS_CDSP_ERROR_ID";
                    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                    if (tbl)
                    {
                        is_error_codes_list = TRUE;
                    }

                    if (last_group) *last_group = FALSE;

                    last_group = &is_error_codes_list;
                    skip_lines = TRUE;
                }
                /* Start of GSM exception list */
                else if (strstr(str_line, "Exception codes for GSM SW"))
                {
                    tbl_it.obj.name = "SYMBOLS_CDSP_ERROR_ID";
                    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                    if (tbl)
                    {
                        is_gsm_warning_codes = TRUE;
                    }

                    if (last_group) *last_group = FALSE;

                    last_group = &is_gsm_warning_codes;
                    skip_lines = TRUE;
                }
                /* Start of complex error list ? */
                else if (strstr(str_line, "WARNING CODES for SHARED SW") ||
                    strstr(str_line, "ERROR CODES for SHARED SW") ||
                    strstr(str_line, "WARNING CODES for Core SW") ||
                    strstr(str_line, "ERROR CODES for Core SW") ||
                    strstr(str_line, "ERROR CODES for OSE") ||
                    strstr(str_line, "WARNING CODES for WCDMA SW") ||
                    strstr(str_line, "ERROR CODES for WCDMA SW") ||
                    strstr(str_line, "WARNING CODES for RF HAL") ||
                    strstr(str_line, "ERROR CODES for RF HAL"))
                {
                    tbl_it.obj.name = "SYMBOLS_CDSP_ERROR_ID";
                    tbl = (autogen_tbl*)autogen_obj_find_in_list(&tbl_it, &sym_res->tbl_list);
                    if (tbl)
                    {
                        is_error_codes_complex = TRUE;
                    }

                    if (last_group) *last_group = FALSE;

                    last_group = &is_error_codes_complex;
                    skip_lines = TRUE;
                }

                /* If entry has been defined, add to current table */
                if (entry)
                {
                    autogen_obj_list_add_obj(&tbl->base.child_list, entry, AUTOGEN_ENV_NONE);
                }
            }
        }
        else
        {
            printf("- Error: dsp5_identifiers.txt file not found: '%s'\n", filename);
        }
    }
    else
    {
        printf("- Error: dsp5_identifiers.txt file name is not valid\n");
    }
}

#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_DSP */

void build_entry_points()
{
    #include "entry_points_m.h"
}

#ifdef AUTOGEN_INCLUDE_VENDOR_TRACES
/* Make separate source file for this? Is function needed at all? */
  void build_vendor_trace()
  {
  }
#endif /* AUTOGEN_INCLUDE_VENDOR_TRACES */

/*  End of file autogen_main.c  */

