/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                os_trc_m.h
                ----------
                SW Include






Project:          autogen

%name:            os_trc_m.h %
%version:         23 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Wed May 26 15:16:57 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file defines the structure of all NOS traces
*/

/* Ensure correct use in autogen */
#if (!defined AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS || !defined AUTOGEN_TRACES_HAVE_FIXED_IDS)
 #define AUTOGEN_TRACE_GROUPS_HAVE_FIXED_IDS
 #define AUTOGEN_TRACES_HAVE_FIXED_IDS
 #include "isi_macros.h"
#endif

/* --------------------------------------------------------------------- */
/* NOS trace groups */
/* --------------------------------------------------------------------- */

#define OS_MONITOR_DYNAMIC_HOOKS           0x00
#define OS_MONITOR_STATUS_HOOKS            0x01
#define OS_MONITOR_RESOURCE_HOOKS          0x02
#define OS_MONITOR_BLOCK_HOOKS             0x03
#define OS_MONITOR_MSG_HOOKS               0x04
#define OS_MONITOR_TIMER_HOOKS             0x05
#define OS_MONITOR_SCHEDULING_HOOKS        0x06
#define OS_MONITOR_STARTUP_HOOKS           0x07
#define OS_MONITOR_INFO_HOOKS              0x08
#define OS_MONITOR_WARNING_HOOKS           0x09
#define OS_MONITOR_INTERRUPT_HOOKS         0x0A
#define OS_MONITOR_MISC_HOOKS              0x10 /* Should not be there at all... */

/* --------------------------------------------------------------------- */
/* NOS traces */
/* --------------------------------------------------------------------- */

#define HOOK_UNKNOWN                                 0

/* Assembly language hooks */
#define HOOK_IRQ_BEGIN                               1
#define HOOK_IRQ_END                                 2
#define HOOK_IRQ_INFO                                3
#define HOOK_IPC_DUMP                                4
/* FIQ hooks */
#define HOOK_FIQ_BEGIN                              0x08
#define HOOK_FIQ_END                                0x09
#define HOOK_FIQ_STACK_OVERFLOW                     0x0A

/* Error and info hooks */
#define HOOK_ERROR                                  16
#define HOOK_WARNING                                17
#define HOOK_INFO                                   18

/* Startup hooks */
#define HOOK_BLOCK_INIT                             19
#define HOOK_IDLE                                   20
#define HOOK_MSG_INIT                               21
#define HOOK_OS_INIT                                22
#define HOOK_REG_EV_MODE_START                      23
#define HOOK_RESOURCE_INIT                          24
#define HOOK_TASK_INIT                              25
#define HOOK_TIMER_INIT                             26

/* Scheduling hooks */
#define HOOK_SCHEDULE                               27
#define HOOK_START_TASK                             28
#define HOOK_TASK_CHANGE_PRIOR                      29
#define HOOK_TASK_LIST_INSERT                       30
#define HOOK_TASK_LIST_REMOVE                       31
#define HOOK_TASK_RESUME                            32
#define HOOK_TASK_SUSPEND                           33

/* Interrupt hooks */
#define HOOK_INTERRUPT_ENABLE                       34
#define HOOK_INTERRUPT_DISABLE                      35
#define HOOK_COND_INT_ENABLE                        36
#define HOOK_COND_INT_DISABLE                       37

/* Timer hooks */
#define HOOK_TIMERMSG_REMOVE                        38
#define HOOK_TIMER_EXPIRED                          39
#define HOOK_TIMER_LIST_INSERT                      40
#define HOOK_TIMER_READ                             41
#define HOOK_TIMER_START                            42
#define HOOK_TIMER_STOP                             43

/* Architecture specific timer hooks */
#define HOOK_READ_TIMER_INT                         44
#define HOOK_SET_TIMER_INT                          45

/* Timer interrupt hooks */
#define HOOK_OS_REG_EVENT_INT                       46
#define HOOK_OS_TIMER_INT                           47

/* Message hooks */
#define HOOK_FASTMSG_RECEIVE                        48
#define HOOK_FASTMSG_SELECT                         49
#define HOOK_FASTMSG_SEND_NO_WAIT                   50
#define HOOK_FASTMSG_SEND_WAIT                      51
#define HOOK_MSG_COUNT_READ                         52
#define HOOK_MSG_RECEIVE                            53
#define HOOK_MSG_SEND_NO_WAIT                       54
#define HOOK_MSG_SEND_WAIT                          55
#define HOOK_TIMERMSG_RECEIVE                       56
#define HOOK_WAIT_IN_FASTMSG_SEND_WAIT              57
#define HOOK_WAIT_IN_MSG_RECEIVE                    58
#define HOOK_WAIT_IN_MSG_SEND_WAIT                  59

/* Block hooks */
#define HOOK_BLOCK_ALLOC                            60
#define HOOK_BLOCK_ALLOC_NO_WAIT                    61
#define HOOK_BLOCK_COUNT_READ                       62
#define HOOK_BLOCK_DEALLOC                          63
#define HOOK_HEAP_ALLOC                             64
#define HOOK_HEAP_BLOCK_COUNT_READ                  65
#define HOOK_HEAP_DEALLOC                           66
#define HOOK_WAIT_IN_BLOCK_ALLOC                    67
#define HOOK_WAIT_IN_HEAP_ALLOC                     68

/* Resource hooks */
#define HOOK_RESOURCE_RESERVE                       69
#define HOOK_RESOURCE_RELEASE                       70
#define HOOK_WAIT_IN_RESOURCE_RESERVE               71

/* Run-time status collection hooks */
#define HOOK_BLOCK_ALLOC_ERROR_GET                  72
#define HOOK_BLOCK_ALLOC_STATUS_GET                 73
#define HOOK_MSGBUF_STATUS_GET                      74
#define HOOK_TASK_LOADING_TRACE                     75

/* Monitoring status hooks */
#define HOOK_MSGBUF_STATUS                          76
#define HOOK_POOL_STATUS                            77
#define HOOK_READY_LIST_STATUS                      78
#define HOOK_RESOURCE_STATUS                        79

/* Dynamic configuration hooks */
#define HOOK_TASK_ID_GET                            80
#define HOOK_TASK_DELETE                            81
#define HOOK_TASK_MODE_GET                          82
#define HOOK_TASK_CREATE                            83
#define HOOK_TIMER_ID_GET                           84
#define HOOK_TIMER_CREATE                           85
#define HOOK_TIMER_DELETE                           86

/* New scheduling hooks */
#define HOOK_TASK_STATUS_CHANGE                     87

/* Removed.
#define HOOK_REMOVED_88                             88
#define HOOK_REMOVED_89                             89
#define HOOK_REMOVED_90                             90
#define HOOK_REMOVED_91                             91
#define HOOK_REMOVED_92                             92
*/

/* New scheduling ID (NOTE: this one is used only as ERROR ID in asm) */
#define HOOK_TASK_SWITCH                            93

/* New dynamic configuration hooks */
#define HOOK_TASK_MODE_SET                          94

/* Architecture specific timer hooks */
#define HOOK_CURRENT_TIME_READ                      95

/* New block related hooks */
#define HOOK_BLOCK_DEBUG_ADDR_GET                   96
#define HOOK_HEAP_DEBUG_ADDR_GET                    97

/* More dynamic configuration hooks */
#define HOOK_TASK_NAME_GET                          98
#define HOOK_TIMER_NAME_GET                         99

/* Tracing related hooks */
#define HOOK_TRACE_GROUP_ENABLE                     100
#define HOOK_TRACE_GROUP_DISABLE                    101

/* Dynamic memory debugging callback feature monitoring */
#define HOOK_BLOCK_DEBUG_CALLBACK_REG               102
#define HOOK_BLOCK_DEBUG_CALLBACK_DEREG             103

/* Static allocation tracing */
#define HOOK_STATIC_BLOCK_INIT                      104
#define HOOK_STATIC_BLOCK_ALLOC                     105

/* Region handling hooks */
#define HOOK_REGION_CREATE                          106
#define HOOK_REGION_DELETE                          107
#define HOOK_REGION_ENTER                           108
#define HOOK_REGION_EXIT                            109
#define HOOK_WAIT_IN_REGION_ENTER                   110
#define HOOK_REGION_NAME_GET                        111
#define HOOK_REGION_ID_GET                          112

/* Auxiliary deallocator hooks */
#define HOOK_AUX_DEALLOCATOR_REG                    113
#define HOOK_AUX_DEALLOCATOR_DEREG                  114

/* Callback hooks */
#define HOOK_CALLBACK_INJECT                        115
#define HOOK_CALLBACK_EXECUTE                       116

/* Yet another scheduling related hook */
#define HOOK_TASK_OWN_PRIOR_READ                    117

/* Bunch of heap handling hooks */
#define HOOK_HEAP_ALLOC_NO_WAIT                     118
#define HOOK_COND_HEAP_ALLOC                        119
#define HOOK_HEAP_AREA_ADD                          120
#define HOOK_HEAP_INIT                              121
#define HOOK_SLOW_HEAP_ALLOC                        122
#define HOOK_SLOW_HEAP_ALLOC_NO_WAIT                123
#define HOOK_SLOW_HEAP_DEALLOC                      124
#define HOOK_WAIT_IN_SLOW_HEAP_ALLOC                125

