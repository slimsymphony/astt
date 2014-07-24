/*
NOKIA                                                             CONFIDENTIAL
Beijing
Nokia / Engine / SW Memory SW
Ma Wenhua-Nancy



                  file_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        -

project path:    global_interface/coresw_interface/coresw_public

name:            file_isi.h

version:         033.000

type:            incl

instance:        -


ISI header file for File Server

Current   ISI Version : 033.000
Supported ISI Versions: 031.000, 032.000, 033.000

Generated with autogen version 12w33 on 17-Jan-2013 13:26:50
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 033.000    NON-DRAFT   08-Jun-2012    Ma Wenhua-Nancy
Reason      : A360 3267335: quota handler in file system
Reference   : ActionDB for SWAM CR: MN12060743395
Description : Added Message FILE2_DRIVE_QUOTA_IND
              Added Constant table FILE2_QUOTA_INFO

Version     : 032.000    NON-DRAFT   06-Sep-2012    Harri Turunen
Reason      : A360 3502216: Add new origin and remove obsolete APIs
Reference   : GIT Gerrit
Description : -

Version     : 031.000    NON-Jul-2012                Juha Angeria
Reason      : Remove obsolete and not supported APIs
Reference   : Evo cleanup
Description : -

------------------------------------------------------------------------------
*/

#ifndef _FILE_ISI_H
#define _FILE_ISI_H

#include "isi_conf.h"

#ifndef FILE_ISI_VERSION
#define FILE_ISI_VERSION
#define FILE_ISI_VERSION_Z  33
#define FILE_ISI_VERSION_Y   0
#endif

#define FILE_ISI_MIN_VERSION(z,y) \
 ((FILE_ISI_VERSION_Z == (z) && FILE_ISI_VERSION_Y >= (y)) || \
  (FILE_ISI_VERSION_Z > (z)))

#if !FILE_ISI_MIN_VERSION(31,0)
#error The specified interface version is not supported by this header file
#elif FILE_ISI_MIN_VERSION(33,1)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

/* constant for variable-length definitions */
#define FILE_ANY_SIZE                            1
#define FILE2_MIN_FILENAME_LEN                   0x04
#define FILE2_MAX_FILENAME_LEN                   0x0104

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_STATUS                                            */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_STATUS_CONST;

#define FILE2_OK                                 0x00  /* OK */
#define FILE2_FAIL                               0x01  /* Fail */
/* Not a valid file descriptor */
#define FILE2_EBADF                              0x02
/* Permission denied  */
#define FILE2_EACCES                             0x03
#define FILE2_EEXIST                             0x04  /* File exists  */
/* Too many open files for process  */
#define FILE2_EMFILE                             0x05
/* No such a file or directory  */
#define FILE2_ENOENT                             0x06
#define FILE2_ESHARE                             0x07  /* Sharing error  */
/* No space in a media */
#define FILE2_ENOSPC                             0x08
/* The file system is not ready */
#define FILE2_ENOTREADY                          0x09
/* Directory structure corrupted  */
#define FILE2_EBADDIR                            0x0A
/* File offset is negative  */
#define FILE2_EINVAL                             0x0B
/* An unspecified file system error  */
#define FILE2_EFAIL                              0x0C
/* OK, more data available  */
#define FILE2_MORE_DATA                          0x0D
/* Empty directory */
#define FILE2_EMPTY                              0x0E
/* HW failure in writing/reading */
#define FILE2_EIO                                0x0F
/* Offset out of bounds */
#define FILE2_OFFSET_ERROR                       0x10
/* Low level format has failed */
#define FILE2_FORMAT_FAIL                        0x11
/* File system initialization has failed */
#define FILE2_INIT_FAIL                          0x12
/* Creating predefined folders has failed */
#define FILE2_PREDEF_CREATE_FAIL                 0x13
/* Path contains illegal character/s */
#define FILE2_EINVALIDPATH                       0x14
/* Drive is blocked by another user */
#define FILE2_EACCESSDENIED                      0x15
/* Illegal search criteria */
#define FILE2_ILLEGAL_CRITERIA                   0x17
/* No space in root */
#define FILE2_EROOTFULL                          0x18
#define FILE2_EDEVICE                            0x19  /* No device */
/* A copyright item blocked the operation */
#define FILE2_COPYRIGHT_FILES                    0x1A

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_CLOSE_INFO                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_CLOSE_INFO_CONST;

/* User's must close this file  */
#define FILE2_CLOSE_MANUAL                       0x01

/* ----------------------------------------------------------------------- */
/* Bitmask Table: FILE2_ACCESS_FLAGS                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_ACCESS_FLAGS_CONST;

/* Open for reading only  */
#define FILE2_O_RDONLY                           0x00  /* -------- */
/* Open for writing only  */
#define FILE2_O_WRONLY                           0x01  /* -------1 */
/* Open for reading and writing  */
#define FILE2_O_RDWR                             0x02  /* ------1- */
/* Fail if already open, fail if another open is tried  */
#define FILE2_F_NOSHARE                          0x04  /* -----1-- */
/* Set append mode.  */
#define FILE2_O_APPEND                           0x08  /* ----1--- */
/* Create file if it does not exist  */
#define FILE2_O_CREAT                            0x10  /* ---1---- */
/* Truncate file  */
#define FILE2_O_TRUNC                            0x20  /* --1----- */
/* File creation fails if file already exist  */
#define FILE2_O_EXCL                             0x40  /* -1------ */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: FILE_SYSTEM_STATUS                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE_SYSTEM_STATUS_CONST;

/* No file system available */
#define FILE_NONE                                0x00  /* -------- */
/* FMAN file system */
#define FILE_FMAN                                0x01  /* -------1 */
/* File2 file system */
#define FILE_FILE2                               0x02  /* ------1- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: FILE2_MODE                                               */
/* ----------------------------------------------------------------------- */
typedef uint32 FILE2_MODE_CONST;

/* Write permitted  */
#define FILE2_S_IWUSR                            0x00000080  /* ------------------------1------- */
/* Read permitted  */
#define FILE2_S_IRUSR                            0x00000100  /* -----------------------1-------- */
/* Directory  */
#define FILE2_S_IFDIR                            0x00004000  /* -----------------1-------------- */
/* Regular */
#define FILE2_S_IFREG                            0x00008000  /* ----------------1--------------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: FILE2_FAT_ATTRIBUTES                                     */
/* ----------------------------------------------------------------------- */
typedef uint32 FILE2_FAT_ATTRIBUTES_CONST;

/* Normal/Regular file */
#define FILE2_ANORMAL                            0x00000000  /* -------------------------------- */
/* Read only */
#define FILE2_ARDONLY                            0x00000001  /* -------------------------------1 */
/* Hidden */
#define FILE2_AHIDDEN                            0x00000002  /* ------------------------------1- */
/* System file */
#define FILE2_ASYSTEM                            0x00000004  /* -----------------------------1-- */
/* The name of this file is actually the label for logical drive  */
#define FILE2_AVOLUME                            0x00000008  /* ----------------------------1--- */
/* Directory */
#define FILE2_ADIRENT                            0x00000010  /* ---------------------------1---- */
/* Archive bit */
#define FILE2_ARCHIVE                            0x00000020  /* --------------------------1----- */
/* Copyright protected file. Not supported in Multimedia Card (MMC). */
#define FILE2_ACOPYRIGHT                         0x00000040  /* -------------------------1------ */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: FILE2_TIMESTAMPS_TBL                                     */
/* ----------------------------------------------------------------------- */
typedef uint32 FILE2_TIMESTAMPS_TBL_CONST;

/* Set modification */
#define FILE2_MODIFICATION                       0x00000001  /* -------------------------------1 */
/* Set creation */
#define FILE2_CREATION                           0x00000002  /* ------------------------------1- */

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_INTERFACE_SELECTION                               */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_INTERFACE_SELECTION_CONST;

#define FILE2_FILESYSTEM                         0x01  /* Filesystem */
#define FILE2_SBIF                               0x02  /* SBIF */
#define FILE2_MAPPER                             0x03  /* MAPPER */
#define FILE2_SNOR                               0x04  /* SNOR */
#define FILE2_HW_MMC                             0x05  /* MMC */

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_MEASUREMENT_CASES                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_MEASUREMENT_CASES_CONST;

/* Write & Read 1 MB */
#define FILE2_WRITE_READ_1MB_CASE                0x01
/* Rewrite many files */
#define FILE2_REWRITE_MANY_FILES_CASE            0x02
/* Write small files */
#define FILE2_WRITE_SMALL_FILES_CASE             0x03
/* Rewrite 1 MB file */
#define FILE2_REWRITE_1MB_FILE_CASE              0x04
/* Write & Read 1 MB free */
#define FILE2_WRITE_READ_1MB_FREE_CASE           0x05
/* Diskwipe full memory */
#define FILE2_DISKWIPE_FULL_MEM_CASE             0x06
/* Read & Write various blocks */
#define FILE2_READ_WRITE_VARIOUS_BLOCK_CASE      0x07
/* Low level format */
#define FILE2_LOW_LEVEL_FORMAT_CASE              0xFF

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_DRIVE_TYPE                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_DRIVE_TYPE_CONST;

