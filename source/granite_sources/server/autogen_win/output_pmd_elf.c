/*
NOKIA 
R&D Copenhagen
CoreSW/Corleone









                output_pmd_elf.c
                ----------------
                SW Module






Project:          autogen

%name:            output_pmd_elf.c %
%version:         co1tss#23 %
%instance:        co1pctls_1 %
%derived_by:      nosterga %
%date_modified:   Thu Feb 17 16:14:14 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen

    This file contains the source code for the ELF parser used for adding debug information, i.e.
    functions, variables, filenames and linenumber, in the PMD file

    Note:
    If command line flag -pmd_debug is set, you will get a text file
    with debug info. This will normally be placed in autogen/pmd.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef AUTOGEN_INCLUDE_NOS_TRACES

/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
 #define LOCAL
#endif /* LOCAL */

#if (PMD_FILE_FORMAT >= 610)

#include "elfReader.h"
#include "dwarfReader.h"

/* Count DLL filenames in info object */
LOCAL int s_dll_filename_index = 0;

/* --------------------------------------------------------------------------------------------- */
/*  Name: extract_debuginfo_func
 
    Description: 
        Callback function used by dwarf_read_debug_info() when it has extracted an Debug Information Entry (DIE).
        Will store following infomation:
          DW_TAG_compile_unit
             DW_AT_name
             DW_AT_comp_dir
             DW_AT_low_pc
             DW_AT_high_pc
          DW_TAG_subprogram
             DW_AT_name
             DW_AT_decl_line
             DW_AT_low_pc
             DW_AT_high_pc

    Parameters:
        elfEnv  : Elf format information
        abbrev  : Abbreviation declaration along with collected data
        data    : Pointer to env->debuginfo where the debug information should be stored

    Returns:
        NULL - No problems
*/
/* --------------------------------------------------------------------------------------------- */
const char *extract_debuginfo_func(ElfEnvironment *elfEnv, Dwarf3_abbreviation *abbrev, void *data)
{
    pmd_debuginfo *user_data = (pmd_debuginfo *)data;
    elfEnv;

    if (abbrev->tag == 0x11 /* DW_TAG_compile_unit */)
    {
        list_element *ptr = NULL;

        const char *file_name           = NULL;
        const char *compile_dir         = NULL;
        unsigned long long low_address  = 0LL;
        unsigned long long high_address = 0LL;

        /* Loop through all attribute specifications and the collected data values */
        ptr = list_iterator_reset(abbrev->attribute_specification_list);
        while(ptr)
        {
            Dwarf3_attribute_specification *attr_spec = (Dwarf3_attribute_specification *)ptr->data;

            switch(attr_spec->name)
            {
            case 0x03: /* DW_AT_name - string */
                file_name = attr_spec->data.cptr;
                break;

            case 0x1b: /* DW_AT_comp_dir - string */
                compile_dir = attr_spec->data.cptr;
                break;

            case 0x11: /* DW_AT_low_pc - address */
                low_address = attr_spec->data.uint;
                break;

            case 0x12: /* DW_AT_high_pc - address */
                high_address = attr_spec->data.uint;
                break;

            default:
                break;
            }
            
            /* Next attribute specification */
            ptr = list_iterator_next(abbrev->attribute_specification_list);
        }

        /* Validate if a FileInfo object should be created */
        if (file_name && high_address > 0LL)
        {
            /* Create new FileInfo object and initialise it */
            pmd_debuginfo_FileInfo *file_info = (pmd_debuginfo_FileInfo *)pmd_heap_alloc(sizeof(pmd_debuginfo_FileInfo));
            memset(file_info, 0, sizeof(pmd_debuginfo_FileInfo));

            /* Store data */
            file_info->file_name    = pmd_heap_strdup(file_name);
            file_info->compile_dir  = pmd_heap_strdup(compile_dir);
            file_info->low_address  = low_address;
            file_info->high_address = high_address;

            /* Compute id of FileInfo object */
            file_info->id = ++user_data->current_fileinfo_id;

            /* Add FileInfo object to result list and store as the new current working element */
            user_data->current_compile_unit_element = list_add(user_data->file_info_list, file_info);
        } 
        else
        {
            /* Compile unit has been rejected */
            user_data->current_compile_unit_element = NULL;
        }

    } 
    else if (abbrev->tag == 0x2e /* DW_TAG_subprogram */)
    {
        list_element *ptr = NULL;

        const char *function_name        = NULL;
        unsigned int declared_line       = 0LL;
        unsigned long long low_address   = 0LL;
        unsigned long long high_address  = 0LL;

        /* Only accept a DW_TAG_subprogram if compile unit has been accepted */
        if (user_data->current_compile_unit_element)
        {
            /* Compile unit was accepted */

            /* Loop through all attribute specifications and the collected data values */
            ptr = list_iterator_reset(abbrev->attribute_specification_list);
            while(ptr)
            {
                Dwarf3_attribute_specification *attr_spec = (Dwarf3_attribute_specification *)ptr->data;

                switch(attr_spec->name)
                {
                case 0x03: /* DW_AT_name - string */
                    function_name = attr_spec->data.cptr;
                    break;

                case 0x3b: /* DW_AT_decl_line - constant */
                    declared_line = attr_spec->data.uint;
                    break;
                case 0x11: /* DW_AT_low_pc - address */
                    low_address = attr_spec->data.uint;
                    break;

                case 0x12: /* DW_AT_high_pc - address */
                    high_address = attr_spec->data.uint;
                    break;

                default:
                    break;
                }

                /* Next attribute specification */
                ptr = list_iterator_next(abbrev->attribute_specification_list);
            }

            /* Validate if a FuncInfo object should be created */
            if (function_name && high_address > 0LL)
            {
                /* Create new FuncInfo object and initialise it */
                pmd_debuginfo_FuncInfo *func_info = (pmd_debuginfo_FuncInfo *)pmd_heap_alloc(sizeof(pmd_debuginfo_FuncInfo));
                memset(func_info, 0, sizeof(pmd_debuginfo_FuncInfo));

                /* Store data */
                func_info->function_name = pmd_heap_strdup(function_name);
                func_info->declared_line = declared_line;
                func_info->low_address   = low_address;
                func_info->high_address  = high_address;

                /* Link id to correct FileInfo object */
                func_info->id = user_data->current_fileinfo_id;

                /* Add FuncInfo object to result list */
                list_add(user_data->func_info_list, func_info);
            }
        }
    } 

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dump_debuginfo
 
    Description: 
        Will dump the data stored in a pmd_debuginfo structure to a text file.
        To be used for debugging purposes.
 
    Parameters:
        fptr     : File pointer to text file where the debug information can be dumped
        dbg_info : Structure containint the debug information to be dumped

    Returns:
        NULL - No problems
*/
/* --------------------------------------------------------------------------------------------- */
void dump_debuginfo(FILE *fptr, pmd_debuginfo *dbg_info)
{
    if (fptr)
    {
        list_element *ptr = NULL;

        fprintf(fptr, "======================================================\n");
        fprintf(fptr, "== File debug info                                  ==\n");
        fprintf(fptr, "======================================================\n");

        /* Loop through all FileInfo objects */
        ptr = list_iterator_reset(dbg_info->file_info_list);
        while(ptr)
        {
            pmd_debuginfo_FileInfo *file_info = (pmd_debuginfo_FileInfo *)ptr->data;

            /* Dump FileInfo data */
            fprintf(fptr, "------------------------------------------------------\n");
            fprintf(fptr, "Compile unit: (ID: %u) %s\n", file_info->id, (file_info->file_name ? file_info->file_name : ""));
            fprintf(fptr, "  Compile dir: %s\n",     (file_info->compile_dir ? file_info->compile_dir : ""));
            fprintf(fptr, "  Low pc:      %016X\n",  file_info->low_address);
            fprintf(fptr, "  High pc:     %016X\n",  file_info->high_address);

            /* Next FileInfo object */
            ptr = list_iterator_next(dbg_info->file_info_list);
        }
        fprintf(fptr, "\n");

        fprintf(fptr, "======================================================\n");
        fprintf(fptr, "== Function debug info                              ==\n");
        fprintf(fptr, "======================================================\n");

        /* Loop through all FuncInfo objects */
        ptr = list_iterator_reset(dbg_info->func_info_list);
        while(ptr)
        {
            pmd_debuginfo_FuncInfo *func_info = (pmd_debuginfo_FuncInfo *)ptr->data;

            /* Dump FuncInfo data */
            fprintf(fptr, "------------------------------------------------------\n");
            fprintf(fptr, "  Subprogram:      %s\n",    (func_info->function_name ? func_info->function_name : ""));
            fprintf(fptr, "    Declared line: %u\n",    func_info->declared_line);
            fprintf(fptr, "    Low pc:        %016X\n", func_info->low_address);
            fprintf(fptr, "    High pc:       %016X\n", func_info->high_address);
            fprintf(fptr, "    File Id:       %u\n",    func_info->id);

            /* Next FuncInfo object */
            ptr = list_iterator_next(dbg_info->func_info_list);
        }
        fprintf(fptr, "\n");

        fprintf(fptr, "======================================================\n");
        fprintf(fptr, "== Line debug info                                  ==\n");
        fprintf(fptr, "======================================================\n");

        /* Loop through all LineInfo objects */
        ptr = list_iterator_reset(dbg_info->line_info_list);
        while(ptr)
        {
            pmd_debuginfo_LineInfo *line_info = (pmd_debuginfo_LineInfo *)ptr->data;

            /* Dump LineInfo data */
            fprintf(fptr, "Adress: %016llX  Line: %d\n", line_info->address, line_info->lineNo);

            /* Next LineInfo object */
            ptr = list_iterator_next(dbg_info->line_info_list);
        }
        fprintf(fptr, "\n");
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: extract_debuginfo_line
 
    Description: 
        Callback function used by dwarf_read_debug_line() when it has extracted an address/line pair.
        Used to store the address/line pairs in a pmd_debuginfo structure.
 
    Parameters:
        elfEnv  : Elf format information
        address : Address extracted from .debug_line section
        line    : Line extracted from .debug_line section
        data    : Pointer to env->debuginfo where the address/line pair should be stored

    Returns:
        NULL - No problems
*/
/* --------------------------------------------------------------------------------------------- */
const char *extract_debuginfo_line(ElfEnvironment *elfEnv, unsigned int address, unsigned int line, void *data)
{
    pmd_debuginfo *user_data = (pmd_debuginfo *)data;
    elfEnv;

    /* Validate if a LineInfo object should be created */
    if (address > 0)
    {
        /* Create new LineInfo object and initialise it */
        pmd_debuginfo_LineInfo *line_info = (pmd_debuginfo_LineInfo *)pmd_heap_alloc(sizeof(pmd_debuginfo_LineInfo));
        memset(line_info, 0, sizeof(pmd_debuginfo_LineInfo));

        /* Store data */
        line_info->address = address;
        line_info->lineNo = line;

        /* Add FileInfo object to result list and store as the new current working element */
        list_add(user_data->line_info_list, line_info);
    }

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: extract_variable_info
 
    Description: 
        Callback function used by elf_read_symtab() when it has extracted an Symbol Table Entry.
        Used to store the variable address and name info in info objects.
 
    Parameters:
        elfEnv       : Elf format information
        symtab_entry : Symbol Table Entry from which to extract variable address information
        data         : pmd_env data structure

    Returns:
        NULL - No problems
*/
/* --------------------------------------------------------------------------------------------- */
const char *extract_variable_info(ElfEnvironment *elfEnv, Elf32_Sym *symtab_entry, void *data)
{
    /* User data */
    pmd_env *env = (pmd_env *)data;

    /* If we have a STT_OBJECT then store name and address information */
    if (ELF32_ST_TYPE(symtab_entry->st_info == STT_OBJECT) && symtab_entry->st_size != 0)
    {
        if (elfEnv->elf_hdr.e_type == ET_DYN)
        {
            /* Data from shared library */
            pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED, 
                &elfEnv->elf_symtab_str_table[symtab_entry->st_name], symtab_entry->st_value, 
                3, symtab_entry->st_value + symtab_entry->st_size - 1, 0, s_dll_filename_index, 0);

            if (elfEnv->debug) fprintf(elfEnv->debug, "------> Data stored in PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED\n\n");
        }
        else if (elfEnv->elf_hdr.e_type == ET_EXEC)
        {
            /* Data from executable */
            pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_VARIABLES, 
                &elfEnv->elf_symtab_str_table[symtab_entry->st_name], symtab_entry->st_value, 
                2, symtab_entry->st_value + symtab_entry->st_size - 1, 0, 0, 0);

            if (elfEnv->debug) fprintf(elfEnv->debug, "------> Data stored in PMD_INFO_TYPE_MCU_DEBUG_VARIABLES\n\n");
        }

    }

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_elf_generate_elf
 
    Description: 
        Parses ELF file (.out file) and generates file/func/line number debug information
 
    Parameters:
        env          : PMD environment variable
        fout         : File pointer to opened .out file
        out_filename : File name of .out file (including path)

    Returns:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void pmd_elf_generate_elf(pmd_env* env, FILE* fout, char* out_filename)
{
    ElfEnvironment elfEnv;
    const char *basefilename = NULL;
    pmd_debuginfo *tmp_debuginfo_ptr = NULL;

    /* Compute the base filename. */
    basefilename = util_get_filename(out_filename);
    if (basefilename == NULL)
    {
        basefilename = out_filename;
    }

    /* Init elf environment data */
    elf_init_ElfEnvironment(&elfEnv);

    /* Save .out file and file name */
    elfEnv.elf_file = fout;

    /* If debug output should be generated */
    if (env->include_debug)
    {
        char debugFile[512];

        sprintf(debugFile, "pmd_debug_elf_processing_%s.txt", basefilename);
        elfEnv.debug = fopen(debugFile, "wt");
    }

    printf("- Parsing .out file (%s) for function/variable/filename info\n", basefilename);

    /* Read elf header and dump contents to debug file */
    elf_read_ElfHeader(&elfEnv);
    elf_dump_ElfHeader(&elfEnv);

    /* Read section header table and strings. */
    elf_read_SectionHeaderTable(&elfEnv, &(elfEnv.shtable));
    elf_read_SectionHeaderStringTable(&elfEnv);

    /* Dump section header table to debug file */
    elf_dump_SectionHeaderTable(&elfEnv);

    /* Create structure for storing debug information and stored it in the list in the pmd environment 'env' */
    tmp_debuginfo_ptr = env->debuginfo;
    env->debuginfo = pmd_debuginfo_create(env, pmd_heap_strdup(basefilename), elfEnv.elf_hdr.e_type);
    env->debuginfo->next = tmp_debuginfo_ptr;

    /* Read dwarf abbreviation tables (.debug_abbrev) */
    dwarf_read_debug_abbrev(&elfEnv);

    /* Read and parse dwarf file and function debug information (.debug_info) */
    dwarf_read_debug_info(&elfEnv, extract_debuginfo_func, env->debuginfo);

#ifdef AUTOGEN_PMD_LINE_NUMBERS
    /* Read and parse line information (.debug_line) */
    printf("- Parsing .out file (%s) for linenumber info\n", basefilename);
    dwarf_read_debug_line(&elfEnv, extract_debuginfo_line, env->debuginfo);
#endif

    /* Dump collected debug info to debug file */
    dump_debuginfo(elfEnv.debug, env->debuginfo);

    /* Read the string table (.strtab) used by the symbol table (.symtab) */
    elf_read_SymbolStringTable(&elfEnv);

    /* Generate DLL filename info object */
    if (elfEnv.elf_hdr.e_type == ET_DYN)
    {
        char *dll_filename = pmd_heap_strdup(basefilename);

        /* Cut off .out ending on the basefilename if present */
        char *dotptr = strrchr(dll_filename, '.');
        if (dotptr)
        {
            if (!strcmp(dotptr, ".out"))
            {
                /* Basefilename ends on a .out. Remove it */
                *dotptr = '\0'; 
            }
        }

        pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_DLL_FILENAMES, 
                    dll_filename, ++s_dll_filename_index, 
                    0, 0, 0, 0, 0);
    }

    /* Read and parse symbol table (.symtab) - extract variable name/address information */
    elf_read_symtab(&elfEnv, extract_variable_info, env);

    /* Free elf environment */
    elf_free_ElfEnvironment(&elfEnv);
}

#else

#define DW_LNS_copy             1
#define DW_LNS_advance_pc       2
#define DW_LNS_advance_line     3
#define DW_LNS_set_file         4
#define DW_LNS_set_column       5
#define DW_LNS_negate_stmt      6
#define DW_LNS_set_basic_block  7
#define DW_LNS_const_add_pc     8
#define DW_LNS_fixed_advance_pc 9
#define DW_LNE_end_Sequence     1
#define DW_LNE_set_address      2
#define DW_LNE_define_file      3

typedef unsigned short Elf32_Half;
typedef unsigned int Elf32_Word;
typedef int Elf32_Sword;
typedef unsigned int Elf32_Addr;
typedef unsigned int Elf32_Off;

/* Special Section Indexes */
#define SHN_UNDEF 0 /* */
#define SHN_LORESERVE 0xff00 /* */
#define SHN_LOPROC 0xff00 /* */
#define SHN_HIPROC 0xff1f /* */
#define SHN_LOOS 0xff20 /* */
#define SHN_HIOS 0xff3f /* */
#define SHN_ABS 0xfff1 /* */
#define SHN_COMMON 0xfff2 /* */
#define SHN_XINDEX 0xffff /* */
#define SHN_HIRESERVE 0xffff /* */

typedef struct
{
    unsigned char e_id_class;
    unsigned char e_id_data;
    unsigned char e_id_version;
    unsigned char e_id_osabi;
    unsigned char e_id_abiversion;
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;
    Elf32_Off e_phoff;
    Elf32_Off e_shoff;
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;
    Elf32_Half e_phentsize;
    Elf32_Half e_phnum;
    Elf32_Half e_shentsize;
    Elf32_Half e_shnum;
    Elf32_Half e_shstrndx;
} Elf32_Ehdr;

/* Elf32_Ehdr.e_type values */
#define ET_NONE 0 /* No file type */
#define ET_REL 1 /* Relocatable file */
#define ET_EXEC 2 /* Executable file */
#define ET_DYN 3 /* Shared object file */
#define ET_CORE 4 /* Core file */
#define ET_LOOS 0xfe00 /* Operating system-specific */
#define ET_HIOS 0xfeff /* Operating system-specific */
#define ET_LOPROC 0xff00 /* Processor-specific */
#define ET_HIPROC 0xffff /* Processor-specific */

/* Elf32_Ehdr.e_id_class values */
#define ELFCLASSNONE 0 /* Invalid class */
#define ELFCLASS32 1 /* 32-bit objects */
#define ELFCLASS64 2 /* 64-bit objects */

/* Elf32_Ehdr.e_id_data values */
#define ELFDATANONE 0 /* Invalid data encoding */
#define ELFDATA2LSB 1 /* See below */
#define ELFDATA2MSB 2 /* See below */

/* Elf32_Ehdr.e_version values */
#define EV_NONE 0 /* Invalid version */
#define EV_CURRENT 1 /* Current version */


typedef struct 
{
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off sh_offset;
    Elf32_Word sh_size;
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
} Elf32_Shdr;

/* Section types Elf32_Shdr.sh_type */
#define SHT_NULL 0 /* */
#define SHT_PROGBITS 1 /* */
#define SHT_SYMTAB 2 /* */
#define SHT_STRTAB 3 /* */
#define SHT_RELA 4 /* */
#define SHT_HASH 5 /* */
#define SHT_DYNAMIC 6 /* */
#define SHT_NOTE 7 /* */
#define SHT_NOBITS 8 /* */
#define SHT_REL 9 /* */
#define SHT_SHLIB 10 /* */
#define SHT_DYNSYM 11 /* */
#define SHT_INIT_ARRAY 14 /* */
#define SHT_FINI_ARRAY 15 /* */
#define SHT_PREINIT_ARRAY 16 /* */
#define SHT_GROUP 17 /* */
#define SHT_SYMTAB_SHNDX 18 /* */
#define SHT_LOOS 0x60000000 /* */
#define SHT_HIOS 0x6fffffff /* */
#define SHT_LOPROC 0x70000000 /* */
#define SHT_HIPROC 0x7fffffff /* */
#define SHT_LOUSER 0x80000000 /* */
#define SHT_HIUSER 0xffffffff /* */

/* Section attibute flags Elf32_Shdr.sh_flags */
#define SHF_WRITE 0x1 /* */
#define SHF_ALLOC 0x2 /* */
#define SHF_EXECINSTR 0x4 /* */
#define SHF_MERGE 0x10 /* */
#define SHF_STRINGS 0x20 /* */
#define SHF_INFO_LINK 0x40 /* */
#define SHF_LINK_ORDER 0x80 /* */
#define SHF_OS_NONCONFORMING 0x100 /* */
#define SHF_GROUP 0x200 /* */
#define SHF_TLS 0x400 /* */
#define SHF_MASKOS 0x0ff00000 /* */
#define SHF_MASKPROC 0xf0000000 /* */

typedef struct 
{
    Elf32_Word st_name;
    Elf32_Addr st_value;
    Elf32_Word st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf32_Half st_shndx;
} Elf32_Sym;

/* Symbol types (LSN of Elf32_Sym.st_info) */
#define STT_NOTYPE 0 /* */
#define STT_OBJECT 1 /* */
#define STT_FUNC 2 /* */
#define STT_SECTION 3 /* */
#define STT_FILE 4 /* */
#define STT_COMMON 5 /* */
#define STT_TLS 6 /* */
#define STT_LOOS 10 /* */
#define STT_HIOS 12 /* */
#define STT_LOPROC 13 /* */
#define STT_HIPROC 15 /* */

#define ELF32_ST_TYPE(i)   ((i)&0xf)

/* Symbol bindings (MSN of Elf32_Sym.st_info) */
#define STB_LOCAL 0 /* */
#define STB_GLOBAL 1 /* */
#define STB_WEAK 2 /* */
#define STB_LOPROC 13 /* */
#define STB_HIPROC 15 /* */

#define ELF32_ST_BIND(i)   ((i)>>4)

typedef struct
{
    Elf32_Word total_length;
    Elf32_Half version;
    Elf32_Word prologue_length;
    unsigned char minimum_instruction_length;
    unsigned char default_is_stmt;
    signed char line_base;
    unsigned char line_range;
    unsigned char opcode_base;
    unsigned char standard_opcode_lengths[256];
} Dwarf2_LinePrologue;

typedef struct 
{
    Elf32_Addr Addr;
    Elf32_Word LineNumber;
    Elf32_Word ID;
    } ElfLineEntry;

typedef struct 
    {
    Elf32_Addr Addr1;
    Elf32_Addr Addr2;
    Elf32_Word Name;
    unsigned int FilenameIndex;
    char HasLines;
} ElfSymbolEntry;

typedef struct 
{
    unsigned int Index;
    const char* Name;
    char HasFuncs;
} ElfFilenameEntry;

#define READ_BYTE(bvalue) \
    if (!elf_read_byte(elfEnv->elf_file, &bvalue)) return "XXX";

#define READ_BYTES(buffer, nbytes) \
    if (!elf_read_bytes(elfEnv->elf_file, buffer, nbytes)) \
    { \
        pmd_elf_close_file(elfEnv); \
        return "Unexpected end of file"; \
    }

#define READ_WORD(svalue) \
    if (!elf_read_word(elfEnv->elf_file, elfEnv->elf_dataorder, &svalue)) \
    { \
        pmd_elf_close_file(elfEnv); \
        return "Unexpected end of file"; \
    }

#define READ_DWORD(lvalue) \
    if (!elf_read_dword(elfEnv->elf_file, elfEnv->elf_dataorder, &lvalue)) \
    { \
        pmd_elf_close_file(elfEnv); \
        return "Unexpected end of file"; \
    }

/* 
  Structure containing various information carried around among the various 
  ELF parsing functions 
*/
typedef struct {
    /* Actual .out file being read from */
    FILE* elf_file;

    /* ELF header */
    Elf32_Ehdr elf_hdr;

    /* Endianess of ELF file */
    unsigned char elf_dataorder;

    /* Section index of symbols section (.symtab) in .out file */
    Elf32_Half elf_symtab_index;

    /* Section index of debug line section (.debug_line) in .out file */
    Elf32_Half elf_debugline_index;

    /* Pointer to symbol strings read from ELF file */
    char* elf_sym_strings;

    /* Pointer to strings read from ELF file */
    char* elf_sec_strings;

    /* Storage of function info and number of entries */
    ElfSymbolEntry* elf_functions;
    size_t elf_n_functions;

    /* Storage of variable info and number of entries */
    ElfSymbolEntry* elf_variables;
    size_t elf_n_variables;

    /* Storage of filenames info and numbers of entries */
    ElfFilenameEntry* elf_filenames;
    size_t elf_n_filenames;

    /* Storage of line number info and number of entries */
    ElfLineEntry* elf_lines;
    size_t elf_n_lines;

    /* Base filename of .out file */
    const char* basefilename;

    /* Various debugging info */
    struct {
        int elf_line_outside_func;
        int elf_line_dupl_addr;
        int elf_line_last_ref;
        int elf_line_first_last;
        int elf_line_skip;
        int elf_line_first;
        int elf_line_last;
        int elf_func_empty;
    } ElfDebugInfo;
} ElfEnvironment;

/* Count DLL filenames in info object */
LOCAL int s_dll_filename_index = 0;

LOCAL const char* pmd_elf_open_file(ElfEnvironment *elfEnv, FILE* fout, const char* filename, int* has_func, int* has_line);
LOCAL const char* pmd_elf_generate_functions(pmd_env* env, ElfEnvironment *elfEnv, FILE* fdebugelf);
#ifdef AUTOGEN_PMD_LINE_NUMBERS
  LOCAL const char* pmd_elf_generate_linenumbers(pmd_env* env, ElfEnvironment *elfEnv, FILE* fdebugelf);
#endif
LOCAL void pmd_elf_generate_objects(pmd_env* env, ElfEnvironment *elfEnv);
LOCAL void pmd_elf_close_file(ElfEnvironment *elfEnv);

LOCAL unsigned short elf_fix_word(unsigned char elf_dataorder, unsigned short w);
LOCAL unsigned int   elf_fix_dword(unsigned char elf_dataorder, unsigned int l);

LOCAL int elf_read_byte(FILE* s_elf_file, unsigned char* bvalue);
LOCAL int elf_read_bytes(FILE* s_elf_file, unsigned char* buffer, unsigned int nbytes);
LOCAL int elf_read_word(FILE* elf_file, unsigned char elf_dataorder, unsigned short* svalue);
LOCAL int elf_read_dword(FILE* elf_file, unsigned char elf_dataorder, unsigned int* lvalue);

LOCAL const char* elf_read_header(ElfEnvironment *elfEnv);
LOCAL void* elf_read_section_data(FILE *elf_file, Elf32_Shdr* pshdr);
LOCAL const char* elf_read_section_header(ElfEnvironment *elfEnv, unsigned int index, Elf32_Shdr* pshdr);
LOCAL const char* elf_read_symbol(ElfEnvironment *elfEnv, Elf32_Sym* psym);

LOCAL unsigned int COFFinfo_read_ULEB128(FILE *elf_file, Elf32_Word* offset);
LOCAL signed   int COFFinfo_read_SLEB128(FILE *elf_file, unsigned int* offset);

LOCAL int ElfFunctionEntriesByAddr(const void* Elem1, const void* Elem2);
LOCAL int ElfLineEntriesByAddr(const void* Elem1, const void* Elem2);

LOCAL int CheckAndAllocateMemory(ElfEnvironment *elfEnv, void **data, size_t elements, size_t *max_elements, size_t element_size);

#define GET_FUNC_FILENAME(index) elfEnv->elf_filenames[elfEnv->elf_functions[index].FilenameIndex-1].Name
#define GET_VAR_FILENAME(index)  elfEnv->elf_filenames[elfEnv->elf_variables[index].FilenameIndex-1].Name

/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */

/* --------------------------------------------------------------------------------------------- */
/*  Name: pmd_elf_generate_elf
 
    Description: 
        Parses ELF file (.out file) and generates file/line number info objects
 
    Returns:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void pmd_elf_generate_elf(pmd_env* env, FILE* fout, char* out_filename)
{
    int has_funcs = FALSE;
    int has_lines = FALSE;
    const char* elf_code = NULL;
    FILE *fdebugelf = NULL;

    /* Initialise environment data carried among the various functions */
    ElfEnvironment elfEnv = {
        NULL, 
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        ELFDATANONE,
        SHN_UNDEF,
        SHN_UNDEF,
        NULL,
        NULL,
        NULL, 0,
        NULL, 0,
        NULL, 0,
        NULL, 0,
        NULL,
        { 0,0,0,0,0,0,0,0 }
    };

    /* Compute the base filename. */
    elfEnv.basefilename = util_get_filename(out_filename);
    if (elfEnv.basefilename == NULL)
    {
        elfEnv.basefilename = out_filename;
    }

    /* If debug output should be generated */
    if (env->include_debug)
    {
        char debugFile[512];

        sprintf(debugFile, "pmd_debug_elf_processing_%s.txt", elfEnv.basefilename);
        fdebugelf = fopen(debugFile, "wt");
    }

    /* Open ELF file */
    elf_code = pmd_elf_open_file(&elfEnv, fout, out_filename, &has_funcs, &has_lines);
    if (elf_code && elf_code[0])
    {
        printf("    Error: %s\n", elf_code);
    }
    /* Generate function/variable/filename info */
    if (!elf_code && has_funcs)
    {
        printf("- Parsing .out file (%s) for function/variable/filename info\n", out_filename);
        elf_code = pmd_elf_generate_functions(env, &elfEnv, fdebugelf);
        if (elf_code && elf_code[0])
        {
            printf("    Error: %s\n", elf_code);
        }
    }

#ifdef AUTOGEN_PMD_LINE_NUMBERS
    /* Generate linenumber info */
    if (!elf_code && has_lines)
    {
        printf("- Parsing .out file (%s) for linenumber info\n", out_filename);
        elf_code = pmd_elf_generate_linenumbers(env, &elfEnv, fdebugelf);
        if (elf_code && elf_code[0])
        {
            printf("    Error: %s\n", elf_code);
        }
    }
#endif

    if (!elf_code)
    {
        pmd_elf_generate_objects(env, &elfEnv);
    }

    /* Close ELF debug file */
    if (env->include_debug && fdebugelf)
    {
        fclose(fdebugelf);
        fdebugelf = NULL;
    }

    /* Clean up */
    pmd_elf_close_file(&elfEnv);
}


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* Opens .out file and returns wether the file has function name info (has_func) and line info (has_line)
*/
LOCAL const char* pmd_elf_open_file(ElfEnvironment *elfEnv, FILE* fout, const char* filename, int* has_func, int* has_line)
{
    const char* ret_code = NULL;

    elfEnv->elf_file = fout;
    if (!elfEnv->elf_file) 
    {
        if (filename && filename[0])
        {
            char* ret_string = pmd_heap_alloc(strlen(filename) + 20);
            sprintf(ret_string, "Can't open out-file '%s'", filename);
            return ret_string;
        }

        return ret_code;
    }

    ret_code = elf_read_header(elfEnv);
    if (!ret_code)
    {
        *has_func = (elfEnv->elf_symtab_index != SHN_UNDEF);
        *has_line = (elfEnv->elf_debugline_index != SHN_UNDEF);
    }

    return ret_code;
}

/* Closes .out file 
*/
LOCAL void pmd_elf_close_file(ElfEnvironment *elfEnv)
{
    elfEnv->elf_file = NULL;
    elfEnv->elf_sym_strings = NULL;
    elfEnv->elf_sec_strings = NULL;

    if (elfEnv->elf_functions)
    {
        free(elfEnv->elf_functions);
        elfEnv->elf_functions = NULL;
    }

    if (elfEnv->elf_variables)
    {
        free(elfEnv->elf_variables);
        elfEnv->elf_variables = NULL;
    }

    if (elfEnv->elf_lines)
        {
        free(elfEnv->elf_lines);
        elfEnv->elf_lines = NULL;
        }

    if (elfEnv->elf_filenames)
        {
        free(elfEnv->elf_filenames);
        elfEnv->elf_filenames = NULL;
        }

    elfEnv->elf_n_functions = 0;
    elfEnv->elf_n_variables = 0;
    elfEnv->elf_n_lines     = 0;
    elfEnv->elf_n_filenames = 0;
}

/* Generates all filename / variable / function name entries from opened .out file
*/
LOCAL const char* pmd_elf_generate_functions(pmd_env* env, ElfEnvironment *elfEnv, FILE* fdebugelf)
{
    if (env->include_debug && fdebugelf)
    {
        fprintf(fdebugelf, "Collecting filenames and function / variable names from .out file\n");
        fprintf(fdebugelf, "===================================================================================================\n");
    }

    /* Read symbols section */
    if (elfEnv->elf_symtab_index != SHN_UNDEF)
    {
        size_t FuncAllocated = 0;
        size_t VariableAllocated = 0;
        size_t FilenamesAllocated = 0;
        Elf32_Word n;
        Elf32_Shdr sec_hdr;
        Elf32_Sym sym;
        elf_read_section_header(elfEnv, elfEnv->elf_symtab_index, &sec_hdr);

        sec_hdr.sh_addr = sec_hdr.sh_addr;

        fseek(elfEnv->elf_file, sec_hdr.sh_offset, SEEK_SET);

        for (n = 0; n < sec_hdr.sh_size / sec_hdr.sh_entsize; ++n)
        {
            elf_read_symbol(elfEnv, &sym);

            if ((ELF32_ST_TYPE(sym.st_info) == STT_FUNC || 
                 ELF32_ST_TYPE(sym.st_info) == STT_OBJECT) && 
                sym.st_size != 0)
            {
                ElfSymbolEntry SymbolEntry;

                SymbolEntry.Addr1         = sym.st_value;
                SymbolEntry.Addr2         = sym.st_value + sym.st_size -1;
                SymbolEntry.Name          = sym.st_name;
                SymbolEntry.HasLines      = TRUE;

                /* filename info for function exists */
                /* NEO: 9. july 20008
                   This code expects that in the .symtab section that a STT_FILE symbol (file) is
                   followed by all the STT_FUNC symbols (functions in the above file).
                   This does not seem true in most cases and the result is that the function in the 
                   PMD file will not point to a filename (using index 0).
                   In those cases where one or more STT_FUNC symbols follows a STT_FILE they will be
                   linked to the STT_FILE symbol in PMD. Question: Is this always correct?
                   Question: Is this according to ELF specification or are we just lucky it works with
                   current compiler and for LOCAL functions?

                   Note:
                   Fixed an error where the if-statement below contained
                       if (sym.st_info == STT_FUNC && ...
                   sym.st_info contains 2 datafields each one the size of 4 bits.
                   This seems an error but to keep same functionality this was changed to
                       if (ELF32_ST_TYPE(sym.st_info) == STT_FUNC && 
                           ELF32_ST_BIND(sym.st_info) == STB_LOCAL && ...
                */
                if (((ELF32_ST_TYPE(sym.st_info) == STT_FUNC)||
                     (ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)) && 
                    ELF32_ST_BIND(sym.st_info) == STB_LOCAL &&
                    elfEnv->elf_n_filenames > 0)
                {
                    SymbolEntry.FilenameIndex = elfEnv->elf_n_filenames;

                    elfEnv->elf_filenames[elfEnv->elf_n_filenames-1].HasFuncs = TRUE;
                }
                /* no filename info for function (CJH: Don't know why...) */
                else
                {
                    SymbolEntry.FilenameIndex = 0;
                }

                /* Store the information in the relevant data structure */
                if (ELF32_ST_TYPE(sym.st_info) == STT_FUNC)
                {
                    /* Store function info */

                    /* Check for sufficient memory in data structure */
                    if (!CheckAndAllocateMemory(elfEnv, &elfEnv->elf_functions, elfEnv->elf_n_functions, &FuncAllocated, sizeof(ElfSymbolEntry)))
                    {
                        return "Out of memory";
                    }

                    /* Store info */
                    elfEnv->elf_functions[elfEnv->elf_n_functions++] = SymbolEntry;
                }
                else if (ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)
                {
                    /* Store variable info */

                    /* Check for sufficient memory in data structure */
                    if (!CheckAndAllocateMemory(elfEnv, &elfEnv->elf_variables, elfEnv->elf_n_variables, &VariableAllocated, sizeof(ElfSymbolEntry)))
                    {
                        return "Out of memory";
                    }

                    /* Store info */
                    elfEnv->elf_variables[elfEnv->elf_n_variables++] = SymbolEntry;
                }

                /* Log the found symbol */
                if (env->include_debug && fdebugelf)
                {
                    fprintf(fdebugelf, "%s Name: %8d   Addr1: 0x%8.8X   Addr2: 0x%8.8X   File: %8d\n", 
                        (ELF32_ST_TYPE(sym.st_info) == STT_OBJECT ? "Variable" : "Function"),
                        SymbolEntry.Name, SymbolEntry.Addr1, SymbolEntry.Addr2, SymbolEntry.FilenameIndex);
                }
            }
            else
                if (ELF32_ST_TYPE(sym.st_info) == STT_FILE)
                {
                    /* only add filename, if it is not already added as last filename */
                    if (elfEnv->elf_n_filenames == 0 || 
                        (elfEnv->elf_n_filenames > 0 && strcmp(elfEnv->elf_filenames[elfEnv->elf_n_filenames-1].Name, &elfEnv->elf_sym_strings[sym.st_name])))
                    {
                        ElfFilenameEntry FilenameEntry;

                        FilenameEntry.Index    = ++elfEnv->elf_n_filenames;
                        FilenameEntry.Name     = &elfEnv->elf_sym_strings[sym.st_name];
                        FilenameEntry.HasFuncs = FALSE;

                        /* Check for sufficient memory in data structure */
                        if (!CheckAndAllocateMemory(elfEnv, &elfEnv->elf_filenames, elfEnv->elf_n_filenames, &FilenamesAllocated, sizeof(ElfFilenameEntry)))
                        {
                            return "Out of memory";
                        }

                        elfEnv->elf_filenames[elfEnv->elf_n_filenames-1] = FilenameEntry;

                        if (env->include_debug && fdebugelf)
                        {
                            fprintf(fdebugelf, "Filename File: %8d   Name:  %s\n", FilenameEntry.Index, FilenameEntry.Name);
                        }
                    }
                }

                /* If entities are larger than the structure, read paddings */
                if (sec_hdr.sh_entsize > sizeof(Elf32_Sym))
                {
                    fseek(elfEnv->elf_file, sec_hdr.sh_entsize - sizeof(Elf32_Sym), SEEK_CUR);
                }
        }
    }

    return NULL;
}

#ifdef AUTOGEN_PMD_LINE_NUMBERS
/* Generates all line number entries from opened .out file
*/
LOCAL const char* pmd_elf_generate_linenumbers(pmd_env* env, ElfEnvironment *elfEnv, FILE* fdebugelf)
{
    if (env->include_debug && fdebugelf)
    {
        fprintf(fdebugelf, "\n");
        fprintf(fdebugelf, "Collecting line numbers from .out file\n");
        fprintf(fdebugelf, "===================================================================================================\n");
    }

    /* read debug section */
    if (elfEnv->elf_debugline_index != SHN_UNDEF)
    {
        size_t NewLineCount = 0;
        size_t LineAllocated=0;
        Elf32_Word LineIx;
        Elf32_Word FuncIx;
        Elf32_Word line_id = 0;
        Elf32_Word SegOffset;
        Dwarf2_LinePrologue lp;
        Elf32_Shdr sec_hdr;

        elf_read_section_header(elfEnv, elfEnv->elf_debugline_index, &sec_hdr);

        if (env->include_debug && fdebugelf)
        {
            fprintf(fdebugelf, "\n");
            fprintf(fdebugelf, "Section header\n");
            fprintf(fdebugelf, "  sh_name:      %8d\n", sec_hdr.sh_name);
            fprintf(fdebugelf, "  sh_type:      %8d\n", sec_hdr.sh_type);
            fprintf(fdebugelf, "  sh_flags:     %8d\n", sec_hdr.sh_flags);
            fprintf(fdebugelf, "  sh_addr:      0x%08X\n", sec_hdr.sh_addr);
            fprintf(fdebugelf, "  sh_offset:    0x%08X\n", sec_hdr.sh_offset);
            fprintf(fdebugelf, "  sh_size:      0x%08X\n", sec_hdr.sh_size);
            fprintf(fdebugelf, "  sh_link:      %8d\n", sec_hdr.sh_link);
            fprintf(fdebugelf, "  sh_info:      %8d\n", sec_hdr.sh_info);
            fprintf(fdebugelf, "  sh_addralign: %8d\n", sec_hdr.sh_addralign);
            fprintf(fdebugelf, "  sh_entsize:   %8d\n", sec_hdr.sh_entsize);
        }

        for (SegOffset=0; SegOffset<sec_hdr.sh_size; SegOffset+=(lp.total_length+4))
        {
            unsigned char reset=1;
            Elf32_Word Offset=0;
            Elf32_Addr address=0;
            Elf32_Word line=0;
            unsigned int pad=0;

retry:
            /* Read Statement Program Prologue */
            fseek(elfEnv->elf_file, sec_hdr.sh_offset+SegOffset, SEEK_SET);

            READ_DWORD(lp.total_length)
            READ_WORD(lp.version)
            READ_DWORD(lp.prologue_length)

            /*
            * Heuristic to detect and skip padding.
            *
            * ARM RVCT  2.x pad .debug_line entries to 4-byte alignment,
            * but 3.x does not.
            */
            if (   (lp.version != 2 && lp.version != 3)
                || (SegOffset > sec_hdr.sh_size)
                || (lp.total_length == 0)
                || (lp.total_length >= sec_hdr.sh_size - SegOffset))
            {
                if (pad < 3)
                {
                    /* Adjust padding to find header. */
                    ++pad;
                    ++SegOffset;

                    if (env->include_debug && fdebugelf)
                    {
                        fprintf(fdebugelf, "Skip pad byte ... ");
                    }

                    goto retry;    /* Read the header again */
                }

                /* Got out of sync with the DWARF format */
                util_error_line(NULL, 0, AUTOGEN_ERROR_WARNING, AUTOGEN_ENV_ALL, 0,
                    "Line number problem in .out file in section .debug_line, section offset %lx (%lx in file)\n", 
                    SegOffset, sec_hdr.sh_offset+SegOffset);
                break;
            }

            if (env->include_debug && fdebugelf && pad > 0)
            {
                /* Padding bytes have been detected and logs written out. Terminate with CR */
                fprintf(fdebugelf, "\n");
            }

            fread(&lp.minimum_instruction_length, 1, 5, elfEnv->elf_file);
            memset(&lp.standard_opcode_lengths[0], 0, 256);
            fread(&lp.standard_opcode_lengths[1], 1, lp.opcode_base-2, elfEnv->elf_file);

            if (env->include_debug && fdebugelf)
            {
                fprintf(fdebugelf, "\n");
                fprintf(fdebugelf, "Statement Program Prologue (File offset / Section offset = 0x%08X / 0x%08X)\n", sec_hdr.sh_offset+SegOffset, SegOffset);
                fprintf(fdebugelf, "---------------------------------------------------------------------------------------------------\n");
                fprintf(fdebugelf, "total_length  version  prologue_length  min_inst_length  is_stmt  line_base  line_range  opcode_base\n");
                fprintf(fdebugelf, "  0x%08X       %2d       0x%08X               %2d       %2d         %2d          %2d          %3d\n", 
                    lp.total_length, lp.version, lp.prologue_length, lp.minimum_instruction_length, 
                    lp.default_is_stmt, lp.line_base, lp.line_range, lp.opcode_base);
            }

            Offset=lp.prologue_length+10;
            fseek(elfEnv->elf_file, sec_hdr.sh_offset+SegOffset+Offset, SEEK_SET);

            if (env->include_debug && fdebugelf)
            {
                fprintf(fdebugelf, "\n");
                fprintf(fdebugelf, "Line numbers\n");
                fprintf(fdebugelf, "---------------------------------------------------------------------------------------------------\n");
                fprintf(fdebugelf, " Line Id      Address   Line number\n");
            }

            while (Offset<(lp.total_length+4))
            {
                unsigned char opcode;
                unsigned char check=0;
                Elf32_Half increment;

                if (reset)
                {
                    address=0;
                    line=1;
                    reset=0;
                }
                fread(&opcode, 1, 1, elfEnv->elf_file);
                Offset+=1;
                if (opcode<lp.opcode_base)
                {
                    switch (opcode)
                    {
                        case 0:
                        {
                            unsigned char length;
                            fread(&length, 1, 1, elfEnv->elf_file);
                            Offset+=1;
                            fread(&opcode, 1, 1, elfEnv->elf_file);
                            Offset+=1;
                            switch(opcode)
                            {
                                case DW_LNE_end_Sequence:
                                    assert(length==1);
                                    check=1;
                                    reset=1;
                                    break;
                                case DW_LNE_set_address:
                                    assert(length==5);
                                    READ_DWORD(address)
                                    Offset+=4;
                                    break;
                                case DW_LNE_define_file:
                                    fseek(elfEnv->elf_file, length-1, SEEK_SET);
                                    Offset+=length-1;
                                    break;
                                default:
                                    fseek(elfEnv->elf_file, length-1, SEEK_SET);
                                    Offset+=length-1;
                                    break;
                            }
                        }
                            break;
                        case DW_LNS_copy:
                            assert(lp.standard_opcode_lengths[opcode]==0);
                            check=1;
                            break;
                        case DW_LNS_advance_pc:
                            assert(lp.standard_opcode_lengths[opcode]==1);
                            address+=lp.minimum_instruction_length*COFFinfo_read_ULEB128(elfEnv->elf_file, &Offset);
                            break;
                        case DW_LNS_advance_line:
                            assert(lp.standard_opcode_lengths[opcode]==1);
                            line+=COFFinfo_read_SLEB128(elfEnv->elf_file, &Offset);
                            break;
                        case DW_LNS_set_file:
                            assert(lp.standard_opcode_lengths[opcode]==1);
                            COFFinfo_read_ULEB128(elfEnv->elf_file, &Offset);
                            break;
                        case DW_LNS_const_add_pc:
                            assert(lp.standard_opcode_lengths[opcode]==0);
                            address += lp.minimum_instruction_length*((255-lp.opcode_base)/lp.line_range);
                            break;
                        case DW_LNS_fixed_advance_pc:
                            assert(lp.standard_opcode_lengths[opcode]==0);
                            READ_WORD(increment)
                            Offset+=2;
                            address += increment;
                            break;
                        default:
                        {
                            int ix;
                            for (ix=0;ix<lp.standard_opcode_lengths[opcode];++ix)
                                (void)COFFinfo_read_ULEB128(elfEnv->elf_file, &Offset);
                            break;
                        }
                    }

                }
                else
                {
                    address += lp.minimum_instruction_length*((opcode-lp.opcode_base)/lp.line_range);
                    line += lp.line_base + ((opcode-lp.opcode_base)%lp.line_range);
                    check=1;
                }
                if (check)
                {
                    ElfLineEntry LineEntry;
                    LineEntry.Addr=address;
                    LineEntry.LineNumber=line;
                    LineEntry.ID = ++line_id;

                    /* Check and allocate more memory if necessary */
                    if (!CheckAndAllocateMemory(elfEnv, &elfEnv->elf_lines, elfEnv->elf_n_lines, &LineAllocated, sizeof(ElfLineEntry)))
                    {
                        return "Out of memory";
                    }

                    elfEnv->elf_lines[elfEnv->elf_n_lines++] = LineEntry;

                    if (env->include_debug && fdebugelf)
                    {
                        fprintf(fdebugelf, "%8d   0x%08X      %8d\n", LineEntry.ID, LineEntry.Addr,LineEntry.LineNumber);
                    }
                }
            }
        }

        if (env->include_debug && fdebugelf)
        {
            fprintf(fdebugelf, "\n");
            fprintf(fdebugelf, "Sorting line numbers and functions...\n");
        }
        qsort(elfEnv->elf_lines, elfEnv->elf_n_lines, sizeof(ElfLineEntry), ElfLineEntriesByAddr);
        qsort(elfEnv->elf_functions, elfEnv->elf_n_functions, sizeof(ElfSymbolEntry), ElfFunctionEntriesByAddr);

        /* Remove unneeded line numbers */
        {
        Elf32_Word PrevLastSourceLine = 0;
        const char* last_filename = NULL;

        if (env->include_debug && fdebugelf)
        {
            fprintf(fdebugelf, "Removing unneeded line number entries...\n\n");
        }

        LineIx = 0;
        NewLineCount = 0;

        for (FuncIx = 0; FuncIx < elfEnv->elf_n_functions && LineIx < elfEnv->elf_n_lines; ++FuncIx)
        {
            Elf32_Word last_line = 0;
            Elf32_Word TravIx;
            Elf32_Word LastSourceLine = 0;
            Elf32_Word LastSourceLineIx = 0;
            int has_lines = FALSE;

            if (env->include_debug && fdebugelf)
            {
                if (elfEnv->elf_functions[FuncIx].FilenameIndex > 0 && GET_FUNC_FILENAME(FuncIx) != last_filename)
                {
                    last_filename = GET_FUNC_FILENAME(FuncIx);

                    fprintf(fdebugelf, "---------------------------\n");
                    fprintf(fdebugelf, "File:%s\n", last_filename);
                    fprintf(fdebugelf, "---------------------------\n");
                }

                fprintf(fdebugelf, "Function: %s (addr1: 0x%08X, addr2: 0x%08X)\n", &elfEnv->elf_sym_strings[elfEnv->elf_functions[FuncIx].Name], elfEnv->elf_functions[FuncIx].Addr1, elfEnv->elf_functions[FuncIx].Addr2);
            }

            /* Skip all lines without a function */
            while (LineIx < elfEnv->elf_n_lines && elfEnv->elf_lines[LineIx].Addr < elfEnv->elf_functions[FuncIx].Addr1)
            {
                ++LineIx;

                if (env->include_debug && fdebugelf)
                {
                    ++elfEnv->ElfDebugInfo.elf_line_outside_func;
                }
            }

            TravIx = LineIx;
            /* Find last source line in function */
            while (TravIx < elfEnv->elf_n_lines && elfEnv->elf_lines[TravIx].Addr <= elfEnv->elf_functions[FuncIx].Addr2)
            {
                LastSourceLine   = elfEnv->elf_lines[TravIx].LineNumber;
                LastSourceLineIx = TravIx++;
            }

            /* Skip all lines not increasing through the function address space */
            while (LineIx < elfEnv->elf_n_lines && elfEnv->elf_lines[LineIx].Addr <= elfEnv->elf_functions[FuncIx].Addr2)
            {
                Elf32_Word new_line = elfEnv->elf_lines[LineIx].LineNumber;

                /* If no lines are saved for function yet, and this line is equal to the last line of the last function,
                   the line number is wrong
                */
                if (new_line == PrevLastSourceLine && !has_lines)
                {
                    if (env->include_debug && fdebugelf)
                    {
                        fprintf(fdebugelf, " 0x%08X -> %d (skipping - first = last)\n", elfEnv->elf_lines[LineIx].Addr, new_line);
                        ++elfEnv->ElfDebugInfo.elf_line_first_last;
                    }
                }
                /* If address is equal to next address, ignore this... */
                else
                if (LineIx < elfEnv->elf_n_lines-1 && elfEnv->elf_lines[LineIx].Addr == elfEnv->elf_lines[LineIx+1].Addr)
                {
                    if (env->include_debug && fdebugelf)
                    {
                        fprintf(fdebugelf, " 0x%08X -> %d (skipping - wrong)\n", elfEnv->elf_lines[LineIx].Addr, new_line);
                        ++elfEnv->ElfDebugInfo.elf_line_dupl_addr;
                    }
                }
                else
                {
                    elfEnv->elf_lines[NewLineCount++] = elfEnv->elf_lines[LineIx];

                    if (env->include_debug && fdebugelf)
                    {
                        fprintf(fdebugelf, " 0x%08X -> %d\n", elfEnv->elf_lines[LineIx].Addr, new_line);
                    }

                    last_line = (last_line > new_line) ? last_line : new_line;
                    has_lines = TRUE;
                }

                ++LineIx;
            }

            if (env->include_debug)
            {
                if (!has_lines)
                {
                    elfEnv->ElfDebugInfo.elf_func_empty++;
                }
            }

            elfEnv->elf_functions[FuncIx].HasLines = (has_lines ? TRUE : FALSE);

            PrevLastSourceLine = LastSourceLine;
        }

        if (env->include_debug && fdebugelf)
        {
            fprintf(fdebugelf, "\nLines before removal: %d\n",        elfEnv->elf_n_lines);
            fprintf(fdebugelf, "Lines after  removal: %d\n",          NewLineCount);
            fprintf(fdebugelf, "- Lines outside func: %d\n",          elfEnv->ElfDebugInfo.elf_line_outside_func);
            fprintf(fdebugelf, "- Lines (duplicate addresses): %d\n", elfEnv->ElfDebugInfo.elf_line_dupl_addr);
            fprintf(fdebugelf, "- Lines (last reference): %d\n",      elfEnv->ElfDebugInfo.elf_line_last_ref);
            fprintf(fdebugelf, "- Lines (last is first): %d\n",       elfEnv->ElfDebugInfo.elf_line_first_last);
            fprintf(fdebugelf, "- Lines (first line): %d\n",          elfEnv->ElfDebugInfo.elf_line_first);
            fprintf(fdebugelf, "- Lines (last line): %d\n",           elfEnv->ElfDebugInfo.elf_line_last);
            fprintf(fdebugelf, "- Lines (general skip): %d\n",        elfEnv->ElfDebugInfo.elf_line_skip);
            fprintf(fdebugelf, "Functions: %d\n",                     elfEnv->elf_n_functions);
            fprintf(fdebugelf, "- Empty: %d\n",                       elfEnv->ElfDebugInfo.elf_func_empty);
        }

        elfEnv->elf_n_lines = NewLineCount;
        }
    }

    return NULL;
}
#endif /* AUTOGEN_PMD_LINE_NUMBERS */

/* Generates PMD info objects from the genated filename/function
*/
LOCAL void pmd_elf_generate_objects(pmd_env* env, ElfEnvironment *elfEnv)
{
    size_t n;
    FILE* felf = NULL;

    if (env->include_debug)
    {
        char debugFile[512];

        sprintf(debugFile, "pmd_debug_elf_%s.txt", elfEnv->basefilename);
        felf = fopen(debugFile, "wt");
    }

    if (env->include_debug && felf)
    {
        fprintf(felf, "PMD_INFO_TYPE_MCU_DEBUG_FILENAMES\n");
        fprintf(felf, "---------------------------------------------------------------------------------------------------\n");
        fprintf(felf, " Index  Filename\n");
    }

    /* Generate DLL filename object */
    if (elfEnv->elf_hdr.e_type == ET_DYN)
    {
        char *dll_filename = pmd_heap_strdup(elfEnv->basefilename);

        /* Cut off .out ending on the basefilename if present */
        char *dotptr = strrchr(dll_filename, '.');
        if (dotptr)
        {
            if (!strcmp(dotptr, ".out"))
            {
                /* Basefilename ends on a .out. Remove it */
                *dotptr = '\0'; 
            }
        }

        pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_DLL_FILENAMES, 
                     dll_filename, ++s_dll_filename_index, 
                     0, 0, 0, 0, 0);
    }

    /* Generate filename objects */
    for (n = 0; n < elfEnv->elf_n_filenames; n++)
    {
        const char* filename;

        /* remove path from filename */
        filename = util_get_filename(elfEnv->elf_filenames[n].Name);
        if (filename == NULL)
        {
            filename = elfEnv->elf_filenames[n].Name;
        }

        if (env->include_debug && felf)
        {
            fprintf(felf, "%d %4u   %s\n", elfEnv->elf_filenames[n].HasFuncs, elfEnv->elf_filenames[n].Index, filename);
        }

        if (elfEnv->elf_filenames[n].HasFuncs)
        {
            if (elfEnv->elf_hdr.e_type == ET_DYN)
            {
                pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_FILENAMES_SHARED, 
                             filename, elfEnv->elf_filenames[n].Index, 
                             1, s_dll_filename_index, 0, 0, 0);
            }
            else
            {
                pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_FILENAMES, 
                             filename, elfEnv->elf_filenames[n].Index, 
                             0, 0, 0, 0, 0);
            }
        }
    }

    /* Generate function objects */
    if (env->include_debug && felf)
    {
        fprintf(felf, "\n");
        fprintf(felf, "PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS\n");
        fprintf(felf, "---------------------------------------------------------------------------------------------------\n");
        fprintf(felf, " Address                Function                                       Filename\n");
    }

    for (n = 0; n < elfEnv->elf_n_functions; n++)
    {
        if (elfEnv->elf_functions[n].HasLines)
        {
            if (env->include_debug && felf)
            {
                if (elfEnv->elf_functions[n].FilenameIndex == 0)
                {
                    fprintf(felf, " 0x%8.8X-0x%8.8X  %-45s  %4u - None\n", elfEnv->elf_functions[n].Addr1, elfEnv->elf_functions[n].Addr2, &elfEnv->elf_sym_strings[elfEnv->elf_functions[n].Name], elfEnv->elf_functions[n].FilenameIndex);
                }
                else
                {
                    fprintf(felf, " 0x%8.8X-0x%8.8X  %-45s  %4u - %s\n", elfEnv->elf_functions[n].Addr1, elfEnv->elf_functions[n].Addr2, &elfEnv->elf_sym_strings[elfEnv->elf_functions[n].Name], elfEnv->elf_functions[n].FilenameIndex, GET_FUNC_FILENAME(n));
                }
            }

            if (elfEnv->elf_hdr.e_type == ET_DYN)
            {
                pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS_SHARED, 
                            &elfEnv->elf_sym_strings[elfEnv->elf_functions[n].Name], elfEnv->elf_functions[n].Addr1, 
                            3, elfEnv->elf_functions[n].Addr2, elfEnv->elf_functions[n].FilenameIndex, s_dll_filename_index, 0);
            }
            else
            {
                pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS, 
                            &elfEnv->elf_sym_strings[elfEnv->elf_functions[n].Name], elfEnv->elf_functions[n].Addr1, 
                            2, elfEnv->elf_functions[n].Addr2, elfEnv->elf_functions[n].FilenameIndex, 0, 0);
            }
        }
    }

    /* Generate variable objects */
    if (env->include_debug && felf)
    {
        fprintf(felf, "\n");
        fprintf(felf, "PMD_INFO_TYPE_MCU_DEBUG_VARIABLES\n");
        fprintf(felf, "---------------------------------------------------------------------------------------------------\n");
        fprintf(felf, " Address                Variable                                       Filename\n");
    }

    for (n = 0; n < elfEnv->elf_n_variables; n++)
    {
        if (env->include_debug && felf)
        {
            if (elfEnv->elf_variables[n].FilenameIndex == 0)
            {
                fprintf(felf, " 0x%8.8X-0x%8.8X  %-45s  %4u - None\n", 
                    elfEnv->elf_variables[n].Addr1, elfEnv->elf_variables[n].Addr2, 
                    &elfEnv->elf_sym_strings[elfEnv->elf_variables[n].Name], elfEnv->elf_variables[n].FilenameIndex);
            }
            else
            {
                fprintf(felf, " 0x%8.8X-0x%8.8X  %-45s  %4u - %s\n", 
                    elfEnv->elf_variables[n].Addr1, elfEnv->elf_variables[n].Addr2, 
                    &elfEnv->elf_sym_strings[elfEnv->elf_variables[n].Name], 
                    elfEnv->elf_variables[n].FilenameIndex, GET_VAR_FILENAME(n));
            }
        }

        if (elfEnv->elf_hdr.e_type == ET_DYN)
        {
            pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED, 
                &elfEnv->elf_sym_strings[elfEnv->elf_variables[n].Name], elfEnv->elf_variables[n].Addr1, 
                3, elfEnv->elf_variables[n].Addr2, elfEnv->elf_variables[n].FilenameIndex, s_dll_filename_index, 0);
        }
        else
        {
            pmd_info_add(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_VARIABLES, 
                &elfEnv->elf_sym_strings[elfEnv->elf_variables[n].Name], elfEnv->elf_variables[n].Addr1, 
                2, elfEnv->elf_variables[n].Addr2, elfEnv->elf_variables[n].FilenameIndex, 0, 0);
        }
    }

