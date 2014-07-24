/*
-------------------------------------------------------------------------
NOKIA
DCT/Adaptation ISA SW













		GLOBAL TYPE DEFINITIONS
		------------------------------------------------------
		SW Include Document





Part:		SW_ARCH:GENERAL_IF_HEADERS.BASE

Item:		SW_ARCH:TYPE_DEF.BASE-H

Workset:        SW_ARCH:WS_SW_ARCH_43UPGRADE

Filename:	type_def.h

Document code:	-

Copyright (c) Nokia Corporation




Change History:

VERSION       43     NON-DRAFT     21-Apr-2008   Jarmo Vaarala
REASON      : 
REFERENCE   : Mail review with Antti Jauhiainen and Stig Aagaard
DESCRIPTION : MSVS (G_MS_VISUAL_C) related update. Unknown type 
              definitions.

VERSION       42     NON-DRAFT     23-Nov-2007   Jarmo Vaarala
REASON      : 
REFERENCE   : Mail review with Antti Jauhiainen
DESCRIPTION : Update

VERSION       41     NON-DRAFT     19-Feb-2007   Milla Ahola
REASON      : PCP error
REFERENCE   : SB07021456840
DESCRIPTION : Incorrect type definitions for G_LINUX_C

VERSION       40     NON-DRAFT     10-Sep-2004   Janne Savolainen
REASON      : 
REFERENCE   : Mail review with Antti Jauhiainen
DESCRIPTION : Modifications:
              - Enabled uint64, int64 and ddword in SUN and HPUX

VERSION       39     NON-DRAFT     10-Aug-2004   Janne Savolainen
REASON      : 
REFERENCE   : Mail review with Antti Jauhiainen
DESCRIPTION : Modifications:
              - changes to G_HPUX_C, G_SUN_C and G_LINUX_C

VERSION       38     NON-DRAFT     21-May-2004   Janne Savolainen
REASON      : 
REFERENCE   : Mail review with Antti Jauhiainen
DESCRIPTION : Modifications:
              - Add NATIVE_64BIT_INTEGERS definition

VERSION       37     NON-DRAFT     08-Mar-2004   Janne Savolainen
REASON      : 
REFERENCE   : PCP Error: LS04030340991
DESCRIPTION : Modifications:
              - Remove control characters

VERSION       36     NON-DRAFT     26-Sep-2003   Janne Savolainen
REASON      : 
REFERENCE   : PCP Error: UH03091744115
DESCRIPTION : Modifications:
              - Changes for E-Sim

VERSION       35     NON-DRAFT     11-Sep-2003   Janne Savolainen
REASON      : 
REFERENCE   :
DESCRIPTION : Modifications:
              - Added PRODUCT_COMPILER_TYPE G_LINUX_C

VERSION       34     NON-DRAFT     04-Sep-2003   Janne Savolainen
REASON      : 
REFERENCE   : Email from Antti Jauhiainen
DESCRIPTION : Modifications:
              - Added type definition utf8_char

VERSION       33     NON-DRAFT     11-Aug-2003   Janne Savolainen
REASON      : 
REFERENCE   : 
DESCRIPTION : Modifications:
              - Removed #define INLINE

VERSION       32     NON-DRAFT     06-Aug-2003   Janne Savolainen
REASON      : 
REFERENCE   : Email from Antti Jauhiainen
DESCRIPTION : Modifications:
              - 64 bit type definitions added for Visual C

VERSION       31     NON-DRAFT     11-Apr-2003   Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ03041143696.
DESCRIPTION : Modifications:
              - Added definition INLINE (used so far only with NORCROFT ARM
                compiler)
              
VERSION       30     NON-DRAFT     04-Apr-2003   Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ03040436366.
DESCRIPTION : Modifications:
              - Added type definition ucs2_char (moved from ui_type.h)
              
VERSION       29     NON-DRAFT     22-Nov-2000   Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ00112053824.
DESCRIPTION : Modifications:
              - Missing '=' added
              
VERSION       28     NON-DRAFT     20-Nov-2000   Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ00112053824.
DESCRIPTION : Modifications:
              - Definition for 'register' was missing from definitions
              of G_KEIL_C167CR_C.
              
VERSION       27     NON-DRAFT     20-Nov-2000   Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ00112053824.
DESCRIPTION : Modifications:
              - type definitions added for compilers G_TI_LEAD3_C
                and G_KEIL_C167CR_C.
              
VERSION       26     NON-DRAFT     21-Dec-99     Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ99122136567.
DESCRIPTION : Modifications:
              - type definitions added for compiler G_SUN_C.
              - reserved keywords moved to end of file.
              - type definition comments moved to beginning of file
              
VERSION       25     NON-DRAFT     08-Oct-99     Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ99100843362.
DESCRIPTION : Modifications:
              - type definitions added for compiler G_IAR_H8_H8S
              - endianess checking corrected for TI ARM compiler:
                V2.0 uses __big_endian__ instead of _TMS470_BIG
              
VERSION       24     NON-DRAFT     17-Aug-99     Antti Jauhiainen    
REASON      : Correction.
REFERENCE   : SWAM ADB inspection minutes AJ99081735515.
DESCRIPTION : Modifications:
              - bitf changed to be unsigned int instead of unsigned
                short int with MS Visual C.
              - int32 range comment corrected.
              - (Non ANSI C) uint64, int64 and ddword types added
                for Norcroft ARM C compiler users (usage shall be
                avoided with any code that may be ported for any 
                other compiler).
              
VERSION       23     NON-DRAFT     08-Feb-99     Antti Jauhiainen    
REASON      : Addition.
REFERENCE   : SWAM ADB inspection minutes AJ99020858626.
DESCRIPTION : Modifications:
              - New compiler type G_NORCROFT_ARM_C definitions added.
              
VERSION       22     NON-DRAFT     21-Jan-99     Antti Jauhiainen    
REASON      : Addition.
REFERENCE   : SWAM ADB inspection minutes AJ99012143786.
DESCRIPTION : Modifications:
              - New compiler type G_KEIL_8051_C definitions added.
              - New type bit added (KEIL 8051 C defines this itself).
              - Old CMS version history removed.
              
VERSION       21     NON-DRAFT     24-Aug-98     Antti Jauhiainen    
REASON      : Bug fix.
REFERENCE   : SWAM ADB inspection minutes AJ98082439529.
DESCRIPTION : bitf changed to 'unsigned int' with HP/UX.
              
VERSION       20     NON-DRAFT     28-Jan-98     Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ98012879098.
DESCRIPTION : Addition:
              - G_SH7K_GH_C and G_SH7K_HIT_C type definitions
              
VERSION       19     NON-DRAFT     15-Oct-97     Antti Jauhiainen    
REASON      : Modification.
REFERENCE   : SWAM ADB inspection minutes AJ97101580963.
DESCRIPTION : Addition:
              - G_GCC_PE_ARM_C type definitions
              
VERSION       18     NON-DRAFT     10-Jun-97     Antti Jauhiainen    
REASON      : Bug fix.
REFERENCE   : SWAM ADB inspection minutes AJ97061054961.
DESCRIPTION : Correction:
              - #if _TMS470_LITTLE == 0 changed to #ifdef _TMS470_BIG
              
VERSION       17     NON-DRAFT     25-Apr-97     Antti Jauhiainen    
REASON      : Improvement.
REFERENCE   : SWAM ADB inspection minutes AJ97042555978.
DESCRIPTION : Additions:
              - char16 type added for wide characters
              - BIG_ENDIAN_TYPE and LITTLE_ENDIAN_TYPE definitions added
              - G_MS_VISUAL_C compiler type added.
              
VERSION       16     NON-DRAFT     15-Feb-96     Jorma Virkkunen    
REASON      : Improvement.
REFERENCE   : IF_SPEC impl 17.
DESCRIPTION : Definitions for NEC processor removed.

VERSION       15     DRAFT         14-Feb-96     Jorma Virkkunen    
REASON      : Moved to PCMS.
REFERENCE   : IF_SPEC impl 16.
DESCRIPTION : Copied as such from SW_COMPONENTS_CMS. Cover page updated.
 ---------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*      Type definitions                                                    */