#define FILE2_DRIVE_USER                         0x00  /* USER drive */
#define FILE2_DRIVE_MEMCARD                      0x01  /* MEMCARD drive */
#define FILE2_DRIVE_SYSTEM                       0x03  /* SYSTEM drive */
#define FILE2_DRIVE_PPM                          0x04  /* PPM drive */
/* USB Mass storage drive. External drive for USER data */
#define FILE2_DRIVE_USB_MASS_STORAGE             0x05
/* SYSTEM_EMMC drive */
#define FILE2_DRIVE_SYSTEM_EMMC                  0x08
/* STORAGE_EMMC drive */
#define FILE2_DRIVE_STORAGE_EMMC                 0x09
/* Undefined drive */
#define FILE2_DRIVE_UNDEFINED                    0xFF

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_ITEM_INACCESSIBLE_REASON_TABLE                    */
/* ----------------------------------------------------------------------- */
typedef uint16 FILE2_ITEM_INACCESSIBLE_REASON_TABLE_CONST;

/* The file was deleted */
#define FILE2_FILE_DELETED                       0x0001
/* DRM usage rights has expired */
#define FILE2_DRM_RIGHTS_EXPIRED                 0x0002
/* The file could not be opened */
#define FILE2_FILE_NOT_FOUND                     0x0003
/* The memory card removed */
#define FILE2_MEM_CARD_REMOVED                   0x0004
/* USB Mass Storage connection (cable) has been removed */
#define FILE2_MSC_CONNECTION_REMOVED             0x0005
/* Memory card has been removed from a USB Mass Storage device */
#define FILE2_MSC_MEM_CARD_REMOVED               0x0006

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_FIM_EVENT_REASON_TABLE                            */
/* ----------------------------------------------------------------------- */
typedef uint16 FILE2_FIM_EVENT_REASON_TABLE_CONST;

/* The file has changed content */
#define FILE2_FILE_UPDATED                       0x0001
/* A removable drive has been reconnected and a file that was previously
   located on the drive is missing.
*/
#define FILE2_FILE_MISSING                       0x0002

/* ----------------------------------------------------------------------- */
/* Bitmask Table: FILE2_DELTREE_FORCE_MODE                                 */
/* ----------------------------------------------------------------------- */
typedef uint32 FILE2_DELTREE_FORCE_MODE_CONST;

/* If a read_only file/directory or an open file is encountered, the
   directory tree deletion is contiuned.
*/
#define FILE2_DELTREE_NONABORT                   0x00000001  /* -------------------------------1 */
/* If a read_only file/directory or an open file is encountered, the
   directory tree deletion is aborted.
*/
#define FILE2_DELTREE_ABORT_ON_ERROR             0x00000002  /* ------------------------------1- */
/* Delete also read-only items - use conjunction with FILE2_DELTREE_NONABORT
*/
#define FILE2_DELTREE_READ_ONLY_DELETE           0x00000004  /* -----------------------------1-- */
/* Deletes all but not system items. If used with
   FILE2_DELTREE_READ_ONLY_DELETE, read only system items will not be
   deleted.
*/
#define FILE2_DELTREE_NO_SYSTEM_ITEMS            0x00000008  /* ----------------------------1--- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: FILE2_SEARCH_INCLUDE                                     */
/* ----------------------------------------------------------------------- */
typedef uint16 FILE2_SEARCH_INCLUDE_CONST;

/* The search result must contain files. */
#define FILE2_INCLUDE_FILES                      0x0001  /* ---------------1 */
/* The search result must contain folders */
#define FILE2_INCLUDE_FOLDERS                    0x0002  /* --------------1- */
/* The search result must contain hidden items */
#define FILE2_INCLUDE_HIDDEN                     0x0004  /* -------------1-- */
/* Copyright files are excluded from search result */
#define FILE2_EXCLUDE_COPYRIGHT                  0x0008  /* ------------1--- */
/* Only predefined items are searched */
#define FILE2_PREDEFINED_ONLY                    0x0010  /* -----------1---- */
/* The search is used for counting items only. */
#define FILE2_COUNT_ONLY                         0x0040  /* ---------1------ */

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_HOTSWAP_STATUS_TBL                                */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_HOTSWAP_STATUS_TBL_CONST;

/* Memory card inserted */
#define FILE2_MEMORY_CARD_INSERTED               0x00
/* Memory card removed */
#define FILE2_MEMORY_CARD_REMOVED                0x01

/* ----------------------------------------------------------------------- */
/* Bitmask Table: FILE2_HOTSWAP_FLAGS                                      */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_HOTSWAP_FLAGS_CONST;

/* The status of the hot swap switch. */
#define FILE2_HOTSWAP_SWITCH_STATE               0x01  /* -------1 */

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_ITEM_ACCESSIBLE_REASON_TABLE                      */
/* ----------------------------------------------------------------------- */
typedef uint16 FILE2_ITEM_ACCESSIBLE_REASON_TABLE_CONST;

/* The memory card inserted */
#define FILE2_MEM_CARD_INSERTED                  0x0001

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_FILE_CHANGE_TYPES                                 */
/* ----------------------------------------------------------------------- */
typedef uint16 FILE2_FILE_CHANGE_TYPES_CONST;

/* A new file has been added */
#define FILE2_FILE_CHANGED_NEW                   0x0001
/* An existing file is modified */
#define FILE2_FILE_CHANGED_MODIFIED              0x0002
/* An existing item is renamed */
#define FILE2_FILE_CHANGED_RENAMED               0x0003

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_FILE_ORIGIN_TYPES                                 */
/* ----------------------------------------------------------------------- */
typedef uint16 FILE2_FILE_ORIGIN_TYPES_CONST;

/* Should be used when Type of change is FILE2_FILE_CHANGED_MODIFIED or
   FILE2_FILE_CHANGED_RENAMED
*/
#define FILE2_FILE_ORIGIN_UNSPECIFIED            0x0000
/* File downloaded. */
#define FILE2_FILE_ORIGIN_DOWNLOAD               0x0001
/* File created by camera */
#define FILE2_FILE_ORIGIN_CAMERA                 0x0002
/* File received via BlueTooth */
#define FILE2_FILE_ORIGIN_BT                     0x0003
/* File received via MMS */
#define FILE2_FILE_ORIGIN_MMS                    0x0004
/* File received via e-mail */
#define FILE2_FILE_ORIGIN_EMAIL                  0x0005
/* File received via Infra Red */
#define FILE2_FILE_ORIGIN_IR                     0x0006
/* Radio recording */
#define FILE2_FILE_ORIGIN_RADIO                  0x0007
#define FILE2_FILE_ORIGIN_TV                     0x0008  /* TV recording */
/* Voice recording */
#define FILE2_FILE_ORIGIN_VOICE                  0x0009
/* File received using Media Transfer Protocol */
#define FILE2_FILE_ORIGIN_MTP                    0x000A
/* Image, video, audio etc. editor */
#define FILE2_FILE_ORIGIN_EDITOR                 0x000B

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_DRIVE_CHANGE_TYPES                                */
/* ----------------------------------------------------------------------- */
typedef uint16 FILE2_DRIVE_CHANGE_TYPES_CONST;

/* A USB mass storage session has been ended */
#define FILE2_DRIVE_CHANGED_MASS_STORAGE_END     0x0001
/* A USB MSC drive has been inserted, but there is no free filesys drive */
#define FILE2_DRIVE_CHANGED_USB_MSC_NO_FREE_DRIVE 0x0002
/* User has unlocked the password protected memory card drive */
#define FILE2_DRIVE_CHANGED_DRIVE_UNLOCKED       0x0003

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_FS_TYPES                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_FS_TYPES_CONST;

/* Bad file system */
#define FILE2_FS_TYPE_BAD                        0x00
#define FILE2_FS_TYPE_FAT                        0x01  /* FAT12/16/32 */
#define FILE2_FS_TYPE_EXFAT                      0x04  /* exFAT, 64bit */

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_OPERATION_TYPE    */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_OPERATION_TYPE_CONST;

/* Register client for memory card power scheme changes. */
#define FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_REGISTER 0x00
/* Unregister client for memory card power scheme changes. */
#define FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_UNREGISTER 0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_MEMORY_CARD_POWER_SCHEME_TYPE                     */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_MEMORY_CARD_POWER_SCHEME_TYPE_CONST;

