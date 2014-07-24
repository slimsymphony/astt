/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                sutogen_symbols.h
                -----------------
                SW Include






Project:          autogen

%name:            autogen_symbols.h %
%version:         co1tss#62 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 12:54:25 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains definitions of all common symbols (from global.h and pn_const.h)
*/

#ifndef _AUTOGEN_SYMBOLS_H_
#define _AUTOGEN_SYMBOLS_H_

/* ============================================================================================= */
/* Symbol definitions */
/* ============================================================================================= */
#if (PMD_FILE_FORMAT >= 600)
PROPERTY(PROPERTY_ALIGNMENT_64_BITS)
#endif
RES_BEGIN(RESOURCE_SYMBOLS, AUTOGEN_NO_RESOURCE_ID, SYMBOLS, "Common symbols", "", FALSE)

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_TRUE_FALSE, 8, BE, "", "")
#ifdef TRUE
        CONST_TBL_ENTRY(TRUE, TRUE, "")
#endif /* TRUE */
#ifdef FALSE
        CONST_TBL_ENTRY(FALSE, FALSE, "")
#endif /* FALSE */
    CONST_TBL_END

    COMMENT(COMMENT_TEXT, "1 bit version of TRUE/FALSE constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_TRUE_FALSE_1, 1, BE, "", "")
#ifdef TRUE
        CONST_TBL_ENTRY(TRUE, TRUE, "")
#endif /* TRUE */
#ifdef FALSE
        CONST_TBL_ENTRY(FALSE, FALSE, "")
#endif /* FALSE */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of TRUE/FALSE constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_TRUE_FALSE_16, 16, BE, "", "")
#ifdef TRUE
        CONST_TBL_ENTRY(TRUE, TRUE, "")
#endif /* TRUE */
#ifdef FALSE
        CONST_TBL_ENTRY(FALSE, FALSE, "")
#endif /* FALSE */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of TRUE/FALSE constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_TRUE_FALSE_16_BE, 16, BE, "", "")
#ifdef TRUE
        CONST_TBL_ENTRY(TRUE, TRUE, "")
#endif /* TRUE */
#ifdef FALSE
        CONST_TBL_ENTRY(FALSE, FALSE, "")
#endif /* FALSE */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit LE version of TRUE/FALSE constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_TRUE_FALSE_16_LE, 16, LE, "", "")
#ifdef TRUE
        CONST_TBL_ENTRY(TRUE, TRUE, "")
#endif /* TRUE */
#ifdef FALSE
        CONST_TBL_ENTRY(FALSE, FALSE, "")
#endif /* FALSE */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit NATIVE version of TRUE/FALSE constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_TRUE_FALSE_16_NATIVE, 16, NATIVE, "", "")
#ifdef TRUE
        CONST_TBL_ENTRY(TRUE, TRUE, "")
#endif /* TRUE */
#ifdef FALSE
        CONST_TBL_ENTRY(FALSE, FALSE, "")
#endif /* FALSE */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_YES_NO, 8, BE, "", "")
#ifdef YES
        CONST_TBL_ENTRY(YES, YES, "")
#endif /* YES */
#ifdef NO
        CONST_TBL_ENTRY(NO, NO, "")
#endif /* NO */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "1 bit version of YES/NO constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_YES_NO_1, 1, BE, "", "")
#ifdef YES
        CONST_TBL_ENTRY(YES, YES, "")
#endif /* YES */
#ifdef NO
        CONST_TBL_ENTRY(NO, NO, "")
#endif /* NO */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of YES/NO constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_YES_NO_16, 16, BE, "", "")
#ifdef YES
        CONST_TBL_ENTRY(YES, YES, "")
#endif /* YES */
#ifdef NO
        CONST_TBL_ENTRY(NO, NO, "")
#endif /* NO */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of YES/NO constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_YES_NO_16_BE, 16, BE, "", "")
#ifdef YES
        CONST_TBL_ENTRY(YES, YES, "")
#endif /* YES */
#ifdef NO
        CONST_TBL_ENTRY(NO, NO, "")
#endif /* NO */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit LE  version of YES/NO constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_YES_NO_16_LE, 16, LE, "", "")
#ifdef YES
        CONST_TBL_ENTRY(YES, YES, "")
#endif /* YES */
#ifdef NO
        CONST_TBL_ENTRY(NO, NO, "")
#endif /* NO */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of YES/NO constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_YES_NO_16_NATIVE, 16, NATIVE, "", "")
#ifdef YES
        CONST_TBL_ENTRY(YES, YES, "")
#endif /* YES */
#ifdef NO
        CONST_TBL_ENTRY(NO, NO, "")
#endif /* NO */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ON_OFF, 8, BE, "", "")
#ifdef ON
        CONST_TBL_ENTRY(ON, ON, "")
#endif /* ON */
#ifdef OFF
        CONST_TBL_ENTRY(OFF, OFF, "")
#endif /* OFF */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "1 bit version of ON/OFF constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ON_OFF_1, 1, BE, "", "")
#ifdef ON
        CONST_TBL_ENTRY(ON, ON, "")
#endif /* ON */
#ifdef OFF
        CONST_TBL_ENTRY(OFF, OFF, "")
#endif /* OFF */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of ON/OFF constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ON_OFF_16, 16, BE, "", "")
#ifdef ON
        CONST_TBL_ENTRY(ON, ON, "")
#endif /* ON */
#ifdef OFF
        CONST_TBL_ENTRY(OFF, OFF, "")
#endif /* OFF */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of ON/OFF constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ON_OFF_16_BE, 16, BE, "", "")
#ifdef ON
        CONST_TBL_ENTRY(ON, ON, "")
#endif /* ON */
#ifdef OFF
        CONST_TBL_ENTRY(OFF, OFF, "")
#endif /* OFF */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of ON/OFF constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ON_OFF_16_LE, 16, LE, "", "")
#ifdef ON
        CONST_TBL_ENTRY(ON, ON, "")
#endif /* ON */
#ifdef OFF
        CONST_TBL_ENTRY(OFF, OFF, "")
#endif /* OFF */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of ON/OFF constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ON_OFF_16_NATIVE, 16, NATIVE, "", "")
#ifdef ON
        CONST_TBL_ENTRY(ON, ON, "")
#endif /* ON */
#ifdef OFF
        CONST_TBL_ENTRY(OFF, OFF, "")
#endif /* OFF */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ENABLED_DISABLED, 8, BE, "", "")
#ifdef ENABLED
        CONST_TBL_ENTRY(ENABLED, ENABLED, "")
#endif /* ENABLED */
#ifdef DISABLED
        CONST_TBL_ENTRY(DISABLED, DISABLED, "")
#endif /* DISABLED */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "1 bit version of ENABLED/DISABLED constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ENABLED_DISABLED_1, 1, BE, "", "")
#ifdef ENABLED
        CONST_TBL_ENTRY(ENABLED, ENABLED, "")
#endif /* ENABLED */
#ifdef DISABLED
        CONST_TBL_ENTRY(DISABLED, DISABLED, "")
#endif /* DISABLED */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of ENABLED/DISABLED constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ENABLED_DISABLED_16, 16, BE, "", "")
#ifdef ENABLED
        CONST_TBL_ENTRY(ENABLED, ENABLED, "")
#endif /* ENABLED */
#ifdef DISABLED
        CONST_TBL_ENTRY(DISABLED, DISABLED, "")
#endif /* DISABLED */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of ENABLED/DISABLED constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ENABLED_DISABLED_16_BE, 16, BE, "", "")
#ifdef ENABLED
        CONST_TBL_ENTRY(ENABLED, ENABLED, "")
#endif /* ENABLED */
#ifdef DISABLED
        CONST_TBL_ENTRY(DISABLED, DISABLED, "")
#endif /* DISABLED */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit LE version of ENABLED/DISABLED constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ENABLED_DISABLED_16_LE, 16, LE, "", "")
#ifdef ENABLED
        CONST_TBL_ENTRY(ENABLED, ENABLED, "")
#endif /* ENABLED */
#ifdef DISABLED
        CONST_TBL_ENTRY(DISABLED, DISABLED, "")
#endif /* DISABLED */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit NATIVE version of ENABLED/DISABLED constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_ENABLED_DISABLED_16_NATIVE, 16, NATIVE, "", "")
#ifdef ENABLED
        CONST_TBL_ENTRY(ENABLED, ENABLED, "")
#endif /* ENABLED */
#ifdef DISABLED
        CONST_TBL_ENTRY(DISABLED, DISABLED, "")
#endif /* DISABLED */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_OK_FAIL, 8, BE, "", "")
#ifdef OK
        CONST_TBL_ENTRY(OK, OK, "")
#endif /* OK */
#ifdef FAIL
        CONST_TBL_ENTRY(FAIL, FAIL, "")
#endif /* FAIL */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "1 bit version of OK/FAIL constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_OK_FAIL_1, 1, BE, "", "")
#ifdef OK
        CONST_TBL_ENTRY(OK, OK, "")
#endif /* OK */
#ifdef FAIL
        CONST_TBL_ENTRY(FAIL, FAIL, "")
#endif /* FAIL */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of OK/FAIL constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_OK_FAIL_16, 16, BE, "", "")
#ifdef OK
        CONST_TBL_ENTRY(OK, OK, "")
#endif /* OK */
#ifdef FAIL
        CONST_TBL_ENTRY(FAIL, FAIL, "")
#endif /* FAIL */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of OK/FAIL constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_OK_FAIL_16_BE, 16, BE, "", "")
#ifdef OK
        CONST_TBL_ENTRY(OK, OK, "")
#endif /* OK */
#ifdef FAIL
        CONST_TBL_ENTRY(FAIL, FAIL, "")
#endif /* FAIL */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit LE version of OK/FAIL constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_OK_FAIL_16_LE, 16, BE, "", "")
#ifdef OK
        CONST_TBL_ENTRY(OK, OK, "")
#endif /* OK */
#ifdef FAIL
        CONST_TBL_ENTRY(FAIL, FAIL, "")
#endif /* FAIL */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit NATIVE version of OK/FAIL constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_OK_FAIL_16_NATIVE, 16, NATIVE, "", "")
#ifdef OK
        CONST_TBL_ENTRY(OK, OK, "")
#endif /* OK */
#ifdef FAIL
        CONST_TBL_ENTRY(FAIL, FAIL, "")
#endif /* FAIL */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_COLD_WARM, 8, BE, "", "")
#ifdef COLD
        CONST_TBL_ENTRY(COLD, COLD, "")
#endif /* COLD */
#ifdef WARM
        CONST_TBL_ENTRY(WARM, WARM, "")
#endif /* WARM */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "1 bit version of COLD/WARM constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_COLD_WARM_1, 1, BE, "", "")
#ifdef COLD
        CONST_TBL_ENTRY(COLD, COLD, "")
#endif /* COLD */
#ifdef WARM
        CONST_TBL_ENTRY(WARM, WARM, "")
#endif /* WARM */
    CONST_TBL_END


    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of COLD/WARM constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_COLD_WARM_16, 16, BE, "", "")
