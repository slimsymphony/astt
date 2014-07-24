/*


                Mulder configuration file
                -------------------------

Copyright (c) Nokia Mobile Phones. All rights reserved.
--------------------------------------------------------------------------------
*/

#ifndef     MULDER_CONF_H
#define     MULDER_CONF_H

/* <conf_file>
     Owner                : <to be updated>
     SCF                  : <to be updated>
     Team                 : <to be updated>
     SCF contacts         : <to be updated>
     Parent feature       : ICF_MONITOR_SERV
</conf_file> */

#include "isa_core_conf.h"

/*  CONSTANTS  */

#define MULDER_DSP_XFILE_PLUGIN_ACTIVE       0
/* <conf>
     Name                 : MULDER_DSP_XFILE_PLUGIN_ACTIVE
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for activating/deactivating DSP xfiles
                            saved to a memory card. DSP xfiles can only be saved
                            on a memory card. This feature has nothing to do with
                            the "normal" xfiles, it is an extension for DSP.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     : DSP xfile will be saved to a memory, if memory card is present
     If feature is off    : DSP xfile will not be saved
     Valid range/ values  : 0 deactivated
                            1 activated
     Affected modules     : mulder_pl_file.c, srvmon.c
     Responsible          : Michael Noerlev
     Configuration type   : feature
     Other comments       : If the device do not have a memory card nothing will be saved
</conf> */

#define MULDER_FILE_PLUGIN_ACTIVE       1
/* <conf>
     Name                 : MULDER_FILE_PLUGIN_ACTIVE
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for activating/deactivating Mulder
                            Crash File Dumper plugin.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 deactivated
                            1 activated
     Affected modules     : mulder.c, mulder_asseble.c, mulder_pl_file.c
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       : This is the activation flag of the fileplugin and should
                            be allways ON, otherwise dump file are not created.
                            For S60 the dump is stored in PMM
                            For R&D the dump is stored in the gallery/file system
                            For sales software the dump is stored in PMM
</conf> */

#if   (MULDER_FILE_PLUGIN_ACTIVE == 1 ) && ((defined BUILD_PRODUCTION) || (defined ENO_SW_BUILD))
#define    MULDER_PMM_PLUGIN_ENABLE       1  /* XFiles stored to PMM instead of file2. */
#else
#define    MULDER_PMM_PLUGIN_ENABLE       0
#endif
/*#define MULDER_PMM_PLUGIN_ENABLE       0*/
/* <conf>
     Name                 : MULDER_PMM_PLUGIN_ENABLE
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling/disabling Mulder PMM
                            plugin.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag MULDER_FILE_PLUGIN_ACTIVE.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 disabled
                            1 enabled
     Affected modules     : mulder.c, mulder_pl_pmm.c, srvmon.c
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       : When PMM pluging is enabled then normal file plugin
                            is disabled so the dump files are stored directly to PMM
                            instead of gallery. This should allways be enabled when
                            Mulder is enabled in Symbian products!
</conf> */

#ifdef BUILD_PRODUCTION
#define MULDER_AUTOSMS_ENABLE       0 /* 0 for sales_sw_config */
#else
#define MULDER_AUTOSMS_ENABLE       1
#endif
/* <conf>
     Name                 : MULDER_AUTOSMS_ENABLE
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling/disabling Mulder
                            AutoSMS feature.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 disabled
                            1 enabled
     Affected modules     : mulder_pl_autosms.c, mulder.c, srvmon.c, mon_autosms.c,
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       : NOTE! Change MULDER_AUTOSMS_PHONE_NUMBER when enabling this feature!
</conf> */
#define MULDER_AUTOSMS_ACTIVE       1
/* <conf>
     Name                 : MULDER_AUTOSMS_ACTIVE
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for activating/deactivating Mulder
                            AutoSMS feature.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 inactive
                            1 active
     Affected modules     : mulder.c
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       : This defines the factory set value for AutoSMS feature.
                            If state changed runtime then the state will be stored into
                            the PMM.
</conf> */

#define MULDER_AUTOSMS_ALIVE_ENABLE       1
/* <conf>
     Name                 : MULDER_AUTOSMS_ALIVE_ENABLE
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling/disabling Mulder
                            AutoSMS alive message sending feature.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 disabled
                            1 enabled
     Affected modules     : mulder_assemble.c, mulder.c, mon_autosms.c,
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       : MULDER_AUTOSMS_ENABLE must be enabled when enabling this.
</conf> */

#define MULDER_AUTOSMS_MESSAGE_FILE_MAX   5
/* <conf>
     Name                 : MULDER_AUTOSMS_MESSAGE_FILE_MAX
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Flag is used for defining how many autosms files
                            can be saved in the filesystem.
     Specification        : If set to 0, no autosms files are saved.
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 disabled
                            1..100 enabled (could be higher, but does it make sense)
     Affected modules     : mon_autosms.c, mulder_pl_autosms.c
     Responsible          : Jarno Lamsa
     Configuration type   : feature
     Other comments       : MULDER_AUTOSMS_ENABLE must be enabled when enabling this.
</conf> */