/*      ================                                                    */
/*      Following types are supported with all compilers                    */
/*        Char  Ascii character (signed or unsigned depending on compiler)  */
/*        Char16: 0 - 65535                                                 */
/*        Ucs2_char: 0 - 65535                                              */
/*        utf8_char:  up to 4 byte UTF-8 format character (www.unicode.org) */
/*        Bool8: FALSE, TRUE                                                */
/*        Bool16:FALSE, TRUE                                                */
/*        Byte:  0 - FFH                                                    */
/*        Word:  0 - FFFFH                                                  */
/*        Dword: 0 - FFFFFFFFH                                              */
/*        Uint8  0 ... 255                                                  */
/*        Uint16:0 ... 65535                                                */
/*        Uint32:0 ... 4294967295                                           */
/*        Int8:  -128 ... +127                                              */
/*        Int16: -32768 ... +32767                                          */
/*        Int32: -2147483648 ... 2147483647                                 */
/*        Bits8: 0 - FFH                                                    */
/*        Bits16:0 - FFFFH                                                  */
/*        Bits32:0 - FFFFFFFFH                                              */
/*        Bit field: 0 - FFFFH                                              */
/*                                                                          */
/*      Following NON-ANSI types are supported with some compilers:         */
/*        Uint64:0 ... 18446744073709551615                  Norcroft ARM C */
/*        Int64: -9223372036854775808 ...9223372036854775807 Norcroft ARM C */
/*        Ddword:0 ... 18446744073709551615                  Norcroft ARM C */
/*        Bit:   0 ... 1                                     KEIL 8051      */
/*      For portability reasons, recommendation is NOT to use these types.  */
/*                                                                          */
/*      For each compiler, there is a definition LITTLE_ENDIAN_TYPE or      */
/*      BIG_ENDIAN_TYPE, depending on the processor endianess               */
/*                                                                          */
/*      For each compiler supporting 64 bit variables, there is a           */
/*	definition NATIVE_64BIT_INTEGERS.                                   */
/*                                                                          */
/*      After the type definitions, there are dummy definitions for keywords*/
/*      that are reserved with some compilers                               */
/*--------------------------------------------------------------------------*/