#ifdef AUTOGEN_PMD_LINE_NUMBERS
    /* Generate line objects */
    if (env->include_debug && felf)
    {
        fprintf(felf, "\n");
        fprintf(felf, "PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS\n");
        fprintf(felf, "---------------------------------------------------------------------------------------------------\n");
        fprintf(felf, " Address               Linenumber\n");
    }

    for (n= 0; n < elfEnv->elf_n_lines; n++)
    {
        if (elfEnv->elf_hdr.e_type == ET_DYN)
        {
            pmd_info_add_uncond(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS_SHARED, 
                                NULL, elfEnv->elf_lines[n].Addr, 
                                2, elfEnv->elf_lines[n].LineNumber, s_dll_filename_index, 0, 0);
        }
        else
        {
            pmd_info_add_uncond(env, env->device_id, PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS, 
                                NULL, elfEnv->elf_lines[n].Addr, 
                                1, elfEnv->elf_lines[n].LineNumber, 0, 0, 0);
        }

        if (env->include_debug && felf)
        {
            fprintf(felf, " 0x%8.8X               %d\n", elfEnv->elf_lines[n].Addr, elfEnv->elf_lines[n].LineNumber);
        }
    }
#endif /* AUTOGEN_PMD_LINE_NUMBERS */

    if (env->include_debug && felf)
    {
        fclose(felf);
    }
}