#define MULDER_START_INTERVAL_AUTOSMS     1
/* <conf>
     Name                 : MULDER_START_INTERVAL_AUTOSMS
     Parent               : MULDER_AUTOSMS_ENABLE
     Type                 : FLAG_SETTING
     Description          : Flag is used for controling the interval between trying
                            to send AutoSMS. Value is in minuttes. Should not be 0
                            If there are no problem with sending SMS's then this interval is always used
                            Example where MULDER_START_INTERVAL_AUTOSMS    = 1
                                          MULDER_INCREASE_INTERVAL_AUTOSMS = 1
                                          MULDER_MAX_INTERVAL_AUTOSMS      = 32
                            Gives the interval 1,1,1,1,... This is default and correspond to the old solution

                            Example where MULDER_START_INTERVAL_AUTOSMS    = 1
                                          MULDER_INCREASE_INTERVAL_AUTOSMS = 2
                                          MULDER_MAX_INTERVAL_AUTOSMS      = 64
                            Gives the interval 1,2,4,8,16 ..64 (MULDER_MAX_INTERVAL_AUTOSMS)

                            Example where MULDER_START_INTERVAL_AUTOSMS    = 1
                                          MULDER_INCREASE_INTERVAL_AUTOSMS = 3
                                          MULDER_MAX_INTERVAL_AUTOSMS      = 64
                            Gives the interval 1,3,9,27..64 (MULDER_MAX_INTERVAL_AUTOSMS)
     Specification        :
     Restrictions         : Must not be 0
     Associated
     features/ parameters : MULDER_MAX_INTERVAL_AUTOSMS, MULDER_INCREASE_INTERVAL_AUTOSMS
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 1..1440 (could be higher, but it should make sense)
     Affected modules     : mulder_assemble.c, mulder.c, mon_autosms.c,
     Responsible          : Michael Noerlev
     Configuration type   : feature
     Other comments       : MULDER_AUTOSMS_ENABLE must be enabled when enabling this.
</conf> */


#define MULDER_INCREASE_INTERVAL_AUTOSMS     1
/* <conf>
     Name                 : MULDER_INCREASE_INTERVAL_AUTOSMS
     Parent               : MULDER_AUTOSMS_ENABLE
     Type                 : FLAG_SETTING
     Description          : Flag is used for controling the interval between trying
                            to send AutoSMS when sending is failing. This value is multiplied
                            with the current interval e.g. if MULDER_INCREASE_INTERVAL_AUTOSMS=2 and
                            current interval is 1 then
                            the interval will be increased 2,4,8,16,32 .. MULDER_MAX_INTERVAL_AUTOSMS for
                            each sending that fails. When sending succeed the interval is set back to
                            MULDER_START_INTERVAL_AUTOSMS
                            See more examples under MULDER_START_INTERVAL_AUTOSMS
     Specification        :
     Restrictions         : Must not be 0
     Associated
     features/ parameters : MULDER_MAX_INTERVAL_AUTOSMS, MULDER_START_INTERVAL_AUTOSMS
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 1..10 (could be higher, but it should make sense)
     Affected modules     : mulder_assemble.c, mulder.c, mon_autosms.c,
     Responsible          : Michael Noerlev
     Configuration type   : feature
     Other comments       : MULDER_AUTOSMS_ENABLE must be enabled when enabling this.
</conf> */

#define MULDER_MAX_INTERVAL_AUTOSMS     32
/* <conf>
     Name                 : MULDER_MAX_INTERVAL_AUTOSMS
     Parent               : MULDER_AUTOSMS_ENABLE
     Type                 : FLAG_SETTING
     Description          : Flag is used for controling the the maximum interval between trying
                            to send AutoSMS. The interval will always be lesser or equal to this value.
                            Value is in minnutes.
                            See examples under MULDER_START_INTERVAL_AUTOSMS
     Specification        :
     Restrictions         : Must not be 0
     Associated
     features/ parameters : MULDER_INCREASE_INTERVAL_AUTOSMS, MULDER_START_INTERVAL_AUTOSMS
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 1..60 (could be higher, but it should make sense)
     Affected modules     : mulder_assemble.c, mulder.c, mon_autosms.c,
     Responsible          : Michael Noerlev
     Configuration type   : feature
     Other comments       : MULDER_AUTOSMS_ENABLE must be enabled when enabling this.
</conf> */

