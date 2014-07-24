/*
NOKIA
R&D Copenhagen
TSS









                Module definition
                -----------------

                SW Module






Status:           DRAFT

Continuus DB:     co_pctls

Project:          autogen

%name:            sig2macro.c %

%version:         co1tss#19 %

%instance:        co_pctls_1 %

%derived_by:      eliasen %

%date_modified:   Tue Jan 13 15:49:23 2009 %

Copyright (c) Nokia. All rights reserved

Change history:

VERSION     : fa1prot#18 DRAFT        14-Jun-2006  Robert White
REASON      : Improvement
REFERENCE   : -
DESCRIPTION : Added appropriate type qualifiers to remove compiler warnings.
              Check if SIG2MACRO_ADSP and SIG2MACRO_CDSP_CDMA macros are
              defined rather than their value.

VERSION     : 17         DRAFT        09-Jan-2006  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : FIxed compile error...

VERSION     : 15-16      DRAFT        14-Dec-2005  Christian Jacob Hansen
REASON      : Support for CDMA CDSP
REFERENCE   : -
DESCRIPTION : Support new type SIG2MACRO_CDSP_CDMA
              New trace macros supported TRACE_BEGIN/TRACE_END

VERSION     : 14         DRAFT        10-Oct-2004  Christian Jacob Hansen
REASON      : Bug fix, improved for ADSP
REFERENCE   : -
DESCRIPTION : Close individual files when combining macro files
              Change generatd resource type to RESOURCE_TRC_ADSP and 
              generated message type to MESSAGE_TRACE

VERSION     : 13         DRAFT        29-Dec-2003  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : Removed trace groups from TX signals for DSP5 CDSP traces

VERSION     : 11         DRAFT        03-Nov-2003  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : Changed environment variables to use new PMD properties

VERSION     : 10         DRAFT        29-Oct-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : Task co_pctls#23306
DESCRIPTION : Add CDSP version to DSP5 (CDSP) macro files

VERSION     : 9          DRAFT        20-Aug-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : Task co_pctls#22588
DESCRIPTION : Add support for version tool argument
              Updated version to 000.008

VERSION     : 8          DRAFT        29-Jul-2003  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : co_pctls#22276
DESCRIPTION : Updated embedded message generation for DSP5
              Updated version to 000.007

VERSION     : 7          DRAFT        17-Jul-2003  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : co_pctls#22143
DESCRIPTION : Changed rule for generating ISI message based traces (CDSP and ADSP)
              Updated version to 000.006

VERSION     : 6          DRAFT        20-May-2003  Christian Jacob Hansen
REASON      : Update
REFERENCE   : co_pctls#21509
DESCRIPTION : Updated version to 000.005

VERSION     : 5          DRAFT        09-May-2003  Christian Jacob Hansen
REASON      : Bugfix
REFERENCE   : Task co_pctls#21439
DESCRIPTION : Undigned enums (containing 0xXXX values were converting wrongly, 
              causing autogen to faile compilation of macro file

VERSION     : 4          DRAFT        08-Apr-2003  Christian Jacob Hansen
REASON      : Improvement
REFERENCE   : Task co_pctls#21108
DESCRIPTION : Added support for DSP5

VERSION     : 3          DRAFT        01-Apr-2003  Christian Jacob Hansen
REASON      : Improvement
REFERENCE   : -
DESCRIPTION : Added inclusion of task names (ADSP and CDSP)

VERSION     : 2          DRAFT        13-Feb-2003  Christian Jacob Hansen
REASON      : Improvement
REFERENCE   : -
DESCRIPTION : Added flag to define raw data as parameters
              Updeted sig2macro version to 000.002

VERSION     : 1          DRAFT        09-Jan-2003  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  This file is part of the source code for the sig2macro tool
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "sig2macro.h"


#define DSP_TYPE_CDSP      1
#define DSP_TYPE_ADSP      2
#define DSP_TYPE_DSP5      3
#define DSP_TYPE_GENERIC   4

#define ENUM_TYPE_DEC      0
#define ENUM_TYPE_HEX      1

#ifdef  SIG2MACRO_CDSP
#define TRACE_TYPE "WCDMA_CDSP_TRACE"
#elif   defined SIG2MACRO_ADSP
#define TRACE_TYPE "MESSAGE_TRACE"
#else
#define TRACE_TYPE "DSP5_TRACE"
#endif

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#define SIG2MACRO_VERSION_NUMBER        "000.009"
#define SIG2MACRO_VERSION_DATE          "10-Oct-2004"

#ifndef LOCAL
#define LOCAL static
#endif /* LOCAL */


typedef struct
{
    char sig_file[256];
    char sig_path[256];
    char macro_path[256];
    int should_exclude;
} t_sig_info;

typedef struct t_def_enum_data
{
    struct t_def_enum_data* next;
    char* name;
    int id;
    int type;
} def_enum_data;

typedef struct t_def_enum
{
    struct t_def_enum* next;
    struct t_def_enum_data* data;
    int is_used;
    char* name;
    int next_id;
    int type;
} def_enum;

typedef struct t_def_typedef
{
    struct t_def_typedef* next;
    int is_used;
    char* name;
    char* alias;
} def_typedef;

typedef struct t_def_struct_data
{
    struct t_def_struct_data* next;
    char* varname;
    int type;
    char* refname;
    int array;
    int q;
} def_struct_data;

typedef struct t_def_struct
{
    struct t_def_struct* next;
    struct t_def_struct_data* data;
    char* name;
    int valid;
    int is_isi_msg;
} def_struct;

typedef struct t_def_union
{
    struct t_def_union* next;
    char* name;
    int has_isi_msg_head;
} def_union;


LOCAL sig_file*     s_sig_file_list = NULL;
#ifdef  SIG2MACRO_CDSP
LOCAL int           s_dsp_type = DSP_TYPE_CDSP;
#elif   defined SIG2MACRO_ADSP
LOCAL int           s_dsp_type = DSP_TYPE_ADSP;
#elif   defined SIG2MACRO_CDSP_CDMA
LOCAL int           s_dsp_type = DSP_TYPE_GENERIC;
#else
LOCAL int           s_dsp_type = DSP_TYPE_DSP5;
#endif


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* returns a pointer to the filename in the file path */
LOCAL const char* find_filename(const char * filepath)
{
    const char* filename;

    /* remove path from file name */
    if ((filename = strrchr(filepath, '/')) != NULL)
    {
        filename++;
    }
    else
    if ((filename = strrchr(filepath, '\\')) != NULL)
    {
        filename++;
    }
    else
    {
        filename = filepath;
    }

    return filename;
}

/* removes any characters listed in 'str_remove' from 'str_line', and remove all trailing 
   spaces, new lines etc. from 'str_line'
*/
LOCAL void strip_line(char* str_line, char* str_remove)
{
    unsigned int j;
    int found = TRUE;;

    /* remove starting spaces */
    while (found)
    {
        found = FALSE;

        for (j = 0; j < strlen(str_remove); j++)
        {
            if (str_line[0] == str_remove[j])
            {
                unsigned int i;

                for (i = 0; i < strlen(str_line); i++)
                {
                    str_line[i] = str_line[i+1];
                }

                found = TRUE;
            }
        }
    }

    /* remove ending spaces */
    while (strlen(str_line) > 0 && 
        str_line[strlen(str_line)-1] == ' ' ||
        str_line[strlen(str_line)-1] == '\r' ||
        str_line[strlen(str_line)-1] == '\n' ||
        str_line[strlen(str_line)-1] == '\t')
    {
        str_line[strlen(str_line)-1] = 0;
    }
}