LOCAL const char* elf_read_header(ElfEnvironment *elfEnv)
{
    const char* ret_code = NULL;
    unsigned int lvalue = 0;
    unsigned char bvalue = 0;
    int i;

    READ_DWORD(lvalue);
    if (lvalue == 0x7f454c46)
    {
        elfEnv->elf_dataorder = ELFDATA2MSB;
    }
    else
        if (lvalue == 0x464c457f)
        {
            elfEnv->elf_dataorder = ELFDATA2LSB;
        }
        else
        {
            pmd_elf_close_file(elfEnv);
            return "Bad ELF header";
        }

        READ_BYTE(elfEnv->elf_hdr.e_id_class);
        if (elfEnv->elf_hdr.e_id_class != ELFCLASS32)
        {
            pmd_elf_close_file(elfEnv);
            return "Unsupported Class of ELF-file";
        }

        READ_BYTE(elfEnv->elf_hdr.e_id_data);
        switch (elfEnv->elf_hdr.e_id_data)
        {
        case ELFDATA2LSB:
            {
                elfEnv->elf_dataorder = ELFDATA2LSB;
                break;
            }
        case ELFDATA2MSB:
            {
                elfEnv->elf_dataorder = ELFDATA2MSB;
                break;
            }
        case ELFDATANONE:
        default:
            {
                pmd_elf_close_file(elfEnv);
                return "Unsupported Data ordering of ELF-file";
                break;
            }
        }
        READ_BYTE(elfEnv->elf_hdr.e_id_version);
        READ_BYTE(elfEnv->elf_hdr.e_id_osabi);
        READ_BYTE(elfEnv->elf_hdr.e_id_abiversion);

        for (i = 0; i < 7; i++)
        {
            READ_BYTE(bvalue);
        }

        READ_WORD(elfEnv->elf_hdr.e_type);
        if (elfEnv->elf_hdr.e_type != ET_EXEC && elfEnv->elf_hdr.e_type != ET_DYN)
        {
            pmd_elf_close_file(elfEnv);
            return "Unsupported file type";
        }

        READ_WORD(elfEnv->elf_hdr.e_machine);

        READ_DWORD(elfEnv->elf_hdr.e_version);
        if (elfEnv->elf_hdr.e_version == EV_NONE)
        {
            pmd_elf_close_file(elfEnv);
            return "Unsupported file version";
        }

        READ_DWORD(elfEnv->elf_hdr.e_entry);
        READ_DWORD(elfEnv->elf_hdr.e_phoff);
        READ_DWORD(elfEnv->elf_hdr.e_shoff);
        READ_DWORD(elfEnv->elf_hdr.e_flags);

        READ_WORD(elfEnv->elf_hdr.e_ehsize);
        READ_WORD(elfEnv->elf_hdr.e_phentsize);
        READ_WORD(elfEnv->elf_hdr.e_phnum);
        READ_WORD(elfEnv->elf_hdr.e_shentsize);
        READ_WORD(elfEnv->elf_hdr.e_shnum);
        READ_WORD(elfEnv->elf_hdr.e_shstrndx);

        /* Read string table */
        if (elfEnv->elf_hdr.e_shstrndx != SHN_UNDEF)
        {
            Elf32_Half ix;
            Elf32_Shdr sec_str_table;
            elf_read_section_header(elfEnv, elfEnv->elf_hdr.e_shstrndx, &sec_str_table);

            if (sec_str_table.sh_type == SHT_STRTAB)
            {
                elfEnv->elf_sec_strings = (char*)elf_read_section_data(elfEnv->elf_file, &sec_str_table);

                /* Find section with string table and copy to memory */
                for (ix = 0; ix < elfEnv->elf_hdr.e_shnum; ++ix)
                {
                    Elf32_Shdr sec_hdr;
                    elf_read_section_header(elfEnv, ix, &sec_hdr);

                    if (sec_hdr.sh_type == SHT_STRTAB && strcmp(&elfEnv->elf_sec_strings[sec_hdr.sh_name], ".strtab") == 0)
                    {
                        elfEnv->elf_sym_strings = (char*)elf_read_section_data(elfEnv->elf_file, &sec_hdr);
                    }
                    else
                        if (sec_hdr.sh_type == SHT_SYMTAB)
                        {
                            elfEnv->elf_symtab_index = ix;
                        }
                else
                if (sec_hdr.sh_type == SHT_PROGBITS && strcmp(&elfEnv->elf_sec_strings[sec_hdr.sh_name], ".debug_line") == 0)
                    {
                    elfEnv->elf_debugline_index = ix;
                    }
                }
            }
        }

        /* Abort if no symbol strings are read */
        if (!elfEnv->elf_sym_strings)
        {
            ret_code = "File does not contain a string table";
        }

        if (ret_code)
        {
            pmd_elf_close_file(elfEnv);
        }

        return ret_code;
}