#if (MULDER_AUTOSMS_ALIVE_ENABLE == 1)
#define MULDER_AUTOSMS_CURRENT_MONITOR 0
/* <conf>
     Name                 : MULDER_AUTOSMS_CURRENT_MONITOR
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling/disabling Mulder
                            AutoSMS for current consumption monitoring
     Specification        : If there is no current measurement below or equal 5mA
                            during the last 1 hour*MULDER_AUTOSMS_CURR_TIMER_ADJUST-periode
                            then an additional alive message with this lowest current value is sent out
     Restrictions         :  -
     Associated
     features/ parameters : MULDER_AUTOSMS_CURR_TIMER_MULTIPLIER, MULDER_AUTOSMS_ALIVE_ENABLE
     If feature is on     : Monitoring message may be sent
     If feature is off    : Monitoring message will never be sent
     Valid range/ values  : 0 disabled
                            1 enabled
     Affected modules     : mon_autosms.c,
     Responsible          : Ole F. Kristensen
     Configuration type   : feature
     Other comments       : MULDER_AUTOSMS_ALIVE_ENABLE must be enabled when enabling this.
</conf> */
#else
#define MULDER_AUTOSMS_CURRENT_MONITOR  0
#endif

#if (MULDER_AUTOSMS_ALIVE_ENABLE == 1)
#if MULDER_AUTOSMS_CURRENT_MONITOR == 1
#define MULDER_AUTOSMS_CURR_TIMER_MULTIPLIER    1
/* <conf>
     Name                 : MULDER_AUTOSMS_CURR_TIMER_MULTIPLIER
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Multiplier used to adjust the size of measurement window for
                            current consumption alive message sending
     Specification        : = 1=> 1 hour interval, 12 => 12 hours interval
     Restrictions         : Must be within stated interval
     Associated
     features/ parameters : MULDER_AUTOSMS_CURRENT_MONITOR, MULDER_AUTOSMS_ALIVE_ENABLE
     If feature is on     : -
     If feature is off    : -
     Valid range/ values  : 1..12
     Affected modules     : mon_autosms.c
     Responsible          : Ole F. Kristensen
     Configuration type   : parameter
     Other comments       : Only used when MULDER_AUTOSMS_CURRENT_MONITOR=1
</conf> */
#endif
#endif


#define MULDER_INFO_PP_AUTOSMS          1
/* <conf>
     Name                 : MULDER_INFO_PP_AUTOSMS
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for activating/deactivating the usage
                            PP-flag.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 inactive
                            1 active
     Affected modules     : mulder.c
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       : This flag defines the usage of PP-flag. AutoSMS feature can be
                            enabled or disabled in runtime by using a PP-flag.
</conf> */

#define MULDER_DUMP_FILE_HIDDEN         0
/* <conf>
     Name                 : MULDER_DUMP_FILE_HIDDEN
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for hiding mulder crash dump files
                            in gallery.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP and MULDER_FILE_PLUGIN_ACTIVE.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 visible
                            1 hidden
     Affected modules     : mulder_pl_file.c
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

/* Define static data types to be collected */
#define MULDER_ABORT_DATA               1
/* <conf>
     Name                 : MULDER_ABORT_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the abort data to be collected
                            into the dump file.
     Specification        :
     Restrictions         : SISA-products takes no affect by defining this flag because
                            in those it is not currently possible to receive abort data.
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_OS_DATA                  1
/* <conf>
     Name                 : MULDER_OS_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the OS post mortem data to be
                            collected into the dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#if ( BUILD_TARGET != G_BUILD_TARGET_UPDATE_AGENT )
#define MULDER_OS_VMM_PAGER_DATA                  1
#else
#define MULDER_OS_VMM_PAGER_DATA                  0
#endif
/* <conf>
     Name                 : MULDER_OS_VMM_PAGER_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the OS VMM PAGER post mortem
                            data to be collected into the dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Michael Noerlev
     Configuration type   : feature
     Other comments       :
</conf> */

#if defined ( ENGINE_ONLY ) || defined ( ENO_SW_BUILD )
#define MULDER_YAPAS_MEM_DATA    0
#else
#define MULDER_YAPAS_MEM_DATA    1
#endif
/* <conf>
     Name                 : MULDER_YAPAS_MEM_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the Yapas post mortem
                            memory status to be collected into the dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_ident_yapas.c, mulder_ident_yapas.h
     Responsible          :
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_CRASHDUMP_CHIPSET_DATA_00    1
#define MULDER_CRASHDUMP_CHIPSET_DATA_01    0
#define MULDER_CRASHDUMP_CHIPSET_DATA_02    0
#define MULDER_CRASHDUMP_CHIPSET_DATA_03    0
#define MULDER_CRASHDUMP_CHIPSET_DATA_04    0
#define MULDER_CRASHDUMP_CHIPSET_DATA_05    0
#define MULDER_CRASHDUMP_CHIPSET_DATA_06    0
#define MULDER_CRASHDUMP_CHIPSET_DATA_07    0
#define MULDER_CRASHDUMP_CHIPSET_DATA_08    0
#define MULDER_CRASHDUMP_CHIPSET_DATA_09    1

/* <conf>
     Name                 : MULDER_CRASHDUMP_CHIPSET_DATA_xx
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the Vendor post mortem
                            data to be collected into the dump file.
                            There are al together 10 idents which can be used
                            The corresponding flag(s) MULDER_CHIPSET_CRASH_DUMP_DATA_SIZE_xx
                            must also be set.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP, MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_xx
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Michael Noerlev
     Configuration type   : feature
     Other comments       :
</conf> */


