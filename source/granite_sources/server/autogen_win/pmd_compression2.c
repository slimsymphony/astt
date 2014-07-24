/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                pmd_compression2.c
                ------------------
                SW Module






Project:          autogen

%name:            pmd_compression2.c %
%version:         co1tss#7 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Jan  4 09:51:45 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen and PMD library

    The purpose of this module is to implement an LZH compression
    algorithm for PMD files.
*/


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "pmd_compression2.h"
#include "pmd_heap.h"


/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
#define LOCAL static
#endif /* LOCAL */

/* Disable warning from MSVC */
#ifdef _MSC_VER
/* warning C4711: function 'XXX' selected for automatic inline expansion */
#pragma warning(disable: 4711)
#endif


/* The size of the compression hash table */
#define COMPRESSION_TABLE_SIZE 1000003 /* Should be a prime number */

/* A number used in hashing. The biggest prime less than 2^32 / COMPRESSION_TABLE_SIZE */
#define HASH_FACTOR 4289

/* Initial size of the decompression code table */
#define INITAL_DECOMPRESSION_SIZE 10000

/* Initial size of bit buffers (in bits) */
#define INITIAL_BIT_BUFFER_SIZE 1000000

/* Initial size of token buffers (in tokens) */
#define INITIAL_TOKEN_BUFFER_SIZE 1000000

/* Initial size of overflow buffer in token buffers */
#define INITIAL_OVERFLOW_BUFFER_SIZE 100

/* Initial size of the Huffman tree in bytes */
#define INITIAL_HUFFMAN_TREE_BYTES 10000

/* Size of the Huffman frequency array */
#define FREQUENCY_SIZE 1000

/* Initial size of the Huffman join table */
#define INITIAL_JOIN_SIZE 1000

/* Size of the encoding lookup table */
#define ENCODING_TABLE_SIZE 65536

/* The frequency below which symbols are shared */
#define MIN_SEPARATE_SYMBOL_FREQUENCY 100

/* The frequency below which codes are shared */
#define MIN_SEPARATE_CODE_FREQUENCY 9

/* Constants for the form of the Huffman tree */
#define HUFFMAN_TREE_LEAF 0
#define HUFFMAN_TREE_NODE 1
#define HUFFMAN_TREE_LEFT 0
#define HUFFMAN_TREE_RIGHT 1

/* The code for the end token */
#define CODE_END 0

/* The first code available for Lempel-Ziv */
#define CODE_FIRST_FREE (CODE_END+1)

/* The size in bits of the code when starting Lempel-Ziv */
#define INITIAL_CODE_SIZE 2

/* The size in bits of the token type used when first encountering a token */
#define TOKEN_TYPE_SIZE 2

/* The size in bits of the bit count for symbols */
#define SYMBOL_BIT_COUNT_SIZE 5

/* The maximum length of a Huffman code */
#define MAX_PATTERN_SIZE 31

/*  6.3    Local macros */

/* Calculates the encode table index for the given compact token */
#define GET_ENCODE_INDEX(token) ((((token) & 0xFFFF) ^ ((token) >> 16)) % ENCODING_TABLE_SIZE)

/* Calculates from bits to bytes for calling malloc and realloc */
#define BIT_BUFFER_ALLOC_ROUND(bits) (((bits)+7) >> 3)

/* Extracts a single bit from the given bit buffer */
#define PMD_EXTRACT_BIT(pBuffer)                                              \
    ((pBuffer->bufferSize) ? ((pBuffer->buffer >> --pBuffer->bufferSize) & 1) \
                           : extract_bit(pBuffer))

/* Compact token; a more compact representation of a canonical token.
   Overflows are stored in the token buffer. */
typedef unsigned int pmd_compact_token;

/* Canonical token structure. Used in the overflow buffer */
typedef struct t_pmd_token pmd_token;

/* Hash bucket used for finding previously seen strings during compression */
struct t_hash_bucket
{
   pmd_compact_token *pTokens;
   unsigned int nTokens;
   unsigned int nCode;
   struct t_hash_bucket *pNext;
};

typedef struct t_hash_bucket hash_bucket;


/* An entry in the decompression code table */
struct t_decompression_entry
{
   unsigned int tokenIndex;
   unsigned int nTokens;
};

typedef struct t_decompression_entry decompression_entry;

/* An entry in the encoding table */
struct t_encoding_entry
{
   pmd_compact_token token;
   unsigned int frequency;
   unsigned int bitpattern;
   unsigned int nBits;
   unsigned int used;
   struct t_encoding_entry *pNext;
};

typedef struct t_encoding_entry encoding_entry;

/* The encoding table */
struct t_encoding_table
{
   encoding_entry **pEntries;
};

typedef struct t_encoding_table encoding_table;

/* A frequency entry in the Huffman table */
struct t_huffman_frequency_entry
{
   pmd_compact_token token;
   unsigned int frequency;
   struct t_huffman_frequency_entry *pNext;
};

typedef struct t_huffman_frequency_entry huffman_frequency_entry;

/* A join entry in the Huffman table */
struct t_huffman_join_entry
{
   pmd_compact_token left;
   pmd_compact_token right;
};

typedef struct t_huffman_join_entry huffman_join_entry;

/* The Huffman table */
struct t_huffman_table
{
   huffman_frequency_entry *arrFrequencies[FREQUENCY_SIZE];
   huffman_frequency_entry *pHighFrequency;
   huffman_frequency_entry *pLastHighFrequency;
   unsigned int minFrequency;
   unsigned int maxFrequency;
   huffman_join_entry *pJoins;
   unsigned int curJoins;
   unsigned int maxJoins;
};

typedef struct t_huffman_table huffman_table;

/* A node in the Huffman decoding tree */

union t_huffman_node
{
   struct
   {
      int is_leaf;
      int used;
      pmd_token token;
   } leaf;
   struct
   {
      int is_leaf;
      union t_huffman_node *pLeft;
      union t_huffman_node *pRight;
   } node;
};

typedef union t_huffman_node huffman_node;
  

/* ============================================================================================= */
/* Local function prototypes */
/* ============================================================================================= */

/* Reallocates the token buffer so that its maximum henceforth is size. */
LOCAL int realloc_tokens(pmd_token_buffer *pBuffer, unsigned int size);

/* Reallocates the overflow buffer so that its maximum henceforth is size. */
LOCAL int realloc_overflow(pmd_token_buffer *pBuffer, unsigned int size);

/*  Extracts the given number of bits from the bit buffer */
LOCAL int extract_bits(pmd_bit_buffer *pBits, unsigned int nBits, unsigned int *pResult); 

/*  Extract a single bit from the bit buffer. Returns < LOWEST_SUCCESSFUL_RETURN on error */
LOCAL int extract_bit(pmd_bit_buffer *pBits); 

/* Appends tokens from the buffer itself. */
LOCAL int append_own_tokens(pmd_token_buffer *pBuffer, unsigned int first, unsigned int size);

/* Creates a compact token from a given type and value */
LOCAL int create_token(pmd_token_buffer *pBuffer,
                       unsigned int type,
                       unsigned int value,
                       pmd_compact_token *pResult);

/* Copies any overflow token table from source to destination. */
LOCAL int pmd_copy_overflow_tokens(pmd_token_buffer *pDestination,
                                   const pmd_token_buffer *pSource);

/* Allocates an encoding table */
LOCAL int allocate_encoding_table(encoding_table *pTable);

/* Adds the given token to the table */
LOCAL int add_token_to_encoding(pmd_compact_token token,
                                encoding_table *pTable,
                                unsigned int frequency);

/* Adds the tokens in the buffer to the table */
LOCAL int add_tokens_to_encoding(pmd_token_buffer *pTokens,
                                 encoding_table *pTable);

/* Finds a token in the encoding table */
LOCAL encoding_entry *lookup_encoding(encoding_table *pEncoding, pmd_compact_token token);

/* Releases an encoding table */
LOCAL int release_encoding_table(encoding_table *pTable);

/* Allocates a Huffman table */
LOCAL int allocate_huffman_table(huffman_table *pTable);

/* Collects shared tokens into a single token */
LOCAL int collect_shared_tokens(pmd_token_buffer *pTokens,
                                encoding_table *pEncoding,
                                huffman_table *pHuffman);

/* Adds a token to the Huffman table */
LOCAL int add_huffman_token(huffman_table *pHuffman,
                            pmd_compact_token token,
                            unsigned int frequency);

/* Releases a Huffman table */
LOCAL int release_huffman_table(huffman_table *pHuffman);

/* Build a Huffman tree for the given table */
LOCAL int build_huffman_tree(huffman_table *pHuffman);

/* Create bit patterns for encoding all leaves with the given join root */
LOCAL int traverse_huffman_tree(huffman_table *pHuffman,
                                encoding_table *pEncoding,
                                unsigned int joinCode,
                                unsigned int bitPattern,
                                unsigned int patternSize,
                                pmd_bit_buffer *pTreeForm);

/* Extracts a low-frequency token from the Huffman table */
LOCAL huffman_frequency_entry *extract_huffman_token(huffman_table *pHuffman);