/* Find a token in 'str_line'. Uses all characters in 'seperators'
   for finding the token.
   If 'str_line' is empty, the last token string is used.
*/
LOCAL char* find_token(char* str_line, char* seperators)
{
    static char s_token_buffer[256];
    static char s_token[256];
    char* token = NULL;
    unsigned int i;


    s_token[0] = 0;

    if (str_line)
    {
        strcpy(s_token_buffer, str_line);
    }

    strip_line(s_token_buffer, seperators);


    for (i = 0; i < strlen(seperators); i++)
    {
        char* sep_index = strchr(s_token_buffer, seperators[i]);
        if (!token)
        {
            token = sep_index;
        }
        else
        if (sep_index && sep_index < token)
        {
            token = sep_index;
        }
    }

    if (token)
    {
        unsigned int offset  = token - s_token_buffer;
        unsigned int n_chars = strlen(s_token_buffer) - offset;

        strncpy(s_token, s_token_buffer, offset);
        s_token[offset] = 0;

        for (i = 0; i < n_chars; i++)
        {
            s_token_buffer[i] = s_token_buffer[i+offset+1];
        }

        token = s_token;
    }
    else
    if (s_token_buffer[0])
    {
        strcpy(s_token, s_token_buffer);
        s_token_buffer[0] = 0;

        token = s_token;
    }

    return token;
}


/* Returns the enum structure named 'name' in the enum list 'list'. 
*/
LOCAL def_enum* find_enum(def_enum* list, char* name)
{
    def_enum* enum_trav = list;

    while (enum_trav && (!enum_trav->name || strcmp(enum_trav->name, name)))
    {
        enum_trav = enum_trav->next;
    }

    return enum_trav;
}


/* Returns the union structure named 'name' in the union list 'list'. 
*/
LOCAL def_union* find_union(def_union* list, char* name)
{
    def_union* union_trav = list;

    while (union_trav && (!union_trav->name || strcmp(union_trav->name, name)))
    {
        union_trav = union_trav->next;
    }

    return union_trav;
}


/* Returns the structure named 'name' in the structure list 'list'. 
*/
LOCAL def_struct* find_struct(def_struct* list, char* name)
{
    char name_t[256];
    def_struct* struct_trav = list;

    sprintf(name_t, "%s_T", name);

    while (struct_trav && (!struct_trav->name || (strcmp(struct_trav->name, name) && strcmp(struct_trav->name, name_t))))
    {
        struct_trav = struct_trav->next;
    }

    return struct_trav;
}


/* Returns the typedef structure named 'name' in the typedef list 'list'. 
*/
LOCAL def_typedef* find_typedef(def_typedef* list, char* name)
{
    char name_t[256];
    def_typedef* typedef_trav = list;

    sprintf(name_t, "%s_T", name);

    while (typedef_trav && strcmp(typedef_trav->name, name) && strcmp(typedef_trav->name, name_t))
    {
        typedef_trav = typedef_trav->next;
    }

    return typedef_trav;
}


/* Generates an ITEM_PARAMETER definition
*/
LOCAL void generate_parameter(FILE* fmacro, int is_in_seq)
{
    fprintf(fmacro, "  PROPERTY(PROPERTY_PMD_PARAMETER)");
    fprintf(fmacro, (s_dsp_type == DSP_TYPE_DSP5 && !is_in_seq) ? " \\" : "");
    fprintf(fmacro, "\n");
}

/* Generates an arbitrary item definition
*/
LOCAL void generate_value(FILE* fmacro, int is_in_seq, char* format, char* varname)
{
    fprintf(fmacro, format, varname, varname);
    fprintf(fmacro, (s_dsp_type == DSP_TYPE_DSP5 && !is_in_seq) ? " \\" : "");
    fprintf(fmacro, "\n");
}



#define DATA_TYPE_UNKNOWN           0
#define DATA_TYPE_SIGNAL_IDENTIFIER 1
#define DATA_TYPE_BITS16            2
#define DATA_TYPE_BITS32            3
#define DATA_TYPE_UINT16            4
#define DATA_TYPE_UINT32            5
#define DATA_TYPE_INT16             6
#define DATA_TYPE_INT32             7
#define DATA_TYPE_BOOL16            8
#define DATA_TYPE_BOOL32            9
#define DATA_TYPE_QN                10
#define DATA_TYPE_ENUM              11
#define DATA_TYPE_POINTER           12
#define DATA_TYPE_NONE              13
#define DATA_TYPE_UNION             14


/* Generates the macro output for the structure item 'data'. The name of the signal is 'name'.
*/
LOCAL void generate_item(FILE* fmacro, char* signame, def_struct_data* data, int generate_array, int is_in_seq)
{
    /* should an array be defined instead of the actual item ? */
    if (generate_array && data->array > 1 && data->type != DATA_TYPE_NONE)
    {
        fprintf(fmacro, "  SEQ_OF(%s, \"%s\", %s_%s, %d)", data->varname, data->varname, 
            signame, data->varname, data->array);
        fprintf(fmacro, (s_dsp_type == DSP_TYPE_DSP5 && !is_in_seq) ? " \\" : "");
        fprintf(fmacro, "\n");
    }
    /* else just generate the item itself */
    else
    {
        switch (data->type)
        {
        case DATA_TYPE_BITS16:
            {
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  VALUE(16, BE, %s, \"%s\", HEX)", data->varname);
            }
            break;

        case DATA_TYPE_UINT16:
            {
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  VALUE(16, BE, %s, \"%s\", DEC)", data->varname);
            }
            break;

        case DATA_TYPE_INT16:
            {
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  VALUE(-16, BE, %s, \"%s\", DEC)", data->varname);
            }
            break;

        case DATA_TYPE_BITS32:
            {
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  VALUE(32, BE, %s, \"%s\", HEX)", data->varname);
            }
            break;

        case DATA_TYPE_UINT32:
            {
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  VALUE(32, BE, %s, \"%s\", DEC)", data->varname);
            }
            break;

        case DATA_TYPE_INT32:
            {
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  VALUE(-32, BE, %s, \"%s\", DEC)", data->varname);
            }
            break;

        case DATA_TYPE_BOOL16:
            {
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  VALUE_CONST(%s, \"%s\", TRUE_FALSE_16)", data->varname);
            }
            break;

        case DATA_TYPE_BOOL32:
            {
            generate_value    (fmacro, is_in_seq, "  FILLER(FILLER_FIXED, 16)", NULL);
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  VALUE_CONST(%s, \"%s\", TRUE_FALSE_16)", data->varname);
            }
            break;

        case DATA_TYPE_ENUM:
            {
            generate_parameter(fmacro, is_in_seq);
            fprintf(fmacro, "  VALUE_CONST(%s, \"%s\", %s)", data->varname, data->varname, data->refname);
            fprintf(fmacro, (s_dsp_type == DSP_TYPE_DSP5 && !is_in_seq) ? " \\" : "");
            fprintf(fmacro, "\n");
            }
            break;

        case DATA_TYPE_QN:
            {
            generate_parameter(fmacro, is_in_seq);
            fprintf(fmacro, "  VALUE(-16, BE, %s, \"%s\", Q%d)", data->varname, data->varname, data->q);
            fprintf(fmacro, (s_dsp_type == DSP_TYPE_DSP5 && !is_in_seq) ? " \\" : "");
            fprintf(fmacro, "\n");
            }
            break;

        case DATA_TYPE_POINTER:
            {
            generate_parameter(fmacro, is_in_seq);
            generate_value    (fmacro, is_in_seq, "  POINTER(BE, %s, \"%s\", POINTER_VOID)", data->varname);
            }
            break;

        case DATA_TYPE_SIGNAL_IDENTIFIER:
        case DATA_TYPE_UNION:
        case DATA_TYPE_NONE:
            {
            }
            break;
        }
    }
}


