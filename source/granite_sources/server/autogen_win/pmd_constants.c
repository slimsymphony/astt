/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                pmd_constants.c
                ---------------
                SW Module






Project:          autogen

%name:            pmd_constants.c %
%version:         155 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Tue Feb 08 13:54:16 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Source file for autogen / TSS Tracing SDK

    This file contains lookup functions for string versions of the PMD constants (pmdconstants.h)
*/

/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pmdconstants.h"
#include "pn_const.h"

/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

pmd_constant pmd_constant_block_algorithm[PMD_BLOCK_ALGORITHM_MAX] =
{
    { "Raw data",           PMD_BLOCK_ALGORITHM_RAW_DATA },
    { "Identity",           PMD_BLOCK_ALGORITHM_IDENTITY },
    { "X-file",             PMD_BLOCK_ALGORITHM_X_FILE },
    { "Entry point",        PMD_BLOCK_ALGORITHM_ENTRYPOINT },
    { "External",           PMD_BLOCK_ALGORITHM_EXTERNAL }
};

pmd_constant pmd_constant_character_type[PMD_CHARACTER_TYPE_MAX] =
{
    { "UNKNOWN",                PMD_CHARACTER_TYPE_UNKNOWN },
    { "BCD",                    PMD_CHARACTER_TYPE_BCD },
    { "ASCII",                  PMD_CHARACTER_TYPE_ASCII },
    { "UNICODE",                PMD_CHARACTER_TYPE_UNICODE },
    { "GSM",                    PMD_CHARACTER_TYPE_GSM },
    { "UTF8",                   PMD_CHARACTER_TYPE_UTF8 }
};