/* Extracts the Huffman decoding tree from the given bit buffer */
LOCAL int extract_huffman_tree(pmd_heap_handle *heap,
                               pmd_bit_buffer *pTreeForm,
                               huffman_node **ppRoot);


/* ============================================================================================= */
/* Local functions */
/* ============================================================================================= */

/* ========================================================================= */
/*  realloc_tokens */

/* Reallocates the token buffer so that its maximum henceforth is size. */
LOCAL int realloc_tokens(pmd_token_buffer *pBuffer, unsigned int size)
{
    pmd_compact_token *pNewData = realloc(pBuffer->pTokens, size * sizeof(pmd_compact_token));
    if (!pNewData)
    {
        return PMD_RC_NO_MEMORY;
    }
    pBuffer->pTokens = pNewData;
    pBuffer->maxSize = size;
    return PMD_RC_OK;
}


/* ========================================================================= */
/*  realloc_overflow */

/* Reallocates the overflow buffer so that its maximum henceforth is size. */
LOCAL int realloc_overflow(pmd_token_buffer *pBuffer, unsigned int size)
{
    pmd_token *pNewData = realloc(pBuffer->pOverflowBuffer, size * sizeof(pmd_token));
    if (!pNewData)
    {
        return PMD_RC_NO_MEMORY;
    }
    pBuffer->pOverflowBuffer = pNewData;
    pBuffer->maxOverflowSize = size;
    return PMD_RC_OK;
}


/* ========================================================================= */
/*  extract_bits */

/*  Extracts the given number of bits from the bit buffer
*/

LOCAL int extract_bits(pmd_bit_buffer *pBits,
                       unsigned int nBits,
                       unsigned int *pResult)
{
    unsigned int result = 0;

    /* Check if the given number of bits is ready in our buffer */
    if (nBits <= pBits->bufferSize)
    {
        result = pBits->buffer >> (pBits->bufferSize - nBits);
        assert(nBits < 32);
        result &= ~((~0) << nBits);
        pBits->bufferSize -= nBits;
    }
    else
    {
        /* Start off with the bits that we have in our buffer */
        unsigned int missing = nBits - pBits->bufferSize;
        result = (pBits->buffer & ~((~0) << pBits->bufferSize)) << missing;

        /* Grab some more bits */
        if (pBits->getSize + 32 <= pBits->curSize)
        {
            /* Just take the next four bytes */
            const unsigned char *pFirstByte = &pBits->pBits[pBits->getSize >> 3];
            unsigned int buffer = (pFirstByte[0] << 24)
                                | (pFirstByte[1] << 16)
                                | (pFirstByte[2] << 8)
                                | (pFirstByte[3]);
            unsigned int newBufferSize = 32 - missing;
            assert((pBits->getSize & 7) == 0);
            result |= buffer >> newBufferSize;
            pBits->getSize = pBits->getSize + 32;
            pBits->buffer = buffer;
            pBits->bufferSize = newBufferSize;
        }
        else
        {
            /* We're approaching the end of the buffer. Handle all special cases. */
            unsigned int nRemainingBits = 0;
            unsigned int newBufferSize = 0;
            if (pBits->getSize == pBits->curSize && missing == nBits)
            {
                return PMD_RC_NO_MORE_DATA;
            }
            if (pBits->getSize + missing > pBits->curSize)
            {
                return PMD_RC_BAD_INPUT;
            }

            /* Grap the remaining whole bytes */
            pBits->bufferSize = 0;
            while (pBits->getSize + 8 <= pBits->curSize)
            {
                pBits->buffer = (pBits->buffer << 8) | pBits->pBits[pBits->getSize >> 3];
                pBits->getSize += 8;
                pBits->bufferSize += 8;
            }

            /* Extract any remaining bits */
            nRemainingBits = pBits->getSize & 7;
            if (nRemainingBits)
            {
                unsigned int remainder = pBits->pBits[pBits->getSize >> 3] >> (8 - nRemainingBits);
                pBits->buffer = (pBits->buffer << nRemainingBits) | remainder;
                pBits->getSize += nRemainingBits;
                pBits->bufferSize += nRemainingBits;
            }

            /* Copy the required number of bits from this, our last, buffer */
            assert(missing <= pBits->bufferSize);
            newBufferSize = pBits->bufferSize - missing;
            result |= (pBits->buffer >> newBufferSize) & ~((~0) << missing);
            pBits->bufferSize = newBufferSize;
        }
    }

    /* Save the result and return */
    *pResult = result;
    return PMD_RC_OK;
}


/* ========================================================================= */
/*  extract_bit */

/*  Extract a single bit from the bit buffer.
    Returns < LOWEST_SUCCESSFUL_RETURN on error. */
LOCAL int extract_bit(pmd_bit_buffer *pBits)
{
    unsigned int result = 0;
    int rc = extract_bits(pBits, 1, &result);
    if (rc != PMD_RC_OK)
    {
        return rc;
    }
    return result;
}


/* ========================================================================= */
/*  append_own_tokens */

/* Appends tokens from the buffer itself, starting at the given index and
   appending the given number of tokens. */
LOCAL int append_own_tokens(pmd_token_buffer *pBuffer, unsigned int first, unsigned int size)
{
    /* Ensure enough space in the buffer before start */
    if (pBuffer->curSize + size > pBuffer->maxSize)
    {
        int rc = realloc_tokens(pBuffer, pBuffer->curSize +
                                         size +
                                         INITIAL_TOKEN_BUFFER_SIZE);
        if (rc != PMD_RC_OK)
        {
            return rc;
        }
    }

    /* Copy the given tokens */
    assert(pBuffer->curSize >= first + size);  /* There should be no overlap */
    memcpy(pBuffer->pTokens + pBuffer->curSize,
           pBuffer->pTokens + first,
           size * sizeof(pmd_compact_token));

    /* Update size and return */
    pBuffer->curSize += size;
    return PMD_RC_OK;
}


/* ========================================================================= */
/*  create_token */

/*  This function checks if the given type and value fits into a compact token.
    If so, it returns this token in the pResult parameter. If not, it creates
    a token overflow entry in the given token buffer, and creates a compact
    token referring to this overflow entry.
*/

LOCAL int create_token(pmd_token_buffer *pBuffer,
                       unsigned int type,
                       unsigned int value,
                       pmd_compact_token *pResult)
{
    /* Check if the token goes as compact */
    if (PMD_IS_COMPACT_TOKEN(type, value))
    {
        *pResult = PMD_CREATE_COMPACT_TOKEN(type, value);
    }
    else
    {
        /* The token cannot fit as compact. Put it in the overflow table. */
        if (pBuffer->curOverflowSize >= PMD_MAX_COMPACT_TOKEN_VALUE)
        {
            return PMD_RC_INTERNAL_LIMIT_REACHED;
        }
        if (pBuffer->curOverflowSize >= pBuffer->maxOverflowSize)
        {
            /* Not enough room. Reallocate */
            int rc = realloc_overflow(pBuffer, pBuffer->maxOverflowSize +
                                               INITIAL_OVERFLOW_BUFFER_SIZE);
            if (rc != PMD_RC_OK)
            {
                return rc;
            }
        }
        pBuffer->pOverflowBuffer[pBuffer->curOverflowSize].type = type;
        pBuffer->pOverflowBuffer[pBuffer->curOverflowSize].value = value;
        *pResult = PMD_CREATE_COMPACT_TOKEN(PMD_TOKEN_TYPE_OVERFLOW, pBuffer->curOverflowSize);
        pBuffer->curOverflowSize++;
    }
    return PMD_RC_OK;
}


/* ========================================================================= */
/*  copy_overflow_tokens */

/*  Copies any overflow token table from the source buffer to the
    destination buffer. Returns an error if the destination buffer
    contains any overflow tokens on entry. */
LOCAL int copy_overflow_tokens(pmd_token_buffer *pDestination, const pmd_token_buffer *pSource)
{
    /* We don't want to handle merging of two overflow buffers */
    if (pDestination->curOverflowSize != 0)
    {
        return PMD_RC_TOKEN_CONFLICT;
    }

    /* Check that enough room has been allocated in the destination buffer */
    if (pDestination->maxOverflowSize < pSource->curOverflowSize)
    {
        /* Not enough room. Reallocate */
        int rc = realloc_overflow(pDestination, pSource->curOverflowSize);
        if (rc != PMD_RC_OK)
        {
           return rc;
        }
    }

    /* Copy the overflow tokens */
    memcpy(pDestination->pOverflowBuffer, pSource->pOverflowBuffer, 
           pSource->curOverflowSize * sizeof(pmd_token));
    pDestination->curOverflowSize = pSource->curOverflowSize;
    return PMD_RC_OK;
}


/* ========================================================================= */
/*  allocate_encoding_table */

/*  Allocates and initialises an encoding table. The table must be subsequently
    released using release_encoding_table.
*/

LOCAL int allocate_encoding_table(encoding_table *pTable)
{
   pTable->pEntries = calloc(ENCODING_TABLE_SIZE, sizeof(encoding_entry *));
   if (!pTable->pEntries)
   {
      return PMD_RC_NO_MEMORY;
   }
   return PMD_RC_OK;
}


/* ========================================================================= */
/*  add_token_to_encoding */