/* Begins a trace definition */
LOCAL void trace_begin(FILE* fmacro, const sig* sigptr)
{
    if (s_dsp_type == DSP_TYPE_GENERIC)
    {
        fprintf(fmacro, "TRACE_BEGIN(%s, \"%s\")\n", sigptr->name, sigptr->fileinfo->filename);
    }
    else if (s_dsp_type == DSP_TYPE_CDSP || s_dsp_type == DSP_TYPE_ADSP)
    {
        fprintf(fmacro, "MSG_BEGIN(%s, %s, \"\", \"\")\n", sigptr->name, TRACE_TYPE);
    }
    else if (s_dsp_type == DSP_TYPE_DSP5)
    {
        fprintf(fmacro, "#define SB_DATA_%s \\\n", sigptr->name);
        fprintf(fmacro, "  COMMON_SB_16_LONG \\\n");
    }
}


/* Ends a trace definition */
LOCAL void trace_end(FILE* fmacro, const sig* sigptr)
{
    if (s_dsp_type == DSP_TYPE_GENERIC)
    {
        fprintf(fmacro, "TRACE_END()\n");
    }
    else if (s_dsp_type == DSP_TYPE_CDSP || s_dsp_type == DSP_TYPE_ADSP)
    {
        fprintf(fmacro, "MSG_END\n\n");
    }
    else if (s_dsp_type == DSP_TYPE_DSP5)
    {
        fprintf(fmacro, "  FILLER(FILLER_VARIABLE, 32)\n\n");

        fprintf(fmacro, "  PROPERTY_VALUE (PROPERTY_PMD_TRACE_SOURCE, %s)\n", 
           sigptr->source);
        fprintf(fmacro, "  PROPERTY_STRING(PROPERTY_PMD_TRACE_LOGICAL_GROUP, \"%s\")\n", 
           sigptr->fileinfo->filename);
        fprintf(fmacro, "  PROPERTY_STRING(PROPERTY_PMD_TRACE_ACTIVATION_TEXT, \"%s\")\n", 
           sigptr->name);
        fprintf(fmacro, "  SB_BEGIN(DSP_SB_SIGNAL_RX_%s, \"\", \"\")\n", sigptr->name);
        fprintf(fmacro, "    SB_DATA_%s\n", sigptr->name);
        fprintf(fmacro, "  SB_END\n\n");

        fprintf(fmacro, "  PROPERTY_VALUE (PROPERTY_PMD_TRACE_SOURCE, %s)\n",
           sigptr->source);
        fprintf(fmacro, "  PROPERTY_STRING(PROPERTY_PMD_TRACE_LOGICAL_GROUP, \"%s\")\n", 
           sigptr->fileinfo->filename);
        fprintf(fmacro, "  PROPERTY_STRING(PROPERTY_PMD_TRACE_ACTIVATION_TEXT, \"\")\n");
        fprintf(fmacro, "  SB_BEGIN(DSP_SB_SIGNAL_TX_%s, \"\", \"\")\n", sigptr->name);
        fprintf(fmacro, "    SB_DATA_%s\n", sigptr->name);
        fprintf(fmacro, "  SB_END\n\n");
    }
}


#define STATE_INIT                  0
#define STATE_SIG_SECTION           1
#define STATE_TYPEDEF               2

#define STATE_TYPEDEF_ENUM          11
#define STATE_TYPEDEF_ENUM_DATA     12
#define STATE_TYPEDEF_ENUM_END      13

#define STATE_TYPEDEF_STRUCT        20
#define STATE_TYPEDEF_STRUCT_DATA   21
#define STATE_TYPEDEF_STRUCT_END    22

#define STATE_TYPEDEF_UNION         30
#define STATE_TYPEDEF_UNION_DATA    31
#define STATE_TYPEDEF_UNION_END     32