#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_00 1036
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_01 2060
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_02  300
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_03 4108
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_04  300
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_05  300
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_06  300
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_07  300
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_08  300
#define MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_09 1036

/* <conf>
     Name                 : MULDER_CRASHDUMP_CHIPSET_DATA_SIZE_xx
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Size of vendor crash dump data
                            This is only used if it is a vendor phone.
                            The value must be changed to reflect the vendor
                            crash dump data. the 300 is only a default. The
                            corresonding flag(s) MULDER_CRASHDUMP_CHIPSET_DATA_xx must
                            also be set.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP
                            MULDER_VENDOR_DATA_xx
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0  Not a vendor phone
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Michael Noerlev
     Configuration type   : parameter
     Other comments       :
</conf> */

#if defined ( ENGINE_ONLY ) || defined ( ENO_SW_BUILD ) || defined ( SP_UI )
#define MULDER_DYN_LD_SW_INFO_DATA      OFF
#else
#define MULDER_DYN_LD_SW_INFO_DATA      ON
#endif
/* <conf>
     Name                 : MULDER_DYN_LD_SW_INFO_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the DL post mortem data to be
                            collected into the dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP
     If feature is on     : Data is collected
     If feature is off    : No data is collected
     Valid range/ values  : N/A
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_CL_DATA                  1
/* <conf>
     Name                 : MULDER_CL_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the CL data to be
                            collected into the dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_MDI_DATA                 0
/* <conf>
     Name                 : MULDER_MDI_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the MDI data to be
                            collected into the dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_CALL_STACK_DATA          1
/* <conf>
     Name                 : MULDER_CALL_STACK_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the call stack
                            data to be collected into the dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_TRACE_BUFFER_DATA        0
/* <conf>
     Name                 : MULDER_TRACE_BUFFER_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the user trace buffer
                            data to be collected into the dumpfile.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_WATCHDOG_DATA            1
/* <conf>
     Name                 : MULDER_WATCHDOG_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Controls the inclusion of SW watchdog data into the
                            dumpfile.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     : Watchdog data is included to the dump.
     If feature is off    : Watchdog data is not included.
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#ifdef BUILD_PRODUCTION
#define MULDER_IAM_DATA                 0 /* 0 for sales_sw_config */
#else
#define MULDER_IAM_DATA                 0
#endif
/* <conf>
     Name                 : MULDER_IAM_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Controls the inclusion of IAM data into the
                            dumpfile.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     : IAM data is included to the dump.
     If feature is off    : IAM data is not included.
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_CM_OBJ_DATA                 1

/* <conf>
     Name                 : MULDER_CM_OBJ_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Controls the inclusion of CM object data into the
                            dumpfile.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     : CM object data is included to the dump.
     If feature is off    : CM object data is not included.
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_BB5_MDI_V1_DATA          0
/* <conf>
     Name                 : MULDER_BB5_MDI_V1_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the MDI MCU-DSP
                            interface protocol messages data to be
                            collected into the dump file.
     Specification        :
     Restrictions         : Should be enabled only in BB5 products.
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_CDSP_STATUS_DATA         0
/* <conf>
     Name                 : MULDER_CDSP_STATUS_DATA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling the CDSP
                            status data to be collected into the
                            dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0 not collected
                            1 collected
     Affected modules     : mulder_assemble.c, mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_TRACE_BUFFER_SIZE        20
/* <conf>
     Name                 : MULDER_TRACE_BUFFER_SIZE
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Defines the size of Mulder user trace buffer.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag MULDER_TRACE_BUFFER_DATA.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 5..
     Affected modules     : mulder.c, mulder_trace.c, mulder_assemble.c,
                            mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       : This flag defines how many trace items will be stored
                            into the circular user trace buffer.
</conf> */

#define MULDER_USER_DATA_SIZE           300
/* <conf>
     Name                 : MULDER_USER_DATA_SIZE
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Defines the size of user data area in dump file.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flag ICF_CRASH_DUMP.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0..
     Affected modules     : mulder_assemble.h
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       : If there happens buffer overflow this buffer size can be
                            increased to avoid overflow. Value is in bytes.
</conf> */

#ifdef BUILD_PRODUCTION
#define MULDER_MAX_LOG_NAMES           4 /* 4 for sales_sw_config */
#else
#define MULDER_MAX_LOG_NAMES           20
#endif
/* <conf>
     Name                 : MULDER_MAX_LOG_NAMES
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Defines the maximum amount of log files in gallery.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : See flags ICF_CRASH_DUMP and MULDER_FILE_PLUGIN_ACTIVE.
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 1..
     Affected modules     : mulder_pl_file.c
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       : When maximum is reached then the oldest logfile will be deleted
                            before saving the new one.
</conf> */