pmd_constant pmd_constant_environment_var_id[PMD_ENVIRONMENT_VAR_ID_MAX] =
{
    { "UNDEFINED",                     0 },
    { "MON_TRACE_BITMAP_ID",           PMD_ENVIRONMENT_VAR_ID_MON_TRACE_BITMAP_ID },
    { "MON_TRACE_BITMAP_LENGTH",       PMD_ENVIRONMENT_VAR_ID_MON_TRACE_BITMAP_LENGTH },
    { "MCU_OS_TIMER_INTERVAL",         PMD_ENVIRONMENT_VAR_ID_MCU_OS_TIMER_INTERVAL },
    { "MCU_SW_VERSION",                PMD_ENVIRONMENT_VAR_ID_MCU_SW_VERSION },
    { "CDSP_SW_VERSION",               PMD_ENVIRONMENT_VAR_ID_CDSP_SW_VERSION },
    { "ADSP_SW_VERSION",               PMD_ENVIRONMENT_VAR_ID_ADSP_SW_VERSION },
    { "PMD_FILE_TYPE",                 PMD_ENVIRONMENT_VAR_ID_PMD_FILE_TYPE },
    { "PMD_FILE_DESCRIPTION",          PMD_ENVIRONMENT_VAR_ID_PMD_FILE_DESCRIPTION },
    { "PMD_FILE_MODIFY_DATE",          PMD_ENVIRONMENT_VAR_ID_PMD_FILE_MODIFY_DATE },
    { "PMD_FILE_ORIGIN",               PMD_ENVIRONMENT_VAR_ID_PMD_FILE_ORIGIN },
    { "CDMA_DSP_SW_VERSION",           PMD_ENVIRONMENT_VAR_ID_CDMA_DSP_SW_VERSION },
    { "PMD_FILE_RESTRICTION",          PMD_ENVIRONMENT_VAR_ID_PMD_FILE_RESTRICTION },
    { "SW_VERSION",                    PMD_ENVIRONMENT_VAR_ID_SW_VERSION },
    { "MONITOR_SERVER_RESOURCE_ID",    PMD_ENVIRONMENT_VAR_ID_MONITOR_SERVER_RESOURCE_ID },
    { "MONITOR_SERVER_VERSION",        PMD_ENVIRONMENT_VAR_ID_MONITOR_SERVER_VERSION },
    { "DEVICE_ENDIANESS",              PMD_ENVIRONMENT_VAR_ID_DEVICE_ENDIANESS },

    { "MCU_OS_BLOCK_ALIGN",                    PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_ALIGN },
    { "MCU_OS_HEADER_DATA_SIZE",               PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEADER_DATA_SIZE },
    { "MCU_OS_SYSTEM_STACK_SIZE",              PMD_ENVIRONMENT_VAR_ID_MCU_OS_SYSTEM_STACK_SIZE },
    { "MCU_OS_SYSTEM_STACK_1_SIZE",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_SYSTEM_STACK_1_SIZE },
    { "MCU_OS_STATIC_HEAP_SIZE",               PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_HEAP_SIZE },
    { "MCU_OS_AUX_HEAP_AREAS",                 PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_HEAP_AREAS },
    { "MCU_OS_HEAP_SIZE_MIN",                  PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_SIZE_MIN },
    { "MCU_OS_HEAP_SIZE_MAX",                  PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_SIZE_MAX },
    { "MCU_OS_HEAP_AREA_1_SIZE",               PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_AREA_1_SIZE },
    { "MCU_OS_HEAP_AREA_2_SIZE",               PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_AREA_2_SIZE },
    { "MCU_OS_AUX_SLOW_HEAP_AREAS",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_SLOW_HEAP_AREAS },
    { "MCU_OS_SLOW_HEAP_SIZE_MIN",             PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_SIZE_MIN },
    { "MCU_OS_SLOW_HEAP_SIZE_MAX",             PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_SIZE_MAX },
    { "MCU_OS_SLOW_HEAP_AREA_1_SIZE",          PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_AREA_1_SIZE },
    { "MCU_OS_SLOW_HEAP_AREA_2_SIZE",          PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_AREA_2_SIZE },
    { "MCU_OS_DYNAMIC_TASK_AMOUNT",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_AMOUNT },
    { "MCU_OS_DYNAMIC_TIMER_AMOUNT",           PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TIMER_AMOUNT },
    { "MCU_OS_DYNAMIC_TASK_HIGH_PRIORITY",     PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_HIGH_PRIORITY },
    { "MCU_OS_DYNAMIC_TASK_LOW_PRIORITY",      PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TASK_LOW_PRIORITY },
    { "MCU_OS_STACK_MULTIPLY",                 PMD_ENVIRONMENT_VAR_ID_MCU_OS_STACK_MULTIPLY },
    { "MCU_OS_64K_TIMERS",                     PMD_ENVIRONMENT_VAR_ID_MCU_OS_64K_TIMERS },
    { "MCU_OS_REG_EVENT_TIMER_INT",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_REG_EVENT_TIMER_INT },
    { "MCU_OS_FILL_STACKS",                    PMD_ENVIRONMENT_VAR_ID_MCU_OS_FILL_STACKS },
    { "MCU_OS_MONITOR",                        PMD_ENVIRONMENT_VAR_ID_MCU_OS_MONITOR },
    { "MCU_OS_DYNAMIC_TRACE_CONTROL",          PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_TRACE_CONTROL },
    { "MCU_OS_PORTABLE_LOG",                   PMD_ENVIRONMENT_VAR_ID_MCU_OS_PORTABLE_LOG },
    { "MCU_OS_ERROR_CHK",                      PMD_ENVIRONMENT_VAR_ID_MCU_OS_ERROR_CHK },
    { NULL,                                    57 },
    { "MCU_OS_AUX_DEALLOC_AREA_LO",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_DEALLOC_AREA_LO },
    { "MCU_OS_AUX_DEALLOC_AREA_HI",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_AUX_DEALLOC_AREA_HI },
    { "MCU_OS_BLOCK_PTR_VALIDITY_CHECK",       PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_PTR_VALIDITY_CHECK },
    { "MCU_OS_POOL_CALLER_DEPTH",              PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_CALLER_DEPTH },
    { "MCU_OS_POOL_HEADER_CALLER_STORE",       PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_HEADER_CALLER_STORE },
    { "MCU_OS_POOL_DEALLOCATOR_STORE",         PMD_ENVIRONMENT_VAR_ID_MCU_OS_POOL_DEALLOCATOR_STORE },
    { "MCU_OS_POST_MORTEM_CALLER_STORE",       PMD_ENVIRONMENT_VAR_ID_MCU_OS_POST_MORTEM_CALLER_STORE },
    { "MCU_OS_POST_MORTEM_CALLER_COUNT",       PMD_ENVIRONMENT_VAR_ID_MCU_OS_POST_MORTEM_CALLER_COUNT },
    { "MCU_OS_LAZY_FN_CALLER",                 PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAZY_FN_CALLER },
    { "MCU_OS_FAILSAFE_STACK_SIZE",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_FAILSAFE_STACK_SIZE },
    { "MCU_OS_IRQ_STACK_LOW_WARNING",          PMD_ENVIRONMENT_VAR_ID_MCU_OS_IRQ_STACK_LOW_WARNING },
    { "MCU_OS_TASK_STACK_LOW_WARNING",         PMD_ENVIRONMENT_VAR_ID_MCU_OS_TASK_STACK_LOW_WARNING },
    { "MCU_OS_UPP_MTC_AWAKE_TIMER_LENGTH",     PMD_ENVIRONMENT_VAR_ID_MCU_OS_UPP_MTC_AWAKE_TIMER_LENGTH },
    { "MCU_OS_UPP_MTC_AWAKE_DSPGPT_OPTIMIZATION",  PMD_ENVIRONMENT_VAR_ID_MCU_OS_UPP_MTC_AWAKE_DSPGPT_OPTIMIZATION },
    { "MCU_OS_REG_EVENT_TICK",                 PMD_ENVIRONMENT_VAR_ID_MCU_OS_REG_EVENT_TICK },
    { "MCU_OS_REG_EVENT_SETTLE_TIME",          PMD_ENVIRONMENT_VAR_ID_MCU_OS_REG_EVENT_SETTLE_TIME },
    { "MCU_OS_MINIMUM_SLEEP_TIME",             PMD_ENVIRONMENT_VAR_ID_MCU_OS_MINIMUM_SLEEP_TIME },
    { "MCU_OS_MULTIPLE_REG_EVENT_SOURCES",     PMD_ENVIRONMENT_VAR_ID_MCU_OS_MULTIPLE_REG_EVENT_SOURCES },
    { "MCU_OS_SIMULATED_REG_EVENT_INT",        PMD_ENVIRONMENT_VAR_ID_MCU_OS_SIMULATED_REG_EVENT_INT },
    { "MCU_OS_FREE_RUNNING_TIMER_USED",        PMD_ENVIRONMENT_VAR_ID_MCU_OS_FREE_RUNNING_TIMER_USED },
    { "MCU_OS_LONG_SW_TIMERS",                 PMD_ENVIRONMENT_VAR_ID_MCU_OS_LONG_SW_TIMERS },
    { "MCU_OS_CURRENT_TIME_USED",              PMD_ENVIRONMENT_VAR_ID_MCU_OS_CURRENT_TIME_USED },
    { "MCU_OS_CURRENT_TIME_IN_MS",             PMD_ENVIRONMENT_VAR_ID_MCU_OS_CURRENT_TIME_IN_MS },
    { "MCU_OS_RESOURCE_ACTIVATION",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_ACTIVATION },
    { "MCU_OS_RESOURCE_INIT_VALUE",            PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_INIT_VALUE },
    { "MCU_OS_FATAL_OWNER_BLOCKING_RESOURCE",  PMD_ENVIRONMENT_VAR_ID_MCU_OS_FATAL_OWNER_BLOCKING_RESOURCE },
    { "MCU_OS_FATAL_BLOCKING_ALLOC",           PMD_ENVIRONMENT_VAR_ID_MCU_OS_FATAL_BLOCKING_ALLOC },
    { "MCU_OS_HEAP_FIRST_FIT",                 PMD_ENVIRONMENT_VAR_ID_MCU_OS_HEAP_FIRST_FIT },
    { "MCU_OS_SLOW_HEAP_IN_USE",               PMD_ENVIRONMENT_VAR_ID_MCU_OS_SLOW_HEAP_IN_USE },
    { "MCU_OS_DYNAMIC_MEMORY_SERVICE",         PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_MEMORY_SERVICE },
    { "MCU_OS_REGION_AMOUNT",                  PMD_ENVIRONMENT_VAR_ID_MCU_OS_REGION_AMOUNT },
    { "MCU_OS_STATIC_TASK_NAMES",              PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_TASK_NAMES },
    { "MCU_OS_STATIC_TIMER_NAMES",             PMD_ENVIRONMENT_VAR_ID_MCU_OS_STATIC_TIMER_NAMES },
    { "MCU_OS_TASK_AMOUNT",                    PMD_ENVIRONMENT_VAR_ID_MCU_OS_TASK_AMOUNT },
    { "MCU_OS_BLOCK_SET_AMOUNT",               PMD_ENVIRONMENT_VAR_ID_MCU_OS_BLOCK_SET_AMOUNT },
    { "MCU_OS_RESOURCE_AMOUNT",                PMD_ENVIRONMENT_VAR_ID_MCU_OS_RESOURCE_AMOUNT },
    { "MCU_OS_TIMER_AMOUNT",                   PMD_ENVIRONMENT_VAR_ID_MCU_OS_TIMER_AMOUNT },
    { "MCU_OS_DYNAMIC_RESOURCE_AMOUNT",        PMD_ENVIRONMENT_VAR_ID_MCU_OS_DYNAMIC_RESOURCE_AMOUNT },

    { NULL,                                    100 /*PMD_ENVIRONMENT_VAR_ID_PRODUCT_PROJECT*/ },
    { "PRODUCT_NAME",                          PMD_ENVIRONMENT_VAR_ID_PRODUCT_NAME },
    { "PRODUCT_COMPILER_TYPE",                 PMD_ENVIRONMENT_VAR_ID_PRODUCT_COMPILER_TYPE },
    { "PRODUCT_TEST_ENV",                      PMD_ENVIRONMENT_VAR_ID_PRODUCT_TEST_ENV },
    { "PRODUCT_OS_TYPE",                       PMD_ENVIRONMENT_VAR_ID_PRODUCT_OS_TYPE },
    { "PRODUCT_CS_TYPE",                       PMD_ENVIRONMENT_VAR_ID_PRODUCT_CS_TYPE },

    { "ICF_3D_IMAGES",                         PMD_ENVIRONMENT_VAR_ID_ICF_3D_IMAGES },
    { "ICF_3RD_PARTY_VIDEOCODEC",              PMD_ENVIRONMENT_VAR_ID_ICF_3RD_PARTY_VIDEOCODEC },
    { "ICF_ACC_SERV",                          PMD_ENVIRONMENT_VAR_ID_ICF_ACC_SERV },
    { "ICF_ADL_SERV",                          PMD_ENVIRONMENT_VAR_ID_ICF_ADL_SERV },
    { "ICF_APPL",                              PMD_ENVIRONMENT_VAR_ID_ICF_APPL },
    { "ICF_ASSERT_LIB",                        PMD_ENVIRONMENT_VAR_ID_ICF_ASSERT_LIB },
    { "ICF_ATK",                               PMD_ENVIRONMENT_VAR_ID_ICF_ATK },
    { "ICF_AUDIO_SERV",                        PMD_ENVIRONMENT_VAR_ID_ICF_AUDIO_SERV },
    { "ICF_AUXILIARY_SW_DOWNLOAD",             PMD_ENVIRONMENT_VAR_ID_ICF_AUXILIARY_SW_DOWNLOAD },
    { "ICF_BOTTOM_CONNECTOR",                  PMD_ENVIRONMENT_VAR_ID_ICF_BOTTOM_CONNECTOR },
    { "ICF_BT",                                PMD_ENVIRONMENT_VAR_ID_ICF_BT },
    { "ICF_BT_AUDIO_STREAMING",                PMD_ENVIRONMENT_VAR_ID_ICF_BT_AUDIO_STREAMING },
    { "ICF_BT_AVRCP_TARGET",                   PMD_ENVIRONMENT_VAR_ID_ICF_BT_AVRCP_TARGET },
    { "ICF_BTCS_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_BTCS_SERV },
    { "ICF_BTIF_LIB",                          PMD_ENVIRONMENT_VAR_ID_ICF_BTIF_LIB },
    { "ICF_CAMERA",                            PMD_ENVIRONMENT_VAR_ID_ICF_CAMERA },
    { "ICF_CAMERA_HAL",                        PMD_ENVIRONMENT_VAR_ID_ICF_CAMERA_HAL },
    { "ICF_CAMERA_SERV",                       PMD_ENVIRONMENT_VAR_ID_ICF_CAMERA_SERV },
    { "ICF_CDB_LIB",                           PMD_ENVIRONMENT_VAR_ID_ICF_CDB_LIB },
    { NULL,                                    219 /* PMD_ENVIRONMENT_VAR_ID_ICF_CHANGELOG_LIB */ },
    { "ICF_CL",                                PMD_ENVIRONMENT_VAR_ID_ICF_CL },
    { NULL,                                    221 },
    { "ICF_COMPASS",                           PMD_ENVIRONMENT_VAR_ID_ICF_COMPASS },
    { "ICF_COMP_LIB",                          PMD_ENVIRONMENT_VAR_ID_ICF_COMP_LIB },
    { "ICF_CONTTYPE_LIB",                      PMD_ENVIRONMENT_VAR_ID_ICF_CONTTYPE_LIB },
    { "ICF_CORE_ONLY_BUILD",                   PMD_ENVIRONMENT_VAR_ID_ICF_CORE_ONLY_BUILD },
    { "ICF_CORE_WAKEUP",                       PMD_ENVIRONMENT_VAR_ID_ICF_CORE_WAKEUP },
    { "ICF_CRASH_DUMP",                        PMD_ENVIRONMENT_VAR_ID_ICF_CRASH_DUMP },
    { "ICF_CRYPTO_LIB",                        PMD_ENVIRONMENT_VAR_ID_ICF_CRYPTO_LIB },
    { "ICF_CS_DATA",                           PMD_ENVIRONMENT_VAR_ID_ICF_CS_DATA },
    { "ICF_CXML_LIB",                          PMD_ENVIRONMENT_VAR_ID_ICF_CXML_LIB },
    { "ICF_D2D_COPY",                          PMD_ENVIRONMENT_VAR_ID_ICF_D2D_COPY },
    { "ICF_D2D_SYNC",                          PMD_ENVIRONMENT_VAR_ID_ICF_D2D_SYNC },
    { "ICF_DCT4_SIM_SERVER",                   PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SERVER },
    { "ICF_DCT4_SIM_SERVER_SUBSET",            PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SERVER_SUBSET },
    { "ICF_DCT4_SIM_SUBSYSTEM",                PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SUBSYSTEM },
    { "ICF_DCT4_SIM_SUBSYSTEM_SUBSET",         PMD_ENVIRONMENT_VAR_ID_ICF_DCT4_SIM_SUBSYSTEM_SUBSET },
    { "ICF_DISP",                              PMD_ENVIRONMENT_VAR_ID_ICF_DISP },
    { "ICF_DSS",                               PMD_ENVIRONMENT_VAR_ID_ICF_DSS },
    { "ICF_DUAL_MCU",                          PMD_ENVIRONMENT_VAR_ID_ICF_DUAL_MCU },
    { "ICF_EM",                                PMD_ENVIRONMENT_VAR_ID_ICF_EM },
    { "ICF_FASTMON_LIB",                       PMD_ENVIRONMENT_VAR_ID_ICF_FASTMON_LIB },
    { "ICF_FBUS",                              PMD_ENVIRONMENT_VAR_ID_ICF_FBUS },
    { "ICF_FILE_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_FILE_SERV },
    { "ICF_FILE2",                             PMD_ENVIRONMENT_VAR_ID_ICF_FILE2 },
    { "ICF_FILE2_ASL_SUPPORT",                 PMD_ENVIRONMENT_VAR_ID_ICF_FILE2_ASL_SUPPORT },
    { "ICF_FLIGHT_MODE",                       PMD_ENVIRONMENT_VAR_ID_ICF_FLIGHT_MODE },
    { "ICF_FM_RADIO",                          PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO },
    { NULL,                                    248 },
    { "ICF_FM_RADIO_CHIP",                     PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO_CHIP },
    { "ICF_FM_RADIO_SERV",                     PMD_ENVIRONMENT_VAR_ID_ICF_FM_RADIO_SERV },
    { NULL,                                    251 /* PMD_ENVIRONMENT_VAR_ID_ICF_FMAN_IF */ },
    { "ICF_FMAN_LIB",                          PMD_ENVIRONMENT_VAR_ID_ICF_FMAN_LIB },
    { "ICF_FTS_APPL",                          PMD_ENVIRONMENT_VAR_ID_ICF_FTS_APPL },
    { NULL,                                    254 /*PMD_ENVIRONMENT_VAR_ID_ICF_FUNCTIONAL_COVERS*/ },
    { "ICF_GDI",                               PMD_ENVIRONMENT_VAR_ID_ICF_GDI },
    { "ICF_GPRS",                              PMD_ENVIRONMENT_VAR_ID_ICF_GPRS },
    { "ICF_HAL_I2C",                           PMD_ENVIRONMENT_VAR_ID_ICF_HAL_I2C },
    { "ICF_HAL_LCD_LITE",                      PMD_ENVIRONMENT_VAR_ID_ICF_HAL_LCD_LITE },
    { "ICF_HAL_LIGHT_LITE",                    PMD_ENVIRONMENT_VAR_ID_ICF_HAL_LIGHT_LITE },
    { "ICF_HAL_HW_PMM_LITE",                   PMD_ENVIRONMENT_VAR_ID_ICF_HAL_HW_PMM_LITE },
    { "ICF_HSM_LIB",                           PMD_ENVIRONMENT_VAR_ID_ICF_HSM_LIB },
    { NULL,                                    262 /*PMD_ENVIRONMENT_VAR_ID_ICF_HTTP_SUPPORT*/ },
    { "ICF_HWDRV",                             PMD_ENVIRONMENT_VAR_ID_ICF_HWDRV },
    { "ICF_HW_GENERATION",                     PMD_ENVIRONMENT_VAR_ID_ICF_HW_GENERATION },
    { NULL,                                    265 /*PMD_ENVIRONMENT_VAR_ID_ICF_I2C_CORE_SERV*/ },
    { "ICF_IMAGES",                            PMD_ENVIRONMENT_VAR_ID_ICF_IMAGES },
    { "ICF_IMAGE_ENGINE_LIB",                  PMD_ENVIRONMENT_VAR_ID_ICF_IMAGE_ENGINE_LIB },
    { "ICF_IMM_LIB",                           PMD_ENVIRONMENT_VAR_ID_ICF_IMM_LIB },
    { NULL,                                    269 },
    { "ICF_IMPLIB_LIB",                        PMD_ENVIRONMENT_VAR_ID_ICF_IMPLIB_LIB },
    { "ICF_INFO_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_INFO_SERV },
    { "ICF_IRDA",                              PMD_ENVIRONMENT_VAR_ID_ICF_IRDA },
    { "ICF_ISA2",                              PMD_ENVIRONMENT_VAR_ID_ICF_ISA2 },
    { "ICF_ISA_UI",                            PMD_ENVIRONMENT_VAR_ID_ICF_ISA_UI },
    { NULL,                                    275 /* PMD_ENVIRONMENT_VAR_ID_ICF_JAPANESE_INPUT */ },
    { "ICF_JAVA_APPS_FILE2_SUPPORT",           PMD_ENVIRONMENT_VAR_ID_ICF_JAVA_APPS_FILE2_SUPPORT },
    { "ICF_KASUMI_LIB",                        PMD_ENVIRONMENT_VAR_ID_ICF_KASUMI_LIB },
    { "ICF_KBD_SERV",                          PMD_ENVIRONMENT_VAR_ID_ICF_KBD_SERV },
    { "ICF_LBEC",                              PMD_ENVIRONMENT_VAR_ID_ICF_LBEC },
    { "ICF_LCD_LIB",                           PMD_ENVIRONMENT_VAR_ID_ICF_LCD_LIB },
    { "ICF_LCIF_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_LCIF_SERV },
    { "ICF_LIBRARIES",                         PMD_ENVIRONMENT_VAR_ID_ICF_LIBRARIES },
    { "ICF_LIGHT_SERV",                        PMD_ENVIRONMENT_VAR_ID_ICF_LIGHT_SERV },
    { "ICF_LIST_LIB",                          PMD_ENVIRONMENT_VAR_ID_ICF_LIST_LIB },
    { "ICF_LOCATION",                          PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION },
    { "ICF_LOCATION_GOPHERS_LTM",              PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_GOPHERS_LTM },
    { "ICF_LOCATION_SERV",                     PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_SERV },
    { "ICF_LOCATION_TEST_LTM",                 PMD_ENVIRONMENT_VAR_ID_ICF_LOCATION_TEST_LTM },
    { "ICF_MAX_VOICE_MODELS",                  PMD_ENVIRONMENT_VAR_ID_ICF_MAX_VOICE_MODELS },
    { NULL,                                    290 /* PMD_ENVIRONMENT_VAR_ID_ICF_MBUS */ },
    { "ICF_MEDIA",                             PMD_ENVIRONMENT_VAR_ID_ICF_MEDIA },
    { NULL,                                    292 },
    { NULL,                                    293 /* PMD_ENVIRONMENT_VAR_ID_ICF_MMC_SUPPORT */ },
    { NULL,                                    294 /* PMD_ENVIRONMENT_VAR_ID_ICF_MMS_FILE2_SUPPORT */ },
    { "ICF_MONITOR_SERV",                      PMD_ENVIRONMENT_VAR_ID_ICF_MONITOR_SERV },
    { "ICF_MS_ASIC_FAMILY",                    PMD_ENVIRONMENT_VAR_ID_ICF_MS_ASIC_FAMILY },
    { "ICF_MTC_SERV",                          PMD_ENVIRONMENT_VAR_ID_ICF_MTC_SERV },
    { "ICF_MUSIC",                             PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC },
    { "ICF_MUSIC_SERV",                        PMD_ENVIRONMENT_VAR_ID_ICF_MUSIC_SERV },
    { NULL,                                    300 },
    { "ICF_NAND_FLASH",                        PMD_ENVIRONMENT_VAR_ID_ICF_NAND_FLASH },
    { "ICF_NMPRT_LIB",                         PMD_ENVIRONMENT_VAR_ID_ICF_NMPRT_LIB },
    { "ICF_NOR_DIRECT_CONTENT_FLASHING",       PMD_ENVIRONMENT_VAR_ID_ICF_NOR_DIRECT_CONTENT_FLASHING },
    { "ICF_NOR_FLASH",                         PMD_ENVIRONMENT_VAR_ID_ICF_NOR_FLASH },
    { "ICF_NOTEPAD_SUPPORT",                   PMD_ENVIRONMENT_VAR_ID_ICF_NOTEPAD_SUPPORT },
    { "ICF_NVD_SERV",                          PMD_ENVIRONMENT_VAR_ID_ICF_NVD_SERV },
    { "ICF_OBEX_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_OBEX_SERV },
    { "ICF_ODIN_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_ODIN_SERV },
    { "ICF_OMA_DM",                            PMD_ENVIRONMENT_VAR_ID_ICF_OMA_DM },
    { "ICF_OMA_DS",                            PMD_ENVIRONMENT_VAR_ID_ICF_OMA_DS },
    { "ICF_OS",                                PMD_ENVIRONMENT_VAR_ID_ICF_OS },
    { "ICF_OTA",                               PMD_ENVIRONMENT_VAR_ID_ICF_OTA },
    { "ICF_OTI",                               PMD_ENVIRONMENT_VAR_ID_ICF_OTI },
    { "ICF_PERM_DATA_FILLERS",                 PMD_ENVIRONMENT_VAR_ID_ICF_PERM_DATA_FILLERS },
    { "ICF_PERM_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_PERM_SERV },
    { "ICF_PMM",                               PMD_ENVIRONMENT_VAR_ID_ICF_PMM },
    { "ICF_PMM_GENERATION",                    PMD_ENVIRONMENT_VAR_ID_ICF_PMM_GENERATION },
    { "ICF_PMM2",                              PMD_ENVIRONMENT_VAR_ID_ICF_PMM2 },
    { "ICF_PN_MEDIA_BT",                       PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_BT },
    { NULL,                                    320 /* PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_ENOS */ },
    { "ICF_PN_MEDIA_I2C",                      PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_I2C },
    { "ICF_PN_MEDIA_IR",                       PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_IR },
    { "ICF_PN_MEDIA_IRDA",                     PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_IRDA },
    { NULL,                                    324 /* PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MBUS */ },
    { "ICF_PN_MEDIA_MDI",                      PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MDI },
    { "ICF_PN_MEDIA_MSTI",                     PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MSTI },
    { NULL,                                    327 /* PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_RS232 */ },
    { "ICF_PN_MEDIA_SOS_USB",                  PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_SOS_USB },
    { "ICF_PN_MEDIA_STI",                      PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_STI },
    { "ICF_PN_MEDIA_TCPIP",                    PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_TCPIP },
    { "ICF_PN_MEDIA_TRUST",                    PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_TRUST },
    { "ICF_PN_MEDIA_USB",                      PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_USB },
    { "ICF_PN_MEDIA_XTI",                      PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_XTI },
    { "ICF_PN_TERMINAL_ADAPTER",               PMD_ENVIRONMENT_VAR_ID_ICF_PN_TERMINAL_ADAPTER },
    { "ICF_POC_SUPPORT",                       PMD_ENVIRONMENT_VAR_ID_ICF_POC_SUPPORT },
    { "ICF_PPM_AS_FILES",                      PMD_ENVIRONMENT_VAR_ID_ICF_PPM_AS_FILES },
    { "ICF_PRODUCT_TYPE",                      PMD_ENVIRONMENT_VAR_ID_ICF_PRODUCT_TYPE },
    { "ICF_RENDER_3D_LIB",                     PMD_ENVIRONMENT_VAR_ID_ICF_RENDER_3D_LIB },
    { NULL,                                    339 /* PMD_ENVIRONMENT_VAR_ID_ICF_RS232 */ },
    { NULL,                                    340 /*PMD_ENVIRONMENT_VAR_ID_ICF_SBC_SERV*/ },
    { "ICF_SCSI_PARSER",                       PMD_ENVIRONMENT_VAR_ID_ICF_SCSI_PARSER },
    { NULL,                                    342 /*PMD_ENVIRONMENT_VAR_ID_ICF_SDND*/ },
    { "ICF_SECENV",                            PMD_ENVIRONMENT_VAR_ID_ICF_SECENV },
    { "ICF_SECURITY",                          PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY },
    { "ICF_SECURITY_LIB",                      PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY_LIB },
    { "ICF_SENSOR_SERV",                       PMD_ENVIRONMENT_VAR_ID_ICF_SENSOR_SERV },
    { "ICF_SERVERS",                           PMD_ENVIRONMENT_VAR_ID_ICF_SERVERS },
    { "ICF_SETTINGS_AS_FILES",                 PMD_ENVIRONMENT_VAR_ID_ICF_SETTINGS_AS_FILES },
    { "ICF_SIM",                               PMD_ENVIRONMENT_VAR_ID_ICF_SIM },
    { "ICF_SIM_ATK",                           PMD_ENVIRONMENT_VAR_ID_ICF_SIM_ATK },
    { NULL,                                    351 },
    { NULL,                                    352 },
    { NULL,                                    353 },
    { NULL,                                    354 },
    { NULL,                                    355 },
    { NULL,                                    356 },
    { NULL,                                    357 },
    { NULL,                                    358 },
    { NULL,                                    359 },
    { NULL,                                    360 },
    { "ICF_SIM_COMMON",                        PMD_ENVIRONMENT_VAR_ID_ICF_SIM_COMMON },
    { NULL,                                    362 },
    { "ICF_SIM_HWDRV",                         PMD_ENVIRONMENT_VAR_ID_ICF_SIM_HWDRV },
    { "ICF_SIM_HW_DRV",                        PMD_ENVIRONMENT_VAR_ID_ICF_SIM_HW_DRV },
    { "ICF_SIMLOCK",                           PMD_ENVIRONMENT_VAR_ID_ICF_SIMLOCK },
    { NULL,                                    366 /* PMD_ENVIRONMENT_VAR_ID_ICF_SIMSON_APDU */ },
    { NULL,                                    367 /* PMD_ENVIRONMENT_VAR_ID_ICF_SIMSON_SIM */ },
    { "ICF_SISA",                              PMD_ENVIRONMENT_VAR_ID_ICF_SISA },
    { "ICF_SNOR_SUPPORT",                      PMD_ENVIRONMENT_VAR_ID_ICF_SNOR_SUPPORT },
    { "ICF_SSI_LIB",                           PMD_ENVIRONMENT_VAR_ID_ICF_SSI_LIB },
    { "ICF_ST_SERV",                           PMD_ENVIRONMENT_VAR_ID_ICF_ST_SERV },
    { "ICF_SUPERDONGLE",                       PMD_ENVIRONMENT_VAR_ID_ICF_SUPERDONGLE },
    { NULL,                                    373 },
    { NULL,                                    374 },
    { "ICF_SYNCML_SERV",                       PMD_ENVIRONMENT_VAR_ID_ICF_SYNCML_SERV },
    { "ICF_TASKS",                             PMD_ENVIRONMENT_VAR_ID_ICF_TASKS },
    { "ICF_TEST_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_TEST_SERV },
    { "ICF_TIME_SERV",                         PMD_ENVIRONMENT_VAR_ID_ICF_TIME_SERV },
    { "ICF_TIME_ZONE",                         PMD_ENVIRONMENT_VAR_ID_ICF_TIME_ZONE },
    { "ICF_TOUCHPAD",                          PMD_ENVIRONMENT_VAR_ID_ICF_TOUCHPAD },
    { "ICF_TOUCHPAD_SERV",                     PMD_ENVIRONMENT_VAR_ID_ICF_TOUCHPAD_SERV },
    { "ICF_TRACE_INTERFACE",                   PMD_ENVIRONMENT_VAR_ID_ICF_TRACE_INTERFACE },
    { "ICF_TTY_SUPPORT",                       PMD_ENVIRONMENT_VAR_ID_ICF_TTY_SUPPORT },
    { "ICF_UCS2_LIB",                          PMD_ENVIRONMENT_VAR_ID_ICF_UCS2_LIB },
    { "ICF_UI_THEMES",                         PMD_ENVIRONMENT_VAR_ID_ICF_UI_THEMES },
    { "ICF_URL_LIB",                           PMD_ENVIRONMENT_VAR_ID_ICF_URL_LIB },
    { "ICF_USB",                               PMD_ENVIRONMENT_VAR_ID_ICF_USB },
    { "ICF_USB_MASS_STORAGE",                  PMD_ENVIRONMENT_VAR_ID_ICF_USB_MASS_STORAGE },
    { "ICF_USB_MASS_STORAGE_INTERNAL_MEMORY",  PMD_ENVIRONMENT_VAR_ID_ICF_USB_MASS_STORAGE_INTERNAL_MEMORY },
    { NULL,                                    390 /* PMD_ENVIRONMENT_VAR_ID_ICF_USER_DATA_AS_FILES */ },
    { "ICF_VERSIT_SERV",                       PMD_ENVIRONMENT_VAR_ID_ICF_VERSIT_SERV },
    { "ICF_VIDEO",                             PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO },
    { "ICF_VIDEO_RECORDER",                    PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_RECORDER },
    { "ICF_VIDEOPLAYBACK",                     PMD_ENVIRONMENT_VAR_ID_ICF_VIDEOPLAYBACK },
    { "ICF_VOICE_RECORDING",                   PMD_ENVIRONMENT_VAR_ID_ICF_VOICE_RECORDING },
    { "ICF_VOICE_TAGS",                        PMD_ENVIRONMENT_VAR_ID_ICF_VOICE_TAGS },
    { "ICF_VRR_SERV",                          PMD_ENVIRONMENT_VAR_ID_ICF_VRR_SERV },
    { "ICF_XBUS_LIB",                          PMD_ENVIRONMENT_VAR_ID_ICF_XBUS_LIB },
    { "ICF_ZLIB_LIB",                          PMD_ENVIRONMENT_VAR_ID_ICF_ZLIB_LIB },
    { "ICF_BATT_CURRENT_MEASUREMENT",          PMD_ENVIRONMENT_VAR_ID_ICF_BATT_CURRENT_MEASUREMENT },
    { "ICF_ZLIB_DEFLATE",                      PMD_ENVIRONMENT_VAR_ID_ICF_ZLIB_DEFLATE },
    { "ICF_BT_FTP",                            PMD_ENVIRONMENT_VAR_ID_ICF_BT_FTP },
    { "ICF_I2C",                               PMD_ENVIRONMENT_VAR_ID_ICF_I2C },
    { "ICF_OFFLINE_MODE",                      PMD_ENVIRONMENT_VAR_ID_ICF_OFFLINE_MODE },
    { "ICF_HAC",                               PMD_ENVIRONMENT_VAR_ID_ICF_HAC },
    { "ICF_SVG",                               PMD_ENVIRONMENT_VAR_ID_ICF_SVG },
    { "ICF_LOADERLESS_ADL",                    PMD_ENVIRONMENT_VAR_ID_ICF_LOADERLESS_ADL },
    { "ICF_FLASH_DEVICES",                     PMD_ENVIRONMENT_VAR_ID_ICF_FLASH_DEVICES },
    { "ICF_SIND",                              PMD_ENVIRONMENT_VAR_ID_ICF_SIND },
    { "ICF_DEFAULT_BATTERY",                   PMD_ENVIRONMENT_VAR_ID_ICF_DEFAULT_BATTERY },
    { NULL,                                    411 /* PMD_ENVIRONMENT_VAR_ID_ICF_ISC_API */ },
    { NULL,                                    412 /* PMD_ENVIRONMENT_VAR_ID_ICF_WSM */ },
    { "ICF_WATCHDOG_SUPPORT",                  PMD_ENVIRONMENT_VAR_ID_ICF_WATCHDOG_SUPPORT },
    { "ICF_SLEEP_SUPPORT",                     PMD_ENVIRONMENT_VAR_ID_ICF_SLEEP_SUPPORT },
    { "ICF_SECURITY_KEYGUARD",                 PMD_ENVIRONMENT_VAR_ID_ICF_SECURITY_KEYGUARD },
    { NULL,                                    416 /* PMD_ENVIRONMENT_VAR_ID_ICF_WSM_DUMMY_CRYPTO */ },
    { "ICF_NO_PMM_CLASS",                      PMD_ENVIRONMENT_VAR_ID_ICF_NO_PMM_CLASS },
    { NULL,                                    418 /* PMD_ENVIRONMENT_VAR_ID_ICF_RAT_DAMPS */ },
    { "ICF_OBEX",                              PMD_ENVIRONMENT_VAR_ID_ICF_OBEX },
    { "ICF_MEMORY_CARD_SUPPORT",               PMD_ENVIRONMENT_VAR_ID_ICF_MEMORY_CARD_SUPPORT },
    { NULL,                                    421 /* PMD_ENVIRONMENT_VAR_ID_ICF_SD_CARD_SUPPORT */},
    { "ICF_OVERLAY_UI",                        PMD_ENVIRONMENT_VAR_ID_ICF_OVERLAY_UI },
    { "ICF_HARDCORE_SERV",                     PMD_ENVIRONMENT_VAR_ID_ICF_HARDCORE_SERV },
    { "ICF_MEMORY_CARD_HOT_SWAP",              PMD_ENVIRONMENT_VAR_ID_ICF_MEMORY_CARD_HOT_SWAP },
    { "ICF_E3_PRODUCTION_BRANCH",              PMD_ENVIRONMENT_VAR_ID_ICF_E3_PRODUCTION_BRANCH },
    { "ICF_JSR82_SUPPORT",                     PMD_ENVIRONMENT_VAR_ID_ICF_JSR82_SUPPORT },
    { "ICF_HAL_ONLY",                          PMD_ENVIRONMENT_VAR_ID_ICF_HAL_ONLY },
    { "ICF_VIBRA",                             PMD_ENVIRONMENT_VAR_ID_ICF_VIBRA },
    { "ICF_VIBRA_IF_NEW",                      PMD_ENVIRONMENT_VAR_ID_ICF_VIBRA_IF_NEW },
    { "ICF_DISCO_LIGHTS",                      PMD_ENVIRONMENT_VAR_ID_ICF_DISCO_LIGHTS },
    { "ICF_OBEX_SERVER_MAX_FRAME_SIZE",        PMD_ENVIRONMENT_VAR_ID_ICF_OBEX_SERVER_MAX_FRAME_SIZE },
    { "IUF_LCIF",                              PMD_ENVIRONMENT_VAR_ID_IUF_LCIF },
    { "ICF_PICT_BRIDGE",                       PMD_ENVIRONMENT_VAR_ID_ICF_PICT_BRIDGE },
    { "ICF_USB_FLASHING",                      PMD_ENVIRONMENT_VAR_ID_ICF_USB_FLASHING },
    { "ICF_RF_BAND_VARIABILITY",               PMD_ENVIRONMENT_VAR_ID_ICF_RF_BAND_VARIABILITY },
    { "ICF_MULTIPART_ADDRESS_SUPPORT",         PMD_ENVIRONMENT_VAR_ID_ICF_MULTIPART_ADDRESS_SUPPORT },
    { "ICF_POWER_ON_BOOT_LOGO",                PMD_ENVIRONMENT_VAR_ID_ICF_POWER_ON_BOOT_LOGO },
    { NULL,                                    438 /* PMD_ENVIRONMENT_VAR_ID_ICF_AVE */ },
    { "ICF_STEREO_IHF",                        PMD_ENVIRONMENT_VAR_ID_ICF_STEREO_IHF },
    { "ICF_EAP",                               PMD_ENVIRONMENT_VAR_ID_ICF_EAP },
    { "ICF_HS23_SUPPORT",                      PMD_ENVIRONMENT_VAR_ID_ICF_HS23_SUPPORT },
    { "ICF_FMM_LIB",                           PMD_ENVIRONMENT_VAR_ID_ICF_FMM_LIB },
    { "ICF_UNIVERSAL_HEADSET",                 PMD_ENVIRONMENT_VAR_ID_ICF_UNIVERSAL_HEADSET },
    { "ICF_UNIVERSAL_STEREO",                  PMD_ENVIRONMENT_VAR_ID_ICF_UNIVERSAL_STEREO },
    { "ICF_3_5MM_AUDIO_PLUG",                  PMD_ENVIRONMENT_VAR_ID_ICF_3_5MM_AUDIO_PLUG },
    { "ICF_FBUS_ROUTING_SUPPORT",              PMD_ENVIRONMENT_VAR_ID_ICF_FBUS_ROUTING_SUPPORT },
    { "ICF_VIDEO_CALL",                        PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_CALL },
    { "ICF_VIDEO_SHARING",                     PMD_ENVIRONMENT_VAR_ID_ICF_VIDEO_SHARING },
    { NULL,                                    449 /* PMD_ENVIRONMENT_VAR_ID_ICF_CONTACT_BIRTHDAY */ },
    { NULL,                                    450 /* PMD_ENVIRONMENT_VAR_ID_ICF_CONTACT_FORMATTED_NAME */ },
    { NULL,                                    451 /* PMD_ENVIRONMENT_VAR_ID_ICF_CONTACT_NICKNAME */ },
    { NULL,                                    452 /* PMD_ENVIRONMENT_VAR_ID_ICF_CONTACT_TITLE_ORG */ },
    { "ICF_DUAL_OS",                           PMD_ENVIRONMENT_VAR_ID_ICF_DUAL_OS },
    { NULL,                                    454 },
    { NULL,                                    455 }, /* PMD_ENVIRONMENT_VAR_ID_ICF_CDMA_MOD */
    { "ICF_RAT_CDMA",                          PMD_ENVIRONMENT_VAR_ID_ICF_RAT_CDMA },
    { "ICF_PN_MEDIA_FBUS",                     PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_FBUS },
    { "ICF_WLAN",                              PMD_ENVIRONMENT_VAR_ID_ICF_WLAN },
    { "ICF_WLAN_DRV",                          PMD_ENVIRONMENT_VAR_ID_ICF_WLAN_DRV },
    { NULL,                                    460 }, /* PMD_ENVIRONMENT_VAR_ID_ICF_NAVIGATOR */
    { "ICF_LOADER",                            PMD_ENVIRONMENT_VAR_ID_ICF_LOADER },
    { "ICF_PN_MEDIA_MADI",                     PMD_ENVIRONMENT_VAR_ID_ICF_PN_MEDIA_MADI },
    { "ICF_SOS_PROXY",                         PMD_ENVIRONMENT_VAR_ID_ICF_SOS_PROXY },
    { "ICF_TUNEPLAYER_SERV",                   PMD_ENVIRONMENT_VAR_ID_ICF_TUNEPLAYER_SERV },
    { "ICF_IKE",                               PMD_ENVIRONMENT_VAR_ID_ICF_IKE },
    { "ICF_SSL",                               PMD_ENVIRONMENT_VAR_ID_ICF_SSL },
    { "ICF_FEATURE_CONTROL",                   PMD_ENVIRONMENT_VAR_ID_ICF_FEATURE_CONTROL },
    { "ICF_BCS_SERV",                          PMD_ENVIRONMENT_VAR_ID_ICF_BCS_SERV },
    { "ICF_STORAGE_EMMC_SUPPORT",              PMD_ENVIRONMENT_VAR_ID_ICF_STORAGE_EMMC_SUPPORT },
    { "ICF_SYSTEM_EMMC_SUPPORT",               PMD_ENVIRONMENT_VAR_ID_ICF_SYSTEM_EMMC_SUPPORT },
    { "ICF_NOKIA_VIRTUAL_SURROUND",            PMD_ENVIRONMENT_VAR_ID_ICF_NOKIA_VIRTUAL_SURROUND },
    { "ICF_USB_ACA_SUPPORT",                   PMD_ENVIRONMENT_VAR_ID_ICF_USB_ACA_SUPPORT },
    { "ICF_OPTIRENDER_LIB",                    PMD_ENVIRONMENT_VAR_ID_ICF_OPTIRENDER_LIB },
    { "ICF_POWER_RESOURCE_MANAGER",            PMD_ENVIRONMENT_VAR_ID_ICF_POWER_RESOURCE_MANAGER },
    { "ICF_ENO_PROTOCOL_SUPPORT",              PMD_ENVIRONMENT_VAR_ID_ICF_ENO_PROTOCOL_SUPPORT },

    { "IPF_3GPP_SPEC_RELEASE",                 PMD_ENVIRONMENT_VAR_ID_IPF_3GPP_SPEC_RELEASE },
    { NULL,                                    601 /* PMD_ENVIRONMENT_VAR_ID_IPF_A5_1 */ },
    { NULL,                                    602 /* PMD_ENVIRONMENT_VAR_ID_IPF_A5_2 */ },
    { NULL,                                    603 /* PMD_ENVIRONMENT_VAR_ID_IPF_A5_3 */ },
    { NULL,                                    604 /* PMD_ENVIRONMENT_VAR_ID_IPF_A5_4 */ },
    { NULL,                                    605 /* PMD_ENVIRONMENT_VAR_ID_IPF_A5_5 */ },
    { NULL,                                    606 /* PMD_ENVIRONMENT_VAR_ID_IPF_A5_6 */ },
    { NULL,                                    607 /* PMD_ENVIRONMENT_VAR_ID_IPF_A5_7 */ },
    { "IPF_ALS",                               PMD_ENVIRONMENT_VAR_ID_IPF_ALS },
    { NULL,                                    609 /* PMD_ENVIRONMENT_VAR_ID_IPF_AOC */ },
    { NULL,                                    610 /* PMD_ENVIRONMENT_VAR_ID_IPF_AOC_VOLUME_BASED */ },
    { "IPF_AUTO_QMEAS_IN_RANDOM_ACCESS",       PMD_ENVIRONMENT_VAR_ID_IPF_AUTO_QMEAS_IN_RANDOM_ACCESS },
    { NULL,                                    612 /* PMD_ENVIRONMENT_VAR_ID_IPF_BAND_E_GSM */ },
    { "IPF_BAND_GSM_450",                      PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_450 },
    { "IPF_BAND_GSM_480",                      PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_480 },
    { "IPF_BAND_GSM_700",                      PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_700 },
    { "IPF_BAND_GSM_850",                      PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_850 },
    { "IPF_BAND_GSM_900",                      PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_900 },
    { "IPF_BAND_GSM_1800",                     PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_1800 },
    { "IPF_BAND_GSM_1900",                     PMD_ENVIRONMENT_VAR_ID_IPF_BAND_GSM_1900 },
    { NULL,                                    620 /* PMD_ENVIRONMENT_VAR_ID_IPF_BAND_R_GSM */ },
    { NULL,                                    621 /* PMD_ENVIRONMENT_VAR_ID_IPF_BAND_UMTS_REGION_A */ },
    { NULL,                                    622 /* PMD_ENVIRONMENT_VAR_ID_IPF_BAND_UMTS_REGION_B*/ },
    { "IPF_BEARER_CONTROL",                    PMD_ENVIRONMENT_VAR_ID_IPF_BEARER_CONTROL },
    { "IPF_BTS_TEST",                          PMD_ENVIRONMENT_VAR_ID_IPF_BTS_TEST },
    { "IPF_BTS_TEST_WITH_NMEAS",               PMD_ENVIRONMENT_VAR_ID_IPF_BTS_TEST_WITH_NMEAS },
    { NULL,                                    626 /* PMD_ENVIRONMENT_VAR_ID_IPF_CALL_DEFLECTION */ },
    { "IPF_CALL_HOLD",                         PMD_ENVIRONMENT_VAR_ID_IPF_CALL_HOLD },
    { "IPF_CCBS",                              PMD_ENVIRONMENT_VAR_ID_IPF_CCBS },
    { NULL,                                    629 /* PMD_ENVIRONMENT_VAR_ID_IPF_CDMA_RAT */ },
    { "IPF_CELLMO_PLATFORM",                   PMD_ENVIRONMENT_VAR_ID_IPF_CELLMO_PLATFORM },
    { "IPF_CLIR",                              PMD_ENVIRONMENT_VAR_ID_IPF_CLIR },
    { "IPF_CNAP",                              PMD_ENVIRONMENT_VAR_ID_IPF_CNAP },
    { NULL,                                    633 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_AMR_FR */ },
    { NULL,                                    634 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_AMR_HR */ },
    { NULL,                                    635 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_AMR_WB */ },
    { NULL,                                    636 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_EFR */ },
    { NULL,                                    637 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_FR */ },
    { NULL,                                    638 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_GSM_HR */ },
    { NULL,                                    639 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_WCDMA_AMR */ },
    { NULL,                                    640 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_WCDMA_AMR_2 */ },
    { NULL,                                    641 /* PMD_ENVIRONMENT_VAR_ID_IPF_CODEC_WCDMA_AMR_WB */ },
    { "IPF_COMBINED_PSW_SYNC_MEAS",            PMD_ENVIRONMENT_VAR_ID_IPF_COMBINED_PSW_SYNC_MEAS },
    { NULL,                                    643 /* PMD_ENVIRONMENT_VAR_ID_IPF_COMMON_LARGE_MEM_BUFFER */ },
    { "IPF_CSD_24_CHANNEL_CODING",             PMD_ENVIRONMENT_VAR_ID_IPF_CSD_24_CHANNEL_CODING },
    { "IPF_CSD_48_CHANNEL_CODING",             PMD_ENVIRONMENT_VAR_ID_IPF_CSD_48_CHANNEL_CODING },
    { "IPF_CSD_96_CHANNEL_CODING",             PMD_ENVIRONMENT_VAR_ID_IPF_CSD_96_CHANNEL_CODING },
    { "IPF_CSD_144_CHANNEL_CODING",            PMD_ENVIRONMENT_VAR_ID_IPF_CSD_144_CHANNEL_CODING },
    { "IPF_CSD_MULTISLOT_CLASS",               PMD_ENVIRONMENT_VAR_ID_IPF_CSD_MULTISLOT_CLASS },
    { "IPF_CTM",                               PMD_ENVIRONMENT_VAR_ID_IPF_CTM },
    { "IPF_CUG",                               PMD_ENVIRONMENT_VAR_ID_IPF_CUG },
    { "IPF_DCM_DRIVE_MODE",                    PMD_ENVIRONMENT_VAR_ID_IPF_DCM_DRIVE_MODE },
    { "IPF_DCT_PLATFORM",                      PMD_ENVIRONMENT_VAR_ID_IPF_DCT_PLATFORM },
    { "IPF_DIGITAL_AFC",                       PMD_ENVIRONMENT_VAR_ID_IPF_DIGITAL_AFC },
    { "IPF_DTM",                               PMD_ENVIRONMENT_VAR_ID_IPF_DTM },
    { "IPF_DTM_EGPRS_MULTISLOT_CLASS",         PMD_ENVIRONMENT_VAR_ID_IPF_DTM_EGPRS_MULTISLOT_CLASS },
    { "IPF_DTM_GPRS_MULTISLOT_CLASS",          PMD_ENVIRONMENT_VAR_ID_IPF_DTM_GPRS_MULTISLOT_CLASS },
    { NULL,                                    657 /* PMD_ENVIRONMENT_VAR_ID_IPF_ECSD_MULTISLOT_CLASS */ },
    { "IPF_ECT",                               PMD_ENVIRONMENT_VAR_ID_IPF_ECT },
    { "IPF_EGPRS",                             PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS },
    { "IPF_EGPRS_8PSK_UPLINK",                 PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_8PSK_UPLINK },
    { "IPF_EGPRS_EXT_DYN_ALLOC",               PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_EXT_DYN_ALLOC },
    { "IPF_EGPRS_MULTISLOT_CLASS",             PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_MULTISLOT_CLASS },
    { "IPF_EGPRS_POWER_CLASS",                 PMD_ENVIRONMENT_VAR_ID_IPF_EGPRS_POWER_CLASS },
    { "IPF_EXT_DTM_EGPRS_MULTISLOT_CLASS",     PMD_ENVIRONMENT_VAR_ID_IPF_EXT_DTM_EGPRS_MULTISLOT_CLASS },
    { "IPF_EXT_DTM_GPRS_MULTISLOT_CLASS",      PMD_ENVIRONMENT_VAR_ID_IPF_EXT_DTM_GPRS_MULTISLOT_CLASS },
    { NULL,                                    666 },
    { "IPF_FDN",                               PMD_ENVIRONMENT_VAR_ID_IPF_FDN },
    { "IPF_FEATURE_CONTROL",                   PMD_ENVIRONMENT_VAR_ID_IPF_FEATURE_CONTROL },
    { NULL,                                    669 },
    { NULL,                                    670 /* PMD_ENVIRONMENT_VAR_ID_IPF_FLOW_CTRL_UL_SINGLE_CREDIT */ },
    { NULL,                                    671 /* PMD_ENVIRONMENT_VAR_ID_IPF_GEA1 */ },
    { NULL,                                    672 /* PMD_ENVIRONMENT_VAR_ID_IPF_GEA2 */ },
    { NULL,                                    673 /* PMD_ENVIRONMENT_VAR_ID_IPF_GEA3 */ },
    { NULL,                                    674 /* PMD_ENVIRONMENT_VAR_ID_IPF_GEA4 */ },
    { NULL,                                    675 /* PMD_ENVIRONMENT_VAR_ID_IPF_GEA5 */ },
    { NULL,                                    676 /* PMD_ENVIRONMENT_VAR_ID_IPF_GEA6 */ },
    { NULL,                                    677 /* PMD_ENVIRONMENT_VAR_ID_IPF_GEA7 */ },
    { NULL,                                    678 },
    { "IPF_GPRS_EXT_DYN_ALLOC",                PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_EXT_DYN_ALLOC },
    { NULL,                                    680 },
    { NULL,                                    681 /* PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_MAC_DSP_INTERFACE */ },
    { "IPF_GPRS_MULTISLOT_CLASS",              PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_MULTISLOT_CLASS },
    { "IPF_GPRS_NON_DRX_TIMER_VALUE",          PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_NON_DRX_TIMER_VALUE },
    { "IPF_GPRS_PDA_OPTIMIZATION",             PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_PDA_OPTIMIZATION },
    { "IPF_GPRS_READY_TIMER_UNIT",             PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_READY_TIMER_UNIT },
    { "IPF_GPRS_READY_TIMER_VALUE",            PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_READY_TIMER_VALUE },
    { "IPF_GPRS_RFC1144_HEADER_COMP",          PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC1144_HEADER_COMP },
    { "IPF_GPRS_RFC2507_HEADER_COMP",          PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC2507_HEADER_COMP },
    { "IPF_GPRS_RFC3095_HEADER_COMP",          PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_RFC3095_HEADER_COMP },
    { "IPF_GPRS_V42BIS_DATA_COMP",             PMD_ENVIRONMENT_VAR_ID_IPF_GPRS_V42BIS_DATA_COMP },
    { "IPF_GSM_CSD",                           PMD_ENVIRONMENT_VAR_ID_IPF_GSM_CSD },
    { "IPF_GSM_LCS_MS_BASED_EOTD",             PMD_ENVIRONMENT_VAR_ID_IPF_GSM_LCS_MS_BASED_EOTD },
    { "IPF_GSM_LOWER_BAND_POWER_CLASS",        PMD_ENVIRONMENT_VAR_ID_IPF_GSM_LOWER_BAND_POWER_CLASS },
    { "IPF_GSM_PS",                            PMD_ENVIRONMENT_VAR_ID_IPF_GSM_PS },
    { "IPF_GSM_RAT",                           PMD_ENVIRONMENT_VAR_ID_IPF_GSM_RAT },
    { "IPF_GSM_UPPER_BAND_POWER_CLASS",        PMD_ENVIRONMENT_VAR_ID_IPF_GSM_UPPER_BAND_POWER_CLASS },
    { NULL,                                    697 },
    { NULL,                                    698 /*PMD_ENVIRONMENT_VAR_ID_IPF_HTTP_CLIENT_PROTOCOL*/ },
    { NULL,                                    699 /*PMD_ENVIRONMENT_VAR_ID_IPF_HTTP_SERVER_PROTOCOL*/ },
    { NULL,                                    700 /*PMD_ENVIRONMENT_VAR_ID_IPF_IMPS*/ },
    { "IPF_IPV6",                              PMD_ENVIRONMENT_VAR_ID_IPF_IPV6 },
    { NULL,                                    702 /*PMD_ENVIRONMENT_VAR_ID_IPF_ISA2_ADAPTATION*/ },
    { "IPF_ISA_PLATFORM",                      PMD_ENVIRONMENT_VAR_ID_IPF_ISA_PLATFORM },
    { NULL,                                    704 /* PMD_ENVIRONMENT_VAR_ID_IPF_LCS */ },
    { NULL,                                    705 /* PMD_ENVIRONMENT_VAR_ID_IPF_LCS_AGPS */ },
    { "IPF_LCS_EOTD",                          PMD_ENVIRONMENT_VAR_ID_IPF_LCS_EOTD },
    { "IPF_LCS_MO_LR",                         PMD_ENVIRONMENT_VAR_ID_IPF_LCS_MO_LR },
    { "IPF_LCS_PRIVACY",                       PMD_ENVIRONMENT_VAR_ID_IPF_LCS_PRIVACY },
    { "IPF_LICENSE_BLOCK_OPTIMIZATION",        PMD_ENVIRONMENT_VAR_ID_IPF_LICENSE_BLOCK_OPTIMIZATION },
    { "IPF_MAX_PDP_CONTEXTS",                  PMD_ENVIRONMENT_VAR_ID_IPF_MAX_PDP_CONTEXTS },
    { "IPF_MPTY",                              PMD_ENVIRONMENT_VAR_ID_IPF_MPTY },
    { "IPF_MS_INIT_PDP_CONTEXT_MODIFICATION",  PMD_ENVIRONMENT_VAR_ID_IPF_MS_INIT_PDP_CONTEXT_MODIFICATION },
    { "IPF_MULTIMEDIA_CALL",                   PMD_ENVIRONMENT_VAR_ID_IPF_MULTIMEDIA_CALL },
    { NULL,                                    714 /* PMD_ENVIRONMENT_VAR_ID_IPF_NITZ */ },
    { NULL,                                    715 /* PMD_ENVIRONMENT_VAR_ID_IPF_NITZ_DAYLIGHT_TIME */ },
    { NULL,                                    716 /* PMD_ENVIRONMENT_VAR_ID_IPF_NO_MDI_DEACTIVATE_WHEN_SUSPEND */ },
    { "IPF_NOKIA_TEST_MOBILE",                 PMD_ENVIRONMENT_VAR_ID_IPF_NOKIA_TEST_MOBILE },
    { "IPF_NW_INIT_PDP_CONTEXT_ACTIVATION",    PMD_ENVIRONMENT_VAR_ID_IPF_NW_INIT_PDP_CONTEXT_ACTIVATION },
    { "IPF_OFFLINE_MODE",                      PMD_ENVIRONMENT_VAR_ID_IPF_OFFLINE_MODE },
    { "IPF_PERFORMANCE_TRACES",                PMD_ENVIRONMENT_VAR_ID_IPF_PERFORMANCE_TRACES },
    { "IPF_PERM_BTS_TEST_CARRIER",             PMD_ENVIRONMENT_VAR_ID_IPF_PERM_BTS_TEST_CARRIER },
    { "IPF_PERM_GPRS_AUTO_ATTACH",             PMD_ENVIRONMENT_VAR_ID_IPF_PERM_GPRS_AUTO_ATTACH },
    { "IPF_PERM_GSM_BANDS",                    PMD_ENVIRONMENT_VAR_ID_IPF_PERM_GSM_BANDS },
    { "IPF_PFC",                               PMD_ENVIRONMENT_VAR_ID_IPF_PFC },
    { NULL,                                    725 /* PMD_ENVIRONMENT_VAR_ID_IPF_POC */ },
    { NULL,                                    726 /*PMD_ENVIRONMENT_VAR_ID_IPF_POC_ACTIVE_GROUPS_MAXIMUM*/ },
    { NULL,                                    727 /* PMD_ENVIRONMENT_VAR_ID_IPF_POC_DIAL_OUT */ },
    { NULL,                                    728 /* PMD_ENVIRONMENT_VAR_ID_IPF_POC_LOGIN_STATUS */ },
    { "IPF_PPC_COUNTERS",                      PMD_ENVIRONMENT_VAR_ID_IPF_PPC_COUNTERS },
    { NULL,                                    730 },
    { NULL,                                    731 },
    { NULL,                                    732 },
    { "IPF_PP_CSD_MULTISLOT_CLASS",            PMD_ENVIRONMENT_VAR_ID_IPF_PP_CSD_MULTISLOT_CLASS },
    { NULL,                                    734 },
    { NULL,                                    735 },
    { NULL,                                    736 },
    { NULL,                                    737 },
    { NULL,                                    738 },
    { NULL,                                    739 },
    { NULL,                                    740 },
    { NULL,                                    741 },
    { "IPF_RD_FEATURES",                       PMD_ENVIRONMENT_VAR_ID_IPF_RD_FEATURES },
    { "IPF_RF_POWER_CLASS_REDUCTION",          PMD_ENVIRONMENT_VAR_ID_IPF_RF_POWER_CLASS_REDUCTION },
    { NULL,                                    744 /*PMD_ENVIRONMENT_VAR_ID_IPF_RTCP*/ },
    { NULL,                                    745 /*PMD_ENVIRONMENT_VAR_ID_IPF_RTP*/ },
    { NULL,                                    746 /*PMD_ENVIRONMENT_VAR_ID_IPF_RTSP*/ },
    { NULL,                                    747 /* PMD_ENVIRONMENT_VAR_ID_IPF_SECONDARY_PDP_CONTEXTS */ },
    { NULL,                                    748 },
    { NULL,                                    749 },
    { NULL,                                    750 },
    { NULL,                                    751 },
    { NULL,                                    752 /*PMD_ENVIRONMENT_VAR_ID_IPF_SIP*/ },
    { "IPF_SMS_RESEND",                        PMD_ENVIRONMENT_VAR_ID_IPF_SMS_RESEND },
    { "IPF_SMSCB",                             PMD_ENVIRONMENT_VAR_ID_IPF_SMSCB },
    { "IPF_SMSCB_EXT_CBCH",                    PMD_ENVIRONMENT_VAR_ID_IPF_SMSCB_EXT_CBCH },
    { "IPF_SOCKET",                            PMD_ENVIRONMENT_VAR_ID_IPF_SOCKET },
    { "IPF_SPLIT_PG_CYCLE_CODE",               PMD_ENVIRONMENT_VAR_ID_IPF_SPLIT_PG_CYCLE_CODE },
    { "IPF_SPLIT_PG_CYCLE_ON_CCCH",            PMD_ENVIRONMENT_VAR_ID_IPF_SPLIT_PG_CYCLE_ON_CCCH },
    { NULL,                                    759 /* PMD_ENVIRONMENT_VAR_ID_IPF_SSL */ },
    { "IPF_SSOM_TEST_SUITE",                   PMD_ENVIRONMENT_VAR_ID_IPF_SSOM_TEST_SUITE },
    { NULL,                                    761 /*PMD_ENVIRONMENT_VAR_ID_IPF_STREAMING*/ },
    { NULL,                                    762 },
    { NULL,                                    763 /* PMD_ENVIRONMENT_VAR_ID_IPF_UMTS_CIPHERING_INDICATION */ },
    { NULL,                                    764 },
    { NULL,                                    765 },
    { NULL,                                    766 /* PMD_ENVIRONMENT_VAR_ID_IPF_USER_AGENT_APPENDED_STRING */ },
    { NULL,                                    767 /* PMD_ENVIRONMENT_VAR_ID_IPF_USER_AGENT_MARKUP_VERSION */ },
    { NULL,                                    768 /* PMD_ENVIRONMENT_VAR_ID_IPF_USER_AGENT_PRODUCT_NAME */ },
    { "IPF_UUS",                               PMD_ENVIRONMENT_VAR_ID_IPF_UUS },
    { NULL,                                    770 /*PMD_ENVIRONMENT_VAR_ID_IPF_WAP_1_X*/ },
    { NULL,                                    771 /*PMD_ENVIRONMENT_VAR_ID_IPF_WAP_2_X*/ },
    { "IPF_WCDMA_CSD",                         PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_CSD },
    { "IPF_WCDMA_PS",                          PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_PS },
    { "IPF_WCDMA_RAT",                         PMD_ENVIRONMENT_VAR_ID_IPF_WCDMA_RAT },
    { NULL,                                    775 /*PMD_ENVIRONMENT_VAR_ID_IPF_WDP*/ },
    { NULL,                                    776 /*PMD_ENVIRONMENT_VAR_ID_IPF_WSP*/ },
    { "IPF_IMS",                               PMD_ENVIRONMENT_VAR_ID_IPF_IMS },
    { "IPF_CSD_AT_COMMAND_INTERPRETER",        PMD_ENVIRONMENT_VAR_ID_IPF_CSD_AT_COMMAND_INTERPRETER },
    { "IPF_UMA",                               PMD_ENVIRONMENT_VAR_ID_IPF_UMA },
    { NULL,                                    780 /* PMD_ENVIRONMENT_VAR_ID_IPF_WLAN_RAT */ },
    { NULL,                                    781 /*PMD_ENVIRONMENT_VAR_ID_IPF_POC_REPLAY*/ },
    { NULL,                                    782 /*PMD_ENVIRONMENT_VAR_ID_IPF_POC_REPLAY_BUFFER_MAX*/ },
    { "IPF_GERAN_FEATURE_PACKAGE_1",           PMD_ENVIRONMENT_VAR_ID_IPF_GERAN_FEATURE_PACKAGE_1 },
    { NULL,                                    784 /*PMD_ENVIRONMENT_VAR_ID_IPF_MES*/ },
    { NULL,                                    785 /*PMD_ENVIRONMENT_VAR_ID_IPF_PP_AUTO_TX_PWR_REDUCTION*/ },
    { NULL,                                    786 /* PMD_ENVIRONMENT_VAR_ID_IPF_CDMA_MDI_REVISION */ },
    { NULL,                                    787 },
    { NULL,                                    788 },
    { NULL,                                    789 /*PMD_ENVIRONMENT_VAR_ID_IPF_NEWS_DELIVERY*/ },
    { "IPF_PERM_WCDMA_BANDS",                  PMD_ENVIRONMENT_VAR_ID_IPF_PERM_WCDMA_BANDS },
    { NULL,                                    791 /* PMD_ENVIRONMENT_VAR_ID_IPF_CDMA_SUPPORT_RUIM */ },
    { NULL,                                    792 /* PMD_ENVIRONMENT_VAR_ID_IPF_SS_CALL_ALLOWED_FEATURE */ },
    { NULL,                                    793 /* PMD_ENVIRONMENT_VAR_ID_IPF_IKE */ },
    { NULL,                                    794 /*PMD_ENVIRONMENT_VAR_ID_IPF_NO_PMM_CLASS */ },
    { NULL,                                    795 /*PMD_ENVIRONMENT_VAR_ID_IPF_SIP_V2*/ },
    { NULL,                                    796 /* PMD_ENVIRONMENT_VAR_ID_IPF_IMS_ISA_SERVER */ },
    { "IPF_OMA_POC",                           PMD_ENVIRONMENT_VAR_ID_IPF_OMA_POC },
    { NULL,                                    798 /*PMD_ENVIRONMENT_VAR_ID_IPF_POC_3G_DND*/ },
    { "IPF_PREPAID_SUPPORT",                   PMD_ENVIRONMENT_VAR_ID_IPF_PREPAID_SUPPORT },
    { NULL,                                    800 /* PMD_ENVIRONMENT_VAR_ID_IPF_SHORT_DATA_BURST */ },
    { NULL,                                    801 /* PMD_ENVIRONMENT_VAR_ID_IPF_307_2_KBPS_SUPPORT */ },
    { NULL,                                    802 },
    { "IPF_H3G_ALWAYS_ON_PDP_CONTEXT",         PMD_ENVIRONMENT_VAR_ID_IPF_H3G_ALWAYS_ON_PDP_CONTEXT },
    { "IPF_CALL_SERVER_FCS_CLIENT",            PMD_ENVIRONMENT_VAR_ID_IPF_CALL_SERVER_FCS_CLIENT },
    { NULL,                                    805 /* PMD_ENVIRONMENT_VAR_ID_IPF_AM_SERV */ },
    { "INFO_PP_SECONDARY_PDP_CONTEXTS",        PMD_ENVIRONMENT_VAR_ID_INFO_PP_SECONDARY_PDP_CONTEXTS },
    { "INFO_PP_LCS",                           PMD_ENVIRONMENT_VAR_ID_INFO_PP_LCS },
    { "INFO_PP_LCS_AGPS",                      PMD_ENVIRONMENT_VAR_ID_INFO_PP_LCS_AGPS },

    { "MON_TRACE_ENABLE",                      PMD_ENVIRONMENT_VAR_ID_MON_TRACE_ENABLE },
    { "MON_TRACE_STORED_ACT_USE_ONCE",         PMD_ENVIRONMENT_VAR_ID_MON_TRACE_STORED_ACT_USE_ONCE },
    { "MON_FW_TRACE_ENABLE",                   PMD_ENVIRONMENT_VAR_ID_MON_FW_TRACE_ENABLE },
    { "MON_EPOC_TRACE_ENABLE",                 PMD_ENVIRONMENT_VAR_ID_MON_EPOC_TRACE_ENABLE },
    { "MON_BT_TRACE_ENABLE",                   PMD_ENVIRONMENT_VAR_ID_MON_BT_TRACE_ENABLE },
    { "MON_PPC_ENABLE",                        PMD_ENVIRONMENT_VAR_ID_MON_PPC_ENABLE },
    { "MON_RESET_NON_RD_DISABLE",              PMD_ENVIRONMENT_VAR_ID_MON_RESET_NON_RD_DISABLE },
    { "MON_RBUG_ENABLE",                       PMD_ENVIRONMENT_VAR_ID_MON_RBUG_ENABLE },
    { "MON_STACK_INFO_ENABLE",                 PMD_ENVIRONMENT_VAR_ID_MON_STACK_INFO_ENABLE },
    { "MON_TRACE_INFO_SUPPORT",                PMD_ENVIRONMENT_VAR_ID_MON_TRACE_INFO_SUPPORT },
    { "MON_STI_TRACE_TIMESTAMP_SB_ENABLE",     PMD_ENVIRONMENT_VAR_ID_MON_STI_TRACE_TIMESTAMP_SB_ENABLE },
    { "MON_TRACE_ANY_GROUP_ENABLED_CHECK",     PMD_ENVIRONMENT_VAR_ID_MON_TRACE_ANY_GROUP_ENABLED_CHECK },
    { "MON_STI_TRACE_BUF_AMOUNT",              PMD_ENVIRONMENT_VAR_ID_MON_STI_TRACE_BUF_AMOUNT },
    { "SOS_MON_OBJ_ID",                        PMD_ENVIRONMENT_VAR_ID_SOS_MON_OBJ_ID }
};

pmd_constant pmd_constant_file_type[PMD_FILE_TYPE_MAX] =
{
    { "UNKNOWN",                PMD_FILE_TYPE_UNKNOWN },
    { "PRODUCT",                PMD_FILE_TYPE_PRODUCT },
    { "CDSP",                   PMD_FILE_TYPE_CDSP },
    { "ADSP",                   PMD_FILE_TYPE_ADSP },
    { "DSP5",                   PMD_FILE_TYPE_DSP5 },
    { "HANDMADE",               PMD_FILE_TYPE_HANDMADE },
    { "DSP5_CDSP",              PMD_FILE_TYPE_DSP5_CDSP },
    { "DSP5_ADSP",              PMD_FILE_TYPE_DSP5_ADSP },
    { "CDMA_DSP",               PMD_FILE_TYPE_CDMA_DSP },
    { "RESOURCES",              PMD_FILE_TYPE_RESOURCES },
    { "REDUCED",                PMD_FILE_TYPE_REDUCED },
    { "SYMBIAN",                PMD_FILE_TYPE_SYMBIAN },
    { "OPTRA",                  PMD_FILE_TYPE_OPTRA },
    { "DEVICE",                 PMD_FILE_TYPE_DEVICE }
};

pmd_constant pmd_constant_file_restriction[PMD_FILE_RESTRICTION_MAX] =
{
    { "RD",                     PMD_FILE_RESTRICTION_RD },
    { "RESTRICTED",             PMD_FILE_RESTRICTION_RESTRICTED },
    { "PUBLIC",                 PMD_FILE_RESTRICTION_PUBLIC }
};

pmd_constant pmd_constant_info_type[PMD_INFO_TYPE_MAX] =
{
    { "NONE",                           0 },
    { "MCU_OS_TASKS",                   1 },
    { "MCU_OS_TIMERS",                  2 },
    { "MCU_OS_RESOURCES",               3 },
    { "MCU_OS_BLOCK_SETS",              4 },
    { "ADSP_TASKS",                     5 },
    { "CDSP_TASKS",                     6 },
    { "OS_TRACE_GROUPS",                7 },
    { "PN_OBJECTS_HOST",                8 },
    { "PN_RESOURCES",                   9 },
    { "PN_MEDIAS",                      10 },
    { "PN_DEVICES",                     11 },
    { "HW_RESET_REASONS",               PMD_INFO_TYPE_HW_RESET_REASONS },
    { "MCU_OS_ERROR_CODES",             PMD_INFO_TYPE_OS_ERROR_CODES_MCU },
    { "MCU_OS_TASK_STATES",             PMD_INFO_TYPE_OS_TASK_STATES_MCU },
    { "",                               15 },
    { "",                               16 },
    { "",                               17 },
    { "MCU_DEBUG_DLL_FILENAMES",        PMD_INFO_TYPE_MCU_DEBUG_DLL_FILENAMES },
    { "",                               PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS_SHARED },
    { "",                               PMD_INFO_TYPE_MCU_DEBUG_FILENAMES_SHARED },
    { "",                               PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS_SHARED },
    { "OST_PRINTF",                     PMD_INFO_TYPE_OST_PRINTF },
    { "MCU_DEBUG_VARIABLES",            PMD_INFO_TYPE_MCU_DEBUG_VARIABLES },
    { "MCU_DEBUG_VARIABLES_SHARED",     PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED },
    /* gap... */
    { "PN_OBJECTS_TRACEBOX",            PMD_INFO_TYPE_PN_OBJECTS_TRACEBOX },
    { "OS_HOOKS_MCU",                   PMD_INFO_TYPE_OS_HOOKS_MCU },
    { "CDSP_SIGNALS",                   PMD_INFO_TYPE_CDSP_SIGNALS },
    { "ADSP_SIGNALS",                   PMD_INFO_TYPE_ADSP_SIGNALS },
    { "PRIVATE_IDS",                    PMD_INFO_TYPE_PRIVATE_IDS },
    { "INVARIANT_TRACE_ENTITY_IDS",     PMD_INFO_TYPE_INVARIANT_TRACE_ENTITY_IDS },
    { "PN_DEVICES_6",                   PMD_INFO_TYPE_PN_DEVICES_6 },
    { "RESOURCE_IDS",                   PMD_INFO_TYPE_RESOURCE_IDS },
    { "XTI_MASTER_IDS",                 PMD_INFO_TYPE_XTI_MASTER_IDS },
    { "CDSP_INTERRUPTS",                PMD_INFO_TYPE_CDSP_INTERRUPTS },
    { "CDSP_ERRORS",                    PMD_INFO_TYPE_CDSP_ERRORS },
    { "CDSP_ERROR_DESCRIPTIONS",        PMD_INFO_TYPE_CDSP_ERROR_DESCRIPTIONS },
    { "CDSP_ERROR_EXTRA_PARAMETERS",    PMD_INFO_TYPE_CDSP_ERROR_EXTRA_PARAMETERS },
    { "SYMBIAN_COMPONENT_IDS",          PMD_INFO_TYPE_SYMBIAN_COMPONENT_IDS },
    { "PN_OBJECTS",                     PMD_INFO_TYPE_PN_OBJECTS },
    { "CDSP_TRACE_ENTITY_IDS",          PMD_INFO_TYPE_CDSP_TRACE_ENTITY_IDS },
    { "ADSP_TRACE_ENTITY_IDS",          PMD_INFO_TYPE_ADSP_TRACE_ENTITY_IDS },
    { "VENDOR_COMPONENT_TRACE_ENTITY_IDS", PMD_INFO_TYPE_VENDOR_COMPONENT_TRACE_ENTITY_IDS },
    { "OST_PROTOCOL_IDS",               PMD_INFO_TYPE_OST_PROTOCOL_IDS },
    { "VENDOR_TRACE_VERSION_MASK",      PMD_INFO_TYPE_VENDOR_TRACE_VERSION_MASK },
    { "VENDOR_CRASH_DUMP",              PMD_INFO_TYPE_VENDOR_CRASH_DUMP },
    { "VENDOR_CRASH_DUMP_FUNCTIONNAME", PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME }
};

pmd_info_attr pmd_constant_info_attributes[PMD_INFO_ATTR_COUNT] =
{
	{ PMD_INFO_TYPE_OS_TASK_MCU,			       PMD_INFO_ATTR_OS_TASK_MCU_PRIORITY,							"PRIORITY" },
	{ PMD_INFO_TYPE_OS_TASK_MCU,			       PMD_INFO_ATTR_OS_TASK_MCU_STACK_SIZE,						"STACK_SIZE" },
	{ PMD_INFO_TYPE_OS_TASK_MCU,			       PMD_INFO_ATTR_OS_TASK_MCU_STACK_ADDRESS,					    "STACK_ADDRESS" },
	{ PMD_INFO_TYPE_OS_TASK_MCU,		 	       PMD_INFO_ATTR_OS_TASK_MCU_MAIL_BOX_LENGTH,					"MAIL_BOX_LENGTH" },
	{ PMD_INFO_TYPE_OS_TASK_MCU,			       PMD_INFO_ATTR_OS_TASK_MCU_FAST_MESSAGE_MAIL_BOX_LENGTH,		"FAST_MESSAGE_MAIL_BOX_LENGTH" },

	{ PMD_INFO_TYPE_OS_TIMER_MCU,			       PMD_INFO_ATTR_OS_TIMER_MCU_TYPE,							    "TYPE" },
	{ PMD_INFO_TYPE_OS_TIMER_MCU,			       PMD_INFO_ATTR_OS_TIMER_MCU_TASK,							    "TASK" },
	{ PMD_INFO_TYPE_OS_TIMER_MCU,			       PMD_INFO_ATTR_OS_TIMER_MCU_MESSAGE,							"MESSAGE" },

	{ PMD_INFO_TYPE_OS_BLOCK_SET_MCU,		       PMD_INFO_ATTR_OS_BLOCK_SET_AMOUNT,							"AMOUNT" },
	{ PMD_INFO_TYPE_OS_BLOCK_SET_MCU,	  	       PMD_INFO_ATTR_OS_BLOCK_SET_SIZE,							    "SIZE" },

	{ PMD_INFO_TYPE_CDSP_TASKS,	                   PMD_INFO_ATTR_CDSP_TASKS_TYPE,				                "TYPE" },
	{ PMD_INFO_TYPE_CDSP_TASKS,	                   PMD_INFO_ATTR_CDSP_TASKS_PRIORITY,							"PRIORITY" },

	{ PMD_INFO_TYPE_CDSP_ERRORS,	               PMD_INFO_ATTR_CDSP_ERRORS_DESCRIPTION_ID,					"ERROR_DESCRIPTION_ID" },
	{ PMD_INFO_TYPE_CDSP_ERRORS,	               PMD_INFO_ATTR_CDSP_ERRORS_EXTRA_PARAMETER_ID,				"EXTRA_PARAMETER_ID" },

	{ PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS,	       PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_LAST_ADDRESS,				"LAST_ADDRESS" },
	{ PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS,	       PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_FILENAME,					"FILENAME" },

	{ PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS,	       PMD_INFO_ATTR_MCU_DEBUG_LINENUMBER,							"LINENUMBER" },

    { PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS_SHARED,	   PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_LAST_ADDRESS_SHARED,		"LAST_ADDRESS" },
	{ PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS_SHARED,	   PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_FILENAME_SHARED,			"FILENAME" },
    { PMD_INFO_TYPE_MCU_DEBUG_FUNCTIONS_SHARED,    PMD_INFO_ATTR_MCU_DEBUG_FUNCTION_DLL_SHARED,				    "DLL" },

	{ PMD_INFO_TYPE_MCU_DEBUG_FILENAMES_SHARED,	   PMD_INFO_ATTR_MCU_DEBUG_FILENAMES_DLL_SHARED,				"DLL" },

	{ PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS_SHARED,  PMD_INFO_ATTR_MCU_DEBUG_LINENUMBER_SHARED,					"LINENUMBER" },
	{ PMD_INFO_TYPE_MCU_DEBUG_LINENUMBERS_SHARED,  PMD_INFO_ATTR_MCU_DEBUG_LINENUMBER_DLL_SHARED,				"DLL" },

	{ PMD_INFO_TYPE_OST_PRINTF,                    PMD_INFO_ATTR_OST_PRINTF_COMPONENTID,                        "COMPONENT_ID" },
	{ PMD_INFO_TYPE_OST_PRINTF,                    PMD_INFO_ATTR_OST_PRINTF_GROUPID,                            "GROUP_ID" },
	{ PMD_INFO_TYPE_OST_PRINTF,                    PMD_INFO_ATTR_OST_PRINTF_TRACEID,                            "TRACE_ID" },

	{ PMD_INFO_TYPE_MCU_DEBUG_VARIABLES,           PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_LAST_ADDRESS,              "LAST_ADDRESS" },
	{ PMD_INFO_TYPE_MCU_DEBUG_VARIABLES,           PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_FILENAME,                  "FILENAME" },

	{ PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED,    PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_LAST_ADDRESS_SHARED,       "LAST_ADDRESS" },
	{ PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED,    PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_FILENAME_SHARED,           "FILENAME" },
	{ PMD_INFO_TYPE_MCU_DEBUG_VARIABLES_SHARED,    PMD_INFO_ATTR_MCU_DEBUG_VARIABLES_DLL_SHARED,                "DLL" },

    { PMD_INFO_TYPE_VENDOR_TRACE_VERSION_MASK,      PMD_INFO_ATTR_VENDOR_TRACE_MASK_SUPPLIERID,                 "SUPPLIER_ID" },
    { PMD_INFO_TYPE_VENDOR_TRACE_VERSION_MASK,      PMD_INFO_ATTR_VENDOR_TRACE_MASK_LENGTH,                     "LENGTH" },
    { PMD_INFO_TYPE_VENDOR_TRACE_VERSION_MASK,      PMD_INFO_ATTR_VENDOR_TRACE_MASK_DATA1,                      "DATA1" },
    { PMD_INFO_TYPE_VENDOR_TRACE_VERSION_MASK,      PMD_INFO_ATTR_VENDOR_TRACE_MASK_DATA2,                      "DATA2" },

    { PMD_INFO_TYPE_VENDOR_CRASH_DUMP,              PMD_INFO_TYPE_VENDOR_CRASH_DUMP_SUPPLIERID,                 "SUPPLIER_ID" },
    { PMD_INFO_TYPE_VENDOR_CRASH_DUMP,              PMD_INFO_TYPE_VENDOR_CRASH_DUMP_SUBINDENT,                  "SUBINDENT" },
    { PMD_INFO_TYPE_VENDOR_CRASH_DUMP,              PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FN_INDEX,                   "FUNCTIONNAME_INDEX" },

    { PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME, PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME_SUPPLIERID,    "SUPPLIER_ID" },
    { PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME, PMD_INFO_TYPE_VENDOR_CRASH_DUMP_FUNCTIONNAME_FN_INDEX,      "FUNCTIONNAME_INDEX" }
};

pmd_constant pmd_constant_length_algorithm[PMD_LENGTH_ALGORITHM_MAX] =
{
    { "Not specified",       0 },
    { "N + Const",           1 },
    { "Const - N",           2 },
    { "Const",               3 },
    { "Const*N",             4 },
    { "Const*N + 1",         5 },
    { "Const*N - 1",         6 },
    { "As many as possible", 7 },
    { "N/Const",             8 },
    { "(Nn/Const) round up", 9 },
    { "Optional",            10 },
    { "Unknown",             PMD_LENGTH_ALGORITHM_UNKNOWN }
};

pmd_constant pmd_constant_function[PMD_FUNCTION_MAX] =
{
    { "Unknown",        PMD_FUNCTION_UNKNOWN },
    { "Request",        PMD_FUNCTION_REQUEST },
    { "Indication",     PMD_FUNCTION_INDICATION },
    { "Response",       PMD_FUNCTION_RESPONSE },
    { "Notification",   PMD_FUNCTION_NOTIFICATION }
};

pmd_message_type_group_conf pmd_constant_message_type_group[PMD_MESSAGE_TYPE_GROUP_MAX] =
{
    { "None",               NULL,               NULL,   0,                              PMD_MESSAGE_TYPE_GROUP_NONE /* 0 */,        PN_DEV_HOST,     0,                                 PMD_INFO_TYPE_NONE,                       PMD_MESSAGE_TYPE_UNDEFINED,              PMD_MESSAGE_TYPE_UNDEFINED },
    { "DSP5 CDSP trace",    "Cdsp5Trace",       "cdsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE, PMD_MESSAGE_TYPE_GROUP_DSP5_CDSP /* 1 */,   PN_DEV_DSP_MAIN, PMD_MESSAGE_TYPE_CDSP5_TRACE,      PMD_INFO_TYPE_NONE,                       PMD_MESSAGE_TYPE_DSP5_CDSP_FIRST,        PMD_MESSAGE_TYPE_DSP5_CDSP_LAST },
    { "DSP5 ADSP trace",    "Adsp5Trace",       "adsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE, PMD_MESSAGE_TYPE_GROUP_DSP5_ADSP /* 2 */,   PN_DEV_DSP_AUX,  PMD_MESSAGE_TYPE_ADSP5_TRACE,      PMD_INFO_TYPE_NONE,                       PMD_MESSAGE_TYPE_DSP5_ADSP_FIRST,        PMD_MESSAGE_TYPE_DSP5_ADSP_LAST },
    { "Invariant trace",    "InvariantTrace",   "inv",  PMD_MESSAGE_TYPE_FLAG_IS_TRACE, PMD_MESSAGE_TYPE_GROUP_INVARIANT /* 3 */,   PN_DEV_HOST,     PMD_MESSAGE_TYPE_INVARIANT_TRACE,  PMD_INFO_TYPE_INVARIANT_TRACE_ENTITY_IDS, PMD_MESSAGE_TYPE_INVARIANT_TRACE_FIRST,  PMD_MESSAGE_TYPE_INVARIANT_TRACE_LAST }
};

#ifndef AUTOGEN_VENDOR_IDENTIFIER
 #define AUTOGEN_VENDOR_IDENTIFIER "vend"
#endif

pmd_message_type_conf pmd_constant_message_type[PMD_MESSAGE_TYPE_MAX] =
{
    { "Undefined",                      NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_UNDEFINED,                     PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "PhoNet header",                  NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_PHONET_HEADER,                 PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "ISI message",                    "IsiMessage",                   "isi",  PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE,   PMD_MESSAGE_TYPE_ISI,                           PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "ISI private message",            "PrivateIsiMessage",            "isi",  PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE,   PMD_MESSAGE_TYPE_ISI_PRIVATE,                   PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  4,                                              PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  5,                                              PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  6,                                              PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "GSM DSP trace",                  "GsmDspTrace",                  "gdsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_GSM_DSP_TRACE,                 PMD_TRACE_ACTIVATION_TYPE_ON_OFF },
    { "MCU trace",                      "McuTrace",                     "mcu",  PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_MCU_TRACE,                     PMD_TRACE_ACTIVATION_TYPE_SHORT_EXTENDED },
    { NULL,                             NULL,                           NULL,   0,                                  9,                                              PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  10,                                             PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  11,                                             PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "Media module",                   "MediaModuleMessage",           "mm",   PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE,   PMD_MESSAGE_TYPE_MEDIA_MODULE,                  PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "OS trace",                       "OsTrace",                      "os",   PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_OS_TRACE,                      PMD_TRACE_ACTIVATION_TYPE_ON_OFF },
    { "STI trace",                      "StiTrace",                     "sti",  PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_STI_TRACE,                     PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  15,                                             PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "WCDMA CDSP trace",               "WcdmaCdspTrace",               "wdsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_WCDMA_CDSP_TRACE,              PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  17,                                             PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "WCDMA CDSP Algorithm trace",     "WcdmaCdspAlgorithmTrace",      "walg", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_WCDMA_CDSP_ALGORITHM_TRACE,    PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "ADSP trace",                     "AdspTrace",                    "adsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_ADSP_TRACE,                    PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "EXTERNAL",                       NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_EXTERNAL,                      PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_DSP5_CORE,                     PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_DSP5_SIGNALS,                  PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_DSP5_TASKS,                    PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_DSP5_WCDMA,                    PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_DSP5_GSM,                      PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { NULL,                             NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_DSP5_APPLICATION,              PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "PhoNet message",                 "PhoNetMessage",                "pn",   PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE,   PMD_MESSAGE_TYPE_PHONET_,                       PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "PhoNet extended message",        "ExtendedPhoNetMessage",        "pn",   PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE,   PMD_MESSAGE_TYPE_PHONET_EXT,                    PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "CDSP OSE trace",                 "CdspOseTrace",                 "cdsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_CDSP_OSE_TRACE,                PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "ADSP OSE trace",                 "AdspOseTrace",                 "adsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_ADSP_OSE_TRACE,                PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "Protocol message",               "ProtocolMessage",              "prot", PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE,   PMD_MESSAGE_TYPE_PROTOCOL,                      PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "HAL trace",                      "HalTrace",                     "hal",  PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_HAL_TRACE,                     PMD_TRACE_ACTIVATION_TYPE_ON_OFF },
    { NULL,                             NULL,                           NULL,   0,                                  33,                                             PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "Invariant trace",                "InvariantTrace",               "inv",  PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_INVARIANT_TRACE,               PMD_TRACE_ACTIVATION_TYPE_ON_OFF },
    { "DSP5 CDSP trace",                "Cdsp5Trace",                   "cdsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_CDSP5_TRACE,                   PMD_TRACE_ACTIVATION_TYPE_ON_OFF_HOOKS },
    { "DSP5 ADSP trace",                "Adsp5Trace",                   "adsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_ADSP5_TRACE,                   PMD_TRACE_ACTIVATION_TYPE_ON_OFF_HOOKS },
    { "Master trace",                   "MasterTrace",                  "xti",  PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_MASTER_TRACE,                  PMD_TRACE_ACTIVATION_TYPE_ON_OFF },
    { "Vendor component trace",         "VendorComponentTrace",         AUTOGEN_VENDOR_IDENTIFIER,
                                                                                PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_VENDOR_COMPONENT_TRACE,        PMD_TRACE_ACTIVATION_TYPE_ON_OFF },
    { "Vendor DLL trace",               "VendorDllTrace",               AUTOGEN_VENDOR_IDENTIFIER,
                                                                                PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_VENDOR_DLL_TRACE,              PMD_TRACE_ACTIVATION_TYPE_ON_OFF },
    { "OST message",                    "OstMessage",                   "ost",  PMD_MESSAGE_TYPE_FLAG_IS_MESSAGE,   PMD_MESSAGE_TYPE_OST,                           PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "HSP XTI trace",                  "HspXtiTrace",                  "hsp",  PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_HSP_TRACE,                     PMD_TRACE_ACTIVATION_TYPE_ON_OFF },
    { "OST header",                     NULL,                           NULL,   0,                                  PMD_MESSAGE_TYPE_OST_HEADER,                    PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "CDMA DSP trace",                 "CdmaDspTrace",                 "cdsp", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_CDMA_DSP_TRACE,                PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED },
    { "Symbian trace",                  "SymbianTrace",                 "symb", PMD_MESSAGE_TYPE_FLAG_IS_TRACE,     PMD_MESSAGE_TYPE_SYMBIAN_TRACE,                 PMD_TRACE_ACTIVATION_TYPE_ON_OFF }

    /* Invariant traces are defined through groups */
    /* CDSP5 traces are defined through groups */
    /* ADSP5 traces are defined through groups */
};

#ifndef AUTOGEN_VENDOR_DLL_TRACE_TYPE_NAME
 #define AUTOGEN_VENDOR_DLL_TRACE_TYPE_NAME "Vendor DLL traces"
#endif

pmd_message_info_tree_conf pmd_constant_message_info_tree[PMD_MESSAGE_INFO_TREE_ELEMENTS_MAX] =
{
    { "Master traces",              PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_MASTER_TRACE },
    { "OS traces",                  PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_OS_TRACE },
    { "HAL traces",                 PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_HAL_TRACE },
    { "STI/XTI traces",             PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_STI_TRACE },
    { "MCU traces",                 PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_MCU_TRACE },
    /* DSP5 ADSP traces for PMD file format <= 4.00 */
    { "DSP5 ADSP traces",           PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_GROUP,  PMD_MESSAGE_TYPE_GROUP_DSP5_ADSP },
    /* DSP5 ADSP traces for PMD file format >= 5.00 */
    { "DSP5 ADSP traces",           PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_ADSP5_TRACE },
    /* DSP5 CDSP traces for PMD file format <= 4.00 */
    { "DSP5 CDSP traces",           PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_GROUP,  PMD_MESSAGE_TYPE_GROUP_DSP5_CDSP },
    /* DSP5 CDSP traces for PMD file format >= 5.00 */
    { "DSP5 CDSP traces",           PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_CDSP5_TRACE },
    { "GSM CDSP traces",            PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_GSM_DSP_TRACE },
    { "CDMA CDSP traces",           PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_CDMA_DSP_TRACE },
    { "ADSP OSE traces",            PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_ADSP_TRANSPORT },
    { "CDSP OSE traces",            PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_CDSP_TRANSPORT },
    { "CDSP traces",                PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_WCDMA_CDSP_TRACE},
    { "ADSP traces",                PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_ADSP_TRACE},
    { "Vendor traces",              PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_VENDOR_COMPONENT_TRACE},
    { AUTOGEN_VENDOR_DLL_TRACE_TYPE_NAME,
                                    PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_VENDOR_DLL_TRACE},
    /* Invariant traces for PMD file format <= 4.00 */
    { "Invariant traces",           PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_GROUP,  PMD_MESSAGE_TYPE_GROUP_INVARIANT },
    /* Invariant traces for PMD file format >= 5.00 */
    { "Invariant traces",           PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_INVARIANT_TRACE },
    { "Symbian traces",             PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_SYMBIAN_TRACE },
    { "ISI resources",              PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_ISI },
    { "ISI resources (private)",    PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_ISI_PRIVATE },
    { "PhoNet resources",           PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_PHONET_ },
    { "PhoNet Extended resources",  PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_PHONET_EXT },
    { "Media Modules",              PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_MEDIA_MODULE },
    { "Generic protocols",          PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_PROTOCOL },
    { "HSP XTI traces",             PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE,        PMD_MESSAGE_TYPE_HSP_TRACE }
};

pmd_number_special_type_conf pmd_constant_number_special_type[PMD_NUMBER_SPECIAL_TYPE_MAX] =
{
    { "NONE",                           NULL,                           PMD_NUMBER_SPECIAL_TYPE_NONE },
    { "PHONET_MEDIA",                   "Media",                        PMD_NUMBER_SPECIAL_TYPE_PHONET_MEDIA },
    { "PHONET_RECEIVER_DEVICE",         "ReceiverDevice",               PMD_NUMBER_SPECIAL_TYPE_PHONET_RECEIVER_DEVICE },
    { "PHONET_SENDER_DEVICE",           "SenderDevice",                 PMD_NUMBER_SPECIAL_TYPE_PHONET_SENDER_DEVICE },
    { "PHONET_RESOURCE",                "Resource",                     PMD_NUMBER_SPECIAL_TYPE_PHONET_RESOURCE },
    { "PHONET_LENGTH",                  "Length",                       PMD_NUMBER_SPECIAL_TYPE_PHONET_LENGTH },
    { "PHONET_RECEIVER_OBJECT",         "ReceiverObject",               PMD_NUMBER_SPECIAL_TYPE_PHONET_RECEIVER_OBJECT },
    { "PHONET_SENDER_OBJECT",           "SenderObject",                 PMD_NUMBER_SPECIAL_TYPE_PHONET_SENDER_OBJECT },
    { "TRANSACTION_ID",                 "TransactionId",                PMD_NUMBER_SPECIAL_TYPE_TRANSACTION_ID },
    { "RAW_DATA",                       NULL,                           PMD_NUMBER_SPECIAL_TYPE_RAW_DATA },
    { "PHONET_ADDRESS_DEVICE",          NULL,                           PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_DEVICE },
    { "PHONET_ADDRESS_OBJECT",          NULL,                           PMD_NUMBER_SPECIAL_TYPE_PHONET_ADDRESS_OBJECT },
    { "MESSAGE_ID",                     "MessageId",                    PMD_NUMBER_SPECIAL_TYPE_MESSAGE_ID },
    { "SUB_MESSAGE_ID",                 "SubmessageId",                 PMD_NUMBER_SPECIAL_TYPE_SUB_MESSAGE_ID },
    { "SUB_BLOCK_ID",                   "SubblockId",                   PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_ID },
    { "SUB_BLOCK_LENGTH",               "SubblockLength",               PMD_NUMBER_SPECIAL_TYPE_SUB_BLOCK_LENGTH },
    { "TRACE_GROUP_ID",                 "TraceGroupId",                 PMD_NUMBER_SPECIAL_TYPE_TRACE_GROUP_ID },
    { "TRACE_ID",                       "TraceId",                      PMD_NUMBER_SPECIAL_TYPE_TRACE_ID },
    { "TRACE_DATA_LENGTH",              "TraceDataLength",              PMD_NUMBER_SPECIAL_TYPE_TRACE_DATA_LENGTH },
    { "PRIVATE_ID",                     "PrivateId",                    PMD_NUMBER_SPECIAL_TYPE_PRIVATE_ID },
    { "FTD_VALUE",                      "FtdValue",                     PMD_NUMBER_SPECIAL_TYPE_FTD_VALUE },
    { "PPC_VALUE",                      "PpcValue",                     PMD_NUMBER_SPECIAL_TYPE_PPC_VALUE },
    { "VALUE_REFERENCE",                NULL,                           PMD_NUMBER_SPECIAL_TYPE_VALUE_REFERENCE },
    { "MESSAGE_LENGTH",                 "MessageLength",                PMD_NUMBER_SPECIAL_TYPE_MESSAGE_LENGTH },
    { "MCU_FUNCTION_ADDR",              "McuFunctionAddress",           PMD_NUMBER_SPECIAL_TYPE_MCU_FUNCTION_ADDR },
    { NULL,                             NULL,                           25 },
    { NULL,                             NULL,                           26 },
    { NULL,                             NULL,                           27 },
    { NULL,                             NULL,                           28 },
    { "DSP_SIGNAL_ID",                  NULL,                           PMD_NUMBER_SPECIAL_TYPE_DSP_SIGNAL_ID },
    { NULL,                             NULL,                           30 },
    { NULL,                             NULL,                           31 },
    { "ACTUAL_MEDIA",                   "MediaId",                      PMD_NUMBER_SPECIAL_TYPE_ACTUAL_MEDIA },
    { "TIMESTAMP",                      NULL,                           PMD_NUMBER_SPECIAL_TYPE_TIMESTAMP },
    { "TRACE_ENTITY_ID",                "TraceEntityId",                PMD_NUMBER_SPECIAL_TYPE_TRACE_ENTITY_ID },
    { "RESOURCE_ID",                    "ResourceId",                   PMD_NUMBER_SPECIAL_TYPE_RESOURCE_ID },
    { "STI_TRACE_ID",                   "StiTraceId",                   PMD_NUMBER_SPECIAL_TYPE_STI_TRACE_ID },
    { "XTI_MASTER_ID",                  "XtiMasterId",                  PMD_NUMBER_SPECIAL_TYPE_XTI_MASTER_ID },
    { "TRACE_MASTER_ID",                "TraceMasterId",                PMD_NUMBER_SPECIAL_TYPE_TRACE_MASTER_ID },
    { "PRINTF_ID",                      "PrintfId",                     PMD_NUMBER_SPECIAL_TYPE_PRINTF_ID },
    { "OST_LENGTH_SHORT",               "OstLengthShort",               PMD_NUMBER_SPECIAL_TYPE_OST_LENGTH_SHORT },
    { "OST_LENGTH_EXTENDED",            "OstLengthExtended",            PMD_NUMBER_SPECIAL_TYPE_OST_LENGTH_EXTENDED },
    { "OST_VERSION",                    "Version",                      PMD_NUMBER_SPECIAL_TYPE_OST_VERSION },
    { "OST_ENTITY_ID",                  "EntityId",                     PMD_NUMBER_SPECIAL_TYPE_OST_ENTITY_ID },
    { "OST_PROTOCOL_ID",                "ProtocolId",                   PMD_NUMBER_SPECIAL_TYPE_OST_PROTOCOL_ID }
};

pmd_timestamp_type_conf pmd_constant_timestamp_type[PMD_TIMESTAMP_TYPE_MAX] =
{
    { "UNKNOWN",     NULL,                           PMD_TIMESTAMP_TYPE_UNKNOWN },
    { "DSP5",        NULL,                           PMD_TIMESTAMP_TYPE_DSP5 },
    { "GSM_FRAMES",  "GsmFrames",                    PMD_TIMESTAMP_TYPE_GSM_FRAMES },
    { "MCU",         "McuTimestamp",                 PMD_TIMESTAMP_TYPE_MCU },
    { "STI_XTI",     "TraceboxTimestamp",            PMD_TIMESTAMP_TYPE_STI_XTI },
    { "CDSP",        "WcdmaCdspTimestamp",           PMD_TIMESTAMP_TYPE_CDSP },
    { "ADSP",        "WcdmaAdspTimestamp",           PMD_TIMESTAMP_TYPE_ADSP },
    { "SOURCE",      NULL,                           PMD_TIMESTAMP_TYPE_SOURCE },
    { "CDMA_SYSTEM", "CdmaTimestamp",                PMD_TIMESTAMP_TYPE_CDMA_SYSTEM }
};

pmd_device_type_conf pmd_constant_device_type[PMD_DEVICE_TYPE_MAX] =
{
#ifdef PN_DEV_HOST
    { "PN_DEV_HOST",      "MCU",        PN_DEV_HOST,        0 },
#else
    { "PN_DEV_HOST",      "MCU",        0x00,               0 },
#endif
#ifdef PN_DEV_PC
    { "PN_DEV_PC",        "PC",         PN_DEV_PC,          PMD_DEVICE_IS_NOT_PHONE_DEVICE },
#else
    { "PN_DEV_PC",        "PC",         0x10,               PMD_DEVICE_IS_NOT_PHONE_DEVICE },
#endif
#ifdef PN_DEV_COMBOX
    { "PN_DEV_COMBOX",    "COMBox",     PN_DEV_COMBOX,      PMD_DEVICE_IS_NOT_PHONE_DEVICE },
#else
    { "PN_DEV_COMBOX",    "COMBox",     0x18,               PMD_DEVICE_IS_NOT_PHONE_DEVICE },
#endif
#ifdef PN_DEV_TRACEBOX
    { "PN_DEV_TRACEBOX",  "Tracebox",   PN_DEV_TRACEBOX,    PMD_DEVICE_IS_NOT_PHONE_DEVICE },
#else
    { "PN_DEV_OSTRICH",   "Tracebox",   PN_DEV_OSTRICH,     PMD_DEVICE_IS_NOT_PHONE_DEVICE },
#endif
#ifdef PN_DEV_FASTTRACE
    { "PN_DEV_FASTTRACE", "FastTrace",  PN_DEV_FASTTRACE,   PMD_DEVICE_IS_NOT_PHONE_DEVICE },
#else
    { "PN_DEV_FASTTRACE", "FastTrace",  0x58,               PMD_DEVICE_IS_NOT_PHONE_DEVICE },
#endif
#ifdef PN_DEV_SOS
    { "PN_DEV_SOS",       "SOS",        PN_DEV_SOS,         0 },
#else
    { "PN_DEV_SOS",       "SOS",        0x6C,               0 },
#endif
#ifdef PN_DEV_DSP_AUX
    { "PN_DEV_DSP_AUX",   "ADSP",       PN_DEV_DSP_AUX,     0 },
#else
    { "PN_DEV_DSP_AUX",   "ADSP",       0x78,               0 },
#endif
#ifdef PN_DEV_DSP_MAIN
    { "PN_DEV_DSP_MAIN",  "CDSP",       PN_DEV_DSP_MAIN,    0 },
#else
    { "PN_DEV_DSP_MAIN",  "CDSP",       0x7C,               0 },
#endif
};

pmd_constant pmd_constant_sequence_type[PMD_SEQUENCE_TYPE_MAX] =
{
    { "NONE",                   PMD_SEQUENCE_TYPE_NONE },
    { "SIMPLE",                 PMD_SEQUENCE_TYPE_SIMPLE },
    { "SUB_BLOCK",              PMD_SEQUENCE_TYPE_SUB_BLOCK },
    { "MERGE_BE",               PMD_SEQUENCE_TYPE_BIG_ENDIAN_MERGED },
    { "MERGE_LE",               PMD_SEQUENCE_TYPE_BIG_ENDIAN_MERGED },
    { "STRUCT",                 PMD_SEQUENCE_TYPE_STRUCTURE },
    { "ANONYMOUS",              PMD_SEQUENCE_TYPE_ANONYMOUS },
    { "MSG",                    PMD_SEQUENCE_TYPE_MESSAGE },
    { "ENTRY_POINT",            PMD_SEQUENCE_TYPE_ENTRY_POINT },
    { "INDEX_ARRAY_ELEMENT",    PMD_SEQUENCE_TYPE_INDEX_ARRAY_ELEMENT },
    { "PRINTF",                 PMD_SEQUENCE_TYPE_PRINTF }
};

/**** enum HW_RESET_REASONS (from os_trace_data.txt in wp_sw build) ****/
pmd_constant pmd_constant_hw_reset_type[PMD_HW_RESET_TYPE_MAX] =
{
    { "HW_RESET_RESERVED",                      0 },
    { "HW_RESET_UNKNOWN",                       1 },
    { "HW_RESET_POWER_OFF_CHARGER_CONNECTED",   2 },
    { "HW_RESET_POWER_OFF_KEY_PRESSED",         3 },
    { "HW_RESET_SW_RESET_REQUESTED",            4 },
    { "HW_RESET_INT_ERROR",                     5 },
    { "HW_RESET_STACK_OVERFLOW",                6 },
    { "HW_RESET_WD_RESET_REQUESTED",            7 },
    { "HW_RESET_DIV_BY_ZERO",                   8 },
    { "HW_RESET_DSP_NO_RESPONSE_ERROR",         9 },
    { "HW_RESET_DSP_ERROR",                    10 },
    { "HW_RESET_DSP_INVALID_MSG_ERROR",        11 },
    { "HW_RESET_PRODUCTION_RESET",             12 },
    { "HW_RESET_ASSERTION_FAILED",             13 },
    { "HW_RESET_UNDEFINED_INSTRUCTION",        14 },
    { "HW_RESET_IO_ABORT",                     15 },
    { "HW_RESET_NULL_ACCESS",                  16 },
    { "HW_RESET_ADDRESS_ERROR",                17 },
    { "HW_RESET_ALIGNMENT_ERROR",              18 },
    { "HW_RESET_FLASH_WRITE_PROTECTION",       19 },
    { "HW_RESET_CBUS_ERROR",                   20 },
    { "HW_RESET_POWER_OFF_RTC",                21 },
    { "HW_RESET_OS_FATAL_HANDLER",             22 },
    { "HW_RESET_FLASH_BLOCK_OVERFLOW",         23 },
    { "HW_RESET_DSP_STARTUP_FAILED",           24 },
    { "HW_RESET_ASIC_WD_RESET",                25 },
    { "HW_RESET_EPOC_RESET",                   26 },
    { "HW_RESET_ADSP_NO_RESPONSE_ERROR",       27 },
    { "HW_RESET_ADSP_ERROR",                   28 },
    { "HW_RESET_ADSP_INVALID_MSG_ERROR",       29 },
    { "HW_RESET_ADSP_STARTUP_FAILED",          30 },
    { "HW_RESET_ABORT_EBUSC",                  31 },
    { "HW_RESET_ABORT_PREFETCH",               32 },
    { "HW_RESET_ABORT_DATA",                   33 },
    { "HW_RESET_UNHANDLED_ABORT",              34 },
    { "HW_RESET_SISA_EXIT",                    35 },
    { "HW_RESET_OS_WARNING_HANDLER",           36 },
    { "HW_RESET_SECURE_VIOLATION",             37 },
    { "HW_RESET_USER_RESET",                   38 },
    { "HW_RESET_MODEM",                        39 }
};

pmd_constant pmd_constant_os_task_state[PMD_OS_TASK_STATE_MAX] =
{
    { "RUNNING",        0x01 },
    { "READY",          0x02 },
    { "WAITING",        0x03 },
    { "MSG_WAITING",    0x04 },
    { "SUSPEND",        0x05 },
    { "YIELDING",       0x06 }
};

pmd_constant pmd_constant_os_error_code[PMD_OS_ERROR_CODE_MAX] =
{
    { "OS_NO_ERROR",                       0 },
    { "OS_USER_DEFINED_ERROR",             1 },
    { "OS_BINARY_SEMAPHORE_USE",         129 },
    { "OS_BLOCK_USE_AFTER_DEALLOC",      130 },
    { "OS_CONFIGURATION",                131 },
    { "OS_ILLEGAL_NAME",                 132 },
    { "OS_ILLEGAL_TASK",                 133 },
    { "OS_ILLEGAL_TIMER",                134 },
    { "OS_ILLEGAL_TYPE",                 135 },
    { "OS_INSUFFICIENT_PRIVILEGE",       136 },
    { "OS_INTERNAL",                     137 },
    { "OS_MULTIPLE_DEALLOCATION",        138 },
    { "OS_NAME_IN_USE",                  139 },
    { "OS_NONEXISTENT_TARGET",           140 },
    { "OS_NO_ROOM_FOR_NEW",              141 },
    { "OS_PARAMETER",                    142 },
    { "OS_PREV_BLOCK_OVERWRITE",         143 },
    { "OS_NO_OPERATION_NEEDED",          144 },
    { "OS_TARGET_MBX_FULL",              145 },
    { "OS_THIS_BLOCK_OVERWRITE",         146 },
    { "OS_PRIORITY_OUT_OF_RANGE",        147 },
    { "OS_BLOCK_SET_NAME_EMPTY",         148 },
    { "OS_NO_BLOCKS",                    149 },
    { "OS_MODIFIED_BLOCK_POINTER",       150 },
    { "OS_BAD_MAGIC_NUMBER",             151 },
    { "OS_POINTER_CORRUPTION",           152 },
    { "OS_USAGE",                        153 },
    { "OS_THIS_BLOCK_TAIL_OVERWRITE",    154 },
    { "OS_CALL_FORWARDED",               155 },
    { "OS_TASK_RETURNED",                156 },
    { "OS_STACK_OVERFLOW",               157 },
    { "OS_TARGET_MBX_FULL_NO_WAIT",      158 },
    { "OS_TARGET_FASTMSG_MBX_FULL",      159 },
    { "OS_TARGET_FASTMSG_MBX_FULL_NO_WAIT",  160 },
    { "OS_LARGER_BLOCK_USED",            161 },
    { "OS_BLOCK_REQUEST_TOO_BIG",        162 },
    { "OS_STACK_LOW",                    163 },
    { "OS_DUPLICATE_REGISTRATION",       164 },
    { "OS_REGION_USE",                   165 },
    { "OS_ILLEGAL_REGION",               166 },
    { "OS_TARGET_CALLBACK_BUFFER_FULL",  167 },
    { "OS_MEMORY_LOW",                   168 },
    { "OS_TOP_RESPONSE",                 169 },
    { "OS_OUT_OF_MEMORY",                170 },
    { "OS_ILLEGAL_ID",                   171 },
    { "OS_ILLEGAL_RESOURCE",             172 },
    { "OS_RESOURCE_ALREADY_RESERVED",    173 },
    { "OS_OBJECT_DELETED",               174 }
};

pmd_constant pmd_constant_os_hook[PMD_OS_HOOK_MAX] =
{
    { "HOOK_UNKNOWN",                                   0 },
    { "HOOK_IRQ_BEGIN",                                 1 },
    { "HOOK_IRQ_END",                                   2 },
    { "HOOK_IRQ_INFO",                                  3 },
    { "HOOK_IPC_DUMP",                                  4 },
    { NULL,                                             5 }, /* ?? */
    { NULL,                                             6 }, /* ?? */
    { NULL,                                             7 }, /* ?? */
    { "HOOK_FIQ_BEGIN",                                 8 },
    { "HOOK_FIQ_END",                                   9 },
    { "HOOK_FIQ_STACK_OVERFLOW",                       10 },
    { NULL,                                            11 }, /* ?? */
    { NULL,                                            12 }, /* ?? */
    { NULL,                                            13 }, /* ?? */
    { NULL,                                            14 }, /* ?? */
    { NULL,                                            15 }, /* ?? */
    { "HOOK_ERROR",                                    16 },
    { "HOOK_WARNING",                                  17 },
    { "HOOK_INFO",                                     18 },
    { "HOOK_BLOCK_INIT",                               19 },
    { "HOOK_IDLE",                                     20 },
    { "HOOK_MSG_INIT",                                 21 },
    { "HOOK_OS_INIT",                                  22 },
    { "HOOK_REG_EV_MODE_START",                        23 },
    { "HOOK_RESOURCE_INIT",                            24 },
    { "HOOK_TASK_INIT",                                25 },
    { "HOOK_TIMER_INIT",                               26 },
    { "HOOK_SCHEDULE",                                 27 },
    { "HOOK_START_TASK",                               28 },
    { "HOOK_TASK_CHANGE_PRIOR",                        29 },
    { "HOOK_TASK_LIST_INSERT",                         30 },
    { "HOOK_TASK_LIST_REMOVE",                         31 },
    { "HOOK_TASK_RESUME",                              32 },
    { "HOOK_TASK_SUSPEND",                             33 },
    { "HOOK_INTERRUPT_ENABLE",                         34 },
    { "HOOK_INTERRUPT_DISABLE",                        35 },
    { "HOOK_COND_INT_ENABLE",                          36 },
    { "HOOK_COND_INT_DISABLE",                         37 },
    { "HOOK_TIMERMSG_REMOVE",                          38 },
    { "HOOK_TIMER_EXPIRED",                            39 },
    { "HOOK_TIMER_LIST_INSERT",                        40 },
    { "HOOK_TIMER_READ",                               41 },
    { "HOOK_TIMER_START",                              42 },
    { "HOOK_TIMER_STOP",                               43 },
    { "HOOK_READ_TIMER",                               44 },
    { "HOOK_SET_TIMER",                                45 },
    { "HOOK_REG_EVENT_INT",                            46 },
    { "HOOK_TIMER_INT",                                47 },
    { "HOOK_FASTMSG_RECEIVE",                          48 },
    { "HOOK_FASTMSG_SELECT",                           49 },
    { "HOOK_FASTMSG_SEND_NO_WAIT",                     50 },
    { "HOOK_FASTMSG_SEND_WAIT",                        51 },
    { "HOOK_MSG_COUNT_READ",                           52 },
    { "HOOK_MSG_RECEIVE",                              53 },
    { "HOOK_MSG_SEND_NO_WAIT",                         54 },
    { "HOOK_MSG_SEND_WAIT",                            55 },
    { "HOOK_TIMERMSG_RECEIVE",                         56 },
    { "HOOK_WAIT_IN_FASTMSG_SEND_WAIT",                57 },
    { "HOOK_WAIT_IN_MSG_RECEIVE",                      58 },
    { "HOOK_WAIT_IN_MSG_SEND_WAIT",                    59 },
    { "HOOK_BLOCK_ALLOC",                              60 },
    { "HOOK_BLOCK_ALLOC_NO_WAIT",                      61 },
    { "HOOK_BLOCK_COUNT_READ",                         62 },
    { "HOOK_BLOCK_DEALLOC",                            63 },
    { "HOOK_HEAP_ALLOC",                               64 },
    { "HOOK_HEAP_BLOCK_COUNT_READ",                    65 },
    { "HOOK_HEAP_DEALLOC",                             66 },
    { "HOOK_WAIT_IN_BLOCK_ALLOC",                      67 },
    { "HOOK_WAIT_IN_HEAP_ALLOC",                       68 },
    { "HOOK_RESOURCE_RESERVE",                         69 },
    { "HOOK_RESOURCE_RELEASE",                         70 },
    { "HOOK_WAIT_IN_RESOURCE_RESERVE",                 71 },
    { "HOOK_BLOCK_ALLOC_ERROR_GET",                    72 },
    { "HOOK_BLOCK_ALLOC_STATUS_GET",                   73 },
    { "HOOK_MSGBUF_STATUS_GET",                        74 },
    { "HOOK_TASK_LOADING_TRACE",                       75 },
    { "HOOK_MSGBUF_STATUS",                            76 },
    { "HOOK_POOL_STATUS",                              77 },
    { "HOOK_READY_LIST_STATUS",                        78 },
    { "HOOK_RESOURCE_STATUS",                          79 },
    { "HOOK_TASK_ID_GET",                              80 },
    { "HOOK_TASK_DELETE",                              81 },
    { "HOOK_TASK_MODE_GET",                            82 },
    { "HOOK_TASK_CREATE",                              83 },
    { "HOOK_TIMER_ID_GET",                             84 },
    { "HOOK_TIMER_CREATE_ID",                          85 },
    { "HOOK_TIMER_DELETE_ID",                          86 },
    { "HOOK_TASK_STATUS_CHANGE",                       87 },
    { NULL,                                            88 }, /* HOOK_BLOCK_ALLOC_F_L */
    { NULL,                                            89 }, /* HOOK_BLOCK_ALLOC_NO_WAIT_F_L */
    { NULL,                                            90 }, /* HOOK_BLOCK_DEALLOC_F_L */
    { NULL,                                            91 }, /* HOOK_HEAP_ALLOC_F_L */
    { NULL,                                            92 }, /* HOOK_HEAP_DEALLOC_F_L */
    { "HOOK_TASK_SWITCH",                              93 },
    { "HOOK_TASK_MODE_SET",                            94 },
    { "HOOK_CURRENT_TIME_READ",                        95 },
    { "HOOK_BLOCK_DEBUG_ADDR_GET",                     96 },
    { "HOOK_HEAP_DEBUG_ADDR_GET",                      97 },
    { "HOOK_TASK_NAME_GET",                            98 },
    { "HOOK_TIMER_NAME_GET",                           99 },
    { "HOOK_TRACE_GROUP_ENABLE",                       100 },
    { "HOOK_TRACE_GROUP_DISABLE",                      101 },
    { "HOOK_BLOCK_DEBUG_CALLBACK_REG",                 102 },
    { "HOOK_BLOCK_DEBUG_CALLBACK_DEREG",               103 },
    { "HOOK_STATIC_BLOCK_INIT",                        104 },
    { "HOOK_STATIC_BLOCK_ALLOC",                       105 },
    { "HOOK_REGION_CREATE",                            106 },
    { "HOOK_REGION_DELETE",                            107 },
    { "HOOK_REGION_ENTER",                             108 },
    { "HOOK_REGION_EXIT",                              109 },
    { "HOOK_WAIT_IN_REGION_ENTER",                     110 },
    { "HOOK_REGION_NAME_GET",                          111 },
    { "HOOK_REGION_ID_GET",                            112 },
    { "HOOK_AUX_DEALLOCATOR_REG",                      113 },
    { "HOOK_AUX_DEALLOCATOR_DEREG",                    114 },
    { "HOOK_CALLBACK_INJECT",                          115 },
    { "HOOK_CALLBACK_EXECUTE",                         116 },
    { "HOOK_TASK_OWN_PRIOR_READ",                      117 },
    { "HOOK_HEAP_ALLOC_NO_WAIT",                       118 },
    { "HOOK_COND_HEAP_ALLOC",                          119 },
    { "HOOK_HEAP_AREA_ADD",                            120 },
    { "HOOK_HEAP_INIT",                                121 },
    { "HOOK_SLOW_HEAP_ALLOC",                          122 },
    { "HOOK_SLOW_HEAP_ALLOC_NO_WAIT",                  123 },
    { "HOOK_SLOW_HEAP_DEALLOC",                        124 },
    { "HOOK_WAIT_IN_SLOW_HEAP_ALLOC",                  125 },
    { "HOOK_CURRENT_TIME_READ_MS",                     126 },
    { "HOOK_CALLER_DEPTH_SET",                         127 },
    { "HOOK_DEBUG_INIT",                               128 },
    { "HOOK_YIELD_LIST_UPDATE",                        129 },
    { "HOOK_YIELD_LIST_CLEAR",                         130 },
    { "HOOK_YIELD",                                    131 },
    { "HOOK_HEAP_ALLOC_NO_WAIT_FROM",                  132 },
    { "HOOK_HEAP_ALLOC_FROM",                          133 },
    { "HOOK_HEAP_CREATE",                              134 },
    { "HOOK_HEAP_TASK_LIST_SET",                       135 },
    { "HOOK_HEAP_DELETE",                              136 },
    { "HOOK_BLOCK_REALLOC",                            137 },
    { "HOOK_ALIGNED_BLOCK_ALLOC_NO_WAIT",              138 },
    { "HOOK_ALIGNED_BLOCK_ALLOC",                      139 },
    { "HOOK_WAIT_IN_ALIGNED_BLOCK_ALLOC",              140 },
    { "HOOK_MMU_PAGE_ALIGNED_HEAP_DEALLOC",            141 },
    { "HOOK_MMU_PAGE_ALIGNED_HEAP_INIT ",              142 },
    { "HOOK_WAIT_IN_HEAP_ALLOC_FROM",                  143 },
    { "HOOK_POOL_ALLOCATOR",                           144 },
    { "HOOK_POOL_DEALLOCATOR",                         145 },
    { "HOOK_POOL_ALLOC_FROM",                          146 },
    { "HOOK_POOL_ALLOC_NO_WAIT_FROM",                  147 },
    { "HOOK_POOL_CREATE",                              148 },
    { "HOOK_WAIT_IN_POOL_ALLOC_FROM",                  149 },
    { "HOOK_HEAP_ALLOCATOR",                           150 },
    { "HOOK_HEAP_DEALLOCATOR",                         151 },
    { "HOOK_TASK_TIME_SLICE_SET",                      152 },
    { "HOOK_TASK_TIME_SLICE_END",                      153 },
    { "HOOK_RESOURCE_RESERVE_TIMED",                   154 },
    { "HOOK_RESOURCE_CREATE",                          155 },
    { "HOOK_RESOURCE_DELETE",                          156 },
    { "HOOK_WAIT_IN_RESOURCE_RESERVE_TIMED",           157 },
    { "HOOK_RESOURCE_RESERVE_EXPIRED",                 158 },
    { "HOOK_RESOURCE_ID_GET",                          159 },
    { "HOOK_RESOURCE_NAME_GET",                        160 },
    { "HOOK_TIMER_EXPIRATION_MODE_SET",                161 }
};

pmd_constant pmd_constant_tracebox_object_id[PMD_TRACEBOX_OBJECT_ID_MAX] =
{
    { NULL,                         0x00 },
    { "PN_OBJ_TRACEBOX_MAIN",       0x01 },
    { "PN_OBJ_TRACEBOX_STI_1",      0x02 },
    { "PN_OBJ_TRACEBOX_XTI_r2_1",   0x03 },
    { "PN_OBJ_TRACEBOX_STI_2",      0x04 },
    { "PN_OBJ_TRACEBOX_XTI_r2_2",   0x05 },
    { "PN_OBJ_TRACEBOX_C_STI_1",    0x06 },
    { "PN_OBJ_TRACEBOX_C_STI_2",    0x07 },
    { "PN_OBJ_TRACEBOX_ST_XTI_1",   0x08 },
    { "PN_OBJ_TRACEBOX_ST_XTI_2",   0x09 },
    { "PN_OBJ_TRACEBOX_XTI_r3_1",   0x0A },
    { "PN_OBJ_TRACEBOX_XTI_r3_2",   0x0B },
    { "PN_OBJ_TRACEBOX_0",          0x0C },
    { "PN_OBJ_TRACEBOX_1",          0x0D },
    { "PN_OBJ_TRACEBOX_2",          0x0E },
    { "PN_OBJ_TRACEBOX_3",          0x0F },
    { "PN_OBJ_TRACEBOX_4",          0x10 },
    { "PN_OBJ_TRACEBOX_5",          0x11 },
    { "PN_OBJ_TRACEBOX_6",          0x12 },
    { "PN_OBJ_TRACEBOX_7",          0x13 }
};

pmd_constant pmd_constant_resource_type[PMD_RESOURCE_TYPE_MAX] =
{
    { "UNKNOWN",          PMD_RESOURCE_TYPE_UNKNOWN },
    { "SERVER",           PMD_RESOURCE_TYPE_SERVER },
    { NULL,               2 },
    { NULL,               3 },
    { "MEDIA_MODULE",     PMD_RESOURCE_TYPE_MEDIA_MODULE },
    { "SERVER_PRIVATE",   PMD_RESOURCE_TYPE_SERVER_PRIVATE },
    { "PHONET",           PMD_RESOURCE_TYPE_PHONET },
    { "PHONET_EXT",       PMD_RESOURCE_TYPE_PHONET_EXT },
    { "PROTOCOL",         PMD_RESOURCE_TYPE_PROTOCOL }
};

pmd_constant pmd_constant_entry_point[PMD_ENTRY_POINT_TOTAL_COUNT] =
{
    /* Protocol group 1 */
    { "PROTOCOL_PHONET",                    PMD_PROTOCOL_PHONET },
    { "PROTOCOL_AI2_CMD_PACKETS",           PMD_PROTOCOL_AI2_CMD_PACKETS },
    { "PROTOCOL_AI2_RSP_PACKETS",           PMD_PROTOCOL_AI2_RSP_PACKETS },
    { "PROTOCOL_X_FILE",                    PMD_PROTOCOL_X_FILE },
    { "PROTOCOL_INVARIANT_TRACE",           PMD_PROTOCOL_INVARIANT_TRACE },
    { "PROTOCOL_MODEM_L1_INTERNAL_MSGS",    PMD_PROTOCOL_MODEM_L1_INTERNAL_MSGS },
    { "PROTOCOL_EUTRAN_L2_INTERNAL_MSGS",   PMD_PROTOCOL_EUTRAN_L2_INTERNAL_MSGS },
    { "PROTOCOL_MCU_TRACE",                 PMD_PROTOCOL_MCU_TRACE },
    { "PROTOCOL_SYMBIAN_TRACE",             PMD_PROTOCOL_SYMBIAN_TRACE },
    { "PROTOCOL_IPC_INTERNAL_MSGS",         PMD_PROTOCOL_IPC_INTERNAL_MSGS },
    { "PROTOCOL_MEIF_MESSAGES",             PMD_PROTOCOL_MEIF_MESSAGES },
    { "PROTOCOL_PEIF_MESSAGES",             PMD_PROTOCOL_PEIF_MESSAGES },
    { "PROTOCOL_CDSP5_TRACE",               PMD_PROTOCOL_CDSP5_TRACE },
    { "PROTOCOL_XTI_MASTER",                PMD_PROTOCOL_XTI_MASTER },
    { "PROTOCOL_OST",                       PMD_PROTOCOL_OST },
    { "PROTOCOL_OST_VERSION",               0x000F },                      /* Obsolete */
    { "PROTOCOL_RANC_MSGS",                 PMD_PROTOCOL_RANC_MSGS },
    { "PROTOCOL_MACN_MSGS",                 PMD_PROTOCOL_MACN_MSGS },
    { "PROTOCOL_NOA_INTERNAL_MSGS",         PMD_PROTOCOL_NOA_INTERNAL_MSGS },
    { "PROTOCOL_LS_NPE_EVENT",              PMD_PROTOCOL_LS_NPE_EVENT },
    { "PROTOCOL_NOA_APPL_INTERNAL_MSGS",    PROTOCOL_NOA_APPL_INTERNAL_MSGS },

    /* Protocol group 2 */
    { "PROTOCOL_LCIF",                      PMD_PROTOCOL_LCIF },
    { "PROTOCOL_GERAN_INTERNAL_MSGS",       PMD_PROTOCOL_GERAN_INTERNAL_MSGS },
    { "PROTOCOL_PH_INTERNAL_MSGS",          PMD_PROTOCOL_PH_INTERNAL_MSGS },

    /* Entry point subtrees */
    { "ENTRY_POINT_PN_RESOURCE",            PMD_ENTRY_POINT_PN_RESOURCE },
    { "ENTRY_POINT_PN_PRIVATE",             PMD_ENTRY_POINT_PN_PRIVATE },
    { "ENTRY_POINT_PN_PREFIX",              PMD_ENTRY_POINT_PN_PREFIX },
    { "ENTRY_POINT_PHONET_RESOURCE",        PMD_ENTRY_POINT_PHONET_RESOURCE },
    { "ENTRY_POINT_XTI_MASTER",             PMD_ENTRY_POINT_XTI_MASTER },
    { "ENTRY_POINT_SYMBIAN_TRACE_ENTITY",   PMD_ENTRY_POINT_SYMBIAN_TRACE_ENTITY },
    { "ENTRY_POINT_INVARIANT_TRACE_ENTITY", PMD_ENTRY_POINT_INVARIANT_TRACE_ENTITY },
    { "ENTRY_POINT_VENDOR_COMPONENT_TRACE_ENTITY", PMD_ENTRY_POINT_VENDOR_COMPONENT_TRACE_ENTITY },
    { "ENTRY_POINT_CDSP5_TRACE_ENTITY",     PMD_ENTRY_POINT_CDSP5_TRACE_ENTITY },
    { "ENTRY_POINT_ADSP5_TRACE_ENTITY",     PMD_ENTRY_POINT_ADSP5_TRACE_ENTITY },
    { "ENTRY_POINT_OST_PROTOCOL",           PMD_ENTRY_POINT_OST_PROTOCOL },

    /* Entry points */
    { "ENTRY_POINT_MCU_TRACE",              PMD_ENTRY_POINT_MCU_TRACE },
    { "ENTRY_POINT_INVARIANT_TRACE",        PMD_ENTRY_POINT_INVARIANT_TRACE },
    { "ENTRY_POINT_NOS_TRACE",              PMD_ENTRY_POINT_NOS_TRACE },
    { "ENTRY_POINT_HAL_TRACE",              PMD_ENTRY_POINT_HAL_TRACE },
    { "ENTRY_POINT_SYMBIAN_TRACE",          PMD_ENTRY_POINT_SYMBIAN_TRACE },
    { "ENTRY_POINT_CDSP5_TRACE",            PMD_ENTRY_POINT_CDSP5_TRACE },
    { "ENTRY_POINT_ADSP5_TRACE",            PMD_ENTRY_POINT_ADSP5_TRACE },
    { "ENTRY_POINT_CDSP5_TRACE_OLD",        PMD_ENTRY_POINT_CDSP5_TRACE_OLD },
    { "ENTRY_POINT_ADSP5_TRACE_OLD",        PMD_ENTRY_POINT_ADSP5_TRACE_OLD },
    { "ENTRY_POINT_MASTER_TRACE",           PMD_ENTRY_POINT_MASTER_TRACE },
    { "ENTRY_POINT_VENDOR_COMPONENT_TRACE", PMD_ENTRY_POINT_VENDOR_COMPONENT_TRACE },
    { "ENTRY_POINT_HSP_TRACE",              PMD_ENTRY_POINT_HSP_TRACE },
    { "ENTRY_POINT_MASTER_HW_TRACE",        PMD_ENTRY_POINT_MASTER_HW_TRACE },

    { "ENTRY_POINT_MEDIA_CONTROLLER_00",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x00 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_01",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x01 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_02",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x02 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_03",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x03 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_04",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x04 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_05",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x05 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_06",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x06 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_07",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x07 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_08",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x08 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_09",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x09 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_0A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x0A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_0B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x0B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_0C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x0C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_0D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x0D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_0E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x0E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_0F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x0F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_10",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x10 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_11",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x11 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_12",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x12 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_13",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x13 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_14",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x14 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_15",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x15 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_16",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x16 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_17",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x17 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_18",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x18 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_19",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x19 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_1A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x1A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_1B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x1B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_1C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x1C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_1D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x1D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_1E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x1E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_1F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x1F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_20",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x20 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_21",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x21 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_22",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x22 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_23",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x23 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_24",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x24 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_25",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x25 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_26",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x26 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_27",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x27 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_28",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x28 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_29",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x29 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_2A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x2A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_2B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x2B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_2C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x2C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_2D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x2D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_2E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x2E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_2F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x2F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_30",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x30 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_31",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x31 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_32",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x32 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_33",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x33 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_34",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x34 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_35",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x35 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_36",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x36 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_37",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x37 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_38",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x38 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_39",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x39 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_3A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x3A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_3B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x3B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_3C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x3C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_3D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x3D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_3E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x3E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_3F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x3F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_40",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x40 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_41",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x41 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_42",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x42 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_43",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x43 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_44",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x44 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_45",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x45 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_46",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x46 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_47",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x47 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_48",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x48 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_49",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x49 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_4A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x4A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_4B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x4B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_4C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x4C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_4D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x4D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_4E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x4E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_4F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x4F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_50",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x50 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_51",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x51 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_52",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x52 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_53",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x53 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_54",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x54 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_55",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x55 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_56",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x56 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_57",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x57 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_58",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x58 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_59",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x59 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_5A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x5A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_5B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x5B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_5C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x5C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_5D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x5D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_5E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x5E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_5F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x5F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_60",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x60 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_61",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x61 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_62",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x62 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_63",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x63 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_64",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x64 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_65",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x65 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_66",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x66 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_67",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x67 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_68",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x68 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_69",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x69 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_6A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x6A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_6B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x6B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_6C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x6C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_6D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x6D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_6E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x6E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_6F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x6F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_70",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x70 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_71",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x71 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_72",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x72 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_73",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x73 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_74",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x74 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_75",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x75 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_76",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x76 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_77",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x77 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_78",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x78 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_79",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x79 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_7A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x7A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_7B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x7B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_7C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x7C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_7D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x7D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_7E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x7E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_7F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x7F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_80",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x80 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_81",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x81 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_82",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x82 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_83",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x83 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_84",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x84 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_85",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x85 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_86",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x86 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_87",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x87 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_88",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x88 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_89",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x89 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_8A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x8A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_8B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x8B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_8C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x8C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_8D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x8D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_8E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x8E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_8F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x8F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_90",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x90 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_91",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x91 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_92",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x92 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_93",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x93 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_94",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x94 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_95",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x95 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_96",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x96 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_97",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x97 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_98",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x98 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_99",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x99 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_9A",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x9A },
    { "ENTRY_POINT_MEDIA_CONTROLLER_9B",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x9B },
    { "ENTRY_POINT_MEDIA_CONTROLLER_9C",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x9C },
    { "ENTRY_POINT_MEDIA_CONTROLLER_9D",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x9D },
    { "ENTRY_POINT_MEDIA_CONTROLLER_9E",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x9E },
    { "ENTRY_POINT_MEDIA_CONTROLLER_9F",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0x9F },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A0",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA0 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A1",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA1 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A2",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA2 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A3",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA3 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A4",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA4 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A5",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA5 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A6",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA6 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A7",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA7 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A8",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA8 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_A9",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xA9 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_AA",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xAA },
    { "ENTRY_POINT_MEDIA_CONTROLLER_AB",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xAB },
    { "ENTRY_POINT_MEDIA_CONTROLLER_AC",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xAC },
    { "ENTRY_POINT_MEDIA_CONTROLLER_AD",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xAD },
    { "ENTRY_POINT_MEDIA_CONTROLLER_AE",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xAE },
    { "ENTRY_POINT_MEDIA_CONTROLLER_AF",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xAF },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B0",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB0 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B1",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB1 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B2",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB2 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B3",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB3 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B4",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB4 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B5",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB5 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B6",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB6 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B7",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB7 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B8",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB8 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_B9",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xB9 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_BA",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xBA },
    { "ENTRY_POINT_MEDIA_CONTROLLER_BB",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xBB },
    { "ENTRY_POINT_MEDIA_CONTROLLER_BC",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xBC },
    { "ENTRY_POINT_MEDIA_CONTROLLER_BD",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xBD },
    { "ENTRY_POINT_MEDIA_CONTROLLER_BE",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xBE },
    { "ENTRY_POINT_MEDIA_CONTROLLER_BF",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xBF },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C0",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC0 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C1",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC1 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C2",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC2 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C3",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC3 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C4",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC4 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C5",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC5 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C6",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC6 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C7",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC7 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C8",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC8 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_C9",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xC9 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_CA",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xCA },
    { "ENTRY_POINT_MEDIA_CONTROLLER_CB",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xCB },
    { "ENTRY_POINT_MEDIA_CONTROLLER_CC",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xCC },
    { "ENTRY_POINT_MEDIA_CONTROLLER_CD",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xCD },
    { "ENTRY_POINT_MEDIA_CONTROLLER_CE",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xCE },
    { "ENTRY_POINT_MEDIA_CONTROLLER_CF",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xCF },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D0",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD0 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D1",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD1 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D2",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD2 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D3",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD3 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D4",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD4 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D5",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD5 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D6",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD6 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D7",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD7 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D8",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD8 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_D9",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xD9 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_DA",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xDA },
    { "ENTRY_POINT_MEDIA_CONTROLLER_DB",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xDB },
    { "ENTRY_POINT_MEDIA_CONTROLLER_DC",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xDC },
    { "ENTRY_POINT_MEDIA_CONTROLLER_DD",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xDD },
    { "ENTRY_POINT_MEDIA_CONTROLLER_DE",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xDE },
    { "ENTRY_POINT_MEDIA_CONTROLLER_DF",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xDF },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E0",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE0 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E1",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE1 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E2",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE2 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E3",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE3 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E4",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE4 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E5",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE5 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E6",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE6 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E7",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE7 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E8",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE8 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_E9",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xE9 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_EA",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xEA },
    { "ENTRY_POINT_MEDIA_CONTROLLER_EB",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xEB },
    { "ENTRY_POINT_MEDIA_CONTROLLER_EC",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xEC },
    { "ENTRY_POINT_MEDIA_CONTROLLER_ED",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xED },
    { "ENTRY_POINT_MEDIA_CONTROLLER_EE",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xEE },
    { "ENTRY_POINT_MEDIA_CONTROLLER_EF",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xEF },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F0",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF0 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F1",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF1 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F2",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF2 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F3",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF3 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F4",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF4 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F5",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF5 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F6",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF6 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F7",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF7 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F8",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF8 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_F9",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xF9 },
    { "ENTRY_POINT_MEDIA_CONTROLLER_FA",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xFA },
    { "ENTRY_POINT_MEDIA_CONTROLLER_FB",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xFB },
    { "ENTRY_POINT_MEDIA_CONTROLLER_FC",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xFC },
    { "ENTRY_POINT_MEDIA_CONTROLLER_FD",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xFD },
    { "ENTRY_POINT_MEDIA_CONTROLLER_FE",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xFE },
    { "ENTRY_POINT_MEDIA_CONTROLLER_FF",    PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST + 0xFF }
};

/* Table listing if a PMD file format version is compatible with the previous version        */
/* Compatibility is determined by the ability of the Tracing SDK to make up for differences  */
/* in the PMD file formats when appending PMD files.                                         */
/* Entries is added for each new format change to the PMD file format and is listed with     */
/* newest versions first.                                                                    */
/* PMD file versions NOT listed here will be considered to be PMD_FILE_FORMAT_INCOMPATIBEL   */
pmd_version_compability pmd_version_compability_table[] =
{
    { 0x0600, PMD_FILE_FORMAT_COMPATIBEL   },
    { 0x0501, PMD_FILE_FORMAT_INCOMPATIBEL },
    { 0x0500, PMD_FILE_FORMAT_INCOMPATIBEL },
    { 0,      PMD_FILE_FORMAT_INCOMPATIBEL }
};
/* ============================================================================================= */
/* Local definitions */
/* ============================================================================================= */

#ifndef LOCAL
#define LOCAL
#endif /* LOCAL */

LOCAL const pmd_message_type_conf* pmd_lookup_message_type_conf(unsigned int id);

/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

unsigned short pmd_constant_lookup_entry_point_id(const char* name)
{
    unsigned short id = PMD_ENTRY_POINT_UNDEFINED;
    unsigned short i;

    for (i = 0; i < PMD_ENTRY_POINT_TOTAL_COUNT && id == PMD_ENTRY_POINT_UNDEFINED; i++)
    {
        if (!strcmp(pmd_constant_entry_point[i].name, name))
        {
            id = (unsigned short)pmd_constant_entry_point[i].id;
        }
    }
    return id;
}

const char* pmd_constant_lookup_entry_point(unsigned short id)
{
    const char* name = NULL;
    int mapped_id = (int)id;

    if (id > PMD_PROTOCOL_GROUP1_LAST)
    {
        mapped_id -= (PMD_PROTOCOL_GROUP2_FIRST - PMD_PROTOCOL_GROUP1_LAST - 1);
        if (mapped_id >= 0 && id > PMD_PROTOCOL_GROUP2_LAST)
        {
            mapped_id -= (PMD_ENTRY_POINT_SUBTREE_FIRST - PMD_PROTOCOL_GROUP2_LAST - 1);
            if (mapped_id >= 0 && id > PMD_ENTRY_POINT_SUBTREE_LAST)
            {
                mapped_id -= (PMD_ENTRY_POINT_FIRST - PMD_ENTRY_POINT_SUBTREE_LAST - 1);
                if (mapped_id >= 0 && id > PMD_ENTRY_POINT_LAST)
                {
                    mapped_id -= (PMD_ENTRY_POINT_MEDIA_CONTROLLER_FIRST - PMD_ENTRY_POINT_LAST - 1);
                }
            }
        }
    }

    if (mapped_id >= 0 && mapped_id < PMD_ENTRY_POINT_TOTAL_COUNT)
    {
        name = pmd_constant_entry_point[mapped_id].name;
    }

    return name;
}

const char* pmd_constant_lookup_block_algorithm(unsigned int id)
{
    if (id == PMD_BLOCK_ALGORITHM_EXTERNAL)
    {
        return pmd_constant_block_algorithm[PMD_BLOCK_ALGORITHM_MAX-1].name;
    }
    else
    {
        return (id < PMD_BLOCK_ALGORITHM_MAX-1 ? pmd_constant_block_algorithm[id].name : NULL);
    }
}

const char* pmd_constant_lookup_character_type(unsigned int id)
{
    return (id >= 0 && id < PMD_CHARACTER_TYPE_MAX) ? pmd_constant_character_type[id].name : NULL;
}

const char* pmd_constant_lookup_environment_var_id(unsigned int id)
{
    const char* name = NULL;
    int mapped_id = (int)id;

    if (id > PMD_ENVIRONMENT_VAR_ID_ORIGINAL_LAST)
    {
        mapped_id -= (PMD_ENVIRONMENT_VAR_ID_MCU_OS_FIRST - PMD_ENVIRONMENT_VAR_ID_ORIGINAL_LAST - 1);
        if (mapped_id >= 0 && id > PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAST)
        {
            mapped_id -= (PMD_ENVIRONMENT_VAR_ID_PRODUCT_FIRST - PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAST - 1);
            if (mapped_id >= 0 && id > PMD_ENVIRONMENT_VAR_ID_PRODUCT_LAST)
            {
                mapped_id -= (PMD_ENVIRONMENT_VAR_ID_ICF_FIRST - PMD_ENVIRONMENT_VAR_ID_PRODUCT_LAST - 1);
                if (mapped_id >= 0 && id > PMD_ENVIRONMENT_VAR_ID_ICF_LAST)
                {
                    mapped_id -= (PMD_ENVIRONMENT_VAR_ID_IPF_FIRST - PMD_ENVIRONMENT_VAR_ID_ICF_LAST - 1);
                    if (mapped_id >= 0 && id > PMD_ENVIRONMENT_VAR_ID_IPF_LAST)
                    {
                        mapped_id -= (PMD_ENVIRONMENT_VAR_ID_MON_FIRST - PMD_ENVIRONMENT_VAR_ID_IPF_LAST - 1);
                    }
                }
            }
        }
    }

    if (mapped_id >= 0 && mapped_id < PMD_ENVIRONMENT_VAR_ID_MAX)
    {
        name = pmd_constant_environment_var_id[mapped_id].name;
    }

    return name;
}

unsigned int pmd_constant_lookup_environment_var_id_from_name(const char* name)
{
    unsigned int id = PMD_ENVIRONMENT_VAR_ID_UNDEFINED;
    unsigned int i = 0;

    for (; i < PMD_ENVIRONMENT_VAR_ID_MAX && name; i++)
    {
        if (pmd_constant_environment_var_id[i].name && !strcmp(pmd_constant_environment_var_id[i].name, name))
        {
			id = pmd_constant_environment_var_id[i].id;
			if (id > PMD_ENVIRONMENT_VAR_ID_ORIGINAL_LAST)
			{
				id += (PMD_ENVIRONMENT_VAR_ID_MCU_OS_FIRST - PMD_ENVIRONMENT_VAR_ID_ORIGINAL_LAST - 1);
			}
			else if (id > PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAST)
			{
				id -= (PMD_ENVIRONMENT_VAR_ID_PRODUCT_FIRST - PMD_ENVIRONMENT_VAR_ID_MCU_OS_LAST - 1);
			}
			else if (id > PMD_ENVIRONMENT_VAR_ID_PRODUCT_LAST)
			{
				id += (PMD_ENVIRONMENT_VAR_ID_ICF_FIRST - PMD_ENVIRONMENT_VAR_ID_PRODUCT_LAST - 1);
			}
			else if (id > PMD_ENVIRONMENT_VAR_ID_ICF_LAST)
			{
				id += (PMD_ENVIRONMENT_VAR_ID_IPF_FIRST - PMD_ENVIRONMENT_VAR_ID_ICF_LAST - 1);
			}
			else if (id > PMD_ENVIRONMENT_VAR_ID_IPF_LAST)
			{
				id += (PMD_ENVIRONMENT_VAR_ID_MON_FIRST - PMD_ENVIRONMENT_VAR_ID_IPF_LAST - 1);
			}
			break;
        }
    }

    return id;
}

const char* pmd_constant_lookup_file_type(unsigned int id)
{
    return (id < PMD_FILE_TYPE_MAX) ? pmd_constant_file_type[id].name : NULL;
}

const char* pmd_constant_lookup_file_restriction(unsigned int id)
{
    return (id < PMD_FILE_RESTRICTION_MAX) ? pmd_constant_file_restriction[id].name : NULL;
}

const char* pmd_constant_lookup_function(unsigned int id)
{
    return (id < PMD_FUNCTION_MAX) ? pmd_constant_function[id].name : NULL;
}

const char* pmd_constant_lookup_info_type(unsigned int id)
{
    const char* info_type_name = NULL;
    int mapped_id = (int)id;

    if (mapped_id > PMD_INFO_TYPE_GROUP_1_LAST)
    {
        mapped_id -= (PMD_INFO_TYPE_GROUP_2_FIRST - PMD_INFO_TYPE_GROUP_1_LAST - 1);
    }

    if (mapped_id >= 0 && mapped_id < PMD_INFO_TYPE_MAX)
    {
        info_type_name = pmd_constant_info_type[mapped_id].name;
    }

    return info_type_name;
}

unsigned int pmd_constant_lookup_info_type_id_from_name(const char* name)
{
    unsigned int id = PMD_INFO_TYPE_NONE;
	unsigned int i = 0;

    for (; i < PMD_INFO_TYPE_MAX && name; ++i)
	{
		if (pmd_constant_info_type[i].name && (strcmp(pmd_constant_info_type[i].name, name) == 0))
		{
            id = i;
		}
	}
	return id;
}


const char* pmd_constant_lookup_info_attribute(unsigned int type, unsigned int id)
{
	unsigned int i = 0;
	for (; i < PMD_INFO_ATTR_COUNT; ++i)
	{
		if ((pmd_constant_info_attributes[i].type == type) && (pmd_constant_info_attributes[i].id == id))
		{
			return pmd_constant_info_attributes[i].name;
		}
	}
	return NULL;
}

const char* pmd_constant_lookup_length_algorithm(unsigned int id)
{
    return (id < PMD_LENGTH_ALGORITHM_MAX) ? pmd_constant_length_algorithm[id].name : NULL;
}

const char* pmd_constant_lookup_message_type_group_name(unsigned int id)
{
    const char* name = NULL;
    const pmd_message_type_group_conf* conf = pmd_constant_lookup_message_type_group_conf(id);
    if (conf)
    {
        name = conf->name;
    }
    return name;
}

const pmd_message_type_group_conf* pmd_constant_lookup_message_type_group_conf_from_message_type(unsigned int id)
{
    int group;
    const pmd_message_type_group_conf* message_type_group = NULL;

    for (group = 0; group < PMD_MESSAGE_TYPE_GROUP_MAX && !message_type_group; group++)
    {
        if (id >= pmd_constant_message_type_group[group].first_type_id &&
            id <= pmd_constant_message_type_group[group].last_type_id)
        {
            message_type_group = &pmd_constant_message_type_group[group];
        }
    }
    return message_type_group;
}

const char* pmd_constant_lookup_message_type_group_xml(unsigned int id)
{
    const char* xml_name = NULL;
    const pmd_message_type_group_conf* conf = pmd_constant_lookup_message_type_group_conf(id);
    if (conf)
    {
        xml_name = conf->xml_name;
    }
    return xml_name;
}

unsigned int pmd_constant_lookup_message_group_first_id(unsigned int id)
{
    unsigned int first_id = 0;
    const pmd_message_type_group_conf* conf = pmd_constant_lookup_message_type_group_conf(id);
    if (conf)
    {
        first_id = conf->first_type_id;
    }
    return first_id;
}

unsigned int pmd_constant_lookup_message_group_last_id(unsigned int id)
{
    unsigned int last_id = 0;
    const pmd_message_type_group_conf* conf = pmd_constant_lookup_message_type_group_conf(id);
    if (conf)
    {
        last_id = conf->last_type_id;
    }
    return last_id;
}

const char* pmd_constant_lookup_message_type_name(unsigned int id)
{
    const char* name = NULL;
    const pmd_message_type_group_conf* group_conf = pmd_constant_lookup_message_type_group_conf_from_message_type(id);
    if (group_conf)
    {
        name = group_conf->name;
    }
    else
    {
        const pmd_message_type_conf* conf = pmd_lookup_message_type_conf(id);
        if (conf)
        {
            name = conf->name;
        }
    }
    return name;
}

const char* pmd_constant_lookup_message_type_xml(unsigned int id)
{
    const char* name = NULL;
    const pmd_message_type_group_conf* group_conf = pmd_constant_lookup_message_type_group_conf_from_message_type(id);
    if (group_conf)
    {
        name = group_conf->xml_name;
    }
    else
    {
        const pmd_message_type_conf* conf = pmd_lookup_message_type_conf(id);
        if (conf)
        {
            name = conf->xml_name;
        }
    }
    return name;
}

const char* pmd_constant_lookup_message_type_identifier(unsigned int id)
{
    const char* name = NULL;
    const pmd_message_type_group_conf* group_conf = pmd_constant_lookup_message_type_group_conf_from_message_type(id);
    if (group_conf)
    {
        name = group_conf->identifier;
    }
    else
    {
        const pmd_message_type_conf* conf = pmd_lookup_message_type_conf(id);
        if (conf)
        {
            name = conf->identifier;
        }
    }
    return name;
}

unsigned int pmd_constant_lookup_message_type_flags(unsigned int id)
{
    unsigned int flags = 0;
    const pmd_message_type_group_conf* group_conf = pmd_constant_lookup_message_type_group_conf_from_message_type(id);
    if (group_conf)
    {
        flags = group_conf->flags;
    }
    else
    {
        const pmd_message_type_conf* conf = pmd_lookup_message_type_conf(id);
        if (conf)
        {
            flags = conf->flags;
        }
    }
    return flags;
}

unsigned int pmd_constant_lookup_message_type_activation_type(unsigned int id)
{
    unsigned int activation_type = PMD_TRACE_ACTIVATION_TYPE_NOT_SUPPORTED;
    const pmd_message_type_conf* conf = pmd_lookup_message_type_conf(id);
    if (conf)
    {
        activation_type = conf->activation_type;
    }
    return activation_type;
}

unsigned int pmd_constant_lookup_message_info_tree_element_type_from_xml(const char* xml)
{
    unsigned int type = PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE;

    if (pmd_constant_lookup_message_type_group_id_from_xml(xml) != PMD_MESSAGE_TYPE_GROUP_NONE)
    {
        type = PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_GROUP;
    }

    return type;
}

unsigned int pmd_constant_lookup_message_type_group_id_from_xml(const char* xml)
{
    unsigned int id = PMD_MESSAGE_TYPE_GROUP_NONE;

    for (; id < PMD_MESSAGE_TYPE_GROUP_MAX; id++)
    {
        if (pmd_constant_message_type_group[id].xml_name &&
            strcmp(pmd_constant_message_type_group[id].xml_name, xml) == 0)
        {
            return id;
        }
    }

    return PMD_MESSAGE_TYPE_GROUP_NONE;
}

unsigned int    pmd_constant_lookup_message_type_id_from_name(const char* name)
{
    unsigned int id = PMD_MESSAGE_TYPE_UNDEFINED;

    id = pmd_constant_lookup_message_type_id_from_name_helper(name, PMD_MESSAGE_TYPE_GROUP_1_FIRST, PMD_MESSAGE_TYPE_GROUP_1_LAST);
    if (id != PMD_MESSAGE_TYPE_UNDEFINED) return id;
    id = pmd_constant_lookup_message_type_id_from_name_helper(name, PMD_MESSAGE_TYPE_GROUP_2_FIRST, PMD_MESSAGE_TYPE_GROUP_2_LAST);
    if (id != PMD_MESSAGE_TYPE_UNDEFINED) return id;
    return PMD_MESSAGE_TYPE_UNDEFINED;
}

unsigned int pmd_constant_lookup_message_type_id_from_name_helper(const char* name, unsigned int id_first, unsigned int id_last)
{
    unsigned int id = id_first;
    for (; id <= id_last; ++id)
    {
        const pmd_message_type_conf* conf = pmd_lookup_message_type_conf(id);
        if (conf && conf->name)
        {
            if (strcmp(name, conf->name) == 0)
            {
                return id;
            }
        }
    }
    return PMD_MESSAGE_TYPE_UNDEFINED;
}

unsigned int pmd_constant_lookup_message_type_id_from_xml(const char* xml)
{
    unsigned int id = PMD_MESSAGE_TYPE_UNDEFINED;

    id = pmd_constant_lookup_message_type_id_from_xml_helper(xml, PMD_MESSAGE_TYPE_GROUP_1_FIRST, PMD_MESSAGE_TYPE_GROUP_1_LAST);
    if (id != PMD_MESSAGE_TYPE_UNDEFINED) return id;
    id = pmd_constant_lookup_message_type_id_from_xml_helper(xml, PMD_MESSAGE_TYPE_GROUP_2_FIRST, PMD_MESSAGE_TYPE_GROUP_2_LAST);
    if (id != PMD_MESSAGE_TYPE_UNDEFINED) return id;
    return PMD_MESSAGE_TYPE_UNDEFINED;
}

unsigned int pmd_constant_lookup_message_type_id_from_xml_helper(const char* xml, unsigned int id_first, unsigned int id_last)
{
    unsigned int id = id_first;
    for (; id <= id_last; ++id)
    {
        const pmd_message_type_conf* conf = pmd_lookup_message_type_conf(id);
        if (conf && conf->xml_name)
        {
            if (strcmp(xml, conf->xml_name) == 0)
            {
                return id;
            }
        }
    }
    return PMD_MESSAGE_TYPE_UNDEFINED;
}

unsigned int pmd_constant_lookup_message_info_tree_element_type_from_message_type(unsigned int id)
{
    unsigned int element_type = PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_UNDEFINED;

    if (pmd_constant_lookup_message_type_group_conf(id))
    {
        element_type = PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE_GROUP;
    }
    else if (pmd_lookup_message_type_conf(id))
    {
        element_type = PMD_MESSAGE_INFO_TREE_ELEMENT_TYPE_MESSAGE_TYPE;
    }

    return element_type;
}

const pmd_message_type_conf* pmd_lookup_message_type_conf(unsigned int id)
{
    const pmd_message_type_conf* conf = NULL;
    int mapped_id = (int)id;

    if (id > PMD_MESSAGE_TYPE_GROUP_1_LAST)
    {
        mapped_id -= (PMD_MESSAGE_TYPE_GROUP_2_FIRST - PMD_MESSAGE_TYPE_GROUP_1_LAST - 1);
    }

    if (mapped_id >= 0 && mapped_id < PMD_MESSAGE_TYPE_MAX)
    {
        conf = &pmd_constant_message_type[mapped_id];
    }

    return conf;
}

const pmd_message_type_group_conf* pmd_constant_lookup_message_type_group_conf(unsigned int id)
{
    return &pmd_constant_message_type_group[id];
}

const char* pmd_constant_lookup_number_special_type(unsigned int id)
{
    return (id < PMD_NUMBER_SPECIAL_TYPE_MAX) ? pmd_constant_number_special_type[id].name : NULL;
}

const char* pmd_constant_lookup_number_special_type_xml(unsigned int id)
{
    return (id < PMD_NUMBER_SPECIAL_TYPE_MAX) ? pmd_constant_number_special_type[id].xml_name : NULL;
}

const char* pmd_constant_lookup_sequence_type(unsigned int id)
{
    return (id < PMD_SEQUENCE_TYPE_MAX) ? pmd_constant_sequence_type[id].name : NULL;
}

const char* pmd_constant_lookup_timestamp_type(unsigned int id)
{
    return (id < PMD_TIMESTAMP_TYPE_MAX) ? pmd_constant_timestamp_type[id].name : NULL;
}

const char* pmd_constant_lookup_timestamp_type_xml(unsigned int id)
{
    return (id < PMD_TIMESTAMP_TYPE_MAX) ? pmd_constant_timestamp_type[id].xml_name : NULL;
}

const char* pmd_constant_lookup_device_name(unsigned short id)
{
    const char* name = NULL;
    int n;

    for (n = 0; n < PMD_DEVICE_TYPE_MAX; n++)
    {
        if (pmd_constant_device_type[n].id == id)
        {
            name = pmd_constant_device_type[n].name;
            break;
        }
        else if (pmd_constant_device_type[n].id > id)
        {
            break;
        }
    }

    return name;
}

const char* pmd_constant_lookup_device_logical_name(unsigned short id)
{
    const char* logical_name = NULL;
    int n;

    for (n = 0; n < PMD_DEVICE_TYPE_MAX; n++)
    {
        if (pmd_constant_device_type[n].id == id)
        {
            logical_name = pmd_constant_device_type[n].logical_name;
            break;
        }
        else if (pmd_constant_device_type[n].id > id)
        {
            break;
        }
    }

    return logical_name;
}

unsigned int pmd_constant_lookup_device_flags(unsigned short id)
{
    unsigned int flags = 0;
    int n;

    for (n = 0; n < PMD_DEVICE_TYPE_MAX; n++)
    {
        if (pmd_constant_device_type[n].id == id)
        {
            flags = pmd_constant_device_type[n].flags;
            break;
        }
        else if (pmd_constant_device_type[n].id > id)
        {
            break;
        }
    }

    return flags;
}

const char* pmd_constant_lookup_hw_reset_type(unsigned int id)
{
    return (id < PMD_HW_RESET_TYPE_MAX) ? pmd_constant_hw_reset_type[id].name : NULL;
}

const char* pmd_constant_lookup_os_error_code(unsigned int id)
{
    if (id < 2)
    {
        pmd_constant_os_error_code[id].name;
    }
    return (id-127 < PMD_OS_ERROR_CODE_MAX) ? pmd_constant_os_error_code[id-127].name : NULL;
}

const char* pmd_constant_lookup_os_task_state(unsigned int id)
{
    return (id < PMD_OS_TASK_STATE_MAX) ? pmd_constant_os_task_state[id].name : NULL;
}

const char* pmd_constant_lookup_os_hook(unsigned int id)
{
    return (id < PMD_OS_HOOK_MAX) ? pmd_constant_os_hook[id].name : NULL;
}

const char* pmd_constant_lookup_tracebox_object_id(unsigned int id)
{
    return (id < PMD_TRACEBOX_OBJECT_ID_MAX) ? pmd_constant_tracebox_object_id[id].name : NULL;
}

const char* pmd_constant_lookup_resource_type(unsigned int id)
{
    return (id < PMD_RESOURCE_TYPE_MAX) ? pmd_constant_resource_type[id].name : NULL;
}

/* Check if two PMD versions are compatible in the Tracing SDK */
unsigned int check_pmd_version_compatibility(unsigned int pmd_version_1, unsigned int pmd_version_2)
{
    unsigned int pmd_ver_new, pmd_ver_old;
    int cnt = 0;

    /* Versions compatible if equal */
    if (pmd_version_1 == pmd_version_2)
        return PMD_FILE_FORMAT_COMPATIBEL;

    /* Determine the newest / oldest version */
    if (pmd_version_1 > pmd_version_2)
    {
        pmd_ver_new = pmd_version_1;
        pmd_ver_old = pmd_version_2;
    }
    else
    {
        pmd_ver_new = pmd_version_2;
        pmd_ver_old = pmd_version_1;
    }

    /* Find newest version in compatibility table */
    cnt = 0;
    while (pmd_version_compability_table[cnt].version != 0 &&
           pmd_version_compability_table[cnt].version != pmd_ver_new)
      cnt++;

    /* Search for oldest version as long the versions remain compatible */
    while (pmd_version_compability_table[cnt].version != 0 &&
           pmd_version_compability_table[cnt].version != pmd_ver_old &&
           pmd_version_compability_table[cnt].compability == PMD_FILE_FORMAT_COMPATIBEL)
      cnt++;

    /* Determine if the versions are compatible */
    if (pmd_version_compability_table[cnt].version == pmd_ver_old)
        return PMD_FILE_FORMAT_COMPATIBEL;
    else
        return PMD_FILE_FORMAT_INCOMPATIBEL;
}

/* Convert a PMD file format version string to an unsigned int             */
/* The PMD file format version is stored in the XML header in a PMD file.  */
/* The version string is stored between the tags <FileFormat></FileFormat> */
/* This function converts the version string to a 4 bytes unsigned int     */
/* containg the version number. Eg. "5.01" -> 0x00050001                   */
unsigned int pmd_version_conversion(const char *fileformat)
{
    unsigned int major_ver = 0;
    unsigned int minor_ver = 0;

    sscanf(fileformat, "%u.%u", &major_ver, &minor_ver);
    return ((major_ver / 10) << 12)
         | ((major_ver % 10) <<  8)
         | ((minor_ver / 10) <<  4)
         |  (minor_ver % 10);
}

/* End of file output_pmd_constants.c */