#ifndef TYPE_DEF_H
#define TYPE_DEF_H

#if PRODUCT_COMPILER_TYPE == G_VAX_C

/*typedef        char           char; */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef          char           int8;
typedef short    int            int16;
typedef long     int            int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned short int      bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;   */
/* typedef signed   long long   int64;    */
/* typedef unsigned long long   ddword;   */
typedef unsigned char           bit;

#define LITTLE_ENDIAN_TYPE                      /*  Little endian processor */

#endif




#if PRODUCT_COMPILER_TYPE == G_IBM_C || \
    PRODUCT_COMPILER_TYPE == G_BORLAND_C

/*typedef        char           char;   */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef signed   short int      int16;
typedef signed   long int       int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64; */
/* typedef signed   long long   int64;  */
/* typedef unsigned long long   ddword; */
typedef unsigned char           bit;

#define LITTLE_ENDIAN_TYPE                      /*  Little endian processor */

#endif




#if PRODUCT_COMPILER_TYPE == G_IAR_H8_500 || \
    PRODUCT_COMPILER_TYPE == G_IAR_H8_300H

/*typedef        char           char;    */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef short    int            int16;
typedef long     int            int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;  */
/* typedef signed   long long   int64;   */
/* typedef unsigned long long   ddword;  */
typedef unsigned char           bit;

#define BIG_ENDIAN_TYPE                         /*  Big endian processor    */

#endif




#if PRODUCT_COMPILER_TYPE==G_IAR_H8_H8S

/*typedef        char           char;    */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef short    int            int16;
typedef long     int            int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;   */
/* typedef signed   long long   int64;    */
/* typedef unsigned long long   ddword;   */
typedef unsigned char           bit;

#define BIG_ENDIAN_TYPE                         /*  Big endian processor    */

#endif




#if PRODUCT_COMPILER_TYPE == G_I86_C