#ifdef COLD
        CONST_TBL_ENTRY(COLD, COLD, "")
#endif /* COLD */
#ifdef WARM
        CONST_TBL_ENTRY(WARM, WARM, "")
#endif /* WARM */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit version of COLD/WARM constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_COLD_WARM_16_BE, 16, BE, "", "")
#ifdef COLD
        CONST_TBL_ENTRY(COLD, COLD, "")
#endif /* COLD */
#ifdef WARM
        CONST_TBL_ENTRY(WARM, WARM, "")
#endif /* WARM */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit LE version of COLD/WARM constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_COLD_WARM_16_LE, 16, LE, "", "")
#ifdef COLD
        CONST_TBL_ENTRY(COLD, COLD, "")
#endif /* COLD */
#ifdef WARM
        CONST_TBL_ENTRY(WARM, WARM, "")
#endif /* WARM */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_GENERATE_AS_BOOL)
    COMMENT(COMMENT_TEXT, "16 bit NATIVE version of COLD/WARM constants. Values taken from global.h")
    CONST_TBL_BEGIN(SYMBOLS_COLD_WARM_16_NATIVE, 16, NATIVE, "", "")
#ifdef COLD
        CONST_TBL_ENTRY(COLD, COLD, "")
#endif /* COLD */
#ifdef WARM
        CONST_TBL_ENTRY(WARM, WARM, "")
#endif /* WARM */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "Values taken from pn_const.h, version 146")
    CONST_TBL_BEGIN(SYMBOLS_PN_MEDIA, 8, BE, "", "")
#ifdef PN_MEDIA_ROUTING_REQ
        CONST_TBL_ENTRY(PN_MEDIA_ROUTING_REQ, PN_MEDIA_ROUTING_REQ, "")
#endif /* PN_MEDIA_ROUTING_REQ */
#ifdef PN_MEDIA_RESERVED
        CONST_TBL_ENTRY(PN_MEDIA_RESERVED, PN_MEDIA_RESERVED, "")
#endif /* PN_MEDIA_RESERVED */
#ifdef PN_MEDIA_OS
        CONST_TBL_ENTRY(PN_MEDIA_OS, PN_MEDIA_OS, "")
#endif /* PN_MEDIA_OS */
#ifdef PN_MEDIA_TRUST
        CONST_TBL_ENTRY(PN_MEDIA_TRUST, PN_MEDIA_TRUST, "")
#endif /* PN_MEDIA_TRUST */
#ifdef PN_MEDIA_RS232
        CONST_TBL_ENTRY(PN_MEDIA_RS232, PN_MEDIA_RS232, "")
#endif /* PN_MEDIA_RS232 */
#ifdef PN_MEDIA_JBUS
        CONST_TBL_ENTRY(PN_MEDIA_JBUS, PN_MEDIA_JBUS, "")
#endif /* PN_MEDIA_JBUS */
#ifdef PN_MEDIA_STI
        CONST_TBL_ENTRY(PN_MEDIA_STI, PN_MEDIA_STI, "")
#endif /* PN_MEDIA_STI */
#ifdef PN_MEDIA_MDI
        CONST_TBL_ENTRY(PN_MEDIA_MDI, PN_MEDIA_MDI, "")
#endif /* PN_MEDIA_MDI */
#ifdef PN_MEDIA_UDP
        CONST_TBL_ENTRY(PN_MEDIA_UDP, PN_MEDIA_UDP, "")
#endif /* PN_MEDIA_UDP */
#ifdef PN_MEDIA_IRDA
        CONST_TBL_ENTRY(PN_MEDIA_IRDA, PN_MEDIA_IRDA, "")
#endif /* PN_MEDIA_IRDA */
#ifdef PN_MEDIA_ENOS
        CONST_TBL_ENTRY(PN_MEDIA_ENOS, PN_MEDIA_ENOS, "")
#endif /* PN_MEDIA_ENOS */
#ifdef PN_MEDIA_INDUCTIVE
        CONST_TBL_ENTRY(PN_MEDIA_INDUCTIVE, PN_MEDIA_INDUCTIVE, "")
#endif /* PN_MEDIA_INDUCTIVE */
#ifdef PN_MEDIA_MSTI
        CONST_TBL_ENTRY(PN_MEDIA_MSTI, PN_MEDIA_MSTI, "")
#endif /* PN_MEDIA_MSTI */
#ifdef PN_MEDIA_RF
        CONST_TBL_ENTRY(PN_MEDIA_RF, PN_MEDIA_RF, "")
#endif /* PN_MEDIA_RF */
#ifdef PN_MEDIA_BT
        CONST_TBL_ENTRY(PN_MEDIA_BT, PN_MEDIA_BT, "")
#endif /* PN_MEDIA_BT */
#ifdef PN_MEDIA_IR
        CONST_TBL_ENTRY(PN_MEDIA_IR, PN_MEDIA_IR, "")
#endif /* PN_MEDIA_IR */
#ifdef PN_MEDIA_USB
        CONST_TBL_ENTRY(PN_MEDIA_USB, PN_MEDIA_USB, "")
#endif /* PN_MEDIA_USB */
#ifdef PN_MEDIA_FBUSIR
        CONST_TBL_ENTRY(PN_MEDIA_FBUSIR, PN_MEDIA_FBUSIR, "")
#endif /* PN_MEDIA_FBUSIR */
#ifdef PN_MEDIA_TCPIP
        CONST_TBL_ENTRY(PN_MEDIA_TCPIP, PN_MEDIA_TCPIP, "")
#endif /* PN_MEDIA_TCPIP */
#ifdef PN_MEDIA_FBUS
        CONST_TBL_ENTRY(PN_MEDIA_FBUS, PN_MEDIA_FBUS, "")
#endif /* PN_MEDIA_FBUS */
#ifdef PN_MEDIA_MBUS
        CONST_TBL_ENTRY(PN_MEDIA_MBUS, PN_MEDIA_MBUS, "")
#endif /* PN_MEDIA_MBUS */
#ifdef PN_MEDIA_MADI
        CONST_TBL_ENTRY(PN_MEDIA_MADI, PN_MEDIA_MADI, "")
#endif /* PN_MEDIA_MADI */
#ifdef PN_MEDIA_DADI
        CONST_TBL_ENTRY(PN_MEDIA_DADI, PN_MEDIA_DADI, "")
#endif /* PN_MEDIA_DADI */
#ifdef PN_MEDIA_SM
        CONST_TBL_ENTRY(PN_MEDIA_SM, PN_MEDIA_SM, "")
#endif /* PN_MEDIA_SM */
#ifdef PN_MEDIA_RTDX
        CONST_TBL_ENTRY(PN_MEDIA_RTDX, PN_MEDIA_RTDX, "")
#endif /* PN_MEDIA_RTDX */
#ifdef PN_MEDIA_I2C
        CONST_TBL_ENTRY(PN_MEDIA_I2C, PN_MEDIA_I2C, "")
#endif /* PN_MEDIA_I2C */
#ifdef PN_MEDIA_DEFAULT
        CONST_TBL_ENTRY(PN_MEDIA_DEFAULT, PN_MEDIA_DEFAULT, "")
#endif /* PN_MEDIA_DEFAULT */
#ifdef PN_MEDIA_HOST_SSI
        CONST_TBL_ENTRY(PN_MEDIA_HOST_SSI, PN_MEDIA_HOST_SSI, "")
#endif /* PN_MEDIA_HOST_SSI */
#ifdef PN_MEDIA_JTAG
        CONST_TBL_ENTRY(PN_MEDIA_JTAG, PN_MEDIA_JTAG, "")
#endif /* PN_MEDIA_JTAG */
    CONST_TBL_END

    COMMENT(COMMENT_TEXT, "Values taken from pn_const.h, version 146")
    CONST_TBL_BEGIN(SYMBOLS_PN_DEVICE, 8, BE, "", "")

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
        init_const_tbl_entry(0, AUTOGEN_DEVICE_NAME, AUTOGEN_DEVICE_ID, "", "", "");
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE */
#ifdef PN_DEV_TRACE
        CONST_TBL_ENTRY(PN_DEV_TRACE, PN_DEV_TRACE, "Trace")
#endif /* PN_DEV_TRACE */
#ifdef PN_DEV_HOST
        CONST_TBL_ENTRY(PN_DEV_HOST, PN_DEV_HOST, "MCU")
#endif /* PN_DEV_HOST */
#ifdef PN_DEV_TRACEBOX
        CONST_TBL_ENTRY(PN_DEV_TRACEBOX, PN_DEV_TRACEBOX, "Tracebox")
#endif /* PN_DEV_TRACEBOX */
#ifdef PN_DEV_PC
        CONST_TBL_ENTRY(PN_DEV_PC, PN_DEV_PC, "PC")
#endif /* PN_DEV_PC */
#ifdef PN_DEV_DSP_TESTER
        CONST_TBL_ENTRY(PN_DEV_DSP_TESTER, PN_DEV_DSP_TESTER, "")
#endif /* PN_DEV_DSP_TESTER */
#ifdef PN_DEV_COMBOX
        CONST_TBL_ENTRY(PN_DEV_COMBOX, PN_DEV_COMBOX, "")
#endif /* PN_DEV_COMBOX */
#ifdef PN_DEV_SECBOX
        CONST_TBL_ENTRY(PN_DEV_SECBOX, PN_DEV_SECBOX, "")
#endif /* PN_DEV_SECBOX */
#ifdef PN_DEV_SIM_READER
        CONST_TBL_ENTRY(PN_DEV_SIM_READER, PN_DEV_SIM_READER, "")