/* Converts the sig file pointed to by 'sigfile' to macro file
*/
LOCAL int convert_sig_2_macro(FILE* flog, sig* siglist, sig_file* sigfile)
{
    FILE* fsig = NULL;
    FILE* fmacro = NULL;
    int error = FALSE;

    /* only continue if the sig file should be converted */
    if (sigfile->should_exclude)
    {
        return error;
    }

    /* open sig file */
    fsig = fopen(sigfile->filepath, "rt");
    if (!fsig)
    {
        fprintf(flog, "Error: Could not open sig file '%s'\n\n", sigfile->filepath);
        printf("Error: Could not open sig file '%s'\n\n", sigfile->filepath);
        error = TRUE;
    }

    /* prepare macro file */
    if (!error)
    {
        /* open file */
        fmacro = fopen(sigfile->filepath_m, "wt");
        if (!fmacro)
        {
            fprintf(flog, "Error: Could not open macro file '%s'\n\n", sigfile->filepath_m);
            printf("Error: Could not open macro file '%s'\n\n", sigfile->filepath_m);
            error = TRUE;
        }

        /* print header */
    }

    /* convert the file */
    if (!error)
    {
        def_typedef* typedef_lst = NULL;
        def_enum* enum_lst = NULL;
        def_union* union_lst = NULL;
        def_struct* struct_lst = NULL;

        char str_line[256];
        char token_key[10] = " \t\n\r";
        int state = STATE_INIT;
        int line = 0;
        int in_comment = FALSE;
        unsigned int i;

        /* read all lines */
        while (!error && !feof(fsig))
        {
            line++;

            if (fgets(str_line, 255, fsig))
            {
                char* token;

                /* any comments? */
                while ((token = strstr(str_line, "/*")) != NULL)
                {
                    char* p_end;

                    /* remove complete comments */
                    if ((p_end = strstr(token+2, "*/")) != NULL)
                    {
                        p_end += 2;

                        for (i = 0; i < strlen(p_end) + 1; i++)
                        {
                            token[i] = p_end[i];
                        }
                    }
                    /* remove comment start and set flag */
                    else
                    {
                        *token = 0;
                        in_comment = TRUE;
                    }
                }

                /* remove comment end and clear flag */
                if (in_comment && strstr(str_line, "*/"))
                {
                    token = strstr(str_line, "*/") + 2;

                    for (i = 0; i < strlen(token) + 1; i++)
                    {
                        str_line[i] = token[i];
                    }

                    in_comment = FALSE;
                }

                /* is still in comment, read next line from file */
                if (in_comment)
                {
                    continue;
                }

                token = find_token(str_line, token_key);
                while (token)
                {
                    /* first check */
                    if (state == STATE_INIT)
                    {
                        /* right section found? */
                        if (!strcmp(token, "#else"))
                        {
                            state = STATE_SIG_SECTION;
                        }
                    }
                    else
                    if (state == STATE_SIG_SECTION)
                    {
                        /* typedef found ? */
                        if (!strcmp(token, "typedef"))
                        {
                            state = STATE_TYPEDEF;
                        }
                    }
                    else
                    if (state == STATE_TYPEDEF)
                    {
                        /* structure */
                        if (!strcmp(token, "struct") || !strcmp(token, "struct{"))
                        {
                            state = STATE_TYPEDEF_STRUCT;
                        }
                        /* enum */
                        else
                        if (!strcmp(token, "enum") || !strcmp(token, "enum{"))
                        {
                            state = STATE_TYPEDEF_ENUM;
                        }
                        /* enum */
                        else
                        if (!strcmp(token, "union") || !strcmp(token, "union{"))
                        {
                            state = STATE_TYPEDEF_UNION;
                        }
                        /* other type */
                        else
                        {
                            def_typedef* new_typedef = (def_typedef*)calloc(1, sizeof(def_typedef));

                            new_typedef->alias = (char*)strdup(token);
                            new_typedef->name  = NULL;
                            new_typedef->next  = typedef_lst;

                            typedef_lst = new_typedef;

                            /* set typedef name */
                            token = find_token(NULL, " \t;");
                            if (token)
                            {
                                new_typedef->name = (char*)strdup(token);
                            }
                            /* if not valid, delete typedef again */
                            else
                            {
                                typedef_lst = typedef_lst->next;

                                free(new_typedef->alias);
                                free(new_typedef);
                            }

                            state = STATE_SIG_SECTION;
                            token = NULL;
                        }
                    }
                    else
                    if (state == STATE_TYPEDEF_STRUCT_DATA)
                    {
                        if (!strcmp(token, "}"))
                        {
                            state = STATE_TYPEDEF_STRUCT_END;
                        }
                        else
                        if (token[0] == '}')
                        {
                            /* pass throught */
                        }
                        else
                        {
                            def_struct_data* data_trav = struct_lst->data;
                            def_struct_data* new_data = (def_struct_data*)calloc(1, sizeof(def_struct_data));

                            new_data->next  = NULL;
                            new_data->array = 1;

                            if (strlen(token) > 1 && token[strlen(token)-1] == '*')
                            {
                                new_data->type = DATA_TYPE_POINTER;
                            }
                            else
                            if (!strcmp(token, "bits16"))
                            {
                                new_data->type = DATA_TYPE_BITS16;
                            }
                            else
                            if (!strcmp(token, "bits32"))
                            {
                                new_data->type = DATA_TYPE_BITS32;
                            }
                            else
                            if (!strcmp(token, "uint16"))
                            {
                                new_data->type = DATA_TYPE_UINT16;
                            }
                            else
                            if (!strcmp(token, "uint32"))
                            {
                                new_data->type = DATA_TYPE_UINT32;
                            }
                            else
                            if (!strcmp(token, "int"))
                            {
                                new_data->type = DATA_TYPE_INT32;
                            }
                            else
                            if (!strcmp(token, "bool16"))
                            {
                                new_data->type = DATA_TYPE_BOOL16;
                            }
                            else
                            if (!strcmp(token, "bool32"))
                            {
                                new_data->type = DATA_TYPE_BOOL32;
                            }
                            else
                            if (!strcmp(token, "int16"))
                            {
                                new_data->type = DATA_TYPE_INT16;
                            }
                            else
                            if (!strcmp(token, "int32"))
                            {
                                new_data->type = DATA_TYPE_INT32;
                            }
                            else
                            if (!strcmp(token, "unsigned"))
                            {
                                token = find_token(NULL, " \t");
                                if (token && !strcmp(token, "int"))
                                {
                                    new_data->type = DATA_TYPE_UINT32;
                                }
                                else
                                if (token)
                                {
                                    new_data->type = DATA_TYPE_UNKNOWN;
                                    new_data->refname = (char*)calloc(1, strlen(token) + strlen("unsigned "));

                                    sprintf(new_data->refname, "unsigned %s", token);

                                    struct_lst->valid = FALSE;
                                }
                                else
                                {
                                    new_data->type = DATA_TYPE_UNKNOWN;
                                    new_data->refname = (char*)strdup("");

                                    struct_lst->valid = FALSE;
                                }
                            }
                            else
                            if (!strcmp(token, "q3_16"))
                            {
                                new_data->type = DATA_TYPE_QN;
                                new_data->q    = 3;
                            }
                            else
                            if (!strcmp(token, "q4_16"))
                            {
                                new_data->type = DATA_TYPE_QN;
                                new_data->q    = 4;
                            }
                            else
                            if (!strcmp(token, "q5_16"))
                            {
                                new_data->type = DATA_TYPE_QN;
                                new_data->q    = 5;
                            }
                            else
                            if (!strcmp(token, "q6_16"))
                            {
                                new_data->type = DATA_TYPE_QN;
                                new_data->q    = 6;
                            }
                            else
                            if (!strcmp(token, "q7_16"))
                            {
                                new_data->type = DATA_TYPE_QN;
                                new_data->q    = 7;
                            }
                            else
                            if (!strcmp(token, "q8_16"))
                            {
                                new_data->type = DATA_TYPE_QN;
                                new_data->q    = 8;
                            }
                            else
                            if (!strcmp(token, "SIGNAL_IDENTIFIER") ||
                                !strcmp(token, "A_SIGNAL_IDENTIFIER") ||
                                !strcmp(token, "C_SIGNAL_IDENTIFIER") ||
                                !strcmp(token, "G_SIGNAL_IDENTIFIER") ||
                                !strcmp(token, "S_SIGNAL_IDENTIFIER") ||
                                !strcmp(token, "W_SIGNAL_IDENTIFIER"))
                            {
                                new_data->type = DATA_TYPE_SIGNAL_IDENTIFIER;
                            }
                            else
                            if (!strcmp(token, "ISI_MSG_HEAD") || !strcmp(token, "SIG_ISI_HEADER"))
                            {
                                new_data->type = DATA_TYPE_NONE;

                                struct_lst->is_isi_msg = TRUE;
                            }
                            else
                            if (find_enum(enum_lst, token))
                            {
                                new_data->type    = DATA_TYPE_ENUM;
                                new_data->refname = (char*)strdup(token);

                                if (struct_lst->valid)
                                {
                                    find_enum(enum_lst, token)->is_used = TRUE;
                                }
                            }
                            else
                            if (find_union(union_lst, token))
                            {
                                new_data->type    = DATA_TYPE_UNION;
                                new_data->refname = (char*)strdup(token);

                                if (find_union(union_lst, token)->has_isi_msg_head)
                                {
                                    struct_lst->is_isi_msg = TRUE;
                                }
                            }
                            else
                            {
                                new_data->type    = DATA_TYPE_UNKNOWN;
                                new_data->refname = (char*)strdup(token);

                                struct_lst->valid = FALSE;
                            }

                            /* decode variable name (or pointer) */
                            token = find_token(NULL, " \t[;");
                            if (token)
                            {
                                if (!strcmp(token, "*"))
                                {
                                    new_data->type    = DATA_TYPE_POINTER;

                                    token = find_token(NULL, " \t[;");
                                    if (token)
                                    {
                                        new_data->varname = (char*)strdup(token);
                                    }

                                }
                                else
                                if (token[0] == '*')
                                {
                                    new_data->type    = DATA_TYPE_POINTER;
                                    new_data->varname = (char*)strdup(&token[1]);
                                }
                                else
                                {
                                    new_data->varname = (char*)strdup(token);
                                }
                            }

                            /* decode array */
                            token = find_token(NULL, "];");
                            if (token)
                            {
                                if (atoi(token) > 1)
                                {
                                    new_data->array = atoi(token);
                                }
                                else
                                {
                                    new_data->array = 0;
                                }
                            }

                            /* insert data as last element in enum list */
                            while (data_trav && data_trav->next)
                            {
                                data_trav = data_trav->next;
                            }

                            if (!data_trav)
                            {
                                struct_lst->data = new_data;
                            }
                            else
                            {
                                data_trav->next = new_data;
                            }

                            token = NULL;
                        }
                    }
                    else
                    if (state == STATE_TYPEDEF_STRUCT_END)
                    {
                        /* set name of structure */
                        struct_lst->name = (char*)strdup(token);
            
            if (!strcmp(token, "W_DEC_MSGR_MSG_T") ||
                            !strcmp(token, "W_MSGR_DEC_MSG_T") ||
                            !strcmp(token, "ISI_DSP_LOAD_MONITOR_REQ_T") ||
                            !strcmp(token, "ISI_DSP_LOAD_MONITOR_RESP_T"))
                        {
                            struct_lst->is_isi_msg = TRUE;
                        }

                        state = STATE_SIG_SECTION;
                        token = NULL;
                    }
                    else
                    if (state == STATE_TYPEDEF_ENUM_DATA)
                    {
                        if (!strcmp(token, "}"))
                        {
                            state = STATE_TYPEDEF_ENUM_END;
                        }
                        else
                        if (token[0] == '}')
                        {
                            /* pass throught */
                        }
                        else
                        {
                            def_enum_data* data_trav = enum_lst->data;
                            def_enum_data* new_data = (def_enum_data*)calloc(1, sizeof(def_enum_data));

                            new_data->name = (char*)strdup(token);
                            new_data->type = ENUM_TYPE_DEC;

                            /* try to parse an enum value */
                            token = find_token(NULL, " \t=,");
                            if (token)
                            {
                                /* decode enum value as hex */
                                if (!strncmp(token, "0x", 2))
                                {
                                    unsigned int i = 2;
                                    int scale = 1;

                                    new_data->id = 0;
                                    new_data->type = ENUM_TYPE_HEX;
                                    enum_lst->type = ENUM_TYPE_HEX;

                                    while (token[i] == '0')
                                    {
                                        ++i;
                                    }

                                    for (; i < strlen(token); i++)
                                    {
                                        int value = 0;

                                        token[i] = (char)toupper(token[i]);
                                        if (token[i] >= '0' && token[i] <= '9')
                                        {
                                            value = token[i] - '0';
                                        }
                                        else 
                                        {
                                            value = token[i] - 'A' + 10;
                                        }

                                        new_data->id *= scale;
                                        new_data->id += value;
                                        scale *= 16;
                                    }
                                }
                                /* decode enum value as decimal */
                                else
                                {
                                    new_data->id = atoi(token);
                                }
                            }
                            /* else just assign the next id as value */
                            else
                            {
                                new_data->id = enum_lst->next_id;
                                new_data->type = ENUM_TYPE_DEC;
                            }

                            /* prepare next enum id */
                            enum_lst->next_id = new_data->id + 1;

                            /* insert data as last element in enum list */
                            while (data_trav && data_trav->next)
                            {
                                data_trav = data_trav->next;
                            }

                            if (!data_trav)
                            {
                                enum_lst->data = new_data;
                            }
                            else
                            {
                                data_trav->next = new_data;
                            }

                            /* no more tokens in this line */
                            token = NULL;
                        }
                    }
                    else
                    if (state == STATE_TYPEDEF_UNION_DATA)
                    {
                        if (!strcmp(token, "}"))
                        {
                            state = STATE_TYPEDEF_UNION_END;
                        }
                        else
                        if (token[0] == '}')
                        {
                            /* pass throught */
                        }
                        else
                        {
                            if (!strcmp(token, "ISI_MSG_HEAD") || !strcmp(token, "SIG_ISI_HEADER"))
                            {
                                union_lst->has_isi_msg_head = TRUE;
                            }

                            token = NULL;
                        }
                    }
                    else
                    if (state == STATE_TYPEDEF_ENUM_END)
                    {
                        /* set name of enum */
                        enum_lst->name = (char*)strdup(token);

                        state = STATE_SIG_SECTION;
                        token = NULL;
                    }
                    else
                    if (state == STATE_TYPEDEF_UNION_END)
                    {
                        /* set name of union */
                        union_lst->name = (char*)strdup(token);

                        state = STATE_SIG_SECTION;
                        token = NULL;
                    }


                    /* second check */
                    if (state == STATE_TYPEDEF_STRUCT)
                    {
                        if (strchr(token, '{'))
                        {
                            /* create new struct */
                            def_struct* new_struct = (def_struct*)calloc(1, sizeof(def_struct));

                            new_struct->next  = struct_lst;
                            new_struct->data  = NULL;
                            new_struct->name  = NULL;
                            new_struct->valid = TRUE;
                            new_struct->is_isi_msg = FALSE;

                            struct_lst = new_struct;

                            state = STATE_TYPEDEF_STRUCT_DATA;
                        }
                    }
                    else
                    if (state == STATE_TYPEDEF_STRUCT_DATA && token && strchr(token, '}'))
                    {
                        /* set name of structure */
                        struct_lst->name = (char*)strdup(&token[1]);

                        state = STATE_SIG_SECTION;
                        token = NULL;
                    }
                    else
                    if (state == STATE_TYPEDEF_ENUM)
                    {
                        if (strchr(token, '{'))
                        {
                            /* create new enum */
                            def_enum* new_enum = (def_enum*)calloc(1, sizeof(def_enum));

                            new_enum->next    = enum_lst;
                            new_enum->data    = NULL;
                            new_enum->is_used = FALSE;
                            new_enum->name    = NULL;
                            new_enum->next_id = 0;
                            new_enum->type    = ENUM_TYPE_DEC;

                            enum_lst = new_enum;

                            state = STATE_TYPEDEF_ENUM_DATA;

                            /* if token also contains an enum, parse that... */
                            if (strcmp(token, "{"))
                            {
                                def_enum_data* data_trav = enum_lst->data;
                                def_enum_data* new_data = (def_enum_data*)calloc(1, sizeof(def_enum_data));

                                new_data->name = (char*)strdup(&token[1]);
                                new_data->type = ENUM_TYPE_DEC;

                                /* try to parse an enum value */
                                token = find_token(NULL, " \t=,");
                                if (token)
                                {
                                    /* decode enum value as hex */
                                    if (!strncmp(token, "0x", 2))
                                    {
                                        unsigned int i = 2;
                                        int scale = 1;

                                        new_data->id = 0;
                                        new_data->type = ENUM_TYPE_HEX;
                                        new_enum->type = ENUM_TYPE_HEX;

                                        while (token[i] == '0')
                                        {
                                            ++i;
                                        }
                                        for (; i < strlen(token); i++)
                                        {
                                            int value = 0;

                                            token[i] = (char)toupper(token[i]);
                                            if (token[i] >= '0' && token[i] <= '9')
                                            {
                                                value = token[i] - '0';
                                            }
                                            else 
                                            {
                                                value = token[i] - 'A' + 10;
                                            }

                                            new_data->id *= scale;
                                            new_data->id += value;
                                            scale *= 16;
                                        }
                                    }
                                    /* decode enum value as decimal */
                                    else
                                    {
                                        new_data->id = atoi(token);
                                    }
                                }
                                /* else just assign the next id as value */
                                else
                                {
                                    new_data->id = enum_lst->next_id;
                                    new_data->type = ENUM_TYPE_DEC;
                                }

                                /* prepare next enum id */
                                enum_lst->next_id = new_data->id + 1;

                                /* insert data as last element in enum list */
                                while (data_trav && data_trav->next)
                                {
                                    data_trav = data_trav->next;
                                }

                                if (!data_trav)
                                {
                                    enum_lst->data = new_data;
                                }
                                else
                                {
                                    data_trav->next = new_data;
                                }

                                /* no more tokens in this line */
                                token = NULL;
                            }
                        }
                    }
                    else
                    if (state == STATE_TYPEDEF_UNION)
                    {
                        if (strchr(token, '{'))
                        {
                            /* create new union */
                            def_union* new_union = (def_union*)calloc(1, sizeof(def_union));

                            new_union->next             = union_lst;
                            new_union->has_isi_msg_head = FALSE;
                            new_union->name             = NULL;

                            union_lst = new_union;

                            state = STATE_TYPEDEF_UNION_DATA;
                        }
                    }
                    else
                    if (state == STATE_TYPEDEF_ENUM_DATA && token && strchr(token, '}'))
                    {
                        /* set name of enum */
                        enum_lst->name = (char*)strdup(&token[1]);

                        state = STATE_SIG_SECTION;
                        token = NULL;
                    }
                    else
                    if (state == STATE_TYPEDEF_UNION_DATA && token && strchr(token, '}'))
                    {
                        /* set name of union */
                        union_lst->name = (char*)strdup(&token[1]);

                        state = STATE_SIG_SECTION;
                        token = NULL;
                    }


                    /* find next appropriate token */

                    if (state == STATE_TYPEDEF ||
                        state == STATE_TYPEDEF_STRUCT ||
                        state == STATE_TYPEDEF_UNION ||
                        state == STATE_TYPEDEF_ENUM)
                    {
                        strcpy(token_key, " \t\n\r");
                    }
                    else
                    if (state == STATE_TYPEDEF_ENUM_DATA)
                    {
                        strcpy(token_key, " \t\n\r,=;");
                    }
                    else
                    if (state == STATE_TYPEDEF_STRUCT_DATA ||
                        state == STATE_TYPEDEF_UNION_DATA)
                    {
                        strcpy(token_key, " \t\n\r;");
                    }
                    else
                    if (state == STATE_TYPEDEF_ENUM_END ||
                        state == STATE_TYPEDEF_UNION_END ||
                        state == STATE_TYPEDEF_STRUCT_END)
                    {
                        strcpy(token_key, " \t\n\r;");
                    }
                    else
                    {
                        strcpy(token_key, " \t\n\r");
                    }

                    /* find next token */
                    if (token)
                    {
                        token = find_token(NULL, token_key);
                    }
                }
            }
        }

        /* generate constant tables */
        {
            def_enum* enum_trav = enum_lst;

            while (enum_trav)
            {
                if (enum_trav->is_used)
                {
                    def_enum_data* data_trav = enum_trav->data;

                    fprintf(fmacro, "/* %s */\n\n", enum_trav->name);

                    if (enum_trav->type == ENUM_TYPE_HEX)
                    {
                        fprintf(fmacro, "CONST_TBL_BEGIN(%s, 16, BE, \"\", \"\")\n", enum_trav->name);
                    }
                    else
                    {
                        fprintf(fmacro, "CONST_TBL_BEGIN(%s, -16, BE, \"\", \"\")\n", enum_trav->name);
                    }

                    while (data_trav)
                    {
                        if (data_trav->type == ENUM_TYPE_HEX)
                        {
                            fprintf(fmacro, "  CONST_TBL_ENTRY(%s, 0x%4.4X, \"\")\n", data_trav->name, data_trav->id);
                        }
                        else
                        {
                            fprintf(fmacro, "  CONST_TBL_ENTRY(%s, %d, \"\")\n", data_trav->name, data_trav->id);
                        }
                        data_trav = data_trav->next;
                    }

                    fprintf(fmacro, "CONST_TBL_END\n\n");
                }

                enum_trav = enum_trav->next;
            }
        }

        /* generate trace sequences */
        {
            sig* sig_trav = siglist;

            while (sig_trav)
            {
                /* only look at signal, if it is in current file */
                if (sig_trav->fileinfo == sigfile)
                {
                    def_struct* struct_def;
                    def_typedef* struct_alias;
                    char* struct_name = sig_trav->name;

                    struct_alias = find_typedef(typedef_lst, struct_name);
                    while (struct_alias)
                    {
                        struct_name  = struct_alias->alias;
                        struct_alias = find_typedef(typedef_lst, struct_name);
                    }

                    fprintf(flog, "    Generating signal %s\n", sig_trav->name);
                    fprintf(fmacro, "/* %s */\n\n", sig_trav->name);

                    struct_def = find_struct(struct_lst, struct_name);
                    if (struct_def)
                    {
                        /* generate sequences for arrays */
                        if (!struct_def->is_isi_msg)
                        {
                            def_struct_data* data_trav;
                            int proceed = TRUE;

                            data_trav = struct_def->data;

                            while (data_trav && proceed)
                            {
                                if (data_trav->array == 0 || data_trav->type == DATA_TYPE_UNKNOWN)
                                {
                                    proceed = FALSE;
                                }
                                else
                                if (data_trav->array > 1)
                                {
                                    fprintf(fmacro, "SEQ_BEGIN(%s_%s, DONT_CREATE_STRUCT, \"\", \"\")\n", 
                                        sig_trav->name, data_trav->varname);

                                    generate_item(fmacro, sig_trav->name, data_trav, FALSE, TRUE);

                                    fprintf(fmacro, "SEQ_END\n\n");
                                }

                                data_trav = data_trav->next;
                            }
                        }

                        /* generate message */
                        trace_begin(fmacro, sig_trav);

                        /* does the signal contain an embedded message ? */
                        if (struct_def->is_isi_msg)
                        {
                            if (s_dsp_type == DSP_TYPE_DSP5)
                            { 
                                generate_value(fmacro, FALSE, "  FILLER(FILLER_FIXED, 16)", NULL);
                            }

                            generate_value(fmacro, FALSE, 
                                "  BLOCK_REF(BE, %s, \"%s\", BLOCK_PN_MSG, 0, 0, 0, REF_AS_MANY_AS_POSSIBLE)",
                                "msg");
                        }
                        /* else dump each element */
                        else
                        {
                            def_struct_data* data_trav = struct_def->data;
                            int proceed = TRUE;

                            while (data_trav && proceed)
                            {
                                if (data_trav->array == 0 || data_trav->type == DATA_TYPE_UNKNOWN)
                                {
                                    proceed = FALSE;

                                    /* print a comment in the log file */
                                    if (data_trav->type == DATA_TYPE_UNKNOWN)
                                    {
                                        fprintf(flog, "\n      *** Unknown data type %s - dumping rest of signal\n\n", data_trav->refname);
                                    }
                                    else
                                    {
                                        fprintf(flog, "\n      *** Unknown array size - dumping rest of signal\n\n");
                                    }
                                }
                                else
                                {
                                    generate_item(fmacro, sig_trav->name, data_trav, TRUE, FALSE);
                                }

                                data_trav = data_trav->next;
                            }

                            /* at last, dump the rest of the bytes */
                            generate_value(fmacro, FALSE, 
                                "  SEQ_OF_REF(%s, \"%s\", AUTOGEN_SEQ_WORD_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)", 
                                "ex_data");
                        }
                    }
                    else
                    {
                        fprintf(flog, "\n      *** Could not locate signal structure. Applying default structure\n\n");

                        trace_begin(fmacro, sig_trav);
            
                        /* apply default dump */
                        generate_value(fmacro, FALSE, 
                            "  SEQ_OF_REF(%s, \"%s\", AUTOGEN_SEQ_WORD_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)", 
                            "ex_data");
                    }

                    trace_end(fmacro, sig_trav);
                }

                sig_trav = sig_trav->next;
            }
        }

        /* free all typedef's */
        {
            while (typedef_lst)
            {
                def_typedef* typedef_trav = typedef_lst->next;

                free(typedef_lst->alias);
                free(typedef_lst->name);
                free(typedef_lst);

                typedef_lst = typedef_trav;
            }
        }

        /* free all enum's */
        {
            while (enum_lst)
            {
                def_enum_data* data_trav = enum_lst->data;
                def_enum* enum_trav = enum_lst->next;

                while (enum_lst->data)
                {
                    data_trav = enum_lst->data->next;

                    free(enum_lst->data->name);
                    free(enum_lst->data);

                    enum_lst->data = data_trav;
                }

                free(enum_lst->name);
                free(enum_lst);

                enum_lst = enum_trav;
            }
        }

        /* free all union's */
        {
            while (union_lst)
            {
                def_union* union_trav = union_lst->next;

                free(union_lst->name);
                free(union_lst);

                union_lst = union_trav;
            }
        }

        /* free all structuress */
        {
            while (struct_lst)
            {
                def_struct_data* data_trav = struct_lst->data;
                def_struct* struct_trav = struct_lst->next;

                while (struct_lst->data)
                {
                    data_trav = struct_lst->data->next;

                    free(struct_lst->data->refname);
                    free(struct_lst->data->varname);
                    free(struct_lst->data);

                    struct_lst->data = data_trav;
                }

                free(struct_lst->name);
                free(struct_lst);

                struct_lst = struct_trav;
            }
        }
    }

    if (fsig)
    {
        fclose(fsig);
    }

    if (fmacro)
    {
        fclose(fmacro);
    }


    return error;
}