/* Another current time hook */
#define HOOK_CURRENT_TIME_READ_MS                   126

/* Debugging related hooks */
#define HOOK_CALLER_DEPTH_SET                       127
#define HOOK_DEBUG_INIT                             128

/* Yield */
#define HOOK_YIELD_LIST_UPDATE                      129
#define HOOK_YIELD_LIST_CLEAR                       130
#define HOOK_YIELD                                  131

/* Heap hooks */
#define HOOK_HEAP_ALLOC_NO_WAIT_FROM                132
#define HOOK_HEAP_ALLOC_FROM                        133
#define HOOK_HEAP_CREATE                            134
#define HOOK_HEAP_TASK_LIST_SET                     135
#define HOOK_HEAP_DELETE                            136

#define HOOK_BLOCK_REALLOC                          137
#define HOOK_ALIGNED_BLOCK_ALLOC_NO_WAIT            138
#define HOOK_ALIGNED_BLOCK_ALLOC                    139
#define HOOK_WAIT_IN_ALIGNED_BLOCK_ALLOC            140
#define HOOK_MMU_PAGE_ALIGNED_HEAP_DEALLOC          141
#define HOOK_MMU_PAGE_ALIGNED_HEAP_INIT             142
#define HOOK_WAIT_IN_HEAP_ALLOC_FROM                143
#define HOOK_POOL_ALLOCATOR                         144
#define HOOK_POOL_DEALLOCATOR                       145
#define HOOK_POOL_ALLOC_FROM                        146
#define HOOK_POOL_ALLOC_NO_WAIT_FROM                147
#define HOOK_POOL_CREATE                            148
#define HOOK_WAIT_IN_POOL_ALLOC_FROM                149
#define HOOK_HEAP_ALLOCATOR                         150
#define HOOK_HEAP_DEALLOCATOR                       151
#define HOOK_TASK_TIME_SLICE_SET                    152
#define HOOK_TASK_TIME_SLICE_END                    153
#define HOOK_RESOURCE_RESERVE_TIMED                 154
#define HOOK_RESOURCE_CREATE                        155
#define HOOK_RESOURCE_DELETE                        156
#define HOOK_WAIT_IN_RESOURCE_RESERVE_TIMED         157
#define HOOK_RESOURCE_RESERVE_EXPIRED               158
#define HOOK_RESOURCE_ID_GET                        159
#define HOOK_RESOURCE_NAME_GET                      160
#define HOOK_TIMER_EXPIRATION_MODE_SET              161