/*  Inserts the given token into the encoding table. The encoding table must
    have been allocated with allocate_encoding_table, and must be subsequently
    released using release_encoding_table.
*/

LOCAL int add_token_to_encoding(pmd_compact_token token,
                                encoding_table *pTable,
                                unsigned int frequency)
{
   unsigned int hash_index = GET_ENCODE_INDEX(token);
   encoding_entry *pEntry = pTable->pEntries[hash_index];
   encoding_entry **ppFollow = &pTable->pEntries[hash_index];

   /* Search for the entry */
   while (pEntry != NULL)
   {
      if (pEntry->token == token)
      {
         break;
      }
      ppFollow = &pEntry->pNext;
      pEntry = pEntry->pNext;
   }

   /* Create a new entry if it didn't exist */
   if (pEntry == NULL)
   {
      pEntry = malloc(sizeof(*pEntry));
      if (pEntry == NULL)
      {
         return PMD_RC_NO_MEMORY;
      }
      pEntry->token = token;
      pEntry->frequency = frequency;
      pEntry->bitpattern = 0;
      pEntry->nBits = 0;
      pEntry->used = 0;
      pEntry->pNext = 0;

      /* Insert the new entry into the table */
      *ppFollow = pEntry;
   }
   else
   {
      /* Update the frequency of the token */
      pEntry->frequency += frequency;
   }

   return PMD_RC_OK;
}


/* ========================================================================= */
/*  add_tokens_to_encoding */

/*  Inserts all tokens in the given token buffer in the encoding table. The
    encoding table must have been allocated with allocate_encoding_table,
    and must be subsequently released using release_encoding_table.
*/

LOCAL int add_tokens_to_encoding(pmd_token_buffer *pTokens,encoding_table *pTable)
{
   unsigned int index = 0;
   for (index = 0; index < pTokens->curSize; index++)
   {
      int rc = add_token_to_encoding(pTokens->pTokens[index], pTable, 1);
      if (rc != PMD_RC_OK)
      {
         return rc;
      }
   }
   return PMD_RC_OK;
}



/* ========================================================================= */
/*  lookup_encoding */

/*  Retrieves the encoding entry for the given token. Returns NULL if the token
    is not in the encoding table.
*/

LOCAL encoding_entry *lookup_encoding(encoding_table *pEncoding, pmd_compact_token token)
{
   encoding_entry *pEntry = pEncoding->pEntries[GET_ENCODE_INDEX(token)];
   while (pEntry && pEntry->token != token)
   {
      pEntry = pEntry->pNext;
   }
   return pEntry;
}


/* ========================================================================= */
/*  release_encoding_table */

/*  Releases memory allocated by allocate_encoding_table and subsequent operations
    on the encoding table.
*/

LOCAL int release_encoding_table(encoding_table *pTable)
{
   if (pTable->pEntries)
   {
      unsigned int index = 0;

      for (index = 0; index < ENCODING_TABLE_SIZE; index++)
      {
         encoding_entry *pEntry = pTable->pEntries[index];
         while (pEntry)
         {
            encoding_entry *pToDelete = pEntry;
            pEntry = pEntry->pNext;
            free(pToDelete);
         }
      }
      free(pTable->pEntries);
      pTable->pEntries = NULL;
   }
   return PMD_RC_OK;
}


/* ========================================================================= */
/*  allocate_huffman_table */

/*  Initialises a Huffman table. The table must be subsequently destroyed
    using release_huffman_table.
*/

LOCAL int allocate_huffman_table(huffman_table *pTable)
{
   memset(pTable->arrFrequencies, 0, sizeof(pTable->arrFrequencies));
   pTable->pHighFrequency = NULL;
   pTable->pLastHighFrequency = NULL;
   pTable->pJoins = malloc(INITIAL_JOIN_SIZE * sizeof(huffman_join_entry));
   if (!pTable->pJoins)
   {
      return PMD_RC_NO_MEMORY;
   }

   pTable->minFrequency = 0;
   pTable->maxFrequency = 0;
   pTable->curJoins = 0;
   pTable->maxJoins = INITIAL_JOIN_SIZE;
   return PMD_RC_OK;
}


/* ========================================================================= */
/*  collect_shared_tokens */

/*  Checks the frequency of the codes and symbols in the encoding table against
    predefined minimum frequencies. Any tokens not meeting the minimum frequency
    are assigned to the collected codes. The collected codes and tokens meeting
    the minimum frequency are added to the given Huffman table.
*/

LOCAL int collect_shared_tokens(pmd_token_buffer *pTokens,
                                encoding_table *pEncoding,
                                huffman_table *pHuffman)
{
   unsigned int collected_symbol_frequency = 0;
   unsigned int collected_code_frequency = 0;
   unsigned int index = 0;
   int rc = PMD_RC_OK;

   /* Collect tokens and calculate collected frequencies */
   for (index = 0; index < ENCODING_TABLE_SIZE; index++)
   {
      encoding_entry *pEntry = NULL;
      for (pEntry = pEncoding->pEntries[index]; pEntry != NULL; pEntry = pEntry->pNext)
      {
         switch (PMD_GET_TOKEN_TYPE(pTokens, pEntry->token))
         {
         case PMD_TOKEN_TYPE_SYMBOL:
            if (pEntry->frequency < MIN_SEPARATE_SYMBOL_FREQUENCY)
            {
               collected_symbol_frequency += pEntry->frequency;
            }
            else
            {
               rc = add_huffman_token(pHuffman, pEntry->token, pEntry->frequency);
            }
            break;
         case PMD_TOKEN_TYPE_CODE:
            if (pEntry->frequency < MIN_SEPARATE_CODE_FREQUENCY)
            {
               collected_code_frequency += pEntry->frequency;
            }
            else
            {
               rc = add_huffman_token(pHuffman, pEntry->token, pEntry->frequency);
            }
            break;
         case PMD_TOKEN_TYPE_CODE_SIZE_CHANGE:
            /* This should not appear in the Huffman table, as they should not
               appear in the encoded output. They are merely for keeping track of the
               number of bits to use for encoding compression codes. The decoder
               will keep track of this itself */
            break;
         default:
            rc = PMD_RC_BAD_INPUT;
            break;
         }
         if (rc != PMD_RC_OK)
         {
            return rc;
         }
      }
   }

   /* Add any collected symbol token to the two tables */
   if (collected_symbol_frequency > 0)
   {
      unsigned int token = PMD_CREATE_COMPACT_TOKEN(PMD_TOKEN_TYPE_COLLECTED_SYMBOL, 0);
      rc = add_huffman_token(pHuffman, token, collected_symbol_frequency);
      if (rc == PMD_RC_OK)
      {
         rc = add_token_to_encoding(token, pEncoding, collected_symbol_frequency);
      }
      if (rc != PMD_RC_OK)
      {
         return rc;
      }
   }

   /* Add any collected code token to the two tables */
   if (collected_code_frequency > 0)
   {
      unsigned int token = PMD_CREATE_COMPACT_TOKEN(PMD_TOKEN_TYPE_COLLECTED_CODE, 0);
      rc = add_huffman_token(pHuffman, token, collected_code_frequency);
      if (rc == PMD_RC_OK)
      {
         rc = add_token_to_encoding(token, pEncoding, collected_code_frequency);
      }
      if (rc != PMD_RC_OK)
      {
         return rc;
      }
   }

   return rc;
}


/* ========================================================================= */
/*  add_huffman_token */

/*  Adds the given token to the Huffman frequency table.
*/

LOCAL int add_huffman_token(huffman_table *pHuffman,
                            pmd_compact_token token,
                            unsigned int frequency)
{
   huffman_frequency_entry *pEntry = NULL;

   /* Allocate and initialise a new entry */
   pEntry = malloc(sizeof(huffman_frequency_entry));
   if (!pEntry)
   {
      return PMD_RC_NO_MEMORY;
   }
   pEntry->token = token;
   pEntry->frequency = frequency;
   pEntry->pNext = NULL;
   
   /* Insert the new entry */
   if (frequency >= FREQUENCY_SIZE)
   {
      /* The high frequency list is ordered. Make sure to insert the new
         element correctly. Due to the nature of Huffman coding, the most
         likely position is the last, which is therefore treated specially. */
      if (pHuffman->pLastHighFrequency)
      {
         if (pHuffman->pLastHighFrequency->frequency < frequency)
         {
            /* We should insert the new element as the last in the existing list */
            pHuffman->pLastHighFrequency->pNext = pEntry;
            pHuffman->pLastHighFrequency = pEntry;
         }
         else
         {
            /* We should find the right place for the new element in the existing list */
            huffman_frequency_entry **ppFollow = &pHuffman->pHighFrequency;
            while (*ppFollow && frequency > (*ppFollow)->frequency)
            {
               ppFollow = &(*ppFollow)->pNext;
            }
            pEntry->pNext = *ppFollow;
            *ppFollow = pEntry;
         }
      }
      else
      {
         /* The list is empty; we should add the element as the only element */
         assert(pHuffman->pHighFrequency == NULL);
         pHuffman->pHighFrequency = pEntry;
         pHuffman->pLastHighFrequency = pEntry;
      }
   }
   else
   {
      /* The low frequency lists are not ordered. Just insert as the first element */
      pEntry->pNext = pHuffman->arrFrequencies[frequency];
      pHuffman->arrFrequencies[frequency] = pEntry;

      /* Adjust min/max ranges */
      if (frequency > pHuffman->maxFrequency)
      {
         pHuffman->maxFrequency = frequency;
      }
      if (frequency < pHuffman->minFrequency)
      {
         pHuffman->minFrequency = frequency;
      }
   }

   return PMD_RC_OK;
}