#endif /* PN_DEV_SIM_READER */
#ifdef PN_DEV_BTHF
        CONST_TBL_ENTRY(PN_DEV_BTHF, PN_DEV_BTHF, "")
#endif /* PN_DEV_BTHF */
#ifdef PN_DEV_PU
        CONST_TBL_ENTRY(PN_DEV_PU, PN_DEV_PU, "")
#endif /* PN_DEV_PU */
#ifdef PN_DEV_TEST
        CONST_TBL_ENTRY(PN_DEV_TEST, PN_DEV_TEST, "")
#endif /* PN_DEV_TEST */
#ifdef PN_DEV_SERVICE_TOOL
        CONST_TBL_ENTRY(PN_DEV_SERVICE_TOOL, PN_DEV_SERVICE_TOOL, "")
#endif /* PN_DEV_SERVICE_TOOL */

#ifdef PN_DEV_DATA_PIC
        CONST_TBL_ENTRY(PN_DEV_DATA_PIC, PN_DEV_DATA_PIC, "")
#endif /* PN_DEV_DATA_PIC */
#ifdef PN_DEV_TA
        CONST_TBL_ENTRY(PN_DEV_TA, PN_DEV_TA, "")
#endif /* PN_DEV_TA */
#ifdef PN_DEV_FASTTRACE
        CONST_TBL_ENTRY(PN_DEV_FASTTRACE, PN_DEV_FASTTRACE, "FastTrace")
#endif /* PN_DEV_FASTTRACE */
#ifdef PN_DEV_MODEM_HOST_1             
        CONST_TBL_ENTRY(PN_DEV_MODEM_HOST_1, PN_DEV_MODEM_HOST_1, "")
#endif /* PN_DEV_MODEM_HOST_1 */
#ifdef PN_DEV_MODEM             
        CONST_TBL_ENTRY(PN_DEV_MODEM, PN_DEV_MODEM, "")
#endif /* PN_DEV_MODEM */
#ifdef PN_DEV_MODEM_HOST_3             
        CONST_TBL_ENTRY(PN_DEV_MODEM_HOST_3, PN_DEV_MODEM_HOST_3, "")
#endif /* PN_DEV_MODEM_HOST_3 */
#ifdef PN_DEV_MODEM_2             
        CONST_TBL_ENTRY(PN_DEV_MODEM_2, PN_DEV_MODEM_2, "")
#endif /* PN_DEV_MODEM_2 */
#ifdef PN_DEV_SOS                      
        CONST_TBL_ENTRY(PN_DEV_SOS, PN_DEV_SOS, "SOS")
#endif /* PN_DEV_SOS */
#ifdef PN_DEV_REMOTE_HOST
        CONST_TBL_ENTRY(PN_DEV_REMOTE_HOST, PN_DEV_REMOTE_HOST, "")
#endif /* PN_DEV_REMOTE_HOST */
#ifdef PN_DEV_DSP_AUX
        CONST_TBL_ENTRY(PN_DEV_DSP_AUX, PN_DEV_DSP_AUX, "ADSP")
#endif /* PN_DEV_DSP_AUX */
#ifdef PN_DEV_DSP_MAIN
        CONST_TBL_ENTRY(PN_DEV_DSP_MAIN, PN_DEV_DSP_MAIN, "CDSP")
#endif /* PN_DEV_DSP_MAIN */
#ifdef PN_DEV_FIRST_DYNAMIC
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_1, PN_DEV_FIRST_DYNAMIC, "")
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_2, PN_DEV_FIRST_DYNAMIC+4, "")
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_3, PN_DEV_FIRST_DYNAMIC+8, "")
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_4, PN_DEV_FIRST_DYNAMIC+12, "")
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_5, PN_DEV_FIRST_DYNAMIC+16, "")
#endif /* PN_DEV_FIRST_DYNAMIC */
    CONST_TBL_END

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    COMMENT(COMMENT_TEXT, "Values taken from pn_const.h, version 146")
    CONST_TBL_BEGIN(SYMBOLS_PN_DEVICE_6, 6, BE, "", "")
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
        init_const_tbl_entry(0, AUTOGEN_DEVICE_NAME, AUTOGEN_DEVICE_ID/4, "", "", "");
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE */
#ifdef PN_DEV_TRACE
        CONST_TBL_ENTRY(PN_DEV_TRACE, PN_DEV_TRACE/4, "")
#endif /* PN_DEV_TRACE */
#ifdef PN_DEV_HOST
        CONST_TBL_ENTRY(PN_DEV_HOST, PN_DEV_HOST/4, "")
#endif /* PN_DEV_HOST */
#ifdef PN_DEV_TRACEBOX
        CONST_TBL_ENTRY(PN_DEV_TRACEBOX, PN_DEV_TRACEBOX/4, "")
#elif defined PN_DEV_OSTRICH
        CONST_TBL_ENTRY(PN_DEV_OSTRICH, PN_DEV_OSTRICH/4, "")
#endif /* PN_DEV_TRACEBOX */
#ifdef PN_DEV_PC
        CONST_TBL_ENTRY(PN_DEV_PC, PN_DEV_PC/4, "")
#endif /* PN_DEV_PC */
#ifdef PN_DEV_DSP_TESTER
        CONST_TBL_ENTRY(PN_DEV_DSP_TESTER, PN_DEV_DSP_TESTER/4, "")
#endif /* PN_DEV_DSP_TESTER */
#ifdef PN_DEV_COMBOX
        CONST_TBL_ENTRY(PN_DEV_COMBOX, PN_DEV_COMBOX/4, "")
#endif /* PN_DEV_COMBOX */
#ifdef PN_DEV_SECBOX
        CONST_TBL_ENTRY(PN_DEV_SECBOX, PN_DEV_SECBOX/4, "")
#endif /* PN_DEV_SECBOX */
#ifdef PN_DEV_SIM_READER
        CONST_TBL_ENTRY(PN_DEV_SIM_READER, PN_DEV_SIM_READER/4, "")
#endif /* PN_DEV_SIM_READER */
#ifdef PN_DEV_BTHF
        CONST_TBL_ENTRY(PN_DEV_BTHF, PN_DEV_BTHF/4, "")
#endif /* PN_DEV_BTHF */
#ifdef PN_DEV_PU
        CONST_TBL_ENTRY(PN_DEV_PU, PN_DEV_PU/4, "")
#endif /* PN_DEV_PU */
#ifdef PN_DEV_TEST
        CONST_TBL_ENTRY(PN_DEV_TEST, PN_DEV_TEST/4, "")
#endif /* PN_DEV_TEST */
#ifdef PN_DEV_SERVICE_TOOL
        CONST_TBL_ENTRY(PN_DEV_SERVICE_TOOL, PN_DEV_SERVICE_TOOL/4, "")
#endif /* PN_DEV_SERVICE_TOOL */
#ifdef PN_DEV_DATA_PIC
        CONST_TBL_ENTRY(PN_DEV_DATA_PIC, PN_DEV_DATA_PIC/4, "")
#endif /* PN_DEV_DATA_PIC */
#ifdef PN_DEV_TA
        CONST_TBL_ENTRY(PN_DEV_TA, PN_DEV_TA/4, "")
#endif /* PN_DEV_TA */
#ifdef PN_DEV_FASTTRACE
        CONST_TBL_ENTRY(PN_DEV_FASTTRACE, PN_DEV_FASTTRACE/4, "")
#endif /* PN_DEV_FASTTRACE */
#ifdef PN_DEV_MODEM_HOST_1             
        CONST_TBL_ENTRY(PN_DEV_MODEM_HOST_1, PN_DEV_MODEM_HOST_1/4, "")
#endif /* PN_DEV_MODEM_HOST_1 */
#ifdef PN_DEV_MODEM             
        CONST_TBL_ENTRY(PN_DEV_MODEM, PN_DEV_MODEM/4, "")
#endif /* PN_DEV_MODEM */
#ifdef PN_DEV_MODEM_HOST_3             
        CONST_TBL_ENTRY(PN_DEV_MODEM_HOST_3, PN_DEV_MODEM_HOST_3/4, "")
#endif /* PN_DEV_MODEM_HOST_3 */
#ifdef PN_DEV_MODEM_2             
        CONST_TBL_ENTRY(PN_DEV_MODEM_2, PN_DEV_MODEM_2/4, "")
#endif /* PN_DEV_MODEM_2 */
#ifdef PN_DEV_SOS                      
        CONST_TBL_ENTRY(PN_DEV_SOS, PN_DEV_SOS/4, "")
#endif /* PN_DEV_SOS */
#ifdef PN_DEV_REMOTE_HOST
        CONST_TBL_ENTRY(PN_DEV_REMOTE_HOST, PN_DEV_REMOTE_HOST/4, "")
#endif /* PN_DEV_REMOTE_HOST */
#ifdef PN_DEV_DSP_AUX
        CONST_TBL_ENTRY(PN_DEV_DSP_AUX, PN_DEV_DSP_AUX/4, "")
#endif /* PN_DEV_DSP_AUX */
#ifdef PN_DEV_DSP_MAIN
        CONST_TBL_ENTRY(PN_DEV_DSP_MAIN, PN_DEV_DSP_MAIN/4, "")
#endif /* PN_DEV_DSP_MAIN */
#ifdef PN_DEV_FIRST_DYNAMIC
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_1, PN_DEV_FIRST_DYNAMIC/4, "")
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_2, PN_DEV_FIRST_DYNAMIC/4 + 1, "")
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_3, PN_DEV_FIRST_DYNAMIC/4 + 2, "")
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_4, PN_DEV_FIRST_DYNAMIC/4 + 3, "")
        CONST_TBL_ENTRY(PN_DEV_DYNAMIC_5, PN_DEV_FIRST_DYNAMIC/4 + 4, "")
#endif /* PN_DEV_FIRST_DYNAMIC */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "Values taken from pn_const.h, version 146")
    CONST_TBL_BEGIN(SYMBOLS_PN_RESOURCE, 8, BE, "", "")

#ifdef PN_TRACE
        CONST_TBL_ENTRY(PN_TRACE, PN_TRACE, "")
#endif /* PN_TRACE */
#ifdef PN_CALL
        CONST_TBL_ENTRY(PN_CALL, PN_CALL, "")