LOCAL int elf_read_byte(FILE* elf_file, unsigned char* bvalue)
{
    size_t nread = fread(bvalue, 1, 1, elf_file);

    return nread == 1;
}

LOCAL int elf_read_bytes(FILE* elf_file, unsigned char* buffer, unsigned int nbytes)
{
    size_t nread = fread(buffer, nbytes, 1, elf_file);

    return nread == 1;
}

LOCAL int elf_read_word(FILE* elf_file, unsigned char elf_dataorder, unsigned short* svalue)
{
    size_t nread = fread(svalue, 2, 1, elf_file);
    *svalue = elf_fix_word(elf_dataorder, *svalue);

    return nread == 1;
}

LOCAL int elf_read_dword(FILE* elf_file, unsigned char elf_dataorder, unsigned int* lvalue)
{
    size_t nread = fread(lvalue, 4, 1, elf_file);
    *lvalue = elf_fix_dword(elf_dataorder, *lvalue);

    return nread == 1;
}

LOCAL unsigned short elf_fix_word(unsigned char elf_dataorder, unsigned short w)
{
    if (elf_dataorder == ELFDATA2MSB)
    {
        w = (unsigned short)(((w & 0x00FF) << 8) | ((w & 0xFF00) >> 8));
    }
    return w;
}