/* ========================================================================= */
/*  release_huffman_table */

/*  Releases the Huffman table allocated by allocate_huffman_table.
*/

LOCAL int release_huffman_table(huffman_table *pHuffman)
{
   unsigned int index;
   huffman_frequency_entry *pEntry = NULL;
   for (index = pHuffman->minFrequency; index <= pHuffman->maxFrequency+1; index++)
   {
      /* Find the list to delete */
      if (index == pHuffman->maxFrequency+1)
      {
         /* We're beyond the highest singe frequency, but we use this
            index to release the high frequency list */
         pEntry = pHuffman->pHighFrequency;
      }
      else
      {
         pEntry = pHuffman->arrFrequencies[index];
      }
      
      /* Delete all entries in the list */
      while (pEntry)
      {
         huffman_frequency_entry *pToDestroy = pEntry;
         pEntry = pEntry->pNext;
         free(pToDestroy);
      }
   }
   free(pHuffman->pJoins);
   pHuffman->pHighFrequency = NULL;
   pHuffman->pLastHighFrequency = NULL;
   pHuffman->pJoins = NULL;
   pHuffman->minFrequency = 0;
   pHuffman->maxFrequency = 0;
   pHuffman->curJoins = 0;
   pHuffman->maxJoins = 0;
   return PMD_RC_OK;
}


/* ========================================================================= */
/*  build_huffman_tree */

/*  Repeatedly joins the two lowest-frequency tokens to a join node token,
    having a frequency which is the sum of the frequencies of the two original
    tokens. The new token replaces the two original tokens. This is repeated
    until there's only one token left, and is the core of the Huffman coding.
*/

LOCAL int build_huffman_tree(huffman_table *pHuffman)
{
   int rc = PMD_RC_OK;
   huffman_frequency_entry *pSmallest = NULL;
   huffman_frequency_entry *pNextBigger = NULL;
   pmd_compact_token token = PMD_INVALID_COMPACT_TOKEN;
   unsigned int frequency = 0;

   for (;;)
   {
      /* Retrieve the two lowest-frequency entries in the Huffman table */
      pSmallest = extract_huffman_token(pHuffman);
      pNextBigger = extract_huffman_token(pHuffman);
      if (!pSmallest)
      {
         /* We must have at least a single entry */
         assert(!pNextBigger);
         rc = PMD_RC_BAD_INPUT;
         break;
      }
      if (!pNextBigger)
      {
         /* We're done joining entries into the tree. Put the entry back in */
         rc = add_huffman_token(pHuffman, pSmallest->token, pSmallest->frequency);
         break;
      }

      /* Check if the join table is big enough to contain another entry */
      if (pHuffman->curJoins >= pHuffman->maxJoins)
      {
         /* Time to extend the join table */
         unsigned int newMax = pHuffman->curJoins * 2;
         int rc = PMD_RC_OK;
         huffman_join_entry *pNewJoins = NULL;
         if (newMax >= PMD_MAX_COMPACT_TOKEN_VALUE)
         {
            /* We need to be able to store join codes as compact tokens */
            rc = PMD_RC_INTERNAL_LIMIT_REACHED;
            break;
         }
         pNewJoins = realloc(pHuffman->pJoins, newMax * sizeof(huffman_join_entry));
         if (!pNewJoins)
         {
            rc = PMD_RC_NO_MEMORY;
            break;
         }
         pHuffman->maxJoins = newMax;
         pHuffman->pJoins = pNewJoins;
      }

      /* Add the combined entry to the frequency table */
      token = PMD_CREATE_COMPACT_TOKEN(PMD_TOKEN_TYPE_HUFFMAN_NODE, pHuffman->curJoins);
      frequency = pSmallest->frequency + pNextBigger->frequency;
      rc = add_huffman_token(pHuffman, token, frequency);
      if (rc != PMD_RC_OK)
      {
         break;
      }

      /* Add another entry to the join table */
      pHuffman->pJoins[pHuffman->curJoins].left = pSmallest->token;
      pHuffman->pJoins[pHuffman->curJoins].right = pNextBigger->token;
      pHuffman->curJoins++;

      /* Clean up the entries that were removed from the Huffman table */
      free(pSmallest);
      free(pNextBigger);
   }

   /* Clean up and return. The pointers may be NULL, but this is OK */
   free(pSmallest);
   free(pNextBigger);
   return rc;
}


/* ========================================================================= */
/*  traverse_huffman_tree */

/*  If the given token is a join token, this function retrieves its join table
    entry and calls itself recursively on the left and right children of the node,
    adding a zero and one bit, respectively, to the pattern. If the given token
    is a leaf token, its encoding entry gets assign the current pattern. In
    both cases, the appropriate bit is appended to the tree form bit buffer
    in order to communicate the form of the Huffman tree to the decoder.
*/

LOCAL int traverse_huffman_tree(huffman_table *pHuffman,
                                encoding_table *pEncoding,
                                pmd_compact_token token,
                                unsigned int bitPattern,
                                unsigned int patternSize,
                                pmd_bit_buffer *pTreeForm)
{
   int rc = PMD_RC_OK;

   if (PMD_GET_COMPACT_TOKEN_TYPE(token) == PMD_TOKEN_TYPE_HUFFMAN_NODE)
   {
      huffman_join_entry *pEntry = NULL;

      /* It's a node. We don't need to check for PMD_TOKEN_TYPE_OVERFLOW,
         since we don't support overflow on Huffman nodes (this is
         checked in build_huffman_tree) */
      if (patternSize == MAX_PATTERN_SIZE)
      {
         /* We don't want to use more than 32 bits for a single code */
         return PMD_RC_INTERNAL_LIMIT_REACHED;
      }

      assert(PMD_GET_COMPACT_TOKEN_VALUE(token) < pHuffman->curJoins);
      pEntry = &pHuffman->pJoins[PMD_GET_COMPACT_TOKEN_VALUE(token)];
      rc = pmd_append_bits(pTreeForm, HUFFMAN_TREE_NODE, 1);
      if (rc == PMD_RC_OK)
      {
         rc = traverse_huffman_tree(pHuffman, pEncoding, pEntry->left,
                                    (bitPattern << 1) + HUFFMAN_TREE_LEFT,
                                    patternSize + 1, pTreeForm);
         if (rc == PMD_RC_OK)
         {
            rc = traverse_huffman_tree(pHuffman, pEncoding, pEntry->right,
                                       (bitPattern << 1) + HUFFMAN_TREE_RIGHT,
                                       patternSize + 1, pTreeForm);
         }
      }
   }
   else
   {
      /* It's a leaf. Find it in the encoding table and store the given pattern there */
      encoding_entry *pEntry = lookup_encoding(pEncoding, token);
      pEntry->bitpattern = bitPattern;
      pEntry->nBits = patternSize;

      rc = pmd_append_bits(pTreeForm, HUFFMAN_TREE_LEAF, 1);
   }

   return rc;
}


/* ========================================================================= */
/*  extract_huffman_token */

/*  Extracts the token with the lowest frequency from the Huffman table.
    The token is removed from the table, and responsibility of deallocation
    of the table entry passes to the caller. This method returns NULL if
    no more tokens exist in the table.
*/

LOCAL huffman_frequency_entry *extract_huffman_token(huffman_table *pHuffman)
{
   huffman_frequency_entry *pEntry = NULL;

   /* First try the frequency table */
   for ( ; pHuffman->minFrequency <= pHuffman->maxFrequency; pHuffman->minFrequency++)
   {
      if (pHuffman->arrFrequencies[pHuffman->minFrequency])
      {
         huffman_frequency_entry *pResult = pHuffman->arrFrequencies[pHuffman->minFrequency];
         pHuffman->arrFrequencies[pHuffman->minFrequency] = pResult->pNext;
         pResult->pNext = NULL;
         return pResult;
      }
   }

   /* Then try the high-frequency list */
   pEntry = pHuffman->pHighFrequency;
   if (pEntry == NULL)
   {
      return NULL;
   }
   pHuffman->pHighFrequency = pEntry->pNext;
   if (pEntry->pNext == NULL)
   {
      pHuffman->pLastHighFrequency = NULL;
   }
   else
   {
      pEntry->pNext = NULL;
   }

   return pEntry;
}


/* ========================================================================= */
/*  extract_huffman_tree */

/*  Extracts the form of the Huffman decoding tree from the given bit buffer.
    All nodes in the tree are allocated on the given heap.
*/