/* Sets the default powering scheme to be used for memory card.  */
#define FILE2_MEMORY_CARD_POWER_SCHEME_DEFAULT   0x00
/* Sets the memory card power down delay to the requested value. Memory card
   is powered down after there is no accesses to card for the given timeout.
*/
#define FILE2_MEMORY_CARD_POWER_SCHEME_POWER_DOWN_DELAY 0x01
/* Set always powered on. Keeps the memory card always powered on. */
#define FILE2_MEMORY_CARD_POWER_SCHEME_ALWAYS_ON 0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: FILE2_QUOTA_INFO - Valid from version 033.000           */
/* ----------------------------------------------------------------------- */
typedef uint8 FILE2_QUOTA_INFO_CONST;

/* Quota has decreased below lower limit of hysteresis */
#define FILE2_QUOTA_OK                           0x00
/* Quota has decreased to safe region of hysteresis */
#define FILE2_QUOTA_SAFE                         0x01
/* Quota is at notification region */
#define FILE2_QUOTA_NOTIFY                       0x02
/* Quota has been exceeded, drive is almost full */
#define FILE2_QUOTA_EXCEEDED                     0x04

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define FILE_CREATE_FOLDER_REQ                   0x04
#define FILE_CREATE_FOLDER_RESP                  0x05
#define FILE_PREINSTALL_FILES_REQ                0x44
#define FILE_PREINSTALL_FILES_RESP               0x45
#define FILE2_WRITE_REQ                          0x58
#define FILE2_WRITE_RESP                         0x59
#define FILE2_OFFSET_WRITE_REQ                   0x5A
#define FILE2_OFFSET_WRITE_RESP                  0x5B
#define FILE2_READ_REQ                           0x5C
#define FILE2_READ_RESP                          0x5D
#define FILE2_OFFSET_READ_REQ                    0x5E
#define FILE2_OFFSET_READ_RESP                   0x5F
#define FILE2_RENAME_REQ                         0x60
#define FILE2_RENAME_RESP                        0x61
#define FILE2_ITEM_DELETE_REQ                    0x62
#define FILE2_ITEM_DELETE_RESP                   0x63
#define FILE2_DIRECTORY_CREATE_REQ               0x64
#define FILE2_DIRECTORY_CREATE_RESP              0x65
#define FILE2_CRC_CALCULATION_REQ                0x66
#define FILE2_CRC_CALCULATION_RESP               0x67
#define FILE2_DIRECTORY_LIST_GET_REQ             0x68
#define FILE2_DIRECTORY_LIST_GET_RESP            0x69
#define FILE2_DELTREE_REQ                        0x6A
#define FILE2_DELTREE_RESP                       0x6B
#define FILE2_PROPERTIES_GET_REQ                 0x6C
#define FILE2_PROPERTIES_GET_RESP                0x6D
#define FILE2_ATTRIBUTES_SET_REQ                 0x6E
#define FILE2_ATTRIBUTES_SET_RESP                0x6F
#define FILE2_DRIVESTAT_GET_REQ                  0x70
#define FILE2_DRIVESTAT_GET_RESP                 0x71
#define FILE2_FILE_OPEN_REQ                      0x72
#define FILE2_FILE_OPEN_RESP                     0x73
#define FILE2_FILE_CLOSE_REQ                     0x74
#define FILE2_FILE_CLOSE_RESP                    0x75
#define FILE_SYSTEM_REQ                          0x76
#define FILE_SYSTEM_RESP                         0x77
#define FILE2_FORMAT_REQ                         0x78
#define FILE2_FORMAT_RESP                        0x79
#define FILE2_MMC_PRODUCTION_TEST_REQ            0x7A
#define FILE2_MMC_PRODUCTION_TEST_RESP           0x7B
#define FILE2_DRIVE_QUERY_REQ                    0x7D
#define FILE2_DRIVE_QUERY_RESP                   0x7E
#define FILE2_ITEM_INACCESSIBLE_IND              0x81
#define FILE2_FIM_FIXED_ID_CREATE_REQ            0x82
#define FILE2_FIM_FIXED_ID_CREATE_RESP           0x83
#define FILE2_FIM_FILE_NAME_PATH_GET_REQ         0x84
#define FILE2_FIM_FILE_NAME_PATH_GET_RESP        0x85
#define FILE2_DRM_ITEM_RIGHTS_UPDATED_IND        0x88
#define FILE2_PERF_TEST_MEASUREMENT_REQ          0x89
#define FILE2_PERF_TEST_MEASUREMENT_RESP         0x8A
#define FILE2_DELTREE_FORCE_REQ                  0x8B
#define FILE2_DELTREE_FORCE_RESP                 0x8C
#define FILE2_COPY_REQ                           0x8D
#define FILE2_COPY_RESP                          0x8E
#define FILE2_FILE_SEARCH_REQ                    0x8F
#define FILE2_FILE_SEARCH_RESP                   0x90
#define FILE2_MEMORY_CARD_HOT_SWAP_IND           0x91
#define FILE2_HOT_SWAP_SWITCH_STATE_REQ          0x92
#define FILE2_HOT_SWAP_SWITCH_STATE_RESP         0x93
#define FILE2_DISKWIPE_REQ                       0x94
#define FILE2_DISKWIPE_RESP                      0x95
#define FILE2_ITEM_ACCESSIBLE_IND                0x96
#define FILE2_TIMESTAMPS_SET_REQ                 0x97
#define FILE2_TIMESTAMPS_SET_RESP                0x98
#define FILE2_DIRECTORY_LIST_GET_NEW_REQ         0x99
#define FILE2_DIRECTORY_LIST_GET_NEW_RESP        0x9A
#define FILE2_PROPERTIES_GET_NEW_REQ             0x9B
#define FILE2_PROPERTIES_GET_NEW_RESP            0x9C
#define FILE2_DRIVESTAT_DIR_GET_REQ              0x9D
#define FILE2_DRIVESTAT_DIR_GET_RESP             0x9E
#define FILE2_PWD_ERASE_REQ                      0x9F
#define FILE2_PWD_ERASE_RESP                     0xA0
#define FILE2_ITEM_CHANGED_IND                   0xA1
#define FILE2_FIM_EVENT_IND                      0xA2
#define FILE2_FILE_OPEN_WRITE_CLOSE_REQ          0xA3
#define FILE2_FILE_OPEN_WRITE_CLOSE_RESP         0xA4
#define FILE2_MEMORY_TEST_REQ                    0xA5
#define FILE2_MEMORY_TEST_RESP                   0xA6
#define FILE2_OFFSET_WRITE64_REQ                 0xA7
#define FILE2_OFFSET_WRITE64_RESP                0xA8
#define FILE2_OFFSET_READ64_REQ                  0xA9
#define FILE2_OFFSET_READ64_RESP                 0xAA
#define FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_REQ 0xAB
#define FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_RESP 0xAC
#define FILE2_MEMORY_CARD_POWER_SCHEME_SET_REQ   0xAD
#define FILE2_MEMORY_CARD_POWER_SCHEME_SET_RESP  0xAE
#define FILE2_DRIVE_QUOTA_IND                    0xAF

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define FILE2_SB_FILE_CHANGED_DATA               0x0002
#define FILE2_SB_DRIVE_CHANGED_DATA              0x0003

/* ----------------------------------------------------------------------- */
/* Sequence: FILE2_ACCESS_DATE                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  year;         /*   */
    uint8   month;        /* 1 to 12  */
    uint8   day;          /* 1 to 31  */
    } FILE2_ACCESS_DATE_STR;

#define SIZE_FILE2_ACCESS_DATE_STR   sizeof(FILE2_ACCESS_DATE_STR)


/* ----------------------------------------------------------------------- */
/* Sequence: FILE2_ACCESS_TIME                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   hour;         /* 0 to 23  */
    uint8   minute;       /* 0 to 59  */
    uint8   second;       /* 0 to 59  */
    uint8   alignment1;   /* Allways 0  */
    } FILE2_ACCESS_TIME_STR;

#define SIZE_FILE2_ACCESS_TIME_STR   sizeof(FILE2_ACCESS_TIME_STR)


/* ----------------------------------------------------------------------- */
/* Sequence: FILE2_DRIVE_INFO                                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    char16  drive_letter; /* Drive letter */
    /* Drive type
       Values from the constant table FILE2_DRIVE_TYPE
    */
    uint8   drive;
    uint8   fill1;
    } FILE2_DRIVE_INFO_STR;

#define SIZE_FILE2_DRIVE_INFO_STR   sizeof(FILE2_DRIVE_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: FILE2_SB_FILE_CHANGED_DATA                                    */
/* ----------------------------------------------------------------------- */
/* This sub block is for sending the path of a file with change reason and
   origin. File move, rename and modify operations can be indicated with this
   Sub Block
*/