#define MULDER_AUTOSMS_PHONE_NUMBER     "+358408033295" /* Oulu server */
/* <conf>
     Name                 : MULDER_AUTOSMS_PHONE_NUMBER
     Type                 : FLAG_SETTING
     Description          : Defines the phone number that is used when sending SMS message
                            with AutoSMS feature.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : mulder_pl_autosms.c
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       : This number should be defined as a string (within ""-marks).
                            Note that SMS service center number will be get directly from
                            phone message settings.
</conf> */

#define MULDER_AUTOSMS_QUEUE_LEN        5
/* <conf>
     Name                 : MULDER_AUTOSMS_QUEUE_LEN
     Type                 : FLAG_SETTING
     Description          : Defines the length of the AutoSMS queue.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 2..
     Affected modules     : mon_autosms.c, mulder_pl_autosms.c
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       :
</conf> */

#define MULDER_AUTOSMS_ALIVE_TIME_HOUR  12
/* <conf>
     Name                 : MULDER_AUTOSMS_ALIVE_TIME_HOUR
     Type                 : FLAG_SETTING
     Description          : Defines the time when sending an alive message.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : 0..23
     Affected modules     : mon_autosms.c
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       :
</conf> */

#define MULDER_AUTOSMS_ALTERNATIVE_CENTER_NUMBER "+3584544", "+86", "+91", "+55", "+234", "+36", "+66", "+62", "+971"           /* NTN, Beijing, Bangalore, Brazil, Nigeria, Hungary, Thailand, Indonesia, UAE */
#define MULDER_AUTOSMS_ALTERNATIVE_SERVER_NUMBER "+3584544182256", "+8613910316592", "+919591998208", "+559293685088", "+2348163732905", "+36306561267", "+66906438628", "+628111587393", "+971556354657"
/* <conf>
     Name                 : MULDER_AUTOSMS_ALTERNATIVE_CENTER_NUMBER
                            MULDER_AUTOSMS_ALTERNATIVE_SERVER_NUMBER
     Type                 : FLAG_SETTING
     Description          : Defines alternative AutoSMS destination
                            number which will be choosen for SIM cards
                            with given service center number.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : The center number is compared by using the
                            amount of digits given in this definition.
     If feature is on     : AutoSMS is sent to alternative number for
                            matching SIM cards.
     If feature is off    : AutoSMS is always sent to default number.
     Valid range/ values  : Phone number as string. You can give more
                            than one number. Separate them with colon:
                            "+3584544", "+3584545"
     Affected modules     : mon_autosms.c
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       : If you give more than one alternative number
                            then the amount of server numbers must be the
                            same as the amount of center numbers.
</conf> */

/* #define MULDER_AUTOSMS_ALIVE_KEY "Stats" */
/* <conf>
     Name                 : MULDER_AUTOSMS_ALIVE_KEY
     Type                 : FLAG_SETTING
     Description          : Enables creation of Extra record field to
                            AliveAutoSMS. Field is used to present PPC data.
                            Choose any string that descripes best the
                            PPC information and it is shown in the beginning
                            of Extra record field.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : AliveAutoSMS generates Extra record field.
     If feature is off    : AliveAutoSMS does not generate Extra record field.
     Valid range/ values  :
     Affected modules     : mon_autosms.c
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       : PPC data to be shown is defined with
                            MULDER_AUTOSMS_ALIVE_ITEMS flag.
</conf> */

#ifdef MULDER_AUTOSMS_ALIVE_KEY
#define MULDER_AUTOSMS_ALIVE_ITEMS MON_PPC_CUMUL_STANDBY_TIMER, MON_PPC_CUMUL_CALL_TIMER, \
                                      MON_PPC_UI_SMS_RECEIVE, MON_PPC_UI_SMS_SEND, \
                                      MON_PPC_MAX_BATTERY_TEMP_REACHED_COUNT, MON_PPC_MAX_BATTERY_TEMP_REACHED
/* <conf>
     Name                 : MULDER_AUTOSMS_ALIVE_ITEMS
     Type                 : FLAG_SETTING
     Description          : Here is defined the PPC data that shown in Extra record
                            field of AliveAutoSMS. Choose any byte, word or dword type PPCs.
     Specification        :
     Restrictions         : BYTE, WORD and DWORD type PPCs are supported.
                            PPC must also be defined in mon_ppc_conf.h.
                            MULDER_AUTOSMS_ALIVE_KEY must be defined.
     Associated
     features/ parameters :
     If feature is on     : PPC data shown in AliveAutoSMS.
     If feature is off    : PPC data is not shown in AliveAutoSMS.
     Valid range/ values  : Amount of PPC IDs: 1..255
     Affected modules     : mon_autosms.c
     Responsible          : Leon Joergensen
     Configuration type   : parameter
     Other comments       :
</conf> */
#endif