/* Task names */
#define OS_TASK(name) \
    VALUE_CONST( name, #name, OS_TASK_NAME )

/* Timer names */
#define OS_TIMER(name) \
    VALUE_CONST(name, #name, OS_TIMER_NAME)

/* Resource names */
#define OS_RESOURCE(name) \
    VALUE_CONST(name, #name, OS_RESOURCE_NAME)

/* Block set names */
#define OS_BLOCK_SET(name) \
    VALUE_CONST(name, #name, OS_BLOCK_SET_NAME)

/* MCU function address */
#define OS_FUNC(name) \
    PROPERTY_VALUE(PROPERTY_PMD_NUMBER_SPECIAL_TYPE, PMD_NUMBER_SPECIAL_TYPE_MCU_FUNCTION_ADDR) \
    VALUE(32, BE, name, #name, HEX)

/* Callers */
#define OS_CALLERS \
    SEQ_OF_REF(callers, "Callers", OS_CALLERS_ENTRY, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)

PROPERTY_STRING(PROPERTY_HTML_FILENAME, "nos_traces.html")
RES_BEGIN(RESOURCE_TRC_OS, AUTOGEN_NO_RESOURCE_ID, NOS, "NOS Traces", "", FALSE)

    SEQ_BEGIN(OS_CALLERS_ENTRY, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_PMD_NUMBER_SPECIAL_TYPE, PMD_NUMBER_SPECIAL_TYPE_MCU_FUNCTION_ADDR)
        VALUE(32, BE, data, "Data", HEX)
    SEQ_END

    CONST_TBL_BEGIN(OS_TASK_LIST_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(OS_READY_LIST,     0x01, "")
        CONST_TBL_ENTRY(OS_WAIT_LIST,      0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OS_TIMER_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(OS_ORDINARY_TIMER,                  0x00, "")
        CONST_TBL_ENTRY(OS_MESSAGE_TIMER,                   0x01, "")
        CONST_TBL_ENTRY(OS_REG_EVENT_ORDINARY_TIMER,        0x02, "")
        CONST_TBL_ENTRY(OS_REG_EVENT_MESSAGE_TIMER,         0x03, "")
        CONST_TBL_ENTRY(OS_FREE_RUNNING_TIMER,              0x05, "")
        CONST_TBL_ENTRY(OS_REG_EVENT_FREE_RUNNING_TIMER,    0x07, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OS_TIMER_LIST_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(TIMER_LIST,              0x03, "")
        CONST_TBL_ENTRY(REG_EVENT_TIMER_LIST,    0x04, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OS_TIMER_REG_EVENT_MODE, 8, BE, "", "")
        CONST_TBL_ENTRY(OS_TIMER_EXPIRE_EARLY,          0x01, "")
        CONST_TBL_ENTRY(OS_TIMER_EXPIRE_LATE,           0x02, "")
        CONST_TBL_ENTRY(OS_TIMER_EXPIRE_EARLY_OR_LATE,  0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OS_PROFILE, 8, BE, "", "")
        CONST_TBL_ENTRY(USER,           0x01, "")
        CONST_TBL_ENTRY(SUPERVISOR,     0x02, "")
        CONST_TBL_ENTRY(UNKNOWN,        0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OS_RESOURCE_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(OS_COUNTING_SEMAPHORE,  0x00, "")
        CONST_TBL_ENTRY(OS_BINARY_SEMAPHORE,    0x01, "")
    CONST_TBL_END

    TRACE_GROUP_BEGIN(OS_MONITOR_INTERRUPT_HOOKS, "", ON)
        /* HOOK_IRQ_BEGIN */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output from an assembly language module "
            "os_uppa.asm when IRQ handler is launched")
        TRACE_BEGIN(HOOK_IRQ_BEGIN, "HOOK_IRQ_BEGIN")
        TRACE_END()

        /* HOOK_IRQ_END */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        TRACE_BEGIN(HOOK_IRQ_END, "HOOK_IRQ_END")
        TRACE_END()

        /* HOOK_IRQ_INFO */
        COMMENT(COMMENT_TEXT,
            "This trace prints the IRQ ID (done from HW drivers).")
        TRACE_BEGIN(HOOK_IRQ_INFO, "HOOK_IRQ_INFO")
            VALUE(32, BE, irq_id, "IRQ ID", DEC)
        TRACE_END()

        /* HOOK_INTERRUPT_ENABLE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_int_enable is called.")
        TRACE_BEGIN(HOOK_INTERRUPT_ENABLE, "HOOK_INTERRUPT_ENABLE")
        TRACE_END()

        /* HOOK_INTERRUPT_DISABLE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_int_disable is called.")
        TRACE_BEGIN(HOOK_INTERRUPT_DISABLE, "HOOK_INTERRUPT_DISABLE")
        TRACE_END()

        /* HOOK_COND_INT_ENABLE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_conditional_int_enable is called.")
        TRACE_BEGIN(HOOK_COND_INT_ENABLE, "HOOK_COND_INT_ENABLE")
        TRACE_END()

        /* HOOK_COND_INT_DISABLE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_conditional_int_disable is called.")
        TRACE_BEGIN(HOOK_COND_INT_DISABLE, "HOOK_COND_INT_DISABLE")
        TRACE_END()

        /* HOOK_OS_REG_EVENT_INT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output internally when a regular event interrupt "
            "occurs.")
        TRACE_BEGIN(HOOK_OS_REG_EVENT_INT, "HOOK_OS_REG_EVENT_INT")
        TRACE_END()

        /* HOOK_OS_TIMER_INT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output internally when a timer interrupt occurs.")
        TRACE_BEGIN(HOOK_OS_TIMER_INT, "HOOK_OS_TIMER_INT")
        TRACE_END()

        /* HOOK_FIQ_BEGIN */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output from an assembly language module "
            "os_fiqa.asm when FIQ handler is launched.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: because FIQ won't be blocked by OS interrupt disable/enable "
            "mechanism, FIQ hooks can't use normal OS channels ch 0 / ch 1.")
        TRACE_BEGIN(HOOK_FIQ_BEGIN, "HOOK_FIQ_BEGIN")
            VALUE(16, BE, IIDR1, "IIDR1", HEX)
            VALUE(16, BE, IIDR2, "IIDR2", HEX)
        TRACE_END()

        /* HOOK_FIQ_END */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        TRACE_BEGIN(HOOK_FIQ_END, "HOOK_FIQ_END")
        TRACE_END()

        /* HOOK_FIQ_STACK_OVERFLOW */
        TRACE_BEGIN(HOOK_FIQ_STACK_OVERFLOW, "HOOK_FIQ_STACK_OVERFLOW")
            SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_WARNING_HOOKS, "", ON)
        /* HOOK_WARNING */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message identifies a potential problem in SW.")
        COMMENT(COMMENT_PARAGRAPH,
            "The function ID (byte 2) identifies the function where problem "
            "occurred, it is the same value as the hook ID of that function.")
        TRACE_BEGIN(HOOK_WARNING, "HOOK_WARNING")
            OS_TASK(Task)
            VALUE_CONST(func, "Func", OS_HOOK_ID)
            VALUE_CONST(ostrich_hook_error, "Warning", OS_ERROR_CODE)
            VALUE(32, BE, p1, "p1", HEX)
            VALUE(32, BE, p2, "p2", HEX)
            VALUE(32, BE, p3, "p3", HEX)
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_INFO_HOOKS, "", ON)
        /* HOOK_INFO */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This is an informational message.")
        COMMENT(COMMENT_PARAGRAPH,
            "The function ID (byte 2) identifies the function that caused this "
            "message to be printed, it is the same value as the hook ID of that "
            "function.")
        TRACE_BEGIN(HOOK_INFO, "HOOK_INFO")
            OS_TASK(Task)
            VALUE_CONST(func, "Func", OS_HOOK_ID)
            VALUE_CONST(ostrich_hook_error, "Info", OS_ERROR_CODE)
            VALUE(32, BE, p1, "p1", HEX)
            VALUE(32, BE, p2, "p2", HEX)
            VALUE(32, BE, p3, "p3", HEX)
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_SCHEDULING_HOOKS, "", ON)
        /* HOOK_IDLE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_idle is entered.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: os_idle is typically only used in workstation environment.")
        TRACE_BEGIN(HOOK_IDLE, "HOOK_IDLE")
        TRACE_END()

        /* HOOK_MSG_INIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_msg_init is called (from os_init).")
        TRACE_BEGIN(HOOK_MSG_INIT, "HOOK_MSG_INIT")
        TRACE_END()

        /* HOOK_REG_EV_MODE_START */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_reg_event_mode_start is called.")
        TRACE_BEGIN(HOOK_REG_EV_MODE_START, "HOOK_REG_EV_MODE_START")
        TRACE_END()

        /* HOOK_BLOCK_INIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_block_init is called (from os_init).")
        TRACE_BEGIN(HOOK_BLOCK_INIT, "HOOK_BLOCK_INIT")
            VALUE(8, BE, pool, "Pool", HEX)
            VALUE(32, BE, descriptor, "Descriptor", HEX)
            VALUE(32, BE, begin, "Begin", HEX)
            VALUE(32, BE, end,   "End",   HEX)
        TRACE_END()

        /* HOOK_RESOURCE_INIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_resource_init is called (from os_init).")
        TRACE_BEGIN(HOOK_RESOURCE_INIT, "HOOK_RESOURCE_INIT")
        TRACE_END()

        /* HOOK_TIMER_INIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_timer_init is called (from os_init).")
        TRACE_BEGIN(HOOK_TIMER_INIT, "HOOK_TIMER_INIT")
        TRACE_END()

        /* HOOK_SCHEDULE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output from os_schedule immediately before the "
            "call to os_task_switch.")
        TRACE_BEGIN(HOOK_SCHEDULE, "HOOK_SCHEDULE")
            OS_TASK(Old)
            OS_TASK(New)
        TRACE_END()

        /* HOOK_START_TASK */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output from os_start_task.")
        COMMENT(COMMENT_PARAGRAPH,
            "This function is automatically called for each task when it is "
            "resumed. A call to os_start_task also enables interrupts.")
        TRACE_BEGIN(HOOK_START_TASK, "HOOK_START_TASK")
            OS_TASK(Task)
        TRACE_END()

        /* HOOK_TASK_CHANGE_PRIOR */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output from os_task_change_prior (when a task "
            "changes its own priority).")
        TRACE_BEGIN(HOOK_TASK_CHANGE_PRIOR, "HOOK_TASK_CHANGE_PRIOR")
            OS_TASK(Task)
            VALUE(16, BE, prior, "Priority", DEC)
        TRACE_END()

        /* HOOK_TASK_LIST_INSERT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task is inserted in a priority list. "
            "The list can be either the ready list or a wait list - different "
            "wait lists are not identified.")
        TRACE_BEGIN(HOOK_TASK_LIST_INSERT, "HOOK_TASK_LIST_INSERT")
            OS_TASK(Task)
            VALUE_CONST(list, "List", OS_TASK_LIST_TYPE)
            COMMENT(COMMENT_TEXT,
                "Shows the resulting position of the task in the list")
            VALUE(8, BE, index, "Index", DEC)
        TRACE_END()

        /* HOOK_TASK_LIST_REMOVE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task is removed from the head of a "
            "priority list. The list can be either the ready list or a wait "
            "list - different wait lists are not identified.")
        TRACE_BEGIN(HOOK_TASK_LIST_REMOVE, "HOOK_TASK_LIST_REMOVE")
            OS_TASK(Task)
            VALUE_CONST(list, "List", OS_TASK_LIST_TYPE)
        TRACE_END()

        /* HOOK_TASK_RESUME */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task is resumed.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: if task resumption is a no-operation (target task was already "
            "resumed), only a HOOK_INFO is output.")
        TRACE_BEGIN(HOOK_TASK_RESUME, "HOOK_TASK_RESUME")
            OS_TASK(Task)
            OS_TASK(Resumed)
        TRACE_END()

        /* HOOK_TASK_SUSPEND */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task is suspended.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: if task resumption is a no-operation (target task was "
            "already suspended), only a MONITOR_INFO_HOOK is output.")
        TRACE_BEGIN(HOOK_TASK_SUSPEND, "HOOK_TASK_SUSPEND")
            OS_TASK(Task)
            OS_TASK(Suspended)
        TRACE_END()

        /* HOOK_TASK_STATUS_CHANGE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when status of a task changes.")
        TRACE_BEGIN(HOOK_TASK_STATUS_CHANGE, "HOOK_TASK_STATUS_CHANGE")
            OS_TASK(Task)
            VALUE_CONST(task_status, "Status", OS_TASK_STATE)
        TRACE_END()

        /* HOOK_HEAP_CREATE */
        TRACE_BEGIN(HOOK_HEAP_CREATE, "HOOK_HEAP_CREATE")
            OS_TASK(Task)
            VALUE(32, BE, heap, "Heap", HEX)
            VALUE(32, BE, start_address, "Start_address", HEX)
            VALUE(32, BE, size, "size", DEC)
            VALUE(32, BE, fragment, "fragment", DEC)
            VALUE(16, BE, heap_id, "Heap ID", DEC)
        TRACE_END()

        /* HOOK_HEAP_DELETE */
        TRACE_BEGIN(HOOK_HEAP_DELETE, "HOOK_HEAP_DELETE")
            OS_TASK(Task)
            VALUE(32, BE, heap, "Heap", HEX)
            VALUE(16, BE, heap_id, "Heap ID", DEC)
        TRACE_END()

        /* HOOK_HEAP_INIT */
        COMMENT(COMMENT_PARAGRAPH,
            "This trace will be output when one of the OS heaps is initialized. "
            "Currently the reserved values for the heaps are 0 (regular OS heap) and "
            "1 (slow heap).")
        TRACE_BEGIN(HOOK_HEAP_INIT, "HOOK_HEAP_INIT")
            VALUE(32, BE, heap, "Heap", HEX)
        TRACE_END()

        /* HOOK_YIELD_LIST_UPDATE */
        COMMENT(COMMENT_TEXT,
            "Trace is output when the list of yielding tasks is updated")
        TRACE_BEGIN(HOOK_YIELD_LIST_UPDATE, "HOOK_YIELD_LIST_UPDATE")
        TRACE_END()

        /* HOOK_YIELD_LIST_CLEAR */
        COMMENT(COMMENT_TEXT,
            "Trace is output when the yield list is cleared")
        TRACE_BEGIN(HOOK_YIELD_LIST_CLEAR, "HOOK_YIELD_LIST_CLEAR")
        TRACE_END()

        /* HOOK_YIELD */
        COMMENT(COMMENT_TEXT,
            "Trace is output when a task yields")
        TRACE_BEGIN(HOOK_YIELD, "HOOK_YIELD")
            OS_TASK(Task)
#ifdef OS_TIMER_INTERVAL
            VALUE_EX(32, BE, max_time, "Max time", DEC, OS_TIMER_INTERVAL, 0.0, "ms")
#else
            VALUE_EX(32, BE, max_time, "Max time", DEC, 1.0, 0.0, "ticks")
#endif
        TRACE_END()

        /* HOOK_STATIC_BLOCK_INIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This hook is output when the static allocator structure is initialized "
            "with os_static_block_init.")
        TRACE_BEGIN(HOOK_STATIC_BLOCK_INIT, "HOOK_STATIC_BLOCK_INIT")
            OS_TASK(Task)
            VALUE(32, BE, begin, "Begin", HEX)
            VALUE(32, BE, end,   "End",   HEX)
        TRACE_END()

        /* HOOK_HEAP_AREA_ADD */
        COMMENT(COMMENT_PARAGRAPH,
            "This trace is output when a new heap area is added to the free list. "
            "Descriptor shows the heap structure where the area was added.")
        TRACE_BEGIN(HOOK_HEAP_AREA_ADD, "HOOK_HEAP_AREA_ADD")
            OS_TASK(Task)
            VALUE(32, BE, area, "Address", HEX)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(32, BE, descriptor, "Descriptor", HEX)
        TRACE_END()

        /* HOOK_CALLBACK_INJECT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This trace is output when a callback is injected (queued) to be "
            "executed in some task's context. This is used from interrupt "
            "handlers when they must be isolated in privileged SW and "
            "upper SW layers must be able to register their event handlers "
            "from non-privileged SW.")
        TRACE_BEGIN(HOOK_CALLBACK_INJECT, "HOOK_CALLBACK_INJECT")
            OS_TASK(Task)
            OS_TASK(Target)
            OS_FUNC(Func)
            VALUE(32, BE, p0, "p0", HEX)
            VALUE(32, BE, p1, "p1", HEX)
            VALUE(32, BE, p2, "p2", HEX)
            VALUE(32, BE, p3, "p3", HEX)
        TRACE_END()

        /* HOOK_CALLBACK_EXECUTE */
        TRACE_BEGIN(HOOK_CALLBACK_EXECUTE, "HOOK_CALLBACK_EXECUTE")
            OS_TASK(Task)
            OS_FUNC(Func)
            VALUE(32, BE, p0, "p0", HEX)
            VALUE(32, BE, p1, "p1", HEX)
            VALUE(32, BE, p2, "p2", HEX)
            VALUE(32, BE, p3, "p3", HEX)
        TRACE_END()

        /* HOOK_TASK_OWN_PRIOR_READ */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Trace is output when a task reads its own priority with function "
            "os_task_own_prior_read.")
        TRACE_BEGIN(HOOK_TASK_OWN_PRIOR_READ, "HOOK_TASK_OWN_PRIOR_READ")
            OS_TASK(Task)
            VALUE(16, BE, own_prior, "Own priority", DEC)
        TRACE_END()

        /* HOOK_TASK_TIME_SLICE_SET */
        COMMENT(COMMENT_PARAGRAPH, "OS function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Trace is output when a task set time slice value to given target task. ")
        TRACE_BEGIN(HOOK_TASK_TIME_SLICE_SET, "HOOK_TASK_TIME_SLICE_SET")
            OS_TASK(Task)
            OS_TASK(Target_task_ID)
            VALUE(32, BE, old_slice_value, "Old slice value", DEC)
            VALUE(32, BE, new_slice_value, "New slice value", DEC)
        TRACE_END()

        /* HOOK_TASK_TIME_SLICE_END */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Trace is output when a task has exceed its time slice window. ")
        TRACE_BEGIN(HOOK_TASK_TIME_SLICE_END, "HOOK_TASK_TIME_SLICE_END")
            OS_TASK(Task)
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_TIMER_HOOKS, "", ON)
        /* HOOK_TIMERMSG_REMOVE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_timermsg_remove is called "
            "(internally from os_timer_start/stop/read) and as a result a timer "
            "message is removed from a task's mailbox (meaning that a timer had "
            "expired but the target task had not yet received the message).")
        TRACE_BEGIN(HOOK_TIMERMSG_REMOVE, "HOOK_TIMERMSG_REMOVE")
            OS_TIMER(Timer)
            VALUE(16, BE, Target, "Target", HEX)
        TRACE_END()

        /* HOOK_TIMER_EXPIRED */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a timer expires and os_timermsg_send "
            "is called internally from OS timer interrupt handler.")
        TRACE_BEGIN(HOOK_TIMER_EXPIRED, "HOOK_TIMER_EXPIRED")
            OS_TIMER(Timer)
            VALUE_CONST(type, "Type", OS_TIMER_TYPE)
            COMMENT(COMMENT_TEXT,
                "NOTE: If type is ORDINARY_TIMER, task ID is 0xFFFFE (UNKNOWN_TASK).")
            OS_TASK(Task)
        TRACE_END()

        /* HOOK_TIMER_LIST_INSERT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a timer is inserted into list of "
            "active timers (timer list or regular event timer list).")
        TRACE_BEGIN(HOOK_TIMER_LIST_INSERT, "HOOK_TIMER_LIST_INSERT")
            OS_TIMER(Timer)
            VALUE_CONST(list, "List", OS_TIMER_LIST_TYPE)
            VALUE(8, BE, index, "Index", HEX)
        TRACE_END()

        /* HOOK_TIMER_READ */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_timer_read is called. Remaining "
            "number of ticks is shown.")
        TRACE_BEGIN(HOOK_TIMER_READ, "HOOK_TIMER_READ")
            OS_TASK(Task)
            OS_TIMER(Timer)
            VALUE(32, BE, ticks, "Ticks", DEC)
        TRACE_END()

        /* HOOK_TIMER_START */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_timer_start is called.")
        TRACE_BEGIN(HOOK_TIMER_START, "HOOK_TIMER_START")
            OS_TASK(Task)
            OS_TIMER(Timer)
            VALUE(32, BE, ticks, "Ticks", DEC)
        TRACE_END()

        /* HOOK_TIMER_STOP */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_timer_read is called. Remaining "
            "number of ticks is shown.")
        TRACE_BEGIN(HOOK_TIMER_STOP, "HOOK_TIMER_STOP")
            OS_TASK(Task)
            OS_TIMER(Timer)
            VALUE(32, BE, ticks, "Ticks", DEC)
        TRACE_END()

        /* HOOK_READ_TIMER_INT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_read_timer_int function is called "
            "internally to synchronize the list of active timers with the "
            "hardware timer.")
        TRACE_BEGIN(HOOK_READ_TIMER_INT, "HOOK_READ_TIMER_INT")
            COMMENT(COMMENT_TEXT,
                "Address of the delay (delta) element in the timer structure.")
            VALUE(32, BE, target, "Target", HEX)
            COMMENT(COMMENT_TEXT,
                "Value of the delay element before the function call")
            VALUE(32, BE, old_delta, "old delta", HEX)
            COMMENT(COMMENT_TEXT,
                "Resulting value")
            VALUE(32, BE, new_delta, "New delta", HEX)
        TRACE_END()

        /* HOOK_SET_TIMER_INT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_set_timer_int function is called "
            "internally to start the hardware timer.")
        TRACE_BEGIN(HOOK_SET_TIMER_INT, "HOOK_SET_TIMER_INT")
            COMMENT(COMMENT_TEXT,
                "The value written to ASIC OS timer length register")
            VALUE(32, BE, trigger, "Trigger", HEX)
            COMMENT(COMMENT_TEXT,
            "Current prescaler counter value")
            VALUE(16, BE, prescaler, "Prescaler count", HEX)
        TRACE_END()

        /* HOOK_CURRENT_TIME_READ */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when current time is requested with function "
            "os_current_time_read. current_time is either in ticks or in milliseconds, "
            "depending on OS configuration flag OS_CURRENT_TIME_IN_MS.")
        TRACE_BEGIN(HOOK_CURRENT_TIME_READ, "HOOK_CURRENT_TIME_READ")
            OS_TASK(Task)