#endif /* PN_CALL */
#ifdef PN_SMS
        CONST_TBL_ENTRY(PN_SMS, PN_SMS, "")
#endif /* PN_SMS */
#ifdef PN_PHONEBOOK
        CONST_TBL_ENTRY(PN_PHONEBOOK, PN_PHONEBOOK, "")
#endif /* PN_PHONEBOOK */
#ifdef PN_PHONE_STATUS
        CONST_TBL_ENTRY(PN_PHONE_STATUS, PN_PHONE_STATUS, "")
#endif /* PN_PHONE_STATUS */
#ifdef PN_SETTINGS
        CONST_TBL_ENTRY(PN_SETTINGS, PN_SETTINGS, "")
#endif /* PN_SETTINGS */
#ifdef PN_SS
        CONST_TBL_ENTRY(PN_SS, PN_SS, "")
#endif /* PN_SS */
#ifdef PN_CUSTOM_IDLE
        CONST_TBL_ENTRY(PN_CUSTOM_IDLE, PN_CUSTOM_IDLE, "")
#endif /* PN_CUSTOM_IDLE */
#ifdef PN_SECURITY
        CONST_TBL_ENTRY(PN_SECURITY, PN_SECURITY, "")
#endif /* PN_SECURITY */
#ifdef PN_SIM
        CONST_TBL_ENTRY(PN_SIM, PN_SIM, "")
#endif /* PN_SIM */
#ifdef PN_NETWORK
        CONST_TBL_ENTRY(PN_NETWORK, PN_NETWORK, "")
#endif /* PN_NETWORK */
#ifdef PN_AUDIO
        CONST_TBL_ENTRY(PN_AUDIO, PN_AUDIO, "")
#endif /* PN_AUDIO */
#ifdef PN_KEY
        CONST_TBL_ENTRY(PN_KEY, PN_KEY, "")
#endif /* PN_KEY */
#ifdef PN_MULTI_SIM
        CONST_TBL_ENTRY(PN_MULTI_SIM, PN_MULTI_SIM, "")
#endif /* PN_MULTI_SIM */
#ifdef PN_PANEL
        CONST_TBL_ENTRY(PN_PANEL, PN_PANEL, "")
#endif /* PN_PANEL */
#ifdef PN_ECHO
        CONST_TBL_ENTRY(PN_ECHO, PN_ECHO, "")
#endif /* PN_ECHO */
#ifdef PN_COMMGR
        CONST_TBL_ENTRY(PN_COMMGR, PN_COMMGR, "")
#endif /* PN_COMMGR */
#ifdef PN_JAVA
        CONST_TBL_ENTRY(PN_JAVA, PN_JAVA, "")
#endif
#ifdef PN_LOCAL_CONNECTIVITY
        CONST_TBL_ENTRY(PN_LOCAL_CONNECTIVITY, PN_LOCAL_CONNECTIVITY, "")
#endif /* PN_LOCAL_CONNECTIVITY */
#ifdef PN_CLDR
        CONST_TBL_ENTRY(PN_CLDR, PN_CLDR, "")
#endif /* PN_CLDR */
#ifdef PN_SMS_MEMORY
        CONST_TBL_ENTRY(PN_SMS_MEMORY, PN_SMS_MEMORY, "")
#endif /* PN_SMS_MEMORY */
#ifdef PN_MTC
        CONST_TBL_ENTRY(PN_MTC, PN_MTC, "")
#endif /* PN_MTC */
#ifdef PN_CSD
        CONST_TBL_ENTRY(PN_CSD, PN_CSD, "")
#endif /* PN_CSD */
#ifdef PN_ENERGY
        CONST_TBL_ENTRY(PN_ENERGY, PN_ENERGY, "")
#endif /* PN_ENERGY */
#ifdef PN_MENU
        CONST_TBL_ENTRY(PN_MENU, PN_MENU, "")
#endif /* PN_MENU */
#ifdef PN_TIME
        CONST_TBL_ENTRY(PN_TIME, PN_TIME, "")
#endif /* PN_TIME */
#ifdef PN_DATA_TEST
        CONST_TBL_ENTRY(PN_DATA_TEST, PN_DATA_TEST, "")
#endif /* PN_DATA_TEST */
#ifdef PN_PHONE_INFO
        CONST_TBL_ENTRY(PN_PHONE_INFO, PN_PHONE_INFO, "")
#endif /* PN_PHONE_INFO */
#ifdef PN_ACCESSORY
        CONST_TBL_ENTRY(PN_ACCESSORY, PN_ACCESSORY, "")
#endif /* PN_ACCESSORY */
#ifdef PN_UDM
        CONST_TBL_ENTRY(PN_UDM, PN_UDM, "")
#endif /* PN_UDM */
#ifdef PN_THEME
        CONST_TBL_ENTRY(PN_THEME, PN_THEME, "")
#endif /* PN_THEME */
#ifdef PN_TONE
        CONST_TBL_ENTRY(PN_TONE, PN_TONE, "")
#endif /* PN_TONE */
#ifdef PN_SOS_ADL
        CONST_TBL_ENTRY(PN_SOS_ADL, PN_SOS_ADL, "")
#endif /* PN_SOS_ADL */
#if (defined PN_PROVISIONING && (!defined PN_WAP_CONN || PN_PROVISIONING != PN_WAP_CONN))
        CONST_TBL_ENTRY(PN_PROVISIONING, PN_PROVISIONING, "")
#endif /* PN_PROVISIONING */
#ifdef PN_PERMANENT_DATA
        CONST_TBL_ENTRY(PN_PERMANENT_DATA, PN_PERMANENT_DATA, "")
#endif /* PN_PERMANENT_DATA */
#ifdef PN_COMMON_CALL1
        CONST_TBL_ENTRY(PN_COMMON_CALL1, PN_COMMON_CALL1, "")
#endif /* PN_COMMON_CALL1 */
#ifdef PN_COMMON_CALL2
        CONST_TBL_ENTRY(PN_COMMON_CALL2, PN_COMMON_CALL2, "")
#endif /* PN_COMMON_CALL2 */
#ifdef PN_WDP
        CONST_TBL_ENTRY(PN_WDP, PN_WDP, "")
#endif /* PN_WDP */
#ifdef PN_WSP
        CONST_TBL_ENTRY(PN_WSP, PN_WSP, "")
#endif /* PN_WSP */
#ifdef PN_SOCKET
        CONST_TBL_ENTRY(PN_SOCKET, PN_SOCKET, "")
#endif /* PN_SOCKET */
#ifdef PN_HELP
        CONST_TBL_ENTRY(PN_HELP, PN_HELP, "")
#endif /* PN_HELP */
#ifdef PN_PRJ_RESOURCE_C
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_C, PN_PRJ_RESOURCE_C, "")
#endif /* PN_PRJ_RESOURCE_C */
#ifdef PN_GPDS
        CONST_TBL_ENTRY(PN_GPDS, PN_GPDS, "")
#endif /* PN_GPDS */
#ifdef PN_GSS
        CONST_TBL_ENTRY(PN_GSS, PN_GSS, "")
#endif /* PN_GSS */
#ifdef PN_SELFTEST
        CONST_TBL_ENTRY(PN_SELFTEST, PN_SELFTEST, "")
#endif /* PN_SELFTEST */
#ifdef PN_OBEX
        CONST_TBL_ENTRY(PN_OBEX, PN_OBEX, "")
#endif /* PN_OBEX */
#ifdef PN_MEDIA_TRANSFER
 #ifdef PN_PRINT
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "PN_PRINT")
 #endif /* PN_PRO*/
        CONST_TBL_ENTRY(PN_MEDIA_TRANSFER, PN_MEDIA_TRANSFER, "")
#endif /* PN_MEDIA_TRANSFER */
#ifdef PN_MON
        CONST_TBL_ENTRY(PN_MON, PN_MON, "")
#endif /* PN_MON */
#ifdef PN_UPF
        CONST_TBL_ENTRY(PN_UPF, PN_UPF, "")
#endif /* PN_UPF */
#ifdef PN_LIGHT
        CONST_TBL_ENTRY(PN_LIGHT, PN_LIGHT, "")
#endif /* PN_LIGHT */
#ifdef PN_GSM_CS_PH
        CONST_TBL_ENTRY(PN_GSM_CS_PH, PN_GSM_CS_PH, "")
#endif /* PN_GSM_CS_PH */
#ifdef PN_FM_RADIO
        CONST_TBL_ENTRY(PN_FM_RADIO, PN_FM_RADIO, "")
#endif /* PN_FM_RADIO */
#ifdef PN_WAP_CONN
        CONST_TBL_ENTRY(PN_WAP_CONN, PN_WAP_CONN, "")
#endif /* PN_WAP_CONN */
#ifdef PN_TEST
        CONST_TBL_ENTRY(PN_TEST, PN_TEST, "")
#endif /* PN_TEST */
#ifdef PN_WARRANTY
        CONST_TBL_ENTRY(PN_WARRANTY, PN_WARRANTY, "")
#endif /* PN_WARRANTY */
#ifdef PN_NVD
        CONST_TBL_ENTRY(PN_NVD, PN_NVD, "")
#endif /* PN_NVD */
#ifdef PN_SECBOX
        CONST_TBL_ENTRY(PN_SECBOX, PN_SECBOX, "")
#endif /* PN_SECBOX */
#ifdef PN_COMBOX
        CONST_TBL_ENTRY(PN_COMBOX, PN_COMBOX, "")
#endif /* PN_COMBOX */
#ifdef PN_RTSP
        CONST_TBL_ENTRY(PN_RTSP, PN_RTSP, "")
#endif /* PN_RTSP */
#ifdef PN_SENSOR
        CONST_TBL_ENTRY(PN_SENSOR, PN_SENSOR, "")
#endif /* PN_SENSOR */
#ifdef PN_APDU
        CONST_TBL_ENTRY(PN_APDU, PN_APDU, "")
#endif /* PN_APDU */
#ifdef PN_CONTENT_DISPATCH
        CONST_TBL_ENTRY(PN_CONTENT_DISPATCH, PN_CONTENT_DISPATCH, "")
#endif /* PN_CONTENT_DISPATCH */
#ifdef PN_VOICE
        CONST_TBL_ENTRY(PN_VOICE, PN_VOICE, "")