/* Read task names from file and 
*/
LOCAL void generate_task_names(FILE* fout, char* task_filepath)
{
    if (task_filepath && task_filepath[0])
    {
        FILE* ftasks = fopen(task_filepath, "rt");
        if (ftasks)
        {
            char str_line[256];
            int found = FALSE;

            while (fgets(str_line, 255, ftasks))
            {
                if (!strncmp(str_line, "PROCESS const ", 14))
                {
                    char name[256] = "";
                    char* id;
                    char* token = find_token(str_line, " =;");
                    token = find_token(NULL, " =;");
                    token = find_token(NULL, " =;");

                    if (token)
                    {
                        strcpy(name, token);
                    }

                    id = find_token(NULL, " =;");

                    if (name[0] && id)
                    {
                        if (!found)
                        {
                            /* header */
                            fprintf(fout, "/* ========================================================================= */\n");
                            fprintf(fout, "/* Process ID's */\n");
                            fprintf(fout, "/* ========================================================================= */\n\n");

                            fprintf(fout, "CONST_TBL_BEGIN(PROCESS_ID_TBL, 16, BE, \"\", \"\")\n");
 
                            found = TRUE;
                        }

                        fprintf(fout, "  CONST_TBL_ENTRY(%s, %s, \"\")\n", name, id);
                    }
                }
            }

            if (found)
            {
                fprintf(fout, "CONST_TBL_END\n");
            }

            fclose(ftasks);
        }
        else
        {
            printf("Error: Could not open Process ID file %s\n\n", task_filepath);
        }
    }
}