LOCAL int extract_huffman_tree(pmd_heap_handle *heap,
                               pmd_bit_buffer *pTreeForm,
                               huffman_node **ppRoot)
{
   /* Retrieve the next bit making up the form of the tree */
   int bit = PMD_EXTRACT_BIT(pTreeForm);
   if (bit < PMD_LOWEST_SUCCESSFUL_RETURN)
   {
      return PMD_RC_INTERNAL_LIMIT_REACHED;
   }

   /* Allocate and initialise space for the next node in the decoding tree */
   *ppRoot = pmd_heap_alloc_h(heap, sizeof(huffman_node));
   if (*ppRoot == NULL)
   {
      return PMD_RC_NO_MEMORY;
   }

   /* Recurse or end depending on the form of the tree */
   if (bit == HUFFMAN_TREE_LEAF)
   {
      (*ppRoot)->leaf.is_leaf = 1;
   }
   else
   {
      int rc = PMD_RC_OK;
      assert(bit == HUFFMAN_TREE_NODE);
      rc = extract_huffman_tree(heap, pTreeForm, &(*ppRoot)->node.pLeft);
      if (rc == PMD_RC_OK)
      {
         rc = extract_huffman_tree(heap, pTreeForm, &(*ppRoot)->node.pRight);
      }
      if (rc != PMD_RC_OK)
      {
         *ppRoot = NULL;
         return rc;
      }
   }

   return PMD_RC_OK;
}


/* ============================================================================================= */
/* Global functions */
/* ============================================================================================= */


/* ========================================================================= */
/*  pmd_release_bits */

/*  Releases a bit buffer allocated with pmd_allocate_bits
*/

int pmd_release_bits(pmd_bit_buffer *pBuffer)
{
   free(pBuffer->pBits);
   pBuffer->pBits = NULL;
   pBuffer->curSize = 0;
   pBuffer->maxSize = 0;
   pBuffer->getSize = 0;
   pBuffer->buffer = 0;
   pBuffer->bufferSize = 0;
   return PMD_RC_OK;
}


/* ========================================================================= */
/*  pmd_release_tokens */

/*  Releases a token buffer allocated with pmd_allocate_tokens
*/

int pmd_release_tokens(pmd_token_buffer *pBuffer)
{
   free(pBuffer->pTokens);
   pBuffer->pTokens = NULL;
   pBuffer->curSize = 0;
   pBuffer->maxSize = 0;
   pBuffer->getSize = 0;
   free(pBuffer->pOverflowBuffer);
   pBuffer->pOverflowBuffer = NULL;
   pBuffer->curOverflowSize = 0;
   pBuffer->maxOverflowSize = 0;
   return PMD_RC_OK;
}


/* ========================================================================= */
/*  pmd_clear_tokens */

/*  Resets the put and get pointers without changing the allocations
*/
int pmd_clear_tokens(pmd_token_buffer *pBuffer)
{
   pBuffer->curOverflowSize = 0;
   pBuffer->curSize = 0;
   pBuffer->getSize = 0;
   return PMD_RC_OK;
}


/* ========================================================================= */
/*  pmd_append_bits */

/*  Appends the given bits to the given bit buffer.
*/

int pmd_append_bits(pmd_bit_buffer *pBuffer, unsigned int bits, unsigned int nBits)
{
   unsigned int unfilledBits = 8 - (pBuffer->curSize & 7);
   assert(nBits == 32 || !(bits & ((~0) << nBits)));

   /* Ensure sufficient space in the buffer */
   if (pBuffer->curSize + nBits > pBuffer->maxSize)
   {
      unsigned int newSize = pBuffer->maxSize + INITIAL_BIT_BUFFER_SIZE;
      unsigned char *pNewData = realloc(pBuffer->pBits, BIT_BUFFER_ALLOC_ROUND(newSize));
      if (!pNewData)
      {
         return PMD_RC_NO_MEMORY;
      }
      pBuffer->pBits = pNewData;
      pBuffer->maxSize = newSize;
      memset(pBuffer->pBits + BIT_BUFFER_ALLOC_ROUND(pBuffer->curSize), 0, 
             BIT_BUFFER_ALLOC_ROUND(newSize) - BIT_BUFFER_ALLOC_ROUND(pBuffer->curSize));
   }

   /* Fill any unfilled byte in the bit buffer */
   if (pBuffer->curSize & 7)
   {
      if (nBits <= unfilledBits)
      {
         /* We're adding so few bits that we won't overflow the current byte */
         pBuffer->pBits[pBuffer->curSize >> 3] |= bits << (unfilledBits - nBits);
         pBuffer->curSize += nBits;
         return PMD_RC_OK;
      }

      /* First fill the current byte, then let the byte aligned case handle
         the remaining bits */
      pBuffer->pBits[pBuffer->curSize >> 3] |= (unsigned char) (bits >> (nBits - unfilledBits));
      nBits -= unfilledBits;
      pBuffer->curSize += unfilledBits;
      /* We're leaving bits behind in bits, but they shouldn't hurt */
   }

   /* Here we have an integral number of bytes in the buffer, and add all whole bytes */
   while (nBits >= 8)
   {
      assert((pBuffer->curSize & 7) == 0);
      nBits -= 8;
      pBuffer->pBits[pBuffer->curSize >> 3] = (unsigned char) (bits >> nBits);
      pBuffer->curSize += 8;
   }

   /* At this point, we add any remaining bits */
   if (nBits > 0)
   {
      assert((pBuffer->curSize & 7) == 0);
      pBuffer->pBits[pBuffer->curSize >> 3] = (unsigned char) (bits << (8 - nBits));
      pBuffer->curSize += nBits;
   }

   return PMD_RC_OK;
}

/* ========================================================================= */
/* pmd_append_token */

/* Appends a token with the given type and value to the given token buffer
*/

int pmd_append_token(pmd_token_buffer *pBuffer, unsigned int type, unsigned int value)
{
    unsigned int token = PMD_INVALID_COMPACT_TOKEN;
    unsigned int rc = PMD_RC_OK;

    /* Ensure sufficient space in the buffer */
    if (pBuffer->curSize >= pBuffer->maxSize)
    {
        rc = realloc_tokens(pBuffer, pBuffer->maxSize + INITIAL_TOKEN_BUFFER_SIZE);
        if (rc != PMD_RC_OK)
        {
            return rc;
        }
    }

    rc = create_token(pBuffer, type, value, &token);
    if (rc != PMD_RC_OK)
    {
        return rc;
    }

    /* Append new data to the end of the buffer */
    pBuffer->pTokens[pBuffer->curSize] = token;
    pBuffer->curSize++;
    return PMD_RC_OK;
}


/* ========================================================================= */
/*  pmd_get_byte_count */

/*  Retrieves the number of bytes stored in the given bit buffer. If include_padding
    is non-zero, the count includes any incomplete byte at the end. Unused bits
    in this byte are set to zero. If include_padding is zero, the count only
    includes completely filled bytes. The pmd_extract_bytes function can be used
    to extract the bytes from the buffer.
*/

int pmd_get_byte_count(pmd_bit_buffer *pBuffer, int include_padding)
{
   if (include_padding)
   {
      return (pBuffer->curSize + 7) >> 3;
   }
   return pBuffer->curSize >> 3;
}


/* ========================================================================= */
/*  pmd_get_byte_pointer */

/*  Simply returns the data pointer
*/

unsigned char *pmd_get_byte_pointer(pmd_bit_buffer *pBuffer)
{
   return pBuffer->pBits;
}


/* ========================================================================= */
/*  pmd_remove_bytes */

/*  Removes the given number of bytes from the input. The count may include
    any last unfilled byte.
*/

int pmd_remove_bytes(pmd_bit_buffer *pBuffer, unsigned int nBytes)
{
    /* Handle the case where everything is removed */
    unsigned int nBytesInBuffer = (pBuffer->curSize + 7) >> 3;
    if (nBytes == nBytesInBuffer)
    {
        pBuffer->curSize = 0;
        pBuffer->getSize = 0;
        pBuffer->bufferSize = 0;
        return PMD_RC_OK;
    }
    else if (nBytes > nBytesInBuffer)
    {
        /* Handle the case where we don't have all that's requested */
        return PMD_RC_NO_MORE_DATA;
    }

    /* Handle the case where we have something remaining */
    memmove(pBuffer->pBits, pBuffer->pBits + nBytes, nBytesInBuffer - nBytes);
    if (pBuffer->getSize >= nBytes << 3)
    {
        pBuffer->getSize -= nBytes << 3;
        if (pBuffer->bufferSize > pBuffer->getSize)
        {
            /* The removed extended from somewhere in the get buffer */
            pBuffer->bufferSize = pBuffer->getSize;
        }
    }
    else
    {
        pBuffer->getSize = 0;
        pBuffer->bufferSize = 0;
    }
    pBuffer->curSize -= nBytes << 3;
    return PMD_RC_OK;
}


/* ========================================================================= */
/*  pmd_get_remaining_bits */

/*  Returns the number of bits remaining to be read in the buffer
*/

int pmd_get_remaining_bits(pmd_bit_buffer *pBuffer)
{
   return pBuffer->bufferSize + pBuffer->curSize - pBuffer->getSize;
}


/* ========================================================================= */
/*  pmd_compress_tokens */

/*  This function compresses the symbols given in pUncompressed, and places the
    resulting tokens in pCompressed. pCompressed should be initialised on entry,
    but should not contain any symbols. The input token buffer should consist
    only of symbols; otherwise compression or decompression will fail unpredictably.
*/