#endif /* PN_VOICE */
#ifdef PN_SIMLOCK
        CONST_TBL_ENTRY(PN_SIMLOCK, PN_SIMLOCK, "")
#endif /* PN_SIMLOCK */
#ifdef PN_LOCATION
        CONST_TBL_ENTRY(PN_LOCATION, PN_LOCATION, "")
#endif /* PN_LOCATION */
#ifdef PN_SMC
        CONST_TBL_ENTRY(PN_SMC, PN_SMC, "")
#endif /* PN_SMC */
#ifdef PN_VRR
        CONST_TBL_ENTRY(PN_VRR, PN_VRR, "")
#endif /* PN_VRR */
#ifdef PN_EPOC_TEST
        CONST_TBL_ENTRY(PN_EPOC_TEST, PN_EPOC_TEST, "")
#endif /* PN_EPOC_TEST */
#ifdef PN_EPOC_SELFTEST
        CONST_TBL_ENTRY(PN_EPOC_SELFTEST, PN_EPOC_SELFTEST, "")
#endif /* PN_EPOC_SELFTEST */
#ifdef PN_ATK
        CONST_TBL_ENTRY(PN_ATK, PN_ATK, "")
#endif /* PN_ATK */
#ifdef PN_WCDMA_CS_PH
        CONST_TBL_ENTRY(PN_WCDMA_CS_PH, PN_WCDMA_CS_PH, "")
#endif /* PN_WCDMA_CS_PH */
#ifdef PN_SYNCML
        CONST_TBL_ENTRY(PN_SYNCML, PN_SYNCML, "")
#endif /* PN_SYNCML */
#ifdef PN_VERSIT
        CONST_TBL_ENTRY(PN_VERSIT, PN_VERSIT, "")
#endif /* PN_VERSIT */
#ifdef PN_EPOC_MON
        CONST_TBL_ENTRY(PN_EPOC_MON, PN_EPOC_MON, "")
#endif /* PN_EPOC_MON */
#ifdef PN_BEARERCTRL
 #ifdef PN_FEATURE_CONTROL
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "PN_FEATURE_CONTROL")
 #endif
        CONST_TBL_ENTRY(PN_BEARERCTRL, PN_BEARERCTRL, "")
#endif /* PN_BEARERCTRL */
#ifdef PN_CAMERA
        CONST_TBL_ENTRY(PN_CAMERA, PN_CAMERA, "")
#endif /* PN_CAMERA */
#ifdef PN_EPOC_INFO
        CONST_TBL_ENTRY(PN_EPOC_INFO, PN_EPOC_INFO, "")
#endif /* PN_EPOC_INFO */
#ifdef PN_LCIF
        CONST_TBL_ENTRY(PN_LCIF, PN_LCIF, "")
#endif /* PN_LCIF */
#ifdef PN_IMPS_CONTACTS
        CONST_TBL_ENTRY(PN_IMPS_CONTACTS, PN_IMPS_CONTACTS, "")
#endif /* PN_IMPS_CONTACTS */
#ifdef PN_MESSAGING
        CONST_TBL_ENTRY(PN_MESSAGING, PN_MESSAGING, "")
#endif /* PN_MESSAGING */
#ifdef PN_POC
        CONST_TBL_ENTRY(PN_POC, PN_POC, "")
#endif /* PN_POC */
#ifdef PN_HTTPSRV
        CONST_TBL_ENTRY(PN_HTTPSRV, PN_HTTPSRV, "")
#endif /* PN_HTTPSRV */
#ifdef PN_HTTP
        CONST_TBL_ENTRY(PN_HTTP, PN_HTTP, "")
#endif /* PN_HTTP */
#ifdef PN_SSL
        CONST_TBL_ENTRY(PN_SSL, PN_SSL, "")
#endif /* PN_SSL */
#ifdef PN_FILE
        CONST_TBL_ENTRY(PN_FILE, PN_FILE, "")
#endif /* PN_FILE */
#ifdef PN_BLUETOOTH
        CONST_TBL_ENTRY(PN_BLUETOOTH, PN_BLUETOOTH, "")
#endif /* PN_BLUETOOTH */
#ifdef PN_ADL
        CONST_TBL_ENTRY(PN_ADL, PN_ADL, "")
#endif /* PN_ADL */
#ifdef PN_TOUCHPAD
        CONST_TBL_ENTRY(PN_TOUCHPAD, PN_TOUCHPAD, "")
#endif /* PN_TOUCHPAD */
#ifdef PN_WIM
        CONST_TBL_ENTRY(PN_WIM, PN_WIM, "")
#endif /* PN_WIM */
#ifdef PN_CONCIERGE
        CONST_TBL_ENTRY(PN_CONCIERGE, PN_CONCIERGE, "")
#endif /* PN_CONCIERGE */
#ifdef PN_SIP
        CONST_TBL_ENTRY(PN_SIP, PN_SIP, "")
#endif /* PN_SIP */
#ifdef PN_RTP
        CONST_TBL_ENTRY(PN_RTP, PN_RTP, "")
#endif /* PN_RTP */
#ifdef PN_MUSIC
        CONST_TBL_ENTRY(PN_MUSIC, PN_MUSIC, "")
#endif /* PN_MUSIC */
#ifdef PN_IMPS
        CONST_TBL_ENTRY(PN_IMPS, PN_IMPS, "")
#endif /* PN_IMPS */
#ifdef PN_TUNEPLAYER
        CONST_TBL_ENTRY(PN_TUNEPLAYER, PN_TUNEPLAYER, "")
#endif /* PN_TUNEPLAYER */
#ifdef PN_ACC
        CONST_TBL_ENTRY(PN_ACC, PN_ACC, "")
#endif /* PN_ACC */
#ifdef PN_GARBAGE
        CONST_TBL_ENTRY(PN_GARBAGE, PN_GARBAGE, "")
#endif /* PN_GARBAGE */
#ifdef PN_TRACEBOX
        CONST_TBL_ENTRY(PN_TRACEBOX, PN_TRACEBOX, "")
#elif defined PN_OSTRICH
        CONST_TBL_ENTRY(PN_OSTRICH, PN_OSTRICH, "")
#endif /* PN_TRACEBOX */
#ifdef PN_LOCATION_STORAGE
        CONST_TBL_ENTRY(PN_LOCATION_STORAGE, PN_LOCATION_STORAGE, "")
#endif /* PN_LOCATION_STORAGE */
#ifdef PN_ACK
        CONST_TBL_ENTRY(PN_ACK, PN_ACK, "")
#endif /* PN_ACK */
#ifdef PN_BLUETOOTH_CORE
        CONST_TBL_ENTRY(PN_BLUETOOTH_CORE, PN_BLUETOOTH_CORE, "")
#endif /* PN_BLUETOOTH_CORE */
#ifdef PN_I2C
        CONST_TBL_ENTRY(PN_I2C, PN_I2C, "")
#endif /* PN_I2C */
#ifdef PN_PRJ_RESOURCE_A
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_A, PN_PRJ_RESOURCE_A, "")
#endif /* PN_PRJ_RESOURCE_A */
#ifdef PN_PRJ_RESOURCE_B
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_B, PN_PRJ_RESOURCE_B, "")
#endif /* PN_PRJ_RESOURCE_B */
#ifdef PN_RB_WAE1
        CONST_TBL_ENTRY(PN_RB_WAE1, PN_RB_WAE1, "")
#endif /* PN_RB_WAE1 */
#ifdef PN_PRJ_RESOURCE_D
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_D, PN_PRJ_RESOURCE_D, "")
#endif /* PN_PRJ_RESOURCE_D */
#ifdef PN_PRJ_RESOURCE_E
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_E, PN_PRJ_RESOURCE_E, "")
#endif /* PN_PRJ_RESOURCE_E */
#ifdef PN_PRJ_RESOURCE_F
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_F, PN_PRJ_RESOURCE_F, "")
#endif /* PN_PRJ_RESOURCE_F */
#ifdef PN_PRJ_RESOURCE_G
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_G, PN_PRJ_RESOURCE_G, "")
#endif /* PN_PRJ_RESOURCE_G */
#ifdef PN_PRJ_RESOURCE_H
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_H, PN_PRJ_RESOURCE_H, "")
#endif /* PN_PRJ_RESOURCE_H */
#ifdef PN_PRJ_RESOURCE_I
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_I, PN_PRJ_RESOURCE_I, "")
#endif /* PN_PRJ_RESOURCE_I */
#ifdef PN_PRJ_RESOURCE_J
        CONST_TBL_ENTRY(PN_PRJ_RESOURCE_J, PN_PRJ_RESOURCE_J, "")
#endif /* PN_PRJ_RESOURCE_J */
#ifdef PN_UICC
        CONST_TBL_ENTRY(PN_UICC, PN_UICC, "")
#endif /* PN_UICC */
#ifdef PN_MODEM_SIM_SRV
        CONST_TBL_ENTRY(PN_MODEM_SIM_SRV, PN_MODEM_SIM_SRV, "")
#endif /* PN_MODEM_SIM_SRV */
#ifdef PN_AT_MODEM
        CONST_TBL_ENTRY(PN_AT_MODEM, PN_AT_MODEM, "")
#endif /* PN_AT_MODEM */

#ifdef PN_AT_APPL
        CONST_TBL_ENTRY(PN_AT_APPL, PN_AT_APPL, "")
#endif /* PN_AT_APPL */
#ifdef PN_MODEM_LCS
        CONST_TBL_ENTRY(PN_MODEM_LCS, PN_MODEM_LCS, "")
#endif /* PN_MODEM_LCS */
#ifdef PN_MODEM_TEST
        CONST_TBL_ENTRY(PN_MODEM_TEST, PN_MODEM_TEST, "")
#endif /* PN_MODEM_TEST */
#ifdef PN_MODEM_NVD
        CONST_TBL_ENTRY(PN_MODEM_NVD, PN_MODEM_NVD, "")
#endif /* PN_MODEM_NVD */
#ifdef PN_MODEM_PERM
        CONST_TBL_ENTRY(PN_MODEM_PERM, PN_MODEM_PERM, "")
#endif /* PN_MODEM_PERM */
#ifdef PN_ODIN
        CONST_TBL_ENTRY(PN_ODIN, PN_ODIN, "")