#define MULDER_DUMP_SECONDS ON
/* <conf>
     Name                 : MULDER_DUMP_SECONDS
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling/disabling inclusion of
                            seconds in the X-file name
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : -
     If feature is on     :
     If feature is off    :
     Valid range/ values  : ON enabled
                            OFF disable
     Affected modules     : mulder_autosms_pl, mulder_pmm_pl.c, mulder_pl_file.c
     Responsible          : Ole F. kristensen
     Configuration type   : feature
     Other comments       :
</conf> */

#define MULDER_REGISTER_MEM OFF
/* <conf>
     Name                 : MULDER_REGISTER_MEM
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enabling/disabling of dumping memory around
                            register values when creating an xfile
     Specification        :
     Restrictions         : Only to be used with CHIPSET_API
     Associated
     features/ parameters : -
     If feature is on     : This ident is included in xfile
     If feature is off    : This ident is NOT included in xfile
     Valid range/ values  : ON/OFF
     Affected modules     : mulder_assemble.h/c
     Responsible          : Ronny Hansen
     Configuration type   :
     Other comments       :
</conf> */

#define MULDER_DUMP_SEC_REASON ON
/* <conf>
     Name                 : MULDER_DUMP_SEC_REASON
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Flag is used for enabling/disabling inclusion of
                            security reset reason at security violation in
                            the X-file name
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : -
     If feature is on     :
     If feature is off    :
     Valid range/ values  : ON enabled
                            OFF disable
     Affected modules     : mulder_assemble.c
     Responsible          : Ole F. kristensen
     Configuration type   : feature
     Other comments       : Should only be ON if FEA_SEC_CRASH_DUMP_DATA_GET
                            is defined. Only valid for RAPU products
</conf> */

/* Insert new Mulder idents here */

typedef enum
{
    MULDER_NOT_ID                   =   0,
    MULDER_DATE                     =   1,
    MULDER_SW_VRS                   =   2,
    MULDER_ABORT                    =   3,
    MULDER_OS                       =   4,
    MULDER_CL                       =   5,
    MULDER_OS_INFO                  =   6,
    MULDER_ASSERT_INFO              =   7,
    MULDER_FILE_INFO                =   8,
    MULDER_PHONE_INFO               =   9,
    MULDER_MDI                      =  10,
    MULDER_INSTR_DUMP               =  11,
    MULDER_CALL_STACK               =  12,
    MULDER_FILE_NAME                =  13,
    MULDER_TRACE                    =  14,
    MULDER_ADSP                     =  15,
    MULDER_CDSP_MDI                 =  16,
    MULDER_ADSP_MDI                 =  17,
    MULDER_DSP                      =  18,
    MULDER_IAM                      =  19,
    MULDER_WATCHDOG                 =  20,
    MULDER_CS                       =  21,
    MULDER_CM_OBJ                   =  22,
    MULDER_CDSP_STATUS              =  23,
    MULDER_BB5_MDI_V1               =  24,
    MULDER_DSP_DATA_STATUS          =  25, /* Not used since Ng */
    MULDER_BTEMP                    =  26,
    MULDER_DYN_LD_SW_INFO           =  27,
    MULDER_OS_VMM_PAGER_ID          =  28,
    MULDER_OS_VMM_PAGER_CONF_ID     =  29,
    MULDER_ASSERT_REG_DUMP_ID       =  30,
    MULDER_NOS_ID                   =  31,
    MULDER_DSP_RF_HAL_ID            =  32,  /* Reserved for 9.2 */
    MULDER_ETB                      =  33,
    MULDER_SEC                      =  34,
    MULDER_REGISTER_DATA_MEM        =  35, /* Not used, no reference */
    MULDER_YAPAS_MEM_STATUS         =  36,
    MULDER_CRASHDUMP_CHIPSET_ID_00  = 240,
    MULDER_CRASHDUMP_CHIPSET_ID_01  = 241,
    MULDER_CRASHDUMP_CHIPSET_ID_02  = 242,
    MULDER_CRASHDUMP_CHIPSET_ID_03  = 243,
    MULDER_CRASHDUMP_CHIPSET_ID_04  = 244,
    MULDER_CRASHDUMP_CHIPSET_ID_05  = 245,
    MULDER_CRASHDUMP_CHIPSET_ID_06  = 246,
    MULDER_CRASHDUMP_CHIPSET_ID_07  = 247,
    MULDER_CRASHDUMP_CHIPSET_ID_08  = 248,
    MULDER_CRASHDUMP_CHIPSET_ID_09  = 249

}MULDER_IDS;


#if MULDER_YAPAS_MEM_DATA == ON
#define MULDER_IDENT_YAPAS_MEMORY_STR_SIZE  (6*sizeof(uint32))
#define MULDER_YAPAS_SIZE (MULDER_IDENT_YAPAS_MEMORY_STR_SIZE + 4 + 4)
#else
#define MULDER_YAPAS_SIZE 0
#endif