/*typedef        char           char;     */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef short    int            int16;
typedef long     int            int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;    */
/* typedef signed   long long   int64;     */
/* typedef unsigned long long   ddword;    */
typedef unsigned char           bit;

#define LITTLE_ENDIAN_TYPE                      /*  Little endian processor */

#endif




#if PRODUCT_COMPILER_TYPE == G_HPUX_C || \
    PRODUCT_COMPILER_TYPE == G_SUN_C

/*typedef        char           char;      */ 
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef signed   short int      int16;
typedef signed   long int       int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
typedef unsigned long long      uint64;
typedef signed   long long      int64;
typedef unsigned long long      ddword;
typedef unsigned char           bit;

#define BIG_ENDIAN_TYPE                         /*  Big endian processor    */

#endif


#if PRODUCT_COMPILER_TYPE == G_LINUX_C

/*typedef        char           char;      */ 
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned int            dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned int            uint32;
typedef signed   char           int8;
typedef signed   short int      int16;
typedef signed   int            int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned int            bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
typedef unsigned long long   uint64;
typedef signed   long long   int64;
typedef unsigned long long   ddword;
typedef unsigned char           bit;

#define NATIVE_64BIT_INTEGERS

#define LITTLE_ENDIAN_TYPE                      /*  Little endian processor */

#endif




#if PRODUCT_COMPILER_TYPE == G_MS_VISUAL_C

/*typedef        char           char;      */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef signed   short int      int16;
typedef signed   long int       int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
typedef unsigned __int64        uint64;
typedef signed   __int64        int64;
typedef unsigned __int64        ddword;
typedef unsigned char           bit;

#define LITTLE_ENDIAN_TYPE                      /*  Little endian processor */

#define NATIVE_64BIT_INTEGERS

#endif




#if PRODUCT_COMPILER_TYPE==G_TI_THUMB_C || \
    PRODUCT_COMPILER_TYPE==G_GCC_PE_ARM_C

/*typedef        char           char;      */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef signed   short int      int16;
typedef signed   long int       int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;    */
/* typedef signed   long long   int64;     */
/* typedef unsigned long long   ddword;    */
typedef unsigned char           bit;

#if defined(_TMS470_BIG) || defined(_GCC_PE_ARM_BIG) || defined(__big_endian__)
#define BIG_ENDIAN_TYPE                         /*  Big endian processor    */
#else
#define LITTLE_ENDIAN_TYPE                      /*  Little endian processor */
#endif

#endif




#if PRODUCT_COMPILER_TYPE==G_NORCROFT_ARM_C

/*typedef        char           char;      */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef signed   short int      int16;
typedef signed   long int       int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
typedef unsigned long long      uint64;
typedef signed   long long      int64;
typedef unsigned long long      ddword;
typedef unsigned char           bit;

#if defined(__BIG_ENDIAN)
#define BIG_ENDIAN_TYPE                         /*  Big endian processor    */
#else
#define LITTLE_ENDIAN_TYPE                      /*  Little endian processor */
#endif

#define NATIVE_64BIT_INTEGERS

#endif




#if PRODUCT_COMPILER_TYPE == G_SH7K_GH_C

/*typedef        char           char;      */
typedef unsigned short          char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short          bool16;
typedef unsigned char           byte;
typedef unsigned short    	word;
typedef unsigned int            dword;
typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef char           		int8;
typedef short                   int16;
typedef int                     int32;
typedef unsigned char           bits8;
typedef unsigned short          bits16;
typedef unsigned int            bits32;
typedef unsigned short          bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;    */
/* typedef signed   long long   int64;     */
/* typedef unsigned long long   ddword;    */
typedef unsigned char           bit;

#define BIG_ENDIAN_TYPE                         /*  Big endian processor    */

#endif




#if PRODUCT_COMPILER_TYPE == G_SH7K_HIT_C

/*typedef        char           char;      */
typedef unsigned short          char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short          bool16;
typedef unsigned char           byte;
typedef unsigned short    	word;
typedef unsigned int            dword;
typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef signed   char           int8;
typedef short                   int16;
typedef long                    int32;
typedef unsigned char           bits8;
typedef unsigned short          bits16;
typedef unsigned int            bits32;
typedef unsigned short          bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;    */
/* typedef signed   long long   int64;     */
/* typedef unsigned long long   ddword;    */
typedef unsigned char           bit;