/* Combines all macro files into the output file
*/
LOCAL int combine_macro_files(FILE* flog, sig* list, sig_file* file_list, 
                              char* output_filepath, char* task_filepath, char* version)
{
    int error = FALSE;

    if (!output_filepath[0])
    {
        printf("Error: No output file is defined (-o option)\n\n");
        error = TRUE;
    }

    if (!error)
    {
        FILE* fout = fopen(output_filepath, "wt");
        if (fout)
        {
            sig* signal_trav = list;
            sig_file* file_trav = file_list;
            char defname[256];
            unsigned int i;
            const char* output_filename = find_filename(output_filepath);

            /* build define name */
            sprintf(defname, "_%s_", output_filename);

            for (i = 0; i < strlen(defname); i++)
            {
                defname[i] = (char)toupper((char)defname[i]);

                if (defname[i] == ' ' || defname[i] == '.')
                {
                    defname[i] = '_';
                }
            }

            fprintf(fout, "#ifndef %s\n", defname);
            fprintf(fout, "#define %s\n\n", defname);


            /* write signal ID's */

            if (s_dsp_type == DSP_TYPE_DSP5)
            {
                fprintf(fout, "/* Signal Sub block ID's */\n");
                while (signal_trav)
                {
                    fprintf(fout, "#define DSP_SB_SIGNAL_RX_%-50s 0x%4.4X  /* %s */\n", 
                        signal_trav->name, signal_trav->id - 0x3000, signal_trav->fileinfo->filename);
                    fprintf(fout, "#define DSP_SB_SIGNAL_TX_%-50s 0x%4.4X  /* %s */\n", 
                        signal_trav->name, signal_trav->id - 0x2000, signal_trav->fileinfo->filename);

                    signal_trav = signal_trav->next;
                }
            }
            else
            {
                fprintf(fout, "/* Signal ID's */\n");
                while (signal_trav)
                {
                    fprintf(fout, "#define %-50s 0x%4.4X  /* %s */\n", 
                        signal_trav->name, signal_trav->id, signal_trav->fileinfo->filename);

                    signal_trav = signal_trav->next;
                }
            }
            fprintf(fout, "\n\n");

            /* write resource definition (start) */
            if (s_dsp_type == DSP_TYPE_CDSP)
            {
                if (version && version[0])
                {
                    fprintf(fout, "PROPERTY_STRING_INDEX(PROPERTY_PMD_ENVIRONMENT_VARIABLE, PMD_ENVIRONMENT_VAR_ID_CDSP_SW_VERSION, \"%s\")\n", version);
                }

                fputs("RES_BEGIN(RESOURCE_TRC_WCDMA_CDSP, AUTOGEN_NO_RESOURCE_ID, WCDSP, "
                      "\"WCDMA CDSP traces\", \"\", FALSE)\n\n", fout);
            }
            else if (s_dsp_type == DSP_TYPE_ADSP)
            {
                if (version && version[0])
                {
                    fprintf(fout, "PROPERTY_STRING_INDEX(PROPERTY_PMD_ENVIRONMENT_VARIABLE, PMD_ENVIRONMENT_VAR_ID_ADSP_SW_VERSION, \"%s\")\n", version);
                }

                fputs("RES_BEGIN(RESOURCE_TRC_ADSP, AUTOGEN_NO_RESOURCE_ID, ADSP, "
                      "\"ADSP traces\", \"\", FALSE)\n\n", fout);
            }
            else if (s_dsp_type == DSP_TYPE_DSP5)
            {
                if (version && version[0])
                {
                    fprintf(fout, "PROPERTY_STRING_INDEX(PROPERTY_PMD_ENVIRONMENT_VARIABLE, PMD_ENVIRONMENT_VAR_ID_CDSP_SW_VERSION, \"%s\")\n\n", 
                        version);
                }
            }
            else if (s_dsp_type == DSP_TYPE_GENERIC)
            {
                if (version && version[0])
                {
                    fprintf(fout, "PROPERTY_STRING_INDEX(PROPERTY_PMD_ENVIRONMENT_VARIABLE, PMD_ENVIRONMENT_VAR_ID_CDSP_SW_VERSION, \"%s\")\n", version);
                }

                fputs("RES_BEGIN(RESOURCE_TRC_CDMA_DSP, AUTOGEN_NO_RESOURCE_ID, CDMA, "
                      "\"CDMA CDSP traces\", \"\", FALSE)\n\n", fout);
            }

            /* copy content of each macro file to the combined file */
            while (file_trav)
            {
                FILE* fmacro = fopen(file_trav->filepath_m, "rt");
                if (fmacro)
                {
                    char str_line[256];

                    /* header */
                    fprintf(fout, "/* ========================================================================= */\n");
                    fprintf(fout, "/* Imported from file %s */\n", file_trav->filename_m);
                    fprintf(fout, "/* ========================================================================= */\n\n");

                    while (fgets(str_line, 255, fmacro))
                    {
                        fputs(str_line, fout);
                    }

                    fclose(fmacro);
                }
                else
                {
                    printf(" File '%s' does not exist\n", file_trav->filepath_m);
                }

                file_trav = file_trav->next;
            }

            /* write task names */
            generate_task_names(fout, task_filepath);

            /* write resource definition (end) */
            if (s_dsp_type == DSP_TYPE_CDSP || s_dsp_type == DSP_TYPE_ADSP || s_dsp_type == DSP_TYPE_GENERIC)
            {
                fputs("\nRES_END\n\n", fout);
            }

            fprintf(fout, "#endif /* %s */\n\n", defname);

            fclose(fout);
        }
        else
        {
            fprintf(flog, "Error: Could not open ouput file '%s' for writing\n\n", output_filepath);
            printf("Error: Could not open ouput file '%s' for writing\n\n", output_filepath);
            error = TRUE;
        }
    }

    return error;
}


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: main
 
    Purpose: 
        Main function of the tool
 
    Functional Description:
        -

    Arguments: 
        argc - [in] number of arguments passed to the tool (including the tool name itself)
        argv - [in] array of arguments (as strings)

    Return Values:
        1 on error, else 0