typedef struct
    {
    uint16  sb_id;
    uint16  sb_len;
    /* Values from the constant table FILE2_FILE_CHANGE_TYPES */
    uint16  type_of_change;
    /* Values from the constant table FILE2_FILE_ORIGIN_TYPES */
    uint16  origin;
    uint16  path_len;     /* Path length including trailing nul */
    uint16  new_path_len; /* New path length including trailing nul */
    /* Path having trailing nul e.g. [drive]:\file.txt\0. 
       The old path is followed by the new path e.g. [drive]:\new_file.txt\0 
       Complete path example: [drive]:\file.txt\0[drive]:\new_file.txt\0 
    */
    uint16  path[FILE_ANY_SIZE];
    /* Filler takes care of the alignment  */
    } FILE2_SB_FILE_CHANGED_DATA_STR;

#define SIZE_FILE2_SB_FILE_CHANGED_DATA_STR   (6*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Subblock: FILE2_SB_DRIVE_CHANGED_DATA                                   */
/* ----------------------------------------------------------------------- */
/* This sub block is for sending the path of a drive with change reason.
   If the type_of_the change is FILE2_DRIVE_CHANGED_USB_MSC_NO_FREE_DRIVE
   then the drive_id will be always FILE2_DRIVE_UNDEFINED. Meaning that the
   inserted USB MSC drive couldn't be mapped into phone's file system,
   because there is no free  drive_id.
*/

typedef struct
    {
    uint16  sb_id;
    uint16  sb_len;
    /* Values from the constant table FILE2_DRIVE_CHANGE_TYPES */
    uint16  type_of_change;
    uint16  drive_id_len; /* drive ID length including trailing nul */
    /*  drive ID path having trailing nul e.g. [drive]:\\0 */
    uint16  drive_id[FILE_ANY_SIZE];
    } FILE2_SB_DRIVE_CHANGED_DATA_STR;

#define SIZE_FILE2_SB_DRIVE_CHANGED_DATA_STR   (4*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: FILE_CREATE_FOLDER_REQ                                         */
/* ----------------------------------------------------------------------- */
/* Creates a new folder, with the header information specified, in the
   sepecified destination folder. The exact header structure is defined in
   /D.3/. The File Manager determines the new folder ID and returns it to the
   client. The folder ID is unique and specific to the device the folder the
   is stored on. 
   The file name is specified in the header informaiton. The File Manager
   checks the names of written to the storage areas. The File Manager will
   not allow files/folders of the same name to be written to the same folder.
   If no name is specified, the file is given a default file name. 
   Each storage device has a seperate root folder. This will allow the file
   to be stored on the appropriate device by adding the file to the
   appropriate folder. All files and folders must exist in at least one
   folder, except the root folder for each device and attached slave files.
   The folders can be nested as deep as the user requires; the only
   restriction is the available memory on the storage device.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  alignment1;
    uint32  dest_folder_id; /* Values from the constant table FMAN_ID_T */
    uint32  header_size;  /* sizeof FMAN STD header */
    uint8   data[FILE_ANY_SIZE];
    } FILE_CREATE_FOLDER_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE_CREATE_FOLDER_RESP                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* A subset of values from the constant table FMAN_STATUS */
    uint8   fman_status;
    uint8   alignment1;
    uint32  folder_id;    /* Values from the constant table FMAN_ID_T */
    } FILE_CREATE_FOLDER_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE_PREINSTALL_FILES_REQ                                      */
/* ----------------------------------------------------------------------- */
/* This function is used to pre-install files in production. It will read
   from a special download package(content package) in the PPM area and
   create files/folders defined in this download package by calling FMAN
   functions. Content package itself is product specific and is not done by
   FMAN(team) 
   The File Manager will return FMAN_OK if FMAN created the files/folders
   successfully. If something went wrong(too less memory, checksum failed,
   files/folders already available...) the File Manager will return FMAN_FAIL
   Messagehandling is depending of flagsetting of 'FILE_PREINSTALL_SUPPORTED'
   defined in file_conf.h 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  alignment1;
    } FILE_PREINSTALL_FILES_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE_PREINSTALL_FILES_RESP                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* A subset of values from the constant table FMAN_STATUS */
    uint8   fman_status;
    uint8   alignment1;
    } FILE_PREINSTALL_FILES_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE_SYSTEM_REQ                                                */
/* ----------------------------------------------------------------------- */
/* This message can use to ask from file server what file system interfaces
   it supports. Supported file systems are FMAN and File2 file system. This
   message is file system independent message. It means that client can send
   this request even if there is file2 or FMAN or none of those file systems
   but file server is running.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    } FILE_SYSTEM_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE_SYSTEM_RESP                                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       Values from the bitmask table FILE_SYSTEM_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE_SYSTEM_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_WRITE_REQ                                                */
/* ----------------------------------------------------------------------- */
/* This message write a data to a file system (File2).File descriptor
   specifies the file to where data will be written.To get file descriptor
   client must use FILE2_FILE_OPEN_REQ message. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   alignment[2];
    uint32  file_desc;    /* File descriptor */
    uint32  data_length;
    uint8   data[FILE_ANY_SIZE];
    } FILE2_WRITE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_WRITE_RESP                                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_WRITE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_OFFSET_WRITE_REQ                                         */
/* ----------------------------------------------------------------------- */
/* This message write a data to a file from given offset. 
   File descriptor specifies the file to where data will be written.To get
   file descriptor client must use FILE2_FILE_OPEN_REQ message.
   Offset is from beginning of the file. If offset is inside of the file the
   data will be overwritten 
   NOTE! Supports only 32 bit or smaller file systems i.e. FAT12/16/32
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  alignment1;
    uint32  file_desc;    /* File descriptor */
    uint32  offset;       /* Offset */
    uint32  data_length;
    uint8   data[FILE_ANY_SIZE];
    } FILE2_OFFSET_WRITE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_OFFSET_WRITE_RESP                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_OFFSET_WRITE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_READ_REQ                                                 */
/* ----------------------------------------------------------------------- */
/* This message reads data from file system (File2).
   In length of response data blocks field client put the size of datablock
   what is used in the response message. In response message status is
   FILE2_MORE_DATA until last response message is sent. In last response
   message status is FILE2_OK. If an empty file is read then FILE2_OK with
   response data size 0 is returned.
   File descriptor specifies the file to where data will be written.To get
   file descriptor client must use FILE2_FILE_OPEN_REQ message. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    uint32  resp_data_len; /* Length of response data blocks */
    uint32  file_desc;    /* File descriptor */
    } FILE2_READ_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_READ_RESP                                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint32  data_length;
    uint8   data[FILE_ANY_SIZE];
    } FILE2_READ_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_OFFSET_READ_REQ                                          */
/* ----------------------------------------------------------------------- */
/* This message reads data from a file from given offset.
   In length of response data blocks field client put the size of data block
   what is used in the response message. In response message status is
   FILE2_MORE_DATA until last response message is sent. In last response
   message status is FILE2_OK.If an empty file is read then FILE2_OK with
   response data size 0 is returned.If offset is out of bounds then
   FILE2_OFFSET_ERROR is returned. 
   File descriptor specifies the file to where data will be written.To get
   file descriptor client must use FILE2_FILE_OPEN_REQ message. Offset is
   from beginning of the file.
   NOTE! Supports only 32 bit or smaller file systems i.e. FAT12/16/32
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    uint32  file_desc;    /* File descriptor */
    uint32  offset;       /* Offset */
    uint32  resp_data_len; /* Length of response data blocks */
    uint32  data_length;  /* Length of data to read */
    } FILE2_OFFSET_READ_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_OFFSET_READ_RESP                                         */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint32  data_length;
    uint8   data[FILE_ANY_SIZE];
    } FILE2_OFFSET_READ_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_RENAME_REQ                                               */
/* ----------------------------------------------------------------------- */
/* This message can be use to rename a file and a directory.
   Filenames includes absolute path of the file or directory 
   e.g. A:\Temp\file.txt or A:\Temp\SubDir .
   A client must reserve enough dynamic memory for name strings according to
   length fields. The old and new name strings will follow the struct and are
   accessed by moving a pointer.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    uint16  old_filename_len;
    uint16  new_filename_len;
    } FILE2_RENAME_REQ_STR;

/* The filenames will follow the struct: 
       ucs2_char old_filename[old_filename_len]; 
       ucs2_char new_filename[new_filename_len]; 
       uint8 filler[2]; */ 

/* ----------------------------------------------------------------------- */
/* Message: FILE2_RENAME_RESP                                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_RENAME_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_ITEM_DELETE_REQ                                          */
/* ----------------------------------------------------------------------- */
/* This message delete a file or a directory from the file system (File2).
   Filename includes absolute path of the directory ( A:\Temp\file.txt or
   A:\Temp\SubDir ).
   Filename is in 16-bit unicode chars. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  filename_len;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_ITEM_DELETE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_ITEM_DELETE_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_ITEM_DELETE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DIRECTORY_CREATE_REQ                                     */