#if defined(MULDER_OS_DATA) && (MULDER_OS_DATA == ON)
  #define MULDER_OS_CRASH_DUMP_LEGACY_SIZE  0
  #define MULDER_OS_INFO_SIZE    (12 + MULDER_INDENT_ID_AND_LENGTH)
  #define __NOS_CRASH_DUMP_SIZE  (2000 + MULDER_INDENT_ID_AND_LENGTH)
  #define MULDER_NOS_DATA_SIZE   (MULDER_OS_CRASH_DUMP_LEGACY_SIZE + MULDER_OS_INFO_SIZE + __NOS_CRASH_DUMP_SIZE)
#else
  #define MULDER_NOS_DATA_SIZE 0
#endif


#if MULDER_CALL_STACK_DATA
     #define MULDER_CALL_STACK_DATA_SIZE (80 + MULDER_INDENT_ID_AND_LENGTH)
#else
    #define MULDER_CALL_STACK_DATA_SIZE 0
#endif

/* MULDER_REGISTER_MEM */
/* Number of bytes needed: */
/* For each 16 byte block: */
/* TLV REGISTER_MEM_ADDRESS_TAG: 6 bytes */
/* TLV REGISTER_MEM_MEMORY_DATA_TAG: 18 bytes */

/* For each Register: */
/* TLV REGISTER_MEM_REGISTER_TAG: 3 bytes */
/* TLV REGISTER_MEM_VALUE_TAG: 6 bytes */
/* Total number of bytes: */
/* 13 registers * number of 16 bytes blocks = 13 * (REGISTER_MEM_NR_OF_16_BLOCKS * 24 + 9) */
#if defined(MULDER_REGISTER_MEM) && (MULDER_REGISTER_MEM == ON)
  #define MULDER_REGISTER_MEM_NR_OF_16_BLOCKS 16
  #define MULDER_REGISTER_MEM_TOTAL_SIZE (13 * (MULDER_REGISTER_MEM_NR_OF_16_BLOCKS * 24 + 9))
  #define MULDER_REGISTER_MEM_SIZE MULDER_REGISTER_MEM_TOTAL_SIZE
#else
  #define MULDER_REGISTER_MEM_SIZE 0
#endif

#if MULDER_DUMP_SEC_REASON == ON
#define MULDER_SEC_SIZE 4*sizeof(uint32)
#else
#define MULDER_SEC_SIZE 0
#endif


/* Note! Makefile must get MULDER_SIZE from mulder_assemble.h for this */
#define MULDER_DAB_SIZE MULDER_SIZE + \
                        MULDER_YAPAS_SIZE + \
                        MULDER_NOS_DATA_SIZE + \
                        MULDER_CALL_STACK_DATA_SIZE + \
                        MULDER_SEC_SIZE + \
                        MULDER_REGISTER_MEM_SIZE + \
                        0  /* Add new required size+4 for new ident */

#endif      /*  MULDER_CONF_H */

/**************** Configuration of Ident collectors follows here ***********************************/


#ifdef MULDER_IDENT
#ifdef MULDER_START_IDENT_LIST

/* Add new required includes or external defines  */


#include "pn_crash_dump.h"
#include "mtc_crash_dump.h"

#if MULDER_OS_VMM_PAGER_DATA == 1
#include "os_vmm_crash_dump.h"
#endif /* MULDER_OS_VMM_PAGER_DATA == TRUE */

#if MULDER_IAM_DATA
extern Mulder_DCL_str *iam_crash_dump_get(void);
#endif

#if (MULDER_CALL_STACK_DATA==1)
#include "crashdump_chipset_api.h"
#endif

#include "libs_chipset_api.h"

#include "os_crash_dump.h"

#include "hal_sec_cmt_api.h"

extern void* hal_sec_crash_dump_data_get(void);

/* Here new ident handler functions must be specified */

/* MULDER_IDENT( ident_name, ident_collector, phases_to_collect_data, ident_extended_info) */

/*
ident_name : As specified in MULDER_IDS

ident_collector: Identification of collector function

phases_to_collect_data: The actual phases where to collect data shall be defined according to following masks:

MULDER_NORMAL        (xfile dump without reset)
MULDER_SOFT_RESET    (SW generates reset after data collection)
MULDER_PREWARNING_OF_RESET (HW reset coming very soon)
MULDER_STARTUP       (additional data collection after reboot)
MULDER_HARD_RESET    (HW reset occured without warning, all data collected after reboot)

legacy support, do not use these anymore:
#define MULDER_RESET            MULDER_SOFT_RESET
#define MULDER_WD_RESET         MULDER_HARD_RESET

Example: (MULDER_NORMAL | MULDER_SOFT_RESET) indicates dumping of data in Normal or SW Reset phase


ident_extended_info : Bitmask used for inclusion of additional information about the Ident to be used by the
                      X-File decoder. Transparent to Mulder.

#define FASTTRACE_SDK_DECODING_MASK         0x00
#define FASTTRACE_EXT_DLL_DECODING_MASK     0x01
*/

