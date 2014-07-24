/*
Nokia
CONFIDENTIAL
Deliverable software


            kernel_hal_chipset_api.h
            ----------------------------

            SW Include Document - ANSI C



Document identification and location in Synergy/CM

Database:           ou1gif

Object
    %name:           kernel_hal_chipset_api.h %
    %cvtype:         incl %
    %instance:       ou1core_1 %
    %version:        9.0 %
    %date_modified:  Tue Dec 20 12:52:59 2011 %

Copyright (c) Nokia. This material, including documentation and any related
computer programs, is protected by copyright controlled by Nokia.
All rights are reserved. Copying, including reproducing, storing, adapting or
translating, any or all of this material requires the prior written consent
of Nokia. This material also contains confidential information, which may not
be disclosed to others without the prior written consent of Nokia.

------------------------------------------------------------------------------
*/

/*
    Abstract and functional description

        3rd party Chipset API Specification for Kernel HAL

    Specification/design references

        GIF_SPECS\CoreSW\coresw_chipset_spec\Kernel HAL Chipset API Specification.pdf


*/

#ifndef KERNEL_HAL_CHIPSET_API_H
#define KERNEL_HAL_CHIPSET_API_H

#include <stdarg.h>
/* Informative list of headers which are directly used by the present header
 * and hence assumed to be included by the .c module before the present header
 *     global.h
 *     product.h
 *     type_def.h
 */

/* ---------------------------------------------------------------------------
 *
 * CONSTANTS
 *
 */

/* Phone startup reasons */
#define HW_STARTUP_UNKNOWN                      0x0000
#define HW_STARTUP_NORMAL                       0x0001
#define HW_STARTUP_RTC_ALARM                    0x0002
#define HW_STARTUP_CHARGER_CONNECTED            0x0004
#define HW_STARTUP_SERVICE_BATTERY              0x0008
#define HW_STARTUP_RESET                        0x0010
#define HW_STARTUP_TEST_BATTERY                 0x0020

#define HW_STARTUP_PRODUCTION_RESET             0x0040
#define HW_STARTUP_SW_RESET                     0x0080
#define HW_STARTUP_SW_WATCHDOG_RESET            0x0100
#define HW_STARTUP_PROMMER_RESET                0x0200
#define HW_STARTUP_MBUS_CONNECTED               0x0400
#define HW_STARTUP_SECURE_VIOLATION             0x0800

#define HW_STARTUP_FLASH_MODE                   0x1000  /* Flash Mode        */
#define HW_STARTUP_PURX                         0x2000  /* PURX              */
#define HW_STARTUP_USB_CABLE_CONNECT            0x4000  /* USB Cable Connect.*/

/* HW IO Control State values */
#define HW_IO_INPUT                               1
#define HW_IO_OUTPUT                              2
#define HW_IO_CURRENT_STATE                       4
#define HW_IO_PULLDOWN                            8
#define HW_IO_PULLUP                             16
#define HW_IO_POWERDOWN                          32

/*for input parameter genio_pin of hw_io_* functions */
#define HW_GENIO_NOT_USED                       0xFFFF

/* ---------------------------------------------------------------------------
 *
 * TYPES
 *
 */

typedef uint32 HAL_TIMER_HANDLE;
typedef void  (*HAL_TIMER_ISR) (void);

typedef enum {
  HAL_TIMER_ONESHOT,
  HAL_TIMER_REPEAT
} HAL_TIMER_MODE;

typedef enum {
  HW_IO_RISING_EDGE,
  HW_IO_FALLING_EDGE,
  HW_IO_LOW,
  HW_IO_HIGH
} HW_IO_EVENT;