#define BIG_ENDIAN_TYPE                         /*  Big endian processor    */

#endif




#if PRODUCT_COMPILER_TYPE == G_KEIL_8051_C || \
    PRODUCT_COMPILER_TYPE == G_KEIL_C167CR_C

/*typedef        char           char;      */
typedef unsigned short int      char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
typedef unsigned char           bool8;
typedef unsigned short int      bool16;
typedef unsigned char           byte;
typedef unsigned short int      word;
typedef unsigned long int       dword;
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef signed   char           int8;
typedef short    int            int16;
typedef long     int            int32;
typedef unsigned char           bits8;
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned int            bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;    */
/* typedef signed   long long   int64;     */
/* typedef unsigned long long   ddword;    */
/*typedef                       bit;       */

#define LITTLE_ENDIAN_TYPE                      /*  Little endian processor */

#endif




#if PRODUCT_COMPILER_TYPE == G_TI_LEAD3_C

/* typedef       char           char;   N/A */
typedef unsigned char           char16;
typedef unsigned short int      ucs2_char;
typedef unsigned char           utf8_char;
/* typedef unsigned char        bool8;  N/A */
typedef unsigned char           bool16;
/* typedef unsigned char        byte;   N/A */
typedef unsigned char           word;
typedef unsigned long int       dword;
/* typedef unsigned char        uint8;  N/A */
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
/* typedef signed   char        int8;   N/A */
typedef signed short int        int16;
typedef signed long int         int32;
/* typedef unsigned char        bits8;  N/A */
typedef unsigned short int      bits16;
typedef unsigned long int       bits32;
typedef unsigned short int      bitf;

/* Non-ANSI extensions: */
/* typedef unsigned long long   uint64;    */
/* typedef signed   long long   int64;     */
/* typedef unsigned long long   ddword;    */
/* typedef unsigned char           bit;    */

#define BIG_ENDIAN_TYPE                         /*  Big endian processor    */

#endif


/****************************************************************************/
/* Following definitions are used with all compilers. */

typedef int16        int16_q1;          /* signed 16-bit Q1 number  */
typedef int16        int16_q2;          /* signed 16-bit Q2 number  */
typedef int16        int16_q3;          /* signed 16-bit Q3 number  */
typedef int16        int16_q4;          /* signed 16-bit Q4 number  */
typedef int16        int16_q5;          /* signed 16-bit Q5 number  */
typedef int16        int16_q6;          /* signed 16-bit Q6 number  */
typedef int16        int16_q7;          /* signed 16-bit Q7 number  */
typedef int16        int16_q8;          /* signed 16-bit Q8 number  */
typedef int16        int16_q9;          /* signed 16-bit Q9 number  */
typedef int16        int16_q10;         /* signed 16-bit Q10 number */
typedef int16        int16_q11;         /* signed 16-bit Q11 number */
typedef int16        int16_q12;         /* signed 16-bit Q12 number */
typedef int16        int16_q13;         /* signed 16-bit Q13 number */
typedef int16        int16_q14;         /* signed 16-bit Q14 number */
typedef int16        int16_q15;         /* signed 16-bit Q15 number */
typedef int16        int16_q;           /* signed 16-bit unspecified Q number */