MULDER_START_IDENT_LIST

#if MULDER_TRACE_BUFFER_DATA
MULDER_IDENT(MULDER_TRACE, mulder_get_trace_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_OS_VMM_PAGER_DATA == TRUE
MULDER_IDENT(MULDER_OS_VMM_PAGER_ID, os_vmm_crash_dump_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)

MULDER_IDENT(MULDER_OS_VMM_PAGER_CONF_ID, os_vmm_crash_conf_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_CALL_STACK_DATA /* NOTE ! before dynamic loaded SW */
MULDER_IDENT(MULDER_CALL_STACK, chipset_mulder_callstack_get, (MULDER_NORMAL | MULDER_SOFT_RESET | MULDER_PREWARNING_OF_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_DYN_LD_SW_INFO_ENABLED == TRUE /* NOTE */
MULDER_IDENT(MULDER_DYN_LD_SW_INFO, vmm_dynsw_crash_dump_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_CDSP_STATUS_DATA
MULDER_IDENT(MULDER_CDSP_STATUS, mulder_cdsp_status_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_CM_OBJ_DATA
MULDER_IDENT(MULDER_CM_OBJ, mtc_cm_crash_dump_data_get, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_IAM_DATA
MULDER_IDENT(MULDER_IAM, iam_crash_dump_get, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_BB5_MDI_V1_DATA
MULDER_IDENT(MULDER_BB5_MDI_V1, mdi_cdsp_hw_crash_dump_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_MDI_DATA
MULDER_IDENT(MULDER_CDSP_MDI, mdi_cdsp_crash_dump_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_CL_DATA
MULDER_IDENT(MULDER_CL, PN_CrashDump_Data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

MULDER_IDENT(MULDER_ASSERT_INFO, mulder_get_assert_data, (MULDER_NORMAL | MULDER_STARTUP | MULDER_HARD_RESET), FASTTRACE_SDK_DECODING_MASK)

MULDER_IDENT(MULDER_ASSERT_REG_DUMP_ID, libs_assert_reg_dump, (MULDER_NORMAL | MULDER_STARTUP | MULDER_HARD_RESET), FASTTRACE_SDK_DECODING_MASK)

#if (MULDER_OS_DATA == ON)
/* mulder_get_os_info_data is used for getting OS data into the AutoSMS */
MULDER_IDENT(MULDER_OS_INFO, mulder_get_os_info_data, (MULDER_NORMAL | MULDER_STARTUP | MULDER_HARD_RESET), FASTTRACE_SDK_DECODING_MASK)
/* os_crash_dump_data_get is used both internally and for Chipset Supplers.
   This ident requires a decode DLL delivered by the OS responsibles */
MULDER_IDENT(MULDER_NOS_ID, os_crash_dump_data_get, (MULDER_NORMAL | MULDER_SOFT_RESET | MULDER_HARD_RESET), FASTTRACE_EXT_DLL_DECODING_MASK)
#endif /* (MULDER_OS_DATA == ON) */


#if MULDER_ABORT_DATA
MULDER_IDENT(MULDER_ABORT, mulder_get_abort_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)

MULDER_IDENT(MULDER_INSTR_DUMP, mulder_get_abort_instr_data, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_WATCHDOG_DATA
MULDER_IDENT(MULDER_WATCHDOG, mtc_wd_crash_dump_data_get, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_DUMP_SEC_REASON == ON
MULDER_IDENT(MULDER_SEC, (Mulder_dump_fn*)hal_sec_crash_dump_data_get, MULDER_HARD_RESET, FASTTRACE_SDK_DECODING_MASK)
#endif

#if defined(MULDER_REGISTER_MEM) && (MULDER_REGISTER_MEM == ON)
MULDER_IDENT(MULDER_REGISTER_DATA_MEM, mulder_register_data_mem, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_SDK_DECODING_MASK)
#endif

#if MULDER_YAPAS_MEM_DATA == ON
MULDER_IDENT(MULDER_YAPAS_MEM_STATUS, mulder_ident_yapas_get_memory_pool_status, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_EXT_DLL_DECODING_MASK)
#endif

#if MULDER_CRASHDUMP_CHIPSET_DATA_09 == ON
MULDER_IDENT(MULDER_CRASHDUMP_CHIPSET_ID_09, crashdump_chipset_data_get_09, (MULDER_NORMAL | MULDER_SOFT_RESET), FASTTRACE_EXT_DLL_DECODING_MASK)
#endif
MULDER_END_IDENT_LIST

#endif /* MULDER_START_IDENT_LIST */

#endif  /* MULDER_IDENT */
/* end of file */