LOCAL unsigned int elf_fix_dword(unsigned char elf_dataorder, unsigned int l)
{
    if (elf_dataorder == ELFDATA2MSB)
    {
        l = ((l & 0x000000FF) << 24) | ((l & 0x0000FF00) <<  8) |
            ((l & 0x00FF0000) >>  8) | ((l & 0xFF000000) >> 24);
    }
    return l;
}

LOCAL void* elf_read_section_data(FILE *elf_file, Elf32_Shdr* pshdr)
{
    unsigned char* buffer = (unsigned char *)pmd_heap_alloc(pshdr->sh_size);

    if (buffer)
    {
        fseek(elf_file, pshdr->sh_offset, SEEK_SET);
        fread(buffer, pshdr->sh_size, 1, elf_file);
    }

    return buffer;
}

/*  This function reads and fixes a SectionHeader from an ELF file
*/
LOCAL const char* elf_read_section_header(ElfEnvironment *elfEnv, unsigned int index, Elf32_Shdr* pshdr)
{
    fseek(elfEnv->elf_file, elfEnv->elf_hdr.e_shoff + elfEnv->elf_hdr.e_shentsize*index, SEEK_SET);

    READ_DWORD(pshdr->sh_name);
    READ_DWORD(pshdr->sh_type);
    READ_DWORD(pshdr->sh_flags);
    READ_DWORD(pshdr->sh_addr);
    READ_DWORD(pshdr->sh_offset);
    READ_DWORD(pshdr->sh_size);
    READ_DWORD(pshdr->sh_link);
    READ_DWORD(pshdr->sh_info);
    READ_DWORD(pshdr->sh_addralign);
    READ_DWORD(pshdr->sh_entsize);

    return NULL;
}