/* ----------------------------------------------------------------------- */
/* This message create a directory to file system (File2).
   If client needs to create many sub directories it must create all
   directories separately 
   E.g. Client want create Temp directory and under that SubDir directory
   (A:\Temp\SubDir ):
   First client must create A:\Temp directory and then A:\Temp\SubDir
   directory
   Directory name is in 16-bit unicode chars. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  dirname_len;
    char16  dirname[FILE_ANY_SIZE];
    } FILE2_DIRECTORY_CREATE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DIRECTORY_CREATE_RESP                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_DIRECTORY_CREATE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DIRECTORY_LIST_GET_REQ                                   */
/* ----------------------------------------------------------------------- */
/* This message list directory entries.
   NOTE! Supports only 32 bit or smaller file systems i.e. FAT12/16/32
   The client send response message and server responses as many response
   massages as there are items.
   The response message status is FILE2_MORE_DATA if more response messages
   are coming. In last response message status is FILE2_OK. 
   In case of empty directory status is FILE2_EMPTY and all data values are
   zeroes.
   A user must give a whole path with a filter as a directory name. Wildcards
   * and ? are allowed in a filter but not in a path. . and .. are not
   returned. If there is only . and .. in a folder then FILE2_EMPTY is
   returned. 
   Directory names are in 16-bit unicode chars. 
   Examples:
   a:\aa\* 	        returns the contents of folder aa 
   a:\aa\*.txt	    returns all txt files on aa folder 
   a:\aa\bbb.txt	returns an attributes of bbb.txt 
   a:\aa             returns an attributes of aa 
   a:\aa\	        returns the contents of folder aa 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  dirname_len;
    char16  dirname[FILE_ANY_SIZE];
    } FILE2_DIRECTORY_LIST_GET_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DIRECTORY_LIST_GET_RESP                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    /* Mode
       Values from the bitmask table FILE2_MODE
    */
    uint32  mode;
    uint32  size;         /* Size */
    FILE2_ACCESS_DATE_STR access_date;
    FILE2_ACCESS_TIME_STR access_time;
    uint32  dev_id;       /* Device ID */
    /* FAT attributes
       Values from the bitmask table FILE2_FAT_ATTRIBUTES
    */
    uint32  fat_attributes;
    uint16  filename_length;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_DIRECTORY_LIST_GET_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DELTREE_REQ                                              */
/* ----------------------------------------------------------------------- */
/* This message delete directory, all sub directories and all files contained
   therein from file system (File2). Directory name is in 16-bit unicode
   chars.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  dirname_len;
    char16  dirname[FILE_ANY_SIZE];
    } FILE2_DELTREE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DELTREE_RESP                                             */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_DELTREE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_PROPERTIES_GET_REQ                                       */
/* ----------------------------------------------------------------------- */
/* This message get file properties from file system (File2). Filename is in
   16-bit unicode chars.
   NOTE! Supports only 32 bit or smaller file systems i.e. FAT12/16/32
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  filename_len;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_PROPERTIES_GET_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_PROPERTIES_GET_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1;        /* Status */
    /* A subset of values from the constant table FILE2_STATUS */
    uint8   status;
    /* Mode
       Values from the bitmask table FILE2_MODE
    */
    uint32  mode;
    uint32  size;         /* Size */
    FILE2_ACCESS_DATE_STR access_date;
    FILE2_ACCESS_TIME_STR access_time;
    /* the ID of the device the file is stored to (MMC, NAND, etc) */
    uint32  dev_id;
    /* FAT attributes
       Values from the bitmask table FILE2_FAT_ATTRIBUTES
    */
    uint32  fat_attributes;
    } FILE2_PROPERTIES_GET_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_ATTRIBUTES_SET_REQ                                       */
/* ----------------------------------------------------------------------- */
/* This message set file attributes in file system (File2). Filename is in
   16-bit unicode chars. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  filename_len;
    /* FAT attributes
       Values from the bitmask table FILE2_FAT_ATTRIBUTES
    */
    uint32  fat_attributes;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_ATTRIBUTES_SET_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_ATTRIBUTES_SET_RESP                                      */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_ATTRIBUTES_SET_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DRIVESTAT_GET_REQ                                        */
/* ----------------------------------------------------------------------- */
/* This message get statistic about logical drive from file system (File2).
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    char16  drive_name[1];
    } FILE2_DRIVESTAT_GET_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DRIVESTAT_GET_RESP                                       */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    /* File system type
       Values from the constant table FILE2_FS_TYPES
    */
    uint8   fs_type;
    uint32  total_sectors; /* LSB Total sectors */
    uint32  free_sectors; /* LSB free sectors */
    uint32  sector_size;  /* Sector size */
    uint32  total_sectors_hi; /* MSB Total sectors, zero if LSB is enough */
    uint32  free_sectors_hi; /* MSB free sectors, zero if LSB is enough */
    } FILE2_DRIVESTAT_GET_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FILE_OPEN_REQ                                            */
/* ----------------------------------------------------------------------- */
/* This message is used to open file from file system (File2).
   When client open file it must select one of three mandatory access flags.
   These flags are FILE2_O_RDONLY, FILE2_O_WRONLY and FILE2_O_RDWR. Another
   flags are optionals.If new file are created then FILE2_O_CREAT must select
   also.More information for these flags see reference /D.4/.
   Filename is in 16-bit unicode chars.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Access flags
       Values from the bitmask table FILE2_ACCESS_FLAGS
    */
    uint8   access_flags;
    /* Close information
       Values from the constant table FILE2_CLOSE_INFO
    */
    uint8   close_info;
    uint16  filename_len;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_FILE_OPEN_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FILE_OPEN_RESP                                           */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint32  file_descriptor; /* File descriptor */
    } FILE2_FILE_OPEN_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FILE_CLOSE_REQ                                           */
/* ----------------------------------------------------------------------- */
/* This message close file from file system (File2) */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    uint32  file_descriptor; /* File descriptor */
    } FILE2_FILE_CLOSE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FILE_CLOSE_RESP                                          */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_FILE_CLOSE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FORMAT_REQ                                               */
/* ----------------------------------------------------------------------- */
/* This message format logical drive from file system (File2). */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    char16  drive_name[1];
    } FILE2_FORMAT_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FORMAT_RESP                                              */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    /* File system type
       Values from the constant table FILE2_FS_TYPES
    */
    uint8   fs_type;
    } FILE2_FORMAT_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_CRC_CALCULATION_REQ                                      */
/* ----------------------------------------------------------------------- */
/* The message responds with the CRC-16 checksum and FILE2_OK if successful.
   If the operation failed then the FILE server will respond with the error
   value 
   To get file descriptor client must use FILE2_FILE_OPEN_REQ message.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    uint32  file_descriptor; /* File descriptor */
    } FILE2_CRC_CALCULATION_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_CRC_CALCULATION_RESP                                     */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint16  checksum;
    } FILE2_CRC_CALCULATION_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MMC_PRODUCTION_TEST_REQ                                  */
/* ----------------------------------------------------------------------- */
/* This message run memory card production test. */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Drive type
       Values from the constant table FILE2_DRIVE_TYPE
    */
    uint8   drive;
    uint8   fill1;
    } FILE2_MMC_PRODUCTION_TEST_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MMC_PRODUCTION_TEST_RESP                                 */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_MMC_PRODUCTION_TEST_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DRIVE_QUERY_REQ                                          */
/* ----------------------------------------------------------------------- */
/* This message is to get a list of all used drives in target. A drive letter
   and system information (NAND, MMC, NOR) is returned as a table. If no
   drives is found then status is FILE2_FAIL, the number of drives is 0  and
   no drive information table is returned. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    } FILE2_DRIVE_QUERY_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DRIVE_QUERY_RESP                                         */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    /* Number of the elements in drive information array */
    uint8   drive_info;
    FILE2_DRIVE_INFO_STR drive_list[FILE_ANY_SIZE];
    } FILE2_DRIVE_QUERY_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_ITEM_INACCESSIBLE_IND                                    */
/* ----------------------------------------------------------------------- */
/* The indication is sent by File ID Manager (FIM) when a file is no longer
   accessible. The indication is only sent out in case the inaccessible file
   has a FIM associated with it. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    /* Values from the constant table FILE2_ITEM_INACCESSIBLE_REASON_TABLE */
    uint16  reason;
    uint16  number_of_items;
    uint32  item_id_list[FILE_ANY_SIZE];
    } FILE2_ITEM_INACCESSIBLE_IND_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_ITEM_ACCESSIBLE_IND                                      */
/* ----------------------------------------------------------------------- */
/* The indication is sent by File ID Manager (FIM)  when a file gets valid
   again. The indication is only sent out in case the accessible file has a
   FIM associated with it. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    /* Values from the constant table FILE2_ITEM_ACCESSIBLE_REASON_TABLE */
    uint16  reason;
    uint16  number_of_items;
    uint32  item_id_list[FILE_ANY_SIZE];
    } FILE2_ITEM_ACCESSIBLE_IND_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FIM_FIXED_ID_CREATE_REQ                                  */