typedef uint16      uint16_q1;         /* unsigned 16-bit Q1 number  */
typedef uint16      uint16_q2;         /* unsigned 16-bit Q2 number  */
typedef uint16      uint16_q3;         /* unsigned 16-bit Q3 number  */
typedef uint16      uint16_q4;         /* unsigned 16-bit Q4 number  */
typedef uint16      uint16_q5;         /* unsigned 16-bit Q5 number  */
typedef uint16      uint16_q6;         /* unsigned 16-bit Q6 number  */
typedef uint16      uint16_q7;         /* unsigned 16-bit Q7 number  */
typedef uint16      uint16_q8;         /* unsigned 16-bit Q8 number  */
typedef uint16      uint16_q9;         /* unsigned 16-bit Q9 number  */
typedef uint16      uint16_q10;        /* unsigned 16-bit Q10 number */
typedef uint16      uint16_q11;        /* unsigned 16-bit Q11 number */
typedef uint16      uint16_q12;        /* unsigned 16-bit Q12 number */
typedef uint16      uint16_q13;        /* unsigned 16-bit Q13 number */
typedef uint16      uint16_q14;        /* unsigned 16-bit Q14 number */
typedef uint16      uint16_q15;        /* unsigned 16-bit Q15 number */
typedef uint16      uint16_q16;        /* unsigned 16-bit Q16 number */
typedef uint16      uint16_q;          /* unsigned 16-bit unspecified Q number */

typedef int32         int32_q1;          /* signed 32-bit Q1 number  */
typedef int32         int32_q2;          /* signed 32-bit Q2 number  */
typedef int32         int32_q3;          /* signed 32-bit Q3 number  */
typedef int32         int32_q4;          /* signed 32-bit Q4 number  */
typedef int32         int32_q5;          /* signed 32-bit Q5 number  */
typedef int32         int32_q6;          /* signed 32-bit Q6 number  */
typedef int32         int32_q7;          /* signed 32-bit Q7 number  */
typedef int32         int32_q8;          /* signed 32-bit Q8 number  */
typedef int32         int32_q9;          /* signed 32-bit Q9 number  */
typedef int32         int32_q10;         /* signed 32-bit Q10 number */
typedef int32         int32_q11;         /* signed 32-bit Q11 number */
typedef int32         int32_q12;         /* signed 32-bit Q12 number */
typedef int32         int32_q13;         /* signed 32-bit Q13 number */
typedef int32         int32_q14;         /* signed 32-bit Q14 number */
typedef int32         int32_q15;         /* signed 32-bit Q15 number */
typedef int32         int32_q16;         /* signed 32-bit Q16 number */
typedef int32         int32_q17;         /* signed 32-bit Q17 number */
typedef int32         int32_q18;         /* signed 32-bit Q18 number */
typedef int32         int32_q19;         /* signed 32-bit Q19 number */
typedef int32         int32_q20;         /* signed 32-bit Q20 number */
typedef int32         int32_q21;         /* signed 32-bit Q21 number */
typedef int32         int32_q22;         /* signed 32-bit Q22 number */
typedef int32         int32_q23;         /* signed 32-bit Q23 number */
typedef int32         int32_q24;         /* signed 32-bit Q24 number */
typedef int32         int32_q25;         /* signed 32-bit Q25 number */
typedef int32         int32_q26;         /* signed 32-bit Q26 number */
typedef int32         int32_q27;         /* signed 32-bit Q27 number */
typedef int32         int32_q28;         /* signed 32-bit Q28 number */
typedef int32         int32_q29;         /* signed 32-bit Q29 number */
typedef int32         int32_q30;         /* signed 32-bit Q30 number */
typedef int32         int32_q31;         /* signed 32-bit Q31 number */
typedef int32         int32_q;           /* signed 32-bit unspecified Q number */
                    