LOCAL const char* elf_read_symbol(ElfEnvironment *elfEnv, Elf32_Sym* psym)
{
    READ_DWORD(psym->st_name);
    READ_DWORD(psym->st_value);
    READ_DWORD(psym->st_size);
    READ_BYTE(psym->st_info);
    READ_BYTE(psym->st_other);
    READ_WORD(psym->st_shndx);

    return NULL;
}

LOCAL unsigned int COFFinfo_read_ULEB128(FILE *elf_file, Elf32_Word* offset)
{
    unsigned int result = 0;
    unsigned int shift = 0;
    unsigned char byte = 0x80;
    while ((byte & 0x80) == 0x80)
    {
        fread(&byte, 1, 1, elf_file);
        ++(*offset);
        result |= (byte & 0x7F) << shift;
        shift += 7;
    }
    return result;
}

LOCAL signed int COFFinfo_read_SLEB128(FILE *elf_file, unsigned int* offset)
{
    signed int result = 0;
    unsigned int shift = 0;
    unsigned char byte = 0x80;
    while ((byte & 0x80) == 0x80)
    {
        fread(&byte, 1, 1, elf_file);
        ++(*offset);
        result |= (byte & 0x7F) << shift;
        shift += 7;
    }
    if (shift < 32 && ((byte & 0x40) == 0x40))
    {
        result |= - (1 << shift);
    }
    return result;
}