#endif /* PN_ODIN */
#ifdef PN_WTA
        CONST_TBL_ENTRY(PN_WTA, PN_WTA, "")
#endif /* PN_WTA */
#ifdef PN_NFC                          
        CONST_TBL_ENTRY(PN_NFC, PN_NFC, "")
#endif /* PN_NFC */
#ifdef PN_SCREENSAVER                          
        CONST_TBL_ENTRY(PN_SCREENSAVER, PN_SCREENSAVER, "")
#endif /* PN_SCREENSAVER */
#ifdef PN_KEYGUARD                          
        CONST_TBL_ENTRY(PN_KEYGUARD, PN_KEYGUARD, "")
#endif /* PN_KEYGUARD */
#ifdef PN_LIGHT_UI                          
        CONST_TBL_ENTRY(PN_LIGHT_UI, PN_LIGHT_UI, "")
#endif /* PN_LIGHT_UI */
#ifdef PN_VAM                          
        CONST_TBL_ENTRY(PN_VAM, PN_VAM, "")
#endif /* PN_VAM */
#ifdef PN_IMS                          
        CONST_TBL_ENTRY(PN_IMS, PN_IMS, "")
#endif /* PN_IMS */
#ifdef PN_SOS_PERM                     
        CONST_TBL_ENTRY(PN_SOS_PERM, PN_SOS_PERM, "")
#endif /* PN_SOS_PERM */
#ifdef PN_POC_UI                       
        CONST_TBL_ENTRY(PN_POC_UI, PN_POC_UI, "")
#endif /* PN_POC_UI */
#ifdef PN_PRESENCE                     
        CONST_TBL_ENTRY(PN_PRESENCE, PN_PRESENCE, "")
#endif /* PN_PRESENCE */
#ifdef PN_XCAP                         
        CONST_TBL_ENTRY(PN_XCAP, PN_XCAP, "")
#endif /* PN_XCAP */
#ifdef PN_POC_GROUP                    
        CONST_TBL_ENTRY(PN_POC_GROUP, PN_POC_GROUP, "")
#endif /* PN_POC_GROUP */
#ifdef PN_ISA_SETTINGS                 
        CONST_TBL_ENTRY(PN_ISA_SETTINGS, PN_ISA_SETTINGS, "")
#endif /* PN_ISA_SETTINGS */
#ifdef PN_TRACFONE                     
        CONST_TBL_ENTRY(PN_TRACFONE, PN_TRACFONE, "")
#endif /* PN_TRACFONE */
#ifdef PN_MESSAGE_STORAGE              
        CONST_TBL_ENTRY(PN_MESSAGE_STORAGE, PN_MESSAGE_STORAGE, "")
#endif /* PN_MESSAGE_STORAGE */
#ifdef PN_MESSAGE_PROTOCOL             
        CONST_TBL_ENTRY(PN_MESSAGE_PROTOCOL, PN_MESSAGE_PROTOCOL, "")
#endif /* PN_MESSAGE_PROTOCOL */
#ifdef PN_VTBTEST                      
        CONST_TBL_ENTRY(PN_VTBTEST, PN_VTBTEST, "")
#endif /* PN_VTBTEST */
#ifdef PN_IP_COMMS                        
        CONST_TBL_ENTRY(PN_IP_COMMS, PN_IP_COMMS, "")
#endif /* PN_IP_COMMS */
#ifdef PN_HARDCORE                     
        CONST_TBL_ENTRY(PN_HARDCORE, PN_HARDCORE, "")
#endif /* PN_HARDCORE */
#ifdef PN_SOS_UMA                      
        CONST_TBL_ENTRY(PN_SOS_UMA, PN_SOS_UMA, "")
#endif /* PN_SOS_UMA */
#ifdef PN_VIDEO_PROTOCOL               
        CONST_TBL_ENTRY(PN_VIDEO_PROTOCOL, PN_VIDEO_PROTOCOL, "")
#endif /* PN_VIDEO_PROTOCOL */
#ifdef PN_WLAN                         
        CONST_TBL_ENTRY(PN_WLAN, PN_WLAN, "")
#endif /* PN_WLAN */
#ifdef PN_NEWS_DELIVERY                
        CONST_TBL_ENTRY(PN_NEWS_DELIVERY, PN_NEWS_DELIVERY, "")
#endif /* PN_NEWS_DELIVERY */
#ifdef PN_WRAN                         
        CONST_TBL_ENTRY(PN_WRAN, PN_WRAN, "")
#endif /* PN_WRAN */
#ifdef PN_EUTRAN_L2                    
        CONST_TBL_ENTRY(PN_EUTRAN_L2, PN_EUTRAN_L2, "")
#endif /* PN_EUTRAN_L2 */
#ifdef PN_EUTRAN_L1                    
        CONST_TBL_ENTRY(PN_EUTRAN_L1, PN_EUTRAN_L1, "")
#endif /* PN_EUTRAN_L1 */
#ifdef PN_RF_HAL                       
        CONST_TBL_ENTRY(PN_RF_HAL, PN_RF_HAL, "")
#endif /* PN_RF_HAL */
#ifdef PN_IM                           
        CONST_TBL_ENTRY(PN_IM, PN_IM, "")
#endif /* PN_IM */
#ifdef PN_NATT                         
        CONST_TBL_ENTRY(PN_NATT, PN_NATT, "")
#endif /* PN_NATT */
#ifdef PN_BACKUP                       
        CONST_TBL_ENTRY(PN_BACKUP, PN_BACKUP, "")
#endif /* PN_BACKUP */
#ifdef PN_MOB_POLICY                          
        CONST_TBL_ENTRY(PN_MOB_POLICY, PN_MOB_POLICY, "")
#endif /* PN_MOB_POLICY */
#ifdef PN_LANDMARK                          
        CONST_TBL_ENTRY(PN_LANDMARK, PN_LANDMARK, "")
#endif /* PN_LANDMARK */
#ifdef PN_MOBICAST                          
        CONST_TBL_ENTRY(PN_MOBICAST, PN_MOBICAST, "")
#endif /* PN_MOBICAST */
#ifdef PN_FWD_ERR_CORR                          
        CONST_TBL_ENTRY(PN_FWD_ERR_CORR, PN_FWD_ERR_CORR, "")
#endif /* PN_FWD_ERR_CORR */
#ifdef PN_GBA                          
        CONST_TBL_ENTRY(PN_GBA, PN_GBA, "")
#endif /* PN_GBA */
#ifdef PN_DYNAMIC_LOADER                          
        CONST_TBL_ENTRY(PN_DYNAMIC_LOADER, PN_DYNAMIC_LOADER, "")
#endif /* PN_DYNAMIC_LOADER */
#ifdef PN_MODEM_MCE                          
        CONST_TBL_ENTRY(PN_MODEM_MCE, PN_MODEM_MCE, "")
#endif /* PN_MODEM_MCE */
#ifdef PN_MODEM_MON_2                          
        CONST_TBL_ENTRY(PN_MODEM_MON_2, PN_MODEM_MON_2, "")
#endif /* PN_MODEM_MON_2 */
#ifdef PN_MODEM_MON_3                          
        CONST_TBL_ENTRY(PN_MODEM_MON_3, PN_MODEM_MON_3, "")
#endif /* PN_MODEM_MON_3 */
#ifdef PN_MODEM_INFO                          
        CONST_TBL_ENTRY(PN_MODEM_INFO, PN_MODEM_INFO, "")
#endif /* PN_MODEM_INFO */
#ifdef PN_RESOURCE_MANAGER                          
        CONST_TBL_ENTRY(PN_RESOURCE_MANAGER, PN_RESOURCE_MANAGER, "")
#endif /* PN_RESOURCE_MANAGER */
#ifdef PN_VENDOR_SPECIFIC_TESTS                          
        CONST_TBL_ENTRY(PN_VENDOR_SPECIFIC_TESTS, PN_VENDOR_SPECIFIC_TESTS, "")
#endif /* PN_VENDOR_SPECIFIC_TESTS */
#ifdef PN_MODEM_NETWORK                          
        CONST_TBL_ENTRY(PN_MODEM_NETWORK, PN_MODEM_NETWORK, "")
#endif /* PN_MODEM_NETWORK */
#ifdef PN_MODEM_CALL                          
        CONST_TBL_ENTRY(PN_MODEM_CALL, PN_MODEM_CALL, "")
#endif /* PN_MODEM_CALL */
#ifdef PN_METADATA                          
        CONST_TBL_ENTRY(PN_METADATA, PN_METADATA, "")
#endif /* PN_METADATA */
#ifdef PN_MODEM_GAN                          
        CONST_TBL_ENTRY(PN_MODEM_GAN, PN_MODEM_GAN, "")
#endif /* PN_MODEM_GAN */
#ifdef PN_GSM_IO                          
        CONST_TBL_ENTRY(PN_GSM_IO, PN_GSM_IO, "")
#endif /* PN_GSM_IO */
#ifdef PN_EAP_AUTH                     
        CONST_TBL_ENTRY(PN_EAP_AUTH, PN_EAP_AUTH, "")
#endif /* PN_EAP_AUTH */
#ifdef PN_MY5                          
        CONST_TBL_ENTRY(PN_MY5, PN_MY5, "")
#endif /* PN_MY5 */

#ifdef PN_REGISTRATION
        CONST_TBL_ENTRY(PN_REGISTRATION, PN_REGISTRATION, "")
#endif /* PN_REGISTRATION */
#ifdef PN_RPC_REQ
        CONST_TBL_ENTRY(PN_RPC_REQ, PN_RPC_REQ, "")
#endif /* PN_RPC_REQ */
#ifdef PN_RPC_RESP
        CONST_TBL_ENTRY(PN_RPC_RESP, PN_RPC_RESP, "")
#endif /* PN_RPC_RESP */
#ifdef PN_SLAVE_LOGOUT
        CONST_TBL_ENTRY(PN_SLAVE_LOGOUT, PN_SLAVE_LOGOUT, "")
#endif /* PN_SLAVE_LOGOUT */
#ifdef PN_ERROR_INFO
        CONST_TBL_ENTRY(PN_ERROR_INFO, PN_ERROR_INFO, "")
#endif /* PN_ERROR_INFO */
#ifdef PN_MEDIA_CONTROL
        CONST_TBL_ENTRY(PN_MEDIA_CONTROL, PN_MEDIA_CONTROL, "")
