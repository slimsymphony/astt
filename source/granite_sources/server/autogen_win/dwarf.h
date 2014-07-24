/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                dwarf.h
                --------------
                SW Include






Project:          autogen

%name:             dwarf.h %
%version:          1 %
%instance:         co1tss_1 %
%derived_by:       nosterga %
%date_modified:    Tue Feb 15 18:07:22 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains DWARF constant definitions and structures used to store DWARF data

    Dwarf format described in

            DWARF Debugging Information Format 
            Version 3

            http://dwarfstd.org/

*/

#ifndef DWARF_H
#define DWARF_H

/* Attribute form encodings */
#define DW_FORM_addr      0x01
#define DW_FORM_block2    0x03
#define DW_FORM_block4    0x04
#define DW_FORM_data2     0x05
#define DW_FORM_data4     0x06
#define DW_FORM_data8     0x07
#define DW_FORM_string    0x08
#define DW_FORM_block     0x09
#define DW_FORM_block1    0x0a
#define DW_FORM_data1     0x0b
#define DW_FORM_flag      0x0c
#define DW_FORM_sdata     0x0d
#define DW_FORM_strp      0x0e
#define DW_FORM_udata     0x0f
#define DW_FORM_ref_addr  0x10
#define DW_FORM_ref1      0x11
#define DW_FORM_ref2      0x12
#define DW_FORM_ref4      0x13
#define DW_FORM_ref8      0x14
#define DW_FORM_ref_udata 0x15
#define DW_FORM_indirect  0x16

/* Line number standard opcode encodings */
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

#endif /* DWARF_H */