enum HW_RESET_REASONS {
  HW_RESET_RESERVED = 0,                            /* 0  not a reset reason */
  HW_RESET_UNKNOWN = 1,                             /* 1 */
  HW_RESET_POWER_OFF_CHARGER_CONNECTED = 2,         /* 2 Charger detected in power off */
  HW_RESET_POWER_OFF_KEY_PRESSED = 3,               /* 3  PWR key pressed during power off */
  HW_RESET_SW_RESET_REQUESTED = 4,                  /* 4  SW reset */
  HW_RESET_STACK_OVERFLOW = 6,                      /* 6 */
  HW_RESET_WD_RESET_REQUESTED = 7,                  /* 7 SW WD reset requested*/
  HW_RESET_DIV_BY_ZERO = 8,                         /* 8 */
  HW_RESET_PRODUCTION_RESET = 12,                   /* 12 state transition reset */
  HW_RESET_ASSERTION_FAILED = 13,                   /* 13 assertion failed */
  HW_RESET_UNDEFINED_INSTRUCTION =14,               /* 14 */
  HW_RESET_IO_ABORT = 15,                           /* 15 I/O byte access attempt */
  HW_RESET_ADDRESS_ERROR = 17,                      /* 17 memory hole access */
  HW_RESET_FLASH_WRITE_PROTECTION = 19,             /* 19 unauthorized FLASH write*/
  HW_RESET_POWER_OFF_RTC = 21,                      /* 21 Alarm detected in power off */
  HW_RESET_OS_FATAL_HANDLER = 22,                   /* 22 */
  HW_RESET_FLASH_BLOCK_OVERFLOW = 23,               /* 23 */
  HW_RESET_ASIC_WD_RESET = 25,                      /* 25 */
  HW_RESET_UNHANDLED_ABORT = 34,                    /* 34 Abort BSE didn't handle */
  HW_RESET_OS_WARNING_HANDLER = 36,                 /* 36 */
  HW_RESET_SECURE_VIOLATION = 37,                   /* 37 */
  HW_RESET_MODEM = 39,                              /* 38 */
  HW_RESET_VENDOR_SW_TRAP = 40,                     /* 40 SW trap from Vendor SW */
  HW_MAX_RESET_REASONS = 42                         /* 42 */
};

/* ASIC data version ifo structure */
typedef struct {
  uint8 type;                  /* type of ASIC, ASIC ID */
  uint8 major;                 /* major version of ASIC */
  uint8 minor;                 /* minor version of ASIC */
  uint8 eco;                   /* ECO version */
  uint8 process;               /* Silicon process (130, 90nm, etc.)*/
  uint8 vendor;                /* vendor ID */
  uint8 reserved1;
  uint8 reserved2;
  void *extended_info;        /* product specific extended information, optional */
} HAL_ASIC_VERSION_INFO;

/* ---------------------------------------------------------------------------
 *
 * FUNCTIONAL PROTOTYPES AND MACROS
 *
 */
void hw_conditional_irq_disable(void);
void hw_conditional_irq_enable(void);

HAL_TIMER_HANDLE hal_timer_start(HAL_TIMER_ISR fp, HAL_TIMER_MODE mode, uint32 time_in_us);
uint32 hal_timer_stop(HAL_TIMER_HANDLE handle);
uint32 hal_timer_read(HAL_TIMER_HANDLE handle);

HAL_TIMER_HANDLE hal_timer_start_ms(HAL_TIMER_ISR fp, HAL_TIMER_MODE mode, uint32 time_in_ms);

uint32 hal_timer_rtc_read(void);

uint8 hw_io_read(dword logical_name);
uint8 hw_io_write(dword logical_name, byte state);
byte hw_io_control(dword logical_name, byte state);

void (*hw_io_event_register(dword logical_name, void (*handler)(void)))(void);
void hw_io_event_type(dword logical_name, HW_IO_EVENT type);
void hw_io_event_acknowledge(dword logical_name);
void hw_io_event_enable(dword logical_name);
void hw_io_event_disable(dword logical_name);

void   hw_power_off(bool8 check);
void   hw_reset_generate(byte status);
byte   hw_reset_reason_get(void);
bits32 hw_startup_reason_get(void);

void   asm_delay(dword delay_in_us);
void   delay_ms(uint32 delay_in_ms);

bool8 is_valid_pointer(void *p);
bool8 is_valid_ram_pointer(void *p);
bool8 is_valid_rom_pointer(void *p);

void hal_asic_version_info_get(HAL_ASIC_VERSION_INFO *data);
#endif /* KERNEL_HAL_CHIPSET_API_H */

/* End of Include File */
