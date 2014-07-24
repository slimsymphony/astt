/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                pmd_compression2.h
                ------------------
                SW Include






Project:          autogen

%name:            pmd_compression2.h %
%version:         co1tss#5 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Jan  4 09:51:42 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen / PMD library

    The file contains the interface for the PMD compression
*/

#ifndef _PMD_COMPRESSION2_H_
#define _PMD_COMPRESSION2_H_

/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include <stdio.h>


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

/*  Use "C" linkage specification when compiling for C++ only  */
#ifdef __cplusplus
extern "C" {
#endif


/* ============================================================================================= */
/* Constants */
/* ============================================================================================= */

/* Return codes */
#define PMD_RC_OK 0
#define PMD_RC_NO_MEMORY -1
#define PMD_RC_BAD_INPUT -2
#define PMD_RC_INTERNAL_LIMIT_REACHED -3
#define PMD_RC_NO_MORE_DATA -4
#define PMD_RC_TOKEN_CONFLICT -5
#define PMD_LOWEST_SUCCESSFUL_RETURN PMD_RC_OK

/* Constants for compact tokens */
#define PMD_COMPACT_TOKEN_TYPE_BITS 3U
#define PMD_COMPACT_TOKEN_VALUE_BITS (32U - PMD_COMPACT_TOKEN_TYPE_BITS)
#define PMD_TOKEN_TYPE_OVERFLOW (~((~0U) << PMD_COMPACT_TOKEN_TYPE_BITS))
#define PMD_COMACT_TOKEN_VALUE_MASK (~((~0U) << (32U - PMD_COMPACT_TOKEN_TYPE_BITS)))
#define PMD_MAX_COMPACT_TOKEN_TYPE (PMD_TOKEN_TYPE_OVERFLOW - 1U)
#define PMD_MAX_COMPACT_TOKEN_VALUE PMD_COMACT_TOKEN_VALUE_MASK
#define PMD_INVALID_COMPACT_TOKEN \
        PMD_CREATE_COMPACT_TOKEN(PMD_TOKEN_TYPE_OVERFLOW, PMD_MAX_COMPACT_TOKEN_VALUE)

/* Constants for the underlying token types */
#define PMD_TOKEN_TYPE_SYMBOL 0
#define PMD_TOKEN_TYPE_CODE 1
#define PMD_TOKEN_TYPE_COLLECTED_SYMBOL 2
#define PMD_TOKEN_TYPE_COLLECTED_CODE 3
#define PMD_TOKEN_TYPE_CODE_SIZE_CHANGE 4
#define PMD_TOKEN_TYPE_HUFFMAN_NODE 5

/* Constants for initialisation of structures */
#define PMD_INITIAL_TOKEN_BUFFER { 0 }
#define PMD_INITIAL_BIT_BUFFER { 0 }
#define PMD_INITIAL_TOKEN { PMD_TOKEN_TYPE_OVERFLOW, PMD_MAX_COMPACT_TOKEN_VALUE }
#define PMD_INITIAL_STRING_TABLE { 0 }


/* ============================================================================================= */
/* Macros */
/* ============================================================================================= */

/*** Macros for compact tokens ***/

/* Determines whether the given combination of token type and token value
   is suitable for storing in a compact token */
#define PMD_IS_COMPACT_TOKEN(type, value)                                     \
      ((type) <= PMD_MAX_COMPACT_TOKEN_TYPE && (value) <= PMD_MAX_COMPACT_TOKEN_VALUE)

/* Creates a compact token from type and value suitable for it */
#define PMD_CREATE_COMPACT_TOKEN(type, value)                                 \
      ((type << PMD_COMPACT_TOKEN_VALUE_BITS) | (value & PMD_COMACT_TOKEN_VALUE_MASK))

/* Returns the type stored in a compact token. May be PMD_TOKEN_TYPE_OVERFLOW */
#define PMD_GET_COMPACT_TOKEN_TYPE(token) (token >> PMD_COMPACT_TOKEN_VALUE_BITS)

/* Returns the value stored in a compact token. May be a overflow index. */
#define PMD_GET_COMPACT_TOKEN_VALUE(token) (token & PMD_COMACT_TOKEN_VALUE_MASK)

/* Returns the underlying type of a compact token. Is never PMD_TOKEN_TYPE_OVERFLOW */
#define PMD_GET_TOKEN_TYPE(pBuffer, token)                                       \
      ((PMD_GET_COMPACT_TOKEN_TYPE(token) == PMD_TOKEN_TYPE_OVERFLOW)            \
       ? (pBuffer)->pOverflowBuffer[PMD_GET_COMPACT_TOKEN_VALUE(token)].type     \
       : PMD_GET_COMPACT_TOKEN_TYPE(token))

/* Returns the underlying value of a compact token. Is never an overflow index */
#define PMD_GET_TOKEN_VALUE(pBuffer, token)                                      \
      ((PMD_GET_COMPACT_TOKEN_TYPE(token) == PMD_TOKEN_TYPE_OVERFLOW)            \
       ? (pBuffer)->pOverflowBuffer[PMD_GET_COMPACT_TOKEN_VALUE(token)].value    \
       : PMD_GET_COMPACT_TOKEN_VALUE(token))


/*** Macros for buffer manipulation ***/

/* Appends a single token to the given token buffer */
#define PMD_APPEND_TOKEN(pBuffer, type, value)                                \
    (((pBuffer)->curSize >= (pBuffer)->maxSize ||                             \
     !PMD_IS_COMPACT_TOKEN(type, value))                                      \
    ? pmd_append_token(pBuffer, type, value)                                  \
    : (*(((pBuffer)->pTokens) + (pBuffer)->curSize) =                         \
            PMD_CREATE_COMPACT_TOKEN(type, value),                            \
       (pBuffer)->curSize++,                                                  \
       PMD_RC_OK))

/* Appends a single token, given as a compact token, to the given token buffer */
#define PMD_APPEND_COMPACT_TOKEN(pBuffer, token, pOrigBuffer)                 \
    (((pBuffer)->curSize >= (pBuffer)->maxSize ||                             \
      PMD_GET_COMPACT_TOKEN_TYPE(token) == PMD_TOKEN_TYPE_OVERFLOW)           \
    ? pmd_append_token(pBuffer, PMD_GET_TOKEN_TYPE(pOrigBuffer, token),       \
                                PMD_GET_TOKEN_VALUE(pOrigBuffer, token))      \
    : (*(((pBuffer)->pTokens) + (pBuffer)->curSize) = token,                  \
       (pBuffer)->curSize++,                                                  \
       PMD_RC_OK))

/* Appends a whole byte to the given bit buffer */
#define PMD_APPEND_BYTE(pBuffer, value)                                       \
    ((((pBuffer)->curSize & 7) || (pBuffer)->curSize+8 >= (pBuffer)->maxSize) \
     ? pmd_append_bits(pBuffer, value, 8)                                     \
     : ((pBuffer)->pBits[(pBuffer)->curSize >> 3] = (value),                  \
        (pBuffer)->curSize += 8,                                              \
        PMD_RC_OK))

/* Returns whether there's more data in the buffer */
#define PMD_HAS_MORE_DATA(pBuffer) ((pBuffer)->getSize < (pBuffer)->curSize)

/* Extracts a single compact token from the given token buffer */
#define PMD_EXTRACT_TOKEN(pBuffer, rType, rValue)                             \
    (PMD_HAS_MORE_DATA(pBuffer)                                               \
     ? ((rType) = PMD_GET_TOKEN_TYPE(pBuffer,                                 \
                           (pBuffer)->pTokens[(pBuffer)->getSize]),           \
        (rValue) = PMD_GET_TOKEN_VALUE(pBuffer,                               \
                           (pBuffer)->pTokens[(pBuffer)->getSize]),           \
        (pBuffer)->getSize++,                                                 \
        PMD_RC_OK)                                                            \
     : PMD_RC_NO_MORE_DATA)


/* Macros for initialisation (primarily for C++) */

#define PMD_INITIALIZE_TOKEN_BUFFER(pBuffer) memset(pBuffer, 0, sizeof(*(pBuffer)))
#define PMD_INITIALIZE_BIT_BUFFER(pBuffer) memset(pBuffer, 0, sizeof(*(pBuffer)))
#define PMD_INITIALIZE_STRING_TABLE(pTable) memset(pTable, 0, sizeof(*(pTable)))


/* ============================================================================================= */
/* Data types */
/* ============================================================================================= */

/* A bit buffer used for compressed data. The bit buffer should not be read
   before all data has been written to it. */
struct t_pmd_bit_buffer
{
   unsigned char *pBits;
   unsigned int curSize;
   unsigned int maxSize;
   unsigned int getSize;
   unsigned int buffer;
   unsigned int bufferSize;
};

typedef struct t_pmd_bit_buffer pmd_bit_buffer;

/* A single uncompressed PMD token */
struct t_pmd_token
{
   unsigned int type;
   unsigned int value;
};

/* A token buffer for uncompressed data */
struct t_pmd_token_buffer
{
   unsigned int *pTokens;
   unsigned int curSize;
   unsigned int maxSize;
   unsigned int getSize;
   struct t_pmd_token *pOverflowBuffer;
   unsigned int curOverflowSize;
   unsigned int maxOverflowSize;
};

typedef struct t_pmd_token_buffer pmd_token_buffer;


/* A hash entry for the string table */
struct t_pmd_string_table_entry
{
   unsigned int index;
   unsigned int length;
   unsigned int id;
   struct t_pmd_string_table_entry *pNext;
};

/* A string table for merging identical strings */
struct t_pmd_string_table
{
   char *pStrings;
   unsigned int curSize;
   unsigned int maxSize;
   unsigned int nextId;
   struct t_pmd_string_table_entry *pHashTable;
};

typedef struct t_pmd_string_table pmd_string_table;


/* ============================================================================================= */
/* Function prototypes */
/* ============================================================================================= */

/* String table functions */
int pmd_allocate_string_table(pmd_string_table *pTable);
int pmd_add_string(pmd_string_table *pTable);
char *pmd_get_string(pmd_string_table *pTable, unsigned int stringId);
int pmd_release_string_table(pmd_string_table *pTable);

/* Buffer allocation functions */
int pmd_release_bits(pmd_bit_buffer *pBuffer);
int pmd_release_tokens(pmd_token_buffer *pBuffer);
int pmd_clear_tokens(pmd_token_buffer *pBuffer);

/* Buffer manipulation functions */
int pmd_append_bits(pmd_bit_buffer *pBuffer, unsigned int bits, unsigned int nBits);
int pmd_append_token(pmd_token_buffer *pBuffer, unsigned int type, unsigned int value);
int pmd_get_byte_count(pmd_bit_buffer *pBuffer, int include_padding);
unsigned char *pmd_get_byte_pointer(pmd_bit_buffer *pBuffer);
int pmd_remove_bytes(pmd_bit_buffer *pBuffer, unsigned int nBytes);
unsigned char *pmd_reserve_bytes(pmd_bit_buffer *pBuffer, unsigned int nBytes);
int pmd_commit_bytes(pmd_bit_buffer *pBuffer, unsigned int nBytes);
int pmd_get_remaining_bits(pmd_bit_buffer *pBuffer);

/* Compression functions */
int pmd_compress_tokens(pmd_token_buffer *pUncompressed, pmd_token_buffer *pCompressed);
int pmd_uncompress_tokens(pmd_token_buffer *pCompressed, pmd_token_buffer *pUncompressed);
int pmd_encode_tokens(pmd_token_buffer *pUncoded, pmd_bit_buffer *pEncoded);
int pmd_decode_tokens(pmd_bit_buffer *pEncoded, pmd_token_buffer *pDecoded);

/* More compression functions */
int pmd_compress_block(pmd_token_buffer *pUncompressed, pmd_bit_buffer *pCompressed);
int pmd_uncompress_block(pmd_bit_buffer *pCompressed, pmd_token_buffer *pUncompressed);

/* Debugging functions */
int pmd_print_tokens(pmd_token_buffer *pTokens, FILE *pStream);
int pmd_print_bits(pmd_bit_buffer *pBits, FILE *pStream);


/*  Use "C" linkage specification when compiling for C++ only  */
#ifdef __cplusplus
}
#endif


#endif /* _PMD_COMPRESSION2_H_ */

/*  End of file pmd_compression2.h  */