int pmd_compress_tokens(pmd_token_buffer *pUncompressed, pmd_token_buffer *pCompressed)
{
   int rc = PMD_RC_OK;
   pmd_compact_token *pSource = pUncompressed->pTokens;
   pmd_compact_token *pEnd = pUncompressed->pTokens + pUncompressed->curSize;
   pmd_compact_token *pCurrent = pSource;
   unsigned int hash_index = 0;
   hash_bucket *pLastKnownString = NULL;
   unsigned int nextCode = CODE_FIRST_FREE;
   unsigned int nCodeSize = INITIAL_CODE_SIZE;
   hash_bucket **ppBuckets;
   unsigned int emit_code = 0;

   /* Initialise compression data */
   ppBuckets = calloc(COMPRESSION_TABLE_SIZE, sizeof(hash_bucket *));

   /* Main compression loop */
   for ( ; pSource != pEnd; pSource++)
   {
      /* Variables local to loop */
      hash_bucket *pBucket = NULL;
      hash_bucket *pFollow = NULL;
      unsigned int nTokens = pSource - pCurrent + 1;
      int found = 0;

      /*** Determine if the already have a definition for the current string ***/

      hash_index = ((hash_index * HASH_FACTOR) ^ *pSource) % COMPRESSION_TABLE_SIZE;
      if (pSource == pCurrent)
      {
         /* We have only one token. Keep on adding. */
         continue;
      }

      /* Search for the string in the current hash bucket */
      pBucket = ppBuckets[hash_index];
      while (pBucket)
      {
         if (pBucket->nTokens == nTokens &&
             memcmp(pBucket->pTokens, pCurrent, nTokens*sizeof(pmd_compact_token)) == 0)
         {
            /* We already have this string. Break the search loop to keep on adding. */
            found = 1;
            break;
         }
         pFollow = pBucket;
         pBucket = pBucket->pNext;
      }
      if (found)
      {
         /* We already have this string. Keep on adding. */
         pLastKnownString = pBucket;
         continue;
      }

      /*** Insert the new string into our table ***/

      /* Create a new hash bucket */
      pBucket = (hash_bucket *) malloc(sizeof(hash_bucket));
      pBucket->pTokens = pCurrent;
      pBucket->nTokens = nTokens;
      pBucket->nCode = nextCode++;
      pBucket->pNext = NULL;

      /* Insert it into the bucket list for this hash value */
      if (pFollow)
      {
         pFollow->pNext = pBucket;
      }
      else
      {
         ppBuckets[hash_index] = pBucket;
      }

      /*** Output the compression code for the last known string ***/

      /* Find the code for the previous token or string */
      if (nTokens == 2)
      {
         rc = PMD_APPEND_COMPACT_TOKEN(pCompressed, *pCurrent, pUncompressed);
      }
      else
      {
         rc = PMD_APPEND_TOKEN(pCompressed, PMD_TOKEN_TYPE_CODE, pLastKnownString->nCode);
      }
      if (rc != PMD_RC_OK)
      {
         break;
      }

      /* Update the compression code size */
      if (nextCode >= (1U << nCodeSize))
      {
         nCodeSize++;
         rc = PMD_APPEND_TOKEN(pCompressed, PMD_TOKEN_TYPE_CODE_SIZE_CHANGE, nCodeSize);
         if (rc != PMD_RC_OK)
         {
            break;
         }
      }

      /* Update the current prefix */
      pCurrent = pSource;
      hash_index = (*pCurrent) % COMPRESSION_TABLE_SIZE;
   }

   /*** Output the compression code for the final string and end code ***/

   if (rc == PMD_RC_OK)
   {
      unsigned int nSymbols = pSource - pCurrent;

      /* Find the code for the previous token or string */
      if (nSymbols == 1)
      {
         rc = PMD_APPEND_COMPACT_TOKEN(pCompressed, *pCurrent, pUncompressed);
      }
      else if (nSymbols > 1)
      {
         rc = PMD_APPEND_TOKEN(pCompressed, PMD_TOKEN_TYPE_CODE, pLastKnownString->nCode);
      }

      /* Update the compression code size in order to accomodate the END code */
      if (rc == PMD_RC_OK && nextCode+1 >= (1U << nCodeSize))
      {
         nCodeSize++;
         rc = PMD_APPEND_TOKEN(pCompressed, PMD_TOKEN_TYPE_CODE_SIZE_CHANGE, nCodeSize);
      }
   }

   if (rc == PMD_RC_OK)
   {
      rc = PMD_APPEND_TOKEN(pCompressed, PMD_TOKEN_TYPE_CODE, CODE_END);
   }

   /* Clean up memory usage */
   for (emit_code = 0; emit_code < COMPRESSION_TABLE_SIZE; emit_code++)
   {
      hash_bucket *pCurrent = ppBuckets[emit_code];
      while (pCurrent)
      {
         hash_bucket *pToDelete = pCurrent;
         pCurrent = pCurrent->pNext;
         free(pToDelete);
      }
   }
   free(ppBuckets);
   if (rc != PMD_RC_OK)
   {
      pmd_release_tokens(pCompressed);
   }

   return rc;
}


/* ========================================================================= */
/*  7.4 pmd_uncompress_tokens */

/*  This function uncompresses the symbols given in pCompressed, and places the
    resulting tokens in pUncompressed. pUncompressed should be initialised on entry,
    but should not contain any symbols.
*/

int pmd_uncompress_tokens(pmd_token_buffer *pCompressed, pmd_token_buffer *pUncompressed)
{
    int rc = PMD_RC_OK;
    pmd_compact_token *pSource = pCompressed->pTokens;
    pmd_compact_token *pEnd = pCompressed->pTokens + pCompressed->curSize;
    unsigned int maxCodeSize = INITAL_DECOMPRESSION_SIZE;
    unsigned int curCodeSize = CODE_FIRST_FREE;
    unsigned int prefixIndex = 0;
    unsigned int prefixLength = 0;

    /* Allocate decompression table */
    decompression_entry *pCodeTable = malloc(maxCodeSize * sizeof(decompression_entry));
    if (!pCodeTable)
    {
        return PMD_RC_NO_MEMORY;
    }

    /* Ensure that we only need to copy the compact tokens */
    rc = copy_overflow_tokens(pUncompressed, pCompressed);
    if (rc != PMD_RC_OK)
    {
        return rc;
    }

    /* Main uncompression loop */
    for ( ; pSource != pEnd; pSource++)
    {
        pmd_compact_token firstToken = 0;
        unsigned int nextPrefixIndex = pUncompressed->curSize;
        unsigned int nextPrefixLength = 0;

        /* Output uncompressed tokens */
        unsigned int tokenType = PMD_GET_TOKEN_TYPE(pCompressed, *pSource);
        if (tokenType == PMD_TOKEN_TYPE_SYMBOL)
        {
            rc = PMD_APPEND_COMPACT_TOKEN(pUncompressed, *pSource, pCompressed);
            firstToken = *pSource;
        }
        else if (tokenType == PMD_TOKEN_TYPE_CODE)
        {
            unsigned int code = PMD_GET_TOKEN_VALUE(pCompressed, *pSource);
            if (code < CODE_FIRST_FREE || code >= curCodeSize)
            {
                /* It's either an invalid code or some special case */
                if (code == curCodeSize)
                {
                    /* The code is the one we're about to add later in this loop */
                    firstToken = pUncompressed->pTokens[prefixIndex];
                    rc = append_own_tokens(pUncompressed, prefixIndex, prefixLength);
                    if (rc == PMD_RC_OK)
                    {
                        rc = PMD_APPEND_COMPACT_TOKEN(pUncompressed, firstToken, pUncompressed);

                    }
                }
                else if (code == CODE_END)
                {
                    /* We're at the end of this compression session. End the loop */
                    break;
                }
                else
                {
                    /* It's not a special case, so the code must be invalid */
                    rc = PMD_RC_BAD_INPUT;
                }
            }
            else 
            {
                /* The code is in our table */
                decompression_entry *pEntry = &pCodeTable[code];
                firstToken = pUncompressed->pTokens[pEntry->tokenIndex];
                rc = append_own_tokens(pUncompressed, pEntry->tokenIndex, pEntry->nTokens);
            }
        }
        else
        {
            assert(tokenType == PMD_TOKEN_TYPE_CODE_SIZE_CHANGE);
        }
        if (rc != PMD_RC_OK)
        {
            break;
        }
        nextPrefixLength = pUncompressed->curSize - nextPrefixIndex;

        /* Maintain code table */
        if (prefixLength > 0)
        {
            if (curCodeSize == maxCodeSize)
            {
                unsigned int newSize = maxCodeSize * 2;
                decompression_entry *pNewTable =
                        realloc(pCodeTable, newSize * sizeof(decompression_entry));
                if (!pNewTable)
                {
                    rc = PMD_RC_NO_MEMORY;
                    break;
                }
                pCodeTable = pNewTable;
                maxCodeSize = newSize;
            }
            pCodeTable[curCodeSize].nTokens = prefixLength+1;
            pCodeTable[curCodeSize].tokenIndex = prefixIndex;
            curCodeSize++;
        }

        /* Update next prefix */
        prefixIndex = nextPrefixIndex;
        prefixLength = nextPrefixLength;
    }

    /* Check that we stopped at the final end code */
    if (rc == PMD_RC_OK && pSource != pEnd - 1)
    {
        rc = PMD_RC_BAD_INPUT;
    }

    /* Free allocated memory */
    free(pCodeTable);
    if (rc != PMD_RC_OK)
    {
        pmd_release_tokens(pCompressed);
    }

    return rc;
}



