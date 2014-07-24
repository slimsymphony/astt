/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                dwarfReader.c
                --------------
                SW Module






Project:          autogen

%name:             dwarfReader.c %
%version:          3 %
%instance:         co1tss_1 %
%derived_by:       nosterga %
%date_modified:    Fri Mar 25 08:22:52 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  File part of the source code for the autogen tool

    Contains the the implementation for various functions to read and parse the DWARF format
    (a way of storing debug information in a number of ELF sections) used by .out file. 
    The functions are focused on extracting debug information.
    Dwarf format described in

            DWARF Debugging Information Format 
            Version 3

            http://dwarfstd.org/

*/

#include "string.h"
#include "stdlib.h"
#include "assert.h"

#include "list.h"
#include "elfReader.h"
#include "dwarfReader.h"

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_parse_debug_abbrev
 
    Purpose: 
        Parses the content of the .debug_abbrev elf section
 
    Functional Description:
        The function loops through the whole .debug_abbrev elf section and parses the dwarf abbreviation tables
        stored here. The data is stored as a list of dwarf abbreviation tables in the 
        ElfEnvironment.dwarf_abbreviation_tables variable. This content is used when parsing the contents
        of the .debug_info elf section.
        The function calls dwarf_compute_abbrev_table_fast_lookup() to create a fast look-up array for the
        abbreviations in each abbreviation table.

    Arguments: 
        elfEnv : ELF data from .out file
        n      : Size of .debug_abbrev section
        data   : Contents of .debug_abbrev section

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_parse_debug_abbrev(ElfEnvironment *elfEnv, size_t n, void *data)
{
    const char *result = NULL;
    unsigned char *offset = (unsigned char *)data;
    unsigned char *last_byte = (unsigned char *)data + n;

    /* Prepare list to store abbrevation tables in */
    elfEnv->dwarf_abbreviation_tables = list_new();

    while (offset < last_byte)
    {
        unsigned int abbrev_code = 0;
        unsigned int saved_offset = 0;
        Dwarf3_abbreviation_table *abbrev_table = NULL;

        /* Read abbreviation code (unsigned LEB128) */
        /* Skip all 0 abbreviation codes */
        saved_offset = offset - (unsigned char *)data;
        abbrev_code = dwarf_read_ULEB128(&offset);
        while (abbrev_code == 0 && offset < last_byte)
        {
            saved_offset = offset - (unsigned char *)data;
            abbrev_code = dwarf_read_ULEB128(&offset);
        }

        /* Prepare a new abbreviation table */
        if (abbrev_code > 0 && offset < last_byte)
        {
            abbrev_table = (Dwarf3_abbreviation_table *)malloc(sizeof(Dwarf3_abbreviation_table));
            if (abbrev_table == 0)
            {
                /* Error */
                return "Out of memory";
            }

            /* Init new abbreviation table */
            abbrev_table->abbreviations = list_new();
            abbrev_table->offset = saved_offset;
            abbrev_table->fast_lookup_n = 0;
            abbrev_table->fast_lookup = NULL;

            /* Store the abbreviation table */
            list_add(elfEnv->dwarf_abbreviation_tables, abbrev_table);
        }

        /* The abbreviations for a compile unit ends with an abbreviation code == 0 */
        while (abbrev_code > 0 && offset < last_byte)
        {
            unsigned int attr_spec_name = 0;
            unsigned int attr_spec_form = 0;

            Dwarf3_abbreviation *abbrev = (Dwarf3_abbreviation *)malloc(sizeof(Dwarf3_abbreviation));
            if (abbrev == 0)
            {
                /* Error */
                return "Out of memory";
            }
            abbrev->attribute_specification_list = list_new();

            /* Store the abbreviation code */
            abbrev->abbreviation_code = abbrev_code;

            /* Read tag (unsigned LEB128) */
            abbrev->tag = dwarf_read_ULEB128(&offset);

            /* Read children (unsigned 1 byte) */
            abbrev->children = *offset++;

            /* Read initial attribute specification */
            /* attribute name / attribute form (unsigned LEB128 / unsigned LEB128) */
            attr_spec_name = dwarf_read_ULEB128(&offset);
            attr_spec_form = dwarf_read_ULEB128(&offset);

            /* Loop through all attribute specifications */
            /* Terminated by (0, 0) attribute specification */
            while (attr_spec_name > 0 || attr_spec_form > 0)
            {
                Dwarf3_attribute_specification *attr_spec = (Dwarf3_attribute_specification *)malloc(sizeof(Dwarf3_attribute_specification));
                if (attr_spec == 0)
                {
                    /* Error */
                    return "Out of memory";
                }

                /* Save attribute specification */
                attr_spec->name = attr_spec_name;
                attr_spec->form = attr_spec_form;
                attr_spec->size_of_blockdata = 0;
                attr_spec->data.vptr = NULL;
                list_add(abbrev->attribute_specification_list, attr_spec);

                /* Read next attribute specification */
                attr_spec_name = dwarf_read_ULEB128(&offset);
                attr_spec_form = dwarf_read_ULEB128(&offset);            
            }

            /* Save the abbreviation */
            list_add(abbrev_table->abbreviations, abbrev);

            /* Read the next abbreviation code (unsigned LEB128) */
            abbrev_code = dwarf_read_ULEB128(&offset);
        }
    }

    /* Compute fast look-up arrays for the abbreviation tables */
    result = dwarf_compute_abbrev_table_fast_lookup(elfEnv);
    
    return result;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_compute_abbrev_table_fast_lookup
 
    Purpose: 
        Loops through all dwarf abbreviation tables stored in ElfEnvironment.dwarf_abbreviation_tables
        and generates a fast look-up array for the abbreviation entries.
 
    Functional Description:
        It is a requirement of this function that ElfEnvironment.dwarf_abbreviation_tables has been 
        populated with abbreviation tables before calling this function.

        The look-up key for the array is the abbreviation code. See Dwarf3_abbreviation.abbreviation_code.

        The look-up array is stored for each abbreviation table in the following variables:
            Dwarf3_abbreviation_table.fast_lookup   : The array
            Dwarf3_abbreviation_table.fast_lookup_n : Size of array and max abbreviation code in the abbreviation table.

    Arguments: 
        elfEnv : ELF data from .out file

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_compute_abbrev_table_fast_lookup(ElfEnvironment *elfEnv)
{
    /* Compute fast look-up array for each abbreviation table */ 
    {
        list_element *abbrev_table_ptr = list_iterator_reset(elfEnv->dwarf_abbreviation_tables);

        /* Loop through all abbreviation tables */
        while (abbrev_table_ptr)
        {
            Dwarf3_abbreviation_table *abbrev_table = (Dwarf3_abbreviation_table *)abbrev_table_ptr->data;

            /* Compute fast look-up for this abbreviation table */
            {
                /* Determine highest abbreviation code number */
                unsigned int max_abbrev_code = 0;
                list_element *abbrev_ptr = list_iterator_reset(abbrev_table->abbreviations);

                while(abbrev_ptr)
                {
                    Dwarf3_abbreviation *abbrev = (Dwarf3_abbreviation *)abbrev_ptr->data;

                    /* Compute max value sofar */
                    max_abbrev_code = (abbrev->abbreviation_code > max_abbrev_code ?  abbrev->abbreviation_code : max_abbrev_code);

                    /* Next abbreviation */
                    abbrev_ptr = list_iterator_next(abbrev_table->abbreviations);
                }

                /* Allocate space for fast look-up table */
                abbrev_table->fast_lookup_n = max_abbrev_code;
                abbrev_table->fast_lookup = (Dwarf3_abbreviation **)malloc(sizeof(Dwarf3_abbreviation *) * (abbrev_table->fast_lookup_n+1));
                if (abbrev_table->fast_lookup == 0)
                {
                    /* Error */
                    return "Out of memory";
                }
                memset(abbrev_table->fast_lookup, 0, sizeof(Dwarf3_abbreviation *) * (abbrev_table->fast_lookup_n+1));

                /* Init fast look-up table */
                abbrev_ptr = list_iterator_reset(abbrev_table->abbreviations);

                while(abbrev_ptr)
                {
                    Dwarf3_abbreviation *abbrev = (Dwarf3_abbreviation *)abbrev_ptr->data;

                    /* Let fast_lookup[abbreviation code] point to corresponding abbreviation */
                    abbrev_table->fast_lookup[abbrev->abbreviation_code] = abbrev;

                    /* Next abbreviation */
                    abbrev_ptr = list_iterator_next(abbrev_table->abbreviations);
                }
            }

            /* Dump abbreviation table fast look-up array */
            dwarf_dump_abbrev_table_fast_lookup(elfEnv, abbrev_table);

            /* Next abbreviation table */
            abbrev_table_ptr = list_iterator_next(elfEnv->dwarf_abbreviation_tables);
        }
    }
    
    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_dump_abbrev_table_fast_lookup
 
    Purpose: 
        Dump the contents of the fast look-up array in an dwarf abbreviation table to a debug text file.
 
    Arguments: 
        elfEnv       : ELF data from .out file
        abbrev_table : Abbreviation table from where the fast look-up array should be dumped

    Return Values:
        - 
*/
/* --------------------------------------------------------------------------------------------- */
void dwarf_dump_abbrev_table_fast_lookup(ElfEnvironment *elfEnv, Dwarf3_abbreviation_table *abbrev_table)
{
    if (elfEnv->debug)
    {
        unsigned int i = 0;

        fprintf(elfEnv->debug, "Abbreviation table - fast look-up array: %d\n", abbrev_table->offset);
        for (i = 0; i <= abbrev_table->fast_lookup_n; i++)
        {
            if (abbrev_table->fast_lookup[i] == 0)
            {
                fprintf(elfEnv->debug, "(-, -), ");
            }
            else
            {
                fprintf(elfEnv->debug, "(%d, %d), ", i, (abbrev_table->fast_lookup[i])->abbreviation_code);
            }
        }
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_dump_abbreviation
 
    Purpose: 
        Dump the contents of a dwarf abbreviation entry to a debug text file.
 
    Arguments: 
        elfEnv : ELF data from .out file
        abbrev : Abbreviation declaration which will have its content dumped

    Return Values:
        - 
*/
/* --------------------------------------------------------------------------------------------- */
void dwarf_dump_abbreviation(ElfEnvironment *elfEnv, Dwarf3_abbreviation *abbrev)
{
    list_element *ptr = NULL;

    if (elfEnv->debug)
    {
        fprintf(elfEnv->debug, "Abbreviation: %d\n", abbrev->abbreviation_code);
        fprintf(elfEnv->debug, "    Tag: %03d Children: %d\n", abbrev->tag, abbrev->children);

        /* Loop through the attribute specification list */
        ptr = list_iterator_reset(abbrev->attribute_specification_list);
        while(ptr)
        {
            Dwarf3_attribute_specification *attr_spec = (Dwarf3_attribute_specification *)ptr->data;

            fprintf(elfEnv->debug, "    (%02X, %02X)\n", attr_spec->name, attr_spec->form);

            /* Next element */
            ptr = list_iterator_next(abbrev->attribute_specification_list);
        }
        fprintf(elfEnv->debug, "\n");
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_dump_abbreviation_tables
 
    Purpose: 
        Dump the contents of all dwarf abbreviation tables stored in ElfEnvironment.dwarf_abbreviation_tables
        to a debug text file.
 
    Arguments: 
        elfEnv : ELF data from .out file

    Return Values:
        - 
*/
/* --------------------------------------------------------------------------------------------- */
void dwarf_dump_abbreviation_tables(ElfEnvironment *elfEnv)
{
    if (elfEnv->debug)
    {
        /* Loop through all abbreviation tables */
        list_element *ptr1 = list_iterator_reset(elfEnv->dwarf_abbreviation_tables);
        while(ptr1)
        {
            Dwarf3_abbreviation_table *abbrev_table = (Dwarf3_abbreviation_table *)ptr1->data;
            list_element *ptr2 = list_iterator_reset(abbrev_table->abbreviations);

            /* Loop through all abbreviations in a single abbreviation table */
            fprintf(elfEnv->debug, "Table: %d\n", abbrev_table->offset);
            fprintf(elfEnv->debug, "================\n");
            while(ptr2)
            {
                Dwarf3_abbreviation *abbrev = (Dwarf3_abbreviation *)ptr2->data;
                dwarf_dump_abbreviation(elfEnv, abbrev);

                /* Next */
                ptr2 = list_iterator_next(abbrev_table->abbreviations);
            }

            /* Next */
            ptr1 = list_iterator_next(elfEnv->dwarf_abbreviation_tables);
        }
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_read_debug_abbrev
 
    Purpose: 
        Read in the .debug_abbrev elf section and calls dwarf_parse_debug_abbrev() to parse the contents.
 
    Arguments: 
        elfEnv : ELF data from .out file

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_read_debug_abbrev(ElfEnvironment *elfEnv)
{
    int i;

    if (elfEnv->shtable == NULL)
    {
        /* Error */
        return "Section header table has not been read";
    }

    /* Loop up the section header entry for .debug_abbrev */
    for (i = 0; i < elfEnv->elf_hdr.e_shnum; i++)
    {
        /* Look up section header name */
        const char *sh_name = &elfEnv->elf_sec_name_str_table[elfEnv->shtable[i].sh_name];

        /* Is the section the correct one? */
        if (strcmp(sh_name, ".debug_abbrev") == 0)
        {
            const char *result = NULL;
            Elf32_Shdr *sec_hdr = &elfEnv->shtable[i];

            /* .debug_abbrev found. Read section data */
            unsigned char *debug_abbrev = (unsigned char *)elf_read_section_data(elfEnv, sec_hdr);
            if (debug_abbrev == 0)
            {
                /* Error */
                return "Error reading .debug_abbrev section";
            }

            /* Dump data */
            /* elf_dump_section_data(elfEnv, ".debug_abbrev:", sec_hdr->sh_size, debug_abbrev); */

            /* Parse data */
            result = dwarf_parse_debug_abbrev(elfEnv,sec_hdr->sh_size, debug_abbrev);
            if (result != NULL)
            {
                /* Error */
                return result;
            }

            /* Clean up */
            free(debug_abbrev);
            break;
        }
    }

    /* Dump parsed data */
    dwarf_dump_abbreviation_tables(elfEnv);

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_parse_compile_unit_header
 
    Purpose: 
        Read and parse a compile unit header in the .debug_info elf section.
 
    Arguments: 
        elfEnv        : ELF data from .out file
        offset        : A pointer to where the compile unit header is stored. After function call this 
                        pointer is updated to point to the first byte after the compile unit header.
        comp_unit_hdr : Pointer to a structure where the contents of the compile unit header is stored.

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void dwarf_parse_compile_unit_header(ElfEnvironment *elfEnv, unsigned char **offset, Dwarf3_compile_unit_header *comp_unit_hdr)
{
    /* Read unit_length */
    comp_unit_hdr->unit_length = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));
    *offset += 4;

    /* Read version */
    comp_unit_hdr->version = elf_fix_word(elfEnv->elf_dataorder, *((unsigned short *)*offset));
    *offset += 2;

    /* Read debug_abrev_offset */
    comp_unit_hdr->debug_abbrev_offset = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));
    *offset += 4;

    /* Read address_size */
    comp_unit_hdr->address_size = *((unsigned char *)*offset);
    *offset += 1;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_dump_compile_unit_header
 
    Purpose: 
        Dump the contents of a compile unit header to a debug text file
 
    Arguments: 
        elfEnv        : ELF data from .out file
        comp_unit_hdr : The compile unit header to be dumped

    Return Values:
        - 
*/
/* --------------------------------------------------------------------------------------------- */
void dwarf_dump_compile_unit_header(ElfEnvironment *elfEnv, Dwarf3_compile_unit_header *comp_unit_hdr)
{
    if (elfEnv->debug && comp_unit_hdr)
    {
        fprintf(elfEnv->debug, "Compile unit: \n");
        fprintf(elfEnv->debug, "  unit_length:         %d\n", comp_unit_hdr->unit_length);
        fprintf(elfEnv->debug, "  version:             %d\n", comp_unit_hdr->version);
        fprintf(elfEnv->debug, "  debug_abbrev_offset: %d\n", comp_unit_hdr->debug_abbrev_offset);
        fprintf(elfEnv->debug, "  address_size:        %d\n", comp_unit_hdr->address_size);
        fprintf(elfEnv->debug, "\n");
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_find_abbreviation_table
 
    Purpose: 
        Loops through all abbreviation tables stored in ElfEnvironment.dwarf_abbreviation_tables
        to find the one with the given Id (offset into .debug_abbrev)
 
    Functional Description:
        It is a requirement of this function that ElfEnvironment.dwarf_abbreviation_tables has been 
        populated with abbreviation tables before calling this function.

    Arguments: 
        elfEnv : ELF data from .out file
        offset : The id / offset of the abbreviation table to be searched for

    Return Values:
        Pointer to the abbreviation tables searched for. NULL if not found
*/
/* --------------------------------------------------------------------------------------------- */
Dwarf3_abbreviation_table *dwarf_find_abbreviation_table(ElfEnvironment *elfEnv, unsigned int offset)
{
    /* Loop through all abbreviation tables searching for one with same offset as parameter offset */
    list_element *ptr1 = list_iterator_reset(elfEnv->dwarf_abbreviation_tables);
    while(ptr1)
    {
        Dwarf3_abbreviation_table *abbrev_table = (Dwarf3_abbreviation_table *)ptr1->data;

        if (abbrev_table->offset == offset)
        {
            /* Found */
            return abbrev_table;
        }

        /* Next */
        ptr1 = list_iterator_next(elfEnv->dwarf_abbreviation_tables);
    }

    /* Not found */
    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_parse_debug_info
 
    Purpose: 
        Parses the content of the .debug_info elf section
 
    Functional Description:
        The function loops through the whole .debug_info elf section and parses all the dwarf compile units
        stored here.
        The compile units consists of a compile unit header followed by a tree of Debugging Information Entries (DIE)
        (see DWARF documentation for further description)

        A user function is called for each DIE collected. The user function can then extract the needed information
        and store it in a user data structure 'user_func_data'.

    Arguments: 
        elfEnv         : ELF data from .out file
        n              : Size of .debug_info section
        data           : Contents of .debug_info section
        user_func      : User supplied function that will be called for each collected DIE
                         Arguments:
                            ElfEnvironment *       : ELF data from .out file
                            Dwarf3_abbreviation *  : The abbreviation also contains the collected data from the DIE
                            void *                 : User supplied data structure. Can be used to store the extracted data
                         Return Values:
                            NULL if all is ok otherwise a text string describing the problem
        user_func_data : User supplied data structure. Can be used to store the extracted data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem

    Example on a user function:

        const char *extract_debuginfo_func(ElfEnvironment *elfEnv, Dwarf3_abbreviation *abbrev, void *data)
        {
            pmd_debuginfo *user_data = (pmd_debuginfo *)data;

            if (abbrev->tag == 0x11 / * DW_TAG_compile_unit * /)
            {
                list_element *ptr = NULL;

                / * Loop through all attribute specifications and the collected data values * /
                ptr = list_iterator_reset(abbrev->attribute_specification_list);
                while(ptr)
                {
                    Dwarf3_attribute_specification *attr_spec = (Dwarf3_attribute_specification *)ptr->data;

                    switch(attr_spec->name)
                    {
                    case 0x11: / * DW_AT_low_pc - address * /
                        user_data->low_address[user_data->cnt] = attr_spec->data.uint;
                        break;

                    case 0x12: / * DW_AT_high_pc - address * /
                        user_data->high_address[user_data->cnt++] = attr_spec->data.uint;
                        break;

                    default:
                        break;
                    }

                    / * Next attribute specification * /
                    ptr = list_iterator_next(abbrev->attribute_specification_list);
                }
            } 

            return NULL;
        }
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_parse_debug_info(ElfEnvironment *elfEnv, size_t n, void *data, const char *(*user_func)(ElfEnvironment *, Dwarf3_abbreviation *, void *), void *user_func_data)
{
    const char *result = NULL;
    unsigned char *offset = (unsigned char *)data;

    /* Loop through all compile units */
    while (offset < (unsigned char *)data + n)
    {
        /* Parse one compile unit */
        result = dwarf_parse_compile_unit(elfEnv, &offset, user_func, user_func_data);
        if (result)
        {
            /* Error */
            return result;
        }
    }

    return result;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_parse_compile_unit
 
    Purpose: 
        Parses the content of a single compile unit in the .debug_info elf section
 
    Functional Description:
        A compile unit consist of a compile unit header followed by a tree of Debugging Information Entries (DIE)
        (see DWARF documentation for further description)

        A user function is called for each DIE collected. The user function can then extract the needed information
        and store it in a user data structure 'user_func_data'. For further information about the user function
        please see comments for dwarf_parse_debug_info()

    Arguments: 
        elfEnv         : ELF data from .out file
        offset         : A pointer to where the compile unit is stored. After function call this 
                         pointer is updated to point to the first byte after the compile unit.
        user_func      : User supplied function that will be called for each collected DIE
        user_func_data : User supplied data structure. Can be used to store the extracted data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_parse_compile_unit(ElfEnvironment *elfEnv, unsigned char **offset, 
                                     const char *(*user_func)(ElfEnvironment *, Dwarf3_abbreviation *, void *),
                                     void *user_func_data)
{
    const char *result = NULL;
    Dwarf3_abbreviation_table *abbrev_table = NULL;
    unsigned char *start_of_comp_unit = *offset;
    Dwarf3_compile_unit_header comp_unit_hdr;

    /* Read compile unit header */
    dwarf_parse_compile_unit_header(elfEnv, offset, &comp_unit_hdr);

    /* Dump compile unit header */
    dwarf_dump_compile_unit_header(elfEnv, &comp_unit_hdr);

    /* Find abbreviation table associated with this compile unit */
    abbrev_table = dwarf_find_abbreviation_table(elfEnv, comp_unit_hdr.debug_abbrev_offset);
    if (abbrev_table == NULL)
    {
        /* Error */
        return "Unknown abbreviation table encountered";
    }

    /* Loop through whole compile unit */
    while(*offset < start_of_comp_unit + 4 + comp_unit_hdr.unit_length)
    {
        unsigned int abbrev_code;
        Dwarf3_abbreviation *abbrev = NULL;

        /* Read abbreviation code */
        abbrev_code = dwarf_read_ULEB128(offset);
        if (abbrev_code > 0)
        {
            list_element *ptr = NULL;

            /* Look-up abbreviation */
            if (abbrev_code > abbrev_table->fast_lookup_n)
            {
                /* Error */
                return "Abbreviation code out of bounds";
            }
            abbrev = abbrev_table->fast_lookup[abbrev_code];

            /* Dump abreviation information */
            if (elfEnv->debug)
            {
                fprintf(elfEnv->debug, "Abbreviation code: %d Tag: %d Children: %d\n", abbrev->abbreviation_code, abbrev->tag, abbrev->children);
            }

            /* Loop through attributes */
            ptr = list_iterator_reset(abbrev->attribute_specification_list);
            while(ptr)
            {
                Dwarf3_attribute_specification *attr_spec = (Dwarf3_attribute_specification *)ptr->data;

                result = dwarf_parse_attributes(elfEnv, &comp_unit_hdr, attr_spec, offset);
                if (result)
                {
                    /* Error */
                    return result;
                }

                /* Next attribute specification */
                ptr = list_iterator_next(abbrev->attribute_specification_list);
            }

            /* Call user function */
            result = user_func(elfEnv, abbrev, user_func_data);
            if (result)
            {
                /* Error */
                return result;
            }
        }
    }

    return result;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_parse_attributes
 
    Purpose: 
        Reads and parses a single attribute value from a DIE.
 
    Functional Description:
        This function reads the next attribute value from the current DIE being parsed.
        The attribute specification 'attr_spec' tells what attribute that should be read and what format
        the attribute value is stored in. The actual attribute value read will be stored in the 'attr_spec'
        structure such that it can be read by the caller of the function.

        The attribute value will be stored in the variable Dwarf3_attribute_specification.data which is a
        union with the following members (Lists also which attribute value formats that uses which union members)
           unsigned int uint      : DW_FORM_addr, DW_FORM_data2, DW_FORM_data4, DW_FORM_data1, DW_FORM_flag
                                    DW_FORM_udata, DW_FORM_ref_addr, DW_FORM_ref1, DW_FORM_ref2, DW_FORM_ref4,
                                    DW_FORM_ref_udata
                                    (DW_FORM_strp (TBD - Currently belongs to uint because it only returns the string index into the .debug_str.
                                                         But it should belong to 'cptr' and return the looked-up string)
                                    )
           unsigned long long ull : DW_FORM_data8, DW_FORM_ref8
           const char *cptr       : DW_FORM_string, 
           signed int sint        : DW_FORM_sdata
           void *vptr             : DW_FORM_block2, DW_FORM_block4, DW_FORM_block, DW_FORM_block1, 

        TBD: DW_FORM_indirect - Can parse attribute value but can not currently return collected data.
                                Needs to be fixed.

        Note that Dwarf3_attribute_specification.size_of_blockdata will tell the size of the block when using 'vptr'
        union member.

    Arguments: 
        elfEnv         : ELF data from .out file
        comp_unit_hdr  : Pointer to the compile unit header associated with the compile unit being parsed.
                         Data in this structure is used by some of the attribute data formats
        attr_spec      : Attribute specification that specifies the attribute name and the format of the attribute
                         value.
        offset         : Points to start of the attribute value. After function call it has been updated to point to the first
                         byte after the attribute value.

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_parse_attributes(ElfEnvironment *elfEnv, Dwarf3_compile_unit_header *comp_unit_hdr, Dwarf3_attribute_specification *attr_spec, unsigned char **offset)
{
    switch (attr_spec->form)
    { 
    case DW_FORM_addr:
        {
            /* An address on the target machine. Size specified in compilation unit header */
            attr_spec->data.uint = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += comp_unit_hdr->address_size;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_addr: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_block2:
        {
            /* A 2-byte length followed by 0 to 65,535 contiguous information bytes */
            attr_spec->size_of_blockdata = elf_fix_word(elfEnv->elf_dataorder, *((unsigned short *)*offset));
            attr_spec->data.vptr = *offset + 2;

            /* Advance pointer */
            *offset += 2 + attr_spec->size_of_blockdata;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_block2: length: %d\n", attr_spec->name, attr_spec->size_of_blockdata);
        }
        break;

    case DW_FORM_block4:
        {
            /* A 4-byte length followed by 0 to 4,294,967,295 contiguous information bytes */
            attr_spec->size_of_blockdata = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));
            attr_spec->data.vptr = *offset + 4;

            /* Advance pointer */
            *offset += 4 + attr_spec->size_of_blockdata;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_block4: length: %d\n", attr_spec->name, attr_spec->size_of_blockdata);
        }
        break;

    case DW_FORM_data2:
        {
            /* A 2-byte constant */
            attr_spec->data.uint = elf_fix_word(elfEnv->elf_dataorder, *((unsigned short *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 2;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_data2: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_data4:
        {
            /* A 4-byte constant */
            attr_spec->data.uint = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 4;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_data4: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_data8:
        {
            /* A 8-byte constant */
            attr_spec->data.ull = elf_fix_ddword(elfEnv->elf_dataorder, *((unsigned long long *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 8;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_data8: %lld\n", attr_spec->name, attr_spec->data.ull);
        }
        break;

    case DW_FORM_string:
        {
            /* A null terminated string */
            attr_spec->data.cptr = (const char *)*offset;
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += strlen((const char *)*offset)+1;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_data8: %s\n", attr_spec->name, attr_spec->data.cptr);
        }
        break;

    case DW_FORM_block:
        {
            /* An unsigned LEB128 length followed by the number of bytes specified by the length */
            attr_spec->size_of_blockdata = dwarf_read_ULEB128(offset);
            attr_spec->data.vptr = *offset;

            /* Advance pointer */
            *offset += attr_spec->size_of_blockdata;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_block: length: %d\n", attr_spec->name, attr_spec->size_of_blockdata);
        }
        break;

    case DW_FORM_block1:
        {
            /* A 1-byte length followed by 0 to 255 contiguous information bytes */
            attr_spec->size_of_blockdata = **offset;
            attr_spec->data.vptr = *offset + 1;

            /* Advance pointer */
            *offset += 1 + attr_spec->size_of_blockdata;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_block1: length: %d\n", attr_spec->name, attr_spec->size_of_blockdata);
        }
        break;

    case DW_FORM_data1:
        {
            /* A 1-byte constant */
            attr_spec->data.uint = **offset;
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 1;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_data1: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_flag:
        {
            /* A 1-byte flag */
            attr_spec->data.uint = **offset;
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 1;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_flag: %02X\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_sdata:
        {
            /* A signed LEB128 constant */
            attr_spec->data.sint = dwarf_read_SLEB128(offset);
            attr_spec->size_of_blockdata = 0;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_sdata: %d\n", attr_spec->name, attr_spec->data.sint);
        }
        break;

    case DW_FORM_strp:
        {
            /* TBD - Not finished - Read in and look up  string in .debug_str. Assign char * to attr_spec->data.cptr */
            /* A 4-byte unsigned offset into a string table contained in the .debug_str section */
            attr_spec->data.uint = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 4;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_strp: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_udata:
        {
            /* A unsigned LEB128 constant */
            attr_spec->data.uint = dwarf_read_ULEB128(offset);
            attr_spec->size_of_blockdata = 0;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_udata: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_ref_addr:
        {
            /* A 4-byte refrence to a DIE within any compilation unit */
            attr_spec->data.uint = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 4;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_ref_addr: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_ref1:
        {
            /* A 1-byte refrence to a DIE within the containing compilation unit */
            attr_spec->data.uint = **offset;
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 1;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_ref1: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_ref2:
        {
            /* A 2-byte refrence to a DIE within the containing compilation unit */
            attr_spec->data.uint = elf_fix_word(elfEnv->elf_dataorder, *((unsigned short *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 2;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_ref2: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_ref4:
        {
            /* A 4-byte refrence to a DIE within the containing compilation unit */
            attr_spec->data.uint = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 4;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_ref4: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_ref8:
        {
            /* A 8-byte refrence to a DIE within the containing compilation unit */
            attr_spec->data.ull = elf_fix_ddword(elfEnv->elf_dataorder, *((unsigned long long *)*offset));
            attr_spec->size_of_blockdata = 0;

            /* Advance pointer */
            *offset += 8;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_ref8: %lld\n", attr_spec->name, attr_spec->data.ull);
        }
        break;

    case DW_FORM_ref_udata:
        {
            /* A unsigned LEB128 refrence to a DIE within the containing compilation unit */
            attr_spec->data.uint = dwarf_read_ULEB128(offset);
            attr_spec->size_of_blockdata = 0;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_ref_udata: %d\n", attr_spec->name, attr_spec->data.uint);
        }
        break;

    case DW_FORM_indirect:
        {
            /* The attribute value itself in the .debug_info section begins with an unsigned LEB128 number that represents its form.*/
            /* The data for this form follows the LEB128 */
            /* TBD - Data is not stored in the attr_spec.data and attr_spec.size_of_blockdata - Needs to be fixed */
            Dwarf3_attribute_specification new_attr_spec;

            new_attr_spec.form = dwarf_read_ULEB128(offset);
            new_attr_spec.name = attr_spec->name;
            new_attr_spec.data.vptr = NULL;
            new_attr_spec.size_of_blockdata = 0;

            if (elfEnv->debug) fprintf(elfEnv->debug, "  Attr: %02d - DW_FORM_indirect - ", attr_spec->name);

            return dwarf_parse_attributes(elfEnv, comp_unit_hdr, &new_attr_spec, offset);
        }
        break;

    default:
        {
            return "Unknown DW_FORM_<x> encountered";
        }
        break;
    }

    return NULL;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_read_debug_info
 
    Purpose: 
        Read in the .debug_info elf section and calls dwarf_parse_debug_info() to parse the contents.
        See description of dwarf_parse_debug_info() for more info.
 
    Arguments: 
        elfEnv         : ELF data from .out file
        user_func      : User supplied function that will be called for each collected DIE
        user_func_data : User supplied data structure. Can be used to store the extracted data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_read_debug_info(ElfEnvironment *elfEnv, const char *(*user_func)(ElfEnvironment *, Dwarf3_abbreviation *, void *), void *user_func_data)
{
    int i;
    const char *result = NULL;

    if (elfEnv->shtable == NULL)
    {
        /* Error */
        return "Section header table has not been read";
    }

    /* Loop up the section header entry for .debug_info */
    for (i = 0; i < elfEnv->elf_hdr.e_shnum; i++)
    {
        /* Look up section header name */
        const char *sh_name = &elfEnv->elf_sec_name_str_table[elfEnv->shtable[i].sh_name];

        /* Is the section the correct one? */
        if (strcmp(sh_name, ".debug_info") == 0)
        {
            Elf32_Shdr *sec_hdr = &elfEnv->shtable[i];

            /* .debug_info found. Read section data */
            unsigned char *debug_info = (unsigned char *)elf_read_section_data(elfEnv, sec_hdr);
            if (debug_info == 0)
            {
                /* Error */
                return "Error reading .debug_info section";
            }

            /* Dump data */
            /* elf_dump_section_data(elfEnv, ".debug_info:", sec_hdr->sh_size, debug_info); */

            /* Parse data */
            result = dwarf_parse_debug_info(elfEnv,sec_hdr->sh_size, debug_info, user_func, user_func_data);

            /* Clean up */
            free(debug_info);
            break;
        }
    }

    return result;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_free_attribute_specification_list
 
    Purpose: 
        A function to be given as argument to list_delete() when deleting a list containing
        Dwarf3_attribute_specification list elements.
 
    Arguments: 
        data : Pointer to a list_element->data. Must be a structure of type Dwarf3_attribute_specification.

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void dwarf_free_attribute_specification_list(void *data)
{
    Dwarf3_attribute_specification *attr_spec = (Dwarf3_attribute_specification *)data;

    /* Free actual attribute specification */
    free(attr_spec);
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_free_abbreviations_entry
 
    Purpose: 
        A function to be given as argument to list_delete() when deleting a list containing
        Dwarf3_abbreviation list elements.
 
    Arguments: 
        data : Pointer to a list_element->data. Must be a structure of type Dwarf3_abbreviation.

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void dwarf_free_abbreviations_entry(void *data)
{
    Dwarf3_abbreviation *abbrev = (Dwarf3_abbreviation *)data;

    /* Delete attribute specification list */
    list_delete(abbrev->attribute_specification_list, dwarf_free_attribute_specification_list);

    /* Delete actual abbreviation */
    free(abbrev);
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_free_dwarf_abbreviation_tables_entry
 
    Purpose: 
        A function to be given as argument to list_delete() when deleting a list containing
        Dwarf3_abbreviation_table list elements.
 
    Arguments: 
        data : Pointer to a list_element->data. Must be a structure of type Dwarf3_abbreviation_table.

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void dwarf_free_dwarf_abbreviation_tables_entry(void *data)
{
    Dwarf3_abbreviation_table *abbrev_table = (Dwarf3_abbreviation_table *)data;

    /* Free the fast look-up table */
    free(abbrev_table->fast_lookup);

    /* Free abbreviations in table */
    list_delete(abbrev_table->abbreviations, dwarf_free_abbreviations_entry);

    /* Free actual abbreviation table */
    free(abbrev_table);
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_parse_debug_line
 
    Purpose: 
        Parse the content of the .debug_line elf section.

    Functional Description:
        The function loops through the whole .debug_line section and parses all the Line Number Programs.
        (See DWARF documentation for further information)

        A user function is called every time an address / source code line number pair has been collected.
        The user function can then extract the needed information and store it in a user data structure 
        'user_func_data'.

    Arguments: 
        elfEnv         : ELF data from .out file
        n              : Size of .debug_line elf section
        data           : Data contents of the .debug_line elf section
        user_func      : User supplied function that will be called for each collected pair of address / line number
                         Arguments:
                            ElfEnvironment *       : ELF data from .out file
                            unsigned int           : Collected address
                            unsigned int           : Collected source code line number
                            void *                 : User supplied data structure. Can be used to store the extracted data
                         Return Values:
                            NULL if all is ok otherwise a text string describing the problem
        user_func_data : User supplied data structure. Can be used to store the extracted data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem

    Example on a user function:

        const char *extract_debuginfo_line(ElfEnvironment *elfEnv, unsigned int address, unsigned int line, void *data)
        {
            pmd_debuginfo *user_data = (pmd_debuginfo *)data;

            / * Store data * /
            user_data->address[user_data->cnt]  = address;
            user_data->lineNo[user_data->cnt++] = line;

            return NULL;
        }
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_parse_debug_line(ElfEnvironment *elfEnv, size_t n, void *data, const char *(*user_func)(ElfEnvironment *, unsigned int, unsigned int, void *), void *user_func_data)
{
     Dwarf3_line_prologue lp;
    unsigned char *offset_ptr = (unsigned char*)data;

    while(offset_ptr < (unsigned char *)data + n)
    {
        unsigned char reset=1;
        unsigned int address=0;
        unsigned int line=0;
        unsigned int pad=0;
        unsigned char *start_line_number_program_header = offset_ptr;

retry:
        lp.total_length    = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)offset_ptr));
        offset_ptr += 4;

        lp.version         = elf_fix_word(elfEnv->elf_dataorder, *((unsigned short *)offset_ptr));
        offset_ptr += 2;

        lp.prologue_length = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)offset_ptr));
        offset_ptr += 4;

        /*
        * Heuristic to detect and skip padding.
        *
        * ARM RVCT  2.x pad .debug_line entries to 4-byte alignment,
        * but 3.x does not.
        */
        if (   (lp.version != 2 && lp.version != 3)
            || (offset_ptr >= (unsigned char *)data + n)
            || (lp.total_length == 0)
            || (lp.total_length >= n - (offset_ptr - (unsigned char *)data))
           )
        {
            if (pad < 3)
            {
                /* Adjust padding to find header. */
                ++pad;
                ++offset_ptr;

                if (elfEnv->debug)
                {
                    fprintf(elfEnv->debug, "Skip pad byte ... ");
                }

                goto retry;    /* Read the header again */
            }

            /* Got out of sync with the DWARF format */
            return "Line number problem in .out file in section .debug_line";
        }

        if (elfEnv->debug && pad > 0)
        {
            /* Padding bytes have been detected and logs written out. Terminate with CR */
            fprintf(elfEnv->debug, "\n");
        }


        lp.minimum_instruction_length = *offset_ptr++;
        lp.default_is_stmt = *offset_ptr++;
        lp.line_base = *((signed char *)offset_ptr++);
        lp.line_range = *offset_ptr++;
        lp.opcode_base = *offset_ptr++;

        memset(&lp.standard_opcode_lengths[0], 0, 256);
        memcpy(&lp.standard_opcode_lengths[1], offset_ptr, lp.opcode_base-1);

        if (elfEnv->debug)
        {
            fprintf(elfEnv->debug, "\n");
            fprintf(elfEnv->debug, "Statement Program Prologue (Section offset = 0x%08X)\n", offset_ptr - (unsigned char *)data);
            fprintf(elfEnv->debug, "---------------------------------------------------------------------------------------------------\n");
            fprintf(elfEnv->debug, "total_length  version  prologue_length  min_inst_length  is_stmt  line_base  line_range  opcode_base\n");
            fprintf(elfEnv->debug, "  0x%08X       %2d       0x%08X               %2d       %2d         %2d          %2d          %3d\n", 
                lp.total_length, lp.version, lp.prologue_length, lp.minimum_instruction_length, 
                lp.default_is_stmt, lp.line_base, lp.line_range, lp.opcode_base);
        }

        offset_ptr = start_line_number_program_header + lp.prologue_length+10;

        while (offset_ptr < (start_line_number_program_header + lp.total_length + 4))
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
            opcode = *offset_ptr++;
            if (opcode<lp.opcode_base)
            {
                switch (opcode)
                {
                case 0:
                    {
                        unsigned char length;
                        length = *offset_ptr++;
                        opcode = *offset_ptr++;
                        switch(opcode)
                        {
                        case DW_LNE_end_Sequence:
                            assert(length==1);
                            check=1;
                            reset=1;
                            break;
                        case DW_LNE_set_address:
                            assert(length==5);
                            address = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)offset_ptr));
                            offset_ptr += 4;
                            break;
                        case DW_LNE_define_file:
                            offset_ptr += length - 1;
                            break;
                        default:
                            offset_ptr += length - 1;
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
                    address += lp.minimum_instruction_length * dwarf_read_ULEB128(&offset_ptr);
                    break;
                case DW_LNS_advance_line:
                    assert(lp.standard_opcode_lengths[opcode]==1);
                    line+=dwarf_read_SLEB128(&offset_ptr);
                    break;
                case DW_LNS_set_file:
                    assert(lp.standard_opcode_lengths[opcode]==1);
                    dwarf_read_ULEB128(&offset_ptr);
                    break;
                case DW_LNS_const_add_pc:
                    assert(lp.standard_opcode_lengths[opcode]==0);
                    address += lp.minimum_instruction_length*((255-lp.opcode_base)/lp.line_range);
                    break;
                case DW_LNS_fixed_advance_pc:
                    assert(lp.standard_opcode_lengths[opcode]==0);
                    increment = elf_fix_word(elfEnv->elf_dataorder, *((unsigned short *)offset_ptr));
                    offset_ptr += 2;
                    address += increment;
                    break;
                default:
                    {
                        int ix;
                        for (ix=0;ix<lp.standard_opcode_lengths[opcode];++ix)
                            dwarf_read_ULEB128(&offset_ptr);
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
                const char *result = NULL;

                result = user_func(elfEnv, address, line, user_func_data);
                if (result) 
                {
                    return result;
                }
            }
        }
    }

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_read_debug_line
 
    Purpose: 
        Read in the .debug_line elf section and calls dwarf_parse_debug_line() to parse the contents.
        See description of dwarf_parse_debug_line() for more info.
 
    Arguments: 
        elfEnv         : ELF data from .out file
        user_func      : User supplied function that will be called for each collected address/line pair
        user_func_data : User supplied data structure. Can be used to store the extracted data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *dwarf_read_debug_line(ElfEnvironment *elfEnv, const char *(*user_func)(ElfEnvironment *, unsigned int, unsigned int, void *), void *user_func_data)
{
    int i;
    const char *result = NULL;

    if (elfEnv->shtable == NULL)
    {
        /* Error */
        return "Section header table has not been read";
    }

    /* Loop up the section header entry for .debug_line */
    for (i = 0; i < elfEnv->elf_hdr.e_shnum; i++)
    {
        /* Look up section header name */
        const char *sh_name = &elfEnv->elf_sec_name_str_table[elfEnv->shtable[i].sh_name];

        /* Is the section the correct one? */
        if (strcmp(sh_name, ".debug_line") == 0)
        {
            Elf32_Shdr *sec_hdr = &elfEnv->shtable[i];

            /* .debug_line found. Read section data */
            unsigned char *debug_info = (unsigned char *)elf_read_section_data(elfEnv, sec_hdr);
            if (debug_info == 0)
            {
                /* Error */
                return "Error reading .debug_line section";
            }

            /* Dump data */
            /* elf_dump_section_data(elfEnv, ".debug_line:", sec_hdr->sh_size, debug_info); */

            /* Parse data */
            result = dwarf_parse_debug_line(elfEnv,sec_hdr->sh_size, debug_info, user_func, user_func_data);

            /* Clean up */
            free(debug_info);
            break;
        }
    }

    return result;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_read_ULEB128
 
    Purpose: 
        Read and return a unsigned LEB128 value.
 
    Arguments: 
        offset : Pointer to start of ULEB128 and is updated to point to first byte after the ULEB128.

    Return Values:
        Value read
*/
/* --------------------------------------------------------------------------------------------- */
static unsigned int dwarf_read_ULEB128(unsigned char **offset)
{
    unsigned int result = 0;
    unsigned int shift = 0;
    unsigned char byte = 0x80;
    while ((byte & 0x80) == 0x80)
    {
        byte = *(*offset)++;
        result |= (byte & 0x7F) << shift;
        shift += 7;
    }
    return result;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: dwarf_read_SLEB128
 
    Purpose: 
        Read and return a signed LEB128 value.
 
    Arguments: 
        offset : Pointer to start of SLEB128 and is updated to point to first byte after the SLEB128.

    Return Values:
        Value read
*/
/* --------------------------------------------------------------------------------------------- */
static signed int dwarf_read_SLEB128(unsigned char **offset)
{
    signed int result = 0;
    unsigned int shift = 0;
    unsigned char byte = 0x80;
    while ((byte & 0x80) == 0x80)
    {
        byte = *(*offset)++;
        result |= (byte & 0x7F) << shift;
        shift += 7;
    }
    if (shift < 32 && ((byte & 0x40) == 0x40))
    {
        result |= - (1 << shift);
    }
    return result;
}

