/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                elf.h
                --------------
                SW Include






Project:          autogen

%name:             elf.h %
%version:          1 %
%instance:         co1tss_1 %
%derived_by:       nosterga %
%date_modified:    Tue Feb 15 18:07:50 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains ELF constant definitions and structures used to store ELF data

    Elf format described in

            Tool Interface Standard (TIS)
            Executable and Linking Format (ELF)
            Specification
            Version 1.2

*/

#ifndef ELF_H
#define ELF_H

typedef unsigned short Elf32_Half;
typedef unsigned int   Elf32_Word;
typedef int            Elf32_Sword;
typedef unsigned int   Elf32_Addr;
typedef unsigned int   Elf32_Off;

/* Special Section Indexes */
#define SHN_UNDEF          0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC    0xff00
#define SHN_HIPROC    0xff1f
#define SHN_LOOS      0xff20
#define SHN_HIOS      0xff3f
#define SHN_ABS       0xfff1
#define SHN_COMMON    0xfff2
#define SHN_XINDEX    0xffff
#define SHN_HIRESERVE 0xffff

/* Elf header */
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
#define ET_NONE 0        /* No file type */
#define ET_REL 1         /* Relocatable file */
#define ET_EXEC 2        /* Executable file */
#define ET_DYN 3         /* Shared object file */
#define ET_CORE 4        /* Core file */
#define ET_LOOS 0xfe00   /* Operating system-specific */
#define ET_HIOS 0xfeff   /* Operating system-specific */
#define ET_LOPROC 0xff00 /* Processor-specific */
#define ET_HIPROC 0xffff /* Processor-specific */

/* Elf32_Ehdr.e_id_class values */
#define ELFCLASSNONE 0   /* Invalid class */
#define ELFCLASS32 1     /* 32-bit objects */
#define ELFCLASS64 2     /* 64-bit objects */

/* Elf32_Ehdr.e_id_data values */
#define ELFDATANONE 0    /* Invalid data encoding */
#define ELFDATA2LSB 1    /* Little endian */
#define ELFDATA2MSB 2    /* Big endian */

/* Elf32_Ehdr.e_version values */
#define EV_NONE 0        /* Invalid version */
#define EV_CURRENT 1     /* Current version */

/* Elf section header */
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
#define SHT_NULL                  0
#define SHT_PROGBITS              1
#define SHT_SYMTAB                2
#define SHT_STRTAB                3
#define SHT_RELA                  4
#define SHT_HASH                  5
#define SHT_DYNAMIC               6
#define SHT_NOTE                  7
#define SHT_NOBITS                8
#define SHT_REL                   9
#define SHT_SHLIB                10
#define SHT_DYNSYM               11
#define SHT_INIT_ARRAY           14
#define SHT_FINI_ARRAY           15
#define SHT_PREINIT_ARRAY        16
#define SHT_GROUP                17
#define SHT_SYMTAB_SHNDX         18
#define SHT_LOOS         0x60000000
#define SHT_HIOS         0x6fffffff
#define SHT_LOPROC       0x70000000
#define SHT_HIPROC       0x7fffffff 
#define SHT_LOUSER       0x80000000
#define SHT_HIUSER       0xffffffff

/* Section attibute flags Elf32_Shdr.sh_flags */
#define SHF_WRITE            0x1 
#define SHF_ALLOC            0x2 
#define SHF_EXECINSTR        0x4 
#define SHF_MERGE            0x10 
#define SHF_STRINGS          0x20 
#define SHF_INFO_LINK        0x40 
#define SHF_LINK_ORDER       0x80 
#define SHF_OS_NONCONFORMING 0x100 
#define SHF_GROUP            0x200 
#define SHF_TLS              0x400 
#define SHF_MASKOS           0x0ff00000 
#define SHF_MASKPROC         0xf0000000 

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
#define STT_NOTYPE 0 
#define STT_OBJECT 1 
#define STT_FUNC 2 
#define STT_SECTION 3 
#define STT_FILE 4 
#define STT_COMMON 5 
#define STT_TLS 6 
#define STT_LOOS 10 
#define STT_HIOS 12 
#define STT_LOPROC 13 
#define STT_HIPROC 15 

#define ELF32_ST_TYPE(i)   ((i)&0xf)

/* Symbol bindings (MSN of Elf32_Sym.st_info) */
#define STB_LOCAL 0 
#define STB_GLOBAL 1 
#define STB_WEAK 2 
#define STB_LOPROC 13 
#define STB_HIPROC 15 

#define ELF32_ST_BIND(i)   ((i)>>4)

#endif /* ELF_H */