/* ========================================================================= */
/*  pmd_encode_tokens */

/*  Encodes the given token buffer into a bit buffer.
*/

int pmd_encode_tokens(pmd_token_buffer *pUncoded, pmd_bit_buffer *pEncoded)
{
   huffman_table huffman = { 0 };
   encoding_table encoding = { 0 };
   encoding_entry *pCollectedSymbol = NULL;
   encoding_entry *pCollectedCode = NULL;

   /* Determine the frequencies of the used tokens */
   int rc = allocate_encoding_table(&encoding);
   if (rc == PMD_RC_OK)
   {
      rc = add_tokens_to_encoding(pUncoded, &encoding);
   }

   /* Create Huffman table to be filled in below */
   if (rc == PMD_RC_OK)
   {
      rc = allocate_huffman_table(&huffman);
   }

   /* Mark some of the tokens as shared tokens */
   if (rc == PMD_RC_OK)
   {
      rc = collect_shared_tokens(pUncoded, &encoding, &huffman);
   }

   /* Build the Huffman code tree */
   if (rc == PMD_RC_OK)
   {
      rc = build_huffman_tree(&huffman);
   }

   /* Update the encoding table with the patterns from Huffman coding,
      and get the form of the Huffman tree output as well. */
   if (rc == PMD_RC_OK)
   {
      huffman_frequency_entry *pEntry = extract_huffman_token(&huffman);
      rc = traverse_huffman_tree(&huffman, &encoding, pEntry->token, 0, 0, pEncoded);
      free(pEntry);
   }

   /* At this point we don't need the Huffman tree anymore. Kill it to save memory */
   if (rc == PMD_RC_OK)
   {
      rc = release_huffman_table(&huffman);
      memset(&huffman, 0, sizeof(huffman));
   }

   /* Look up the encodings for the collected symbols and codes */
   if (rc == PMD_RC_OK)
   {
      pCollectedSymbol = lookup_encoding(&encoding,
                              PMD_CREATE_COMPACT_TOKEN(PMD_TOKEN_TYPE_COLLECTED_SYMBOL, 0));
      pCollectedCode = lookup_encoding(&encoding,
                              PMD_CREATE_COMPACT_TOKEN(PMD_TOKEN_TYPE_COLLECTED_CODE, 0));
   }

   /* Encode every token in turn */
   if (rc == PMD_RC_OK)
   {
      unsigned int tokenIndex = 0;
      unsigned int codeSize = INITIAL_CODE_SIZE;
      for (tokenIndex = 0; tokenIndex < pUncoded->curSize; tokenIndex++)
      {
         /* Find the encoding entry for the token */
         pmd_compact_token token = pUncoded->pTokens[tokenIndex];
         unsigned int tokenType = PMD_GET_TOKEN_TYPE(pUncoded, token);
         encoding_entry *pEntry = NULL;

         /* Handle code size tokens. */
         if (tokenType == PMD_TOKEN_TYPE_CODE_SIZE_CHANGE)
         {
            codeSize++;
            continue; /* We shouldn't output anything here */
         }

         pEntry = lookup_encoding(&encoding, token);

         /* Check if the token has its own separate code */
         if (pEntry->nBits == 0)
         {
            if (tokenType == PMD_TOKEN_TYPE_CODE)
            {
               tokenType = PMD_TOKEN_TYPE_COLLECTED_CODE;
               pEntry = pCollectedCode;
            }
            else
            {
               assert(tokenType == PMD_TOKEN_TYPE_SYMBOL);
               tokenType = PMD_TOKEN_TYPE_COLLECTED_SYMBOL;
               pEntry = pCollectedSymbol;
            }
         }

         /* Output the bit pattern for the token */
         rc = pmd_append_bits(pEncoded, pEntry->bitpattern, pEntry->nBits);
         if (rc != PMD_RC_OK)
         {
            break;
         }

         /* Check if this is the first use, and add token type if so */
         if (!pEntry->used)
         {
            /* Output the token type */
            rc = pmd_append_bits(pEncoded, tokenType, TOKEN_TYPE_SIZE);
            if (rc != PMD_RC_OK)
            {
               break;
            }
         }

         /* Output values for tokens and codes */
         if (tokenType == PMD_TOKEN_TYPE_COLLECTED_CODE ||
             (tokenType == PMD_TOKEN_TYPE_CODE && !pEntry->used))
         {
            /* Output the value with the number of bits given by the current code size */
            assert(PMD_GET_TOKEN_VALUE(pUncoded, token) < (1U << codeSize));
            rc = pmd_append_bits(pEncoded, PMD_GET_TOKEN_VALUE(pUncoded, token), codeSize);
            if (rc != PMD_RC_OK)
            {
               break;
            }
         }
         else if (tokenType == PMD_TOKEN_TYPE_COLLECTED_SYMBOL ||
                  (tokenType == PMD_TOKEN_TYPE_SYMBOL && !pEntry->used))
         {
            /* Output the required number of bits in the value minus one stored in
               five bits, followed by the value stored as follows:
               - If the size field is zero, corresponding to 1 bit, one bit is stored.
               - Otherwise, the number of bits in the size field is stored.
               This will typically erase the most significant bit, but only in
               the cases where this bit is 1. Thus, we can restore it at decoding. */

            /* First determined the number of bits required for the value */
            unsigned int nRequiredBits = 0;
            unsigned int value = PMD_GET_TOKEN_VALUE(pUncoded, token);
            unsigned int testValue = value;
            if (testValue == 0)
            {
               nRequiredBits = 1;
            }
            else
            {
               do
               {
                  nRequiredBits++;
                  testValue >>= 1;
               }
               while (testValue != 0);
            }

            /* Then encode the bit count followed by the value */
            assert(nRequiredBits > 0 && nRequiredBits <= (1 << SYMBOL_BIT_COUNT_SIZE));
            assert(nRequiredBits == 32 || value < (1U << nRequiredBits));
            rc = pmd_append_bits(pEncoded, nRequiredBits-1, SYMBOL_BIT_COUNT_SIZE);
            if (rc == PMD_RC_OK)
            {
               if (nRequiredBits > 1)
               {
                  /* Don't store the most significant bit with the value 1. */
                  assert(value & (1 << (nRequiredBits - 1)));
                  value &= ~((~0) << (nRequiredBits - 1));
                  rc = pmd_append_bits(pEncoded, value, nRequiredBits-1);
               }
               else
               {
                  /* We don't know what value the most significant bit has. Store them all. */
                  rc = pmd_append_bits(pEncoded, value, nRequiredBits);
               }
            }
            if (rc != PMD_RC_OK)
            {
               break;
            }
         }

         /* Update the used flag */
         pEntry->used = 1;
      }
   }

   /* Clean up and return */
   release_encoding_table(&encoding);
   release_huffman_table(&huffman);
   if (rc != PMD_RC_OK)
   {
      pmd_release_bits(pEncoded);
   }

   return rc;
}


/* ========================================================================= */
/*  pmd_decode_tokens */

/*  Decodes the bit buffer into tokens. Decoding stops just after the
    END code has been extracted.
*/