/* ----------------------------------------------------------------------- */
/* Create a fixed FIM (File Id Manager) ID. A file name with whole path is
   given in a request and a fixed FIM ID is returned. In error case
   FILE2_FAIL is returned and FIM ID is 0. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  filename_len;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_FIM_FIXED_ID_CREATE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FIM_FIXED_ID_CREATE_RESP                                 */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint32  fim_id;       /* File Id Manager (FIM) ID */
    } FILE2_FIM_FIXED_ID_CREATE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FIM_FILE_NAME_PATH_GET_REQ                               */
/* ----------------------------------------------------------------------- */
/* Get the whole file name and path of the file attached to the FIM (File Id
   Manager) ID. In error case the status is FILE2_FAIL and the length of
   filename is 0.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    uint32  fim_id;       /* File Id Manager (FIM) ID */
    } FILE2_FIM_FILE_NAME_PATH_GET_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FIM_FILE_NAME_PATH_GET_RESP                              */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint16  filename_len;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_FIM_FILE_NAME_PATH_GET_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DRM_ITEM_RIGHTS_UPDATED_IND                              */
/* ----------------------------------------------------------------------- */
/* The indication is sent by DRM when a new rights object has been received
   and saved. Applications that are trying to use a file without any active
   rights object, can use this indication to retry their action.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    } FILE2_DRM_ITEM_RIGHTS_UPDATED_IND_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_PERF_TEST_MEASUREMENT_REQ                                */
/* ----------------------------------------------------------------------- */
/* This message is only for SCF Corsa's internal use !! More information can
   be found from FILE2_perftest_spec.doc located in continuus>sa_core.
   Project: corsa_docs Directory: test>file2_test 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Measurement to be executed 
       Values from the constant table FILE2_MEASUREMENT_CASES
    */
    uint8   measurement;
    uint8   fill1;
    uint32  write_times;  /* How many times to write is called  */
    /* Amount of data to be written with write access  */
    uint32  amount_of_data;
    /* Interf
       Values from the constant table FILE2_INTERFACE_SELECTION
    */
    uint8   interf;
    uint8   fill2;
    char16  drive_letter[1]; /* Letter of the drive  */
    } FILE2_PERF_TEST_MEASUREMENT_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_PERF_TEST_MEASUREMENT_RESP                               */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    /* Measurement to be executed 
       Values from the constant table FILE2_MEASUREMENT_CASES
    */
    uint8   measurement;
    uint32  data_length;
    uint32  data[FILE_ANY_SIZE];
    } FILE2_PERF_TEST_MEASUREMENT_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DELTREE_FORCE_REQ                                        */
/* ----------------------------------------------------------------------- */
/* This message deletes directory, all sub directories and all files
   contained therein from file system (File2). Directory name is in 16-bit
   unicode chars. Either FILE2_DELTREE_NONABORT or
   FILE2_DELTREE_ABORT_ON_ERROR has to be defined in mode parameter,
   otherwise FILE2_EINVAL is returned. FILE2_DELTREE_NONABORT mode defines
   continuous directory tree deletion. If a read_only file/directory or an
   open file is encountered, the deletion is not stopped, but directory tree
   will be left partially removed. If an open file(s) is encountered,
   FILE2_EBADF is returned. If a read-only file(s) or directory(s) is
   encountered, FILE2_EACCES is returned. If both an open file(s) and a
   read-only item(s) are encountered, FILE2_EBADF is returned.
   FILE2_DELTREE_ABORT_ON_ERROR mode is similar as FILE2_DELTREE_REQ/RESP
   functionality. FILE2_DELTREE_READ_ONLY_DELETE mode is used conjunction
   with FILE2_DELTREE_NONABORT mode. Otherwise FILE2_DELTREE_READ_ONLY_DELETE
   mode doesn't have effect. This mode allows to delete read-only marked
   files and folders. FILE2_DELTREE_NO_SYSTEM_ITEMS deletes all but not
   system files. If FILE2_DELTREE_NO_SYSTEM_ITEMS is used with
   FILE2_DELTREE_READ_ONLY_DELETE, read only system items will not be
   deleted.If a directory tree is left partially un-deleted due system items
   and FILE2_DELTREE_NO_SYSTEM_ITEMS mode, the returned error code will be
   FILE2_EACCES.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  dirname_len;
    /* deltree force modes
       Values from the bitmask table FILE2_DELTREE_FORCE_MODE
    */
    uint32  mode;
    char16  dirname[FILE_ANY_SIZE];
    } FILE2_DELTREE_FORCE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DELTREE_FORCE_RESP                                       */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_DELTREE_FORCE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_COPY_REQ                                                 */
/* ----------------------------------------------------------------------- */
/* This message can be used to copy a file or a directory. 
   Source includes absolute path of the file or directory to be copied. 
   e.g. C:\Temp\file.txt or C:\SubDir . Name strings are null terminated. 
   Destination includes absolute path of the new file or folder to copy to.
   Copyright files will not be copied across drives. Timestamp of the new
   file is the same as the old file. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    uint16  source_len;
    uint16  destination_len;
    } FILE2_COPY_REQ_STR;

/* The file names will follow the struct: 
       ucs2_char source[source_len]; 
       ucs2_char destination[destination_len] 
       uint8 filler[2]; */ 

/* ----------------------------------------------------------------------- */
/* Message: FILE2_COPY_RESP                                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_COPY_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FILE_SEARCH_REQ                                          */
/* ----------------------------------------------------------------------- */
/* Search files, count number of files or get filepath of N:th file in a
   folder. 
   The search returns a list of file paths of found items corresponding to
   the contents of the criteria. The first part of a result contains a 16 bit
   value of how many search results will be expected. Each search result is a
   null terminated 16-bit unicode string. The folder names ends with \
   character. 
   Counting number of files returns number of found items. No paths are
   included. From search_include FILE2_FILE_COUNT_ONLY must be set high.
   When reading N:th file from a folder set Index as some random number and
   Limit as 1. Then file path is returned.
   Search_include defines what part of the search result will be returned to
   the user. If there are no bits set in this parameter, the search results
   will be empty. The user is allowed to select multiple bits for one search
   and to search all items it is always necessary to select at least
   FILE2_FILE_FILES or FILE2_FILE_FOLDERS bits. If multiple bits are
   selected, only the files that contain all the conditions will be returned.
   Index is a item number in a folder where to start this search e.g. 10
   would mean that 0-9 is skipped. 
   Limit is a maximum number of items to include in this search. 
   Search criteria consist of one or more unicode strings. All strings must
   be null terminated. The format of the string is such that the first part
   contains a 16-bit value for how many criteria to be expected. Example: 
    \0\02\0*\0.\0j\0p\0\g\0\0\0*\0.\h\0e\0l\0l\0o\0\0
   A client must reserve enough dynamic memory for search criteria and file
   path strings according to length fields. The search criteria and file path
   strings will follow the struct and are accessed by moving a pointer.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1;
    uint8   subdirs;      /* Search subdirs recursively (TRUE\FALSE) */
    /* Search include bits
       Values from the bitmask table FILE2_SEARCH_INCLUDE
    */
    uint16  search_include;
    uint16  index;        /* Index */
    uint16  limit;        /* Limit */
    uint8   fill2[2];
    uint16  search_criteria_len;
    uint16  source_path_len;
    } FILE2_FILE_SEARCH_REQ_STR;

/* The strings will follow the struct: 
       ucs2_char search_criteria[search_criteria_len]; 
       ucs2_char source_path[source_path_len]; 
       uint8 filler[2]; */ 

/* ----------------------------------------------------------------------- */
/* Message: FILE2_FILE_SEARCH_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint16  search_result_len;
    char16  search_result[FILE_ANY_SIZE];
    } FILE2_FILE_SEARCH_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MEMORY_CARD_HOT_SWAP_IND                                 */
/* ----------------------------------------------------------------------- */
/* This indication is generated whenever an external card is either inserted
   or removed.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1;
    /* Values from the constant table FILE2_HOTSWAP_STATUS_TBL */
    uint8   status;
    uint8   fill2[2];
    char16  drive_letter[1]; /* Letter of the drive  */
    } FILE2_MEMORY_CARD_HOT_SWAP_IND_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_HOT_SWAP_SWITCH_STATE_REQ                                */
/* ----------------------------------------------------------------------- */
/* This message returns status of the detection switch. Real meaning of
   ON/OFF on this switch is very product specific. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    } FILE2_HOT_SWAP_SWITCH_STATE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_HOT_SWAP_SWITCH_STATE_RESP                               */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    /* Status of the switch
       Values from the bitmask table FILE2_HOTSWAP_FLAGS
    */
    uint8   flag_status;
    } FILE2_HOT_SWAP_SWITCH_STATE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DISKWIPE_REQ                                             */