#if defined OS_TIMER_INTERVAL
            VALUE_EX(32, BE, os_time, "Current time", DEC, OS_TIMER_INTERVAL, 0.0, "ms")
#else
            VALUE(32, BE, os_time, "Current time", DEC)
#endif
        TRACE_END()

        /* HOOK_CURRENT_TIME_READ_MS */
        TRACE_BEGIN(HOOK_CURRENT_TIME_READ_MS, "HOOK_CURRENT_TIME_READ_MS")
            OS_TASK(Task)
            VALUE_EX(32, BE, current_time, "Current time", DEC, 1.0, 0.0, "ms")
        TRACE_END()

        /* HOOK_TIMER_EXPIRATION_MODE_SET */
        TRACE_BEGIN(HOOK_TIMER_EXPIRATION_MODE_SET, "HOOK_TIMER_EXPIRATION_MODE_SET")
            OS_TASK(Task)
            OS_TIMER(Timer)
            VALUE_CONST(Mode, "Mode", OS_TIMER_REG_EVENT_MODE)
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_MSG_HOOKS, "", ON)
        /* HOOK_FASTMSG_RECEIVE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when function os_msg_receive returns a fast "
            "message.")
        TRACE_BEGIN(HOOK_FASTMSG_RECEIVE, "HOOK_FASTMSG_RECEIVE")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            COMMENT(COMMENT_PARAGRAPH,
                "First four bytes of message contents.")
            COMMENT(COMMENT_PARAGRAPH,
                "NOTE: if the pointer points outside of RAM or FLASH, the value of "
                "is unpredictable.")
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

        /* HOOK_FASTMSG_SELECT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_fastmsg_select is called.")
        TRACE_BEGIN(HOOK_FASTMSG_SELECT, "HOOK_FASTMSG_SELECT")
            OS_TASK(Task)
        TRACE_END()

        /* HOOK_FASTMSG_SEND_NO_WAIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_fastmsg_send_no_wait is called "
            "(note: os_fastmsg_send is a macro that is defined as "
            "os_fastmsg_send_no_wait) and the message sending succeeds. ")
        COMMENT(COMMENT_PARAGRAPH,
            "If the fast message mailbox of the receiving task is full, "
            "HOOK_WARNING is output.")
        TRACE_BEGIN(HOOK_FASTMSG_SEND_NO_WAIT, "HOOK_FASTMSG_SEND_NO_WAIT")
            OS_TASK(Sender)
            OS_TASK(Receiver)
            VALUE(32, BE, ptr, "Ptr", HEX)
            COMMENT(COMMENT_PARAGRAPH,
                "First four bytes of message contents.")
            COMMENT(COMMENT_PARAGRAPH,
                "NOTE: if the pointer points outside of RAM or FLASH, the value of "
                "is unpredictable.")
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

        /* HOOK_FASTMSG_SEND_WAIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_fastmsg_send_wait is called and the "
            "message sending succeeds.")
        COMMENT(COMMENT_PARAGRAPH,
            "If the fast message mailbox of the receiving task is full, the "
            "calling task is set to wait and HOOK_WAIT_IN_FASTMSG_SEND_WAIT is output.")
        TRACE_BEGIN(HOOK_FASTMSG_SEND_WAIT, "HOOK_FASTMSG_SEND_WAIT")
            OS_TASK(Sender)
            OS_TASK(Receiver)
            VALUE(32, BE, ptr, "Ptr", HEX)
            COMMENT(COMMENT_PARAGRAPH,
                "First four bytes of message contents.")
            COMMENT(COMMENT_PARAGRAPH,
                "NOTE: if the pointer points outside of RAM or FLASH, the value of "
                "is unpredictable.")
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

        /* HOOK_MSG_COUNT_READ */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_msg_count_read is called.")
        TRACE_BEGIN(HOOK_MSG_COUNT_READ, "HOOK_MSG_COUNT_READ")
            OS_TASK(Task)
            VALUE(16, BE, msg_count, "Count", DEC)
        TRACE_END()

        /* HOOK_MSG_RECEIVE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task returns from function "
            "os_msg_receive with a normal message.")
        TRACE_BEGIN(HOOK_MSG_RECEIVE, "HOOK_MSG_RECEIVE")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            COMMENT(COMMENT_PARAGRAPH,
                "First four bytes of message contents.")
            COMMENT(COMMENT_PARAGRAPH,
                "NOTE: if the pointer points outside of RAM or FLASH, the value of "
                "is unpredictable.")
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

        /* HOOK_MSG_SEND_NO_WAIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_msg_send_no_wait is called (note: "
            "os_msg_send is a macro that is defined as os_msg_send_no_wait) and "
            "the message sending succeeds.")
        COMMENT(COMMENT_PARAGRAPH,
            "If the message mailbox of the receiving task is full, "
            "HOOK_WARNING is output.")
        TRACE_BEGIN(HOOK_MSG_SEND_NO_WAIT, "HOOK_MSG_SEND_NO_WAIT")
            OS_TASK(Sender)
            OS_TASK(Receiver)
            VALUE(32, BE, ptr, "Ptr", HEX)
            COMMENT(COMMENT_PARAGRAPH,
                "First four bytes of message contents.")
            COMMENT(COMMENT_PARAGRAPH,
                "NOTE: if the pointer points outside of RAM or FLASH, the value of "
                "is unpredictable.")
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

        /* HOOK_MSG_SEND_WAIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_msg_send_wait is called and the "
            "message sending succeeds.")
        COMMENT(COMMENT_PARAGRAPH,
            "If mailbox of the receiving task is full, calling task is set to "
            "wait and HOOK_WAIT_IN_MSG_SEND_WAIT_HOOK is output.")
        TRACE_BEGIN(HOOK_MSG_SEND_WAIT, "HOOK_MSG_SEND_WAIT")
            OS_TASK(Sender)
            OS_TASK(Receiver)
            VALUE(32, BE, ptr, "Ptr", HEX)
            COMMENT(COMMENT_PARAGRAPH,
                "First four bytes of message contents.")
            COMMENT(COMMENT_PARAGRAPH,
                "NOTE: if the pointer points outside of RAM or FLASH, the value of "
                "is unpredictable.")
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

        /* HOOK_TIMERMSG_RECEIVE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a function os_msg_receive returns a "
            "timer message.")
        TRACE_BEGIN(HOOK_TIMERMSG_RECEIVE, "HOOK_TIMERMSG_RECEIVE")
            OS_TASK(Task)
            OS_TIMER(Timer)
            VALUE(32, BE, ptr, "Ptr", HEX)
            COMMENT(COMMENT_PARAGRAPH,
                "First four bytes of message contents.")
            COMMENT(COMMENT_PARAGRAPH,
                "NOTE: if the pointer points outside of RAM or FLASH, the value of "
                "is unpredictable.")
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

        /* HOOK_WAIT_IN_FASTMSG_SEND_WAIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task tries to send a fast message "
            "but fast message mailbox of the receiving task is full.")
        TRACE_BEGIN(HOOK_WAIT_IN_FASTMSG_SEND_WAIT, "HOOK_WAIT_IN_FASTMSG_SEND_WAIT")
            OS_TASK(Sender)
            OS_TASK(Receiver)
            COMMENT(COMMENT_PARAGRAPH,
                "First four bytes of message contents.")
            COMMENT(COMMENT_PARAGRAPH,
                "NOTE: if the pointer points outside of RAM or FLASH, the value of "
                "is unpredictable.")
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

        /* HOOK_WAIT_IN_MSG_RECEIVE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task calls os_msg_receive but there "
            "aren't any messages in the mailbox.")
        TRACE_BEGIN(HOOK_WAIT_IN_MSG_RECEIVE, "HOOK_WAIT_IN_MSG_RECEIVE")
            OS_TASK(Task)
        TRACE_END()

        /* HOOK_WAIT_IN_MSG_SEND_WAIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task tries to send a message with "
            "os_msg_send_wait but mailbox of the receiving task is full.")
        TRACE_BEGIN(HOOK_WAIT_IN_MSG_SEND_WAIT, "HOOK_WAIT_IN_MSG_SEND_WAIT")
            OS_TASK(Sender)
            OS_TASK(Receiver)
            VALUE(32, BE, msg, "Msg", HEX)
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_BLOCK_HOOKS, "", ON)
        /* HOOK_BLOCK_ALLOC */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_block_alloc returns with a block "
            "pointer.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: if there isn't enough dynamic memory available, the calling "
            "task is set to wait and HOOK_WAIT_IN_BLOCK_ALLOC is output.")
        TRACE_BEGIN(HOOK_BLOCK_ALLOC, "HOOK_BLOCK_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(16, BE, size, "Size", DEC)
            OS_BLOCK_SET(Set)
            OS_CALLERS
        TRACE_END()

        /* HOOK_HEAP_ALLOC */
        COMMENT(COMMENT_PARAGRAPH, "OS interface/internal function hook.")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_heap_block_alloc returns with a "
            "block pointer.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: If both block and heap based dynamic memory handlers are "
            "selected in configuration, os_heap_block_alloc is called "
            "internally from os_block_alloc.")
        COMMENT(COMMENT_PARAGRAPH,
            "If only heap based dynamic memory handler is selected, "
            "os_block_alloc is a macro that is defined to "
            "os_heap_block_alloc.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: if there isn't enough dynamic memory available, the calling "
            "task is set to wait and HOOK_WAIT_IN_BLOCK_ALLO is output.")
        TRACE_BEGIN(HOOK_HEAP_ALLOC, "HOOK_HEAP_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_BLOCK_ALLOC_NO_WAIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_block_alloc_no_wait returns with a "
            "block pointer.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: if there isn't enough dynamic memory available, "
            "HOOK_WARNING is output.")
        TRACE_BEGIN(HOOK_BLOCK_ALLOC_NO_WAIT, "HOOK_BLOCK_ALLOC_NO_WAIT")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(16, BE, size, "Size", DEC)
            OS_BLOCK_SET(Set)
            OS_CALLERS
        TRACE_END()

        /* HOOK_BLOCK_DEALLOC */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a dynamic memory block is returned to "
            "pool.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: If the pointer doesn't point to pool, HOOK_INFO is output.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: If both block and heap based dynamic memory systems are "
            "selected and the pointer doesn't point to pool, "
            "os_heap_dealloc is called.")
        TRACE_BEGIN(HOOK_BLOCK_DEALLOC, "HOOK_BLOCK_DEALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            OS_CALLERS
        TRACE_END()

        /* HOOK_HEAP_DEALLOC */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a dynamic memory block is returned to "
            "heap.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: If only heap based dynamic memory system is "
            "selected, os_block_dealloc is defined to os_heap_dealloc.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: if the pointer doesn't point to heap, HOOK_INFO is output.")
        TRACE_BEGIN(HOOK_HEAP_DEALLOC, "HOOK_HEAP_DEALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            OS_CALLERS
        TRACE_END()

        /* HOOK_BLOCK_COUNT_READ */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_block_count_read is called.")
        TRACE_BEGIN(HOOK_BLOCK_COUNT_READ, "HOOK_BLOCK_COUNT_READ")
            OS_TASK(Task)
            VALUE(32, BE, request, "Request", HEX)
            VALUE(32, BE, blocks, "Blocks", DEC)
        TRACE_END()

        /* HOOK_HEAP_BLOCK_COUNT_READ */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_heap_count_read is called.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: if only heap based dynamic memory handler is selected, "
            "os_block_count_read is a macro that is defined to "
            "os_heap_count_read.")
        TRACE_BEGIN(HOOK_HEAP_BLOCK_COUNT_READ, "HOOK_HEAP_BLOCK_COUNT_READ")
            OS_TASK(Task)
            VALUE(32, BE, request, "Request", HEX)
            VALUE(32, BE, blocks, "Blocks", DEC)
        TRACE_END()

        /* HOOK_WAIT_IN_BLOCK_ALLOC */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task calls os_block_alloc but there "
            "isn't any blocks large enough for the request.")
        TRACE_BEGIN(HOOK_WAIT_IN_BLOCK_ALLOC, "HOOK_WAIT_IN_BLOCK_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, size, "Size", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_WAIT_IN_HEAP_ALLOC */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task calls os_heap_alloc but there "
            "isn't any blocks large enough for the request.")
        TRACE_BEGIN(HOOK_WAIT_IN_HEAP_ALLOC, "HOOK_WAIT_IN_HEAP_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, size, "Size", DEC)
            OS_CALLERS
        TRACE_END()

        /*  HOOK_WAIT_IN_POOL_ALLOC_FROM */
         TRACE_BEGIN(HOOK_WAIT_IN_POOL_ALLOC_FROM, "HOOK_WAIT_IN_POOL_ALLOC_FROM")
            OS_TASK(Task)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(8, BE, pool, "Pool", HEX)
            OS_CALLERS
        TRACE_END()

        /* HOOK_BLOCK_DEBUG_ADDR_GET */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when block debug address is requested from OS. "
            "bl_ptr is the block pointer given as argument. ptr points to the  "
            "user debug data area, the first four bytes are output as data bytes 6-9.")
        TRACE_BEGIN(HOOK_BLOCK_DEBUG_ADDR_GET, "HOOK_BLOCK_DEBUG_ADDR_GET")
            OS_TASK(Task)
            VALUE(32, BE, bl_ptr, "Block Ptr", HEX)
            VALUE(32, BE, ptr, "Ptr", HEX)
        TRACE_END()

        /* HOOK_HEAP_DEBUG_ADDR_GET */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This hook is similar to HOOK_BLOCK_DEBUG_ADDR_GET.")
        TRACE_BEGIN(HOOK_HEAP_DEBUG_ADDR_GET, "HOOK_HEAP_DEBUG_ADDR_GET")
            OS_TASK(Task)
            VALUE(32, BE, bl_ptr, "Block Ptr", HEX)
            VALUE(32, BE, ptr, "Ptr", HEX)
        TRACE_END()

        /* HOOK_OS_BLOCK_REALLOC */
        TRACE_BEGIN(HOOK_BLOCK_REALLOC, "HOOK_BLOCK_REALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(32, BE, new_ptr, "New ptr", HEX)
            OS_CALLERS
        TRACE_END()

        /* HOOK_BLOCK_DEBUG_CALLBACK_REG */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when someone registers a debugging callback for dynamic memory "
            "alloc/dealloc functions with os_block_debug_callback_register.")
        TRACE_BEGIN(HOOK_BLOCK_DEBUG_CALLBACK_REG, "HOOK_BLOCK_DEBUG_CALLBACK_REG")
            OS_TASK(Task)
            OS_FUNC(Func)
        TRACE_END()

        /* HOOK_BLOCK_DEBUG_CALLBACK_DEREG */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when the dynamic memory debugging callback function is deregistered "
            "with os_block_debug_callback_deregister.")
        TRACE_BEGIN(HOOK_BLOCK_DEBUG_CALLBACK_DEREG, "HOOK_BLOCK_DEBUG_CALLBACK_DEREG")
            OS_TASK(Task)
        TRACE_END()

       /* HOOK_HEAP_ALLOC_NO_WAIT_FROM */
        TRACE_BEGIN(HOOK_HEAP_ALLOC_NO_WAIT_FROM, "HOOK_HEAP_ALLOC_NO_WAIT_FROM")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(16, BE, heap_id, "Heap ID", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_HEAP_ALLOC_FROM */
        TRACE_BEGIN(HOOK_HEAP_ALLOC_FROM, "HOOK_HEAP_ALLOC_FROM")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(16, BE, heap_id, "Heap ID", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_STATIC_BLOCK_ALLOC */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when a static block allocation is done via os_static_block_alloc.")
        TRACE_BEGIN(HOOK_STATIC_BLOCK_ALLOC, "HOOK_STATIC_BLOCK_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, req, "Request", HEX)
            VALUE(32, BE, siz, "Size", DEC)
        TRACE_END()

        /* HOOK_HEAP_ALLOC_NO_WAIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This trace is output when a block is allocated with function "
            "os_heap_block_alloc_no_wait.")
        TRACE_BEGIN(HOOK_HEAP_ALLOC_NO_WAIT, "HOOK_HEAP_ALLOC_NO_WAIT")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_COND_HEAP_ALLOC */
        COMMENT(COMMENT_PARAGRAPH,
            "This trace is output when a block is conditionally allocated with function "
            "os_cond_heap_block_alloc.")
        TRACE_BEGIN(HOOK_COND_HEAP_ALLOC, "HOOK_COND_HEAP_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(32, BE, low_water_mark, "Low water mark", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_SLOW_HEAP_ALLOC */
        COMMENT(COMMENT_PARAGRAPH,
            "This trace is output when a block is allocated from the slow heap.")
        TRACE_BEGIN(HOOK_SLOW_HEAP_ALLOC, "HOOK_SLOW_HEAP_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_SLOW_HEAP_ALLOC_NO_WAIT */
        COMMENT(COMMENT_PARAGRAPH,
            "This trace is output when a block is allocated from the slow heap "
            "with os_slow_heap_block_alloc_no_wait.")
        TRACE_BEGIN(HOOK_SLOW_HEAP_ALLOC_NO_WAIT, "HOOK_SLOW_HEAP_ALLOC_NO_WAIT")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_SLOW_HEAP_DEALLOC */
        COMMENT(COMMENT_PARAGRAPH,
            "This trace is output when a block is deallocated back to the slow heap.")
        TRACE_BEGIN(HOOK_SLOW_HEAP_DEALLOC, "HOOK_SLOW_HEAP_DEALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            OS_CALLERS
        TRACE_END()

        /* HOOK_WAIT_IN_SLOW_HEAP_ALLOC */
        TRACE_BEGIN(HOOK_WAIT_IN_SLOW_HEAP_ALLOC, "HOOK_WAIT_IN_SLOW_HEAP_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, size, "Size", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_AUX_DEALLOCATOR_REG */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when an auxiliary deallocator area & function is registered "
            "with os_aux_deallocator_register.")
        TRACE_BEGIN(HOOK_AUX_DEALLOCATOR_REG, "HOOK_AUX_DEALLOCATOR_REG")
            OS_TASK(Task)
            VALUE(32, BE, araa_lo, "Begin", HEX)
            VALUE(32, BE, area_hi, "End", HEX)
            OS_FUNC(Func)
        TRACE_END()

        /* HOOK_AUX_DEALLOCATOR_DEREG */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when an auxiliary deallocator area & function is deregistered "
            "with os_aux_deallocator_deregister.")
        TRACE_BEGIN(HOOK_AUX_DEALLOCATOR_DEREG, "HOOK_AUX_DEALLOCATOR_DEREG")
            OS_TASK(Task)
        TRACE_END()

        /* HOOK_POOL_ALLOC_FROM */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_pool_alloc_from returns with a block "
            "pointer.")
        COMMENT(COMMENT_PARAGRAPH,
            "NOTE: if there isn't enough dynamic memory available, the calling "
            "task is set to wait.")
        TRACE_BEGIN(HOOK_POOL_ALLOC_FROM, "HOOK_POOL_ALLOC_FROM")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(16, BE, size, "Size", DEC)
            VALUE(8, BE, set_no, "Set", DEC)
            VALUE(8, BE, pool, "Pool", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_POOL_ALLOC_NO_WAIT_FROM */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_pool_alloc_no_wait_from returns with a block "
            "pointer.")
        TRACE_BEGIN(HOOK_POOL_ALLOC_NO_WAIT_FROM, "HOOK_POOL_ALLOC_NO_WAIT_FROM")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(16, BE, size, "Size", DEC)
            VALUE(8, BE, set_no, "Set", DEC)
            VALUE(8, BE, pool, "Pool", DEC)
            OS_CALLERS
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_RESOURCE_HOOKS, "", ON)

        /* HOOK_RESOURCE_CREATE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_resource_create is called.")
        TRACE_BEGIN(HOOK_RESOURCE_CREATE, "HOOK_RESOURCE_CREATE")
            OS_TASK(Task)
            STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, name, "Name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
            OS_RESOURCE(Res)
            VALUE_CONST(res_type, "Type", OS_RESOURCE_TYPE)
            VALUE(8, BE, init_value, "Init value", DEC)
        TRACE_END()

        /* HOOK_RESOURCE_DELETE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_resource_delete is called.")
        TRACE_BEGIN(HOOK_RESOURCE_DELETE, "HOOK_RESOURCE_DELETE")
            OS_TASK(Task)
            OS_RESOURCE(Res)
        TRACE_END()

        /* HOOK_RESOURCE_RESERVE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a resource is reserved.")
        TRACE_BEGIN(HOOK_RESOURCE_RESERVE, "HOOK_RESOURCE_RESERVE")
            OS_TASK(Task)
            OS_RESOURCE(Res)
        TRACE_END()

        /* HOOK_RESOURCE_RESERVE_TIMED */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a resource is reserved with given timeout value.")
        TRACE_BEGIN(HOOK_RESOURCE_RESERVE_TIMED, "HOOK_RESOURCE_RESERVE_TIMED")
            OS_TASK(Task)
            OS_RESOURCE(Res)
            VALUE(32, BE, ticks, "Ticks", DEC)
        TRACE_END()

        /* HOOK_WAIT_IN_RESOURCE_RESERVE_TIMED */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task tries to reserve a reserved resource with timeout value.")
        TRACE_BEGIN(HOOK_WAIT_IN_RESOURCE_RESERVE_TIMED, "HOOK_WAIT_IN_RESOURCE_RESERVE_TIMED")
            OS_TASK(Task)
            OS_RESOURCE(Res)
            OS_TASK(Owner)
            VALUE(32, BE, ticks, "Ticks", DEC)
        TRACE_END()

        /* HOOK_RESOURCE_RESERVE_TIMEOUT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a resource reservation is expired by timeout value.")
        TRACE_BEGIN(HOOK_RESOURCE_RESERVE_EXPIRED, "HOOK_RESOURCE_RESERVE_EXPIRED")
            OS_TASK(Task)
            OS_RESOURCE(Res)
        TRACE_END()

        /* HOOK_RESOURCE_RELEASE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a resource is released.")
        TRACE_BEGIN(HOOK_RESOURCE_RELEASE, "HOOK_RESOURCE_RELEASE")
            OS_TASK(Task)
            OS_RESOURCE(Res)
        TRACE_END()

        /* HOOK_WAIT_IN_RESOURCE_RESERVE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when a task tries to reserve a reserved "
            "resource.")
        TRACE_BEGIN(HOOK_WAIT_IN_RESOURCE_RESERVE, "HOOK_WAIT_IN_RESOURCE_RESERVE")
            OS_TASK(Task)
            OS_RESOURCE(Res)
            OS_TASK(Owner)
        TRACE_END()

        /* HOOK_BLOCK_ALLOC_ERROR_GET */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_block_alloc_error_get is called.")
        TRACE_BEGIN(HOOK_BLOCK_ALLOC_ERROR_GET, "HOOK_BLOCK_ALLOC_ERROR_GET")
            OS_TASK(Task)
        TRACE_END()

        /* HOOK_BLOCK_ALLOC_STATUS_GET */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_block_alloc_status_get is called.")
        TRACE_BEGIN(HOOK_BLOCK_ALLOC_STATUS_GET, "HOOK_BLOCK_ALLOC_STATUS_GET")
            OS_TASK(Task)
        TRACE_END()

        /* HOOK_MSGBUF_STATUS_GET */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_msgbuf_status_get is called.")
        TRACE_BEGIN(HOOK_MSGBUF_STATUS_GET, "HOOK_MSGBUF_STATUS_GET")
            OS_TASK(Task)
        TRACE_END()

        /* HOOK_TASK_LOADING_TRACE */
        TRACE_BEGIN(HOOK_TASK_LOADING_TRACE, "HOOK_TASK_LOADING_TRACE")
            SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
        TRACE_END()

        /* HOOK_REGION_CREATE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when os_region_create is used to create a region.")
        TRACE_BEGIN(HOOK_REGION_CREATE, "HOOK_REGION_CREATE")
            OS_TASK(Task)
            STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, name, "Name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
            VALUE(16, BE, region, "Region", HEX)
        TRACE_END()

        /* HOOK_REGION_DELETE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when a region is deleted with os_region_delete.")
        TRACE_BEGIN(HOOK_REGION_DELETE, "HOOK_REGION_DELETE")
            OS_TASK(Task)
            VALUE(16, BE, region, "Region", HEX)
        TRACE_END()

        /* HOOK_REGION_ENTER */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when a region is successfully entered with os_region_enter.")
        TRACE_BEGIN(HOOK_REGION_ENTER, "HOOK_REGION_ENTER")
            OS_TASK(Task)
            VALUE(16, BE, region, "Region", HEX)
            VALUE(16, BE, count, "Count", DEC)
        TRACE_END()

        /* HOOK_REGION_EXIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when a region is exit with os_region_exit.")
        TRACE_BEGIN(HOOK_REGION_EXIT, "HOOK_REGION_EXIT")
            OS_TASK(Task)
            VALUE(16, BE, region, "Region", HEX)
            VALUE(16, BE, count, "Count", DEC)
        TRACE_END()

        /* HOOK_WAIT_IN_REGION_ENTER */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "Output when os_region_enter blocks the caller.")
        TRACE_BEGIN(HOOK_WAIT_IN_REGION_ENTER, "HOOK_WAIT_IN_REGION_ENTER")
            OS_TASK(Task)
            VALUE(16, BE, region, "Region", HEX)
            OS_TASK(Owner)
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_STATUS_HOOKS, "", ON)
        /* HOOK_MSGBUF_STATUS */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is not related to any OS function call but it is output "
            "from application (e.g. idle task). The application e.g. calls macro "
            "MONITOR_ALL_STATUS_HOOKS which calls macro "
            "MONITOR_MSGBUF_STATUS_HOOK() which outputs mailbox allocation status "
            "data of one task per each call.")
        COMMENT(COMMENT_PARAGRAPH,
            "The information can be used by the OS monitor user interface to "
            "synchronize its own view of the mailbox allocation status.")
        TRACE_BEGIN(HOOK_MSGBUF_STATUS, "HOOK_MSGBUF_STATUS")
            OS_TASK(Task)
            VALUE(8, BE, buf_cur, "Buf cur", DEC)
            VALUE(8, BE, fastmsg_cur, "Fastmsg cur", DEC)
            VALUE(8, BE, msg_buf_peak, "Msg buf peak", DEC)
            VALUE(8, BE, fastm_buf_peak, "Fastmsg buf peak", DEC)
        TRACE_END()

        /* HOOK_POOL_STATUS */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is not related to any OS function call but it is output "
            "from application (e.g. idle task). The application e.g. calls macro "
            "MONITOR_ALL_STATUS_HOOKS which calls macro "
            "MONITOR_POOL_STATUS_HOOK() which outputs block set allocation status "
            "data of one task per each call.")
        COMMENT(COMMENT_PARAGRAPH,
            "The information can be used by the OS monitor user interface to "
            "synchronize its own view of the mailbox allocation status.")
        TRACE_BEGIN(HOOK_POOL_STATUS, "HOOK_POOL_STATUS")
            OS_BLOCK_SET(Set)
            VALUE(8, BE, block_rsrvd_cur, "Block rsrvd cur", DEC)
            VALUE(8, BE, block_rsrvd_peak, "Block rsrvd peak", DEC)
        TRACE_END()

        /* HOOK_READY_LIST_STATUS */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is not related to any OS function call but it is output "
            "from application (e.g. idle task). The application e.g. calls macro "
            "MONITOR_ALL_STATUS_HOOKS which calls macro "
            "MONITOR_READY_LIST_STATUS_HOOK() which outputs the list length.")
        TRACE_BEGIN(HOOK_READY_LIST_STATUS, "HOOK_READY_LIST_STATUS")
            COMMENT(COMMENT_TEXT,
                "Current ready list length")
            VALUE(8, BE, len, "Length", DEC)
        TRACE_END()

        /* HOOK_RESOURCE_STATUS */
        COMMENT(COMMENT_PARAGRAPH, "OS internal status hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is not related to any OS function call but it is output "
            "from application (e.g. idle task). The application e.g. calls macro "
            "MONITOR_ALL_STATUS_HOOKS() which calls macro "
            "MONITOR_RESOURCE_STATUS_HOOK() which outputs the resource status.")
        TRACE_BEGIN(HOOK_RESOURCE_STATUS, "HOOK_RESOURCE_STATUS")
            VALUE(16, BE, res_tbl, "Res tbl", DEC)
            OS_RESOURCE(Res)
        TRACE_END()

    TRACE_GROUP_END()

    TRACE_GROUP_BEGIN(OS_MONITOR_DYNAMIC_HOOKS, "", ON)
        /* HOOK_TASK_INIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_task_init is called (from os_init).")
        TRACE_BEGIN(HOOK_TASK_INIT, "HOOK_TASK_INIT")
        TRACE_END()

        /* HOOK_TASK_CREATE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_task_create is called.")
        TRACE_BEGIN(HOOK_TASK_CREATE, "HOOK_TASK_CREATE")
            OS_TASK(Task)
            STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, name, "Name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
            VALUE(8, BE, target_prior, "Target priority", DEC)
            VALUE(32, BE, target_address, "Target addr", HEX)
            VALUE(32, BE, stack_bottom, "Stack bottom", HEX)
            VALUE(32, BE, stack_size, "Stack size", DEC)
            VALUE(32, BE, mbox_size, "Mbox size", DEC)
            VALUE(32, BE, fastmbx_size, "Fastmbx size", DEC)
            VALUE(32, BE, callbackbuf_size, "Callback buf size", DEC)
            VALUE(16, BE, new_id, "New ID", HEX)
        TRACE_END()

        /* HOOK_TASK_DELETE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_task_delete is called.")
        TRACE_BEGIN(HOOK_TASK_DELETE, "HOOK_TASK_DELETE")
            OS_TASK(Task)
            VALUE(16, BE, target, "Target", HEX)
        TRACE_END()

        /* HOOK_TASK_ID_GET */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_task_id_get is called.")
        TRACE_BEGIN(HOOK_TASK_ID_GET, "HOOK_TASK_ID_GET")
            OS_TASK(Task)
            VALUE(16, BE, target, "Target", HEX)
            STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, name, "Name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
        TRACE_END()

        /* HOOK_TIMER_CREATE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_timer_create is called.")
        TRACE_BEGIN(HOOK_TIMER_CREATE, "HOOK_TIMER_CREATE")
            OS_TASK(Task)
            OS_TIMER(Timer)
            STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, name, "Name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
            OS_TASK(Target)
            VALUE_CONST(timer_type, "Type", OS_TIMER_TYPE)
        TRACE_END()

        /* HOOK_TIMER_DELETE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_timer_delete is called.")
        TRACE_BEGIN(HOOK_TIMER_DELETE, "HOOK_TIMER_DELETE")
            OS_TASK(Task)
            OS_TIMER(Timer)
        TRACE_END()

        /* HOOK_TIMER_ID_GET */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_timer_id_get is called.")
        TRACE_BEGIN(HOOK_TIMER_ID_GET, "HOOK_TIMER_ID_GET")
            OS_TASK(Task)
            OS_TIMER(Timer)
            STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, name, "Name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
        TRACE_END()

    TRACE_GROUP_END()

    PROPERTY(PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE)
    TRACE_GROUP_BEGIN(OS_MONITOR_MISC_HOOKS, "", ON)

        /* HOOK_TRACE_GROUP_ENABLE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This hook is output when the OS trace group configuration is dynamically "
            "changed with function os_monitor_trace_group_enable.")
        TRACE_BEGIN(HOOK_TRACE_GROUP_ENABLE, "HOOK_TRACE_GROUP_ENABLE")
            OS_TASK(Task)
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
            VALUE_CONST_IMP(osmo_group, "OS trace groups", MON_OS_TRACE_CONTROL_BITMAP, PN_MON)
#else
            COMMENT(COMMENT_PARAGRAPH, "For bit definitions, please see ")
            COMMENT_LINK(LINK_NOTE, "/14/", "", "")
            COMMENT(COMMENT_TEXT, " chapter 6.2 and 13.")
            VALUE(32, BE, osmo_group, "OS trace groups", HEX)
#endif
        TRACE_END()

        /* HOOK_TRACE_GROUP_DISABLE */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This hook is output when the OS trace group configuration is dynamically "
            "changed with function os_monitor_trace_group_disable.")
        TRACE_BEGIN(HOOK_TRACE_GROUP_DISABLE, "HOOK_TRACE_GROUP_DISABLE")
            OS_TASK(Task)
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
            VALUE_CONST_IMP(osmo_group, "OS trace groups", MON_OS_TRACE_CONTROL_BITMAP, PN_MON)
