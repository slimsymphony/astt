/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                elfReader.c
                --------------
                SW Module






Project:          autogen

%name:             elfReader.c %
%version:          3 %
%instance:         co1tss_1 %
%derived_by:       nosterga %
%date_modified:    Thu Mar 24 17:58:19 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  File part of the source code for the autogen tool

    Contains the the implementation for various functions to read and parse the ELF format
    used by .out file. The functions are focused on extracting debug information.
    Elf format described in

            Tool Interface Standard (TIS)
            Executable and Linking Format (ELF)
            Specification
            Version 1.2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elf.h"
#include "elfReader.h"
#include "dwarfReader.h"

/* Read a byte from file and return value */
int elf_read_byte(FILE* elf_file, unsigned char* bvalue)
{
    size_t nread = fread(bvalue, 1, 1, elf_file);

    return nread == 1;
}

/* Read a number of bytes from file */
int elf_read_bytes(FILE* elf_file, unsigned char* buffer, unsigned int nbytes)
{
    size_t nread = fread(buffer, nbytes, 1, elf_file);

    return nread == 1;
}

/* Read 2 bytes from file and return value fixed wrt to endianess */
int elf_read_word(FILE* elf_file, unsigned char elf_dataorder, unsigned short* svalue)
{
    size_t nread = fread(svalue, 2, 1, elf_file);
    *svalue = elf_fix_word(elf_dataorder, *svalue);

    return nread == 1;
}