/* ----------------------------------------------------------------------- */
/* Disk wipe for internal drives: 
   Clears memory by erasing every deleted sector/byte. All existing files and
   folders remain. 
    
   Disk wipe for external drives such as MMC and SD cards: 
   Clears completely memory by formatting the drive on memory level. All
   existing files and folders will be lost. 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    char16  drive_letter[1];
    } FILE2_DISKWIPE_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DISKWIPE_RESP                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_DISKWIPE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_TIMESTAMPS_SET_REQ                                       */
/* ----------------------------------------------------------------------- */
/* Change a modification and/or creation reference time of a file. The
   reference time is 1.1.1980 and the date should be after that. Odd seconds
   are not supported and those are rounded down. 
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  filename_len;
    uint32  modification_date; /* Modified date, yyyymmdd  */
    uint32  modification_time; /* Modified time, 00hhmmss */
    uint32  creation_date; /* Created date, yyyymmdd  */
    uint32  creation_time; /* Created time, 00hhmmss */
    /* Modification 0x01, creation 0x02, both 0x03
       Values from the bitmask table FILE2_TIMESTAMPS_TBL
    */
    uint32  set_mode;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_TIMESTAMPS_SET_REQ_STR;

#define SIZE_FILE2_TIMESTAMPS_SET_REQ_STR   (2*sizeof(uint8) + \
        sizeof(uint16) + 5*sizeof(uint32))


/* ----------------------------------------------------------------------- */
/* Message: FILE2_TIMESTAMPS_SET_RESP                                      */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_TIMESTAMPS_SET_RESP_STR;

#define SIZE_FILE2_TIMESTAMPS_SET_RESP_STR   \
        sizeof(FILE2_TIMESTAMPS_SET_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DIRECTORY_LIST_GET_NEW_REQ                               */
/* ----------------------------------------------------------------------- */
/* This message list directory entries.The client send response message and
   server responses as many response massages as there are items.The response
   message status is FILE2_MORE_DATA if more response messages are coming. In
   last response message status is FILE2_OK. In case of empty directory
   status is FILE2_EMPTY and all data values are zeroes.A user must give a
   whole path with a filter as a directory name. Wildcards * and ? are
   allowed in a filter but not in a path. . and .. are not returned. If there
   is only . and .. in a folder then FILE2_EMPTY is returned. Directory names
   are in 16-bit unicode chars. Examples:a:\aa\* 	        returns the
   contents of folder aa a:\aa\*.txt	    returns all txt files on aa folder
   a:\aa\bbb.txt	returns an attributes of bbb.txt a:\aa             returns
   an attributes of aa a:\aa\	        returns the contents of folder aa 
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  dirname_len;
    char16  dirname[FILE_ANY_SIZE];
    } FILE2_DIRECTORY_LIST_GET_NEW_REQ_STR;

#define SIZE_FILE2_DIRECTORY_LIST_GET_NEW_REQ_STR   (2*sizeof(uint8) + \
        sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DIRECTORY_LIST_GET_NEW_RESP                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    /* Mode
       Values from the bitmask table FILE2_MODE
    */
    uint32  mode;
    uint32  size;   /* Size of a 32bit file, LSB part of a 64bit file size */
    FILE2_ACCESS_DATE_STR modification_date;
    FILE2_ACCESS_TIME_STR modification_time;
    FILE2_ACCESS_DATE_STR creation_date;
    FILE2_ACCESS_TIME_STR creation_time;
    uint32  dev_id;       /* Device ID */
    /* FAT attributes
       Values from the bitmask table FILE2_FAT_ATTRIBUTES
    */
    uint32  fat_attributes;
    uint16  filename_length;
    char16  filename[FILE2_MAX_FILENAME_LEN];
    uint8   fill2[2];
    /* MSB part of a 64bit file size, zero for a 32bit file size */
    uint32  size_hi;
    } FILE2_DIRECTORY_LIST_GET_NEW_RESP_STR;

#define SIZE_FILE2_DIRECTORY_LIST_GET_NEW_RESP_STR   \
        sizeof(FILE2_DIRECTORY_LIST_GET_NEW_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: FILE2_PROPERTIES_GET_NEW_REQ                                   */
/* ----------------------------------------------------------------------- */
/* This message get file properties from file system (File2). Filename is in
   16-bit unicode chars.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  filename_len;
    char16  filename[FILE_ANY_SIZE];
    } FILE2_PROPERTIES_GET_NEW_REQ_STR;

#define SIZE_FILE2_PROPERTIES_GET_NEW_REQ_STR   (2*sizeof(uint8) + \
        sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: FILE2_PROPERTIES_GET_NEW_RESP                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;        /* Status */
    /* A subset of values from the constant table FILE2_STATUS */
    uint8   status;
    /* Mode
       Values from the bitmask table FILE2_MODE
    */
    uint32  mode;
    uint32  size;   /* Size of a 32bit file, LSB part of a 64bit file size */
    FILE2_ACCESS_DATE_STR modification_date;
    FILE2_ACCESS_TIME_STR modification_time;
    FILE2_ACCESS_DATE_STR creation_date;
    FILE2_ACCESS_TIME_STR creation_time;
    /* the ID of the device the file is stored to (MMC, NAND, etc) */
    uint32  dev_id;
    /* FAT attributes
       Values from the bitmask table FILE2_FAT_ATTRIBUTES
    */
    uint32  fat_attributes;
    /* MSB part of a 64bit file size, zero for a 32bit file size */
    uint32  size_hi;
    } FILE2_PROPERTIES_GET_NEW_RESP_STR;

#define SIZE_FILE2_PROPERTIES_GET_NEW_RESP_STR   \
        sizeof(FILE2_PROPERTIES_GET_NEW_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DRIVESTAT_DIR_GET_REQ                                    */
/* ----------------------------------------------------------------------- */
/* Mainly for a test purpose. This message get statistic about logical
   directory from file system (File2). Directory name is in 16-bit unicode
   chars. Note: Total sector size and free sector size are not necessary
   distinct values, they depends on a memory configuration. 
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  dirname_len;
    char16  dirname[FILE_ANY_SIZE];
    } FILE2_DRIVESTAT_DIR_GET_REQ_STR;

#define SIZE_FILE2_DRIVESTAT_DIR_GET_REQ_STR   (2*sizeof(uint8) + \
        sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DRIVESTAT_DIR_GET_RESP                                   */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    /* File system type
       Values from the constant table FILE2_FS_TYPES
    */
    uint8   fs_type;
    uint32  total_sectors; /* LSB Total sectors */
    uint32  free_sectors; /* LSB free sectors */
    uint32  sector_size;  /* Sector size */
    uint32  total_sectors_hi; /* MSB Total sectors, zero if LSB is enough */
    uint32  free_sectors_hi; /* MSB free sectors, zero if LSB is enough */
    } FILE2_DRIVESTAT_DIR_GET_RESP_STR;

#define SIZE_FILE2_DRIVESTAT_DIR_GET_RESP_STR   \
        sizeof(FILE2_DRIVESTAT_DIR_GET_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: FILE2_PWD_ERASE_REQ                                            */
/* ----------------------------------------------------------------------- */
/* The FILE2_PWD_ERASE operation performs forced erase to the locked card.
   Price is that all data on the card will be erased altogether with the
   password! The FILE2_PWD_ERASE operation can be performed only for cards
   having a password. 
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    char16  drive_letter[1];
    } FILE2_PWD_ERASE_REQ_STR;

#define SIZE_FILE2_PWD_ERASE_REQ_STR   sizeof(FILE2_PWD_ERASE_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: FILE2_PWD_ERASE_RESP                                           */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_PWD_ERASE_RESP_STR;

#define SIZE_FILE2_PWD_ERASE_RESP_STR   sizeof(FILE2_PWD_ERASE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: FILE2_ITEM_CHANGED_IND                                         */
/* ----------------------------------------------------------------------- */
/* An item has been changed in the file system. 
    See also GIF_SPECS\CoreSW\file_if.doc: 2.5	file2_file_changed_signal()
   and 2.6	file2_drive_changed_signal()
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;
    uint8   nbr_of_sub_blocks; /* Number of sub blocks */
    /* Subblock list:
       FILE2_SB_DRIVE_CHANGED_DATA
       FILE2_SB_FILE_CHANGED_DATA
    */
    } FILE2_ITEM_CHANGED_IND_STR;

#define SIZE_FILE2_ITEM_CHANGED_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FIM_EVENT_IND                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    /* The indication is sent by File ID Manager (FIM) when a file has
       changed content or is missing. The indication is only sent out in case
       the affected file has a FIM ID associated with it.
    */
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    /* Values from the constant table FILE2_FIM_EVENT_REASON_TABLE */
    uint16  reason;
    uint16  number_of_items;
    uint32  item_id_list[FILE_ANY_SIZE];
    } FILE2_FIM_EVENT_IND_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_FILE_OPEN_WRITE_CLOSE_REQ                                */