*/
/* --------------------------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{
    char str_output[256] = "";
    char str_tasks[256] = "";
    char str_version[256] = "";
    int error = FALSE;
    sig* signal_list = NULL;

    FILE* flog = fopen("sig2macro.log", "wt");
    if (!flog)
    {
        printf("Error: Could not open log file 'sig2macro.log' for writing\n\n");
        error = TRUE;
    }

    fprintf(flog, "sig2macro log file\n");
    fprintf(flog, "------------------------------------------------------------------------------\n");
    fprintf(flog, "Version:     %s\n", SIG2MACRO_VERSION_NUMBER);
    fprintf(flog, "------------------------------------------------------------------------------\n");


    if (argc > 1 && strcmp(argv[1], "-?") && strcmp(argv[1], "-h"))
    {
        int i;


        /* generate all signal ID's */
        if (!error)
        {
            error = generate_signal_ids(flog, &signal_list);
        }

        /* parse tool arguments */
        for (i = 1; i < argc; i++)
        {
            if (!strncmp(argv[i], "-m", 2))
            {
                /* insert path in all macro file names */
                sig_file* file_trav = s_sig_file_list;

                while (file_trav)
                {
                    free(file_trav->filepath_m);

                    file_trav->filepath_m = (char*)calloc(1, strlen(argv[i]) + strlen(file_trav->filename_m));
                    sprintf(file_trav->filepath_m, "%s/%s", &argv[i][2], file_trav->filename_m);

                    file_trav = file_trav->next;
                }
            }
            else
            if (!strncmp(argv[i], "-e", 2))
            {
                sig_file* file_trav = s_sig_file_list;

                while (file_trav && strcmp(file_trav->filename, &argv[i][2]))
                {
                    file_trav = file_trav->next;
                }

                if (file_trav)
                {
                    file_trav->should_exclude = TRUE;
                }
                else
                {
                    fprintf(flog, " Error: sig file '%s' can't be excluded, as it is not included at all...\n", &argv[i][2]);
                    printf(" Error: sig file '%s' can't be excluded, as it is not included at all...\n\n", &argv[i][2]);
                    error = TRUE;
                }
            }
            else
            if (!strncmp(argv[i], "-i", 2))
            {
            }
            else
            if (!strncmp(argv[i], "-o", 2))
            {
                strcpy(str_output, &argv[i][2]);
            }
            else
            if (!strncmp(argv[i], "-p", 2))
            {
                strcpy(str_tasks, &argv[i][2]);
            }
            else
            if (!strncmp(argv[i], "-v", 2))
            {
                strcpy(str_version, &argv[i][2]);
            }
            else
            {
                fprintf(flog, "Error: Unknown argument '%s'\n", argv[i]);
                printf("Error: Unknown argument '%s'\n", argv[i]);
                error = TRUE;
            }
        }

        if (!str_output[0])
        {
            fprintf(flog, " Error: Output file is not specified\n\n");
            printf(" Error: Output file is not specified\n\n");
            error = TRUE;
        }

        /* generate individual macro files */
        if (!error)
        {
            sig_file* file_trav = s_sig_file_list;

            fprintf(flog, "\nGenerating macro files\n");
            printf("\nGenerating macro files\n");

            while (file_trav && !error)
            {
                if (file_trav->should_exclude)
                {
                    fprintf(flog, "  Ignoring   file '%s'\n", file_trav->filename);
                    printf(" Ignoring   file '%s'\n", file_trav->filename);
                }
                else
                {
                    fprintf(flog, "  Converting file '%s' -> '%s'\n", 
                        file_trav->filename, file_trav->filename_m);
                    printf(" Converting file '%s' -> '%s'\n", 
                        file_trav->filename, file_trav->filename_m);
                }

                error = convert_sig_2_macro(flog, signal_list, file_trav);

                file_trav = file_trav->next;
            }
        }

        /* combine macro files */
        if (!error)
        {
            fprintf(flog, "\nGenerating output file '%s'\n", str_output);
            printf("\nGenerating output file '%s'\n", str_output);

            error = combine_macro_files(flog, signal_list, s_sig_file_list, str_output, str_tasks, str_version);
        }

        /* free signals */
        while (signal_list)
        {
            sig* sig_trav = signal_list->next;

            free(signal_list->name);
            free(signal_list);

            signal_list = sig_trav;
        }

        /* free signal files */
        while (s_sig_file_list)
        {
            sig_file* file_trav = s_sig_file_list->next;

            free(s_sig_file_list->filename);
            free(s_sig_file_list->filename_m);
            free(s_sig_file_list->filepath);
            free(s_sig_file_list->filepath_m);
            free(s_sig_file_list);

            s_sig_file_list = file_trav;
        }
    }
    else
    {
        /* show tool usage */
        printf("Sig2macro version %s, %s\n", SIG2MACRO_VERSION_NUMBER, SIG2MACRO_VERSION_DATE);
        printf("Copyright (c) Nokia Corporation. All rights reserved.\n");
        printf("\n");
        printf("sig2macro [options]\n");
        printf("\n");
        printf("Options are:\n");
        printf("%-20s%s\n", "-?",               "Shows this help");
        printf("%-20s%s\n", "-h",               "Shows this help");
        printf("%-20s%s\n", "-m<folder>",       "Path for macro files");
        printf("%-20s%s\n", "-i<filename>",     "Include file (enums and constants)");
        printf("%-20s%s\n", "-p<filename>",     "Process ID file");
        printf("%-20s%s\n", "-o<filename>",     "Combined output macro file");
        printf("%-20s%s\n", "-e<filename.sig>", "Exclude this sig file from conversion");
        printf("\n");
    }

    if (!error)
    {
        fprintf(flog, "\nDone...\n\n");
        printf("\nDone...\n\n");
    }

    if (flog)
    {
        fclose(flog);
    }

    return error;
}


