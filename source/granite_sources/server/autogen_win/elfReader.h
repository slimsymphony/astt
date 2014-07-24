/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                elfReader.h
                --------------
                SW Include






Project:          autogen

%name:             elfReader.h %
%version:          2 %
%instance:         co1tss_1 %
%derived_by:       nosterga %
%date_modified:    Thu Feb 17 16:13:58 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains the the declarations for various functions to read and parse the ELF format
    used by .out file. The functions are focused on extracting debug information.
    Elf format described in

            Tool Interface Standard (TIS)
            Executable and Linking Format (ELF)
            Specification
            Version 1.2
*/

#ifndef ELFREADER_H
#define ELFREADER_H

#include "stdio.h"
#include "list.h"
#include "elf.h"

/* 
  Structure containing various information carried around among the various 
  ELF parsing functions 
*/
typedef struct {
    /* Actual .out file being read from */
    FILE *elf_file;

    /* File to dump debug information */
    /* If variable != NULL then debug enabled and FILE pointer is valid */
    FILE *debug;

    /* ELF header */
    Elf32_Ehdr elf_hdr;

    /* Endianess of ELF file */
    unsigned char elf_dataorder;

    /* Section header table */
    Elf32_Shdr *shtable;

    /* Section name string table */
    /* Strings used by the section header table */
    char *elf_sec_name_str_table;

    /* Symbol string table */
    /* Strings used by the symbol table */
    char *elf_symtab_str_table;

    /* Abbreviation tables read from section .debug_abbrev */
    list_header *dwarf_abbreviation_tables;
} ElfEnvironment;

/*
    Functions to read bytes, words and double words
*/
#define READ_BYTE(bvalue) \
    if (!elf_read_byte(elfEnv->elf_file, &bvalue)) return "XXX";

#define READ_BYTES(buffer, nbytes) \
    if (!elf_read_bytes(elfEnv->elf_file, buffer, nbytes)) \
    { \
        return "Unexpected end of file"; \
    }

#define READ_WORD(svalue) \
    if (!elf_read_word(elfEnv->elf_file, elfEnv->elf_dataorder, &svalue)) \
    { \
        return "Unexpected end of file"; \
    }

#define READ_DWORD(lvalue) \
    if (!elf_read_dword(elfEnv->elf_file, elfEnv->elf_dataorder, &lvalue)) \
    { \
        return "Unexpected end of file"; \
    }

/* Functions */
int                elf_read_byte(FILE* elf_file, unsigned char* bvalue);
int                elf_read_bytes(FILE* elf_file, unsigned char* buffer, unsigned int nbytes);
int                elf_read_word(FILE* elf_file, unsigned char elf_dataorder, unsigned short* svalue);
int                elf_read_dword(FILE* elf_file, unsigned char elf_dataorder, unsigned int* lvalue);
unsigned short     elf_fix_word(unsigned char elf_dataorder, unsigned short w);
unsigned int       elf_fix_dword(unsigned char elf_dataorder, unsigned int l);
unsigned long long elf_fix_ddword(unsigned char elf_dataorder, unsigned long long l);

void        elf_init_ElfEnvironment(ElfEnvironment *elfEnv);
void        elf_free_ElfEnvironment(ElfEnvironment *elfEnv);

const char *elf_read_ElfHeader(ElfEnvironment *elfEnv);
void        elf_dump_ElfHeader(ElfEnvironment *elfEnv);
const char *elf_read_SectionHeaderTable(ElfEnvironment *elfEnv, Elf32_Shdr **shtable);
void        elf_dump_SectionHeaderTable(ElfEnvironment *elfEnv);
const char *elf_read_SectionHeader(ElfEnvironment *elfEnv, Elf32_Shdr *pshdr);
void        elf_dump_SectionHeader(ElfEnvironment *elfEnv, Elf32_Shdr *sec_hdr);
void       *elf_read_section_data(ElfEnvironment *elfEnv, Elf32_Shdr *shdr);
void        elf_dump_section_data(ElfEnvironment *elfEnv, const char *header, size_t n, void *data);
const char *elf_read_SectionHeaderStringTable(ElfEnvironment *elfEnv);
const char *elf_read_SymbolStringTable(ElfEnvironment *elfEnv);
const char *elf_read_symtab(ElfEnvironment *elfEnv, const char *(*user_func)(ElfEnvironment *, Elf32_Sym *, void *), void *user_func_data);
const char *elf_parse_symtab(ElfEnvironment *elfEnv, size_t n, void *data, size_t symtab_entry_size, const char *(*user_func)(ElfEnvironment *, Elf32_Sym *, void *), void *user_func_data);
void        elf_parse_symtab_entry(ElfEnvironment *elfEnv, Elf32_Sym *symtab_entry, unsigned char **offset);
void        elf_dump_symbol_table_entry(ElfEnvironment *elfEnv, Elf32_Sym *symtab_entry);

#endif /* ELFREADER_H */