#endif /* PN_MEDIA_CONTROL */
#ifdef PN_MEDIA_REQUEST
        CONST_TBL_ENTRY(PN_MEDIA_REQUEST, PN_MEDIA_REQUEST, "")
#endif /* PN_MEDIA_REQUEST */
#ifdef PN_PIPE
        CONST_TBL_ENTRY(PN_PIPE, PN_PIPE, "")
#endif /* PN_PIPE */
#ifdef PN_ALIVE
        CONST_TBL_ENTRY(PN_ALIVE, PN_ALIVE, "")
#endif /* PN_ALIVE */
#ifdef PN_NAMESERVICE
        CONST_TBL_ENTRY(PN_NAMESERVICE, PN_NAMESERVICE, "")
#endif /* PN_NAMESERVICE */
#ifdef PN_ROUTER
        CONST_TBL_ENTRY(PN_ROUTER, PN_ROUTER, "")
#endif /* PN_ROUTER */
#ifdef PN_AUTHENTICATION
        CONST_TBL_ENTRY(PN_AUTHENTICATION, PN_AUTHENTICATION, "")
#endif /* PN_AUTHENTICATION */
#ifdef PN_DUMMY_RESOURCE
        CONST_TBL_ENTRY(PN_DUMMY_RESOURCE, PN_DUMMY_RESOURCE, "")
#endif /* PN_DUMMY_RESOURCE */
#ifdef PN_PREFIX
        CONST_TBL_ENTRY(PN_PREFIX, PN_PREFIX, "")
#endif /* PN_PREFIX */
#ifdef PN_PRIVATE
        CONST_TBL_ENTRY(PN_PRIVATE, PN_PRIVATE, "")
#endif /* PN_PRIVATE */

#ifdef PN_SOS_AUDIO                    
        CONST_TBL_ENTRY(PN_SOS_AUDIO, PN_SOS_AUDIO, "")
#endif /* PN_SOS_AUDIO */
#ifdef PN_UI_STARTUP_CTRL              
        CONST_TBL_ENTRY(PN_UI_STARTUP_CTRL, PN_UI_STARTUP_CTRL, "")
#endif /* PN_UI_STARTUP_CTRL */
#ifdef PN_KODIAK                       
        CONST_TBL_ENTRY(PN_KODIAK, PN_KODIAK, "")
#endif /* PN_KODIAK */
#ifdef PN_PAYLOAD_TEST                       
        CONST_TBL_ENTRY(PN_PAYLOAD_TEST, PN_PAYLOAD_TEST, "")
#endif /* PN_PAYLOAD_TEST */

/* DSP resources */

#ifdef PN_DSP_CORE
        CONST_TBL_ENTRY(PN_DSP_CORE, PN_DSP_CORE, "")
#endif /* PN_DSP_CORE */
#ifdef PN_DSP_VIDEO
        CONST_TBL_ENTRY(PN_DSP_VIDEO, PN_DSP_VIDEO, "")
#endif /* PN_DSP_VIDEO */
#ifdef PN_DSP_VOICE
        CONST_TBL_ENTRY(PN_DSP_VOICE, PN_DSP_VOICE, "")
#endif /* PN_DSP_VOICE */
#ifdef PN_DSP_MIDI
        CONST_TBL_ENTRY(PN_DSP_MIDI, PN_DSP_MIDI, "")
#endif /* PN_DSP_MIDI */
#ifdef PN_ADSP_CORE
        CONST_TBL_ENTRY(PN_ADSP_CORE, PN_ADSP_CORE, "")
#endif /* PN_ADSP_CORE */
#ifdef PN_DSP_SELF_TEST
        CONST_TBL_ENTRY(PN_DSP_SELF_TEST, PN_DSP_SELF_TEST, "")
#endif /* PN_DSP_SELF_TEST */
#ifdef PN_DSP_COMMON_TEST
        CONST_TBL_ENTRY(PN_DSP_COMMON_TEST, PN_DSP_COMMON_TEST, "")
#endif /* PN_DSP_COMMON_TEST */
#ifdef PN_WCDMA_DSP_CS
        CONST_TBL_ENTRY(PN_WCDMA_DSP_CS, PN_WCDMA_DSP_CS, "")
#endif /* PN_WCDMA_DSP_CS */
#ifdef PN_WCDMA_DSP_TEST
        CONST_TBL_ENTRY(PN_WCDMA_DSP_TEST, PN_WCDMA_DSP_TEST, "")
#endif /* PN_WCDMA_DSP_TEST */
#ifdef PN_GSM_DSP_CS
        CONST_TBL_ENTRY(PN_GSM_DSP_CS, PN_GSM_DSP_CS, "")
#endif /* PN_GSM_DSP_CS */
#ifdef PN_GSM_DSP_TEST
        CONST_TBL_ENTRY(PN_GSM_DSP_TEST, PN_GSM_DSP_TEST, "")
#endif /* PN_GSM_DSP_TEST */
#ifdef PN_GSM_DSP
        CONST_TBL_ENTRY(PN_GSM_DSP, PN_GSM_DSP, "")
#endif /* PN_GSM_DSP */
#ifdef PN_DSP_AUDIO
        CONST_TBL_ENTRY(PN_DSP_AUDIO, PN_DSP_AUDIO, "")
#endif /* PN_DSP_AUDIO */
#ifdef PN_DSP_GPRS
        CONST_TBL_ENTRY(PN_DSP_GPRS, PN_DSP_GPRS, "")
#endif /* PN_DSP_GPRS */
#ifdef PN_DSP_MUSIC
        CONST_TBL_ENTRY(PN_DSP_MUSIC, PN_DSP_MUSIC, "")
#endif /* PN_DSP_MUSIC */

#ifdef PN_NO_ROUTING
        CONST_TBL_ENTRY(PN_NO_ROUTING, PN_NO_ROUTING, "")
#endif /* PN_NO_ROUTING */

    CONST_TBL_END
    

    COMMENT(COMMENT_TEXT, 
        "Values taken from pn_const.h, version 79, "
        "and from autogenerated pn_obj_auto.h file")
    CONST_TBL_BEGIN(SYMBOLS_PN_OBJECT, 8, BE, "", "")
#ifdef PN_OBJ_ROUTING_REQ
        CONST_TBL_ENTRY(PN_OBJ_ROUTING_REQ, PN_OBJ_ROUTING_REQ, "")
#endif /* PN_OBJ_ROUTING_REQ */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, 
        "Values taken from pn_const.h, version 79, "
        "and from autogenerated pn_obj_auto.h file")
    CONST_TBL_BEGIN(SYMBOLS_PN_OBJECT_10, 10, BE, "", "")
#ifdef PN_OBJ_ROUTING_REQ
        CONST_TBL_ENTRY(PN_OBJ_ROUTING_REQ, PN_OBJ_ROUTING_REQ, "")
#endif /* PN_OBJ_ROUTING_REQ */
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, 
        "Values taken from pn_const.h, version 79, "
        "and from autogenerated pn_obj_auto.h file")
    CONST_TBL_BEGIN(SYMBOLS_PN_OBJECT_16, 16, BE, "", "")
#ifdef PN_OBJ_ROUTING_REQ
        CONST_TBL_ENTRY(PN_OBJ_ROUTING_REQ, PN_OBJ_ROUTING_REQ, "")
#endif /* PN_OBJ_ROUTING_REQ */
    CONST_TBL_END


    /* OS tasks */
    CONST_TBL_BEGIN(SYMBOLS_OS_TASK_NAME, 16, BE, "", "")

#ifdef AUTOGEN_INCLUDE_NOS_TRACES

		CONST_TBL_ENTRY(OS_INTERRUPT_HANDLER, 	0x00FE, "")
		CONST_TBL_ENTRY(OS_UNKNOWN_TASK, 		0x00FF, "")

 #define task(handle, stack, addr, prio, msg_buf_l, fast_msg_buf_l, os_task_init_msg) \
	CONST_TBL_ENTRY(handle, handle_id++, "")
 #define callback_task(handle, stack, addr, prio, msg_buf_l, fast_msg_buf_l, cb_buf_length, os_task_init_msg) \
	CONST_TBL_ENTRY(handle, handle_id++, "")

        {
        char taskname[25];
        unsigned int handle_id;

        for (handle_id = 0; handle_id < OS_DYNAMIC_TASK_AMOUNT; handle_id++)
            {
            sprintf(taskname, "OS_DYNAMIC_TASK_%u", handle_id+1);
            init_const_tbl_entry(0, pmd_heap_strdup(taskname), handle_id, "", "", NULL);
            }

        #include "os_elem.h"
        }

 #undef task
 #undef callback_task

#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

    CONST_TBL_END


    /* OS resources */
    CONST_TBL_BEGIN(SYMBOLS_OS_RESOURCE_NAME, 32, BE, "", "")

#ifdef AUTOGEN_INCLUDE_NOS_TRACES

 #define resource_strict(handle, type, init) \
    CONST_TBL_ENTRY(handle, handle_id++, "")

 #ifdef resource
  #undef resource
 #endif
 #define resource(handle) \
    CONST_TBL_ENTRY(handle, handle_id++, "")

 #ifdef semaphore
  #undef semaphore
 #endif
 #define semaphore(handle) \
    CONST_TBL_ENTRY(handle, handle_id++, "")
    
 #if defined OS_DYNAMIC_RESOURCE_AMOUNT

        {
        char resourcename[30];
        unsigned int handle_id;

        for (handle_id = 0; handle_id < OS_DYNAMIC_RESOURCE_AMOUNT; handle_id++)
            {
            sprintf(resourcename, "OS_DYNAMIC_RESOURCE_%u", handle_id+1);
            init_const_tbl_entry(0, pmd_heap_strdup(resourcename), handle_id, "", "", NULL);
            }

        #include "os_elem.h"

        }
 #else
        {
        unsigned int handle_id = 0;
        #include "os_elem.h"
        }
 #endif
 
 #undef semaphore
 #undef resource
 #undef resource_strich

 #define resource(handle)
 #define semaphore(handle)

#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

    CONST_TBL_END


    /* OS timers */
    CONST_TBL_BEGIN(SYMBOLS_OS_TIMER_NAME, 16, BE, "", "")