/* ----------------------------------------------------------------------- */
/* This message creates a new file in a file system (File2). The name of the
   file and the data are given in the message. The file is automatically
   closed after the data is written. Existing files can be opened and and
   updated according to the file access flags.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Access flags
       Values from the bitmask table FILE2_ACCESS_FLAGS
    */
    uint8   access_flags;
    uint8   fill1;
    uint16  filename_len; /* Filename length */
    uint16  data_length;  /* Data length */
    /* Filename with the whole path as a zero terminated unicode string */
    char16  filename[FILE_ANY_SIZE];
    /* File data that will be written to the file */
    /* Filler takes care of the alignment  */
    } FILE2_FILE_OPEN_WRITE_CLOSE_REQ_STR;

/* The filename and the file data should follow the struct: 
       ucs2_char filename[filename_len]; 
       uint8 data[data_length]; 
       uint8 filler[]; */ 

/* ----------------------------------------------------------------------- */
/* Message: FILE2_FILE_OPEN_WRITE_CLOSE_RESP                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_FILE_OPEN_WRITE_CLOSE_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MEMORY_TEST_REQ                                          */
/* ----------------------------------------------------------------------- */
/* This message is only for Memory team's internal use !!  */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Select drive type 
       Values from the constant table FILE2_DRIVE_TYPE
    */
    uint8   drive_type;
    /* Interface
       Values from the constant table FILE2_INTERFACE_SELECTION
    */
    uint8   interface;
    uint32  test_case;    /* Test case number  */
    uint32  data_length;
    uint32  data[FILE_ANY_SIZE];
    } FILE2_MEMORY_TEST_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MEMORY_TEST_RESP                                         */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint32  data_length;
    uint32  data[FILE_ANY_SIZE];
    } FILE2_MEMORY_TEST_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_OFFSET_WRITE64_REQ                                       */
/* ----------------------------------------------------------------------- */
/* This message write a data to a file from given offset. 
   File descriptor specifies the file to where data will be written.To get
   file descriptor client must use FILE2_FILE_OPEN_REQ message.
   Offset is from beginning of the file. If offset is inside of the file the
   data will be overwritten 
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  alignment1;
    uint32  file_desc;    /* File descriptor */
    /* Offset of an 32bit offset, LSB part of an 64bit offset */
    uint32  offset;
    /* MSB part of an 64bit offset, zero for a 32bit offset */
    uint32  offset_hi;
    uint32  data_length;
    uint8   data[FILE_ANY_SIZE];
    } FILE2_OFFSET_WRITE64_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_OFFSET_WRITE64_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_OFFSET_WRITE64_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_OFFSET_READ64_REQ                                        */
/* ----------------------------------------------------------------------- */
/* This message reads data from a file from given offset.
   In length of response data blocks field client put the size of data block
   what is used in the response message. In response message status is
   FILE2_MORE_DATA until last response message is sent. In last response
   message status is FILE2_OK.If an empty file is read then FILE2_OK with
   response data size 0 is returned.If offset is out of bounds then
   FILE2_OFFSET_ERROR is returned. 
   File descriptor specifies the file to where data will be written.To get
   file descriptor client must use FILE2_FILE_OPEN_REQ message. Offset is
   from beginning of the file.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill1[2];
    uint32  file_desc;    /* File descriptor */
    /* Offset of an 32bit offset, LSB part of an 64bit offset */
    uint32  offset;
    /* MSB part of an 64bit offset, zero for a 32bit offset */
    uint32  offset_hi;
    uint32  resp_data_len; /* Length of response data blocks */
    uint32  data_length;  /* Length of data to read */
    } FILE2_OFFSET_READ64_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_OFFSET_READ64_RESP                                       */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    uint32  data_length;
    uint8   data[FILE_ANY_SIZE];
    } FILE2_OFFSET_READ64_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_REQ                      */
/* ----------------------------------------------------------------------- */
/* This message registers/unregisters client for memory card power scheme
   handling.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Operation (register/unregister)
       Values from the constant table
       FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_OPERATION_TYPE
    */
    uint8   operation;
    uint8   fill1;
    /* Client ID to be unregistered, for register operation this field is
       discarded.
    */
    uint16  client_ID;
    } FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_RESP                     */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    /* Client ID for the register operation is returned here. */
    uint16  client_ID;
    } FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MEMORY_CARD_POWER_SCHEME_SET_REQ                         */
/* ----------------------------------------------------------------------- */
/* This message changes the memory card power scheme.
   The actual power scheme selected depends on requests received from all
   registered clients.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Power scheme
       Values from the constant table FILE2_MEMORY_CARD_POWER_SCHEME_TYPE
    */
    uint8   power_scheme;
    uint8   fill1;
    /* Power down timeout in seconds to be set with
       FILE2_MEMORY_CARD_POWER_SCHEME_POWER_DOWN_DELAY request
    */
    uint16  timeout;
    /* Client ID received through
       FILE2_MEMORY_CARD_POWER_SCHEME_CLIENT_REQ/RESP messages
    */
    uint16  client_ID;
    } FILE2_MEMORY_CARD_POWER_SCHEME_SET_REQ_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_MEMORY_CARD_POWER_SCHEME_SET_RESP                        */
/* ----------------------------------------------------------------------- */
/* Response message */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Status
       A subset of values from the constant table FILE2_STATUS
    */
    uint8   status;
    uint8   fill1;
    } FILE2_MEMORY_CARD_POWER_SCHEME_SET_RESP_STR;


/* ----------------------------------------------------------------------- */
/* Message: FILE2_DRIVE_QUOTA_IND - Valid from version 033.000             */
/* ----------------------------------------------------------------------- */
/* This indication is sent when drive quota hysteresis limits are met.
   Application can notify user to delete some files or stop notifying user if
   enough space has been freed. 
   Note! FILE2_QUOTA_OK/SAFE can be indicated only if it has been preceded at
   least once by indication of FILE2_QUOTA_NOTIFY/EXCEEDED.
   Note! Only sent for internal file system drives.
*/

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   quota_info; /* Values from the constant table FILE2_QUOTA_INFO */
    uint8   quota_percentage; /* Quota percentage */
    /* Minimum amount of free space in bytes that must be achieved. Valid
       only if Quota info is FILE2_QUOTA_EXCEEDED
    */
    uint32  min_free;
    FILE2_DRIVE_INFO_STR drive_info;
    } FILE2_DRIVE_QUOTA_IND_STR;




/* ----------------------------------------------------------------------- */
/* Notes                                                                   */
/* ----------------------------------------------------------------------- */
/*
   /1/   autogen documentation
         Intranet
         http://rdsuite.europe.nokia.com/products/autogen/documentation.asp
         Link: autogen documentation

   /2/   ISI Server Specification Documentation Guidelines
         Document code: XXXL7714-EN
         DocMan location: eslns42/SRV/Nokia
         DocMan: TP / WP Front End DocMan
         Filename: TP/WP/tpwpfendm.nsf

   /3/   ISI General Information
         Document code: XXXL7715-EN
         DocMan location: eslns42/SRV/Nokia
         DocMan: TP / WP Front End DocMan
         Filename: TP/WP/tpwpfendm.nsf

   /4/   ISI Common Message Descriptions
         Continuus Database: ou1gif
         Continuus Project: GIF_SPECS-ou1gif#browse
         Directory Path: GIF_SPECS/CoreSW
         Filename: i_comm_m.html

   /5/   ISI Common Feature Descriptions
         Continuus Database: ou1gif
         Continuus Project: GIF_SPECS-ou1gif#browse
         Directory Path: GIF_SPECS/CoreSW
         Filename:  i_comm_fp.doc

   /6/   MIME media types
         ftp://ftp.isi.edu/in-notes/iana/assignments/media-types/media-types 

   /7/   FMAN's supported file types
         /disks/corsa/work/mem/docs/file_fman/fman_file_types_list.doc

   /8/   File Manager Interface Specification
         Continuus database:    ou1gif
         Continuus project:     GIF_SPECS-ou1gif#browse
         Directory path:        GIF_SPECS/CoreSW
         Filename:              file_manager_if.doc 

   /9/   File system interface
         Continuus database:    ou1gif
         Continuus project:     GIF_SPECS-ou1gif#browse
         Directory path:        GIF_SPECS/CoreSW
         Filename:              filesys_if_spec.doc 

   /10/  File2 Application Support Library, FASL
         Continuus database:    ou1gif
         Continuus project:     GIF_SPECS-ou1gif#browse
         Directory path:        GIF_SPECS/CoreSW
         Filename:              file2_asl_spec.doc 
*/


#endif /* _FILE_ISI_H */