#else
            COMMENT(COMMENT_PARAGRAPH, "For bit definitions, please see ")
            COMMENT_LINK(LINK_NOTE, "/14/", "", "")
            COMMENT(COMMENT_TEXT, " chapter 6.2 and 13.")
            VALUE(32, BE, osmo_group, "OS trace groups", HEX)
#endif
        TRACE_END()

        /* HOOK_TASK_SWITCH */
        TRACE_BEGIN(HOOK_TASK_SWITCH, "HOOK_TASK_SWITCH")
        TRACE_END()

        /* HOOK_CALLER_DEPTH_SET */
        COMMENT(COMMENT_TEXT,
            "Trace is output when os_task_caller_depth_set is used to set the "
            "call stack depth for dynamic memory traces")
        TRACE_BEGIN(HOOK_CALLER_DEPTH_SET, "HOOK_CALLER_DEPTH_SET")
            OS_TASK(Task)
            OS_TASK(TargetTask)
            VALUE(8, BE, caller_depth, "Caller depth", DEC)
        TRACE_END()

        /* HOOK_DEBUG_INIT */
        COMMENT(COMMENT_TEXT,
            "Trace is output when OS initializes its debug related data at system startup")
        TRACE_BEGIN(HOOK_DEBUG_INIT, "HOOK_DEBUG_INIT")
        TRACE_END()

        /* HOOK_HEAP_TASK_LIST_SET */
        TRACE_BEGIN(HOOK_HEAP_TASK_LIST_SET, "HOOK_HEAP_TASK_LIST_SET")
            OS_TASK(Task)
            /* Something missing here...? */
        TRACE_END()

        /* HOOK_OS_INIT */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message is output when os_init is called.")
        TRACE_BEGIN(HOOK_OS_INIT, "HOOK_OS_INIT")
        TRACE_END()

        /* HOOK_ERROR - Always out... */
        COMMENT(COMMENT_PARAGRAPH, "OS internal function hook")
        COMMENT(COMMENT_PARAGRAPH,
            "This message identifies a fatal error in SW; or an error message "
            "that the user wants to display (and be handled as an OS-detected "
            " error).")
        COMMENT(COMMENT_PARAGRAPH,
            "The function ID (byte 2) identifies the function where error "
            "happened, it is the same value as the hook ID of that function.")
        TRACE_BEGIN(HOOK_ERROR, "HOOK_ERROR")
            OS_TASK(Task)
            VALUE_CONST(func, "Func", OS_HOOK_ID)
            VALUE_CONST(ostrich_hook_error, "Error", OS_ERROR_CODE)
            VALUE(32, BE, p1, "p1", HEX)
            VALUE(32, BE, p2, "p2", HEX)
            VALUE(32, BE, p3, "p3", HEX)
        TRACE_END()

        /* HOOK_UNKNOWN - always out */
        TRACE_BEGIN(HOOK_UNKNOWN, "HOOK_UNKNOWN")
        TRACE_END()

        /* HOOK_ALIGNED_BLOCK_ALLOC_NO_WAIT */
        TRACE_BEGIN(HOOK_ALIGNED_BLOCK_ALLOC_NO_WAIT, "HOOK_ALIGNED_BLOCK_ALLOC_NO_WAIT")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(32, BE, block_alignment, "Block alignment", DEC)
            OS_CALLERS
        TRACE_END()

        /* HOOK_ALIGNED_BLOCK_ALLOC */
        TRACE_BEGIN(HOOK_ALIGNED_BLOCK_ALLOC, "HOOK_ALIGNED_BLOCK_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(32, BE, block_alignment, "Block alignment", DEC)
            VALUE(32, BE, c1, "C1", DEC)
            VALUE(32, BE, c2, "C2", DEC)
        TRACE_END()

        /* HOOK_WAIT_IN_ALIGNED_BLOCK_ALLOC */
        TRACE_BEGIN(HOOK_WAIT_IN_ALIGNED_BLOCK_ALLOC, "HOOK_WAIT_IN_ALIGNED_BLOCK_ALLOC")
            OS_TASK(Task)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(32, BE, block_alignment, "Block alignment", DEC)
            VALUE(32, BE, c1, "C1", DEC)
            VALUE(32, BE, c2, "C2", DEC)
        TRACE_END()

        /* HOOK_MMU_PAGE_ALIGNED_HEAP_DEALLOC */
        TRACE_BEGIN(HOOK_MMU_PAGE_ALIGNED_HEAP_DEALLOC, "HOOK_MMU_PAGE_ALIGNED_HEAP_DEALLOC")
            OS_TASK(Task)
            VALUE(32, BE, ptr, "Ptr", HEX)
            OS_CALLERS
        TRACE_END()

        /* HOOK_MMU_PAGE_ALIGNED_HEAP_INIT */
        TRACE_BEGIN(HOOK_MMU_PAGE_ALIGNED_HEAP_INIT, "HOOK_MMU_PAGE_ALIGNED_HEAP_INIT")
            OS_TASK(Task)
            /* Something missing here...? */
        TRACE_END()

        /*  HOOK_WAIT_IN_HEAP_ALLOC_FROM */
         TRACE_BEGIN(HOOK_WAIT_IN_HEAP_ALLOC_FROM, "HOOK_WAIT_IN_HEAP_ALLOC_FROM")
            OS_TASK(Task)
            VALUE(32, BE, size, "Size", DEC)
            VALUE(16, BE, heap_id, "Heap ID", DEC)
            OS_CALLERS
        TRACE_END()

    TRACE_GROUP_END()

    COMMENT(COMMENT_PARAGRAPH, "Part: OS_MS:SPEC.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item: OS_MS:OS_USER_SPEC.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Workset Name: OS_MS:WS_OS_MS_43UPGRADE")
    COMMENT(COMMENT_PARAGRAPH, "Filename: os_user_spec.txt")
    NOTE("/14/")

RES_END

/*  End of file os_trc_m.h */