int pmd_decode_tokens(pmd_bit_buffer *pEncoded, pmd_token_buffer *pDecoded)
{
    unsigned int nCodeSize = INITIAL_CODE_SIZE;
    unsigned int lastCode = CODE_FIRST_FREE;
    huffman_node *pRoot = NULL;
    int rc = PMD_RC_OK;

    /* Create a local heap for the Huffman nodes */
    pmd_heap_handle* heap = pmd_heap_init_h(INITIAL_HUFFMAN_TREE_BYTES);
    if (heap == NULL)
    {
        return PMD_RC_NO_MEMORY;
    }

    /* Extract the Huffman tree from the input stream */
    rc = extract_huffman_tree(heap, pEncoded, &pRoot);
    if (rc != PMD_RC_OK)
    {
        pmd_heap_free_h(heap);
        return rc;
    }

    /* Repeat until we reach the end code */
    for (;;)
    {
        /* Retrieve the next code from the input */
        huffman_node *pCurrent = pRoot;
        unsigned int *pValue = NULL;
        while (!pCurrent->leaf.is_leaf)
        {
            /* Retrieve the next bit of the code from the input */
            int bit = PMD_EXTRACT_BIT(pEncoded);
            if (bit < PMD_LOWEST_SUCCESSFUL_RETURN)
            {
                pmd_heap_free_h(heap);
                pmd_release_tokens(pDecoded);
                return bit;
            }

            /* Move to the appropriate child */
            if (bit == HUFFMAN_TREE_LEFT)
            {
                pCurrent = pCurrent->node.pLeft;
            }
            else
            {
                pCurrent = pCurrent->node.pRight;
            }
        }

        /* Check if this is the first time we see this Huffman code */
        if (!pCurrent->leaf.used)
        {
            /* It's the first time. Extract the token type */
            rc = extract_bits(pEncoded, TOKEN_TYPE_SIZE, &pCurrent->leaf.token.type);
            if (rc != PMD_RC_OK)
            {
                break;
            }

            /* Update the used flag and make sure we retrieve the value */
            pCurrent->leaf.used = 1;
            pValue = &pCurrent->leaf.token.value;
        }

        /* Always extract the value for collected tokens */
        if (pCurrent->leaf.token.type == PMD_TOKEN_TYPE_COLLECTED_SYMBOL ||
            pCurrent->leaf.token.type == PMD_TOKEN_TYPE_COLLECTED_CODE)
        {
            pValue = &pCurrent->leaf.token.value;
        }

        /* Check if the value should be extracted */
        if (pValue)
        {
            /* It should. Extract code values and symbols values in different ways */
            if (pCurrent->leaf.token.type == PMD_TOKEN_TYPE_SYMBOL ||
                pCurrent->leaf.token.type == PMD_TOKEN_TYPE_COLLECTED_SYMBOL)
            {
                /* The symbol is a fixed size bit count, followed by the value.
                   The size of the value field is interpreted as follows:
                   - If nBits is zero, the value is stored in one bit.
                   - If nBits is non-zero, the value is stored as that number
                     of bits. A most siginificant bit of 1 should be added on
                     top of that number */
                unsigned int nBits = 0;
                rc = extract_bits(pEncoded, SYMBOL_BIT_COUNT_SIZE, &nBits);
                if (rc != PMD_RC_OK)
                {
                    break;
                }

                /* Now extract the appropriate number of bits */
                if (nBits == 0)
                {
                    rc = extract_bits(pEncoded, 1, pValue);
                }
                else
                {
                    rc = extract_bits(pEncoded, nBits, pValue);
                    *pValue |= 1 << nBits;
                }
                if (rc != PMD_RC_OK)
                {
                    break;
                }
            }
            else
            {
                /* The code is a fixed size value, based on the current code size */
                assert(pCurrent->leaf.token.type == PMD_TOKEN_TYPE_CODE ||
                       pCurrent->leaf.token.type == PMD_TOKEN_TYPE_COLLECTED_CODE);
                rc = extract_bits(pEncoded, nCodeSize, pValue);
                if (rc != PMD_RC_OK)
                {
                    break;
                }

                /* We never see the end code twice, so this is a good place to
                   check for it */
                if (*pValue == CODE_END)
                {
                    rc = pmd_append_token(pDecoded, PMD_TOKEN_TYPE_CODE, CODE_END);
                    break;
                }
            }
        }

        /* Insert the retrieved token into the output buffer */
        if (pCurrent->leaf.token.type == PMD_TOKEN_TYPE_SYMBOL ||
            pCurrent->leaf.token.type == PMD_TOKEN_TYPE_COLLECTED_SYMBOL)
        {
            rc = pmd_append_token(pDecoded, PMD_TOKEN_TYPE_SYMBOL, pCurrent->leaf.token.value);
        }
        else
        {
            assert(pCurrent->leaf.token.type == PMD_TOKEN_TYPE_CODE ||
                   pCurrent->leaf.token.type == PMD_TOKEN_TYPE_COLLECTED_CODE);
            rc = pmd_append_token(pDecoded, PMD_TOKEN_TYPE_CODE, pCurrent->leaf.token.value);
        }
        if (rc != PMD_RC_OK)
        {
            break;
        }

        /* Update the code size. We assume, that for every time a token is output
           by the Lempel-Zip compression, a code has been added. Otherwise, we can't
           do decoding separate from decompression. */
        if (++lastCode == (1U << nCodeSize))
        {
            nCodeSize++;
        }
    }

    /* Check if an error occurred, and clean up */
    if (rc != PMD_RC_OK)
    {
        pmd_release_tokens(pDecoded);
    }
    pmd_heap_free_h(heap);

    return rc;
}


/* ========================================================================= */
/*  pmd_compress_block */

/*  Compresses and encodes the given tokens. Adds an end code to the compressed
    output.
*/

int pmd_compress_block(pmd_token_buffer *pUncompressed, pmd_bit_buffer *pCompressed)
{
   /* Compress the given tokens */
   pmd_token_buffer compressed = PMD_INITIAL_TOKEN_BUFFER;
   int rc = pmd_compress_tokens(pUncompressed, &compressed);
   if (rc != PMD_RC_OK)
   {
      return rc;
   }

   /* Encode the compressed tokens and return */
   rc = pmd_encode_tokens(&compressed, pCompressed);
   
   pmd_release_tokens(&compressed);
   return rc;
}


/* ========================================================================= */
/*  pmd_uncompress_block */

/*  Decodes the tokens up to and including the next clear or end code, and uncompresses
    the decoded tokens.
*/

int pmd_uncompress_block(pmd_bit_buffer *pCompressed, pmd_token_buffer *pUncompressed)
{
   /* Decode the next block */
   pmd_token_buffer compressed = PMD_INITIAL_TOKEN_BUFFER;
   int rc = pmd_decode_tokens(pCompressed, &compressed);
   if (rc != PMD_RC_OK)
   {
      return rc;
   }

   /* Uncompress the decoded tokens and return */
   rc = pmd_uncompress_tokens(&compressed, pUncompressed);
   pmd_release_tokens(&compressed);
   return rc;
}


/* ========================================================================= */
/*  pmd_print_tokens */

/*  This function dumps the given token buffer to the given C stream.
    It's only used for debugging.
*/

int pmd_print_tokens(pmd_token_buffer *pTokens, FILE *pStream)
{
   unsigned int index;
   for (index = 0; index < pTokens->curSize; index++)
   {
      /* Retrieve token type and value */
      unsigned int tokenType = PMD_GET_COMPACT_TOKEN_TYPE(pTokens->pTokens[index]);
      unsigned int tokenValue = PMD_GET_COMPACT_TOKEN_VALUE(pTokens->pTokens[index]);
      if (tokenType == PMD_TOKEN_TYPE_OVERFLOW)
      {
         if (tokenValue == PMD_MAX_COMPACT_TOKEN_VALUE)
         {
            fprintf(pStream, "Invalid token\n");
            continue;
         }
         tokenType = pTokens->pOverflowBuffer[tokenValue].type;
         tokenValue = pTokens->pOverflowBuffer[tokenValue].value;
      }

      /* Print human readable text for the token */
      switch (tokenType)
      {
      case PMD_TOKEN_TYPE_SYMBOL:
         fprintf(pStream, "Symbol %u\n", tokenValue);
         break;
      case PMD_TOKEN_TYPE_CODE:
         if (tokenValue == CODE_END)
         {
            fprintf(pStream, "CODE_END\n", tokenValue);
         }
         else if (tokenValue < CODE_FIRST_FREE)
         {
            fprintf(pStream, "*** Reserved code %u\n", tokenValue);
         }
         else
         {
            fprintf(pStream, "Code %u\n", tokenValue);
         }
         break;
      case PMD_TOKEN_TYPE_COLLECTED_SYMBOL:
         fprintf(pStream, "Collected symbol %u\n", tokenValue);
         break;
      case PMD_TOKEN_TYPE_COLLECTED_CODE:
         fprintf(pStream, "Collected %u\n", tokenValue);
         break;
      case PMD_TOKEN_TYPE_CODE_SIZE_CHANGE:
         fprintf(pStream, "Code size change\n");
         break;
      case PMD_TOKEN_TYPE_HUFFMAN_NODE:
         fprintf(pStream, "Huffman node: %u\n", tokenValue);
         break;
      default:
         fprintf(pStream, "*** Unkown token type (%u): %u ***\n", tokenType, tokenValue);
         break;
      }
   }
   return PMD_RC_OK;
}


/* ========================================================================= */
/*  pmd_print_bits */

/*  This function dumps the given bit buffer to the given C stream.
    It's only used for debugging.
*/

int pmd_print_bits(pmd_bit_buffer *pBits, FILE *pStream)
{
   unsigned int wholeByteEnd = pBits->curSize >> 3U;
   unsigned int index;

   /* Check for the empty stream */
   if (pBits->curSize == 0)
   {
      fprintf(pStream, "The bit buffer is empty\n");
      return PMD_RC_OK;
   }

   /* Output all whole bytes */
   for (index = 0; index < wholeByteEnd; index++)
   {
      unsigned char value = pBits->pBits[index];
      fprintf(pStream, "%6d : 0x%02X\n", index, value);
   }

   /* Output the remaining bits, if any */
   if (pBits->curSize & 7)
   {
      unsigned char value = pBits->pBits[pBits->curSize >> 3];
      fprintf(pStream, "%6d : 0x%02X  (%d bits valid)\n",
              index, value, pBits->curSize & 7);
   }

   if (pBits->getSize)
   {
      fprintf(pStream, "The get index is %u\n", pBits->getSize);
   }

   return PMD_RC_OK;
}


/* End of file pmd_compression2.c */