typedef uint32       uint32_q1;         /* unsigned 32-bit Q1 number  */
typedef uint32       uint32_q2;         /* unsigned 32-bit Q2 number  */
typedef uint32       uint32_q3;         /* unsigned 32-bit Q3 number  */
typedef uint32       uint32_q4;         /* unsigned 32-bit Q4 number  */
typedef uint32       uint32_q5;         /* unsigned 32-bit Q5 number  */
typedef uint32       uint32_q6;         /* unsigned 32-bit Q6 number  */
typedef uint32       uint32_q7;         /* unsigned 32-bit Q7 number  */
typedef uint32       uint32_q8;         /* unsigned 32-bit Q8 number  */
typedef uint32       uint32_q9;         /* unsigned 32-bit Q9 number  */
typedef uint32       uint32_q10;        /* unsigned 32-bit Q10 number */
typedef uint32       uint32_q11;        /* unsigned 32-bit Q11 number */
typedef uint32       uint32_q12;        /* unsigned 32-bit Q12 number */
typedef uint32       uint32_q13;        /* unsigned 32-bit Q13 number */
typedef uint32       uint32_q14;        /* unsigned 32-bit Q14 number */
typedef uint32       uint32_q15;        /* unsigned 32-bit Q15 number */
typedef uint32       uint32_q16;        /* unsigned 32-bit Q16 number */
typedef uint32       uint32_q17;        /* unsigned 32-bit Q17 number */
typedef uint32       uint32_q18;        /* unsigned 32-bit Q18 number */
typedef uint32       uint32_q19;        /* unsigned 32-bit Q19 number */
typedef uint32       uint32_q20;        /* unsigned 32-bit Q20 number */
typedef uint32       uint32_q21;        /* unsigned 32-bit Q21 number */
typedef uint32       uint32_q22;        /* unsigned 32-bit Q22 number */
typedef uint32       uint32_q23;        /* unsigned 32-bit Q23 number */
typedef uint32       uint32_q24;        /* unsigned 32-bit Q24 number */
typedef uint32       uint32_q25;        /* unsigned 32-bit Q25 number */
typedef uint32       uint32_q26;        /* unsigned 32-bit Q26 number */
typedef uint32       uint32_q27;        /* unsigned 32-bit Q27 number */
typedef uint32       uint32_q28;        /* unsigned 32-bit Q28 number */
typedef uint32       uint32_q29;        /* unsigned 32-bit Q29 number */
typedef uint32       uint32_q30;        /* unsigned 32-bit Q30 number */
typedef uint32       uint32_q31;        /* unsigned 32-bit Q31 number */
typedef uint32       uint32_q;          /* unsigned 32-bit unspecified Q number */




/****************************************************************************/
/* Following definitions are used with all compilers, if they are not defined
   elsewhere. */


/* NOTE! If the tiny, near, far and huge pointers are to be used by a project
         then these defs must be undefined and then redefine to the compilers
         equivalent keyword in a suitable configuration file ( product.h ).
         Projects should be aware that using these keywords will change the
         amount of RAM and ROM consumed by their software. */

#ifndef _tiny
#define _tiny
#endif

#ifndef _near
#define _near
#endif

#ifndef _far
#define _far
#endif

#ifndef _huge
#define _huge
#endif


/****************************************************************************/
/* Following reserved keywords with some compilers have to be defined
   for portability reasons also with other compilers (to dummy):
     no_init         Compilers for Hitachi processors
     iram            Compilers for Hitachi processors
     C_task          Compilers for Hitachi H8 processors
     ioport          Compilers for LEAD3 processor 
     register        Compiler for C16x (from KEIL) */

#if PRODUCT_COMPILER_TYPE==G_IAR_H8_500 || PRODUCT_COMPILER_TYPE==G_IAR_H8_300H
   
/*#define no_init                                   IAR H8/500 no_init      */
/*#define iram                                      IAR H8/500              */
/*#define C_task                                    IAR H8/500              */

#elif PRODUCT_COMPILER_TYPE==G_IAR_H8_H8S

/*#define no_init                                   IAR H8/500 no_init      */
/*#define iram                                      IAR H8/500              */
/*#define C_task                                    IAR H8/500              */

#elif PRODUCT_COMPILER_TYPE==G_SH7K_GH_C || PRODUCT_COMPILER_TYPE==G_SH7K_HIT_C

/*#define no_init                                   IAR H8/500 no_init      */
/*#define iram                                      IAR H8/500              */
#define C_task                                  /*  IAR H8/500              */

#else

#define no_init                                 /*  IAR H8/500 no_init      */
#define iram                                    /*  IAR H8/500              */
#define C_task                                  /*  IAR H8/500              */

#endif


/* So far, LEAD3 reserved word ioport is defined to empty only with Borland C */
#if PRODUCT_COMPILER_TYPE == G_BORLAND_C

#define ioport

#endif


/* With Keil C16x compiler, register shall be defined empty */
#if PRODUCT_COMPILER_TYPE == G_KEIL_C167CR_C

#define register

#endif



#endif	/* TYPE_DEF_H */
