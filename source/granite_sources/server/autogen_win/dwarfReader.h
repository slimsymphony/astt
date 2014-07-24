/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                dwarfReader.h
                --------------
                SW Include






Project:          autogen

%name:             dwarfReader.h %
%version:          1 %
%instance:         co1tss_1 %
%derived_by:       nosterga %
%date_modified:    Tue Feb 15 18:07:41 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains the the declarations for various functions to read and parse the DWARF format
    (a way of storing debug information in a number of ELF sections) used by .out file. 
    The functions are focused on extracting debug information.
    Dwarf format described in

            DWARF Debugging Information Format 
            Version 3

            http://dwarfstd.org/
*/

#ifndef DWARFREADER_H
#define DWARFREADER_H

#include "elfReader.h"
#include "dwarf.h"

/* Dwarf attribute specification */
/* Attribute specifications are stored in an abbreviation: See Dwarf3_abbreviation */
typedef struct t_Dwarf3_attribute_specification
{
    /* DW_AT_<x> */
    unsigned int name;

    /* DW_FORM_<x> */
    unsigned int form;

    /* Used to temporarily store collected data from DIEs */
    /* The data will be the data corresponding to the DW_AT_<x> attribute */
    union {
        unsigned int uint;
        unsigned long long ull;
        const char *cptr;
        signed int sint;
        void *vptr;
    } data;

    /* Some DW_FORM_<x> represents a block of data. This will store the length of such a block read from a DIE */
    unsigned int size_of_blockdata;

} Dwarf3_attribute_specification; 

/* Dwarf abbreviation */
/* Abbreviations are stored in an abbreviation table: See Dwarf3_abbreviation_table */
typedef struct t_Dwarf3_abbreviation
{
    /* Abbreviation code identifying this abbreviation */
    unsigned int abbreviation_code;

    /* DW_TAG_<x> */
    unsigned int tag;

    /* Does the DIE contain children */
    /* DW_CHILDREN_no / DW_CHILDREN_yes */
    unsigned short children;

    /* List of attribute specifications */
    list_header *attribute_specification_list;
} Dwarf3_abbreviation;

/* Dwarf abbreviation table */
/* Abbreviation tables are stored in the .debug_abbrev elf section */
typedef struct t_Dwarf3_abbreviation_table
{
    /* Id of abbreviation table (and offset into the .debug_abbrev section */
    unsigned int offset;

    /* List of abbreviation that this table consist of */
    list_header *abbreviations;

    /* Fast look-up array for the abbreviations in above list */
    Dwarf3_abbreviation **fast_lookup;
    unsigned int          fast_lookup_n;   /* Number of elements in array */
} Dwarf3_abbreviation_table;

/* Dwarf compile unit header */
/* Stored in .debug_info elf sections */
typedef struct t_Dwarf3_compile_unit_header {
    /* Length of compile unit (not including length field itself) */
    unsigned int unit_length;

    /* Dwarf version */
    unsigned short version;

    /* Id (offset into .debug_abbrev) of abbreviation table */
    unsigned int debug_abbrev_offset;

    /* Size in bytes of an address in the target architecture */
    unsigned char address_size;
} Dwarf3_compile_unit_header;

/* Line number program header */
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
} Dwarf3_line_prologue;

/* Functions */
const char                 *dwarf_parse_debug_abbrev(ElfEnvironment *elfEnv, size_t n, void *data);
const char                 *dwarf_compute_abbrev_table_fast_lookup(ElfEnvironment *elfEnv);
Dwarf3_abbreviation_table  *dwarf_find_abbreviation_table(ElfEnvironment *elfEnv, unsigned int offset);
void                        dwarf_dump_abbrev_table_fast_lookup(ElfEnvironment *elfEnv, Dwarf3_abbreviation_table *abbrev_table);
void                        dwarf_dump_abbreviation(ElfEnvironment *elfEnv, Dwarf3_abbreviation *abbrev);
void                        dwarf_dump_abbreviation_tables(ElfEnvironment *elfEnv);
const char                 *dwarf_read_debug_abbrev(ElfEnvironment *elfEnv);
const char                 *dwarf_parse_debug_info(ElfEnvironment *elfEnv, size_t n, void *data, const char *(*user_func)(ElfEnvironment *, Dwarf3_abbreviation *, void *), void *user_func_data);
const char                 *dwarf_read_debug_info(ElfEnvironment *elfEnv, const char *(*user_func)(ElfEnvironment *, Dwarf3_abbreviation *, void *), void *user_func_data);
const char                 *dwarf_parse_compile_unit(ElfEnvironment *elfEnv, unsigned char **offset, 
                                                     const char *(*user_func)(ElfEnvironment *, Dwarf3_abbreviation *, void *),
                                                     void *user_func_data);
void                        dwarf_parse_compile_unit_header(ElfEnvironment *elfEnv, unsigned char **offset, Dwarf3_compile_unit_header *comp_unit_hdr);
void                        dwarf_dump_compile_unit_header(ElfEnvironment *elfEnv, Dwarf3_compile_unit_header *comp_unit_hdr);
const char                 *dwarf_parse_attributes(ElfEnvironment *elfEnv, Dwarf3_compile_unit_header *comp_unit_hdr, Dwarf3_attribute_specification *attr_spec, unsigned char **offset);

void                        dwarf_free_dwarf_abbreviation_tables_entry(void *data);
void                        dwarf_free_abbreviations_entry(void *data);
void                        dwarf_free_attribute_specification_list(void *data);

const char                 *dwarf_read_debug_line(ElfEnvironment *elfEnv, const char *(*user_func)(ElfEnvironment *, unsigned int, unsigned int, void *), void *user_func_data);
const char                 *dwarf_parse_debug_line(ElfEnvironment *elfEnv, size_t n, void *data, const char *(*user_func)(ElfEnvironment *, unsigned int, unsigned int, void *), void *user_func_data);

static unsigned int         dwarf_read_ULEB128(unsigned char **offset);
static signed int           dwarf_read_SLEB128(unsigned char **offset);

#endif