/* Adds a signal ID to the list
*/
int add_signal_id(FILE* flog, sig** list, 
                  const char* filepath, int line, 
                  const char* name, unsigned int id, const char* source)
{
    int error = FALSE;
    const char* filename = NULL;
    sig* last = NULL;
    sig* trav = *list;
    sig* new_sig = (sig*)calloc(1, sizeof(sig));

    new_sig->name         = (char*)strdup(name);
    new_sig->source       = (char*)strdup(source);
    new_sig->id           = id;
    new_sig->is_generated = FALSE;
    new_sig->fileline     = line;

    /* remove path from file name */
    filename = find_filename(filepath);

    /* jump to the end of the list */
    while (!error && trav)
    {
        /* is the name already defined? If so, produce an error */
        if (!strcmp(trav->name, name))
        {
            fprintf(flog, "  Error: Signal '%s' defined twice\n", name);
            printf(" Error: Signal '%s' defined twice\n", name);
            error = TRUE;
        }

        last = trav;
        trav = trav->next;
    }

    /* should a new sig file be added? */
    if (!last || strcmp(last->fileinfo->filename, filename))
    {
        sig_file* file_trav = s_sig_file_list;
        sig_file* sigfile = (sig_file*)calloc(1, sizeof(sig_file));

        sigfile->filename = (char*)strdup(filename);
        sigfile->filepath = (char*)strdup(filepath);

        if (strrchr(filename, '.'))
        {
            sigfile->filepath_m = (char*)calloc(1, strlen(sigfile->filename) + 5);
            strcpy(sigfile->filepath_m, sigfile->filename);
            strcpy(strrchr(sigfile->filepath_m, '.'), "_m.h");

            /* remove path from file name */
            sigfile->filename_m = (char*)strdup(find_filename(sigfile->filepath_m));
        }
        else
        {
            fprintf(flog, "Error: Illegal sig filename encountered '%s'\n\n", sigfile->filename);
            printf("Error: Illegal sig filename encountered '%s'\n\n", sigfile->filename);
            error = TRUE;
        }

        /* add sigfile to list of files */
        while (file_trav && file_trav->next)
        {
            file_trav = file_trav->next;
        }

        if (file_trav)
        {
            file_trav->next = sigfile;
        }
        else
        {
            s_sig_file_list = sigfile;
        }

        new_sig->fileinfo = sigfile;
    }
    else
    {
        new_sig->fileinfo = last->fileinfo;
    }


    /* insert the new signal at the end of the list */
    if (!error)
    {
        if (last)
        {
            new_sig->next  = trav;
            last->next = new_sig;
        }
        else
        {
            *list = new_sig;
        }

        fprintf(flog, "  0x%4.4X %s (%s)\n", id, name, new_sig->fileinfo->filename);
        printf(" 0x%4.4X %s\n", id, name);
    }

    return error;
}

/* end of file sig2macro.c */