#ifdef AUTOGEN_INCLUDE_NOS_TRACES

 #define timer(handle, type, dest_task, message) \
	CONST_TBL_ENTRY(handle, handle_id++, "")
 #define timer_no_msg(handle) \
	CONST_TBL_ENTRY(handle, handle_id++, "")
 #define timer_default_msg(handle, type, dest_task) \
	CONST_TBL_ENTRY(handle, handle_id++, "")

        {
        char timername[25];
        unsigned int handle_id;

        for (handle_id = 0; handle_id < OS_DYNAMIC_TIMER_AMOUNT; handle_id++)
            {
            sprintf(timername, "OS_DYNAMIC_TIMER_%u", handle_id+1);
            init_const_tbl_entry(0, pmd_heap_strdup(timername), handle_id, "", "", NULL);
            }

        #include "os_elem.h"

 #ifdef OS_SIMULATED_REG_EVENT_INT
	CONST_TBL_ENTRY(RE_SERVICE_TIMER, handle_id, "")
 #endif
        }

 #undef timer
 #undef timer_no_msg
 #undef timer_default_msg

#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

    CONST_TBL_END


    /* OS block set */
    CONST_TBL_BEGIN(SYMBOLS_OS_BLOCK_SET_NAME, 16, BE, "", "")

#ifdef AUTOGEN_INCLUDE_NOS_TRACES

 #define block(count, size) \
    CONST_TBL_ENTRY(BLOCK_##size, handle_id++, "")

        {
        unsigned int handle_id = 0;
        #include "os_elem.h"
        }

#endif /* AUTOGEN_INCLUDE_NOS_TRACES */

    CONST_TBL_END

    /* Update also PMD_TRACE_SOURCE constants in pmdconstant.h when adding entries here */
    CONST_TBL_BEGIN(SYMBOLS_CDSP5_TRACE_SOURCES, 16, BE, "", "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_MAIN_CONTROL, PMD_TRACE_SOURCE_DSP5_CDSP_MAIN_CONTROL, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_CORE_SIGNALS, PMD_TRACE_SOURCE_DSP5_CDSP_CORE_SIGNALS, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_APPLICATION_SIGNALS, PMD_TRACE_SOURCE_DSP5_CDSP_APPLICATION_SIGNALS, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_SIGNALS, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_SIGNALS, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_SHARED_SIGNALS, PMD_TRACE_SOURCE_DSP5_CDSP_SHARED_SIGNALS, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_WCDMA_SIGNALS, PMD_TRACE_SOURCE_DSP5_CDSP_WCDMA_SIGNALS, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_APPLICATION, PMD_TRACE_SOURCE_DSP5_CDSP_APPLICATION, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_WCDMA_ALGORITHMS, PMD_TRACE_SOURCE_DSP5_CDSP_WCDMA_ALGORITHM, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_SHARED, PMD_TRACE_SOURCE_DSP5_CDSP_SHARED, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_SLEEP, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_SLEEP, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_COMMON, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_COMMON, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_MDI, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_MDI, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_TIMING, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_TIMING, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_AMR, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_AMR, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_GPRS, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_GPRS, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_EDGE, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_EDGE, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_GSM_RF, PMD_TRACE_SOURCE_DSP5_CDSP_GSM_RF, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_CDMA_SIGNALS, PMD_TRACE_SOURCE_DSP5_CDSP_CDMA_SIGNALS, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_WCDMA_ASIP, PMD_TRACE_SOURCE_DSP5_CDSP_WCDMA_ASIP, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_RF_HAL_SIGNALS, PMD_TRACE_SOURCE_DSP5_CDSP_RF_HAL_SIGNALS, "")
        CONST_TBL_ENTRY(CDSP_TRCSRC_RF_HAL, PMD_TRACE_SOURCE_DSP5_CDSP_RF_HAL, "")
    CONST_TBL_END

    /* Update also PMD_TRACE_SOURCE constants in pmdconstant.h when adding entries here */
    CONST_TBL_BEGIN(SYMBOLS_ADSP5_TRACE_SOURCES, 16, BE, "", "")
        CONST_TBL_ENTRY(ADSP_TRCSRC_MAIN_CONTROL, PMD_TRACE_SOURCE_DSP5_ADSP_MAIN_CONTROL, "")
        CONST_TBL_ENTRY(ADSP_TRCSRC_EAP, PMD_TRACE_SOURCE_DSP5_ADSP_EAP, "")
        CONST_TBL_ENTRY(ADSP_TRCSRC_VIDEO, PMD_TRACE_SOURCE_DSP5_ADSP_VIDEO, "")
        CONST_TBL_ENTRY(ADSP_TRCSRC_AUDIO, PMD_TRACE_SOURCE_DSP5_ADSP_AUDIO, "")
        CONST_TBL_ENTRY(ADSP_TRCSRC_SPEECH, PMD_TRACE_SOURCE_DSP5_ADSP_SPEECH, "")
        CONST_TBL_ENTRY(ADSP_TRCSRC_MIDI, PMD_TRACE_SOURCE_DSP5_ADSP_MIDI, "")
        CONST_TBL_ENTRY(ADSP_TRCSRC_MUSIC_ENHANCED, PMD_TRACE_SOURCE_DSP5_ADSP_MUSIC_ENHANCED, "")
        CONST_TBL_ENTRY(ADSP_TRCSRC_VOICE_UI, PMD_TRACE_SOURCE_DSP5_ADSP_VOICE_UI, "")
    CONST_TBL_END

    /* Invariant trace entity ID's */
    CONST_TBL_BEGIN(SYMBOLS_INVARIANT_TRACE_ENTITY_ID, 8, BE, "", "")
        /* entries are autogenerated... */
    CONST_TBL_END

    /* Vendor trace entity ID's */
    CONST_TBL_BEGIN(SYMBOLS_VENDOR_TRACE_ENTITY_ID, 8, BE, "", "")
        /* entries are autogenerated... */
    CONST_TBL_END

    /* Master trace types */
    CONST_TBL_BEGIN(SYMBOLS_MASTER_TRACE_TYPE, 8, BE, "", "")
        /* entries are autogenerated... */
    CONST_TBL_END

#ifdef AUTOGEN_INCLUDE_OST
    /* OST Version definitions */
    CONST_TBL_BEGIN(SYMBOLS_OST_VERSION, 8, BE, "", "")
        CONST_TBL_ENTRY(NO_VERSION,                    0, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_1,  1, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_2,  2, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_3,  3, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_4,  4, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_5,  5, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_6,  6, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_7,  7, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_8,  8, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_9,  9, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_10, 10, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_11, 11, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_12, 12, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_13, 13, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_14, 14, "")
        CONST_TBL_ENTRY(PROPRIETARY_IMPLEMENTATION_15, 15, "")
        CONST_TBL_ENTRY(OST_BASE_PROTOCOL_VERSION_1,   16, "")

        /* "Reserved for futur use" entries */
        {
            const unsigned int start_of_reserved = 17;      /* Change this when reserved entries are taken into use */
            char name[50];
            unsigned int entry;

            for (entry = start_of_reserved; entry <= 255; entry++)
            {
                sprintf(name, "RESERVED_FOR_FUTURE_USE_%u", entry-start_of_reserved+1);
                init_const_tbl_entry(0, pmd_heap_strdup(name), entry, "", "", NULL);
            }   
        }
    CONST_TBL_END
#endif

    /* simple sequences */
    SEQ_BEGIN(AUTOGEN_SEQ_BYTE_DEC, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_BYTE_HEX, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, data, "Data", HEX)
    SEQ_END


    SEQ_BEGIN(AUTOGEN_SEQ_WORD_DEC, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_WORD_DEC_BE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_WORD_DEC_LE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, LE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_WORD_DEC_NATIVE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, NATIVE, data, "Data", DEC)
    SEQ_END


    SEQ_BEGIN(AUTOGEN_SEQ_WORD_HEX, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_WORD_HEX_BE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_WORD_HEX_LE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, LE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_WORD_HEX_NATIVE, DONT_CREATE_STRUCT, "", "")
        VALUE(16, NATIVE, data, "Data", HEX)
    SEQ_END


    SEQ_BEGIN(AUTOGEN_SEQ_DWORD_DEC, DONT_CREATE_STRUCT, "", "")
        VALUE(32, BE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DWORD_DEC_BE, DONT_CREATE_STRUCT, "", "")
        VALUE(32, BE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DWORD_DEC_LE, DONT_CREATE_STRUCT, "", "")
        VALUE(32, LE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DWORD_DEC_NATIVE, DONT_CREATE_STRUCT, "", "")
        VALUE(32, NATIVE, data, "Data", DEC)
    SEQ_END


    SEQ_BEGIN(AUTOGEN_SEQ_DWORD_HEX, DONT_CREATE_STRUCT, "", "")
        VALUE(32, BE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DWORD_HEX_BE, DONT_CREATE_STRUCT, "", "")
        VALUE(32, BE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DWORD_HEX_LE, DONT_CREATE_STRUCT, "", "")
        VALUE(32, LE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DWORD_HEX_NATIVE, DONT_CREATE_STRUCT, "", "")
        VALUE(32, NATIVE, data, "Data", HEX)
    SEQ_END

#if (PMD_FILE_FORMAT >= 600)
    SEQ_BEGIN(AUTOGEN_SEQ_DDWORD_DEC_BE, DONT_CREATE_STRUCT, "", "")
        VALUE(64, BE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DDWORD_DEC_LE, DONT_CREATE_STRUCT, "", "")
        VALUE(64, LE, data, "Data", DEC)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DDWORD_DEC_NATIVE, DONT_CREATE_STRUCT, "", "")
        VALUE(64, NATIVE, data, "Data", DEC)
    SEQ_END


    SEQ_BEGIN(AUTOGEN_SEQ_DDWORD_HEX_BE, DONT_CREATE_STRUCT, "", "")
        VALUE(64, BE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DDWORD_HEX_LE, DONT_CREATE_STRUCT, "", "")
        VALUE(64, LE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(AUTOGEN_SEQ_DDWORD_HEX_NATIVE, DONT_CREATE_STRUCT, "", "")
        VALUE(64, NATIVE, data, "Data", HEX)
    SEQ_END
#endif

RES_END

#endif /* _AUTOGEN_SYMBOLS_H_ */


/*  End of file autogen_symbols.h */