/*  Functional Description

    This function is a qsort compare routine to order ElfLineEntry by address

    Return Values:  int = -1 Elem1 should be first
    1 Elem2 should be first
    0 The two elements has same address
*/
LOCAL int ElfFunctionEntriesByAddr(const void* Elem1, const void* Elem2)
{
    if (((ElfSymbolEntry*)Elem1)->Addr1 < ((ElfSymbolEntry*)Elem2)->Addr1) return -1;
    if (((ElfSymbolEntry*)Elem1)->Addr1 > ((ElfSymbolEntry*)Elem2)->Addr1) return  1;

    return 0;
}

#ifdef AUTOGEN_PMD_LINE_NUMBERS
/*  Functional Description
    This function is a qsort compare routine to order ElfLineEntry by address

    Return Values:  int = -1 Elem1 should be first
                           1 Elem2 should be first
                           0 The two elements has same address
*/
LOCAL int ElfLineEntriesByAddr(const void* Elem1, const void* Elem2)
    {
    if (((ElfLineEntry*)Elem1)->Addr < ((ElfLineEntry*)Elem2)->Addr) return -1;
    if (((ElfLineEntry*)Elem1)->Addr > ((ElfLineEntry*)Elem2)->Addr) return  1;

    if (((ElfLineEntry*)Elem1)->ID < ((ElfLineEntry*)Elem2)->ID) return  1;
    if (((ElfLineEntry*)Elem1)->ID > ((ElfLineEntry*)Elem2)->ID) return -1;

    return 0;
    }
#endif /* AUTOGEN_PMD_LINE_NUMBERS */

/* Check and allocate more memory if necessary to symbol storage */
LOCAL int CheckAndAllocateMemory(ElfEnvironment *elfEnv, void **data, size_t elements, size_t *max_elements, size_t element_size)
{
    if (elements >= *max_elements)
    {
        *max_elements = (*max_elements > 0) ? 2*(*max_elements) : 100;
        *data = realloc(*data, *max_elements * element_size);
        if (!*data)
        {
            pmd_elf_close_file(elfEnv);
            return FALSE;
        }
    }
    return TRUE;
}

#endif /* #else (PMD_FILE_FORMAT >= 610) */

#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

/* End of file output_pmd_elf.c */