/* Read 4 bytes from file and return value fixed wrt to endianess */
int elf_read_dword(FILE* elf_file, unsigned char elf_dataorder, unsigned int* lvalue)
{
    size_t nread = fread(lvalue, 4, 1, elf_file);
    *lvalue = elf_fix_dword(elf_dataorder, *lvalue);

    return nread == 1;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_fix_word
 
    Purpose: 
        Convert the input value (2 bytes) accordingly with the endianess of the .out file

    Arguments: 
        elf_dataorder : ELFDATA2MSB = ELF values in big endian. Convert value to little endian
                        ELFDATA2LSB = ELF values in little endian. Return value as is.
        l             : Value to be converted

    Return Values:
        The converted value
*/
/* --------------------------------------------------------------------------------------------- */
unsigned short elf_fix_word(unsigned char elf_dataorder, unsigned short w)
{
    if (elf_dataorder == ELFDATA2MSB)
    {
        w = (unsigned short)(((w & 0x00FF) << 8) | ((w & 0xFF00) >> 8));
    }
    return w;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_fix_dword
 
    Purpose: 
        Convert the input value (4 bytes) accordingly with the endianess of the .out file

    Arguments: 
        elf_dataorder : ELFDATA2MSB = ELF values in big endian. Convert value to little endian
                        ELFDATA2LSB = ELF values in little endian. Return value as is.
        l             : Value to be converted

    Return Values:
        The converted value
*/
/* --------------------------------------------------------------------------------------------- */
unsigned int elf_fix_dword(unsigned char elf_dataorder, unsigned int l)
{
    if (elf_dataorder == ELFDATA2MSB)
    {
        l = ((l & 0x000000FF) << 24) | ((l & 0x0000FF00) <<  8) |
            ((l & 0x00FF0000) >>  8) | ((l & 0xFF000000) >> 24);
    }
    return l;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_fix_ddword
 
    Purpose: 
        Convert the input value (8 bytes) accordingly with the endianess of the .out file

    Arguments: 
        elf_dataorder : ELFDATA2MSB = ELF values in big endian. Convert value to little endian
                        ELFDATA2LSB = ELF values in little endian. Return value as is.
        l             : Value to be converted

    Return Values:
        The converted value
*/
/* --------------------------------------------------------------------------------------------- */
unsigned long long elf_fix_ddword(unsigned char elf_dataorder, unsigned long long l)
{
    if (elf_dataorder == ELFDATA2MSB)
    {
        l = ((l & 0x00000000000000FF) << 56) | ((l & 0x000000000000FF00) << 40) | ((l & 0x0000000000FF0000) << 24) | ((l & 0x00000000FF000000) <<  8) |
            ((l & 0x000000FF00000000) >>  8) | ((l & 0x0000FF0000000000) >> 24) | ((l & 0x00FF000000000000) >> 40) | ((l & 0xFF00000000000000) >> 56);
    }

    return l;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_init_ElfEnvironment
 
    Purpose: 
        Null initialise the elf environment structure.

    Arguments: 
        elfEnv : ELF information data

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void elf_init_ElfEnvironment(ElfEnvironment *elfEnv)
{
    elfEnv->elf_file = NULL;
    elfEnv->debug = NULL;

    memset(&elfEnv->elf_hdr, 0, sizeof(Elf32_Ehdr));

    elfEnv->elf_dataorder = 0;
    elfEnv->shtable = NULL;
    elfEnv->elf_sec_name_str_table = NULL;
    elfEnv->elf_symtab_str_table = NULL;
    elfEnv->dwarf_abbreviation_tables = NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_free_ElfEnvironment
 
    Purpose: 
        Free all memory allocated in the ElfEnvironment structure and close the FILE * pointers

    Arguments: 
        elfEnv : ELF information data

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void elf_free_ElfEnvironment(ElfEnvironment *elfEnv)
{
    /* Free section header table */
    free(elfEnv->shtable);
    elfEnv->shtable = NULL;

    /* Free section header string table */
    free(elfEnv->elf_sec_name_str_table);
    elfEnv->elf_sec_name_str_table = NULL;

    /* Free symbol string table */
    free(elfEnv->elf_symtab_str_table);
    elfEnv->elf_symtab_str_table = NULL;

    /* Free abbreviation tables */
    list_delete(elfEnv->dwarf_abbreviation_tables, dwarf_free_dwarf_abbreviation_tables_entry);
    elfEnv->dwarf_abbreviation_tables = NULL;

    /* Close files */
    elfEnv->elf_file = NULL;  /* File pointer must be closed by caller */
    if (elfEnv->debug)
    {
        fclose(elfEnv->debug);
        elfEnv->debug = NULL;
    }
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_read_ElfHeader
 
    Purpose: 
        Read and parse the ELF header data in the beginning of the .out file

    Functional Description:
        This information is the entry to all other information stored in the .out file
        The collected data is stored in ElfEnvironment.elf_hdr and ElfEnvironment.elf_dataorder

    Arguments: 
        elfEnv : ELF information data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char* elf_read_ElfHeader(ElfEnvironment *elfEnv)
{
    unsigned int lvalue = 0;
    unsigned char bvalue = 0;
    int i;

    /* Read magic number: EI_MAG0 - EI_MAG3 */
    /* Detect endianess but this will also be done using EI_DATA */
    READ_DWORD(lvalue);
    if (lvalue == 0x7f454c46)
    {
        /* Big endian format */
        elfEnv->elf_dataorder = ELFDATA2MSB;
    }
    else if (lvalue == 0x464c457f)
    {
        /* Little endian format */
        elfEnv->elf_dataorder = ELFDATA2LSB;
    }
    else
    {
        return "Bad ELF header";
    }

    /* Read EI_CLASS */
    /* Only 32 bit architectures are supported */
    READ_BYTE(elfEnv->elf_hdr.e_id_class);
    if (elfEnv->elf_hdr.e_id_class != ELFCLASS32)
    {
        return "Unsupported Class of ELF-file";
    }

    /* Read EI_DATA */
    /* Determines endianess of stored data */
    READ_BYTE(elfEnv->elf_hdr.e_id_data);
    switch (elfEnv->elf_hdr.e_id_data)
    {
    case ELFDATA2LSB:
        {
            /* Little endian format */
            elfEnv->elf_dataorder = ELFDATA2LSB;
            break;
        }
    case ELFDATA2MSB:
        {
            /* Big endian format */
            elfEnv->elf_dataorder = ELFDATA2MSB;
            break;
        }
    case ELFDATANONE:
    default:
        {
            /* Unsupported format */
            return "Unsupported Data ordering of ELF-file";
            break;
        }
    }

    /* Read EI_VERSION */
    READ_BYTE(elfEnv->elf_hdr.e_id_version);
    READ_BYTE(elfEnv->elf_hdr.e_id_osabi);
    READ_BYTE(elfEnv->elf_hdr.e_id_abiversion);

    /* Read EI_PAD bytes */
    for (i = 0; i < 7; i++)
    {
        READ_BYTE(bvalue);
    }

    /* Read e_type */
    /* Only executable and shared files supported */
    READ_WORD(elfEnv->elf_hdr.e_type);
    if (elfEnv->elf_hdr.e_type != ET_EXEC && elfEnv->elf_hdr.e_type != ET_DYN)
    {
        return "Unsupported file type";
    }

    /* Read e_machine */
    READ_WORD(elfEnv->elf_hdr.e_machine);

    /* Read e_version */
    READ_DWORD(elfEnv->elf_hdr.e_version);
    if (elfEnv->elf_hdr.e_version == EV_NONE)
    {
        return "Unsupported file version";
    }

    /* Read remaining fields of the ELF header */
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

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_dump_ElfHeader
 
    Purpose: 
        Dump the contents of the elf header (ElfEnvironment.elf_hdr) to a debug text file

    Arguments: 
        elfEnv : ELF information data

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void elf_dump_ElfHeader(ElfEnvironment *elfEnv)
{
    if (elfEnv->debug)
    {
        fprintf(elfEnv->debug, "ELF  header:\n");
        fprintf(elfEnv->debug, "=======================================================\n");
        fprintf(elfEnv->debug, "  e_ident[N]\n");
        fprintf(elfEnv->debug, "    elf_dataorder:    %10d\n",    elfEnv->elf_dataorder);
        fprintf(elfEnv->debug, "    e_id_class:       %10d\n",    elfEnv->elf_hdr.e_id_class);
        fprintf(elfEnv->debug, "    e_id_data:        %10d\n",    elfEnv->elf_hdr.e_id_data);
        fprintf(elfEnv->debug, "    e_id_version:     %10d\n",    elfEnv->elf_hdr.e_id_version);
        fprintf(elfEnv->debug, "    e_id_osabi:       %10d\n",    elfEnv->elf_hdr.e_id_osabi);
        fprintf(elfEnv->debug, "    e_id_abiversion:  %10d\n",    elfEnv->elf_hdr.e_id_abiversion);
        fprintf(elfEnv->debug, "  e_type:             %10d\n",    elfEnv->elf_hdr.e_type);
        fprintf(elfEnv->debug, "  e_machine:          %10d\n",    elfEnv->elf_hdr.e_machine);
        fprintf(elfEnv->debug, "  e_version:          %10d\n",    elfEnv->elf_hdr.e_version);
        fprintf(elfEnv->debug, "  e_entry:            0x%08X\n",  elfEnv->elf_hdr.e_entry);
        fprintf(elfEnv->debug, "  e_phoff:            %10d\n",    elfEnv->elf_hdr.e_phoff);
        fprintf(elfEnv->debug, "  e_shoff:            %10d\n",    elfEnv->elf_hdr.e_shoff);
        fprintf(elfEnv->debug, "  e_flags:            0x%08X\n",  elfEnv->elf_hdr.e_flags);
        fprintf(elfEnv->debug, "  e_ehsize:           %10d\n",    elfEnv->elf_hdr.e_ehsize);
        fprintf(elfEnv->debug, "  e_phentsize:        %10d\n",    elfEnv->elf_hdr.e_phentsize);
        fprintf(elfEnv->debug, "  e_phnum:            %10d\n",    elfEnv->elf_hdr.e_phnum);
        fprintf(elfEnv->debug, "  e_shentsize:        %10d\n",    elfEnv->elf_hdr.e_shentsize);
        fprintf(elfEnv->debug, "  e_shnum:            %10d\n",    elfEnv->elf_hdr.e_shnum);
        fprintf(elfEnv->debug, "  e_shstrndx:         %10d\n",    elfEnv->elf_hdr.e_shstrndx);
        fprintf(elfEnv->debug, "\n");
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_read_SectionHeader
 
    Purpose: 
        Read and parse the ELF section header.

    Arguments: 
        elfEnv  : ELF information data
        sec_hdr : The section header data is stored here

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *elf_read_SectionHeader(ElfEnvironment *elfEnv, Elf32_Shdr *sec_hdr)
{
    /* Read section head */
    READ_DWORD(sec_hdr->sh_name);
    READ_DWORD(sec_hdr->sh_type);
    READ_DWORD(sec_hdr->sh_flags);
    READ_DWORD(sec_hdr->sh_addr);
    READ_DWORD(sec_hdr->sh_offset);
    READ_DWORD(sec_hdr->sh_size);
    READ_DWORD(sec_hdr->sh_link);
    READ_DWORD(sec_hdr->sh_info);
    READ_DWORD(sec_hdr->sh_addralign);
    READ_DWORD(sec_hdr->sh_entsize);

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_dump_SectionHeader
 
    Purpose: 
        Dump the contents of the section header to a debug text file
        Note: sh_name is only printed out as text if the section name string table has been read
        and stored in ElfEnvironment.elf_sec_name_str_table[]. The index of this section is stored 
        in ElfEnvironment.elf_hdr.e_shstrndx.

    Arguments: 
        elfEnv  : ELF information data
        sec_hdr : Section header to be dumped

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void elf_dump_SectionHeader(ElfEnvironment *elfEnv, Elf32_Shdr *sec_hdr)
{
    if (elfEnv->debug)
    {
        fprintf(elfEnv->debug, "Section header:\n");
        fprintf(elfEnv->debug, "=======================================================\n");
        if (elfEnv->elf_sec_name_str_table)
        {
            fprintf(elfEnv->debug, "  sh_name:            %10d  %s\n", sec_hdr->sh_name, &elfEnv->elf_sec_name_str_table[sec_hdr->sh_name]);
        }
        else
        {
            fprintf(elfEnv->debug, "  sh_name:            %10d\n", sec_hdr->sh_name);
        }
        fprintf(elfEnv->debug, "  sh_type:            %10d\n",   sec_hdr->sh_type);
        fprintf(elfEnv->debug, "  sh_flags:           %10d\n",   sec_hdr->sh_flags);
        fprintf(elfEnv->debug, "  sh_addr:            0x%08X\n", sec_hdr->sh_addr);
        fprintf(elfEnv->debug, "  sh_offset:          0x%08X\n", sec_hdr->sh_offset);
        fprintf(elfEnv->debug, "  sh_size:            0x%08X\n", sec_hdr->sh_size);
        fprintf(elfEnv->debug, "  sh_link:            %10d\n",   sec_hdr->sh_link);
        fprintf(elfEnv->debug, "  sh_info:            %10d\n",   sec_hdr->sh_info);
        fprintf(elfEnv->debug, "  sh_addralign:       %10d\n",   sec_hdr->sh_addralign);
        fprintf(elfEnv->debug, "  sh_entsize:         %10d\n",   sec_hdr->sh_entsize);
        fprintf(elfEnv->debug, "\n");
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_read_SectionHeaderTable
 
    Purpose: 
        Read and parse the section header table

    Functional Description:
        This reads the section header table which is stored as an array of section headers.
        The function allocates memory to store this section header table and returns a pointer
        to the data.

        The offset in the .out file for the section header table is determined by ElfEnvironment.elf_hdr.e_shoff.
        The number of section headers in the array is determined by ElfEnvironment.elf_hdr.e_shnum.
        The size of each section header is determined by ElfEnvironment.elf_hdr.e_shentsize.

    Arguments: 
        elfEnv  : ELF information data
        shtable : The function returns a pointer to the section header table. Caller must free memory.

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char* elf_read_SectionHeaderTable(ElfEnvironment *elfEnv, Elf32_Shdr **shtable)
{
    int i;
    const char *result = NULL;

    /* Check that a section header is present */
    if (elfEnv->elf_hdr.e_shoff == 0)
    {
        return "No section header table";
    }

    /* Allocate space for section header table */
    *shtable = (Elf32_Shdr *)malloc(elfEnv->elf_hdr.e_shentsize * elfEnv->elf_hdr.e_shnum);
    if (*shtable == NULL)
    {
        return "Not enough memory";
    }

    /* Look-up start of section header table */
    fseek(elfEnv->elf_file, elfEnv->elf_hdr.e_shoff, SEEK_SET);

    /* Read section header table */
    for(i = 0; result == NULL && i < elfEnv->elf_hdr.e_shnum; i++)
    {
        /* Read one section header entry */
        result = elf_read_SectionHeader(elfEnv, &((*shtable)[i]));
    }

    return result;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_dump_SectionHeaderTable
 
    Purpose: 
        Dump the contents of the section header table ElfEnvironment.shtable[] to a debug text file

    Arguments: 
        elfEnv  : ELF information data

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void elf_dump_SectionHeaderTable(ElfEnvironment *elfEnv)
{
    int i;

    if (elfEnv->debug)
    {
        /* Loop through section header table and dump each section header entry */
        for(i = 0; i < elfEnv->elf_hdr.e_shnum; i++)
        {
            /* Dump section header */
            fprintf(elfEnv->debug, "%d - ", i);
            elf_dump_SectionHeader(elfEnv, &(elfEnv->shtable[i]));
        }
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_read_section_data
 
    Purpose: 
        Read the data contained in an ELF section

    Arguments: 
        elfEnv  : ELF information data
        shdr    : Section header to be read

    Return Values:
        Pointer to data read. NULL in case of failure
*/
/* --------------------------------------------------------------------------------------------- */
void *elf_read_section_data(ElfEnvironment *elfEnv, Elf32_Shdr *shdr)
{
    /* Allocate sufficient space for section data */
    unsigned char *buffer = (unsigned char *)malloc(shdr->sh_size);

    if (buffer)
    {
        size_t nread;

        /* Read section data */
        fseek(elfEnv->elf_file, shdr->sh_offset, SEEK_SET);
        nread = fread(buffer, shdr->sh_size, 1, elfEnv->elf_file);
        
        if (nread != 1)
        {
            /* Error */
            free(buffer);
            return NULL;
        }
    }

    return buffer;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_dump_section_data
 
    Purpose: 
        Dump the contents of an arbitary section to a debug text file
        Data is dumped as lines of hex values and ASCII characters

    Arguments: 
        elfEnv  : ELF information data
        header  : Text string to write out first before any data is printed
        n       : Size of data section
        data    : Data section

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void elf_dump_section_data(ElfEnvironment *elfEnv, const char *header, size_t n, void *data)
{
    if (elfEnv->debug)
    {
        size_t i,j = 0;
        
        fprintf(elfEnv->debug, "%s\n", header);
        for (i = 0; i < n; i += 16)
        {
            /* Print offset */
            fprintf(elfEnv->debug, "%08X  ", i);

            /* Print hex dump */
            for (j = 0; i+j < n && j < 16; j++)
            {
                fprintf(elfEnv->debug, "%02X ", ((unsigned char *)data)[i+j]);
            }

            /* Print space between hex and ascii dump */
            while (j++ < 16)
            {
                fprintf(elfEnv->debug, "   ");
            }
            fprintf(elfEnv->debug, "   ");

            /* Print ascii dump */
            for (j = 0; i+j < n && j < 16; j++)
            {
                unsigned char c = ((unsigned char *)data)[i+j];
                fprintf(elfEnv->debug, "%c", (32 <= c && c <= 126 ? c : '.'));
            }

            fprintf(elfEnv->debug, "\n");
        }
        fprintf(elfEnv->debug, "\n");
    }
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_read_SectionHeaderStringTable
 
    Purpose: 
        Read the section name string table.

    Functional Description:
        Reads the section name string table which stores the names of the section headers.
        The section data is stored in ElfEnvironment.elf_sec_name_str_table.

    Arguments: 
        elfEnv  : ELF information data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *elf_read_SectionHeaderStringTable(ElfEnvironment *elfEnv)
{
    /* Check that the section header string table is defined */
    if (elfEnv->elf_hdr.e_shstrndx == SHN_UNDEF)
    {
        /* No section header string table present */
        return "No section header string table present";
    }

    /* Check that type of section is SHT_STRTAB */
    if (elfEnv->shtable[elfEnv->elf_hdr.e_shstrndx].sh_type != SHT_STRTAB)
    {
        /* Error */
        return "Section header string table do not have correct type";
    }

    /* Given e_shstrndx look-up the section header entry and use that to read the section data */
    elfEnv->elf_sec_name_str_table = (char *)elf_read_section_data(elfEnv, &(elfEnv->shtable[elfEnv->elf_hdr.e_shstrndx]));
    if (elfEnv->elf_sec_name_str_table == NULL)
    {
        /* Error */
        return "Error reading section header string table.";
    }

    /* Dump contents of section header string table */
    /* elf_dump_section_data(elfEnv, "Section header string table:", 
                          elfEnv->shtable[elfEnv->elf_hdr.e_shstrndx].sh_size, 
                          elfEnv->elf_sec_name_str_table); */
    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_read_SymbolStringTable
 
    Purpose: 
        Read the symbol string table '.strtab'.

    Functional Description:
        Reads the symbol string table which stores the names used in the symbol table '.symtab'.
        The section data is stored in ElfEnvironment.elf_symtab_table.

    Arguments: 
        elfEnv  : ELF information data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *elf_read_SymbolStringTable(ElfEnvironment *elfEnv)
{
    int i;

    if (elfEnv->shtable == NULL)
    {
        /* Error */
        return "Section header table has not been read";
    }

    /* Loop up the section header entry for .strtab */
    for (i = 0; i < elfEnv->elf_hdr.e_shnum; i++)
    {
        /* Look up section header name */
        const char *sh_name = &elfEnv->elf_sec_name_str_table[elfEnv->shtable[i].sh_name];

        /* Is the section the correct one? */
        if (strcmp(sh_name, ".strtab") == 0)
        {
            Elf32_Shdr *sec_hdr = &elfEnv->shtable[i];

            /* .strtab found. Read section data */
            elfEnv->elf_symtab_str_table = (char *)elf_read_section_data(elfEnv, sec_hdr);
            if (elfEnv->elf_symtab_str_table == 0)
            {
                /* Error */
                return "Error reading .strtab section";
            }

            /* Dump contents of symbol string table */
            /* elf_dump_section_data(elfEnv, "Symbol string table:", sec_hdr->sh_size, elfEnv->elf_symtab_str_table); */
        }
    }

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_read_symtab
 
    Purpose: 
        Read in the .symtab elf section and calls elf_parse_symtab() to parse the contents.
        See description of elf_parse_symtab() for more info.
 
    Arguments: 
        elfEnv         : ELF data from .out file
        user_func      : User supplied function that will be called for each collected Symbol Table Entry
        user_func_data : User supplied data structure. Can be used to store the extracted data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem
*/
/* --------------------------------------------------------------------------------------------- */
const char *elf_read_symtab(ElfEnvironment *elfEnv, const char *(*user_func)(ElfEnvironment *, Elf32_Sym *, void *), void *user_func_data)
{
    int i;
    const char *result = NULL;

    if (elfEnv->shtable == NULL)
    {
        /* Error */
        return "Section header table has not been read";
    }

    /* Loop up the section header entry for .symtab */
    for (i = 0; i < elfEnv->elf_hdr.e_shnum; i++)
    {
        /* Look up section header name */
        const char *sh_name = &elfEnv->elf_sec_name_str_table[elfEnv->shtable[i].sh_name];

        /* Is the section the correct one? */
        if (strcmp(sh_name, ".symtab") == 0)
        {
            Elf32_Shdr *sec_hdr = &elfEnv->shtable[i];

            /* .symtab found. Read section data */
            unsigned char *symtab = (unsigned char *)elf_read_section_data(elfEnv, sec_hdr);
            if (symtab == 0)
            {
                /* Error */
                return "Error reading .symtab section";
            }

            /* Dump data */
            /* elf_dump_section_data(elfEnv, ".symtab:", sec_hdr->sh_size, symtab); */

            /* Parse data */
            result = elf_parse_symtab(elfEnv, sec_hdr->sh_size, symtab, sec_hdr->sh_entsize, user_func, user_func_data);

            /* Clean up */
            free(symtab);
            break;
        }
    }

    return result;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_parse_symtab
 
    Purpose: 
        Parse the content of the .symtab elf section.

    Functional Description:
        The function loops through the whole .symtab section and parses all the Symbol Table Entries.
        (See ELF documentation for further information)

        A user function is called every time an symbol table entry been collected.
        The user function can then extract the needed information and store it in a user data structure 
        'user_func_data'.

    Arguments: 
        elfEnv            : ELF data from .out file
        n                 : Size of .symtab elf section
        data              : Data contents of the .symtab elf section
        symtab_entry_size : Size of each symbol table entry. Can be retrieved from section header field 'sh_entsize'
        user_func         : User supplied function that will be called for each symbol table entry
                            Arguments:
                               ElfEnvironment *       : ELF data from .out file
                               Elf32_Sym              : Symbol Table Entry
                               void *                 : User supplied data structure. Can be used to store the extracted data
                            Return Values:
                               NULL if all is ok otherwise a text string describing the problem
        user_func_data    : User supplied data structure. Can be used to store the extracted data

    Return Values:
        NULL if all is ok otherwise a text string describing the problem

    Example on a user function:

        const char *extract_variable_info(ElfEnvironment *elfEnv, Elf32_Sym *symtab_entry, void *data)
        {
            pmd_symboldata *user_data = (pmd_symboldata *)data;

            / * Store data * /
            user_data->name[user_data->cnt]    = symtab_entry->st_name;
            user_data->value[user_data->cnt++] = symtab_entry->st_value;

            return NULL;
        }
*/
/* --------------------------------------------------------------------------------------------- */
const char *elf_parse_symtab(ElfEnvironment *elfEnv, size_t n, void *data, size_t symtab_entry_size, const char *(*user_func)(ElfEnvironment *, Elf32_Sym *, void *), void *user_func_data)
{
    Elf32_Word cnt;
    Elf32_Sym symtab_entry;
    const char *result = NULL;
    unsigned char *offset = (unsigned char *)data;

    /* Loop through the number of symbol table entries in .symtab */
    for (cnt = 0; cnt < n / symtab_entry_size; ++cnt)
    {
        /* Read symbol table entry */
        elf_parse_symtab_entry(elfEnv, &symtab_entry, &offset);

        /* Dump contents of symbol table entry */
        elf_dump_symbol_table_entry(elfEnv, &symtab_entry);

        /* Call user function with collected data */
        result = user_func(elfEnv, &symtab_entry, user_func_data);
        if (result) 
        {
            /* Error */
            return result;
        }

        /* If entities are larger than the structure, read paddings */
        if (symtab_entry_size > sizeof(Elf32_Sym))
        {
            offset += symtab_entry_size - sizeof(Elf32_Sym);
        }
    }

    return NULL;
}

/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_parse_symtab_entry
 
    Purpose: 
        The function will parse a single Symbol Table Entry and return the data. 
 
    Arguments: 
        elfEnv       : ELF data from .out file
        symtab_entry : Pointer to structure where the parsed data will be stored
        offset       : Pointer to where to start reading the symbol table entry. 
                       After call offset points to the first byte after the symbol table entry.

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void elf_parse_symtab_entry(ElfEnvironment *elfEnv, Elf32_Sym *symtab_entry, unsigned char **offset)
{
    /* Read a symbol table entry record */
    symtab_entry->st_name  = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));   *offset += 4;
    symtab_entry->st_value = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));   *offset += 4;
    symtab_entry->st_size  = elf_fix_dword(elfEnv->elf_dataorder, *((unsigned int *)*offset));   *offset += 4;
    symtab_entry->st_info  = **offset;                                                           *offset += 1;
    symtab_entry->st_other = **offset;                                                           *offset += 1;
    symtab_entry->st_shndx = elf_fix_word(elfEnv->elf_dataorder, *((unsigned short *)*offset));  *offset += 2;
}


/* --------------------------------------------------------------------------------------------- */
/*  Name: elf_dump_symbol_table_entry
 
    Purpose: 
        Dump the content of a symbol table entry to a debug text file 
 
    Arguments: 
        elfEnv       : ELF data from .out file
        symtab_entry : Pointer to structure containing symbol table entry

    Return Values:
        -
*/
/* --------------------------------------------------------------------------------------------- */
void elf_dump_symbol_table_entry(ElfEnvironment *elfEnv, Elf32_Sym *symtab_entry)
{
    if (elfEnv->debug && symtab_entry)
    {
        fprintf(elfEnv->debug, "Symbol table entry:\n");
        fprintf(elfEnv->debug, "-------------------\n");
        if (elfEnv->elf_symtab_str_table)
        {
            fprintf(elfEnv->debug, "  Name:        %u - %s\n", symtab_entry->st_name, &elfEnv->elf_symtab_str_table[symtab_entry->st_name]);
        }
        else
        {
            fprintf(elfEnv->debug, "  Name:        %u\n", symtab_entry->st_name, &elfEnv->elf_symtab_str_table[symtab_entry->st_name]);
        }
        fprintf(elfEnv->debug, "  Value:       %08X\n", symtab_entry->st_value);
        fprintf(elfEnv->debug, "  Size:        %u\n",   symtab_entry->st_size);
        fprintf(elfEnv->debug, "  Info:        %02X\n", symtab_entry->st_info);
        fprintf(elfEnv->debug, "  Other:       %u\n",   symtab_entry->st_other);
        fprintf(elfEnv->debug, "  Sec hdr idx: %u\n",   symtab_entry->st_shndx);
        fprintf(elfEnv->debug, "\n");
    }
}

